#include "GetLog.h" 
#include "CCS08F.h"
//#include "Excel.h"
#include "UserAPI.h" 
#include "UserDef.h"
#include "RegDef.h"
#include "d2sProtocolSSI.h"
#include <string>
#include <math.h>
#include "D2S_CAL_Module.h"
#include <vector>
#include <string.h>
#include "linearfit.h"
#include "D2S_PMU_Module.h"
#include "Globle_Var.h"

//using namespace MuTest;

int TX_Power_Trim_Function(API * api, emMode Mode_Select,emTX_Band Band_Select,char *Channel, double *Pre_Output_Power,int *TrimData)
{
    char *Channel_p;
    Channel_p=strstr(Channel,"C0");
    double Exp_Power = 0;
    long retAddr = 0;
    
    switch(Mode_Select)
    {
        case(WLAN_2G_Mode):
        {
            Exp_Power = 20;
            if(Channel_p!=NULL)
            {
                switch(Band_Select)
                {
                    case(WLAN_2G_TX_L_Band):
                    {
                        retAddr = 0x98;  //reg38,2G_C0_L
                        break;
                    }
                    case(WLAN_2G_TX_M_Band):                   
                    {
                        retAddr = 0x94;  //reg37,2G_C0_M
                        break;
                    }
                    case(WLAN_2G_TX_H_Band):
                    {
                        retAddr = 0x90;  //reg36,2G_C0_H
                        break;
                    }
                }
                    
            }
            else
            {
                switch(Band_Select)
                {
                    case(WLAN_2G_TX_L_Band):
                    {
                        retAddr = 0xA8;  //reg42,2G_C1_L
                        break;
                    }
                    case(WLAN_2G_TX_M_Band):
                    {
                        retAddr = 0xA4;  //reg41,2G_C1_M
                        break;
                    }
                    case(WLAN_2G_TX_H_Band):
                    {
                        retAddr = 0xA0;  //reg40,2G_C1_H
                        break;
                    }
                }
            }
            break;
        }
        case(WLAN_5G_Mode):
        {
            Exp_Power = -8.2;
            if(Channel_p!=NULL)
            {
                switch(Band_Select)
                {
                    case(WLAN_5G_TX_B1_Band):
                    {//B1
                        retAddr = 0xC0;  //reg48,5G_C0_B1
                        break;
                    }
                    case(WLAN_5G_TX_B2_Band):
                    {//B2
                         retAddr = 0xC4; //reg49,5G_C0_B2
                         break;
                    }             
                    case(WLAN_5G_TX_B3_Band):
                    {//B3
                        retAddr = 0xC8;  //reg50,5G_C0_B3
                        break;
                    }            
                    case(WLAN_5G_TX_B4_Band):
                    {//B4
                        retAddr = 0xCC; //reg51,5G_C0_B4
                        break;
                    }            
                    case(WLAN_5G_TX_B5_Band):
                    {//B5
                        retAddr = 0xD0;  //reg52,5G_C0_B5
                        break;
                    }            
                    case(WLAN_5G_TX_B6_Band):
                    {//B6
                        retAddr = 0xD4;  //reg53,5G_C0_B6
                        break;
                    }
                    case(WLAN_5G_TX_B7_Band):
                    {//B7
                        retAddr = 0xD8;  //reg54,5G_C0_B7
                        break;
                    }
                }
            }
            else
            {
                
                switch(Band_Select)
                    case(WLAN_5G_TX_B1_Band):
                    {//B1
                        retAddr = 0xEC;  //reg59,5G_C1_B1
                        break;
                    }
                    case(WLAN_5G_TX_B2_Band):
                    {//B2
                         retAddr = 0xF0; //reg60,5G_C1_B2
                         break;
                    }             
                    case(WLAN_5G_TX_B3_Band):
                    {//B3
                        retAddr = 0xF4; //reg61,5G_C1_B3
                        break;
                    }
                    case(WLAN_5G_TX_B4_Band):
                    {//B4
                        retAddr = 0xF8;  //reg62,5G_C1_B4
                        break;
                    }
                    case(WLAN_5G_TX_B5_Band):
                    {//B5
                        retAddr = 0xFC;  //reg63,5G_C1_B5
                        break;
                    }
                    case(WLAN_5G_TX_B6_Band):
                    {//B6
                        retAddr = 0x100;  //reg64,5G_C1_B6
                        break;
                    }
                    case(WLAN_5G_TX_B7_Band):
                    {//B7
                        retAddr = 0x104;  //reg65,5G_C1_B7
                        break;
                    }
            }
            break;
        }
    }
    d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", d2s_WorkMode);   
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_read(retAddr, "retdata", 9);
    d2s::d2s_LABEL_END();
    
    map<int, long long> Basic_Upc;
    FOREACH_ACTIVE_SITE(api){
        long long read_data = d2s_test.getReadValue("retdata");
        int site_id = api->Get_active_site();
        Basic_Upc[site_id] = read_data & 0x3F;
        TrimData[site_id] = int(Basic_Upc[site_id] * pow(10,((Exp_Power - *(Pre_Output_Power+site_id)) / 20)) + 1);//+ 0.5);
        if(TrimData[site_id]>63){
            TrimData[site_id]=63;
        }
        if(TrimData[site_id]<1){
            TrimData[site_id]=1;
        }
      }
    //to be add
    d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", d2s_WorkMode);   
    d2s_test.SSI_read(retAddr,"modify_data",9);    
    d2s::d2s_LABEL_END();   
    map<int, long long> Modify_TrimData;
    FOREACH_ACTIVE_SITE(api){
        long long modify_value = d2s_test.getReadValue("modify_data");
        int site_id = api->Get_active_site();
        Modify_TrimData[site_id] = modify_value ;
        Modify_TrimData[site_id]=Modify_TrimData[site_id]&(0xFFC0);
        Modify_TrimData[site_id]=Modify_TrimData[site_id]|TrimData[site_id];
    }  
    d2s::d2s_LABEL_BEGIN(api, "burst_test", "dynamic", d2s_WorkMode);
    d2s_test.SSI_writeDynamic(retAddr,Modify_TrimData,"write");
    d2s::d2s_LABEL_END();
    
    return EXIT_SUCCESS;
}

int Calc_Power_dbm(SpecAnResultAttribute *ResultAttribute, int Exp_Bin, int index_bin_num,double *Pre_Output_Power,double pathloss)
{    
    double *Power_Buf;
    double Power_Max=-70;
    int Bin_dev;
    
    Power_Buf = new double[index_bin_num];
    for(int i=0;i<index_bin_num;i++)
    {
        Bin_dev = Exp_Bin+i-((index_bin_num-1)/2);
        Power_Buf[i] = (ResultAttribute->pPowerDataBuf)[Bin_dev];
        
        if((Power_Max>=Power_Buf[i])||(i == 0))
        {
            Power_Max = Power_Max;
        }
        else
        {
            Power_Max = Power_Buf[i];
        }
    }    
    
    *Pre_Output_Power = Power_Max + pathloss;//debug
    delete[] Power_Buf;
    return EXIT_SUCCESS; 
}

