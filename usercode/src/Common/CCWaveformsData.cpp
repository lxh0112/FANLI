#include "CCWaveformsData.h"
#include "string.h"
#include <stdlib.h>

#include <fstream>    
#include <string>
#include <vector>
#include <map>      
using namespace std;

CWaveformData::CWaveformData()
{ 
    pDataArray = new vector<ViInt32>;
    ((vector<ViInt32>*)pDataArray)->clear();
}

CWaveformData::CWaveformData(CWaveformData& waveformData)
{
    CWaveformData();
    for(int i=0;i<waveformData.Size();i++)
    {
        ((vector<ViInt32>*)pDataArray)->push_back(waveformData[i]);
    }
}

CWaveformData::~CWaveformData()
{
    if(pDataArray != VI_NULL)
    {
        ((vector<ViInt32>*)pDataArray)->clear();
        delete ((vector<ViInt32>*)pDataArray);
    }
    pDataArray = VI_NULL;
}


ViInt32 CWaveformData::FileImport(ViConstString pszWaveformPath)
{
    try
    {
        std::ifstream ifs;
        string szData;
        ((vector<ViInt32>*)pDataArray)->clear();
        ifs.open(pszWaveformPath);
        
        while(getline(ifs,szData))
        {
            ((vector<ViInt32>*)pDataArray)->push_back(atoi(szData.c_str()));
        }
        ifs.close();
    }
    catch(...)
    {
        ((vector<ViInt32>*)pDataArray)->clear();
        return -1;
    }
    
    return ((vector<ViInt32>*)pDataArray)->size();
}

ViInt32 CWaveformData::Size()
{
    return ((vector<ViInt32>*)pDataArray)->size();
}

ViInt32 CWaveformData::operator [](ViInt32 nIndex)
{
    if(nIndex < Size())
    {
        return ((vector<ViInt32>*)pDataArray)->at(nIndex);
    }
    else
    {
        return 0;
    }
}
/*********************************************************************************/
typedef struct{
    string szMode;
    double dValue;
}GAINMODE,*pGAINMODE;

typedef vector<GAINMODE> CCGAIN;
typedef map<string, CCGAIN> CCBAND;

CGainMode::CGainMode() 
{
    pBandArray = new CCBAND;
    ((CCBAND*)pBandArray)->clear();
}

CGainMode::~CGainMode() 
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
    for(int n = 0;n < vMode.size();n++)
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

int CGainMode::Insert(const char* pszBand, const char* pszGainMode, double dValue) 
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
        //gainTemp.insert(pair<string,double>(szGainMode,dValue));
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

double CGainMode::Get(const char* pszBand, const char* pszGainMode)
{
    double dResult = 0.0;
    string szBand = string(pszBand);
    
    CCBAND::iterator bandIt;
    bandIt = ((CCBAND*)pBandArray)->find(szBand);
    if(bandIt != ((CCBAND*)pBandArray)->end())
    {
        CCGAIN gainTemp = bandIt->second;
        
        int nIndex = SearchIndex(pszGainMode,gainTemp);
        if(nIndex != -1)
        {
            dResult = gainTemp[nIndex].dValue;
        }
    }
    return dResult;
}

double CGainMode::Get(const char* pszBand, int nIndex)
{
    double dResult = 0.0;
    int nSize = 0;
    int nLoop = nIndex;
    string szBand = string(pszBand);
    CCBAND::iterator bandIt;
    bandIt = ((CCBAND*)pBandArray)->find(szBand);
    
    if(bandIt != ((CCBAND*)pBandArray)->end())
    {
        CCGAIN gainTemp = bandIt->second;
        nSize = gainTemp.size();
        
        if(nIndex < nSize)
        {
            dResult = gainTemp[nIndex].dValue;
        }
    }
    return dResult;
}

int CGainMode::FindIndex(const char* pszBand,const char* pszGainMode)
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

void CGainMode::Clear() 
{
    ((CCBAND*)pBandArray)->clear();
}

/*********************************************************************************/
CSiteLong::CSiteLong()
{
    
}

CSiteLong::~CSiteLong()
{
    
}

CSiteDouble::CSiteDouble()
{
    
}

CSiteDouble::~CSiteDouble()
{
    
}
