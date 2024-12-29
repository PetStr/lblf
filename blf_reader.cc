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


namespace
{

const uint32_t FileSignature = 0x47474F4C;   // LOGG
const uint32_t ObjectSignature = 0x4A424F4C; // LOBJ
const uint32_t defaultContainerSize = 0x20000;


auto getfileLength(std::fstream &fileStream) -> uint32_t
{
    fileStream.seekg(0, std::fstream::end);
    const uint32_t length = fileStream.tellg();
    fileStream.seekg(0, std::fstream::beg);
    return length;
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


auto read_deque(std::deque<char> &que, BaseHeader &ohb) -> bool
{
    consume_que(que, ohb.ObjSign);
    if (ohb.ObjSign != ObjectSignature)
        {
            std::cout << "consume_que Not Found LOBJ: " << std::hex << (int) ohb.ObjSign;
            std::cout << '\n';
            return false;
        }
    consume_que(que, ohb.headerSize);
    consume_que(que, ohb.headerVer);
    consume_que(que, ohb.objSize);
    consume_que(que, ohb.objectType);
    return true;
}


auto read_logcontainer(std::fstream &fileStream, LogContainer &lc, const BaseHeader &ohb) -> bool
{
    fileStream.read(reinterpret_cast<char *>(&lc), sizeof(LogContainer));

    if (lc.compressionMethod == compressionMethod_e::uncompressed)
        {
            lc.unCompressedFileSize = ohb.objSize - sizeof(lc.compressionMethod) - sizeof(lc.reserv1) - sizeof(lc.reserv2) - sizeof(lc.unCompressedFileSize) - sizeof(lc.reserv3);
        }

    return true;
}


} // namespace


auto blf_reader::read_fileStatistics() -> bool
{
    fileStream.read(reinterpret_cast<char *>(&fileStat.FileSign), sizeof(fileStat.FileSign));
    if (fileStat.FileSign != FileSignature)
        {
            return false;
        }

    fileStream.read(reinterpret_cast<char *>(&fileStat.StatSize), sizeof(fileStat.StatSize));
    fileStream.read(reinterpret_cast<char *>(&fileStat.AppId), sizeof(fileStat.AppId));
    fileStream.read(reinterpret_cast<char *>(&fileStat.AppMaj), sizeof(fileStat.AppMaj));
    fileStream.read(reinterpret_cast<char *>(&fileStat.AppMin), sizeof(fileStat.AppMin));
    fileStream.read(reinterpret_cast<char *>(&fileStat.AppBuild), sizeof(fileStat.AppBuild));
    fileStream.read(reinterpret_cast<char *>(&fileStat.ApiMaj), sizeof(fileStat.ApiMaj));
    fileStream.read(reinterpret_cast<char *>(&fileStat.ApiMin), sizeof(fileStat.ApiMin));
    fileStream.read(reinterpret_cast<char *>(&fileStat.ApiBuild), sizeof(fileStat.ApiBuild));
    fileStream.read(reinterpret_cast<char *>(&fileStat.ApiPatch), sizeof(fileStat.ApiPatch));
    fileStream.read(reinterpret_cast<char *>(&fileStat.fileSize), sizeof(fileStat.fileSize));
    fileStream.read(reinterpret_cast<char *>(&fileStat.uncompressedSize), sizeof(fileStat.uncompressedSize));
    fileStream.read(reinterpret_cast<char *>(&fileStat.objCount), sizeof(fileStat.objCount));
    fileStream.read(reinterpret_cast<char *>(&fileStat.objRead), sizeof(fileStat.objRead));
    fileStream.read(reinterpret_cast<char *>(&fileStat.meas_start_time), sizeof(fileStat.meas_start_time));
    fileStream.read(reinterpret_cast<char *>(&fileStat.last_obj_time), sizeof(fileStat.last_obj_time));
    fileStream.read(reinterpret_cast<char *>(&fileStat.fileSize_less115), sizeof(fileStat.fileSize_less115));
    const uint32_t offset = fileStat.StatSize - sizeof(fileStat);
    fileStream.seekg(offset, std::ios_base::cur);
    return true;
}

auto blf_reader::read_baseHeader(BaseHeader &ohb) -> bool
{
    uint32_t current_position = fileStream.tellg();
    if (current_position == fileLength)
        {
            return false;
        }

    fileStream.read(reinterpret_cast<char *>(&ohb.ObjSign), sizeof(ohb.ObjSign));
    if (ohb.ObjSign != ObjectSignature)
        {
            std::cout << "Directly from file: Not Found LOBJ: " << std::hex << (int) ohb.ObjSign << '\n';
            return false;
        }
    fileStream.read(reinterpret_cast<char *>(&ohb.headerSize), sizeof(ohb.headerSize));
    fileStream.read(reinterpret_cast<char *>(&ohb.headerVer), sizeof(ohb.headerVer));
    fileStream.read(reinterpret_cast<char *>(&ohb.objSize), sizeof(ohb.objSize));
    fileStream.read(reinterpret_cast<char *>(&ohb.objectType), sizeof(ohb.objectType));
    return true;
}


auto blf_reader::fill_deque() -> bool
{
    if (fileStream.eof())
        {
            std::cout << "BLF file ended\n";
            return false;
        }

    struct BaseHeader ohb;
    if (read_baseHeader(ohb))
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
            read_logcontainer(fileStream, lc, ohb);
            // print(std::cout, lc);
            std::vector<char> container_data;
            auto compressedFileSize = ohb.objSize - ohb.headerSize - sizeof(LogContainer);

            // std::cout << "compressed blob: " << compressedFileSize << '\n';

            container_data.resize(compressedFileSize);

            fileStream.read(reinterpret_cast<char *>(container_data.data()), compressedFileSize);

            // Padding
            fileStream.seekg(ohb.objSize % 4, std::ios_base::cur);

            if (lc.compressionMethod == compressionMethod_e::zlib)
                {
                    uLong uncompressedFileSize = lc.unCompressedFileSize;
                    std::vector<uint8_t> uncompressedData {};

                    uncompressedData.resize(uncompressedFileSize);

                    const int retVal = uncompress(
                        reinterpret_cast<Byte *>(uncompressedData.data()),
                        &uncompressedFileSize,
                        reinterpret_cast<Byte *>(container_data.data()),
                        static_cast<uLong>(container_data.size()));

                    logcontainer_que.insert(logcontainer_que.end(), uncompressedData.begin(), uncompressedData.end());

                    if (retVal not_eq 0)
                        {
                            throw std::runtime_error("zlib error");
                        }
                }
            else
                {
                    lblf::print::print(std::cout, lc);
                    logcontainer_que.insert(logcontainer_que.end(), container_data.begin(), container_data.end());
                    // throw std::runtime_error("Not implemented uncompressed");
                }
        }
    else
        {
            const int32_t bytes_to_jump = ohb.objSize - ohb.headerSize + (ohb.objSize % 4);
            std::cout << "No LogContainer on fileStream, to jump: " << bytes_to_jump << '\n';
            fileStream.seekg(bytes_to_jump, std::ios_base::cur);
        }
    return true;
}


blf_reader::blf_reader(const std::string &filename)
{
    fileStream.open(filename, std::fstream::in | std::fstream::binary);

    if (fileStream.fail())
        {
            throw std::runtime_error("Failed to open file: " + filename);
        }

    if (fileStream)
        {
            fileLength = getfileLength(fileStream);
            if (read_fileStatistics())
                {
                    lblf::print::print(std::cout, fileStat);
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
    fileStream.close();
}


auto blf_reader::next() -> bool
{
    return not(logcontainer_que.empty() and (fileStream.tellg() >= fileLength));
}


auto blf_reader::fileStatistics() -> struct fileStatistics
{
    return fileStat;
}


auto
blf_reader::data() -> struct lblf::lobj
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

    read_deque(logcontainer_que, result.base_header);

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
