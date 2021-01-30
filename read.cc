#include <iostream>
#include <fstream>
#include <array>
#include <iomanip>

//hexdump -v -C -n 512 truck02.blf

#include "blf_structs.hh"

const int32_t FileSignature = 0x47474F4C;   //LOGG
const int32_t ObjectSignature = 0x4A424F4C; //LOBJ

std::string print(ObjectType ot)
{
    switch (ot)
        {
        case ObjectType::UNKNOWN:
            return "UNKNOWN";
        case ObjectType::CAN_MESSAGE:
            return "CAN_MESSAGE";
        case ObjectType::CAN_ERROR:
            return "CAN_ERROR";
        case ObjectType::CAN_OVERLOAD:
            return "CAN_OVERLOAD";
        case ObjectType::APP_TRIGGER:
            return "APP_TRIGGER";
        case ObjectType::ENV_INTEGER:
            return "ENV_INTEGER";
        case ObjectType::ENV_DOUBLE:
            return "ENV_DOUBLE";
        case ObjectType::ENV_STRING:
            return "ENV_STRING";
        case ObjectType::ENV_DATA:
            return "ENV_DATA";
        case ObjectType::LOG_CONTAINER:
            return "LOG_CONTAINER";
        case ObjectType::LIN_MESSAGE:
            return "LIN_MESSAGE";
        case ObjectType::LIN_CRC_ERROR:
            return "LIN_CRC_ERROR";
        case ObjectType::LIN_DLC_INFO:
            return "LIN_DLC_INFO";
        case ObjectType::LIN_RCV_ERROR:
            return "LIN_RCV_ERROR";
        case ObjectType::LIN_SND_ERROR:
            return "LIN_SND_ERROR";
        case ObjectType::LIN_SLV_TIMEOUT:
            return "LIN_SLV_TIMEOUT";
        case ObjectType::LIN_SCHED_MODCH:
            return "LIN_SCHED_MODCH";
        case ObjectType::LIN_SYN_ERROR:
            return "LIN_SYN_ERROR";
        case ObjectType::LIN_BAUDRATE:
            return "LIN_BAUDRATE";
        case ObjectType::LIN_SLEEP:
            return "LIN_SLEEP";
        case ObjectType::LIN_WAKEUP:
            return "LIN_WAKEUP";
        case ObjectType::MOST_SPY:
            return "MOST_SPY";
        case ObjectType::MOST_CTRL:
            return "MOST_CTRL";
        case ObjectType::MOST_LIGHTLOCK:
            return "MOST_LIGHTLOCK";
        case ObjectType::MOST_STATISTIC:
            return "MOST_STATISTIC";
        case ObjectType::reserved_1:
            return "reserved_1";
        case ObjectType::reserved_2:
            return "reserved_2";
        case ObjectType::reserved_3:
            return "reserved_3";
        case ObjectType::FLEXRAY_DATA:
            return "FLEXRAY_DATA";
        case ObjectType::FLEXRAY_SYNC:
            return "FLEXRAY_SYNC";
        case ObjectType::CAN_DRIVER_ERROR:
            return "CAN_DRIVER_ERROR";
        case ObjectType::MOST_PKT:
            return "MOST_PKT";
        case ObjectType::MOST_PKT2:
            return "MOST_PKT2";
        case ObjectType::MOST_HWMODE:
            return "MOST_HWMODE";
        case ObjectType::MOST_REG:
            return "MOST_REG";
        case ObjectType::MOST_GENREG:
            return "MOST_GENREG";
        case ObjectType::MOST_NETSTATE:
            return "MOST_NETSTATE";
        case ObjectType::MOST_DATALOST:
            return "MOST_DATALOST";
        case ObjectType::MOST_TRIGGER:
            return "MOST_TRIGGER";
        case ObjectType::FLEXRAY_CYCLE:
            return "FLEXRAY_CYCLE";
        case ObjectType::FLEXRAY_MESSAGE:
            return "FLEXRAY_MESSAGE";
        case ObjectType::LIN_CHECKSUM_INFO:
            return "LIN_CHECKSUM_INFO";
        case ObjectType::LIN_SPIKE_EVENT:
            return "LIN_SPIKE_EVENT";
        case ObjectType::CAN_DRIVER_SYNC:
            return "CAN_DRIVER_SYNC";
        case ObjectType::FLEXRAY_STATUS:
            return "FLEXRAY_STATUS";
        case ObjectType::GPS_EVENT:
            return "GPS_EVENT";
        case ObjectType::FR_ERROR:
            return "FR_ERROR";
        case ObjectType::FR_STATUS:
            return "FR_STATUS";
        case ObjectType::FR_STARTCYCLE:
            return "FR_STARTCYCLE";
        case ObjectType::FR_RCVMESSAGE:
            return "FR_RCVMESSAGE";
        case ObjectType::REALTIMECLOCK:
            return "REALTIMECLOCK";
        case ObjectType::AVAILABLE2:
            return "AVAILABLE2";
        case ObjectType::AVAILABLE3:
            return "AVAILABLE3";
        case ObjectType::LIN_STATISTIC:
            return "LIN_STATISTIC";
        case ObjectType::J1708_MESSAGE:
            return "J1708_MESSAGE";
        case ObjectType::J1708_VIRTUAL_MSG:
            return "J1708_VIRTUAL_MSG";
        case ObjectType::LIN_MESSAGE2:
            return "LIN_MESSAGE2";
        case ObjectType::LIN_SND_ERROR2:
            return "LIN_SND_ERROR2";
        case ObjectType::LIN_SYN_ERROR2:
            return "LIN_SYN_ERROR2";
        case ObjectType::LIN_CRC_ERROR2:
            return "LIN_CRC_ERROR2";
        case ObjectType::LIN_RCV_ERROR2:
            return "LIN_RCV_ERROR2";
        case ObjectType::LIN_WAKEUP2:
            return "LIN_WAKEUP2";
        case ObjectType::LIN_SPIKE_EVENT2:
            return "LIN_SPIKE_EVENT2";
        case ObjectType::LIN_LONG_DOM_SIG:
            return "LIN_LONG_DOM_SIG";
        case ObjectType::APP_TEXT:
            return "APP_TEXT";
        case ObjectType::FR_RCVMESSAGE_EX:
            return "FR_RCVMESSAGE_EX";
        case ObjectType::MOST_STATISTICEX:
            return "MOST_STATISTICEX";
        case ObjectType::MOST_TXLIGHT:
            return "MOST_TXLIGHT";
        case ObjectType::MOST_ALLOCTAB:
            return "MOST_ALLOCTAB";
        case ObjectType::MOST_STRESS:
            return "MOST_STRESS";
        case ObjectType::ETHERNET_FRAME:
            return "ETHERNET_FRAME";
        case ObjectType::SYS_VARIABLE:
            return "SYS_VARIABLE";
        case ObjectType::CAN_ERROR_EXT:
            return "CAN_ERROR_EXT";
        case ObjectType::CAN_DRIVER_ERROR_EXT:
            return "CAN_DRIVER_ERROR_EXT";
        case ObjectType::LIN_LONG_DOM_SIG2:
            return "LIN_LONG_DOM_SIG2";
        case ObjectType::MOST_150_MESSAGE:
            return "MOST_150_MESSAGE";
        case ObjectType::MOST_150_PKT:
            return "MOST_150_PKT";
        case ObjectType::MOST_ETHERNET_PKT:
            return "MOST_ETHERNET_PKT";
        case ObjectType::MOST_150_MESSAGE_FRAGMENT:
            return "MOST_150_MESSAGE_FRAGMENT";
        case ObjectType::MOST_150_PKT_FRAGMENT:
            return "MOST_150_PKT_FRAGMENT";
        case ObjectType::MOST_ETHERNET_PKT_FRAGMENT:
            return "MOST_ETHERNET_PKT_FRAGMENT";
        case ObjectType::MOST_SYSTEM_EVENT:
            return "MOST_SYSTEM_EVENT";
        case ObjectType::MOST_150_ALLOCTAB:
            return "MOST_150_ALLOCTAB";
        case ObjectType::MOST_50_MESSAGE:
            return "MOST_50_MESSAGE";
        case ObjectType::MOST_50_PKT:
            return "MOST_50_PKT";
        case ObjectType::CAN_MESSAGE2:
            return "CAN_MESSAGE2";
        case ObjectType::LIN_UNEXPECTED_WAKEUP:
            return "LIN_UNEXPECTED_WAKEUP";
        case ObjectType::LIN_SHORT_OR_SLOW_RESPONSE:
            return "LIN_SHORT_OR_SLOW_RESPONSE";
        case ObjectType::LIN_DISTURBANCE_EVENT:
            return "LIN_DISTURBANCE_EVENT";
        case ObjectType::SERIAL_EVENT:
            return "SERIAL_EVENT";
        case ObjectType::OVERRUN_ERROR:
            return "OVERRUN_ERROR";
        case ObjectType::EVENT_COMMENT:
            return "EVENT_COMMENT";
        case ObjectType::WLAN_FRAME:
            return "WLAN_FRAME";
        case ObjectType::WLAN_STATISTIC:
            return "WLAN_STATISTIC";
        case ObjectType::MOST_ECL:
            return "MOST_ECL";
        case ObjectType::GLOBAL_MARKER:
            return "GLOBAL_MARKER";
        case ObjectType::AFDX_FRAME:
            return "AFDX_FRAME";
        case ObjectType::AFDX_STATISTIC:
            return "AFDX_STATISTIC";
        case ObjectType::KLINE_STATUSEVENT:
            return "KLINE_STATUSEVENT";
        case ObjectType::CAN_FD_MESSAGE:
            return "CAN_FD_MESSAGE";
        case ObjectType::CAN_FD_MESSAGE_64:
            return "CAN_FD_MESSAGE_64";
        case ObjectType::ETHERNET_RX_ERROR:
            return "ETHERNET_RX_ERROR";
        case ObjectType::ETHERNET_STATUS:
            return "ETHERNET_STATUS";
        case ObjectType::CAN_FD_ERROR_64:
            return "CAN_FD_ERROR_64";
        case ObjectType::LIN_SHORT_OR_SLOW_RESPONSE2:
            return "LIN_SHORT_OR_SLOW_RESPONSE2";
        case ObjectType::AFDX_STATUS:
            return "AFDX_STATUS";
        case ObjectType::AFDX_BUS_STATISTIC:
            return "AFDX_BUS_STATISTIC";
        case ObjectType::reserved_4:
            return "reserved_4";
        case ObjectType::AFDX_ERROR_EVENT:
            return "AFDX_ERROR_EVENT";
        case ObjectType::A429_ERROR:
            return "A429_ERROR";
        case ObjectType::A429_STATUS:
            return "A429_STATUS";
        case ObjectType::A429_BUS_STATISTIC:
            return "A429_BUS_STATISTIC";
        case ObjectType::A429_MESSAGE:
            return "A429_MESSAGE";
        case ObjectType::ETHERNET_STATISTIC:
            return "ETHERNET_STATISTIC";
        case ObjectType::reserved_5:
            return "reserved_5";
        case ObjectType::reserved_6:
            return "reserved_6";
        case ObjectType::reserved_7:
            return "reserved_7";
        case ObjectType::TEST_STRUCTURE:
            return "TEST_STRUCTURE";
        case ObjectType::DIAG_REQUEST_INTERPRETATION:
            return "DIAG_REQUEST_INTERPRETATION";
        case ObjectType::ETHERNET_FRAME_EX:
            return "ETHERNET_FRAME_EX";
        case ObjectType::ETHERNET_FRAME_FORWARDED:
            return "ETHERNET_FRAME_FORWARDED";
        case ObjectType::ETHERNET_ERROR_EX:
            return "ETHERNET_ERROR_EX";
        case ObjectType::ETHERNET_ERROR_FORWARDED:
            return "ETHERNET_ERROR_FORWARDED";
        case ObjectType::FUNCTION_BUS:
            return "FUNCTION_BUS";
        case ObjectType::DATA_LOST_BEGIN:
            return "DATA_LOST_BEGIN";
        case ObjectType::DATA_LOST_END:
            return "DATA_LOST_END";
        case ObjectType::WATER_MARK_EVENT:
            return "WATER_MARK_EVENT";
        case ObjectType::TRIGGER_CONDITION:
            return "TRIGGER_CONDITION";
        }
    return "missing Object Type";
}

