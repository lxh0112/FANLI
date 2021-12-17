/*
 * CAL_RX_Phase.cpp
 *
 *  Created on: 2021年10月31日
 *      Author: huawei
 */



#include "TestClass.h"
#include "GetLog.h"
#include "UserAPI.h"
#include "UserDef.h"
//#include "MT_DSP_Lib.h"
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
#include "Test_CAL.h"
#include "Globle_Var.h"

#include <synchapi.h>

class CAL_RX_Phase: public TestClass{
public:


	void init(){

	    }

    void execute(){



			TheInst.DCVS().Power().Apply(); //下发执行  DCVS  power pin上电
			TheInst.Digital().Level().Apply();//下发执行 DIO  pattern pin  level
			TheInst.Digital().Timing().Apply();//下发执行 DIO  pattern pin  timing


    	    string testname = TheSoft.Flow().Test().GetCurrentTestName();
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

    }

    void RXIQ_5G_C1_Restore_Module() {

    	//File:  Hi1151_V200_Calibration_Config_for_ATE_20170619.xlsx
    	//Sheet: RXIQ_5G_C1_Module
    	//File time: 2017/6/20 19:11:50
    	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
    	d2sProtocolSSI d2s_test;
    	d2s_test.SSI_write(0x200, 0x2003, false);
    	d2s_test.SSI_write(0x202, 0x90, false);
    	d2s_test.SSI_write(0x1D0, 0x0);    //phy

    	d2s_test.SSI_write(0x200, 0x2000, false);
    	d2s_test.SSI_write(0x202, 0x90, false);
    	d2s_test.SSI_write(0x28, 0x80);        //rf
    	d2s_test.SSI_write(0x20, 0x37);        //rf
    	d2s_test.SSI_write(0x0, 0x0);      //rf
    	d2s_test.SSI_write(0x4, 0x0);      //rf
    	d2s_test.SSI_write(0x8, 0x0);      //rf
    	d2s_test.SSI_write(0xC, 0x2);      //rf
    	d2s_test.SSI_write(0x10, 0x2);         //rf

    	d2s_test.SSI_write(0x200, 0x2001, false);
    	d2s_test.SSI_write(0x202, 0x80, false);
    	d2s_test.SSI_write(0x0, 0x0);      //mac
    	d2s::d2s_LABEL_END();
    }

    void RXIQ_5G_C0_Restore_Module() {

    	//File:  Hi1151_V200_Calibration_Config_for_ATE_20170619.xlsx
    	//Sheet: RXIQ_5G_C0_Module
    	//File time: 2017/6/20 19:11:50
    	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
    	d2sProtocolSSI d2s_test;
    	d2s_test.SSI_write(0x200, 0x2003, false);
    	d2s_test.SSI_write(0x202, 0x90, false);
    	d2s_test.SSI_write(0x1D0, 0x0);    //phy

    	d2s_test.SSI_write(0x200, 0x2000, false);
    	d2s_test.SSI_write(0x202, 0x90, false);
    	d2s_test.SSI_write(0x24, 0x80);        //rf
    	d2s_test.SSI_write(0x20, 0x37);        //rf
    	d2s_test.SSI_write(0x0, 0x0);      //rf
    	d2s_test.SSI_write(0x4, 0x0);      //rf
    	d2s_test.SSI_write(0x8, 0x0);      //rf
    	d2s_test.SSI_write(0xC, 0x2);      //rf
    	d2s_test.SSI_write(0x10, 0x2);            //rf

    	d2s_test.SSI_write(0x200, 0x2001, false);
    	d2s_test.SSI_write(0x202, 0x80, false);
    	d2s_test.SSI_write(0x0, 0x0);      //mac
    	d2s::d2s_LABEL_END();
    }

    void RXIQ_5G_C0_Set_Module() {

    	//File:  Hi1151_V200_Calibration_Config_for_ATE_20170619.xlsx
    	//Sheet: RXIQ_5G_C0_Module
    	//File time: 2017/6/20 19:11:50
    	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
    	d2sProtocolSSI d2s_test;
    	d2s_test.SSI_write(0x204, 0x0, false);     //mac

    	d2s_test.SSI_write(0x200, 0x2001, false);
    	d2s_test.SSI_write(0x202, 0x80, false);
    	d2s_test.SSI_write(0x0, 0x0);      //mac

    	d2s_test.SSI_write(0x200, 0x2000, false);
    	d2s_test.SSI_write(0x202, 0x90, false);
    	d2s_test.SSI_write(0x0, 0x1);      //rf
    	d2s_test.SSI_write(0x4, 0x0);      //rf
    	d2s_test.SSI_write(0x8, 0x3);      //rf
    	d2s_test.SSI_write(0xC, 0x2F);     //rf
    	d2s_test.SSI_write(0x10, 0x2F);        //rf

    	d2s_test.SSI_write(0x200, 0x2000, false);
    	d2s_test.SSI_write(0x202, 0x80, false);
    	d2s_test.SSI_write(0x240, 0x111);      //soc
    	d2s_test.SSI_write(0x244, 0x1);    //soc
    	d2s_test.SSI_write(0x244, 0x101);      //soc

    	d2s_test.SSI_write(0x200, 0x2000, false);
    	d2s_test.SSI_write(0x202, 0x90, false);
    	d2s_test.SSI_write(0x20, 0x37);        //rf

    	d2s_test.SSI_write(0x200, 0x2001, false);
    	d2s_test.SSI_write(0x202, 0x4, false);
    	d2s_test.SSI_write(0x94, 0x0);     //soc

    	d2s_test.SSI_write(0x200, 0x2003, false);
    	d2s_test.SSI_write(0x202, 0x88, false);
    	d2s_test.SSI_write(0x20, 0x1);     //phy
    	d2s_test.SSI_write(0x24, 0x1);     //phy

    	d2s_test.SSI_write(0x200, 0x2003, false);
    	d2s_test.SSI_write(0x202, 0x90, false);
    	d2s_test.SSI_write(0x1D0, 0x5);        //phy

    	d2s_test.SSI_write(0x200, 0x2000, false);
    	d2s_test.SSI_write(0x202, 0x90, false);
    	d2s_test.SSI_write(0x24, 0x1E0);       //rf
    	d2s::d2s_LABEL_END();
    }


};
REGISTER_TESTCLASS("CAL_RX_Phase",CAL_RX_Phase)




