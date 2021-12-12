#include "GetLog.h" 
#include "UserAPI.h" 
#include "UserDef.h"
#include "MT_DSP_Lib.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>
#include <numeric>
#include "CCS08F.h"
#include "RegDef.h"
#include "d2sProtocolSSI.h"
#include "DSP_test_ABB.h"
#include "Globle_Var.h"
//using namespace MuTest;
using namespace std;


int RX_DC_offset_cal_cpp(API * api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char RF_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_GC_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    
    CCIQResults IQResults;
    IQMeasureAttribute MeasureResult; 
    double I_LSB_mv;
    double Q_LSB_mv;

    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    Get_Signal_Name(RF_Test_Data, RF_GC_SrcSignal, Ana_CapSignal);

    if (strstr(testname, "2G") != NULL) {
        I_LSB_mv = 5.0;
        Q_LSB_mv = 5.0;
    } 
    else {
        I_LSB_mv = 5.3;
        Q_LSB_mv = 5.3;
    }
    
    //2. Get Passloss
    //pathloss = Read_Pathloss(testname);   //CC的ReadEeprom函数
    
    //3. DUT register setting: PLL, GAIN_MODE  
    Set_RF_RX_Pll_BW(api, (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);            
    Set_RF_RX_GainMode(api,RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);
    
    if (strstr(testname, "C0") != NULL) {
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", d2s_WorkMode);  
        d2sProtocolSSI d2s_test;
        d2s_test.SSI_write(0x200, 0x2000, false);
        d2s_test.SSI_write(0x202, 0x90, false);
        d2s_test.SSI_write(0x74, 0x8080);
        d2s::d2s_LABEL_END();
    }
    else{
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", d2s_WorkMode);  
        d2sProtocolSSI d2s_test;
        d2s_test.SSI_write(0x200, 0x2000, false);
        d2s_test.SSI_write(0x202, 0x90, false);
        d2s_test.SSI_write(0x78, 0x8080);
        d2s::d2s_LABEL_END();
    }
        
    
     CCRFTester.SelectSites("Site0, Site2");
     CapUtilitySites0(api);
     api->sleep(0.005);                                                          //add for relay stable @20210408
    //4. Load source and capture signal  
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Configure();

    //5. Trigger capture signal, get wave, calculate gain
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Read(&IQResults);
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Stop();
      
    CCRFTester.SelectSites("Site1, Site3");
    CapUtilitySites1(api);
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Read(&IQResults);
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Stop();
    CapUtilitySites0(api);                                                      //recover Rely state
    
    long FFT_Size=RF_Test_Data.tyCapSigSet.dSampleSize;
    double *Inreal = new double[FFT_Size];
    double *Inimag = new double[FFT_Size];
    double *SpectrumTemp_I = new double[FFT_Size];
    double *SpectrumTemp_Q = new double[FFT_Size];
    map<int, long long> DCOC_Code;
    FOREACH_ACTIVE_SITE(api){
            int site_id = api->Get_active_site();
            Testsoftbin[site_id] = 1;//softbin flag
            MeasureResult = IQResults[site_id];//IQResults[site_id];
//            //PlotCurve(api, &MeasureResult, "DCOC");
            if(MeasureResult.actualSamples >= FFT_Size)                         //Ensure the samples number larger than FFT_SIZE
            {
                for(int i = 0; i < FFT_Size; i++)
                {
                    Inreal[i] = MeasureResult.pComplexData[i].real;
                    Inimag[i] = MeasureResult.pComplexData[i].imaginary;
                }
            }
            
            double vOffset_I_Pre = std::accumulate(Inreal, Inreal+FFT_Size, 0.0)/FFT_Size*2;
            double vOffset_Q_Pre = std::accumulate(Inimag, Inimag+FFT_Size, 0.0)/FFT_Size*2;
            
            long long DCOC_I_Cal_Code = 0x80-floor(vOffset_I_Pre*1000/I_LSB_mv+0.5);
            long long DCOC_Q_Cal_Code = 0x80-floor(vOffset_Q_Pre*1000/Q_LSB_mv+0.5);
            
            if(DCOC_I_Cal_Code>255){
                DCOC_I_Cal_Code=255;
            }
            else if(DCOC_I_Cal_Code<0){
                DCOC_I_Cal_Code=0;
            }
            
            if(DCOC_Q_Cal_Code>255){
                DCOC_Q_Cal_Code=255;
            }
            else if(DCOC_Q_Cal_Code<0){
                DCOC_Q_Cal_Code=0;
            }
            DCOC_Code[site_id]= DCOC_I_Cal_Code+(DCOC_Q_Cal_Code<<8);
           
            ValueTest (api, Ana_CapPin, vOffset_I_Pre, lowl[0], hil[0], "V", Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
            ValueTest (api, Ana_CapPin, vOffset_Q_Pre, lowl[1], hil[1], "V", Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
            ValueTest (api, Ana_CapPin, DCOC_Code[site_id], lowl[2], hil[2], Units[2], Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);
            
    }
                    
    if (strstr(testname, "C0") != NULL) {  
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "dynamic", d2s_WorkMode);
        d2sProtocolSSI d2s_test;
        d2s_test.SSI_writeDynamic(0x74,DCOC_Code,"write");//SSI_write(0x74, 0x8080);
        d2s::d2s_LABEL_END();       
    } else {
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "dynamic", d2s_WorkMode);
        d2sProtocolSSI d2s_test;
        d2s_test.SSI_writeDynamic(0x78,DCOC_Code,"write");
        d2s::d2s_LABEL_END();
    }     
    
     CCRFTester.SelectSites("Site0, Site2");
     CapUtilitySites0(api);
     api->sleep(0.005);                                                          //add for relay stable @20210408
    //4. Load source and capture signal  
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Configure();

    //5. Trigger capture signal, get wave, calculate gain
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Read(&IQResults);
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Stop();
      
    CCRFTester.SelectSites("Site1, Site3");
    CapUtilitySites1(api);
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Read(&IQResults);
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Stop();
    CapUtilitySites0(api);                                                      //recover Rely state
    
    FOREACH_ACTIVE_SITE(api){
            int site_id = api->Get_active_site();
            MeasureResult = IQResults[site_id];//IQResults[site_id];
            //PlotCurve(api, &MeasureResult, "DCOC");
            if(MeasureResult.actualSamples >= FFT_Size)                         //Ensure the samples number larger than FFT_SIZE
            {
                for(int i = 0; i < FFT_Size; i++)
                {
                    Inreal[i] = MeasureResult.pComplexData[i].real;
                    Inimag[i] = MeasureResult.pComplexData[i].imaginary;
                }
            }
            
            double vOffset_I_Post = std::accumulate(Inreal, Inreal+FFT_Size, 0.0)/FFT_Size*2;
            double vOffset_Q_Post = std::accumulate(Inimag, Inimag+FFT_Size, 0.0)/FFT_Size*2;         
            
            ValueTest (api, Ana_CapPin, vOffset_I_Post, lowl[3], hil[3], "V", Test_Item[3], "FAIL_BIN", Test_number[3], Clogenable);
            ValueTest (api, Ana_CapPin, vOffset_Q_Post, lowl[4], hil[4], "V", Test_Item[4], "FAIL_BIN", Test_number[4], Clogenable);
            if(Testsoftbin[site_id]!=1){
                api->Set_result_bin(Testsoftbin[site_id]);
                } 

    }
                    
    delete[] Inreal;
    delete[] Inimag;
    delete[] SpectrumTemp_I;
    delete[] SpectrumTemp_Q;                
                    
    return EXIT_SUCCESS;
}

int RX_Gain_cpp(API * api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char RF_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    
    bool complexGainFlag = 0;
    
    CCIQResults IQResults;
    IQMeasureAttribute MeasureResult;  
    int Spectrum_I = 0;
    int Spectrum_Q = 0;
    double dwPeakPower_I = 0, dwPeakPower_Q = 0;
    double dwTestFreq = 0;                        //指定测试的频点   
    double pathloss[4];
    double GAIN_I[4] = {0};
    double GAIN_Q[4] = {0};
    int index = 0;
    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    Get_Signal_Name(RF_Test_Data, RF_SrcSignal, Ana_CapSignal);
    
    complexGainFlag = RF_Test_Data.bComplexGain;

    //2. Get Passloss
    Read_Pathloss(RF_Test_Data, pathloss) ;
    
    //3. DUT register setting:  WL_5G_CAL_Code, PLL, Filter  
    //iMode：2G/5G；iBand = Fre 全是枚举类型，以一定的格式区分 参考TX_Power_Trim_Function函数
    Set_RF_RX_Pll_BW(api, (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
    Set_RF_RX_GainMode(api,RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);
    
    CCRFTester.SelectSites("Site0, Site2");
    CapUtilitySites0(api);
    
    //4. Load source and capture signal
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Start();
    
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Configure();

    //5. Trigger capture signal, get wave, calculate gain
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Start();
    //这边需要根据read回来的数据做一些运算(有IQ数据，通过mx库计算得到Spectrum))
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Read(&IQResults);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Stop();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Stop();
    
    CCRFTester.SelectSites("Site1, Site3");
    CapUtilitySites1(api);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Start();
    
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Read(&IQResults);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Stop();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Stop();
    CapUtilitySites0(api);                                                      //recover Rely state

    dwTestFreq = RF_Test_Data.tyRXTest.dDf1;     //请在这里输入要获取Power的频点
    FOREACH_ACTIVE_SITE(api){
            int site_id = api->Get_active_site();
            MeasureResult = IQResults[site_id];
            //PlotCurve(api, &MeasureResult, "Gain");
            FFTFromIQData(api, &MeasureResult, &Spectrum_I, &Spectrum_Q);  //根据IQ数据分别I路FFT，Q路FFT
            GetPowerofSpecifiedFreq((double*)Spectrum_I, (double*)Spectrum_Q, dwTestFreq, RF_Test_Data.tyCapSigSet.dSampleRate, RF_Test_Data.tyCapSigSet.dSampleSize, dwPeakPower_I, dwPeakPower_Q, 7);
            GAIN_I[site_id]=dwPeakPower_I-RF_Test_Data.tyRXTest.dP1+pathloss[site_id];
            GAIN_Q[site_id]=dwPeakPower_Q-RF_Test_Data.tyRXTest.dP1+pathloss[site_id];
            //以下可以打印PeakPower，如果要保存数据注意多site需要分配数组
            ValueTest (api, Ana_CapPin, GAIN_I[site_id], lowl[0], hil[0], "dB", Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
            ValueTest (api, Ana_CapPin, GAIN_Q[site_id], lowl[1], hil[1], "dB", Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
    }
    
    //6. Save Gain, retrieve gain of LNA stage

    RX_GAIN_I_LIST.Insert(RF_Test_Data.cRxFreq,RF_Test_Data.cGainMode,sizeof(GAIN_I)/sizeof(double),GAIN_I);
    RX_GAIN_Q_LIST.Insert(RF_Test_Data.cRxFreq,RF_Test_Data.cGainMode,sizeof(GAIN_Q)/sizeof(double),GAIN_Q);

    index = RX_GAIN_I_LIST.FindIndex(RF_Test_Data.cRxFreq,RF_Test_Data.cGainMode);
    
    if(index == 0){
        FOREACH_ACTIVE_SITE(api){
            int site_id = api->Get_active_site();
            if(strstr(testname , "C0_RFI_")!=NULL){
                RX_GAIN_MAX_I_C0[RF_Test_Data.iBand][site_id] = GAIN_I[site_id];
            }
            else if(strstr(testname , "C1_RFI_")!=NULL){
                RX_GAIN_MAX_I_C1[RF_Test_Data.iBand][site_id] = GAIN_I[site_id];;
            }
        }
    }
    double GainStep_I = 0;
    double GainStep_Q = 0;
    if(RF_Test_Data.iLNA_Stage_Num >= 0){
        Last_Gain_I = RX_GAIN_I_LIST.Get(RF_Test_Data.cRxFreq,index-1);
        Last_Gain_Q = RX_GAIN_Q_LIST.Get(RF_Test_Data.cRxFreq,index-1); 
        
        FOREACH_ACTIVE_SITE(api){
            int site_id = api->Get_active_site();
            GainStep_I = Last_Gain_I[site_id] - GAIN_I[site_id];
            GainStep_Q = Last_Gain_Q[site_id] - GAIN_Q[site_id];
            ValueTest (api, Ana_CapPin, GainStep_I, lowl[2], hil[2], "dB", Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);
            ValueTest (api, Ana_CapPin, GainStep_Q, lowl[3], hil[3], "dB", Test_Item[3], "FAIL_BIN", Test_number[3], Clogenable);
            
        }
    }   
  
    return EXIT_SUCCESS;
}

int RX_IIP3_Fund_Tone_Inband_cpp(API * api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char RF_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_IIP3_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_IIP3_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};

    CCIQResults IQResults;
    IQMeasureAttribute MeasureResult; 
    int Spectrum_I = 0, Spectrum_Q = 0;
    double out_Power_I =0.0, out_Power_Q =0.0;
    double dwIMD3Val_I = 0.0, dwIMD3Val_Q = 0.0;
    double dwIIP3Val_I = 0.0, dwIIP3Val_Q = 0.0;
    double pathloss[4];
    double pathloss_average = 0.0;
    double pathloss_IQ = 0.0;
    double GAIN_I = 0.0;
    double GAIN_Q = 0.0;
    int site_cnt = 0;
    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    Get_Signal_Name(RF_Test_Data, RF_IIP3_SrcSignal, Ana_IIP3_CapSignal); 
    
    if(strstr(testname , "C0")!= NULL){
        pathloss_IQ = 1.0 ;   //only for dual tone
    }
    else{
        pathloss_IQ = 2.0 ;  ////only for dual tone
    }
    //2. Get Passloss
    Read_Pathloss(RF_Test_Data, pathloss) ;
    //取pathloss的平均值
    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site();
        pathloss_average=pathloss_average+pathloss[site_id];
        site_cnt = site_cnt + 1;
    }
    if(site_cnt)
        pathloss_average=pathloss_average/site_cnt - pathloss_IQ;   //1dB for IQ loss
    
    //3. DUT register setting:  WL_5G_CAL_Code, PLL, Filter  
    //iMode：2G/5G；iBand = Fre 全是枚举类型，以一定的格式区分 参考TX_Power_Trim_Function函数
    Set_RF_RX_Pll_BW(api, (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
    Set_RF_RX_GainMode(api,RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);
    
    CCRFTester.SelectSites("Site0, Site2");
    CapUtilitySites0(api);
    //4. Load source and capture signal
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP3_SrcSignal).Configure(); 
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP3_SrcSignal).Update(selectFrequency(RF_Test_Data.cRxFreq),RF_Test_Data.tyRXTest.dP1+pathloss_average + 3);  //3dB for dual tone
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP3_SrcSignal).Start();
    
    //5. Trigger capture signal, get wave, calculate IIP3
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP3_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP3_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP3_CapSignal).Read(&IQResults);
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP3_CapSignal).Stop();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP3_SrcSignal).Stop();
    
    CCRFTester.SelectSites("Site1, Site3"); 
    CapUtilitySites1(api);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP3_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP3_SrcSignal).Update(selectFrequency(RF_Test_Data.cRxFreq),RF_Test_Data.tyRXTest.dP1+pathloss_average + 3);  //3dB for dual tone
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP3_SrcSignal).Start();
    
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP3_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP3_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP3_CapSignal).Read(&IQResults);
    
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP3_CapSignal).Stop();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP3_SrcSignal).Stop();
    CapUtilitySites0(api);                                                      //recover Rely state
    
    FOREACH_ACTIVE_SITE(api){
            int site_id = api->Get_active_site();
            MeasureResult = IQResults[site_id];
//            PlotCurve(api, &MeasureResult, "IIP3");
            FFTFromIQData(api, &MeasureResult, &Spectrum_I, &Spectrum_Q);  //根据IQ数据分别I路FFT，Q路FFT
            GetIMD3FromIQData((double*)Spectrum_I, (double*)Spectrum_Q, RF_Test_Data.tyRXTest.dDf1, RF_Test_Data.tyRXTest.dDf2,\
                              RF_Test_Data.tyCapSigSet.dSampleRate, RF_Test_Data.tyCapSigSet.dSampleSize, dwIMD3Val_I, dwIMD3Val_Q, out_Power_I, out_Power_Q);
            GAIN_I = out_Power_I - RF_Test_Data.tyRXTest.dP1 + pathloss_IQ;
            GAIN_Q = out_Power_Q - RF_Test_Data.tyRXTest.dP1 + pathloss_IQ;
            dwIIP3Val_I = dwIMD3Val_I / 2 + RF_Test_Data.tyRXTest.dP1;
            dwIIP3Val_Q = dwIMD3Val_Q / 2 + RF_Test_Data.tyRXTest.dP1;
            
            ValueTest (api, Ana_CapPin, GAIN_I, lowl[0], hil[0], "dB", Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
            ValueTest (api, Ana_CapPin, GAIN_Q, lowl[1], hil[1], "dB", Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
            ValueTest (api, Ana_CapPin, dwIIP3Val_I, lowl[2], hil[2], "dB", Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);
            ValueTest (api, Ana_CapPin, dwIIP3Val_Q, lowl[3], hil[3], "dB", Test_Item[3], "FAIL_BIN", Test_number[3], Clogenable);
    }
    
    return EXIT_SUCCESS;
}

int WL_RX_EVM_cpp(API *api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char RF_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_EVM_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_EVM_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};

    double EVM;
    
    CCMxWlanResults MxWlanResults;
    WlanResultsAttribute MeasureResult;
    
    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    Get_Signal_Name(RF_Test_Data, RF_EVM_SrcSignal, Ana_EVM_CapSignal); 
    
    //2. DUT register setting: BW, PLL, gain mode
    Set_RF_RX_Pll_BW(api, (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
    Set_RF_RX_GainMode(api,RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);

    CCRFTester.SelectSites("Site0, Site2");
    CapUtilitySites0(api);
    //3. Load source and capture signal
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_EVM_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_EVM_SrcSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_EVM_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_EVM_CapSignal).Start();
//    api->sleep(0.01);
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_EVM_CapSignal).Read(&MxWlanResults);
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_EVM_CapSignal).Stop();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_EVM_SrcSignal).Stop();
    
    CCRFTester.SelectSites("Site1, Site3"); 
    CapUtilitySites1(api);

    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_EVM_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_EVM_SrcSignal).Start(); 
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_EVM_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_EVM_CapSignal).Start();
//    api->sleep(0.01);
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_EVM_CapSignal).Read(&MxWlanResults);
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_EVM_CapSignal).Stop();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_EVM_SrcSignal).Stop(); 
    CapUtilitySites0(api);                                                      //recover Rely state
    
    FOREACH_ACTIVE_SITE(api){
            int site_id = api->Get_active_site();
            MeasureResult = MxWlanResults[site_id];
            EVM=MeasureResult.OFDMM.CompositeRMSEVM.dCompositeRMSEVMMean;

            ValueTest (api, RF_SrcPin, 100*pow(10,(EVM/20)), lowl[0], hil[0], Units[0], Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable); 
    }

    return EXIT_SUCCESS;
}

