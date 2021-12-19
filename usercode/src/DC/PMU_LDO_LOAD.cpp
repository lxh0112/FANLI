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
#include "UserDef.h"
#include <string>


using namespace PhxAPI;
using namespace PinTool;

class PMU_LDO_LOAD: public TestClass{
public:
	    std::string powerpinlist;
		std::string pinlist1;
		std::string pinlist2;
		double iforce;
		double irange;
		double vclampl;
		double vclamph;
		int samplesize;
		double waittime;
    void init(){
				  add_param( "Measure_pinlist1",  "PinString", &pinlist1).set_default("VDD_BUCK_1V5_IN,VDD_PMU_CLDO,VDD_PMU_SYSLDO,VDD_PMU_3V3_O");
				  add_param( "Measure_pinlist2",  "PinString", &pinlist2).set_default("VDD_PMU_RFLDO1,RF_VDD_PLLVCO_1P2,RF_VDD_PLL_1P2,CMU_LDO_TCXO");
				  add_param("Iforce","double",&iforce).set_default("0");
				  add_param("Irange","double",&irange).set_default("0.000005");
				  add_param("Vclampl","double",&vclampl).set_default("-1");
				  add_param("Vclamph","double",&vclamph).set_default("3.3");
				  add_param("WaitTime","double",&waittime).set_default("0.005");
				  add_param("SampleSize","int",&samplesize).set_default("2");
    }
    void execute(){
			double hil[30],lowl[30];
			vector<string> Test_Item;
			vector<string> Units;
			int Test_number[30];
			int Soft_Bin[30];
			int Hard_Bin[30];
			Read_Limit(lowl, hil, Test_Item, Test_number, Units, Soft_Bin,Hard_Bin);
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

			TheInst.DCVI().Power().Apply();
			TheInst.Digital().Level().Apply();

			TheInst.DCVI().Pins(pinlist1).SetMeasureMode(PhxAPI::E_DC_MODE_MV)
										 .SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
										 .SetMeasureMethod(PhxAPI::E_DC_METHOD_STATIC)
										 .SetMeasureOrder(PhxAPI::E_DC_ORDER_SINGLE)
										 .SetSampleSize(samplesize)
										 .SetWaitTime(waittime)//5ms
										 .Measure();
			PinArrayDouble result1 = TheInst.DCVI().Pins(pinlist1).GetMeasureResults();
			vector<string> pinname1 = SplitPinList(pinlist1);
			for(unsigned int i=0;i<pinname1.size();i++)
			{
				TheSoft.Flow().TestLimit(pinname1[i],result1,lowl[i], hil[i],Hard_Bin[i],Soft_Bin[i], Units[i], Test_Item[i], Test_number[i]);
			}


			TheInst.PPMU().Pins(pinlist2).SetClear();
			TheInst.PPMU().Pins(pinlist2).SetMeasureType(PhxAPI::E_MEASURE)
										 .SetVClampL(vclampl)//-1v
										 .SetVClampH(vclamph)//3.3V
										 .SetIRange(irange)//5ua
										 .SetIForce(iforce)//0ua
										 .SetMeasureMode(PhxAPI::E_DC_FI_MV)
										 .Connect(true)
										 .SetWaitTime(waittime)//5ms
										 .SetSampleSize(samplesize)
										 .Measure();
			PinArrayDouble result2 = TheInst.PPMU().Pins(pinlist2).GetMeasureResults();
			TheInst.PPMU().Pins(pinlist2).Connect(false).Apply();
			vector<string> pinname2 = SplitPinList(pinlist2);
			for(unsigned int i = 0;i<pinname2.size();i++)
			{
				TheSoft.Flow().TestLimit(pinname2[i],result2,lowl[i+4], hil[i+4],Hard_Bin[i+4],Soft_Bin[i+4], Units[i+4], Test_Item[i+4], Test_number[i+4]);
			}
//					powerpinlist = "VDD_PMU_RFLDO1,RF_VDD_PLLVCO_1P2,RF_VDD_PLL_1P2,CMU_LDO_TCXO";
//					TheInst.PPMU().Pins(powerpinlist).SetIForce(0.0);
//					TheInst.PPMU().Pins(powerpinlist).Connect(0);
//					TheInst.PPMU().Pins(powerpinlist).Apply();
//					cout << "" << endl;

    }
};

REGISTER_TESTCLASS("PMU_LDO_LOAD",PMU_LDO_LOAD)




