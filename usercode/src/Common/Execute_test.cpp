#include "Globle_Var.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include "Execute_Test.h"
#include "UserDef.h"

using namespace PhxAPI;

struct Supply_PinList{
	string dcname;
	DcMeasureMode mode;
	float force;
    double LLimit;
    double HLimit;
    PowerRange range;
	double clampl;
	double clamph;
//  int clampdelay;
	DcReadMode MType;
	double Delay;
	DcMeasureMethod method;
	DcMeasureOrder order;
};


PinArrayDouble TX_2G_IDD_TEST(){
	double hil[30], lowl[30];
//	char *Test_Item[30], *Units[30];
	vector<string> Test_Item;
	vector<string> Units;
	int Test_number[30];
	int Soft_Bin[30];
	int Hard_Bin[30];
	Read_Limit(lowl,hil,Test_Item,Test_number,Units,Soft_Bin,Hard_Bin);

//	TheSoft.Flow().Power().SetPower("3V3_VDDN_FUNC");
//	TheInst.DCVI().Power().Apply();
//	TheSoft.Flow().Level().SetLevel("3V3_VIHLR_VOHLR_IOHLR");
//	TheInst.Digital().Level().Apply();

	TheInst.DCVI().Pins("RF_VDD_TX2G_3P3_0").SetMeasureMode(E_DC_MODE_MI)
										  .SetMeasureMethod(E_DC_METHOD_STATIC)
										  .SetReadMode(E_DC_MODE_GONOGO)
										  .SetMeasureOrder(E_DC_ORDER_SINGLE)
										  .SetIRange(E_POWER_R500MA)
										  .SetVForce(3.3* V)
//										  .SetILimitL(-5* uA)
//										  .SetILimitH(20* mA)
										  .SetIClampL(-20* mA)
										  .SetIClampH(200* mA)
		//								  .SetSampleSize(sampleSize);
										  .SetWaitTime(10* ms)
										  .Measure();
	PinArrayDouble Result= TheInst.PPMU().Pins("RF_VDD_TX2G_3P3_0").GetMeasureResults();
	TheInst.PPMU().Pins("RF_VDD_TX2G_3P3_0").Connect(false).Apply();
	Result.ShowPinArrayData();
	TheSoft.Flow().TestLimit("RF_VDD_TX2G_3P3_0",Result);
	return Result;
}

void WL_TX_2G_M_C0_IDD(int number){
	double hil[30], lowl[30];
//	char *Test_Item[30], *Units[30];
	vector<string> Test_Item;
	vector<string> Units;
	int Test_number[30];
	int Soft_Bin[30];
	int Hard_Bin[30];
	Read_Limit(lowl,hil,Test_Item,Test_number,Units,Soft_Bin,Hard_Bin);



	Supply_PinList pin[3] = {
				{"VDD_PMU_1V5_IN",E_DC_MODE_MI,1.4*V,93*mA,113*mA,E_POWER_R500MA,-20*mA,200*mA,E_DC_MODE_MEASURE,100*us,E_DC_METHOD_STATIC,E_DC_ORDER_SINGLE},
				{"RF_VDD_TX2G_3P3_0",E_DC_MODE_MI,3.3*V,200*mA,350*mA,E_POWER_R500MA,-20*mA,500*mA,E_DC_MODE_MEASURE,100*us,E_DC_METHOD_STATIC,E_DC_ORDER_SINGLE},
				{"RF_VDD_TX2G_3P3_1",E_DC_MODE_MI,3.3*V,-5*uA,10*mA,E_POWER_R250UA,-200*uA,200*uA,E_DC_MODE_MEASURE,1*ms,E_DC_METHOD_STATIC,E_DC_ORDER_SINGLE},
			};
	string pinGroup = "VDD_PMU_1V5_IN,,RF_VDD_TX2G_3P3_0,RF_VDD_TX2G_3P3_1";
	/********************遍历********************/
	for( int i=0; i<3; i++ ){
		TheInst.DCVI().Pins(pin[i].dcname).SetMeasureMode(pin[i].mode)
//										  .SetVForce(pin[i].force)
//	    								  .SetILimitL(pin[i].LLimit)
//	    								  .SetILimitH(pin[i].HLimit)
										  .SetIRange(pin[i].range)
										  .SetIClampL(pin[i].clampl)
										  .SetIClampH(pin[i].clamph)
										  .SetReadMode(pin[i].MType)
										  .SetWaitTime(pin[i].Delay)
	    								  .SetMeasureMethod(pin[i].method)
										  .SetMeasureOrder(pin[i].order)
										  .Measure();
	};
	PinArrayDouble Result= TheInst.DCVI().Pins(pinGroup).GetMeasureResults();

	Result.ShowPinArrayData();
	TheSoft.Flow().TestLimit("VDD_PMU_1V5_IN",Result,lowl[3],hil[3],Hard_Bin[3],Soft_Bin[3],Units[3],"WL_TX_2G_M_C0_IDD",Test_number[3]+number);
	TheSoft.Flow().TestLimit("RF_VDD_TX2G_3P3_0",Result,lowl[6],hil[6],Hard_Bin[6],Soft_Bin[6],Units[6],"WL_TX_2G_M_C0_IDD",Test_number[6]+number);
	TheSoft.Flow().TestLimit("RF_VDD_TX2G_3P3_1",Result,lowl[7],hil[7],Hard_Bin[7],Soft_Bin[7],Units[7],"WL_TX_2G_M_C0_IDD",Test_number[7]+number);

}

