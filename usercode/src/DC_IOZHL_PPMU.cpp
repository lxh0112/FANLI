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



class DC_IOZHL_PPMU: public TestClass {
public:
	std::string strPinList;
	double VForce;
	double IRang;
	int SampleSize;

	void init() {
		add_param( "strPinList",  "PinString", &strPinList);
		add_param("VForce","double",&VForce);
		add_param("IRang","double",&IRang);
		add_param("SampleSize","int",&SampleSize);
	}


	void execute() {

//********************************SET UP UBIT**************************************************************//
	//strPinList ="DC_IOZHL_DDR4_1V2_group";
//********************************ubit set END************************************************************//
//	TheInst.Digital().Timing("").StopFreeRunningClock("CLK_IN");
//	TheInst.Digital().Timing("").Apply();
//	TheInst.Digital().Timing().Apply();
	TheInst.DCVI().Power().Apply();
	TheInst.Digital().Level().Apply();
	TheInst.Digital().Timing().Apply();
	TheInst.Digital().PatEng().SetupMCFData();
	TheInst.Digital().PatEng().SetFailMode(PhxAPI::E_SET_HIL_MODE);
	//TheInst.Digital().Pattern().Run(); //执行pattern，并判定bin 信息
	TheInst.Digital().Pattern().Run();
	map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
	for(auto it :result)
	{
		cout<<"passfail :"<< it.second<<endl;
	}

//*****************************************DC IOZH***********************************************************
		  TheInst.PPMU().Pins(strPinList).SetClear();
		  TheInst.PPMU().Pins(strPinList).SetMeasureType(PhxAPI::E_MEASURE)
												.SetIClampH(20.0 *uA)
												.SetIClampL(-20.0 *uA)
												.SetIRange(IRang)
												.SetVForce(VForce )
												.SetMeasureMode(PhxAPI::E_DC_FV_MI)
												.Connect(true)
												.SetSampleSize(5)
												.SetWaitTime(1*ms)
												.Measure();
			PinArrayDouble Result1 = TheInst.PPMU().Pins(strPinList).GetMeasureResults();
			TheInst.PPMU().Pins(strPinList).Connect(false).Apply();

//***************************************DC IOZL**********************************************************
			TheInst.PPMU().Pins(strPinList).SetClear();
			TheInst.PPMU().Pins(strPinList).SetMeasureType(PhxAPI::E_MEASURE)
											.SetIClampH(20.0 *uA)
											.SetIClampL(-20.0 *uA)
											.SetIRange(IRang)
											.SetVForce(0* V )
											.SetMeasureMode(PhxAPI::E_DC_FV_MI)
											.Connect(true)
											.SetSampleSize(5)
											.SetWaitTime(1 * ms)
											.Measure();
			 PinArrayDouble Result2 = TheInst.PPMU().Pins(strPinList).GetMeasureResults();
			 TheInst.PPMU().Pins(strPinList).Connect(false).Apply();


/****************************************** step4: get result *********************************************/
			Result1.ShowPinArrayData();
			//TheSoft.Flow().TestLimit(strPinList,Result1);
			Result2.ShowPinArrayData();
			//TheSoft.Flow().TestLimit(strPinList,Result2);
			auto vec_strPinList = PinTool::SplitPinList(strPinList);
			if(vec_strPinList.size()>0){
				TheSoft.Flow().TestLimit(vec_strPinList.at(0),Result1);
				TheSoft.Flow().TestLimit(vec_strPinList.at(0),Result2);
			}
	}
};


REGISTER_TESTCLASS("DC_IOZHL_PPMU", DC_IOZHL_PPMU)