int WL_RX_COMPLEX_NF_cpp(API *api)
{
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char RF_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_NF_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_NF_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    
    CCIQResults IQResults;
    IQMeasureAttribute MeasureResult; 
    int Spectrum_I = 0, Spectrum_Q = 0;
    
    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    Get_Signal_Name(RF_Test_Data, RF_NF_SrcSignal, Ana_NF_CapSignal); 
    
    //2. DUT register setting: BW, PLL, gain mode
    Set_RF_RX_Pll_BW(api, (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
    Set_RF_RX_GainMode(api,RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);
    
    CCRFTester.SelectSites("Site0, Site2");
    CapUtilitySites0(api);
    //3. Disconnect source pin 
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_NF_SrcSignal).Stop();
    
    //4. Load capture signal
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Read(&IQResults);
    
    CCRFTester.SelectSites("Site1, Site3");  
    CapUtilitySites1(api);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_NF_SrcSignal).Stop();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Read(&IQResults);
    CapUtilitySites0(api);                                                      //recover Rely state
    
    FOREACH_ACTIVE_SITE(api){
            int site_id = api->Get_active_site();
            MeasureResult = IQResults[site_id];
            FFTFromIQData(api, &MeasureResult, &Spectrum_I, &Spectrum_Q);  //根据IQ数据分别I路FFT，Q路FFT
            //具体需求请添加，注意上述的Spectrum_I和Spectrum_Q是每个频点的RMS值
            //以下可以打印PeakPower，如果要保存数据注意多site需要分配数组
    }
    
    //5. Calculate NF
//    rundsp.Calc_RX_NF_Complex CapWav_I, CapWav_Q, NF_Freq_Pos_L, NF_Freq_Pos_H, _
//                                                    NF_Freq_Neg_L, NF_Freq_Neg_H, _
//                                                    NF_Pos_w_Gain, NF_neg_w_Gain
    
    //6. Load Gain
    
    
    //7. Output test result

    
    return EXIT_SUCCESS;
}

