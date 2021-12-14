

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include <synchapi.h>
//#include "Lib.h"

class DFT_MODE: public TestClass{
public:
	void init(){

}
    void execute(){
        TheInst.GIFA().SetSingleEndMode();
        Sleep(1);
        TheInst.GIFA().SetClkFreq(40);
        TheInst.GIFA().SetChannel(0xff);
        TheInst.GIFA().Start();

        Sleep(10);

		TheInst.DCVI().Power().Apply();
		TheInst.Digital().Level().Apply();
		TheInst.Digital().Timing().Apply();
		TheInst.Digital().PatEng().SetupMCFData();
		TheInst.Digital().PatEng().SetFailMode(PhxAPI::E_SET_HIL_MODE);
		TheInst.Digital().Pattern().Run();

	 	map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
	 	for(auto it = result.begin(); it != result.end(); it++)
		{
	 		cout<<"get pass/fail:"<< it->second<<endl;
		}
	 	uint64_t executedcount=TheInst.Digital().PatEng().GetExecutedCyclesCount();
	 		    cout<<dec;
	 		    cout<<"executedcount (dec) :"<<executedcount<<endl;
	 		    std::string testname = TheSoft.Flow().Test().GetCurrentTestName();
	 		  	cout<<"*******testname is********"<<testname<<endl;


      cout<<"============end============="<<endl;

    }

};



REGISTER_TESTCLASS("DFT_MODE",DFT_MODE)

