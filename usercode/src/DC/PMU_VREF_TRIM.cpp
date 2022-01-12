/*
 * PMU_VREF_TRIM.cpp
 *
 *  Created on: 2021年8月18日
 *      Author: 荣耀
 */

#include "Globle_Var.h"
#include "TestClass.h"
#include <iostream>
#include <string>
#include "UserAPI.h"
#include "d2sProtocolSSI.h"
#include "D2S_PMU_Module.h"
#include <math.h>
#include "UserDef.h"




class PMU_VrefTrim: public TestClass {
public:
	std::string pinlist;
	int samplesize;
	double waittime;
	void init() {
		add_param("Measure_pinlist", "PinString", &pinlist).set_default(
				"PMU_REFBP"); //PMU_REFBP
		add_param("WaitTime", "double", &waittime).set_default("0.005");
		add_param("SampleSize", "int", &samplesize).set_default("2");
	}

	void execute() {
		TheInst.DCVI().Power().Apply();
		TheInst.Digital().Level().Apply();
		TheInst.Digital().Timing().Apply();

		double hil[30], lowl[30];
		vector<string> Test_Item;
		vector<string> Units;
		int Test_number[30];
		int Soft_Bin[30];
		int Hard_Bin[30];
		Read_Limit(lowl, hil, Test_Item, Test_number, Units, Soft_Bin,Hard_Bin);


		// Register
		d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
		d2sProtocolSSI d2s_test;
		d2s_test.SSI_write(0x200, 0x2000, false);
		d2s_test.SSI_write(0x202, 0x40, false);
		d2s_test.SSI_write(0x124, 0xb0);
		d2s::d2s_LABEL_END();

		map<int, double> preTrimMeas;
		map<int, long long> TrimData;
		map<int, double> postTrimMeas;
		double Voffset = 0.002;

		TheInst.DCVI().Power().Apply();
		TheInst.Digital().Level().Apply();
		TheInst.DCVI().Pins(pinlist).SetMeasureMode(PhxAPI::E_DC_MODE_MV).SetReadMode(
				PhxAPI::E_DC_MODE_MEASURE).SetMeasureMethod(
				PhxAPI::E_DC_METHOD_STATIC).SetMeasureOrder(
				PhxAPI::E_DC_ORDER_GROUP).SetSampleSize(samplesize).SetWaitTime(
				waittime) //5ms
		.Measure();

		// Trim Code
		PinArrayDouble res = TheInst.DCVI().Pins(pinlist).GetMeasureResults();
		FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)double GetValue = res.GetData(pinlist, site_id);
		Testsoftbin[site_id] = 1;
		preTrimMeas[site_id] = GetValue + Voffset;






		if(FT_PASSFLAG[site_id]==0) {
			pmu_v_trimData[site_id] = floor((1-(1.2/preTrimMeas[site_id]))*219.2+0.5);
			if(pmu_v_trimData[site_id]>15) {
				pmu_v_trimData[site_id]=0;
			}
			else if(pmu_v_trimData[site_id]>=0) {
				pmu_v_trimData[site_id]=pmu_v_trimData[site_id];

			}
			else if(pmu_v_trimData[site_id]>=-16) {
				pmu_v_trimData[site_id]=abs(pmu_v_trimData[site_id])-1+16;
			}
			else {
				pmu_v_trimData[site_id]=0;
			}
		} else {
			pmu_v_trimData[site_id] = pmu_v_pretrimData[site_id];
		}




		TrimData[site_id]=pmu_v_trimData[site_id]<<10;
		cout << "preTrimMeas:" << preTrimMeas[site_id] << endl;
		cout << "pmu_v_trimData:" << pmu_v_trimData[site_id] << endl;
		FOREACH_ACTIVESITE_END
		TheSoft.Flow().TestLimit("PMU_REFBP", preTrimMeas, lowl[0], hil[0],
				Hard_Bin[0], Soft_Bin[0], "V", Test_Item[0], Test_number[0],
				PhxAPI::E_Fail, PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,
				PhxAPI::E_RS_DEC);
		TheSoft.Flow().TestLimit("PMU_REFBP", pmu_v_trimData, lowl[1], hil[1],
				Hard_Bin[1], Soft_Bin[1], "", Test_Item[1], Test_number[1],
				PhxAPI::E_Fail, PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,
				PhxAPI::E_RS_DEC);


