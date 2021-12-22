/* 
 * File:   CBBAPI.cpp
 * Author: dongyuqing
 * 
 * Created on 2020年11月4日, 上午11:33
 */
#include "LogFile.h"
#include "Excel.h"
#include "CCS08F.h"
#include "UserAPI.h" 
#include <fstream>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>
#include "Globle_Var.h"
#include "UserDef.h"
#include "GetLog.h"
#include <synchapi.h>
#include "CCFFT.h"

using namespace std;
map<string, tyLimitsData> mapLimits;
tyTestDatas AllTabelData; 
//const char* programPath = "C:/Users/Peng/Desktop/CBBDebuging/CPP_Test_RX_TX";
const char* programPath;
static char WaveFormPath[512] = {"\0"};
//选择L,M,H对应的频率
double selectFrequency(char* cFreq)
{
    if(!strcmp(cFreq,"L"))
    {
        return WLAN_RX_2G_L_Freq;
    }
    else if(!strcmp(cFreq,"M"))
    {
        return WLAN_RX_2G_M_Freq;
    }
    else if(!strcmp(cFreq,"H"))
    {
        return WLAN_RX_2G_H_Freq;
    }
    else if(!strcmp(cFreq,"A"))
    {
        return WLAN_RX_5G_A_Freq;
    }
    else if(!strcmp(cFreq,"B"))
    {
        return WLAN_RX_5G_B_Freq;
    }
    else if(!strcmp(cFreq,"C"))
    {
        return WLAN_RX_5G_C_Freq;
    }
    else if(!strcmp(cFreq,"D"))
    {
        return WLAN_RX_5G_D_Freq;
    }
    else if(!strcmp(cFreq,"B1"))
    {
        return WLAN_TX_5G_B1_Freq;
    }
    else if(!strcmp(cFreq,"B2"))
    {
        return WLAN_TX_5G_B2_Freq;
    }
    else if(!strcmp(cFreq,"B3"))
    {
        return WLAN_TX_5G_B3_Freq;
    }
    else if(!strcmp(cFreq,"B4"))
    {
        return WLAN_TX_5G_B4_Freq;
    }
    else if(!strcmp(cFreq,"B5"))
    {
        return WLAN_TX_5G_B5_Freq;
    }
    else if(!strcmp(cFreq,"B6"))
    {
        return WLAN_TX_5G_B6_Freq;
    }
    else if(!strcmp(cFreq,"B7"))
    {
        return WLAN_TX_5G_B7_Freq;
    }

    return EXIT_SUCCESS;
}

//选择调制的Standard
//static int selectStandard(char* cWave)
//{
//    if(!strcmp(strupr(cWave),"11AG"))
//    {
//        return RFMXWLAN_VAL_STANDARD_802_11_AG;
//    }
//    else if(!strcmp(strupr(cWave),"11B"))
//    {
//        return RFMXWLAN_VAL_STANDARD_802_11_B;
//    }
//    else if(!strcmp(strupr(cWave),"11J"))
//    {
//        return RFMXWLAN_VAL_STANDARD_802_11_J;
//    }
//    else if(!strcmp(strupr(cWave),"11P"))
//    {
//        return RFMXWLAN_VAL_STANDARD_802_11_P;
//    }
//    else if(!strcmp(strupr(cWave),"11N"))
//    {
//        return RFMXWLAN_VAL_STANDARD_802_11_N;
//    }
//    else if(!strcmp(strupr(cWave),"11AC"))
//    {
//        return RFMXWLAN_VAL_STANDARD_802_11_AC;
//    }
//    else if(!strcmp(strupr(cWave),"11AX"))
//    {
//        return RFMXWLAN_VAL_STANDARD_802_11_AX;
//    }
//    return EXIT_SUCCESS;
//}

static int LoadSignal_RX_Trig(tyTestData testRecordData)
{
    int nRet = 0;
    CCSingleToneAttribute singleToneAttr;
    CCMeasureIQAttribute IQAttr;
    
    CCRFmxSpecAnAttribute cfgMxSpecAn;

    //SG
    singleToneAttr.dwFrequency = selectFrequency(testRecordData.cRxFreq) + testRecordData.tyRXTest.dDf1;//ST的频率  //M+DF1
    singleToneAttr.dwPowerLevel = testRecordData.tyRXTest.dP1;          //ST的功率 //dP1
//    singleToneAttr.nTrigger = CCRF_TRIGGER_TYPE_DIGITAL;                //SG ,PXI_Trig0
    nRet = CCRFTester.RFSRC("").SIGNAL(testRecordData.cSrcSig).AddSignalAttribute(&singleToneAttr);

    //SA
    IQAttr.nTrigger = CCRF_TRIGGER_TYPE_DIGITAL;
    IQAttr.dCarrierFrequency = 0; 
    IQAttr.dReferenceLevel = testRecordData.tyCapSigSet.dAmp;
    IQAttr.dwNumberOfSamples = testRecordData.tyCapSigSet.dSampleSize;
    IQAttr.dSampleRate = testRecordData.tyCapSigSet.dSampleRate;//
    nRet = CCRFTester.MIXCAP("").SIGNAL(testRecordData.cCapSig).AddSignalAttribute(&IQAttr);
    
//    cfgMxSpecAn.trigger.nTriggerType = RFMXINSTR_VAL_TRIGGER_TYPE_DIGITAL_EDGE;         //SA
//    cfgMxSpecAn.trigger.DigitalEdgeTrigger.pszDigitalEdgeSource = "PXI_Trig0";
//    cfgMxSpecAn.trigger.DigitalEdgeTrigger.nDigitalEdge = 0;
//    cfgMxSpecAn.trigger.DigitalEdgeTrigger.dTriggerDelay = 0;
//    cfgMxSpecAn.trigger.DigitalEdgeTrigger.nEnableTrigger = VI_TRUE;
    
//    if(strstr(testRecordData.cTestName,"IR")!=NULL){
//        cfgMxSpecAn.dCenterFrequency = 0;
//        cfgMxSpecAn.dReferenceLevel = testRecordData.tyCapSigSet.dAmp;
//        cfgMxSpecAn.Spectrum.dwSampleRate = testRecordData.tyCapSigSet.dSampleRate;
//        cfgMxSpecAn.Spectrum.dwSampleNumbers = testRecordData.tyCapSigSet.dSampleSize;
//        cfgMxSpecAn.SelectMeasurement.nMeasurements = 128;
//        nRet = CCRFTester.MIXCAP("").SIGNAL(testRecordData.cCapSig).AddSignalAttribute(&cfgMxSpecAn);
//    }
//    else{
//        nRet = CCRFTester.MIXCAP("").SIGNAL(testRecordData.cCapSig).AddSignalAttribute(&IQAttr);
//    }

    return nRet;
}

