/*
 * HiEfuseCbbV4.hpp
 *
 *  Created on: Apr 14, 2015
 *      Author: s00195165
 */

#ifndef LIBHIEFUSECBBV4_HPP_
#define LIBHIEFUSECBBV4_HPP_

#include <fstream>
//#include "mUserAPI.hpp"
//#include "tpi_c.h"
//#include "tml_def.h"
#include "time.h"
#include <iomanip>
#include <cstring>
#include <unistd.h>
#include "string.h"
//#include "libcicpi.h"
//#include "ifaddrs.h"
#include "sys/types.h"
//#include "netinet/in.h"
//#include "arpa/inet.h"
//#include "net/if.h"
//#include "sys/ioctl.h"
//#include "socket.h"
#include <map>
#include <vector>
#include <list>
#include "EFUSE_ProdDataMonitor.h"

//using namespace MuTest;

#define ms *0.001
#define UbitOn 1
#define UbitOff 0
#define Ratio_1 1

#define LibHiEfuseCbbV4_HppVer 4020009
#define csvMAXCharPerLine 1024
#define csvMAXLineNum 10000
#define MAX_PGM_FLOW 32
#define ATE_MIN_Data 0.000000000001

#define SET_MULTIBIN api->Set_result_bin

extern unsigned int  LibHiEfuseCbbV4_CppVer;//=300100;
extern ofstream FileErrorOut;

enum ENUM_TM{
    mGE_LE = 0,
    mPASS = 1,
    mFAIL = 2,
    mLOG = 3,
};

enum ENUM_ITEM_MODE{
	mSTD 				= 0,
	mDIEID 				= 1,
	mIDDQ 				= 2,
	mTSRDIF		 		= 3,
	mTSRABS		 		= 4,
	mFREQBIN			= 5,
	mDATE				= 6,
	mOTG				= 7,
	mPASSFLAG           = 8,
	mCMPU				= 9,
	mORC				= 10,
	mFIX 				= 11,
	mHPM 				= 12,
	mIPADDR 			= 13,
	mPARTGOOD 			= 14,
	mPASSFLAGV2 		= 15,
	mCRC 				= 16,
	mBI 				= 17,
	mFAILFLAG			= 18,
	mINT				= 19,
	mEND                = 100,
	mNULL               = 999,
};

struct STR_HISI_EFUSE_DIE_TABLE{
	int iDieNo;
	char cEfuseContrMode[16];
	unsigned int iEfuseTotalLen;
	unsigned int iEfuseItemNum;
	unsigned int iEfuseMultBitNum;
	int iEfusePgmHighWfIndex;
	int iEfusePgmLowWfIndex;
	int iEfusePgmVecNumInit;
	int iEfusePgmVecDeltaLen;
	int iEfuseWordWidth;
        int iEfusePgmVecRPTNum;
        int iEfusePgmVecRPTDelta;
};

struct STR_HISI_EFUSE_TABLE{
	int iDieNo;
	char cItemName[32];
	ENUM_ITEM_MODE eItemMode;
	unsigned int iPhyAddrLSB;
	unsigned int iPhyAddrLEN;
	unsigned int iItemPgmFlowCnt;
	char cItemPgmFlow[MAX_PGM_FLOW][10];
	double dItemLowLimit;
	double dItemHighLimit;

	string DM_strPreTrimMonitor;
	int DM_iDataBaseMonitor;
	double DM_dDataIn_LLim;
	double DM_dDataIn_HLim;
	double DM_dMean_LLim;
	double DM_dMean_HLim;
	double DM_dS2Sgap_MeanLim;
	double DM_dT2Tgap_MeanLim;
	double DM_dSigma_LLim;
	double DM_dSigma_HLim;
};

struct STR_HISI_EFUSE_DATA{
	bool bItemPgmEnable;
	bool bItemPgmedEnable;
	unsigned int iItemEfuseWriteCode;
	unsigned int iItemEfuseReadCode;
	double dItemTestValue;
	double dItemRefValue;
	double dItemCrcValue;
	unsigned int iItemOtpMode;
};

