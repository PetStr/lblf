#include <deque>
#include <iostream>
#include <algorithm>

class DynamicBuffer {
public:
    // Add data to the buffer
    void append(const char* data, std::size_t size) {
        buffer_.insert(buffer_.end(), data, data + size);
    }

    // Consume data from the front of the buffer
    std::size_t consume(std::size_t n) {
        std::size_t to_consume = std::min(n, buffer_.size());
        buffer_.erase(buffer_.begin(), buffer_.begin() + to_consume);
        return to_consume;
    }

    // Get the size of the buffer
    std::size_t size() const {
        return buffer_.size();
    }

    // Print buffer contents (demonstration)
    void print() const {
        for (char c : buffer_) {
            std::cout << c;
        }
        std::cout << '\n';
    }

private:
    std::deque<char> buffer_;
};

int main() {
    DynamicBuffer buffer;

    // Simulate appending data
    buffer.append("Hello", 5);
    buffer.append(" World", 6);

    std::cout << "Buffer size: " << buffer.size() << "\n";
    std::cout << "Buffer contents: ";
    buffer.print();

    // Simulate consuming data
    std::size_t consumed = buffer.consume(7);
    std::cout << "Consumed " << consumed << " bytes\n";

    std::cout << "Remaining buffer size: " << buffer.size() << "\n";
    std::cout << "Remaining buffer contents: ";
    buffer.print();

    return 0;
}
