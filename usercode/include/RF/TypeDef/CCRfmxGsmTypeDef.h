/* 
 * File:   CCRfmxGsmTypeDef.h
 * Author: dongyuqing
 *
 * Created on 2020年12月29日, 上午11:23
 */
#pragma once

#ifndef CCRFMXGSMTYPEDEF_H
#define	CCRFMXGSMTYPEDEF_H

#include "CCResults.h"
#include "CCTesterDef.h"


#define CCRFMXGSM_ATTR_MODACC_MEASUREMENT_ENABLED                              0x00401000
#define CCRFMXGSM_ATTR_MODACC_AVERAGING_ENABLED                                0x00401002
#define CCRFMXGSM_ATTR_MODACC_AVERAGING_COUNT                                  0x00401004
#define CCRFMXGSM_ATTR_MODACC_DROOP_COMPENSATION_ENABLED                       0x00401005
#define CCRFMXGSM_ATTR_MODACC_ALL_TRACES_ENABLED                               0x00401006
#define CCRFMXGSM_ATTR_MODACC_NUMBER_OF_ANALYSIS_THREADS                       0x00401007
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_MEAN_RMS_EVM                         0x00401008
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_MAXIMUM_RMS_EVM                      0x00401009
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_MEAN_PEAK_EVM                        0x0040100a
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_MAXIMUM_PEAK_EVM                     0x0040100b
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_95TH_PERCENTILE_EVM                  0x0040100c
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_PEAK_EVM_SYMBOL                      0x0040100d
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_MEAN_MAGNITUDE_ERROR                 0x0040100e
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_MAXIMUM_MAGNITUDE_ERROR              0x0040100f
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_MEAN_PHASE_ERROR                     0x00401010
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_MAXIMUM_PHASE_ERROR                  0x00401011
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_MEAN_FREQUENCY_ERROR                 0x00401012
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_MAXIMUM_FREQUENCY_ERROR              0x00401013
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_MEAN_AMPLITUDE_DROOP                 0x00401014
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_MAXIMUM_AMPLITUDE_DROOP              0x00401015
#define CCRFMXGSM_ATTR_MODACC_RESULTS_PFER_MEAN_RMS_PHASE_ERROR                0x00401016
#define CCRFMXGSM_ATTR_MODACC_RESULTS_PFER_MAXIMUM_RMS_PHASE_ERROR             0x00401017
#define CCRFMXGSM_ATTR_MODACC_RESULTS_PFER_MEAN_PEAK_PHASE_ERROR               0x00401018
#define CCRFMXGSM_ATTR_MODACC_RESULTS_PFER_MAXIMUM_PEAK_PHASE_ERROR            0x00401019
#define CCRFMXGSM_ATTR_MODACC_RESULTS_PFER_PEAK_PHASE_ERROR_SYMBOL             0x0040101a
#define CCRFMXGSM_ATTR_MODACC_RESULTS_PFER_MEAN_FREQUENCY_ERROR                0x0040101b
#define CCRFMXGSM_ATTR_MODACC_RESULTS_PFER_MAXIMUM_FREQUENCY_ERROR             0x0040101c
#define CCRFMXGSM_ATTR_MODACC_RESULTS_MEAN_IQ_GAIN_IMBALANCE                   0x0040101d
#define CCRFMXGSM_ATTR_MODACC_RESULTS_MAXIMUM_IQ_GAIN_IMBALANCE                0x0040101e
#define CCRFMXGSM_ATTR_MODACC_RESULTS_MEAN_IQ_ORIGIN_OFFSET                    0x0040101f
#define CCRFMXGSM_ATTR_MODACC_RESULTS_MAXIMUM_IQ_ORIGIN_OFFSET                 0x00401020
#define CCRFMXGSM_ATTR_MODACC_RESULTS_DETECTED_TSC                             0x00401021
#define CCRFMXGSM_ATTR_ORFS_MEASUREMENT_ENABLED                                0x00402000
#define CCRFMXGSM_ATTR_ORFS_AVERAGING_ENABLED                                  0x00402002
#define CCRFMXGSM_ATTR_ORFS_AVERAGING_TYPE                                     0x00402003
#define CCRFMXGSM_ATTR_ORFS_AVERAGING_COUNT                                    0x00402004
#define CCRFMXGSM_ATTR_ORFS_MEASUREMENT_TYPE                                   0x00402005
#define CCRFMXGSM_ATTR_ORFS_OFFSET_FREQUENCY_MODE                              0x00402007
#define CCRFMXGSM_ATTR_ORFS_EVALUATION_SYMBOLS_START                           0x00402011
#define CCRFMXGSM_ATTR_ORFS_EVALUATION_SYMBOLS_INCLUDE_TSC                     0x00402012
#define CCRFMXGSM_ATTR_ORFS_EVALUATION_SYMBOLS_STOP                            0x00402013
#define CCRFMXGSM_ATTR_ORFS_MODULATION_NUMBER_OF_OFFSETS                       0x0040201d
#define CCRFMXGSM_ATTR_ORFS_MODULATION_OFFSET_FREQUENCY                        0x0040201e
#define CCRFMXGSM_ATTR_ORFS_MODULATION_OFFSET_RBW                              0x0040201f
#define CCRFMXGSM_ATTR_ORFS_SWITCHING_NUMBER_OF_OFFSETS                        0x00402020
#define CCRFMXGSM_ATTR_ORFS_SWITCHING_OFFSET_FREQUENCY                         0x00402021
#define CCRFMXGSM_ATTR_ORFS_SWITCHING_OFFSET_RBW                               0x00402022
#define CCRFMXGSM_ATTR_ORFS_NOISE_COMPENSATION_ENABLED                         0x00402006
#define CCRFMXGSM_ATTR_ORFS_ALL_TRACES_ENABLED                                 0x00402014
#define CCRFMXGSM_ATTR_ORFS_NUMBER_OF_ANALYSIS_THREADS                         0x00402015
#define CCRFMXGSM_ATTR_PVT_MEASUREMENT_ENABLED                                 0x00403000
#define CCRFMXGSM_ATTR_PVT_AVERAGING_ENABLED                                   0x00403002
#define CCRFMXGSM_ATTR_PVT_AVERAGING_TYPE                                      0x00403004
#define CCRFMXGSM_ATTR_PVT_AVERAGING_COUNT                                     0x00403005
#define CCRFMXGSM_ATTR_PVT_ALL_TRACES_ENABLED                                  0x00403009
#define CCRFMXGSM_ATTR_PVT_NUMBER_OF_ANALYSIS_THREADS                          0x0040300a
#define CCRFMXGSM_ATTR_PVT_RESULTS_MEASUREMENT_STATUS                          0x0040300b
#define CCRFMXGSM_ATTR_PVT_RESULTS_SLOT_AVERAGE_POWER                          0x0040300c
#define CCRFMXGSM_ATTR_PVT_RESULTS_SLOT_BURST_WIDTH                            0x0040300d
#define CCRFMXGSM_ATTR_PVT_RESULTS_SLOT_MAXIMUM_POWER                          0x0040300e
#define CCRFMXGSM_ATTR_PVT_RESULTS_SLOT_MINIMUM_POWER                          0x0040300f
#define CCRFMXGSM_ATTR_PVT_RESULTS_SLOT_BURST_THRESHOLD                        0x00403010
#define CCRFMXGSM_ATTR_PVT_RESULTS_SLOT_MEASUREMENT_STATUS                     0x00403011
#define CCRFMXGSM_ATTR_LIMITED_CONFIGURATION_CHANGE                            0x0040d003
#define CCRFMXGSM_ATTR_RESULT_FETCH_TIMEOUT                                    0x0040c000
#define CCRFMXGSM_ATTR_CENTER_FREQUENCY                                        0x00400001
#define CCRFMXGSM_ATTR_REFERENCE_LEVEL                                         0x00400002
#define CCRFMXGSM_ATTR_EXTERNAL_ATTENUATION                                    0x00400003
#define CCRFMXGSM_ATTR_TRIGGER_TYPE                                            0x00400004
#define CCRFMXGSM_ATTR_DIGITAL_EDGE_TRIGGER_SOURCE                             0x00400005
#define CCRFMXGSM_ATTR_DIGITAL_EDGE_TRIGGER_EDGE                               0x00400006
#define CCRFMXGSM_ATTR_IQ_POWER_EDGE_TRIGGER_SOURCE                            0x00400007
#define CCRFMXGSM_ATTR_IQ_POWER_EDGE_TRIGGER_LEVEL                             0x00400008
#define CCRFMXGSM_ATTR_IQ_POWER_EDGE_TRIGGER_LEVEL_TYPE                        0x00400fff
#define CCRFMXGSM_ATTR_IQ_POWER_EDGE_TRIGGER_SLOPE                             0x00400009
#define CCRFMXGSM_ATTR_TRIGGER_DELAY                                           0x0040000a
#define CCRFMXGSM_ATTR_TRIGGER_MINIMUM_QUIET_TIME_MODE                         0x0040000b
#define CCRFMXGSM_ATTR_TRIGGER_MINIMUM_QUIET_TIME_DURATION                     0x0040000c
#define CCRFMXGSM_ATTR_LINK_DIRECTION                                          0x0040000d
#define CCRFMXGSM_ATTR_BAND                                                    0x0040000e
#define CCRFMXGSM_ATTR_SIGNAL_STRUCTURE                                        0x00400017
#define CCRFMXGSM_ATTR_NUMBER_OF_TIMESLOTS                                     0x0040000f
#define CCRFMXGSM_ATTR_MODULATION_TYPE                                         0x00400010
#define CCRFMXGSM_ATTR_BURST_TYPE                                              0x00400011
#define CCRFMXGSM_ATTR_HB_FILTER_WIDTH                                         0x00400012
#define CCRFMXGSM_ATTR_AUTO_TSC_DETECTION_ENABLED                              0x00400013
#define CCRFMXGSM_ATTR_TSC                                                     0x00400014
#define CCRFMXGSM_ATTR_POWER_CONTROL_LEVEL                                     0x00400015
#define CCRFMXGSM_ATTR_TIMING_ADVANCE                                          0x00400018
#define CCRFMXGSM_ATTR_BURST_SYNCHRONIZATION_TYPE                              0x00400016
#define CCRFMXGSM_ATTR_AUTO_LEVEL_INITIAL_REFERENCE_LEVEL                      0x0040d000
#define CCRFMXGSM_ATTR_SELECTED_PORTS                                          0x00400ffd
#define CCRFMXGSM_ATTR_REFERENCE_LEVEL_HEADROOM                                0x00400ffc
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_MEAN_PEAK_MAGNITUDE_ERROR            0x00401023
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_MAXIMUM_PEAK_MAGNITUDE_ERROR         0x00401024
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_95TH_PERCENTILE_MAGNITUDE_ERROR      0x00401025
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_MEAN_PEAK_PHASE_ERROR                0x00401026
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_MAXIMUM_PEAK_PHASE_ERROR             0x00401027
#define CCRFMXGSM_ATTR_MODACC_RESULTS_EVM_95TH_PERCENTILE_PHASE_ERROR          0x00401028
#define CCRFMXGSM_ATTR_MODACC_RESULTS_PFER_95TH_PERCENTILE_PHASE_ERROR         0x00401029

