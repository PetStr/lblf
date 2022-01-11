/*
 * Copyright (C) 2021 Petter Strandh.
 * Contact: petter.strandh@gmail.com
 *
 *
 */

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "blf_structs.hh"
#include "count_id.hh"
#include "print.hh"

//Forward declaration. Just to handle that functions are not in order.
exit_codes handle_ObjectType(std::fstream &fs, const BaseHeader &ohb);
void handleCanMessage(ObjectHeader const & oh, CanMessage const & message);


const uint32_t FileSignature = 0x47474F4C;   //LOGG
const uint32_t ObjectSignature = 0x4A424F4C; //LOBJ

static uint64_t u64_from_can_msg(const uint8_t m[8])
{
    return ((uint64_t)m[7] << 56) | ((uint64_t)m[6] << 48) |
           ((uint64_t)m[5] << 40) | ((uint64_t)m[4] << 32) |
           ((uint64_t)m[3] << 24) | ((uint64_t)m[2] << 16) |
           ((uint64_t)m[1] << 8) | ((uint64_t)m[0] << 0);
}


void printData(uint8_t *data, size_t size)
{
    if ((data == nullptr) || (size == 0))
        {
            return;
        }

    std::cout << "[";
    for (size_t i = 0; i < size; ++i)
        {
            uint16_t value = data[i];
            if (i > 0)
                {
                    std::cout << " ";
                }
            std::cout << std::setfill('0') << std::setw(2) << std::hex
                      << static_cast<uint16_t>(value);
        }
    std::cout << "]";
}



uint32_t fileLength(std::fstream &fs)
{
    fs.seekg(0, std::fstream::end);
    uint32_t length = fs.tellg();
    fs.seekg(0, std::fstream::beg);
    return length;
}


bool read(std::fstream &fs, fileStatistics &os)
{
    fs.read(reinterpret_cast<char *>(&os.FileSign), sizeof(os.FileSign));
    if (os.FileSign != FileSignature)
        {
            return false;
        }

    fs.read(reinterpret_cast<char *>(&os.StatSize), sizeof(os.StatSize));
    fs.read(reinterpret_cast<char *>(&os.AppId), sizeof(os.AppId));
    fs.read(reinterpret_cast<char *>(&os.AppMaj), sizeof(os.AppMaj));
    fs.read(reinterpret_cast<char *>(&os.AppMin), sizeof(os.AppMin));
    fs.read(reinterpret_cast<char *>(&os.AppBuild), sizeof(os.AppBuild));
    fs.read(reinterpret_cast<char *>(&os.ApiMaj), sizeof(os.ApiMaj));
    fs.read(reinterpret_cast<char *>(&os.ApiMin), sizeof(os.ApiMin));
    fs.read(reinterpret_cast<char *>(&os.ApiBuild), sizeof(os.ApiBuild));
    fs.read(reinterpret_cast<char *>(&os.ApiPatch), sizeof(os.ApiPatch));
    fs.read(reinterpret_cast<char *>(&os.fileSize), sizeof(os.fileSize));
    fs.read(reinterpret_cast<char *>(&os.uncompressedSize), sizeof(os.uncompressedSize));
    fs.read(reinterpret_cast<char *>(&os.objCount), sizeof(os.objCount));
    fs.read(reinterpret_cast<char *>(&os.objRead), sizeof(os.objRead));
    fs.read(reinterpret_cast<char *>(&os.meas_start_time), sizeof(os.meas_start_time));
    fs.read(reinterpret_cast<char *>(&os.last_obj_time), sizeof(os.last_obj_time));
    fs.read(reinterpret_cast<char *>(&os.fileSize_less115), sizeof(os.fileSize_less115));
    auto offset = os.StatSize - sizeof(fileStatistics);
    fs.seekg(offset, std::ios_base::cur);
    return true;
}


