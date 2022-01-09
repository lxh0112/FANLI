/*
 * d2s.cpp
 *
 *  Created on: 2022/1/4
 *      Author: dongyuqing
 *      Modified: w00600447
 */
#include <d2s.h>
#include <windows.h>
#include <direct.h>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "MD5.h"
#include "PatternManager.h"
#include <UserAPI.h>
#include "unistd.h"
using namespace PhxAPI;

vector<string> d2s::vecPatternLsit = vector<string>();
unordered_map<string, bool> d2s::mapPatternLsit = unordered_map<string, bool>();
vector<d2sWriteDynamic> d2s::vecDynamicList = vector<d2sWriteDynamic>();
map<string, map<int, long long> > d2s::capture_data_map = map<string, map<int, long long> >();
map<string, unsigned long> d2s::capture_start_loc_map = map<string, unsigned long>();
string d2s::burstpattern_prefix = "";
d2sWorkModeType d2s::work_mode = LearningMode;
string d2s::burst_name = "";
bool d2s::bInd2sBlock = false;
bool d2s::bExpectValue = false;
unsigned long d2s::vector_offset = 0;
unsigned long d2s::capture_start_offset = 0;
vector<int> d2s::active_sites = TheSoft.Sites().Active().GetActiveSites();
int d2s::site_count = TheSoft.Sites().Existing().GetExistedSiteCount();
string d2s::patterns_path = TheSoft.GetProgramPath();

d2s::d2s(bool bPreD2S) {
    is_pre_d2s = bPreD2S;
}

d2s::d2s() {
	// TODO Auto-generated constructor stub
	is_pre_d2s = false;
}

d2s::~d2s() {
	// TODO Auto-generated destructor stub
}

void d2s::d2s_LABEL_CLEAR(bool isBegin) {
	active_sites.clear();
	active_sites=TheSoft.Sites().Active().GetActiveSites();
	site_count = TheSoft.Sites().Existing().GetExistedSiteCount();
	patterns_path = TheSoft.GetProgramPath();
	if(patterns_path[patterns_path.size() - 1] != '/' && patterns_path[patterns_path.size() - 1] != '\\') {
		patterns_path += "\\";
	}
	patterns_path += "pattern\\";
}
/**
 * @brief   This function is used to set begin label of d2s

 * @param 	BurstTestName:	the burst name (can be deleted???)
 * 			labelPrefix: the prefix of burst test name
 * 			mode: the mode of this d2s. LearningMode or ProductionMode

 * @note 	It is used in paris with d2s_LABEL_END
 * */
void d2s::d2s_LABEL_BEGIN(std::string labelPrefix, d2sWorkModeType mode) {

	if(labelPrefix == "") {
		MessageBox(NULL, "Parameter 1 can not be empty.", "Error", MB_OK);
		return;
	}

	d2s::work_mode = mode;
	d2s::burstpattern_prefix = labelPrefix;

	vecPatternLsit.clear();
	mapPatternLsit.clear();
	vecDynamicList.clear();
	capture_data_map.clear();
	capture_start_loc_map.clear();
	burst_name = "";
	bInd2sBlock = true;
	bExpectValue = false;

	vector_offset = 0;
	capture_start_offset = 0;

	d2s_LABEL_CLEAR();
}

/**
 * @brief   This function is used to set end label of d2s, update all pattern file to pattern block

 * @param 	NONE

 * @note 	It is used in paris with d2s_LABEL_BEGIN
 * */
void d2s::d2s_LABEL_END() {
	if(!bInd2sBlock) {
		MessageBox(NULL, "[d2s_LABEL_END] can only be used after labeL begin.", "Error", MB_OK);
		return;
	}

	string burst_name = getBurstPatternBlockName();
	if(d2s::work_mode == LearningMode) {
		// vecPatternLsit + burst_name
		TheSoft.Flow().Pattern().SetBurstName(vecPatternLsit, burst_name);
	} else if(d2s::work_mode == ProductionMode) {
		if(vecDynamicList.size() > 0) {
			doWriteDynamicInProductionMode(burst_name);
		}
		// Execute current test, according to the same burst_name
		TheInst.Digital().PatEng().SetupMCFData();   //@20211129 ADD
		TheInst.Digital().PatEng().SetFailMode(PhxAPI::E_SET_PF_MODE);	//@20211129 ADD
		TheInst.Digital().Pattern().Start(burst_name);
	}
	if(bExpectValue) {
		map<uint32_t, bool> map_pass_fail_result = TheInst.Digital().PatEng().GetPassFail();
	}

	bInd2sBlock = false;
}

bool d2s::isProductionMode() {
    return (work_mode == ProductionMode) ? true : false;
}

bool d2s::is_in_d2s_block() {
    return bInd2sBlock;
}

bool d2s::Is_simulator() {
 //V100   return d2s_api->Is_simulator();
	   return false;
}

/**
 * @brief   This function is used to modify pattern in dynamic mode of write template test.
 * 		    First convert the setting data in array.
 * 		    Then using pattern-api to change DDR memory and execute pattern test.
 * 		    Finally save the necessary data in pattern file
 * @param 	llAddress:	the address register
 * 			llData:     the data register
 * 			llMd5Data:  the md5 code using for new pattern name
 * @note
 * */

