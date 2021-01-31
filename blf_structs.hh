#ifndef BLF_STRUCTS_HH
#define BLF_STRUCTS_HH


enum class ObjectType_e : uint32_t
{
    UNKNOWN                       = 0,
    CAN_MESSAGE                   = 1,
    CAN_ERROR                     = 2,
    CAN_OVERLOAD                  = 3,
    APP_TRIGGER                   = 5,
    ENV_INTEGER                   = 6,
    ENV_DOUBLE                    = 7,
    ENV_STRING                    = 8,
    ENV_DATA                      = 9,
    LOG_CONTAINER                = 10,
    LIN_MESSAGE                  = 11,
    LIN_CRC_ERROR                = 12,
    LIN_DLC_INFO                 = 13,
    LIN_RCV_ERROR                = 14,
    LIN_SND_ERROR                = 15,
    LIN_SLV_TIMEOUT              = 16,
    LIN_SCHED_MODCH              = 17,
    LIN_SYN_ERROR                = 18,
    LIN_BAUDRATE                 = 19,
    LIN_SLEEP                    = 20,
    LIN_WAKEUP                   = 21,
    MOST_SPY                     = 22,
    MOST_CTRL                    = 23,
    MOST_LIGHTLOCK               = 24,
    MOST_STATISTIC               = 25,
    reserved_1                   = 26,
    reserved_2                   = 27,
    reserved_3                   = 28,
    FLEXRAY_DATA                 = 29,
    FLEXRAY_SYNC                 = 30,
    CAN_DRIVER_ERROR             = 31,
    MOST_PKT                     = 32,
    MOST_PKT2                    = 33,
    MOST_HWMODE                  = 34,
    MOST_REG                     = 35,
    MOST_GENREG                  = 36,
    MOST_NETSTATE                = 37,
    MOST_DATALOST                = 38,
    MOST_TRIGGER                 = 39,
    FLEXRAY_CYCLE                = 40,
    FLEXRAY_MESSAGE              = 41,
    LIN_CHECKSUM_INFO            = 42,
    LIN_SPIKE_EVENT              = 43,
    CAN_DRIVER_SYNC              = 44,
    FLEXRAY_STATUS               = 45,
    GPS_EVENT                    = 46,
    FR_ERROR                     = 47,
    FR_STATUS                    = 48,
    FR_STARTCYCLE                = 49,
    FR_RCVMESSAGE                = 50,
    REALTIMECLOCK                = 51,
    AVAILABLE2                   = 52,
    AVAILABLE3                   = 53,
    LIN_STATISTIC                = 54,
    J1708_MESSAGE                = 55,
    J1708_VIRTUAL_MSG            = 56,
    LIN_MESSAGE2                 = 57,
    LIN_SND_ERROR2               = 58,
    LIN_SYN_ERROR2               = 59,
    LIN_CRC_ERROR2               = 60,
    LIN_RCV_ERROR2               = 61,
    LIN_WAKEUP2                  = 62,
    LIN_SPIKE_EVENT2             = 63,
    LIN_LONG_DOM_SIG             = 64,
    APP_TEXT                     = 65,
    FR_RCVMESSAGE_EX             = 66,
    MOST_STATISTICEX             = 67,
    MOST_TXLIGHT                 = 68,
    MOST_ALLOCTAB                = 69,
    MOST_STRESS                  = 70,
    ETHERNET_FRAME               = 71,
    SYS_VARIABLE                 = 72,
    CAN_ERROR_EXT                = 73,
    CAN_DRIVER_ERROR_EXT         = 74,
    LIN_LONG_DOM_SIG2            = 75,
    MOST_150_MESSAGE             = 76,
    MOST_150_PKT                 = 77,
    MOST_ETHERNET_PKT            = 78,
    MOST_150_MESSAGE_FRAGMENT    = 79,
    MOST_150_PKT_FRAGMENT        = 80,
    MOST_ETHERNET_PKT_FRAGMENT   = 81,
    MOST_SYSTEM_EVENT            = 82,
    MOST_150_ALLOCTAB            = 83,
    MOST_50_MESSAGE              = 84,
    MOST_50_PKT                  = 85,
    CAN_MESSAGE2                 = 86,
    LIN_UNEXPECTED_WAKEUP       =  87,
    LIN_SHORT_OR_SLOW_RESPONSE  =  88,
    LIN_DISTURBANCE_EVENT       =  89,
    SERIAL_EVENT                =  90,
    OVERRUN_ERROR               =  91,
    EVENT_COMMENT               =  92,
    WLAN_FRAME                  =  93,
    WLAN_STATISTIC              =  94,
    MOST_ECL                    =  95,
    GLOBAL_MARKER               =  96,
    AFDX_FRAME                  =  97,
    AFDX_STATISTIC              =  98,
    KLINE_STATUSEVENT           =  99,
    CAN_FD_MESSAGE              = 100,
    CAN_FD_MESSAGE_64           = 101,
    ETHERNET_RX_ERROR           = 102,
    ETHERNET_STATUS             = 103,
    CAN_FD_ERROR_64             = 104,
    LIN_SHORT_OR_SLOW_RESPONSE2 = 105,
    AFDX_STATUS                 = 106,
    AFDX_BUS_STATISTIC          = 107,
    reserved_4                  = 108,
    AFDX_ERROR_EVENT            = 109,
    A429_ERROR                  = 110,
    A429_STATUS                 = 111,
    A429_BUS_STATISTIC          = 112,
    A429_MESSAGE                = 113,
    ETHERNET_STATISTIC          = 114,
    reserved_5                  = 115,
    reserved_6                  = 116,
    reserved_7                  = 117,
    TEST_STRUCTURE              = 118,
    DIAG_REQUEST_INTERPRETATION = 119,
    ETHERNET_FRAME_EX           = 120,
    ETHERNET_FRAME_FORWARDED    = 121,
    ETHERNET_ERROR_EX           = 122,
    ETHERNET_ERROR_FORWARDED    = 123,
    FUNCTION_BUS                = 124,
    DATA_LOST_BEGIN             = 125,
    DATA_LOST_END               = 126,
    WATER_MARK_EVENT            = 127,
    TRIGGER_CONDITION           = 128
};


enum class AppId_e : uint8_t
{
    UNKNOWN       = 0,
    CANALYZER     = 1,
    CANOE         = 2,
    CANSTRESS     = 3,
    CANLOG        = 4,
    CANAPE        = 5,
    CANCASEXLLOG  = 6,
    VLCONFIG      = 7,
    PORSCHELOGGER = 200
};

//For DriverOverrun.
enum class BusType : uint32_t
{
    CAN      = 1,
    LIN      = 5,
    MOST     = 6,
    FLEXRAY  = 7,
    J1708    = 9,
    ETHERNET = 10,
    WLAN     = 13,
    AFDX     = 14
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
    AppId_e AppId; //uint8_t
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
    enum ObjectType_e objectType; //  : uint32_t;
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


struct CanError_short
{
    uint16_t channel;
    uint16_t length;
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


#pragma pack()

#endif
