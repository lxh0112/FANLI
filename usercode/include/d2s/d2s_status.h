/*
 * d2s_status.h
 *
 *  Created on: Jun 16, 2016
 *      Author: yanfen.fang
 */

#ifndef D2S_STATUS_H_
#define D2S_STATUS_H_

//#include "mapi.hpp"
#include <map>
#include <string>
using namespace std;
#define CREATE_PATTERN_BY_FW

namespace std {

class d2s_status {
private:
	static map<string,string> status;
	static string last_suitename;
	static void check_suite_change();
public:
	static void set_status(const string& id,const string& val);
	static void delete_status(const string& id);
	static string get_status();
	static bool isStatusAvailable(const string& id,string& result);
	d2s_status();
	virtual ~d2s_status();
};

} /* namespace std */
#endif /* D2S_STATUS_H_ */