void d2s::write(long long llAddress, long long llData, long long llMd5Data) {

	if (d2s::work_mode == ProductionMode && is_pre_d2s) {
		return;
	}

	if(!bInd2sBlock) {
		MessageBox(NULL, "[write] can only be used inside a d2s_LABEL_BEGIN/END-block.", "Error", MB_OK);
		return;
	}
	getWriteRegisterAttribute();
	string newPatternName = getNewWritePatternName(llAddress, llData, vectors_attr_t[Write].positive_addr, vectors_attr_t[Write].positive_data);
	string newPatternNmae_MD5 = getNewWritePatternName_MD5(llAddress, llData, vectors_attr_t[Write].positive_addr, vectors_attr_t[Write].positive_data, llMd5Data);

	bool pattern_exist = checkPatternNameExist(newPatternName);
	if(!is_pre_d2s)
	{
		vecPatternLsit.push_back(newPatternName);
		mapPatternLsit[newPatternName] = true;
	}

	if(d2s::work_mode == LearningMode) {
		string newPatternFile = d2s::patterns_path + newPatternName + ".cap";

		unsigned long* addr_array = new unsigned long[vectors_attr_t[Write].addr_vectors];
		unsigned long* data_array = new unsigned long[vectors_attr_t[Write].data_vectors];

		string str_addr = ConvertToArray(llAddress, addr_array, vectors_attr_t[Write].addr_vectors, vectors_attr_t[Write].positive_addr); // convert llAddress to array and string
		string str_data = ConvertToArray(llData, data_array, vectors_attr_t[Write].data_vectors, vectors_attr_t[Write].positive_data);    // convert llData to array and string

		// Dynamic change pattern
		DynamicSetVectors(getWriteTemplatePatternName(), getWritePinName(), vectors_attr_t[Write].start_addr, vectors_attr_t[Write].addr_vectors, addr_array);
		DynamicSetVectors(getWriteTemplatePatternName(), getWritePinName(), vectors_attr_t[Write].start_data, vectors_attr_t[Write].data_vectors, data_array);
		// Execute Pattern
		TheInst.Digital().Pattern().Start(getWriteTemplatePatternName());

//		cout<<getWriteTemplatePatternName()<<endl;


		// save data in pattern file
		if(!pattern_exist && !is_pre_d2s) {
			getWriteTemplatFileInfos();
			PatternManager::UpdateVectorInfos(&write_t.template_vectors, getWritePinName(), write_t.template_signals, vectors_attr_t[Write].start_addr, str_addr);
			PatternManager::UpdateVectorInfos(&write_t.template_vectors, getWritePinName(), write_t.template_signals, vectors_attr_t[Write].start_data, str_data);
			PatternManager::WritePatternFile(newPatternFile, write_t.template_head, &write_t.template_vectors, write_t.template_tail);
		}

		delete[] addr_array;
		delete[] data_array;
	}

	if(!is_pre_d2s) {
		vector_offset += getWritePatternVectors();
		burst_name += newPatternNmae_MD5;
	}
	return;
}


/**
 * @brief   This function is used to modify pattern in dynamic mode of read template test.
 * 		    First convert the setting data in array.
 * 		    Then using pattern-api to change DDR memory and execute pattern test.
 * 		    Afterthat capture data and save.
 * 		    Finally save the necessary data in pattern file
 * @param 	llAddress:	the address register
 * 			llData:     the data register
 * @note
 * */
void d2s::read(long long llAddress, string id, int offset) {
	if (d2s::work_mode == ProductionMode && is_pre_d2s) {
		return;
	}

	if(!bInd2sBlock) {
		MessageBox(NULL, "[read] can only be used inside a d2s_LABEL_BEGIN/END-block.", "Error", MB_OK);
		return;
	}

	if(id == "") {
		MessageBox(NULL, "read id can't be empty!", "Error", MB_OK);
		return;
	}
	if(capture_data_map.find(id) != capture_data_map.end() && !is_pre_d2s) {
		ostringstream error_info;
		error_info << "read id \"" << id << "\" already exist";
		MessageBox(NULL, error_info.str().data(), "Warning", MB_OK);
		return;
	}
	getReadRegisterAttribute();
	string newPatternName = getNewReadPatternName(llAddress, vectors_attr_t[Read].positive_addr, offset);
	bool pattern_exist = checkPatternNameExist(newPatternName);
	if(!is_pre_d2s)
	{
		vecPatternLsit.push_back(newPatternName);
		mapPatternLsit[newPatternName] = true;
	}

	if(d2s::work_mode == LearningMode) {
		string newPatternFile = d2s::patterns_path + newPatternName + ".cap";

		unsigned long* addr_array = new unsigned long[vectors_attr_t[Read].addr_vectors];
		string str_addr = ConvertToArray(llAddress, addr_array, vectors_attr_t[Read].addr_vectors, vectors_attr_t[Read].positive_addr); // convert llAddress to array and string
		// Dynamic change pattern
		DynamicSetVectors(getReadTemplatePatternName(), getReadAddressPinName(), vectors_attr_t[Read].start_addr, vectors_attr_t[Read].addr_vectors, addr_array);
		// Execute pattern
		TheInst.Digital().Pattern().Start(getReadTemplatePatternName());

//		cout<<getReadTemplatePatternName()<<endl;
		// Capture data
		map<int, long long> capture_data;
		capture_data = GetCaptureData(getReadPinName(), 0, getDataBits(), vectors_attr_t[Read].positive_addr);//???
		capture_data_map[id] = capture_data;

		// save data in pattern file
		if(!pattern_exist && !is_pre_d2s) {
			getReadTemplatFileInfos();
			PatternManager::UpdateVectorInfos(&read_t.template_vectors, getReadAddressPinName(), read_t.template_signals, vectors_attr_t[Read].start_addr, str_addr);
			PatternManager::WritePatternFile(newPatternFile, read_t.template_head, &read_t.template_vectors, read_t.template_tail);
		}

		delete[] addr_array;
	}
	capture_start_loc_map[id] = capture_start_offset;
	if(!is_pre_d2s) {
		capture_start_offset += getDataBits();
		vector_offset += getReadPatternVectors();
		burst_name += newPatternName;
	}

	return;
}

