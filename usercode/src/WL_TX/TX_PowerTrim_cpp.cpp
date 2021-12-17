#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include "CCS08F.h"
#include "Excel.h"
#include "RegDef.h"
#include "d2sProtocolSSI.h"
#include "UserDef.h"
#include "Test_TX_cpp.h"
#include <fstream>

using namespace PhxAPI;

//static void WriteData(const char* pszFileName,float dData[],long lDataSize)
//{
//	char szPath[64] = {0};
//	sprintf(szPath,"%s.txt",pszFileName);
//	ofstream fout(szPath);
////	fout.seekp(ios::end);
//	for(long i = 0;i<lDataSize;i++)
//	{
//		fout << dData[i] << endl;
//	}
//	fout.close();
//}

class TX_PowerTrim_cpp: public TestClass {
public:

	void init() {

	}

	void execute() {

//		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
//		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
		TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing

		double hil[30], lowl[30];
//		char *Test_Item[30], *Units[30];
		vector<string> Test_Item;
		vector<string> Units;
		int Test_number[30];

		int Soft_Bin[30];
		int Hard_Bin[30];
		Read_Limit(lowl,hil,Test_Item,Test_number,Units,Soft_Bin,Hard_Bin);
		//Parameter definition here
		tyTestData RF_Test_Data;
		char Ana_SrcPin[_MAX_NAME_SIZE_RF] = { "\0" };
		char RF_CapPin[_MAX_NAME_SIZE_RF] = { "\0" };
		char Ana_Src_Signal[_MAX_NAME_SIZE_RF] = { "\0" };
		char RF_Cap_Signal[_MAX_NAME_SIZE_RF] = { "\0" };

		long Exp_Bin = 0;
		volatile double Exp_Freq = 0;
		double pathloss[4];

		CCRfmxSpecAnResults mxSpecAnResults;
		SpecAnResultAttribute ResultAttribute;
		double Pre_Output_Power[4] = { 0 };
		int TrimData[4] = { 0 };

		//1. Get test item information
		string testname = TheSoft.Flow().Test().GetCurrentTestName();
        Get_TestItem_Info(testname.c_str(), RF_Test_Data);
        Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
        Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);
        Exp_Freq = selectFrequency(RF_Test_Data.cRxFreq) + RF_Test_Data.tyTXTest.dFreqSpacing;

		//2. Get Passloss
        Read_Pathloss(RF_Test_Data,pathloss);

		//3. Measre pre Power
		//3.1  DUT register setting: cal code, PLL, gain
		Set_RF_TX_Pll_BW((emMode) RF_Test_Data.iMode,(emTX_Band) RF_Test_Data.iBand, RF_Test_Data.dBW,RF_Test_Data.cChannel);

		CCRFTester.SelectSites("site0,site2");
        SrcUtilitySites0();
		//3.2  Load source and capture signal
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();

		//3.3  Trigger capture signal, get wave, calculate power
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(
				&mxSpecAnResults);

		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
#ifdef semi_parallel_en
		CCRFTester.SelectSites("site1,site3");
        SrcUtilitySites1();
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();

		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
		//3.3  Trigger capture signal, get wave, calculate power
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(
				&mxSpecAnResults);

		CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
		CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
        SrcUtilitySites0();                                                      //recover Relay state
#endif
		FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
			int site_id = index;
			ResultAttribute = mxSpecAnResults[site_id];
			if(ResultAttribute.dwNumbersOfSpectrum > 0)
			{
				Exp_Bin = int((Exp_Freq - ResultAttribute.dInitiaFrequency)/ResultAttribute.dFrequencyIncrement);
				// Debug
//				WriteData(RF_Cap_Signal,ResultAttribute.pPowerDataBuf,ResultAttribute.dwNumbersOfPower);

				Calc_Power_dbm(&ResultAttribute,Exp_Bin,5,&Pre_Output_Power[site_id],pathloss[site_id]);
			}
		FOREACH_ACTIVESITE_END

		//4. Calculate trim code
		TX_Power_Trim_Function((emMode) RF_Test_Data.iMode,(emTX_Band) RF_Test_Data.iBand, RF_Test_Data.cChannel,Pre_Output_Power, TrimData);

		//5. Output test result
		FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
			int site_id = index;
			if(strstr(testname.c_str() , "C0")!=NULL) {
				TRIM_DATA_LIST_C0[RF_Test_Data.iBand-10][site_id] = TrimData[site_id];
			}
			else {
				TRIM_DATA_LIST_C1[RF_Test_Data.iBand-10][site_id] = TrimData[site_id];
			}
			TheSoft.Flow().TestLimit(RF_CapPin,site_id, Pre_Output_Power[site_id], lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0] ,Units[0], Test_Item[0], Test_number[0]);
			TheSoft.Flow().TestLimit(RF_CapPin,site_id, TrimData[site_id], lowl[1], hil[1],Hard_Bin[1],Soft_Bin[1], Units[1], Test_Item[1], Test_number[1]);
		FOREACH_ACTIVESITE_END

	}
};
REGISTER_TESTCLASS("TX_PowerTrim_cpp", TX_PowerTrim_cpp)

