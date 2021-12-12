/*
 * readlimit.cpp
 *
 *  Created on: 2021年8月23日
 *      Author: 荣耀
 */

#include"readlimit.h"
#include "Globle_Var.h"
#include "TestClass.h"
#include <iostream>
#include <string>
#include "UserAPI.h"
#include <math.h>


void Read_Limit(double *Lowlimit,double *Highlimit,char* Test_name[],int *Test_number,char* Units[])
{
	map<string, tyLimitsData> mapLimits;
    string name = TheSoft.Flow().GetCurrentFlowName();
    map<string, tyLimitsData>::iterator iter;
    tyLimitsData tempLimitsData;
    vector<string> test_name;
    vector<double> lowlimit;
    vector<double> highlimit;
    vector<string> units;
    vector<ViUInt64> test_number;

    iter = mapLimits.find(name);
    if(iter != mapLimits.end())
    {
        tempLimitsData = iter->second;
//        flowtable = tempLimitsData.flowtable;

        if(CurrentLimitSet=="Default"){
        lowlimit = tempLimitsData.Default_lolim;
        highlimit = tempLimitsData.Default_hilim;
        }
        else if(CurrentLimitSet=="Golden"){
        lowlimit = tempLimitsData.Golden_lolim;
        highlimit = tempLimitsData.Golden_hilim;
        }
//        else if(CurrentLimitSet=="L40C_QA"){
//        lowlimit = tempLimitsData.L40C_QA_lolim;
//        highlimit = tempLimitsData.L40C_QA_hilim;
//        }
//        else if(CurrentLimitSet=="L40C"){
//        lowlimit = tempLimitsData.L40C_lolim;
//        highlimit = tempLimitsData.L40C_hilim;
//        }
        else if(CurrentLimitSet=="QA"){
        lowlimit = tempLimitsData.QA_lolim;
        highlimit = tempLimitsData.QA_hilim;
        }
//        else if(CurrentLimitSet=="_105C_QA"){
//        lowlimit = tempLimitsData._105C_QA_lolim;
//        highlimit = tempLimitsData._105C_QA_hilim;
//        }
//        else if(CurrentLimitSet=="_105C"){
//        lowlimit = tempLimitsData._105C_lolim;
//        highlimit = tempLimitsData._105C_hilim;
//        }

        test_name = tempLimitsData.testname;
        test_number = tempLimitsData.testnumber;
        units = tempLimitsData.units;

    }

    for(int i = 0; i < lowlimit.size(); i++)
    {
       Lowlimit[i] = lowlimit[i];
       Highlimit[i] = highlimit[i];
       Test_number[i] = test_number[i];

       Test_name[i] = (char*)test_name[i].c_str();
       Units[i] = (char*)units[i].c_str();
    }

}
