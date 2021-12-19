//
// Created by f.he on 2021/6/18.
//
#include <helpers.h>
#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include "UserDef.h"

using namespace PhxAPI;
using namespace PinTool;

class Basic_00_PowerShort: public TestClass{
public:
    std::string powerpinlist;

    int samplesize;
    double waittime;



    void init(){
    	//gOS_PS 0.005 2
		add_param( "powerpinlist",  "PinString", &powerpinlist);
		add_param("WaitTime","double",&waittime);
		add_param("SampleSize","int",&samplesize);
	}



    void execute(){
		double hil[30], lowl[30];
		vector<string> Test_Item;
		vector<string> Units;
		int Test_number[30],Soft_Bin[30],Hard_Bin[30];
//		Read_Limit(lowl, hil, Test_Item, Test_number, Units, Soft_Bin,Hard_Bin);

		TheInst.DCVI().Power().Apply();
		TheInst.DCVI().Pins(powerpinlist).SetMeasureMode(PhxAPI::E_DC_MODE_MI)
										 .SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
										 .SetMeasureMethod(PhxAPI::E_DC_METHOD_STATIC)
										 .SetMeasureOrder(PhxAPI::E_DC_ORDER_GROUP)
										 .SetSampleSize(samplesize)
										 .SetWaitTime(waittime)//5ms
										 .Measure();
		PinArrayDouble  Result=TheInst.DCVI().Pins(powerpinlist).GetMeasureResults();
		vector<string> pinname = GetGroupPinItems(powerpinlist);

		for(unsigned int i=0;i<pinname.size();i++)
		{
			TheSoft.Flow().TestLimit(pinname[i],Result,lowl[i], hil[i],Hard_Bin[i],Soft_Bin[i], Units[i], Test_Item[i], Test_number[i]);
		}

	}
};

REGISTER_TESTCLASS("Basic_00_PowerShort",Basic_00_PowerShort)

