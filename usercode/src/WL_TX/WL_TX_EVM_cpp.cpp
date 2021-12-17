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

class WL_TX_EVM_cpp: public TestClass {
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

		CCMxWlanResults MxWlanResults;
		WlanResultsAttribute ResultsAttribute;
		double EVM;
		double EVM_Power_Abs;
		double pathloss[4];

		//1. Get test item information
		string testname = TheSoft.Flow().Test().GetCurrentTestName();
		Get_TestItem_Info(testname.c_str(), RF_Test_Data);
		Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
		Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);

		//2. Get Passloss
		Read_Pathloss(RF_Test_Data, pathloss);

		//3. DUT register setting
		TX_PLL_Setup((emMode) RF_Test_Data.iMode,(emTX_Band) RF_Test_Data.iBand, RF_Test_Data.cChannel,RF_Test_Data.dBW);
		if (RF_Test_Data.dBW = 24e6) {
			d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
			d2sProtocolSSI d2s_test;
			d2s_test.SSI_write(0x200, 0x2000, false);
			d2s_test.SSI_write(0x202, 0x90, false);
			d2s_test.SSI_write(0xC, 0x37);     //wl_trx_reg3
			d2s_test.SSI_write(0x10, 0x37);
			d2s::d2s_LABEL_END();
		} else if (RF_Test_Data.dBW == 48e6) {
			d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
			d2sProtocolSSI d2s_test;
			d2s_test.SSI_write(0x200, 0x2000, false);
			d2s_test.SSI_write(0x202, 0x90, false);
			d2s_test.SSI_write(0xC, 0x3F);     //wl_trx_reg3
			d2s_test.SSI_write(0x10, 0x3F);
			d2s::d2s_LABEL_END();
		}

		CCRFTester.SelectSites("site0,site2");
		SrcUtilitySites0();
		//4  Load source and capture signal
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();

		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&MxWlanResults);
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
#ifdef semi_parallel_en
		CCRFTester.SelectSites("site1,site3");
		SrcUtilitySites1();
		//4  Load source and capture signal
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();

		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();

		//5. Trigger capture signal, get wave, calculate evm
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&MxWlanResults);

		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
		SrcUtilitySites0();                                //recover Relay state
#endif
		FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
			/* site: 0,2,3 */
			int		site_id = index;
			Testsoftbin[site_id] = 1;                                 //softbin flag
			ResultsAttribute = MxWlanResults[site_id];
			EVM=ResultsAttribute.OFDMM.CompositeRMSEVM.dCompositeRMSEVMMean;
			EVM_Power_Abs = ResultsAttribute.SEM.CarrierMeasurement.dAbsolutePower+pathloss[site_id];

			TheSoft.Flow().TestLimit(RF_CapPin,site_id, 100*pow(10,(EVM/20)), lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], Units[0], Test_Item[0],Test_number[0]);
			TheSoft.Flow().TestLimit(RF_CapPin,site_id, EVM_Power_Abs, lowl[1], hil[1],Hard_Bin[1],Soft_Bin[1], Units[1], Test_Item[1], Test_number[1]);

		FOREACH_ACTIVESITE_END

		d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
		d2sProtocolSSI d2s_test;
		d2s_test.SSI_write(0x200, 0x2000, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0xC, 0x2F);     //wl_trx_reg3, default value
		d2s_test.SSI_write(0x10, 0x2F);
		d2s::d2s_LABEL_END();
//		FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
//			int site_id = index;
//			if(Testsoftbin[site_id]!=1) {
//	//???    	         api->Set_result_bin(Testsoftbin[site_id]);
//			}
//		FOREACH_ACTIVESITE_END

	}
};
REGISTER_TESTCLASS("WL_TX_EVM_cpp", WL_TX_EVM_cpp)

