
#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
//#include "D2S_CAL_Module.h"
//#include "Globle_Var.h"
#include "CCS08F.h"
#include "Excel.h"
#include "RegDef.h"
#include "d2sProtocolSSI.h"
#include "UserDef.h"
#include "D2S_PMU_Module.h"
#include "Test_TX_cpp.h"

using namespace PhxAPI;

class PLL_Sweep_vbt: public TestClass {
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


		CSiteLong SiteData;
		//    long long Dataarray[146];
		long sweep_size;
		long sweep_step;
		double startFreq;
		double stopFreq;
		double stepFreq;

		double bandError;
		long first_band_value;
		long last_band_value;
		long max_pll_State;
		long min_pll_State;

		string testname = TheSoft.Flow().Test().GetCurrentTestName();
		if (strstr(testname.c_str(), "2G") != NULL) {
			startFreq = 2412e6;
			stopFreq = 2484e6;
			stepFreq = 1e6;
			sweep_step = (stopFreq - startFreq) / stepFreq + 1;
			WL_2G_PLL_Sweep_Module(&SiteData);
			//sweep_step = ?;
		} else {
			startFreq = 4920e6;
			stopFreq = 5824e6;
			stepFreq = 2e6;
			sweep_step = (stopFreq - startFreq) / stepFreq + 1;
			WL_5G_PLL_Sweep_Module(&SiteData);
			//sweep_step = ?;
		}

		sweep_size = sweep_step * 2;
		long long *Dataarray = new long long[sweep_size];

		FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
		int site_id = index;
			for(int m = 0;m<sweep_size;m++)
			{
				Dataarray[m] = SiteData(site_id,m);
			}
			calc_PLL_Sweep(site_id,Dataarray,sweep_step,&bandError,&first_band_value,&last_band_value,&max_pll_State,&min_pll_State);

			TheSoft.Flow().TestLimit("SSI_DATA",site_id, bandError, lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], Units[0], Test_Item[0],Test_number[0],PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE);
			TheSoft.Flow().TestLimit("SSI_DATA",site_id, (int)first_band_value, lowl[1], hil[1],Hard_Bin[1],Soft_Bin[1], Units[1], Test_Item[1],Test_number[1],PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE);
			TheSoft.Flow().TestLimit("SSI_DATA",site_id, (int)last_band_value, lowl[2], hil[2],Hard_Bin[2],Soft_Bin[2], Units[2], Test_Item[2],Test_number[2],PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE);
			TheSoft.Flow().TestLimit("SSI_DATA",site_id, (int)max_pll_State, lowl[3], hil[3],Hard_Bin[3],Soft_Bin[3], Units[3], Test_Item[3],Test_number[3],PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE);
			TheSoft.Flow().TestLimit("SSI_DATA",site_id, (int)min_pll_State, lowl[4], hil[4],Hard_Bin[4],Soft_Bin[4], Units[4], Test_Item[4],Test_number[4],PhxAPI::E_Fail,PhxAPI::E_LEFTCLOSE_RIGHTCLOSE);

		FOREACH_ACTIVESITE_END
		delete[] Dataarray;

	}
};
REGISTER_TESTCLASS("PLL_Sweep_vbt", PLL_Sweep_vbt)

