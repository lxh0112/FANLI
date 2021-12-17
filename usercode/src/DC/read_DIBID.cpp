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
#include "UserDef.h"
#include "Globle_Var.h"


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
        vector<string> Test_Item;
		vector<string> Units;
		int  Test_number[MAX_PATH_LOSS_ITEM] = {0};
        int Soft_Bin[30];
		int Hard_Bin[30];
		Read_Limit(lowl,hil,Test_Item,Test_number,Units,Soft_Bin,Hard_Bin);

		int i = 0;
		int nIndex = 0;
		tyTestData testRecord;

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
		                if(!stricmp(szCurrentName, Test_Item[n].c_str()))
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
								TheSoft.Flow().TestLimit("",site_id,testRecord.plInfo.plLossArray[site_id], lowl[nIndex], hil[nIndex],2,2300, "dB", Test_Item[nIndex], Test_number[nIndex]);
				            else
				            	TheSoft.Flow().TestLimit("",site_id, 0, 999, 999,2,2300, "dB", szCurrentName,Test_number[0]);
		        	FOREACH_ACTIVESITE_END
		            szPreviousNameMap.insert(std::pair<std::string,std::string>(szCurrentName,szCurrentName));
		        }
		    }

	}
};
REGISTER_TESTCLASS("readDIBID", readDIBID)
