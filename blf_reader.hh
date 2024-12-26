#ifndef BLF_READER_HH
#define BLF_READER_HH

#include "blf_structs.hh"
#include <deque>
#include <fstream>

namespace lblf
{

struct lobj
{
    BaseHeader base_header;
    std::vector<char> payload {};
};

class blf_reader
{
private:
    std::fstream fs;
    std::deque<char> logcontainer_que;
    fileStatistics fileStat;
    auto fill_deque() -> bool;

public:
    blf_reader(const blf_reader &) = delete;
    blf_reader(blf_reader &&) = delete;
    auto operator=(const blf_reader &) -> blf_reader & = delete;
    auto operator=(blf_reader &&) -> blf_reader & = delete;
    explicit blf_reader(const std::string &filename);
    ~blf_reader();
    auto next() -> bool;
    auto data() -> struct lobj;
    auto fileStatistics() -> struct fileStatistics;
};

} // namespace lblf

#endif
