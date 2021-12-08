/* 
 * File:   CCRfmxNrTypeDef.h
 * Author: dongyuqing
 *
 * Created on 2021年1月25日, 上午9:55
 */
#pragma once

#ifndef CCRFMXNRTYPEDEF_H
#define	CCRFMXNRTYPEDEF_H

#include "CCResults.h"
#include "CCTesterDef.h"
#include "CCRfmxLteTypeDef.h"

#ifndef MAX_RESOURCE_BLOCK_CLUSTERS
#define MAX_RESOURCE_BLOCK_CLUSTERS           8
#endif

#ifndef MAX_COMPONENT_CARRIERS
#define MAX_COMPONENT_CARRIERS                8
#endif

#define CCRFMXNR_VAL_CARRIER_SIGNLE                                          1 << 0
#define CCRFMXNR_VAL_CARRIER_CONTIGUOUS                                      1 << 1
#define CCRFMXNR_VAL_CARRIER_NO_CONTIGUOUS                                   1 << 2

// Values for MeasurementTypes
#define CCRFMXNR_VAL_MODACC                                                                         1<<0
#define CCRFMXNR_VAL_SEM                                                                            1<<1
#define CCRFMXNR_VAL_ACP                                                                            1<<2
#define CCRFMXNR_VAL_CHP                                                                            1<<3
#define CCRFMXNR_VAL_OBW                                                                            1<<4
#define CCRFMXNR_VAL_PVT                                                                            1<<5

// Values for RFMXLTE_ATTR_DUPLEX_SCHEME
#define CCRFMXNR_VAL_DUPLEX_SCHEME_FDD                                                              0
#define CCRFMXNR_VAL_DUPLEX_SCHEME_TDD                                                              1
#define CCRFMXNR_VAL_DUPLEX_SCHEME_LAA                                                              2

// Values for RFAttenuationAuto
#define CCRFMXNR_VAL_RF_ATTENUATION_AUTO_FALSE                                                      0
#define CCRFMXNR_VAL_RF_ATTENUATION_AUTO_TRUE                                                       1

// Values for RFMXNR_ATTR_LINK_DIRECTION
#define CCRFMXNR_VAL_LINK_DIRECTION_DOWNLINK                                                        0
#define CCRFMXNR_VAL_LINK_DIRECTION_UPLINK                                                          1

// Values for RFMXNR_ATTR_FREQUENCY_RANGE
#define CCRFMXNR_VAL_FREQUENCY_RANGE_RANGE1                                                         0
#define CCRFMXNR_VAL_FREQUENCY_RANGE_RANGE2                                                         1

// Values for RFMXNR_ATTR_COMPONENT_CARRIER_SPACING_TYPE
#define CCRFMXNR_VAL_COMPONENT_CARRIER_SPACING_TYPE_NOMINAL                                         0
#define CCRFMXNR_VAL_COMPONENT_CARRIER_SPACING_TYPE_USER                                            2

// Values for RFMXNR_ATTR_DOWNLINK_TEST_MODEL
#define CCRFMXNR_VAL_DOWNLINK_TEST_MODEL_TM1_1                                                      0
#define CCRFMXNR_VAL_DOWNLINK_TEST_MODEL_TM1_2                                                      1
#define CCRFMXNR_VAL_DOWNLINK_TEST_MODEL_TM2                                                        2
#define CCRFMXNR_VAL_DOWNLINK_TEST_MODEL_TM2A                                                       3
#define CCRFMXNR_VAL_DOWNLINK_TEST_MODEL_TM3_1                                                      4
#define CCRFMXNR_VAL_DOWNLINK_TEST_MODEL_TM3_1A                                                     5
#define CCRFMXNR_VAL_DOWNLINK_TEST_MODEL_TM3_2                                                      6
#define CCRFMXNR_VAL_DOWNLINK_TEST_MODEL_TM3_3                                                      7

// Values for RFMXNR_ATTR_DOWNLINK_TEST_MODEL_DUPLEX_SCHEME
#define CCRFMXNR_VAL_DOWNLINK_TEST_MODEL_DUPLEX_SCHEME_FDD                                          0
#define CCRFMXNR_VAL_DOWNLINK_TEST_MODEL_DUPLEX_SCHEME_TDD                                          1

// Values for RFMXNR_ATTR_AUTO_RESOURCE_BLOCK_DETECTION_ENABLED
#define CCRFMXNR_VAL_AUTO_RESOURCE_BLOCK_DETECTION_ENABLED_FALSE                                    0
#define CCRFMXNR_VAL_AUTO_RESOURCE_BLOCK_DETECTION_ENABLED_TRUE                                     1