		// Register
		d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
		d2s_test.SSI_read(0x154, "readdata",7);
		d2s::d2s_LABEL_END();
		map<int, long long> capture_data;
		map<int, long long> iter = d2s_test.getReadValue("readdata");
		for (map<int, long long>::iterator it = iter.begin(); it != iter.end();
				it++) {
			long long readvalue = it->second;
			capture_data[it->first] = readvalue;
			capture_data[it->first] = capture_data[it->first] & (0x83FF);
			capture_data[it->first] = capture_data[it->first]
					| TrimData[it->first];
		}
		d2s::d2s_LABEL_BEGIN("dynamic", d2s_WorkMode);
		d2s_test.SSI_writeDynamic(0x154, capture_data, "write");
		d2s::d2s_LABEL_END();


		// Print Result
		TheInst.Wait(10 * ms);

		TheInst.DCVI().Power().Apply();
		TheInst.Digital().Level().Apply();
		TheInst.DCVI().Pins(pinlist).SetMeasureMode(PhxAPI::E_DC_MODE_MV).SetMeasureMethod(
				PhxAPI::E_DC_METHOD_STATIC).SetReadMode(
				PhxAPI::E_DC_MODE_MEASURE).SetMeasureOrder(
				PhxAPI::E_DC_ORDER_GROUP).SetSampleSize(samplesize).SetWaitTime(
				waittime) //5ms
		.Measure();
		PinArrayDouble res2 = TheInst.DCVI().Pins(pinlist).GetMeasureResults();

		TheSoft.Flow().TestLimit("PMU_REFBP", res2, lowl[2], hil[2], Hard_Bin[2],
				Soft_Bin[2], "V", Test_Item[2], Test_number[2], PhxAPI::E_Fail,
				PhxAPI::E_LEFTCLOSE_RIGHTCLOSE, PhxAPI::E_RS_DEC);

	}

private:
	vector<double> VoltageTrim(vector<double> value, int baseTrimCode) {

		vector<double> trimCode = {0, 0};
		trimCode[0] = 0;
		trimCode[1] = 0;

		vector<double> voltage = value;
		int orgTrimCode = baseTrimCode;

		for (int i = 0; i < voltage.size(); i++) {

			orgTrimCode = orgTrimCode | 0x11A0;
			int calcTrimCode = 0;

			// 可以考虑重构
			if (voltage[i] > 898 and voltage[i] < 902) {
				calcTrimCode = 0;
			}
			else if (voltage[i] >= 902) {
				try {
					calcTrimCode = 737 - 900 * 737 / voltage[i];
					calcTrimCode = round(calcTrimCode / 3) + 15;
				}
				catch (exception &e) {
					cout << "Error!" << endl;
				}
			}
			else if (voltage[i] <= 898) {
				try {
					calcTrimCode = 900 * 737 / voltage[i] - 737;
					calcTrimCode = round(calcTrimCode / 3);
				}
				catch (exception &e) {
					cout << "Error!" << endl;
				}

				if (calcTrimCode >= 15) {
					calcTrimCode = 15;
				}
			}
			else {
				calcTrimCode = 0;
			}

			bool effuseIRC_FTPASS = true;
			double pmu_vref_trimdata = 0;
			if (effuseIRC_FTPASS) {
				calcTrimCode = pmu_vref_trimdata;
			}

			trimCode[0] = calcTrimCode;
			trimCode[1] = calcTrimCode + orgTrimCode;

		}

		return trimCode;
}



};


REGISTER_TESTCLASS("PMU_VrefTrim", PMU_VrefTrim)

