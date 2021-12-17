/*
 * PatternManager.h
 *
 *  Created on: 2021��5��25��
 *      Author: dongyuqing
 */

#ifndef PATTERNMANAGER_H_
#define PATTERNMANAGER_H_

#include <vector>
#include <string>
using namespace std;

#define MAX_REPEAT_CYCLES    (1<<14)

class PatternManager {
public:
	static int GetHeadInfos(const string pattern_file, string &str_head, string &str_signals);
	static int GetVectorsInfos(const string pattern_file, vector<string>* vector_list, int &vector_count);
	static int GetWaitInfos(const string pattern_file, string &str_wait);
	static int GetTailInfos(const string pattern_file, string &str_tail);

	static int UpdateVectorInfos(vector<string>* vector_list, const string pin_name, const string pin_list, const unsigned long start, const string str_array);
	static int UpdateWaitInfos(string &str_wait, int cycles);
	static int WritePatternFile(const string pattern_file, const string str_head, vector<string>* vector_list, const string str_tail, bool bCreate = true);
	static int WritePatternFile(const string pattern_file, const string str_head, const string str_vector, const string str_tail, bool bCreate = true);
	static int UpdatePatternBlock(const string patternblock_file, const string new_patternblock_name, vector<string> pattern_list);

public:
	static string ConvertVectorListToString(vector<string>* vector_list);
	static int GetRepeatCountInStr(const string & strStream, const string & str);

	// xixi debug
public:
	static int SaveBurstName(const string file, const string str_wf);
	static bool isPatternAvailable(const std::string& labelFile, const std::string& labelType="ALL",const std::string& port="@@");
    static int createBurst(const std::string& burstName, std::vector<std::string> labelsToCall, const std::string& portName="", bool warnEmpty=true);
    static int deleteLabel(const std::string& label, const std::string& portName="");
    static unsigned long long getCyclesFromLabel(const std::string& label, const std::string& portName="@");
    static int copyLabel(const std::string& sourceLabel, const std::string& destinationLabel);
    static int renameLabel(const std::string& sourceLabel, const std::string& destinationLabel);
    static int saveLabel(const std::string& labelName);
    static int mergeLabelFromFile(const std::string& fileName);
};



#endif /* PATTERNMANAGER_H_ */
