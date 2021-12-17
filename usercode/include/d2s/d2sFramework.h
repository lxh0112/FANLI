#ifndef D2SFRAMEWORK_H_
#define D2SFRAMEWORK_H_

#include <string>
#include <set>
#include "TransactionPort.h"
#include "d2sModes.h"
#include "d2s_status.h"

class d2sFramework
{
public:

	d2sFramework();
	virtual ~d2sFramework();

	void d2s_LABEL_BEGIN(const std::string& identifier);
    void d2s_LABEL_BEGIN(const std::string& identifier, d2sFrameWorkModeType::Enum mode, d2sExecutionModeType::Enum execMode=d2sExecutionModeType::FUNCTIONAL_TST);
    void d2s_LABEL_END(bool appendsuitename=true);
    virtual void setPrimaries();
    d2sFrameWorkModeType::Enum getCurrentMode();
    d2sExecutionModeType::Enum getCurrentExecutionMode();
    std::string getCurrentBurstName();  
    bool registerTransactionPort(TransactionPort &port);
    void synchronizePorts();
    void synchronizePorts(TransactionPort &port1, TransactionPort &port2);
    void synchronizePorts(TransactionPort &port1, TransactionPort &port2, TransactionPort &port3);
    void synchronizePorts(TransactionPort &port1, TransactionPort &port2, TransactionPort &port3, TransactionPort &port4);
    void synchronizePorts(TransactionPort &port1, TransactionPort &port2, TransactionPort &port3, TransactionPort &port4, TransactionPort &port5);
    void synchronizePorts(TransactionPort &port1, TransactionPort &port2, TransactionPort &port3, TransactionPort &port4, TransactionPort &port5, TransactionPort &port6);
    void synchronizePorts(TransactionPort &port1, TransactionPort &port2, TransactionPort &port3, TransactionPort &port4, TransactionPort &port5, TransactionPort &port6, TransactionPort &port7);
    void synchronizePorts(TransactionPort &port1, TransactionPort &port2, TransactionPort &port3, TransactionPort &port4, TransactionPort &port5, TransactionPort &port6, TransactionPort &port7, TransactionPort &port8);
    
    d2sFrameWorkModeType::Enum default_mode;
    static string get_current_prefix();
protected:
    virtual bool setPrimariesAndExecuteStartLabel(const std::string& startLabel);

    typedef std::set<TransactionPort*> TransactionPortSet;
    typedef TransactionPortSet::iterator TransactionPortSetIter;
    typedef std::set<std::string> StringSet;
    TransactionPortSet registeredTransactionPorts;
    StringSet registeredPorts;
    d2sExecutionModeType::Enum currentExecutionMode;
    d2sFrameWorkModeType::Enum currentFrameworkMode;
    
private:
    void changeFrameworkMode(d2sFrameWorkModeType::Enum newMode);
    void synchronizePorts(TransactionPortSet selectedPortsToSync);
    static bool hwprbs_enable;
    std::string currentIdentifier;  
    static map<string,string> lable_md5;
    static string current_prefix;
};

#endif /*D2SFRAMEWORK_H_*/
