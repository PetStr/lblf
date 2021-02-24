#include <iostream>
#include <fstream>
#include <array>
#include <iomanip>
#include <vector>
#include <cstring>

#include <zlib.h>

//hexdump -v -C -n 512 truck02.blf

#include "blf_structs.hh"

#include "print.hh"

const uint32_t FileSignature = 0x47474F4C;   //LOGG
const uint32_t ObjectSignature = 0x4A424F4C; //LOBJ

//Forward declaration.
exit_codes handle_ObjectType(std::iostream &fs, const ObjectHeaderBase &ohb);


uint32_t fileLength(std::iostream &is)
{
    is.seekg(0, is.end);
    uint32_t length = is.tellg();
    is.seekg(0, is.beg);
    return length;
}


template <typename type_data>
bool read_template(std::iostream &fs, type_data &data)
{
    fs.read(reinterpret_cast<char *>(&data), sizeof(type_data));
    return true;
}


bool read(std::iostream &fs, fileStatistics &os)
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


bool read(std::iostream & fs, uint32_t length, std::vector<uint8_t> & data)
{
    for(uint32_t n = 0; n<length; n++)
        {
            uint8_t value;
            fs.read((char *) &value, 1);
            data.push_back(value);
        }
    return true;
}


bool read(std::iostream & fs, uint32_t length, std::string & data)
{
    data.resize(length);
    fs.read(const_cast<char *>(data.data()), length);
    return true;
}


bool read(std::iostream &fs, ObjectHeaderBase &ohb)
{
    fs.read(reinterpret_cast<char *>(&ohb.ObjSign), sizeof(ohb.ObjSign));
    if (ohb.ObjSign != ObjectSignature)
        {
            std::cout << __LINE__ << ": Not Found LOBJ: " << std::hex << (int) ohb.ObjSign;
            std::cout << '\n';
            return false;
        }
    fs.read(reinterpret_cast<char *>(&ohb.headerSize), sizeof(ohb.headerSize));
    fs.read(reinterpret_cast<char *>(&ohb.headerVer), sizeof(ohb.headerVer));
    fs.read(reinterpret_cast<char *>(&ohb.objSize), sizeof(ohb.objSize));
    fs.read(reinterpret_cast<char *>(&ohb.objectType), sizeof(ohb.objectType));
    return true;
}


bool read_headers(std::iostream &fs, ObjectHeaderCarry &ohc)
{
    fs.read(reinterpret_cast<char *>(&ohc.ohb.ObjSign), sizeof(ohc.ohb.ObjSign));
    if (ohc.ohb.ObjSign != ObjectSignature)
        {
            std::cout << __LINE__ << ": Not Found LOBJ: " << std::hex << (int) ohc.ohb.ObjSign;
            std::cout << '\n';
            return false;
        }
    fs.read(reinterpret_cast<char *>(&ohc.ohb.headerSize), sizeof(ohc.ohb.headerSize));
    fs.read(reinterpret_cast<char *>(&ohc.ohb.headerVer),  sizeof(ohc.ohb.headerVer));
    fs.read(reinterpret_cast<char *>(&ohc.ohb.objSize),    sizeof(ohc.ohb.objSize));
    fs.read(reinterpret_cast<char *>(&ohc.ohb.objectType), sizeof(ohc.ohb.objectType));

    switch (ohc.ohb.headerSize)
    {
        case 16 : 
            ohc.oh_enum = ObjectHeaders_e::ONLY_HEADER_BASE;
            break;
        case 32 :
                read_template(fs, ohc.oh);
                ohc.oh_enum = ObjectHeaders_e::BASE_AND_HEADER;
                break;
        case 40 :
                read_template(fs, ohc.oh2);
                ohc.oh_enum = ObjectHeaders_e::BASE_AND_HEADER2;
                break;
    }
    return true;    
}


bool read(std::iostream &input_stream, LogContainer &lc, const ObjectHeaderBase &ohb)
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


