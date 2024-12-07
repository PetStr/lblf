#include <iostream>
#include <fstream>
#include <vector>
#include <zlib.h>  // zlib header for decompression

class ZlibStreamReader {
public:
    explicit ZlibStreamReader(std::istream &inputStream, size_t bufferSize = 8192)
        : input(inputStream), inputBuffer(bufferSize), outputBuffer(bufferSize) {
        // Initialize zlib stream
        inflateStream.zalloc = Z_NULL;
        inflateStream.zfree = Z_NULL;
        inflateStream.opaque = Z_NULL;

        // Initialize inflation (decompression) process
        if (inflateInit(&inflateStream) != Z_OK) {
            throw std::runtime_error("Failed to initialize zlib decompression.");
        }
    }

    ~ZlibStreamReader() {
        inflateEnd(&inflateStream);  // Clean up zlib resources
    }

    // Reads decompressed data into user-provided buffer
    size_t read(char *buffer, size_t size) {
        size_t totalBytesRead = 0;

        while (totalBytesRead < size) {
            if (outputPos == outputEnd) {
                if (!inflateNextChunk()) {
                    break;  // No more data to decompress
                }
            }

            // Copy decompressed data to the user buffer
            size_t remaining = size - totalBytesRead;
            size_t available = outputEnd - outputPos;
            size_t toCopy = std::min(remaining, available);

            std::memcpy(buffer + totalBytesRead, outputBuffer.data() + outputPos, toCopy);
            totalBytesRead += toCopy;
            outputPos += toCopy;
        }

        return totalBytesRead;
    }

private:
    std::istream &input;              // Compressed input stream
    std::vector<char> inputBuffer;    // Buffer for compressed data
    std::vector<char> outputBuffer;   // Buffer for decompressed data

    z_stream inflateStream{};         // zlib decompression state
    size_t outputPos = 0;             // Current position in output buffer
    size_t outputEnd = 0;             // End position of valid decompressed data

    // Load the next chunk of compressed data and decompress
    bool inflateNextChunk() {
        // Read compressed data into inputBuffer
        input.read(inputBuffer.data(), inputBuffer.size());
        std::streamsize bytesRead = input.gcount();
        if (bytesRead == 0) return false;  // No more data in the input stream

        // Setup zlib input
        inflateStream.next_in = reinterpret_cast<Bytef *>(inputBuffer.data());
        inflateStream.avail_in = static_cast<uInt>(bytesRead);

        // Decompress into outputBuffer
        inflateStream.next_out = reinterpret_cast<Bytef *>(outputBuffer.data());
        inflateStream.avail_out = static_cast<uInt>(outputBuffer.size());

        // Perform decompression
        int ret = inflate(&inflateStream, Z_NO_FLUSH);
        if (ret != Z_OK && ret != Z_STREAM_END) {
            throw std::runtime_error("Zlib decompression failed.");
        }

        outputPos = 0;  // Reset output buffer position
        outputEnd = outputBuffer.size() - inflateStream.avail_out;  // Amount decompressed
        return outputEnd > 0;
    }
};

int main() {
    try {
        std::ifstream file("compressed_file.zlib", std::ios::binary);
        if (!file) {
            std::cerr << "Failed to open file.\n";
            return 1;
        }

        ZlibStreamReader reader(file);
        std::vector<char> buffer(1024);

        // Read and print decompressed data
        while (size_t bytesRead = reader.read(buffer.data(), buffer.size())) {
            std::cout.write(buffer.data(), bytesRead);
        }

        std::cout << "\nDecompression complete.\n";
    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