// Values for RFMXNR_ATTR_AUTO_INCREMENT_CELL_ID_ENABLED
#define CCRFMXNR_VAL_AUTO_INCREMENT_CELL_ID_ENABLED_FALSE                                           0
#define CCRFMXNR_VAL_AUTO_INCREMENT_CELL_ID_ENABLED_TRUE                                            1

// Values for RFMXNR_ATTR_PUSCH_TRANSFORM_PRECODING_ENABLED
#define CCRFMXNR_VAL_PUSCH_TRANSFORM_PRECODING_ENABLED_FALSE                                        0
#define CCRFMXNR_VAL_PUSCH_TRANSFORM_PRECODING_ENABLED_TRUE                                         1

// Values for RFMXNR_ATTR_PUSCH_MODULATION_TYPE
#define CCRFMXNR_VAL_PUSCH_MODULATION_TYPE_PI_BY_2_BPSK                                             0
#define CCRFMXNR_VAL_PUSCH_MODULATION_TYPE_QPSK                                                     1
#define CCRFMXNR_VAL_PUSCH_MODULATION_TYPE_QAM16                                                    2
#define CCRFMXNR_VAL_PUSCH_MODULATION_TYPE_QAM64                                                    3
#define CCRFMXNR_VAL_PUSCH_MODULATION_TYPE_QAM256                                                   4

// Values for RFMXNR_ATTR_PUSCH_DMRS_POWER_MODE
#define CCRFMXNR_VAL_PUSCH_DMRS_POWER_MODE_CDM_GROUPS                                               0
#define CCRFMXNR_VAL_PUSCH_DMRS_POWER_MODE_USER_DEFINED                                             1

// Values for RFMXNR_ATTR_PUSCH_DMRS_CONFIGURATION_TYPE
#define CCRFMXNR_VAL_PUSCH_DMRS_CONFIGURATION_TYPE_TYPE1                                            0
#define CCRFMXNR_VAL_PUSCH_DMRS_CONFIGURATION_TYPE_TYPE2                                            1

// Values for RFMXNR_ATTR_PUSCH_MAPPING_TYPE
#define RFMXNR_VAL_PUSCH_MAPPING_TYPE_TYPE_A                                                      0
#define CCRFMXNR_VAL_PUSCH_MAPPING_TYPE_TYPE_B                                                      1

// Values for RFMXNR_ATTR_PUSCH_DMRS_DURATION
#define CCRFMXNR_VAL_PUSCH_DMRS_DURATION_SINGLE_SYMBOL                                              1
#define CCRFMXNR_VAL_PUSCH_DMRS_DURATION_DOUBLE_SYMBOL                                              2

// Values for RFMXNR_ATTR_ACP_AVERAGING_ENABLED
#define CCRFMXNR_VAL_ACP_AVERAGING_ENABLED_FALSE                                                    0
#define CCRFMXNR_VAL_ACP_AVERAGING_ENABLED_TRUE                                                     1

// Values for RFMXNR_ATTR_ACP_AVERAGING_TYPE
#define CCRFMXNR_VAL_ACP_AVERAGING_TYPE_RMS                                                         0
#define CCRFMXNR_VAL_ACP_AVERAGING_TYPE_LOG                                                         1
#define CCRFMXNR_VAL_ACP_AVERAGING_TYPE_SCALAR                                                      2
#define CCRFMXNR_VAL_ACP_AVERAGING_TYPE_MAXIMUM                                                     3
#define CCRFMXNR_VAL_ACP_AVERAGING_TYPE_MINIMUM                                                     4

// Values for RFMXNR_ATTR_ACP_SWEEP_TIME_AUTO
#define CCRFMXNR_VAL_ACP_SWEEP_TIME_AUTO_FALSE                                                      0
#define CCRFMXNR_VAL_ACP_SWEEP_TIME_AUTO_TRUE                                                       1

// Values for RFMXNR_ATTR_ACP_MEASUREMENT_METHOD
#define CCRFMXNR_VAL_ACP_MEASUREMENT_METHOD_NORMAL                                                  0
#define CCRFMXNR_VAL_ACP_MEASUREMENT_METHOD_DYNAMIC_RANGE                                           1
#define CCRFMXNR_VAL_ACP_MEASUREMENT_METHOD_SEQUENTIAL_FFT                                          2

// Values for RFMXNR_ATTR_ACP_NOISE_COMPENSATION_ENABLED
#define CCRFMXNR_VAL_ACP_NOISE_COMPENSATION_ENABLED_FALSE                                           0
#define CCRFMXNR_VAL_ACP_NOISE_COMPENSATION_ENABLED_TRUE                                            1

// Values for RFMXNR_ATTR_OBW_AVERAGING_ENABLED
#define CCRFMXNR_VAL_OBW_AVERAGING_ENABLED_FALSE                                                    0
#define CCRFMXNR_VAL_OBW_AVERAGING_ENABLED_TRUE                                                     1

