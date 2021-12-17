/* 
 * File:   ABB_Test.cpp
 * Author: dzr
 *
 * Created on 2020年11月10日, 下午3:48
 */
#include "Systick.h"
#include "GetLog.h" 
#include "UserAPI.h"
#include "UserDef.h"
#include "d2sProtocolSSI.h"
#include "D2S_CAL_Module.h"
#include "D2S_ABB_Module.h"
#include "Test_ABB.h"
#include "CCS08F.h"
#include "RegDef.h"
#include "Globle_Var.h"
#include <math.h>
//#include "RegDef.h"
#include "Excel.h"
#include <vector>
#include <string.h>
#include "linearfit.h"
#include "Globle_Var.h"
#include "CCS08F.h"
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;




//static void WriteData(const char* pszFileName,long long dData[],long lDataSize)
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


int Calc_RC_data(int Site_id,long long *Capwave,CSiteLong *RC_Code,CSiteLong *R_Code,CSiteLong *C_Code)
{
    long long Freq_1M_Wave[64] ={0};
    long long Freq_24M_Wave[64] ={0};
    double  Diff_Wave[64] ={0.0};
    
    double index_MinValue = 10000.0;
    int index_Pos = 0;
    
    double R_var = 0;
    double RC_var = 0;
    double C_var = 0;

    RC_Code->InitDataArray(Site_id, 1);
    R_Code->InitDataArray(Site_id, 1);
    C_Code->InitDataArray(Site_id, 1);


    for(int i = 0; i<=63; i++)
    {
        Freq_1M_Wave[i] = (Capwave[i*4]&0xFFC0)>>6; 
        Freq_1M_Wave[i] = Freq_1M_Wave[i] + ((Capwave[i*4+1]&0x7)<<10);

        Freq_24M_Wave[i] = (Capwave[i*4+2]&0xFFC0)>>6;
        Freq_24M_Wave[i] = Freq_24M_Wave[i] + ((Capwave[i*4+3]&0x7)<<10);
        
        if(Freq_24M_Wave[i] != 0)                                                //
        {
            Diff_Wave[i] = ((double)Freq_1M_Wave[i])/((double)Freq_24M_Wave[i]);    
            Diff_Wave[i] = fabs(Diff_Wave[i]-(511.0/256.0));
        }
        
        if((index_MinValue<Diff_Wave[i])||(i ==0))
        {
            index_MinValue = index_MinValue;
        }
        else
        {
            index_MinValue = Diff_Wave[i];
            index_Pos = i;
        }                             
    }

    RC_Code->SetElement(Site_id,0,index_Pos);
    R_Code->SetElement(Site_id,0,(pb_i_TrimData[Site_id]&0x1C) / 4);
    
    R_var = 120000 / (103327 + 1275.65 * (pb_i_TrimData[Site_id]&0x1C));
    RC_var = (24.0 + 24.0) / (24 + RC_Code->Element(Site_id,0));
    C_var = RC_var / R_var;
    
    if(1.077 < C_var)
    {
        C_Code->SetElement(Site_id,0,0);
    }
    else if(1.045 < C_var && C_var <= 1.077)
    {
        C_Code->SetElement(Site_id,0,1);
    }
    else if(1.016 < C_var && C_var <= 1.045)
    {
        C_Code->SetElement(Site_id,0,2);
    }
    else if(0.988 < C_var && C_var <= 1.016)
    {
        C_Code->SetElement(Site_id,0,3);
    }
    else if(0.961 < C_var && C_var <= 0.988)
    {
        C_Code->SetElement(Site_id,0,4);
    }
    else if(0.936 < C_var && C_var <= 0.961)
    {
        C_Code->SetElement(Site_id,0,5);
    }
    else if(0.912 < C_var && C_var <= 0.936)
    {
        C_Code->SetElement(Site_id,0,6);
    }
    else if(C_var <= 0.912)
    {
        C_Code->SetElement(Site_id,0,7);
    }    
    return EXIT_SUCCESS;
}

int Calc_VI_Det(long long *CAL_V_Code,long long *CAL_I_Code,\
                            long *tempFlow,\
                            long *Delt,\
                            long *Delt_Index,\
                            long *FirstVal,\
                            long *LastVal,\
                            long *Near_125K_Val,\
                            long *Near_125K_Val_index,\
                            double *Poly_Max,\
                            double *Poly_Min,\
                            long *I_FirstCode,\
                            long *I_FirstData,\
                            long *I_HalfCycle,\
                            long *I_VppL,\
                            long *I_CycleL,\
                            long *I_VppH,\
                            long *I_CycleH,\
                            long *I_FlatnessL,\
                            long *I_FlatnessH) 
{
    long n;
    double band_fit_wave[48];//band_fit_wave As New DspWave
    double band_err_wave[48];//band_err_wave As New DspWave
    double Delta[31] = {0};
    double CAL_V_Code_Copy[64] = {0};
    double Cur_I_Wave[204] = {0};
    long minVal;
    long fitLength = 48;
    
    ////// Cal all V parameter, fit from 7~54
    for(int i = 0; i < fitLength; i++ )
    {
        CAL_V_Code_Copy[i] = CAL_V_Code[i + 7];
    }
    
    vector<double> res;
    if(polyUseSimple(3, fitLength, CAL_V_Code_Copy, &res) == false)
    {

        cout<<"----------------------polyUseSimple==false---------------------------------"<<endl;
        return -1;
    }
    for(int i = 0;i < fitLength; i++)
    {
        band_fit_wave[i] = res[0] * pow(i,3) + res[1] * pow(i,2) + res[2] * i +res[3];
        band_err_wave[i] = band_fit_wave[i] - CAL_V_Code_Copy[i];
    }
    
// Debug
//  WriteData("CAL_V_Code",CAL_V_Code,64);
//	WriteData("CAL_V",CAL_V_Code_Copy,fitLength);
//	WriteData("CAL_I_Code",CAL_I_Code,fitLength);
//	WriteData("err_wave",band_err_wave,fitLength);

               
    (*Poly_Max) = band_err_wave[0];
    (*Poly_Min) = band_err_wave[0];
    for(int i = 0; i < fitLength; i++ )
    {
        if((*Poly_Max) < band_err_wave[i])
        {
            (*Poly_Max) = band_err_wave[i];
        }
        if((*Poly_Min) > band_err_wave[i])
        {
            (*Poly_Min) = band_err_wave[i];
        }
    }
    
    (*FirstVal) = CAL_V_Code[0];
    for(int i = 0; i < 64; i++)
    {
        CAL_V_Code[i] = CAL_V_Code[i] - (*FirstVal); // get the offset
    }
    (*LastVal) = CAL_V_Code[63];

    for(int i = 0; i < 64; i++)
    {
        CAL_V_Code_Copy[i] = CAL_V_Code[i] - 31250;//find the 20dBm//s power.
    }
    minVal = fabs(CAL_V_Code_Copy[0]);
    (*Near_125K_Val_index) = 0;
    for(int i = 0; i < 64; i++)
    {
        if(minVal > fabs(CAL_V_Code_Copy[i]))
        {
            minVal = fabs(CAL_V_Code_Copy[i]);
            (*Near_125K_Val_index) = i;
        }
    }
    (*Near_125K_Val) = CAL_V_Code[(*Near_125K_Val_index)];
    
    for(int i = 1; i <= 30; i++){
        Delta[i] = CAL_V_Code[i * 2 + 2] - CAL_V_Code[i * 2]; //Calc the linerity every two codes
    }
    
    Delta[0] = 7000;
    (*Delt) = Delta[0];
    
    
    (*Delt_Index) = 0;
    for(int i = 0; i < 31; i++)
    {
        if((*Delt) > Delta[i])
        {
            (*Delt) = Delta[i];
            (*Delt_Index) = i;
        }
    }
    (*Delt_Index) = (*Delt_Index) * 2;
    
    //******************cal I curve******************************************//// 
    
    ////// Use different coef
    double CAL_I_Diff_Wave[101] = {0};
    double CAL_I_Flag_Wave[101] = {0};
    double CAL_I_Index_Wave[101] = {0};
    
    long Cycle_Start;
    long Cycle_End;
    long Cycle_Half;
    long Cycle_3rd;
    
    for(int i = 0; i < 101; i++){
        CAL_I_Diff_Wave[i] = CAL_I_Code[i + 1] - CAL_I_Code[i];
    }
    
//    api->Set_curve_data("CAL_I_diff", 0, 1/80e6, 100, (double*)CAL_I_Code);
    
    n = 0;
    
    // calculate the Vmin and Vmax, choose the one which is bigger than 3mV
    for(int i = 0; i < 100; i++)
    {
        if(CAL_I_Diff_Wave[i] > 0 && CAL_I_Diff_Wave[i + 1] > 0)
        {
            CAL_I_Flag_Wave[i] = 0;
        }
        else if(CAL_I_Diff_Wave[i] < 0 && CAL_I_Diff_Wave[i + 1] < 0)
        {
            CAL_I_Flag_Wave[i] = 0;
        }
        else if(n == 0 && CAL_I_Flag_Wave[i] > 0 && CAL_I_Flag_Wave[i + 1] <= 0)
        {
            CAL_I_Flag_Wave[i] = 1;
            CAL_I_Index_Wave[n] = i;
            n = n + 1;
        }
        else if(n == 0 && CAL_I_Flag_Wave[i] < 0 && CAL_I_Flag_Wave[i + 1] >= 0)
        {
            CAL_I_Flag_Wave[i] = -1;
            CAL_I_Index_Wave[n] = i;
            n = n + 1;
        }
        else if(i < 2)
        {
            CAL_I_Flag_Wave[i] = -1;
        }
        else if(i > 1 && (CAL_I_Flag_Wave[i - 1] == -1 || CAL_I_Flag_Wave[i - 2] == -1))
        {
            CAL_I_Flag_Wave[i] = 0;
        }
        else if(CAL_I_Flag_Wave[i - 1] == 1 || CAL_I_Flag_Wave[i - 2] == 1)
        {
            CAL_I_Flag_Wave[i] = 0;
        }
        else if(CAL_I_Diff_Wave[i] > 0 && CAL_I_Diff_Wave[i + 1] <= 0)
        {
            CAL_I_Flag_Wave[i] = 1;
            CAL_I_Index_Wave[n] = i;
            n = n + 1;
        }
        else if(CAL_I_Diff_Wave[i] < 0 && CAL_I_Diff_Wave[i + 1] >= 0)
        {
            CAL_I_Flag_Wave[i] = -1;
            CAL_I_Index_Wave[n] = i;
            n = n + 1;
        }
        else
        {
            CAL_I_Flag_Wave[i] = 0;
        }
    }
    
    Cycle_Start = CAL_I_Index_Wave[0] + 1;  //-1
    Cycle_Half = CAL_I_Index_Wave[1] + 1;   //1
    Cycle_3rd = CAL_I_Index_Wave[2] + 1;    //-1
    Cycle_End = CAL_I_Index_Wave[3] + 1;    //1
    
    (*I_FirstData) = CAL_I_Code[Cycle_Start];
    (*I_FirstCode) = Cycle_Start;
    (*I_HalfCycle) = Cycle_Half - Cycle_Start + 1;
    
    (*I_VppL) = CAL_I_Code[Cycle_Half] - CAL_I_Code[Cycle_Start];
    (*I_VppH) = CAL_I_Code[Cycle_End] - CAL_I_Code[Cycle_3rd];
    (*I_CycleL) = Cycle_3rd - Cycle_Start + 1;
    (*I_CycleH) = Cycle_End - Cycle_Half + 1;
    
    (*I_FlatnessL) = fabs(CAL_I_Code[Cycle_3rd] - CAL_I_Code[Cycle_Start]);
    (*I_FlatnessH) = fabs(CAL_I_Code[Cycle_End] - CAL_I_Code[Cycle_Half]);
    
    //L40 temp tests, in case the I wave shift, @2018-11-30
//    if((*tempFlow) != 0)
//    {
//        (*I_VppL) = abs((*I_VppL));
//        (*I_VppH) = abs((*I_VppH));
//        (*I_FirstData) = abs((*I_FirstData)) * -1;
//        (*I_FirstCode) = (*I_FirstCode) % (*I_HalfCycle);
//    }
    
    return EXIT_SUCCESS;
    
}