void WL_TX_2G_M_C1_IDD(int number){
	double hil[30], lowl[30];
	vector<string> Test_Item;
	vector<string> Units;
	int Test_number[30];
	int Soft_Bin[30];
	int Hard_Bin[30];
	Read_Limit(lowl,hil,Test_Item,Test_number,Units,Soft_Bin,Hard_Bin);

	Supply_PinList pin[10] = {
			{"DBB_VDDIO_3V3",E_DC_MODE_MI,3.3*V,-5*uA,10*uA,E_POWER_R2_5MA,-20*uA,2*mA,E_DC_MODE_MEASURE,10*ms,E_DC_METHOD_STATIC,E_DC_ORDER_SINGLE},
			{"DBB_VDDIO_3V3_1V8",E_DC_MODE_MI,3.3*V,60*uA,120*uA,E_POWER_R250UA,-20*uA,200*uA,E_DC_MODE_MEASURE,10*ms,E_DC_METHOD_STATIC,E_DC_ORDER_SINGLE},
			{"VDD_PMU_3V3_IN3",E_DC_MODE_MI,3.3*V,5*mA,9.5*mA,E_POWER_R25MA,-20*mA,25*mA,E_DC_MODE_MEASURE,100*us,E_DC_METHOD_STATIC,E_DC_ORDER_SINGLE},
			{"VDD_PMU_1V5_IN",E_DC_MODE_MI,1.4*V,97*mA,117*mA,E_POWER_R500MA,-20*mA,200*mA,E_DC_MODE_MEASURE,100*us,E_DC_METHOD_STATIC,E_DC_ORDER_SINGLE},
			{"VDD_PMU_3V3_IN1",E_DC_MODE_MI,3.3*V,3*mA,5.5*mA,E_POWER_R25MA,-20*mA,10*mA,E_DC_MODE_MEASURE,1000*us,E_DC_METHOD_STATIC,E_DC_ORDER_SINGLE},
			{"VDD_PMU_3V3_IN2",E_DC_MODE_MI,3.3*V,15*mA,28*mA,E_POWER_R500MA,-20*mA,30*mA,E_DC_MODE_MEASURE,100*us,E_DC_METHOD_STATIC,E_DC_ORDER_SINGLE},
			{"RF_VDD_TX2G_3P3_0",E_DC_MODE_MI,3.3*V,-5*uA,10*uA,E_POWER_R250UA,-200*uA,200*uA,E_DC_MODE_MEASURE,10*ms,E_DC_METHOD_STATIC,E_DC_ORDER_SINGLE},
			{"RF_VDD_TX2G_3P3_1",E_DC_MODE_MI,3.3*V,200*mA,350*mA,E_POWER_R500MA,-20*mA,500*mA,E_DC_MODE_MEASURE,100*us,E_DC_METHOD_STATIC,E_DC_ORDER_SINGLE},
			{"RF_VDD_TX5G_3P3_0",E_DC_MODE_MI,3.3*V,-5*uA,10*uA,E_POWER_R250UA,-200*uA,200*uA,E_DC_MODE_MEASURE,10*ms,E_DC_METHOD_STATIC,E_DC_ORDER_SINGLE},
			{"RF_VDD_TX5G_3P3_1",E_DC_MODE_MI,3.3*V,-5*uA,10*uA,E_POWER_R250UA,-200*uA,200*uA,E_DC_MODE_MEASURE,10*ms,E_DC_METHOD_STATIC,E_DC_ORDER_SINGLE}
		};

	/********************遍历********************/
	for( int i=0; i<10; i++ ){
		TheInst.DCVI().Pins(pin[i].dcname).SetMeasureMode(pin[i].mode)
//										  .SetVForce(pin[i].force)
//	    								  .SetILimitL(pin[i].LLimit)
//	    								  .SetILimitH(pin[i].HLimit)
										  .SetIRange(pin[i].range)
										  .SetIClampL(pin[i].clampl)
										  .SetIClampH(pin[i].clamph)
										  .SetReadMode(pin[i].MType)
										  .SetWaitTime(pin[i].Delay)
	    								  .SetMeasureMethod(pin[i].method)
										  .SetMeasureOrder(pin[i].order)
//										  .Connect(true)
//										  .SetSampleSize(16)
										  .Measure();
		PinArrayDouble Result= TheInst.DCVI().Pins(pin[i].dcname).GetMeasureResults();

		Result.ShowPinArrayData();
		TheSoft.Flow().TestLimit(pin[i].dcname,Result,lowl[i],hil[i],Hard_Bin[i],Soft_Bin[i],Units[i],"WL_TX_2G_M_C1_IDD",Test_number[i]+number);
	};
}