// Values for RFMXNR_ATTR_OBW_AVERAGING_TYPE
#define CCRFMXNR_VAL_OBW_AVERAGING_TYPE_RMS                                                         0
#define CCRFMXNR_VAL_OBW_AVERAGING_TYPE_LOG                                                         1
#define CCRFMXNR_VAL_OBW_AVERAGING_TYPE_SCALAR                                                      2
#define CCRFMXNR_VAL_OBW_AVERAGING_TYPE_MAXIMUM                                                     3
#define CCRFMXNR_VAL_OBW_AVERAGING_TYPE_MINIMUM                                                     4

// Values for RFMXNR_ATTR_OBW_SWEEP_TIME_AUTO
#define CCRFMXNR_VAL_OBW_SWEEP_TIME_AUTO_FALSE                                                      0
#define CCRFMXNR_VAL_OBW_SWEEP_TIME_AUTO_TRUE                                                       1

// Values for RFMXNR_ATTR_MODACC_AVERAGING_ENABLED
#define CCRFMXNR_VAL_MODACC_AVERAGING_ENABLED_FALSE                                                 0
#define CCRFMXNR_VAL_MODACC_AVERAGING_ENABLED_TRUE                                                  1

// Values for RFMXNR_ATTR_MODACC_MEASUREMENT_LENGTH_UNIT
#define CCRFMXNR_VAL_MODACC_MEASUREMENT_LENGTH_UNIT_SLOT                                            1
#define CCRFMXNR_VAL_MODACC_MEASUREMENT_LENGTH_UNIT_SUBFRAME                                        3
#define CCRFMXNR_VAL_MODACC_MEASUREMENT_LENGTH_UNIT_TIME                                            6

// Values for RFMXNR_ATTR_MODACC_SYNCHRONIZATION_MODE
#define CCRFMXNR_VAL_MODACC_SYNCHRONIZATION_MODE_SLOT                                               1
#define CCRFMXNR_VAL_MODACC_SYNCHRONIZATION_MODE_FRAME                                              5

typedef struct{
    /* Specifies the method for performing the ACP measurement. */
    ViInt32 nMeasurementMethod;
    /* Specifies whether to enable compensation of the channel powers for the inherent noise floor of the signal analyzer. */
    ViInt32 nNoiseCompensationEnabled;
    
    SweepTimeAttribute SweepTime;
    AveragingAttribute Averaging;
}cfgNrACPAttribute,*pcfgNrACPAttribute;

typedef struct{
    ViInt32 nPUSCHTransformPrecodingEnabled;
    ViInt32 nPUSCHModulationType;
    ViChar* pPUSCHSlotAllocation;
    ViChar* pPUSCHSymbolAllocation;
    ViInt32 nPUSCHNumberOfResourceBlockClusters;
    ViInt32 nPUSCHDMRSPowerMode;
    ViInt32 nPUSCHDMRSConfigurationType;
    ViInt32 nPUSCHMappingType;
    ViInt32 nPUSCHDMRSTypeAPosition;
    ViInt32 nPUSCHDMRSDuration;
    ViInt32 nPUSCHDMRSAdditionalPositions;
    
    ViReal64 dwPUSCHDMRSPower;
    ViInt32 nPUSCHResourceBlockOffset[MAX_RESOURCE_BLOCK_CLUSTERS];
    ViInt32 PUSCHNumberOfResourceBlocks[MAX_RESOURCE_BLOCK_CLUSTERS];
//    ViInt32 nPUSCHResourceBlockOffset[MAX_RESOURCE_BLOCK_CLUSTERS];
//    ViInt32 nPUSCHResourceBlockOffset[MAX_RESOURCE_BLOCK_CLUSTERS];
}cfgPUSCHAttribute,*pcfgPUSCHAttribute;

typedef struct{
    ViInt32 nMeasurementLengthUnit;
    ViReal64 dwMeasurementOffset;
    ViReal64 dwMeasurementLength;
}MeasurementAttribute,*pMeasurementAttribute;

typedef struct{
    AveragingAttribute Averaging;
    SynchronizationModeAndIntervalAttribute SynchronizationModeAndInterval;
    MeasurementAttribute Measurement;
    /* Specifies the units of the EVM results.*/
    ViInt32 nEVMUnit;
    
}cfgNrModAccAttribute,*pcfgNrModAccAttribute;

//class DLLAPI CCRFmxNrAttribute
class CCRFmxNrAttribute
{
public:
    CCRFmxNrAttribute();
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
    /* Specifies the link direction of the received signal.*/
    ViInt32 nLinkDirection;
    ViInt32 nFreqRange;
    ViInt32 nSpacingType;
    ViInt32 nCarrierAtCenterFrequency;
    
    ViReal64 dwBandWidth;
    ViReal64 dwSubcarrierSpacing;
    ViReal64 dwChannelRaster;
    
