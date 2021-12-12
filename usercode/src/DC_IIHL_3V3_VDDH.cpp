/*
 * DC_IIHL_3V3_VDDH.cpp
 *
 *  Created on: 2021年8月24日
 *      Author: 荣耀
 */

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>

using namespace PhxAPI;

class DC_IIHL_3V3_VDDH: public TestClass{
public:
	bool HBIN_FLAG[4];

    void init(){

    }

    void execute(){
        TheInst.DCVS().Power().Apply();
        TheInst.Digital().Level().Apply();
        TheInst.Digital().Timing().Apply();
    	TheInst.Digital().Pattern().Start();

    	/**********************创建DC******************/
    	struct PinList{
    		string dcname;
    		PPMUMeasureMode_E mode;
    		float force;
//    		double LLimit;
//    		double HLimit;
    		double range;
    		double clampl;
    		double clamph;
//    		int clampdelay;
    		PPMUMeasureType_E MType;
    		double Delay;
//    		PPMUMethod_E method;
    		PPMUOrder_E order;
    	};
    	PinList pin[2] = {
    	    			{"gDC_IIHL_3V3_VDDH_H",E_DC_FV_MI,3.63,5e-6,-5e-6,5e-6,E_MEASURE,10*ms,E_MEASURE_ODER_GROUP},
//						{"DBB_GPIO4",E_DC_FV_MI,3.63,5e-6,-5e-6,5e-6,E_MEASURE,10*ms,E_MEASURE_ODER_SINGLE},
//						{"DBB_FEM_CTRL0_0",E_DC_FV_MI,3.63,5e-6,-5e-6,5e-6,E_MEASURE,10*ms,E_MEASURE_ODER_SINGLE},
//						{"DBB_FEM_CTRL0_1",E_DC_FV_MI,3.63,5e-6,-5e-6,5e-6,E_MEASURE,10*ms,E_MEASURE_ODER_SINGLE},
//						{"gNORMAL_3V3_1V8_IO_PU",E_DC_FV_MI,3.63,5e-6,-5e-6,5e-6,E_MEASURE,10*ms,E_MEASURE_ODER_GROUP},
//						{"gNORMAL_3V3_IO_PD",E_DC_FV_MI,3.63,5e-6,-5e-6,5e-6,E_MEASURE,10*ms,E_MEASURE_ODER_GROUP},
//						{"gNORMAL_3V3_1V8_IO_PD",E_DC_FV_MI,0,5e-6,-5e-6,5e-6,E_MEASURE,10*ms,E_MEASURE_ODER_GROUP},
//						{"DBB_GPIO4",E_DC_FV_MI,0,5e-6,-5e-6,5e-6,E_MEASURE,10*ms,E_MEASURE_ODER_SINGLE},
//						{"DBB_FEM_CTRL0_0",E_DC_FV_MI,0,5e-6,-5e-6,5e-6,E_MEASURE,10*ms,E_MEASURE_ODER_SINGLE},
//						{"DBB_FEM_CTRL0_1",E_DC_FV_MI,0,5e-6,-5e-6,5e-6,E_MEASURE,10*ms,E_MEASURE_ODER_SINGLE},
//						{"gNORMAL_3V3_1V8_IO_PU",E_DC_FV_MI,0,5e-6,-5e-6,5e-6,E_MEASURE,10*ms,E_MEASURE_ODER_GROUP},
						{"gDC_IIHL_3V3_VDDH_L",E_DC_FV_MI,0,5e-6,-5e-6,5e-6,E_MEASURE,10*ms,E_MEASURE_ODER_GROUP}
				};

    	/********************遍历********************/
    	for( int i=0; i<2; i++ ){
    		TheInst.PPMU().Pins(pin[i].dcname).SetMeasureMode(pin[i].mode)
											  .SetVForce(pin[i].force)
//    										  .SetILimitL(pin[i].LLimit)
//    										  .SetILimitH(pin[i].HLimit)
    										  .SetIRange(pin[i].range)
    										  .SetIClampL(pin[i].clampl)
    										  .SetIClampH(pin[i].clamph)
    										  .SetMeasureType(pin[i].MType)
    										  .SetWaitTime(pin[i].Delay)
//    										  .SetMeasureMethod(pin[i].method)
    										  .SetMeasureOrder(pin[i].order)
											  .Connect(true)
											  .SetSampleSize(16)
    										  .Measure();
    		PinArrayDouble Result= TheInst.PPMU().Pins(pin[i].dcname).GetMeasureResults();
    		TheInst.PPMU().Pins(pin[i].dcname).Connect(false).Apply();
    		Result.ShowPinArrayData();
    		TheSoft.Flow().TestLimit(pin[i].dcname,Result);
    	};

//    	FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
//    		if((HBIN_FLAG[site_id] == 0)&&( TheSoft.Flow().Bin().GetResultSoftBin(site_id)!= 1)){
//    			HBIN_FLAG[site_id] = 1;
//    	    }
//    	FOREACH_ACTIVESITE_END
    }

};

REGISTER_TESTCLASS("DC_IIHL_3V3_VDDH",DC_IIHL_3V3_VDDH)


