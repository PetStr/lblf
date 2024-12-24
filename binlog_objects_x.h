/*----------------------------------------------------------------------------
|
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ------------------------------------
| Sn           Michael Stephan           Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date         Ver  Author  Description
| ---------    ---  ------  --------------------------------------------------
| 01/04/02     1.0  Sn      Creation
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2002 by Vector Informatik GmbH.  All rights reserved.
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
|
| Object type IDs
|
-----------------------------------------------------------------------------*/

#include <array>
#include <cstdint>

#define BL_OBJ_SIGNATURE 0x4A424F4C /* object signature */

#define BL_OBJ_TYPE_UNKNOWN 0        /* unknown object */
#define BL_OBJ_TYPE_CAN_MESSAGE 1    /* CAN message object */
#define BL_OBJ_TYPE_CAN_ERROR 2      /* CAN error frame object */
#define BL_OBJ_TYPE_CAN_OVERLOAD 3   /* CAN overload frame object */
#define BL_OBJ_TYPE_CAN_STATISTIC 4  /* CAN driver statistics object */
#define BL_OBJ_TYPE_APP_TRIGGER 5    /* application trigger object */
#define BL_OBJ_TYPE_ENV_INTEGER 6    /* environment integer object */
#define BL_OBJ_TYPE_ENV_ double 7    /* environment  double object */
#define BL_OBJ_TYPE_ENV_STRING 8     /* environment string object */
#define BL_OBJ_TYPE_ENV_DATA 9       /* environment data object */
#define BL_OBJ_TYPE_LOG_CONTAINER 10 /* container object */

#define BL_OBJ_TYPE_LIN_MESSAGE 11     /* LIN message object */
#define BL_OBJ_TYPE_LIN_CRC_ERROR 12   /* LIN CRC error object */
#define BL_OBJ_TYPE_LIN_DLC_INFO 13    /* LIN DLC info object */
#define BL_OBJ_TYPE_LIN_RCV_ERROR 14   /* LIN receive error object */
#define BL_OBJ_TYPE_LIN_SND_ERROR 15   /* LIN send error object */
#define BL_OBJ_TYPE_LIN_SLV_TIMEOUT 16 /* LIN slave timeout object */
#define BL_OBJ_TYPE_LIN_SCHED_MODCH 17 /* LIN scheduler mode change object */
#define BL_OBJ_TYPE_LIN_SYN_ERROR 18   /* LIN sync error object */
#define BL_OBJ_TYPE_LIN_BAUDRATE 19    /* LIN baudrate event object */
#define BL_OBJ_TYPE_LIN_SLEEP 20       /* LIN sleep mode event object */
#define BL_OBJ_TYPE_LIN_WAKEUP 21      /* LIN wakeup event object */

#define BL_OBJ_TYPE_MOST_SPY 22       /* MOST spy message object */
#define BL_OBJ_TYPE_MOST_CTRL 23      /* MOST control message object */
#define BL_OBJ_TYPE_MOST_LIGHTLOCK 24 /* MOST light lock object */
#define BL_OBJ_TYPE_MOST_STATISTIC 25 /* MOST statistic object */

#define BL_OBJ_TYPE_reserved_1 26
#define BL_OBJ_TYPE_reserved_2 27
#define BL_OBJ_TYPE_reserved_3 28

#define BL_OBJ_TYPE_FLEXRAY_DATA 29 /* FLEXRAY data object */
#define BL_OBJ_TYPE_FLEXRAY_SYNC 30 /* FLEXRAY sync object */

#define BL_OBJ_TYPE_CAN_DRIVER_ERROR 31 /* CAN driver error object */

#define BL_OBJ_TYPE_MOST_PKT 32      /* MOST Packet */
#define BL_OBJ_TYPE_MOST_PKT2 33     /* MOST Packet including original timestamp */
#define BL_OBJ_TYPE_MOST_HWMODE 34   /* MOST hardware mode event */
#define BL_OBJ_TYPE_MOST_REG 35      /* MOST register data (various chips)*/
#define BL_OBJ_TYPE_MOST_GENREG 36   /* MOST register data (MOST register) */
#define BL_OBJ_TYPE_MOST_NETSTATE 37 /* MOST NetState event */
#define BL_OBJ_TYPE_MOST_DATALOST 38 /* MOST data lost */
#define BL_OBJ_TYPE_MOST_TRIGGER 39  /* MOST trigger */

#define BL_OBJ_TYPE_FLEXRAY_CYCLE 40   /* FLEXRAY V6 start cycle object */
#define BL_OBJ_TYPE_FLEXRAY_MESSAGE 41 /* FLEXRAY V6 message object */

#define BL_OBJ_TYPE_LIN_CHECKSUM_INFO 42 /* LIN checksum info event object */
#define BL_OBJ_TYPE_LIN_SPIKE_EVENT 43   /* LIN spike event object */

#define BL_OBJ_TYPE_CAN_DRIVER_SYNC 44 /* CAN driver hardware sync */

#define BL_OBJ_TYPE_FLEXRAY_STATUS 45 /* FLEXRAY status event object */

#define BL_OBJ_TYPE_GPS_EVENT 46 /* GPS event object */

#define BL_OBJ_TYPE_FR_ERROR 47      /* FLEXRAY error event object */
#define BL_OBJ_TYPE_FR_STATUS 48     /* FLEXRAY status event object */
#define BL_OBJ_TYPE_FR_STARTCYCLE 49 /* FLEXRAY start cycle event object */
#define BL_OBJ_TYPE_FR_RCVMESSAGE 50 /* FLEXRAY receive message event object */

#define BL_OBJ_TYPE_REALTIMECLOCK 51 /* Realtime clock object */
#define BL_OBJ_TYPE_AVAILABLE2 52    /* this object ID is available for the future */
#define BL_OBJ_TYPE_AVAILABLE3 53    /* this object ID is available for the future */

#define BL_OBJ_TYPE_LIN_STATISTIC 54 /* LIN statistic event object */

#define BL_OBJ_TYPE_J1708_MESSAGE 55     /* J1708 message object */
#define BL_OBJ_TYPE_J1708_VIRTUAL_MSG 56 /* J1708 message object with more than 21 datauint8_ts */

#define BL_OBJ_TYPE_LIN_MESSAGE2 57     /* LIN frame object - extended */
#define BL_OBJ_TYPE_LIN_SND_ERROR2 58   /* LIN transmission error object - extended */
#define BL_OBJ_TYPE_LIN_SYN_ERROR2 59   /* LIN sync error object - extended */
#define BL_OBJ_TYPE_LIN_CRC_ERROR2 60   /* LIN checksum error object - extended */
#define BL_OBJ_TYPE_LIN_RCV_ERROR2 61   /* LIN receive error object */
#define BL_OBJ_TYPE_LIN_WAKEUP2 62      /* LIN wakeup event object  - extended */
#define BL_OBJ_TYPE_LIN_SPIKE_EVENT2 63 /* LIN spike event object - extended */
#define BL_OBJ_TYPE_LIN_LONG_DOM_SIG 64 /* LIN uint32_t dominant signal object */

#define BL_OBJ_TYPE_APP_TEXT 65 /* text object */

#define BL_OBJ_TYPE_FR_RCVMESSAGE_EX 66 /* FLEXRAY receive message ex event object */

#define BL_OBJ_TYPE_MOST_STATISTICEX 67 /* MOST extended statistic event */
#define BL_OBJ_TYPE_MOST_TXLIGHT 68     /* MOST TxLight event */
#define BL_OBJ_TYPE_MOST_ALLOCTAB 69    /* MOST Allocation table event */
#define BL_OBJ_TYPE_MOST_STRESS 70      /* MOST Stress event */

#define BL_OBJ_TYPE_ETHERNET_FRAME 71 /* Ethernet frame object */

#define BL_OBJ_TYPE_SYS_VARIABLE 72 /* system variable object */

#define BL_OBJ_TYPE_CAN_ERROR_EXT 73        /* CAN error frame object (extended) */
#define BL_OBJ_TYPE_CAN_DRIVER_ERROR_EXT 74 /* CAN driver error object (extended) */

#define BL_OBJ_TYPE_LIN_LONG_DOM_SIG2 75 /* LIN uint32_t dominant signal object - extended */

#define BL_OBJ_TYPE_MOST_150_MESSAGE 76           /* MOST150 Control channel message */
#define BL_OBJ_TYPE_MOST_150_PKT 77               /* MOST150 Asynchronous channel message */
#define BL_OBJ_TYPE_MOST_ETHERNET_PKT 78          /* MOST Ethernet channel message */
#define BL_OBJ_TYPE_MOST_150_MESSAGE_FRAGMENT 79  /* Partial transmitted MOST50/150 Control channel message */
#define BL_OBJ_TYPE_MOST_150_PKT_FRAGMENT 80      /* Partial transmitted MOST50/150 data packet on asynchronous channel */
#define BL_OBJ_TYPE_MOST_ETHERNET_PKT_FRAGMENT 81 /* Partial transmitted MOST Ethernet packet on asynchronous channel */
#define BL_OBJ_TYPE_MOST_SYSTEM_EVENT 82          /* Event for various system states on MOST */
#define BL_OBJ_TYPE_MOST_150_ALLOCTAB 83          /* MOST50/150 Allocation table event */
#define BL_OBJ_TYPE_MOST_50_MESSAGE 84            /* MOST50 Control channel message */
#define BL_OBJ_TYPE_MOST_50_PKT 85                /* MOST50 Asynchronous channel message */

#define BL_OBJ_TYPE_CAN_MESSAGE2 86 /* CAN message object - extended */

#define BL_OBJ_TYPE_LIN_UNEXPECTED_WAKEUP 87
#define BL_OBJ_TYPE_LIN_SHORT_OR_SLOW_RESPONSE 88
#define BL_OBJ_TYPE_LIN_DISTURBANCE_EVENT 89

#define BL_OBJ_TYPE_SERIAL_EVENT 90

#define BL_OBJ_TYPE_OVERRUN_ERROR 91 /* driver overrun event */

#define BL_OBJ_TYPE_EVENT_COMMENT 92

#define BL_OBJ_TYPE_WLAN_FRAME 93
#define BL_OBJ_TYPE_WLAN_STATISTIC 94

#define BL_OBJ_TYPE_MOST_ECL 95 /* MOST Electrical Control Line event */

#define BL_OBJ_TYPE_GLOBAL_MARKER 96

#define BL_OBJ_TYPE_AFDX_FRAME 97
#define BL_OBJ_TYPE_AFDX_STATISTIC 98

#define BL_OBJ_TYPE_KLINE_STATUSEVENT 99 /* E.g. wake-up pattern */

#define BL_OBJ_TYPE_CAN_FD_MESSAGE 100 /*CAN FD message object*/

#define BL_OBJ_TYPE_CAN_FD_MESSAGE_64 101 /*CAN FD message object */

#define BL_OBJ_TYPE_ETHERNET_RX_ERROR 102 /* Ethernet RX error object */
#define BL_OBJ_TYPE_ETHERNET_STATUS 103   /* Ethernet status object */

#define BL_OBJ_TYPE_CAN_FD_ERROR_64 104 /*CAN FD Error Frame object */
#define BL_OBJ_TYPE_LIN_SHORT_OR_SLOW_RESPONSE2 105

#define BL_OBJ_TYPE_AFDX_STATUS 106        /* AFDX status object */
#define BL_OBJ_TYPE_AFDX_BUS_STATISTIC 107 /* AFDX line-dependent busstatistic object */
#define BL_OBJ_TYPE_reserved_4 108
#define BL_OBJ_TYPE_AFDX_ERROR_EVENT 109 /* AFDX asynchronous error event*/

#define BL_OBJ_TYPE_A429_ERROR 110         /* A429 error object */
#define BL_OBJ_TYPE_A429_STATUS 111        /* A429 status object */
#define BL_OBJ_TYPE_A429_BUS_STATISTIC 112 /* A429 busstatistic object */
#define BL_OBJ_TYPE_A429_MESSAGE 113       /* A429 Message*/

#define BL_OBJ_TYPE_ETHERNET_STATISTIC 114 /* Ethernet statistic object */

#define BL_OBJ_TYPE_reserved_5 115

#define BL_OBJ_TYPE_reserved_6 116

#define BL_OBJ_TYPE_reserved_7 117

#define BL_OBJ_TYPE_TEST_STRUCTURE 118 /* Event for test execution flow */

#define BL_OBJ_TYPE_DIAG_REQUEST_INTERPRETATION 119 /* Event for correct interpretation of diagnostic requests */

#define BL_OBJ_TYPE_ETHERNET_FRAME_EX 120        /* Ethernet packet extended object */
#define BL_OBJ_TYPE_ETHERNET_FRAME_FORWARDED 121 /* Ethernet packet forwarded object */
#define BL_OBJ_TYPE_ETHERNET_ERROR_EX 122        /* Ethernet error extended object */
#define BL_OBJ_TYPE_ETHERNET_ERROR_FORWARDED 123 /* Ethernet error forwarded object */

#define BL_OBJ_TYPE_FUNCTION_BUS 124 /* FunctionBus object */

#define BL_OBJ_TYPE_DATA_LOST_BEGIN 125   /* Data lost begin*/
#define BL_OBJ_TYPE_DATA_LOST_END 126     /* Data lost end*/
#define BL_OBJ_TYPE_WATER_MARK_EVENT 127  /* Watermark event*/
#define BL_OBJ_TYPE_TRIGGER_CONDITION 128 /* Trigger Condition event*/

/*----------------------------------------------------------------------------
|
| Define pointers
|
-----------------------------------------------------------------------------*/

#ifndef BL_LPBYTE
#define BL_LPBYTE LPBYTE
#endif

#ifndef BL_LPSTR
#define BL_LPSTR LPSTR
#endif

#ifndef BL_LPWSTR
#define BL_LPWSTR LPWSTR
#endif

#ifndef BL_PLONGLONG
#define BL_PLONGLONG PLONGLONG
#endif

/*----------------------------------------------------------------------------
|
| Base object header type definition
|
-----------------------------------------------------------------------------*/

struct VBLObjectHeaderBase_t
{
    uint32_t mSignature;     /* signature (BL_OBJ_SIGNATURE) */
    uint16_t mHeaderSize;    /* sizeof object header */
    uint16_t mHeaderVersion; /* header version (1) */
    uint32_t mObjectSize;    /* object size */
    uint32_t mObjectType;    /* object type (BL_OBJ_TYPE_XXX) */
};

