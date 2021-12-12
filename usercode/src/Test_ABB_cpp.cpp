/* 
 * File:   ABB_Test.cpp
 * Author: dzr
 *
 * Created on 2020年11月10日, 下午3:58
 */



#include <iostream>
#include "GetLog.h" 
#include "UserAPI.h" 



//#include "Excel.h"

#if 0
#include "UserDef.h"
#include "CCS08F.h"
#include "RegDef.h"
#endif


#include "Test_ABB.h"
#include "d2sProtocolSSI.h"
#include "D2S_ABB_Module.h"
#include "Globle_Var.h"

using namespace std;



void ABB_ADC_PV_Cal(std::string Channel,CSiteLong* WL_PV_Sensor_Val,int CalType){
    
	CSiteLong ReadValue;
   
    if(Channel=="C0"){
        if(CalType==calType_LV){        
            WL_ADC_C0_Setup_PVCal_LV_Module(&ReadValue);
        }
        else if(CalType==calType_LV1){
            WL_ADC_C0_Setup_PVCal_LV1_Module(&ReadValue);
        }
        else if(CalType==calType_Normal){
            WL_ADC_C0_Setup_PVCal_Module(&ReadValue);
        }
    }
    else if(Channel =="C1"){
        if(CalType==calType_LV){        
            WL_ADC_C1_Setup_PVCal_LV_Module(&ReadValue);
        }
        else if(CalType==calType_LV1){
            WL_ADC_C1_Setup_PVCal_LV1_Module(&ReadValue);
        }
        else if(CalType==calType_Normal){
            WL_ADC_C1_Setup_PVCal_Module(&ReadValue);
        }
    }
    
    long long nValue = 0;
//    long long* pData = ReadValue.GetAddress(0);
    FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
        //int site_id = api->Get_active_site();
        nValue=(((ReadValue(index,0)>>9)&15)<<4)+(ReadValue(index,1)>>12);
        
        WL_PV_Sensor_Val->InitDataArray(index, 1);
        WL_PV_Sensor_Val->CopyElement(index,&nValue,1);
	FOREACH_ACTIVESITE_END
    
}



