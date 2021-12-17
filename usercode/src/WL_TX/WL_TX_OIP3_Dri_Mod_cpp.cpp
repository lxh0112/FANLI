
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

class WL_TX_OIP3_Dri_Mod_cpp: public TestClass{
public:


    void init(){

    }

    void execute(){
//		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
//		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
		TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing

        double hil[30],lowl[30];
//        char *Test_Item[30],*Units[30];
        vector<string> Test_Item;
        vector<string> Units;
        int  Test_number[30];

        int Soft_Bin[30];
		int Hard_Bin[30];
		Read_Limit(lowl,hil,Test_Item,Test_number,Units,Soft_Bin,Hard_Bin);

        //Parameter definition here
        tyTestData RF_Test_Data;

        char Ana_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
        char RF_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
        char Ana_Src_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
        char RF_Cap_Signal[_MAX_NAME_SIZE_RF] = {"\0"};

        CCRfmxSpecAnResults mxSpecAnResults;
        SpecAnResultAttribute ResultAttribute;
        double pathloss[4];
        double Output_Power;
        double Result_im3;
        double Result_oip3;

        //1. Get test item information
        string testname = TheSoft.Flow().Test().GetCurrentTestName();
        Get_TestItem_Info(testname.c_str(), RF_Test_Data);
        Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
        Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);

        //2. Get Passloss
        Read_Pathloss(RF_Test_Data,pathloss);

        Driver_Mode_Setup();

        /********************dynamic write UPC code***************************************
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", d2s_WorkMode);
        d2sProtocolSSI d2s_test;
        d2s_test.SSI_write(0x200, 0x2000, false);
        d2s_test.SSI_write(0x202, 0x90, false);
        d2s_test.SSI_read(0x94, "OLD_TrimData_C0",9);//attention loss true
        d2s_test.SSI_read(0xA4, "OLD_TrimData_C1",9);//attention loss true
        d2s::d2s_LABEL_END();

        map<int, long long> OLD_TrimData_C0;
        map<int, long long> OLD_TrimData_C1;
        map<int, long long> TrimData_C0;
        map<int, long long> TrimData_C1;
        FOREACH_ACTIVE_SITE(api){
            int site_id = api->Get_active_site();

            long long readvalue1 = d2s_test.getReadValue("OLD_TrimData_C0");
            long long readvalue2 = d2s_test.getReadValue("OLD_TrimData_C1");
            OLD_TrimData_C0[site_id] = readvalue1;
            OLD_TrimData_C1[site_id] = readvalue2;
            TrimData_C0[site_id] =  OLD_TrimData_C0[site_id] * 0.29 + 0.5;
            TrimData_C1[site_id] =  OLD_TrimData_C1[site_id] * 0.29 + 0.5;

            ValueTest (api, RF_CapPin, TrimData_C0[site_id], lowl[3], hil[3], "dB", "UPC_CODE_C0", "FAIL_BIN", Test_number[3], Clogenable);
            ValueTest (api, RF_CapPin, TrimData_C1[site_id], lowl[3], hil[3], "dB", "UPC_CODE_C1", "FAIL_BIN", Test_number[3], Clogenable);

        }
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "dynamic", d2s_WorkMode);
        d2s_test.SSI_writeDynamic(0x94, TrimData_C0,"write"); //Set C0 M UPC Code
        d2s_test.SSI_writeDynamic(0xA4, TrimData_C1,"write"); //Set C1 M UPC Code
        d2s::d2s_LABEL_END();
        *******************************************************************/

        Set_RF_TX_Pll_BW((emMode)RF_Test_Data.iMode, (emTX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);

        CCRFTester.SelectSites("site0,site2");
        SrcUtilitySites0();
        //3.2  Load source and capture signal
        CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
        CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();

        CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
        CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
        CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);

        CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
        CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
#ifdef semi_parallel_en
        CCRFTester.SelectSites("site1,site3");
        SrcUtilitySites1();
        //3.2  Load source and capture signal
        CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
        CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();

        //3.  Load capture signal
        CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
        CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
        CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);

        CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
        CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
        SrcUtilitySites0();                                                      //recover Relay state
#endif
        FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
            int site_id = index;
            Testsoftbin[site_id] = 1;//softbin flag
            ResultAttribute = mxSpecAnResults[site_id];
            calc_WL_TX_OIP3_Dri_Mode(&RF_Test_Data,&ResultAttribute,pathloss[site_id], &Output_Power, &Result_im3, &Result_oip3);

            TheSoft.Flow().TestLimit (RF_CapPin,site_id, Output_Power, lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], Units[0], Test_Item[0],Test_number[0]);
            TheSoft.Flow().TestLimit (RF_CapPin,site_id, Result_im3, lowl[1], hil[1],Hard_Bin[1],Soft_Bin[1], Units[1], Test_Item[1],Test_number[1]);
            TheSoft.Flow().TestLimit (RF_CapPin,site_id, Result_oip3, lowl[2], hil[2],Hard_Bin[2],Soft_Bin[2], Units[2], Test_Item[2], Test_number[2]);
        FOREACH_ACTIVESITE_END

        /********************dynamic write UPC code***************************************
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "dynamic", d2s_WorkMode);
        d2s_test.SSI_writeDynamic(0x94, OLD_TrimData_C0,"write"); //Set C0 M UPC Code
        d2s_test.SSI_writeDynamic(0xA4, OLD_TrimData_C1,"write"); //Set C1 M UPC Code
        d2s::d2s_LABEL_END();
         * *******************************************************************/

        Driver_Mode_Recover_Setup();

        FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
            int site_id = index;
            if(Testsoftbin[site_id]!=1){
//???             api->Set_result_bin(Testsoftbin[site_id]);
            }
        FOREACH_ACTIVESITE_END


    }
};
REGISTER_TESTCLASS("WL_TX_OIP3_Dri_Mod_cpp",WL_TX_OIP3_Dri_Mod_cpp)


