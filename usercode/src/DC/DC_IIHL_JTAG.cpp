/*
 * DC_IIHL_JTAG.cpp
 *
 *  Created on: 2021年8月16日
 *      Author: YK16
 */
#include "TestClass.h"
#include <d2s.h>
#include <iostream>
#include <UserAPI.h>
#include "d2sProtocolSSI.h"
#include "Globle_Var.h"
#include "UserDef.h"

using namespace PhxAPI;
using namespace PinTool;

class DC_IIHL_JTAG: public TestClass{
public:
		std::string pinlist;
		double vforce_h;
		double vforce_l;
		double range;
		double iClampl;
		double iClamph;
		int samplesize;
		double waittime;

    void init(){
					add_param( "Measure_pinlist",  "PinString", &pinlist).set_default("gDC_IIHL_JTAG");
					add_param("IIH_VForce","double",&vforce_h).set_default("3.63");
					add_param("Range","double",&range).set_default("0.000005");
					add_param("IClampL","double",&iClampl).set_default("-0.000005");
					add_param("IClampH","double",&iClamph).set_default("0.000005");
					add_param("IIL_VForce","double",&vforce_l).set_default("0");
					add_param("Waittime","double",&waittime).set_default("0.001");
					add_param("SampleSize","int",&samplesize).set_default("2");

              }
	void execute(){

		double hil[30], lowl[30];
		vector<string> Test_Item;
		vector<string> Units;
		int Test_number[30],Soft_Bin[30],Hard_Bin[30];
//		Read_Limit(lowl, hil, Test_Item, Test_number, Units, Soft_Bin,Hard_Bin);

		TheInst.DCVI().Power().Apply();
		TheInst.Digital().Level().Apply();

		d2s::d2s_LABEL_BEGIN("ssi",d2s_WorkMode);
		d2sProtocolSSI d2s_test;
		d2s_test.SSI_write(0x200,0x2000,false);
		d2s_test.SSI_write(0x202,0x0,false);
		d2s_test.SSI_write(0x130,0x4);
		d2s_test.SSI_write(0x12c,0x0);

		d2s_test.SSI_write(0x200,0x2001,false);
		d2s_test.SSI_write(0x202,0x40,false);
		d2s_test.SSI_write(0x4,0x0);
		d2s::d2s_LABEL_END();


		TheInst.DCVI().Power().Apply();
		TheInst.Digital().Level().Apply();
//				printf("**************111111");
		map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
		for(auto it = result.begin(); it != result.end(); it++)
		{
			cout<<"passfail :"<< it->second<<endl;
		}

		   TheInst.PPMU().Pins(pinlist).SetClear();
		   TheInst.PPMU().Pins(pinlist).SetMeasureMode(PhxAPI::E_DC_FV_MI)
									   .SetMeasureOrder(E_MEASURE_ODER_GROUP)
									   .SetVForce(vforce_h)
									   .SetIRange(range)
									   .SetIClampL(iClampl)
									   .SetIClampH(iClamph)
									   .SetMeasureType(E_MEASURE)
									   .SetSampleSize(samplesize)
									   .SetWaitTime(waittime)
									   .Connect(true)
									   .Measure();
			PinArrayDouble Result1 = TheInst.PPMU().Pins(pinlist).GetMeasureResults();
			TheInst.PPMU().Pins(pinlist).Connect(false).Apply();
			TheSoft.Flow().TestLimit(pinlist,Result1,lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], Units[0], Test_Item[0], Test_number[0]);

		   TheInst.PPMU().Pins(pinlist).SetClear();
		   TheInst.PPMU().Pins(pinlist).SetMeasureMode(PhxAPI::E_DC_FV_MI)
									   .SetVForce(vforce_l)
									   .SetIRange(range)
									   .SetIClampL(iClampl)
									   .SetIClampH(iClamph)
									   .SetMeasureOrder(E_MEASURE_ODER_GROUP)
									   .SetMeasureType(PhxAPI::E_MEASURE)
									   .SetSampleSize(samplesize)
									   .SetWaitTime(waittime)
									   .Connect(true)
									   .Measure();
			PinArrayDouble Result2 = TheInst.PPMU().Pins(pinlist).GetMeasureResults();
			TheInst.PPMU().Pins(pinlist).Connect(false).Apply();
			TheSoft.Flow().TestLimit(pinlist,Result2,lowl[1], hil[1],Hard_Bin[1],Soft_Bin[1], Units[1], Test_Item[1], Test_number[1]);


	}
};
REGISTER_TESTCLASS("DC_IIHL_JTAG",DC_IIHL_JTAG)






