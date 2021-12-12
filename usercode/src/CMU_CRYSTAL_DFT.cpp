 //
// Created by f.he on 2021/6/18.
//

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>

#define ORG 1

class CMU_CRYSTAL_DFT: public TestClass{
public:
std::string freq_pinlist;

	void init(){
    				add_param( "FREQ_pinlist",  "string", &freq_pinlist).set_default("DBB_GPIO0");
	           }
    void Cal_Frequency_oversampling(double fs,int *data,int size,double &ft,int multi) {
    	{
    	    int start_sampling = 0;
    	    int end_sampling = 0;
    	    int len = 0;

    	    for(int i =10000; (i <size-2); i++)
    	    {
    	        if( ((data[i+1]-data[i]) ==1))
    	        {
    	            if(len ==0)
    	            {
    	                start_sampling = i;
    	            }
    	            else
    	            {
    	                end_sampling = i;
    	            }
    	            len++;
    	            if(len >multi){
    	                break;
    	            }
    	        }

    	    }

           cout<<"start_sampling"<<start_sampling<<endl;
           cout<<"end_sampling"<<end_sampling<<endl;
           cout<<"len"<<len<<endl;

           if(len==0)ft=0;
           else ft = (len - 1)*fs/(end_sampling - start_sampling);

           cout<<"KKKKKK"<<ft<<endl;
       }
    }

	int Frequency_Counter(string strPinList, double dIntervalTime, map<uint32_t, map<string, double> >& Result)
	{
		using namespace PhxAPI;
		TheInst.Digital().Frequency().EnablePins(strPinList );

		TheInst.Digital().Frequency().Clear();

		TheInst.Digital().Frequency().SetSource       ( E_FC_SOURCE_VOH )
									 .SetSlope        ( E_FC_SLOPE_FALL )
									 .SetInterValMode ( E_FC_IVM_FIXED  )
									 .SetInterValTime ( dIntervalTime   )
									 .SetFilterTime   (               0 )
									 .Apply();

		TheInst.Digital().Frequency().Start();

#if ORG
		uint32_t uiRet = TheInst.Digital().Frequency().GetResults(Result);
		if(uiRet != 0) {
			cout << "[ERROR] GetResults failed." << endl;
			return uiRet;
		}
#endif
		if(Result.size() == 0){
			cout << "Result is null." << endl;
			return -1;
		}

		return 0;
	}

	int Frequency_Counter(string strPinList, double dIntervalTime, map<string, map<uint32_t, double> >& Result)
	{
		using namespace PhxAPI;
		TheInst.Digital().Frequency().EnablePins(strPinList );

		TheInst.Digital().Frequency().Clear();

		TheInst.Digital().Frequency().SetSource       ( E_FC_SOURCE_VOH )
									 .SetSlope        ( E_FC_SLOPE_FALL )
									 .SetInterValMode ( E_FC_IVM_FIXED  )
									 .SetInterValTime ( dIntervalTime   )
									 .SetFilterTime   (               0 )
									 .Apply();

		TheInst.Digital().Frequency().Start();
#if !ORG
		uint32_t uiRet = TheInst.Digital().Frequency().GetResults(Result);
		if(uiRet != 0) {
			cout << "[ERROR] GetResults failed." << endl;
			return uiRet;
		}
#endif
		if(Result.size() == 0){
			cout << "Result is null." << endl;
			return -1;
		}

		return 0;
	}

