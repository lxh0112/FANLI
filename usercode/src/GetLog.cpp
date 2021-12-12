#include "GetLog.h"
#include "UserAPI.h" 
#include <iostream>
#include "string.h"
#include "CCWaveformsData.h"
#include "Globle_Var.h"
using namespace std;

TMResult ValueTest (const int &site_id,const char *Pin, const double &Value,const double &LowLimit, const double &HighLimit, const char *Units, const char *Comment, const char *FailBin, const unsigned int &MinorId, const bool &CLOGEnable)
{
      char szLowLimit[32] = {0};
      char szHighLimit[32] = {0};
      char szLowUnits[32] = {0};
      char szHighUnits[32] = {0};
      TMResult testResult = TM_NOTEST;
      int STDF_LOG_FLAG = 0;//stdf_log flag 
      if (LowLimit == -999999 & HighLimit == 999999)
      {
          testResult = TM_PASS;
          STDF_LOG_FLAG = 4;//stdf_log flag 
      }
      else if (LowLimit == -999999)
      {
        STDF_LOG_FLAG = 3;//stdf_log flag 
        testResult = (Value <= HighLimit ) ? TM_PASS : TM_FAIL;
        sprintf(szHighLimit,"%f",HighLimit);
        sprintf(szHighUnits,"%s",Units);
      }
      else if (HighLimit == 999999)
      {
        STDF_LOG_FLAG = 2;//stdf_log flag 
        testResult = (Value >= LowLimit) ? TM_PASS : TM_FAIL;
        sprintf(szLowLimit,"%f",LowLimit);
        sprintf(szLowUnits,"%s",Units);
      }    
      else    
      {
        STDF_LOG_FLAG = 1;//stdf_log flag 
        testResult = (Value >= LowLimit && Value <= HighLimit ) ? TM_PASS : TM_FAIL;
        sprintf(szHighLimit,"%f",HighLimit);
        sprintf(szLowLimit,"%f",LowLimit);
        sprintf(szLowUnits,"%s",Units);
        sprintf(szHighUnits,"%s",Units);
      }
      
      string flagResult = "*PASS*";
      string flagResult_file = "PASS";
      if( testResult == TM_FAIL )
      {
          flagResult = "*FAIL*";
          flagResult_file = "FAIL";
      }
      //int site_id = api->Get_active_site();
      if( strlen(FailBin)!=0 && testResult == TM_FAIL )
      {
           
//           if (api->set_result_bin_name(FailBin) == -1 )
//           {
//               api->error_message("set result bin %s failed", FailBin);
//
//           }
           

			if(Testsoftbin[site_id] == 1){
				Testsoftbin[site_id] = TheSoft.Flow().Bin().GetResultSoftBin(site_id);
			}

//           if(Testsoftbin[site_id] == 1){
//                Testsoftbin[site_id] = api->Get_result_bin();
//           }
           if(HBIN_FLAG[site_id] == 0)
           {
                HBIN_FLAG[site_id] = 1;   
           }      
       }

      unsigned int MajorId;
       bool Change_Flag;
       string name = TheSoft.Flow().GetCurrentFlowName();
      //string name = api->Get_current_test_name();
      if(name!=Last_TestName)
      {
          Change_Flag = true;
      }
      else
      {
          Change_Flag = false;
      }
      Last_TestName=name;


#if 0

      api->Get_test_values(name.c_str(),THE_TESTNUMBER, &MajorId, THE_END);
      if ( MinorId!=0 ) {                     
           api->Set_test_values(name.c_str(),THE_TESTNUMBER, MajorId + MinorId, THE_END);
      }

#endif
      if(Change_Flag){

    	  printf("%11s  %4s    %4s %30s %19s   %17s %19s %19s","Test_Number","P/F","Site","Test_Name","Pin","L_Limit","Measure","H_Limit");
      }
      int LengthUnit = strlen(Units);
      if( LengthUnit == 0 )
    	  printf("%11d  %4s    %4d %30s %19s   %17s%s %19f%s %19s%s",MinorId,flagResult.c_str(),site_id,Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);
      else if( LengthUnit == 1 )
    	  printf("%11d  %4s    %4d %30s %19s   %15s %s %17f %s %17s %s",MinorId,flagResult.c_str(),site_id,Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);
      else if( LengthUnit == 2 )
    	  printf("%11d  %4s    %4d %30s %19s   %14s %s %16f %s %16s %s",MinorId,flagResult.c_str(),site_id,Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);
      else if( LengthUnit == 3 )
    	  printf("%11d  %4s    %4d %30s %19s   %13s %s %15f %s %15s %s",MinorId,flagResult.c_str(),site_id,Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);
      else
    	  printf("%11d  %4s    %4d %30s %19s   %12s %s %14f %s %14s %s",MinorId,flagResult.c_str(),site_id,Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);

#if 0
      if(CLOGEnable)
      {
          if(Change_Flag){
                api->Datalog_ascii_print("%11s  %4s    %4s %30s %19s   %17s %19s %19s","Test_Number","P/F","Site","Test_Name","Pin","L_Limit","Measure","H_Limit");
          }
          if( LengthUnit == 0 )
              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %17s%s %19f%s %19s%s",MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);
          else if( LengthUnit == 1 )
              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %15s %s %17f %s %17s %s",MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);
          else if( LengthUnit == 2 )
              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %14s %s %16f %s %16s %s",MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);
          else if( LengthUnit == 3 )
              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %13s %s %15f %s %15s %s",MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);
          else
              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %12s %s %14f %s %14s %s",MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);
          //print stdf log
          if(STDF_LOG_FLAG == 1){
            api->Datalog_STDF_parametric_test(Comment, STDF_LOW_LIMIT, LowLimit, STDF_HIGH_LIMIT, HighLimit, STDF_UNITS, Units, STDF_RESULT, Value, STDF_END);  
          }
          else if(STDF_LOG_FLAG == 2){
            api->Datalog_STDF_parametric_test(Comment, STDF_LOW_LIMIT, LowLimit, STDF_UNITS, Units, STDF_RESULT, Value, STDF_END);  
          }
          else if(STDF_LOG_FLAG == 3){
            api->Datalog_STDF_parametric_test(Comment, STDF_HIGH_LIMIT, HighLimit, STDF_UNITS, Units, STDF_RESULT, Value, STDF_END);  
          }
          else if(STDF_LOG_FLAG == 4){
            api->Datalog_STDF_parametric_test(Comment, STDF_UNITS, Units, STDF_RESULT, Value,STDF_SET_RESULT_BIN, 0, STDF_END);  
          }
          //api->Datalog_STDF_parametric_test(Comment, STDF_LOW_LIMIT, LowLimit, STDF_HIGH_LIMIT, HighLimit, STDF_UNITS, Units, STDF_RESULT, Value, STDF_END);   
      }
             
       api->Set_test_values(name.c_str(),THE_TESTNUMBER, MajorId, THE_END);
       
#endif
      return testResult;
}


