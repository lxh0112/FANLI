//#include "Excel.h"
#include "UserAPI.h" 
#include "d2sProtocolSSI.h"
#include "RegDef.h"
#include "Globle_Var.h"

void WLAN_2G_TX_C0_PLL_Reg(emTX_Band Band_Select)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
   switch(Band_Select)
   {
        case(WLAN_2G_TX_L_Band):  //2412MHz
            //write PLL register
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
            
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x5011);      //TX_2G_C0_L_LPF24
            break;
//            d2s_test.wait(0.0001)
            
        case(WLAN_2G_TX_M_Band):  //2442MHz
        
            //write PLL register
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
            
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x5021);      //TX_2G_C0_M_LPF24
            break;
//            d2s_test.wait(0.0001)
            
        case(WLAN_2G_TX_H_Band):  //2472MHz
            //write PLL register
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
            
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x5031);      //TX_2G_C0_H_LPF24
            break;
//            d2s_test.wait(0.0001)

   }
   d2s::d2s_LABEL_END();
}

void WLAN_2G_TX_C1_PLL_Reg(emTX_Band Band_Select)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    switch(Band_Select)
    {
        case(WLAN_2G_TX_L_Band):  //2412MHz
            //write PLL register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x5066);      //d516,Set PLL freq to 2412MHz
            d2s_test.SSI_write(0x14, 0x6666);      //d517
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x1000);   //d513,PLL EN,need wait
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x1003);   //d513,need wait
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x100B);   //d513,need wait
            d2s_test.wait(0.0001);
            
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x7011);      //TX_2G_C1_L_LPF24
            break;
//            d2s_test.wait(0.0001)
            
        case(WLAN_2G_TX_M_Band):  //2442MHz
            //write PLL register
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
            
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x7021);      //TX_2G_C1_M_LPF24
            break;
//            d2s_test.wait(0.0001)
            
        case(WLAN_2G_TX_H_Band):  //2472MHz
            //write PLL register
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
            
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x7031);      //TX_2G_C1_H_LPF24
            break;
//            d2s_test.wait(0.0001)

    }
    d2s::d2s_LABEL_END();
}

void WLAN_5G_TX_C0_PLL_Reg(emTX_Band Band_Select, double BW)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    switch(Band_Select)
    {
       case(WLAN_5G_TX_B2_Band): //5210MHz
            //write PLL Register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x56D5);      //d516,Set PLL freq to 5210MHz
            d2s_test.SSI_write(0x14, 0x5555);      //d517
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x1000);   //d513,PLL EN,need wait
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x1003);   //d513,need wait
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x100B);   //d513,need wait
            d2s_test.wait(0.0001);
            
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x1412);      //TX_5G_C0_B2_LPF48
            break;
//            d2s_test.wait(0.0001)
            
        case(WLAN_5G_TX_B4_Band): //5540MHz
            //write PLL Register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x5C55);      //d516,Set PLL freq to 5540MHz
            d2s_test.SSI_write(0x14, 0x5555);      //d517
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x1000);   //d513,PLL EN,need wait
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x1003);   //d513,need wait
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x100B);   //d513,need wait
            d2s_test.wait(0.0001);
            
            //write LPW and band register
            if(BW == 24000000)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x1014);      //TX_5G_C0_B4_LPF24
            }
            else if(BW == 48000000)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x1414);      //TX_5G_C0_B4_LPF48
            }
//            else
//                TheExec.Datalog.WriteComment "WLAN_2G_RX_C0_PLL_Reg Error: Cannot identify BW: " & BW
            break;
            
//            d2s_test.wait(0.0001)

        case(WLAN_5G_TX_B7_Band): //5785MHz
            //write PLL Register
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x606A);      //d516,Set PLL freq to 5785MHz
            d2s_test.SSI_write(0x14, 0xAAAA);      //d517
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x1000);   //d513,PLL EN,need wait
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x1003);   //d513,need wait
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x100B);   //d513,need wait
            d2s_test.wait(0.0001);
            
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x1417);      //TX_5G_C0_B7_LPF48
            break;
