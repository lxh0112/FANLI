/* 
 * File:   CCRfmxLteTypeDef.h
 * Author: dongyuqing
 *
 * Created on 2021年1月6日, 上午10:22
 */

#pragma once

#ifndef CCRFMXLTETYPEDEF_H
#define	CCRFMXLTETYPEDEF_H

#include "CCResults.h"
#include "CCTesterDef.h"

#ifndef MAX_SELECTOR_STRING
#define MAX_SELECTOR_STRING		256
#endif

#ifndef MAX_CARRIER_SIZE
#define MAX_CARRIER_SIZE		8
#endif

#define CCRFMXLTE_VAL_CARRIER_SIGNLE                                          1 << 0
#define CCRFMXLTE_VAL_CARRIER_CONTIGUOUS                                      1 << 1
#define CCRFMXLTE_VAL_CARRIER_NO_CONTIGUOUS                                   1 << 2

#define CCRFMXLTE_VAL_LINK_DL                                                 1 << 0
#define CCRFMXLTE_VAL_LINK_SL                                                 1 << 1
#define CCRFMXLTE_VAL_LINK_UL                                                 1 << 2

#define CCRFMXLTE_ATTR_MODACC_MEASUREMENT_ENABLED                                             0x00304000
#define CCRFMXLTE_ATTR_MODACC_SYNCHRONIZATION_MODE                                            0x00304003
#define CCRFMXLTE_ATTR_MODACC_MEASUREMENT_OFFSET                                              0x00304004
#define CCRFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH                                              0x00304005
#define CCRFMXLTE_ATTR_MODACC_SPECTRUM_INVERTED                                               0x00304036
#define CCRFMXLTE_ATTR_MODACC_CHANNEL_ESTIMATION_TYPE                                         0x00304037
#define CCRFMXLTE_ATTR_MODACC_EVM_UNIT                                                        0x00304006
#define CCRFMXLTE_ATTR_MODACC_FFT_WINDOW_TYPE                                                 0x00304038
#define CCRFMXLTE_ATTR_MODACC_FFT_WINDOW_OFFSET                                               0x00304007
#define CCRFMXLTE_ATTR_MODACC_FFT_WINDOW_LENGTH                                               0x00304039
#define CCRFMXLTE_ATTR_MODACC_COMMON_CLOCK_SOURCE_ENABLED                                     0x00304009
#define CCRFMXLTE_ATTR_MODACC_EVM_WITH_EXCLUSION_PERIOD_ENABLED                               0x00304032
#define CCRFMXLTE_ATTR_MODACC_SPECTRAL_FLATNESS_CONDITION                                     0x00304008
#define CCRFMXLTE_ATTR_MODACC_AVERAGING_ENABLED                                               0x0030400a
#define CCRFMXLTE_ATTR_MODACC_AVERAGING_COUNT                                                 0x0030400b
#define CCRFMXLTE_ATTR_MODACC_ALL_TRACES_ENABLED                                              0x0030400d
#define CCRFMXLTE_ATTR_MODACC_NUMBER_OF_ANALYSIS_THREADS                                      0x0030400e
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MEAN_RMS_COMPOSITE_EVM                                  0x0030400f
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MAXIMUM_PEAK_COMPOSITE_EVM                              0x00304010
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MEAN_RMS_COMPOSITE_MAGNITUDE_ERROR                      0x0030403a
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MAXIMUM_PEAK_COMPOSITE_MAGNITUDE_ERROR                  0x0030403b
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MEAN_RMS_COMPOSITE_PHASE_ERROR                          0x0030403c
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MAXIMUM_PEAK_COMPOSITE_PHASE_ERROR                      0x0030403d
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PEAK_COMPOSITE_EVM_SLOT_INDEX                           0x00304013
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PEAK_COMPOSITE_EVM_SYMBOL_INDEX                         0x00304014
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PEAK_COMPOSITE_EVM_SUBCARRIER_INDEX                     0x00304015
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PUSCH_MEAN_RMS_DATA_EVM                                 0x00304016
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PUSCH_MAXIMUM_PEAK_DATA_EVM                             0x00304017
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PUSCH_MEAN_RMS_DMRS_EVM                                 0x00304018
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PUSCH_MAXIMUM_PEAK_DMRS_EVM                             0x00304019
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PUSCH_MEAN_DATA_POWER                                   0x0030401a
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PUSCH_MEAN_DMRS_POWER                                   0x0030401b
#define CCRFMXLTE_ATTR_MODACC_RESULTS_IN_BAND_EMISSION_MARGIN                                 0x0030402b
#define CCRFMXLTE_ATTR_MODACC_RESULTS_SPECTRAL_FLATNESS_RANGE1_MAXIMUM_TO_RANGE1_MINIMUM      0x0030402c
#define CCRFMXLTE_ATTR_MODACC_RESULTS_SPECTRAL_FLATNESS_RANGE2_MAXIMUM_TO_RANGE2_MINIMUM      0x0030402d
#define CCRFMXLTE_ATTR_MODACC_RESULTS_SPECTRAL_FLATNESS_RANGE1_MAXIMUM_TO_RANGE2_MINIMUM      0x0030402e
#define CCRFMXLTE_ATTR_MODACC_RESULTS_SPECTRAL_FLATNESS_RANGE2_MAXIMUM_TO_RANGE1_MINIMUM      0x0030402f
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MEAN_FREQUENCY_ERROR                                    0x00304022
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MEAN_IQ_ORIGIN_OFFSET                                   0x00304023
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MEAN_IQ_GAIN_IMBALANCE                                  0x00304024
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MEAN_QUADRATURE_ERROR                                   0x00304025
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MEAN_SYMBOL_CLOCK_ERROR                                 0x00304028
#define CCRFMXLTE_ATTR_MODACC_RESULTS_SUBBLOCK_IN_BAND_EMISSION_MARGIN                        0x0030403e
#define CCRFMXLTE_ATTR_MODACC_RESULTS_SUBBLOCK_MEAN_IQ_ORIGIN_OFFSET                          0x0030403f
#define CCRFMXLTE_ATTR_MODACC_RESULTS_SUBBLOCK_MEAN_IQ_GAIN_IMBALANCE                         0x00304040
#define CCRFMXLTE_ATTR_MODACC_RESULTS_SUBBLOCK_MEAN_QUADRATURE_ERROR                          0x00304041
#define CCRFMXLTE_ATTR_ACP_MEASUREMENT_ENABLED                                                0x00301000
#define CCRFMXLTE_ATTR_ACP_SUBBLOCK_INTEGRATION_BANDWIDTH                                     0x0030103f
#define CCRFMXLTE_ATTR_ACP_COMPONENT_CARRIER_INTEGRATION_BANDWIDTH                            0x00301005
#define CCRFMXLTE_ATTR_ACP_NUMBER_OF_UTRA_OFFSETS                                             0x0030103a
#define CCRFMXLTE_ATTR_ACP_NUMBER_OF_EUTRA_OFFSETS                                            0x0030103b
#define CCRFMXLTE_ATTR_ACP_OFFSET_FREQUENCY                                                   0x0030100a
#define CCRFMXLTE_ATTR_ACP_OFFSET_INTEGRATION_BANDWIDTH                                       0x0030100e
#define CCRFMXLTE_ATTR_ACP_RBW_FILTER_AUTO_BANDWIDTH                                          0x0030101b
#define CCRFMXLTE_ATTR_ACP_RBW_FILTER_BANDWIDTH                                               0x0030101c
#define CCRFMXLTE_ATTR_ACP_RBW_FILTER_TYPE                                                    0x0030101d
#define CCRFMXLTE_ATTR_ACP_SWEEP_TIME_AUTO                                                    0x0030101e
#define CCRFMXLTE_ATTR_ACP_SWEEP_TIME_INTERVAL                                                0x0030101f
#define CCRFMXLTE_ATTR_ACP_MEASUREMENT_METHOD                                                 0x00301012
#define CCRFMXLTE_ATTR_ACP_SEQUENTIAL_FFT_SIZE                                                0x00301041
#define CCRFMXLTE_ATTR_ACP_NOISE_COMPENSATION_ENABLED                                         0x00301020
#define CCRFMXLTE_ATTR_ACP_AVERAGING_ENABLED                                                  0x00301016
#define CCRFMXLTE_ATTR_ACP_AVERAGING_COUNT                                                    0x00301015
#define CCRFMXLTE_ATTR_ACP_AVERAGING_TYPE                                                     0x00301018
#define CCRFMXLTE_ATTR_ACP_IF_OUTPUT_POWER_OFFSET_AUTO                                        0x00301034
#define CCRFMXLTE_ATTR_ACP_NEAR_IF_OUTPUT_POWER_OFFSET                                        0x00301035
#define CCRFMXLTE_ATTR_ACP_FAR_IF_OUTPUT_POWER_OFFSET                                         0x00301036
#define CCRFMXLTE_ATTR_ACP_ALL_TRACES_ENABLED                                                 0x00301021
#define CCRFMXLTE_ATTR_ACP_NUMBER_OF_ANALYSIS_THREADS                                         0x00301014
#define CCRFMXLTE_ATTR_ACP_RESULTS_TOTAL_AGGREGATED_POWER                                     0x00301022
#define CCRFMXLTE_ATTR_ACP_RESULTS_SUBBLOCK_CENTER_FREQUENCY                                  0x00301039
#define CCRFMXLTE_ATTR_ACP_RESULTS_SUBBLOCK_INTEGRATION_BANDWIDTH                             0x00301037
#define CCRFMXLTE_ATTR_ACP_RESULTS_SUBBLOCK_POWER                                             0x00301038
#define CCRFMXLTE_ATTR_ACP_RESULTS_COMPONENT_CARRIER_ABSOLUTE_POWER                           0x00301026
#define CCRFMXLTE_ATTR_ACP_RESULTS_COMPONENT_CARRIER_RELATIVE_POWER                           0x00301027
#define CCRFMXLTE_ATTR_ACP_RESULTS_LOWER_OFFSET_ABSOLUTE_POWER                                0x0030102c
#define CCRFMXLTE_ATTR_ACP_RESULTS_LOWER_OFFSET_RELATIVE_POWER                                0x0030102d
#define CCRFMXLTE_ATTR_ACP_RESULTS_UPPER_OFFSET_ABSOLUTE_POWER                                0x00301032
#define CCRFMXLTE_ATTR_ACP_RESULTS_UPPER_OFFSET_RELATIVE_POWER                                0x00301033
#define CCRFMXLTE_ATTR_CHP_MEASUREMENT_ENABLED                                                0x00303000
#define CCRFMXLTE_ATTR_CHP_INTEGRATION_BANDWIDTH_TYPE                                         0x00303018
#define CCRFMXLTE_ATTR_CHP_SUBBLOCK_INTEGRATION_BANDWIDTH                                     0x00303022
#define CCRFMXLTE_ATTR_CHP_COMPONENT_CARRIER_INTEGRATION_BANDWIDTH                            0x00303002
#define CCRFMXLTE_ATTR_CHP_RBW_FILTER_AUTO_BANDWIDTH                                          0x0030300c
#define CCRFMXLTE_ATTR_CHP_RBW_FILTER_BANDWIDTH                                               0x0030300d
#define CCRFMXLTE_ATTR_CHP_RBW_FILTER_TYPE                                                    0x0030300e
#define CCRFMXLTE_ATTR_CHP_SWEEP_TIME_AUTO                                                    0x00303011
#define CCRFMXLTE_ATTR_CHP_SWEEP_TIME_INTERVAL                                                0x00303012
#define CCRFMXLTE_ATTR_CHP_AVERAGING_ENABLED                                                  0x00303007
#define CCRFMXLTE_ATTR_CHP_AVERAGING_COUNT                                                    0x00303006
#define CCRFMXLTE_ATTR_CHP_AVERAGING_TYPE                                                     0x00303009
#define CCRFMXLTE_ATTR_CHP_ALL_TRACES_ENABLED                                                 0x00303014
#define CCRFMXLTE_ATTR_CHP_NUMBER_OF_ANALYSIS_THREADS                                         0x00303003
#define CCRFMXLTE_ATTR_CHP_RESULTS_TOTAL_AGGREGATED_POWER                                     0x00303019
#define CCRFMXLTE_ATTR_CHP_RESULTS_SUBBLOCK_FREQUENCY                                         0x0030301b
#define CCRFMXLTE_ATTR_CHP_RESULTS_SUBBLOCK_INTEGRATION_BANDWIDTH                             0x0030301c
#define CCRFMXLTE_ATTR_CHP_RESULTS_SUBBLOCK_POWER                                             0x0030301d
#define CCRFMXLTE_ATTR_CHP_RESULTS_COMPONENT_CARRIER_ABSOLUTE_POWER                           0x00303015
#define CCRFMXLTE_ATTR_CHP_RESULTS_COMPONENT_CARRIER_RELATIVE_POWER                           0x00303020
#define CCRFMXLTE_ATTR_OBW_MEASUREMENT_ENABLED                                                0x00306000
#define CCRFMXLTE_ATTR_OBW_SPAN                                                               0x00306004
#define CCRFMXLTE_ATTR_OBW_RBW_FILTER_AUTO_BANDWIDTH                                          0x0030600c
#define CCRFMXLTE_ATTR_OBW_RBW_FILTER_BANDWIDTH                                               0x0030600d
#define CCRFMXLTE_ATTR_OBW_RBW_FILTER_TYPE                                                    0x0030600e
#define CCRFMXLTE_ATTR_OBW_SWEEP_TIME_AUTO                                                    0x0030600f
#define CCRFMXLTE_ATTR_OBW_SWEEP_TIME_INTERVAL                                                0x00306010
#define CCRFMXLTE_ATTR_OBW_AVERAGING_ENABLED                                                  0x00306007
#define CCRFMXLTE_ATTR_OBW_AVERAGING_COUNT                                                    0x00306006
#define CCRFMXLTE_ATTR_OBW_AVERAGING_TYPE                                                     0x00306009
#define CCRFMXLTE_ATTR_OBW_ALL_TRACES_ENABLED                                                 0x00306012
#define CCRFMXLTE_ATTR_OBW_NUMBER_OF_ANALYSIS_THREADS                                         0x00306003
#define CCRFMXLTE_ATTR_OBW_RESULTS_OCCUPIED_BANDWIDTH                                         0x00306013
#define CCRFMXLTE_ATTR_OBW_RESULTS_ABSOLUTE_POWER                                             0x00306014
#define CCRFMXLTE_ATTR_OBW_RESULTS_START_FREQUENCY                                            0x00306015
#define CCRFMXLTE_ATTR_OBW_RESULTS_STOP_FREQUENCY                                             0x00306016
#define CCRFMXLTE_ATTR_SEM_MEASUREMENT_ENABLED                                                0x00308000
#define CCRFMXLTE_ATTR_SEM_SUBBLOCK_INTEGRATION_BANDWIDTH                                     0x00308051
#define CCRFMXLTE_ATTR_SEM_SUBBLOCK_AGGREGATED_CHANNEL_BANDWIDTH                              0x00308052
#define CCRFMXLTE_ATTR_SEM_COMPONENT_CARRIER_INTEGRATION_BANDWIDTH                            0x00308005
#define CCRFMXLTE_ATTR_SEM_NUMBER_OF_OFFSETS                                                  0x0030800b
#define CCRFMXLTE_ATTR_SEM_OFFSET_START_FREQUENCY                                             0x00308014
#define CCRFMXLTE_ATTR_SEM_OFFSET_STOP_FREQUENCY                                              0x00308015
#define CCRFMXLTE_ATTR_SEM_OFFSET_SIDEBAND                                                    0x00308013
#define CCRFMXLTE_ATTR_SEM_OFFSET_RBW_FILTER_BANDWIDTH                                        0x00308017
#define CCRFMXLTE_ATTR_SEM_OFFSET_RBW_FILTER_TYPE                                             0x00308018
#define CCRFMXLTE_ATTR_SEM_OFFSET_BANDWIDTH_INTEGRAL                                          0x0030800c
#define CCRFMXLTE_ATTR_SEM_OFFSET_ABSOLUTE_LIMIT_START                                        0x00308010
#define CCRFMXLTE_ATTR_SEM_OFFSET_ABSOLUTE_LIMIT_STOP                                         0x00308011
#define CCRFMXLTE_ATTR_SEM_SWEEP_TIME_AUTO                                                    0x00308025
#define CCRFMXLTE_ATTR_SEM_SWEEP_TIME_INTERVAL                                                0x00308026
#define CCRFMXLTE_ATTR_SEM_AVERAGING_ENABLED                                                  0x0030801f
#define CCRFMXLTE_ATTR_SEM_AVERAGING_COUNT                                                    0x0030801e
#define CCRFMXLTE_ATTR_SEM_AVERAGING_TYPE                                                     0x00308021
#define CCRFMXLTE_ATTR_SEM_ALL_TRACES_ENABLED                                                 0x00308027
#define CCRFMXLTE_ATTR_SEM_NUMBER_OF_ANALYSIS_THREADS                                         0x0030801d
#define CCRFMXLTE_ATTR_SEM_RESULTS_TOTAL_AGGREGATED_POWER                                     0x00308028
#define CCRFMXLTE_ATTR_SEM_RESULTS_MEASUREMENT_STATUS                                         0x00308029
#define CCRFMXLTE_ATTR_SEM_RESULTS_SUBBLOCK_CENTER_FREQUENCY                                  0x0030804d
#define CCRFMXLTE_ATTR_SEM_RESULTS_SUBBLOCK_INTEGRATION_BANDWIDTH                             0x0030804e
#define CCRFMXLTE_ATTR_SEM_RESULTS_SUBBLOCK_POWER                                             0x0030804f
#define CCRFMXLTE_ATTR_SEM_RESULTS_COMPONENT_CARRIER_ABSOLUTE_INTEGRATED_POWER                0x0030802d
#define CCRFMXLTE_ATTR_SEM_RESULTS_COMPONENT_CARRIER_RELATIVE_INTEGRATED_POWER                0x0030802e
#define CCRFMXLTE_ATTR_SEM_RESULTS_COMPONENT_CARRIER_ABSOLUTE_PEAK_POWER                      0x0030802f
#define CCRFMXLTE_ATTR_SEM_RESULTS_COMPONENT_CARRIER_PEAK_FREQUENCY                           0x00308030
#define CCRFMXLTE_ATTR_SEM_RESULTS_LOWER_OFFSET_MEASUREMENT_STATUS                            0x0030803d
#define CCRFMXLTE_ATTR_SEM_RESULTS_LOWER_OFFSET_ABSOLUTE_INTEGRATED_POWER                     0x00308034
#define CCRFMXLTE_ATTR_SEM_RESULTS_LOWER_OFFSET_RELATIVE_INTEGRATED_POWER                     0x00308035
#define CCRFMXLTE_ATTR_SEM_RESULTS_LOWER_OFFSET_ABSOLUTE_PEAK_POWER                           0x00308036
#define CCRFMXLTE_ATTR_SEM_RESULTS_LOWER_OFFSET_RELATIVE_PEAK_POWER                           0x00308037
#define CCRFMXLTE_ATTR_SEM_RESULTS_LOWER_OFFSET_PEAK_FREQUENCY                                0x00308038
#define CCRFMXLTE_ATTR_SEM_RESULTS_LOWER_OFFSET_MARGIN                                        0x00308039
#define CCRFMXLTE_ATTR_SEM_RESULTS_LOWER_OFFSET_MARGIN_ABSOLUTE_POWER                         0x0030803a
#define CCRFMXLTE_ATTR_SEM_RESULTS_LOWER_OFFSET_MARGIN_RELATIVE_POWER                         0x0030803b
#define CCRFMXLTE_ATTR_SEM_RESULTS_LOWER_OFFSET_MARGIN_FREQUENCY                              0x0030803c
#define CCRFMXLTE_ATTR_SEM_RESULTS_UPPER_OFFSET_MEASUREMENT_STATUS                            0x0030804a
#define CCRFMXLTE_ATTR_SEM_RESULTS_UPPER_OFFSET_ABSOLUTE_INTEGRATED_POWER                     0x00308041
#define CCRFMXLTE_ATTR_SEM_RESULTS_UPPER_OFFSET_RELATIVE_INTEGRATED_POWER                     0x00308042
#define CCRFMXLTE_ATTR_SEM_RESULTS_UPPER_OFFSET_ABSOLUTE_PEAK_POWER                           0x00308043
#define CCRFMXLTE_ATTR_SEM_RESULTS_UPPER_OFFSET_RELATIVE_PEAK_POWER                           0x00308044
#define CCRFMXLTE_ATTR_SEM_RESULTS_UPPER_OFFSET_PEAK_FREQUENCY                                0x00308045
#define CCRFMXLTE_ATTR_SEM_RESULTS_UPPER_OFFSET_MARGIN                                        0x00308046
#define CCRFMXLTE_ATTR_SEM_RESULTS_UPPER_OFFSET_MARGIN_ABSOLUTE_POWER                         0x00308047
#define CCRFMXLTE_ATTR_SEM_RESULTS_UPPER_OFFSET_MARGIN_RELATIVE_POWER                         0x00308048
#define CCRFMXLTE_ATTR_SEM_RESULTS_UPPER_OFFSET_MARGIN_FREQUENCY                              0x00308049
#define CCRFMXLTE_ATTR_PVT_MEASUREMENT_ENABLED                                                0x00309000
#define CCRFMXLTE_ATTR_PVT_MEASUREMENT_METHOD                                                 0x00309002
#define CCRFMXLTE_ATTR_PVT_AVERAGING_ENABLED                                                  0x00309007
#define CCRFMXLTE_ATTR_PVT_AVERAGING_COUNT                                                    0x00309009
#define CCRFMXLTE_ATTR_PVT_AVERAGING_TYPE                                                     0x0030900a
#define CCRFMXLTE_ATTR_PVT_OFF_POWER_EXCLUSION_BEFORE                                         0x00309015
#define CCRFMXLTE_ATTR_PVT_OFF_POWER_EXCLUSION_AFTER                                          0x00309016
#define CCRFMXLTE_ATTR_PVT_ALL_TRACES_ENABLED                                                 0x0030900b
#define CCRFMXLTE_ATTR_PVT_NUMBER_OF_ANALYSIS_THREADS                                         0x0030900c
#define CCRFMXLTE_ATTR_PVT_RESULTS_MEASUREMENT_STATUS                                         0x0030900e
#define CCRFMXLTE_ATTR_PVT_RESULTS_MEAN_ABSOLUTE_OFF_POWER_BEFORE                             0x00309010
#define CCRFMXLTE_ATTR_PVT_RESULTS_MEAN_ABSOLUTE_OFF_POWER_AFTER                              0x00309011
#define CCRFMXLTE_ATTR_PVT_RESULTS_MEAN_ABSOLUTE_ON_POWER                                     0x00309012
#define CCRFMXLTE_ATTR_PVT_RESULTS_BURST_WIDTH                                                0x00309014
#define CCRFMXLTE_ATTR_LIMITED_CONFIGURATION_CHANGE                                           0x0030d003
#define CCRFMXLTE_ATTR_RESULT_FETCH_TIMEOUT                                                   0x0030c000
#define CCRFMXLTE_ATTR_CENTER_FREQUENCY                                                       0x00300001
#define CCRFMXLTE_ATTR_REFERENCE_LEVEL                                                        0x00300002
#define CCRFMXLTE_ATTR_EXTERNAL_ATTENUATION                                                   0x00300003
#define CCRFMXLTE_ATTR_TRIGGER_TYPE                                                           0x00300004
#define CCRFMXLTE_ATTR_DIGITAL_EDGE_TRIGGER_SOURCE                                            0x00300005
#define CCRFMXLTE_ATTR_DIGITAL_EDGE_TRIGGER_EDGE                                              0x00300006
#define CCRFMXLTE_ATTR_IQ_POWER_EDGE_TRIGGER_SOURCE                                           0x00300007
#define CCRFMXLTE_ATTR_IQ_POWER_EDGE_TRIGGER_LEVEL                                            0x00300008
#define CCRFMXLTE_ATTR_IQ_POWER_EDGE_TRIGGER_LEVEL_TYPE                                       0x00300fff
#define CCRFMXLTE_ATTR_IQ_POWER_EDGE_TRIGGER_SLOPE                                            0x00300009
#define CCRFMXLTE_ATTR_TRIGGER_DELAY                                                          0x0030000a
#define CCRFMXLTE_ATTR_TRIGGER_MINIMUM_QUIET_TIME_MODE                                        0x0030000b
#define CCRFMXLTE_ATTR_TRIGGER_MINIMUM_QUIET_TIME_DURATION                                    0x0030000c
#define CCRFMXLTE_ATTR_DUPLEX_SCHEME                                                          0x0030000d
#define CCRFMXLTE_ATTR_UPLINK_DOWNLINK_CONFIGURATION                                          0x0030000e
#define CCRFMXLTE_ATTR_LINK_DIRECTION                                                         0x00300029
#define CCRFMXLTE_ATTR_NUMBER_OF_SUBBLOCKS                                                    0x00300023
#define CCRFMXLTE_ATTR_SUBBLOCK_FREQUENCY_DEFINITION                                          0x00300024
#define CCRFMXLTE_ATTR_BAND                                                                   0x00300017
#define CCRFMXLTE_ATTR_COMPONENT_CARRIER_SPACING_TYPE                                         0x00300013
#define CCRFMXLTE_ATTR_COMPONENT_CARRIER_AT_CENTER_FREQUENCY                                  0x00300014
#define CCRFMXLTE_ATTR_NUMBER_OF_COMPONENT_CARRIERS                                           0x0030000f
#define CCRFMXLTE_ATTR_COMPONENT_CARRIER_BANDWIDTH                                            0x00300010
#define CCRFMXLTE_ATTR_COMPONENT_CARRIER_FREQUENCY                                            0x00300011
#define CCRFMXLTE_ATTR_CELL_ID                                                                0x00300012
#define CCRFMXLTE_ATTR_CYCLIC_PREFIX_MODE                                                     0x00300015
#define CCRFMXLTE_ATTR_AUTO_RESOURCE_BLOCK_DETECTION_ENABLED                                  0x00300026
#define CCRFMXLTE_ATTR_AUTO_DMRS_DETECTION_ENABLED                                            0x00300028
#define CCRFMXLTE_ATTR_UPLINK_GROUP_HOPPING_ENABLED                                           0x00300019
#define CCRFMXLTE_ATTR_UPLINK_SEQUENCE_HOPPING_ENABLED                                        0x0030001a
#define CCRFMXLTE_ATTR_PUSCH_N_DMRS_1                                                         0x0030001f
#define CCRFMXLTE_ATTR_PUSCH_DELTA_SEQUENCE_SHIFT                                             0x00300021
#define CCRFMXLTE_ATTR_PUSCH_MODULATION_TYPE                                                  0x0030001b
#define CCRFMXLTE_ATTR_PUSCH_NUMBER_OF_RESOURCE_BLOCK_CLUSTERS                                0x0030001c
#define CCRFMXLTE_ATTR_PUSCH_RESOURCE_BLOCK_OFFSET                                            0x0030001e
#define CCRFMXLTE_ATTR_PUSCH_NUMBER_OF_RESOURCE_BLOCKS                                        0x00300022
#define CCRFMXLTE_ATTR_PUSCH_N_DMRS_2                                                         0x00300020
#define CCRFMXLTE_ATTR_PUSCH_POWER                                                            0x00300027
#define CCRFMXLTE_ATTR_AUTO_LEVEL_INITIAL_REFERENCE_LEVEL                                     0x0030d000
#define CCRFMXLTE_ATTR_ACQUISITION_BANDWIDTH_OPTIMIZATION_ENABLED                             0x0030d001
#define CCRFMXLTE_ATTR_TRANSMITTER_ARCHITECTURE                                               0x0030d002
#define CCRFMXLTE_ATTR_DMRS_OCC_ENABLED                                                       0x00300051
#define CCRFMXLTE_ATTR_PUSCH_CYCLIC_SHIFT_FIELD                                               0x00300052
#define CCRFMXLTE_ATTR_SLOTPHASE_MEASUREMENT_ENABLED                                          0x0030a000
#define CCRFMXLTE_ATTR_SLOTPHASE_SYNCHRONIZATION_MODE                                         0x0030a006
#define CCRFMXLTE_ATTR_SLOTPHASE_MEASUREMENT_OFFSET                                           0x0030a002
#define CCRFMXLTE_ATTR_SLOTPHASE_MEASUREMENT_LENGTH                                           0x0030a003
#define CCRFMXLTE_ATTR_SLOTPHASE_EXCLUSION_PERIOD_ENABLED                                     0x0030a007
#define CCRFMXLTE_ATTR_SLOTPHASE_COMMON_CLOCK_SOURCE_ENABLED                                  0x0030a008
#define CCRFMXLTE_ATTR_SLOTPHASE_SPECTRUM_INVERTED                                            0x0030a009
#define CCRFMXLTE_ATTR_SLOTPHASE_ALL_TRACES_ENABLED                                           0x0030a00b
#define CCRFMXLTE_ATTR_SLOTPHASE_RESULTS_MAXIMUM_PHASE_DISCONTINUITY                          0x0030a014
#define CCRFMXLTE_ATTR_SLOTPOWER_MEASUREMENT_ENABLED                                          0x0030b000
#define CCRFMXLTE_ATTR_SLOTPOWER_MEASUREMENT_OFFSET                                           0x0030b002
#define CCRFMXLTE_ATTR_SLOTPOWER_MEASUREMENT_LENGTH                                           0x0030b003
#define CCRFMXLTE_ATTR_SLOTPOWER_COMMON_CLOCK_SOURCE_ENABLED                                  0x0030b005
#define CCRFMXLTE_ATTR_SLOTPOWER_SPECTRUM_INVERTED                                            0x0030b006
#define CCRFMXLTE_ATTR_SLOTPOWER_ALL_TRACES_ENABLED                                           0x0030b00a
#define CCRFMXLTE_ATTR_MODACC_RESULTS_DOWNLINK_DETECTED_CELL_ID                               0x00304053
#define CCRFMXLTE_ATTR_SPECIAL_SUBFRAME_CONFIGURATION                                         0x0030002a
#define CCRFMXLTE_ATTR_NUMBER_OF_DUT_ANTENNAS                                                 0x0030002b
#define CCRFMXLTE_ATTR_TRANSMIT_ANTENNA_TO_ANALYZE                                            0x0030002c
#define CCRFMXLTE_ATTR_SRS_ENABLED                                                            0x0030002d
#define CCRFMXLTE_ATTR_SRS_SUBFRAME_CONFIGURATION                                             0x0030002e
#define CCRFMXLTE_ATTR_SRS_C_SRS                                                              0x0030002f
#define CCRFMXLTE_ATTR_SRS_B_SRS                                                              0x00300030
#define CCRFMXLTE_ATTR_SRS_I_SRS                                                              0x00300031
#define CCRFMXLTE_ATTR_SRS_n_RRC                                                              0x00300032
#define CCRFMXLTE_ATTR_SRS_n_SRS_CS                                                           0x00300033
#define CCRFMXLTE_ATTR_SRS_b_HOP                                                              0x00300034
#define CCRFMXLTE_ATTR_SRS_k_TC                                                               0x00300035
#define CCRFMXLTE_ATTR_SRS_MAXIMUM_UpPTS_ENABLED                                              0x00300036
#define CCRFMXLTE_ATTR_SRS_SUBFRAME1_N_RA                                                     0x00300037
#define CCRFMXLTE_ATTR_SRS_SUBFRAME6_N_RA                                                     0x00300038
#define CCRFMXLTE_ATTR_SRS_POWER                                                              0x00300039
#define CCRFMXLTE_ATTR_DOWNLINK_AUTO_CELL_ID_DETECTION_ENABLED                                0x0030003c
#define CCRFMXLTE_ATTR_DOWNLINK_CHANNEL_CONFIGURATION_MODE                                    0x0030003d
#define CCRFMXLTE_ATTR_DOWNLINK_USER_DEFINED_CELL_SPECIFIC_RATIO                              0x0030003e
#define CCRFMXLTE_ATTR_PSS_POWER                                                              0x0030003f
#define CCRFMXLTE_ATTR_SSS_POWER                                                              0x00300040
#define CCRFMXLTE_ATTR_PBCH_POWER                                                             0x00300041
#define CCRFMXLTE_ATTR_PDCCH_POWER                                                            0x00300042
#define CCRFMXLTE_ATTR_DOWNLINK_NUMBER_OF_SUBFRAMES                                           0x00300043
#define CCRFMXLTE_ATTR_PCFICH_CFI                                                             0x00300044
#define CCRFMXLTE_ATTR_PCFICH_POWER                                                           0x00300045
#define CCRFMXLTE_ATTR_PHICH_RESOURCE                                                         0x00300046
#define CCRFMXLTE_ATTR_PHICH_DURATION                                                         0x00300047
#define CCRFMXLTE_ATTR_PHICH_POWER                                                            0x00300048
#define CCRFMXLTE_ATTR_NUMBER_OF_PDSCH_CHANNELS                                               0x00300049
#define CCRFMXLTE_ATTR_PDSCH_CW0_MODULATION_TYPE                                              0x0030004a
#define CCRFMXLTE_ATTR_PDSCH_RESOURCE_BLOCK_ALLOCATION                                        0x0030004b
#define CCRFMXLTE_ATTR_PDSCH_POWER                                                            0x0030004c
#define CCRFMXLTE_ATTR_DOWNLINK_TEST_MODEL                                                    0x0030004d
#define CCRFMXLTE_ATTR_MODACC_MULTICARRIER_FILTER_ENABLED                                     0x00304002
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MEAN_RMS_SRS_EVM                                        0x00304042
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MEAN_SRS_POWER                                          0x00304043
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PDSCH_MEAN_RMS_EVM                                      0x00304044
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PDSCH_MEAN_RMS_QPSK_EVM                                 0x00304045
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PDSCH_MEAN_RMS_16QAM_EVM                                0x00304046
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PDSCH_MEAN_RMS_64QAM_EVM                                0x00304047
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PDSCH_MEAN_RMS_256QAM_EVM                               0x00304048
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MEAN_RMS_CSRS_EVM                                       0x00304049
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MEAN_RMS_PSS_EVM                                        0x0030404a
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MEAN_RMS_SSS_EVM                                        0x0030404b
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MEAN_RMS_PBCH_EVM                                       0x0030404c
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MEAN_RMS_PCFICH_EVM                                     0x0030404d
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MEAN_RMS_PDCCH_EVM                                      0x0030404e
#define CCRFMXLTE_ATTR_MODACC_RESULTS_MEAN_RMS_PHICH_EVM                                      0x0030404f
#define CCRFMXLTE_ATTR_MODACC_RESULTS_DOWNLINK_OFDM_SYMBOL_TRANSMIT_POWER                     0x00304052
#define CCRFMXLTE_ATTR_ENODEB_CATEGORY                                                        0x00300050
#define CCRFMXLTE_ATTR_SEM_UPLINK_MASK_TYPE                                                   0x0030804c
#define CCRFMXLTE_ATTR_SEM_DOWNLINK_MASK_TYPE                                                 0x00308053
#define CCRFMXLTE_ATTR_SEM_DELTA_F_MAXIMUM                                                    0x00308054
#define CCRFMXLTE_ATTR_SEM_AGGREGATED_MAXIMUM_POWER                                           0x00308055
#define CCRFMXLTE_ATTR_MODACC_RESULTS_DOWNLINK_RS_TRANSMIT_POWER                              0x00304051
#define CCRFMXLTE_ATTR_ACP_AMPLITUDE_CORRECTION_TYPE                                          0x00301040
#define CCRFMXLTE_ATTR_CHP_AMPLITUDE_CORRECTION_TYPE                                          0x00303023
#define CCRFMXLTE_ATTR_OBW_AMPLITUDE_CORRECTION_TYPE                                          0x0030601b
#define CCRFMXLTE_ATTR_SEM_COMPONENT_CARRIER_MAXIMUM_OUTPUT_POWER                             0x00308056
#define CCRFMXLTE_ATTR_SEM_AMPLITUDE_CORRECTION_TYPE                                          0x00308057
#define CCRFMXLTE_ATTR_SEM_OFFSET_RELATIVE_LIMIT_START                                        0x0030801a
#define CCRFMXLTE_ATTR_SEM_OFFSET_RELATIVE_LIMIT_STOP                                         0x0030801b
#define CCRFMXLTE_ATTR_SEM_OFFSET_LIMIT_FAIL_MASK                                             0x0030800d
#define CCRFMXLTE_ATTR_AUTO_PDSCH_CHANNEL_DETECTION_ENABLED                                   0x00304054
#define CCRFMXLTE_ATTR_AUTO_CONTROL_CHANNEL_POWER_DETECTION_ENABLED                           0x00304055
#define CCRFMXLTE_ATTR_AUTO_PCFICH_CFI_DETECTION_ENABLED                                      0x00304056
#define CCRFMXLTE_ATTR_LAA_STARTING_SUBFRAME                                                  0x00304057
#define CCRFMXLTE_ATTR_LAA_NUMBER_OF_SUBFRAMES                                                0x00304058
#define CCRFMXLTE_ATTR_LAA_UPLINK_START_POSITION                                              0x00304059
#define CCRFMXLTE_ATTR_LAA_UPLINK_ENDING_SYMBOL                                               0x0030405a
#define CCRFMXLTE_ATTR_LAA_DOWNLINK_STARTING_SYMBOL                                           0x0030405b
#define CCRFMXLTE_ATTR_LAA_DOWNLINK_NUMBER_OF_ENDING_SYMBOLS                                  0x0030405c
#define CCRFMXLTE_ATTR_MI_CONFIGURATION                                                       0x00300053
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PDSCH_MEAN_RMS_1024QAM_EVM                              0x0030405d
#define CCRFMXLTE_ATTR_NCELL_ID                                                               0x0030405e
#define CCRFMXLTE_ATTR_NB_IOT_UPLINK_SUBCARRIER_SPACING                                       0x0030405f
#define CCRFMXLTE_ATTR_AUTO_NPUSCH_CHANNEL_DETECTION_ENABLED                                  0x00304060
#define CCRFMXLTE_ATTR_NPUSCH_FORMAT                                                          0x00304061
#define CCRFMXLTE_ATTR_NPUSCH_TONE_OFFSET                                                     0x00304062
#define CCRFMXLTE_ATTR_NPUSCH_NUMBER_OF_TONES                                                 0x00304063
#define CCRFMXLTE_ATTR_NPUSCH_MODULATION_TYPE                                                 0x00304064
#define CCRFMXLTE_ATTR_NPUSCH_DMRS_BASE_SEQUENCE_MODE                                         0x00304065
#define CCRFMXLTE_ATTR_NPUSCH_DMRS_BASE_SEQUENCE_INDEX                                        0x00304066
#define CCRFMXLTE_ATTR_NPUSCH_DMRS_CYCLIC_SHIFT                                               0x00304067
#define CCRFMXLTE_ATTR_NPUSCH_DMRS_GROUP_HOPPING_ENABLED                                      0x00304069
#define CCRFMXLTE_ATTR_NPUSCH_DMRS_DELTA_SEQUENCE_SHIFT                                       0x00304068
#define CCRFMXLTE_ATTR_EMTC_ANALYSIS_ENABLED                                                  0x00304070
#define CCRFMXLTE_ATTR_MODACC_IN_BAND_EMISSION_MASK_TYPE                                      0x00304071
#define CCRFMXLTE_ATTR_MODACC_RESULTS_NPUSCH_MEAN_RMS_DATA_EVM                                0x0030406a
#define CCRFMXLTE_ATTR_MODACC_RESULTS_NPUSCH_MAXIMUM_PEAK_DATA_EVM                            0x0030406b
#define CCRFMXLTE_ATTR_MODACC_RESULTS_NPUSCH_MEAN_RMS_DMRS_EVM                                0x0030406c
#define CCRFMXLTE_ATTR_MODACC_RESULTS_NPUSCH_MAXIMUM_PEAK_DMRS_EVM                            0x0030406d
#define CCRFMXLTE_ATTR_MODACC_RESULTS_NPUSCH_MEAN_DATA_POWER                                  0x0030406e
#define CCRFMXLTE_ATTR_MODACC_RESULTS_NPUSCH_MEAN_DMRS_POWER                                  0x0030406f
#define CCRFMXLTE_ATTR_ACP_CONFIGURABLE_NUMBER_OF_OFFSETS_ENABLED                             0x00301044
#define CCRFMXLTE_ATTR_ACP_EUTRA_OFFSET_DEFINITION                                            0x00301043
#define CCRFMXLTE_ATTR_ACP_NUMBER_OF_GSM_OFFSETS                                              0x00301042
#define CCRFMXLTE_ATTR_NPUSCH_STARTING_SLOT                                                   0x00304072
#define CCRFMXLTE_ATTR_SELECTED_PORTS                                                         0x00300ffd
#define CCRFMXLTE_ATTR_CENTER_FREQUENCY_FOR_LIMITS                                            0x0030d004
#define CCRFMXLTE_ATTR_REFERENCE_LEVEL_HEADROOM                                               0x00300ffc
#define CCRFMXLTE_ATTR_PSSCH_MODULATION_TYPE                                                  0x00300055
#define CCRFMXLTE_ATTR_PSSCH_RESOURCE_BLOCK_OFFSET                                            0x00300056
#define CCRFMXLTE_ATTR_PSSCH_NUMBER_OF_RESOURCE_BLOCKS                                        0x00300057
#define CCRFMXLTE_ATTR_PSSCH_POWER                                                            0x00300058
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PSSCH_MEAN_RMS_DATA_EVM                                 0x00304073
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PSSCH_MAXIMUM_PEAK_DATA_EVM                             0x00304074
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PSSCH_MEAN_RMS_DMRS_EVM                                 0x00304075
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PSSCH_MAXIMUM_PEAK_DMRS_EVM                             0x00304076
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PSSCH_MEAN_DATA_POWER                                   0x00304077
#define CCRFMXLTE_ATTR_MODACC_RESULTS_PSSCH_MEAN_DMRS_POWER                                   0x00304078
#define CCRFMXLTE_ATTR_SEM_SIDELINK_MASK_TYPE                                                 0x00308058

