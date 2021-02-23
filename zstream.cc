#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>

#include <zlib.h>




auto uncompresser(std::vector<uint8_t> & uncompressed, 
                    std::vector<uint8_t> &compressed)
{
   
    auto compressedSize = compressed.size();
    compressed.resize(compressedSize);

    //Byte * in = nullptr; 
    //std::copy(uncompressed.cbegin(), uncompressed.cend(), in);

    auto retVal = ::uncompress(
                     reinterpret_cast<Byte *>(uncompressed.data()),
                     &compressedSize,
                     reinterpret_cast<Byte *>(compressed.data()),
                     static_cast<uLong>(compressedSize));

    uncompressed.resize(compressedSize);

    return retVal;
}


auto pressa(std::vector<uint8_t> & uncompressed, 
                std::vector<uint8_t> &compressed, 
                const int compressionLevel)
{
        /* deflate/compress data */
        uLong compressedBufferSize = compressBound(uncompressed.size());
        std::cout << "compressBound: " << std::dec << compressedBufferSize << '\n';
        compressed.resize(compressedBufferSize); // extend
        auto retVal = ::compress2(
                         reinterpret_cast<Byte *>(compressed.data()),
                         &compressedBufferSize,
                         reinterpret_cast<Byte *>(uncompressed.data()),
                         uncompressed.size(),
                         compressionLevel);
        
        std::cout << "compressBound after: " << std::dec << compressedBufferSize << '\n';
        compressed.resize(compressedBufferSize);
                    
    return retVal;
}

void print(const std::vector<uint8_t> &data)
{
    std::cout << "size:" << std::dec << data.size() << " ;capacity " << data.capacity() << " : ";
    for(const auto a : data)
        {
            std::cout << " " << std::hex << std::setfill('0') << std::setw(2) << static_cast<int> (a);
        }
        std::cout << '\n';
}





int main()
{

    std::vector<uint8_t> okompad = { 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,0x55, 0x55, 0x55,0x55, 0x55, 0x55,0x55, 0x55, 0x55,0x55, 0x55, 0x55,0x55, 0x55, 0x55 };
    print(okompad);

    std::vector<uint8_t> kompressed;
    pressa(okompad, kompressed,9);
    print(kompressed);

    std::vector<uint8_t> okompad_tillbaka(40);
    uncompresser(okompad_tillbaka,  kompressed);
    print(okompad_tillbaka);

    return EXIT_SUCCESS;
}