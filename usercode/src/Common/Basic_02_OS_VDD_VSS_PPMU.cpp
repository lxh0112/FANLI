//
// Created by f.he on 2021/6/18.
//

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include "UserDef.h"

using namespace PhxAPI;
using namespace PinTool;

class Basic_02_OS_VDD_VSS_PPMU: public TestClass{
public:
    std::string pinlist;
    double iforce;
	double vclampl;
	double vclamph;
	double range;
	int samplesize;
	double waittime;

    void init(){
					add_param( "Measure_pinlist",  "PinString", &pinlist).set_default("");
					add_param("IForce","double",&iforce).set_default("");
					add_param("Range","double",&range).set_default("");
					add_param("VClampL","double",&vclampl).set_default("-2");
					add_param("VClampH","double",&vclamph).set_default("2");
					add_param("WaitTime","double",&waittime).set_default("0.005");
					add_param("SampleSize","int",&samplesize).set_default("2");
               }

    void execute(){
		double hil[30], lowl[30];
		vector<string> Test_Item;
		vector<string> Units;
		int Test_number[30],Soft_Bin[30],Hard_Bin[30];
		Read_Limit(lowl, hil, Test_Item, Test_number, Units, Soft_Bin,Hard_Bin);

		TheInst.DCVS().Power().Apply();
		TheInst.PPMU().Pins(pinlist).SetClear();
		TheInst.PPMU().Pins(pinlist).SetMeasureType(PhxAPI::E_MEASURE)
									.SetVClampL(vclampl)
									.SetVClampH(vclamph)
									.SetIRange(range)
									.SetIForce(iforce)
									.SetMeasureMode(PhxAPI::E_DC_FI_MV)
									.Connect(true)
									.SetSampleSize(samplesize)
									.SetWaitTime(waittime)//5ms
									.Measure();
		PinArrayDouble result = TheInst.PPMU().Pins(pinlist).GetMeasureResults();
		TheInst.PPMU().Pins(pinlist).Connect(false).Apply();
		vector<string> pinname = GetGroupPinItems(pinlist);

		for(unsigned int i=0;i<pinname.size();i++)
		{
			TheSoft.Flow().TestLimit(pinname[i],result,lowl[i], hil[i],Hard_Bin[i],Soft_Bin[i], Units[i], Test_Item[i], Test_number[i]);
		}
	 }

};

REGISTER_TESTCLASS("Basic_02_OS_VDD_VSS_PPMU",Basic_02_OS_VDD_VSS_PPMU)