// Values for CCRFMXLTE_ATTR_TRIGGER_TYPE
#define CCRFMXLTE_VAL_TRIGGER_TYPE_NONE                                                              0
#define CCRFMXLTE_VAL_TRIGGER_TYPE_DIGITAL_EDGE                                                      1
#define CCRFMXLTE_VAL_TRIGGER_TYPE_IQ_POWER_EDGE                                                     2
#define CCRFMXLTE_VAL_TRIGGER_TYPE_SOFTWARE                                                          3

// Values for CCRFMXLTE_ATTR_DIGITAL_EDGE_TRIGGER_SOURCE
#define CCRFMXLTE_VAL_PFI0_STR                                                                       "PFI0"
#define CCRFMXLTE_VAL_PFI1_STR                                                                       "PFI1"
#define CCRFMXLTE_VAL_PXI_TRIG0_STR                                                                  "PXI_Trig0"
#define CCRFMXLTE_VAL_PXI_TRIG1_STR                                                                  "PXI_Trig1"
#define CCRFMXLTE_VAL_PXI_TRIG2_STR                                                                  "PXI_Trig2"
#define CCRFMXLTE_VAL_PXI_TRIG3_STR                                                                  "PXI_Trig3"
#define CCRFMXLTE_VAL_PXI_TRIG4_STR                                                                  "PXI_Trig4"
#define CCRFMXLTE_VAL_PXI_TRIG5_STR                                                                  "PXI_Trig5"
#define CCRFMXLTE_VAL_PXI_TRIG6_STR                                                                  "PXI_Trig6"
#define CCRFMXLTE_VAL_PXI_TRIG7_STR                                                                  "PXI_Trig7"
#define CCRFMXLTE_VAL_PXI_STAR_STR                                                                   "PXI_STAR"

