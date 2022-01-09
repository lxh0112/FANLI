/*
 * BOOT_UP.cpp
 *
 *  Created on: 2021年8月18日
 *      Author: 荣耀
 */




#include "TestClass.h"
#include <iostream>
#include <string>
#include "UserAPI.h"
#include "d2sProtocolSSI.h"
#include <math.h>
#include "Globle_Var.h"
#include "UserDef.h"
#include "D2S_PMU_Module.h"

using namespace std;
using namespace PinTool;

class BOOT_UP: public TestClass{
public:

	void init(){
	            }

    void execute(){
					TheInst.DCVI().Power().Apply();
					TheInst.Digital().Level().Apply();
					TheInst.Digital().Timing().Apply();

					BOOT_UP_PAmodule();

				}

};

REGISTER_TESTCLASS("BOOT_UP",BOOT_UP)


