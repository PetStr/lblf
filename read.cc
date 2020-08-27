#include <iostream>
#include <fstream>
#include <array>
#include <iomanip>

//hexdump -v -C -n 512 truck02.blf

const int32_t FileSignature   = 0x47474F4C; //LOGG
const int32_t ObjectSignature = 0x4A424F4C; //LOBJ


uint32_t fileLength(std::fstream & fs)
{
    fs.seekg (0, fs.end);
    uint32_t length = fs.tellg();
    fs.seekg (0, fs.beg);
    return length;
}


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


void print(std::ostream & s, const sysTime_t & ts)
{
    s << std::dec;
    s << "year : " << (int) ts.year;
    s << " month: " << (int) ts.month ;
    s << " dayOfWeek : "<< (int) ts.dayOfWeek ;
    s << " day :"<< (int) ts.day ;
    s << " hour :" << (int) ts.hour ;
    s << " minute :" << (int) ts.minute ;
    s << " second :" << (int) ts.second ;
    s << " milliseconds :" << (int) ts.milliseconds ;
    s << '\n';
}

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


bool read(std::fstream & fs, fileStatistics & os)
{
    fs.read(reinterpret_cast<char *> (&os.FileSign ),sizeof(os.FileSign ));
    if(os.FileSign != FileSignature)
        {
            return false;
        }

    fs.read(reinterpret_cast<char *> (&os.StatSize ),sizeof(os.StatSize ));
    fs.read(reinterpret_cast<char *> (&os.AppId ),sizeof(os.AppId ));
    fs.read(reinterpret_cast<char *> (&os.AppMaj ),sizeof(os.AppMaj ));
    fs.read(reinterpret_cast<char *> (&os.AppMin ),sizeof(os.AppMin ));
    fs.read(reinterpret_cast<char *> (&os.AppBuild ),sizeof(os.AppBuild ));
    fs.read(reinterpret_cast<char *> (&os.ApiMaj ),sizeof(os.ApiMaj  ));
    fs.read(reinterpret_cast<char *> (&os. ApiMin ),sizeof(os.ApiMin ));
    fs.read(reinterpret_cast<char *> (&os.ApiBuild ),sizeof(os.ApiBuild ));
    fs.read(reinterpret_cast<char *> (&os.ApiPatch ),sizeof(os.ApiPatch ));
    fs.read(reinterpret_cast<char *> (&os.fileSize ),sizeof(os.fileSize ));
    fs.read(reinterpret_cast<char *> (&os.uncompressedSize ),sizeof(os.uncompressedSize ));
    fs.read(reinterpret_cast<char *> (&os.objCount ),sizeof(os.objCount ));
    fs.read(reinterpret_cast<char *> (&os.objRead ),sizeof(os.objRead ));
    fs.read(reinterpret_cast<char *> (&os.meas_start_time ),sizeof(os.meas_start_time ));
    fs.read(reinterpret_cast<char *> (&os.last_obj_time ),sizeof(os.last_obj_time ));
    fs.read(reinterpret_cast<char *> (&os.fileSize_less115 ),sizeof(os.fileSize_less115 ));
    auto offset = os.StatSize - sizeof(fileStatistics);
    fs.seekg(offset, std::ios_base::cur);
    return true;
}


void print(std::ostream & s, const fileStatistics & os)
{
    s << "os.FileSign           " << std::hex << static_cast<uint64_t> ( os.FileSign ) << '\n';
    s << "os.StatSize           " << static_cast<uint64_t> ( os.StatSize );
    s << " dec: " << std::dec     << static_cast<uint64_t> ( os.StatSize ) << '\n';
    s << "os.AppId              " << static_cast<uint64_t> ( os.AppId	 ) << '\n';
    s << "os.AppMaj             " << static_cast<uint64_t> ( os.AppMaj	 ) << '\n';
    s << "os.AppMin             " << static_cast<uint64_t> ( os.AppMin	 ) << '\n';
    s << "os.AppBuild           " << static_cast<uint64_t> ( os.AppBuild ) << '\n';
    s << "os.ApiMaj             " << static_cast<uint64_t> ( os.ApiMaj	 ) << '\n';
    s << "os.ApiMin             " << static_cast<uint64_t> ( os.ApiMin	 ) << '\n';
    s << "os.ApiBuild           " << static_cast<uint64_t> ( os.ApiBuild ) << '\n';
    s << "os.ApiPatch           " << static_cast<uint64_t> ( os.ApiPatch ) << '\n';
    s << "os.fileSize           " << static_cast<uint64_t> ( os.fileSize ) << '\n';
    s << "os.uncompressedSize   " << static_cast<uint64_t> ( os.uncompressedSize  ) << '\n';
    s << "os.objCount           " << static_cast<uint64_t> ( os.objCount ) << '\n';
    s << "os.objRead            " << static_cast<uint64_t> ( os.objRead  ) << '\n';
    s << "os.meas_start_time: ";
    print(s,  os.meas_start_time);
    s << "os.last_obj_time: ";
    print(s,  os.last_obj_time);
    s << "os.fileSize_less115   " << static_cast<uint64_t> ( os.fileSize_less115 ) << '\n';
}


