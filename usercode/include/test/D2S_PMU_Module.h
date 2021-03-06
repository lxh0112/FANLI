/* 
 * File:   D2S_PMU_Module.h
 * Author: dzr
 *
 * Created on 2020年11月4日, 下午4:39
 */

#ifndef D2S_PMU_MODULE_H
#define	D2S_PMU_MODULE_H
#include "UserAPI.h" 
#include "d2sProtocolSSI.h"
#include "CCS08F.h"
#include "Globle_Var.h"



void CMU_Module();
void TSENSOR_PAmodule();
void BOOST_OFF();
void BOOST_BOOTUP_PAlib();
void Sleep_PAmodule();
void BOOT_UP_PAmodule();
void TSENSOR_PAmodule();
void Poweron_PAModule();
void BOOST_IDLE();
void BOOST_Efuse_RD_const_PAlib_reg_module();
void BOOST_POWERON_PAlib();
void BOOST_W5_PAlib();
void SIMLDO_VCC_PAmodule();
void PMUVCC_SIM_PAmodule();
void BOOST_WR3_const_PAlib();
void Boost_Pwrdown_PAmodule();
void MEMORY_Mode1_PAmodule();
void MEMORY_Mode2_PAmodule();
void MEMORY_Mode3_PAmodule();
void MEMORY_Mode4_PAmodule();
void MEMORY_Mode5_PAmodule();
void DC_IO_VOL_PAmodule();
void DC_IO_VOH_PAmodule();
void DC_IO_VIHL_PAmodule();
void DC_IO_reset_PAmodule();
void READBACK_VIH();
void READBACK_VIL();
void call_NCPU_RESET_Module();
void NFC_ReaderInit();
void NFC_Tx();
void NFC_Tx_MI_CAIL();
void NFC_Tx_MOD();
void NFC_Tx_mode_off();
void NFC_Tx_HP();
void NFC_Tx_PA_OFF();
void NFC_TXP_IMPEDENCE_MIN();
void NFC_TXP_IMPEDENCE_MAX();
void NFC_TXP_IMPEDENCE_reset();
void NFC_Reader_RX_Init();
void NFC_cap_module();
void NFC_swp();
void NFC_swp2();
void NFC_SWIO_RESET();
void NFC_non_cdr_mode();
void NFC_cdr();
void NFC_adpll();
void NFC_adpll_reset();
void NFC_Clk_extra();
void NFC_non_cdr();
void NFC_non_cdr_reset();
void NFC_Fiedlddet_hpmode();
void NFC_Fielddet_read();
void NFC_reset();
void BOOST_RD_block_const_PAlib();
void NFC_Adc_config();
void NFC_abbcap_module();
void NFC_DAC_ADC_Pamodule();
void NFC_VbattoVddio();
void NFC_VddiotoVbat();
void EFUSE_BOOT_UP_PAmodule();
void EFUSE_READ();
void EFUSE_PGM_WRITE();


void PMU_CAPLESS_LDO();
void CMU_TEST();
void ADPLL_TEST_1();
void ADPLL_TEST_2();
void ADPLL_TEST_3();
void CMU_TEST_19p2M_1();
void CMU_TEST_19p2M_2();
void CMU_TEST_19p2M_3();
void CMU_TEST_19p2M_4();
void ADPLL_TEST_27p12M_1();
void ADPLL_TEST_27p12M_2();
void ADPLL_TEST_27p12M_3();
void CMU_TEST_27p12M_1();
void CMU_TEST_27p12M_2();
void CMU_TEST_27p12M_3();
void CMU_TEST_27p12M_4();
void ADPLL_TEST_19p2M_1();
void ADPLL_TEST_19p2M_2();
void ADPLL_TEST_19p2M_3();
void CMU_TEST_38p4M_1();
void CMU_TEST_38p4M_2();
void CMU_TEST_38p4M_3();
void EFUSE_FRC_BST();
void NFC_ADC_108M();
void XO_CMU_TEST_1();
void XO_CMU_TEST_2();
void XO_CMU_TEST_3();


#endif	/* D2S_PMU_MODULE_H */

