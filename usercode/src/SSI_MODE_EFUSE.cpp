//
// Created by f.he on 2021/6/18.
//

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include "Globle_Var.h"
#include "GetLog.h"

class SSI_MODE_EFUSE: public TestClass{
public:

    void init(){

    }

    void execute(){
    		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
			TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
			TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing
			TheInst.Digital().Pattern().Start();

	//		CCRFTester.CHANNEL("XIN").setClkFreq(40);
//			CCRFTester.CHANNEL("XIN").Start();


    }
};

REGISTER_TESTCLASS("SSI_MODE_EFUSE",SSI_MODE_EFUSE)

