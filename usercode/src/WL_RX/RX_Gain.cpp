/*
 * RX_Gain.cpp
 *
 *  Created on: 2021年10月29日
 *      Author: huawei
 */
#include<time.h>
#include<windows.h>
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
#include "DSP_test_ABB.h"
#include "Globle_Var.h"
#include <synchapi.h>
#include "CCFFT.h"


class RX_Gain: public TestClass{
public:



	void init(){

	    }


    void execute(){


//    	LONGLONG starttime = start();

//		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
//		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
		TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing
//		end(starttime,"---------------Test config power apply:");

//		starttime = start();
    	double hil[30],lowl[30];
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
		char RF_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
		char Ana_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};

		bool complexGainFlag = 0;

		CCIQResults IQResults;
		IQMeasureAttribute MeasureResult;
		double* Spectrum_I = 0;
		double* Spectrum_Q = 0;
		double dwPeakPower_I = 0, dwPeakPower_Q = 0;
		double dwTestFreq = 0;                        //指定测试的频点
		double pathloss[4];
		double GAIN_I[4] = {0};
		double GAIN_Q[4] = {0};
		int index = 0;
		//1. Get test item information
		string testname = TheSoft.Flow().Test().GetCurrentTestName();
		Get_TestItem_Info(testname.c_str(), RF_Test_Data);
		Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
		Get_Signal_Name(RF_Test_Data, RF_SrcSignal, Ana_CapSignal);


//		string tmp = RF_SrcPin;
//		string tmp1 = Ana_CapPin;
//		string tmp2 = RF_SrcSignal;
//		string tmp3 = Ana_CapSignal;
//
//		cout << "RF_SrcPin	:"<<tmp << endl;
//		cout << "Ana_CapPin	:"<<tmp1 << endl;
//		cout << "RF_SrcSignal	:"<<tmp2 << endl;
//		cout << "Ana_CapSignal	:"<<tmp3 << endl;


		complexGainFlag = RF_Test_Data.bComplexGain;

		//2. Get Passloss
		Read_Pathloss(RF_Test_Data, pathloss) ;

		//3. DUT register setting:  WL_5G_CAL_Code, PLL, Filter
		//iMode：2G/5G；iBand = Fre 全是枚举类型，以一定的格式区分 参考TX_Power_Trim_Function函数
		Set_RF_RX_Pll_BW( (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
		Set_RF_RX_GainMode(RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);
//		end(starttime,"---------------d2s:");


		CCRFTester.SelectSites("Site0, Site2");
//		starttime = start();
		CapUtilitySites0();
//		end(starttime,"---------------Relay1:");

//		QueryPerformanceCounter(&litmp);
//		T_sp = litmp.QuadPart;
//		T_delay = (T_sp - T_st)/ddfreq*1e3;
//		cout << "stoptime_relay_first: ---------------------------" << T_delay<< "ms ----------------------------------------" << endl;
//		QueryPerformanceCounter(&litmp);
//		T_st = litmp.QuadPart;

		//4. Load source and capture signal
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Configure();
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Start();

		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Configure();

		//5. Trigger capture signal, get wave, calculate gain
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Start();
		//这边需要根据read回来的数据做一些运算(有IQ数据，通过mx库计算得到Spectrum))
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Read(&IQResults);
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Stop();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Stop();


//		QueryPerformanceCounter(&litmp);
//		T_sp = litmp.QuadPart;
//		T_delay = (T_sp - T_st)/ddfreq*1e3;
//		cout << "stoptime_RF_config_1: ---------------------------" << T_delay<< "ms ----------------------------------------" << endl;
//		QueryPerformanceCounter(&litmp);
//		T_st = litmp.QuadPart;


#ifdef semi_parallel_en
		CCRFTester.SelectSites("Site1, Site3");
		CapUtilitySites1();

//		QueryPerformanceCounter(&litmp);
//		T_sp = litmp.QuadPart;
//		T_delay = (T_sp - T_st)/ddfreq*1e3;
//		cout << "stoptime_relay_second: ---------------------------" << T_delay<< "ms ----------------------------------------" << endl;
//		QueryPerformanceCounter(&litmp);
//		T_st = litmp.QuadPart;


		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Configure();
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Start();

		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Configure();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Start();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Read(&IQResults);
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Stop();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Stop();

		CapUtilitySites0();                                                      //recover Rely state

#endif
		dwTestFreq = RF_Test_Data.tyRXTest.dDf1;     //请在这里输入要获取Power的频点
		FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)

				MeasureResult = IQResults[site_id];
				//PlotCurve( &MeasureResult, "Gain");
				FFTFromIQData( &MeasureResult, &Spectrum_I, &Spectrum_Q);  //根据IQ数据分别I路FFT，Q路FFT
				GetPowerofSpecifiedFreq((double*)Spectrum_I, (double*)Spectrum_Q, dwTestFreq, RF_Test_Data.tyCapSigSet.dSampleRate, RF_Test_Data.tyCapSigSet.dSampleSize, dwPeakPower_I, dwPeakPower_Q, 7);
				GAIN_I[site_id]=dwPeakPower_I-RF_Test_Data.tyRXTest.dP1+pathloss[site_id];
				GAIN_Q[site_id]=dwPeakPower_Q-RF_Test_Data.tyRXTest.dP1+pathloss[site_id];
				//以下可以打印PeakPower，如果要保存数据注意多site需要分配数组
//				cout<<"GainStep_I:"<<GAIN_I[site_id]<<endl;
//				cout<<"GainStep_Q:"<<GAIN_Q[site_id]<<endl;
//				TheSoft.Flow().TestLimit( Ana_CapPin,site_id, GAIN_I[site_id], 62.5, 67.5,6,6203, "dB","GAIN_I" , 62030000);
//				TheSoft.Flow().TestLimit( Ana_CapPin,site_id, GAIN_Q[site_id], 62.5, 67.5,6,6203, "dB","GAIN_Q" , 62030001);

				TheSoft.Flow().TestLimit( Ana_CapPin,site_id, GAIN_I[site_id], lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], "dB", string(Test_Item[0]), Test_number[0]);
				TheSoft.Flow().TestLimit( Ana_CapPin,site_id, GAIN_Q[site_id], lowl[1], hil[1],Hard_Bin[1],Soft_Bin[1], "dB", string(Test_Item[1]), Test_number[1]);
		FOREACH_ACTIVESITE_END