bool read(std::fstream &fs, BaseHeader &ohb)
{
    fs.read(reinterpret_cast<char *>(&ohb.ObjSign), sizeof(ohb.ObjSign));
    if (ohb.ObjSign != ObjectSignature)
        {
            std::cout << "Not Found LOBJ: " << std::hex << static_cast<int> (ohb.ObjSign);
            std::cout << '\n';
            return false;
        }
    fs.read(reinterpret_cast<char *>(&ohb.headerSize), sizeof(ohb.headerSize));
    fs.read(reinterpret_cast<char *>(&ohb.headerVer), sizeof(ohb.headerVer));
    fs.read(reinterpret_cast<char *>(&ohb.objSize), sizeof(ohb.objSize));
    fs.read(reinterpret_cast<char *>(&ohb.objectType), sizeof(ohb.objectType));
    return true;
}


bool read(const uint8_t * data, BaseHeader &ohb)
{
    std::memcpy(&ohb.ObjSign, data, sizeof(ohb.ObjSign));
    if (ohb.ObjSign != ObjectSignature)
        {
            std::cout << "Not Found LOBJ: " << std::hex << static_cast<int> (ohb.ObjSign);
            std::cout << '\n';
            return false;
        }
    data = data + sizeof(ohb.ObjSign);
    std::memcpy(&ohb.headerSize, data, sizeof(ohb.headerSize));
    data = data + sizeof(ohb.headerSize);
    std::memcpy(&ohb.headerVer, data, sizeof(ohb.headerVer));
    data = data + sizeof(ohb.headerVer);
    std::memcpy(&ohb.objSize, data, sizeof(ohb.objSize));
    data = data + sizeof(ohb.objSize);
    std::memcpy(&ohb.objectType, data, sizeof(ohb.objectType));
    return true;
}


bool read(std::fstream &fs, LogContainer &lc, const BaseHeader &ohb)
{
    fs.read(reinterpret_cast<char *>(&lc), sizeof(LogContainer));

    if (lc.compressionMethod == compressionMethod_e::uncompressed)
        {
            lc.unCompressedFileSize = ohb.objSize - sizeof(lc.compressionMethod) - sizeof(lc.reserv1) - sizeof(lc.reserv2) - sizeof(lc.unCompressedFileSize) - sizeof(lc.reserv3);
        }

    return true;
}


template <typename type_data>
bool read_template(std::fstream &fs, type_data &data)
{
    fs.read(reinterpret_cast<char *>(&data), sizeof(type_data));
    return true;
}


exit_codes parse_container_uncompressed(std::fstream &fs, const LogContainer &lc)
{
    int32_t bytes_left_in_container = lc.unCompressedFileSize;
    bool run = true;
    while(run)
        {
            struct BaseHeader ohb;
            if (read(fs, ohb))
                {
                    //print(std::cout, ohb);
                }
            else
                return exit_codes::UNABLE_TO_READ_OBJECT_HEADER_BASE;

            handle_ObjectType(fs, ohb);
            bytes_left_in_container = bytes_left_in_container - ohb.objSize;
            //std::cout << "LogContainer/ bytes left: " << std::dec << bytes_left_in_container << '\n';
            if(bytes_left_in_container <= 16) //Changed this a bit randomly. migth be some junk at the end. mod 4. 
                run = false;
        }
    return exit_codes::EXITING_SUCCESS;
}


exit_codes handle_ObjectType(std::fstream &fs, const BaseHeader &ohb)
{
    const auto payload_size = ohb.objSize-ohb.headerSize;
    switch (ohb.objectType)
        {
        case (ObjectType_e::LOG_CONTAINER): //Get Logcontainer
        {
            struct LogContainer lc;
            read(fs, lc, ohb);
            if(lc.compressionMethod == compressionMethod_e::uncompressed)
                {
                    //Lets work through the logcontainer.
                    if(parse_container_uncompressed(fs, lc) == exit_codes::EXITING_SUCCESS)
                        {
                            std::cout << "LogContainer handled.\n";
                        }
                    else
                        {
                            std::cout << "LogContainer walk through failed.\n";
                            return exit_codes::LOGCONTAINER_WALK_THROUGH_FAIL;
                        }
                }
        }
        break;

        case (ObjectType_e::CAN_MESSAGE): //read Can message;
        {
            struct ObjectHeader oh;
            read_template(fs, oh);
            if(payload_size == sizeof(CanMessage))
                {
                    struct CanMessage cm;
                    if (read_template(fs, cm))
                        {
                            handleCanMessage(oh,cm);

                        }
                }
            else
                {
                    return exit_codes::CAN_MESSAGE_INVALID_LENGTH;
                }
        }
        break;

        case (ObjectType_e::CAN_MESSAGE2):
        {
            struct ObjectHeader oh;
            read_template(fs, oh);
            struct CanMessage2 cm2;
            if (read_template(fs, cm2))
                {
                    // DO nothing now. handle(cm2);
                }
            else
                {
                    return exit_codes::CAN_MESSAGE_INVALID_LENGTH;
                }
        }
        break;

        default:
        {
            auto bytes_to_jump = 0;
            if(ohb.headerSize == 16)
                bytes_to_jump = ohb.objSize - ohb.headerSize;

            if(ohb.headerSize == 32)
                bytes_to_jump = ohb.objSize - ohb.headerSize + 16;

            fs.seekg(bytes_to_jump,std::ios_base::cur);
        }
        }
    return exit_codes::EXITING_SUCCESS;
}


