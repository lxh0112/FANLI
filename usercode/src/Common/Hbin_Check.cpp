/*
 * Hbin_Check.cpp
 *
 *  Created on: 2021年8月24日
 *      Author: 荣耀
 */


#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>

using namespace PhxAPI;

class Hbin_Check: public TestClass{
public:
	bool HBIN_FLAG[4];

    void init(){

    }

    void execute(){
        TheInst.DCVS().Power().Apply();
        TheInst.Digital().Level().Apply();
        TheInst.Digital().Timing().Apply();
    	TheInst.Digital().Pattern().Start();

    	FOREACH_ACTIVESITE_BEGIN(site_id, bInterrupt)
    		if((HBIN_FLAG[site_id] == 0)&&( TheSoft.Flow().Bin().GetResultSoftBin(site_id)!= 1)){
    			HBIN_FLAG[site_id] = 1;
    	    }
    	FOREACH_ACTIVESITE_END
    }

};

REGISTER_TESTCLASS("Hbin_Check",Hbin_Check)

