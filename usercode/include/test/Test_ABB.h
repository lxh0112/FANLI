/* 
 * File:   ABB_Test.h
 * Author: TRD-02
 *
 * Created on 2020年11月10日, 下午4:51
 */
#pragma once
#ifndef ABB_TEST_H
#define	ABB_TEST_H

#include "UserAPI.h" 
#include "D2S_ABB_Module.h"
#include "CCWaveformsData.h"
#include "DSP_test_ABB.h"

void ABB_ADC_CalStatus(std::string Channel,CSiteLong*cal_status,CSiteLong*cal_status_C1);
void ABB_ADC_CalStatus(std::string Channel,CSiteLong *cal_status,CSiteLong *cal_status_C1,int CalType,CSiteLong *COMP_CAL_CODE_A1,CSiteLong *COMP_CAL_CODE_A2,CSiteLong *COMP_CAL_CODE_A3,CSiteLong *COMP_CAL_CODE);
void ABB_ADC_PV_Cal(std::string Channel,CSiteLong* pReadValue,int CalType);
void ABB_ADC_CapCal_DC(std::string Channel,double SampleRate,CSiteLong *WL_ADC_CAP_STS,int CalType);



#endif	/* ABB_TEST_H */