bool parse_container_compressed(std::iostream &fs, const LogContainer &lc, const ObjectHeaderBase &ohb)
{
    std::cout << "Entering: " << __FUNCTION__ << '\n';

    uLong bytes_left_in_container = lc.unCompressedFileSize;
    std::vector<uint8_t> compressedData {};
    std::vector<uint8_t> uncompressedData {};
    auto compressedDataSize = ohb.objSize - ohb.headerSize - sizeof(LogContainer);
    compressedData.resize(compressedDataSize);

    std::cout << __LINE__ << " Bytes be4 read: " << fs.tellg() << std::hex << ", 0x" << fs.tellg() << '\n';
    fs.read(reinterpret_cast<char *>(compressedData.data()), compressedDataSize);


    std::cout << __LINE__ << " Bytes after : " << std::dec << fs.tellg() << std::hex << ", 0x" << fs.tellg() << '\n';

    uncompressedData.resize(bytes_left_in_container);
    int retVal = ::uncompress(
                     reinterpret_cast<Byte *>(uncompressedData.data()),
                     &bytes_left_in_container,
                     reinterpret_cast<Byte *>(compressedData.data()),
                     static_cast<uLong>(compressedDataSize));

    std::cout << __FUNCTION__ << " retVal; " << std::dec << retVal << '\n';

//Transfer data to stream;
    std::stringstream uncompressedStream;
    for (const auto & data : uncompressedData)
        {
            uncompressedStream.write(reinterpret_cast<const char*>(&data), sizeof(uint8_t));
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
            struct ObjectHeaderBase ohb;
            if (read(uncompressedStream, ohb))
                {
                    print(std::cout, ohb);
                }
            else
                break;

            handle_ObjectType(uncompressedStream, ohb);
            bytes_left_in_container = bytes_left_in_container - ohb.objSize;

            std::cout << "Compressed LogContainer/ bytes left: " << std::dec << bytes_left_in_container << '\n';

            if((bytes_left_in_container <= 0)  || (uncompressedStream.eof() ) )
                run = false;
        }
    return true;
}


bool parse_container_uncompressed(std::iostream &fs, const LogContainer &lc)
{
    int32_t bytes_left_in_container = lc.unCompressedFileSize;
    bool run = true;
    while(run)
        {
            struct ObjectHeaderCarry ohc;
            if (read(fs, ohc.ohb))
                {
                    print(std::cout, ohc.ohb);
                }
            else
                return false;

            handle_ObjectType(fs, ohc);
            bytes_left_in_container = bytes_left_in_container - ohb.objSize;
            std::cout << "LogContainer/ bytes left: " << std::dec << bytes_left_in_container << '\n';
            if(bytes_left_in_container <= 0)
                run = false;
        }
    return true;
}


bool read_head(std::iostream &fs)
{
    struct ObjectHeaderBase ohb;
    if (read(fs, ohb))
        print(std::cout, ohb);
    else
        {
            std::cout << "Error reading ObjectHeaderBase\n";
            return false;
        }

    auto bytes_to_jump = 0;
    if(ohb.headerSize == 16)
        bytes_to_jump = ohb.objSize - ohb.headerSize;

    if(ohb.headerSize == 32)
        bytes_to_jump = ohb.objSize - ohb.headerSize + 16;

    fs.seekg(bytes_to_jump,std::ios_base::cur);
    std::cout << print(ohb.objectType) << " " << static_cast<int> (ohb.objectType) << " " << std::dec << (int) bytes_to_jump << '\n';
    return true;
}


bool parse_logcontainer_base(std::fstream &fs, const LogContainer &lc)
{
    uint32_t bytes_left_in_container = lc.unCompressedFileSize;
    bool run = true;
    while(run)
        {
            struct ObjectHeaderBase ohb;
            if (read (fs, ohb))
                {
                    //   print(std::cout, ohb);
                }
            else
                {
                    std::cout << "Error reading ObjectHeaderBase\n";
                    return false;
                }

            auto bytes_to_jump = 0;
            if(ohb.headerSize == 16)
                bytes_to_jump = ohb.objSize - ohb.headerSize;

            if(ohb.headerSize == 32)
                bytes_to_jump = ohb.objSize - ohb.headerSize + 16;

            fs.seekg(bytes_to_jump,std::ios_base::cur);
            //std::cout << "Bytes_to_jump: " << bytes_to_jump << " current position " << std::hex << fs.tellg() << '\n';
            std::cout << print(ohb.objectType) << "(" << static_cast<int> (ohb.objectType) << ") " << std::dec << (int) bytes_to_jump << '\n';

            bytes_left_in_container = bytes_left_in_container - ohb.objSize;
            //std::cout << "bytes left: " << std::dec << bytes_left_in_container << '\n';
            if(bytes_left_in_container <= 0)
                run = false;
        }
    return true;
}


void go_through_file_header_base(const char * const filename)
{
    std::cout << "Opening file: " << filename;
    std::fstream fs(filename, std::fstream::in | std::fstream::binary);
    if (fs.fail())
        {
            std::cout << " ";
            std::cout << "File open failed, Exiting program\n";
            return;
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
                    return;
                }
        }

    while (!fs.eof())
        {
            if((filelength - fs.tellg() == 0))
                break;
            std::cout << "Bytes left: " << filelength - fs.tellg() << '\n';
            struct ObjectHeaderBase ohb;
            if (read(fs, ohb))
                {
                    std::cout << print(ohb.objectType) << " " << static_cast<int> (ohb.objectType) << '\n';
                }

            else
                {
                    std::cout << __LINE__ << " Unable to read ObjectHeaderBase\n";
                    break;
                }

            if(ohb.objectType == ObjectType_e::LOG_CONTAINER)
                {
                    struct LogContainer lc;
                    read(fs,lc,ohb);
                    parse_logcontainer_base(fs, lc);
                }
            else
                read_head(fs);
        }
    fs.close();
}


