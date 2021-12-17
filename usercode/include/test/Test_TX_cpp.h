/*
 * Test_TX_cpp.h
 *
 *  Created on: 2021年10月29日
 *      Author: 荣耀
 */

#ifndef INCLUDE_TEST_TX_CPP_H_
#define INCLUDE_TEST_TX_CPP_H_

#include "GetLog.h"
#include "CCS08F.h"
//#include "Excel.h"
#include "UserAPI.h"
#include "UserDef.h"
#include "RegDef.h"
#include "d2sProtocolSSI.h"
#include <string>
#include <math.h>
#include "D2S_CAL_Module.h"
#include <vector>
#include <string.h>
#include "linearfit.h"
#include "D2S_PMU_Module.h"
#include "Globle_Var.h"

int TX_Power_Trim_Function(emMode Mode_Select,emTX_Band Band_Select,char *Channel, double *Pre_Output_Power,int *TrimData);
int Calc_Power_dbm(SpecAnResultAttribute *ResultAttribute, int Exp_Bin, int index_bin_num,double *Pre_Output_Power,double pathloss);
int calc_WL_TX_OIP3(tyTestData *pRF_Test_Data,SpecAnResultAttribute *ResultAttribute,double pathloss,double *Output_Power,double *Result_oip3);
int calc_WL_TX_OIP3_Dri_Mode(tyTestData *pRF_Test_Data,SpecAnResultAttribute *ResultAttribute,double pathloss, double *Output_Power,double *Result_im3,double *Result_oip3);
int Calc_TX_Power_CR_SR(tyTestData *pRF_Test_Data,SpecAnResultAttribute *ResultAttribute,double pathloss,double *Post_Power,double *CR,double *SR);
void Calc_TX_Power_2_Spur(tyTestData *pRF_Test_Data,SpecAnResultAttribute *ResultAttribute,double pathloss,double Space1,double Space2,double *outPower,double *SPUR1_dbm,double *SPUR2_dbm);
void Calc_TX_Power_3_Spur(tyTestData *pRF_Test_Data,SpecAnResultAttribute *ResultAttribute,double pathloss,double Space1,double Space2,double Space3,double *outPower,double *SPUR1_dbm,double *SPUR2_dbm,double *SPUR3_dbm);
int calc_PLL_Sweep(int site_id,long long *Dataarray,long sweep_step,double *bandError,long *first_band_value,long *last_band_value,long *max_pll_State,long *min_pll_State);


#endif /* INCLUDE_TEST_TX_CPP_H_ */
