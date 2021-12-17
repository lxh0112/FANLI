#include "UserAPI.h" 
#include "GetLog.h" 
#include "Excel.h"
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <cstdio>
//#include "CCGIFAFun.h"
#include "UserDef.h"
#include "CCS08F.h"
#include "Globle_Var.h"
#include <synchapi.h>

//using namespace MuTest;

#define NUM_SITES          2
#define PASS_FLAG          1
#define FAIL_FLAG          0
#define RESULT_BIN_FALT    1
#define RESULT_BIN_PASS    0
double * measures = {0},* measures1 = {0},* measures2 = {0};
double * hi_limit = {0},* lo_limit = {0},* hi_limit1 = {0},* lo_limit1 = {0},* hi_limit2 = {0},* lo_limit2 = {0};
int first_fail_flag[NUM_SITES]={0};
int first_fail_number[NUM_SITES]={0};


int CapUtilitySites0()
{
//    api->Set_loadboard_x_ubits(X_UBIT_NONE,X_UBIT_158 + X_UBIT_194 + X_UBIT_148 + X_UBIT_184 + X_UBIT_080 + X_UBIT_081);//S0&2-digitizer
    int UtilitySites0[6] = {158,194,80,81};
//    for(uint32_t j=0;j<256;j++)
//	{
//		TheInst.Util().SetRelayState(j, 1); //bihe-0,duankai-1
//	}
//    Sleep(2);

//    TheInst.Util().SetRelayState("CAP_K2,CAP_K4,CAP_K5,CAP_K6", PhxAPI::E_UTIL_STATE_OFF);

    for(uint32_t i=0;i<4;i++)
	{
		TheInst.Util().SetRelayState(UtilitySites0[i], 1); //bihe-0,duankai-1
	}
//    Sleep(2);

    return EXIT_SUCCESS;
}
int CapUtilitySites1()
{
	int UtilitySites1[6] = {158,194,80,81};
//	for(uint32_t j=0;j<256;j++)
//	{
//		TheInst.Util().SetRelayState(j, 1); //bihe-0,duankai-1
//	}
//	Sleep(2);

//	TheInst.Util().SetRelayState("CAP_K2,CAP_K4,CAP_K5,CAP_K6", PhxAPI::E_UTIL_STATE_ON);

	for(uint32_t i=0;i<4;i++)
	{
		TheInst.Util().SetRelayState(UtilitySites1[i], 0); //bihe-0,duankai-1

	}
//	Sleep(2);

//	api->Set_loadboard_x_ubits(X_UBIT_158 + X_UBIT_194 + X_UBIT_148 + X_UBIT_184 + X_UBIT_080 + X_UBIT_081, X_UBIT_NONE);//S1&3-digitizer
    return EXIT_SUCCESS;
}

int SrcUtilitySites0()
{
//    api->Set_loadboard_x_ubits(X_UBIT_NONE,X_UBIT_140 + X_UBIT_176 + X_UBIT_167 + X_UBIT_131);//S0&2-AWG
	int UtilitySites0[4] = {140,176,167,131};
//	for(uint32_t j=0;j<256;j++)
//	{
//		TheInst.Util().SetRelayState(j, 1); //bihe-0,duankai-1
//	}
//	Sleep(2);

	for(uint32_t i=0;i<4;i++)
	{
		TheInst.Util().SetRelayState(UtilitySites0[i], 1); //bihe-0,duankai-1

	}
//	Sleep(2);

    return EXIT_SUCCESS;
    
}
int SrcUtilitySites1()
{
//    api->Set_loadboard_x_ubits(X_UBIT_140 + X_UBIT_176 + X_UBIT_167 + X_UBIT_131, X_UBIT_NONE);//S1&3-AWG

    int UtilitySites1[4] = {140,176,167,131};
//	for(uint32_t j=0;j<256;j++)
//	{
//		TheInst.Util().SetRelayState(j, 1); //bihe-0,duankai-1
//	}
//	Sleep(2);

	for(uint32_t i=0;i<4;i++)
	{
		TheInst.Util().SetRelayState(UtilitySites1[i], 0); //bihe-0,duankai-1
	}
//	Sleep(2);

    return EXIT_SUCCESS;
}

void RF_SWITCH_Control(string pinlist_3V3,string pinlist_0V)
{

	string Switch_pin = "SW_U1_V1,SW_U1_V2,SW_U1_V3,SW_U2_V1,SW_U2_V2,SW_U2_V3,SW_U3_V1,SW_U3_V2,SW_U3_V3,SW_U4_V1,SW_U4_V2,SW_U4_V3";
	TheInst.PPMU().Pins(Switch_pin).SetClear();
	TheInst.PPMU().Pins(Switch_pin).SetMeasureType(PhxAPI::E_MEASURE)
									.SetIClampH(50e-3)
									.SetIClampL(-50e-3)
									.SetIRange(50e-3)
									.SetVForce(0)
									.SetMeasureMode(PhxAPI::E_DC_FV_MV)
									.Connect(true)
									.SetSampleSize(1)
									.SetWaitTime(0.1 *ms)//5ms
									.Measure();


	TheInst.PPMU().Pins(Switch_pin).SetClear();
	TheInst.PPMU().Pins(Switch_pin).SetMeasureType(PhxAPI::E_MEASURE)
									.SetIClampH(1e-9)
									.SetIClampL(-1e-9)
									.SetIRange(1e-9)
									.SetVForce(1e-9)
									.SetMeasureMode(PhxAPI::E_DC_FV_MV)
									.Connect(1)
									.SetSampleSize(1)
									.SetWaitTime(0.1 *ms)//5ms
									.Measure();
	TheInst.PPMU().Pins(Switch_pin).Connect(false).Apply();

	TheInst.PPMU().Pins(pinlist_3V3).SetMeasureType(PhxAPI::E_MEASURE)
									.SetIClampH(50e-3)
									.SetIClampL(-50e-3)
									.SetIRange(50e-3)
									.SetVForce(3.3)
									.SetMeasureMode(PhxAPI::E_DC_FV_MV)
									.Connect(true)
									.SetSampleSize(1)
									.SetWaitTime(0.1 *ms)//5ms
									.Measure();

	TheInst.PPMU().Pins(pinlist_0V).SetMeasureType(PhxAPI::E_MEASURE)
									.SetIClampH(50e-3)
									.SetIClampL(-50e-3)
									.SetIRange(50e-3)
									.SetVForce(0 *V)
									.SetMeasureMode(PhxAPI::E_DC_FV_MV)
									.Connect(true)
									.SetSampleSize(1)
									.SetWaitTime(0.1 *ms)//5ms
									.Measure();


}


