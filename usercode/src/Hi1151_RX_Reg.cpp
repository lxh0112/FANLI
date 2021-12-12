//#include "UserAPI.h" 
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string.h>
#include "d2sProtocolSSI.h"
#include "RegDef.h"
#include "Globle_Var.h"

using namespace std;

int WLAN_2G_RX_C0_PLL_Reg(emRX_Band Band_Select,double BW)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    switch(Band_Select)
    {
        case(WLAN_2G_RX_L_Band):  //2412MHz
        {
            //Write PLL register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x5066);      //d516,Set PLL freq to 2412MHz
            d2s_test.SSI_write(0x14, 0x6666);      //d517
            d2s_test.wait(0.0001);
            
            //d513,PLL EN,need wait
            d2s_test.SSI_write(0x4, 0x1000);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x1003);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x100B);
            d2s_test.wait(0.0001);
            
            //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x5111);    //RX_2G_C0_L_LPF20
            break;
        }          
        case(WLAN_2G_RX_M_Band):  //2442MHz
        {
            //Write PLL register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x5166);      //d516,Set PLL freq to 2442MHz
            d2s_test.SSI_write(0x14, 0x6666);      //d517
            d2s_test.wait(0.001);
            
            //d513,PLL EN,need wait
            d2s_test.SSI_write(0x4, 0x1000);
            d2s_test.wait(0.001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x1003);
            d2s_test.wait(0.001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x100B);
            d2s_test.wait(0.001);
            
            //write LPW and band register
            if(BW == 10e6)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x5021);      //RX_2G_C0_M_LPF10
            } 
            else if(BW == 20e6)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x5121);      //RX_2G_C0_M_LPF20
            }          
            break;
        }
        case(WLAN_2G_RX_H_Band):  //2472MHz
        {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x5266);      //d516,Set PLL freq to 2472MHz
            d2s_test.SSI_write(0x14, 0x6666);      //d517
            d2s_test.wait(0.0001);
            
            //d513,PLL EN,need wait
            d2s_test.SSI_write(0x4, 0x1000);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x1003);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x100B);
            d2s_test.wait(0.0001);
            
             //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x5131);      //RX_2G_C0_H_LPF20
            break;
        }
    }
    
    d2s::d2s_LABEL_END();
    
    return EXIT_SUCCESS;
}

int WLAN_2G_RX_C1_PLL_Reg(emRX_Band Band_Select,double BW)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    switch(Band_Select)
    {     
        case(WLAN_2G_RX_L_Band):  //2412MHz
            //Write PLL register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x5066);      //d516,Set PLL freq to 2412MHz
            d2s_test.SSI_write(0x14, 0x6666);      //d517
            d2s_test.wait(0.0001);
            
            //d513,PLL EN,need wait
            d2s_test.SSI_write(0x4, 0x1000);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x1003);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x100B);
            d2s_test.wait(0.0001);
            
             //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x7111);      //RX_2G_C1_L_LPF20
            break;
            
        case(WLAN_2G_RX_M_Band):  //2442MHz
            //Write PLL register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x5166);      //d516,Set PLL freq to 2442MHz
            d2s_test.SSI_write(0x14, 0x6666);      //d517
            d2s_test.wait(0.0001);
            
            //d513,PLL EN,need wait
            d2s_test.SSI_write(0x4, 0x1000);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x1003);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x100B);
            d2s_test.wait(0.0001);
            
            //write LPW and band register
            if(BW == 10e6)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x7021);      //RX_2G_C1_M_LPF10
            }
            else if(BW == 20e6)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x7121);      //RX_2G_C1_M_LPF20
            }
//            else
//                TheExec.Datalog.WriteComment "WLAN_2G_RX_C1_PLL_Reg Error: Cannot identify BW: " & BW
            break;

        case(WLAN_2G_RX_H_Band):  //2472MHz
            //Write PLL register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x5266);      //d516,Set PLL freq to 2472MHz
            d2s_test.SSI_write(0x14, 0x6666);      //d517
            d2s_test.wait(0.0001);
            
            //d513,PLL EN,need wait
            d2s_test.SSI_write(0x4, 0x1000);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x1003);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x100B);
            d2s_test.wait(0.0001);
            
            //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x7131);      //RX_2G_C1_H_LPF20   
            break;
    }   
    d2s::d2s_LABEL_END();
    
    return EXIT_SUCCESS;
}

