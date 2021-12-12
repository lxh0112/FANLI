/*
 * PMU_CAPLESSLDO_TEST.cpp
 *
 *  Created on: 2021年8月16日
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

class PMU_CAPLESS_LDO_TEST: public TestClass{
public:
		std::string pinlist;
		int samplesize;

    void init(){
				 add_param( "Measure_pinlist",  "PinString", &pinlist).set_default("PMU_RBIAS");
				 add_param("SampleSize","int",&samplesize).set_default("16");
               }

    void execute(){
					TheInst.DCVS().Power().Apply();
					TheInst.Digital().Level().Apply();
					FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
					Testsoftbin[site_id] = 1;
					FOREACH_ACTIVESITE_END
					d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
					d2sProtocolSSI d2s_test;
					d2s_test.SSI_write(0x200,0x2000,false);
					d2s_test.SSI_write(0x202,0x40,false);
					d2s_test.SSI_write(0x124,0x10);
					d2s::d2s_LABEL_END();

					double *GetValue;
					map<int, double> vMeas;
					char *muxMeasPins[3]={"INTLDO","BBLDO0","BBLDO1"};
					double muxLowLimit[3]={1.4,1.14,1.14};
					double muxHighLimit[3]={1.54,1.26,1.26};
					int muxTest_Number[3]={60050008,60050009,60050010};
					long muxRegs[9]={0x0,0x0,0x40,0x800,0x0,0x80,0x0,0x800,0x80};

					for(int i=0;i<3;i++){
						d2s::d2s_LABEL_BEGIN( "ssi", d2s_WorkMode);
						d2sProtocolSSI d2s_test;
						d2s_test.SSI_write(0x202,0x94,false);
						d2s_test.SSI_write(0x37C,muxRegs[i*3]);
						d2s_test.SSI_write(0x384,muxRegs[i*3+1]);
						d2s_test.SSI_write(0x202,0x40,false);
						d2s_test.SSI_write(0x148,muxRegs[i*3+2]);
						d2s::d2s_LABEL_END();

						TheInst.DCVS().Pins(pinlist).SetMeasureMode(PhxAPI::E_DC_MODE_MV)
												    .SetMeasureMethod(PhxAPI::E_DC_METHOD_STATIC)
												    .SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
												    .SetSampleSize(samplesize)
												    .SetWaitTime(5 * ms)
						                            .Measure();

						PinArrayDouble result = TheInst.DCVS().Pins(pinlist).GetMeasureResults();
						TheSoft.Flow().TestLimit(pinlist,result);
					  }
				}
};

 REGISTER_TESTCLASS("PMU_CAPLESS_LDO_TEST",PMU_CAPLESS_LDO_TEST)
