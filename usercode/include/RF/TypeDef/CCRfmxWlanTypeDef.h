/* 
 * File:   CCRfmxWlanTypeDef.h
 * Author: Liang
 *
 * Created on 2020年8月17日, 下午3:37
 */
#pragma once

#ifndef CCRFMXWLANTYPEDEF_H
#define	CCRFMXWLANTYPEDEF_H

#include "CCResults.h"
#include "CCTesterDef.h"

// Values for RFMXWLAN_ATTR_STANDARD
#define RFMXWLAN_VAL_STANDARD_802_11_AG                                                             0
#define RFMXWLAN_VAL_STANDARD_802_11_B                                                              1
#define RFMXWLAN_VAL_STANDARD_802_11_J                                                              2
#define RFMXWLAN_VAL_STANDARD_802_11_P                                                              3
#define RFMXWLAN_VAL_STANDARD_802_11_N                                                              4
#define RFMXWLAN_VAL_STANDARD_802_11_AC                                                             5
#define RFMXWLAN_VAL_STANDARD_802_11_AX                                                             6
#define RFMXWLAN_VAL_STANDARD_UNKNOWN                                                               -1


// Values for MeasurementTypes
#define RFMXWLAN_VAL_TXP                                                                            1<<0
#define RFMXWLAN_VAL_POWERRAMP                                                                      1<<1
#define RFMXWLAN_VAL_DSSSMODACC                                                                     1<<2
#define RFMXWLAN_VAL_OFDMMODACC                                                                     1<<3
#define RFMXWLAN_VAL_SEM                                                                            1<<4

/****************************************************************************************************/   
typedef struct{
    /* Specifies the center frequency.
     * This value is expressed in Hz. 
     * The default of this attribute is hardware dependent.*/
    ViReal64 dwCarrierFrequence;
    /* Specifies the attenuation of a switch (or cable) connected to the RF IN connector of the signal analyzer. 
     * This value is expressed in dB. */
    ViReal64 dwExternalAttenuation;
    /* Specifies the reference level which represents the maximum expected power of the RF input signal. 
     * This value is expressed in dBm for RF devices and Vpk-pk for baseband devices.
     * The default value of this attribute is hardware dependent.*/
    ViReal64 dwReferenceLevel;
    /* Specifies the signal under analysis as defined under IEEE Standard 802.11.*/
    ViInt32 nWlanStandard;
    /* Specifies the channel spacing as defined in section 3.1 of IEEE Standard 802.11-2016 (pp. 130). This value is expressed in Hz. */
    ViReal64 dChannelBandwidth;
    /*Specifies the measurement type*/
    SelectMeasurementTypeAttribute SelectMeasurement;
    /* Path Loss*/
    ViReal64 dwPathLoss[MAX_SITE];
    RfmxInstrTrigger trigger;   
}RfmxWlanField,*pRfmxWlanField;


typedef struct{
    /* Specifies whether to enable averaging for OFDMModAcc measurements. 
     * RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_FALSE (0)  The measurement is performed on a single acquisition. 
     * RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE (1)   The measurement uses the value of the averagingCount parameter as the number of acquisitions over which the results are averaged. 
     */
    ViInt32 nAveragingEnabled;
    /* Specifies the number of acquisitions used for averaging when you set the averagingEnabled parameter to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE.*/
    ViInt32 nAveragingCount;
}WLANAveragingAttribute,*pWLANAveragingAttribute;

typedef struct{
    /* Specifies whether the measurement automatically computes the acquisition length of the waveform based on other OFDMModAcc attributes. 
     * The default value is RFMXWLAN_VAL_OFDMMODACC_ACQUISITION_LENGTH_MODE_AUTO. 
     * RFMXWLAN_VAL_OFDMMODACC_ACQUISITION_LENGTH_MODE_MANUAL (0)   Uses the acquisition length specified by the OFDMModAcc Acquisition Length attribute. 
     * RFMXWLAN_VAL_OFDMMODACC_ACQUISITION_LENGTH_MODE_AUTO (1)     Computes the acquisition length based on the OFDMModAcc Meas Offset and the OFDMModAcc Max Meas Length attributes.
     */
    ViInt32 nAcquisitionLengthMode;
    /* Specifies the length of the waveform to be acquired for the OFDMModAcc measurement when you set the acquisitionLengthMode parameter to RFMXWLAN_VAL_OFDMMODACC_ACQUISITION_LENGTH_MODE_MANUAL. 
     * This value is expressed in seconds.*/
    ViReal64 dAcquisitionLength;
}AcquisitionLengthAttribute,*pAcquisitionLengthAttribute;

typedef struct{
    /* Specifies the number of data OFDM symbols to be ignored from the start of the data field for EVM computation.*/
    ViInt32 nMeasurementOffset;
    /* Specifies the maximum number of data OFDM symbols that the measurement uses to compute EVM.*/
    ViInt32 nMaximumMeasurementLength;
}MeasurementLengthAttribute,*pMeasurementLengthAttribute;

typedef struct{
    /* Specifies the array of start time of the custom power gates. 
     * This value is expressed in seconds. 
     * A value of 0 indicates that the start time is the start of the PPDU.
     */
    ViReal64* pStartTime;
    /* Specifies the array of stop time of the custom power gates. 
     * This value is expressed in seconds.
     */
    ViReal64* pStopTime;
    /* Specifies the number of elements in each array.*/
    ViInt32 nNumberOfElements;
}CustomGateArrayAttribute,*pCustomGateArrayAttribute;

typedef struct{
    /* Configures averaging for the DSSSModAcc measurement. */
    WLANAveragingAttribute Averaging;
    /* Configures EVM unit for the DSSSModAcc measurement.
     * Specifies the unit for the EVM results. 
     * RFMXWLAN_VAL_DSSSMODACC_EVM_UNIT_PERCENTAGE (0)  EVM results are returned in dB. 
     * RFMXWLAN_VAL_DSSSMODACC_EVM_UNIT_DB (1)          EVM results are returned in percentage. 
     */
    ViInt32 nEVMUnit;
    /* Configures the acquisition length mode and acquisition length of the waveform to be acquired for the DSSSModAcc measurement.*/
    AcquisitionLengthAttribute AcquisitionLength;
    /* Configures the measurement offset and maximum measurement length for the DSSSModAcc EVM measurements.*/
    MeasurementLengthAttribute MeasurementLength;
    /* Specifies if power measurement is performed. 
     * This measurement computes power of various fields in the PPDU. 
     * Additionally, this parameter computes power over the custom gates that 
     * you can configure using the RFMXWLAN_ATTR_DSSSMODACC_POWER_NUMBER_OF_CUSTOM_GATES, 
     * the DSSSModAcc Pwr Custom Gate Start Time and the DSSSModAcc Pwr Custom Gate Stop Time attributes. 
     * RFMXWLAN_VAL_DSSSMODACC_POWER_MEASUREMENT_ENABLED_FALSE (0)      Disables power measurement.
     * RFMXWLAN_VAL_DSSSMODACC_POWER_MEASUREMENT_ENABLED_TRUE (1)       Enables power measurement.
     */
    ViInt32 nPowerMeasurementEnabled;
    /* Specifies the number of custom gates used for power measurement. */
    ViInt32 nNumberOfCustomGates;
    /* Configures the custom gate start and stop times for power measurement. */
    CustomGateArrayAttribute PowerMeasurementCustomGateArray;
}RfmxWlanDSSSModAccAttribute,*pRfmxWlanDSSSModAccAttribute;

typedef struct{
    /* Specifies whether to optimize the analyzer’s dynamic range for the EVM measurement. 
     * This parameter computes optimum attenuation settings for the analyzer based on the reference level you specify while still avoiding ADC or onboard signal processing (OSP) overflow. 
     * When you specify the reference level and you notice an overflow error, you can increase the reference level or specify a margin above the reference level by configuring the optimizeDynamicRangeForEVMMargin parameter. 
     * Supported Devices: NI 5646R/NI 5840. 
     * The default value is RFMXWLAN_VAL_OFDMMODACC_OPTIMIZE_DYNAMIC_RANGE_FOR_EVM_ENABLED_FALSE.
     * RFMXWLAN_VAL_OFDMMODACC_OPTIMIZE_DYNAMIC_RANGE_FOR_EVM_ENABLED_FALSE (0) Specifies that Dynamic range is not optimized for EVM measurement. 
     * RFMXWLAN_VAL_OFDMMODACC_OPTIMIZE_DYNAMIC_RANGE_FOR_EVM_ENABLED_TRUE (1)  Specifies that Dynamic range is optimized for EVM measurement. 
     */
    ViInt32 nEnabled;
    /* Specifies the margin above the reference level you specify when you set the optimizeDynamicRangeForEVMEnabled parameter to RFMXWLAN_VAL_OFDMMODACC_OPTIMIZE_DYNAMIC_RANGE_FOR_EVM_ENABLED_TRUE. 
     * This value is expressed in dB. When the property's value is 0, 
     * the dynamic range is optimized. When you set a positive value to the property, the dynamic range reduces from the optimized dynamic range. 
     * You can use this property to avoid ADC and onboard signal processing (OSP) overflows. 
     * The default value is 0.*/
    ViReal64 dMargin;
    
}OptimizeDynamicRangeForEVMAttribute,*pOptimizeDynamicRangeForEVMAttribute;

typedef struct{
    /* Specifies whether to enable the estimation of I/Q gain imbalance, I/Q quadrature error, and I/Q timing skew impairments.*/
    ViInt32 nEstimationEnabled;
    /* Specifies whether to enable I/Q gain imbalance correction.*/
    ViInt32 nGainImbalanceCorrectionEnabled;
    /* Specifies whether to enable I/Q quadrature error correction.*/
    ViInt32 nQuadratureErrorCorrectionEnabled;
    /* Specifies whether to enable I/Q timing skew correction.*/
    ViInt32 nTimingSkewCorrectionEnabled;
    /* Specifies whether to estimate I/Q impairments independently for each subcarrier.*/
    ViInt32 nSubCarrierEnabled;
}CfgIQImpairmentsAttribute,*pCfgIQImpairmentsAttribute;


typedef struct{
    /* Specifies the fields in the PPDU used to estimate the channel frequency response. */
    ViInt32 nType;
    /* Specifies whether smoothing of the channel estimates is performed using a triangular-weighted moving average window across subcarriers.*/
    ViInt32 nSmoothingEnabled;
    /* Specifies the length of the triangular-weighted moving window across subcarriers that is used for averaging the channel estimate.
     * This attribute is used only when you set the RFMXWLAN_ATTR_OFDMMODACC_CHANNEL_ESTIMATION_SMOOTHING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_CHANNEL_ESTIMATION_SMOOTHING_ENABLED_TRUE. 
     * The window is always symmetrical about the subcarrier. The length of the window is reduced at the edges in order to keep it symmetrical. 
     * For a window length of L, the weights generated are 1, 2, 3, ..., (L+1)/2, ..., 3, 2, 1. For a fully occupied channel bandwidth, 
     * valid values are all odd numbers between 1 and half the number of subcarriers in the bandwidth, inclusive. 
     * For 802.11ax MU and trigger-based PPDU signals, the valid values are all odd numbers between 1 and the size of the smallest RU. 
     */
    ViInt32 nSmoothingLength;
    /* Specifies whether to use the legacy channel estimation field for combining with the reference channel frequency response.*/
    ViInt32 nLLTFEnabled;
}CfgChannelEstimationAttribute,*pCfgChannelEstimationAttribute;