int WLAN_5G_RX_C0_PLL_Reg(emRX_Band Band_Select,double BW)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    switch(Band_Select)
    {
       case(WLAN_5G_RX_A_Band):  //4950MHz
             //Write PLL register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x5280);      //d516,Set PLL freq to 4950MHz
            d2s_test.SSI_write(0x14, 0x0);         //d517
            d2s_test.wait(0.0001);
            
            //d513,PLL EN,need wait
            d2s_test.SSI_write(0x4, 0x1000);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x1003);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x100B);
            d2s_test.wait(0.0001);
            
             //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x1211);      //RX_5G_C0_A_LPF40
            break;
            
         case(WLAN_5G_RX_B_Band):  //5250MHz
             //Write PLL register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x5780);      //d516,Set PLL freq to 5250MHz
            d2s_test.SSI_write(0x14, 0x0);         //d517
            d2s_test.wait(0.0001);
            
            //d513,PLL EN,need wait
            d2s_test.SSI_write(0x4, 0x1000);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x1003);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x100B);
            d2s_test.wait(0.0001);
            
            //write LPW and band register
            if(BW == 20e6)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x1112);      //RX_5G_C0_B_LPF20
            }
    
            else if(BW == 40e6)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x1212);      //RX_5G_C0_B_LPF40
            }
//            else
//                TheExec.Datalog.WriteComment "WLAN_5G_RX_C0_PLL_Reg Error: Cannot identify BW: " & BW
            break;

        case(WLAN_5G_RX_C_Band):  //5580MHz
            //Write PLL register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x5D00);      //d516,Set PLL freq to 5580MHz
            d2s_test.SSI_write(0x14, 0x0);         //d517
            d2s_test.wait(0.0001);
            
            //d513,PLL EN,need wait
            d2s_test.SSI_write(0x4, 0x1000);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x1003);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x100B);
            d2s_test.wait(0.0001);
            
            //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x1215);      //RX_5G_C0_C_LPF40
            break;

        case(WLAN_5G_RX_D_Band):  //5725MHz
            //Write PLL register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x5F6A);      //d516,Set PLL freq to 5720MHz
            d2s_test.SSI_write(0x14, 0xAAAA);      //d517
            d2s_test.wait(0.0001);
            
            //d513,PLL EN,need wait
            d2s_test.SSI_write(0x4, 0x1000);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x1003);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x100B);
            d2s_test.wait(0.0001);
            
            //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x1217);      //RX_5G_C0_D_LPF40
            break;
    }
   
    d2s::d2s_LABEL_END();
    
    return EXIT_SUCCESS;
}

int WLAN_5G_RX_C1_PLL_Reg(emRX_Band Band_Select,double BW)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    switch(Band_Select)
    {
       case(WLAN_5G_RX_A_Band):  //4950MHz
             //Write PLL register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x5280);      //d516,Set PLL freq to 4950MHz
            d2s_test.SSI_write(0x14, 0x0);         //d517
            d2s_test.wait(0.0001);
            
            //d513,PLL EN,need wait
            d2s_test.SSI_write(0x4, 0x1000);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x1003);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x100B);
            d2s_test.wait(0.0001);
            
             //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x3211);      //RX_5G_C1_A_LPF40
            break;
            
         case(WLAN_5G_RX_B_Band):  //5250MHz
             //Write PLL register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x5780);      //d516,Set PLL freq to 5250MHz
            d2s_test.SSI_write(0x14, 0x0);         //d517
            d2s_test.wait(0.0001);
            
            //d513,PLL EN,need wait
            d2s_test.SSI_write(0x4, 0x1000);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x1003);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x100B);
            d2s_test.wait(0.0001);
            
            //write LPW and band register
            if(BW == 20e6)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x3112);      //RX_5G_C1_B_LPF20
            }
            else if(BW == 40e6)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x3212);      //RX_5G_C1_B_LPF40
            }
