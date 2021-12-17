/* 
 * File:   D2S_ABB_Module.cpp
 * Author: dzr
 *
 * Created on 2020年11月10日, 下午3:28
 */
//#include "Systick.h"
#include "api.h" 
#include "d2sProtocolSSI.h"
#include "D2S_ABB_Module.h"
#include "string.h"
#include "CCWaveformsData.h"
#include "Globle_Var.h"
#include "Capture_Function.h"

#include "minwindef.h"



void WL_ADC_C0_DC_Module() {
    
    long i;
    long j;
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    
    d2s_test.SSI_write(0x290, 0x0);    //WL_DC_EN
    d2s_test.SSI_write(0x218, 0x60);   //PN_CAPMIS_INDEX
    d2s_test.SSI_write(0x298, 0x0);    //WL_DC_MODE
    d2s_test.SSI_write(0x294, 0x1);    //WL_DC_WAIT_CYCLE_SEL
    d2s_test.SSI_write(0x29C, 0x1);    //WL_DC_PN_CAPSTAT
    d2s_test.SSI_write(0x290, 0x1);    //WL_DC_EN
    
    d2s_test.wait(0.0001);
    
    d2s_test.SSI_write(0x290, 0x0);    //WL_DC_EN
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);
    d2s::d2s_LABEL_END();
}


void WL_ADC_C1_DC_Module() {
    
    long i;
    long j;
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    
    d2s_test.SSI_write(0x2B4, 0x0);    //WL_DC_EN
    d2s_test.SSI_write(0x284, 0x60);   //PN_CAPMIS_INDEX
    d2s_test.SSI_write(0x2BC, 0x0);    //WL_DC_MODE
    d2s_test.SSI_write(0x2B8, 0x1);    //WL_DC_WAIT_CYCLE_SEL
    d2s_test.SSI_write(0x2C0, 0x1);    //WL_DC_PN_CAPSTAT
    d2s_test.SSI_write(0x2B4, 0x1);    //WL_DC_EN
    
    d2s_test.wait(0.0001);
    
    d2s_test.SSI_write(0x2B4, 0x0);    //WL_DC_EN
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);
    
    d2s::d2s_LABEL_END();
}


void WL_ADC_C0_Cap_Module(CSiteLong *pReadValue) {

    long i;
    long j;
    char cReadFlag[32] = {"\0"};
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;

    /**************before capture Module***********************************/
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x0, 0x0);      //RF reg0
    d2s_test.SSI_write(0x4, 0x0);      //RF reg1
    d2s_test.SSI_write(0x8, 0x0);      //RF reg2
    d2s_test.SSI_write(0xC, 0x0);      //RF reg3
    d2s_test.SSI_write(0x10, 0x0);     //RF reg4
    d2s_test.SSI_write(0x14, 0x0);     //RF reg5
    d2s_test.SSI_write(0x18, 0x0);     //RF reg6
    d2s_test.SSI_write(0x68, 0x3);     //S25
    d2s_test.SSI_write(0x6C, 0x300);   //S0B
    d2s_test.SSI_write(0x5C, 0x3);     //S20
    d2s_test.SSI_write(0x54, 0xF);     //S08&S00
    d2s_test.SSI_write(0x58, 0x0);     //muxreg
    d2s_test.SSI_write(0x60, 0x0);     //muxreg
    d2s_test.SSI_write(0x64, 0x0);     //muxreg

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x240, 0x111);      //ABB_WL_ADC_0CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x244, 0x1);        //ABB_WL_ADC_0CH_CTRL_REG
    
    d2s_test.wait(0.00005);
    
    d2s_test.SSI_write(0x244, 0x101);      //ABB_WL_ADC_0CH_CTRL_REG
        
    d2s_test.SSI_write(0x258, 0x111);   //ABB_WL_ADC_1CH_CTRL_REG_SEL  @20170525
    d2s_test.SSI_write(0x25C, 0x0);     //ABB_WL_ADC_1CH_CTRL_REG
    
    d2s_test.SSI_write(0x24C, 0x111);   //ABB_WL_DAC_0CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x250, 0x0);     //ABB_WL_DAC_0CH_CTRL_REG
    
    d2s_test.SSI_write(0x264, 0x111);      //ABB_WL_DAC_1CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x268, 0x0);    //ABB_WL_DAC_1CH_CTRL_REG
    
    d2s_test.wait(0.00005);
    /**************before capture Module***********************************/
   
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x1);    //PKTMEM_MODE_CFG

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x1);    //PKTMEM_SEL

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x11);   //PKTMEM_MODE_CFG
    
    d2s_test.wait(0.001);

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x0);    //PKTMEM_SEL

    d2s_test.wait(0.00005);
    
    //2003C000~2003FFFF

//    d2s_test.SSI_write(0x200, 0x2003, false);
//
//    for(i=0;i<8;i++){         //0xc0 to 0xfc, step 4
//        d2s_test.SSI_write(0x202, 0xC0 + i * 4, false);
//    
//        for(j=0;j<128;j++){       //0 to 0x3ff
//            //Call SSI_read_Module(0x0 + 8 * j, True, 8);
//            //Call SSI_read_Module(0x2 + 8 * j, True, 8);
//            long k=i*128+j;
//            sprintf(cReadFlag, "readdata_i%d", k);
//            d2s_test.SSI_read(0x0 + 8 * j,cReadFlag,7);
//            
//            sprintf(cReadFlag, "readdata_q%d", k);
//            d2s_test.SSI_read(0x2 + 8 * j,cReadFlag,7);
//        }
//    }
//    
    d2s::d2s_LABEL_END();
//
//    long long nCapData[2048] = {0};
//    int nsize = sizeof (nCapData) / sizeof (long long);
//
////    CSysTick sysTick;   
//    FOREACH_ACTIVE_SITE(api) {
//
//        if (!d2s::isProductionMode()) {
//            for (j = 0; j < 1024; j++) {
//                sprintf(cReadFlag, "readdata_i%d", j);
//                //            sysTick.Start();
//                nCapData[j * 2] = d2s_test.getReadValue(cReadFlag);
//                //            sysTick.End();
//                //            api->info_message(".........................getReadValue:%f ms", sysTick.GetElapsedTime());     
//
//                sprintf(cReadFlag, "readdata_q%d", j);
//                nCapData[j * 2 + 1] = d2s_test.getReadValue(cReadFlag);
//            }
//        } else {
//            unsigned long data[32768];
//            
//            api->Get_capture_data("DBB_GPIO7", 0, 32768, data);
//
//            for(int n = 0;n<32768;n+=16)
//            {
//                nCapData[n/16] = ConvertCapData(data+n,16);
//            }
//        }
//        
//        pReadValue->InitDataArray(site_id, nsize);
//        pReadValue->CopyElement(site_id, nCapData,nsize);
//    }
        
}

void WL_ADC_C0_Cap_Module_read(CSiteLong *pReadValue) {

    long i;
    long j;
    char cReadFlag[32] = {"\0"};
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;    
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0xA0, false);
//    d2s_test.SSI_write(0x2F8, 0x1);    //PKTMEM_MODE_CFG
//
//    d2s_test.SSI_write(0x200, 0x2001, false);
//    d2s_test.SSI_write(0x202, 0x4, false);
//    d2s_test.SSI_write(0x2CC, 0x1);    //PKTMEM_SEL
//
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0xA0, false);
//    d2s_test.SSI_write(0x2F8, 0x11);   //PKTMEM_MODE_CFG
//    
//    d2s_test.wait(0.001);
//
//    d2s_test.SSI_write(0x200, 0x2001, false);
//    d2s_test.SSI_write(0x202, 0x4, false);
//    d2s_test.SSI_write(0x2CC, 0x0);    //PKTMEM_SEL
//
//    d2s_test.wait(0.00005);
    
    //2003C000~2003FFFF

    d2s_test.SSI_write(0x200, 0x2003, false);

    for(i=0;i<8;i++){         //0xc0 to 0xfc, step 4
        d2s_test.SSI_write(0x202, 0xC0 + i * 4, false);
    
        for(j=0;j<128;j++){       //0 to 0x3ff
            //Call SSI_read_Module(0x0 + 8 * j, True, 8);
            //Call SSI_read_Module(0x2 + 8 * j, True, 8);
            long k=i*128+j;
            sprintf(cReadFlag, "readdata_i%d", k);
            d2s_test.SSI_read(0x0 + 8 * j,cReadFlag,7);
            
            sprintf(cReadFlag, "readdata_q%d", k);
            d2s_test.SSI_read(0x2 + 8 * j,cReadFlag,7);
        }
    }
    
    d2s::d2s_LABEL_END();

    long long nCapData[2048] = {0};
    int nsize = sizeof (nCapData) / sizeof (long long);

////    CSysTick sysTick;
//    FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
//
//        if (!d2s::isProductionMode()) {
//            for (j = 0; j < 1024; j++) {
//                sprintf(cReadFlag, "readdata_i%d", j);
//                //            sysTick.Start();
//                nCapData[j * 2] = d2s_test.getReadValue(cReadFlag).at(site_id);
//                //            sysTick.End();
//                //            api->info_message(".........................getReadValue:%f ms", sysTick.GetElapsedTime());
//
//                sprintf(cReadFlag, "readdata_q%d", j);
//                nCapData[j * 2 + 1] = d2s_test.getReadValue(cReadFlag).at(site_id);
//            }
//        } else {
//            unsigned long data[32768];
//            DIO_Capture(site_id,"DBB_GPIO7",data);
////            api->Get_capture_data("DBB_GPIO7", 0, 32768, data);
//
//            for(int n = 0;n<32768;n+=16)
//            {
//                nCapData[n/16] = ConvertCapData(data+n,16);
//            }
//        }
//
//        pReadValue->InitDataArray(site_id, nsize);
//        pReadValue->CopyElement(site_id, nCapData,nsize);
//	FOREACH_ACTIVESITE_END


	if (!d2s::isProductionMode()) {
		FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
		for (j = 0; j < 1024; j++) {
			sprintf(cReadFlag, "readdata_i%d", j);
			nCapData[j * 2] = d2s_test.getReadValue(cReadFlag).at(site_id);
			sprintf(cReadFlag, "readdata_q%d", j);
			nCapData[j * 2 + 1] = d2s_test.getReadValue(cReadFlag).at(site_id);
		}
		pReadValue->InitDataArray(site_id, nsize);
		pReadValue->CopyElement(site_id,nCapData,nsize);

	FOREACH_ACTIVESITE_END
	} else {

		unsigned long data[32768];

		auto CAP_Data = TheInst.Digital().PatEng().GetCaptureData("DBB_GPIO7");

		for (auto siteData : CAP_Data)
		{
			for (auto pinData : siteData.second)
			{
				int i=0;
				for (auto capData : pinData.second)
				{
					data[i] = capData.iECResult;
					i++;
				}
			}
			for(int n = 0;n<32768;n+=16)
			{
				nCapData[n/16] = ConvertCapData(data+n,16);
			}

			pReadValue->InitDataArray(siteData.first, nsize);
			pReadValue->CopyElement(siteData.first,nCapData,nsize);
		}
	}

}

void WL_RX_CAL_PHASE_ADC_C0_Cap_Module(CSiteLong *pReadValue) {

    long i;
    long j;
    char cReadFlag[32] = {"\0"};
    d2s::d2s_LABEL_BEGIN("ssi", LearningMode);//LearningMode);//ProductionMode);
    d2sProtocolSSI d2s_test;    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x1);    //PKTMEM_MODE_CFG

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x1);    //PKTMEM_SEL

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x11);   //PKTMEM_MODE_CFG
    
    d2s_test.wait(0.001);

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x0);    //PKTMEM_SEL

    d2s_test.wait(0.00005);
    
    //2003C000~2003FFFF

    d2s_test.SSI_write(0x200, 0x2003, false);

    for(i=0;i<16;i++){         //0xc0 to 0xfc, step 4
        d2s_test.SSI_write(0x202, 0xC0 + i * 4, false);
    
        for(j=0;j<128;j++){       //0 to 0x3ff
            //Call SSI_read_Module(0x0 + 8 * j, True, 8);
            //Call SSI_read_Module(0x2 + 8 * j, True, 8);
            long k=i*128+j;
            sprintf(cReadFlag, "readdata_i%d", k);
            d2s_test.SSI_read(0x0 + 8 * j,cReadFlag,7);
            
            sprintf(cReadFlag, "readdata_q%d", k);
            d2s_test.SSI_read(0x2 + 8 * j,cReadFlag,7);
        }
    }
    
    d2s::d2s_LABEL_END();

    long long nCapData[4096] = {0};
    int nsize = sizeof (nCapData) / sizeof (long long);
  
    FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)

        for (j = 0; j < 2048; j++) {
            sprintf(cReadFlag, "readdata_i%d", j);
            nCapData[j*2] = d2s_test.getReadValue(cReadFlag).at(site_id);
            
            sprintf(cReadFlag, "readdata_q%d", j);
            nCapData[j*2+1] = d2s_test.getReadValue(cReadFlag).at(site_id);
        }
        
        pReadValue->InitDataArray(site_id, nsize);
        pReadValue->CopyElement(site_id, nCapData,nsize);
	FOREACH_ACTIVESITE_END
        
}

void WL_PD_BUF_ADC_C0_BeforeCap_Module(CSiteLong *pReadValue) {

    long i;
    long j;
    char cReadFlag[32] = {"\0"};
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);//LearningMode);//ProductionMode);
    d2sProtocolSSI d2s_test;    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x1);    //PKTMEM_MODE_CFG

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x1);    //PKTMEM_SEL

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x11);   //PKTMEM_MODE_CFG
    
    d2s_test.wait(0.001);

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x0);    //PKTMEM_SEL

    d2s_test.wait(0.00005);
    
    //2003C000~2003FFFF

//    d2s_test.SSI_write(0x200, 0x2003, false);
//
//    for(i=0;i<16;i++){         //0xc0 to 0xfc, step 4
//        d2s_test.SSI_write(0x202, 0xC0 + i * 4, false);
//    
//        for(j=0;j<128;j++){       //0 to 0x3ff
//            //Call SSI_read_Module(0x0 + 8 * j, True, 8);
//            //Call SSI_read_Module(0x2 + 8 * j, True, 8);
//            long k=i*128+j;
//            sprintf(cReadFlag, "readdata_i%d", k);
//            d2s_test.SSI_read(0x0 + 8 * j,cReadFlag,7);
//            
//            sprintf(cReadFlag, "readdata_q%d", k);
//            d2s_test.SSI_read(0x2 + 8 * j,cReadFlag,7);
//        }
//    }
    
    d2s::d2s_LABEL_END();

//    long long nCapData[4096] = {0};
//    int nsize = sizeof (nCapData) / sizeof (long long);
//  
//    FOREACH_ACTIVE_SITE(api) {
//
//        for (j = 0; j < 2048; j++) {
//            sprintf(cReadFlag, "readdata_i%d", j);
//            nCapData[j*2] = d2s_test.getReadValue(cReadFlag);
//            
//            sprintf(cReadFlag, "readdata_q%d", j);
//            nCapData[j*2+1] = d2s_test.getReadValue(cReadFlag);
//        }
//        
//        pReadValue->InitDataArray(site_id, nsize);
//        pReadValue->CopyElement(site_id, nCapData,nsize);
//    }
        
}

void WL_PD_BUF_ADC_C0_Cap_Module(CSiteLong *pReadValue) {

    long i;
    long j;
    char cReadFlag[32] = {"\0"};
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);//LearningMode);//ProductionMode);
    d2sProtocolSSI d2s_test;    
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0xA0, false);
//    d2s_test.SSI_write(0x2F8, 0x1);    //PKTMEM_MODE_CFG
//
//    d2s_test.SSI_write(0x200, 0x2001, false);
//    d2s_test.SSI_write(0x202, 0x4, false);
//    d2s_test.SSI_write(0x2CC, 0x1);    //PKTMEM_SEL
//
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0xA0, false);
//    d2s_test.SSI_write(0x2F8, 0x11);   //PKTMEM_MODE_CFG
//    
//    d2s_test.wait(0.001);
//
//    d2s_test.SSI_write(0x200, 0x2001, false);
//    d2s_test.SSI_write(0x202, 0x4, false);
//    d2s_test.SSI_write(0x2CC, 0x0);    //PKTMEM_SEL
//
//    d2s_test.wait(0.00005);
    
    //2003C000~2003FFFF

    d2s_test.SSI_write(0x200, 0x2003, false);

    for(i=0;i<4;i++){         //0xc0 to 0xfc, step 4
        d2s_test.SSI_write(0x202, 0xC0 + i * 4, false);
    
        for(j=0;j<128;j++){       //0 to 0x3ff
            //Call SSI_read_Module(0x0 + 8 * j, True, 8);
            //Call SSI_read_Module(0x2 + 8 * j, True, 8);
            long k=i*128+j;
            sprintf(cReadFlag, "readdata_i%d", k);
            d2s_test.SSI_read(0x0 + 8 * j,cReadFlag,7);
            
            sprintf(cReadFlag, "readdata_q%d", k);
            d2s_test.SSI_read(0x2 + 8 * j,cReadFlag,7);
        }
    }
    
    d2s::d2s_LABEL_END();

    long long nCapData[1024] = {0};
    int nsize = sizeof (nCapData) / sizeof (long long);
  
    FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
        
        if (!d2s::isProductionMode()) {
            for (j = 0; j < 512; j++) {
                sprintf(cReadFlag, "readdata_i%d", j);
                nCapData[j*2] = d2s_test.getReadValue(cReadFlag).at(site_id);

                sprintf(cReadFlag, "readdata_q%d", j);
                nCapData[j*2+1] = d2s_test.getReadValue(cReadFlag).at(site_id);
            }
        } else {
            unsigned long data[16384];
            
            DIO_Capture(site_id,"DBB_GPIO7",data);

//            api->Get_capture_data("DBB_GPIO7", 0, 16384, data);

            for(int n = 0;n<16384;n+=16)
            {
                nCapData[n/16] = ConvertCapData(data+n,16);
            }
        }
        
        pReadValue->InitDataArray(site_id, nsize);
        pReadValue->CopyElement(site_id, nCapData,nsize);
	FOREACH_ACTIVESITE_END
        
}

void WL_PD_BUF_GPIO1_ADC_C0_Cap_Module(CSiteLong *pReadValue) {

    long i;
    long j;
    char cReadFlag[32] = {"\0"};
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);//LearningMode);//ProductionMode);
    d2sProtocolSSI d2s_test;    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x1);    //PKTMEM_MODE_CFG

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x1);    //PKTMEM_SEL

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x11);   //PKTMEM_MODE_CFG
    
    d2s_test.wait(0.001);

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x0);    //PKTMEM_SEL

    d2s_test.wait(0.00005);
    
    //2003C000~2003FFFF

    d2s_test.SSI_write(0x200, 0x2003, false);

    for(i=0;i<1;i++){         //0xc0 to 0xfc, step 4
        d2s_test.SSI_write(0x202, 0xC0 + i * 4, false);
    
        for(j=0;j<64;j++){       //0 to 0x3ff
            //Call SSI_read_Module(0x0 + 8 * j, True, 8);
            //Call SSI_read_Module(0x2 + 8 * j, True, 8);
            long k=i*128+j;
            sprintf(cReadFlag, "readdata_i%d", k);
            d2s_test.SSI_read(0x0 + 8 * j,cReadFlag,7);
            
            sprintf(cReadFlag, "readdata_q%d", k);
            d2s_test.SSI_read(0x2 + 8 * j,cReadFlag,7);
        }
    }
    
    d2s::d2s_LABEL_END();

    long long nCapData[4096] = {0};
    int nsize = sizeof (nCapData) / sizeof (long long);
  
