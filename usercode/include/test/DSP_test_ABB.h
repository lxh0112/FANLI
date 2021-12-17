/* 
 * File:   DSP_test_ABB.h
 * Author: TRD-02
 *
 * Created on 2020年11月20日, 下午3:02
 */
#pragma once
#ifndef DSP_TEST_ABB_H
#define	DSP_TEST_ABB_H

#include "UserAPI.h"
#include "UserDef.h"
//#include "MT_DSP_Lib.h"
#include <vector>
#include <iostream>
#include "cmath"
#include <algorithm>
#include <numeric>
#include <sstream>
#include "CCS08F.h"
#include "RegDef.h"


void adcDynamicCalc(const unsigned &FundBin, double *data, const unsigned &samplesCount, long Divided_Num, double &snr_i,double &snr_q, double &thd_i,double &thd_q, double &sfdr_i,double &sfdr_q,
                        double &sinad_i, double &sinad_q,double &enob_i, double &enob_q, double &enob_iq, double &FullScalRange_i,double &FullScalRange_q, double &GainMismatch, const unsigned &distortion_num, const unsigned &SpurBin);


void dacDynamicCalc(const unsigned &FundBin, IQMeasureAttribute *IQMeasData, const unsigned &samplesCount, double &FullScalRange_i, double &FullScalRange_q, double &dc_offset_i, double &dc_offset_q,
                      double &snr_i, double &snr_q, double &thd_i, double &thd_q, double &sfdr_i, double &sfdr_q, double &sinad_i, double &sinad_q, double &enob_i, double &enob_q, double &GainMismatch, const unsigned &distortion_num);
//void dacStaticCalc(API * api, double *Data, const unsigned &samplesCount,double &offset, double &fsr, double &inl, double &dnl, unsigned &monotonic, STATIC_ANALYSIS_TYPE AnalysisType);
//void adcStaticCalc(API * api, int *Data, const unsigned &samplesCount, const double &Vo_in, const double &Vn_in, const int &AdcBits, 
//                   double &offset, double &gain, double &inl, double &dnl, unsigned &missingCode);


#endif	/* DSP_TEST_ABB_H */

