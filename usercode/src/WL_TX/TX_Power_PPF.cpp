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

class TX_Power_PPF: public TestClass {
public:

	void init() {

	}

	void execute() {

//		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
//		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
		TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing

		char *RF_Cap_Signal;
		char *RF_CapPin;
		//int nSite = 0;

		double Power_Data;
		double CR_Data;
		double SR_Data;

		double Exp_Fre = 37.5E6;
		CCRfmxSpecAnResults mxSpecAnResults;
		SpecAnResultAttribute ResultAttribute;
		string testname = TheSoft.Flow().Test().GetCurrentTestName();
		if (strstr(testname.c_str(), "C0") != NULL) {
			TXIQ_5G_C0_Module ();
			TXIQ_5G_37p5M_C0_Module();
			RF_Cap_Signal = "TX_POWR_PPF_37p5_M";
			RF_CapPin = "RF_RFO_5G_C0";
		} else {
			TXIQ_5G_C1_Module ();
			TXIQ_5G_37p5M_C1_Module();
			RF_Cap_Signal = "TX_POWR_PPF_37p5_M";
			RF_CapPin = "RF_RFO_5G_C1";
		}

		TXIQ_5G_Restore_Module();

	}
};
REGISTER_TESTCLASS("TX_Power_PPF", TX_Power_PPF)

