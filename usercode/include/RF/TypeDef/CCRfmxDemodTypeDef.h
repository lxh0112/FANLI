/* 
 * File:   CCRfmxDemodTypeDef.h
 * Author: guiyuliang
 *
 * Created on 2020年10月27日, 上午9:11
 */

#pragma once

#ifndef CCRFMXDEMODTYPEDEF_H
#define	CCRFMXDEMODTYPEDEF_H

#include "CCResults.h"
#include "CCTesterDef.h"

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
    /* Path Loss*/
    ViReal64 dwPathLoss[MAX_SITE];
    /*Specifies the measurement type*/
    SelectMeasurementTypeAttribute SelectMeasurement;
    /*Specifies the trigger type*/
    RfmxInstrTrigger trigger;   
}RfmxDemodField,*pRfmxDemodField;

typedef struct{
    /* Specifies the analog modulation type of the signal that needs to be analyzed.
     * RFMXDEMOD_VAL_ADEMOD_MODULATION_TYPE_AM (0) The signal to be analyzed is amplitude modulated (AM).
     * RFMXDEMOD_VAL_ADEMOD_MODULATION_TYPE_FM (1) The signal to be analyzed is frequency modulated (FM). 
     * RFMXDEMOD_VAL_ADEMOD_MODULATION_TYPE_PM (2) The signal to be analyzed is phase modulated (PM). 
     */
    ViInt32 nModulationType;
    
    /* Specifies the shape of the digital RBW filter.
     * RFMXDEMOD_VAL_ADEMOD_RBW_FILTER_TYPE_NONE (0)            RBW filter is not applied on the acquired signal.
     * RFMXDEMOD_VAL_ADEMOD_RBW_FILTER_TYPE_GAUSSIAN (1)        RBW filter has a Gaussian response. 
     * RFMXDEMOD_VAL_ADEMOD_RBW_FILTER_TYPE_FLAT (2)            RBW filter has a Flat response. 
     * RFMXDEMOD_VAL_ADEMOD_RBW_FILTER_TYPE_SYNCH_TUNED_4 (3)   RBW filter has a response of a 4-pole synchronously tuned filter. 
     * RFMXDEMOD_VAL_ADEMOD_RBW_FILTER_TYPE_SYNCH_TUNED_5 (4)   RBW filter has a response of a 5-pole synchronously tuned filter. 
     * RFMXDEMOD_VAL_ADEMOD_RBW_FILTER_TYPE_RRC (5)             RRC filter with roll-off specified by the RFMXDEMOD_ATTR_ADEMOD_RBW_FILTER_ALPHA attribute is used as the RBW filter.
     */
    ViInt32 nRBWFilterType;
    
    /* Specifies the roll-off factor of the root-raised cosine (RRC) filter.*/
    ViReal64 dwRBWRRCAlpha;
    
    /* Specifies the signal acquisition time, in seconds, for the analog demodulation measurement.*/
    ViReal64 dwMeasurementInterval;
    
    /* Specifies whether the carrier of the AM signal is absent.
     * RFMXDEMOD_VAL_ADEMOD_AM_CARRIER_SUPPRESSED_FALSE (0)     The carrier of the AM signal is present.
     * RFMXDEMOD_VAL_ADEMOD_AM_CARRIER_SUPPRESSED_TRUE (1)      The carrier of the AM signal is absent.
     */
    ViInt32 nAMCarrierSuppressedEnabled;
    
    /* Specifies whether to correct the frequency error in the carrier when demodulating frequency-modulated or phase-modulated signals.
     * RFMXDEMOD_VAL_ADEMOD_CARRIER_FREQUENCY_CORRECTION_ENABLED_FALSE (0)      Does not correct the carrier frequency error. 
     * RFMXDEMOD_VAL_ADEMOD_CARRIER_FREQUENCY_CORRECTION_ENABLED_TRUE (1)       Corrects the carrier frequency error. 
     */
    ViInt32 nCarrierFrequencyCorrectionEnabled;
    
    /* Specifies whether to correct the phase error in the carrier when demodulating phase-modulated signals.
     * RFMXDEMOD_VAL_ADEMOD_CARRIER_PHASE_CORRECTION_ENABLED_FALSE (0)  Does not correct the carrier phase error.
     * RFMXDEMOD_VAL_ADEMOD_CARRIER_PHASE_CORRECTION_ENABLED_TRUE (1)   Corrects the carrier phase error.
     */
    ViInt32 nCarrierPhaseCorrectionEnabled;
    
    /* Specifies the time constant, in seconds, of the de-emphasis filter, which compensates for the pre-emphasis filter in the FM transmitter.*/
    ViReal64 dwDeEmphasis;
    
    /* Specifies the audio filter to be applied on the analog demodulated signal.
     * RFMXDEMOD_VAL_ADEMOD_AUDIO_FILTER_TYPE_NONE (0)          Does not use any audio filter.
     * RFMXDEMOD_VAL_ADEMOD_AUDIO_FILTER_TYPE_CUSTOM (1)        Uses the filter specified by the RFMXDEMOD_ATTR_ADEMOD_AUDIO_FILTER_LOWER_CUTOFF_FREQUENCY attribute and the RFMXDEMOD_ATTR_ADEMOD_AUDIO_FILTER_UPPER_CUTOFF_FREQUENCY attribute.
     * RFMXDEMOD_VAL_ADEMOD_AUDIO_FILTER_TYPE_A_WEIGHT (2)      Uses an A-weighted filter.
     * RFMXDEMOD_VAL_ADEMOD_AUDIO_FILTER_TYPE_B_WEIGHT (3)      Uses a B-weighted filter.
     * RFMXDEMOD_VAL_ADEMOD_AUDIO_FILTER_TYPE_C_WEIGHT (4)      Uses a C-weighted filter.
     * RFMXDEMOD_VAL_ADEMOD_AUDIO_FILTER_TYPE_CCITT (5)         Uses the filter specified by CCITT.
     * RFMXDEMOD_VAL_ADEMOD_AUDIO_FILTER_TYPE_ITU_R_468_4 (6)   Uses the filter specified by ITU-R 468-4.
     */
    ViInt32 nAudioFilterType;
    
    /* Specifies the lower cutoff frequency, in Hz, of the custom audio filter.*/
    ViReal64 dwAudioFilterLowerCutoffFrequency;
    
    /* Specifies the upper cutoff frequency, in Hz, of the custom audio filter.*/
    ViReal64 dwAudioFilterUpperCutoffFrequency;
    
    /* Enables averaging for analog demodulation measurements.
     * RFMXDEMOD_VAL_ADEMOD_AVERAGING_ENABLED_FALSE (0)         The measurement is performed on a single acquisition.
     * RFMXDEMOD_VAL_ADEMOD_AVERAGING_ENABLED_TRUE (1)          The measurement uses the value of the averagingCount parameter for the number of acquisitions over which the measurement is averaged. The traces are not averaged.
     */
    ViInt32 nAveragingEnabled;
    
    /* Specifies the number of acquisitions used for averaging when you set the averagingEnabled parameter to RFMXDEMOD_VAL_ADEMOD_AVERAGING_ENABLED_TRUE.*/
    ViInt32 nAveragingCount;
    
    /* Specifies the averaging type for the measurement.
     * RFMXDEMOD_VAL_ADEMOD_AVERAGING_TYPE_LINEAR (0)   The averaged result is the mean value measured across multiple acquisitions.
     * RFMXDEMOD_VAL_ADEMOD_AVERAGING_TYPE_MAXIMUM (1)  The averaged result is the maximum value measured across multiple acquisitions.
     * RFMXDEMOD_VAL_ADEMOD_AVERAGING_TYPE_MINIMUM (2)  The averaged result is the minimum value measured across multiple acquisitions.
     */
    ViInt32 nAveragingType;
}cfgADemodField,*pCfgADemodField;


