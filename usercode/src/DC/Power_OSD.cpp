//
// Created by f.he on 2021/6/18.
//

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include "Globle_Var.h";

using namespace PhxAPI;
using namespace PinTool;

class power_osd: public TestClass{
public:
    std::string powerpinlist;

    void init(){
    	add_param( "powerpinlist",  "PinString", &powerpinlist);

    }

    void execute(){

    	//string TName = TheSoft.Flow().Test().GetCurrentTestName();
		PHXSYS_LOGSTR_TRACE("-------------------------------------------");
		PHXSYS_LOGSTR_TRACE("------!!!Hello power_osd!!!------");
		//PHXSYS_LOG_TRACE("The Current Test is : %s",TName.c_str());

		/* step1: apply current powerblock*/
		TheInst.DCVI().Power().Apply();
		//string PowerName = TheSoft.Flow().Power().GetCurrentPowerBlockName();

		std::string pin = "BOOST_LX,PMU_REFBP,PMUVCC12,PMUVCC3,SIMVCC1,SIMVCC2,SIMVCC3,VBAT,VDD_PMU_AIOLDO,VDD_PMU_CLDO,VDD_PMU_SYSLDO,VDDBOOST,VDDIO,VDDPA";
		PinArrayUInt result = TheInst.DCVI().Pins(pin).OpenKelDetect(0.5,0.5);//检测OSD

		vector<string> pinname = SplitPinList(pin);
		result.ShowPinArrayData();
		for(unsigned int i = 0; i < pinname.size(); i++){
			TheSoft.Flow().TestLimit(pinname[i] ,result ,0 ,0 ,2,2010,"","POWER_OSD",20100000+i,PhxAPI::E_FailStop,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
		}
		PHXSYS_LOGSTR_TRACE("-------------------------------------------");
		PHXSYS_LOGSTR_TRACE("------------------TEST END-----------------");
		PHXSYS_LOGSTR_TRACE("-------------------------------------------");
    }

};
REGISTER_TESTCLASS("power_osd",power_osd)