//    FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
////        int site_id = 0;
//
//        if (!d2s::isProductionMode()) {
//            for (j = 0; j < 32; j++) {
//                sprintf(cReadFlag, "readdata_i%d", j);
//                nCapData[j*2] = d2s_test.getReadValue(cReadFlag).at(site_id);
//
//                sprintf(cReadFlag, "readdata_q%d", j);
//                nCapData[j*2+1] = d2s_test.getReadValue(cReadFlag).at(site_id);
//            }
//        } else {
//            unsigned long data[1024];
//
//            DIO_Capture(site_id,"DBB_GPIO7",data);
////            api->Get_capture_data("DBB_GPIO7", 0, 65536, data);
//
//            for(int n = 0;n<1024;n+=16)
//            {
//                nCapData[n/16] = ConvertCapData(data+n,16);
//            }
//        }
//
//        pReadValue->InitDataArray(site_id, nsize);
//        pReadValue->CopyElement(site_id, nCapData,nsize);
//	FOREACH_ACTIVESITE_END

    if (!d2s::isProductionMode()) {
    		FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
		for (j = 0; j < 32; j++) {
			sprintf(cReadFlag, "readdata_i%d", j);
			nCapData[j*2] = d2s_test.getReadValue(cReadFlag).at(site_id);

			sprintf(cReadFlag, "readdata_q%d", j);
			nCapData[j*2+1] = d2s_test.getReadValue(cReadFlag).at(site_id);
		}
    		pReadValue->InitDataArray(site_id, nsize);
    		pReadValue->CopyElement(site_id,nCapData,nsize);

    	FOREACH_ACTIVESITE_END
    	} else {

    		unsigned long data[1024];

    		auto CAP_Data = TheInst.Digital().PatEng().GetCaptureData("DBB_GPIO7");

    		for (auto siteData : CAP_Data)
    		{
    			for (auto pinData : siteData.second)
    			{
    				int i=0;
    				for (auto capData : pinData.second)
    				{
    					data[i] = capData.iECResult;
    					i++;

    				}
    			}

    			for(int n = 0;n<1024;n+=16)
    			{
    				nCapData[n/16] = ConvertCapData(data+n,16);
    			}

    			pReadValue->InitDataArray(siteData.first, nsize);
    			pReadValue->CopyElement(siteData.first,nCapData,nsize);
    		}

    	}
        
}

void WL_ADC_C1_Cap_Module(CSiteLong *pReadValue) {
    
    long i;
    long j;
    char cReadFlag[32] = {"\0"};
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;

    /****************before capture Module*************************/
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x0, 0x0);      //RF reg0  0x3->0 20170508
    d2s_test.SSI_write(0x4, 0x0);      //RF reg1
    d2s_test.SSI_write(0x8, 0x0);      //RF reg2  0x3->0 20170508
    d2s_test.SSI_write(0xC, 0x0);      //RF reg3
    d2s_test.SSI_write(0x10, 0x0);     //RF reg4
    d2s_test.SSI_write(0x14, 0x0);     //RF reg5  0x3400->0 20170508
    d2s_test.SSI_write(0x18, 0x0);     //RF reg6  0x3400->0 20170508
    d2s_test.SSI_write(0x68, 0xC);     //S25
    d2s_test.SSI_write(0x6C, 0x0);     //S0B
    d2s_test.SSI_write(0x5C, 0x0);     //S20
    d2s_test.SSI_write(0x58, 0x3C);    //S18&S10
    d2s_test.SSI_write(0x54, 0x0);     //mux reg
    d2s_test.SSI_write(0x60, 0x0);     //mux reg
    d2s_test.SSI_write(0x64, 0x0);     //mux reg

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x258, 0x111);      //ABB_WL_ADC_1CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x25C, 0x1);    //ABB_WL_ADC_1CH_CTRL_REG
    
    d2s_test.wait(0.00005);
    
    d2s_test.SSI_write(0x25C, 0x101);      //ABB_WL_ADC_1CH_CTRL_REG
    
    d2s_test.SSI_write(0x240, 0x111);      //ABB_WL_ADC_0CH_CTRL_REG_SEL  @20170525
    d2s_test.SSI_write(0x244, 0x0);        //ABB_WL_ADC_0CH_CTRL_REG
      
    d2s_test.SSI_write(0x24C, 0x111);   //ABB_WL_DAC_0CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x250, 0x0);     //ABB_WL_DAC_0CH_CTRL_REG
    
    d2s_test.SSI_write(0x264, 0x111);      //ABB_WL_DAC_1CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x268, 0x0);    //ABB_WL_DAC_1CH_CTRL_REG
    
    d2s_test.wait(0.00005);
/****************before capture Module*************************/
   
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x1);    //PKTMEM_MODE_CFG

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x1);    //PKTMEM_SEL

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x11);   //PKTMEM_MODE_CFG

    d2s_test.wait(0.001);
 
    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x0);    //PKTMEM_SEL

    d2s_test.wait(0.00005);
    
    //2003C000~2003FFFF
    
//    d2s_test.SSI_write(0x200, 0x2003, false);
//
//    for(i=0;i<8;i++){         //0xc0 to 0xfc, step 4
//        d2s_test.SSI_write(0x202, 0xC0 + i * 4, false);
//    
//        for(j=0;j<128;j++){       //0 to 0x3ff
//            //Call SSI_read_Module(0x0 + 8 * j, True, 8);
//            //Call SSI_read_Module(0x2 + 8 * j, True, 8);
//            long k=i*128+j;
//            sprintf(cReadFlag, "readdata_i%d", k);
//            d2s_test.SSI_read(0x4 + 8 * j,cReadFlag,7);
//            
//            sprintf(cReadFlag, "readdata_q%d", k);
//            d2s_test.SSI_read(0x6 + 8 * j,cReadFlag,7);
//        }
//    }
//    
    d2s::d2s_LABEL_END();
//    
//    long long nCapData[2048] = {0};
//    int nsize = sizeof (nCapData) / sizeof (long long);
////    CSiteLong ReadValue;
//    
//    FOREACH_ACTIVE_SITE(api) {
//        
//
//        if (!d2s::isProductionMode()) {
//            for (j = 0; j < 1024; j++) {
//                sprintf(cReadFlag, "readdata_i%d", j);
//                nCapData[j * 2] = d2s_test.getReadValue(cReadFlag);
//                sprintf(cReadFlag, "readdata_q%d", j);
//                nCapData[j * 2 + 1] = d2s_test.getReadValue(cReadFlag);
//            }
//        } 
//        else {
//            unsigned long data[32768];         
//            api->Get_capture_data("DBB_GPIO7", 0, 32768, data);
//
//            for(int n = 0;n<32768;n+=16)
//            {
//                nCapData[n/16] = ConvertCapData(data+n,16);
//            }
//        }
//        
//        pReadValue->InitDataArray(site_id, nsize);
//        pReadValue->CopyElement(site_id, nCapData,nsize);
////        api->info_message("Site:%d---------- %s    measure  value    :    %lld-----------", site_id, "SSI_DATA", ReadValue(site_id, 1));
//    }
    
    
}

void WL_ADC_C1_Cap_Module_read(CSiteLong *pReadValue) {
    
    long i;
    long j;
    char cReadFlag[32] = {"\0"};
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;    
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0xA0, false);
//    d2s_test.SSI_write(0x2F8, 0x1);    //PKTMEM_MODE_CFG
//
//    d2s_test.SSI_write(0x200, 0x2001, false);
//    d2s_test.SSI_write(0x202, 0x4, false);
//    d2s_test.SSI_write(0x2CC, 0x1);    //PKTMEM_SEL
//
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0xA0, false);
//    d2s_test.SSI_write(0x2F8, 0x11);   //PKTMEM_MODE_CFG
//
//    d2s_test.wait(0.001);
// 
//    d2s_test.SSI_write(0x200, 0x2001, false);
//    d2s_test.SSI_write(0x202, 0x4, false);
//    d2s_test.SSI_write(0x2CC, 0x0);    //PKTMEM_SEL
//
//    d2s_test.wait(0.00005);
    
    //2003C000~2003FFFF
    
    d2s_test.SSI_write(0x200, 0x2003, false);

    for(i=0;i<8;i++){         //0xc0 to 0xfc, step 4
        d2s_test.SSI_write(0x202, 0xC0 + i * 4, false);
    
        for(j=0;j<128;j++){       //0 to 0x3ff
            //Call SSI_read_Module(0x0 + 8 * j, True, 8);
            //Call SSI_read_Module(0x2 + 8 * j, True, 8);
            long k=i*128+j;
            sprintf(cReadFlag, "readdata_i%d", k);
            d2s_test.SSI_read(0x4 + 8 * j,cReadFlag,7);
            
            sprintf(cReadFlag, "readdata_q%d", k);
            d2s_test.SSI_read(0x6 + 8 * j,cReadFlag,7);
        }
    }
    
    d2s::d2s_LABEL_END();
    
    long long nCapData[2048] = {0};
    int nsize = sizeof (nCapData) / sizeof (long long);
//    CSiteLong ReadValue;
    
//    FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
//
//
//        if (!d2s::isProductionMode()) {
//            for (j = 0; j < 1024; j++) {
//                sprintf(cReadFlag, "readdata_i%d", j);
//                nCapData[j * 2] = d2s_test.getReadValue(cReadFlag).at(site_id);
//                sprintf(cReadFlag, "readdata_q%d", j);
//                nCapData[j * 2 + 1] = d2s_test.getReadValue(cReadFlag).at(site_id);
//            }
//        }
//        else {
//            unsigned long data[32768];
//            DIO_Capture(site_id,"DBB_GPIO7",data);
////            api->Get_capture_data("DBB_GPIO7", 0, 32768, data);
//
//            for(int n = 0;n<32768;n+=16)
//            {
//                nCapData[n/16] = ConvertCapData(data+n,16);
//            }
//        }
//
//        pReadValue->InitDataArray(site_id, nsize);
//        pReadValue->CopyElement(site_id, nCapData,nsize);
////        api->info_message("Site:%d---------- %s    measure  value    :    %lld-----------", site_id, "SSI_DATA", ReadValue(site_id, 1));
//	FOREACH_ACTIVESITE_END
    if (!d2s::isProductionMode()) {
		FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
		for (j = 0; j < 1024; j++) {
			sprintf(cReadFlag, "readdata_i%d", j);
			nCapData[j * 2] = d2s_test.getReadValue(cReadFlag).at(site_id);
			sprintf(cReadFlag, "readdata_q%d", j);
			nCapData[j * 2 + 1] = d2s_test.getReadValue(cReadFlag).at(site_id);
		}
		pReadValue->InitDataArray(site_id, nsize);
		pReadValue->CopyElement(site_id,nCapData,nsize);

	FOREACH_ACTIVESITE_END
	} else {

		unsigned long data[32768];

		auto CAP_Data = TheInst.Digital().PatEng().GetCaptureData("DBB_GPIO7");

		for (auto siteData : CAP_Data)
		{
			for (auto pinData : siteData.second)
			{
				int i=0;
				for (auto capData : pinData.second)
				{
					data[i] = capData.iECResult;
					i++;
				}
			}
			for(int n = 0;n<32768;n+=16)
			{
				nCapData[n/16] = ConvertCapData(data+n,16);
			}

			pReadValue->InitDataArray(siteData.first, nsize);
			pReadValue->CopyElement(siteData.first,nCapData,nsize);
		}
	}
    
}

void WL_RX_CAL_PHASE_ADC_C1_Cap_Module(CSiteLong *pReadValue) {
    
    long i;
    long j;
    char cReadFlag[32] = {"\0"};
    d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
    d2sProtocolSSI d2s_test;    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x1);    //PKTMEM_MODE_CFG

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x1);    //PKTMEM_SEL

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x11);   //PKTMEM_MODE_CFG

    d2s_test.wait(0.001);
 
    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x0);    //PKTMEM_SEL

    d2s_test.wait(0.00005);
    
    //2003C000~2003FFFF
    
    d2s_test.SSI_write(0x200, 0x2003, false);
    
//    for(i=0;i<15;i++){         //0xc0 to 0xfc, step 4
//        d2s_test.SSI_write(0x202, 0xC0 + i * 4, false);
//    
//        for(j=0;j<127;j++){       //0 to 0x3ff
//            //Call SSI_read_Module(0x4 + 8 * j, True, 8);
//            //Call SSI_read_Module(0x6 + 8 * j, True, 8);
//        }
//    }
    for(i=0;i<16;i++){         //0xc0 to 0xfc, step 4
        d2s_test.SSI_write(0x202, 0xC0 + i * 4, false);
    
        for(j=0;j<128;j++){       //0 to 0x3ff
            //Call SSI_read_Module(0x4 + 8 * j, True, 8);
            //Call SSI_read_Module(0x6 + 8 * j, True, 8);
            long k=i*128+j;
            sprintf(cReadFlag, "readdata_i%d", k);
            d2s_test.SSI_read(0x4 + 8 * j,cReadFlag,7);
            
            sprintf(cReadFlag, "readdata_q%d", k);
            d2s_test.SSI_read(0x6 + 8 * j,cReadFlag,7);
        }
    }
    
    d2s::d2s_LABEL_END();
    
    long long nCapData[4096] = {0};
    int nsize = sizeof (nCapData) / sizeof (long long);
//    CSiteLong ReadValue;
    
    FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)

        for (j = 0; j < 2048; j++) {
            sprintf(cReadFlag, "readdata_i%d", j);
            nCapData[j*2] = d2s_test.getReadValue(cReadFlag).at(site_id);
            
            sprintf(cReadFlag, "readdata_q%d", j);
            nCapData[j*2+1] = d2s_test.getReadValue(cReadFlag).at(site_id);
        }
        
        pReadValue->InitDataArray(site_id, nsize);
        pReadValue->CopyElement(site_id, nCapData,nsize);
//        api->info_message("Site:%d---------- %s    measure  value    :    %lld-----------", site_id, "SSI_DATA", ReadValue(site_id, 1));
	FOREACH_ACTIVESITE_END
    
    
}

void WL_PD_BUF_ADC_C1_BeforeCap_Module(CSiteLong *pReadValue) {
    
    long i;
    long j;
    char cReadFlag[32] = {"\0"};
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x1);    //PKTMEM_MODE_CFG

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x1);    //PKTMEM_SEL

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x11);   //PKTMEM_MODE_CFG

    d2s_test.wait(0.001);
 
    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x0);    //PKTMEM_SEL

    d2s_test.wait(0.00005);
    
    //2003C000~2003FFFF
    
//    d2s_test.SSI_write(0x200, 0x2003, false);
//    
//    for(i=0;i<16;i++){         //0xc0 to 0xfc, step 4
//        d2s_test.SSI_write(0x202, 0xC0 + i * 4, false);
//    
//        for(j=0;j<128;j++){       //0 to 0x3ff
//            //Call SSI_read_Module(0x4 + 8 * j, True, 8);
//            //Call SSI_read_Module(0x6 + 8 * j, True, 8);
//            long k=i*128+j;
//            sprintf(cReadFlag, "readdata_i%d", k);
//            d2s_test.SSI_read(0x4 + 8 * j,cReadFlag,7);
//            
//            sprintf(cReadFlag, "readdata_q%d", k);
//            d2s_test.SSI_read(0x6 + 8 * j,cReadFlag,7);
//        }
//    }
    
    d2s::d2s_LABEL_END();
    
//    long long nCapData[4096] = {0};
//    int nsize = sizeof (nCapData) / sizeof (long long);
//    
//    FOREACH_ACTIVE_SITE(api) {
//
//        for (j = 0; j < 2048; j++) {
//            sprintf(cReadFlag, "readdata_i%d", j);
//            nCapData[j*2] = d2s_test.getReadValue(cReadFlag);
//            
//            sprintf(cReadFlag, "readdata_q%d", j);
//            nCapData[j*2+1] = d2s_test.getReadValue(cReadFlag);
//        }
//        
//        pReadValue->InitDataArray(site_id, nsize);
//        pReadValue->CopyElement(site_id, nCapData,nsize);
//    }
      
}

void WL_PD_BUF_ADC_C1_Cap_Module(CSiteLong *pReadValue) {
    
    long i;
    long j;
    char cReadFlag[32] = {"\0"};
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;    
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0xA0, false);
//    d2s_test.SSI_write(0x2F8, 0x1);    //PKTMEM_MODE_CFG
//
//    d2s_test.SSI_write(0x200, 0x2001, false);
//    d2s_test.SSI_write(0x202, 0x4, false);
//    d2s_test.SSI_write(0x2CC, 0x1);    //PKTMEM_SEL
//
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0xA0, false);
//    d2s_test.SSI_write(0x2F8, 0x11);   //PKTMEM_MODE_CFG
//
//    d2s_test.wait(0.001);
// 
//    d2s_test.SSI_write(0x200, 0x2001, false);
//    d2s_test.SSI_write(0x202, 0x4, false);
//    d2s_test.SSI_write(0x2CC, 0x0);    //PKTMEM_SEL
//
//    d2s_test.wait(0.00005);
    
    //2003C000~2003FFFF
    
    d2s_test.SSI_write(0x200, 0x2003, false);
    
    for(i=0;i<4;i++){         //0xc0 to 0xfc, step 4
        d2s_test.SSI_write(0x202, 0xC0 + i * 4, false);
    
        for(j=0;j<128;j++){       //0 to 0x3ff
            //Call SSI_read_Module(0x0 + 8 * j, True, 8);
            //Call SSI_read_Module(0x2 + 8 * j, True, 8);
            long k=i*128+j;
            sprintf(cReadFlag, "readdata_i%d", k);
            d2s_test.SSI_read(0x4 + 8 * j,cReadFlag,7);
            
            sprintf(cReadFlag, "readdata_q%d", k);
            d2s_test.SSI_read(0x6 + 8 * j,cReadFlag,7);
        }
    }
    
    d2s::d2s_LABEL_END();
    
    long long nCapData[1024] = {0};
    int nsize = sizeof (nCapData) / sizeof (long long);
    
    FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
        

        if (!d2s::isProductionMode()) {
            for (j = 0; j < 512; j++) {
                sprintf(cReadFlag, "readdata_i%d", j);
                nCapData[j*2] = d2s_test.getReadValue(cReadFlag).at(site_id);

                sprintf(cReadFlag, "readdata_q%d", j);
                nCapData[j*2+1] = d2s_test.getReadValue(cReadFlag).at(site_id);
            }
        } else {
            unsigned long data[16384];
            
            DIO_Capture(site_id,"DBB_GPIO7",data);

//            api->Get_capture_data("DBB_GPIO7", 0, 16384, data);

            for(int n = 0;n<16384;n+=16)
            {
                nCapData[n/16] = ConvertCapData(data+n,16);
            }
        }
        
        pReadValue->InitDataArray(site_id, nsize);
        pReadValue->CopyElement(site_id, nCapData,nsize);
	FOREACH_ACTIVESITE_END
      
}

void WL_PD_BUF_GPIO1_ADC_C1_Cap_Module(CSiteLong *pReadValue) {
    
    long i;
    long j;
    char cReadFlag[32] = {"\0"};
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x1);    //PKTMEM_MODE_CFG

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x1);    //PKTMEM_SEL

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x11);   //PKTMEM_MODE_CFG

    d2s_test.wait(0.001);
 
    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x0);    //PKTMEM_SEL

    d2s_test.wait(0.00005);
    
    //2003C000~2003FFFF
    
    d2s_test.SSI_write(0x200, 0x2003, false);
    
    for(i=0;i<1;i++){         //0xc0 to 0xfc, step 4
        d2s_test.SSI_write(0x202, 0xC0 + i * 4, false);
    
        for(j=0;j<64;j++){       //0 to 0x3ff
            //Call SSI_read_Module(0x0 + 8 * j, True, 8);
            //Call SSI_read_Module(0x2 + 8 * j, True, 8);
            long k=i*64+j;
            sprintf(cReadFlag, "readdata_i%d", k);
            d2s_test.SSI_read(0x4 + 8 * j,cReadFlag,7);
            
            sprintf(cReadFlag, "readdata_q%d", k);
            d2s_test.SSI_read(0x6 + 8 * j,cReadFlag,7);
        }
    }
    
    d2s::d2s_LABEL_END();
    
    long long nCapData[64] = {0};
    int nsize = sizeof (nCapData) / sizeof (long long);
    
