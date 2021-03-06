/* 
 * File:   Globle_Var.h
 * Author: TRD-02
 *
 * Created on 2020年12月4日, 下午4:47
 */

#pragma once
#include "d2sProtocolSSI.h"
#include "CCWaveformsData.h"
#include "Gainmode_Parse.h"
#include "string.h"
#include "Excel.h"
#include "CBBLimits.h"

#include <vector>

#ifndef GLOBLE_VAR_H
#define	GLOBLE_VAR_H

//
#define semi_parallel_en
//#define NEW_DLL


#ifdef NEW_DLL
typedef CGainMode GAINMODE;
#else
typedef CGainModeParse GAINMODE;
#endif
extern d2sWorkModeType d2s_WorkMode;
//extern bool semi_parallel_en;

extern map<int,long long> pmu_v_trimData;
extern map<int,long long> pmu_i_trimData;
extern map<int,long long> buck_v_trimData;

extern map<int,long long> pmu_v_pretrimData;
extern map<int,long long> buck_v_pretrimData;
extern map<int,long long> pb_i_pretrimData;
extern map<int,long long> TSENSOR_TG;
extern map<int,double> IDDQ_CLDO;

extern map<int,long long> FT_PASSFLAG;
extern long PRE_ABB_ADC[4];
extern long PRE_2G_C0_UPC[4];
extern long PRE_2G_C1_UPC[4];
extern long PRE_2G_C0_GAIN[4];
extern long PRE_2G_C1_GAIN[4];
        
//map<int,long long> RC_CAL_CODE_C0;
//map<int,long long> R_CAL_CODE_C0;
//map<int,long long> C_CAL_CODE_C0;

extern CSiteLong RC_CAL_CODE_C0;
extern CSiteLong R_CAL_CODE_C0;
extern CSiteLong C_CAL_CODE_C0;

extern CSiteLong RC_CAL_CODE_C1;
extern CSiteLong R_CAL_CODE_C1;
extern CSiteLong C_CAL_CODE_C1;  

extern CSiteLong PV_SENSOR_C0_CODE;
extern CSiteLong PV_SENSOR_C1_CODE;

extern CSiteLong ADC_C0_COMP_CAL_CODE_A1;
extern CSiteLong ADC_C0_COMP_CAL_CODE_A2;
extern CSiteLong ADC_C0_COMP_CAL_CODE_A3;
extern CSiteLong ADC_C1_COMP_CAL_CODE_A1;
extern CSiteLong ADC_C1_COMP_CAL_CODE_A2;
extern CSiteLong ADC_C1_COMP_CAL_CODE_A3;

extern long WL5G_B1_PPF[64];
extern long WL5G_B2_PPF[64];
extern long WL5G_B4_PPF[64];
extern long WL5G_B5_PPF[64];
extern long WL5G_B7_PPF[64];

extern CSiteLong WL_C0_PPF_CODE;
extern CSiteLong WL_C1_PPF_CODE;

extern map<int, long long> pb_i_TrimData;
//extern CSiteLong pb_i_TrimData;

extern bool TestInfoLoaded_Flag;

extern long CosLut_5M[32];
extern long SinLut_5M[32];

extern long CosLut_25M[32];
extern long SinLut_25M[32];

extern long CosLut_35M[32];
extern long SinLut_35M[32];

extern char *Last_GainMode;
extern int Last_RFmode;
extern int Last_RFband;
extern int Last_LPFBW;
extern GAINMODE RX_GAIN_I_LIST;
extern GAINMODE RX_GAIN_Q_LIST;
extern double* Last_Gain_I;
extern double* Last_Gain_Q;
extern string Last_TestName;

extern map<string, tyLimitsData> mapLimits;
extern tyTestDatas AllTabelData;
extern char *CurrentLimitSet;
extern bool Clogenable;
extern int Testsoftbin[4];
extern bool HBIN_FLAG[4];
//extern long long i_TrimData;

extern map<int,long long> TEST_COUNT;//globle
    
extern map<int,double> PRE_VREF_TRIM;//globle,value in code
extern map<int,double> PRE_BUCK_TRIM;
extern map<int,double> PRE_IREF_TRIM;

extern map<int,double> PRE_VREF_TRIM_SUM;//globle
extern map<int,double> PRE_BUCK_TRIM_SUM;
extern map<int,double> PRE_IREF_TRIM_SUM;

extern map<int,double> PreVrefAve;//globle
extern map<int,double> PreBuckAve;
extern map<int,double> PreIrefAve;

extern CSiteDouble PRE_VREF_ARRAY;//globle
extern CSiteDouble PRE_BUCK_ARRAY;//globle
extern CSiteDouble PRE_IREF_ARRAY;//globle
extern int TRIM_DATA_LIST_C0[10][4];
extern int TRIM_DATA_LIST_C1[10][4];
extern double RX_GAIN_MAX_I_C0[10][4];
extern double RX_GAIN_MAX_I_C1[10][4];

//extern map<string, tyLimitsData> mapLimits;

#endif	/* GLOBLE_VAR_H */



