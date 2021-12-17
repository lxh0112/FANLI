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

#include "Test_TX_cpp.h"
//using namespace MuTest;

#include <fstream>

//using namespace PhxAPI;

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

int TX_Power_Trim_Function(emMode Mode_Select,emTX_Band Band_Select,char *Channel, double *Pre_Output_Power,int *TrimData)
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
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_read(retAddr, "retdata", 9);
    d2s::d2s_LABEL_END();
    
    map<int, long long> Basic_Upc;
    FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
        long long read_data = d2s_test.getReadValue("retdata").at(index);
        int site_id = index;
        Basic_Upc[site_id] = read_data & 0x3F;
        TrimData[site_id] = int(Basic_Upc[site_id] * pow(10,((Exp_Power - *(Pre_Output_Power+site_id)) / 20)) + 1);//+ 0.5);
        if(TrimData[site_id]>63){
            TrimData[site_id]=63;
        }
        if(TrimData[site_id]<1){
            TrimData[site_id]=1;
        }
    FOREACH_ACTIVESITE_END
    //to be add
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2s_test.SSI_read(retAddr,"modify_data",9);    
    d2s::d2s_LABEL_END();   
    map<int, long long> Modify_TrimData;
    FOREACH_ACTIVESITE_BEGIN(index, bInterrupt)
        long long modify_value = d2s_test.getReadValue("modify_data").at(index);
        int site_id = index;
        Modify_TrimData[site_id] = modify_value ;
        Modify_TrimData[site_id]=Modify_TrimData[site_id]&(0xFFC0);
        Modify_TrimData[site_id]=Modify_TrimData[site_id]|TrimData[site_id];
    FOREACH_ACTIVESITE_END
    d2s::d2s_LABEL_BEGIN("dynamic", d2s_WorkMode);
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
        
//        if((Power_Max>=Power_Buf[i])||(i == 0))
//        {
//            Power_Max = Power_Max;
//        }
//        else
//        {
//            Power_Max = Power_Buf[i];
//        }

        if((Power_Max < Power_Buf[i])&&(i != 0))
        {
            Power_Max = Power_Buf[i];
        }
    }    
    
    *Pre_Output_Power = Power_Max + pathloss;//debug
    delete[] Power_Buf;
    return EXIT_SUCCESS; 
}

int Calc_TX_Power_CR_SR(tyTestData *pRF_Test_Data,SpecAnResultAttribute *ResultAttribute,double pathloss,double *Post_Power,double *CR,double *SR)
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
    return EXIT_SUCCESS;
}


int calc_WL_TX_OIP3(tyTestData *pRF_Test_Data,SpecAnResultAttribute *ResultAttribute,double pathloss,double *Output_Power,double *Result_oip3)
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


int calc_WL_TX_OIP3_Dri_Mode(tyTestData *pRF_Test_Data,SpecAnResultAttribute *ResultAttribute,double pathloss, double *Output_Power,double *Result_im3,double *Result_oip3)
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

void Calc_TX_Power_2_Spur(tyTestData *pRF_Test_Data,SpecAnResultAttribute *ResultAttribute,double pathloss,double Space1,double Space2,double *outPower,double *SPUR1_dbm,double *SPUR2_dbm)
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

void Calc_TX_Power_3_Spur(tyTestData *pRF_Test_Data,SpecAnResultAttribute *ResultAttribute,double pathloss,double Space1,double Space2,double Space3,double *outPower,double *SPUR1_dbm,double *SPUR2_dbm,double *SPUR3_dbm)
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


int calc_PLL_Sweep(int site_id,long long *Dataarray,long sweep_step,double *bandError,long *first_band_value,long *last_band_value,long *max_pll_State,long *min_pll_State)
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
    
//    WriteData("band_wave",band_wave,sweep_step);


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