// Values for RFMXGSM_ATTR_TRIGGER_TYPE
#define CCRFMXGSM_VAL_TRIGGER_TYPE_NONE                                                              0
#define CCRFMXGSM_VAL_TRIGGER_TYPE_DIGITAL_EDGE                                                      1
#define CCRFMXGSM_VAL_TRIGGER_TYPE_IQ_POWER_EDGE                                                     2
#define CCRFMXGSM_VAL_TRIGGER_TYPE_SOFTWARE                                                          3

// Values for RFMXGSM_ATTR_DIGITAL_EDGE_TRIGGER_SOURCE
#define CCRFMXGSM_VAL_PFI0_STR                                                                       "PFI0"
#define CCRFMXGSM_VAL_PFI1_STR                                                                       "PFI1"
#define CCRFMXGSM_VAL_PXI_TRIG0_STR                                                                  "PXI_Trig0"
#define CCRFMXGSM_VAL_PXI_TRIG1_STR                                                                  "PXI_Trig1"
#define CCRFMXGSM_VAL_PXI_TRIG2_STR                                                                  "PXI_Trig2"
#define CCRFMXGSM_VAL_PXI_TRIG3_STR                                                                  "PXI_Trig3"
#define CCRFMXGSM_VAL_PXI_TRIG4_STR                                                                  "PXI_Trig4"
#define CCRFMXGSM_VAL_PXI_TRIG5_STR                                                                  "PXI_Trig5"
#define CCRFMXGSM_VAL_PXI_TRIG6_STR                                                                  "PXI_Trig6"
#define CCRFMXGSM_VAL_PXI_TRIG7_STR                                                                  "PXI_Trig7"
#define CCRFMXGSM_VAL_PXI_STAR_STR                                                                   "PXI_STAR"