/*----------------------------------------------------------------------------
|
| Extended base object header type definition with dynamic extendible objects
|
-----------------------------------------------------------------------------*/


struct VBLVarObjectHeader_t
{
    VBLObjectHeaderBase_t mBase; /* base header object */
    uint32_t mObjectFlags;       /* object flags */
    uint16_t mObjectStaticSize;  /* size of the static part of the object */
    uint16_t mObjectVersion;     /* object specific version */
    uint64_t mObjectTimeStamp;   /* object timestamp */
};


/*----------------------------------------------------------------------------
|
| Object flag IDs
|
-----------------------------------------------------------------------------*/

#define BL_OBJ_FLAG_TIME_TEN_MICS 0x00000001 /* 10 micro second timestamp */
#define BL_OBJ_FLAG_TIME_ONE_NANS 0x00000002 /* 1 nano second timestamp */

/*----------------------------------------------------------------------------
|
| Object header type definitions
|
-----------------------------------------------------------------------------*/

struct VBLObjectHeader_t
{
    VBLObjectHeaderBase_t mBase; /* base header object */
    uint32_t mObjectFlags;       /* object flags */
    uint16_t mClientIndex;       /* client index of send node */
    uint16_t mObjectVersion;     /* object specific version */
    uint64_t mObjectTimeStamp;   /* object timestamp */
};

struct VBLObjectHeader2_t
{
    VBLObjectHeaderBase_t mBase; /* base header object */
    uint32_t mObjectFlags;       /* object flags */
    uint8_t mTimeStampStatus;    /* time stamp status */
    uint8_t mReserved1;          /* reserved */
    uint16_t mObjectVersion;     /* object specific version */
    uint64_t mObjectTimeStamp;   /* object timestamp */
    uint64_t mOriginalTimeStamp; /* original object timestamp */
};

/*----------------------------------------------------------------------------
|
| Flags for TimeStampStatus
|
-----------------------------------------------------------------------------*/

#define BL_OBJ_TIMESTAMPSTATUS_FLAG_ORIG 0x01 /* 1: valid orig. timestamp  */
#define BL_OBJ_TIMESTAMPSTATUS_FLAG_SWHW 0x02 /* 1: sw generated ts; 0: hw */
#define BL_OBJ_TIMESTAMPSTATUS_FLAG_USER 0x10 /* protocol specific meaning */

/*----------------------------------------------------------------------------
|
| CAN objects
|
-----------------------------------------------------------------------------*/
/* HINT: Extension of this structure is not allowed! */
struct VBLCANMessage_t
{
    VBLObjectHeader_t mHeader;    /* object header */
    uint16_t mChannel;            /* application channel */
    uint8_t mFlags;               /* CAN dir & rtr */
    uint8_t mDLC;                 /* CAN dlc */
    uint32_t mID;                 /* CAN ID */
    std::array<uint8_t, 8> mData; /* CAN data */
};

// CAN dir, rtr, wu & nerr encoded into flags
#define CAN_MSG_DIR(f) (uint8_t) (f & 0x0F)
#define CAN_MSG_RTR(f) (uint8_t) ((f & 0x80) >> 7)
#define CAN_MSG_WU(f) (uint8_t) ((f & 0x40) >> 6)
#define CAN_MSG_NERR(f) (uint8_t) ((f & 0x20) >> 5)
#define CAN_MSG_FLAGS(dir, rtr) (uint8_t) (((uint8_t) (rtr & 0x01) << 7) | (uint8_t) (dir & 0x0F))
#define CAN_MSG_FLAGS_EXT(dir, rtr, wu, nerr) \
    (uint8_t) (((uint8_t) (rtr & 0x01) << 7) | ((uint8_t) (wu & 0x01) << 6) | ((uint8_t) (nerr & 0x01) << 5) | (uint8_t) (dir & 0x0F))
#define CAN_FD_MSG_EDL(f) (BYTE)(f & 0x1)
#define CAN_FD_MSG_BRS(f) (BYTE)((f & 0x2) >> 1)
#define CAN_FD_MSG_ESI(f) (BYTE)((f & 0x4) >> 2)


#define CAN_FD_MSG_FLAGS(edl, brs, esi) \
    (uint8_t) (((uint8_t) (edl & 0x01)) | ((uint8_t) (brs & 0x01) << 1) | (uint8_t) (esi & 0x01) << 2)

/* HINT: Extension of this structure is not allowed! */
struct VBLCANErrorFrame_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint16_t mLength;          /* CAN error frame length */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLCANErrorFrameExt_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint16_t mLength;          /* CAN error frame length */
    uint32_t mFlags;           /* extended CAN error frame flags */
    uint8_t mECC;              /* error control code */
    uint8_t mPosition;         /* error position */
    uint8_t mDLC;              /* lower 4 bits: DLC from CAN-Core. Upper 4 bits: reserved */
    uint8_t mReserved1;
    uint32_t mFrameLengthInNS; /* frame length in ns */
    uint32_t mID;              /* frame ID from CAN-Core */
    uint16_t mFlagsExt;        /* extended error flags */
    uint16_t mReserved2;
    std::array<uint8_t, 8> mData; /* Payload, only for CAN-Core */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLCANOverloadFrame_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint16_t mDummy;           /* pad */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLCANDriverStatistic_t
{
    VBLObjectHeader_t mHeader;      /* object header */
    uint16_t mChannel;              /* application channel */
    uint16_t mBusLoad;              /* CAN bus load */
    uint32_t mStandardDataFrames;   /* standard CAN id data frames */
    uint32_t mExtendedDataFrames;   /* extended CAN id data frames */
    uint32_t mStandardRemoteFrames; /* standard CAN id remote frames */
    uint32_t mExtendedRemoteFrames; /* extened CAN id remote frames */
    uint32_t mErrorFrames;          /* CAN error frames */
    uint32_t mOverloadFrames;       /* CAN overload frames */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLCANDriverError_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint8_t mTXErrors;         /* # of TX errors */
    uint8_t mRXErrors;         /* # of RX errors */
    uint32_t mErrorCode;       /* CAN driver error code */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLCANDriverErrorExt_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint8_t mTXErrors;         /* # of TX errors */
    uint8_t mRXErrors;         /* # of RX errors */
    uint32_t mErrorCode;       /* CAN driver error code */
    uint32_t mFlags;           /* flags */
    uint8_t mState;            /* state register */
    uint8_t mReserved1;
    uint16_t mReserved2;
    uint32_t mReserved3[4];
};

#define BL_HWSYNC_FLAGS_TX 1      /* sync was sent from this channel */
#define BL_HWSYNC_FLAGS_RX 2      /* external sync received */
#define BL_HWSYNC_FLAGS_RX_THIS 4 /* sync received but generated from this hardware */

/* HINT: Extension of this structure is not allowed! */
struct VBLCANDriverHwSync_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* channel where sync occured */
    uint8_t mFlags;            /* BL_HWSYNC_FLAGS_XXX */
    uint8_t mDummy;            /* pad */
};

/*----------------------------------------------------------------------------
|
| CAN extended objects
|
-----------------------------------------------------------------------------*/

/* HINT: This structure might be extended in future versions! */
struct VBLCANMessage2_t
{
    VBLObjectHeader_t mHeader;    /* object header */
    uint16_t mChannel;            /* application channel */
    uint8_t mFlags;               /* CAN dir & rtr */
    uint8_t mDLC;                 /* CAN dlc */
    uint32_t mID;                 /* CAN ID */
    std::array<uint8_t, 8> mData; /* CAN data */
    uint32_t mFrameLength;        /* message length in ns - without 3 Interframe Space bits and by Rx-message also without 1 End-Of-Frame bit */
    uint8_t mBitCount;            /* complete message length in bits */
    uint8_t mReserved1;           /* reserved */
    uint16_t mReserved2;          /* reserved */
};

/*----------------------------------------------------------------------------
|
| CAN FD objects
|
-----------------------------------------------------------------------------*/
/* HINT: This structure might be extended in future versions! */
struct VBLCANFDMessage_t
{
    VBLObjectHeader_t mHeader;     /* object header */
    uint16_t mChannel;             /* application channel */
    uint8_t mFlags;                /* CAN dir & rtr */
    uint8_t mDLC;                  /* CAN dlc */
    uint32_t mID;                  /* CAN ID */
    uint32_t mFrameLength;         /* message length in ns - without 3 inter frame space bits and by Rx-message also without 1 End-Of-Frame bit */
    uint8_t mArbBitCount;          /* bit count of arbitration phase */
    uint8_t mCANFDFlags;           /* CAN FD flags */
    uint8_t mValidDataBytes;       /* Valid payload length of mData */
    uint8_t mReserved1;            /* reserved */
    uint32_t mReserved2;           /* reserved */
    std::array<uint8_t, 64> mData; /* CAN FD data */
} VBLCANFDMessage;

/*----------------------------------------------------------------------------
|
| CAN FD objects
|
-----------------------------------------------------------------------------*/


struct VBLCANFDExtFrameData_t
{
    uint32_t mBTRExtArb;
    uint32_t mBTRExtData;
    // may be extended in future versions
} VBLCANFDExtFrameData;

#define BLHasExtFrameData(b) (((b)->mExtDataOffset != 0) && ((b)->mHeader.mBase.mObjectSize >= ((b)->mExtDataOffset + sizeof(VBLCANFDExtFrameData))))
#define BLExtFrameDataPtr(b) ((VBLCANFDExtFrameData*) ((byte*) (b) + (b)->mExtDataOffset))

struct VBLCANFDMessage64_t
{
    VBLObjectHeader_t mHeader;    /* object header */
    uint8_t mChannel;             /* application channel */
    uint8_t mDLC;                 /* CAN dlc */
    uint8_t mValidDataBytes;      /* Valid payload length of mData */
    uint8_t mTxCount;             /* TXRequiredCount (4 bits), TxReqCount (4 Bits) */
    uint32_t mID;                 /* CAN ID */
    uint32_t mFrameLength;        /* message length in ns - without 3 inter frame space bits */
                                  /* and by Rx-message also without 1 End-Of-Frame bit */
    uint32_t mFlags;              /* flags */
    uint32_t mBtrCfgArb;          /* bit rate used in arbitration phase */
    uint32_t mBtrCfgData;         /* bit rate used in data phase */
    uint32_t mTimeOffsetBrsNs;    /* time offset of brs field */
    uint32_t mTimeOffsetCrcDelNs; /* time offset of crc delimiter field */
    uint16_t mBitCount;           /* complete message length in bits */
    uint8_t mDir;
    uint8_t mExtDataOffset;
    uint32_t mCRC;                 /* CRC for CAN */
    std::array<uint8_t, 64> mData; /* CAN FD data */
    VBLCANFDExtFrameData_t mExtFrameData;
} VBLCANFDMessage64;


struct VBLCANFDErrorFrame64_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint8_t mChannel;          /* application channel */
    uint8_t mDLC;              /* CAN dlc */
    uint8_t mValidDataBytes;   /* Valid payload length of mData */
    uint8_t mECC;
    uint16_t mFlags;
    uint16_t mErrorCodeExt;
    uint16_t mExtFlags; /* FD specific flags */
    uint8_t mExtDataOffset;
    uint8_t reserved1;
    uint32_t mID;                 /* CAN ID */
    uint32_t mFrameLength;        /* message length in ns - without 3 inter frame space bits */
                                  /* and by Rx-message also without 1 End-Of-Frame bit */
    uint32_t mBtrCfgArb;          /* bit rate used in arbitration phase */
    uint32_t mBtrCfgData;         /* bit rate used in data phase */
    uint32_t mTimeOffsetBrsNs;    /* time offset of brs field */
    uint32_t mTimeOffsetCrcDelNs; /* time offset of crc delimiter field */
    uint32_t mCRC;
    uint16_t mErrorPosition; /* error position as bit offset */
    uint16_t mReserved2;
    std::array<uint8_t, 64> mData; /* CAN FD data */
    VBLCANFDExtFrameData_t mExtFrameData;
};