typedef struct{
    /* Specifies the digital modulation type of the signal that needs to be analyzed.
     * RFMXDEMOD_VAL_DDEMOD_MODULATION_TYPE_ASK (0)     The modulation type is amplitude-shift keying (ASK). 
     * RFMXDEMOD_VAL_DDEMOD_MODULATION_TYPE_FSK (1)     The modulation type is frequency-shift keying (FSK). 
     * RFMXDEMOD_VAL_DDEMOD_MODULATION_TYPE_PSK (2)     The modulation type is phase-shift keying (PSK). 
     * RFMXDEMOD_VAL_DDEMOD_MODULATION_TYPE_QAM (3)     The modulation type is quadrature-amplitude modulation (QAM). 
     * RFMXDEMOD_VAL_DDEMOD_MODULATION_TYPE_MSK (4)     The modulation type is minimum shift keying (MSK). 
     */
    ViInt32 nModulationType;
    
    /* Specifies the M-ary number, which is the number of distinct states that represent symbols in the complex baseband modulated waveform.  
     * Note  Refer to the following recommended values of m based on modulation type: 
     * ASK: 2, 4, 8 
     * FSK , PSK: 2, 4, 8, 16 
     * QAM: 16, 32, 64, 128, 256, 512, 1028, 2048, 4096. 
     * RFMXDEMOD_VAL_DDEMOD_M_2 (2)             The M-ary number is 2. 
     * RFMXDEMOD_VAL_DDEMOD_M_4 (4)             The M-ary number is 4. 
     * RFMXDEMOD_VAL_DDEMOD_M_8 (8)             The M-ary number is 8. 
     * RFMXDEMOD_VAL_DDEMOD_M_16 (16)           The M-ary number is 16. 
     * RFMXDEMOD_VAL_DDEMOD_M_32 (32)           The M-ary number is 32. 
     * RFMXDEMOD_VAL_DDEMOD_M_64 (64)           The M-ary number is 64. 
     * RFMXDEMOD_VAL_DDEMOD_M_128 (128)         The M-ary number is 128. 
     * RFMXDEMOD_VAL_DDEMOD_M_256 (256)         The M-ary number is 256. 
     * RFMXDEMOD_VAL_DDEMOD_M_512 (512)         The M-ary number is 512. 
     * RFMXDEMOD_VAL_DDEMOD_M_1024 (1024)       The M-ary number is 1,024. 
     * RFMXDEMOD_VAL_DDEMOD_M_2048 (2048)       The M-ary number is 2,048.
     * RFMXDEMOD_VAL_DDEMOD_M_4096 (4096)       The M-ary number is 4,096.
     */
    ViInt32 nMAry;
    /* Specifies whether the symbols are differentially encoded. This attribute is applicable only to PSK and MSK modulation types.
     * RFMXDEMOD_VAL_DDEMOD_DIFFERENTIAL_ENABLED_FALSE (0)      The symbols are directly mapped onto the symbol map. 
     * RFMXDEMOD_VAL_DDEMOD_DIFFERENTIAL_ENABLED_TRUE (1)       In case of PSK modulation, the transition between two consecutive symbols is mapped onto the symbol map. 
     * In case of MSK modulation, the consecutive bits are XORed.
     */
    ViInt32 nDifferentialEnabled;
}DDemodModulationType,*pDDemodModulationType;

typedef struct{
    /* Specifies the expected FSK frequency deviation, in Hz. */
    ViReal64 dwFSKDeviation;
    /* Specifies whether the FSK deviation that you specify is used to compensate for gain errors and to compute the FSK error.
     * RFMXDEMOD_VAL_DDEMOD_FSK_REFERENCE_COMPENSATION_ENABLED_FALSE (0) Does not compensate for gain errors. 
     * RFMXDEMOD_VAL_DDEMOD_FSK_REFERENCE_COMPENSATION_ENABLED_TRUE (1) Compensates for gain errors. 
     */
    ViInt32 nFSKRefCompEnabled;
}DDemodFSKDeviation,*pDDemodFSKDeviation;

typedef struct{
    /* Specifies whether the measurement uses the default symbol map or the map that you configure using this function.
     * RFMXDEMOD_VAL_DDEMOD_SYMBOL_MAP_TYPE_AUTO (0)    Uses a default symbol map. 
     * RFMXDEMOD_VAL_DDEMOD_SYMBOL_MAP_TYPE_CUSTOM (1)  Uses the map that you specify.
     */
    ViInt32 nSymbolMapType;
    /* Specifies the custom symbol map.*/
    ComplexNumber* pSymbolMap;
    /* Specifies the size of the array.*/
    ViInt32 nArraySize;
}DDemodSymbolMap,*pDDemodSymbolMap;