// Values for RFMXGSM_ATTR_DIGITAL_EDGE_TRIGGER_EDGE
#define CCRFMXGSM_VAL_DIGITAL_EDGE_RISING_EDGE                                                       0
#define CCRFMXGSM_VAL_DIGITAL_EDGE_FALLING_EDGE                                                      1

// Values for RFMXGSM_ATTR_IQ_POWER_EDGE_TRIGGER_LEVEL_TYPE
#define CCRFMXGSM_VAL_IQ_POWER_EDGE_TRIGGER_LEVEL_TYPE_RELATIVE                                      0
#define CCRFMXGSM_VAL_IQ_POWER_EDGE_TRIGGER_LEVEL_TYPE_ABSOLUTE                                      1

// Values for RFMXGSM_ATTR_IQ_POWER_EDGE_TRIGGER_SLOPE
#define CCRFMXGSM_VAL_IQ_POWER_EDGE_RISING_SLOPE                                                     0
#define CCRFMXGSM_VAL_IQ_POWER_EDGE_FALLING_SLOPE                                                    1

// Values for RFMXGSM_ATTR_TRIGGER_MINIMUM_QUIET_TIME_MODE
#define CCRFMXGSM_VAL_TRIGGER_MINIMUM_QUIET_TIME_MODE_MANUAL                                         0
#define CCRFMXGSM_VAL_TRIGGER_MINIMUM_QUIET_TIME_MODE_AUTO                                           1

