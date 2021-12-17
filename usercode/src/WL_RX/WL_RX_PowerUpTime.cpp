/*
 * WL_RX_PowerUpTime.cpp
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

class WL_RX_PowerUpTime: public TestClass{
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
		char RF_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
		char Ana_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};

		bool site0_flag = false;

		double PowerUp_Time_I;
		double PowerUp_Time_Q;

		unsigned int sites[MAX_SITES] = {0};
		vector<int> sites_vec = TheSoft.Sites().Active().GetActiveSites();
		unsigned int active_sites_size = TheSoft.Sites().Active().GetActiveSiteCount();


		CCIQResults IQResults;
		IQMeasureAttribute MeasureResult;
		double dwTestFreq = 0.0;

		//1. Get test item information
		string testname = TheSoft.Flow().Test().GetCurrentTestName();
		Get_TestItem_Info(testname.c_str(), RF_Test_Data);
		Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
		Get_Signal_Name(RF_Test_Data, RF_SrcSignal, Ana_CapSignal);

		//2. DUT register setting: BW, PLL, gain mode
		Set_RF_RX_Pll_BW( (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
		Set_RF_RX_GainMode(RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);

		CCRFTester.SelectSites("Site0, Site2");
		CapUtilitySites0();
		//3. Load source and capture signal
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Configure();
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Start();

		//api->Execute_test("WL_RX_POWER_DOWN");
		Excute_Test("","3V3_VIHLR_VOHLR_IOHLR","TIM_SETUP","WL_power_down");

		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Configure();
		//5. Trigger capture signal, get wave, calculate setting time
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Start();

		if(strstr(testname.c_str(),"C0")!=NULL){
			//api->Execute_test("WL_RX_C0_SETUPTIME");
			Excute_Test("","3V3_VIHLR_VOHLR_IOHLR","TIM_SETUP","WL_C0_SetupTime");

		}
		else{
			//api->Execute_test("WL_RX_C1_SETUPTIME");
			Excute_Test("","3V3_VIHLR_VOHLR_IOHLR","TIM_SETUP","WL_C1_SetupTime");
		}

		CCRFTester.SelectSites("Site0, Site2");
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Read(&IQResults);
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Stop();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Stop();

#ifdef semi_parallel_en
		CCRFTester.SelectSites("Site1, Site3");
		CapUtilitySites1();
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Configure();
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Start();
		//api->Execute_test("WL_RX_POWER_DOWN");
		Excute_Test("","3V3_VIHLR_VOHLR_IOHLR","TIM_SETUP","WL_power_down");

		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Configure();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Start();


		if(strstr(testname.c_str(),"C0")!=NULL){
			Excute_Test("","3V3_VIHLR_VOHLR_IOHLR","TIM_SETUP","WL_C0_SetupTime");
			//api->Execute_test("WL_RX_C0_SETUPTIME");
		}
		else{
			Excute_Test("","3V3_VIHLR_VOHLR_IOHLR","TIM_SETUP","WL_C1_SetupTime");
			//api->Execute_test("WL_RX_C1_SETUPTIME");
		}


		CCRFTester.SelectSites("Site1, Site3");
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Read(&IQResults);
		CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Stop();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Stop();
		CapUtilitySites0();                                                      //recover Rely state
#endif
		//FOR EACHSITE
		dwTestFreq = RF_Test_Data.tyRXTest.dDf1;
		FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)

				MeasureResult = IQResults[site_id];

				Calc_PowerUpTime(&MeasureResult,RF_Test_Data.tyCapSigSet.dSampleRate,&PowerUp_Time_I,&PowerUp_Time_Q);

				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, PowerUp_Time_I, lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], "ns", Test_Item[0],Test_number[0]);
				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, PowerUp_Time_Q, lowl[1], hil[1],Hard_Bin[1],Soft_Bin[1], "ns", Test_Item[1], Test_number[1]);
		FOREACH_ACTIVESITE_END
    }

    void WriteData(const char* pszFileName,double dData[],long lDataSize)
    {
    	char szPath[64] = {0};
    	sprintf(szPath,"%s.txt",pszFileName);
    	ofstream fout(szPath);
    //	fout.seekp(ios::end);
    	for(long i = 0;i<lDataSize;i++)
    	{
    		fout << dData[i] << endl;
    	}
    	fout.close();
    }

    //计算指定level起来的时间
    int Get_PowerUpTime(double *IQMeasData,long SampleSize,double SampleRate,  double *PowerUp_Time)
    {
        double waveDC = 0;
        double IQMeasDataSum = 0;
        //double *refwave = new double[128];
        double refamp = 0;
        double refSum = 0;
        double refSize = 128;
        double comSum = 0;
        double comamp = 0;
        double relative = 0;

        for(int i = 0;i<SampleSize;i++)
        {
            IQMeasDataSum = IQMeasDataSum + IQMeasData[i];
        }
        waveDC = IQMeasDataSum / SampleSize;
        for(int j = 0;j<SampleSize;j++)
        {
            IQMeasData[j] = IQMeasData[j]-waveDC;
        }
        for(int k =SampleSize-refSize; k<SampleSize;k++)
        {
            refSum = IQMeasData[k]*IQMeasData[k]+refSum;
        }
        refamp = refSum/refSize;
        /************************************************************************/
        int nStartIndex = 0;
        for(int m = 10;m < SampleSize-10;m++)
        {
            comSum = 0;
            for(int n = 0;n<10;n++)
            {
                comSum += IQMeasData[m+n];
            }
            comamp = comSum/10;
            if(fabs(IQMeasData[m] - comamp) > 0.05)
            {
                nStartIndex = m;
                break;
            }
        }


        for(int m = nStartIndex;m < SampleSize-refSize;m++)
        {
            comSum = 0;
            for(int n = 0;n<refSize;n++)
            {
                comSum = IQMeasData[m+n]*IQMeasData[m+n]+comSum;
            }
            comamp = comSum/refSize;
            relative = comamp/refamp;

            if(refamp>0&&relative>=0.891&&relative<1.585)
            {
                *PowerUp_Time = m/SampleRate*1e9 - 3300;   //33 cycles,10MHz pattern
                break;
            }
        }


        /****************************************************************/

    //    for(int m = nStartIndex;m<SampleSize-refSize;m++)
    //    {
    //        comSum = 0;
    //        for(int n =0; n<refSize;n++)
    //        {
    //            comSum = IQMeasData[m+n]*IQMeasData[m+n]+comSum;
    //        }
    //        comamp = comSum/refSize;
    //
    //        relative = comamp/refamp;
    //        if(refamp>0&&relative>=0.891&&relative<1.585)
    //        {
    //            *PowerUp_Time = (m - nStartIndex - 4)/SampleRate*1e9;
    //            break;
    //        }
    //    }

        if((*PowerUp_Time < 0)&&(*PowerUp_Time > -3300))//change by CC ZJ
        {
            *PowerUp_Time = 123.4;
        }
        else if(*PowerUp_Time <= -3300)
        {
            *PowerUp_Time = 0;
        }


        //delete[] refwave;

        return 0;
    }
    int Calc_PowerUpTime(IQMeasureAttribute *IQMeasData,double SampleRate,double *PowerUp_Time_I,double *PowerUp_Time_Q)
    {
        double *Inreal, *Inimag;

        *PowerUp_Time_I = 123.4;
        *PowerUp_Time_Q = 123.4;

        if(IQMeasData->actualSamples > 0)                                           //ensure the samples number must larger than 0.
        {
            Inreal = new double[IQMeasData->actualSamples];
            Inimag = new double[IQMeasData->actualSamples];
            memset(Inreal, 0.0, sizeof(double)*IQMeasData->actualSamples);
            memset(Inimag, 0.0, sizeof(double)*IQMeasData->actualSamples);

            SplitIQData(IQMeasData, Inreal, Inimag);

        //    double tempI[4096] = {0};
        //    double tempQ[4096] = {0};
        //    for(int i =0;i<IQMeasData->actualSamples;i++)
        //    {
        //        tempI[i] = Inreal[i];
        //        tempQ[i] = Inimag[i];
        //    }
//            char PowerUpTime_r[32]={"\0"};
//            char PowerUpTime_i[32]={"\0"};
//            sprintf(PowerUpTime_r, "PowerUpTime_Real_Data_%d", site_id);
//            sprintf(PowerUpTime_i, "PowerUpTime_imag_Data_%d", site_id);
//
//            WriteData(PowerUpTime_r,Inreal,IQMeasData->actualSamples);
//            WriteData(PowerUpTime_i,Inimag,IQMeasData->actualSamples);

            Get_PowerUpTime(Inreal,IQMeasData->actualSamples,SampleRate, PowerUp_Time_I);
            Get_PowerUpTime(Inimag,IQMeasData->actualSamples,SampleRate, PowerUp_Time_Q);

            delete[] Inreal;
            delete[] Inimag;
        }
        return 0;
    }

};
REGISTER_TESTCLASS("WL_RX_PowerUpTime",WL_RX_PowerUpTime)





