#include "Systick.h"
#include "GetLog.h" 
#include "UserAPI.h"
#include "d2sProtocolSSI.h"
#include "D2S_PMU_Module.h"
#include "D2S_ABB_Module.h"
#include "Globle_Var.h"
#include "CCWaveformsData.h"
#include "string.h"
#include "Globle_Var.h"
#include "UserDef.h"
#include <cmath>

////using namespace MuTest;

int bootUp() {//
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
//    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);

    d2s::d2s_LABEL_BEGIN( "ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200,0x2000,false);
    
    d2s_test.SSI_write(0x236,0x1,false);
    d2s_test.SSI_write(0x232,0x3,false);
    d2s_test.SSI_write(0x234,0x0,false);
    d2s_test.wait(0.003);
    d2s_test.SSI_write(0x234,0xb,false);
    d2s_test.wait(0.003);
    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x0,false);
    d2s_test.SSI_write(0x4,0x1151);
    d2s_test.SSI_write(0x8,0x1151);
    
    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x40,false);
    d2s_test.SSI_write(0x4,0x1151);
    d2s_test.SSI_write(0x8,0x1151);
    
    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x80,false);
    d2s_test.SSI_write(0x4,0x1151);
    d2s_test.SSI_write(0x8,0x1151);
    
    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x40,false);
    d2s_test.SSI_write(0x204,0x9);
    d2s_test.SSI_write(0x208,0x6);
    
    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x80,false);
    d2s_test.SSI_write(0x270,0x1);
    d2s_test.SSI_write(0x278,0x3);
    
    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x40,false);
    d2s_test.SSI_write(0x124,0x20);
    d2s_test.SSI_write(0x16c,0x40);
    d2s_test.SSI_write(0x154,0x1A0);  //1a0
    d2s_test.SSI_write(0x14c,0xffff);
    
    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x90,false);
    d2s_test.SSI_write(0x84,0x0);
    
    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x40,false);
    d2s_test.SSI_write(0x32c,0x1a);
    d2s_test.SSI_write(0x32c,0x1b);
    
    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x40,false); 
    
    d2s_test.SSI_read(0x154,"readdata");

    d2s::d2s_LABEL_END();
    
    map<int, long long> capture_data;
    FOREACH_ACTIVE_SITE(api){
        long long readvalue = d2s_test.getReadValue("readdata");
        int site_id = api->Get_active_site();
        capture_data[site_id] = readvalue ;
        ValueTest (api, "SSI_DATA", capture_data[site_id], lowl[0], hil[0], Units[0], Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
    }
    return EXIT_SUCCESS;
}