// Values for RFMXGSM_ATTR_LINK_DIRECTION
#define CCRFMXGSM_VAL_LINK_DIRECTION_DOWNLINK                                                        0
#define CCRFMXGSM_VAL_LINK_DIRECTION_UPLINK                                                          1

// Values for RFMXGSM_ATTR_BAND
#define CCRFMXGSM_VAL_BAND_PGSM                                                                      0
#define CCRFMXGSM_VAL_BAND_EGSM                                                                      1
#define CCRFMXGSM_VAL_BAND_RGSM                                                                      2
#define CCRFMXGSM_VAL_BAND_DCS1800                                                                   3
#define CCRFMXGSM_VAL_BAND_PCS1900                                                                   4
#define CCRFMXGSM_VAL_BAND_GSM450                                                                    5
#define CCRFMXGSM_VAL_BAND_GSM480                                                                    6
#define CCRFMXGSM_VAL_BAND_GSM850                                                                    7
#define CCRFMXGSM_VAL_BAND_GSM750                                                                    8
#define CCRFMXGSM_VAL_BAND_TGSM810                                                                   9

// Values for RFMXGSM_ATTR_SIGNAL_STRUCTURE
#define CCRFMXGSM_VAL_SIGNAL_STRUCTURE_BURSTED                                                       0
#define CCRFMXGSM_VAL_SIGNAL_STRUCTURE_CONTINUOUS                                                    1

// Values for RFMXGSM_ATTR_MODULATION_TYPE
#define CCRFMXGSM_VAL_MODULATION_TYPE_GMSK                                                           0
#define CCRFMXGSM_VAL_MODULATION_TYPE_8PSK                                                           1
#define CCRFMXGSM_VAL_MODULATION_TYPE_QPSK                                                           2
#define CCRFMXGSM_VAL_MODULATION_TYPE_16QAM                                                          3
#define CCRFMXGSM_VAL_MODULATION_TYPE_32QAM                                                          4