uint32_t fileLength(std::fstream &fs)
{
    fs.seekg(0, fs.end);
    uint32_t length = fs.tellg();
    fs.seekg(0, fs.beg);
    return length;
}

void print(std::ostream &s, const sysTime_t &ts)
{
    s << std::dec;
    s << "year : " << (int)ts.year;
    s << " month: " << (int)ts.month;
    s << " dayOfWeek : " << (int)ts.dayOfWeek;
    s << " day :" << (int)ts.day;
    s << " hour :" << (int)ts.hour;
    s << " minute :" << (int)ts.minute;
    s << " second :" << (int)ts.second;
    s << " milliseconds :" << (int)ts.milliseconds;
    s << '\n';
}

bool read(std::fstream &fs, fileStatistics &os)
{
    fs.read(reinterpret_cast<char *>(&os.FileSign), sizeof(os.FileSign));
    if (os.FileSign != FileSignature)
        {
            return false;
        }

    fs.read(reinterpret_cast<char *>(&os.StatSize), sizeof(os.StatSize));
    fs.read(reinterpret_cast<char *>(&os.AppId), sizeof(os.AppId));
    fs.read(reinterpret_cast<char *>(&os.AppMaj), sizeof(os.AppMaj));
    fs.read(reinterpret_cast<char *>(&os.AppMin), sizeof(os.AppMin));
    fs.read(reinterpret_cast<char *>(&os.AppBuild), sizeof(os.AppBuild));
    fs.read(reinterpret_cast<char *>(&os.ApiMaj), sizeof(os.ApiMaj));
    fs.read(reinterpret_cast<char *>(&os.ApiMin), sizeof(os.ApiMin));
    fs.read(reinterpret_cast<char *>(&os.ApiBuild), sizeof(os.ApiBuild));
    fs.read(reinterpret_cast<char *>(&os.ApiPatch), sizeof(os.ApiPatch));
    fs.read(reinterpret_cast<char *>(&os.fileSize), sizeof(os.fileSize));
    fs.read(reinterpret_cast<char *>(&os.uncompressedSize), sizeof(os.uncompressedSize));
    fs.read(reinterpret_cast<char *>(&os.objCount), sizeof(os.objCount));
    fs.read(reinterpret_cast<char *>(&os.objRead), sizeof(os.objRead));
    fs.read(reinterpret_cast<char *>(&os.meas_start_time), sizeof(os.meas_start_time));
    fs.read(reinterpret_cast<char *>(&os.last_obj_time), sizeof(os.last_obj_time));
    fs.read(reinterpret_cast<char *>(&os.fileSize_less115), sizeof(os.fileSize_less115));
    auto offset = os.StatSize - sizeof(fileStatistics);
    fs.seekg(offset, std::ios_base::cur);
    return true;
}

