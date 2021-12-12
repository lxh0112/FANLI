/*
 * 	readDIBID
 *
 *  Created on: 2021年8月16日    --based on 1.0.2.4
 */

#include "Excel.h"
#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include <map>
#include"readlimit.h"
#include"Getlog.h"

using namespace std;
using namespace PinTool;

class readDIBID: public TestClass {
public:

	void init() {

	}

	void execute() {
//    	TheSoft.Message().InfoMessage("readDIBID");

		TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
		TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level

		#define MAX_PATH_LOSS_ITEM     (40)
		double hil[MAX_PATH_LOSS_ITEM] = {0}, lowl[MAX_PATH_LOSS_ITEM] = {0};
		char *Test_Item[MAX_PATH_LOSS_ITEM] = {0}, *Units[MAX_PATH_LOSS_ITEM] = {0};
		int  Test_number[MAX_PATH_LOSS_ITEM] = {0};
		Read_Limit(lowl, hil, Test_Item, Test_number, Units);

		int i = 0;
		int nIndex = 0;
		tyTestData testRecord;

		tyTestDatas AllTabelData;
		char szCurrentName[64] = {0};
		std::map<std::string,std::string> szPreviousNameMap;
		szPreviousNameMap.clear();

		for(i = 0; i < AllTabelData.lDataLength; i++)
		    {
		        testRecord = AllTabelData.testData[i];
		        memset(szCurrentName,0x00,sizeof(szCurrentName));
		        if(testRecord.plInfo.plMode&&testRecord.plInfo.plPath&&testRecord.plInfo.plBand&&testRecord.plInfo.plChannel)
		        {
		            sprintf(szCurrentName,"%s_%s_%s_%s",\
		                    testRecord.plInfo.plMode,\
		                    testRecord.plInfo.plPath,\
		                    testRecord.plInfo.plBand,\
		                    testRecord.plInfo.plChannel);
		            nIndex = -1;
		            for(int n = 0; n < MAX_PATH_LOSS_ITEM; n++)
		            {
		                if(!stricmp(szCurrentName, Test_Item[n]))
		                {
		                    nIndex = n;
		                    break;
		                }
		            }
		        }
		        if((szPreviousNameMap.find(szCurrentName) == szPreviousNameMap.end())&&(stricmp(szCurrentName,"")))
		        {
		        	FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
							if((nIndex >= 0)&&(nIndex < MAX_PATH_LOSS_ITEM))
				                ValueTest (site_id, "", testRecord.plInfo.plLossArray[site_id], lowl[nIndex], hil[nIndex], "dB", Test_Item[nIndex], "FAIL_BIN", Test_number[nIndex], Clogenable);
				            else
				                ValueTest (site_id, "", 0, 999, 999, "dB", szCurrentName, "FAIL_BIN", Test_number[0], Clogenable);
		        	FOREACH_ACTIVESITE_END
		            szPreviousNameMap.insert(std::pair<std::string,std::string>(szCurrentName,szCurrentName));
		        }
		    }

	}
};
REGISTER_TESTCLASS("readDIBID", readDIBID)
