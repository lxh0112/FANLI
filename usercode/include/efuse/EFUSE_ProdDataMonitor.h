/*
 * ProdDataMonitor.h
 *
 *  Created on: Feb 6, 2018
 *      Author: l00249487
 *      Version: 09
 */

#ifndef EFUSE_PRODDATAMONITOR_H_
#define EFUSE_PRODDATAMONITOR_H_
//#include "TestMethod.h"
#include "UserAPI.h" 
#include <vector>
#include <cstring>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <math.h>

#define  PDMV10_HppVer 4020008

using namespace std;
//using namespace MuTest;

struct LIMIT
{
    double low;
    double high;
};

extern unsigned int PDMV10_CppVer;

class EFUSE_ProdDataMonitor
{
private:
	vector< vector<double> > MeanMonitor_rawdata_all;
//	vector< vector<double> > MeanMonitor_meandata_all;
	vector<int> MeanMonitor_passcnt_bysite;
	vector<long> MeanMonitor_recenttest_cnt;

public:
	vector< vector<double> > MeanMonitor_meandata_all;
	vector<double> MeanMonitor_sqrt_bysite;
	vector<double> MeanMonitor_avg_bysite;
	vector<double> MeanMonitor_gap_value;
	vector<double> MeanMonitor_gap_samesite;
	vector<bool>   MeanMonitor_basefull;
	vector<int>    MeanMonitor_testedDieCnt;

private:
	double max_avg_value;
	double max_avg_siteindex;
	double min_avg_value;
	double min_avg_siteindex;
	unsigned int allsite_cnt;
        string str_all_site;

private:
	vector< vector<double> > SigmaMonitor_rawdata_all;
	vector<int> SigmaMonitor_passcnt_bysite;
	vector<double> SigmaMonitor_sigma_llim;
	vector<double> SigmaMonitor_sigma_hlim;
public:
	vector<double> SigmaMonitor_avg_bysite;
	vector<double> SigmaMonitor_sqrt_bysite;
	vector<bool>   SigmaMonitor_basefull;
	vector<LIMIT>  SigmaMonitor_Limit;
public:
	void func_MeanMonitor(
			double cur_site_data,
			unsigned int site_index,
			int Monitor_BaseData,
			double llimit,
			double hlimit);

	void func_SigmaMonitor(
			double cur_site_data,
			unsigned int site_index,
			int Monitor_BaseData,
			double llimit,
			double hlimit,
			double llim_sigma,
			double hlim_sigma);

	void func_ProdDM_Initial(string &strSelectedSites);
  
	EFUSE_ProdDataMonitor(void);
	~EFUSE_ProdDataMonitor(void);
};

#endif /* PRODDATAMONITOR_H_ */