//            d2s_test.wait(0.0001)
    }
    d2s::d2s_LABEL_END();
}

void WLAN_5G_TX_C1_PLL_Reg(emTX_Band Band_Select, double BW)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    switch(Band_Select)
    {
       case(WLAN_5G_TX_B2_Band): //5210MHz
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x56D5);      //d516,Set PLL freq to 5210MHz
            d2s_test.SSI_write(0x14, 0x5555);      //d517
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x1000);   //d513,PLL EN,need wait
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x1003);   //d513,need wait
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x100B);   //d513,need wait
            d2s_test.wait(0.0001);
            
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x3412);      //TX_5G_C1_B2_LPF48
            break;
//            d2s_test.wait(0.0001)
            
        case(WLAN_5G_TX_B4_Band): //5540MHz
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x5C55);      //d516,Set PLL freq to 5540MHz
            d2s_test.SSI_write(0x14, 0x5555);      //d517
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x1000);   //d513,PLL EN,need wait
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x1003);   //d513,need wait
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x100B);   //d513,need wait
            d2s_test.wait(0.0001);
            
            //write LPW and band register
            if(BW == 24000000)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x3014);      //TX_5G_C1_B4_LPF24
            }
            else if(BW == 48000000)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x3414);      //TX_5G_C1_B4_LPF48
            }
//            else
//                TheExec.Datalog.WriteComment "WLAN_2G_RX_C0_PLL_Reg Error: Cannot identify BW: " & BW
            break;
            
//            d2s_test.wait(0.0001)

        case(WLAN_5G_TX_B7_Band): //5785MHz
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0xC8, false);
            d2s_test.SSI_write(0x10, 0x606A);      //d516,Set PLL freq to 5785MHz
            d2s_test.SSI_write(0x14, 0xAAAA);      //d517
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x1000);   //d513,PLL EN,need wait
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x1003);   //d513,need wait
            d2s_test.wait(0.0001);
            d2s_test.SSI_write(0x4, 0x100B);   //d513,need wait
            d2s_test.wait(0.0001);
            
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x3417);      //TX_5G_C1_B7_LPF48
            break;
//            d2s_test.wait(0.0001)

    }
    d2s::d2s_LABEL_END();
}

void WLAN_2G_TX_C0_BW_Reg(emTX_Band Band_Select)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
     switch(Band_Select)
     {
        case(WLAN_2G_TX_L_Band):  //2412MHz
            
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x5011);      //TX_2G_C0_L_LPF24
            break;
        case(WLAN_2G_TX_M_Band):  //2442MHz
          
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x5021);      //TX_2G_C0_M_LPF24
            break;

        case(WLAN_2G_TX_H_Band):  //2472MHz
          
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x5031);      //TX_2G_C0_H_LPF24
            break;
     }
     d2s::d2s_LABEL_END();
}

void WLAN_2G_TX_C1_BW_Reg(emTX_Band Band_Select)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    switch(Band_Select)
    {
        case(WLAN_2G_TX_L_Band):  //2412MHz
            
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x7011);      //TX_2G_C1_L_LPF24
            break;
                      
        case(WLAN_2G_TX_M_Band):  //2442MHz
            
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x7021);      //TX_2G_C1_M_LPF24
            break;
            
        case(WLAN_2G_TX_H_Band):  //2472MHz
           
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x7031);      //TX_2G_C1_H_LPF24
            break;
    }
    d2s::d2s_LABEL_END();
}

void WLAN_5G_TX_C0_BW_Reg(emTX_Band Band_Select, double BW)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    switch(Band_Select)
    {
       case(WLAN_5G_TX_B2_Band): //5210MHz
            
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x1412);      //TX_5G_C0_B2_LPF48
            break;
                       
        case(WLAN_5G_TX_B4_Band): //5540MHz
            
            //write BW/LPF and Band
            if(BW == 24000000)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x1014);      //TX_5G_C0_B4_LPF24
            }
    
            else if(BW == 48000000)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x1414);      //TX_5G_C0_B4_LPF48
            }
