/*
 * Basic_07_TSensor_Read.cpp
 *
 *  Created on: 2021å¹´7æœˆ28æ—¥    --based on 1.0.2.8
 */

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include <math.h>
#include <synchapi.h>

using namespace PinTool;

#define I2C_DELAY 		4

class Basic_07_TSensor_Read: public TestClass{
public:
	std::string CapPin;
	std::string DieID_TSR_Read;
	std::string DieID_TSR_Ref;
	double T_A;
	double T_B;
	int Cnt;
	int Delta_Temp;
	int Temp_Ref;
	int N_sample;

    void init(){
    	add_param( "TSensor_CapPin",  "PinString", &CapPin).set_default("JTAG_TDO");
    	add_param( "TSersor_DieID_TSR_Read",  "String", &DieID_TSR_Read).set_default("TSR1");
    	add_param( "TSersor_DieID_TSR_Ref",  "String", &DieID_TSR_Ref).set_default("TSR_REF");
		add_param("TSensor_T_A","double",&T_A).set_default("116");
		add_param("TSensor_T_B","double",&T_B).set_default("922");
		add_param("TSersor_Cnt","int",&Cnt).set_default("1");
		add_param("TSersor_Delta_Temp","int",&Delta_Temp).set_default("0");
		add_param("TSersor_Temp_Ref","int",&Temp_Ref).set_default("25");
		add_param("TSensor_N_sample","int",&N_sample).set_default("16");

    }


    void execute(){

		TheInst.DCVS().Power().Apply();
		TheInst.Digital().Level().Apply();
		TheInst.Digital().Timing().Apply();
		TheInst.Digital().Pattern().Start();

	    int num =Cnt*N_sample*10;
	    int cap_data_re[num];
	    double TSensor_Temp[Cnt][N_sample];
	    double SUM_Temp[Cnt];
	    double TsensorAvg_SDBL[Cnt];

	    map<uint32_t, map<string, vector<PatEngGetCaptureData> > > capData;

	    capData = TheInst.Digital().PatEng().GetCaptureData("JTAG_TDO");
		map<string, vector<PatEngGetCaptureData>> capFailData;
		vector<PatEngGetCaptureData> data;

		if(capData.size() > 0U)
		{
			for(auto it = capData.begin(); it != capData.end(); it++)
			{
				cout<<"\n\nSite Number : " << dec << it->first<<endl;
                auto capFailData = it->second;

				for(auto pit = capFailData.begin(); pit != capFailData.end(); pit++)
				{
					cout<<"\nPin Name : " <<  (pit->first)<<endl;
					data = (pit->second);
					cout<<"Cap result : bit 0 ~ 19"<<endl;
				}
				cout<<endl;
			}
			cout<< "cature size: " << data.size() <<endl;
			for(int i = 0; i < data.size(); i++)
			{
				cap_data_re[i] = data.size();
				cout<<"\ncapture data1111111 is : " << cap_data_re[i] <<endl;
			}
		}
		else
		{
			cout<<"\n\nThere's no capture data !"<<endl;
		}


		for(int Count=0; Count<Cnt; Count++){
			SUM_Temp[Count]=0.0;

			for(int i=Count*16; i<N_sample*(Count+1); i++){
				TSensor_Temp[Count][i]={0};
				int data123[10]={0};
				for(int j=0; j<10; j++){
					data123[j]=cap_data_re[i*10+j];
					TSensor_Temp[Count][i]=TSensor_Temp[Count][i]+data123[j]*pow(2,j);
				}

				cout<<"\TSensor_Temp data is : " << TSensor_Temp[Count][i] << " temp result ="<<((TSensor_Temp[Count][i] - T_A)/(T_B-T_A) * (125 + 40) -40) <<endl;

				SUM_Temp[Count] = SUM_Temp[Count] + TSensor_Temp[Count][i];
			}
			cout<<"\n*********** SUM_Temp data is : " << SUM_Temp[Count] <<" ";

			TsensorAvg_SDBL[Count]=((SUM_Temp[Count]/N_sample) - T_A)/(T_B-T_A) * (125 + 40) -40;
			printf("TsensorAvg_SDBL is %lf **************\n",TsensorAvg_SDBL[Count]);
		}

    }


};






REGISTER_TESTCLASS("Basic_07_TSensor_Read",Basic_07_TSensor_Read)