void print(std::ostream &s, const fileStatistics &os)
{
    s << "os.FileSign           " << std::hex << static_cast<uint64_t>(os.FileSign) << '\n';
    s << "os.StatSize           " << static_cast<uint64_t>(os.StatSize);
    s << " dec: " << std::dec << static_cast<uint64_t>(os.StatSize) << '\n';
    s << "os.AppId              " << static_cast<uint64_t>(os.AppId) << '\n';
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
    s << "os.meas_start_time: ";
    print(s, os.meas_start_time);
    s << "os.last_obj_time: ";
    print(s, os.last_obj_time);
    s << "os.fileSize_less115   " << static_cast<uint64_t>(os.fileSize_less115) << '\n';
}

void print(std::ostream &s, const ObjectHeaderBase &ohb)
{
    s << "ObjectHeaderBase: ";
    s << "ObjSign " << std::hex << (int)ohb.ObjSign;
    s << std::dec;
    s << ", headerSize " << (int)ohb.headerSize;
    s << ", headerVer " << (int)ohb.headerVer;
    s << ", objSize " << (int)ohb.objSize;
    s << ", objectType " << print(ohb.objectType);
    s << '\n';
}

bool read(std::fstream &fs, ObjectHeaderBase &ohb)
{
    fs.read(reinterpret_cast<char *>(&ohb.ObjSign), sizeof(ohb.ObjSign));
    if (ohb.ObjSign != ObjectSignature)
        {
            return false;
        }
    fs.read(reinterpret_cast<char *>(&ohb.headerSize), sizeof(ohb.headerSize));
    fs.read(reinterpret_cast<char *>(&ohb.headerVer), sizeof(ohb.headerVer));
    fs.read(reinterpret_cast<char *>(&ohb.objSize), sizeof(ohb.objSize));
    fs.read(reinterpret_cast<char *>(&ohb.objectType), sizeof(ohb.objectType));
    return true;
}