//            else
//                TheExec.Datalog.WriteComment "WLAN_2G_RX_C0_PLL_Reg Error: Cannot identify BW: " & BW
                break;
            
        case(WLAN_5G_TX_B7_Band): //5785MHz
            
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x1417);      //TX_5G_C0_B7_LPF48
            break;
            
    }
    d2s::d2s_LABEL_END();
}

void WLAN_5G_TX_C1_BW_Reg(emTX_Band Band_Select, double BW)
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    switch(Band_Select)
    {
       case(WLAN_5G_TX_B2_Band): //5210MHz
            
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x3412);      //TX_5G_C1_B2_LPF48
            break;
                        
        case(WLAN_5G_TX_B4_Band): //5540MHz
            
            //write BW/LPF and Band
            if(BW == 24000000)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x3014);      //TX_5G_C1_B4_LPF24
            }
    
            else if(BW == 48000000)
            {
                d2s_test.SSI_write(0x200, 0x2000, false);
                d2s_test.SSI_write(0x202, 0x90, false);
                d2s_test.SSI_write(0x34, 0x3414);      //TX_5G_C1_B4_LPF48
            }
//            else
//                TheExec.Datalog.WriteComment "WLAN_2G_RX_C0_PLL_Reg Error: Cannot identify BW: " & BW
                break;
            

        case(WLAN_5G_TX_B7_Band): //5785MHz
            
            //write BW/LPF and Band
            d2s_test.SSI_write(0x200, 0x2000, false);
            d2s_test.SSI_write(0x202, 0x90, false);
            d2s_test.SSI_write(0x34, 0x3417);      //TX_5G_C1_B7_LPF48
            break;
            
    }
    d2s::d2s_LABEL_END();
}

void TestMux_TX_C0_Reg()
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    
    d2s_test.SSI_write(0x0, 0x0);      //wl_trx_reg0
    d2s_test.SSI_write(0x4, 0x1);      //wl_trx_reg1
    d2s_test.SSI_write(0x8, 0x3);      //wl_trx_reg2

    d2s_test.SSI_write(0x54, 0xC00);       //wl_trx_reg21  TestMux C0 TX
    d2s_test.SSI_write(0x58, 0xC00);       //wl_trx_reg22  TestMux C0 TX
    d2s_test.SSI_write(0x5C, 0x3);         //wl_trx_reg23  TestMux C0 TX
    d2s_test.SSI_write(0x60, 0x0);         //wl_trx_reg24  TestMux C0 TX
    d2s_test.SSI_write(0x64, 0x0);         //wl_trx_reg25  TestMux C0 TX
    d2s_test.SSI_write(0x68, 0x3);         //wl_trx_reg26  TestMux C0 TX
    d2s_test.SSI_write(0x6C, 0x300);       //wl_trx_reg27  TestMux C0 TX
    
    d2s::d2s_LABEL_END();
}

void TestMux_TX_C1_Reg()
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    
    d2s_test.SSI_write(0x0, 0x0);      //wl_trx_reg0
    d2s_test.SSI_write(0x4, 0x2);      //wl_trx_reg1
    d2s_test.SSI_write(0x8, 0x3);      //wl_trx_reg2

    d2s_test.SSI_write(0x54, 0xC00);       //wl_trx_reg21  TestMux C1 TX
    d2s_test.SSI_write(0x58, 0xC00);       //wl_trx_reg22  TestMux C1 TX
    d2s_test.SSI_write(0x5C, 0x30);        //wl_trx_reg23  TestMux C1 TX
    d2s_test.SSI_write(0x60, 0x0);         //wl_trx_reg24  TestMux C1 TX
    d2s_test.SSI_write(0x64, 0x0);         //wl_trx_reg25  TestMux C1 TX
    d2s_test.SSI_write(0x68, 0x3);         //wl_trx_reg26  TestMux C1 TX
    d2s_test.SSI_write(0x6C, 0x300);       //wl_trx_reg27  TestMux C1 TX
    
    d2s::d2s_LABEL_END();
}