typedef struct{
    /* Specifies the pulse-shaping filter used to transmit the signal and determines the measurement filter to be used for analysis when the RFMXDEMOD_ATTR_DDEMOD_MEASUREMENT_FILTER_TYPE attribute is set to RFMXDEMOD_VAL_DDEMOD_MEASUREMENT_FILTER_TYPE_AUTO.
     * RFMXDEMOD_VAL_DDEMOD_PULSE_SHAPING_FILTER_TYPE_RECTANGULAR (0)           The transmitted waveform is filtered using a rectangular filter. 
     * RFMXDEMOD_VAL_DDEMOD_PULSE_SHAPING_FILTER_TYPE_RAISED_COSINE (1)         The transmitted waveform is filtered using a raised cosine filter. Specify the filter Alpha in the RFMXDEMOD_ATTR_DDEMOD_PULSE_SHAPING_FILTER_PARAMETER attribute. 
     * RFMXDEMOD_VAL_DDEMOD_PULSE_SHAPING_FILTER_TYPE_ROOT_RAISED_COSINE (2)    The transmitted waveform is filtered using a root raised cosine filter. Specify the filter Alpha in the RFMXDEMOD_ATTR_DDEMOD_PULSE_SHAPING_FILTER_PARAMETER attribute. 
     * RFMXDEMOD_VAL_DDEMOD_PULSE_SHAPING_FILTER_TYPE_GAUSSIAN (3)              The transmitted waveform is filtered using a Gaussian filter. Specify the filter bandwidth * sample duration in the RFMXDEMOD_ATTR_DDEMOD_PULSE_SHAPING_FILTER_PARAMETER attribute. This filter is applicable only to FSK and MSK modulation types. 
     * RFMXDEMOD_VAL_DDEMOD_PULSE_SHAPING_FILTER_TYPE_CUSTOM (4)                The transmitted waveform is filtered using the coefficients that you specify in the RFmxDemod_DDemodCfgPulseShapingFilterCustomCoefficients function. 
     * RFMXDEMOD_VAL_DDEMOD_PULSE_SHAPING_FILTER_TYPE_HALF_SINE (5)             The transmitted waveform is filtered using a half sine filter. 
     */
    ViInt32 nPulseShapingFilterType;
    /* Specifies the roll-off factor for the raised cosine and root-raised cosine filters that are used for the pulse-shaping filter and measurement filter respectively. 
     * When the pulseShapingFilterType parameter is set to RFMXDEMOD_VAL_DDEMOD_PULSE_SHAPING_FILTER_TYPE_GAUSSIAN, 
     * the pulseShapingFilterParameter parameter specifies bandwidth * sample duration (BT).*/
    ViReal64 dwPulseShapingFilterParameter;
    /* Always pass 0 to this parameter. Any other values are ignored.*/
    ViReal64 dwX0;
    /* Specifies the spacing between the coefficients as a fraction of the symbol spacing. For example, if four coefficients correspond to one symbol, the spacing is 1/4.*/
    ViReal64 dwDx;
    /* Specifies the filter coefficients used as the pulse-shaping filter on the transmitter.*/
    ViReal32* pFilterBuf;
    /* Specifies the size of the array.*/
    ViReal32 nArraySize;
}DDemodPulseShapingFilter,*pDDemodPulseShapingFilter;

typedef struct{
    /* Always pass 0 to this parameter. Any other values are ignored.*/
    ViReal64 dwX0;
    /* Specifies the spacing between the coefficients as a fraction of the symbol spacing. For example, if four coefficients correspond to one symbol, the spacing is 1/4.*/
    ViReal64 dwDx;
    /* Specifies the filter coefficients used as the pulse-shaping filter on the transmitter.*/
    ViReal32* pPulseShapingFilterCustomCoefficients;
    /* Specifies the size of the array.*/
    ViInt32 nArraySize;
}DDemodPulseShapingFilterCustomCoefficients,*pDDemodPulseShapingFilterCustomCoefficients;

typedef struct{
    /* Specifies whether the measurement needs to compute the measurement filter based on the pulse-shaping filter type or uses the custom measurement filter coefficients.
     * RFMXDEMOD_VAL_DDEMOD_MEASUREMENT_FILTER_TYPE_AUTO (0)    The signal analyzer computes the measurement filter coefficients based on the pulse-shaping filter information that you specify in the pulseShapingFilterType parameter of the RFmxDemod_DDemodCfgPulseShapingFilter function. If the pulseShapingFilterType parameter is set to RFMXDEMOD_VAL_DDEMOD_PULSE_SHAPING_FILTER_TYPE_CUSTOM, the signal analyzer enables equalization. 
     * RFMXDEMOD_VAL_DDEMOD_MEASUREMENT_FILTER_TYPE_CUSTOM (1)  The signal analyzer uses the coefficients specified by RFmxDemod_DDemodCfgMeasurementFilterCustomCoefficients function. 
     */
    ViInt32 nMeasurementFilterType;
    /* Always pass 0 to this parameter. Any other values are ignored.*/
    ViReal64 dwX0;
    /* Specifies the spacing between the coefficients as a fraction of the symbol spacing. For example, if four coefficients correspond to one symbol, the spacing is 1/4.*/
    ViReal64 dwDx;
    /* Specifies the filter coefficients to be used by the demodulator.*/
    ViReal32* pMeasurementFilterCustomCoefficients;
    /* Specifies the size of the array.*/
    ViInt32 nArraySize;
}DDemodMeasurementFilter,*pDDemodMeasurementFilter;

typedef struct{
    /* Specifies whether the measurement needs to perform equalization.
     * RFMXDEMOD_VAL_DDEMOD_EQUALIZER_MODE_OFF (0)      Equalization is not performed. 
     * RFMXDEMOD_VAL_DDEMOD_EQUALIZER_MODE_TRAIN (1)    The adaptive feedforward equalizer is turned ON to compensate for the effect of the channel. You can set the initial coefficients to be used by the equalizer. If you do not specify the initial coefficients, an impulse is used. 
     * RFMXDEMOD_VAL_DDEMOD_EQUALIZER_MODE_HOLD (2)     The filter that you specify using the initial coefficients is used as the channel filter and is applied before demodulating the acquired signal. 
     */
    ViInt32 nEqualizerMode;
    /* Specifies the length of the equalization filter to be computed. The length is specified in terms of symbols. This parameter is ignored when the equalizer initial coefficients are specified.*/
    ViInt32 nEqualizerFilterLength;
    /* Always pass 0 to this parameter. Any other values are ignored.*/
    ViReal64 dwX0;
    /* Specifies the spacing between the coefficients as a fraction of the symbol spacing. For example, if four coefficients correspond to one symbol, the spacing is 1/4.*/
    ViReal64 dwDx;
    /* Specifies the initial coefficients to be used by the equalizer.*/
    ComplexNumber* pEqualizerInitialCoefficients;
    /* Specifies the number of iterations during which the equalizer adapts its coefficients in the training stage.*/
    ViInt32 nEqualizerTrainingCount;
    /* Specifies the incremental step used to adapt the equalizer to the channel, during the training stage.*/
    ViReal64 dwEqualizerConvergenceFactor;
    /* Specifies the size of the array.*/
    ViInt32 nArraySize;
}DDemodEqualizer,*pDDemodEqualizer;