//    FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
//        //int site_id = 0;
//
//        if (!d2s::isProductionMode()) {
//            for (j = 0; j < 32; j++) {
//                sprintf(cReadFlag, "readdata_i%d", j);
//                nCapData[j*2] = d2s_test.getReadValue(cReadFlag).at(site_id);
//
//                sprintf(cReadFlag, "readdata_q%d", j);
//                nCapData[j*2+1] = d2s_test.getReadValue(cReadFlag).at(site_id);
//            }
//        } else {
//            unsigned long data[1024];
//
//            DIO_Capture(site_id,"DBB_GPIO7",data);
//
////            api->Get_capture_data("DBB_GPIO7", 0, 1024, data);
//
//            for(int n = 0;n<1024;n+=16)
//            {
//                nCapData[n/16] = ConvertCapData(data+n,16);
//            }
//        }
//
//        pReadValue->InitDataArray(site_id, nsize);
//        pReadValue->CopyElement(site_id, nCapData,nsize);
//	FOREACH_ACTIVESITE_END

    if (!d2s::isProductionMode()) {
		FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
    		for (j = 0; j < 32; j++) {
    			sprintf(cReadFlag, "readdata_i%d", j);
    			nCapData[j*2] = d2s_test.getReadValue(cReadFlag).at(site_id);

    			sprintf(cReadFlag, "readdata_q%d", j);
    			nCapData[j*2+1] = d2s_test.getReadValue(cReadFlag).at(site_id);
    		}
        		pReadValue->InitDataArray(site_id, nsize);
        		pReadValue->CopyElement(site_id,nCapData,nsize);

		FOREACH_ACTIVESITE_END
		} else {

			unsigned long data[2048];

			auto CAP_Data = TheInst.Digital().PatEng().GetCaptureData("DBB_GPIO7");

			for (auto siteData : CAP_Data)
			{
				for (auto pinData : siteData.second)
				{
					int i=0;
					for (auto capData : pinData.second)
					{
						data[i] = capData.iECResult;
//						cout << "i :" << i << endl;
						i++;

					}
				}
//				cout << "hello_2" << endl;
				for(int n = 0;n<1024;n+=16)
				{
					nCapData[n/16] = ConvertCapData(data+n,16);
				}
//				cout << "hello_1" << endl;

				pReadValue->InitDataArray(siteData.first, nsize);
				pReadValue->CopyElement(siteData.first,nCapData,nsize);

//				cout << "hello" << endl;




			}

		}
      
}

void WL_DAC_SRC_DATA_module() {

    long i;
    long j;
    
    //Dim DAC_i_wave As New DspWave
    //Dim DAC_q_wave As New DspWave
    
    CWaveformData DAC_i_wave;
    CWaveformData DAC_q_wave;
    
    string pszCurrentPath = TheSoft.GetProgramPath();
    char szWaveformPath[MAX_PATH] = {0};
    sprintf(szWaveformPath, "%s\\Waveforms\\1151_M11_10p23294M_wave.txt", pszCurrentPath.c_str());
    DAC_i_wave.FileImport(szWaveformPath);
    DAC_q_wave.FileImport(szWaveformPath);
    
//    DAC_i_wave.FileImport("D:\\Hi1151A\\Program\\RF\\Hi1151AGNAV300_FTx2_S08F_T10_20201124\\Waveforms\\1151_M11_10p23294M_wave.txt");
//    DAC_q_wave.FileImport("D:\\Hi1151A\\Program\\RF\\Hi1151AGNAV300_FTx2_S08F_T10_20201124\\Waveforms\\1151_M11_10p23294M_wave.txt");
    
    //DAC_i_wave.FileImport ".\Waveforms\1151_M11_10p23294M_wave.txt", File_txt
    //DAC_q_wave.FileImport ".\Waveforms\1151_M11_10p23294M_wave.txt", File_txt
  
    //PKTMEM 2003C000~2003FFFF
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;    
    for(i=0;i<=15;i++){        //0xc0 to 0xfc, step 4
         
        for(j=0;j<=1023;j=j+4){   //0 to 0x3ff
//            d2s_test.SSI_write(0x204, DAC_q_wave.Element((i * 1024 + j); / 4);, false);
            d2s_test.SSI_write(0x204, DAC_q_wave[(i * 1024 + j) / 4], false);
            if(j==0){
                d2s_test.SSI_write(0x200, 0x2003, false);
                d2s_test.SSI_write(0x202, 0xC0 + i * 4, false);
            }
            
//            d2s_test.SSI_write(j, DAC_i_wave.Element((i * 1024 + j); / 4););
            d2s_test.SSI_write(j, DAC_i_wave[(i * 1024 + j) / 4]);
        }

    }

    d2s::d2s_LABEL_END();
}


void WL_ADC_C0_Setup_PVCal_Module(CSiteLong *pReadValue) {

    //File:  Hi1151 V200 Pilot ABB reg.xlsx
    //Sheet: WiFi_ADC_CH0
    //File time: 5/22/2017, update to this version.
    char cReadFlag[32] = {"\0"};
    
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x68, 0x0);     //S25
    d2s_test.SSI_write(0x6C, 0x0);     //S0B
    d2s_test.SSI_write(0x5C, 0x0);     //S20
    d2s_test.SSI_write(0x54, 0x0);     //S08&S00
    d2s_test.SSI_write(0x58, 0x0);     //muxreg
    d2s_test.SSI_write(0x60, 0x0);     //muxreg
    d2s_test.SSI_write(0x64, 0x0);     //muxreg
    d2s_test.SSI_write(0x0, 0x3);      //RF reg0
    d2s_test.SSI_write(0x4, 0x0);      //RF reg1
    d2s_test.SSI_write(0x8, 0x3);      //RF reg2
    d2s_test.SSI_write(0xC, 0x0);      //RF reg3
    d2s_test.SSI_write(0x10, 0x0);     //RF reg4
    d2s_test.SSI_write(0x14, 0x3400);      //RF reg5
    d2s_test.SSI_write(0x18, 0x3400);      //RF reg6

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0x350, 0x18A0);     //d_WL_ADC_REG0_c0<15:0>
    d2s_test.SSI_write(0x354, 0x4AA8);     //d_WL_ADC_REG1_c0<31:16>
    d2s_test.SSI_write(0x358, 0x81);       //d_WL_ADC_REG2_c0<47:32>
    d2s_test.SSI_write(0x35C, 0x2A00);      //d_WL_ADC_REG3_c0<63:48>  //2B00->2A00@2017-08-14 for V210,0b00->2b00@2017-06-23
    d2s_test.SSI_write(0x360, 0x0);        //d_WL_ADC_REG4_c0<69:64>

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x240, 0x111);      //ABB_WL_ADC_0CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x244, 0x1);    //ABB_WL_ADC_0CH_CTRL_REG
    
    d2s_test.wait(0.00005);
    
    d2s_test.SSI_write(0x244, 0x101);      //ABB_WL_ADC_0CH_CTRL_REG
    
    d2s_test.wait(0.0001);
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);  //CMU_RESERVE
    d2s_test.SSI_write(0x33C, 0x19B);      //CMU_RESERVE, 160Msps to get PV sensor. @2017-5-22
//    d2s_test.SSI_write(0x11C, 0x101);      //BBLDO set to 1.2V to get PV sensor. using external setup.

    //PV_Sensor
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    
    d2s_test.SSI_write(0x35C, 0x2A80);     //@2017-07-10
    d2s_test.wait(0.00008);
    
    d2s_test.SSI_write(0x35C, 0x2AA0);     //@2017-07-10
    d2s_test.wait(0.00008);
    
    d2s_test.SSI_write(0x35C, 0x2AC0);     //@2017-07-10
    d2s_test.wait(0.00008);

    d2s_test.SSI_write(0x35C, 0x2AE0);     //PV_Sensor en, @2017-5-22
    
    d2s_test.wait(0.00015);
    
    //Call SSI_read_Module(0x398, , 12);
    //Call SSI_read_Module(0x394, , 12);
    sprintf(cReadFlag, "readdata%d", 0);
    d2s_test.SSI_read(0x398,cReadFlag,9);
    sprintf(cReadFlag, "readdata%d", 1);
    d2s_test.SSI_read(0x394,cReadFlag,9);
    
    d2s_test.SSI_write(0x35C, 0x2A00);     //PV_Sensor disable,2B00->2A00@2017-08-14 for V210, @2017-5-22 //0b00->2b00@2017-06-23
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);  //CMU_RESERVE
    d2s_test.SSI_write(0x33C, 0x1B3);        //CMU_RESERVE, using 80Msps to do cal. @2017-5-22

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x20, 0x0);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0x24, 0x1);     //CH0_WL_AGCAL_COARSE_LOOP_SEL
    d2s_test.SSI_write(0x28, 0x1);     //CH0_WL_AGCAL_FINE_LOOP_SEL
    d2s_test.SSI_write(0x2C, 0x0);     //CH0_WL_AGCAL_COARSE_RANGE_SEL
    d2s_test.SSI_write(0x30, 0x3);     //CH0_WL_AGCAL_FINE_RANGE_SEL
    d2s_test.SSI_write(0x34, 0x0);     //CH0_WL_AGCAL_INVERSE
    d2s_test.SSI_write(0x38, 0x1);     //CH0_WL_AGCAL_DATA_SEL_A1
    d2s_test.SSI_write(0x3C, 0x2);     //CH0_WL_AGCAL_DATA_SEL_A2
    d2s_test.SSI_write(0x40, 0x4);     //CH0_WL_AGCAL_DATA_SEL_A3
    d2s_test.SSI_write(0x44, 0x8);     //CH0_WL_AGCAL_DATA_SEL_B1
    d2s_test.SSI_write(0x48, 0x10);    //CH0_WL_AGCAL_DATA_SEL_B2
    d2s_test.SSI_write(0x4C, 0x20);    //CH0_WL_AGCAL_DATA_SEL_B3
    d2s_test.SSI_write(0x50, 0x40);    //CH0_WL_AGCAL_DATA_SEL_C1
    d2s_test.SSI_write(0x54, 0x80);    //CH0_WL_AGCAL_DATA_SEL_C2
    d2s_test.SSI_write(0x58, 0x100);   //CH0_WL_AGCAL_DATA_SEL_C3
    d2s_test.SSI_write(0x68, 0x0);     //CH0_FIRST_COM_SEL
    d2s_test.SSI_write(0x5C, 0x0);     //CH0_WL_AGCAL_CTRL_SEL

    d2s::d2s_LABEL_END();
    
    long long nCapData[2] = {0};    
    int nsize = sizeof (nCapData) / sizeof (long long);
    //int site_id = 0;


    FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)

        sprintf(cReadFlag, "readdata%d", 0);
        nCapData[0]=d2s_test.getReadValue(cReadFlag).at(site_id);

        cout << "---------------start--------------------"<<endl;
        cout << "nCapData[0]:"<<nCapData[0] << endl;
        cout << "---------------stop--------------------------"<<endl;
        sprintf(cReadFlag, "readdata%d", 1);

        nCapData[1]=d2s_test.getReadValue(cReadFlag).at(site_id);
        cout << "---------------start--------------------------"<<endl;
        cout << "nCapData[1]:"<<nCapData[1] << endl;
        cout << "----------------stop--------------------------"<<endl;
        pReadValue->InitDataArray(site_id, nsize);
        pReadValue->CopyElement(site_id, nCapData,nsize);
	FOREACH_ACTIVESITE_END
}


void WL_ADC_C0_Setup_PVCal_LV_Module(CSiteLong *pReadValue) {

    //File:  Hi1151 V200 Pilot ABB reg.xlsx
    //Sheet: WiFi_ADC_CH0
    //File time: 5/22/2017, update to this version.
    char cReadFlag[32] = {"\0"};
    
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x68, 0x0);     //S25
    d2s_test.SSI_write(0x6C, 0x0);     //S0B
    d2s_test.SSI_write(0x5C, 0x0);     //S20
    d2s_test.SSI_write(0x54, 0x0);     //S08&S00
    d2s_test.SSI_write(0x58, 0x0);     //muxreg
    d2s_test.SSI_write(0x60, 0x0);     //muxreg
    d2s_test.SSI_write(0x64, 0x0);     //muxreg
    d2s_test.SSI_write(0x0, 0x3);      //RF reg0
    d2s_test.SSI_write(0x4, 0x0);      //RF reg1
    d2s_test.SSI_write(0x8, 0x3);      //RF reg2
    d2s_test.SSI_write(0xC, 0x0);      //RF reg3
    d2s_test.SSI_write(0x10, 0x0);     //RF reg4
    d2s_test.SSI_write(0x14, 0x3400);      //RF reg5
    d2s_test.SSI_write(0x18, 0x3400);      //RF reg6

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0x350, 0x18A0);     //d_WL_ADC_REG0_c0<15:0>
    d2s_test.SSI_write(0x354, 0x4AA8);     //d_WL_ADC_REG1_c0<31:16>
    d2s_test.SSI_write(0x358, 0x81);       //d_WL_ADC_REG2_c0<47:32>
    d2s_test.SSI_write(0x35C, 0x2800);      //d_WL_ADC_REG3_c0<63:48> 0B00->2800@2017-08-14 for V210
    d2s_test.SSI_write(0x360, 0x0);        //d_WL_ADC_REG4_c0<69:64>

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x240, 0x111);      //ABB_WL_ADC_0CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x244, 0x1);    //ABB_WL_ADC_0CH_CTRL_REG
    
    d2s_test.wait(0.00005);
    
    d2s_test.SSI_write(0x244, 0x101);      //ABB_WL_ADC_0CH_CTRL_REG
    
    d2s_test.wait(0.0001);
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);  //CMU_RESERVE
    d2s_test.SSI_write(0x33C, 0x19B);      //CMU_RESERVE, 160Msps to get PV sensor. @2017-5-22
//    d2s_test.SSI_write(0x11C, 0x101);      //BBLDO set to 1.2V to get PV sensor. using external setup.

    //PV_Sensor
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    
    d2s_test.SSI_write(0x35C, 0x2880);     //@2017-07-10
    d2s_test.wait(0.00008);
    
    d2s_test.SSI_write(0x35C, 0x28A0);     //@2017-07-10
    d2s_test.wait(0.00008);
    
    d2s_test.SSI_write(0x35C, 0x28C0);     //@2017-07-10
    d2s_test.wait(0.00008);
    
    d2s_test.SSI_write(0x35C, 0x28E0);     //PV_Sensor en, @2017-5-22
    
    d2s_test.wait(0.00015);
    
    //Call SSI_read_Module(0x398, , 12);
    //Call SSI_read_Module(0x394, , 12);
    
    sprintf(cReadFlag, "readdata%d", 0);
    d2s_test.SSI_read(0x398,cReadFlag,9);
    sprintf(cReadFlag, "readdata%d", 1);
    d2s_test.SSI_read(0x394,cReadFlag,9);
 
    d2s_test.SSI_write(0x35C, 0x2800);     //0B00->2800@2017-08-14 for V210, PV_Sensor disable,  @2017-5-22
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);  //CMU_RESERVE
    d2s_test.SSI_write(0x33C, 0x1B3);        //CMU_RESERVE, using 80Msps to do cal. @2017-5-22

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x20, 0x0);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0x24, 0x1);     //CH0_WL_AGCAL_COARSE_LOOP_SEL
    d2s_test.SSI_write(0x28, 0x1);     //CH0_WL_AGCAL_FINE_LOOP_SEL
    d2s_test.SSI_write(0x2C, 0x0);     //CH0_WL_AGCAL_COARSE_RANGE_SEL
    d2s_test.SSI_write(0x30, 0x3);     //CH0_WL_AGCAL_FINE_RANGE_SEL
    d2s_test.SSI_write(0x34, 0x0);     //CH0_WL_AGCAL_INVERSE
    d2s_test.SSI_write(0x38, 0x1);     //CH0_WL_AGCAL_DATA_SEL_A1
    d2s_test.SSI_write(0x3C, 0x2);     //CH0_WL_AGCAL_DATA_SEL_A2
    d2s_test.SSI_write(0x40, 0x4);     //CH0_WL_AGCAL_DATA_SEL_A3
    d2s_test.SSI_write(0x44, 0x8);     //CH0_WL_AGCAL_DATA_SEL_B1
    d2s_test.SSI_write(0x48, 0x10);    //CH0_WL_AGCAL_DATA_SEL_B2
    d2s_test.SSI_write(0x4C, 0x20);    //CH0_WL_AGCAL_DATA_SEL_B3
    d2s_test.SSI_write(0x50, 0x40);    //CH0_WL_AGCAL_DATA_SEL_C1
    d2s_test.SSI_write(0x54, 0x80);    //CH0_WL_AGCAL_DATA_SEL_C2
    d2s_test.SSI_write(0x58, 0x100);   //CH0_WL_AGCAL_DATA_SEL_C3
    d2s_test.SSI_write(0x68, 0x0);     //CH0_FIRST_COM_SEL
    d2s_test.SSI_write(0x5C, 0x0);     //CH0_WL_AGCAL_CTRL_SEL

    d2s::d2s_LABEL_END();
    
    long long nCapData[2] = {0};
    long long dwResult = 0;
    int nsize = sizeof (nCapData) / sizeof (long long);
    FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)

        sprintf(cReadFlag, "readdata%d", 0);
        nCapData[0]=d2s_test.getReadValue(cReadFlag).at(site_id);

        sprintf(cReadFlag, "readdata%d", 1);
        nCapData[1]=d2s_test.getReadValue(cReadFlag).at(site_id);

        pReadValue->InitDataArray(site_id, nsize);
        pReadValue->CopyElement(site_id, nCapData,nsize);
	FOREACH_ACTIVESITE_END
}


void WL_ADC_C0_Setup_PVCal_LV1_Module(CSiteLong *pReadValue) {

    //File:  Hi1151 V200 Pilot ABB reg.xlsx
    //Sheet: WiFi_ADC_CH0
    //File time: 5/22/2017, update to this version.
    char cReadFlag[32] = {"\0"};
    
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x68, 0x0);     //S25
    d2s_test.SSI_write(0x6C, 0x0);     //S0B
    d2s_test.SSI_write(0x5C, 0x0);     //S20
    d2s_test.SSI_write(0x54, 0x0);     //S08&S00
    d2s_test.SSI_write(0x58, 0x0);     //muxreg
    d2s_test.SSI_write(0x60, 0x0);     //muxreg
    d2s_test.SSI_write(0x64, 0x0);     //muxreg
    d2s_test.SSI_write(0x0, 0x3);      //RF reg0
    d2s_test.SSI_write(0x4, 0x0);      //RF reg1
    d2s_test.SSI_write(0x8, 0x3);      //RF reg2
    d2s_test.SSI_write(0xC, 0x0);      //RF reg3
    d2s_test.SSI_write(0x10, 0x0);     //RF reg4
    d2s_test.SSI_write(0x14, 0x3400);      //RF reg5
    d2s_test.SSI_write(0x18, 0x3400);      //RF reg6

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0x350, 0x18A0);     //d_WL_ADC_REG0_c0<15:0>
    d2s_test.SSI_write(0x354, 0x4AA8);     //d_WL_ADC_REG1_c0<31:16>
    d2s_test.SSI_write(0x358, 0x81);       //d_WL_ADC_REG2_c0<47:32>
    d2s_test.SSI_write(0x35C, 0xA00);      //d_WL_ADC_REG3_c0<63:48>  //2B00->A00@2017-08-14 for V210,SS corr
    d2s_test.SSI_write(0x360, 0x0);        //d_WL_ADC_REG4_c0<69:64>

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x240, 0x111);      //ABB_WL_ADC_0CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x244, 0x1);    //ABB_WL_ADC_0CH_CTRL_REG
    
    d2s_test.wait(0.00005);
    
    d2s_test.SSI_write(0x244, 0x101);      //ABB_WL_ADC_0CH_CTRL_REG
    
    d2s_test.wait(0.0001);
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);  //CMU_RESERVE
    d2s_test.SSI_write(0x33C, 0x19B);      //CMU_RESERVE, 160Msps to get PV sensor. @2017-5-22
