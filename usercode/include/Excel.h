// Excel.h : Excel DLL 的主头文件
//

#pragma once

#define WLAN_RX_2G_L_Freq 2412 * 1E6
#define WLAN_RX_2G_M_Freq 2442 * 1E6
#define WLAN_RX_2G_H_Freq 2472 * 1E6

#define WLAN_RX_5G_A_Freq 4950 * 1E6
#define WLAN_RX_5G_B_Freq 5250 * 1E6
#define WLAN_RX_5G_C_Freq 5580 * 1E6
#define WLAN_RX_5G_D_Freq 5725 * 1E6

#define WLAN_TX_5G_B1_Freq 4950 * 1E6
#define WLAN_TX_5G_B2_Freq 5210 * 1E6
#define WLAN_TX_5G_B3_Freq 5290 * 1E6
#define WLAN_TX_5G_B4_Freq 5540 * 1E6
#define WLAN_TX_5G_B5_Freq 5620 * 1E6
#define WLAN_TX_5G_B6_Freq 5680 * 1E6
#define WLAN_TX_5G_B7_Freq 5785 * 1E6

typedef enum 
{
	TX_Path,
    RX_Path,
    PMU_Mode,
    ADC_Path,
    DAC_Path
}emTRX;typedef enum 
{
	Sig_NULL,
	Sig_ST,
    Sig_DT,
    Sig_MOD,
	Sig_TRIG
}emSigtype;typedef enum{
    WLAN_2G_Mode,
    WLAN_5G_Mode
}emMode;typedef enum{
    //WLAN 2G Part
    WLAN_2G_RX_L_Band,
    WLAN_2G_RX_M_Band,
    WLAN_2G_RX_H_Band,
    //WLAN 5G Part
    WLAN_5G_RX_A_Band,
    WLAN_5G_RX_B_Band,
    WLAN_5G_RX_C_Band,
    WLAN_5G_RX_D_Band
}emRX_Band;typedef enum{ 
    //WLAN 2G Part
    WLAN_2G_TX_L_Band = 10,
    WLAN_2G_TX_M_Band = 11,
    WLAN_2G_TX_H_Band = 12,
    //WLAN 5G Part
    WLAN_5G_TX_B1_Band = 13,
    WLAN_5G_TX_B2_Band = 14,
    WLAN_5G_TX_B3_Band = 15,
    WLAN_5G_TX_B4_Band = 16,
    WLAN_5G_TX_B5_Band = 17,
    WLAN_5G_TX_B6_Band = 18,
    WLAN_5G_TX_B7_Band = 19
}emTX_Band;typedef struct
{
	int iCol_Name;
	int iCol_Parameter;
    int iCol_WLBand;
    int iCol_Channel;
    int iCol_BW;
    
    int iCol_RXFreq;
    int iCol_Reg;
    int iCol_P1;
    int iCol_Df1;
    int iCol_P2;
    int iCol_Df2;

    int iCol_GainSetRF;
    int iCol_GainSetBPF;
    int iCol_GainSetVGA;
    
    int iCol_ADC_SampleRate;
    int iCol_ADC_SampleSize;
    int iCol_ADC_Vpp;
    
    int iCol_SampleRate;
    int iCol_SampleSize;
    int iCol_Amp;
    int iCol_CalFreq;
    
    int iCol_WLTXPort;
    int iCol_TXBand;
    int iCol_TXBBFreq;
    int iCol_LevelRms;
    
    int iCol_IFFreq;
    int iCol_IFFilter;
    int iCol_MWCapTSD;
    int iCol_MWSrcTSD;
    int iCol_DFTMode;
    
    int iCol_AnaSrcSampleRate;
    int iCol_AnaSrcSampleSize;
    int iCol_AnaSrcAmp;
    int iCol_AnaSrcCalFreq;
    
    int iCol_Cycle;
    int iCol_ComModeVol;
    int iCol_WaveI;
    int iCol_WaveQ;
    
    
    int iCol_ABBSampleRate;
    int iCol_SigFreq;
    int iCol_StartFreq;
    int iCol_StopFreq;
    int iCol_Vpp;
    int iCol_DivideNum;
}tyPlanSheet,*ptyPlanSheet;

