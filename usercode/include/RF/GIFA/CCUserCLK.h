/* 
 * File:   CCUserCLK.h
 * Author: wengmenghao
 *
 * Created on 2020年10月16日, 下午4:38
 */
#pragma once
#ifndef CCUSERCLK_H
#define	CCUSERCLK_H

#include "cctype.h"

typedef struct{
    ViReal64 dFrequency;
    ViUInt8 nChannel;
}UserClkAttribute,*pUserClkAttribute;

class __declspec(dllexport) CCUserClk
{
public:
    CCUserClk();
    virtual ~CCUserClk();
public:
    ViReal32 temperature();
    // 设置clk频率
    ViInt16 setClkFreq(ViReal64 dwClkFrequencyMHz);
    // 开始变频与开关通道
    ViInt16 Start();
    // 通过关闭通道来关闭输出频率
    ViInt16 Close();

private:
    UserClkAttribute UserClkAttr;

    ViInt16 ChangeClkAndChannel(ViReal64 dClkFrequencyMHz, ViUInt8 nChannelCfg);
    
    ViInt16 CfgChannelRegisters(ViUInt8 nUserCfgData);
    ViInt16 RunChannelRegistersCfg();
    
    /* dExpectedFreq: From 10MHz -- 250MHz*/
    ViInt16 CfgFrequencyRegisters(ViReal64 dExpectedFreq);
    ViInt16 RunFrequencyRegistersCfg();
    
    ViInt16 ValidatePinName(ViConstString pszPinName);
    
    inline void decimal2Fractional(ViReal64 decimal,ViReal64 &numerator,ViReal64 &denominator);
    inline void divisor(ViReal64 nDivisor, ViReal64 ndividend, ViReal64 &nDiv);
};
#endif	/* CCGIFAMIX_H */