typedef struct{
    /* Always pass 0 to this parameter. Any other values are ignored.*/
    ViReal64 dwX0;
    /* Specifies the spacing between the coefficients as a fraction of the symbol spacing. For example, if four coefficients correspond to one symbol, the spacing is 1/4.*/
    ViReal64 dwDx;
    /* Specifies the initial coefficients to be used by the equalizer.*/
    ComplexNumber* pInitialData;
    /* Specifies the size of the array.*/
    ViInt32 nArraySize;
}DDemodEqualizerCoefficients,*pDDemodEqualizerCoefficients;

typedef struct{
    /* Specifies whether the demodulator needs to search and synchronize the signal to a known reference sequence. The reference sequence is the symbol representation of a defined set of bits known to be present in the transmitted signal. If the synchronization is found in the demodulated signal, the measurement is performed from this point onward. If the synchronization is not found, the entire signal is used for the measurement.
     * RFMXDEMOD_VAL_DDEMOD_SYNCHRONIZATION_ENABLED_FALSE (0) Does not search and synchronize the signal. 
     * RFMXDEMOD_VAL_DDEMOD_SYNCHRONIZATION_ENABLED_TRUE (1) Searches and synchronizes the signal. 
     */
    ViInt32 nSynchronizationEnabled;
    /* Specifies the synchronization bits used to create the reference sequence that needs to be searched in the demodulated signal.*/
    ViInt8* pSyncBits;
    /* Specifies the offset, which is the location from which the signal is considered for further measurements.*/
    ViInt32 nMeasurementOffset;
    /* Specifies the size of the array.*/
    ViInt32 nArraySize;
}DDemodSynchronization,*pDDemodSynchronization;

typedef struct{
    /* Enables averaging for digital demodulation measurements.
     * RFMXDEMOD_VAL_DDEMOD_AVERAGING_ENABLED_FALSE (0) The measurement is performed on a single acquisition.
     * RFMXDEMOD_VAL_DDEMOD_AVERAGING_ENABLED_TRUE (1) The measurement uses the value of the averagingCount parameter for the number of acquisitions over which the measurement is averaged. The traces are not averaged.
     */
    ViInt32 nAveragingEnabled;
    /* Specifies the number of acquisitions used for averaging when you set the averagingEnabled parameter to RFMXDEMOD_VAL_DDEMOD_AVERAGING_ENABLED_TRUE.*/
    ViInt32 nAveragingCount;
}DDemodAveraging,*pDDemodAveraging;

typedef struct{
    /* Specifies the number of symbols from the start of the burst trigger that is excluded from the measurement.*/
    ViInt32 nStartVal;
    /* Specifies the number of symbols that is excluded from the measurement before the falling edge of the burst.*/
    ViInt32 nEndVal;
}DDemodExclusionSymbols,*pDDemodExclusionSymbols;

typedef struct{
    /* Configures the modulation type of the signal that needs to be analyzed.*/
    DDemodModulationType ModulationType;
    /* Specifies the PSK format.
     * RFMXDEMOD_VAL_DDEMOD_PSK_FORMAT_NORMAL (0)       Sets the modulation type to normal PSK. 
     * RFMXDEMOD_VAL_DDEMOD_PSK_FORMAT_OFFSET_QPSK (1)  Sets the modulation type to offset quadrature PSK (OQPSK). The ideal symbol timing of Q is offset by half of a symbol period from the ideal symbol timing of I. 
     * RFMXDEMOD_VAL_DDEMOD_PSK_FORMAT_PI_BY_4_QPSK (2) Sets the modulation type to pi/4 QPSK. In this modulation, each QPSK symbol is rotated by pi/4. 
     * RFMXDEMOD_VAL_DDEMOD_PSK_FORMAT_PI_BY_8_8PSK (3) Sets the modulation type to pi/8 8-PSK. In this modulation, each 8-PSK symbol is rotated by pi/8. 
     */
    ViInt32 nPSKFormat;
    /* Specifies the symbol rate, in Hz. */
    ViReal64 dwSymbolRate;
    /* Configures the expected FSK deviation.*/
    DDemodFSKDeviation FSKDeviation;
    /* Configures the symbol map that you use during measurements.*/
    DDemodSymbolMap SymbolMap;
    /* Specifies whether the signal is either a bursted signal or a continuous signal. 
     * RFMXDEMOD_VAL_DDEMOD_SIGNAL_STRUCTURE_BURSTED (0)        The signal is a bursty signal. 
     * RFMXDEMOD_VAL_DDEMOD_SIGNAL_STRUCTURE_CONTINUOUS (1)     The signal is a continuous signal.
     */
    ViInt32 nSignalStructure;
    /* Specifies the number of symbols to be analyzed. The measurement acquires additional symbols to account for filter delays.*/
    ViInt32 nNumberOfSymbols;
    /* Specifies the samples per symbol (SPS) used to acquire the signal for the measurement.
     * RFMXDEMOD_VAL_DDEMOD_SAMPLES_PER_SYMBOL_AUTO (-1) The measurement uses appropriate SPS based on modulation type and pulse-shaping filter.
     * SPS=8, for FSK.
     * SPS=4, for ASK, PSK, QAM, MSK when pulse shape filter is not rectangular.
     * SPS=8, for ASK, PSK, QAM, MSK when pulse shape filter is rectangular. 
     * RFMXDEMOD_VAL_DDEMOD_SAMPLES_PER_SYMBOL_4 (4)    The SPS value is 4. 
     * RFMXDEMOD_VAL_DDEMOD_SAMPLES_PER_SYMBOL_8 (8)    The SPS value is 8. 
     * RFMXDEMOD_VAL_DDEMOD_SAMPLES_PER_SYMBOL_16 (16)  The SPS value is 16. 
     */
    ViInt32 nSamplesPerSymbol;
    /* Configures the pulse-shaping filter.*/
    DDemodPulseShapingFilter PulseShapingFilter;
    /* Configures the pulse-shaping filter coefficients.*/
    DDemodPulseShapingFilterCustomCoefficients PulseShapingFilterCustomCoefficients;
    /* Configures the measurement filter.*/
    DDemodMeasurementFilter MeasurementFilter;
    /* Configures the equalizer.*/
    DDemodEqualizer Equalizer;
    /* Configures the equalizer coefficients.*/
    DDemodEqualizerCoefficients EqualizerCoefficients;
    /* Specifies the reference used to normalize the EVM.
     * RFMXDEMOD_VAL_DDEMOD_EVM_NORMALIZATION_REFERENCE_PEAK (0)        The EVM is normalized to the peak magnitude of the reference symbols. 
     * RFMXDEMOD_VAL_DDEMOD_EVM_NORMALIZATION_REFERENCE_RMS (1)         The EVM is normalized to the RMS magnitude of the reference symbols. This value is applicable only to modulation types, such as quadrature-amplitude modulation (QAM), in which the symbols in the map do not have a constant amplitude. 
     */
    ViInt32 nEVMNormRef;
    /* Configures bit pattern synchronization.*/
    DDemodSynchronization Synchronization;
    /* Specifies whether to swap the acquired I and Q samples for demodulation.
     * RFMXDEMOD_VAL_DDEMOD_SPECTRUM_INVERTED_FALSE (0) The acquired I and Q samples are used for demodulation as is. 
     * RFMXDEMOD_VAL_DDEMOD_SPECTRUM_INVERTED_TRUE (1) The acquired I and Q samples are swapped before using the signal for demodulation. 
     */
    ViInt32 nSpectrumInverted;
    /* Configures averaging for digital demodulation measurements.*/
    DDemodAveraging Averaging;
    /* */
    DDemodExclusionSymbols ExclusionSymbols;
}cfgDDemodField,*pCfgDDemodField;

