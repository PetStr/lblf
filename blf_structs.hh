#ifndef BLF_STRUCTS_HH
#define BLF_STRUCTS_HH

#include <array>
#include <cstdint>


/*
translate
WORD = uint16_t
DWORD = uint32_t
BYTE = uint8_t
*/

namespace lblf
{

enum class exit_codes : uint32_t
{
    EXITING_SUCCESS,
    UNABLE_TO_OPEN_FILE,
    NOT_A_VALID_BLF_FILE,
    CAN_MESSAGE_INVALID_LENGTH,
    LOGCONTAINER_WALK_THROUGH_FAIL,
    UNHANDLED_OBJECT_TYPE,
    UNABLE_TO_READ_OBJECT_HEADER_BASE
};


enum class ObjectType_e : uint32_t
{
    UNKNOWN = 0,
    CAN_MESSAGE = 1,
    CAN_ERROR = 2,
    CAN_OVERLOAD = 3,
    CAN_STATISTIC = 4,
    APP_TRIGGER = 5,
    ENV_INTEGER = 6,
    ENV_DOUBLE = 7,
    ENV_STRING = 8,
    ENV_DATA = 9,
    LOG_CONTAINER = 10,
    LIN_MESSAGE = 11,
    LIN_CRC_ERROR = 12,
    LIN_DLC_INFO = 13,
    LIN_RCV_ERROR = 14,
    LIN_SND_ERROR = 15,
    LIN_SLV_TIMEOUT = 16,
    LIN_SCHED_MODCH = 17,
    LIN_SYN_ERROR = 18,
    LIN_BAUDRATE = 19,
    LIN_SLEEP = 20,
    LIN_WAKEUP = 21,
    MOST_SPY = 22,
    MOST_CTRL = 23,
    MOST_LIGHTLOCK = 24,
    MOST_STATISTIC = 25,
    reserved_1 = 26,
    reserved_2 = 27,
    reserved_3 = 28,
    FLEXRAY_DATA = 29,
    FLEXRAY_SYNC = 30,
    CAN_DRIVER_ERROR = 31,
    MOST_PKT = 32,
    MOST_PKT2 = 33,
    MOST_HWMODE = 34,
    MOST_REG = 35,
    MOST_GENREG = 36,
    MOST_NETSTATE = 37,
    MOST_DATALOST = 38,
    MOST_TRIGGER = 39,
    FLEXRAY_CYCLE = 40,
    FLEXRAY_MESSAGE = 41,
    LIN_CHECKSUM_INFO = 42,
    LIN_SPIKE_EVENT = 43,
    CAN_DRIVER_SYNC = 44,
    FLEXRAY_STATUS = 45,
    GPS_EVENT = 46,
    FR_ERROR = 47,
    FR_STATUS = 48,
    FR_STARTCYCLE = 49,
    FR_RCVMESSAGE = 50,
    REALTIMECLOCK = 51,
    AVAILABLE2 = 52,
    AVAILABLE3 = 53,
    LIN_STATISTIC = 54,
    J1708_MESSAGE = 55,
    J1708_VIRTUAL_MSG = 56,
    LIN_MESSAGE2 = 57,
    LIN_SND_ERROR2 = 58,
    LIN_SYN_ERROR2 = 59,
    LIN_CRC_ERROR2 = 60,
    LIN_RCV_ERROR2 = 61,
    LIN_WAKEUP2 = 62,
    LIN_SPIKE_EVENT2 = 63,
    LIN_LONG_DOM_SIG = 64,
    APP_TEXT = 65,
    FR_RCVMESSAGE_EX = 66,
    MOST_STATISTICEX = 67,
    MOST_TXLIGHT = 68,
    MOST_ALLOCTAB = 69,
    MOST_STRESS = 70,
    ETHERNET_FRAME = 71,
    SYS_VARIABLE = 72,
    CAN_ERROR_EXT = 73,
    CAN_DRIVER_ERROR_EXT = 74,
    LIN_LONG_DOM_SIG2 = 75,
    MOST_150_MESSAGE = 76,
    MOST_150_PKT = 77,
    MOST_ETHERNET_PKT = 78,
    MOST_150_MESSAGE_FRAGMENT = 79,
    MOST_150_PKT_FRAGMENT = 80,
    MOST_ETHERNET_PKT_FRAGMENT = 81,
    MOST_SYSTEM_EVENT = 82,
    MOST_150_ALLOCTAB = 83,
    MOST_50_MESSAGE = 84,
    MOST_50_PKT = 85,
    CAN_MESSAGE2 = 86,
    LIN_UNEXPECTED_WAKEUP = 87,
    LIN_SHORT_OR_SLOW_RESPONSE = 88,
    LIN_DISTURBANCE_EVENT = 89,
    SERIAL_EVENT = 90,
    OVERRUN_ERROR = 91,
    EVENT_COMMENT = 92,
    WLAN_FRAME = 93,
    WLAN_STATISTIC = 94,
    MOST_ECL = 95,
    GLOBAL_MARKER = 96,
    AFDX_FRAME = 97,
    AFDX_STATISTIC = 98,
    KLINE_STATUSEVENT = 99,
    CAN_FD_MESSAGE = 100,
    CAN_FD_MESSAGE_64 = 101,
    ETHERNET_RX_ERROR = 102,
    ETHERNET_STATUS = 103,
    CAN_FD_ERROR_64 = 104,
    LIN_SHORT_OR_SLOW_RESPONSE2 = 105,
    AFDX_STATUS = 106,
    AFDX_BUS_STATISTIC = 107,
    reserved_4 = 108,
    AFDX_ERROR_EVENT = 109,
    A429_ERROR = 110,
    A429_STATUS = 111,
    A429_BUS_STATISTIC = 112,
    A429_MESSAGE = 113,
    ETHERNET_STATISTIC = 114,
    reserved_5 = 115,
    reserved_6 = 116,
    reserved_7 = 117,
    TEST_STRUCTURE = 118,
    DIAG_REQUEST_INTERPRETATION = 119,
    ETHERNET_FRAME_EX = 120,
    ETHERNET_FRAME_FORWARDED = 121,
    ETHERNET_ERROR_EX = 122,
    ETHERNET_ERROR_FORWARDED = 123,
    FUNCTION_BUS = 124,
    DATA_LOST_BEGIN = 125,
    DATA_LOST_END = 126,
    WATER_MARK_EVENT = 127,
    TRIGGER_CONDITION = 128
};


enum class AppId_e : uint8_t
{
    UNKNOWN = 0,
    CANALYZER = 1,
    CANOE = 2,
    CANSTRESS = 3,
    CANLOG = 4,
    CANAPE = 5,
    CANCASEXLLOG = 6,
    VLCONFIG = 7,
    PORSCHELOGGER = 200
};


// For DriverOverrun.
enum class BusType : uint32_t
{
    CAN = 1,
    LIN = 5,
    MOST = 6,
    FLEXRAY = 7,
    J1708 = 9,
    ETHERNET = 10,
    WLAN = 13,
    AFDX = 14
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
    uint32_t FileSign {0};
    uint32_t StatSize {0};
    AppId_e AppId {0};
    uint8_t AppMaj {0};
    uint8_t AppMin {0};
    uint8_t AppBuild {0};
    uint8_t ApiMaj {0};
    uint8_t ApiMin {0};
    uint8_t ApiBuild {0};
    uint8_t ApiPatch {0};
    uint64_t fileSize {0};
    uint64_t uncompressedSize {0};
    uint32_t objCount {0};
    uint32_t objRead {0};
    sysTime_t meas_start_time {0, 0, 0, 0, 0, 0, 0, 0};
    sysTime_t last_obj_time {0, 0, 0, 0, 0, 0, 0, 0};
    uint64_t fileSize_less115 {0};
};


struct BaseHeader
{
    uint32_t ObjSign {0}; // LOBJ
    uint16_t headerSize {0};
    uint16_t headerVer {0};
    uint32_t objSize {0};
    enum ObjectType_e objectType
    {
        ObjectType_e::UNKNOWN
    }; // uint32_t
};


enum class ObjectFlags_e : uint32_t
{
    TimeTenMics = 0x00000001,
    TimeNano = 0x00000002
};


enum class timeStampStatus_e : uint8_t
{
    original = 0x01,
    SwGen = 0x02,
    User = 0x10
};


struct ObjectHeader
{
    ObjectFlags_e objectFlags {};
    uint16_t clientIndex {0};
    uint16_t objectVersion {0};
    uint64_t objectTimeStamp {0};
};


struct ObjectHeader2
{
    ObjectFlags_e objectFlags {0};
    timeStampStatus_e timeStampStatus {0};
    uint8_t reservObjHeader {0};
    uint16_t ObjectHeaderVersion {0};
    uint64_t ObjectTimeStamp {0};
    uint64_t originalObjectTimeStamp {0};
};


enum class compressionMethod_e : int16_t
{
    uncompressed = 0x00,
    zlib = 0x02,
};


struct LogContainer
{
    compressionMethod_e compressionMethod {0}; // int16_t
    uint16_t reserv1 {0};
    uint32_t reserv2 {0};
    uint32_t unCompressedFileSize {0};
    uint32_t reserv3 {0};
};


// CAN_MSG_DIR	Direction	Sent (TX) or Received (RX).
//  Extract direction (lower 4 bits)
constexpr auto CAN_MSG_DIR(uint8_t f) -> uint8_t
{
    return f & 0x0FU;
}

// CAN_MSG_RTR	Remote Transmission Request	Normal (0) or Remote (1).
//  Extract Remote Transmission Request (RTR) (bit 7)
constexpr auto CAN_MSG_RTR(uint8_t f) -> uint8_t
{
    return (f & 0x80U) >> 7U;
}

// CAN_MSG_WU	Wake-Up Message	Message causing wake-up.
//  Extract Wake-Up (WU) flag (bit 6)
constexpr auto CAN_MSG_WU(uint8_t f) -> uint8_t
{
    return (f & 0x40U) >> 6U;
}

// CAN_MSG_NERR	Network Error	Error frame detected.
//  Extract Network Error (NERR) flag (bit 5)
constexpr auto CAN_MSG_NERR(uint8_t f) -> uint8_t
{
    return (f & 0x20U) >> 5U;
}

// CAN_MSG_FLAGS	General Flags	Additional message information.
//  Combine direction and RTR into flags
constexpr auto CAN_MSG_FLAGS(uint8_t dir, uint8_t rtr) -> uint8_t
{
    return ((rtr & 0x01U) << 7U) | (dir & 0x0FU);
}

// CAN_MSG_FLAGS_EXT	Extended Identifier	Standard (0) or Extended (1).
//  Combine direction, RTR, WU, and NERR into extended flags
constexpr auto CAN_MSG_FLAGS_EXT(uint8_t dir, uint8_t rtr, uint8_t wu, uint8_t nerr) -> uint8_t
{
    return ((rtr & 0x01U) << 7U) | ((wu & 0x01U) << 6U) | ((nerr & 0x01U) << 5U) | (dir & 0x0FU);
}

// CAN_FD_MSG_EDL	CAN FD Mode	Indicates FD protocol.
//  Extract CAN FD Extended Data Length (EDL) flag (bit 0)
constexpr auto CAN_FD_MSG_EDL(uint8_t f) -> uint8_t
{
    return f & 0x01U;
}

// CAN_FD_MSG_BRS	Bit Rate Switching	Higher bit rate during data phase.
//  Extract CAN FD Bit Rate Switch (BRS) flag (bit 1)
constexpr auto CAN_FD_MSG_BRS(uint8_t f) -> uint8_t
{
    return (f & 0x02U) >> 1U;
}

// CAN_FD_MSG_ESI	Error State Indicator	Active (0) or Passive (1).
//  Extract CAN FD Error State Indicator (ESI) flag (bit 2)
constexpr auto CAN_FD_MSG_ESI(uint8_t f) -> uint8_t
{
    return (f & 0x04U) >> 2U;
}


struct CanMessage
{
    uint16_t channel {0};
    uint8_t flags {0};
    uint8_t dlc {0};
    uint32_t id {0};
    std::array<uint8_t, 8> data {0, 0, 0, 0, 0, 0, 0, 0};
};


struct CanMessage_obh
{
    ObjectHeader obh;
    uint16_t channel {0};
    uint8_t flags {0};
    uint8_t dlc {0};
    uint32_t id {0};
    std::array<uint8_t, 8> data {0, 0, 0, 0, 0, 0, 0, 0};
};


struct CanError
{
    uint16_t channel {0};
    uint16_t length {0};
    uint32_t reservedCanErrorFrame {0};
};


struct CanError_obh
{
    ObjectHeader obh;
    uint16_t channel {0};
    uint16_t length {0};
    uint32_t reservedCanErrorFrame {0};
};


struct CanError_short
{
    uint16_t channel {0};
    uint16_t length {0};
};


struct CanError_short_obh
{
    ObjectHeader obh;
    uint16_t channel {0};
    uint16_t length {0};
};


struct CanOverload
{
    uint16_t channel {0};
    uint16_t reservedCanOverloadFrame1 {0};
    uint32_t reservedCanOverloadFrame2 {0}; // Corrected //??
};


struct CanOverload_short
{
    uint16_t channel {0};
    uint16_t reservedCanOverloadFrame1 {0};
};


struct CanOverload_short_obh
{
    ObjectHeader obh;
    uint16_t channel {0};
    uint16_t reservedCanOverloadFrame1 {0};
};


struct CanMessage2
{
    uint16_t channel {0};
    uint8_t flags {0};
    uint8_t dlc {0};
    uint32_t id {0};
    std::array<uint8_t, 8> data {0, 0, 0, 0, 0, 0, 0, 0};
    uint32_t frameLength {0};
    uint8_t bitCount {0};
    uint8_t reservedCanMessage1 {0};
    uint16_t reservedCanMessage2 {0};
};


struct CanMessage2_obh
{
    ObjectHeader obh;
    uint16_t channel {0};
    uint8_t flags {0};
    uint8_t dlc {0};
    uint32_t id {0};
    std::array<uint8_t, 8> data {0, 0, 0, 0, 0, 0, 0, 0};
    uint32_t frameLength {0};
    uint8_t bitCount {0};
    uint8_t reservedCanMessage1 {0};
    uint16_t reservedCanMessage2 {0};
};

enum class AppTriggerFlags : uint16_t
{
    BL_TRIGGER_FLAG_SINGLE_TRIGGER = 0x00000000, /* single trigger type */
    BL_TRIGGER_FLAG_LOGGING_START = 0x00000001,  /* start of logging trigger type */
    BL_TRIGGER_FLAG_LOGGING_STOP = 0x00000002    /* stop of logging trigger type */
};


struct AppTrigger
{
    uint64_t preTriggerTime {0};
    uint64_t postTriggerTime {0};
    uint16_t channel {0};
    AppTriggerFlags flags {0};
    uint32_t appSpecific2 {0};
};


struct AppText
{
    uint32_t mSource {0};
    uint32_t reserved {0};
    uint32_t mTextLength {0};
    uint32_t reserved2 {0}; // extra field not present in reference documentation.
    char *mText {nullptr};
};


struct AppText_obh
{
    ObjectHeader obh;
    uint32_t mSource {0};
    uint32_t reserved {0};
    uint32_t mTextLength {0};
    uint32_t reserved2 {0}; // extra field not present in reference documentation.
    // string that is mTextLength
};


struct CANErrorFrameExt // CAN_DRIVER_ERROR_EXT
{
    uint16_t Channel {0}; /* application channel */
    uint16_t Length {0};  /* CAN error frame length */
    uint32_t Flags {0};   /* extended CAN error frame flags */
    uint8_t ECC {0};      /* error control code */
    uint8_t Position {0}; /* error position */
    uint8_t DLC {0};      /* lower 4 bits: DLC from CAN-Core. Upper 4 bits: reserved */
    uint8_t Reserved1 {0};
    uint32_t FrameLengthInNS {0}; /* frame length in ns */
    uint32_t ID {0};              /* frame ID from CAN-Core */
    uint16_t FlagsExt {0};        /* extended error flags */
    uint16_t Reserved2 {0};
    std::array<uint8_t, 8> Data {0, 0, 0, 0, 0, 0, 0, 0}; /* Payload, only for CAN-Core */
};


struct reserved_5
{
    std::array<uint32_t, 6> data {0, 0, 0, 0, 0, 0};
};


struct CANDriverStatistic
{
    uint16_t mChannel {0};              /* application channel */
    uint16_t mBusLoad {0};              /* CAN bus load */
    uint32_t mStandardDataFrames {0};   /* standard CAN id data frames */
    uint32_t mExtendedDataFrames {0};   /* extended CAN id data frames */
    uint32_t mStandardRemoteFrames {0}; /* standard CAN id remote frames */
    uint32_t mExtendedRemoteFrames {0}; /* extended CAN id remote frames */
    uint32_t mErrorFrames {0};          /* CAN error frames */
    uint32_t mOverloadFrames {0};       /* CAN overload frames */
};

#pragma pack()


// Application helper structs.
enum class ObjectHeaders_e
{
    NONE,
    ONLY_HEADER_BASE,
    BASE_AND_HEADER,
    BASE_AND_HEADER2
};


struct ObjectHeaderCarry
{
    ObjectHeaders_e oh_enum {};
    struct BaseHeader ohb;
    struct ObjectHeader oh;
    struct ObjectHeader2 oh2;
};


} // namespace lblf

#endif
