//
// Created by f.he on 2021/6/18.
//

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>

using namespace PinTool;

class Basic_03_DC_Leakage: public TestClass{
public:
    std::string leakagepinlist;
    string VForce;
	double LIClamp;
	double HIClamp;
	double waittime;

	int SampleSize;

    void init(){
        add_param( "IOpinlist",  "PinString", &leakagepinlist)
                .set_default("IIHL")
                .set_options("IIHL:IIHL_PU");
        add_param("VForce","VString",&VForce).set_default("0");
        add_param("LIClamp","double",&LIClamp).set_default("-2");
        add_param("HIClamp","double",&HIClamp).set_default("2");
        add_param("waittime","double",&waittime).set_default("0.005");
        add_param("SampleSize","int",&SampleSize).set_default("16");
    }

    void execute(){

		//setting 过程在界面设定
		//power， waitTime ,order 等在界面设置

    	/* step1: apply current power,level,timing,pattern*/
		TheInst.DCVI().Power().Apply();
		TheInst.Digital().Level().Apply();
		TheInst.Digital().Timing().Apply();
		TheInst.Digital().Pattern().Start();
		printf("**************111111");
		map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
		for(auto it = result.begin(); it != result.end(); it++)
		{
			cout<<"passfail :"<< it->second<<endl;
		}

//		// set timingblock
//		string timingblock = TheSoft.Flow().Timing().GetCurrentTimingBlockName();
//		if(timingblock.empty() == false){
//			TheInst.Digital().Timing().Apply();
//		}
//
//		//get patternname
//		string patternname = TheSoft.Flow().Pattern().GetCurrentPatternName();
//		if(patternname.empty() == false){
//			//run pattern
//			TheInst.Digital().Pattern().Start();
//			//Sleep(200);//设置等待时间，等待pattern运行结束，单位us
//		}

		/*step2: splitStr,将force的电压字符，根据“，”分割*/
//		vector<string> force = SplitPinList(VForce);
//
//		PinArrayData Result[force.size()];
		PinArrayDouble Result;
		PinArrayDouble Result1;
		//for(int i =0; i <force.size(); i++){
			/* step3: DC_leakage  FVMI Set ppmu parameter , then measure*/
		leakagepinlist = "IIHL";

		TheInst.PPMU().Pins(leakagepinlist).SetMeasureMode(PhxAPI::E_DC_FV_MI)
									  .SetMeasureType(PhxAPI::E_MEASURE)
									  .SetIRange(5*uA) // enable force .Gate(1)
									  .SetVForce(1.89*V)
									  .SetIClampH(2*uA)
									  .SetIClampL(-2*uA)
									  .SetSampleSize(0.0)
									  .SetWaitTime(5*ms)
									  .Measure();


			printf("**************111111111111111");
			//Sleep(200);//设置等待时间，等待板卡measure setting 完成和芯片输出稳定 ，单位us
			TheInst.PPMU().Pins(leakagepinlist).Measure();//下发测试指令，开始测试
			TheInst.PPMU().Pins(leakagepinlist).SetVForce(0.0);//设置ppum force 电压值为0
			TheInst.PPMU().Pins(leakagepinlist).Connect(0);//设置ppum pin 与DUT pin 断开
			/* step4: get result */
			Result = TheInst.PPMU().Pins(leakagepinlist).GetMeasureResults();



			TheInst.PPMU().Pins(leakagepinlist).SetMeasureMode(PhxAPI::E_DC_FV_MI)
										  .SetMeasureType(PhxAPI::E_MEASURE)
										  .SetIRange(500*uA) // enable force .Gate(1)
										  .SetVForce(0*V)
										  .SetIClampH(2*uA)
										  .SetIClampL(-200*uA)
										  .SetSampleSize(0.0)
										  .SetWaitTime(5*ms)
										  .Measure();

            printf("**************111111111111111");
			//Sleep(200);//设置等待时间，等待板卡measure setting 完成和芯片输出稳定 ，单位us
			TheInst.PPMU().Pins(leakagepinlist).Measure();//下发测试指令，开始测试
			TheInst.PPMU().Pins(leakagepinlist).SetVForce(0.0);//设置ppum force 电压值为0
			TheInst.PPMU().Pins(leakagepinlist).Connect(0);//设置ppum pin 与DUT pin 断开
			/* step4: get result */
			Result1 = TheInst.PPMU().Pins(leakagepinlist).GetMeasureResults();



			printf("**************Force 1.89V");
			PinTool::ShowPinArrayData(Result);
			printf("**************Force 0V");
			PinTool::ShowPinArrayData(Result1);


			/* step5: judgement and output datalog */
//			TheSoft.Flow().TestLimit(Result[i]);
//			TheSoft.Datalog().DatalogMultiParametricTest(Result[i],"DC_Leakage");
		}

    //}

};
REGISTER_TESTCLASS("Basic_03_DC_Leakage",Basic_03_DC_Leakage)

