/*
 * RX_NF.cpp
 *
 *  Created on: 2021年10月29日
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
#include "CCFFT.h"

class RX_NF: public TestClass{
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
    	    char RF_NF_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    	    char Ana_NF_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};

    	    CCIQResults IQResults;
    	    IQMeasureAttribute MeasureResult;

    	    double Noise_i=0,Noise_q=0;
    	    double Noise2_i=0,Noise2_q=0;
    	    double NF_I=0,NF_Q=0;
    	    double NF2_I=0,NF2_Q=0;

    	    double Noise_Freq_L;
    	    double Noise_Freq_H;
    	    double NF2_Freq_L;
    	    double NF2_Freq_H;


    	    long Noise_Bin_L;
    	    long Noise_Bin_H;
    	    long NF2_Bin_L;
    	    long NF2_Bin_H;

    	    //1. Get test item information
    	    string testname = TheSoft.Flow().Test().GetCurrentTestName();
    	    Get_TestItem_Info(testname.c_str(), RF_Test_Data);
    	    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    	    Get_Signal_Name(RF_Test_Data, RF_NF_SrcSignal, Ana_NF_CapSignal);

    	    if(strcmp(testname.c_str(),"WL_RX_2G_H_C0_RFI_NF")== 0){
				RF_SWITCH_Control("SW_U3_V2,SW_U4_V1","SW_U3_V1,SW_U3_V3,SW_U4_V2,SW_U4_V3");
			}
    	    else if(strcmp(testname.c_str(),"WL_RX_2G_H_C1_RFI_NF")== 0){
				RF_SWITCH_Control("SW_U1_V2,SW_U2_V1","SW_U1_V1,SW_U1_V3,SW_U2_V2,SW_U2_V3");
			}


    	    if(strstr(testname.c_str(),"2G")!=NULL){
    	        Noise_Freq_L=4e6;
    	        Noise_Freq_H=6e6;
    	        NF2_Freq_L=14e6;
    	        NF2_Freq_H=16e6;
    	    }
    	    else{
    	        Noise_Freq_L=1.1e6;
    	        Noise_Freq_H=1.9e6;
    	        NF2_Freq_L=6.1e6;
    	        NF2_Freq_H=6.9e6;
    	    }

    	    //2. DUT register setting:  WL_5G_CAL_Code, PLL, Filter
    	    Set_RF_RX_Pll_BW( (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
    	    Set_RF_RX_GainMode(RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);

    	    CCRFTester.SelectSites("Site0, Site2");
    	    CapUtilitySites0();
    	    //3. Disconnect RF source pin
    	    //CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_NF_SrcSignal).Stop();

    	    //4 Load capture signal, Trigger capture signal, get wave calculate
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Configure();
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Start();
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Read(&IQResults);
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Stop();
#ifdef semi_parallel_en
    	    CCRFTester.SelectSites("Site1, Site3");
    	    CapUtilitySites1();
    	//    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_NF_SrcSignal).Stop();
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Configure();
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Start();
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Read(&IQResults);
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Stop();
    	    CapUtilitySites0();                                                      //recover Rely state
#endif
    	    //Calculate NF
    	    //FOR EACHSITE
    	    long FFT_Size=RF_Test_Data.tyCapSigSet.dSampleSize;
    	    double Res_Freq_NF=RF_Test_Data.tyCapSigSet.dSampleRate/RF_Test_Data.tyCapSigSet.dSampleSize;
    	    double *Inreal = new double[FFT_Size];
    	    double *Inimag = new double[FFT_Size];
    	    double *SpectrumTemp_I = new double[FFT_Size];
    	    double *SpectrumTemp_Q = new double[FFT_Size];
    	    FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)

				Testsoftbin[site_id] = 1;//softbin flag
				MeasureResult = IQResults[site_id];
				//PlotCurve( &MeasureResult, "NF");
				if(MeasureResult.actualSamples >= FFT_Size)                         //ensure the samples number larger than FFT_SIZE
				{
					for(int i = 0; i < FFT_Size; i++)
					{
						Inreal[i] = MeasureResult.pComplexData[i].real;
						Inimag[i] = MeasureResult.pComplexData[i].imaginary;
					}
				}
	//            api->Set_curve_data("NF_real", 0, 1/40.96e6, 4096, Inreal);   //打印FFT波形
	//            api->Set_curve_data("NF_image", 0, 1/40.96e6, 4096, Inimag);

	//            MT_FFT( FFT_Size, Inreal, Inreal, SpectrumTemp_I);
	//            MT_FFT( FFT_Size, Inimag, Inimag, SpectrumTemp_Q);
				CCDSP::FFT(Inreal,FFT_Size,SpectrumTemp_I,CCDSP::_0_Ohm);
				CCDSP::FFT(Inimag,FFT_Size,SpectrumTemp_Q,CCDSP::_0_Ohm);

				for(unsigned i =0;i<FFT_Size;++i)
				{
					SpectrumTemp_I[i] = pow(SpectrumTemp_I[i],2);
					SpectrumTemp_Q[i] = pow(SpectrumTemp_Q[i],2);
				}

				Noise_Bin_L = int(Noise_Freq_L/Res_Freq_NF+0.5);
				Noise_Bin_H = int(Noise_Freq_H/Res_Freq_NF+0.5);
				NF2_Bin_L = int(NF2_Freq_L/Res_Freq_NF+0.5);
				NF2_Bin_H = int(NF2_Freq_H/Res_Freq_NF+0.5);

				Noise_i = std::accumulate(SpectrumTemp_I+Noise_Bin_L, SpectrumTemp_I+Noise_Bin_H, 0.0) + 1e-20;
				Noise_q = std::accumulate(SpectrumTemp_Q+Noise_Bin_L, SpectrumTemp_Q+Noise_Bin_H, 0.0) + 1e-20;
				NF_I=10*log10(1000*Noise_i/50)-10*log10((Noise_Bin_H-Noise_Bin_L)*Res_Freq_NF)+174-60;
				NF_Q=10*log10(1000*Noise_q/50)-10*log10((Noise_Bin_H-Noise_Bin_L)*Res_Freq_NF)+174-60;

				Noise2_i = std::accumulate(SpectrumTemp_I+NF2_Bin_L, SpectrumTemp_I+NF2_Bin_H, 0.0) + 1e-20;
				Noise2_q = std::accumulate(SpectrumTemp_Q+NF2_Bin_L, SpectrumTemp_Q+NF2_Bin_H, 0.0) + 1e-20;
				NF2_I=10*log10(1000*Noise2_i/50)-10*log10((NF2_Bin_H-NF2_Bin_L)*Res_Freq_NF)+174-60;
				NF2_Q=10*log10(1000*Noise2_q/50)-10*log10((NF2_Bin_H-NF2_Bin_L)*Res_Freq_NF)+174-60;

				if(NF_I>NF2_I){
					NF_I=NF2_I;
				}
				if(NF_Q>NF2_Q){
					NF_Q=NF2_Q;
				}
//    	            TheSoft.Flow().TestLimit( Ana_CapPin, site_id, NF_I, 0.1, 11,6,6214, "dB", "NF_I",62140000);
//					TheSoft.Flow().TestLimit( Ana_CapPin, site_id, NF_Q,  0.1, 11,6,6214, "dB", "NF_Q",62140001);

				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, NF_I, lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], "dB", Test_Item[0],Test_number[0]);
				TheSoft.Flow().TestLimit( Ana_CapPin, site_id, NF_Q, lowl[1], hil[1],Hard_Bin[1],Soft_Bin[1], "dB", Test_Item[1],Test_number[1]);


    		FOREACH_ACTIVESITE_END
    	    delete[] Inreal;
    	    delete[] Inimag;
    	    delete[] SpectrumTemp_I;
    	    delete[] SpectrumTemp_Q;


    	    //5. Output test result
    	    if(strstr(testname.c_str(),"2G_H_C0")!=NULL){
//    	    	Excute_Test("3V3_VDDN_FUNC","3V3_VIHLR_VOHLR_IOHLR","TIM_RF_INIT","XXX");
    	    	RF_SWITCH_Control("SW_U1_V1,SW_U2_V2","SW_U1_V2,SW_U1_V3,SW_U2_V1,SW_U2_V3");//
//    	    	Excute_Test("3V3_VDDN_FUNC","3V3_VIHLR_VOHLR_IOHLR","TIM_RF_INIT","WLAN_2G_RX_C0_RFI");
    	    }
    	    else if(strstr(testname.c_str(),"2G_H_C1")!=NULL){
//    	    	Excute_Test("3V3_VDDN_FUNC","3V3_VIHLR_VOHLR_IOHLR","TIM_RF_INIT","XXX");
    	    	RF_SWITCH_Control("SW_U3_V1,SW_U4_V2","SW_U3_V2,SW_U3_V3,SW_U4_V1,SW_U4_V3");
//    	    	Excute_Test("3V3_VDDN_FUNC","3V3_VIHLR_VOHLR_IOHLR","TIM_RF_INIT","WLAN_2G_RX_C1_RFI");
    	    }
    	    else if(strstr(testname.c_str(),"5G_B_C0")!=NULL){
//    	    	Excute_Test("3V3_VDDN_FUNC","3V3_VIHLR_VOHLR_IOHLR","TIM_RF_INIT","XXX");
    	    	RF_SWITCH_Control("SW_U2_V3","SW_U2_V1,SW_U2_V2");
//   	    	Excute_Test("3V3_VDDN_FUNC","3V3_VIHLR_VOHLR_IOHLR","TIM_RF_INIT","WLAN_5G_RX_C0");
    	    }
    	    else if(strstr(testname.c_str(),"5G_B_C1")!=NULL){
//    	    	Excute_Test("3V3_VDDN_FUNC","3V3_VIHLR_VOHLR_IOHLR","TIM_RF_INIT","XXX");
    	    	RF_SWITCH_Control("SW_U4_V3","SW_U4_V1,SW_U4_V2");
//    	    	Excute_Test("3V3_VDDN_FUNC","3V3_VIHLR_VOHLR_IOHLR","TIM_RF_INIT","WLAN_5G_RX_C1");
    	    }

    }

};
REGISTER_TESTCLASS("RX_NF",RX_NF)



