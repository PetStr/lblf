/*
 * Copyright (C) 2021 Petter Strandh.
 * Contact: petter.strandh@gmail.com
 */

//g++ count_id.cc -o count_id -Wall -Wextra -Wpedantic -Wno-switch -O0 -g

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "blf_structs.hh"
#include "count_id.hh"
#include "print.hh"



const size_t CAN_ID_MARK = 1;
const size_t CAN_NAME_MARK = 2;

const uint32_t FileSignature = 0x47474F4C;   //LOGG
const uint32_t ObjectSignature = 0x4A424F4C; //LOBJ

//Forward declaration.
exit_codes handle_ObjectType(std::fstream &fs, const ObjectHeaderBase &ohb);

struct can_counter_record
{
    uint32_t id;
    uint16_t channel;
    uint32_t hit_counter;
};

//Global
namespace GLOBAL
{
std::vector <can_counter_record> id_data;
uint32_t can_frame_counter;
}


uint8_t can_id_name_func(std::string & can_id_name, const uint32_t can_id, const std::vector <dbc_id_data> &dbc_table)
{
    uint8_t bank = 0xff;
    can_id_name.clear();
    for(const auto &itr : dbc_table)
        {
            if(itr.id == can_id)
                {
                    can_id_name = itr.id_name;
                    bank = itr.dbc_table;
                    break;
                }
        }
    return bank;
}


void can_id_count(std::vector<can_counter_record> & id_record, const uint32_t can_id, const uint8_t channel)
{
//Lookfor id in vector. If it does not exist add it. if it does exist count one.
    bool found_first_time = false;
    auto size_vector = id_record.size();

    for(uint32_t itr = 0; itr < size_vector; ++itr)
        {
            if((can_id == id_record[itr].id) && (channel == id_record[itr].channel))
                {
                    // cout << "found_first_time existing." << '\n';
                    id_record[itr].hit_counter++;
                    found_first_time = true;
                    break;
                }
        }

    if(!found_first_time)
        {
            struct can_counter_record can_id_data = {can_id, channel, 1};
            id_record.push_back(can_id_data);
        }
}


bool begin_does_exist(const std::string &str, const std::string &to_find)
{
    auto pos = str.find(to_find);
    //if (pos != std::string::npos)
    if (pos == 0)
        {
            return true;
        }
    else
        {
            return false;
        }
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
    //adding beginning and end that does not have marks.
    marks.insert(marks.begin(), -1);
    marks.push_back(row.size());
}


std::string partString(std::string const &row, std::vector<size_t> const &marks, size_t index)
{
    return row.substr(marks[index] + 1, (marks[index + 1] - marks[index]) - 1);
}


uint64_t toInt(const std::string &s)
{
    char * end = nullptr;
    const int base {10};
    return std::strtoul(s.c_str(), &end, base);
}


bool read_dbc_file(std::ifstream & infile, std::vector<dbc_id_data> & dbc_data, const std::string & separator, const uint8_t bank)
{
    std::string row;
    std::vector<size_t> marks;
    bool exit_status = false;
    while(getline(infile, row))
        {
            if(begin_does_exist(row,"BO_"))
                {
                    struct dbc_id_data dbc_data_temp;
                    find_marks(marks, row, separator);
                    dbc_data_temp.dbc_table = bank;
                    dbc_data_temp.id = toInt(partString(row, marks, CAN_ID_MARK)); // &  0xCFFFFFFF;
                    dbc_data_temp.id_name = partString(row, marks, CAN_NAME_MARK);
                    dbc_data_temp.id_name.pop_back(); //remove last character which is a :
                    dbc_data.push_back(dbc_data_temp);
                    exit_status = true;
                }
        }
    return exit_status;
}


bool parse_dbc_file(const std::string &filename, std::vector <dbc_id_data> & dbc_data, const std::string & separator, const uint8_t bank)
{
    std::ifstream infile;
    infile.open(filename.c_str());

    if (infile.good())
        {
            return read_dbc_file(infile, dbc_data, separator, bank);
        }
    else
        {
            std::cout << __LINE__ <<  " failed to open file: " << filename << '\n';
            return false;
        }
    return false;
}


void print_frameid_dbcdata(std::ostream & stream, std::vector <can_counter_record> & id_data, std::vector<dbc_id_data> & dbc_data)
{
    std::string can_id_name;
    stream <<  "channel" << "\t" << "id_dec" << "\t" << "id_hex" << "\t" << "hits" << "\t" << "dbc_file" << "\t" << "frame_name" << '\n';
    //Got through id_data.

    for(uint8_t channel = 0; channel <10; channel++)
        {

            for(auto itr : id_data)
                {
                    if(itr.channel == channel)
                        {
                            uint8_t bank = can_id_name_func(can_id_name, itr.id, dbc_data);
                            if(bank == 0xff)
                                {
                                    stream << static_cast<int> (itr.channel)  << "\t" << itr.id << "\t0x"
                                           << std::hex << itr.id << "\t" << std::dec << itr.hit_counter
                                           << "\t" << "unknown" << "\t" << "unknown" << '\n';
                                }
                            else
                                {
                                    stream << static_cast<int> (itr.channel)  << "\t" << itr.id << "\t0x"
                                           << std::hex << itr.id << "\t" << std::dec << itr.hit_counter
                                           << "\t" << DBC[bank].short_name << "\t" << can_id_name << '\n';
                                }
                        }
                }
        }
}


