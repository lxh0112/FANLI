/*
 * CAL_RC_PPF.cpp
 *
 *  Created on: 2021年7月14日    --based on 1.0.2.4
 */
#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include <map>
#include "d2sProtocolSSI.h"
#include "D2S_CAL_Module.h"
#include "D2S_ABB_Module.h"
#include "Globle_Var.h"
#include "CCWaveformsData.h"
#include "Test_ABB.h"
#include "UserDef.h"
#include "GetLog.h"
#include"readlimit.h"

using namespace std;
using namespace PinTool;

class CAL_RC_PPF: public TestClass {
//public:

	void init() {

		}
	void execute() {

		double hil[30],lowl[30];
		char *Test_Item[30],*Units[30];
		int  Test_number[30];

		Read_Limit(lowl,hil,Test_Item,Test_number,Units);

		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
		TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing

		CSiteLong SiteData;

		Cal_SOC_2G_Init_Module();
		Cal_PHY_2G_Init_Module();
		Cal_ABB_RF_2G_Init_Module();

		d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);//ProductionMode);
			d2sProtocolSSI d2s_test;
			d2s_test.SSI_write(0x200,0x2000,false);
			d2s_test.SSI_write(0x202,0x40,false);  //CMU_RESERVE
			d2s_test.SSI_write(0x11c,0x1);
			d2s_test.SSI_write(0x120,0x1);
		d2s::d2s_LABEL_END();

		TheInst.Wait(1*ms);//1ms

		ABB_ADC_PV_Cal("C0",&PV_SENSOR_C0_CODE,calType_Normal);
		ABB_ADC_PV_Cal("C1",&PV_SENSOR_C1_CODE,calType_Normal);

		d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);//ProductionMode);
		d2s_test.SSI_write(0x200,0x2000,false);
		d2s_test.SSI_write(0x202,0x40,false);  //CMU_RESERVE
		d2s_test.SSI_write(0x11c,0x101);
		d2s_test.SSI_write(0x120,0x101);
		d2s::d2s_LABEL_END();

		TheInst.Wait(1*ms);//1ms

		CSiteLong cal_status_C0;
		CSiteLong cal_status_C1;

		CSiteLong WL_ADC_CAP_STS_C0;
		CSiteLong WL_ADC_CAP_STS_C1;

		long long Dataarray[256];

		ABB_ADC_CalStatus("C0C1", &cal_status_C0, &cal_status_C1);
		ABB_ADC_CapCal_DC("C0", 80E6, &WL_ADC_CAP_STS_C0, calType_Normal);
		ABB_ADC_CapCal_DC("C1", 80E6, &WL_ADC_CAP_STS_C1, calType_Normal);

		RC_Cal_C0_Module(&SiteData);
		FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)

		   Testsoftbin[index] = 1;//softbin flag

		   for(int m = 0;m<256;m++)
		   {
			   Dataarray[m] = SiteData(index, m);
		   }
		   Calc_RC_data(index,Dataarray,&RC_CAL_CODE_C0,&R_CAL_CODE_C0,&C_CAL_CODE_C0);
	   FOREACH_ACTIVESITE_END

	   RC_Cal_C1_Module(&SiteData);

	   FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)

		   for(int m = 0;m<256;m++)
		   {
			   Dataarray[m] = SiteData(index,m);
		   }
		   Calc_RC_data(index,Dataarray,&RC_CAL_CODE_C1,&R_CAL_CODE_C1,&C_CAL_CODE_C1);

		   ValueTest (index,"SSI_DATA", RC_CAL_CODE_C0(index,0), lowl[0], hil[0], Units[0], Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
		   ValueTest (index,"SSI_DATA", RC_CAL_CODE_C1(index,0), lowl[1], hil[1], Units[1], Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
		   ValueTest (index,"SSI_DATA", C_CAL_CODE_C0(index,0), lowl[2], hil[2], Units[2], Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);
		   ValueTest (index,"SSI_DATA", C_CAL_CODE_C1(index,0), lowl[3], hil[3], Units[3], Test_Item[3], "FAIL_BIN", Test_number[3], Clogenable);
		   ValueTest (index,"SSI_DATA", R_CAL_CODE_C0(index,0), lowl[4], hil[4], Units[4], Test_Item[4], "FAIL_BIN", Test_number[4], Clogenable);
		   ValueTest (index,"SSI_DATA", R_CAL_CODE_C1(index,0), lowl[5], hil[5], Units[5],Test_Item[5], "FAIL_BIN", Test_number[5], Clogenable);
		   ValueTest (index,"SSI_DATA", PV_SENSOR_C0_CODE(index,0), lowl[6], hil[6], Units[6], Test_Item[6], "FAIL_BIN", Test_number[6], Clogenable);
		   ValueTest (index,"SSI_DATA", PV_SENSOR_C1_CODE(index,0), lowl[7], hil[7], Units[7], Test_Item[7], "FAIL_BIN", Test_number[7], Clogenable);
		   ValueTest (index,"SSI_DATA", cal_status_C0(index,0), lowl[8], hil[8], Units[8], Test_Item[8], "FAIL_BIN", Test_number[8], Clogenable);
		   ValueTest (index,"SSI_DATA", cal_status_C1(index,0), lowl[9], hil[9], Units[9], Test_Item[9], "FAIL_BIN", Test_number[9], Clogenable);
		   ValueTest (index,"SSI_DATA", WL_ADC_CAP_STS_C0(index,0), lowl[10], hil[10], Units[10],Test_Item[10], "FAIL_BIN", Test_number[10], Clogenable);
		   ValueTest (index,"SSI_DATA", WL_ADC_CAP_STS_C1(index,0), lowl[11], hil[11], Units[11], Test_Item[11], "FAIL_BIN", Test_number[11], Clogenable);

	   FOREACH_ACTIVESITE_END

	   RC_CAL_Final_Module();

	   FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)

			if(Testsoftbin[index]!=1){
//			 api->Set_result_bin(Testsoftbin[index]);
			}
   FOREACH_ACTIVESITE_END


	}

};

REGISTER_TESTCLASS("CAL_RC_PPF", CAL_RC_PPF)

