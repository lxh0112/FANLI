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

using namespace std;
using namespace PinTool;

class BOOT_UP: public TestClass{
public:

	void init(){
	            }
    void execute(){
					TheInst.DCVS().Power().Apply();
					TheInst.Digital().Level().Apply();
					TheInst.Digital().Timing().Apply();

			        double hil[30],lowl[30];
			        vector<string> Test_Item;
					vector<string> Units;
			        int  Test_number[30];
			        int Soft_Bin[30];
					int Hard_Bin[30];
					Read_Limit(lowl,hil,Test_Item,Test_number,Units,Soft_Bin,Hard_Bin);

					d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
					d2sProtocolSSI d2s_test;
					d2s_test.SSI_write(0x200,0x2000,false);

					d2s_test.SSI_write(0x236,0x1,false);
					d2s_test.SSI_write(0x232,0x3,false);
					d2s_test.SSI_write(0x234,0x0,false);

					for(int i=0;i<3;i++)
						d2s_test.wait(0.001);
					d2s_test.SSI_write(0x234,0xb,false);

					for(int i=0;i<3;i++)
						d2s_test.wait(0.001);
					d2s_test.SSI_write(0x200,0x2000,false);
					d2s_test.SSI_write(0x202,0x0,false);
					d2s_test.SSI_write(0x4,0x1151);
					d2s_test.SSI_write(0x8,0x1151);

					d2s_test.SSI_write(0x200,0x2000,false);
					d2s_test.SSI_write(0x202,0x40,false);
					d2s_test.SSI_write(0x4,0x1151);
					d2s_test.SSI_write(0x8,0x1151);

					d2s_test.SSI_write(0x200,0x2000,false);
					d2s_test.SSI_write(0x202,0x80,false);
					d2s_test.SSI_write(0x4,0x1151);
					d2s_test.SSI_write(0x8,0x1151);

					d2s_test.SSI_write(0x200,0x2000,false);
					d2s_test.SSI_write(0x202,0x40,false);
					d2s_test.SSI_write(0x204,0x9);
					d2s_test.SSI_write(0x208,0x6);

					d2s_test.SSI_write(0x200,0x2000,false);
					d2s_test.SSI_write(0x202,0x80,false);
					d2s_test.SSI_write(0x270,0x1);
					d2s_test.SSI_write(0x278,0x3);

					d2s_test.SSI_write(0x200,0x2000,false);
					d2s_test.SSI_write(0x202,0x40,false);
					d2s_test.SSI_write(0x124,0x20);
					d2s_test.SSI_write(0x16c,0x40);
					d2s_test.SSI_write(0x154,0x1A0);
					d2s_test.SSI_write(0x14c,0xffff);

					d2s_test.SSI_write(0x200,0x2000,false);
					d2s_test.SSI_write(0x202,0x90,false);
					d2s_test.SSI_write(0x84,0x0);

					d2s_test.SSI_write(0x200,0x2000,false);
					d2s_test.SSI_write(0x202,0x40,false);
					d2s_test.SSI_write(0x32c,0x1a);
					d2s_test.SSI_write(0x32c,0x1b);

					d2s_test.SSI_write(0x200,0x2000,false);
					d2s_test.SSI_write(0x202,0x40,false);

					d2s_test.SSI_read(0x154,"readdata",7);

					d2s::d2s_LABEL_END();

					map<int, long long> capture_data = d2s_test.getReadValue("readdata");

					TheSoft.Flow().TestLimit("SSI_DATA", capture_data, lowl[0], hil[0],Hard_Bin[0] ,Soft_Bin[0],Units[0], Test_Item[0],Test_number[0],PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);

				}

};

REGISTER_TESTCLASS("BOOT_UP",BOOT_UP)


