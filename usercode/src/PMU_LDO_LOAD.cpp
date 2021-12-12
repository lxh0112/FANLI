/*
 * PMU_LDO_LOAD.cpp
 *
 *  Created on: 2021年8月17日
 *      Author: YK16
 */
#include "D2S_PMU_Module.h"
#include "TestClass.h"
#include <d2s.h>
#include <iostream>
#include <UserAPI.h>
#include "d2sProtocolSSI.h"
#include "Globle_Var.h"
#include"readlimit.h"
#include <string>
#define I2C_DELAY 		4

using namespace PhxAPI;
using namespace PinTool;

class PMU_LDO_LOAD: public TestClass{
public:
		std::string powerpinlist;
		std::string pinlist1;
		std::string pinlist2;
		std::string pinlist3;
		std::string pinlist4;
		std::string pinlist5;
		std::string pinlist6;
		double iforce1;
		double iforce2;
		double irange1;
		double irange2;
		double vclampl1;
		double vclamph1;
		double vclampl2;
		double vclamph2;
		int samplesize;
    void init(){
				  add_param( "Measure_pinlist1",  "PinString", &pinlist1).set_default("VDD_BUCK_1V5_IN,VDD_PMU_CLDO,VDD_PMU_SYSLDO,VDD_PMU_3V3_O,");
				  add_param( "Measure_pinlist5",  "PinString", &pinlist5).set_default("VDD_PMU_RFLDO1,RF_VDD_PLLVCO_1P2,RF_VDD_PLL_1P2,CMU_LDO_TCXO");
				  add_param("SampleSize","int",&samplesize).set_default("12");
    }
    void execute(){
					double hil[30],lowl[30];
					char *Test_Item[30],*Units[30];
					int  Test_number[30];
					Read_Limit(lowl,hil,Test_Item,Test_number,Units);
					uint32_t UBIT[8] = {0,15,38,74,42,3,29,83};
					for(int i=0;i<8;i++)
					{
						TheInst.Util().SetRelayState(UBIT[i],PhxAPI:: E_UTIL_STATE_ON);
						int res = TheInst.Util().GetRelayState(UBIT[i]);
						if(res==0)
						{
							cout<< res << endl;
						}
						else
						{
							cout<< "Relay_ok" << endl;

						}

					}
					TheInst.Wait(4*ms);
					LDO_Module();
					TheInst.Wait(10*ms);

					TheInst.DCVS().Power().Apply();
					TheInst.Digital().Level().Apply();

					TheInst.DCVS().Pins(pinlist1).SetMeasureMode(PhxAPI::E_DC_MODE_MV)
								                 .SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
								                 .SetMeasureMethod(PhxAPI::E_DC_METHOD_STATIC)
								                 .SetMeasureOrder(PhxAPI::E_DC_ORDER_SINGLE)
								                 .SetSampleSize(samplesize)
								                 .SetWaitTime(5 * ms)
                                                 .Measure();
					PinArrayDouble result1 = TheInst.DCVS().Pins(pinlist1).GetMeasureResults();
					TheSoft.Flow().TestLimit(pinlist1,result1);

					TheInst.PPMU().Pins(pinlist5).SetClear();
					TheInst.PPMU().Pins(pinlist5).SetMeasureMode(PhxAPI::E_DC_FI_MV)
								                 .SetMeasureType(PhxAPI::E_MEASURE)
								                 .SetIRange(5*uA)
								                 .SetIForce(0*uA)
								                 .Connect(true)
								                 .SetVClampH(3.3*V)
								                 .SetVClampL(-1*V)
								                 .SetSampleSize(16)
								                 .SetWaitTime(5*ms)
								                 .Measure();
					PinArrayDouble result5 = TheInst.PPMU().Pins(pinlist5).GetMeasureResults();
					TheInst.PPMU().Pins(pinlist5).Connect(false).Apply();
					vector<string> pinname = SplitPinList(pinlist5);
					for(int i=0;i<pinname.size();i++)
					{
					TheSoft.Flow().TestLimit(pinname[i],result5);
					}
					powerpinlist = "VDD_PMU_RFLDO1,RF_VDD_PLLVCO_1P2,RF_VDD_PLL_1P2,CMU_LDO_TCXO";
					TheInst.PPMU().Pins(powerpinlist).SetIForce(0.0);
					TheInst.PPMU().Pins(powerpinlist).Connect(0);
					TheInst.PPMU().Pins(powerpinlist).Apply();
					cout << "" << endl;

    }
};

REGISTER_TESTCLASS("PMU_LDO_LOAD",PMU_LDO_LOAD)




