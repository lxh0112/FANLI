/* 
 * File:   CCTesterDef.h
 * Author: guiyuliang
 *
 * Created on 2020年9月15日, 上午9:00
 */
#pragma once

#ifndef CCTESTERDEF_H
#define	CCTESTERDEF_H

#include "ccivi.h"
#include "CCListTemplate.h"
#include "CCSiteType.h"

#define USE_THREAD_POOLS

#ifndef _CC_RFMX_SESSION_DEFINED_
#define _CC_RFMX_SESSION_DEFINED_
typedef void*   CCRFmxInstrHandle;
#endif

typedef ViStatus                CCRF_STATUS;

typedef void*                   TaskHandle;

#ifndef CCRF_R_ERROR
#define CCRF_R_ERROR            (ViStatus(-1))
#endif

#ifndef DLLAPI
#define DLLAPI                  __declspec(dllexport)
#endif

#define CC_RELEASE_BUF(P)   \
do                          \
{                           \
    if(P != VI_NULL)        \
    {                       \
        delete[] P;         \
        P = VI_NULL;        \
    }                       \
}while(0)                   \

#define MAX_DEV_NAME_SIZE       (16)
#define	MAX_SN_SIZE				(16)
#define MAX_NAME_SIZE           (64)
#define MAX_WAVEFORM_NAME_SIZE  (32)
#define MAX_PINNAME_SIZE        (32)
#define MAX_ERROR_SIZE          (2048)
#define MAX_TEMP_SIZE           (64)

/*- Values for attributes CCRFSG_ATTR_REF_CLOCK_SOURCE and CCRFSG_ATTR_PXI_CHASSIS_CLK10_SOURCE -*/
#define CCRFSG_VAL_ONBOARD_CLOCK_STR            "OnboardClock"
#define CCRFSG_VAL_REF_IN_STR                   "RefIn"
#define CCRFSG_VAL_PXI_CLK_STR                  "PXI_CLK"
#define CCRFSG_VAL_NONE_STR                     "None"
#define CCRFSG_VAL_REF_IN_2_STR                 "RefIn2"
#define CCRFSG_VAL_PXI_CLK_MASTER_STR           "PXI_ClkMaster"

#define VST_REF_CLK_SEL_SRC     (CCRFSG_VAL_PXI_CLK_STR) 

#ifndef MAX_SITE
#define MAX_SITE                		(8)
#endif

#define VST_POSITION_UNDEFINED          (0)
#define VST_POSITION_A                  (1)
#define VST_POSITION_B                  (2)

#define RFPM_VAL_SOURCE_PATH_DIRECT     (0)
#define RFPM_VAL_FIGS_PATH_UNSPECIFIED  (3)
#define DAQMX_MAX_SIZE                  (4)

#define RFPM_USE_NONE                   (0)
#define RFPM_USE_5530                   (1)
#define RFPM_USE_RS32                   (2)

typedef void* CCSysCfgResourceHandle;

typedef enum{
    CCVST_TYPE_INVALID = 0,
    CCVST_TYPE_5841,
    CCVST_TYPE_6955,
    CCVST_TYPE_5820,
    CCVST_TYPE_4463,
    CCVST_TYPE_4464, 
    CCVST_TYPE_GIFA,
    CCVST_TYPE_MAX,
}CCVSTTYPE;

#define   MULTISITE_FLAG    (0x5A)

typedef enum{
    //SG
    CCRFSG_TYPE = 0,
    CCMIXSG_TYPE,
    CCDAQMXSG_AUDIO_TYPE,
    //SA        
    CCRFSA_SPECTRUM_TYPE,
    CCRFSA_IQ_TYPE,
    CCRFSA_RFMX_WLAN,           //5820,5841
    CCRFSA_RFMX_DEMOD,
    CCRFSA_RFMX_SPECAN, 
    CCDAQMXSA_AUDIO_TYPE,
    CCRFSA_RFMX_GSM,  
    CCRFSA_RFMX_LTE,
    CCRFSA_RFMX_NR,
  
    CCRF_OBJ_MAX_SIZE,
}CCRFSGSATYPE;