int Driver_Mode_Setup()
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0xB0, 0x4);         //pa code,wl_trx_reg44
    d2s_test.SSI_write(0xB4, 0x4);         //pa code,wl_trx_reg45
    d2s_test.SSI_write(0xB8, 0x4);         //pa code,wl_trx_reg46
    d2s_test.SSI_write(0xBC, 0x4);         //pa code,wl_trx_reg47

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0xE4, 0xF323);      //pa bias,wl_trx_reg313
    d2s_test.SSI_write(0xE8, 0xF323);      //pa bias,wl_trx_reg314
    d2s_test.SSI_write(0xEC, 0xF323);      //pa bias,wl_trx_reg315
    d2s_test.SSI_write(0xF0, 0xF323);      //pa bias,wl_trx_reg316
    d2s_test.SSI_write(0xF4, 0xF323);      //pa bias,wl_trx_reg317
    d2s_test.SSI_write(0xF8, 0xF323);      //pa bias,wl_trx_reg318
    d2s_test.SSI_write(0xFC, 0xF323);      //pa bias,wl_trx_reg319
    d2s_test.SSI_write(0x100, 0xF323);     //pa bias,wl_trx_reg320
    d2s_test.SSI_write(0x104, 0xF323);     //pa bias,wl_trx_reg321
    d2s_test.SSI_write(0x108, 0xF323);     //pa bias,wl_trx_reg322
    d2s_test.SSI_write(0x10C, 0xF323);     //pa bias,wl_trx_reg323
    d2s_test.SSI_write(0x110, 0xF323);     //pa bias,wl_trx_reg324
    d2s_test.SSI_write(0x114, 0xF323);     //pa bias,wl_trx_reg325
    d2s_test.SSI_write(0x118, 0xF323);     //pa bias,wl_trx_reg326
    d2s_test.SSI_write(0x11C, 0xF323);     //pa bias,wl_trx_reg327
    d2s_test.SSI_write(0x120, 0xF323);     //pa bias,wl_trx_reg328
    d2s_test.SSI_write(0x154, 0xF323);     //pa bias,wl_trx_reg341
    d2s_test.SSI_write(0x158, 0xF323);     //pa bias,wl_trx_reg342
    d2s_test.SSI_write(0x15C, 0xF323);     //pa bias,wl_trx_reg343
    d2s_test.SSI_write(0x160, 0xF323);     //pa bias,wl_trx_reg344
    d2s_test.SSI_write(0x164, 0xF323);     //pa bias,wl_trx_reg345
    d2s_test.SSI_write(0x168, 0xF323);     //pa bias,wl_trx_reg346
    d2s_test.SSI_write(0x16C, 0xF323);     //pa bias,wl_trx_reg347
    d2s_test.SSI_write(0x170, 0xF323);     //pa bias,wl_trx_reg348
    d2s_test.SSI_write(0x174, 0xF323);     //pa bias,wl_trx_reg349
    d2s_test.SSI_write(0x178, 0xF323);     //pa bias,wl_trx_reg350
    d2s_test.SSI_write(0x17C, 0xF323);     //pa bias,wl_trx_reg351
    d2s_test.SSI_write(0x180, 0xF323);     //pa bias,wl_trx_reg352
    d2s_test.SSI_write(0x184, 0xF323);     //pa bias,wl_trx_reg353
    d2s_test.SSI_write(0x188, 0xF323);     //pa bias,wl_trx_reg354
    d2s_test.SSI_write(0x18C, 0xF323);     //pa bias,wl_trx_reg355
    d2s_test.SSI_write(0x190, 0xF323);     //pa bias,wl_trx_reg356
    
    //20210107 add for UPC code
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x94, 0x7);//attention loss true
    d2s_test.SSI_write(0xA4, 0x7);//attention loss true    
    
    d2s::d2s_LABEL_END();
    return EXIT_SUCCESS;
}