map<int, long long> d2s::getReadValue(const string id) {
	map<int, long long> rv_data;
	rv_data.clear();
	if (d2s::work_mode == ProductionMode && is_pre_d2s) {
		return rv_data;
	}

	if(id == "") {
		MessageBox(NULL, "read id can't be empty!", "Error", MB_OK);
		return rv_data;
	}
	map<string, unsigned long>::iterator it = capture_start_loc_map.find(id);
	if(it == capture_start_loc_map.end()) {
		ostringstream error_info;
		error_info << "read id \"" << id << "\" does not exist";
		MessageBox(NULL, error_info.str().data(), "Error", MB_OK);
		return rv_data;
	}
	getReadRegisterAttribute();

	if(d2s::work_mode == LearningMode) {
		map<int, long long> capture_data = capture_data_map[id];
		for(map<int, long long>::iterator it = capture_data.begin(); it!=capture_data.end(); it++) {
			rv_data[it->first] = it->second;
		}
	} else {
		unsigned long start_capture = capture_start_loc_map[id];
		map<int, long long> capResult = GetCaptureData(getReadPinName(), start_capture, getDataBits(), vectors_attr_t[Read].positive_addr);//???
		rv_data.insert(capResult.begin(), capResult.end());
	}

	return rv_data;
}
/**
 * @brief   This function is used to modify pattern in dynamic mode of wait template test.
 * 		    First compute the cycles in setting wait time.
 * 		    Then using pattern-api to change DDR memory and execute pattern test.
 * 		    Finally save the necessary data in pattern file
 * @param 	timeS:	the wait time in second

 * @note
 * */
void d2s::wait(double timeS) {
	if (d2s::work_mode == ProductionMode && is_pre_d2s) {
		return;
	}

	if(!bInd2sBlock) {
		MessageBox(NULL, "[wait] can only be used inside a d2s_LABEL_BEGIN/END-block.", "Error", MB_OK);
		return;
	}

	string newPatternName = getNewWaitPatternName(timeS);
	bool pattern_exist = checkPatternNameExist(newPatternName);
	if(!is_pre_d2s)
	{
		vecPatternLsit.push_back(newPatternName);
		mapPatternLsit[newPatternName] = true;
	}

	if(d2s::work_mode == LearningMode) {
		string newPatternFile = d2s::patterns_path + newPatternName + ".cap";
		// get period

//		double period = TheSoft.Flow().Timing().GetPeriod(TheSoft.Flow().Timing().GetCurrentTimingBlockName(), getTimingSetName());
//		cout<<"d2s::wait timing block now  static  use TIM_HiLink30LR, not use GetCurrentTimingBlockName() api"<<endl;
		double period = TheSoft.Flow().Timing().GetPeriod(TheSoft.Flow().Timing().GetCurrentTimingBlockName(), "TS1_0");
//		cout<<TheSoft.Flow().Timing().GetCurrentTimingBlockName()<<endl;
//		cout<<getTimingSetName()<<endl;
		if(period == 0)
		{
//			MessageBox(NULL, "[wait] fail to get period.", "Error", MB_OK);//masked by tony 20210915
			cout<<"[wait] fail to get period"<<endl;
			period = 100e-9;// 5ns
//			return;
		}
		unsigned long cycles = (unsigned long)(timeS / period);
		if(cycles < 2) {
			cycles = 2;
		}

		// dynamic set loop number
		uint32_t oprand = cycles;
		while(oprand / MAX_REPEAT_CYCLES > 0)
		{
			TheInst.Digital().Pattern().SetVectorMicroInstruction(getWaitTemplatePatternName(), 1, E_REPEAT, MAX_REPEAT_CYCLES);
			oprand -= MAX_REPEAT_CYCLES;
		}
		TheInst.Digital().Pattern().SetVectorMicroInstruction(getWaitTemplatePatternName(), 1, E_REPEAT, oprand);
		// Execute Pattern
		TheInst.Digital().Pattern().Start(getWaitTemplatePatternName());

		cout<<getWaitTemplatePatternName()<<endl;

//		// save data in pattern file
		if(!pattern_exist && !is_pre_d2s) {
			getWaitTemplatFileInfos();
			PatternManager::UpdateWaitInfos(wait_t.template_vector, cycles);
			PatternManager::WritePatternFile(newPatternFile, wait_t.template_head, wait_t.template_vector, wait_t.template_tail);
		}
	}
	if(!is_pre_d2s) {
		vector_offset += 1;
		burst_name += newPatternName;
	}

	return;
}

/**
 * @brief   This function is used to modify pattern in dynamic mode of wait template test.
 * 		    Directly using pattern-api to change DDR memory and execute pattern test.
 * 		    Finally save the necessary data in pattern file
 * @param 	timeS:	the wait time in second

 * @note	NONE
 * */
void d2s::wait_cycles(unsigned long cycles) {
	if (d2s::work_mode == ProductionMode && is_pre_d2s) {
		return;
	}

	if(!bInd2sBlock) {
		MessageBox(NULL, "[wait_cycles] can only be used inside a d2s_LABEL_BEGIN/END-block.", "Error", MB_OK);
		return;
	}
	string newPatternName = getNewWaitPatternName(cycles);
	bool pattern_exist = checkPatternNameExist(newPatternName);
	if(!is_pre_d2s)
	{
		vecPatternLsit.push_back(newPatternName);
		mapPatternLsit[newPatternName] = true;
	}

	if(d2s::work_mode == LearningMode) {
		string newPatternFile = d2s::patterns_path + newPatternName + ".cap";

		// dynamic set loop number
		uint32_t oprand = cycles;
		while(oprand / MAX_REPEAT_CYCLES > 0)
		{
			TheInst.Digital().Pattern().SetVectorMicroInstruction(getWaitTemplatePatternName(), 1, E_REPEAT, MAX_REPEAT_CYCLES);
			oprand -= MAX_REPEAT_CYCLES;
		}
		TheInst.Digital().Pattern().SetVectorMicroInstruction(getWaitTemplatePatternName(), 1, E_REPEAT, oprand);
		// Execute Pattern
		TheInst.Digital().Pattern().Start(getWaitTemplatePatternName());

		// save data in pattern file
		if(!pattern_exist && !is_pre_d2s) {
			getWaitTemplatFileInfos();
			PatternManager::UpdateWaitInfos(wait_t.template_vector, cycles);
			PatternManager::WritePatternFile(newPatternFile, wait_t.template_head, wait_t.template_vector, wait_t.template_tail);
		}
	}
	if(!is_pre_d2s) {
		vector_offset += 1;
		burst_name += newPatternName;
	}
}

