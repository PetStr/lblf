#include <array>
#include <cstring>
#include <fstream>
#include <iomanip>

#include <vector>


#include <zlib.h>

// hexdump -v -C -n 512 truck02.blf

#include "blf_structs.hh"
#include "print.hh"

using namespace lblf;

const uint32_t FileSignature = 0x47474F4C;   // LOGG
const uint32_t ObjectSignature = 0x4A424F4C; // LOBJ

// Forward declaration.
exit_codes handle_ObjectType(std::fstream &fs, const BaseHeader &ohb);


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


bool read(std::fstream &fs, uint32_t length, std::vector<uint8_t> &data)
{
    for (uint32_t n = 0; n < length; n++)
        {
            uint8_t value = 0;
            fs.read(reinterpret_cast<char *>(&value), 1);
            data.push_back(value);
        }
    return true;
}


bool read(std::fstream &fs, uint32_t length, std::string &data)
{
    data.resize(length);
    fs.read(const_cast<char *>(data.data()), length);
    return true;
}


bool read(std::fstream &fs, BaseHeader &ohb)
{
    fs.read(reinterpret_cast<char *>(&ohb.ObjSign), sizeof(ohb.ObjSign));
    if (ohb.ObjSign != ObjectSignature)
        {
            std::cout << "Not Found LOBJ: " << std::hex << (int) ohb.ObjSign;
            std::cout << '\n';
            return false;
        }
    fs.read(reinterpret_cast<char *>(&ohb.headerSize), sizeof(ohb.headerSize));
    fs.read(reinterpret_cast<char *>(&ohb.headerVer), sizeof(ohb.headerVer));
    fs.read(reinterpret_cast<char *>(&ohb.objSize), sizeof(ohb.objSize));
    fs.read(reinterpret_cast<char *>(&ohb.objectType), sizeof(ohb.objectType));
    return true;
}