struct ObjectHeaderBase
{
    uint32_t ObjSign;
    uint16_t headerSize;
    uint16_t headerVer;
    uint32_t objSize;
    uint32_t objectType;
};


void print(std::ostream & s, const ObjectHeaderBase & ohb)
{
    s << "ObjectHeaderBase: ";
    s << "ObjSign " << std::hex <<(int) ohb.ObjSign ;
    s << std::dec;
    s << ", headerSize " << (int) ohb.headerSize ;
    s << ", headerVer " << (int) ohb.headerVer ;
    s << ", objSize " << (int) ohb.objSize ;
    s << ", objectType " << (int) ohb.objectType  ;
    s << '\n';
}


bool read(std::fstream & fs, ObjectHeaderBase & ohb)
{
    fs.read(reinterpret_cast<char *> (&ohb.ObjSign),sizeof(ohb.ObjSign));
    if(ohb.ObjSign != ObjectSignature)
        {
            return false;
        }
    fs.read(reinterpret_cast<char *> (&ohb.headerSize),sizeof(ohb.headerSize));
    fs.read(reinterpret_cast<char *> (&ohb.headerVer),sizeof(ohb.headerVer));
    fs.read(reinterpret_cast<char *> (&ohb.objSize),sizeof(ohb.objSize));
    fs.read(reinterpret_cast<char *> (&ohb.objectType),sizeof(ohb.objectType));
//    auto offset = ohb.headerSize - sizeof(ohb.ObjSign) - sizeof(ohb.headerSize) -
//                  sizeof(ohb.headerVer) - sizeof(ohb.objSize) - sizeof(ohb.objectType);
//    fs.seekg(offset, std::ios_base::cur);
//    std::cout << "Moving file pointer extra offset: " << std::dec << (int) offset << '\n';
    return true;
}


enum ObjectFlags_e : uint32_t
{
    TimeTenMics = 0x00000001,
    TimeNano = 0x00000002
};

enum timeStampStatus_e : uint8_t
{
    orginal = 0x01, SwGen = 0x02, User = 0x10
};


#pragma pack(1)
struct ObjectHeader2
{
    ObjectFlags_e objectFlags;
    timeStampStatus_e  timeStampStatus;
    uint8_t  reservObjHeader;
    uint16_t ObjectHeaderVersion;
    uint64_t ObjectTimeStamp;
    uint64_t originalObjectTimeStamp;
};
#pragma pack()


bool read(std::fstream & fs, ObjectHeader2 & oh2)
{
//    fs.read(reinterpret_cast<char *> (&oh2.objectFlags),   sizeof(oh2.objectFlags));
//    fs.read(reinterpret_cast<char *> (&oh2.timeStampStatus),sizeof(oh2.timeStampStatus));
//    fs.read(reinterpret_cast<char *> (&oh2.reservObjHeader), sizeof(oh2.reservObjHeader));
//    fs.read(reinterpret_cast<char *> (&oh2.ObjectTimeStamp),   sizeof(oh2.ObjectTimeStamp));
//    fs.read(reinterpret_cast<char *> (&oh2.originalObjectTimeStamp), sizeof(oh2.originalObjectTimeStamp));
//
    fs.read(reinterpret_cast<char *> (&oh2), sizeof(ObjectHeader2));

    
    return true;
}


