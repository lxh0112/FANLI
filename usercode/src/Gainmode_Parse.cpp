#include "Gainmode_Parse.h"
#include "string.h"
#include <stdlib.h>

#include "LogFile.h"

#include <fstream>    
#include <string>
#include <vector>
#include <map>      
using namespace std;

#define MAX_MODE_SITE   (8)

typedef struct{
    string szMode;
    double* pValue;
}GAINMODE,*pGAINMODE;

typedef vector<GAINMODE> CCGAIN;
typedef map<string, CCGAIN> CCBAND;

CGainModeParse::CGainModeParse() 
{
    pBandArray = new CCBAND;
    ((CCBAND*)pBandArray)->clear();
}

CGainModeParse::~CGainModeParse() 
{
    ((CCBAND*)pBandArray)->clear();
    delete (CCBAND*)pBandArray;
}
/* BAND: L/M/H
 * INDEX: G1/2/3/4/5/6/7/"MAX"
 * MAX: L/M/H
 */

static int SearchIndex(const char* pszGainMode,CCGAIN vMode)
{
    int nIndex = -1;
    GAINMODE mode;
    for(unsigned int n = 0;n<vMode.size();n++)
    {
        mode = vMode[n];
        if(!strcmp(pszGainMode,mode.szMode.c_str()))
        {
            nIndex = n;
            break;
        }
    }
    return nIndex;
}
/*
int CGainModeParse::Insert(const char* pszBand, const char* pszGainMode, double dValue) 
{
    int nIndex = 0;
    CCBAND::iterator bandIt;
    string szBand = string(pszBand);
    string szGainMode = string(pszGainMode);
    bandIt = ((CCBAND*)pBandArray)->find(szBand);
    if(bandIt == ((CCBAND*)pBandArray)->end())
    {
        CCGAIN gainTemp;
        GAINMODE mode = {szGainMode,dValue};
        gainTemp.push_back(mode);
        ((CCBAND*)pBandArray)->insert(pair<string,CCGAIN>(szBand,gainTemp));
    }
    else
    {
        CCGAIN gainTemp = bandIt->second;
        nIndex = SearchIndex(pszGainMode,gainTemp);
        if(nIndex != -1)
        {
            gainTemp[nIndex].dValue = dValue;
        }
        else
        {
            GAINMODE mode = {szGainMode,dValue};
            gainTemp.push_back(mode);
            nIndex = gainTemp.size() - 1;
        }  
        ((CCBAND*)pBandArray)->lower_bound(szBand)->second = gainTemp;
    }
    return nIndex;
}
*/
int CGainModeParse::Insert(const char* pszBand, const char* pszGainMode, int nNum,double* pValue)
{
    int nIndex = 0;
    CCBAND::iterator bandIt;
    string szBand = string(pszBand);
    string szGainMode = string(pszGainMode);
    
    int nSize = min(nNum,MAX_MODE_SITE);
    
  
    bandIt = ((CCBAND*)pBandArray)->find(szBand);
    if(bandIt == ((CCBAND*)pBandArray)->end())
    {
        CCGAIN gainTemp;
        GAINMODE mode;
        mode.szMode = szGainMode;
        if(nSize)
        {
            mode.pValue = new double[nSize];
            memcpy(mode.pValue,pValue,nSize*sizeof(double));
            gainTemp.push_back(mode);
            ((CCBAND*)pBandArray)->insert(pair<string,CCGAIN>(szBand,gainTemp));
        }
    }
    else
    {
        CCGAIN gainTemp = bandIt->second;
        nIndex = SearchIndex(pszGainMode,gainTemp);
        if(nIndex != -1)
        {
            if(gainTemp[nIndex].pValue)
            {
                delete[] gainTemp[nIndex].pValue;
                gainTemp[nIndex].pValue = NULL;
            }
            gainTemp[nIndex].pValue = new double[nSize];
            memcpy(gainTemp[nIndex].pValue,pValue,nSize*sizeof(double));
        }
        else
        {
            GAINMODE mode;
            mode.szMode = szGainMode;
            if(nSize)
            {
                mode.pValue = new double[nSize];
                memcpy(mode.pValue,pValue,nSize*sizeof(double));
                gainTemp.push_back(mode);
            }
            nIndex = gainTemp.size() - 1;
        }  
        ((CCBAND*)pBandArray)->lower_bound(szBand)->second = gainTemp;
    }
    return nIndex;
}

