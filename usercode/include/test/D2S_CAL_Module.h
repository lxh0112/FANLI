/* 
 * File:   D2S_CAL_Module.h
 * Author: Administrator
 *
 * Created on 2020年11月10日, 下午3:45
 */

#ifndef D2S_CAL_MODULE_H
#define	D2S_CAL_MODULE_H

#include "UserAPI.h" 
#include "d2sProtocolSSI.h"
#include "CCWaveformsData.h"



void Cal_SOC_2G_Init_Module();
void Cal_SOC_5G_Init_Module();
void Cal_PHY_2G_Init_Module();
void Cal_PHY_5G_Init_Module();
void Cal_ABB_RF_2G_Init_Module();
void Cal_ABB_RF_5G_Init_Module();
void RC_CAL_Final_Module();
//void VI_DET_C0_Module();
void VI_DET_C0_Module(CSiteLong *pReadValue);
//void VI_DET_C1_Module();
void VI_DET_C1_Module(CSiteLong *pReadValue);
void PDBUF_DET_C0_Set_Module();
void PDBUF_DET_C0_Restore_Module();
void PDBUF_DET_C1_Set_Module();
void PDBUF_DET_C1_Restore_Module();
//void PD_BUF_Cmmulate_Module();
void RXIQ_5G_C0_Set_Module();
void RXIQ_5G_C0_Restore_Module();
void RXIQ_5G_C1_Set_Module();
void RXIQ_5G_C1_Restore_Module();
void TXIQ_5G_C0_Module();
void DAC_SPUR_C0_Module();
void DAC_SPUR_C1_Module();
void TXIQ_5G_37p5M_C0_Module();
void TXIQ_5G_C1_Module();
void DAC_SPUR_Restore_Module();

void RC_Cal_C0_Module(CSiteLong* pSiteData);
void RC_Cal_C1_Module(CSiteLong* pSiteData);

void PD_BUF_Cmmulate_Module(CSiteLong *FEM_PD_data);
void TXIQ_5G_37p5M_C1_Module();
void TXIQ_5G_Restore_Module();
void PDBUF_C0_C1_Module(CSiteLong *pReadValue0,CSiteLong *pReadValue1);


#endif	/* D2S_CAL_MODULE_H */
