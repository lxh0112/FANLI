
#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include "D2S_CAL_Module.h"
//#include "Globle_Var.h"
#include "CCS08F.h"
#include "Excel.h"
#include "RegDef.h"
#include "d2sProtocolSSI.h"
#include "UserDef.h"


using namespace PhxAPI;

class CAL_TX_IQ: public TestClass{
public:


    void init(){

    }

    void execute(){
//		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
//		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
		TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing

        string testname = TheSoft.Flow().Test().GetCurrentTestName();

        if(strstr(testname.c_str(),"C0")!=NULL){
            Cal_ABB_RF_5G_Init_Module();
        }

        if(strstr(testname.c_str(),"C0")!=NULL){
            TXIQ_5G_C0_Module();
        }
        else{
            TXIQ_5G_C1_Module();
        }


    }
};
REGISTER_TESTCLASS("CAL_TX_IQ",CAL_TX_IQ)