	void execute(){
        TheInst.GIFA().SetChannel(0x00);
        TheInst.GIFA().Close();
		uint32_t UBIT[4] = {10,01,12,47};

//		TheInst.Util().SetUserPower(PhxAPI::E_USERPW_P5V, PhxAPI::E_UTIL_STATE_ON);
//		TheInst.Wait(5*s);
//		for(uint32_t j=0;j<256;j++)
//		{
//			TheInst.Util().SetRelayState(j, PhxAPI::E_UTIL_STATE_OFF); //bihe-0,duankai-1
//		}
//		TheInst.Wait(4*ms);//us

		for(int i=0;i<4;i++)
		{
			TheInst.Util().SetRelayState(UBIT[i],PhxAPI:: E_UTIL_STATE_ON);
		}
//		TheInst.Wait(4*ms);
		//relay


		TheInst.DCVS().Power().Apply();
		TheInst.Digital().Level().Apply();
		//        TheInst.Digital().Timing("").SetFreeRunningClock("XIN", 2.5e-8);
		TheInst.Digital().Timing().Apply();
		TheInst.Digital().Pattern().Start();


//		string TimingName = TheSoft.Flow().Timing().GetCurrentTimingBlockName();
//		string PatternName = TheSoft.Flow().Pattern().GetCurrentPatternName();

//		TheSoft.Flow().Timing().SetTiming("Capture_PLL");
//		TheInst.Digital().Timing().Apply();
//		TheSoft.Flow().Pattern().SetPattern("Capture_PLL");
//		TheInst.Digital().Pattern().Start();

#if ORG
			map<uint32_t, map<string, double> > Result;
			int iRet = Frequency_Counter(freq_pinlist, 2e-3, Result);
			if(iRet != 0) {
				cout <<"[ERROR] Frequency counter test failed." << endl;
				return;
			}
			map<string, map<int, double> > mapTemp;
			map<uint32_t, map<string, double> >::iterator it = Result.begin();
			for( ; it != Result.end(); it++) {
				uint32_t uiSite = it->first;
				map<string, double>& mapSite = Result[uiSite];
				map<string, double>::iterator itSite = mapSite.begin();
				for( ; itSite != mapSite.end(); itSite++)
				{
					string strPinName = itSite->first;
					double dFrequency = itSite->second;
					mapTemp[strPinName][uiSite] = dFrequency;
				}
			}
			PinArrayDouble pinarraydata;
			map<string, map<int, double> >::iterator ite = mapTemp.begin();
			for( ; ite != mapTemp.end(); ite++) {
				string strPinName = ite->first;
				map<int, double> mapValue = ite->second;
				pinarraydata.AddPinData(strPinName, mapValue);
				pinarraydata.ShowPinArrayData();
				TheSoft.Flow().TestLimit(strPinName,pinarraydata);
			}
#else
			map<string, map<uint32_t, double> > Result;
			int iRet = Frequency_Counter(freq_pinlist, 1.2e-3, Result);
			if(iRet != 0) {
				cout <<"[ERROR] Frequency counter test failed." << endl;
				return;
			}
			map<string, map<uint32_t, double> >::iterator it = Result.begin();
			PinArrayDouble pinarraydata;
			for( ; it != Result.end(); it++) {
				string strPinName = it->first;
				map<int, double> mapTemp;
				map<uint32_t, double> mapPin = Result[strPinName];
				map<uint32_t, double>::iterator itTemp = mapPin.begin();
				for( ; itTemp != mapPin.end(); itTemp++) {
					int nSite = itTemp->first;
					double dFrequency = itTemp->second;
					mapTemp[nSite] = dFrequency;
				}
				pinarraydata.AddPinData(strPinName, mapTemp);
				pinarraydata.ShowPinArrayData();
				TheSoft.Flow().TestLimit(strPinName,pinarraydata);
			}
#endif

//		std::vector<std::string> vec_FREQpinlist = PinTool::SplitPinList(freq_pinlist);
//		for(int i =0; i<vec_FREQpinlist.size(); i++){
//		    int CapDspWave[360000]={0};
//		    auto capData = TheInst.Digital().PatEng().GetCaptureData(vec_FREQpinlist[i]);
//
//			    for(auto siteData : capData){
//			    	cout<<"\n\nSite Number : " << siteData.first<<endl;
//			    	for(auto pinData : siteData.second){
//			    		cout<<"\nPin Name : " << pinData.first<<endl;
//			    		int i=0;
//
//			    		for(auto data : pinData.second){
//			    			CapDspWave[i] = data.iECResult;
//			    			i++;
//	//		    			cout << data.iECResult;
//	//		    			if(i % 200 == 0){
//	//		    				cout << endl;
//	//		    			}
//			    		}
//			    		cout << endl;
//			    	}
//			    }
//
//			double FT = 0.0;
//
//			cout<<"\nPin Name : " << vec_FREQpinlist[i] <<endl;
//			Cal_Frequency_oversampling(100,CapDspWave,360000, FT, 20000);
//			PinArrayDouble pinarraydata;
//			pinarraydata.AddPinData(vec_FREQpinlist[i],FT);
//			pinarraydata.ShowPinArrayData();
//			TheSoft.Flow().TestLimit(vec_FREQpinlist[i],pinarraydata);
//		}
//		TheSoft.Flow().Timing().SetTiming(TimingName);
//		TheInst.Digital().Timing().Apply();
//		TheSoft.Flow().Pattern().SetPattern(PatternName);


        TheInst.GIFA().SetSingleEndMode();
        TheInst.Wait(1*ms);
        TheInst.GIFA().SetClkFreq(40);
        TheInst.GIFA().SetChannel(0xff);
        TheInst.GIFA().Start();

        TheInst.Wait(10*ms);

		for(int i=0;i<4;i++)
		{
			TheInst.Util().SetRelayState(UBIT[i],PhxAPI:: E_UTIL_STATE_OFF);
		}
//		TheInst.Wait(4*ms);

    }

};


REGISTER_TESTCLASS("CMU_CRYSTAL_DFT",CMU_CRYSTAL_DFT)

