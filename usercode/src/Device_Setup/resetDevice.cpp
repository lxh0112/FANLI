#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include "CCS08F.h"
#include "D2S_ABB_Module.h"

using namespace PhxAPI;

class resetDevice: public TestClass{
public:


    void init(){

    }

    void execute(){

		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
		TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing




    	PHY_ABB_RF_Reset_Module();
    }
};





REGISTER_TESTCLASS("resetDevice",resetDevice)




