/* 
 * File:   D2S_ABB_Module.h
 * Author: Administrator
 *
 * Created on 2020年11月10日, 下午4:14
 */
#pragma once
#ifndef D2S_ABB_MODULE_H
#define	D2S_ABB_MODULE_H

#include "UserAPI.h" 
#include "d2sProtocolSSI.h"
#include "CCWaveformsData.h"


enum emADCCalType{calType_Normal=0,calType_LV,cal_Type_SS,calType_Nocal,calType_LV1};

void WL_ADC_C0_DC_Module();
void WL_ADC_C1_DC_Module();
//void WL_ADC_C0_Cap_Module();
//void WL_ADC_C0_Cap_Module(CSiteLong *pReadValue);

void WL_DAC_SRC_DATA_module();
void WL_ADC_C0_Setup_PVCal_Module(CSiteLong* pReadValue);
void WL_ADC_C0_Setup_PVCal_LV_Module(CSiteLong *pReadValue);
void WL_ADC_C0_Setup_PVCal_LV1_Module(CSiteLong *pReadValue);
//void WL_ADC_C0C1_Setup_CalStatus_Module();
void WL_ADC_C0C1_Setup_CalStatus_Module(CSiteLong *pReadValue);
//void WL_ADC_C0_Setup_CalStatus_Module();
void WL_ADC_C0_Setup_CalStatus_Module(CSiteLong *pReadValue);
//void WL_ADC_C0_Setup_CapCal_Module();
void WL_ADC_C0_Setup_CapCal_Module(CSiteLong *pReadValue);
void WL_ADC_C1_Setup_PVCal_Module(map<int, long long> capture_data0,map<int, long long> capture_data1);
void WL_ADC_C1_Setup_PVCal_Module(CSiteLong* pReadValue);
void WL_ADC_C1_Setup_PVCal_LV_Module(CSiteLong *pReadValue);
void WL_ADC_C1_Setup_PVCal_LV1_Module(CSiteLong *pReadValue);
//void WL_ADC_C1_Setup_CalStatus_Module();
void WL_ADC_C1_Setup_CalStatus_Module(CSiteLong *pReadValue);
//void WL_ADC_C1_Setup_CapCal_Module();
//void WL_ADC_C1_Setup_CapCal_Module(CSiteLong *pReadValue);
void WL_ADC_C1_Setup_CapCal_Module(CSiteLong *pReadValue);
void WL_DAC_C0_LPF_Module();
void WL_DAC_DEM_C0_LPF_Module();
void WL_DAC_C1_LPF_Module();
void WL_DAC_DEM_C1_LPF_Module();
void PHY_ABB_RF_Reset_Module();
void WL_ADC_C0_BeforeCap_Module();
void WL_ADC_C1_BeforeCap_Module();

void WL_ADC_C0_Cap_Module(CSiteLong *pReadValue);
void WL_ADC_C0_Cap_Module_read(CSiteLong *pReadValue);
void WL_RX_CAL_PHASE_ADC_C0_Cap_Module(CSiteLong *pReadValue);
//void WL_ADC_C1_Cap_Module(CSiteLong *pReadValue);
void WL_ADC_C1_Cap_Module(CSiteLong *pReadValue);
void WL_ADC_C1_Cap_Module_read(CSiteLong *pReadValue);
void WL_RX_CAL_PHASE_ADC_C1_Cap_Module(CSiteLong *pReadValue);

void WL_PD_BUF_ADC_C0_BeforeCap_Module(CSiteLong *pReadValue);
void WL_PD_BUF_ADC_C0_Cap_Module(CSiteLong *pReadValue);
void WL_PD_BUF_ADC_C1_BeforeCap_Module(CSiteLong *pReadValue);
void WL_PD_BUF_ADC_C1_Cap_Module(CSiteLong *pReadValue);

void WL_PD_BUF_GPIO1_ADC_C1_Cap_Module(CSiteLong *pReadValue);
void WL_PD_BUF_GPIO1_ADC_C0_Cap_Module(CSiteLong *pReadValue);

#endif	/* D2S_ABB_MODULE_H */

