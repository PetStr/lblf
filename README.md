# lblf - lite binary logging file

## Abstract 
`lblf` is an implementation for Vector BLF file that main driver is to be small and fast.

BLF Logging File (BLF) is a file format created by [Vector](http://www.vector.com) which is their main preferred log file format. For Vector customers there exists a dll `binlog` as their reference implementation. However that is only available for Vector customers and only for Windows. 

Since blf is a capable format it has several use cases. Many CAN loggers can emit blf format file and it can be used for Vector CANALYSER and other analytics software. 

The main over source is Tobias Lorenz [vector_blf](https://bitbucket.org/tobylorenz/vector_blf/src/master/) which is a very nice reference implementation. However, vector_blf implementation is fairly large and performance is slow. 


##Data structure

The BLF file starts with "LOGG" or 0x47474F4C(GGOL) intel byteorder.
Followed by fileStatistics struct. 

At byte 144 the data follows. 

Data starts with an BaseHeader. each BaseHeader starts with LOBJ 0x4A424F4C(JBOL).

Which is subsequent followed by a two possible ObjectHeaders

* 16bytes. No additional header. typical for LogContainer. 
* 32bytes, ObjectHeader.
* 40bytes, ObjectHeader2. 

All data should be wrapped within a LogContainer. 

The LogContainer can raw or be compressed with zlib. The zlib LogContainer will contain a block of 131072 (0x20000) bytes. The zlib blocks will cut in the middle of the under laying data so that in order to process a continuous data flow must be created to read the underlying data.
