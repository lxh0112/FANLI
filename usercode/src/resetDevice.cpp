
#include "UserAPI.h"
#include "D2S_ABB_Module.h"
#include "TestClass.h"

class resetDevice: public TestClass{
public:
	void init(){

		}
	    void execute(){
						TheInst.DCVS().Power().Apply();
						TheInst.Digital().Level().Apply();
						PHY_ABB_RF_Reset_Module();

      }
};
REGISTER_TESTCLASS("resetDevice", resetDevice)