struct DIEID_INFO{
	unsigned int igrpLotIDValue[255];
	unsigned int iWAFERID;
	int iDIEX;
	int iDIEY;
};




//extern STR_HISI_EFUSE_TABLE aStrHisiEfuseTableItem[];
extern int GetStrHisiEfuseItemLen(STR_HISI_EFUSE_TABLE *);

//extern int ItemPgmEnable(const char cItemPgmFlow[][10],const char cFlowFlag[]);
extern int GetStrHisiEfuseItemLen(STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[]);
extern int GetStrHisiEfuseItemIndex(STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],const char cItemName[]);
extern void UpdateTestDataToEfuseWriteCode(
		 STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		 STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
		 //int site_index,
		 const char cItemName[],
		 double dTestData,
		 double dRefData,
		 int iDebug);

extern void DisplayCurrentItemStrHisiEfsue(
		 STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		 STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
		 const char cItemName[]);

extern void DisplayAllItemStrHisiEfsue(
		 STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		 STR_HISI_EFUSE_DATA aStrHisiEfuseData[]);
extern void InitalStrHisiEfuseData(
		 STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		 STR_HISI_EFUSE_DATA aStrHisiEfuseData[]);
//extern unsigned int PhyAddr2VectorNum(unsigned int PhyAddr);
extern void EfuseBit2ItemRd(
		 STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		 STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
		 bool aEFUSE_BIT[]);

extern int GetOTGEnableResult(
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		STR_HISI_EFUSE_DATA aStrHisiEfuseData[]);

extern int GetOneTimeCheckByBitResult(
		//STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		//STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
		bool aEFUSE_BIT_WR[],
		bool aEFUSE_BIT_RD_PRC[],
		bool aEFUSE_BIT_RD_OTC[],
		int EFUSE_TOTAL_LEN);
extern int GetOneTimeCheckByItemResult(
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		STR_HISI_EFUSE_DATA aStrHisiEfuseData[]);
extern int GetFinalReadCheckByBitResult(bool aEFUSE_BIT_WR[],
								 bool aEFUSE_BIT_RD_PRC[],
								 bool aEFUSE_BIT_RD_OTC[],
								 bool aEFUSE_BIT_RD_FRC[],
								 int EFUSE_TOTAL_LEN);
extern int GetNullUsedFreshBitCheckResult(
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		//STR_HISI_EFUSE_DATA aStrHisiEfuseData[])
		bool aEFUSE_BIT[],
		int EFUSE_TOTAL_LEN,
		int MULT_BIT_NUM);

extern int GetMultBitCheckResult(
		bool aEFUSE_BIT[],
		int EFUSE_TOTAL_LEN,
		int MULT_BIT_NUM);
extern int GetCBBUsedFreshWordCheckResult(
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		STR_HISI_EFUSE_DATA aStrHisiEfuseData[]);

extern int GetEfuseItemZeroPgmEnResult(
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
		const char cFlowFlag[]);

extern int GetPassFlagPgmCrcResult(
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
		const char cFlowFlag[]);
extern char Dec2Char(int value);
extern int Char2Dec(char ch);
extern void UpdateTesterIpToEfuseWriteData(
        API *api,
        STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
	STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
	int iDebug);
extern void UpdateTestDateToEfuseWriteData(
   	 STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
   	 STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
   	 int iDebug);
extern unsigned int PhyAddr2VectorNum(unsigned int PhyAddr,unsigned int VEC_NUM_INIT,unsigned int VEC_DELTA_LEN);


//extern int GetHardBinResult(API *api);
//extern int GetSoftBinResult(API *api);

extern int UpdateDieidToEfuseWriteData(
                API *api,
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
	   	STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
	   	const char* cModeFileStrWaferId,
	   	DIEID_INFO &para_DieIDFromTester,
	   	vector<string> &vec_strLotIDName,
	   	int iDebug);