int WL_RX_GC_cpp(API *api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    string strTestName = "";
    char RF_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_GC_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_GC_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    
    bool complexGainFlag = 0;
    
    CCIQResults IQResults;
    IQMeasureAttribute MeasureResult;  
    double dwTestFreq = 0;
    int Spectrum_I = 0, Spectrum_Q = 0;
    double dwPeakPower_I = 0, dwPeakPower_Q = 0;
    double Gain_I_GC;
    double Gain_Q_GC;
    double pathloss[4];
    double* Gain_I_Max;
    double* Gain_Q_Max;
    int index = 0;
    
    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    Get_Signal_Name(RF_Test_Data, RF_GC_SrcSignal, Ana_GC_CapSignal); 
    
    complexGainFlag = RF_Test_Data.bComplexGain;
    
    Read_Pathloss(RF_Test_Data, pathloss) ;
    
    //2. DUT register setting: BW, PLL, gain mode
    Set_RF_RX_Pll_BW(api, (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
    Set_RF_RX_GainMode(api,RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);

    CCRFTester.SelectSites("Site0, Site2");
    CapUtilitySites0(api);
    //3. Load source and capture signal
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_GC_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_GC_SrcSignal).Start();
    
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_GC_CapSignal).Configure();
    
    //4. Trigger capture signal, get wave, calculate gain
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_GC_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_GC_CapSignal).Read(&IQResults);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_GC_SrcSignal).Stop();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_GC_CapSignal).Stop();

    CCRFTester.SelectSites("Site1, Site3");
    CapUtilitySites1(api);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_GC_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_GC_SrcSignal).Start();
    
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_GC_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_GC_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_GC_CapSignal).Read(&IQResults); 
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_GC_SrcSignal).Stop();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_GC_CapSignal).Stop();
    CapUtilitySites0(api);                                                      //recover Rely state
    
    //5. Calculate GC
    index = RX_GAIN_I_LIST.FindIndex(RF_Test_Data.cRxFreq,RF_Test_Data.cGainMode);
    Gain_I_Max = RX_GAIN_I_LIST.Get(RF_Test_Data.cRxFreq,index);
    Gain_Q_Max = RX_GAIN_Q_LIST.Get(RF_Test_Data.cRxFreq,index);
    dwTestFreq = RF_Test_Data.tyRXTest.dDf1;     //请在这里输入要获取Power的频点
    strTestName = testname;
    if(strTestName.find("WL_RX_5G") < strTestName.length())
    {
        
    }
    else
    {
        FOREACH_ACTIVE_SITE(api){
            int site_id = api->Get_active_site();
            MeasureResult = IQResults[site_id];
            //PlotCurve(api, &MeasureResult, "GC");
            FFTFromIQData(api, &MeasureResult, &Spectrum_I, &Spectrum_Q);  //根据IQ数据分别I路FFT，Q路FFT
            GetPowerofSpecifiedFreq((double*)Spectrum_I, (double*)Spectrum_Q, dwTestFreq, RF_Test_Data.tyCapSigSet.dSampleRate, RF_Test_Data.tyCapSigSet.dSampleSize, dwPeakPower_I, dwPeakPower_Q);
            Gain_I_GC = dwPeakPower_I - RF_Test_Data.tyRXTest.dP1+pathloss[site_id];
            Gain_Q_GC = dwPeakPower_Q - RF_Test_Data.tyRXTest.dP1+pathloss[site_id];
            //以下可以打印PeakPower，如果要保存数据注意多site需要分配数组
            
            ValueTest (api, Ana_CapPin, Gain_I_Max[site_id], lowl[0], hil[0], "dB", Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
            ValueTest (api, Ana_CapPin, Gain_Q_Max[site_id], lowl[1], hil[1], "dB", Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
            ValueTest (api, Ana_CapPin, Gain_I_Max[site_id]-Gain_I_GC, lowl[2], hil[2], "dB", Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);
            ValueTest (api, Ana_CapPin, Gain_Q_Max[site_id]-Gain_Q_GC, lowl[3], hil[3], "dB", Test_Item[3], "FAIL_BIN", Test_number[3], Clogenable);
            
        }
    }

    
    return EXIT_SUCCESS;
}

//计算指定level起来的时间
int Get_PowerUpTime(double *IQMeasData,long SampleSize,double SampleRate,  double *PowerUp_Time)
{    
    double waveDC = 0;
    double IQMeasDataSum = 0;
    //double *refwave = new double[128];
    double refamp = 0;
    double refSum = 0;
    double refSize = 128;
    double comSum = 0;
    double comamp = 0;
    double relative = 0;
    
    for(int i = 0;i<SampleSize;i++)
    {
        IQMeasDataSum = IQMeasDataSum + IQMeasData[i];
    }
    waveDC = IQMeasDataSum / SampleSize;
    for(int j = 0;j<SampleSize;j++)
    {
        IQMeasData[j] = IQMeasData[j]-waveDC;
    }
    for(int k =SampleSize-refSize; k<SampleSize;k++)
    {
        refSum = IQMeasData[k]*IQMeasData[k]+refSum;
    }
    refamp = refSum/refSize;
    /************************************************************************/
    int nStartIndex = 0;
    for(int m = 10;m < SampleSize-10;m++)
    {
        comSum = 0;
        for(int n = 0;n<10;n++)
        {
            comSum += IQMeasData[m+n];
        }
        comamp = comSum/10;
        if(fabs(IQMeasData[m] - comamp) > 0.05)
        {
            nStartIndex = m;
            break;
        }
    }
    
   
    for(int m = nStartIndex;m < SampleSize-refSize;m++)
    {
        comSum = 0;
        for(int n = 0;n<refSize;n++)
        {
            comSum = IQMeasData[m+n]*IQMeasData[m+n]+comSum;
        }
        comamp = comSum/refSize;
        relative = comamp/refamp;
        
        if(refamp>0&&relative>=0.891&&relative<1.585)
        {
            *PowerUp_Time = m/SampleRate*1e9 - 3300;   //33 cycles,10MHz pattern
            break;
        }     
    }
    
    
    /****************************************************************/

//    for(int m = nStartIndex;m<SampleSize-refSize;m++)
//    {
//        comSum = 0;
//        for(int n =0; n<refSize;n++)
//        {
//            comSum = IQMeasData[m+n]*IQMeasData[m+n]+comSum;
//        }
//        comamp = comSum/refSize;
//        
//        relative = comamp/refamp;
//        if(refamp>0&&relative>=0.891&&relative<1.585)
//        {
//            *PowerUp_Time = (m - nStartIndex - 4)/SampleRate*1e9;
//            break;
//        }     
//    }
    
    if((*PowerUp_Time < 0)&&(*PowerUp_Time > -3300))//change by CC ZJ 
    {
        *PowerUp_Time = 123.4;
    }
    else if(*PowerUp_Time <= -3300)
    {
        *PowerUp_Time = 0;
    }
    
    
    //delete[] refwave;
    
    return 0;
}

int Calc_PowerUpTime(IQMeasureAttribute *IQMeasData,double SampleRate,double *PowerUp_Time_I,double *PowerUp_Time_Q)
{
    double *Inreal, *Inimag;
    
    *PowerUp_Time_I = 123.4;
    *PowerUp_Time_Q = 123.4;
    
    if(IQMeasData->actualSamples > 0)                                           //ensure the samples number must larger than 0.
    {
        Inreal = new double[IQMeasData->actualSamples];
        Inimag = new double[IQMeasData->actualSamples];
        memset(Inreal, 0.0, sizeof(double)*IQMeasData->actualSamples);
        memset(Inimag, 0.0, sizeof(double)*IQMeasData->actualSamples);

        SplitIQData(IQMeasData, Inreal, Inimag);

    //    double tempI[4096] = {0};
    //    double tempQ[4096] = {0};
    //    for(int i =0;i<IQMeasData->actualSamples;i++)
    //    {
    //        tempI[i] = Inreal[i];
    //        tempQ[i] = Inimag[i];
    //    }

        Get_PowerUpTime(Inreal,IQMeasData->actualSamples,SampleRate, PowerUp_Time_I);
        Get_PowerUpTime(Inimag,IQMeasData->actualSamples,SampleRate, PowerUp_Time_Q);

        delete[] Inreal;
        delete[] Inimag;
    }
    return 0;
}

int WL_RX_PowerUpTime_cpp(API *api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char RF_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    
    bool site0_flag = false;
    
    double PowerUp_Time_I;
    double PowerUp_Time_Q;
    
    unsigned int sites[MAX_SITES] = {0}; 
    unsigned int active_sites_size = api->Get_active_sites(sites); 
    
    CCIQResults IQResults;
    IQMeasureAttribute MeasureResult;
    double dwTestFreq = 0.0;  
    
    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    Get_Signal_Name(RF_Test_Data, RF_SrcSignal, Ana_CapSignal); 

    //2. DUT register setting: BW, PLL, gain mode
    Set_RF_RX_Pll_BW(api, (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
    Set_RF_RX_GainMode(api,RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);
              
    CCRFTester.SelectSites("Site0, Site2");
    CapUtilitySites0(api);
    //3. Load source and capture signal
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Start();
    api->Execute_test("WL_RX_POWER_DOWN");
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Configure();
    //5. Trigger capture signal, get wave, calculate setting time
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Start();
    
    if(sites[0]!=0)
    {
        sites[3]=sites[2];
        sites[2]=sites[1];
        sites[1]=sites[0];
        sites[0]=0;
        api->Set_active_sites(sites,active_sites_size+1);
        site0_flag = true;
    }
    
    if(strstr(testname,"C0")!=NULL){
        api->Execute_test("WL_RX_C0_SETUPTIME");
    }
    else{
        api->Execute_test("WL_RX_C1_SETUPTIME");
    }
    
     if(site0_flag==true)
    {
        sites[0]=sites[1];
        sites[1]=sites[2];
        sites[2]=sites[3];
        sites[3]=0;
        api->Set_active_sites(sites,active_sites_size);
        CCRFTester.ActiveSites(sites,active_sites_size);                        //recover the sites information for RF
        site0_flag = false;
    } 
    
    CCRFTester.SelectSites("Site0, Site2");
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Read(&IQResults); 
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Stop();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Stop();
    
    CCRFTester.SelectSites("Site1, Site3");
    CapUtilitySites1(api);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Start();
    api->Execute_test("WL_RX_POWER_DOWN");
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Start();
    
    if(sites[0]!=0)
    {
        sites[3]=sites[2];
        sites[2]=sites[1];
        sites[1]=sites[0];
        sites[0]=0;
        api->Set_active_sites(sites,active_sites_size+1);
        site0_flag = true;
    } 
    
    if(strstr(testname,"C0")!=NULL){
        api->Execute_test("WL_RX_C0_SETUPTIME");
    }
    else{
        api->Execute_test("WL_RX_C1_SETUPTIME");
    }
    
    if(site0_flag==true)
    {
        sites[0]=sites[1];
        sites[1]=sites[2];
        sites[2]=sites[3];
        sites[3]=0;
        api->Set_active_sites(sites,active_sites_size);
        CCRFTester.ActiveSites(sites,active_sites_size);                        //recover the sites information for RF
        site0_flag = false;
    }
    
    CCRFTester.SelectSites("Site1, Site3");
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Read(&IQResults);   
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Stop();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Stop();
    CapUtilitySites0(api);                                                      //recover Rely state
   
    //FOR EACHSITE
    dwTestFreq = RF_Test_Data.tyRXTest.dDf1;
    FOREACH_ACTIVE_SITE(api){
            int site_id = api->Get_active_site();
            MeasureResult = IQResults[site_id];
//            if(strstr(testname,"C0")!=NULL){
//                PlotCurve(api, &MeasureResult, "SETUP_C0");
//            }
//            else{
//                PlotCurve(api, &MeasureResult, "SETUP_C1");
//            }
                        
            Calc_PowerUpTime(&MeasureResult,RF_Test_Data.tyCapSigSet.dSampleRate,&PowerUp_Time_I,&PowerUp_Time_Q);
          
            ValueTest (api, Ana_CapPin, PowerUp_Time_I, lowl[0], hil[0], "ns", Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
            ValueTest (api, Ana_CapPin, PowerUp_Time_Q, lowl[1], hil[1], "ns", Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
    }
    
    return EXIT_SUCCESS;
}


int RX_IIP2_Fund_Tone_Inband_cpp(API * api)
{
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char RF_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_IIP2_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_IIP2_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};

    CCIQResults IQResults;
    IQMeasureAttribute MeasureResult; 
    int Spectrum_I = 0, Spectrum_Q = 0;
    double BB_IIP2_IQ_Freq = 0;
    double dwIIP2Val_I = 0.0, dwIIP2Val_Q = 0.0;
    double dwPeakPower_I = 0.0, dwPeakPower_Q = 0.0;
    double pathloss[4];
    double pathloss_average=0.0;
    int site_cnt = 0;

    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    Get_Signal_Name(RF_Test_Data, RF_IIP2_SrcSignal, Ana_IIP2_CapSignal); 
    
     //2. Get Passloss
    Read_Pathloss(RF_Test_Data, pathloss) ;
    //取pathloss的平均值
    for(int i=0;i<4;i++){
        pathloss_average=pathloss_average+pathloss[i];
        site_cnt = site_cnt + 1;
    }
    pathloss_average=pathloss_average/site_cnt - 1;   //1dB for IQ loss
    
    //3. DUT register setting:  WL_5G_CAL_Code, PLL, Filter  
    //iMode：2G/5G；iBand = Fre 全是枚举类型，以一定的格式区分 参考TX_Power_Trim_Function函数
    Set_RF_RX_Pll_BW(api, (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
    Set_RF_RX_GainMode(api,RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);
    
    //4. Measure IIP2
    CCRFTester.SelectSites("Site0, Site2");
    CapUtilitySites0(api);
    //4.1 Load source signal
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP2_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP2_SrcSignal).Start();
    
    //4.2. Load capture signal, trigger capget wave, calculate IIP3
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP2_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP2_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP2_CapSignal).Read(&IQResults);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP2_SrcSignal).Stop();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP2_CapSignal).Stop();
    
    CCRFTester.SelectSites("Site1, Site3");
    CapUtilitySites1(api);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP2_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP2_SrcSignal).Start();
    
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP2_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP2_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP2_CapSignal).Read(&IQResults);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIP2_SrcSignal).Stop();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIP2_CapSignal).Stop();
    CapUtilitySites0(api);                                                      //recover Rely state
    
    //4.3 Calculate IIP2
    BB_IIP2_IQ_Freq = RF_Test_Data.tyRXTest.dDf2 - RF_Test_Data.dLO_Freq - RF_Test_Data.tyRXTest.dDf1;
    FOREACH_ACTIVE_SITE(api){
            int site_id = api->Get_active_site();
            MeasureResult = IQResults[site_id];
            FFTFromIQData(api, &MeasureResult, &Spectrum_I, &Spectrum_Q);  //根据IQ数据分别I路FFT，Q路FFT
            GetPowerofSpecifiedFreq((double*)Spectrum_I, (double*)Spectrum_Q, BB_IIP2_IQ_Freq, RF_Test_Data.tyCapSigSet.dSampleRate, RF_Test_Data.tyCapSigSet.dSampleSize, dwPeakPower_I, dwPeakPower_Q);
            //可根据PeakPower继续计算其余的，如果要保存数据注意多site需要分配数组
    }
    
    //4.4 Disconnect RF source pin
    
    
    //5. Output test result

    return EXIT_SUCCESS;
}


