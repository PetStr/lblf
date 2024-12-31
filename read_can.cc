
#include "blf_reader.hh"
#include "blf_structs.hh"
#include "print.hh"
#include <cstring>
#include <iostream>


void read_all_candata(const std::string &filename)
{
    lblf::blf_reader reader(filename);
    size_t counter = 0;
    while (reader.next())
        {
            const auto data = reader.data();
            struct lblf::CanMessage_common cmm;
            switch (data.base_header.objectType)
                {
                case lblf::ObjectType_e::CAN_MESSAGE:
                    {
                        struct lblf::CanMessage_obh can;
                        lblf::read_blf_struct(data, can);
                        cmm.got_data = true;
                        cmm.obh = can.obh;
                        cmm.id = can.id;
                        cmm.dlc = can.dlc;
                        cmm.channel = can.channel;
                        cmm.flags = can.flags;
                        cmm.data = can.data;
                        counter++;
                        break;
                    }

                case lblf::ObjectType_e::CAN_MESSAGE2:
                    {
                        struct lblf::CanMessage2_obh can2;
                        lblf::read_blf_struct(data, can2);
                        cmm.got_data = true;
                        cmm.obh = can2.obh;
                        cmm.id = can2.id;
                        cmm.dlc = can2.dlc;
                        cmm.flags = can2.flags;
                        cmm.channel = can2.channel;
                        cmm.data = can2.data;
                        counter++;
                        break;
                    }
                default:
                    {
                        // Nothing exciting happened.
                    }
                }
            if (cmm.got_data)
                {
                    std::cout << std::dec << counter << ": ";
                    lblf::print::print(std::cout, cmm);
                }
        }
}


auto main(int argc, char *argv[]) -> int
{
    std::cout << "----- START OF OUTPUT -----------------------------\n";

    if (argc > 1)
        {
            try
                {
                    const std::string filename(argv[1]); // NOLINT
                    read_all_candata(filename);
                }
            catch (const std::runtime_error &error)
                {
                    std::cout << "Error: " << error.what() << '\n';
                }
            catch (...)
                {
                    std::cout << "Houston, we have a problem\n";
                }
        }
    else
        {
            std::cout << "run blf evaluation: " << argv[0] << " filname.blf\n"; // NOLINT
        }

    std::cout << "----- END OF OUTPUT -----------------------------\n";
}
