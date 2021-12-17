#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
//#include "D2S_CAL_Module.h"
#include "Globle_Var.h"
#include "CCS08F.h"
#include "Excel.h"
#include "RegDef.h"
#include "UserDef.h"
#include "d2sProtocolSSI.h"
#include "Execute_Test.h"
#include <string.h>

using namespace PhxAPI;

class TRX_Init: public TestClass {
public:

	void init() {

	}

	void execute() {

//		TheInst.DCVS().Power().Apply();
//		TheInst.Digital().Level().Apply();
		TheInst.Digital().Timing().Apply();

		tyTestData RF_Test_Data;
		emTRX TRX_Path_Select;
		char *Channel;
		emMode Mode_Select;

		string testname = TheSoft.Flow().Test().GetCurrentTestName();
		Get_TestItem_Info(testname.c_str(), RF_Test_Data);
		Channel = RF_Test_Data.cChannel;
		TRX_Path_Select = RF_Test_Data.iTRX;
		Mode_Select = (emMode) RF_Test_Data.iMode;


		if(strcmp(testname.c_str(),"WL_RX_2G_M_C0_RFI_INIT") == 0){
			RF_SWITCH_Control("SW_U1_V1,SW_U2_V2","SW_U1_V2,SW_U1_V3,SW_U2_V1,SW_U2_V3");
		}
		else if(strcmp(testname.c_str(),"WL_RX_2G_M_C0_RFIO_INIT")== 0){
			RF_SWITCH_Control("SW_U1_V2,SW_U2_V1","SW_U1_V1,SW_U1_V3,SW_U2_V2,SW_U2_V3");
		}
		else if(strcmp(testname.c_str(),"WL_RX_2G_M_C1_RFI_INIT")== 0){
			RF_SWITCH_Control("SW_U3_V1,SW_U4_V2","SW_U3_V2,SW_U3_V3,SW_U4_V1,SW_U4_V3");
		}
		else if(strcmp(testname.c_str(),"WL_RX_2G_M_C1_RFIO_INIT")== 0){
			RF_SWITCH_Control("SW_U3_V2,SW_U4_V1","SW_U3_V1,SW_U3_V3,SW_U4_V2,SW_U4_V3");
		}
		else if(strcmp(testname.c_str(),"WL_TX_2G_M_C0_RFIO_INIT")== 0){
			RF_SWITCH_Control("SW_U1_V3","SW_U1_V1,SW_U1_V2");
		}
		else if(strcmp(testname.c_str(),"WL_TX_2G_M_C1_RFIO_INIT")== 0){
			RF_SWITCH_Control("SW_U3_V3","SW_U3_V1,SW_U3_V2");
		}

		//disconnectall RF pins
		//disconnectall ana pins
		//LB UPAC K2/K3 RELAY
		int UtilitySites[8] = {51,24,20,65,19,33,11,56};
		if (TRX_Path_Select == RX_Path) {
    		for(uint32_t i=0;i<8;i++)
    		{
    			TheInst.Util().SetRelayState(UtilitySites[i], 1);

    		}
		} else {
    	    for(uint32_t i=0;i<8;i++)
			{
				TheInst.Util().SetRelayState(UtilitySites[i], 0);
			}
		}

		//start pattern

		Test_Mode_Init_Setup(Mode_Select, TRX_Path_Select, Channel);
		TestMUX_Init_Setup(TRX_Path_Select, Channel);
		if ((strstr(testname.c_str(), "RX"))&& (strstr(testname.c_str(), "C0_RFI_INIT"))) {
			Write_RC_PPF(TRX_Path_Select, Channel);
//			Write_RC_PPF(RX_Path, "C0_RFI");
		}


		Last_GainMode = (char*) "\0";
		Last_RFmode = -1;
		Last_RFband = -1;
		Last_LPFBW = -1;

		RX_GAIN_I_LIST.Clear();
		RX_GAIN_Q_LIST.Clear();



	}
};
REGISTER_TESTCLASS("TRX_Init", TRX_Init)

