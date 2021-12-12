/*
 * Basic_07_TSensor_Read.cpp
 *
 *  Created on: 2021å¹´7æœˆ28æ—¥    --based on 1.0.2.8
 */

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include <math.h>
#include <synchapi.h>

using namespace PinTool;

#define I2C_DELAY 		4

class Ubit_control: public TestClass{
public:


    void init(){


    }

    void execute(){
                string Ubit_control;
		    	cout << "!!!Hello Ubit_control!!!" << endl;
//		    	TheSoft.Message().LogInfo(Ubit_control, 256, "%d,number")
		    	TheSoft.Message().LogInfo(Ubit_control, 256, "%d,number");
		  


			TheInst.Util().SetUserPower(PhxAPI::E_USERPW_P5V, 0);
	    	int i = -1;
	    	for(uint32_t j=0;j<256;j++)
	    	{
	    		TheInst.Util().SetRelayState(j, 0); //bihe-0,duankai-1
	    		Sleep(I2C_DELAY);
	    		i = TheInst.Util().GetRelayState(j);
	    		if (i==0)
	    		{
	    			printf("\n***********OPEN Relay-  %d error**************\n",j);
	    		}
	    		Sleep(I2C_DELAY);
	    	}

    }

};

REGISTER_TESTCLASS("Ubit_control",Ubit_control)

