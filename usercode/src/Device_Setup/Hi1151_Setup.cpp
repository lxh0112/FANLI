#include "GetLog.h" 
#include "CCS08F.h"
#include "Excel.h"
#include <string>
#include "RegDef.h"
#include "d2sProtocolSSI.h"
#include "UserDef.h"
#include "Globle_Var.h"

#include <sstream>// V200 202108

/*******************************************************************************************************************************************************************
//===============================================================Hi1151_RX_SETUP_CODE===============================================================================
 ********************************************************************************************************************************************************************/

int Set_RF_RX_Pll_BW(emMode RF_Mode, emRX_Band RF_Band, double LPF_BW, char * Channel) {
    bool RFModeBand_Changed_flag = true;
    bool LPFBW_Changed_flag = true;

    RFModeBand_Changed_flag = RFMode_Changed(RF_Mode, RF_Band);
    LPFBW_Changed_flag = LPFBW_Changed(LPF_BW);

    if (RFModeBand_Changed_flag) {
        RX_PLL_Setup(RF_Mode, RF_Band, Channel, LPF_BW);
    }

    if (LPFBW_Changed_flag) {
        RX_BW_Setup(RF_Mode, RF_Band, Channel, LPF_BW);
    }

    //    d2s::d2s_LABEL_BEGIN("burst_test", "ssi", LearningMode);
    //    d2sProtocolSSI d2s_test;
    ////    d2s_test.SSI_write(0x200, 0x2000, false);
    ////    d2s_test.SSI_write(0x202, 0x90, false);
    ////    d2s_test.SSI_read(0x34,"readdata",9);
    //    d2s_test.SSI_write(0x200,0x2000,false);
    //    d2s_test.SSI_write(0x202,0x40,false);
    //    d2s_test.SSI_read(0x330,"readdata",9);
    //    d2s::d2s_LABEL_END();

    //    map<int, long long> capture_data;
    //    FOREACH_ACTIVE_SITE(){
    //        long long readvalue = d2s_test.getReadValue("readdata");
    //        int site_id = ->Get_active_site();
    //        capture_data[site_id] = readvalue ;
    //        ->info_message("Site:%d---------- %s    measure  value    :    %lld-----------",site_id,"SSI_DATA",capture_data[site_id]);
    //    }

    return EXIT_SUCCESS;
}

bool RFMode_Changed(emMode RF_Mode, int RF_Band) {
    //    static int Last_RFmode = 0;
    //    static int Last_RFband = 0;
    bool Change_Flag;

    if (RF_Mode == Last_RFmode && RF_Band == Last_RFband) {
        Change_Flag = false;
    } else {
        Change_Flag = true;
    }

    Last_RFmode = RF_Mode;
    Last_RFband = RF_Band;

    return Change_Flag;
}

bool LPFBW_Changed(double LPF_BW) {
    //    static int Last_LPFBW = 0;
    bool Change_Flag;

    if (LPF_BW == Last_LPFBW) {
        Change_Flag = false;
    } else {
        Change_Flag = true;
    }

    Last_LPFBW = LPF_BW;

    return Change_Flag;
}

int RX_PLL_Setup(emMode Mode_Select, emRX_Band Band_Select, char *Channel, double BW) {
    char *Channel_p;
    Channel_p = strstr(Channel, "C0");

    if (Mode_Select == WLAN_2G_Mode) {
        if (Channel_p != NULL) {
            WLAN_2G_RX_C0_PLL_Reg(Band_Select, BW);
        } else {
            WLAN_2G_RX_C1_PLL_Reg(Band_Select, BW);
        }

    } else if (Mode_Select == WLAN_5G_Mode) {
        if (Channel_p != NULL) {
            WLAN_5G_RX_C0_PLL_Reg(Band_Select, BW);
        } else {
            WLAN_5G_RX_C1_PLL_Reg(Band_Select, BW);
        }

    }

    return EXIT_SUCCESS;
}

