
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


using namespace PhxAPI;

class TRX_Disable: public TestClass{
public:


    void init(){

    }

    void execute(){

		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
		TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing



    	WLAN_Disable_Reg();

    }
};
REGISTER_TESTCLASS("TRX_Disable",TRX_Disable)



