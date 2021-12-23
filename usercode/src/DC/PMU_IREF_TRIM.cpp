/*
 * PMU_IrefTrim.cpp
 *
 *  Created on: 2021年8月19日
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
#include"Getlog.h"
#include "UserDef.h"

class PMU_IrefTrim: public TestClass {
public:
	std::string pinlist;
	int samplesize;
	double waittime;
	double vforce;
	double irange;
	double iClampl;
	double iClamph;


	void init() {
		add_param("Measure_pinlist", "PinString", &pinlist).set_default(
				"NFC_GPIO0"); //PMU_RBIAS
		add_param("WaitTime", "double", &waittime).set_default("0.001");
		add_param("SampleSize", "int", &samplesize).set_default("3");
		add_param("VForce","double",&vforce).set_default("1.275");
		add_param("IRange","double",&irange).set_default("100e-6");
		add_param("IClampL","double",&iClampl).set_default("-100e-6");
		add_param("IClampH","double",&iClamph).set_default("100e-6");
		add_param("Waittime","double",&waittime).set_default("0.001");
	}

	void execute() {
		double hil[30], lowl[30];
		vector<string> Test_Item;
		vector<string> Units;
		int Test_number[30];
		int Soft_Bin[30];
		int Hard_Bin[30];
		Read_Limit(lowl, hil, Test_Item, Test_number, Units, Soft_Bin,
				Hard_Bin);

		map<int, double> preTrimMeas;
		map<int, long long> TrimData;
		map<int, double> postTrimMeas;
		double Voffset[4] = { 0.009, 0.009, 0.009, 0.009 };

		TheInst.DCVI().Power().Apply();
		TheInst.Digital().Level().Apply();

		TheInst.PPMU().Pins(pinlist).SetClear();
		TheInst.PPMU().Pins(pinlist).SetMeasureMode(PhxAPI::E_DC_FV_MV)
									.SetVForce(vforce)
									.SetIRange(irange)
									.SetIClampL(iClampl)
									.SetIClampH(iClamph)
									.SetMeasureOrder(PhxAPI::E_MEASURE_ODER_GROUP)
									.SetMeasureType(PhxAPI::E_MEASURE)
									.SetSampleSize(samplesize)
									.SetWaitTime(waittime)
									.Connect(true)
									.Measure();
		PinArrayDouble res = TheInst.DCVI().Pins(pinlist).GetMeasureResults();

		FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)double GetValue = res.GetData(pinlist, site_id);
		Testsoftbin[site_id] = 1;
		preTrimMeas[site_id] = GetValue;
		preTrimMeas[site_id] = preTrimMeas[site_id]*(-120000) + Voffset[site_id];
		if(FT_PASSFLAG[site_id]==0) {
			TrimData[site_id] = floor((((99*preTrimMeas[site_id])/1.2)-99)+13+0.5);
			if(TrimData[site_id] > 31) {
				TrimData[site_id] = 0;
			}
			else if(TrimData[site_id] >=0 ) {
				TrimData[site_id] = TrimData[site_id];
			}
			else {
				TrimData[site_id] = 0;
			}
		} else {
			TrimData[site_id] = pb_i_pretrimData[site_id];
		}

		pb_i_TrimData[site_id] = TrimData[site_id];
		TrimData[site_id] = TrimData[site_id]<<5;
		FOREACH_ACTIVESITE_END
		TheSoft.Flow().TestLimit("NFC_GPIO0", preTrimMeas, lowl[0], hil[0],
				Hard_Bin[0], Soft_Bin[0], "V", Test_Item[0], Test_number[0],
				PhxAPI::E_Fail, PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,
				PhxAPI::E_RS_DEC);
		TheSoft.Flow().TestLimit("NFC_GPIO0", pb_i_TrimData, lowl[1], hil[1],
				Hard_Bin[1], Soft_Bin[1], "", Test_Item[1], Test_number[1],
				PhxAPI::E_Fail, PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,
				PhxAPI::E_RS_DEC);

		d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
		d2sProtocolSSI d2s_test;
		d2s_test.SSI_write(0x200, 0x2000, false);
		d2s_test.SSI_write(0x202, 0x40, false);
		d2s_test.SSI_read(0x154, "readdata", 7);
		d2s::d2s_LABEL_END();

		map<int, long long> capture_data;
		map<int, long long> iter = d2s_test.getReadValue("readdata");

		for (map<int, long long>::iterator it = iter.begin(); it != iter.end();
				it++) {
			long long readvalue = it->second;
			capture_data[it->first] = readvalue;
			capture_data[it->first] = capture_data[it->first] & (0xFC1F);
			capture_data[it->first] = capture_data[it->first]
					| TrimData[it->first];
		}
		d2s::d2s_LABEL_BEGIN("dynamic", d2s_WorkMode);
		d2s_test.SSI_writeDynamic(0x154, capture_data, "write");
		d2s::d2s_LABEL_END();
		TheInst.Wait(10 * ms);

		TheInst.PPMU().Pins(pinlist).SetClear();
		TheInst.PPMU().Pins(pinlist).SetMeasureMode(PhxAPI::E_DC_FV_MV)
									.SetVForce(vforce)
									.SetIRange(irange)
									.SetIClampL(iClampl)
									.SetIClampH(iClamph)
									.SetMeasureOrder(PhxAPI::E_MEASURE_ODER_GROUP)
									.SetMeasureType(PhxAPI::E_MEASURE)
									.SetSampleSize(samplesize)
									.SetWaitTime(waittime)
									.Connect(true)
									.Measure();
		PinArrayDouble res2 = TheInst.DCVI().Pins(pinlist).GetMeasureResults();

		FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)double GetValue2 = res2.GetData(pinlist, site_id);
			postTrimMeas[site_id] = GetValue2;
			postTrimMeas[site_id] = postTrimMeas[site_id]*(-120000) + Voffset[site_id];
			PRE_IREF_TRIM[site_id] = preTrimMeas[site_id];
		FOREACH_ACTIVESITE_END
		TheSoft.Flow().TestLimit("NFC_GPIO0", postTrimMeas, lowl[2], hil[2],
				Hard_Bin[2], Soft_Bin[2], "V", Test_Item[2], Test_number[2],
				PhxAPI::E_Fail, PhxAPI::E_LEFTCLOSE_RIGHTCLOSE,
				PhxAPI::E_RS_DEC);

	}

};
REGISTER_TESTCLASS("PMU_IrefTrim", PMU_IrefTrim)