extern void EfuseItem2BitWr(STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
					 STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
					 bool aEFUSE_BIT_WR[],
					 int EFUSE_TOTAL_LEN,
					 int MULT_BIT_NUM,
					 int PRC_RESULT);

extern void UpdateEfuseDataToVectorMem(const char EFUSE_PGM_PIN[],
								int HIGH_WF_INDEX,
								int LOW_WF_INDEX,
								bool aEFUSE_BIT_WR[],
								int EFUSE_USER_LEN,
								int VEC_NUM_INIT,
								int VEC_DELTA_LEN);


//extern void EfuseItemFRC(
//
//		 STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
//		 STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
//		 bool aEFUSE_BIT[]);
extern int GetDynEfuseReadCheakResult(
		 STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		 //STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
		 int ItemIndex,//const char cItemName[],
		 bool aEFUSE_BIT[]);
//extern int ItemPgmEnablePerFlow(const char cItemPgmFlow[],const char cFlowFlag[]);
extern void UpdateFixItemToEfuseWriteData(
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
	   	STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
	   	int iDebug);
extern void DisplayItemMode(ENUM_ITEM_MODE eItemMode);

extern int UserStrHiEfuseItemCheck(
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		STR_HISI_EFUSE_DIE_TABLE aStrHisiEfuseDieTable,
		vector<string> &vec_strLotIDIn);

extern int EfuseItemPgmCheck(
		 STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		 STR_HISI_EFUSE_DATA aStrHisiEfuseData[]
		                 );
//extern bool FRCEfuseItemTestAndLog(
//		 STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
//		 STR_HISI_EFUSE_DATA aStrHisiEfuseData[],//		 bool aEFUSE_BIT[]);

extern int UserInputCheck(
                API *api,
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		STR_HISI_EFUSE_DIE_TABLE mStrHisiEfuseDieTab,
		int myStrEfuseTableCheck,
		int *ptn,
		const char cCurrentFlow[],
		const char mSoftBinNumberChar[],
		vector<string> &vec_strLotID);

extern void UpdateEfuseItemPgmEnableFlag(
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
		int iFinalFlowFalg,
		const char cFlowFlag[]);
extern int GetIRCandPRCDiffResult(
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		bool IRCbuf[],
		bool PRCbuf[]);
extern int GetReadBufferAll0andAll1CheckResult(
		bool aEFUSE_BIT[],
		int EFUSE_TOTAL_LEN);
extern int FRCEfuseItemTestAndLogWithTn(
                API *api,
                STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
                STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
                bool aEFUSE_BIT[],
                const char mSoftBinNumberChar[],
                const char mCurrFlowName[],
                //const char mPreCheckFlowName[],
                int *ptn,
                int iDebug);

int IRCPreChkEfuseItemTestAndLogWithTn(
                 API *api,
		 STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		 STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
		 bool aEFUSE_BIT[],
		 const char mSoftBinNumberChar[],
		 const char mCurrFlowName[],
		 const char mPreCheckFlowName[],
		 int *ptn,
                 int iDebug);

extern void EfuseItemReadDataLogWithTn(
                API *api,
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
		bool aEFUSE_BIT[],
		const char mProcessChar[],
                const char mSoftBinNumberChar[],
		int *ptn);

extern void EfuseDataByWordLogWithTn(
                API *api,
                bool aEFUSE_BUF[],
                int EfuseTotalLen,
                int WordLen,
                const char mSoftBinNumberChar[],
                int *ptn);

extern int GetDieidFilterResult(
                API *api,
                STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
		vector<string> vecStr_LotIDName,
                char *cgrpSBinNo,
		int DieNum,
                int iDebug);

