/*
 * PatternManager.cpp
 *
 *  Created on: 2021��5��25��
 *      Author: dongyuqing
 */
#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <helpers.h>
#include "string.h"
#include "PatternManager.h"

/*
 * @brief 	get the head info of .cap
 *
 * @param 	pattern_file: cap full path
 * 			str_head: the head info
 * 			str_signals: the signal list used in pattern part
 *
 * @return	1: OK
 * 			-1: cap open failed
 *
 * @note	NONE
 *
 */

int PatternManager::copyLabel(const std::string& sourceLabel, const std::string& destinationLabel) {

    renameLabel(sourceLabel, destinationLabel);

    saveLabel(destinationLabel);

    //rename original back
    renameLabel(destinationLabel, sourceLabel);

    //merge in the just created new label
    mergeLabelFromFile(destinationLabel);

    return 1;
}

int PatternManager::renameLabel(const std::string& sourceLabel, const std::string& destinationLabel) {

    return 1;
}

int PatternManager::saveLabel(const std::string& labelName) {

    return 0; //爲了編譯通過+的
}

int PatternManager::mergeLabelFromFile(const std::string& fileName) {

    return 1;
}

int PatternManager::createBurst(const std::string& burstName, vector<string> labelsToCall, const std::string& portName, bool warnEmpty) {
   // assert(burstName.size() <= 128);

    return 1;
}

int PatternManager::deleteLabel(const std::string& label, const std::string& port) {


    return 1;
}

unsigned long long PatternManager::getCyclesFromLabel(const std::string& label, const std::string& port) {
    int seqNoStart;
    int seqNoStop;

}

bool PatternManager::isPatternAvailable(const string& labelFile, const string& labelType, const string& port) {
    //    fwout << "SQLB? \"" << labelFile << "\"," << labelType << ",(" << port << ")" << endl;
    //   // cout << "SQLB? \"" << labelFile << "\"," << labelType << ",(" << port << ")" << endl;
    //    if(fwresult.size() >0){
    //        return true;
    //    }
    //    else{
    //        return false;
    //    }
    return true;
}

int PatternManager::GetHeadInfos(const string pattern_file, string &str_head, string &str_signals) {
	str_head = "";
	str_signals = "";
	ifstream file;
	file.open(pattern_file.data(), ios::in);
	if(!file.is_open()) {
		return -1;
	}

	string buff = "", signal_list_in_pattern = "";
	map<string, string> group_signal;
	while(getline(file, buff)) {
		if(buff.find("SignalGroups {") != string::npos) {
			str_head += buff + "\n";
			getline(file, buff);    // signal list
			while(buff.find("}") == string::npos) {    // at signalgroups end
				str_head += buff + "\n";
				string groupname = buff.substr(0, buff.find("="));
				string signalnames = buff.substr(buff.find("=")+1, buff.size());
				trim(groupname);
				replace(signalnames.begin(), signalnames.end(), '+', ',');
				signalnames = signalnames.substr(0, signalnames.size()-1);
				group_signal[groupname] = signalnames;
				getline(file, buff);
			}
		}
		if(buff.find("Pattern {") != string::npos) {
			str_head += buff + "\n";
			getline(file, buff);    // signal list in pattern
			signal_list_in_pattern = buff;
			break;
		}
		str_head += buff + "\n";
	}
//	str_head += str_signals + "\n";
	str_head += buff + "\n";

	file.close();

	// get actual singal list
	str_signals = signal_list_in_pattern;
	for(map<string, string>::iterator it = group_signal.begin(); it != group_signal.end(); it++) {
		if(str_signals.find(it->first) != string::npos) {
			str_signals.replace(str_signals.find(it->first), it->first.size(), it->second, 0, it->second.size());
		}
	}

	return 1;
}

/*
 * @brief 	get the vectors info of .cap
 *
 * @param 	pattern_file: cap full path
 * 			vector_list: the list of vectors
 * 			vector_count: the count of vectors
 *
 * @return	1: OK
 * 			-1: cap open failed
 *
 * @note	NONE
 *
 */
