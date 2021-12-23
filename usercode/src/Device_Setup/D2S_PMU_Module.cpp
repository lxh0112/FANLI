#include <UserAPI.h>
#include "d2sProtocolSSI.h"
#include "D2S_PMU_Module.h"
#include "Globle_Var.h"
#include <string>
#include <math.h>
#include "Capture_Function.h"


using namespace PhxAPI;

void bootUp_module() {

    //From SSI manual AON&CLDO Power Up sheet  version 1.3
    d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x236, 0x1, false);    //Step 1
    d2s_test.SSI_write(0x232, 0x3, false);    //Step 2
    d2s_test.SSI_write(0x234, 0x0, false);    //Step 3  B
    d2s_test.wait(0.003);    
    d2s_test.SSI_write(0x234, 0xB, false);    //Step 3  B
    d2s_test.wait(0.003);   

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x0, false);
    d2s_test.SSI_write(0x4, 0x1151);   //GLB_SYS_CTL_PAGE0_KEY
    d2s_test.SSI_write(0x8, 0x1151);   //GLB_SYS_CTL_PAGE1_KEY

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);
    d2s_test.SSI_write(0x4, 0x1151);   //PMU_CMU_CTL_PAGE0_KEY
    d2s_test.SSI_write(0x8, 0x1151);   //PMU_CMU_CTL_PAGE1_KEY

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x4, 0x1151);   //RF_ABB_CTL_PAGE0_KEY
    d2s_test.SSI_write(0x8, 0x1151);   //RF_ABB_CTL_PAGE1_KEY

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);
    d2s_test.SSI_write(0x204, 0x9);    //BUCK_FRQ_SEL change from 8 to 9 for V1.0
    d2s_test.SSI_write(0x208, 0x6);    //BUCK_RESERVED   change 7 to 6 for V1.0

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x270, 0x1);    //WL_RF_ABB_REG_SEL
    d2s_test.SSI_write(0x278, 0x3);    //RF_REG_CLK_EN

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);
    d2s_test.SSI_write(0x124, 0x20);   //PMU_CFG
    d2s_test.SSI_write(0x16C, 0x40);   //RFLDO4_CFG0
    d2s_test.SSI_write(0x154, 0x1A0);      //EFUSE_VALUE_MAN
    d2s_test.SSI_write(0x14C, 0xFFFF);     //EFUSE_VALUE_SEL

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x84, 0x0);     //RF_TRX_REG33
    
    //set XLDO to 2.8V    @2017-06-22
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);
    d2s_test.SSI_write(0x32C, 0x1A);      //RF_TRX_REG33
    d2s_test.SSI_write(0x32C, 0x1B);      //RF_TRX_REG33

    d2s::d2s_LABEL_END();
    
}


void LDO_Module() {

    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x0, false);
    d2s_test.SSI_write(0x24C, 0x1);    //BOOT_MAN1
    d2s_test.SSI_write(0x248, 0x1);    //BOOT_MAN0
    d2s_test.SSI_write(0x260, 0x1F);   //BOOT_MAN_SEL
    d2s_test.SSI_write(0x25C, 0x0);    //TEST_POWERDOWN_MAN

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);
    d2s_test.SSI_write(0x10C, 0x33);   //PMU_CMU_CTL_CLDO_CFG
    d2s_test.wait(0.0002);    
//    d2s_test.SSI_write(0x130, 0x820);      //PMU_LDO_EN_STS

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x0, false);
    d2s_test.SSI_write(0x24C, 0x0);    //BOOT_MAN1
    d2s_test.SSI_write(0x248, 0x0);    //BOOT_MAN0
    d2s_test.SSI_write(0x250, 0x1);    //BOOT_MAN2
    d2s_test.SSI_write(0x26C, 0xF);    //CLDO_RTS_SEL
    d2s_test.SSI_write(0x264, 0x3);    //SOFT_RESET
    d2s_test.SSI_write(0x264, 0xC);    //SOFT_RESET
    
    d2s_test.SSI_write(0x154, 0x0);    //ABB_CALI_RST_CFG
    d2s_test.SSI_write(0x154, 0x1);    //ABB_CALI_RST_CFG
    
    d2s_test.SSI_write(0x236, 0x0, false);    //SSI_MUX
    d2s_test.wait(0.0002);    
    
    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x0, false);
    d2s_test.SSI_write(0x4, 0x1151);   //LCL_CTL_PAGE0_KEY
    d2s_test.SSI_write(0x8, 0x1151);   //LCL_CTL_PAGE1_KEY

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x20, false);
    d2s_test.SSI_write(0x4, 0x1151);   //COEX_CTL_PAGE0_KEY
    d2s_test.SSI_write(0x8, 0x1151);   //COEX_CTL_PAGE1_KEY

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);       //1-> 4 2017-05-26
    d2s_test.SSI_write(0x0, 0x33);   //LCL_CTL_SOFT_RST_PHY
    d2s_test.SSI_write(0x0, 0x3F);   //LCL_CTL_SOFT_RST_PHY
    
    d2s_test.SSI_write(0x14, 0x1FF);   //LOCAL_CLK_EN3
    
    // start high frequency
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);
    d2s_test.SSI_write(0x218, 0x5);    //INTLDO_CFG
    d2s_test.wait(0.0002);    
    
