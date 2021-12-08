/* 
 * File:   CCRfmxSpecAnTypeDef.h
 * Author: guiyuliang
 *
 * Created on 2020年10月28日, 下午3:59
 */

#pragma once

#ifndef CCRFMXSPECANTYPEDEF_H
#define	CCRFMXSPECANTYPEDEF_H

#include "CCResults.h"
#include "CCTesterDef.h"

/* The measurement uses the RBW that you specify in the RBW parameter.*/
#define CCRFMXSPECAN_VAL_SPECTRUM_RBW_AUTO_FALSE  (0)
/* The measurement computes the RBW. */
#define CCRFMXSPECAN_VAL_SPECTRUM_RBW_AUTO_TRUE   (1)

#define CCRFMXSPECAN_VAL_SPECTRUM_RBW_FILTER_TYPE_FFT_BASED (0)
#define CCRFMXSPECAN_VAL_SPECTRUM_RBW_FILTER_TYPE_GAUSSIAN (1) 
#define CCRFMXSPECAN_VAL_SPECTRUM_RBW_FILTER_TYPE_FLAT (2) 
#define CCRFMXSPECAN_VAL_SPECTRUM_RBW_FILTER_TYPE_SYNCH_TUNED_4 (3)
#define CCRFMXSPECAN_VAL_SPECTRUM_RBW_FILTER_TYPE_SYNCH_TUNED_5 (4)

#define CCRFMXSPECAN_VAL_SPECTRUM_POWER_UNITS_DBM (0)

#define CCRFMXSPECAN_VAL_SPECTRUM_AVERAGING_ENABLED_FALSE (0)
#define CCRFMXSPECAN_VAL_SPECTRUM_AVERAGING_ENABLED_TRUE (1)

#define CCRFMXSPECAN_VAL_SPECTRUM_SWEEP_TIME_AUTO_FALSE (0)

#define CCRFMXSPECAN_VAL_SPECTRUM_VBW_FILTER_AUTO_BANDWIDTH_False (0)

// Values for MeasurementTypes
#define CCRFMXSPECAN_VAL_ACP                                                                            1 << 0
#define CCRFMXSPECAN_VAL_CCDF                                                                           1 << 1
#define CCRFMXSPECAN_VAL_CHP                                                                            1 << 2
#define CCRFMXSPECAN_VAL_FCNT                                                                           1 << 3
#define CCRFMXSPECAN_VAL_HARMONICS                                                                      1 << 4
#define CCRFMXSPECAN_VAL_OBW                                                                            1 << 5
#define CCRFMXSPECAN_VAL_SEM                                                                            1 << 6
#define CCRFMXSPECAN_VAL_SPECTRUM                                                                       1 << 7
#define CCRFMXSPECAN_VAL_SPUR                                                                           1 << 8
#define CCRFMXSPECAN_VAL_TXP                                                                            1 << 9
#define CCRFMXSPECAN_VAL_AMPM                                                                           1 << 10
#define CCRFMXSPECAN_VAL_DPD                                                                            1 << 11
#define CCRFMXSPECAN_VAL_IQ                                                                             1 << 12
#define CCRFMXSPECAN_VAL_IM                                                                             1 << 13
#define CCRFMXSPECAN_VAL_NF                                                                             1 << 14
#define CCRFMXSPECAN_VAL_PHASENOISE                                                                     1 << 15
#define CCRFMXSPECAN_VAL_PAVT                                                                           1 << 16

// Values for RFMXSPECAN_ATTR_ACP_CARRIER_MODE
#define CCRFMXSPECAN_VAL_ACP_CARRIER_MODE_PASSIVE                                                       0
#define CCRFMXSPECAN_VAL_ACP_CARRIER_MODE_ACTIVE                                                        1

// Values for RFMXSPECAN_ATTR_ACP_OFFSET_RRC_FILTER_ENABLED
#define CCRFMXSPECAN_VAL_ACP_OFFSET_RRC_FILTER_ENABLED_FALSE                                            0
#define CCRFMXSPECAN_VAL_ACP_OFFSET_RRC_FILTER_ENABLED_TRUE                                             1

// Values for RFMXSPECAN_ATTR_ACP_OFFSET_FREQUENCY_DEFINITION
#define CCRFMXSPECAN_VAL_ACP_CARRIER_CENTER_TO_OFFSET_CENTER                                            0
#define CCRFMXSPECAN_VAL_ACP_CARRIER_CENTER_TO_OFFSET_EDGE                                              1

// Values for RFMXSPECAN_ATTR_ACP_OFFSET_SIDEBAND
#define CCRFMXSPECAN_VAL_ACP_OFFSET_SIDEBAND_NEGATIVE                                                   0
#define CCRFMXSPECAN_VAL_ACP_OFFSET_SIDEBAND_POSITIVE                                                   1
#define CCRFMXSPECAN_VAL_ACP_OFFSET_SIDEBAND_BOTH                                                       2

// Values for RFMXSPECAN_ATTR_ACP_OFFSET_POWER_REFERENCE_CARRIER
#define CCRFMXSPECAN_VAL_ACP_OFFSET_POWER_REFERENCE_CARRIER_CLOSEST                                     0
#define CCRFMXSPECAN_VAL_ACP_OFFSET_POWER_REFERENCE_CARRIER_HIGHEST                                     1
#define CCRFMXSPECAN_VAL_ACP_OFFSET_POWER_REFERENCE_CARRIER_COMPOSITE                                   2
#define CCRFMXSPECAN_VAL_ACP_OFFSET_POWER_REFERENCE_CARRIER_SPECIFIC                                    3

// Values for RFMXSPECAN_ATTR_ACP_MEASUREMENT_METHOD
#define CCRFMXSPECAN_VAL_ACP_MEASUREMENT_METHOD_NORMAL                                                  0
#define CCRFMXSPECAN_VAL_ACP_MEASUREMENT_METHOD_DYNAMIC_RANGE                                           1
#define CCRFMXSPECAN_VAL_ACP_MEASUREMENT_METHOD_SEQUENTIAL_FFT                                          2

// Values for RFMXSPECAN_ATTR_ACP_POWER_UNITS
#define CCRFMXSPECAN_VAL_ACP_POWER_UNITS_DBM                                                            0
#define CCRFMXSPECAN_VAL_ACP_POWER_UNITS_DBM_PER_HZ                                                     1

// Values for RFMXSPECAN_ATTR_ACP_AVERAGING_TYPE
#define CCRFMXSPECAN_VAL_ACP_AVERAGING_TYPE_RMS                                                         0
#define CCRFMXSPECAN_VAL_ACP_AVERAGING_TYPE_LOG                                                         1
#define CCRFMXSPECAN_VAL_ACP_AVERAGING_TYPE_SCALAR                                                      2
#define CCRFMXSPECAN_VAL_ACP_AVERAGING_TYPE_MAXIMUM                                                     3
#define CCRFMXSPECAN_VAL_ACP_AVERAGING_TYPE_MINIMUM                                                     4

// Values for RFMXSPECAN_ATTR_ACP_FFT_WINDOW
#define CCRFMXSPECAN_VAL_ACP_FFT_WINDOW_NONE                                                            0
#define CCRFMXSPECAN_VAL_ACP_FFT_WINDOW_FLAT_TOP                                                        1
#define CCRFMXSPECAN_VAL_ACP_FFT_WINDOW_HANNING                                                         2
#define CCRFMXSPECAN_VAL_ACP_FFT_WINDOW_HAMMING                                                         3
#define CCRFMXSPECAN_VAL_ACP_FFT_WINDOW_GAUSSIAN                                                        4
#define CCRFMXSPECAN_VAL_ACP_FFT_WINDOW_BLACKMAN                                                        5
#define CCRFMXSPECAN_VAL_ACP_FFT_WINDOW_BLACKMAN_HARRIS                                                 6
#define CCRFMXSPECAN_VAL_ACP_FFT_WINDOW_KAISER_BESSEL                                                   7

// Values for RFMXSPECAN_ATTR_ACP_RBW_FILTER_TYPE
#define CCRFMXSPECAN_VAL_ACP_RBW_FILTER_TYPE_FFT_BASED                                                  0
#define CCRFMXSPECAN_VAL_ACP_RBW_FILTER_TYPE_GAUSSIAN                                                   1
#define CCRFMXSPECAN_VAL_ACP_RBW_FILTER_TYPE_FLAT                                                       2

// Values for RFMXSPECAN_ATTR_ACP_RBW_FILTER_BANDWIDTH_DEFINITION
#define CCRFMXSPECAN_VAL_ACP_RBW_FILTER_BANDWIDTH_DEFINITION_3DB                                        0
#define CCRFMXSPECAN_VAL_ACP_RBW_FILTER_BANDWIDTH_DEFINITION_BIN_WIDTH                                  2

// Values for RFMXSPECAN_ATTR_ACP_SWEEP_TIME_AUTO
#define CCRFMXSPECAN_VAL_ACP_SWEEP_TIME_AUTO_FALSE                                                      0
#define CCRFMXSPECAN_VAL_ACP_SWEEP_TIME_AUTO_TRUE                                                       1

// Values for RFMXSPECAN_ATTR_ACP_RBW_FILTER_AUTO_BANDWIDTH
#define CCRFMXSPECAN_VAL_ACP_RBW_AUTO_FALSE                                                             0
#define CCRFMXSPECAN_VAL_ACP_RBW_AUTO_TRUE                                                              1

// Values for RFMXSPECAN_ATTR_ACP_OFFSET_ENABLED
#define CCRFMXSPECAN_VAL_ACP_OFFSET_FREQUENCY_ENABLED_FALSE                                             0
#define CCRFMXSPECAN_VAL_ACP_OFFSET_FREQUENCY_ENABLED_TRUE                                              1