// Values for CCRFMXLTE_ATTR_DIGITAL_EDGE_TRIGGER_EDGE
#define CCRFMXLTE_VAL_DIGITAL_EDGE_RISING_EDGE                                                       0
#define CCRFMXLTE_VAL_DIGITAL_EDGE_FALLING_EDGE                                                      1

// Values for CCRFMXLTE_ATTR_IQ_POWER_EDGE_TRIGGER_LEVEL_TYPE
#define CCRFMXLTE_VAL_IQ_POWER_EDGE_TRIGGER_LEVEL_TYPE_RELATIVE                                      0
#define CCRFMXLTE_VAL_IQ_POWER_EDGE_TRIGGER_LEVEL_TYPE_ABSOLUTE                                      1

// Values for CCRFMXLTE_ATTR_IQ_POWER_EDGE_TRIGGER_SLOPE
#define CCRFMXLTE_VAL_IQ_POWER_EDGE_RISING_SLOPE                                                     0
#define CCRFMXLTE_VAL_IQ_POWER_EDGE_FALLING_SLOPE                                                    1

// Values for CCRFMXLTE_ATTR_TRIGGER_MINIMUM_QUIET_TIME_MODE
#define CCRFMXLTE_VAL_TRIGGER_MINIMUM_QUIET_TIME_MODE_MANUAL                                         0
#define CCRFMXLTE_VAL_TRIGGER_MINIMUM_QUIET_TIME_MODE_AUTO                                           1