PinArrayDouble Execute_test(string testname){
	PinArrayDouble result;
	string currentPowerName = TheSoft.Flow().Power().GetCurrentPowerBlockName();
	string currentLevelBlock = TheSoft.Flow().Level().GetCurrentLevelName();
	string currentTimingBlockName = TheInst.Digital().Timing("").GetCurrentTimingBlockName();
	string currentPattern = TheSoft.Flow().Pattern().GetCurrentPatternName();

	if(testname == "TX_2G_IDD_TEST"){
		result = TX_2G_IDD_TEST();
	}else if(testname == "WL_TX_2G_M_C0_IDD"){
		WL_TX_2G_M_C0_IDD(20);
	}else if(testname == "WL_TX_2G_M_C1_IDD"){
		WL_TX_2G_M_C1_IDD(20);
	}


	TheSoft.Flow().Power().SetPower(currentPowerName);
	TheSoft.Flow().Level().SetLevel(currentLevelBlock);
	TheSoft.Flow().Timing().SetTiming(currentTimingBlockName);
	TheSoft.Flow().Pattern().SetPattern(currentPattern);


	return result;
}

void Excute_Test(string Pname,string Lname,string Tname,string PTname)
{
    string PowerBlockName = TheSoft.Flow().Power().GetCurrentPowerBlockName();
    string LevelName = TheSoft.Flow().Level().GetCurrentLevelName();
    string TimingBlockName = TheSoft.Flow().Timing().GetCurrentTimingBlockName();
    string PatternName = TheSoft.Flow().Pattern().GetCurrentPatternName();

    TheSoft.Flow().Power().SetPower(Pname);
    TheInst.DCVI().Power().Apply();
	TheSoft.Flow().Level().SetLevel(Lname);
	TheInst.Digital().PatEng().SetupMCFData();
	TheSoft.Flow().Timing().SetTiming(Tname); //5ns,RL
	TheInst.Digital().Timing().Apply();
	TheSoft.Flow().Pattern().SetPattern(PTname);
	TheInst.Digital().Pattern().Start();

	TheSoft.Flow().Power().SetPower(PowerBlockName);
	TheSoft.Flow().Level().SetLevel(LevelName);
	TheSoft.Flow().Timing().SetTiming(TimingBlockName); //5ns,RL
	TheSoft.Flow().Pattern().SetPattern(PatternName);
}