extern int GetDieidEfuseReadDataCheckResult(
                API *api,
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
	   	STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
	   	const char cModeFileStrWaferId[],
	   	DIEID_INFO &para_DieIDFromTester,
	   	vector<string> &vec_strLotIDName,
	   	int iDebug);

extern int GetLastandCurrentChipIdDiffResult(
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
	   	STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
	   	vector<string> vecStr_LotIDName,
	   	unsigned int LastChipId[],
                int iDebug);

extern int FlowPassFlagPreCheck(
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
		const char cPreCheckFlows[]);

extern void UpdateEfuseFailFlag2BitWr(  STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		 STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
		 bool aEFUSE_BIT_WR[],
		 int EFUSE_TOTAL_LEN,
		 int MULT_BIT_NUM);

extern unsigned int ComputeCrc(unsigned char *CrcBuf,unsigned int nBytes,unsigned int CRCn);
extern unsigned int ComputeCrc32(unsigned char *CrcBuf,unsigned int nBytes);
extern unsigned short ComputeCrc16(unsigned char *CrcBuf,unsigned int nBytes);
extern unsigned char ComputeCrc8(unsigned char *CrcBuf,unsigned int nBytes);
extern unsigned int ComputeCrc4(unsigned char *CrcBuf,unsigned int nBytes);
extern void UpdateExpEfuseData(
		 bool aEFUSE_BIT_WR[],
		 bool aEFUSE_BIT_RD[],
		 bool aEFUSE_BIT_EXP[],
		 int EFUSE_TOTAL_LEN);
extern void UpdateCrcToEfuseWriteBuffer(
                STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
                STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
                bool aEFUSE_BIT_WR[],
                bool aEFUSE_BIT_RD[],
                const int EFUSE_TOTAL_LEN,
                const int MULT_BIT_NUM,
                int iDebug);

extern int GetCrcCheckResult(
                API *api,
                STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
                STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
                bool aEFUSE_BIT_RD[],
                const int EFUSE_TOTAL_LEN,
                const int MULT_BIT_NUM,
                int *ptn,
                int iDebug);

extern void DisplayAllItemStrHisiOtp(
		 STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		 STR_HISI_EFUSE_DATA aStrHisiEfuseData[]);

extern void OtpItem2BitWr(	STR_HISI_EFUSE_TABLE aStrHisiOtpTable[],
		STR_HISI_EFUSE_DATA aStrHisiOtpData[],
		bool bOtpWrBufferPGM[],
		bool bOtpWrBufferDIN[],
		bool bOtpWrBufferWEB[],
		bool bOtpWrBufferCPUMPEN[],
		bool bOtpWrBufferPGMEN[],
		int iOTP_WR_OFF_ADDR,
		int OTP_TOTAL_LEN,
		int MULT_BIT_NUM,
		int PRC_RESULT
		);
extern void OtpFailFalg2BitWr(	STR_HISI_EFUSE_TABLE aStrHisiOtpTable[],
		STR_HISI_EFUSE_DATA aStrHisiOtpData[],
		bool bOtpWrBufferPGM[],
		bool bOtpWrBufferDIN[],
		bool bOtpWrBufferWEB[],
		bool bOtpWrBufferCPUMPEN[],
		bool bOtpWrBufferPGMEN[],
		int iOTP_WR_OFF_ADDR,
		int OTP_WR_LEN,
		int MULT_BIT_NUM
		);
extern int ReadConfigFile(
                API *api,
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		STR_HISI_EFUSE_DIE_TABLE &mStrHisiEfuseDieTab,
		vector<string> &vecLotIDIn,
		string para_strFNameIn_ItemTab,
		string para_strFNameIn_DieTab,
		int para_DieNum,
		int &para_glbMaxDieNo,
		int para_iDebug);

extern bool funcFileLine2Vec(
		ifstream& para_fFileIn,
		vector<string> &para_vecStrOut,
		unsigned int para_iMinColumn,
		unsigned int para_iMaxColumn,
		int para_iCurLineNum,
		string &para_strErrorMsg,
		int &pata_iReadRlt);

