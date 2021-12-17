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

class TX_5G_PowerTrim_cpp: public TestClass {
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

		//Parameter definition here
		tyTestData RF_Test_Data;

		char Ana_SrcPin[_MAX_NAME_SIZE_RF] = { "\0" };
		char RF_CapPin[_MAX_NAME_SIZE_RF] = { "\0" };
		char Ana_Src_Signal[_MAX_NAME_SIZE_RF] = { "\0" };
		char RF_Cap_Signal[_MAX_NAME_SIZE_RF] = { "\0" };

		long Exp_Bin = 0;
		volatile double Exp_Freq = 0;
		double pathloss[4];

		CCRfmxSpecAnResults mxSpecAnResults;
		SpecAnResultAttribute ResultAttribute;
		double Pre_Output_Power[4] = { 0 };

		//1. Get test item information
		string testname = TheSoft.Flow().Test().GetCurrentTestName();
		Get_TestItem_Info(testname.c_str(), RF_Test_Data);
		Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
		Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);
		Exp_Freq = selectFrequency(RF_Test_Data.cRxFreq) + RF_Test_Data.tyTXTest.dFreqSpacing;
		//    Exp_Freq=2443e6;

		//2. Get Passloss
		Read_Pathloss(RF_Test_Data, pathloss);

		//3. Measre pre Power
		//3.1  DUT register setting: cal code, PLL, gain
		Set_RF_TX_Pll_BW((emMode) RF_Test_Data.iMode, (emTX_Band) RF_Test_Data.iBand, RF_Test_Data.dBW,
				RF_Test_Data.cChannel);

		CCRFTester.SelectSites("site0,site2");
		SrcUtilitySites0();
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

		CCRFTester.SelectSites("site1,site3");
		SrcUtilitySites1();
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();

		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
		//3.3  Trigger capture signal, get wave, calculate power
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);

		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
		SrcUtilitySites0();                                //recover Relay state

		FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
			int site_id = index;
			ResultAttribute = mxSpecAnResults[site_id];
			if(ResultAttribute.dwNumbersOfSpectrum > 0)
			{
				Exp_Bin = int((Exp_Freq - ResultAttribute.dInitiaFrequency)/ResultAttribute.dFrequencyIncrement);
				Calc_Power_dbm(&ResultAttribute,Exp_Bin,5,&Pre_Output_Power[site_id],pathloss[site_id]);
			}
			TheSoft.Flow().TestLimit(RF_CapPin,site_id, Pre_Output_Power[site_id], lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], Units[0], Test_Item[0], Test_number[0]);
		FOREACH_ACTIVESITE_END

	}
};
REGISTER_TESTCLASS("TX_5G_PowerTrim_cpp", TX_5G_PowerTrim_cpp)

