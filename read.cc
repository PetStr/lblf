
#include <iostream>
#include <fstream>
#include <array>
#include <iomanip>
#include <vector>
#include <cstring>
#include <sstream>

#include <zlib.h>

//hexdump -v -C -n 512 truck02.blf

#include "blf_structs.hh"
#include "print.hh"

using namespace lblf;

const uint32_t FileSignature = 0x47474F4C;   //LOGG
const uint32_t ObjectSignature = 0x4A424F4C; //LOBJ

//Forward declaration.
template <typename stream_type> 
exit_codes handle_ObjectType(stream_type &fs, const ObjectHeaderCarry &ohc);


uint32_t fileLength(std::iostream &is)
{
    is.seekg(0, is.end);
    uint32_t length = is.tellg();
    is.seekg(0, is.beg);
    return length;
}


template <typename type_data, typename stream_type>
bool read_template(stream_type &fs, type_data &data)
{
    //fs.read(reinterpret_cast<char *>(&data), sizeof(type_data));
 //   fs >> data;
    return true;
}


template <typename stream_type>
std::istream& operator>> (stream_type& is, AppId_e& aid)
{
    uint8_t temp;
    is >> temp;
    aid = static_cast<AppId_e> (temp);
    return is;
}


/**
* @brief support operator for getting data.  
*
*/
template <typename stream_type>
stream_type& operator>> (stream_type& is, sysTime_t& st)
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


bool readX(std::iostream &fs, fileStatistics &os)
{
    fs >> os.FileSign;
    if (os.FileSign != FileSignature)
        {
            return false;
        }

    fs >> os.StatSize;
    fs >> os.AppId;
    fs >> os.AppMaj;
    fs >> os.AppMin;
    fs >> os.AppBuild;
    fs >> os.ApiMaj;
    fs >> os.ApiMin;
    fs >> os.ApiBuild;
    fs >> os.ApiPatch;
    fs >> os.fileSize;
    fs >> os.uncompressedSize;
    fs >> os.objCount;
    fs >> os.objRead;
    fs >> os.meas_start_time;
    fs >> os.last_obj_time;
    fs >> os.fileSize_less115;
    auto offset = os.StatSize - sizeof(fileStatistics);
    fs.seekg(offset, std::ios_base::cur);
    return true;
}


template <typename stream_type>
bool read(stream_type &fs, fileStatistics &os)
{
    std::cout << __LINE__ << ": file pointer: " << fs.tellg()<< '\n';
    fs >> os.FileSign;
    std::cout << __LINE__ << ": file pointer: " << fs.tellg()<< '\n';
    if (os.FileSign != FileSignature)
        {
            return false;
        }
    fs >> os.StatSize; 
    fs >> os.AppId; 
    fs >> os.AppMaj; 
    fs >> os.AppMin; 
    fs >> os.AppBuild; 
    fs >> os.ApiMaj; 
    fs >> os.ApiMin; 
    fs >> os.ApiBuild; 
    fs >> os.ApiPatch; 
    fs >> os.fileSize; 
    fs >> os.uncompressedSize; 
    fs >> os.objCount; 
    fs >> os.objRead; 
    fs >> os.meas_start_time; 
    fs >> os.last_obj_time; 
    fs >> os.fileSize_less115; 
    auto offset = os.StatSize - sizeof(fileStatistics);
    fs.seekg(offset, std::ios_base::cur);
    return true;
}


template <typename stream_type>
bool read(stream_type & fs, uint32_t length, std::vector<uint8_t> & data)
{
    for(uint32_t n = 0; n<length; n++)
        {
            uint8_t value;
            fs.read((char *) &value, 1);
            data.push_back(value);
        }
    return true;
}


template <typename stream_type>
bool read(stream_type & fs, uint32_t length, std::string & data)
{
    data.resize(length);
    fs.read(const_cast<char *>(data.data()), length);
    return true;
}


