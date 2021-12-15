<?xml version="1.0" encoding="UTF-8" ?>
<tests>
    <test name="OS_VSS_FUNC" type="Test" timing="" level="levelset1_OS_VSS" pattern="OS_FUNC" power="OS" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="OS_VSS_PPMU" type="Test" timing="" level="" pattern="" power="OS" comment="">
        <testclass name="libUserCode.Basic_02_OS_VSS_PPMU">
            <propvalues>
                <propvalue name="VSS_pinlist" value="" />
                <propvalue name="IForce" value="-0.0002" />
                <propvalue name="VClampL" value="-1" />
                <propvalue name="VClampH" value="0" />
                <propvalue name="Waittime" value="5000" />
                <propvalue name="SampleSize" value="16" />
            </propvalues>
        </testclass>
    </test>
    <test name="OS_VDD_FUNC" type="Test" timing="" level="levelset1_OS_VDD" pattern="OS_FUNC" power="OS" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="OS_VDD_PPMU" type="Test" timing="" level="" pattern="" power="OS" comment="">
        <testclass name="libUserCode.Basic_02_OS_VDD_PPMU">
            <propvalues>
                <propvalue name="VDD_pinlist" value="" />
                <propvalue name="IForce" value="100*uA" />
                <propvalue name="VClampl" value="#NAME?" />
                <propvalue name="VClamph" value="2*V" />
                <propvalue name="Waittime" value="10*ms" />
                <propvalue name="SampleSize" value="2" />
            </propvalues>
        </testclass>
    </test>
    <test name="waitForAllResults();" type="Test" timing="" level="" pattern="" power="" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="Disconnect();" type="Test" timing="" level="" pattern="" power="" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="OS_PS" type="Test" timing="" level="" pattern="" power="" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="LoadBoard ID" type="Test" timing="" level="" pattern="" power="" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_IDD_OFF_VDDH" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDH_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_limiter" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_IDD_SLEEP" type="Test" timing="SSI_MODE" level="VIHLR_VOHLR_IOHLR" pattern="SSI_MODE" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libUserCode.SSI_MODE">
            <propvalues />
        </testclass>
    </test>
    <test name="SSI_MODE" type="Test" timing="SSI_MODE" level="VIHLR_VOHLR_IOHLR" pattern="SSI_MODE" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libUserCode.SSI_MODE">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOT_UP" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="EFUSE_IRC" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_VREF_TRIM" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_IREF_TRIM" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_CLK32K_TRIM" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_CLK20M_TRIM" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="TSENSOR" type="Test" timing="TCXO_CTRL_ON" level="VIHLR_VOHLR_IOHLR" pattern="TCXO_CTRL_ON" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_POWERON" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOST_IDD_IDLE" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOST_IDD_OFF" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOST_BOOTUP" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="EFUSE_IRC_BST" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOST_POWERON" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOST_VOUT_TRIM" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_LDO_VDDH" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDH_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_LDO_VDDL" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDL_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_IDD_EC0" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_CAPLESS_LDO" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_SIMVCC_RON" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOST_RC_250K_TRIM" type="Test" timing="BOOST_RC250K" level="VIHLR_VOHLR_IOHLR" pattern="BOOST_RC250K" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOST_OSC_TRIM" type="Test" timing="BOOST_OSC" level="VIHLR_VOHLR_IOHLR" pattern="BOOST_OSC" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOST_VOUTH" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOST_VOUTHP" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOST_VOUTL" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDL_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOST_PWRTHRU" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="CMU_TEST" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="MEMORY_TEST MODE 1" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="MEMORY_TEST MODE 2" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="MEMORY_TEST MODE 3" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="MEMORY_TEST MODE 4" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="MEMORY_TEST MODE 5" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="SSI_IO_TEST" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="loadFW" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="Reader_Init" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="ADPLL_TEST" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TX_MODE" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TX_TYPEA_106kbps_MI_100" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TX_TYPEB_212kbps_MI_12" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TX_TYPEB_848kbps_MI12" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TX_TYPEF_212kbps_MI12" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TX_TYPEF_424kbps_MI12" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TX_IDD_POWER" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TX_IMPEDENCE_MIN" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TX_IMPEDENCE_MAX" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="Reader_RX_Init" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="Reader_RX_IDD" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_SNR_THD3" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_COURSE_GAIN4" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_COURSE_GAIN3" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_COURSE_GAIN2" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_COURSE_GAIN1" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_FINE_GAIN4" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_FINE_GAIN3" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_FINE_GAIN2" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_FINE_GAIN1" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_Driv_Invcom" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_SWP_S1_SWIO1" type="Test" timing="SWIO1_S1_CAP" level="VIHLR_VOHLR_IOHLR" pattern="SWIO1_S1_CAP" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_SWP_S2_SWIO1" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_SWP_SWIO2" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_SWP_S1_SWIO3" type="Test" timing="SWIO1_S1_CAP" level="VIHLR_VOHLR_IOHLR" pattern="SWIO3_S1_CAP" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_SWP_S2_SWIO3" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="CMU_TEST_19p2M" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="ADPLL_TEST_27p12M" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="CMU_TEST_27p12M" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="ADPLL_TEST_19p2M" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="CMU_TEST_38p4M" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RESET_MODE" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TAG_MODE" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TAG_CDR" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_FIELD_CLK_EXTRA" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TAG_NCDR" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_FIELD_DET_HP" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_FIELD_DET_NP" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_FIELD_DET_LP" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOST_REG_SCAN" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOST_REG_SCAN_ZERO" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="EFUSE_FRC_BST" type="Test" timing="TIMING_OS" level="VIHLR_VOHLR_IOHLR" pattern="OS_FUNC" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_ADC_108M" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_DAC_216M" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_VBAT2VDDIO" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="XO_CMU_TEST" type="Test" timing="TCXO_CTRL_OFF" level="VIHLR_VOHLR_IOHLR" pattern="TCXO_CTRL_OFF" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_IDD_OFF_VDDN_STA" type="Test" timing="TCXO_CTRL_OFF" level="VIHLR_VOHLR_IOHLR" pattern="TCXO_CTRL_OFF" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="DFT_MODE" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="DFT_MODE_VDDN_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libUserCode.DFT_MODE">
            <propvalues />
        </testclass>
    </test>
    <test name="DFT_MODE_STEP1" type="Test" timing="" level="" pattern="" power="DFT_MODE_STEP1" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="DFT_MODE_STEP2" type="Test" timing="" level="" pattern="" power="DFT_MODE_STEP2" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_JTAG_VDDH" type="Test" timing="DC_TIM6_V1" level="VIHLR_VOHLR_IOHLR" pattern="BSCAN_R01_HI1122" power="JTAG_VDDH_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_JTAG_VDDL" type="Test" timing="DC_TIM6_V1" level="VIHLR_VOHLR_IOHLR" pattern="BSCAN_R01_HI1122" power="JTAG_VDDL_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_CHAIN_VDDH" type="Test" timing="CHAIN_TIM2_V1" level="VIHLR_VOHLR_IOHLR" pattern="CHAIN_R01_HI1122_ONECLK_BODY" power="CHAIN_VDDH_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_CHAIN_VDDL" type="Test" timing="CHAIN_TIM2_V1" level="VIHLR_VOHLR_IOHLR" pattern="CHAIN_R01_HI1122_ONECLK_BODY" power="CHAIN_VDDL_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_STUCKAT_VDDH" type="Test" timing="STUCK_TIM2_V1" level="VIHLR_VOHLR_IOHLR" pattern="STUCK_R01_HI1122_ONECLK_BODY" power="SA_VDDH_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_STUCKAT_VDDL" type="Test" timing="STUCK_TIM2_V1" level="VIHLR_VOHLR_IOHLR" pattern="STUCK_R01_HI1122_ONECLK_BODY" power="SA_VDDL_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_TRANS_VDDH" type="Test" timing="TRANS_TIM3_V1" level="VIHLR_VOHLR_IOHLR" pattern="TRANS_R03_HI1122_ONECLK_INIT" power="TRANS_VDDH_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_TRANS_VDDL" type="Test" timing="TRANS_TIM3_V1" level="VIHLR_VOHLR_IOHLR" pattern="TRANS_R03_HI1122_ONECLK_INIT" power="TRANS_VDDL_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_RAM_VDDH" type="Test" timing="MBIST_TIM4_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_PART1" power="MBIST_540ns_VDDH_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_RAM_VDDL" type="Test" timing="MBIST_TIM4_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_PART1" power="MBIST_540ns_VDDL_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_RAM_MINOR1_VDDH" type="Test" timing="MBIST_TIM4_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_PART1_MINOR1" power="MBIST_540ns_VDDH_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_RAM_MINOR1_VDDL" type="Test" timing="MBIST_TIM4_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_PART1_MINOR1" power="MBIST_540ns_VDDL_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_RAM_PLUS1_VDDH" type="Test" timing="MBIST_TIM4_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_PART1_PLUS1" power="MBIST_540ns_VDDH_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_RAM_PLUS1_VDDL" type="Test" timing="MBIST_TIM4_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_PART1_PLUS1" power="MBIST_540ns_VDDL_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_ROM_VDDH" type="Test" timing="MBIST_TIM5_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_ROM" power="MBIST_80ns_VDDH_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_ROM_VDDL" type="Test" timing="MBIST_TIM5_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_ROM" power="MBIST_80ns_VDDL_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_ROM_MINOR1_VDDH" type="Test" timing="MBIST_TIM5_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_ROM_MINOR1" power="MBIST_80ns_VDDH_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_ROM_MINOR1_VDDL" type="Test" timing="MBIST_TIM5_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_ROM_MINOR1" power="MBIST_80ns_VDDL_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_ROM_PLUS1_VDDH" type="Test" timing="MBIST_TIM5_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_ROM_PLUS1" power="MBIST_80ns_VDDH_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_ROM_PLUS1_VDDL" type="Test" timing="MBIST_TIM5_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_ROM_PLUS1" power="MBIST_80ns_VDDL_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_IDDQ" type="Test" timing="DC_IDDQ_TIM2_V1" level="VIHLR_VOHLR_IOHLR" pattern="IDDQ_R02_HI1122_ONECLK" power="IDDQ_20ns_VDDN_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="DC_IDDQ" type="Test" timing="DC_IDDQ_TIM2_V1" level="VIHLR_VOHLR_IOHLR" pattern="IDDQ_R02_HI1122_ONECLK" power="IDDQ_20ns_VDDN_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libUserCode.Basic_04_DC_IDDQ_Measure">
            <propvalues>
                <propvalue name="Measure_pinlist" value="" />
                <propvalue name="SampleSize" value="16" />
            </propvalues>
        </testclass>
    </test>
    <test name="FC_VIHL_VDDL" type="Test" timing="IOZ_TIM6_V1" level="VIHLS_VOHLR_IOHLR" pattern="VIHL_R01_HI1122_NO_PULL" power="DC_VDDL_VIHLS_VOHLR_IOHLR" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_VIHL_VDDH" type="Test" timing="IOZ_TIM6_V1" level="VIHLS_VOHLR_IOHLR" pattern="VIHL_R01_HI1122_NO_PULL" power="DC_VDDH_VIHLS_VOHLR_IOHLR" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_IOZ_VDDN" type="Test" timing="IOZ_TIM6_V1" level="VIHLR_VOHLR_IOHLS" pattern="IOZ_R01_HI1122" power="IOZ_VDDH_VIHLR_VOHLR_IOHLS" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_VOHL_VDDL" type="Test" timing="IOZ_TIM6_V1" level="VIHLR_VOHLS_IOHLS" pattern="VOHL_R01_HI1122" power="DC_VDDL_VIHLR_VOHLS_IOHLS" comment="">
        <testclass name="libUserCode.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="DC_IIHL_PU_VDDH" type="Test" timing="IOZ_TIM6_V1" level="VIHLR_VOHLR_IOHLR" pattern="VIHL_R01_HI1122_PULL_DOWN" power="DC_VDDH_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libUserCode.Basic_03_DC_IIHL_Leakage">
            <propvalues>
                <propvalue name="Measure_pinlist" value="gDFTPINS,gDFTPINS_DC," />
                <propvalue name="IIH_VForce" value="1.98" />
                <propvalue name="RangeH" value="100e-6" />
                <propvalue name="IIH_IClampL" value="-100e-6" />
                <propvalue name="IIH_IClampH" value="100e-6" />
                <propvalue name="IIL_VForce" value="0.0" />
                <propvalue name="RangeL" value="100e-6" />
                <propvalue name="IIL_IClampL" value="-100e-6" />
                <propvalue name="IIL_IClampH" value="100e-6" />
                <propvalue name="Waittime" value="10e-3" />
                <propvalue name="SampleSize" value="12" />
            </propvalues>
        </testclass>
    </test>
    <test name="DC_IIHLPD_VDDH" type="Test" timing="DC_TIM6_V1" level="VIHLR_VOHLR_IOHLR" pattern="VIHL_R01_HI1122_PULL_DOWN" power="DC_VDDH_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libUserCode.Basic_03_DC_IIHL_Leakage">
            <propvalues>
                <propvalue name="Measure_pinlist" value="gDFTPINS_DC,gDFTPINS," />
                <propvalue name="IIH_VForce" value="1.98" />
                <propvalue name="RangeH" value="100e-6" />
                <propvalue name="IIH_IClampL" value="-100e-6" />
                <propvalue name="IIH_IClampH" value="100e-6" />
                <propvalue name="IIL_VForce" value="0.0" />
                <propvalue name="RangeL" value="10e-6" />
                <propvalue name="IIL_IClampL" value="-10e-6" />
                <propvalue name="IIL_IClampH" value="10e-6" />
                <propvalue name="Waittime" value="10e-3" />
                <propvalue name="SampleSize" value="12" />
            </propvalues>
        </testclass>
    </test>
    <test name="DC_IOZ_VDDH" type="Test" timing="IOZ_TIM6_V1" level="VIHLR_VOHLR_IOHLS" pattern="IOZ_R01_HI1122" power="IOZ_VDDN_VIHLR_VOHLR_IOHLS" comment="">
        <testclass name="libUserCode.DC_IOZHL_PPMU">
            <propvalues>
                <propvalue name="strPinList" value="" />
                <propvalue name="VForce" value="" />
                <propvalue name="IRang" value="" />
                <propvalue name="SampleSize" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="DFT_EXIT_STEP1" type="Test" timing="" level="" pattern="" power="DFT_EXIT_STEP1" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="DFT_EXIT_STEP2" type="Test" timing="" level="" pattern="" power="DFT_EXIT_STEP2" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
</tests>