//    d2s_test.SSI_write(0x130, 0x3820);   //PMU_LDO_EN_STS
    d2s_test.SSI_write(0x218, 0x1);    //INTLDO_CFG
    d2s_test.wait(0.00005);    
    
    d2s_test.SSI_write(0x140, 0x8F88);    //LDO_EN_DELAY_CNT2   2017-08-11 for V1.4 ,2017-05-12 8E88 for V1.0
    
    d2s_test.SSI_write(0x320, 0x452);   //CMU_CFG_7
    d2s_test.SSI_write(0x118, 0x1);    //RFLDO3_CFG
    d2s_test.wait(0.0002);    
//    d2s_test.SSI_write(0x130, 0x3924);   //PMU_LDO_EN_STS
    
    d2s_test.SSI_write(0x31C, 0x281);   //CMU_CFG_6
    d2s_test.SSI_write(0x310, 0x30);   //CMU_CFG_3
    d2s_test.SSI_write(0x314, 0x0);    //CMU_CFG_4
    d2s_test.SSI_write(0x318, 0x0);    //CMU_CFG_5
    d2s_test.SSI_write(0x33C, 0x19B);   //CMU_RESERVE
    d2s_test.SSI_write(0x300, 0xE04);   //CMU_CFG_0
    d2s_test.SSI_write(0x300, 0x604);   //CMU_CFG_0
   // d2s_test.SSI_write(0x330, 0x6);    //CMU_LOCK_STS   modified at 20170508
    d2s_test.wait(0.0002);      //add wait time
    d2s_test.SSI_write(0x304, 0xC);    //CMU_CFG_1

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x0, false);
    d2s_test.SSI_write(0x118, 0x1);    //AON_CLK_MUX0
    d2s_test.SSI_write(0x11C, 0x1);    //AON_CLK_MUX1
    
    //////RF Init
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);
    
    d2s_test.SSI_write(0x13C, 0xFF8);    //LDO_EN_DELAY_CNT1   2017-08-11 for V1.4, 2017-05-12 EE8 for V1.0
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x0, false);
    d2s_test.SSI_write(0x118, 0x0);    //AON_CLK_MUX0  2017-08-11 for V1.4
    d2s_test.SSI_write(0x11C, 0x0);    //AON_CLK_MUX1  2017-08-11 for V1.4
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);
    
//    d2s_test.SSI_write(0x16C, 0x1);    //RFLDO4_CFG0
//    d2s_test.wait(0.0002);       @not need to enable RFLDO4
//    d2s_test.SSI_write(0x170, 0x4);    //RFLDO4_CFG1
    d2s_test.SSI_write(0x110, 0x1);    //RFLD1_CFG
    d2s_test.wait(0.0002);    
//    d2s_test.SSI_write(0x130, 0x3D34);   //PMU_LDO_EN_STS
    d2s_test.SSI_write(0x114, 0x1);    //RFLD2_CFG
    d2s_test.wait(0.0002);    
//    d2s_test.SSI_write(0x130, 0x3F3C);   //PMU_LDO_EN_STS
    d2s_test.SSI_write(0x124, 0x30);   //PMU_CFG
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x0, false);
    d2s_test.SSI_write(0x118, 0x1);    //AON_CLK_MUX0  2017-08-11 for V1.4
    d2s_test.SSI_write(0x11C, 0x1);    //AON_CLK_MUX1  2017-08-11 for V1.4
    
    //ABB Init
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);
    d2s_test.SSI_write(0x11C, 0x100);   //RFLD4_CFG
    d2s_test.SSI_write(0x11C, 0x101);   //RFLD4_CFG
    d2s_test.wait(0.0002);    
    
//    d2s_test.SSI_write(0x130, 0x3FBE);   //PMU_LDO_EN_STS
    d2s_test.SSI_write(0x120, 0x100);   //RFLD5_CFG
    d2s_test.SSI_write(0x120, 0x101);   //RFLD5_CFG
    d2s_test.wait(0.0002);    
    
