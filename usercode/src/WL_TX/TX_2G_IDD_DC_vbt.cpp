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
#include "Execute_Test.h"

using namespace PhxAPI;

class TX_2G_IDD_DC_vbt: public TestClass {
public:

	void init() {

	}

	void execute() {
		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
		TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing

		tyTestData RF_Test_Data;
		char *Channel_p;
		char *Channel;

		char Ana_Src_Signal[32] = { "\0" };
		char *Ana_SrcPin = "RF_TEST_TX_IP";

		string testname = TheSoft.Flow().Test().GetCurrentTestName();
		Get_TestItem_Info(testname.c_str(), RF_Test_Data);
		//    Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);

		Channel = RF_Test_Data.cChannel;
		Channel_p = strstr(Channel, "C0");

		//PPMU_ForceV IQ_SrcPin, 0.6, 0.002
		//    api->Execute_test("TX_2G_IDD_PPMU_FORCE_TEST");
		CCRFTester.SelectSites("site0,site2");
		sprintf(Ana_Src_Signal, "TX_2G_IDD_DC_0p%d", 6);
		LoadSignal_MIX_TX_2G_DC(0.6, Ana_Src_Signal);
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();

		d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
		d2sProtocolSSI d2s_test;
		d2s_test.SSI_write(0x200, 0x2000, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0xC, 0x3F);       //reg3 txmode=3
		d2s_test.SSI_write(0x10, 0x3F);      //reg4 txmode=3
		d2s::d2s_LABEL_END();

		if (Channel_p != NULL) {
			d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
			d2s_test.SSI_write(0x1C, 0x1D1D); //delta current=(dc current with reg7<2>=1)-(dc current with reg7<2>=0)
			d2s::d2s_LABEL_END();
		} else {
			d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
			d2s_test.SSI_write(0x1C, 0x1D1D); //delta current=(dc current with reg7<10>=1)-(dc current with reg7<10>=0)
			d2s::d2s_LABEL_END();
		}

		map<int, double> iddMeasUpc1;
//		double *GetValue;
		PinArrayDouble GetValue = Execute_test("TX_2G_IDD_TEST");

		FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
//???    			api->Get_dctest_values("TX_2G_IDD_TEST","RF_VDD_TX2G_3P3_0",0,THE_MEASURE,&GetValue,THE_END);
    	    int	site_id = index;
			iddMeasUpc1[site_id] = GetValue.GetData("RF_VDD_TX2G_3P3_0",site_id);
//???    			api->info_message("Site:%d---------------- %s    iddMeasUpc1    :    %f-----------",site_id,"RF_VDD_TX2G_3P3_0",iddMeasUpc1[site_id]);
		FOREACH_ACTIVESITE_END

		if (Channel_p != NULL) {
			d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
			d2s_test.SSI_write(0x1C, 0x1D19); //delta current=(dc current with reg7<2>=1)-(dc current with reg7<2>=0)
			d2s::d2s_LABEL_END();
		} else {
			d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
			d2s_test.SSI_write(0x1C, 0x191D); //delta current=(dc current with reg7<10>=1)-(dc current with reg7<10>=0)
			d2s::d2s_LABEL_END();
		}

		map<int, double> iddMeasUpc0;
		//double *GetValue;
		GetValue = Execute_test("TX_2G_IDD_TEST");

		FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
//???    			api->Get_dctest_values("TX_2G_IDD_TEST","RF_VDD_TX2G_3P3_0",0,THE_MEASURE,&GetValue,THE_END);
    	    int	site_id = index;
			iddMeasUpc0[site_id] = GetValue.GetData("RF_VDD_TX2G_3P3_0",site_id);
//???    			api->info_message("Site:%d---------------- %s    iddMeasUpc0    :    %f-----------",site_id,"RF_VDD_TX2G_3P3_0",iddMeasUpc0[site_id]);
		FOREACH_ACTIVESITE_END

		d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
		d2s_test.SSI_write(0x1C, 0x1D1D);
		d2s_test.SSI_write(0x202, 0x94, false);
		d2s::d2s_LABEL_END();

		if (Channel_p != NULL) {
			d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
			d2s_test.SSI_write(0xE0, 0x1);
			d2s_test.SSI_write(0xF0 + 0x10, 0x79A3); //channel 0: delta current=(dc current with reg312=1, reg320<15:10>=30)- (dc current with reg312=0, reg320<15:10>=0) }
			d2s::d2s_LABEL_END();
		} else {
			d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
			d2s_test.SSI_write(0x150, 0x1);
			d2s_test.SSI_write(0x160 + 0x10, 0x79A3); //channel 0: delta current=(dc current with reg312=1, reg320<15:10>=30)- (dc current with reg312=0, reg320<15:10>=0)
			d2s::d2s_LABEL_END();
		}

		map<int, double> iddMeasPAA1;
		//double *GetValue;
		GetValue = Execute_test("TX_2G_IDD_TEST");

		FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
//???		api->Get_dctest_values("TX_2G_IDD_TEST","RF_VDD_TX2G_3P3_0",0,THE_MEASURE,&GetValue,THE_END);
			int site_id = index;
			iddMeasPAA1[site_id] = GetValue.GetData("RF_VDD_TX2G_3P3_0",site_id);
//???		api->info_message("Site:%d---------------- %s    iddMeasPAA1    :    %f-----------",site_id,"RF_VDD_TX2G_3P3_0",iddMeasPAA1[site_id]);
		FOREACH_ACTIVESITE_END

		if (Channel_p != NULL) {
			d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
			d2s_test.SSI_write(0xE0, 0x0);
			d2s_test.SSI_write(0xF0 + 0x10, 0x1A3); //channel 0: delta current=(dc current with reg312=1, reg320<15:10>=40)- (dc current with reg312=0, reg320<15:10>=0)
			d2s::d2s_LABEL_END();
		} else {
			d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
			d2s_test.SSI_write(0x150, 0x0);
			d2s_test.SSI_write(0x160 + 0x10, 0x1A3); //channel 0: delta current=(dc current with reg312=1, reg320<15:10>=40)- (dc current with reg312=0, reg320<15:10>=0)
			d2s::d2s_LABEL_END();
		}

		map<int, double> iddMeasPAA0;
		//double *GetValue;
		GetValue = Execute_test("TX_2G_IDD_TEST");

		FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
//???		api->Get_dctest_values("TX_2G_IDD_TEST","RF_VDD_TX2G_3P3_0",0,THE_MEASURE,&GetValue,THE_END);
			int site_id = index;
			iddMeasPAA0[site_id] = GetValue.GetData("RF_VDD_TX2G_3P3_0",site_id);
//???		api->info_message("Site:%d---------------- %s    iddMeasPAA0    :    %f-----------",site_id,"RF_VDD_TX2G_3P3_0",iddMeasPAA0[site_id]);
		FOREACH_ACTIVESITE_END

		d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
		d2s_test.SSI_write(0x202, 0x94, false);
		d2s_test.SSI_write(0xE0, 0x1);
		d2s_test.SSI_write(0x150, 0x1);
		d2s_test.SSI_write(0xF0 + 0x10, 0x81A3);
		d2s_test.SSI_write(0x160 + 0x10, 0x81A3);
		d2s::d2s_LABEL_END();

		if (Channel_p != NULL) {
			d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
			d2s_test.SSI_write(0xF0 + 0x10, 0x8283); //channel 0: delta current=(dc current with reg312=1, reg320<15:10>=24)- (dc current with reg312=0, reg320<15:10>=0)
			d2s::d2s_LABEL_END();
		} else {
			d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
			d2s_test.SSI_write(0x160 + 0x10, 0x8283); //channel 0: delta current=(dc current with reg312=1, reg320<15:10>=24)- (dc current with reg312=0, reg320<15:10>=0)
			d2s::d2s_LABEL_END();
		}

		map<int, double> iddMeasPAB1;
		//double *GetValue;
		GetValue = Execute_test("TX_2G_IDD_TEST");

		FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
//???		api->Get_dctest_values("TX_2G_IDD_TEST","RF_VDD_TX2G_3P3_0",0,THE_MEASURE,&GetValue,THE_END);
			int site_id = index;
			iddMeasPAB1[site_id] = GetValue.GetData("RF_VDD_TX2G_3P3_0",site_id);
//???		api->info_message("Site:%d---------------- %s    iddMeasPAB1    :    %f-----------",site_id,"RF_VDD_TX2G_3P3_0",iddMeasPAB1[site_id]);
		FOREACH_ACTIVESITE_END

		if (Channel_p != NULL) {
			d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
			d2s_test.SSI_write(0xF0 + 0x10, 0x8003); //channel 0: delta current=(dc current with reg312=1, reg320<15:10>=24)- (dc current with reg312=0, reg320<15:10>=0)
			d2s::d2s_LABEL_END();
		} else {
			d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
			d2s_test.SSI_write(0x160 + 0x10, 0x8003); //channel 0: delta current=(dc current with reg312=1, reg320<15:10>=24)- (dc current with reg312=0, reg320<15:10>=0)
			d2s::d2s_LABEL_END();
		}

		map<int, double> iddMeasPAB0;
		//double *GetValue;
		GetValue = Execute_test("TX_2G_IDD_TEST");

		FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
//???		api->Get_dctest_values("TX_2G_IDD_TEST","RF_VDD_TX2G_3P3_0",0,THE_MEASURE,&GetValue,THE_END);
			int site_id = index;
			iddMeasPAB0[site_id] = GetValue.GetData("RF_VDD_TX2G_3P3_0",site_id);
//???		api->info_message("Site:%d---------------- %s    iddMeasPAB0    :    %f-----------",site_id,"RF_VDD_TX2G_3P3_0",iddMeasPAB0[site_id]);
		FOREACH_ACTIVESITE_END

		d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
		d2s_test.SSI_write(0xF0 + 0x10, 0x81A3);
		d2s_test.SSI_write(0x160 + 0x10, 0x81A3);
		d2s_test.SSI_write(0x200, 0x2000, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s::d2s_LABEL_END();

		if (Channel_p != NULL) {
			d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
			d2s_test.SSI_write(0xB0, 0x1F); //channel 0: delta current=(dc current with reg44[0]=1, reg45[0]=1
			d2s_test.SSI_write(0xB4, 0x1F);
			d2s::d2s_LABEL_END();
		} else {
			d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
			d2s_test.SSI_write(0xB8, 0x1F); //channel 1: delta current=(dc current with reg46[0]=1, reg47[0]=1
			d2s_test.SSI_write(0xBC, 0x1F);
			d2s::d2s_LABEL_END();
		}

		map<int, double> iddMeasPABit0_1;
		//double *GetValue;
		GetValue = Execute_test("TX_2G_IDD_TEST");

		FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
//???		api->Get_dctest_values("TX_2G_IDD_TEST","RF_VDD_TX2G_3P3_0",0,THE_MEASURE,&GetValue,THE_END);
		int site_id = index;
		iddMeasPABit0_1[site_id] = GetValue.GetData("RF_VDD_TX2G_3P3_0",site_id);
//???		api->info_message("Site:%d---------------- %s    iddMeasPABit0_1    :    %f-----------",site_id,"RF_VDD_TX2G_3P3_0",iddMeasPABit0_1[site_id]);
		FOREACH_ACTIVESITE_END

		if (Channel_p != NULL) {
			d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
			d2s_test.SSI_write(0xB0, 0x1E); //channel 0: delta current=(dc current with reg44[0]=0, reg45[0]=0
			d2s_test.SSI_write(0xB4, 0x1E);
			d2s::d2s_LABEL_END();
		} else {
			d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
			d2s_test.SSI_write(0xB8, 0x1E); //channel 1: delta current=(dc current with reg46[0]=0, reg47[0]=0
			d2s_test.SSI_write(0xBC, 0x1E);
			d2s::d2s_LABEL_END();
		}

		map<int, double> iddMeasPABit0_0;
		//double *GetValue;
		GetValue = Execute_test("TX_2G_IDD_TEST");

		FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
//???		api->Get_dctest_values("TX_2G_IDD_TEST","RF_VDD_TX2G_3P3_0",0,THE_MEASURE,&GetValue,THE_END);
			int site_id = index;
			iddMeasPABit0_0[site_id] = GetValue.GetData("RF_VDD_TX2G_3P3_0",site_id);
		//		api->info_message("Site:%d---------------- %s    iddMeasPABit0_0    :    %f-----------",site_id,"RF_VDD_TX2G_3P3_0",iddMeasPABit0_0[site_id]);
		FOREACH_ACTIVESITE_END

		d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
		d2s_test.SSI_write(0xB0, 0x1F);
		d2s_test.SSI_write(0xB4, 0x1F);
		d2s_test.SSI_write(0xB8, 0x1F);
		d2s_test.SSI_write(0xBC, 0x1F);
		d2s::d2s_LABEL_END();

		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();

	}
};
REGISTER_TESTCLASS("TX_2G_IDD_DC_vbt", TX_2G_IDD_DC_vbt)

