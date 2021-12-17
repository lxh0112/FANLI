/*
 * ABB_DAC_IQ.cpp
 *
 *  Created on: Nov 23, 2021
 *      Author: Administrator
 */


#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include "D2S_ABB_Module.h"
#include "DSP_test_ABB.h"
#include "Globle_Var.h"
#include "CCS08F.h"
#include "Excel.h"
#include "RegDef.h"
#include "d2sProtocolSSI.h"
#include "UserDef.h"
#include <synchapi.h>


using namespace PhxAPI;

class ABB_DAC_IQ: public TestClass{
public:


    void init(){

    }

    void execute(){

//		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
//		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
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
    	    char RF_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    	    char Ana_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};

    	    CCIQResults IQResults;
    	    IQMeasureAttribute MeasureResult;
    	    unsigned int FunBin=0;

    	    double tone_Vp_i;
    	    double tone_Vp_q;
    	    double dc_offset_i;
    	    double dc_offset_q;
    	    double snr_i;
    	    double snr_q;
    	    double thd_i;
    	    double thd_q;
    	    double sfdr_i;
    	    double sfdr_q;
    	    double sinad_i;
    	    double sinad_q;
    	    double enob_i;
    	    double enob_q;
    	    double GainMismatch;
    	    const unsigned distortion_num = 3;
    	    unsigned samplesize;

    	    //1. Get test item information
    	    //string testname = TheSoft.Flow().Test().GetCurrentTestName();
    	    string testname = TheSoft.Flow().Test().GetCurrentTestName();
    	    Get_TestItem_Info(testname.c_str(), RF_Test_Data);
    	    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    	    Get_Signal_Name(RF_Test_Data, RF_SrcSignal, Ana_CapSignal);



    		int UtilitySites[8] = {51,24,20,65,19,33,11,56};
    		for(uint32_t i=0;i<8;i++)
    		{
    			TheInst.Util().SetRelayState(UtilitySites[i], E_UTIL_STATE_OFF);
    		}

    	    WL_DAC_SRC_DATA_module();

    	     if(strstr(testname.c_str(),"_DEM")!=NULL){
    	         if(strstr(testname.c_str(),"C0")!=NULL){
    	             WL_DAC_DEM_C0_LPF_Module();
    	         }
    	         else{
    	             WL_DAC_DEM_C1_LPF_Module();
    	         }
    	     }
    	     else{
    	         if(strstr(testname.c_str(),"C0")!=NULL){
    	             WL_DAC_C0_LPF_Module();
    	         }
    	         else{
    	             WL_DAC_C1_LPF_Module();
    	         }
    	     }

    	    CCRFTester.SelectSites("Site0,Site2");
    	    CapUtilitySites0();
    	    Sleep(5);                                                          //add for relay stable @20210408
    	    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Configure();
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
    	    CapUtilitySites0();                                                      //recover Relay state
#endif
    	    FunBin = RF_Test_Data.tyABBTest.dSigFreq/(2*RF_Test_Data.tyCapSigSet.dSampleRate/RF_Test_Data.tyCapSigSet.dSampleSize);
    	    FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)

    	        MeasureResult = IQResults[site_id];

    	        //PlotCurve( &MeasureResult, "DAC");

    	        samplesize=MeasureResult.actualSamples;
    	        dacDynamicCalc(FunBin, &MeasureResult,samplesize, tone_Vp_i, tone_Vp_q, dc_offset_i, dc_offset_q,
    	                  snr_i, snr_q, thd_i, thd_q, sfdr_i, sfdr_q, sinad_i, sinad_q, enob_i, enob_q, GainMismatch, distortion_num);

    	        TheSoft.Flow().TestLimit ( Ana_CapPin,site_id, sinad_i, lowl[0], hil[0], Hard_Bin[0],Soft_Bin[0],"dB", Test_Item[0], Test_number[0]);
				TheSoft.Flow().TestLimit ( Ana_CapPin,site_id, sinad_q, lowl[1], hil[1], Hard_Bin[1],Soft_Bin[1],"dB", Test_Item[1], Test_number[1]);
				TheSoft.Flow().TestLimit ( Ana_CapPin,site_id, enob_i, lowl[2], hil[2], Hard_Bin[2],Soft_Bin[2],Units[2], Test_Item[2],Test_number[2]);
				TheSoft.Flow().TestLimit ( Ana_CapPin,site_id, enob_q, lowl[3], hil[3], Hard_Bin[3],Soft_Bin[3],Units[3], Test_Item[3], Test_number[3]);
				TheSoft.Flow().TestLimit ( Ana_CapPin,site_id, sfdr_i, lowl[4], hil[4], Hard_Bin[4],Soft_Bin[4],"dB", Test_Item[4],  Test_number[4]);
				TheSoft.Flow().TestLimit ( Ana_CapPin,site_id, sfdr_q, lowl[5], hil[5], Hard_Bin[5],Soft_Bin[5],"dB", Test_Item[5],  Test_number[5]);
				TheSoft.Flow().TestLimit ( Ana_CapPin,site_id, snr_i, lowl[6], hil[6], Hard_Bin[6],Soft_Bin[6],"dB", Test_Item[6],  Test_number[6]);
				TheSoft.Flow().TestLimit ( Ana_CapPin,site_id, snr_q, lowl[7], hil[7], Hard_Bin[7],Soft_Bin[7],"dB", Test_Item[7],  Test_number[7]);
				TheSoft.Flow().TestLimit ( Ana_CapPin,site_id, thd_i, lowl[8], hil[8], Hard_Bin[8],Soft_Bin[8],"dB", Test_Item[8],  Test_number[8]);
				TheSoft.Flow().TestLimit ( Ana_CapPin,site_id, thd_q, lowl[9], hil[9], Hard_Bin[9],Soft_Bin[9],"dB", Test_Item[9],  Test_number[9]);
				TheSoft.Flow().TestLimit ( Ana_CapPin,site_id, tone_Vp_i, lowl[10], hil[10], Hard_Bin[10],Soft_Bin[10],"V", Test_Item[10],  Test_number[10]);
				TheSoft.Flow().TestLimit ( Ana_CapPin,site_id, tone_Vp_q, lowl[11], hil[11],Hard_Bin[11],Soft_Bin[11], "V", Test_Item[11], Test_number[11]);
				TheSoft.Flow().TestLimit ( Ana_CapPin,site_id, GainMismatch, lowl[12], hil[12], Hard_Bin[12],Soft_Bin[12],"dB", Test_Item[12], Test_number[12]);


    		FOREACH_ACTIVESITE_END

    }
};
REGISTER_TESTCLASS("ABB_DAC_IQ",ABB_DAC_IQ)






