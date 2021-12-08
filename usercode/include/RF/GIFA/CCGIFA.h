/* 
 * File:   CCS08FDIO.h
 * Author: guiyuliang
 *
 * Created on 2020年7月30日, 上午9:30
 */

#ifndef CCS08F_GIFA_H
#define	CCS08F_GIFA_H

#pragma once
#include <cctype.h>

typedef enum{
    Temperature0 = 0,
    Temperature1,
    Temperature2,
    Temperature3
}TMP117Type;

typedef enum{
    EEPROM_NO0 = 0,
    EEPROM_NO1,
    EEPROM_NO2,
    EEPROM_NO3
}EEPROMIndex;

#define TMP117_R_OK             (0x00)
#define TMP117_E_PWR            (0x01)
#define TMP117_E_ACK            (0x02)
#define TMP117_E_TIMEOUT        (0x04)


ViUInt16 ReadTemp117(TMP117Type nType,ViReal32* pTemperature);
// 未测试
ViUInt16 ReadEeprom(EEPROMIndex nIndex, ViUInt16 nStartAddress,ViUInt16 nEndAddress,ViUInt8* pOutData);
// 未测试
ViUInt16 WriteEeprom(EEPROMIndex nIndex, ViUInt16 nStartAddress,ViUInt16 nEndAddress,ViUInt8* pInData,ViUInt16 nDataBytes);

#endif	/* CCS08F_GIFA_H */

