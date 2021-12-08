//
// Created by Administrator on 2021/4/30.
//

#ifndef TESTCLASS_TML_TESTCLASSPARAM_H
#define TESTCLASS_TML_TESTCLASSPARAM_H
#include <string>

class TestClassParam {
public:
    TestClassParam(void* ref);
    virtual ~TestClassParam();

    const std::string get_type() const;
    const std::string get_default() const;
    const std::string get_options() const;
    const std::string get_name() const;

    TestClassParam& set_comment(std::string cmt);
    TestClassParam& set_default(std::string default_val);
    TestClassParam& set_options(std::string options);
private:
    void* param_ref;
};


#endif //TESTCLASS_TML_TESTCLASSPARAM_H