//5841 SG SingleTone, 5820 SA
static int LoadSignal_RX_ST(tyTestData testRecordData)
{
    int nRet = 0;
    CCSingleToneAttribute singleToneAttr;
    CCMeasureIQAttribute IQAttr;
    
    CCRFmxSpecAnAttribute cfgMxSpecAn;

    //SG
    singleToneAttr.dwFrequency = selectFrequency(testRecordData.cRxFreq) + testRecordData.tyRXTest.dDf1;//ST的频率  //M+DF1
    singleToneAttr.dwPowerLevel = testRecordData.tyRXTest.dP1;          //ST的功率 //dP1
    
    nRet = CCRFTester.RFSRC("").SIGNAL(testRecordData.cSrcSig).AddSignalAttribute(&singleToneAttr);
    
    //SA
    IQAttr.dCarrierFrequency = 0; 
    IQAttr.dReferenceLevel = testRecordData.tyCapSigSet.dAmp;
    IQAttr.dwNumberOfSamples = testRecordData.tyCapSigSet.dSampleSize;
    IQAttr.dSampleRate = testRecordData.tyCapSigSet.dSampleRate;//
    

    if(strstr(testRecordData.cTestName,"IR")!=NULL){
        cfgMxSpecAn.dCenterFrequency = 0;
        cfgMxSpecAn.dReferenceLevel = testRecordData.tyCapSigSet.dAmp;
        cfgMxSpecAn.Spectrum.RBWFilter.nRBWAuto = CCRFMXSPECAN_VAL_SPECTRUM_RBW_AUTO_FALSE;
        cfgMxSpecAn.Spectrum.dwSampleRate = testRecordData.tyCapSigSet.dSampleRate;
        cfgMxSpecAn.Spectrum.dwSampleNumbers = testRecordData.tyCapSigSet.dSampleSize;
        cfgMxSpecAn.SelectMeasurement.nMeasurements = CCRFMXSPECAN_VAL_SPECTRUM;  //Capture Spectrum
        nRet = CCRFTester.MIXCAP("").SIGNAL(testRecordData.cCapSig).AddSignalAttribute(&cfgMxSpecAn);
    }
    else{
        nRet = CCRFTester.MIXCAP("").SIGNAL(testRecordData.cCapSig).AddSignalAttribute(&IQAttr);
    }

    return nRet;
}

//5841 SG DualTone, 5820 SA 波形文件的方式，返回值-1：配置的参数信息有误
static int LoadSignal_RX_DT(tyTestData testRecordData)
{
    int nRet = 0;
    char waveformFilePath[512] = {"\0"};
    CCModulationAttribute moduleAttr;
    CCMeasureIQAttribute IQAttr;
    double pathloss[4];
   
    //SG
    if(testRecordData.tyRXTest.dDf1>500e6)
    {
        moduleAttr.dwCarrierFrequency = testRecordData.tyRXTest.dDf1-1e6; //DT的载波频率
    }
    else
    {
        if(testRecordData.tyRXTest.dDf2<500e6){
            moduleAttr.dwCarrierFrequency = selectFrequency(testRecordData.cRxFreq); //DT的载波频率
        }
        else{
            moduleAttr.dwCarrierFrequency = (selectFrequency(testRecordData.cRxFreq)+testRecordData.tyRXTest.dDf2)/2; //DT的载波频率
        }
        
    }
    
    if(testRecordData.tyRXTest.dP1<testRecordData.tyRXTest.dP2){
        moduleAttr.dwPowerLevel = testRecordData.tyRXTest.dP2 ;                   //DT的载波功率
    }
    else{
        moduleAttr.dwPowerLevel = testRecordData.tyRXTest.dP1;                   //DT的载波功率        
    }

    if(!strcmp(testRecordData.tySrcSigSet.cMWSrcTSD, ""))                    //DT对应的波形文件 
    {
        return -1;
    }
//    sprintf(waveformFilePath, "%s%s",WaveFormPath, testRecordData.tySrcSigSet.cMWSrcTSD);
    sprintf(waveformFilePath, "%s", testRecordData.tySrcSigSet.cMWSrcTSD);
    moduleAttr.pszFilePath = waveformFilePath;
    
    //testRecordData.cSrcSig = "DTSrc";
    CCRFTester.RFSRC("").SIGNAL(testRecordData.cSrcSig).AddSignalAttribute(&moduleAttr);

    //SA      
    IQAttr.dCarrierFrequency = 0; 
        
    IQAttr.dReferenceLevel = testRecordData.tyCapSigSet.dAmp;
    IQAttr.dwNumberOfSamples = testRecordData.tyCapSigSet.dSampleSize;
    IQAttr.dSampleRate = testRecordData.tyCapSigSet.dSampleRate;
    
    nRet = CCRFTester.MIXCAP("").SIGNAL(testRecordData.cCapSig).AddSignalAttribute(&IQAttr);
    
    return nRet;
}

//5841 SG DualTone, 5820 SA 波形文件的方式，返回值-1：配置的参数信息有误
static int LoadSignal_RX_MOD(tyTestData testRecordData)
{
    int nRet = 0;
    char waveformFilePath[512] = {"\0"};
    CCModulationAttribute moduleAttr;
    CCRFmxWlanStruct rfmxWlan;
   
    //SG
    moduleAttr.dwCarrierFrequency = selectFrequency(testRecordData.cRxFreq); //DT的载波频率
    moduleAttr.dwPowerLevel = testRecordData.tyRXTest.dP1;
        
    if(!strcmp(testRecordData.tySrcSigSet.cMWSrcTSD, ""))                    //DT对应的波形文件 
    {
        return -1;
    }
//    sprintf(waveformFilePath, "%s%s",WaveFormPath, testRecordData.tySrcSigSet.cMWSrcTSD);
    sprintf(waveformFilePath, "%s", testRecordData.tySrcSigSet.cMWSrcTSD);
    moduleAttr.pszFilePath = waveformFilePath;
    
    //testRecordData.cSrcSig = "MODSrc";
    CCRFTester.RFSRC("").SIGNAL(testRecordData.cSrcSig).AddSignalAttribute(&moduleAttr);

    //SA
    //rfmxWlan.cfgWLAN.SelectMeasurement.nMeasurements = RFMXWLAN_VAL_OFDMMODACC;
    rfmxWlan.dChannelBandwidth = testRecordData.AnaModCap.BW;
    rfmxWlan.dwCarrierFrequence = 0;
    rfmxWlan.dReferenceLevel = testRecordData.tyCapSigSet.dAmp;     //????????20211028
//    rfmxWlan.nWlanStandard = selectStandard(testRecordData.AnaModCap.cStandard);
    
//    rfmxWlan.cfgOFDMModAcc.nEVMUnit = 1;
    
    rfmxWlan.trigger.nTriggerType = RFMXINSTR_VAL_TRIGGER_TYPE_IQ_POWER_EDGE;
    rfmxWlan.trigger.IQPowerEdgeTrigger.pszIQPowerEdgeSource = "0";
    rfmxWlan.trigger.IQPowerEdgeTrigger.nEnableTrigger = CCRFMXINSTR_VAL_TRUE;
    rfmxWlan.trigger.IQPowerEdgeTrigger.nIQPowerEdgeSlope = RFMXINSTR_VAL_IQ_POWER_EDGE_RISING_SLOPE;
    rfmxWlan.trigger.IQPowerEdgeTrigger.dwTriggerMinQuietTimeDuration = 5E-6;
    rfmxWlan.trigger.IQPowerEdgeTrigger.nTriggerMinQuietTimeMode = RFMXINSTR_VAL_TRIGGER_MINIMUM_QUIET_TIME_MODE_AUTO;
    rfmxWlan.trigger.IQPowerEdgeTrigger.nIQPowerEdgeLevelType = RFMXINSTR_VAL_IQ_POWER_EDGE_TRIGGER_LEVEL_TYPE_RELATIVE;
    rfmxWlan.trigger.IQPowerEdgeTrigger.dwTriggerDelay = 0.0;
    rfmxWlan.trigger.IQPowerEdgeTrigger.dwIQPowerEdgeLevel = -20.0;

    nRet = CCRFTester.MIXCAP("").SIGNAL(testRecordData.cCapSig).AddSignalAttribute(&rfmxWlan);
    
    return nRet;
}

