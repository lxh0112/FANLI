/*
 * File:   d2sProtocolSSI.h
 * Author: zhongdanbiao
 *
 * Created on 2020年6月15日, 下午5:09
 */

#ifndef D2SPROTOCOLTEMPLATE_H
#define	D2SPROTOCOLTEMPLATE_H
#include "d2s.h"
class d2sProtocolSSI:public d2s{
         /*general parameters*/
public:
    d2sProtocolSSI():d2s(){}

    std::string DR2R_template;
    int ReadAddressVectorNumberLSB;
    int ReadAddressVectorNumberMSB;
    int ReadDataVectorNumberLSB;
    int ReadDataVectorNumberMSB;
    int ReadPatternVectors;

    int getAddressBits(){ return 10;}
    int getDataBits(){ return 16;}
    int getPadding() { return 1;}
    std::string getInterfaceName(){return "SSI";}
     ~d2sProtocolSSI(){}
    ////
    /*write parameters*/
    std::string getWriteTemplatePatternName(){return "Hi1151A_DR2W_template_test";}
    std::string getWritePinName() {return "DBB_GPIO7";}
    int getWriteAddressVectorNumberLSB(){return 22;}
    int getWriteAddressVectorNumberMSB(){return 13;}
    int getWriteDataVectorNumberLSB(){return 38;}
    int getWriteDataVectorNumberMSB(){return 23;}
    int getWritePatternVectors(){return 51;}
    void SSI_write(long regAddr,long regData,bool bitShiftflag=true){
        if(bitShiftflag){
            if(regAddr<0){
                regAddr=(65536+regAddr)/2;
            }
            else{
                regAddr=regAddr/2;
            }
        }
        write(regAddr,regData) ;
    }

    void SSI_writeDynamic(long regAddr,map<int, long long>regData,std::string id,bool bitShiftflag=true){
        if(bitShiftflag){
            if(regAddr<0){
                regAddr=(65536+regAddr)/2;
            }
            else{
                regAddr=regAddr/2;
            }
        }

        writeDynamic(regAddr, regData,id);
    }

    /*read parameters*/
    std::string getReadTemplatePatternName(){ return DR2R_template;}
    std::string getReadAddressPinName() { return "DBB_GPIO7";}
     std::string getReadPinName() { return "DBB_GPIO7";}
     int getReadAddressVectorNumberLSB(){return ReadAddressVectorNumberLSB;}
    int getReadAddressVectorNumberMSB(){return ReadAddressVectorNumberMSB;}
    int getReadDataVectorNumberLSB(){ return ReadDataVectorNumberLSB;}
    int getReadDataVectorNumberMSB(){ return ReadDataVectorNumberMSB;}
    int getReadPatternVectors(){return ReadPatternVectors;}

//    int getReadAddressVectorNumberLSB(){return 19;}
//    int getReadAddressVectorNumberMSB(){return 10;}
//    int getReadDataVectorNumberLSB(){ return 43;}
//    int getReadDataVectorNumberMSB(){ return 28;}
//    int getReadPatternVectors(){return 51;}

    void SSI_read(long regAddr,std::string id,int offset=7,bool bitShiftflag=true){
        if(bitShiftflag){
            if(regAddr<0){
                regAddr=(65536+regAddr)/2;
            }
            else{
                regAddr=regAddr/2;
            }
        }
        ReadAddressVectorNumberLSB=19;
        ReadAddressVectorNumberMSB=10;
        switch(offset){
            case 3:
                DR2R_template="Hi1151A_DR2R_template_test_offset3";
                ReadDataVectorNumberMSB=ReadAddressVectorNumberLSB+offset+2;
                ReadDataVectorNumberLSB=ReadDataVectorNumberMSB+15;
                ReadPatternVectors=ReadDataVectorNumberLSB+8;
            break;
            case 7:
                DR2R_template="Hi1151A_DR2R_template_test_offset7";
                ReadDataVectorNumberMSB=ReadAddressVectorNumberLSB+offset+2;
                ReadDataVectorNumberLSB=ReadDataVectorNumberMSB+15;
                ReadPatternVectors=ReadDataVectorNumberLSB+8;
            break;
            case 8:
                DR2R_template="Hi1151A_DR2R_template_test_offset8";
                ReadDataVectorNumberMSB=ReadAddressVectorNumberLSB+offset+2;
                ReadDataVectorNumberLSB=ReadDataVectorNumberMSB+15;
                ReadPatternVectors=ReadDataVectorNumberLSB+8;
            break;
            case 9:
                DR2R_template="Hi1151A_DR2R_template_test_offset9";
                ReadDataVectorNumberMSB=ReadAddressVectorNumberLSB+offset+2;
                ReadDataVectorNumberLSB=ReadDataVectorNumberMSB+15;
                ReadPatternVectors=ReadDataVectorNumberLSB+8;
            break;
            case 12:
                DR2R_template="Hi1151A_DR2R_template_test_offset12";
                ReadDataVectorNumberMSB=ReadAddressVectorNumberLSB+offset+2;
                ReadDataVectorNumberLSB=ReadDataVectorNumberMSB+15;
                ReadPatternVectors=ReadDataVectorNumberLSB+8;
            break;
            case 15:
                DR2R_template="Hi1151A_DR2R_template_test_offset15";
                ReadDataVectorNumberMSB=ReadAddressVectorNumberLSB+offset+2;
                ReadDataVectorNumberLSB=ReadDataVectorNumberMSB+15;
                ReadPatternVectors=ReadDataVectorNumberLSB+8;
            break;
            case 32:
                DR2R_template="Hi1151A_DR2R_template_test_offset32";
                ReadDataVectorNumberMSB=ReadAddressVectorNumberLSB+offset+2;
                ReadDataVectorNumberLSB=ReadDataVectorNumberMSB+15;
                ReadPatternVectors=ReadDataVectorNumberLSB+8;
            break;
        }
        read(regAddr,id) ;
    }

    /*wait parameters*/
    std::string getTimingPort(){ return "TS1_0";}
    //std::string getWaitTemplateTestName(){ return "wait_template";}
    std::string getWaitTemplatePatternName(){ return "HI1i51A_wait_template";}
    //std::string getTriggerTestName(){ return "trigger_template";}

	/*expect value parameters*/
    //int id;

	std::string getExpectTemplatePatternName(){return "EVTemplateP";}
	std::string getExpectAddressPinName() {return "JTAG_TDI";}
	std::string getExpectPinName() {return "JTAG_TDI";}
	int getExpectAddressVectorNumberLSB(){return 10;}
	int getExpectAddressVectorNumberMSB(){return 10;}
	int getExpectDataVectorNumberLSB(){return 30;}
	int getExpectDataVectorNumberMSB(){return 45;}
	int getExpectPatternVectors(){return 48;}
	string getTimingSetName() {return "timeplate_1_0";}


};

#endif	/* D2SPROTOCOLTEMPLATE_H */