void print(std::ostream & s, const ObjectHeader2 & oh2)
{
    s << "ObjectHeader2: ";
    s << std::dec;
    s << "objectFlags " << std::hex <<(int) oh2.objectFlags ;
    s << ", timeStampStatus " << (int) oh2.timeStampStatus ;
    s << ", reservObjHeader " << (int) oh2.reservObjHeader ;
    s << ", ObjectTimeStamp " << (int) oh2.ObjectTimeStamp ;
    s << ", originalObjectTimeStamp " << (int) oh2.originalObjectTimeStamp  ;
    s << '\n';
}

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
    //Calculated
    uint32_t compressedFileSize;
};


bool read(std::fstream & fs, LogContainer & lc, const ObjectHeaderBase & ohb)
{
    fs.read(reinterpret_cast<char *> (&lc.compressionMethod ), sizeof(lc.compressionMethod));
    fs.read(reinterpret_cast<char *> (&lc.reserv1), sizeof(lc.reserv1));
    fs.read(reinterpret_cast<char *> (&lc.reserv2), sizeof(lc.reserv2));
    fs.read(reinterpret_cast<char *> (&lc.unCompressedFileSize),   sizeof(lc.unCompressedFileSize));
    fs.read(reinterpret_cast<char *> (&lc.reserv3), sizeof(lc.reserv3));


    
    if(lc.compressionMethod == 2)
        {
            lc.compressedFileSize = ohb.objSize - sizeof(lc.compressionMethod) - sizeof(lc.reserv1)
                                    - sizeof(lc.reserv2)- sizeof(lc.unCompressedFileSize) - sizeof(lc.reserv3);
        }
    else //Assume uncompressed
        {
            lc.compressedFileSize = lc.unCompressedFileSize;
        }
    return true;
}


void print(std::ostream & s, const LogContainer & lc)
{
    s << "LogContainer : ";
    s << std::dec;
    s << "compressionMethod: " << std::hex <<(int) lc.compressionMethod ;
    s << ", uncompressedFileSize: " << std::dec <<(int) lc.unCompressedFileSize;
    s << ", compressedFileSize: " << std::dec <<(int) lc.compressedFileSize;
    s << '\n';
}

#pragma pack(1)
struct ObjectHeader
{
    ObjectFlags_e objectFlag;
    uint16_t clientIndex;
    uint16_t objectVersion;
    uint64_t objectTimeStamp;
};
#pragma pack()


bool read(std::fstream & fs, ObjectHeader & oh)
{
  //  std::cout << "Reading ObjectHeader\n";
//    fs.read(reinterpret_cast<char *> (&oh.objectFlag), sizeof(oh.objectFlag));
//    fs.read(reinterpret_cast<char *> (&oh.clientIndex), sizeof(oh.clientIndex));
//    fs.read(reinterpret_cast<char *> (&oh.objectVersion), sizeof(oh.objectVersion));
//    fs.read(reinterpret_cast<char *> (&oh.objectTimeStamp), sizeof(oh.objectTimeStamp));
//
    fs.read(reinterpret_cast<char *> (&oh), sizeof(ObjectHeader));
    
    return true;
}


void print(std::ostream & s, const ObjectHeader & oh)
{
    s << "ObjectHeader : ";
    s << std::dec;
    s << "objectFlag: " << (int) oh.clientIndex ;
    s << ", objectVersion: " << std::dec << (int) oh.objectVersion;
    s << ", objectTimeStamp: " << std::dec << (int) oh.objectTimeStamp;
    s << '\n';
}

#pragma pack(1)
struct CanMessage
{
    uint16_t channel;
    uint8_t flags;
    uint8_t dlc;
    uint32_t id;
    std::array<uint8_t, 8> data {};
};
#pragma pack()

bool read(std::fstream & fs, CanMessage & cm)
{
//    fs.read(reinterpret_cast<char *> (&cm.channel), sizeof(cm.channel));
//    fs.read(reinterpret_cast<char *> (&cm.flags), sizeof(cm.flags));
//    fs.read(reinterpret_cast<char *> (&cm.dlc), sizeof(cm.dlc));
//    if(cm.dlc > 8)
//      cm.dlc = 8;
//    fs.read(reinterpret_cast<char *> (&cm.id), sizeof(cm.id));
//    fs.read(reinterpret_cast<char *> (cm.data.data()), static_cast<std::streamsize>(cm.data.size()));


  fs.read(reinterpret_cast<char *> (&cm), sizeof(CanMessage));
  if(cm.dlc > 8)
    {
      cm.dlc = 8;
    }
    
    return true;
}