template <typename stream_type>
bool read_headers(stream_type /* std::basic_stringstream<uint8_t>*/  &fs, ObjectHeaderCarry &ohc)
{
    fs >> ohc.ohb.ObjSign;

    if (ohc.ohb.ObjSign != ObjectSignature)
        {
            std::cout << std::dec << __LINE__ << ": Not Found LOBJ: " << std::hex << (int) ohc.ohb.ObjSign;
            std::cout << '\n';
            return false;
        }
    
    fs >> ohc.ohb.headerSize;
    fs >> ohc.ohb.headerVer;
    fs >> ohc.ohb.objSize;

    uint32_t ot;
    fs >> ot;
    ohc.ohb.objectType = static_cast<ObjectType_e> (ot);


    switch (ohc.ohb.headerSize)
        {
        case 16 :
            ohc.oh_enum = ObjectHeaders_e::ONLY_HEADER_BASE;
            break;
        case 32 :
            {     
            uint32_t oF;
            fs >> oF;
            ohc.oh.objectFlag = static_cast<ObjectFlags_e> (oF);
            fs >> ohc.oh.clientIndex;
            fs >> ohc.oh.objectVersion;
            fs >> ohc.oh.objectTimeStamp;
            ohc.oh_enum = ObjectHeaders_e::BASE_AND_HEADER;
            }
            break;
        case 40 :
            {
            uint32_t oF;
            fs >> oF;
            ohc.oh2.objectFlags = static_cast<ObjectFlags_e> (oF);
            uint8_t tss;
            fs >> tss;
            ohc.oh2.timeStampStatus = static_cast<timeStampStatus_e> (tss);
            fs >> ohc.oh2.reservObjHeader;
            fs >> ohc.oh2.ObjectHeaderVersion;
            fs >> ohc.oh2.ObjectTimeStamp;
            fs >> ohc.oh2.originalObjectTimeStamp;
            ohc.oh_enum = ObjectHeaders_e::BASE_AND_HEADER2;
            }
            break;
        }
    return true;
}


template <typename stream_type_data>
auto read_logcontainer(stream_type_data &input_stream, const BaseHeader &ohb) -> LogContainer
{
    struct LogContainer lc;
    int16_t temp;
    input_stream >> temp;

    lc.compressionMethod = static_cast<compressionMethod_e> (temp);
    input_stream >> lc.reserv1;
    input_stream >> lc.reserv2;
    input_stream >> lc.unCompressedFileSize;
    input_stream >> lc.reserv3;

    if (lc.compressionMethod == compressionMethod_e::uncompressed)
        {
            lc.unCompressedFileSize = ohb.objSize - sizeof(lc.compressionMethod) - 
                sizeof(lc.reserv1) - sizeof(lc.reserv2) - sizeof(lc.unCompressedFileSize) - 
                sizeof(lc.reserv3);
        }
    return lc;
}


bool read(std::iostream &input_stream, LogContainer &lc, const BaseHeader &ohb)
{
    input_stream.read(reinterpret_cast<char *>(&lc), sizeof(LogContainer));

    if (lc.compressionMethod == compressionMethod_e::uncompressed)
        {
            lc.unCompressedFileSize = ohb.objSize - sizeof(lc.compressionMethod) - sizeof(lc.reserv1) - sizeof(lc.reserv2) - sizeof(lc.unCompressedFileSize) - sizeof(lc.reserv3);
        }

    return true;
}


void current_position(std::ostream &s, const uint64_t pos)
{
    s << "Current position: "
      << "0x" << std::hex << (uint64_t)pos << ", " << std::dec << (uint64_t)pos << '\n';
}


