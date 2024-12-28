/*
 * Copyright (C) 2021 Petter Strandh.
 * Contact: petter.strandh@gmail.com
 *
 *
 */

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

#include "blf_reader.hh"
#include "blf_structs.hh"
#include "print.hh"


const uint32_t ETC2_X_TECU = 0x98f00503;

auto u64_from_can_msg(const std::array<uint8_t, 8> candata) -> uint64_t
{
    return ((uint64_t) candata[7] << 56U) | ((uint64_t) candata[6] << 48U) | ((uint64_t) candata[5] << 40U) | ((uint64_t) candata[4] << 32U) | ((uint64_t) candata[3] << 24U) | ((uint64_t) candata[2] << 16U) | ((uint64_t) candata[1] << 8U) | ((uint64_t) candata[0] << 0U);
}


template <typename type_data>
auto read_template(const char *indata_array, type_data &data) -> size_t
{
    std::memcpy(reinterpret_cast<char *>(&data), indata_array, sizeof(type_data));
    return sizeof(type_data);
}


auto fileLength(std::fstream &fs) -> uint32_t
{
    fs.seekg(0, std::fstream::end);
    uint32_t length = fs.tellg();
    fs.seekg(0, std::fstream::beg);
    return length;
}


void handleCanMessage(lblf::lobj const &data)
{
    static uint64_t last_time = 0;
    static int32_t last_gear = 0;
    static bool first_time = true;

    if (data.base_header.objectType == lblf::ObjectType_e::CAN_MESSAGE2)
        {
            struct lblf::CanMessage2_obh can;
            if (sizeof(can) <= data.payload.size())
                {
                    read_template(data.payload.data(), can);
                }
            else
                {
                    return;
                }

            if (can.dlc != 8)
                { // if dlc is not 8 I am not interested.
                    return;
                }

            uint64_t time = can.obh.objectTimeStamp;

            if (can.id == ETC2_X_TECU)
                {
                    uint64_t can_bits = u64_from_can_msg(can.data);
                    /* TransmissionCurrentGear: start-bit 24, length 8, endianess intel, scaling
                     * 1, offset -125 */
                    int32_t gear = ((can_bits >> 24U) & 0xFFU) - 125;

                    if (gear != last_gear)
                        {
                            if (first_time)
                                {
                                    last_time = time;
                                    last_gear = gear;
                                    first_time = false;
                                }

                            uint64_t passed_time = time - last_time;
                            std::cout << static_cast<double>(passed_time) / 1000000000.0 << ";" << last_gear << '\n';
                            last_gear = gear;
                            last_time = time;
                        }
                }
        }
}


auto go_through_blf_file(const std::string &filename) -> lblf::exit_codes
{
    lblf::blf_reader reader(filename);
    while (reader.next())
        {
            handleCanMessage(reader.data());
        }
    return lblf::exit_codes::EXITING_SUCCESS;
}


int main(int argc, char *argv[])
{
    if (argc != 2)
        {
            std::cout << "./tell_gear <filename.blf>" << '\n';
            return -1;
        }

    const std::string filename = argv[1];


    lblf::exit_codes result = go_through_blf_file(filename);

    if (result != lblf::exit_codes::EXITING_SUCCESS)
        {
            return (EXIT_FAILURE);
        }

    return EXIT_SUCCESS;
}
