#include "blf_structs.hh"
#include "print.hh"
#include <array>
#include <cstring>
#include <deque>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <type_traits>
#include <vector>
#include <zlib.h>

// hexdump -v -C -n 512 truck02.blf


using namespace lblf;

const uint32_t FileSignature = 0x47474F4C;   // LOGG
const uint32_t ObjectSignature = 0x4A424F4C; // LOBJ

const uint32_t defaultContainerSize = 0x20000;

// Forward declaration.
auto handle_ObjectType(std::deque<char> &log_que, const BaseHeader &obh) -> exit_codes;


struct lobj
{
    BaseHeader base_header;
    std::vector<char> payload {};
};


void print(const std::deque<char> &data, size_t counts_to_print)
{
    size_t cnt = 0;
    for (auto a: data)
        {
            std::cout << " " << std::hex << std::setfill('0') << std::setw(2) << (int) static_cast<uint8_t>(a);
            cnt++;
            if ((cnt % 16) == 0)
                {
                    std::cout << '\n';
                }
            if (cnt >= counts_to_print)
                {
                    break;
                }
        }
    std::cout << '\n';
}


auto fileLength(std::fstream &fs) -> uint32_t
{
    fs.seekg(0, std::fstream::end);
    uint32_t length = fs.tellg();
    fs.seekg(0, std::fstream::beg);
    return length;
}


auto read(std::fstream &fs, fileStatistics &os) -> bool
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
    const uint32_t offset = os.StatSize - sizeof(fileStatistics);
    fs.seekg(offset, std::ios_base::cur);
    return true;
}


auto read(std::fstream &fs, uint32_t length, std::vector<uint8_t> &data) -> bool
{
    for (uint32_t n = 0; n < length; n++)
        {
            uint8_t value = 0;
            fs.read(reinterpret_cast<char *>(&value), 1);
            data.push_back(value);
        }
    return true;
}


auto read(std::fstream &fs, uint32_t length, std::string &data) -> bool
{
    data.resize(length);
    fs.read(reinterpret_cast<char *>(data.data()), length);
    return true;
}


auto read(std::fstream &fs, BaseHeader &ohb) -> bool
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


auto read(uint8_t *data, BaseHeader &ohb) -> bool
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


template <typename param>
auto consume_que(std::deque<char> &que, param &output) -> bool
{
    if (que.size() >= sizeof(param))
        {
            std::vector<char> data(sizeof(param));
            for (auto &cvalue: data)
                {
                    cvalue = que.front();
                    que.pop_front();
                }
            std::memcpy(&output, data.data(), sizeof(param));
            return true;
        }
    return false;
}


auto read(std::deque<char> &que, BaseHeader &ohb) -> bool
{
    // print(que, 16);
    consume_que(que, ohb.ObjSign);
    // print(que, 16);
    if (ohb.ObjSign != ObjectSignature)
        {
            std::cout << "Not Found LOBJ: " << std::hex << (int) ohb.ObjSign;
            std::cout << '\n';
            return false;
        }

    consume_que(que, ohb.headerSize);
    // print(que, 16);
    consume_que(que, ohb.headerVer);
    // print(que, 16);
    consume_que(que, ohb.objSize);
    // print(que, 16);
    consume_que(que, ohb.objectType);
    // print(que, 16);

    return true;
}


auto read(std::fstream &fs, LogContainer &lc, const BaseHeader &ohb) -> bool
{
    fs.read(reinterpret_cast<char *>(&lc), sizeof(LogContainer));

    if (lc.compressionMethod == compressionMethod_e::uncompressed)
        {
            lc.unCompressedFileSize = ohb.objSize - sizeof(lc.compressionMethod) - sizeof(lc.reserv1) - sizeof(lc.reserv2) - sizeof(lc.unCompressedFileSize) - sizeof(lc.reserv3);
        }

    return true;
}


template <typename type_data>
auto read_template(std::fstream &fs, type_data &data) -> bool
{
    fs.read(reinterpret_cast<char *>(&data), sizeof(type_data));
    return true;
}


template <typename type_data>
auto read_template(const uint8_t *indata_array, type_data &data) -> size_t
{
    std::memcpy(reinterpret_cast<char *>(&data), indata_array, sizeof(type_data));
    return sizeof(type_data);
}


void print(const std::vector<uint8_t> &data)
{
    size_t cnt = 0;
    for (auto a: data)
        {
            std::cout << " " << std::hex << std::setfill('0') << std::setw(2) << (int) a;
            cnt++;
            if ((cnt % 16) == 0)
                {
                    std::cout << '\n';
                }
        }
    std::cout << '\n';
}