//5820 SG ST， 5841 SA
static int LoadSignal_TX_ST(tyTestData testRecordData)
{
    int nRet = 0;
    char waveformFilePath[512] = {"\0"};
    CCMixAttribute MixAttr;
    //CCMeasureSpectrumAttribute SpectrumAttr;
    CCRFmxSpecAnAttribute mxSpecAnAttribute;   
    
    //SG
    MixAttr.dwCommonModeOffset = testRecordData.tySrcSigSet.dComModeVol;
    MixAttr.dwPowerLevel = testRecordData.tySrcSigSet.dAnaSrcAmp0;            //ST的功率
//    sprintf(waveformFilePath, "%s%s",WaveFormPath, testRecordData.tySrcSigSet.cWaveI0);
    sprintf(waveformFilePath, "%s",testRecordData.tySrcSigSet.cWaveI0);
    MixAttr.pszFilePath = waveformFilePath;
    MixAttr.dwLoadImpedance = 100;  //100
    nRet = CCRFTester.MIXSRC("").SIGNAL(testRecordData.cSrcSig).AddSignalAttribute(&MixAttr);
    
    //SA
    mxSpecAnAttribute.dCenterFrequency = selectFrequency(testRecordData.cRxFreq);
    mxSpecAnAttribute.dReferenceLevel = testRecordData.tyCapSigSet.dAmp;
    mxSpecAnAttribute.Spectrum.RBWFilter.nRBWAuto = CCRFMXSPECAN_VAL_SPECTRUM_RBW_AUTO_FALSE;
    mxSpecAnAttribute.Spectrum.dwSampleNumbers = testRecordData.tyCapSigSet.dSampleSize;
    mxSpecAnAttribute.Spectrum.dwSampleRate = testRecordData.tyCapSigSet.dSampleRate;
    mxSpecAnAttribute.Spectrum.nSpectrumPowerUnits = 0;    //0：unit = dbm
    
    nRet = CCRFTester.RFCAP("").SIGNAL(testRecordData.cCapSig).AddSignalAttribute(&mxSpecAnAttribute);
    
    return nRet;
}

static int LoadSignal_TX_DT(tyTestData testRecordData)
{
    int nRet = 0;
    char waveformFilePath[512] = {"\0"};
    CCMixAttribute MixAttr;
    //CCMeasureSpectrumAttribute SpectrumAttr;
    CCRFmxSpecAnAttribute mxSpecAnAttribute;  
    
    //SG
    MixAttr.dwCommonModeOffset = testRecordData.tySrcSigSet.dComModeVol;
    MixAttr.dwPowerLevel = testRecordData.tySrcSigSet.dAnaSrcAmp0;            //DT的功率
//    sprintf(waveformFilePath, "%s%s",WaveFormPath, testRecordData.tySrcSigSet.cWaveI0);
    sprintf(waveformFilePath, "%s",testRecordData.tySrcSigSet.cWaveI0);
    MixAttr.pszFilePath = waveformFilePath;
    MixAttr.dwLoadImpedance = 100;

    nRet = CCRFTester.MIXSRC("").SIGNAL(testRecordData.cSrcSig).AddSignalAttribute(&MixAttr);
    
    //SA
//    SpectrumAttr.dCenterFrequency = selectFrequency(testRecordData.cRxFreq) + (testRecordData.tyTXTest.d2Tone_L + testRecordData.tyTXTest.d2Tone_R)/2;  
//    SpectrumAttr.dReferenceLevel = testRecordData.tyCapSigSet.dAmp;
//    SpectrumAttr.dwSampleNumbers = testRecordData.tyCapSigSet.dSampleSize;
//    SpectrumAttr.dwSampleRate = testRecordData.tyCapSigSet.dSampleRate;
    mxSpecAnAttribute.dCenterFrequency = selectFrequency(testRecordData.cRxFreq) + (testRecordData.tyTXTest.d2Tone_L + testRecordData.tyTXTest.d2Tone_R)/2;  
    mxSpecAnAttribute.dReferenceLevel = testRecordData.tyCapSigSet.dAmp;
    mxSpecAnAttribute.Spectrum.RBWFilter.nRBWAuto = CCRFMXSPECAN_VAL_SPECTRUM_RBW_AUTO_FALSE;
    mxSpecAnAttribute.Spectrum.dwSampleNumbers = testRecordData.tyCapSigSet.dSampleSize;
    mxSpecAnAttribute.Spectrum.dwSampleRate = testRecordData.tyCapSigSet.dSampleRate;
    mxSpecAnAttribute.Spectrum.nSpectrumPowerUnits = 0;
    
    nRet = CCRFTester.RFCAP("").SIGNAL(testRecordData.cCapSig).AddSignalAttribute(&mxSpecAnAttribute);
    
    return nRet;
}

//5820 SG Modulation, 5841 SA
static int LoadSignal_TX_MOD(tyTestData testRecordData)
{
    int nRet = 0;
    char waveformFilePath[512] = {"\0"};
    CCMixAttribute moduleAttr;
    CCRFmxWlanStruct rfmxWlan;
    
    //SG
    moduleAttr.dwCommonModeOffset = testRecordData.tySrcSigSet.dComModeVol;
    moduleAttr.dwPowerLevel = testRecordData.tySrcSigSet.dAnaSrcAmp0;            //MOD的功率
//    sprintf(waveformFilePath, "%s%s",WaveFormPath, testRecordData.tySrcSigSet.cWaveI0);
    sprintf(waveformFilePath, "%s",testRecordData.tySrcSigSet.cWaveI0);
    moduleAttr.pszFilePath = waveformFilePath;
    moduleAttr.dwLoadImpedance = 100;
    nRet = CCRFTester.MIXSRC("").SIGNAL(testRecordData.cSrcSig).AddSignalAttribute(&moduleAttr);
    
    //SA
    rfmxWlan.SelectMeasurement.nMeasurements = RFMXWLAN_VAL_OFDMMODACC|RFMXWLAN_VAL_SEM;
    
    rfmxWlan.dChannelBandwidth = testRecordData.RfModCap.BW;
    rfmxWlan.dwCarrierFrequence = selectFrequency(testRecordData.cRxFreq);
    rfmxWlan.dReferenceLevel = testRecordData.tyCapSigSet.dAmp;     //????????
//    rfmxWlan.nWlanStandard = selectStandard(testRecordData.RfModCap.cStandard);

    rfmxWlan.trigger.nTriggerType = RFMXINSTR_VAL_TRIGGER_TYPE_IQ_POWER_EDGE;
    rfmxWlan.trigger.IQPowerEdgeTrigger.pszIQPowerEdgeSource = "0";
    rfmxWlan.trigger.IQPowerEdgeTrigger.nEnableTrigger = CCRFMXINSTR_VAL_TRUE;
    rfmxWlan.trigger.IQPowerEdgeTrigger.nIQPowerEdgeSlope = RFMXINSTR_VAL_IQ_POWER_EDGE_RISING_SLOPE;
    rfmxWlan.trigger.IQPowerEdgeTrigger.dwTriggerMinQuietTimeDuration = 5E-6;
    rfmxWlan.trigger.IQPowerEdgeTrigger.nTriggerMinQuietTimeMode = RFMXINSTR_VAL_TRIGGER_MINIMUM_QUIET_TIME_MODE_AUTO;
    rfmxWlan.trigger.IQPowerEdgeTrigger.nIQPowerEdgeLevelType = RFMXINSTR_VAL_IQ_POWER_EDGE_TRIGGER_LEVEL_TYPE_RELATIVE;
    rfmxWlan.trigger.IQPowerEdgeTrigger.dwTriggerDelay = 0.0;
    rfmxWlan.trigger.IQPowerEdgeTrigger.dwIQPowerEdgeLevel = -30.0;
    
    nRet = CCRFTester.RFCAP("").SIGNAL(testRecordData.cCapSig).AddSignalAttribute(&rfmxWlan);
    
    return nRet;
}

