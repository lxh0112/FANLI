/*
 * d2sProtocolTemplate.h
 *
 *  Created on: 2021��6��2��
 *      Author: dongyuqing
 */

#ifndef d2sPROTOCOLTEMPLATE_H_
#define d2sPROTOCOLTEMPLATE_H_

#include <d2s.h>
#include <iostream>
#include <AFE_COM_Types.h>



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
		int LSB_d2s = 0;

		switch(id) {
		case 0:
			LSB_d2s = 10;
			break;
		case 1:
			LSB_d2s = 25;
			break;
		default:
			LSB_d2s = 10;
			break;
		}
		return LSB_d2s;
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

public:
// RF add
	    void write(long long address, long long data, enum SPI_Modes SPI_Mode, long long md5data = 0XFFFFFFFF)
	    {
	        if(SPI_Mode!=0) {
	            Pri_SelectAddr(&address, SPI_Mode);
	        }
	        d2s::write(address, data,md5data);
	    }
	    void write(long long address, long long data,long long md5data = 0XFFFFFFFF)
	    {

	        d2s::write(address, data, md5data);
	    }
	    void writeDynamicRf(long long address, long long *data, std::string id, enum SPI_Modes SPI_Mode)
//	    void writeDynamicRf(long long address, long long *data, int id, enum SPI_Modes SPI_Mode)
	    {
	        if(SPI_Mode!=0) {
	            Pri_SelectAddr(&address, SPI_Mode);
	        }

	        d2s::writeDynamic(address, data, id);

	    }

	    void read(long long address, std::string id, enum SPI_Modes SPI_Mode)
	    {
	        if (SPI_Mode != 0) {
	            Pri_SelectAddr(&address, SPI_Mode);
	        }
	        d2s::read(address, id);
	    }
	    void read(long long address, std::string id)
	    {
	        d2s::read(address, id);
	    }

	    void Pri_SelectAddr(long long *in_Address_lng, enum SPI_Modes SPI_Mode = GlobalMode){
	        switch(SPI_Mode)
	        {
	            case GlobalMode:
	                *in_Address_lng = *in_Address_lng + 0;    break;
	            case A_TX_Dig:
	                *in_Address_lng = *in_Address_lng + 0x14700000;    break;
	            case A_TX_ANA:
	                *in_Address_lng = *in_Address_lng + 0x1470A000;    break;       //  '0xB4700000
	            case A_FB:
	                *in_Address_lng = *in_Address_lng + 0x14300000;
	                break;
	    //        '        case A_FB_Indirect
	    //        '            *in_Address_lng = *in_Address_lng + 0x14300000    '!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	            case A_PLL_Ana:
	                *in_Address_lng = *in_Address_lng + 0x14400000;    break;
	            case B_RX_Dig:
	                *in_Address_lng = *in_Address_lng + 0x14200000;    break;
	            case B_RX_Ana:
	                *in_Address_lng = *in_Address_lng + 0x14200DC5;    break;
	            case B_LOPLL:
	                *in_Address_lng = *in_Address_lng + 0x14500000;    break;
	            case B_SAPLL:
	                *in_Address_lng = *in_Address_lng + 0x14400000;    break;
	            // 'add by haohui
	            case B_CRG:
	                *in_Address_lng = *in_Address_lng + 0x14800000;    break;
	            case A_spi:
	                *in_Address_lng = *in_Address_lng + 0x14100000;    break;
	            default:
	                cerr << "ZLLQX Error 00001: Wrong SPI Mode !" << endl;
	    //        If TheExec.RunMode = runModeProduction Then
	    //            TheExec.AddOutput "ZLLQX Error 00001: Wrong SPI Mode !"
	    //            '                GoTo errHandler
	    //        Else
	    //            'Error message here
	    //            MsgBox "ZLLQX Error 00001: Wrong SPI Mode !"
	    //            Stop
	    //        End If


	        }

	    }

  };


#endif /* d2sPROTOCOLTEMPLATE_H_ */