typedef struct{
    /* Specifies whether power measurements are performed.
     * The measurement computes power of the various fields in the PPDU. Additionally, the measurement also computes power over the custom gates 
     * that you configure using RFMXWLAN_ATTR_OFDMMODACC_POWER_NUMBER_OF_CUSTOM_GATES, OFDMModAcc Pwr Custom Gate Start Time and OFDMModAcc Pwr 
     * Custom Gate Stop Time attributes.
     * Refer to ModAcc Power Measurement for more information about power measurements.
     * You do not need to use a selector string to configure or read this attribute for the default signal instance. 
     * Refer to the Selector Strings topic for information about the string syntax for named signals.
     * The default value is RFMXWLAN_VAL_OFDMMODACC_POWER_MEASUREMENT_ENABLED_FALSE.
     */
    ViInt32 nEnable;
    /* Specifies the number of custom gates for power measurement.
     * You do not need to use a selector string to configure or read this attribute for the default signal instance. 
     * Refer to the Selector Strings topic for information about the string syntax for named signals.
     * The default value is 0. 
     */
    ViInt32 nCustomGates;
    /* Specifies the start time of the custom power gate. This value is expressed in seconds.
     * A value of 0 indicates that the start time is the start of the PPDU. 
     * Use 'gate(n)' as the selector string to configure or read this attribute.
     * The default value is 0.
     */
    ViReal64 dStartTime;
    /* Specifies the stop time of the custom power gate, and must be greater than the corresponding OFDMModAcc Pwr Custom Gate Start Time attribute. 
     * This value is expressed in seconds.
     * Use 'gate(n)' as the selector string to configure this attribute.
     * The default value is 10 microseconds.
     */
     ViReal64 dStopTime;
}CfgPowerAttribute,*pCfgPowerAttribute;

typedef struct{
    /* Configures averaging for the OFDMModAcc measurement.*/
    WLANAveragingAttribute Averaging;
    /* Configures the measurement mode for the OFDMModAcc measurement. 
     * Specifies whether the measurement should calibrate the noise floor of the analyzer or perform the OFDMModAcc measurement. 
     * RFMXWLAN_VAL_OFDMMODACC_MEASUREMENT_MODE_MEASURE (0)                 The OFDMModAcc measurement is performed on the acquired signal. 
     * RFMXWLAN_VAL_OFDMMODACC_MEASUREMENT_MODE_CALIBRATE_NOISE_FLOOR (1)   The OFDMModAcc measurement measures the noise floor of the instrument across the frequency range of interest determined by the carrier frequency and channel bandwidth. 
     * In this mode, the measurement expects that the signal generator to be turned off and checks whether no signal power is detected at the RF In port of the analyzer beyond a certain threshold. 
     * All scalar results and traces are invalid in this mode. Even if the instrument noise floor is previously calibrated, the measurement performs all the required acquisitions and overwrites any pre-existing noise floor calibration data. 
     */
    ViInt32 nMeasurementMode;
    /* Configures EVM unit for the OFDMModAcc measurement.
     * Specifies the unit for the EVM results. 
     * RFMXWLAN_VAL_OFDMMODACC_EVM_UNIT_PERCENTAGE (0)  EVM results are returned in dB. 
     * RFMXWLAN_VAL_OFDMMODACC_EVM_UNIT_DB (1)          EVM results are returned in percentage. 
     */
    ViInt32 nEVMUnit;
    /* Configures the acquisition length mode and acquisition length of the waveform to be acquired for the OFDMModAcc measurement.*/
    AcquisitionLengthAttribute AcquisitionLength;
    /* Configures the measurement offset and maximum measurement length for the OFDMModAcc EVM measurements.*/
    MeasurementLengthAttribute MeasurementLength;
    /* Configures the frequency error estimation method for the OFDMModAcc measurement.
     * Specifies the PPDU fields that the measurement uses to estimate the carrier frequency error in the acquired signal. 
     * RFMXWLAN_VAL_OFDMMODACC_FREQUENCY_ERROR_ESTIMATION_METHOD_DISABLED (0)           Carrier frequency error is not computed and the corresponding result is returned as NaN. 
     * RFMXWLAN_VAL_OFDMMODACC_FREQUENCY_ERROR_ESTIMATION_METHOD_INITIAL_PREAMBLE (1)   Short and long training fields in the PPDU are used.
     * RFMXWLAN_VAL_OFDMMODACC_FREQUENCY_ERROR_ESTIMATION_METHOD_PREAMBLE (2)           Short and long training fields along with the SIGnal fields are used.
     * RFMXWLAN_VAL_OFDMMODACC_FREQUENCY_ERROR_ESTIMATION_METHOD_PREAMBLE_AND_PILOTS (3)  The short and long training fields, SIGnal fields, and the pilot subcarriers in the DATA field are used.
     * RFMXWLAN_VAL_OFDMMODACC_FREQUENCY_ERROR_ESTIMATION_METHOD_PREAMBLE_PILOTS_AND_DATA (4)  The short and long training fields, SIGnal fields, and all the subcarriers in the DATA field are used.
     */
    ViInt32 nFrequencyErrorEstimationMethod;
    /* Configures whether the transmitter uses the same reference clock signal for generating the RF carrier and for the symbol clock.
     * Specifies if the transmitter uses the same reference clock signal for generating the RF carrier and the symbol clock. 
     * RFMXWLAN_VAL_OFDMMODACC_COMMON_CLOCK_SOURCE_ENABLED_FALSE (0)    Specifies that the transmitter does not use a common reference clock. The OFDMModAcc measurement computes the symbol clock error and carrier frequency error independently. 
     * RFMXWLAN_VAL_OFDMMODACC_COMMON_CLOCK_SOURCE_ENABLED_TRUE (1)     Specifies that the transmitter uses a common reference clock. The OFDMModAcc measurement derives the symbol clock error from the configured center frequency and carrier frequency error.
     */
    ViInt32 nCommonClockSourceEnabled;
    /* Configures whether to enable pilot-based mean amplitude tracking per OFDM data symbol.
     * Specifies whether to enable pilot-based mean amplitude tracking per OFDM data symbol. Amplitude tracking is useful if the mean amplitude of the OFDM symbols in a PPDU varies over time. However, enabling tracking may degrade EVM because of attempts to track random amplitude distortions caused by additive noise and other distortions. 
     * RFMXWLAN_VAL_OFDMMODACC_AMPLITUDE_TRACKING_ENABLED_FALSE (0)     Amplitude tracking is disabled.
     * RFMXWLAN_VAL_OFDMMODACC_AMPLITUDE_TRACKING_ENABLED_TRUE (1)      Amplitude tracking is enabled. 
     */
    ViInt32 nAmplitudeTrackingEnabled;
    /* Configures whether to enable pilot-based common phase error correction per OFDM data symbol.
     * Specifies whether to enable pilot-based common phase error correction per OFDM data symbol. 
     * RFMXWLAN_VAL_OFDMMODACC_PHASE_TRACKING_ENABLED_FALSE (0)  Phase tracking is disabled. 
     * RFMXWLAN_VAL_OFDMMODACC_PHASE_TRACKING_ENABLED_TRUE (1)  Phase tracking is enabled. 
     */
    ViInt32 nPhaseTrackingEnabled;
    /* Configures whether to enable symbol clock error correction.
     * Specifies whether to enable symbol clock error correction. 
     * RFMXWLAN_VAL_OFDMMODACC_SYMBOL_CLOCK_ERROR_CORRECTION_ENABLED_FALSE (0)  Symbol clock error correction is disabled.
     * RFMXWLAN_VAL_OFDMMODACC_SYMBOL_CLOCK_ERROR_CORRECTION_ENABLED_TRUE (1)   Symbol clock error correction is enabled. 
     */
    ViInt32 nSymbolClockErrorCorrectionEnabled;
    /* Specifies whether the contribution of the instrument noise is compensated for EVM computation. 
     * RFMXWLAN_VAL_OFDMMODACC_NOISE_COMPENSATION_ENABLED_FALSE (0)     Disables instrument noise compensation for EVM results.
     * RFMXWLAN_VAL_OFDMMODACC_NOISE_COMPENSATION_ENABLED_TRUE (1)      Enables instrument noise compensation for EVM results 
     */
    ViInt32 nNoiseCompensationEnabled;
    /* Specifies whether to optimize analyzer’s dynamic range for the EVM measurement.*/
    OptimizeDynamicRangeForEVMAttribute OptimizeDynamicRangeForEVM;
    
    CfgIQImpairmentsAttribute IQImpairments;
    
    CfgChannelEstimationAttribute ChannelEstimation;
    
    CfgPowerAttribute Power;
}RfmxWlanOFDMModAccAttribute,*pRfmxWlanOFDMModAccAttribute;


typedef struct{
    /* Specifies whether to enable averaging for the SEM. 
     * RFMXWLAN_VAL_SEM_AVERAGING_ENABLED_FALSE (0)     The measurement is performed on a single acquisition. 
     * RFMXWLAN_VAL_SEM_AVERAGING_ENABLED_TRUE (1)      The measurement uses the averagingCount parameter as the number of acquisitions over which the results are averaged.
     */
    ViInt32 nEnabled;
    /* Specifies the number of acquisitions used for averaging when you set the averagingEnabled parameter to RFMXWLAN_VAL_SEM_AVERAGING_ENABLED_TRUE.*/
    ViInt32 nCount;
    /* Specifies the averaging type for averaging multiple spectrum acquisitions. The averaged spectrum is used for SEM measurement. 
     * RFMXWLAN_VAL_SEM_AVERAGING_TYPE_RMS (0)  The power spectrum is linearly averaged. RMS averaging reduces signal fluctuations but not the noise floor. 
     * RFMXWLAN_VAL_SEM_AVERAGING_TYPE_LOG (1)  The power spectrum is averaged in a logarithmic scale.
     * RFMXWLAN_VAL_SEM_AVERAGING_TYPE_SCALAR (2)  The square root of the power spectrum is averaged.
     * RFMXWLAN_VAL_SEM_AVERAGING_TYPE_MAXIMUM (3)  The peak power in the spectrum at each frequency bin is retained from one record to the next.
     * RFMXWLAN_VAL_SEM_AVERAGING_TYPE_MINIMUM (4)  The least power in the spectrum at each frequency bin is retained from one record to the next.
     */
    ViInt32 nType;
}SEMAveragingAttribute,*pSEMAveragingAttribute;