int RX_BW_Setup(emMode Mode_Select, emRX_Band Band_Select, char *Channel, double BW) {
    char *Channel_p;
    Channel_p = strstr(Channel, "C0");

    if (Mode_Select == WLAN_2G_Mode) {
        if (Channel_p != NULL) {
            WLAN_2G_RX_C0_BW_Reg(Band_Select, BW);
        } else {
            WLAN_2G_RX_C1_BW_Reg(Band_Select, BW);
        }

    } else if (Mode_Select == WLAN_5G_Mode) {
        if (Channel_p != NULL) {
            WLAN_5G_RX_C0_BW_Reg(Band_Select, BW);
        } else {
            WLAN_5G_RX_C1_BW_Reg(Band_Select, BW);
        }
    }

    return EXIT_SUCCESS;
}

int Set_RF_RX_GainMode(char * GainMode, emMode RF_Mode, char * Channel) {
    bool Changed_flag = true;

    Changed_flag = GainMode_Changed(GainMode); //true;//= GainMode_Changed(GainMode);

    if (Changed_flag) {
        RX_Gain_Mode_Setup(RF_Mode, GainMode, Channel);
    }

    return EXIT_SUCCESS;
}

bool GainMode_Changed(char *GainMode) {
    //    static char *Last_GainMode = "\0";
    bool Change_Flag;

    if (!strcmp(GainMode, Last_GainMode)) {
        Change_Flag = false;
    } else {
        Change_Flag = true;
    }

    Last_GainMode = GainMode;

    return Change_Flag;
}

int RX_Gain_Mode_Setup(emMode Mode_Select, char *RX_Gain_Mode_Label, char *Channel) {
    char *Channel_p;
    Channel_p = strstr(Channel, "C0");

    if (Mode_Select == WLAN_2G_Mode) {
        if (Channel_p != NULL) {
            WLAN_2G_RX_C0_Gain_Mode_Reg(RX_Gain_Mode_Label);
        } else {
            WLAN_2G_RX_C1_Gain_Mode_Reg(RX_Gain_Mode_Label);
        }

    } else if (Mode_Select == WLAN_5G_Mode) {
        if (Channel_p != NULL) {
            WLAN_5G_RX_C0_Gain_Mode_Reg(RX_Gain_Mode_Label);
        } else {
            WLAN_5G_RX_C1_Gain_Mode_Reg(RX_Gain_Mode_Label);
        }
    }
    return EXIT_SUCCESS;
}

/*******************************************************************************************************************************************************************
//===============================================================Hi1151_TX_SETUP_CODE===============================================================================
 ********************************************************************************************************************************************************************/

int Set_RF_TX_Pll_BW(emMode RF_Mode, emTX_Band RF_Band, double LPF_BW, char *Channel) {
    bool RFModeBand_Changed_flag;
    bool LPFBW_Changed_flag;

    RFModeBand_Changed_flag = RFMode_Changed(RF_Mode,RF_Band);  //???????
    LPFBW_Changed_flag = LPFBW_Changed(LPF_BW);

    if (RFModeBand_Changed_flag) {
        TX_PLL_Setup(RF_Mode, RF_Band, Channel, LPF_BW);
    }

    if (LPFBW_Changed_flag) {
        TX_BW_Setup(RF_Mode, RF_Band, Channel, LPF_BW);
    }

    return EXIT_SUCCESS;
}

int TX_PLL_Setup(emMode Mode_Select, emTX_Band Band_Select, char *Channel, double BW) {
    char *Channel_p;
    Channel_p = strstr(Channel, "C0");

    if (Mode_Select == WLAN_2G_Mode) {
        if (Channel_p != NULL) {
            WLAN_2G_TX_C0_PLL_Reg(Band_Select);
        } else {
            WLAN_2G_TX_C1_PLL_Reg(Band_Select);
        }

    } else if (Mode_Select == WLAN_5G_Mode) {
        if (Channel_p != NULL) {
            WLAN_5G_TX_C0_PLL_Reg(Band_Select, BW);
        } else {
            WLAN_5G_TX_C1_PLL_Reg(Band_Select, BW);
        }

    }
    return EXIT_SUCCESS;
}

int TX_BW_Setup(emMode Mode_Select, emTX_Band Band_Select, char *Channel, double BW) {
    char *Channel_p;
    Channel_p = strstr(Channel, "C0");

    if (Mode_Select == WLAN_2G_Mode) {
        if (Channel_p != NULL) {
            WLAN_2G_TX_C0_BW_Reg(Band_Select);
        } else {
            WLAN_2G_TX_C1_BW_Reg(Band_Select);
        }

    } else if (Mode_Select == WLAN_5G_Mode) {
        if (Channel_p != NULL) {
            WLAN_5G_TX_C0_BW_Reg(Band_Select, BW);
        } else {
            WLAN_5G_TX_C1_BW_Reg(Band_Select, BW);
        }
    }

    return EXIT_SUCCESS;
}

