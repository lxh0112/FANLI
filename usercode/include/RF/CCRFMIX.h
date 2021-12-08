/* 
 * File:   CCS08FPins.h
 * Author: guiyuliang
 *
 * Created on 2020年8月31日, 下午8:02
 */
#pragma once
#ifndef CCRFMIX_H
#define	CCRFMIX_H



#include "CCSIGNAL.h"

/*********************************************************************/

class DLLAPI CCRFSRC
{
public:
    CCRFSRC();
    virtual ~CCRFSRC();
    CCSrcSignal SIGNAL(ViConstString pszSignalName);
protected:
    CCSrcSignal Signals;
};


class DLLAPI CCRFCAP
{
public:
    CCRFCAP();
    virtual ~CCRFCAP();
    CCCapSignal SIGNAL(ViConstString pszSignalName);
protected:
    CCCapSignal Signals;
};

#endif	/* CCRFMIX_H */

