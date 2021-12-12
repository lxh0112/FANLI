//
// Created by f.he on 2021/6/18.
//

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>

using namespace PhxAPI;
using namespace PinTool;

class Basic_02_OS_VDD_VSS_PPMU: public TestClass{
public:
    std::string pinlist;
    double iforce;
	double vclampl;
	double vclamph;
	double range;
	int sampleSize;

    void init(){
					add_param( "Measure_pinlist",  "PinString", &pinlist).set_default("");
					add_param("IForce","double",&iforce).set_default("");
					add_param("Range","double",&range).set_default("");
					add_param("VClampL","double",&vclampl).set_default("");
					add_param("VClampH","double",&vclamph).set_default("");
					add_param("SampleSize","int",&sampleSize).set_default("16");
               }

    void execute(){
					TheInst.DCVS().Power().Apply();
					TheInst.PPMU().Pins(pinlist).SetClear();
					TheInst.PPMU().Pins(pinlist).SetMeasureType(PhxAPI::E_MEASURE)
												.SetVClampL(vclampl)
												.SetVClampH(vclamph)
												.SetIRange(range)
												.SetIForce(iforce)
												.SetMeasureMode(PhxAPI::E_DC_FI_MV)
												.Connect(true)
												.SetSampleSize(sampleSize)
												.SetWaitTime(5*ms)
												.Measure();
					PinArrayDouble result = TheInst.PPMU().Pins(pinlist).GetMeasureResults();
					TheInst.PPMU().Pins(pinlist).Connect(false).Apply();
				    cout<<"=========Force:"<<iforce<<endl;
					vector<string> pinname = SplitPinList(pinlist);
					for(int i=0;i<pinname.size();i++)
					    {
						 TheSoft.Flow().TestLimit(pinname[i],result);
					    }
				  }

};

REGISTER_TESTCLASS("Basic_02_OS_VDD_VSS_PPMU",Basic_02_OS_VDD_VSS_PPMU)