/*----------------------------------------------------------------------------
|
| LIN objects
|
-----------------------------------------------------------------------------*/
/* HINT: Extension of this structure is not allowed! */
struct VBLLINMessage_t
{
    VBLObjectHeader_t mHeader;    /* object header */
    uint16_t mChannel;            /* application channel */
    uint8_t mID;                  /* LIN ID */
    uint8_t mDLC;                 /* LIN DLC */
    std::array<uint8_t, 8> mData; /* t.b.d. */
    uint8_t mFSMId;               /* t.b.d. */
    uint8_t mFSMState;            /* t.b.d. */
    uint8_t mHeaderTime;          /* t.b.d. */
    uint8_t mFullTime;            /* t.b.d. */
    uint16_t mCRC;                /* t.b.d. */
    uint8_t mDir;                 /* t.b.d. */
    uint8_t mReserved;            /* t.b.d. */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLLINCRCError_t
{
    VBLObjectHeader_t mHeader;    /* object header */
    uint16_t mChannel;            /* application channel */
    uint8_t mID;                  /* LIN ID */
    uint8_t mDLC;                 /* LIN DLC */
    std::array<uint8_t, 8> mData; /* t.b.d. */
    uint8_t mFSMId;               /* t.b.d. */
    uint8_t mFSMState;            /* t.b.d. */
    uint8_t mHeaderTime;          /* t.b.d. */
    uint8_t mFullTime;            /* t.b.d. */
    uint16_t mCRC;                /* t.b.d. */
    uint8_t mDir;                 /* t.b.d. */
    uint8_t mReserved;            /* t.b.d. */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLLINDLCInfo_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint8_t mID;               /* LIN ID */
    uint8_t mDLC;              /* LIN DLC */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLLINChecksumInfo_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint8_t mID;               /* LIN ID */
    uint8_t mChecksumModel;    /* LIN checksum model */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLLINReceiveError_t
{
    VBLObjectHeader_t mHeader;          /* object header */
    uint16_t mChannel;                  /* application channel */
    uint8_t mID;                        /* LIN ID */
    uint8_t mDLC;                       /* LIN DLC */
    uint8_t mFSMId;                     /* t.b.d. */
    uint8_t mFSMState;                  /* t.b.d. */
    uint8_t mHeaderTime;                /* t.b.d. */
    uint8_t mFullTime;                  /* t.b.d. */
    uint8_t mStateReason;               /* t.b.d. */
    uint8_t mOffendingByte;             /* t.b.d. */
    uint8_t mShortError;                /* t.b.d. */
    uint8_t mTimeoutDuringDlcDetection; /* t.b.d. */
};


/* HINT: Extension of this structure is not allowed! */
struct VBLLINSendError_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint8_t mID;               /* LIN ID */
    uint8_t mDLC;              /* LIN DLC */
    uint8_t mFSMId;            /* t.b.d. */
    uint8_t mFSMState;         /* t.b.d. */
    uint8_t mHeaderTime;       /* t.b.d. */
    uint8_t mFullTime;         /* t.b.d. */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLLINSlaveTimeout_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint8_t mSlaveID;          /* t.b.d. */
    uint8_t mStateID;          /* t.b.d. */
    uint32_t mFollowStateID;   /* t.b.d. */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLLINSchedulerModeChange_t
{
    VBLObjectHeader_t mHeader;      /* object header */
    uint16_t mChannel;              /* application channel */
    uint8_t mOldMode;               /* t.b.d. */
    uint8_t mNewMode;               /* t.b.d. */
    uint8_t mOldSlot;               /* t.b.d. */
    uint8_t mNewSlot;               /* t.b.d. */
    uint8_t mFirstEventAfterWakeUp; /* t.b.d. */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLLINSyncError_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint16_t mDummy;           /* t.b.d */
    uint16_t mTimeDiff[4];     /* t.b.d */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLLINBaudrateEvent_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint16_t mDummy;           /* t.b.d */
    uint32_t mBaudrate;        /* t.b.d */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLLINSleepModeEvent_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint8_t mReason;           /* t.b.d */
    uint8_t mFlags;            /* LIN "was awake", "is awake" & "external" */
};

#define LIN_SLEEP_WAS_AWAKE 0x01
#define LIN_SLEEP_IS_AWAKE 0x02
#define LIN_SLEEP_EXTERNAL 0x04

/* HINT: Extension of this structure is not allowed! */
struct VBLLINWakeupEvent_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint8_t mSignal;           /* t.b.d */
    uint8_t mExternal;         /* t.b.d */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLLINSpikeEvent_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint32_t mWidth;           /* the spike's width */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLLINStatisticEvent_t
{
    VBLObjectHeader_t mHeader;  /* object header */
    uint16_t mChannel;          /* application channel */
    double mBusLoad;            /* bus load */
    uint32_t mBurstsTotal;      /* bursts total */
    uint32_t mBurstsOverrun;    /* bursts overrun */
    uint32_t mFramesSent;       /* frames sent */
    uint32_t mFramesReceived;   /* frames received */
    uint32_t mFramesUnanswered; /* frames unanswered */
};


/*----------------------------------------------------------------------------
|
| MOST objects
|
-----------------------------------------------------------------------------*/
/* HINT: Extension of this structure is not allowed! */
struct VBLMOSTSpy_t
{
    VBLObjectHeader_t mHeader;    /* object header */
    uint16_t mChannel;            /* application channel */
    uint8_t mDir;                 /* t.b.d */
    uint8_t mDummy1;              /* t.b.d */
    uint32_t mSourceAdr;          /* t.b.d */
    uint32_t mDestAdr;            /* t.b.d */
    std::array<uint8_t, 17> mMsg; /* t.b.d */
    uint8_t mDummy2;              /* t.b.d */
    uint16_t mRTyp;               /* t.b.d */
    uint8_t mRTypAdr;             /* t.b.d */
    uint8_t mState;               /* t.b.d */
    uint8_t mDummy3;              /* t.b.d */
    uint8_t mAckNack;             /* t.b.d */
    uint32_t mCRC;                /* t.b.d */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOSTCtrl_t
{
    VBLObjectHeader_t mHeader;    /* object header */
    uint16_t mChannel;            /* application channel */
    uint8_t mDir;                 /* t.b.d */
    uint8_t mDummy1;              /* t.b.d */
    uint32_t mSourceAdr;          /* t.b.d */
    uint32_t mDestAdr;            /* t.b.d */
    std::array<uint8_t, 17> mMsg; /* t.b.d */
    uint8_t mDummy2;              /* t.b.d */
    uint16_t mRTyp;               /* t.b.d */
    uint8_t mRTypAdr;             /* t.b.d */
    uint8_t mState;               /* t.b.d */
    uint8_t mDummy3H;             /* t.b.d */
    uint8_t mAckNack;             /* acknowledge bits */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOSTLightLock_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    int16_t mState;            /* t.b.d */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOSTStatistic_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint16_t mPktCnt;          /* t.b.d */
    uint32_t mFrmCnt;          /* t.b.d */
    uint32_t mLightCnt;        /* t.b.d */
    uint32_t mBufferLevel;     /* t.b.d */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOSTPkt_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint8_t mDir;              /* t.b.d */
    uint8_t mDummy1;           /* t.b.d */
    uint32_t mSourceAdr;       /* t.b.d */
    uint32_t mDestAdr;         /* t.b.d */
    uint8_t mArbitration;
    uint8_t mTimeRes;
    uint8_t mQuadsToFollow;
    uint16_t mCRC;
    uint8_t mPriority;
    uint8_t mTransferType;
    uint8_t mState;
    uint32_t mPktDataLength; /* length of variable data inuint8_ts */
    // BL_LPBYTE mPktData;      /* variable data */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOSTPkt2_t
{
    VBLObjectHeader2_t mHeader; /* object header - NOTE! set the object size to*/
                                /* */
                                /* mHeader.mObjectSize = sizeof( VBLMOSTPkt2) + mPktDataLength; */
                                /* */
    uint16_t mChannel;          /* application channel */
    uint8_t mDir;               /* t.b.d */
    uint8_t mDummy1;            /* t.b.d */
    uint32_t mSourceAdr;        /* t.b.d */
    uint32_t mDestAdr;          /* t.b.d */
    uint8_t mArbitration;
    uint8_t mTimeRes;
    uint8_t mQuadsToFollow;
    uint16_t mCRC;
    uint8_t mPriority;
    uint8_t mTransferType;
    uint8_t mState;
    uint32_t mPktDataLength; /* length of variable data uint8_t */
    // BL_LPBYTE mPktData;      /* variable data */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOSTHWMode_t
{
    VBLObjectHeader2_t mHeader; /* object header */
    uint16_t mChannel;          /* application channel */
    uint16_t mDummy1;
    uint16_t mHWMode;     /* bypass/master/slave/spy */
    uint16_t mHWModeMask; /* marks the altered bits */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOSTReg_t
{
    VBLObjectHeader2_t mHeader; /* object header */
    uint16_t mChannel;          /* application channel */
    uint8_t mSubType;           /* read/write request/result */
    uint8_t mDummy1;
    uint32_t mHandle;                 /* operation handle */
    uint32_t mOffset;                 /* start address */
    uint16_t mChip;                   /* chip id */
    uint16_t mRegDataLen;             /* number ofuint8_ts */
    std::array<uint8_t, 16> mRegData; /* datauint8_ts */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOSTGenReg_t
{
    VBLObjectHeader2_t mHeader; /* object header */
    uint16_t mChannel;          /* application channel */
    uint8_t mSubType;           /* read/write request/result */
    uint8_t mDummy1;
    uint32_t mHandle; /* operation handle */
    uint16_t mRegId;  /* register ID */
    uint16_t mDummy2;
    uint32_t mDummy3;
    uint64_t mRegValue; /* register value */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOSTNetState_t
{
    VBLObjectHeader2_t mHeader; /* object header */
    uint16_t mChannel;          /* application channel */
    uint16_t mStateNew;         /* MOST NetState */
    uint16_t mStateOld;
    uint16_t mDummy1;
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOSTDataLost_t
{
    VBLObjectHeader2_t mHeader; /* object header */
    uint16_t mChannel;          /* application channel */
    uint16_t mDummy1;
    uint32_t mInfo; /* info about data loss */
    uint32_t mLostMsgsCtrl;
    uint32_t mLostMsgsAsync;
    uint64_t mLastGoodTimeStampNS;
    uint64_t mNextGoodTimeStampNS;
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOSTTrigger_t
{
    VBLObjectHeader2_t mHeader; /* object header */
    uint16_t mChannel;          /* application channel */
    uint16_t mDummy1;
    uint16_t mMode; /* trigger mode */
    uint16_t mHW;   /* HW info */
    uint32_t mPreviousTriggerValue;
    uint32_t mCurrentTriggerValue;
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOSTStatisticEx_t
{
    VBLObjectHeader2_t mHeader; /* object header */
    uint16_t mChannel;          /* application channel */
    uint16_t mDummy1;
    uint32_t mCodingErrors;
    uint32_t mFrameCounter;
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOSTTxLight_t
{
    VBLObjectHeader2_t mHeader; /* object header */
    uint16_t mChannel;          /* application channel */
    uint16_t mState;
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOSTAllocTab_t
{
    VBLObjectHeader2_t mHeader; /* object header - NOTE! set the object size to*/
                                /* */
                                /* mHeader.mObjectSize = sizeof( VBLMOSTAllocTab) + mLength; */
                                /* */
    uint16_t mChannel;          /* application channel */
    uint16_t mLength;
    // BL_LPBYTE mTableData;
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOSTStress_t
{
    VBLObjectHeader2_t mHeader; /* object header */
    uint16_t mChannel;          /* application channel */
    uint16_t mState;
    uint16_t mMode;
    uint16_t mDummy1;
};

/* HINT: This structure might be extended in future versions! */
struct VBLMOSTEcl_t
{
    VBLObjectHeader2_t mHeader; /* object header */
    uint16_t mChannel;          /* application channel */
    uint16_t mMode;
    uint16_t mEclState; /* Electrical Control Line level */
    uint16_t mDummy2;
};


/*----------------------------------------------------------------------------
|
| MOST 50/150 objects
|
-----------------------------------------------------------------------------*/
/* HINT: Extension of this structure is not allowed! */
struct VBLMOST150Message_t
{
    VBLObjectHeader2_t mHeader; /* object header - NOTE! set the object size to */
                                /* mHeader.mObjectSize = sizeof(VBLMOST150Message) + mMsgLen; */
    uint16_t mChannel;          /* application channel */
    uint8_t mDir;               /* direction: 0: Rx; 1: Tx; 2: TxRequest */
    uint8_t mDummy1;
    uint32_t mSourceAdr;   /* source address */
    uint32_t mDestAdr;     /* target address */
    uint8_t mTransferType; /* 1: node message; 2: spy message*/
    uint8_t mState;        /* transmission status */
    uint8_t mAckNack;      /* acknowledge code */
    uint8_t mDummy2;
    uint32_t mCRC;     /* Cyclic Redundancy Check */
    uint8_t mPAck;     /* a preemptive acknowledge code */
    uint8_t mCAck;     /* CRC acknowledge from the packet receiver(s) to the packet transmitter */
    uint8_t mPriority; /* priority of the message */
    uint8_t mPIndex;   /* packet index, increments per message on MOST */
    uint32_t mMsgLen;  /* length of variable data inuint8_ts (51 max) */
    // BL_LPBYTE mMsg;    /* variable data */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOST150Pkt_t
{
    VBLObjectHeader2_t mHeader; /* object header - NOTE! set the object size to */
                                /* mHeader.mObjectSize = sizeof(VBLMOST150Pkt) + mPktDataLength; */
    uint16_t mChannel;          /* application channel */
    uint8_t mDir;               /* direction: 0: Rx; 1: Tx; 2: TxRequest */
    uint8_t mDummy1;
    uint32_t mSourceAdr;   /* source address */
    uint32_t mDestAdr;     /* target address */
    uint8_t mTransferType; /* 1: node message; 2: spy message*/
    uint8_t mState;        /* transmission status */
    uint8_t mAckNack;      /* acknowledge code */
    uint8_t mDummy2;
    uint32_t mCRC;           /* Cyclic Redundancy Check */
    uint8_t mPAck;           /* a preemptive acknowledge code */
    uint8_t mCAck;           /* CRC acknowledge from the packet receiver(s) to the packet transmitter */
    uint8_t mPriority;       /* priority of the message */
    uint8_t mPIndex;         /* packet index, increments per message on MOST */
    uint32_t mPktDataLength; /* length of variable data inuint8_ts (1014 max) */
    // BL_LPBYTE mPktData;      /* variable data */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOSTEthernetPkt_t
{
    VBLObjectHeader2_t mHeader; /* object header - NOTE! set the object size to */
                                /* mHeader.mObjectSize = sizeof(VBLMOSTEthernetPkt) + mPktDataLength; */
    uint16_t mChannel;          /* application channel */
    uint8_t mDir;               /* direction: 0: Rx; 1: Tx; 2: TxRequest */
    uint8_t mDummy1;
    uint64_t mSourceMacAdr; /* 48 bit source address */
    uint64_t mDestMacAdr;   /* 48 bit target address */
    uint8_t mTransferType;  /* 1: node message; 2: spy message*/
    uint8_t mState;         /* transmission status */
    uint8_t mAckNack;       /* acknowledge code */
    uint8_t mDummy2;
    uint32_t mCRC; /* Cyclic Redundancy Check */
    uint8_t mPAck; /* a preemptive acknowledge code */
    uint8_t mCAck; /* CRC acknowledge from the packet receiver(s) to the packet transmitter */
    uint16_t mDummy3;
    uint32_t mPktDataLength; /* length of variable data inuint8_ts (1506 max) */
    // BL_LPBYTE mPktData;      /* variable data */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOST150MessageFragment_t /* applied for MOST50 and MOST150 */
{
    VBLObjectHeader2_t mHeader; /* object header - NOTE! set the object size to */
                                /* mHeader.mObjectSize = sizeof(VBLMOST150MessageFragment) + mFirstDataLen; */
    uint16_t mChannel;          /* application channel */
    uint8_t mDummy1;
    uint8_t mAckNack;           /* acknowledge code */
    uint32_t mValidMask;        /* bitfield indicating which members have valid data */
    uint32_t mSourceAdr;        /* source address */
    uint32_t mDestAdr;          /* target address */
    uint8_t mPAck;              /* a preemptive acknowledge code */
    uint8_t mCAck;              /* CRC acknowledge from the packet receiver(s) to the packet transmitter */
    uint8_t mPriority;          /* priority of the message */
    uint8_t mPIndex;            /* packet index, increments per message on MOST */
    uint32_t mCRC;              /* Cyclic Redundancy Check */
    uint32_t mDataLen;          /* number of transmitted user datauint8_ts */
    uint32_t mDataLenAnnounced; /* announced user data length at the start of the transmission */
    uint32_t mFirstDataLen;     /* number  in mFirstData */
    // BL_LPBYTE mFirstData;       /* variable data */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOST150PktFragment_t /* applied for MOST50 and MOST150 */
{
    VBLObjectHeader2_t mHeader; /* object header - NOTE! set the object size to */
                                /* mHeader.mObjectSize = sizeof(VBLMOST150PktFragment) + mFirstDataLen; */
    uint16_t mChannel;          /* application channel */
    uint8_t mDummy1;
    uint8_t mAckNack;           /* acknowledge code */
    uint32_t mValidMask;        /* bitfield indicating which members have valid data */
    uint32_t mSourceAdr;        /* source address */
    uint32_t mDestAdr;          /* target address */
    uint8_t mPAck;              /* a preemptive acknowledge code */
    uint8_t mCAck;              /* CRC acknowledge from the packet receiver(s) to the packet transmitter */
    uint8_t mPriority;          /* priority of the message */
    uint8_t mPIndex;            /* packet index, increments per message on MOST */
    uint32_t mCRC;              /* Cyclic Redundancy Check */
    uint32_t mDataLen;          /* number of transmitted user datauint8_ts */
    uint32_t mDataLenAnnounced; /* announced user data length at the start of the transmission */
    uint32_t mFirstDataLen;     /* number ofuint8_ts in mFirstData */
    // BL_LPBYTE mFirstData;       /* variable data */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOSTEthernetPktFragment_t
{
    VBLObjectHeader2_t mHeader; /* object header - NOTE! set the object size to */
                                /* mHeader.mObjectSize = sizeof(VBLMOSTEthernetPktFragment) + mFirstDataLen; */
    uint16_t mChannel;          /* application channel */
    uint8_t mDummy1;
    uint8_t mAckNack;       /* acknowledge code */
    uint32_t mValidMask;    /* bitfield indicating which members have valid data */
    uint64_t mSourceMacAdr; /* 48 bit source address */
    uint64_t mDestMacAdr;   /* 48 bit target address */
    uint8_t mPAck;          /* a preemptive acknowledge code */
    uint8_t mCAck;          /* CRC acknowledge from the packet receiver(s) to the packet transmitter */
    uint16_t mDummy2;
    uint32_t mCRC;              /* Cyclic Redundancy Check */
    uint32_t mDataLen;          /* number of transmitted user datauint8_ts */
    uint32_t mDataLenAnnounced; /* announced user data length at the start of the transmission */
    uint32_t mFirstDataLen;     /* number ofuint8_ts in mFirstData */
    // BL_LPBYTE mFirstData;       /* variable data */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOSTSystemEvent_t
{
    VBLObjectHeader2_t mHeader; /* object header */
    uint16_t mChannel;          /* application channel */
    uint16_t mId;               /* identifier of transported data */
    uint32_t mValue;            /* current value */
    uint32_t mValueOld;         /* previous value */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOST150AllocTab_t /* applied for MOST50 and MOST150 */
{
    VBLObjectHeader2_t mHeader; /* object header - NOTE! set the object size too */
    uint16_t mChannel;          /* application channel */
    uint16_t mEventModeFlags;   /* determines the data layout */
    uint16_t mFreeBytes;        /* number of freeuint8_ts after the operation */
    uint16_t mLength;           /* number ofuint8_ts in mTableData*/
    // BL_LPBYTE mTableData;
    /*
      Data layout:
      if((mEventModeFlags & 0x0001) == 0)
        layout A: SLLLWWWWSLLLWWWWSLLLWWWW...
      if((mEventModeFlags & 0x0001) == 0x0001)
        layout B: SLLLWWWW<channels>SLLLWWWW<channels>SLLLWWWW<channels>...
      S:    status flags
            0x4: 1: new label (alloc)
            0x8: 1: this label has been removed (dealloc)
      LLL:  label number
      WWWW: label width
      <channels>: list of 16-bit channel numbers (size = label width)
    */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOST50Message_t
{
    VBLObjectHeader2_t mHeader; /* object header - NOTE! set the object size to */
                                /* mHeader.mObjectSize = sizeof(VBLMOST50Message) + mMsgLen; */
    uint16_t mChannel;          /* application channel */
    uint8_t mDir;               /* direction: 0: Rx; 1: Tx; 2: TxRequest */
    uint8_t mDummy1;
    uint32_t mSourceAdr;   /* source address */
    uint32_t mDestAdr;     /* target address */
    uint8_t mTransferType; /* 1: node message; 2: spy message*/
    uint8_t mState;        /* transmission status */
    uint8_t mAckNack;      /* acknowledge code */
    uint8_t mDummy2;
    uint32_t mCRC;     /* Cyclic Redundancy Check */
    uint8_t mDummy3;   /* reserved */
    uint8_t mDummy4;   /* reserved */
    uint8_t mPriority; /* priority of the message */
    uint8_t mDummy5;   /* reserved */
    uint32_t mMsgLen;  /* length of variable data inuint8_ts (17 max) */
    // BL_LPBYTE mMsg;    /* variable data */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLMOST50Pkt_t
{
    VBLObjectHeader2_t mHeader; /* object header - NOTE! set the object size to */
                                /* mHeader.mObjectSize = sizeof(VBLMOST50Pkt) + mPktDataLength; */
    uint16_t mChannel;          /* application channel */
    uint8_t mDir;               /* direction: 0: Rx; 1: Tx; 2: TxRequest */
    uint8_t mDummy1;
    uint32_t mSourceAdr;   /* source address */
    uint32_t mDestAdr;     /* target address */
    uint8_t mTransferType; /* 1: node message; 2: spy message*/
    uint8_t mState;        /* transmission status */
    uint8_t mAckNack;      /* acknowledge code */
    uint8_t mDummy2;
    uint32_t mCRC;           /* Cyclic Redundancy Check */
    uint8_t mDummy3;         /* reserved */
    uint8_t mDummy4;         /* reserved */
    uint8_t mPriority;       /* priority of the message */
    uint8_t mDummy5;         /* reserved */
    uint32_t mPktDataLength; /* length of variable data inuint8_ts (1014 max) */
    // BL_LPBYTE mPktData;      /* variable data */
};


/*----------------------------------------------------------------------------
|
| LIN extended objects
|
-----------------------------------------------------------------------------*/
/* HINT: Extension of this structure is not allowed! */
struct VBLLINBusEvent_t
{
    uint64_t mSOF;                    /* Start Of Frame timestamp */
    uint32_t mEventBaudrate;          /* Baudrate of the event in bit/sec */
    uint16_t mChannel;                /* application channel */
    std::array<uint8_t, 2> mReserved; /* 4-byte alignment */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLLINSynchFieldEvent_t
{
    VBLLINBusEvent_t mLinBusEvent; /* LIN object header */
    uint64_t mSynchBreakLength;    /* Sync Break Length in ns */
    uint64_t mSynchDelLength;      /* Sync Delimiter Length in ns */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLLINMessageDescriptor_t
{
    VBLLINSynchFieldEvent_t mLinSynchFieldEvent; /* LIN object header */
    uint16_t mSupplierID;                        /* LIN Sub-Identifier - Supplier ID */
    uint16_t mMessageID;                         /* LIN Sub-Identifier - Message ID (16 bits) */
    uint8_t mNAD;                                /* LIN Sub-Identifier - NAD */
    uint8_t mID;                                 /* LIN ID */
    uint8_t mDLC;                                /* LIN DLC */
    uint8_t mChecksumModel;                      /* LIN checksum model */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLLINDatabyteTimestampEvent_t
{
    VBLLINMessageDescriptor_t mLinMsgDescrEvent; /* object header */
    std::array<uint64_t, 9> mDatabyteTimestamps; /* Databyte timestamps, where d[0] = EndOfHeader, d[1]=EndOfDataByte1, ..., d[8]=EndOfDataByte8 */
};

/* HINT: this struct might be extended in future versions! */
struct VBLLINMessage2_t
{
    VBLObjectHeader_t mHeader;                         /* object header */
    VBLLINDatabyteTimestampEvent_t mLinTimestampEvent; /* LIN object header */
    std::array<uint8_t, 8> mData;                      /* datauint8_ts. */
    uint16_t mCRC;                                     /* checksumuint8_t */
    uint8_t mDir;                                      /* direction */
    uint8_t mSimulated;                                /* simulated frame */
    uint8_t mIsETF;                                    /* Event-triggered frame */
    uint8_t mETFAssocIndex;                            /* Unconditional frame associated with ETF - serial index */
    uint8_t mETFAssocETFId;                            /* Unconditional frame associated with ETF - id of ETF */
    uint8_t mFSMId;                                    /* t.b.d. */
    uint8_t mFSMState;                                 /* t.b.d. */
    std::array<uint8_t, 3> mReserved;                  /* 4-byte alignment */
    uint32_t mRespBaudrate;                            /* Response baudrate of the event in bit/sec */
    double mExactHeaderBaudrate;                       /* Exact baudrate of the header in bit/sec */
    uint32_t mEarlyStopbitOffset;                      /* Early stop bit offset for UART timestamps in ns */
    uint32_t mEarlyStopbitOffsetResponse;              /* Early stop bit offset in frame response for UART timestamps in ns */
};

/* HINT: this struct might be extended in future versions! */
struct VBLLINSendError2_t
{
    VBLObjectHeader_t mHeader;                   /* object header */
    VBLLINMessageDescriptor_t mLinMsgDescrEvent; /* LIN object header */
    uint64_t mEOH;                               /* EndOfHeader timestamp */
    uint8_t mIsETF;                              /* Event-triggered frame */
    uint8_t mFSMId;                              /* t.b.d. */
    uint8_t mFSMState;                           /* t.b.d. */
    uint8_t mReserved;                           /* 4-byte alignment */
    std::array<uint8_t, 4> mReserved2;           /* 4-byte alignment, reserved since BLF 3.9.3.0, BLF files from older versions may have junk data here */
    double mExactHeaderBaudrate;                 /* Exact baudrate of the header in bit/sec */
    uint32_t mEarlyStopbitOffset;                /* Early stop bit offset for UART timestamps in ns */
};

/* HINT: this struct might be extended in future versions! */
struct VBLLINSyncError2_t
{
    VBLObjectHeader_t mHeader;                   /* object header */
    VBLLINSynchFieldEvent_t mLinSynchFieldEvent; /* LIN object header */
    std::array<uint8_t, 4> mTimeDiff;            /* t.b.d */
};


/* HINT: this struct might be extended in future versions! */
struct VBLLINCRCError2_t
{
    VBLObjectHeader_t mHeader;                         /* object header */
    VBLLINDatabyteTimestampEvent_t mLinTimestampEvent; /* LIN object header */
    std::array<uint8_t, 8> mData;                      /* datauint8_ts. */
    uint16_t mCRC;                                     /* checksumuint8_t */
    uint8_t mDir;                                      /* direction */
    uint8_t mFSMId;                                    /* t.b.d. */
    uint8_t mFSMState;                                 /* t.b.d. */
    uint8_t mSimulated;                                /* simulated frame */
    std::array<uint8_t, 2> mReserved;                  /* 4-byte alignment */
    uint32_t mRespBaudrate;                            /* Response baudrate of the event in bit/sec */
    std::array<uint8_t, 4> mReserved2;                 /* 4-byte alignment, reserved since BLF 3.9.3.0, BLF files from older versions may have junk data here */
    double mExactHeaderBaudrate;                       /* Exact baudrate of the header in bit/sec */
    uint32_t mEarlyStopbitOffset;                      /* Early stop bit offset for UART timestamps in ns */
    uint32_t mEarlyStopbitOffsetResponse;              /* Early stop bit offset in frame response for UART timestamps in ns */
};

/* HINT: this struct might be extended in future versions! */
struct VBLLINReceiveError2_t
{
    VBLObjectHeader_t mHeader;                         /* object header */
    VBLLINDatabyteTimestampEvent_t mLinTimestampEvent; /* LIN object header */
    std::array<uint8_t, 8> mData;                      /* datauint8_ts. */
    uint8_t mFSMId;                                    /* t.b.d. */
    uint8_t mFSMState;                                 /* t.b.d. */
    uint8_t mStateReason;                              /* t.b.d. */
    uint8_t mOffendingByte;                            /* t.b.d. */
    uint8_t mShortError;                               /* t.b.d. */
    uint8_t mTimeoutDuringDlcDetection;                /* t.b.d. */
    uint8_t mIsETF;                                    /* ETF collision flag */
    uint8_t mHasDatabytes;                             /* t.b.d. */
    uint32_t mRespBaudrate;                            /* Response baudrate of the event in bit/sec */
    std::array<uint8_t, 4> mReserved;                  /* 4-byte alignment, reserved since BLF 3.9.3.0, BLF files from older versions may have junk data here */
    double mExactHeaderBaudrate;                       /* Exact baudrate of the header in bit/sec */
    uint32_t mEarlyStopbitOffset;                      /* Early stop bit offset for UART timestamps in ns */
    uint32_t mEarlyStopbitOffsetResponse;              /* Early stop bit offset in frame response for UART timestamps in ns */
};

/* HINT: this struct might be extended in future versions! */
struct VBLLINWakeupEvent2_t
{
    VBLObjectHeader_t mHeader;     /* object header */
    VBLLINBusEvent_t mLinBusEvent; /* LIN object header */
    uint8_t mLengthInfo;           /* t.b.d */
    uint8_t mSignal;               /* t.b.d */
    uint8_t mExternal;             /* t.b.d */
    uint8_t mReserved;             /* 4-byte alignment */
};

/* HINT: this struct might be extended in future versions! */
struct VBLLINSpikeEvent2_t
{
    VBLObjectHeader_t mHeader;        /* object header */
    VBLLINBusEvent_t mLinBusEvent;    /* LIN object header */
    uint32_t mWidth;                  /* the spike's width in microseconds */
    uint8_t mInternal;                /* t.b.d */
    std::array<uint8_t, 3> mReserved; /* 4-byte alignment */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLLINLongDomSignalEvent_t
{
    VBLObjectHeader_t mHeader;        /* object header */
    VBLLINBusEvent_t mLinBusEvent;    /* LIN object header */
    uint8_t mType;                    /* t.b.d */
    std::array<uint8_t, 3> mReserved; /* 4-byte alignment */
};

/* HINT: this struct might be extended in future versions! */
struct VBLLINLongDomSignalEvent2_t
{
    VBLObjectHeader_t mHeader;        /* object header */
    VBLLINBusEvent_t mLinBusEvent;    /* LIN object header */
    uint8_t mType;                    /* t.b.d */
    std::array<uint8_t, 7> mReserved; /* 4-byte alignment */
    uint64_t mLength;
};

/* HINT: this struct might be extended in future versions! */
struct VBLLINUnexpectedWakeup_t
{
    VBLObjectHeader_t mHeader;        /* object header */
    VBLLINBusEvent_t mLinBusEvent;    /* LIN object header */
    uint64_t mWidth;                  /* width of the unexpected wakeup in nanoseconds (valid for LIN 2.x) */
    uint8_t mSignal;                  /*uint8_t signal of the unexpected wakeup (valid for LIN 1.x) */
    std::array<uint8_t, 7> mReserved; /* 8-byte alignment */
};

/* HINT: this struct might be extended in future versions! */
struct VBLLINShortOrSlowResponse_t
{
    VBLObjectHeader_t mHeader;                         /* object header */
    VBLLINDatabyteTimestampEvent_t mLinTimestampEvent; /* LIN object header */
    uint32_t mNumberOfRespBytes;                       /* number of valid responseuint8_ts */
    std::array<uint8_t, 9> mRespBytes;                 /* the responseuint8_ts (can include the checksum) */
    uint8_t mSlowResponse;                             /* non-zero, if the response was too slow */
    uint8_t mInterruptedByBreak;                       /* non-zero, if the response was interrupted by a sync break */
    uint8_t mReserved;                                 /* 8-byte alignment */
};

struct VBLLINShortOrSlowResponse2_t
{
    VBLObjectHeader_t mHeader;                         /* object header */
    VBLLINDatabyteTimestampEvent_t mLinTimestampEvent; /* LIN object header */
    uint32_t mNumberOfRespBytes;                       /* number of valid responseuint8_ts */
    std::array<uint8_t, 9> mRespBytes;                 /* the responseuint8_ts (can include the checksum) */
    uint8_t mSlowResponse;                             /* non-zero, if the response was too slow */
    uint8_t mInterruptedByBreak;                       /* non-zero, if the response was interrupted by a sync break */
    uint8_t mReserved;                                 /* 8-byte alignment */
    double mExactHeaderBaudrate;                       /* Exact baudrate of the header in bit/sec */
    uint32_t mEarlyStopbitOffset;                      /* Early stop bit offset for UART timestamps in ns */
};

/* HINT: this struct might be extended in future versions! */
struct VBLLINDisturbanceEvent_t
{
    VBLObjectHeader_t mHeader;                  /* object header */
    uint16_t mChannel;                          /* application channel */
    uint8_t mID;                                /* LIN ID of disturbed response */
    uint8_t mDisturbingFrameID;                 /* LIN ID of disturbing header */
    uint32_t mDisturbanceType;                  /* type of disturbance (dominant, recessive, header, bitstream, variable bitstream) */
    uint32_t mByteIndex;                        /* index of theuint8_t that was disturbed */
    uint32_t mBitIndex;                         /* index of the bit that was disturbed */
    uint32_t mBitOffsetInSixteenthBits;         /* offset in 1/16th bits into the disturbed bit */
    uint32_t mDisturbanceLengthInSixteenthBits; /* length of the disturbance in units of 1/16th bit */
};

/*----------------------------------------------------------------------------
|
| FLEXRAY objects
|
-----------------------------------------------------------------------------*/
/* HINT: Extension of this structure is not allowed! */
struct VBLFLEXRAYData_t
{
    VBLObjectHeader_t mHeader;          /* object header */
    uint16_t mChannel;                  /* application channel */
    uint8_t mMUX;                       /* t.b.d */
    uint8_t mLen;                       /* t.b.d */
    uint16_t mMessageID;                /* t.b.d */
    uint16_t mCRC;                      /* t.b.d */
    uint8_t mDir;                       /* t.b.d */
    uint8_t mDummy1;                    /* t.b.d */
    uint16_t mDummy2;                   /* t.b.d */
    std::array<uint8_t, 12> mDataBytes; /* t.b.d */
};


/* HINT: Extension of this structure is not allowed! */
struct VBLFLEXRAYSync_t
{
    VBLObjectHeader_t mHeader;          /* object header */
    uint16_t mChannel;                  /* application channel */
    uint8_t mMUX;                       /* t.b.d */
    uint8_t mLen;                       /* t.b.d */
    uint16_t mMessageID;                /* t.b.d */
    uint16_t mCRC;                      /* t.b.d */
    uint8_t mDir;                       /* t.b.d */
    uint8_t mDummy1;                    /* t.b.d */
    uint16_t mDummy2;                   /* t.b.d */
    std::array<uint8_t, 11> mDataBytes; /* t.b.d */
    uint8_t mCycle;                     /* t.b.d */
};

/* HINT: Extension of this structure is not allowed! */
struct VBLFLEXRAYV6StartCycleEvent_t
{
    VBLObjectHeader_t mHeader;         /* object header */
    uint16_t mChannel;                 /* application channel */
    uint8_t mDir;                      /* dir flag (tx, rx) */
    uint8_t mLowTime;                  /* additional time field in simulation */
    uint32_t mFPGATick;                /* timestamp generated from xModule */
    uint32_t mFPGATickOverflow;        /* overflow counter of the timestamp */
    uint32_t mClientIndex;             /* clientindex of send node */
    uint32_t mClusterTime;             /* relatvie clustertime, from 0 to cyclelength*/
    std::array<uint8_t, 2> mDataBytes; /* array of databytes*/
    uint16_t mReserved;
};

/* HINT: Extension of this structure is not allowed! */
struct VBLFLEXRAYV6Message_t
{
    VBLObjectHeader_t mHeader;  /* object header */
    uint16_t mChannel;          /* application channel */
    uint8_t mDir;               /* dir flag (tx, rx) */
    uint8_t mLowTime;           /* additional time field in simulation */
    uint32_t mFPGATick;         /* timestamp generated from xModule */
    uint32_t mFPGATickOverflow; /* overflow counter of the timestamp */
    uint32_t mClientIndex;      /* clientindex of send node */
    uint32_t mClusterTime;      /* relatvie clustertime, from 0 to cyclelength*/
    uint16_t mFrameId;          /* slot identifier,uint16_t  */
    uint16_t mHeaderCRC;        /*                 uint16_t  */
    uint16_t mFrameState;       /* V6 framestate          */
    uint8_t mLength;            /* dlc of message, uint8_t  */
    uint8_t mCycle;             /* current cycle,  uint8_t  */
    uint8_t mHeaderBitMask;     /* Bit0 = NMBit, Bit1 = SyncBit, Bit2 = Reserved */
    uint8_t mReserved1;
    uint16_t mReserved2;
    std::array <uint8_t,64> mDataBytes; /* array of databytes*/
};

/* HINT: Extension of this structure is not allowed! */
struct VBLFLEXRAYStatusEvent_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint16_t mVersion;         /* object version */
    uint16_t mStatusType;      /* type of status event */
    uint16_t mInfoMask1;       /* additional info 1 */
    uint16_t mInfoMask2;       /* additional info 2 */
    uint16_t mInfoMask3;       /* additional info 3 */
    std::array<uint16_t, 16> mReserved;
};

// New FlexRay events
/* HINT: Extension of this structure is not allowed! */
struct VBLFLEXRAYVFrReceiveMsgEx_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint16_t mVersion;         /* version of data struct */
    uint16_t mChannelMask;     /* channel mask */
    uint16_t mDir;             /* dir flag (tx, rx) */
    uint32_t mClientIndex;     /* clientindex of send node */
    uint32_t mClusterNo;       /* number of cluster */
    uint16_t mFrameId;         /* slot identifier,uint16_t  */
    uint16_t mHeaderCRC1;      /* header crc channel 1  */
    uint16_t mHeaderCRC2;      /* header crc channel 2  */
    uint16_t mByteCount;       /*uint8_t count (not payload) of frame from CC receive buffer */
    uint16_t mDataCount;       /* length of the data array (stretchy struct) */
    uint16_t mCycle;           /* current cycle,uint8_t  */
    uint32_t mTag;             /* type of cc */
    uint32_t mData;            /* register flags */
    uint32_t mFrameFlags;      /* frame flags */
    uint32_t mAppParameter;    /* TxRq, TxAck flags */
    uint32_t mFrameCRC;        /* frame crc */
    uint32_t mFrameLengthNS;   /* length of frame in ns */
    uint16_t mFrameId1;        /* for internal use */
    uint16_t mPDUOffset;       /* payload offset (position in a frame) */
    uint16_t mBlfLogMask;      /* only valid for frames. Every stands for one PDU. If set, the PDU must be extracted out of the frame. The bit order is the PDU order in the frame starting with the PDU with the smallest offset */
    uint16_t mReservedW;
    std::array<uint32_t, 6> mReserved;   /* reserved */
    std::array<uint8_t, 254> mDataBytes; /* array of databytes*/
};

/* HINT: Extension of this structure is not allowed! */
struct VBLFLEXRAYVFrReceiveMsg_t
{
    VBLObjectHeader_t mHeader;           /* object header */
    uint16_t mChannel;                   /* application channel */
    uint16_t mVersion;                   /* version of data struct */
    uint16_t mChannelMask;               /* channel mask */
    uint8_t mDir;                        /* dir flag (tx, rx) */
    uint32_t mClientIndex;               /* clientindex of send node */
    uint32_t mClusterNo;                 /* number of cluster */
    uint16_t mFrameId;                   /* slot identifier,uint16_t  */
    uint16_t mHeaderCRC1;                /* header crc channel 1  */
    uint16_t mHeaderCRC2;                /* header crc channel 2  */
    uint16_t mByteCount;                 /*uint8_t count (not payload) of frame from CC receive buffer */
    uint16_t mDataCount;                 /* length of the data array (stretchy struct) */
    uint8_t mCycle;                      /* current cycle,uint8_t  */
    uint32_t mTag;                       /* type of cc */
    uint32_t mData;                      /* register flags */
    uint32_t mFrameFlags;                /* frame flags */
    uint32_t mAppParameter;              /* TxRq, TxAck flags */
    std::array<uint8_t, 254> mDataBytes; /* array of databytes*/
};

/* HINT: Extension of this structure is not allowed! */
struct VBLFLEXRAYVFrStartCycle_t
{
    VBLObjectHeader_t mHeader;          /* object header */
    uint16_t mChannel;                  /* application channel */
    uint16_t mVersion;                  /* version of data struct */
    uint16_t mChannelMask;              /* channel mask */
    uint8_t mDir;                       /* dir flag (tx, rx) */
    uint8_t mCycle;                     /* current cycle,  uint8_t  */
    uint32_t mClientIndex;              /* clientindex of send node */
    uint32_t mClusterNo;                /* number of cluster */
    uint16_t mNmSize;                   /* size of NM Vector */
    std::array<uint8_t, 12> mDataBytes; /* array of databytes (NM vector max. length)*/
    uint32_t mTag;                      /* type of cc */
    std::array<uint32_t, 5> mData;      /* register flags */
    uint16_t mReserved;
};

/* HINT: Extension of this structure is not allowed! */
struct VBLFLEXRAYVFrStatus_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint16_t mVersion;         /* object version */
    uint16_t mChannelMask;     /* channel mask */
    uint8_t mCycle;            /* current cycle,  uint8_t */
    uint32_t mClientIndex;     /* clientindex of send node */
    uint32_t mClusterNo;       /* number of cluster */
    uint32_t mWus;             /* wakeup status */
    uint32_t mCcSyncState;     /* sync state of cc */
    uint32_t mTag;             /* type of cc */
    uint32_t mData[2];         /* register flags */
    uint16_t mReserved[16];
};

/* HINT: Extension of this structure is not allowed! */
struct VBLFLEXRAYVFrError_t
{
    VBLObjectHeader_t mHeader;     /* object header */
    uint16_t mChannel;             /* application channel */
    uint16_t mVersion;             /* object version */
    uint16_t mChannelMask;         /* channel mask */
    uint8_t mCycle;                /* current cycle,uint8_t */
    uint32_t mClientIndex;         /* clientindex of send node */
    uint32_t mClusterNo;           /* number of cluster */
    uint32_t mTag;                 /* type of cc */
    std::array<uint32_t, 4> mData; /* register flags */
    uint16_t mReserved;
};

/*----------------------------------------------------------------------------
|
| J1708 message object
|
-----------------------------------------------------------------------------*/
/* HINT: Extension of this structure is not allowed! */
struct VBLJ1708Message_t
{
    VBLObjectHeader_t mHeader;      /* object header */
    uint16_t mChannel;              /* application channel */
    uint8_t mDir;                   /* direction */
    uint16_t mError;                /* error code */
    uint8_t mSize;                  /* data size */
    std::array<uint8_t, 255> mData; /* data */
} VBLJ1708Message;

/*----------------------------------------------------------------------------
|
| Environment variable object
|
-----------------------------------------------------------------------------*/
/* HINT: Extension of this structure is not allowed! */
struct VBLEnvironmentVariable_t
{
    VBLObjectHeader_t mHeader; /* object header - NOTE! set the object size to*/
                               /* */
                               /* mHeader.mObjectSize = sizeof( VBLEnvironmentVariable) + mNameLength + mDataLength; */
                               /* */
    uint32_t mNameLength;      /* length of variable name inuint8_ts */
    uint32_t mDataLength;      /* length of variable data inuint8_ts */
    // BL_LPSTR mName;          /* variable name in MBCS */
    // BL_LPBYTE mData;         /* variable data */
} VBLEnvironmentVariable;

/*----------------------------------------------------------------------------
|
| System variable object
|
-----------------------------------------------------------------------------*/

#define BL_SYSVAR_TYPE_ double 1
#define BL_SYSVAR_TYPE_LONG 2
#define BL_SYSVAR_TYPE_STRING 3
#define BL_SYSVAR_TYPE_ doubleARRAY 4
#define BL_SYSVAR_TYPE_LONGARRAY 5
#define BL_SYSVAR_TYPE_LONGLONG 6
#define BL_SYSVAR_TYPE_BYTEARRAY 7

/* HINT: Extension of this structure is not allowed! */
struct VBLSystemVariable_t
{
    VBLObjectHeader_t mHeader; /* object header - NOTE! set the object size to*/
                               /* */
                               /* mHeader.mObjectSize = sizeof( VBLSystemVariable) + mNameLength + mDataLength; */
                               /* */
    uint32_t mType;            /* type of system variable (see BL_SYSVAR_TYPE_xxx) */
    uint32_t mRepresentation;  /* signed, later perhaps also string codepage */
    std::array<uint32_t, 2> mReserved;
    uint32_t mNameLength; /* length of variable name inuint8_ts */
    uint32_t mDataLength; /* length of variable data inuint8_ts */
    // BL_LPSTR mName;       /* variable name in MBCS */
    // BL_LPBYTE mData;      /* variable data */
};

/*----------------------------------------------------------------------------
|
| GPS event object
|
-----------------------------------------------------------------------------*/
/* HINT: Extension of this structure is not allowed! */
struct VBLGPSEvent_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint32_t mFlags;           /* t.b.d. */
    uint16_t mChannel;         /* channel of event */
    uint16_t mReserved;        /* t.b.d. */
    double mLatitude;          /* t.b.d. */
    double mLongitude;         /* t.b.d. */
    double mAltitude;          /* t.b.d. */
    double mSpeed;             /* t.b.d. */
    double mCourse;            /* t.b.d. */
};

/*----------------------------------------------------------------------------
|
| Serial event object
|
-----------------------------------------------------------------------------*/

#define BL_SERIAL_TYPE_KLINE_EVENT 0x000000001
#define BL_SERIAL_TYPE_DIAG_REQUEST 0x000000002  /* only valid if BL_SERIAL_TYPE_KLINE_EVENT is set */
#define BL_SERIAL_TYPE_SINGLE_BYTE 0x000000004   /* optimization for logging singleuint8_ts */
#define BL_SERIAL_TYPE_COMPACT_BYTES 0x000000008 /* optimization for logging a fewuint8_ts without additional timestamps */

/* HINT: this struct might be extended in future versions! */
struct VBLGeneralSerialEvent_t
{
    uint32_t mDataLength;       /* length of variable data inuint8_ts */
    uint32_t mTimeStampsLength; /* length of variable timestamps inuint8_ts */
    // BL_LPBYTE mData;            /* variable data */
    // BL_PLONGLONG mTimeStamps;   /* variable timestamps (optional) */
};

/* HINT: this struct might be extended in future versions! */
struct VBLSingleByteSerialEvent_t
{
    uint8_t mByte;
};

/* HINT: this struct might be extended in future versions! */
struct VBLCompactSerialEvent_t
{
    uint8_t mCompactLength;
    uint8_t mCompactData[15];
};

/* HINT: this struct might be extended in future versions! */
struct VBLSerialEvent_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint32_t mFlags;           /* see above */
    uint32_t mPort;            /* channel of event */
    uint32_t mBaudrate;        /* baudrate at which this event was transmitted (optional) */
    uint32_t mReserved;        /* t.b.d. */
    union
    {
        VBLGeneralSerialEvent_t mGeneral;
        VBLSingleByteSerialEvent_t mSingleByte;
        VBLCompactSerialEvent_t mCompact;
    };
} VBLSerialEvent;


#define BL_KLINE_TYPE_TOECU 0x8000 /* If set in mType, direction is tester -> ECU */
#define BL_KLINE_TYPE_MASK 0x7FFF  /* Use this mask to filter out the type from mType */
/* HINT: this struct might be extended in future versions! */
struct VBLKLineStatusEvent_t
{
    VBLObjectHeader_t mHeader;     /* object header */
    uint16_t mType;                /* BusSystemFacility::VKLineStatusEventType */
    uint16_t mDataLen;             /* number of *bytes* used in mData */
    uint32_t mPort;                /* channel of event */
    uint32_t mReserved;            /* t.b.d. */
    std::array<uint64_t, 3> mData; /* the actual data, but only mDataLenuint8_tS are used! */
} VBLKLineStatusEvent;

/*----------------------------------------------------------------------------
|
| Ethernet frame object
|
-----------------------------------------------------------------------------*/
/* HINT: Extension of this structure is not allowed! */
struct VBLEthernetFrame_t
{
    VBLObjectHeader_t mHeader; /* object header - NOTE! set the object size to*/
                               /* mHeader.mObjectSize = sizeof( VBLEthernetFrame) + mPayLoadLength; */
    std::array<uint8_t, 6> mSourceAddress;
    uint16_t mChannel;
    std::array<uint8_t, 6> mDestinationAddress;
    uint16_t mDir; /* Direction flag: 0=Rx, 1=Tx, 2=TxRq */
    uint16_t mType;
    uint16_t mTPID;
    uint16_t mTCI;
    uint16_t mPayLoadLength; /* Number of valid mPayLoaduint8_ts */
    // BL_LPBYTE mPayLoad;      /* Max 1582 (1600 packet length - 18 header) datauint8_ts per frame  */
} VBLEthernetFrame;

/*----------------------------------------------------------------------------
|
| Ethernet frame2 object
|
-----------------------------------------------------------------------------*/
struct VBLEthernetFrameEx_t
{
    VBLObjectHeader_t mHeader; /* object header - NOTE! set the object size to*/
                               /* mHeader.mObjectSize = sizeof( VBLEthernetFrame) + mPayLoadLength; */
    uint16_t mStructLength;    /* Length of this structure, without sizeof(VBLObjectHeader_t), without mStructLength member and without mFrameData member */
                               /* mStructLength = sizeof(VBLEthernetFrameEx) - sizeof(VBLObjectHeader_t) - sizeof(mStructLength) - sizeof(mFrameData) */
    uint16_t mFlags;           /* flags, which indicates the valid fields: */
                               /*   Bit 0 - reserved */
                               /*   Bit 1 - mHardwareChannel valid */
                               /*   Bit 2 - mFrameDuration valid */
                               /*   Bit 3 - mFrameChecksum valid */
                               /*   Bit 4 - mFrameHandle valid */
    uint16_t mChannel;         /* application channel, i.e. Eth 1 */
    uint16_t mHardwareChannel; /* HW channel */
    uint64_t mFrameDuration;   /* Transmission duration in [ns] */
    uint32_t mFrameChecksum;   /* Ethernet checksum */
    uint16_t mDir;             /* Direction flag: 0=Rx, 1=Tx, 2=TxRq */
    uint16_t mFrameLength;     /* Number of valid mFrameDatauint8_ts */
    uint32_t mFrameHandle;     /* Handle which refer the corresponding VBLEthernetFrameForwarded event */
    uint32_t mReserved;
    // BL_LPBYTE mFrameData; /* Max 1612 datauint8_ts per frame. Contains Ethernet header + Ethernet payload  */
} VBLEthernetFrameEx;

/*----------------------------------------------------------------------------
|
| Ethernet frame forwarded object
|
-----------------------------------------------------------------------------*/
struct VBLEthernetFrameForwarded_t
{
    VBLObjectHeader_t mHeader; /* object header - NOTE! set the object size to*/
                               /* mHeader.mObjectSize = sizeof( VBLEthernetFrame) + mPayLoadLength; */
    uint16_t mStructLength;    /* Length of this structure, without sizeof(VBLObjectHeader_t), without mStructLength member and without mFrameData member */
                               /* mStructLength = sizeof(VBLEthernetFrameForwarded) - sizeof(VBLObjectHeader_t) - sizeof(mStructLength) - sizeof(mFrameData) */
    uint16_t mFlags;           /* flags, which indicates the valid fields: */
                               /*   Bit 0 - reserved */
                               /*   Bit 1 - mHardwareChannel valid */
                               /*   Bit 2 - mFrameDuration valid */
                               /*   Bit 3 - mFrameChecksum valid */
                               /*   Bit 4 - mFrameHandle valid */
    uint16_t mChannel;         /* application channel, i.e. Eth 1 */
    uint16_t mHardwareChannel; /* HW channel */
    uint64_t mFrameDuration;   /* Transmission duration in [ns] */
    uint32_t mFrameChecksum;   /* Ethernet checksum */
    uint16_t mDir;             /* Direction flag: 0=Rx, 1=Tx, 2=TxRq */
    uint16_t mFrameLength;     /* Number of valid mFrameDatauint8_ts */
    uint32_t mFrameHandle;     /* Handle which refer the corresponding VBLEthernetFrameForwarded event */
    uint32_t mReserved;
    // BL_LPBYTE mFrameData; /* Max 1612 datauint8_ts per frame. Contains Ethernet header + Ethernet payload  */
} VBLEthernetFrameForwarded;

/*----------------------------------------------------------------------------
|
| Ethernet RX error
|
-----------------------------------------------------------------------------*/

struct VBLEthernetRxError_t
{
    VBLObjectHeader_t mHeader; /* object header - NOTE! set the object size to*/
                               /* mHeader.mObjectSize = offsetof(VBLEthernetRxError, mFrameData) + event.mFrameDataLength */
    uint16_t mStructLength;    /* Length of this structure, without sizeof(VBLObjectHeader_t) and without raw data length */
                               /* mStructLength = sizeof(VBLEthernetRxError) - sizeof(VBLObjectHeader_t) - sizeof(uint32_t) */
    uint16_t mChannel;
    uint16_t mDir;             /* Direction flag: 0=Rx, 1=Tx, 2=TxRq */
    uint16_t mHardwareChannel; /* HW channel. 0 = invalid. */
    uint32_t mFcs;             /* Frame Check Sum */
    uint16_t mFrameDataLength; /* Number of valid raw ethernet datauint8_ts, starting with Target MAC ID */
    uint16_t mReserved2;       /* Gap */
    uint32_t mError;
    // BL_LPBYTE mFrameData; /* Max 1600 datauint8_ts per frame  */
} VBLEthernetRxError;

/*----------------------------------------------------------------------------
|
| Ethernet error
|
-----------------------------------------------------------------------------*/

struct VBLEthernetErrorEx_t
{
    VBLObjectHeader_t mHeader; /* object header - NOTE! set the object size to*/
                               /* mHeader.mObjectSize = offsetof(VBLEthernetRxError, mFrameData) + event.mFrameDataLength */
    uint16_t mStructLength;    /* Length of this structure, without sizeof(VBLObjectHeader_t), without mStructLength member and without mFrameData member */
                               /* mStructLength = sizeof(VBLEthernetErrorEx) - sizeof(VBLObjectHeader_t) - sizeof(mStructLength) - sizeof(mFrameData) */
    uint16_t mFlags;           /* flags, which indicates the valid fields: */
                               /*   Bit 0 - reserved */
                               /*   Bit 1 - mHardwareChannel valid */
                               /*   Bit 2 - mFrameDuration valid */
                               /*   Bit 3 - mFrameChecksum valid */
                               /*   Bit 4 - mFrameHandle valid */
    uint16_t mChannel;         /* application channel, i.e. Eth 1 */
    uint16_t mHardwareChannel; /* HW channel */
    uint64_t mFrameDuration;   /* Transmission duration in [ns] */
    uint32_t mFrameChecksum;   /* Ethernet checksum */
    uint16_t mDir;             /* Direction flag: 0=Rx, 1=Tx, 2=TxRq */
    uint16_t mFrameLength;     /* Number of valid mFrameDatauint8_ts */
    uint32_t mFrameHandle;     /* Handle which refer the corresponding VBLEthernetErrorEx event */
    uint32_t mError;
    // BL_LPBYTE mFrameData; /* Max 1612 datauint8_ts per frame. Contains Ethernet header + Ethernet payload  */
};

/*----------------------------------------------------------------------------
|
| Ethernet error forwarded
|
-----------------------------------------------------------------------------*/

struct VBLEthernetErrorForwarded_t
{
    VBLObjectHeader_t mHeader; /* object header - NOTE! set the object size to*/
                               /* mHeader.mObjectSize = offsetof(VBLEthernetRxError, mFrameData) + event.mFrameDataLength */
    uint16_t mStructLength;    /* Length of this structure, without sizeof(VBLObjectHeader_t), without mStructLength member and without mFrameData member */
                               /* mStructLength = sizeof(VBLEthernetErrorForwarded) - sizeof(VBLObjectHeader_t) - sizeof(mStructLength) - sizeof(mFrameData) */
    uint16_t mFlags;           /* flags, which indicates the valid fields: */
                               /*   Bit 0 - reserved */
                               /*   Bit 1 - mHardwareChannel valid */
                               /*   Bit 2 - mFrameDuration valid */
                               /*   Bit 3 - mFrameChecksum valid */
                               /*   Bit 4 - mFrameHandle valid */
    uint16_t mChannel;         /* application channel, i.e. Eth 1 */
    uint16_t mHardwareChannel; /* HW channel */
    uint64_t mFrameDuration;   /* Transmission duration in [ns] */
    uint32_t mFrameChecksum;   /* Ethernet checksum */
    uint16_t mDir;             /* Direction flag: 0=Rx, 1=Tx, 2=TxRq */
    uint16_t mFrameLength;     /* Number of valid mFrameDatauint8_ts */
    uint32_t mFrameHandle;     /* Handle which refer the corresponding VBLEthernetErrorForwarded event */
    uint32_t mError;
    // BL_LPBYTE mFrameData; /* Max 1612 datauint8_ts per frame. Contains Ethernet header + Ethernet payload  */
};

/*----------------------------------------------------------------------------
|
| Ethernet Status
|
-----------------------------------------------------------------------------*/

struct VBLEthernetStatus_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;
    uint16_t mFlags;      /* Valid fields: */
                          /* Bit 0 - Link Status */
                          /* Bit 1 - Bitrate */
                          /* Bit 2 - Ethernet Phy */
                          /* Bit 3 - Duplex */
                          /* Bit 4 - MDI Type */
                          /* Bit 5 - Connector */
                          /* Bit 6 - Clock Mode */
                          /* Bit 7 - BR Pair */
                          /* Bit 8 - mHardwareChannel */
    uint8_t mLinkStatus;  /* Link Status:   */
                          /* 0 - Unknown    */
                          /* 1 - Link down  */
                          /* 2 - Link up    */
                          /* 3 - Negotiate  */
                          /* 4 - Link error */
    uint8_t mEthernetPhy; /* Ethernet Phy:     */
                          /* 0 - Unknown      */
                          /* 1 - IEEE 802.3   */
                          /* 2 - BroadR-Reach */
    uint8_t mDuplex;      /* Duplex: */
                          /* 0 - Unknown     */
                          /* 1 - Half Duplex */
                          /* 2 - Full Duplex */
    uint8_t mMdi;         /* 0 - Unknown */
                          /* 1 - Direct*/
                          /* 2 - Crossover */
    uint8_t mConnector;   /* 0 - Unknown */
                          /* 1 - RJ45*/
                          /* 2 - D-Sub */
    uint8_t mClockMode;   /* 0 - Unknown */
                          /* 1 - Master */
                          /* 2 - Slave */
    uint8_t mPairs;       /* 0 - Unknown */
                          /* 1 - BR 1-pair*/
                          /* 2 - BR 2-pair */
                          /* 3 - BR 4-pair */
    uint8_t mHardwareChannel;
    uint32_t mBitrate; /* Bitrate in [kbit/sec] */
};

/*----------------------------------------------------------------------------
|
| Ethernet Statistics
|
-----------------------------------------------------------------------------*/

struct VBLEthernetStatistic_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;
    uint64_t mRcvOk_HW;
    uint64_t mXmitOk_HW;
    uint64_t mRcvError_HW;
    uint64_t mXmitError_HW;
    uint64_t mRcvBytes_HW;
    uint64_t mXmitBytes_HW;
    uint64_t mRcvNoBuffer_HW;
    int16_t mSQI;
    uint16_t mHardwareChannel;
};

/*----------------------------------------------------------------------------
|
| WLAN frame object
|
-----------------------------------------------------------------------------*/
/* HINT: Extension of this structure is not allowed! */
struct VBLWlanFrame_t
{
    VBLObjectHeader_t mHeader; /* object header - NOTE! set the object size to*/
                               /* mHeader.mObjectSize = sizeof( VBLWlanFrame_t) + mFrameLength; */
    uint16_t mChannel;         /* application channel 1..n */
    uint16_t mFlags;           /* Bit0=Genuine MAC-Header, Bit1=Correct Frame Control Format */
    uint8_t mDir;              /* Direction flag: 0=Rx, 1=Tx, 2=TxRq */
    uint8_t mRadioChannel;     /* channel number of the radio frequencey */
    int16_t mSignalStrength;   /* signal strength in [dbm] */
    uint16_t mSignalQuality;   /* signal quality in [dbm] */
    uint16_t mFrameLength;     /* Number ofuint8_ts (header + payload) */
    // BL_LPBYTE mFrameData;    /* Max. 2342 datauint8_ts per frame  */
};

/* HINT: this struct might be extended in future versions! */
struct VBLWlanStatistic_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint16_t mFlags;           /* Bit0=Valid Rx/Tx Counter, Bit1=Valid Error Counter */
    uint32_t mRxPacketCount;
    uint32_t mRxByteCount;
    uint32_t mTxPacketCount;
    uint32_t mTxByteCount;
    uint32_t mCollisionCount;
    uint32_t mErrorCount;
};

/*----------------------------------------------------------------------------
|
| AFDX frame object
|
-----------------------------------------------------------------------------*/
/* HINT: Extension of this structure is not allowed! */
struct VBLAfdxFrame_t
{
    VBLObjectHeader_t mHeader; /* object header - NOTE! set the object size to*/
                               /* mHeader.mObjectSize = sizeof( VBLEthernetFrame) + mPayLoadLength; */
    uint8_t mSourceAddress[6];
    uint16_t mChannel;
    uint8_t mDestinationAddress[6];
    uint16_t mDir; /* Direction flag: 0=Rx, 1=Tx, 2=TxRq */
    uint16_t mType;
    uint16_t mTPID;
    uint16_t mTCI;
    uint8_t mEthChannel;
    uint16_t mAfdxFlags;
    uint32_t mBAGusec;
    uint16_t mPayLoadLength; /* Number of valid mPayLoaduint8_ts */
    // BL_LPBYTE mPayLoad;      /* Max 1582 (1600 packet length - 18 header) datauint8_ts per frame  */
};

/*----------------------------------------------------------------------------
|
| AFDX combined bus- and VL- statistic event; used before 8.2
|
-----------------------------------------------------------------------------*/
/* HINT: this struct might be extended in future versions! */
struct VBLAfdxStatistic_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint16_t mFlags;           /* Bit 0 - channel is configured */
                               /* Bit 1 - HW related counters valid */
                               /* Bit 2 - CANwin related counters are valid */
                               /* Bit 3 - link-related info is valid */
                               /* Bit 4 - invalid packet counter is valid */
                               /* Bit 5 - lost packet counter is valid */
                               /* Bit 6 - dropped packet counter is valid */
                               /* Bit 7 -uint8_t counters are based on CANwin packets, not HW */
    uint32_t mRxPacketCount;
    uint32_t mRxByteCount;
    uint32_t mTxPacketCount;
    uint32_t mTxByteCount;
    uint32_t mCollisionCount;
    uint32_t mErrorCount;
    uint32_t mStatDroppedRedundantPacketCount;
    uint32_t mStatRedundantErrorPacketCount;
    uint32_t mStatIntegrityErrorPacketCount;
    uint32_t mStatAvrgPeriodMsec;
    uint32_t mStatAvrgJitterMysec;
    uint32_t mVLId;
    uint32_t mStatDuration;
};

/*----------------------------------------------------------------------------
|
| AFDX line-specific bus-statistic event used since 8.2
|
-----------------------------------------------------------------------------*/
/* HINT: this struct might be extended in future versions! */
struct VBLAfdxBusStatistic_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint16_t mFlags;           /* Bit0=Valid Rx/Tx Counter, Bit1=Valid Error Counter; Bit2=Valid VLId */
    uint32_t mStatDuration;    /* real time period in mysec of statistic datacollection */
    /* bus-specific info */
    uint32_t mStatRxPacketCountHW; /* read frames taken from hardware, i.e. on bus */
    uint32_t mStatTxPacketCountHW; /* send frames as taken from hardware, i.e. on bus */
    uint32_t mStatRxErrorCountHW;  /* number of erronous Rx-frames detected by HW */
    uint32_t mStatTxErrorCountHW;  /* number of erronous Tx-frames detected by HW */
    uint32_t mStatRxBytesHW;       /*uint8_ts received by HW during this time period */
    uint32_t mStatTxBytesHW;       /*uint8_ts sent by HW during this time period */
    /* CANwin specific info */
    uint32_t mStatRxPacketCount;      /* received frames within CANwin */
    uint32_t mStatTxPacketCount;      /* send packets from within CANwin */
    uint32_t mStatDroppedPacketCount; /* number of packets aktively dropped by CANwin */
    uint32_t mStatInvalidPacketCount; /* number of packets with incompatible eth-header regarding AFDX-spec */
    uint32_t mStatLostPacketCount;    /* number of packets lost by CABwin due to queue overflow etc */
                                      /* connection related info */
    uint8_t mLine;                    /* lineA (0) or lineB (1) */
    uint8_t mLinkStatus;              /* status of adapter as per EthernetStatus */
    uint16_t mLinkSpeed;              /* link speed: 0:=10mbps 1:=100mbps 2:=1000mbps */
    uint16_t mLinkLost;               /* counter of link-losses during this period */
};

/*----------------------------------------------------------------------------
|
| AFDX adapter status event, available since 8.2
|
-----------------------------------------------------------------------------*/
/* HINT: this struct might be extended in future versions! */
struct VBLAfdxLineStatus_t /* note: this should match specific items of VBLAEthernetStatus */
{
    uint16_t mFlags;      /* Valid fields: */
                          /* Bit 0 - Link Status */
                          /* Bit 1 - Bitrate */
                          /* Bit 2 - Ethernet Phy */
                          /* Bit 3 - Duplex */
    uint8_t mLinkStatus;  /* Link Status:   */
                          /* 0 - Unknown    */
                          /* 1 - Link down  */
                          /* 2 - Link up    */
                          /* 3 - Negotiate  */
                          /* 4 - Link error */
    uint8_t mEthernetPhy; /* Eternet Phy:     */
                          /* 0 - Unknown      */
                          /* 1 - IEEE 802.3   */
                          /* 2 - BroadR-Reach */
    uint8_t mDuplex;      /* Duplex: */
                          /* 0 - Unknown     */
                          /* 1 - Half Duplex */
                          /* 2 - Full Duplex */
    uint8_t mMdi;         /* 0 - Unknown */
                          /* 1 - Direct*/
                          /* 2 - Crossover */
    uint8_t mConnector;   /* 0 - Unknown */
                          /* 1 - RJ45*/
                          /* 2 - D-Sub */
    uint8_t mClockMode;   /* 0 - Unknown */
                          /* 1 - Master */
                          /* 2 - Slave */
    uint8_t mPairs;       /* 0 - Unknown */
                          /* 1 - BR 1-pair*/
                          /* 2 - BR 2-pair */
                          /* 3 - BR 4-pair */
    uint8_t mReserved;
    uint32_t mBitrate; /* Bitrate in [kbit/sec] */
};

struct VBLAfdxStatus_t
{
    VBLObjectHeader_t mHeader;    /* object header */
    uint16_t mChannel;            /* application channel */
    VBLAfdxLineStatus_t mStatusA; /* status of adapter lineA */
    VBLAfdxLineStatus_t mStatusB; /* status of adapter lineB */
};

/*----------------------------------------------------------------------------
|
| AFDX general error event, available since 8.5
|
-----------------------------------------------------------------------------*/
/* HINT: this struct might be extended in future versions! */
#define BL_AFDX_ERRORTEXT_LEN 512
struct VBLAfdxErrorEvent_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint16_t mErrorLevel;      /* Error Level, 0=error, 1=warning, 2=info*/
    uint32_t mSourceIdentifier;
    char mErrorText[BL_AFDX_ERRORTEXT_LEN]; /* error events are rare, so no need to optimize storage */
    char mErrorAttributes[BL_AFDX_ERRORTEXT_LEN];
};

/*----------------------------------------------------------------------------
|
| A429 message object
|
-----------------------------------------------------------------------------*/
/* HINT: Extension of this structure is not allowed! */
struct VBLA429Message_t
{
    VBLObjectHeader_t mHeader; /* object header */
    std::array<uint8_t, 4> mA429Data;
    uint16_t mChannel;
    uint8_t mDir; /* direction flag: 0=Rx, 1=Tx */
    uint8_t mReserved;
    uint32_t mBitrate;
    uint32_t mErrReason;
    uint16_t mErrPosition;
    uint64_t mFrameGap;
    uint32_t mFrameLength;
    uint16_t mMsgCtrl;
    uint32_t mCycleTime;
    uint32_t mError; /* reserved */
    uint32_t mBitLenOfLastBit;
};

/*----------------------------------------------------------------------------
|
| A429 error object
|
-----------------------------------------------------------------------------*/
/* HINT: Extension of this structure is not allowed! */
constexpr size_t BL_A429_ERRORTEXT_LEN = 512;
struct VBLA429Error_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;         /* application channel */
    uint16_t mErrorType;       /* error type, 0=error, 1=warning, 2=info*/
    uint32_t mSourceIdentifier;
    uint32_t mErrReason;
    std::array<char, BL_A429_ERRORTEXT_LEN> mErrorText; /* error events are rare, so no need to optimize storage */
    std::array<char, BL_A429_ERRORTEXT_LEN> mErrorAttributes;
};

/*----------------------------------------------------------------------------
|
| A429 status object
|
-----------------------------------------------------------------------------*/
/* HINT: Extension of this structure is not allowed! */
using VBLA429Status = struct VBLA429Status_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;
    uint8_t mDir;         /* direction flag: 0=Rx, 1=Tx */
    uint16_t mParity;     /* parity */
    uint32_t mMinGap;     /* minimum gap */
    uint32_t mBitrate;    /* Tx bit rate */
    uint32_t mMinBitrate; /* Rx min bit rate */
    uint32_t mMaxBitrate; /* Rx max bit rate */
};

/*----------------------------------------------------------------------------
|
| A429 bus statistic object
|
-----------------------------------------------------------------------------*/
/* HINT: Extension of this structure is not allowed! */
struct VBLA429BusStatistic_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint16_t mChannel;
    uint8_t mDir; /* direction flag: 0=Rx, 1=Tx */
    uint32_t mBusLoad;
    uint32_t mDataTotal;
    uint32_t mErrorTotal;
    uint32_t mBitrate;
    uint16_t mParityErrors;  /* error count (parity) */
    uint16_t mBitrateErrors; /* error count (bit rate) */
    uint16_t mGapErrors;     /* error count (gaps) */
    uint16_t mLineErrors;    /* error count (lines) */
    uint16_t mFormatErrors;
    uint16_t mDutyFactorErrors;
    uint16_t mWordLenErrors;
    uint16_t mCodingErrors;
    uint16_t mIdleErrors;
    uint16_t mLevelErrors;
    uint16_t mLabelCount[256];
} VBLA429BusStatistic;

/*----------------------------------------------------------------------------
|
| Application trigger object
|
-----------------------------------------------------------------------------*/

#define BL_TRIGGER_FLAG_SINGLE_TRIGGER 0x00000000 /* single trigger type */
#define BL_TRIGGER_FLAG_LOGGING_START 0x00000001  /* start of logging trigger type */
#define BL_TRIGGER_FLAG_LOGGING_STOP 0x00000002   /* stop of logging trigger type */
/* HINT: Extension of this structure is not allowed! */
struct VBLAppTrigger_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint64_t mPreTriggerTime;  /* pre-trigger time */
    uint64_t mPostTriggerTime; /* post-trigger time */
    uint16_t mChannel;         /* channel of event which triggered (if any) */
    uint16_t mFlags;           /* trigger type (see above) */
    uint32_t mAppSecific2;     /* app specific member 2 */
} VBLAppTrigger;

/*----------------------------------------------------------------------------
|
| Application text object
|
-----------------------------------------------------------------------------*/
#define BL_APPTEXT_MEASUREMENTCOMMENT 0x00000000
#define BL_APPTEXT_DBCHANNELINFO 0x00000001
#define BL_APPTEXT_METADATA 0x00000002

#define APPTEXT_DBCHANNELINFO_VERSION(f) (uint8_t) (f & 0x000000FF)
#define APPTEXT_DBCHANNELINFO_CHANNEL(f) (uint8_t) ((f & 0x0000FF00) >> 8)
#define APPTEXT_DBCHANNELINFO_BUSTYPE(f) (uint8_t) ((f & 0x00FF0000) >> 16)
#define APPTEXT_DBCHANNELINFO_CANFD(f) (uint8_t) ((f & 0x01000000) >> 24)
#define APPTEXT_DBCHANNELINFO_FLAGS(version, bustype, channel, canfd) \
    (uint32_t) (((uint32_t) (canfd & 0x01) << 24) | ((uint32_t) (bustype & 0xFF) << 16) | ((uint32_t) (channel & 0xFF) << 8) | ((uint32_t) (version & 0xFF)))
/* HINT: Extension of this structure is not allowed! */
struct VBLAppText_t
{
    VBLObjectHeader_t mHeader; /* object header - NOTE! set the object size to*/
                               /* */
                               /* mHeader.mObjectSize = sizeof( VBLAppText) + mTextLength; */
                               /* */
    uint32_t mSource;          /* source of text */
    uint32_t mReserved;        /* reserved */
    uint32_t mTextLength;      /* text length inuint8_ts */
    // BL_LPSTR mText;          /* text in MBCS */
} VBLAppText;

/*----------------------------------------------------------------------------
|
| Realtime clock object
|
-----------------------------------------------------------------------------*/
/* HINT: Extension of this structure is not allowed! */
struct VBLRealtimeClock_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint64_t mTime;            /* logging start time in ns since 00:00 1.1.1970 GMT */
    uint64_t mLoggingOffset;   /* measurement zero offset in ns to 00:00 1.1.1970 GMT */
} VBLRealtimeClock;

/*----------------------------------------------------------------------------
|
| File statistics
|
-----------------------------------------------------------------------------*/

#define BL_APPID_UNKNOWN 0
#define BL_APPID_CANALYZER 1
#define BL_APPID_CANOE 2
#define BL_APPID_CANSTRESS 3
#define BL_APPID_CANLOG 4
#define BL_APPID_CANAPE 5
#define BL_APPID_CANCASEXLLOG 6
#define BL_APPID_VLCONFIG 7
#define BL_APPID_PORSCHELOGGER 200

#define BL_COMPRESSION_NONE 0
#define BL_COMPRESSION_SPEED 1
#define BL_COMPRESSION_DEFAULT 6
#define BL_COMPRESSION_MAX 9

struct VBLFileStatistics_t
{
    uint32_t mStatisticsSize;       /* sizeof (VBLFileStatistics) */
    uint8_t mApplicationID;         /* application ID */
    uint8_t mApplicationMajor;      /* application major number */
    uint8_t mApplicationMinor;      /* application minor number */
    uint8_t mApplicationBuild;      /* application build number */
    uint64_t mFileSize;             /* file size inuint8_ts */
    uint64_t mUncompressedFileSize; /* uncompressed file size inuint8_ts */
    uint32_t mObjectCount;          /* number of objects */
    uint32_t mObjectsRead;          /* number of objects read */
} VBLFileStatistics;

struct SYSTEMTIME
{
    uint16_t wYear;
    uint16_t wMonth;
    uint16_t wDayOfWeek;
    uint16_t wDay;
    uint16_t wHour;
    uint16_t wMinute;
    uint16_t wSecond;
    uint16_t wMilliseconds;
};

struct VBLFileStatisticsEx_t
{
    uint32_t mStatisticsSize;         /* sizeof (VBLFileStatisticsEx) */
    uint8_t mApplicationID;           /* application ID */
    uint8_t mApplicationMajor;        /* application major number */
    uint8_t mApplicationMinor;        /* application minor number */
    uint8_t mApplicationBuild;        /* application build number */
    uint64_t mFileSize;               /* file size inuint8_ts */
    uint64_t mUncompressedFileSize;   /* uncompressed file size inuint8_ts */
    uint32_t mObjectCount;            /* number of objects */
    uint32_t mObjectsRead;            /* number of objects read */
    SYSTEMTIME mMeasurementStartTime; /* measurement start time */
    SYSTEMTIME mLastObjectTime;       /* last object time */
    uint32_t mReserved[18];           /* reserved */
} VBLFileStatisticsEx;


/*----------------------------------------------------------------------------
|
| Bus system independent
|
-----------------------------------------------------------------------------*/

#define BL_BUSTYPE_CAN 1
#define BL_BUSTYPE_LIN 5
#define BL_BUSTYPE_MOST 6
#define BL_BUSTYPE_FLEXRAY 7
#define BL_BUSTYPE_J1708 9
#define BL_BUSTYPE_ETHERNET 10
#define BL_BUSTYPE_WLAN 13
#define BL_BUSTYPE_AFDX 14

struct VBLDriverOverrun_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint32_t mBusType;         /* bus type (see BL_BUSTYPE_...) */
    uint16_t mChannel;         /* channel where overrun occured */
    uint16_t mDummy;
} VBLDriverOverrun;

/*----------------------------------------------------------------------------
|
| Event Comment
|
-----------------------------------------------------------------------------*/
struct VBLEventComment_t
{
    VBLObjectHeader_t mHeader; /* object header - NOTE! set the object size to*/
    /* */
    /* mHeader.mObjectSize = sizeof( VBLEventComment) + mTextLength; */
    /* */
    uint32_t mCommentedEventType; /* commented event type */
    uint32_t mTextLength;         /* text length inuint8_ts */
    // BL_LPSTR mText;               /* text in MBCS */
} VBLEventComment;

/*----------------------------------------------------------------------------
|
| Event Global Marker
|
-----------------------------------------------------------------------------*/
struct VBLGlobalMarker_t
{
    VBLObjectHeader_t mHeader; /* object header - NOTE! set the object size to*/
    /* */
    /* mHeader.mObjectSize = sizeof( VBLEventComment) + mGroupNameLength + mMarkerNameLength + mDescriptionLength */
    /* */
    uint32_t mCommentedEventType; /* commented event type */
    uint32_t mForegroundColor;
    uint32_t mBackgroundColor;
    uint8_t mIsRelocatable;
    uint32_t mGroupNameLength;   /* group name length inuint8_ts */
    uint32_t mMarkerNameLength;  /* marker name length inuint8_ts */
    uint32_t mDescriptionLength; /* description length inuint8_ts */
    // BL_LPSTR mGroupName;         /* group name in MBCS */
    // BL_LPSTR mMarkerName;        /* marker name in MBCS */
    // BL_LPSTR mDescription;       /* description in MBCS */
};


/*----------------------------------------------------------------------------
|
| Test Structure Event
|
-----------------------------------------------------------------------------*/
#define BL_TESTSTRUCT_TYPE_TM_TESTMODULE 1
#define BL_TESTSTRUCT_TYPE_TM_TESTGROUP 2
#define BL_TESTSTRUCT_TYPE_TM_TESTCASE 3

#define BL_TESTSTRUCT_TYPE_TESTCONFIGURATION 8
#define BL_TESTSTRUCT_TYPE_TESTUNIT 9
#define BL_TESTSTRUCT_TYPE_TESTGROUP 10
#define BL_TESTSTRUCT_TYPE_TESTFIXTURE 11
#define BL_TESTSTRUCT_TYPE_TESTSEQUENCE 12
#define BL_TESTSTRUCT_TYPE_TESTSEQUENCELIST 13
#define BL_TESTSTRUCT_TYPE_TESTCASE 14
#define BL_TESTSTRUCT_TYPE_TESTCASELIST 15

#define BL_TESTSTRUCT_ACTION_BEGIN 1
#define BL_TESTSTRUCT_ACTION_END 2
#define BL_TESTSTRUCT_ACTION_ABORT 3 // early abortion of test execution (due to e.g. verdict impact, user stop or failed assure pattern),
                                     // always correlated to test module / test configuration and followed by "end" action

#define BL_TESTSTRUCT_VERDICT_UNDEFINED 0
#define BL_TESTSTRUCT_VERDICT_NONE 1
#define BL_TESTSTRUCT_VERDICT_PASSED 2
#define BL_TESTSTRUCT_VERDICT_INCONCLUSIVE 3
#define BL_TESTSTRUCT_VERDICT_FAILED 4
#define BL_TESTSTRUCT_VERDICT_ERRORINTESTSYSTEM 5

/* HINT: Extension of this structure is not allowed! */
struct VBLTestStructure_t
{
    VBLObjectHeader_t mHeader; /* object header - NOTE! set the object size too */
    /* */
    /* mHeader.mObjectSize = sizeof(VBLTestStructure) + (mExecutingObjectNameLength + mNameLength + mTextLength) * sizeof(wchar_t) */
    /* */
    uint32_t mExecutingObjectIdentity;   /* unique ID identifying the executing test module or test configuration */
    uint16_t mType;                      /* type of structure element, see BL_TESTSTRUCT_TYPE_xxx */
    uint32_t mUniqueNo;                  /* unique number of structure element (in this test run, transitive, can be used to correlate begin/end events) */
    uint16_t mAction;                    /* indicates begin/end of structure element, see BL_TESTSTRUCT_ACTION_xxx */
    uint16_t mResult;                    /* overall result (verdict) for end of structure element events */
    uint32_t mExecutingObjectNameLength; /* string length in wchar_t's for mExecutingObjectName */
    uint32_t mNameLength;                /* string length in wchar_t's for mName */
    uint32_t mTextLength;                /* string length in wchar_t's for mText */
    // BL_LPWSTR mExecutingObjectName;      /* name of the executing test module or test configuration as shown in CANoe (wchar_t) */
    // BL_LPWSTR mName;                     /* name of structure element (can change between begin/end when using CAPL function TestCaseTitle or similar (wchar_t) */
    // BL_LPWSTR mText;                     /* full informational text for event as it appears in CANoe trace window */
} VBLTestStructure;

/*----------------------------------------------------------------------------
|
| FunctionBus object
|
-----------------------------------------------------------------------------*/

#define BL_FB_TYPE_UNDEFINED 0
#define BL_FB_TYPE_SIGNAL 1
#define BL_FB_TYPE_SERVICE_FUNCTION 2
#define BL_FB_TYPE_STATE 3

struct VBLFunctionBus_t
{
    VBLVarObjectHeader_t mHeader; /* object header - NOTE! set the object size to*/
    /* */
    /* mHeader.mObjectSize = sizeof( VBLVarObjectHeader) + sizeof (VBLFunctionBusStatic_t) + mNameLength + mDataLength; */
    /* */
    struct VBLFunctionBusStatic_t
    {
        uint32_t mObjectType; /* type of system variable (see BL_FB_TYPE_xxx) */
        uint32_t mVEType;
        uint32_t mNameLength; /* length of variable name inuint8_ts */
        uint32_t mDataLength; /* length of variable data inuint8_ts */
    } mStatic;

    struct VBLFunctionBusDynamic_t
    {
        // BL_LPSTR mName;  /* path name in the port server */
        // BL_LPBYTE mData; /* variable data */
    };
};

/* HINT: Extension of this structure is not allowed! */
struct VBLDiagRequestInterpretation_t
{
    VBLObjectHeader_t mHeader; /* object header - NOTE! set the object size too */
    /* */
    /* mHeader.mObjectSize = sizeof(VBLDiagRequestInterpretation) + (mEcuQualifierLength + mVariantQualifierLength + mServiceQualifierLength) */
    /* */
    uint32_t mDiagDescriptionHandle;  /* unique ID identifying the used diagnostic description */
    uint32_t mDiagVariantHandle;      /* unique ID identifying the used diagnostic variant     */
    uint32_t mDiagServiceHandle;      /* unique ID identifying the used diagnostic service     */
    uint32_t mEcuQualifierLength;     /* string length for mEcuQualifier     */
    uint32_t mVariantQualifierLength; /* string length for mVariantQualifier */
    uint32_t mServiceQualifierLength; /* string length for mServiceQualifier */
    // BL_LPSTR mEcuQualifier;           /* qualifier of the ECU the request was sent to */
    // BL_LPSTR mVariantQualifier;       /* qualifier of the active diagnostic variant   */
    // BL_LPSTR mServiceQualifier;       /* qualifier of the diagnostic service          */
};

/*----------------------------------------------------------------------------
|
| Queue state
|
-----------------------------------------------------------------------------*/

#define BL_WM_QS_STATUS_NORMAL 0
#define BL_WM_QS_STATUS_EMERGENCY 1
#define BL_WM_QS_STATUS_LOST_DATA 2

struct VBLWaterMarkEvent_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint32_t mQueueState;      /* the current state of the queue */
} VBLWaterMarkEvent;

#define BL_DL_QI_RT_QUEUE 0
#define BL_DL_QI_ANLYZ_QUEUE 1
#define BL_DL_QI_RT_AND_ANLYZ_QUEUE 2

struct VBLDataLostBegin_t
{
    VBLObjectHeader_t mHeader; /* object header */
    uint32_t mQueueIdentifier; /* identifier for the leaking queue */
} VBLDataLostBegin;

struct VBLDataLostEnd_t
{
    VBLObjectHeader_t mHeader;          /* object header */
    uint32_t mQueueIdentifier;          /* identifier for the leaking queue */
    uint64_t mFirstObjectLostTimeStamp; /* timestamp of the first object lost */
    uint32_t mNumberOfLostEvents;       /* number of lost events */
} VBLDataLostEnd;

/*----------------------------------------------------------------------------
|
| Trigger Condition object
|
-----------------------------------------------------------------------------*/

#define BL_TC_STATUS_UNKNOWN 0
#define BL_TC_STATUS_START 1
#define BL_TC_STATUS_STOP 2
#define BL_TC_STATUS_STARTSTOP 3

struct VBLTriggerCondition_t
{
    VBLVarObjectHeader_t mHeader; /* object header - NOTE! set the object size to*/
    /* */
    /* mHeader.mObjectSize = sizeof(VBLVarObjectHeader) + sizeof (VBLTriggerCondition_t) + mNameLength + mDataLength; */
    /* */
    struct VBLTriggerConditionStatic_t
    {
        uint32_t mState;                  /* status */
        uint32_t mTriggerBlockNameLength; /* length of trigger block name inuint8_ts */
        uint32_t mTriggerConditionLength; /* length of trigger condition inuint8_ts */
    } mStatic;

    struct VBLTriggerConditionDynamic_t
    {
        // BL_LPSTR mTriggerBlockName; /* trigger block name */
        // BL_LPSTR mTriggerCondition; /* trigger condition */
    } mDynamic;
};
