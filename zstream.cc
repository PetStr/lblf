#include <iostream>
#include <vector>
#include <algorithm>
#include <zlib.h>



 void f()
 {
std::vector<uint8_t> uncompressedFile;

std::streampos m_tellg;

uint64_t uncompressedFileSize, filePosition;

std::streamoff offset = m_tellg - filePosition;

std::streamsize n;

std::streamsize gcount = std::min(n, static_cast<std::streamsize>(uncompressedFileSize - offset));



 std::copy(uncompressedFile.cbegin() + offset, uncompressedFile.cbegin() + offset + gcount, s);

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
    int retVal = ::uncompress(
                     reinterpret_cast<Byte *>(uncompressedFile.data()),
                     &bytes_left_in_container,
                     reinterpret_cast<Byte *>(compressedFile.data()),
                     static_cast<uLong>(compressedFileSize));

 }