    ViInt32 nNumberOfComponentCarriers;
    cfgComponentCarrierArrayAttribute ComponentCarrierArray;
    
    ViInt32 nDownlinkTestModel;
    ViInt32 nDownlinkTestModelDuplexScheme;
    
    ViInt32 nCellID;
    ViInt32 pCellID[MAX_COMPONENT_CARRIERS];
    ViInt32 nBand;
    ViInt32 nAutoResourceBlockDetectionEnabled;
    ViInt32 nAutoIncrementCellIDEnabled;
    
    cfgPUSCHAttribute PUSCHAttr;
    
    cfgNrACPAttribute ACP;
    cfgOBWAttribute OBW;
    cfgNrModAccAttribute ModAcc;
    /*Specifies the trigger type*/
    RfmxInstrTrigger trigger; 
};

#include <map>
#include "string"
using namespace std;

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
    /* */
    ViReal64 dwAbsolutePower;
    ViReal64 dwRelativePower;
}NrACPResultAttribute,*pNrACPResultAttribute;

typedef struct{
    ViReal64 dInit;
    ViReal64 dIncrement;
    ViReal32* pSpectralFlatness;
    ViReal32* pSpectralFlatnessLowerMask;
    ViReal32* pSpectralFlatnessUpperMask;
    ViInt32 nActualArraySize;
}SpectralFlatnessTraceAttribute,*pSpectralFlatnessTraceAttribute;

typedef struct{
    ModAccCompositeEVMAttribute CompositeEVM;
    ViReal64 dwComponentCarrierFrequencyErrorMean;
    
    ModAccIQImpairmentsAttribute IQImpairments;
    
    ViReal64 dwPDSCHRMSEVMMean;
    ModAccPDSCHConstellationAttribute PDSCHQPSKConstellation;
    ModAccPDSCHConstellationAttribute PDSCH16QAMConstellation;
    ModAccPDSCHConstellationAttribute PDSCH64QAMConstellation;
    ModAccPDSCHConstellationAttribute PDSCH256QAMConstellation;
    ModAccPDSCHConstellationAttribute PDSCH1024QAMConstellation;
    
    /* Returns the in-band emission margin.*/
    ViReal64 dInBandEmissionMargin;

    DataResultAttribute EVMPerSubcarrierTrace;
    DataResultAttribute EVMPerSymbolMeanTrace;
    
    ModAccPDSCHConstellationAttribute PUSCHDataConstellationTrace;
    ModAccPDSCHConstellationAttribute PUSCHDMRSConstellationTrace;
    SpectralFlatnessTraceAttribute SpectralFlatnessTrace;
}NrModAccBaseResultAttribute,*pNrModAccBaseResultAttribute;

typedef struct{
    ModAccCompositeEVMAttribute* CompositeEVM;
    ViReal64* dwComponentCarrierFrequencyErrorMean;
    
    ModAccIQImpairmentsAttribute* IQImpairments;
    
    ViReal64* dwPDSCHRMSEVMMean;
    ModAccPDSCHConstellationAttribute* PDSCHQPSKConstellation;
    ModAccPDSCHConstellationAttribute* PDSCH16QAMConstellation;
    ModAccPDSCHConstellationAttribute* PDSCH64QAMConstellation;
    ModAccPDSCHConstellationAttribute* PDSCH256QAMConstellation;
    ModAccPDSCHConstellationAttribute* PDSCH1024QAMConstellation;
    
    /* Returns the in-band emission margin.*/
    ViReal64* dInBandEmissionMargin;

    DataResultAttribute* EVMPerSubcarrierTrace;
    DataResultAttribute* EVMPerSymbolMeanTrace;
    
    ModAccPDSCHConstellationAttribute* PUSCHDataConstellationTrace;
    ModAccPDSCHConstellationAttribute* PUSCHDMRSConstellationTrace;
    SpectralFlatnessTraceAttribute SpectralFlatnessTrace;
}NrModAccBaseResultAttributeArray,*pNrModAccBaseResultAttributeArray;

typedef struct{
    NrModAccBaseResultAttribute SingleCarrier;
    NrModAccBaseResultAttributeArray MultiCarrier;
}NrModAccResultAttribute,*pNrModAccResultAttribute;

typedef struct{
    NrACPResultAttribute ACPResult;
    NrModAccResultAttribute ModAccResult;
    LteOBWResultAttribute OBWResult;
}NrResultAttribute, *pNrResultAttribute;

class DLLAPI CCRfmxNrResults:public CCResultsArray<NrResultAttribute>
{
public:
    CCRfmxNrResults();
    ~CCRfmxNrResults();
    
    void RemoveAll();
    
};


#endif	/* CCRFMXNRTYPEDEF_H */