typedef struct
{
	double dP1;
    double dDf1;
    double dP2;
    double dDf2;
    double dGainSet_RF;
    double dGainSet_BPF;
    double dGainSet_VGA;
}tyRXTestPlan,*ptyRXTestPlan;

typedef struct
{
	double d2Tone_L;
    double d2Tone_R;
    long dFreqSpacing;
    double dLevelRms;
}tyTXTestPlan,*ptyTXTestPlan;

typedef struct
{
	long iDivideNum;
    double dABBSampleRate;
    double dSigFreq;
    double dVpp;
    double dStartFreq;
    double dStopFreq;
}tyABBTestPlan,*ptyABBTestPlan;

typedef struct
{
	double dADCSampleRate;
    double dADCSampleSize;
    double dADCVpp;
}tyRXADCSet,*ptyRXADCSet;

typedef struct
{
	double dSampleRate;
    double dSampleSize;
    double dAmp;
    double dCalFreq;
    
    double dIFFreq;
    double dIFFilter;
    char *cMWCapTSD;
    bool bDFTMode;
    
    char *cI_CapPin_P;
    char *cI_CapPin_N;
    char *cQ_CapPin_P;
    char *cQ_CapPin_N;
    char *cRF_CapPin;
}tyCapSigSetting,*ptyCapSigSetting;

typedef struct
{
	char *cMWSrcTSD;
    
    double dAnaSrcSampleRate;
    double dAnaSrcSampleSize;
    double dAnaSrcAmp0;
	double dAnaSrcAmp1;
    double dAnaSrcCalFreq;

    double iCycle;
    double dComModeVol;
    char *cWaveI0;
	char *cWaveI1;
    char *cWaveQ0;
	char *cWaveQ1;
    
    char *cI_SrcPin_P;
    char *cI_SrcPin_N;
    char *cQ_SrcPin_P;
    char *cQ_SrcPin_N;
    char *cRF_SrcPin;
}tySrcSigSetting,*ptySrcSigSetting;

typedef struct
{
	// rx
	char *cStandard;
	long BW;

}tyAnaModCap,*ptyAnaModCap;

typedef struct
{
	//tx
	char *cStandard;
	long BW;
}tyRfModCap,*ptyRfModCap;

typedef struct
{
	char *plTestName;
	char *plMode;
	char *plPath;
	char *plBand;
	char *plChannel;
	double plLossArray[8];
}tyPathloss,*ptyPathloss;

typedef struct
{
	char *cTestName;	
    char *cRxFreq;
    char *cChannel;
                
    double dLO_Freq;
    long iMode;
    emTRX iTRX;
    long iBand;
    
    char *cGainMode;
    double dBW;
    
    long iLNA_Stage_Num;
    bool bComplexGain;
    long iIIPX_Order;
    
    char *cPreRegister;
    char *cPostRegister;
    
    char *cSrcSig;
    char *cCapSig;
    
    tyRXTestPlan tyRXTest; 
    tyTXTestPlan tyTXTest;
    tyABBTestPlan tyABBTest;
   
    //tyRXADCSet tyRXADC;
    tyCapSigSetting tyCapSigSet;
    tySrcSigSetting tySrcSigSet;

	tyAnaModCap AnaModCap;
	tyRfModCap RfModCap;

	emSigtype Sigtype;

	tyPathloss plInfo;
}tyTestData,*ptyTestData;

typedef struct
{
	tyTestData *testData;
	long lDataLength;
}tyTestDatas,*ptyTestDatas;

/*
* description : get whole table data
* return : 0 == success,-1 == initExcelFail,-2 == openExcelFail,-3 == loadSheetFail
*/
extern "C" __declspec(dllexport) int Get_TestDatas(char *xlsxPath, char *pathlossPath, tyTestDatas &testDatas);

