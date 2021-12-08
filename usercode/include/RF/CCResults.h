/* 
 * File:   CCResults.h
 * Author: guiyuliang
 *
 * Created on 2020年11月6日, 上午8:38
 */
#pragma once
#ifndef CCRESULTS_H
#define	CCRESULTS_H
#include "CCTesterDef.h"
#include <map>
using namespace std;

#ifndef NULL
#define NULL    (void*)0
#endif

#ifndef  FOREACH_SITE_BEGIN
#define FOREACH_SITE_BEGIN(ResMap) for(ResMap.init(); ResMap.check(); ResMap.increment()){
#endif

#ifndef FOREACH_SITE_END
#define FOREACH_SITE_END\
        }
#endif  

#ifndef GET_CURRENT_SITE
#define GET_CURRENT_SITE_RESULT(ResMap)  ResMap.GetCurrentSite()
#endif

#ifndef GET_SITE_NUM
#define GET_SITE_NUM(ResMap)  ResMap.GetSiteNum()
#endif

template <class T>
class CCResultsArray
{
public:
    CCResultsArray();
    virtual ~CCResultsArray();
    
    void Add(ViUInt8 nSiteNum,T element);
    int Size();
    T Find(ViUInt8 nSiteNum);
    T* GetAddress(ViUInt8 nSiteNum);
    T operator [](ViUInt8 nSiteNum);
    
    T GetCurrentSite();
    ViUInt8 GetSiteNum();
    virtual void RemoveAll() = 0;
    virtual void init();
    virtual bool check();
    virtual void increment();
protected:
    typename map<ViUInt8,T>::iterator it;
    map<ViUInt8,T> resultsMap;    
};

template <class T>
CCResultsArray<T>::CCResultsArray()
{
    resultsMap.clear();
}

template <class T>
CCResultsArray<T>::~CCResultsArray()
{
}

template <class T>
int CCResultsArray<T>::Size()
{
    return resultsMap.size();
}

template <class T>
ViUInt8 CCResultsArray<T>::GetSiteNum()
{
    return it->first;
}

template <class T>
T CCResultsArray<T>::GetCurrentSite()
{
    return it->second;
}

template <class T>
void CCResultsArray<T>::init()
{
    it = resultsMap.begin();
}

template <class T>
bool CCResultsArray<T>::check()
{
    return (it == resultsMap.end())?false:true;
}

template <class T>
void CCResultsArray<T>::increment()
{
    it++;
}

template <class T>
void CCResultsArray<T>::Add(ViUInt8 nSiteNum,T element)
{
    it = resultsMap.find(nSiteNum);
    if(it == resultsMap.end())
    {
        resultsMap.insert(pair<ViUInt8,T>(nSiteNum,element));
    }
    else
    {
        resultsMap[nSiteNum] = element;
    }
}

template <class T>
T CCResultsArray<T>::Find(ViUInt8 nSiteNum)
{
    T tmp = {0};
    it = resultsMap.find(nSiteNum);
    
    if(it != resultsMap.end())
    {
        tmp = resultsMap[nSiteNum];
    }
    return tmp;
}

template <class T>
T* CCResultsArray<T>::GetAddress(ViUInt8 nSiteNum)
{
    it = resultsMap.find(nSiteNum);
    if(it != resultsMap.end())
    {
        return &resultsMap[nSiteNum];
    }
    else
    {
        return NULL;
    }
}

template <class T>
T CCResultsArray<T>::operator [](ViUInt8 nSiteNum)
{
    return Find(nSiteNum);
}

#endif	/* CCRESULTS_H */

