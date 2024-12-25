#ifndef PRINT_HH
#define PRINT_HH


#include <iostream>
#include <string>

#include "blf_structs.hh"

namespace lblf
{

auto print(lblf::exit_codes ec) -> std::string;
auto print(lblf::ObjectType_e ot) -> std::string;
auto print(lblf::AppId_e ai) -> std::string;
auto print(lblf::ObjectFlags_e of) -> std::string;
auto print(lblf::timeStampStatus_e tss) -> std::string;
void print(std::ostream &s, const lblf::sysTime_t &ts);
void print(std::ostream &s, const lblf::fileStatistics &os);
void print(std::ostream &s, const lblf::BaseHeader &ohb);
void print(std::ostream &s, const lblf::ObjectHeader &oh);
void print(std::ostream &s, const lblf::ObjectHeader2 &oh2);
void print(std::ostream &s, const lblf::ObjectHeaderCarry &ohc);
void print(std::ostream &s, const lblf::LogContainer &lc);
void print(std::ostream &s, const lblf::CanMessage &cm);
void print(std::ostream &s, const lblf::CanOverload &co);
void print(std::ostream &s, const lblf::CanOverload_short &co);
void print(std::ostream &s, const lblf::CanMessage2 &cm2);
void print(std::ostream &s, const lblf::AppTrigger &at);
void print(std::ostream &s, const lblf::AppText &at);
void print(std::ostream &s, const lblf::reserved_5 &r);
void print(std::ostream &s, const lblf::CanError &cfe);
void print(std::ostream &s, const lblf::CanError_short &cfe);
void print(std::ostream &s, const lblf::CANErrorFrameExt &ce);
void print(std::ostream &s, const CANDriverStatistic &can_stat);

} // namespace lblf

#endif