
#include "Systick.h"
#include "GetLog.h"
#include "UserAPI.h"
#include "TestClass.h"

//#include "UserDef.h"
#include "d2sProtocolSSI.h"
#include "D2S_CAL_Module.h"
#include "D2S_ABB_Module.h"
#include "Test_ABB.h"
#include "Test_CAL.h"
#include "readlimit.h"
//#include "CCS08F.h"
//#include "RegDef.h"
#include "Globle_Var.h"
#include <math.h>
//#include "RegDef.h"
#include "Excel.h"
#include <vector>
#include <string.h>
#include "linearfit.h"
#include "Globle_Var.h"
//#include "CCS08F.h"
#include <algorithm>

using namespace std;


class CAL_VI_DET: public TestClass{
public:
//    std::string powerpinlist;
//    double vforce;
//	double iClampl;
//	double iClamph;
//	double waittime;
//    int sampleSize;

    void init(){

    }

    void execute(){

    	TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
		TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing
		TheInst.Digital().Pattern().Start();



    	double hil[30],lowl[30];
		char *Test_Item[30],*Units[30];
		int  Test_number[30];
		Read_Limit(lowl,hil,Test_Item,Test_number,Units);

		CSiteLong SiteData;

		double divider = 128.0;

		string flowname = TheSoft.Flow().GetCurrentFlowName();

	//    if(strstr(flowname,"105C")!=NULL){
	//        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
	//        d2sProtocolSSI d2s_test;
	//        d2s_test.SSI_write(0x200,0x2000,false);
	//        d2s_test.SSI_write(0x202,0x90,false);
	//        d2s_test.SSI_write(0x24,0x181);
	//        d2s_test.SSI_write(0x28,0x181);
	//        d2s::d2s_LABEL_END();
	//    }
	//    else if(strstr(flowname,"L40C")!=NULL){
	//        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
	//        d2sProtocolSSI d2s_test;
	//        d2s_test.SSI_write(0x200,0x2000,false);
	//        d2s_test.SSI_write(0x202,0x90,false);
	//        d2s_test.SSI_write(0x24,0x19F);
	//        d2s_test.SSI_write(0x28,0x19F);
	//        d2s::d2s_LABEL_END();
	//    }
	//    else{
			d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
			d2sProtocolSSI d2s_test;
			d2s_test.SSI_write(0x200,0x2000,false);
			d2s_test.SSI_write(0x202,0x90,false);
			d2s_test.SSI_write(0x24,0x180);
			d2s_test.SSI_write(0x28,0x180);
			d2s::d2s_LABEL_END();
	//    }
		string testname = TheSoft.Flow().Test().GetCurrentTestName();

		//temp variable
		long tempFlow;
		 tempFlow = 0;
		long Delt;
		long Delt_Index;
		long FirstVal;
		long LastVal;
		long Near_125K_Val;
		long Near_125K_Val_index;
		double Poly_Max;
		double Poly_Min;
		long I_FirstCode;
		long I_FirstData;
		long I_HalfCycle;
		long I_VppL;
		long I_CycleL;
		long I_VppH;
		long I_CycleH;
		long I_FlatnessL;
		long I_FlatnessH;

		long long Cur_V_Code[64];
		long long Cur_I_Code[102];
		long DATA2exp22 = pow(2,22);


	//    double Cur_V_Code_debug_1[64];
	//    double Cur_V_Code_debug_2[64];
	//    double Cur_I_Code_debug_1[102];
	//    double Cur_I_Code_debug_2[102];

		if(strstr(testname.c_str(),"C0")!=NULL){
			VI_DET_C0_Module(&SiteData);
		}
		else{
			VI_DET_C1_Module(&SiteData);
		}

		FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
			//int index = api->Get_active_site();
			for(int i=0;i<64;i++)
			{
	//                Cur_V_Code_debug_1[i] = (double)SiteData(index,i*2);
	//                Cur_V_Code_debug_2[i] = (double)SiteData(index,i*2+1);

				Cur_V_Code[i] = SiteData(index,i*2) + ((SiteData(index,i*2+1)&0x3f)<<16);
				if(SiteData(index,i*2+1)&0x20)
				{
					Cur_V_Code[i] = Cur_V_Code[i] - DATA2exp22;
				}
			}
			for(int j=0;j<102;j++)
			{
	//                Cur_I_Code_debug_1[j] = (double)SiteData(index,128+j*2);
	//                Cur_I_Code_debug_2[j] = (double)SiteData(index,128+j*2+1);

				Cur_I_Code[j] = SiteData(index,128+j*2) + ((SiteData(index,128+j*2+1)&0x3f)<<16);
				if(SiteData(index,128+j*2+1)&0x20)
				{
					Cur_I_Code[j] = Cur_I_Code[j] - DATA2exp22;
				}
			}

	//            api->Set_curve_data("CAL_V_1", 0, 1/80e6, 64, Cur_V_Code_debug_1);
	//            api->Set_curve_data("CAL_V_2", 0, 1/80e6, 64, Cur_V_Code_debug_2);
	//            api->Set_curve_data("CAL_I_1", 0, 1/80e6, 102, Cur_I_Code_debug_1);
	//            api->Set_curve_data("CAL_I_2", 0, 1/80e6, 102, Cur_I_Code_debug_2);


			Calc_VI_Det(Cur_V_Code,Cur_I_Code, &tempFlow, &Delt, &Delt_Index, &FirstVal, &LastVal, &Near_125K_Val,\
					&Near_125K_Val_index, &Poly_Max, &Poly_Min, &I_FirstCode, &I_FirstData, &I_HalfCycle, &I_VppL, &I_CycleL,\
					&I_VppH, &I_CycleH, &I_FlatnessL, &I_FlatnessH);

			ValueTest (index, "SSI_DATA", Delt/divider, lowl[0], hil[0], Units[0], Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
			ValueTest (index, "SSI_DATA", Delt_Index, lowl[1], hil[1], Units[1], Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
			ValueTest (index, "SSI_DATA", FirstVal/divider, lowl[2], hil[2], Units[2], Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);
			ValueTest (index, "SSI_DATA", LastVal/divider, lowl[3], hil[3], Units[3], Test_Item[3], "FAIL_BIN", Test_number[3], Clogenable);
			ValueTest (index, "SSI_DATA", Near_125K_Val/divider, lowl[4], hil[4], Units[4], Test_Item[4], "FAIL_BIN", Test_number[4], Clogenable);
			ValueTest (index, "SSI_DATA", Near_125K_Val_index, lowl[5], hil[5], Units[5],Test_Item[5], "FAIL_BIN", Test_number[5], Clogenable);
			ValueTest (index, "SSI_DATA", Poly_Max/divider, lowl[6], hil[6], Units[6], Test_Item[6], "FAIL_BIN", Test_number[6], Clogenable);
			ValueTest (index, "SSI_DATA", Poly_Min/divider, lowl[7], hil[7], Units[7], Test_Item[7], "FAIL_BIN", Test_number[7], Clogenable);
			ValueTest (index, "SSI_DATA", I_FirstCode, lowl[8], hil[8], Units[8], Test_Item[8], "FAIL_BIN", Test_number[8], Clogenable);
			ValueTest (index, "SSI_DATA", I_FirstData/divider, lowl[9], hil[9], Units[9], Test_Item[9], "FAIL_BIN", Test_number[9], Clogenable);
			ValueTest (index, "SSI_DATA", I_HalfCycle, lowl[10], hil[10], Units[10],Test_Item[10], "FAIL_BIN", Test_number[10], Clogenable);
			ValueTest (index, "SSI_DATA", I_VppL/(divider*2)+(I_FirstData/divider), lowl[11], hil[11], Units[11], Test_Item[11], "FAIL_BIN", Test_number[11], Clogenable);
			ValueTest (index, "SSI_DATA", I_VppL/(divider), lowl[12], hil[12], Units[12], Test_Item[12], "FAIL_BIN", Test_number[12], Clogenable);
			ValueTest (index, "SSI_DATA", I_VppL/(divider)-(I_VppH/divider), lowl[13], hil[13], Units[13], Test_Item[13], "FAIL_BIN", Test_number[13], Clogenable);
			ValueTest (index, "SSI_DATA", I_CycleL, lowl[14], hil[14], Units[14], Test_Item[14], "FAIL_BIN", Test_number[14], Clogenable);
			ValueTest (index, "SSI_DATA", (409.5/I_CycleL), lowl[15], hil[15], Units[15], Test_Item[15], "FAIL_BIN", Test_number[15], Clogenable);
			ValueTest (index, "SSI_DATA", I_CycleL-I_CycleH, lowl[16], hil[16], Units[16],Test_Item[16], "FAIL_BIN", Test_number[16], Clogenable);
			ValueTest (index, "SSI_DATA", I_FlatnessL/divider, lowl[17], hil[17], Units[17], Test_Item[17], "FAIL_BIN", Test_number[17], Clogenable);

		FOREACH_ACTIVESITE_END


    }
};



REGISTER_TESTCLASS("CAL_VI_DET",CAL_VI_DET)


























