/*
 * md5_pack.h
 *
 *  Created on: Jun 27, 2016
 *      Author: yanfen.fang
 */

#ifndef MD5_PACK_H_
#define MD5_PACK_H_
#include <string>
#include <vector>
#include <map>

using namespace std;
typedef unsigned char (MD5_RESULT)[16];

string get_MD5(const string &in);

#endif /* MD5_PACK_H_ */
