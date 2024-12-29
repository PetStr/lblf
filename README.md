# lblf - lite binary logging file reader

`lblf` is an implementation for reading Vector BLF files, the main driver for making this is to have a fast, simple and small tool for parsing BLF files. Aim is to have simple and fast program for special use cases. Aim is to support all platforms for little endian. 

## Introduction 

BLF Logging File (BLF) is a file format created by [Vector](http://www.vector.com) which is their main preferred log file format. For Vector customers there exists a dll `binlog` as their reference implementation. However, that is only available for Vector customers and only for Windows platform x86. 

The BLF can handle various network types such as CAN, LIN, ETHERNET, MOST and to forth.  Many CAN loggers can emit blf format file and it can be used for Vector CANalyzer and other analytics software. 

The main source for information is Tobias Lorenz [vector_blf](https://bitbucket.org/tobylorenz/vector_blf/src/master/) which is a very nice reference implementation. However, the vector_blf implementation is fairly large, complex and performance is slow for my liking. 

By searching internet for `BLF`, `binlog`, `BINLOG-DLL-Manual`, `vector_blf` and `binlog_objects.h` it is possible to find information regarding the inner working about this file format.


## File data structure

The BLF file starts with "LOGG" or 0x47474F4C(GGOL) intel byteorder.
Followed by fileStatistics struct. 

At byte 144 the data follows. 

Data starts with an BaseHeader which always starts with LOBJ 0x4A424F4C(JBOL).

Which is subsequent followed by a two possible ObjectHeaders

* ObjectHeader.
* ObjectHeader2. 

Followed by a dynamic struct based on the type in BaseHeader.

## The Log Container
All data should be wrapped within a LogContainer. 

The LogContainer can uncompressed or compressed with zlib. The zlib LogContainer will contain a block of 131072 (0x20000) bytes. The zlib blocks will cut in the middle of the under laying data stream so that in order to process, a continuous data flow must be created to read the underlying data.

## Using lblf.

This is a sample code of how reading a blf looks like. Common for all LOBJ is the BaseHeader. The rest is variable lengths base on type and length of data. 

```cpp
#include "blf_structs.hh"
#include "blf_reader.hh"

struct lblf::lobj
{
    BaseHeader base_header;
    std::vector<char> payload {};
};

void read_blf()
{
  lblf::blf_reader reader(filename);
    while (reader.next())
        {
            struct lblf::lobj data = reader.data();
            // do stuff with data.
        }
}
```
## Building