/***************************Specifies Fetch Attributes************************************************************/
typedef struct{
    /* Returns the mean of the measured carrier frequency offset, in Hz.*/
    ViReal64 dwMeanFrequencyOffset;
    /* Returns the mean of the measured carrier frequency drift, in Hz.*/
    ViReal64 dwMeanFrequencyDrift;
    /* Returns the mean of the measured phase offset, in degrees, from the transmitted carrier phase.*/
    ViReal64 dwMeanPhaseError;
}D_CarrierMeasurementAttribute, *pD_CarrierMeasurementAttribute;

typedef struct{
    /* Returns the mean of the RMS EVM, as a percentage, measured per acquisition.*/
    ViReal64 dwMeanRMSEVM;
    /* Returns the maximum of the RMS EVM, as a percentage, measured per acquisition.*/
    ViReal64 dwMaximumRMSEVM;
    /* Returns the modulation error ratio, in dB.*/
    ViReal64 dwMeanModulationErrorRatio;
    /* Returns the maximum of the peak EVM measured per acquisition.*/
    ViReal64 dwMaximumPeakEVM;
    /* Returns the mean of the peak EVM measured per acquisition.*/
    ViReal64 dwMeanPeakEVM;
}D_EVMAttribute, *pD_EVMAttribute;

typedef struct{
    /* Returns the mean of the RMS EVM, measured per acquisition, after removing the offset between the I and Q channels of OQPSK demodulated signal.*/
    ViReal64 dwMeanRMSOffsetEVM;
    /* Returns the maximum of the RMS EVM, measured per acquisition, after removing the offset between the I and Q channels of OQPSK demodulated signal.*/
    ViReal64 dwMaximumRMSOffsetEVM;
    /* Returns the maximum of the peak EVM, measured per acquisition, after removing the offset between the I and Q channels of OQPSK demodulated signal.*/
    ViReal64 dwMaximumPeakOffsetEVM;
    /*  Returns the mean of the peak EVM, measured per acquisition, after removing the offset between the I and Q channels of OQPSK demodulated signal.*/
    ViReal64 dwMeanPeakOffsetEVM;
}D_OffsetEVMAttribute, *pD_OffsetEVMAttribute;

typedef struct{
    /* Returns the mean of the magnitude error measured per acquisition.*/
    ViReal64 dwMeanMagnitudeError;
    /* Returns the maximum of the magnitude error measured per acquisition.*/
    ViReal64 dwMaximumMagnitudeError;
}D_MagnitudeErrorAttribute, *pD_MagnitudeErrorAttribute;

typedef struct{
    /* Returns the mean of the phase error.*/
    ViReal64 dwMeanPhaseError;
    /* Returns the maximum of the phase error.*/
    ViReal64 dwMaximumPhaseError;
}D_PhaseErrorAttribute, *pD_PhaseErrorAttribute;

typedef struct{
    /* Returns the measured FSK deviation, in Hz.*/
    ViReal64 dwMeanFSKDeviation;
    /* Returns the mean of the RMS frequency error, in Hz, of the FSK symbols measured per acquisition.*/
    ViReal64 dwMeanRMSFSKError;
    /* Returns the maximum of peak frequency error, in Hz, of the FSK symbols measured per acquisition.*/
    ViReal64 dwMaximumPeakFSKError;
}D_FSKResultsAttribute, *pD_FSKResultsAttribute;

typedef struct{
    /* Returns RFMXDEMOD_VAL_TRUE if the synchronization bits were found in the demodulated signal.*/
    ViInt32 nSyncFound;
}D_SyncFoundAttribute, *pD_SyncFoundAttribute;

typedef struct{
    /* Returns the measured ratio of I gain to Q gain, in dB.*/
    ViReal64 dwMeanIQGainImbalance;
    /* Returns a measure of I and Q components in the signal that are not perfectly orthogonal.*/
    ViReal64 dwMeanQuadratureSkew;
    /* Returns the offset, in dB, from the ideal location of the constellation origin.*/
    ViReal64 dwMeanIQOriginOffset;
}D_IQImpairmentsAttribute, *pD_IQImpairmentsAttribute;

typedef struct{
    /* Returns the mean amplitude droop per symbol.*/
    ViReal64 dwMeanAmplitudeDroop;
}D_MeanAmplitudeDroopAttribute, *pD_MeanAmplitudeDroopAttribute;

