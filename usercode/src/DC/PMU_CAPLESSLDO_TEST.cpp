/*
 * PMU_CAPLESSLDO_TEST.cpp
 *
 *  Created on: 2021年8月16日
 *      Author: YK16
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

using namespace PhxAPI;
using namespace PinTool;

class PMU_CAPLESS_LDO_TEST: public TestClass{
public:
		std::string pinlist;
		int samplesize;
		double iforce;
		double irange;
		double waittime;

    void init(){
		add_param( "Measure_pinlist",  "PinString", &pinlist);
		add_param("SampleSize","int",&samplesize);
		add_param("IForce","double",&iforce);
		add_param("IRange","double",&irange);
		add_param("Waittime","double",&waittime);
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

		d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
		d2sProtocolSSI d2s_test;
		d2s_test.SSI_write(0x200,0x2000,false);
		d2s_test.SSI_write(0x202,0x40,false);
		d2s_test.SSI_write(0x124,0x10);
		d2s::d2s_LABEL_END();

		long muxRegs[9]={0x0,0x0,0x40,0x800,0x0,0x80,0x0,0x800,0x80};

		for(int i=0;i<3;i++){
			d2s::d2s_LABEL_BEGIN( "ssi", d2s_WorkMode);
			d2sProtocolSSI d2s_test;
			d2s_test.SSI_write(0x202,0x94,false);
			d2s_test.SSI_write(0x37C,muxRegs[i*3]);
			d2s_test.SSI_write(0x384,muxRegs[i*3+1]);
			d2s_test.SSI_write(0x202,0x40,false);
			d2s_test.SSI_write(0x148,muxRegs[i*3+2]);
			d2s::d2s_LABEL_END();

			TheInst.PPMU().Pins(pinlist).SetClear();
			TheInst.PPMU().Pins(pinlist).SetIRange(irange)
										.SetMeasureType(E_MEASURE)
										.SetMeasureMode(PhxAPI::E_DC_FI_MV)
										.Connect(true)
										.SetSampleSize(samplesize)
										.SetIForce(iforce)
										.SetWaitTime(waittime)
										.Measure();

			PinArrayDouble result = TheInst.PPMU().Pins(pinlist).GetMeasureResults();
			TheInst.PPMU().Pins(pinlist).Connect(false).Apply();
//			vector<string> pinname2 = SplitPinList(pinlist);
			TheSoft.Flow().TestLimit(pinlist,result,lowl[i], hil[i],Hard_Bin[i],Soft_Bin[i], Units[i], Test_Item[i], Test_number[i]);
		  }
	}
};
 REGISTER_TESTCLASS("PMU_CAPLESS_LDO_TEST",PMU_CAPLESS_LDO_TEST)