bool read(uint8_t *data, BaseHeader &ohb)
{
    std::memcpy(&ohb.ObjSign, data, sizeof(ohb.ObjSign));
    if (ohb.ObjSign != ObjectSignature)
        {
            std::cout << "Not Found LOBJ: " << std::hex << (int) ohb.ObjSign;
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


template <typename type_data>
size_t read_template(const uint8_t *indata_array, type_data &data)
{
    std::memcpy(reinterpret_cast<char *>(&data), indata_array, sizeof(type_data));
    return sizeof(type_data);
}


void current_position(std::ostream &s, const uint64_t pos)
{
    s << "Current position: "
      << "0x" << std::hex << (uint64_t) pos << ", " << std::dec << (uint64_t) pos << '\n';
}


bool parse_container_compressed(std::istream &fs, const LogContainer &lc, const BaseHeader &ohb)
{
    std::cout << "Bytes be4 read: " << fs.tellg() << std::hex << ", 0x" << fs.tellg() << '\n';
    std::cout << "Entering: " << __FUNCTION__ << '\n';
    uLong bytes_left_in_container = lc.unCompressedFileSize;
    std::vector<uint8_t> compressedFile {};
    std::vector<uint8_t> uncompressedFile {};
    auto compressedFileSize = ohb.objSize - ohb.headerSize - sizeof(LogContainer);
    compressedFile.resize(compressedFileSize);

    std::cout << "Bytes be4 read: " << fs.tellg() << std::hex << ", 0x" << fs.tellg() << '\n';
    fs.read(reinterpret_cast<char *>(compressedFile.data()), compressedFileSize);


    std::cout << "Bytes after : " << std::dec << fs.tellg() << std::hex << ", 0x" << fs.tellg() << '\n';

    uncompressedFile.resize(bytes_left_in_container);
    int retVal = uncompress(
        reinterpret_cast<Byte *>(uncompressedFile.data()),
        &bytes_left_in_container,
        reinterpret_cast<Byte *>(compressedFile.data()),
        static_cast<uLong>(compressedFileSize));


    std::cout << __FUNCTION__ << " retVal; " << std::dec << retVal << '\n';


    size_t cnt = 0;
    for (auto a: uncompressedFile)
        {
            std::cout << " " << std::hex << std::setfill('0') << std::setw(2) << (int) a;
            cnt++;
            if ((cnt % 48) == 0)
                std::cout << '\n';
        }
    std::cout << '\n';


    uint8_t *uncompresseddata = uncompressedFile.data();
    bool run = true;
    while (run)
        {
            struct BaseHeader ohb;
            if (read(uncompresseddata, ohb))
                {
                    print(std::cout, ohb);
                }
            else
                break;

            // Move pointer to next step
            uncompresseddata += sizeof(ohb);
            bytes_left_in_container -= sizeof(ohb);
            if (bytes_left_in_container <= 0)
                return true;

            struct ObjectHeader oh;
            auto bytes_read = read_template(uncompresseddata, oh);
            uncompresseddata += bytes_read;
            bytes_left_in_container -= bytes_read;
            // print(std::cout, oh);
            if (bytes_left_in_container <= 0)
                return true;


            struct CanMessage cm;
            bytes_read = read_template(uncompresseddata, cm);
            uncompresseddata += bytes_read;
            bytes_left_in_container -= bytes_read;
            print(std::cout, cm);

            std::cout << "LogContainer/ bytes left: " << std::dec << bytes_left_in_container << '\n';

            if (bytes_left_in_container <= 0)
                run = false;
        }
    return true;
}


auto handle_container_compressed(std::vector<uint8_t> &compressedFile, LogContainer &lc, const BaseHeader &ohb) -> bool
{

    uLong bytes_left_in_container = lc.unCompressedFileSize;
    // std::vector<uint8_t> compressedFile {};
    std::vector<uint8_t> uncompressedFile {};
    auto compressedFileSize = ohb.objSize - ohb.headerSize - sizeof(LogContainer);
    compressedFile.resize(compressedFileSize);

    uncompressedFile.resize(bytes_left_in_container);

    // std::cout << "compressed file size: " << compressedFile.size() << '\n';
    // std::cout << "uncompressed file size: " << bytes_left_in_container << '\n';


    if (0)
        {

            std::cout << "compressed file size: " << compressedFile.size() << '\n';
            size_t cnt = 0;
            for (auto a: compressedFile)
                {
                    std::cout << " " << std::hex << std::setfill('0') << std::setw(2) << (int) a;
                    cnt++;
                    if ((cnt % 48) == 0)
                        std::cout << '\n';
                }
            std::cout << '\n';
        }


    int retVal = uncompress(
        reinterpret_cast<Byte *>(uncompressedFile.data()),
        &bytes_left_in_container,
        reinterpret_cast<Byte *>(compressedFile.data()),
        static_cast<uLong>(compressedFileSize));


    std::cout << __FUNCTION__ << " retVal; " << std::dec << retVal << '\n';

    if (0)
        {
            size_t cnt = 0;
            for (auto a: uncompressedFile)
                {
                    std::cout << " " << std::hex << std::setfill('0') << std::setw(2) << (int) a;
                    cnt++;
                    if ((cnt % 48) == 0)
                        std::cout << '\n';
                }
            std::cout << '\n';
        }

    uint8_t *uncompresseddata = uncompressedFile.data();
    bool run = true;
    while (run)
        {
            struct BaseHeader ohb;
            if (read(uncompresseddata, ohb))
                {
                    print(std::cout, ohb);
                }
            else
                break;

            // Move pointer to next step
            uncompresseddata += sizeof(ohb);
            bytes_left_in_container -= sizeof(ohb);
            if (bytes_left_in_container <= 0)
                return true;

            struct ObjectHeader oh;
            auto bytes_read = read_template(uncompresseddata, oh);
            uncompresseddata += bytes_read;
            bytes_left_in_container -= bytes_read;
            // print(std::cout, oh);
            if (bytes_left_in_container <= 0)
                return true;


            std::cout << "LogContainer/ bytes left: " << std::dec << bytes_left_in_container << '\n';

            if (bytes_left_in_container <= 0)
                run = false;
        }
    return true;
}


bool parse_container_uncompressed(std::fstream &fs, const LogContainer &lc)
{
    int32_t bytes_left_in_container = lc.unCompressedFileSize;
    bool run = true;
    while (run)
        {
            struct BaseHeader ohb;
            if (read(fs, ohb))
                {
                    // print(std::cout, ohb);
                }
            else
                return false;

            handle_ObjectType(fs, ohb);
            bytes_left_in_container = bytes_left_in_container - ohb.objSize;
            std::cout << "LogContainer/ bytes left: " << std::dec << bytes_left_in_container << '\n';
            if (bytes_left_in_container <= 0)
                run = false;
        }
    return true;
}


bool read_head(std::fstream &fs)
{
    struct BaseHeader ohb;
    if (read(fs, ohb))
        print(std::cout, ohb);
    else
        {
            std::cout << "Error reading BaseHeader\n";
            return false;
        }

    auto bytes_to_jump = 0;
    if (ohb.headerSize == 16)
        bytes_to_jump = ohb.objSize - ohb.headerSize;

    if (ohb.headerSize == 32)
        bytes_to_jump = ohb.objSize - ohb.headerSize + 16;

    fs.seekg(bytes_to_jump, std::ios_base::cur);
    std::cout << print(ohb.objectType) << " " << static_cast<int>(ohb.objectType) << " " << std::dec << (int) bytes_to_jump << '\n';
    return true;
}


bool parse_logcontainer_base(std::fstream &fs, const LogContainer &lc)
{
    uint32_t bytes_left_in_container = lc.unCompressedFileSize;
    bool run = true;
    while (run)
        {

            struct BaseHeader ohb;
            if (read(fs, ohb))
                {
                    //   print(std::cout, ohb);
                }
            else
                {
                    std::cout << "Error reading BaseHeader\n";
                    return false;
                }

            auto bytes_to_jump = 0;
            if (ohb.headerSize == 16)
                bytes_to_jump = ohb.objSize - ohb.headerSize;

            if (ohb.headerSize == 32)
                bytes_to_jump = ohb.objSize - ohb.headerSize + 16;

            fs.seekg(bytes_to_jump, std::ios_base::cur);
            // std::cout << "Bytes_to_jump: " << bytes_to_jump << " current position " << std::hex << fs.tellg() << '\n';
            std::cout << print(ohb.objectType) << "(" << static_cast<int>(ohb.objectType) << ") " << std::dec << (int) bytes_to_jump << '\n';

            bytes_left_in_container = bytes_left_in_container - ohb.objSize;
            // std::cout << "bytes left: " << std::dec << bytes_left_in_container << '\n';
            if (bytes_left_in_container <= 0)
                run = false;
        }
    return true;
}


auto handle_ObjectType(std::fstream &fs, const BaseHeader &ohb) -> exit_codes
{
    const auto payload_size = ohb.objSize - ohb.headerSize;
    switch (ohb.objectType)
        {
        case (ObjectType_e::CAN_MESSAGE): // read Can message;
            {
                struct ObjectHeader oh;
                (read_template(fs, oh));
                //	  print(std::cout, oh);
                if (payload_size == sizeof(CanMessage))
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

        case (ObjectType_e::CAN_ERROR): // CanErrorFrame
            {
                struct ObjectHeader oh;
                read_template(fs, oh);
                print(std::cout, oh);
                switch (payload_size)
                    {
                    case sizeof(CanError_short):
                        {
                            struct CanError_short cef;
                            read_template(fs, cef);
                            print(std::cout, cef);
                            break;
                        }
                    case sizeof(CanError):
                        {
                            struct CanError cef;
                            read_template(fs, cef);
                            print(std::cout, cef);
                            break;
                        }
                    }
            }
            break;

        case (ObjectType_e::CAN_OVERLOAD): // CanOverload
            {
                print(std::cout, ohb);
                struct ObjectHeader oh;
                read_template(fs, oh);
                print(std::cout, oh);
                switch (payload_size)
                    {
                    case sizeof(CanOverload):
                        struct CanOverload col;
                        read_template(fs, col);
                        print(std::cout, col);
                        break;
                    case sizeof(CanOverload_short):
                        struct CanOverload_short cols;
                        read_template(fs, cols);
                        print(std::cout, cols);
                        break;
                    default:
                        std::cout << "Error wrong CanOverload Frame!\n";
                    }
            }
            break;

        case (ObjectType_e::APP_TRIGGER): // Handle apptrigger
            {
                struct ObjectHeader oh;
                read_template(fs, oh);
                // print(std::cout, oh);
                struct AppTrigger ap;
                read_template(fs, ap);
                print(std::cout, ap);
            }
            break;

        case (ObjectType_e::LOG_CONTAINER): // Get Logcontainer
            {
                struct LogContainer lc;
                if (read(fs, lc, ohb))
                    print(std::cout, lc);

                if (lc.compressionMethod == compressionMethod_e::uncompressed)
                    {
                        // Lets work through the logcontainer.
                        if (parse_container_uncompressed(fs, lc))
                            {
                                std::cout << "LogContainer handled.\n";
                            }
                        else
                            {
                                std::cout << "LogContainer walk through failed.\n";
                                return exit_codes::LOGCONTAINER_WALK_THROUGH_FAIL;
                            }
                    }
                if (lc.compressionMethod == compressionMethod_e::zlib)
                    {
                        if (parse_container_compressed(fs, lc, ohb))
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
                read_template(fs, ap);
                print(std::cout, ap);
                // std::vector<uint8_t> data;
                std::string data;
                read(fs, ap.mTextLength, data);
                // std::cout << "Length: " << data.size() << '\n';
                // for (auto i : data)
                //     std::cout << static_cast<int> (i) << ' ';
                std::cout << "Sträng: " << data << '\n';
            }
            break;

        case (ObjectType_e::reserved_5):
            {
                std::cout << "sizeof (reserved5) " << sizeof(reserved_5) << '\n';
                struct ObjectHeader oh;
                read_template(fs, oh);
                struct reserved_5 r5;
                read_template(fs, r5);
                print(std::cout, r5);
            }
            break;


        default:
            std::cout << "New ObjectType: " << (int) ohb.objectType << '\n';
            return exit_codes::UNHANDLED_OBJECT_TYPE;
        }
    return exit_codes::EXITING_SUCCESS;
}


void go_through_file_header_base(const char *const filename)
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
            if ((filelength - fs.tellg() == 0))
                break;
            // std::cout << "Bytes left: " << filelength - fs.tellg() << '\n';

            struct BaseHeader ohb;
            if (read(fs, ohb))
                {
                    // std::cout << print(ohb.objectType) << " " << static_cast<int>(ohb.objectType) << '\n';
                    print(std::cout, ohb);
                    const size_t bytes_to_jump = ohb.objSize - ohb.headerSize + (ohb.objSize % 4);
                    // std::cout << "To jump: " << bytes_to_jump << '\n';
                    fs.seekg(bytes_to_jump, std::ios_base::cur);
                }

            else
                {
                    std::cout << std::dec << __LINE__ << " Unable to read BaseHeader\n";
                }
        }
    fs.close();
}


void go_through_file_log_container(const char *const filename)
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
            if ((filelength - fs.tellg() == 0))
                break;
            std::cout << "Bytes left: " << filelength - fs.tellg() << '\n';

            struct BaseHeader ohb;
            if (read(fs, ohb))
                {
                    // std::cout << print(ohb.objectType) << " " << static_cast<int>(ohb.objectType) << '\n';
                    print(std::cout, ohb);
                }

            else
                {
                    std::cout << std::dec << __LINE__ << " Unable to read BaseHeader\n";
                    //   fs.seekg(1,std::ios_base::cur);
                }

            if (ohb.objectType == ObjectType_e::LOG_CONTAINER)
                {
                    struct LogContainer lc;
                    read(fs, lc, ohb);
                    print(std::cout, lc);
                    std::vector<uint8_t> container_data;
                    auto compressedFileSize = ohb.objSize - ohb.headerSize - sizeof(LogContainer);

                    // std::cout << "compressed blob: " << compressedFileSize << '\n';

                    container_data.resize(compressedFileSize);

                    fs.read(reinterpret_cast<char *>(container_data.data()), compressedFileSize);

                    // Padding
                    fs.seekg(ohb.objSize % 4, std::ios_base::cur);

                    std::cout << "data size: " << container_data.size() << '\n';

                    handle_container_compressed(container_data, lc, ohb);
                }
            else
                {
                    const size_t bytes_to_jump = ohb.objSize - ohb.headerSize + (ohb.objSize % 4);
                    // std::cout << "To jump: " << bytes_to_jump << '\n';
                    fs.seekg(bytes_to_jump, std::ios_base::cur);
                }
        }
    fs.close();
}


int main(int argc, char *argv[])
{

    std::cout << "----- START OF OUTPUT -----------------------------\n";

    if (argc > 1)
        {
            // go_through_file( argv[1] );
            go_through_file_log_container(argv[1]);
        }
    else
        {
            std::cout << "run blf evaluation: " << argv[0] << " filname.blf\n";
        }

    std::cout << "----- END OF OUTPUT -----------------------------\n";
}
