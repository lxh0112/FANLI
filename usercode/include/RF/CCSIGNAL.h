/* 
 * File:   CCSIGNAL.h
 * Author: guiyuliang
 *
 * Created on 2020年9月1日, 下午4:06
 */
#pragma once
#ifndef CCSIGNAL_H
#define	CCSIGNAL_H

#include "CCRfsgTypeDef.h"
#include "CCRfsaTypeDef.h"
#include "CCRfmxWlanTypeDef.h"
#include "CCRfmxDemodTypeDef.h"
#include "CCRfmxSpecAnTypeDef.h"
#include "CCDAQmxStructDef.h"
#include "CCRfmxGsmTypeDef.h"
#include "CCRfmxLteTypeDef.h"
#include "CCRfmxNrTypeDef.h"

#define MAX_RFPM_PATH_MSG_SIZE    (100)
/**************************************************************************************************/
class CCSignalBase
{
public:
    CCSignalBase();
public:
    DLLAPI CCRF_STATUS DeleteSignalAttribute();
    CCRF_STATUS TestSite(ViInt16 nNum);
protected:
    CCRF_STATUS LoadWaveformIntoVST(CCVSTTYPE nVST,ViConstString pszWaveformPath,ViChar* pszWaveformName,ViBoolean bDPD = VI_FALSE);
    CCRF_STATUS DownloadPlaybackWaveform(ViSession rfsgSession,ViConstString pszFilePath,ViConstString pszWaveformName,ViBoolean bDPD = VI_FALSE);
    CCRF_STATUS DeletePlaybackWaveform(ViSession rfsgSession,ViConstString pszWaveformName);
};
/**************************************************************************************************/
class DLLAPI CCSrcSignal:public CCSignalBase
{
public:
    CCRF_STATUS AddSignalAttribute(CCSingleToneAttribute* vptrCfg);
    CCRF_STATUS AddSignalAttribute(CCMultiSiteSingleToneAttribute vptrCfg);
    CCRF_STATUS AddSignalAttribute(CCModulationAttribute* vptrCfg);
    CCRF_STATUS AddSignalAttribute(CCMultiSiteModulationAttribute cfgSiteMod);
    CCRF_STATUS AddSignalAttribute(CCMixAttribute* vptrCfg);    
    CCRF_STATUS AddSignalAttribute(CCDAQmxsgSignalAttribute* vptrCfg);

    CCRF_STATUS Update(CCRFSITE_DOUBLE dSiteFreq,CCRFSITE_DOUBLE dSiteLevel);
    
    CCRF_STATUS Configure();
    CCRF_STATUS Start();
    CCRF_STATUS Stop();
};

class DLLAPI CCCapSignal:public CCSignalBase
{
public:
    CCRF_STATUS AddSignalAttribute(CCMeasureSpectrumAttribute* vptrCfg);
    CCRF_STATUS AddSignalAttribute(CCMeasureIQAttribute* vptrCfg);
    CCRF_STATUS AddSignalAttribute(CCRFmxWlanStruct* vptrCfg);
    CCRF_STATUS AddSignalAttribute(CCRFmxDemodAttribute* vptrCfg);
    CCRF_STATUS AddSignalAttribute(CCRFmxSpecAnAttribute* vptrCfg);
    CCRF_STATUS AddSignalAttribute(CCMultiSiteRFmxSpecAnAttribute cfgSiteSpecAn);
    CCRF_STATUS AddSignalAttribute(CCDAQmxMeasureAttribute* vptrCfg);
    CCRF_STATUS AddSignalAttribute(CCRFmxGsmAttribute* vptrCfg);
    CCRF_STATUS AddSignalAttribute(CCRFmxLteAttribute* vptrCfg);
    CCRF_STATUS AddSignalAttribute(CCRFmxNrAttribute* vptrCfg);
    
    CCRF_STATUS Update(CCRFSITE_DOUBLE dSiteFreq,CCRFSITE_DOUBLE dSiteLevel);
    CCRF_STATUS Configure();
    CCRF_STATUS Start();
    CCRF_STATUS Stop();
    CCRF_STATUS Read(CCSpectrumResults* vptrResults);
    CCRF_STATUS Read(CCIQResults* vptrResults);
    CCRF_STATUS Read(CCMxWlanResults* vptrResults);
    CCRF_STATUS Read(CCMxDemodResults* vptrResults);
    CCRF_STATUS Read(CCRfmxSpecAnResults* vptrResults);
    CCRF_STATUS Read(CCFetchAudioResults* vptrResults);
    CCRF_STATUS Read(CCMxGsmResults* vptrResults);
    CCRF_STATUS Read(CCRfmxLteResults* vptrResults);
    CCRF_STATUS Read(CCRfmxNrResults* vptrResults);
private:
    CCRF_STATUS ReadResult(void* vptrResults);
};

class DLLAPI CCMxDemod:public CCSignalBase
{   
public:
    CCRF_STATUS Configure();
    CCRF_STATUS Load(const CCSpectrumResults* pResults,ViUInt8 nSiteNum);
    CCRF_STATUS Load(const CCIQResults* pResults,ViUInt8 nSiteNum);
    CCRF_STATUS Fetch(ViUInt8 nSiteNum,CCMxWlanResults* pWlanResults);
    CCRF_STATUS Create();
    CCRF_STATUS Close();
private:
    CCRFSGSATYPE typeOption;
    CCRF_STATUS LoadRawData(void* vptrResults,ViUInt8 nSiteNum);
};
#endif	/* CCSIGNAL_H */

