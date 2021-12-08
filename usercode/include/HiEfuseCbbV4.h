/*
 * HiEfuseCbbV4.hpp
 *
 *  Created on: Jun 2, 2015
 *      Author: s195165
 */
#ifndef HIEFUSECBBV4_HPP_
#define HIEFUSECBBV4_HPP_
//#include "testmethod.hpp"
//#include "mUserAPI.hpp"
//#include "tpi_c.h"
#include "LibHiEfuseCbbV4.h"

//using namespace MuTest;
using namespace std;

//#include "LibHiEfuseCbbV4.hpp"
#define HiEfuseCbbV4_HppVer 4030001

#define MULT_DIE_NUM 3
#define MAX_EFUSE_TOTAL_LEN 10240
#define MAX_EFUSE_ITEM_NUM  3000
#define MAX_MULT_SITE_NUM 16

extern STR_HISI_EFUSE_TABLE mStrHisiEfuseTable[MULT_DIE_NUM][MAX_EFUSE_ITEM_NUM+1];
extern STR_HISI_EFUSE_DATA mStrHisiEfuseData[MULT_DIE_NUM][MAX_MULT_SITE_NUM][MAX_EFUSE_ITEM_NUM];
extern STR_HISI_EFUSE_DIE_TABLE mStrHisiEfuseDieTable[MULT_DIE_NUM];

extern DIEID_INFO glbDieIDInfoForECID[MULT_DIE_NUM][MAX_MULT_SITE_NUM];
extern EFUSE_ProdDataMonitor vecProdDataMonitor[MULT_DIE_NUM][MAX_EFUSE_ITEM_NUM];

extern int glbCalc_MAX_SITE_NUM;
extern int glbCalc_MULT_DIE_NUM;

extern int glb_CSVDisposed;
extern int glb_OTPCSVDisposed;
extern int glb_firstECIDRecord;
extern string glb_testSuitefirstECID;
extern int glb_ECIDIndex;

extern map<string,unsigned long> UbitMap;


//extern void EFUSE_ITEM_UPDATE(
//		 const char cItemName[],
//		 int site_index,
//		 double dTestData,
//		 double dRefData);
//
//extern unsigned int GET_EFUSE_ITEM_CODE(
//		 const char cItemName[],
//		 int site_index);
//
//extern double GET_EFUSE_ITEM_DATA(
//		 const char cItemName[],
//		 int site_index);

extern void UpdateWriteBufferToVector(
                API *api,
		STR_HISI_EFUSE_DIE_TABLE mStrHisiEfuseDieTab,
		const char EfusePgmPin[],
		const char EfusePgmLabel[],
		bool WriteBuffer[]);

extern int UpdateVectorToReadBuffer(
                API *api,
		STR_HISI_EFUSE_DIE_TABLE mStrHisiEfuseDieTab,
		bool ReadBuffer[]);

extern void ResetWriteBufferToVector(
                API *api,
                STR_HISI_EFUSE_DIE_TABLE mStrHisiEfuseDieTab,
                const char EfusePgmPin[],
                const char EfusePgmLabel[]);

//extern void MULT_EFUSE_ITEM_UPDATE(
//		 const char cItemName[],
//		 int DieNum,
//		 int site_index,
//		 double dTestData,
//		 double dRefData);
//
//
//extern unsigned int GET_MULT_EFUSE_ITEM_CODE(
//		 const char cItemName[],
//		 int DieNum,
//		 int site_index);
//
//
//extern double GET_MULT_EFUSE_ITEM_DATA(
//		 const char cItemName[],
//		 int DieNum,
//		 int site_index);

extern void EFUSE_ITEM_UPDATE(
                const char cItemName[],
                //int DieNum,
                int site_index,
                double dTestData,
                int iDebug);

extern void EFUSE_ITEM_UPDATE(
                const char cItemName[],
                //int DieNum,
                int site_index,
                double dTestData,
                double dRefData,
                int iDebug);

extern void EFUSE_ITEM_UPDATE(
                const char cItemName[],
                //int DieNum,
                int site_index,
                double dTestData,
                double dRefData,
                double dDM_Data,
                int iDebug);

extern unsigned int GET_EFUSE_ITEM_CODE(
                const char cItemName[],
                //int DieNum,
                int site_index);

extern double GET_EFUSE_ITEM_DATA(
                const char cItemName[],
                //int DieNum,
                int site_index);

extern unsigned int GET_EFUSE_ITEM_CODE_WR(
                const char cItemName[],
                //int DieNum,
                int site_index);

extern unsigned int GET_EFUSE_ITEM_CODE_RD(
                const char cItemName[],
                //int DieNum,
                int site_index);

extern double GET_EFUSE_ITEM_TEST_DATA(
                const char cItemName[],
                //int DieNum,
                int site_index);

