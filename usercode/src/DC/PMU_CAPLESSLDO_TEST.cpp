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
		add_param("SampleSize","int",&samplesize).set_default("4");
		add_param("IForce","double",&iforce).set_default("0");
		add_param("IRange","double",&irange).set_default("1e-9");
//		add_param("Waittime","double",&waittime);
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

//		PMU_CAPLESS_LDO();

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
			TheSoft.Flow().TestLimit(pinlist,result,lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], Units[0], Test_Item[0], Test_number[0]);
		  }

};
 REGISTER_TESTCLASS("PMU_CAPLESS_LDO_TEST",PMU_CAPLESS_LDO_TEST)