void print(std::ostream & s, const CanMessage & cm)
{
    s << "CanMessage : ";
    s << std::dec;
    s << "channel: " << (int) cm.channel;
    s << ", flags: " << std::dec << (int) cm.flags;
    s << ", dlc: " << std::dec << (int) cm.dlc;
    s << ", id: 0x" << std::hex << (int) cm.id;
    s << ", data: ";
    for(int n = 0; n < cm.dlc; n++)
        s << " " << std::hex << std::setfill('0') << std::setw(2) << (int) cm.data[n];
    s << '\n';
}

#pragma pack(1)
struct AppTrigger
{
    uint64_t preTriggerTime;
    uint64_t postTriggerTime;
    uint16_t channel;
    uint16_t flags;
    uint32_t appSpecific2;
};
#pragma pack()

bool read(std::fstream & fs, AppTrigger & at)
{
//    fs.read(reinterpret_cast<char *> (&at.preTriggerTime ), sizeof(at.preTriggerTime));
//    fs.read(reinterpret_cast<char *> (&at.postTriggerTime ), sizeof(at.postTriggerTime));
//    fs.read(reinterpret_cast<char *> (&at.channel ), sizeof(at.channel));
//    fs.read(reinterpret_cast<char *> (&at.flags ), sizeof(at.flags));
//    fs.read(reinterpret_cast<char *> (&at.appSpecific2 ), sizeof(at.appSpecific2));
//
    fs.read(reinterpret_cast<char *> (&at), sizeof(AppTrigger));
    
    return true;
}

void print(std::ostream & s, const AppTrigger & at)
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

#pragma pack(1)
struct CanErrorFrame
{
    uint16_t channel;
    uint16_t length;
    uint32_t reservedCanErrorFrame;
};
#pragma pack()

bool read(std::fstream & fs, CanErrorFrame & cfe)
{
//    fs.read(reinterpret_cast<char *> (&cfe.channel ), sizeof(cfe.channel));
//    fs.read(reinterpret_cast<char *> (&cfe.length ), sizeof(cfe.length));
//    fs.read(reinterpret_cast<char *> (&cfe.reservedCanErrorFrame ), sizeof(cfe.reservedCanErrorFrame));
//
    fs.read(reinterpret_cast<char *> (&cfe), sizeof(CanErrorFrame));
    
    return true;
}

void print(std::ostream & s, const CanErrorFrame & cfe)
{
    s << "CanErrorFrame: ";
    s << std::dec;
    s << ", channel : " << (uint64_t) cfe.channel;
    s << ", length : " << (uint64_t) cfe.length;
    s << ", reservedCanErrorFrame : " << (uint64_t) cfe.reservedCanErrorFrame; 
    s << '\n';
}


void runfile (const char * filename)
{
    std::cout << "Opening file: " << filename << '\n';
    std::fstream fs(filename, std::fstream::in | std::fstream::binary);

    if(fs)
        {
            struct fileStatistics os;
            std::cout << "sizeof(os) " << std::dec << sizeof(os) << '\n';
            read(fs, os);
            print(std::cout, os);
            std::cout << "Current position: " << std::hex << (int) fs.tellg() << ", " << std::dec << (int) fs.tellg()  << '\n';

            //    fs.seekg(os.StatSize, std::ios::beg);
            std::cout << "Current position: " << std::hex << (int) fs.tellg() << ", " << std::dec << (int) fs.tellg()  << '\n';

            struct ObjectHeaderBase ohb;
            read(fs, ohb);
            print(std::cout, ohb);
            std::cout << "sizeof(ohb) " << std::dec << sizeof(ohb) << '\n';
            std::cout << "Current position: " << std::hex << (int) fs.tellg() << ", " << std::dec << (int) fs.tellg()  << '\n';

            struct LogContainer lc;
            read(fs, lc, ohb);
            print(std::cout, lc);
            std::cout << "Current position: " << std::hex << (int) fs.tellg() << ", " << std::dec << (int) fs.tellg()  << '\n';
        }
    fs.close();
}


void current_position(std::ostream & s, uint64_t pos)
{
    s << "Current position: " << "0x" << std::hex << (uint64_t) pos << ", " << std::dec << (uint64_t) pos << '\n';
}


