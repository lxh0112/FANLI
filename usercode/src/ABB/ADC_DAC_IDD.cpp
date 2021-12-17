/*
 * ADC_DAC_IDD.cpp
 *
 *  Created on: Nov 24, 2021
 *      Author: Administrator
 */
#include<windows.h>
#include<helpers.h>
#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include "Globle_Var.h"
#include "CCS08F.h"
#include "Excel.h"
#include "RegDef.h"
#include "d2sProtocolSSI.h"
#include "UserDef.h"


using namespace PhxAPI;

class ADC_DAC_IDD: public TestClass{
public:

	string pinlist;
	string irange;
	string iClampL;
	string iClampH;
	double waittime;

    void init(){

//		add_param("irange","string",&irange).set_default("R25MA")
//											.set_options("BEST_FIT:R5UA:R25UA:R250UA:R2_5MA:R25MA:R500MA:R1A");
    	add_param("Pinlist","string",&pinlist);//.set_default("VDD_PMU_3V3_IN3,VDD_PMU_1V5_IN,VDD_PMU_3V3_IN1,VDD_PMU_3V3_IN2");
		add_param("Irange","string",&irange);//.set_default("E_POWER_R25MA,E_POWER_R500MA,E_POWER_R25MA,E_POWER_R500MA");
		add_param("IClampL","string",&iClampL);//.set_default("-0.02,-0.02,-0.02,-0.02");
		add_param("IClampH","string",&iClampH);//.set_default("0.02,0.1,0.01,0.1");
		add_param("WaitTime","double",&waittime);//.set_default("100e-6");

    }
    PowerRange rangeSuite(string str){
        	PowerRange range;
        	if(str == "E_POWER_BEST_FIT"){
        		range = E_POWER_BEST_FIT;
        	}else if(str == "0.000005"){
        		range = E_POWER_R5UA;
        	}else if(str == "0.000025"){
        		range = E_POWER_R25UA;
        	}else if(str == "0.00025"){
        		range = E_POWER_R250UA;
        	}else if(str == "0.0025"){
        		range = E_POWER_R2_5MA;
        	}else if(str == "0.025"){
        		range = E_POWER_R25MA;
        	}else if(str == "0.5"){
        		range = E_POWER_R500MA;
        	}else if(str == "1"){
        		range = E_POWER_R1A;
        	}
        	return range;
        }

    void execute(){
		double hil[30], lowl[30];
		vector<string> Test_Item;
		vector<string> Units;
		int Test_number[30],Soft_Bin[30],Hard_Bin[30];
		Read_Limit(lowl, hil, Test_Item, Test_number, Units, Soft_Bin,Hard_Bin);

		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level

    	vector<string> pinlist_tmp = split(pinlist,',');
    	vector<string> irange_tmp = split(irange,',');
    	vector<string> iClampL_tmp = split(iClampL,',');
    	vector<string> iClampH_tmp = split(iClampH,',');


    	for(unsigned int i=0;i< pinlist_tmp.size();i++)
    	{
			TheInst.DCVS().Pins(pinlist_tmp[i]).SetIRange(rangeSuite(irange_tmp[i]))
													.SetIClampL(atof(iClampL_tmp[i].c_str()))
													.SetIClampH(atof(iClampH_tmp[i].c_str()))
													.Apply();

    	}

		TheInst.DCVS().Pins(pinlist).SetMeasureMode(E_DC_MODE_MI)
											  .SetMeasureMethod(E_DC_METHOD_STATIC)
											  .SetReadMode(E_DC_MODE_MEASURE)
											  .SetMeasureOrder(E_DC_ORDER_SINGLE)
											  .SetWaitTime(waittime)//chuanru
											  .Measure();

		PinArrayDouble Result1= TheInst.DCVS().Pins(pinlist).GetMeasureResults();
		for(unsigned int i=0;i< pinlist_tmp.size();i++){
			TheSoft.Flow().TestLimit(pinlist_tmp[i],Result1,lowl[i], hil[i],Hard_Bin[i],Soft_Bin[i], Units[i], Test_Item[i], Test_number[i]);
		}

		TheInst.DCVS().Power().Apply();
    }
};
REGISTER_TESTCLASS("ADC_DAC_IDD",ADC_DAC_IDD)







