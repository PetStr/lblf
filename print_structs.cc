#include <iostream>
#include <fstream>
#include <array>
#include <iomanip>

#include "blf_structs.hh"

int main()
{

    std::cout << "sysTime_t       : " << std::dec << sizeof(sysTime_t         ) << '\n';
    std::cout << "fileStatistics  : " << std::dec << sizeof(fileStatistics    ) << '\n';
    std::cout << "ObjectHeaderBase: " << std::dec << sizeof(ObjectHeaderBase  ) << '\n';
    std::cout << "ObjectHeader    : " << std::dec << sizeof(ObjectHeader      ) << '\n';
    std::cout << "ObjectHeader2   : " << std::dec << sizeof(ObjectHeader2     ) << '\n';
    std::cout << "LogContainer    : " << std::dec << sizeof(LogContainer      ) << '\n';
    std::cout << "CanMessage      : " << std::dec << sizeof(CanMessage        ) << '\n';
    std::cout << "CanMessage2     : " << std::dec << sizeof(CanMessage2       ) << '\n';
    std::cout << "AppTrigger      : " << std::dec << sizeof(AppTrigger        ) << '\n';
    std::cout << "CanError        : " << std::dec << sizeof(CanError          ) << '\n';
    std::cout << "CanOverload     : " << std::dec << sizeof(CanOverload       ) << '\n';
    std::cout << "CanError_short  : " << std::dec << sizeof(CanError_short    ) << '\n';
    std::cout << "CanOverload_shor: " << std::dec << sizeof(CanOverload_short ) << '\n';
    std::cout << "CanOverload     : " << std::dec << sizeof(CanOverload       ) << '\n';
    std::cout << "uint            : " << std::dec << sizeof(unsigned int      ) << '\n';
    std::cout << "long int        : " << std::dec << sizeof(long int          ) << '\n';
    std::cout << "long            : " << std::dec << sizeof(long              ) << '\n';
    std::cout << "ObjectHeaderCarry : " << std::dec << sizeof(ObjectHeaderCarry ) << '\n';
    std::cout << "ObjectHeaders_e : " << std::dec << sizeof(ObjectHeaders_e ) << '\n';
    std::cout << "CANErrorFrameExt : " << std::dec << sizeof(CANErrorFrameExt ) << '\n';
    


    return 0;
}

