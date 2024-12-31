# lblf - the lite Binary Logging File (BLF) reader

`lblf` is an implementation for reading Vector BLF files. 

* Simple and fast program for special use cases.
* To support all major platforms, right now only for little endian. 

## Introduction 

BLF Logging File (BLF) is a file format created by [Vector](http://www.vector.com) which is their main preferred log file format. For Vector customers there exists a dll `binlog` as their reference implementation. However, that is only available for Vector customers and only for Windows platform x86. 

The BLF can handle various network types such as CAN, LIN, ETHERNET, MOST and to forth.  Many CAN loggers can export BLF formatted file and it can be used for Vector CANalyzer and other analytics software.

The main source for information is Tobias Lorenz [vector_blf](https://bitbucket.org/tobylorenz/vector_blf/src/master/) which is a very nice reference implementation. However, the vector_blf implementation is fairly large, complex and performance is slow for my liking. 

By searching internet for `BLF`, `binlog`, `BINLOG-DLL-Manual`, `vector_blf` and `binlog_objects.h` it is possible to find information regarding the inner working about this file format.


## File data structure

The BLF file starts with "LOGG" or 0x47474F4C(GGOL) intel byteorder.
Followed by fileStatistics struct. 

At byte 144 the data follows. 

Data starts with a BaseHeader which always starts with LOBJ 0x4A424F4C(JBOL).

Which is subsequent followed by a two possible ObjectHeaders. Followed by a dynamic struct based on the number of `objectType` type in the BaseHeader.

## The Log Container
All data should be wrapped within a LogContainer. 

The LogContainer can be uncompressed or compressed with zlib. The zlib LogContainer will contain a block of 131072 (0x20000) bytes. The zlib blocks will cut in the middle of the under laying data stream so that in order to process, a continuous data flow must be created to read the underlying data.

## Using lblf.

This is a small sample code of how reading a blf looks like. Common for all LOBJ is the BaseHeader. Depending of the `objectType` the data an be fixed size. Simple read into a `#pragma pack(1)` struct or data is of variable length first read the fixed data then the variable length, for example AppText.

Example code for printing all CAN_MESSAGE2 data from given BLF file:

```cpp
#include "blf_structs.hh"
#include "blf_reader.hh"
#include "print.hh"

struct lblf::lobj
{
    lblf::BaseHeader base_header;
    std::vector<char> payload {};
};

void read_blf()
{
  lblf::blf_reader reader("sample.blf");
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
```

How to handle the various data types is up to the user. I would expect that the files are evaluated in a specific domain. The `payload` is in a `std::vector<char>` then it can be cast into a struct and then the dynamic portion of the data needs to be added outside of the struct. 

## Building

The only external dependency is zlib. If installed properly it should only require the `-lz` linker switch.

A sample program can be built with cmake. A simple one liner can do it as well.

```console
mkdir build
cd build
cmake ..
make
```

Or just a one liner for quick iterations.

```console
g++ -std=c++20 blf_reader.cc read.cc print.cc -o read -lz
```

## Customization.  

The main thing is to handle all the possible ~130 different types of `objectType`s. Using read_blf_struct to catch the first static struct formatted part of the data. Then as a second stage catch the rest of the data that is in dynamic size.

By looking into `binlog_objects.h` one can see the structs on the early versions of BLF. However this is not always true. best way is to look into `vector_blf` reference to see what is done there. `blf_structs.hh` contains a small subset of the various structs. It is not complete!

### Handling CAN frames. 

In the BLF, there are several object types that deals with CAN.

The older loggers tends to stores in CAN_MESSAGE objectType, and new implementations as CANalyzer stores in CAN_MESSAGE2 format.

If a certain signal from a CAN is to be evaluated I have found [dbcc](https://github.com/howerj/dbcc) to be very helpful. Howerj´s software will convert a Vector `dbc` file into `C`. I have found to simply look into the generated code and then cut and paste the needed signals into the evaluating code will help with handling tricky conversions and bit shifts. 

## ToDo's

* Creating BLF_writer class for storing data.
* Now when reading a uncompressed LogContainer all data is retrieved into the internal buffer. Intend to make  user adjustable or use the standard length for zlib container to keep the memory footprint a bit smaller. This is not a problem for normal PCs however, might be an issue for smaller foot print computers. It can be an issue for PCs if the BLF are very large.
* Working on ideas to smother handle the different object types. There are ideas with `C++ concepts` that will be able to handle various types without virtual functions calls.
* I am a bit tempted to look into Godbolting some of the code in the hot path for better performance. 
* Make a Python wrapper so that is it can improve the life for evaluating data.


Happy Coding

PetStr