void ABB_ADC_CalStatus(std::string Channel,CSiteLong*cal_status,CSiteLong*cal_status_C1,int CalType,
        CSiteLong*COMP_CAL_CODE_A1,CSiteLong*COMP_CAL_CODE_A2,CSiteLong*COMP_CAL_CODE_A3,CSiteLong*COMP_CAL_CODE){
    
    long long COARSE_CALIP_A1;
    long long COARSE_CALIP_A2;
    long long COARSE_CALIP_A3;
    long long FINE_CALIP_A1;
    long long FINE_CALIP_A2;
    long long FINE_CALIP_A3;
    CSiteLong pReadValue;
   
    if(Channel =="C0"){
        WL_ADC_C0_Setup_CalStatus_Module( &pReadValue);
    }
    else if(Channel =="C1"){
        WL_ADC_C1_Setup_CalStatus_Module( &pReadValue);
    }
    else if(Channel =="C0C1")
    {
        WL_ADC_C0C1_Setup_CalStatus_Module(&pReadValue);
    }
    long long statusReadValue=0; 
    long long CompCalCdoe=0; 
    FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
        //int index = api->Get_active_site();
        if(Channel=="C0C1"){
                statusReadValue= pReadValue(index,0)*32+pReadValue(index,2)*16+pReadValue(index,4)*8+pReadValue(index,6)*4+pReadValue(index,8)*2+pReadValue(index,10);
                cal_status->InitDataArray(index, 1);
                cal_status->SetElement(index,0,statusReadValue);
                
                statusReadValue= pReadValue(index,1)*32+pReadValue(index,3)*16+pReadValue(index,5)*8+pReadValue(index,7)*4+pReadValue(index,9)*2+pReadValue(index,11);
                cal_status_C1->InitDataArray(index, 1);
                cal_status_C1->SetElement(index,0,statusReadValue);
            }
            else {
                statusReadValue= pReadValue(index,0)*32+pReadValue(index,1)*16+pReadValue(index,2)*8+pReadValue(index,3)*4+pReadValue(index,4)*2+pReadValue(index,5);
                cal_status->InitDataArray(index, 1);
                cal_status->SetElement(index,0,statusReadValue);
                
                COARSE_CALIP_A1=pReadValue(index,6);
                FINE_CALIP_A1=pReadValue(index,7);
                COARSE_CALIP_A2=pReadValue(index,8);
                FINE_CALIP_A2=pReadValue(index,9);
                COARSE_CALIP_A3=pReadValue(index,10);
                FINE_CALIP_A3=pReadValue(index,11);
                
                COARSE_CALIP_A1=(COARSE_CALIP_A1&63)<<4;
                FINE_CALIP_A1=FINE_CALIP_A1&15;
                COMP_CAL_CODE_A1->InitDataArray(index, 1);
                COMP_CAL_CODE_A1->SetElement(index,0,(FINE_CALIP_A1+COARSE_CALIP_A1));
                
                COARSE_CALIP_A2=(COARSE_CALIP_A2&63)<<4;
                FINE_CALIP_A2=FINE_CALIP_A2&15;
                COMP_CAL_CODE_A2->InitDataArray(index, 1);
                COMP_CAL_CODE_A2->SetElement(index,0,(FINE_CALIP_A2+COARSE_CALIP_A2));
                
                COARSE_CALIP_A3=(COARSE_CALIP_A3&63)<<4;
                FINE_CALIP_A3=FINE_CALIP_A3&15;
                COMP_CAL_CODE_A3->InitDataArray(index, 1);
                COMP_CAL_CODE_A3->SetElement(index,0,(FINE_CALIP_A3+COARSE_CALIP_A3));
                
                CompCalCdoe=abs(COMP_CAL_CODE_A1->Element(index,0)%512-511)*abs(COMP_CAL_CODE_A2->Element(index,0)%512-511)*abs(COMP_CAL_CODE_A3->Element(index,0)%512-511);
                COMP_CAL_CODE->InitDataArray(index, 1);
                COMP_CAL_CODE->SetElement(index,0,CompCalCdoe);
            }
        
        //update to efuse
        if(CalType == calType_Normal){
            if(Channel=="C0"){
                ADC_C0_COMP_CAL_CODE_A1.InitDataArray(index, 1);
                ADC_C0_COMP_CAL_CODE_A1.SetElement(index,0,(COMP_CAL_CODE_A1->Element(index,0)>>4));
                ADC_C0_COMP_CAL_CODE_A2.InitDataArray(index, 1);
                ADC_C0_COMP_CAL_CODE_A2.SetElement(index,0,(COMP_CAL_CODE_A2->Element(index,0)>>4));
                ADC_C0_COMP_CAL_CODE_A3.InitDataArray(index, 1);
                ADC_C0_COMP_CAL_CODE_A3.SetElement(index,0,(COMP_CAL_CODE_A3->Element(index,0)>>4));
            }
            else{
                ADC_C1_COMP_CAL_CODE_A1.InitDataArray(index, 1);
                ADC_C1_COMP_CAL_CODE_A1.SetElement(index,0,(COMP_CAL_CODE_A1->Element(index,0)>>4));
                ADC_C1_COMP_CAL_CODE_A2.InitDataArray(index, 1);
                ADC_C1_COMP_CAL_CODE_A2.SetElement(index,0,(COMP_CAL_CODE_A2->Element(index,0)>>4));
                ADC_C1_COMP_CAL_CODE_A3.InitDataArray(index, 1);
                ADC_C1_COMP_CAL_CODE_A3.SetElement(index,0,(COMP_CAL_CODE_A3->Element(index,0)>>4));
            }
        }

	FOREACH_ACTIVESITE_END
    
}