// Values for RFMXGSM_ATTR_BURST_TYPE
#define CCRFMXGSM_VAL_BURST_TYPE_NB                                                                  0
#define CCRFMXGSM_VAL_BURST_TYPE_HB                                                                  1
#define CCRFMXGSM_VAL_BURST_TYPE_AB                                                                  2

// Values for RFMXGSM_ATTR_HB_FILTER_WIDTH
#define CCRFMXGSM_VAL_HB_FILTER_WIDTH_NARROW                                                         0
#define CCRFMXGSM_VAL_HB_FILTER_WIDTH_WIDE                                                           1

// Values for RFMXGSM_ATTR_AUTO_TSC_DETECTION_ENABLED
#define CCRFMXGSM_VAL_AUTO_TSC_DETECTION_ENABLED_FALSE                                               0
#define CCRFMXGSM_VAL_AUTO_TSC_DETECTION_ENABLED_TRUE                                                1

// Values for RFMXGSM_ATTR_TSC
#define CCRFMXGSM_VAL_TSC0                                                                           0
#define CCRFMXGSM_VAL_TSC1                                                                           1
#define CCRFMXGSM_VAL_TSC2                                                                           2
#define CCRFMXGSM_VAL_TSC3                                                                           3
#define CCRFMXGSM_VAL_TSC4                                                                           4
#define CCRFMXGSM_VAL_TSC5                                                                           5
#define CCRFMXGSM_VAL_TSC6                                                                           6
#define CCRFMXGSM_VAL_TSC7                                                                           7

// Values for RFMXGSM_ATTR_BURST_SYNCHRONIZATION_TYPE
#define CCRFMXGSM_VAL_BURST_SYNC_TYPE_TSC                                                            0
#define CCRFMXGSM_VAL_BURST_SYNC_TYPE_AMPLITUDE                                                      1
#define CCRFMXGSM_VAL_BURST_SYNC_TYPE_NONE                                                           2

// Values for RFMXGSM_ATTR_MODACC_AVERAGING_ENABLED
#define CCRFMXGSM_VAL_MODACC_AVERAGING_ENABLED_FALSE                                                 0
#define CCRFMXGSM_VAL_MODACC_AVERAGING_ENABLED_TRUE                                                  1

// Values for RFMXGSM_ATTR_MODACC_DROOP_COMPENSATION_ENABLED
#define CCRFMXGSM_VAL_MODACC_DROOP_COMPENSATION_ENABLED_FALSE                                        0
#define CCRFMXGSM_VAL_MODACC_DROOP_COMPENSATION_ENABLED_TRUE                                         1

// Values for RFMXGSM_ATTR_MODACC_RESULTS_DETECTED_TSC
#define CCRFMXGSM_VAL_MODACC_DETECTED_TSC_UNKNOWN                                                    -1
#define CCRFMXGSM_VAL_MODACC_DETECTED_TSC_TSC0                                                       0
#define CCRFMXGSM_VAL_MODACC_DETECTED_TSC_TSC1                                                       1
#define CCRFMXGSM_VAL_MODACC_DETECTED_TSC_TSC2                                                       2
#define CCRFMXGSM_VAL_MODACC_DETECTED_TSC_TSC3                                                       3
#define CCRFMXGSM_VAL_MODACC_DETECTED_TSC_TSC4                                                       4
#define CCRFMXGSM_VAL_MODACC_DETECTED_TSC_TSC5                                                       5
#define CCRFMXGSM_VAL_MODACC_DETECTED_TSC_TSC6                                                       6
#define CCRFMXGSM_VAL_MODACC_DETECTED_TSC_TSC7                                                       7

// Values for RFMXGSM_ATTR_ORFS_AVERAGING_ENABLED
#define CCRFMXGSM_VAL_ORFS_AVERAGING_ENABLED_FALSE                                                   0
#define CCRFMXGSM_VAL_ORFS_AVERAGING_ENABLED_TRUE                                                    1

// Values for RFMXGSM_ATTR_ORFS_AVERAGING_TYPE
#define CCRFMXGSM_VAL_ORFS_AVERAGING_TYPE_RMS                                                        0
#define CCRFMXGSM_VAL_ORFS_AVERAGING_TYPE_LOG                                                        1

