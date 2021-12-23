/*
 * ABB_ADC_IQ.cpp
 *
 *  Created on: Nov 23, 2021
 *      Author: Administrator
 */


#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
//#include "D2S_CAL_Module.h"
#include "Globle_Var.h"
#include "CCS08F.h"
#include "Excel.h"
#include "RegDef.h"
#include "d2sProtocolSSI.h"
#include "UserDef.h"
#include "D2S_ABB_Module.h"
#include "Test_ABB.h"
#include <cfloat>

using namespace PhxAPI;

class ABB_ADC_IQ: public TestClass{
public:


    void init(){

    }

    void execute(){

    	double hil[30],lowl[30];
//		char *Test_Item[30],*Units[30];
		vector<string> Test_Item;
		vector<string> Units;
		int  Test_number[30];
		int Soft_Bin[30];
		int Hard_Bin[30];
//		Read_Limit(lowl,hil,Test_Item,Test_number,Units,Soft_Bin,Hard_Bin);

//		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
		TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing

		//Parameter definition here
		tyTestData RF_Test_Data;
		//const char* testname = NULL;
		char Ana_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
		char RF_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
		char Ana_Src_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
		char RF_Cap_Signal[_MAX_NAME_SIZE_RF] = {"\0"};

		int CalType;
		CSiteLong pcal_status;
		CSiteLong pcal_status_C1;
		CSiteLong pCOMP_CAL_CODE_A1;
		CSiteLong pCOMP_CAL_CODE_A2;
		CSiteLong pCOMP_CAL_CODE_A3;
		CSiteLong pCOMP_CAL_CODE;
		CSiteLong pWL_ADC_CAP_STS;
		CSiteLong WL_PV_Sensor;
		CSiteLong myWave;
		double nData[2048];
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
		double enob_iq;
		double Amp_i;
		double Amp_q;
		double GainMismatch;
		double distortion_num = 4;
		int FunBin=0;
		int SpurBin=0;

		bool site0_flag = false;
		unsigned int sitestmp[4] = {0,0,0,0};
		unsigned int sites[MAX_SITES] = {0};

//		vector<int> Sites_Init = TheSoft.Sites().Active().GetActiveSites();
//		unsigned int active_sites_size = TheSoft.Sites().Active().GetActiveSiteCount();
//		unsigned int active_sites_cnt = 0;
//		for(unsigned int i=0;i<active_sites_size;i++)
//		{
//			sitestmp[i]=Sites_Init[i];
//		}

		//1. Get test item information
//		string testname = TheSoft.Flow().Test().GetCurrentTestName();
//		Get_TestItem_Info(testname.c_str(), RF_Test_Data);
//		Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
//		Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);

//		if (strstr(testname.c_str(), "80M") != NULL) {
//			CalType = 0; //calType_Normal;
//		}
//		else if (strstr(testname.c_str(), "SS") != NULL) {
//			CalType = 2; //cal_Type_SS;
//		}
//		else if (strstr(testname.c_str(), "LV1") != NULL) {
//			CalType = 4; //calType_LV1;
//		}
//		else if (strstr(testname.c_str(), "LV") != NULL) {
//			CalType = 1; //calType_LV;
//		}
//		else if (strstr(testname.c_str(), "160M") != NULL) {
//			CalType = 3; //calType_Nocal;
//		}


//		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
//		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();

//
//		int UtilitySites[8] = {51,24,20,65,19,33,11,56};
//
//		for(uint32_t i=0;i<8;i++)
//		{
//			TheInst.Util().SetRelayState(UtilitySites[i], E_UTIL_STATE_ON);
//		}


		//2 DUT register setting for diff CalType
//		if(CalType == cal_Type_SS){
//
//			d2s::d2s_LABEL_BEGIN( "ssi", d2s_WorkMode);
//			d2sProtocolSSI d2s_test;
//			d2s_test.SSI_write(0x200,0x2000,false);
//			d2s_test.SSI_write(0x202,0x94,false);
//			d2s_test.SSI_write(0x350,0x10a0);
//			d2s_test.SSI_write(0x35c,0x2800);
//			d2s_test.SSI_write(0x364,0x10a0);
//			d2s_test.SSI_write(0x370,0x2800);
//			d2s::d2s_LABEL_END();
	//        FOREACH_ACTIVE_SITE() {
	//            int site_id = api->Get_active_site();
	//            if(PV_SENSOR_C0_CODE(site_id,0)>110){
	//                ADC_Reg0[site_id]=0x10a0;
	//                ADC_Reg3[site_id]=0x2800;
	//            }
	//            else{
	//                ADC_Reg0[site_id]=0x18a0;
	//                ADC_Reg3[site_id]=0x2A00;
	//            }
	//        }
	//        d2s::d2s_LABEL_BEGIN( "dynamic", d2s_WorkMode);
	//        d2sProtocolSSI d2s_test;
	//        d2s_test.SSI_write(0x200,0x2000,false);
	//        d2s_test.SSI_write(0x202,0x94,false);
	//        d2s_test.SSI_writeDynamic(0x350,ADC_Reg0,"write1");
	//        d2s_test.SSI_writeDynamic(0x35c,ADC_Reg3,"write2");
	//        d2s_test.SSI_writeDynamic(0x364,ADC_Reg0,"write3");
	//        d2s_test.SSI_writeDynamic(0x370,ADC_Reg3,"write4");
	//        d2s::d2s_LABEL_END();
//
//		}
//		else if(CalType == calType_Nocal){
//
//			if(RF_Test_Data.tyABBTest.dABBSampleRate==160e6){
//				d2s::d2s_LABEL_BEGIN( "ssi", d2s_WorkMode);
//				d2sProtocolSSI d2s_test;
//				d2s_test.SSI_write(0x200,0x2000,false);
//				d2s_test.SSI_write(0x202,0x40,false);
//				d2s_test.SSI_write(0x33C,0x19B);
//				d2s::d2s_LABEL_END();
//			}
//			else{
//				d2s::d2s_LABEL_BEGIN( "ssi", d2s_WorkMode);
//				d2sProtocolSSI d2s_test;
//				d2s_test.SSI_write(0x200,0x2000,false);
//				d2s_test.SSI_write(0x202,0x40,false);
//				d2s_test.SSI_write(0x33C,0x1B6);
//				d2s::d2s_LABEL_END();
//			}
//
//		}
//		else {
//			  //resetDevice();
//			  PHY_ABB_RF_Reset_Module();
//			  if(strstr(testname.c_str(),"C0")!=NULL){
//					ABB_ADC_PV_Cal("C0",&WL_PV_Sensor,CalType);
//					ABB_ADC_CalStatus("C0", &pcal_status, &pcal_status_C1,CalType, &pCOMP_CAL_CODE_A1, &pCOMP_CAL_CODE_A2, &pCOMP_CAL_CODE_A3, &pCOMP_CAL_CODE);
//					ABB_ADC_CapCal_DC("C0",RF_Test_Data.tyABBTest.dABBSampleRate,&pWL_ADC_CAP_STS,CalType);
//
//				}
//				else{
//					ABB_ADC_PV_Cal("C1",&WL_PV_Sensor,CalType);
//					ABB_ADC_CalStatus("C1", &pcal_status, &pcal_status_C1,CalType, &pCOMP_CAL_CODE_A1, &pCOMP_CAL_CODE_A2, &pCOMP_CAL_CODE_A3, &pCOMP_CAL_CODE);
//					ABB_ADC_CapCal_DC("C1",RF_Test_Data.tyABBTest.dABBSampleRate,&pWL_ADC_CAP_STS,CalType);
//				}
//		}

	//    if (strstr(testname.c_str(), "C0") != NULL) {
	//        WL_ADC_C0_BeforeCap_Module();
	//    }
	//    else {
	//        WL_ADC_C1_BeforeCap_Module();
	//    }

		//3  Load source signal
//		CCRFTester.SelectSites("site0,site2");
//		SrcUtilitySites0();
//		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
//		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();
//
//
//
//		vector<int> Site_ac;
//		Site_ac.push_back(0);
//		Site_ac.push_back(2);
//		TheSoft.Sites().Active().SetActive(Site_ac);

	//    sites[0]=0;
	//    sites[1]=2;
	//    sites[2]=0;
	//    sites[3]=0;
	//    api->Set_active_sites(sites,2);
		//3.1 DUT register setting: just set before capture & wait for capture module, not capture
//		if (strstr(testname.c_str(), "C0") != NULL) {
//			WL_ADC_C0_Cap_Module( &myWave);
//		}
//		else {
//			WL_ADC_C1_Cap_Module( &myWave);
//		}

//		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
//
//		Sites_Init.clear();
//		for(unsigned int i=0;i<active_sites_size;i++)
//		{
//			sites[i]=sitestmp[i];
//			Sites_Init.push_back(sitestmp[i]);
//		}
////        vec_Site.clear();
////        vec_Site.push_back(0);
//		TheSoft.Sites().Active().SetActive(Sites_Init);                         //recover the sites information for Mutest
//		CCRFTester.ActiveSites(sites,active_sites_size);                        //recover the sites information for RF
//#ifdef semi_parallel_en
//		CCRFTester.SelectSites("site1,site3");
//		SrcUtilitySites1();
//		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
//		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();
//
//
//		Site_ac.clear();
//		Site_ac.push_back(1);
//		Site_ac.push_back(3);
//		TheSoft.Sites().Active().SetActive(Site_ac);
//	//    sites[0]=1;
	//    sites[1]=3;
	//    sites[2]=0;
	//    sites[3]=0;
	//    api->Set_active_sites(sites,2);
		//3.1 DUT register setting: just set before capture & wait for capture module, not capture
//		if (strstr(testname.c_str(), "C0") != NULL) {
//			WL_ADC_C0_Cap_Module( &myWave);
//		}
//		else {
//			WL_ADC_C1_Cap_Module( &myWave);
//		}
//		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
//
//		Sites_Init.clear();
//		for(unsigned int i=0;i<active_sites_size;i++)
//		{
//			sites[i]=sitestmp[i];
//			Sites_Init.push_back(sitestmp[i]);
//		}
////        vec_Site.clear();
////        vec_Site.push_back(0);
//		TheSoft.Sites().Active().SetActive(Sites_Init);                         //recover the sites information for Mutest
//		CCRFTester.ActiveSites(sites,active_sites_size);                        //recover the sites information for RF
//		SrcUtilitySites0();                                                      //recover Relay state
//#endif
//
//		//4  capture for all active site
//		if (strstr(testname.c_str(), "C0") != NULL) {
//			WL_ADC_C0_Cap_Module_read( &myWave);
//		}
//		else {
//			WL_ADC_C1_Cap_Module_read( &myWave);
//		}

		//5 calculator dynamic parameter
//		FunBin=RF_Test_Data.tyABBTest.dSigFreq / (2*RF_Test_Data.tyABBTest.dABBSampleRate/RF_Test_Data.tySrcSigSet.dAnaSrcSampleSize);
//		SpurBin=40e6 / (2*RF_Test_Data.tyABBTest.dABBSampleRate/RF_Test_Data.tySrcSigSet.dAnaSrcSampleSize);
		FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
			//int site_id = api->Get_active_site();
				for(int i=0;i<RF_Test_Data.tySrcSigSet.dAnaSrcSampleSize;i++){
					nData[i]=myWave(site_id,i) xor 0x200;
				}



				adcDynamicCalc( FunBin, nData, RF_Test_Data.tySrcSigSet.dAnaSrcSampleSize, RF_Test_Data.tyABBTest.iDivideNum,  snr_i, snr_q, thd_i, thd_q, sfdr_i,sfdr_q, sinad_i, sinad_q,
							   enob_i, enob_q, enob_iq, Amp_i, Amp_q, GainMismatch, distortion_num, SpurBin);

				TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, sinad_i, lowl[0], hil[0], Hard_Bin[0],Soft_Bin[0],"dB", Test_Item[0], Test_number[0]);
				TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, sinad_q, lowl[1], hil[1], Hard_Bin[1],Soft_Bin[1],"dB", Test_Item[1], Test_number[1]);
				TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, enob_i, lowl[2], hil[2], Hard_Bin[2],Soft_Bin[2],Units[2], Test_Item[2],Test_number[2]);
				TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, enob_q, lowl[3], hil[3], Hard_Bin[3],Soft_Bin[3],Units[3], Test_Item[3], Test_number[3]);
				TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, enob_iq, lowl[4], hil[4], Hard_Bin[4],Soft_Bin[4],Units[4], Test_Item[4],  Test_number[4]);
				TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, sfdr_i, lowl[5], hil[5], Hard_Bin[5],Soft_Bin[5],"dB", Test_Item[5],  Test_number[5]);
				TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, sfdr_q, lowl[6], hil[6], Hard_Bin[6],Soft_Bin[6],"dB", Test_Item[6],  Test_number[6]);
				TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, snr_i, lowl[7], hil[7], Hard_Bin[7],Soft_Bin[7],"dB", Test_Item[7],  Test_number[7]);
				TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, snr_q, lowl[8], hil[8], Hard_Bin[8],Soft_Bin[8],"dB", Test_Item[8],  Test_number[8]);
				TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, thd_i, lowl[9], hil[9], Hard_Bin[9],Soft_Bin[9],"dB", Test_Item[9],  Test_number[9]);
				TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, thd_q, lowl[10], hil[10], Hard_Bin[10],Soft_Bin[10],"dB", Test_Item[10],  Test_number[10]);
				TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, (Amp_i/RF_Test_Data.tyABBTest.iDivideNum)*RF_Test_Data.tyABBTest.dVpp, lowl[11], hil[11],Hard_Bin[11],Soft_Bin[11], "dB", Test_Item[11], Test_number[11]);
				TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, (Amp_q/RF_Test_Data.tyABBTest.iDivideNum)*RF_Test_Data.tyABBTest.dVpp, lowl[12], hil[12], Hard_Bin[12],Soft_Bin[12],"dB", Test_Item[12], Test_number[12]);
				TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, GainMismatch, lowl[13], hil[13], Hard_Bin[13],Soft_Bin[13],"dB", Test_Item[13],  Test_number[13]);

				if((CalType != cal_Type_SS)&&(CalType != calType_Nocal)){



					TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, (double)pWL_ADC_CAP_STS(site_id,0), lowl[14], hil[14],Hard_Bin[14],Soft_Bin[14],"", Test_Item[14], Test_number[14],PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
					TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, (double)pcal_status(site_id,0), lowl[15], hil[15],Hard_Bin[15],Soft_Bin[15],"", Test_Item[15], Test_number[15],PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
					TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, (double)pCOMP_CAL_CODE_A1(site_id,0), lowl[17], hil[17],Hard_Bin[17],Soft_Bin[17],"", Test_Item[17], Test_number[17],PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
					TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, (double)pCOMP_CAL_CODE_A2(site_id,0), lowl[18], hil[18],Hard_Bin[18],Soft_Bin[18],"", Test_Item[18], Test_number[18],PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
					TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, (double)pCOMP_CAL_CODE_A3(site_id,0), lowl[19], hil[19], Hard_Bin[19],Soft_Bin[19],"", Test_Item[19],  Test_number[19],PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
					TheSoft.Flow().TestLimit ( Ana_SrcPin,site_id, (double)pCOMP_CAL_CODE(site_id,0), lowl[20], hil[20], Hard_Bin[20],Soft_Bin[20],"", Test_Item[20],  Test_number[20],PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);

				}
		FOREACH_ACTIVESITE_END


    }
};
REGISTER_TESTCLASS("ABB_ADC_IQ",ABB_ADC_IQ)




