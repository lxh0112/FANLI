//
// Created by f.he on 2021/6/18.
//

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>

class Basic_02_OS_VSS_PPMU: public TestClass{
public:
    std::string vsspinlist;
    double iforce;
	double vclampl;
	double vclamph;
	double waittime;
	int sampleSize;

    void init(){
        add_param( "VSS_pinlist",  "PinString", &vsspinlist);
        add_param("IForce","double",&iforce).set_default("-0.0002");
        add_param("VClampL","double",&vclampl).set_default("-1");
        add_param("VClampH","double",&vclamph).set_default("0");
        add_param("Waittime","double",&waittime).set_default("5000");
        add_param("SampleSize","int",&sampleSize).set_default("16");
    }

    void execute(){
    	//    	cout << "!!!Hello Basic_02_OS_VSS_PPMU!!!" << endl;
    	//    	TheSoft.Message().InfoMessage("Basic_02_OS_VSS_PPMU");
    	TheInst.DCVI().Power().Apply();
#if 1
//    	vsspinlist="gOS_VSS";
		std::string strPinList = vsspinlist;
		/* step2: Set ppmu parameter
		/*==================OS_PPMU  FIMV==================*/
		TheInst.PPMU().Pins(strPinList).SetClear();
		TheInst.PPMU().Pins(strPinList).SetMeasureMode(PhxAPI::E_DC_FI_MV)
	                                   .SetMeasureType(PhxAPI::E_MEASURE)
//		                               .SetMeasureOrder(PhxAPI::E_MEASURE_ODER_SINGLE)
//		                               .SetFIRange(2)
//		                               .SetMIRange(2)               // measure by group
		                               .Connect(true)               	// connect PPMU
									   .SetIRange(5*mA)                             // enable force .Gate(1)
		                               .SetIForce(-200*uA)
		                               .SetVClampH(2*V)
			                           .SetVClampL(-2*V)
			                           .SetSampleSize(2)
				                       .SetWaitTime(1*ms)
		                               .Measure();
//									   .SetMeasureMethod(PhxAPI::E_METHODE_DYNAMIC)


		//Sleep(200);
//		TheInst.PPMU().Pins(vsspinlist).Measure();	//下发测试指令，开始测试
//		TheInst.PPMU().Pins(vsspinlist).SetIForce(0.0); //设置ppum force 电流值 为0
//		TheInst.PPMU().Pins(vsspinlist).Connect(0);//设置ppum pin 与DUT pin 断开

		/*step3: get result*/
		PinArrayDouble result = TheInst.PPMU().Pins(strPinList).GetMeasureResults();
		TheInst.PPMU().Pins(strPinList).Connect(false).Apply();//设置ppum disconnect
		result.ShowPinArrayData();
		TheSoft.Flow().TestLimit(vsspinlist,result);
//		PinTool::ShowPinArrayData(result);
		/* step4: judgement and output datalog */
//		TheSoft.Flow().TestLimit(Result);
//		TheSoft.Datalog().DatalogMultiParametricTest(Result,"OS_VDD_PPMU");
#endif
    }

};


REGISTER_TESTCLASS("Basic_02_OS_VSS_PPMU",Basic_02_OS_VSS_PPMU)

