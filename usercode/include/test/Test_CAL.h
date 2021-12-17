/*
 * File:   CAL_Test.h
 * Author: TRD-02
 *
 * Created on 2020年11月10日, 下午4:51
 */
#pragma once
#ifndef CAL_TEST_H
#define	CAL_TEST_H

#include "Systick.h"
#include "GetLog.h"
#include "UserAPI.h"
#include "UserDef.h"
#include "d2sProtocolSSI.h"
#include "D2S_CAL_Module.h"
#include "D2S_ABB_Module.h"
#include "Test_ABB.h"
//#include "CCS08F.h"
//#include "RegDef.h"
#include "Globle_Var.h"
#include <math.h>
//#include "RegDef.h"
#include "Excel.h"
#include <vector>
#include <string.h>
#include "linearfit.h"
#include "Globle_Var.h"
//#include "CCS08F.h"
#include <algorithm>
#include <iostream>


int Calc_VI_Det(long long *CAL_V_Code,long long *CAL_I_Code,\
                            long *tempFlow,\
                            long *Delt,\
                            long *Delt_Index,\
                            long *FirstVal,\
                            long *LastVal,\
                            long *Near_125K_Val,\
                            long *Near_125K_Val_index,\
                            double *Poly_Max,\
                            double *Poly_Min,\
                            long *I_FirstCode,\
                            long *I_FirstData,\
                            long *I_HalfCycle,\
                            long *I_VppL,\
                            long *I_CycleL,\
                            long *I_VppH,\
                            long *I_CycleH,\
                            long *I_FlatnessL,\
                            long *I_FlatnessH);


int DSP_WLAN_IQ_P_FIT_VBT(double *P_Wave, double *P_MaxError, double *Freq_MaxError, double *AvgError);
int Calc_WLAN_IQ_PE_VBT(int index,int Capsize,CSiteLong *Capwave,\
                                        long *gCos, \
                                        long *gSin, \
                                        double *E_Value, \
                                        double *P_Value);


#endif	/* ABB_TEST_H */

