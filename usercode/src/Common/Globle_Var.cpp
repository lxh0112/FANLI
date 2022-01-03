
#include "d2sProtocolSSI.h"
#include "Globle_Var.h"
#include "string.h"
#include"UserAPI.h"
#include <iostream>

d2sWorkModeType d2s_WorkMode = LearningMode;

//bool semi_parallel_en;
map<string, tyLimitsData> mapLimits;
map<int,long long> pmu_v_trimData;
map<int,long long> buck_v_trimData;
map<int,long long> pb_i_TrimData;



map<int,long long> pmu_v_pretrimData;
map<int,long long> buck_v_pretrimData;
map<int,long long> pb_i_pretrimData;
//CSiteLong pb_i_TrimData;

map<int,long long> TSENSOR_TG;
map<int,double> IDDQ_CLDO;

map<int,long long> FT_PASSFLAG;
long PRE_ABB_ADC[4];
long PRE_2G_C0_UPC[4];
long PRE_2G_C1_UPC[4];
long PRE_2G_C0_GAIN[4];
long PRE_2G_C1_GAIN[4];

//map<int,long long> RC_CAL_CODE_C0;
//map<int,long long> R_CAL_CODE_C0;
//map<int,long long> C_CAL_CODE_C0;

CSiteLong RC_CAL_CODE_C0;
CSiteLong R_CAL_CODE_C0;
CSiteLong C_CAL_CODE_C0;

CSiteLong RC_CAL_CODE_C1;
CSiteLong R_CAL_CODE_C1;
CSiteLong C_CAL_CODE_C1;

CSiteLong PV_SENSOR_C0_CODE;
CSiteLong PV_SENSOR_C1_CODE;

CSiteLong ADC_C0_COMP_CAL_CODE_A1;
CSiteLong ADC_C0_COMP_CAL_CODE_A2;
CSiteLong ADC_C0_COMP_CAL_CODE_A3;
CSiteLong ADC_C1_COMP_CAL_CODE_A1;
CSiteLong ADC_C1_COMP_CAL_CODE_A2;
CSiteLong ADC_C1_COMP_CAL_CODE_A3;

map<int,long long> TEST_COUNT;//globle

map<int,double> PRE_VREF_TRIM;//globle,value in code
map<int,double> PRE_BUCK_TRIM;
map<int,double> PRE_IREF_TRIM;

map<int,double> PRE_VREF_TRIM_SUM;//globle
map<int,double> PRE_BUCK_TRIM_SUM;
map<int,double> PRE_IREF_TRIM_SUM;

map<int,double> PreVrefAve;//globle
map<int,double> PreBuckAve;
map<int,double> PreIrefAve;

CSiteDouble PRE_VREF_ARRAY;//globle
CSiteDouble PRE_BUCK_ARRAY;//globle
CSiteDouble PRE_IREF_ARRAY;//globle


long WL5G_B1_PPF[64];
long WL5G_B2_PPF[64];
long WL5G_B4_PPF[64];
long WL5G_B5_PPF[64];
long WL5G_B7_PPF[64];

CSiteLong WL_C0_PPF_CODE;
CSiteLong WL_C1_PPF_CODE;

//WL_C0_PPF_CODE->InitDataArray(0,36);


bool TestInfoLoaded_Flag = false;
//long long i_TrimData;

//long pb_i_TrimData = 15;


long CosLut_5M[32];
long SinLut_5M[32];

long CosLut_25M[32];
long SinLut_25M[32];

long CosLut_35M[32];
long SinLut_35M[32];
char *Last_GainMode;
int Last_RFmode;
int Last_RFband;
int Last_LPFBW;
//GAINMODE RX_GAIN_I_LIST;
//GAINMODE RX_GAIN_Q_LIST;
double* Last_Gain_I;
double* Last_Gain_Q;
string Last_TestName;
char *CurrentLimitSet;
bool Clogenable;
int Testsoftbin[4] = {1,1,1,1};
bool HBIN_FLAG[4];
int TRIM_DATA_LIST_C0[10][4];
int TRIM_DATA_LIST_C1[10][4];
double RX_GAIN_MAX_I_C0[10][4];
double RX_GAIN_MAX_I_C1[10][4];


