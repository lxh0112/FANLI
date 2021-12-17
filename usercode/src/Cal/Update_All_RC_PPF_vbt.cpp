/*
 * Update_All_RC_PPF_vbt.cpp
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
#include "Globle_Var.h"
#include <synchapi.h>

class Update_All_RC_PPF_vbt: public TestClass{
public:


	void init(){

	    }

    void execute(){
    	char channelC0[5] = "C0";
		char channelC1[5] = "C1";

		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
		TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing


		Write_RC_PPF(RX_Path, channelC0);
		Write_RC_PPF(RX_Path, channelC1);
		Write_RC_PPF(TX_Path, channelC0);
		Write_RC_PPF(TX_Path, channelC1);
    }

};
REGISTER_TESTCLASS("Update_All_RC_PPF_vbt",Update_All_RC_PPF_vbt)




