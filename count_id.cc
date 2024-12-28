/*
 * Copyright (C) 2021 Petter Strandh.
 * Contact: petter.strandh@gmail.com
 */


#include "blf_reader.hh"
#include "blf_structs.hh"
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>


struct dbc_id_data
{
    uint8_t dbc_table {0};
    uint32_t id {0};
    std::string id_name;
};


struct dbc_names
{
    const char *const short_name;
    const char *const file_name;
};


static const dbc_names DBC[] = {
    {"Backbone1J1939_mod_DM1_v2.dbc", "Backbone1J1939_mod_DM1_v2.dbc"},
    {"DiagnosticsLink.dbc", "DiagnosticsLink.dbc"},
    {"DisplaySubnet.dbc", "DisplaySubnet.dbc"},
    {"InfotainmentSubnet.dbc", "InfotainmentSubnet.dbc"},
    {"bb1.dbc", "bb1.dbc"},
    {"bb1_t2.dbc", "bb1_t2.dbc"},
    {"bb2.dbc", "bb2.dbc"},
    {"bb2_t2.dbc", "bb2_t2.dbc"},
    {"engine_subnet.dbc", "engine_subnet.dbc"},
    {"engine_subnet_t2.dbc", "engine_subnet_t2.dbc"},
    {"ptcan.dbc", "ptcan.dbc"},
    {"ptcan_t2.dbc", "ptcan_t2.dbc"},
};

const int DBC_number = 12;


using namespace lblf;

const size_t CAN_ID_MARK = 1;
const size_t CAN_NAME_MARK = 2;


// Forward declaration.
auto handle_ObjectType(std::fstream &fs, const BaseHeader &ohb) -> exit_codes;

struct can_counter_record
{
    uint32_t id;
    uint16_t channel;
    uint32_t hit_counter;
};

// Global
namespace GLOBAL
{
std::vector<can_counter_record> id_data; // NOLINT
uint32_t can_frame_counter;              // NOLINT
} // namespace GLOBAL


auto can_id_name_func(std::string &can_id_name, const uint32_t can_id, const std::vector<dbc_id_data> &dbc_table) -> uint8_t
{
    uint8_t bank = 0xff;
    can_id_name.clear();
    for (const auto &itr: dbc_table)
        {
            if (itr.id == can_id)
                {
                    can_id_name = itr.id_name;
                    bank = itr.dbc_table;
                    break;
                }
        }
    return bank;
}


void can_id_count(std::vector<can_counter_record> &id_record, const uint32_t can_id, const uint8_t channel)
{
    // Lookfor id in vector. If it does not exist add it. if it does exist count one.
    bool found_first_time = false;
    auto size_vector = id_record.size();

    for (uint32_t itr = 0; itr < size_vector; ++itr)
        {
            if ((can_id == id_record[itr].id) && (channel == id_record[itr].channel))
                {
                    // cout << "found_first_time existing." << '\n';
                    id_record[itr].hit_counter++;
                    found_first_time = true;
                    break;
                }
        }

    if (!found_first_time)
        {
            struct can_counter_record can_id_data = {can_id, channel, 1};
            id_record.push_back(can_id_data);
        }
}


auto begin_does_exist(const std::string &str, const std::string &to_find) -> bool
{
    auto pos = str.find(to_find);
    // if (pos != std::string::npos)
    return pos == 0;
}


void find_marks(std::vector<size_t> &marks, const std::string &row, const std::string &column_divider)
{
    marks.clear();
    for (std::string::size_type i = 0; i < row.size(); i++)
        {
            if (row[i] == column_divider[0])
                {
                    marks.push_back(i);
                }
        }
    // adding beginning and end that does not have marks.
    marks.insert(marks.begin(), -1);
    marks.push_back(row.size());
}


auto partString(std::string const &row,
    std::vector<size_t> const &marks,
    size_t index) -> std::string
{
    return row.substr(marks[index] + 1, (marks[index + 1] - marks[index]) - 1);
}


auto toInt(const std::string &s) -> uint64_t
{
    char *end = nullptr;
    const int base {10};
    return std::strtoul(s.c_str(), &end, base);
}


auto read_dbc_file(std::ifstream &infile,
    std::vector<dbc_id_data> &dbc_data,
    const std::string &separator,
    const uint8_t bank) -> bool
{
    std::string row;
    std::vector<size_t> marks;
    bool exit_status = false;
    while (getline(infile, row))
        {
            if (begin_does_exist(row, "BO_"))
                {
                    struct dbc_id_data dbc_data_temp;
                    find_marks(marks, row, separator);
                    dbc_data_temp.dbc_table = bank;
                    dbc_data_temp.id = toInt(partString(row, marks, CAN_ID_MARK)); // &  0xCFFFFFFF;
                    dbc_data_temp.id_name = partString(row, marks, CAN_NAME_MARK);
                    dbc_data_temp.id_name.pop_back(); // remove last character which is a :
                    dbc_data.push_back(dbc_data_temp);
                    exit_status = true;
                }
        }
    return exit_status;
}


auto parse_dbc_file(const std::string &filename,
    std::vector<dbc_id_data> &dbc_data,
    const std::string &separator,
    const uint8_t bank) -> bool
{
    std::ifstream infile;
    infile.open(filename.c_str());

    if (infile.good())
        {
            return read_dbc_file(infile, dbc_data, separator, bank);
        }
    else
        {
            std::cout << __LINE__ << " failed to open file: " << filename << '\n';
            return false;
        }
    return false;
}


