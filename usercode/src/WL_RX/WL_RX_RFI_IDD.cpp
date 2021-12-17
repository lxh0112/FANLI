/*
 * WL_RX_2G_M_C0_RFI_IDD.cpp
 *
 *  Created on: Nov 16, 2021
 *      Author: Administrator
 */

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include "Globle_Var.h"
#include "CCS08F.h"
#include "Excel.h"
#include "RegDef.h"
#include "d2sProtocolSSI.h"
#include "UserDef.h"


using namespace PhxAPI;

class WL_RX_RFI_IDD: public TestClass{
public:


    void init(){

    }

    void execute(){
    	TheInst.DCVS().Power().Apply();	//

		/* step2: Set DCVS parameter , then measure*/

		TheInst.DCVS().Pins("VDD_PMU_1V5_IN").SetMeasureMode(PhxAPI::E_DC_MODE_MI)
//		                                 .SetVForce(100*mV)
//		                                 .SetIRange(PhxAPI::E_POWER_BEST_FIT)
//							             .SetIClampL(LIClamp)
//							             .SetIClampH(HIClamp)
										 .SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
										 .SetMeasureMethod(PhxAPI::E_DC_METHOD_STATIC)
										 .SetMeasureOrder(PhxAPI::E_DC_ORDER_SINGLE)
										 .SetSampleSize(16)//32,16(6221)
										 .SetWaitTime(10*ms)
										 .Measure();
		//Sleep(5000);

		/* step3: get result */

		PinArrayDouble  Result=TheInst.DCVS().Pins("VDD_PMU_1V5_IN").GetMeasureResults();
		Result.ShowPinArrayData();
		//TheSoft.Flow().TestLimit(powerpinlist,Result);
		/* step4: judgement and output datalog */
//		TheSoft.Flow().TestLimit(result);
//		TheSoft.Datalog().DatalogMultiParametricTest(result,"OS_PS");
//		vector<string> pinname = SplitPinList("VDD_PMU_1V5_IN");
		TheInst.DCVS().ClearAllSetPara();

//		for(int i =0;i<pinname.size();i++)
//		{
//			if(pinname[i] == "VDD_PMU_CLDO"){
//			TheSoft.Flow().TestLimit(pinname[i] ,Result ,-0.00002 ,0.0003 ,2,2000,"A","POWER_OSD",20000000+i,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
//			}
//			else
//			TheSoft.Flow().TestLimit(pinname[i] ,Result ,-0.00002 ,0.00002 ,2,2000,"A","POWER_OSD",20000000+i,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
//		}

    }
};
REGISTER_TESTCLASS("WL_RX_RFI_IDD",WL_RX_RFI_IDD)