// Values for RFMXSPECAN_ATTR_ACP_NOISE_COMPENSATION_ENABLED
#define CCRFMXSPECAN_VAL_ACP_NOISE_COMPENSATION_ENABLED_FALSE                                           0
#define CCRFMXSPECAN_VAL_ACP_NOISE_COMPENSATION_ENABLED_TRUE                                            1

// Values for RFMXSPECAN_ATTR_ACP_AVERAGING_ENABLED
#define CCRFMXSPECAN_VAL_ACP_AVERAGING_ENABLED_FALSE                                                    0
#define CCRFMXSPECAN_VAL_ACP_AVERAGING_ENABLED_TRUE                                                     1

// Values for RFMXSPECAN_ATTR_ACP_IF_OUTPUT_POWER_OFFSET_AUTO
#define CCRFMXSPECAN_VAL_ACP_IF_OUTPUT_POWER_OFFSET_AUTO_FALSE                                          0
#define CCRFMXSPECAN_VAL_ACP_IF_OUTPUT_POWER_OFFSET_AUTO_TRUE                                           1

// Values for RFMXSPECAN_ATTR_ACP_CARRIER_RRC_FILTER_ENABLED
#define CCRFMXSPECAN_VAL_ACP_CARRIER_RRC_FILTER_ENABLED_FALSE                                           0
#define CCRFMXSPECAN_VAL_ACP_CARRIER_RRC_FILTER_ENABLED_TRUE                                            1

// Values for RFMXSPECAN_ATTR_ACP_AMPLITUDE_CORRECTION_TYPE
#define CCRFMXSPECAN_VAL_ACP_AMPLITUDE_CORRECTION_TYPE_RF_CENTER_FREQUENCY                              0
#define CCRFMXSPECAN_VAL_ACP_AMPLITUDE_CORRECTION_TYPE_SPECTRUM_FREQUENCY_BIN                           1 

// Values for RFMXSPECAN_ATTR_ACP_OFFSET_RRC_FILTER_ENABLED
#define CCRFMXSPECAN_VAL_ACP_RRC_FILTER_ENABLED_FALSE                                                   0
#define CCRFMXSPECAN_VAL_ACP_RRC_FILTER_ENABLED_TRUE                                                    1

// Values for RFMXSPECAN_ATTR_ACP_OFFSET_ENABLED
#define CCRFMXSPECAN_VAL_ACP_OFFSET_ENABLED_FALSE                                                       0
#define CCRFMXSPECAN_VAL_ACP_OFFSET_ENABLED_TRUE                                                        1


// Values for RFMXSPECAN_ATTR_OBW_AVERAGING_ENABLED
#define CCRFMXSPECAN_VAL_OBW_AVERAGING_ENABLED_FALSE                                                    0
#define CCRFMXSPECAN_VAL_OBW_AVERAGING_ENABLED_TRUE                                                     1

// Values for RFMXSPECAN_ATTR_OBW_AVERAGING_TYPE
#define CCRFMXSPECAN_VAL_OBW_AVERAGING_TYPE_RMS                                                         0
#define CCRFMXSPECAN_VAL_OBW_AVERAGING_TYPE_LOG                                                         1
#define CCRFMXSPECAN_VAL_OBW_AVERAGING_TYPE_SCALAR                                                      2
#define CCRFMXSPECAN_VAL_OBW_AVERAGING_TYPE_MAXIMUM                                                     3
#define CCRFMXSPECAN_VAL_OBW_AVERAGING_TYPE_MINIMUM                                                     4

// Values for RFMXSPECAN_ATTR_OBW_FFT_WINDOW
#define CCRFMXSPECAN_VAL_OBW_FFT_WINDOW_NONE                                                            0
#define CCRFMXSPECAN_VAL_OBW_FFT_WINDOW_FLAT_TOP                                                        1
#define CCRFMXSPECAN_VAL_OBW_FFT_WINDOW_HANNING                                                         2
#define CCRFMXSPECAN_VAL_OBW_FFT_WINDOW_HAMMING                                                         3
#define CCRFMXSPECAN_VAL_OBW_FFT_WINDOW_GAUSSIAN                                                        4
#define CCRFMXSPECAN_VAL_OBW_FFT_WINDOW_BLACKMAN                                                        5
#define CCRFMXSPECAN_VAL_OBW_FFT_WINDOW_BLACKMAN_HARRIS                                                 6
#define CCRFMXSPECAN_VAL_OBW_FFT_WINDOW_KAISER_BESSEL                                                   7

// Values for RFMXSPECAN_ATTR_OBW_RBW_FILTER_AUTO_BANDWIDTH
#define CCRFMXSPECAN_VAL_OBW_RBW_AUTO_FALSE                                                             0
#define CCRFMXSPECAN_VAL_OBW_RBW_AUTO_TRUE                                                              1

// Values for RFMXSPECAN_ATTR_OBW_RBW_FILTER_TYPE
#define CCRFMXSPECAN_VAL_OBW_RBW_FILTER_TYPE_FFT_BASED                                                  0
#define CCRFMXSPECAN_VAL_OBW_RBW_FILTER_TYPE_GAUSSIAN                                                   1
#define CCRFMXSPECAN_VAL_OBW_RBW_FILTER_TYPE_FLAT                                                       2

// Values for RFMXSPECAN_ATTR_OBW_RBW_FILTER_BANDWIDTH_DEFINITION
#define CCRFMXSPECAN_VAL_OBW_RBW_FILTER_BANDWIDTH_DEFINITION_3DB                                        0
#define CCRFMXSPECAN_VAL_OBW_RBW_FILTER_BANDWIDTH_DEFINITION_BIN_WIDTH                                  2

// Values for RFMXSPECAN_ATTR_OBW_SWEEP_TIME_AUTO
#define CCRFMXSPECAN_VAL_OBW_SWEEP_TIME_AUTO_FALSE                                                      0
#define CCRFMXSPECAN_VAL_OBW_SWEEP_TIME_AUTO_TRUE                                                       1

// Values for RFMXSPECAN_ATTR_OBW_POWER_UNITS
#define CCRFMXSPECAN_VAL_OBW_POWER_UNITS_DBM                                                            0
#define CCRFMXSPECAN_VAL_OBW_POWER_UNITS_DBM_PER_HZ                                                     1

// Values for RFMXSPECAN_ATTR_OBW_AMPLITUDE_CORRECTION_TYPE
#define CCRFMXSPECAN_VAL_OBW_AMPLITUDE_CORRECTION_TYPE_RF_CENTER_FREQUENCY                              0
#define CCRFMXSPECAN_VAL_OBW_AMPLITUDE_CORRECTION_TYPE_SPECTRUM_FREQUENCY_BIN                           1

// Values for RFMXSPECAN_ATTR_CHP_AVERAGING_TYPE
#define CCRFMXSPECAN_VAL_CHP_AVERAGING_TYPE_RMS                                                         0
#define CCRFMXSPECAN_VAL_CHP_AVERAGING_TYPE_LOG                                                         1
#define CCRFMXSPECAN_VAL_CHP_AVERAGING_TYPE_SCALAR                                                      2
#define CCRFMXSPECAN_VAL_CHP_AVERAGING_TYPE_MAXIMUM                                                     3
#define CCRFMXSPECAN_VAL_CHP_AVERAGING_TYPE_MINIMUM                                                     4

// Values for RFMXSPECAN_ATTR_CHP_FFT_WINDOW
#define CCRFMXSPECAN_VAL_CHP_FFT_WINDOW_NONE                                                            0
#define CCRFMXSPECAN_VAL_CHP_FFT_WINDOW_FLAT_TOP                                                        1
#define CCRFMXSPECAN_VAL_CHP_FFT_WINDOW_HANNING                                                         2
#define CCRFMXSPECAN_VAL_CHP_FFT_WINDOW_HAMMING                                                         3
#define CCRFMXSPECAN_VAL_CHP_FFT_WINDOW_GAUSSIAN                                                        4
#define CCRFMXSPECAN_VAL_CHP_FFT_WINDOW_BLACKMAN                                                        5
#define CCRFMXSPECAN_VAL_CHP_FFT_WINDOW_BLACKMAN_HARRIS                                                 6
#define CCRFMXSPECAN_VAL_CHP_FFT_WINDOW_KAISER_BESSEL                                                   7

// Values for RFMXSPECAN_ATTR_CHP_RBW_FILTER_AUTO_BANDWIDTH
#define CCRFMXSPECAN_VAL_CHP_RBW_AUTO_FALSE                                                             0
#define CCRFMXSPECAN_VAL_CHP_RBW_AUTO_TRUE                                                              1

// Values for RFMXSPECAN_ATTR_CHP_RBW_FILTER_TYPE
#define CCRFMXSPECAN_VAL_CHP_RBW_FILTER_TYPE_FFT_BASED                                                  0
#define CCRFMXSPECAN_VAL_CHP_RBW_FILTER_TYPE_GAUSSIAN                                                   1
#define CCRFMXSPECAN_VAL_CHP_RBW_FILTER_TYPE_FLAT                                                       2

// Values for RFMXSPECAN_ATTR_CHP_RBW_FILTER_BANDWIDTH_DEFINITION
#define CCRFMXSPECAN_VAL_CHP_RBW_FILTER_BANDWIDTH_DEFINITION_3DB                                        0
#define CCRFMXSPECAN_VAL_CHP_RBW_FILTER_BANDWIDTH_DEFINITION_BIN_WIDTH                                  2