// Values for RFMXGSM_ATTR_ORFS_MEASUREMENT_TYPE
#define CCRFMXGSM_VAL_ORFS_MEASUREMENT_TYPE_MODULATION_AND_SWITCHING                                 0
#define CCRFMXGSM_VAL_ORFS_MEASUREMENT_TYPE_MODULATION                                               1
#define CCRFMXGSM_VAL_ORFS_MEASUREMENT_TYPE_SWITCHING                                                2

// Values for RFMXGSM_ATTR_ORFS_OFFSET_FREQUENCY_MODE
#define CCRFMXGSM_VAL_ORFS_OFFSET_FREQUENCY_MODE_STANDARD                                            0
#define CCRFMXGSM_VAL_ORFS_OFFSET_FREQUENCY_MODE_SHORT                                               1
#define CCRFMXGSM_VAL_ORFS_OFFSET_FREQUENCY_MODE_CUSTOM                                              2

// Values for RFMXGSM_ATTR_ORFS_EVALUATION_SYMBOLS_INCLUDE_TSC
#define CCRFMXGSM_VAL_ORFS_EVALUATION_SYMBOLS_INCLUDE_TSC_FALSE                                      0
#define CCRFMXGSM_VAL_ORFS_EVALUATION_SYMBOLS_INCLUDE_TSC_TRUE                                       1

// Values for RFMXGSM_ATTR_ORFS_NOISE_COMPENSATION_ENABLED
#define CCRFMXGSM_VAL_ORFS_NOISE_COMPENSATION_ENABLED_FALSE                                          0
#define CCRFMXGSM_VAL_ORFS_NOISE_COMPENSATION_ENABLED_TRUE                                           1

// Values for RFMXGSM_ATTR_PVT_AVERAGING_ENABLED
#define CCRFMXGSM_VAL_PVT_AVERAGING_ENABLED_FALSE                                                    0
#define CCRFMXGSM_VAL_PVT_AVERAGING_ENABLED_TRUE                                                     1

// Values for RFMXGSM_ATTR_PVT_AVERAGING_TYPE
#define CCRFMXGSM_VAL_PVT_AVERAGING_TYPE_RMS                                                         0
#define CCRFMXGSM_VAL_PVT_AVERAGING_TYPE_LOG                                                         1
#define CCRFMXGSM_VAL_PVT_AVERAGING_TYPE_MAXIMUM                                                     3
#define CCRFMXGSM_VAL_PVT_AVERAGING_TYPE_MINIMUM                                                     4

// Values for RFMXGSM_ATTR_PVT_RESULTS_MEASUREMENT_STATUS
#define CCRFMXGSM_VAL_PVT_MEASUREMENT_STATUS_FAIL                                                    0
#define CCRFMXGSM_VAL_PVT_MEASUREMENT_STATUS_PASS                                                    1

// Values for RFMXGSM_ATTR_PVT_RESULTS_SLOT_MEASUREMENT_STATUS
#define CCRFMXGSM_VAL_PVT_SLOT_MEASUREMENT_STATUS_FAIL                                               0
#define CCRFMXGSM_VAL_PVT_SLOT_MEASUREMENT_STATUS_PASS                                               1

// Values for RFMXGSM_ATTR_LIMITED_CONFIGURATION_CHANGE
#define CCRFMXGSM_VAL_LIMITED_CONFIGURATION_CHANGE_DISABLED                                          0
#define CCRFMXGSM_VAL_LIMITED_CONFIGURATION_CHANGE_NO_CHANGE                                         1
#define CCRFMXGSM_VAL_LIMITED_CONFIGURATION_CHANGE_FREQUENCY                                         2
#define CCRFMXGSM_VAL_LIMITED_CONFIGURATION_CHANGE_REFERENCE_LEVEL                                   3
#define CCRFMXGSM_VAL_LIMITED_CONFIGURATION_CHANGE_FREQUENCY_AND_REFERENCE_LEVEL                     4
#define CCRFMXGSM_VAL_LIMITED_CONFIGURATION_CHANGE_SELECTED_PORTS_FREQUENCY_AND_REFERENCE_LEVEL      5