void print_dbcdata(std::ostream & stream, std::vector<dbc_id_data> & dbc_data)
{
    for(const auto &data : dbc_data)
        {
            stream << std::dec << data.id << ", 0x" << std::hex << data.id << ", " << data.id_name << '\n';
        }
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


bool read(std::fstream &fs, ObjectHeaderBase &ohb)
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


bool read(const uint8_t * data, ObjectHeaderBase &ohb)
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


bool read(std::fstream &fs, LogContainer &lc, const ObjectHeaderBase &ohb)
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
            struct ObjectHeaderBase ohb;
            if (read(fs, ohb))
                {
                    //print(std::cout, ohb);
                }
            else
                return exit_codes::UNABLE_TO_READ_OBJECT_HEADER_BASE;

            handle_ObjectType(fs, ohb);
            bytes_left_in_container = bytes_left_in_container - ohb.objSize;
            //std::cout << "LogContainer/ bytes left: " << std::dec << bytes_left_in_container << '\n';
            if(bytes_left_in_container <= 0)
                run = false;
        }
    return exit_codes::EXITING_SUCCESS;
}


exit_codes handle_ObjectType(std::fstream &fs, const ObjectHeaderBase &ohb)
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
                    GLOBAL::can_frame_counter++;
                    struct CanMessage cm;
                    if (read_template(fs, cm))
                        {
                            unsigned int can_id = cm.id;
                            unsigned char channel = cm.channel;
                            can_id_count(GLOBAL::id_data, can_id, channel);
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
            GLOBAL::can_frame_counter++;
            struct ObjectHeader oh;
            read_template(fs, oh);
            struct CanMessage2 cm2;
            if (read_template(fs, cm2))
                {
                    unsigned int can_id = cm2.id;
                    unsigned char channel = cm2.channel;
                    can_id_count(GLOBAL::id_data, can_id, channel);
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
            struct ObjectHeaderBase ohb;
            if (read(fs, ohb))
                {
                    handle_ObjectType(fs, ohb);
                }
            else
                {
                    std::cout << __FUNCTION__ << ':' << __LINE__ << " Unable to read ObjectHeaderBase\n";
                    fs.close();
                    return exit_codes::UNABLE_TO_READ_OBJECT_HEADER_BASE;
                }
        }
    fs.close();
    return exit_codes::EXITING_SUCCESS;
}


#ifdef TEST_DBC
int main(int argc, char *argv[])
{
    if (argc != 2)
        {
            std::cout << "count_id <filename.blf>" << '\n';
            return -1;
        }

    const char * const filename = argv[1];
    std::string separator(" ");
    std::vector<dbc_id_data> dbc_data;

    for(int n = 0; n < DBC_number; n++)
        {
            std::string filename(DBC[n].file_name);
            if(parse_dbc_file(filename, dbc_data, separator,n))
                std::cout << "Success reading: " << DBC[n].file_name << '\n';
        }

    print_dbcdata(std::cout, dbc_data);

    return EXIT_SUCCESS;
}
#endif


int main(int argc, char *argv[])
{
    if (argc != 2)
        {
            std::cout << "count_id <filename.blf>" << '\n';
            return -1;
        }

    const char * const filename = argv[1];
    std::string separator(" ");
    std::vector<dbc_id_data> dbc_data;

    for(int n = 0; n < DBC_number; n++)
        {
            std::string filename(DBC[n].file_name);
            if(parse_dbc_file(filename, dbc_data, separator,n))
                std::cout << "Success reading: " << DBC[n].file_name << '\n';
        }

    GLOBAL::can_frame_counter = 0;
    exit_codes result = go_through_blf_file(filename);

    if(result != exit_codes::EXITING_SUCCESS)
        {
            std::cout << print(result) << '\n';
            std::cout << "Exiting\n";
            return(EXIT_FAILURE);
        }

    print_frameid_dbcdata(std::cout, GLOBAL::id_data, dbc_data);
    std::cout << "Number of dbc frames: " << dbc_data.size() << '\n';

    std::cout << "Number of different frames: " << GLOBAL::id_data.size() <<
              " total number of frames in blf:" << GLOBAL::can_frame_counter  << '\n';
    return EXIT_SUCCESS;
}
