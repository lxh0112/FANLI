/*
 * BUCKLoading.cpp
 *
 *  Created on: 2021年8月19日
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
#include"Getlog.h"
#include "UserDef.h"

class BUCKLoading: public TestClass{
public:
	   std::string pinlist;
	   int samplesize;
	   double waittime;
    void init(){
				  add_param( "Measure_pinlist",  "PinString", &pinlist).set_default("VDD_BUCK_1V5_IN");//VDD_BUCK_1V5_IN
				  add_param("WaitTime","double",&waittime).set_default("0.0001");
				  add_param("SampleSize","int",&samplesize).set_default("2");
               }

    void execute(){
		double hil[30],lowl[30];
		vector<string> Test_Item;
		vector<string> Units;
		int Test_number[30];
		int Soft_Bin[30];
		int Hard_Bin[30];
		Read_Limit(lowl, hil, Test_Item, Test_number, Units, Soft_Bin,Hard_Bin);

		TheInst.DCVS().Power().Apply();
		TheInst.Digital().Level().Apply();
		TheInst.DCVS().Pins(pinlist).SetMeasureMode(PhxAPI::E_DC_MODE_MV)
									.SetMeasureMethod(PhxAPI::E_DC_METHOD_STATIC)
									.SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
									.SetMeasureOrder(PhxAPI::E_DC_ORDER_SINGLE)
									.SetSampleSize(samplesize)
									.SetWaitTime(waittime)//100us
									.Measure();
		PinArrayDouble result = TheInst.DCVS().Pins(pinlist).GetMeasureResults();
//		result.ShowPinArrayData();
//		TheSoft.Flow().TestLimit(pinlist,result ,lowl[0], hil[0],Hard_Bin[0], Soft_Bin[0],"",Test_Item[0], Test_number[0],PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);

		d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
		d2sProtocolSSI d2s_test;
		d2s_test.SSI_write(0x200,0x2000,false);
		d2s_test.SSI_write(0x202,0x0,false);
		d2s_test.SSI_read(0x4,"readdata",7);
		d2s::d2s_LABEL_END();

		map<int, long long> capture_data;
		map<int, long long> iter = d2s_test.getReadValue("readdata");
		for(map<int, long long>::iterator it = iter.begin(); it != iter.end(); it++) {
			long long readvalue =it->second;
			capture_data[it->first] = readvalue;
		}
		TheSoft.Flow().TestLimit("SSI_DATA" ,capture_data,lowl[0], hil[0],Hard_Bin[0], Soft_Bin[0],"",Test_Item[0], Test_number[0],PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);

	}
};
REGISTER_TESTCLASS("BUCKLoading",BUCKLoading)
