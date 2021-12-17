/*
 * File:   Capture_Function.h
 * Author:
 *
 * Created on 2020年12月25日, 上午11:29
 */
#pragma once

#ifndef CAPTURE_FUNCTION_H
#define	CAPTURE_FUNCTION_H



#include "Systick.h"
#include "UserAPI.h"
#include "d2sProtocolSSI.h"
#include "string.h"

void DIO_Capture(int Site_id,std::string Pin,unsigned long *Cap_data);
//void DIO_Capture(std::string Pin, map<uint32_t, vector<uint8_t>> Cap_data);
long long D2S_GetValue(int Site_id,d2sProtocolSSI d2s_test,char *cReadFlag);
void Cal_Frequency_Undersampling(double fs,int *data,int originN,double &ft);





#endif