//    d2s_test.SSI_write(0x11C, 0x101);      //BBLDO set to 1.2V to get PV sensor. using external setup.

    //PV_Sensor
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    
    d2s_test.SSI_write(0x35C, 0xA80);     //@2017-07-10
    d2s_test.wait(0.00008);
    
    d2s_test.SSI_write(0x35C, 0xAA0);     //@2017-07-10
    d2s_test.wait(0.00008);
    
    d2s_test.SSI_write(0x35C, 0xAC0);     //@2017-07-10
    d2s_test.wait(0.00008);

    d2s_test.SSI_write(0x35C, 0xAE0);     //PV_Sensor en, @2017-5-22
    
    d2s_test.wait(0.00015);
    
    //Call SSI_read_Module(0x398, , 12);
    //Call SSI_read_Module(0x394, , 12);
    sprintf(cReadFlag, "readdata%d", 0);
    d2s_test.SSI_read(0x398,cReadFlag,9);
    sprintf(cReadFlag, "readdata%d", 1);
    d2s_test.SSI_read(0x394,cReadFlag,9);
    
    d2s_test.SSI_write(0x35C, 0xA00);     //PV_Sensor disable,2B00->A00@2017-08-14 for V210, @2017-5-22 //0b00->2b00@2017-06-23
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);  //CMU_RESERVE
    d2s_test.SSI_write(0x33C, 0x1B3);        //CMU_RESERVE, using 80Msps to do cal. @2017-5-22

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x20, 0x0);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0x24, 0x1);     //CH0_WL_AGCAL_COARSE_LOOP_SEL
    d2s_test.SSI_write(0x28, 0x1);     //CH0_WL_AGCAL_FINE_LOOP_SEL
    d2s_test.SSI_write(0x2C, 0x0);     //CH0_WL_AGCAL_COARSE_RANGE_SEL
    d2s_test.SSI_write(0x30, 0x3);     //CH0_WL_AGCAL_FINE_RANGE_SEL
    d2s_test.SSI_write(0x34, 0x0);     //CH0_WL_AGCAL_INVERSE
    d2s_test.SSI_write(0x38, 0x1);     //CH0_WL_AGCAL_DATA_SEL_A1
    d2s_test.SSI_write(0x3C, 0x2);     //CH0_WL_AGCAL_DATA_SEL_A2
    d2s_test.SSI_write(0x40, 0x4);     //CH0_WL_AGCAL_DATA_SEL_A3
    d2s_test.SSI_write(0x44, 0x8);     //CH0_WL_AGCAL_DATA_SEL_B1
    d2s_test.SSI_write(0x48, 0x10);    //CH0_WL_AGCAL_DATA_SEL_B2
    d2s_test.SSI_write(0x4C, 0x20);    //CH0_WL_AGCAL_DATA_SEL_B3
    d2s_test.SSI_write(0x50, 0x40);    //CH0_WL_AGCAL_DATA_SEL_C1
    d2s_test.SSI_write(0x54, 0x80);    //CH0_WL_AGCAL_DATA_SEL_C2
    d2s_test.SSI_write(0x58, 0x100);   //CH0_WL_AGCAL_DATA_SEL_C3
    d2s_test.SSI_write(0x68, 0x0);     //CH0_FIRST_COM_SEL
    d2s_test.SSI_write(0x5C, 0x0);     //CH0_WL_AGCAL_CTRL_SEL

    d2s::d2s_LABEL_END();
    
    long long nCapData[2] = {0};
    long long dwResult = 0;
    int nsize = sizeof (nCapData) / sizeof (long long);
    FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)

        sprintf(cReadFlag, "readdata%d", 0);
        nCapData[0]=d2s_test.getReadValue(cReadFlag).at(site_id);
        sprintf(cReadFlag, "readdata%d", 1);
        nCapData[1]=d2s_test.getReadValue(cReadFlag).at(site_id);
        
        pReadValue->InitDataArray(site_id, nsize);
        pReadValue->CopyElement(site_id, nCapData,nsize);
	FOREACH_ACTIVESITE_END
}


void WL_ADC_C0C1_Setup_CalStatus_Module(CSiteLong *pReadValue) {
    
    char cReadFlag[32] = {"\0"};
    
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x0, 0x0);      //RF reg0
    d2s_test.SSI_write(0x4, 0x0);      //RF reg1
    d2s_test.SSI_write(0x8, 0x0);      //RF reg2
    d2s_test.SSI_write(0xC, 0x2);      //RF reg3
    d2s_test.SSI_write(0x10, 0x2);     //RF reg4
    d2s_test.SSI_write(0x14, 0x7FF0);   //RF reg5
    d2s_test.SSI_write(0x18, 0x7FF0);   //RF reg6
    
    // Comparater Cal 1
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x20, 0x0);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0x20, 0x1);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
    d2s_test.SSI_write(0xEC, 0x1);     //CH1_WL_AGCAL_EN
    for(int i = 0;i<100;i++){
    	d2s_test.wait(0.0002);
    }
//    d2s_test.wait(0.02);
    sprintf(cReadFlag, "readdata%d", 0);
    d2s_test.SSI_read(0xE8,cReadFlag,9);
    sprintf(cReadFlag, "readdata%d", 1);
    d2s_test.SSI_read(0x1B4,cReadFlag,9);
    
    //Call SSI_read_Module(0xE8, True, 12);    //WL_ADC0_AGCAL_NUM_ONE_ADD_DONE
    //Call SSI_read_Module(0x1B4, True, 12);    //WL_ADC1_AGCAL_NUM_ONE_ADD_DONE

    // Comparater Cal 2
    
    d2s_test.SSI_write(0x20, 0x0);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0x20, 0x1);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
    d2s_test.SSI_write(0xEC, 0x1);     //CH1_WL_AGCAL_EN
    for(int i = 0;i<100;i++)
    	d2s_test.wait(0.00008);
    sprintf(cReadFlag, "readdata%d", 2);
    d2s_test.SSI_read(0xE8,cReadFlag,9);
    sprintf(cReadFlag, "readdata%d", 3);
    d2s_test.SSI_read(0x1B4,cReadFlag,9);
    //Call SSI_read_Module(0xE8, True, 12);    //WL_ADC0_AGCAL_NUM_ONE_ADD_DONE
    //Call SSI_read_Module(0x1B4, True, 12);    //WL_ADC1_AGCAL_NUM_ONE_ADD_DONE
    
    // Comparater Cal 3
    
    d2s_test.SSI_write(0x20, 0x0);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0x20, 0x1);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
    d2s_test.SSI_write(0xEC, 0x1);     //CH1_WL_AGCAL_EN
    for(int i=0;i<100;i++)
        d2s_test.wait(0.00008);
    sprintf(cReadFlag, "readdata%d", 4);
    d2s_test.SSI_read(0xE8,cReadFlag,9);
    sprintf(cReadFlag, "readdata%d", 5);
    d2s_test.SSI_read(0x1B4,cReadFlag,9);
    //Call SSI_read_Module(0xE8, True, 12);    //WL_ADC0_AGCAL_NUM_ONE_ADD_DONE
    //Call SSI_read_Module(0x1B4, True, 12);    //WL_ADC1_AGCAL_NUM_ONE_ADD_DONE
    
    // Comparater Cal 4
    
    d2s_test.SSI_write(0x20, 0x0);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0x20, 0x1);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
    d2s_test.SSI_write(0xEC, 0x1);     //CH1_WL_AGCAL_EN
    for(int i=0;i<100;i++)
        d2s_test.wait(0.00008);
    sprintf(cReadFlag, "readdata%d", 6);
    d2s_test.SSI_read(0xE8,cReadFlag,9);
    sprintf(cReadFlag, "readdata%d", 7);
    d2s_test.SSI_read(0x1B4,cReadFlag,9);
    //Call SSI_read_Module(0xE8, True, 12);    //WL_ADC0_AGCAL_NUM_ONE_ADD_DONE
    //Call SSI_read_Module(0x1B4, True, 12);    //WL_ADC1_AGCAL_NUM_ONE_ADD_DONE
    
    // Comparater Cal 5
    
    d2s_test.SSI_write(0x20, 0x0);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0x20, 0x1);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
    d2s_test.SSI_write(0xEC, 0x1);     //CH1_WL_AGCAL_EN
    for(int i=0;i<100;i++)
        d2s_test.wait(0.00008);
    sprintf(cReadFlag, "readdata%d", 8);
    d2s_test.SSI_read(0xE8,cReadFlag,9);
    sprintf(cReadFlag, "readdata%d", 9);
    d2s_test.SSI_read(0x1B4,cReadFlag,9);
    //Call SSI_read_Module(0xE8, True, 12);    //WL_ADC0_AGCAL_NUM_ONE_ADD_DONE
    //Call SSI_read_Module(0x1B4, True, 12);    //WL_ADC1_AGCAL_NUM_ONE_ADD_DONE
    
    // Comparater Cal 6
    
    d2s_test.SSI_write(0x20, 0x0);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0x20, 0x1);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
    d2s_test.SSI_write(0xEC, 0x1);     //CH1_WL_AGCAL_EN
    for(int i=0;i<100;i++)
        d2s_test.wait(0.00008);
    sprintf(cReadFlag, "readdata%d", 10);
    d2s_test.SSI_read(0xE8,cReadFlag,9);
    sprintf(cReadFlag, "readdata%d", 11);
    d2s_test.SSI_read(0x1B4,cReadFlag,9);
    //Call SSI_read_Module(0xE8, True, 12);    //WL_ADC0_AGCAL_NUM_ONE_ADD_DONE
    //Call SSI_read_Module(0x1B4, True, 12);    //WL_ADC1_AGCAL_NUM_ONE_ADD_DONE

    d2s_test.SSI_write(0x20, 0x0);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
    
    d2s::d2s_LABEL_END();
    
    long long nCapData[12] = {0};
    int nsize = sizeof (nCapData) / sizeof (long long);
//    FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
//
//
//        if (!d2s::isProductionMode()) {
//            for(int RegNum=0;RegNum<12;RegNum++)
//            {
//                sprintf(cReadFlag, "readdata%d", RegNum);
//                nCapData[RegNum]=d2s_test.getReadValue(cReadFlag).at(site_id);
//            }
//        } else {
//            unsigned long data[192];
//
//            DIO_Capture(site_id,"DBB_GPIO7",data);
////            api->Get_capture_data("DBB_GPIO7", 0, 192, data);
//
//            for(int n = 0;n<192;n+=16)
//            {
//                nCapData[n/16] = ConvertCapData(data+n,16);
//            }
//        }
//
//        pReadValue->InitDataArray(site_id, nsize);
//        pReadValue->CopyElement(site_id, nCapData,nsize);
//
//	FOREACH_ACTIVESITE_END


    if (!d2s::isProductionMode()) {
    		FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
		for(int RegNum=0;RegNum<12;RegNum++)
		{
			sprintf(cReadFlag, "readdata%d", RegNum);
			nCapData[RegNum]=d2s_test.getReadValue(cReadFlag).at(site_id);
		}
    		pReadValue->InitDataArray(site_id, nsize);
    		pReadValue->CopyElement(site_id,nCapData,nsize);

//    		for(int i=0;i<256;i++)
//    		{
//    			cout << nCapData[i] << "\t";
//
//    		}
//    		cout << endl;

    	FOREACH_ACTIVESITE_END
    	} else {

    		unsigned long data[192];

    		auto CAP_Data = TheInst.Digital().PatEng().GetCaptureData("DBB_GPIO7");

    		for (auto siteData : CAP_Data)
    		{

    			for (auto pinData : siteData.second)
    			{
    				int i=0;
    				for (auto capData : pinData.second)
    				{

    					data[i] = capData.iECResult;
//    					cout <<  data[i] ;
    					i++;

    				}


//    				cout << endl;

    			}



    			for(int n = 0;n<192;n+=16)
    			{
    				nCapData[n/16] = ConvertCapData(data+n,16);
//    				cout << nCapData[n/16]<< "\t";
    			}
//    			cout << endl;
    			pReadValue->InitDataArray(siteData.first, nsize);
    			pReadValue->CopyElement(siteData.first,nCapData,nsize);
    		}
    	}






}


void WL_ADC_C0_Setup_CalStatus_Module(CSiteLong *pReadValue) {
    
    char cReadFlag[32] = {"\0"};
    
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    // Comparater Cal 1
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x20, 0x0);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0x20, 0x1);     //CH0_WL_AGCAL_EN
    for(int i=0;i<100;i++)
    d2s_test.wait(0.0002);
    sprintf(cReadFlag, "readdata%d", 0);
    d2s_test.SSI_read(0xE8,cReadFlag,9);

    //Call SSI_read_Module(0xE8, True, 12);    //WL_ADC0_AGCAL_NUM_ONE_ADD_DONE

    // Comparater Cal 2
    
    d2s_test.SSI_write(0x20, 0x0);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0x20, 0x1);     //CH0_WL_AGCAL_EN
    for(int i=0;i<100;i++)
        d2s_test.wait(0.00008);
    sprintf(cReadFlag, "readdata%d", 1);
    d2s_test.SSI_read(0xE8,cReadFlag,9);
    //Call SSI_read_Module(0xE8, True, 12);    //WL_ADC0_AGCAL_NUM_ONE_ADD_DONE
    
    // Comparater Cal 3
    
    d2s_test.SSI_write(0x20, 0x0);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0x20, 0x1);     //CH0_WL_AGCAL_EN
    for(int i=0;i<100;i++)
        d2s_test.wait(0.00008);
    sprintf(cReadFlag, "readdata%d", 2);
    d2s_test.SSI_read(0xE8,cReadFlag,9);
    //Call SSI_read_Module(0xE8, True, 12);    //WL_ADC0_AGCAL_NUM_ONE_ADD_DONE
    
    // Comparater Cal 4
    
    d2s_test.SSI_write(0x20, 0x0);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0x20, 0x1);     //CH0_WL_AGCAL_EN
    for(int i=0;i<100;i++)
        d2s_test.wait(0.00008);
    sprintf(cReadFlag, "readdata%d", 3);
    d2s_test.SSI_read(0xE8,cReadFlag,9);  
    //Call SSI_read_Module(0xE8, True, 12);    //WL_ADC0_AGCAL_NUM_ONE_ADD_DONE
    
    // Comparater Cal 5
    
    d2s_test.SSI_write(0x20, 0x0);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0x20, 0x1);     //CH0_WL_AGCAL_EN
    for(int i=0;i<100;i++)
        d2s_test.wait(0.00008);
    //Call SSI_read_Module(0xE8, True, 12);    //WL_ADC0_AGCAL_NUM_ONE_ADD_DONE
    sprintf(cReadFlag, "readdata%d", 4);
    d2s_test.SSI_read(0xE8,cReadFlag,9);    
    // Comparater Cal 6
    
    d2s_test.SSI_write(0x20, 0x0);     //CH0_WL_AGCAL_EN
    d2s_test.SSI_write(0x20, 0x1);     //CH0_WL_AGCAL_EN
    for(int i=0;i<100;i++)
        d2s_test.wait(0.00008);
    //Call SSI_read_Module(0xE8, True, 12);    //WL_ADC0_AGCAL_NUM_ONE_ADD_DONE
    sprintf(cReadFlag, "readdata%d", 5);
    d2s_test.SSI_read(0xE8,cReadFlag,9);
    //Read ABB ADC Registers @2017/6/19
    
    sprintf(cReadFlag, "readdata%d", 6);
    d2s_test.SSI_read(0x6C,cReadFlag,9);
    
    sprintf(cReadFlag, "readdata%d", 7);
    d2s_test.SSI_read(0x70,cReadFlag,9);
    
    sprintf(cReadFlag, "readdata%d", 8);
    d2s_test.SSI_read(0x74,cReadFlag,9);
    
    sprintf(cReadFlag, "readdata%d", 9);
    d2s_test.SSI_read(0x78,cReadFlag,9);
    
    sprintf(cReadFlag, "readdata%d", 10);
    d2s_test.SSI_read(0x7C,cReadFlag,9);
    
    sprintf(cReadFlag, "readdata%d", 11);
    d2s_test.SSI_read(0x80,cReadFlag,9);
    //Call SSI_read_Module(0x6C, True, 12);    //WL_ADC0_AGCAL_COARSE_CALIP_A1
    //Call SSI_read_Module(0x70, True, 12);    //WL_ADC0_AGCAL_fine_CALIP_A1
    //Call SSI_read_Module(0x74, True, 12);    //WL_ADC0_AGCAL_COARSE_CALIP_A2
    //Call SSI_read_Module(0x78, True, 12);    //WL_ADC0_AGCAL_fine_CALIP_A2
    //Call SSI_read_Module(0x7C, True, 12);    //WL_ADC0_AGCAL_COARSE_CALIP_A3
    //Call SSI_read_Module(0x80, True, 12);    //WL_ADC0_AGCAL_fine_CALIP_A3
    
    d2s_test.SSI_write(0x20, 0x0);     //CH0_WL_AGCAL_EN
    
    d2s::d2s_LABEL_END();
    
    long long nCapData[12] = {0};
    long long dwResult = 0;
//    CSiteLong ReadValue;
    int nsize = sizeof (nCapData) / sizeof (long long);
//    FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
//
//
//        if (!d2s::isProductionMode()) {
//            for(int RegNum=0;RegNum<12;RegNum++)
//            {
//                sprintf(cReadFlag, "readdata%d", RegNum);
//                nCapData[RegNum]=d2s_test.getReadValue(cReadFlag).at(site_id);
//            }
//        } else {
//            unsigned long data[192];
//
//            DIO_Capture(site_id,"DBB_GPIO7",data);
////            api->Get_capture_data("DBB_GPIO7", 0, 192, data);
//
//            for(int n = 0;n<192;n+=16)
//            {
//                nCapData[n/16] = ConvertCapData(data+n,16);
//            }
//        }
//
//        pReadValue->InitDataArray(site_id, nsize);
//        pReadValue->CopyElement(site_id, nCapData,nsize);
//
//	FOREACH_ACTIVESITE_END


    if (!d2s::isProductionMode()) {
		FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
			for(int RegNum=0;RegNum<12;RegNum++)
			{
				sprintf(cReadFlag, "readdata%d", RegNum);
				nCapData[RegNum]=d2s_test.getReadValue(cReadFlag).at(site_id);
			}
			pReadValue->InitDataArray(site_id, nsize);
			pReadValue->CopyElement(site_id,nCapData,nsize);

    	FOREACH_ACTIVESITE_END
    	} else {

    		unsigned long data[192];

    		auto CAP_Data = TheInst.Digital().PatEng().GetCaptureData("DBB_GPIO7");

    		for (auto siteData : CAP_Data)
    		{
    			for (auto pinData : siteData.second)
    			{
    				int i=0;
    				for (auto capData : pinData.second)
    				{
    					data[i] = capData.iECResult;
    					i++;

    				}
    			}
    			for(int n = 0;n<192;n+=16)
    			{
    				nCapData[n/16] = ConvertCapData(data+n,16);
    			}

    			pReadValue->InitDataArray(siteData.first, nsize);
    			pReadValue->CopyElement(siteData.first,nCapData,nsize);
    		}

    	}

}