template <typename stream_type>
bool parse_container_compressed(stream_type &fs, const LogContainer &lc, const BaseHeader &ohb)
{
    std::cout << "Entering: " << __FUNCTION__ << '\n';

    uLong bytes_left_in_container = lc.unCompressedFileSize;
    std::vector<uint8_t> compressedData {};
    std::vector<uint8_t> uncompressedData {};
    auto compressedDataSize = ohb.objSize - ohb.headerSize - sizeof(LogContainer);
    compressedData.resize(compressedDataSize);

    std::cout << std::dec << __LINE__ << " Bytes be4 read: " << fs.tellg() << std::hex << ", 0x" << fs.tellg() << '\n';
    fs.read(reinterpret_cast<char *>(compressedData.data()), compressedDataSize);


    std::cout << std::dec <<__LINE__ << " Bytes after : " << std::dec << fs.tellg() << std::hex << ", 0x" << fs.tellg() << '\n';

    uncompressedData.resize(bytes_left_in_container);
    int retVal = ::uncompress(
                     reinterpret_cast<Byte *>(uncompressedData.data()),
                     &bytes_left_in_container,
                     reinterpret_cast<Byte *>(compressedData.data()),
                     static_cast<uLong>(compressedDataSize));

    std::cout << __FUNCTION__ << "uncompress: retVal: " << std::dec << retVal << '\n';

//Transfer data to stream;
    std::basic_stringstream<uint8_t> uncompressedStream;
    //std::stringstream                       uncompressedStream;
    for (uint8_t data : uncompressedData)
        {
            //uncompressedStream.write(reinterpret_cast<uint8_t*>(&data), sizeof(uint8_t));
            uncompressedStream.write(&data, sizeof(uint8_t));
        }

    std::cout << "Printing uncompressedData, size: " << uncompressedData.size() << "\n";
    size_t cnt = 0;
    for(auto a: uncompressedData)
        {
            std::cout << " " << std::hex << std::setfill('0') << std::setw(2) << (int) a;
            cnt++;
            if((cnt % 48) == 0)
                std::cout << '\n';
        }
    std::cout << '\n';

    uncompressedData.clear();
    compressedData.clear();

    bool run = true;
    while(run)
        {
            struct ObjectHeaderCarry ohc;
            if (read_headers<std::basic_stringstream<uint8_t>>(uncompressedStream, ohc))
                {
                    print(std::cout, ohc.ohb);
                }
            else
                break;

            handle_ObjectType(uncompressedStream, ohc);
            bytes_left_in_container = bytes_left_in_container - ohc.ohb.objSize;

            std::cout << std::dec << __LINE__ << ": Compressed LogContainer/ bytes left: " << std::dec << bytes_left_in_container << '\n';

            if((bytes_left_in_container <= 0)  || (uncompressedStream.eof() ) )
                run = false;
        }
    return true;
}


template <typename type_stream_data> 
bool parse_container_uncompressed(type_stream_data &fs, const LogContainer &lc)
{
    int32_t bytes_left_in_container = lc.unCompressedFileSize;
    bool run = true;
    while(run)
        {

            std::cout << std::dec << __LINE__ << ": " << std::hex << fs.tellg() << '\n';
            struct ObjectHeaderCarry ohc;
            if (read_headers<type_stream_data>(fs, ohc))
                {
                    print(std::cout, ohc.ohb);
                }
            else
                return false;
            std::cout << std::dec << __LINE__ << ": " << std::hex << fs.tellg() << '\n';
            handle_ObjectType(fs, ohc);
            std::cout << std::dec << __LINE__ << ": " << std::hex << fs.tellg() << '\n';

            auto offset = fs.tellg() % 4;
            std::cout << std::dec << __LINE__ << ": offset: " << std::hex << offset << '\n';
            //fs.seekg(offset, std::ios_base::cur);

            bytes_left_in_container = bytes_left_in_container - ohc.ohb.objSize; //- offset;
            std::cout << std::dec << __LINE__ << ": LogContainer/ bytes left: " << std::dec << bytes_left_in_container << '\n';
            if(bytes_left_in_container <= 0)
                run = false;
        }
    return true;
}