void ABB_ADC_CalStatus(std::string Channel,CSiteLong*cal_status,CSiteLong*cal_status_C1)
{
    
//    long long COARSE_CALIP_A1;
//    long long COARSE_CALIP_A2;
//    long long COARSE_CALIP_A3;
//    long long FINE_CALIP_A1;
//    long long FINE_CALIP_A2;
//    long long FINE_CALIP_A3;
    CSiteLong pReadValue;
   
    if(Channel=="C0"){
        WL_ADC_C0_Setup_CalStatus_Module( &pReadValue);
    }
    else if(Channel =="C1"){
        WL_ADC_C1_Setup_CalStatus_Module(&pReadValue);
    }
    else if(Channel=="C0C1")
    {
        WL_ADC_C0C1_Setup_CalStatus_Module(&pReadValue);
    }
    long long statusReadValue=0; 
//    long long CompCalCdoe=0; 
    FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)

        //int site_id = api->Get_active_site();
        if(Channel=="C0C1")
        {
                statusReadValue= pReadValue(index,0)*32+pReadValue(index,2)*16+pReadValue(index,4)*8+pReadValue(index,6)*4+pReadValue(index,8)*2+pReadValue(index,10);
                cal_status->InitDataArray(index, 1);
                cal_status->SetElement(index,0,statusReadValue);
                
                statusReadValue= pReadValue(index,1)*32+pReadValue(index,3)*16+pReadValue(index,5)*8+pReadValue(index,7)*4+pReadValue(index,9)*2+pReadValue(index,11);
                cal_status_C1->InitDataArray(index, 1);
                cal_status_C1->SetElement(index,0,statusReadValue);
        }
            
    FOREACH_ACTIVESITE_END
    
}


