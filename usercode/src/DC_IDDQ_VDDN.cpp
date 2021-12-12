/*
 * DC_IDDQ_VDDN.cpp
 *
 *  Created on: 2021年8月26日
 *      Author: YK16
 */
#include "Globle_Var.h"
#include "TestClass.h"
#include <iostream>
#include <string>
#include "UserAPI.h"
#include "d2sProtocolSSI.h"
#include "D2S_PMU_Module.h"
#include <math.h>
#include"Getlog.h"
#include"readlimit.h"

using namespace PhxAPI;

class DC_IDDQ_VDDN: public TestClass{
public:
	std::string measurepin;
//	bool HBIN_FLAG[4];

    void init(){

    }

    void execute(){
        TheInst.DCVS().Power().Apply();
        TheInst.Digital().Level().Apply();
        TheInst.Digital().Timing().Apply();
    	TheInst.Digital().Pattern().Start();
//
//    	 const char *dctestblock = "DC_IDDQ";
//    	 const char *signal_1 = "VDD_PMU_SYSLDO";
//    	 const char *signal_2 = "VDD_PMU_CLDO";
//
//    	 double hil[40],lowl[40];
//    	 char *Test_Item[40],*Units[40];
//    	 int  Test_number[40];
//    	 Read_Limit(lowl,hil,Test_Item,Test_number,Units);

    	//    int Minorld = 0;
//    	 int active_site = 0;
//    	 double sum_IDDQ_CLDO[4] = {0};
//    	 double sum_IDDQ_SYSLDO[4] = {0};
//    	 double IDDQ_SYSLDO[4] = {0};


//    	 PATTERN_STATUS patternstatus;
//    	 const char *patternname = api->Get_current_patternblock_name();
//    	 site_id->info_message("--------------pattern name is %s -------------",patternname);
    	 //void InfoMessage(string format, ...);
//    	 api->Start_pattern();
//modify    	 bool Start(string DC_IDDQ_R02_HI1151V200_ALL_BODY_X1_SM_V1);
//    	 int i=0;
//    	 do{
//    	        patternstatus =api->Get_pattern_status();
//    	        if(patternstatus == PS_INFINITE){
    	        //execute DC_IDDQ_ONLY
    	 measurepin="VDD_PMU_SYSLDO,VDD_PMU_CLDO";
    	        	TheInst.DCVS().Power().Apply();
    	        	TheInst.Digital().Level().Apply();

    	        	TheInst.DCVS().Pins("VDD_PMU_SYSLDO").SetMeasureMode(PhxAPI::E_DC_MODE_MI)
    	        											 .SetMeasureMethod(PhxAPI::E_DC_METHOD_TRIGGER)
    	        											 .SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
    	        											 .SetMeasureOrder(PhxAPI::E_DC_ORDER_SINGLE)
    	        											 .SetVForce(1.1* V)
    	        											 .SetIRange(PhxAPI::E_POWER_R2_5MA)
    	        											 .SetILimitH(600* uA)
    	        											 .SetILimitL(5 *uA)
    	        											 .SetIClampH(1* mA)
    	        											 .SetIClampL(-1* mA)
    	        											 .SetSampleSize(16)
    	        											 .SetWaitTime(100*us)	//unit:us
    	        											.Measure();

    	        	TheInst.Digital().Pattern().Start();
    	        	TheInst.Wait(10000*us);  //unit:us
//    	        	PinArrayDouble res = TheInst.DCVS().Pins("VDD_PMU_SYSLDO").GetMeasureResults();//有问题吗

    	        	TheInst.DCVS().Pins("VDD_PMU_CLDO").SetMeasureMode(PhxAPI::E_DC_MODE_MI)
    	        											 .SetMeasureMethod(PhxAPI::E_DC_METHOD_TRIGGER)
    	        											 .SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
    	        											 .SetMeasureOrder(PhxAPI::E_DC_ORDER_SINGLE)
    	        											 .SetVForce(1.1* V)
    	        											 .SetIRange(PhxAPI::E_POWER_R25MA )
    	        											 .SetILimitH(16* mA)
    	        											 .SetILimitL(100* uA)
    	        											 .SetIClampH(20* mA)
    	        											 .SetIClampL(-10* uA)
    	        											 .SetSampleSize(16)
    	        											 .SetWaitTime(100*us)	//unit:us
    	        											.Measure();

    	        	TheInst.Digital().Pattern().Start();
    	        	TheInst.Wait(10000*us);  //unit:us
    	        	PinArrayDouble res2 = TheInst.DCVS().Pins("VDD_PMU_CLDO").GetMeasureResults();//有问题吗

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
    	    //    }
#if 0
    	            FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
    	        	double *result_pin1;
    	            double *result_pin2;

//    	            site_id->Info_message("------DC_IDDQ_VDDN%d------",i);
    	            double GetValue = res.GetData("VDD_PMU_SYSLDO,VDD_PMU_CLDO", site_id);
    	            sum_IDDQ_SYSLDO[active_site] = sum_IDDQ_SYSLDO[active_site] + result_pin1[0];
    	            double GetValue2 = res2.GetData("VDD_PMU_SYSLDO,VDD_PMU_CLDO", site_id);
    	            sum_IDDQ_CLDO[active_site] = sum_IDDQ_CLDO[active_site] + result_pin2[0];
    	            ValueTest (site_id, signal_2, result_pin2[0], lowl[i*2], hil[i*2], "A", Test_Item[i*2], "FAIL_BIN", Test_number[i*2], Clogenable);
    	            ValueTest (site_id, signal_1, result_pin1[0], lowl[i*2+1], hil[i*2+1], "A", Test_Item[i*2+1], "FAIL_BIN", Test_number[i*2+1], Clogenable);

    	//                api->info_message("Site:%d---------- %s    measure  value    :    %f-----------",active_site,signal_1,result_pin1[0]);
    	//                api->info_message("Site:%d---------- %s    measure  value    :    %f-----------",active_site,signal_2,result_pin2[0]);

    	//                if((HBIN_FLAG[active_site] == 0)&&(api->Get_result_bin() != 1)){
    	//                                HBIN_FLAG[active_site] = 1;
    	//                        }

    	            FOREACH_ACTIVESITE_END
    	            i++;
//    	            api->Resume_pattern();

//    	        }
//    	    }
//    	    while(patternstatus!=PS_STOPPED);

    	    FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)

    	        IDDQ_CLDO[site_id] = sum_IDDQ_CLDO[site_id]/i;
    	        IDDQ_SYSLDO[site_id] = sum_IDDQ_SYSLDO[site_id]/i;

    	        ValueTest (site_id, signal_2, IDDQ_CLDO[site_id], lowl[32], hil[32], "A", Test_Item[32], "FAIL_BIN", Test_number[32], Clogenable);
    	        ValueTest (site_id, signal_1, IDDQ_SYSLDO[site_id], lowl[33], hil[33], "A", Test_Item[33], "FAIL_BIN", Test_number[33], Clogenable);
    	    FOREACH_ACTIVESITE_END
#endif
	}

};

REGISTER_TESTCLASS("DC_IDDQ_VDDN",DC_IDDQ_VDDN)