void WL_ADC_C0_Setup_CapCal_Module(CSiteLong *pReadValue) {
    
    char cReadFlag[32] = {"\0"};
    
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0x354, 0x4AA0);     //d_WL_ADC_REG1_c0<31:16>
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x1B8, 0x0);    //WL_CAP_EN
    d2s_test.SSI_write(0x1E0, 0x1);    //WL_CAP_MODE
    d2s_test.SSI_write(0x1BC, 0x1);    //WL_CAP_WAIT_CYCLE_SEL
    d2s_test.SSI_write(0x1D8, 0x1);    //WL_CAP_INDEX_SOFT
    d2s_test.SSI_write(0x1DC, 0x1);    //WL_CAP_PN_CAPSTAT
    d2s_test.SSI_write(0x1C0, 0x0);    //WL_CAP_PN_INDEX_C1
    d2s_test.SSI_write(0x1C4, 0x21);   //WL_CAP_PN_INDEX_C2
    d2s_test.SSI_write(0x1C8, 0x22);   //WL_CAP_PN_INDEX_C4
    d2s_test.SSI_write(0x1CC, 0x24);   //WL_CAP_PN_INDEX_C8
    d2s_test.SSI_write(0x1D0, 0x28);   //WL_CAP_PN_INDEX_C16
    d2s_test.SSI_write(0x1D4, 0x30);   //WL_CAP_PN_INDEX_C32
    d2s_test.SSI_write(0x1B8, 0x1);    //WL_CAP_EN

    d2s_test.wait(0.001);
    sprintf(cReadFlag, "readdata%d", 0);
    d2s_test.SSI_read(0x1FC,cReadFlag,9);
        
    sprintf(cReadFlag, "readdata%d", 1);
    d2s_test.SSI_read(0x200,cReadFlag,9);
        
    sprintf(cReadFlag, "readdata%d", 2);
    d2s_test.SSI_read(0x204,cReadFlag,9);
        
    sprintf(cReadFlag, "readdata%d", 3);
    d2s_test.SSI_read(0x208,cReadFlag,9);
        
    sprintf(cReadFlag, "readdata%d", 4);
    d2s_test.SSI_read(0x20C,cReadFlag,9);
        
    sprintf(cReadFlag, "readdata%d", 5);
    d2s_test.SSI_read(0x210,cReadFlag,9);
    
    sprintf(cReadFlag, "readdata%d", 6);
    d2s_test.SSI_read(0x214,cReadFlag,9);
    
    d2s_test.SSI_write(0x1B8, 0x0);

    d2s::d2s_LABEL_END();
    
    long long nCapData[7] = {0};
    int nsize = sizeof (nCapData) / sizeof (long long);
//    FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
//
//
//        if (!d2s::isProductionMode()) {
//            for(int RegNum=0;RegNum<7;RegNum++)
//            {
//                sprintf(cReadFlag, "readdata%d", RegNum);
//                nCapData[RegNum]=d2s_test.getReadValue(cReadFlag).at(site_id);
//                cout << "----------------start------------------"<< endl;
//                cout << "nCapData[RegNum]:" << nCapData[RegNum] << endl;
//                cout << "----------------stop------------------"<< endl;
//            }
//        } else {
//            unsigned long data[112];
//
//            DIO_Capture(site_id,"DBB_GPIO7",data);
//
//
//            for(int n = 0;n<112;n+=16)
//            {
//                nCapData[n/16] = ConvertCapData(data+n,16);
//            }
//        }
//        pReadValue->InitDataArray(site_id, nsize);
//        pReadValue->CopyElement(site_id, nCapData,nsize);

//	FOREACH_ACTIVESITE_END

	if (!d2s::isProductionMode()) {
		FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
		for(int RegNum=0;RegNum<7;RegNum++)
		{
			sprintf(cReadFlag, "readdata%d", RegNum);
			nCapData[RegNum]=d2s_test.getReadValue(cReadFlag).at(site_id);
//			cout << "----------------start------------------"<< endl;
//			cout << "nCapData[RegNum]:" << nCapData[RegNum] << endl;
//			cout << "----------------stop------------------"<< endl;
		}
		pReadValue->InitDataArray(site_id, nsize);
		pReadValue->CopyElement(site_id,nCapData,nsize);

	FOREACH_ACTIVESITE_END
	} else {

		unsigned long data[112];

		auto CAP_Data = TheInst.Digital().PatEng().GetCaptureData("DBB_GPIO7");

		for (auto siteData : CAP_Data)
		{
			for (auto pinData : siteData.second)
			{
				int i=0;
				for (auto capData : pinData.second)
				{
					data[i] = capData.iECResult;
					i++;

				}
			}
			for(int n = 0;n<112;n+=16)
			{
				nCapData[n/16] = ConvertCapData(data+n,16);
			}

			pReadValue->InitDataArray(siteData.first, nsize);
			pReadValue->CopyElement(siteData.first,nCapData,nsize);
		}

	}

}


void WL_ADC_C1_Setup_PVCal_Module(map<int, long long> capture_data0,map<int, long long> capture_data1) {

    //File:  Hi1151 V200 Pilot ABB reg.xlsx
    //Sheet: WiFi_ADC_CH1
    //File time: 5/15/2017, update to this version.
    
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x68, 0x0);     //S25
    d2s_test.SSI_write(0x6C, 0x0);     //S0B
    d2s_test.SSI_write(0x5C, 0x0);     //S20
    d2s_test.SSI_write(0x58, 0x0);     //S18&S10
    d2s_test.SSI_write(0x54, 0x0);     //mux reg
    d2s_test.SSI_write(0x60, 0x0);     //mux reg
    d2s_test.SSI_write(0x64, 0x0);     //mux reg
    d2s_test.SSI_write(0x0, 0x3);      //RF reg0
    d2s_test.SSI_write(0x4, 0x0);      //RF reg1
    d2s_test.SSI_write(0x8, 0x3);      //RF reg2
    d2s_test.SSI_write(0xC, 0x0);      //RF reg3
    d2s_test.SSI_write(0x10, 0x0);     //RF reg4
    d2s_test.SSI_write(0x14, 0x3400);      //RF reg5
    d2s_test.SSI_write(0x18, 0x3400);      //RF reg6

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0x364, 0x18A0);     //d_WL_ADC_REG0_c1<15:0>
    d2s_test.SSI_write(0x368, 0x4AA8);     //d_WL_ADC_REG1_c1<31:16>
    d2s_test.SSI_write(0x36C, 0x81);       //d_WL_ADC_REG2_c1<47:32>
    d2s_test.SSI_write(0x370, 0x2A00);      //d_WL_ADC_REG3_c1<63:48> 2B00->2A00@2017-08-14forV210,0b00->2b00@2017-06-23
    d2s_test.SSI_write(0x374, 0x0);        //d_WL_ADC_REG4_c1<69:64>

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x258, 0x111);      //ABB_WL_ADC_1CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x25C, 0x1);    //ABB_WL_ADC_1CH_CTRL_REG
    
    d2s_test.wait(0.00005);
    
    d2s_test.SSI_write(0x25C, 0x101);      //ABB_WL_ADC_1CH_CTRL_REG
    
    d2s_test.wait(0.0001);
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);  //CMU_RESERVE
    d2s_test.SSI_write(0x33C, 0x19B);      //CMU_RESERVE, 160Msps to get PV sensor. @2017-5-22
//    d2s_test.SSI_write(0x11C, 0x101);      //BBLDO set to 1.2V to get PV sensor. using external setup.

    //PV_Sensor
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
        
    d2s_test.SSI_write(0x370, 0x2A80);     //@2017-07-10
    d2s_test.wait(0.00008);
    
    d2s_test.SSI_write(0x370, 0x2AA0);     //@2017-07-10
    d2s_test.wait(0.00008);
    
    d2s_test.SSI_write(0x370, 0x2AC0);     //@2017-07-10
    d2s_test.wait(0.00008);
    
    d2s_test.SSI_write(0x370, 0x2AE0);     //PV_Sensor en, @2017-5-22
    
    d2s_test.wait(0.00015);
    
    //Call SSI_read_Module(0x3A8, , 12);
    //Call SSI_read_Module(0x3A4, , 12);
    d2s_test.SSI_read(0x3A8,"readdata0",12);
    d2s_test.SSI_read(0x3A4,"readdata1",12);    
    
    d2s_test.SSI_write(0x370, 0x2A00);     //PV_Sensor disable, 2B00->2A00@2017-08-14 for V210,@2017-5-22
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);  //CMU_RESERVE
    d2s_test.SSI_write(0x33C, 0x1B3);        //CMU_RESERVE, using 80Msps to do cal. @2017-5-22

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
    d2s_test.SSI_write(0xF0, 0x1);     //CH1_WL_AGCAL_COARSE_LOOP_SEL
    d2s_test.SSI_write(0xF4, 0x1);     //CH1_WL_AGCAL_FINE_LOOP_SEL
    d2s_test.SSI_write(0xF8, 0x0);     //CH1_WL_AGCAL_COARSE_RANGE_SEL
    d2s_test.SSI_write(0xFC, 0x3);     //CH1_WL_AGCAL_FINE_RANGE_SEL
    d2s_test.SSI_write(0x100, 0x0);    //CH1_WL_AGCAL_INVERSE
    d2s_test.SSI_write(0x104, 0x1);    //CH1_WL_AGCAL_DATA_SEL_A1
    d2s_test.SSI_write(0x108, 0x2);    //CH1_WL_AGCAL_DATA_SEL_A2
    d2s_test.SSI_write(0x10C, 0x4);    //CH1_WL_AGCAL_DATA_SEL_A3
    d2s_test.SSI_write(0x110, 0x8);    //CH1_WL_AGCAL_DATA_SEL_B1
    d2s_test.SSI_write(0x114, 0x10);   //CH1_WL_AGCAL_DATA_SEL_B2
    d2s_test.SSI_write(0x118, 0x20);   //CH1_WL_AGCAL_DATA_SEL_B3
    d2s_test.SSI_write(0x11C, 0x40);   //CH1_WL_AGCAL_DATA_SEL_C1
    d2s_test.SSI_write(0x120, 0x80);   //CH1_WL_AGCAL_DATA_SEL_C2
    d2s_test.SSI_write(0x124, 0x100);      //CH1_WL_AGCAL_DATA_SEL_C3
    d2s_test.SSI_write(0x134, 0x0);    //CH1_FIRST_COM_SEL
    d2s_test.SSI_write(0x128, 0x0);    //CH1_WL_AGCAL_CTRL_SEL
    
    d2s::d2s_LABEL_END();
    
//    map<int, long long> capture_data0;
//    map<int, long long> capture_data1;
    FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
        long long readvalue0 = d2s_test.getReadValue("readdata0").at(site_id);
        long long readvalue1 = d2s_test.getReadValue("readdata0").at(site_id);

        capture_data0[site_id] = readvalue0 ;
        capture_data1[site_id] = readvalue1 ;
        printf("Site:%d---------- %s    measure  value    :    %lld-----------",site_id,"SSI_DATA",capture_data0[site_id]);
        printf("Site:%d---------- %s    measure  value    :    %lld-----------",site_id,"SSI_DATA",capture_data1[site_id]);



	FOREACH_ACTIVESITE_END
}

void WL_ADC_C1_Setup_PVCal_Module(CSiteLong *pReadValue) {

    //File:  Hi1151 V200 Pilot ABB reg.xlsx
    //Sheet: WiFi_ADC_CH1
    //File time: 5/15/2017, update to this version.
    char cReadFlag[32] = {"\0"};
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x68, 0x0);     //S25
    d2s_test.SSI_write(0x6C, 0x0);     //S0B
    d2s_test.SSI_write(0x5C, 0x0);     //S20
    d2s_test.SSI_write(0x58, 0x0);     //S18&S10
    d2s_test.SSI_write(0x54, 0x0);     //mux reg
    d2s_test.SSI_write(0x60, 0x0);     //mux reg
    d2s_test.SSI_write(0x64, 0x0);     //mux reg
    d2s_test.SSI_write(0x0, 0x3);      //RF reg0
    d2s_test.SSI_write(0x4, 0x0);      //RF reg1
    d2s_test.SSI_write(0x8, 0x3);      //RF reg2
    d2s_test.SSI_write(0xC, 0x0);      //RF reg3
    d2s_test.SSI_write(0x10, 0x0);     //RF reg4
    d2s_test.SSI_write(0x14, 0x3400);      //RF reg5
    d2s_test.SSI_write(0x18, 0x3400);      //RF reg6

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0x364, 0x18A0);     //d_WL_ADC_REG0_c1<15:0>
    d2s_test.SSI_write(0x368, 0x4AA8);     //d_WL_ADC_REG1_c1<31:16>
    d2s_test.SSI_write(0x36C, 0x81);       //d_WL_ADC_REG2_c1<47:32>
    d2s_test.SSI_write(0x370, 0x2A00);      //d_WL_ADC_REG3_c1<63:48> 2B00->2A00@2017-08-14forV210,0b00->2b00@2017-06-23
    d2s_test.SSI_write(0x374, 0x0);        //d_WL_ADC_REG4_c1<69:64>

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x258, 0x111);      //ABB_WL_ADC_1CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x25C, 0x1);    //ABB_WL_ADC_1CH_CTRL_REG
    
    d2s_test.wait(0.00005);
    
    d2s_test.SSI_write(0x25C, 0x101);      //ABB_WL_ADC_1CH_CTRL_REG
    
    d2s_test.wait(0.0001);
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);  //CMU_RESERVE
    d2s_test.SSI_write(0x33C, 0x19B);      //CMU_RESERVE, 160Msps to get PV sensor. @2017-5-22
//    d2s_test.SSI_write(0x11C, 0x101);      //BBLDO set to 1.2V to get PV sensor. using external setup.

    //PV_Sensor
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
        
    d2s_test.SSI_write(0x370, 0x2A80);     //@2017-07-10
    d2s_test.wait(0.00008);
    
    d2s_test.SSI_write(0x370, 0x2AA0);     //@2017-07-10
    d2s_test.wait(0.00008);
    
    d2s_test.SSI_write(0x370, 0x2AC0);     //@2017-07-10
    d2s_test.wait(0.00008);
    
    d2s_test.SSI_write(0x370, 0x2AE0);     //PV_Sensor en, @2017-5-22
    
    d2s_test.wait(0.00015);
    
    //Call SSI_read_Module(0x3A8, , 12);
    //Call SSI_read_Module(0x3A4, , 12);
//    d2s_test.SSI_read(0x3A8,"readdata0",12);
//    d2s_test.SSI_read(0x3A4,"readdata1",12);
    sprintf(cReadFlag, "readdata%d", 0);
    d2s_test.SSI_read(0x3A8,cReadFlag,9);
    sprintf(cReadFlag, "readdata%d", 1);
    d2s_test.SSI_read(0x3A4,cReadFlag,9);
    
    d2s_test.SSI_write(0x370, 0x2A00);     //PV_Sensor disable, 2B00->2A00@2017-08-14 for V210,@2017-5-22
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);  //CMU_RESERVE
    d2s_test.SSI_write(0x33C, 0x1B3);        //CMU_RESERVE, using 80Msps to do cal. @2017-5-22

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
    d2s_test.SSI_write(0xF0, 0x1);     //CH1_WL_AGCAL_COARSE_LOOP_SEL
    d2s_test.SSI_write(0xF4, 0x1);     //CH1_WL_AGCAL_FINE_LOOP_SEL
    d2s_test.SSI_write(0xF8, 0x0);     //CH1_WL_AGCAL_COARSE_RANGE_SEL
    d2s_test.SSI_write(0xFC, 0x3);     //CH1_WL_AGCAL_FINE_RANGE_SEL
    d2s_test.SSI_write(0x100, 0x0);    //CH1_WL_AGCAL_INVERSE
    d2s_test.SSI_write(0x104, 0x1);    //CH1_WL_AGCAL_DATA_SEL_A1
    d2s_test.SSI_write(0x108, 0x2);    //CH1_WL_AGCAL_DATA_SEL_A2
    d2s_test.SSI_write(0x10C, 0x4);    //CH1_WL_AGCAL_DATA_SEL_A3
    d2s_test.SSI_write(0x110, 0x8);    //CH1_WL_AGCAL_DATA_SEL_B1
    d2s_test.SSI_write(0x114, 0x10);   //CH1_WL_AGCAL_DATA_SEL_B2
    d2s_test.SSI_write(0x118, 0x20);   //CH1_WL_AGCAL_DATA_SEL_B3
    d2s_test.SSI_write(0x11C, 0x40);   //CH1_WL_AGCAL_DATA_SEL_C1
    d2s_test.SSI_write(0x120, 0x80);   //CH1_WL_AGCAL_DATA_SEL_C2
    d2s_test.SSI_write(0x124, 0x100);      //CH1_WL_AGCAL_DATA_SEL_C3
    d2s_test.SSI_write(0x134, 0x0);    //CH1_FIRST_COM_SEL
    d2s_test.SSI_write(0x128, 0x0);    //CH1_WL_AGCAL_CTRL_SEL
    
    d2s::d2s_LABEL_END();
    
    long long nCapData[2] = {0};
    long long dwResult = 0;
//    CSiteLong ReadValue;
    int nsize = sizeof (nCapData) / sizeof (long long);
    FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
//    	int site_id = 0;
        sprintf(cReadFlag, "readdata%d", 0);
        nCapData[0]=d2s_test.getReadValue(cReadFlag).at(site_id);
//        cout << "---------------start--------------------"<<endl;
//		cout << "ABB_ADC_PV_Cal_nCapData[0]:"<<nCapData[0] << endl;
//		cout << "---------------stop--------------------------"<<endl;
        sprintf(cReadFlag, "readdata%d", 1);
        nCapData[1]=d2s_test.getReadValue(cReadFlag).at(site_id);
//        cout << "---------------start--------------------"<<endl;
//		cout << "ABB_ADC_PV_Cal_nCapData[1]:"<<nCapData[1] << endl;
//		cout << "---------------stop--------------------------"<<endl;
        
        pReadValue->InitDataArray(site_id, nsize);
        pReadValue->CopyElement(site_id, nCapData,nsize);

//        dwResult = (((ReadValue(site_id,0)>>9)&15)<<4)+(ReadValue(site_id,1)>>12);
//        pReadValue->InitDataArray(site_id, 1);
//        pReadValue->AddElement(site_id,0,pReadValue);
//        capture_data0[site_id] = readvalue0 ;
//        capture_data1[site_id] = readvalue1 ;
//        api->info_message("Site:%d---------- %s    measure  value    :    %lld-----------",site_id,"SSI_DATA",ReadValue(site_id,0));
//        api->info_message("Site:%d---------- %s    measure  value    :    %lld-----------",site_id,"SSI_DATA",ReadValue(site_id,1));
	FOREACH_ACTIVESITE_END
}

void WL_ADC_C1_Setup_PVCal_LV_Module(CSiteLong *pReadValue) {

    //File:  Hi1151 V200 Pilot ABB reg.xlsx
    //Sheet: WiFi_ADC_CH1
    //File time: 5/15/2017, update to this version.
    char cReadFlag[32] = {"\0"};
    
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x68, 0x0);     //S25
    d2s_test.SSI_write(0x6C, 0x0);     //S0B
    d2s_test.SSI_write(0x5C, 0x0);     //S20
    d2s_test.SSI_write(0x58, 0x0);     //S18&S10
    d2s_test.SSI_write(0x54, 0x0);     //mux reg
    d2s_test.SSI_write(0x60, 0x0);     //mux reg
    d2s_test.SSI_write(0x64, 0x0);     //mux reg
    d2s_test.SSI_write(0x0, 0x3);      //RF reg0
    d2s_test.SSI_write(0x4, 0x0);      //RF reg1
    d2s_test.SSI_write(0x8, 0x3);      //RF reg2
    d2s_test.SSI_write(0xC, 0x0);      //RF reg3
    d2s_test.SSI_write(0x10, 0x0);     //RF reg4
    d2s_test.SSI_write(0x14, 0x3400);      //RF reg5
    d2s_test.SSI_write(0x18, 0x3400);      //RF reg6

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0x364, 0x18A0);     //d_WL_ADC_REG0_c1<15:0>
    d2s_test.SSI_write(0x368, 0x4AA8);     //d_WL_ADC_REG1_c1<31:16>
    d2s_test.SSI_write(0x36C, 0x81);       //d_WL_ADC_REG2_c1<47:32>
    d2s_test.SSI_write(0x370, 0x2800);      //d_WL_ADC_REG3_c0<63:48> 0B00->2800@2017-08-14 for V210
    d2s_test.SSI_write(0x374, 0x0);        //d_WL_ADC_REG4_c1<69:64>

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x258, 0x111);      //ABB_WL_ADC_1CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x25C, 0x1);    //ABB_WL_ADC_1CH_CTRL_REG

    d2s_test.wait(0.00005);

    d2s_test.SSI_write(0x25C, 0x101);      //ABB_WL_ADC_1CH_CTRL_REG

    d2s_test.wait(0.0001);

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);  //CMU_RESERVE
    d2s_test.SSI_write(0x33C, 0x19B);      //CMU_RESERVE, 160Msps to get PV sensor. @2017-5-22