//            else
//                TheExec.Datalog.WriteComment "WLAN_5G_RX_C1_PLL_Reg Error: Cannot identify BW: " & BW
            break;

        case(WLAN_5G_RX_C_Band):  //5580MHz
            //Write PLL register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x5D00);      //d516,Set PLL freq to 5580MHz
            d2s_test.SSI_write(0x14, 0x0);         //d517
            d2s_test.wait(0.0001);
            
            //d513,PLL EN,need wait
            d2s_test.SSI_write(0x4, 0x1000);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x1003);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x100B);
            d2s_test.wait(0.0001);
            
            //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x3215);      //RX_5G_C1_C_LPF40
            break;

        case(WLAN_5G_RX_D_Band):  //5725MHz
            //Write PLL register
             d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x5F6A);      //d516,Set PLL freq to 5720MHz
            d2s_test.SSI_write(0x14, 0xAAAA);      //d517
            d2s_test.wait(0.0001);
            
            //d513,PLL EN,need wait
            d2s_test.SSI_write(0x4, 0x1000);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x1003);
            d2s_test.wait(0.0001);
            
            //d513,need wait
            d2s_test.SSI_write(0x4, 0x100B);
            d2s_test.wait(0.0001);
            
            //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x3217);      //RX_5G_C1_D_LPF40
            break;
            
    }
    
    d2s::d2s_LABEL_END();
    
    return EXIT_SUCCESS;
}


int WLAN_2G_RX_C0_BW_Reg(emRX_Band Band_Select,double BW)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    switch(Band_Select)
    {
        case(WLAN_2G_RX_L_Band):  //2412MHz
            
            //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x5111);    //RX_2G_C0_L_LPF20
            break;           
        case(WLAN_2G_RX_M_Band):  //2442MHz
            
            //write LPW and band register
            if(BW == 10e6)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x5021);      //RX_2G_C0_M_LPF10
            }
            else if(BW == 20e6)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x5121);      //RX_2G_C0_M_LPF20
            }
//            else
//                TheExec.Datalog.WriteComment "WLAN_2G_RX_C0_BW_Reg Error: Cannot identify BW: " & BW
        break;
                
        case(WLAN_2G_RX_H_Band):  //2472MHz
            
             //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x5131);      //RX_2G_C0_H_LPF20
        break;     
    }
            
    d2s::d2s_LABEL_END();
    
    return EXIT_SUCCESS;
}

int WLAN_2G_RX_C1_BW_Reg(emRX_Band Band_Select,double BW)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    switch(Band_Select)
    {
        case(WLAN_2G_RX_L_Band):  //2412MHz
        {   
             //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x7111);      //RX_2G_C1_L_LPF20
            break;
        }
        case(WLAN_2G_RX_M_Band):  //2442MHz
        {    
            //write LPW and band register
            if(BW == 10e6)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x7021);      //RX_2G_C1_M_LPF10
            }
            else if(BW == 20e6)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x7121);      //RX_2G_C1_M_LPF20
//            else
//                TheExec.Datalog.WriteComment "WLAN_2G_RX_C1_BW_Reg Error: Cannot identify BW: " & BW
            }
            break;
        }
        case(WLAN_2G_RX_H_Band):  //2472MHz
        {
            //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x7131);      //RX_2G_C1_H_LPF20
            break;
        }
    }
    
    d2s::d2s_LABEL_END();
    
    return EXIT_SUCCESS;
}

int WLAN_5G_RX_C0_BW_Reg(emRX_Band Band_Select,double BW)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    switch(Band_Select)
    {
       case(WLAN_5G_RX_A_Band):  //4950MHz
             
             //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x1211);      //RX_5G_C0_A_LPF40
            break;
         case(WLAN_5G_RX_B_Band):  //5250MHz
            
            //write LPW and band register
            if(BW == 20e6)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x1112);      //RX_5G_C0_B_LPF20
            }
            else if(BW == 40e6)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x1212);      //RX_5G_C0_B_LPF40
            }
            break;
