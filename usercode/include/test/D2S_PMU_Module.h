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


void LDO_Module();
void CMU_Module();
void PCIE_EP_LB_Module();
void WL_2G_PLL_Sweep_Module(CSiteLong* pReadValue);
void WL_5G_PLL_Sweep_Module(CSiteLong* pReadValue);


#endif	/* D2S_PMU_MODULE_H */