// Values for RFMXSPECAN_ATTR_CHP_CARRIER_RRC_FILTER_ENABLED
#define CCRFMXSPECAN_VAL_CHP_CARRIER_RRC_FILTER_ENABLED_FALSE                                           0
#define CCRFMXSPECAN_VAL_CHP_CARRIER_RRC_FILTER_ENABLED_TRUE                                            1

// Values for RFMXSPECAN_ATTR_CHP_SWEEP_TIME_AUTO
#define CCRFMXSPECAN_VAL_CHP_SWEEP_TIME_AUTO_FALSE                                                      0
#define CCRFMXSPECAN_VAL_CHP_SWEEP_TIME_AUTO_TRUE                                                       1

// Values for RFMXSPECAN_ATTR_CHP_AMPLITUDE_CORRECTION_TYPE
#define CCRFMXSPECAN_VAL_CHP_AMPLITUDE_CORRECTION_TYPE_RF_CENTER_FREQUENCY                              0
#define CCRFMXSPECAN_VAL_CHP_AMPLITUDE_CORRECTION_TYPE_SPECTRUM_FREQUENCY_BIN                           1

// Values for RFMXSPECAN_ATTR_IQ_BANDWIDTH_AUTO
#define CCRFMXSPECAN_VAL_IQ_AUTO_BANDWIDTH_FALSE                                                        0
#define CCRFMXSPECAN_VAL_IQ_AUTO_BANDWIDTH_TRUE                                                         1

// Values for RFMXSPECAN_ATTR_IQ_DELETE_RECORD_ON_FETCH
#define CCRFMXSPECAN_VAL_IQ_DELETE_RECORD_ON_FETCH_FALSE                                                0
#define CCRFMXSPECAN_VAL_IQ_DELETE_RECORD_ON_FETCH_TRUE                                                 1

/* USE CHP instead of SPECTRUM*/
#ifndef USE_SPEC_SPLIT
#define USE_SPEC_SPLIT
#endif

typedef struct{
    /* Specifies whether to apply the root-raised-cosine (RRC) filter on the acquired carrier channel before measuring the carrier channel power. 
     * RFMXSPECAN_VAL_CHP_RRC_FILTER_ENABLED_FALSE (0)  The measurement measures the channel power directly on the acquired channel. 
     * RFMXSPECAN_VAL_CHP_RRC_FILTER_ENABLED_TRUE (1)   The measurement applies the RRC filter on the acquired channel before measuring the channel power.
     */
    ViInt32 nRRCFilterEnabled;
    /* Specifies the roll-off factor for the root-raised-cosine (RRC) filter.*/
    ViReal64 dRRCAlpha;
}RRCFilterAttribute,*pRRCFilterAttribute;


typedef struct{
    /* Specifies whether the measurement computes the RBW. Refer to the RBW and Sweep Time section in the Spectrum topic for more information about RBW and sweep time. 
     * RFMXSPECAN_VAL_SPECTRUM_RBW_AUTO_FALSE (0)       The measurement uses the RBW that you specify in the RBW parameter. 
     * RFMXSPECAN_VAL_SPECTRUM_RBW_AUTO_TRUE (1)        The measurement computes the RBW. 
     */
    ViInt32 nRBWAuto;
    /* Specifies the bandwidth, in hertz (Hz), of the RBW filter used to sweep the acquired carrier signal, when you set the RBWAuto parameter to RFMXSPECAN_VAL_SPECTRUM_RBW_AUTO_FALSE.*/
    ViReal64 dwRBW;
    /* Specifies the shape of the digital RBW filter. 
     * RFMXSPECAN_VAL_SPECTRUM_RBW_FILTER_TYPE_FFT_BASED (0)            No RBW filtering is performed. 
     * RFMXSPECAN_VAL_SPECTRUM_RBW_FILTER_TYPE_GAUSSIAN (1)             An RBW filter with a Gaussian response is applied. 
     * RFMXSPECAN_VAL_SPECTRUM_RBW_FILTER_TYPE_FLAT (2)                 An RBW filter with a flat response is applied. 
     * RFMXSPECAN_VAL_SPECTRUM_RBW_FILTER_TYPE_SYNCH_TUNED_4 (3)        An RBW filter with a 4-pole synchronously-tuned response is applied.
     * RFMXSPECAN_VAL_SPECTRUM_RBW_FILTER_TYPE_SYNCH_TUNED_5 (4)        An RBW filter with a 5-pole synchronously-tuned response is applied.
     */
    ViInt32 nRBWFilterType;
}RBWFilterAttribute,*pRBWFilterAttribute;


typedef struct{
    /* Specifies whether to enable averaging for the measurement. 
     * RFMXSPECAN_VAL_SPECTRUM_AVERAGING_ENABLED_FALSE (0)      The measurement is performed on a single acquisition. 
     * RFMXSPECAN_VAL_SPECTRUM_AVERAGING_ENABLED_TRUE (1)       The measurement uses the averagingCount parameter to calculate the number of acquisitions over which the measurement is averaged. 
     */
    ViInt32 nAveragingEnabled;
    /* Specifies the number of acquisitions used for averaging when you set the averagingEnabled parameter to RFMXSPECAN_VAL_SPECTRUM_AVERAGING_ENABLED_TRUE.*/
    ViInt32 nAveragingCount;
    /* Specifies the averaging type for averaging multiple spectrum acquisitions. The averaged spectrum is used for the measurement. Refer to the Averaging section of the Spectrum topic for more information about averaging types. 
     * RFMXSPECAN_VAL_SPECTRUM_AVERAGING_TYPE_RMS (0)           The power spectrum is linearly averaged. RMS averaging reduces signal fluctuations but not the noise floor. 
     * RFMXSPECAN_VAL_SPECTRUM_AVERAGING_TYPE_LOG (1)           The power spectrum is averaged in a logarithm scale. 
     * RFMXSPECAN_VAL_SPECTRUM_AVERAGING_TYPE_SCALAR (2)        The square root of the power spectrum is averaged. 
     * RFMXSPECAN_VAL_SPECTRUM_AVERAGING_TYPE_MAXIMUM (3)       The peak power in the spectrum at each frequency bin is retained from one acquisition to the next. 
     * RFMXSPECAN_VAL_SPECTRUM_AVERAGING_TYPE_MINIMUM (4)       The least power in the spectrum at each frequency bin is retained from one acquisition to the next.
     */
    ViInt32 nAveragingType;
}AveragingAttribute,*pAveragingAttribute;

typedef struct{
    /* Specifies whether the measurement computes the sweep time. 
     * RFMXSPECAN_VAL_SPECTRUM_SWEEP_TIME_AUTO_FALSE (0)        The measurement uses the sweep time that you specify in the sweepTimeInterval parameter. 
     * RFMXSPECAN_VAL_SPECTRUM_SWEEP_TIME_AUTO_TRUE (1)         The measurement calculates the sweep time based on the value of the RFMXSPECAN_ATTR_SPECTRUM_RBW_FILTER_BANDWIDTH attribute. 
     */
    ViInt32 nSweepTimeAuto;
    /* Specifies the sweep time, in seconds, when you set the sweepTimeAuto parameter to RFMXSPECAN_VAL_SPECTRUM_SWEEP_TIME_AUTO_FALSE.*/
    ViReal64 dSweepTimeInterval;
}SweepTimeAttribute,*pSweepTimeAttribute;

typedef struct{
    /* Specifies the FFT window type to use to reduce spectral leakage. Refer to the Window and FFT section of the Spectrum topic for more information about FFT window types. 
     * RFMXSPECAN_VAL_SPECTRUM_FFT_WINDOW_NONE (0)              Analyzes transients for which duration is shorter than the window length. You can also use this window type to separate two tones with frequencies close to each other but with almost equal amplitudes. 
     * RFMXSPECAN_VAL_SPECTRUM_FFT_WINDOW_FLAT_TOP (1)          Measures single-tone amplitudes accurately. 
     * RFMXSPECAN_VAL_SPECTRUM_FFT_WINDOW_HANNING (2)           Analyzes transients for which duration is longer than the window length. You can also use this window type to provide better frequency resolution for noise measurements. 
     * RFMXSPECAN_VAL_SPECTRUM_FFT_WINDOW_HAMMING (3)           Analyzes closely-spaced sine waves. 
     * RFMXSPECAN_VAL_SPECTRUM_FFT_WINDOW_GAUSSIAN (4)          Provides a good balance of spectral leakage, frequency resolution, and amplitude attenuation. Hence, this windowing is useful for time-frequency analysis. 
     * RFMXSPECAN_VAL_SPECTRUM_FFT_WINDOW_BLACKMAN (5)          Analyzes single tone because it has a low maximum side lobe level and a high side lobe roll-off rate. 
     * RFMXSPECAN_VAL_SPECTRUM_FFT_WINDOW_BLACKMAN_HARRIS (6)   Useful as a good general purpose window, having side lobe rejection >90dB and having a moderately wide main lobe. 
     * RFMXSPECAN_VAL_SPECTRUM_FFT_WINDOW_KAISER_BESSEL (7)     Separates two tones with frequencies close to each other but with widely-differing amplitudes. 
     */
    ViInt32 nFFTWindow;
    /* Specifies the factor by which the time-domain waveform is zero-padded before FFT. 
     * The FFT size is given by the following formula: waveform size * padding. 
     * This parameter is used only when the acquisition span is less than the device instantaneous bandwidth of the device.
     */
    ViReal64 dFFTPadding;
}FFTAttribute,*pFFTAttribute;