int TX_PowerTrim_cpp(API * api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char Ana_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_Src_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_Cap_Signal[_MAX_NAME_SIZE_RF] = {"\0"};

    long Exp_Bin = 0;
    volatile double Exp_Freq = 0;
    double pathloss[4];
    
    CCRfmxSpecAnResults mxSpecAnResults;  
    SpecAnResultAttribute ResultAttribute;    
    double Pre_Output_Power[4] = {0};
    int TrimData[4] = {0};
    
    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
    Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);
    Exp_Freq = selectFrequency(RF_Test_Data.cRxFreq) + RF_Test_Data.tyTXTest.dFreqSpacing;

    //2. Get Passloss
    Read_Pathloss(RF_Test_Data,pathloss);
    
    //3. Measre pre Power  
    //3.1  DUT register setting: cal code, PLL, gain
    Set_RF_TX_Pll_BW(api, (emMode)RF_Test_Data.iMode, (emTX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
   
    CCRFTester.SelectSites("site0,site2");
    SrcUtilitySites0(api);
    //3.2  Load source and capture signal
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();        
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
    
    //3.3  Trigger capture signal, get wave, calculate power
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);
    
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();  

    CCRFTester.SelectSites("site1,site3"); 
    SrcUtilitySites1(api);
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();
    
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
    //3.3  Trigger capture signal, get wave, calculate power
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);
    
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
    SrcUtilitySites0(api);                                                      //recover Relay state

    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site();       
        ResultAttribute = mxSpecAnResults[site_id]; 
        if(ResultAttribute.dwNumbersOfSpectrum > 0)
        {
            Exp_Bin = int((Exp_Freq - ResultAttribute.dInitiaFrequency)/ResultAttribute.dFrequencyIncrement);
            Calc_Power_dbm(&ResultAttribute,Exp_Bin,5,&Pre_Output_Power[site_id],pathloss[site_id]);
        }
    }                                  
    
              
    //4. Calculate trim code
    TX_Power_Trim_Function(api,(emMode)RF_Test_Data.iMode, (emTX_Band)RF_Test_Data.iBand, RF_Test_Data.cChannel,Pre_Output_Power,TrimData);
    
    //5. Output test result
    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site();
        if(strstr(testname , "C0")!=NULL){
            TRIM_DATA_LIST_C0[RF_Test_Data.iBand-10][site_id] = TrimData[site_id];
        }
        else {
            TRIM_DATA_LIST_C1[RF_Test_Data.iBand-10][site_id] = TrimData[site_id];
        }
        
        ValueTest (api, RF_CapPin, Pre_Output_Power[site_id], lowl[0], hil[0], Units[0], Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
        ValueTest (api, RF_CapPin, TrimData[site_id], (int)lowl[1], (int)hil[1], Units[1], Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
    }
    
    
    return EXIT_SUCCESS;
}

int TX_5G_PowerTrim_cpp(API * api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char Ana_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_Src_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_Cap_Signal[_MAX_NAME_SIZE_RF] = {"\0"};

    long Exp_Bin = 0;
    volatile double Exp_Freq = 0;
    double pathloss[4];
    
    CCRfmxSpecAnResults mxSpecAnResults;  
    SpecAnResultAttribute ResultAttribute;    
    double Pre_Output_Power[4] = {0};
    
    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
    Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);
    Exp_Freq = selectFrequency(RF_Test_Data.cRxFreq) + RF_Test_Data.tyTXTest.dFreqSpacing;
//    Exp_Freq=2443e6;

    //2. Get Passloss
    Read_Pathloss(RF_Test_Data,pathloss);
    
    //3. Measre pre Power  
    //3.1  DUT register setting: cal code, PLL, gain
    Set_RF_TX_Pll_BW(api, (emMode)RF_Test_Data.iMode, (emTX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
   
    CCRFTester.SelectSites("site0,site2");
    SrcUtilitySites0(api);
    //3.2  Load source and capture signal
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();        
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
    
    //3.3  Trigger capture signal, get wave, calculate power
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);
    
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();  

    CCRFTester.SelectSites("site1,site3"); 
    SrcUtilitySites1(api);
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();
    
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
    //3.3  Trigger capture signal, get wave, calculate power
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);
    
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
    SrcUtilitySites0(api);                                                      //recover Relay state

    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site();       
        ResultAttribute = mxSpecAnResults[site_id]; 
        if(ResultAttribute.dwNumbersOfSpectrum > 0)
        {
            Exp_Bin = int((Exp_Freq - ResultAttribute.dInitiaFrequency)/ResultAttribute.dFrequencyIncrement);
            Calc_Power_dbm(&ResultAttribute,Exp_Bin,5,&Pre_Output_Power[site_id],pathloss[site_id]);
        }
        ValueTest (api, RF_CapPin, Pre_Output_Power[site_id], lowl[0], hil[0], Units[0], Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
    }                                  
    
    return EXIT_SUCCESS;
}

int Calc_TX_Power_CR_SR(API *api,tyTestData *pRF_Test_Data,SpecAnResultAttribute *ResultAttribute,double pathloss,double *Post_Power,double *CR,double *SR)
{
    long Signal_Bin = 0;
    long Carrier_Bin = 0;
    long Image_Bin = 0;
    
    double Signal_dbm = 0;
    double Carrier_dbm = 0;
    double Image_dbm = 0;
    
    *Post_Power = 0;
    *CR = 0;
    *SR = 0;
    
    if(ResultAttribute->dwNumbersOfSpectrum > 0)                                //ensure the spectrum is valid.
    {
        Signal_Bin = int((pRF_Test_Data->dLO_Freq+ pRF_Test_Data->tyTXTest.dFreqSpacing- ResultAttribute->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);
        Carrier_Bin = int((pRF_Test_Data->dLO_Freq - ResultAttribute->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);
        Image_Bin = int((pRF_Test_Data->dLO_Freq - pRF_Test_Data->tyTXTest.dFreqSpacing- ResultAttribute->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);
    
        Calc_Power_dbm(ResultAttribute,Signal_Bin,3,&Signal_dbm,pathloss);
        Calc_Power_dbm(ResultAttribute,Carrier_Bin,3,&Carrier_dbm,pathloss);
        Calc_Power_dbm(ResultAttribute,Image_Bin,3,&Image_dbm,pathloss);
        
        *Post_Power = Signal_dbm;
        *CR = Signal_dbm - Carrier_dbm;
        *SR = Signal_dbm - Image_dbm;
    }           
}

int TX_Power_cpp(API *api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char Ana_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_Src_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_Cap_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
    
    CCRfmxSpecAnResults mxSpecAnResults;  
    SpecAnResultAttribute ResultAttribute;
    double pathloss[4];
    double Post_Power;
    double CR;
    double SR;
    
    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
    Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);
    
    //2. Get Passloss
    Read_Pathloss(RF_Test_Data,pathloss);

    CCRFTester.SelectSites("site0,site2");
    SrcUtilitySites0(api);
    //3.2  Load source and capture signal
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();        
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
    
    //3.3  Trigger capture signal, get wave, calculate power
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);
   
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();  
        
    CCRFTester.SelectSites("site1,site3"); 
    SrcUtilitySites1(api);
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();
    
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
    //3.3  Trigger capture signal, get wave, calculate power
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);
    
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
    SrcUtilitySites0(api);                                                      //recover Relay state
    
    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site(); 
        ResultAttribute = mxSpecAnResults[site_id];
        Calc_TX_Power_CR_SR(api,&RF_Test_Data,&ResultAttribute,pathloss[site_id],&Post_Power,&CR,&SR); 

        ValueTest (api, RF_CapPin, Post_Power, lowl[0], hil[0], Units[0], Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
        ValueTest (api, RF_CapPin, CR, lowl[1], hil[1], "dB", Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
        ValueTest (api, RF_CapPin, SR, lowl[2], hil[2], "dB", Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);
    }                               
    
    return EXIT_SUCCESS;
}

int TX_IDD_cpp(API *api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char Ana_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_Src_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_Cap_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
    
    unsigned int sitestmp[4] = {0,0,0,0};
    unsigned int sites[MAX_SITES] = {0}; 
    bool site0_flag = false;
    //bool site1_flag = false;
    bool site2_flag = false;
    //bool site3_flag = false;
    bool skip = false;
    unsigned int active_sites_size = api->Get_active_sites(sites);
    unsigned int active_sites_cnt=0;
    for(int i=0;i<4;i++)
    {
        sitestmp[i]=sites[i];
    }
    
    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
    Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);
    
    //2. Get Passloss

    CCRFTester.SelectSites("site0,site2");
    SrcUtilitySites0(api);
    //3.2  Load source and capture signal
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();        
   
    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site();
        if(site_id==0){
            site0_flag = true;   
        }
        if(site_id==2){
           site2_flag = true;
        }  
        Testsoftbin[site_id] = 1;
    }
    
    if(site0_flag == true&&site2_flag == true)
    {
        sites[0]=0;
        sites[1]=2;   
        active_sites_cnt=2;
    }
    else if(site0_flag == true&&site2_flag == false)
    {
        sites[0]=0;
        sites[1]=0; 
        active_sites_cnt=1;
    }
    else if(site0_flag == false&&site2_flag == true)
    {
        sites[0]=2;
        sites[1]=0;
        active_sites_cnt=1;
    }
    else
    {
        skip = true;
    }
    
    if(skip!=true)
    {
        sites[2]=0;
        sites[3]=0;
        api->Set_active_sites(sites,active_sites_cnt);

        if(strstr(testname,"C0")!=NULL){
            api->Execute_test("WL_TX_2G_M_C0_IDD");
        }
        else{
            api->Execute_test("WL_TX_2G_M_C1_IDD");
        }
        FOREACH_ACTIVE_SITE(api){
            int site_id = api->Get_active_site();
            
            if(Testsoftbin[site_id] == 1){
               Testsoftbin[site_id] = api->Get_result_bin();   
               }
        }
    }
    for(int i=0;i<4;i++)
    {
        sites[i]=sitestmp[i];
    }
    api->Set_active_sites(sites,active_sites_size);                             //recover the sites information for Mutest
    CCRFTester.ActiveSites(sites,active_sites_size);                            //recover the sites information for RF
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    
    site0_flag = false;
    site2_flag = false;
    skip = false;
    active_sites_cnt=0;
    
    //CCRFTester.ActiveSites("Site0,Site1,Site2,Site3");
    CCRFTester.SelectSites("Site1,Site3");
    
    SrcUtilitySites1(api);//////////////////////////////////////////////////////////////////////////////////////////////////////
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();  
    
    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site();
        if(site_id==1){
            site0_flag = true;   
        }
        if(site_id==3){
           site2_flag = true;
        }  
    }
    
    if(site0_flag == true&&site2_flag == true)
    {
        sites[0]=1;
        sites[1]=3;  
        active_sites_cnt=2;
    }
    else if(site0_flag == true&&site2_flag == false)
    {
        sites[0]=1;
        sites[1]=0; 
        active_sites_cnt=1;
    }
    else if(site0_flag == false&&site2_flag == true)
    {
        sites[0]=3;
        sites[1]=0; 
        active_sites_cnt=1;
    }
    else
    {
        skip = true;
    }
    
    if(skip!=true)
    {
        sites[2]=0;
        sites[3]=0;
        api->Set_active_sites(sites,active_sites_cnt);

        if(strstr(testname,"C0")!=NULL){
            api->Execute_test("WL_TX_2G_M_C0_IDD");
        }
        else{
            api->Execute_test("WL_TX_2G_M_C1_IDD");
        }
        
        FOREACH_ACTIVE_SITE(api){
            int site_id = api->Get_active_site();
            if(Testsoftbin[site_id] == 1){
               Testsoftbin[site_id] = api->Get_result_bin();   
               }
        }
    }
    for(int i=0;i<4;i++)
    {
        sites[i]=sitestmp[i];
    }
    api->Set_active_sites(sites,active_sites_size);                             //recover the sites information for Mutest
    CCRFTester.ActiveSites(sites,active_sites_size);                            //recover the sites information for RF
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    SrcUtilitySites0(api);                                                      //recover Relay state
    
    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site();
        if(Testsoftbin[site_id]!=1){
         api->Set_result_bin(Testsoftbin[site_id]);
        }
    }
 
    return EXIT_SUCCESS;
}

