/*
 * SSI_MODE.cpp
 *
 *  Created on: 2021年8月18日
 *      Author: 荣耀
 */


#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include <synchapi.h>

class SSI_MODE: public TestClass{
public:
		std::string measurepin;
		double vforce;
		double iclamph;
		double iclampl;

	void init(){

	}
    void execute(){
					TheInst.GIFA().SetSingleEndMode();
					Sleep(1);
					TheInst.GIFA().SetClkFreq(40);
					TheInst.GIFA().SetChannel(0xff);
					TheInst.GIFA().Start();
					Sleep(10);

					TheInst.DCVS().Power().Apply();
					TheInst.Digital().Level().Apply();
					TheInst.Digital().Timing().Apply();
					TheInst.Digital().PatEng().SetupMCFData();
					TheInst.Digital().PatEng().SetFailMode(PhxAPI::E_SET_HIL_MODE);
					TheInst.Digital().Pattern().Run();
    }

};
REGISTER_TESTCLASS("SSI_MODE",SSI_MODE)


