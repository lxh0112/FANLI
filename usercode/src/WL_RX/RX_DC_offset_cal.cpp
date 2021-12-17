/*
 * RX_DC_offset_cal.cpp
 *
 *  Created on: 2021年10月29日
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

using namespace PhxAPI;

class RX_DC_offset_cal: public TestClass {
public:

	void init() {

	}

	void execute() {

//		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
//		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
		TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing


		double hil[30], lowl[30];
//		char *Test_Item[30], *Units[30];
		vector<string> Test_Item;
		vector<string> Units;
		int Test_number[30];
		int Soft_Bin[30];
		int Hard_Bin[30];
		Read_Limit(lowl, hil, Test_Item, Test_number, Units, Soft_Bin,
				Hard_Bin);
		//Parameter definition here
		tyTestData RF_Test_Data;
		//const char* testname = NULL;
		char RF_SrcPin[_MAX_NAME_SIZE_RF] = { "\0" };
		char Ana_CapPin[_MAX_NAME_SIZE_RF] = { "\0" };
		char RF_GC_SrcSignal[_MAX_NAME_SIZE_RF] = { "\0" };
		char Ana_CapSignal[_MAX_NAME_SIZE_RF] = { "\0" };

		CCIQResults IQResults;
		IQMeasureAttribute MeasureResult;
		double I_LSB_mv;
		double Q_LSB_mv;

		//1. Get test item information
		string testname = TheSoft.Flow().Test().GetCurrentTestName();
		Get_TestItem_Info(testname.c_str(), RF_Test_Data);
		Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
		Get_Signal_Name(RF_Test_Data, RF_GC_SrcSignal, Ana_CapSignal);

		if (strstr(testname.c_str(), "2G") != NULL) {
			I_LSB_mv = 5.0;
			Q_LSB_mv = 5.0;
		} else {
			I_LSB_mv = 5.3;
			Q_LSB_mv = 5.3;
		}

		//2. Get Passloss
		//pathloss = Read_Pathloss(testname);   //CC的ReadEeprom函数

		//3. DUT register setting: PLL, GAIN_MODE
		Set_RF_RX_Pll_BW((emMode) RF_Test_Data.iMode,
				(emRX_Band) RF_Test_Data.iBand, RF_Test_Data.dBW,
				RF_Test_Data.cChannel);
		Set_RF_RX_GainMode(RF_Test_Data.cGainMode, (emMode) RF_Test_Data.iMode,
				RF_Test_Data.cChannel);

		if (strstr(testname.c_str(), "C0") != NULL) {
			d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
			d2sProtocolSSI d2s_test;
			d2s_test.SSI_write(0x200, 0x2000, false);
			d2s_test.SSI_write(0x202, 0x90, false);
			d2s_test.SSI_write(0x74, 0x8080);
			d2s::d2s_LABEL_END();
		} else {
			d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
			d2sProtocolSSI d2s_test;
			d2s_test.SSI_write(0x200, 0x2000, false);
			d2s_test.SSI_write(0x202, 0x90, false);
			d2s_test.SSI_write(0x78, 0x8080);
			d2s::d2s_LABEL_END();
		}

		CCRFTester.SelectSites("Site0, Site2");
		CapUtilitySites0();
		Sleep(5);                               //add for relay stable @20210408
		//4. Load source and capture signal
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Configure();

		//5. Trigger capture signal, get wave, calculate gain
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Start();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Read(&IQResults);
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Stop();
#ifdef semi_parallel_en
		CCRFTester.SelectSites("Site1, Site3");
		CapUtilitySites1();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Configure();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Start();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Read(&IQResults);
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Stop();
		CapUtilitySites0();                                 //recover Rely state
#endif
		long FFT_Size = RF_Test_Data.tyCapSigSet.dSampleSize;
		double *Inreal = new double[FFT_Size];
		double *Inimag = new double[FFT_Size];
		double *SpectrumTemp_I = new double[FFT_Size];
		double *SpectrumTemp_Q = new double[FFT_Size];
		map<int, long long> DCOC_Code;
		double vOffset_I_Pre = -999;
		double vOffset_Q_Pre = -999;
		FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
			vOffset_I_Pre = -999;
			vOffset_Q_Pre = -999;
			Testsoftbin[site_id] = 1;                                 //softbin flag
			MeasureResult = IQResults[site_id];						  //IQResults[site_id];
			//            //PlotCurve( &MeasureResult, "DCOC");
			if(MeasureResult.actualSamples >= FFT_Size)//Ensure the samples number larger than FFT_SIZE
			{
				for(int i = 0; i < FFT_Size; i++)
				{
					Inreal[i] = MeasureResult.pComplexData[i].real;
					Inimag[i] = MeasureResult.pComplexData[i].imaginary;
				}


				vOffset_I_Pre = std::accumulate(Inreal, Inreal+FFT_Size, 0.0)/FFT_Size*2;
				vOffset_Q_Pre = std::accumulate(Inimag, Inimag+FFT_Size, 0.0)/FFT_Size*2;

				long long DCOC_I_Cal_Code = 0x80 - floor(vOffset_I_Pre*1000/I_LSB_mv+0.5);
				long long DCOC_Q_Cal_Code = 0x80 - floor(vOffset_Q_Pre*1000/Q_LSB_mv+0.5);

				if(DCOC_I_Cal_Code>255) {
					DCOC_I_Cal_Code=255;
				}
				else if(DCOC_I_Cal_Code<0) {
					DCOC_I_Cal_Code=0;
				}

				if(DCOC_Q_Cal_Code>255) {
					DCOC_Q_Cal_Code=255;
				}
				else if(DCOC_Q_Cal_Code<0) {
					DCOC_Q_Cal_Code=0;
				}
				DCOC_Code[site_id]= DCOC_I_Cal_Code+(DCOC_Q_Cal_Code<<8);

//				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, vOffset_I_Pre, lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], "V", Test_Item[0], Test_number[0]);
//				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, vOffset_Q_Pre, lowl[1], hil[1],Hard_Bin[1],Soft_Bin[1], "V", Test_Item[1],Test_number[1]);
			}
			TheSoft.Flow().TestLimit( Ana_CapPin, site_id, vOffset_I_Pre, -0.4, 0.4,6,6201, "V", "vOffset_I_Pre", 62010000);
			TheSoft.Flow().TestLimit( Ana_CapPin, site_id, vOffset_Q_Pre, -0.4, 0.4,6,6201, "V", "vOffset_Q_Pre",62010001);
		FOREACH_ACTIVESITE_END
		TheSoft.Flow().TestLimit(Ana_CapPin, DCOC_Code, 62010002,"DCOC_Code",0,40000 );
//		TheSoft.Flow().TestLimit(Ana_CapPin, DCOC_Code, lowl[2], hil[2],Hard_Bin[2], Soft_Bin[2], Units[2], Test_Item[2],Test_number[2]);

		if (strstr(testname.c_str(), "C0") != NULL) {
			d2s::d2s_LABEL_BEGIN("dynamic", d2s_WorkMode);
			d2sProtocolSSI d2s_test;
			d2s_test.SSI_writeDynamic(0x74, DCOC_Code, "write"); //SSI_write(0x74, 0x8080);
			d2s::d2s_LABEL_END();
		} else {
			d2s::d2s_LABEL_BEGIN("dynamic", d2s_WorkMode);
			d2sProtocolSSI d2s_test;
			d2s_test.SSI_writeDynamic(0x78, DCOC_Code, "write");
			d2s::d2s_LABEL_END();
		}

		CCRFTester.SelectSites("Site0, Site2");
		CapUtilitySites0();
		Sleep(5);                               //add for relay stable @20210408
		//4. Load source and capture signal
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Configure();

		//5. Trigger capture signal, get wave, calculate gain
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Start();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Read(&IQResults);
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Stop();

#ifdef semi_parallel_en
		CCRFTester.SelectSites("Site1, Site3");
		CapUtilitySites1();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Configure();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Start();
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Read(&IQResults);
		CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Stop();
		CapUtilitySites0();                                 //recover Rely state
#endif
		FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)

		MeasureResult = IQResults[site_id];                //IQResults[site_id];
		//PlotCurve( &MeasureResult, "DCOC");
		if(MeasureResult.actualSamples >= FFT_Size)//Ensure the samples number larger than FFT_SIZE
		{
			for(int i = 0; i < FFT_Size; i++)
			{
				Inreal[i] = MeasureResult.pComplexData[i].real;
				Inimag[i] = MeasureResult.pComplexData[i].imaginary;
			}
		}

		double vOffset_I_Post = std::accumulate(Inreal, Inreal+FFT_Size, 0.0)/FFT_Size*2;
		double vOffset_Q_Post = std::accumulate(Inimag, Inimag+FFT_Size, 0.0)/FFT_Size*2;
//		TheSoft.Flow().TestLimit( Ana_CapPin,site_id, vOffset_I_Post, -0.05, 0.05,6,6201, "V", "vOffset_I_Post",62010003);
//		TheSoft.Flow().TestLimit( Ana_CapPin,site_id, vOffset_Q_Post, -0.05, 0.05,6,6201, "V", "vOffset_Q_Post",62010004);

		TheSoft.Flow().TestLimit( Ana_CapPin,site_id, vOffset_I_Post, lowl[3], hil[3],Hard_Bin[3],Soft_Bin[3], "V", Test_Item[3],Test_number[3]);
		TheSoft.Flow().TestLimit( Ana_CapPin,site_id, vOffset_Q_Post, lowl[4], hil[4],Hard_Bin[4],Soft_Bin[4], "V", Test_Item[4], Test_number[4]);
		if(Testsoftbin[site_id]!=1) {
#if 0
			api->Set_result_bin(Testsoftbin[site_id]);
#endif
		}

		FOREACH_ACTIVESITE_END

		delete[] Inreal;
		delete[] Inimag;
		delete[] SpectrumTemp_I;
		delete[] SpectrumTemp_Q;

	}

};
REGISTER_TESTCLASS("RX_DC_offset_cal", RX_DC_offset_cal)