int calc_WL_TX_OIP3(API * api,tyTestData *pRF_Test_Data,SpecAnResultAttribute *ResultAttribute,double pathloss,double *Output_Power,double *Result_oip3)
{
    long fbin_fund = 0;
    
    long fbin_im3_1 = 0;
    long fbin_im3_2 = 0;
    
    double im_power1 = 0;
    double im_power2 = 0;
    double fund_power = 0;
    
    *Output_Power = 0;
    *Result_oip3 = 0;

    if(ResultAttribute->dwNumbersOfSpectrum > 0)                                //ensure the spectrum is valid.
    {
        fbin_fund = int((pRF_Test_Data->dLO_Freq+ pRF_Test_Data->tyTXTest.d2Tone_L- ResultAttribute->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);
        fbin_im3_1 = int(((pRF_Test_Data->dLO_Freq + pRF_Test_Data->tyTXTest.d2Tone_L *2 - pRF_Test_Data->tyTXTest.d2Tone_R) - ResultAttribute->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);
        fbin_im3_2 = int(((pRF_Test_Data->dLO_Freq + pRF_Test_Data->tyTXTest.d2Tone_R *2 - pRF_Test_Data->tyTXTest.d2Tone_L) - ResultAttribute->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);    

        Calc_Power_dbm(ResultAttribute,fbin_fund,3,&fund_power,pathloss);
        Calc_Power_dbm(ResultAttribute,fbin_im3_1,3,&im_power1,pathloss);
        Calc_Power_dbm(ResultAttribute,fbin_im3_2,3,&im_power2,pathloss);

        *Output_Power = fund_power;
        if(im_power1<im_power2)
        {
            *Result_oip3 = fund_power + (fund_power - im_power2)/2;
        }
        else
        {
            *Result_oip3 = fund_power + (fund_power - im_power1)/2;
        }    
    }
    return EXIT_SUCCESS;
}

int TX_OIP3_cpp(API * api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char Ana_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_Src_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_Cap_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
    double Output_Power;
    double Result_oip3;

    CCRfmxSpecAnResults mxSpecAnResults;  
    SpecAnResultAttribute ResultAttribute;
    double pathloss[4];

    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
    Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);
    
    //2. Get Passloss
    Read_Pathloss(RF_Test_Data,pathloss);
    
    Set_RF_TX_Pll_BW(api, (emMode)RF_Test_Data.iMode, (emTX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
    
    CCRFTester.SelectSites("site0,site2");
    SrcUtilitySites0(api);    
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
    
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);
    
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
      
    CCRFTester.SelectSites("site1,site3");
    SrcUtilitySites1(api);
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();
      
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);

    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop(); 
    SrcUtilitySites0(api);                                                      //recover Relay state
      
    FOREACH_ACTIVE_SITE(api){
        /* site: 0,2,3 */
        int site_id = api->Get_active_site(); 
        ResultAttribute = mxSpecAnResults[site_id];
        calc_WL_TX_OIP3(api,&RF_Test_Data,&ResultAttribute,pathloss[site_id], &Output_Power, &Result_oip3);
        
        ValueTest (api, RF_CapPin, Output_Power, lowl[0], hil[0], Units[0], Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
        ValueTest (api, RF_CapPin, Result_oip3, lowl[1], hil[1], Units[1], Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
    }
    return EXIT_SUCCESS;
}

int calc_WL_TX_OIP3_Dri_Mode(API * api,tyTestData *pRF_Test_Data,SpecAnResultAttribute *ResultAttribute,double pathloss, double *Output_Power,double *Result_im3,double *Result_oip3)
{
    long fbin_fund1 = 0;
    long fbin_fund2 = 0;  
    long fbin_im3_1 = 0;
    long fbin_im3_2 = 0;
    
    double im_power1 = 0;
    double im_power2 = 0;
    double fund_power1 = 0;
    double fund_power2 = 0;
    double fund_power = 0;

    *Output_Power = 0;
    *Result_im3 = 0;
    *Result_oip3 = 0;
        
    if(ResultAttribute->dwNumbersOfSpectrum > 0)                                //ensure the spectrum is valid.
    {
        fbin_fund1 = int((pRF_Test_Data->dLO_Freq+ pRF_Test_Data->tyTXTest.d2Tone_L- ResultAttribute->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);
        fbin_fund2 = int((pRF_Test_Data->dLO_Freq+ pRF_Test_Data->tyTXTest.d2Tone_R- (ResultAttribute)->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);
        fbin_im3_1 = int(((pRF_Test_Data->dLO_Freq + pRF_Test_Data->tyTXTest.d2Tone_L *2 - pRF_Test_Data->tyTXTest.d2Tone_R) - ResultAttribute->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);
        fbin_im3_2 = int(((pRF_Test_Data->dLO_Freq + pRF_Test_Data->tyTXTest.d2Tone_R *2 - pRF_Test_Data->tyTXTest.d2Tone_L) - ResultAttribute->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);    


        Calc_Power_dbm(ResultAttribute,fbin_fund1,3,&fund_power1,pathloss);
        Calc_Power_dbm(ResultAttribute,fbin_fund2,3,&fund_power2,pathloss);
        Calc_Power_dbm(ResultAttribute,fbin_im3_1,3,&im_power1,pathloss);
        Calc_Power_dbm(ResultAttribute,fbin_im3_2,3,&im_power2,pathloss);

        fund_power = (fund_power1+fund_power2)/2;
        *Output_Power = fund_power;

        if(im_power1<im_power2)
        {
            im_power1 = im_power2;
        }
        else
        {
            im_power1 = im_power1;     
        }        
        *Result_im3 = fund_power - im_power1;
        *Result_oip3 = fund_power + (fund_power - im_power1)/2;
    }       
    return EXIT_SUCCESS;
}

int WL_TX_OIP3_Dri_Mod_cpp(API * api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char Ana_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_Src_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_Cap_Signal[_MAX_NAME_SIZE_RF] = {"\0"};

    CCRfmxSpecAnResults mxSpecAnResults;  
    SpecAnResultAttribute ResultAttribute;
    double pathloss[4];
    double Output_Power;
    double Result_im3;
    double Result_oip3;
    
    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
    Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);
    
    //2. Get Passloss
    Read_Pathloss(RF_Test_Data,pathloss);
    
    Driver_Mode_Setup(api);
    
    /********************dynamic write UPC code***************************************
    d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_read(0x94, "OLD_TrimData_C0",9);//attention loss true
    d2s_test.SSI_read(0xA4, "OLD_TrimData_C1",9);//attention loss true    
    d2s::d2s_LABEL_END();
    
    map<int, long long> OLD_TrimData_C0;
    map<int, long long> OLD_TrimData_C1;    
    map<int, long long> TrimData_C0;
    map<int, long long> TrimData_C1;     
    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site();
        
        long long readvalue1 = d2s_test.getReadValue("OLD_TrimData_C0");
        long long readvalue2 = d2s_test.getReadValue("OLD_TrimData_C1");
        OLD_TrimData_C0[site_id] = readvalue1;
        OLD_TrimData_C1[site_id] = readvalue2;
        TrimData_C0[site_id] =  OLD_TrimData_C0[site_id] * 0.29 + 0.5;
        TrimData_C1[site_id] =  OLD_TrimData_C1[site_id] * 0.29 + 0.5;
        
        ValueTest (api, RF_CapPin, TrimData_C0[site_id], lowl[3], hil[3], "dB", "UPC_CODE_C0", "FAIL_BIN", Test_number[3], Clogenable);
        ValueTest (api, RF_CapPin, TrimData_C1[site_id], lowl[3], hil[3], "dB", "UPC_CODE_C1", "FAIL_BIN", Test_number[3], Clogenable);

    }
    d2s::d2s_LABEL_BEGIN(api, "burst_test", "dynamic", d2s_WorkMode);
    d2s_test.SSI_writeDynamic(0x94, TrimData_C0,"write"); //Set C0 M UPC Code
    d2s_test.SSI_writeDynamic(0xA4, TrimData_C1,"write"); //Set C1 M UPC Code
    d2s::d2s_LABEL_END();
    *******************************************************************/
    
    Set_RF_TX_Pll_BW(api, (emMode)RF_Test_Data.iMode, (emTX_Band)RF_Test_Data.iBand, RF_Test_Data.dBW, RF_Test_Data.cChannel);
    
    CCRFTester.SelectSites("site0,site2");
    SrcUtilitySites0(api);
    //3.2  Load source and capture signal
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();
    
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);
    
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
  
    CCRFTester.SelectSites("site1,site3");
    SrcUtilitySites1(api);
    //3.2  Load source and capture signal
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();
    
    //3.  Load capture signal  
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);
    
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
    SrcUtilitySites0(api);                                                      //recover Relay state
    
    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site();
        Testsoftbin[site_id] = 1;//softbin flag
        ResultAttribute = mxSpecAnResults[site_id];
        calc_WL_TX_OIP3_Dri_Mode(api,&RF_Test_Data,&ResultAttribute,pathloss[site_id], &Output_Power, &Result_im3, &Result_oip3);
        
        ValueTest (api, RF_CapPin, Output_Power, lowl[0], hil[0], Units[0], Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
        ValueTest (api, RF_CapPin, Result_im3, lowl[1], hil[1], Units[1], Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
        ValueTest (api, RF_CapPin, Result_oip3, lowl[2], hil[2], Units[2], Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);
    }
     
    /********************dynamic write UPC code***************************************
    d2s::d2s_LABEL_BEGIN(api, "burst_test", "dynamic", d2s_WorkMode);
    d2s_test.SSI_writeDynamic(0x94, OLD_TrimData_C0,"write"); //Set C0 M UPC Code
    d2s_test.SSI_writeDynamic(0xA4, OLD_TrimData_C1,"write"); //Set C1 M UPC Code
    d2s::d2s_LABEL_END();
     * *******************************************************************/

    Driver_Mode_Recover_Setup(api);
    
    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site();
        if(Testsoftbin[site_id]!=1){
         api->Set_result_bin(Testsoftbin[site_id]);
        }
    }
    return EXIT_SUCCESS;
}


int WL_TX_EVM_cpp(API * api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char Ana_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_Src_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_Cap_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
    
    CCMxWlanResults MxWlanResults;
    WlanResultsAttribute ResultsAttribute;
    double EVM;
    double EVM_Power_Abs;
    double pathloss[4];
    
    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
    Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);
    
    //2. Get Passloss
    Read_Pathloss(RF_Test_Data,pathloss);
    
    //3. DUT register setting  
    TX_PLL_Setup(api, (emMode)RF_Test_Data.iMode, (emTX_Band)RF_Test_Data.iBand, RF_Test_Data.cChannel, RF_Test_Data.dBW);
    if(RF_Test_Data.dBW = 24e6){
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", d2s_WorkMode);
        d2sProtocolSSI d2s_test;        
        d2s_test.SSI_write(0x200, 0x2000, false);
        d2s_test.SSI_write(0x202, 0x90, false);
        d2s_test.SSI_write(0xC, 0x37);     //wl_trx_reg3
        d2s_test.SSI_write(0x10, 0x37);        
        d2s::d2s_LABEL_END();
    }
    else if(RF_Test_Data.dBW == 48e6){
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", d2s_WorkMode);
        d2sProtocolSSI d2s_test;        
        d2s_test.SSI_write(0x200, 0x2000, false);
        d2s_test.SSI_write(0x202, 0x90, false);
        d2s_test.SSI_write(0xC, 0x3F);     //wl_trx_reg3
        d2s_test.SSI_write(0x10, 0x3F);        
        d2s::d2s_LABEL_END();
    }
    
    CCRFTester.SelectSites("site0,site2");
    SrcUtilitySites0(api);
    //4  Load source and capture signal
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();
    
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();    
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&MxWlanResults);
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
    
    CCRFTester.SelectSites("site1,site3");
    SrcUtilitySites1(api);
    //4  Load source and capture signal
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();
    
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
    
    //5. Trigger capture signal, get wave, calculate evm
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&MxWlanResults);  
    
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
    SrcUtilitySites0(api);                                                      //recover Relay state
    
    FOREACH_ACTIVE_SITE(api){
        /* site: 0,2,3 */
        int site_id = api->Get_active_site();
        Testsoftbin[site_id] = 1;//softbin flag
        ResultsAttribute = MxWlanResults[site_id];
        EVM=ResultsAttribute.OFDMM.CompositeRMSEVM.dCompositeRMSEVMMean;
        EVM_Power_Abs = ResultsAttribute.SEM.CarrierMeasurement.dAbsolutePower+pathloss[site_id];        
        
        ValueTest (api, RF_CapPin, 100*pow(10,(EVM/20)), lowl[0], hil[0], Units[0], Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
        ValueTest (api, RF_CapPin, EVM_Power_Abs, lowl[1], hil[1], Units[1], Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);

    }
         
    d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0xC, 0x2F);     //wl_trx_reg3, default value
    d2s_test.SSI_write(0x10, 0x2F);
    d2s::d2s_LABEL_END();
    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site();
        if(Testsoftbin[site_id]!=1){
         api->Set_result_bin(Testsoftbin[site_id]);
        }
    }
    return EXIT_SUCCESS;
}

int WL_TX_Mask_cpp(API * api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    //Parameter definition here
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char Ana_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_Src_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_Cap_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
    
    CCMxWlanResults MxWlanResults;
    WlanResultsAttribute ResultsAttribute;
    double Result_freq_L;
    double Result_freq_R;
    double Result_power_L;
    double Result_power_R;
    double Channel_Power;
    double pathloss[4];
    
    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
    Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);
    
    //2. Get Passloss
    Read_Pathloss(RF_Test_Data,pathloss);
    
    //3. DUT register setting  
    TX_PLL_Setup(api, (emMode)RF_Test_Data.iMode, (emTX_Band)RF_Test_Data.iBand, RF_Test_Data.cChannel, RF_Test_Data.dBW);
    d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;        
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0xC, 0x2F);     //wl_trx_reg3
    d2s_test.SSI_write(0x10, 0x2F);        
    d2s::d2s_LABEL_END();
 
    
    CCRFTester.SelectSites("site0,site2");
    SrcUtilitySites0(api);
    //4  Load source and capture signal
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();
    
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();    
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&MxWlanResults);
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
    
    CCRFTester.SelectSites("site1,site3");
    SrcUtilitySites1(api);
    //4  Load source and capture signal
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();
    
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
    
    //5. Trigger capture signal, get wave, calculate evm
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&MxWlanResults);  
    
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
    SrcUtilitySites0(api);                                                      //recover Relay state
    
    FOREACH_ACTIVE_SITE(api){
        /* site: 0,2,3 */
        int site_id = api->Get_active_site();
        ResultsAttribute = MxWlanResults[site_id];
        Result_freq_L=ResultsAttribute.SEM.LowerOffsetMargin.dMarginFrequency/1e6;
        Result_freq_R=ResultsAttribute.SEM.UpperOffsetMargin.dMarginFrequency/1e6;
        Result_power_L=ResultsAttribute.SEM.LowerOffsetMargin.dMargin;
        Result_power_R=ResultsAttribute.SEM.UpperOffsetMargin.dMargin;
        Channel_Power = ResultsAttribute.SEM.CarrierMeasurement.dAbsolutePower+pathloss[site_id];  

        ValueTest (api, RF_CapPin, Channel_Power, lowl[0], hil[0], Units[0], Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
        ValueTest (api, RF_CapPin, Result_freq_L, lowl[3], hil[3], Units[3], Test_Item[3], "FAIL_BIN", Test_number[3], Clogenable);
        ValueTest (api, RF_CapPin, Result_power_L, lowl[4], hil[4], Units[4], Test_Item[4], "FAIL_BIN", Test_number[4], Clogenable);
        ValueTest (api, RF_CapPin, Result_freq_R, lowl[5], hil[5], Units[5], Test_Item[5], "FAIL_BIN", Test_number[5], Clogenable);
        ValueTest (api, RF_CapPin, Result_power_R, lowl[6], hil[6], Units[6], Test_Item[6], "FAIL_BIN", Test_number[6], Clogenable);
        
    }
    return EXIT_SUCCESS;
}

