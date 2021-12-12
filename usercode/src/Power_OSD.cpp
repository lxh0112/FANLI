//
// Created by f.he on 2021/6/18.
//

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>

using namespace PhxAPI;
using namespace PinTool;

class power_osd: public TestClass{
public:
       std::string powerpinlist;

    void init(){
    	         add_param( "powerpinlist",  "PinString", &powerpinlist);
    }

    void execute(){

					string TName = TheSoft.Flow().Test().GetCurrentTestName();
					PHXSYS_LOGSTR_TRACE("-------------------------------------------");
					PHXSYS_LOGSTR_TRACE("------!!!Hello power_osd!!!------");
					PHXSYS_LOG_TRACE("The Current Test is : %s",TName.c_str());

					TheInst.DCVS().Power().Apply();
					string PowerName = TheSoft.Flow().Power().GetCurrentPowerBlockName();


					std::string pin = "PMU_RBIAS,PMU_REFBP,DBB_VDDIO_3V3,DBB_VDDIO_3V3_1V8,VDD_PMU_CLDO,VDD_PMU_3V3_O,VPTX_VP,VDD_PMU_SYSLDO,VDD_PMU_3V3_IN3,VDD_PMU_1V5_IN,VDD_BUCK_1V5_IN,VDD_PMU_3V3_IN1,VDD_PMU_3V3_IN2,RF_VDD_TX2G_3P3_0,RF_VDD_TX2G_3P3_1,RF_VDD_TX5G_3P3_0,RF_VDD_TX5G_3P3_1";

					PinArrayUInt result = TheInst.DCVS().Pins(pin).OpenKelDetect(0.5,0.5);

					vector<string> pinname = SplitPinList(pin);
					result.ShowPinArrayData();
					for(unsigned int i = 0; i < pinname.size(); i++){
						TheSoft.Flow().TestLimit(pinname[i] ,result ,0 ,0 ,2,2010,"","POWER_OSD",20100000+i,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
					}
					PHXSYS_LOGSTR_TRACE("-------------------------------------------");
					PHXSYS_LOGSTR_TRACE("------------------TEST END-----------------");
					PHXSYS_LOGSTR_TRACE("-------------------------------------------");
    }

};


REGISTER_TESTCLASS("power_osd",power_osd)