//    d2s_test.SSI_write(0x130, 0x3FFF);   //PMU_LDO_EN_STS
    d2s_test.SSI_write(0x124, 0x30);   //PMU_CFG
    d2s_test.SSI_write(0x300, 0x4);    //CMU_CFG_0
    d2s_test.SSI_write(0x304, 0x4);    //CMU_CFG_1
    d2s_test.SSI_write(0x324, 0x0);    //CMU_CFG_8

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x244, 0x1010);   //ABB_WL_ADC_0CH_CTRL_REG
    d2s_test.SSI_write(0x25C, 0x1010);   //ABB_WL_ADC_1CH_CTRL_REG
    d2s_test.SSI_write(0x250, 0x1010);   //ABB_WL_DAC_0CH_CTRL_REG
    d2s_test.SSI_write(0x268, 0x1010);   //ABB_WL_DAC_1CH_CTRL_REG
    d2s_test.SSI_write(0x240, 0x111);   //ABB_WL_ADC_0CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x258, 0x111);   //ABB_WL_ADC_1CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x24C, 0x111);   //ABB_WL_ADC_0CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x264, 0x111);   //ABB_WL_ADC_1CH_CTRL_REG_SEL
    //Until step 12 of ABB debug sheet.

    d2s::d2s_LABEL_END();    
    
}


void CMU_Module() {

    //copy from step 13 to the end of ABB debug sheet.
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    
    d2s_test.SSI_write(0x244, 0x10);   //ABB_WL_ADC_0CH_CTRL_REG @remove for ECO test, keep in standby
    d2s_test.SSI_write(0x25C, 0x10);   //ABB_WL_ADC_1CH_CTRL_REG
    d2s_test.SSI_write(0x250, 0x10);   //ABB_WL_DAC_0CH_CTRL_REG
    d2s_test.SSI_write(0x268, 0x10);   //ABB_WL_DAC_1CH_CTRL_REG
    
    d2s_test.SSI_write(0x244, 0x11);   //ABB_WL_ADC_0CH_CTRL_REG
    d2s_test.SSI_write(0x25C, 0x11);   //ABB_WL_ADC_1CH_CTRL_REG
    d2s_test.SSI_write(0x250, 0x11);   //ABB_WL_DAC_0CH_CTRL_REG
    d2s_test.SSI_write(0x268, 0x11);   //ABB_WL_DAC_1CH_CTRL_REG
    
    d2s_test.SSI_write(0x244, 0x1);   //ABB_WL_ADC_0CH_CTRL_REG
    d2s_test.SSI_write(0x25C, 0x1);   //ABB_WL_ADC_1CH_CTRL_REG
    d2s_test.SSI_write(0x250, 0x1);   //ABB_WL_DAC_0CH_CTRL_REG
    d2s_test.SSI_write(0x268, 0x1);   //ABB_WL_DAC_1CH_CTRL_REG

    d2s_test.SSI_write(0x244, 0x101);   //ABB_WL_ADC_0CH_CTRL_REG
    d2s_test.SSI_write(0x25C, 0x101);   //ABB_WL_ADC_1CH_CTRL_REG
    d2s_test.SSI_write(0x250, 0x101);   //ABB_WL_DAC_0CH_CTRL_REG
    d2s_test.SSI_write(0x268, 0x101);   //ABB_WL_DAC_1CH_CTRL_REG
    
    d2s_test.SSI_write(0x200, 0x2000, false);    //power down VPH//s gate, @2017-06-02
    d2s_test.SSI_write(0x202, 0x40, false);  //power down VPH//s gate, @2017-06-02
    d2s_test.SSI_write(0x10C, 0x13);    //power down VPH//s gate, @2017-06-02

    d2s::d2s_LABEL_END();
    
}





void TSENSOR_Module() {

    d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x304, 0x0);    //TSENSOR_CTRL1  1->0
    d2s_test.SSI_write(0x2EC, 0x32);   //TSENSOR_CLK_DIV  0x28->0x32 20170428 for moving Tsensor after bootup , divide by 50 from SSI clock 50MHz
    d2s_test.SSI_write(0x2EC, 0x128);   //TSENSOR_CLK_DIV

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x0, false);
    d2s_test.SSI_write(0x124, 0xF);    //RF_PLL_CLK_EN

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x2F8, 0x0);    //TSENSOR_CTRL
    d2s_test.SSI_write(0x2F8, 0x1);    //TSENSOR_CTRL
    d2s_test.SSI_write(0x2F4, 0x1);    //TSENSOR_START
    
    d2s::d2s_LABEL_END();
    
}