template <typename stream_type> 
auto handle_ObjectType(stream_type  &fs, const ObjectHeaderCarry &ohc) -> exit_codes
{
    const auto payload_size = ohc.ohb.objSize-ohc.ohb.headerSize;
    std::cout << std::dec << __LINE__ << ": payload: " << payload_size << '\n';
    switch (ohc.ohb.objectType)
        {
        case (ObjectType_e::CAN_MESSAGE): //read Can message;
        {
            if(payload_size == sizeof(CanMessage))
                {
                    struct CanMessage cm;
                    if (read_template(fs, cm))
                        print(std::cout, cm);
                }
            else
                {
                    return exit_codes::CAN_MESSAGE_INVALID_LENGTH;
                }
        }
        break;

        case (ObjectType_e::CAN_ERROR): //CanErrorFrame
        {
            switch(payload_size)
                {
                case sizeof(CanError_short) :
                {
                    struct CanError_short cef;
                    read_template(fs,cef);
                    print(std::cout, cef);
                    break;
                }
                case sizeof(CanError) :
                {
                    struct CanError cef;
                    read_template(fs, cef);
                    print(std::cout, cef);
                    break;
                }
                }
        }
        break;

        case (ObjectType_e::CAN_OVERLOAD): //CanOverload
        {
            switch(payload_size)
                {
                case sizeof(CanOverload) :
                    struct CanOverload col;
                    read_template(fs, col);
                    print(std::cout, col);
                    break;
                case sizeof(CanOverload_short) :
                    struct CanOverload_short cols;
                    read_template(fs, cols);
                    print(std::cout, cols);
                    break;
                default:
                    std::cout << "Error wrong CanOverload Frame!\n";
                }
        }
        break;

        case (ObjectType_e::APP_TRIGGER): //Handle apptrigger
        {
            struct AppTrigger ap;
            read_template(fs, ap);
            print(std::cout, ap);
        }
        break;

        case (ObjectType_e::LOG_CONTAINER): //Get Logcontainer
        {
            auto lc = read_logcontainer(fs, ohc.ohb);
            print(std::cout, lc);

            if(lc.compressionMethod == compressionMethod_e::uncompressed)
                {
                    //Lets work through the logcontainer.
                    if(parse_container_uncompressed(fs, lc))
                        {
                            std::cout << "LogContainer handled.\n";
                        }
                    else
                        {
                            std::cout << "LogContainer walk through failed.\n";
                            return exit_codes::LOGCONTAINER_WALK_THROUGH_FAIL;
                        }
                }
            if(lc.compressionMethod == compressionMethod_e::zlib)
                {
                    if(parse_container_compressed(fs, lc, ohc.ohb))
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

        case (ObjectType_e::CAN_MESSAGE2):
        {
            struct CanMessage2 cm2;
            if (read_template(fs, cm2))
                print(std::cout, cm2);
        }
        break;

        case (ObjectType_e::CAN_ERROR_EXT):
        {
            struct CANErrorFrameExt cefe;
            if (read_template(fs, cefe))
                {
                    print(std::cout, cefe);
                }
        }
        break;



        case (ObjectType_e::APP_TEXT):
        {
            struct AppText ap;
            read_template(fs,ap);
            print(std::cout,ap);
            //std::vector<uint8_t> data;
            std::string data;
            read(fs, ap.mTextLength, data);
            //std::cout << "Length: " << data.size() << '\n';
            //for (auto i : data)
            //    std::cout << static_cast<int> (i) << ' ';
            std::cout << "Sträng: " << data << '\n';
        }
        break;

        case (ObjectType_e::reserved_5):
        {
            std::cout << "sizeof (reserved5) " << sizeof(reserved_5) << '\n';
            struct reserved_5 r5;
            read_template(fs,r5);
            print(std::cout, r5);
        }
        break;

        default:
            std::cout << "New ObjectType: " << (int)ohc.ohb.objectType << '\n';
            fs.seekg(payload_size, std::ios_base::cur);
            return exit_codes::UNHANDLED_OBJECT_TYPE;
        }
    return exit_codes::EXITING_SUCCESS;
}


auto go_through_file(const char * const filename) -> exit_codes
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
                    print(std::cout, fileStat);
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
            if((filelength - fs.tellg() <= 16))
                break;
            std::cout << std::dec << __LINE__ << ": Bytes left: " << filelength - fs.tellg() << '\n';
            std::cout << std::dec << __LINE__ << ": Bytes now: " << fs.tellg() << std::hex << ", 0x" << fs.tellg() << '\n';

            auto offset = fs.tellg() % 4;

            std::cout << std::dec  << __LINE__  << ": Offset to move: " << offset << '\n';

            fs.seekg(offset, std::ios_base::cur);

            std::cout << std::dec << __LINE__  << ": Aftermove: " << fs.tellg() << std::hex << ", 0x" << fs.tellg() << '\n';

            if(fs.eof())
                {
                    std::cout << __LINE__ << " End of file reached\n";
                    break;
                }
            struct ObjectHeaderCarry ohc;
            if (read_headers<std::fstream>(fs, ohc))
                print(std::cout, ohc);
            else
                {
                    std::cout << __LINE__ << " Unable to read BaseHeader\n";
                    fs.close();
                    return exit_codes::UNABLE_TO_READ_OBJECT_HEADER_BASE;
                }

            handle_ObjectType<std::fstream>(fs, ohc);
        }
    fs.close();
    return exit_codes::EXITING_SUCCESS;
}


int main(int argc, char* argv[])
{

    std::cout << "----- START OF OUTPUT -----\n";

    if(argc > 1)
        {
            go_through_file( argv[1] );
        }
    else
        {
            std::cout << "run blf evaluation: " << argv[0] << " filname.blf\n";
        }

    std::cout << "----- END OF OUTPUT -----\n";

}
