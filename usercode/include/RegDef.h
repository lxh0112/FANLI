/* 
 * File:   RegDef.h
 * Author: TRD-02
 *
 * Created on 2020年11月11日, 下午12:27
 */

#ifndef TESTAPI_H
#define	TESTAPI_H



#if 0

#include "CCS08F.h"

#endif

#include "UserAPI.h"
#include "Excel.h"
//using namespace MuTest;

//RX_Reg
int WLAN_2G_RX_C0_PLL_Reg(emRX_Band Band_Select,double BW);
int WLAN_2G_RX_C1_PLL_Reg(emRX_Band Band_Select,double BW);
int WLAN_5G_RX_C0_PLL_Reg(emRX_Band Band_Select,double BW);
int WLAN_5G_RX_C1_PLL_Reg(emRX_Band Band_Select,double BW);
int WLAN_2G_RX_C0_BW_Reg(emRX_Band Band_Select,double BW);
int WLAN_2G_RX_C1_BW_Reg(emRX_Band Band_Select,double BW);
int WLAN_5G_RX_C0_BW_Reg(emRX_Band Band_Select,double BW);
int WLAN_5G_RX_C1_BW_Reg(emRX_Band Band_Select,double BW);
int WLAN_2G_RX_C0_Gain_Mode_Reg(char *RX_Gain_Mode_Label);
int WLAN_2G_RX_C1_Gain_Mode_Reg( char *RX_Gain_Mode_Label);
int WLAN_5G_RX_C0_Gain_Mode_Reg(char *RX_Gain_Mode_Label);
int WLAN_5G_RX_C1_Gain_Mode_Reg(char *RX_Gain_Mode_Label);
int TestMux_RX_C0_Reg();
int TestMux_RX_C1_Reg();

//TX_Reg
void WLAN_2G_TX_C0_PLL_Reg(emTX_Band Band_Select);
void WLAN_2G_TX_C1_PLL_Reg(emTX_Band Band_Select);
void WLAN_5G_TX_C0_PLL_Reg(emTX_Band Band_Select, double BW);
void WLAN_5G_TX_C1_PLL_Reg(emTX_Band Band_Select, double BW);
void WLAN_2G_TX_C0_BW_Reg(emTX_Band Band_Select);
void WLAN_2G_TX_C1_BW_Reg(emTX_Band Band_Select);
void WLAN_5G_TX_C0_BW_Reg(emTX_Band Band_Select, double BW);
void WLAN_5G_TX_C1_BW_Reg(emTX_Band Band_Select, double BW);
void TestMux_TX_C0_Reg();
void TestMux_TX_C1_Reg();

//Init_Reg
int WLAN_RX_2G_C0_Init_Reg();
int WLAN_RX_2G_C1_Init_Reg();
int WLAN_RX_5G_C0_Init_Reg();
int WLAN_RX_5G_C1_Init_Reg();
void WLAN_TX_2G_C0_Init_Reg();
void WLAN_TX_2G_C1_Init_Reg();
void WLAN_TX_5G_C0_Init_Reg();
void WLAN_TX_5G_C1_Init_Reg();

//Setup
bool RFMode_Changed(emMode RF_Mode,int RF_Band);
bool LPFBW_Changed(double LPF_BW);
int RX_PLL_Setup(emMode Mode_Select ,emRX_Band Band_Select ,char *Channel, double BW);
int RX_BW_Setup(emMode Mode_Select ,emRX_Band Band_Select ,char *Channel, double BW);
bool GainMode_Changed(char *GainMode);
int RX_Gain_Mode_Setup(emMode Mode_Select,char *RX_Gain_Mode_Label, char *Channel);
int TX_PLL_Setup(emMode Mode_Select ,emTX_Band Band_Select ,char *Channel, double BW);
int TX_BW_Setup(emMode Mode_Select ,emTX_Band Band_Select ,char *Channel, double BW);
int Set_RF_RX_Pll_BW(emMode RF_Mode,emRX_Band RF_Band,double LPF_BW,char * Channel);
int Set_RF_RX_GainMode(char * GainMode,emMode RF_Mode,char * Channel);
int Set_RF_TX_Pll_BW(emMode RF_Mode, emTX_Band RF_Band, double LPF_BW, char *Channel);
int WLAN_Disable_Reg();

#endif	/* TESTAPI_H */