//5820 SG ST
static int LoadSignal_ADC_ST(tyTestData testRecordData)
{
    int nRet = 0;
    char waveformFilePath[512] = {"\0"};
    CCMixAttribute MixAttr;
    //CCMeasureSpectrumAttribute SpectrumAttr;
    CCRFmxSpecAnAttribute mxSpecAnAttribute;   
    
    //SG
    MixAttr.dwCommonModeOffset = testRecordData.tySrcSigSet.dComModeVol;
    MixAttr.dwPowerLevel = testRecordData.tySrcSigSet.dAnaSrcAmp0;            //ST的功率
//    sprintf(waveformFilePath, "%s%s",WaveFormPath, testRecordData.tySrcSigSet.cWaveI0);
    sprintf(waveformFilePath, "%s", testRecordData.tySrcSigSet.cWaveI0);
    MixAttr.pszFilePath = waveformFilePath;
    //MixAttr.pszFilePath  = testRecordData.tySrcSigSet.cWaveI0;         //TDMS波形文件的路径
    //testRecordData.cSrcSig = "TXST";
    MixAttr.dwLoadImpedance = 100;
    nRet = CCRFTester.MIXSRC("").SIGNAL(testRecordData.cSrcSig).AddSignalAttribute(&MixAttr);
    
    //SA
//    mxSpecAnAttribute.dCenterFrequency = selectFrequency(testRecordData.cRxFreq); 
//    mxSpecAnAttribute.dReferenceLevel = testRecordData.tyCapSigSet.dAmp;
//    mxSpecAnAttribute.Spectrum.dwSampleNumbers = testRecordData.tyCapSigSet.dSampleSize;
//    mxSpecAnAttribute.Spectrum.dwSampleRate = testRecordData.tyCapSigSet.dSampleRate;
//    mxSpecAnAttribute.Spectrum.nSpectrumPowerUnits = 0;
//    
//    nRet = CCRFTester.RFCAP("").SIGNAL(testRecordData.cCapSig).AddSignalAttribute(&mxSpecAnAttribute);
    
    return nRet;
}

//5820 SA
static int LoadSignal_DAC_ST(tyTestData testRecordData)
{
    int nRet = 0;
    CCSingleToneAttribute singleToneAttr;
    CCMeasureIQAttribute IQAttr;
    
    CCRFmxSpecAnAttribute cfgMxSpecAn;

    //SG
//    singleToneAttr.dwFrequency = selectFrequency(testRecordData.cRxFreq) + testRecordData.tyRXTest.dDf1;//ST的频率  //M+DF1
//    singleToneAttr.dwPowerLevel = testRecordData.tyRXTest.dP1;          //ST的功率 //dP1
//    
//    nRet = CCRFTester.RFSRC("").SIGNAL(testRecordData.cSrcSig).AddSignalAttribute(&singleToneAttr);
    
    //SA
    IQAttr.dCarrierFrequency = 0; 
    IQAttr.dReferenceLevel = testRecordData.tyCapSigSet.dAmp;
    IQAttr.dwNumberOfSamples = testRecordData.tyCapSigSet.dSampleSize;
    IQAttr.dSampleRate = testRecordData.tyCapSigSet.dSampleRate;//
    nRet = CCRFTester.MIXCAP("").SIGNAL(testRecordData.cCapSig).AddSignalAttribute(&IQAttr);


    return nRet;
}

static int LoadEverySignal(tyTestData testRecordData) 
{
    int nRet = 0;
    
    if(testRecordData.iTRX == RX_Path)
    {
        switch(testRecordData.Sigtype)
        {
            case Sig_ST:
                nRet = LoadSignal_RX_ST(testRecordData);
                break;
            case Sig_DT:
                nRet = LoadSignal_RX_DT(testRecordData);
                break;
            case Sig_MOD:
                nRet = LoadSignal_RX_MOD(testRecordData);
                break;
            case Sig_TRIG:
                nRet = LoadSignal_RX_Trig(testRecordData);               
            default:
                break;
        }
    }
    else if(testRecordData.iTRX == TX_Path)
    {
        switch(testRecordData.Sigtype)
        {
            case Sig_ST:
                nRet = LoadSignal_TX_ST(testRecordData);
                break;
            case Sig_DT:
                nRet = LoadSignal_TX_DT(testRecordData);
                break;
            case Sig_MOD:
                nRet = LoadSignal_TX_MOD(testRecordData);
                break;
            default:
                break;
        }
    }
    else if(testRecordData.iTRX == ADC_Path)
    {      
        nRet = LoadSignal_ADC_ST(testRecordData); 
    }
    else if(testRecordData.iTRX == DAC_Path)
    {
        nRet = LoadSignal_DAC_ST(testRecordData);     
    }
    
    return EXIT_SUCCESS;

}

int LoadAllSignalAttr(char* ExcelFilePath,char* PathlossFilePath)
{
    int nRet = 0;
    int nTestRecordCount = 0;
    tyTestData testRecord;
    int nRecordIndex = 0;
    //调用库函数 获取整个excel表格的所有数据
    //only install excel
    //if(Get_TestDatas(ExcelFilePath, AllTabelData) != 0)Get_TestDatas(char *xlsxPath, char *pathlossPath, tyTestDatas &testDatas);

    if(Get_TestDatas(ExcelFilePath, PathlossFilePath, AllTabelData)!=0)
    {
        return -1;
    }

    //遍历整个数据，进行signal的load
    nTestRecordCount = AllTabelData.lDataLength;

    while(nRecordIndex < nTestRecordCount)
    { 
        //取出每一个testRecord
        testRecord = AllTabelData.testData[nRecordIndex++];
        //进行signal的配置
        nRet = LoadEverySignal(testRecord);
        if(nRet != 0)
        {
            LOG("Load Fail TestName: \n");
            LOG(testRecord.cTestName);
            LOG("\n");
        }
    }
    
//    tyTestData RF_Test_Data;
//	emTRX TRX_Path_Select;
//	char *Channel;
//	emMode Mode_Select;
//
//	Get_TestItem_Info("WL_RX_2G_M_C0_RFI_INIT", RF_Test_Data);
//	Channel = RF_Test_Data.cChannel;
//	TRX_Path_Select = RF_Test_Data.iTRX;
//	Mode_Select = (emMode) RF_Test_Data.iMode;





    return 0;
}

int Get_TestItem_Info(const char* testname, tyTestData &Test_Data)
{
    char * strTestName = 0;
    int i = 0;
    
    for(; i < AllTabelData.lDataLength; i++)
    {
        strTestName = AllTabelData.testData[i].cTestName;
//        if(strTestName.find(testname) < strTestName.length())
        if(!strcmp(testname,strTestName)) //AllTabelData.testData[i].cTestName))
        {
            Test_Data = AllTabelData.testData[i];
            break;
        }
    }

    return ((i < AllTabelData.lDataLength)? 0 : -1);
}

int Get_Pin_Name(tyTestData Test_Data, char* SrcPinName, char* CapPinName)
{
    if(Test_Data.iTRX == RX_Path)
    {
        strcpy(SrcPinName, Test_Data.tySrcSigSet.cRF_SrcPin);
        strcpy(CapPinName, Test_Data.tyCapSigSet.cI_CapPin_P);
    }
    else if(Test_Data.iTRX == TX_Path)
    {
        strcpy(SrcPinName, Test_Data.tySrcSigSet.cI_SrcPin_P);
        strcpy(CapPinName, Test_Data.tyCapSigSet.cRF_CapPin);
    }
    else if(Test_Data.iTRX == ADC_Path)
    {      
        strcpy(SrcPinName, Test_Data.tySrcSigSet.cI_SrcPin_P);
    }
    else if(Test_Data.iTRX == DAC_Path)
    {
        strcpy(CapPinName, Test_Data.tyCapSigSet.cI_CapPin_P);     
    }
    
    return 0;
}