/**
 * @brief   This function is used to modify pattern in dynamic mode of write template test.
 * 		    First convert the setting data in array.
 * 		    Then using pattern-api to change DDR memory and execute pattern test.
 * 		    Finally save the necessary data in pattern file
 * @param 	llAddress:	the address register
 * 			llData:     the data register
 * 			llMd5Data:  the md5 code using for new pattern name
 * @note
 * */
void d2s::expectValue(long long llAddress, long long llData, long long mask) {
	if (d2s::work_mode == ProductionMode && is_pre_d2s) {
		return;
	}

	if(!bInd2sBlock) {
		MessageBox(NULL, "[write] can only be used inside a d2s_LABEL_BEGIN/END-block.", "Error", MB_OK);
		return;
	}
	bExpectValue = true;
	getExpectRegisterAttribute();
	string newPatternName = getNewExpectPatternName(llAddress, llData, vectors_attr_t[Expect].positive_addr, vectors_attr_t[Expect].positive_data);
	newPatternName = newPatternName + "_" + to_string(mask);
	bool pattern_exist = checkPatternNameExist(newPatternName);
	if(!is_pre_d2s)
	{
		vecPatternLsit.push_back(newPatternName);
		mapPatternLsit[newPatternName] = true;
	}

	if(d2s::work_mode == LearningMode) {
		string newPatternFile = d2s::patterns_path + newPatternName + ".cap";

		unsigned long* addr_array = new unsigned long[vectors_attr_t[Expect].addr_vectors];
		unsigned long* data_array = new unsigned long[vectors_attr_t[Expect].data_vectors];

		string str_addr = ConvertToArray(llAddress, addr_array, vectors_attr_t[Expect].addr_vectors, vectors_attr_t[Expect].positive_addr); // convert llAddress to array and string
		string str_data = ConvertToArray(llData, data_array, vectors_attr_t[Expect].data_vectors, vectors_attr_t[Expect].positive_data, getLowStrobeWaveformChar(), getHighStrobeWaveformChar(), mask);    // convert llData to array and string

		// Dynamic change pattern
		DynamicSetVectors(getExpectTemplatePatternName(), getExpectAddressPinName(), vectors_attr_t[Expect].start_addr, vectors_attr_t[Expect].addr_vectors, addr_array);
		DynamicSetVectors(getExpectTemplatePatternName(), getExpectPinName(), vectors_attr_t[Expect].start_data, vectors_attr_t[Expect].data_vectors, data_array);
		// Execute Pattern
//	    TheInst.Digital().PatEng().SetupMCFData();
//		TheInst.Digital().PatEng().SetFailMode(PhxAPI::E_SET_HIL_MODE);
//		cout<<"expect  LearningMode newPatternFile="<<newPatternFile<<endl;
//		cout<<"expect  LearningMode getExpectTemplatePatternName="<<getExpectTemplatePatternName()<<endl;
//		cout<<"expect  LearningMode getExpectAddressPinName="<<getExpectAddressPinName()<<endl;
//		cout<<"expect  LearningMode getExpectPinName="<<getExpectPinName()<<endl;
		TheInst.Digital().Pattern().Start(getExpectTemplatePatternName());

		// save data in pattern file
		if(!pattern_exist && !is_pre_d2s) {
			getExpectTemplatFileInfos();
			PatternManager::UpdateVectorInfos(&expect_t.template_vectors, getExpectAddressPinName(), expect_t.template_signals, vectors_attr_t[Expect].start_addr, str_addr);
			PatternManager::UpdateVectorInfos(&expect_t.template_vectors, getExpectPinName(), expect_t.template_signals, vectors_attr_t[Expect].start_data, str_data);
			PatternManager::WritePatternFile(newPatternFile, expect_t.template_head, &expect_t.template_vectors, expect_t.template_tail);
		}

		delete[] addr_array;
		delete[] data_array;
	}

	if(!is_pre_d2s) {
		vector_offset += getExpectPatternVectors();
		burst_name += newPatternName;
	}

	return;
}

/*
 * @brief 	Modify pattern in dynamic mode with different data in different site<array>.
 * 			First modify address register in DDR, then get each site data to modify data register in DDR.
 * 			For Learning Mode, the start vector is equal to the LSB/MSB,
 * 			but in ProductionMode, the start vector is calculated after offset from the position of he previous vectors.
 * 			And in Learning Mode, the pattern is need to executed while with no need for Production Mode.
 * @param   NONE
 * @note 	Please check data register modification in different site how to work.
 * 			Worries: site mask how to handle and whether the DDR data is covered for the last time???
 */
