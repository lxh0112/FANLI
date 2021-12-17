#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
//#include "D2S_CAL_Module.h"
#include "Globle_Var.h"
#include "CCS08F.h"
#include "Excel.h"
#include "RegDef.h"
#include "d2sProtocolSSI.h"
#include "UserDef.h"
#include "Test_TX_cpp.h"

using namespace PhxAPI;

class WL_TX_FEM_PD_BUF: public TestClass {
public:

	void init() {

	}

	void execute() {

        TheInst.Digital().Timing().Apply();

		double Force_Val1[3] = { 0.6, 0.3, 0.9 };
		double Force_Val2[2] = { 0.3 };

		Calc_PD_BUF("C0", false, 3, Force_Val1);    // cal C0&C1
		Calc_PD_BUF("C1", true, 1, Force_Val2);

	}
};
REGISTER_TESTCLASS("WL_TX_FEM_PD_BUF", WL_TX_FEM_PD_BUF)

