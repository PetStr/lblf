#include "print.hh"

namespace lblf
{

auto print(exit_codes ec) -> std::string
{
    switch (ec)
        {
        case exit_codes::EXITING_SUCCESS:
            return "EXITING_SUCCESS,";
        case exit_codes::UNABLE_TO_OPEN_FILE:
            return "UNABLE_TO_OPEN_FILE,";
        case exit_codes::NOT_A_VALID_BLF_FILE:
            return "NOT_A_VALID_BLF_FILE,";
        case exit_codes::CAN_MESSAGE_INVALID_LENGTH:
            return "CAN_MESSAGE_INVALID_LENGTH,";
        case exit_codes::LOGCONTAINER_WALK_THROUGH_FAIL:
            return "LOGCONTAINER_WALK_THROUGH_FAIL,";
        case exit_codes::UNHANDLED_OBJECT_TYPE:
            return "UNHANDLED_OBJECT_TYPE,";
        case exit_codes::UNABLE_TO_READ_OBJECT_HEADER_BASE:
            return "UNABLE_TO_READ_OBJECT_HEADER_BASE";
        }
    return "Missing exit_code";
}


auto print(ObjectType_e ot) -> std::string
{
    switch (ot)
        {
        case ObjectType_e::UNKNOWN:
            return "UNKNOWN";
        case ObjectType_e::CAN_MESSAGE:
            return "CAN_MESSAGE";
        case ObjectType_e::CAN_ERROR:
            return "CAN_ERROR";
        case ObjectType_e::CAN_OVERLOAD:
            return "CAN_OVERLOAD";
        case ObjectType_e::CAN_STATISTIC:
            return "CAN_STATISTIC";
        case ObjectType_e::APP_TRIGGER:
            return "APP_TRIGGER";
        case ObjectType_e::ENV_INTEGER:
            return "ENV_INTEGER";
        case ObjectType_e::ENV_DOUBLE:
            return "ENV_DOUBLE";
        case ObjectType_e::ENV_STRING:
            return "ENV_STRING";
        case ObjectType_e::ENV_DATA:
            return "ENV_DATA";
        case ObjectType_e::LOG_CONTAINER:
            return "LOG_CONTAINER";
        case ObjectType_e::LIN_MESSAGE:
            return "LIN_MESSAGE";
        case ObjectType_e::LIN_CRC_ERROR:
            return "LIN_CRC_ERROR";
        case ObjectType_e::LIN_DLC_INFO:
            return "LIN_DLC_INFO";
        case ObjectType_e::LIN_RCV_ERROR:
            return "LIN_RCV_ERROR";
        case ObjectType_e::LIN_SND_ERROR:
            return "LIN_SND_ERROR";
        case ObjectType_e::LIN_SLV_TIMEOUT:
            return "LIN_SLV_TIMEOUT";
        case ObjectType_e::LIN_SCHED_MODCH:
            return "LIN_SCHED_MODCH";
        case ObjectType_e::LIN_SYN_ERROR:
            return "LIN_SYN_ERROR";
        case ObjectType_e::LIN_BAUDRATE:
            return "LIN_BAUDRATE";
        case ObjectType_e::LIN_SLEEP:
            return "LIN_SLEEP";
        case ObjectType_e::LIN_WAKEUP:
            return "LIN_WAKEUP";
        case ObjectType_e::MOST_SPY:
            return "MOST_SPY";
        case ObjectType_e::MOST_CTRL:
            return "MOST_CTRL";
        case ObjectType_e::MOST_LIGHTLOCK:
            return "MOST_LIGHTLOCK";
        case ObjectType_e::MOST_STATISTIC:
            return "MOST_STATISTIC";
        case ObjectType_e::reserved_1:
            return "reserved_1";
        case ObjectType_e::reserved_2:
            return "reserved_2";
        case ObjectType_e::reserved_3:
            return "reserved_3";
        case ObjectType_e::FLEXRAY_DATA:
            return "FLEXRAY_DATA";
        case ObjectType_e::FLEXRAY_SYNC:
            return "FLEXRAY_SYNC";
        case ObjectType_e::CAN_DRIVER_ERROR:
            return "CAN_DRIVER_ERROR";
        case ObjectType_e::MOST_PKT:
            return "MOST_PKT";
        case ObjectType_e::MOST_PKT2:
            return "MOST_PKT2";
        case ObjectType_e::MOST_HWMODE:
            return "MOST_HWMODE";
        case ObjectType_e::MOST_REG:
            return "MOST_REG";
        case ObjectType_e::MOST_GENREG:
            return "MOST_GENREG";
        case ObjectType_e::MOST_NETSTATE:
            return "MOST_NETSTATE";
        case ObjectType_e::MOST_DATALOST:
            return "MOST_DATALOST";
        case ObjectType_e::MOST_TRIGGER:
            return "MOST_TRIGGER";
        case ObjectType_e::FLEXRAY_CYCLE:
            return "FLEXRAY_CYCLE";
        case ObjectType_e::FLEXRAY_MESSAGE:
            return "FLEXRAY_MESSAGE";
        case ObjectType_e::LIN_CHECKSUM_INFO:
            return "LIN_CHECKSUM_INFO";
        case ObjectType_e::LIN_SPIKE_EVENT:
            return "LIN_SPIKE_EVENT";
        case ObjectType_e::CAN_DRIVER_SYNC:
            return "CAN_DRIVER_SYNC";
        case ObjectType_e::FLEXRAY_STATUS:
            return "FLEXRAY_STATUS";
        case ObjectType_e::GPS_EVENT:
            return "GPS_EVENT";
        case ObjectType_e::FR_ERROR:
            return "FR_ERROR";
        case ObjectType_e::FR_STATUS:
            return "FR_STATUS";
        case ObjectType_e::FR_STARTCYCLE:
            return "FR_STARTCYCLE";
        case ObjectType_e::FR_RCVMESSAGE:
            return "FR_RCVMESSAGE";
        case ObjectType_e::REALTIMECLOCK:
            return "REALTIMECLOCK";
        case ObjectType_e::AVAILABLE2:
            return "AVAILABLE2";
        case ObjectType_e::AVAILABLE3:
            return "AVAILABLE3";
        case ObjectType_e::LIN_STATISTIC:
            return "LIN_STATISTIC";
        case ObjectType_e::J1708_MESSAGE:
            return "J1708_MESSAGE";
        case ObjectType_e::J1708_VIRTUAL_MSG:
            return "J1708_VIRTUAL_MSG";
        case ObjectType_e::LIN_MESSAGE2:
            return "LIN_MESSAGE2";
        case ObjectType_e::LIN_SND_ERROR2:
            return "LIN_SND_ERROR2";
        case ObjectType_e::LIN_SYN_ERROR2:
            return "LIN_SYN_ERROR2";
        case ObjectType_e::LIN_CRC_ERROR2:
            return "LIN_CRC_ERROR2";
        case ObjectType_e::LIN_RCV_ERROR2:
            return "LIN_RCV_ERROR2";
        case ObjectType_e::LIN_WAKEUP2:
            return "LIN_WAKEUP2";
        case ObjectType_e::LIN_SPIKE_EVENT2:
            return "LIN_SPIKE_EVENT2";
        case ObjectType_e::LIN_LONG_DOM_SIG:
            return "LIN_LONG_DOM_SIG";
        case ObjectType_e::APP_TEXT:
            return "APP_TEXT";
        case ObjectType_e::FR_RCVMESSAGE_EX:
            return "FR_RCVMESSAGE_EX";
        case ObjectType_e::MOST_STATISTICEX:
            return "MOST_STATISTICEX";
        case ObjectType_e::MOST_TXLIGHT:
            return "MOST_TXLIGHT";
        case ObjectType_e::MOST_ALLOCTAB:
            return "MOST_ALLOCTAB";
        case ObjectType_e::MOST_STRESS:
            return "MOST_STRESS";
        case ObjectType_e::ETHERNET_FRAME:
            return "ETHERNET_FRAME";
        case ObjectType_e::SYS_VARIABLE:
            return "SYS_VARIABLE";
        case ObjectType_e::CAN_ERROR_EXT:
            return "CAN_ERROR_EXT";
        case ObjectType_e::CAN_DRIVER_ERROR_EXT:
            return "CAN_DRIVER_ERROR_EXT";
        case ObjectType_e::LIN_LONG_DOM_SIG2:
            return "LIN_LONG_DOM_SIG2";
        case ObjectType_e::MOST_150_MESSAGE:
            return "MOST_150_MESSAGE";
        case ObjectType_e::MOST_150_PKT:
            return "MOST_150_PKT";
        case ObjectType_e::MOST_ETHERNET_PKT:
            return "MOST_ETHERNET_PKT";
        case ObjectType_e::MOST_150_MESSAGE_FRAGMENT:
            return "MOST_150_MESSAGE_FRAGMENT";
        case ObjectType_e::MOST_150_PKT_FRAGMENT:
            return "MOST_150_PKT_FRAGMENT";
        case ObjectType_e::MOST_ETHERNET_PKT_FRAGMENT:
            return "MOST_ETHERNET_PKT_FRAGMENT";
        case ObjectType_e::MOST_SYSTEM_EVENT:
            return "MOST_SYSTEM_EVENT";
        case ObjectType_e::MOST_150_ALLOCTAB:
            return "MOST_150_ALLOCTAB";
        case ObjectType_e::MOST_50_MESSAGE:
            return "MOST_50_MESSAGE";
        case ObjectType_e::MOST_50_PKT:
            return "MOST_50_PKT";
        case ObjectType_e::CAN_MESSAGE2:
            return "CAN_MESSAGE2";
        case ObjectType_e::LIN_UNEXPECTED_WAKEUP:
            return "LIN_UNEXPECTED_WAKEUP";
        case ObjectType_e::LIN_SHORT_OR_SLOW_RESPONSE:
            return "LIN_SHORT_OR_SLOW_RESPONSE";
        case ObjectType_e::LIN_DISTURBANCE_EVENT:
            return "LIN_DISTURBANCE_EVENT";
        case ObjectType_e::SERIAL_EVENT:
            return "SERIAL_EVENT";
        case ObjectType_e::OVERRUN_ERROR:
            return "OVERRUN_ERROR";
        case ObjectType_e::EVENT_COMMENT:
            return "EVENT_COMMENT";
        case ObjectType_e::WLAN_FRAME:
            return "WLAN_FRAME";
        case ObjectType_e::WLAN_STATISTIC:
            return "WLAN_STATISTIC";
        case ObjectType_e::MOST_ECL:
            return "MOST_ECL";
        case ObjectType_e::GLOBAL_MARKER:
            return "GLOBAL_MARKER";
        case ObjectType_e::AFDX_FRAME:
            return "AFDX_FRAME";
        case ObjectType_e::AFDX_STATISTIC:
            return "AFDX_STATISTIC";
        case ObjectType_e::KLINE_STATUSEVENT:
            return "KLINE_STATUSEVENT";
        case ObjectType_e::CAN_FD_MESSAGE:
            return "CAN_FD_MESSAGE";
        case ObjectType_e::CAN_FD_MESSAGE_64:
            return "CAN_FD_MESSAGE_64";
        case ObjectType_e::ETHERNET_RX_ERROR:
            return "ETHERNET_RX_ERROR";
        case ObjectType_e::ETHERNET_STATUS:
            return "ETHERNET_STATUS";
        case ObjectType_e::CAN_FD_ERROR_64:
            return "CAN_FD_ERROR_64";
        case ObjectType_e::LIN_SHORT_OR_SLOW_RESPONSE2:
            return "LIN_SHORT_OR_SLOW_RESPONSE2";
        case ObjectType_e::AFDX_STATUS:
            return "AFDX_STATUS";
        case ObjectType_e::AFDX_BUS_STATISTIC:
            return "AFDX_BUS_STATISTIC";
        case ObjectType_e::reserved_4:
            return "reserved_4";
        case ObjectType_e::AFDX_ERROR_EVENT:
            return "AFDX_ERROR_EVENT";
        case ObjectType_e::A429_ERROR:
            return "A429_ERROR";
        case ObjectType_e::A429_STATUS:
            return "A429_STATUS";
        case ObjectType_e::A429_BUS_STATISTIC:
            return "A429_BUS_STATISTIC";
        case ObjectType_e::A429_MESSAGE:
            return "A429_MESSAGE";
        case ObjectType_e::ETHERNET_STATISTIC:
            return "ETHERNET_STATISTIC";
        case ObjectType_e::reserved_5:
            return "reserved_5";
        case ObjectType_e::reserved_6:
            return "reserved_6";
        case ObjectType_e::reserved_7:
            return "reserved_7";
        case ObjectType_e::TEST_STRUCTURE:
            return "TEST_STRUCTURE";
        case ObjectType_e::DIAG_REQUEST_INTERPRETATION:
            return "DIAG_REQUEST_INTERPRETATION";
        case ObjectType_e::ETHERNET_FRAME_EX:
            return "ETHERNET_FRAME_EX";
        case ObjectType_e::ETHERNET_FRAME_FORWARDED:
            return "ETHERNET_FRAME_FORWARDED";
        case ObjectType_e::ETHERNET_ERROR_EX:
            return "ETHERNET_ERROR_EX";
        case ObjectType_e::ETHERNET_ERROR_FORWARDED:
            return "ETHERNET_ERROR_FORWARDED";
        case ObjectType_e::FUNCTION_BUS:
            return "FUNCTION_BUS";
        case ObjectType_e::DATA_LOST_BEGIN:
            return "DATA_LOST_BEGIN";
        case ObjectType_e::DATA_LOST_END:
            return "DATA_LOST_END";
        case ObjectType_e::WATER_MARK_EVENT:
            return "WATER_MARK_EVENT";
        case ObjectType_e::TRIGGER_CONDITION:
            return "TRIGGER_CONDITION";
        }
    return "missing Object Type";
}


auto print(AppId_e ai) -> std::string
{
    switch (ai)
        {
        case AppId_e::UNKNOWN:
            return "Unknown";
        case AppId_e::CANALYZER:
            return "CANALYZER";
        case AppId_e::CANOE:
            return "CANOE";
        case AppId_e::CANSTRESS:
            return "CANSTRESS";
        case AppId_e::CANLOG:
            return "CANLOG";
        case AppId_e::CANAPE:
            return "CANAPE";
        case AppId_e::CANCASEXLLOG:
            return "CANCASEXLLOG";
        case AppId_e::VLCONFIG:
            return "VLCONFIG";
        case AppId_e::PORSCHELOGGER:
            return "PORSCHELOGGER";
        }
    return "Undeclared AppId: ";
}


std::string print(compressionMethod_e cm)
{
    switch (cm)
        {
        case compressionMethod_e::uncompressed:
            return "Uncompressed";
        case compressionMethod_e::zlib:
            return "zlib";
        }
    return "Undeclared AppId: ";
}


auto print(ObjectFlags_e of) -> std::string
{
    switch (of)
        {
        case ObjectFlags_e::TimeTenMics:
            return "Time Ten Microseconds";
        case ObjectFlags_e::TimeNano:
            return "Time in Nanoseconds";
        }
    return "Unknown Timeflags";
}


auto print(timeStampStatus_e tss) -> std::string
{
    switch (tss)
        {
        case timeStampStatus_e::orginal:
            return "Orginal";
        case timeStampStatus_e::SwGen:
            return "Software Generated";
        case timeStampStatus_e::User:
            return "User defined";
        }
    return "Unknown time stamp status.";
}


void print(std::ostream &s, const sysTime_t &ts)
{
    s << std::dec;
    s << "year: " << (int) ts.year;
    s << " month: " << (int) ts.month;
    s << " dayOfWeek : " << (int) ts.dayOfWeek;
    s << " day :" << (int) ts.day;
    s << " hour :" << (int) ts.hour;
    s << " minute :" << (int) ts.minute;
    s << " second :" << (int) ts.second;
    s << " milliseconds :" << (int) ts.milliseconds;
    s << '\n';
}


void print(std::ostream &s, const fileStatistics &os)
{
    s << "os.FileSign           " << std::hex << static_cast<uint64_t>(os.FileSign) << '\n';
    s << "os.StatSize           " << static_cast<uint64_t>(os.StatSize);
    s << " dec: " << std::dec << static_cast<uint64_t>(os.StatSize) << '\n';
    s << "os.AppId              " << print(os.AppId);
    s << " " << static_cast<uint64_t>(os.AppId) << '\n';
    s << "os.AppMaj             " << static_cast<uint64_t>(os.AppMaj) << '\n';
    s << "os.AppMin             " << static_cast<uint64_t>(os.AppMin) << '\n';
    s << "os.AppBuild           " << static_cast<uint64_t>(os.AppBuild) << '\n';
    s << "os.ApiMaj             " << static_cast<uint64_t>(os.ApiMaj) << '\n';
    s << "os.ApiMin             " << static_cast<uint64_t>(os.ApiMin) << '\n';
    s << "os.ApiBuild           " << static_cast<uint64_t>(os.ApiBuild) << '\n';
    s << "os.ApiPatch           " << static_cast<uint64_t>(os.ApiPatch) << '\n';
    s << "os.fileSize           " << static_cast<uint64_t>(os.fileSize) << '\n';
    s << "os.uncompressedSize   " << static_cast<uint64_t>(os.uncompressedSize) << '\n';
    s << "os.objCount           " << static_cast<uint64_t>(os.objCount) << '\n';
    s << "os.objRead            " << static_cast<uint64_t>(os.objRead) << '\n';
    s << "os.meas_start_time:   ";
    print(s, os.meas_start_time);
    s << "os.last_obj_time:     ";
    print(s, os.last_obj_time);
    s << "os.fileSize_less115   " << static_cast<uint64_t>(os.fileSize_less115) << '\n';
}


void print(std::ostream &s, const BaseHeader &ohb)
{
    s << "BaseHeader ";
    // s << "ObjSign " << std::hex << (int)ohb.ObjSign;
    // s << std::dec;
    s << std::dec;
    s << " headerSize " << (int) ohb.headerSize;
    s << ", headerVer " << (int) ohb.headerVer;
    s << ", objSize " << (int) ohb.objSize;
    s << ", objectType# " << static_cast<int>(ohb.objectType);
    s << ", " << print(ohb.objectType);
    s << '\n';
}


void print(std::ostream &s, const ObjectHeader2 &oh2)
{
    s << "ObjectHeader2: ";
    s << std::dec;
    s << "objectFlags " << std::hex << (int) oh2.objectFlags;
    s << ", timeStampStatus " << (int) oh2.timeStampStatus;
    s << ", reservObjHeader " << (int) oh2.reservObjHeader;
    s << ", ObjectTimeStamp " << (int) oh2.ObjectTimeStamp;
    s << ", originalObjectTimeStamp " << (int) oh2.originalObjectTimeStamp;
    s << '\n';
}


void print(std::ostream &s, const ObjectHeader &oh)
{
    s << "ObjectHeader : ";
    s << std::dec;
    s << "objectFlag: " << (int) oh.clientIndex;
    s << ", objectVersion: " << std::dec << oh.objectVersion;
    s << ", objectTimeStamp: " << std::dec << oh.objectTimeStamp;
    s << '\n';
}


void print(std::ostream &s, const ObjectHeaderCarry &ohc)
{
    switch (ohc.oh_enum)
        {
        case ObjectHeaders_e::NONE:
            s << "No Header Carry defined\n";
            break;
        case ObjectHeaders_e::ONLY_HEADER_BASE:
            print(s, ohc.ohb);
            break;
        case ObjectHeaders_e::BASE_AND_HEADER:
            print(s, ohc.ohb);
            print(s, ohc.oh);
            break;
        case ObjectHeaders_e::BASE_AND_HEADER2:
            print(s, ohc.ohb);
            print(s, ohc.oh2);
            break;
        }
}


void print(std::ostream &s, const LogContainer &lc)
{
    s << "LogContainer : ";
    s << std::dec;
    s << "compressionMethod: " << print(lc.compressionMethod);
    s << ", uncompressedFileSize: " << std::dec << (int) lc.unCompressedFileSize;
    s << '\n';
}


void print(std::ostream &s, const CanMessage &cm)
{
    s << "CanMessage : ";
    s << std::dec;
    s << "channel: " << (int) cm.channel;
    s << ", flags: " << std::dec << (int) cm.flags;
    s << ", dlc: " << std::dec << (int) cm.dlc;
    auto dlc = cm.dlc;
    if (dlc > 8)
        dlc = 8;
    s << ", dlc: " << std::dec << (int) dlc;
    s << ", id: 0x" << std::hex << (int) cm.id;
    s << ", data: ";
    for (auto n = 0; n < dlc; n++)
        s << " " << std::hex << std::setfill('0') << std::setw(2) << (int) cm.data[n];
    s << '\n';
}


void print(std::ostream &s, const CanOverload &co)
{
    s << "CanOverload : ";
    s << std::dec;
    s << "channel: " << (int) co.channel;
    s << ", reservedCanOverloadFrame1: " << std::hex << (int) co.reservedCanOverloadFrame1;
    s << ", reservedCanOverloadFrame2: " << std::hex << (int) co.reservedCanOverloadFrame2;
    s << '\n';
}


void print(std::ostream &s, const CanOverload_short &co)
{
    s << "CanOverload : ";
    s << std::dec;
    s << "channel: " << (int) co.channel;
    s << ", reservedCanOverloadFrame1: " << std::hex << (int) co.reservedCanOverloadFrame1;
    s << '\n';
}


void print(std::ostream &s, const CanMessage2 &cm2)
{
    s << "CanMessage2 : ";
    s << std::dec;
    s << "channel: " << (int) cm2.channel;
    s << ", flags: " << std::dec << (int) cm2.flags;
    auto dlc = cm2.dlc;
    if (dlc > 8)
        dlc = 8;
    s << ", dlc: " << std::dec << dlc;
    s << ", dlc: " << std::dec << cm2.dlc;
    s << ", id: 0x" << std::hex << (int) cm2.id;
    s << ", data: ";
    for (auto d: cm2.data)
        s << " " << std::hex << std::setfill('0') << std::setw(2) << (int) d;
    s << '\n';
}


void print(std::ostream &s, const AppTrigger &at)
{
    s << "Apptrigger: ";
    s << std::dec;
    s << "preTriggerTime: " << (uint64_t) at.preTriggerTime;
    s << ", postTriggerTime : " << (uint64_t) at.postTriggerTime;
    s << ", channel: " << (uint64_t) at.channel;
    s << ", flags: " << (uint64_t) at.flags;
    s << ", appSpecific2: " << (uint64_t) at.appSpecific2;
    s << '\n';
}


void print(std::ostream &s, const AppText &at)
{
    s << "AppText: ";
    s << std::dec;
    s << "mSource: " << (uint64_t) at.mSource;
    s << ", mTextLength: " << (uint64_t) at.mTextLength;
    s << '\n';
}


void print(std::ostream &s, const reserved_5 &r)
{
    s << "Reserved_5: ";
    for (auto a: r.data)
        s << " 0x" << std::hex << a;
    s << '\n';
}


void print(std::ostream &s, const CanError &cfe)
{
    s << "CanError: ";
    s << std::dec;
    s << ", channel : " << (uint64_t) cfe.channel;
    s << ", length : " << (uint64_t) cfe.length;
    s << ", reservedCanErrorFrame : " << (uint64_t) cfe.reservedCanErrorFrame;
    s << '\n';
}


void print(std::ostream &s, const CanError_short &cfe)
{
    s << "CanError_short: ";
    s << std::dec;
    s << ", channel : " << (uint64_t) cfe.channel;
    s << ", length : " << (uint64_t) cfe.length;
    s << '\n';
}


void print(std::ostream &s, const CANErrorFrameExt &ce)
{
    s << "mChannel: " << static_cast<int>(ce.Channel);
    s << " mLength: " << (int) ce.Length;
    s << " mFlags: " << (int) ce.Flags;
    s << " mECC: " << (int) ce.ECC;
    s << " mPosition: " << (int) ce.Position;
    s << " mDLC: " << (int) ce.DLC << '\n';
    s << " mFrameLengthInNS: " << (int) ce.FrameLengthInNS;
    s << " mID: " << (int) ce.ID;
    s << " mFlagsExt: " << (int) ce.FlagsExt;
    s << " mReserved2: " << (int) ce.Reserved2;
    s << " mData:";
    for (auto n: ce.Data)
        s << " " << std::hex << std::setfill('0') << std::setw(2) << (int) n;
    s << '\n';
}


}