void print(std::ostream &s, const ObjectHeader2 &oh2)
{
    s << "ObjectHeader2: ";
    s << std::dec;
    s << "objectFlags " << std::hex << (int)oh2.objectFlags;
    s << ", timeStampStatus " << (int)oh2.timeStampStatus;
    s << ", reservObjHeader " << (int)oh2.reservObjHeader;
    s << ", ObjectTimeStamp " << (int)oh2.ObjectTimeStamp;
    s << ", originalObjectTimeStamp " << (int)oh2.originalObjectTimeStamp;
    s << '\n';
}

bool read(std::fstream &fs, LogContainer &lc, const ObjectHeaderBase &ohb)
{
    fs.read(reinterpret_cast<char *>(&lc), sizeof(LogContainer));

    if (lc.compressionMethod == 2)
        {
            lc.unCompressedFileSize = ohb.objSize - sizeof(lc.compressionMethod) - sizeof(lc.reserv1) - sizeof(lc.reserv2) - sizeof(lc.unCompressedFileSize) - sizeof(lc.reserv3);
        }

    return true;
}

void print(std::ostream &s, const LogContainer &lc)
{
    s << "LogContainer : ";
    s << std::dec;
    s << "compressionMethod: " << std::hex << (int)lc.compressionMethod;
    s << ", uncompressedFileSize: " << std::dec << (int)lc.unCompressedFileSize;
    s << '\n';
}

