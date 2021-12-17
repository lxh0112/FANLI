/*
 * RX_IQ_IR.cpp
 *
 *  Created on: 2021年10月31日
 *      Author: huawei
 */



#include "TestClass.h"
#include "GetLog.h"
#include "UserAPI.h"
#include "UserDef.h"
//#include "MT_DSP_Lib.h"
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

class RX_IQ_IR: public TestClass{
public:
	void init(){
	    }

    void execute(){

		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
		TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing
		string testname = TheSoft.Flow().Test().GetCurrentTestName();
		if(strstr(testname.c_str(),"C0")!=NULL){
			RXIQ_5G_C0_Set_Module();
		}
		else{
			RXIQ_5G_C1_Set_Module();
		}
    }
};
REGISTER_TESTCLASS("RX_IQ_IR",RX_IQ_IR)



