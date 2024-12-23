#include <deque>
#include <functional>
#include <iostream>
#include <optional>
#include <string>

// A sample struct to be returned by the read() function.
struct Data
{
    int id;
    std::string value;
};

class DataProcessor
{
public:
    explicit DataProcessor(std::function<std::deque<Data>()> replenisher)
        : replenisher_function(std::move(replenisher))
    {
        replenish();
    }

    // Function to process the next section of the deque.
    auto next() -> bool
    {
        if (data_queue.empty())
            {
                replenish();
                if (data_queue.empty())
                    {
                        return false; // Deque is empty and could not be replenished.
                    }
            }

        // Process and remove the front element of the deque.
        current_data = data_queue.front();
        data_queue.pop_front();
        return true;
    }

    // Function to read the current data.
    [[nodiscard]] auto read() const -> std::optional<Data>
    {
        return current_data;
    }

private:
    std::deque<Data> data_queue;                            // Internal deque.
    std::optional<Data> current_data;                       // Currently processed data.
    std::function<std::deque<Data>()> replenisher_function; // Function to replenish the deque.

    // Replenishes the deque using the replenisher function.
    void replenish()
    {
        if (replenisher_function)
            {
                auto new_data = replenisher_function();
                data_queue.insert(data_queue.end(), new_data.begin(), new_data.end());
            }
    }
};


// Example replenisher function.
auto example_replenisher() -> std::deque<Data>
{
    static int counter = 1;
    std::deque<Data> new_data;
    for (int i = 0; i < 5; ++i)
        {
            new_data.push_back({counter++, "Value " + std::to_string(counter)});
        }
    return new_data;
}


auto main() -> int
{
    // Create a DataProcessor instance with the example replenisher.
    DataProcessor processor(example_replenisher);

    // Process and read data until the deque cannot be replenished.
    while (processor.next())
        {
            if (auto data = processor.read())
                {
                    std::cout << "ID: " << data->id << ", Value: " << data->value << '\n';
                }
        }

    std::cout << "Deque processing completed." << '\n';
    return 0;
}