void print(std::ostream &s, const ObjectHeader &oh)
{
    s << "ObjectHeader : ";
    s << std::dec;
    s << "objectFlag: " << (int)oh.clientIndex;
    s << ", objectVersion: " << std::dec << (int)oh.objectVersion;
    s << ", objectTimeStamp: " << std::dec << (int)oh.objectTimeStamp;
    s << '\n';
}

void print(std::ostream &s, const CanMessage &cm)
{
    s << "CanMessage : ";
    s << std::dec;
    s << "channel: " << (int)cm.channel;
    s << ", flags: " << std::dec << (int)cm.flags;
    s << ", dlc: " << std::dec << (int)cm.dlc;
    s << ", id: 0x" << std::hex << (int)cm.id;
    s << ", data: ";
    for (int n = 0; n < cm.dlc; n++)
        s << " " << std::hex << std::setfill('0') << std::setw(2) << (int)cm.data[n];
    s << '\n';
}

void print(std::ostream &s, const CanOverload &co)
{
    s << "CanOverload : ";
    s << std::dec;
    s << "channel: " << (int)co.channel;
    s << ", reservedCanOverloadFrame1: " << std::hex << (int)co.reservedCanOverloadFrame1;
    s << ", reservedCanOverloadFrame2: " << std::hex << (int)co.reservedCanOverloadFrame2;
    s << '\n';
}