extern long EfuseCBB_string2long(
		const string& input,
		string name);

extern double EfuseCBB_string2double(
		string& input,
		string name);

extern int EfuseCBB_splitStr(
		const string& ,
		char sepCh,
		vector<string>& array,
		const bool=true);

extern string EfuseCBB_double2string(
		double double_input,
		int width,
		int precision);

extern string EfuseCBB_int2string(long int_input);

void funcDisplayItemTab(
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		vector<string> vecstr_LotIDIn,
		int para_glbMaxItemNum);

extern void funcDisplayDieTab(STR_HISI_EFUSE_DIE_TABLE &mStrHisiEfuseDieTab);

extern void funcItemTabDieTabInitial(
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		STR_HISI_EFUSE_DIE_TABLE &mStrHisiEfuseDieTab,
		vector<string> &vecLotIDIn,
		int para_iMaxItemNum,
		int para_iMaxPgmFlow);

extern ENUM_ITEM_MODE STRING_2_ENUM(string strInData);

extern int mainWriteDIEIDToPARTTXT(
                API *api,
		DIEID_INFO &para_DieIDForECID,
		vector<string> &vecStr_LotIDName,
		int iDieIndex,
		int iDebug);

extern int WritestrECIDToPARTTXT(
                API *api,
		string strLOTIDIn,
		string strWIDIn,
		string strDIEXIn,
		string strDIEYIn,
		int iDieIndex,
		int iDebug);

extern int funcGetDieIDFromEfuse(
                API *api,
		STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
		STR_HISI_EFUSE_DATA aStrHisiEfuseData[],
		DIEID_INFO &para_DieIDFromEfuse,
		vector<string> &vec_strLotIDName,
		int iDebug);

extern int GetSignUnsignDieXDieY(STR_HISI_EFUSE_TABLE para_HisiEfuseTable[]);

extern string MyGetLotIDFromTester(API *api);

extern int MyGetAutoRunFlag(API *api);

extern string GetStrDieLotID(
    DIEID_INFO &para_DieIDFromEfuse,
    vector<string> vecStr_LotIDName);

int GetCPDieLotIDDiffRlt(
    string &str_FT_LastLotID,
    string &str_FT_CurLotID,
    string &str_CP_LastDieLotID,
    string &str_CP_CurDieLotID,
    int iIRCPassFail);

//UT Function Code
extern int UTTestCode_ReadEfuse(
    int iSite_Index,
    string strTestSuite,
    bool ReadBuffer[],
    STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
    STR_HISI_EFUSE_DATA  aStrHisiEfuseData[],
    int EFUSE_TOTAL_LEN,
    int MULT_BIT_NUM);

int UT_UpdateVectorToReadBuffer(
    string strItemName,
    bool ReadBuffer[],
    STR_HISI_EFUSE_TABLE aStrHisiEfuseTable[],
    STR_HISI_EFUSE_DATA  aStrHisiEfuseData[],
    int EFUSE_TOTAL_LEN,
    int MULT_BIT_NUM);

//void UT_TSensorData_Generation(
//		int para_iSite,
//		ARRAY_D& paraOut_arrayD_Tsensor_RawData,
//		int &para_iloopCnt);

extern int TESTSET(
        API *api,
        long lTestNumber,
        string strTestName,
        ENUM_TM enum_TM_Judge, 
        double dlowlimit,
        double dhighlimit,
        double dTestValue,
        string strSBinNum
);
extern int TESTSET(
        API *api,
        long lTestNumber,
        string strTestName,
        ENUM_TM enum_TM_Judge, 
        double dTestValue,
        string strSBinNum
);
extern int TESTSET(
        API *api,
        long lTestNumber,
        string strTestName,
        ENUM_TM enum_TM_Judge, 
        double dTestValue
);
#endif /* LIBHIEFUSECBBV3_HPP_ */
