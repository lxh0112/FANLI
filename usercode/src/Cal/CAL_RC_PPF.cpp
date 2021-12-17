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
#include "UserDef.h"

using namespace std;
using namespace PinTool;

class CAL_RC_PPF: public TestClass {
//public:

	void init() {

		}
	void execute() {

		double hil[30],lowl[30];
		vector<string> Test_Item;
		vector<string> Units;
		int  Test_number[30];
        int Soft_Bin[30];
		int Hard_Bin[30];
		Read_Limit(lowl,hil,Test_Item,Test_number,Units,Soft_Bin,Hard_Bin);

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




			int RC_CAL_CODE_C0_tmp = RC_CAL_CODE_C0(index,0);
			int RC_CAL_CODE_C1_tmp = RC_CAL_CODE_C1(index,0);
			int C_CAL_CODE_C0_tmp = C_CAL_CODE_C0(index,0);
			int C_CAL_CODE_C1_tmp = C_CAL_CODE_C1(index,0);
			int R_CAL_CODE_C0_tmp = R_CAL_CODE_C0(index,0);
			int R_CAL_CODE_C1_tmp = R_CAL_CODE_C1(index,0);
			int PV_SENSOR_C0_CODE_tmp = PV_SENSOR_C0_CODE(index,0);
			int PV_SENSOR_C1_CODE_tmp = PV_SENSOR_C1_CODE(index,0);
			int cal_status_C0_tmp = cal_status_C0(index,0);
			int cal_status_C1_tmp = cal_status_C1(index,0);
			int WL_ADC_CAP_STS_C0_tmp = WL_ADC_CAP_STS_C0(index,0);
			int WL_ADC_CAP_STS_C1_tmp = WL_ADC_CAP_STS_C1(index,0);


			TheSoft.Flow().TestLimit( "SSI_DATA",index, RC_CAL_CODE_C0_tmp, 10, 40,6,6009, "", "RC_CAL_CODE_C0",60090000,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
			TheSoft.Flow().TestLimit( "SSI_DATA",index, RC_CAL_CODE_C1_tmp, 10, 40,6,6009, "", "RC_CAL_CODE_C1",60090001,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
			TheSoft.Flow().TestLimit( "SSI_DATA",index, C_CAL_CODE_C0_tmp, 0, 7,6,6009, "", "C_CAL_CODE_C0",60090002,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
			TheSoft.Flow().TestLimit( "SSI_DATA",index, C_CAL_CODE_C1_tmp, 0, 7,6,6009, "", "C_CAL_CODE_C1",60090003,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
			TheSoft.Flow().TestLimit( "SSI_DATA",index, R_CAL_CODE_C0_tmp, 0, 7,6,6009, "", "R_CAL_CODE_C0",60090004,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
			TheSoft.Flow().TestLimit( "SSI_DATA",index, R_CAL_CODE_C1_tmp, 0, 7,6,6009, "", "R_CAL_CODE_C1",60090005,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
			TheSoft.Flow().TestLimit( "SSI_DATA",index, PV_SENSOR_C0_CODE_tmp, 86, 152,6,6009, "", "PV_SENSOR_C0_CODE",60090006,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
			TheSoft.Flow().TestLimit( "SSI_DATA",index, PV_SENSOR_C1_CODE_tmp, 86, 152,6,6009, "", "PV_SENSOR_C1_CODE",60090007,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
			TheSoft.Flow().TestLimit( "SSI_DATA",index, cal_status_C0_tmp, 63, 63,6,6009, "", "cal_status_C0",60090008,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
			TheSoft.Flow().TestLimit( "SSI_DATA",index, cal_status_C1_tmp, 63, 63,6,6009, "", "cal_status_C1",60090009,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
			TheSoft.Flow().TestLimit( "SSI_DATA",index, WL_ADC_CAP_STS_C0_tmp, 778, 778,6,6009, "", "WL_ADC_CAP_STS_C0",60090010,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
			TheSoft.Flow().TestLimit( "SSI_DATA",index, WL_ADC_CAP_STS_C1_tmp, 778, 778,6,6009, "", "WL_ADC_CAP_STS_C1",60090011,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);

	   FOREACH_ACTIVESITE_END

	   RC_CAL_Final_Module();




	}

};

REGISTER_TESTCLASS("CAL_RC_PPF", CAL_RC_PPF)

