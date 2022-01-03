/*
 * CMU_TCXO_SSI.cpp
 *
 *  Created on: 2021年7月14日    --based on 1.0.2.4
 */

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include <map>
#include "d2sProtocolSSI.h"
#include "D2S_PMU_Module.h"
#include "Globle_Var.h"
#include "GetLog.h"
#include "Capture_Function.h"
#include <math.h>
#include <fstream>
#include "UserDef.h"


using namespace std;
using namespace PinTool;

#define ORG 0

//static void WriteData(const char* pszFileName,int dData[],long lDataSize)
//{
//	char szPath[64] = {0};
//	sprintf(szPath,"%s.txt",pszFileName);
//	ofstream fout(szPath);
//	for(long i = 0;i<lDataSize;i++)
//	{
//		fout << dData[i] << endl;
//	}
//	fout.close();
//}

class CMU_TCXO_SSI: public TestClass {
public:
		std::string freq_pinlist;
		std::string timingname;
		std::string patternname;
		double fs_freq;
		int num;

	    void init(){
	    	add_param( "FREQ_pinlist",  "string", &freq_pinlist);
	    }

#if 1
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
#endif
	    void execute() {
#if 1

	    double hil[30] = {0.0}, lowl[30] = {0.0};
	    vector<string> Test_Item;
	    vector<string> Units;
	    Test_Item.clear();
	    Units.clear();
	    int Test_number[30] = {0},Soft_Bin[30],Hard_Bin[30];
	    Read_Limit(lowl, hil, Test_Item, Test_number, Units, Soft_Bin,Hard_Bin);

		TheInst.DCVI().Power().Apply(); //下发执行  DCVI  power pin上电
		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
		TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing
//		TheInst.Digital().Pattern().Start();

		CMU_Module();

	    double *GetValue1;
	    double *GetValue2;
	    map<int, double> vMeas1;
	    map<int, double> vMeas2;

	    long muxRegs[4]={0xA91,0xCB1,0x631,0x871};
//		string TimingName = TheSoft.Flow().Timing().GetCurrentTimingBlockName();
//		string PatternName = TheSoft.Flow().Pattern().GetCurrentPatternName();

	    for(int i=0;i<2;i++){
			d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
			d2sProtocolSSI d2s_test;
			d2s_test.SSI_write(0x200,0x2000,false);
			d2s_test.SSI_write(0x202,0x0,false);
			d2s_test.SSI_write(0x12c,0x6000);
			d2s_test.SSI_write(0x158,0x6);
			d2s_test.SSI_write(0x244,muxRegs[i]);
			d2s_test.wait(0.0001);

			d2s_test.SSI_write(0x200,0x2000,false);
			d2s_test.SSI_write(0x202,0x40,false);
			d2s_test.SSI_read(0x330,"readdata",9);
			d2s::d2s_LABEL_END();

			map<int, long long>capture_data;
			capture_data = d2s_test.getReadValue("readdata");

			for(auto it = capture_data.begin(); it != capture_data.end(); it++)
			{
				cout<<"capture_data :"<< it->second << endl;
				long long X = (it->second | 0x4) >> 2;
				cout << X <<endl;
			}

#if 1
//			TheSoft.Flow().Timing().SetTiming("Capture_PLL");
//			TheInst.Digital().Timing().Apply();
//			TheSoft.Flow().Pattern().SetPattern("Capture_PLL");
//			TheInst.Digital().Pattern().Start();

#if ORG
			map<uint32_t, map<string, double> > Result;
			int iRet = Frequency_Counter(freq_pinlist, 1.2e-3, Result);
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

//			std::vector<std::string> vec_FREQpinlist = PinTool::SplitPinList(freq_pinlist);
//			for(int j =0; j<vec_FREQpinlist.size(); j++){
//				map<uint32_t, map<string, double> > Result;
//				int iRet = Frequency_Counter(freq_pinlist, 1.2e-3, Result);
//				if(iRet != 0) {
//					cout <<"[ERROR] Frequency counter test failed." << endl;
//					return;
//				}
//				map<uint32_t, map<string, double> >::iterator itSite = Result.begin();
//				int num = 0;
//				PinArrayDouble pinarraydata;
//				for( ; itSite != Result.end(); itSite++) {
//					uint32_t uiSite = itSite->first;
//					map<string, double>& mapSite = Result[uiSite];
//					map<string, double>::iterator itPin = mapSite.begin();
//					string strPinName = "";
//					for( ; itPin != mapSite.end(); itPin++) {
//						strPinName = itPin->first;
//						double& dFrequency = mapSite[strPinName];
//						//PinArrayDouble pinarraydata;
//						pinarraydata.AddPinData(strPinName, dFrequency);
//						pinarraydata.ShowPinArrayData();
//						//TheSoft.Flow().TestLimit(strPinName,pinarraydata);
//					}
//					num++;
//					string strtestname = TheSoft.Flow().GetCurrentFlowTestOperand();
//					cout<<"\t num:"<<num<<"Testname:"<<strtestname<<endl;
//
//				}
//				TheSoft.Flow().TestLimit(strPinName,pinarraydata);
//
//
//				map<string, map<uint32_t, double> > Result;
//				map<string, map<uint32_t, double> >::iterator it = Result.begin();
//				for( ; it != Result.end(); it++) {
//					string strPinName = it->first();
//					map<uint32_t, double> map1;
//					pinarraydata.AddPinData(strPinName, map1);
//					pinarraydata.ShowPinArrayData();
//					TheSoft.Flow().TestLimit(strPinName,pinarraydata);
//				}
//			}

//			std::vector<std::string> vec_FREQpinlist = PinTool::SplitPinList(freq_pinlist);
//			for(int i =0; i<vec_FREQpinlist.size(); i++){
//			    int CapDspWave[360000]={0};
//			    auto capData = TheInst.Digital().PatEng().GetCaptureData(vec_FREQpinlist[i]);
//
//				    for(auto siteData : capData){
//				    	cout<<"\n\nSite Number : " << siteData.first<<endl;
//				    	for(auto pinData : siteData.second){
//				    		cout<<"\nPin Name : " << pinData.first<<endl;
//				    		int i=0;
//
//				    		for(auto data : pinData.second){
//				    			CapDspWave[i] = data.iECResult;
//				    			i++;
//		//		    			cout << data.iECResult;
//		//		    			if(i % 200 == 0){
//		//		    				cout << endl;
//		//		    			}
//				    		}
//				    		cout << endl;
//				    	}
//				    }
//
//				double FT = 0.0;
//
//				cout<<"\nPin Name : " << vec_FREQpinlist[i] <<endl;
//				Cal_Frequency_oversampling(100,CapDspWave,360000, FT, 20000);
//				PinArrayDouble pinarraydata;
//				pinarraydata.AddPinData(vec_FREQpinlist[i],FT);
//				pinarraydata.ShowPinArrayData();
//				TheSoft.Flow().TestLimit(vec_FREQpinlist[i],pinarraydata);
//			}
//			TheSoft.Flow().Timing().SetTiming(TimingName);
//			TheInst.Digital().Timing().Apply();
//			TheSoft.Flow().Pattern().SetPattern(PatternName);
			//TheInst.Digital().Timing().Apply();
#endif
		}
		d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
		d2sProtocolSSI d2s_test;
		d2s_test.SSI_write(0x200,0x2000,false);
		d2s_test.SSI_write(0x202,0x0,false);
		d2s_test.SSI_write(0x244,0x0);
		d2s_test.SSI_write(0x12c,0x0);
		d2s_test.SSI_write(0x158,0x0);
		d2s::d2s_LABEL_END();
#endif
	}

};
REGISTER_TESTCLASS("CMU_TCXO_SSI", CMU_TCXO_SSI)



















