/**
 * @file object_types.cc
 * @author Petter Strandh (github.com/PetStr/lblf)
 * @brief Sample code to show of to extract a list of possible LOBJ in BLF.
 * @version 0.1
 * @date 2024-12-31
 *
 * @copyright Copyright (c) 2024
 *
 */


#include "blf_reader.hh"
#include "blf_structs.hh"
#include "print.hh"
#include <map>

void object_types(const std::string &filename)
{
    std::map<lblf::ObjectType_e, std::pair<size_t, size_t>> input_types;
    lblf::blf_reader reader(filename);
    size_t counter = 0;
    while (reader.next())
        {
            counter++;
            const auto data = reader.data();
            input_types[data.base_header.objectType].first++;
            input_types[data.base_header.objectType].second += data.base_header.objSize;
        }
    std::cout << std::dec << "Loops: " << counter << '\n';
    std::cout << "ObjectType: Number of frames\n";
    std::cout << "------------------------------------------------\n";

    for (const auto &value: input_types)
        {
            std::cout << lblf::print::print(value.first) << ": " 
            << value.second.first << " frames, " <<value.second.second << " bytes\n";
        }
    std::cout << "Number of BaseHead reads: " << std::dec << reader.getBaseHeadRead() << '\n';
}


auto main(int argc, char *argv[]) -> int
{
    std::cout << "----- START OF OUTPUT -----\n";

    if (argc > 1)
        {
            try
                {
                    const std::string filename(argv[1]); //NOLINT
                    object_types(filename);
                }
            catch (const std::runtime_error &error)
                {
                    std::cout << "Error: " << error.what() << '\n';
                }
        }
    else
        {
            std::cout << "run blf evaluation: " << argv[0] << " filname.blf\n"; //NOLINT
        }

    std::cout << "----- END OF OUTPUT -----\n";
}