int Tsensor() {
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    d2s::d2s_LABEL_BEGIN( "ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x80,false);
    d2s_test.SSI_write(0x304,0x0);    //TSENSOR_CTRL1  1->0
    d2s_test.SSI_write(0x2EC,0x32);   //TSENSOR_CLK_DIV  0x28->0x32 20170428 for moving Tsensor after bootup , divide by 50 from SSI clock 50MHz
    d2s_test.SSI_write(0x2EC,0x128);   //TSENSOR_CLK_DIV

    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x0,false);
    d2s_test.SSI_write(0x124,0xF);    //RF_PLL_CLK_EN

    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x80,false);
    d2s_test.SSI_write(0x2F8,0x0);    //TSENSOR_CTRL
    d2s_test.SSI_write(0x2F8,0x1);    //TSENSOR_CTRL
    d2s_test.SSI_write(0x2F4,0x1);    //TSENSOR_START
      
    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x80,false);
    for(int i=0;i<100;i++)
    	d2s_test.wait(0.0004);
    
    d2s_test.SSI_read(0x300,"readdata");
    d2s_test.SSI_write(0x300,0x1);    
    d2s::d2s_LABEL_END();
    
    map<int, double> tempVal; 
    FOREACH_ACTIVE_SITE(api){
        long long temp_data = d2s_test.getReadValue("readdata");
        int site_id = api->Get_active_site();
        tempVal[site_id] = ((temp_data &(0xFFC))/4.0);
        tempVal[site_id]=(((tempVal[site_id]-118)/(933-118))*165)-40;
        TSENSOR_TG[site_id] = (tempVal[site_id] - 15)/5 + 0.5;
        
        ValueTest (api, "SSI_DATA", (temp_data & 0x2) >>1, lowl[0], hil[0], Units[0], Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
        ValueTest (api, "SSI_DATA", tempVal[site_id], lowl[1], hil[1], Units[1], Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
    }
    
    return EXIT_SUCCESS;
}

int PMU_VrefTrim() {
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);    
    
    d2s::d2s_LABEL_BEGIN( "ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x40,false);
    d2s_test.SSI_write(0x124,0xb0);    
    d2s::d2s_LABEL_END();
    
    double *GetValue;
    map<int, double> preTrimMeas;
    map<int, long long> TrimData;
    map<int, double> postTrimMeas;
    double Voffset = 0.002;
    
    /***********Execute pre DC test,Get preTrim value,cal Trim code****************/
    api->Execute_test("PMU_VREF_TEST");
  
    FOREACH_ACTIVE_SITE(api){
        api->Get_dctest_values("PMU_VREF_TEST","PMU_REFBP",0,THE_MEASURE,&GetValue,THE_END);
        int site_id = api->Get_active_site();
        Testsoftbin[site_id] = 1;//softbin flag
        preTrimMeas[site_id] = GetValue[0] + Voffset;
        
        if(FT_PASSFLAG[site_id]==0){  
            pmu_v_trimData[site_id] = floor((1-(1.2/preTrimMeas[site_id]))*219.2+0.5);
            if(pmu_v_trimData[site_id]>15){
                pmu_v_trimData[site_id]=0;
            }
            else if(pmu_v_trimData[site_id]>=0){
                pmu_v_trimData[site_id]=pmu_v_trimData[site_id];
            }
            else if(pmu_v_trimData[site_id]>=-16){
                pmu_v_trimData[site_id]=abs(pmu_v_trimData[site_id])-1+16;
            }
            else{
                pmu_v_trimData[site_id]=0;
            }
        }else{
            pmu_v_trimData[site_id] = pmu_v_pretrimData[site_id];
        }
        TrimData[site_id]=pmu_v_trimData[site_id]<<10;
        ValueTest (api, "PMU_REFBP", preTrimMeas[site_id], lowl[0], hil[0], "V", Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
        ValueTest (api, "PMU_REFBP", pmu_v_trimData[site_id], lowl[1], hil[1],"" , Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable); 
    }
    
    /*************************Dynamic write Trim code***********************************************/
    d2s::d2s_LABEL_BEGIN( "ssi", d2s_WorkMode);
    d2s_test.SSI_read(0x154,"readdata");    
    d2s::d2s_LABEL_END();   
    map<int, long long> capture_data;
    FOREACH_ACTIVE_SITE(api){
        long long readvalue = d2s_test.getReadValue("readdata");
        int site_id = api->Get_active_site();
        capture_data[site_id] = readvalue ;
        capture_data[site_id]=capture_data[site_id]&(0x83FF);
        capture_data[site_id]=capture_data[site_id]|TrimData[site_id];
    }  
    d2s::d2s_LABEL_BEGIN( "dynamic", d2s_WorkMode);
    d2s_test.SSI_writeDynamic(0x154,capture_data,"write");
    d2s::d2s_LABEL_END(); 
    api->sleep(0.01); 
    /**************************Execute post DC test,Get postTrim value*******************************/
    api->Execute_test("PMU_VREF_TEST");
     
    FOREACH_ACTIVE_SITE(api){
        api->Get_dctest_values("PMU_VREF_TEST","PMU_REFBP",0,THE_MEASURE,&GetValue,THE_END);
        int site_id = api->Get_active_site();
        postTrimMeas[site_id] = GetValue[0] + Voffset;
        ValueTest (api, "PMU_REFBP", postTrimMeas[site_id], lowl[2], hil[2], "V", Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);
        if(Testsoftbin[site_id]!=1){
         api->Set_result_bin(Testsoftbin[site_id]);
        } 
        
        PRE_VREF_TRIM[site_id] = preTrimMeas[site_id];
     }
    return EXIT_SUCCESS;
}

int BUCK_VrefTrim() {
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);      
    
    double *GetValue;
    map<int, double> preTrimMeas;
    map<int, long long> TrimData;

    /***********Execute pre DC test,Get preTrim value,cal Trim code****************/
    api->Execute_test("PMU_BUCK_TEST");
    
    FOREACH_ACTIVE_SITE(api){
        api->Get_dctest_values("PMU_BUCK_TEST","VDD_BUCK_1V5_IN",0,THE_MEASURE,&GetValue,THE_END);
        int site_id = api->Get_active_site();
        Testsoftbin[site_id] = 1;//softbin flag
        preTrimMeas[site_id] = GetValue[0];
        if(FT_PASSFLAG[site_id]==0){
            buck_v_trimData[site_id] = floor((1.4/preTrimMeas[site_id]-1)*267+0.5);
            if(buck_v_trimData[site_id]>15){
                buck_v_trimData[site_id]=0;
            }
            else if(buck_v_trimData[site_id]>=0){
                buck_v_trimData[site_id]=buck_v_trimData[site_id];
            }
            else if(buck_v_trimData[site_id]>=-15){
                buck_v_trimData[site_id]=abs(buck_v_trimData[site_id])+16;
            }
            else{
                buck_v_trimData[site_id]=0;
            }
        }else{
            buck_v_trimData[site_id] = buck_v_pretrimData[site_id];
        }
        
        ValueTest (api, "VDD_BUCK_1V5_IN", preTrimMeas[site_id], lowl[0], hil[0], "V", Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
        ValueTest (api, "VDD_BUCK_1V5_IN", buck_v_trimData[site_id], lowl[1], hil[1], "", Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);   
    }
    
    /*************************Dynamic write Trim code***********************************************/
    d2s::d2s_LABEL_BEGIN( "ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x40,false);
    d2s_test.SSI_read(0x154,"readdata1");    
    d2s::d2s_LABEL_END();
    
    map<int, long long> capture_data;
    FOREACH_ACTIVE_SITE(api){
        long long readvalue = d2s_test.getReadValue("readdata1");
        int site_id = api->Get_active_site();
        capture_data[site_id] = readvalue ;
        capture_data[site_id]=capture_data[site_id]&(0xFFE0);
        capture_data[site_id]=capture_data[site_id]|buck_v_trimData[site_id];
    }
    d2s::d2s_LABEL_BEGIN( "dynamic", d2s_WorkMode);
    d2s_test.SSI_writeDynamic(0x154,capture_data,"write");
    d2s::d2s_LABEL_END();
    
    api->sleep(0.05);  //delay time  0.01->0.05
    
    /**************************Execute post DC test,Get postTrim value*******************************/
    api->Execute_test("PMU_BUCK_TEST");
    
    FOREACH_ACTIVE_SITE(api){
        api->Get_dctest_values("PMU_BUCK_TEST","VDD_BUCK_1V5_IN",0,THE_MEASURE,&GetValue,THE_END);
        int site_id = api->Get_active_site();
        preTrimMeas[site_id] = GetValue[0];
       
        ValueTest (api, "VDD_BUCK_1V5_IN", preTrimMeas[site_id], lowl[2], hil[2], "V", Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable); 
        //////////////soft bin //////////////
        if(Testsoftbin[site_id]!=1){
         api->Set_result_bin(Testsoftbin[site_id]);
        }
        
        PRE_BUCK_TRIM[site_id] = preTrimMeas[site_id];
     }
    
    return EXIT_SUCCESS;
}

int PMU_IrefTrim() {
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);   
    
    double *GetValue;      
    map<int, double> preTrimMeas;
    map<int, long long> TrimData;
    map<int, double> postTrimMeas;
    double Voffset[4] = {0.009, 0.009, 0.009, 0.009};

    /***********Execute pre DC test,Get preTrim value,cal Trim code****************/
    api->Execute_test("PMU_IREF_TEST");   
    
    FOREACH_ACTIVE_SITE(api){
        api->Get_dctest_values("PMU_IREF_TEST","PMU_RBIAS",0,THE_MEASURE,&GetValue,THE_END);
        int site_id = api->Get_active_site();
        Testsoftbin[site_id] = 1;//softbin flag
        preTrimMeas[site_id] = GetValue[0];
        preTrimMeas[site_id] = preTrimMeas[site_id]*(-120000) + Voffset[site_id];
       if(FT_PASSFLAG[site_id]==0){    
            TrimData[site_id] = floor((((99*preTrimMeas[site_id])/1.2)-99)+13+0.5);
            if(TrimData[site_id] > 31){
                TrimData[site_id] = 0;
            }
            else if(TrimData[site_id] >=0 ){
                TrimData[site_id] = TrimData[site_id];
            }
            else {
                TrimData[site_id] = 0;
            }
       }else{
           TrimData[site_id] = pb_i_pretrimData[site_id];
       }

        ValueTest (api, "PMU_RBIAS", preTrimMeas[site_id], lowl[0], hil[0], "V", Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);   
        ValueTest (api, "PMU_RBIAS", TrimData[site_id], lowl[1], hil[1], "", Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);   
        
        pb_i_TrimData[site_id] = TrimData[site_id];        
        TrimData[site_id] = TrimData[site_id]<<5;
      
    }
    
    /*************************Dynamic write Trim code***********************************************/
    d2s::d2s_LABEL_BEGIN( "ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x40,false);
    d2s_test.SSI_read(0x154,"readdata");    
    d2s::d2s_LABEL_END();
    
    map<int, long long> capture_data;
    FOREACH_ACTIVE_SITE(api){
        long long readvalue = d2s_test.getReadValue("readdata");
        int site_id = api->Get_active_site();
        capture_data[site_id] = readvalue ;
        capture_data[site_id] = capture_data[site_id]&(0xFC1F);
        capture_data[site_id] = capture_data[site_id]|TrimData[site_id];
    }
    d2s::d2s_LABEL_BEGIN( "dynamic", d2s_WorkMode);
    d2s_test.SSI_writeDynamic(0x154,capture_data,"write");
    d2s::d2s_LABEL_END();
    api->sleep(0.03);
    
    /**************************Execute post DC test,Get postTrim value*******************************/
    api->Execute_test("PMU_IREF_TEST");  
    
    FOREACH_ACTIVE_SITE(api){
        api->Get_dctest_values("PMU_IREF_TEST","PMU_RBIAS",0,THE_MEASURE,&GetValue,THE_END);
        int site_id = api->Get_active_site();
        postTrimMeas[site_id] = GetValue[0];
        postTrimMeas[site_id] = postTrimMeas[site_id]*(-120000) + Voffset[site_id];
        ValueTest (api, "PMU_RBIAS", postTrimMeas[site_id], lowl[2], hil[2], "V", Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);
        
        //////////////soft bin //////////////
        if(Testsoftbin[site_id]!=1){
         api->Set_result_bin(Testsoftbin[site_id]);
        } 
        
        PRE_IREF_TRIM[site_id] = preTrimMeas[site_id];
    }
    
    return EXIT_SUCCESS;
}

int BUCKLoading() {
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);   
    
    d2s::d2s_LABEL_BEGIN( "ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x0,false);   
    d2s_test.SSI_read(0x4,"readdata");  
    d2s::d2s_LABEL_END();
    
    map<int, long long> capture_data;
    FOREACH_ACTIVE_SITE(api){
        long long readvalue = d2s_test.getReadValue("readdata");
        int site_id = api->Get_active_site();
        capture_data[site_id] = readvalue;

        ValueTest (api, "SSI_DATA", capture_data[site_id], lowl[0], hil[0], "", Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);  
    }
    
    return EXIT_SUCCESS;
}

int LDO_test() {
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api); 
    
    api->Set_loadboard_x_ubits(X_UBIT_000+X_UBIT_015+X_UBIT_038+X_UBIT_074, X_UBIT_NONE);  //K5 on    
    api->Set_loadboard_x_ubits(X_UBIT_042+X_UBIT_003+X_UBIT_029+X_UBIT_083, X_UBIT_NONE);  //K4 on
  
    LDO_Module(api);
    api->sleep(0.01);
    
    return EXIT_SUCCESS;
}

int CaplessLDOx_voltMux() {
    
    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site();
        Testsoftbin[site_id] = 1;//softbin flag
    }
    
    d2s::d2s_LABEL_BEGIN( "ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x40,false);
    d2s_test.SSI_write(0x124,0x10);    //PMU_CFG        
    d2s::d2s_LABEL_END();

    double *GetValue;
    map<int, double> vMeas;
    char *muxMeasPins[3]={"INTLDO","BBLDO0","BBLDO1"};
    double muxLowLimit[3]={1.4,1.14,1.14};
    double muxHighLimit[3]={1.54,1.26,1.26};
    int muxTest_Number[3]={60050008,60050009,60050010};
    long muxRegs[9]={0x0,0x0,0x40,0x800,0x0,0x80,0x0,0x800,0x80};
    
    for(int i=0;i<3;i++){
        d2s::d2s_LABEL_BEGIN( "ssi", d2s_WorkMode);
        d2sProtocolSSI d2s_test;
        d2s_test.SSI_write(0x202,0x94,false);
        d2s_test.SSI_write(0x37C,muxRegs[i*3]); 
        d2s_test.SSI_write(0x384,muxRegs[i*3+1]); 
        d2s_test.SSI_write(0x202,0x40,false);
        d2s_test.SSI_write(0x148,muxRegs[i*3+2]); 
        d2s::d2s_LABEL_END();
        
        api->Execute_test("CAPLESS_LDO_TEST");
    
        FOREACH_ACTIVE_SITE(api){
            api->Get_dctest_values("CAPLESS_LDO_TEST","PMU_RBIAS",0,THE_MEASURE,&GetValue,THE_END);
            int site_id = api->Get_active_site();
            vMeas[site_id] = GetValue[0];
   
            ValueTest (api, "PMU_RBIAS", vMeas[site_id], muxLowLimit[i], muxHighLimit[i], "V", muxMeasPins[i], "FAIL_BIN", muxTest_Number[i], Clogenable);

         } 
    }
    
    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site();
        if(Testsoftbin[site_id]!=1){
         api->Set_result_bin(Testsoftbin[site_id]);
        }
    }
    return EXIT_SUCCESS;
}

int CMU_SSI() {
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);    
    
    CMU_Module(api);

    double *GetValue1;
    double *GetValue2;
    map<int, double> vMeas1;
    map<int, double> vMeas2;
    
    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site();
        Testsoftbin[site_id] = 1;//softbin flag
    }
    long muxRegs[4]={0xA91,0xCB1,0x631,0x871};

    for(int i=0;i<2;i++){
        d2s::d2s_LABEL_BEGIN( "ssi", d2s_WorkMode);
        d2sProtocolSSI d2s_test;
        d2s_test.SSI_write(0x200,0x2000,false);
        d2s_test.SSI_write(0x202,0x0,false);
        d2s_test.SSI_write(0x12c,0x6000); 
        d2s_test.SSI_write(0x158,0x6);        
        d2s_test.SSI_write(0x244,muxRegs[i]); 
        d2s_test.wait(0.0001);
        
        d2s_test.SSI_write(0x200,0x2000,false);
        d2s_test.SSI_write(0x202,0x40,false);
        d2s_test.SSI_read(0x330,"readdata",9);
        d2s::d2s_LABEL_END();
        
        map<int, long long> capture_data;
        FOREACH_ACTIVE_SITE(api){
            long long readvalue = d2s_test.getReadValue("readdata");
            int site_id = api->Get_active_site();
            capture_data[site_id] = (readvalue | 0x4)>>2 ;
        }

        api->Execute_test("CMU_TCXO_SSI_TMU");

        FOREACH_ACTIVE_SITE(api){
            api->Get_TMU_values("CMU_TCXO_SSI","DBB_GPIO1",THE_MEASURE,&GetValue1,THE_END);           
            api->Get_TMU_values("CMU_TCXO_SSI","DBB_GPIO2",THE_MEASURE,&GetValue2,THE_END);
            int site_id = api->Get_active_site();
            vMeas1[site_id] = GetValue1[0]/1E6;            
            vMeas2[site_id] = GetValue2[0]/1E6;
           
            ValueTest (api, "DBB_GPIO1", vMeas1[site_id], lowl[3*i]/1E6, hil[3*i]/1E6, "MHz", Test_Item[3*i], "FAIL_BIN", Test_number[3*i], Clogenable);
            ValueTest (api, "DBB_GPIO2", vMeas2[site_id], lowl[3*i+1]/1E6, hil[3*i+1]/1E6, "MHz", Test_Item[3*i+1], "FAIL_BIN", Test_number[3*i+1], Clogenable); 
            ValueTest (api, "", capture_data[site_id], 1, 1, "", Test_Item[3*i+2], "FAIL_BIN", Test_number[3*i+2], Clogenable);
         }
    
    }

    d2s::d2s_LABEL_BEGIN( "ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x0,false);
    d2s_test.SSI_write(0x244,0x0); 
    d2s_test.SSI_write(0x12c,0x0);
    d2s_test.SSI_write(0x158,0x0); 
    d2s::d2s_LABEL_END();
    
    FOREACH_ACTIVE_SITE(api){
        int site_id = api->Get_active_site();
        if(Testsoftbin[site_id]!=1){
         api->Set_result_bin(Testsoftbin[site_id]);
        }
    }
        
    return EXIT_SUCCESS;
}

