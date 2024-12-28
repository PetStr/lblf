#include <deque>
#include <iostream>
#include <string>
#include <variant>

// Define possible types
struct StructA
{
    int value;
    void print() const
    {
        std::cout << "StructA: " << value << '\n';
    }
};

struct StructB
{
    std::string text;
    void print() const
    {
        std::cout << "StructB: " << text << '\n';
    }
};

using VariantType = std::variant<StructA, StructB>;

auto main() -> int
{
    std::deque<VariantType> deque;

    // Add different types of structs
    deque.emplace_back(StructA {42});
    deque.emplace_back(StructB {"Hello"});

    // Process and print
    for (const auto& item: deque)
        {
            std::visit([](const auto& data) { data.print(); }, item);
        }

    return 0;
}