void d2s::writeDynamic(long long llAddress, long long* llData, std::string id) {
	if (d2s::work_mode == ProductionMode && is_pre_d2s) {
		return;
	}

	if(!bInd2sBlock) {
		MessageBox(NULL, "[writeDynamic] can only be used inside a d2s_LABEL_BEGIN/END-block.", "Error", MB_OK);
		return;
	}

	string newPatternName = getWriteDynamicPatternName(llAddress, vectors_attr_t[Write].positive_addr, id);
	getWriteRegisterAttribute();
	bool pattern_exist = checkPatternNameExist(newPatternName);
	if(!is_pre_d2s)
	{
		vecPatternLsit.push_back(newPatternName);
		mapPatternLsit[newPatternName] = true;
	}

	unsigned long* addr_array = new unsigned long[vectors_attr_t[Write].addr_vectors];
	unsigned long* data_array = new unsigned long[vectors_attr_t[Write].data_vectors];

	if(d2s::work_mode == LearningMode) {
		string newPatternFile = d2s::patterns_path + newPatternName + ".cap";
		int start_addr = vectors_attr_t[Write].start_addr;
		int start_data = vectors_attr_t[Write].start_data;

		string str_addr = ConvertToArray(llAddress, addr_array, vectors_attr_t[Write].addr_vectors, vectors_attr_t[Write].positive_addr); // convert llAddress to array and string
		DynamicSetVectors(getWriteTemplatePatternName(), getWritePinName(), start_addr, vectors_attr_t[Write].addr_vectors, addr_array);

		string str_data = "";
		map<uint32_t, vector<uint32_t> > map_data_array;
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			str_data = ConvertToArray(llData[SiteID], data_array, vectors_attr_t[Write].data_vectors, vectors_attr_t[Write].positive_data);
			vector<uint32_t> vec_data_array(data_array, data_array+vectors_attr_t[Write].data_vectors);
			map_data_array[SiteID] = vec_data_array;
		FOREACH_ACTIVESITE_END

		// Dynamic change pattern
		DynamicSetSiteVectors(getWriteTemplatePatternName(), getWritePinName(), start_data, vectors_attr_t[Write].data_vectors, map_data_array);
		// Execute Pattern
		TheInst.Digital().Pattern().Start(getWriteTemplatePatternName());

		// save data in pattern file
		if(!pattern_exist && !is_pre_d2s) {
			getWriteTemplatFileInfos();
			PatternManager::UpdateVectorInfos(&write_t.template_vectors, getWritePinName(), write_t.template_signals, vectors_attr_t[Write].start_addr, str_addr);
			PatternManager::UpdateVectorInfos(&write_t.template_vectors, getWritePinName(), write_t.template_signals, vectors_attr_t[Write].start_data, str_data);
			PatternManager::WritePatternFile(newPatternFile, write_t.template_head, &write_t.template_vectors, write_t.template_tail);
		}
	} else {
		int start_addr = vectors_attr_t[Write].start_addr + vector_offset;
		int start_data = vectors_attr_t[Write].start_data + vector_offset;
		string str_addr = ConvertToArray(llAddress, addr_array, vectors_attr_t[Write].addr_vectors, vectors_attr_t[Write].positive_addr); // convert llAddress to array and string
		vector<unsigned long> addr_info(addr_array, addr_array + vectors_attr_t[Write].addr_vectors);
		map<int, vector<unsigned long> > data_info;
		string str_data = "";
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			str_data = ConvertToArray(llData[SiteID], data_array, vectors_attr_t[Write].data_vectors, vectors_attr_t[Write].positive_data);
			vector<unsigned long> temp_array(data_array, data_array + vectors_attr_t[Write].data_vectors);
			data_info[SiteID] = temp_array;
		FOREACH_ACTIVESITE_END

		vecDynamicList.push_back(d2sWriteDynamic(getWritePinName(), start_addr, vectors_attr_t[Write].addr_vectors, addr_info, \
				start_data, vectors_attr_t[Write].data_vectors, data_info));
	}

	if(!is_pre_d2s) {
		vector_offset += getWritePatternVectors();
		burst_name += "writeDynamic";
	}

	delete[] addr_array;
	delete[] data_array;
}

/*
 * @brief 	Modify pattern in dynamic mode with different data in different site<map>.
 * 			First modify address register in DDR, then get each site data to modify data register in DDR.
 * 			For Learning Mode, the start vector is equal to the LSB/MSB,
 * 			but in ProductionMode, the start vector is calculated after offset from the position of he previous vectors.
 * 			And in Learning Mode, the pattern is need to executed while with no need for Production Mode.
 * @param   NONE
 * @note 	Please check data register modification in different site how to work.
 * 			Worries: site mask how to handle and whether the DDR data is covered for the last time???
 */
void d2s::writeDynamic(long long llAddress, map<int, long long> llData, std::string id) {

	long long data[MAX_SITES];
	memset(data, 0xdeadbeaf, MAX_SITES*sizeof(long long));

	for (map<int, long long>::const_iterator it = llData.begin(); it != llData.end(); it++) {
		int siteID = it->first;
		long long temp = it->second;
		if (siteID >= 0 && siteID < MAX_SITES) {
			data[siteID] = temp;
		}
	}
	writeDynamic(llAddress, data, id);

}


string d2s::get_d2s_type() {
	if (is_pre_d2s) {
		return "pre_d2s";
	} else {
		return "d2s";
	}
}

/*
 * @brief 	Convert the long long data to array.
 *
 * @param   src_data: the long long value
 * 			des_array: the returned vector array
 * 			num_vectors: the length of vectors
 * 			bPositive: LSB>MSB or LSB<MSB
 * 			mask: using to decide the char of vector
 * @return  the long long value in string, using to save in .cap
 *
 * @note 	NONE
 *
 */
string d2s::ConvertToArray(long long src_data, unsigned long * des_array, unsigned long num_vectors, bool bPositive, unsigned long mask) {
	ostringstream des_str;
	unsigned long maskBit = 0;
	unsigned long shift = 0;

	for(unsigned long index = 0; index < num_vectors; index++) {
		shift = bPositive? index : (num_vectors - 1 - index);
		des_array[index] = ((src_data >> (shift / getPadding())) & 0x01);
		maskBit = ((mask >> (shift / getPadding())) & 0x01);
		if(maskBit == 0x01) {
			des_str << (des_array[index] == 0 ? getLowWaveformChar() : getHighWaveformChar());
		} else {
			des_array[index]=3;  //0826
			des_str << 'X';
		}

	}

	return des_str.str();
}

string d2s::ConvertToArray(long long src_data, unsigned long * des_array, unsigned long num_vectors, bool bPositive, char low_waveform, char high_waveform, unsigned long mask) {
	ostringstream des_str;
	unsigned long maskBit = 0;
	unsigned long shift = 0;

	for(unsigned long index = 0; index < num_vectors; index++) {
		shift = bPositive? index : (num_vectors - 1 - index);
		des_array[index] = ((src_data >> (shift / getPadding())) & 0x01);
		maskBit = ((mask >> (shift / getPadding())) & 0x01);
		if(maskBit == 0x01) {
			des_str << (des_array[index] == 0 ? low_waveform : high_waveform);
		} else {
			des_array[index]=3;  //0826
			des_str << 'X';
		}
	}

	return des_str.str();
}
/*
 * @brief 	Set vectors in dynamic mode
 *
 * @param
 *
 * @return
 *
 * @note
 *
 */
