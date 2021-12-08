/* 
 * File:   CCRfsaTypeDef.h
 * Author: Liang
 *
 * Created on 2020年8月17日, 下午5:26
 */

#pragma once

#ifndef CCRFSATYPEDEF_H
#define	CCRFSATYPEDEF_H

#include "CCResults.h"
#include "CCTesterDef.h"
#include "string.h"

typedef enum{
/*- CCRFSA_ATTR_AVERAGING_MODE Values -*/
 CCRFSA_VAL_NO_AVERAGING = 400,
 CCRFSA_VAL_RMS_AVERAGING,                        
 CCRFSA_VAL_VECTOR_AVERAGING,
 CCRFSA_VAL_PEAK_HOLD_AVERAGING,
 CCRFSA_VAL_MIN_HOLD_AVERAGING,
 CCRFSA_VAL_SCALAR_AVERAGING,
 CCRFSA_VAL_LOG_AVERAGING, 
}CCRFSA_AVERAGING_MODE;

#define NIRFSA_VAL_RISING_SLOPE                        1000

typedef struct{
    /* Specifies the channel from which the device monitors the trigger. NI-RFSA currently supports only 0 as the value of this attribute. */
    ViChar* pszIQPowerEdgeSource;
    /* Specifies whether the device asserts the trigger when the signal power is rising or falling. 
     * When you set the NIRFSA_ATTR_REF_TRIGGER_TYPE attribute to NIRFSA_VAL_IQ_POWER_EDGE, 
     * the device asserts the trigger when the signal power exceeds the specified level with the slope you specify.*/
    ViInt32 nIQPowerEdgeSlope;
    /* Specifies the power level, in dBm, at which the device triggers. 
     * The device asserts the trigger when the signal crosses the level specified by the value of this attribute, taking into consideration the specified slope. 
     * If you are using external gain, refer to the NIRFSA_ATTR_EXTERNAL_GAIN attribute for more information about how this attribute affects the I/Q power edge trigger level.
     */
    ViReal64 dwIQPowerEdgeLevel;
    /* Specifies the trigger delay time, in seconds. 
     * The trigger delay time is the length of time the IF digitizer waits after it receives the trigger before it asserts the Reference Event.
     */
    ViReal64 dwTriggerDelay;
    /* Specifies the number of pretrigger samples—the samples acquired before the Reference Trigger is received—to be acquired per record*/
    ViInt64 dwPreTriggerSamples;
    /* Specifies a time duration, in seconds, for which the signal must be quiet before the device arms the trigger. 
     * The signal is quiet when it is below the trigger level if the trigger slope, specified by the NIRFSA_ATTR_IQ_POWER_EDGE_REF_TRIGGER_SLOPE attribute, 
     * is set to NIRFSA_VAL_RISING_SLOPE or when it is above the trigger level if the trigger slope is set to NIRFSA_VAL_FALLING_SLOPE.
     * By default, this value is set to 0, which means the device does not wait for a quiet time before arming the trigger. 
     * This attribute is useful to trigger the acquisition on signals containing repeated bursts, but for which each burst may have large changes in signal power within itself. 
     * By configuring the minimum quiet time to the time between bursts, you can ensure that the trigger occurs at the beginning of a burst rather than at the signal power change within a burst.
     */
    ViReal64 dwTriggerMinQuietTimeDuration;
}IQPowerEdgeTrigger,*pIQPowerEdgeTrigger;

