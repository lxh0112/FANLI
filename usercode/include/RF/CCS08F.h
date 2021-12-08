/* 
 * File:   CCS08F.h
 * Author: Liang
 *
 * Created on 2020年8月14日, 下午2:33
 */
#pragma once
#ifndef CCS08F_H
#define	CCS08F_H


#include "CCRFMIX.h"




#include "CCUserCLK.h"

#define TEST_VSA
/***********************************************************************************************************************************/




class DLLAPI CCRFHardware
{
public:
    CCRFHardware();
    virtual ~CCRFHardware();
public:
    CCRFSRC RFSRC(ViConstString pszPinName);
    CCRFCAP RFCAP(ViConstString pszPinName);
    CCRFSRC MIXSRC(ViConstString pszPinName);
    CCRFCAP MIXCAP(ViConstString pszPinName);
    
    CCRFSRC DAQmxSRC(ViConstString pszPinName);
    CCRFCAP DAQmxCAP(ViConstString pszPinName);
    /* Analysis Only*/
    CCMxDemod MXDEMOD(ViConstString pszSignalName);
    /* GIFA*/
    CCUserClk CHANNEL(ViConstString pszChannelName);
    
    CCRF_STATUS Init(ViConstString pszMttxFilePath, ViConstString pszBlockName);
    CCRF_STATUS ActiveSites(ViConstString pszSites);
    CCRF_STATUS ActiveSites(unsigned int* pSites,unsigned int nSize);
    CCRF_STATUS SelectSites(ViConstString pszSites);
    void EnableDebugMode();
    void DisableDebugMode();
    const char* GetErrorInfo();
    
    CCRF_STATUS FlowEnd();
    CCRF_STATUS Close();
    CCRF_STATUS ClearAllSignalAttributes();
    
    CCRF_STATUS VST_SG_RunTask(const char* pszVSGPin,const char* pszVSGSignal);
    CCRF_STATUS VST_SA_RunTask(
        const char* pszVSAPin,\
        const char* pszVSASignal,\
        CCFetchType nType,\
        void* pResult);
};

DLLAPI ViReal64 ReadPathLoss(ViConstString pszCalibrationFilePath,ViConstString pszSignalPath,ViReal64 dFrequency,ViReal64 dPowerLevel);

extern CCRFHardware DLLAPI CCRFTester;
#endif	/* CCS08F_H */



