#ifndef BLF_STRUCTS_HH
#define BLF_STRUCTS_HH


enum class ObjectType : uint32_t {
  UNKNOWN = 0,
  CAN_MESSAGE = 1,
  CAN_ERROR = 2,
  CAN_OVERLOAD = 3,
  APP_TRIGGER = 5,
  LOG_CONTAINER = 10,
  CAN_MESSAGE2 = 86
};


#pragma pack(1)

struct sysTime_t
{
    uint16_t year;
    uint16_t month;
    uint16_t dayOfWeek;
    uint16_t day;
    uint16_t hour;
    uint16_t minute;
    uint16_t second;
    uint16_t milliseconds;
};


struct fileStatistics
{
    uint32_t FileSign;
    uint32_t StatSize;
    uint8_t  AppId;
    uint8_t  AppMaj;
    uint8_t  AppMin;
    uint8_t  AppBuild;
    uint8_t  ApiMaj;
    uint8_t  ApiMin;
    uint8_t  ApiBuild;
    uint8_t  ApiPatch;
    uint64_t fileSize;
    uint64_t uncompressedSize;
    uint32_t objCount;
    uint32_t objRead;
    sysTime_t meas_start_time;
    sysTime_t last_obj_time;
    uint64_t fileSize_less115;
};


struct ObjectHeaderBase
{
    uint32_t ObjSign;
    uint16_t headerSize;
    uint16_t headerVer;
    uint32_t objSize;
    uint32_t objectType;
};


enum ObjectFlags_e : uint32_t
{
    TimeTenMics = 0x00000001,
    TimeNano = 0x00000002
};

enum timeStampStatus_e : uint8_t
{
    orginal = 0x01, SwGen = 0x02, User = 0x10
};


struct ObjectHeader2
{
    ObjectFlags_e objectFlags;
    timeStampStatus_e  timeStampStatus;
    uint8_t  reservObjHeader;
    uint16_t ObjectHeaderVersion;
    uint64_t ObjectTimeStamp;
    uint64_t originalObjectTimeStamp;
};


enum compressionMethod_e : int16_t
{
    uncompressed = 0x00,
    zlib = 0x02
};


struct LogContainer
{
    compressionMethod_e compressionMethod;
    uint16_t reserv1;
    uint32_t reserv2;
    uint32_t unCompressedFileSize;
    uint32_t reserv3;
};


struct ObjectHeader
{
    ObjectFlags_e objectFlag;
    uint16_t clientIndex;
    uint16_t objectVersion;
    uint64_t objectTimeStamp;
};


struct CanMessage
{
    uint16_t channel;
    uint8_t flags;
    uint8_t dlc;
    uint32_t id;
    std::array<uint8_t, 8> data {};
};


struct CanError
{
    uint16_t channel;
    uint16_t length;
    uint32_t reservedCanErrorFrame;
};


struct CanOverload
{
    uint16_t channel;
    uint16_t reservedCanOverloadFrame1;
    uint32_t reservedCanOverloadFrame2; // Corrected //?? 
};


struct CanMessage2
{
    uint16_t channel;
    uint8_t flags;
    uint8_t dlc;
    uint32_t id;
    std::array<uint8_t, 8> data {};
    uint32_t frameLength;
    uint8_t bitCount;
    uint8_t reservedCanMessage1;
    uint16_t reservedCanMessage2;  
};


struct AppTrigger
{
    uint64_t preTriggerTime;
    uint64_t postTriggerTime;
    uint16_t channel;
    uint16_t flags;
    uint32_t appSpecific2;
};


struct CanErrorFrame
{
    uint16_t channel;
    uint16_t length;
    uint32_t reservedCanErrorFrame;
};

#pragma pack()

#endif