int PatternManager::GetVectorsInfos(const string pattern_file, vector<string>* vector_list, int &vector_count) {
	vector_list->clear();
	ifstream file;
	file.open(pattern_file.data(), ios::in);
	if(!file.is_open()) {
		return -1;
	}

	vector_count = 0;
	string str_vector = "";
	string buff = "";
	bool bfind_pattern = false;
	while(getline(file, buff)) {
		if(buff.find("Pattern {") != string::npos) {
			bfind_pattern = true;
			while(getline(file, buff)) {
				if(buff.find(">") != string::npos) {    // in vectors
					break;
				}
			}
		}
		if(bfind_pattern) {
			if(buff.find(">") != string::npos) {
				vector_count++;
			}
			vector_list->push_back(buff);
			str_vector += buff + "\n";
			if(buff.find("}") != string::npos) {
				break;
			}
		}
	}

	file.close();

	return 1;
}

/*
 * @brief 	get the vectors info of wait template .cap
 *
 * @param 	pattern_file: cap full path
 * 			str_wait: the wait template vector info
 *
 * @return	1: OK
 * 			-1: cap open failed
 *
 * @note	NONE
 *
 */
int PatternManager::GetWaitInfos(const string pattern_file, string &str_wait) {
	str_wait = "";
	ifstream file;
	file.open(pattern_file.data(), ios::in);
	if(!file.is_open()) {
		return -1;
	}

	string buff = "";
	bool bfind_pattern = false;
	while(getline(file, buff)) {
		if(buff.find("Pattern {") != string::npos) {
			bfind_pattern = true;
			while(getline(file, buff)) {
				if(buff.find(">") != string::npos) {    // in vectors
					break;
				}
			}
		}
		if(bfind_pattern) {
			str_wait += buff + "\n";
			if(buff.find("}") != string::npos) {
				break;
			}
		}
	}

	file.close();

	return 1;
}

/*
 * @brief 	get the tail info of .cap
 *
 * @param 	pattern_file: cap full path
 * 			str_tail: the tail info (currentlt it = timing block info)
 *
 * @return	1: OK
 * 			-1: cap open failed
 *
 * @note	NONE
 *
 */
int PatternManager::GetTailInfos(const string pattern_file, string &str_tail) {
	str_tail = "";
	ifstream file;
	file.open(pattern_file.data(), ios::in);
	if(!file.is_open()) {
		return -1;
	}

	string buff = "";
	bool bfind_tail = false;
	while(getline(file, buff)) {
		if(buff.find("TimingBlock {") != string::npos) {
			bfind_tail = true;
		}
		if(bfind_tail) {
			str_tail += buff + "\n";
		}
	}

	file.close();

	return 1;
}

/*
 * @brief 	update new vectors info
 *
 * @param 	vector_list: the orignal vectors, update with the new vectors and return
 * 			pin_name: the pin name updated
 * 			pin_list: the pin list in template cap
 * 			start: start updating address in vector list
 * 			str_array: the array to be updated
 *
 * @return	1: OK
 * 			-1: fail to find the pin name in pin list
 *
 * @note	NONE
 *
 */
int PatternManager::UpdateVectorInfos(vector<string>* vector_list, const string pin_name, const string pin_list, const unsigned long start, const string str_array) {
	int pin_index = 0;
	if(pin_list.find(pin_name) == string::npos) {
		return -1;
	}
	string strpinlist = pin_list;
	string key_word = pin_name + ",";

	int index = 0;
	string str = ",";
//	int signal_cnt = count(strpinlist.begin(), strpinlist.end(), ',') + 1;
	int signal_cnt = GetRepeatCountInStr(strpinlist, str) + 1;
	index = strpinlist.find(key_word);
	if(index == string::npos) {
		pin_index = signal_cnt;  // signal in end of the signal list
	} else {
		strpinlist = strpinlist.substr(0, index);
		pin_index = GetRepeatCountInStr(strpinlist, str) + 1;
//		pin_index = count(strpinlist.begin(), strpinlist.end(), ',') + 1;
	}

	string str_vector, str_replace;
	int end_index = 0, replace_index = 0;
	for(int idx = start; idx < str_array.length() + start; idx++) {
		str_vector = vector_list->at(idx);
		end_index = str_vector.find(';');
		replace_index = end_index - signal_cnt + pin_index;
		str_replace = str_array[idx - start];
		str_vector = str_vector.replace(replace_index-1, 1, str_replace);
		vector_list->at(idx) = str_vector;
	}

	return 1;
}

