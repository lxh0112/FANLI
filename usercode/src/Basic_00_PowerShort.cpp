//
// Created by f.he on 2021/6/18.
//

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>

using namespace PhxAPI;
using namespace PinTool;

class Basic_00_PowerShort: public TestClass{
public:
    std::string powerpinlist;

    int samplesize;

    void init(){
					add_param( "powerpinlist",  "PinString", &powerpinlist);
					add_param("SampleSize","int",&samplesize).set_default("16");
                }

    void execute(){
					TheInst.DCVS().Power().Apply();


					TheInst.DCVS().Pins(powerpinlist).SetMeasureMode(PhxAPI::E_DC_MODE_MI)
													 .SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
													 .SetMeasureMethod(PhxAPI::E_DC_METHOD_STATIC)
													 .SetMeasureOrder(PhxAPI::E_DC_ORDER_GROUP)
													 .SetSampleSize(samplesize)
													 .SetWaitTime(5*ms)
													 .Measure();
					PinArrayDouble  Result=TheInst.DCVS().Pins(powerpinlist).GetMeasureResults();
					vector<string> pinname = SplitPinList(powerpinlist);
					for(int i=0;i<pinname.size();i++)
					{
						TheSoft.Flow().TestLimit(pinname[i],Result);
					}
                    }
};


REGISTER_TESTCLASS("Basic_00_PowerShort",Basic_00_PowerShort)