void ABB_ADC_CapCal_DC(std::string Channel,double SampleRate,CSiteLong *WL_ADC_CAP_STS,int CalType){
    
    long long WL_ADC_C1;
    long long WL_ADC_C2;
    long long WL_ADC_C4;
    long long WL_ADC_C8;
    long long WL_ADC_C16;
    long long WL_ADC_C32;
    map<int, long long> WL_ADC_Cfirst;
    map<int, long long> WL_ADC_Csecnd;
    CSiteLong pReadValue;
    
    if(Channel=="C0"){ 
        WL_ADC_C0_Setup_CapCal_Module(&pReadValue);
    }
    else if(Channel =="C1"){
        WL_ADC_C1_Setup_CapCal_Module(&pReadValue);
    }
   
    FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
        //int site_id = api->Get_active_site();
        WL_ADC_CAP_STS->InitDataArray(index, 1);
        WL_ADC_CAP_STS->SetElement(index,0,pReadValue(index,0));
        
        WL_ADC_C1  = pReadValue(index,1);
        WL_ADC_C2  = pReadValue(index,2);
        WL_ADC_C4  = pReadValue(index,3);
        WL_ADC_C8  = pReadValue(index,4);
        WL_ADC_C16 = pReadValue(index,5);
        WL_ADC_C32 = pReadValue(index,6);
        WL_ADC_Cfirst[index] = (WL_ADC_C2>>8)+(WL_ADC_C4>>8)+(WL_ADC_C8>>8)+(WL_ADC_C16>>8)+(WL_ADC_C32>>8);
        WL_ADC_Csecnd[index] = (WL_ADC_C2&0xFF)+(WL_ADC_C4&0xFF)+(WL_ADC_C8&0xFF)+(WL_ADC_C16&0xFF)+(WL_ADC_C32&0xFF);
        
        if(WL_ADC_Cfirst[index]==0){
            WL_ADC_Cfirst[index] = 0x80;
        }else{
            WL_ADC_Cfirst[index] = int(128*128/(WL_ADC_Cfirst[index]/5.0));
        }
        if(WL_ADC_Csecnd[index]==0){
            WL_ADC_Csecnd[index] = 0x80;
        }else{
            WL_ADC_Csecnd[index] = int(128*128/(WL_ADC_Csecnd[index]/5.0));
        }
	FOREACH_ACTIVESITE_END
 
    if(CalType==0){
        if(Channel=="C0"){ 
            d2s::d2s_LABEL_BEGIN("dynamic", d2s_WorkMode);
            d2sProtocolSSI d2s_test;
            d2s_test.SSI_writeDynamic(0x21C,WL_ADC_Cfirst,"write");
            d2s_test.SSI_writeDynamic(0x220,WL_ADC_Csecnd,"write");
            d2s::d2s_LABEL_END();
        }
        else if(Channel =="C1"){
            d2s::d2s_LABEL_BEGIN("dynamic", d2s_WorkMode);
            d2sProtocolSSI d2s_test;
            d2s_test.SSI_writeDynamic(0x288,WL_ADC_Cfirst,"write");
            d2s_test.SSI_writeDynamic(0x28C,WL_ADC_Csecnd,"write");
            d2s::d2s_LABEL_END();
        }
    }
    
    if(Channel=="C0"){ 
        WL_ADC_C0_DC_Module();
    }
    else if(Channel =="C1"){
        WL_ADC_C1_DC_Module();
    }
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    if(SampleRate == 160e6){
      
        d2s_test.SSI_write(0x33C, 0x19B);
        
    }else{
        d2s_test.SSI_write(0x33C, 0x1B6);
    }
    d2s::d2s_LABEL_END();
}
#if 0
int ABB_ADC_IQ(API * api){
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
    
    int CalType;
    CSiteLong pcal_status;
    CSiteLong pcal_status_C1;
    CSiteLong pCOMP_CAL_CODE_A1;
    CSiteLong pCOMP_CAL_CODE_A2;
    CSiteLong pCOMP_CAL_CODE_A3;
    CSiteLong pCOMP_CAL_CODE;
    CSiteLong pWL_ADC_CAP_STS;
    CSiteLong WL_PV_Sensor;
    CSiteLong myWave;
    double nData[2048];
    double snr_i;
    double snr_q;
    double thd_i;
    double thd_q;
    double sfdr_i;
    double sfdr_q;
    double sinad_i;
    double sinad_q;
    double enob_i;
    double enob_q;
    double enob_iq;
    double Amp_i;
    double Amp_q;
    double GainMismatch;
    double distortion_num = 4;
    int FunBin=0;
    int SpurBin=0;

//    map<int, long long> ADC_Reg0;
//    map<int, long long> ADC_Reg3;
    
    unsigned int sitestmp[4] = {0,0,0,0};
    unsigned int sites[MAX_SITES] = {0}; 

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

    if (strstr(testname, "80M") != NULL) {
        CalType = 0; //calType_Normal;
    } 
    else if (strstr(testname, "SS") != NULL) {
        CalType = 2; //cal_Type_SS;
    } 
    else if (strstr(testname, "LV1") != NULL) {
        CalType = 4; //calType_LV1;
    } 
    else if (strstr(testname, "LV") != NULL) {
        CalType = 1; //calType_LV;
    } 
    else if (strstr(testname, "160M") != NULL) {
        CalType = 3; //calType_Nocal;
    }
      
    api->Set_loadboard_x_ubits(X_UBIT_051 + X_UBIT_024 + X_UBIT_020 + X_UBIT_065, X_UBIT_NONE);  //K2 on
    api->Set_loadboard_x_ubits(X_UBIT_019 + X_UBIT_033 + X_UBIT_011 + X_UBIT_056, X_UBIT_NONE);  //K3 on
    
    //2 DUT register setting for diff CalType
    if(CalType == cal_Type_SS){
        
        d2s::d2s_LABEL_BEGIN( "burst_test", "ssi", d2s_WorkMode);
        d2sProtocolSSI d2s_test;
        d2s_test.SSI_write(0x200,0x2000,false);
        d2s_test.SSI_write(0x202,0x94,false);
        d2s_test.SSI_write(0x350,0x10a0);
        d2s_test.SSI_write(0x35c,0x2800);
        d2s_test.SSI_write(0x364,0x10a0);
        d2s_test.SSI_write(0x370,0x2800);
        d2s::d2s_LABEL_END();
//        FOREACH_ACTIVE_SITE(api) {
//            int site_id = api->Get_active_site();
//            if(PV_SENSOR_C0_CODE(site_id,0)>110){
//                ADC_Reg0[site_id]=0x10a0;
//                ADC_Reg3[site_id]=0x2800;
//            }
//            else{
//                ADC_Reg0[site_id]=0x18a0;
//                ADC_Reg3[site_id]=0x2A00;
//            }  
//        }
//        d2s::d2s_LABEL_BEGIN( "burst_test", "dynamic", d2s_WorkMode);
//        d2sProtocolSSI d2s_test;
//        d2s_test.SSI_write(0x200,0x2000,false);
//        d2s_test.SSI_write(0x202,0x94,false);
//        d2s_test.SSI_writeDynamic(0x350,ADC_Reg0,"write1");
//        d2s_test.SSI_writeDynamic(0x35c,ADC_Reg3,"write2");
//        d2s_test.SSI_writeDynamic(0x364,ADC_Reg0,"write3");
//        d2s_test.SSI_writeDynamic(0x370,ADC_Reg3,"write4");
//        d2s::d2s_LABEL_END();
     
    }
    else if(CalType == calType_Nocal){
   
        if(RF_Test_Data.tyABBTest.dABBSampleRate==160e6){
            d2s::d2s_LABEL_BEGIN( "burst_test", "ssi", d2s_WorkMode);
            d2sProtocolSSI d2s_test;
            d2s_test.SSI_write(0x200,0x2000,false);
            d2s_test.SSI_write(0x202,0x40,false);
            d2s_test.SSI_write(0x33C,0x19B);    
            d2s::d2s_LABEL_END();
        }
        else{
            d2s::d2s_LABEL_BEGIN( "burst_test", "ssi", d2s_WorkMode);
            d2sProtocolSSI d2s_test;
            d2s_test.SSI_write(0x200,0x2000,false);
            d2s_test.SSI_write(0x202,0x40,false);
            d2s_test.SSI_write(0x33C,0x1B6);    
            d2s::d2s_LABEL_END();
        }
        
    }
    else {
          resetDevice(api);
          if(strstr(testname,"C0")!=NULL){ 
                ABB_ADC_PV_Cal("C0",&WL_PV_Sensor,CalType);
                ABB_ADC_CalStatus("C0", &pcal_status, &pcal_status_C1,CalType, &pCOMP_CAL_CODE_A1, &pCOMP_CAL_CODE_A2, &pCOMP_CAL_CODE_A3, &pCOMP_CAL_CODE);
                ABB_ADC_CapCal_DC("C0",RF_Test_Data.tyABBTest.dABBSampleRate,&pWL_ADC_CAP_STS,CalType);
      
            }
            else{
                ABB_ADC_PV_Cal("C1",&WL_PV_Sensor,CalType);
                ABB_ADC_CalStatus("C1", &pcal_status, &pcal_status_C1,CalType, &pCOMP_CAL_CODE_A1, &pCOMP_CAL_CODE_A2, &pCOMP_CAL_CODE_A3, &pCOMP_CAL_CODE);
                ABB_ADC_CapCal_DC("C1",RF_Test_Data.tyABBTest.dABBSampleRate,&pWL_ADC_CAP_STS,CalType);
            }  
    }
    
//    if (strstr(testname, "C0") != NULL) {
//        WL_ADC_C0_BeforeCap_Module(api);
//    } 
//    else {
//        WL_ADC_C1_BeforeCap_Module(api);
//    } 
    
    //3  Load source signal        
    CCRFTester.SelectSites("site0,site2");
    SrcUtilitySites0(api);
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start(); 
    sites[0]=0;
    sites[1]=2; 
    sites[2]=0;
    sites[3]=0;
    api->Set_active_sites(sites,2);
    //3.1 DUT register setting: just set before capture & wait for capture module, not capture
    if (strstr(testname, "C0") != NULL) {
        WL_ADC_C0_Cap_Module( &myWave);
    } 
    else {
        WL_ADC_C1_Cap_Module( &myWave);
    }  
    
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    for(int i=0;i<4;i++)
    {
        sites[i]=sitestmp[i];
    }
    api->Set_active_sites(sites,active_sites_size);                             //recover the sites information for Mutest
    CCRFTester.ActiveSites(sites,active_sites_size);                            //recover the sites information for RF
    
    CCRFTester.SelectSites("site1,site3");    
    SrcUtilitySites1(api);
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start();     
    sites[0]=1;
    sites[1]=3; 
    sites[2]=0;
    sites[3]=0;
    api->Set_active_sites(sites,2);
    //3.1 DUT register setting: just set before capture & wait for capture module, not capture
    if (strstr(testname, "C0") != NULL) {
        WL_ADC_C0_Cap_Module( &myWave);
    } 
    else {
        WL_ADC_C1_Cap_Module( &myWave);
    }  
    CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
    
    for(int i=0;i<4;i++)
    {
        sites[i]=sitestmp[i];
    }
    api->Set_active_sites(sites,active_sites_size);                             //recover the sites information for Mutest
    CCRFTester.ActiveSites(sites,active_sites_size);                            //recover the sites information for RF
    SrcUtilitySites0(api);                                                      //recover Relay state
    
    //4  capture for all active site
    if (strstr(testname, "C0") != NULL) {
        WL_ADC_C0_Cap_Module_read( &myWave);
    } 
    else {
        WL_ADC_C1_Cap_Module_read( &myWave);
    } 
    
    //5 calculator dynamic parameter
    FunBin=RF_Test_Data.tyABBTest.dSigFreq / (2*RF_Test_Data.tyABBTest.dABBSampleRate/RF_Test_Data.tySrcSigSet.dAnaSrcSampleSize);
    SpurBin=40e6 / (2*RF_Test_Data.tyABBTest.dABBSampleRate/RF_Test_Data.tySrcSigSet.dAnaSrcSampleSize);
    FOREACH_ACTIVE_SITE(api) {
        int site_id = api->Get_active_site();
            for(int i=0;i<RF_Test_Data.tySrcSigSet.dAnaSrcSampleSize;i++){
                nData[i]=myWave(site_id,i) xor 0x200;
            }
            adcDynamicCalc( FunBin, nData, RF_Test_Data.tySrcSigSet.dAnaSrcSampleSize, RF_Test_Data.tyABBTest.iDivideNum,  snr_i, snr_q, thd_i, thd_q, sfdr_i,sfdr_q, sinad_i, sinad_q,
                           enob_i, enob_q, enob_iq, Amp_i, Amp_q, GainMismatch, distortion_num, SpurBin);

            ValueTest ( Ana_SrcPin, sinad_i, lowl[0], hil[0], "dB", Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
            ValueTest ( Ana_SrcPin, sinad_q, lowl[1], hil[1], "dB", Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
            ValueTest ( Ana_SrcPin, enob_i, lowl[2], hil[2], Units[2], Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);
            ValueTest ( Ana_SrcPin, enob_q, lowl[3], hil[3], Units[3], Test_Item[3], "FAIL_BIN", Test_number[3], Clogenable);
            ValueTest ( Ana_SrcPin, enob_iq, lowl[4], hil[4], Units[4], Test_Item[4], "FAIL_BIN", Test_number[4], Clogenable);
            ValueTest ( Ana_SrcPin, sfdr_i, lowl[5], hil[5], "dB", Test_Item[5], "FAIL_BIN", Test_number[5], Clogenable);
            ValueTest ( Ana_SrcPin, sfdr_q, lowl[6], hil[6], "dB", Test_Item[6], "FAIL_BIN", Test_number[6], Clogenable);
            ValueTest ( Ana_SrcPin, snr_i, lowl[7], hil[7], "dB", Test_Item[7], "FAIL_BIN", Test_number[7], Clogenable);
            ValueTest ( Ana_SrcPin, snr_q, lowl[8], hil[8], "dB", Test_Item[8], "FAIL_BIN", Test_number[8], Clogenable);
            ValueTest ( Ana_SrcPin, thd_i, lowl[9], hil[9], "dB", Test_Item[9], "FAIL_BIN", Test_number[9], Clogenable);
            ValueTest ( Ana_SrcPin, thd_q, lowl[10], hil[10], "dB", Test_Item[10], "FAIL_BIN", Test_number[10], Clogenable);
            ValueTest ( Ana_SrcPin, (Amp_i/RF_Test_Data.tyABBTest.iDivideNum)*RF_Test_Data.tyABBTest.dVpp, lowl[11], hil[11], "dB", Test_Item[11], "FAIL_BIN", Test_number[11], Clogenable);
            ValueTest ( Ana_SrcPin, (Amp_q/RF_Test_Data.tyABBTest.iDivideNum)*RF_Test_Data.tyABBTest.dVpp, lowl[12], hil[12], "dB", Test_Item[12], "FAIL_BIN", Test_number[11], Clogenable);
            ValueTest ( Ana_SrcPin, GainMismatch, lowl[13], hil[13], "dB", Test_Item[13], "FAIL_BIN", Test_number[13], Clogenable);
            
            if((CalType != cal_Type_SS)&&(CalType != calType_Nocal)){
                ValueTest ( Ana_SrcPin, pWL_ADC_CAP_STS(site_id,0), lowl[14], hil[14], "", Test_Item[14], "FAIL_BIN", Test_number[14], Clogenable);
                ValueTest ( Ana_SrcPin, pcal_status(site_id,0), lowl[15], hil[15], "", Test_Item[15], "FAIL_BIN", Test_number[15], Clogenable);
                ValueTest ( Ana_SrcPin, pCOMP_CAL_CODE_A1(site_id,0), lowl[17], hil[17], "", Test_Item[17], "FAIL_BIN", Test_number[17], Clogenable);
                ValueTest ( Ana_SrcPin, pCOMP_CAL_CODE_A2(site_id,0), lowl[18], hil[18], "", Test_Item[18], "FAIL_BIN", Test_number[18], Clogenable);
                ValueTest ( Ana_SrcPin, pCOMP_CAL_CODE_A3(site_id,0), lowl[19], hil[19], "", Test_Item[19], "FAIL_BIN", Test_number[19], Clogenable);
                ValueTest ( Ana_SrcPin, pCOMP_CAL_CODE(site_id,0), lowl[20], hil[20], "", Test_Item[20], "FAIL_BIN", Test_number[20], Clogenable);
            }
    }

  return EXIT_SUCCESS;  
}

int ABB_DAC_IQ(API * api){
    
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
    
    CCIQResults IQResults;
    IQMeasureAttribute MeasureResult;  
    unsigned int FunBin=0; 

    double tone_Vp_i;
    double tone_Vp_q;
    double dc_offset_i;
    double dc_offset_q;
    double snr_i;
    double snr_q;
    double thd_i;
    double thd_q;
    double sfdr_i;
    double sfdr_q;
    double sinad_i;
    double sinad_q;
    double enob_i;
    double enob_q;
    double GainMismatch;
    const unsigned distortion_num = 3;
    unsigned samplesize;

    //1. Get test item information
    testname = api->Get_current_test_name();
    Get_TestItem_Info(testname, RF_Test_Data);
    Get_Pin_Name(RF_Test_Data, RF_SrcPin, Ana_CapPin);
    Get_Signal_Name(RF_Test_Data, RF_SrcSignal, Ana_CapSignal);
    
    api->Set_loadboard_x_ubits(X_UBIT_NONE, X_UBIT_051 + X_UBIT_024 + X_UBIT_020 + X_UBIT_065);  //K2 off
    api->Set_loadboard_x_ubits(X_UBIT_NONE, X_UBIT_019 + X_UBIT_033 + X_UBIT_011 + X_UBIT_056);  //K3 off
    
    WL_DAC_SRC_DATA_module(api);
    
     if(strstr(testname,"_DEM")!=NULL){
         if(strstr(testname,"C0")!=NULL){
             WL_DAC_DEM_C0_LPF_Module(api);
         }
         else{
             WL_DAC_DEM_C1_LPF_Module(api);
         }
     }
     else{
         if(strstr(testname,"C0")!=NULL){
             WL_DAC_C0_LPF_Module(api);
         }
         else{
             WL_DAC_C1_LPF_Module(api);
         }
     }

    CCRFTester.SelectSites("Site0,Site2");
    CapUtilitySites0(api);
    api->sleep(0.005);                                                          //add for relay stable @20210408
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Read(&IQResults);
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Stop();
    
    CCRFTester.SelectSites("Site1, Site3");
    CapUtilitySites1(api);
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Configure();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Start();
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Read(&IQResults);
    CCRFTester.MIXCAP(Ana_CapPin).SIGNAL(Ana_CapSignal).Stop();
    CapUtilitySites0(api);                                                      //recover Relay state

    FunBin = RF_Test_Data.tyABBTest.dSigFreq/(2*RF_Test_Data.tyCapSigSet.dSampleRate/RF_Test_Data.tyCapSigSet.dSampleSize);
    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site();
        MeasureResult = IQResults[site_id];

        //PlotCurve( &MeasureResult, "DAC");

        samplesize=MeasureResult.actualSamples;
        dacDynamicCalc(FunBin, &MeasureResult,samplesize, tone_Vp_i, tone_Vp_q, dc_offset_i, dc_offset_q,
                  snr_i, snr_q, thd_i, thd_q, sfdr_i, sfdr_q, sinad_i, sinad_q, enob_i, enob_q, GainMismatch, distortion_num);    
        
//        ValueTest ( Ana_CapPin, sinad_i, lowl[0], hil[0], "dB", Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
//        ValueTest ( Ana_CapPin, sinad_q, lowl[1], hil[1], "dB", Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
//        ValueTest ( Ana_CapPin, enob_i, lowl[2], hil[2], Units[2], Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);
//        ValueTest ( Ana_CapPin, enob_q, lowl[3], hil[3], Units[3], Test_Item[3], "FAIL_BIN", Test_number[3], Clogenable);
//        ValueTest ( Ana_CapPin, sfdr_i, lowl[4], hil[4], "dB", Test_Item[4], "FAIL_BIN", Test_number[4], Clogenable);
//        ValueTest ( Ana_CapPin, sfdr_q, lowl[5], hil[5], "dB", Test_Item[5], "FAIL_BIN", Test_number[5], Clogenable);
//        ValueTest ( Ana_CapPin, snr_i, lowl[6], hil[6], "dB", Test_Item[6], "FAIL_BIN", Test_number[6], Clogenable);
//        ValueTest ( Ana_CapPin, snr_q, lowl[7], hil[7], "dB", Test_Item[7], "FAIL_BIN", Test_number[7], Clogenable);
//        ValueTest ( Ana_CapPin, thd_i, lowl[8], hil[8], "dB", Test_Item[8], "FAIL_BIN", Test_number[8], Clogenable);
//        ValueTest ( Ana_CapPin, thd_q, lowl[9], hil[9], "dB", Test_Item[9], "FAIL_BIN", Test_number[9], Clogenable);
//        ValueTest ( Ana_CapPin, tone_Vp_i, lowl[10], hil[10], "V", Test_Item[10], "FAIL_BIN", Test_number[10], Clogenable);
//        ValueTest ( Ana_CapPin, tone_Vp_q, lowl[11], hil[11], "V", Test_Item[11], "FAIL_BIN", Test_number[11], Clogenable);
//        ValueTest ( Ana_CapPin, GainMismatch, lowl[12], hil[12], "dB", Test_Item[12], "FAIL_BIN", Test_number[12], Clogenable);

    }
    
    
  return EXIT_SUCCESS;  
}

#endif
