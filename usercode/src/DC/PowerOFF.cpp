

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include <synchapi.h>
#include "CCS08F.h"
#include "Globle_Var.h"

class PowerOFF: public TestClass{
public:
    std::string pinlist;
    std::string UbitON;
    std::string UbitOFF;
    double IForce;
	double LVClamp;
	double HVClamp;
	double waittime;
	int samplesize;

    void init(){
    	add_param( "Measure_pinlist",  "PinString", &pinlist).set_default("gOS_VDD,gOS_VSS");
    	add_param("SampleSize","int",&samplesize).set_default("32");
//        add_param( "IO_VSSpinlist",  "PinString", &IO_VSSpinlist);
//        add_param( "UbitON",  "PinString", &UbitON);
//        add_param( "UbitOFF",  "PinString", &UbitOFF);
//        add_param("IForce","double",&IForce).set_default("-0.0002");
//        add_param("LVClamp","double",&LVClamp).set_default("-1");
//        add_param("HVClamp","double",&HVClamp).set_default("0");
//        add_param("waittime","double",&waittime).set_default("0.002");
//        add_param("SampleSize","int",&SampleSize).set_default("16");
    }

    void execute(){

        //TheInst.GIFA().SetSingleEndMode();
        //Sleep(60);
        //TheInst.GIFA().SetClkFreq(40);
        TheInst.GIFA().SetChannel(0x00);
        TheInst.GIFA().Close();
        Sleep(60);
//		TheInst.Digital().Timing("").StopFreeRunningClock();
//		TheInst.Digital().Timing("").Apply();

//		IO_VSSpinlist="gOS_VDD,gOS_VSS";
//		TheInst.PPMU().Pins(pinlist).SetClear();
//		TheInst.PPMU().Pins(pinlist).SetMeasureType(PhxAPI::E_MEASURE)
//										.SetIClampH(20.0 *uA)
//										.SetIClampL(-20.0 *uA)
//										.SetIRange(50 *uA)
//										.SetVForce(0* V )
//										.SetMeasureMode(PhxAPI::E_DC_FV_MI)
//										.Connect(true)
//										.SetSampleSize(samplesize)
//										.SetWaitTime(5 * ms)
//										.Measure();
//		TheInst.PPMU().Pins(pinlist).Connect(false).Apply();

		TheInst.Util().SetUserPower(PhxAPI::E_USERPW_P5V , 1  );
		TheInst.Wait(5*ms);

		TheInst.DCVI().Power().Apply();

		cout<<"all power off now!!!!!"<<endl;

		cout << "----------------------------------TestInfoLoaded_Flag :" << TestInfoLoaded_Flag << endl;
//		CCRFTester.Close();
//		cout<<"Close CCRFTester!!!!!"<<endl;
    }

};


REGISTER_TESTCLASS("PowerOFF",PowerOFF)
