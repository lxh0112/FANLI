/*
 * File:   D2S_ABB_Module.cpp
 * Author:
 *
 * Created on 2020年11月10日, 下午3:28
 */
#include "Systick.h"
#include "UserAPI.h"
#include "d2sProtocolSSI.h"
#include "string.h"
#include "Capture_Function.h"


void DIO_Capture(int Site_id,std::string Pin,unsigned long *Cap_data)
{
	//int cap_data_re[num];
	/* step2:  get capture data*/
	map<uint32_t, map<string, vector<uint8_t> > > CAP_Data = TheInst.Digital().PatEng().GetCaptureRawData(Pin);
	map<string, vector<uint8_t>> capFailData;
	vector<uint8_t> data;

	if(CAP_Data.size() > 0U)
	{
		for(auto it = CAP_Data.begin(); it != CAP_Data.end(); it++)
		{
			if(Site_id == it->first)
			{
				cout<<"\n\nSite Number : " << dec << it->first<<endl;
					capFailData = it->second;

				for(auto pit = capFailData.begin(); pit != capFailData.end(); pit++)
				{
					cout<<"\nPin Name : " <<  (pit->first)<<endl;
					data = (pit->second);
					cout<<"Cap result : bit 0 ~ 19"<<endl;
				}
				cout<<endl;
			}
		}
		cout<< "cature size: " << data.size() <<endl;
		for(int i = 0; i < data.size(); i++)
		{
			Cap_data[i] = ((unsigned long)(data[i])>>2U)&0x3;
			if(Cap_data[i] == 3)
				Cap_data[i] = 0;

			//cout<<"\ncapture data1111111 is : " << cap_data[i] <<endl;
		}
	}
	else
	{
		cout<<"\n\nThere's no capture data !"<<endl;
	}
}

long long D2S_GetValue(int Site_id,d2sProtocolSSI d2s_test,char *cReadFlag)
{
	long long D2S_value;
	map<int, long long> capture_data = d2s_test.getReadValue(cReadFlag);
	if(capture_data.size() > 0U)
	{
		for(auto it = capture_data.begin(); it != capture_data.end(); it++)
		{
			if(Site_id == it->first)
				D2S_value =  it->second;
		}

	}
	else
	{
		cout<<"\n\nThere's no capture data !"<<endl;
	}
	return D2S_value;

}


void Cal_Frequency_Undersampling(double fs,int *data,int originN,double &ft) {
	int length0 = 0;
	int length1 = 0;

	int transFlag021 = 0;
	int transFlag120 = 0;
	for(int i =100;i < 10000; i++)
	{
//        api->Info_message("-------%d",i);
//        api->Info_message("################%d",data1[i]);
		if(data[100] == 0)
		{
			transFlag021 = 1;
		}
		else
		{
			transFlag120 = 1;
		}

		if(1 == transFlag021)
		{
			if(data[i] == 0)
			{
				if(length1 == 0)
				{

				}
				else
				{
					if(data[i+1] == 0 && data[i+2] == 0  && data[i+3] == 0 )
					{
						length0 ++;
					}
				}

			}
			else if(data[i] == 1 )
			{
				if(data[i+1] == 1 && data[i+2] == 1  && data[i+3] == 1 )
				{
					length1 ++;
				}

				if( length0 > 0)
				{
					if((length1 + length0) > (originN)/2)
					{
						break;
					}
					else
					{
						length0 =0;
						length1 =0;
					}
				}

//              pre1 = 1;
			}
		}
		else if(1 == transFlag120)
		{
			if(data[i] == 1)
			{
				if(length0 == 0)
				{

				}
				else
				{
					if(data[i+1] == 1 && data[i+2] == 1 && data[i+3] == 1 )
					{
						length1 ++;
					}
				}

			}
			else if(data[i] == 0)
			{

				if(data[i+1] == 0  &&data[i+2] == 0  && data[i+3] == 0  )
				{
					length0 ++;
				}


				if( length1 > 0)
				{
					if( (length1 + length0) > (originN)/2)
					{
						break;
					}
					else
					{
						length0 =0;
						length1 =0;
					}
				}

			}

		}
	}

	int N = length0 + length1;

	cout<<"L0################"<<length0<<endl;
	cout<<"L1################"<<length1<<endl;

	ft = fs*(1+N)/N ;

	cout<<"KKKKKK"<<ft<<endl;
}