typedef struct{
    /* Specifies whether the sweep time for the SEM measurement is computed automatically by the measurement or is configured by you. 
     * RFMXWLAN_VAL_SEM_SWEEP_TIME_AUTO_FALSE (0)  The sweep time you configure using the sweepTime parameter is used as the sweep time for the SEM measurement.
     * RFMXWLAN_VAL_SEM_SWEEP_TIME_AUTO_TRUE (1)  The sweep time is computed automatically based on the configured standard. 
     */
    ViInt32 nAuto;
    /* Specifies the sweep time for the SEM measurement. 
     * This value is expressed in seconds. 
     * This parameter is ignored when you set the Sweep Time Auto parameter to RFMXWLAN_VAL_SEM_SWEEP_TIME_AUTO_FALSE. 
     * The default value is 1 ms.*/
    ViReal64 dInterval;
    
}SEMSweepTimeAttribute,*pSEMSweepTimeAttribute;

typedef struct{
    /* Specifies whether the frequency range of the spectrum used for the SEM measurement is computed automatically by the measurement or is configured by you. 
     * This parameter is applicable when you set the RFMXWLAN_ATTR_SEM_MASK_TYPE attribute to RFMXWLAN_VAL_SEM_MASK_TYPE_STANDARD. 
     * RFMXWLAN_VAL_SEM_SPAN_AUTO_FALSE (0)  The span you configure is used as the frequency range for the SEM measurement.
     * RFMXWLAN_VAL_SEM_SPAN_AUTO_TRUE (1)  The span is automatically computed based on the configured standard and bandwidth.
     */
    ViInt32 nAuto;
    /* Specifies the frequency range of the spectrum that is used for the SEM measurement. 
     * This value is expressed in Hz. 
     * This parameter is applicable only when you set the spanAuto parameter to RFMXWLAN_VAL_SEM_SPAN_AUTO_FALSE, 
     * and the RFMXWLAN_ATTR_SEM_MASK_TYPE attribute to RFMXWLAN_VAL_SEM_MASK_TYPE_STANDARD. */
    ViReal64 dSpan;
}SEMSpanAttribute,*pSEMSpanAttribute;

typedef struct{
    /* Specifies an array of offset start frequencies, relative to the carrier frequency. This value is expressed in Hz. */
    ViReal64* pOffsetStartFrequency;
    /* Specifies an array of offset stop frequencies, relative to the carrier frequency. This value is expressed in Hz.*/
    ViReal64* pOffsetStopFrequency;
    /* Specifies whether the offset segments present on one or both sides of the carrier. 
     
     * RFMXWLAN_VAL_SEM_OFFSET_SIDEBAND_NEGATIVE (0)    Configures a lower offset segment to the left of the carrier. 
     * RFMXWLAN_VAL_SEM_OFFSET_SIDEBAND_POSITIVE (1)    Configures an upper offset segment to the right of the carrier.
     * RFMXWLAN_VAL_SEM_OFFSET_SIDEBAND_BOTH (2)        Configures both negative and positive offset segments.
     */
    ViInt32* pOffsetSideband;
    /* Specifies the number of elements in each array.*/
    ViInt32 nNumberOfElements;
}SEMOffsetFrequencyAttribute,*pSEMOffsetFrequencyAttribute;

typedef struct{
    /* Specifies an array of relative power limits corresponding to the start frequencies of the offsets. 
     * The relative limits are relative to the peak power of the carrier. This value is expressed in dB. 
     */
    ViReal64* pRelativeLimitStart;
    /* Specifies an array of relative power limits corresponding to the stop frequencies of the offsets. 
     * The relative limits are relative to the peak power of the carrier. This value is expressed in dB. 
     */
    ViReal64* pRelativeLimitStop;
    /* Specifies the number of elements in each array.*/
    ViInt32 nNumberOfElements;
}SEMOffsetRelativeLimitAttribute,*pSEMOffsetRelativeLimitAttribute;

typedef struct{
    /* Configures averaging for the spectral emission mask (SEM) measurement.*/
    SEMAveragingAttribute Averaging;
    /* Configures the sweep time.*/
    SEMSweepTimeAttribute SweepTime;
    /* Configures the frequency range around the center frequency to be acquired for the SEM measurement.*/
    SEMSpanAttribute Span;
    /* Specifies whether the mask used for the SEM measurement is as per the standard or specified by you. 
     * RFMXWLAN_VAL_SEM_MASK_TYPE_STANDARD (0)  Mask limits are configured as per the standard, channel bandwidth, and band.
     * RFMXWLAN_VAL_SEM_MASK_TYPE_CUSTOM (1)  Mask limits are configured by you.
     */
    ViInt32 nMaskType;
    /* Specifies the number of SEM offset segments. */
    ViInt32 nNumberOfOffsets;
    /* Configures an array of offset start and stop frequencies and specifies whether the offsets are present on one side, 
     * or on both the sides of the carrier when you set the RFMXWLAN_ATTR_SEM_MASK_TYPE attribute to RFMXWLAN_VAL_SEM_MASK_TYPE_CUSTOM.
     */
    SEMOffsetFrequencyAttribute OffsetFrequencyArray;
    /* Configures an array of relative mask limits corresponding the start and stop frequencies of the offsets 
     * when you set the RFMXWLAN_ATTR_SEM_MASK_TYPE attribute to RFMXWLAN_VAL_SEM_MASK_TYPE_CUSTOM. 
     * The relative limits are relative to the peak power of the carrier.
     */
    SEMOffsetRelativeLimitAttribute OffsetRelativeLimitArray;
}RfmxWlanSEMAttribute,*pRfmxWlanSEMAttribute;


#ifdef _DSSS_
typedef struct{
    /* Specifies whether to enable averaging for DSSSModAcc measurements.*/
    ViInt32 nAveragingEnabled;
    /* Specifies the number of acquisitions used for averaging when you set the averagingEnabled parameter to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE.*/
    ViInt32 nAveragingCount;
    /* Specifies the unit for the EVM results.*/
    ViInt32 nEVMUnit;
    /* Specifies whether the measurement automatically computes the acquisition length of the waveform based on DSSSModAcc attributes.*/
    ViInt32 nAcquisitionLengthMode;
    /* Specifies the length of the waveform to be acquired for the DSSSModAcc measurement when you set the acquisitionLengthMode parameter 
     * to RFMXWLAN_VAL_DSSSMODACC_ACQUISITION_LENGTH_MODE_MANUAL.
     * This value is expressed in seconds.
     */
    ViReal64 dwAcquisitionLength;
    /* Specifies the number of data chips to be ignored from the start of the data field for the EVM computation. 
     * This value is expressed in chips.
     */
    ViInt32 nMeasurementOffset;
    /* Specifies the maximum number of data chips that the measurement uses to compute EVM. This value is expressed in chips.*/
    ViInt32 nMaximumMeasurementLength;
    /* Specifies if power measurement is performed. This measurement computes power of various fields in the PPDU.*/
    ViInt32 nPowerMeasurementEnabled;
    /* Specifies the number of custom gates used for power measurement.*/
    ViInt32 nNumberOfCustomGates;
    /* Specifies the array of start time of the custom power gates. This value is expressed in seconds.
     * A value of 0 indicates that the start time is the start of the PPDU.
     */
    ViReal64* pStartTime;
    /* Specifies the array of stop time of the custom power gates. This value is expressed in seconds.*/
    ViReal64* pStopTime;
    /* Specifies the number of elements in each array.*/
    ViInt32 nNumberOfElements;
    /* Specifies the type of pulse shaping filter used at the transmitter.*/
    ViInt32 nPulseShapingFilterType;
    /* Specifies the value of the filter roll-off when you set the Pulse Shaping Filter Type method to Raised Cosine or Root Raised Cosine. 
     * This method is ignored if you set the Pulse Shaping Filter Type method to Rectangular.
     */
    ViReal64 dPulseShapingFilterParameter; 
    /* Specifies the timeout, in seconds, for fetching the specified measurement.
     * Set this value to an appropriate time, longer than expected for fetching the measurement.
     * A value of -1 specifies that the function waits until the measurement is complete.
     */
    ViReal64 dwTimeout;
}RfmxWlanDSSSModAccAttribute,*pRfmxWlanDSSSModAccAttribute;
#endif

/****************************************************************************************************/

typedef struct{
    /*Returns the RMS EVM results of the burst. 
      When you set the RFMXWLAN_ATTR_DSSSMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE, \
      this result returns the mean of the RMS EVM computed for each averaging count. \
      This value is expressed as a percentage or in dB.
    */
    ViReal64 dRMSEVMMean;
    /* Returns the peak EVM results of the burst.
     * This value is expressed as a percentage or in dB.
     * This measurement is performed in accordance with section 16.3.7.9 of IEEE Standard 802.11-2016.
     * When you set the RFMXWLAN_ATTR_DSSSMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE,
     * this result returns the maximum of the peak EVM computed for each averaging count.
     */
    ViReal64 dPeakEVM80211_2016Maximum;
    /* Returns the peak EVM results of the burst.
     * This value is expressed as a percentage or in dB.
     * This measurement is performed in accordance with section 18.4.7.8 of IEEE Standard 802.11-2007.
     * When you set the RFMXWLAN_ATTR_DSSSMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE,
     * this result returns the maximum of the peak EVM computed for each averaging count.
     */
    ViReal64 dPeakEVM80211_2007Maximum;
    /* Returns the peak EVM results of the burst.
     * This value is expressed as a percentage or in dB.
     * This measurement is performed in accordance with section 16.3.7.9 of IEEE Standard 802.11-2016.
     * When you set the RFMXWLAN_ATTR_DSSSMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE,
     * this result returns the maximum of the peak EVM computed for each averaging count.
     */
    ViReal64 dPeakEVM80211_1999Maximum;
    /* Returns the carrier frequency error of the transmitter.
     * This value is expressed in Hz.
     * When you set the RFMXWLAN_ATTR_DSSSMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE,
     * this result returns the mean of the carrier frequency error results computed for each averaging count.
     */
    ViReal64 dFrequencyErrorMean;
    /* Returns the chip clock error result of the transmitter.
     * This value is expressed in parts per million (ppm).
     * When you set the RFMXWLAN_ATTR_DSSSMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE,
     * this result returns the mean of the chip clock error computed for each averaging count.
     */
    ViReal64 dChipClockErrorMean;
    /* Returns the number of chips used for the DSSSModAcc measurement.*/
    ViInt32 dNumberOfChipsUsed;
}DSSSModAccEVMResults,*pDSSSModAccEVMResults;