TMResult ValueTest (const int &site_id, const char *Pin, const int &Value, const int &LowLimit, const int &HighLimit, const char *Units, const char *Comment, const char *FailBin, const unsigned int &MinorId, const bool &CLOGEnable)
{
      char szLowLimit[10] = {0};
      char szHighLimit[10] = {0};
      TMResult testResult = TM_NOTEST;
      int STDF_LOG_FLAG = 0;//stdf_log flag 
      int Value1 =  Value; //The Value (double) to (int)
      
      if (LowLimit == -999999 & HighLimit == 999999)
      {
          STDF_LOG_FLAG = 4;//stdf_log flag 
          testResult = TM_PASS;
      }
      else if (LowLimit == -999999)
      {
          STDF_LOG_FLAG = 3;//stdf_log flag 
          testResult = (Value <= HighLimit ) ? TM_PASS : TM_FAIL;
          sprintf(szHighLimit,"%d",HighLimit);
      }
      else if (HighLimit == 999999)
      {
          STDF_LOG_FLAG = 2;//stdf_log flag 
          testResult = (Value >= LowLimit) ? TM_PASS : TM_FAIL;
          sprintf(szLowLimit,"%d",LowLimit);
      }    
      else    
      {
          STDF_LOG_FLAG = 1;//stdf_log flag 
          testResult = (Value >= LowLimit && Value <= HighLimit ) ? TM_PASS : TM_FAIL;
          sprintf(szHighLimit,"%d",HighLimit);
          sprintf(szLowLimit,"%d",LowLimit);
      }
//      
      string flagResult = "*PASS*";
      string flagResult_file = "PASS";
      if( testResult == TM_FAIL )
      {
          flagResult = "*FAIL*";
          flagResult_file = "FAIL";
      }
      //int site_id = api->Get_active_site();
      if( strlen(FailBin)!=0 && testResult == TM_FAIL )
      {        

#if 0
    	  if (api->set_result_bin_name(FailBin) == -1 )
           {
               api->error_message("set result bin %s failed", FailBin);
           }
#endif
           if(Testsoftbin[site_id] == 1){
                //Testsoftbin[site_id] = api->Get_result_bin();
        	   Testsoftbin[site_id] = TheSoft.Flow().Bin().GetResultSoftBin(site_id);
           }
           if(HBIN_FLAG[site_id] == 0)
           {
                HBIN_FLAG[site_id] = 1;   
           } 
       }

      unsigned int MajorId;
      bool Change_Flag;

      string name = TheSoft.Flow().GetCurrentFlowName();
      //string name = api->Get_current_test_name();
      if(name!=Last_TestName)
      {
          Change_Flag = true;
      }
      else
      {
          Change_Flag = false;
      }
      Last_TestName=name;

#if 0
      api->Get_test_values(name.c_str(),THE_TESTNUMBER, &MajorId, THE_END);
      if ( MinorId!=0 ) {                     
           api->Set_test_values(name.c_str(),THE_TESTNUMBER, MajorId + MinorId, THE_END);
      }
#endif
      if(Change_Flag){
           printf("%11s  %4s    %4s %30s %19s   %17s %19s %19s","Test_Number","P/F","Site","Test_Name","Pin","L_Limit","Measure","H_Limit");
      }
      int LengthUnit = strlen(Units);
      if( LengthUnit == 0 )
    	  printf("%11d  %4s    %4d %30s %19s   %17s%s %19d%s %19s%s",MinorId,flagResult.c_str(),site_id,Comment,Pin,szLowLimit,Units,Value,Units,szHighLimit,Units);
      else if( LengthUnit == 1 )
    	  printf("%11d  %4s    %4d %30s %19s   %15s %s %17d %s %17s %s",MinorId,flagResult.c_str(),site_id,Comment,Pin,szLowLimit,Units,Value,Units,szHighLimit,Units);
      else if( LengthUnit == 2 )
    	  printf("%11d  %4s    %4d %30s %19s   %14s %s %16d %s %16s %s",MinorId,flagResult.c_str(),site_id,Comment,Pin,szLowLimit,Units,Value,Units,szHighLimit,Units);
      else if( LengthUnit == 3 )
    	  printf("%11d  %4s    %4d %30s %19s   %13s %s %15d %s %15s %s",MinorId,flagResult.c_str(),site_id,Comment,Pin,szLowLimit,Units,Value,Units,szHighLimit,Units);
      else
    	  printf("%11d  %4s    %4d %30s %19s   %12s %s %14d %s %14s %s",MinorId,flagResult.c_str(),site_id,Comment,Pin,szLowLimit,Units,Value,Units,szHighLimit,Units);

#if 0
      if(CLOGEnable)
      {
          if(Change_Flag){
                api->Datalog_ascii_print("%11s  %4s    %4s %30s %19s   %17s %19s %19s","Test_Number","P/F","Site","Test_Name","Pin","L_Limit","Measure","H_Limit");
          }
          if( LengthUnit == 0 )
              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %17s%s %19d%s %19s%s",MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,Units,Value,Units,szHighLimit,Units);
          else if( LengthUnit == 1 )
              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %15s %s %17d %s %17s %s",MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,Units,Value,Units,szHighLimit,Units);
          else if( LengthUnit == 2 )
              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %14s %s %16d %s %16s %s",MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,Units,Value,Units,szHighLimit,Units);
          else if( LengthUnit == 3 )
              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %13s %s %15d %s %15s %s",MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,Units,Value,Units,szHighLimit,Units);
          else
              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %12s %s %14d %s %14s %s",MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,Units,Value,Units,szHighLimit,Units);
          //print stdf log
          if(STDF_LOG_FLAG == 1){
            api->Datalog_STDF_parametric_test(Comment, STDF_LOW_LIMIT, (double)LowLimit, STDF_HIGH_LIMIT, (double)HighLimit, STDF_UNITS, Units, STDF_RESULT, (double)Value1, STDF_END);  
          }
          else if(STDF_LOG_FLAG == 2){
            api->Datalog_STDF_parametric_test(Comment, STDF_LOW_LIMIT, (double)LowLimit, STDF_UNITS, Units, STDF_RESULT, (double)Value1, STDF_END);  
          }
          else if(STDF_LOG_FLAG == 3){
            api->Datalog_STDF_parametric_test(Comment, STDF_HIGH_LIMIT, (double)HighLimit, STDF_UNITS, Units, STDF_RESULT, (double)Value1, STDF_END);  
          }
          else if(STDF_LOG_FLAG == 4){
            api->Datalog_STDF_parametric_test(Comment, STDF_UNITS, Units, STDF_RESULT, (double)Value1,STDF_SET_RESULT_BIN, 0, STDF_END);  
          }
     //     api->Datalog_STDF_parametric_test(Comment, STDF_LOW_LIMIT, (double)LowLimit, STDF_HIGH_LIMIT, (double)HighLimit, STDF_UNITS, Units, STDF_RESULT, (double)Value, STDF_END);   
      }
             
      api->Set_test_values(name.c_str(),THE_TESTNUMBER, MajorId, THE_END);
       
#endif
      return testResult;
}



