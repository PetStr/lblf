/**
 * @file blf_reader.cc
 * @author Petter Strandh (petter.strandh@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-12-27
 *
 * MIT License
 *
 * @copyright (c) 2024 Petter Strandh
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, subject
 * to the following conditions:
 *
 * 1. The above copyright notice, this list of conditions, and the following disclaimer
 *    shall be included in all copies or substantial portions of the Software.
 * 2. Credit to the original author(s) must be prominently displayed in any derivative
 *    works or redistributed versions, in a reasonable form such as a README file,
 *    documentation, or within the user interface of the software where appropriate.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES, OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT,
 * OR OTHERWISE, ARISING FROM, OUT OF, OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */


#include "blf_reader.hh"
#include "blf_structs.hh"
#include "print.hh"
#include <cstring>
#include <stdexcept>
#include <vector>
#include <zlib.h>

// hexdump -v -C -n 512 truck02.blf

namespace lblf
{

namespace
{

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


    auto read_baseheader(std::deque<char> &que, lblf::blf_struct::BaseHeader &ohb) -> bool
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


    auto read_logcontainer(std::fstream &fileStream, blf_struct::LogContainer &lc, const blf_struct::BaseHeader &ohb) -> bool
    {
        fileStream.read(reinterpret_cast<char *>(&lc), sizeof(blf_struct::LogContainer));

        if (lc.compressionMethod == compressionMethod_e::uncompressed)
            {
                lc.unCompressedFileSize = ohb.objSize - sizeof(lc.compressionMethod) - sizeof(lc.reserv1) - sizeof(lc.reserv2) - sizeof(lc.unCompressedFileSize) - sizeof(lc.reserv3);
            }

        return true;
    }


    auto fill_deque_direct(std::fstream &fileStream, std::deque<char> &logcontainer_que, uint32_t bytes_to_read) -> void
    {
        std::vector<char> container_data;
        container_data.resize(bytes_to_read);
        fileStream.read(reinterpret_cast<char *>(container_data.data()), bytes_to_read);
        logcontainer_que.insert(logcontainer_que.end(), container_data.begin(), container_data.end());
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
    fileStream.read(reinterpret_cast<char *>(&fileStat.applicationBuild), sizeof(fileStat.applicationBuild));
    fileStream.read(reinterpret_cast<char *>(&fileStat.meas_start_time), sizeof(fileStat.meas_start_time));
    fileStream.read(reinterpret_cast<char *>(&fileStat.last_obj_time), sizeof(fileStat.last_obj_time));
    fileStream.read(reinterpret_cast<char *>(&fileStat.fileSize_less115), sizeof(fileStat.fileSize_less115));
    const uint32_t offset = fileStat.StatSize - sizeof(fileStat);
    fileStream.seekg(offset, std::ios_base::cur);
    return true;
}

auto blf_reader::read_baseHeader(blf_struct::BaseHeader &ohb) -> bool
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
    static bool split_read = false;
    static uint32_t rest_of_data = 0;
    static struct blf_struct::BaseHeader ohb;

    if (split_read)
        {
            if (rest_of_data > defaultContainerSize)
                {
                    split_read = true;
                    fill_deque_direct(fileStream, logcontainer_que, defaultContainerSize);
                    rest_of_data = rest_of_data - defaultContainerSize;
                    return true;
                }

            split_read = false;
            fill_deque_direct(fileStream, logcontainer_que, rest_of_data);
            rest_of_data = 0;
            fileStream.seekg(ohb.objSize % 4, std::ios_base::cur);
            return true;
        }


    if (fileStream.eof())
        {
            std::cout << "BLF file ended\n";
            return false;
        }

    // struct blf_struct::BaseHeader ohb;
    if (read_baseHeader(ohb))
        {
            BaseHeaderRead++;
        }
    else
        {
            return false;
        }

    if (ohb.objectType == ObjectType_e::LOG_CONTAINER)
        {
            struct blf_struct::LogContainer lc;
            read_logcontainer(fileStream, lc, ohb);
            // print(std::cout, lc);

            if (lc.compressionMethod == compressionMethod_e::zlib)
                {
                    std::vector<char> container_data;
                    const auto compressedBlobSize = ohb.objSize - ohb.headerSize - sizeof(blf_struct::LogContainer);

                    container_data.resize(compressedBlobSize);

                    fileStream.read(reinterpret_cast<char *>(container_data.data()), compressedBlobSize);
                    fileStream.seekg(ohb.objSize % 4, std::ios_base::cur);

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
                    const auto uncompressedBlobSize = ohb.objSize - ohb.headerSize - sizeof(blf_struct::LogContainer);
                    if (uncompressedBlobSize > defaultContainerSize)
                        {
                            split_read = true;
                            fill_deque_direct(fileStream, logcontainer_que, defaultContainerSize);
                            rest_of_data = uncompressedBlobSize - defaultContainerSize;
                        }
                }
        }
    else
        {
            // I should never end up here
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
                    // lblf::print::print(std::cout, fileStat);
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
    return !logcontainer_que.empty() || (fileStream.tellg() < fileLength);
}


auto blf_reader::getfileStatistics() const -> const struct blf_struct::fileStatistics &
{
    return fileStat;
}


auto blf_reader::getBaseHeadRead() const -> size_t
{
    return BaseHeaderRead;
}


auto blf_reader::data() -> struct lblf::lobj
{
    struct lblf::lobj result;
    if (logcontainer_que.size() < sizeof(blf_struct::BaseHeader))
        {
            fill_deque();
        }

    if (logcontainer_que.empty())
        {
            result.base_header.objectType = static_cast<ObjectType_e>(0x888);
            return result;
        }

    if (read_baseheader(logcontainer_que, result.base_header))
        {
            BaseHeaderRead++;
        }

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

} // namespace lblf