#if 1
void Read_Limit(double *Lowlimit,double *Highlimit,vector<string> &Test_name,int *Test_number,vector<string> &Units,int *Fail_Soft,int *Fail_Hard)
{
    string name = TheSoft.Flow().Test().GetCurrentTestName();
    map<string, tyLimitsData>::iterator iter;
    tyLimitsData tempLimitsData;
    vector<string> test_name;
    vector<double> lowlimit;
    vector<double> highlimit;
    vector<string> units;
    vector<ViUInt64> test_number;
    vector<ViUInt32> fail_sort;
    vector<ViUInt8> fail_bin;

    iter = mapLimits.find(name);
    if(iter != mapLimits.end())
    {
        tempLimitsData = iter->second;
//        flowtable = tempLimitsData.flowtable;

        if(strcmp("Default",CurrentLimitSet) == 0){
			lowlimit = tempLimitsData.Default_lolim;
			highlimit = tempLimitsData.Default_hilim;
        }
        else if(strcmp("Golden",CurrentLimitSet) == 0){
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
        else if(strcmp("QA",CurrentLimitSet) == 0){
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
        fail_sort = tempLimitsData.failsort;
        fail_bin = tempLimitsData.failbin;

        test_name = tempLimitsData.testname;
        test_number = tempLimitsData.testnumber;
        units = tempLimitsData.units;

    }

    Test_name = test_name;
    Units = units;

    for(unsigned int i = 0; i < lowlimit.size(); i++)
    {
       Lowlimit[i] = lowlimit[i];
       Highlimit[i] = highlimit[i];
       Test_number[i] = test_number[i];
       Fail_Soft[i]=fail_sort[i];
       Fail_Hard[i] = fail_bin[i];

//       Test_name[i] = test_name[i];
//       Units[i] = units[i];

//       printf(".................... Test_name:%s --- Units:%s \n",Test_name[i],Units[i]);
    }

}
#endif



void Read_Limit(double *Lowlimit,double *Highlimit,char *Test_name[],int *Test_number,char *Units[],int *Fail_Soft,int *Fail_Hard)
{
    string name = TheSoft.Flow().Test().GetCurrentTestName();
    map<string, tyLimitsData>::iterator iter;
    tyLimitsData tempLimitsData;
    vector<string> test_name;
    vector<double> lowlimit;
    vector<double> highlimit;
    vector<string> units;
    vector<ViUInt64> test_number;
    vector<ViUInt32> fail_sort;
    vector<ViUInt8> fail_bin;

    iter = mapLimits.find(name);
    if(iter != mapLimits.end())
    {
        tempLimitsData = iter->second;
//        flowtable = tempLimitsData.flowtable;

        if(strcmp("Default",CurrentLimitSet) == 0){
			lowlimit = tempLimitsData.Default_lolim;
			highlimit = tempLimitsData.Default_hilim;
        }
        else if(strcmp("Golden",CurrentLimitSet) == 0){
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
        else if(strcmp("QA",CurrentLimitSet) == 0){
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
        fail_sort = tempLimitsData.failsort;
        fail_bin = tempLimitsData.failbin;

        test_name = tempLimitsData.testname;
        test_number = tempLimitsData.testnumber;
        units = tempLimitsData.units;

    }

    for(unsigned int i = 0; i < lowlimit.size(); i++)
    {
       Lowlimit[i] = lowlimit[i];
       Highlimit[i] = highlimit[i];
       Test_number[i] = test_number[i];
       Fail_Soft[i]=fail_sort[i];
       Fail_Hard[i] = fail_bin[i];

       Test_name[i] = (char*)test_name[i].c_str();
       Units[i] = (char*)units[i].c_str();

       printf(".................... Test_name:%s --- Units:%s \n",Test_name[i],Units[i]);
    }

}
