//
// Created by Administrator on 2021/4/11.
//

#include "TestClass.h"
#include "UserAPI.h"

class mytestClass3: public TestClass{
public:
    std::string pinlist;
    std::string param1;
    double param2;
    int param3;
	
	void init();
	void execute();
	



};

void mytestClass3::init(){
	add_param( "pinlist",  "PinString", &pinlist)
			.set_comment("test pin list")
			.set_default("pin1")
			.set_options("pin1:pin2");
	add_param("t3param1","string",&param1);
	add_param("t3param2","double",&param2);
	add_param("t3param3","int",&param3);
}

void mytestClass3::execute(){

}


REGISTER_TESTCLASS("mytest3_name",mytestClass3)

