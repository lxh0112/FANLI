 //
// Created by f.he on 2021/6/18.
//

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include <synchapi.h>

class Basic_04_DC_IDDQ_Measure: public TestClass{
public:
		std::string pinlist;
		int samplesize;

	void init(){
					add_param( "Measure_pinlist",  "PinString", &pinlist);
					add_param("SampleSize","int",&samplesize).set_default("16");
	           }
    void execute(){
					TheInst.DCVS().Power().Apply();
					TheInst.Digital().Level().Apply();
					TheInst.Digital().Timing().Apply();
					TheInst.DCVS().Pins("VDD_PMU_SYSLDO").SetIRange(PhxAPI::E_POWER_R2_5MA).SetIClampH(1*mA).SetIClampL(-1*mA);
					TheInst.DCVS().Pins("VDD_PMU_CLDO").SetIRange(PhxAPI::E_POWER_R25MA).SetIClampH(20*mA).SetIClampH(-0.01*mA);
					TheInst.DCVS().Pins(pinlist).SetMeasureMode(PhxAPI::E_DC_MODE_MI)
												.SetReadMode(PhxAPI::E_DC_MODE_MEASURE)
												.SetMeasureMethod(PhxAPI::E_DC_METHOD_TRIGGER)
												.SetMeasureOrder(PhxAPI::E_DC_ORDER_SINGLE)
												.SetSampleSize(samplesize)
												.SetWaitTime(5*ms)
												.Measure();
					TheInst.Digital().Pattern().Start();
					TheInst.Wait(3*ms);
					vector<PinArrayDouble> iddq_result = TheInst.DCVS().Pins(pinlist).GetTrigResults();
					TheInst.DCVS().ClearAllSetPara();

//					map<int,double> IDDQ_DATA_1[17];
//					map<int,double> IDDQ_DATA_2[17];
//					FOREACH_ACTIVESITE_BEGIN(SiteID,bInterrupt)
//					double SUM_IDDQ1 = 0.0;
//					double SUM_IDDQ2 = 0.0;
////					PinArrayDouble AVG_IDDQ_CLDO;
////					PinArrayDouble AVG_IDDQ_SYSLDO;
//					for(int i=0;i<iddq_result.size(); i++)
//					{
//
//						SUM_IDDQ1 = SUM_IDDQ1 + iddq_result[i].GetData("VDD_PMU_CLDO",SiteID);
//						IDDQ_DATA_1[i][SiteID]=iddq_result[i].GetData("VDD_PMU_CLDO",SiteID);
////						TheSoft.Flow().TestLimit("VDD_PMU_CLDO",SiteID,iddq_result[i].GetData("VDD_PMU_CLDO",SiteID));
//						SUM_IDDQ2 = SUM_IDDQ2 + iddq_result[i].GetData("VDD_PMU_SYSLDO",SiteID);
//						IDDQ_DATA_2[i][SiteID]=iddq_result[i].GetData("VDD_PMU_SYSLDO",SiteID);
////						TheSoft.Flow().TestLimit("VDD_PMU_SYSLDO",SiteID,iddq_result[i].GetData("VDD_PMU_SYSLDO",SiteID));
////						IDDQ_DATA[i][SiteID] = iddq_result[i].GetData("VDD_PMU_SYSLDO",SiteID);
//					}
//
//					double AVG_IDDQ1 = SUM_IDDQ1/iddq_result.size();
//					double AVG_IDDQ2 = SUM_IDDQ2/iddq_result.size();
//					IDDQ_DATA_1[17][SiteID] = AVG_IDDQ1;
//					IDDQ_DATA_2[17][SiteID] = AVG_IDDQ2;
//
//					for(int i=0;i<(iddq_result.size()+1); i++)
//					{
//						TheSoft.Flow().TestLimit("VDD_PMU_CLDO",IDDQ_DATA_1[i]);
//						TheSoft.Flow().TestLimit("VDD_PMU_SYSLDO",IDDQ_DATA_2[i]);
//					}
//
////					AVG_IDDQ_CLDO.AddPinData("VDD_PMU_CLDO",AVG_IDDQ1);
////					AVG_IDDQ_SYSLDO.AddPinData("VDD_PMU_CLDO",AVG_IDDQ2);
////					TheSoft.Flow().TestLimit("VDD_PMU_CLDO",AVG_IDDQ_CLDO);
////					TheSoft.Flow().TestLimit("VDD_PMU_SYSLDO",AVG_IDDQ_SYSLDO);
//					FOREACH_ACTIVESITE_END
					FOREACH_ACTIVESITE_BEGIN(SiteID,bInterrupt)
					int cap_size = iddq_result.size();
					vector<double> data1;
					vector<double> data2;
					double IDDQ_SYSLDO_result = 0.0;
					double IDDQ_CLDO_result = 0.0;
					PinArrayDouble IDDQ_SYSLDO;
					PinArrayDouble IDDQ_CLDO;
					for(int i=0;i<iddq_result.size();i++)
					{
//						iddq_result[i].ShowPinArrayData();
						double datatemp1 =0.0;
						double datatemp2 =0.0;
						datatemp1=iddq_result[i].GetData("VDD_PMU_SYSLDO",SiteID);
						data1.push_back(datatemp1);

						datatemp2=iddq_result[i].GetData("VDD_PMU_CLDO",SiteID);
						data2.push_back(datatemp2);

						IDDQ_SYSLDO_result =IDDQ_SYSLDO_result+datatemp1;
						IDDQ_CLDO_result =IDDQ_CLDO_result+datatemp2;
					}

					if(cap_size!=0)
					{
						IDDQ_CLDO_result= IDDQ_CLDO_result /cap_size;
						IDDQ_SYSLDO_result= IDDQ_SYSLDO_result /cap_size;

						cout<<IDDQ_CLDO_result<<endl;
						cout<<IDDQ_SYSLDO_result<<endl;

						IDDQ_CLDO.AddPinData("VDD_PMU_CLDO",IDDQ_CLDO_result);
						IDDQ_SYSLDO.AddPinData("VDD_PMU_SYSLDO",IDDQ_SYSLDO_result);

						TheSoft.Flow().TestLimit("VDD_PMU_CLDO",IDDQ_CLDO);
						TheSoft.Flow().TestLimit("VDD_PMU_SYSLDO",IDDQ_SYSLDO);
					}
					else
					{
						cout<<"!!!The capture size is :"<<cap_size<<",it is WRONG!!!"<<endl;
					}
					FOREACH_ACTIVESITE_END
			}
};
REGISTER_TESTCLASS("Basic_04_DC_IDDQ_Measure",Basic_04_DC_IDDQ_Measure)