void d2s::DynamicSetVectors(string pat_name, string pin_name, unsigned long start_addr, unsigned long num_vectors, unsigned long * array) {
	vector<uint32_t> vec_data_array(array, array+num_vectors);
	// dynamic set new vectors
	TheInst.Digital().Pattern().SetVectorDataArray(pat_name, pin_name, start_addr, num_vectors, vec_data_array);

	return;
}

void d2s::DynamicSetSiteVectors(string pat_name, string pin_name, unsigned long start_addr, unsigned long num_vectors, map<uint32_t, vector<uint32_t> > map_data) {
	map<string, map<uint32_t, vector<uint32_t> > > map_pin_data_array;
	map_pin_data_array[pin_name] = map_data;
	// dynamic set new vectors
	 TheInst.Digital().Pattern().SetVectorSitesDataArray(pat_name, start_addr, num_vectors, map_pin_data_array);

	return;
}

/*
 * @brief 	Convert the long long data to array.
 *
 * @param
 *
 * @return
 *
 * @note
 *
 */
int d2s::ConvertCaptureData(unsigned long cap_data) {
	int ret = 0;
	switch(cap_data) {
	case 0:          // L
		ret = 0;
		break;
	case 1:          // H
		ret = 1;
		break;
	case 3:          // M
		ret = 1;
//		cout << "[d2s] error capture data[M]" << endl;
		break;
	default:
		break;
	}
	return ret;
}

map<int, long long> d2s::GetCaptureData(string pin_name, unsigned long start_addr, unsigned long bits, bool bPositive) {
	map<int, long long> rv_data;
	// attention
	map<uint32_t, map<string, vector<PatEngGetCaptureData> > > mapCap_data;
	mapCap_data = TheInst.Digital().PatEng().GetCaptureData(pin_name);

	if(mapCap_data.size() <= 0) {
		for(int site = 0; site < active_sites.size(); site++) {
			rv_data[active_sites.at(site)] = 0x0;
		}
		return rv_data;
	}

	for(map<uint32_t, map<string, vector<PatEngGetCaptureData> > >::iterator it = mapCap_data.begin(); it != mapCap_data.end(); it++) {
		long long cap_data = 0;
//		vector<uint8_t> veccap_data;
		for(map<string, vector<PatEngGetCaptureData> >::iterator itt = it->second.begin(); itt != it->second.end(); itt++) {
			if(itt->second.size() < (start_addr + bits))
			{
				cout << "capture data is oversize(" << itt->second.size() << " )"<< endl;
				continue;
			}
//			cout<<"==checking== "<<"d2s::GetCaptureData  rawData= ";  //add by tony 20210827
//			for(int i = 0; i < bits; i++) {
//				veccap_data.push_back(ConvertCaptureData(itt->second.at(start_addr+i)>>2));
//				cout<< (ConvertCaptureData(itt->second.at(start_addr+i)>>2));  //add by tony 20210827
//			}
//			cout<<endl;  //add by tony 20210827

			for (unsigned long index = 0; index < bits; index++) {
				unsigned long shift = bPositive ? index : (bits - index - 1);
				cap_data += (itt->second.at(start_addr+index).iECResult) * (1 << shift);
			}
			rv_data[it->first] = cap_data;
			break;
		}
	}

	return rv_data;
}

void d2s::doWriteDynamicInProductionMode(string pat_name) {
	for(auto writeDynamic : vecDynamicList) {
		unsigned long * addrArray = new unsigned long[writeDynamic.addr_vectors];
		unsigned long * dataArray = new unsigned long[writeDynamic.data_vectors];
		map<uint32_t, vector<uint32_t> > map_data_array;

		memcpy(addrArray, &writeDynamic.addr_array[0], writeDynamic.addr_array.size() * sizeof(unsigned long));
		DynamicSetVectors(pat_name, writeDynamic.pin_name, writeDynamic.addr_start, writeDynamic.addr_vectors, addrArray);

//		for(map<int ,vector<unsigned long> >::iterator it = writeDynamic.data_array.begin(); it != writeDynamic.data_array.end(); it++) {
////			if(!TheSoft.Sites().Active().GetActiveState(site_index)) continue;
//			vector<unsigned long> data_list = it->second;
//			memcpy(dataArray, &data_list[0], data_list.size() * sizeof(unsigned long));
//			DynamicSetVectors(test_name, writeDynamic.pin_name, writeDynamic.data_start, writeDynamic.data_vectors, dataArray);
//		}
		for(map<int ,vector<unsigned long> >::iterator it = writeDynamic.data_array.begin(); it != writeDynamic.data_array.end(); it++) {
			map_data_array[it->first].insert(map_data_array[it->first].end(), it->second.begin(), it->second.end());
		}
		DynamicSetSiteVectors(pat_name, writeDynamic.pin_name, writeDynamic.data_start, writeDynamic.data_vectors, map_data_array);

		delete[] addrArray;
		delete[] dataArray;
	}
}

/*
 * @brief 	compute some attributes by vector parameters.
 *
 * @param 	NONE
 *
 * @return	NONE
 *
 * @note	NONE
 *
 */
void d2s::getWriteRegisterAttribute() {
	vectors_attr_t[Write].positive_addr = getWriteAddressVectorNumberLSB() < getWriteAddressVectorNumberMSB()? true : false;
	vectors_attr_t[Write].positive_data = getWriteDataVectorNumberLSB() < getWriteDataVectorNumberMSB()? true : false;
	vectors_attr_t[Write].start_addr = vectors_attr_t[Write].positive_addr? getWriteAddressVectorNumberLSB() : getWriteAddressVectorNumberMSB();
	vectors_attr_t[Write].start_data = vectors_attr_t[Write].positive_data? getWriteDataVectorNumberLSB() : getWriteDataVectorNumberMSB();
	vectors_attr_t[Write].addr_vectors = getAddressBits() * getPadding();
	vectors_attr_t[Write].data_vectors = getDataBits() * getPadding();
}