//            else
//                TheExec.Datalog.WriteComment "WLAN_5G_RX_C0_BW_Reg Error: Cannot identify BW: " & BW
        case(WLAN_5G_RX_C_Band):  //5580MHz
            
            //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x1215);      //RX_5G_C0_C_LPF40
            break;
        case(WLAN_5G_RX_D_Band):  //5725MHz
        
            //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x1217);      //RX_5G_C0_D_LPF40
            break;
    }
    d2s::d2s_LABEL_END();
    
    return EXIT_SUCCESS;
}

int WLAN_5G_RX_C1_BW_Reg(emRX_Band Band_Select,double BW)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    switch(Band_Select)
    {
       case(WLAN_5G_RX_A_Band):  //4950MHz
            
             //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x3211);      //RX_5G_C1_A_LPF40
            break;
         case(WLAN_5G_RX_B_Band):  //5250MHz
            
            //write LPW and band register
            if(BW == 20e6)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x3112);      //RX_5G_C1_B_LPF20
            }
            else if(BW == 40e6)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x3212);      //RX_5G_C1_B_LPF40
            }
//            else
//                TheExec.Datalog.WriteComment "WLAN_5G_RX_C1_BW_Reg Error: Cannot identify BW: " & BW
            break;

        case(WLAN_5G_RX_C_Band):  //5580MHz
          
            //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x3215);      //RX_5G_C1_C_LPF40
            break;

        case(WLAN_5G_RX_D_Band):  //5725MHz
            
            //write LPW and band register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x3217);      //RX_5G_C1_D_LPF40
            break;
    }   
    d2s::d2s_LABEL_END();
    
    return EXIT_SUCCESS;
}

int WLAN_2G_RX_C0_Gain_Mode_Reg(char *RX_Gain_Mode_Label)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    if(!strcmp(RX_Gain_Mode_Label,"WL_2G_RF_32p9_LPF_6_VGA_26"))
    {

         d2s_test.SSI_write(0x200, 0x2000, false);
         d2s_test.SSI_write(0x202, 0x90, false);
         d2s_test.SSI_write(0x24, 0x1FA);       //reg9, RF_32p9_LPF_6_VGA_26
    }
    else if(!strcmp(RX_Gain_Mode_Label,"WL_2G_RF_32p9_LPF_6_VGA_N4"))
    {
         d2s_test.SSI_write(0x200, 0x2000, false);
         d2s_test.SSI_write(0x202, 0x90, false);
         d2s_test.SSI_write(0x24, 0x1FC);       //reg9,RF_32p9_LPF_6_VGA_N4
    }
    else if(!strcmp(RX_Gain_Mode_Label,"WL_2G_RF_26p9_LPF_6_VGA_N4"))
    {
         d2s_test.SSI_write(0x200, 0x2000, false);
         d2s_test.SSI_write(0x202, 0x90, false);
         d2s_test.SSI_write(0x24, 0x1DC);       //reg9,RF_26p9_LPF_6_VGA_N4
    }
    else if(!strcmp(RX_Gain_Mode_Label,"WL_2G_RF_20p9_LPF_6_VGA_N4"))
    {
         d2s_test.SSI_write(0x200, 0x2000, false);
         d2s_test.SSI_write(0x202, 0x90, false);
         d2s_test.SSI_write(0x24, 0x1BC);       //reg9,RF_20p9_LPF_6_VGA_N4
    }
    else if(!strcmp(RX_Gain_Mode_Label,"WL_2G_RF_14p9_LPF_6_VGA_N4"))
    {
         d2s_test.SSI_write(0x200, 0x2000, false);
         d2s_test.SSI_write(0x202, 0x90, false);
         d2s_test.SSI_write(0x24, 0x19C);       //reg9,RF_14p9_LPF_6_VGA_N4
    }
    else if(!strcmp(RX_Gain_Mode_Label,"WL_2G_RF_8p9_LPF_6_VGA_N4"))
    {
         d2s_test.SSI_write(0x200, 0x2000, false);
         d2s_test.SSI_write(0x202, 0x90, false);
         d2s_test.SSI_write(0x24, 0x17C);       //reg9,RF_8p9_LPF_6_VGA_N4
    }
    else if(!strcmp(RX_Gain_Mode_Label,"WL_2G_RF_2p9_LPF_6_VGA_N4"))
    {
         d2s_test.SSI_write(0x200, 0x2000, false);
         d2s_test.SSI_write(0x202, 0x90, false);
         d2s_test.SSI_write(0x24, 0x15C);       //reg9,RF_2p9_LPF_6_VGA_N4
    }
    else if(!strcmp(RX_Gain_Mode_Label,"WL_2G_RF_N3p1_LPF_6_VGA_N4"))
    {
         d2s_test.SSI_write(0x200, 0x2000, false);
         d2s_test.SSI_write(0x202, 0x90, false);
         d2s_test.SSI_write(0x24, 0x13C);       //reg9,RF_N3p1_LPF_6_VGA_N4
    }
    else if(!strcmp(RX_Gain_Mode_Label,"WL_2G_RF_32p9_LPF_6_VGA_1"))
    {
         d2s_test.SSI_write(0x200, 0x2000, false);
         d2s_test.SSI_write(0x202, 0x90, false);
         d2s_test.SSI_write(0x24, 0x1E1);       //reg9,RF_32p9_LPF_6_VGA_1
    }
    
     d2s::d2s_LABEL_END();
    
    return EXIT_SUCCESS;
}