typedef struct{
    /* Returns the offset, in dB, from the ideal location of the constellation origin.*/
    ViReal32 dwMeanIQOriginOffset;
}D_MeanIQOriginOffsetAttribute, *pD_MeanIQOriginOffsetAttribute;

typedef struct{
    /* Returns a measure of I and Q components in the signal that are not perfectly orthogonal. 
     * Quadrature error can be either positive or negative, with the sign indicating the orientation of the error.
     */
    ViReal32 dwMeanQuadratureSkew;
}D_MeanQuadratureSkewAttribute, *pD_MeanQuadratureSkewAttribute;

typedef struct{
    /* Returns the correlation of the measurement waveform and the reference waveform.*/
    ViReal64 dwMeanAmplitudeDroop;
}D_MeanRhoFactorAttribute, *pD_MeanRhoFactorAttribute;

typedef struct{
    /* Returns the start symbol index.*/
    ViReal64 dX0;
    /* Returns the spacing between symbols normalized to symbol rate.*/
    ViReal64 dDX;
    /* Returns the offset EVM per symbol. To get the size of y array, set arraySize parameter to 0. 
     * You can pass NULL for this parameter if the arraySize is set to 0. 
     * If the y array is not large enough to hold all the samples, the function returns an error.
     */
    ViReal32 *pEVM;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}D_EVMTraceAttribute, *pD_EVMTraceAttribute;

typedef struct{
    /* Returns the start symbol index.*/
    ViReal64 dX0;
    /* Returns the spacing between symbols normalized to symbol rate.*/
    ViReal64 dDX;
    /* Returns the offset EVM per symbol. To get the size of y array, set arraySize parameter to 0. 
     * You can pass NULL for this parameter if the arraySize is set to 0. 
     * If the y array is not large enough to hold all the samples, the function returns an error.
     */
    ViReal32 *pOffsetEvm;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}D_OffsetEVMTraceAttribute, *pD_OffsetEVMTraceAttribute;

typedef struct{
    /* Returns the start symbol index.*/
    ViReal64 dX0;
    /* Returns the spacing between symbols normalized to symbol rate.*/
    ViReal64 dDX;
    /* Returns the magnitude error per symbol. 
     * To get the size of y array, set arraySize parameter to 0. 
     * You can pass NULL for this parameter if the arraySize is set to 0. 
     * If the y array is not large enough to hold all the samples, the function returns an error.
     */
    ViReal32 *pMagnitideError;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}D_MagnitudeErrorTraceAttribute, *pD_MagnitudeErrorTraceAttribute;

typedef struct{
    /* Returns the start symbol index.*/
    ViReal64 dX0;
    /* Returns the spacing between symbols normalized to symbol rate.*/
    ViReal64 dDX;
    /* Returns the phase error per symbol. To get the size of y array, set arraySize parameter to 0. 
     * You can pass NULL for this parameter if the arraySize is set to 0. 
     * If the y array is not large enough to hold all the samples, the function returns an error.
     */
    ViReal32 *pPhaseError;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}D_PhaseErrorTraceAttribute, *pD_PhaseErrorTraceAttribute;

typedef struct{
    /* Returns the start symbol index.*/
    ViReal64 dX0;
    /* Returns the spacing between symbols normalized to symbol rate.*/
    ViReal64 dDX;
    /* Returns the FSK deviation error per symbol. To get the size of y array, set arraySize parameter to 0. 
     * You can pass NULL for this parameter if the arraySize is set to 0. 
     * If the y array is not large enough to hold all the samples, the function returns an error.
     */
    ViReal32* pFSKError;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}D_FSKDeviationTraceAttribute, *pD_FSKDeviationTraceAttribute;

typedef struct{
    /* Returns the constellation trace. To get the size of constellationTrace array, set arraySize parameter to 0. 
     * You can pass NULL for this parameter if the arraySize is set to 0. 
     * If the constellationTrace array is not large enough to hold all the samples, the function returns an error.
     */
    ComplexNumber* pConstellationTrace;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}D_ConstellationTraceAttribute, *pD_ConstellationTraceAttribute;

typedef struct{
    /* Returns the real part of constellation trace. 
     * To get the size of constellationTrace array, set arraySize parameter to 0. 
     * You can pass NULL for this parameter if the arraySize is set to 0. 
     * If the constellationTrace array is not large enough to hold all the samples, the function returns an error.
     */
    ViReal32* pIData;
    /* Returns the imaginary part of constellation trace. 
     * To get the size of constellationTrace array, set arraySize parameter to 0. 
     * You can pass NULL for this parameter if the arraySize is set to 0. 
     * If the constellationTrace array is not large enough to hold all the samples, the function returns an error.
     */
    ViReal32* pQData;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}D_ConstellationTraceSplitAttribute, *pD_ConstellationTraceSplitAttribute;

typedef struct{
    /* Returns the constellation trace. 
     * To get the size of constellationTrace array, set arraySize parameter to 0. 
     * You can pass NULL for this parameter if the arraySize is set to 0. 
     * If the constellationTrace array is not large enough to hold all the samples, the function returns an error.
     */
    ComplexNumber* pConstellationTrace;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}D_OffsetConstellationTraceAttribute, *pD_OffsetConstellationTraceAttribute;

typedef struct{
    /* Returns the real part of constellation trace. 
     * To get the size of constellationTrace array, set arraySize parameter to 0. 
     * You can pass NULL for this parameter if the arraySize is set to 0. 
     * If the constellationTrace array is not large enough to hold all the samples, the function returns an error.
     */
    ViReal32* pIData;
    /* Returns the imaginary part of constellation trace. 
     * To get the size of constellationTrace array, set arraySize parameter to 0. 
     * You can pass NULL for this parameter if the arraySize is set to 0. 
     * If the constellationTrace array is not large enough to hold all the samples, the function returns an error.*/
    ViReal32* pQData;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}D_OffsetConstellationTraceSplitAttribute, *pD_OffsetConstellationTraceSplitAttribute;

