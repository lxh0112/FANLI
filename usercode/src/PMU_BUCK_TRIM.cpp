/*
 * BUCK_VrefTrim.cpp
 *
 *  Created on: 2021年8月19日
 *      Author: 荣耀
 */
#include "GetLog.h"
#include "Globle_Var.h"
#include "TestClass.h"
#include <iostream>
#include <string>
#include "UserAPI.h"
#include "d2sProtocolSSI.h"
#include "D2S_PMU_Module.h"
#include <math.h>
#include"readlimit.h"

class BUCK_VrefTrim: public TestClass{
public:
	std::string pinlist;
    int samplesize;
    void init(){
				 add_param( "Measure_pinlist",  "PinString", &pinlist).set_default("VDD_BUCK_1V5_IN");
				 add_param("SampleSize","int",&samplesize).set_default("16");
    }

    void execute(){
					double hil[30],lowl[30];
					char *Test_Item[30],*Units[30];
					int  Test_number[30];
					Read_Limit(lowl,hil,Test_Item,Test_number,Units);

					double *GetValue;
					map<int, double> preTrimMeas;
					map<int, long long> TrimData;

					TheInst.DCVS().Power().Apply();
					TheInst.Digital().Level().Apply();
					TheInst.DCVS().Pins(pinlist).SetMeasureMode(PhxAPI::E_DC_MODE_MV)
											    .SetMeasureMethod(PhxAPI::E_DC_METHOD_STATIC)
											    .SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
											    .SetMeasureOrder(PhxAPI::E_DC_ORDER_SINGLE)
											    .SetSampleSize(samplesize)
											    .SetWaitTime(5*ms)
											    .Measure();

					PinArrayDouble res = TheInst.DCVS().Pins(pinlist).GetMeasureResults();
					FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
						double GetValue = res.GetData(pinlist, site_id);
						Testsoftbin[site_id] = 1;
						preTrimMeas[site_id] = GetValue;
						if(FT_PASSFLAG[site_id]==0){
							buck_v_trimData[site_id] = floor((1.4/preTrimMeas[site_id]-1)*267+0.5);
							if(buck_v_trimData[site_id]>15){
								buck_v_trimData[site_id]=0;
							}
							else if(buck_v_trimData[site_id]>=0){
								buck_v_trimData[site_id]=buck_v_trimData[site_id];
							}
							else if(buck_v_trimData[site_id]>=-15){
								buck_v_trimData[site_id]=abs(buck_v_trimData[site_id])+16;
							}
							else{
								buck_v_trimData[site_id]=0;
							}
						}else{
							buck_v_trimData[site_id] = buck_v_pretrimData[site_id];
						}
					FOREACH_ACTIVESITE_END
					TheSoft.Flow().TestLimit("VDD_BUCK_1V5_IN" ,preTrimMeas ,1.25 ,1.65 ,6,6003,"V","PRETRIM",60030000,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);
					TheSoft.Flow().TestLimit("VDD_BUCK_1V5_IN" ,buck_v_trimData ,0 ,30 ,6,6003,"","TRIMCODE",60030001,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);

					d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
					d2sProtocolSSI d2s_test;
					d2s_test.SSI_write(0x200,0x2000,false);
					d2s_test.SSI_write(0x202,0x40,false);
					d2s_test.SSI_read(0x154,"readdata1");
					d2s::d2s_LABEL_END();

					map<int, long long> capture_data;
					map<int, long long> iter = d2s_test.getReadValue("readdata1");
					for(map<int, long long>::iterator it = iter.begin(); it != iter.end(); it++) {
						long long readvalue =it->second;
						capture_data[it->first] = readvalue ;
						capture_data[it->first]=capture_data[it->first]&(0xFFE0);
						capture_data[it->first]=capture_data[it->first]|buck_v_trimData[it->first];
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
						preTrimMeas[site_id] = GetValue;

						if(Testsoftbin[site_id]!=1){
						}

						PRE_BUCK_TRIM[site_id] = preTrimMeas[site_id];
					FOREACH_ACTIVESITE_END
					TheSoft.Flow().TestLimit("VDD_BUCK_1V5_IN" ,preTrimMeas ,1.384 ,1.416 ,6,6002,"V","POSTTRIM",60030002,PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,PhxAPI::E_RS_DEC);


    }

};



REGISTER_TESTCLASS("BUCK_VrefTrim",BUCK_VrefTrim)
