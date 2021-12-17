/*
 * RX_IIP3_Fund_Tone_Inband.cpp
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
#include "Capture_Function.h"


class RX_IIP3_Fund_Tone_Inband: public TestClass{
public:

	void init(){

	    }
    void execute(){

//			TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
//			TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
			TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing



    		double hil[30],lowl[30];
//    	    char *Test_Item[30],*Units[30];
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
    	    char RF_IIP3_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    	    char Ana_IIP3_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};

    	    CCIQResults IQResults;
    	    IQMeasureAttribute MeasureResult;
    	    double* Spectrum_I = 0;
    	    double* Spectrum_Q = 0;
    	    double out_Power_I =0.0, out_Power_Q =0.0;
    	    double dwIMD3Val_I = 0.0, dwIMD3Val_Q = 0.0;
    	    double dwIIP3Val_I = 0.0, dwIIP3Val_Q = 0.0;
    	    double pathloss[4];
    	    double pathloss_average = 0.0;
    	    double pathloss_IQ = 0.0;
    	    double GAIN_I = 0.0;
    	    double GAIN_Q = 0.0;
    	    int site_cnt = 0;
    	    //1. Get test item information
    	    string testname = TheSoft.Flow().Test().GetCurrentTestName();
    	    Get_TestItem_Info(testname.c_str(), RF_Test_Data);
    	    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    	    Get_Signal_Name(RF_Test_Data, RF_IIP3_SrcSignal, Ana_IIP3_CapSignal);

    	    if(strstr(testname.c_str() , "C0")!= NULL){
    	        pathloss_IQ = 1.0 ;   //only for dual tone
    	    }
    	    else{
    	        pathloss_IQ = 2.0 ;  ////only for dual tone
    	    }
    	    //2. Get Passloss
    	    Read_Pathloss(RF_Test_Data, pathloss) ;
    	    //取pathloss的平均值
    	    FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)

    	        pathloss_average=pathloss_average+pathloss[site_id];
    	        site_cnt = site_cnt + 1;
    		FOREACH_ACTIVESITE_END
    	    if(site_cnt)
    	        pathloss_average=pathloss_average/site_cnt - pathloss_IQ;   //1dB for IQ loss

    	    //3. DUT register setting:  WL_5G_CAL_Code, PLL, Filter
    	    //iMode：2G/5G；iBand = Fre 全是枚举类型，以一定的格式区分 参考TX_Power_Trim_Function函数
    	    Set_RF_RX_Pll_BW( (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
    	    Set_RF_RX_GainMode(RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);

    	    CCRFTester.SelectSites("Site0, Site2");
    	    CapUtilitySites0();
    	    CCRFSITE_DOUBLE dFreq = selectFrequency(RF_Test_Data.cRxFreq);
    	    CCRFSITE_DOUBLE dPower = RF_Test_Data.tyRXTest.dP1+pathloss_average + 3;
    	    //4. Load source and capture signal
    	    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP3_SrcSignal).Configure();
//    	    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP3_SrcSignal).Update(selectFrequency(RF_Test_Data.cRxFreq),RF_Test_Data.tyRXTest.dP1+pathloss_average + 3);  //3dB for dual tone
    	    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP3_SrcSignal).Update(dFreq,dPower);
    	    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP3_SrcSignal).Start();

    	    //5. Trigger capture signal, get wave, calculate IIP3
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP3_CapSignal).Configure();
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP3_CapSignal).Start();
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP3_CapSignal).Read(&IQResults);
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP3_CapSignal).Stop();
    	    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP3_SrcSignal).Stop();
#ifdef semi_parallel_en
    	    CCRFTester.SelectSites("Site1, Site3");
    	    CapUtilitySites1();
    	    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP3_SrcSignal).Configure();
    	    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP3_SrcSignal).Update(selectFrequency(RF_Test_Data.cRxFreq),RF_Test_Data.tyRXTest.dP1+pathloss_average + 3);  //3dB for dual tone
    	    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP3_SrcSignal).Start();

    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP3_CapSignal).Configure();
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP3_CapSignal).Start();
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP3_CapSignal).Read(&IQResults);

    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP3_CapSignal).Stop();
    	    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP3_SrcSignal).Stop();
    	    CapUtilitySites0();                                                      //recover Rely state
#endif
    	    FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)

    	            MeasureResult = IQResults[site_id];
    	//            PlotCurve( &MeasureResult, "IIP3");
    	            FFTFromIQData( &MeasureResult, &Spectrum_I, &Spectrum_Q);  //根据IQ数据分别I路FFT，Q路FFT
    	            GetIMD3FromIQData((double*)Spectrum_I, (double*)Spectrum_Q, RF_Test_Data.tyRXTest.dDf1, RF_Test_Data.tyRXTest.dDf2,\
    	                              RF_Test_Data.tyCapSigSet.dSampleRate, RF_Test_Data.tyCapSigSet.dSampleSize, dwIMD3Val_I, dwIMD3Val_Q, out_Power_I, out_Power_Q);
    	            GAIN_I = out_Power_I - RF_Test_Data.tyRXTest.dP1 + pathloss_IQ;
    	            GAIN_Q = out_Power_Q - RF_Test_Data.tyRXTest.dP1 + pathloss_IQ;
    	            dwIIP3Val_I = dwIMD3Val_I / 2 + RF_Test_Data.tyRXTest.dP1;
    	            dwIIP3Val_Q = dwIMD3Val_Q / 2 + RF_Test_Data.tyRXTest.dP1;

//    	            TheSoft.Flow().TestLimit( Ana_CapPin, site_id, GAIN_I, 32, 38,6,6215, "dB", "GAIN_I",62150000);
//					TheSoft.Flow().TestLimit( Ana_CapPin, site_id, GAIN_Q, 32, 38,6,6215, "dB", "GAIN_Q",62150001);
//					TheSoft.Flow().TestLimit( Ana_CapPin, site_id, dwIIP3Val_I, -22, 10,6,6215, "dB", "IIP_I",62150002);
//					TheSoft.Flow().TestLimit( Ana_CapPin, site_id, dwIIP3Val_Q, -22, 10,6,6215, "dB", "IIP_Q",62150003);
    	            TheSoft.Flow().TestLimit( Ana_CapPin, site_id, GAIN_I, lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], "dB", Test_Item[0],Test_number[0]);
    	            TheSoft.Flow().TestLimit( Ana_CapPin, site_id, GAIN_Q, lowl[1], hil[1],Hard_Bin[1],Soft_Bin[1], "dB", Test_Item[1],Test_number[1]);
    	            TheSoft.Flow().TestLimit( Ana_CapPin, site_id, dwIIP3Val_I, lowl[2], hil[2],Hard_Bin[2],Soft_Bin[2], "dB", Test_Item[2],Test_number[2]);
    	            TheSoft.Flow().TestLimit( Ana_CapPin, site_id, dwIIP3Val_Q, lowl[3], hil[3],Hard_Bin[3],Soft_Bin[3], "dB", Test_Item[3],Test_number[3]);
    		FOREACH_ACTIVESITE_END

    }

};
REGISTER_TESTCLASS("RX_IIP3_Fund_Tone_Inband",RX_IIP3_Fund_Tone_Inband)


