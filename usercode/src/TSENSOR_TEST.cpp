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
#include"readlimit.h"
#include"Getlog.h"

using namespace std;
using namespace PinTool;

class Tsensor_Test: public TestClass{
public:

	void init(){

	}
    void execute(){
					TheInst.DCVS().Power().Apply();
					TheInst.Digital().Level().Apply();

					double hil[30],lowl[30];
					char *Test_Item[30],*Units[30];
					int  Test_number[30];
					Read_Limit(lowl,hil,Test_Item,Test_number,Units);

					d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
					d2sProtocolSSI d2s_test;
					d2s_test.SSI_write(0x200,0x2000,false);
					d2s_test.SSI_write(0x202,0x80,false);
					d2s_test.SSI_write(0x304,0x0);
					d2s_test.SSI_write(0x2EC,0x32);
					d2s_test.SSI_write(0x2EC,0x128);

					d2s_test.SSI_write(0x200,0x2000,false);
					d2s_test.SSI_write(0x202,0x0,false);
					d2s_test.SSI_write(0x124,0xF);

					d2s_test.SSI_write(0x200,0x2000,false);
					d2s_test.SSI_write(0x202,0x80,false);
					d2s_test.SSI_write(0x2F8,0x0);
					d2s_test.SSI_write(0x2F8,0x1);
					d2s_test.SSI_write(0x2F4,0x1);

					d2s_test.SSI_write(0x200,0x2000,false);
					d2s_test.SSI_write(0x202,0x80,false);

					for(int i=0;i<40;i++)
					d2s_test.wait(0.001);

					d2s_test.SSI_read(0x300,"readdata");
					d2s_test.SSI_write(0x300,0x1);
					d2s::d2s_LABEL_END();

					map<int, double> tempVal;
					map<int, long long> iter = d2s_test.getReadValue("readdata");
					for(map<int, long long>::iterator it = iter.begin(); it != iter.end(); it++) {
						long long temp_data =it->second;
						int site_id = it->first;
						cout << "---------------------------start------------------------------------------" << endl;
						cout << "temp_data:" << temp_data << endl;

						tempVal[site_id] = ((temp_data &(0xFFC))/4.0);
						cout << "tempVal:" << tempVal[site_id] << endl;

						tempVal[site_id]=(((tempVal[site_id]-118)/(933-118))*165)-40;
						cout << "tempVal:" << tempVal[site_id] << endl;

						TSENSOR_TG[site_id] = (tempVal[site_id] - 15)/5 + 0.5;
						cout << "TSENSOR_TG:"<<TSENSOR_TG[site_id] << endl;

						cout << "TEMPERATURE:" << tempVal[site_id] << endl;
						cout << "---------------------------stop------------------------------------------" << endl;

		}

    }

};



REGISTER_TESTCLASS("Tsensor_Test",Tsensor_Test)


