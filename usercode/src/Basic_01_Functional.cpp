/*
 * Basic_02_Functional.cpp
 *
 *  Created on: 2021年7月14日    --based on 1.0.2.4
 */




#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include <map>

using namespace std;
using namespace PinTool;

class Basic_01_Functional: public TestClass {
public:
	void init() {

	            }
	void execute() {
						cout << "!!!Hello Basic_01_Functional!!!" << endl;
						TheInst.DCVS().Power().Apply();
						TheInst.Digital().Level().Apply();
						TheInst.Digital().Timing().Apply();
						TheInst.Digital().PatEng().SetupMCFData();
						TheInst.Digital().PatEng().SetFailMode(PhxAPI::E_SET_HIL_MODE);
						TheInst.Digital().Pattern().Run();
						map<uint32_t, bool> result = TheInst.Digital().PatEng().GetPassFail();
//						for(auto it = result.begin(); it != result.end(); it++)
//						{
//						  cout<<"get pass/fail:"<< it->second<<endl;
//						}
						  uint64_t executedcount=TheInst.Digital().PatEng().GetExecutedCyclesCount();
						  cout<<dec;
//						  cout<<"executedcount (dec) :"<<executedcount<<endl;
						  std::string testname = TheSoft.Flow().Test().GetCurrentTestName();
//						  cout<<"*******testname is********"<<testname<<endl;
						  if(testname == "PCIE_PREEM_EXT_5G")
						  {
							  TheInst.Digital().Timing("").StopFreeRunningClock();
							  TheInst.Digital().Timing("").Apply();
//							  double freq_result = Cymomer_Read_Freq_Hz(100);
//							  if(freq_result > 900000) freq_result = 0;
						  }
					    }

};


REGISTER_TESTCLASS("Basic_01_Functional", Basic_01_Functional)