// Values for RFMXLTE_ATTR_DUPLEX_SCHEME
#define CCRFMXLTE_VAL_DUPLEX_SCHEME_FDD                                                              0
#define CCRFMXLTE_VAL_DUPLEX_SCHEME_TDD                                                              1
#define CCRFMXLTE_VAL_DUPLEX_SCHEME_LAA                                                              2

// Values for RFMXLTE_ATTR_UPLINK_DOWNLINK_CONFIGURATION
#define CCRFMXLTE_VAL_UPLINK_DOWNLINK_CONFIGURATION_0                                                0
#define CCRFMXLTE_VAL_UPLINK_DOWNLINK_CONFIGURATION_1                                                1
#define CCRFMXLTE_VAL_UPLINK_DOWNLINK_CONFIGURATION_2                                                2
#define CCRFMXLTE_VAL_UPLINK_DOWNLINK_CONFIGURATION_3                                                3
#define CCRFMXLTE_VAL_UPLINK_DOWNLINK_CONFIGURATION_4                                                4
#define CCRFMXLTE_VAL_UPLINK_DOWNLINK_CONFIGURATION_5                                                5
#define CCRFMXLTE_VAL_UPLINK_DOWNLINK_CONFIGURATION_6                                                6

// Values for RFMXLTE_ATTR_SUBBLOCK_FREQUENCY_DEFINITION
#define CCRFMXLTE_VAL_SUBBLOCK_FREQUENCY_DEFINITION_RELATIVE                                         0
#define CCRFMXLTE_VAL_SUBBLOCK_FREQUENCY_DEFINITION_ABSOLUTE                                         1

// Values for RFMXLTE_ATTR_COMPONENT_CARRIER_SPACING_TYPE
#define CCRFMXLTE_VAL_COMPONENT_CARRIER_SPACING_TYPE_NOMINAL                                         0
#define CCRFMXLTE_VAL_COMPONENT_CARRIER_SPACING_TYPE_MINIMUM                                         1
#define CCRFMXLTE_VAL_COMPONENT_CARRIER_SPACING_TYPE_USER                                            2

// Values for RFMXLTE_ATTR_CYCLIC_PREFIX_MODE
#define CCRFMXLTE_VAL_CYCLIC_PREFIX_MODE_NORMAL                                                      0
#define CCRFMXLTE_VAL_CYCLIC_PREFIX_MODE_EXTENDED                                                    1

// Values for RFMXLTE_ATTR_AUTO_RESOURCE_BLOCK_DETECTION_ENABLED
#define CCRFMXLTE_VAL_AUTO_RESOURCE_BLOCK_DETECTION_ENABLED_FALSE                                    0
#define CCRFMXLTE_VAL_AUTO_RESOURCE_BLOCK_DETECTION_ENABLED_TRUE                                     1

// Values for RFMXLTE_ATTR_AUTO_DMRS_DETECTION_ENABLED
#define CCRFMXLTE_VAL_AUTO_DMRS_DETECTION_ENABLED_FALSE                                              0
#define CCRFMXLTE_VAL_AUTO_DMRS_DETECTION_ENABLED_TRUE                                               1

// Values for RFMXLTE_ATTR_UPLINK_GROUP_HOPPING_ENABLED
#define CCRFMXLTE_VAL_UPLINK_GROUP_HOPPING_ENABLED_FALSE                                             0
#define CCRFMXLTE_VAL_UPLINK_GROUP_HOPPING_ENABLED_TRUE                                              1

// Values for RFMXLTE_ATTR_UPLINK_SEQUENCE_HOPPING_ENABLED
#define CCRFMXLTE_VAL_UPLINK_SEQUENCE_HOPPING_ENABLED_FALSE                                          0
#define CCRFMXLTE_VAL_UPLINK_SEQUENCE_HOPPING_ENABLED_TRUE                                           1

// Values for RFMXLTE_ATTR_PUSCH_MODULATION_TYPE
#define CCRFMXLTE_VAL_PUSCH_MODULATION_TYPE_QPSK                                                     0
#define CCRFMXLTE_VAL_PUSCH_MODULATION_TYPE_16_QAM                                                   1
#define CCRFMXLTE_VAL_PUSCH_MODULATION_TYPE_64_QAM                                                   2
#define CCRFMXLTE_VAL_PUSCH_MODULATION_TYPE_256_QAM                                                  3
#define CCRFMXLTE_VAL_PUSCH_MODULATION_TYPE_1024_QAM                                                 4

// Values for RFMXLTE_ATTR_MODACC_SYNCHRONIZATION_MODE
#define CCRFMXLTE_VAL_MODACC_SYNCHRONIZATION_MODE_FRAME                                              0
#define CCRFMXLTE_VAL_MODACC_SYNCHRONIZATION_MODE_SLOT                                               1
#define CCRFMXLTE_VAL_MODACC_SYNCHRONIZATION_MODE_MARKER                                             2

// Values for RFMXLTE_ATTR_MODACC_MULTICARRIER_FILTER_ENABLED
#define CCRFMXLTE_VAL_MODACC_MULTICARRIER_FILTER_ENABLED_TRUE                                        1
#define CCRFMXLTE_VAL_MODACC_MULTICARRIER_FILTER_ENABLED_FALSE                                       0

// Values for RFMXLTE_ATTR_MODACC_SPECTRUM_INVERTED
#define CCRFMXLTE_VAL_MODACC_SPECTRUM_INVERTED_FALSE                                                 0
#define CCRFMXLTE_VAL_MODACC_SPECTRUM_INVERTED_TRUE                                                  1

// Values for RFMXLTE_ATTR_MODACC_CHANNEL_ESTIMATION_TYPE
#define CCRFMXLTE_VAL_MODACC_CHANNEL_ESTIMATION_TYPE_REFERENCE                                       0
#define CCRFMXLTE_VAL_MODACC_CHANNEL_ESTIMATION_TYPE_REFERENCE_AND_DATA                              1

// Values for RFMXLTE_ATTR_MODACC_EVM_UNIT
#define CCRFMXLTE_VAL_MODACC_EVM_UNIT_PERCENTAGE                                                     0
#define CCRFMXLTE_VAL_MODACC_EVM_UNIT_DB                                                             1

// Values for RFMXLTE_ATTR_MODACC_FFT_WINDOW_TYPE
#define CCRFMXLTE_VAL_MODACC_FFT_WINDOW_TYPE_3GPP                                                    0
#define CCRFMXLTE_VAL_MODACC_FFT_WINDOW_TYPE_CUSTOM                                                  1

// Values for RFMXLTE_ATTR_MODACC_COMMON_CLOCK_SOURCE_ENABLED
#define CCRFMXLTE_VAL_MODACC_COMMON_CLOCK_SOURCE_ENABLED_FALSE                                       0
#define CCRFMXLTE_VAL_MODACC_COMMON_CLOCK_SOURCE_ENABLED_TRUE                                        1

// Values for RFMXLTE_ATTR_MODACC_EVM_WITH_EXCLUSION_PERIOD_ENABLED
#define CCRFMXLTE_VAL_MODACC_EVM_WITH_EXCLUSION_PERIOD_ENABLED_FALSE                                 0
#define CCRFMXLTE_VAL_MODACC_EVM_WITH_EXCLUSION_PERIOD_ENABLED_TRUE                                  1

// Values for RFMXLTE_ATTR_MODACC_SPECTRAL_FLATNESS_CONDITION
#define CCRFMXLTE_VAL_MODACC_SPECTRAL_FLATNESS_CONDITION_NORMAL                                      0
#define CCRFMXLTE_VAL_MODACC_SPECTRAL_FLATNESS_CONDITION_EXTREME                                     1

// Values for RFMXLTE_ATTR_MODACC_AVERAGING_ENABLED
#define CCRFMXLTE_VAL_MODACC_AVERAGING_ENABLED_FALSE                                                 0
#define CCRFMXLTE_VAL_MODACC_AVERAGING_ENABLED_TRUE                                                  1

// Values for RFMXLTE_ATTR_ACP_RBW_FILTER_AUTO_BANDWIDTH
#define CCRFMXLTE_VAL_ACP_RBW_FILTER_AUTO_BANDWIDTH_FALSE                                            0
#define CCRFMXLTE_VAL_ACP_RBW_FILTER_AUTO_BANDWIDTH_TRUE                                             1

// Values for RFMXLTE_ATTR_ACP_RBW_FILTER_TYPE
#define CCRFMXLTE_VAL_ACP_RBW_FILTER_TYPE_FFT_BASED                                                  0
#define CCRFMXLTE_VAL_ACP_RBW_FILTER_TYPE_GAUSSIAN                                                   1
#define CCRFMXLTE_VAL_ACP_RBW_FILTER_TYPE_FLAT                                                       2

// Values for RFMXLTE_ATTR_ACP_SWEEP_TIME_AUTO
#define CCRFMXLTE_VAL_ACP_SWEEP_TIME_AUTO_FALSE                                                      0
#define CCRFMXLTE_VAL_ACP_SWEEP_TIME_AUTO_TRUE                                                       1

// Values for RFMXLTE_ATTR_ACP_MEASUREMENT_METHOD
#define CCRFMXLTE_VAL_ACP_MEASUREMENT_METHOD_NORMAL                                                  0
#define CCRFMXLTE_VAL_ACP_MEASUREMENT_METHOD_DYNAMIC_RANGE                                           1
#define CCRFMXLTE_VAL_ACP_MEASUREMENT_METHOD_SEQUENTIAL_FFT                                          2

// Values for RFMXLTE_ATTR_ACP_NOISE_COMPENSATION_ENABLED
#define CCRFMXLTE_VAL_ACP_NOISE_COMPENSATION_ENABLED_FALSE                                           0
#define CCRFMXLTE_VAL_ACP_NOISE_COMPENSATION_ENABLED_TRUE                                            1

// Values for RFMXLTE_ATTR_ACP_AVERAGING_ENABLED
#define CCRFMXLTE_VAL_ACP_AVERAGING_ENABLED_FALSE                                                    0
#define CCRFMXLTE_VAL_ACP_AVERAGING_ENABLED_TRUE                                                     1