typedef struct{
    /* Specifies whether the VBW is expressed directly or computed based on VBW to RBW ratio. This value is expressed in Hz. 
     * RFMXSPECAN_VAL_SPECTRUM_VBW_FILTER_AUTO_BANDWIDTH_False (0)      Specify the video bandwidth in the VBW parameter. The VBWToRBWRatio parameter is disregarded in this mode.
     * RFMXSPECAN_VAL_SPECTRUM_VBW_FILTER_AUTO_BANDWIDTH_True (1)       Specify video bandwidth in terms of the VBW to RBW ratio. 
     *                                                                  The value of the video bandwidth is then computed by using the RFMXSPECAN_ATTR_SPECTRUM_VBW_FILTER_VBW_TO_RBW_RATIO attribute 
     *                                                                  and the RFMXSPECAN_ATTR_SPECTRUM_RBW_FILTER_AUTO_BANDWIDTH attribute. The value of the VBW parameter is disregarded in this mode.
     */
    ViInt32 nVBWAuto;
    /* Specifies the video bandwidth when you set the VBWAuto parameter RFMXSPECAN_VAL_SPECTRUM_VBW_FILTER_AUTO_BANDWIDTH_False. This value is expressed in Hz.*/
    ViReal64 dwVBW;
    /* Specifies the VBW to RBW Ratio when you set the VBWAuto parameter to RFMXSPECAN_VAL_SPECTRUM_VBW_FILTER_AUTO_BANDWIDTH_True. */
    ViReal64 dwVBWToRBWRatio;
}VBWFilterAttribute,*pVBWFilterAttribute;

typedef struct{
    /* Specifies the frequency range, in Hz, over which the measurement integrates the carrier power. */
    ViReal64 dwIntegrationBandwidth;
    /* Specifies the number of offset channels. */
    ViInt32 nNumberOfOffsets;
    /* Specifies the spacing between offset channels. */
    ViReal64 dwChannelSpacing;
}ACPcfgCarrierandOffsetsAttribute,*pACPcfgCarrierandOffsetsAttribute;

typedef struct{
    /* Specifies an array of center or edge frequencies, in Hz, of the offset channel, relative to the center frequency of the closest carrier as determined by the RFMXSPECAN_ATTR_ACP_OFFSET_FREQUENCY_DEFINITION attribute. 
     * The sign of offset frequency is ignored and the RFMXSPECAN_ATTR_ACP_OFFSET_SIDEBAND attribute determines whether the upper, lower, or both offsets are measured.*/
    ViReal64* pOffsetFrequency;
    /* Specifies whether the offset segment is present on one side, or on both sides of the carriers. Specify NULL if you do not want to set a value for this array. */
    ViInt32* pOffsetSideband;
    /* Specifies whether to enable the offset channel for ACP measurement. Specify NULL if you do not want to set a value for this array. */
    ViInt32* pOffsetEnabled;
    /* Specifies the number of elements in each array. */
    ViInt32 nNumberOfElements;
}ACPcfgOffsetArray,*pACPcfgOffsetArray;

typedef struct{
    /* Specifies an array of frequency ranges, in Hz, over which the measurement integrates the offset channel power. Specify NULL if you do not want to set a value for this array.*/
    ViReal64* pIntegrationBandwidth;
    /* Specifies the number of elements in each array. */
    ViInt32 nNumberOfElements;
}ACPcfgOffsetIntegragrationBandwidthArray,*pACPcfgOffsetIntegragrationBandwidthArray;

typedef struct{
    /* Specifies the array of carriers to be used as power reference to measure offset channel relative power.
     *  The offset channel power is measured only if you set the RFMXSPECAN_ATTR_ACP_CARRIER_MODE attribute of the reference carrier to RFMXSPECAN_VAL_ACP_CARRIER_MODE_ACTIVE. 
     * Specify NULL if you do not want to set a value for this array. .*/
    ViInt32* pOffsetPowerReferenceCarrier;
    /* Specifies the array of carrier indexes to use as the reference carrier for each offset channel. 
     * The power measured in this carrier is used as the power reference for measuring the offset channel relative power, when you set the offsetPowerReferenceCarrier parameter to RFMXSPECAN_VAL_ACP_OFFSET_POWER_REFERENCE_CARRIER_SPECIFIC.
     *  Specify NULL if you do not want to set a value for this array. */
    ViInt32* pOffsetPowerReferenceSpecific;
    /* Specifies the number of elements in each array. */
    ViInt32 nNumberOfElements;
}ACPcfgOffsetPowerReferenceArray,*pACPcfgOffsetPowerReferenceArray;

typedef struct{
    /* Specifies whether to apply the RRC filter on the acquired offset channel before measuring the offset channel power. Specify NULL if you do not want to set a value for this array..*/
    ViInt32* pRRCFilterEnabled;
    /* Specifies an array of roll-off factors of the RRC filter to apply on the acquired offset channel before measuring the offset channel power. Specify NULL if you do not want to set a value for this array. */
    ViReal64* pRRCAlpha;
    /* Specifies the number of elements in each array. */
    ViInt32 nNumberOfElements;
}ACPcfgOffsetRRCFilterArray,*pACPcfgOffsetRRCFilterArray;

typedef struct{
    /* Specifies the carrier to be used as power reference to measure offset channel relative power. 
     * The offset channel power is measured only if you set the RFMXSPECAN_ATTR_ACP_CARRIER_MODE attribute of the reference carrier to RFMXSPECAN_VAL_ACP_CARRIER_MODE_ACTIVE. */
    ViInt32 nOffsetReferenceCarrier;
    /* Specifies the index of the carrier to be used as the reference carrier. 
     * The power measured in this carrier is used as the power reference for measuring the offset channel relative power, 
     * when you set the offsetReferenceCarrier parameter to RFMXSPECAN_VAL_ACP_OFFSET_REFERENCE_CARRIER_SPECIFIC. */
    ViInt32 nOffsetReferenceSpecific;
}ACPcfgOffsetPowerReference,*pACPcfgOffsetPowerReference;

typedef struct{
    /* Specifies whether to consider the carrier power as part of total carrier power measurement. */
    ViInt32 nCarrierMode;
    /* Specifies the center frequency, in Hz, of the carrier, relative to the RF center frequency. */
    ViReal64 dwCarrierFrequency;
    /* Specifies the frequency range, in Hz, over which the measurement integrates the carrier power. */
    ViReal64 dwIntegrationBandwidth;
    /* Configures the root-raised-cosine (RRC) filter to apply on the carrier channel before measuring the carrier channel power. */
    RRCFilterAttribute RRCFilter;
}ACPcfgCarrierAttribute,*pACPcfgCarrierAttribute;

typedef struct{
    /* Specifies the number of offset channels. */
    ViInt32 nNumberOfOffsets;
    /* Configures an offset channel on one or both sides of carrier with center-to-center spacing as specified by the offset frequency and offset frequency definition. 
     * In case of multiple carriers, offset frequency is relative to the closest carrier. */
    ACPcfgOffsetArray OffsetArray;
    /* Specifies the frequency range, in Hz, over which the measurement integrates the carrier power. */
    ACPcfgOffsetIntegragrationBandwidthArray IntegrationBandwidthArray;
    /* Configures the power reference to use for measuring the relative power of the offset channel. */
    ACPcfgOffsetPowerReferenceArray PowerReferenceArray;
    /* Specifies the attenuation, in dB, relative to the external attenuation. Use this parameter to compensate for variations in external attenuation when the offset channels are spread wide in frequency. */
    ACPcfgOffsetIntegragrationBandwidthArray RelativeAttenuationArray;
    /* Configures the root raised cosine (RRC) channel filter to be applied on the offset channel before measuring channel power. */
    ACPcfgOffsetRRCFilterArray RRCFilterArray;
    /* Specifies the offset frequency definition. The default value is RFMXSPECAN_VAL_ACP_CARRIER_CENTER_TO_OFFSET_CENTER. */
    ViInt32 *pOffsetFrequencyDefinition;
}ACPcfgOffsetsAttribute,*pACPcfgOffsetsAttribute;

typedef struct{
    ViReal64 dwSampleNumbers;
    /* Specifies the resolution bandwidth of a spectrum acquisition. The value is expressed in hertz (Hz). \
     * Configure the type of resolution bandwidth with the NIRFSA_ATTR_RESOLUTION_BANDWIDTH_TYPE attribute.
     */
    ViReal64 dwSampleRate;
    /* Specifies the frequency range, in Hz, over which the measurement integrates the carrier power.*/
    ViReal64 dIntegrationBandwidth;
    /* Configures the root raised cosine (RRC) filter to apply on the channel before measuring the channel power.*/
    RRCFilterAttribute RRCFilter;
    RBWFilterAttribute RBWFilter;
    SweepTimeAttribute SweepTime;
    AveragingAttribute Averaging;
    FFTAttribute FFT;
    /* Configures the number of carriers for a channel power (CHP) measurement.*/
    ViInt32 nNumberOfCarriers;
    /* Specifies the center frequency, in Hz, of the carrier, relative to the RF center frequency.*/
    ViReal64 dCarrierFrequency;
}CfgCHPAttribute,*pCfgCHPAttribute;

typedef struct{
    /* Specifies the frequency of the tone that has a lower frequency among the two tones in the input signal. This value is expressed in Hz.*/
    ViReal64 dLowerToneFrequency;
    /* Specifies the frequency of the tone that has a higher frequency among the two tones in the input signal. This value is expressed in Hz.*/
    ViReal64 dUpperToneFrequency;
}TwoTonesAttribute,*pTwoTonesAttribute;