typedef struct{
    /* Returns the I/Q origin offset. This value is expressed in dB. 
     * I/Q origin offset is the ratio of the mean value of the signal to the RMS value of the signal. 
     * When you set the RFMXWLAN_ATTR_DSSSMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the I/Q origin offset results computed for each averaging count.
     */
    ViReal64 dIQOriginOffsetMean;
    /* Returns the I/Q gain imbalance results. This value is expressed in dB. 
     * I/Q gain imbalance is the ratio of the mean amplitude of the in-phase (I) signal to the mean amplitude of the quadrature-phase (Q) signal. 
     * When you set the RFMXWLAN_ATTR_DSSSMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the I/Q gain imbalance results computed for each averaging count.
     */
    ViReal64 dIQGainImbalanceMean;
    /* Returns the I/Q quadrature error. This value is expressed in degrees. 
     * Quadrature error is the deviation in angle from 90 degrees between the in-phase (I) and quadrature-phase (Q) signals. 
     * When the RFMXWLAN_ATTR_DSSSMODACC_AVERAGING_ENABLED attribute is set to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the I/Q quadrature error results computed for each averaging count.
     */
    ViReal64 dIQQuadratureErrorMean;
}DSSSModAccIQImpairmentsResults,*pDSSSModAccIQImpairmentsResults;

typedef struct{
    /* Returns the data modulation format results of the analyzed waveform. */
    ViInt32 dDataModulationFormat;
    /* Returns the payload length of the acquired burst. This value is expressed in bytes.*/
    ViInt32 dPayloadLength;
    /*Returns the detected preamble type.*/
    ViInt32 dPreambleType;
    /*Returns the value of the locked clocks bit in the Long PHY SERVICE field. 
     * A value of 1 indicates that the transmit frequency and the symbol clock are derived from the same oscillator.
     * A value of 0 indicates that the transmit frequency and the symbol clock are derived from independent oscillators.*/
    ViInt32 dLockedClocksBit;
    /* Returns whether the header CRC is successfully passed, as defined under section 16.2.3.7 of IEEE Standard 802.11 2016.*/
    ViInt32 dHeaderCRCStatus;
    /* ReturnsÂ whether the PSDU cyclic redundancy check (CRC) has successfully passed.*/
    ViInt32 dPSDUCRCStatus;
}DSSSModAccPPDUResults,*pDSSSModAccPPDUResults;


typedef struct{
    /* Returns the average power of the preamble field of the PPDU. 
     * When you set the RFMXWLAN_ATTR_DSSSMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE, 
     * this result returns the mean of the average preamble field power computed for each averaging count. 
     * This value is expressed in dBm.
     */
    ViReal64 dPreambleAveragePowerMean;
    /* Returns the average power of the header field of the PPDU. 
     * When you set the RFMXWLAN_ATTR_DSSSMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE, 
     * this result returns the mean of the average header field power computed for each averaging count. 
     * This value is expressed in dBm.
     */
    ViReal64 dHeaderAveragePowerMean;
    /* Returns the average power of the data field of the PPDU. 
     * When you set the RFMXWLAN_ATTR_DSSSMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE, 
     * this attribute returns the mean of the data field average power results computed for each averaging count. 
     * This value is expressed in dBm. 
     */
    ViReal64 dDataAveragePowerMean;
    /* Returns the average power of the PPDU. 
     * When you set the RFMXWLAN_ATTR_DSSSMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the average PPDU power results computed for each averaging count. 
     * This value is expressed in dBm. 
     */
    ViReal64 dPPDUAveragePowerMean;
}DSSSModAccAveragePowersResults,*pDSSSModAccAveragePowersResults;


typedef struct{
    /* Returns the peak power of the preamble field of the PPDU. 
     * When you set the RFMXWLAN_ATTR_DSSSMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE, 
     * this result returns the maximum of the peak preamble field power results computed for each averaging count. 
     * This value is expressed as a percentage or in dB. 
     */
    ViReal64 dPreamblePeakPowerMaximum;
    /* Returns the peak power of the header field of the PPDU. 
     * When you set the RFMXWLAN_ATTR_DSSSMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE, 
     * this result returns the maximum of the peak header field power results computed for each averaging count. 
     * This value is expressed as a percentage or in dB. 
     */
    ViReal64 dHeaderPeakPowerMaximum;
    /* Returns the peak power of the data field of the PPDU. 
     * When you set the RFMXWLAN_ATTR_DSSSMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE, 
     * this result returns the maximum of the peak data field power results computed for each averaging count. 
     * This value is expressed as a percentage or in dB.
     */
    ViReal64 dDataPeakPowerMaximum;
   /* Returns the peak power of the PPDU. 
    * When you set the RFMXWLAN_ATTR_DSSSMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE, 
    * this parameter returns the maximum of the peak PPDU power results computed for each averaging count. 
    * This value is expressed as a percentage or in dB.
    */
    ViReal64 dPPDUPeakPowerMaximum;
}DSSSModAccPeakPowersResults,*pDSSSModAccPeakPowersResults;


typedef struct{
    /* Returns the array of average powers of the custom gates. 
     * This value is expressed in dBm. 
     * When you set the RFMXWLAN_ATTR_DSSSMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the array of the mean of the average custom gate power results computed for each averaging count.
     */
    ViReal64* pAveragePowerMean;
    /* Returns the array of peak powers of the custom gates. 
     * This value is expressed in dBm. 
     * When you set the RFMXWLAN_ATTR_DSSSMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_DSSSMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the array of the maximum of the peak custom gate power results computed for each averaging count.
     */
    ViReal64* pPeakPowerMaximum;
    /* Returns the actual size of the array, 
     * if you pass NULL to all output array parameters, and set the arraySize parameter to 0.
     */
    ViInt32 dwActualArraySize;
}DSSSModAccCustomGatePowersArrayResults,*pDSSSModAccCustomGatePowersArrayResults;


typedef struct{
    /* Specifies the size of the array. 
     * Set the arraySize parameter to 0 to get the size of all the arrays in the actualArraySize parameter.
     */
    ViInt32 dwArraySize;
    /* Returns the constellation of the received symbols.*/
    ComplexNumber* pConstellation;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 dwActualArraySize;
}DSSSModAccConstellationTraceResults,*pDSSSModAccConstellationTraceResults;


typedef struct{
    /* Specifies the size of the array. Set the arraySize parameter to 0 to get the size of all the arrays in the actualArraySize parameter.*/
    ViInt32 dwArraySize;
    /* Returns the in-phase part of constellation of the received symbols.*/
    ViReal32* pIDataBuf;
    /* Returns the quadrature-phase part of constellation of the received symbols.*/
    ViReal32* pQDataBuf;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 dwActualArraySize;
}DSSSModAccConstellationTraceSplitResults,*pDSSSModAccConstellationTraceSplitResults;


typedef struct{
    /* Specifies the size of the array. Set the arraySize parameter to 0 to get the size of all the arrays in the actualArraySize parameter.*/
    ViInt32 dwArraySize;
    /* Returns the index of the first chip. */
    ViReal64 dX0;
    /* Returns the trace increment interval in number of chips. This value is always equal to 1.*/
    ViReal64 dDx;
    /* Returns the array of EVM per chip. This value is expressed as a percentage or in dB. */
    ViReal32* pEVMPerChipMean;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 dwActualArraySize;
}DSSSModAccEVMPerChipMeanTraceResults,*pDSSSModAccEVMPerChipMeanTraceResults;


typedef struct{
    DSSSModAccEVMResults EVM;
    DSSSModAccIQImpairmentsResults IQImpairments;
    DSSSModAccPPDUResults PPDU;
    DSSSModAccAveragePowersResults AveragePowers;
    DSSSModAccPeakPowersResults PeakPowers;
    DSSSModAccCustomGatePowersArrayResults CustomGatePowersArray;
    DSSSModAccConstellationTraceResults ConstellationTrace;
    DSSSModAccConstellationTraceSplitResults ConstellationTraceSplit;
    DSSSModAccEVMPerChipMeanTraceResults EVMPerChipMeanTrace;
}DSSSModAccResults,*pDSSSModAccResults;

typedef struct{
    /*Returns the RMS EVM of all subcarriers in all OFDM symbols. This value is expressed as a percentage or in dB.*/
    ViReal64 dCompositeRMSEVMMean;
    /*Returns the RMS EVM of data-subcarriers in all OFDM symbols. This value is expressed as a percentage or in dB.*/
    ViReal64 dCompositeDataRMSEVMMean;
    /*Returns the RMS EVM of pilot-subcarriers in all OFDM symbols. This value is expressed as a percentage or in dB.*/
    ViReal64 dCompositePilotRMSEVMMean;
}CompositeRMSEVMAttribute,*pCompositeRMSEVMAttribute;


typedef struct{
    /*Returns the RMS EVM of all subcarriers in all OFDM symbols for the specified user. This value is expressed as a percentage or in dB.*/
    ViReal64 dUserStreamRMSEVMMean;
    /*Returns the RMS EVM of data-subcarriers in all OFDM symbols for the specified user. This value is expressed as a percentage or in dB.*/
    ViReal64 dUserStreamDataRMSEVMMean;
    /*Returns the RMS EVM of pilot-subcarriers in all OFDM symbols for the specified user. This value is expressed as a percentage or in dB.*/
    ViReal64 dUserStreamPilotRMSEVMMean;
}UserStreamRMSEVMAttribute,*pUserStreamRMSEVMAttribute;


typedef struct{
    /* Returns the carrier frequency error of the transmitter. This value is expressed in Hz. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this attribute returns the mean of the carrier frequency error results computed for each averaging count.*/
    ViReal64 dFrequencyErrorMean;
}FrequencyErrorMeanAttribute,*pFrequencyErrorMeanAttribute;


typedef struct{
    /* Returns the frequency error for which the Complementary Cumulative Distribution Function (CCDF) of absolute frequency error is 10%. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * the CCDF is computed over each averaging count. This value is expressed in Hz.*/
    ViReal64 dFrequencyErrorCCDF10Percent;
}FrequencyErrorCCDF10PercentAttribute,*pFrequencyErrorCCDF10PercentAttribute;


typedef struct{
    /* Returns the symbol clock error of the transmitter. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the symbol clock error results computed for each averaging count. 
     * This value is expressed in parts per million (ppm). */
    ViReal64 dSymbolClockErrorMean;
}SymbolClockErrorMeanAttribute,*pSymbolClockErrorMeanAttribute;