void d2s::getReadRegisterAttribute() {
	vectors_attr_t[Read].positive_addr = getReadAddressVectorNumberLSB() < getReadAddressVectorNumberMSB()? true : false;
	vectors_attr_t[Read].positive_data = getReadDataVectorNumberLSB() < getReadDataVectorNumberMSB()? true : false;
	vectors_attr_t[Read].start_addr = vectors_attr_t[Read].positive_addr? getReadAddressVectorNumberLSB() : getReadAddressVectorNumberMSB();
	vectors_attr_t[Read].start_data = vectors_attr_t[Read].positive_data? getReadDataVectorNumberLSB() : getReadDataVectorNumberMSB();
	vectors_attr_t[Read].addr_vectors = getAddressBits() * getPadding();
	vectors_attr_t[Read].data_vectors = getDataBits() * getPadding();

}

void d2s::getExpectRegisterAttribute() {
	vectors_attr_t[Expect].positive_addr = getExpectAddressVectorNumberLSB() < getExpectAddressVectorNumberMSB()? true : false;
	vectors_attr_t[Expect].positive_data = getExpectDataVectorNumberLSB() < getExpectDataVectorNumberMSB()? true : false;
	vectors_attr_t[Expect].start_addr = vectors_attr_t[Expect].positive_addr? getExpectAddressVectorNumberLSB() : getExpectAddressVectorNumberMSB();
	vectors_attr_t[Expect].start_data = vectors_attr_t[Expect].positive_data? getExpectDataVectorNumberLSB() : getExpectDataVectorNumberMSB();
	vectors_attr_t[Expect].addr_vectors = getAddressBits() * getPadding();
	vectors_attr_t[Expect].data_vectors = getDataBits() * getPadding();

}

/*
 * @brief 	read cap to get the count of vectors in template cap.
 *
 * @param 	NONE
 *
 * @return	1: OK
 * 			-5: the setting pattern vectors != the count vectors in write mode
 * 			-6: the setting pattern vectors != the count vectors in read mode
 *
 * @note	NONE
 *
 */
int d2s::getWriteTemplatFileInfos() {
	int vectors_cnt = 0;
	string strWriteTemplateFile;
	string str1 = ".cbp", str2 = ".cap";

	vector<string> patternlist = TheSoft.Flow().Pattern().GetBurshPathList(getWriteTemplatePatternName());
	if(patternlist.size() > 0) {
		strWriteTemplateFile = d2s::patterns_path + patternlist.at(0);
		if(strWriteTemplateFile.find(".cbp") != string::npos) {
			strWriteTemplateFile.replace(strWriteTemplateFile.find(str1), str1.size(), str2, 0, str2.size());
		}
	} else {
		return 0;      // error
	}

	PatternManager::GetHeadInfos(strWriteTemplateFile, write_t.template_head, write_t.template_signals);
	PatternManager::GetVectorsInfos(strWriteTemplateFile, &write_t.template_vectors, vectors_cnt);
	if(vectors_cnt != getWritePatternVectors()) {
		return -5;
	}
	write_t.template_tail = "";

	return 1;
}

int d2s::getReadTemplatFileInfos() {
	int vectors_cnt = 0;
	string strReadTemplateFile;
	string str1 = ".cbp", str2 = ".cap";

	vector<string> patternlist = TheSoft.Flow().Pattern().GetBurshPathList(getReadTemplatePatternName());
	if(patternlist.size() > 0) {
		strReadTemplateFile = d2s::patterns_path + patternlist.at(0);
		if(strReadTemplateFile.find(".cbp") != string::npos) {
			strReadTemplateFile.replace(strReadTemplateFile.find(str1), str1.size(), str2, 0, str2.size());
		}
	} else {
		return 0;      // error
	}

	PatternManager::GetHeadInfos(strReadTemplateFile, read_t.template_head, read_t.template_signals);
	PatternManager::GetVectorsInfos(strReadTemplateFile, &read_t.template_vectors, vectors_cnt);
	if(vectors_cnt != getReadPatternVectors()) {
		return -6;
	}
	read_t.template_tail = "";

	return 1;
}

int d2s::getWaitTemplatFileInfos() {
	int vectors_cnt = 0;
	string strWaitTemplateFile;
	string str1 = ".cbp", str2 = ".cap";

	vector<string> patternlist = TheSoft.Flow().Pattern().GetBurshPathList(getWaitTemplatePatternName());
	if(patternlist.size() > 0) {
		strWaitTemplateFile = d2s::patterns_path + patternlist.at(0);
		if(strWaitTemplateFile.find(".cbp") != string::npos) {
			strWaitTemplateFile.replace(strWaitTemplateFile.find(str1), str1.size(), str2, 0, str2.size());
		}
	} else {
		return 0;      // error
	}

	PatternManager::GetHeadInfos(strWaitTemplateFile, wait_t.template_head, wait_t.template_signals);
	PatternManager::GetWaitInfos(strWaitTemplateFile, wait_t.template_vector);
	wait_t.template_tail = "";

	return 1;
}

/*
 * @brief 	read cap to get the count of vectors in template cap.
 *
 * @param 	NONE
 *
 * @return	1: OK
 * 			-5: the setting pattern vectors != the count vectors in write mode
 * 			-6: the setting pattern vectors != the count vectors in read mode
 *
 * @note	NONE
 *
 */
int d2s::getExpectTemplatFileInfos() {
	int vectors_cnt = 0;
	string strExpectTemplateFile;
	string str1 = ".cbp", str2 = ".cap";

	vector<string> patternlist = TheSoft.Flow().Pattern().GetBurshPathList(getExpectTemplatePatternName());
	if(patternlist.size() > 0) {
		strExpectTemplateFile = d2s::patterns_path + patternlist.at(0);
		if(strExpectTemplateFile.find(".cbp") != string::npos) {
			strExpectTemplateFile.replace(strExpectTemplateFile.find(str1), str1.size(), str2, 0, str2.size());
		}
	} else {
		return 0;      // error
	}

	PatternManager::GetHeadInfos(strExpectTemplateFile, expect_t.template_head, expect_t.template_signals);
	PatternManager::GetVectorsInfos(strExpectTemplateFile, &expect_t.template_vectors, vectors_cnt);
	if(vectors_cnt != getExpectPatternVectors()) {
		return -5;
	}
	expect_t.template_tail = "";

	return 1;
}