		//6. Save Gain, retrieve gain of LNA stage

		RX_GAIN_I_LIST.Insert(RF_Test_Data.cRxFreq,RF_Test_Data.cGainMode,sizeof(GAIN_I)/sizeof(double),GAIN_I);
		RX_GAIN_Q_LIST.Insert(RF_Test_Data.cRxFreq,RF_Test_Data.cGainMode,sizeof(GAIN_Q)/sizeof(double),GAIN_Q);

		double* Gain_I_Max;
		double* Gain_Q_Max;
		index = RX_GAIN_I_LIST.FindIndex(RF_Test_Data.cRxFreq,RF_Test_Data.cGainMode);
		Gain_I_Max = RX_GAIN_I_LIST.Get(RF_Test_Data.cRxFreq,index);
		Gain_Q_Max = RX_GAIN_Q_LIST.Get(RF_Test_Data.cRxFreq,index);

		index = RX_GAIN_I_LIST.FindIndex(RF_Test_Data.cRxFreq,RF_Test_Data.cGainMode);

		if(index == 0){
			FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
				if(strstr(testname.c_str() , "C0_RFI_")!=NULL){
					RX_GAIN_MAX_I_C0[RF_Test_Data.iBand][site_id] = GAIN_I[site_id];
				}
				else if(strstr(testname.c_str() , "C1_RFI_")!=NULL){
					RX_GAIN_MAX_I_C1[RF_Test_Data.iBand][site_id] = GAIN_I[site_id];
				}
			FOREACH_ACTIVESITE_END
		}

		double GainStep_I = 0;
		double GainStep_Q = 0;
		if(RF_Test_Data.iLNA_Stage_Num >= 0){
			Last_Gain_I = RX_GAIN_I_LIST.Get(RF_Test_Data.cRxFreq,index-1);
			Last_Gain_Q = RX_GAIN_Q_LIST.Get(RF_Test_Data.cRxFreq,index-1);

			FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)

				GainStep_I = Last_Gain_I[site_id] - GAIN_I[site_id];
				GainStep_Q = Last_Gain_Q[site_id] - GAIN_Q[site_id];
//				cout<<"GainStep_I:"<<GainStep_I<<endl;
//				cout<<"GainStep_Q:"<<GainStep_Q<<endl;
				TheSoft.Flow().TestLimit( Ana_CapPin,site_id,  GainStep_I, lowl[2], hil[2],Hard_Bin[2],Soft_Bin[2], "dB", string(Test_Item[2]),Test_number[2]);
				TheSoft.Flow().TestLimit( Ana_CapPin,site_id, GainStep_Q, lowl[3], hil[3],Hard_Bin[3],Soft_Bin[3], "dB", string(Test_Item[3]),Test_number[3]);

			FOREACH_ACTIVESITE_END
		}
    }

};
REGISTER_TESTCLASS("RX_Gain",RX_Gain)