//    d2s_test.SSI_write(0x11C, 0x101);      //BBLDO set to 1.2V to get PV sensor. using external setup.

    //PV_Sensor
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
        
    d2s_test.SSI_write(0x370, 0x2880);     //@2017-07-10
    d2s_test.wait(0.00008);
    
    d2s_test.SSI_write(0x370, 0x28A0);     //@2017-07-10
    d2s_test.wait(0.00008);
    
    d2s_test.SSI_write(0x370, 0x28C0);     //@2017-07-10
    d2s_test.wait(0.00008);
    
    d2s_test.SSI_write(0x370, 0x28E0);     //PV_Sensor en, @2017-5-22

    d2s_test.wait(0.00015);

    //Call SSI_read_Module(0x3A8, , 12);
    //Call SSI_read_Module(0x3A4, , 12);
    sprintf(cReadFlag, "readdata%d", 0);
    d2s_test.SSI_read(0x398,cReadFlag,9);
    sprintf(cReadFlag, "readdata%d", 1);
    d2s_test.SSI_read(0x394,cReadFlag,9);

    d2s_test.SSI_write(0x370, 0x2800);     //0B00->2800@2017-08-14 for V210, PV_Sensor disable, @2017-5-22

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);  //CMU_RESERVE
    d2s_test.SSI_write(0x33C, 0x1B3);        //CMU_RESERVE, using 80Msps to do cal. @2017-5-22

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
    d2s_test.SSI_write(0xF0, 0x1);     //CH1_WL_AGCAL_COARSE_LOOP_SEL
    d2s_test.SSI_write(0xF4, 0x1);     //CH1_WL_AGCAL_FINE_LOOP_SEL
    d2s_test.SSI_write(0xF8, 0x0);     //CH1_WL_AGCAL_COARSE_RANGE_SEL
    d2s_test.SSI_write(0xFC, 0x3);     //CH1_WL_AGCAL_FINE_RANGE_SEL
    d2s_test.SSI_write(0x100, 0x0);    //CH1_WL_AGCAL_INVERSE
    d2s_test.SSI_write(0x104, 0x1);    //CH1_WL_AGCAL_DATA_SEL_A1
    d2s_test.SSI_write(0x108, 0x2);    //CH1_WL_AGCAL_DATA_SEL_A2
    d2s_test.SSI_write(0x10C, 0x4);    //CH1_WL_AGCAL_DATA_SEL_A3
    d2s_test.SSI_write(0x110, 0x8);    //CH1_WL_AGCAL_DATA_SEL_B1
    d2s_test.SSI_write(0x114, 0x10);   //CH1_WL_AGCAL_DATA_SEL_B2
    d2s_test.SSI_write(0x118, 0x20);   //CH1_WL_AGCAL_DATA_SEL_B3
    d2s_test.SSI_write(0x11C, 0x40);   //CH1_WL_AGCAL_DATA_SEL_C1
    d2s_test.SSI_write(0x120, 0x80);   //CH1_WL_AGCAL_DATA_SEL_C2
    d2s_test.SSI_write(0x124, 0x100);      //CH1_WL_AGCAL_DATA_SEL_C3
    d2s_test.SSI_write(0x134, 0x0);    //CH1_FIRST_COM_SEL
    d2s_test.SSI_write(0x128, 0x0);    //CH1_WL_AGCAL_CTRL_SEL
    
    d2s::d2s_LABEL_END();
    
    long long nCapData[2] = {0};
    long long dwResult = 0;
    int nsize = sizeof (nCapData) / sizeof (long long);
    FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)

        sprintf(cReadFlag, "readdata%d", 0);
        nCapData[0]=d2s_test.getReadValue(cReadFlag).at(site_id);
        sprintf(cReadFlag, "readdata%d", 1);
        nCapData[1]=d2s_test.getReadValue(cReadFlag).at(site_id);
        
        pReadValue->InitDataArray(site_id, nsize);
        pReadValue->CopyElement(site_id, nCapData,nsize);
	FOREACH_ACTIVESITE_END
}


void WL_ADC_C1_Setup_PVCal_LV1_Module(CSiteLong *pReadValue) {

    //File:  Hi1151 V200 Pilot ABB reg.xlsx
    //Sheet: WiFi_ADC_CH1
    //File time: 5/15/2017, update to this version.
    char cReadFlag[32] = {"\0"};
    
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x68, 0x0);     //S25
    d2s_test.SSI_write(0x6C, 0x0);     //S0B
    d2s_test.SSI_write(0x5C, 0x0);     //S20
    d2s_test.SSI_write(0x58, 0x0);     //S18&S10
    d2s_test.SSI_write(0x54, 0x0);     //mux reg
    d2s_test.SSI_write(0x60, 0x0);     //mux reg
    d2s_test.SSI_write(0x64, 0x0);     //mux reg
    d2s_test.SSI_write(0x0, 0x3);      //RF reg0
    d2s_test.SSI_write(0x4, 0x0);      //RF reg1
    d2s_test.SSI_write(0x8, 0x3);      //RF reg2
    d2s_test.SSI_write(0xC, 0x0);      //RF reg3
    d2s_test.SSI_write(0x10, 0x0);     //RF reg4
    d2s_test.SSI_write(0x14, 0x3400);      //RF reg5
    d2s_test.SSI_write(0x18, 0x3400);      //RF reg6

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0x364, 0x18A0);     //d_WL_ADC_REG0_c1<15:0>
    d2s_test.SSI_write(0x368, 0x4AA8);     //d_WL_ADC_REG1_c1<31:16>
    d2s_test.SSI_write(0x36C, 0x81);       //d_WL_ADC_REG2_c1<47:32>
    d2s_test.SSI_write(0x370, 0xA00);      //d_WL_ADC_REG3_c1<63:48> 2B00->A00@2017-08-14forV210,0b00->2b00@2017-06-23
    d2s_test.SSI_write(0x374, 0x0);        //d_WL_ADC_REG4_c1<69:64>

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x258, 0x111);      //ABB_WL_ADC_1CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x25C, 0x1);    //ABB_WL_ADC_1CH_CTRL_REG
    
    d2s_test.wait(0.00005);
    
    d2s_test.SSI_write(0x25C, 0x101);      //ABB_WL_ADC_1CH_CTRL_REG
    
    d2s_test.wait(0.0001);
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);  //CMU_RESERVE
    d2s_test.SSI_write(0x33C, 0x19B);      //CMU_RESERVE, 160Msps to get PV sensor. @2017-5-22
//    d2s_test.SSI_write(0x11C, 0x101);      //BBLDO set to 1.2V to get PV sensor. using external setup.

    //PV_Sensor
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
        
    d2s_test.SSI_write(0x370, 0xA80);     //@2017-07-10
    d2s_test.wait(0.00008);
    
    d2s_test.SSI_write(0x370, 0xAA0);     //@2017-07-10
    d2s_test.wait(0.00008);
    
    d2s_test.SSI_write(0x370, 0xAC0);     //@2017-07-10
    d2s_test.wait(0.00008);
    
    d2s_test.SSI_write(0x370, 0xAE0);     //PV_Sensor en, @2017-5-22
    
    d2s_test.wait(0.00015);
    
    //Call SSI_read_Module(0x3A8, , 12);
    //Call SSI_read_Module(0x3A4, , 12);
    sprintf(cReadFlag, "readdata%d", 0);
    d2s_test.SSI_read(0x398,cReadFlag,9);
    sprintf(cReadFlag, "readdata%d", 1);
    d2s_test.SSI_read(0x394,cReadFlag,9);
    
    d2s_test.SSI_write(0x370, 0xA00);     //PV_Sensor disable, 2B00->2A00@2017-08-14 for V210,@2017-5-22
    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);  //CMU_RESERVE
    d2s_test.SSI_write(0x33C, 0x1B3);        //CMU_RESERVE, using 80Msps to do cal. @2017-5-22

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
    d2s_test.SSI_write(0xF0, 0x1);     //CH1_WL_AGCAL_COARSE_LOOP_SEL
    d2s_test.SSI_write(0xF4, 0x1);     //CH1_WL_AGCAL_FINE_LOOP_SEL
    d2s_test.SSI_write(0xF8, 0x0);     //CH1_WL_AGCAL_COARSE_RANGE_SEL
    d2s_test.SSI_write(0xFC, 0x3);     //CH1_WL_AGCAL_FINE_RANGE_SEL
    d2s_test.SSI_write(0x100, 0x0);    //CH1_WL_AGCAL_INVERSE
    d2s_test.SSI_write(0x104, 0x1);    //CH1_WL_AGCAL_DATA_SEL_A1
    d2s_test.SSI_write(0x108, 0x2);    //CH1_WL_AGCAL_DATA_SEL_A2
    d2s_test.SSI_write(0x10C, 0x4);    //CH1_WL_AGCAL_DATA_SEL_A3
    d2s_test.SSI_write(0x110, 0x8);    //CH1_WL_AGCAL_DATA_SEL_B1
    d2s_test.SSI_write(0x114, 0x10);   //CH1_WL_AGCAL_DATA_SEL_B2
    d2s_test.SSI_write(0x118, 0x20);   //CH1_WL_AGCAL_DATA_SEL_B3
    d2s_test.SSI_write(0x11C, 0x40);   //CH1_WL_AGCAL_DATA_SEL_C1
    d2s_test.SSI_write(0x120, 0x80);   //CH1_WL_AGCAL_DATA_SEL_C2
    d2s_test.SSI_write(0x124, 0x100);      //CH1_WL_AGCAL_DATA_SEL_C3
    d2s_test.SSI_write(0x134, 0x0);    //CH1_FIRST_COM_SEL
    d2s_test.SSI_write(0x128, 0x0);    //CH1_WL_AGCAL_CTRL_SEL
    
    d2s::d2s_LABEL_END();
    
    long long nCapData[2] = {0};
    long long dwResult = 0;
    int nsize = sizeof (nCapData) / sizeof (long long);
    FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)

        sprintf(cReadFlag, "readdata%d", 0);
        nCapData[0]=d2s_test.getReadValue(cReadFlag).at(site_id);
        sprintf(cReadFlag, "readdata%d", 1);
        nCapData[1]=d2s_test.getReadValue(cReadFlag).at(site_id);
        
        pReadValue->InitDataArray(site_id, nsize);
        pReadValue->CopyElement(site_id, nCapData,nsize);
	FOREACH_ACTIVESITE_END
}


void WL_ADC_C1_Setup_CalStatus_Module(CSiteLong *pReadValue) {
    char cReadFlag[32] = {"\0"};
    
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;    
    // Comparater Cal 1
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
    d2s_test.SSI_write(0xEC, 0x1);     //CH1_WL_AGCAL_EN
    for(int i=0;i<100;i++)
        d2s_test.wait(0.0002);
    
    sprintf(cReadFlag, "readdata%d", 0);
    d2s_test.SSI_read(0x1B4,cReadFlag,9);
    //Call SSI_read_Module(0x1B4, True, 12);    //WL_ADC1_AGCAL_NUM_ONE_ADD_DONE
    
    // Comparater Cal 2
    
    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
    d2s_test.SSI_write(0xEC, 0x1);     //CH1_WL_AGCAL_EN
    for(int i=0;i<100;i++)
    d2s_test.wait(0.00008);
    
    sprintf(cReadFlag, "readdata%d", 1);
    d2s_test.SSI_read(0x1B4,cReadFlag,9);
    //Call SSI_read_Module(0x1B4, True, 12);    //WL_ADC1_AGCAL_NUM_ONE_ADD_DONE
    
    // Comparater Cal 3
    
    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
    d2s_test.SSI_write(0xEC, 0x1);     //CH1_WL_AGCAL_EN
    for(int i=0;i<100;i++)
        d2s_test.wait(0.00008);
    
    sprintf(cReadFlag, "readdata%d", 2);
    d2s_test.SSI_read(0x1B4,cReadFlag,9);
    //Call SSI_read_Module(0x1B4, True, 12);    //WL_ADC1_AGCAL_NUM_ONE_ADD_DONE
    
    // Comparater Cal 4
    
    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
    d2s_test.SSI_write(0xEC, 0x1);     //CH1_WL_AGCAL_EN
    for(int i=0;i<100;i++)
        d2s_test.wait(0.00008);
    
    sprintf(cReadFlag, "readdata%d", 3);
    d2s_test.SSI_read(0x1B4,cReadFlag,9);
    //Call SSI_read_Module(0x1B4, True, 12);    //WL_ADC1_AGCAL_NUM_ONE_ADD_DONE
    
    // Comparater Cal 5
    
    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
    d2s_test.SSI_write(0xEC, 0x1);     //CH1_WL_AGCAL_EN
    for(int i=0;i<100;i++)
        d2s_test.wait(0.00008);
    
    sprintf(cReadFlag, "readdata%d", 4);
    d2s_test.SSI_read(0x1B4,cReadFlag,9);
    //Call SSI_read_Module(0x1B4, True, 12);    //WL_ADC1_AGCAL_NUM_ONE_ADD_DONE
    
    // Comparater Cal 6
    
    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
    d2s_test.SSI_write(0xEC, 0x1);     //CH1_WL_AGCAL_EN
    for(int i=0;i<100;i++)
        d2s_test.wait(0.00008);
    
    sprintf(cReadFlag, "readdata%d", 5);
    d2s_test.SSI_read(0x1B4,cReadFlag,9);
    //Call SSI_read_Module(0x1B4, True, 12);    //WL_ADC1_AGCAL_NUM_ONE_ADD_DONE
    
    //Read ABB ADC Registers @2017/6/19
    sprintf(cReadFlag, "readdata%d", 6);
    d2s_test.SSI_read(0x138,cReadFlag,9);
    
    sprintf(cReadFlag, "readdata%d", 7);
    d2s_test.SSI_read(0x13C,cReadFlag,9);
    
    sprintf(cReadFlag, "readdata%d", 8);
    d2s_test.SSI_read(0x140,cReadFlag,9);
    
    sprintf(cReadFlag, "readdata%d", 9);
    d2s_test.SSI_read(0x144,cReadFlag,9);
    
    sprintf(cReadFlag, "readdata%d", 10);
    d2s_test.SSI_read(0x148,cReadFlag,9);
    
    sprintf(cReadFlag, "readdata%d", 11);
    d2s_test.SSI_read(0x14C,cReadFlag,9);    
    //Call SSI_read_Module(0x138, True, 12);    //WL_ADC1_AGCAL_COARSE_CALIP_A1
    //Call SSI_read_Module(0x13C, True, 12);    //WL_ADC1_AGCAL_fine_CALIP_A1
    //Call SSI_read_Module(0x140, True, 12);    //WL_ADC1_AGCAL_COARSE_CALIP_A2
    //Call SSI_read_Module(0x144, True, 12);    //WL_ADC1_AGCAL_fine_CALIP_A2
    //Call SSI_read_Module(0x148, True, 12);    //WL_ADC1_AGCAL_COARSE_CALIP_A3
    //Call SSI_read_Module(0x14C, True, 12);    //WL_ADC1_AGCAL_fine_CALIP_A3

    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN

    d2s::d2s_LABEL_END();
    
    long long nCapData[12] = {0};
    long long dwResult = 0;
//    CSiteLong ReadValue;
    int nsize = sizeof (nCapData) / sizeof (long long);
//    FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
//
//
//        if (!d2s::isProductionMode()) {
//            for(int RegNum=0;RegNum<12;RegNum++)
//            {
//                sprintf(cReadFlag, "readdata%d", RegNum);
//                nCapData[RegNum]=d2s_test.getReadValue(cReadFlag).at(site_id);
//            }
//        } else {
//            unsigned long data[192];
//            DIO_Capture(site_id,"DBB_GPIO7",data);
////            api->Get_capture_data("DBB_GPIO7", 0, 192, data);
//
//            for(int n = 0;n<192;n+=16)
//            {
//                nCapData[n/16] = ConvertCapData(data+n,16);
//            }
//        }
//
//        pReadValue->InitDataArray(site_id, nsize);
//        pReadValue->CopyElement(site_id, nCapData,nsize);
//
//	FOREACH_ACTIVESITE_END


    if (!d2s::isProductionMode()) {
	FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
		for(int RegNum=0;RegNum<12;RegNum++)
		{
			sprintf(cReadFlag, "readdata%d", RegNum);
			nCapData[RegNum]=d2s_test.getReadValue(cReadFlag).at(site_id);
		}
		pReadValue->InitDataArray(site_id, nsize);
		pReadValue->CopyElement(site_id,nCapData,nsize);

	FOREACH_ACTIVESITE_END
	} else {

		unsigned long data[192];

		auto CAP_Data = TheInst.Digital().PatEng().GetCaptureData("DBB_GPIO7");

		for (auto siteData : CAP_Data)
		{
			for (auto pinData : siteData.second)
			{
				int i=0;
				for (auto capData : pinData.second)
				{
					data[i] = capData.iECResult;
					i++;

				}
			}
			for(int n = 0;n<192;n+=16)
			{
				nCapData[n/16] = ConvertCapData(data+n,16);
			}

			pReadValue->InitDataArray(siteData.first, nsize);
			pReadValue->CopyElement(siteData.first,nCapData,nsize);
		}

	}

}