typedef struct{
    /* Returns the relative I/Q origin offset, which is the ratio of the power of the DC subcarrier to the total power of all the subcarriers. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this attribute returns the mean of the relative I/Q origin offset computed for each averaging count. 
     * This value is expressed in dB. */
    ViReal64 dRelativeIQOriginOffsetMean;
    /* Returns the I/Q gain imbalance, which is the ratio of the RMS amplitude of the in-phase (I) component of the signal to the RMS amplitude of the quadrature-phase (Q) component of the signal. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this attribute returns the mean of the I/Q gain imbalance computed for each averaging count. 
     * This value is expressed in dB.*/
    ViReal64 dIQGainImbalanceMean;
    /* Returns the I/Q quadrature error, which is a measure of deviation of the phase difference between the quadrature-phase (Q) and the in-phase (I) component of the signal from 90 degrees. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this attribute returns the I/Q quadrature error computed for each averaging count. 
     * This value is expressed in degrees.*/
    ViReal64 dIQQuadratureErrorMean;
    /* Returns the absolute I/Q origin offset, which is the power of the DC subcarrier. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this attribute returns the mean of the absolute I/Q origin offset computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dAbsoluteIQOriginOffsetMean;
    /* Returns the I/Q timing skew, which is the difference between the group delay of the in-phase (I) and quadrature (Q) components of the signal. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this attribute returns the mean of the I/Q timing skew computed for each averaging count. 
     * This value is expressed in seconds.*/
    ViReal64 dIQTimingSkewMean;
}IQImpairmentsAttribute,*pIQImpairmentsAttribute;


typedef struct{
    /* Returns the spectral flatness margin, which is the minimum of the upper and lower spectral flatness margins. 
     * The upper spectral flatness margin is the minimum difference between the upper mask and the spectral flatness across subcarriers. 
     * The lower spectral flatness margin is the minimum difference between the spectral flatness and the lower mask across subcarriers. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * the spectral flatness is computed using the mean of the channel frequency response magnitude computed for each averaging count. 
     * This value is expressed in dB.*/
    ViReal64 dSpectralFlatnessMargin;
    /* Returns the subcarrier index corresponding to the spectralFlatnessMargin parameter.*/
    ViInt32 nSpectralFlatnessMarginSubcarrierIndex;
}SpectralFlatnessAttribute,*pSpectralFlatnessAttribute;


typedef struct{
    /* Returns the number of OFDM symbols used by the measurement.*/
    ViInt32 nNumberOfSymbolsUsed;
}NumberofSymbolsUsedAttribute,*pNumberofSymbolsUsedAttribute;


typedef struct{
    /* Returns the number of space time streams.*/
    ViInt32 nNumberOfSpaceTimeStreams;
}NumberOfSpaceTimeStreamsAttribute,*pNumberOfSpaceTimeStreamsAttribute;


typedef struct{
    /* Returns the PPDU type.*/
    ViInt32 nPPDUType;
}PPDUTypeAttribute,*pPPDUTypeAttribute;


typedef struct{
    /* Returns the MCS index or the data rate. The MCS index or data rate for various standard signals are decoded as follows: 
     * Standard                                 Field 
     * 802.11a, 802.11j, 802.11p                The data rate is decoded from the SIGNAL field.  
     * 802.11n                                  The MCS index is decoded from the HT-SIG field.  
     * 802.11ac                                 The MCS index is decoded from the VHT-SIG-A field.  
     * 802.11ax SU and Extended Range SU PPDU   The MCS index is decoded from the HE-SIG-A field.  
     * 802.11ax MU PPDU                         The MCS index is decoded from the HE-SIG-B field.

     * For 802.11a, 802.11j, and 802.11p signals, the following MCS indices corresponds to their data rates: 
     * MCS      Data Rate 
     * 0        1.5 Mbps, 3 Mbps, and 6 Mbps for channel bandwidths of 5 MHz, 10 MHz, and 20 MHz, respectively.  
     * 1        2.25 Mbps, 4.5 Mbps, and 9 Mbps for channel bandwidths of 5 MHz, 10 MHz, and 20 MHz, respectively.  
     * 2        3 Mbps, 6 Mbps, and 12 Mbps for channel bandwidths of 5 MHz, 10 MHz, and 20 MHz, respectively.  
     * 3        4.5 Mbps, 9 Mbps, and 18 Mbps for channel bandwidths of 5 MHz, 10 MHz, and 20 MHz, respectively.  
     * 4        6 Mbps, 12 Mbps, and 24 Mbps for channel bandwidths of 5 MHz, 10 MHz, and 20 MHz, respectively.  
     * 5        9 Mbps, 18 Mbps, and 36 Mbps for channel bandwidths of 5 MHz, 10 MHz, and 20 MHz, respectively.  
     * 6        12 Mbps, 24 Mbps, and 48 Mbps for channel bandwidths of 5 MHz, 10 MHz, and 20 MHz, respectively.  
     * 7        13.5 Mbps, 27 Mbps, and 54 Mbps for channel bandwidths of 5 MHz, 10 MHz, and 20 MHz, respectively.  */
    ViInt32 nMCSIndex;
}MCSIndexAttribute,*pMCSIndexAttribute;


typedef struct{
    /* Returns the location of RU for a user in terms of the index of a 26-tone RU, assuming the entire bandwidth is composed of 26-tone RUs. */
    ViInt32 nRUOffset;
    /* Returns the RU size for a user.*/
    ViInt32 nRUSize;
}RUOffsetAndSizeAttribute,*pRUOffsetAndSizeAttribute;


typedef struct{
    /* Returns the number of users.*/
    ViInt32 nNumberOfUsers;
}NumberOfUsersAttribute,*pNumberOfUsersAttribute;


typedef struct{
    /* Returns the number of HE-SIG-B symbols. This result is applicable for 802.11ax MU PPDU signals, and is decoded from the HE-SIG-A field.*/
    ViInt32 nNumberOfHESIGBSymbols;
}NumberOfHESIGBSymbolsAttribute,*pNumberOfHESIGBSymbolsAttribute;


typedef struct{
    /* Returns the size of the guard interval of OFDM symbols.*/
    ViInt32 nGuardIntervalType;
}GuardIntervalTypeAttribute,*pGuardIntervalTypeAttribute;

typedef struct{
    /* Returns the HE-LTF size.*/
    ViInt32 nHELTFSize;
}HELTFSizeAttribute,*pHELTFSizeAttribute;


typedef struct{
    /* Returns whether the parity check has passed either for the SIGNAL field of the 802.11a/g waveform or for the L-SIG field of the 802.11n/802.11ac/802.11ax waveforms. 

     * RFMXWLAN_VAL_OFDMMODACC_L_SIG_PARITY_CHECK_STATUS_NOT_APPLICABLE (-1)    Returns that the parity check is invalid for the current waveform. 
     * RFMXWLAN_VAL_OFDMMODACC_L_SIG_PARITY_CHECK_STATUS_FAIL (0)               Returns that the parity check failed. 
     * RFMXWLAN_VAL_OFDMMODACC_L_SIG_PARITY_CHECK_STATUS_PASS (1)               Returns that the parity check passed. 
     */
    
    ViInt32 nLSIGParityCheckStatus;
}LSIGParityCheckStatusAttribute,*pLSIGParityCheckStatusAttribute;


typedef struct{
    /* Returns whether the cyclic redundancy check (CRC) has passed either for the HT-SIG field of the 802.11n waveform, for the VHT-SIG-A field of the 802.11ac waveform, or for the HE-SIG-A field of the 802.11ax waveform. 

     * RFMXWLAN_VAL_OFDMMODACC_SIG_CRC_STATUS_NOT_APPLICABLE (-1)   Returns that the SIG CRC is invalid for the current waveform. 
     * RFMXWLAN_VAL_OFDMMODACC_SIG_CRC_STATUS_FAIL (0)              Returns that the SIG CRC failed. 
     * RFMXWLAN_VAL_OFDMMODACC_SIG_CRC_STATUS_PASS (1)              Returns that the SIG CRC passed. 
     */
    ViInt32 nSIGCRCStatus;
}SIGCRCStatusAttribute,*pSIGCRCStatusAttribute;


typedef struct{
    /* Returns whether the cyclic redundancy check (CRC) has passed for the HE-SIG-B field of the 802.11ax MU PPDU waveform. 

     * RFMXWLAN_VAL_OFDMMODACC_SIG_B_CRC_STATUS_NOT_APPLICABLE (-1)     Returns that the SIG-B CRC is invalid for the current waveform. 
     * RFMXWLAN_VAL_OFDMMODACC_SIG_B_CRC_STATUS_FAIL (0)                Returns that the SIG-B CRC failed. 
     * RFMXWLAN_VAL_OFDMMODACC_SIG_B_CRC_STATUS_PASS (1)                Returns that the SIG-B CRC passed. 
     */
    ViInt32 nSIGBCRCStatus;
}SIGBCRCStatusAttribute,*pSIGBCRCStatusAttribute;


typedef struct{
    /* Returns the average power of the data field. This value is expressed in dBm.*/
    ViReal64 dDataAveragePowerMean;
}DataAveragePowerAttribute,*pDataAveragePowerAttribute;


typedef struct{
    /* Returns the peak power of the data field. This value is expressed in dBm.*/
    ViReal64 dDataPeakPowerMaximum;
}DataPeakPowerAttribute,*pDataPeakPowerAttribute;


typedef struct{
    /* Returns the average power of the PPDU. This value is expressed in dBm.*/
    ViReal64 dPPDUAveragePowerMean;
}PPDUAveragePowerAttribute,*pPPDUAveragePowerAttribute;


