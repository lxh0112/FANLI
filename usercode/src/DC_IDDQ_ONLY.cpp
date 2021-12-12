/*
 * DC_IDDQ_ONLY.cpp
 *
 *  Created on: 2021年8月26日
 *      Author: YK16
 */
#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>

class DC_IDDQ_ONLY: public TestClass{
public:
    std::string measurepin;
    double vforce;
    double iclamph;
    double iclampl;
    double IRang;
    int SampleSize;

	void init(){
		add_param( "MeasurePin",  "PinString", &measurepin);
		add_param( "Vforce",  "double", &vforce);
		add_param( "IClampH",  "double", &iclamph);
		add_param( "IClampL",  "double", &iclampl);
		add_param("IRang","double",&IRang);
		add_param("SampleSize","int",&SampleSize);
	}
    void execute(){
    	measurepin="VDD_PMU_SYSLDO,VDD_PMU_CLDO";
        TheInst.DCVS().Power().Apply();
        TheInst.Digital().Level().Apply();

      	TheInst.DCVS().Pins("VDD_PMU_SYSLDO").SetMeasureMode(PhxAPI::E_DC_MODE_MI)
										 .SetMeasureMethod(PhxAPI::E_DC_METHOD_TRIGGER)
										 .SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
										 .SetMeasureOrder(PhxAPI::E_DC_ORDER_SINGLE)
										 .SetVForce(1.1*V)
										 .SetIRange(PhxAPI::E_POWER_R2_5MA)
										 .SetILimitH(600*uA)
										 .SetILimitL(5*uA)
										 .SetIClampH(1*mA)
										 .SetIClampL(-1*mA)
										 .SetSampleSize(16)
										 .SetWaitTime(100*us)	//unit:us
										 .Measure();

    	TheInst.Digital().Pattern().Start();
    	TheInst.Wait(10000*us);  //unit:us

    	TheInst.DCVS().Pins("VDD_PMU_CLDO").SetMeasureMode(PhxAPI::E_DC_MODE_MI)
										 .SetMeasureMethod(PhxAPI::E_DC_METHOD_TRIGGER)
										 .SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
										 .SetMeasureOrder(PhxAPI::E_DC_ORDER_SINGLE)
										 .SetVForce(1.1* V)
										 .SetIRange(PhxAPI::E_POWER_R25MA)
										 .SetILimitH(16* mA)
										 .SetILimitL(100* uA)
										 .SetIClampH(20* mA)
										 .SetIClampL(-10* mA)
										 .SetSampleSize(16)
										 .SetWaitTime(100*us)	//unit:us
										.Measure();

    	TheInst.Digital().Pattern().Start();
    	TheInst.Wait(10000*us);  //unit:us


    	vector<PinArrayDouble> iddq_result = TheInst.DCVS().Pins(measurepin).GetTrigResults();
//    	TheSoft.Message().InfoMessage("num: %d",iddq_result.size());
    	TheInst.DCVS().ClearAllSetPara();

    	int cap_size = iddq_result.size();
    	double IDDQ_SYSLDO_result;
        double IDDQ_CLDO_result;
    	PinArrayDouble IDDQ_SYSLDO;
    	PinArrayDouble IDDQ_CLDO;
    	for(int i =0; i <iddq_result.size(); i++)
		{
			PinTool::ShowPinArrayData(iddq_result[i]);
			double datatemp1;
			double datatemp2;
			//TheSoft.Flow().TestLimit(iddq_result[i]);
			//TheSoft.Datalog().DatalogMultiParametricTest(iddq_result[i],"DC_IDDQ");
			datatemp1=iddq_result[i].GetData("VDD_PMU_SYSLDO",0);
		    datatemp2=iddq_result[i].GetData("VDD_PMU_CLDO",0);
		    IDDQ_SYSLDO_result =datatemp1;
		    IDDQ_CLDO_result=datatemp2;
		}
    	if(cap_size!=0)
    	{
    		IDDQ_SYSLDO_result=IDDQ_SYSLDO_result/cap_size;
    		IDDQ_CLDO_result=IDDQ_CLDO_result/cap_size;

    		cout<<IDDQ_SYSLDO_result<<endl;
    		cout<<IDDQ_CLDO_result<<endl;

    		IDDQ_SYSLDO.AddPinData("VDD_PMU_SYSLDO",IDDQ_SYSLDO_result);

    		IDDQ_CLDO.AddPinData("VDD_PMU_CLDO",IDDQ_CLDO_result);

    		TheSoft.Flow().TestLimit("VDD_PMU_SYSLDO",IDDQ_SYSLDO);
    		TheSoft.Flow().TestLimit("VDD_PMU_CLDO",IDDQ_CLDO);

    	}
    }

};
REGISTER_TESTCLASS("DC_IDDQ_ONLY",DC_IDDQ_ONLY)



