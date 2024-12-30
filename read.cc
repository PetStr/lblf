
#include "blf_reader.hh"
#include "print.hh"
#include <cstring>
#include <iostream>
#include <map>

template <typename type_data>
auto read_template(const char *indata_array, type_data &data) -> size_t
{
    std::memcpy(reinterpret_cast<char *>(&data), indata_array, sizeof(type_data));
    return sizeof(type_data);
}


void doit(const std::string &filename)
{
    lblf::blf_reader reader(filename);
    size_t counter = 0;
    while (reader.next())
        {
            counter++;
            const auto data = reader.data();
            std::cout << std::dec << counter << ", ";
            std::cout << lblf::print::print(data.base_header.objectType) << '\n';
        }
}


void doit2(const std::string &filename)
{
    lblf::blf_reader reader(filename);
    size_t counter = 0;
    while (reader.next())
        {
            counter++;
            const auto data = reader.data();
            if (data.base_header.objectType == lblf::ObjectType_e::CAN_MESSAGE2)
                {
                    struct lblf::CanMessage2_obh can2;
                    if (sizeof(can2) <= data.payload.size())
                        {
                            lblf::read_blf_struct(data, can2);
                        }
                    std::cout << std::dec << counter << ", ";
                    lblf::print::print(std::cout, can2);
                }
        }
}


void doit3(const std::string &filename)
{
    lblf::blf_reader reader(filename);
    size_t counter = 0;
    while (reader.next())
        {
            counter++;
            const auto data = reader.data();
            if (data.base_header.objectType == lblf::ObjectType_e::APP_TEXT)
                {
                    struct lblf::AppText_obh Apptext;
                    if (sizeof(Apptext) <= data.payload.size())
                        {
                            read_template(data.payload.data(), Apptext);
                        }
                    std::cout << std::dec << counter << ", ";
                    std::string AppText_string;
                    const auto length = Apptext.mTextLength;
                    const auto offset = sizeof(Apptext);
                    const auto far_length = length + offset;
                    for (size_t i = offset; i < far_length; ++i)
                        {
                            AppText_string.push_back(data.payload.at(i));
                        }
                    std::cout << AppText_string << '\n';
                }
        }
    std::cout << std::dec << "Loops: " << counter << '\n';
}


void doit4(const std::string &filename)
{
    std::map<lblf::ObjectType_e, size_t> input_types;
    lblf::blf_reader reader(filename);
    size_t counter = 0;
    while (reader.next())
        {
            counter++;
            const auto data = reader.data();
            input_types[data.base_header.objectType]++;
        }
    std::cout << std::dec << "Loops: " << counter << '\n';
    for (const auto value: input_types)
        {
            std::cout << lblf::print::print(value.first) << '\t' << value.second << '\n';
        }
    std::cout << "Number of BaseHead reads: " << std::dec << reader.getBaseHeadRead() << '\n';
}


auto main(int argc, char *argv[]) -> int
{
    std::cout << "----- START OF OUTPUT -----------------------------\n";

    if (argc > 1)
        {
            try
                {
                    const std::string filename(argv[1]);
                    doit4(filename);
                }
            catch (...)
                {
                    std::cout << "Houston, we have a problem\n";
                }
        }
    else
        {
            std::cout << "run blf evaluation: " << argv[0] << " filname.blf\n";
        }

    std::cout << "----- END OF OUTPUT -----------------------------\n";
}
