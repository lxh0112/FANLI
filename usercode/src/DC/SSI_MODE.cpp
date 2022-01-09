/*
 * SSI_MODE.cpp
 *
 *  Created on: 2021年8月18日
 *      Author: 荣耀
 */


#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include <synchapi.h>

class SSI_MODE: public TestClass{
public:

	void init(){

	}
    void execute(){
			TheInst.DCVI().Power().Apply();
			TheInst.Digital().Level().Apply();
			TheInst.Digital().Timing().Apply();
			TheInst.Digital().PatEng().SetFailMode(PhxAPI::E_SET_HIL_MODE);
			TheInst.Digital().Pattern().Run();
    }

};
REGISTER_TESTCLASS("SSI_MODE",SSI_MODE)


