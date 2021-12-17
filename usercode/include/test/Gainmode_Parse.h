/* 
 * File:   Gainmode_Parse.h
 * Author: Administrator
 *
 * Created on 2020年12月28日, 上午9:56
 */
#pragma once
#ifndef GAINMODE_PARSE_H
#define	GAINMODE_PARSE_H


class CGainModeParse
{
public:
    CGainModeParse();
    ~CGainModeParse();
public:
    //int Insert(const char* pszBand,const char* pszGainMode,double dValue);
    int Insert(const char* pszBand, const char* pszGainMode, int nNum,double* pValue); 
    void Clear();
    int Size(const char* pszBand);
    int FindIndex(const char* pszBand,const char* pszGainMode);
    double* Get(const char* pszBand,const char* pszGainMode);
    double* Get(const char* pszBand,int nIndex);
private:
    void* pBandArray;      
};

typedef union{
    unsigned long nData;
    struct {
        unsigned long bit0 : 1;
        unsigned long bit1 : 1;
        unsigned long bit2 : 1;
        unsigned long bit3 : 1;
        unsigned long bit4 : 1;
        unsigned long bit5 : 1;
        unsigned long bit6 : 1;
        unsigned long bit7 : 1;
        unsigned long bit8 : 1;
        unsigned long bit9 : 1;
        unsigned long bit10 : 1;
        unsigned long bit11 : 1;
        unsigned long bit12 : 1;
        unsigned long bit13 : 1;
        unsigned long bit14 : 1;
        unsigned long bit15 : 1;
    }bit;
}CapData;

unsigned long ConvertCapData(unsigned long* pData,unsigned char nSize);


#endif	/* GAINMODE_PARSE_H */

