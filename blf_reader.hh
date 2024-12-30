#ifndef BLF_READER_HH
#define BLF_READER_HH

#include "blf_structs.hh"
#include <cstring>
#include <deque>
#include <fstream>
#include <vector>

namespace lblf
{


/**
 * @brief lobj frame struct
 * 
 */
struct lobj
{
    BaseHeader base_header;
    std::vector<char> payload;
};


/**
 * @brief Static lobj reading function
 * 
 * @tparam type_data typically a struct with that aligns with blf type 
 * @param indata incoming lobj frame
 * @param blf_struct_data var parameter of type_data
 * @return size_t Number of read bytes
 */
template <typename type_data>
auto read_blf_struct(const struct lobj &indata, type_data &blf_struct_data) -> size_t
{
    if (indata.payload.size() >= sizeof(type_data))
        {
            std::memcpy(reinterpret_cast<char *>(&blf_struct_data),
                indata.payload.data(),
                sizeof(type_data));
            return sizeof(type_data);
        }
    return 0;
}


/**
 * @brief blf_reader class
 * 
 */
class blf_reader
{
private:
    std::fstream fileStream;
    std::deque<char> logcontainer_que;
    fileStatistics fileStat;
    uint32_t fileLength {0};
    size_t BaseHeaderRead {0};
    auto fill_deque() -> bool;
    auto read_baseHeader(BaseHeader &ohb) -> bool;
    auto read_fileStatistics() -> bool;

public:
    blf_reader(const blf_reader &) = delete;
    blf_reader(blf_reader &&) = delete;
    auto operator=(const blf_reader &) -> blf_reader & = delete;
    auto operator=(blf_reader &&) -> blf_reader & = delete;
    explicit blf_reader(const std::string &filename);
    ~blf_reader();
    auto next() -> bool;
    auto data() -> struct lobj;
    auto getfileStatistics() const -> const struct fileStatistics&;
    auto getBaseHeadRead() const -> size_t;
};

} // namespace lblf

#endif
