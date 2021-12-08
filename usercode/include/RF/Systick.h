/* 
 * File:   Systick.h
 * Author: Liang
 *
 * Created on 2020年8月25日, 下午8:23
 */

#ifndef SYSTICK_H
#define	SYSTICK_H

class __declspec(dllexport) CSysTick
{
public:
    CSysTick();
    CSysTick(const char* pszFileName);
    virtual ~CSysTick();
public:
    void Start();
    double End();
    double End(const char* pszTitle);
    double GetElapsedTime();
    
private:
    double dwElapsedTime;
};

#endif	/* SYSTICK_H */

