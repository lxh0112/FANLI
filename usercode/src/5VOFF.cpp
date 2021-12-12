

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include <synchapi.h>
//#include "Lib.h"

class OFF: public TestClass{
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
    }

    void execute(){


        TheInst.GIFA().SetChannel(0x00);
        TheInst.GIFA().Close();
        Sleep(60);


		TheInst.Util().SetUserPower(PhxAPI::E_USERPW_P5V , 1  );
		TheInst.Wait(5*ms);

		TheInst.DCVS().Power().Apply();

		cout<<"all power off now!!!!!"<<endl;


    }

};


REGISTER_TESTCLASS("OFF",OFF)

