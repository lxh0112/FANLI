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
        TheInst.DCVI().Power().Apply();
        TheInst.Digital().Level().Apply();

        double hil[30],lowl[30];
        vector<string> Test_Item;
		vector<string> Units;
        int  Test_number[30];
        int Soft_Bin[30];
		int Hard_Bin[30];
	//	Read_Limit(lowl,hil,Test_Item,Test_number,Units,Soft_Bin,Hard_Bin);

        d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
        d2sProtocolSSI d2s_test;
        d2s_test.SSI_write(0x200,0x2000,false);
        d2s_test.SSI_write(0x202,0x80,false);
        d2s_test.SSI_write(0x304,0x0);    //TSENSOR_CTRL1  1->0
        d2s_test.SSI_write(0x2EC,0x32);   //TSENSOR_CLK_DIV  0x28->0x32 20170428 for moving Tsensor after bootup , divide by 50 from SSI clock 50MHz
        d2s_test.SSI_write(0x2EC,0x128);   //TSENSOR_CLK_DIV

        d2s_test.SSI_write(0x200,0x2000,false);
        d2s_test.SSI_write(0x202,0x0,false);
        d2s_test.SSI_write(0x124,0xF);    //RF_PLL_CLK_EN


        d2s_test.SSI_write(0x200,0x2000,false);
        d2s_test.SSI_write(0x202,0x80,false);
        d2s_test.SSI_write(0x2F8,0x0);    //TSENSOR_CTRL
        d2s_test.SSI_write(0x2F8,0x1);    //TSENSOR_CTRL
        d2s_test.SSI_write(0x2F4,0x1);    //TSENSOR_START

        d2s_test.SSI_write(0x200,0x2000,false);
        d2s_test.SSI_write(0x202,0x80,false);

        for(int i=0;i<40;i++)
        d2s_test.wait(0.001);

        d2s_test.SSI_read(0x300,"readdata", 7);
        d2s_test.SSI_write(0x300,0x1);
        d2s::d2s_LABEL_END();

        map<int, double> tempVal;
		map<int, long long> iter = d2s_test.getReadValue("readdata");
		for(map<int, long long>::iterator it = iter.begin(); it != iter.end(); it++) {
			long long temp_data =it->second;
			int site_id = it->first;

	        tempVal[site_id] = ((temp_data &(0xFFC))/4.0);
	        tempVal[site_id]=(((tempVal[site_id]-118)/(933-118))*165)-40;
	        TSENSOR_TG[site_id] = (tempVal[site_id] - 15)/5 + 0.5;
	        TheSoft.Flow().TestLimit("SSI_DATA", site_id, double((temp_data & 0x2) >>1), lowl[0], hil[0],Hard_Bin[0] ,Soft_Bin[0],Units[0], Test_Item[0],Test_number[0],PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
	        TheSoft.Flow().TestLimit("SSI_DATA", site_id, tempVal[site_id], lowl[1], hil[1],Hard_Bin[0] ,Soft_Bin[0], Units[1], Test_Item[1],Test_number[1]);
		}

    }

};


REGISTER_TESTCLASS("Tsensor_Test",Tsensor_Test)