int Get_Signal_Name(tyTestData Test_Data, char* SrcSignalName, char* CapSignalName)
{
    strcpy(SrcSignalName, Test_Data.cSrcSig);
    strcpy(CapSignalName, Test_Data.cCapSig);
    
    return 0;
}

//在频谱中获取指定频点的功率值
int GetPowerofSpecifiedFreq(SpecAnResultAttribute *SpecAnMeasData, double dwFrequency, ViReal32 &dwPower, int nSpanNum)
{
    ViReal32 nFreIndex = 0;
    nFreIndex = (dwFrequency - SpecAnMeasData->dInitiaFrequency) / SpecAnMeasData->dFrequencyIncrement;
    for(int w = nFreIndex - nSpanNum; w < nFreIndex + nSpanNum; w++)
    {
        if(w >= SpecAnMeasData->dwNumbersOfSpectrum)
        {
            break;
        }
        dwPower = max(SpecAnMeasData->pSpectrumDataBuf[w], dwPower);
    }
    
    return 0;
}

/* 取出双音计算IMD3的4个功率 （算法可进一步优化）*/
int ComputeDoubleToneIMD3(SpecAnResultAttribute *SpecAnMeasData, double dwFrequency1, double dwFrequency2, ViReal32 &dwIMD3Val, int nSpanNum){
 
    double dwFrequency[4] = {2*dwFrequency1 - dwFrequency2, dwFrequency1, dwFrequency2, 2*dwFrequency2 - dwFrequency1};
    ViReal32 dwIMD3Power[4] = {0.0};
    
    for(int i = 0; i < 4; i++)
    {
        GetPowerofSpecifiedFreq(SpecAnMeasData, dwFrequency[i], dwIMD3Power[i], nSpanNum);
    }

    dwIMD3Val = min(dwIMD3Power[1], dwIMD3Power[2]) - max(dwIMD3Power[0], dwIMD3Power[3]);
    
    return 0;
}

int SplitIQData(IQMeasureAttribute *IQMeasData, double *Inreal, double *Inimag)
{

    for(int i = 0; i < IQMeasData->actualSamples; i++)
    {
        Inreal[i] = IQMeasData->pComplexData[i].real;
        Inimag[i] = IQMeasData->pComplexData[i].imaginary;

    }
    
    return 0;
}


//static void WriteData(const char* pszFileName,double dData[],long lDataSize)
//{
//	char szPath[64] = {0};
//	sprintf(szPath,"%s.txt",pszFileName);
//	ofstream fout(szPath);
////	fout.seekp(ios::end);
//	for(long i = 0;i<lDataSize;i++)
//	{
//		fout << dData[i] << endl;
//	}
//	fout.close();
//}

//根据抓取的IQ数据，分别做FFT,
/* @Spectrum_I: int指针指向double数据
 * @Spectrum_Q：int指针指向double数据
 */
int FFTFromIQData(IQMeasureAttribute *IQMeasData, double** Spectrum_I, double** Spectrum_Q)
{
    double *Inreal = 0, *Inimag = 0;
//    double *SpectrumTemp_I = 0, *SpectrumTemp_Q = 0;
    long long DataSize = IQMeasData->actualSamples;
    
//    if((*Spectrum_I))
//    {
//    	delete[] (*Spectrum_I);
//    	(*Spectrum_I) = 0;
//    }
//
//    if(*Spectrum_Q)
//    {
//    	delete[] *Spectrum_Q;
//    	*Spectrum_Q = 0;
//    }
    CC_RELEASE_BUF(*Spectrum_I);
	CC_RELEASE_BUF(*Spectrum_Q);

//    *Spectrum_I = 0;
//    *Spectrum_Q = 0;
    if(DataSize > 0)                    //Ensure the samples  number must larger than 0.                                       
    {
        Inreal = new double[DataSize];
        Inimag = new double[DataSize];
        memset(Inreal, 0x00, sizeof(double)*DataSize);
        memset(Inimag, 0x00, sizeof(double)*DataSize);

        *Spectrum_I = new double[DataSize/2];
        *Spectrum_Q = new double[DataSize/2];
        memset(*Spectrum_I, 0x00, sizeof(double)*DataSize/2);
        memset(*Spectrum_Q, 0x00, sizeof(double)*DataSize/2);

        SplitIQData(IQMeasData, Inreal, Inimag);


//        WriteData("Real_Data",Inreal,DataSize);
//        WriteData("Image_Data",Inimag,DataSize);
        CCDSP::FFT(Inreal,DataSize,*Spectrum_I,CCDSP::_0_Ohm);
        CCDSP::FFT(Inimag,DataSize,*Spectrum_Q,CCDSP::_0_Ohm);
//        WriteData("Real_FFT_Data",*Spectrum_I,DataSize/2);
//        WriteData("Image_FFT_Data",*Spectrum_Q,DataSize/2);

        for(int i = 0;i < DataSize/2; i++){
        	(*Spectrum_I)[i] = (*Spectrum_I)[i]*2;
        	(*Spectrum_Q)[i] = (*Spectrum_Q)[i]*2;
        }

        CC_RELEASE_BUF(Inreal);
        CC_RELEASE_BUF(Inimag);
//        delete[] Inreal;
//        delete[] Inimag;
    }
    return 0;
}

