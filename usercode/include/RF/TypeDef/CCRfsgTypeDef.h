/* 
 * File:   CCRfsgTypeDef.h
 * Author: Liang
 *
 * Created on 2020年8月14日, 下午3:21
 */
#pragma once

#ifndef CCRFSGTYPEDEF_H
#define	CCRFSGTYPEDEF_H

#include "CCTesterDef.h"
#include "string.h"

#define MAX_MODEL_CHAR_SIZE                     (64)

class CCRFSGCfgBase
{
public:
    CCRFSGCfgBase()
    {
        dwFrequency = 1E9;
        dwPowerLevel = -50;
        dwLoOffset = 0.0;
        bDPDFlag = VI_FALSE;
        memset(dwPathLoss,0x00,sizeof(dwPathLoss));
        memset(szWaveformName,0x00,sizeof(szWaveformName));
        nTrigger = CCRF_TRIGGER_TYPE_NONE;
    }
public:
    union
    {
        /* Specifies the frequency of the generated RF signal, in hertz. Units: hertz (Hz).*/
        ViReal64 dwFrequency;
        /* Specifies the frequency of the generated RF signal, in hertz. Units: hertz (Hz) */
        ViReal64 dwCarrierFrequency;
    };
    /* Specifies either the average power level or peak power level of the generated RF signal. Units: dBm.*/
    ViReal64 dwPowerLevel;
    /* Path Loss*/
    ViReal64 dwPathLoss[MAX_SITE];
    /* This attribute offsets the NIRFSG_ATTR_UPCONVERTER_CENTER_FREQUENCY from the RF frequency. 
        Use this attribute to keep the local oscillator (LO) leakage at a determined offset from the RF signal.
        You cannot set the NIRFSG_ATTR_UPCONVERTER_CENTER_FREQUENCY attribute or the NIRFSG_ATTR_ARB_CARRIER_FREQUENCY 
        attribute at the same time as the NIRFSG_ATTR_UPCONVERTER_FREQUENCY_OFFSET attribute.
        Resetting this attribute disables the upconverter frequency offset.
    */
    ViReal64 dwLoOffset;

    ViBoolean bDPDFlag;
    /* Waveform name */
    ViChar szWaveformName[MAX_NAME_SIZE];
    CCRFTRIGGERTYPE nTrigger;
};

class CCSingleToneAttribute : public CCRFSGCfgBase
{
public:
    CCSingleToneAttribute()
    {
        pszLOSource = (ViChar*)"";
        bOutLOEnabled = VI_FALSE;
    }
    CCSingleToneAttribute(const CCSingleToneAttribute& attr)
    {
        dwFrequency = attr.dwFrequency;
        dwPowerLevel = attr.dwPowerLevel;
        dwLoOffset = attr.dwLoOffset;
        nTrigger = attr.nTrigger;
        pszLOSource = attr.pszLOSource;
        memcpy(dwPathLoss,attr.dwPathLoss,sizeof(dwPathLoss));
        memcpy(szWaveformName,attr.szWaveformName,sizeof(szWaveformName));
        bOutLOEnabled = attr.bOutLOEnabled;
        bDPDFlag = attr.bDPDFlag;
    }
    
    CCSingleToneAttribute(const CCSingleToneAttribute* pAttr)
    {
        dwFrequency = pAttr->dwFrequency;
        dwPowerLevel = pAttr->dwPowerLevel;
        dwLoOffset = pAttr->dwLoOffset;
        nTrigger = pAttr->nTrigger;
        pszLOSource = pAttr->pszLOSource;
        memcpy(dwPathLoss,pAttr->dwPathLoss,sizeof(dwPathLoss));
        memcpy(szWaveformName,pAttr->szWaveformName,sizeof(szWaveformName));
        bOutLOEnabled = pAttr->bOutLOEnabled;
        bDPDFlag = pAttr->bDPDFlag;
    }
    
public:
    /* Specifies whether to use the internal or external local oscillator (LO) source. 
     * If the NIRFSG_ATTR_LO_SOURCE attribute is set to "" (empty string), NI-RFSG uses the internal LO source. 
     * To set this attribute, the NI-RFSG device must be in the Configuration state.
     */
    ViChar* pszLOSource;
    /* Specifies whether the local oscillator signal is present at the LO OUT front panel connector. 
     * The local oscillator signal remains at the LO OUT front panel connector until this attribute is set to VI_FALSE, 
     * even if the NIRFSG_ATTR_OUTPUT_ENABLED attribute is set to VI_FALSE, 
     * the niRFSG_Abort function is called, or the NI-RFSG session is closed.*/
    ViBoolean bOutLOEnabled;
};

