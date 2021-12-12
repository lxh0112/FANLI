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



class DC_IOZHL_3V3_VDDH: public TestClass {
public:
	   std::string pinlist;
	    double vforce_h;
	    double vforce_l;
	    double range_l;
	    double range_h;
		double IOZH_iClampl;
		double IOZH_iClamph;
		double IOZL_iClampl;
		double IOZL_iClamph;

		int samplesize;

	    void init(){
	        add_param( "Measure_pinlist",  "PinString", &pinlist).set_default("");
	        add_param("IOZH_VForce","double",&vforce_h).set_default("");
	        add_param("RangeH","double",&range_h).set_default("");
	        add_param("IOZH_IClampL","double",&IOZH_iClampl).set_default("");
	        add_param("IOZH_IClampH","double",&IOZH_iClamph).set_default("");
	        add_param("IOZL_VForce","double",&vforce_l).set_default("0");
	        add_param("RangeL","double",&range_l).set_default("");
	        add_param("IOZL_IClampL","double",&IOZL_iClampl).set_default("");
	        add_param("IOZL_IClampH","double",&IOZL_iClamph).set_default("");
	        add_param("SampleSize","int",&samplesize).set_default("16");
	    }



	void execute() {

//********************************SET UP UBIT**************************************************************//
//	    strPinList ="gDC_IOZHL_3V3_VDDH";
		//********************************ubit set END************************************************************//
//6221:	    TheInst.Digital().Timing("").StopFreeRunningClock("CLK_IN");
//	    TheInst.Digital().Timing("").Apply();
	    TheInst.DCVS().Power().Apply();
		TheInst.Digital().Level().Apply();
		TheInst.Digital().Timing().Apply();
		TheInst.Digital().PatEng().SetupMCFData();
		TheInst.Digital().PatEng().SetFailMode(PhxAPI::E_SET_HIL_MODE);
		//TheInst.Digital().Pattern().Run(); //执行pattern，并判定bin 信息
		TheInst.Digital().Pattern().Start();
		map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
		for(auto it :result)
		{
			cout<<"passfail :"<< it.second<<endl;
		}

//*****************************************DC IOZH***********************************************************
		  TheInst.PPMU().Pins(pinlist).SetClear();
		  TheInst.PPMU().Pins(pinlist).SetMeasureType(PhxAPI::E_MEASURE)
		                              .SetVForce(vforce_h )//3.63*V
									  .SetIRange(range_h)//5 *uA
									  .SetIClampL(IOZH_iClampl)//-25 *uA
									  .SetIClampH(IOZH_iClamph)//5*uA
									  .SetMeasureMode(PhxAPI::E_DC_FV_MI)
									  .Connect(true)
									  .SetSampleSize(samplesize)//32//6221的
									  .SetWaitTime(100* us)
									  .Measure();
			PinArrayDouble Result1 = TheInst.PPMU().Pins(pinlist).GetMeasureResults();
			TheInst.PPMU().Pins(pinlist).Connect(false).Apply();

//***************************************DC IOZL**********************************************************
			TheInst.PPMU().Pins(pinlist).SetClear();
			TheInst.PPMU().Pins(pinlist).SetMeasureMode(PhxAPI::E_DC_FV_MI)
		                                .SetVForce(vforce_l)//0*V
										.SetIRange(range_l)//5 *uA
										.SetIClampL(IOZL_iClampl)//-5*uA
										.SetIClampH(IOZL_iClamph)//5 *uA
					                    .SetMeasureType(PhxAPI::E_MEASURE)
										.Connect(true)
										.SetSampleSize(samplesize)//32//6221的
										.SetWaitTime(100 * us)
										.Measure();
			 PinArrayDouble Result2 = TheInst.PPMU().Pins(pinlist).GetMeasureResults();
			 TheInst.PPMU().Pins(pinlist).Connect(false).Apply();


/****************************************** step4: get all result *********************************************/
			Result1.ShowPinArrayData();
			TheSoft.Flow().TestLimit(pinlist,Result1);
			Result2.ShowPinArrayData();
			TheSoft.Flow().TestLimit(pinlist,Result2);



	}
};


REGISTER_TESTCLASS("DC_IOZHL_3V3_VDDH", DC_IOZHL_3V3_VDDH)