typedef struct{
    /* Returns the peak power of the PPDU. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this paramter returns the maximum of the PPDU peak power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dPPDUPeakPowerMaximum;
}PPDUPeakPowerAttribute,*pPPDUPeakPowerAttribute;



typedef struct{
    /* Returns the average power of the packet extension field. 
     * This parameter is applicable for 802.11ax signals. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the packet extension field average power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dPEAveragePowerMean;
}PEAveragePowerAttribute,*pPEAveragePowerAttribute;


typedef struct{
    /* Returns the peak power of the packet extension field. This parameter is applicable for 802.11ax signals. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this paramter returns the maximum of the PE field peak power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dPEPeakPowerMaximum;
}PEPeakPowerAttribute,*pPEPeakPowerAttribute;


typedef struct{
    /* Returns the average power of the L-STF or STF field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the L-STF or STF average power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dLSTFAveragePowerMean;
    /* Returns the average power of the L-LTF or LTF field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the L-LTF or LTF average power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dLLTFAveragePowerMean;
    /* Returns the average power of the L-SIG or SIGNAL field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the L-SIG or SIGNAL field average power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dLSIGAveragePowerMean;
    
}PreambleAveragePowersCommonAttribute,*pPreambleAveragePowersCommonAttribute;


typedef struct{
    /* Returns the peak power of the L-STF or STF field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the maximum of the L-STF or STF peak power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dLSTFPeakPowerMaximum;
    /* Returns the peak power of the L-LTF or LTF field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the maximum of the L-LTF or LTF peak power results computed for each averaging count. 
     * This value is expressed in dBm. */
    ViReal64 dLLTFPeakPowerMaximum;
    /* Returns the peak power of the L-SIG or SIGNAL field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the maximum of the L-SIG or SIGNAL field peak power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dLSIGPeakPowerMaximum;
}PreamblePeakPowersCommonAttribute,*pPreamblePeakPowersCommonAttribute;


typedef struct{
    /* Returns the average power of the HT-SIG field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the HT-SIG field average power results computed for each averaging count.
     * This value is expressed in dBm.*/
    ViReal64 dHTSIGAveragePowerMean;
    /* Returns the average power of the HT-STF field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the HT-STF average power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dHTSTFAveragePowerMean;
    /* Returns the average power of the HT-DLTF. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the HT-DLTF average power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dHTDLTFAveragePowerMean;
    /* Returns the average power of the HT-ELTF field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the HT-ELTF average power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dHTELTFAveragePowerMean;
    
}PreambleAveragePowers80211nAttribute,*pPreambleAveragePowers80211nAttribute;


typedef struct{
    /* Returns the peak power of the HT-SIG field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the maximum of the HT-SIG field peak power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dHTSIGPeakPowerMaximum;
    /* Returns the peak power of the HT-STF field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the maximum of the HT-STF peak power results computed for each averaging count. 
     * This value is expressed in dBm. */
    ViReal64 dHTSTFPeakPowerMaximum;
    /* Returns the peak power of the HT-DLTF field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the maximum of the HT-DLTF peak power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dHTDLTFPeakPowerMaximum;
    /* Returns the peak power of the HT-ELTF field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the maximum of the HT-ELTF peak power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dHTELTFPeakPowerMaximum;
}PreamblePeakPowers80211nAttribute,*pPreamblePeakPowers80211nAttribute;


typedef struct{
    /* Returns the average power of the VHT-SIG-A field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the VHT-SIG-A field average power results computed for each averaging count. 
     * This value is expressed in dBm. */
    ViReal64 dVHTSIGAAveragePowerMean;
    /* Returns the average power of the VHT-STF field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the VHT-STF average power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dVHTSTFAveragePowerMean;
    /* Returns the average power of the VHT-LTF field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this paramter returns the mean of the VHT-LTF average power results computed for each averaging count. 
     * This value is expressed in dBm. */
    ViReal64 dVHTLTFAveragePowerMean;
    /* Returns the average power of the VHT-SIG-B field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the VHT-SIG-B field average power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dVHTSIGBAveragePowerMean;
}PreambleAveragePowers80211acAttribute,*pPreambleAveragePowers80211acAttribute;


typedef struct{
    /* Returns the peak power of the VHT-SIG-A field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this attribute returns the maximum of the VHT-SIG-A field peak power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dVHTSIGAPeakPowerMaximum;
    /* Returns the peak power of the VHT-STF field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the maximum of the VHT-STF peak power results computed for each averaging count. 
     * This value is expressed in dBm. */
    ViReal64 dVHTSTFPeakPowerMaximum;
    /* Returns the peak power of the VHT-LTF field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the maximum of the VHT-LTF peak power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dVHTLTFPeakPowerMaximum;
    /* Returns the peak power of the VHT-SIG-B field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the maximum of the VHT-SIG-B field peak power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dVHTSIGBPeakPowerMaximum;
}PreamblePeakPowers80211acAttribute,*pPreamblePeakPowers80211acAttribute;


typedef struct{
    /* Returns the average power of the RL-SIG field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the RL-SIG field average power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dRLSIGAveragePowerMean;
    /* Returns the average power of the HE-SIG-A field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the HE-SIG-A field average power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dHESIGAAveragePowerMean;
    /* Returns the average power of the HE-SIG-B field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the HE-SIG-B field average power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dHESIGBAveragePowerMean;
    /* Returns the average power of the HE-STF field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the HE-STF average power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dHESTFAveragePowerMean;
    /* Returns the average power of the HE-LTF field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the mean of the HE-LTF average power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dHELTFAveragePowerMean;
    
}PreambleAveragePowers80211axAttribute,*pPreambleAveragePowers80211axAttribute;

typedef struct{
    /* Returns the peak power of the RL-SIG field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the maximum of the RL-SIG field peak power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dRLSIGPeakPowerMaximum;
    /* Returns the peak power of the HE-SIG-A field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the maximum of the HE-SIG-A field peak power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dHESIGAPeakPowerMaximum;
    /* Returns the peak power of the HE-SIG-B field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the maximum of the HE-SIG-B field peak power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dHESIGBPeakPowerMaximum;
    /* Returns the peak power of the HE-STF field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the maximum of the HE-STF peak power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dHESTFPeakPowerMaximum;
    /* Returns the peak power of the HE-LTF field. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the maximum of the HE-LTF peak power results computed for each averaging count. 
     * This value is expressed in dBm.*/
    ViReal64 dHELTFPeakPowerMaximum;
}PreamblePeakPowers80211axAttribute,*pPreamblePeakPowers80211axAttribute;

typedef struct{
    /* Returns the array of average powers of the custom gates. This value is expressed in dBm. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the array of the mean of the average custom gate power results computed for each averaging count.*/
    ViReal64* pAveragePowerMean;
    /* Returns the array of peak powers of the custom gates. This value is expressed in dBm. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this parameter returns the array of the maximum of the peak custom gate power results computed for each averaging count. */
    ViReal64* pPeakPowerMaximum;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}CustomGatePowersArrayAttribute,*pCustomGatePowersArrayAttribute;

typedef struct{
    /* Describes error conditions that occur before this node runs. This input provides standard error in functionality.*/
    ViReal64 dUnusedToneErrorMargin;
    /* Returns the 26-tone RU index corresponding to the unusedToneErrorMargin parameter.*/
    ViInt32 nUnusedToneErrorMarginRUIndex;
}UnusedToneErrorAttribute,*pUnusedToneErrorAttribute;

typedef struct{
    /* Returns the array of unused tone error margin per RU, which is the difference between the unused tone error mask and the unused tone error for each RU. This value is expressed in dB. */
    ViReal64* pUnusedToneErrorMarginPerRU;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}UnusedToneErrorMarginPerRUAttribute,*pUnusedToneErrorMarginPerRUAttribute;

typedef struct{
    /* Returns the demodulated QAM symbols from all the data-subcarriers in all the OFDM symbols. */
    ComplexNumber* pDataConstellation;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}DataConstellationTraceAttribute,*pDataConstellationTraceAttribute;

typedef struct{
    /* Returns the in-phase part of demodulated QAM symbols from all the data-subcarriers in all the OFDM symbols.*/
    ViReal32* pIData;
    /* Returns the quadrature-phase part of demodulated QAM symbols from all the data-subcarriers in all the OFDM symbols.*/
    ViReal32* pQData;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize; 
}DataConstellationTraceSplitAttribute,*pDataConstellationTraceSplitAttribute;


typedef struct{
    /* Returns the demodulated QAM symbols from all the pilot-subcarriers in all OFDM symbols.*/
    ComplexNumber* pPilotConstellation;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}PilotConstellationTraceAttribute,*pPilotConstellationTraceAttribute;


typedef struct{
    /* Returns the in-phase part of demodulated QAM symbols from all the pilot-subcarriers in all OFDM symbols.*/
    ViReal32* pIData;
    /* Returns the quadrature-phase part of demodulated QAM symbols from all the pilot-subcarriers in all OFDM symbols.*/
    ViReal32* pQData;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}PilotConstellationTraceSplitAttribute,*pPilotConstellationTraceSplitAttribute;

typedef struct{
    /* Returns the demodulated QAM symbols from all the data-subcarriers in all of the OFDM symbols for each user.*/
    ComplexNumber* pUserDataConstellation;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}UserDataConstellationTraceAttribute,*pUserDataConstellationTraceAttribute;


typedef struct{
    /* Returns the real part of demodulated QAM symbols from all the data-subcarriers in all of the OFDM symbols for each user.*/
    ViReal32* pRealUserDataConstellation;
    /* Returns the imaginary part of demodulated QAM symbols from all the data-subcarriers in all of the OFDM symbols for each user.*/
    ViReal32* pImagUserDataConstellation;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}UserDataConstellationTraceSplitAttribute,*pUserDataConstellationTraceSplitAttribute;

typedef struct{
    /* Returns the demodulated QAM symbols from all the pilot-subcarriers in all of the OFDM symbols for each user.*/
    ComplexNumber* pUserPilotConstellation;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}UserPilotConstellationTraceAttribute,*pUserPilotConstellationTraceAttribute;

typedef struct{
    /* Returns the real part of demodulated QAM symbols from all the pilot-subcarriers in all of the OFDM symbols for each user.*/
    ViReal32* pRealUserPilotConstellation;
    /* Returns the imaginary part of demodulated QAM symbols from all the pilot-subcarriers in all of the OFDM symbols for each user.*/
    ViReal32* pImagUserPilotConstellation;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}UserPilotConstellationTraceSplitAttribute,*pUserPilotConstellationTraceSplitAttribute;


/* ChainRMSEVMPerSubcarrierMeanTrace --- SubcarrierChainEVMPerSymbolTrace*/
typedef struct{
    /* Returns the starting subcarrier index.*/
    ViReal64 dX0;
    /* Returns the subcarrier increment value. This value is always 1.*/
    ViReal64 dDx;
    /* Returns the array of chain RMS EVM of each subcarrier. This array is expressed as a percentage or in dB. */
    ViReal32* pDataBuf;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}TraceAttribute,*pTraceAttribute;



typedef struct{
    /* Returns the starting subcarrier index.*/
    ViReal64 dX0;
    /* Returns the subcarrier increment value. This value is always 1.*/
    ViReal64 dDx;
    /* Returns the array of spectral flatness for each subcarrier. This value is expressed in dB.*/
    ViReal32* pSpectralFlatnessMean;
    /* Returns the array of spectral flatness lower mask for each subcarrier. This value is expressed in dB.*/
    ViReal32* pSpectralFlatnessLowerMask;
    /* Returns the array of spectral flatness upper mask for each subcarrier. This value is expressed in dB.*/
    ViReal32* pSpectralFlatnessUpperMask;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}SpectralFlatnessMeanTraceAttribute,*pSpectralFlatnessMeanTraceAttribute;


typedef struct{
    /* Returns the starting OFDM symbol index corresponding to the value of OFDMModAcc Meas Offset attribute.*/
    ViReal64 dX0;
    /* Returns the OFDM symbol increment value. This value is always equal to 1.*/
    ViReal64 dDx;
    /* Returns the array of magnitude of the common pilot error for each OFDM symbol. This value is expressed in dB. */
    ViReal32* pCommonPilotErrorMagnitude;
    /* Returns the array pf phase of the common pilot error for each OFDM symbol. This value is expressed in degrees.*/
    ViReal32* pCommonPilotErrorPhase;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}CommonPilotErrorTraceAttribute,*pCommonPilotErrorTraceAttribute;

