#ifndef TESTP_SHARE2_FACTORY_MARCO_H
#define TESTP_SHARE2_FACTORY_MARCO_H
#include "TestClass.h"
#include "TestClassFactory.h"

#include <iostream>

#define REGISTER_TESTCLASS(TestClass_type, TestClass_class) \
class __declspec(dllexport) TEST_CLASS_FACTORY_UNIQUE_NAME : \
  public TestClassFactory { \
public: \
  explicit TEST_CLASS_FACTORY_UNIQUE_NAME( \
    const char* type, \
    const char* location) \
    :TestClassFactory(type), \
     mTmLocation(location) \
  { \
  } \
  virtual ~TEST_CLASS_FACTORY_UNIQUE_NAME() \
  { \
  } \
  virtual TestClass* createUserTestClass() const \
  { \
    TestClass_class *pProto = NULL; \
    try \
    { \
      pProto = new TestClass_class(); \
    } \
    catch(std::exception &e) \
    { \
      std::cerr<<"Error happening in creating TestClass \""<<"\" :"<< e.what()<<std::endl; \
    } \
    catch(...) \
    { } \
    return pProto; \
  }; \
  virtual const char* getFileLocation() const  \
  { \
    return mTmLocation; \
  } \
private: \
  const char* mTmLocation; \
};                                                          \
TEST_CLASS_FACTORY_UNIQUE_NAME \
	__declspec(dllexport) \
   TEST_CLASS_FACTORY_INS_UNIQUE_NAME (TestClass_type, __FILE__":"#TestClass_class);\

#define TEST_CLASS_FACTORY_UNIQUE_NAME CAT_STR(__TestClassFactory__,__LINE__)
#define TEST_CLASS_FACTORY_INS_UNIQUE_NAME CAT_STR(__TestClassFactoryInstance__,__LINE__)
#define CAT_STR(ARG1,ARG2) CAT_STR2(ARG1,ARG2)
#define CAT_STR2(ARG1,ARG2) ARG1##ARG2


#endif