// Values for RFMXLTE_ATTR_ACP_AVERAGING_TYPE
#define CCRFMXLTE_VAL_ACP_AVERAGING_TYPE_RMS                                                         0
#define CCRFMXLTE_VAL_ACP_AVERAGING_TYPE_LOG                                                         1
#define CCRFMXLTE_VAL_ACP_AVERAGING_TYPE_SCALAR                                                      2
#define CCRFMXLTE_VAL_ACP_AVERAGING_TYPE_MAXIMUM                                                     3
#define CCRFMXLTE_VAL_ACP_AVERAGING_TYPE_MINIMUM                                                     4

// Values for RFMXLTE_ATTR_ACP_IF_OUTPUT_POWER_OFFSET_AUTO
#define CCRFMXLTE_VAL_ACP_IF_OUTPUT_POWER_OFFSET_AUTO_FALSE                                          0
#define CCRFMXLTE_VAL_ACP_IF_OUTPUT_POWER_OFFSET_AUTO_TRUE                                           1

// Values for RFMXLTE_ATTR_CHP_INTEGRATION_BANDWIDTH_TYPE
#define CCRFMXLTE_VAL_CHP_INTEGRATION_BANDWIDTH_TYPE_SIGNAL_BANDWIDTH                                0
#define CCRFMXLTE_VAL_CHP_INTEGRATION_BANDWIDTH_TYPE_CHANNEL_BANDWIDTH                               1

// Values for RFMXLTE_ATTR_CHP_RBW_FILTER_AUTO_BANDWIDTH
#define CCRFMXLTE_VAL_CHP_RBW_FILTER_AUTO_BANDWIDTH_FALSE                                            0
#define CCRFMXLTE_VAL_CHP_RBW_FILTER_AUTO_BANDWIDTH_TRUE                                             1

// Values for RFMXLTE_ATTR_CHP_RBW_FILTER_TYPE
#define CCRFMXLTE_VAL_CHP_RBW_FILTER_TYPE_FFT_BASED                                                  0
#define CCRFMXLTE_VAL_CHP_RBW_FILTER_TYPE_GAUSSIAN                                                   1
#define CCRFMXLTE_VAL_CHP_RBW_FILTER_TYPE_FLAT                                                       2

// Values for RFMXLTE_ATTR_CHP_SWEEP_TIME_AUTO
#define CCRFMXLTE_VAL_CHP_SWEEP_TIME_AUTO_FALSE                                                      0
#define CCRFMXLTE_VAL_CHP_SWEEP_TIME_AUTO_TRUE                                                       1

// Values for RFMXLTE_ATTR_CHP_AVERAGING_ENABLED
#define CCRFMXLTE_VAL_CHP_AVERAGING_ENABLED_FALSE                                                    0
#define CCRFMXLTE_VAL_CHP_AVERAGING_ENABLED_TRUE                                                     1

// Values for RFMXLTE_ATTR_CHP_AVERAGING_TYPE
#define CCRFMXLTE_VAL_CHP_AVERAGING_TYPE_RMS                                                         0
#define CCRFMXLTE_VAL_CHP_AVERAGING_TYPE_LOG                                                         1
#define CCRFMXLTE_VAL_CHP_AVERAGING_TYPE_SCALAR                                                      2
#define CCRFMXLTE_VAL_CHP_AVERAGING_TYPE_MAXIMUM                                                     3
#define CCRFMXLTE_VAL_CHP_AVERAGING_TYPE_MINIMUM                                                     4

// Values for RFMXLTE_ATTR_OBW_RBW_FILTER_AUTO_BANDWIDTH
#define CCRFMXLTE_VAL_OBW_RBW_FILTER_AUTO_BANDWIDTH_FALSE                                            0
#define CCRFMXLTE_VAL_OBW_RBW_FILTER_AUTO_BANDWIDTH_TRUE                                             1

// Values for RFMXLTE_ATTR_OBW_RBW_FILTER_TYPE
#define CCRFMXLTE_VAL_OBW_RBW_FILTER_TYPE_FFT_BASED                                                  0
#define CCRFMXLTE_VAL_OBW_RBW_FILTER_TYPE_GAUSSIAN                                                   1
#define CCRFMXLTE_VAL_OBW_RBW_FILTER_TYPE_FLAT                                                       2

// Values for RFMXLTE_ATTR_OBW_SWEEP_TIME_AUTO
#define CCRFMXLTE_VAL_OBW_SWEEP_TIME_AUTO_FALSE                                                      0
#define CCRFMXLTE_VAL_OBW_SWEEP_TIME_AUTO_TRUE                                                       1

// Values for RFMXLTE_ATTR_OBW_AVERAGING_ENABLED
#define CCRFMXLTE_VAL_OBW_AVERAGING_ENABLED_FALSE                                                    0
#define CCRFMXLTE_VAL_OBW_AVERAGING_ENABLED_TRUE                                                     1

// Values for RFMXLTE_ATTR_OBW_AVERAGING_TYPE
#define CCRFMXLTE_VAL_OBW_AVERAGING_TYPE_RMS                                                         0
#define CCRFMXLTE_VAL_OBW_AVERAGING_TYPE_LOG                                                         1
#define CCRFMXLTE_VAL_OBW_AVERAGING_TYPE_SCALAR                                                      2
#define CCRFMXLTE_VAL_OBW_AVERAGING_TYPE_MAXIMUM                                                     3
#define CCRFMXLTE_VAL_OBW_AVERAGING_TYPE_MINIMUM                                                     4

// Values for RFMXLTE_ATTR_SEM_OFFSET_SIDEBAND
#define CCRFMXLTE_VAL_SEM_OFFSET_SIDEBAND_NEGATIVE                                                   0
#define CCRFMXLTE_VAL_SEM_OFFSET_SIDEBAND_POSITIVE                                                   1
#define CCRFMXLTE_VAL_SEM_OFFSET_SIDEBAND_BOTH                                                       2

// Values for RFMXLTE_ATTR_SEM_OFFSET_RBW_FILTER_TYPE
#define CCRFMXLTE_VAL_SEM_OFFSET_RBW_FILTER_TYPE_FFT_BASED                                           0
#define CCRFMXLTE_VAL_SEM_OFFSET_RBW_FILTER_TYPE_GAUSSIAN                                            1
#define CCRFMXLTE_VAL_SEM_OFFSET_RBW_FILTER_TYPE_FLAT                                                2

// Values for RFMXLTE_ATTR_SEM_SWEEP_TIME_AUTO
#define CCRFMXLTE_VAL_SEM_SWEEP_TIME_AUTO_FALSE                                                      0
#define CCRFMXLTE_VAL_SEM_SWEEP_TIME_AUTO_TRUE                                                       1

// Values for RFMXLTE_ATTR_SEM_AVERAGING_ENABLED
#define CCRFMXLTE_VAL_SEM_AVERAGING_ENABLED_FALSE                                                    0
#define CCRFMXLTE_VAL_SEM_AVERAGING_ENABLED_TRUE                                                     1

// Values for RFMXLTE_ATTR_SEM_AVERAGING_TYPE
#define CCRFMXLTE_VAL_SEM_AVERAGING_TYPE_RMS                                                         0
#define CCRFMXLTE_VAL_SEM_AVERAGING_TYPE_LOG                                                         1
#define CCRFMXLTE_VAL_SEM_AVERAGING_TYPE_SCALAR                                                      2
#define CCRFMXLTE_VAL_SEM_AVERAGING_TYPE_MAXIMUM                                                     3
#define CCRFMXLTE_VAL_SEM_AVERAGING_TYPE_MINIMUM                                                     4

// Values for RFMXLTE_ATTR_SEM_RESULTS_MEASUREMENT_STATUS
#define CCRFMXLTE_VAL_SEM_MEASUREMENT_STATUS_FAIL                                                    0
#define CCRFMXLTE_VAL_SEM_MEASUREMENT_STATUS_PASS                                                    1

// Values for RFMXLTE_ATTR_DMRS_OCC_ENABLED
#define CCRFMXLTE_VAL_DMRS_OCC_ENABLED_FALSE                                                         0
#define CCRFMXLTE_VAL_DMRS_OCC_ENABLED_TRUE                                                          1

// Values for RFMXLTE_ATTR_SEM_RESULTS_LOWER_OFFSET_MEASUREMENT_STATUS
#define CCRFMXLTE_VAL_SEM_LOWER_OFFSET_MEASUREMENT_STATUS_FAIL                                       0
#define CCRFMXLTE_VAL_SEM_LOWER_OFFSET_MEASUREMENT_STATUS_PASS                                       1

// Values for RFMXLTE_ATTR_SEM_RESULTS_UPPER_OFFSET_MEASUREMENT_STATUS
#define CCRFMXLTE_VAL_SEM_UPPER_OFFSET_MEASUREMENT_STATUS_FAIL                                       0
#define CCRFMXLTE_VAL_SEM_UPPER_OFFSET_MEASUREMENT_STATUS_PASS                                       1

// Values for RFMXLTE_ATTR_PVT_MEASUREMENT_METHOD
#define CCRFMXLTE_VAL_PVT_MEASUREMENT_METHOD_NORMAL                                                  0
#define CCRFMXLTE_VAL_PVT_MEASUREMENT_METHOD_DYNAMIC_RANGE                                           1

// Values for RFMXLTE_ATTR_PVT_AVERAGING_ENABLED
#define CCRFMXLTE_VAL_PVT_AVERAGING_ENABLED_FALSE                                                    0
#define CCRFMXLTE_VAL_PVT_AVERAGING_ENABLED_TRUE                                                     1

// Values for RFMXLTE_ATTR_PVT_AVERAGING_TYPE
#define CCRFMXLTE_VAL_PVT_AVERAGING_TYPE_RMS                                                         0
#define CCRFMXLTE_VAL_PVT_AVERAGING_TYPE_LOG                                                         1

// Values for RFMXLTE_ATTR_PVT_RESULTS_MEASUREMENT_STATUS
#define CCRFMXLTE_VAL_PVT_RESULTS_MEASUREMENT_STATUS_FAIL                                            0
#define CCRFMXLTE_VAL_PVT_RESULTS_MEASUREMENT_STATUS_PASS                                            1

// Values for RFMXLTE_ATTR_ACQUISITION_BANDWIDTH_OPTIMIZATION_ENABLED
#define CCRFMXLTE_VAL_ACQUISITION_BANDWIDTH_OPTIMIZATION_ENABLED_FALSE                               0
#define CCRFMXLTE_VAL_ACQUISITION_BANDWIDTH_OPTIMIZATION_ENABLED_TRUE                                1

// Values for RFMXLTE_ATTR_TRANSMITTER_ARCHITECTURE
#define CCRFMXLTE_VAL_TRANSMITTER_ARCHITECTURE_LO_PER_COMPONENT_CARRIER                              0
#define CCRFMXLTE_VAL_TRANSMITTER_ARCHITECTURE_LO_PER_SUBBLOCK                                       1

// Values for RFMXLTE_ATTR_LIMITED_CONFIGURATION_CHANGE
#define CCRFMXLTE_VAL_LIMITED_CONFIGURATION_CHANGE_DISABLED                                          0
#define CCRFMXLTE_VAL_LIMITED_CONFIGURATION_CHANGE_NO_CHANGE                                         1
#define CCRFMXLTE_VAL_LIMITED_CONFIGURATION_CHANGE_FREQUENCY                                         2
#define CCRFMXLTE_VAL_LIMITED_CONFIGURATION_CHANGE_REFERENCE_LEVEL                                   3
#define CCRFMXLTE_VAL_LIMITED_CONFIGURATION_CHANGE_FREQUENCY_AND_REFERENCE_LEVEL                     4
#define CCRFMXLTE_VAL_LIMITED_CONFIGURATION_CHANGE_SELECTED_PORTS_FREQUENCY_AND_REFERENCE_LEVEL      5

// Values for Boolean
#define CCRFMXLTE_VAL_FALSE                                                                          0
#define CCRFMXLTE_VAL_TRUE                                                                           1

// Values for MeasurementTypes
#define CCRFMXLTE_VAL_ACP                                                                            1 << 0
#define CCRFMXLTE_VAL_CHP                                                                            1 << 1
#define CCRFMXLTE_VAL_MODACC                                                                         1 << 2
#define CCRFMXLTE_VAL_OBW                                                                            1 << 3
#define CCRFMXLTE_VAL_SEM                                                                            1 << 4
#define CCRFMXLTE_VAL_PVT                                                                            1 << 5
#define CCRFMXLTE_VAL_SLOTPHASE                                                                      1 << 6
#define CCRFMXLTE_VAL_SLOTPOWER                                                                      1 << 7

// Values for FrequencyReferenceSource
#define CCRFMXLTE_VAL_ONBOARD_CLOCK_STR                                                              "OnboardClock"
#define CCRFMXLTE_VAL_REF_IN_STR                                                                     "RefIn"
#define CCRFMXLTE_VAL_PXI_CLK_STR                                                                    "PXI_Clk"
#define CCRFMXLTE_VAL_CLK_IN_STR                                                                     "ClkIn"

// Values for RFAttenuationAuto
#define CCRFMXLTE_VAL_RF_ATTENUATION_AUTO_FALSE                                                      0
#define CCRFMXLTE_VAL_RF_ATTENUATION_AUTO_TRUE                                                       1

// Values for MechanicalAttenuationAuto
#define CCRFMXLTE_VAL_MECHANICAL_ATTENUATION_AUTO_FALSE                                              0
#define CCRFMXLTE_VAL_MECHANICAL_ATTENUATION_AUTO_TRUE                                               1

// Values for RFMXLTE_ATTR_LINK_DIRECTION
#define CCRFMXLTE_VAL_LINK_DIRECTION_DOWNLINK                                                        0
#define CCRFMXLTE_VAL_LINK_DIRECTION_UPLINK                                                          1
#define CCRFMXLTE_VAL_LINK_DIRECTION_SIDELINK                                                        2