class CCMeasureSpectrumAttribute
{
public:
    CCMeasureSpectrumAttribute()
    {
        dReferenceLevel = 0.0;
        dCenterFrequency = 0.0;
        
        dwSampleRate = 0.0;
        dwSampleNumbers = 0.0;

        memset(dwPathLoss,0x00,sizeof(ViReal64)*MAX_SITE);
        nAveragingMode = CCRFSA_VAL_NO_AVERAGING;
        nAverageNumbers = 1;
    }
    CCMeasureSpectrumAttribute(const CCMeasureSpectrumAttribute& attr)
    {
        dReferenceLevel = attr.dReferenceLevel;
        dCenterFrequency = attr.dCenterFrequency;
        dwSampleRate = attr.dwSampleRate;
        dwSampleNumbers = attr.dwSampleNumbers;
        nAveragingMode = attr.nAveragingMode;
        nAverageNumbers = attr.nAverageNumbers;
        memcpy(dwPathLoss,attr.dwPathLoss,sizeof(ViReal64)*MAX_SITE);
    }
    CCMeasureSpectrumAttribute(const CCMeasureSpectrumAttribute* pAttr)
    {
        dReferenceLevel = pAttr->dReferenceLevel;
        dCenterFrequency = pAttr->dCenterFrequency;
        dwSampleRate = pAttr->dwSampleRate;
        dwSampleNumbers = pAttr->dwSampleNumbers;
        nAveragingMode = pAttr->nAveragingMode;
        nAverageNumbers = pAttr->nAverageNumbers;
        memcpy(dwPathLoss,pAttr->dwPathLoss,sizeof(ViReal64)*MAX_SITE);
    }

    
public:
     /* Specifies the expected total power, in dBm, of the RF input signal.*/
    ViReal64 dReferenceLevel;
    /* Specifies the center frequency in a spectrum acquisition. The value is expressed in hertz (Hz). \
     * The NI-RFSA device you use determines the valid range. \
     * Refer to your device specifications document for more information about frequency range.
     */
    ViReal64 dCenterFrequency;
    /* Specifies the span of a spectrum acquisition. The value is expressed in hertz (Hz).*/
    ViReal64 dwSampleNumbers;
    /* Specifies the resolution bandwidth of a spectrum acquisition. The value is expressed in hertz (Hz). \
     * Configure the type of resolution bandwidth with the NIRFSA_ATTR_RESOLUTION_BANDWIDTH_TYPE attribute.
     */
    ViReal64 dwSampleRate;
    /* Path Loss*/
    ViReal64 dwPathLoss[MAX_SITE];
    /* Specifies the averaging mode for the spectrum acquisition.*/
    CCRFSA_AVERAGING_MODE nAveragingMode;
    /* Specifies the number of acquisitions to average. 
     * The averaging process returns the final result after the number of averages is complete.
     */
    ViInt32 nAverageNumbers;
};


class CCMeasureIQAttribute
{
public:
    CCMeasureIQAttribute()
    {
        dReferenceLevel = 0.0;
        dCarrierFrequency = 0.0;
        dwNumberOfSamples = 0.0;
        dSampleRate = 0.0;
        dwCommonLevel = 0.0;
        memset(dwPathLoss,0x00,sizeof(ViReal64)*MAX_SITE);
        nTrigger = CCRF_TRIGGER_TYPE_NONE;
        
        IQTrigger.dwIQPowerEdgeLevel = 0;
        IQTrigger.dwPreTriggerSamples = 0;
        IQTrigger.dwTriggerDelay = 0;
        IQTrigger.dwTriggerMinQuietTimeDuration = 0;
        IQTrigger.nIQPowerEdgeSlope = NIRFSA_VAL_RISING_SLOPE;
        IQTrigger.pszIQPowerEdgeSource = VI_NULL;
    }
    CCMeasureIQAttribute(const CCMeasureIQAttribute& attr)
    {
        dReferenceLevel = attr.dReferenceLevel;
        dCarrierFrequency = attr.dCarrierFrequency;
        dwNumberOfSamples = attr.dwNumberOfSamples;
        dSampleRate = attr.dSampleRate;
        dwCommonLevel = attr.dwCommonLevel;
        memcpy(dwPathLoss,attr.dwPathLoss,sizeof(ViReal64)*MAX_SITE);
        IQTrigger = attr.IQTrigger;
        nTrigger = attr.nTrigger;
    }
    CCMeasureIQAttribute(const CCMeasureIQAttribute* pAttr)
    {
        dReferenceLevel = pAttr->dReferenceLevel;
        dCarrierFrequency = pAttr->dCarrierFrequency;
        dwNumberOfSamples = pAttr->dwNumberOfSamples;
        dSampleRate = pAttr->dSampleRate;
        dwCommonLevel = pAttr->dwCommonLevel;
        memcpy(dwPathLoss,pAttr->dwPathLoss,sizeof(ViReal64)*MAX_SITE);
        IQTrigger = pAttr->IQTrigger;
        nTrigger = pAttr->nTrigger;
    }
    
public:
    /* Specifies the expected total power, in dBm, of the RF input signal.*/
    ViReal64 dReferenceLevel;
    /* Specifies the carrier frequency, in hertz (Hz), of the RF signal to acquire. \
     * The RF vector signal analyzer tunes to this frequency. \
     * NI-RFSA may coerce this value based on hardware settings and downconversion settings.
     */
    ViReal64 dCarrierFrequency;
    /* Specifies the number of samples per record if numberOfSamplesIsFinite is set to VI_TRUE.*/
    ViInt64 dwNumberOfSamples;
    /* Specifies the I/Q rate for the acquisition. The value is expressed in samples per second (S/s).*/
    ViReal64 dSampleRate;
    /* Specifies the common-mode level presented at each differential input terminal.*/
    ViReal64 dwCommonLevel;
    /* Path Loss*/
    ViReal64 dwPathLoss[MAX_SITE];
    IQPowerEdgeTrigger IQTrigger;
    CCRFTRIGGERTYPE nTrigger;
};