//void WL_ADC_C1_Setup_CalStatus_Module(CSiteLong *pReadValue) {
//    char cReadFlag[32] = {"\0"};
//    
//    d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
//    d2sProtocolSSI d2s_test;    
//    // Comparater Cal 1
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0xA0, false);
//    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
//    d2s_test.SSI_write(0xEC, 0x1);     //CH1_WL_AGCAL_EN
//    d2s_test.wait(0.02);
//    
//    sprintf(cReadFlag, "readdata%d", 0);
//    d2s_test.SSI_read(0x1B4,cReadFlag,9);
//    //Call SSI_read_Module(0x1B4, True, 12);    //WL_ADC1_AGCAL_NUM_ONE_ADD_DONE
//    
//    // Comparater Cal 2
//    
//    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
//    d2s_test.SSI_write(0xEC, 0x1);     //CH1_WL_AGCAL_EN
//    d2s_test.wait(0.008);
//    
//    sprintf(cReadFlag, "readdata%d", 1);
//    d2s_test.SSI_read(0x1B4,cReadFlag,9);
//    //Call SSI_read_Module(0x1B4, True, 12);    //WL_ADC1_AGCAL_NUM_ONE_ADD_DONE
//    
//    // Comparater Cal 3
//    
//    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
//    d2s_test.SSI_write(0xEC, 0x1);     //CH1_WL_AGCAL_EN
//    d2s_test.wait(0.008);
//    
//    sprintf(cReadFlag, "readdata%d", 2);
//    d2s_test.SSI_read(0x1B4,cReadFlag,9);
//    //Call SSI_read_Module(0x1B4, True, 12);    //WL_ADC1_AGCAL_NUM_ONE_ADD_DONE
//    
//    // Comparater Cal 4
//    
//    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
//    d2s_test.SSI_write(0xEC, 0x1);     //CH1_WL_AGCAL_EN
//    d2s_test.wait(0.008);
//    
//    sprintf(cReadFlag, "readdata%d", 3);
//    d2s_test.SSI_read(0x1B4,cReadFlag,9);
//    //Call SSI_read_Module(0x1B4, True, 12);    //WL_ADC1_AGCAL_NUM_ONE_ADD_DONE
//    
//    // Comparater Cal 5
//    
//    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
//    d2s_test.SSI_write(0xEC, 0x1);     //CH1_WL_AGCAL_EN
//    d2s_test.wait(0.008);
//    
//    sprintf(cReadFlag, "readdata%d", 4);
//    d2s_test.SSI_read(0x1B4,cReadFlag,9);
//    //Call SSI_read_Module(0x1B4, True, 12);    //WL_ADC1_AGCAL_NUM_ONE_ADD_DONE
//    
//    // Comparater Cal 6
//    
//    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
//    d2s_test.SSI_write(0xEC, 0x1);     //CH1_WL_AGCAL_EN
//    d2s_test.wait(0.008);
//    
//    sprintf(cReadFlag, "readdata%d", 5);
//    d2s_test.SSI_read(0x1B4,cReadFlag,9);
//    //Call SSI_read_Module(0x1B4, True, 12);    //WL_ADC1_AGCAL_NUM_ONE_ADD_DONE
//    
//    //Read ABB ADC Registers @2017/6/19
//    sprintf(cReadFlag, "readdata%d", 6);
//    d2s_test.SSI_read(0x138,cReadFlag,9);
//    
//    sprintf(cReadFlag, "readdata%d", 7);
//    d2s_test.SSI_read(0x13C,cReadFlag,9);
//    
//    sprintf(cReadFlag, "readdata%d", 8);
//    d2s_test.SSI_read(0x140,cReadFlag,9);
//    
//    sprintf(cReadFlag, "readdata%d", 9);
//    d2s_test.SSI_read(0x144,cReadFlag,9);
//    
//    sprintf(cReadFlag, "readdata%d", 10);
//    d2s_test.SSI_read(0x148,cReadFlag,9);
//    
//    sprintf(cReadFlag, "readdata%d", 11);
//    d2s_test.SSI_read(0x14C,cReadFlag,9);    
//    //Call SSI_read_Module(0x138, True, 12);    //WL_ADC1_AGCAL_COARSE_CALIP_A1
//    //Call SSI_read_Module(0x13C, True, 12);    //WL_ADC1_AGCAL_fine_CALIP_A1
//    //Call SSI_read_Module(0x140, True, 12);    //WL_ADC1_AGCAL_COARSE_CALIP_A2
//    //Call SSI_read_Module(0x144, True, 12);    //WL_ADC1_AGCAL_fine_CALIP_A2
//    //Call SSI_read_Module(0x148, True, 12);    //WL_ADC1_AGCAL_COARSE_CALIP_A3
//    //Call SSI_read_Module(0x14C, True, 12);    //WL_ADC1_AGCAL_fine_CALIP_A3
//
//    d2s_test.SSI_write(0xEC, 0x0);     //CH1_WL_AGCAL_EN
//
//    d2s::d2s_LABEL_END();
//    
//    long long nCapData[12] = {0};
//    long long dwResult = 0;
////    CSiteLong ReadValue;
//    int nsize = sizeof (nCapData) / sizeof (long long);
//    FOREACH_ACTIVE_SITE(api){        
//
//        for(int RegNum=0;RegNum<12;RegNum++)
//        {
//        sprintf(cReadFlag, "readdata%d", RegNum);
//        nCapData[RegNum]=d2s_test.getReadValue(cReadFlag);
//        }
//        pReadValue->InitDataArray(site_id, nsize);
//        pReadValue->CopyElement(site_id, nCapData,nsize);
//        
//    }
//}

void WL_ADC_C1_Setup_CapCal_Module(CSiteLong *pReadValue) {
    
    //char cReadFlag[32] = {"\0"};
    char cReadFlag[32] = {"\0"};
    
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0x368, 0x4AA0);     //d_WL_ADC_REG1_c1<31:16>

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x224, 0x0);    //WL_ADC1_CAP_EN
    d2s_test.SSI_write(0x24C, 0x1);    //WL_ADC1_CAP_MODE
    d2s_test.SSI_write(0x228, 0x1);    //WL_ADC1_CAP_WAIT_CYCLE_SEL
    d2s_test.SSI_write(0x244, 0x1);    //WL_ADC1_CAP_INDEX_SOFT
    d2s_test.SSI_write(0x248, 0x1);    //WL_ADC1_CAP_PN_CAPSTAT
    d2s_test.SSI_write(0x22C, 0x0);    //WL_ADC1_CAP_PN_INDEX_C1
    d2s_test.SSI_write(0x230, 0x21);   //WL_ADC1_CAP_PN_INDEX_C2
    d2s_test.SSI_write(0x234, 0x22);   //WL_ADC1_CAP_PN_INDEX_C4
    d2s_test.SSI_write(0x238, 0x24);   //WL_ADC1_CAP_PN_INDEX_C8
    d2s_test.SSI_write(0x23C, 0x28);   //WL_ADC1_CAP_PN_INDEX_C16
    d2s_test.SSI_write(0x240, 0x30);   //WL_ADC1_CAP_PN_INDEX_C32
    d2s_test.SSI_write(0x224, 0x1);    //WL_ADC1_CAP_EN

    d2s_test.wait(0.001);
    
    sprintf(cReadFlag, "readdata%d", 0);
    d2s_test.SSI_read(0x268,cReadFlag,9);
        
    sprintf(cReadFlag, "readdata%d", 1);
    d2s_test.SSI_read(0x26C,cReadFlag,9);
        
    sprintf(cReadFlag, "readdata%d", 2);
    d2s_test.SSI_read(0x270,cReadFlag,9);
        
    sprintf(cReadFlag, "readdata%d", 3);
    d2s_test.SSI_read(0x274,cReadFlag,9);
        
    sprintf(cReadFlag, "readdata%d", 4);
    d2s_test.SSI_read(0x278,cReadFlag,9);
        
    sprintf(cReadFlag, "readdata%d", 5);
    d2s_test.SSI_read(0x27C,cReadFlag,9);
    
    sprintf(cReadFlag, "readdata%d", 6);
    d2s_test.SSI_read(0x280,cReadFlag,9);
    //Call SSI_read_Module(0x268, , 12);
    //Call SSI_read_Module(0x26C, , 12);
    //Call SSI_read_Module(0x270, , 12);
    //Call SSI_read_Module(0x274, , 12);
    //Call SSI_read_Module(0x278, , 12);
    //Call SSI_read_Module(0x27C, , 12);
    //Call SSI_read_Module(0x280, , 12);
    
    d2s_test.SSI_write(0x224, 0x0);    //WL_ADC1_CAP_EN

    d2s::d2s_LABEL_END();
    
    long long nCapData[7] = {0};
    long long dwResult = 0;
//    CSiteLong ReadValue;
    int nsize = sizeof (nCapData) / sizeof (long long);
//    FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
//
//
//        if (!d2s::isProductionMode()) {
//            for(int RegNum=0;RegNum<7;RegNum++)
//            {
//                sprintf(cReadFlag, "readdata%d", RegNum);
//                nCapData[RegNum]=d2s_test.getReadValue(cReadFlag).at(site_id);
//            }
//        } else {
//            unsigned long data[112];
//            DIO_Capture(site_id,"DBB_GPIO7",data);
////            api->Get_capture_data("DBB_GPIO7", 0, 112, data);
//
//            for(int n = 0;n<112;n+=16)
//            {
//                nCapData[n/16] = ConvertCapData(data+n,16);
//            }
//        }
//        pReadValue->InitDataArray(site_id, nsize);
//        pReadValue->CopyElement(site_id, nCapData,nsize);
//
//        FOREACH_ACTIVESITE_END

	if (!d2s::isProductionMode()) {
		FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
		for(int RegNum=0;RegNum<7;RegNum++)
		{
			sprintf(cReadFlag, "readdata%d", RegNum);
			nCapData[RegNum]=d2s_test.getReadValue(cReadFlag).at(site_id);
//			cout << "----------------start------------------"<< endl;
//			cout << "nCapData[RegNum]:" << nCapData[RegNum] << endl;
//			cout << "----------------stop------------------"<< endl;
		}
		pReadValue->InitDataArray(site_id, nsize);
		pReadValue->CopyElement(site_id,nCapData,nsize);

	FOREACH_ACTIVESITE_END
	} else {

		unsigned long data[112];

		auto CAP_Data = TheInst.Digital().PatEng().GetCaptureData("DBB_GPIO7");

		for (auto siteData : CAP_Data)
		{
			for (auto pinData : siteData.second)
			{
				int i=0;
				for (auto capData : pinData.second)
				{
					data[i] = capData.iECResult;
					i++;

				}
			}
			for(int n = 0;n<112;n+=16)
			{
				nCapData[n/16] = ConvertCapData(data+n,16);
			}

			pReadValue->InitDataArray(siteData.first, nsize);
			pReadValue->CopyElement(siteData.first,nCapData,nsize);
		}

	}

}


void WL_DAC_C0_LPF_Module() {
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);
    d2s_test.SSI_write(0x33C, 0x19B);      //CMU_RESERVE

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x68, 0x3);     //S25
    d2s_test.SSI_write(0x6C, 0x300);   //S25
    d2s_test.SSI_write(0x5C, 0x3);     //S20
    d2s_test.SSI_write(0x54, 0x303);   //S00&S09
    d2s_test.SSI_write(0x58, 0x0);     //mux rf reg
    d2s_test.SSI_write(0x60, 0x0);     //mux rf reg
    d2s_test.SSI_write(0x64, 0x0);     //mux rf reg
    d2s_test.SSI_write(0x6, 0x2);      //d_wl_tx_gain_ctrl_mode_c0
    d2s_test.SSI_write(0x0, 0x0);      //wl_trx_reg0
    d2s_test.SSI_write(0x4, 0x1);      //wl_trx_reg1 @20170825 3->1
    d2s_test.SSI_write(0x8, 0x1);      //wl_trx_reg2 @20170825 3->1  make 1V5In1 current = C1 .from 36ma to 24
    d2s_test.SSI_write(0xC, 0x3F);     //wl_trx_reg3
    d2s_test.SSI_write(0x10, 0x3F);        //wl_trx_reg4
    d2s_test.SSI_write(0x14, 0x400);   //wl_trx_reg5
    d2s_test.SSI_write(0x18, 0x400);   //wl_trx_reg6
    d2s_test.SSI_write(0x1C, 0x101);   //wl_trx_reg7
    d2s_test.SSI_write(0x2C, 0x5);         //wl_trx_reg11
    d2s_test.SSI_write(0x34, 0x400);   //wl_trx_reg13
    d2s_test.SSI_write(0x3C, 0x444);       //wl_trx_reg15
    d2s_test.SSI_write(0x44, 0x5D7);       //wl_trx_reg17
    d2s_test.SSI_write(0x4C, 0x5D7);       //wl_trx_reg19
    d2s_test.SSI_write(0x310, 0x4);        //wl_trx_reg196
    d2s_test.SSI_write(0x314, 0x31);       //wl_trx_reg197
    d2s_test.SSI_write(0x318, 0x31);       //wl_trx_reg198
    d2s_test.SSI_write(0x31C, 0x0);        //wl_trx_reg199
    d2s_test.SSI_write(0x320, 0x0);        //wl_trx_reg200
    d2s_test.SSI_write(0x324, 0x4444);     //wl_trx_reg201
    d2s_test.SSI_write(0x328, 0x140);      //wl_trx_reg202
    d2s_test.SSI_write(0x32C, 0x1133);     //wl_trx_reg203
    d2s_test.SSI_write(0x330, 0x9577);     //wl_trx_reg204
    d2s_test.SSI_write(0x334, 0x52C);      //wl_trx_reg205
    d2s_test.SSI_write(0x338, 0x784);      //wl_trx_reg206
    d2s_test.SSI_write(0x360, 0x31);       //wl_trx_reg216
    d2s_test.SSI_write(0x364, 0x31);       //wl_trx_reg217
    d2s_test.SSI_write(0x368, 0x0);        //wl_trx_reg218
    d2s_test.SSI_write(0x36C, 0x0);        //wl_trx_reg219
    d2s_test.SSI_write(0x370, 0x4444);     //wl_trx_reg220
    d2s_test.SSI_write(0x374, 0x140);      //wl_trx_reg221
    d2s_test.SSI_write(0x378, 0x1133);     //wl_trx_reg222
    d2s_test.SSI_write(0x37C, 0x9577);     //wl_trx_reg223
    d2s_test.SSI_write(0x380, 0x52C);      //wl_trx_reg224
    d2s_test.SSI_write(0x384, 0x784);      //wl_trx_reg225

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0x378, 0x0);    //d_WL_DAC_REG0_c0<15:0>
    d2s_test.SSI_write(0x37C, 0x0);    //d_WL_DAC_REG1_c0<15:0>
    d2s_test.SSI_write(0x388, 0x0);    //d_WL_DAC_Gain_I_c0<2:0>
    d2s_test.SSI_write(0x388, 0x0);    //d_WL_DAC_Gain_Q_c0<2:0>

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x8, 0x33);    //WB_DAC0_DEM_CTL 0x3233->0x0133 @20170520  CLA2 config from 133->33

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0x378, 0x140);      //d_WL_DAC_REG0_c0<15:0>  0x100->0x140 @20170520
    d2s_test.SSI_write(0x37C, 0x5);    //d_WL_DAC_REG1_c0<15:0>    0x4-> 0x5 @20170520

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x24C, 0x111);      //ABB_WL_DAC_0CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x250, 0x1);    //ABB_WL_DAC_0CH_CTRL_REG
    
    d2s_test.wait(0.00005);
    
    d2s_test.SSI_write(0x250, 0x101);      //ABB_WL_DAC_0CH_CTRL_REG
    
    d2s_test.SSI_write(0x240, 0x111);      //ABB_WL_ADC_0CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x244, 0x0);        //ABB_WL_ADC_0CH_CTRL_REG
               
    d2s_test.SSI_write(0x258, 0x111);   //ABB_WL_ADC_1CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x25C, 0x0);     //ABB_WL_ADC_1CH_CTRL_REG
        
    d2s_test.SSI_write(0x264, 0x111);      //ABB_WL_DAC_1CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x268, 0x0);    //ABB_WL_DAC_1CH_CTRL_REG
    
    d2s_test.wait(0.00005);

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x7);    //PKTMEM_MODE_CFG
    d2s_test.SSI_write(0x2FC, 0x1);    //ABB_CALI_MODE

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x1);    //PKTMEM_SEL

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x17);   //PKTMEM_MODE_CFG
    
    d2s_test.wait(0.0001);
    
    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2E4, 0xF); //DIG_CTRL
    d2s_test.SSI_write(0x2E0, 0xC);
    d2s_test.SSI_write(0x2E4, 0x0);
    d2s_test.SSI_write(0x2E4, 0xF);
    
    d2s::d2s_LABEL_END();
}


void WL_DAC_DEM_C0_LPF_Module() {

    //File:  Hi1151 V200 Pilot ABB reg.xlsx
    //Sheet: WIFI_DAC_CH0+LPF
    //File time: 5/15/2017, update to this version.
    //no need to change CMU @2017-05-22
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x40, false);
//    d2s_test.SSI_write(0x308, 0x230);      //CMU Driver
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);
    d2s_test.SSI_write(0x33C, 0x19B);      //CMU_RESERVE

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x68, 0x3);     //S25
    d2s_test.SSI_write(0x6C, 0x300);   //S25
    d2s_test.SSI_write(0x5C, 0x3);     //S20
    d2s_test.SSI_write(0x54, 0x303);   //S00&S09
    d2s_test.SSI_write(0x58, 0x0);     //mux rf reg
    d2s_test.SSI_write(0x60, 0x0);     //mux rf reg
    d2s_test.SSI_write(0x64, 0x0);     //mux rf reg
    d2s_test.SSI_write(0x6, 0x2);      //d_wl_tx_gain_ctrl_mode_c0
    d2s_test.SSI_write(0x0, 0x0);      //wl_trx_reg0
    d2s_test.SSI_write(0x4, 0x1);      //wl_trx_reg1 @20170825 3->1
    d2s_test.SSI_write(0x8, 0x1);      //wl_trx_reg2 @20170825 3->1  make 1V5In1 current = C1 .from 36ma to 24
    d2s_test.SSI_write(0xC, 0x3F);     //wl_trx_reg3
    d2s_test.SSI_write(0x10, 0x3F);        //wl_trx_reg4
    d2s_test.SSI_write(0x14, 0x400);   //wl_trx_reg5
    d2s_test.SSI_write(0x18, 0x400);   //wl_trx_reg6
    d2s_test.SSI_write(0x1C, 0x101);   //wl_trx_reg7
    d2s_test.SSI_write(0x2C, 0x5);         //wl_trx_reg11
    d2s_test.SSI_write(0x34, 0x400);   //wl_trx_reg13
    d2s_test.SSI_write(0x3C, 0x444);       //wl_trx_reg15
    d2s_test.SSI_write(0x44, 0x5D7);       //wl_trx_reg17
    d2s_test.SSI_write(0x4C, 0x5D7);       //wl_trx_reg19
    d2s_test.SSI_write(0x310, 0x4);        //wl_trx_reg196
    d2s_test.SSI_write(0x314, 0x31);       //wl_trx_reg197
    d2s_test.SSI_write(0x318, 0x31);       //wl_trx_reg198
    d2s_test.SSI_write(0x31C, 0x0);        //wl_trx_reg199
    d2s_test.SSI_write(0x320, 0x0);        //wl_trx_reg200
    d2s_test.SSI_write(0x324, 0x4444);     //wl_trx_reg201
    d2s_test.SSI_write(0x328, 0x140);      //wl_trx_reg202
    d2s_test.SSI_write(0x32C, 0x1133);     //wl_trx_reg203
    d2s_test.SSI_write(0x330, 0x9577);     //wl_trx_reg204
    d2s_test.SSI_write(0x334, 0x52C);      //wl_trx_reg205
    d2s_test.SSI_write(0x338, 0x784);      //wl_trx_reg206
    d2s_test.SSI_write(0x360, 0x31);       //wl_trx_reg216
    d2s_test.SSI_write(0x364, 0x31);       //wl_trx_reg217
    d2s_test.SSI_write(0x368, 0x0);        //wl_trx_reg218
    d2s_test.SSI_write(0x36C, 0x0);        //wl_trx_reg219
    d2s_test.SSI_write(0x370, 0x4444);     //wl_trx_reg220
    d2s_test.SSI_write(0x374, 0x140);      //wl_trx_reg221
    d2s_test.SSI_write(0x378, 0x1133);     //wl_trx_reg222
    d2s_test.SSI_write(0x37C, 0x9577);     //wl_trx_reg223
    d2s_test.SSI_write(0x380, 0x52C);      //wl_trx_reg224
    d2s_test.SSI_write(0x384, 0x784);      //wl_trx_reg225

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0x378, 0x0);    //d_WL_DAC_REG0_c0<15:0>
    d2s_test.SSI_write(0x37C, 0x0);    //d_WL_DAC_REG1_c0<15:0>
    d2s_test.SSI_write(0x388, 0x0);    //d_WL_DAC_Gain_I_c0<2:0>
    d2s_test.SSI_write(0x388, 0x0);    //d_WL_DAC_Gain_Q_c0<2:0>

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x8, 0x133);    //WB_DAC0_DEM_CTL 0x3233->0x0133 @20170520

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0x378, 0x140);      //d_WL_DAC_REG0_c0<15:0>  0x100->0x140 @20170520
    d2s_test.SSI_write(0x37C, 0x5);    //d_WL_DAC_REG1_c0<15:0>    0x4-> 0x5 @20170520

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x24C, 0x111);      //ABB_WL_DAC_0CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x250, 0x1);    //ABB_WL_DAC_0CH_CTRL_REG
    
    d2s_test.wait(0.00005);
    
    d2s_test.SSI_write(0x250, 0x101);      //ABB_WL_DAC_0CH_CTRL_REG
    
    d2s_test.SSI_write(0x240, 0x111);      //ABB_WL_ADC_0CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x244, 0x0);        //ABB_WL_ADC_0CH_CTRL_REG
               
    d2s_test.SSI_write(0x258, 0x111);   //ABB_WL_ADC_1CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x25C, 0x0);     //ABB_WL_ADC_1CH_CTRL_REG
        
    d2s_test.SSI_write(0x264, 0x111);      //ABB_WL_DAC_1CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x268, 0x0);    //ABB_WL_DAC_1CH_CTRL_REG
    
    d2s_test.wait(0.00005);

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x7);    //PKTMEM_MODE_CFG
    d2s_test.SSI_write(0x2FC, 0x1);    //ABB_CALI_MODE

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x1);    //PKTMEM_SEL

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x17);   //PKTMEM_MODE_CFG
    
    d2s_test.wait(0.0001);
    
    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2E4, 0xF); //DIG_CTRL
    d2s_test.SSI_write(0x2E0, 0xC);
    d2s_test.SSI_write(0x2E4, 0x0);
    d2s_test.SSI_write(0x2E4, 0xF);

    d2s::d2s_LABEL_END();
}