/*
 * @brief 	get new pattern name of write test.
 *
 * @param 	address: the setting address data
 * 			data: the setting data data
 * 			bPositiveAddr/bPositiveData: LSB VS MSB
 *
 * @return 	the new name
 *
 * @note 	NONE
 */
string d2s::getNewWritePatternName(long long address, long long data, bool bPositiveAddr, bool bPositiveData) {
    ostringstream pattern_name;
    pattern_name << "d2s_" << getInterfaceName() << "_"  << getWritePinName() \
    			 << "_"  << (bPositiveAddr? "P" : "N") << (bPositiveData? "P" : "N") << "_Write_0x" << hex << address << "_0x" << data;
    return pattern_name.str();
}


string d2s::getNewWritePatternName_MD5(long long address, long long data, bool bPositiveAddr, bool bPositiveData, long long md5data) {
    ostringstream pattern_name;
    if(md5data == 0XFFFFFFFF){
        pattern_name << "d2s_" << getInterfaceName() \
        		<< "_"  << (bPositiveAddr? "P" : "N") << (bPositiveData? "P" : "N") << "_Write_0x" << hex << address << "_0x" << data;
    }
    else{
        pattern_name << "d2s_" << getInterfaceName() \
        		<< "_"  << (bPositiveAddr? "P" : "N") << (bPositiveData? "P" : "N") << "_Write_0x" << hex << address << "_0x" << md5data;
    }
    return pattern_name.str();
}
/*
 * @brief 	get new pattern name of read test.
 *
 * @param 	address: the setting address data
 * 			bPositiveAddr: LSB VS MSB
 * 			id: the id of capture label
 *
 * @return 	the new name
 *
 * @note 	NONE
 */
string d2s::getNewReadPatternName(long long address, bool bPositiveAddr, int offset) {
	ostringstream pattern_name;
//	string current_test = TheSoft.Flow().Test().GetCurrentTestName();    //@20211129 add

	pattern_name << "d2s_" << getInterfaceName() << "_" << getReadAddressPinName() \
				 << "_"  << (bPositiveAddr? "P" : "N") << "_Read_0x" << hex << address <<  "_sync_"<< offset;    //@20211130 change
//	if(id != "") {
//		pattern_name << "_" << id;
//	}

	return pattern_name.str();
}

/*
 * @brief 	get new pattern name of wait test in second.
 *
 * @param 	timeS: the waiting time in second
 *
 * @return 	the new name
 *
 * @note 	NONE
 */
string d2s::getNewWaitPatternName(double timeS) {
    ostringstream pattern_name;
    pattern_name << "d2s_" << getInterfaceName() << "_wait_" << timeS << "S";
    return pattern_name.str();
}

/*
 * @brief 	get new pattern name of wait test in cycles.
 *
 * @param 	timeS: the waiting cycles
 *
 * @return 	the new name
 *
 * @note 	NONE
 */
string d2s::getNewWaitPatternName(unsigned long cycles) {
    ostringstream pattern_name;
    pattern_name << "d2s_" << getInterfaceName() << "_wait_" << dec << cycles;
    return pattern_name.str();
}

/*
 * @brief 	get new pattern name of expect test.
 *
 * @param 	address: the setting address data
 * 			data: the setting data data
 * 			bPositiveAddr/bPositiveData: LSB VS MSB
 *
 * @return 	the new name
 *
 * @note 	NONE
 */
string d2s::getNewExpectPatternName(long long address, long long data, bool bPositiveAddr, bool bPositiveData) {
    ostringstream pattern_name;
    pattern_name << "d2s_" << getInterfaceName() << "_"  << getExpectPinName() \
    			 << "_"  << (bPositiveAddr? "P" : "N") << (bPositiveData? "P" : "N") << "_EV_0x" << hex << address << "_0x" << data;
    return pattern_name.str();
}

/*
 * @brief 	get new pattern name of dynamic write test.
 *
 * @param 	address: the setting address data
 *
 * @return 	the new name
 *
 * @note 	NONE
 */
string d2s::getWriteDynamicPatternName(long long address, bool bPositiveAddr, string id) {
	ostringstream pattern_name;
	pattern_name << "d2s_" << getInterfaceName() << "_"  << getWritePinName() \
	    			 << "_"  << (bPositiveAddr? "P" : "N") << "_WriteD_0x_" << hex << address;
	pattern_name << "_" << id;
	return pattern_name.str();
}

/*
 * @brief 	Union each pattern name to burst pattern block name.
 *
 * @param 	None
 *
 * @return 	Finally the name is like "d2s_123123_Test1_md5code".
 *
 * @note 	Every d2s in one test has different name pattern block name with the different md5.
 * 			Every test with different pattern block name with the different test name.
 */
string d2s::getBurstPatternBlockName() {
	ostringstream patternblock_name;
	string current_test = TheSoft.Flow().Test().GetCurrentTestName();

	patternblock_name << "d2s_" << d2s::burstpattern_prefix << "_" << current_test << "_" << MD5(burst_name).toString();
	return patternblock_name.str();
}

/*
 * @brief 	check new pattern name if already exist. If it exists, then return.
 *
 * @param 	newPatternName: new pattern name
 * 			patlist: already existing pattern names
 *
 * @return 	true: exist, return.
 * 			false: not exist, continue
 *
 * @note 	NONE
 */
bool d2s::checkPatternNameExist(const string newPatternName) {

	return mapPatternLsit[newPatternName];
}

//bool d2s::checkPatternNameExist(const string newPatternName, vector<string>& patlist) {
//
//	if(find(patlist.begin(), patlist.end(), newPatternName) != patlist.end()) {
//		if(d2s::work_mode == LearningMode) {
//			cout << "pattern name \"" << newPatternName << "\" already exist" << endl;
//		}
//		return true;
//	}
//
//	return false;
//}