auto handle_container_compressed_deque(
    std::vector<uint8_t> &compressedData,
    const LogContainer &lc,
    std::deque<char> &logcontainer_que) -> int
{
    uLong uncompressedFileSize = lc.unCompressedFileSize;
    std::vector<uint8_t> uncompressedData {};

    uncompressedData.resize(uncompressedFileSize);

    int retVal = uncompress(
        reinterpret_cast<Byte *>(uncompressedData.data()),
        &uncompressedFileSize,
        reinterpret_cast<Byte *>(compressedData.data()),
        static_cast<uLong>(compressedData.size()));

    // std::cout << __FUNCTION__ << " retVal; " << std::dec << retVal << '\n';

    logcontainer_que.insert(logcontainer_que.end(), uncompressedData.begin(), uncompressedData.end());

    // print(uncompressedData);

    return retVal;
}


auto handle_ObjectType(std::deque<char> &log_que, const BaseHeader &ohb) -> exit_codes
{
    const auto payload_size = ohb.objSize - ohb.headerSize;
    switch (ohb.objectType)
        {
        case (ObjectType_e::CAN_MESSAGE): // read Can message;
            {
                struct ObjectHeader oheader;
                consume_que(log_que, oheader);
                //	  print(std::cout, oheader);
                if (payload_size == sizeof(CanMessage))
                    {
                        struct CanMessage cmessage;
                        if (consume_que(log_que, cmessage))
                            {
                                print(std::cout, cmessage);
                            }
                    }
                else
                    {
                        return exit_codes::CAN_MESSAGE_INVALID_LENGTH;
                    }
            }
            break;

        case (ObjectType_e::CAN_ERROR): // CanErrorFrame
            {
                struct ObjectHeader oheader;
                consume_que(log_que, oheader);
                print(std::cout, oheader);
                if (payload_size == sizeof(CanError_short))
                    {
                        struct CanError_short cef;
                        consume_que(log_que, cef);
                        print(std::cout, cef);
                    }
                else if (payload_size == sizeof(CanError))
                    {
                        struct CanError cef;
                        consume_que(log_que, cef);
                        print(std::cout, cef);
                    }
            }
            break;


        case (ObjectType_e::CAN_OVERLOAD): // CanOverload
            {
                print(std::cout, ohb);
                struct ObjectHeader oheader;
                consume_que(log_que, oheader);
                print(std::cout, oheader);
                if (payload_size == sizeof(CanOverload))
                    {
                        struct CanOverload col;
                        consume_que(log_que, col);
                        print(std::cout, col);
                    }
                else if (payload_size == sizeof(CanOverload_short))
                    {
                        struct CanOverload_short cols;
                        consume_que(log_que, cols);
                        print(std::cout, cols);
                    }
                else
                    {
                        std::cout << "Error wrong CanOverload Frame!\n";
                    }
            }
            break;

        case (ObjectType_e::APP_TRIGGER): // Handle apptrigger
            {
                struct ObjectHeader oh;
                consume_que(log_que, oh);
                // print(std::cout, oh);
                struct AppTrigger ap;
                consume_que(log_que, ap);
                print(std::cout, ap);
            }
            break;

        case (ObjectType_e::LOG_CONTAINER): // Get Logcontainer
            {
                std::cout << "Log container not implemented inside a log container\n";
                return exit_codes::UNHANDLED_OBJECT_TYPE;
                break;
            }

        case (ObjectType_e::CAN_MESSAGE2):
            {
                struct ObjectHeader oh;
                consume_que(log_que, oh);
                //	  print(std::cout, oh);
                struct CanMessage2 cm2;
                if (consume_que(log_que, cm2))
                    {
                        print(std::cout, cm2);
                    }
            }
            break;

        case (ObjectType_e::APP_TEXT):
            {
                struct ObjectHeader oh;
                consume_que(log_que, oh);
                struct AppText ap;
                consume_que(log_que, ap.mSource);
                consume_que(log_que, ap.reserved);
                consume_que(log_que, ap.mTextLength);
                uint32_t dummy = 0;
                consume_que(log_que, dummy);
                std::cout << std::dec << "objSize: " << (int) ohb.objSize << ", TextLength: " << (int) ap.mTextLength;
                std::string app_text_string;
                for (uint32_t i = 0; i < ap.mTextLength; ++i)
                    {
                        app_text_string.insert(app_text_string.begin() + i, log_que.front());
                        log_que.pop_front();
                    }
                // std::cout << "App_text: " << app_text_string << '\n';
            }
            break;

        case (ObjectType_e::reserved_5):
            {
                struct ObjectHeader oh;
                consume_que(log_que, oh);
                struct reserved_5 r5;
                consume_que(log_que, r5);
                print(std::cout, r5);
            }
            break;

        case (ObjectType_e::CAN_STATISTIC):
            {
                ObjectHeader oh;
                consume_que(log_que, oh);
                CANDriverStatistic can_stat;
                consume_que(log_que, can_stat);
                print(std::cout, can_stat);
                const auto rest = payload_size - sizeof(CANDriverStatistic);
                std::cout << "rest: " << rest << '\n';
                std::cout << "Left in deque: " << log_que.size() << '\n';
                log_que.erase(log_que.begin(), log_que.begin() + rest);
            }
            break;

        default:
            std::cout << "New ObjectType: " << (int) ohb.objectType << '\n';
            return exit_codes::UNHANDLED_OBJECT_TYPE;
        }
    return exit_codes::EXITING_SUCCESS;
}