void print(std::ostream &s, const CanMessage2 &cm2)
{
    s << "CanMessage2 : ";
    s << std::dec;
    s << "channel: " << (int)cm2.channel;
    s << ", flags: " << std::dec << (int)cm2.flags;
    s << ", dlc: " << std::dec << (int)cm2.dlc;
    s << ", id: 0x" << std::hex << (int)cm2.id;
    s << ", data: ";
    for (int n = 0; n < cm2.dlc; n++)
        s << " " << std::hex << std::setfill('0') << std::setw(2) << (int)cm2.data[n];
    s << '\n';
}

void print(std::ostream &s, const AppTrigger &at)
{
    s << "Apptrigger: ";
    s << std::dec;
    s << "preTriggerTime: " << (uint64_t)at.preTriggerTime;
    s << ", postTriggerTime : " << (uint64_t)at.postTriggerTime;
    s << ", channel: " << (uint64_t)at.channel;
    s << ", flags: " << (uint64_t)at.flags;
    s << ", appSpecific2: " << (uint64_t)at.appSpecific2;
    s << '\n';
}

template <typename type_data>
bool read_template(std::fstream &fs, type_data &data)
{
    fs.read(reinterpret_cast<char *>(&data), sizeof(type_data));
    return true;
}

void print(std::ostream &s, const CanErrorFrame &cfe)
{
    s << "CanErrorFrame: ";
    s << std::dec;
    s << ", channel : " << (uint64_t)cfe.channel;
    s << ", length : " << (uint64_t)cfe.length;
    s << ", reservedCanErrorFrame : " << (uint64_t)cfe.reservedCanErrorFrame;
    s << '\n';
}

void current_position(std::ostream &s, const uint64_t pos)
{
    s << "Current position: "
      << "0x" << std::hex << (uint64_t)pos << ", " << std::dec << (uint64_t)pos << '\n';
}

void handle_ObjectType(std::fstream &fs, const ObjectHeaderBase &ohb)
{
    switch (ohb.objectType)
        {
        case (ObjectType::CAN_MESSAGE): //read Can message;
        {
            struct ObjectHeader oh;
            (read_template(fs, oh));
            //	  print(std::cout, oh);
            struct CanMessage cm;
            if (read_template(fs, cm))
                print(std::cout, cm);
        }
        break;

        case (ObjectType::CAN_ERROR): //CanErrorFrame
        {
            print(std::cout, ohb);
            struct ObjectHeader oh;
            read_template(fs, oh);
            print(std::cout, oh);
            struct CanErrorFrame cef;
            (read_template(fs, cef));
            print(std::cout, cef);
        }
        break;

        case (ObjectType::CAN_OVERLOAD): //CanOverload
        {
            print(std::cout, ohb);
            struct ObjectHeader oh;
            read_template(fs, oh);
            print(std::cout, oh);
            struct CanOverload col;
            (read_template(fs, col));
            print(std::cout, col);
        }
        break;

        case (ObjectType::APP_TRIGGER): //Handle apptrigger
        {
            current_position(std::cout, fs.tellg());
            struct ObjectHeader oh;
            read_template(fs, oh);
            //print(std::cout, oh);
            struct AppTrigger ap;
            current_position(std::cout, fs.tellg());
            (read_template(fs, ap));
            //  print(std::cout, ap);
        }
        break;

        case (ObjectType::LOG_CONTAINER): //Get Logcontainer
        {
            struct LogContainer lc;
            if (read(fs, lc, ohb))
                print(std::cout, lc);
        }
        break;

        case (ObjectType::CAN_MESSAGE2):
        {
            struct ObjectHeader oh;
            (read_template(fs, oh));
            //	  print(std::cout, oh);
            struct CanMessage cm2;
            if (read_template(fs, cm2))
                print(std::cout, cm2);
        }
        break;

        default:
            std::cout << "New ObjectType: " << (int)ohb.objectType << '\n';
            exit(-1);
            //Unhandled message
            break;
        }
}

