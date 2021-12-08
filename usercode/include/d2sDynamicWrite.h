/* 
 * File:   d2sDynamicWrite.h
 * Author: zhongdanbiao
 *
 * Created on 2021年1月5日, 下午5:04
 */

#ifndef D2SDYNAMICWRITE_H
#define	D2SDYNAMICWRITE_H
#include <vector>
#include <map>
using namespace std;
class d2sDynamicWrite{
public:
    string pin_name;//address pin name
    unsigned long addr_start;
    unsigned long addr_vectors;
    vector<unsigned long> addr_array;    
    unsigned long data_start;
    unsigned long data_vectors;
    map<int ,vector<unsigned long> > data_array;    //site,data_array
    d2sDynamicWrite(){
        pin_name = "";
        addr_start = 0;
        addr_vectors = 0;
        data_start = 0;
        data_vectors = 0;
    }
    d2sDynamicWrite(string strPinName,unsigned long reg_addr_start,unsigned long reg_addr_vectors,vector<unsigned long> reg_addr_array,unsigned long reg_data_start,unsigned long reg_data_vectors,map<int ,vector<unsigned long> > reg_data_array){
        pin_name = strPinName;
        addr_start = reg_addr_start;
        addr_vectors = reg_addr_vectors;
        addr_array.swap(reg_addr_array);
        data_start = reg_data_start;
        data_vectors = reg_data_vectors;
        data_array.swap(reg_data_array);
    }
};


#endif	/* D2SDYNAMICWRITE_H */

