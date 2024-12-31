#ifndef PRINT_HH
#define PRINT_HH

#include <deque>
#include <iostream>
#include <string>
#include <vector>

#include "blf_structs.hh"

namespace lblf::print
{
void print(std::ostream &stream, const std::vector<uint8_t> &data);
void print(std::ostream &stream, const std::deque<char> &data, size_t counts_to_print);
auto print(lblf::exit_codes ec) -> std::string;
auto print(lblf::ObjectType_e ot) -> std::string;
auto print(lblf::AppId_e ai) -> std::string;
auto print(lblf::ObjectFlags_e of) -> std::string;
auto print(lblf::timeStampStatus_e tss) -> std::string;
void print(std::ostream &stream, const lblf::sysTime_t &ts);
void print(std::ostream &stream, const lblf::fileStatistics &os);
void print(std::ostream &stream, const lblf::BaseHeader &ohb);
void print(std::ostream &stream, const lblf::ObjectHeader &oh);
void print(std::ostream &stream, const lblf::ObjectHeader2 &oh2);
void print(std::ostream &stream, const lblf::ObjectHeaderCarry &ohc);
void print(std::ostream &stream, const lblf::LogContainer &lc);
void print(std::ostream &stream, const lblf::CanMessage &cm);
void print(std::ostream &stream, const lblf::CanOverload &co);
void print(std::ostream &stream, const lblf::CanOverload_short &co);
void print(std::ostream &stream, const lblf::CanMessage2 &cm2);
void print(std::ostream &stream, const CanMessage2_obh &cm2);
void print(std::ostream &stream, const lblf::AppTrigger &at);
void print(std::ostream &stream, const lblf::AppText &at);
void print(std::ostream &stream, const lblf::reserved_5 &r);
void print(std::ostream &stream, const lblf::CanError &cfe);
void print(std::ostream &stream, const lblf::CanError_short &cfe);
void print(std::ostream &stream, const lblf::CANErrorFrameExt &ce);
void print(std::ostream &stream, const CANDriverStatistic &can_stat);
void print(std::ostream &stream, const lblf::CanMessage_common &cm);
} // namespace lblf::print

#endif