typedef struct{
    /* Returns the starting subcarrier index.*/
    ViReal64 dX0;
    /* Returns the subcarrier increment value. This value is always 1. */
    ViReal64 dDx;
    /* Returns the array of magnitudes of the channel frequency response for each subcarrier. This array is expressed in dB.*/
    ViReal32* pChannelFrequencyResponseMeanMagnitude;
    /* Returns the array of deviation of the measured phase-response of the channel from the ideal linear phase response for all subcarriers. This value is expressed in degrees.*/
    ViReal32* pChannelFrequencyResponseMeanPhase;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}ChannelFrequencyResponseMeanTraceAttribute,*pChannelFrequencyResponseMeanTraceAttribute;

typedef struct{
    /* Returns the starting RU index. This value is always 0.*/
    ViReal64 dX0;
    /* Returns the RU increment value. This value is always 1.*/
    ViReal64 dDx;
    /* Returns the array of unused tone error for each RU. This value is expressed in dB.*/
    ViReal32* pUnusedToneError;
    /* Returns the array of unused tone error mask for each RU. This value is expressed in dB.*/
    ViReal32* pUnusedToneErrorMask;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}UnusedToneErrorMeanTraceAttribute,*pUnusedToneErrorMeanTraceAttribute;


typedef struct{
    /* Fetches the composite RMS EVM results.*/
    CompositeRMSEVMAttribute CompositeRMSEVM;
    /* Fetches the stream RMS EVM results for each user.*/
    UserStreamRMSEVMAttribute UserStreamRMSEVM;
    /* Fetches the carrier frequency error of the transmitter.*/
    FrequencyErrorMeanAttribute FrequencyErrorMean;
    /* Fetches the frequency error CCDF 10% result.*/
    FrequencyErrorCCDF10PercentAttribute FrequencyErrorCCDF10Percent;
    /* Fetches the symbol clock error of the transmitter.*/
    SymbolClockErrorMeanAttribute SymbolClockErrorMean;
    /* Fetches the I/Q Impairment results for the OFDMModAcc measurement.*/
    IQImpairmentsAttribute IQImpairments;
    /* Fetches the spectral flatness margin results.*/
    SpectralFlatnessAttribute SpectralFlatness;
    /* Fetches the number of OFDM symbols used for EVM measurement.*/
    NumberofSymbolsUsedAttribute NumberofSymbolsUsed;
    /* Fetches the number of space time streams.*/
    NumberOfSpaceTimeStreamsAttribute NumberOfSpaceTimeStreams;
    /* Fetches the PPDU type.*/
    PPDUTypeAttribute PPDUType;
    /* Fetches the MCS index.*/
    MCSIndexAttribute MCSIndex;
    /* Fetches the RU offset and the RU size.*/
    RUOffsetAndSizeAttribute RUOffsetAndSize;
    /* Fetches the number of users.*/
    NumberOfUsersAttribute NumberOfUsers;
    /* Fetches the number of HE-SIG-B symbols.*/
    NumberOfHESIGBSymbolsAttribute NumberOfHESIGBSymbols;
    /* Fetches the guard interval type.*/
    GuardIntervalTypeAttribute GuardIntervalType;
    /* Fetches the HE-LTF size.*/
    HELTFSizeAttribute HELTFSize;
    /* Fetches the L-SIG parity check status. */
    LSIGParityCheckStatusAttribute LSIGParityCheckStatus;
    /* Fetches the SIG CRC Status. */
    SIGCRCStatusAttribute SIGCRCStatus;
    /* Fetches the SIG-B CRC Status. */
    SIGBCRCStatusAttribute SIGBCRCStatus;
    /* Fetches the average power of the data field.*/
    DataAveragePowerAttribute DataAveragePower;
    /* Fetches the peak power of the data field.*/
    DataPeakPowerAttribute DataPeakPower;
    /* Fetches the average power of the PPDU.*/
    PPDUAveragePowerAttribute PPDUAveragePower;
    /* Fetches the peak power of the PPDU.*/
    PPDUPeakPowerAttribute PPDUPeakPower;
    /* Fetches the average power of the packet extension field.*/
    PEAveragePowerAttribute PEAveragePower;
    /* Fetches the peak power of the packet extension field.*/
    PEPeakPowerAttribute PEPeakPower;
    /* Fetches the average power of the preamble fields.*/
    PreambleAveragePowersCommonAttribute PreambleAveragePowersCommon;
    /* Fetches the peak power of the preamble fields.*/
    PreamblePeakPowersCommonAttribute PreamblePeakPowersCommon;
    /* Fetches the average power of the 802.11n specific preamble fields.*/
    PreambleAveragePowers80211nAttribute PreambleAveragePowers802_11n;
    /* Fetches the peak power of the 802.11n specific preamble fields.*/
    PreamblePeakPowers80211nAttribute PreamblePeakPowers802_11n;
    /* Fetches the average power of the 802.11ac specific preamble fields.*/
    PreambleAveragePowers80211acAttribute PreambleAveragePowers802_11ac;
    /* Fetches the peak power of the 802.11ac specific preamble fields.*/
    PreamblePeakPowers80211acAttribute PreamblePeakPowers802_11ac;
    /* Fetches the average power of the 802.11ax specific preamble fields.*/
    PreambleAveragePowers80211axAttribute PreambleAveragePowers802_11ax;
    /* Fetches the peak power of the 802.11ax specific preamble fields.*/
    PreamblePeakPowers80211axAttribute PreamblePeakPowers802_11ax;
    /* Fetches the average and peak power of the custom gates.*/
    CustomGatePowersArrayAttribute CustomGatePowersArray;
    /* Fetches the unused tone error margin results.*/
    UnusedToneErrorAttribute UnusedToneError;
    /* Fetches the unused tone error margin result per RU.*/
    UnusedToneErrorMarginPerRUAttribute UnusedToneErrorMarginPerRU;
    /* Fetches the constellation trace for the data-subcarriers.*/
    DataConstellationTraceAttribute DataConstellationTrace;
    /* Fetches the in-phase and quadrature-phase part of constellation trace for the data-subcarriers.*/
    DataConstellationTraceSplitAttribute DataConstellationTraceSplit;
    /* Fetches the constellation trace for the pilot-subcarriers.*/
    PilotConstellationTraceAttribute PilotConstellationTrace;
    /* Fetches the in-phase and quadrature-phase part of constellation trace for the pilot-subcarriers.*/
    PilotConstellationTraceSplitAttribute PilotConstellationTraceSplit;
    /* Fetches the constellation trace for the data-subcarriers of each user. 
    Use "user<n>" as the selector channel string to read parameters from this function.*/
    UserDataConstellationTraceAttribute UserDataConstellationTrace;
    /* Fetches the constellation trace for the data-subcarriers of each user. 
    Use "user<n>" as the selector channel string to read parameters from this function.*/
    UserDataConstellationTraceSplitAttribute UserDataConstellationTraceSplit;
    /* Fetches the constellation trace for the pilot-subcarriers of each user. 
    Use "user<n>" as the selector channel string to read parameters from this function.*/
    UserPilotConstellationTraceAttribute UserPilotConstellationTrace;
    /* Fetches the constellation trace for the pilot-subcarriers of each user. 
    Use "user<n>" as the selector channel string to read parameters from this function.*/
    UserPilotConstellationTraceSplitAttribute UserPilotConstellationTraceSplit;
    /* Fetches the chain RMS EVM per subcarrier trace. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this function returns the mean of the chain RMS EVM per subcarrier computed for each averaging count.*/
    TraceAttribute ChainRMSEVMPerSubcarrierMeanTrace;
    /* Fetches the chain RMS EVM per symbol trace. 
     * When you set the When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this function returns the mean of the chain RMS EVM per symbol computed for each averaging count.*/
    TraceAttribute ChainRMSEVMPerSymbolMeanTrace;
    /* Fetches the stream RMS EVM per subcarrier trace for each user. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this function returns the mean of the user stream RMS EVM per subcarrier computed for each averaging count. 
     * Use "user<n>" as the selector channel string to read parameters from this function.*/
    TraceAttribute UserStreamRMSEVMPerSubcarrierMeanTrace;
    /* Fetches the stream RMS EVM per symbol trace for each user. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this function returns the mean of the user stream RMS EVM per symbol computed for each averaging count. 
     * Use "user<n>" as the selector channel string to read parameters from this function.*/
    TraceAttribute UserStreamRMSEVMPerSymbolMeanTrace;
    /* Fetches the stream data-subcarriers RMS EVM per symbol trace for each user. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this function returns the mean of the user stream data RMS EVM per symbol computed for each averaging count. 
     * Use "user<n>" as the selector channel string to read parameters from this function.*/
    TraceAttribute UserStreamDataRMSEVMPerSymbolMeanTrace;
    /* Fetches the stream pilot-subcarriers RMS EVM per symbol trace for each user.
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this function returns the mean of the user stream pilot RMS EVM per symbol computed for each averaging count. 
     * Use "user<n>" as the selector channel string to read parameters from this function.*/
    TraceAttribute UserStreamPilotRMSEVMPerSymbolMeanTrace;
    /* Fetches the chain data-subcarriers RMS EVM per symbol trace. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this function returns the mean of the chain data RMS EVM per symbol computed for each averaging count.*/
    TraceAttribute ChainDataRMSEVMPerSymbolMeanTrace;
    /* Fetches the chain pilot-subcarriers RMS EVM per symbol trace. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this function returns the mean of the chain pilot RMS EVM per symbol computed for each averaging count.*/
    TraceAttribute ChainPilotRMSEVMPerSymbolMeanTrace;
    /* Fetches the chain EVM per subcarrier trace for a symbol. For symbol indices outside the measurement interval, the trace value is NaN.*/
    TraceAttribute SymbolChainEVMPerSubcarrierTrace;
    /* Fetches the stream RMS EVM per subcarrier trace for each user. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this function returns the mean of the user stream RMS EVM per subcarrier computed for each averaging count. 
     * Use "user<n>" as the selector channel string to read parameters from this function.*/
    //TraceAttribute UserStreamRMSEVMPerSubcarrierMeanTrace;
    /* Fetches the chain EVM per symbol trace for a subcarrier. For unoccupied subcarriers, the trace value is NaN.*/
    TraceAttribute SubcarrierChainEVMPerSymbolTrace;
    /* Fetches the spectral flatness trace, and the lower and upper spectral flatness mask traces. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this function returns the spectral flatness trace computed on the mean of the channel estimates computed for each averaging count.*/
    SpectralFlatnessMeanTraceAttribute SpectralFlatnessMeanTrace;
    /* Fetches the common pilot error magnitude and phase traces.*/
    CommonPilotErrorTraceAttribute CommonPilotErrorTrace;
    /* Fetches the preamble frequency error trace for signals containing an OFDM payload. 
     * Preamble frequency error computes the variations, across time, of the frequency error over initial 16us which 
     * comprises of the short training field (STF) and long training field (LTF) symbols. */
    TraceAttribute PreambleFrequencyErrorTrace;
    /* Fetches the channel frequency response trace. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this function returns the mean of the channel frequency response trace computed for each averaging count.*/
    ChannelFrequencyResponseMeanTraceAttribute ChannelFrequencyResponseMeanTrace;
    /* Fetches the I/Q gain imbalance per subcarrier trace. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this function returns the mean of the I/Q gain imbalance computed for each averaging count.*/
    TraceAttribute IQGainImbalancePerSubcarrierMeanTrace;
    /* Fetches the I/Q quadrature error per subcarrier trace. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this function returns the mean of the I/Q quadrature error computed for each averaging count.*/
    TraceAttribute IQQuadratureErrorPerSubcarrierMeanTrace;
    /* Fetches the unused tone error trace and the unused tone error mask trace. 
     * When you set the RFMXWLAN_ATTR_OFDMMODACC_AVERAGING_ENABLED attribute to RFMXWLAN_VAL_OFDMMODACC_AVERAGING_ENABLED_TRUE, 
     * this function returns the mean of the unused tone error computed for each averaging count.*/
    UnusedToneErrorMeanTraceAttribute UnusedToneErrorMeanTrace;
  
}OFDMModAccResults,*pOFDMModAccResults;


