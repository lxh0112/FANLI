#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
//#include "D2S_CAL_Module.h"
//#include "Globle_Var.h"
//#include "GetLog.h"
#include "CCS08F.h"
#include "Excel.h"
#include "RegDef.h"
#include "d2sProtocolSSI.h"
#include "UserDef.h"
#include "Test_TX_cpp.h"

using namespace PhxAPI;

class WL_TX_Mask_cpp: public TestClass{
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

        CCMxWlanResults MxWlanResults;
        WlanResultsAttribute ResultsAttribute;
        double Result_freq_L;
        double Result_freq_R;
        double Result_power_L;
        double Result_power_R;
        double Channel_Power;
        double pathloss[4];

        //1. Get test item information
        string testname = TheSoft.Flow().Test().GetCurrentTestName();
        Get_TestItem_Info(testname.c_str(), RF_Test_Data);
        Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
        Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);

        //2. Get Passloss
        Read_Pathloss(RF_Test_Data,pathloss);

        //3. DUT register setting
        TX_PLL_Setup((emMode)RF_Test_Data.iMode, (emTX_Band)RF_Test_Data.iBand, RF_Test_Data.cChannel, RF_Test_Data.dBW);
        d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
        d2sProtocolSSI d2s_test;
        d2s_test.SSI_write(0x200, 0x2000, false);
        d2s_test.SSI_write(0x202, 0x90, false);
        d2s_test.SSI_write(0xC, 0x2F);     //wl_trx_reg3
        d2s_test.SSI_write(0x10, 0x2F);
        d2s::d2s_LABEL_END();


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
        SrcUtilitySites0();                                                      //recover Relay state
#endif
        FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
            /* site: 0,2,3 */
            int site_id = index;
            ResultsAttribute = MxWlanResults[site_id];
            Result_freq_L=ResultsAttribute.SEM.LowerOffsetMargin.dMarginFrequency/1e6;
            Result_freq_R=ResultsAttribute.SEM.UpperOffsetMargin.dMarginFrequency/1e6;
            Result_power_L=ResultsAttribute.SEM.LowerOffsetMargin.dMargin;
            Result_power_R=ResultsAttribute.SEM.UpperOffsetMargin.dMargin;
            Channel_Power = ResultsAttribute.SEM.CarrierMeasurement.dAbsolutePower+pathloss[site_id];

            TheSoft.Flow().TestLimit(RF_CapPin,site_id, Channel_Power, lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], Units[0], Test_Item[0],Test_number[0]);
            TheSoft.Flow().TestLimit(RF_CapPin,site_id, Result_freq_L, lowl[3], hil[3],Hard_Bin[3],Soft_Bin[3], Units[3], Test_Item[3],Test_number[3]);
            TheSoft.Flow().TestLimit(RF_CapPin,site_id, Result_power_L, lowl[4], hil[4],Hard_Bin[4],Soft_Bin[4], Units[4], Test_Item[4],Test_number[4]);
            TheSoft.Flow().TestLimit(RF_CapPin,site_id, Result_freq_R, lowl[5], hil[5],Hard_Bin[5],Soft_Bin[5], Units[5], Test_Item[5],Test_number[5]);
            TheSoft.Flow().TestLimit(RF_CapPin,site_id, Result_power_R, lowl[6], hil[6],Hard_Bin[6],Soft_Bin[6], Units[6], Test_Item[6], Test_number[6]);
         FOREACH_ACTIVESITE_END

    }
};
REGISTER_TESTCLASS("WL_TX_Mask_cpp",WL_TX_Mask_cpp)