exit_codes handle_ObjectType(std::iostream &fs, const ObjectHeaderCarry &ohc)
{
    const auto payload_size = ohc.ohb.objSize-ohc.ohb.headerSize;
    switch (ohc.ohb.objectType)
        {
        case (ObjectType_e::CAN_MESSAGE): //read Can message;
        {
            struct ObjectHeader oh;
            (read_template(fs, oh));
            //	  print(std::cout, oh);
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
            struct ObjectHeader oh;
            read_template(fs, oh);
            print(std::cout, oh);
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
            print(std::cout, ohb);
            struct ObjectHeader oh;
            read_template(fs, oh);
            print(std::cout, oh);
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
            struct ObjectHeader oh;
            read_template(fs, oh);
            //print(std::cout, oh);
            struct AppTrigger ap;
            read_template(fs, ap);
            print(std::cout, ap);
        }
        break;

        case (ObjectType_e::LOG_CONTAINER): //Get Logcontainer
        {
            struct LogContainer lc;
            if (read(fs, lc, ohb))
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
                    if(parse_container_compressed(fs, lc, ohb))
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
            struct ObjectHeader oh;
            (read_template(fs, oh));
            //	  print(std::cout, oh);
            struct CanMessage2 cm2;
            if (read_template(fs, cm2))
                print(std::cout, cm2);
        }
        break;

        case (ObjectType_e::APP_TEXT):
        {
            struct ObjectHeader oh;
            read_template(fs, oh);
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
            struct ObjectHeader oh;
            read_template(fs, oh);
            struct reserved_5 r5;
            read_template(fs,r5);
            print(std::cout, r5);
        }
        break;


        default:
            std::cout << "New ObjectType: " << (int)ohb.objectType << '\n';
            return exit_codes::UNHANDLED_OBJECT_TYPE;
        }
    return exit_codes::EXITING_SUCCESS;
}


exit_codes go_through_file(const char * const filename)
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
            if((filelength - fs.tellg() == 0))
                break;
            std::cout << __LINE__ << ": Bytes left: " << filelength - fs.tellg() << '\n';
            std::cout << __LINE__ << ": Bytes now: " << fs.tellg() << std::hex << ", 0x" << fs.tellg() << '\n';

            auto offset = fs.tellg() % 4;

            std::cout << __LINE__  << ": Offset to move: " << offset << '\n';

            fs.seekg(offset, std::ios_base::cur);

            std::cout << __LINE__  << ": Aftermove: " << fs.tellg() << std::hex << ", 0x" << fs.tellg() << '\n';

            if(fs.eof())
            {
                std::cout << __LINE__ << " End of file reached\n";
                break;
            }
            struct ObjectHeaderBase ohb;
            if (read(fs, ohb))
                print(std::cout, ohb);
            else
                {
                    std::cout << __LINE__ << " Unable to read ObjectHeaderBase\n";
                    fs.close();
                    return exit_codes::UNABLE_TO_READ_OBJECT_HEADER_BASE;
                }

            handle_ObjectType(fs, ohb);
        }
    fs.close();
    return exit_codes::EXITING_SUCCESS;
}


int main(int argc, char* argv[])
{
    /*
        std::cout << "LogContainer    : " << std::dec << sizeof(LogContainer      ) << '\n';
        std::cout << "CanMessage      : " << std::dec << sizeof(CanMessage        ) << '\n';
        std::cout << "CanMessage2     : " << std::dec << sizeof(CanMessage2       ) << '\n';
        std::cout << "AppTrigger      : " << std::dec << sizeof(AppTrigger        ) << '\n';
        std::cout << "ObjectHeader      : " << std::dec << sizeof(ObjectHeader    ) << '\n';
        std::cout << "ObjectHeader2      : " << std::dec << sizeof(ObjectHeader2  ) << '\n';
        std::cout << "ObjectHeaderBase  : " << std::dec << sizeof(ObjectHeaderBase) << '\n';
      */


    std::cout << "----- START OF OUTPUT -----------------------------\n";

    if(argc > 1)
        {
            go_through_file( argv[1] );
            //go_through_file_header_base ( argv[1] );
        }
    else
        {
            std::cout << "run blf evaluation: " << argv[0] << " filname.blf\n";
        }

    std::cout << "----- END OF OUTPUT -----------------------------\n";

}
