// -*- C++ -*-
/* 
 * File:   GetLog.h
 * Author: Administrator
 *
 * Created on 2020年12月12日, 下午1:58
 */

#ifndef GETLOG_H
#define	GETLOG_H

#include "UserAPI.h"
#include "CCWaveformsData.h"
////using namespace MuTest;
enum TMResult {
    TM_PASS,    ///<Test passed. 
    TM_FAIL,    ///<Test failed. 
    TM_NOTEST  ///<Test was not executed. 
};

//TMResult ValueTest (const char *Pin, const double &Value, const double &LowLimit, const double &HighLimit, const char *Units, const char *Comment, const char *FailBin, const unsigned int &MinorId ,int mark, const bool &CLOGEnable);

TMResult ValueTest (const int &site_id, const char *Pin, const double &Value,const double &LowLimit, const double &HighLimit, const char *Units, const char *Comment, const char *FailBin, const unsigned int &MinorId, const bool &CLOGEnable);

TMResult ValueTest (const int &site_id, const char *Pin, const int &Value, const int &LowLimit, const int &HighLimit, const char *Units, const char *Comment, const char *FailBin, const unsigned int &MinorId, const bool &CLOGEnable);

//TMResult ValueTest (const char *Pin, const int &Value,const double &LowLimit, const double &HighLimit, const char *Units, const char *Comment, const char *FailBin, const unsigned int &MinorId, const bool &CLOGEnable);

#endif	/* GETLOG_H */

