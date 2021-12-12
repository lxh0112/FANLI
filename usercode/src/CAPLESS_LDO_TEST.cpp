/*
 * CAPLESS_LDO_TEST.cpp
 *
 *  Created on: 2021年8月18日
 *      Author: YK16
 */
#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>

class CAPLESS_LDO_TEST: public TestClass{
public:
    std::string powerpinlist;
    double vforce;
	double iClampl;
	double iClamph;
	double waittime;
    int sampleSize;

    void init(){
//        add_param( "powerpinlist",  "PinString", &powerpinlist)
//                .set_default("DCVI,DCVI_NOFB")
//                .set_options("DCVI,DCVI_NOFB");
//        add_param("VForce","double",&vforce).set_default("0.1");
//        add_param("IClampL","double",&iClampl).set_default("-0.025");
//        add_param("IClampH","double",&iClamph).set_default("0.025");
//        add_param("Waittime","double",&waittime).set_default("5000");
//        add_param("SampleSize","int",&sampleSize).set_default("16");;
    }

    void execute(){


#if 1

    	TheInst.DCVS().Power().Apply();
    	TheInst.Digital().Level().Apply();
    	powerpinlist = "PMU_RBIAS";
    	TheInst.DCVS().Pins(powerpinlist).SetMeasureMode(PhxAPI::E_DC_MODE_MV)//FNMV
								  .SetMeasureMethod(PhxAPI::E_DC_METHOD_STATIC)
								  .SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
//								  .SetMeasureOrder(PhxAPI::E_MEASURE_ODER_SINGLE)
								  .SetIRange(PhxAPI::E_POWER_R25UA)
//   							      .SetVForce(vforce)
								  .SetVLimitH(1.54* V)
								  .SetVLimitL(1.14* V)
								  .SetIClampL(-25* uA)
								  .SetIClampH(25* uA)
								  .SetSampleSize(16)
								  .SetWaitTime(10 * ms);


		TheInst.DCVS().Pins(powerpinlist).Measure();

PinArrayDouble result1 = TheInst.DCVS().Pins(powerpinlist).GetMeasureResults();
result1.ShowPinArrayData();
//    	PinTool::ShowPinArrayData(result2);
TheSoft.Flow().TestLimit(powerpinlist,result1);

#endif
    }
};
REGISTER_TESTCLASS("CAPLESS_LDO_TEST",CAPLESS_LDO_TEST)




