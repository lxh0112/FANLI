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
#include "Test_TX_cpp.h"
#include "Execute_Test.h"

using namespace PhxAPI;

class TX_IDD_cpp: public TestClass {
public:

	void init() {

	}

	void execute() {
//		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
//		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
//		TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing

//		double hil[30], lowl[30];
//		char *Test_Item[30], *Units[30];
//		int Test_number[30];
//		int Soft_Bin[30];
//		int Hard_Bin[30];
//		Read_Limit(lowl,hil,Test_Item,Test_number,Units,Soft_Bin,Hard_Bin);


		tyTestData RF_Test_Data;
		char Ana_SrcPin[_MAX_NAME_SIZE_RF] = { "\0" };
		char RF_CapPin[_MAX_NAME_SIZE_RF] = { "\0" };
		char Ana_Src_Signal[_MAX_NAME_SIZE_RF] = { "\0" };
		char RF_Cap_Signal[_MAX_NAME_SIZE_RF] = { "\0" };

		unsigned int sitestmp[4] = { 0, 0, 0, 0 };
		unsigned int sites[MAX_SITES] = { 0 };
		bool site0_flag = false;
		//bool site1_flag = false;
		bool site2_flag = false;
		//bool site3_flag = false;
		bool skip = false;
		vector<int> vec_Site = TheSoft.Sites().Active().GetActiveSites();
		unsigned int active_sites_size = TheSoft.Sites().Active().GetActiveSiteCount();
		for (int i = 0; i < 4; i++) {
			sitestmp[i] = vec_Site[i];
		}

		//1. Get test item information
		string testname = TheSoft.Flow().Test().GetCurrentTestName();
		Get_TestItem_Info(testname.c_str(), RF_Test_Data);
		Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
		Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);

		//2. Get Passloss
		CCRFTester.SelectSites("site0,site2");
		SrcUtilitySites0();
		//3.2  Load source and capture signal
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();


		FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
			int site_id = index;
			if(site_id==0) {
				site0_flag = true;
			}
			if(site_id==2) {
				site2_flag = true;
			}
			//Testsoftbin[site_id] = 1;
		FOREACH_ACTIVESITE_END

		vec_Site.clear();

		if ((site0_flag == true) && (site2_flag == true)) {
			vec_Site.push_back(0);
			vec_Site.push_back(2);
		} else if (site0_flag == true && site2_flag == false) {
			vec_Site.push_back(0);
		} else if (site0_flag == false && site2_flag == true) {
			vec_Site.push_back(2);
		} else {
			skip = true;
		}

		if (skip != true) {
			TheSoft.Sites().Active().SetActive(vec_Site);

			if (strstr(testname.c_str(), "C0") != NULL) {
				WL_TX_2G_M_C0_IDD(0);
			} else {
				WL_TX_2G_M_C1_IDD(0);
			}
		}

		vec_Site.clear();
		for(unsigned int i=0;i<active_sites_size;i++)
		{
			sites[i]=sitestmp[i];
			vec_Site.push_back(sitestmp[i]);
		}

		TheSoft.Sites().Active().SetActive(vec_Site);                         //recover the sites information for Mutest
		CCRFTester.ActiveSites(sites,active_sites_size);                        //recover the sites information for RF


		// CCRFTester.ActiveSites("site0,site1,site2,site3");
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();

		site0_flag = false;
		site2_flag = false;
		skip = false;

		CCRFTester.SelectSites("Site1,Site3");

		SrcUtilitySites1();	//////////////////////////////////////////////////////////////////////////////////////////////////////
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();

		FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
			int site_id = index;
			if(site_id==1) {
				site0_flag = true;
			}
			if(site_id==3) {
				site2_flag = true;
			}
		FOREACH_ACTIVESITE_END

		vec_Site.clear();
		if (site0_flag == true && site2_flag == true) {
			vec_Site.push_back(1);
			vec_Site.push_back(3);
		} else if (site0_flag == true && site2_flag == false) {
			vec_Site.push_back(1);
		} else if (site0_flag == false && site2_flag == true) {
			vec_Site.push_back(3);
		} else {
			skip = true;
		}

		if (skip != true) {
			TheSoft.Sites().Active().SetActive(vec_Site);

			if (strstr(testname.c_str(), "C0") != NULL) {
				WL_TX_2G_M_C0_IDD(20);
			} else {
				WL_TX_2G_M_C1_IDD(20);
			}

		}
		for (int i = 0; i < 4; i++) {
			sites[i] = sitestmp[i];
		}
		vec_Site.clear();
		for(unsigned int i=0;i<active_sites_size;i++)
		{
			sites[i]=sitestmp[i];
			vec_Site.push_back(sitestmp[i]);
		}

		TheSoft.Sites().Active().SetActive(vec_Site);                         //recover the sites information for Mutest
		CCRFTester.ActiveSites(sites,active_sites_size);                        //recover the sites information for RF
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
		SrcUtilitySites0();                                //recover Relay state
		TheInst.DCVS().Power().Apply();


	}
};
REGISTER_TESTCLASS("TX_IDD_cpp", TX_IDD_cpp)