int RX_IIPX_cpp(API * api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char RF_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_IIPX_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_IIPX_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    
    long IIPx_Order = 0;
    double BB_IIPX_IQ_Freq = 0.0;
    
    CCIQResults IQResults;
    IQMeasureAttribute MeasureResult;  
    int Spectrum_I = 0, Spectrum_Q = 0;
    double dwPeakPower_I = 0.0, dwPeakPower_Q = 0.0;
    double dwIIPXVal_I = 0.0, dwIIPXVal_Q = 0.0;
    double pathloss[4];
    double pathloss_average=0.0;
    double pathloss_IQ = 0.0;
    double* Gain_I_Max;
    double* Gain_Q_Max;
    int index = 0;
    int site_cnt = 0;

    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    Get_Signal_Name(RF_Test_Data, RF_IIPX_SrcSignal, Ana_IIPX_CapSignal); 
    
    IIPx_Order = RF_Test_Data.iIIPX_Order;
    
    if(strstr(testname , "C0")!= NULL){
        pathloss_IQ = 3.0 ;
    }
    else{
        pathloss_IQ = 3.5 ;
    }
            
    //2. Get Passloss
    Read_Pathloss(RF_Test_Data, pathloss) ;
    //取pathloss的平均值
    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site();
        pathloss_average=pathloss_average+pathloss[site_id];
        site_cnt = site_cnt+1;
    }
    
    if(site_cnt)
        pathloss_average=pathloss_average/site_cnt - pathloss_IQ;   
    
    if(RF_SrcPin =="WL_RF_RFI_5G_C0"){
        pathloss_average = pathloss_average / 1.5;
    }
    //3. DUT register setting:  WL_5G_CAL_Code, PLL, Filter  
    Set_RF_RX_Pll_BW(api, (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
    Set_RF_RX_GainMode(api,RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);
      
    //get IIPX Freq
    if(IIPx_Order == 2)
    {
        BB_IIPX_IQ_Freq = fabs(RF_Test_Data.tyRXTest.dDf1 - RF_Test_Data.tyRXTest.dDf2);
    }
    else
    {
        BB_IIPX_IQ_Freq = 2*(RF_Test_Data.tyRXTest.dDf1 - RF_Test_Data.dLO_Freq) - RF_Test_Data.tyRXTest.dDf2;
    }
    
    CCRFTester.SelectSites("Site0, Site2");
    CapUtilitySites0(api);
    //4 Load source signal
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIPX_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIPX_SrcSignal).Update(RF_Test_Data.tyRXTest.dDf1-1e6,RF_Test_Data.tyRXTest.dP1 + pathloss_average + 3);  
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIPX_SrcSignal).Start();
    //5. Load capture signal, trigger capture signal, calculate gain
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIPX_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIPX_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIPX_CapSignal).Read(&IQResults);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIPX_SrcSignal).Stop();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIPX_CapSignal).Stop();
    
    CCRFTester.SelectSites("Site1, Site3");
    CapUtilitySites1(api);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIPX_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIPX_SrcSignal).Update(RF_Test_Data.tyRXTest.dDf1-1e6,RF_Test_Data.tyRXTest.dP1 + pathloss_average + 3);  
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIPX_SrcSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIPX_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIPX_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIPX_CapSignal).Read(&IQResults);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IIPX_SrcSignal).Stop();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IIPX_CapSignal).Stop();
    CapUtilitySites0(api);                                                      //recover Rely state

    //Calculate IIPX
    index = RX_GAIN_I_LIST.FindIndex(RF_Test_Data.cRxFreq,RF_Test_Data.cGainMode);
    Gain_I_Max = RX_GAIN_I_LIST.Get(RF_Test_Data.cRxFreq,index);
    Gain_Q_Max = RX_GAIN_Q_LIST.Get(RF_Test_Data.cRxFreq,index);
    FOREACH_ACTIVE_SITE(api){
            int site_id = api->Get_active_site();
            MeasureResult = IQResults[site_id];
//            PlotCurve(api, &MeasureResult, "IIP2");
            FFTFromIQData(api, &MeasureResult, &Spectrum_I, &Spectrum_Q);  //根据IQ数据分别I路FFT，Q路FFT
            GetPowerofSpecifiedFreq((double*)Spectrum_I, (double*)Spectrum_Q, BB_IIPX_IQ_Freq, RF_Test_Data.tyCapSigSet.dSampleRate, RF_Test_Data.tyCapSigSet.dSampleSize, dwPeakPower_I, dwPeakPower_Q);
            
            dwIIPXVal_I = 2*RF_Test_Data.tyRXTest.dP1 - dwPeakPower_I + Gain_I_Max[site_id];
            dwIIPXVal_Q = 2*RF_Test_Data.tyRXTest.dP1 - dwPeakPower_Q + Gain_Q_Max[site_id];
            
            ValueTest (api, Ana_CapPin, Gain_I_Max[site_id], lowl[0], hil[0], Units[0], Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
            ValueTest (api, Ana_CapPin, Gain_Q_Max[site_id], lowl[1], hil[1], Units[1], Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
            
            ValueTest (api, Ana_CapPin, dwIIPXVal_I, lowl[2], hil[2], Units[2], Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);
            ValueTest (api, Ana_CapPin, dwIIPXVal_Q, lowl[3], hil[3], Units[3], Test_Item[3], "FAIL_BIN", Test_number[3], Clogenable);

    }

    return EXIT_SUCCESS;
}

int RX_IRR_IF_cpp(API * api)
{
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char RF_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_IRR_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_IRR_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    
    CCIQResults IQResults;
    IQMeasureAttribute MeasureResult;  
    double dwTestFreq = 0;
    int Spectrum_I = 0, Spectrum_Q = 0;
    double dwPeakPower_I = 0, dwPeakPower_Q = 0;
    double dGain_I = 0, dGain_Q = 0;

    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    Get_Signal_Name(RF_Test_Data, RF_IRR_SrcSignal, Ana_IRR_CapSignal); 
    
    //2. Get Passloss
    //pathloss = Read_Pathloss(testname);   //CC的ReadEeprom函数

    //3. DUT register setting:  WL_5G_CAL_Code, PLL, Filter  
    Set_RF_RX_Pll_BW(api, (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
    Set_RF_RX_GainMode(api,RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);
    
    CCRFTester.SelectSites("Site0, Site2");
    CapUtilitySites0(api);
    //4 Load source and capture signal
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IRR_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IRR_SrcSignal).Start();

    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_CapSignal).Configure();
    
    //5. Trigger capture signal, get wave calculate
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_CapSignal).Read(&IQResults);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IRR_SrcSignal).Stop();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_CapSignal).Stop();
   
    CCRFTester.SelectSites("Site1, Site3");
    CapUtilitySites1(api);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IRR_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IRR_SrcSignal).Start();
    
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_CapSignal).Read(&IQResults);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IRR_SrcSignal).Stop();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_CapSignal).Stop();
    CapUtilitySites0(api);                                                      //recover Rely state
 
    //Calculate IIPX
    dwTestFreq = RF_Test_Data.tyRXTest.dDf1;
    FOREACH_ACTIVE_SITE(api){
            int site_id = api->Get_active_site();
            MeasureResult = IQResults[site_id];
            FFTFromIQData(api, &MeasureResult, &Spectrum_I, &Spectrum_Q);  //根据IQ数据分别I路FFT，Q路FFT
            GetPowerofSpecifiedFreq((double*)Spectrum_I, (double*)Spectrum_Q, dwTestFreq, RF_Test_Data.tyCapSigSet.dSampleRate, RF_Test_Data.tyCapSigSet.dSampleSize, dwPeakPower_I, dwPeakPower_Q);
            dGain_I = dwPeakPower_I - RF_Test_Data.tyRXTest.dP1;
            dGain_Q = dwPeakPower_Q - RF_Test_Data.tyRXTest.dP1;
            //以下可以打印PeakPower，如果要保存数据注意多site需要分配数组
    }

    return EXIT_SUCCESS;
}

