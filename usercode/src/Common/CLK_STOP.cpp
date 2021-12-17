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


class CLK_STOP: public TestClass{
public:


	void init(){

	}
    void execute(){
    	 TheInst.Digital().Timing("").StopFreeRunningClock();
    	 TheInst.Digital().Timing("").Apply();
//					TheInst.GIFA().SetSingleEndMode();
//					Sleep(1);
//					TheInst.GIFA().SetClkFreq(40);
//					TheInst.GIFA().SetChannel(0xff);
//					TheInst.GIFA().Start();
//					Sleep(10);

    }

};
REGISTER_TESTCLASS("CLK_STOP",CLK_STOP)