void handleCanMessage(ObjectHeader const & oh, CanMessage const & message)
{
    const uint32_t ETC2_X_TECU = 0x98f00503;

    //static means memeber the value throuout the lifetime of the program. initial value 0.
    static uint64_t last_time = 0;
    static uint32_t last_gear = 0;
    static bool first_time = true;

    if (message.dlc != 8) //if dlc is not 8 I am not interested.
        return;
   
    uint64_t time = oh.objectTimeStamp;

    if(message.id == ETC2_X_TECU)
        {
             uint64_t can_bits = u64_from_can_msg(message.data.data());
            /* TransmissionCurrentGear: start-bit 24, length 8, endianess intel, scaling
               * 1, offset -125 */
            uint32_t gear = ((can_bits >> 24) & 0xff) - 125;

            if (gear != last_gear)
                {

                    if (first_time)
                        {
                            last_time = time;
                            last_gear = gear;
                            first_time = false;
                        }

                    uint64_t passed_time = time - last_time;
                    std::cout << passed_time / 1000000000.0 << ";" << last_gear << '\n';
                    last_gear = gear;
                    last_time = time;
                }

        }
}


exit_codes go_through_blf_file(const char * const filename)
{
    std::cout << "Opening file: " << filename;
    std::fstream fs(filename, std::fstream::in | std::fstream::binary);
    if (fs.fail())
        {
            std::cout << " ";
            std::cout << "File open failed, Exiting program\n";
            return exit_codes::UNABLE_TO_OPEN_FILE;
        }
    else
        {
            std::cout << " ** SUCCESS **\n";
        }

    auto filelength = fileLength(fs);

    if (fs)
        {
            struct fileStatistics fileStat;
            if (read(fs, fileStat))
                {
                    //
                }
            else
                {
                    std::cout << "Error file is not a BLF file\n";
                    fs.close();
                    return exit_codes::NOT_A_VALID_BLF_FILE;
                }
        }

    while (!fs.eof())
        {
            if((filelength - fs.tellg() == 0))
                break;
            //std::cout << __FUNCTION__ << "Bytes left: " << filelength - fs.tellg() << '\n';
            struct BaseHeader ohb;
            if (read(fs, ohb))
                {
                    handle_ObjectType(fs, ohb);
                }
            else
                {
                    std::cout << __FUNCTION__ << ':' << __LINE__ << " Unable to read BaseHeader\n";
                    fs.close();
                    return exit_codes::UNABLE_TO_READ_OBJECT_HEADER_BASE;
                }
        }
    fs.close();
    return exit_codes::EXITING_SUCCESS;
}


int main(int argc, char *argv[])
{
    if (argc != 2)
        {
            std::cout << "./tell_gear <filename.blf>" << '\n';
            return -1;
        }

    const char * const filename = argv[1];


    exit_codes result = go_through_blf_file(filename);

    if(result != exit_codes::EXITING_SUCCESS)
        {
            std::cout << print(result) << '\n';
            std::cout << "Exiting\n";
            return(EXIT_FAILURE);
        }


    return EXIT_SUCCESS;
}
