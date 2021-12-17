//
// Created by Administrator on 2021/4/11.
//

#include "TestClass.h"
#include "UserAPI.h"
#include <iostream>

class mytestClass1: public TestClass{
public:
    std::string pinlist;
    std::string param1;
    double param2;
    int param3;
	
    void init();
	void execute();


};

void mytestClass1::init(){
	add_param( "pinlist",  "PinString", &pinlist)
			.set_comment("test pin list")
			.set_default("pin1")
			.set_options("pin1:pin2");
	add_param("t1param1","string",&param1);
	add_param("t1param2","double",&param2);
	add_param("t1param3","int",&param3);
}

void mytestClass1::execute(){
	cout << "!!!Hello World!!!" << endl;


}

REGISTER_TESTCLASS("mytest1_name", mytestClass1)

