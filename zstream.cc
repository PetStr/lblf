#include <iostream>
#include <vector>
#include <algorithm>
#include <zlib.h>




void uncompresser(std::vector<uint8_t> & uncompressedFile, 
    const std::vector<uint8_t> &compressedFile, size_t compressed )
{
    
    std::streampos m_tellg;
    uint64_t uncompressedFileSize, filePosition;

    //std::streamoff offset = m_tellg - filePosition;
    //std::streamsize n;
    //std::streamsize gcount = std::min(n, static_cast<std::streamsize>(uncompressedFileSize - offset));

  
    uLong bytes_left_in_container = lc.unCompressedFileSize;
    
    auto compressedFileSize = ohb.objSize - ohb.headerSize - sizeof(LogContainer);
    compressedFile.resize(compressedFileSize);

    fs.read(reinterpret_cast<char *>(compressedFile.data()), compressedFileSize);

    uncompressedFile.resize(bytes_left_in_container);
    int retVal = ::uncompress(
                     reinterpret_cast<Byte *>(uncompressedFile.data()),
                     &bytes_left_in_container,
                     reinterpret_cast<Byte *>(compressedFile.data()),
                     static_cast<uLong>(compressedFileSize));

    std::copy(uncompressedFile.cbegin() + offset, uncompressedFile.cbegin() + offset + gcount, s);

}