extern double GET_EFUSE_ITEM_FEF_DATA(
                const char cItemName[],
                //int DieNum,
                int site_index);

extern void MULT_EFUSE_ITEM_UPDATE(
                const char cItemName[],
                int DieNum,
                int site_index,
                double dTestData,
                int iDebug);

extern void MULT_EFUSE_ITEM_UPDATE(
                const char cItemName[],
                int DieNum,
                int site_index,
                double dTestData,
                double dRefData,
                int iDebug);

extern void MULT_EFUSE_ITEM_UPDATE(
                const char cItemName[],
                int DieNum,
                int site_index,
                double dTestData,
                double dRefData,
                double dDM_Data,
                int iDebug);

extern unsigned int GET_MULT_EFUSE_ITEM_CODE(
                const char cItemName[],
                int DieNum,
                int site_index);

extern double GET_MULT_EFUSE_ITEM_DATA(
                const char cItemName[],
                int DieNum,
                int site_index);

extern unsigned int GET_MULT_EFUSE_ITEM_CODE_WR(
                const char cItemName[],
                int DieNum,
                int site_index);

extern unsigned int GET_MULT_EFUSE_ITEM_CODE_RD(
                const char cItemName[],
                int DieNum,
                int site_index);

extern double GET_MULT_EFUSE_ITEM_TEST_DATA(
                const char cItemName[],
                int DieNum,
                int site_index);

extern double GET_MULT_EFUSE_ITEM_REF_DATA(
                const char cItemName[],
                int DieNum,
                int site_index);

extern void PUT_MULT_EFUSE_ITEM_CODE_RD(
                const char cItemName[],
                int DieNum,
                int site_index,
                unsigned int datain);

extern void PUT_MULT_EFUSE_ITEM_CODE_WR(
                const char cItemName[],
                int DieNum,
                int site_index,
                unsigned int datain);

extern void HiEFUSE_IRC(
                API *api,
                string FlowTempFlag,
                string FlowBurnFlag,
                string FlowFuncFlag,
                string FlowFuncPart,   
                string PreCheckFlows,
                string DieLotIDMixChk_YN,
                int    DieNum,
                string HardBinByPass,
                string mStrSoftBinNum,
                string output,
                string strFNameIn_ItemTab,
                string strFNameIn_DieTab,
                string strRdInFileEachTest,
                string strRecordECID_YesNo,

                int iRecordECID_DieIndex,
                int iDebug
);
extern void HiEFUSE_PRC(
                API *api,
                int DieNum,
                string HardBinByPass,
                string mStrSoftBinNum,
                string mStr_DMSoftBinNum,
                string output,
                int iDebug
);
extern void HiEFUSE_PGM(
                API *api,
                int DieNum,
                string EFUSE_PGM_PIN,
                string EFUSE_PGM_LABEL,
        
                int PowerVcoef_EN,
                string PowerVcoef,
                string VDDQ_EFUSE,
        
                int UTIL_EN,
                string UTIL_VDDQ,
        
                string mStrSoftBinNum,
                int iDebug
);
extern void HiEFUSE_REPGM_FFLAG(
                API *api,
                int DieNum,
                string mStrSoftBinNum,
                int iDebug
);
extern void HiEFUSE_OTC(
            API *api,
            int DieNum,
            string  mStrSoftBinNum,
            string  output,
            int iDebug
);
extern void HiEFUSE_FRC(
                API *api,
                int DieNum,
                string mStrSoftBinNum,
                string para_StrSBinDieIDFilter,
                string output,
                int iDebug
);


//- - - - - - - - - UBIT control - - - - - - - - - - - - - - - - - - - - -
void ActiveUbit(
        API *api,
        string Ubit,
        bool UbitOnorOff);

//- - - - - - - - - - - - - -DC_Value_change- - - - - - - - - - -  -  - - - - - -
extern void DPS_ForceV(
        API *api,
        const char * powerblock,
        const char * signal,
        double DCvalue,double ratio);

//- - - - - - - - - - - - delay time- - - - - - - - - - - -  - - - - - - - - -
extern void WAIT_TIME(
        API *api,
        double delay_time_S);

//- - - - - - - - - - - - Get_cur_dctestblock_name- - - - - - - - - - - - - - - 
extern const char* MyGet_PowerName(
        API *api);

extern void Change_pattern(
        API *api,
        const char * patternblock,
        const char * signal,
        unsigned long first_vector,
        unsigned long vector_count,
        unsigned long *data);

//void func_DIGITAL_CAPTURE_TEST(
//        API *api,
//        string strPatName);

extern void DIGITAL_CAPTURE_TEST(
        API *api,
        const char *pCharPatName);

#endif /* HIEFUSECBBV3_HPP_ */