double* CGainModeParse::Get(const char* pszBand, const char* pszGainMode)
{
    double* pResult = 0;
    string szBand = string(pszBand);
    
    CCBAND::iterator bandIt;
    bandIt = ((CCBAND*)pBandArray)->find(szBand);
    if(bandIt != ((CCBAND*)pBandArray)->end())
    {
        CCGAIN gainTemp = bandIt->second;
        
        int nIndex = SearchIndex(pszGainMode,gainTemp);
        if(nIndex != -1)
        {
            pResult = gainTemp[nIndex].pValue;
        }
    }
    return pResult;
}

double* CGainModeParse::Get(const char* pszBand, int nIndex)
{
    double* pResult = 0;
    int nSize = 0;
    
    string szBand = string(pszBand);
    CCBAND::iterator bandIt;
    bandIt = ((CCBAND*)pBandArray)->find(szBand);
    
    if(bandIt != ((CCBAND*)pBandArray)->end())
    {
        CCGAIN gainTemp = bandIt->second;
        nSize = gainTemp.size();
        
        if(nIndex < nSize)
        {
            pResult = gainTemp[nIndex].pValue;
        }
    }
    return pResult;
}

int CGainModeParse::FindIndex(const char* pszBand,const char* pszGainMode)
{
    int nIndex = -1;
    string szBand = string(pszBand);

    CCBAND::iterator bandIt;
    bandIt = ((CCBAND*)pBandArray)->find(szBand);
    if(bandIt != ((CCBAND*)pBandArray)->end())
    {
        CCGAIN gainTemp = bandIt->second;
        nIndex = SearchIndex(pszGainMode,gainTemp);
    }
    return nIndex;
}

void CGainModeParse::Clear() 
{
    int nSize = 0;
    CCBAND::iterator bandIt;
    for(bandIt = ((CCBAND*)pBandArray)->begin();bandIt != ((CCBAND*)pBandArray)->end();bandIt++)
    {
        CCGAIN gainMode = bandIt->second;
        nSize = gainMode.size();
        for(int i =0;i<nSize;i++)
        {
            if(gainMode[i].pValue != NULL)
            {
                delete[] gainMode[i].pValue;
                gainMode[i].pValue = NULL;
            }
        }
    }

    ((CCBAND*)pBandArray)->clear();
}


/*******************************************************************************/

unsigned long ConvertCapData(unsigned long* pData,unsigned char nSize)
{
#define MAX_COUNT       (16)
    
    CapData nCapData = {0};
    
    int nCount = nSize;
    if(pData == NULL)
    {
        return nCapData.nData;
    }
    if(nSize>MAX_COUNT)
    {
        nCount = MAX_COUNT;
    }
    
    switch (MAX_COUNT - nCount) {
        case 0:
            nCapData.bit.bit15 = pData[0];
        case 1:
            nCapData.bit.bit14 = pData[1];
        case 2:
            nCapData.bit.bit13 = pData[2];
        case 3:
            nCapData.bit.bit12 = pData[3];
        case 4:
            nCapData.bit.bit11 = pData[4];
        case 5:
            nCapData.bit.bit10 = pData[5];
        case 6:
            nCapData.bit.bit9 = pData[6];
        case 7:
            nCapData.bit.bit8 = pData[7];
        case 8:
            nCapData.bit.bit7 = pData[8];
        case 9:
            nCapData.bit.bit6 = pData[9];
        case 10:
            nCapData.bit.bit5 = pData[10];
        case 11:
            nCapData.bit.bit4 = pData[11];
        case 12:
            nCapData.bit.bit3 = pData[12];
        case 13:
            nCapData.bit.bit2 = pData[13];
        case 14:
            nCapData.bit.bit1 = pData[14];
        case 15:
            nCapData.bit.bit0 = pData[15];
    }
    
    return nCapData.nData;
 #undef MAX_COUNT   
}