int RX_Selectivity_cpp(API * api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char RF_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_Sel_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_Sel_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    
    CCIQResults IQResults;
    IQMeasureAttribute MeasureResult; 
    double dwTestFreq = 0;
    int Spectrum_I = 0, Spectrum_Q = 0;
    double dwPeakPower_I = 0.0, dwPeakPower_Q = 0.0;
    double Selectivity_Gain_I;
    double Selectivity_Gain_Q;
    double pathloss[4];
    double* Gain_I_Max;
    double* Gain_Q_Max;
    int index = 0;

    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    Get_Signal_Name(RF_Test_Data, RF_Sel_SrcSignal, Ana_Sel_CapSignal); 
 
    //2. Get Passloss
    Read_Pathloss(RF_Test_Data,pathloss);   

    //3. DUT register setting:  WL_5G_CAL_Code, PLL, Filter  
    Set_RF_RX_Pll_BW(api, (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
    Set_RF_RX_GainMode(api,RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);
    
    CCRFTester.SelectSites("Site0, Site2");
    CapUtilitySites0(api);
    //4 Load source and capture signal
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_Sel_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_Sel_SrcSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_Sel_CapSignal).Configure();
    
    //5. Trigger capture signal, get wave calculate
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_Sel_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_Sel_CapSignal).Read(&IQResults);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_Sel_SrcSignal).Stop();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_Sel_CapSignal).Stop();

   
    CCRFTester.SelectSites("Site1, Site3");
    CapUtilitySites1(api);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_Sel_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_Sel_SrcSignal).Start();
    
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_Sel_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_Sel_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_Sel_CapSignal).Read(&IQResults);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_Sel_SrcSignal).Stop();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_Sel_CapSignal).Stop();
    CapUtilitySites0(api);                                                      //recover Rely state
 
    index = RX_GAIN_I_LIST.FindIndex(RF_Test_Data.cRxFreq,RF_Test_Data.cGainMode);
    Gain_I_Max = RX_GAIN_I_LIST.Get(RF_Test_Data.cRxFreq,index);
    Gain_Q_Max = RX_GAIN_Q_LIST.Get(RF_Test_Data.cRxFreq,index);
    dwTestFreq = RF_Test_Data.tyRXTest.dDf1;
    FOREACH_ACTIVE_SITE(api){
            int site_id = api->Get_active_site();
            MeasureResult = IQResults[site_id];
            FFTFromIQData(api, &MeasureResult, &Spectrum_I, &Spectrum_Q);  //根据IQ数据分别I路FFT，Q路FFT
            GetPowerofSpecifiedFreq((double*)Spectrum_I, (double*)Spectrum_Q, dwTestFreq, RF_Test_Data.tyCapSigSet.dSampleRate, RF_Test_Data.tyCapSigSet.dSampleSize, dwPeakPower_I, dwPeakPower_Q);
            Selectivity_Gain_I = dwPeakPower_I - RF_Test_Data.tyRXTest.dP1 + pathloss[site_id];
            Selectivity_Gain_Q = dwPeakPower_Q - RF_Test_Data.tyRXTest.dP1 + pathloss[site_id];

            ValueTest (api, Ana_CapPin, Gain_I_Max[site_id] - Selectivity_Gain_I, lowl[0], hil[0], "dB", Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
            ValueTest (api, Ana_CapPin, Gain_Q_Max[site_id] - Selectivity_Gain_Q, lowl[1], hil[1], "dB", Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
            
    }

    //6 Disconnect RF source pin
    
    //7. Output test result

    return EXIT_SUCCESS;
}

int RX_NF_cpp(API * api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char RF_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_NF_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_NF_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    
    CCIQResults IQResults;
    IQMeasureAttribute MeasureResult; 
    double Noise_i=0,Noise_q=0;
    double Noise2_i=0,Noise2_q=0;
    double NF_I=0,NF_Q=0;
    double NF2_I=0,NF2_Q=0;
    
    double Noise_Freq_L;
    double Noise_Freq_H;
    double NF2_Freq_L;
    double NF2_Freq_H;
    
    long Noise_Bin_L;
    long Noise_Bin_H;
    long NF2_Bin_L;
    long NF2_Bin_H;

    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    Get_Signal_Name(RF_Test_Data, RF_NF_SrcSignal, Ana_NF_CapSignal); 
    
    if(strstr(testname,"2G")!=NULL){
        Noise_Freq_L=4e6;
        Noise_Freq_H=6e6;
        NF2_Freq_L=14e6;
        NF2_Freq_H=16e6;
    }
    else{
        Noise_Freq_L=1.1e6;
        Noise_Freq_H=1.9e6;
        NF2_Freq_L=6.1e6;
        NF2_Freq_H=6.9e6;
    }
        
    //2. DUT register setting:  WL_5G_CAL_Code, PLL, Filter  
    Set_RF_RX_Pll_BW(api, (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
    Set_RF_RX_GainMode(api,RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);
    
    CCRFTester.SelectSites("Site0, Site2");
    CapUtilitySites0(api);
    //3. Disconnect RF source pin
//    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_NF_SrcSignal).Stop();
    
    //4 Load capture signal, Trigger capture signal, get wave calculate
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Read(&IQResults);
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Stop();
    
    CCRFTester.SelectSites("Site1, Site3");
    CapUtilitySites1(api);
//    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_NF_SrcSignal).Stop();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Read(&IQResults);
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_NF_CapSignal).Stop();
    CapUtilitySites0(api);                                                      //recover Rely state

    //Calculate NF
    //FOR EACHSITE
    long FFT_Size=RF_Test_Data.tyCapSigSet.dSampleSize;
    double Res_Freq_NF=RF_Test_Data.tyCapSigSet.dSampleRate/RF_Test_Data.tyCapSigSet.dSampleSize;
    double *Inreal = new double[FFT_Size];
    double *Inimag = new double[FFT_Size];
    double *SpectrumTemp_I = new double[FFT_Size];
    double *SpectrumTemp_Q = new double[FFT_Size];
    FOREACH_ACTIVE_SITE(api){
            int site_id = api->Get_active_site();
            Testsoftbin[site_id] = 1;//softbin flag
            MeasureResult = IQResults[site_id];
            //PlotCurve(api, &MeasureResult, "NF");
            if(MeasureResult.actualSamples >= FFT_Size)                         //ensure the samples number larger than FFT_SIZE
            {
                for(int i = 0; i < FFT_Size; i++)
                {
                    Inreal[i] = MeasureResult.pComplexData[i].real;
                    Inimag[i] = MeasureResult.pComplexData[i].imaginary;
                }
            }
//            api->Set_curve_data("NF_real", 0, 1/40.96e6, 4096, Inreal);   //打印FFT波形
//            api->Set_curve_data("NF_image", 0, 1/40.96e6, 4096, Inimag);

            MT_FFT(api, FFT_Size, Inreal, Inreal, SpectrumTemp_I);
            MT_FFT(api, FFT_Size, Inimag, Inimag, SpectrumTemp_Q);

            for(unsigned i =0;i<FFT_Size;++i)
            {
                SpectrumTemp_I[i] = pow(SpectrumTemp_I[i],2);
                SpectrumTemp_Q[i] = pow(SpectrumTemp_Q[i],2);
            }
            
            Noise_Bin_L = int(Noise_Freq_L/Res_Freq_NF+0.5);
            Noise_Bin_H = int(Noise_Freq_H/Res_Freq_NF+0.5);
            NF2_Bin_L = int(NF2_Freq_L/Res_Freq_NF+0.5);
            NF2_Bin_H = int(NF2_Freq_H/Res_Freq_NF+0.5);

            Noise_i = std::accumulate(SpectrumTemp_I+Noise_Bin_L, SpectrumTemp_I+Noise_Bin_H, 0.0) + 1e-20;
            Noise_q = std::accumulate(SpectrumTemp_Q+Noise_Bin_L, SpectrumTemp_Q+Noise_Bin_H, 0.0) + 1e-20;
            NF_I=10*log10(1000*Noise_i/50)-10*log10((Noise_Bin_H-Noise_Bin_L)*Res_Freq_NF)+174-60;
            NF_Q=10*log10(1000*Noise_q/50)-10*log10((Noise_Bin_H-Noise_Bin_L)*Res_Freq_NF)+174-60;
            
            Noise2_i = std::accumulate(SpectrumTemp_I+NF2_Bin_L, SpectrumTemp_I+NF2_Bin_H, 0.0) + 1e-20;
            Noise2_q = std::accumulate(SpectrumTemp_Q+NF2_Bin_L, SpectrumTemp_Q+NF2_Bin_H, 0.0) + 1e-20;
            NF2_I=10*log10(1000*Noise2_i/50)-10*log10((NF2_Bin_H-NF2_Bin_L)*Res_Freq_NF)+174-60;
            NF2_Q=10*log10(1000*Noise2_q/50)-10*log10((NF2_Bin_H-NF2_Bin_L)*Res_Freq_NF)+174-60;
            
            if(NF_I>NF2_I){
                NF_I=NF2_I;
            }
            if(NF_Q>NF2_Q){
                NF_Q=NF2_Q;
            }
            
            ValueTest (api, Ana_CapPin, NF_I, lowl[0], hil[0], "dB", Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
            ValueTest (api, Ana_CapPin, NF_Q, lowl[1], hil[1], "dB", Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
            
            
    }
    delete[] Inreal;
    delete[] Inimag;
    delete[] SpectrumTemp_I;
    delete[] SpectrumTemp_Q;
    
    //5. Output test result
    
    if(strstr(testname,"2G_H_C0")!=NULL){                
        api->Execute_test("WL_RX_2G_M_C0_RFI_SWITCH_RESTORE"); 
    }
    else if(strstr(testname,"2G_H_C1")!=NULL){ 
        api->Execute_test("WL_RX_2G_M_C1_RFI_SWITCH_RESTORE"); 
    }
    else if(strstr(testname,"5G_B_C0")!=NULL){ 
        api->Execute_test("WL_RX_5G_B_C0_RFI_SWITCH_RESTORE"); 
    }
    else if(strstr(testname,"5G_B_C1")!=NULL){ 
        api->Execute_test("WL_RX_5G_B_C1_RFI_SWITCH_RESTORE"); 
    }
    
    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site();
        if(Testsoftbin[site_id]!=1){
         api->Set_result_bin(Testsoftbin[site_id]);
        } 
    } 
    return EXIT_SUCCESS;
}

int RX_IRR_IQ_cpp(API * api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char RF_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_IRR_IQ_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_IRR_IQ_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    
    CCRfmxSpecAnResults SpectrumResults;
    SpecAnResultAttribute MeasureResult;
    double dwTestFreq = 0, dwTestFreq_IRR = 0;
    double dwSignalPower = 0;
    double dwImagePower = 0;

    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    Get_Signal_Name(RF_Test_Data, RF_IRR_IQ_SrcSignal, Ana_IRR_IQ_CapSignal); 

    //2. DUT register setting:  WL_5G_CAL_Code, PLL, Filter  
    Set_RF_RX_Pll_BW(api, (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
    Set_RF_RX_GainMode(api,RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);

    CCRFTester.SelectSites("Site0, Site2");
    CapUtilitySites0(api);
    api->sleep(0.005);                                                          //add for relay stable @20210408
    //3. Load source and capture signal
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IRR_IQ_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IRR_IQ_SrcSignal).Start();
    
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_IQ_CapSignal).Configure();
    
    //4. Trigger capture signal, get wave calculate
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_IQ_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_IQ_CapSignal).Read(&SpectrumResults);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IRR_IQ_SrcSignal).Stop();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_IQ_CapSignal).Stop();
    //MeasureResult = SpectrumResults[0];

    CCRFTester.SelectSites("Site1, Site3");
    CapUtilitySites1(api);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IRR_IQ_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IRR_IQ_SrcSignal).Start();
    
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_IQ_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_IQ_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_IQ_CapSignal).Read(&SpectrumResults);
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_IRR_IQ_SrcSignal).Stop();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_IRR_IQ_CapSignal).Stop();
    CapUtilitySites0(api);                                                      //recover Rely state

    //Calculate IRR
    dwTestFreq = RF_Test_Data.tyRXTest.dDf1;
    dwTestFreq_IRR = -1 * RF_Test_Data.tyRXTest.dDf1;
    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site();
        MeasureResult = SpectrumResults[site_id];
        if(MeasureResult.dFrequencyIncrement > 0)
        {
            int nBin = (dwTestFreq - MeasureResult.dInitiaFrequency)/MeasureResult.dFrequencyIncrement;
            int nBin_Image = (dwTestFreq_IRR - MeasureResult.dInitiaFrequency)/MeasureResult.dFrequencyIncrement;

            Calc_Power_dbm(&MeasureResult, nBin, 3, &dwSignalPower, 0);
            Calc_Power_dbm(&MeasureResult, nBin_Image, 3, &dwImagePower, 0);
        }
        ValueTest (api, Ana_CapPin, dwSignalPower-dwImagePower, lowl[0], hil[0], "dB", Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
    } 
    //6. Output test result

    return EXIT_SUCCESS;
}