void print_frameid_dbcdata(std::ostream &stream,
    std::vector<can_counter_record> &id_data,
    std::vector<dbc_id_data> &dbc_data)
{
    std::string can_id_name;
    stream << "channel"
           << "\t"
           << "id_dec"
           << "\t"
           << "id_hex"
           << "\t"
           << "hits"
           << "\t"
           << "dbc_file"
           << "\t"
           << "frame_name" << '\n';
    // Got through id_data.

    for (uint8_t channel = 0; channel < 10; channel++)
        {

            for (auto itr: id_data)
                {
                    if (itr.channel == channel)
                        {
                            uint8_t bank = can_id_name_func(can_id_name, itr.id, dbc_data);
                            if (bank == 0xff)
                                {
                                    stream << static_cast<int>(itr.channel) << "\t" << itr.id << "\t0x"
                                           << std::hex << itr.id << "\t" << std::dec << itr.hit_counter
                                           << "\t"
                                           << "unknown"
                                           << "\t"
                                           << "unknown" << '\n';
                                }
                            else
                                {
                                    stream << static_cast<int>(itr.channel) << "\t" << itr.id << "\t0x"
                                           << std::hex << itr.id << "\t" << std::dec << itr.hit_counter
                                           << "\t" << DBC[bank].short_name << "\t" << can_id_name << '\n';
                                }
                        }
                }
        }
}


void print_dbcdata(std::ostream &stream, std::vector<dbc_id_data> &dbc_data)
{
    for (const auto &data: dbc_data)
        {
            stream << std::dec << data.id << ", 0x" << std::hex << data.id << ", " << data.id_name << '\n';
        }
}


/**
 * @brief support operator for enum typed data.
 *
 */
template <typename stream_type>
auto operator>>(stream_type &is, AppId_e &aid) -> std::istream &
{
    uint8_t temp;
    is >> temp;
    aid = static_cast<AppId_e>(temp);
    return is;
}


/**
 * @brief support operator for getting sysTime.
 *
 */
template <typename stream_type>
auto operator>>(stream_type &is, sysTime_t &st) -> stream_type &
{
    is >> st.year;
    is >> st.month;
    is >> st.dayOfWeek;
    is >> st.day;
    is >> st.hour;
    is >> st.minute;
    is >> st.second;
    is >> st.milliseconds;
    return is;
}


template <typename type_data>
auto read_template(const char *indata_array, type_data &data) -> size_t
{
    std::memcpy(reinterpret_cast<char *>(&data), indata_array, sizeof(type_data));
    return sizeof(type_data);
}


auto main(int argc, char *argv[]) -> int
{
    if (argc != 2)
        {
            std::cout << "count_id <filename.blf>" << '\n';
            return -1;
        }

    const std::string filename = argv[1];


    std::string separator(" ");
    std::vector<dbc_id_data> dbc_data;

    for (int n = 0; n < DBC_number; n++)
        {
            std::string filename_dbc(DBC[n].file_name);
            if (parse_dbc_file(filename_dbc, dbc_data, separator, n))
                std::cout << "Success reading: " << DBC[n].file_name << '\n';
        }

    GLOBAL::can_frame_counter = 0;

    lblf::blf_reader reader(filename);

    while (reader.next())
        {
            const auto data = reader.data();
            if (data.base_header.objectType == lblf::ObjectType_e::CAN_MESSAGE2)
                {
                    GLOBAL::can_frame_counter++;
                    struct lblf::CanMessage2_obh can2;
                    if (sizeof(can2) <= data.payload.size())
                        {
                            read_template(data.payload.data(), can2);
                            unsigned int can_id = can2.id;
                            unsigned char channel = can2.channel;
                            can_id_count(GLOBAL::id_data, can_id, channel);
                        }
                }

            if (data.base_header.objectType == lblf::ObjectType_e::CAN_MESSAGE)
                {
                    GLOBAL::can_frame_counter++;
                    struct lblf::CanMessage_obh can2;
                    if (sizeof(can2) <= data.payload.size())
                        {
                            read_template(data.payload.data(), can2);
                            unsigned int can_id = can2.id;
                            unsigned char channel = can2.channel;
                            can_id_count(GLOBAL::id_data, can_id, channel);
                        }
                }
        }
    print_frameid_dbcdata(std::cout, GLOBAL::id_data, dbc_data);
    std::cout << "Number of dbc frames: " << dbc_data.size() << '\n';

    std::cout << "Number of different frames: " << GLOBAL::id_data.size()
              << " total number of frames in blf:" << GLOBAL::can_frame_counter << '\n';
    return EXIT_SUCCESS;
}


#ifdef TEST_DBC
int main(int argc, char *argv[])
{
    if (argc != 2)
        {
            std::cout << "count_id <filename.blf>" << '\n';
            return -1;
        }

    const char *const filename = argv[1];
    std::string separator(" ");
    std::vector<dbc_id_data> dbc_data;

    for (int n = 0; n < DBC_number; n++)
        {
            std::string filename(DBC[n].file_name);
            if (parse_dbc_file(filename, dbc_data, separator, n))
                std::cout << "Success reading: " << DBC[n].file_name << '\n';
        }

    print_dbcdata(std::cout, dbc_data);

    return EXIT_SUCCESS;
}
#endif
