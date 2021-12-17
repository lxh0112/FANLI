/*
 * PROG_INIT.cpp
 *
 *  Created on: 2021年11月1日
 *      Author: huawei
 */

#include "TestClass.h"
#include "LogFile.h"
#include "Excel.h"
#include "CCS08F.h"
#include "UserAPI.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>
#include "Globle_Var.h"
#include "UserDef.h"
#include <synchapi.h>

using namespace PhxAPI;
using namespace PinTool;


class PROG_INIT: public TestClass{
public:

	void init(){

	    }
    void execute(){



    	d2s_WorkMode = ProductionMode;  //ProductionMode;  //LearningMode;

		char szWfmPath[256] = {0};
		const char* pszWfmpath = TheSoft.GetProgramFullPath().c_str();
		int nLength = strlen(strrchr(pszWfmpath,('\\')));
		ZeroMemory(strrchr(pszWfmpath,('\\')),nLength*sizeof(char));
		sprintf(szWfmPath,"%s\\Waveforms",pszWfmpath);
		if(CCRF_R_ERROR ==CCRFTester.LoadWaveformFiles(szWfmPath))
		{
			printf("\"LoadWaveformFiles\":<%s> Exec Fail...\n",pszWfmpath);
		}
    	TheInst.Util().SetUserPower(PhxAPI::E_USERPW_P5V, PhxAPI::E_UTIL_STATE_ON);
		for(uint32_t j=0;j<256;j++)
		{
			TheInst.Util().SetRelayState(j, PhxAPI::E_UTIL_STATE_OFF); //bihe-0,duankai-1
		}
		TheInst.Wait(4*ms);//us

		Clogenable = true;
		Last_TestName="";

		Globle_Array_Init();

		CosSin_Value();
		FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
			HBIN_FLAG[site_id] = 0;

		FOREACH_ACTIVESITE_END

		string flowname = TheSoft.Flow().GetCurrentFlowName();
		if(strstr(flowname.c_str() , "QA")!=NULL){
			CurrentLimitSet="QA";
		}
		else if(strstr(flowname.c_str() , "GLD")!=NULL){
			CurrentLimitSet="Golden";
		}
		else{
			CurrentLimitSet="Default";
		}

		if(!TestInfoLoaded_Flag)//
		{
			char pathFinal[256] = "\0";
			//const char *programPath = api->Get_program_path();
			string programPath = TheSoft.GetProgramPath();
			char *limitsPath = "/TestLimit/Hi1151SV208_Limits.xlsx";
			sprintf(pathFinal, "%s%s", programPath.c_str(), limitsPath);

			CBBLimits cbbLimits;

			if(cbbLimits.ReadLimits(pathFinal, &mapLimits) != READ_SUCCESS)
			{
				cout << "read limits fail" << endl;
				return;
			}

			else
			{
				LoadSignalSetting();
			}
			TestInfoLoaded_Flag = true;

			for(int i =0;i<4;i++)
			{
				PRE_VREF_ARRAY.InitDataArray(i,200);//lay init
				PRE_BUCK_ARRAY.InitDataArray(i,200);//lay init
				PRE_IREF_ARRAY.InitDataArray(i,200);//lay init
			}

		}
		//osd code
		PHXSYS_LOGSTR_TRACE("-------------------------------------------");
		PHXSYS_LOGSTR_TRACE("------!!!Hello power_osd!!!------");
		TheInst.DCVS().Power().Apply();
		std::string pin = "PMU_RBIAS,PMU_REFBP,DBB_VDDIO_3V3,DBB_VDDIO_3V3_1V8,VDD_PMU_CLDO,VDD_PMU_3V3_O,VPTX_VP,VDD_PMU_SYSLDO,VDD_PMU_3V3_IN3,VDD_PMU_1V5_IN,VDD_BUCK_1V5_IN,VDD_PMU_3V3_IN1,VDD_PMU_3V3_IN2,RF_VDD_TX2G_3P3_0,RF_VDD_TX2G_3P3_1,RF_VDD_TX5G_3P3_0,RF_VDD_TX5G_3P3_1";
		PinArrayUInt result = TheInst.DCVS().Pins(pin).OpenKelDetect(0.5,0.5);//检测OSD

		vector<string> pinname = SplitPinList(pin);
//		result.ShowPinArrayData();
		for(unsigned int i = 0; i < pinname.size(); i++){
			TheSoft.Flow().TestLimit(pinname[i] ,result ,0 ,0 ,2,2010,"","POWER_OSD",20100000+i,PhxAPI::E_FailStop,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
		}
		PHXSYS_LOGSTR_TRACE("-------------------------------------------");
		PHXSYS_LOGSTR_TRACE("------------------TEST END-----------------");
		PHXSYS_LOGSTR_TRACE("-------------------------------------------");


    }

};
REGISTER_TESTCLASS("PROG_INIT",PROG_INIT)