int Driver_Mode_Recover_Setup()
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0xB0, 0x1F);         //pa code,wl_trx_reg44
    d2s_test.SSI_write(0xB4, 0x1F);         //pa code,wl_trx_reg45
    d2s_test.SSI_write(0xB8, 0x1F);         //pa code,wl_trx_reg46
    d2s_test.SSI_write(0xBC, 0x1F);         //pa code,wl_trx_reg47

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0xE4, 0xC942);      //wl_trx_reg313
    d2s_test.SSI_write(0xE8, 0xC9E2);      //wl_trx_reg314
    d2s_test.SSI_write(0xEC, 0x8E03);      //wl_trx_reg315
    d2s_test.SSI_write(0xF0, 0x8D93);      //wl_trx_reg316
    d2s_test.SSI_write(0xF4, 0xC992);      //wl_trx_reg317
    d2s_test.SSI_write(0xF8, 0xCA82);      //wl_trx_reg318
    d2s_test.SSI_write(0xFC, 0x8E63);      //wl_trx_reg319
    d2s_test.SSI_write(0x100, 0x8E63);     //wl_trx_reg320
    d2s_test.SSI_write(0x104, 0xC9E2);     //wl_trx_reg321
    d2s_test.SSI_write(0x108, 0xCAA2);     //wl_trx_reg322
    d2s_test.SSI_write(0x10C, 0x9663);     //wl_trx_reg323
    d2s_test.SSI_write(0x110, 0x9663);     //wl_trx_reg324
    d2s_test.SSI_write(0x114, 0xCA32);     //wl_trx_reg325
    d2s_test.SSI_write(0x118, 0xCAD2);     //wl_trx_reg326
    d2s_test.SSI_write(0x11C, 0xA263);     //wl_trx_reg327
    d2s_test.SSI_write(0x120, 0xA283);     //wl_trx_reg328
    d2s_test.SSI_write(0x154, 0xC942);     //wl_trx_reg341
    d2s_test.SSI_write(0x158, 0xC9E2);     //wl_trx_reg342
    d2s_test.SSI_write(0x15C, 0x7A03);     //wl_trx_reg343
    d2s_test.SSI_write(0x160, 0x7993);     //wl_trx_reg344
    d2s_test.SSI_write(0x164, 0xC992);     //wl_trx_reg345
    d2s_test.SSI_write(0x168, 0xCA82);     //wl_trx_reg346
    d2s_test.SSI_write(0x16C, 0x7A63);     //wl_trx_reg347
    d2s_test.SSI_write(0x170, 0x7A63);     //wl_trx_reg348
    d2s_test.SSI_write(0x174, 0xC9E2);     //wl_trx_reg349
    d2s_test.SSI_write(0x178, 0xCAA2);     //wl_trx_reg350
    d2s_test.SSI_write(0x17C, 0x8263);     //wl_trx_reg351
    d2s_test.SSI_write(0x180, 0x8263);     //wl_trx_reg352
    d2s_test.SSI_write(0x184, 0xCA32);     //wl_trx_reg353
    d2s_test.SSI_write(0x188, 0xCAD2);     //wl_trx_reg354
    d2s_test.SSI_write(0x18C, 0x8E63);     //wl_trx_reg355
    d2s_test.SSI_write(0x190, 0x8E83);     //wl_trx_reg356
    
    d2s::d2s_LABEL_END();
    
    return EXIT_SUCCESS;
}

int DummyOP_Path_Setup()
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x1C, 0x1E1E);
   // d2s_test.SSI_write(0x34, 0x7121);
    d2s_test.SSI_write(0x54, 0xC0);
    d2s_test.SSI_write(0x58, 0xC0);

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0x37C, 0xF400);
    d2s_test.SSI_write(0x384, 0xF400);
    
    d2s::d2s_LABEL_END();    
    return EXIT_SUCCESS;
}

int DummyOP_Path_Recover()
{
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x1C, 0x1D1D);
   // d2s_test.SSI_write(0x34, 0x7121);
    d2s_test.SSI_write(0x54, 0xC00);
    d2s_test.SSI_write(0x58, 0xC00);

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0x37C, 0xF0);
    d2s_test.SSI_write(0x384, 0xF0);
    
    d2s::d2s_LABEL_END();    
    return EXIT_SUCCESS;
}
