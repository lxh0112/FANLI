/* 
 * File:   UserDef.h
 * Author: dongyuqing
 *
 * Created on 2020年11月5日, 上午9:45
 */






#ifndef USERDEF_H
#define	USERDEF_H
#include "UserAPI.h"
#include "CCS08F.h"
#include "Excel.h"
#include "Globle_Var.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>
#include <synchapi.h>




//using namespace MuTest;

#define Test_Success 0
#define _MAX_NAME_SIZE_RF   128



#define ErrorCheck(functionCall) if( Test_Success != (error=(functionCall)) ) goto errHandler; else

//#define PINGPONG_TEST

//extern CBBAPI CC08F_CBB_API;
extern const char* programPath;
extern int LoadAllSignalAttr(char* ExcelFilePath,char* PathlossFilePath);
extern int Get_TestItem_Info(const char* testname, tyTestData &Test_Data);
extern int Get_Pin_Name(tyTestData Test_Data, char* SrcPinName, char* CapPinName);
extern int Get_Signal_Name(tyTestData Test_Data, char* SrcSignalName, char* CapSignalName);
//extern int GetPowerofSpecifiedFreq(SpecAnResultAttribute *SpecAnMeasData, double dwFrequency, double &dwPower, int nSpanNum = 5);

//extern int ComputeDoubleToneIMD3(SpecAnResultAttribute *SpecAnMeasData, double dwFrequency1, double dwFrequency2, ViReal32 &dwIMD3Power, int nSpanNum = 5);
extern int FFTFromIQData(IQMeasureAttribute *IQMeasData, double** Spectrum_I, double** Spectrum_Q);
//extern int FFTFromIQData(IQMeasureAttribute *IQMeasData, double *Spectrum_I, double *Spectrum_Q);

extern int GetPowerofSpecifiedFreq(double *Spectrum_I, double *Spectrum_Q, double dwFrequency, double dwSampleRate, double dwSampleSize, 
                            double &dwPower_I, double &dwPower_Q, double BinNum =1);
extern int Cal_PowerUpTime(IQMeasureAttribute *IQMeasData, double TriggerData, double &dwPowerUpI, double &dwPowerUpQ);
extern int GetIMD3FromIQData(double *Spectrum_I, double *Spectrum_Q, double dwFrequency1, double dwFrequency2, \
                      double dwSampleRate, double dwSampleSize, double &dwIMD3Power_I, double &dwIMD3Power_Q, double &fund_Power_I, double &fund_Power_Q);
//extern int PlotCurve(IQMeasureAttribute *IQMeasData, char* waveformName);


int Driver_Mode_Setup();
int Driver_Mode_Recover_Setup();
int DummyOP_Path_Setup();
int DummyOP_Path_Recover();
extern double selectFrequency(char* cFreq);
int LoadSignalSetting();

void Load_PPF();




//int Calc_RC_data(int Site_id,long long *Capwave,int *RC_Code,int *R_Code,int *C_Code);
//int Calc_RC_data(int Site_id,CSiteLong *Capwave,int *RC_Code,int *R_Code,int *C_Code);
//int Calc_RC_data(int Site_id,long long *Capwave,int *RC_Code,int *R_Code,int *C_Code);
int Calc_RC_data(int Site_id,long long *Capwave,CSiteLong *RC_Code,CSiteLong *R_Code,CSiteLong *C_Code);

//int Calc_PD_BUF(string Channel,int num,double *Force_Val);

int Calc_PD_BUF(string Channel,bool GPIO_Flag,int num,double *Force_Val);


int LoadSignal_MIX_DC(double Force_val,char *Signalname);

extern int Calc_Power_dbm(SpecAnResultAttribute *ResultAttribute, int Exp_Bin, int index_bin_num,double *Pre_Output_Power,double pathloss);

extern void Load_UltraWave_Cap_Signals(double WLAN_RX_5G_Band_Fre,char *Signalname);

extern int Write_RC_PPF(int TRX,char * channel);
extern int Write_RC_C_CODE(char * Channel);


extern void Write_SingleBand_PPF_Site(char *Channel,int Band,CSiteLong &PPF_Code);
extern int MWCapture_Signal(double CenterFrequency,double ReferenceLevel,long SampleNumbers,double SampleRate,char *Signalname);
void Calc_TX_Power_CR_maxSR(SpecAnResultAttribute *ResultAttribute,double Exp_Fre,double Lo,double *Power_Data,double *CR_Data,double *SR_Data);
int MWSource_Signal_CW(double Frequency,double PowerLevel,char *Signalname);

int LoadSignal_MIX_TX_2G_DC(double Force_val,char *Signalname);

void CosSin_Value();
int TestMUX_Init_Setup(emTRX TRX_Path_Select, char * Channel);
int Test_Mode_Init_Setup(emMode Mode_Select,emTRX TRX_Path_Select, char *Channel);
void Read_Pathloss(tyTestData Test_Data, double *pathloss) ;
//void Read_Limit(double *Lowlimit,double *Highlimit,char* Test_name[],int *Test_number,char* Units[]);
//void Read_Limit(double *Lowlimit,double *Highlimit,char *Test_name[],int *Test_number,char *Units[],int *Fail_Soft,int *Fail_Hard);
void Read_Limit(double *Lowlimit,double *Highlimit,vector<string> &Test_name,int *Test_number, vector<string> &Units,int *Fail_Soft,int *Fail_Hard);
//void Read_Limit_debug(double *Lowlimit,double *Highlimit,char (*Test_name)[30],int *Test_number,char (*Units)[30],int *Fail_Soft,int *Fail_Hard);

int resetDevice();
//void VI_DET_C0_Module();
int CapUtilitySites0();
int CapUtilitySites1();
int SrcUtilitySites0();
int SrcUtilitySites1();
int SplitIQData(IQMeasureAttribute *IQMeasData, double *Inreal, double *Inimag);
void RF_SWITCH_Control(string pinlist_3V3,string pinlist_0V);

void Globle_Array_Init();

LONGLONG start();
void end(LONGLONG stime,string cout_name);

#endif	/* USERDEF_H */



//CapUtilitySites0(api);
//
//CapUtilitySites1(api);
//
//SrcUtilitySites0(api);
//
//SrcUtilitySites1(api);
