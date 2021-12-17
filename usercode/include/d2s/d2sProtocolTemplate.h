/*
 * d2sProtocolTemplate.h
 *
 *  Created on: 2021��6��2��
 *      Author: dongyuqing
 */

#ifndef d2sPROTOCOLTEMPLATE_H_
#define d2sPROTOCOLTEMPLATE_H_

#include <d2s.h>

class d2sSPI:public d2s{
         /*general parameters*/
public:
	d2sSPI():d2s(){}

    int getAddressBits(){ return 30;}
    int getDataBits(){ return 32;}
    int getPadding() { return 1;}
    string getInterfaceName(){return "SPI_RW";}
     ~d2sSPI(){}
    ////
    /*write parameters*/
    int id;
    string getWriteTemplatePatternName(){return "SPI_write";}
    string getWritePinName() {return "ROC_SPIA_SDI";}
    int getWriteAddressVectorNumberLSB(){return 32;}
    int getWriteAddressVectorNumberMSB(){return 3;}
    int getWriteDataVectorNumberLSB(){return 73;}
    int getWriteDataVectorNumberMSB(){return 42;}
    int getWritePatternVectors(){return 62;}

    /*read parameters*/
      string getReadTemplatePatternName(){ return "SPI_read";}
	  string getReadAddressPinName() { return "ROC_SPIA_SDI";}
	  string getReadPinName() { return "ROC_SPIA_SDIO";}
	  int getReadAddressVectorNumberLSB(){return 32;}
	  int getReadAddressVectorNumberMSB(){return 3;}
	  int getReadDataVectorNumberLSB(){ return 73;}
	  int getReadDataVectorNumberMSB(){ return 42;}
	  int getReadPatternVectors(){return 32;}

	  /*wait parameters*/
	  std::string getTimingPort(){ return "TS1";}
	  std::string getWaitTemplatePatternName(){ return "SPI_wait";}

	  /*expect value parameters*/
	  std::string getExpectTemplatePatternName(){return "EVTemplateP";}
	  std::string getExpectAddressPinName() {return "JTAG_TDI";}
	  std::string getExpectPinName() {return "JTAG_TDI";}
	  int getExpectAddressVectorNumberLSB(){
		int LSB = 0;
		switch(id) {
		case 0:
			LSB = 10;
			break;
		case 1:
			LSB = 25;
			break;
		default:
			LSB = 10;
			break;
		}
		return LSB;
	  }
	  int getExpectAddressVectorNumberMSB(){
		int MSB = 0;
		switch(id) {
		case 0:
			MSB = 25;
			break;
		case 1:
			MSB = 10;
			break;
		default:
			MSB = 25;
			break;
		}
		return MSB;
	  }
	  int getExpectDataVectorNumberLSB(){return 30;}
	  int getExpectDataVectorNumberMSB(){return 45;}
	  int getExpectPatternVectors(){return 48;}
	  string getTimingSetName() {return "timeplate_1_0";}
  };



#endif /* d2sPROTOCOLTEMPLATE_H_ */