//根据FFT的结果取出指定频点的Power
int GetPowerofSpecifiedFreq(double *Spectrum_I, double *Spectrum_Q, double dwFrequency, double dwSampleRate, double dwSampleSize, \
                            double &dwPower_I, double &dwPower_Q,double BinNum )
{
    dwPower_I = -999;
    dwPower_Q = -999;

    if((Spectrum_I != 0)&&(Spectrum_Q != 0))                                    //ensure the pointer must be a valid address.
    {
        int WavBin = floor(dwFrequency / (dwSampleRate / dwSampleSize));

        if(BinNum == 1){
            dwPower_I = 10*log10((Spectrum_I[WavBin]*Spectrum_I[WavBin] + 1e-18)/50*1000);
            dwPower_Q = 10*log10((Spectrum_Q[WavBin]*Spectrum_Q[WavBin] + 1e-18)/50*1000);
        }
        else if(BinNum == 3){
            dwPower_I = 10*log10((Spectrum_I[WavBin-1]*Spectrum_I[WavBin-1] + Spectrum_I[WavBin]*Spectrum_I[WavBin] + Spectrum_I[WavBin+1]*Spectrum_I[WavBin+1] + 1e-18)/50*1000);
            dwPower_Q = 10*log10((Spectrum_Q[WavBin-1]*Spectrum_Q[WavBin-1] + Spectrum_Q[WavBin]*Spectrum_Q[WavBin] + Spectrum_Q[WavBin+1]*Spectrum_Q[WavBin+1] + 1e-18)/50*1000);
        }
        else if(BinNum == 5){
            dwPower_I = 10*log10((Spectrum_I[WavBin-2]*Spectrum_I[WavBin-2] + Spectrum_I[WavBin-1]*Spectrum_I[WavBin-1] + Spectrum_I[WavBin]*Spectrum_I[WavBin] + Spectrum_I[WavBin+1]*Spectrum_I[WavBin+1] + Spectrum_I[WavBin+2]*Spectrum_I[WavBin+2] + 1e-18)/50*1000);
            dwPower_Q = 10*log10((Spectrum_Q[WavBin-2]*Spectrum_Q[WavBin-2] + Spectrum_Q[WavBin-1]*Spectrum_Q[WavBin-1] + Spectrum_Q[WavBin]*Spectrum_Q[WavBin] + Spectrum_Q[WavBin+1]*Spectrum_Q[WavBin+1] + Spectrum_Q[WavBin+2]*Spectrum_Q[WavBin+2] + 1e-18)/50*1000);
        }
        else if(BinNum == 7){
            dwPower_I = 10*log10((Spectrum_I[WavBin-3]*Spectrum_I[WavBin-3] + Spectrum_I[WavBin-2]*Spectrum_I[WavBin-2] + Spectrum_I[WavBin-1]*Spectrum_I[WavBin-1] + Spectrum_I[WavBin]*Spectrum_I[WavBin] + Spectrum_I[WavBin+1]*Spectrum_I[WavBin+1] + Spectrum_I[WavBin+2]*Spectrum_I[WavBin+2] + Spectrum_I[WavBin+3]*Spectrum_I[WavBin+3] + 1e-18)/50*1000);
            dwPower_Q = 10*log10((Spectrum_Q[WavBin-3]*Spectrum_Q[WavBin-3] + Spectrum_Q[WavBin-2]*Spectrum_Q[WavBin-2] + Spectrum_Q[WavBin-1]*Spectrum_Q[WavBin-1] + Spectrum_Q[WavBin]*Spectrum_Q[WavBin] + Spectrum_Q[WavBin+1]*Spectrum_Q[WavBin+1] + Spectrum_Q[WavBin+2]*Spectrum_Q[WavBin+2] + Spectrum_Q[WavBin+3]*Spectrum_Q[WavBin+3] + 1e-18)/50*1000);
        }

//        CC_RELEASE_BUF(Spectrum_I);
//        CC_RELEASE_BUF(Spectrum_Q);
//        delete[] Spectrum_I;      Dead
//        delete[] Spectrum_Q;
    }
    return 0;
}
//根据抓取IQ数据，画图
int PlotCurve(IQMeasureAttribute *IQMeasData, char* waveformName)
{
    double *Inreal, *Inimag;
    char waveformI[256] = {"\0"};
    char waveformQ[256] = {"\0"};
    
    sprintf(waveformI, "%s_I", waveformName);
    sprintf(waveformQ, "%s_Q", waveformName);
    
    Inreal = new double[IQMeasData->actualSamples];
    Inimag = new double[IQMeasData->actualSamples];
    memset(Inreal, 0x00, sizeof(double)*IQMeasData->actualSamples);
    memset(Inimag, 0x00, sizeof(double)*IQMeasData->actualSamples);
    
    SplitIQData(IQMeasData, Inreal, Inimag);
    
    //画出波形

    return 0;
}

//计算指定level起来的时间
int Cal_PowerUpTime(IQMeasureAttribute *IQMeasData, double TriggerData, double &dwPowerUpI, double &dwPowerUpQ)
{
    double *Inreal, *Inimag;
    int nTriggerIndex_I = 0, nTriggerIndex_Q = 0;
    
    Inreal = new double[IQMeasData->actualSamples];
    Inimag = new double[IQMeasData->actualSamples];
    memset(Inreal, 0x00, sizeof(double)*IQMeasData->actualSamples);
    memset(Inimag, 0x00, sizeof(double)*IQMeasData->actualSamples);
    
    SplitIQData(IQMeasData, Inreal, Inimag);
    
    for(int i = 1; i < IQMeasData->actualSamples; i++)
    {
        if(Inreal[i-1] < TriggerData && Inreal[i] > TriggerData)
        {
            nTriggerIndex_I = i;
            break;
        }
    }
    for(int i = 1; i < IQMeasData->actualSamples; i++)
    {
        if(Inimag[i-1] < TriggerData && Inimag[i] > TriggerData)
        {
            nTriggerIndex_Q = i;
            break;
        }
    }
    
    dwPowerUpI = nTriggerIndex_I * IQMeasData->xIncrement;
    dwPowerUpQ = nTriggerIndex_Q * IQMeasData->xIncrement;
    
    return 0;
}

int GetIMD3FromIQData(double *Spectrum_I, double *Spectrum_Q, double dwFrequency1, double dwFrequency2, \
                      double dwSampleRate, double dwSampleSize, double &dwIMD3Power_I, double &dwIMD3Power_Q, double &fund_Power_I, double &fund_Power_Q)
{
    double dwFrequency[4] = {2*dwFrequency1 - dwFrequency2, dwFrequency1, dwFrequency2, 2*dwFrequency2 - dwFrequency1};
    double dwIMD3Power[2][4] = {0.0};
    
    for(int i = 0; i < 4; i++)
    {
        GetPowerofSpecifiedFreq(Spectrum_I, Spectrum_Q, dwFrequency[i], dwSampleRate, dwSampleSize,dwIMD3Power[0][i], dwIMD3Power[1][i]);
    }
    
    dwIMD3Power_I = dwIMD3Power[0][1] - dwIMD3Power[0][0];
    dwIMD3Power_Q = dwIMD3Power[1][1] - dwIMD3Power[1][0];
    
    fund_Power_I = dwIMD3Power[0][1];
    fund_Power_Q = dwIMD3Power[1][1]; 

//    dwIMD3Power_I = min(dwIMD3Power[0][1], dwIMD3Power[0][2]) - max(dwIMD3Power[0][0], dwIMD3Power[0][3]);
//    dwIMD3Power_Q = min(dwIMD3Power[1][1], dwIMD3Power[1][2]) - max(dwIMD3Power[1][0], dwIMD3Power[1][3]);
    
    return 0;
}

int LoadSignal_MIX_DC(double Force_val,char *Signalname)
{
    int nRet = 0;
    char waveformFilePath[512] = {"\0"};
    CCMixAttribute MixAttr;
    //CCMeasureSpectrumAttribute SpectrumAttr;
    //SG
//    const char* pszWaveFormPath = "E:\\1151\\Hi1151SGNCV208_FTx4_S08F_M43_35022813(V200)_20211116\\Waveforms";

    MixAttr.dwPowerLevel = 1.3;//Force_val;  
    MixAttr.dwCommonModeOffset = Force_val;//Force_val/2;          
    //MixAttr.pszFilePath = "/Waveform_DC.tdms";
//    sprintf(waveformFilePath, "%s%s",WaveFormPath, "\\PD_BUF_ST_1M875.tdms");
    sprintf(waveformFilePath, "%s", "PD_BUF_ST_1M875");

//    cout << WaveFormPath <<endl;

    MixAttr.pszFilePath = waveformFilePath;
    //MixAttr.pszFilePath  = testRecordData.tySrcSigSet.cWaveI0;         //TDMS波形文件的路径
    //sprintf(Signalname, "PDBUF_%f", Force_val);
    MixAttr.dwLoadImpedance = 100;
    nRet = CCRFTester.MIXSRC("").SIGNAL(Signalname).AddSignalAttribute(&MixAttr);
    



    return nRet;
}

//int LoadSignal_MIX_DC(double Force_val,char *Signalname)
//{
//    int nRet = 0;
//    char waveformFilePath[512] = {"\0"};
//    CCMixAttribute MixAttr;
//    //CCMeasureSpectrumAttribute SpectrumAttr;
//    
//    //SG
//    MixAttr.dwPowerLevel = 0.01;//Force_val;  
//    MixAttr.dwCommonModeOffset = Force_val;//Force_val/2;          
//    //MixAttr.pszFilePath = "/Waveform_DC.tdms";
//    sprintf(waveformFilePath, "%s%s",WaveFormPath, "/TX_DC.tdms");
//    MixAttr.pszFilePath = waveformFilePath;
//    //MixAttr.pszFilePath  = testRecordData.tySrcSigSet.cWaveI0;         //TDMS波形文件的路径
//    //sprintf(Signalname, "PDBUF_%f", Force_val);
//    MixAttr.dwLoadImpedance = 100;
//    nRet = CCRFTester.MIXSRC("").SIGNAL(Signalname).AddSignalAttribute(&MixAttr);
//    
//    return nRet;
//}