// Values for RFMXLTE_ATTR_SLOTPHASE_SYNCHRONIZATION_MODE
#define CCRFMXLTE_VAL_SLOTPHASE_SYNCHRONIZATION_MODE_FRAME                                           0
#define CCRFMXLTE_VAL_SLOTPHASE_SYNCHRONIZATION_MODE_SLOT                                            1

// Values for RFMXLTE_ATTR_SLOTPHASE_EXCLUSION_PERIOD_ENABLED
#define CCRFMXLTE_VAL_SLOTPHASE_EXCLUSION_PERIOD_ENABLED_FALSE                                       0
#define CCRFMXLTE_VAL_SLOTPHASE_EXCLUSION_PERIOD_ENABLED_TRUE                                        1

// Values for RFMXLTE_ATTR_SLOTPHASE_COMMON_CLOCK_SOURCE_ENABLED
#define CCRFMXLTE_VAL_SLOTPHASE_COMMON_CLOCK_SOURCE_ENABLED_FALSE                                    0
#define CCRFMXLTE_VAL_SLOTPHASE_COMMON_CLOCK_SOURCE_ENABLED_TRUE                                     1

// Values for RFMXLTE_ATTR_SLOTPHASE_SPECTRUM_INVERTED
#define CCRFMXLTE_VAL_SLOTPHASE_SPECTRUM_INVERTED_FALSE                                              0
#define CCRFMXLTE_VAL_SLOTPHASE_SPECTRUM_INVERTED_TRUE                                               1

// Values for RFMXLTE_ATTR_SLOTPOWER_COMMON_CLOCK_SOURCE_ENABLED
#define CCRFMXLTE_VAL_SLOTPOWER_COMMON_CLOCK_SOURCE_ENABLED_FALSE                                    0
#define CCRFMXLTE_VAL_SLOTPOWER_COMMON_CLOCK_SOURCE_ENABLED_TRUE                                     1

// Values for RFMXLTE_ATTR_SLOTPOWER_SPECTRUM_INVERTED
#define CCRFMXLTE_VAL_SLOTPOWER_SPECTRUM_INVERTED_FALSE                                              0
#define CCRFMXLTE_VAL_SLOTPOWER_SPECTRUM_INVERTED_TRUE                                               1

// Values for RFMXLTE_ATTR_DOWNLINK_AUTO_CELL_ID_DETECTION_ENABLED
#define CCRFMXLTE_VAL_DOWNLINK_AUTO_CELL_ID_DETECTION_ENABLED_FALSE                                  0
#define CCRFMXLTE_VAL_DOWNLINK_AUTO_CELL_ID_DETECTION_ENABLED_TRUE                                   1

// Values for RFMXLTE_ATTR_DOWNLINK_CHANNEL_CONFIGURATION_MODE
#define CCRFMXLTE_VAL_DOWNLINK_CHANNEL_CONFIGURATION_MODE_USER_DEFINED                               1
#define CCRFMXLTE_VAL_DOWNLINK_CHANNEL_CONFIGURATION_MODE_TEST_MODEL                                 2

// Values for RFMXLTE_ATTR_DOWNLINK_USER_DEFINED_CELL_SPECIFIC_RATIO
#define CCRFMXLTE_VAL_DOWNLINK_USER_DEFINED_RATIO_P_B0                                               0
#define CCRFMXLTE_VAL_DOWNLINK_USER_DEFINED_RATIO_P_B1                                               1
#define CCRFMXLTE_VAL_DOWNLINK_USER_DEFINED_RATIO_P_B2                                               2
#define CCRFMXLTE_VAL_DOWNLINK_USER_DEFINED_RATIO_P_B3                                               3

// Values for RFMXLTE_ATTR_PHICH_RESOURCE
#define CCRFMXLTE_VAL_DOWNLINK_USER_DEFINED_PHICH_RESOURCE_ONE_SIXTH                                 0
#define CCRFMXLTE_VAL_DOWNLINK_USER_DEFINED_PHICH_RESOURCE_HALF                                      1
#define CCRFMXLTE_VAL_DOWNLINK_USER_DEFINED_PHICH_RESOURCE_ONE                                       2
#define CCRFMXLTE_VAL_DOWNLINK_USER_DEFINED_PHICH_RESOURCE_TWO                                       3

// Values for RFMXLTE_ATTR_PHICH_DURATION
#define CCRFMXLTE_VAL_DOWNLINK_USER_DEFINED_PHICH_DURATION_NORMAL                                    0

// Values for RFMXLTE_ATTR_PDSCH_CW0_MODULATION_TYPE
#define CCRFMXLTE_VAL_USER_DEFINED_PDSCH_CW0_MODULATION_TYPE_QPSK                                    0
#define CCRFMXLTE_VAL_USER_DEFINED_PDSCH_CW0_MODULATION_TYPE_QAM16                                   1
#define CCRFMXLTE_VAL_USER_DEFINED_PDSCH_CW0_MODULATION_TYPE_QAM64                                   2
#define CCRFMXLTE_VAL_USER_DEFINED_PDSCH_CW0_MODULATION_TYPE_QAM256                                  3
#define CCRFMXLTE_VAL_USER_DEFINED_PDSCH_CW0_MODULATION_TYPE_QAM1024                                 4

// Values for RFMXLTE_ATTR_DOWNLINK_TEST_MODEL
#define CCRFMXLTE_VAL_DOWNLINK_TEST_MODEL_TM1_1                                                      0
#define CCRFMXLTE_VAL_DOWNLINK_TEST_MODEL_TM1_2                                                      1
#define CCRFMXLTE_VAL_DOWNLINK_TEST_MODEL_TM2                                                        2
#define CCRFMXLTE_VAL_DOWNLINK_TEST_MODEL_TM2A                                                       3
#define CCRFMXLTE_VAL_DOWNLINK_TEST_MODEL_TM3_1                                                      4
#define CCRFMXLTE_VAL_DOWNLINK_TEST_MODEL_TM3_2                                                      5
#define CCRFMXLTE_VAL_DOWNLINK_TEST_MODEL_TM3_3                                                      6
#define CCRFMXLTE_VAL_DOWNLINK_TEST_MODEL_TM3_1A                                                     7

// Values for RFMXLTE_ATTR_ENODEB_CATEGORY
#define CCRFMXLTE_VAL_ENODEB_WIDE_AREA_BASE_STATION_CATEGORY_A                                       0
#define CCRFMXLTE_VAL_ENODEB_WIDE_AREA_BASE_STATION_CATEGORY_B_OPTION1                               1
#define CCRFMXLTE_VAL_ENODEB_WIDE_AREA_BASE_STATION_CATEGORY_B_OPTION2                               2
#define CCRFMXLTE_VAL_ENODEB_LOCAL_AREA_BASE_STATION                                                 3
#define CCRFMXLTE_VAL_ENODEB_HOME_BASE_STATION                                                       4
#define CCRFMXLTE_VAL_ENODEB_MEDIUM_RANGE_BASE_STATION                                               5

// Values for RFMXLTE_ATTR_SRS_ENABLED
#define CCRFMXLTE_VAL_SRS_ENABLED_FALSE                                                              0
#define CCRFMXLTE_VAL_SRS_ENABLED_TRUE                                                               1

// Values for RFMXLTE_ATTR_SRS_MAXIMUM_UpPTS_ENABLED
#define RCCRFMXLTE_VAL_SRS_MAXIMUM_UpPTS_ENABLED_FALSE                                               0
#define RCCRFMXLTE_VAL_SRS_MAXIMUM_UpPTS_ENABLED_TRUE                                                1

// Values for RFMXLTE_ATTR_SEM_UPLINK_MASK_TYPE
#define CCRFMXLTE_VAL_SEM_UPLINK_MASK_TYPE_GENERAL_NS01                                              0
#define CCRFMXLTE_VAL_SEM_UPLINK_MASK_TYPE_NS03_OR_NS11_OR_NS20_OR_NS21                              1
#define CCRFMXLTE_VAL_SEM_UPLINK_MASK_TYPE_NS04                                                      2
#define CCRFMXLTE_VAL_SEM_UPLINK_MASK_TYPE_NS06_OR_NS07                                              3
#define CCRFMXLTE_VAL_SEM_UPLINK_MASK_TYPE_CANS04                                                    4
#define CCRFMXLTE_VAL_SEM_UPLINK_MASK_TYPE_CUSTOM                                                    5
#define CCRFMXLTE_VAL_SEM_UPLINK_MASK_TYPE_GENERAL_CACLASSB                                          6
#define CCRFMXLTE_VAL_SEM_UPLINK_MASK_TYPE_CANCNS01                                                  7
#define CCRFMXLTE_VAL_SEM_UPLINK_MASK_TYPE_NS27                                                      8
#define CCRFMXLTE_VAL_SEM_UPLINK_MASK_TYPE_NS35                                                      9

// Values for RFMXLTE_ATTR_SEM_DOWNLINK_MASK_TYPE
#define CCRFMXLTE_VAL_SEM_DOWNLINK_MASK_TYPE_ENODEB_CATEGORY_BASED                                   0
#define CCRFMXLTE_VAL_SEM_DOWNLINK_MASK_TYPE_BAND46                                                  1
#define CCRFMXLTE_VAL_SEM_DOWNLINK_MASK_TYPE_CUSTOM                                                  5

// Values for RFMXLTE_ATTR_ACP_AMPLITUDE_CORRECTION_TYPE
#define CCRFMXLTE_VAL_ACP_AMPLITUDE_CORRECTION_TYPE_RF_CENTER_FREQUENCY                              0
#define CCRFMXLTE_VAL_ACP_AMPLITUDE_CORRECTION_TYPE_SPECTRUM_FREQUENCY_BIN                           1

// Values for RFMXLTE_ATTR_CHP_AMPLITUDE_CORRECTION_TYPE
#define CCRFMXLTE_VAL_CHP_AMPLITUDE_CORRECTION_TYPE_RF_CENTER_FREQUENCY                              0
#define CCRFMXLTE_VAL_CHP_AMPLITUDE_CORRECTION_TYPE_SPECTRUM_FREQUENCY_BIN                           1

// Values for RFMXLTE_ATTR_OBW_AMPLITUDE_CORRECTION_TYPE
#define CCRFMXLTE_VAL_OBW_AMPLITUDE_CORRECTION_TYPE_RF_CENTER_FREQUENCY                              0
#define CCRFMXLTE_VAL_OBW_AMPLITUDE_CORRECTION_TYPE_SPECTRUM_FREQUENCY_BIN                           1

// Values for RFMXLTE_ATTR_SEM_AMPLITUDE_CORRECTION_TYPE
#define CCRFMXLTE_VAL_SEM_AMPLITUDE_CORRECTION_TYPE_RF_CENTER_FREQUENCY                              0
#define CCRFMXLTE_VAL_SEM_AMPLITUDE_CORRECTION_TYPE_SPECTRUM_FREQUENCY_BIN                           1

// Values for RFMXLTE_ATTR_SEM_OFFSET_LIMIT_FAIL_MASK
#define CCRFMXLTE_VAL_SEM_OFFSET_LIMIT_FAIL_MASK_ABS_AND_REL                                         0
#define CCRFMXLTE_VAL_SEM_OFFSET_LIMIT_FAIL_MASK_ABS_OR_REL                                          1
#define CCRFMXLTE_VAL_SEM_OFFSET_LIMIT_FAIL_MASK_ABSOLUTE                                            2
#define CCRFMXLTE_VAL_SEM_OFFSET_LIMIT_FAIL_MASK_RELATIVE                                            3

// Values for RFMXLTE_ATTR_AUTO_PDSCH_CHANNEL_DETECTION_ENABLED
#define CCRFMXLTE_VAL_AUTO_PDSCH_CHANNEL_DETECTION_ENABLED_FALSE                                     0
#define CCRFMXLTE_VAL_AUTO_PDSCH_CHANNEL_DETECTION_ENABLED_TRUE                                      1

// Values for RFMXLTE_ATTR_AUTO_CONTROL_CHANNEL_POWER_DETECTION_ENABLED
#define CCRFMXLTE_VAL_AUTO_CONTROL_CHANNEL_POWER_DETECTION_ENABLED_FALSE                             0
#define CCRFMXLTE_VAL_AUTO_CONTROL_CHANNEL_POWER_DETECTION_ENABLED_TRUE                              1

// Values for RFMXLTE_ATTR_AUTO_PCFICH_CFI_DETECTION_ENABLED
#define CCRFMXLTE_VAL_AUTO_PCFICH_CFI_DETECTION_ENABLED_FALSE                                        0
#define CCRFMXLTE_VAL_AUTO_PCFICH_CFI_DETECTION_ENABLED_TRUE                                         1

// Values for RFMXLTE_ATTR_LAA_UPLINK_START_POSITION
#define CCRFMXLTE_VAL_LAA_UPLINK_START_POSITION_00                                                   0
#define CCRFMXLTE_VAL_LAA_UPLINK_START_POSITION_01                                                   1
#define CCRFMXLTE_VAL_LAA_UPLINK_START_POSITION_10                                                   2
#define CCRFMXLTE_VAL_LAA_UPLINK_START_POSITION_11                                                   3

// Values for RFMXLTE_ATTR_LAA_UPLINK_ENDING_SYMBOL
#define CCRFMXLTE_VAL_LAA_UPLINK_ENDING_SYMBOL_12                                                    12
#define CCRFMXLTE_VAL_LAA_UPLINK_ENDING_SYMBOL_13                                                    13

// Values for RFMXLTE_ATTR_LAA_DOWNLINK_STARTING_SYMBOL
#define CCRFMXLTE_VAL_LAA_DOWNLINK_STARTING_SYMBOL_0                                                 0
#define CCRFMXLTE_VAL_LAA_DOWNLINK_STARTING_SYMBOL_7                                                 7

