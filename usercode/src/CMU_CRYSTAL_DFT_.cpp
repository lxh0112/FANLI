/*
 * .cpp
 *
 *  Created on: 2021年8月30日
 *      Author: 荣耀
 */


///#include <d2sProtocolSSI.h>
#include "TestClass.h"
#include <UserAPI.h>
//#include "Capture_Function.h"

class CMU_CRYSTAL_DFT: public TestClass{
public:
//	 uint32_t UBIT[4];
	std::string dc_pinlist;
	std::string freq_pinlist;
    void init(){
//    	add_param( "DC_pinlist",  "string", &dc_pinlist).set_default("ROC_INT0");
//    	add_param( "FREQ_pinlist",  "string", &freq_pinlist).set_default("UART_TXD");//
    }
//    void execute(){
//
//    	 uint32_t UBIT[4] = {10,01,12,47};
//
//    	TheInst.Util().SetUserPower(PhxAPI::E_USERPW_P5V, PhxAPI::E_UTIL_STATE_ON);
//    	TheInst.Wait(5*s);
//    	for(uint32_t j=0;j<256;j++)
//    			{
//    				TheInst.Util().SetRelayState(j, PhxAPI::E_UTIL_STATE_OFF); //bihe-0,duankai-1
//    				TheInst.Wait(4*us);//us
//    			}
//
//    	 for(int i=0;i<4;i++)
//    	 		{
//    	 			TheInst.Util().SetRelayState(UBIT[i],PhxAPI:: E_UTIL_STATE_ON);
//    	 			TheInst.Wait(4*us);
//    	 		}
//    	 //relay
//
//
//        TheInst.DCVS().Power().Apply();
//        TheInst.Digital().Level().Apply();
////        TheInst.Digital().Timing("").SetFreeRunningClock("XIN", 2.5e-8);
//        TheInst.Digital().Timing().Apply();
//    	TheInst.Digital().Pattern().Start();
//
//#if 0
//		string TimingName = TheSoft.Flow().Timing().GetCurrentTimingBlockName();
//		string PatternName = TheSoft.Flow().Pattern().GetCurrentPatternName();
//		TheSoft.Flow().Timing().SetTiming("PLL_TIM5_V1");
//		TheInst.Digital().Timing().Apply();
//		TheSoft.Flow().Pattern().SetPattern("PLL_CRYSTAL_PLL2DBB_320M_R03_Hi1151V200");
//		TheInst.Digital().Pattern().Start();
//
//		map<uint32_t, map<string, vector<uint8_t> > > CAP_Data = TheInst.Digital().PatEng().GetCaptureRawData("DBB_GPIO0");
//		map<string, vector<uint8_t> > data;
//		vector<uint8_t> data_ECC;
//		int CapDspWave[10000];
//
//		if(CAP_Data.size() > 0U)
//		{
//			for(auto it = CAP_Data.begin(); it != CAP_Data.end(); it++)
//			{
//				cout<<"\n\nSite Number : " << dec << it->first<<endl;
//				data = it->second;
//
//				for(auto pit = data.begin(); pit != data.end(); pit++)
//				{
//					cout<<"\nPin Name : " <<  (pit->first)<<endl;
//					data_ECC = (pit->second);
//				}
//			}
//			cout<< "capture size: " << data.size() <<endl;
////			for(int i = 0; i < data_ECC.size(); i++)
////			{
////				CapDspWave[i] = (int)(((data_ECC[i])>>2U)&(0x3U));
//////				CapDspWave[i] = (CapDspWave[i])&0x3;
//////						cout<<"\ncapture data is : " << CapDspWave[i] <<endl;
////			}
//////			for(int i=8600;i<8800;i++){
//////				cout<< CapDspWave[i] <<"\n"<<endl;
//////			}
//
//			for(int i = 0; i < data_ECC.size(); i++)
//			{
//				CapDspWave[i] = (int)(((data_ECC[i])>>2U)&(0x3U));
////				CapDspWave[i] = 1;
//				if(CapDspWave[i] == 3)
//				{
//					CapDspWave[i] = 0;
//				}
//	//				CapDspWave[i] = (CapDspWave[i])&0x3;
//	//						cout<<"\ncapture data is : " << CapDspWave[i] <<endl;
//			}
//		}
//
//
//		else
//		{
//			cout<<"\n\nThere's no capture data !"<<endl;
//		}
//
//		for(int i=0;i< 10000 ;i++){
//			cout<< CapDspWave[i]<<" ";
//			if(i%100 == 0 && i>0) cout<<endl;
//		}
//		cout<<endl;
//		double FT = 0.0;
////
//		Cal_Frequency_Undersampling(38.36,CapDspWave,959, FT);
//
//		TheSoft.Flow().Timing().SetTiming(TimingName);
//		TheSoft.Flow().Pattern().SetPattern(PatternName);
//
////		 CCRFTester.CHANNEL("XIN").setClkFreq(40);
////		   CCRFTester.CHANNEL("XIN").Start();
//
//		TheInst.Util().SetUserPower(PhxAPI::E_USERPW_P5V, PhxAPI::E_UTIL_STATE_OFF);
//	        	TheInst.Wait(20*ms);//sleep(0.02)
//	}
//
//#endif
//
//
};
REGISTER_TESTCLASS("CMU_CRYSTAL_DFT",CMU_CRYSTAL_DFT)

