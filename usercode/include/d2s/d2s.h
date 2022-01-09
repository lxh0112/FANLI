/*
 * d2s.h
 *
 *  Created on: 2022/1/4
 *      Author: dongyuqing
 *      Modified: w00600447
 */

#ifndef d2s_H_
#define d2s_H_

#include <d2sStructDef.h>
#include <map>
#include <unordered_map>
#include <vector>
#include "d2sModes.h"
#include "d2sFramework.h"
using namespace std;

#define NO_FILE_EXIST      0xdeadcd

extern "C" class DLLAPI d2s {
public:
	d2s();
	~d2s();
	d2s(bool bPreD2S);
public:
	static void d2s_LABEL_BEGIN(std::string labelPrefix, d2sWorkModeType mode);
	static void d2s_LABEL_END();
	static bool isProductionMode();
	static bool is_in_d2s_block();
    static bool Is_simulator();

	void write(long long llAddress, long long llData, long long llMd5Data = 0XFFFFFFFF);
	void read(long long llAddress, string id, int offset);	//@20211030 change
	void wait(double timeS);
	void wait_cycles(unsigned long cycles);
	void expectValue(long long address, long long value, long long mask = 0XFFFFFFFF);
	void writeDynamic(long long llAddress, long long* llData, std::string id);
	void writeDynamic(long long llAddress, map<int, long long> llData, std::string id);
	map<int, long long> getReadValue(const string id);
	string get_d2s_type();
private:
	string ConvertToArray(long long src_data, unsigned long * des_array, unsigned long num_vectors, bool bPositive, unsigned long mask = 0xFFFFFFFF);
	string ConvertToArray(long long src_data, unsigned long * des_array, unsigned long num_vectors, bool bPositive, char low_waveform, char high_waveform, unsigned long mask = 0xFFFFFFFF);
	static void DynamicSetVectors(string pat_name, string pin_name, unsigned long start_addr, unsigned long num_vectors, unsigned long * array);
	static void DynamicSetSiteVectors(string pat_name, string pin_name, unsigned long start_addr, unsigned long num_vectors, map<uint32_t, vector<uint32_t> > map_data);
	int ConvertCaptureData(unsigned long cap_data);
	map<int, long long> GetCaptureData(string pin_name, unsigned long start_addr, unsigned long bits, bool bPositive = true);
	static void doWriteDynamicInProductionMode(string pat_name);
private:
	void getWriteRegisterAttribute();
	void getReadRegisterAttribute();
	void getExpectRegisterAttribute();
	int getWriteTemplatFileInfos();
	int getReadTemplatFileInfos();
	int getWaitTemplatFileInfos();
	int getExpectTemplatFileInfos();
	string getNewWritePatternName(long long address, long long data, bool bPositiveAddr, bool bPositiveData);
	string getNewWritePatternName_MD5(long long address, long long data, bool bPositiveAddr, bool bPositiveData,long long md5data = 0XFFFFFFFF);
	string getNewReadPatternName(long long address, bool bPositiveAddr, int offset);    //@20211030 change
	string getNewWaitPatternName(double timeS);
	string getNewWaitPatternName(unsigned long cycles);
	string getNewExpectPatternName(long long address, long long data, bool bPositiveAddr, bool bPositiveData);
	string getWriteDynamicPatternName(long long address, bool bPositiveAddr, string id);
	static string getBurstPatternBlockName();
private:
	bool checkPatternNameExist(const string newPatternName);
//	bool checkPatternNameExist(const string newPatternName, vector<string>& patlist);
private:
//	d2sParameter* pVectorAttribute;
	static vector<int> active_sites;
	static int site_count;
	static string patterns_path;

	static string burstpattern_prefix;
	static d2sWorkModeType work_mode;
	static bool bInd2sBlock;
	static bool bExpectValue;
	static string burst_name;
	static unsigned long vector_offset;   // the offset of each mode(equals to the count of each template pattern)
	static unsigned long capture_start_offset;
	static vector<string> vecPatternLsit;
	static unordered_map<string, bool> mapPatternLsit;
	static vector<d2sWriteDynamic> vecDynamicList;
	static map<string, map<int, long long> > capture_data_map;
	static map<string, unsigned long> capture_start_loc_map;
	static void d2s_LABEL_CLEAR(bool isBegin = true);
private:
	TemplateFile_T write_t;
	TemplateFile_T read_t;
	TemplateFile_T wait_t;
	TemplateFile_T expect_t;
	VectorsAttribute_T vectors_attr_t[3];
	bool is_pre_d2s;
public:
	/*general parameters*/
	/**
	 * @brief getAddressBits specifies how many bits are used to code the register address
	 *
	 * This method has to return the number of address bits
	 */
	virtual int getAddressBits() = 0;

	/**
	 * @brief getDataBits specifies how many data bits your device register has
	 *
	 * This method has to return the number of data bits
	 */
	virtual int getDataBits() = 0;

	/**
	 * @brief getPadding specifies how many padding vectors are specified in your templates
	 *
	 * Default padding is 1.
	 *
	 * This method has to return the number of padding vectors
	 */
	virtual int getPadding() = 0;

	/**
	 * @brief getHighWaveformIndex specifies the waveform index of your wavetable that is used for driving a 1
	 */
	char getHighWaveformChar() {
		return '1';
	};

	/**
	 * @brief getLowWaveformIndex specifies the waveform index of your wavetable that is used for driving a 0
	 */
	char getLowWaveformChar() {
		return '0';
	};

	/**
	 * @brief getHighWaveformIndex specifies the waveform index of your wavetable that is used for comparing for a 1
	 */
	char getHighStrobeWaveformChar() {
		return 'H';
	};

	/**
	 * @brief getLowWaveformIndex specifies the waveform index of your wavetable that is used for comparing for a 0
	 */
	char getLowStrobeWaveformChar() {
		return 'L';
	};

	/**
	 * @brief getLowWaveformIndex specifies the waveform index of your wavetable that is used for comparing for a X
	 */
	// virtual W getMaskStrobeWaveformIndex() = 0;


	/*write parameters*/

	/**
	 * @brief getWritePinName specifies the pinname that drives the address and data.
	 */
	virtual string getWritePinName() = 0;


	/**
	 * @brief getWriteAddressVectorNumberLSB specifies the vector number that contains the least significant ADDRESS bit (LSB).
	 *
	 * In case of padding !=1 this is the first vector number before additional padding vectors
	 */
	virtual int getWriteAddressVectorNumberLSB() = 0;

	/**
	 * @brief getWriteAddressVectorNumberMSB specifies the vector number that contains the most significant ADDRESS bit (MSB).
	 *
	 * In case of padding !=1 this is the first vector number before additional padding vectors
	 */
	virtual int getWriteAddressVectorNumberMSB() = 0;

	/**
	 * @brief getWriteDataVectorNumberLSB specifies the vector number that contains the least significant bit DATA (LSB) bit.
	 *
	 * In case of padding !=1 this is the first vector number before additional padding vectors
	 */
	virtual int getWriteDataVectorNumberLSB() = 0;

	/**
	 * @brief getWriteDataVectorNumberMSB specifies the vector number that contains the most significant DATA bit (MSB).
	 *
	 * In case of padding !=1 this is the first vector number before additional padding vectors
	 */
	virtual int getWriteDataVectorNumberMSB() = 0;


	/*read parameters*/

	/**
	 * @brief getWriteAddressPinName specifies the pinname that drives the address.
	 */
	virtual string getReadAddressPinName() = 0;

	/**
	 * @brief getReadPinName specifies the output pinname that contains the data
	 */
	virtual string getReadPinName() = 0;

	/**
	 * @brief getReadAddressVectorNumberLSB specifies the vector number that contains the least significant ADDRESS bit (LSB).
	 *
	 * In case of padding !=1 this is the first vector number before additional padding vectors
	 */
	virtual int getReadAddressVectorNumberLSB() = 0;

	/**
	 * @brief getReadAddressVectorNumberMSB specifies the vector number that contains the most significant ADDRESS bit (MSB).
	 *
	 * In case of padding !=1 this is the first vector number before additional padding vectors
	 */
	virtual int getReadAddressVectorNumberMSB() = 0;

	virtual int getReadDataVectorNumberLSB() = 0;
	virtual int getReadDataVectorNumberMSB() = 0;

	/*expect parameters*/

	/**
	 * @brief getWriteAddressPinName specifies the pinname that drives the address.
	 */
	virtual string getExpectAddressPinName() = 0;
	/**
	 * @brief getReadPinName specifies the output pinname that contains the data
	 */
	virtual string getExpectPinName() = 0;

	/**
	 * @brief getReadAddressVectorNumberLSB specifies the vector number that contains the least significant ADDRESS bit (LSB).
	 *
	 * In case of padding !=1 this is the first vector number before additional padding vectors
	 */
	virtual int getExpectAddressVectorNumberLSB() = 0;

	/**
	 * @brief getReadAddressVectorNumberMSB specifies the vector number that contains the most significant ADDRESS bit (MSB).
	 *
	 * In case of padding !=1 this is the first vector number before additional padding vectors
	 */
	virtual int getExpectAddressVectorNumberMSB() = 0;

	virtual int getExpectDataVectorNumberLSB() = 0;
	virtual int getExpectDataVectorNumberMSB() = 0;
	virtual string getWriteTemplatePatternName() = 0;
	virtual string getReadTemplatePatternName() = 0;
	virtual string getWaitTemplatePatternName() = 0;
	virtual string getExpectTemplatePatternName() = 0;
	virtual int getWritePatternVectors() = 0;
	virtual int getReadPatternVectors() = 0;
	virtual int getExpectPatternVectors() = 0;
	virtual string getInterfaceName() = 0;
	virtual string getTimingPort() = 0;
	virtual string getTimingSetName()=0;
};


#endif /* d2s_H_ */