int TX_DummyOP_cpp(API *api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    
     //1. Get test item information    
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char Ana_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_Src_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_Cap_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
    
    CCRfmxSpecAnResults mxSpecAnResults;  
    SpecAnResultAttribute ResultAttribute; 
    double pathloss[4];
    double Post_Power;
    double CR;
    double SR;
    
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
    Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);
 
    //2. Get Passloss
    Read_Pathloss(RF_Test_Data,pathloss);
    
    DummyOP_Path_Setup(api);
    
    CCRFTester.SelectSites("site0,site2");
    SrcUtilitySites0(api);
    //3.2  Load source and capture signal
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();        
    
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);
    
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();  
   
    CCRFTester.SelectSites("site1,site3");
    SrcUtilitySites1(api);
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();  
    
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);
    
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop(); 
    SrcUtilitySites0(api);                                                      //recover Relay state

    DummyOP_Path_Recover(api);
    
    FOREACH_ACTIVE_SITE(api){       
        int site_id = api->Get_active_site();
        ResultAttribute = mxSpecAnResults[site_id]; 
        Calc_TX_Power_CR_SR(api,&RF_Test_Data,&ResultAttribute,pathloss[site_id],&Post_Power,&CR,&SR); 
        
        ValueTest (api, RF_CapPin, Post_Power, lowl[0], hil[0], Units[0], Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
        ValueTest (api, RF_CapPin, CR, lowl[1], hil[1], "dB", Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
        ValueTest (api, RF_CapPin, SR, lowl[2], hil[2], "dB", Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);
        
    }           
    return EXIT_SUCCESS;
}

int TX_PXdB_cpp(API *api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char Ana_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_Src_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_Cap_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
    
    CCRfmxSpecAnResults mxSpecAnResults;  
    SpecAnResultAttribute ResultAttribute;
    long Signal_Bin = 0;
    double Signal_dbm = 0;
    double pathloss[4] = {0};
    
    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
    Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);
    
    //2. Get Passloss
    Read_Pathloss(RF_Test_Data,pathloss);

    CCRFTester.SelectSites("site0,site2");
    SrcUtilitySites0(api);
    //3.2  Load source and capture signal
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();        
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
    
    //3.3  Trigger capture signal, get wave, calculate power
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);
    
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();  
         
    CCRFTester.SelectSites("site1,site3"); 
    SrcUtilitySites1(api);
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();
    
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
    //3.3  Trigger capture signal, get wave, calculate power
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);
    
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
    SrcUtilitySites0(api);                                                      //recover Relay state
    
    FOREACH_ACTIVE_SITE(api){
        /* site: 0,2,3 */
        int site_id = api->Get_active_site();
        ResultAttribute = mxSpecAnResults[site_id];
        if(ResultAttribute.dwNumbersOfSpectrum > 0)
        {
            Signal_Bin = int((RF_Test_Data.dLO_Freq+ RF_Test_Data.tyTXTest.dFreqSpacing- ResultAttribute.dInitiaFrequency)/ResultAttribute.dFrequencyIncrement);
            Calc_Power_dbm(&ResultAttribute,Signal_Bin,3,&Signal_dbm,pathloss[site_id]);
        }
        ValueTest (api, RF_CapPin, Signal_dbm, lowl[2], hil[2], Units[2], Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);

    }                               
    
    return EXIT_SUCCESS;
} 