void run_handle(const char *const filename)
{
    std::cout << "Opening file: " << filename << '\n';
    std::fstream fs(filename, std::fstream::in | std::fstream::binary);

    if (fs)
        {
            struct fileStatistics os;
            read(fs, os);
            //            print(std::cout, os);
            current_position(std::cout, fs.tellg());
            int counter = 0;
            int jump_byte_counter = 0;
            struct ObjectHeaderBase ohb;
            while (!fs.eof())
                {
                    counter++;
                    bool result = read(fs, ohb);
                    if (!result)
                        {
                            jump_byte_counter++;
                            uint8_t dummy;
                            fs.read(reinterpret_cast<char *>(&dummy), sizeof(dummy));
                            std::cout << "jump\n";
                        }
                    else
                        {
                            std::cout << std::dec << (int)counter << ' ';
                            std::cout << ", size: " << ohb.objSize << ", type: " << print(static_cast<ObjectType>(ohb.objectType)) << ' ';
                            handle_ObjectType(fs, ohb);
                            //	    current_position(std::cout, fs.tellg());
                        }
                }
            std::cout << "End of file\n";
        }
    fs.close();
}

void go_through_header(const char *const filename)
{
    std::cout << "Opening file: " << filename << '\n';
    std::fstream fs(filename, std::fstream::in | std::fstream::binary);

    if (fs)
        {
            struct fileStatistics fileStat;
            if (read(fs, fileStat))
                {
                    print(std::cout, fileStat);
                }
            else
                {
                    std::cout << "Error file did not start with file statistics\n";
                    exit(-1);
                }

            current_position(std::cout, fs.tellg());

            struct ObjectHeaderBase ohb;
            if (read(fs, ohb))
                print(std::cout, ohb);
            else
                exit(-1);

            std::cout << ".";

            int counter = 0;
            int jump_byte_counter = 0;
            while (!fs.eof())
                {
                    counter++;
                    bool result = read(fs, ohb);

                    if (!result)
                        exit(-1);

                    uint32_t offset = ohb.objSize - sizeof(ObjectHeaderBase);
                    std::cout << "offset: " << std::dec << (int)offset << '\n';
                    fs.seekg(offset, std::ios_base::cur);
                    if (fs.eof())
                        std::cout << "End of file!!!!!!\n";

                    std::cout << std::dec << (int)counter << ' ';
                    std::cout << ", objSize: " << ohb.objSize << ", type: " << print(static_cast<ObjectType>(ohb.objectType)) << '\n';
                    current_position(std::cout, fs.tellg());
                }
            std::cout << "End of file\n";
        }
    fs.close();
}

void go_through_file(const char *const filename)
{
    std::cout << "Opening file: " << filename;
    std::fstream fs(filename, std::fstream::in | std::fstream::binary);
    if (fs.fail())
        {
            std::cout << " ";
            std::cout << "File open failed, Exiting program\n";
            exit(-1);
        }
    else
        {
            std::cout << " ** SUCCESS **\n";
        }

    if (fs)
        {
            struct fileStatistics fileStat;
            if (read(fs, fileStat))
                {
                    print(std::cout, fileStat);
                }
            else
                {
                    std::cout << "Error file is not a BLF file\n";
                    exit(-1);
                }
        }

    struct ObjectHeaderBase ohb;
    if (read(fs, ohb))
        print(std::cout, ohb);
    else
        exit(-1);

    fs.close();
}

int main()
{

    //  runfile("save.blf");
    //std::cout << "----------------------------------\n";
    //runfile("night.blf");

    std::cout << "----------------------------------\n";

    //     run_handle("truck02.blf");
    //    run_handle("b-874992_logfile008.blf");

    go_through_file("zuf016.blf");

    std::cout << "----------------------------------\n";
    //run_handle("truck03.blf");
}
