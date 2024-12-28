/**
 * @file blf_reader.cc
 * @author Petter Strandh (petter.strandh@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include "blf_reader.hh"
#include "blf_structs.hh"
#include "print.hh"
#include <cstring>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <zlib.h>

// hexdump -v -C -n 512 truck02.blf


using namespace lblf;


namespace {

const uint32_t FileSignature = 0x47474F4C;   // LOGG
const uint32_t ObjectSignature = 0x4A424F4C; // LOBJ

const uint32_t defaultContainerSize = 0x20000;


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
    consume_que(que, ohb.ObjSign);
    if (ohb.ObjSign != ObjectSignature)
        {
            std::cout << "Not Found LOBJ: " << std::hex << (int) ohb.ObjSign;
            std::cout << '\n';
            return false;
        }
    consume_que(que, ohb.headerSize);
    consume_que(que, ohb.headerVer);
    consume_que(que, ohb.objSize);
    consume_que(que, ohb.objectType);
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

    logcontainer_que.insert(logcontainer_que.end(), uncompressedData.begin(), uncompressedData.end());

    return retVal;
}

} // namespace

auto blf_reader::fill_deque() -> bool
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
            // print(std::cout, lc);
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
                    print(std::cout, lc);
                    logcontainer_que.insert(logcontainer_que.end(), container_data.begin(), container_data.end());
                    //throw std::runtime_error("Not implemented uncompressed");
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


auto blf_reader::data() -> struct lblf::lobj
{
    struct lblf::lobj result;
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

    // lblf::print(std::cout, result.base_header);
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
