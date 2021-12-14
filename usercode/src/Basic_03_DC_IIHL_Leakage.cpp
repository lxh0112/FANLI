//
// Created by f.he on 2021/6/18.
//

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>

using namespace PinTool;

class Basic_03_DC_IIHL_Leakage: public TestClass{
public:
	   std::string pinlist;
	    double vforce_h;
	    double vforce_l;
	    double range_l;
	    double range_h;
		double IIH_iClampl;
		double IIH_iClamph;
		double IIL_iClampl;
		double IIL_iClamph;
		double waittime;
	    int samplesize;

    void init(){
					add_param( "Measure_pinlist",  "PinString", &pinlist).set_default("");
					add_param("IIH_VForce","double",&vforce_h).set_default("");
					add_param("RangeH","double",&range_h).set_default("");
					add_param("IIH_IClampL","double",&IIH_iClampl).set_default("");
					add_param("IIH_IClampH","double",&IIH_iClamph).set_default("");
					add_param("IIL_VForce","double",&vforce_l).set_default("");
					add_param("RangeL","double",&range_l).set_default("");
					add_param("IIL_IClampL","double",&IIL_iClampl).set_default("");
					add_param("IIL_IClampH","double",&IIL_iClamph).set_default("");
					add_param("Waittime","double",&waittime).set_default("");
					add_param("SampleSize","int",&samplesize).set_default("12");
               }

    void execute(){
					TheInst.DCVI().Power().Apply();
					TheInst.Digital().Level().Apply();
					TheInst.Digital().Timing().Apply();
					TheInst.Digital().Pattern().Run();
//					printf("**************111111");
					map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
//					for(auto it = result.begin(); it != result.end(); it++)
//					{
//						cout<<"pass/fail :"<< it->second<<endl;
//					}

					TheInst.PPMU().Pins(pinlist).SetClear();
					TheInst.PPMU().Pins(pinlist).SetMeasureMode(PhxAPI::E_DC_FV_MI)
		                                        .SetMeasureOrder(PhxAPI::E_MEASURE_ODER_GROUP)
												.SetVForce(vforce_h)
												.SetIRange(range_h)
												.SetIClampL(IIH_iClampl)
												.SetIClampH(IIH_iClamph)
												.SetMeasureType(PhxAPI::E_MEASURE)
												.SetSampleSize(samplesize)
												.SetWaitTime(waittime)
												.Connect(true)
												.Measure();
					PinArrayDouble Result1 = TheInst.PPMU().Pins(pinlist).GetMeasureResults();
					TheInst.PPMU().Pins(pinlist).Connect(false).Apply();
					cout<<"=========Force:"<<vforce_h<<endl;
				    TheSoft.Flow().TestLimit(pinlist,Result1);

					TheInst.PPMU().Pins(pinlist).SetClear();
					TheInst.PPMU().Pins(pinlist).SetMeasureMode(PhxAPI::E_DC_FV_MI)
											    .SetMeasureOrder(PhxAPI::E_MEASURE_ODER_GROUP)
												.SetVForce(vforce_l)
												.SetIRange(range_l)
												.SetIClampL(IIL_iClampl)
												.SetIClampH(IIL_iClamph)
												.SetMeasureType(PhxAPI::E_MEASURE)
												.SetSampleSize(samplesize)
												.SetWaitTime(waittime)
												.Connect(true)
												.Measure();
					PinArrayDouble Result2 = TheInst.PPMU().Pins(pinlist).GetMeasureResults();
					TheInst.PPMU().Pins(pinlist).Connect(false).Apply();
					cout<<"=========Force:"<<vforce_l<<endl;
					TheSoft.Flow().TestLimit(pinlist,Result2);
					}
};
REGISTER_TESTCLASS("Basic_03_DC_IIHL_Leakage",Basic_03_DC_IIHL_Leakage)