/*************************************************************************************************/

/*Output Data*/
typedef struct{
     /* Returns the peak amplitude, of the averaged spectrum. When you set the RFMXSPECAN_ATTR_SPECTRUM_SPAN attribute to 0, this function returns the peak amplitude in the time domain power trace.*/
    ViReal64 dPeakAmplitude;
    /* Returns the frequency, in hertz (Hz), at the peak amplitude of the averaged spectrum. This parameter is not valid if you set the RFMXSPECAN_ATTR_SPECTRUM_SPAN attribute to 0.*/
    ViReal64 dPeakFrequency;
    /* Returns the measured average power, in dBm, at each time instance. Set the arraySize parameter to 0 to get the size of the y array. 
     * You can pass NULL for this parameter if you set the arraySize parameter to 0. 
     * If the y array is not large enough to hold all the samples, the function returns an error.
     */
    ViReal64* pPowerDataBuf;
    /* Returns power spectrum data. Allocate an array as large as dataArraySize.*/
    ViReal64* pSpectrumDataBuf;
    /* Returns additional information about the powerSpectrumData array. \
     * This information includes the frequency, in hertz (Hz), \
     * corresponding to the first element in the array, the frequency increment, in Hz, \
     * between adjacent array elements, and the number of spectral lines the function returned.
     */
    ViInt32 dwActualNumbers;
    /* start frequency*/
    ViReal64 dInitiaFrequency;
    /* RBW*/
    ViInt32 dwFrequencyIncrement;
}SpectrumMeasureAttribute,*pSpectrumMeasureAttribute;


typedef struct{
    /* Returns the acquired waveform. Allocate an NIComplexI16 array at least as large as numberOfSamples.*/
    ComplexNumber* pComplexData;
    /* Returns the timestamp, in seconds, of the first fetched sample that is comparable between records and acquisitions.*/
    ViReal64 absoluteInitialX;
    /* Returns a timestamp that corresponds to the difference, in seconds, between the first sample returned and the Reference Trigger location. \
     * The timestamp is zero if the Reference Trigger has not occurred.
     */
    ViReal64 relativeInitialX;
    /* Returns the time interval between data points in the acquired signal. The I/Q data sample rate is the reciprocal of this value.*/
    ViReal64 xIncrement;
    /* Returns an integer representing the number of samples in the waveform.*/
    ViInt64 actualSamples;
    /* Returns the offset to scale data, (b), in mx + b form.*/
    ViReal64 offset;
    /* Returns the gain to scale data, (m), in mx + b form.*/
    ViReal64 gain;
}IQMeasureAttribute,*pIQMeasureAttribute;

class DLLAPI CCSpectrumResults : public CCResultsArray<SpectrumMeasureAttribute>
{
public:
    CCSpectrumResults();
    ~CCSpectrumResults();
public:
    void RemoveAll();

};

class DLLAPI CCIQResults : public CCResultsArray<IQMeasureAttribute>
{
public:
    CCIQResults();
    ~CCIQResults();

public:
    void RemoveAll();

};

#endif	/* CCRFSATYPEDEF_H */