void Calc_TX_Power_CR_maxSR(SpecAnResultAttribute *ResultAttribute,double Exp_Fre,double Lo,double *Power_Data,double *CR_Data,double *SR_Data)
{
    long Signal_Bin;
    long Carrier_Bin;
    long Image_Bin;
    
    double Signal_dbm;
    double Carrier_dbm;
    double Image_dbm;
    
    double Post_Power;
    double CR;
    double SR;
    
    Signal_Bin = int((Lo+ Exp_Fre- ResultAttribute->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);
    Carrier_Bin = int((Lo - ResultAttribute->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);
    Image_Bin = int((Lo - Exp_Fre- ResultAttribute->dInitiaFrequency)/ResultAttribute->dFrequencyIncrement);
       
    Calc_Power_dbm(ResultAttribute,Signal_Bin,3,&Signal_dbm,0);
    Calc_Power_dbm(ResultAttribute,Carrier_Bin,3,&Carrier_dbm,0);
    Calc_Power_dbm(ResultAttribute,Image_Bin,3,&Image_dbm,0);

    *Power_Data = Signal_dbm;
    *CR_Data = Signal_dbm - Carrier_dbm;
    *SR_Data = Signal_dbm - Image_dbm; 
}



void Write_SingleBand_PPF(char *Channel,int Band,int PPF_Code)
{
    d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s::d2s_LABEL_END();
    
    map<int,long long> reg_val;
    
    long reg_addr;
    FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
       ////int index = api->Get_active_site();
       reg_val[index] = PPF_Code + PPF_Code * 256 + 0x4040;
    FOREACH_ACTIVESITE_END
    if(Band == WLAN_5G_TX_B1_Band||Band == WLAN_5G_RX_A_Band){
        reg_addr = (strstr(Channel,"C0")!=NULL)?0x2A4:0x2C0;
    }
    else if(Band == WLAN_5G_TX_B2_Band||Band == WLAN_5G_RX_B_Band){
        reg_addr = (strstr(Channel,"C0")!=NULL)?0x2A8:0x2C4;
    }
    else if(Band == WLAN_5G_TX_B4_Band){
        reg_addr = (strstr(Channel,"C0")!=NULL)?0x2B0:0x2CC;
    }
    else if(Band == WLAN_5G_TX_B5_Band||Band == WLAN_5G_RX_C_Band){
        reg_addr = (strstr(Channel,"C0")!=NULL)?0x2B4:0x2D0;
    }
    else if(Band == WLAN_5G_TX_B7_Band||Band == WLAN_5G_RX_D_Band){
        reg_addr = (strstr(Channel,"C0")!=NULL)?0x2BC:0x2D8;
    }
    
    d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
    d2s_test.SSI_writeDynamic(reg_addr,reg_val,"write");  
    d2s::d2s_LABEL_END();
}

void Write_SingleBand_PPF_Site(char *Channel,int Band,CSiteLong *PPF_Code)
{
    d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s::d2s_LABEL_END();
    
    map<int,long long> reg_val;
    
    long reg_addr;
    FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
       ////int index = api->Get_active_site();
       reg_val[index] = PPF_Code->Element(index,0) + PPF_Code->Element(index,0) * 256 + 0x4040;
       //api->info_message("Site:%d---------- %s    reg_val    :    %lld-----------",index,"SSI_DATA",reg_val[index]);
    FOREACH_ACTIVESITE_END
    if(Band == WLAN_5G_TX_B1_Band||Band == WLAN_5G_RX_A_Band){
        reg_addr = (strstr(Channel,"C0")!=NULL)?0x2A4:0x2C0;
    }
    else if(Band == WLAN_5G_TX_B2_Band||Band == WLAN_5G_RX_B_Band){
        reg_addr = (strstr(Channel,"C0")!=NULL)?0x2A8:0x2C4;
    }
    else if(Band == WLAN_5G_TX_B4_Band){
        reg_addr = (strstr(Channel,"C0")!=NULL)?0x2B0:0x2CC;
    }
    else if(Band == WLAN_5G_TX_B5_Band||Band == WLAN_5G_RX_C_Band){
        reg_addr = (strstr(Channel,"C0")!=NULL)?0x2B4:0x2D0;
    }
    else if(Band == WLAN_5G_TX_B7_Band||Band == WLAN_5G_RX_D_Band){
        reg_addr = (strstr(Channel,"C0")!=NULL)?0x2BC:0x2D8;
    }
    
    d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
    d2s_test.SSI_writeDynamic(reg_addr,reg_val,"write");  
    d2s::d2s_LABEL_END();
    
    d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
    d2s_test.SSI_read(reg_addr,"readdata",7);
    d2s::d2s_LABEL_END();   
    map<int, long long> capture_data = d2s_test.getReadValue("readdata");

//    FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
//        long long readvalue = d2s_test.getReadValue("readdata");
//        ////int index = api->Get_active_site();
//        //capture_data[index] = readvalue ;
//        //api->info_message("Site:%d---------- %s    read init  value    :    %lld-----------",index,"SSI_DATA",capture_data[index]);
//	FOREACH_ACTIVESITE_END
}




int Get_I_Q_Wave(double *inI_Wave,\
        double *inQ_Wave,\
        long I_Size,\
        int Shift_Point,\
        double *IWave,\
        double *QWave) 
{
    long i; 
    
    long X_size =  I_Size*2 + 7;
    long Y_size = I_Size + 3;
    
    double X_Wave[X_size]; 
    double Y_Wave[I_Size];    
    
    /*
    For i = 0 To X_size - 1
        If i < 7 Then
            X_Wave.Element(i) = 0
        Else
            X_Wave.Element(i) = inQ_Wave.Element(i - 7)
        End If
    Next i
    */
    for(i = 0; i < X_size; i++)
    {
        if(i < 7)
        {
            X_Wave[i] = 0;
        }
        else
        {
            X_Wave[i] = inQ_Wave[i - 7];
        }
    }
    
    /*
    'interleave Q Data and remove the first 10 points.
    For i = 4 + Shift_Point To Y_size + Shift_Point
        
        Y_Wave.Element(i - 4 - Shift_Point) = (X_Wave.Element(i + 7) + X_Wave.Element(i)) * (-2) _
                            + (X_Wave.Element(i + 6) + X_Wave.Element(i + 1)) * 18 _
                            + (X_Wave.Element(i + 5) + X_Wave.Element(i + 2)) * (-71) _
                            + (X_Wave.Element(i + 4) + X_Wave.Element(i + 3)) * 311
    Next i
    */
    for(i = 4 + Shift_Point; i <= Y_size + Shift_Point; i++)
    {
        Y_Wave[i - 4 - Shift_Point] = (X_Wave[i + 7] + X_Wave[i]) * (-2) \
                            + (X_Wave[i + 6] + X_Wave[i + 1]) * 18 \
                            + (X_Wave[i + 5] + X_Wave[i + 2]) * (-71) \
                            + (X_Wave[i + 4] + X_Wave[i + 3]) * 311;
    }
    
    /*
    IWave.CreateConstant 0, SampleSize, DspDouble
    QWave.CreateConstant 0, SampleSize, DspDouble
    */
    
    /*
    Set QWave = Y_Wave.Divide(512).Copy
    Set IWave = inI_Wave.Select(Shift_Point, 1, SampleSize).Copy
    */   
    for(i = 0; i <= I_Size; i++)
    {
        QWave[i] = Y_Wave[i] / 512.0;
    }
    for(i = 0; i <= I_Size; i++)
    {
        IWave[i] = inI_Wave[Shift_Point + i];
    }
}

int Calc_WLAN_IQ_PE_VBT(int index,int Capsize,CSiteLong *Capwave,\
                                        long *gCos, \
                                        long *gSin, \
                                        double *E_Value, \
                                        double *P_Value)
{                
    double I_cos_wave; 
    double Q_SIN_wave; 
    double I_SIN_wave; 
    double Q_cos_wave; 
    
    double result_I_cos; 
    double result_Q_SIN; 
    double result_I_SIN; 
    double result_Q_cos; 
    
    double l_if_minus; 
    double l_qf_minus; 
    double l_if_plus; 
    double l_qf_plus; 
    
    double numReal;
    double numImage;
    
    double denomReal; 
    double denomImage; 
        
    double denomPower; 

    long Sample_Size;
    long I_Size; 
      
//    E_Value->InitDataArray(index, 6);
//    P_Value->InitDataArray(index, 6);

    Sample_Size = Capsize / 64;//4096/64 = 64
    I_Size = Sample_Size / 2;
    
    double IWave[I_Size];
    double QWave[I_Size];
    long Capwave_tmp;
    
    for(int i = 0; i <= Sample_Size - 1; i++)
    {
        if(Capwave->Element(index,i) > 512)
        {
            Capwave_tmp = Capwave->Element(index,i) - pow(2,10);
            Capwave->SetElement(index,i,Capwave_tmp);
        }
    }
    
    double IWave_Temp[64]={0.0}; 
    double QWave_Temp[64]={0.0};
    
    for(int i = 0; i < Sample_Size; i++)
    {
        double div1 = 0;
        double temp_IWave_Temp = 0;
        for(int j = i * 2; j < Capsize;j += 64); 
        {
            temp_IWave_Temp += Capwave->Element(index,i*2);
            div1++;        
            //j += 64;
        }
        IWave_Temp[i] = temp_IWave_Temp / div1;
        
        double div2 = 0;
        double temp_QWave_Temp = 0;
        for(int j = i * 2 + 1; j < Capsize;j+=64); 
        {
            temp_QWave_Temp +=Capwave->Element(index,i*2+1);
            div2++;        
            //j += 64;
        }
        QWave_Temp[i] = temp_QWave_Temp / div2;
    }
    
//    api->CSV_write_rows("RXIQ_I.txt", Sample_Size,  THE_DOUBLE_ARRAY, IWave_Temp, THE_END);
//    api->CSV_write_rows("RXIQ_Q.txt", Sample_Size,  THE_DOUBLE_ARRAY, QWave_Temp, THE_END);
    
//    api->Set_curve_data("IWave_Temp", 0, 1/160e6, Sample_Size, IWave_Temp);   //打印FFT波形
//    api->Set_curve_data("QWave_Temp", 0, 1/160e6, Sample_Size, QWave_Temp);
    
    Get_I_Q_Wave(IWave_Temp, QWave_Temp, I_Size, 8, IWave, QWave);

    I_cos_wave = 0;
    for(int i = 0; i < 32; i++)
    {
        I_cos_wave += (IWave[i] * gCos[i]);
    }
    Q_SIN_wave = 0;
    for(int i = 0; i < 32; i++)
    {
        Q_SIN_wave += (QWave[i] * gSin[i]);
    }
    I_SIN_wave = 0;
    for(int i = 0; i < 32; i++)
    {
        I_SIN_wave += (IWave[i] * gSin[i]);
    }
    Q_cos_wave = 0;
    for(int i = 0; i < 32; i++)
    {
        Q_cos_wave += (QWave[i] * gCos[i]);
    }

    result_I_cos = I_cos_wave;
    result_Q_SIN = Q_SIN_wave;
    result_I_SIN = I_SIN_wave;
    result_Q_cos = Q_cos_wave;
    
    l_if_minus = (result_I_cos - result_Q_SIN) / 512;
    l_qf_minus = (result_I_SIN + result_Q_cos) / 512;
    l_if_plus = (result_I_cos + result_Q_SIN) / 512;
    l_qf_plus = (-result_I_SIN + result_Q_cos) / 512;
    // --------------------- Complex Division ------------------------------------

    /*
    numReal = l_if_minus
    numImage = l_qf_minus   'a + bi
    */
    numReal = l_if_minus;
    numImage = l_qf_minus;
    /*
    denomReal = l_if_plus + l_if_minus
    denomImage = l_qf_minus - l_qf_plus  'c + di
    denomPower = (denomReal / 32) ^ 2 + (denomImage / 32) ^ 2
    */
    denomReal = l_if_plus + l_if_minus;
    denomImage = l_qf_minus - l_qf_plus;
    denomPower = pow((denomReal / 32.0),2) + pow((denomImage / 32.0),2);

    //(a + bi) / (c + di) = x + yi     power = c^2 + d^2    x = (ac + bd) / power      y= (bc - ad) / power

    if( denomPower == 0 ){
        *E_Value = 999.0;
        *P_Value = 999.0;
    }else{
        *E_Value = (numReal * denomReal + numImage * denomImage) / denomPower;
        *P_Value = -(numImage * denomReal - numReal * denomImage) / denomPower;
    }
    
    return EXIT_SUCCESS;
}



int DSP_WLAN_IQ_P_FIT_VBT(double *P_Wave, double *P_MaxError, double *Freq_MaxError, double *AvgError)
{

    double raw_P_BestFitWave[6]; 
    double P_BestFitWave[6];
    double P_ErrorWave[6]; 
    long MaxErrorIndex; 

    
//    Set raw_P_BestFitWave = P_Wave.FitPolynomial(1)
//    P_BestFitWave.CreatePolynomial raw_P_BestFitWave, 6
    
    vector<double> res;
    if(polyUseSimple(1, 6, P_Wave, &res) == false) //
    {
        return -1;
    }
    for(int i = 0;i < 6; i++)
    {
        P_BestFitWave[i] = res[1] * i +res[0];
    }
    
    /*
    P_ErrorWave = P_BestFitWave.Subtract(P_Wave)
    P_MaxError = P_ErrorWave.Abs.CalcMaximumValue(MaxErrorIndex)
    AvgError = P_ErrorWave.Abs.CalcMean
    */
    for(int i = 0;i < 6; i++)
    {
        P_ErrorWave[i] = P_BestFitWave[i] - P_Wave[i];
    }
    *P_MaxError = P_ErrorWave[0];
    MaxErrorIndex = 0;
    for(int i = 0;i < 6; i++)
    {
        if(*P_MaxError < P_ErrorWave[i])
        {
            *P_MaxError = P_ErrorWave[i];
            MaxErrorIndex = i;
        }
    }
    *AvgError = 0;
    for(int i = 0; i < 6; i++)
    {
        *AvgError += fabs(P_ErrorWave[i]);
    }
    *AvgError /= 6;
    
    if(MaxErrorIndex == 0) *Freq_MaxError = -35;
    if(MaxErrorIndex == 1) *Freq_MaxError = -25;
    if(MaxErrorIndex == 2) *Freq_MaxError = -5;
    if(MaxErrorIndex == 3) *Freq_MaxError = 5;
    if(MaxErrorIndex == 4) *Freq_MaxError = 25;
    if(MaxErrorIndex == 5) *Freq_MaxError = 35;

}

int CAL_RX_Phase() {
    
    //const char* testname = NULL;
    string testname = TheSoft.Flow().Test().GetCurrentTestName();
    //testname = api->Get_current_test_name();
    CSiteLong SiteData;
    double Freq_List[6] = {-35E6,-25E6,-5E6,5E6,25E6,35E6};
    
    //auto site;
    //double i;
    char* RF_Src_Label;
//    double myWave[];
    long gCos[32];
    long gSin[32];
    //string Freq_Array[];
    double E_wave[24];
    double P_Wave[24];
    CSiteDouble E_array;
    CSiteDouble P_array;
    double e_val;
    double p_val;
    CSiteDouble P_MaxError;
    CSiteDouble P_AvgError;
    CSiteDouble Freq_MaxError;
    
    char *RF_SrcPin;
    char Src_Pin_C0[32]="RF_RFI_5G_C0";
    char Src_Pin_C1[32]="RF_RFI_5G_C1";
    char RF_SrcSignal[32]={"\0"};
    
    int P_Wave_Size = 0;
    
    ///////////////run patten,if channel = C0,then RX_5G_C0_RFI;if channel  =C1,then RX_5G_C1_RFI
    
//        Test_Mode_Init_Setup(WLAN_5G_Mode, RX_Path, "C0");
//        TestMUX_Init_Setup(RX_Path, "C0");
    
    if(strstr(testname.c_str(),"C0")!=NULL){
        RXIQ_5G_C0_Set_Module();
        RX_PLL_Setup( WLAN_5G_Mode,WLAN_5G_RX_D_Band,"C0",40e6);
        RF_SrcPin = Src_Pin_C0;
    }
    else{
        RXIQ_5G_C1_Set_Module();
        RX_PLL_Setup( WLAN_5G_Mode,WLAN_5G_RX_D_Band,"C1",40e6);
        RF_SrcPin = Src_Pin_C1;
    }
    
    for(int i = 0; i < 1; i++)
    {

        sprintf(RF_SrcSignal, "MWsrc_RX5G_D_PHASE_C0_%dM", Freq_List[i]);
        MWSource_Signal_CW(WLAN_RX_5G_D_Freq + Freq_List[i],-30,RF_SrcSignal);
        
        CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Configure();
        CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Start();

        if(strstr(testname.c_str(),"C0")!=NULL){
            WL_RX_CAL_PHASE_ADC_C0_Cap_Module(&SiteData);
        }
        else{
            WL_RX_CAL_PHASE_ADC_C1_Cap_Module(&SiteData);
        }
        double nData[4096];
        for(int j=0;j<1024;j++){
            nData[j]=SiteData(0,2*j);
            if(nData[j]>512){
                nData[j]=nData[j]-1024;
            }
        }
//        api->CSV_write_rows("measure.txt", 2048,  THE_DOUBLE_ARRAY, nData, THE_END);
//        api->Set_curve_data("RXIQ_I", 0, 1/160e6, 1024, nData);   //打印FFT波形
//        api->Set_curve_data("RXIQ_Q", 0, 1/160e6, Sample_Size, QWave_Temp);

        CCRFTester.RFSRC(RF_SrcPin).SIGNAL(RF_SrcSignal).Stop();

        if(Freq_List[i] == 35E6 || Freq_List[i] == -35E6)
        {
//            gCos = CosLut_35M;
//            gSin = SinLut_35M;
            memcpy(gCos,CosLut_35M,32*sizeof(long));
            memcpy(gSin,SinLut_35M,32*sizeof(long));
        }
        else if(Freq_List[i] == 25E6 || Freq_List[i] == -25E6)
        {
//            gCos = CosLut_25M;
//            gSin = SinLut_25M;
            memcpy(gCos,CosLut_25M,32*sizeof(long));
            memcpy(gSin,SinLut_25M,32*sizeof(long));
        }
        else
        {
//            gCos = CosLut_5M;
//            gSin = SinLut_5M;
            memcpy(gCos,CosLut_5M,32*sizeof(long));
            memcpy(gSin,SinLut_5M,32*sizeof(long));
        }
        //api->info_message("---------- %s    Freq_List    :    %d-----------","SSI_DATA",Freq_List[i]);
        printf("---------- %s    Freq_List    :    %d-----------","SSI_DATA",Freq_List[i]);
        FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
            //int index = api->Get_active_site();
//            long long Capwave[4096];
            double E_data=0;
            double P_data=0;
            
            if(i ==0)
            {
                E_array.InitDataArray(index, 6);
                P_array.InitDataArray(index, 6);
            }
            
//            for(intk =0;k<4096;k++)
//            {
//                Capwave[k] = SiteData(index,k)
//            }
            
            Calc_WLAN_IQ_PE_VBT(index,4096, &SiteData, gCos, gSin, &E_data, &P_data);// E_array、P_array应该为出参
            
            E_array.SetElement(index,i,E_data);
            printf("Site:%d---------- %s    E_array    :    %f-----------",index,"SSI_DATA",E_array(index,i));
            P_array.SetElement(index,i,P_data);
            printf("Site:%d---------- %s    P_array    :    %f-----------",index,"SSI_DATA",P_array(index,i));
                    
		FOREACH_ACTIVESITE_END
        
    }  
    
    FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
        //int index = api->Get_active_site();
        double wavearray[6] ={0};
        double P_MaxErrordata;
        double Freq_MaxErrordata;
        double P_AvgErrordata;
        
        for(int j=0;j<6;j++)
        {
           wavearray[j]=P_array.Element(index,j);
        }
    
        DSP_WLAN_IQ_P_FIT_VBT( wavearray, &P_MaxErrordata, &Freq_MaxErrordata, &P_AvgErrordata);
        
        P_MaxError.SetElement(index,0,P_MaxErrordata);
        printf("Site:%d---------- %s    P_MaxError    :    %f-----------",index,"SSI_DATA",P_MaxError(index,0));
        Freq_MaxError.SetElement(index,0,Freq_MaxErrordata);
        printf("Site:%d---------- %s    Freq_MaxError    :    %f-----------",index,"SSI_DATA",Freq_MaxError(index,0));
        P_AvgError.SetElement(index,0,P_AvgErrordata);
        printf("Site:%d---------- %s    P_AvgError    :    %f-----------",index,"SSI_DATA",P_AvgError(index,0));
	FOREACH_ACTIVESITE_END
    if(strstr(testname.c_str(),"C0")!=NULL){
        RXIQ_5G_C0_Restore_Module();
    }
    else{
        RXIQ_5G_C1_Restore_Module();
    } 
    return EXIT_SUCCESS;
}





int Calc_PD_BUF(string Channel,bool GPIO_Flag,int num,double *Force_Val)
{

	if(Channel == "C1")
	{
		TheInst.PPMU().Pins("DBB_GPIO1").SetClear()
										.SetMeasureType(PhxAPI::E_MEASURE)
										.SetIClampH(5e-3)
										.SetIClampL(-5e-3)
										.SetIRange(5e-3)
										.SetVForce(0.2)			// DEBUG 0.3V
										.SetMeasureMode(PhxAPI::E_DC_FV_MV)
										.Connect(true)
										.SetSampleSize(1)//2
										.SetWaitTime(2*ms)
										.Measure();
	}

    double hil[30],lowl[30];
    vector<string> Test_Item;
	vector<string> Units;
    int  Test_number[30];
    int Soft_Bin[30];
	int Hard_Bin[30];
	Read_Limit(lowl,hil,Test_Item,Test_number,Units,Soft_Bin,Hard_Bin);

    const char* testname = NULL; 
    char Ana_Src_Signal[32] = {"\0"};
    char *Ana_SrcPin = "RF_TEST_TX_IP";  
    CSiteLong pReadValue;
    CSiteLong pReadValue0;
    CSiteLong pReadValue1;
    
    unsigned int sitestmp[MAX_SITES] = {0,0,0,0};
    unsigned int sites[MAX_SITES] = {0}; 

    vector<int> active_sites = TheSoft.Sites().Active().GetActiveSites();
    unsigned int active_sites_size = TheSoft.Sites().Active().GetActiveSiteCount();

    for(unsigned int i=0;i<active_sites_size;i++)
    {
        sitestmp[i]=active_sites[i];
    }
       
    if(GPIO_Flag==true)
    {
        
//        api->Set_loadboard_x_ubits(X_UBIT_NONE,X_UBIT_051 + X_UBIT_024 + X_UBIT_020 + X_UBIT_065);
//        api->Set_loadboard_x_ubits(X_UBIT_NONE,X_UBIT_019 + X_UBIT_033 + X_UBIT_011 + X_UBIT_056);
        
        if(Channel == "C0"){
            PDBUF_DET_C0_Set_Module();
            d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
            d2sProtocolSSI d2s_test;
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x68, 0x50);
            d2s_test.SSI_write(0x5C, 0x0);
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x94, false);
            d2s_test.SSI_write(0x18, 0x82);
            d2s::d2s_LABEL_END();

        }
        else
        {
            PDBUF_DET_C1_Set_Module();
            d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
            d2sProtocolSSI d2s_test;
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x68, 0x50);
            d2s_test.SSI_write(0x5C, 0x0);
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x94, false);
            d2s_test.SSI_write(0x94, 0x82); 
            d2s::d2s_LABEL_END();
        }
    }
    else
    {
        int UtilitySites1[8] = {51,24,20,65,19,33,11,56};
    	for(uint32_t j=0;j<8;j++)
    	{
    		TheInst.Util().SetRelayState(UtilitySites1[j], PhxAPI::E_UTIL_STATE_ON); //bihe-0,duankai-1
    	}
    }
    
    double nData[512];
    double nData0[512];
    double nData1[512];
    double PD_average = 0.0;
    double PD_max = 0.0;
    double PD_min = 0.0;
    double dSum = 0.0;
    double C0_PD_average[4];
    double C1_PD_average[4];
    
    if(GPIO_Flag==true)
    {
        for(int i=0;i<num;i++)
        {
            if(Channel == "C0"){
                WL_PD_BUF_GPIO1_ADC_C0_Cap_Module(&pReadValue);
                PDBUF_DET_C0_Restore_Module();
            }
            else{
                WL_PD_BUF_GPIO1_ADC_C1_Cap_Module(&pReadValue);
                PDBUF_DET_C1_Restore_Module();
            }

            FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
                for(int i=0;i<32;i++){
                    nData[i] = pReadValue(index,i*2+1);
                    if(nData[i] > 512){
                        nData[i] = nData[i] - 1024;
                    }

                }
//                api->Set_curve_data("PD_BUF_GPIO", 0, 1/80e6, 32, nData);

                dSum = 0.0;
                PD_average = 0;
                PD_max = 0;
                PD_min = 0;

                for(int i=0;i<32;i++){
                    dSum += nData[i];
                    if(PD_max <= nData[i])
                    {
                        PD_max = nData[i];
                    }

                    if((PD_min >= nData[i])||(PD_min == 0))
                    {
                        PD_min = nData[i];
                    }
                }
                PD_average = dSum/32 - C1_PD_average[index];

                TheSoft.Flow().TestLimit("RF_TEST_TX_IP",index,  PD_average, lowl[7], hil[7],Hard_Bin[7],Soft_Bin[7], "", Test_Item[7],Test_number[7]);
			FOREACH_ACTIVESITE_END
        }
    }
    else
    {
        LoadSignal_MIX_DC(0.6,Ana_Src_Signal); 
        CCRFTester.SelectSites("site0,site2");
        SrcUtilitySites0();

        CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
        CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start(); 


        vector<int> vec_Site;
        vec_Site.push_back(0);
        vec_Site.push_back(2);
        TheSoft.Sites().Active().SetActive(vec_Site);
        PDBUF_C0_C1_Module( &pReadValue0, &pReadValue1);
        CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();

        for(int i=0;i<4;i++)
        {
            sites[i]=sitestmp[i];
        }
        vec_Site.clear();
        vec_Site.push_back(1);
        vec_Site.push_back(3);
        TheSoft.Sites().Active().SetActive(vec_Site);
        CCRFTester.ActiveSites(sites,active_sites_size);                        		//recover the sites information for RF
        
        CCRFTester.SelectSites("site1,site3");
        SrcUtilitySites1();
        CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Configure();
        CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Start(); 


        PDBUF_C0_C1_Module( &pReadValue0, &pReadValue1);
        
        CCRFTester.MIXSRC(Ana_SrcPin).SIGNAL(Ana_Src_Signal).Stop();
        
        vec_Site.clear();
        for(unsigned int i=0;i<active_sites_size;i++)
        {
            sites[i]=sitestmp[i];
            vec_Site.push_back(sitestmp[i]);
        }
        TheSoft.Sites().Active().SetActive(vec_Site);
        CCRFTester.ActiveSites(sites,active_sites_size);                        //recover the sites information for RF
        SrcUtilitySites0();                                                  //recover Relay state

        FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
            for(int i=0;i<512;i++){
                
                nData0[i] = pReadValue0(index,i*2+1);
                nData1[i] = pReadValue1(index,i*2+1);
                if(nData0[i] > 512){
                    nData0[i] = nData0[i] - 1024;
                }
                if(nData1[i] > 512){
                    nData1[i] = nData1[i] - 1024;
                }
                
            }
           
//            api->Set_curve_data("ADC_C0", 0, 1/80e6, 512, nData0);
//            api->Set_curve_data("ADC_C1", 0, 1/80e6, 512, nData1);
            
            dSum = 0.0;
            PD_average = 0;
            PD_max = 0;
            PD_min = 0;

            for(int i=0;i<512;i++){
                dSum += nData0[i];

            }
            PD_average = dSum/512;
            
            sort(nData0, nData0+512);

            /*****Get average of 3 min******/
            for(int i=0; i<6; i++){
               PD_min += nData0[i];
            }           
            PD_min = PD_min/6 - PD_average;
            
            /*****Get average of 3 max******/
            for(int i=506; i<512; i++){
               PD_max += nData0[i];
            }           
            PD_max = PD_max/6 - PD_average;
            
            C0_PD_average[index] = PD_average;


            TheSoft.Flow().TestLimit( "RF_TEST_TX_IP",index, PD_average, lowl[0], hil[0],Hard_Bin[0],Soft_Bin[0], "", Test_Item[0],Test_number[0]);
            TheSoft.Flow().TestLimit( "RF_TEST_TX_IP",index, PD_min, lowl[1], hil[1],Hard_Bin[1],Soft_Bin[1], "", Test_Item[1],Test_number[1]);
            TheSoft.Flow().TestLimit( "RF_TEST_TX_IP",index, PD_max, lowl[2], hil[2],Hard_Bin[2],Soft_Bin[2], "", Test_Item[2],Test_number[2]);

            dSum = 0.0;
            PD_average = 0;
            PD_max = 0;
            PD_min = 0;
            
            for(int i=0;i<512;i++){
                dSum += nData1[i];
            }
            PD_average = dSum/512;
            
            sort(nData1, nData1+512);
            
            /*****Get average of 3 min******/
            for(int i=0; i<6; i++){
               PD_min += nData1[i];
            }        
            PD_min = PD_min/6 - PD_average;
            
            /*****Get average of 3 max******/
            for(int i=506; i<512; i++){
               PD_max += nData1[i];
            }         
            PD_max = PD_max/6 - PD_average;
            
            C1_PD_average[index] = PD_average;

            TheSoft.Flow().TestLimit( "RF_TEST_TX_IP",index, PD_average, lowl[3], hil[3],Hard_Bin[3],Soft_Bin[3], "", Test_Item[3],Test_number[3]);
            TheSoft.Flow().TestLimit( "RF_TEST_TX_IP",index,  PD_min, lowl[4], hil[4],Hard_Bin[4],Soft_Bin[4], "", Test_Item[4], Test_number[4]);
            TheSoft.Flow().TestLimit( "RF_TEST_TX_IP",index,  PD_max, lowl[5], hil[5],Hard_Bin[5],Soft_Bin[5], "", Test_Item[5], Test_number[5]);

		FOREACH_ACTIVESITE_END
    }
    
	if(Channel == "C1")
	{
		TheInst.PPMU().Pins("DBB_GPIO1").SetClear()
										.SetMeasureType(PhxAPI::E_MEASURE)
										.SetIClampH(5e-3)
										.SetIClampL(-5e-3)
										.SetIRange(5e-3)
										.SetVForce(0)			// clear
										.SetMeasureMode(PhxAPI::E_DC_FV_MV)
										.Connect(true)
										.SetSampleSize(1)//2
										.SetWaitTime(2*ms)
										.Measure();
		TheInst.PPMU().Pins("DBB_GPIO1").Connect(false).Apply();
	}

	return EXIT_SUCCESS;
}



