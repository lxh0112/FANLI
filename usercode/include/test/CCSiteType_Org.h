
#pragma once

#ifndef CCSITETYPE_ORG_H
#define CCSITETYPE_ORG_H

#include "CCTesterDef.h"

#include <map>      
using namespace std;

typedef struct
{
   ViInt32 nSize;
   void* vptrArray;
}SiteDataAttribute,*pSiteDataAttribute;


template <class T>
class CSiteBase
{
public:
    CSiteBase();
    CSiteBase(ViInt16 nSites,ViInt32 nSize);
    CSiteBase(ViInt16 nSite,T* pSrcData,ViInt32 nSize);
    virtual ~CSiteBase();
    
public:
    void InitDataArray(ViInt16 nSite,ViInt32 nSize);
    void SetElement(ViInt16 nSite,ViInt16 nIndex,T dwValue);
    void CopyElement(ViInt16 nSite,T* pSrcData,ViInt32 nSize);
    
    T* GetAddress(ViInt16 nSite);
    T* operator [](ViInt16 nSite);
    T Element(ViInt16 nSite,ViInt32 nIndex);
    T operator ()(ViInt16 nSite,ViInt32 nIndex);
protected:
    void* pDataMap;
};


template <class T>
CSiteBase<T>::CSiteBase()
{
    pDataMap = new map<ViInt16,SiteDataAttribute>;
    ((map<ViInt16,SiteDataAttribute>*)pDataMap)->clear();
}

template <class T>
CSiteBase<T>::CSiteBase(ViInt16 nSites, ViInt32 nSize)
{
    pDataMap = new map<ViInt16,SiteDataAttribute>;
    ((map<ViInt16,SiteDataAttribute>*)pDataMap)->clear();
    
    for(int i = 0;i<nSites;i++)
    {
        T* pDataArray = new T[nSize];
        memset(pDataArray, 0x00, sizeof (T) * nSize);
        SiteDataAttribute siteAttr = {nSize, pDataArray};
        ((map<ViInt16, SiteDataAttribute>*)pDataMap)->insert(pair<ViInt16, SiteDataAttribute>(i, siteAttr));
    }
}

template <class T>
CSiteBase<T>::CSiteBase(ViInt16 nSite, T* pSrcData, ViInt32 nSize)
{
    pDataMap = new map<ViInt16,SiteDataAttribute>;
    ((map<ViInt16,SiteDataAttribute>*)pDataMap)->clear();
    
    CopyElement(nSite, pSrcData, nSize);
}

template <class T>
CSiteBase<T>::~CSiteBase()
{
    map<ViInt16,SiteDataAttribute>::iterator it;
    
    for(it = ((map<ViInt16,SiteDataAttribute>*)pDataMap)->begin();\
        it != ((map<ViInt16,SiteDataAttribute>*)pDataMap)->end();\
        it++)
    {
        if(it->second.vptrArray != NULL)
        {
            delete[] ((T*)(it->second.vptrArray));
            it->second.vptrArray = NULL;
        }
    }
    
    ((map<ViInt16,SiteDataAttribute>*)pDataMap)->clear();
}

template <class T>
void CSiteBase<T>::InitDataArray(ViInt16 nSite, ViInt32 nSize)
{
    map<ViInt16,SiteDataAttribute>::iterator it;
    it = ((map<ViInt16,SiteDataAttribute>*)pDataMap)->find(nSite);
    if(it != ((map<ViInt16,SiteDataAttribute>*)pDataMap)->end())
    {
        if(it->second.vptrArray != NULL)
        {
            delete[] ((T*)(it->second.vptrArray));
            it->second.vptrArray = NULL;
        }
        ((map<ViInt16,SiteDataAttribute>*)pDataMap)->erase(it);
    }
    
    T* pDataArray = new T[nSize];
    memset(pDataArray, 0x00, sizeof (T) * nSize);
    SiteDataAttribute siteAttr = {nSize, pDataArray};
    ((map<ViInt16, SiteDataAttribute>*)pDataMap)->insert(pair<ViInt16, SiteDataAttribute>(nSite, siteAttr));
}

template <class T>
void CSiteBase<T>::SetElement(ViInt16 nSite, ViInt16 nIndex, T dwValue)
{
    map<ViInt16,SiteDataAttribute>::iterator it;
    
    it = ((map<ViInt16,SiteDataAttribute>*)pDataMap)->find(nSite);
    
    if(it != ((map<ViInt16,SiteDataAttribute>*)pDataMap)->end())
    {
        T* pDataArray = (T*)it->second.vptrArray;
        
        if(nIndex < it->second.nSize)
        {
            pDataArray[nIndex] = dwValue;
        }
    }
}

template <class T>
void CSiteBase<T>::CopyElement(ViInt16 nSite, T* pSrcData, ViInt32 nSize)
{
    T* pMemoryAddr = NULL;
    map<ViInt16,SiteDataAttribute>::iterator it;
    it = ((map<ViInt16,SiteDataAttribute>*)pDataMap)->find(nSite);
    if(it != ((map<ViInt16,SiteDataAttribute>*)pDataMap)->end())
    {
        pMemoryAddr = (T*)it->second.vptrArray;
        
        if(pMemoryAddr != NULL)
        {
            delete[] pMemoryAddr;
            pMemoryAddr = NULL;
        }
        
        pMemoryAddr = new T[nSize];
        memcpy(pMemoryAddr,pSrcData,sizeof(T)*nSize);
        
        it->second.vptrArray = pMemoryAddr;
        it->second.nSize = nSize;
    }
    else
    {
        pMemoryAddr = new T[nSize];
        memcpy(pMemoryAddr,pSrcData,sizeof(T)*nSize);
        
        SiteDataAttribute siteAttr = {nSize,pMemoryAddr};
        ((map<ViInt16,SiteDataAttribute>*)pDataMap)->insert(pair<ViInt16,SiteDataAttribute>(nSite,siteAttr));
    }
}

template <class T>
T* CSiteBase<T>::GetAddress(ViInt16 nSite)
{
    T* pMemoryAddr = NULL;
    map<ViInt16,SiteDataAttribute>::iterator it;
    
    it = ((map<ViInt16,SiteDataAttribute>*)pDataMap)->find(nSite);
    if(it != ((map<ViInt16,SiteDataAttribute>*)pDataMap)->end())
    {
        pMemoryAddr = (T*)it->second.vptrArray;
    }
    
    return pMemoryAddr;
}

template <class T>
T* CSiteBase<T>::operator [](ViInt16 nSite)
{
    return GetAddress(nSite);
}

template <class T>
T CSiteBase<T>::Element(ViInt16 nSite, ViInt32 nIndex)
{
    T dwMemoryAddr = 0;
    map<ViInt16,SiteDataAttribute>::iterator it;
    T* pData = NULL;
    it = ((map<ViInt16,SiteDataAttribute>*)pDataMap)->find(nSite);
    if(it != ((map<ViInt16,SiteDataAttribute>*)pDataMap)->end())
    {
        pData = (T*)it->second.vptrArray;
        dwMemoryAddr = pData[nIndex];
    }
    return dwMemoryAddr;
}

template <class T>
T CSiteBase<T>::operator ()(ViInt16 nSite, ViInt32 nIndex)
{
    return Element(nSite,nIndex);
}

#endif
