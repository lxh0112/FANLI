/*
 * TSENSOR_TEST.cpp
 *
 *  Created on: 2021年8月18日
 *      Author: 荣耀
 */

#include "Globle_Var.h"
#include "TestClass.h"
#include <iostream>
#include <string>
#include "UserAPI.h"
#include "d2sProtocolSSI.h"
#include "D2S_PMU_Module.h"
#include <math.h>
#include "UserDef.h"


using namespace std;
using namespace PinTool;

class Tsensor_Test: public TestClass{
public:

	void init(){

	}

    void execute(){
    	double hil[30] = {0.0}, lowl[30] = {0.0};
    	vector<string> Test_Item;
    	vector<string> Units;
    	Test_Item.clear();
    	Units.clear();
    	int Test_number[30] = {0},Soft_Bin[30],Hard_Bin[30];
    	Read_Limit(lowl, hil, Test_Item, Test_number, Units, Soft_Bin,Hard_Bin);

        TheInst.DCVI().Power().Apply();
        TheInst.Digital().Level().Apply();
		TheInst.Digital().Timing().Apply();
		TheInst.Digital().PatEng().SetFailMode(PhxAPI::E_SET_HIL_MODE);
		TheInst.Digital().Pattern().Run(); //执行pattern，并判定bin 信息



		TSENSOR_PAmodule();
    }

};


REGISTER_TESTCLASS("Tsensor_Test",Tsensor_Test)



