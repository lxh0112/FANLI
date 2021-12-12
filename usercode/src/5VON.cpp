

#include "TestClass.h"
#include <UserAPI.h>
#include <iostream>
#include <string>
#include <synchapi.h>
//#include "Lib.h"

class ON: public TestClass{
public:


    void init(){

    }

    void execute(){
    	 TheInst.Util().SetUserPower(PhxAPI::E_USERPW_P5V, PhxAPI::E_UTIL_STATE_ON);
    	        TheInst.Wait(5*s);



    }

};



REGISTER_TESTCLASS("ON",ON)