int LoadSignal_MIX_TX_2G_DC(double Force_val,char *Signalname)
{
    int nRet = 0;
    char waveformFilePath[512] = {"\0"};
    CCMixAttribute MixAttr;
    //CCMeasureSpectrumAttribute SpectrumAttr;
    
    //SG
    MixAttr.dwPowerLevel = 0.01;//1.2;  
    MixAttr.dwCommonModeOffset = 0;//0.3;          
    //MixAttr.pszFilePath = "/Waveform_DC.tdms";
//    sprintf(waveformFilePath, "%s%s",WaveFormPath, "/TX_DC.tdms");
    sprintf(waveformFilePath, "%s", "TX_DC");
    MixAttr.pszFilePath = waveformFilePath;
    //MixAttr.pszFilePath  = testRecordData.tySrcSigSet.cWaveI0;         //TDMS波形文件的路径
    //sprintf(Signalname, "PDBUF_%f", Force_val);
    MixAttr.dwLoadImpedance = 100;
    nRet = CCRFTester.MIXSRC("").SIGNAL(Signalname).AddSignalAttribute(&MixAttr);
    
    return nRet;
}

int MWCapture_Signal(double CenterFrequency,double ReferenceLevel,long SampleNumbers,double SampleRate,char *Signalname)
{
    int nRet = 0;       
    CCRFmxSpecAnAttribute mxSpecAnAttribute;   
    
    //SA
    mxSpecAnAttribute.dCenterFrequency = CenterFrequency; 
    mxSpecAnAttribute.dReferenceLevel = ReferenceLevel;
    mxSpecAnAttribute.Spectrum.dwSampleNumbers = SampleNumbers;
    mxSpecAnAttribute.Spectrum.dwSampleRate = SampleRate;
    mxSpecAnAttribute.Spectrum.nSpectrumPowerUnits = 0;
    
    nRet = CCRFTester.RFCAP("").SIGNAL(Signalname).AddSignalAttribute(&mxSpecAnAttribute);

    return nRet;
}

void Load_UltraWave_Cap_Signals(double WLAN_RX_5G_Band_Fre,char *Signalname)
{
    MWCapture_Signal(WLAN_RX_5G_Band_Fre + 2.5E6,0,1024, 20.48E6,Signalname);
    //MWCapture_Signal(WLAN_RX_5G_Band_Fre + 2.5E6,0,1024, 20.48E6,Signalname);  //C1
    
//    MWCapture_Signal(5120E6,-60,2048, 10.24E6,"MWCap_WL_5G_DAC_SPUR1_C0");
//    MWCapture_Signal(5120E6,-60,2048, 10.24E6,"MWCap_WL_5G_DAC_SPUR1_C1");
//    
//    MWCapture_Signal(5440E6,-60,2048, 10.24E6,"MWCap_WL_5G_DAC_SPUR2_C0");
//    MWCapture_Signal(5440E6,-60,2048, 10.24E6,"MWCap_WL_5G_DAC_SPUR2_C1");
//    
//    MWCapture_Signal(5295E6,-10,4096, 20.48E6,"MWCap_WL_5G_DAC_CW_C0");
//    MWCapture_Signal(5295E6,-10,4096, 20.48E6,"MWCap_WL_5G_DAC_CW_C1");
//    
//    MWCapture_Signal(WLAN_TX_5G_B7_Freq + 37.5E6,0,4096, 300E6,"MWCap_WL_5G_B7_37P5M_C0");
//    MWCapture_Signal(WLAN_TX_5G_B7_Freq + 37.5E6,0,4096, 300E6,"MWCap_WL_5G_B7_37P5M_C1");    
}



int MWSource_Signal_CW(double Frequency,double PowerLevel,char *Signalname)
{
    int nRet = 0;
    CCSingleToneAttribute singleToneAttr;            

    //SG
    singleToneAttr.dwFrequency = Frequency;//ST的频率  //M+DF1
    singleToneAttr.dwPowerLevel = PowerLevel;          //ST的功率 //dP1
    
    nRet = CCRFTester.RFSRC("").SIGNAL(Signalname).AddSignalAttribute(&singleToneAttr);
    return nRet;
}


void Load_UltraWave_Src_Signals()
{
    MWSource_Signal_CW(WLAN_RX_5G_D_Freq + 5E6,-40,"MWsrc_RX5G_D_PHASE_C0_5M");
    MWSource_Signal_CW(WLAN_RX_5G_D_Freq + 25E6,-40,"MWsrc_RX5G_D_PHASE_C0_25M");
    MWSource_Signal_CW(WLAN_RX_5G_D_Freq + 35E6,-40,"MWsrc_RX5G_D_PHASE_C0_35M");
    MWSource_Signal_CW(WLAN_RX_5G_D_Freq - 5E6,-40,"MWsrc_RX5G_D_PHASE_C0_N5M");
    MWSource_Signal_CW(WLAN_RX_5G_D_Freq - 25E6,-40,"MWsrc_RX5G_D_PHASE_C0_N25M");
    MWSource_Signal_CW(WLAN_RX_5G_D_Freq - 35E6,-40,"MWsrc_RX5G_D_PHASE_C0_N35M");
    
    MWSource_Signal_CW(WLAN_RX_5G_D_Freq + 5E6,-40,"MWsrc_RX5G_D_PHASE_C1_5M");
    MWSource_Signal_CW(WLAN_RX_5G_D_Freq + 25E6,-40,"MWsrc_RX5G_D_PHASE_C1_25M");
    MWSource_Signal_CW(WLAN_RX_5G_D_Freq + 35E6,-40,"MWsrc_RX5G_D_PHASE_C1_35M");
    MWSource_Signal_CW(WLAN_RX_5G_D_Freq - 5E6,-40,"MWsrc_RX5G_D_PHASE_C1_N5M");
    MWSource_Signal_CW(WLAN_RX_5G_D_Freq - 25E6,-40,"MWsrc_RX5G_D_PHASE_C1_N25M");
    MWSource_Signal_CW(WLAN_RX_5G_D_Freq - 35E6,-40,"MWsrc_RX5G_D_PHASE_C1_N35M");
    
}


int LoadSignalSetting()
{
    int error = 0;
    char TemplatePath[512] = {"\0"};
    char PathlossPath[512] = {"\0"};

    string programPath = TheSoft.GetProgramPath();
    sprintf(TemplatePath, "%s/TestPlan.xlsx",programPath.c_str());
    sprintf(PathlossPath, "%s/Hi1151GNCV200_FTx4_S08F_CAL_N10.xlsx.lnk",programPath.c_str());
    sprintf(WaveFormPath, "%s/Waveforms",programPath.c_str());
    

    ErrorCheck (LoadAllSignalAttr(TemplatePath,PathlossPath));
errHandler:
    if(Test_Success != error)
    {
    //    api->set_result_bin_name("FAIL_BIN");
    }
    return EXIT_SUCCESS;
}

//RC_Code->InitDataArray(Site_id, 1);
//MaxSR_Value.SetElement(site_id,0,SR_Data);



void Globle_Array_Init()
{    
	FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)

        WL_C0_PPF_CODE.InitDataArray(site_id,32);
        WL_C1_PPF_CODE.InitDataArray(site_id,32);

        for(int i = 0;i<32;i++)
        {
            WL_C0_PPF_CODE.SetElement(site_id,0,-999);
            WL_C1_PPF_CODE.SetElement(site_id,0,-999);
        }    

	FOREACH_ACTIVESITE_END
