//
// Created by f.he on 2021/6/18.
//

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include "Globle_Var.h"
#include "GetLog.h"
#include "readlimit.h"

class PRE_TRIM_SUM: public TestClass{
public:


    void init(){

    }

    void execute(){
    	double hil[30],lowl[30];
		char *Test_Item[30],*Units[30];
		int  Test_number[30];
		Read_Limit(lowl,hil,Test_Item,Test_number,Units);

		long Cycle =200;

		double PreVrefMax=0;
		double PreBuckMax=0;
		double PreIrefMax=0;

		double PreVrefMin=10;
		double PreBuckMin=10;
		double PreIrefMin=10;

		double PreVrefDiff;
		double PreBuckDiff;
		double PreIrefDiff;

		long count_flag;

		FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
			//int index = api->Get_active_site();

			///////////////////////////////
			//loss judge bin1 branch and print production mode
			if(HBIN_FLAG[index] == 0)
			{
				TEST_COUNT[index] = TEST_COUNT[index]+1;

				if(TEST_COUNT[index]<Cycle)
				{
					count_flag = 0;
					PRE_VREF_TRIM_SUM[index] = PRE_VREF_TRIM_SUM[index] + PRE_VREF_TRIM[index];
					PRE_BUCK_TRIM_SUM[index] = PRE_BUCK_TRIM_SUM[index] + PRE_BUCK_TRIM[index];
					PRE_IREF_TRIM_SUM[index] = PRE_IREF_TRIM_SUM[index] + PRE_IREF_TRIM[index];

					PreVrefAve[index]=PRE_VREF_TRIM_SUM[index]/TEST_COUNT[index];
					PreBuckAve[index]=PRE_BUCK_TRIM_SUM[index]/TEST_COUNT[index];
					PreIrefAve[index]=PRE_IREF_TRIM_SUM[index]/TEST_COUNT[index];

					PRE_VREF_ARRAY.SetElement(index,TEST_COUNT[index],PRE_VREF_TRIM[index]);
					PRE_BUCK_ARRAY.SetElement(index,TEST_COUNT[index],PRE_BUCK_TRIM[index]);
					PRE_IREF_ARRAY.SetElement(index,TEST_COUNT[index],PRE_IREF_TRIM[index]);
				}
				else if(TEST_COUNT[index]>=Cycle&&TEST_COUNT[index]%Cycle!=0)
				{
					count_flag = 1;
					int i = TEST_COUNT[index]%Cycle;

					PRE_VREF_TRIM_SUM[index]=PRE_VREF_TRIM_SUM[index]-PRE_VREF_ARRAY(index,i)+PRE_VREF_TRIM[index];
					PRE_BUCK_TRIM_SUM[index]=PRE_BUCK_TRIM_SUM[index]-PRE_BUCK_ARRAY(index,i)+PRE_BUCK_TRIM[index];
					PRE_IREF_TRIM_SUM[index]=PRE_IREF_TRIM_SUM[index]-PRE_IREF_ARRAY(index,i)+PRE_IREF_TRIM[index];

					PreVrefAve[index]=PRE_VREF_TRIM_SUM[index]/Cycle;
					PreBuckAve[index]=PRE_BUCK_TRIM_SUM[index]/Cycle;
					PreIrefAve[index]=PRE_IREF_TRIM_SUM[index]/Cycle;

					PRE_VREF_ARRAY.SetElement(index,i,PRE_VREF_TRIM[index]);
					PRE_BUCK_ARRAY.SetElement(index,i,PRE_BUCK_TRIM[index]);
					PRE_IREF_ARRAY.SetElement(index,i,PRE_IREF_TRIM[index]);

				}
				else if(TEST_COUNT[index]>=Cycle&&TEST_COUNT[index]%Cycle==0)
				{
					count_flag = 1;

					PRE_VREF_TRIM_SUM[index]=PRE_VREF_TRIM_SUM[index]-PRE_VREF_ARRAY(index,0)+PRE_VREF_TRIM[index];
					PRE_BUCK_TRIM_SUM[index]=PRE_BUCK_TRIM_SUM[index]-PRE_BUCK_ARRAY(index,0)+PRE_BUCK_TRIM[index];
					PRE_IREF_TRIM_SUM[index]=PRE_IREF_TRIM_SUM[index]-PRE_IREF_ARRAY(index,0)+PRE_IREF_TRIM[index];

					PreVrefAve[index]=PRE_VREF_TRIM_SUM[index]/Cycle;
					PreBuckAve[index]=PRE_BUCK_TRIM_SUM[index]/Cycle;
					PreIrefAve[index]=PRE_IREF_TRIM_SUM[index]/Cycle;

					PRE_VREF_ARRAY.SetElement(index,0,PRE_VREF_TRIM[index]);
					PRE_BUCK_ARRAY.SetElement(index,0,PRE_BUCK_TRIM[index]);
					PRE_IREF_ARRAY.SetElement(index,0,PRE_IREF_TRIM[index]);
				}

				if(PreVrefAve[index]>PreVrefMax)
				{
					PreVrefMax=PreVrefAve[index];
				}
				if(PreVrefAve[index]<PreVrefMin)
				{
					PreVrefMin=PreVrefAve[index];
				}
				if(PreBuckAve[index]>PreBuckMax)
				{
					PreBuckMax=PreBuckAve[index];
				}
				if(PreBuckAve[index]<PreBuckMin)
				{
					PreBuckMin=PreBuckAve[index];
				}
				if(PreIrefAve[index]>PreIrefMax)
				{
					PreIrefMax=PreIrefAve[index];
				}
				if(PreIrefAve[index]<PreIrefMin)
				{
					PreIrefMin=PreIrefAve[index];
				}

				ValueTest (index, "PMU_REFBP", PreVrefAve[index], lowl[0], hil[0], "V", Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
				ValueTest (index, "VDD_BUCK_1V5_IN", PreBuckAve[index], lowl[1], hil[1], "V", Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
				ValueTest (index, "PMU_RBIAS", PreIrefAve[index], lowl[2], hil[2], "V", Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);

				ValueTest (index, "", TEST_COUNT[index], lowl[3], hil[3], "", Test_Item[3], "FAIL_BIN", Test_number[3], Clogenable);

			}
			else
			{
				if(TEST_COUNT[index] < 1)
				{
					count_flag = 0;
					TEST_COUNT[index] = 0;
					PreVrefAve[index] = 0;
					PreBuckAve[index] = 0;
					PreIrefAve[index] = 0;
				}
				else if(TEST_COUNT[index] < Cycle)
				{
					count_flag = 0;
					TEST_COUNT[index] = TEST_COUNT[index];
					PreVrefAve[index] = PreVrefAve[index];
					PreBuckAve[index] = PreBuckAve[index];
					PreIrefAve[index] = PreIrefAve[index];
				}
				else if(TEST_COUNT[index]>=Cycle)
				{
					count_flag = 1;
					TEST_COUNT[index] = TEST_COUNT[index];
					PreVrefAve[index] = PreVrefAve[index];
					PreBuckAve[index] = PreBuckAve[index];
					PreIrefAve[index] = PreIrefAve[index];
				}

			}
		FOREACH_ACTIVESITE_END

		PreVrefDiff = PreVrefMax - PreVrefMin;
		PreBuckDiff = PreBuckMax - PreBuckMin;
		PreIrefDiff = PreIrefMax - PreIrefMin;

		FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
			ValueTest (index, "", PreVrefDiff, lowl[4], hil[4], "V", Test_Item[4], "FAIL_BIN", Test_number[4], Clogenable);
			ValueTest (index, "", PreBuckDiff, lowl[5], hil[5], "V", Test_Item[5], "FAIL_BIN", Test_number[5], Clogenable);
			ValueTest (index, "", PreIrefDiff, lowl[6], hil[6], "V", Test_Item[6], "FAIL_BIN", Test_number[6], Clogenable);

			if(count_flag==0)
			{
				ValueTest (index, "", 0.000001, lowl[7], hil[7], "V", Test_Item[7], "FAIL_BIN", Test_number[7], Clogenable);
				ValueTest (index, "", 0.000001, lowl[8], hil[8], "V", Test_Item[8], "FAIL_BIN", Test_number[8], Clogenable);
				ValueTest (index, "", 0.000001, lowl[9], hil[9], "V", Test_Item[9], "FAIL_BIN", Test_number[9], Clogenable);
			}
			else
			{
				ValueTest (index, "", PreVrefDiff, lowl[7], hil[7], "V", Test_Item[7], "FAIL_BIN", Test_number[7], Clogenable);
				ValueTest (index, "", PreBuckDiff, lowl[8], hil[8], "V", Test_Item[8], "FAIL_BIN", Test_number[8], Clogenable);
				ValueTest (index, "", PreIrefDiff, lowl[9], hil[9], "V", Test_Item[9], "FAIL_BIN", Test_number[9], Clogenable);
			}
		FOREACH_ACTIVESITE_END


    }
};



REGISTER_TESTCLASS("PRE_TRIM_SUM",PRE_TRIM_SUM)

