/*
 * RX_Selectivity.cpp
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


class RX_Selectivity: public TestClass{
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
		char RF_Sel_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
		char Ana_Sel_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};

		CCIQResults IQResults;
		IQMeasureAttribute MeasureResult;
		double dwTestFreq = 0;
		double* Spectrum_I = 0;
		double* Spectrum_Q = 0;
		double dwPeakPower_I = 0.0, dwPeakPower_Q = 0.0;
		double Selectivity_Gain_I;
		double Selectivity_Gain_Q;
		double pathloss[4];
		double* Gain_I_Max;
		double* Gain_Q_Max;
		int index = 0;

		//1. Get test item information
		string testname = TheSoft.Flow().Test().GetCurrentTestName();
		Get_TestItem_Info(testname.c_str(), RF_Test_Data);
		Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
		Get_Signal_Name(RF_Test_Data, RF_Sel_SrcSignal, Ana_Sel_CapSignal);

		//2. Get Passloss
		Read_Pathloss(RF_Test_Data,pathloss);

		//3. DUT register setting:  WL_5G_CAL_Code, PLL, Filter
		Set_RF_RX_Pll_BW( (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
		Set_RF_RX_GainMode(RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);

		CCRFTester.SelectSites("Site0, Site2");
		CapUtilitySites0();
		//4 Load source and capture signal
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_Sel_SrcSignal).Configure();
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_Sel_SrcSignal).Start();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_Sel_CapSignal).Configure();

		//5. Trigger capture signal, get wave calculate
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_Sel_CapSignal).Start();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_Sel_CapSignal).Read(&IQResults);
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_Sel_SrcSignal).Stop();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_Sel_CapSignal).Stop();

#ifdef semi_parallel_en
		CCRFTester.SelectSites("Site1, Site3");
		CapUtilitySites1();
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_Sel_SrcSignal).Configure();
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_Sel_SrcSignal).Start();

		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_Sel_CapSignal).Configure();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_Sel_CapSignal).Start();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_Sel_CapSignal).Read(&IQResults);
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_Sel_SrcSignal).Stop();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_Sel_CapSignal).Stop();
		CapUtilitySites0();                                                      //recover Rely state
#endif
		index = RX_GAIN_I_LIST.FindIndex(RF_Test_Data.cRxFreq,RF_Test_Data.cGainMode);
		Gain_I_Max = RX_GAIN_I_LIST.Get(RF_Test_Data.cRxFreq,index);
		Gain_Q_Max = RX_GAIN_Q_LIST.Get(RF_Test_Data.cRxFreq,index);
		dwTestFreq = RF_Test_Data.tyRXTest.dDf1;
		FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
	//            int site_id = api->Get_active_site();
				MeasureResult = IQResults[site_id];
				FFTFromIQData( &MeasureResult, &Spectrum_I, &Spectrum_Q);  //根据IQ数据分别I路FFT，Q路FFT
				GetPowerofSpecifiedFreq((double*)Spectrum_I, (double*)Spectrum_Q, dwTestFreq, RF_Test_Data.tyCapSigSet.dSampleRate, RF_Test_Data.tyCapSigSet.dSampleSize, dwPeakPower_I, dwPeakPower_Q);
				Selectivity_Gain_I = dwPeakPower_I - RF_Test_Data.tyRXTest.dP1 + pathloss[site_id];
				Selectivity_Gain_Q = dwPeakPower_Q - RF_Test_Data.tyRXTest.dP1 + pathloss[site_id];

				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, Gain_I_Max[site_id] - Selectivity_Gain_I, lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], "dB", Test_Item[0],Test_number[0]);
				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, Gain_Q_Max[site_id] - Selectivity_Gain_Q, lowl[1], hil[1],Hard_Bin[1],Soft_Bin[1], "dB", Test_Item[1], Test_number[1]);

		FOREACH_ACTIVESITE_END

		//6 Disconnect RF source pin

		//7. Output test result
    }

};
REGISTER_TESTCLASS("RX_Selectivity",RX_Selectivity)







