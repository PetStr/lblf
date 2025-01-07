
#include "blf_reader.hh"
#include "print.hh"


auto main(int argc, char *argv[]) -> int
{
    std::cout << "----- START OF OUTPUT -----\n";

    if (argc > 1)
        {
            try
                {
                    const std::string filename(argv[1]); // NOLINT
                    lblf::blf_reader reader(filename);
                    lblf::print::print(std::cout, reader.getfileStatistics());
                }
            catch (const std::runtime_error &error)
                {
                    std::cout << "Error: " << error.what() << '\n';
                }
        }
    else
        {
            std::cout << "run blf evaluation: " << argv[0] << " filname.blf\n"; // NOLINT
        }

    std::cout << "----- END OF OUTPUT -----\n";
}
