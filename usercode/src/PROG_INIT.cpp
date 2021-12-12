#include "D2S_PMU_Module.h"
#include "TestClass.h"
#include <d2s.h>
#include <iostream>
#include <UserAPI.h>
#include "d2sProtocolSSI.h"
#include "Globle_Var.h"
#include"readlimit.h"
#include"Test_CAL.h"
#include <fstream>
#include <algorithm>
#include <math.h>
#include <vector>
//#include "MT_DSP_Lib.h"
//#include "UserDef.h"
#include "GetLog.h"
class PROG_INIT: public TestClass{
public:
	 void init(){

	    }

//     void Globle_Array_Init()
//     {
//     	  FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
//     //                int site_id = api->Get_active_site();
//             WL_C0_PPF_CODE.InitDataArray(site_id,32);
//             WL_C1_PPF_CODE.InitDataArray(site_id,32);
//
//             for(int i = 0;i<32;i++)
//             {
//                 WL_C0_PPF_CODE.SetElement(site_id,0,-999);
//                 WL_C1_PPF_CODE.SetElement(site_id,0,-999);
//
//
//         }
//     //    TRIM_DATA_LIST_C0[10][4];
//     //    TRIM_DATA_LIST_C1[10][4];
//     //    RX_GAIN_MAX_I_C0[10][4];
//     //    RX_GAIN_MAX_I_C1[10][4];
//         memset(TRIM_DATA_LIST_C0,0 ,sizeof(TRIM_DATA_LIST_C0));
//         memset(TRIM_DATA_LIST_C1,0 ,sizeof(TRIM_DATA_LIST_C1));
//         memset(RX_GAIN_MAX_I_C0,0 ,sizeof(RX_GAIN_MAX_I_C0));
//         memset(RX_GAIN_MAX_I_C1,0 ,sizeof(RX_GAIN_MAX_I_C1));
//
//
//     FOREACH_ACTIVESITE_END
//     }
//
//     int LoadSignalSetting()
//     {
//         int error = 0;
//         char TemplatePath[512] = {"\0"};
//         char PathlossPath[512] = {"\0"};
//         char WaveFormPath[512] = {"\0"};
//     //    char WaveFormPath[512] = {"\0"};
//        std::string programPath = TheSoft.GetProgramPath();
//         sprintf(TemplatePath, "%s/TestPlan.xlsx",programPath);
//         sprintf(PathlossPath, "%s/Hi1151GNCV200_FTx4_S08F_CAL_N10.xlsx.lnk",programPath);
//         sprintf(WaveFormPath, "%s/Waveforms",programPath);
//
////         ErrorCheck (LoadAllSignalAttr(TemplatePath,PathlossPath));
////     errHandler:
////         if(Test_Success != error)
////         {
////             api->set_result_bin_name("FAIL_BIN");
////         }
////         return EXIT_SUCCESS;
//     }


	    void execute(){
	    	//int Ubit_Power_on(API * api){
//	    	       api->set_loadboard_supplies(LBD_P5V,LBD_NONE);
//	    	       api->Set_loadboard_supplies(LBD_P5V, LBD_NONE, 5000);
	    	//       /****************close user clk before OS_PS ****************/
	    	//       CCRFTester.CHANNEL("XIN").setClkFreq(40);
	    	//       CCRFTester.CHANNEL("XIN").Close();
	    	//      	return EXIT_SUCCESS;
	    	//
	    	//}
              TheInst.Util().SetUserPower(PhxAPI::E_USERPW_P5V, PhxAPI::E_UTIL_STATE_ON);



//    d2s_WorkMode = ProductionMode;  //ProductionMode;  //LearningMode;
////    api->Set_loadboard_x_ubits(X_UBIT_NONE,X_UBIT_ALL);                         //recover All ubit state
//    for(uint32_t j=0;j<256;j++)
//    		{
//    			TheInst.Util().SetRelayState(j, PhxAPI::E_UTIL_STATE_OFF); //bihe-0,duankai-1
//    			TheInst.Wait(4*us);//us
//    		}
//    Clogenable = true;
//    Last_TestName="";
//    Globle_Array_Init();
//    CosSin_Value();
//    FOREACH_ACTIVE_SITE(api){
//        int site_id = api->Get_active_site();
//        HBIN_FLAG[site_id] = 0;
//    }
//         FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
//    {
//          HBIN_FLAG[site_id] = 0;
//    }
//          FOREACH_ACTIVESITE_END
////    const char * flowname = api->Get_current_flow_name();
//		  string flowname = TheSoft.Flow().GetCurrentFlowName();
//    if(strstr("flowname" , "QA")!=NULL){
//        CurrentLimitSet="QA";
//    }
//    else if(strstr("flowname", "GLD")!=NULL){
//        CurrentLimitSet="Golden";
//    }
//    else{
//        CurrentLimitSet="Default";
//    }
//
//    if(!TestInfoLoaded_Flag)
//    {
//        char pathFinal[256] = "\0";
//       std::string programPath = TheSoft.GetProgramPath();
////        const char *programPath = api->Get_program_path();
//       std::string limitsPath = "/TestLimit/Hi1151SV208_Limits.xlsx";
//        sprintf(pathFinal, "%s%s", programPath, limitsPath);
////        CBBLimits cbbLimits;
////       if(cbbLimits.ReadLimits(pathFinal, &mapLimits) != READ_SUCCESS)
//        {
////            return -1;
//        }
//        LoadSignalSetting();
//        TestInfoLoaded_Flag = true;
//
//        for(int i =0;i<4;i++)
//        {
//        PRE_VREF_ARRAY.InitDataArray(i,200);//lay init
//        PRE_BUCK_ARRAY.InitDataArray(i,200);//lay init
//        PRE_IREF_ARRAY.InitDataArray(i,200);//lay init
//        }
//    }
//
////    return EXIT_SUCCESS;

    }
};
REGISTER_TESTCLASS("PROG_INIT",PROG_INIT);