typedef struct{
    /*  Returns the start sample index. */
    ViReal64 dX0;
    /* Returns the spacing between samples normalized to samples per symbol.*/
    ViReal64 dDX;
    /* Returns the measured samples. To get the size of y array, set arraySize parameter to 0. 
     * You can pass NULL for this parameter if the arraySize is set to 0. 
     * If the y array is not large enough to hold all the samples, the function returns an error.
     */
    ComplexNumber* pMeasurementWaveform;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
    /* Returns the samples per symbol.*/
    ViInt32 nSamplesPerSymbol;
    /* Returns the symbol rate in Hz.*/
    ViReal64 dwSymbolRate;
}D_MeasurementWaveformAttribute, *pD_MeasurementWaveformAttribute;

typedef struct{
    /* Returns the start sample index.*/
    ViReal64 dX0;
    /* Returns the spacing between samples normalized to samples per symbol.*/
    ViReal64 dDX;
    /* Returns the real part of measured samples. 
     * To get the size of y array, set arraySize parameter to 0. 
     * You can pass NULL for this parameter if the arraySize is set to 0. 
     * If the y array is not large enough to hold all the samples, the function returns an error.*/
    ViReal32* pIData;
    /* Returns the imaginary part of measured samples. 
     * To get the size of y array, set arraySize parameter to 0. 
     * You can pass NULL for this parameter if the arraySize is set to 0. 
     * If the y array is not large enough to hold all the samples, the function returns an error.*/
    ViReal32* pQData;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
    /* Returns the samples per symbol.*/
    ViInt32 nSamplesPerSymbol;
    /* Returns the symbol rate in Hz.*/
    ViReal64 dwSymbolRate;
}D_MeasurementWaveformSplitAttribute, *pD_MeasurementWaveformSplitAttribute;

typedef struct{
    /* Returns the start sample index.*/
    ViReal64 dX0;
    /* Returns the spacing between samples normalized to samples per symbol.*/
    ViReal64 dDX;
    /* Returns the reference samples. 
     * To get the size of y array, set arraySize parameter to 0. 
     * You can pass NULL for this parameter if the arraySize is set to 0. 
     * If the y array is not large enough to hold all the samples, the function returns an error.
     */
    ComplexNumber* pMeasurementWaveform;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}D_ReferenceWaveformAttribute, *pD_ReferenceWaveformAttribute;

typedef struct{
    /* Returns the demodulated bit stream. 
     * To get the size of demodulatedBits array, set arraySize parameter to 0. 
     * You can pass NULL for this parameter if the arraySize is set to 0. 
     * If the demodulatedBits array is not large enough to hold all the samples, the function returns an error.
     */
    ViInt8* pDemodulatedBits;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}D_DemodulatedBitsAttribute, *pD_DemodulatedBitsAttribute;

typedef struct{
    /* This parameter always returns 0.*/
    ViReal64 dX0;
    /* Returns the spacing between the coefficients as a fraction of the symbol spacing. For example, if four coefficients correspond to one symbol, the spacing is 1/4. */
    ViReal64 dDX;
    /* Specifies the filter coefficients used as the equalizer coefficients. 
     * To get the size of y array, set arraySize parameter to 0. You can pass NULL for this parameter if the arraySize is set to 0. 
     * If the y array is not large enough to hold all the samples, the function returns an error.
     */
    ComplexNumber* pEqualizerCoefficients;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}D_EqualizerCoefficientsAttribute, *pD_EqualizerCoefficientsAttribute;


typedef struct{
    D_CarrierMeasurementAttribute CarrierMeasurement;
    D_EVMAttribute EVM;
    D_OffsetEVMAttribute OffsetEVM;
    D_MagnitudeErrorAttribute MagnitudeError;
    D_PhaseErrorAttribute PhaseError;
    D_FSKResultsAttribute FSKResults;
    D_SyncFoundAttribute SyncFound;
    D_IQImpairmentsAttribute IQImpairments;
    D_MeanAmplitudeDroopAttribute MeanAmplitudeDroop;
    D_MeanIQOriginOffsetAttribute MeanIQOriginOffset;
    D_MeanQuadratureSkewAttribute MeanQuadratureSkew;
    D_MeanRhoFactorAttribute MeanRhoFactor;
    D_EVMTraceAttribute EVMTrace;
    D_OffsetEVMTraceAttribute OffsetEVMTrace;
    D_MagnitudeErrorTraceAttribute MagnitudeErrorTrace;
    D_PhaseErrorTraceAttribute PhaseErrorTrace;
    D_FSKDeviationTraceAttribute FSKDeviationTrace;
    D_ConstellationTraceAttribute ConstellationTrace;
    D_OffsetConstellationTraceAttribute OffsetConstellationTrace;
    D_MeasurementWaveformAttribute MeasurementWaveform;
    D_ReferenceWaveformAttribute ReferenceWaveform;
    D_DemodulatedBitsAttribute DemodulatedBits;
    D_EqualizerCoefficientsAttribute EqualizerCoefficients;
}RfmxDDemodResult, *pRfmxDDemodResult;


typedef struct{
    /* Returns the mean of the measured carrier frequency offset, in Hz.*/
    ViReal64 dwMeanCarrierFrequencyError;
    /* Returns the mean of the measured carrier power, in dBm.*/
    ViReal64 dwMeanCarrierPower;
}ACarrierMeasurementAttribute,*pACarrierMeasurementAttribute;

typedef struct{
    /* Returns the mean of the demodulated signal frequency.*/
    ViReal64 dwMeanModulationFrequency;
}AModulationFrequencyAttribute,*pAModulationFrequencyAttribute;

typedef struct{
    /*  Returns the averaged signal-to-noise and distortion ratio, in dB, of the demodulated signal. */
    ViReal64 dwAverageSINAD;
    /* Returns the averaged signal-to-noise ratio, in dB, of the demodulated signal.*/
    ViReal64 dwAverageSNR;
    /* Returns the averaged total harmonic distortion (THD), as a percentage, of the demodulated signal.*/
    ViReal64 dwAverageTHD;
    /* Returns the averaged THD with noise, as a percentage, of the demodulated signal.*/
    ViReal64 dwAverageTHDWithNoise;
}ADistortionsAttribute,*pADistortionsAttribute;

typedef struct{
    /* Returns the mean amplitude variation, as a percentage, around the unmodulated carrier amplitude. If the carrier is suppressed, the amplitude variation of the modulating signal is returned.*/
    ViReal64 dwMeanModulationDepth;
    /* Returns the mean (peak-to-peak)/2 amplitude, as a percentage, of the modulating signal.*/
    ViReal64 dwMeanHalfPeakToPeak;
    /* Returns the mean RMS amplitude of the modulating signal.*/
    ViReal64 dwMeanRMS;
    /* Returns the mean positive peak amplitude, as a percentage, of the modulating signal.*/
    ViReal64 dwMeanPositivePeak;
    /* Returns the mean negative peak amplitude, as a percentage, of the modulating signal.*/
    ViReal64 dwMeanNegativePeak;
}AMMeanModulationDepthAttribute,*pAMMeanModulationDepthAttribute;


