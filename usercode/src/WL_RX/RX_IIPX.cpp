/*
 * RX_IIPX.cpp
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

class RX_IIPX: public TestClass{
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
		char RF_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
		char Ana_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
		char RF_IIPX_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
		char Ana_IIPX_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};

		long IIPx_Order = 0;
		double BB_IIPX_IQ_Freq = 0.0;

		CCIQResults IQResults;
		IQMeasureAttribute MeasureResult;
		double* Spectrum_I = 0;
		double* Spectrum_Q = 0;
		double dwPeakPower_I = 0.0, dwPeakPower_Q = 0.0;
		double dwIIPXVal_I = 0.0, dwIIPXVal_Q = 0.0;
		double pathloss[4];
		double pathloss_average=0.0;
		double pathloss_IQ = 0.0;
		double* Gain_I_Max;
		double* Gain_Q_Max;
		int index = 0;
		int site_cnt = 0;

		//1. Get test item information
		string testname = TheSoft.Flow().Test().GetCurrentTestName();
		Get_TestItem_Info(testname.c_str(), RF_Test_Data);
		Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
		Get_Signal_Name(RF_Test_Data, RF_IIPX_SrcSignal, Ana_IIPX_CapSignal);

		IIPx_Order = RF_Test_Data.iIIPX_Order;

		if(strstr(testname.c_str() , "C0")!= NULL){
			pathloss_IQ = 3.0 ;
		}
		else{
			pathloss_IQ = 3.5 ;
		}

		//2. Get Passloss
		Read_Pathloss(RF_Test_Data, pathloss) ;
		//取pathloss的平均值
		FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
			//int site_id = api->Get_active_site();
			pathloss_average=pathloss_average+pathloss[site_id];
			site_cnt = site_cnt+1;
		FOREACH_ACTIVESITE_END

		if(site_cnt)
			pathloss_average=pathloss_average/site_cnt - pathloss_IQ;

		if(RF_SrcPin =="WL_RF_RFI_5G_C0"){
			pathloss_average = pathloss_average / 1.5;
		}
		//3. DUT register setting:  WL_5G_CAL_Code, PLL, Filter
		Set_RF_RX_Pll_BW( (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
		Set_RF_RX_GainMode(RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);

		//get IIPX Freq
		if(IIPx_Order == 2)
		{
			BB_IIPX_IQ_Freq = fabs(RF_Test_Data.tyRXTest.dDf1 - RF_Test_Data.tyRXTest.dDf2);
		}
		else
		{
			BB_IIPX_IQ_Freq = 2*(RF_Test_Data.tyRXTest.dDf1 - RF_Test_Data.dLO_Freq) - RF_Test_Data.tyRXTest.dDf2;
		}

		CCRFTester.SelectSites("Site0, Site2");
		CapUtilitySites0();
		//4 Load source signal
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIPX_SrcSignal).Configure();
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIPX_SrcSignal).Update(RF_Test_Data.tyRXTest.dDf1-1e6,RF_Test_Data.tyRXTest.dP1 + pathloss_average + 3);
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIPX_SrcSignal).Start();
		//5. Load capture signal, trigger capture signal, calculate gain
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIPX_CapSignal).Configure();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIPX_CapSignal).Start();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIPX_CapSignal).Read(&IQResults);
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIPX_SrcSignal).Stop();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIPX_CapSignal).Stop();
#ifdef semi_parallel_en
		CCRFTester.SelectSites("Site1, Site3");
		CapUtilitySites1();
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIPX_SrcSignal).Configure();
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIPX_SrcSignal).Update(RF_Test_Data.tyRXTest.dDf1-1e6,RF_Test_Data.tyRXTest.dP1 + pathloss_average + 3);
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIPX_SrcSignal).Start();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIPX_CapSignal).Configure();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIPX_CapSignal).Start();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIPX_CapSignal).Read(&IQResults);
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIPX_SrcSignal).Stop();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIPX_CapSignal).Stop();
		CapUtilitySites0();                                                      //recover Rely state
#endif
		//Calculate IIPX
		index = RX_GAIN_I_LIST.FindIndex(RF_Test_Data.cRxFreq,RF_Test_Data.cGainMode);
		Gain_I_Max = RX_GAIN_I_LIST.Get(RF_Test_Data.cRxFreq,index);
		Gain_Q_Max = RX_GAIN_Q_LIST.Get(RF_Test_Data.cRxFreq,index);
		FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
	//            int site_id = api->Get_active_site();
				MeasureResult = IQResults[site_id];
	//            PlotCurve( &MeasureResult, "IIP2");
				FFTFromIQData( &MeasureResult, &Spectrum_I, &Spectrum_Q);  //根据IQ数据分别I路FFT，Q路FFT
				GetPowerofSpecifiedFreq((double*)Spectrum_I, (double*)Spectrum_Q, BB_IIPX_IQ_Freq, RF_Test_Data.tyCapSigSet.dSampleRate, RF_Test_Data.tyCapSigSet.dSampleSize, dwPeakPower_I, dwPeakPower_Q);

				dwIIPXVal_I = 2*RF_Test_Data.tyRXTest.dP1 - dwPeakPower_I + Gain_I_Max[site_id];
				dwIIPXVal_Q = 2*RF_Test_Data.tyRXTest.dP1 - dwPeakPower_Q + Gain_Q_Max[site_id];

//				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, Gain_I_Max[site_id], 62, 68,6,6218, "dB", "Gain_I",62180000);
//				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, Gain_Q_Max[site_id], 62, 68,6,6218,"dB", "Gain_Q",62180001);
//
//				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, dwIIPXVal_I, 20, 70,6,6218, "dBm", "dwIIPXVal_I",62180002);
//				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, dwIIPXVal_Q, 20, 70,6,6218, "dBm", "dwIIPXVal_Q",62180003);

				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, Gain_I_Max[site_id], lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], Units[0], Test_Item[0],Test_number[0]);
				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, Gain_Q_Max[site_id], lowl[1], hil[1],Hard_Bin[1],Soft_Bin[1], Units[1], Test_Item[1],Test_number[1]);

				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, dwIIPXVal_I, lowl[2], hil[2],Hard_Bin[2],Soft_Bin[2], Units[2], Test_Item[2],Test_number[2]);
				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, dwIIPXVal_Q, lowl[3], hil[3],Hard_Bin[3],Soft_Bin[3], Units[3], Test_Item[3],Test_number[3]);

		FOREACH_ACTIVESITE_END

	}
};
REGISTER_TESTCLASS("RX_IIPX",RX_IIPX)


