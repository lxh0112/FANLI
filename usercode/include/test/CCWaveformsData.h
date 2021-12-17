#pragma once
#ifndef CCWAVEFORMSDATA_H
#define	CCWAVEFORMSDATA_H

#include "CCSiteType.h"
#include "CCSiteType_Org.h"

extern "C" class DLLAPI CWaveformData
{
public:
    CWaveformData();
    CWaveformData(CWaveformData& waveformData);
    virtual ~CWaveformData();
    
public:
    ViInt32 FileImport(ViConstString pszWaveformPath);
    ViInt32 Size();
    ViInt32 operator [](ViInt32 nIndex);
private:
    void* pDataArray;
};
/*********************************************************************************/
extern "C" class DLLAPI CGainMode
{
public:
    CGainMode();
    ~CGainMode();
public:
    int Insert(const char* pszBand,const char* pszGainMode,double dValue);
    void Clear();
    int Size(const char* pszBand);
    int FindIndex(const char* pszBand,const char* pszGainMode);
    double Get(const char* pszBand,const char* pszGainMode);
    double Get(const char* pszBand,int nIndex);
private:
    void* pBandArray;      
};


/*********************************************************************************/
extern "C" class DLLAPI CSiteLong : public CSiteBase<ViInt64>
{
public:
    CSiteLong();
    ~CSiteLong();
};

extern "C"  class DLLAPI CSiteDouble : public CSiteBase<ViReal64>
{
public:
    CSiteDouble();
    ~CSiteDouble();
};

/*********************************************************************************/
#endif