int Write_RC_PPF(int TRX,char *Channel)
{
    Write_RC_C_CODE(Channel);
    
//    CSiteLong PPF_CODE_A_Band;
//    CSiteLong PPF_CODE_B_Band;
//    CSiteLong PPF_CODE_C_Band;
//    CSiteLong PPF_CODE_D_Band;
//    
//    CSiteLong PPF_CODE_B2_Band;
//    CSiteLong PPF_CODE_B4_Band;
//    CSiteLong PPF_CODE_B7_Band;
//    
//    FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
//    //int index = api->Get_active_site();
//        PPF_CODE_A_Band.InitDataArray(index, 1);
//        PPF_CODE_B_Band.InitDataArray(index, 1);
//        PPF_CODE_C_Band.InitDataArray(index, 1);
//        PPF_CODE_D_Band.InitDataArray(index, 1);
//
//        PPF_CODE_B2_Band.InitDataArray(index, 1);
//        PPF_CODE_B4_Band.InitDataArray(index, 1);
//        PPF_CODE_B7_Band.InitDataArray(index, 1);
//    }
//       
//    if(strstr(Channel,"C0")!=NULL)
//    //if(Channel=="C0")
//    {
//        if(TRX == RX_Path)
//        {
//            FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
//            //int index = api->Get_active_site();
//                PPF_CODE_A_Band.SetElement(index,0,WL_C0_PPF_CODE(index,WLAN_5G_RX_A_Band));
//                api->info_message("Site:%d---------- %s    PPF_CODE_A_Band    :    %lld-----------",index,"SSI_DATA",PPF_CODE_A_Band(index,0));
//                api->info_message("Site:%d---------- %s    WL_C0_PPF_CODE    :    %lld-----------",index,"SSI_DATA",WL_C0_PPF_CODE(index,WLAN_5G_RX_A_Band));
//                PPF_CODE_B_Band.SetElement(index,0,WL_C0_PPF_CODE(index,WLAN_5G_RX_B_Band));
//                PPF_CODE_C_Band.SetElement(index,0,WL_C0_PPF_CODE(index,WLAN_5G_RX_C_Band));
//                PPF_CODE_D_Band.SetElement(index,0,WL_C0_PPF_CODE(index,WLAN_5G_RX_D_Band));
//            }
//            Write_SingleBand_PPF_Site(Channel, WLAN_5G_RX_A_Band,&PPF_CODE_A_Band);
//            Write_SingleBand_PPF_Site(Channel, WLAN_5G_RX_B_Band,&PPF_CODE_B_Band);
//            Write_SingleBand_PPF_Site(Channel, WLAN_5G_RX_C_Band,&PPF_CODE_C_Band);
//            Write_SingleBand_PPF_Site(Channel, WLAN_5G_RX_D_Band,&PPF_CODE_D_Band);
//        }
//        else
//        {
//            FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
//            //int index = api->Get_active_site();
//                PPF_CODE_B2_Band.SetElement(index,0,WL_C0_PPF_CODE(index,WLAN_5G_TX_B2_Band));
//                api->info_message("Site:%d---------- %s    PPF_CODE_B2_Band    :    %lld-----------",index,"SSI_DATA",PPF_CODE_B2_Band(index,0));
//                api->info_message("Site:%d---------- %s    WL_C0_PPF_CODE    :    %lld-----------",index,"SSI_DATA",WL_C0_PPF_CODE(index,WLAN_5G_TX_B2_Band));
//                PPF_CODE_B4_Band.SetElement(index,0,WL_C0_PPF_CODE(index,WLAN_5G_TX_B4_Band));
//                PPF_CODE_B7_Band.SetElement(index,0,WL_C0_PPF_CODE(index,WLAN_5G_TX_B7_Band));
//            }
//            Write_SingleBand_PPF_Site(Channel, WLAN_5G_TX_B2_Band, &PPF_CODE_B2_Band);
//            Write_SingleBand_PPF_Site(Channel, WLAN_5G_TX_B4_Band, &PPF_CODE_B4_Band);
//            Write_SingleBand_PPF_Site(Channel, WLAN_5G_TX_B7_Band, &PPF_CODE_B7_Band);
//        }
//    }
//    else if(strstr(Channel,"C1")!=NULL)
//    {
//        if(TRX == RX_Path)
//        {
//            FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
//            //int index = api->Get_active_site();
//                PPF_CODE_A_Band.SetElement(index,0,WL_C1_PPF_CODE(index,WLAN_5G_RX_A_Band));
//                PPF_CODE_B_Band.SetElement(index,0,WL_C1_PPF_CODE(index,WLAN_5G_RX_B_Band));
//                PPF_CODE_C_Band.SetElement(index,0,WL_C1_PPF_CODE(index,WLAN_5G_RX_C_Band));
//                PPF_CODE_D_Band.SetElement(index,0,WL_C1_PPF_CODE(index,WLAN_5G_RX_D_Band));
//            }
//            
//            Write_SingleBand_PPF_Site(Channel, WLAN_5G_RX_A_Band, &PPF_CODE_A_Band);
//            Write_SingleBand_PPF_Site(Channel, WLAN_5G_RX_B_Band, &PPF_CODE_B_Band);
//            Write_SingleBand_PPF_Site(Channel, WLAN_5G_RX_C_Band, &PPF_CODE_C_Band);
//            Write_SingleBand_PPF_Site(Channel, WLAN_5G_RX_D_Band, &PPF_CODE_D_Band);
//        }
//        else
//        {
//            FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
//            //int index = api->Get_active_site();
//                PPF_CODE_B2_Band.SetElement(index,0,WL_C1_PPF_CODE(index,WLAN_5G_TX_B2_Band));
//                PPF_CODE_B4_Band.SetElement(index,0,WL_C1_PPF_CODE(index,WLAN_5G_TX_B4_Band));
//                PPF_CODE_B7_Band.SetElement(index,0,WL_C1_PPF_CODE(index,WLAN_5G_TX_B7_Band));
//            }
//            Write_SingleBand_PPF_Site(Channel, WLAN_5G_TX_B2_Band, &PPF_CODE_B2_Band);
//            Write_SingleBand_PPF_Site(Channel, WLAN_5G_TX_B4_Band, &PPF_CODE_B4_Band);
//            Write_SingleBand_PPF_Site(Channel, WLAN_5G_TX_B7_Band, &PPF_CODE_B7_Band);
//        }
//    }
        
    return EXIT_SUCCESS;
}