typedef struct{
    /*Specifies whether the measurement computes the intermod frequencies or uses manually specified frequencies. 
     * RFMXSPECAN_VAL_IM_AUTO_INTERMODS_SETUP_ENABLED_FALSE (0)         The measurement uses the values that you specify for the 
     *                                                                  RFMXSpecAn_ATTR_IM_LOWER_INTERMOD_FREQUENCY and 
     *                                                                  RFMXSpecAn_ATTR_IM_UPPER_INTERMOD_FREQUENCY attributes.
     * RFMXSPECAN_VAL_IM_AUTO_INTERMODS_SETUP_ENABLED_TRUE (1)          The measurement computes intermod frequencies. 
     *                                                                  The number of intermods to measure is based on the value 
     *                                                                  of the maximumIntermodOrder parameter.
     */
    ViInt32 nAutoIntermodsSetupEnabled;
    /* Specifies the order up to which the RFmx driver measures odd order intermodulation products when you set the autoIntermodsSetupEnabled 
     * parameter to RFMXSPECAN_VAL_IM_AUTO_INTERMODS_SETUP_ENABLED_TRUE. The lower and upper intermodulation products are measured for each order.
     */
    ViInt32 nMaximumIntermodOrder;
    /* Specifies the number of intermods to measure when you set the RFMXSpecAn_ATTR_IM_AUTO_INTERMODS_SETUP_ENABLED attribute to 
      * RFMXSPECAN_VAL_IM_AUTO_INTERMODS_SETUP_ENABLED_FALSE. 
      */
     ViInt32 nNumberOfIntermods;
}IntermodsSetupAttribute,*pIntermodsSetupAttribute;


typedef struct{
    /* Specifies the order of the intermod.*/
    ViInt32 nIntermodOrder;
    /* Specifies the frequency of the lower intermodulation product. This value is expressed in Hz.*/
    ViReal64 dLowerIntermodFrequency;
    /* Specifies the frequency of the upper intermodulation product. This value is expressed in Hz. */
    ViReal64 dUpperIntermodFrequency;
    /* Specifies whether to measure intermodulation products corresponding to both lower and upper intermod frequencies or either one of them. 
     * RFMXSPECAN_VAL_IM_INTERMOD_SIDE_LOWER (0)  Measures the intermodulation product corresponding to the lowerIntermodFrequency parameter.
     * RFMXSPECAN_VAL_IM_INTERMOD_SIDE_UPPER (1)  Measures the intermodulation product corresponding to the upperIntermodFrequency parameter.
     * RFMXSPECAN_VAL_IM_INTERMOD_SIDE_BOTH (2)   Measures the intermodulation product corresponding to both lowerIntermodFrequency and upperIntermodFrequency parameters.
     */
    ViInt32 nIntermodSide;
    /* Specifies whether to enable an intermod for the IM measurement. 
     * RFMXSPECAN_VAL_IM_INTERMOD_ENABLED_FALSE (0)  Disables an intermod for the IM measurement. The results for the disabled intermods are displayed as NaN.
     * RFMXSPECAN_VAL_IM_INTERMOD_ENABLED_TRUE (1)  Enables an intermod for the IM measurement.
     */
    ViInt32 nIntermodEnabled;
}IntermodAttribute,*pIntermodAttribute;

typedef struct{
    /* Specifies whether you can specify the tones and intermod frequencies as either relative to the RF center frequency or 
     * as absolute frequencies.
     * RFMXSPECAN_VAL_IM_FREQUENCY_DEFINITION_RELATIVE (0)  The tone and intermod frequencies are relative to the RF center frequency.
     * RFMXSPECAN_VAL_IM_FREQUENCY_DEFINITION_ABSOLUTE (1)  The tone and intermod frequencies are absolute frequencies. 
     *                                                      The measurement ignores the RF center frequency.
     */
    ViInt32 nFrequencyDefinition;
    /* Configures the frequencies of the upper and lower frequencies in a two-tone input signal.*/
    TwoTonesAttribute TwoTones;
    /* Configures whether the measurement computes the intermod frequencies or uses manually specified frequencies.*/
    IntermodsSetupAttribute IntermodsSetup;
    /* Specifies the method for performing the IM measurement. 
     * RFMXSPECAN_VAL_IM_MEASUREMENT_METHOD_NORMAL (0)  
     *          The IM measurement acquires the spectrum using the same signal analyzer settings across frequency bands. 
     *          Use this method when the fundamental tone separation is not large. 
     *          Supported devices:PXIe-5644/5645/5646/5840/5841/5830/5831, PXIe-5663/5665/5668.
     * RFMXSPECAN_VAL_IM_MEASUREMENT_METHOD_DYNAMIC_RANGE (1)  
     *          The IM measurement acquires a segmented spectrum using the signal analyzer specific optimizations for different frequency bands. 
     *          The spectrum is acquired in segments, one per tone or intermod frequency to be measured. 
     *          The span of each acquired spectral segment is equal to the frequency separation between the two input tones, or 1 MHz, 
     *          whichever is smaller.
     *          Use this method to configure the IM measurement and the signal analyzer for maximum dynamic range instead of measurement speed.
     *          Supported devices:PXIe-5665/5668
     * RFMXSPECAN_VAL_IM_MEASUREMENT_METHOD_SEGMENTED (2)  
     *          Similar to the dynamicRange method, this method also acquires a segmented spectrum, 
     *          except that signal analyzer is not explicitly configured to provide maximum dynamic range. 
     *          Use this method when the frequency separation of the two input tones is large and the measurement 
     *          accuracy can be traded off for measurement speed.
     *          Supported devices:PXIe-5644/5645/5646/5840/5841/5830/5831, PXIe-5663/5665/5668
     */
     ViInt32 nMeasurementMethod;
     /* Configures the intermod order, intermod side, lower intermod frequency, and upper intermod frequency when you set the 
      * RFMXSpecAn_ATTR_IM_AUTO_INTERMODS_SETUP_ENABLED attribute to RFMXSPECAN_VAL_IM_AUTO_INTERMODS_SETUP_ENABLED_FALSE.
      */
     IntermodAttribute Intermod;
     /* Configures the RBW filter.*/
    RBWFilterAttribute RBWFilter;
    /* Configures the sweep time.*/
    SweepTimeAttribute SweepTime;
    /* Configures averaging for the IM measurement.*/
    AveragingAttribute Averaging;
    /* Configures the window and FFT to obtain a spectrum for the IM measurement.*/
    FFTAttribute FFT;
}cfgIMAttribute,*pCfgIMAttribute;

typedef struct{
    /* Specifies the span of a spectrum acquisition. The value is expressed in hertz (Hz).*/
    ViReal64 dwSampleNumbers;
    /* Specifies the resolution bandwidth of a spectrum acquisition. The value is expressed in hertz (Hz). \
     * Configure the type of resolution bandwidth with the NIRFSA_ATTR_RESOLUTION_BANDWIDTH_TYPE attribute.
     */
    ViReal64 dwSampleRate;
    /* Specifies the units for the absolute power. 
     * RFMXSPECAN_VAL_SPECTRUM_POWER_UNITS_DBM (0)              The absolute powers are reported in dBm. 
     * RFMXSPECAN_VAL_SPECTRUM_POWER_UNITS_DBM_PER_HZ (1)       The absolute powers are reported in dBm/Hz. 
     * RFMXSPECAN_VAL_SPECTRUM_POWER_UNITS_DBW (2)              The absolute powers are reported in dBW. 
     * RFMXSPECAN_VAL_SPECTRUM_POWER_UNITS_DBV (3)              The absolute powers are reported in dBV. 
     * RFMXSPECAN_VAL_SPECTRUM_POWER_UNITS_DBMV (4)             The absolute powers are reported in dBmV. 
     * RFMXSPECAN_VAL_SPECTRUM_POWER_UNITS_DBUV (5)             The absolute powers are reported in dBuV. 
     * RFMXSPECAN_VAL_SPECTRUM_POWER_UNITS_WATTS (6)            The absolute powers are reported in W. 
     * RFMXSPECAN_VAL_SPECTRUM_POWER_UNITS_VOLTS (7)            The absolute powers are reported in volts. 
     * RFMXSPECAN_VAL_SPECTRUM_POWER_UNITS_VOLTS_SQUARED (8)    The absolute powers are reported in volts2.
     */
    ViInt32 nSpectrumPowerUnits;
    /* Configures the resolution bandwidth (RBW) filter*/
    RBWFilterAttribute RBWFilter;
    /* Configures the sweep time.*/
    SweepTimeAttribute SweepTime;
    /* Configures averaging for the spectrum measurement.*/
    AveragingAttribute Averaging;
    /* Configures the VBW settings including VBW Auto, VBW(Hz) and VBW to RBW ratio.*/
    VBWFilterAttribute VBWFilter;
    /* Configures window and FFT to obtain a spectrum for the spectrum measurement.*/
    FFTAttribute FFT;
}cfgSpectrumAttribute,*pCfgSpectrumAttribute;

typedef struct{
    /* Specifies the span of a spectrum acquisition. The value is expressed in hertz (Hz).*/
    ViReal64 dwSampleNumbers;
    /* Specifies the resolution bandwidth of a spectrum acquisition. The value is expressed in hertz (Hz). \
     * Configure the type of resolution bandwidth with the NIRFSA_ATTR_RESOLUTION_BANDWIDTH_TYPE attribute.
     */
    ViReal64 dwSampleRate;
    /* Specifies the percentage of the total power that is contained in the OBW.*/
    ViReal64 dBandwidthPercentage;
    /* Specifies the units for the absolute power. 
     * RFMXSPECAN_VAL_OBW_POWER_UNITS_DBM (0)           The absolute powers are reported in dBm. 
     * RFMXSPECAN_VAL_OBW_POWER_UNITS_DBM_PER_HZ (1)    The absolute powers are reported in dBm/Hz.
     */
    ViInt32 nPowerUnits;
    /* Configures the resolution bandwidth (RBW) filter*/
    RBWFilterAttribute RBWFilter;
    /* Configures the sweep time.*/
    SweepTimeAttribute SweepTime;
    /* Configures averaging for the spectrum measurement.*/
    AveragingAttribute Averaging;
    /* Configures window and FFT to obtain a spectrum for the spectrum measurement.*/
    FFTAttribute FFT;
}cfgOBWAttribute,*pCfgOBWAttribute;

