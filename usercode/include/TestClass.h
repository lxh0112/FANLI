#ifndef TESTCLASS_H
#define TESTCLASS_H
#include <string>
#include <map>
#include <typeinfo>
#include "TestClassParam.h"
#include <vector>
#include "TestClassFactoryMacro.h"
#include <typeinfo>

class TestClass
{
public:
    virtual ~TestClass();
    virtual void init() = 0;

protected:
    TestClass();

    virtual void execute() = 0;



    virtual void param_change(const std::string param_name) {

    };

    template<typename T>
    TestClassParam add_param(std::string param_name,
                             std::string param_type,
                             T* pValue){
        return add_param(param_name,param_type,typeid(T),static_cast<void*>( pValue));
    }

public:
    TestClassParam get_param(const std::string param_name);

    const TestClassParam get_param(const std::string param_name) const;

    void get_all_param_name(std::vector<std::string>& all_param);
protected:
    virtual const std::string getComment() const
    {  return ""; };

private:
    void* pref;
    //disable
    TestClass(const TestClass&);
    TestClass& operator=(const TestClass&);

    TestClassParam add_param(std::string param_name,
                             std::string param_type,
                             const std::type_info& val_type,
                             void* pValue);
};

#endif
