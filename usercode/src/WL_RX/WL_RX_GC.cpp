/*
 * WL_RX_GC.cpp
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


class WL_RX_GC: public TestClass{
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
		//const char* testname = NULL;
		string strTestName = "";
		char RF_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
		char Ana_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
		char RF_GC_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
		char Ana_GC_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};

		bool complexGainFlag = 0;

		CCIQResults IQResults;
		IQMeasureAttribute MeasureResult;
		double dwTestFreq = 0;
		double* Spectrum_I = 0;
		double* Spectrum_Q = 0;
		double dwPeakPower_I = 0, dwPeakPower_Q = 0;
		double Gain_I_GC;
		double Gain_Q_GC;
		double pathloss[4];
		double* Gain_I_Max;
		double* Gain_Q_Max;
		int index = 0;

		//1. Get test item information
		string testname = TheSoft.Flow().Test().GetCurrentTestName();
		Get_TestItem_Info(testname.c_str(), RF_Test_Data);
		Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
		Get_Signal_Name(RF_Test_Data, RF_GC_SrcSignal, Ana_GC_CapSignal);

		complexGainFlag = RF_Test_Data.bComplexGain;

		Read_Pathloss(RF_Test_Data, pathloss) ;

		//2. DUT register setting: BW, PLL, gain mode
		Set_RF_RX_Pll_BW( (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
		Set_RF_RX_GainMode(RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);

		CCRFTester.SelectSites("Site0, Site2");
		CapUtilitySites0();
		//3. Load source and capture signal
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_GC_SrcSignal).Configure();
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_GC_SrcSignal).Start();

		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_GC_CapSignal).Configure();

		//4. Trigger capture signal, get wave, calculate gain
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_GC_CapSignal).Start();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_GC_CapSignal).Read(&IQResults);
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_GC_SrcSignal).Stop();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_GC_CapSignal).Stop();
#ifdef semi_parallel_en
		CCRFTester.SelectSites("Site1, Site3");
		CapUtilitySites1();
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_GC_SrcSignal).Configure();
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_GC_SrcSignal).Start();

		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_GC_CapSignal).Configure();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_GC_CapSignal).Start();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_GC_CapSignal).Read(&IQResults);
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_GC_SrcSignal).Stop();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_GC_CapSignal).Stop();
		CapUtilitySites0();                                                      //recover Rely state
#endif
		//5. Calculate GC
		index = RX_GAIN_I_LIST.FindIndex(RF_Test_Data.cRxFreq,RF_Test_Data.cGainMode);
		Gain_I_Max = RX_GAIN_I_LIST.Get(RF_Test_Data.cRxFreq,index);
		Gain_Q_Max = RX_GAIN_Q_LIST.Get(RF_Test_Data.cRxFreq,index);
		dwTestFreq = RF_Test_Data.tyRXTest.dDf1;     //请在这里输入要获取Power的频点
		strTestName = testname;
		if(strTestName.find("WL_RX_5G") < strTestName.length())
		{

		}
		else
		{
			FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
	//            int site_id = api->Get_active_site();
				MeasureResult = IQResults[site_id];
				//PlotCurve( &MeasureResult, "GC");
	            FFTFromIQData( &MeasureResult, &Spectrum_I, &Spectrum_Q);  //根据IQ数据分别I路FFT，Q路FFT
				GetPowerofSpecifiedFreq((double*)Spectrum_I, (double*)Spectrum_Q, dwTestFreq, RF_Test_Data.tyCapSigSet.dSampleRate, RF_Test_Data.tyCapSigSet.dSampleSize, dwPeakPower_I, dwPeakPower_Q);
				Gain_I_GC = dwPeakPower_I - RF_Test_Data.tyRXTest.dP1+pathloss[site_id];
				Gain_Q_GC = dwPeakPower_Q - RF_Test_Data.tyRXTest.dP1+pathloss[site_id];
				//以下可以打印PeakPower，如果要保存数据注意多site需要分配数组

				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, Gain_I_Max[site_id], lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], "dB", Test_Item[0], Test_number[0]);
				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, Gain_Q_Max[site_id], lowl[1], hil[1],Hard_Bin[1],Soft_Bin[1], "dB", Test_Item[1],Test_number[1]);
				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, Gain_I_Max[site_id]-Gain_I_GC, lowl[2], hil[2],Hard_Bin[2],Soft_Bin[2], "dB", Test_Item[2],Test_number[2]);
				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, Gain_Q_Max[site_id]-Gain_Q_GC, lowl[3], hil[3],Hard_Bin[3],Soft_Bin[3], "dB", Test_Item[3], Test_number[3]);

			FOREACH_ACTIVESITE_END
		}
    }

};
REGISTER_TESTCLASS("WL_RX_GC",WL_RX_GC)