typedef struct{
    /* Specifies the acquisition sample rate, in samples per second (S/s). */
    ViReal64 dSampleRate;
    ViReal64 dwSampleNumbers;
    /* Specifies the number of records to acquire.*/
    ViInt32 nNumberOfRecords;
    /* Specifies the pretrigger time, in seconds, for the I/Q measurement.*/
    ViReal64 dPretriggerTime;
    /* Specifies whether the measurement computes the minimum acquisition bandwidth. 
     * RFMXSPECAN_VAL_IQ_AUTO_BANDWIDTH_FALSE (0) The measurement uses the value of the bandwidth parameter as the minimum acquisition bandwidth.
     * RFMXSPECAN_VAL_IQ_AUTO_BANDWIDTH_TRUE (1) The measurement uses 0.8 * sample rate as the minimum signal bandwidth. 
     */
    ViInt32 nBandwidthAuto;
    /* Specifies the minimum acquisition bandwidth, in hertz (Hz), when you set the bandwidthAuto parameter to RFMXSPECAN_VAL_IQ_AUTO_BANDWIDTH_FALSE.*/
    ViReal64 dBandwidth;
}cfgIQAttribute,*pCfgIQAttribute;


typedef struct{
    /* Specifies the attritube of carrier and offsets. */
    ACPcfgCarrierandOffsetsAttribute CarrierandOffsets;
    /* Specifies the number of carriers. */
    ViInt32 nNumberOfCarriers;
    ACPcfgCarrierAttribute *pCarrier;
    ACPcfgOffsetsAttribute Offsets;
    RBWFilterAttribute RBWFilter;
    SweepTimeAttribute SweepTime;
    AveragingAttribute Averaging;
    FFTAttribute FFT;
    /* Specifies the units for the absolute power. */
    ViInt32 nPowerUnits;
    /* Specifies the method for performing the ACP measurement. */
    ViInt32 nMeasurementMethod;
    /* Specifies whether to enable compensation of the channel powers for the inherent noise floor of the signal analyzer. */
    ViInt32 nNoiseCompensationEnabled;
}cfgACPAttribute,*pCfgACPAttribute;

typedef struct{
    /* Specifies the start frequency of the offset frequency when you set the 
     * RFMXSPECAN_ATTR_PHASENOISE_RANGE_DEFINITION attribute to RFMXSPECAN_VAL_PHASENOISE_RANGE_DEFINITION_AUTO. 
     * This value is expressed in Hz. */
    ViReal64 dStartFrequency;
    /* Specifies the stop frequency of the offset frequency range when you set the 
     * RFMXSPECAN_ATTR_PHASENOISE_RANGE_DEFINITION attribute to RFMXSPECAN_VAL_PHASENOISE_RANGE_DEFINITION_AUTO. 
     * This value is expressed in Hz.
     */
    ViReal64 dStopFrequency;
    /* Specifies the RBW as a percentage of the start frequencyof each sub-range when you set the 
     * RFMXSPECAN_ATTR_PHASENOISE_RANGE_DEFINITION attribute to RFMXSPECAN_VAL_PHASENOISE_RANGE_DEFINITION_AUTO. 
     * This value is expressed as a percentage.
     */
    ViReal64 dRBWPercentage;
}AutoRangeAttribute;

typedef struct{
    /* Specifies the start frequency for the specified subrange when you set the RFMXSPECAN_ATTR_PHASENOISE_RANGE_DEFINITION attribute to RFMXSPECAN_VAL_PHASENOISE_RANGE_DEFINITION_MANUAL. */
    ViReal64* pRangeStartFrequency;
    /* Specifies the stop frequency for the specified subrange when you set the RFMXSPECAN_ATTR_PHASENOISE_RANGE_DEFINITION attribute to RFMXSPECAN_VAL_PHASENOISE_RANGE_DEFINITION_MANUAL. 
     * This value is expressed in Hz.
     */
    ViReal64* pRangeStopFrequency;
    /* Specifies the RBW of the start offset of each sub-range. This value is expressed as a percentage. */
    ViReal64* pRangeRBWPercentage;
    /* Specifies the averaging count for the specified range. */
    ViInt32* pRangeAveragingCount;
    /* Specifies the number of elements in each array. */
    ViInt32 nNumberOfElements;
}ManualRangeArrayAttribute;

typedef struct{
    /* Specifies the smoothing type used to smoothen a log plot trace. 
     * RFMXSPECAN_VAL_PHASENOISE_SMOOTHING_TYPE_NONE (0)                Smoothing is disabled. 
     * RFMXSPECAN_VAL_PHASENOISE_SMOOTHING_TYPE_LINEAR (1)              Performs linear moving average filtering on the measured phase noise log plot trace. 
     * RFMXSPECAN_VAL_PHASENOISE_SMOOTHING_TYPE_LOGARITHMIC (2)         Performs logarithmic moving average filtering on the measured phase noise log plot trace. 
     * RFMXSPECAN_VAL_PHASENOISE_SMOOTHING_TYPE_MEDIAN (3)              Performs moving median filtering on the measured phase noise log plot trace.  
     */
    ViInt32 nType;
    /* Specifies the number of points to use in the moving average filter as a percentage of total number of points in the log plot trace. This value is expressed as a percentage. */
    ViReal64 dPercentage;
}PhaseNoiseSmoothingAttribute;

typedef struct{
    /* Specifies an array of offset frequencies at which the corresponding phase noise is measured using the smoothed log plot trace. This value is expressed in Hz. */
    ViReal64* pFrequencyList;
    /*  Specifies the size of the array. */
    ViInt32 nSize;
}PhaseNoiseFrequencyListAttribute;

typedef struct{
    /* Specifies whether to use the complete measurement range for computing integrated measurements, or to use the range that you specify. */
    ViInt32 nIntegratedNoiseRangeDefinition;
    /* Specifies an array of the start frequencies for integrated measurement. This value is expressed in Hz. */
    ViReal64* pIntegratedNoiseStartFrequency;
    /* Specifies an array of the stop offset frequencies for integrated measurement. This value is expressed in Hz. */
    ViReal64* pIntegratedNoiseStopFrequency;
    /* Specifies the size of the array. */
    ViInt32 nSize;
}PhaseNoiseIntegratedNoiseAttribute;

typedef struct{
    /* Specifies whether the spur removal is enabled or disabled.
     * RFMXSPECAN_VAL_PHASENOISE_SPUR_REMOVAL_ENABLED_FALSE (0)         Disables spur removal on the log plot trace.
     * RFMXSPECAN_VAL_PHASENOISE_SPUR_REMOVAL_ENABLED_TRUE (1)          Enables spur removal on the log plot trace.
     */
    ViInt32 nEnabled;
    /* Specifies the minimum amplitude variation required in a signal to be considered as a peak. 
     * The signal must rise and fall above the threshold level by at least the peak excursion value to be considered as an eligible peak. 
     * The threshold is a curve fit performed on the measured phase noise.
     */
    ViReal64 dPeakExcursion;
}PhaseNoiseSpurRemovalAttribute;

typedef struct{
    /* Specifies whether to enable or disable the phase noise cancellation.
     * RFMXSPECAN_VAL_PHASENOISE_CANCELLATION_ENABLED_FALSE (0)     Disables phase noise cancellation.
     * RFMXSPECAN_VAL_PHASENOISE_CANCELLATION_ENABLED_TRUE (1)      Enables phase noise cancellation. 
     *                                                              Specify the value to be used for phase noise cancellation in 
     *                                                              the RFMXSPECAN_ATTR_PHASENOISE_CANCELLATION_REFERENCE_PHASE_NOISE attribute.
     */
    ViInt32 nEnabled;
    /* Specifies the minimum delta between the reference and pre-cancellation traces that must exist before any cancellation is performed. 
     * The delta is evaluated on a bin per bin basis. This value is expressed in dB.
     */
    ViReal64 dThreshold;
    /* Specifies an array of frequency offsets where the reference phase noise has been measured. This value is expressed in Hz. */
    ViReal32* pFrequency;
    /* Specifies an array of the reference phase noise at the frequency offsets. This value is expressed in dBc/Hz. */
    ViReal32* pReferencePhaseNoise;
    /* Specifies the size of the array. */
    ViInt32 nSize;
}PhaseNoiseCancellationAttribute;

