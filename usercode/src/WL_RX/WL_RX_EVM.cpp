/*
 * WL_RX_EVM.cpp
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
#include "Globle_Var.h"
#include <synchapi.h>
#include "Capture_Function.h"

class WL_RX_EVM: public TestClass{
public:

	void init(){

	    }
    void execute(){

//		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
//		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
		TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing

    	double hil[30],lowl[30];
//		char *Test_Item[30],*Units[30];
    	vector<string> Test_Item;
    	vector<string> Units;
		int  Test_number[30];

		int Soft_Bin[30];
		int Hard_Bin[30];
		Read_Limit(lowl,hil,Test_Item,Test_number,Units,Soft_Bin,Hard_Bin);
		//Parameter definition here
		tyTestData RF_Test_Data;
		char RF_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
		char Ana_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
		char RF_EVM_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
		char Ana_EVM_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};

		double EVM;

		CCMxWlanResults MxWlanResults;
		WlanResultsAttribute MeasureResult;

		//1. Get test item information
		string testname = TheSoft.Flow().Test().GetCurrentTestName();
		Get_TestItem_Info(testname.c_str(), RF_Test_Data);
		Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
		Get_Signal_Name(RF_Test_Data, RF_EVM_SrcSignal, Ana_EVM_CapSignal);

		//2. DUT register setting: BW, PLL, gain mode
		Set_RF_RX_Pll_BW( (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
		Set_RF_RX_GainMode(RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);

		CCRFTester.SelectSites("Site0, Site2");
		CapUtilitySites0();
		//3. Load source and capture signal
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_EVM_SrcSignal).Configure();
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_EVM_SrcSignal).Start();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_EVM_CapSignal).Configure();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_EVM_CapSignal).Start();
	//    api->sleep(0.01);
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_EVM_CapSignal).Read(&MxWlanResults);
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_EVM_CapSignal).Stop();
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_EVM_SrcSignal).Stop();
#ifdef semi_parallel_en
		CCRFTester.SelectSites("Site1, Site3");
		CapUtilitySites1();

		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_EVM_SrcSignal).Configure();
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_EVM_SrcSignal).Start();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_EVM_CapSignal).Configure();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_EVM_CapSignal).Start();
	//    api->sleep(0.01);
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_EVM_CapSignal).Read(&MxWlanResults);
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_EVM_CapSignal).Stop();
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_EVM_SrcSignal).Stop();
		CapUtilitySites0();                                                      //recover Rely state
#endif
		FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)

				MeasureResult = MxWlanResults[site_id];
				EVM=MeasureResult.OFDMM.CompositeRMSEVM.dCompositeRMSEVMMean;
				TheSoft.Flow().TestLimit( RF_SrcPin, site_id, 100*pow(10,(EVM/20)), lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], Units[0], Test_Item[0],Test_number[0]);
		FOREACH_ACTIVESITE_END
    }

};
REGISTER_TESTCLASS("WL_RX_EVM",WL_RX_EVM)


