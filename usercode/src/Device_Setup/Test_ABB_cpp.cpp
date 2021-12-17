/* 
 * File:   ABB_Test.cpp
 * Author: dzr
 *
 * Created on 2020年11月10日, 下午3:58
 */



#include <iostream>
#include "GetLog.h" 
#include "UserAPI.h" 
#include "Excel.h"
#include "UserDef.h"
#include "CCS08F.h"
#include "RegDef.h"
#include "Test_ABB.h"
#include "d2sProtocolSSI.h"
#include "D2S_ABB_Module.h"
#include "Globle_Var.h"
#include <synchapi.h>

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
    FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
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