// Values for RFMXLTE_ATTR_LAA_DOWNLINK_NUMBER_OF_ENDING_SYMBOLS
#define CCRFMXLTE_VAL_LAA_DOWNLINK_NUMBER_OF_ENDING_SYMBOLS_3                                        3
#define CCRFMXLTE_VAL_LAA_DOWNLINK_NUMBER_OF_ENDING_SYMBOLS_6                                        6
#define CCRFMXLTE_VAL_LAA_DOWNLINK_NUMBER_OF_ENDING_SYMBOLS_9                                        9
#define CCRFMXLTE_VAL_LAA_DOWNLINK_NUMBER_OF_ENDING_SYMBOLS_10                                       10
#define CCRFMXLTE_VAL_LAA_DOWNLINK_NUMBER_OF_ENDING_SYMBOLS_11                                       11
#define CCRFMXLTE_VAL_LAA_DOWNLINK_NUMBER_OF_ENDING_SYMBOLS_12                                       12
#define CCRFMXLTE_VAL_LAA_DOWNLINK_NUMBER_OF_ENDING_SYMBOLS_14                                       14

// Values for RFMXLTE_ATTR_NB_IOT_UPLINK_SUBCARRIER_SPACING
#define CCRFMXLTE_VAL_NB_IOT_UPLINK_SUBCARRIER_SPACING_15KHZ                                         0
#define CCRFMXLTE_VAL_NB_IOT_UPLINK_SUBCARRIER_SPACING_3_75KHZ                                       1

// Values for RFMXLTE_ATTR_AUTO_NPUSCH_CHANNEL_DETECTION_ENABLED
#define CCRFMXLTE_VAL_AUTO_NPUSCH_CHANNEL_DETECTION_ENABLED_FALSE                                    0
#define CCRFMXLTE_VAL_AUTO_NPUSCH_CHANNEL_DETECTION_ENABLED_TRUE                                     1

// Values for RFMXLTE_ATTR_NPUSCH_MODULATION_TYPE
#define CCRFMXLTE_VAL_NPUSCH_MODULATION_TYPE_BPSK                                                    0
#define CCRFMXLTE_VAL_NPUSCH_MODULATION_TYPE_QPSK                                                    1

// Values for RFMXLTE_ATTR_NPUSCH_DMRS_BASE_SEQUENCE_MODE
#define CCRFMXLTE_VAL_NPUSCH_DMRS_BASE_SEQUENCE_MODE_MANUAL                                          0
#define CCRFMXLTE_VAL_NPUSCH_DMRS_BASE_SEQUENCE_MODE_AUTO                                            1

// Values for RFMXLTE_ATTR_MI_CONFIGURATION
#define CCRFMXLTE_VAL_MI_CONFIGURATION_TEST_MODEL                                                    0
#define CCRFMXLTE_VAL_MI_CONFIGURATION_STANDARD                                                      1

// Values for RFMXLTE_ATTR_NPUSCH_DMRS_GROUP_HOPPING_ENABLED
#define CCRFMXLTE_VAL_NPUSCH_DMRS_GROUP_HOPPING_ENABLED_FALSE                                        0
#define CCRFMXLTE_VAL_NPUSCH_DMRS_GROUP_HOPPING_ENABLED_TRUE                                         1

// Values for RFMXLTE_ATTR_EMTC_ANALYSIS_ENABLED
#define CCRFMXLTE_VAL_EMTC_ANALYSIS_ENABLED_FALSE                                                    0
#define CCRFMXLTE_VAL_EMTC_ANALYSIS_ENABLED_TRUE                                                     1

// Values for RFMXLTE_ATTR_ACP_EUTRA_OFFSET_DEFINITION
#define CCRFMXLTE_VAL_ACP_EUTRA_OFFSET_DEFINITION_AUTO                                               0
#define CCRFMXLTE_VAL_ACP_EUTRA_OFFSET_DEFINITION_CLOSEST                                            1
#define CCRFMXLTE_VAL_ACP_EUTRA_OFFSET_DEFINITION_COMPOSITE                                          2

// Values for RFMXLTE_ATTR_ACP_CONFIGURABLE_NUMBER_OF_OFFSETS_ENABLED
#define CCRFMXLTE_VAL_ACP_CONFIGURABLE_NUMBER_OF_OFFSETS_ENABLED_FALSE                               0
#define CCRFMXLTE_VAL_ACP_CONFIGURABLE_NUMBER_OF_OFFSETS_ENABLED_TRUE                                1

// Values for RFMXLTE_ATTR_MODACC_IN_BAND_EMISSION_MASK_TYPE
#define CCRFMXLTE_VAL_MODACC_IN_BAND_EMISSION_MASK_TYPE_RELEASE_8_10                                 0
#define CCRFMXLTE_VAL_MODACC_IN_BAND_EMISSION_MASK_TYPE_RELEASE_11_ONWARDS                           1

// Values for RFMXLTE_ATTR_PSSCH_MODULATION_TYPE
#define CCRFMXLTE_VAL_PSSCH_MODULATION_TYPE_QPSK                                                     0
#define CCRFMXLTE_VAL_PSSCH_MODULATION_TYPE_QAM16                                                    1
#define CCRFMXLTE_VAL_PSSCH_MODULATION_TYPE_QAM64                                                    2

// Values for RFMXLTE_ATTR_SEM_SIDELINK_MASK_TYPE
#define CCRFMXLTE_VAL_SEM_SIDELINK_MASK_TYPE_GENERAL_NS01                                            0
#define CCRFMXLTE_VAL_SEM_SIDELINK_MASK_TYPE_NS33_OR_NS34                                            1
#define CCRFMXLTE_VAL_SEM_SIDELINK_MASK_TYPE_CUSTOM                                                  5

typedef struct{
    /* Specifies whether the RFmx driver computes the RF attenuation.*/
    ViInt32 nRFAttenuationAuto;
    /* Specifies the nominal attenuation setting for all attenuators before the first mixer in the RF signal chain 
     * when you set the RFAttenuationAuto parameter to CCRFMXLTE_VAL_RF_ATTENUATION_AUTO_FALSE. This value is expressed in dB. */
    ViReal64 dRFAttenuationValue;
}cfgRFCfgRFAttenuationAttribute,*pcfgRFCfgRFAttenuationAttribute;

typedef struct{
    /* Specifies the spacing between the two adjacent component carriers within a subblock.*/
    ViInt32 nComponentCarrierSpacingType;
    /* Specifies the index of the component carrier having its center at the user-configured center frequency. 
     * RFmxLTE uses this attribute along with the CC Spacing Type attribute to calculate the component carrier frequency.*/
    ViInt32 nComponentCarrierAtCenterFrequency;
}cfgComponentCarrierSpacingAttribute,*pcfgComponentCarrierSpacingAttribute;

typedef struct{
    /* Specifies the channel bandwidths of the signal being measured.*/
    ViReal64 dComponentCarrierBandwidth;
    /* Specifies the offsets of the component carrier from the subblock center frequency that you configure in the RFMXLTE_ATTR_CENTER_FREQUENCY attribute. 
     * This parameter is applicable only if you set the RFMXLTE_ATTR_COMPONENT_CARRIER_SPACING_TYPE attribute to CCRFMXLTE_VAL_COMPONENT_CARRIER_SPACING_TYPE_USER.*/
    ViReal64 dComponentCarrierFrequency;
    /* Specifies the physical layer cell identities.*/
    ViInt32 nCellID;
}cfgComponentCarrierAttribute,*pcfgComponentCarrierAttribute;

typedef struct{
    /* Specifies the duplexing technique of the signal being measured.*/
    ViInt32 nDuplexScheme;
    /* Specifies the configuration of the LTE frame structure in the time division duplex (TDD) mode. 
     * To configure the LTE frame, refer to table 4.2-2 of the 3GPP TS 36.211 specification.*/
    ViInt32 nUplinkDownlinkConfiguration;
}cfgDuplexSchemeAttribute,*pcfgDuplexSchemeAttribute;

typedef struct 
{
    ViInt32 nSubblockFrequencyDefinition;
    ViInt32 nComponentCarrierSpacingType;
    ViInt32 nComponentCarrierAtCenterFrequency;
    ViInt32 nNumberOfComponentCarriers;
    ViReal64 dCenterFrequency;
    ViInt32 nBand;
    ViReal64* pComponentCarrierBandwidth;    /*(Hz) */
    ViReal64* pComponentCarrierFrequency;    /*(Hz) */
    ViInt32* pDownlinkTestModelArray;
    ViChar pszSubblockString[MAX_SELECTOR_STRING];
}cfgSubblockInputAttribute,*pcfgSubblockInputAttribute;

typedef struct{
    /* Specifies the array of channel bandwidths of the signal being measured.*/
    //ViReal64* pComponentCarrierBandwidth;
    ViReal64 pComponentCarrierBandwidth[MAX_CARRIER_SIZE];
    /* Specifies the array of offsets of the component carrier from the subblock center frequency that you configure in the RFMXLTE_ATTR_CENTER_FREQUENCY attribute. 
     * This parameter is applicable only if you set the RFMXLTE_ATTR_COMPONENT_CARRIER_SPACING_TYPE attribute to CCRFMXLTE_VAL_COMPONENT_CARRIER_SPACING_TYPE_USER.*/
    //ViReal64* pComponentCarrierFrequency;
    ViReal64 pComponentCarrierFrequency[MAX_CARRIER_SIZE];
    /* Specifies the array of the physical layer cell identities.*/
    //ViInt32* pCellID;
    ViInt32 pCellID[MAX_CARRIER_SIZE];
    /* Specifies the number of elements in each array.*/
    ViInt32 nNumberOfElements;
}cfgComponentCarrierArrayAttribute,*pcfgComponentCarrierArrayAttribute;

typedef struct{
    /* Specifies the number of UTRA adjacent channel offsets to be configured at offset positions as defined in the 3GPP specification*/
    ViInt32 nNumberOfUTRAOffsets;
    /* Specifies the number of E-UTRA adjacent channel offsets to be configured at offset positions as defined in the 3GPP specification*/
    ViInt32 nNumberOfEUTRAOffsets;
}ACPCfgUTRAAndEUTRAOffsetsAttribute,*pACPCfgUTRAAndEUTRAOffsetsAttribute;

typedef struct{
    /* Specifies whether the measurement is performed from the frame or the slot boundary.*/
    ViInt32 nSynchronizationMode;
    /* Specifies the measurement offset, in slots, to skip from the synchronization boundary.*/
    ViInt32 nMeasurementOffset;
    /* Specifies the number of slots to be measured.*/
    ViInt32 nMeasurementLength;
}SynchronizationModeAndIntervalAttribute,*pSynchronizationModeAndIntervalAttribute;

typedef struct{
    SweepTimeAttribute SweepTime;
    AveragingAttribute Averaging;
    /* Specifies whether to enable compensation of the channel powers for the inherent noise floor of the signal analyzer. */
    ViInt32 nNoiseCompensationEnabled;
    /* Specifies the method for performing the ACP measurement. */
    ViInt32 nMeasurementMethod;
    /* Specifies whether the number of offsets is computed by measurement or configured by you. 
     * When the carrier bandwidth is 200 kHz or the RFMXLTE_ATTR_LINK_DIRECTION is CCRFMXLTE_VAL_LINK_DIRECTION_DOWNLINK, the default value is false. */
    ViInt32 nConfigurableNumberOfOffsetsEnabled;
    /* */
    ACPCfgUTRAAndEUTRAOffsetsAttribute UTRAAndEUTRAOffsets;
    /* Specifies the number of GSM adjacent channel offsets to be configured when the channel bandwidth is 200 kHz (NB-IOT), 
     * when you set the ACP Configurable Number of Offset Enabled attribute to true*/
    ViInt32 nNumberOfGSMOffsets;
    /* */
    RBWFilterAttribute RBWFilter;
}cfgLteACPAttribute,*pcfgLteACPAttribute;

typedef struct{
    AveragingAttribute Averaging;
    SynchronizationModeAndIntervalAttribute SynchronizationModeAndInterval;
    /* Specifies the units of the EVM results.*/
    ViInt32 nEVMUnit;
    /* Specifies the in-band emissions mask type to be used for measuring in-band emission margin (dB) 
     * and subblock in-Band emission margin (dB) results. 
     * Refer to section 6.5.2.3.5 of the 3GPP 36.521-1 specification for more information.*/
    ViInt32 nInBandEmissionMaskType;
}cfgLteModAccAttribute,*pcfgLteModAccAttribute;

//class DLLAPI CCRFmxLteAttribute
class CCRFmxLteAttribute
{
public:
    CCRFmxLteAttribute();
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
    /* Specifies the type of Carrier*/
    ViInt32 nCarrierType;
    /* Configures the nominal attenuation and the RFmx driver setting.*/
    cfgRFCfgRFAttenuationAttribute RFCfgRFAttenuation;
    /* Configures the duplexing technique of the signal being measured.*/
    cfgDuplexSchemeAttribute DuplexScheme;
    /* Specifies the link direction of the received signal.*/
    ViInt32 nLinkDirection;
    /* Configures the componentCarrierSpacingType and componentCarrierAtCenterFrequency parameters.*/
    cfgComponentCarrierSpacingAttribute ComponentCarrierSpacing;
    /* Configures the componentCarrierBandwidth, componentCarrierFrequency, and cellID of the component carrier.*/
    cfgComponentCarrierAttribute ComponentCarrier;
    /* Specifies the number of component carriers configured within a subblock.*/
    ViInt32 nNumberOfComponentCarriers;
    /* Specifies the number of offsets.*/
    ViInt32 nNumberOfOffsets;
    /* */
    cfgComponentCarrierArrayAttribute ComponentCarrierArray;
    /* Specifies the number of subblocks that are configured in the intra-band noncontiguous carrier aggregation.*/
    ViInt32 nNumberOfSubblocks;
    cfgSubblockInputAttribute* pSubblockInput;
    /* Specifies the E-UTRA operating frequency band of a subblock as defined in section 5.2 of the 3GPP TS 36.521 specification. 
     * Valid values are from 1 to 255, inclusive.*/
    ViInt32 nBand;
    /* Specifies the modulation scheme used in the PUSCH channel of the signal being measured.*/
    ViInt32 nModulationType;
    /* Specifies the EUTRA test model type when you set the RFMXLTE_ATTR_DOWNLINK_CHANNEL_CONFIGURATION_MODE attribute to 
     * CCRFMXLTE_VAL_DOWNLINK_CHANNEL_CONFIGURATION_MODE_TEST_MODEL. Refer to section 6.1.1 of the 3GPP 36.141 specification 
     * for more information regarding test model configurations.*/
    ViInt32 nDownlinkTestModel;
    ViInt32* pDownlinkTestModelArray;
    ViInt32 nNumberOfDownlinkTestModel;
    /* Specifies whether the values of the RFMXLTE_ATTR_PUSCH_MODULATION_TYPE, PUSCH Num Clusters, RFMXLTE_ATTR_PUSCH_RESOURCE_BLOCK_OFFSET, 
     * and RFMXLTE_ATTR_PUSCH_NUMBER_OF_RESOURCE_BLOCKS attributes are automatically detected by the measurement or 
     * if you specify the values of these attributes.*/
    ViInt32 nAutoResourceBlockDetectionEnabled;
    /* Specifies whether you need to configure the DMRS parameters.*/
    ViInt32 nAutoDMRSDetectionEnabled;
            