#ifndef CCRFFetchType
#define CCRFFetchType
typedef enum{
    CCRFmx_SpecAn = 0,
    CCRFmx_Wlan,
    CCRFmx_Demod,
    CCDAQmx_Audio,
}CCFetchType;
#endif

typedef enum{
    CCRF_TRIGGER_TYPE_NONE = 0,
    CCRF_TRIGGER_TYPE_DIGITAL,
    CCRF_TRIGGER_TYPE_IQPOWEREDGE, 
    CCRF_TRIGGER_TYPE_SOFTWARE,
}CCRFTRIGGERTYPE;

typedef struct{
   ViReal32 real;
   ViReal32 imaginary;
}ComplexNumber;

#define RFMXINSTR_IQPOWER_EDGE_SOURCE_DEFAULT                                                       ("0")
        
// Values for RFMXWLAN_ATTR_TRIGGER_TYPE
#define RFMXINSTR_VAL_TRIGGER_TYPE_NONE                                                              0
#define RFMXINSTR_VAL_TRIGGER_TYPE_DIGITAL_EDGE                                                      1
#define RFMXINSTR_VAL_TRIGGER_TYPE_IQ_POWER_EDGE                                                     2
#define RFMXINSTR_VAL_TRIGGER_TYPE_SOFTWARE                                                          3

// Values for Boolean
#define CCRFMXINSTR_VAL_FALSE                                                                        0
#define CCRFMXINSTR_VAL_TRUE                                                                         1

// Values for RFMXWLAN_ATTR_IQ_POWER_EDGE_TRIGGER_SLOPE
#define RFMXINSTR_VAL_IQ_POWER_EDGE_RISING_SLOPE                                                     0
#define RFMXINSTR_VAL_IQ_POWER_EDGE_FALLING_SLOPE                                                    1

// Values for RFMXWLAN_ATTR_IQ_POWER_EDGE_TRIGGER_LEVEL_TYPE
#define RFMXINSTR_VAL_IQ_POWER_EDGE_TRIGGER_LEVEL_TYPE_RELATIVE                                      0
#define RFMXINSTR_VAL_IQ_POWER_EDGE_TRIGGER_LEVEL_TYPE_ABSOLUTE                                      1

// Values for RFMXWLAN_ATTR_TRIGGER_MINIMUM_QUIET_TIME_MODE
#define RFMXINSTR_VAL_TRIGGER_MINIMUM_QUIET_TIME_MODE_MANUAL                                         0
#define RFMXINSTR_VAL_TRIGGER_MINIMUM_QUIET_TIME_MODE_AUTO                                           1

//Rfmx Instr Trigger defined
typedef struct{
    /* Specifies the source terminal for the digital edge trigger. 
     * This parameter is used only when you set the RFMXWLAN_ATTR_TRIGGER_TYPE attribute to RFMXWLAN_VAL_TRIGGER_TYPE_DIGITAL_EDGE. 
     * The default value of this attribute is hardware dependent.
     */ 
    ViChar* pszDigitalEdgeSource;
    /* Specifies the active edge for the trigger. 
     * This parameter is used only when you set the RFMXWLAN_ATTR_TRIGGER_TYPE attribute to RFMXWLAN_VAL_TRIGGER_TYPE_DIGITAL_EDGE.
     */
    ViInt32 nDigitalEdge;
    /* Specifies the trigger delay time. This value is expressed in seconds.*/
    ViReal64 dTriggerDelay;
    /* Specifies whether to enable the trigger.*/
    ViInt32 nEnableTrigger;
}RfmxInstrDigitalEdgeTrigger,*pRfmxInstrDigitalEdgeTrigger;