int Rely_off_K4_K5() {
   api->Set_loadboard_x_ubits(X_UBIT_NONE,X_UBIT_000+X_UBIT_015+X_UBIT_038+X_UBIT_074);  //K5 off  
   api->Set_loadboard_x_ubits(X_UBIT_NONE,X_UBIT_042+X_UBIT_003+X_UBIT_029+X_UBIT_083 );  //K4 off
    return EXIT_SUCCESS;
}
//Reset Device
int resetDevice() {
    PHY_ABB_RF_Reset_Module(api);
    return EXIT_SUCCESS;
}

int PCIE_EP_LB() {
    LDO_Module();
    PCIE_EP_LB_Module();
    
    return EXIT_SUCCESS;
}

int Leakage_JTAG() {
    d2s::d2s_LABEL_BEGIN( "ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200,0x2000,false);
    d2s_test.SSI_write(0x202,0x0,false);
    d2s_test.SSI_write(0x130,0x4); 
    d2s_test.SSI_write(0x12c,0x0);
    
    d2s_test.SSI_write(0x200,0x2001,false);
    d2s_test.SSI_write(0x202,0x40,false);
    d2s_test.SSI_write(0x4,0x0); 
    d2s::d2s_LABEL_END();

    return EXIT_SUCCESS;
}

int Pre_Trim_Sum()
{
    double hil[30],lowl[30];
    char *Test_Item[30],*Units[30];
    int  Test_number[30];
    //Read_Limit(lowl,hil,Test_Item,Test_number,Units,api);
    
    long Cycle =200;
    
    double PreVrefMax=0;
    double PreBuckMax=0;
    double PreIrefMax=0;
    
    double PreVrefMin=10;
    double PreBuckMin=10;
    double PreIrefMin=10;
    
    double PreVrefDiff;
    double PreBuckDiff;
    double PreIrefDiff;
    
    long count_flag;
    
    FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
        //int index = api->Get_active_site();
        
        ///////////////////////////////
        //loss judge bin1 branch and print production mode    
        if(HBIN_FLAG[index] == 0)
        {
            TEST_COUNT[index] = TEST_COUNT[index]+1;

            if(TEST_COUNT[index]<Cycle)
            {
                count_flag = 0;
                PRE_VREF_TRIM_SUM[index] = PRE_VREF_TRIM_SUM[index] + PRE_VREF_TRIM[index];
                PRE_BUCK_TRIM_SUM[index] = PRE_BUCK_TRIM_SUM[index] + PRE_BUCK_TRIM[index];
                PRE_IREF_TRIM_SUM[index] = PRE_IREF_TRIM_SUM[index] + PRE_IREF_TRIM[index];

                PreVrefAve[index]=PRE_VREF_TRIM_SUM[index]/TEST_COUNT[index];
                PreBuckAve[index]=PRE_BUCK_TRIM_SUM[index]/TEST_COUNT[index];
                PreIrefAve[index]=PRE_IREF_TRIM_SUM[index]/TEST_COUNT[index];

                PRE_VREF_ARRAY.SetElement(index,TEST_COUNT[index],PRE_VREF_TRIM[index]);
                PRE_BUCK_ARRAY.SetElement(index,TEST_COUNT[index],PRE_BUCK_TRIM[index]);
                PRE_IREF_ARRAY.SetElement(index,TEST_COUNT[index],PRE_IREF_TRIM[index]);
            }
            else if(TEST_COUNT[index]>=Cycle&&TEST_COUNT[index]%Cycle!=0)
            {
                count_flag = 1;
                int i = TEST_COUNT[index]%Cycle;

                PRE_VREF_TRIM_SUM[index]=PRE_VREF_TRIM_SUM[index]-PRE_VREF_ARRAY(index,i)+PRE_VREF_TRIM[index];
                PRE_BUCK_TRIM_SUM[index]=PRE_BUCK_TRIM_SUM[index]-PRE_BUCK_ARRAY(index,i)+PRE_BUCK_TRIM[index];
                PRE_IREF_TRIM_SUM[index]=PRE_IREF_TRIM_SUM[index]-PRE_IREF_ARRAY(index,i)+PRE_IREF_TRIM[index];

                PreVrefAve[index]=PRE_VREF_TRIM_SUM[index]/Cycle;
                PreBuckAve[index]=PRE_BUCK_TRIM_SUM[index]/Cycle;
                PreIrefAve[index]=PRE_IREF_TRIM_SUM[index]/Cycle;

                PRE_VREF_ARRAY.SetElement(index,i,PRE_VREF_TRIM[index]);
                PRE_BUCK_ARRAY.SetElement(index,i,PRE_BUCK_TRIM[index]);
                PRE_IREF_ARRAY.SetElement(index,i,PRE_IREF_TRIM[index]);

            }
            else if(TEST_COUNT[index]>=Cycle&&TEST_COUNT[index]%Cycle==0)
            {
                count_flag = 1;

                PRE_VREF_TRIM_SUM[index]=PRE_VREF_TRIM_SUM[index]-PRE_VREF_ARRAY(index,0)+PRE_VREF_TRIM[index];
                PRE_BUCK_TRIM_SUM[index]=PRE_BUCK_TRIM_SUM[index]-PRE_BUCK_ARRAY(index,0)+PRE_BUCK_TRIM[index];
                PRE_IREF_TRIM_SUM[index]=PRE_IREF_TRIM_SUM[index]-PRE_IREF_ARRAY(index,0)+PRE_IREF_TRIM[index];

                PreVrefAve[index]=PRE_VREF_TRIM_SUM[index]/Cycle;
                PreBuckAve[index]=PRE_BUCK_TRIM_SUM[index]/Cycle;
                PreIrefAve[index]=PRE_IREF_TRIM_SUM[index]/Cycle;

                PRE_VREF_ARRAY.SetElement(index,0,PRE_VREF_TRIM[index]);
                PRE_BUCK_ARRAY.SetElement(index,0,PRE_BUCK_TRIM[index]);
                PRE_IREF_ARRAY.SetElement(index,0,PRE_IREF_TRIM[index]);
            }       

            if(PreVrefAve[index]>PreVrefMax)
            {
                PreVrefMax=PreVrefAve[index];
            }
            if(PreVrefAve[index]<PreVrefMin)
            {
                PreVrefMin=PreVrefAve[index];
            }
            if(PreBuckAve[index]>PreBuckMax)
            {
                PreBuckMax=PreBuckAve[index];
            }
            if(PreBuckAve[index]<PreBuckMin)
            {
                PreBuckMin=PreBuckAve[index];
            }
            if(PreIrefAve[index]>PreIrefMax)
            {
                PreIrefMax=PreIrefAve[index];
            }
            if(PreIrefAve[index]<PreIrefMin)
            {
                PreIrefMin=PreIrefAve[index];
            }

            ValueTest (api, "PMU_REFBP", PreVrefAve[index], lowl[0], hil[0], "V", Test_Item[0], "FAIL_BIN", Test_number[0], Clogenable);
            ValueTest (api, "VDD_BUCK_1V5_IN", PreBuckAve[index], lowl[1], hil[1], "V", Test_Item[1], "FAIL_BIN", Test_number[1], Clogenable);
            ValueTest (api, "PMU_RBIAS", PreIrefAve[index], lowl[2], hil[2], "V", Test_Item[2], "FAIL_BIN", Test_number[2], Clogenable);

            ValueTest (api, "", TEST_COUNT[index], lowl[3], hil[3], "", Test_Item[3], "FAIL_BIN", Test_number[3], Clogenable);
            
        }
        else
        {         
            if(TEST_COUNT[index] < 1)
            {
                count_flag = 0;
                TEST_COUNT[index] = 0;
                PreVrefAve[index] = 0;
                PreBuckAve[index] = 0;
                PreIrefAve[index] = 0;
            }
            else if(TEST_COUNT[index] < Cycle)
            {
                count_flag = 0;
                TEST_COUNT[index] = TEST_COUNT[index];
                PreVrefAve[index] = PreVrefAve[index];
                PreBuckAve[index] = PreBuckAve[index];
                PreIrefAve[index] = PreIrefAve[index];
            }
            else if(TEST_COUNT[index]>=Cycle)
            {
                count_flag = 1;
                TEST_COUNT[index] = TEST_COUNT[index];
                PreVrefAve[index] = PreVrefAve[index];
                PreBuckAve[index] = PreBuckAve[index];
                PreIrefAve[index] = PreIrefAve[index];
            }
            
        }
    FOREACH_ACTIVESITE_END
       
    PreVrefDiff = PreVrefMax - PreVrefMin;
    PreBuckDiff = PreBuckMax - PreBuckMin;
    PreIrefDiff = PreIrefMax - PreIrefMin;

    FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
        ValueTest (api, "", PreVrefDiff, lowl[4], hil[4], "V", Test_Item[4], "FAIL_BIN", Test_number[4], Clogenable);
        ValueTest (api, "", PreBuckDiff, lowl[5], hil[5], "V", Test_Item[5], "FAIL_BIN", Test_number[5], Clogenable);
        ValueTest (api, "", PreIrefDiff, lowl[6], hil[6], "V", Test_Item[6], "FAIL_BIN", Test_number[6], Clogenable);  
  
        if(count_flag==0)
        {          
            ValueTest (api, "", 0.000001, lowl[7], hil[7], "V", Test_Item[7], "FAIL_BIN", Test_number[7], Clogenable);
            ValueTest (api, "", 0.000001, lowl[8], hil[8], "V", Test_Item[8], "FAIL_BIN", Test_number[8], Clogenable);
            ValueTest (api, "", 0.000001, lowl[9], hil[9], "V", Test_Item[9], "FAIL_BIN", Test_number[9], Clogenable); 
        }
        else
        {
            ValueTest (api, "", PreVrefDiff, lowl[7], hil[7], "V", Test_Item[7], "FAIL_BIN", Test_number[7], Clogenable);
            ValueTest (api, "", PreBuckDiff, lowl[8], hil[8], "V", Test_Item[8], "FAIL_BIN", Test_number[8], Clogenable);
            ValueTest (api, "", PreIrefDiff, lowl[9], hil[9], "V", Test_Item[9], "FAIL_BIN", Test_number[9], Clogenable);
        }
	FOREACH_ACTIVESITE_END
        
    return EXIT_SUCCESS;
}