typedef struct{
    union{
        /* Returns the mean amplitude variation, as a percentage, around the unmodulated carrier amplitude. If the carrier is suppressed, the amplitude variation of the modulating signal is returned.*/
        ViReal64 dwMeanModulationDepth;
        /* Returns the mean deviation, in Hz, of the frequency-modulated signal.*/
        ViReal64 dwMeanDeviation;
    };
    /* Returns the mean (peak-to-peak)/2 frequency variation, in Hz, around the nominal frequency of the FM carrier.*/
    ViReal64 dwMeanHalfPeakToPeak;
    /* Returns the mean RMS frequency deviation, in Hz, of the frequency-modulated signal.*/
    ViReal64 dwMeanRMS;
    /* Returns the mean positive peak frequency deviation, in Hz, of the frequency-modulated signal.*/
    ViReal64 dwMeanPositivePeak;
    /* Returns the mean negative peak frequency deviation, in Hz, of the frequency-modulated signal.*/
    ViReal64 dwMeanNegativePeak;
}MeanDeviationAttribute,*pMeanDeviationAttribute;

typedef struct{
    union{
        /* Returns the maximum modulation depth, as a percentage, measured across multiple acquisitions.*/
        ViReal64 dwMaximumModulationDepth;
        /* Returns the maximum frequency deviation, in Hz, of the frequency-modulated signal measured across multiple acquisitions.*/
        ViReal64 dwMaximumDeviation;
    };
    /* Returns the maximum (peak-to-peak)/2 amplitude, as a percentage, of the modulating signal measured across multiple acquisitions.
     * Returns the maximum (peak-to-peak)/2 frequency variation, in Hz, around the nominal frequency of the FM carrier measured across multiple acquisitions.
     * Returns the maximum (peak to peak)/2 phase deviation, in degrees, around the unmodulated carrier phase measured over multiple acquisitions.
     */
    ViReal64 dwMaximumHalfPeakToPeak;
    /* Returns the maximum RMS amplitude, as a percentage, of the modulating signal measured across multiple acquisitions.
     * Returns the maximum RMS frequency deviation, in Hz, of the frequency-modulated signal measured across multiple acquisitions.
     * Returns the maximum RMS phase deviation, in degrees, of the PM signal measured over multiple acquisitions.
     */
    ViReal64 dwMaximumRMS;
    /* Returns the maximum positive peak amplitude, as a percentage, of the modulating signal measured across multiple acquisitions.
     * Returns the maximum positive peak frequency deviation, in Hz, of the frequency-modulated signal measured across multiple acquisitions.
     * Returns the maximum positive peak phase deviation, in degrees, around the unmodulated carrier phase, measured across multiple acquisitions.
     */
    ViReal64 dwMaximumPositivePeak;
    /* Returns the maximum negative peak amplitude, as a percentage, of the modulating signal measured across multiple acquisitions.
     * Returns the maximum negative peak frequency deviation, in Hz, of the frequency-modulated signal measured across multiple acquisitions.
     * Returns the maximum negative peak phase deviation, in degrees, around the unmodulated carrier phase, measured across multiple acquisitions.
     */
    ViReal64 dwMaximumNegativePeak;
}MaximumDeviationAttribute,*pMaximumDeviationAttribute;


typedef struct{
    /* Returns the start time, in seconds.*/
    ViReal64 dwX0;
    /* Returns the sample duration, in seconds.*/
    ViReal64 dwDx;
    /* Returns the signal amplitude as a percentage for AM, in Hz for FM, and in degrees for PM signals, at each time instance. 
     * To get the size of y array, set arraySize parameter to 0. You can pass NULL for this parameter if the arraySize is set to 0. 
     * If the y array is not large enough to hold all the samples, the function returns an error. 
     */
    ViReal32* pDemodulatedBuf;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}ADemodTrace,*pADemodTrace;

typedef struct{
    /* Fetches the carrier measurement.*/
    ACarrierMeasurementAttribute CarrierMeasurement;
    /* Fetches the mean modulation frequency.*/
    AModulationFrequencyAttribute MeanModulationFrequency;
    /* Fetches distortions for analog demodulation measurements.*/
    ADistortionsAttribute Distortions;
    union{
        /* Fetches AM mean modulation depth for analog demodulation measurements.*/
        MeanDeviationAttribute AMMeanModulationDepth;
        /* Fetches the FM mean deviation measurements.*/
        MeanDeviationAttribute FMMeanDeviation;
        /* Fetches the PM mean deviation measurements.*/
        MeanDeviationAttribute PMMeanDeviation;
    };
    union{
        /* Fetches the AM maximum modulation depth.*/
        MaximumDeviationAttribute AMMaximumModulationDepth;
        /* Fetches the FM maximum deviation measurements.*/
        MaximumDeviationAttribute FMMaximumDeviation;
        /* Fetches the PM maximum deviation measurements.*/
        MaximumDeviationAttribute PMMaximumDeviation;
    };
    /* Fetches the demodulated signal trace.*/
    ADemodTrace DemodSignalTrace;
    /* Fetches the demodulated signal spectrum trace.*/
    ADemodTrace DemodSpectrumTrace;
}RfmxADemodResult, *pRfmxADemodResult;

typedef struct{
    RfmxADemodResult ADemod;
    RfmxDDemodResult DDemod;
}DemodResultsAttribute,*pDemodResultsAttribute;

class DLLAPI CCRFmxDemodAttribute
{
public:
    CCRFmxDemodAttribute();
    
    RfmxDemodField cfgDemod;
    cfgADemodField ADemod;
    cfgDDemodField DDemod;

private:
    void DemodFields_SetDefault();
    void FetchDDemod_SetDefault();
    void FetchADemod_SetDefault();
};

class DLLAPI CCMxDemodResults: public CCResultsArray<DemodResultsAttribute>
{
public:
    CCMxDemodResults();
    ~CCMxDemodResults();
    
public:
    void RemoveAll();

};


#endif	/* CCRFMXDEMODTYPEDEF_H */

