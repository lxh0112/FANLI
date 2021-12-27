/*
 * BOOT_UP.cpp
 *
 *  Created on: 2021年8月18日
 *      Author: 荣耀
 */




#include "TestClass.h"
#include <iostream>
#include <string>
#include "UserAPI.h"
#include "d2sProtocolSSI.h"
#include <math.h>
#include "Globle_Var.h"
#include "UserDef.h"
#include "D2S_PMU_Module.h"

using namespace std;
using namespace PinTool;

class BOOT_UP: public TestClass{
public:

	void init(){
	            }
    void execute(){
					TheInst.DCVI().Power().Apply();
					TheInst.Digital().Level().Apply();
	//				TheInst.Digital().Timing().Apply();

			        double hil[30],lowl[30];
			        vector<string> Test_Item;
					vector<string> Units;
			        int  Test_number[30];
			        int Soft_Bin[30];
					int Hard_Bin[30];
					Read_Limit(lowl,hil,Test_Item,Test_number,Units,Soft_Bin,Hard_Bin);


					d2sProtocolSSI d2s_test;
					BOOT_UP_PAmodule();



					map<int, long long> capture_data = d2s_test.getReadValue("readdata");

					TheSoft.Flow().TestLimit("SSI_DATA", capture_data, lowl[0], hil[0],Hard_Bin[0] ,Soft_Bin[0],Units[0], Test_Item[0],Test_number[0],PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);

				}

};

REGISTER_TESTCLASS("BOOT_UP",BOOT_UP)


