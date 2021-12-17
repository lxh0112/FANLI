/*
 * PMU_IDD_OFF.cpp
 *
 *  Created on: 2021年8月18日
 *      Author: 荣耀
 */
#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include "UserDef.h"

using namespace PinTool;
using namespace PhxAPI;
class PMU_IDD_OFF: public TestClass{
public:
	std::string pinlist;
	int samplesize;
    double waittime;
//    PowerRange range;
	void init(){
					add_param("Measure_pinlist",  "PinString", &pinlist).set_default("gIDD_OFF");
					add_param("WaitTime","double",&waittime).set_default("0.08");
					add_param("SampleSize","int",&samplesize).set_default("2");
//					add_param("Rang","PowerRange",&range).set_default("2");
	}
    void execute(){
		double hil[30], lowl[30];
		vector<string> Test_Item;
		vector<string> Units;
		int Test_number[30],Soft_Bin[30],Hard_Bin[30];
		Read_Limit(lowl, hil, Test_Item, Test_number, Units, Soft_Bin,Hard_Bin);

		TheInst.DCVS().Power().Apply();
		TheInst.Digital().Level().Apply();
		TheInst.Digital().Timing().Apply();
		TheInst.Wait(5*ms);
		TheInst.DCVS().Pins("RF_VDD_TX2G_3P3_0").SetIRange(E_POWER_R250UA)
												.SetIClampH(250*uA)
												.SetIClampL(-250*uA)
												.Apply();
		TheInst.DCVS().Pins("VDD_PMU_3V3_IN2").SetIRange(E_POWER_R250UA )
											  .SetIClampH(250*uA)
											  .SetIClampL(-250*uA)
											  .Apply();
		TheInst.DCVS().Pins("RF_VDD_TX2G_3P3_1").SetIRange(E_POWER_R250UA )
												.SetIClampH(250*uA)
												.SetIClampL(-250*uA)
												.Apply();
		TheInst.Wait(5*ms);
		TheInst.DCVS().Pins(pinlist).SetMeasureMode(E_DC_MODE_MI)
									 .SetMeasureMethod(E_DC_METHOD_STATIC)
									 .SetReadMode(E_DC_MODE_MEASURE)
									 .SetMeasureOrder(E_DC_ORDER_GROUP)
									 .SetSampleSize(samplesize)
									 .SetWaitTime(waittime)//80ms
									 .Measure();
		PinArrayDouble result = TheInst.DCVS().Pins(pinlist).GetMeasureResults();
    	vector<string> pinname = GetGroupPinItems(pinlist);
		for(unsigned int i=0;i<pinname.size();i++)
		{
			TheSoft.Flow().TestLimit(pinname[i],result,lowl[i], hil[i],Hard_Bin[i],Soft_Bin[i], Units[i], Test_Item[i], Test_number[i]);
		}

	}

};

REGISTER_TESTCLASS("PMU_IDD_OFF",PMU_IDD_OFF)