int TX_Power_PPF(API * api) {
    
    const char* testname = NULL;
    char *RF_Cap_Signal;
    char *RF_CapPin;
    //int nSite = 0;
    
    double Power_Data;
    double CR_Data;
    double SR_Data;
    
    double Exp_Fre = 37.5E6;
    CCRfmxSpecAnResults mxSpecAnResults;  
    SpecAnResultAttribute ResultAttribute;    
    testname = api->Get_current_test_name();
    if(strstr(testname,"C0")!=NULL){
        TXIQ_5G_C0_Module(api);
        TXIQ_5G_37p5M_C0_Module(api);
        RF_Cap_Signal = "TX_POWR_PPF_37p5_M";
        RF_CapPin = "RF_RFO_5G_C0";
//        sprintf(RF_Cap_Signal, "TX_POWR_PPF_37p5_M");
//        sprintf(RF_CapPin, "RF_RFO_5G_C0");
    }
    else{
        TXIQ_5G_C1_Module(api);
        TXIQ_5G_37p5M_C1_Module(api);
        RF_Cap_Signal = "TX_POWR_PPF_37p5_M";
        RF_CapPin = "RF_RFO_5G_C1";
//        sprintf(RF_Cap_Signal, "TX_POWR_PPF_37p5_M");
//        sprintf(RF_CapPin, "RF_RFO_5G_C1");
    }
    
//    MWCapture_Signal(WLAN_TX_5G_B7_Freq + 37.5E6,0,4096, 200E6,RF_Cap_Signal);
//    
//    CCRFTester.SelectSites("site0,site2");
//    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
//    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
//    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);
//    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
//    
//    FOREACH_ACTIVE_SITE(api){
//        /* site: 0,2,3 */
//        int site_id = GET_SITE_NUM(mxSpecAnResults);
//        ResultAttribute = mxSpecAnResults[site_id];
//        //Calc_TX_Power_CR_SR(api,&RF_Test_Data,&ResultAttribute); 
//        //Calc_TX_Power_CR_maxSR(&ResultAttribute,Exp_Fre,lo_array[i],&Power_Data,&CR_Data,&SR_Data);
//        Calc_TX_Power_CR_maxSR(&ResultAttribute,Exp_Fre,WLAN_TX_5G_B7_Freq,&Power_Data,&CR_Data,&SR_Data);
//        
//        api->info_message("Site:%d---------- %s    Power_Data    :    %f-----------",site_id,"SSI_DATA",Power_Data);           
//        api->info_message("Site:%d---------- %s    CR_Data    :    %f-----------",site_id,"SSI_DATA",CR_Data);     
//        api->info_message("Site:%d---------- %s    SR_Data    :    %f-----------",site_id,"SSI_DATA",SR_Data);
//    }
    
//    if(strstr(testname,"C1")!=NULL))
//    {
//        TXIQ_5G_Restore_Module(api);
//    }
    TXIQ_5G_Restore_Module(api);
 
    return EXIT_SUCCESS;
}

