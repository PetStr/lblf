
#include "blf_structs.hh"
#include "blf_reader.hh"
#include "print.hh"



void read_blf(const std::string & filename)
{
  lblf::blf_reader reader(filename);
    while (reader.next())
        {
            struct lblf::lobj data = reader.data();
            if (data.base_header.objectType == lblf::ObjectType_e::CAN_MESSAGE2)
                {
                    struct lblf::CanMessage2_obh can2;
                    lblf::read_blf_struct(data, can2);
                    lblf::print::print(std::cout, can2);
                }
        }
}


auto main(int argc, char *argv[]) -> int
{
    std::cout << "----- START OF OUTPUT -----\n";

    if (argc > 1)
        {
            try
                {
                    const std::string filename(argv[1]);
                    read_blf(filename);
                }
            catch (const std::runtime_error &error)
                {
                    std::cout << "Error: " << error.what() << '\n';
                }
        }
    else
        {
            std::cout << "run blf evaluation: " << argv[0] << " filname.blf\n";
        }

    std::cout << "----- END OF OUTPUT -----\n";
}