class CCModulationAttribute : public CCRFSGCfgBase
{
public:
    CCModulationAttribute()
    {
        pszFilePath = VI_NULL;
        pszLOSource = (ViChar*)"";
        bOutLOEnabled = VI_FALSE;
    }
    CCModulationAttribute(const CCModulationAttribute& attr)
    {
        dwCarrierFrequency = attr.dwCarrierFrequency;
        dwPowerLevel = attr.dwPowerLevel;
        dwLoOffset = attr.dwLoOffset;
        pszFilePath = attr.pszFilePath;
        memcpy(dwPathLoss,attr.dwPathLoss,sizeof(dwPathLoss));
        memcpy(szWaveformName,attr.szWaveformName,sizeof(szWaveformName));
        nTrigger = attr.nTrigger;
        pszLOSource = attr.pszFilePath;
        bOutLOEnabled = attr.bOutLOEnabled;
        bDPDFlag = attr.bDPDFlag;
    }
    CCModulationAttribute(const CCModulationAttribute* pAttr)
    {
        dwCarrierFrequency = pAttr->dwCarrierFrequency;
        dwPowerLevel = pAttr->dwPowerLevel;
        dwLoOffset = pAttr->dwLoOffset;
        pszFilePath = pAttr->pszFilePath;
        memcpy(dwPathLoss,pAttr->dwPathLoss,sizeof(dwPathLoss));
        memcpy(szWaveformName,pAttr->szWaveformName,sizeof(szWaveformName));
        nTrigger = pAttr->nTrigger;
        pszLOSource = pAttr->pszFilePath;
        bOutLOEnabled = pAttr->bOutLOEnabled;
        bDPDFlag = pAttr->bDPDFlag;
    }
    
    CCModulationAttribute(const CCSingleToneAttribute* pAttr)
    {
        dwCarrierFrequency = pAttr->dwFrequency;
        dwPowerLevel = pAttr->dwPowerLevel;
        dwLoOffset = pAttr->dwLoOffset;
        memcpy(dwPathLoss,pAttr->dwPathLoss,sizeof(dwPathLoss));
        memcpy(szWaveformName,pAttr->szWaveformName,sizeof(szWaveformName));
        nTrigger = pAttr->nTrigger;
        pszLOSource = pAttr->pszLOSource;
        bOutLOEnabled = pAttr->bOutLOEnabled;
        bDPDFlag = pAttr->bDPDFlag;
    }
    
public:
    ViChar* pszFilePath;
    /* Specifies whether to use the internal or external local oscillator (LO) source. 
     * If the NIRFSG_ATTR_LO_SOURCE attribute is set to "" (empty string), NI-RFSG uses the internal LO source. 
     * To set this attribute, the NI-RFSG device must be in the Configuration state.
     */
    ViChar* pszLOSource;
    /* Specifies whether the local oscillator signal is present at the LO OUT front panel connector. 
     * The local oscillator signal remains at the LO OUT front panel connector until this attribute is set to VI_FALSE, 
     * even if the NIRFSG_ATTR_OUTPUT_ENABLED attribute is set to VI_FALSE, 
     * the niRFSG_Abort function is called, or the NI-RFSG session is closed.*/
    ViBoolean bOutLOEnabled;
};

class CCMixAttribute : public CCRFSGCfgBase
{
public:
    CCMixAttribute()
    {
        dwCommonModeOffset = 0;
        pszFilePath = VI_NULL;
        dwLoadImpedance = 2E6;
    }
    CCMixAttribute(const CCMixAttribute& attr)
    {
        dwPowerLevel = attr.dwPowerLevel;
        dwCommonModeOffset = attr.dwCommonModeOffset;
        bDPDFlag = attr.bDPDFlag;
        pszFilePath = attr.pszFilePath;
        dwLoadImpedance = attr.dwLoadImpedance;
        memcpy(dwPathLoss,attr.dwPathLoss,sizeof(dwPathLoss));
        memcpy(szWaveformName,attr.szWaveformName,sizeof(szWaveformName));
        nTrigger = attr.nTrigger;
    }
    CCMixAttribute(const CCMixAttribute* pAttr)
    {
        dwPowerLevel = pAttr->dwPowerLevel;
        dwCommonModeOffset = pAttr->dwCommonModeOffset;
        bDPDFlag = pAttr->bDPDFlag;
        pszFilePath = pAttr->pszFilePath;
        dwLoadImpedance = pAttr->dwLoadImpedance;
        memcpy(dwPathLoss,pAttr->dwPathLoss,sizeof(dwPathLoss));
        memcpy(szWaveformName,pAttr->szWaveformName,sizeof(szWaveformName));
        nTrigger = pAttr->nTrigger;
    }
public:
    /* Specifies the common-mode offset applied to the signals generated at each differential output terminal.*/
    ViReal64 dwCommonModeOffset;
    /* Specifies the absolute path to the TDMS file from which the playback library reads the waveforms.*/
    ViChar* pszFilePath;
    /* Specifies the load impedance connected to the I/Q OUT port. 
     * 50 ohm if you set the NIRFSG_ATTR_IQ_OUT_PORT_TERMINAL_CONFIGURATION attribute to NIRFSG_VAL_SINGLE_ENDED, 
     * 100 ohm if you set the NIRFSG_ATTR_IQ_OUT_PORT_TERMINAL_CONFIGURATION attribute to NIRFSG_VAL_DIFFERENTIAL.
     * Values greater than or equal to 1 megaohms (Mohm) are interpreted as high impedance.
     * PXIe-5820: The only valid value for attribute NIRFSG_ATTR_IQ_OUT_PORT_TERMINAL_CONFIGURATION is NIRFSG_VAL_DIFFERENTIAL. 
     * Units: Ohms
     */
    ViReal64 dwLoadImpedance;
};

typedef CCRFMultiSite<CCModulationAttribute> CCMultiSiteModulationAttribute;
typedef CCRFMultiSite<CCSingleToneAttribute> CCMultiSiteSingleToneAttribute;

#endif	/* CCRFSGTYPEDEF_H */

