#include <string>
#include <vector>
#include <map>
using namespace std;

#ifndef DLLAPI
#define DLLAPI __declspec(dllexport)
#endif
#define MAX_SITES 256 //< maximum available sites number
enum d2sOperationMode {
	Write = 0,
	Read = 1,
	Expect = 2
};

typedef struct {
	string template_head;
	string template_signals;
	vector<string> template_vectors;
	string template_vector;
	string template_tail;
}TemplateFile_T;

typedef struct {
	bool positive_addr;
	bool positive_data;
	int addr_vectors;
	int data_vectors;
	int start_addr;
	int start_data;
}VectorsAttribute_T, *pVectorsAttribute_T;

/*enum d2sWorkModeType {
    LearningMode = 0,
    ProductionMode = 1
};*/

typedef struct {
	int AddrBits;
	int DataBits;
	int Padding;

	string InterfaceName;
}VectorsParam_T, *pVectorsParam_T;

typedef struct {
	int WriteAddrVectorLSB;
	int WriteAddrVectorMSB;
	int WriteDataVectorLSB;
	int WriteDataVectorMSB;
	int WritePatternVectors;

	string WritePinName;
	string WriteTemplateTestName;
}WriteParam_T, *pWriteParam_T;

typedef struct {
	int ReadAddrVectorLSB;
	int ReadAddrVectorMSB;
	int ReadDataVectorLSB;
	int ReadDataVectorMSB;
	int ReadPatternVectors;

	string ReadPinName;
	string ReadTemplateTestName;
}ReadParam_T, *pReadParam_T;

typedef struct {
	string TimingPort;
	string WaitTemplateTestName;
}WaitParam_T, *pWaitParam_T;

typedef struct {
	char High;
	char Low;
	char HighStrobe;
	char LowStrobe;
}WaveformChar_T, *pWaveformChar_T;

class d2sWriteDynamic {
public:
	d2sWriteDynamic() {
		pin_name = "";
		addr_start = 0;
		addr_vectors = 0;
		data_start = 0;
		data_vectors = 0;
	}

	d2sWriteDynamic(string write_pin, unsigned long reg_addr_start, unsigned long addr_vectors_len, vector<unsigned long> reg_addr_array,\
			unsigned long reg_data_start, unsigned long data_vectors_len, map<int ,vector<unsigned long> > reg_data_array) {
		pin_name = write_pin;
		addr_start = reg_addr_start;
		addr_vectors = addr_vectors_len;
		addr_array.insert(addr_array.end(), reg_addr_array.begin(), reg_addr_array.end());
//		addr_array = reg_addr_array;
		data_start = reg_data_start;
		data_vectors = data_vectors_len;
		data_array.insert(reg_data_array.begin(), reg_data_array.end());
//		data_array.swap(reg_data_array);
	}

public:
	string pin_name;
	unsigned long addr_start;
	unsigned long addr_vectors;
	vector<unsigned long> addr_array;
	unsigned long data_start;
	unsigned long data_vectors;
	map<int ,vector<unsigned long> > data_array;
};
