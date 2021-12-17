//
// Created by Administrator on 2021/4/10.
//

#ifndef TESTP_SHARE2_TESTFAC_H
#define TESTP_SHARE2_TESTFAC_H

class TestClass;

class TestClassFactory
{
public:
    explicit TestClassFactory(const char* type);

    virtual ~TestClassFactory();

    virtual TestClass* createUserTestClass() const = 0;

    virtual const char* getFileLocation() const  = 0;

    const char* getTestClassName();
protected:

private:

    TestClassFactory(const TestClassFactory&);
    TestClassFactory& operator = (const TestClassFactory&);

    const char* type;

};

#endif