/*******************************************************************************************************************************************************************
===============================================================Hi1151_INIT_SETUP_CODE===============================================================================
 ********************************************************************************************************************************************************************/
int Test_Mode_Init_Setup(emMode Mode_Select, emTRX TRX_Path_Select, char *Channel) {
    char *Channel_p;
    Channel_p = strstr(Channel, "C0");

    if (Mode_Select == WLAN_2G_Mode) {
        if (TRX_Path_Select == RX_Path) {
            if (Channel_p != NULL) {
                WLAN_RX_2G_C0_Init_Reg();
            } else {
                WLAN_RX_2G_C1_Init_Reg();
            }
        } else {
            if (Channel_p != NULL) {
                WLAN_TX_2G_C0_Init_Reg();
            } else {
                WLAN_TX_2G_C1_Init_Reg();
            }
        }
    } else {
        if (TRX_Path_Select == RX_Path) {
            if (Channel_p != NULL) {
                WLAN_RX_5G_C0_Init_Reg();
            } else {
                WLAN_RX_5G_C1_Init_Reg();
            }
        } else {
            if (Channel_p != NULL) {
                WLAN_TX_5G_C0_Init_Reg();
            } else {
                WLAN_TX_5G_C1_Init_Reg();
            }
        }
    }

    return EXIT_SUCCESS;
}

int TestMUX_Init_Setup(emTRX TRX_Path_Select, char * Channel) {
    char *Channel_p;
    Channel_p = strstr(Channel, "C0");

    if (TRX_Path_Select == RX_Path) {
        if (Channel_p != NULL) {
            TestMux_RX_C0_Reg();
        } else {
            TestMux_RX_C1_Reg();
        }
    } else {
        if (Channel_p != NULL) {
            TestMux_TX_C0_Reg();
        } else {
            TestMux_TX_C1_Reg();
        }
    }

    return EXIT_SUCCESS;

}

string ConvertToArray(long long src_data, unsigned long * des_array, unsigned long num_vectors, unsigned long padding, unsigned long lsb, unsigned long msb, char low_waveform, char high_waveform, unsigned long mask) {
    if (num_vectors == 0) {
        return "";
    }
    ostringstream des_str; //"0101010101";
    unsigned long maskBit = 0;
    for (unsigned long index = 0; index < num_vectors; index++) {
        unsigned long shift = lsb > msb ? (num_vectors - 1 - index) : index;
        des_array[index] = src_data >> (shift / padding) & 0x01;
        maskBit = mask >> (shift / padding) & 0x01;
        if (maskBit == 0x01) {
            des_str << (des_array[index] == 0 ? low_waveform : high_waveform);
        } else {
            des_str << 'X';
        }
    }
    return des_str.str();
}



int Write_RC_C_CODE(char * Channel) {

    char * Channel_p;
    Channel_p = strstr(Channel, "C0");

    d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
    d2sProtocolSSI d2s_test;
    d2s_test.SSI_write(0x200, 0x2000, false);
    d2s_test.SSI_write(0x202, 0x90, false);
    d2s::d2s_LABEL_END();
    map<int, long long> reg_44_val;
    map<int, long long> reg_4C_val;
    map<int, long long> reg_3C_val;

    	FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)

            reg_44_val[index] = RC_CAL_CODE_C0(index, 0) * 64 + RC_CAL_CODE_C0(index, 0) + 4096;
            reg_4C_val[index] = RC_CAL_CODE_C1(index, 0) * 64 + RC_CAL_CODE_C1(index, 0) + 4096;
            reg_3C_val[index] = C_CAL_CODE_C0(index, 0) + C_CAL_CODE_C1(index, 0) * 8 + R_CAL_CODE_C1(index, 0) * 128 + 8 + 128 + 2048;

		FOREACH_ACTIVESITE_END

        d2s::d2s_LABEL_BEGIN("dynamic", d2s_WorkMode);
			d2s_test.SSI_writeDynamic(0x44, reg_44_val, "write");
			d2s_test.SSI_writeDynamic(0x40, reg_44_val, "write");
			d2s_test.SSI_writeDynamic(0x4C, reg_4C_val, "write");
			d2s_test.SSI_writeDynamic(0x48, reg_4C_val, "write");
			d2s_test.SSI_writeDynamic(0x3C, reg_3C_val, "write");
        d2s::d2s_LABEL_END();