class blf_reader
{
private:
    std::fstream fs;
    std::deque<char> logcontainer_que;
    fileStatistics fileStat;
    auto fill_deque() -> bool;

public:
    blf_reader(const blf_reader &) = delete;
    blf_reader(blf_reader &&) = delete;
    auto operator=(const blf_reader &) -> blf_reader & = delete;
    auto operator=(blf_reader &&) -> blf_reader & = delete;
    explicit blf_reader(const std::string &filename);
    ~blf_reader();
    auto next() -> bool;
    auto data() -> struct lobj;
    auto fileStatistics() -> struct fileStatistics;
};


inline auto blf_reader::fill_deque() -> bool
{
    struct BaseHeader ohb;
    if (read(fs, ohb))
        {
            // Successful with object header
        }
    else
        {
            return false;
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

            if (lc.compressionMethod == compressionMethod_e::zlib)
                {
                    const auto retVal = handle_container_compressed_deque(
                        container_data,
                        lc,
                        logcontainer_que);
                    if (retVal not_eq 0)
                        {
                            throw std::runtime_error("zlib error");
                        }
                }
            else
                {
                    throw std::runtime_error("Not implemented uncompressed");
                }
        }
    else
        {
            const int32_t bytes_to_jump = ohb.objSize - ohb.headerSize + (ohb.objSize % 4);
            // std::cout << "To jump: " << bytes_to_jump << '\n';
            fs.seekg(bytes_to_jump, std::ios_base::cur);
        }
    return true;
}


blf_reader::blf_reader(const std::string &filename)
{
    fs.open(filename, std::fstream::in | std::fstream::binary);

    if (fs.fail())
        {
            throw std::runtime_error("Failed to open file: " + filename);
        }

    if (fs)
        {
            if (read(fs, fileStat))
                {
                    print(std::cout, fileStat);
                }
            else
                {
                    throw std::runtime_error("Not BLF file: " + filename);
                }
        }
    fill_deque();
}


blf_reader::~blf_reader()
{
    fs.close();
}


auto blf_reader::fileStatistics() -> struct fileStatistics
{
    return fileStat;
}


auto
blf_reader::next() -> bool
{
    return !fs.eof();
}


auto blf_reader::data() -> struct lobj
{
    struct lobj result;
    if (logcontainer_que.size() < sizeof(BaseHeader))
        {
            fill_deque();
        }

    if (logcontainer_que.empty())
        {
            result.base_header.objectType = static_cast<ObjectType_e>(0x888);
            return result;
        }

    read(logcontainer_que, result.base_header);

    lblf::print(std::cout, result.base_header);
    const size_t size_of_data = result.base_header.objSize - sizeof(result.base_header) + (result.base_header.objSize % 4);

    if (logcontainer_que.size() < size_of_data)
        {
            fill_deque();
        }

    result.payload.clear();
    result.payload.reserve(size_of_data);
    for (size_t i = 0; i < size_of_data; ++i)
        {
            result.payload.push_back(logcontainer_que.front());
            logcontainer_que.pop_front();
        }

    return result;
}


void
doit(const std::string &filename)
{
    blf_reader reader(filename);
    size_t counter = 0;
    while (reader.next())
        {
            counter++;
            const auto data = reader.data();
            std::cout << std::dec << counter << ", ";
            print(data.base_header.objectType);
        }
}


auto main(int argc, char *argv[]) -> int
{

    std::cout << "----- START OF OUTPUT -----------------------------\n";

    if (argc > 1)
        {
            // go_through_file( argv[1] );
            doit(argv[1]);
        }
    else
        {
            std::cout << "run blf evaluation: " << argv[0] << " filname.blf\n";
        }

    std::cout << "----- END OF OUTPUT -----------------------------\n";
}
