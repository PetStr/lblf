#include <functional> // For std::function
#include <iostream>
#include <optional>
#include <vector>

class BufferedReader
{
public:
    using SourceReader = std::function<std::size_t(char*, std::size_t)>;

    BufferedReader(std::size_t buffer_capacity, SourceReader source_reader)
        : buffer_(buffer_capacity)
        , source_reader_(source_reader)
        , read_pos_(0)
        , buffer_size_(0)
    {
    }

    // Read 'n' bytes into 'dest'. Returns the number of bytes actually read.
    auto read(char* dest, std::size_t n) -> std::size_t
    {
        std::size_t total_read = 0;

        while (n > 0)
            {
                if (read_pos_ >= buffer_size_)
                    {
                        // Buffer underflow, refill it
                        refill();
                        if (buffer_size_ == 0)
                            {
                                // Source is exhausted, stop reading
                                break;
                            }
                    }

                // Calculate how many bytes to copy from the buffer
                std::size_t bytes_available = buffer_size_ - read_pos_;
                std::size_t bytes_to_copy = std::min(n, bytes_available);

                // Copy bytes to destination
                std::memcpy(dest + total_read, buffer_.data() + read_pos_, bytes_to_copy);

                // Update positions and counters
                read_pos_ += bytes_to_copy;
                total_read += bytes_to_copy;
                n -= bytes_to_copy;
            }

        return total_read;
    }

private:
    std::vector<char> buffer_;
    SourceReader source_reader_; // Function to refill data
    std::size_t read_pos_;       // Current read position
    std::size_t buffer_size_;    // Number of valid bytes in the buffer

    void refill()
    {
        read_pos_ = 0; // Reset position to the beginning
        buffer_size_ = source_reader_(buffer_.data(), buffer_.size());
    }
};

int main()
{
    // Example source reader: Simulates intermittent data source
    auto source_reader = [](char* buffer, std::size_t max_bytes) -> std::size_t {
        static int call_count = 0;
        ++call_count;

        if (call_count <= 10)
            {
                // Fill buffer with 'A', 'B', 'C'... for demo purposes
                std::size_t bytes_to_write = std::min<std::size_t>(max_bytes, 50);
                for (std::size_t i = 0; i < bytes_to_write; ++i)
                    {
                        buffer[i] = 'A' + i;
                    }
                return bytes_to_write;
            }
        else
            {
                std::cout <<  "Simulate end of data\n";
                return 0;
            }
    };

    BufferedReader buffered_reader(5, source_reader);

    char read_buffer[10];
    std::size_t total_bytes_read = buffered_reader.read(read_buffer, 10);

    std::cout << "Read " << total_bytes_read << " bytes: ";
    for (auto value : read_buffer)
        {
            std::cout << value;
        }
    std::cout << '\n';
    std::cout << '\n';

    char read_buffer2[32];
    total_bytes_read = buffered_reader.read(read_buffer2, 32);

    std::cout << "Read " << total_bytes_read << " bytes: ";
    for (auto value : read_buffer2)
        {
            std::cout << value;
        }
    std::cout << '\n';

    return 0;
}
