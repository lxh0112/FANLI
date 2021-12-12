/*
 * PMU_IrefTrim.cpp
 *
 *  Created on: 2021年8月19日
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

class PMU_IrefTrim: public TestClass{
public:
		std::string pinlist;
		int samplesize;
    void init(){
    	        add_param("Measure_pinlist",  "PinString", &pinlist).set_default("PMU_RBIAS");
    	        add_param("SampleSize","int",&samplesize).set_default("16");
    }

    void execute(){
                     double hil[30],lowl[30];
                     char *Test_Item[30],*Units[30];
                     int  Test_number[30];
                     Read_Limit(lowl,hil,Test_Item,Test_number,Units);

                     map<int, double> preTrimMeas;
                     map<int, long long> TrimData;
                     map<int, double> postTrimMeas;
                     double Voffset[4] = {0.009, 0.009, 0.009, 0.009};

		             TheInst.DCVS().Power().Apply();
		             TheInst.Digital().Level().Apply();
		             TheInst.DCVS().Pins(pinlist).SetMeasureMode(PhxAPI::E_DC_MODE_MI)
										         .SetMeasureMethod(PhxAPI::E_DC_METHOD_STATIC)
										         .SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
										         .SetMeasureOrder(PhxAPI::E_DC_ORDER_SINGLE)
										         .SetSampleSize(samplesize)
										         .SetWaitTime(1*ms)
										         .Measure();
					PinArrayDouble res = TheInst.DCVS().Pins(pinlist).GetMeasureResults();
					FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
					double GetValue = res.GetData(pinlist, site_id);
					Testsoftbin[site_id] = 1;
					preTrimMeas[site_id] = GetValue;
					preTrimMeas[site_id] = preTrimMeas[site_id]*(-120000) + Voffset[site_id];
					if(FT_PASSFLAG[site_id]==0){
						TrimData[site_id] = floor((((99*preTrimMeas[site_id])/1.2)-99)+13+0.5);
						if(TrimData[site_id] > 31){
							TrimData[site_id] = 0;
						}
						else if(TrimData[site_id] >=0 ){
							TrimData[site_id] = TrimData[site_id];
						}
						else {
							TrimData[site_id] = 0;
						}
					}else{
					   TrimData[site_id] = pb_i_pretrimData[site_id];
					}

					pb_i_TrimData[site_id] = TrimData[site_id];
					TrimData[site_id] = TrimData[site_id]<<5;
					FOREACH_ACTIVESITE_END
					TheSoft.Flow().TestLimit("PMU_RBIAS" ,preTrimMeas ,1.11 ,1.33 ,6,6004,"V","PRETRIM",60040000,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
					TheSoft.Flow().TestLimit("PMU_RBIAS" ,pb_i_TrimData ,0 ,30 ,6,6004,"","TRIMCODE",60040001,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);

					d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
					d2sProtocolSSI d2s_test;
					d2s_test.SSI_write(0x200,0x2000,false);
					d2s_test.SSI_write(0x202,0x40,false);
					d2s_test.SSI_read(0x154,"readdata");
					d2s::d2s_LABEL_END();

					map<int, long long> capture_data;
					map<int, long long> iter = d2s_test.getReadValue("readdata");

					for(map<int, long long>::iterator it = iter.begin(); it != iter.end(); it++) {
					long long readvalue = it->second;
					capture_data[it->first] = readvalue ;
					capture_data[it->first]=capture_data[it->first]&(0xFC1F);
					capture_data[it->first]=capture_data[it->first]|TrimData[it->first];
					}
					d2s::d2s_LABEL_BEGIN("dynamic", d2s_WorkMode);
					d2s_test.SSI_writeDynamic(0x154,capture_data,"write");
					d2s::d2s_LABEL_END();
					TheInst.Wait(10*ms);

					TheInst.DCVS().Power().Apply();
					TheInst.Digital().Level().Apply();
					TheInst.DCVS().Pins(pinlist).SetMeasureMode(PhxAPI::E_DC_MODE_MI)
												.SetMeasureMethod(PhxAPI::E_DC_METHOD_STATIC)
												.SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
												.SetMeasureOrder(PhxAPI::E_DC_ORDER_SINGLE)
												.SetSampleSize(samplesize)
												.SetWaitTime(1*ms)
												.Measure();
					PinArrayDouble res2 = TheInst.DCVS().Pins(pinlist).GetMeasureResults();
					FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
					double GetValue2 = res2.GetData(pinlist, site_id);
					postTrimMeas[site_id] = GetValue2;
					postTrimMeas[site_id] = postTrimMeas[site_id]*(-120000) + Voffset[site_id];
					if(Testsoftbin[site_id]!=1){
					}

					PRE_IREF_TRIM[site_id] = preTrimMeas[site_id];
					FOREACH_ACTIVESITE_END
					TheSoft.Flow().TestLimit("PMU_RBIAS" ,postTrimMeas ,1.188 ,1.215 ,6,6004,"V","POSTTRIM",60040002,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);

    }

};
REGISTER_TESTCLASS("PMU_IrefTrim",PMU_IrefTrim)

