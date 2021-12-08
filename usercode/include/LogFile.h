#pragma once

#ifndef LOGFILE_H    
#define LOGFILE_H    
  
#define LOG_FILE_NAME ("log.txt")  
#define LOG_ENABLE  

#include "string.h"
#include "time.h"
#include <windows.h>
#include <fstream>    
#include <string>      
using namespace std;

class CLogFile {
public:
    static void GetLogFilePath(TCHAR* szPath) 
    {
        GetModuleFileName(NULL, szPath, MAX_PATH);
        ZeroMemory(strrchr(szPath, TEXT('\\')), strlen(strrchr(szPath, TEXT('\\'))) * sizeof (TCHAR));
        strcat(szPath, TEXT("\\"));
        strcat(szPath, LOG_FILE_NAME);
    }

    template <class T>
    static void WriteLog(T x) 
    {
        TCHAR szPath[MAX_PATH] = {0};
        GetLogFilePath(szPath);
        ofstream fout(szPath, ios::app);
        //ofstream fout(szPath);
        fout.seekp(ios::end);
        fout << x << endl;
        fout.close();
    }

    static void WriteString(string szText) 
    {
        WriteLog(szText);
    }

    template<class T1, class T2>
    static void WriteLog2(T1 x1, T2 x2) 
    {
        CHAR szPath[MAX_PATH] = {0};
        GetLogFilePath(szPath);
        ofstream fout(szPath, ios::app);
        fout.seekp(ios::end);
        fout << x1 << " = " << x2 << endl;
        fout.close();
    }

    template <class T>
    static void WriteFuncBegin(T x) 
    {
        TCHAR szPath[MAX_PATH] = {0};
        GetLogFilePath(szPath);
        ofstream fout(szPath, ios::app);
        fout.seekp(ios::end);
        fout << "--------------------" << x << "  Begin--------------------" << endl;
        fout.close();
    }

    template <class T>
    static void WriteFuncEnd(T x) 
    {
        TCHAR szPath[MAX_PATH] = {0};
        GetLogFilePath(szPath);
        ofstream fout(szPath, ios::app);
        fout.seekp(ios::end);
        fout << "--------------------" << x << "  End  --------------------" << endl;
        fout << endl;
        fout.close();
    }
};

#ifdef LOG_ENABLE  


#define LOG(x)		CLogFile::WriteLog(x);		
#define LOG2(x1,x2)     CLogFile::WriteLog2(x1,x2);  
#define LOG_STRING(x)	CLogFile::WriteString(x);
#define LOG_FUNC        LOG(__FUNCTION__)							
#define LOG_LINE        LOG(__LINE__)								
#define LOG_FUNC_BEGIN  CLogFile::WriteFuncBegin(__FUNCTION__);     
#define LOG_FUNC_END	CLogFile::WriteFuncEnd(__FUNCTION__);		

#else  

#define LOG(x)  
#define LOG_STRING(x)
#define LOG2(x1,x2)       
#define LOG_FUNC          
#define LOG_LINE          
#define LOG_FUNC_BEGIN    
#define LOG_FUNC_END      

#endif  

#endif    