void WL_DAC_C1_LPF_Module() {

    //File:  Hi1151 V200 Pilot ABB reg.xlsx
    //Sheet: WIFI_DAC_CH1+LPF
    ////File time: 5/15/2017, update to this version.
    //no need to change CMU @2017-05-22
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x40, false);
//    d2s_test.SSI_write(0x308, 0x220);      //CMU Driver
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);
    d2s_test.SSI_write(0x33C, 0x19B);      //CMU_RESERVE

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x58, 0x330);   //S19&S11
    d2s_test.SSI_write(0x68, 0xC);     //S27
    d2s_test.SSI_write(0x54, 0x0);     //mux rf reg
    d2s_test.SSI_write(0x5C, 0x0);     //mux rf reg
    d2s_test.SSI_write(0x60, 0x0);     //mux rf reg
    d2s_test.SSI_write(0x64, 0x0);     //mux rf reg
    d2s_test.SSI_write(0x6C, 0x0);     //mux rf reg
    d2s_test.SSI_write(0x8, 0x2);      //d_wl_tx_gain_ctrl_mode_c1
    d2s_test.SSI_write(0x0, 0x0);      //wl_trx_reg0
    d2s_test.SSI_write(0x4, 0x2);      //wl_trx_reg1 @20170825 3->2
    d2s_test.SSI_write(0xC, 0x3F);     //wl_trx_reg3
    d2s_test.SSI_write(0x10, 0x3F);        //wl_trx_reg4
    d2s_test.SSI_write(0x14, 0x400);   //wl_trx_reg5
    d2s_test.SSI_write(0x18, 0x400);   //wl_trx_reg6
    d2s_test.SSI_write(0x1C, 0x101);   //wl_trx_reg7
    d2s_test.SSI_write(0x2C, 0x5);         //wl_trx_reg11
    d2s_test.SSI_write(0x34, 0x400);   //wl_trx_reg13
    d2s_test.SSI_write(0x3C, 0x444);       //wl_trx_reg15
    d2s_test.SSI_write(0x44, 0x5D7);       //wl_trx_reg17
    d2s_test.SSI_write(0x4C, 0x5D7);       //wl_trx_reg19
    d2s_test.SSI_write(0x310, 0x4);        //wl_trx_reg196
    d2s_test.SSI_write(0x314, 0x31);       //wl_trx_reg197
    d2s_test.SSI_write(0x318, 0x31);       //wl_trx_reg198
    d2s_test.SSI_write(0x31C, 0x0);        //wl_trx_reg199
    d2s_test.SSI_write(0x320, 0x0);        //wl_trx_reg200
    d2s_test.SSI_write(0x324, 0x4444);     //wl_trx_reg201
    d2s_test.SSI_write(0x328, 0x140);      //wl_trx_reg202
    d2s_test.SSI_write(0x32C, 0x1133);     //wl_trx_reg203
    d2s_test.SSI_write(0x330, 0x9577);     //wl_trx_reg204
    d2s_test.SSI_write(0x334, 0x52C);      //wl_trx_reg205
    d2s_test.SSI_write(0x338, 0x784);      //wl_trx_reg206
    d2s_test.SSI_write(0x360, 0x31);       //wl_trx_reg216
    d2s_test.SSI_write(0x364, 0x31);       //wl_trx_reg217
    d2s_test.SSI_write(0x368, 0x0);        //wl_trx_reg218
    d2s_test.SSI_write(0x36C, 0x0);        //wl_trx_reg219
    d2s_test.SSI_write(0x370, 0x4444);     //wl_trx_reg220
    d2s_test.SSI_write(0x374, 0x140);      //wl_trx_reg221
    d2s_test.SSI_write(0x378, 0x1133);     //wl_trx_reg222
    d2s_test.SSI_write(0x37C, 0x9577);     //wl_trx_reg223
    d2s_test.SSI_write(0x380, 0x52C);      //wl_trx_reg224
    d2s_test.SSI_write(0x384, 0x784);      //wl_trx_reg225

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0x380, 0x0);    //d_WL_DAC_REG0_c1<15:0>
    d2s_test.SSI_write(0x384, 0x0);    //d_WL_DAC_REG1_c1<15:0>
    d2s_test.SSI_write(0x388, 0x0);    //d_WL_DAC_Gain_I_c1<2:0>
    d2s_test.SSI_write(0x388, 0x0);    //d_WL_DAC_Gain_Q_c1<2:0>

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0xC, 0x33);    //WB_DAC1_DEM_CTL  0x3233->0x0133 @20170520 CLA2 config from 133-33

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0x380, 0x140);      //d_WL_DAC_REG0_c1<15:0>  0x100->0x140 @20170520
    d2s_test.SSI_write(0x384, 0x5);    //d_WL_DAC_REG1_c1<15:0>   0x4->0x5 @20170520

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x264, 0x111);      //ABB_WL_DAC_1CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x268, 0x1);    //ABB_WL_DAC_1CH_CTRL_REG
    
    d2s_test.wait(0.00005);
    
    d2s_test.SSI_write(0x268, 0x101);      //ABB_WL_DAC_1CH_CTRL_REG
       
    d2s_test.SSI_write(0x240, 0x111);      //ABB_WL_ADC_0CH_CTRL_REG_SEL  @20170525
    d2s_test.SSI_write(0x244, 0x0);        //ABB_WL_ADC_0CH_CTRL_REG
         
    d2s_test.SSI_write(0x258, 0x111);   //ABB_WL_ADC_1CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x25C, 0x0);     //ABB_WL_ADC_1CH_CTRL_REG
        
    d2s_test.SSI_write(0x24C, 0x111);   //ABB_WL_DAC_0CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x250, 0x0);    //ABB_WL_DAC_0CH_CTRL_REG
    
    d2s_test.wait(0.00005);

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x8);    //PKTMEM_MODE_CFG
    d2s_test.SSI_write(0x2FC, 0x4);    //ABB_CALI_MODE

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x1);    //PKTMEM_SEL

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x18);   //PKTMEM_MODE_CFG
    
    d2s_test.wait(0.0001);
    
    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2E4, 0xF); //DIG_CTRL
    d2s_test.SSI_write(0x2E0, 0xC);
    d2s_test.SSI_write(0x2E4, 0x0);
    d2s_test.SSI_write(0x2E4, 0xF);

    d2s::d2s_LABEL_END();
}


void WL_DAC_DEM_C1_LPF_Module() {

    //File:  Hi1151 V200 Pilot ABB reg.xlsx
    //Sheet: WIFI_DAC_CH1+LPF
    ////File time: 5/15/2017, update to this version.
    //no need to change CMU @2017-05-22
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x40, false);
//    d2s_test.SSI_write(0x308, 0x230);      //CMU Driver
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x40, false);
    d2s_test.SSI_write(0x33C, 0x19B);      //CMU_RESERVE

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x58, 0x330);   //S19&S11
    d2s_test.SSI_write(0x68, 0xC);     //S27
    d2s_test.SSI_write(0x54, 0x0);     //mux rf reg
    d2s_test.SSI_write(0x5C, 0x0);     //mux rf reg
    d2s_test.SSI_write(0x60, 0x0);     //mux rf reg
    d2s_test.SSI_write(0x64, 0x0);     //mux rf reg
    d2s_test.SSI_write(0x6C, 0x0);     //mux rf reg
    d2s_test.SSI_write(0x8, 0x2);      //d_wl_tx_gain_ctrl_mode_c1
    d2s_test.SSI_write(0x0, 0x0);      //wl_trx_reg0
    d2s_test.SSI_write(0x4, 0x2);      //wl_trx_reg1 @20170825 3->2
    d2s_test.SSI_write(0xC, 0x3F);     //wl_trx_reg3
    d2s_test.SSI_write(0x10, 0x3F);        //wl_trx_reg4
    d2s_test.SSI_write(0x14, 0x400);   //wl_trx_reg5
    d2s_test.SSI_write(0x18, 0x400);   //wl_trx_reg6
    d2s_test.SSI_write(0x1C, 0x101);   //wl_trx_reg7
    d2s_test.SSI_write(0x2C, 0x5);         //wl_trx_reg11
    d2s_test.SSI_write(0x34, 0x400);   //wl_trx_reg13
    d2s_test.SSI_write(0x3C, 0x444);       //wl_trx_reg15
    d2s_test.SSI_write(0x44, 0x5D7);       //wl_trx_reg17
    d2s_test.SSI_write(0x4C, 0x5D7);       //wl_trx_reg19
    d2s_test.SSI_write(0x310, 0x4);        //wl_trx_reg196
    d2s_test.SSI_write(0x314, 0x31);       //wl_trx_reg197
    d2s_test.SSI_write(0x318, 0x31);       //wl_trx_reg198
    d2s_test.SSI_write(0x31C, 0x0);        //wl_trx_reg199
    d2s_test.SSI_write(0x320, 0x0);        //wl_trx_reg200
    d2s_test.SSI_write(0x324, 0x4444);     //wl_trx_reg201
    d2s_test.SSI_write(0x328, 0x140);      //wl_trx_reg202
    d2s_test.SSI_write(0x32C, 0x1133);     //wl_trx_reg203
    d2s_test.SSI_write(0x330, 0x9577);     //wl_trx_reg204
    d2s_test.SSI_write(0x334, 0x52C);      //wl_trx_reg205
    d2s_test.SSI_write(0x338, 0x784);      //wl_trx_reg206
    d2s_test.SSI_write(0x360, 0x31);       //wl_trx_reg216
    d2s_test.SSI_write(0x364, 0x31);       //wl_trx_reg217
    d2s_test.SSI_write(0x368, 0x0);        //wl_trx_reg218
    d2s_test.SSI_write(0x36C, 0x0);        //wl_trx_reg219
    d2s_test.SSI_write(0x370, 0x4444);     //wl_trx_reg220
    d2s_test.SSI_write(0x374, 0x140);      //wl_trx_reg221
    d2s_test.SSI_write(0x378, 0x1133);     //wl_trx_reg222
    d2s_test.SSI_write(0x37C, 0x9577);     //wl_trx_reg223
    d2s_test.SSI_write(0x380, 0x52C);      //wl_trx_reg224
    d2s_test.SSI_write(0x384, 0x784);      //wl_trx_reg225

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0x380, 0x0);    //d_WL_DAC_REG0_c1<15:0>
    d2s_test.SSI_write(0x384, 0x0);    //d_WL_DAC_REG1_c1<15:0>
    d2s_test.SSI_write(0x388, 0x0);    //d_WL_DAC_Gain_I_c1<2:0>
    d2s_test.SSI_write(0x388, 0x0);    //d_WL_DAC_Gain_Q_c1<2:0>

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0xC, 0x133);    //WB_DAC1_DEM_CTL  0x3233->0x0133 @20170520

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x94, false);
    d2s_test.SSI_write(0x380, 0x140);      //d_WL_DAC_REG0_c1<15:0>  0x100->0x140 @20170520
    d2s_test.SSI_write(0x384, 0x5);    //d_WL_DAC_REG1_c1<15:0>   0x4->0x5 @20170520

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x264, 0x111);      //ABB_WL_DAC_1CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x268, 0x1);    //ABB_WL_DAC_1CH_CTRL_REG
    
    d2s_test.wait(0.00005);
    
    d2s_test.SSI_write(0x268, 0x101);      //ABB_WL_DAC_1CH_CTRL_REG
       
    d2s_test.SSI_write(0x240, 0x111);      //ABB_WL_ADC_0CH_CTRL_REG_SEL  @20170525
    d2s_test.SSI_write(0x244, 0x0);        //ABB_WL_ADC_0CH_CTRL_REG
         
    d2s_test.SSI_write(0x258, 0x111);   //ABB_WL_ADC_1CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x25C, 0x0);     //ABB_WL_ADC_1CH_CTRL_REG
        
    d2s_test.SSI_write(0x24C, 0x111);   //ABB_WL_DAC_0CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x250, 0x0);    //ABB_WL_DAC_0CH_CTRL_REG
    
    d2s_test.wait(0.00005);

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x8);    //PKTMEM_MODE_CFG
    d2s_test.SSI_write(0x2FC, 0x4);    //ABB_CALI_MODE

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2CC, 0x1);    //PKTMEM_SEL

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0xA0, false);
    d2s_test.SSI_write(0x2F8, 0x18);   //PKTMEM_MODE_CFG
    
    d2s_test.wait(0.0001);
    
    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2E4, 0xF); //DIG_CTRL
    d2s_test.SSI_write(0x2E0, 0xC);
    d2s_test.SSI_write(0x2E4, 0x0);
    d2s_test.SSI_write(0x2E4, 0xF);

    d2s::d2s_LABEL_END();
}


void PHY_ABB_RF_Reset_Module() {

    //File:  Hi1151V200_SSI_Setting_Process.xlsx
    //Sheet: PHY_ABB_RF_reset
    //File time: 5/24/2017 7:16:17 AM
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x0, 0x33);     //SOFT_RESET
    d2s_test.wait(0.00001);
    d2s_test.SSI_write(0x0, 0x3C);     //SOFT_RESET
    d2s_test.wait(0.00001);

    d2s_test.SSI_write(0x200, 0x2000, false);        //0x2001 -> 0x2000 2017-05-27
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x278, 0x3);    //RF_REG_CLK_EN
    d2s_test.SSI_write(0x274, 0x0);    //WL_RF_ABB_REG_RST_CFG
    d2s_test.wait(0.00001);
    d2s_test.SSI_write(0x274, 0x1);    //WL_RF_ABB_REG_RST_CFG
    d2s_test.wait(0.00001);
    d2s_test.SSI_write(0x278, 0x0);    //RF_REG_CLK_EN

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x0, false);
    d2s_test.SSI_write(0x128, 0x0);    //RF_PLL_RST_CFG
    d2s_test.wait(0.00001);
    d2s_test.SSI_write(0x128, 0x1);    //RF_PLL_RST_CFG
    d2s_test.wait(0.00001);

    d2s_test.SSI_write(0x154, 0x0);    //ABB_CALI_RST_CFG
    d2s_test.wait(0.00001);
    d2s_test.SSI_write(0x154, 0x1);    //ABB_CALI_RST_CFG
    d2s_test.wait(0.00001);

    d2s_test.SSI_write(0x200, 0x2001, false);
    d2s_test.SSI_write(0x202, 0x4, false);
    d2s_test.SSI_write(0x2E4, 0xF);    //ABB_CALI_RST_MAN
    d2s_test.SSI_write(0x2E0, 0xF);    //ABB_CALI_RST_SEL
    d2s_test.SSI_write(0x2E4, 0x0);    //ABB_CALI_RST_MAN
    d2s_test.wait(0.00001);
    d2s_test.SSI_write(0x2E4, 0xF);    //ABB_CALI_RST_MAN
    d2s_test.wait(0.00001);
    d2s_test.SSI_write(0x2E0, 0x0);    //ABB_CALI_RST_SEL

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x84, 0x0);      //RF_TRX_REG33, Defalut value//s bug
    d2s_test.wait(0.00001);
    
    d2s::d2s_LABEL_END();
}


void WL_ADC_C0_BeforeCap_Module() {
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x0, 0x0);      //RF reg0
    d2s_test.SSI_write(0x4, 0x0);      //RF reg1
    d2s_test.SSI_write(0x8, 0x0);      //RF reg2
    d2s_test.SSI_write(0xC, 0x0);      //RF reg3
    d2s_test.SSI_write(0x10, 0x0);     //RF reg4
    d2s_test.SSI_write(0x14, 0x0);     //RF reg5
    d2s_test.SSI_write(0x18, 0x0);     //RF reg6
    d2s_test.SSI_write(0x68, 0x3);     //S25
    d2s_test.SSI_write(0x6C, 0x300);   //S0B
    d2s_test.SSI_write(0x5C, 0x3);     //S20
    d2s_test.SSI_write(0x54, 0xF);     //S08&S00
    d2s_test.SSI_write(0x58, 0x0);     //muxreg
    d2s_test.SSI_write(0x60, 0x0);     //muxreg
    d2s_test.SSI_write(0x64, 0x0);     //muxreg

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x240, 0x111);      //ABB_WL_ADC_0CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x244, 0x1);        //ABB_WL_ADC_0CH_CTRL_REG
    
    d2s_test.wait(0.00005);
    
    d2s_test.SSI_write(0x244, 0x101);      //ABB_WL_ADC_0CH_CTRL_REG
        
    d2s_test.SSI_write(0x258, 0x111);   //ABB_WL_ADC_1CH_CTRL_REG_SEL  @20170525
    d2s_test.SSI_write(0x25C, 0x0);     //ABB_WL_ADC_1CH_CTRL_REG
    
    d2s_test.SSI_write(0x24C, 0x111);   //ABB_WL_DAC_0CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x250, 0x0);     //ABB_WL_DAC_0CH_CTRL_REG
    
    d2s_test.SSI_write(0x264, 0x111);      //ABB_WL_DAC_1CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x268, 0x0);    //ABB_WL_DAC_1CH_CTRL_REG
    
    d2s_test.wait(0.00005);
    
    d2s::d2s_LABEL_END();
}


void WL_ADC_C1_BeforeCap_Module() {
    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;    
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s_test.SSI_write(0x0, 0x0);      //RF reg0  0x3->0 20170508
    d2s_test.SSI_write(0x4, 0x0);      //RF reg1
    d2s_test.SSI_write(0x8, 0x0);      //RF reg2  0x3->0 20170508
    d2s_test.SSI_write(0xC, 0x0);      //RF reg3
    d2s_test.SSI_write(0x10, 0x0);     //RF reg4
    d2s_test.SSI_write(0x14, 0x0);     //RF reg5  0x3400->0 20170508
    d2s_test.SSI_write(0x18, 0x0);     //RF reg6  0x3400->0 20170508
    d2s_test.SSI_write(0x68, 0xC);     //S25
    d2s_test.SSI_write(0x6C, 0x0);     //S0B
    d2s_test.SSI_write(0x5C, 0x0);     //S20
    d2s_test.SSI_write(0x58, 0x3C);    //S18&S10
    d2s_test.SSI_write(0x54, 0x0);     //mux reg
    d2s_test.SSI_write(0x60, 0x0);     //mux reg
    d2s_test.SSI_write(0x64, 0x0);     //mux reg

    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x80, false);
    d2s_test.SSI_write(0x258, 0x111);      //ABB_WL_ADC_1CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x25C, 0x1);    //ABB_WL_ADC_1CH_CTRL_REG
    
    d2s_test.wait(0.00005);
    
    d2s_test.SSI_write(0x25C, 0x101);      //ABB_WL_ADC_1CH_CTRL_REG
    
    d2s_test.SSI_write(0x240, 0x111);      //ABB_WL_ADC_0CH_CTRL_REG_SEL  @20170525
    d2s_test.SSI_write(0x244, 0x0);        //ABB_WL_ADC_0CH_CTRL_REG
      
    d2s_test.SSI_write(0x24C, 0x111);   //ABB_WL_DAC_0CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x250, 0x0);     //ABB_WL_DAC_0CH_CTRL_REG
    
    d2s_test.SSI_write(0x264, 0x111);      //ABB_WL_DAC_1CH_CTRL_REG_SEL
    d2s_test.SSI_write(0x268, 0x0);    //ABB_WL_DAC_1CH_CTRL_REG
    
    d2s_test.wait(0.00005);
    
    d2s::d2s_LABEL_END();
}