void EFUSE_DATA_Module() {

	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
    d2sProtocolSSI d2s_test;   
    long i;
    
    d2s_test.SSI_write(0x304, 0x64, false);
    d2s_test.SSI_write(0x280, 0x5A5A, false);

    d2s_test.wait(0.001);     
    
    for (i=0;i<=31;i++){
//         Call SSI_read_Module(0x2C4 + i * 2, false, 3)
	}
    
	d2s::d2s_LABEL_END();
    
}
void BOOST_OFF(){


}


void PCIE_EP_LB_Module() {

    //File:  1151V200_PCIE_EP_LB.xlsx
    //Sheet: PCIE_EP_LB
    //File time: 10/11/2017 4:52:30 PM

    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x204, 0x0, false);     //PCIE_W_DBI_SEL

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x0, false);
    d2s_test.SSI_write(0x214, 0x100);   //PCIE_W_DBI_SEL
    d2s_test.SSI_write(0x21C, 0x100);   //PCIE_R_DBI_SEL

    d2s_test.SSI_write(0x204, 0x1, false);     //PCIE_REG0

    d2s_test.SSI_write(0x200, 0x4000, false);
    d2s_test.SSI_write(0x202, 0x8, false);
    d2s_test.SSI_write(0x90, 0x0);         //PCIE_REG0

    d2s_test.SSI_write(0x204, 0x8000, false);      //PCIE_REG1
    d2s_test.SSI_write(0xB8, 0x1);         //PCIE_REG1

    d2s_test.SSI_write(0x204, 0x1, false);     //PCIE_REG2

    d2s_test.SSI_write(0x200, 0x4000, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x310, 0x124);   //PCIE_REG2
    
    d2s_test.wait(0.0001);    

    d2s_test.SSI_write(0x204, 0x10, false);    //PCIE_REG3

    d2s_test.SSI_write(0x200, 0x4000, false);
    d2s_test.SSI_write(0x202, 0x0, false);
    d2s_test.SSI_write(0x4, 0x7);   //PCIE_REG3

    d2s_test.SSI_write(0x204, 0x1, false);     //PCIE_REG4

    d2s_test.SSI_write(0x200, 0x4000, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x310, 0x24);       //PCIE_REG4
    
    d2s_test.wait(0.0001);    

    d2s_test.SSI_write(0x204, 0x0, false);     //PCIE_REG5

    d2s_test.SSI_write(0x200, 0x4000, false);
    d2s_test.SSI_write(0x202, 0x8, false);
    d2s_test.SSI_write(0x100, 0x0);    //PCIE_REG5
    d2s_test.SSI_write(0x104, 0x0);    //PCIE_REG6

    d2s_test.SSI_write(0x204, 0x8000, false);      //PCIE_REG7
    d2s_test.SSI_write(0x108, 0x0);        //PCIE_REG7

    d2s_test.SSI_write(0x204, 0x5000, false);      //PCIE_REG8
    d2s_test.SSI_write(0x10C, 0x0);        //PCIE_REG8

    d2s_test.SSI_write(0x204, 0x0, false);     //PCIE_REG9
    d2s_test.SSI_write(0x110, 0x0);    //PCIE_REG9

    d2s_test.SSI_write(0x204, 0x50FF, false);      //PCIE_REG10
    d2s_test.SSI_write(0x114, 0xFFFF);   //PCIE_REG10

    d2s_test.SSI_write(0x204, 0x2000, false);      //PCIE_REG11
    d2s_test.SSI_write(0x118, 0x0);        //PCIE_REG11

    d2s_test.SSI_write(0x204, 0x0, false);     //PCIE_REG12
    d2s_test.SSI_write(0x11C, 0x0);    //PCIE_REG12

    d2s_test.SSI_write(0x204, 0x2000, false);      //PCIE_REG12

    d2s_test.SSI_write(0x200, 0x4000, false);
    d2s_test.SSI_write(0x202, 0x0, false);
    d2s_test.SSI_write(0x10, 0x0);         //PCIE_REG12

    d2s_test.SSI_write(0x204, 0x0, false);     //PCIE_W_DBI_SEL

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x0, false);
    d2s_test.SSI_write(0x214, 0x0);    //PCIE_W_DBI_SEL
    d2s_test.SSI_write(0x21C, 0x0);    //PCIE_R_DBI_SEL
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x0, false);
    d2s_test.SSI_write(0x118, 0x0);    //AON_CLK_MUX0
    d2s_test.SSI_write(0x11C, 0x0);    //AON_CLK_MUX1
    
	d2s::d2s_LABEL_END();
    
}