int WLAN_2G_RX_C1_Gain_Mode_Reg( char *RX_Gain_Mode_Label)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    if(!strcmp(RX_Gain_Mode_Label,"WL_2G_RF_32p9_LPF_6_VGA_26"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x28, 0x1FA);       //reg10,RF_32p9_LPF_6_VGA_26
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_2G_RF_32p9_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x28, 0x1FC);       //reg10,RF_32p9_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_2G_RF_26p9_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x28, 0x1DC);       //reg10,RF_26p9_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_2G_RF_20p9_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x28, 0x1BC);       //reg10,RF_20p9_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_2G_RF_14p9_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x28, 0x19C);       //reg10,RF_14p9_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_2G_RF_8p9_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x28, 0x17C);       //reg10,RF_8p9_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_2G_RF_2p9_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x28, 0x15C);       //reg10,RF_2p9_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_2G_RF_N3p1_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x28, 0x13C);       //reg10,RF_N3p1_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_2G_RF_32p9_LPF_6_VGA_1"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x28, 0x1E1);       //reg10,RF_32p9_LPF_6_VGA_1
       }

    d2s::d2s_LABEL_END();
    
    return EXIT_SUCCESS;
}

int WLAN_5G_RX_C0_Gain_Mode_Reg(char *RX_Gain_Mode_Label)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    if(!strcmp(RX_Gain_Mode_Label,"WL_5G_RF_32p9_LPF_6_VGA_26"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x24, 0x1FA);       //reg10,RF_32p9_LPF_6_VGA_26
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_5G_RF_32p9_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x24, 0x1FC);       //reg10,RF_32p9_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_5G_RF_26p9_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x24, 0x1DC);       //reg10,RF_26p9_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_5G_RF_20p9_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x24, 0x1BC);       //reg10,RF_20p9_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_5G_RF_14p9_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x24, 0x19C);       //reg10,RF_14p9_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_5G_RF_8p9_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x24, 0x17C);       //reg10,RF_8p9_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_5G_RF_2p9_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x24, 0x15C);       //reg10,RF_2p9_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_5G_RF_N3p1_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x24, 0x13C);       //reg10,RF_N3p1_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_5G_RF_32p9_LPF_6_VGA_1"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x24, 0x1E1);       //reg10,RF_32p9_LPF_6_VGA_1
       }
  
    d2s::d2s_LABEL_END();
    
    return EXIT_SUCCESS;
}

