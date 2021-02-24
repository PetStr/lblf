#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>

#include <zlib.h>




auto uncompresser(std::vector<uint8_t> & uncompressed, 
                    std::vector<uint8_t> &compressed, uLongf output_size)
{
   
    auto compressedSize = compressed.size();
    uncompressed.resize(output_size);

    //Byte * in = nullptr; 
    //std::copy(uncompressed.cbegin(), uncompressed.cend(), in);

    auto retVal = ::uncompress(
                     reinterpret_cast<Byte *>(uncompressed.data()),
                     &output_size,
                     reinterpret_cast<Byte *>(compressed.data()),
                     static_cast<uLong>(compressedSize));
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

uint32_t fileLength(std::istream &fs)
{
    fs.seekg(0, fs.end);
    uint32_t length = fs.tellg();
    fs.seekg(0, fs.beg);
    return length;
}


int main()
{

    std::vector<uint8_t> indata = { 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,0x55, 
    0x55, 0x55,0x55, 0x55, 0x55,0x55, 0x55, 0x55,0x55, 0x55, 0x55 , 0xAA, 0xAA,0x55, 0x55, 
    0x55,0x55, 0x55, 0x55,0x55, 0x55, 0x55 , 0xAA, 0xAA };
    
    size_t indata_size = indata.size();
    std::cout << "indata.size: " << indata_size << '\n';
    
    std::stringstream binary_buffer;

    for (const auto& v : indata) {
        binary_buffer.write(reinterpret_cast<const char*>(&v), sizeof(uint8_t));
    }

    std::cout << "stream length: " << fileLength(binary_buffer) << '\n';

    print(indata);


    
    std::vector<uint8_t> okompad;
    char buffer[1];
    while (binary_buffer.read(buffer, 1)) {
        okompad.push_back(*reinterpret_cast<uint8_t*>(buffer));
    }

    std::cout << "stream length after read : " << fileLength(binary_buffer) << '\n';


    print(okompad);

    std::vector<uint8_t> kompressed;
    pressa(okompad, kompressed,9);
    print(kompressed);

    std::vector<uint8_t> okompad_tillbaka(indata_size);
    uncompresser(okompad_tillbaka,  kompressed, indata_size);
    print(okompad_tillbaka);

    return EXIT_SUCCESS;
}