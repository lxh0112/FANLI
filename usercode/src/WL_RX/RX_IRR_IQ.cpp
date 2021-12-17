/*
 * RX_IRR_IQ.cpp
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
#include "Execute_Test.h"


class RX_IRR_IQ_cpp: public TestClass{
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
    	    char RF_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    	    char Ana_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    	    char RF_IRR_IQ_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    	    char Ana_IRR_IQ_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};

    	    CCRfmxSpecAnResults SpectrumResults;
    	    SpecAnResultAttribute MeasureResult;
    	    double dwTestFreq = 0, dwTestFreq_IRR = 0;
    	    double dwSignalPower = 0;
    	    double dwImagePower = 0;

    	    //1. Get test item information
    	    string testname = TheSoft.Flow().Test().GetCurrentTestName();
    	    Get_TestItem_Info(testname.c_str(), RF_Test_Data);
    	    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    	    Get_Signal_Name(RF_Test_Data, RF_IRR_IQ_SrcSignal, Ana_IRR_IQ_CapSignal);

    	    //2. DUT register setting:  WL_5G_CAL_Code, PLL, Filter
    	    Set_RF_RX_Pll_BW((emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
    	    Set_RF_RX_GainMode(RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);

    	    CCRFTester.SelectSites("Site0, Site2");
    	    CapUtilitySites0();
    	    TheInst.Wait(0.005);                                                          //add for relay stable @20210408
    	    //3. Load source and capture signal
    	    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IRR_IQ_SrcSignal).Configure();
    	    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IRR_IQ_SrcSignal).Start();

    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_IQ_CapSignal).Configure();

    	    //4. Trigger capture signal, get wave calculate
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_IQ_CapSignal).Start();
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_IQ_CapSignal).Read(&SpectrumResults);
    	    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IRR_IQ_SrcSignal).Stop();
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_IQ_CapSignal).Stop();
    	    //MeasureResult = SpectrumResults[0];
#ifdef semi_parallel_en
    	    CCRFTester.SelectSites("Site1, Site3");
    	    CapUtilitySites1();
    	    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IRR_IQ_SrcSignal).Configure();
    	    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IRR_IQ_SrcSignal).Start();

    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_IQ_CapSignal).Configure();
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_IQ_CapSignal).Start();
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_IQ_CapSignal).Read(&SpectrumResults);
    	    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IRR_IQ_SrcSignal).Stop();
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_IQ_CapSignal).Stop();
    	    CapUtilitySites0();                                                      //recover Rely state
#endif
    	    //Calculate IRR
    	    dwTestFreq = RF_Test_Data.tyRXTest.dDf1;
    	    dwTestFreq_IRR = -1 * RF_Test_Data.tyRXTest.dDf1;
    	    FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
    	        MeasureResult = SpectrumResults[site_id];
    	        if(MeasureResult.dFrequencyIncrement > 0)
    	        {
    	            int nBin = (dwTestFreq - MeasureResult.dInitiaFrequency)/MeasureResult.dFrequencyIncrement;
    	            int nBin_Image = (dwTestFreq_IRR - MeasureResult.dInitiaFrequency)/MeasureResult.dFrequencyIncrement;

    	            Calc_Power_dbm(&MeasureResult, nBin, 3, &dwSignalPower, 0);
    	            Calc_Power_dbm(&MeasureResult, nBin_Image, 3, &dwImagePower, 0);
    	        }
//    	        TheSoft.Flow().TestLimit(Ana_CapPin,site_id, dwSignalPower-dwImagePower, 30, 40,6,6221, "dB", "IRR",62210000);

    	        TheSoft.Flow().TestLimit(Ana_CapPin,site_id, dwSignalPower-dwImagePower, lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], "dB", Test_Item[0],Test_number[0]);
			FOREACH_ACTIVESITE_END



    }

};
REGISTER_TESTCLASS("RX_IRR_IQ_cpp",RX_IRR_IQ_cpp)