// Values for Boolean
#define CCRFMXGSM_VAL_FALSE                                                                          0
#define CCRFMXGSM_VAL_TRUE                                                                           1

// Values for MeasurementTypes
#define CCRFMXGSM_VAL_MODACC                                                                         1 << 0
#define CCRFMXGSM_VAL_ORFS                                                                           1 << 1
#define CCRFMXGSM_VAL_PVT                                                                            1 << 2

// Values for FrequencyReferenceSource
#define CCRFMXGSM_VAL_ONBOARD_CLOCK_STR                                                              "OnboardClock"
#define CCRFMXGSM_VAL_REF_IN_STR                                                                     "RefIn"
#define CCRFMXGSM_VAL_PXI_CLK_STR                                                                    "PXI_Clk"
#define CCRFMXGSM_VAL_CLK_IN_STR                                                                     "ClkIn"

// Values for RFAttenuationAuto
#define CCRFMXGSM_VAL_RF_ATTENUATION_AUTO_FALSE                                                      0
#define CCRFMXGSM_VAL_RF_ATTENUATION_AUTO_TRUE                                                       1

// Values for MechanicalAttenuationAuto
#define CCRFMXGSM_VAL_MECHANICAL_ATTENUATION_AUTO_FALSE                                              0
#define CCRFMXGSM_VAL_MECHANICAL_ATTENUATION_AUTO_TRUE                                               1


typedef struct{
    /* Specifies the modulation type of the signal.*/
    ViInt32 nModulationType;
    /* Specifies the burst type.*/
    ViInt32 nBurstType;
    /* Specifies the filter width when you set the burstType parameter to RFMXGSM_VAL_BURST_TYPE_HB.*/
    ViInt32 nHBFilterWidth;
}CfgSignalTypeAttribute,*pCfgSignalTypeAttribute;

typedef struct{
    /* Specifies the source of the signal to be measured.*/
    ViInt32 nLinkDirection;
    /* Specifies the band of operation.*/
    ViInt32 nBand;
    /* Specifies the ARFCN. */
    ViInt32 nARFCN;
}CfgFrequencyARFCNAttribute,*pCfgFrequencyARFCNAttribute;

typedef struct{
    /* Specifies whether to enable droop compensation for the ModAcc measurement. 
     * Droop compensation allows the ModAcc measurement to minimize the contribution of amplifier power variations to the EVM results.*/
    ViInt32 nDroopCompensationEnabled;
    /* Specifies whether to enable averaging for the measurement.*/
    ViInt32 nAveragingEnabled;
    /* Specifies the number of acquisitions used for averaging when you set the averagingEnabled parameter to RFMXGSM_VAL_MODACC_AVERAGING_ENABLED_TRUE.*/
    ViInt32 nAveragingCount;
}CfgModAccAttribute,*pCfgModAccAttribute;

typedef struct{
    /* Returns the mean of RMS EVM values measured over all acquisition time slots. 
     * This value is expressed as a percentage.*/
    ViReal64 dMeanRMSEVM;
    /* Returns the maximum of RMS EVM values measured over all acquisition time slots. 
     * This value is expressed as a percentage.*/
    ViReal64 dMaximumRMSEVM;
    /* Returns the mean of peak EVM values measured over all acquisition time slots. 
     * This value is expressed as a percentage.*/
    ViReal64 dMeanPeakEVM;
    /* Returns the maximum of peak EVM values measured over all acquisition time slots. 
     * This value is expressed as a percentage.*/
    ViReal64 dMaximumPeakEVM;
    /* Returns the EVM value, at which no more than 5 percent of the symbols have an EVM exceeding this value. 
     * This value is expressed as a percentage.*/
    ViReal64 dNinetyFifthPercentileEVM;
    /* Returns the mean of frequency error values measured over all acquisition time slots. 
     * This value is expressed in Hz. */
    ViReal64 dMeanFrequencyError;
    /* Returns the symbol number in the burst measurement interval corresponding to the EVM value returned by the maximumPeakEVM parameter.*/
    ViInt32 nPeakEVMSymbol;
}EVMResultsAttribute,*pEVMResultsAttribute;