typedef struct{
    /* Returns the average power of the carrier channel over the bandwidth indicated by the SEM Carrier IBW attribute. 
     * This value is expressed in dBm.*/
    ViReal64 dAbsolutePower;
    /* Returns the average power of the carrier channel, relative to the peak power of the carrier channel, over the bandwidth indicated by the SEM Carrier IBW attribute. 
     * This value is expressed in dBm.*/
    ViReal64 dRelativePower;
}CarrierMeasurementAttribute,*pCarrierMeasurementAttribute;


typedef struct{
    /* Returns the lower offset (negative) segment measurement status, indicating whether the spectrum exceeds the SEM measurement mask limits in the lower offset segment. 
     * RFMXWLAN_VAL_SEM_MEASUREMENT_STATUS_FAIL (0)  The spectrum exceeds the SEM measurement mask limits the lower offset segment.
     * RFMXWLAN_VAL_SEM_MEASUREMENT_STATUS_PASS (1)  The spectrum does not exceed the SEM measurement mask limits for the lower offset segment. 
     */
    ViInt32 nMeasurementStatus;
    /* Returns the margin from the SEM measurement mask for the lower (negative) offset. 
     * This value is expressed in dB. 
     * Margin is defined as the maximum difference between the spectrum and the mask.*/
    ViReal64 dMargin;
    /* Returns the frequency corresponding to the margin for the lower (negative) offset. 
     * This value is expressed in Hz.*/
    ViReal64 dMarginFrequency;
    /* Returns the absolute power corresponding to the margin for the lower (negative) offset. 
     * This value is expressed in dBm.*/
    ViReal64 dMarginAbsolutePower;
    /* Returns the relative power corresponding to the margin for the lower (negative) offset. 
     * The relative power is relative to the peak power of the carrier channel. 
     * This value is expressed in dB.*/
    ViReal64 dMarginRelativePower;
}OffsetMarginAttribute,*pLowerOffsetMarginAttribute;

typedef struct{
    /* Returns the average power of the lower (negative) offset over the bandwidth determined by the offset start and stop frequencies. 
     * This value is expressed in dBm.*/
    ViReal64 dTotalAbsolutePower;
    /* Returns the average power of the lower (negative) offset relative to the peak power of the carrier channel. 
     * This value is expressed in dB.*/
    ViReal64 dTotalRelativePower;
    /* Returns the peak power of the lower (negative) offset. 
     * This value is expressed in dBm.*/
    ViReal64 dPeakAbsolutePower;
    /* Returns the frequency at which the peak power occurs in the lower (negative) offset. 
     * This value is expressed in Hz.*/
    ViReal64 dPeakFrequency;
    /* Returns the peak power of the lower (negative) offset, relative to the peak power of the carrier channel. This value is expressed in dBm.*/
    ViReal64 dPeakRelativePower;
}OffsetPowerAttribute,*pLowerOffsetPowerAttribute;


typedef struct{
    /* Returns an array of lower (negative) offset segment measurement status, indicating whether the spectrum exceeds the SEM measurement mask limits in the lower offset segments. 
     * RFMXWLAN_VAL_SEM_MEASUREMENT_STATUS_FAIL (0)  The spectrum exceeds the SEM measurement mask limits the lower offset segment.
     * RFMXWLAN_VAL_SEM_MEASUREMENT_STATUS_PASS (1)  The spectrum does not exceed the SEM measurement mask limits for the lower offset segment. 
     */
    ViInt32* pMeasurementStatus;
    /* Returns the array of margins from the SEM measurement mask for the lower (negative) offset. 
     * This value is expressed in dB. 
     * Margin is defined as the maximum difference between the spectrum and the mask.*/
    ViReal64* pMargin;
    /* Returns the array of frequencies corresponding to the margins for the lower (negative) offsets. This value is expressed in dB. */
    ViReal64* pMarginFrequency;
    /* Returns the array of absolute powers corresponding to the margins for the lower (negative) offsets. This value is expressed in dBm.*/
    ViReal64* pMarginAbsolutePower;
    /* Returns the array of relative powers corresponding to the margins for the lower (negative) offsets. The relative powers are relative to the peak power of the carrier channel. 
     * This value is expressed in dB.*/
    ViReal64* pMarginRelativePower;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}OffsetMarginArrayAttribute,*pOffsetMarginArrayAttribute;


typedef struct{
    /*  Returns the array of average powers of the lower (negative) offsets over the bandwidth determined by the offset start and stop frequencies. 
     * This value is expressed in dBm. */
    ViReal64* pTotalAbsolutePower;
    /* Returns the array of average powers of the lower (negative) offsets relative to the peak power of the carrier channel. This value is expressed in dB.*/
    ViReal64* pTotalRelativePower;
    /* Returns the array of peak powers of the lower (negative) offsets. This value is expressed in dBm.*/
    ViReal64* pPeakAbsolutePower;
    /* Returns the array of frequencies at which the peak power occurs in the lower (negative) offsets. This value is expressed in Hz.*/
    ViReal64* pPeakFrequency;
    /* Returns the array of peak powers of the lower (negative) offsets, relative to the peak power of the carrier channel. This value is expressed in dBm.*/
    ViReal64* pPeakRelativePower;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}OffsetPowerArrayAttribute,*pOffsetPowerArrayAttribute;

typedef struct{
    /* Returns the start frequency. This value is expressed in Hz.*/
    ViReal64 dX0;
    /* Returns the frequency bin spacing. This value is expressed in Hz. */
    ViReal64 dDx;
    /* Returns the array of power measured at each frequency bin. This value is expressed in dBm.*/
    ViReal32* pSpectrum;
    /* Returns the array of mask level values for each frequency bin. This value is expressed in dBm.*/
    ViReal32* pCompositeMask;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}SpectrumAttribute,*pSpectrumAttribute;

typedef struct{
    /* Returns the overall measurement status indicating whether the spectrum exceeds the SEM measurement mask limits in any of the offset segments. 
     * RFMXWLAN_VAL_SEM_MEASUREMENT_STATUS_FAIL (0)  The spectrum exceeds the SEM measurement mask limits for atleast one of the offset segments.
     * RFMXWLAN_VAL_SEM_MEASUREMENT_STATUS_PASS (1)  The spectrum does not exceed the SEM measurement mask limits for any offset segment. 
     */
    ViInt32 nMeasurementStatus;
    /* Returns the absolute and relative carrier power measurements. The relative power is relative to the peak power of the carrier.*/
    CarrierMeasurementAttribute CarrierMeasurement;
    /* Returns the measurement status, margin, margin-frequency, and absolute and relative power corresponding to the margin-frequency for lower offset segment. 
     * The relative power is relative to the peak power in the carrier. 
     * Use "offset<n>" as the selector string to read the parameters from this function.*/
    OffsetMarginAttribute LowerOffsetMargin;
    /* Returns the total absolute and relative powers, peak absolute and relative powers and frequency at peak absolute power of lower offset segment. 
     * The relative power is relative to the peak power of the carrier.*/
    OffsetPowerAttribute LowerOffsetPower;
    /* Returns the measurement status, margin, margin-frequency, absolute and relative power corresponding to the margin-frequency for upper offset segment. 
     * The relative power is relative to the peak power in the carrier.
     * Use "offset<n>" as the selector string to read parameters from this function.*/
    OffsetMarginAttribute UpperOffsetMargin;
    /* Returns the total absolute and relative powers, peak absolute and relative powers and frequency at peak absolute power of upper offset segment. 
     * The relative power is relative to the peak power of the carrier.
     * Use "offset<n>" as the selector string to read parameters from this function.*/
    OffsetPowerAttribute UpperOffsetPower;
    /* Returns an array of measurement status, margins, margin-frequencies, and absolute and relative powers corresponding to the margin-frequencies for lower offset segments. 
     * The relative powers are relative to the peak power in the carrier. */
    OffsetMarginArrayAttribute LowerOffsetMarginArray;
    /* Returns an array of total absolute and relative powers, peak absolute and relative powers and frequencies corresponding to the peak absolute powers of lower offset segments. 
     * The relative powers are relative to peak power of the carrier.*/
    OffsetPowerArrayAttribute LowerOffsetPowerArray;
    /* Returns an array of measurement status, margins, margin frequencies, absolute and relative powers corresponding to the margin-frequencies for upper offset segments. 
     * The relative powers are relative to the peak power in the carrier. */
    OffsetMarginArrayAttribute UpperOffsetMarginArray;
    /* Fetches an array of total absolute and relative powers, peak absolute and relative powers, and frequencies corresponding to the peak absolute powers of upper offset segments. 
     * The relative powers are relative to peak power of the carrier. */
    OffsetPowerArrayAttribute UpperOffsetPowerArray;
    /* Fetches the spectrum and mask traces.*/
    SpectrumAttribute Spectrum;  
}SEMResluts,*pSEMResluts;

typedef struct{
    DSSSModAccResults DSSS;
    OFDMModAccResults OFDMM;
    SEMResluts SEM;
}WlanResultsAttribute,*pWlanResultsAttribute;

class DLLAPI CCRFmxWlanStruct
{
public:
    CCRFmxWlanStruct();
    RfmxWlanField cfgWLAN;
    RfmxWlanDSSSModAccAttribute cfgDSSSModAcc;
    RfmxWlanOFDMModAccAttribute cfgOFDMModAcc;
    RfmxWlanSEMAttribute cfgSEM;

private:
    void WlanFields_SetDefault();
    void DSSSModAcc_SetDefault();
    void OFDMModAcc_SetDefault();
    void SEM_SetDefault();
};


class DLLAPI CCMxWlanResults : public CCResultsArray<WlanResultsAttribute>
{
public:
    CCMxWlanResults();
    ~CCMxWlanResults();
public:   
    void RemoveAll();
};

#endif	/* CCRFMXWLANTYPEDEF_H */

