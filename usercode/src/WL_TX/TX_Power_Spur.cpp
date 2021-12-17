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

class TX_Power_Spur: public TestClass {
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

		tyTestData RF_Test_Data;

		char Ana_SrcPin[_MAX_NAME_SIZE_RF] = { "\0" };
		char RF_CapPin[_MAX_NAME_SIZE_RF] = { "\0" };
		char Ana_Src_Signal[_MAX_NAME_SIZE_RF] = { "\0" };
		char RF_Cap_Signal[_MAX_NAME_SIZE_RF] = { "\0" };
		double pathloss[4];

		CCRfmxSpecAnResults mxSpecAnResults;
		SpecAnResultAttribute ResultAttribute;

		//1. Get test item information
		string testname = TheSoft.Flow().Test().GetCurrentTestName();
		Get_TestItem_Info(testname.c_str(), RF_Test_Data);
		Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
		Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);

		Read_Pathloss(RF_Test_Data, pathloss);

		//2. Get Passloss
		//pathloss = Read_Pathloss(testname);

		CCRFTester.SelectSites("site0,site2");
		SrcUtilitySites0 ();
		//3.2  Load source and capture signal
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();

		//3.3  Trigger capture signal, get wave, calculate power
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
		//3.3  Trigger capture signal, get wave, calculate power
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(
				&mxSpecAnResults);

		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
		SrcUtilitySites0();                                //recover Relay state
#endif
		double outPower = 0;
		double SPUR1_dbm = 0;
		double SPUR2_dbm = 0;
		double SPUR3_dbm = 0;

		FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
			/* site: 0,2,3 */
			int		site_id = index;
			ResultAttribute = mxSpecAnResults[site_id];

			if(RF_Test_Data.iMode == WLAN_2G_Mode)
			{
				if(ResultAttribute.dwNumbersOfSpectrum > 0)
				Calc_TX_Power_2_Spur(&RF_Test_Data,&ResultAttribute,pathloss[site_id],-0.5E6,0.5E6,&outPower,&SPUR1_dbm,&SPUR2_dbm);

				TheSoft.Flow().TestLimit(RF_CapPin,site_id, outPower, lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], "dBm", Test_Item[0],Test_number[0]);
				TheSoft.Flow().TestLimit(RF_CapPin,site_id, outPower-SPUR1_dbm, lowl[1], hil[1],Hard_Bin[1],Soft_Bin[1], "dBc", Test_Item[1],Test_number[1]);
				TheSoft.Flow().TestLimit(RF_CapPin,site_id, outPower-SPUR2_dbm, lowl[2], hil[2],Hard_Bin[2],Soft_Bin[2], "dBc", Test_Item[2],Test_number[2]);
			}
			else
			{
				if(ResultAttribute.dwNumbersOfSpectrum > 0)
				Calc_TX_Power_3_Spur(&RF_Test_Data,&ResultAttribute,pathloss[site_id],40E6,80E6,120E6,&outPower,&SPUR1_dbm,&SPUR2_dbm,&SPUR3_dbm);

				TheSoft.Flow().TestLimit(RF_CapPin,site_id, outPower, lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], "dBm", Test_Item[0],Test_number[0]);
				TheSoft.Flow().TestLimit(RF_CapPin,site_id, outPower-SPUR1_dbm, lowl[1], hil[1],Hard_Bin[1],Soft_Bin[1], "dBc", Test_Item[1],Test_number[1]);
				TheSoft.Flow().TestLimit(RF_CapPin,site_id, outPower-SPUR2_dbm, lowl[2], hil[2],Hard_Bin[2],Soft_Bin[2], "dBc", Test_Item[2], Test_number[2]);
				TheSoft.Flow().TestLimit(RF_CapPin,site_id, outPower-SPUR3_dbm, -999999.0, 999999.0,1,1, "dBc", "SPUR3", 1); //???
			}
		FOREACH_ACTIVESITE_END

	}
};
REGISTER_TESTCLASS("TX_Power_Spur", TX_Power_Spur)