int RX_EOS_cpp(API * api)
{
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char RF_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_EOS_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_EOS_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};

    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    Get_Signal_Name(RF_Test_Data, RF_EOS_SrcSignal, Ana_EOS_CapSignal); 

    //2. DUT register setting:  WL_5G_CAL_Code, PLL, Filter  
    Set_RF_RX_Pll_BW(api, (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
    Set_RF_RX_GainMode(api,RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);

    //3. Load source and capture signal
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_EOS_SrcSignal).Configure();
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_EOS_SrcSignal).Start();
    
    //4. Disconnect RF source pin
    CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_EOS_SrcSignal).Stop();
    
    //5. Datalog

    return EXIT_SUCCESS;
}

int RX_SAT_DET_cpp(API * api)
{
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char RF_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_SAT_DET_SrcSignal[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_SAT_DET_CapSignal[_MAX_NAME_SIZE_RF] = {"\0"};

    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    Get_Signal_Name(RF_Test_Data, RF_SAT_DET_SrcSignal, Ana_SAT_DET_CapSignal); 

    //2. DUT register setting:  WL_5G_CAL_Code, PLL, Filter  
    Set_RF_RX_Pll_BW(api, (emMode)RF_Test_Data.iMode, (emRX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
    Set_RF_RX_GainMode(api,RF_Test_Data.cGainMode, (emMode)RF_Test_Data.iMode, RF_Test_Data.cChannel);

    return EXIT_SUCCESS;
}