typedef struct{
    /* Specifies the channel from which the device monitors the trigger.
     * This attribute is used only when you set the RFMXWLAN_ATTR_TRIGGER_TYPE attribute to RFMXWLAN_VAL_TRIGGER_TYPE_IQ_POWER_EDGE.
     * The default value of this attribute is hardware dependent. */
    ViChar* pszIQPowerEdgeSource;
    /* Specifies the power level at which the device triggers.*/
    ViReal64 dwIQPowerEdgeLevel;
    /* Specifies whether the device asserts the trigger when the signal power is rising or falling.
     * The device asserts the trigger when the signal power exceeds the specified level with the slope you specify.
     * This attribute is used only when you set the RFMXWLAN_ATTR_TRIGGER_TYPE attribute to RFMXWLAN_VAL_TRIGGER_TYPE_IQ_POWER_EDGE.
     */
    ViInt32 nIQPowerEdgeSlope;
    /* Specifies the trigger delay time. This value is expressed in seconds.*/
    ViReal64 dwTriggerDelay;
    /* Specifies whether the measurement computes the minimum quiet time used for triggering.*/
    ViInt32 nTriggerMinQuietTimeMode;
    /* Specifies the time duration for which the signal must be quiet before the signal analyzer arms the I/Q power edge trigger.
     * This value is expressed in seconds.*/
    ViReal64 dwTriggerMinQuietTimeDuration;
    /* Specifies the reference for the RFMXWLAN_ATTR_IQ_POWER_EDGE_TRIGGER_LEVEL parameter.
     * This parameter is used only when you set the RFMXWLAN_ATTR_TRIGGER_TYPE attribute to RFMXWLAN_VAL_TRIGGER_TYPE_IQ_POWER_EDGE. 
     */
    ViInt32 nIQPowerEdgeLevelType;
    /* Specifies whether to enable the trigger.*/
    ViInt32 nEnableTrigger;
}RfmxInstrIQPowerEdgeTrigger,*pRfmxInstrIQPowerEdgeTrigger;

typedef struct{
    /* Specifies the trigger delay time. This value is expressed in seconds.*/
    ViReal64 dTriggerDelay;
    /* Specifies whether to enable the trigger.*/
    ViInt32 nEnableTrigger;
}RfmxInstrSoftwareEdgeTrigger,*pRfmxInstrSoftwareEdgeTrigger;

typedef struct{
    //
    ViInt16 nTriggerType;
    RfmxInstrIQPowerEdgeTrigger IQPowerEdgeTrigger;
    RfmxInstrDigitalEdgeTrigger DigitalEdgeTrigger;
    RfmxInstrSoftwareEdgeTrigger SoftwareEdgeTrigger;
}RfmxInstrTrigger;

typedef struct{
    /*Specifies the measurements to perform*/
    ViInt32 nMeasurements;
    /*Specifies whether to enable all the traces for the selected measurement*/
    ViInt32 nEnableAllTraces;
}SelectMeasurementTypeAttribute, *pSelectMeasurementTypeAttribute;


#pragma pack(4)
typedef struct{
    ViChar szProductName[MAX_DEV_NAME_SIZE];
    ViChar szLinkName[MAX_DEV_NAME_SIZE];
    ViChar szSerialNumber[MAX_SN_SIZE];
    bool bIsActived;
    
    ViUInt16 nBusNumber;
    ViUInt8 nVstPosition;
    CCVSTTYPE vstType;
    
    ViSession rfsgSession;
    ViSession rfsaSession;
    CCRFmxInstrHandle rfmxInstrSession;
    ViSession rfpmSwitchSession;
    ViSession rfpmSession;
    
    TaskHandle hAudioTask[DAQMX_MAX_SIZE];
}CCVSTAttribute,*pCCVSTAttribute;

typedef struct{
    ViUInt16 nBusNumber;
    ViUInt8 nVstPosition;
    CCVSTTYPE vstType;
    ViSession rfsgSession;
    ViSession rfsaSession;
    CCRFmxInstrHandle rfmxInstrSession;
    ViSession rfpmSwitchSession;
    ViSession rfpmSession;
    TaskHandle hAudioTask;
    
    ViChar* pszLinkName;
    ViUInt8 nSelectedPort;
    ViUInt8 nSiteNum;
}CCVSTSelectedAttribute,*pCCVSTSelectedAttribute;

typedef struct{
    CCVSTTYPE vstType;
    CCRFSGSATYPE opType;
    ViUInt8 nMultiFlag;
    void* vptrCfg;
}CCSignalAttribute,*pCCSignalAttribute;
#pragma pack()

typedef struct{
    ViUInt8 nAllSite;
    ViUInt8 nUserSite;
    ViUInt8 nMergeSite;
    ViUInt8 nSiteNum;
    ViUInt8 siteNo[MAX_SITE];
}CCSiteState,*pCCSiteState;


#endif	/* CCTESTERDEF_H */