typedef struct{
    /*
     *  Specifies how the measurement computes offset subranges.
     *  RFMXSPECAN_VAL_PHASENOISE_RANGE_DEFINITION_MANUAL (0)                   Specify the offset sub-ranges used for the measurement. 
     *                                                                          Use the RFMXSPECAN_ATTR_PHASENOISE_RANGE_START_FREQUENCY attribute and 
     *                                                                          the RFMXSPECAN_ATTR_PHASENOISE_RANGE_STOP_FREQUENCY attribute to configure 
     *                                                                          single or multiple range start and range stop frequencies.
     * RFMXSPECAN_VAL_PHASENOISE_RANGE_DEFINITION_AUTO (1)                      Measurement computes offset sub-ranges by dividing the user configured offset 
     *                                                                          range into multiple decade sub-ranges. The range is specified by the RFMXSPECAN_ATTR_PHASENOISE_START_FREQUENCY 
     *                                                                          and the RFMXSPECAN_ATTR_PHASENOISE_STOP_FREQUENCY attributes.
     */
    ViInt32 nRangeDefinition;
    /*  Configures the offset range and the RBW percentage when you set the RFMXSpecAn_ATTR_PHASENOISE_RANGE_DEFINITION attribute 
     * to RFMXSPECAN_VAL_PHASENOISE_RANGE_DEFINITION_AUTO.
     */
    AutoRangeAttribute AutoRange;
    /* Configures the number of offset ranges when you set the RFMXSpecAn_ATTR_PHASENOISE_RANGE_DEFINITION attribute to Manual.
     * Specifies the number of manual ranges.
     */
    ViInt32 nNumberOfRanges;
    
    /* Configures an array of the offset range, RBW percentage and averaging count when you set 
     * the RFMXSpecAn_ATTR_PHASENOISE_RANGE_DEFINITION attribute to RFMXSPECAN_VAL_PHASENOISE_RANGE_DEFINITION_MANUAL.
     */
    ManualRangeArrayAttribute ManualRangeArray;
    /* Specifies the factor by which the averaging count for each sub-range to increase. */
    ViInt32 nAveragingMultiplier;
    /* Configures the smoothing type and smoothing percentage used to smoothen the measured log plot trace. */
    PhaseNoiseSmoothingAttribute Smoothing;
    /* Configures a list of frequencies at which the phase noise values are to be read using the smoothed log plot trace. */
    PhaseNoiseFrequencyListAttribute FrequencyList;
    /* Configures the integrated noise ranges. The smoothed log plot trace is used when computing integrated measurements. */
    PhaseNoiseIntegratedNoiseAttribute IntegratedNoise;
    /* Configures enabling or disabling of the spur removal and the peak excursion to use when spur removal is enabled. */
    PhaseNoiseSpurRemovalAttribute SpurRemoval;
    /* Configures the enabling or disabling of the phase noise cancellation, threshold cancellation, and the reference phase noise used for cancellation. */
    PhaseNoiseCancellationAttribute Cancellation;
}cfgPhaseNoiseAttribute,*pCfgPhaseNoiseAttribute;

typedef struct{
    ViReal64 dInit;
    ViReal64 dIncrement;
    ViReal32* pDataBuf;
    ViInt32 dwNumbersOfData;
}DataResultAttribute,*pDataResultAttribute;

typedef struct{
    ViReal64 dInitT0;
    ViReal64 dIncrement;
    ViReal32* pIDataBuf;
    ViReal32* pQDataBuf;
    ViInt32 dwNumbersOfData;
}IQSplitResultAttribute,*pIQSplitResultAttribute;

typedef struct{
    /* Returns the peak amplitude, of the averaged spectrum. When you set the RFMXSPECAN_ATTR_SPECTRUM_SPAN attribute to 0, this function returns the peak amplitude in the time domain power trace.*/
    ViReal64 dPeakAmplitude;
    /* Returns the frequency, in hertz (Hz), at the peak amplitude of the averaged spectrum. This parameter is not valid if you set the RFMXSPECAN_ATTR_SPECTRUM_SPAN attribute to 0.*/
    ViReal64 dPeakFrequency;
    /* Returns the frequency bin spacing, in hertz (Hz), of the spectrum acquired by the measurement. This parameter is not valid if you set the RFMXSPECAN_ATTR_SPECTRUM_SPAN attribute to 0.*/
    ViReal64 dFrequencyResolution;
    /* Fetches the spectrum used for the Spectrum measurement.*/
    DataResultAttribute Spectrum;
    /* Fetches the power trace for the Spectrum measurement.*/
    DataResultAttribute Power;
}SpectrumResultAttribute,*pSpectrumResultAttribute;

typedef struct{
    DataResultAttribute Spectrum;
    /* Returns the absolute power, in dBm, measured in the specified integration bandwidth.*/
    ViReal64 dAbsolutePower;
    /* Returns the power spectral density of the channel, in dBm/Hz.*/
    ViReal64 dPSD;
    /* Returns the carrier power, in dB, measured relative to the total carrier power.*/
    ViReal64 dRelativePower;
    /* Returns the total integrated power of all carriers, in dBm. */
    ViReal64 dTotalCarrierPower;
}CHPResultAttribute,*pCHPResultAttribute;

typedef struct{
    /* Returns the occupied bandwidth, in hertz (Hz).*/
    ViReal64 dOccupiedBandwidth;
    /* Returns the total integrated power of the averaged spectrum acquired by the OBW measurement when you 
     * set the RFMXSPECAN_ATTR_OBW_POWER_UNITS attribute to RFMXSPECAN_VAL_OBW_POWER_UNITS_DBM. 
     * This function returns the power spectral density when you 
     * set the RFMXSPECAN_ATTR_OBW_POWER_UNITS attribute to RFMXSPECAN_VAL_OBW_POWER_UNITS_DBM_PER_HZ.
     */
    ViReal64 dAveragePower;
    /* Returns the frequency bin spacing, in hertz (Hz), of the spectrum acquired by the measurement.*/
    ViReal64 dFrequencyResolution;
    /* Returns the start frequency, in Hz, of the OBW. 
     * The OBW is calculated using the following formula: OBW = stop frequency - start frequency.
     */
    ViReal64 dStartFrequency;
    /* Returns the stop frequency, in Hz, of the OBW.*/
    ViReal64 dStopFrequency;
    /* Fetches the spectrum trace used for the OBW measurement.*/
    DataResultAttribute Spectrum;
}OBWResultAttribute,*pOBWResultAttribute;

typedef struct{
    /* Returns an array of the orders of the intermods.*/
    ViInt32* pIntermodOrder;
    /* Returns an array of the peak power values measured around the lower intermod frequency when you set the 
     * RFMXSPECAN_ATTR_IM_LOCAL_PEAK_SEARCH_ENABLED attribute to RFMXSPECAN_VAL_IM_LOCAL_PEAK_SEARCH_ENABLED_TRUE. 
     * This value is expressed in dBm. When you set the RFMXSPECAN_ATTR_IM_LOCAL_PEAK_SEARCH_ENABLED attribute to 
     * RFMXSPECAN_VAL_IM_LOCAL_PEAK_SEARCH_ENABLED_FALSE, the measurement returns the power at the lower intermod frequency.
     */
    ViReal64* pLowerIntermodPower;
    /* Returns an array of the peak power values measured around the upper intermod frequency when you set the 
     * RFMXSPECAN_ATTR_IM_LOCAL_PEAK_SEARCH_ENABLED attribute to RFMXSPECAN_VAL_IM_LOCAL_PEAK_SEARCH_ENABLED_TRUE. 
     * This value is expressed in dBm. When you set the RFMXSPECAN_ATTR_IM_LOCAL_PEAK_SEARCH_ENABLED attribute to 
     * RFMXSPECAN_VAL_IM_LOCAL_PEAK_SEARCH_ENABLED_FALSE, the measurement returns the power at the upper intermod frequency.
     */
    ViReal64* pUpperIntermodPower;
    /* Returns the actual size of the array. If you set the arraySize parameter to 0, it returns the required array size.*/
    ViInt32 nActualArraySize;
}IntermodMeasurementArrayAttribute,*pIntermodMeasurementArrayAttribute;

typedef struct{
    /* Returns an array of the orders of the intermods. */
    ViInt32* pIntermodOrder;
    /* Returns an array of the worst case output intercept powers which are equal to the minimum of the values of the 
     * RFMXSPECAN_ATTR_IM_RESULTS_UPPER_OUTPUT_INTERCEPT_POWER and RFMXSPECAN_ATTR_IM_RESULTS_LOWER_OUTPUT_INTERCEPT_POWER results. 
     * This value is expressed in dBm.*/
    ViReal64* pWorstCaseOutputInterceptPower;
    /* Returns an array of the lower output intercept power values. This value is expressed in dBm.*/
    ViReal64* pLowerOutputInterceptPower;
    /* Returns an array of the upper output intercept power values. This value is expressed in dBm.*/
    ViReal64* pUpperOutputInterceptPower;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}InterceptPowerArrayAttribute,*pInterceptPowerArrayAttribute;



typedef struct{
    IntermodMeasurementArrayAttribute IntermodMeasurementArray;
    DataResultAttribute Spectrum;
    InterceptPowerArrayAttribute InterceptPowerArray;
    /* Returns the peak power measured around the lower tone frequency when you set the 
     * RFMXSPECAN_ATTR_IM_LOCAL_PEAK_SEARCH_ENABLED attribute to RFMXSPECAN_VAL_IM_LOCAL_PEAK_SEARCH_ENABLED_TRUE. 
     * This value is expressed in dBm. 
     * When you set the RFMXSPECAN_ATTR_IM_LOCAL_PEAK_SEARCH_ENABLED attribute to RFMXSPECAN_VAL_IM_LOCAL_PEAK_SEARCH_ENABLED_FALSE, 
     * the measurement returns the power at the lower tone frequency. 
     */
    ViReal64 dLowerTonePower;
    /* Returns the peak power measured around the upper tone frequency when you set the 
     * RFMXSPECAN_ATTR_IM_LOCAL_PEAK_SEARCH_ENABLED attribute to RFMXSPECAN_VAL_IM_LOCAL_PEAK_SEARCH_ENABLED_TRUE. 
     * This value is expressed in dBm. 
     * When you set the RFMXSPECAN_ATTR_IM_LOCAL_PEAK_SEARCH_ENABLED attribute to RFMXSPECAN_VAL_IM_LOCAL_PEAK_SEARCH_ENABLED_FALSE, 
     * the measurement returns the power at the upper tone frequency. 
     */
    ViReal64 dUpperTonePower;
}IMResultAttribute,*pIMResultAttribute;

