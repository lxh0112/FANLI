/*
 * DAC_SPUR.cpp
 *
 *  Created on: 2021年10月31日
 *      Author: huawei
 */


#include "TestClass.h"
#include "GetLog.h"
#include "UserAPI.h"
#include "UserDef.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>
#include <numeric>
#include "CCS08F.h"
#include "RegDef.h"
#include "d2sProtocolSSI.h"
#include "DSP_test_ABB.h"
#include "D2S_CAL_Module.h"
#include "Globle_Var.h"
#include <synchapi.h>

class DAC_SPUR: public TestClass{
public:
	void init(){

	    }

    void execute(){

		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
		TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing

        string testname = TheSoft.Flow().Test().GetCurrentTestName();
        if(strstr(testname.c_str(),"C0")!=NULL){
            DAC_SPUR_C0_Module();
        }
        else{
            DAC_SPUR_C1_Module();
        }
        if(strstr(testname.c_str(),"C1")!=NULL){
            DAC_SPUR_Restore_Module();
        }
    }
};
REGISTER_TESTCLASS("DAC_SPUR",DAC_SPUR)