void Calc_TX_Power_2_Spur(API *api,tyTestData *pRF_Test_Data,SpecAnResultAttribute *ResultAttribute,double pathloss,double Space1,double Space2,double *outPower,double *SPUR1_dbm,double *SPUR2_dbm)
{
    long Signal_Bin = 0;
    long Spur_Bin1 = 0;
    long Spur_Bin2 = 0;
    
    
    Signal_Bin = int((pRF_Test_Data->dLO_Freq+ pRF_Test_Data->tyTXTest.dFreqSpacing- ResultAttribute->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);    
    Spur_Bin1 = int((pRF_Test_Data->dLO_Freq+ pRF_Test_Data->tyTXTest.dFreqSpacing + Space1 - ResultAttribute->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);
    Spur_Bin2 = int((pRF_Test_Data->dLO_Freq+ pRF_Test_Data->tyTXTest.dFreqSpacing + Space2 - ResultAttribute->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);
    
    Calc_Power_dbm(ResultAttribute,Signal_Bin,3,outPower,pathloss);
    Calc_Power_dbm(ResultAttribute,Spur_Bin1,3,SPUR1_dbm,pathloss);
    Calc_Power_dbm(ResultAttribute,Spur_Bin2,3,SPUR2_dbm,pathloss);
}

void Calc_TX_Power_3_Spur(API *api,tyTestData *pRF_Test_Data,SpecAnResultAttribute *ResultAttribute,double pathloss,double Space1,double Space2,double Space3,double *outPower,double *SPUR1_dbm,double *SPUR2_dbm,double *SPUR3_dbm)
{

    long Signal_Bin = 0;
    long Spur_Bin1 = 0;
    long Spur_Bin2 = 0;
    long Spur_Bin3 = 0;   
    
    Signal_Bin = int((pRF_Test_Data->dLO_Freq + pRF_Test_Data->tyTXTest.dFreqSpacing- ResultAttribute->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);    
    Spur_Bin1 = int((pRF_Test_Data->dLO_Freq + pRF_Test_Data->tyTXTest.dFreqSpacing + Space1 - ResultAttribute->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);
    Spur_Bin2 = int((pRF_Test_Data->dLO_Freq + pRF_Test_Data->tyTXTest.dFreqSpacing + Space2 - ResultAttribute->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);
    Spur_Bin3 = int((pRF_Test_Data->dLO_Freq + pRF_Test_Data->tyTXTest.dFreqSpacing + Space3 - ResultAttribute->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);
    
    Calc_Power_dbm(ResultAttribute,Signal_Bin,3,outPower,pathloss);
    Calc_Power_dbm(ResultAttribute,Spur_Bin1,3,SPUR1_dbm,pathloss);
    Calc_Power_dbm(ResultAttribute,Spur_Bin2,3,SPUR2_dbm,pathloss);
    Calc_Power_dbm(ResultAttribute,Spur_Bin3,3,SPUR3_dbm,pathloss);
}

int TX_Power_Spur(API *api)
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    
    tyTestData RF_Test_Data;
    const char* testname = NULL;
    char Ana_SrcPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_CapPin[_MAX_NAME_SIZE_RF] = {"\0"};
    char Ana_Src_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
    char RF_Cap_Signal[_MAX_NAME_SIZE_RF] = {"\0"};
    double pathloss[4];
    
    CCRfmxSpecAnResults mxSpecAnResults;  
    SpecAnResultAttribute ResultAttribute;
    
    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
    Get_Signal_Name(RF_Test_Data, Ana_Src_Signal, RF_Cap_Signal);
    
    Read_Pathloss(RF_Test_Data,pathloss);
    
    //2. Get Passloss
    //pathloss = Read_Pathloss(testname);

    CCRFTester.SelectSites("site0,site2");
    SrcUtilitySites0(api);
    //3.2  Load source and capture signal
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();        
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
    
    //3.3  Trigger capture signal, get wave, calculate power
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);
    
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();  
    
        
    CCRFTester.SelectSites("site1,site3");
    SrcUtilitySites1(api);
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Configure();
    //3.3  Trigger capture signal, get wave, calculate power
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Start();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Read(&mxSpecAnResults);
    
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    CCRFTester.RFCAP(RF_CapPin).SIGNAL(RF_Cap_Signal).Stop();
    SrcUtilitySites0(api);                                                      //recover Relay state
    
    double outPower = 0;
    double SPUR1_dbm = 0;
    double SPUR2_dbm = 0;
    double SPUR3_dbm = 0;
    
    FOREACH_ACTIVE_SITE(api){
        /* site: 0,2,3 */
        int site_id = api->Get_active_site();
        ResultAttribute = mxSpecAnResults[site_id];
        
        if(RF_Test_Data.iMode == WLAN_2G_Mode)
        {
            if(ResultAttribute.dwNumbersOfSpectrum > 0)
                Calc_TX_Power_2_Spur(api,&RF_Test_Data,&ResultAttribute,pathloss[site_id],-0.5E6,0.5E6,&outPower,&SPUR1_dbm,&SPUR2_dbm); 
            
            ValueTest (api, RF_CapPin, outPower, lowl[0], hil[0], "dBm", Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
            ValueTest (api, RF_CapPin, outPower-SPUR1_dbm, lowl[1], hil[1], "dBc", Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
            ValueTest (api, RF_CapPin, outPower-SPUR2_dbm, lowl[2], hil[2], "dBc", Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);
        }
        else
        {
            if(ResultAttribute.dwNumbersOfSpectrum > 0)
                Calc_TX_Power_3_Spur(api,&RF_Test_Data,&ResultAttribute,pathloss[site_id],40E6,80E6,120E6,&outPower,&SPUR1_dbm,&SPUR2_dbm,&SPUR3_dbm); 
            
            ValueTest (api, RF_CapPin, outPower, lowl[0], hil[0], "dBm", Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
            ValueTest (api, RF_CapPin, outPower-SPUR1_dbm, lowl[1], hil[1], "dBc", Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
            ValueTest (api, RF_CapPin, outPower-SPUR2_dbm, lowl[2], hil[2], "dBc", Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);
            ValueTest (api, RF_CapPin, outPower-SPUR3_dbm, -999999.0, 999999.0, "dBc", "SPUR3", "FAIL_BIN", 1, false);
        }
    }                               
    return EXIT_SUCCESS;
}

int calc_PLL_Sweep(API *api,int site_id,long long *Dataarray,long sweep_step,double *bandError,long *first_band_value,long *last_band_value,long *max_pll_State,long *min_pll_State)
{

    long long raw_band_wave[sweep_step];
    double band_wave[sweep_step];
    long long pll_state_wave[sweep_step];
    
    double band_best_fit_wave[sweep_step];
    double band_err_wave[sweep_step];
    
//    long total_sweep_step;
//    
//    total_sweep_step = *sweep_step;
    
    for(int i=0;i<sweep_step;i++)
    {
        band_wave[i]= (Dataarray[2*i]>>7)*1.0;
        pll_state_wave[i]= Dataarray[2*i+1]>>10;
    }
    
//    api->Set_curve_data("BAND_WAVE", 0, 1/80e6, sweep_step, band_wave);  //debug
    
    *first_band_value = band_wave[0];
    *last_band_value = band_wave[sweep_step-1];
    
    vector<double> res;
    if(polyUseSimple(2, sweep_step, band_wave, &res) == false)
    {
        return -1;
    }
    
    for(int i = 0;i < sweep_step; i++)
    {
        band_best_fit_wave[i] =res[0] * pow(i,2) + res[1] * i +res[2];
        band_err_wave[i] =fabs( band_best_fit_wave[i] - band_wave[i]);
    }
    
//    api->Set_curve_data("FIT_WAVE", 0, 1/80e6, sweep_step, band_best_fit_wave);  //debug
    
    *bandError = band_err_wave[0];
    for(int i = 1;i < sweep_step; i++)
    {
        if(*bandError < band_err_wave[i])
        {
            *bandError = band_err_wave[i];
        }
    }
    
    *max_pll_State = pll_state_wave[0];
    *min_pll_State = pll_state_wave[0];
    for(int i = 1;i < 73; i++)
    {
        if(*max_pll_State < pll_state_wave[i])
        {
            *max_pll_State = pll_state_wave[i];
        }
        else if(*min_pll_State > pll_state_wave[i])
        {
            *min_pll_State = pll_state_wave[i];
        }
    }
    return EXIT_SUCCESS;
}

int PLL_Sweep_vbt(API *api)
{
    
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    
    const char* testname = NULL;
    CSiteLong SiteData;
//    long long Dataarray[146];
    long sweep_size;
    long sweep_step;
    double startFreq;
    double stopFreq;
    double stepFreq;
    
    double bandError;
    long first_band_value;
    long last_band_value;
    long max_pll_State;
    long min_pll_State;
    
    testname = api->Get_current_test_name();
    if(strstr(testname,"2G")!=NULL)
    {
        startFreq=2412e6;
        stopFreq=2484e6;
        stepFreq=1e6;
        sweep_step=(stopFreq-startFreq)/stepFreq+1;
        WL_2G_PLL_Sweep_Module(api,&SiteData);
        //sweep_step = ?;
    }
    else
    {
        startFreq=4920e6;
        stopFreq=5824e6;
        stepFreq=2e6;
        sweep_step=(stopFreq-startFreq)/stepFreq+1;
        WL_5G_PLL_Sweep_Module(api,&SiteData);
        //sweep_step = ?;
    }

    sweep_size=sweep_step*2;
    long long *Dataarray = new long long[sweep_size];

    FOREACH_ACTIVE_SITE(api){
       int site_id = api->Get_active_site();
       for(int m = 0;m<sweep_size;m++)
       {
           Dataarray[m] = SiteData(site_id,m);
       }     
       calc_PLL_Sweep(api,site_id,Dataarray,sweep_step,&bandError,&first_band_value,&last_band_value,&max_pll_State,&min_pll_State);

       ValueTest (api, "SSI_DATA", bandError, lowl[0], hil[0], Units[0], Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
       ValueTest (api, "SSI_DATA", first_band_value, lowl[1], hil[1], Units[1], Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
       ValueTest (api, "SSI_DATA", last_band_value, lowl[2], hil[2], Units[2], Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);
       ValueTest (api, "SSI_DATA", max_pll_State, lowl[3], hil[3], Units[3], Test_Item[3], "FAIL_BIN", Test_number[3], Clogenable);
       ValueTest (api, "SSI_DATA", min_pll_State, lowl[4], hil[4], Units[4], Test_Item[4], "FAIL_BIN", Test_number[4], Clogenable);

    }
    delete[] Dataarray;
    return EXIT_SUCCESS;
}


int TX_2G_IDD_DC_vbt(API *api)
{
    tyTestData RF_Test_Data;
    char *Channel_p;
    char *Channel;
    const char* testname = NULL;
    
    char Ana_Src_Signal[32] = {"\0"};
    char *Ana_SrcPin = "RF_TEST_TX_IP";   
    
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
//    Get_Pin_Name(RF_Test_Data, Ana_SrcPin, RF_CapPin);
    
    Channel=RF_Test_Data.cChannel;
    Channel_p=strstr(Channel,"C0");
    
    //PPMU_ForceV IQ_SrcPin, 0.6, 0.002
//    api->Execute_test("TX_2G_IDD_PPMU_FORCE_TEST");
    CCRFTester.SelectSites("site0,site2");
    sprintf(Ana_Src_Signal, "TX_2G_IDD_DC_0p%d", 6);
    LoadSignal_MIX_TX_2G_DC(0.6,Ana_Src_Signal);
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();     
    
    d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0xC, 0x3F);       //reg3 txmode=3
    d2s_test.SSI_write(0x10, 0x3F);      //reg4 txmode=3
    d2s::d2s_LABEL_END();
    
    if(Channel_p!=NULL)
    {
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
        d2s_test.SSI_write(0x1C, 0x1D1D);    //delta current=(dc current with reg7<2>=1)-(dc current with reg7<2>=0)
        d2s::d2s_LABEL_END();
    }
    else
    {
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
        d2s_test.SSI_write(0x1C, 0x1D1D);    //delta current=(dc current with reg7<10>=1)-(dc current with reg7<10>=0)
        d2s::d2s_LABEL_END();
    }
    
    map<int,double> iddMeasUpc1;
    double *GetValue;
    api->Execute_test("TX_2G_IDD_TEST");
    
    FOREACH_ACTIVE_SITE(api){
    api->Get_dctest_values("TX_2G_IDD_TEST","RF_VDD_TX2G_3P3_0",0,THE_MEASURE,&GetValue,THE_END);
    int site_id = api->Get_active_site();
    iddMeasUpc1[0]=GetValue[0];
    api->info_message("Site:%d---------------- %s    iddMeasUpc1    :    %f-----------",site_id,"RF_VDD_TX2G_3P3_0",iddMeasUpc1[site_id]);    
    }
    
    if(Channel_p!=NULL)
    {
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
        d2s_test.SSI_write(0x1C, 0x1D19);    //delta current=(dc current with reg7<2>=1)-(dc current with reg7<2>=0)
        d2s::d2s_LABEL_END();
    }
    else
    {
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
        d2s_test.SSI_write(0x1C, 0x191D);    //delta current=(dc current with reg7<10>=1)-(dc current with reg7<10>=0)
        d2s::d2s_LABEL_END();
    }
    
    map<int,double> iddMeasUpc0;
    //double *GetValue;
    api->Execute_test("TX_2G_IDD_TEST");
    
    FOREACH_ACTIVE_SITE(api){
    api->Get_dctest_values("TX_2G_IDD_TEST","RF_VDD_TX2G_3P3_0",0,THE_MEASURE,&GetValue,THE_END);
    int site_id = api->Get_active_site();
    iddMeasUpc0[0]=GetValue[0];
    api->info_message("Site:%d---------------- %s    iddMeasUpc0    :    %f-----------",site_id,"RF_VDD_TX2G_3P3_0",iddMeasUpc0[site_id]);    
    }
    
    d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
    d2s_test.SSI_write(0x1C, 0x1D1D);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s::d2s_LABEL_END();    
    
    if(Channel_p!=NULL)
    {
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
        d2s_test.SSI_write(0xE0, 0x1);
        d2s_test.SSI_write(0xF0 + 0x10 , 0x79A3);   //channel 0: delta current=(dc current with reg312=1, reg320<15:10>=30)- (dc current with reg312=0, reg320<15:10>=0) }
        d2s::d2s_LABEL_END();
    }
    else
    {
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
        d2s_test.SSI_write(0x150, 0x1);
        d2s_test.SSI_write(0x160 + 0x10, 0x79A3);   //channel 0: delta current=(dc current with reg312=1, reg320<15:10>=30)- (dc current with reg312=0, reg320<15:10>=0)
        d2s::d2s_LABEL_END();
    }
    
    map<int,double> iddMeasPAA1;
    //double *GetValue;
    api->Execute_test("TX_2G_IDD_TEST");
    
    FOREACH_ACTIVE_SITE(api){
    api->Get_dctest_values("TX_2G_IDD_TEST","RF_VDD_TX2G_3P3_0",0,THE_MEASURE,&GetValue,THE_END);
    int site_id = api->Get_active_site();
    iddMeasPAA1[0]=GetValue[0];
    api->info_message("Site:%d---------------- %s    iddMeasPAA1    :    %f-----------",site_id,"RF_VDD_TX2G_3P3_0",iddMeasPAA1[site_id]);    
    }
    
    if(Channel_p!=NULL)
    {
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
        d2s_test.SSI_write(0xE0, 0x0);
        d2s_test.SSI_write(0xF0 + 0x10, 0x1A3);    //channel 0: delta current=(dc current with reg312=1, reg320<15:10>=40)- (dc current with reg312=0, reg320<15:10>=0)
        d2s::d2s_LABEL_END();
    }
    else
    {
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
        d2s_test.SSI_write(0x150, 0x0);
        d2s_test.SSI_write(0x160 + 0x10, 0x1A3);    //channel 0: delta current=(dc current with reg312=1, reg320<15:10>=40)- (dc current with reg312=0, reg320<15:10>=0)
        d2s::d2s_LABEL_END();
    }
    
    map<int,double> iddMeasPAA0;
    //double *GetValue;
    api->Execute_test("TX_2G_IDD_TEST");
    
    FOREACH_ACTIVE_SITE(api){
    api->Get_dctest_values("TX_2G_IDD_TEST","RF_VDD_TX2G_3P3_0",0,THE_MEASURE,&GetValue,THE_END);
    int site_id = api->Get_active_site();
    iddMeasPAA0[0]=GetValue[0];
    api->info_message("Site:%d---------------- %s    iddMeasPAA0    :    %f-----------",site_id,"RF_VDD_TX2G_3P3_0",iddMeasPAA0[site_id]);    
    }
    
    d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0xE0, 0x1);
    d2s_test.SSI_write(0x150, 0x1);
    d2s_test.SSI_write(0xF0 + 0x10, 0x81A3);
    d2s_test.SSI_write(0x160 + 0x10, 0x81A3);
    d2s::d2s_LABEL_END();
    
    if(Channel_p!=NULL)
    {
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
        d2s_test.SSI_write(0xF0 + 0x10, 0x8283);   //channel 0: delta current=(dc current with reg312=1, reg320<15:10>=24)- (dc current with reg312=0, reg320<15:10>=0)
        d2s::d2s_LABEL_END();
    }
    else
    {
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
        d2s_test.SSI_write(0x160 + 0x10, 0x8283);   //channel 0: delta current=(dc current with reg312=1, reg320<15:10>=24)- (dc current with reg312=0, reg320<15:10>=0)
        d2s::d2s_LABEL_END();
    }
    
    map<int,double> iddMeasPAB1;
    //double *GetValue;
    api->Execute_test("TX_2G_IDD_TEST");
    
    FOREACH_ACTIVE_SITE(api){
    api->Get_dctest_values("TX_2G_IDD_TEST","RF_VDD_TX2G_3P3_0",0,THE_MEASURE,&GetValue,THE_END);
    int site_id = api->Get_active_site();
    iddMeasPAB1[0]=GetValue[0];
    api->info_message("Site:%d---------------- %s    iddMeasPAB1    :    %f-----------",site_id,"RF_VDD_TX2G_3P3_0",iddMeasPAB1[site_id]);    
    }
    
    if(Channel_p!=NULL)
    {
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
        d2s_test.SSI_write(0xF0 + 0x10, 0x8003);    //channel 0: delta current=(dc current with reg312=1, reg320<15:10>=24)- (dc current with reg312=0, reg320<15:10>=0)
        d2s::d2s_LABEL_END();
    }
    else
    {
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
        d2s_test.SSI_write(0x160 + 0x10, 0x8003);    //channel 0: delta current=(dc current with reg312=1, reg320<15:10>=24)- (dc current with reg312=0, reg320<15:10>=0)
        d2s::d2s_LABEL_END();
    }
    
    map<int,double> iddMeasPAB0;
    //double *GetValue;
    api->Execute_test("TX_2G_IDD_TEST");
    
    FOREACH_ACTIVE_SITE(api){
    api->Get_dctest_values("TX_2G_IDD_TEST","RF_VDD_TX2G_3P3_0",0,THE_MEASURE,&GetValue,THE_END);
    int site_id = api->Get_active_site();
    iddMeasPAB0[0]=GetValue[0];
    api->info_message("Site:%d---------------- %s    iddMeasPAB0    :    %f-----------",site_id,"RF_VDD_TX2G_3P3_0",iddMeasPAB0[site_id]);    
    }
    
    d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
    d2s_test.SSI_write(0xF0 + 0x10, 0x81A3);
    d2s_test.SSI_write(0x160 + 0x10, 0x81A3);    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);      
    d2s::d2s_LABEL_END();
    
    if(Channel_p!=NULL)
    {
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
        d2s_test.SSI_write(0xB0, 0x1F);    //channel 0: delta current=(dc current with reg44[0]=1, reg45[0]=1
        d2s_test.SSI_write(0xB4, 0x1F);        
        d2s::d2s_LABEL_END();
    }
    else
    {
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
        d2s_test.SSI_write(0xB8, 0x1F);    //channel 1: delta current=(dc current with reg46[0]=1, reg47[0]=1
        d2s_test.SSI_write(0xBC, 0x1F);
        d2s::d2s_LABEL_END();
    }
    
    map<int,double> iddMeasPABit0_1;
    //double *GetValue;
    api->Execute_test("TX_2G_IDD_TEST");
    
    FOREACH_ACTIVE_SITE(api){
    api->Get_dctest_values("TX_2G_IDD_TEST","RF_VDD_TX2G_3P3_0",0,THE_MEASURE,&GetValue,THE_END);
    int site_id = api->Get_active_site();
    iddMeasPABit0_1[0]=GetValue[0];
    api->info_message("Site:%d---------------- %s    iddMeasPABit0_1    :    %f-----------",site_id,"RF_VDD_TX2G_3P3_0",iddMeasPABit0_1[site_id]);    
    }
    
    if(Channel_p!=NULL)
    {
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
        d2s_test.SSI_write(0xB0, 0x1E);    //channel 0: delta current=(dc current with reg44[0]=0, reg45[0]=0
        d2s_test.SSI_write(0xB4, 0x1E);
        d2s::d2s_LABEL_END();
    }
    else
    {
        d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
        d2s_test.SSI_write(0xB8, 0x1E);    //channel 1: delta current=(dc current with reg46[0]=0, reg47[0]=0
        d2s_test.SSI_write(0xBC, 0x1E);
        d2s::d2s_LABEL_END();
    }
    
    map<int,double> iddMeasPABit0_0;
    //double *GetValue;
    api->Execute_test("TX_2G_IDD_TEST");
    
    FOREACH_ACTIVE_SITE(api){
    api->Get_dctest_values("TX_2G_IDD_TEST","RF_VDD_TX2G_3P3_0",0,THE_MEASURE,&GetValue,THE_END);
    int site_id = api->Get_active_site();
    iddMeasPABit0_0[0]=GetValue[0];
    api->info_message("Site:%d---------------- %s    iddMeasPABit0_0    :    %f-----------",site_id,"RF_VDD_TX2G_3P3_0",iddMeasPABit0_0[site_id]);    
    }

    d2s::d2s_LABEL_BEGIN(api, "burst_test", "ssi", LearningMode);
    d2s_test.SSI_write(0xB0, 0x1F);
    d2s_test.SSI_write(0xB4, 0x1F);
    d2s_test.SSI_write(0xB8, 0x1F);
    d2s_test.SSI_write(0xBC, 0x1F);
    d2s::d2s_LABEL_END();
    
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop(); 
    
    return EXIT_SUCCESS;
    
}    