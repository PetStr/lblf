#ifndef PRINT_HH
#define PRINT_HH

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "blf_structs.hh"


std::string print(exit_codes ec);
std::string print(ObjectType_e ot);
std::string print(AppId_e ai);
std::string print(ObjectFlags_e of);
std::string print(timeStampStatus_e tss);
void print(std::ostream &s, const sysTime_t &ts);
void print(std::ostream &s, const fileStatistics &os);
void print(std::ostream &s, const ObjectHeaderBase &ohb);
void print(std::ostream &s, const ObjectHeader2 &oh2);
void print(std::ostream &s, const LogContainer &lc);
void print(std::ostream &s, const ObjectHeader &oh);
void print(std::ostream &s, const CanMessage &cm);
void print(std::ostream &s, const CanOverload &co);
void print(std::ostream &s, const CanOverload_short &co);
void print(std::ostream &s, const CanMessage2 &cm2);
void print(std::ostream &s, const AppTrigger &at);
void print(std::ostream &s, const AppText &at);
void print(std::ostream &s, const reserved_5 &r);
void print(std::ostream &s, const CanError &cfe);
void print(std::ostream &s, const CanError_short &cfe);

#endif