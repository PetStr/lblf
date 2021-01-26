#include <iostream>
#include <string>
#include <array>
#include <iomanip>


//hexdump -v -C -n 512 truck02.blf

#include "blf_structs.hh"




std::string print(ObjectType ot)
{
    switch (ot)
        {
        case ObjectType::UNKNOWN                     :
            return "UNKNOWN";
        case ObjectType::CAN_MESSAGE                 :
            return "CAN_MESSAGE";
        case ObjectType::CAN_ERROR                   :
            return "CAN_ERROR";
        case ObjectType::CAN_OVERLOAD                :
            return "CAN_OVERLOAD";
        case ObjectType::APP_TRIGGER                 :
            return "APP_TRIGGER";
        case ObjectType::ENV_INTEGER                 :
            return "ENV_INTEGER";
        case ObjectType::ENV_DOUBLE                  :
            return "ENV_DOUBLE";
        case ObjectType::ENV_STRING                  :
            return "ENV_STRING";
        case ObjectType::ENV_DATA                    :
            return "ENV_DATA";
        case ObjectType::LOG_CONTAINER               :
            return "LOG_CONTAINER";
        case ObjectType::LIN_MESSAGE                 :
            return "LIN_MESSAGE";
        case ObjectType::LIN_CRC_ERROR               :
            return "LIN_CRC_ERROR";
        case ObjectType::LIN_DLC_INFO                :
            return "LIN_DLC_INFO";
        case ObjectType::LIN_RCV_ERROR               :
            return "LIN_RCV_ERROR";
        case ObjectType::LIN_SND_ERROR               :
            return "LIN_SND_ERROR";
        case ObjectType::LIN_SLV_TIMEOUT             :
            return "LIN_SLV_TIMEOUT";
        case ObjectType::LIN_SCHED_MODCH             :
            return "LIN_SCHED_MODCH";
        case ObjectType::LIN_SYN_ERROR               :
            return "LIN_SYN_ERROR";
        case ObjectType::LIN_BAUDRATE                :
            return "LIN_BAUDRATE";
        case ObjectType::LIN_SLEEP                   :
            return "LIN_SLEEP";
        case ObjectType::LIN_WAKEUP                  :
            return "LIN_WAKEUP";
        case ObjectType::MOST_SPY                    :
            return "MOST_SPY";
        case ObjectType::MOST_CTRL                   :
            return "MOST_CTRL";
        case ObjectType::MOST_LIGHTLOCK              :
            return "MOST_LIGHTLOCK";
        case ObjectType::MOST_STATISTIC              :
            return "MOST_STATISTIC";
        case ObjectType::reserved_1                  :
            return "reserved_1";
        case ObjectType::reserved_2                  :
            return "reserved_2";
        case ObjectType::reserved_3                  :
            return "reserved_3";
        case ObjectType::FLEXRAY_DATA                :
            return "FLEXRAY_DATA";
        case ObjectType::FLEXRAY_SYNC                :
            return "FLEXRAY_SYNC";
        case ObjectType::CAN_DRIVER_ERROR            :
            return "CAN_DRIVER_ERROR";
        case ObjectType::MOST_PKT                    :
            return "MOST_PKT";
        case ObjectType::MOST_PKT2                   :
            return "MOST_PKT2";
        case ObjectType::MOST_HWMODE                 :
            return "MOST_HWMODE";
        case ObjectType::MOST_REG                    :
            return "MOST_REG";
        case ObjectType::MOST_GENREG                 :
            return "MOST_GENREG";
        case ObjectType::MOST_NETSTATE               :
            return "MOST_NETSTATE";
        case ObjectType::MOST_DATALOST               :
            return "MOST_DATALOST";
        case ObjectType::MOST_TRIGGER                :
            return "MOST_TRIGGER";
        case ObjectType::FLEXRAY_CYCLE               :
            return "FLEXRAY_CYCLE";
        case ObjectType::FLEXRAY_MESSAGE             :
            return "FLEXRAY_MESSAGE";
        case ObjectType::LIN_CHECKSUM_INFO           :
            return "LIN_CHECKSUM_INFO";
        case ObjectType::LIN_SPIKE_EVENT             :
            return "LIN_SPIKE_EVENT";
        case ObjectType::CAN_DRIVER_SYNC             :
            return "CAN_DRIVER_SYNC";
        case ObjectType::FLEXRAY_STATUS              :
            return "FLEXRAY_STATUS";
        case ObjectType::GPS_EVENT                   :
            return "GPS_EVENT";
        case ObjectType::FR_ERROR                    :
            return "FR_ERROR";
        case ObjectType::FR_STATUS                   :
            return "FR_STATUS";
        case ObjectType::FR_STARTCYCLE               :
            return "FR_STARTCYCLE";
        case ObjectType::FR_RCVMESSAGE               :
            return "FR_RCVMESSAGE";
        case ObjectType::REALTIMECLOCK               :
            return "REALTIMECLOCK";
        case ObjectType::AVAILABLE2                  :
            return "AVAILABLE2";
        case ObjectType::AVAILABLE3                  :
            return "AVAILABLE3";
        case ObjectType::LIN_STATISTIC               :
            return "LIN_STATISTIC";
        case ObjectType::J1708_MESSAGE               :
            return "J1708_MESSAGE";
        case ObjectType::J1708_VIRTUAL_MSG           :
            return "J1708_VIRTUAL_MSG";
        case ObjectType::LIN_MESSAGE2                :
            return "LIN_MESSAGE2";
        case ObjectType::LIN_SND_ERROR2              :
            return "LIN_SND_ERROR2";
        case ObjectType::LIN_SYN_ERROR2              :
            return "LIN_SYN_ERROR2";
        case ObjectType::LIN_CRC_ERROR2              :
            return "LIN_CRC_ERROR2";
        case ObjectType::LIN_RCV_ERROR2              :
            return "LIN_RCV_ERROR2";
        case ObjectType::LIN_WAKEUP2                 :
            return "LIN_WAKEUP2";
        case ObjectType::LIN_SPIKE_EVENT2            :
            return "LIN_SPIKE_EVENT2";
        case ObjectType::LIN_LONG_DOM_SIG            :
            return "LIN_LONG_DOM_SIG";
        case ObjectType::APP_TEXT                    :
            return "APP_TEXT";
        case ObjectType::FR_RCVMESSAGE_EX            :
            return "FR_RCVMESSAGE_EX";
        case ObjectType::MOST_STATISTICEX            :
            return "MOST_STATISTICEX";
        case ObjectType::MOST_TXLIGHT                :
            return "MOST_TXLIGHT";
        case ObjectType::MOST_ALLOCTAB               :
            return "MOST_ALLOCTAB";
        case ObjectType::MOST_STRESS                 :
            return "MOST_STRESS";
        case ObjectType::ETHERNET_FRAME              :
            return "ETHERNET_FRAME";
        case ObjectType::SYS_VARIABLE                :
            return "SYS_VARIABLE";
        case ObjectType::CAN_ERROR_EXT               :
            return "CAN_ERROR_EXT";
        case ObjectType::CAN_DRIVER_ERROR_EXT        :
            return "CAN_DRIVER_ERROR_EXT";
        case ObjectType::LIN_LONG_DOM_SIG2           :
            return "LIN_LONG_DOM_SIG2";
        case ObjectType::MOST_150_MESSAGE            :
            return "MOST_150_MESSAGE";
        case ObjectType::MOST_150_PKT                :
            return "MOST_150_PKT";
        case ObjectType::MOST_ETHERNET_PKT           :
            return "MOST_ETHERNET_PKT";
        case ObjectType::MOST_150_MESSAGE_FRAGMENT   :
            return "MOST_150_MESSAGE_FRAGMENT";
        case ObjectType::MOST_150_PKT_FRAGMENT       :
            return "MOST_150_PKT_FRAGMENT";
        case ObjectType::MOST_ETHERNET_PKT_FRAGMENT  :
            return "MOST_ETHERNET_PKT_FRAGMENT";
        case ObjectType::MOST_SYSTEM_EVENT           :
            return "MOST_SYSTEM_EVENT";
        case ObjectType::MOST_150_ALLOCTAB           :
            return "MOST_150_ALLOCTAB";
        case ObjectType::MOST_50_MESSAGE             :
            return "MOST_50_MESSAGE";
        case ObjectType::MOST_50_PKT                 :
            return "MOST_50_PKT";
        case ObjectType::CAN_MESSAGE2                :
            return "CAN_MESSAGE2";
        case ObjectType::LIN_UNEXPECTED_WAKEUP       :
            return "LIN_UNEXPECTED_WAKEUP";
        case ObjectType::LIN_SHORT_OR_SLOW_RESPONSE  :
            return "LIN_SHORT_OR_SLOW_RESPONSE";
        case ObjectType::LIN_DISTURBANCE_EVENT       :
            return "LIN_DISTURBANCE_EVENT";
        case ObjectType::SERIAL_EVENT                :
            return "SERIAL_EVENT";
        case ObjectType::OVERRUN_ERROR               :
            return "OVERRUN_ERROR";
        case ObjectType::EVENT_COMMENT               :
            return "EVENT_COMMENT";
        case ObjectType::WLAN_FRAME                  :
            return "WLAN_FRAME";
        case ObjectType::WLAN_STATISTIC              :
            return "WLAN_STATISTIC";
        case ObjectType::MOST_ECL                    :
            return "MOST_ECL";
        case ObjectType::GLOBAL_MARKER               :
            return "GLOBAL_MARKER";
        case ObjectType::AFDX_FRAME                  :
            return "AFDX_FRAME";
        case ObjectType::AFDX_STATISTIC              :
            return "AFDX_STATISTIC";
        case ObjectType::KLINE_STATUSEVENT           :
            return "KLINE_STATUSEVENT";
        case ObjectType::CAN_FD_MESSAGE              :
            return "CAN_FD_MESSAGE";
        case ObjectType::CAN_FD_MESSAGE_64           :
            return "CAN_FD_MESSAGE_64";
        case ObjectType::ETHERNET_RX_ERROR           :
            return "ETHERNET_RX_ERROR";
        case ObjectType::ETHERNET_STATUS             :
            return "ETHERNET_STATUS";
        case ObjectType::CAN_FD_ERROR_64             :
            return "CAN_FD_ERROR_64";
        case ObjectType::LIN_SHORT_OR_SLOW_RESPONSE2 :
            return "LIN_SHORT_OR_SLOW_RESPONSE2";
        case ObjectType::AFDX_STATUS                 :
            return "AFDX_STATUS";
        case ObjectType::AFDX_BUS_STATISTIC          :
            return "AFDX_BUS_STATISTIC";
        case ObjectType::reserved_4                  :
            return "reserved_4";
        case ObjectType::AFDX_ERROR_EVENT            :
            return "AFDX_ERROR_EVENT";
        case ObjectType::A429_ERROR                  :
            return "A429_ERROR";
        case ObjectType::A429_STATUS                 :
            return "A429_STATUS";
        case ObjectType::A429_BUS_STATISTIC          :
            return "A429_BUS_STATISTIC";
        case ObjectType::A429_MESSAGE                :
            return "A429_MESSAGE";
        case ObjectType::ETHERNET_STATISTIC          :
            return "ETHERNET_STATISTIC";
        case ObjectType::reserved_5                  :
            return "reserved_5";
        case ObjectType::reserved_6                  :
            return "reserved_6";
        case ObjectType::reserved_7                  :
            return "reserved_7";
        case ObjectType::TEST_STRUCTURE              :
            return "TEST_STRUCTURE";
        case ObjectType::DIAG_REQUEST_INTERPRETATION :
            return "DIAG_REQUEST_INTERPRETATION";
        case ObjectType::ETHERNET_FRAME_EX           :
            return "ETHERNET_FRAME_EX";
        case ObjectType::ETHERNET_FRAME_FORWARDED    :
            return "ETHERNET_FRAME_FORWARDED";
        case ObjectType::ETHERNET_ERROR_EX           :
            return "ETHERNET_ERROR_EX";
        case ObjectType::ETHERNET_ERROR_FORWARDED    :
            return "ETHERNET_ERROR_FORWARDED";
        case ObjectType::FUNCTION_BUS                :
            return "FUNCTION_BUS";
        case ObjectType::DATA_LOST_BEGIN             :
            return "DATA_LOST_BEGIN";
        case ObjectType::DATA_LOST_END               :
            return "DATA_LOST_END";
        case ObjectType::WATER_MARK_EVENT            :
            return "WATER_MARK_EVENT";
        case ObjectType::TRIGGER_CONDITION           :
            return "TRIGGER_CONDITION";
        }
    return "missing Object Type";
}


int main()
{

    std::cout << "Enter objecttype: ";

    uint32_t in;

    std::cin >> in;

    ObjectType local_objectType = static_cast <ObjectType> (in);

    std::cout << "Object type is: " << print(local_objectType) << '\n';


    return 0;
}