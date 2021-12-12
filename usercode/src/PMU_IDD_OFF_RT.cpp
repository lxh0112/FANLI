/*
 * PMU_IDD_OFF_RT.cpp
 *
 *  Created on: 2021年8月24日
 *      Author: 荣耀
 */

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>

using namespace PhxAPI;

class PMU_IDD_OFF_RT: public TestClass{
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
    		float force;
    		double Delay;

    	};
    	PinList pin[10] = {
    	    			{"VDD_PMU_3V3_IN1",3.6*V,50*ms},
						{"VDD_PMU_3V3_IN2",3.6*V,1*ms},
						{"VDD_PMU_3V3_IN3",3.6*V,1*ms},
						{"DBB_VDDIO_3V3",3.63*V,100*us},
						{"DBB_VDDIO_3V3_1V8",3.63*V,100*us},
						{"VDD_PMU_1V5_IN",1.6*V,100*us},
						{"RF_VDD_TX2G_3P3_0",3.465*V,100*us},
						{"RF_VDD_TX2G_3P3_1",3.465*V,100*us},
						{"RF_VDD_TX5G_3P3_0",3.465*V,100*us},
						{"RF_VDD_TX5G_3P3_1",3.465*V,100*us},
    	    	};

    	/********************遍历********************/
    	for( int i=0; i<10; i++ ){
    		TheInst.DCVS().Pins(pin[i].dcname).SetMeasureMode(PhxAPI::E_DC_MODE_MI)
    										  .SetMeasureMethod(PhxAPI::E_DC_METHOD_STATIC)
    										  .SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
    										  .SetMeasureOrder(PhxAPI::E_DC_ORDER_SINGLE)
//    										  .SetIRange(PhxAPI::E_POWER_BEST_FIT)
											  .SetIRange(PhxAPI::E_POWER_R250UA)
    										  .SetVForce(pin[i].force)
    										  .SetILimitH(12*uA)
    										  .SetILimitL(-5*uA)
    										  .SetIClampL(-20*uA)
    										  .SetIClampH(20*uA)
    										  .SetSampleSize(16)
    										  .SetWaitTime(pin[i].Delay)
    										  .Measure();

    		PinArrayDouble result = TheInst.DCVS().Pins(pin[i].dcname).GetMeasureResults();
    				result.ShowPinArrayData();
    				TheSoft.Flow().TestLimit(pin[i].dcname,result);

//    	FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
//    		if((HBIN_FLAG[site_id] == 0)&&( TheSoft.Flow().Bin().GetResultSoftBin(site_id)!= 1)){
//    			HBIN_FLAG[site_id] = 1;
//    	    }
//    	FOREACH_ACTIVESITE_END
    }
   }

};
REGISTER_TESTCLASS("PMU_IDD_OFF_RT",PMU_IDD_OFF_RT)