    cfgLteACPAttribute ACP;
    cfgLteModAccAttribute ModAcc;
    cfgOBWAttribute OBW;
    
    /*Specifies the trigger type*/
    RfmxInstrTrigger trigger; 
};


#include <map>
#include "string"
using namespace std;

/* Output Data*/
typedef struct{
    ViReal64 dAbsolutePower;
    ViReal64 dRelativePower;
}LteACPCarrierMeasurementAttritube,*pLteACPCarrierMeasurementAttritube;

typedef struct{
    /* Returns the array of powers measured over the integration bandwidths of the component carriers in a subblock.*/
    ViReal64* pAbsolutePower;
    /* Returns the array of component carrier powers relative to their subblock powers measured over the integration bandwidths of the component carriers in the subblock.*/
    ViReal64* pRelativePower;
    /* Returns the actual size of the array*/
    ViInt32 nActualArraySize;
}ACPComponentCarrierMeasurementArrayAttritube,*pACPComponentCarrierMeasurementArrayAttritube;

typedef struct{
    /* Returns the sum of powers of all the frequency bins over the integration bandwidth of the subblock.*/
    ViReal64 dSubblockPower;
    /* Returns the integration bandwidth used in calculating the power of the subblock.
     * Integration bandwidth is the span from left edge of the leftmost carrier to the right edge of the rightmost carrier within a subblock.*/
    ViReal64 dIntegrationBandwidth;
    /* Returns the absolute center frequency of the subblock. This value is the center of the subblock integration bandwidth.*/
    ViReal64 dFrequency;
}ACPSubblockMeasurementAttritube,*pACPSubblockMeasurementAttritube;

typedef struct{
    /* Returns the sum of powers of all the subblocks.*/
    ViReal64 dTotalAggregatedPower;
    /* Returns the power, integration bandwidth and center frequency of the subblock.*/
    ACPSubblockMeasurementAttritube* pSubblockMeasurement;
    /* Fetches the ACP component carrier measurement.*/
    LteACPCarrierMeasurementAttritube ComponentCarrierMeasurement;
    /* Fetches an array of the absolute and relative powers of the component carriers.*/
    ACPComponentCarrierMeasurementArrayAttritube ComponentCarrierMeasurementArray;
    /* Returns the absolute and relative powers measured in the offset channel.*/
    ACPOffsetMeasurementAttritube OffsetMeasurement;
    /* Returns the absolute and relative powers measured in the offset channel. */
    ACPOffsetMeasurementArrayAttritube OffsetMeasurementArray;
    ACPOffsetMeasurementArrayAttritube* pOffsetMeasurementArray;
    /* Fetches the spectrum used for adjacent channel power (ACP) measurement.*/
    DataResultAttribute Spectrum;
    /* Fetches the relative powers trace for adjacent channel power (ACP) measurement.*/
    DataResultAttribute* pRelativePowersTrace;
    /* Fetches the absolute powers trace for the adjacent channel power (ACP) measurement.*/
    DataResultAttribute* pAbsolutePowersTrace;
}LteACPResultAttribute,*pLteACPResultAttribute;

typedef struct{
    /* Returns the bandwidth that occupies 99 percentage of the total power of the signal within a carrier/subblock.*/
    ViReal64 dOccupiedBandwidth;
    /* Returns the power measured over the integration bandwidth of the carrier/subblock. */
    ViReal64 dAbsolutePower;
    /* Returns the start frequency of the subblock. */
    ViReal64 dStartFrequency;
    /* Returns the stop frequency of the subblock.*/
    ViReal64 dStopFrequency;
}LteMeasurementAttribute,*pLteMeasurementAttribute;

typedef struct{
    /* */
    LteMeasurementAttribute Measurement;
    LteMeasurementAttribute* pMeasurementSubbolck;
    /* Fetches the spectrum trace used for the OBW measurement.*/
    DataResultAttribute Spectrum;
}LteOBWResultAttribute,*pLteOBWResultAttribute;

typedef struct{
    /* Returns the mean value of the RMS EVMs calculated on all configured channels over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute.*/
    ViReal64 dMeanRMSCompositeEVM;
    /* Returns the symbol index where the ModAcc maximum peak composite EVM occurs.*/
    ViReal64 dMaximumPeakCompositeEVM;
    /* Returns the estimated carrier frequency offset averaged over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute.*/
    ViReal64 dMeanFrequencyError;
    /* Returns the symbol index where the ModAcc maximum peak composite EVM occurs.*/
    ViInt32 nPeakCompositeEVMSymbolIndex;
    /* Returns the subcarrier index where the ModAcc maximum peak composite EVM occurs.*/
    ViInt32 nPeakCompositeEVMSubcarrierIndex;
    /* Returns the slot index where the ModAcc maximum peak composite EVM occurs.*/
    ViInt32 nPeakCompositeEVMSlotIndex;
}ModAccCompositeEVMAttribute,*pModAccCompositeEVMAttribute;

typedef struct{
    /* Returns the mean value of the RMS EVMs calculated on all configured channels over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute.*/
    ViReal64* pMeanRMSCompositeEVM;
    /* Returns the symbol index where the ModAcc maximum peak composite EVM occurs.*/
    ViReal64* pMaximumPeakCompositeEVM;
    /* Returns the estimated carrier frequency offset averaged over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute.*/
    ViReal64* pMeanFrequencyError;
    /* Returns the symbol index where the ModAcc maximum peak composite EVM occurs.*/
    ViInt32* pPeakCompositeEVMSymbolIndex;
    /* Returns the subcarrier index where the ModAcc maximum peak composite EVM occurs.*/
    ViInt32* pPeakCompositeEVMSubcarrierIndex;
    /* Returns the slot index where the ModAcc maximum peak composite EVM occurs.*/
    ViInt32* pPeakCompositeEVMSlotIndex;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, 
     * and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}ModAccCompositeEVMArrayAttribute,*pModAccCompositeEVMArrayAttribute;

typedef struct{
    /* Returns the estimated I/Q origin offset averaged over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute..*/
    ViReal64 dMeanIQOriginOffset;
    /* Returns the estimated I/Q gain imbalance averaged over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute..*/
    ViReal64 dMeanIQGainImbalance;
    /* Returns the estimated quadrature error averaged over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute..*/
    ViReal64 dMeanIQQuadratureError;
}ModAccIQImpairmentsAttribute,*pModAccIQImpairmentsAttribute;

typedef struct{
    /* Returns the estimated I/Q origin offset averaged over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute..*/
    ViReal64* pMeanIQOriginOffset;
    /* Returns the estimated I/Q gain imbalance averaged over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute..*/
    ViReal64* pMeanIQGainImbalance;
    /* Returns the estimated quadrature error averaged over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute..*/
    ViReal64* pMeanIQQuadratureError;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, 
     * and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}ModAccIQImpairmentsArrayAttribute,*pModAccIQImpairmentsArrayAttribute;

typedef struct{
    /* Returns the mean value of RMS EVMs calculated on PDSCH data symbols over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute. */
    ViReal64 dMeanRMSEVM;
    /* Returns the mean value of RMS EVMs calculated on all QPSK modulated PDSCH resource blocks over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute.*/
    ViReal64 dMeanRMSQPSKEVM;
    /* Returns the mean value of RMS EVMs calculated on all 16QAM modulated PDSCH resource blocks over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute.*/
    ViReal64 dMeanRMS16QAMEVM;
    /* Returns the mean value of RMS EVMs calculated on all 64QAM modulated PDSCH resource blocks over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute.*/
    ViReal64 dMeanRMS64QAMEVM;
    /* Returns the mean value of RMS EVMs calculated on all 256QAM modulated PDSCH resource blocks over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute.*/
    ViReal64 dMeanRMS256QAMEVM;
}ModAccPDSCHEVMAttribute,*pModAccPDSCHEVMAttribute;

typedef struct{
    /* Returns the mean value of RMS EVMs calculated on PDSCH data symbols over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute. */
    ViReal64* pMeanRMSEVM;
    /* Returns the mean value of RMS EVMs calculated on all QPSK modulated PDSCH resource blocks over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute.*/
    ViReal64* pMeanRMSQPSKEVM;
    /* Returns the mean value of RMS EVMs calculated on all 16QAM modulated PDSCH resource blocks over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute.*/
    ViReal64* pMeanRMS16QAMEVM;
    /* Returns the mean value of RMS EVMs calculated on all 64QAM modulated PDSCH resource blocks over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute.*/
    ViReal64* pMeanRMS64QAMEVM;
    /* Returns the mean value of RMS EVMs calculated on all 256QAM modulated PDSCH resource blocks over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute.*/
    ViReal64* pMeanRMS256QAMEVM;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, 
     * and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}ModAccPDSCHEVMArrayAttribute,*pModAccPDSCHEVMArrayAttribute;

typedef struct{
    /* Returns the constellation trace.*/
    ComplexNumber* pConstellation;
    /* Returns the actual size of the array, if you pass NULL to all output array parameters, 
     * and set the arraySize parameter to 0.*/
    ViInt32 nActualArraySize;
}ModAccPDSCHConstellationAttribute, *pModAccPDSCHConstellationAttribute;

typedef struct{
    /* Returns the data constellation trace.*/
    ComplexNumber* pDataConstellation;
    /* Returns the actual size of dataConstellationI and dataConstellationQ array, if you pass NULL to all output array parameters, 
     * and set the dataConstellationArraySize parameter to 0.*/
    ViInt32 nDataConstellationActualArraySize;
    /* Returns the demodulation reference signal (DMRS) constellation trace.*/
    ComplexNumber* pDMRSConstellation;
    /* Returns the actual size of DMRSConstellationI and DMRSConstellationQ array, if you pass NULL to all output array parameters, 
     * and set the DMRSConstellationArraySize parameter to 0.*/
    ViInt32 nDMRSConstellationActualArraySize;
}ModAccConstellationTraceAttribute,*pModAccConstellationTraceAttribute;

typedef struct{
    ViReal64* pDataBuf;
    ViInt32 nActualArraySize;
}ArrayData,*pArrayData;

typedef struct{
    ModAccCompositeEVMAttribute CompositeEVM;
    ModAccCompositeEVMArrayAttribute CompositeEVMArray;
    
    ModAccIQImpairmentsAttribute IQImpairments;
    ModAccIQImpairmentsArrayAttribute IQImpairmentsArray;
    
    ModAccPDSCHEVMAttribute PDSCHEVM;
    ModAccPDSCHEVMArrayAttribute PDSCHEVMArray;
    
    /* Returns a mean value of the calculated RMS EVMs on all 1024QAM modulated PDSCH resource blocks over the slots specified 
     * by the RFMXLTE_ATTR_MODACC_MEASUREMENT_LENGTH attribute.*/
    ViReal64 dMeanRMS1024QAMEVM;
    ArrayData MeanRMS1024QAMEVMArray;
    
    ModAccPDSCHConstellationAttribute PDSCHQPSKConstellation;
    ModAccPDSCHConstellationAttribute* pPDSCHQPSKConstellation;
    ModAccPDSCHConstellationAttribute PDSCH16QAMConstellation;
    ModAccPDSCHConstellationAttribute PDSCH64QAMConstellation;
    ModAccPDSCHConstellationAttribute PDSCH256QAMConstellation;
    ModAccPDSCHConstellationAttribute PDSCH1024QAMConstellation;
    
    /* Returns the in-band emission margin.*/
    ViReal64 dInBandEmissionMargin;
    ArrayData InBandEmissionMarginArray;
    
    ModAccConstellationTraceAttribute PUSCHConstellationTrace;
    ModAccConstellationTraceAttribute* pPUSCHConstellationTrace;
    ModAccConstellationTraceAttribute PSSCHConstellationTrace;
    
    DataResultAttribute EVMPerSubcarrierTrace;
    DataResultAttribute* pEVMPerSubcarrierTrace;
}ModAccResultBaseAttribute,*pModAccResultBaseAttribute;

typedef struct{
    ModAccResultBaseAttribute Results;
    ModAccResultBaseAttribute* pSubblocksResults;
}LteModAccResultAttribute,*pLteModAccResultAttribute;

typedef struct{
    
    /* Returns the occupied bandwidth (OBW) measurement.*/
    LteACPResultAttribute ACPResult;
    LteModAccResultAttribute ModAccResult;
    LteOBWResultAttribute OBWResult;
    
}LteResultAttribute,*pLteResultAttribute;

class DLLAPI CCRfmxLteResults :public CCResultsArray<LteResultAttribute>
{
public:
    CCRfmxLteResults();
    ~CCRfmxLteResults();
   
    void RemoveAll();
private:
    inline void RemoveModAcc();
};


#endif	/* CCRFMXLTETYPEDEF_H */

