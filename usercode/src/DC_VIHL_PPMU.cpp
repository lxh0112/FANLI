/*
 * Basic_01_Functional.cpp
 *
 *  Created on: 2021年7月14日    --based on 1.0.2.4
 */



#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include <iomanip>

class DC_VIHL_PPMU: public TestClass {
public:
	std::string strPinList;
	double VForce;
	double hIRang;
	double lIRang;
	double hclamph;
	double hclampl;
	double lclamph;
	double lclampl;
	int SampleSize;

	void init() {
		add_param( "strPinList",  "PinString", &strPinList);
		add_param("VForce","double",&VForce);
		add_param("hIRang","double",&hIRang);
		add_param("lIRang","double",&lIRang);
		add_param("hclamph","double",&hclamph);
		add_param("hclampl","double",&hclampl);
		add_param("lclamph","double",&lclamph);
		add_param("lclampl","double",&lclampl);
		add_param("SampleSize","int",&SampleSize);
	}

	void execute() {

//********************************SET UP UBIT**************************************************************//
		//strPinList ="DC_IIHL_LVCMOS_1V8_group";
//********************************ubit set END************************************************************//
//		TheInst.Digital().Timing("").StopFreeRunningClock("CLK_IN");
//		TheInst.Digital().Timing("").Apply();
//		TheInst.Digital().Timing().Apply();
		TheInst.DCVI().Power().Apply();

		auto pattname= TheSoft.Flow().Pattern().GetCurrentPatternName();

		if(pattname.empty() == false){
			TheInst.Digital().Level().Apply();
			TheInst.Digital().Timing().Apply();
			TheInst.Digital().PatEng().SetupMCFData();
			TheInst.Digital().PatEng().SetFailMode(PhxAPI::E_SET_HIL_MODE);
			//TheInst.Digital().Pattern().Run(); //执行pattern，并判定bin 信息
			TheInst.Digital().Pattern().Start();
			map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
			for(auto it = result.begin(); it != result.end(); it++)
			{
				cout<<"passfail :"<< it->second<<endl;
			}
		}
////*****************************************DC IIH***********************************************************

		//zxc
//    	double Voltage_Value = 2; //v
//    	double v_ma = 5e-6;//50e-3;
//    	//double v_ma=500;
//		 TheInst.PPMU().Pins(SigName)
//				.SetClear()
//				.SetMeasureMode(E_DC_FV_MI)
//				.SetMeasureType(E_MEASURE)
//				.SetVForce(Voltage_Value)
//				.SetIRange(v_ma )
////				.SetIRange(4e-3)
//				.SetIClampH(v_ma )
//				.SetIClampL(-v_ma)
//				.SetSampleSize(10)
//				.Connect(1)
//				.SetWaitTime(5 * ms);
//
//		 TheInst.PPMU().Pins(SigName).Measure();
//		 PinArrayDouble dataarr = TheInst.PPMU().Pins(SigName).GetMeasureResults();
		//end

//		string strPinList_user="FB_SW11";
	    TheInst.PPMU().Pins(strPinList).SetClear();
	    TheInst.PPMU().Pins(strPinList).SetMeasureType(PhxAPI::E_MEASURE)
										.SetIClampH(hclamph)
										.SetIClampL(hclampl)
										.SetIRange(hIRang)
//										.SetIClampH(5.0 *uA)
//										.SetIClampL(-5.0 *uA)
//										.SetIRange(50 *uA)
										.SetVForce(VForce )
										.SetMeasureMode(PhxAPI::E_DC_FV_MI)
										.Connect(true)
										.SetSampleSize(5)
										.SetWaitTime(1*ms)
										.Measure();
		 PinArrayDouble Result1 = TheInst.PPMU().Pins(strPinList).GetMeasureResults();
		 TheInst.PPMU().Pins(strPinList).Connect(false).Apply();
			/* step4: get result */
		 Result1.ShowPinArrayData();
		// TheSoft.Flow().TestLimit(strPinList,Result1);
		 auto vec_strPinList = PinTool::SplitPinList(strPinList);
			if(vec_strPinList.size()>0){
				TheSoft.Flow().TestLimit(vec_strPinList.at(0),Result1);
				//TheSoft.Flow().TestLimit(vec_strPinList.at(0),Result2);
			}
//**********************************************************************************************************
//		//*****************************************DC IIH***********************************************************
//			    TheInst.PPMU().Pins(strPinList).SetClear();
//			    TheInst.PPMU().Pins(strPinList).SetMeasureType(PhxAPI::E_MEASURE)
////												.SetIClampH(hclamph)
////												.SetIClampL(hclampl)
////												.SetIRange(hIRang)
//												.SetIClampH(5.0 *uA)
//												.SetIClampL(-5.0 *uA)
//												.SetIRange(5 *uA)
//												.SetVForce(VForce )
//												.SetMeasureMode(PhxAPI::E_DC_FV_MI)
//												.Connect(true)
//												.SetSampleSize(10)
//												.SetWaitTime(5 * ms)
//												.Measure();
//				 PinArrayDouble Result1 = TheInst.PPMU().Pins(strPinList).GetMeasureResults();
//				 TheInst.PPMU().Pins(strPinList).Connect(false).Apply();
//					/* step4: get result */
//				 Result1.ShowPinArrayData();
//				// TheSoft.Flow().TestLimit(strPinList,Result1);
//				 auto vec_strPinList = PinTool::SplitPinList(strPinList);
//					if(vec_strPinList.size()>0){
//						TheSoft.Flow().TestLimit(vec_strPinList.at(0),Result1);
//						//TheSoft.Flow().TestLimit(vec_strPinList.at(0),Result2);
//					}
//***************************************DC IIL**********************************************************
		TheInst.PPMU().Pins(strPinList).SetClear();
		TheInst.PPMU().Pins(strPinList).SetMeasureType(PhxAPI::E_MEASURE)
										.SetIClampH(lclamph)
										.SetIClampL(lclampl)
										.SetIRange(lIRang)
										.SetVForce(0* V )
										.SetMeasureMode(PhxAPI::E_DC_FV_MI)
										.Connect(true)
										.SetSampleSize(5)
										.SetWaitTime(1*ms)
										.Measure();
		 PinArrayDouble Result2 = TheInst.PPMU().Pins(strPinList).GetMeasureResults();
		 TheInst.PPMU().Pins(strPinList).Connect(false).Apply();
//***********************************************************************************************************
//		 TheInst.PPMU().Pins(strPinList).SetClear();
//		 		TheInst.PPMU().Pins(strPinList).SetMeasureType(PhxAPI::E_MEASURE)
////		 										.SetIClampH(lclamph)
////		 										.SetIClampL(lclampl)
////		 										.SetIRange(lIRang)
//		                                        .SetIClampH(5.0 *uA)
//												.SetIClampL(-5.0 *uA)
//												.SetIRange(5 *uA)
//		 										.SetVForce(0* V )
//		 										.SetMeasureMode(PhxAPI::E_DC_FV_MI)
//		 										.Connect(true)
//		 										.SetSampleSize(10)
//		 										.SetWaitTime(5 * ms)
//		 										.Measure();
//		 		 PinArrayDouble Result2 = TheInst.PPMU().Pins(strPinList).GetMeasureResults();
//		 		 TheInst.PPMU().Pins(strPinList).Connect(false).Apply();
/****************************************** step4: get result *********************************************/

		Result2.ShowPinArrayData();
		//TheSoft.Flow().TestLimit(strPinList,Result1);
		//TheSoft.Flow().TestLimit(strPinList,Result2);
		//auto vec_strPinList = PinTool::SplitPinList(strPinList);
		if(vec_strPinList.size()>0){
			//TheSoft.Flow().TestLimit(vec_strPinList.at(0),Result1);
		    TheSoft.Flow().TestLimit(vec_strPinList.at(0),Result2);
		}
	}
};



REGISTER_TESTCLASS("DC_VIHL_PPMU", DC_VIHL_PPMU)
