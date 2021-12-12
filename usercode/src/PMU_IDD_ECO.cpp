//
// Created by f.he on 2021/6/18.
//

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>

using namespace PhxAPI;
using namespace PinTool;

class PMU_ECO_IDD: public TestClass{
public:
    std::string pinlist;
    int samplesize;

	void init(){
					add_param( "Measure_pinlist",  "PinString", &pinlist);
					add_param("SampleSize","int",&samplesize).set_default("12");
	}
    void execute(){
					uint32_t UBIT[8] = {0,15,38,74,42,3,29,83};

					for(int i=0;i<8;i++)
					{
						TheInst.Util().SetRelayState(UBIT[i],PhxAPI:: E_UTIL_STATE_OFF);
					}
					TheInst.Wait(4*ms);
					TheInst.DCVS().Power().Apply();
					TheInst.Digital().Level().Apply();
					TheInst.Digital().Timing().Apply();
					TheInst.Digital().Pattern().Start();
					TheInst.Wait(5*ms);


					TheInst.DCVS().Pins("RF_VDD_TX2G_3P3_0").SetIRange(E_POWER_R250UA)
															.SetIClampL(-200*uA)
															.SetIClampH(200*uA)
															.Apply();
					TheInst.DCVS().Pins("RF_VDD_TX2G_3P3_1").SetIRange(E_POWER_R250UA)
															.SetIClampL(-200*uA)
															.SetIClampH(200*uA)
															.Apply();

					TheInst.DCVS().Pins("RF_VDD_TX5G_3P3_0").SetIRange(E_POWER_R250UA)
															.SetIClampL(-200*uA)
															.SetIClampH(200*uA)
															.Apply();

					TheInst.DCVS().Pins("RF_VDD_TX5G_3P3_1").SetIRange(E_POWER_R250UA)
															.SetIClampL(-200*uA)
															.SetIClampH(200*uA)
															.Apply();
					TheInst.DCVS().Pins("DBB_VDDIO_3V3").SetIRange(E_POWER_R25UA)
														.SetIClampL(-20*uA)
														.SetIClampH(20*uA)
														.Apply();
					TheInst.Wait(5*ms);
					TheInst.DCVS().Pins(pinlist).SetMeasureMode(PhxAPI::E_DC_MODE_MI)
												.SetMeasureMethod(PhxAPI::E_DC_METHOD_STATIC)
												.SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
												.SetMeasureOrder(PhxAPI::E_DC_ORDER_GROUP)
												.SetSampleSize(samplesize)
												.SetWaitTime(500*us)
												.Measure();

					PinArrayDouble Idd_ECO_result = TheInst.DCVS().Pins(pinlist).GetMeasureResults();
			//    	vector<string> pinname = SplitPinList(pinlist);
			//    	for(int i=0;i<pinname.size();i++)
			//		{
			//    		TheSoft.Flow().TestLimit(pinname[i],Idd_ECO_result);
			//		}
					TheSoft.Flow().TestLimit(pinlist,Idd_ECO_result);
                    }

};



REGISTER_TESTCLASS("PMU_ECO_IDD",PMU_ECO_IDD)

