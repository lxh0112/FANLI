<?xml version="1.0" encoding="UTF-8" ?>
<tests>
    <test name="OS_VSS_FUNC" type="Test" timing="" level="levelset1_OS_VSS" pattern="OS_FUNC" power="OS" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="OS_VSS_PPMU" type="Test" timing="" level="" pattern="" power="OS" comment="">
        <testclass name="libtestp_share2.Basic_02_OS_VDD_VSS_PPMU">
            <propvalues>
                <propvalue name="Measure_pinlist" value="gOS,gOS_M," />
                <propvalue name="IForce" value="" />
                <propvalue name="Range" value="" />
                <propvalue name="VClampL" value="-2" />
                <propvalue name="VClampH" value="2" />
                <propvalue name="WaitTime" value="0.005" />
                <propvalue name="SampleSize" value="2" />
            </propvalues>
        </testclass>
    </test>
    <test name="OS_VDD_FUNC" type="Test" timing="" level="levelset1_OS_VDD" pattern="OS_FUNC" power="OS" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="OS_VDD_PPMU" type="Test" timing="" level="" pattern="" power="OS" comment="">
        <testclass name="libtestp_share2.Basic_02_OS_VDD_VSS_PPMU">
            <propvalues>
                <propvalue name="Measure_pinlist" value="gOS,gOS_M," />
                <propvalue name="IForce" value="" />
                <propvalue name="Range" value="" />
                <propvalue name="VClampL" value="-2" />
                <propvalue name="VClampH" value="2" />
                <propvalue name="WaitTime" value="0.005" />
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
    <test name="OS_PS" type="Test" timing="" level="" pattern="" power="OS_PS" comment="">
        <testclass name="libtestp_share2.Basic_00_PowerShort">
            <propvalues>
                <propvalue name="powerpinlist" value="" />
                <propvalue name="WaitTime" value="" />
                <propvalue name="SampleSize" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="LoadBoard ID" type="Test" timing="" level="" pattern="" power="" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_IDD_OFF_VDDH" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDH_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.PMU_IDD_OFFVDDH">
            <propvalues>
                <propvalue name="Measure_pinlist" value="BOOST_LX,VBAT,VDDIO," />
                <propvalue name="WaitTime" value="10e-3" />
                <propvalue name="SampleSize" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="NFC_limiter" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_limiter">
            <propvalues>
                <propvalue name="Measure_pinlist" value="RXN_D,RXP_D," />
                <propvalue name="WaitTime" value="10e-3" />
                <propvalue name="SampleSize" value="3" />
                <propvalue name="IForce" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="PMU_IDD_SLEEP" type="Test" timing="SSI_MODE" level="VIHLR_VOHLR_IOHLR" pattern="SSI_MODE" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.PMU_IDD_SLEEP">
            <propvalues>
                <propvalue name="WaitTime" value="10e-3" />
                <propvalue name="SampleSize" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="SSI_MODE" type="Test" timing="SSI_MODE" level="VIHLR_VOHLR_IOHLR" pattern="SSI_MODE" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.SSI_MODE">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOT_UP" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.BOOT_UP">
            <propvalues />
        </testclass>
    </test>
    <test name="EFUSE_IRC" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_VREF_TRIM" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.PMU_VrefTrim">
            <propvalues>
                <propvalue name="Measure_pinlist" value="PMU_REFBP," />
                <propvalue name="WaitTime" value="0.005" />
                <propvalue name="SampleSize" value="2" />
            </propvalues>
        </testclass>
    </test>
    <test name="PMU_IREF_TRIM" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.PMU_IrefTrim">
            <propvalues>
                <propvalue name="Measure_pinlist" value="" />
                <propvalue name="WaitTime" value="" />
                <propvalue name="SampleSize" value="" />
                <propvalue name="VForce" value="" />
                <propvalue name="IRange" value="" />
                <propvalue name="IClampL" value="" />
                <propvalue name="IClampH" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="PMU_CLK32K_TRIM" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.PMU_CLK32K_TRIM">
            <propvalues>
                <propvalue name="Measure_pinlist" value="PMU_REFBP" />
                <propvalue name="WaitTime" value="0.005" />
                <propvalue name="SampleSize" value="4" />
            </propvalues>
        </testclass>
    </test>
    <test name="PMU_CLK20M_TRIM" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.PMU_CLK20M_TRIM">
            <propvalues>
                <propvalue name="Measure_pinlist" value="" />
                <propvalue name="WaitTime" value="" />
                <propvalue name="SampleSize" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="TSENSOR" type="Test" timing="TCXO_CTRL_ON" level="VIHLR_VOHLR_IOHLR" pattern="TCXO_CTRL_ON" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.Tsensor_Test">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_POWERON" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.BOOST_POWERON">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOST_IDD_IDLE" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.BOOST_IDD_IDLE">
            <propvalues>
                <propvalue name="Measure_pinlist" value="" />
                <propvalue name="WaitTime" value="" />
                <propvalue name="SampleSize" value="" />
                <propvalue name="IRange" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="BOOST_IDD_OFF" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.BOOST_IDD_OFF">
            <propvalues>
                <propvalue name="Measure_pinlist" value="" />
                <propvalue name="WaitTime" value="" />
                <propvalue name="SampleSize" value="" />
                <propvalue name="IRange" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="BOOST_BOOTUP" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.BOOST_BOOTUP">
            <propvalues />
        </testclass>
    </test>
    <test name="EFUSE_IRC_BST" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.EFUSE_IRC_BST">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOST_POWERON" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.BOOST_POWERON">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOST_VOUT_TRIM" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.BOOST_VOUT_TRIM">
            <propvalues>
                <propvalue name="Measure_pinlist" value="" />
                <propvalue name="WaitTime" value="" />
                <propvalue name="SampleSize" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="PMU_LDO_VDDH" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDH_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.PMU_LDO_VDDH">
            <propvalues>
                <propvalue name="Pinlist" value="" />
                <propvalue name="IForce" value="" />
                <propvalue name="Irangedps" value="" />
                <propvalue name="IClampL" value="" />
                <propvalue name="IClampH" value="" />
                <propvalue name="WaitTime" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="PMU_LDO_VDDL" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDL_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.PMU_LDO_VDDL">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_IDD_EC0" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.PMU_IDD_EC0">
            <propvalues>
                <propvalue name="Measure_pinlist" value="VBAT,VDDIO," />
                <propvalue name="WaitTime" value="5e-3" />
                <propvalue name="SampleSize" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="PMU_CAPLESS_LDO" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.PMU_CAPLESS_LDO_TEST">
            <propvalues>
                <propvalue name="Measure_pinlist" value="NFC_GPIO1," />
                <propvalue name="SampleSize" value="3" />
                <propvalue name="IForce" value="0" />
                <propvalue name="IRange" value="1e-9" />
                <propvalue name="Waittime" value="5e-3" />
            </propvalues>
        </testclass>
    </test>
    <test name="PMU_SIMVCC_RON" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.PMU_SIMVCC_RON">
            <propvalues>
                <propvalue name="Measure_pinlist" value="SIMVCC1,SIMVCC2,SIMVCC3," />
                <propvalue name="WaitTime" value="0.001" />
                <propvalue name="SampleSize" value="3" />
                <propvalue name="IForce" value="100e-3" />
                <propvalue name="IRange" value="" />
                <propvalue name="IClampL" value="" />
                <propvalue name="IClampH" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="BOOST_RC_250K_TRIM" type="Test" timing="BOOST_RC250K" level="VIHLR_VOHLR_IOHLR" pattern="BOOST_RC250K" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.BOOST_RC_250K_TRIM">
            <propvalues>
                <propvalue name="Measure_pinlist" value="" />
                <propvalue name="WaitTime" value="" />
                <propvalue name="SampleSize" value="" />
                <propvalue name="VForce" value="" />
                <propvalue name="IRange" value="" />
                <propvalue name="IClampL" value="" />
                <propvalue name="IClampH" value="" />
                <propvalue name="Waittime" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="BOOST_OSC_TRIM" type="Test" timing="BOOST_OSC" level="VIHLR_VOHLR_IOHLR" pattern="BOOST_OSC" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.BOOST_OSC_TRIM">
            <propvalues>
                <propvalue name="Measure_pinlist" value="BOOST_LX_D" />
                <propvalue name="WaitTime" value="0.001" />
                <propvalue name="SampleSize" value="3" />
                <propvalue name="VForce" value="1.275" />
                <propvalue name="IRange" value="100e-6" />
                <propvalue name="IClampL" value="-100e-6" />
                <propvalue name="IClampH" value="100e-6" />
                <propvalue name="Waittime" value="0.001" />
            </propvalues>
        </testclass>
    </test>
    <test name="BOOST_VOUTH" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.BOOST_VOUTH">
            <propvalues>
                <propvalue name="Measure_pinlist" value="VDDBOOST" />
                <propvalue name="WaitTime" value="0.001" />
                <propvalue name="SampleSize" value="3" />
                <propvalue name="IForce" value="100e-3" />
                <propvalue name="IRange" value="" />
                <propvalue name="IClampL" value="" />
                <propvalue name="IClampH" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="BOOST_VOUTHP" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.BOOST_VOUTHP">
            <propvalues>
                <propvalue name="Measure_pinlist" value="VDDBOOST" />
                <propvalue name="IForce" value="400e-3" />
                <propvalue name="Range" value="100e-3" />
                <propvalue name="VClampL" value="-2" />
                <propvalue name="VClampH" value="2" />
                <propvalue name="WaitTime" value="0.005" />
                <propvalue name="SampleSize" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="BOOST_VOUTL" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDL_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.BOOST_VOUTL">
            <propvalues>
                <propvalue name="Measure_pinlist" value="" />
                <propvalue name="WaitTime" value="" />
                <propvalue name="SampleSize" value="" />
                <propvalue name="IForce" value="" />
                <propvalue name="IRange" value="" />
                <propvalue name="IClampL" value="" />
                <propvalue name="IClampH" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="BOOST_PWRTHRU" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.BOOST_POWERON">
            <propvalues />
        </testclass>
    </test>
    <test name="CMU_TEST" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.CMU_TEST">
            <propvalues>
                <propvalue name="FREQ_pinlist" value="RXN" />
            </propvalues>
        </testclass>
    </test>
    <test name="MEMORY_TEST MODE 1" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.MEMORY_TEST">
            <propvalues />
        </testclass>
    </test>
    <test name="MEMORY_TEST MODE 2" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.MEMORY_TEST">
            <propvalues />
        </testclass>
    </test>
    <test name="MEMORY_TEST MODE 3" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.MEMORY_TEST">
            <propvalues />
        </testclass>
    </test>
    <test name="MEMORY_TEST MODE 4" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.MEMORY_TEST">
            <propvalues />
        </testclass>
    </test>
    <test name="MEMORY_TEST MODE 5" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.MEMORY_TEST">
            <propvalues />
        </testclass>
    </test>
    <test name="SSI_IO_TEST" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.SSI_IO_TEST">
            <propvalues>
                <propvalue name="Measure_pinlist" value="NFC_CLK_REQ,NFC_IC_ADDR0,NFC_IC_ADDR1,NFC_IC_SDA,RXN,RXP," />
                <propvalue name="H_IForce" value="-0.002" />
                <propvalue name="RangeH" value="2e-3" />
                <propvalue name="IClamphl" value="-0.002" />
                <propvalue name="IClamphh" value="0002" />
                <propvalue name="L_IForce" value="0.002" />
                <propvalue name="RangeL" value="2e-3" />
                <propvalue name="IClampll" value="-0002" />
                <propvalue name="IClamplh" value="0.002" />
                <propvalue name="SampleSize" value="16" />
            </propvalues>
        </testclass>
    </test>
    <test name="loadFW" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.loadFW">
            <propvalues />
        </testclass>
    </test>
    <test name="Reader_Init" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.Reader_Init">
            <propvalues />
        </testclass>
    </test>
    <test name="ADPLL_TEST" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.ADPLL_TEST">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TX_MODE" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_TX_MODE">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TX_TYPEA_106kbps_MI_100" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_TX_TYPEA_106kbps_MI_100">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TX_TYPEB_212kbps_MI_12" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_TX_TYPEB_212kbps_MI_12">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TX_TYPEB_848kbps_MI12" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_TX_TYPEB_848kbps_MI12">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TX_TYPEF_212kbps_MI12" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_TX_TYPEF_212kbps_MI12">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TX_TYPEF_424kbps_MI12" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_TX_TYPEF_424kbps_MI12">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TX_IDD_POWER" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_TX_IDD_POWER">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TX_IMPEDENCE_MIN" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_TX_IMPEDENCE_MIN">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TX_IMPEDENCE_MAX" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_TX_IMPEDENCE_MAX">
            <propvalues />
        </testclass>
    </test>
    <test name="Reader_RX_Init" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.Reader_RX_Init">
            <propvalues />
        </testclass>
    </test>
    <test name="Reader_RX_IDD" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.Reader_RX_IDD">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_SNR_THD3" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_RX_SNR_THD3">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_COURSE_GAIN4" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_RX_COURSE_GAIN">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_COURSE_GAIN3" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_RX_COURSE_GAIN">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_COURSE_GAIN2" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_RX_COURSE_GAIN">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_COURSE_GAIN1" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_RX_COURSE_GAIN">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_FINE_GAIN4" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_RX_FINE_GAIN">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_FINE_GAIN3" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_RX_FINE_GAIN">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_FINE_GAIN2" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_RX_FINE_GAIN">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_FINE_GAIN1" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_RX_FINE_GAIN">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RX_Driv_Invcom" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_RX_Driv_Invcom">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_SWP_S1_SWIO1" type="Test" timing="SWIO1_S1_CAP" level="VIHLR_VOHLR_IOHLR" pattern="SWIO1_S1_CAP" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_SWP_S1_SWIO">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_SWP_S2_SWIO1" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_SWP_S2SWIO1">
            <propvalues>
                <propvalue name="Measure_pinlist" value="NFC_SIM_SWIO2" />
                <propvalue name="WaitTime" value="10e-3" />
                <propvalue name="SampleSize" value="3" />
                <propvalue name="VForce" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="NFC_SWP_SWIO2" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_SWP_SWIO2">
            <propvalues>
                <propvalue name="Measure_pinlist" value="NFC_SIM_SWIO2" />
                <propvalue name="WaitTime" value="10e-3" />
                <propvalue name="SampleSize" value="3" />
                <propvalue name="VForce" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="NFC_SWP_S1_SWIO3" type="Test" timing="SWIO1_S1_CAP" level="VIHLR_VOHLR_IOHLR" pattern="SWIO3_S1_CAP" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_SWP_S1SWIO3">
            <propvalues>
                <propvalue name="Measure_pinlist" value="NFC_SIM_SWIO3" />
                <propvalue name="WaitTime" value="10e-3" />
                <propvalue name="SampleSize" value="3" />
                <propvalue name="IForce" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="NFC_SWP_S2_SWIO3" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_SWP_S2SWIO3">
            <propvalues>
                <propvalue name="Measure_pinlist" value="NFC_SIM_SWIO2" />
                <propvalue name="WaitTime" value="10e-3" />
                <propvalue name="SampleSize" value="3" />
                <propvalue name="VForce" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="CMU_TEST_19p2M" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.CMU_TEST_19p2M">
            <propvalues />
        </testclass>
    </test>
    <test name="ADPLL_TEST_27p12M" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.ADPLL_TEST_27p12M">
            <propvalues />
        </testclass>
    </test>
    <test name="CMU_TEST_27p12M" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
    <test name="ADPLL_TEST_19p2M" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.BOOT_UP">
            <propvalues />
        </testclass>
    </test>
    <test name="CMU_TEST_38p4M" type="Test" timing="RF_ADPLL_TEST" level="VIHLR_VOHLR_IOHLR" pattern="RF_ADPLL_TEST" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.BOOT_UP">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_RESET_MODE" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_RESET_MODE">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TAG_MODE" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_TAG_MODE">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TAG_CDR" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_TAG_CDR">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_FIELD_CLK_EXTRA" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_FIELD_CLK_EXTRA">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_TAG_NCDR" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_TAG_NCDR">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_FIELD_DET_HP" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_FIELD_DET">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_FIELD_DET_NP" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_FIELD_DET">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_FIELD_DET_LP" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_FIELD_DET">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOST_REG_SCAN" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.BOOST_REG_SCAN">
            <propvalues />
        </testclass>
    </test>
    <test name="BOOST_REG_SCAN_ZERO" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.BOOST_REG_SCAN_ZERO">
            <propvalues />
        </testclass>
    </test>
    <test name="EFUSE_FRC_BST" type="Test" timing="TIMING_OS" level="VIHLR_VOHLR_IOHLR" pattern="OS_FUNC" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.EFUSE_FRC_BST">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_ADC_108M" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_ADC_108M">
            <propvalues />
        </testclass>
    </test>
    <test name="NFC_DAC_216M" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.NFC_DAC_216M">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_VBAT2VDDIO" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.PMU_VBAT2VDDIO">
            <propvalues>
                <propvalue name="Measure_pinlist" value="" />
                <propvalue name="WaitTime" value="" />
                <propvalue name="SampleSize" value="" />
                <propvalue name="IForce" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="XO_CMU_TEST" type="Test" timing="TCXO_CTRL_OFF" level="VIHLR_VOHLR_IOHLR" pattern="TCXO_CTRL_OFF" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.XO_CMU_TEST">
            <propvalues />
        </testclass>
    </test>
    <test name="PMU_IDD_OFF_VDDN_STA" type="Test" timing="TCXO_CTRL_OFF" level="VIHLR_VOHLR_IOHLR" pattern="TCXO_CTRL_OFF" power="VDDN_VIHLR_VOHLR_IOHLR_TIM_NFC" comment="">
        <testclass name="libtestp_share2.PMU_IDDOFFVDDNSTA">
            <propvalues>
                <propvalue name="Measure_pinlist" value="VDDIO,VBAT,BOOST_LX" />
                <propvalue name="WaitTime" value="30e-3" />
                <propvalue name="SampleSize" value="3" />
            </propvalues>
        </testclass>
    </test>
    <test name="DFT_MODE" type="Test" timing="" level="VIHLR_VOHLR_IOHLR" pattern="" power="DFT_MODE_VDDN_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libtestp_share2.DFT_MODE">
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
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_JTAG_VDDL" type="Test" timing="DC_TIM6_V1" level="VIHLR_VOHLR_IOHLR" pattern="BSCAN_R01_HI1122" power="JTAG_VDDL_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_CHAIN_VDDH" type="Test" timing="CHAIN_TIM2_V1" level="VIHLR_VOHLR_IOHLR" pattern="CHAIN_R01_HI1122_ONECLK_BODY" power="CHAIN_VDDH_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_CHAIN_VDDL" type="Test" timing="CHAIN_TIM2_V1" level="VIHLR_VOHLR_IOHLR" pattern="CHAIN_R01_HI1122_ONECLK_BODY" power="CHAIN_VDDL_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_STUCKAT_VDDH" type="Test" timing="STUCK_TIM2_V1" level="VIHLR_VOHLR_IOHLR" pattern="STUCK_R01_HI1122_ONECLK_BODY" power="SA_VDDH_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_STUCKAT_VDDL" type="Test" timing="STUCK_TIM2_V1" level="VIHLR_VOHLR_IOHLR" pattern="STUCK_R01_HI1122_ONECLK_BODY" power="SA_VDDL_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_TRANS_VDDH" type="Test" timing="TRANS_TIM3_V1" level="VIHLR_VOHLR_IOHLR" pattern="TRANS_R03_HI1122_ONECLK_INIT" power="TRANS_VDDH_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_TRANS_VDDL" type="Test" timing="TRANS_TIM3_V1" level="VIHLR_VOHLR_IOHLR" pattern="TRANS_R03_HI1122_ONECLK_INIT" power="TRANS_VDDL_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_RAM_VDDH" type="Test" timing="MBIST_TIM4_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_PART1" power="MBIST_540ns_VDDH_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_RAM_VDDL" type="Test" timing="MBIST_TIM4_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_PART1" power="MBIST_540ns_VDDL_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_RAM_MINOR1_VDDH" type="Test" timing="MBIST_TIM4_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_PART1_MINOR1" power="MBIST_540ns_VDDH_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_RAM_MINOR1_VDDL" type="Test" timing="MBIST_TIM4_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_PART1_MINOR1" power="MBIST_540ns_VDDL_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_RAM_PLUS1_VDDH" type="Test" timing="MBIST_TIM4_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_PART1_PLUS1" power="MBIST_540ns_VDDH_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_RAM_PLUS1_VDDL" type="Test" timing="MBIST_TIM4_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_PART1_PLUS1" power="MBIST_540ns_VDDL_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_ROM_VDDH" type="Test" timing="MBIST_TIM5_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_ROM" power="MBIST_80ns_VDDH_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_ROM_VDDL" type="Test" timing="MBIST_TIM5_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_ROM" power="MBIST_80ns_VDDL_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_ROM_MINOR1_VDDH" type="Test" timing="MBIST_TIM5_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_ROM_MINOR1" power="MBIST_80ns_VDDH_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_ROM_MINOR1_VDDL" type="Test" timing="MBIST_TIM5_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_ROM_MINOR1" power="MBIST_80ns_VDDL_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_ROM_PLUS1_VDDH" type="Test" timing="MBIST_TIM5_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_ROM_PLUS1" power="MBIST_80ns_VDDH_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_MBIST_ROM_PLUS1_VDDL" type="Test" timing="MBIST_TIM5_V1" level="VIHLR_VOHLR_IOHLR" pattern="MBIST_R02_HI1122_ROM_PLUS1" power="MBIST_80ns_VDDL_VIHLR_VOHLR_IOHLR_CASE1" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_IDDQ" type="Test" timing="DC_IDDQ_TIM2_V1" level="VIHLR_VOHLR_IOHLR" pattern="IDDQ_R02_HI1122_ONECLK" power="IDDQ_20ns_VDDN_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="DC_IDDQ" type="Test" timing="DC_IDDQ_TIM2_V1" level="VIHLR_VOHLR_IOHLR" pattern="IDDQ_R02_HI1122_ONECLK" power="IDDQ_20ns_VDDN_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libtestp_share2.Basic_04_DC_IDDQ_Measure">
            <propvalues>
                <propvalue name="Measure_pinlist" value="" />
                <propvalue name="SampleSize" value="16" />
            </propvalues>
        </testclass>
    </test>
    <test name="FC_VIHL_VDDL" type="Test" timing="IOZ_TIM6_V1" level="VIHLS_VOHLR_IOHLR" pattern="VIHL_R01_HI1122_NO_PULL" power="DC_VDDL_VIHLS_VOHLR_IOHLR" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_VIHL_VDDH" type="Test" timing="IOZ_TIM6_V1" level="VIHLS_VOHLR_IOHLR" pattern="VIHL_R01_HI1122_NO_PULL" power="DC_VDDH_VIHLS_VOHLR_IOHLR" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_IOZ_VDDN" type="Test" timing="IOZ_TIM6_V1" level="VIHLR_VOHLR_IOHLS" pattern="IOZ_R01_HI1122" power="IOZ_VDDH_VIHLR_VOHLR_IOHLS" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="FC_VOHL_VDDL" type="Test" timing="IOZ_TIM6_V1" level="VIHLR_VOHLS_IOHLS" pattern="VOHL_R01_HI1122" power="DC_VDDL_VIHLR_VOHLS_IOHLS" comment="">
        <testclass name="libtestp_share2.Basic_01_Functional">
            <propvalues />
        </testclass>
    </test>
    <test name="DC_IIHL_PU_VDDH" type="Test" timing="IOZ_TIM6_V1" level="VIHLR_VOHLR_IOHLR" pattern="VIHL_R01_HI1122_PULL_DOWN" power="DC_VDDH_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libtestp_share2.DC_IIHL_VDDH">
            <propvalues />
        </testclass>
    </test>
    <test name="DC_IIHLPD_VDDH" type="Test" timing="DC_TIM6_V1" level="VIHLR_VOHLR_IOHLR" pattern="VIHL_R01_HI1122_PULL_DOWN" power="DC_VDDH_VIHLR_VOHLR_IOHLR" comment="">
        <testclass name="libtestp_share2.DC_IIHL_VDDH">
            <propvalues />
        </testclass>
    </test>
    <test name="DC_IOZ_VDDH" type="Test" timing="IOZ_TIM6_V1" level="VIHLR_VOHLR_IOHLS" pattern="IOZ_R01_HI1122" power="IOZ_VDDN_VIHLR_VOHLR_IOHLS" comment="">
        <testclass name="libtestp_share2.DC_IOZHL_3V3_VDDH">
            <propvalues>
                <propvalue name="Measure_pinlist" value="gDFTPINS," />
                <propvalue name="IOZH_VForce" value="1.98" />
                <propvalue name="RangeH" value="10e-6" />
                <propvalue name="IOZH_IClampL" value="-10e-6" />
                <propvalue name="IOZH_IClampH" value="10e-6" />
                <propvalue name="IOZL_VForce" value="0" />
                <propvalue name="RangeL" value="10e-6" />
                <propvalue name="IOZL_IClampL" value="-10e-6" />
                <propvalue name="IOZL_IClampH" value="10e-6" />
                <propvalue name="SampleSize" value="4" />
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
    <test name="OSD" type="Test" timing="" level="" pattern="" power="Power_OSD" comment="">
        <testclass name="libtestp_share2.power_osd">
            <propvalues>
                <propvalue name="powerpinlist" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="POWEROFFF" type="Test" timing="" level="" pattern="" power="" comment="">
        <testclass name="">
            <propvalues />
        </testclass>
    </test>
</tests>