/*
 * @brief 	update new wait vectors info
 *
 * @param 	str_wait: the orignal wait info and will be update
 * 			cycles: the new cycles in wait template cap
 *
 * @return	1: OK
 *
 * @note	NONE
 *
 */
int PatternManager::UpdateWaitInfos(string &str_wait, int cycles) {
	string str_rv = str_wait;
	str_rv = str_rv.substr(0, str_rv.find('}'));
	int index = str_rv.find('>');
	if(index < 0)
	{
		ostringstream error_info;
		error_info << "Fail to read correct template [Wait]";
		MessageBox(NULL, error_info.str().data(), "Error", MB_OK);
		return -1;
	}

	str_rv = str_rv.substr(index, str_rv.length());
	str_wait = "";
	while(cycles > MAX_REPEAT_CYCLES && (cycles / MAX_REPEAT_CYCLES > 0))
	{
		str_wait += "  Repeat " + to_string(MAX_REPEAT_CYCLES) + "   " + str_rv;
		cycles -= MAX_REPEAT_CYCLES;
	}
	string ss = to_string(cycles);
	str_wait += "  Repeat " + ss + "   " + str_rv;
	str_wait += "  }";

	return 1;
}

/*
 * @brief 	write the new pattern file
 *
 * @param 	pattern_file: full pattern file path
 * 			str_head: the head info
 * 			vector_list: the list of vectors
 * 			str_tail: the tail info
 * 			bCreate: [true] create the new file, [false] append info to existing file
 *
 * @return	1: OK
 * 			-1: cap open failed
 *
 * @note	NONE
 *
 */
int PatternManager::WritePatternFile(const string pattern_file, const string str_head, vector<string>* vector_list, const string str_tail, bool bCreate) {
	ofstream write_file;
	if (bCreate) {
		write_file.open(pattern_file.data(), ios::out | ios::trunc);
	} else {
		write_file.open(pattern_file.data(), ios::app);
	}
	if (!write_file.is_open()) {
		return -1;
	}

	// head
	write_file << str_head;

	// vectors
	string str_vector = ConvertVectorListToString(vector_list);
	write_file << str_vector;

	// timingblock
	write_file << "\n";
	write_file << str_tail;

	write_file.close();
	return 0;
}

/*
 * @brief 	write the new pattern file
 *
 * @param 	pattern_file: full pattern file path
 * 			str_head: the head info
 * 			str_vector: the lvectors info
 * 			str_tail: the tail info
 * 			bCreate: [true] create the new file, [false] append info to existing file
 *
 * @return	1: OK
 * 			-1: cap open failed
 *
 * @note	NONE
 *
 */
int PatternManager::WritePatternFile(const string pattern_file, const string str_head, const string str_vector, const string str_tail, bool bCreate) {
	ofstream write_file;
	if (bCreate) {
		write_file.open(pattern_file.data(), ios::out | ios::trunc);
	} else {
		write_file.open(pattern_file.data(), ios::app);
	}
	if (!write_file.is_open()) {
		return -1;
	}

	// head
	write_file << str_head;

	// vectors
	write_file << str_vector;

	// timingblock
	write_file << "\n";
	write_file << str_tail;

	write_file.close();
	return 0;
}

int PatternManager::UpdatePatternBlock(const string patternblock_file, const string new_patternblock_name, vector<string> pattern_list) {
	return 1;
}

/*
 * @brief 	convert vector list to string
 *
 * @param 	vector_list: the vector list
 *
 * @return	the corresponding string
 *
 * @note	NONE
 *
 */
string PatternManager::ConvertVectorListToString(vector<string>* vector_list) {
	string str_vectors = "";
	for(int index = 0; index < vector_list->size(); index++) {
		str_vectors += vector_list->at(index) + "\n";
	}

	return str_vectors;
}

int PatternManager::GetRepeatCountInStr(const string & strStream, const string & str) {
	int count = 0;
	int begin = -1;
	while((begin = strStream.find(str, begin+1)) != string::npos) {
		count++;
		begin += str.length() - 1;
	}

	return count;
}
// xixi debug
int PatternManager::SaveBurstName(const string file, const string str_wf) {
	ofstream write_file;
	write_file.open(file.data(), ios::app);
	if (!write_file.is_open()) {
		return -1;
	}
	write_file << str_wf;
	write_file << "\n";

	write_file.close();
	return 0;
}