//TMResult ValueTest (API *api, const char *Pin, const int &Value,const double &LowLimit, const double &HighLimit, const char *Units, const char *Comment, const char *FailBin, const unsigned int &MinorId, const bool &CLOGEnable)
//{
//      char szLowLimit[32] = {0};
//      char szHighLimit[32] = {0};
//      char szLowUnits[32] = {0};
//      char szHighUnits[32] = {0};
//      TMResult testResult = TM_NOTEST;
//      if (LowLimit == -999999 & HighLimit == 999999)
//      {
//          testResult = TM_PASS;
//      }
//      else if (LowLimit == -999999)
//      {
//        testResult = (Value <= HighLimit ) ? TM_PASS : TM_FAIL;
//        sprintf(szHighLimit,"%f",HighLimit);
//        sprintf(szHighUnits,"%s",Units);
//      }
//      else if (HighLimit == 999999)
//      {
//      testResult = (Value >= LowLimit) ? TM_PASS : TM_FAIL;
//      sprintf(szLowLimit,"%f",LowLimit);
//      sprintf(szLowUnits,"%s",Units);
//      }    
//      else    
//      {
//      testResult = (Value >= LowLimit && Value <= HighLimit ) ? TM_PASS : TM_FAIL;
//      sprintf(szHighLimit,"%f",HighLimit);
//      sprintf(szLowLimit,"%f",LowLimit);
//      sprintf(szLowUnits,"%s",Units);
//      sprintf(szHighUnits,"%s",Units);
//      }
//      
//      string flagResult = "*PASS*";
//      string flagResult_file = "PASS";
//      if( testResult == TM_FAIL )
//      {
//          flagResult = "*FAIL*";
//          flagResult_file = "FAIL";
//      }
//
//      if( strlen(FailBin)!=0 && testResult == TM_FAIL )
//      {
//           if (api->set_result_bin_name(FailBin) == -1 )
//           {
//               api->error_message("set result bin %s failed", FailBin);
//           }      
//       }
//
//      unsigned int MajorId;
//       bool Change_Flag;
//      string name = api->Get_current_test_name();
//      if(name!=Last_TestName)
//      {
//          Change_Flag = true;
//      }
//      else
//      {
//          Change_Flag = false;
//      }
//      Last_TestName=name;
//      api->Get_test_values(name.c_str(),THE_TESTNUMBER, &MajorId, THE_END);
//      if ( MinorId!=0 ) {                     
//           api->Set_test_values(name.c_str(),THE_TESTNUMBER, MajorId + MinorId, THE_END);
//      }
//      if(Change_Flag){
//          api->info_message("%11s  %4s    %4s %30s %19s   %17s %19s %19s","Test_Number","P/F","Site","Test_Name","Pin","L_Limit","Measure","H_Limit");
//      }
//      int LengthUnit = strlen(Units);
//      if( LengthUnit == 0 )
//          api->Info_message("%11d  %4s    %4d %30s %19s   %17s%s %19d%s %19s%s",MinorId,flagResult.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);
//      else if( LengthUnit == 1 )
//          api->Info_message("%11d  %4s    %4d %30s %19s   %15s %s %17d %s %17s %s",MinorId,flagResult.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);
//      else if( LengthUnit == 2 )
//          api->Info_message("%11d  %4s    %4d %30s %19s   %14s %s %16d %s %16s %s",MinorId,flagResult.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);
//      else if( LengthUnit == 3 )
//          api->Info_message("%11d  %4s    %4d %30s %19s   %13s %s %15d %s %15s %s",MinorId,flagResult.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);
//      else
//          api->Info_message("%11d  %4s    %4d %30s %19s   %12s %s %14d %s %14s %s",MinorId,flagResult.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);
//
//      if(CLOGEnable)
//      {
//          if(Change_Flag){
//                api->Datalog_ascii_print("%11s  %4s    %4s %30s %19s   %17s %19s %19s","Test_Number","P/F","Site","Test_Name","Pin","L_Limit","Measure","H_Limit");
//          }
//          if( LengthUnit == 0 )
//              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %17s%s %19d%s %19s%s",MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);
//          else if( LengthUnit == 1 )
//              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %15s %s %17d %s %17s %s",MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);
//          else if( LengthUnit == 2 )
//              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %14s %s %16d %s %16s %s",MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);
//          else if( LengthUnit == 3 )
//              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %13s %s %15d %s %15s %s",MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);
//          else
//              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %12s %s %14d %s %14s %s",MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,szLowLimit,szLowUnits,Value,Units,szHighLimit,szHighUnits);
//          
//          api->Datalog_STDF_parametric_test(Comment, STDF_LOW_LIMIT, LowLimit, STDF_HIGH_LIMIT, HighLimit, STDF_UNITS, Units, STDF_RESULT, Value, STDF_END);   
//      }
//             
//       api->Set_test_values(name.c_str(),THE_TESTNUMBER, MajorId, THE_END);
//       
//
//      return testResult;
//}
//        
        
        
//{
//      TMResult testResult = TM_NOTEST;
//      testResult = (Value >= LowLimit && Value <= HighLimit ) ? TM_PASS : TM_FAIL;
//      string flagResult = "*PASS*";
//      string flagResult_file = "PASS";
//      if( testResult == TM_FAIL )
//      {
//          flagResult = "*FAIL*";
//          flagResult_file = "FAIL";
//      }
//
//      if( strlen(FailBin)!=0 && testResult == TM_FAIL )
//      {
//          if (api->set_result_bin_name(FailBin) == -1 )
//          {
//              api->error_message("set result bin %s failed", FailBin);
//          }      
//       }
//  
//      unsigned int MajorId;
//      string name = api->Get_current_test_name();
//      api->Get_test_values(name.c_str(),THE_TESTNUMBER, &MajorId, THE_END);
//      if ( MinorId!=0 ) {                     
//          api->Set_test_values(name.c_str(),THE_TESTNUMBER, MajorId + MinorId, THE_END);
//      }
//  
//      api->info_message("%11s  %4s    %4s %30s %19s   %17s %19s %19s","Test_Number","P/F","Site","Test_Name","Pin","L_Limit","Measure","H_Limit");
//      int LengthUnit = strlen(Units);
//      if( LengthUnit == 0 )
//          api->Info_message("%11d  %4s    %4d %30s %19s   %17f%s %19f%s %19f%s",MajorId + MinorId,flagResult.c_str(),api->Get_active_site(),Comment,Pin,LowLimit,Units,Value,Units,HighLimit,Units);
//      else if( LengthUnit == 1 )   
//          api->Info_message("%11d  %4s    %4d %30s %19s   %17f%s %19f%s %19f%s",MajorId + MinorId,flagResult.c_str(),api->Get_active_site(),Comment,Pin,LowLimit,Units,Value,Units,HighLimit,Units);
//      else if( LengthUnit == 2 )   
//          api->Info_message("%11d  %4s    %4d %30s %19s   %17f%s %19f%s %19f%s",MajorId + MinorId,flagResult.c_str(),api->Get_active_site(),Comment,Pin,LowLimit,Units,Value,Units,HighLimit,Units);
//      else if( LengthUnit == 3 )   
//          api->Info_message("%11d  %4s    %4d %30s %19s   %17f%s %19f%s %19f%s",MajorId + MinorId,flagResult.c_str(),api->Get_active_site(),Comment,Pin,LowLimit,Units,Value,Units,HighLimit,Units);
//      else
//          api->Info_message("%11d  %4s    %4d %30s %19s   %17f%s %19f%s %19f%s",MajorId + MinorId,flagResult.c_str(),api->Get_active_site(),Comment,Pin,LowLimit,Units,Value,Units,HighLimit,Units);
//      
//      if(CLOGEnable)
//      {
//          api->Datalog_ascii_print("%11s  %4s    %4s %30s %19s   %17s %19s %19s","Test_Number","P/F","Site","Test_Name","Pin","L_Limit","Measure","H_Limit");
//          if( LengthUnit == 0 )
//              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %17f%s %19f%s %19f%s",MajorId + MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,LowLimit,Units,Value,Units,HighLimit,Units);
//          else if( LengthUnit == 1 )   
//              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %17f%s %19f%s %19f%s",MajorId + MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,LowLimit,Units,Value,Units,HighLimit,Units);
//          else if( LengthUnit == 2 )   
//              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %17f%s %19f%s %19f%s",MajorId + MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,LowLimit,Units,Value,Units,HighLimit,Units);
//          else if( LengthUnit == 3 )   
//              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %17f%s %19f%s %19f%s",MajorId + MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,LowLimit,Units,Value,Units,HighLimit,Units);
//          else
//              api->Datalog_ascii_print("%11d  %4s    %4d %30s %19s   %17f%s %19f%s %19f%s",MajorId + MinorId,flagResult_file.c_str(),api->Get_active_site(),Comment,Pin,LowLimit,Units,Value,Units,HighLimit,Units);
//          
//          api->Datalog_STDF_parametric_test(Comment, STDF_LOW_LIMIT, (double)LowLimit, STDF_HIGH_LIMIT, (double)HighLimit, STDF_UNITS, Units, STDF_RESULT, (double)Value, STDF_END);    
//      }
//             
//       api->Set_test_values(name.c_str(),THE_TESTNUMBER, MajorId, THE_END);
//
//      return testResult;
//}  
