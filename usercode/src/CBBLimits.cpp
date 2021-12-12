#include "CBBLimits.h"
#include "TestClass.h"
#include "ExcelOprt.h"
#include <string>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cctype>
#include <algorithm>

using namespace std;
class CBBLimits: public TestClass{
public:
	void init(){
	}
#define START_ROW 4
#define DOUBLE_LOW_NA -999999
#define DOUBLE_HIGH_NA 999999
#define LOW 0
#define HIGH 1

void execute(){
typedef struct{
    ViUInt16 col_flowtable;
    ViUInt16 col_instance;
    ViUInt16 col_testname;
    ViUInt16 col_testnumber;
    ViUInt16 col_Default_lolim;
    ViUInt16 col_Default_hilim;
    ViUInt16 col_QA_lolim;
    ViUInt16 col_QA_hilim;
    ViUInt16 col_Golden_lolim;
    ViUInt16 col_Golden_hilim;
//    ViUInt16 col_L40C_lolim;
//    ViUInt16 col_L40C_hilim;
//    ViUInt16 col_L40C_QA_lolim;
//    ViUInt16 col_L40C_QA_hilim;
//    ViUInt16 col_105C_lolim;
//    ViUInt16 col_105C_hilim;
//    ViUInt16 col_105C_QA_lolim;
//    ViUInt16 col_105C_QA_hilim;
    ViUInt16 col_scale;
    ViUInt16 col_units;
    ViUInt16 col_failsort;
    ViUInt16 col_failbin;
	}ColAllIndex;
}

//static void EnableCol(ColAllIndex *retColAllIndex);

CBBLimits::CBBLimits()
{
    
}

CBBLimits::~CBBLimits()
{
    
}

int CBBLimits::ReadLimits(char* pszLimitsPath, map<string, tyLimitsData>* mapOfLimits)
{
    clock_t start, stop;
    double duration = 0.0;
    
    string strLimitsPath = pszLimitsPath;
    if(strLimitsPath.find(".xlsx") == string::npos)
    {
        return ERR_EXCEL_PATH;
    }
    
    if(InitExcelOLE() != true)
    {
        ReleaseExcelOLE();
        return INIT_EXCEL_FAIL;
    }
    
    if(OpenExcel(pszLimitsPath) != true)
    {
        CloseExcel();
        ReleaseExcelOLE();
        return OPEN_EXCEL_FAIL;
    }
    
    LoadSheetByIndex(1);

/*    ColAllIndex colAllIndex;
    char *pszInstance;
    char *pszNextInstance;
    tyLimitsData limitsData;
    ViUInt32 rowTotal = GetRowCount();
    ViUInt32 colTotal = GetColumnCount();
    
    EnableCol(&colAllIndex);
    char *cell;
    for(int row_i = START_ROW; row_i <= rowTotal; row_i++)
    {
        pszInstance = GetCellString(row_i, colAllIndex.col_instance);
        pszNextInstance = GetCellString(row_i + 1, colAllIndex.col_instance);
        
        limitsData.flowtable.push_back(string(GetCellString(row_i, colAllIndex.col_flowtable)));
        limitsData.testname.push_back(string(GetCellString(row_i, colAllIndex.col_testname)));
        
        limitsData.testnumber.push_back((ViUInt64)GetCellInt(row_i, colAllIndex.col_testnumber));
        limitsData.Default_lolim.push_back(GetDoubleData(GetCellString(row_i, colAllIndex.col_Default_lolim), LOW));
        limitsData.Default_hilim.push_back(GetDoubleData(GetCellString(row_i, colAllIndex.col_Default_hilim), HIGH));
        limitsData.QA_lolim.push_back(GetDoubleData(GetCellString(row_i, colAllIndex.col_QA_lolim), LOW));
        limitsData.QA_hilim.push_back(GetDoubleData(GetCellString(row_i, colAllIndex.col_QA_hilim), HIGH));
        limitsData.Golden_lolim.push_back(GetDoubleData(GetCellString(row_i, colAllIndex.col_Golden_lolim), LOW));
        limitsData.Golden_hilim.push_back(GetDoubleData(GetCellString(row_i, colAllIndex.col_Golden_hilim), HIGH));
        
//        limitsData.L40C_lolim.push_back(GetDoubleData(GetCellString(row_i, colAllIndex.col_L40C_lolim), LOW));
//        limitsData.L40C_hilim.push_back(GetDoubleData(GetCellString(row_i, colAllIndex.col_L40C_hilim), HIGH));
//        limitsData.L40C_QA_lolim.push_back(GetDoubleData(GetCellString(row_i, colAllIndex.col_L40C_QA_lolim), LOW));
//        limitsData.L40C_QA_hilim.push_back(GetDoubleData(GetCellString(row_i, colAllIndex.col_L40C_QA_hilim), HIGH));
//        limitsData._105C_lolim.push_back(GetDoubleData(GetCellString(row_i, colAllIndex.col_105C_lolim), LOW));
//        limitsData._105C_hilim.push_back(GetDoubleData(GetCellString(row_i, colAllIndex.col_105C_hilim), HIGH));
//        limitsData._105C_QA_lolim.push_back(GetDoubleData(GetCellString(row_i, colAllIndex.col_105C_QA_lolim), LOW));
//        limitsData._105C_QA_hilim.push_back(GetDoubleData(GetCellString(row_i, colAllIndex.col_105C_QA_hilim), HIGH));
        
        limitsData.scale.push_back(string(GetCellString(row_i, colAllIndex.col_scale)));
        limitsData.units.push_back(string(GetCellString(row_i, colAllIndex.col_units)));
        
        limitsData.failsort.push_back((ViUInt32)GetCellInt(row_i, colAllIndex.col_failsort));
        limitsData.failbin.push_back((ViUInt8)GetCellInt(row_i, colAllIndex.col_failbin));
        
        if(strcmp(pszInstance, pszNextInstance) != 0)
        {
            string temp = string(pszInstance);
            for(int temp_i = 0; temp_i < temp.size(); temp_i++)
            {
                temp[temp_i] = toupper(temp[temp_i]);
            }
            //transform(temp.begin(), temp.end(), temp.begin(), toupper);
//            mapOfLimits->insert(make_pair<string,tyLimitsData>(temp, limitsData));
            memset((void *)&limitsData, 0x00, sizeof(tyLimitsData));
        }
    }*/
    
    CloseExcel();
    ReleaseExcelOLE();
    
    return READ_SUCCESS;
}

/*
void EnableCol(ColAllIndex *retColAllIndex)
{
    retColAllIndex->col_flowtable = 3;
    retColAllIndex->col_instance = 4;
    retColAllIndex->col_testname = 5;
    retColAllIndex->col_testnumber = 6;
    retColAllIndex->col_Default_lolim = 9;
    retColAllIndex->col_Default_hilim = 10;
    retColAllIndex->col_QA_lolim = 13;
    retColAllIndex->col_QA_hilim = 14;
    retColAllIndex->col_Golden_lolim = 11;
    retColAllIndex->col_Golden_hilim = 12;
//    retColAllIndex->col_L40C_lolim = 15;
//    retColAllIndex->col_L40C_hilim = 16;
//    retColAllIndex->col_L40C_QA_lolim = 17;
//    retColAllIndex->col_L40C_QA_hilim = 18;
//    retColAllIndex->col_105C_lolim = 19;
//    retColAllIndex->col_105C_hilim = 20;
//    retColAllIndex->col_105C_QA_lolim = 21;
//    retColAllIndex->col_105C_QA_hilim = 22;
    retColAllIndex->col_scale = 15;
    retColAllIndex->col_units = 16;
    retColAllIndex->col_failsort = 19;
    retColAllIndex->col_failbin = 21;
}
*/


inline double CBBLimits::GetDoubleData(char *pszData , int nLowOrHigh)
{
    if(!strcmp(pszData, "NA"))
    {
        if(nLowOrHigh == LOW)
        {
            return DOUBLE_LOW_NA;
        }
        else
        {
            return DOUBLE_HIGH_NA;
        }
    }
    return atof(pszData);

}

};

	REGISTER_TESTCLASS("CBBLimits",CBBLimits);