typedef struct{
    ViReal64 dAbsolutePower;
    ViReal64 dTotalRelativePower;
    ViReal64 dCarrierOffset;
    ViReal64 dIntegrationBandwidth;
}ACPCarrierMeasurementAttritube,*pACPCarrierMeasurementAttritube;

typedef struct{
    ViReal64 dLowerRelativePower;
    ViReal64 dUpperRelativePower;
    ViReal64 dLowerAbsolutePower;
    ViReal64 dUpperAbsolutePower;
}ACPOffsetMeasurementAttritube,*pACPOffsetMeasurementAttritube;

typedef struct{
    ACPOffsetMeasurementAttritube* pDataBuf;
    ViInt32 nActualArraySize;
}ACPOffsetMeasurementArrayAttritube,*pACPOffsetMeasurementArrayAttritube;

typedef struct{
    /* Returns the total integrated power of all the active carriers measured.*/
    ViReal64 dTotalCarrierPower;
    /* Returns the frequency bin spacing, in Hz, of the spectrum acquired by the measurement.*/
    ViReal64 pFrequencyResolution;
    /* Returns the measured carrier power.*/
    ACPCarrierMeasurementAttritube* pCarrierMeasurement;
    /* Returns the absolute and relative powers measured in the offset channel.*/
    ACPOffsetMeasurementAttritube OffsetMeasurement;
    /* Returns the absolute and relative powers measured in the offset channel. */
    ACPOffsetMeasurementArrayAttritube OffsetMeasurementArray;
    /* Fetches the spectrum used for adjacent channel power (ACP) measurement.*/
    DataResultAttribute Spectrum;
    /* Fetches the relative powers trace for adjacent channel power (ACP) measurement.*/
    DataResultAttribute RelativePowersTrace;
    /* Fetches the absolute powers trace for the adjacent channel power (ACP) measurement.*/
    DataResultAttribute AbsolutePowersTrace;
}ACPResultAttribute,*pACPResultAttribute;

typedef struct{
    /* Returns the measured carrier power. This value is expressed in Hz. */
    ViReal64 dFrequency;
    /* Returns the measured carrier frequency. This value is expressed in dBm. */
    ViReal64 dPower;
}PhaseNoiseCarrierMeasurementResultAttribute;

typedef struct{
    /* Returns the phase noise corresponding to the value of the RFMXSPECAN_ATTR_PHASENOISE_SPOT_NOISE_FREQUENCY_LIST attribute, by using the smoothed log plot trace. */
    ViReal64* pSpotPhaseNoise;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0. */
    ViInt32 nActualArraySize;
}PhaseNoiseSpotNoiseResultAttribute;

typedef struct{
    /* Returns the integrated phase noise. This value is expressed in dBc. */
    ViReal64* pIntegratedPhaseNoise;
    /* Returns the residual PM in radians. */
    ViReal64* pResidualPMInRadian;
    /* Returns the residual PM. This value is expressed in degrees. */
    ViReal64* pResidualPMInDegree;
    /* Returns the residual FM. This value is expressed in Hz. */
    ViReal64* pResidualFM;
    /* Returns the jitter. This value is expressed in seconds. */
    ViReal64* pJitter;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0. */
    ViInt32 nActualArraySize;
}PhaseNoiseIntegratedNoiseResultAttribute;

typedef struct{
    /* Fetches the carrier measurement. */
    PhaseNoiseCarrierMeasurementResultAttribute CarrierMeasurement;
    /* Fetches the spot noise. */
    PhaseNoiseSpotNoiseResultAttribute SpotNoise;
    /* Fetches the integrated noise measurement. */
    PhaseNoiseIntegratedNoiseResultAttribute IntegratedNoise;
}PhaseNoiseResultAttribute,*pPhaseNoiseResultAttribute;

class DLLAPI CCRFmxSpecAnAttribute
{
public:
    CCRFmxSpecAnAttribute();
public:
    /* Specifies the carrier frequency, in Hz, of the RF signal that needs to be acquired. The signal analyzer tunes to this frequency.*/
    ViReal64 dCenterFrequency;
    /* Specifies the reference level which represents the maximum expected power of the RF input signal. 
     * This value is configured in dBm for RF devices and as Vpk-pk for baseband devices. 
     * The default of this property is hardware dependent.
     */
    ViReal64 dReferenceLevel;
    
    /*Specifies the measurement type*/
    SelectMeasurementTypeAttribute SelectMeasurement;
    /* Path Loss*/
    ViReal64 dwPathLoss[MAX_SITE];
    
    CfgCHPAttribute CHP;
    cfgSpectrumAttribute Spectrum;
    cfgOBWAttribute OBW;
    cfgIQAttribute IQ;
    cfgIMAttribute IM;
    cfgACPAttribute ACP;
    cfgPhaseNoiseAttribute PhaseNoise;
    /*Specifies the trigger type*/
    RfmxInstrTrigger trigger;   
};

typedef CCRFMultiSite<CCRFmxSpecAnAttribute> CCMultiSiteRFmxSpecAnAttribute;

#include <map>
#include "string"
using namespace std;

/*Output Data*/
typedef struct{
#ifdef USE_SPEC_SPLIT
    /* Returns the peak amplitude, of the averaged spectrum. When you set the RFMXSPECAN_ATTR_SPECTRUM_SPAN attribute to 0, this function returns the peak amplitude in the time domain power trace.*/
    ViReal64 dPeakAmplitude;
    /* Returns the frequency, in hertz (Hz), at the peak amplitude of the averaged spectrum. This parameter is not valid if you set the RFMXSPECAN_ATTR_SPECTRUM_SPAN attribute to 0.*/
    ViReal64 dPeakFrequency;
    /* Returns the frequency bin spacing, in hertz (Hz), of the spectrum acquired by the measurement. This parameter is not valid if you set the RFMXSPECAN_ATTR_SPECTRUM_SPAN attribute to 0.*/
    ViReal64 dFrequencyResolution;
    
    /* Returns the start frequency, in hertz (Hz). When you set the RFMXSPECAN_ATTR_SPECTRUM_SPAN attribute to 0, x0 returns the start time, in seconds.*/
    ViReal64 dInitiaFrequency;
    /* Returns the frequency bin spacing, in Hz. When you set the RFMXSPECAN_ATTR_SPECTRUM_SPAN attribute to 0, dx returns the sample duration, in seconds.*/
    ViReal64 dFrequencyIncrement;
    /* Returns the averaged power, measured at each frequency bin. 
     * When you set the RFMXSPECAN_ATTR_SPECTRUM_SPAN attribute to 0, the averaged power is measured at each sample instance in time. 
     * The units of power is as specified using the RFMXSPECAN_ATTR_SPECTRUM_POWER_UNITS attribute. 
     * Set the arraySize parameter to 0 to get the size of the y array. You can pass NULL for this parameter if you set the arraySize parameter to 0. 
     * If the y array is not large enough to hold all the samples, the function returns an error.
     */
    ViReal32* pSpectrumDataBuf;
    /* Returns the actual size of the output array parameters, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 dwNumbersOfSpectrum;
    
    /* Returns the start time, in seconds.*/
    ViReal64 dInitiaTime;
    /* Returns the sample duration, in seconds.*/
    ViReal64 dSampleDuration;
    /* Returns the measured average power, in dBm, at each time instance. Set the arraySize parameter to 0 to get the size of the y array. 
     * You can pass NULL for this parameter if you set the arraySize parameter to 0. 
     * If the y array is not large enough to hold all the samples, the function returns an error.
     */
    ViReal32* pPowerDataBuf;
    /* Returns the actual size of the output array parameters, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 dwNumbersOfPower;
    
    /* Returns the start time of the first sample. The timestamp corresponds to the difference, in seconds, between the first sample returned and the Reference Trigger location. */
    ViReal64 dStartTime;
    /* Returns the time interval between data points in the acquired signal. The I/Q data sample rate is the reciprocal of this value.*/
    ViReal64 dIntervalTime;
    /* Returns the complex-value time domain data array. 
     * The real and imaginary parts of this complex data array correspond to the in-phase (I) and quadrature-phase (Q) data, respectively. 
     * To calculate the instantaneous power of a sampled I/Q point, use the equation (I2 + Q2) / 2R, where R is the input impedance in ohms. For RFmx, R = 50 ohms. 
     */
    ComplexNumber* pIQData;
    /* Returns the actual size of the array, if you pass NULL to the data parameter and set the arraySize parameter to 0.*/
    ViInt32 dwNumbersOfIQData;
#else    
    SpectrumResultAttribute SpectrumResult;
    IQSplitResultAttribute IQResult;
#endif
    CHPResultAttribute CHPResult;
    /* Returns the occupied bandwidth (OBW) measurement.*/
    OBWResultAttribute OBWResult;
    IMResultAttribute IMResult;
    ACPResultAttribute ACPResult;
    PhaseNoiseResultAttribute PhaseNoiseResult;
}SpecAnResultAttribute,*pSpecAnResultAttribute;


class DLLAPI CCRfmxSpecAnResults :public CCResultsArray<SpecAnResultAttribute>
{
public:
    CCRfmxSpecAnResults();
    ~CCRfmxSpecAnResults();
   
    void RemoveAll();
};

#endif	/* CCRFMXSPECANTYPEDEF_H */