int Update_All_RC_PPF_vbt()
{
    char channelC0[5] = "C0";
    char channelC1[5] = "C1";
    
    Write_RC_PPF(RX_Path, channelC0);
    Write_RC_PPF(RX_Path, channelC1);
    Write_RC_PPF(TX_Path, channelC0);
    Write_RC_PPF(TX_Path, channelC1);
    
    return EXIT_SUCCESS;
}


void Load_PPF()
{                                                
    WL5G_B1_PPF[0] = 11;
    WL5G_B1_PPF[1] = 11;
    WL5G_B1_PPF[2] = 11;
    WL5G_B1_PPF[3] = 11;
    WL5G_B1_PPF[4] = 11;
    WL5G_B1_PPF[5] = 11;
    WL5G_B1_PPF[6] = 11;
    WL5G_B1_PPF[7] = 11;
    WL5G_B1_PPF[8] = 11;
    WL5G_B1_PPF[9] = 11;
    WL5G_B1_PPF[10] = 11;
    WL5G_B1_PPF[11] = 10;
    WL5G_B1_PPF[12] = 9;
    WL5G_B1_PPF[13] = 9;
    WL5G_B1_PPF[14] = 9;
    WL5G_B1_PPF[15] = 8;
    WL5G_B1_PPF[16] = 6;
    WL5G_B1_PPF[17] = 6;
    WL5G_B1_PPF[18] = 5;
    WL5G_B1_PPF[19] = 5;
    WL5G_B1_PPF[20] = 5;
    WL5G_B1_PPF[21] = 5;
    WL5G_B1_PPF[22] = 4;
    WL5G_B1_PPF[23] = 4;
    WL5G_B1_PPF[24] = 4;
    WL5G_B1_PPF[25] = 3;
    WL5G_B1_PPF[26] = 3;
    WL5G_B1_PPF[27] = 2;
    WL5G_B1_PPF[28] = 2;
    WL5G_B1_PPF[29] = 2;
    WL5G_B1_PPF[30] = 2;
    WL5G_B1_PPF[31] = 2;
    WL5G_B1_PPF[32] = 2;
    WL5G_B1_PPF[33] = 0;
    WL5G_B1_PPF[34] = 0;
    WL5G_B1_PPF[35] = 0;
    WL5G_B1_PPF[36] = 0;
    WL5G_B1_PPF[37] = 0;
    WL5G_B1_PPF[38] = 0;
    WL5G_B1_PPF[39] = 0;
    WL5G_B1_PPF[40] = 0;
    WL5G_B1_PPF[41] = 0;
    WL5G_B1_PPF[42] = 0;
    WL5G_B1_PPF[43] = 0;
    WL5G_B1_PPF[44] = 0;
    WL5G_B1_PPF[45] = 0;
    WL5G_B1_PPF[46] = 0;
    WL5G_B1_PPF[47] = 0;
    WL5G_B1_PPF[48] = 0;
    WL5G_B1_PPF[49] = 0;
    WL5G_B1_PPF[50] = 0;
    WL5G_B1_PPF[51] = 0;
    WL5G_B1_PPF[52] = 0;
    WL5G_B1_PPF[53] = 0;
    WL5G_B1_PPF[54] = 0;
    WL5G_B1_PPF[55] = 0;
    WL5G_B1_PPF[56] = 0;
    WL5G_B1_PPF[57] = 0;
    WL5G_B1_PPF[58] = 0;
    WL5G_B1_PPF[59] = 0;
    WL5G_B1_PPF[60] = 0;
    WL5G_B1_PPF[61] = 0;
    WL5G_B1_PPF[62] = 0;
    WL5G_B1_PPF[63] = 0;
                                                    
    WL5G_B2_PPF[0] = 12;
    WL5G_B2_PPF[1] = 12;
    WL5G_B2_PPF[2] = 12;
    WL5G_B2_PPF[3] = 12;
    WL5G_B2_PPF[4] = 12;
    WL5G_B2_PPF[5] = 12;
    WL5G_B2_PPF[6] = 12;
    WL5G_B2_PPF[7] = 12;
    WL5G_B2_PPF[8] = 12;
    WL5G_B2_PPF[9] = 12;
    WL5G_B2_PPF[10] = 12;
    WL5G_B2_PPF[11] = 11;
    WL5G_B2_PPF[12] = 10;
    WL5G_B2_PPF[13] = 10;
    WL5G_B2_PPF[14] = 10;
    WL5G_B2_PPF[15] = 9;
    WL5G_B2_PPF[16] = 7;
    WL5G_B2_PPF[17] = 7;
    WL5G_B2_PPF[18] = 6;
    WL5G_B2_PPF[19] = 6;
    WL5G_B2_PPF[20] = 6;
    WL5G_B2_PPF[21] = 6;
    WL5G_B2_PPF[22] = 5;
    WL5G_B2_PPF[23] = 5;
    WL5G_B2_PPF[24] = 5;
    WL5G_B2_PPF[25] = 4;
    WL5G_B2_PPF[26] = 4;
    WL5G_B2_PPF[27] = 3;
    WL5G_B2_PPF[28] = 3;
    WL5G_B2_PPF[29] = 3;
    WL5G_B2_PPF[30] = 2;
    WL5G_B2_PPF[31] = 2;
    WL5G_B2_PPF[32] = 2;
    WL5G_B2_PPF[33] = 1;
    WL5G_B2_PPF[34] = 1;
    WL5G_B2_PPF[35] = 1;
    WL5G_B2_PPF[36] = 1;
    WL5G_B2_PPF[37] = 1;
    WL5G_B2_PPF[38] = 1;
    WL5G_B2_PPF[39] = 1;
    WL5G_B2_PPF[40] = 4;
    WL5G_B2_PPF[41] = 0;
    WL5G_B2_PPF[42] = 0;
    WL5G_B2_PPF[43] = 0;
    WL5G_B2_PPF[44] = 0;
    WL5G_B2_PPF[45] = 0;
    WL5G_B2_PPF[46] = 0;
    WL5G_B2_PPF[47] = 0;
    WL5G_B2_PPF[48] = 0;
    WL5G_B2_PPF[49] = 0;
    WL5G_B2_PPF[50] = 0;
    WL5G_B2_PPF[51] = 0;
    WL5G_B2_PPF[52] = 0;
    WL5G_B2_PPF[53] = 0;
    WL5G_B2_PPF[54] = 0;
    WL5G_B2_PPF[55] = 0;
    WL5G_B2_PPF[56] = 0;
    WL5G_B2_PPF[57] = 0;
    WL5G_B2_PPF[58] = 0;
    WL5G_B2_PPF[59] = 0;
    WL5G_B2_PPF[60] = 0;
    WL5G_B2_PPF[61] = 0;
    WL5G_B2_PPF[62] = 0;
    WL5G_B2_PPF[63] = 0;
    
    WL5G_B4_PPF[0] = 14;
    WL5G_B4_PPF[1] = 14;
    WL5G_B4_PPF[2] = 14;
    WL5G_B4_PPF[3] = 14;
    WL5G_B4_PPF[4] = 14;
    WL5G_B4_PPF[5] = 14;
    WL5G_B4_PPF[6] = 14;
    WL5G_B4_PPF[7] = 14;
    WL5G_B4_PPF[8] = 14;
    WL5G_B4_PPF[9] = 13;
    WL5G_B4_PPF[10] = 13;
    WL5G_B4_PPF[11] = 12;
    WL5G_B4_PPF[12] = 12;
    WL5G_B4_PPF[13] = 11;
    WL5G_B4_PPF[14] = 11;
    WL5G_B4_PPF[15] = 10;
    WL5G_B4_PPF[16] = 9;
    WL5G_B4_PPF[17] = 9;
    WL5G_B4_PPF[18] = 9;
    WL5G_B4_PPF[19] = 9;
    WL5G_B4_PPF[20] = 6;
    WL5G_B4_PPF[21] = 6;
    WL5G_B4_PPF[22] = 6;
    WL5G_B4_PPF[23] = 6;
    WL5G_B4_PPF[24] = 6;
    WL5G_B4_PPF[25] = 5;
    WL5G_B4_PPF[26] = 5;
    WL5G_B4_PPF[27] = 4;
    WL5G_B4_PPF[28] = 4;
    WL5G_B4_PPF[29] = 4;
    WL5G_B4_PPF[30] = 3;
    WL5G_B4_PPF[31] = 3;
    WL5G_B4_PPF[32] = 3;
    WL5G_B4_PPF[33] = 2;
    WL5G_B4_PPF[34] = 2;
    WL5G_B4_PPF[35] = 2;
    WL5G_B4_PPF[36] = 2;
    WL5G_B4_PPF[37] = 1;
    WL5G_B4_PPF[38] = 1;
    WL5G_B4_PPF[39] = 1;
    WL5G_B4_PPF[40] = 1;
    WL5G_B4_PPF[41] = 1;
    WL5G_B4_PPF[42] = 1;
    WL5G_B4_PPF[43] = 1;
    WL5G_B4_PPF[44] = 1;
    WL5G_B4_PPF[45] = 1;
    WL5G_B4_PPF[46] = 0;
    WL5G_B4_PPF[47] = 0;
    WL5G_B4_PPF[48] = 0;
    WL5G_B4_PPF[49] = 0;
    WL5G_B4_PPF[50] = 0;
    WL5G_B4_PPF[51] = 0;
    WL5G_B4_PPF[52] = 0;
    WL5G_B4_PPF[53] = 0;
    WL5G_B4_PPF[54] = 0;
    WL5G_B4_PPF[55] = 0;
    WL5G_B4_PPF[56] = 0;
    WL5G_B4_PPF[57] = 0;
    WL5G_B4_PPF[58] = 0;
    WL5G_B4_PPF[59] = 0;
    WL5G_B4_PPF[60] = 0;
    WL5G_B4_PPF[61] = 0;
    WL5G_B4_PPF[62] = 0;
    WL5G_B4_PPF[63] = 0;
    
    WL5G_B5_PPF[0] = 14;
    WL5G_B5_PPF[1] = 14;
    WL5G_B5_PPF[2] = 14;
    WL5G_B5_PPF[3] = 14;
    WL5G_B5_PPF[4] = 14;
    WL5G_B5_PPF[5] = 14;
    WL5G_B5_PPF[6] = 14;
    WL5G_B5_PPF[7] = 14;
    WL5G_B5_PPF[8] = 14;
    WL5G_B5_PPF[9] = 13;
    WL5G_B5_PPF[10] = 13;
    WL5G_B5_PPF[11] = 13;
    WL5G_B5_PPF[12] = 12;
    WL5G_B5_PPF[13] = 11;
    WL5G_B5_PPF[14] = 11;
    WL5G_B5_PPF[15] = 10;
    WL5G_B5_PPF[16] = 10;
    WL5G_B5_PPF[17] = 10;
    WL5G_B5_PPF[18] = 9;
    WL5G_B5_PPF[19] = 9;
    WL5G_B5_PPF[20] = 7;
    WL5G_B5_PPF[21] = 7;
    WL5G_B5_PPF[22] = 6;
    WL5G_B5_PPF[23] = 6;
    WL5G_B5_PPF[24] = 6;
    WL5G_B5_PPF[25] = 5;
    WL5G_B5_PPF[26] = 5;
    WL5G_B5_PPF[27] = 4;
    WL5G_B5_PPF[28] = 4;
    WL5G_B5_PPF[29] = 4;
    WL5G_B5_PPF[30] = 3;
    WL5G_B5_PPF[31] = 3;
    WL5G_B5_PPF[32] = 3;
    WL5G_B5_PPF[33] = 2;
    WL5G_B5_PPF[34] = 2;
    WL5G_B5_PPF[35] = 2;
    WL5G_B5_PPF[36] = 2;
    WL5G_B5_PPF[37] = 2;
    WL5G_B5_PPF[38] = 2;
    WL5G_B5_PPF[39] = 2;
    WL5G_B5_PPF[40] = 2;
    WL5G_B5_PPF[41] = 1;
    WL5G_B5_PPF[42] = 1;
    WL5G_B5_PPF[43] = 1;
    WL5G_B5_PPF[44] = 1;
    WL5G_B5_PPF[45] = 1;
    WL5G_B5_PPF[46] = 0;
    WL5G_B5_PPF[47] = 0;
    WL5G_B5_PPF[48] = 0;
    WL5G_B5_PPF[49] = 0;
    WL5G_B5_PPF[50] = 0;
    WL5G_B5_PPF[51] = 0;
    WL5G_B5_PPF[52] = 0;
    WL5G_B5_PPF[53] = 0;
    WL5G_B5_PPF[54] = 0;
    WL5G_B5_PPF[55] = 0;
    WL5G_B5_PPF[56] = 0;
    WL5G_B5_PPF[57] = 0;
    WL5G_B5_PPF[58] = 0;
    WL5G_B5_PPF[59] = 0;
    WL5G_B5_PPF[60] = 0;
    WL5G_B5_PPF[61] = 0;
    WL5G_B5_PPF[62] = 0;
    WL5G_B5_PPF[63] = 0;
    
    WL5G_B7_PPF[0] = 15;
    WL5G_B7_PPF[1] = 15;
    WL5G_B7_PPF[2] = 15;
    WL5G_B7_PPF[3] = 15;
    WL5G_B7_PPF[4] = 15;
    WL5G_B7_PPF[5] = 15;
    WL5G_B7_PPF[6] = 15;
    WL5G_B7_PPF[7] = 15;
    WL5G_B7_PPF[8] = 15;
    WL5G_B7_PPF[9] = 14;
    WL5G_B7_PPF[10] = 14;
    WL5G_B7_PPF[11] = 13;
    WL5G_B7_PPF[12] = 13;
    WL5G_B7_PPF[13] = 12;
    WL5G_B7_PPF[14] = 12;
    WL5G_B7_PPF[15] = 11;
    WL5G_B7_PPF[16] = 10;
    WL5G_B7_PPF[17] = 10;
    WL5G_B7_PPF[18] = 10;
    WL5G_B7_PPF[19] = 10;
    WL5G_B7_PPF[20] = 7;
    WL5G_B7_PPF[21] = 7;
    WL5G_B7_PPF[22] = 8;
    WL5G_B7_PPF[23] = 8;
    WL5G_B7_PPF[24] = 8;
    WL5G_B7_PPF[25] = 6;
    WL5G_B7_PPF[26] = 6;
    WL5G_B7_PPF[27] = 5;
    WL5G_B7_PPF[28] = 5;
    WL5G_B7_PPF[29] = 5;
    WL5G_B7_PPF[30] = 4;
    WL5G_B7_PPF[31] = 4;
    WL5G_B7_PPF[32] = 4;
    WL5G_B7_PPF[33] = 3;
    WL5G_B7_PPF[34] = 3;
    WL5G_B7_PPF[35] = 3;
    WL5G_B7_PPF[36] = 3;
    WL5G_B7_PPF[37] = 2;
    WL5G_B7_PPF[38] = 2;
    WL5G_B7_PPF[39] = 2;
    WL5G_B7_PPF[40] = 2;
    WL5G_B7_PPF[41] = 1;
    WL5G_B7_PPF[42] = 1;
    WL5G_B7_PPF[43] = 1;
    WL5G_B7_PPF[44] = 1;
    WL5G_B7_PPF[45] = 1;
    WL5G_B7_PPF[46] = 0;
    WL5G_B7_PPF[47] = 0;
    WL5G_B7_PPF[48] = 0;
    WL5G_B7_PPF[49] = 0;
    WL5G_B7_PPF[50] = 0;
    WL5G_B7_PPF[51] = 0;
    WL5G_B7_PPF[52] = 0;
    WL5G_B7_PPF[53] = 0;
    WL5G_B7_PPF[54] = 0;
    WL5G_B7_PPF[55] = 0;
    WL5G_B7_PPF[56] = 0;
    WL5G_B7_PPF[57] = 0;
    WL5G_B7_PPF[58] = 0;
    WL5G_B7_PPF[59] = 0;
    WL5G_B7_PPF[60] = 0;
    WL5G_B7_PPF[61] = 0;
    WL5G_B7_PPF[62] = 0;
    WL5G_B7_PPF[63] = 0;

}


