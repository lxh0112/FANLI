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

using namespace PinTool;

class PMU_IDD_OFF: public TestClass{
public:
	std::string pinlist;
	int samplesize;

	void init(){
					add_param("Measure_pinlist",  "PinString", &pinlist);
					add_param("SampleSize","int",&samplesize).set_default("12");
	}
    void execute(){
					TheInst.DCVS().Power().Apply();
					TheInst.Digital().Level().Apply();
					TheInst.Digital().Timing().Apply();
					TheInst.Wait(5*ms);
					TheInst.DCVS().Pins("RF_VDD_TX2G_3P3_0").SetIRange(PhxAPI::E_POWER_R250UA )
															.SetIClampH(250*uA)
															.SetIClampL(-250*uA)
															.Apply();
					TheInst.DCVS().Pins("VDD_PMU_3V3_IN2").SetIRange(PhxAPI::E_POWER_R250UA )
														  .SetIClampH(250*uA)
														  .SetIClampL(-250*uA)
														  .Apply();
					TheInst.DCVS().Pins("RF_VDD_TX2G_3P3_1").SetIRange(PhxAPI::E_POWER_R250UA )
															.SetIClampH(250*uA)
															.SetIClampL(-250*uA)
															.Apply();
					TheInst.Wait(5*ms);
					TheInst.DCVS().Pins(pinlist).SetMeasureMode(PhxAPI::E_DC_MODE_MI)
												 .SetMeasureMethod(PhxAPI::E_DC_METHOD_STATIC)
												 .SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
												 .SetMeasureOrder(PhxAPI::E_DC_ORDER_GROUP)
												 .SetSampleSize(samplesize)
												 .SetWaitTime(80*ms)
												 .Measure();
					PinArrayDouble result = TheInst.DCVS().Pins(pinlist).GetMeasureResults();
			//    	vector<string> pinname = SplitPinList(pinlist);
			//    	    	for(int i=0;i<pinname.size();i++)
			//    			{
			//    				TheSoft.Flow().TestLimit(pinname[i],result);
			//    			}

					TheSoft.Flow().TestLimit(pinlist,result);
					}

};


REGISTER_TESTCLASS("PMU_IDD_OFF",PMU_IDD_OFF)