//        FOREACH_ACTIVE_SITE() {
//            int site_id = ->Get_active_site();
//            reg_4C_val[site_id] = RC_CAL_CODE_C1(site_id, 0) * 64 + RC_CAL_CODE_C1(site_id, 0) + 4096;
//            reg_3C_val[site_id] = C_CAL_CODE_C0(site_id, 0) + C_CAL_CODE_C1(site_id, 0) * 8 + R_CAL_CODE_C1(site_id, 0) * 128 + 8 + 128 + 2048;
//        }
//        d2s::d2s_LABEL_BEGIN("burst_test", "dynamic", d2s_WorkMode);
//        d2s_test.SSI_writeDynamic(0x4C, reg_4C_val, "write");
//        d2s_test.SSI_writeDynamic(0x48, reg_4C_val, "write");
//        d2s_test.SSI_writeDynamic(0x3C, reg_3C_val, "write");
//        d2s::d2s_LABEL_END();

    return EXIT_SUCCESS;

}



//int Write_RC_C_CODE(char * Channel) {
//
//    char * Channel_p;
//    Channel_p = strstr(Channel, "C0");
//
//    d2s::d2s_LABEL_BEGIN("burst_test", "ssi", d2s_WorkMode);
//    d2sProtocolSSI d2s_test;
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x90, false);
//    d2s::d2s_LABEL_END();
//    map<int, long long> reg_44_val;
//    map<int, long long> reg_4C_val;
//    map<int, long long> reg_3C_val;
//    if (Channel_p != NULL) {
//
//        FOREACH_ACTIVE_SITE() {
//            int site_id = ->Get_active_site();
//            reg_44_val[site_id] = RC_CAL_CODE_C0(site_id, 0) * 64 + RC_CAL_CODE_C0(site_id, 0) + 4096;
//            reg_3C_val[site_id] = C_CAL_CODE_C0(site_id, 0) + C_CAL_CODE_C1(site_id, 0) * 8 + R_CAL_CODE_C1(site_id, 0) * 128 + 8 + 128 + 2048;
//        }
//
//        d2s::d2s_LABEL_BEGIN("burst_test", "dynamic", d2s_WorkMode);
//        d2s_test.SSI_writeDynamic(0x44, reg_44_val, "write");
//        d2s_test.SSI_writeDynamic(0x40, reg_44_val, "write");
//        d2s_test.SSI_writeDynamic(0x3C, reg_3C_val, "write");
//        d2s::d2s_LABEL_END();
//
//    } else {
//
//        FOREACH_ACTIVE_SITE() {
//            int site_id = ->Get_active_site();
//            reg_4C_val[site_id] = RC_CAL_CODE_C1(site_id, 0) * 64 + RC_CAL_CODE_C1(site_id, 0) + 4096;
//            reg_3C_val[site_id] = C_CAL_CODE_C0(site_id, 0) + C_CAL_CODE_C1(site_id, 0) * 8 + R_CAL_CODE_C1(site_id, 0) * 128 + 8 + 128 + 2048;
//        }
//        d2s::d2s_LABEL_BEGIN("burst_test", "dynamic", d2s_WorkMode);
//        d2s_test.SSI_writeDynamic(0x4C, reg_4C_val, "write");
//        d2s_test.SSI_writeDynamic(0x48, reg_4C_val, "write");
//        d2s_test.SSI_writeDynamic(0x3C, reg_3C_val, "write");
//        d2s::d2s_LABEL_END();
//    }
//
//    return EXIT_SUCCESS;
//
//}
#if 0
int TRX_Init() {

    //const char* testname = NULL;
    tyTestData RF_Test_Data;
    emTRX TRX_Path_Select;
    char *Channel;
    emMode Mode_Select;
    string testname = TheSoft.Flow().Test().GetCurrentTestName();
    //testname = ->Get_current_test_name();



    Get_TestItem_Info(testname.c_str(), RF_Test_Data);
    Channel = RF_Test_Data.cChannel;
    TRX_Path_Select = RF_Test_Data.iTRX;
    Mode_Select = (emMode) RF_Test_Data.iMode;

    //disconnectall RF pins
    //disconnectall ana pins
    //LB UPAC K2/K3 RELAY
    if (TRX_Path_Select == RX_Path) {
#if 0
        ->Set_loadboard_x_ubits(X_UBIT_NONE, X_UBIT_051 + X_UBIT_024 + X_UBIT_020 + X_UBIT_065);
        ->Set_loadboard_x_ubits(X_UBIT_NONE, X_UBIT_019 + X_UBIT_033 + X_UBIT_011 + X_UBIT_056);
#endif
    } else {
#if 0
        ->Set_loadboard_x_ubits(X_UBIT_051 + X_UBIT_024 + X_UBIT_020 + X_UBIT_065, X_UBIT_NONE);
        ->Set_loadboard_x_ubits(X_UBIT_019 + X_UBIT_033 + X_UBIT_011 + X_UBIT_056, X_UBIT_NONE);
#endif
    }

    //start pattern
    Test_Mode_Init_Setup(Mode_Select, TRX_Path_Select, Channel);
    TestMUX_Init_Setup(TRX_Path_Select, Channel);
    if((strstr(testname.c_str() , "RX"))&&(strstr(testname.c_str() , "C0_RFI_INIT"))){
        Write_RC_PPF(TRX_Path_Select, Channel);
    }
    
//    d2s::d2s_LABEL_BEGIN("burst_test", "dynamic", d2s_WorkMode);
//    d2sProtocolSSI d2s_test;
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x90, false);
//    d2s_test.SSI_read(0x44, "readdata1");
//    d2s_test.SSI_read(0x40, "readdata2");
//    d2s_test.SSI_read(0x4C, "readdata3");
//    d2s_test.SSI_read(0x48, "readdata4");
//    d2s_test.SSI_read(0x3C, "readdata5");
//    d2s::d2s_LABEL_END();
//    
//    map<int, long long> capture_data1;
//    map<int, long long> capture_data2;
//    map<int, long long> capture_data3;
//    map<int, long long> capture_data4;
//    map<int, long long> capture_data5;
//
//    FOREACH_ACTIVE_SITE(){
//        long long readvalue1 = d2s_test.getReadValue("readdata1");
//        long long readvalue2 = d2s_test.getReadValue("readdata2");
//        long long readvalue3 = d2s_test.getReadValue("readdata3");
//        long long readvalue4 = d2s_test.getReadValue("readdata4");
//        long long readvalue5 = d2s_test.getReadValue("readdata5");
//        int site_id = ->Get_active_site();
//        capture_data1[site_id] = readvalue1 ;
//        capture_data2[site_id] = readvalue2 ;
//        capture_data3[site_id] = readvalue3 ;
//        capture_data4[site_id] = readvalue4 ;
//        capture_data5[site_id] = readvalue5 ;
//        
//        ValueTest ("SSI_DATA", capture_data1[site_id], 0, 0, "", "RC_CODE", "FAIL_BIN", 10000, Clogenable);
//        ValueTest ("SSI_DATA", capture_data2[site_id], 0, 0,"" , "RC_CODE", "FAIL_BIN", 10000, Clogenable);
//        ValueTest ("SSI_DATA", capture_data3[site_id], 0, 0,"" , "RC_CODE", "FAIL_BIN", 10000, Clogenable);
//        ValueTest ("SSI_DATA", capture_data4[site_id], 0, 0,"" , "RC_CODE", "FAIL_BIN", 10000, Clogenable);
//        ValueTest ("SSI_DATA", capture_data5[site_id], 0, 0,"" , "RC_CODE", "FAIL_BIN", 10000, Clogenable);
//    }
    
    Last_GainMode = (char*) "\0";
    Last_RFmode = -1;
    Last_RFband = -1;
    Last_LPFBW = -1;

    RX_GAIN_I_LIST.Clear();
    RX_GAIN_Q_LIST.Clear();

    return EXIT_SUCCESS;
}
#endif

#if 0
int TRX_Disable() {
    WLAN_Disable_Reg();

    return EXIT_SUCCESS;
}
#endif