void CosSin_Value()
{
    CosLut_5M[0] = 512;
    CosLut_5M[1] = 502;
    CosLut_5M[2] = 473;
    CosLut_5M[3] = 426;
    CosLut_5M[4] = 362;
    CosLut_5M[5] = 284;
    CosLut_5M[6] = 196;
    CosLut_5M[7] = 100;
    CosLut_5M[8] = 0;
    CosLut_5M[9] = -100;
    CosLut_5M[10] = -196;
    CosLut_5M[11] = -284;
    CosLut_5M[12] = -362;
    CosLut_5M[13] = -426;
    CosLut_5M[14] = -473;
    CosLut_5M[15] = -502;
    CosLut_5M[16] = -512;
    CosLut_5M[17] = -502;
    CosLut_5M[18] = -473;
    CosLut_5M[19] = -426;
    CosLut_5M[20] = -362;
    CosLut_5M[21] = -284;
    CosLut_5M[22] = -196;
    CosLut_5M[23] = -100;
    CosLut_5M[24] = 0;
    CosLut_5M[25] = 100;
    CosLut_5M[26] = 196;
    CosLut_5M[27] = 284;
    CosLut_5M[28] = 362;
    CosLut_5M[29] = 426;
    CosLut_5M[30] = 473;
    CosLut_5M[31] = 502;
    
    SinLut_5M[0] = 0;
    SinLut_5M[1] = 100;
    SinLut_5M[2] = 196;
    SinLut_5M[3] = 284;
    SinLut_5M[4] = 362;
    SinLut_5M[5] = 426;
    SinLut_5M[6] = 473;
    SinLut_5M[7] = 502;
    SinLut_5M[8] = 512;
    SinLut_5M[9] = 502;
    SinLut_5M[10] = 473;
    SinLut_5M[11] = 426;
    SinLut_5M[12] = 362;
    SinLut_5M[13] = 284;
    SinLut_5M[14] = 196;
    SinLut_5M[15] = 100;
    SinLut_5M[16] = 0;
    SinLut_5M[17] = -100;
    SinLut_5M[18] = -196;
    SinLut_5M[19] = -284;
    SinLut_5M[20] = -362;
    SinLut_5M[21] = -426;
    SinLut_5M[22] = -473;
    SinLut_5M[23] = -502;
    SinLut_5M[24] = -512;
    SinLut_5M[25] = -502;
    SinLut_5M[26] = -473;
    SinLut_5M[27] = -426;
    SinLut_5M[28] = -362;
    SinLut_5M[29] = -284;
    SinLut_5M[30] = -196;
    SinLut_5M[31] = -100;
    
    CosLut_25M[0] = 512;
    CosLut_25M[1] = 284;
    CosLut_25M[2] = -196;
    CosLut_25M[3] = -502;
    CosLut_25M[4] = -362;
    CosLut_25M[5] = 100;
    CosLut_25M[6] = 473;
    CosLut_25M[7] = 426;
    CosLut_25M[8] = 0;
    CosLut_25M[9] = -426;
    CosLut_25M[10] = -473;
    CosLut_25M[11] = -100;
    CosLut_25M[12] = 362;
    CosLut_25M[13] = 502;
    CosLut_25M[14] = 196;
    CosLut_25M[15] = -284;
    CosLut_25M[16] = -512;
    CosLut_25M[17] = -284;
    CosLut_25M[18] = 196;
    CosLut_25M[19] = 502;
    CosLut_25M[20] = 362;
    CosLut_25M[21] = -100;
    CosLut_25M[22] = -473;
    CosLut_25M[23] = -426;
    CosLut_25M[24] = 0;
    CosLut_25M[25] = 426;
    CosLut_25M[26] = 473;
    CosLut_25M[27] = 100;
    CosLut_25M[28] = -362;
    CosLut_25M[29] = -502;
    CosLut_25M[30] = -196;
    CosLut_25M[31] = 284;
    
    SinLut_25M[0] = 0;
    SinLut_25M[1] = 426;
    SinLut_25M[2] = 473;
    SinLut_25M[3] = 100;
    SinLut_25M[4] = -362;
    SinLut_25M[5] = -502;
    SinLut_25M[6] = -196;
    SinLut_25M[7] = 284;
    SinLut_25M[8] = 512;
    SinLut_25M[9] = 284;
    SinLut_25M[10] = -196;
    SinLut_25M[11] = -502;
    SinLut_25M[12] = -362;
    SinLut_25M[13] = 100;
    SinLut_25M[14] = 473;
    SinLut_25M[15] = 426;
    SinLut_25M[16] = 0;
    SinLut_25M[17] = -426;
    SinLut_25M[18] = -473;
    SinLut_25M[19] = -100;
    SinLut_25M[20] = 362;
    SinLut_25M[21] = 502;
    SinLut_25M[22] = 196;
    SinLut_25M[23] = -284;
    SinLut_25M[24] = -512;
    SinLut_25M[25] = -284;
    SinLut_25M[26] = 196;
    SinLut_25M[27] = 502;
    SinLut_25M[28] = 362;
    SinLut_25M[29] = -100;
    SinLut_25M[30] = -473;
    SinLut_25M[31] = -426;

    CosLut_35M[0] = 512;
    CosLut_35M[1] = 100;
    CosLut_35M[2] = -473;
    CosLut_35M[3] = -284;
    CosLut_35M[4] = 362;
    CosLut_35M[5] = 426;
    CosLut_35M[6] = -196;
    CosLut_35M[7] = -502;
    CosLut_35M[8] = 0;
    CosLut_35M[9] = 502;
    CosLut_35M[10] = 196;
    CosLut_35M[11] = -426;
    CosLut_35M[12] = -362;
    CosLut_35M[13] = 284;
    CosLut_35M[14] = 473;
    CosLut_35M[15] = -100;
    CosLut_35M[16] = -512;
    CosLut_35M[17] = -100;
    CosLut_35M[18] = 473;
    CosLut_35M[19] = 284;
    CosLut_35M[20] = -362;
    CosLut_35M[21] = -426;
    CosLut_35M[22] = 196;
    CosLut_35M[23] = 502;
    CosLut_35M[24] = 0;
    CosLut_35M[25] = -502;
    CosLut_35M[26] = -196;
    CosLut_35M[27] = 426;
    CosLut_35M[28] = 362;
    CosLut_35M[29] = -284;
    CosLut_35M[30] = -473;
    CosLut_35M[31] = 100;
    
    SinLut_35M[0] = 0;
    SinLut_35M[1] = 502;
    SinLut_35M[2] = 196;
    SinLut_35M[3] = -426;
    SinLut_35M[4] = -362;
    SinLut_35M[5] = 284;
    SinLut_35M[6] = 473;
    SinLut_35M[7] = -100;
    SinLut_35M[8] = -512;
    SinLut_35M[9] = -100;
    SinLut_35M[10] = 473;
    SinLut_35M[11] = 284;
    SinLut_35M[12] = -362;
    SinLut_35M[13] = -426;
    SinLut_35M[14] = 196;
    SinLut_35M[15] = 502;
    SinLut_35M[16] = 0;
    SinLut_35M[17] = -502;
    SinLut_35M[18] = -196;
    SinLut_35M[19] = 426;
    SinLut_35M[20] = 362;
    SinLut_35M[21] = -284;
    SinLut_35M[22] = -473;
    SinLut_35M[23] = 100;
    SinLut_35M[24] = 512;
    SinLut_35M[25] = 100;
    SinLut_35M[26] = -473;
    SinLut_35M[27] = -284;
    SinLut_35M[28] = 362;
    SinLut_35M[29] = 426;
    SinLut_35M[30] = -196;
    SinLut_35M[31] = -502;
}



