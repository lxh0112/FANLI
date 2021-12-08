/* 
 * File:   d2sBurst.h
 * Author: zhongdanbiao
 *
 * Created on 2020年6月21日, 下午5:51
 */

#ifndef D2SBURST_H
#define	D2SBURST_H
#include "d2sPatternModes.h"
using namespace std;
class d2sBurstPattern{
public:
    d2sPatternMode mode;    
    string templatePatternBlockName;
    string newPatternName;
    string pin_name;//address pin name
    unsigned long addr_start;
    string addr_array;
    string read_pin_name;//read data pin name，只有expect的时候能用到
    unsigned long data_start;
    string data_array;
    unsigned long waitCycles;
    d2sBurstPattern(){
        mode = Write_Mode;
        newPatternName = "";
        templatePatternBlockName = "";
        pin_name = "";
        addr_start = 0;
        addr_array = "" ;
        read_pin_name = "";
        data_start = 0;
        data_array = "";
        waitCycles = 0;
    }
    d2sBurstPattern(d2sPatternMode pattern_mode,string newPatName,string templatePatternName,string strPinName,long reg_addr_start,string reg_addr_array,long reg_data_start,string reg_data_array,unsigned long reg_wait){
        mode = pattern_mode;
        newPatternName = newPatName;
        templatePatternBlockName = templatePatternName;
        pin_name = strPinName;
        addr_start = reg_addr_start;
        addr_array = reg_addr_array;
        data_start = reg_data_start;
        data_array = reg_data_array;
        waitCycles = reg_wait;
    }
    d2sBurstPattern(d2sPatternMode pattern_mode,string newPatName,string templatePatternName,string strAddrPinName,long reg_addr_start,string reg_addr_array,string strReadPinName,long reg_data_start,string reg_data_array,unsigned long reg_wait){
        mode = pattern_mode;
        newPatternName = newPatName;
        templatePatternBlockName = templatePatternName;
        pin_name = strAddrPinName;
        addr_start = reg_addr_start;
        addr_array = reg_addr_array;
        read_pin_name = strReadPinName;
        data_start = reg_data_start;
        data_array = reg_data_array;
        waitCycles = reg_wait;
    }
};

#endif	/* D2SBURST_H */