//    TRIM_DATA_LIST_C0[10][4];
//    TRIM_DATA_LIST_C1[10][4];
//    RX_GAIN_MAX_I_C0[10][4];
//    RX_GAIN_MAX_I_C1[10][4];
    memset(TRIM_DATA_LIST_C0,0 ,sizeof(TRIM_DATA_LIST_C0));
    memset(TRIM_DATA_LIST_C1,0 ,sizeof(TRIM_DATA_LIST_C1));
    memset(RX_GAIN_MAX_I_C0,0 ,sizeof(RX_GAIN_MAX_I_C0));
    memset(RX_GAIN_MAX_I_C1,0 ,sizeof(RX_GAIN_MAX_I_C1));
    
}


void Read_Pathloss(tyTestData Test_Data, double *pathloss) 
{
    double att;
    if(strstr(Test_Data.cTestName,"TX_2G")!=NULL){
        att=10.0;
    }
    else{
        att=0.0;
    }
        
    for (int i = 0; i < 4; i++) {
        pathloss[i] = Test_Data.plInfo.plLossArray[i]+att;
    }
    
}
#if 1
void Read_Limit(double *Lowlimit,double *Highlimit,vector<string> &Test_name,int *Test_number,vector<string> &Units,int *Fail_Soft,int *Fail_Hard)
{
    string name = TheSoft.Flow().Test().GetCurrentTestName();
    map<string, tyLimitsData>::iterator iter;
    tyLimitsData tempLimitsData;
    vector<string> test_name;
    vector<double> lowlimit;
    vector<double> highlimit;
    vector<string> units;
    vector<ViUInt64> test_number;
    vector<ViUInt32> fail_sort;
    vector<ViUInt8> fail_bin;

    iter = mapLimits.find(name);
    if(iter != mapLimits.end())
    {
        tempLimitsData = iter->second;
//        flowtable = tempLimitsData.flowtable;

        if(strcmp("Default",CurrentLimitSet) == 0){
			lowlimit = tempLimitsData.Default_lolim;
			highlimit = tempLimitsData.Default_hilim;
        }
        else if(strcmp("Golden",CurrentLimitSet) == 0){
			lowlimit = tempLimitsData.Golden_lolim;
			highlimit = tempLimitsData.Golden_hilim;
        }
//        else if(CurrentLimitSet=="L40C_QA"){
//        lowlimit = tempLimitsData.L40C_QA_lolim;
//        highlimit = tempLimitsData.L40C_QA_hilim;
//        }
//        else if(CurrentLimitSet=="L40C"){
//        lowlimit = tempLimitsData.L40C_lolim;
//        highlimit = tempLimitsData.L40C_hilim;
//        }
        else if(strcmp("QA",CurrentLimitSet) == 0){
			lowlimit = tempLimitsData.QA_lolim;
			highlimit = tempLimitsData.QA_hilim;
        }
//        else if(CurrentLimitSet=="_105C_QA"){
//        lowlimit = tempLimitsData._105C_QA_lolim;
//        highlimit = tempLimitsData._105C_QA_hilim;
//        }
//        else if(CurrentLimitSet=="_105C"){
//        lowlimit = tempLimitsData._105C_lolim;
//        highlimit = tempLimitsData._105C_hilim;
//        }
        fail_sort = tempLimitsData.failsort;
        fail_bin = tempLimitsData.failbin;

        test_name = tempLimitsData.testname;
        test_number = tempLimitsData.testnumber;
        units = tempLimitsData.units;

    }

    Test_name = test_name;
    Units = units;

    for(unsigned int i = 0; i < lowlimit.size(); i++)
    {
       Lowlimit[i] = lowlimit[i];
       Highlimit[i] = highlimit[i];
       Test_number[i] = test_number[i];
       Fail_Soft[i]=fail_sort[i];
       Fail_Hard[i] = fail_bin[i];

//       Test_name[i] = test_name[i];
//       Units[i] = units[i];

//       printf(".................... Test_name:%s --- Units:%s \n",Test_name[i],Units[i]);
    }

}
#endif



void Read_Limit(double *Lowlimit,double *Highlimit,char *Test_name[],int *Test_number,char *Units[],int *Fail_Soft,int *Fail_Hard)
{
    string name = TheSoft.Flow().Test().GetCurrentTestName();
    map<string, tyLimitsData>::iterator iter;
    tyLimitsData tempLimitsData;
    vector<string> test_name;
    vector<double> lowlimit;
    vector<double> highlimit;
    vector<string> units;
    vector<ViUInt64> test_number;
    vector<ViUInt32> fail_sort;
    vector<ViUInt8> fail_bin;

    iter = mapLimits.find(name);
    if(iter != mapLimits.end())
    {
        tempLimitsData = iter->second;
//        flowtable = tempLimitsData.flowtable;

        if(strcmp("Default",CurrentLimitSet) == 0){
			lowlimit = tempLimitsData.Default_lolim;
			highlimit = tempLimitsData.Default_hilim;
        }
        else if(strcmp("Golden",CurrentLimitSet) == 0){
			lowlimit = tempLimitsData.Golden_lolim;
			highlimit = tempLimitsData.Golden_hilim;
        }
//        else if(CurrentLimitSet=="L40C_QA"){
//        lowlimit = tempLimitsData.L40C_QA_lolim;
//        highlimit = tempLimitsData.L40C_QA_hilim;
//        }
//        else if(CurrentLimitSet=="L40C"){
//        lowlimit = tempLimitsData.L40C_lolim;
//        highlimit = tempLimitsData.L40C_hilim;
//        }
        else if(strcmp("QA",CurrentLimitSet) == 0){
			lowlimit = tempLimitsData.QA_lolim;
			highlimit = tempLimitsData.QA_hilim;
        }
//        else if(CurrentLimitSet=="_105C_QA"){
//        lowlimit = tempLimitsData._105C_QA_lolim;
//        highlimit = tempLimitsData._105C_QA_hilim;
//        }
//        else if(CurrentLimitSet=="_105C"){
//        lowlimit = tempLimitsData._105C_lolim;
//        highlimit = tempLimitsData._105C_hilim;
//        }
        fail_sort = tempLimitsData.failsort;
        fail_bin = tempLimitsData.failbin;

        test_name = tempLimitsData.testname;
        test_number = tempLimitsData.testnumber;
        units = tempLimitsData.units;

    }

    for(unsigned int i = 0; i < lowlimit.size(); i++)
    {
       Lowlimit[i] = lowlimit[i];
       Highlimit[i] = highlimit[i];
       Test_number[i] = test_number[i];
       Fail_Soft[i]=fail_sort[i];
       Fail_Hard[i] = fail_bin[i];

       Test_name[i] = (char*)test_name[i].c_str();
       Units[i] = (char*)units[i].c_str();

       printf(".................... Test_name:%s --- Units:%s \n",Test_name[i],Units[i]);
    }

}

LONGLONG start(){
    	LARGE_INTEGER litmp;
    	LONGLONG T_st = 0;
    	QueryPerformanceCounter(&litmp);
    	T_st = litmp.QuadPart;
    	return T_st;
	}

void end(LONGLONG stime,string cout_name){
	LARGE_INTEGER litmp;
	LONGLONG T_sp = 0;
	double ddfreq;
	QueryPerformanceFrequency(&litmp);
	ddfreq = (double)litmp.QuadPart;
	QueryPerformanceCounter(&litmp);
	T_sp = litmp.QuadPart;
	double T_delay = (T_sp - stime)/ddfreq*1e3;
	cout << cout_name << T_delay<< "ms ----------------------------------------" << endl;

}


