/* 
 * File:   CBBLimits.h
 * Author: wengmenghao
 *
 * Created on 2020年12月25日, 上午11:29
 */

#ifndef CBBLIMITS_H
#define	CBBLIMITS_H

#include <vector>
#include <map>
#include "cctype.h"
#include <string>
#include <string.h>

using namespace std;

#define ERR_EXCEL_PATH 1
#define INIT_EXCEL_FAIL 2
#define OPEN_EXCEL_FAIL 3
#define READ_SUCCESS 0

typedef struct
{
    vector<string> flowtable;
    vector<string> testname;
    vector<ViUInt64> testnumber;
    vector<double> Default_lolim;
    vector<double> Default_hilim;
    vector<double> QA_lolim;
    vector<double> QA_hilim;
    vector<double> Golden_lolim;
    vector<double> Golden_hilim;
//    vector<double> L40C_lolim;
//    vector<double> L40C_hilim;
//    vector<double> L40C_QA_lolim;
//    vector<double> L40C_QA_hilim;
//    vector<double> _105C_lolim;
//    vector<double> _105C_hilim;
//    vector<double> _105C_QA_lolim;
//    vector<double> _105C_QA_hilim;
    vector<string> scale;
    vector<string> units;
    vector<ViUInt32> failsort;
    vector<ViUInt8> failbin;
}tyLimitsData,*ptyLimitsData;

class CBBLimits
{
public:
    CBBLimits();
    ~CBBLimits();
public:
    int ReadLimits(char *pszLimitsPath, map<string,tyLimitsData> *mapOfLimits); 
private:
    inline double GetDoubleData(char *pszData , int nLowOrHigh);
};

#endif	/* CBBLIMITS_H */