int WLAN_5G_RX_C1_Gain_Mode_Reg(char *RX_Gain_Mode_Label)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    if(!strcmp(RX_Gain_Mode_Label,"WL_5G_RF_32p9_LPF_6_VGA_26"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x28, 0x1FA);       //reg10,RF_32p9_LPF_6_VGA_26
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_5G_RF_32p9_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x28, 0x1FC);       //reg10,RF_32p9_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_5G_RF_26p9_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x28, 0x1DC);       //reg10,RF_26p9_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_5G_RF_20p9_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x28, 0x1BC);       //reg10,RF_20p9_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_5G_RF_14p9_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x28, 0x19C);       //reg10,RF_14p9_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_5G_RF_8p9_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x28, 0x17C);       //reg10,RF_8p9_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_5G_RF_2p9_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x28, 0x15C);       //reg10,RF_2p9_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_5G_RF_N3p1_LPF_6_VGA_N4"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x28, 0x13C);       //reg10,RF_N3p1_LPF_6_VGA_N4
       }
       else if(!strcmp(RX_Gain_Mode_Label,"WL_5G_RF_32p9_LPF_6_VGA_1"))
       {
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x28, 0x1E1);       //reg10,RF_32p9_LPF_6_VGA_1
       } 
    d2s::d2s_LABEL_END();
    
    return EXIT_SUCCESS;
}

int WLAN_Disable_Reg()
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xC0, false);
    d2s_test.SSI_write(0x4, 0x0);    //d513

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x0, 0x0);         //reg0
    d2s_test.SSI_write(0x4, 0x0);         //reg1
    
    d2s::d2s_LABEL_END();
    
    return EXIT_SUCCESS;
}

int TestMux_RX_C0_Reg()
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    
    d2s_test.SSI_write(0x0, 0x1);    //wl_trx_reg0
    d2s_test.SSI_write(0x4, 0x0);    //wl_trx_reg1
    d2s_test.SSI_write(0x8, 0x3);    //wl_trx_reg2
    
    d2s_test.SSI_write(0x54, 0xF);         //wl_trx_reg21 TestMux C0 RX
    d2s_test.SSI_write(0x58, 0xF);         //wl_trx_reg22 TestMux C0 RX
    d2s_test.SSI_write(0x5C, 0x3);         //wl_trx_reg23 TestMux C0 RX
    d2s_test.SSI_write(0x60, 0x0);         //wl_trx_reg24 TestMux C0 RX
    d2s_test.SSI_write(0x64, 0x0);         //wl_trx_reg25 TestMux C0 RX
    d2s_test.SSI_write(0x68, 0x3);         //wl_trx_reg26 TestMux C0 RX
    d2s_test.SSI_write(0x6C, 0x3A2); 
    
    d2s::d2s_LABEL_END();
    
    return EXIT_SUCCESS;
}

int TestMux_RX_C1_Reg()
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    
    d2s_test.SSI_write(0x0, 0x2);      //wl_trx_reg0
    d2s_test.SSI_write(0x4, 0x0);      //wl_trx_reg1
    d2s_test.SSI_write(0x8, 0x3);      //wl_trx_reg2

    d2s_test.SSI_write(0x54, 0xF);         //wl_trx_reg21  TestMux C1 RX
    d2s_test.SSI_write(0x58, 0xF);         //wl_trx_reg22  TestMux C1 RX
    d2s_test.SSI_write(0x5C, 0x30);        //wl_trx_reg23  TestMux C1 RX
    d2s_test.SSI_write(0x60, 0x0);         //wl_trx_reg24  TestMux C1 RX
    d2s_test.SSI_write(0x64, 0x0);         //wl_trx_reg25  TestMux C1 RX
    d2s_test.SSI_write(0x68, 0x3);         //wl_trx_reg26  TestMux C1 RX
    d2s_test.SSI_write(0x6C, 0x3A2);       //wl_trx_reg27  TestMux C1 RX
    
    d2s::d2s_LABEL_END();
    
    return EXIT_SUCCESS;
}
