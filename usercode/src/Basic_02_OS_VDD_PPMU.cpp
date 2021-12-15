//
// Created by f.he on 2021/6/18.
//

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>

using namespace PhxAPI;

class Basic_02_OS_VDD_PPMU: public TestClass{
public:
    std::string vddpinlist;
    double iforce;
	double vclampl;
	double vclamph;
	double waittime;
	int sampleSize;

    void init(){
        add_param( "VDD_pinlist",  "PinString", &vddpinlist);
        add_param("IForce","double",&iforce).set_default("100*uA");
        add_param("VClampl","double",&vclampl).set_default("-2*V");
        add_param("VClamph","double",&vclamph).set_default("2*V");
        add_param("Waittime","double",&waittime).set_default("10*ms");
        add_param("SampleSize","int",&sampleSize).set_default("2");
    }

    void execute(){
    	//    	cout << "!!!Hello Basic_02_OS_VDD_PPMU!!!" << endl;
    	//    	TheSoft.Message().InfoMessage("Basic_02_OS_VDD_PPMU");

    	TheInst.DCVI().Power().Apply();
#if 1
//    	vddpinlist="gOS_VDD";
    	string strPinList = vddpinlist;
    	TheInst.PPMU().Pins(strPinList).SetClear();
		TheInst.PPMU().Pins(strPinList).SetMeasureMode(PhxAPI::E_DC_FI_MV)
									   .SetMeasureType(PhxAPI::E_MEASURE)
									   .SetIRange(500*uA) // enable force .Gate(1)
									   .SetIForce(100*uA)
									   .Connect(true)
									   .SetVClampH(2*V)
									   .SetVClampL(-2*V)
									   .SetSampleSize(2)
									   .SetWaitTime(10*ms)
									   .Measure();

		/*step3: get result*/
		PinArrayDouble result = TheInst.PPMU().Pins(strPinList).GetMeasureResults();
		TheInst.PPMU().Pins(strPinList).Connect(false).Apply();//设置ppum disconnect
		result.ShowPinArrayData();
		TheSoft.Flow().TestLimit(vddpinlist,result);
		//power off
//		TheInst.PPMU().Pins(vddpinlist).SetMeasureMode(PhxAPI::E_DC_FV_MV)
//									   .SetMeasureType(PhxAPI::E_MEASURE)
//									   .SetIRange(300*uA) // enable force .Gate(1)
//									   .SetVForce(0*V)
//									   .SetIClampH(2*mA)
//									   .SetIClampL(-0.5*mA)
//									   .SetSampleSize(0.0)
//									   .SetWaitTime(5*ms)
//									   .Measure();

		/* step4: judgement and output datalog */
//		TheSoft.Flow().TestLimit(Result);
//		TheSoft.Datalog().DatalogMultiParametricTest(Result,"OS_VDD_PPMU");
#endif


    }

};

REGISTER_TESTCLASS("Basic_02_OS_VDD_PPMU",Basic_02_OS_VDD_PPMU)