void handle_ObjectType(std::fstream & fs, const ObjectHeaderBase &  ohb)
{
  
    switch(ohb.objectType)
        {
        case 1: //read Can message;
	  {
	  struct ObjectHeader oh;
	  (read(fs, oh));
	  //	  print(std::cout, oh);
	  struct CanMessage cm;
	  if(read(fs,cm))
	    print(std::cout, cm);
	  }
            break;

	case 2 : //CanErrorFrame
	  {
	    print(std::cout, ohb);
	    struct ObjectHeader oh;
	    read(fs, oh);
	    print(std::cout, oh);
	    struct CanErrorFrame cef;
	    (read(fs,cef));
	    print(std::cout, cef);
	  }
	  break;
	    
        case 5 : //Handle apptrigger
	  {
	    current_position(std::cout, fs.tellg());
	    struct ObjectHeader oh;
	    read(fs, oh);
	    //print(std::cout, oh);
	    struct AppTrigger ap;
	    current_position(std::cout, fs.tellg());
	    (read(fs,ap));
	    //  print(std::cout, ap);
	  }
	  break;
        case 10: //Get Logcontainer
	  {
	  struct LogContainer lc;
	  if(read(fs, lc, ohb))
	    print(std::cout, lc);
	  }
            break;
        default:
	  std::cout << "Now ObjectType\n";
	  exit(-1);
            //Unhandled message
            break;
        }

}


void runfile_nocompress (const char * filename)
{
    std::cout << "Opening file: " << filename << '\n';
    std::fstream fs(filename, std::fstream::in | std::fstream::binary);

    if(fs)
        {
            struct fileStatistics os;
            read(fs, os);
            //            print(std::cout, os);
            current_position(std::cout, fs.tellg());

            struct ObjectHeaderBase ohb;
            read(fs, ohb);
            print(std::cout, ohb);
            current_position(std::cout, fs.tellg());

            struct LogContainer lc;
            read(fs, lc, ohb);
            print(std::cout, lc);
            current_position(std::cout, fs.tellg());

            struct ObjectHeaderBase ohb2;
            read(fs, ohb2);
            print(std::cout, ohb2);
            current_position(std::cout, fs.tellg());

            struct ObjectHeader oh;
            read(fs, oh);
            print(std::cout, oh);
            current_position(std::cout, fs.tellg());


            struct CanMessage cm;
            read(fs, cm);
            print(std::cout, cm);
            current_position(std::cout, fs.tellg());

        }
    fs.close();
}



void run_handle (const char * filename)
{
    std::cout << "Opening file: " << filename << '\n';
    std::fstream fs(filename, std::fstream::in | std::fstream::binary);

    if(fs)
        {
            struct fileStatistics os;
            read(fs, os);
            //            print(std::cout, os);
            current_position(std::cout, fs.tellg());

            struct ObjectHeaderBase ohb;

	    int counter = 0;
	    while(!fs.eof())
	      {
		counter++;
		read(fs, ohb);
		//  print(std::cout, ohb);
	        //  current_position(std::cout, fs.tellg());
		std::cout << std::dec << (int) counter << ' ';
		std::cout << "s: " << ohb.objSize << "t: " << ohb.objectType << ' ';		
		handle_ObjectType(fs, ohb);
		//	    current_position(std::cout, fs.tellg());
	      }
        }
    fs.close();
}



int main()
{

    std::cout << "sysTime_t       : " << std::dec << sizeof(sysTime_t         ) << '\n';
    std::cout << "fileStatistics  : " << std::dec << sizeof(fileStatistics    ) << '\n';
    std::cout << "ObjectHeaderBase: " << std::dec << sizeof(ObjectHeaderBase  ) << '\n';
    std::cout << "ObjectHeader    : " << std::dec << sizeof(ObjectHeader      ) << '\n';
    std::cout << "ObjectHeader2   : " << std::dec << sizeof(ObjectHeader2     ) << '\n';
    std::cout << "LogContainer    : " << std::dec << sizeof(LogContainer      ) << '\n';
    std::cout << "CanMessage      : " << std::dec << sizeof(CanMessage        ) << '\n';
    std::cout << "AppTrigger      : " << std::dec << sizeof(AppTrigger        ) << '\n';

    //  runfile("save.blf");
    //std::cout << "----------------------------------\n";
    //runfile("night.blf");
    std::cout << "----------------------------------\n";

    //    runfile_nocompress("truck02.blf");

    run_handle("truck03.blf");
    

}