typedef struct{
    /* Returns the mean of I/Q gain imbalance values measured over all acquisition time slots*/
    ViReal64 dMeanIQGainImbalance;
    /* Returns the maximum of I/Q gain imbalance values measured over all acquisition time slots.*/
    ViReal64 dMaximumIQGainImbalance;
    /* Returns the mean of I/Q origin offset values measured over all acquisition time slots.*/
    ViReal64 dMeanIQOriginOffset;
    /* Returns the maximum of I/Q origin offset values measured over all acquisition time slots.*/
    ViReal64 dMaximumIQOriginOffset;
}IQImpairmentsResultsAttribute,*pIQImpairmentsResultsAttribute;

typedef struct{
    /* Returns an array of the detected TSCs when you set the RFMXGSM_ATTR_BURST_SYNCHRONIZATION_TYPE attribute to RFMXGSM_VAL_BURST_SYNC_TYPE_TSC.*/
    ViInt32* pDetectedTSC;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}DetectedTSCArrayResultsAttribute,*pDetectedTSCArrayResultsAttribute;

typedef struct{
    /* Returns the constellation trace concatenated over all slots for the last acquisition.*/
    ComplexNumber* pConstellationTrace;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}ConstellationTraceResultsAttribute,*pConstellationTraceResultsAttribute;

typedef struct{
    EVMResultsAttribute EVM;
    IQImpairmentsResultsAttribute IQImpairments;
    DetectedTSCArrayResultsAttribute DetectedTSCArray;
    DataResultAttribute EVMTrace;
    ConstellationTraceResultsAttribute ConstellationTrace;
}ModAccResultAttribute,*pModAccResultAttribute;

typedef struct{
    ModAccResultAttribute ModAcc;
}GsmResultsAttribute,*pGsmResultsAttribute;

//class DLLAPI CCRFmxGsmAttribute
class CCRFmxGsmAttribute
{
public:
    CCRFmxGsmAttribute();
public:
    /* Specifies the expected center frequency of the RF signal to acquire. 
     * This value is expressed in Hz. The signal analyzer tunes to this frequency.*/
    ViReal64 dCenterFrequency;
    /* Specifies the reference level, which represents the maximum expected power of the RF input signal. 
     * This value is expressed in dBm for RF devices and Vpk-pk for baseband devices.*/
    ViReal64 dReferenceLevel;
    /*Specifies the measurement type*/
    SelectMeasurementTypeAttribute SelectMeasurement;
    /* Path Loss*/
    ViReal64 dwPathLoss[MAX_SITE];
    /* Specifies the source of the signal to be measured.*/
    ViInt32 nLinkDirection;
    /* Configures the signal type.*/
    CfgSignalTypeAttribute SignalType;
    /* Specifies whether to auto detect the TSC.*/
    ViInt32 nAutoTSCDetectionEnabled;
    /* Specifies the training sequence code in the burst. For access burst TSC0, TSC1, and TSC2 are applicable.*/
    ViInt32 nTSC;
    /* Specifies the number of time slots to be measured.*/
    ViInt32 nNumberOfTimeslots;
    /* Specifies the band of operation.*/
    ViInt32 nBand;
    /* Specifies the power control level corresponding to the transmitted power, 
     * as defined in section 4.1 of the 3GPP TS 45.005 v8.0.0 specifications. */
    ViInt32 nPowerControlLevel;
    /* Specifies the method used to synchronize the burst.*/
    ViInt32 nBurstSynchronizationType;
    /* Configures the center frequency from the absolute RF channel number (ARFCN), band, and the link direction.*/
    CfgFrequencyARFCNAttribute ARFCN;
    /* ModAcc*/        
    CfgModAccAttribute ModAcc;
    /*Specifies the trigger type*/
    RfmxInstrTrigger trigger;   
};

class DLLAPI CCMxGsmResults : public CCResultsArray<GsmResultsAttribute>
{
public:
    CCMxGsmResults();
    ~CCMxGsmResults();
    
    void RemoveAll();
};

#endif	/* CCRFMXGSMTYPEDEF_H */

