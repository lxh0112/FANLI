/*
 * PMU_VREF_TRIM.cpp
 *
 *  Created on: 2021年8月18日
 *      Author: 荣耀
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

class PMU_VrefTrim: public TestClass{
public:
		std::string pinlist;
		int samplesize;
    void init(){
				 add_param("Measure_pinlist",  "PinString", &pinlist).set_default("PMU_REFBP");
				 add_param("SampleSize","int",&samplesize).set_default("16");
    }

    void execute(){
					 TheInst.DCVS().Power().Apply();
					 TheInst.Digital().Level().Apply();

					 double hil[30],lowl[30];
					 char *Test_Item[30],*Units[30];
					 int  Test_number[30];
					 Read_Limit(lowl,hil,Test_Item,Test_number,Units);

					 d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
					 d2sProtocolSSI d2s_test;
					 d2s_test.SSI_write(0x200,0x2000,false);
					 d2s_test.SSI_write(0x202,0x40,false);
					 d2s_test.SSI_write(0x124,0xb0);
					 d2s::d2s_LABEL_END();

					 map<int, double> preTrimMeas;
					 map<int, long long> TrimData;
					 map<int, double> postTrimMeas;
					 double Voffset = 0.002;

					 TheInst.DCVS().Power().Apply();
					 TheInst.Digital().Level().Apply();
					 TheInst.DCVS().Pins(pinlist).SetMeasureMode(PhxAPI::E_DC_MODE_MV)
												 .SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
												 .SetMeasureMethod(PhxAPI::E_DC_METHOD_STATIC)
												 .SetMeasureOrder(PhxAPI::E_DC_ORDER_SINGLE)
												 .SetSampleSize(samplesize)
												 .SetWaitTime(5*ms)
												 .Measure();
					 PinArrayDouble res = TheInst.DCVS().Pins(pinlist).GetMeasureResults();
					 FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
						double GetValue = res.GetData(pinlist, site_id);
						Testsoftbin[site_id] = 1;
						preTrimMeas[site_id] = GetValue + Voffset;
						 if(FT_PASSFLAG[site_id]==0){
							 pmu_v_trimData[site_id] = floor((1-(1.2/preTrimMeas[site_id]))*219.2+0.5);
							 if(pmu_v_trimData[site_id]>15){
								 pmu_v_trimData[site_id]=0;
							 }
							 else if(pmu_v_trimData[site_id]>=0){
								pmu_v_trimData[site_id]=pmu_v_trimData[site_id];

							 }
							 else if(pmu_v_trimData[site_id]>=-16){
								 pmu_v_trimData[site_id]=abs(pmu_v_trimData[site_id])-1+16;
							 }
							 else{
								 pmu_v_trimData[site_id]=0;
							 }
						 }else{
							 pmu_v_trimData[site_id] = pmu_v_pretrimData[site_id];
						 }
						 TrimData[site_id]=pmu_v_trimData[site_id]<<10;
						 cout << "preTrimMeas:" << preTrimMeas[site_id] << endl;
						 cout << "pmu_v_trimData:" << pmu_v_trimData[site_id] << endl;
					 FOREACH_ACTIVESITE_END
					 TheSoft.Flow().TestLimit("PMU_REFBP" ,preTrimMeas ,1.118 ,1.288 ,6,6002,"V","PRETRIM",60020000,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
					 TheSoft.Flow().TestLimit("PMU_REFBP" ,pmu_v_trimData ,0 ,30 ,6,6002,"","TRIMCODE",60020001,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);

					 d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
					 d2s_test.SSI_read(0x154,"readdata");
					 d2s::d2s_LABEL_END();
					 map<int, long long> capture_data;
					 map<int, long long> iter = d2s_test.getReadValue("readdata");
					 for(map<int, long long>::iterator it = iter.begin(); it != iter.end(); it++) {
						long long readvalue =it->second;
						capture_data[it->first] = readvalue ;
						capture_data[it->first]=capture_data[it->first]&(0x83FF);
						capture_data[it->first]=capture_data[it->first]|TrimData[it->first];
					 }
					 d2s::d2s_LABEL_BEGIN("dynamic", d2s_WorkMode);
					 d2s_test.SSI_writeDynamic(0x154,capture_data,"write");
					 d2s::d2s_LABEL_END();
					 TheInst.Wait(10*ms);

					 TheInst.DCVS().Power().Apply();
					 TheInst.Digital().Level().Apply();
					 TheInst.DCVS().Pins(pinlist).SetMeasureMode(PhxAPI::E_DC_MODE_MV)
											     .SetMeasureMethod(PhxAPI::E_DC_METHOD_STATIC)
											     .SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
											     .SetMeasureOrder(PhxAPI::E_DC_ORDER_SINGLE)
											     .SetSampleSize(samplesize)
											     .SetWaitTime(5*ms)
											     .Measure();
					 PinArrayDouble res2 = TheInst.DCVS().Pins(pinlist).GetMeasureResults();
					 FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
						double GetValue = res2.GetData(pinlist, site_id);
						postTrimMeas[site_id] = GetValue + Voffset;
						cout << "postTrimMeas:" << postTrimMeas[site_id] << endl;
						 if(Testsoftbin[site_id]!=1){
						 }
						 PRE_VREF_TRIM[site_id] = preTrimMeas[site_id];
					 FOREACH_ACTIVESITE_END
					 TheSoft.Flow().TestLimit("PMU_REFBP" ,postTrimMeas ,1.194 ,1.206 ,6,6002,"V","POSTTRIM",60020002,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);

    }

};

REGISTER_TESTCLASS("PMU_VrefTrim",PMU_VrefTrim)


