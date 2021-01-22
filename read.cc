#include <iostream>
#include <fstream>
#include <array>
#include <iomanip>

//hexdump -v -C -n 512 truck02.blf

#include "blf_structs.hh"

const int32_t FileSignature   = 0x47474F4C; //LOGG
const int32_t ObjectSignature = 0x4A424F4C; //LOBJ


uint32_t fileLength(std::fstream & fs)
{
    fs.seekg (0, fs.end);
    uint32_t length = fs.tellg();
    fs.seekg (0, fs.beg);
    return length;
}


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
    fs.read(reinterpret_cast<char *> (&os.ApiMin ),sizeof(os.ApiMin ));
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


bool read(std::fstream & fs, LogContainer & lc, const ObjectHeaderBase & ohb)
{
    fs.read(reinterpret_cast<char *> (&lc), sizeof(LogContainer));

    if(lc.compressionMethod == 2)
        {
            lc.unCompressedFileSize = ohb.objSize - sizeof(lc.compressionMethod) - sizeof(lc.reserv1)
                                      - sizeof(lc.reserv2)- sizeof(lc.unCompressedFileSize) - sizeof(lc.reserv3);
        }

    return true;
}


void print(std::ostream & s, const LogContainer & lc)
{
    s << "LogContainer : ";
    s << std::dec;
    s << "compressionMethod: " << std::hex <<(int) lc.compressionMethod ;
    s << ", uncompressedFileSize: " << std::dec <<(int) lc.unCompressedFileSize;
    s << '\n';
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


void print(std::ostream & s, const CanOverload & co)
{
    s << "CanOverload : ";
    s << std::dec;
    s << "channel: " << (int) co.channel;
    s << ", reservedCanOverloadFrame1: " << std::hex << (int) co.reservedCanOverloadFrame1;
    s << ", reservedCanOverloadFrame2: " << std::hex << (int) co.reservedCanOverloadFrame2;
    s << '\n';
}


void print(std::ostream & s, const CanMessage2 & cm2)
{
    s << "CanMessage2 : ";
    s << std::dec;
    s << "channel: " << (int) cm2.channel;
    s << ", flags: " << std::dec << (int) cm2.flags;
    s << ", dlc: " << std::dec << (int) cm2.dlc;
    s << ", id: 0x" << std::hex << (int) cm2.id;
    s << ", data: ";
    for(int n = 0; n < cm2.dlc; n++)
        s << " " << std::hex << std::setfill('0') << std::setw(2) << (int) cm2.data[n];
    s << '\n';
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


template <typename type_data>
bool read_template(std::fstream & fs, type_data & data)
{
    fs.read(reinterpret_cast<char *> (&data), sizeof( type_data ));
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


void current_position(std::ostream & s, uint64_t pos)
{
    s << "Current position: " << "0x" << std::hex << (uint64_t) pos << ", " << std::dec << (uint64_t) pos << '\n';
}


void handle_ObjectType(std::fstream & fs, const ObjectHeaderBase &  ohb)
{

    switch(ohb.objectType)
        {
        case static_cast <uint32_t> ( ObjectType::CAN_MESSAGE ): //read Can message;
        {
            struct ObjectHeader oh;
            (read_template(fs, oh));
            //	  print(std::cout, oh);
            struct CanMessage cm;
            if(read_template(fs,cm))
                print(std::cout, cm);
        }
        break;

        case static_cast <uint32_t> ( ObjectType::CAN_ERROR )  : //CanErrorFrame
        {
            print(std::cout, ohb);
            struct ObjectHeader oh;
            read_template(fs, oh);
            print(std::cout, oh);
            struct CanErrorFrame cef;
            (read_template(fs,cef));
            print(std::cout, cef);
        }
        break;

        case static_cast <uint32_t> ( ObjectType::CAN_OVERLOAD )  : //CanOverload
        {
            print(std::cout, ohb);
            struct ObjectHeader oh;
            read_template(fs, oh);
            print(std::cout, oh);
            struct CanOverload col;
            (read_template(fs,col));
            print(std::cout, col);
        }
        break;
	
        case static_cast <uint32_t> ( ObjectType::APP_TRIGGER ) : //Handle apptrigger
        {
            current_position(std::cout, fs.tellg());
            struct ObjectHeader oh;
            read_template(fs, oh);
            //print(std::cout, oh);
            struct AppTrigger ap;
            current_position(std::cout, fs.tellg());
            (read_template(fs,ap));
            //  print(std::cout, ap);
        }
        break;
	
        case static_cast <uint32_t> ( ObjectType::LOG_CONTAINER ) : //Get Logcontainer
        {
            struct LogContainer lc;
            if(read(fs, lc, ohb))
                print(std::cout, lc);
        }
        break;

	case static_cast <uint32_t> ( ObjectType::CAN_MESSAGE2 ):
	{
	    struct ObjectHeader oh;
            (read_template(fs, oh));
            //	  print(std::cout, oh);
            struct CanMessage cm2;
            if(read_template(fs,cm2))
                print(std::cout, cm2);
	}
	break;
	
        default:
	  std::cout << "New ObjectType: " << (int) ohb.objectType << '\n';
            exit(-1);
            //Unhandled message
            break;
        }

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
	    int jump_byte_counter = 0;
            while(!fs.eof())
                {
                    counter++;
                    bool result = read(fs, ohb);
		    if(!result)
		      {
			jump_byte_counter++;
			uint8_t dummy;
			fs.read(reinterpret_cast<char *> (&dummy ),sizeof(dummy));
			std::cout << "jump\n";
		      }
		    else
		      {
                    std::cout << std::dec << (int) counter << ' ';
                    std::cout << ", size: " << ohb.objSize << ", type: " << ohb.objectType << ' ';
                    handle_ObjectType(fs, ohb);
                    //	    current_position(std::cout, fs.tellg());
		      }
                }
	    std::cout << "End of file\n";
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
    std::cout << "CanMessage2     : " << std::dec << sizeof(CanMessage2       ) << '\n';
    std::cout << "AppTrigger      : " << std::dec << sizeof(AppTrigger        ) << '\n';

    //  runfile("save.blf");
    //std::cout << "----------------------------------\n";
    //runfile("night.blf");
    
    std::cout << "----------------------------------\n";

    //     run_handle("truck02.blf");
    run_handle("b-874992_logfile008.blf");
    

    std::cout << "----------------------------------\n";
    //run_handle("truck03.blf");
}

