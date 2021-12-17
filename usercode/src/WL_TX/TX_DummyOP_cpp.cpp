#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
//#include "D2S_CAL_Module.h"
//#include "Globle_Var.h"
#include "CCS08F.h"
#include "Excel.h"
#include "RegDef.h"
#include "d2sProtocolSSI.h"
#include "UserDef.h"
#include "Test_TX_cpp.h"

using namespace PhxAPI;

class TX_DummyOP_cpp: public TestClass {
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
		Read_Limit(lowl,hil,Test_Item,Test_number,Units,Soft_Bin,Hard_Bin);

		//1. Get test item information
		tyTestData RF_Test_Data;

		char Ana_SrcPin[_MAX_NAME_SIZE_RF] = { "\0" };
		char RF_CapPin[_MAX_NAME_SIZE_RF] = { "\0" };
		char Ana_Src_Signal[_MAX_NAME_SIZE_RF] = { "\0" };
		char RF_Cap_Signal[_MAX_NAME_SIZE_RF] = { "\0" };

		CCRfmxSpecAnResults mxSpecAnResults;
		SpecAnResultAttribute ResultAttribute;
		double pathloss[4];
		double Post_Power;
		double CR;
		double SR;

		string testname = TheSoft.Flow().Test().GetCurrentTestName();
		Get_TestItem_Info(testname.c_str(), RF_Test_Data);
		Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
		Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);

		//2. Get Passloss
		Read_Pathloss(RF_Test_Data, pathloss);

		DummyOP_Path_Setup ();

		CCRFTester.SelectSites("site0,site2");
		SrcUtilitySites0();
		//3.2  Load source and capture signal
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();

		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();

		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(
				&mxSpecAnResults);

		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
#ifdef semi_parallel_en
		CCRFTester.SelectSites("site1,site3");
		SrcUtilitySites1();
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();

		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();

		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(
				&mxSpecAnResults);

		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
		SrcUtilitySites0();                             //recover Relay state
#endif
		DummyOP_Path_Recover();

		FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
			int site_id = index;
			ResultAttribute = mxSpecAnResults[site_id];
			Calc_TX_Power_CR_SR( &RF_Test_Data, &ResultAttribute, pathloss[site_id], &Post_Power, &CR, &SR);

			TheSoft.Flow().TestLimit(RF_CapPin,site_id, Post_Power, lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], Units[0],Test_Item[0],Test_number[0]);
			TheSoft.Flow().TestLimit(RF_CapPin,site_id, CR, lowl[1], hil[1],Hard_Bin[1],Soft_Bin[1], "dB", Test_Item[1],Test_number[1]);
			TheSoft.Flow().TestLimit(RF_CapPin,site_id, SR, lowl[2], hil[2],Hard_Bin[2],Soft_Bin[2], "dB", Test_Item[2],Test_number[2]);
		FOREACH_ACTIVESITE_END

	}
};
REGISTER_TESTCLASS("TX_DummyOP_cpp", TX_DummyOP_cpp)

