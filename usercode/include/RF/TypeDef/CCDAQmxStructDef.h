/* 
 * File:   CCDAQmxStructDef.h
 * Author: wengmenghao
 *
 * Created on 2020年8月29日, 下午3:07
 */
#pragma once
#ifndef CCDAQMXSTRUCTDEF_H
#define	CCDAQMXSTRUCTDEF_H

#include "CCResults.h"
#include "CCTesterDef.h"
#include "CCDAQmx.h"

#ifndef CCDAQ_STATUS
typedef ViStatus        CCDAQ_STATUS;
#endif
//

#ifndef CCDAQ_R_ERROR
#define CCDAQ_R_ERROR    (ViStatus(-1))
#endif

#define MAX_ERROR_DESCRIPTION (1024)
#define MAX_SAMPLE_NUM        (4096)

#define PI	              (3.1415926535)

/*- Values for attributes CCRFSG_ATTR_REF_CLOCK_SOURCE and CCRFSG_ATTR_PXI_CHASSIS_CLK10_SOURCE -*/
#define CCRFSA_VAL_ONBOARD_CLOCK_STR                    "OnboardClock"
#define CCRFSA_VAL_REF_IN_STR                           "RefIn"
#define CCRFSA_VAL_PXI_CLK_STR                          "PXI_CLK"
#define CCRFSA_VAL_NONE_STR                             "None"
#define CCRFSA_VAL_REF_IN_2_STR                         "RefIn2"
#define CCRFSA_VAL_PXI_CLK_MASTER_STR                   "PXI_ClkMaster"

#define DAQMX_VAL_GENCHAN_TYPE_ANALOG_VOLTAGE         (0)
#define DAQMX_VAL_GENCHAN_TYPE_ANALOG_CURRENT         (1)
#define DAQMX_VAL_GENCHAN_TYPE_ANALOG_FUNC            (2)
#define DAQMX_VAL_GENCHAN_TYPE_DIGIT                  (3)
#define DAQMX_VAL_GENCHAN_TYPE_COUNTER_FREG           (4)
#define DAQMX_VAL_GENCHAN_TYPE_COUNTER_TICK           (5)
#define DAQMX_VAL_GENCHAN_TYPE_COUNTER_TIME           (6)

#define DAQMX_VAL_ACQUISITION_TYPE_ANALOG_VOLTAGE     (0)

#define DAQMX_VAL_TIMMING_TYPE_SAMPLECLOCK            (0)

#define DAQMX_VAL_WAVEFORM_TYPE_SINE                  (0)
#define DAQMX_VAL_WAVEFORM_TYPE_TRIANGLE              (1)
#define DAQMX_VAL_WAVEFORM_TYPE_SQUARE                (2)
#define DAQMX_VAL_WAVEFORM_TYPE_SAWTOOTH              (3)

#define DAQMX_VAL_WRITEDATA_TYPE_ANALOG_F64           (0)
#define DAQMX_VAL_WRITEDATA_TYPE_ANALOG_SCALAR_F64    (1)

#define DAQMX_VAL_READDATA_TYPE_ANALOG_F64            (0)

/********************************************************************************************************************************************************/
/**************************************************Configuration Functions Struct************************************************************************/
/********************************************************************************************************************************************************/

typedef struct{
    /*The channels to add to the task.*/
    ViConstString szChannelNames;
}AddGlobalChansToTaskAttribute,*pAddGlobalChansToTaskAttribute;

typedef struct{
    /*The path to the TDMS file to which you want to log data.*/
    ViConstString szFilePath;
    /*Specifies whether to enable logging and whether to allow reading data while logging. 
     * Log mode allows for the best performance.
     * DAQmx_Val_Off  Disable logging for the task.
     * DAQmx_Val_Log  Enable logging for the task. You cannot read data using DAQmx Read when using this mode. If you require access to the data, read from the TDMS file. 
     * DAQmx_Val_LogAndRead  Enable both logging and reading data for the task. You must use DAQmx Read to read samples for NI-DAQmx to stream them to disk. */
    ViInt32 nLoggingMode;
    /*The name of the group to create within the TDMS file for data from this task. */
    ViConstString szGroupName;
    /*Specifies how to open the TDMS file.
     * DAQmx_Val_Open  Open an existing TDMS file, and append data to that file. If the file does not exist, NI-DAQmx returns an error.
     * DAQmx_Val_OpenOrCreate  Open an existing TDMS file, and append data to that file. If the file does not exist, NI-DAQmx creates a new TDMS file.
     * DAQmx_Val_CreateOrReplace  Create a new TDMS file, or replace an existing TDMS file. 
     * DAQmx_Val_Create  Create a new TDMS file. If the file already exists, NI-DAQmx returns an error. */
    ViInt32 nOperation;
}ConfigureLoggingAttribute,*pConfigureLoggingAttribute;

typedef struct{
    /*Indicates whether the measurement or generation completed.*/
    ViBoolean *bIsTaskDone;
}IsTaskDoneAttribute,*pIsTaskDoneAttribute;

typedef struct{
    /*The path to the TDMS file to which you want to log data.*/
    ViConstString szFilePath;
}StartNewFileAttribute,*pStartNewFileAttribute;

typedef struct{
    /*The maximum amount of time, in seconds, to wait for the measurement or generation to complete.*/
    ViReal64 dTimeToWait;
}WaitUntilTaskDoneAttribute,*pWaitUntilTaskDoneAttribute;

typedef struct{
    /*Use this parameter to set certain options. 
     * You can combine flags with the bitwise-OR operator ('|') to set multiple options. 
     * Pass a value of zero if no options need to be set.
     * 0  The callback function is called in a DAQmx thread. This is the default value.
     * DAQmx_Val_SynchronousEventCallbacks  The callback function is called in the thread which registered the event.  */
    ViUInt32 unOptions;
    /*The function that you want DAQmx to call when the event occurs.*/
    DAQmxDoneEventCallbackPtr callbackFunction;
    /*A value that you want DAQmx to pass to the callback function as the function data parameter.*/
    void *pCallbackData;
}RegisterDoneEventAttribute,*pRegisterDoneEventAttribute;

typedef struct{
    /*The type of event you want to receive.
     * DAQmx_Val_Acquired_Into_Buffer  This event type is only supported for input tasks.  
     * DAQmx_Val_Transferred_From_Buffer  This event type is only supported for output tasks.  */
    ViInt32 nEveryNsamplesEventType;
    /*The number of samples after which each event should occur.*/
    ViUInt32 unNSamples;
    /*Use this parameter to set certain options. 
     * You can combine flags with the bitwise-OR operator ('|') to set multiple options. 
     * Pass a value of zero if no options need to be set.
     * 0  The callback function is called in a DAQmx thread. This is the default value.
     * DAQmx_Val_SynchronousEventCallbacks  The callback function is called in the thread which registered the event.  */
    ViUInt32 unOptions;
    /*The function that you want DAQmx to call when the event occurs.*/
    DAQmxEveryNSamplesEventCallbackPtr callbackFunction;
    /*A value that you want DAQmx to pass to the callback function as the function data parameter.*/
    void *pCallbackData;
}RegisterEveryNSamplesEventAttribute,*pRegisterEveryNSamplesEventAttribute;

typedef struct{
    /*The signal for which you want to receive results.
     * DAQmx_Val_SampleClock  Sample clock 
     * DAQmx_Val_SampleCompleteEvent  Sample complete event 
     * DAQmx_Val_ChangeDetectionEvent  Change detection event 
     * DAQmx_Val_CounterOutputEvent  Counter output event */
    ViInt32 nSignalID;
    /*Use this parameter to set certain options. 
     * You can combine flags with the bitwise-OR operator ('|') to set multiple options. 
     * Pass a value of zero if no options need to be set.
     * 0  The callback function is called in a DAQmx thread. This is the default value.
     * DAQmx_Val_SynchronousEventCallbacks  The callback function is called in the thread which registered the event.  */
    ViUInt32 unOptions;
    /*The function that you want DAQmx to call when the event occurs.*/
    DAQmxSignalEventCallbackPtr callbackFunction;
    /*A value that you want DAQmx to pass to the callback function as the function data parameter.*/
    void *pCallbackData;
}RegisterSignalEventAttribute,*pRegisterSignalEventAttribute;

typedef struct{
    /*The Nth channel to return. The index starts at 1.*/
    ViUInt32 unIndex;
    /*The size, in bytes, of buffer. If you pass 0, this function returns the number of bytes needed to allocate.*/
    ViInt32 nBufferSize;
    /*Output:The Nth channel in the index. If you pass NULL, this function returns the number of bytes needed to allocate.*/
    ViChar *cBuffer;
}GetNthTaskChannelAttribute,*pGetNthTaskChannelAttribute;

typedef struct{
    /*The Nth channel to return. The index starts at 1.*/
    ViUInt32 unIndex;
    /*The size, in bytes, of buffer. If you pass 0, this function returns the number of bytes needed to allocate.*/
    ViInt32 nBufferSize;
    /*Output:The Nth channel in the index. If you pass NULL, this function returns the number of bytes needed to allocate.*/
    ViChar *cBuffer;
}GetNthTaskDeviceAttribute,*pGetNthTaskDeviceAttribute;

typedef struct{
    /*Specifies how to alter the task state.
     * DAQmx_Val_Task_Start  Starts execution of the task.
     * DAQmx_Val_Task_Stop  Stops execution of the task.
     * DAQmx_Val_Task_Verify  Verifies that all task parameters are valid for the hardware.
     * DAQmx_Val_Task_Commit  Programs the hardware as much as possible according to the task configuration. 
     * DAQmx_Val_Task_Reserve  Reserves the hardware resources needed for the task. No other tasks can reserve these same resources. 
     * DAQmx_Val_Task_Unreserve  Releases all previously reserved resources.
     * DAQmx_Val_Task_Abort  Abort is used to stop an operation, such as Read or Write, that is currently active.  */
    ViInt32 nAction;
}TaskControlAttribute,*pTaskControlAttribute;

typedef struct{
    /*Adds global virtual channels from MAX to the given task.*/
    AddGlobalChansToTaskAttribute AddGlobalChansToTask;
    /*Configures TDMS file logging for the task.*/
    ConfigureLoggingAttribute ConfigureLogging;
    /*Queries the status of the task and indicates if it completed execution.*/
    IsTaskDoneAttribute IsTaskDone;
    /*Starts a new TDMS file the next time data is written to disk.*/
    StartNewFileAttribute StartNewFile;
    /*Waits for the measurement or generation to complete. 
     * Use this function to ensure that the specified operation is complete before you stop the task.*/
    WaitUntilTaskDoneAttribute WaitUntilTaskDone;
    /*Registers a callback function to receive an event when a task stops due to an error or when a finite acquisition task or finite generation task completes execution.*/
    RegisterDoneEventAttribute RegisterDoneEvent;
    /*Registers a callback function to receive an event when the specified number of samples is written from the device to the buffer or from the buffer to the device.*/
    RegisterEveryNSamplesEventAttribute RegisterEveryNSamplesEvent;
    /*Registers a callback function to receive an event when the specified hardware event occurs.*/
    RegisterSignalEventAttribute RegisterSignalEvent;
    /*Returns the Nth channel. This function takes the taskHandle, index, and bufferSize you specify and returns the Nth channel.*/
    GetNthTaskChannelAttribute GetNthTaskChannel;
    /*Returns the Nth device. This function takes the taskHandle, index, and bufferSize you specify and returns the Nth device.*/
    GetNthTaskDeviceAttribute GetNthTaskDevice;
    /*Alters the state of a task according to the action you specify. 
     * To minimize the time required to start a task, for example, DAQmxTaskControl can commit the task prior to starting.*/
    TaskControlAttribute TaskControl;
}TaskConfigureAttribute,*pTaskConfigureAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s).*/
    ViConstString szNameToAssignToChannel;
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel.
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode 
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return acceleration measurements from the channel.
     * DAQmx_Val_AccelUnit_g  G-force (g). 1 g is approximately equal to 9.81 m/s2. 
     * DAQmx_Val_FromCustomScale  Units specified by a custom scale. Use customScaleName to specify a custom scale. */
    ViInt32 nUnits;
    /*The sensitivity of the sensor. 
     * This value is in the units you specify with the sensitivityUnits input. Refer to the sensor documentation to determine this value.*/
    ViReal64 dSensitivity;
    /*The units of sensitivity.
     * DAQmx_Val_mVoltsPerG  mVolts/g. 
     * DAQmx_Val_VoltsPerG  Volts/g. */
    ViInt32 nSensitivityUnits;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. 
     * DAQmx_Val_None  Supply no excitation to the channel.  */
    ViInt32 nCurrentExcitSource;
    /*The amount of excitation, in amperes, that the sensor requires.*/
    ViReal64 dCurrentExcitVal;
    /*The name of a custom scale to apply to the channel. */
    ViConstString szCustomScaleName;
}AIAccelChanAttribute,*pAIAccelChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViChar cNameToAssignToChannel;
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel.
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode 
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name. 
     * DAQmx_Val_g  Grams
     * DAQmx_Val_MetersPerSecondSquared  Meters per second squared 
     * DAQmx_Val_InchesPerSecondSquared  Inches per second squared */
    ViInt32 nUnits;
    /*The sensitivity of the sensor. This value is in the units you specify with the sensitivityUnits input. Refer to the sensor documentation to determine this value.*/
    ViReal64 dSensitivity;
    /*The units of sensitivity.
     * DAQmx_Val_mVoltsPerG  Millivolts per gram
     * DAQmx_Val_VoltsPerG  Volts per gram */
    ViInt32 nSensitivityUnits;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation.
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel.*/
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor. */
    ViReal64 dVoltageExcitVal;
    /*Whether the excitation voltage will be used to scale the returned data*/
    ViBoolean bUseExcitForScaling;
    /*The name of a custom scale to apply to the channel. 
     * To use this parameter, you must set units to DAQmx_Val_FromCustomScale. 
     * If you do not set units to DAQmx_Val_FromCustomScale, you must set customScaleName to NULL.*/
    ViConstString szCustomScaleName;
}AIAccel4WireDCVoltageChanAttribute,*pAIAccel4WireDCVoltageChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel. 
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode 
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_AccelUnit_g  Grams 
     * DAQmx_Val_MetersPerSecondSquared  Meters per second squared 
     * DAQmx_Val_InchesPerSecondSquared  Inches per second squared */
    ViInt32 nUnits;
    /*The sensitivity of the sensor.*/
    ViReal64 dSensitivity;
    /*The units of sensitivity.
     * DAQmx_Val_PicoCoulombsPerG  pCoulomb/g 
     * DAQmx_Val_PicoCoulombsPerMetersPerSecondSquared  pCoulomb/(m/s^2) 
     * DAQmx_Val_PicoCoulombsPerInchesPerSecondSquared  pCoulomb/(in/s^2) */
    ViInt32 nSensitivityUnits;
    /*The name of a custom scale to apply to the channel. 
     * To use this parameter, you must set units to DAQmx_Val_FromCustomScale.*/
    ViConstString szCustomScaleName;
}AIAccelChargeChanAttribute,*pAIAccelChargeChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*Specifies in which unit to return voltage ratios from the channel.
     * DAQmx_Val_VoltsPerVolt  volts per volt 
     * DAQmx_Val_mVoltsPerVolt  millivolts per volt 
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. Use customScaleName to specify a custom scale. */
    ViInt32 nUnits;
    /*Specifies the Wheatstone bridge configuration connected to the channel.
     * DAQmx_Val_FullBridge  Four active sensing elements in the bridge 
     * DAQmx_Val_HalfBridge  Two active sensing elements in the bridge 
     * DAQmx_Val_QuarterBridge  One active sensing element in the bridge */
    ViInt32 nBridgeConfig;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor.*/
    ViReal64 dVoltageExcitVal;
    /*Specifies in ohms the resistance of the bridge while not under load.*/
    ViReal64 dNominalBridgeResistance;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}AIBridgeChanAttribute,*pAIBridgeChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel.
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode 
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}AIChargeChanAttribute,*pAIChargeChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel.
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode 
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The location of the shunt resistor.
     * DAQmx_Val_Default  At run time, NI-DAQmx chooses the default shunt resistor location for the channel. 
     * DAQmx_Val_Internal  Use the built-in shunt resistor of the device. 
     * DAQmx_Val_External  Use a shunt resistor external to the device. */
    ViInt32 nShuntResistorLoc;
    /*The value, in ohms, of an external shunt resistor.*/
    ViReal64 dExtShuntResistorVal;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}AICurrentChanAttribute,*pAICurrentChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel.
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode 
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The location of the shunt resistor.
     * DAQmx_Val_Default  At run time, NI-DAQmx chooses the default shunt resistor location for the channel. 
     * DAQmx_Val_Internal  Use the built-in shunt resistor of the device. 
     * DAQmx_Val_External  Use a shunt resistor external to the device. */
    ViInt32 nShuntResistorLoc;
    /*The value, in ohms, of an external shunt resistor.*/
    ViReal64 dExtShuntResistorVal;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}AICurrentRMSChanAttribute,*pAICurrentRMSChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*Specifies the Wheatstone bridge configuration connected to the channel.
     * DAQmx_Val_FullBridge  Four active sensing elements in the bridge 
     * DAQmx_Val_HalfBridge  Two active sensing elements in the bridge 
     * DAQmx_Val_QuarterBridge  One active sensing element in the bridge */
    ViInt32 nBridgeConfig;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device.  
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor.*/
    ViReal64 dVoltageExcitVal;
    /*Specifies in ohms the resistance of the bridge while not under load.*/
    ViReal64 dNominalBridgeResistance;
    /*An array of coefficients for the polynomial that converts electrical values to physical values.*/
    const ViReal64 *dForwardCoeffs;
    /*The number of coefficients in the forwardCoeffs array.*/
    ViUInt32 unNumForwardCoeffs;
    /*An array of coefficients for the polynomial that converts physical values to electrical values. */
    const ViReal64 *dReverseCoeffs;
    /*The number of coefficients in the reverseCoeffs array.*/
    ViUInt32 unNumReverseCoeffs;
    /*Specifies from which electrical unit to scale data.
     * DAQmx_Val_VoltsPerVolt  volts per volt 
     * DAQmx_Val_mVoltsPerVolt  millivolts per volt */
    ViInt32 nElectricalUnits;
    /*Specifies to which physical units to scale electrical data.
     * DAQmx_Val_Newtons  newtons 
     * DAQmx_Val_Pounds  pounds
     * DAQmx_Val_KilogramForce  kilograms-force */
    ViInt32 nPhysicalUnits;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}AIForceBridgePolynomialChanAttribute,*pAIForceBridgePolynomialChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*Specifies the Wheatstone bridge configuration connected to the channel.
     * DAQmx_Val_FullBridge  Four active sensing elements in the bridge 
     * DAQmx_Val_HalfBridge  Two active sensing elements in the bridge 
     * DAQmx_Val_QuarterBridge  One active sensing element in the bridge */
    ViInt32 nBridgeConfig;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device.  
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor.*/
    ViReal64 dVoltageExcitVal;
    /*Specifies in ohms the resistance of the bridge while not under load.*/
    ViReal64 dNominalBridgeResistance;
    /*The array of electrical values that map to the values in physicalVals. */
    const ViReal64 *dElectricalVals;
    /*The number of electrical values in the electricalVals array.*/
    ViUInt32 unNumElectricalVals;
    /*Specifies from which electrical unit to scale data.
     * DAQmx_Val_VoltsPerVolt  volts per volt 
     * DAQmx_Val_mVoltsPerVolt  millivolts per volt */
    ViInt32 nElectricalUnits;
    /*The array of physical values that map to the values in electricalVals.*/
    const ViReal64 *dPhysicalVals;
    /*The number of physical values in the physicalVals array.*/
    ViUInt32 unNumPhysicalVals;
    /*Specifies to which physical units to scale electrical data.
     * DAQmx_Val_Newtons  newtons 
     * DAQmx_Val_Pounds  pounds
     * DAQmx_Val_KilogramForce  kilograms-force */
    ViInt32 nPhysicalUnits;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}AIForceBridgeTableChanAttribute,*pAIForceBridgeTableChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*Specifies the Wheatstone bridge configuration connected to the channel.
     * DAQmx_Val_FullBridge  Four active sensing elements in the bridge 
     * DAQmx_Val_HalfBridge  Two active sensing elements in the bridge 
     * DAQmx_Val_QuarterBridge  One active sensing element in the bridge */
    ViInt32 nBridgeConfig;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device.  
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor.*/
    ViReal64 dVoltageExcitVal;
    /*Specifies in ohms the resistance of the bridge while not under load.*/
    ViReal64 dNominalBridgeResistance;
    /*The first electrical value, corresponding to firstPhysicalVal.*/
    ViReal64 dFirstElectricalVal;
    /*The second electrical value, corresponding to secondPhysicalVal. */
    ViReal64 dSecondElectricalVal;
    /*Specifies from which electrical unit to scale data.
     * DAQmx_Val_VoltsPerVolt  volts per volt 
     * DAQmx_Val_mVoltsPerVolt  millivolts per volt */
    ViInt32 nElectricalUnits;
    /*The first physical value, corresponding to firstElectricalVal. */
    ViReal64 dFirstPhysicalVal;
    /*The second physical value, corresponding to secondElectricalValue.*/
    ViReal64 dSecondPhysicalVal;
    /*Specifies to which physical units to scale electrical data.
     * DAQmx_Val_Newtons  newtons 
     * DAQmx_Val_Pounds  pounds
     * DAQmx_Val_KilogramForce  kilograms-force */
    ViInt32 nPhysicalUnits;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}AIForceBridgeTwoPointLinChanAttribute,*pAIForceBridgeTwoPointLinChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel. 
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode 
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The sensitivity of the sensor. This value is in the units you specify with the sensitivityUnits input.*/
    ViReal64 dSensitivity;
    /*The units of sensitivity input.
     * DAQmx_Val_mVoltsPerNewton  millivolts per newton 
     * DAQmx_Val_mVoltsPerPound  millivolts per pound */
    ViInt32 nSensitivityUnits;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device.  
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device.  
     * DAQmx_Val_None  Supply no excitation to the channel.  */
    ViInt32 nCurrentExcitSource;
    /*The amount of excitation, in amperes, that the sensor requires.*/
    ViReal64 dCurrentExcitVal;
    /*The name of a custom scale to apply to the channel. */
    ViConstString szCustomScaleName;
}AIForceIEPEChanAttribute,*pAIForceIEPEChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The voltage level at which to recognize waveform repetitions.*/
    ViReal64 dThresholdLevel;
    /*Specifies in volts a window below thresholdLevel.*/
    ViReal64 dHysteresis;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}AIFreqVoltageChanAttribute,*pAIFreqVoltageChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel. 
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode 
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The units to use to return sound pressure measurements.
     * DAQmx_Val_Pascals  pascals 
     * DAQmx_Val_FromCustomScale  Units specified by a custom scale. Use customScaleName to specify a custom scale. */
    ViInt32 nUnits;
    /*ViReal64 The sensitivity of the microphone. Specify this value in millivolts per pascal. */
    ViReal64 dMicSensitivity;
    /*ViReal64 The maximum instantaneous sound pressure level you expect to measure. This value is in decibels, referenced to 20 micropascals. */
    ViReal64 dMaxSndPressLevel;
    /*ViInt32 The source of excitation. 
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. You must use currentExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. You must use currentExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. You cannot use this value if the sensor requires excitation. */
    ViInt32 nCurrentExcitSource;
    /*The amount of excitation, in amperes, that the sensor requires.*/
    ViReal64 dCurrentExcitVal;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}AIMicrophoneChanAttribute,*pAIMicrophoneChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*Specifies the Wheatstone bridge configuration connected to the channel.
     * DAQmx_Val_FullBridge  Four active sensing elements in the bridge 
     * DAQmx_Val_HalfBridge  Two active sensing elements in the bridge 
     * DAQmx_Val_QuarterBridge  One active sensing element in the bridge */
    ViInt32 nBridgeConfig;
    /*The source of excitation. 
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor.*/
    ViReal64 dVoltageExcitVal;
    /*Specifies in ohms the resistance of the bridge while not under load.*/
    ViReal64 dNominalBridgeResistance;
    /*An array of coefficients for the polynomial that converts electrical values to physical values. */
    const ViReal64 *dForwardCoeffs;
    /*The number of coefficients in the forwardCoeffs array.*/
    ViUInt32 unNumForwardCoeffs;
    /*An array of coefficients for the polynomial that converts physical values to electrical values.*/
    const ViReal64 *dReverseCoeffs;
    /*The number of coefficients in the reverseCoeffs array.*/
    ViUInt32 unNumReverseCoeffs;
    /*Specifies from which electrical unit to scale data. 
     * DAQmx_Val_VoltsPerVolt  volts per volt 
     * DAQmx_Val_mVoltsPerVolt  millivolts per volt */
    ViInt32 nElectricalUnits;
    /*Specifies to which physical unit to scale electrical data.
     * DAQmx_Val_PoundsPerSquareInch  pounds per square inch 
     * DAQmx_Val_Bar  bar 
     * DAQmx_Val_Pascals  pascals */
    ViInt32 nPhysicalUnits;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}AIPressureBridgePolynomialChanAttribute,*pAIPressureBridgePolynomialChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*Specifies the Wheatstone bridge configuration connected to the channel.
     * DAQmx_Val_FullBridge  Four active sensing elements in the bridge 
     * DAQmx_Val_HalfBridge  Two active sensing elements in the bridge 
     * DAQmx_Val_QuarterBridge  One active sensing element in the bridge */
    ViInt32 nBridgeConfig;
    /*The source of excitation. 
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor.*/
    ViReal64 dVoltageExcitVal;
    /*Specifies in ohms the resistance of the bridge while not under load.*/
    ViReal64 dNominalBridgeResistance;
    /*The array of electrical values that map to the values in physicalVals. */
    const ViReal64 *dElectricalVals;
    /*The number of electrical values in the electricalVals array.*/
    ViUInt32 unNumElectricalVals;
    /*Specifies from which electrical unit to scale data. 
     * DAQmx_Val_VoltsPerVolt  volts per volt 
     * DAQmx_Val_mVoltsPerVolt  millivolts per volt */
    ViInt32 nElectricalUnits;
    /*The array of physical values that map to the values in electricalVals. */
    const ViReal64 *dPhysicalVals;
    /*The number of physical values in the physicalVals array.*/
    ViUInt32 unNumPhysicalVals;
    /*Specifies to which physical unit to scale electrical data.
     * DAQmx_Val_PoundsPerSquareInch  pounds per square inch 
     * DAQmx_Val_Bar  bar 
     * DAQmx_Val_Pascals  pascals */
    ViInt32 nPhysicalUnits;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}AIPressureBridgeTableChanAttribute,*pAIPressureBridgeTableChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*Specifies the Wheatstone bridge configuration connected to the channel.
     * DAQmx_Val_FullBridge  Four active sensing elements in the bridge 
     * DAQmx_Val_HalfBridge  Two active sensing elements in the bridge 
     * DAQmx_Val_QuarterBridge  One active sensing element in the bridge */
    ViInt32 nBridgeConfig;
    /*The source of excitation. 
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor.*/
    ViReal64 dVoltageExcitVal;
    /*Specifies in ohms the resistance of the bridge while not under load.*/
    ViReal64 dNominalBridgeResistance;
    /*The first electrical value, corresponding to firstPhysicalVal. */
    ViReal64 dFirstElectricalVal;
    /*The second electrical value, corresponding to secondPhysicalVal. */
    ViReal64 dSecondElectricalVal;
    /*Specifies from which electrical unit to scale data.
     * DAQmx_Val_VoltsPerVolt  volts per volt 
     * DAQmx_Val_mVoltsPerVolt  millivolts per volt */
    ViInt32 nElectricalUnits;
    /*The first physical value, corresponding to firstElectricalVal.*/
    ViReal64 dFirstPhysicalVal;
    /*The second physical value, corresponding to secondElectricalValue. */
    ViReal64 dSecondPhysicalVal;
    /*Specifies to which physical unit to scale electrical data.
     * DAQmx_Val_PoundsPerSquareInch  pounds per square inch 
     * DAQmx_Val_Bar  bar 
     * DAQmx_Val_Pascals  pascals */
    ViInt32 nPhysicalUnits;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}AIPressureBridgeTwoPointLinChanAttribute,*pAIPressureBridgeTwoPointLinChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The configuration for resistance measurements.
     * DAQmx_Val_2Wire  2-wire mode. 
     * DAQmx_Val_3Wire  3-wire mode. 
     * DAQmx_Val_4Wire  4-wire mode. */
    ViInt32 nResistanceConfig;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. You must use currentExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. You must use currentExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. You cannot use this value if the sensor requires excitation. */
    ViInt32 nCurrentExcitSource;
    /*The amount of excitation, in amperes, that the sensor requires.*/
    ViReal64 dCurrentExcitVal;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}AIResistanceChanAttribute,*pAIResistanceChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*Specifies the type of the rosette.
     * DAQmx_Val_RectangularRosette  A rectangular rosette consists of three strain gages, each separated by a 45 degree angle. 
     * DAQmx_Val_DeltaRosette  A delta rosette consists of three strain gages, each separated by a 60 degree angle. 
     * DAQmx_Val_TeeRosette  A tee rosette consists of two strain gages oriented at 90 degrees with respect to each other. */
    ViInt32 nRosetteType;
    /*Specifies, in degrees, the orientation of the gage with respect to the preferred X axis.*/
    ViReal64 dGageOrientation;
    /*Specifies the virtual channels to create for the rosette measurements.
     * DAQmx_Val_PrincipalStrain1  The maximum tensile strain coplanar to the surface of the material under stress. 
     * DAQmx_Val_PrincipalStrain2  The minimum tensile strain coplanar to the surface of the material under stress. 
     * DAQmx_Val_PrincipalStrainAngle  The angle, in degrees, at which the principal strains of the rosette occur with respect to the preferred X axis. 
     * DAQmx_Val_CartesianStrainX  The tensile strain coplanar to the surface of the material under stress in the X coordinate direction. 
     * DAQmx_Val_CartesianStrainY  The tensile strain coplanar to the surface of the material under stress in the Y coordinate direction.
     * DAQmx_Val_CartesianShearStrainXY  The strain coplanar to the cross section of the material under stress in the XY coordinate direction. 
     * DAQmx_Val_MaxShearStrain  The maximum strain coplanar to the cross section of the material under stress. 
     * DAQmx_Val_MaxShearStrainAngle  The angle, in degrees, at which the maximum shear strain of the rosette occurs with respect to the preferred X axis. */
    const ViInt32 *nRosetteMeasTypes;
    /*Specifies the number of virtual channels used in rosetteMeasTypes.*/
    ViUInt32 unNumRosetteMeasTypes;
    /*The strain gage bridge configuration.
     * DAQmx_Val_FullBridgeI  Four active gages with two pairs subjected to equal and opposite strains. 
     * DAQmx_Val_FullBridgeII  Four active gages with two aligned with maximum principal strain and two Poisson gages in adjacent arms. 
     * DAQmx_Val_FullBridgeIII  Four active gages with two aligned with maximum principal strain and two Poisson gages in opposite arms. 
     * DAQmx_Val_HalfBridgeI  Two active gages with one aligned with maximum principal strain and one Poisson gage. 
     * DAQmx_Val_HalfBridgeII  Two active gages with equal and opposite strains. 
     * DAQmx_Val_QuarterBridgeI  Single active gage. 
     * DAQmx_Val_QuarterBridgeII  Single active gage and one dummy gage. */
    ViInt32 nStrainConfig;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor. */
    ViReal64 dVoltageExcitVal;
    /*The sensitivity of the strain gages and relates the change in electrical resistance to the change in strain. */
    ViReal64 dGageFactor;
    /*The resistance, in ohms, of the gages in an unstrained position. */
    ViReal64 dNominalGageResistance;
    /*The ratio of lateral strain to axial strain in the material in which you measure strain.*/
    ViReal64 dPoissonRatio;
    /*The amount, in ohms, of resistance in the lead wires. Ideally, this value is the same for all leads. */
    ViReal64 dLeadWireResistance;
}AIRosetteStrainGageChanAttribute,*pAIRosetteStrainGageChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*ViInt32 The type of RTD connected to the channel. 
     * DAQmx_Val_Pt3750 Pt3750 
     * DAQmx_Val_Pt3851 Pt3851 
     * DAQmx_Val_Pt3911 Pt3911 
     * DAQmx_Val_Pt3916 Pt3916 
     * DAQmx_Val_Pt3920 Pt3920 
     * DAQmx_Val_Pt3928 Pt3928 
     * DAQmx_Val_Custom You must specify the 'A', 'B', and 'C' constants for the Callendar-Van Dusen equation */
    ViInt32 nRtdType;
    /*The configuration for resistance measurements.
     * DAQmx_Val_2Wire  2-wire mode. 
     * DAQmx_Val_3Wire  3-wire mode. 
     * DAQmx_Val_4Wire  4-wire mode. */
    ViInt32 nResistanceConfig;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. You must use currentExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. You must use currentExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. You cannot use this value if the sensor requires excitation. */
    ViInt32 nCurrentExcitSource;
    /*The amount of excitation, in amperes, that the sensor requires.*/
    ViReal64 dCurrentExcitVal;
    /*The sensor resistance in ohms at 0 deg C for the Callendar-Van Dusen equation Refer to the sensor documentation to determine this value.*/
    ViReal64 dR0;
}AIRTDChanAttribute,*pAIRTDChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The strain gage bridge configuration.
     * DAQmx_Val_FullBridgeI  Four active gages with two pairs subjected to equal and opposite strains. 
     * DAQmx_Val_FullBridgeII  Four active gages with two aligned with maximum principal strain and two Poisson gages in adjacent arms. 
     * DAQmx_Val_FullBridgeIII  Four active gages with two aligned with maximum principal strain and two Poisson gages in opposite arms. 
     * DAQmx_Val_HalfBridgeI  Two active gages with one aligned with maximum principal strain and one Poisson gage. 
     * DAQmx_Val_HalfBridgeII  Two active gages with equal and opposite strains. 
     * DAQmx_Val_QuarterBridgeI  Single active gage. 
     * DAQmx_Val_QuarterBridgeII  Single active gage and one dummy gage. */
    ViInt32 nStrainConfig;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor. */
    ViReal64 dVoltageExcitVal;
    /*The sensitivity of the strain gages and relates the change in electrical resistance to the change in strain. */
    ViReal64 dGageFactor;
    /*The bridge output voltage in the unloaded condition. 
     * NI-DAQmx subtracts this value from any measurements before applying scaling equations. */
    ViReal64 dInitialBridgeVoltage;
    /*The resistance, in ohms, of the gages in an unstrained position. 
     * Each gage in the bridge must have the same nominal gage resistance. */
    ViReal64 dNominalGageResistance;
    /*The ratio of lateral strain to axial strain in the material in which you measure strain.*/
    ViReal64 dPoissonRatio;
    /*The amount, in ohms, of resistance in the lead wires. Ideally, this value is the same for all leads.*/
    ViReal64 dLeadWireResistance;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}AIStrainGageChanAttribute,*pAIStrainGageChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
}AITempBuiltInSensorChanAttribute,*pAITempBuiltInSensorChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The type of thermocouple connected to the channel.
     * DAQmx_Val_J_Type_TC  J-type thermocouple. 
     * DAQmx_Val_K_Type_TC  K-type thermocouple.
     * DAQmx_Val_N_Type_TC  N-type thermocouple. 
     * DAQmx_Val_R_Type_TC  R-type thermocouple. 
     * DAQmx_Val_S_Type_TC  S-type thermocouple. 
     * DAQmx_Val_T_Type_TC  T-type thermocouple. 
     * DAQmx_Val_B_Type_TC  B-type thermocouple. 
     * DAQmx_Val_E_Type_TC  E-type thermocouple. */
    ViInt32 nThermocoupleType;
    /*The source of cold junction compensation.
     * DAQmx_Val_BuiltIn  Use a cold-junction compensation channel built into the terminal block.
     * DAQmx_Val_ConstVal  You must specify the cold-junction temperature. 
     * DAQmx_Val_Chan  Use a channel for cold-junction compensation. */
    ViInt32 nCjcSource;
    /*The temperature of the cold junction of the thermocouple if you set cjcSource to DAQmx_Val_ConstVal.*/
    ViReal64 dCjcVal;
    /*The channel that acquires the temperature of the thermocouple cold-junction if you set cjcSource to DAQmx_Val_Chan.*/
    ViConstString szCjcChannel;
}AIThrmcplChanAttribute,*pAIThrmcplChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The configuration for resistance measurements.
     * DAQmx_Val_2Wire  2-wire mode. 
     * DAQmx_Val_3Wire  3-wire mode. 
     * DAQmx_Val_4Wire  4-wire mode. */
    ViInt32 nResistanceConfig;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. You must use currentExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. You must use currentExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. You cannot use this value if the sensor requires excitation. */
    ViInt32 nCurrentExcitSource;
    /*The amount of excitation, in amperes, that the sensor requires.*/
    ViReal64 dCurrentExcitVal;
    /*The A constant from the Steinhart-Hart thermistor equation.*/
    ViReal64 dA;
    /*The B constant from the Steinhart-Hart thermistor equation.*/
    ViReal64 dB;
    /*The C constant from the Steinhart-Hart thermistor equation.*/
    ViReal64 dC;
}AIThrmstrChanIexAttribute,*pAIThrmstrChanIexAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The configuration for resistance measurements.
     * DAQmx_Val_2Wire  2-wire mode. 
     * DAQmx_Val_3Wire  3-wire mode. 
     * DAQmx_Val_4Wire  4-wire mode. */
    ViInt32 nResistanceConfig;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor. Refer to the sensor documentation to determine appropriate excitation values.*/
    ViReal64 dVoltageExcitVal;
    /*The A constant from the Steinhart-Hart thermistor equation.*/
    ViReal64 dA;
    /*The B constant from the Steinhart-Hart thermistor equation.*/
    ViReal64 dB;
    /*The C constant from the Steinhart-Hart thermistor equation.*/
    ViReal64 dC;
    /*The value, in ohms, of the reference resistor.*/
    ViReal64 dR1;
}AIThrmstrChanVexAttribute,*pAIThrmstrChanVexAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*Specifies the Wheatstone bridge configuration connected to the channel.
     * DAQmx_Val_FullBridge  Four active sensing elements in the bridge 
     * DAQmx_Val_HalfBridge  Two active sensing elements in the bridge 
     * DAQmx_Val_QuarterBridge  One active sensing element in the bridge */
    ViInt32 nBridgeConfig;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor. Refer to the sensor documentation to determine appropriate excitation values.*/
    ViReal64 dVoltageExcitVal;
    /*Specifies in ohms the resistance of the bridge while not under load.*/
    ViReal64 dNominalBridgeResistance;
    /*An array of coefficients for the polynomial that converts electrical values to physical values. */
    const ViReal64 *dForwardCoeffs;
    /*The number of coefficients in the forwardCoeffs array.*/
    ViUInt32 unNumForwardCoeffs;
    /*An array of coefficients for the polynomial that converts physical values to electrical values.*/
    const ViReal64 *dReverseCoeffs;
    /*The number of coefficients in the reverseCoeffs array.*/
    ViUInt32 unNumReverseCoeffs;
    /*Specifies from which electrical unit to scale data.
     * DAQmx_Val_VoltsPerVolt  volts per volt 
     * DAQmx_Val_mVoltsPerVolt  millivolts per volt */
    ViInt32 nElectricalUnits;
    /*Specifies to which physical units to scale electrical data.
     * DAQmx_Val_NewtonMeters  newton meters 
     * DAQmx_Val_InchOunces  ounce-inches 
     * DAQmx_Val_InchPounds  pound-inches 
     * DAQmx_Val_FootPounds  pound-feet */
    ViInt32 nPhysicalUnits;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}AITorqueBridgePolynomialChanAttribute,*pAITorqueBridgePolynomialChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*Specifies the Wheatstone bridge configuration connected to the channel.
     * DAQmx_Val_FullBridge  Four active sensing elements in the bridge 
     * DAQmx_Val_HalfBridge  Two active sensing elements in the bridge 
     * DAQmx_Val_QuarterBridge  One active sensing element in the bridge */
    ViInt32 nBridgeConfig;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor. Refer to the sensor documentation to determine appropriate excitation values.*/
    ViReal64 dVoltageExcitVal;
    /*Specifies in ohms the resistance of the bridge while not under load.*/
    ViReal64 dNominalBridgeResistance;
    /*The array of electrical values that map to the values in physicalVals. Specify this value in the unit indicated by electricalUnits.*/
    const ViReal64 *dElectricalVals;
    /*The number of electrical values in the electricalVals array.*/
    ViUInt32 unNumElectricalVals;
    /*Specifies from which electrical unit to scale data. Select the same unit that the sensor data sheet or calibration certificate uses for electrical values.
     * DAQmx_Val_VoltsPerVolt  volts per volt 
     * DAQmx_Val_mVoltsPerVolt  millivolts per volt */
    ViInt32 nElectricalUnits;
    /*The array of physical values that map to the values in electricalVals. Specify this value in the unit indicated by physicalUnits.*/
    const ViReal64 *dPhysicalVals;
    /*The number of physical values in the physicalVals array.*/
    ViUInt32 unNumPhysicalVals;
    /*Specifies to which physical units to scale electrical data.
     * DAQmx_Val_NewtonMeters  newton meters 
     * DAQmx_Val_InchOunces  ounce-inches 
     * DAQmx_Val_InchPounds  pound-inches 
     * DAQmx_Val_FootPounds  pound-feet */
    ViInt32 nPhysicalUnits;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}AITorqueBridgeTableChanAttribute,*pAITorqueBridgeTableChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*Specifies the Wheatstone bridge configuration connected to the channel.
     * DAQmx_Val_FullBridge  Four active sensing elements in the bridge 
     * DAQmx_Val_HalfBridge  Two active sensing elements in the bridge 
     * DAQmx_Val_QuarterBridge  One active sensing element in the bridge */
    ViInt32 nBridgeConfig;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor. Refer to the sensor documentation to determine appropriate excitation values.*/
    ViReal64 dVoltageExcitVal;
    /*Specifies in ohms the resistance of the bridge while not under load.*/
    ViReal64 dNominalBridgeResistance;
    /*The first electrical value, corresponding to firstPhysicalVal. */
    ViReal64 dFirstElectricalVal;
    /*The second electrical value, corresponding to secondPhysicalVal.*/
    ViReal64 dSecondElectricalVal;
    /*Specifies from which electrical unit to scale data.
     * DAQmx_Val_VoltsPerVolt  volts per volt 
     * DAQmx_Val_mVoltsPerVolt  millivolts per volt */
    ViInt32 nElectricalUnits;
    /*The first physical value, corresponding to firstElectricalVal.*/
    ViReal64 dFirstPhysicalVal;
    /*The second physical value, corresponding to secondElectricalValue.*/
    ViReal64 dSecondPhysicalVal;
    /*Specifies to which physical units to scale electrical data.
     * DAQmx_Val_NewtonMeters  newton meters 
     * DAQmx_Val_InchOunces  ounce-inches 
     * DAQmx_Val_InchPounds  pound-inches 
     * DAQmx_Val_FootPounds  pound-feet */
    ViInt32 nPhysicalUnits;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}AITorqueBridgeTwoPointLinChanAttribute,*pAITorqueBridgeTwoPointLinChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel. 
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode 
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The sensitivity of the sensor. This value is in the units you specify with the sensitivityUnits input.*/
    ViReal64 dSensitivity;
    /*The units of sensitivity.
     * DAQmx_Val_MillivoltsPerMillimeterPerSecond  mVolts/mm/s.
     * DAQmx_Val_MilliVoltsPerInchPerSecond  mVolts/in/s. */
    ViInt32 nSensitivityUnits;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. You must use currentExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. You must use currentExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. You cannot use this value if the sensor requires excitation. */
    ViInt32 nCurrentExcitSource;
    /*The amount of excitation, in amperes, that the sensor requires.*/
    ViReal64 dCurrentExcitVal;
    /*The name of a custom scale to apply to the channel. To use this parameter, you must set units to DAQmx_Val_FromCustomScale. */
    ViConstString szCustomScaleName;
}AIVelocityIEPEChanAttribute,*pAIVelocityIEPEChanAttribute;

typedef struct{
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel. 
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode 
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The name of a custom scale to apply to the channel. To use this parameter, you must set units to DAQmx_Val_FromCustomScale. */
    ViConstString szCustomScaleName;
}AIVoltageChanAttribute,*pAIVoltageChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel. 
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode 
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The name of a custom scale to apply to the channel. To use this parameter, you must set units to DAQmx_Val_FromCustomScale. */
    ViConstString szCustomScaleName;
}AIVoltageRMSChanAttribute,*pAIVoltageRMSChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel. 
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode 
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*Specifies in which unit to return voltage ratios from the channel.
     * DAQmx_Val_VoltsPerVolt  volts per volt 
     * DAQmx_Val_mVoltsPerVolt  millivolts per volt 
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. Use customScaleName to specify a custom scale. */
    ViInt32 nUnits;
    /*Specifies the Wheatstone bridge configuration connected to the channel.
     * DAQmx_Val_FullBridge  Four active sensing elements in the bridge 
     * DAQmx_Val_HalfBridge  Two active sensing elements in the bridge 
     * DAQmx_Val_QuarterBridge  One active sensing element in the bridge */
    ViInt32 nBridgeConfig;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor.*/
    ViReal64 dVoltageExcitVal;
    /*Specifies whether NI-DAQmx divides the measurement by the excitation. */
    ViBoolean bUseExcitForScaling;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}AIVoltageChanWithExcitAttribute,*pAIVoltageChanWithExcitAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The sensitivity of the sensor. This value is in the units you specify with the sensitivityUnits input.*/
    ViReal64 dSensitivity;
    /*The units of sensitivity.
     * DAQmx_Val_mVoltsPerMil  mVolts/mil 
     * DAQmx_Val_VoltsPerMil  Volts/mil 
     * DAQmx_Val_mVoltsPerMillimeter  mVolts/mMeter 
     * DAQmx_Val_VoltsPerMillimeter  Volts/mMeter 
     * DAQmx_Val_mVoltsPerMicron  mVolts/micron */
    ViInt32 nSensitivityUnits;
    /*The name of a custom scale to apply to the channel. To use this parameter, you must set units to DAQmx_Val_FromCustomScale. */
    ViConstString szCustomScaleName;
}AIPosEddyCurrProxProbeChanAttribute,*pAIPosEddyCurrProxProbeChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The sensitivity of the sensor. This value is in the units you specify with the sensitivityUnits input.*/
    ViReal64 dSensitivity;
    /*The units of sensitivity.
     * DAQmx_Val_mVoltsPerMil  mVolts/mil 
     * DAQmx_Val_VoltsPerMil  Volts/mil 
     * DAQmx_Val_mVoltsPerMillimeter  mVolts/mMeter 
     * DAQmx_Val_VoltsPerMillimeter  Volts/mMeter 
     * DAQmx_Val_mVoltsPerMicron  mVolts/micron */
    ViInt32 nSensitivityUnits;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation.
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel.*/
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor. */
    ViReal64 dVoltageExcitVal;
    /*The excitation frequency, in hertz, that the sensor requires. Refer to the sensor documentation to determine this value. */
    ViReal64 dVoltageExcitFreq;
    /*The number of leads on the sensor. Some sensors may require you to tie leads together to create a 4-wire, 5-wire, or 6-wire sensor.
     * DAQmx_Val_4Wire  4-wire. 
     * DAQmx_Val_5Wire  5-wire. 
     * DAQmx_Val_6Wire  6-wire. */
    ViInt32 nACExcitWireMode;
    /*The name of a custom scale to apply to the channel. To use this parameter, you must set units to DAQmx_Val_FromCustomScale. */
    ViConstString szCustomScaleName;
}AIPosLVDTChanAttribute,*pAIPosLVDTChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The sensitivity of the sensor. This value is in the units you specify with the sensitivityUnits input.*/
    ViReal64 dSensitivity;
    /*The units of sensitivity.
     * DAQmx_Val_mVoltsPerMil  mVolts/mil 
     * DAQmx_Val_VoltsPerMil  Volts/mil 
     * DAQmx_Val_mVoltsPerMillimeter  mVolts/mMeter 
     * DAQmx_Val_VoltsPerMillimeter  Volts/mMeter 
     * DAQmx_Val_mVoltsPerMicron  mVolts/micron */
    ViInt32 nSensitivityUnits;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation.
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel.*/
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor. */
    ViReal64 dVoltageExcitVal;
    /*The excitation frequency, in hertz, that the sensor requires. Refer to the sensor documentation to determine this value. */
    ViReal64 dVoltageExcitFreq;
    /*The number of leads on the sensor. Some sensors may require you to tie leads together to create a 4-wire, 5-wire, or 6-wire sensor.
     * DAQmx_Val_4Wire  4-wire. 
     * DAQmx_Val_5Wire  5-wire. 
     * DAQmx_Val_6Wire  6-wire. */
    ViInt32 nACExcitWireMode;
    /*The name of a custom scale to apply to the channel. To use this parameter, you must set units to DAQmx_Val_FromCustomScale. */
    ViConstString szCustomScaleName;
}AIPosRVDTChanAttribute,*pAIPosRVDTChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s).*/
    ViConstString szNameToAssignToChannel;
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel.
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode 
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return acceleration measurements from the channel.
     * DAQmx_Val_AccelUnit_g  G-force (g). 1 g is approximately equal to 9.81 m/s2. 
     * DAQmx_Val_FromCustomScale  Units specified by a custom scale. Use customScaleName to specify a custom scale. */
    ViInt32 nUnits;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. 
     * DAQmx_Val_None  Supply no excitation to the channel.  */
    ViInt32 nCurrentExcitSource;
    /*The amount of excitation, in amperes, that the sensor requires.*/
    ViReal64 dCurrentExcitVal;
    /*The name of a custom scale to apply to the channel. */
    ViConstString szCustomScaleName;
}TEDSAIAccelChanAttribute,*pTEDSAIAccelChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel.
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode 
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The location of the shunt resistor.
     * DAQmx_Val_Default  At run time, NI-DAQmx chooses the default shunt resistor location for the channel. 
     * DAQmx_Val_Internal  Use the built-in shunt resistor of the device. 
     * DAQmx_Val_External  Use a shunt resistor external to the device. */
    ViInt32 nShuntResistorLoc;
    /*The value, in ohms, of an external shunt resistor.*/
    ViReal64 dExtShuntResistorVal;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}TEDSAICurrentChanAttribute,*pTEDSAICurrentChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*Specifies in which unit to return voltage ratios from the channel.
     * DAQmx_Val_VoltsPerVolt  volts per volt 
     * DAQmx_Val_mVoltsPerVolt  millivolts per volt 
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. Use customScaleName to specify a custom scale. */
    ViInt32 nUnits;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor.*/
    ViReal64 dVoltageExcitVal;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}TEDSAIBridgeChanAttribute,*pTEDSAIBridgeChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*Specifies in which unit to return voltage ratios from the channel.
     * DAQmx_Val_VoltsPerVolt  volts per volt 
     * DAQmx_Val_mVoltsPerVolt  millivolts per volt 
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. Use customScaleName to specify a custom scale. */
    ViInt32 nUnits;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor.*/
    ViReal64 dVoltageExcitVal;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}TEDSAIForceBridgeChanAttribute,*pTEDSAIForceBridgeChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel. 
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode 
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device.  
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device.  
     * DAQmx_Val_None  Supply no excitation to the channel.  */
    ViInt32 nCurrentExcitSource;
    /*The amount of excitation, in amperes, that the sensor requires.*/
    ViReal64 dCurrentExcitVal;
    /*The name of a custom scale to apply to the channel. */
    ViConstString szCustomScaleName;
}TEDSAIForceIEPEChanAttribute,*pTEDSAIForceIEPEChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel. 
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode 
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The units to use to return sound pressure measurements.
     * DAQmx_Val_Pascals  pascals 
     * DAQmx_Val_FromCustomScale  Units specified by a custom scale. Use customScaleName to specify a custom scale. */
    ViInt32 nUnits;
    /*ViReal64 The maximum instantaneous sound pressure level you expect to measure. This value is in decibels, referenced to 20 micropascals. */
    ViReal64 dMaxSndPressLevel;
    /*ViInt32 The source of excitation. 
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. You must use currentExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. You must use currentExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. You cannot use this value if the sensor requires excitation. */
    ViInt32 nCurrentExcitSource;
    /*The amount of excitation, in amperes, that the sensor requires.*/
    ViReal64 dCurrentExcitVal;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}TEDSAIMicrophoneChanAttribute,*pTEDSAIMicrophoneChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*Specifies in which unit to return voltage ratios from the channel.
     * DAQmx_Val_VoltsPerVolt  volts per volt 
     * DAQmx_Val_mVoltsPerVolt  millivolts per volt 
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. Use customScaleName to specify a custom scale. */
    ViInt32 nUnits;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor.*/
    ViReal64 dVoltageExcitVal;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}TEDSAIPressureBridgeChanAttribute,*pTEDSAIPressureBridgeChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The configuration for resistance measurements.
     * DAQmx_Val_2Wire  2-wire mode. 
     * DAQmx_Val_3Wire  3-wire mode. 
     * DAQmx_Val_4Wire  4-wire mode. */
    ViInt32 nResistanceConfig;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. You must use currentExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. You must use currentExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. You cannot use this value if the sensor requires excitation. */
    ViInt32 nCurrentExcitSource;
    /*The amount of excitation, in amperes, that the sensor requires.*/
    ViReal64 dCurrentExcitVal;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}TEDSAIResistanceChanAttribute,*pTEDSAIResistanceChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The configuration for resistance measurements.
     * DAQmx_Val_2Wire  2-wire mode. 
     * DAQmx_Val_3Wire  3-wire mode. 
     * DAQmx_Val_4Wire  4-wire mode. */
    ViInt32 nResistanceConfig;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. You must use currentExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. You must use currentExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. You cannot use this value if the sensor requires excitation. */
    ViInt32 nCurrentExcitSource;
    /*The amount of excitation, in amperes, that the sensor requires.*/
    ViReal64 dCurrentExcitVal;
}TEDSAIRTDChanAttribute,*pTEDSAIRTDChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor. */
    ViReal64 dVoltageExcitVal;
    /*The bridge output voltage in the unloaded condition. NI-DAQmx subtracts this value from any measurements before applying scaling equations.*/
    ViReal64 dInitialBridgeVoltage;
    /*The amount, in ohms, of resistance in the lead wires. Ideally, this value is the same for all leads.*/
    ViReal64 dLeadWireResistance;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}TEDSAIStrainGageChanAttribute,*pTEDSAIStrainGageChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The source of cold junction compensation.
     * DAQmx_Val_BuiltIn  Use a cold-junction compensation channel built into the terminal block. 
     * DAQmx_Val_ConstVal  You must specify the cold-junction temperature. 
     * DAQmx_Val_Chan  Use a channel for cold-junction compensation. */
    ViInt32 nCjcSource;
    /*The temperature of the cold junction of the thermocouple if you set cjcSource to DAQmx_Val_ConstVal.*/
    ViReal64 dCjcVal;
    /*The channel that acquires the temperature of the thermocouple cold-junction if you set cjcSource to DAQmx_Val_Chan.*/
    ViConstString szCjcChannel;
}TEDSAIThrmcplChanAttribute,*pTEDSAIThrmcplChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The configuration for resistance measurements.
     * DAQmx_Val_2Wire  2-wire mode. 
     * DAQmx_Val_3Wire  3-wire mode. 
     * DAQmx_Val_4Wire  4-wire mode. */
    ViInt32 nResistanceConfig;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. You must use currentExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. You must use currentExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. You cannot use this value if the sensor requires excitation. */
    ViInt32 nCurrentExcitSource;
    /*The amount of excitation, in amperes, that the sensor requires.*/
    ViReal64 dCurrentExcitVal;
}TEDSAIThrmstrChanIexAttribute,*pTEDSAIThrmstrChanIexAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The configuration for resistance measurements.
     * DAQmx_Val_2Wire  2-wire mode. 
     * DAQmx_Val_3Wire  3-wire mode. 
     * DAQmx_Val_4Wire  4-wire mode. */
    ViInt32 nResistanceConfig;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor. Refer to the sensor documentation to determine appropriate excitation values.*/
    ViReal64 dVoltageExcitVal;
    /*The value, in ohms, of the reference resistor.*/
    ViReal64 dR1;
}TEDSAIThrmstrChanVexAttribute,*pTEDSAIThrmstrChanVexAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor. Refer to the sensor documentation to determine appropriate excitation values.*/
    ViReal64 dVoltageExcitVal;
    /*The name of a custom scale to apply to the channel. To use this parameter, you must set units to DAQmx_Val_FromCustomScale.*/
    ViConstString szCustomScaleName;
}TEDSAITorqueBridgeChanAttribute,*pTEDSAITorqueBridgeChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel. 
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The name of a custom scale to apply to the channel. To use this parameter, you must set units to DAQmx_Val_FromCustomScale.*/
    ViConstString szCustomScaleName;
}TEDSAIVoltageChanAttribute,*pTEDSAIVoltageChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel. 
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel. */
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor. Refer to the sensor documentation to determine appropriate excitation values.*/
    ViReal64 dVoltageExcitVal;
    /*The name of a custom scale to apply to the channel. To use this parameter, you must set units to DAQmx_Val_FromCustomScale.*/
    ViConstString szCustomScaleName;
}TEDSAIVoltageChanWithExcitAttribute,*pTEDSAIVoltageChanWithExcitAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation.
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel.*/
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor. */
    ViReal64 dVoltageExcitVal;
    /*The excitation frequency, in hertz, that the sensor requires. Refer to the sensor documentation to determine this value. */
    ViReal64 dVoltageExcitFreq;
    /*The number of leads on the sensor. Some sensors may require you to tie leads together to create a 4-wire, 5-wire, or 6-wire sensor.
     * DAQmx_Val_4Wire  4-wire. 
     * DAQmx_Val_5Wire  5-wire. 
     * DAQmx_Val_6Wire  6-wire. */
    ViInt32 nACExcitWireMode;
    /*The name of a custom scale to apply to the channel. To use this parameter, you must set units to DAQmx_Val_FromCustomScale. */
    ViConstString szCustomScaleName;
}TEDSAIPosLVDTChanAttribute,*pTEDSAIPosLVDTChanAttribute;

typedef struct{
    /*The names of the physical channels to use to create virtual channels.*/
    ViConstString szPhysicalChannel;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The source of excitation.
     * DAQmx_Val_Internal  Use the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation.
     * DAQmx_Val_External  Use an excitation source other than the built-in excitation source of the device. If you select this value, you must use voltageExcitVal to specify the amount of excitation. 
     * DAQmx_Val_None  Supply no excitation to the channel.*/
    ViInt32 nVoltageExcitSource;
    /*Specifies in volts the amount of excitation supplied to the sensor. */
    ViReal64 dVoltageExcitVal;
    /*The excitation frequency, in hertz, that the sensor requires. Refer to the sensor documentation to determine this value. */
    ViReal64 dVoltageExcitFreq;
    /*The number of leads on the sensor. Some sensors may require you to tie leads together to create a 4-wire, 5-wire, or 6-wire sensor.
     * DAQmx_Val_4Wire  4-wire. 
     * DAQmx_Val_5Wire  5-wire. 
     * DAQmx_Val_6Wire  6-wire. */
    ViInt32 nACExcitWireMode;
    /*The name of a custom scale to apply to the channel. To use this parameter, you must set units to DAQmx_Val_FromCustomScale. */
    ViConstString szCustomScaleName;
}TEDSAIPosRVDTChanAttribute,*pTEDSAIPosRVDTChanAttribute;

typedef struct{
//    /*The names of the physical channels to use to create virtual channels.*/
//    ViConstString szPhysicalChannel;
//    /*The name(s) to assign to the created virtual channel(s). */
//    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*The units to use to return from the channel.
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies. If you select this value, you must specify a custom scale name.
     * DAQmx_Val_Coulombs  Coulombs 
     * DAQmx_Val_PicoCoulombs  Picocoulombs */
    ViInt32 nUnits;
    /*The name of a custom scale to apply to the channel.*/
    ViConstString szCustomScaleName;
}AOVIGenChanAttribute,*pAOVIGenChanAttribute;

typedef struct{
    /*Specifies the kind of waveform to generate.
     * DAQmx_Val_Sine  Sine wave 
     * DAQmx_Val_Triangle  Triangle wave 
     * DAQmx_Val_Square  Sawtooth wave 
     * DAQmx_Val_Sawtooth  Square wave */
    ViInt32 nType;
    /*The frequency of the waveform to generate in hertz.*/
    ViReal64 dFrequency;
    /*The zero-to-peak amplitude of the waveform to generate in volts. Zero and negative values are valid.*/
    ViReal64 dAmplitude;
    /*The voltage offset of the waveform to generate.*/
    ViReal64 dOffset;
}AOFuncGenChanAttribute,*pAOFuncGenChanAttribute;

typedef struct{
    /*The names of the digital lines used to create a virtual channel. You can specify a list or range of lines.*/
    ViConstString szLines;
    /*The name of the created virtual channel(s). If you create multiple virtual channels with one call to this function, you can specify a list of names separated by commas.*/
    ViConstString szNameToAssignToLines;
    /*Specifies whether to group digital lines into one or more virtual channels. 
     * DAQmx_Val_ChanPerLine  One channel for each line 
     * DAQmx_Val_ChanForAllLines  One channel for all lines */
    ViInt32 nLineGrouping;
}DIChanAttribute,*pDIChanAttribute;

typedef struct{
    /*Specifies whether to group digital lines into one or more virtual channels. 
     * DAQmx_Val_ChanPerLine  One channel for each line 
     * DAQmx_Val_ChanForAllLines  One channel for all lines */
    ViInt32 nLineGrouping;
}DOChanAttribute,*pDOChanAttribute;

typedef struct{
    /*The name of the counter to use to create virtual channels.*/
    ViConstString szCounter;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*Specifies how to count and interpret the pulses that the encoder generates on signal A and signal B. */
    ViInt32 nDecodingType;
    /*Specifies in which unit to return velocity measurements from the channel.
     * DAQmx_Val_RPM  Revolutions per minute.
     * DAQmx_Val_RadiansPerSecond  Radians per second. 
     * DAQmx_Val_DegreesPerSecond  Degrees per second. 
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies.  */
    ViInt32 nUnits;
    /*The number of pulses the encoder generates per revolution.*/
    ViUInt32 unPulsesPerRev;
    /*The name of a custom scale to apply to the channel. */
    ViConstString szCustomScaleName;
}CIAngVelocityChanAttribute,*pCIAngVelocityChanAttribute;

typedef struct{
    /*The name of the counter to use to create virtual channels.*/
    ViConstString szCounter;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*Specifies on which edges of the input signal to increment or decrement the count.
     * DAQmx_Val_Rising  Rising edge(s). 
     * DAQmx_Val_Falling  Falling edge(s). */
    ViInt32 nEdge;
    /*The value from which to start counting.*/
    ViUInt32 unInitialCount;
    /*Specifies whether to increment or decrement the counter on each edge.
     * DAQmx_Val_CountUp  Increment the count register on each edge. 
     * DAQmx_Val_CountDown  Decrement the count register on each edge. 
     * DAQmx_Val_ExtControlled  The state of a digital line controls the count direction.  */
    ViInt32 nCountDirection;
}CICountEdgesChanAttribute,*pCICountEdgesChanAttribute;

typedef struct{
    /*The name of the counter to use to create virtual channels.*/
    ViConstString szCounter;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum frequency you expect to measure.*/
    ViReal64 dMinFreq;
    /*The maximum frequency you expect to measure.*/
    ViReal64 dMaxFreq;
    /*Specifies on which edges of the input signal to increment or decrement the count.
     * DAQmx_Val_Rising  Rising edge(s). 
     * DAQmx_Val_Falling  Falling edge(s). */
    ViInt32 nEdge;
    /*The name of a custom scale to apply to the channel. */
    ViConstString szCustomScaleName;
}CIDutyCycleChanAttribute,*pCIDutyCycleChanAttribute;

typedef struct{
    /*The name of the counter to use to create virtual channels.*/
    ViConstString szCounter;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*Specifies in which unit to return velocity measurements from the channel.
     * DAQmx_Val_RPM  Revolutions per minute.
     * DAQmx_Val_RadiansPerSecond  Radians per second. 
     * DAQmx_Val_DegreesPerSecond  Degrees per second. 
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies.  */
    ViInt32 nUnits;
    /*Specifies on which edges of the input signal to increment or decrement the count.
     * DAQmx_Val_Rising  Rising edge(s). 
     * DAQmx_Val_Falling  Falling edge(s). */
    ViInt32 nEdge;
    /*The method used to calculate the period or frequency of the signal.
     * DAQmx_Val_LowFreq1Ctr  Use one counter that uses a constant timebase to measure the input signal. 
     * DAQmx_Val_HighFreq2Ctr  Use two counters, one of which counts pulses of the signal to measure during the specified measurement time.
     * DAQmx_Val_LargeRng2Ctr  Use one counter to divide the frequency of the input signal to create a lower-frequency signal that the second counter can more easily measure. */
    ViInt32 nMeasMethod;
    /*The length of time to measure the frequency or period of a digital signal, when measMethod is DAQmx_Val_HighFreq2Ctr. */
    ViReal64 dMeasTime;
    /*The value by which to divide the input signal, when measMethod is DAQmx_Val_LargeRng2Ctr. */
    ViUInt32 unDivisor;
    /*The name of a custom scale to apply to the channel. */
    ViConstString szCustomScaleName;
}CIFreqChanAttribute,*pCIFreqChanAttribute;

typedef struct{
    /*The name of the counter to use to create virtual channels.*/
    ViConstString szCounter;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*Specifies how to count and interpret the pulses that the encoder generates on signal A and signal B. */
    ViInt32 nDecodingType;
    /*Specifies in which unit to return velocity measurements from the channel.
     * DAQmx_Val_RPM  Revolutions per minute.
     * DAQmx_Val_RadiansPerSecond  Radians per second. 
     * DAQmx_Val_DegreesPerSecond  Degrees per second. 
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies.  */
    ViInt32 nUnits;
    /*The distance to measure for each pulse the encoder generates on signal A or signal B. */
    ViReal64 dDistPerPulse;
    /*The name of a custom scale to apply to the channel. */
    ViConstString szCustomScaleName;
}CILinVelocityChanAttribute,*pCILinVelocityChanAttribute;

typedef struct{
    /*The name of the counter to use to create virtual channels.*/
    ViConstString szCounter;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*Specifies in which unit to return velocity measurements from the channel.
     * DAQmx_Val_RPM  Revolutions per minute.
     * DAQmx_Val_RadiansPerSecond  Radians per second. 
     * DAQmx_Val_DegreesPerSecond  Degrees per second. 
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies.  */
    ViInt32 nUnits;
    /*Specifies between which edges to measure the frequency or period of the signal.
     * DAQmx_Val_Rising  Rising edge(s). 
     * DAQmx_Val_Falling  Falling edge(s). */
    ViInt32 nEdge;
    /*Specifies the method used to calculate the frequency or period of the signal.
     * DAQmx_Val_LowFreq1Ctr  Use one counter that uses a constant timebase to measure the input signal. 
     * DAQmx_Val_HighFreq2Ctr  Use two counters, one of which counts pulses of the signal to measure during the specified measurement time. 
     * DAQmx_Val_LargeRng2Ctr  Use one counter to divide the frequency of the input signal to create a lower-frequency signal that the second counter can more easily measure. */
    ViInt32 nMeasMethod;
    /*The length of time to measure the frequency or period of a digital signal, when measMethod is DAQmx_Val_HighFreq2Ctr.*/
    ViReal64 dMeasTime;
    /*The value by which to divide the input signal, when measMethod is DAQmx_Val_LargeRng2Ctr. */
    ViUInt32 unDivisor;
    /*The name of a custom scale to apply to the channel. */
    ViConstString szCustomScaleName;
}CIPeriodChanAttribute,*pCIPeriodChanAttribute;

typedef struct{
    /*The name of the counter to use to create virtual channels.*/
    ViConstString szCounter;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*Specifies in which unit to return velocity measurements from the channel.
     * DAQmx_Val_RPM  Revolutions per minute.
     * DAQmx_Val_RadiansPerSecond  Radians per second. 
     * DAQmx_Val_DegreesPerSecond  Degrees per second. 
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies.  */
    ViInt32 nUnits;
}CIPulseChanFreqAttribute,*pCIPulseChanFreqAttribute;

typedef struct{
    /*The name of the counter to use to create virtual channels.*/
    ViConstString szCounter;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The originating terminal of the route. You can specify a terminal name.*/
    ViConstString szSourceTerminal;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
}CIPulseChanTicksAttribute,*pCIPulseChanTicksAttribute;

typedef struct{
    /*The name of the counter to use to create virtual channels.*/
    ViConstString szCounter;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*Specifies in which unit to return velocity measurements from the channel.
     * DAQmx_Val_RPM  Revolutions per minute.
     * DAQmx_Val_RadiansPerSecond  Radians per second. 
     * DAQmx_Val_DegreesPerSecond  Degrees per second. 
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies.  */
    ViInt32 nUnits;
}CIPulseChanTimeAttribute,*pCIPulseChanTimeAttribute;

typedef struct{
    /*The name of the counter to use to create virtual channels.*/
    ViConstString szCounter;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*Specifies in which unit to return velocity measurements from the channel.
     * DAQmx_Val_RPM  Revolutions per minute.
     * DAQmx_Val_RadiansPerSecond  Radians per second. 
     * DAQmx_Val_DegreesPerSecond  Degrees per second. 
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies.  */
    ViInt32 nUnits;
    /*Specifies on which edge to begin measuring pulse width.
     * DAQmx_Val_Rising  Rising edge(s).
     * DAQmx_Val_Falling  Falling edge(s). */
    ViInt32 nStartingEdge;
    /*The name of a custom scale to apply to the channel. */
    ViConstString szCustomScaleName;
}CIPulseWidthChanAttribute,*pCIPulseWidthChanAttribute;

typedef struct{
    /*The name of the counter to use to create virtual channels.*/
    ViConstString szCounter;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*Specifies in which unit to return velocity measurements from the channel.
     * DAQmx_Val_RPM  Revolutions per minute.
     * DAQmx_Val_RadiansPerSecond  Radians per second. 
     * DAQmx_Val_DegreesPerSecond  Degrees per second. 
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies.  */
    ViInt32 nUnits;
    /*The name of a custom scale to apply to the channel. */
    ViConstString szCustomScaleName;
}CISemiPeriodChanAttribute,*pCISemiPeriodChanAttribute;

typedef struct{
    /*The name of the counter to use to create virtual channels.*/
    ViConstString szCounter;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The minimum value, in units, that you expect to measure.*/
    ViReal64 dMinVal;
    /*The maximum value, in units, that you expect to measure.*/
    ViReal64 dMaxVal;
    /*Specifies in which unit to return velocity measurements from the channel.
     * DAQmx_Val_RPM  Revolutions per minute.
     * DAQmx_Val_RadiansPerSecond  Radians per second. 
     * DAQmx_Val_DegreesPerSecond  Degrees per second. 
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies.  */
    ViInt32 nUnits;
    /*Specifies on which edge of the first signal to start each measurement.
     * DAQmx_Val_Rising  Start each measurement on the rising edge of the first signal. 
     * DAQmx_Val_Falling  Start each measurement on the falling edge of the first signal. */
    ViInt32 nFirstEdge;
    /*Specifies on which edge of the first signal to stop each measurement.
     * DAQmx_Val_Rising  Stop each measurement on the rising edge of the second signal.
     * DAQmx_Val_Falling  Stop each measurement on the falling edge of the second signal. */
    ViInt32 nSecondEdge;
    /*The name of a custom scale to apply to the channel. */
    ViConstString szCustomScaleName;
}CITwoEdgeSepChanAttribute,*pCITwoEdgeSepChanAttribute;

typedef struct{
    /*The name of the counter to use to create virtual channels.*/
    ViConstString szCounter;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*Specifies how to count and interpret the pulses that the encoder generates on signal A and signal B. 
     * DAQmx_Val_X1  If signal A leads signal B, count the rising edges of signal A. If signal B leads signal A, count the falling edges of signal A.
     * DAQmx_Val_X2  Count the rising and falling edges of signal A. 
     * DAQmx_Val_X4  Count the rising and falling edges of both signal A and signal B. 
     * DAQmx_Val_TwoPulseCounting  Increment the count on rising edges of signal A. Decrement the count on rising pulses of signal B. */
    ViInt32 nDecodingType;
    /*Specifies whether to enable z indexing for the measurement.*/
    ViBoolean bZidxEnable;
    /*The value, in units, to which to reset the measurement when signal Z is high and signal A and signal B are at the states you specify with ZidxPhase.*/
    ViReal64 dZidxVal;
    /*The states at which signal A and signal B must be while signal Z is high for NI-DAQmx to reset the measurement. 
     * DAQmx_Val_AHighBHigh  Reset the measurement when both signal A and signal B are at high logic. 
     * DAQmx_Val_AHighBLow  Reset the measurement when signal A is at high logic and signal B is at low logic. 
     * DAQmx_Val_ALowBHigh  Reset the measurement when signal A is at low logic and signal B is at high logic. 
     * DAQmx_Val_ALowBLow  Reset the measurement when both signal A and signal B are at low logic. */
    ViInt32 nZidxPhase;
    /*The units to use to return linear position measurements from the channel.
     * DAQmx_Val_Meters  Meters. 
     * DAQmx_Val_Inches  Inches. 
     * DAQmx_Val_Ticks  Timebase Ticks. 
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies.  */
    ViInt32 nUnits;
    /*The distance measured for each pulse the encoder generates.*/
    ViReal64 dDistPerPulse;
    /*The position of the encoder when the measurement begins. */
    ViReal64 dInitialPos;
    /*The name of a custom scale to apply to the channel. */
    ViConstString szCustomScaleName;
}CILinEncoderChanAttribute,*pCILinEncoderChanAttribute;

typedef struct{
    /*The name of the counter to use to create virtual channels.*/
    ViConstString szCounter;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*Specifies how to count and interpret the pulses that the encoder generates on signal A and signal B. 
     * DAQmx_Val_X1  If signal A leads signal B, count the rising edges of signal A. If signal B leads signal A, count the falling edges of signal A.
     * DAQmx_Val_X2  Count the rising and falling edges of signal A. 
     * DAQmx_Val_X4  Count the rising and falling edges of both signal A and signal B. 
     * DAQmx_Val_TwoPulseCounting  Increment the count on rising edges of signal A. Decrement the count on rising pulses of signal B. */
    ViInt32 nDecodingType;
    /*Specifies whether to enable z indexing for the measurement.*/
    ViBoolean bZidxEnable;
    /*The value, in units, to which to reset the measurement when signal Z is high and signal A and signal B are at the states you specify with ZidxPhase.*/
    ViReal64 dZidxVal;
    /*The states at which signal A and signal B must be while signal Z is high for NI-DAQmx to reset the measurement. 
     * DAQmx_Val_AHighBHigh  Reset the measurement when both signal A and signal B are at high logic. 
     * DAQmx_Val_AHighBLow  Reset the measurement when signal A is at high logic and signal B is at low logic. 
     * DAQmx_Val_ALowBHigh  Reset the measurement when signal A is at low logic and signal B is at high logic. 
     * DAQmx_Val_ALowBLow  Reset the measurement when both signal A and signal B are at low logic. */
    ViInt32 nZidxPhase;
    /*The units to use to return linear position measurements from the channel.
     * DAQmx_Val_Meters  Meters. 
     * DAQmx_Val_Inches  Inches. 
     * DAQmx_Val_Ticks  Timebase Ticks. 
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies.  */
    ViInt32 nUnits;
    /*The number of pulses the encoder generates per revolution. */
    ViUInt32 unPulsesPerRev;
    /*The starting angle of the encoder when the measurement begins.*/
    ViReal64 dInitialAngle;
    /*The name of a custom scale to apply to the channel. */
    ViConstString szCustomScaleName;
}CIAngEncoderChanAttribute,*pCIAngEncoderChanAttribute;

typedef struct{
    /*The name of the counter to use to create virtual channels.*/
    ViConstString szCounter;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The units to use to return linear position measurements from the channel.
     * DAQmx_Val_Meters  Meters. 
     * DAQmx_Val_Inches  Inches. 
     * DAQmx_Val_Ticks  Timebase Ticks. 
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies.  */
    ViInt32 nUnits;
    /*The method to use to synchronize the counter to a GPS receiver.
     * DAQmx_Val_IRIGB  IRIG-B 
     * DAQmx_Val_PPS  PPS 
     * DAQmx_Val_None  None */
    ViInt32 nGpsSyncMethod;
    /*The name of a custom scale to apply to the channel. */
    ViConstString szCustomScaleName;
}CIGPSTimestampChanAttribute,*pCIGPSTimestampChanAttribute;

typedef struct{
    /*The units to use to return linear position measurements from the channel.
     * DAQmx_Val_Meters  Meters. 
     * DAQmx_Val_Inches  Inches. 
     * DAQmx_Val_Ticks  Timebase Ticks. 
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies.  */
    ViInt32 nUnits;
    /*The resting state of the output terminal.
     * DAQmx_Val_High  High state. 
     * DAQmx_Val_Low  Low state.*/
    ViInt32 nIdleState;
    /*The amount of time in seconds to wait before generating the first pulse.*/
    ViReal64 dInitialDelay;
    /*The frequency at which to generate pulses.*/
    ViReal64 dFreq;
    /*The width of the pulse divided by the pulse period. */
    ViReal64 dDutyCycle;
}COPulseChanFreqAttribute,*pCOPulseChanFreqAttribute;

typedef struct{
    /*The name of the counter to use to create virtual channels.*/
    ViConstString szCounter;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The terminal to which you connect an external timebase. */
    ViConstString szSourceTerminal;
    /*The resting state of the output terminal.
     * DAQmx_Val_High  High state. 
     * DAQmx_Val_Low  Low state. */
    ViInt32 nIdleState;
    /*The number of timebase ticks to wait before generating the first pulse.*/
    ViInt32 nInitialDelay;
    /*The number of timebase ticks that the pulse is low.*/
    ViInt32 nLowTicks;
    /*The number of timebase ticks that the pulse is high.*/
    ViInt32 nHighTicks;
}COPulseChanTicksAttribute,*pCOPulseChanTicksAttribute;

typedef struct{/*The name of the counter to use to create virtual channels.*/
    ViConstString szCounter;
    /*The name(s) to assign to the created virtual channel(s). */
    ViConstString szNameToAssignToChannel;
    /*The units to use to return linear position measurements from the channel.
     * DAQmx_Val_Meters  Meters. 
     * DAQmx_Val_Inches  Inches. 
     * DAQmx_Val_Ticks  Timebase Ticks. 
     * DAQmx_Val_FromCustomScale  Units a custom scale specifies.  */
    ViInt32 nUnits;
    /*The resting state of the output terminal.
     * DAQmx_Val_High  High state. 
     * DAQmx_Val_Low  Low state. */
    ViInt32 nIdleState;
    /*The number of timebase ticks to wait before generating the first pulse.*/
    ViInt32 nInitialDelay;
    /*The amount of time the pulse is low, in seconds.*/
    ViReal64 dLowTime;
    /*The amount of time the pulse is high, in seconds.*/
    ViReal64 dHighTime;
}COPulseChanTimeAttribute,*pCOPulseChanTimeAttribute;

typedef struct{
    ViInt16 GenChanType;
    //The name of a custom scale to apply to the channel.
    ViChar* pszCustomScaleName;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////Create Analog Input /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*Creates channel(s) that use an accelerometer to measure acceleration and adds the channel(s) to the task you specify with taskHandle.*/
    AIAccelChanAttribute AIAccelChan;
    /*Creates channel(s) to measure acceleration.*/
    AIAccel4WireDCVoltageChanAttribute AIAccel4WireDCVoltageChan;
    /*Creates channel(s) that use a ViCharge-based sensor to measure acceleration.*/
    AIAccelChargeChanAttribute AIAccelChargeChan;
    /*Creates channel(s) that measure voltage ratios from a Wheatstone bridge.*/
    AIBridgeChanAttribute AIBridgeChan;
    /*Creates channel(s) that use a sensor with ViCharge output.*/
    AIChargeChanAttribute AIChargeChan;
    /*Creates channel(s) for current measurement and adds the channel(s) to the task you specify with taskHandle.*/
    AICurrentChanAttribute AICurrentChan;
    /*Creates channel(s) for RMS current measurement and adds the channel(s) to the task you specify with taskHandle.*/
    AICurrentRMSChanAttribute AICurrentRMSChan;
    /*Creates channel(s) that use a Wheatstone bridge to measure force or load.*/
    AIForceBridgePolynomialChanAttribute AIForceBridgePolynomialChan;
    /*Creates channel(s) that use a Wheatstone bridge to measure force or load.*/
    AIForceBridgeTableChanAttribute AIForceBridgeTableChan;
    /*Creates channel(s) that use a Wheatstone bridge to measure force or load.*/
    AIForceBridgeTwoPointLinChanAttribute AIForceBridgeTwoPointLinChan;
    /*Creates channel(s) that use an IEPE force sensor to measure force or load.*/
    AIForceIEPEChanAttribute AIForceIEPEChan;
    /*Creates channel(s) that use a frequency-to-voltage converter to measure frequency and adds the channel(s) to the task you specify with taskHandle.*/
    AIFreqVoltageChanAttribute AIFreqVoltageChan;
    /*Creates channel(s) that use a microphone to measure sound pressure and adds the channel(s) to the task you specify with taskHandle.*/
    AIMicrophoneChanAttribute AIMicrophoneChan;
    /*Creates channel(s) that use a Wheatstone bridge to measure pressure.*/
    AIPressureBridgePolynomialChanAttribute AIPressureBridgePolynomialChan;
    /*Creates channel(s) that use a Wheatstone bridge to measure pressure.*/
    AIPressureBridgeTableChanAttribute AIPressureBridgeTableChan;
    /*Creates channel(s) that use a Wheatstone bridge to measure pressure.*/
    AIPressureBridgeTwoPointLinChanAttribute AIPressureBridgeTwoPointLinChan;
    /*Create channel(s) to measure resistance and adds the channel(s) to the task you specify with taskHandle.*/
    AIResistanceChanAttribute AIResistanceChan;
    /*Creates channel(s) to measure strain and adds the channel(s) to the task you specify with taskHandle.*/
    AIRosetteStrainGageChanAttribute AIRosetteStrainGageChan;
    /*Creates channel(s) that use an RTD to measure temperature and adds the channel(s) to the task you specify with taskHandle.*/
    AIRTDChanAttribute AIRTDChan;
    /*Creates channel(s) to measure strain and adds the channel(s) to the task you specify with taskHandle.*/
    AIStrainGageChanAttribute AIStrainGageChan;
    /*Creates channel(s) to measure temperature with a built-in sensor of a terminal block or device and adds the channel(s) to the task you specify with taskHandle. */
    AITempBuiltInSensorChanAttribute AITempBuiltInSensorChan;
    /*Creates channel(s) that use a thermocouple to measure temperature and adds the channel(s) to the task you specify with taskHandle.*/
    AIThrmcplChanAttribute AIThrmcplChan;
    /*Creates channel(s) that use a thermistor to measure temperature and adds the channel(s) to the task you specify with taskHandle.*/
    AIThrmstrChanIexAttribute AIThrmstrChanIex;
    /*Creates channel(s) that use a thermistor to measure temperature and adds the channel(s) to the task you specify with taskHandle. */
    AIThrmstrChanVexAttribute AIThrmstrChanVex;
    /*Creates channel(s) that use a Wheatstone bridge to measure torque.*/
    AITorqueBridgePolynomialChanAttribute AITorqueBridgePolynomialChan;
    /*Creates channel(s) that use a Wheatstone bridge to measure torque.*/
    AITorqueBridgeTableChanAttribute AITorqueBridgeTableChan;
    /*Creates channel(s) that use a Wheatstone bridge to measure torque.*/
    AITorqueBridgeTwoPointLinChanAttribute AITorqueBridgeTwoPointLinChan;
    /*Creates channel(s) that use an IEPE velocity sensor to measure velocity.*/
    AIVelocityIEPEChanAttribute AIVelocityIEPEChan;
    /*Creates channel(s) to measure voltage and adds the channel(s) to the task you specify with taskHandle.*/
    AIVoltageChanAttribute AIVoltageChan;
    /*Creates channel(s) to measure RMS voltage and adds the channel(s) to the task you specify with taskHandle.*/
    AIVoltageRMSChanAttribute AIVoltageRMSChan;
    /*Creates channel(s) to measure voltage and adds the channels to the task you specify with taskHandle.*/
    AIVoltageChanWithExcitAttribute AIVoltageChanWithExcit;
    /*Creates channel(s) that use an eddy current proximity probe to measure linear position and adds the channel(s) to the task you specify with taskHandle.*/
    AIPosEddyCurrProxProbeChanAttribute AIPosEddyCurrProxProbeChan;
    /*Creates channel(s) that use an LVDT to measure linear position and adds the channel(s) to the task you specify with taskHandle.*/
    AIPosLVDTChanAttribute AIPosLVDTChan;
    /*Creates channel(s) that use an RVDT to measure angular position and adds the channel(s) to the task you specify with taskHandle.*/
    AIPosRVDTChanAttribute AIPosRVDTChan;
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////Create TEDs Analog Input ////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*Creates channel(s) that use an accelerometer to measure acceleration and adds the channel(s) to the task you specify with taskHandle.*/
    TEDSAIAccelChanAttribute TEDSAIAccelChan;
    /*Creates channel(s) to measure current and adds the channel(s) to the task you specify with taskHandle.*/
    TEDSAICurrentChanAttribute TEDSAICurrentChan;
    /*Creates a channel that measures voltage ratios from a Wheatstone bridge.*/
    TEDSAIBridgeChanAttribute TEDSAIBridgeChan;
    /*Creates channel(s) that use a Wheatstone bridge to measure force or load.*/
    TEDSAIForceBridgeChanAttribute TEDSAIForceBridgeChan;
    /*Creates channel(s) that use an IEPE force sensor to measure force or load.*/
    TEDSAIForceIEPEChanAttribute TEDSAIForceIEPEChan;
    /*Creates channel(s) that use a microphone to measure sound pressure and adds the channel(s) to the task you specify with taskHandle.*/
    TEDSAIMicrophoneChanAttribute TEDSAIMicrophoneChan;
    /*Creates channel(s) that use a Wheatstone bridge to measure pressure.*/
    TEDSAIPressureBridgeChanAttribute TEDSAIPressureBridgeChan;
    /*Creates channel(s) to measure resistance and adds the channel(s) to the task you specify with taskHandle.*/
    TEDSAIResistanceChanAttribute TEDSAIResistanceChan;
    /*Creates channel(s) that use an RTD to measure temperature and adds the channel(s) to the task you specify with taskHandle.*/
    TEDSAIRTDChanAttribute TEDSAIRTDChan;
    /*Creates channel(s) to measure strain and adds the channel(s) to the task you specify with taskHandle.*/
    TEDSAIStrainGageChanAttribute TEDSAIStrainGageChan;
    /*Creates channel(s) that use a thermocouple to measure temperature and adds the channel(s) to the task you specify with taskHandle.*/
    TEDSAIThrmcplChanAttribute TEDSAIThrmcplChan;
    /*Creates channel(s) that use a thermistor to measure temperature and adds the channel(s) to the task you specify with taskHandle.*/
    TEDSAIThrmstrChanIexAttribute TEDSAIThrmstrChanIex;
    /*Creates channel(s) that use a thermistor to measure temperature and adds the channel(s) to the task you specify with taskHandle.*/
    TEDSAIThrmstrChanVexAttribute TEDSAIThrmstrChanVex;
    /*Creates channel(s) that use a Wheatstone bridge to measure torque.*/
    TEDSAITorqueBridgeChanAttribute TEDSAITorqueBridgeChan;
    /*Creates channel(s) to measure voltage and adds the channel(s) to the task you specify with taskHandle.*/
    TEDSAIVoltageChanAttribute TEDSAIVoltageChan;
    /*Creates channel(s) to measure voltage and adds the channel(s) to the task you specify with taskHandle.*/
    TEDSAIVoltageChanWithExcitAttribute TEDSAIVoltageChanWithExcit;
    /*Creates channel(s) that use an LVDT to measure linear position and adds the channel(s) to the task you specify with taskHandle. */
    TEDSAIPosLVDTChanAttribute TEDSAIPosLVDTChan;
    /*Creates channel(s) that use an RVDT to measure angular position and adds the channel(s) to the task you specify with taskHandle.*/
    TEDSAIPosRVDTChanAttribute TEDSAIPosRVDTChan;
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////Create Digital Input ////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*Creates channel(s) to measure digital signals and adds the channel(s) to the task you specify with taskHandle.*/
    DIChanAttribute DIChan;
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////Create Counter Input ////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*Creates a channel to measure angular velocity. */
    CIAngVelocityChanAttribute CIAngVelocityChan;
    /*Creates a channel to count the number of rising or falling edges of a digital signal and adds the channel to the task you specify with taskHandle. */
    CICountEdgesChanAttribute CICountEdgesChan;
    /*Creates channel(s) to duty cycle of a digital pulse.*/
    CIDutyCycleChanAttribute CIDutyCycleChan;
    /*Creates a channel to measure the frequency of a digital signal and adds the channel to the task you specify with taskHandle. */
    CIFreqChanAttribute CIFreqChan;
    /*Creates a channel that uses a linear encoder to measure linear velocity. */
    CILinVelocityChanAttribute CILinVelocityChan;
    /*Creates a channel to measure the period of a digital signal and adds the channel to the task you specify with taskHandle.*/
    CIPeriodChanAttribute CIPeriodChan;
    /*Creates a channel to measure pulse specifications, returning the measurements as pairs of frequency and duty cycle, and adds the channel to the task you specify with taskHandle. */
    CIPulseChanFreqAttribute CIPulseChanFreq;
    /*Creates a channel to measure pulse specifications, returning the measurements as pairs of high ticks and low ticks, and adds the channel to the task you specify with taskHandle.*/
    CIPulseChanTicksAttribute CIPulseChanTicks;
    /*Creates a channel to measure pulse specifications, returning the measurements as pairs of high time and low time, and adds the channel to the task you specify with taskHandle. */
    CIPulseChanTimeAttribute CIPulseChanTime;
    /*Creates a channel to measure the width of a digital pulse and adds the channel to the task you specify with taskHandle.*/
    CIPulseWidthChanAttribute CIPulseWidthChan;
    /*Creates a channel to measure the time between state transitions of a digital signal and adds the channel to the task you specify with taskHandle.*/
    CISemiPeriodChanAttribute CISemiPeriodChan;
    /*Creates a channel that measures the amount of time between the rising or falling edge of one digital signal and the rising or falling edge of another digital signal.*/
    CITwoEdgeSepChanAttribute CITwoEdgeSepChan;
    /*Creates a channel that uses a linear encoder to measure linear position.*/
    CILinEncoderChanAttribute CILinEncoderChan;
    /*Creates a channel that uses an angular encoder to measure angular position. */
    CIAngEncoderChanAttribute CIAngEncoderChan;
    /*Creates a channel that uses a special-purpose counter to take a timestamp and synchronizes that counter to a GPS receiver. */
    CIGPSTimestampChanAttribute CIGPSTimestampChan;
}InputChannelConfigureAttribute,*pInputChannelConfigureAttribute;

typedef struct{
    ViInt16 GenChanType;
	/*Creates channel(s) to generate current and adds the channel(s) to the task you specify with taskHandle.*/
    AOVIGenChanAttribute AOVIGenChanAttr;
	/*Creates a channel for continually generating a waveform on the selected physical channel.*/
    AOFuncGenChanAttribute FunGenChanAttr;
	/*Creates channel(s) to generate digital signals and adds the channel(s) to the task you specify with taskHandle.*/
    DOChanAttribute DOChan;
	/*Creates channel(s) to generate digital pulses that freq and dutyCycle define and adds the channel to the task you specify with taskHandle. */
    COPulseChanFreqAttribute COPulseChanFreq;
    /*Creates channel(s) to generate digital pulses defined by the number of timebase ticks that the pulse is at a high state and the number of timebase 
     * ticks that the pulse is at a low state and also adds the channel to the task you specify with taskHandle.*/
    COPulseChanTicksAttribute COPulseChanTicks;
    /*Creates channel(s) to generate digital pulses defined by the amount of time the pulse is at a high state and the amount of time 
     * the pulse is at a low state and adds the channel to the task you specify with taskHandle.*/
    COPulseChanTimeAttribute COPulseChanTime;
}OutputChannelConfigureAttribute, *pOutputChannelConfigureAttribute;

typedef struct{
    /*Specifies whether the task acquires or generates samples continuously or if it acquires or generates a finite number of samples.
     * DAQmx_Val_FiniteSamps  Acquire or generate a finite number of samples. 
     * DAQmx_Val_ContSamps  Acquire or generate samples until you stop the task.
     * DAQmx_Val_HWTimedSinglePoint  Acquire or generate samples continuously using hardware timing without a buffer. */
    ViInt32 nSampleMode;
    /*The number of samples to acquire from each channel if sampleMode is DAQmx_Val_FiniteSamps. */
    ViUInt64 unSampsPerChan;
    /*Specifies the sampling rate in samples per channel per second. */
    ViReal64 dSampleClkRate;
    /*Specifies the terminal to which to route the Sample Clock.*/
    ViConstString szSampleClkOutpTerm;
    /*Specifies if the polarity for the exported sample clock is active high or active low.*/
    ViInt32 nSampleClkPulsePolarity;
    /*Specifies whether the task pauses while the signal is high or low.*/
    ViInt32 nPauseWhen;
    /*Specifies the polarity for the Ready for Transfer event.*/
    ViInt32 nReadyEventActiveLevel;
}BurstHandshakingTimingExportClockAttribute,*pBurstHandshakingTimingExportClockAttribute;

typedef struct{
    /*Specifies whether the task acquires or generates samples continuously or if it acquires or generates a finite number of samples.
     * DAQmx_Val_FiniteSamps  Acquire or generate a finite number of samples. 
     * DAQmx_Val_ContSamps  Acquire or generate samples until you stop the task.
     * DAQmx_Val_HWTimedSinglePoint  Acquire or generate samples continuously using hardware timing without a buffer. */
    ViInt32 nSampleMode;
    /*The number of samples to acquire from each channel if sampleMode is DAQmx_Val_FiniteSamps. */
    ViUInt64 unSampsPerChan;
    /*Specifies the sampling rate in samples per channel per second. */
    ViReal64 dSampleClkRate;
    /*Specifies the terminal of the signal to use as the Sample Clock.*/
    ViConstString szSampleClkSrc;
    /*Specifies on which edge of a clock pulse sampling takes place.
     * DAQmx_Val_Rising  Acquire or generate samples on the rising edges of the Sample Clock. 
     * DAQmx_Val_Falling  Acquire or generate samples on the falling edges of the Sample Clock. */
    ViInt32 nSampleClkActiveEdge;
    /*Specifies whether the task pauses while the signal is high or low.*/
    ViInt32 nPauseWhen;
    /*Specifies the polarity for the Ready for Transfer event.*/
    ViInt32 nReadyEventActiveLevel;
}BurstHandshakingTimingImportClockAttribute,*pBurstHandshakingTimingImportClockAttribute;

typedef struct{
    /*The names of the digital lines or ports on which to detect rising edges. */
    ViConstString szRisingEdgeChan;
    /*The names of the digital lines or ports on which to detect falling edges. */
    ViConstString szFallingEdgeChan;
    /*Specifies whether the task acquires or generates samples continuously or if it acquires or generates a finite number of samples.
     * DAQmx_Val_FiniteSamps  Acquire or generate a finite number of samples. 
     * DAQmx_Val_ContSamps  Acquire or generate samples until you stop the task.
     * DAQmx_Val_HWTimedSinglePoint  Acquire or generate samples continuously using hardware timing without a buffer. */
    ViInt32 nSampleMode;
    /*The number of samples to acquire from each channel if sampleMode is DAQmx_Val_FiniteSamps. */
    ViUInt64 unSampsPerChan;
}ChangeDetectionTimingAttribute,*pChangeDetectionTimingAttribute;

typedef struct{
    /*Specifies whether the task acquires or generates samples continuously or if it acquires or generates a finite number of samples.
     * DAQmx_Val_FiniteSamps  Acquire or generate a finite number of samples. 
     * DAQmx_Val_ContSamps  Acquire or generate samples until you stop the task.
     * DAQmx_Val_HWTimedSinglePoint  Acquire or generate samples continuously using hardware timing without a buffer. */
    ViInt32 nSampleMode;
    /*The number of samples to acquire or generate for each channel in the task if sampleMode is DAQmx_Val_FiniteSamps.*/
    ViUInt64 unSampsPerChanToAcquire;
}HandshakingTimingAttribute,*pHandshakingTimingAttribute;

typedef struct{
    /*Specifies whether the task acquires or generates samples continuously or if it acquires or generates a finite number of samples.
     * DAQmx_Val_FiniteSamps  Acquire or generate a finite number of samples. 
     * DAQmx_Val_ContSamps  Acquire or generate samples until you stop the task.
     * DAQmx_Val_HWTimedSinglePoint  Acquire or generate samples continuously using hardware timing without a buffer. */
    ViInt32 nSampleMode;
    /*The number of samples to acquire or generate for each channel in the task if sampleMode is DAQmx_Val_FiniteSamps.*/
    ViUInt64 unSampsPerChanToAcquire;
}ImplicitTimingAttribute,*pImplicitTimingAttribute;

typedef struct{
    /*The source terminal of the Sample Clock.*/
    ViConstString szSource;
    /*The sampling rate in samples per second per channel. */
    ViReal64 dRate;
    /*Specifies on which edge of the clock to acquire or generate samples.
     * DAQmx_Val_Rising  Acquire or generate samples on the rising edges of the Sample Clock.
     * DAQmx_Val_Falling  Acquire or generate samples on the falling edges of the Sample Clock. */
    ViInt32 nActiveEdge;
    /*Specifies whether the task acquires or generates samples continuously or if it acquires or generates a finite number of samples.
     * DAQmx_Val_FiniteSamps  Acquire or generate a finite number of samples. 
     * DAQmx_Val_ContSamps  Acquire or generate samples until you stop the task.
     * DAQmx_Val_HWTimedSinglePoint  Acquire or generate samples continuously using hardware timing without a buffer. */
    ViInt32 nSampleMode;
    /*The number of samples to acquire or generate for each channel in the task if sampleMode is DAQmx_Val_FiniteSamps.*/
    ViUInt64 unSamplesPerChannel;
}PipelinedSampClkTimingAttribute,*pPipelinedSampClkTimingAttribute;

typedef struct{
    /*The source terminal of the Sample Clock.*/
    ViConstString szSource;
    /*The sampling rate in samples per second per channel. */
    ViReal64 dRate;
    /*Specifies on which edge of the clock to acquire or generate samples.
     * DAQmx_Val_Rising  Acquire or generate samples on the rising edges of the Sample Clock.
     * DAQmx_Val_Falling  Acquire or generate samples on the falling edges of the Sample Clock. */
    ViInt32 nActiveEdge;
    /*Specifies whether the task acquires or generates samples continuously or if it acquires or generates a finite number of samples.
     * DAQmx_Val_FiniteSamps  Acquire or generate a finite number of samples. 
     * DAQmx_Val_ContSamps  Acquire or generate samples until you stop the task.
     * DAQmx_Val_HWTimedSinglePoint  Acquire or generate samples continuously using hardware timing without a buffer. */
    ViInt32 nSampleMode;
    /*The number of samples to acquire or generate for each channel in the task if sampleMode is DAQmx_Val_FiniteSamps. */
    ViUInt64 unSampsPerChanToAcquire;
}SampClkTimingAttribute,*pSampClkTimingAttribute;

typedef struct{
    ViInt16 TimingType;
    /*Configures when the DAQ device transfers data to a peripheral device, using the DAQ device's onboard sample clock to control burst handshaking timing.*/
    BurstHandshakingTimingExportClockAttribute BurstHandshakingTimingExportClock;
    /*Configures when the DAQ device transfers data to a peripheral device, using an imported sample clock to control burst handshaking timing.*/
    BurstHandshakingTimingImportClockAttribute BurstHandshakingTimingImportClock;
    /*Configures the task to acquire samples on the rising and/or falling edges of the lines or ports you specify.*/
    ChangeDetectionTimingAttribute ChangeDetectionTiming;
    /*Determines the number of digital samples to acquire or generate using digital handshaking between the device and a peripheral device.*/
    HandshakingTimingAttribute HandshakingTiming;
    /*Sets only the number of samples to acquire or generate without specifying timing.*/
    ImplicitTimingAttribute ImplicitTiming;
    /*Sets the source of the Sample Clock, the rate of the Sample Clock, and the number of samples to acquire or generate.*/
    PipelinedSampClkTimingAttribute PipelinedSampClkTiming;
    /*Sets the source of the Sample Clock, the rate of the Sample Clock, and the number of samples to acquire or generate.*/
    SampClkTimingAttribute SampClkTiming;
}TimingConfigureAttribute,*pTimingConfigureAttribute;

typedef struct{
    /*Specifies on which slope of the signal to start acquiring or generating samples when the signal crosses triggerLevel.
     * DAQmx_Val_RisingSlope  Trigger on the rising slope of the signal. 
     * DAQmx_Val_FallingSlope  Trigger on the falling slope of the signal. */
    ViInt32 nTriggerSlope;
    /*The threshold at which to start acquiring or generating samples.*/
    ViReal64 dTriggerLevel;
}AnlgEdgeStartTrigAttribute,*pAnlgEdgeStartTrigAttribute;

typedef struct{
    /*The array containing the slopes of the signals to start acquiring or generating samples when the respective signal crosses the specified trigger level.
     * DAQmx_Val_RisingSlope  Trigger on the rising slope of the signal. 
     * DAQmx_Val_FallingSlope  Trigger on the falling slope of the signal. */
    ViInt32 *nTriggerSlopeArray;
    /*The array containing the thresholds at which to start acquiring or generating samples.*/
    ViReal64 *dTriggerLevelArray;
    /*The size of triggerSlopeArray and triggerLevelArray. */
    ViUInt32 unArraySize;
}AnlgMultiEdgeStartTrigAttribute,*pAnlgMultiEdgeStartTrigAttribute;

typedef struct{
    /*The name of a channel or terminal where there is an analog signal to use as the source of the trigger.*/
    ViConstString szTriggerSource;
    /*Specifies on which edge of a digital signal to start acquiring or generating samples.
     * DAQmx_Val_Rising  Rising edge(s). 
     * DAQmx_Val_Falling  Falling edge(s). */
    ViInt32 nTriggerEdge;
}DigEdgeStartTrigAttribute,*pDigEdgeStartTrigAttribute;

typedef struct{
   
    /*Specifies the unit of trigger delay.*/
    
}TriggerDelayAttribute, *TriggerDelayAttributep;

typedef struct{
     /*Specifies the trigger delay time*/
    ViReal64 dwDelay;
    /*Specifies the retriggerable state*/
    ViBoolean bReTriggerable;
    /*The name of a channel or terminal where there is an analog signal to use as the source of the trigger.*/
    ViChar* szTriggerSource;
    /*Configures the task to start acquiring or generating samples when an analog signal crosses the level you specify.*/
    AnlgEdgeStartTrigAttribute AnlgEdgeStartTrig;
    /*Configures the task to start acquiring or generating samples when any of the configured analog signals cross the respective levels you specified.*/
    AnlgMultiEdgeStartTrigAttribute AnlgMultiEdgeStartTrig;
    /*Configures the task to start acquiring or generating samples on a rising or falling edge of a digital signal.*/
    DigEdgeStartTrigAttribute DigEdgeStartTrig;
}TriggerConfigureAttribute,*pTriggerConfigureAttribute;

typedef struct{
    /*The size of the array, in samples, into which samples are read.*/
    ViUInt32 unArraySizeInSamps;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViUInt32 *bReserved;
}AnalogF64InputAttribute,*pAnalogF64InputAttribute;

typedef struct{
    /*The array to read samples into, organized according to fillMode.*/
    ViReal64 *dReadArray;
    /*The actual number of samples read from each channel.*/
    ViInt32 nSampsPerChanRead;
}AnalogF64OutputAttribute,*pAnalogF64OutputAttribute;

typedef struct{
    /*The amount of time, in seconds, to wait for the function to read the sample(s). */
    ViReal64 dTimeout;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}AnalogScalarF64InputAttribute,*pAnalogScalarF64InputAttribute;

typedef struct{
    /*The sample read from the task.*/
    ViReal64 *dValue;
}AnalogScalarF64OutputAttribute,*pAnalogScalarF64OutputAttribute;

typedef struct{
    /*The number of samples, per channel, to read. 
     * The default value of -1 (DAQmx_Val_Auto) reads all available samples. */
    ViInt32 nNumSampsPerChan;
    /*The amount of time, in seconds, to wait for the function to read the sample(s). 
     * To specify an infinite wait, pass -1 (DAQmx_Val_WaitInfinitely). */
    ViReal64 dTimeout;
    /*Specifies whether or not the samples are interleaved.
     * DAQmx_Val_GroupByChannel  Group by channel (non-interleaved) 
     * DAQmx_Val_GroupByScanNumber  Group by scan number (interleaved) */
    ViBoolean bFillMode;
    /*The size of the array, in samples, into which samples are read.*/
    ViUInt32 unArraySizeInSamps;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}BinaryInputAttribute,*pBinaryInputAttribute;

typedef struct{
    /*The array to read samples into, organized according to fillMode.*/
    ViInt16 *nReadArray;
    /*The actual number of samples read from each channel.*/
    ViInt32 *nSampsPerChanRead;
}BinaryI16OutputAttribute,*pBinaryI16OutputAttribute;

typedef struct{
    /*The array to read samples into, organized according to fillMode.*/
    ViInt32 *nReadArray;
    /*The actual number of samples read from each channel.*/
    ViInt32 *nSampsPerChanRead;
}BinaryI32OutputAttribute,*pBinaryI32OutputAttribute;

typedef struct{
    /*The array to read samples into, organized according to fillMode.*/
    ViUInt16 *unReadArray;
    /*The actual number of samples read from each channel.*/
    ViInt32 *nSampsPerChanRead;
}BinaryU16OutputAttribute,*pBinaryU16OutputAttribute;

typedef struct{
    /*The array to read samples into, organized according to fillMode.*/
    ViUInt32 *unReadArray;
    /*The actual number of samples read from each channel.*/
    ViInt32 *nSampsPerChanRead;
}BinaryU32OutputAttribute,*pBinaryU32OutputAttribute;

typedef struct{
    /*The number of samples, per channel, to read. 
     * The default value of -1 (DAQmx_Val_Auto) reads all available samples. */
    ViInt32 nNumSampsPerChan;
    /*The amount of time, in seconds, to wait for the function to read the sample(s). 
     * To specify an infinite wait, pass -1 (DAQmx_Val_WaitInfinitely). */
    ViReal64 dTimeout;
    /*The size of the array, in samples, into which samples are read.*/
    ViUInt32 unArraySizeInSamps;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}CounterF64InputAttribute,*pCounterF64InputAttribute;

typedef struct{
    /*The array to read samples into, organized according to fillMode.*/
    ViReal64 *dReadArray;
    /*The actual number of samples read from each channel.*/
    ViInt32 *nSampsPerChanRead;
}CounterF64OutputAttribute,*pCounterF64OutputAttribute;

typedef struct{
    /*The amount of time, in seconds, to wait for the function to read the sample(s). */
    ViReal64 dTimeout;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}CounterScalarF64InputAttribute,*pCounterScalarF64InputAttribute;

typedef struct{
    /*The sample read from the task.*/
    ViReal64 *dValue;
}CounterScalarF64OutputAttribute,*pCounterScalarF64OutputAttribute;

typedef struct{
    /*The sample read from the task.*/
    ViUInt32 *unValue;
}CounterScalarU32OutputAttribute,*pCounterScalarU32OutputAttribute;

typedef struct{
    /*The number of samples, per channel, to read. 
     * The default value of -1 (DAQmx_Val_Auto) reads all available samples. */
    ViInt32 nNumSampsPerChan;
    /*The amount of time, in seconds, to wait for the function to read the sample(s). 
     * To specify an infinite wait, pass -1 (DAQmx_Val_WaitInfinitely). */
    ViReal64 dTimeout;
    /*Specifies whether or not the samples are interleaved.
     * DAQmx_Val_GroupByChannel  Group by channel (non-interleaved) 
     * DAQmx_Val_GroupByScanNumber  Group by scan number (interleaved) */
    ViBoolean bInterleaved;
    /*The size of the array, in samples, into which samples are read.*/
    ViUInt32 unArraySizeInSamps;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}CtrFreqInputAttribute,*pCtrFreqInputAttribute;

typedef struct{
    /*The array to read frequency samples into.*/
    ViReal64 *dReadArrayFrequency;
    /*The array to read duty cycles into. 
     * The duty cycle is the pulse high time divided by the pulse period.*/
    ViReal64 *dReadArrayDutyCycle;
    /*The actual number of samples read from each channel.*/
    ViInt32 *nSampsPerChanRead;
}CtrFreqOutputAttribute,*pCtrFreqOutputAttribute;

typedef struct{
    /*The pulse frequency.*/
    ViReal64 *dFrequency;
    /*The pulse high time divided by the pulse period.*/
    ViReal64 *dDutyCycle;
}CtrFreqScalarOutputAttribute,*pCtrFreqScalarOutputAttribute;

typedef struct{
    /*The array to read the number of high ticks into.*/
    ViUInt32 *unReadArrayHighTicks;
    /*The array to read the number of low ticks into.*/
    ViUInt32 *unReadArrayLowTicks;
    /*The actual number of samples read from each channel.*/
    ViInt32 *nSampsPerChanRead;
}CtrTicksOutputAttribute,*pCtrTicksOutputAttribute;

typedef struct{
    /*The number of ticks the pulse is high.*/
    ViUInt32 *unHighTicks;
    /*The number of ticks the pulse is low.*/
    ViUInt32 *unLowTicks;
}CtrTicksScalarOutputAttribute,*pCtrTicksScalarOutputAttribute;

typedef struct{
    /*The array to read the number of high ticks into.*/
    ViUInt32 *unReadArrayHighTime;
    /*The array to read the number of low ticks into.*/
    ViUInt32 *unReadArrayLowTime;
    /*The actual number of samples read from each channel.*/
    ViInt32 *nSampsPerChanRead;
}CtrTimeOutputAttribute,*pCtrTimeOutputAttribute;

typedef struct{
    /*The amount of time the pulse is high.*/
    ViReal64 *dHighTime;
    /*The amount of time the pulse is low.*/
    ViReal64 *dLowTime;
}CtrTimeScalarOutputAttribute,*pCtrTimeScalarOutputAttribute;

typedef struct{
    /*The number of samples, per channel, to read. 
     * The default value of -1 (DAQmx_Val_Auto) reads all available samples. */
    ViInt32 nNumSampsPerChan;
    /*The amount of time, in seconds, to wait for the function to read the sample(s). 
     * To specify an infinite wait, pass -1 (DAQmx_Val_WaitInfinitely). */
    ViReal64 dTimeout;
    /*Specifies whether or not the samples are interleaved.
     * DAQmx_Val_GroupByChannel  Group by channel (non-interleaved) 
     * DAQmx_Val_GroupByScanNumber  Group by scan number (interleaved) */
    ViBoolean bFillMode;
    /*The size of the array, in samples, into which samples are read.*/
    ViUInt32 unArraySizeInBytes;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}DigitalLinesInputAttribute,*pDigitalLinesInputAttribute;

typedef struct{
    /*The array to read samples into. Each numBytesPerSamp corresponds to one sample per channel, with each element in that grouping corresponding to 
     * a line in that channel, up to the number of lines contained in the channel.*/
    ViUInt8 *unReadArray;
    /*The actual number of samples read from each channel.*/
    ViInt32 *nSampsPerChanRead;
    /*The number of elements in readArray that constitutes a sample per channel.*/
    ViInt32 *nNumBytesPerSamp;
}DigitalLinesOutputAttribute,*pDigitalLinesOutputAttribute;

typedef struct{
    /*The number of samples, per channel, to read. 
     * The default value of -1 (DAQmx_Val_Auto) reads all available samples. */
    ViInt32 nNumSampsPerChan;
    /*The amount of time, in seconds, to wait for the function to read the sample(s). 
     * To specify an infinite wait, pass -1 (DAQmx_Val_WaitInfinitely). */
    ViReal64 dTimeout;
    /*Specifies whether or not the samples are interleaved.
     * DAQmx_Val_GroupByChannel  Group by channel (non-interleaved) 
     * DAQmx_Val_GroupByScanNumber  Group by scan number (interleaved) */
    ViBoolean bFillMode;
    /*The size of the array, in samples, into which samples are read.*/
    ViUInt32 unArraySizeInSamps;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}DigitalU8InputAttribute,*pDigitalU8InputAttribute;

typedef struct{
    /*The array to read samples into, organized according to fillMode.*/
    ViUInt8 *unReadArray;
    /*The actual number of samples read from each channel.*/
    ViInt32 *nSampsPerChanRead;
}DigitalU8OutputAttribute,*pDigitalU8OutputAttribute;

typedef struct{
    /*The array to read samples into, organized according to fillMode.*/
    ViUInt16 *unReadArray;
    /*The actual number of samples read from each channel.*/
    ViInt32 *nSampsPerChanRead;
}DigitalU16OutputAttribute,*pDigitalU16OutputAttribute;

typedef struct{
    /*The array to read samples into, organized according to fillMode.*/
    ViUInt32 *unReadArray;
    /*The actual number of samples read from each channel.*/
    ViInt32 *nSampsPerChanRead;
}DigitalU32OutputAttribute,*pDigitalU32OutputAttribute;

typedef struct{
    /*The Nth channel to return. The index starts at 1.*/
    ViUInt32 unIndex;
    /*The size, in bytes, of buffer. 
     * If you pass 0, this function returns the number of bytes needed to allocate.*/
    ViInt32 nBufferSize;
}GetNthTaskReadChannelInputAttribute,*pGetNthTaskReadChannelInputAttribute;

typedef struct{
    /*The Nth channel in the index. 
     * If you pass NULL, this function returns the number of bytes needed to allocate.*/
    ViChar *cBuffer;
}GetNthTaskReadChannelOutputAttribute,*pGetNthTaskReadChannelOutputAttribute;

typedef struct{
    /*The number of samples, per channel, to read. 
     * The default value of -1 (DAQmx_Val_Auto) reads all available samples. */
    ViInt32 nNumSampsPerChan;
    /*The amount of time, in seconds, to wait for the function to read the sample(s). 
     * To specify an infinite wait, pass -1 (DAQmx_Val_WaitInfinitely). */
    ViReal64 dTimeout;
    /*The size of the array, in samples, into which samples are read.*/
    ViUInt32 unArraySizeInBytes;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}RawInputAttribute,*pRawInputAttribute;

typedef struct{
    /*The array into which samples are read.*/
    void *vReadArray;
    /*The actual number of samples read into the array per scan.*/
    ViInt32 *nSampsRead;
    /*The number of elements in readArray that constitutes a sample.*/
    ViInt32 *nNumBytesPerSamp;
}RawOutputAttribute,*pRawOutputAttribute;

typedef struct{
    /*The number of samples, per channel, to read. The default value of -1 (DAQmx_Val_Auto) reads all available samples.*/
    ViInt32 nArraySizeInSamps;
    /*Specifies whether or not the samples are interleaved.
     * DAQmx_Val_GroupByChannel  Group by channel (non-interleaved) 
     * DAQmx_Val_GroupByScanNumber  Group by scan number (interleaved) */
    ViBoolean bFillMode;
    /*Reads multiple floating-point samples from a task that contains one or more analog input channels.*/
    AnalogF64InputAttribute AnalogF64Input;
    AnalogF64OutputAttribute AnalogF64Output;
    /*Reads a single floating-point sample from a task that contains a single analog input channel.*/
    AnalogScalarF64InputAttribute AnalogScalarF64Input;
    AnalogScalarF64OutputAttribute AnalogScalarF64Output;
    /*Reads multiple unscaled, signed 16-bit integer samples from a task that contains one or more analog input channels.*/
    BinaryInputAttribute BinaryI16Input;
    BinaryI16OutputAttribute BinaryI16Output;
    /*Reads one or more unscaled 32-bit signed integer samples from a task that contains one or more analog input channels.*/
    BinaryInputAttribute BinaryI32Input;
    BinaryI32OutputAttribute BinaryI32Output;
    /*Reads multiple unscaled, unsigned 16-bit integer samples from a task that contains one or more analog input channels.*/
    BinaryInputAttribute BinaryU16Input;
    BinaryU16OutputAttribute BinaryU16Output;
    /*Reads one or more unscaled 32-bit unsigned integer samples from a task that contains one or more analog input channels.*/
    BinaryInputAttribute BinaryU32Input;
    BinaryU32OutputAttribute BinaryU32Output;
    /*Reads multiple floating-point samples from a counter task.*/
    CounterF64InputAttribute CounterF64Input;
    CounterF64OutputAttribute CounterF64Output;
    /*Reads multiple floating-point samples from a counter task.*/
    BinaryInputAttribute CounterF64ExInput;
    CounterF64OutputAttribute CounterF64ExOutput;
    /*Reads a single floating-point sample from a counter task.*/
    CounterScalarF64InputAttribute CounterScalarF64Input;
    CounterScalarF64OutputAttribute CounterScalarF64Output;
    /*Reads a 32-bit integer sample from a counter task. */
    CounterScalarF64InputAttribute CounterScalarU32Input;
    CounterScalarU32OutputAttribute CounterScalarU32Output;
    /*Reads multiple 32-bit integer samples from a counter task.*/
    CounterF64InputAttribute CounterU32Input;
    BinaryU32OutputAttribute CounterU32Output;
    /*Reads multiple 32-bit integer samples from a counter task. */
    BinaryInputAttribute CounterU32ExInput;
    BinaryU32OutputAttribute CounterU32ExOutput;
    /*Reads one or more pairs of pulse frequency and duty cycle from a counter input task.*/
    CtrFreqInputAttribute CtrFreqInput;
    CtrFreqOutputAttribute CtrFreqOutput;
    /*Reads a single pair of pulse frequency and duty cycle from a counter input task.*/
    CounterScalarF64InputAttribute CtrFreqScalarInput;
    CtrFreqScalarOutputAttribute CtrFreqScalarOutput;
    /*Reads one or more pairs of pulse high and low tick counts from a counter input task.*/
    CtrFreqInputAttribute CtrTicksInput;
    CtrTicksOutputAttribute CtrTicksOutput;
    /*Reads one or more pairs of pulse high and low tick counts from a counter input task.*/
    CounterScalarF64InputAttribute CtrTicksScalarInput;
    CtrTicksScalarOutputAttribute CtrTicksScalarOutput;
    /*Reads one or more pairs of pulse high and low times from a counter input task.*/
    CtrFreqInputAttribute CtrTimeInput;
    CtrTimeOutputAttribute CtrTimeOutput;
    /*Reads one or more pairs of pulse high and low times from a counter input task.*/
    CounterScalarF64InputAttribute CtrTimeScalarInput;
    CtrTimeScalarOutputAttribute CtrTimeScalarOutput;
    /*Reads multiple samples from each digital line in a task. Each line in a channel gets one byte per sample.*/
    DigitalLinesInputAttribute DigitalLinesInput;
    DigitalLinesOutputAttribute DigitalLinesOutput;
    /*Reads a single 32-bit integer sample from a task that contains a single digital input channel. */
    CounterScalarF64InputAttribute DigitalScalarU32Input;
    CounterScalarU32OutputAttribute DigitalScalarU32Output;
    /*Reads multiple 8-bit integer samples from a task that has one or more multiple digital input channels.*/
    DigitalU8InputAttribute DigitalU8Input;
    DigitalU8OutputAttribute DigitalU8Output;
    /*Reads multiple 16-bit integer samples from a task that contains one or more digital input channels. */
    DigitalU8InputAttribute DigitalU16Input;
    DigitalU16OutputAttribute DigitalU16Output;
    /*Reads multiple 32-bit integer samples from a task that contains one or more digital input channels. */
    DigitalU8InputAttribute DigitalU32Input;
    DigitalU32OutputAttribute DigitalU32Output;
    /*Returns the Nth channel of the channels that are configured to be read by the DAQmxSetReadChannelsToRead property.*/
    GetNthTaskReadChannelInputAttribute GetNthTaskReadChannelInput;
    GetNthTaskReadChannelOutputAttribute GetNthTaskReadChannelOutput;
    /*Reads raw samples directly from the input lines.*/
    RawInputAttribute RawInput;
    RawOutputAttribute RawOutput;
}DAQMXMeasureResult,*pDAQMXMeasureResult;

typedef struct{
    /*Specifies how the samples are arranged, either interleaved or noninterleaved.
     * DAQmx_Val_GroupByChannel  Group by channel (noninterleaved) 
     * DAQmx_Val_GroupByScanNumber  Group by sample (interleaved) */
    ViBoolean bDataLayout;
    /*The array of 64-bit samples to write to the task.*/
    ViReal64 *dWriteArray;
    /*Return the actual number of samples per channel successfully written to the buffer.*/
    ViInt32 nSampsPerChanWritten;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViUInt32 *bReserved;
}WriteAnalogF64InputAttribute,*pWriteAnalogF64InputAttribute;

typedef struct{
    /*A 64-bit sample to write to the task.*/
    ViReal64 dValue;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViUInt32 *bReserved;
}WriteAnalogScalarF64InputAttribute,*pWriteAnalogScalarF64InputAttribute;

typedef struct{
    /*The number of samples, per channel, to write. */
    ViInt32 nNumSampsPerChan;
    /*Specifies whether or not this function automatically starts the task if you do not start it.*/
    ViBoolean bAutoStart;
    /*The amount of time, in seconds, to wait for this function to write all the samples.*/
    ViReal64 dTimeout;
    /*Specifies how the samples are arranged, either interleaved or noninterleaved.
     * DAQmx_Val_GroupByChannel  Group by channel (noninterleaved) 
     * DAQmx_Val_GroupByScanNumber  Group by sample (interleaved) */
    ViBoolean bDataLayout;
    /*The array of 16-bit samples to write to the task.*/
    ViInt16 *nWriteArray;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}WriteBinaryI16InputAttribute,*pWriteBinaryI16InputAttribute;

typedef struct{
    /*The number of samples, per channel, to write. */
    ViInt32 nNumSampsPerChan;
    /*Specifies whether or not this function automatically starts the task if you do not start it.*/
    ViBoolean bAutoStart;
    /*The amount of time, in seconds, to wait for this function to write all the samples.*/
    ViReal64 dTimeout;
    /*Specifies how the samples are arranged, either interleaved or noninterleaved.
     * DAQmx_Val_GroupByChannel  Group by channel (noninterleaved)
     * DAQmx_Val_GroupByScanNumber  Group by sample (interleaved) */
    ViBoolean bDataLayout;
    /*The array of 16-bit samples to write to the task.*/
    ViUInt16 *unWriteArray;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}WriteBinaryU16InputAttribute,*pWriteBinaryU16InputAttribute;

typedef struct{
    /*The number of samples, per channel, to write. */
    ViInt32 nNumSampsPerChan;
    /*Specifies whether or not this function automatically starts the task if you do not start it.*/
    ViBoolean bAutoStart;
    /*The amount of time, in seconds, to wait for this function to write all the samples.*/
    ViReal64 dTimeout;
    /*Specifies how the samples are arranged, either interleaved or noninterleaved.
     * DAQmx_Val_GroupByChannel  Group by channel (noninterleaved)
     * DAQmx_Val_GroupByScanNumber  Group by sample (interleaved) */
    ViBoolean bDataLayout;
    /*Specifies at what frequency to generate pulses.*/
    ViReal64 *dFrequency;
    /*The width of the pulse divided by the pulse period.*/
    ViReal64 *dDutyCycle;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}WriteCtrFreqInputAttribute,*pWriteCtrFreqInputAttribute;

typedef struct{
    /*Specifies whether or not this function automatically starts the task if you do not start it.*/
    ViBoolean bAutoStart;
    /*The amount of time, in seconds, to wait for this function to write all the samples.*/
    ViReal64 dTimeout;
    /*Specifies at what frequency to generate pulses.*/
    ViReal64 *dFrequency;
    /*The width of the pulse divided by the pulse period.*/
    ViReal64 *dDutyCycle;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}WriteCtrFreqScalarInputAttribute,*pWriteCtrFreqScalarInputAttribute;

typedef struct{
    /*The number of samples, per channel, to write. */
    ViInt32 nNumSampsPerChan;
    /*Specifies whether or not this function automatically starts the task if you do not start it.*/
    ViBoolean bAutoStart;
    /*The amount of time, in seconds, to wait for this function to write all the samples.*/
    ViReal64 dTimeout;
    /*Specifies how the samples are arranged, either interleaved or noninterleaved.
     * DAQmx_Val_GroupByChannel  Group by channel (noninterleaved)
     * DAQmx_Val_GroupByScanNumber  Group by sample (interleaved) */
    ViBoolean bDataLayout;
    /*The number of timebase ticks the pulse is high.*/
    ViUInt32 *unHighTicks;
    /*The number of timebase ticks the pulse is low.*/
    ViUInt32 *unLowTicks;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}WriteCtrTicksInputAttribute,*pWriteCtrTicksInputAttribute;

typedef struct{
    /*Specifies whether or not this function automatically starts the task if you do not start it.*/
    ViBoolean bAutoStart;
    /*The amount of time, in seconds, to wait for this function to write all the samples.*/
    ViReal64 dTimeout;
    /*The number of timebase ticks the pulse is high.*/
    ViUInt32 *unHighTicks;
    /*The number of timebase ticks the pulse is low.*/
    ViUInt32 *unLowTicks;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}WriteCtrTicksScalarInputAttribute,*pWriteCtrTicksScalarInputAttribute;

typedef struct{
    /*The number of samples, per channel, to write. */
    ViInt32 nNumSampsPerChan;
    /*Specifies whether or not this function automatically starts the task if you do not start it.*/
    ViBoolean bAutoStart;
    /*The amount of time, in seconds, to wait for this function to write all the samples.*/
    ViReal64 dTimeout;
    /*Specifies how the samples are arranged, either interleaved or noninterleaved.
     * DAQmx_Val_GroupByChannel  Group by channel (noninterleaved)
     * DAQmx_Val_GroupByScanNumber  Group by sample (interleaved) */
    ViBoolean bDataLayout;
    /*The amount of time the pulse is high.*/
    ViReal64 *dHighTime;
    /*The amount of time the pulse is low.*/
    ViReal64 *dLowTime;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}WriteCtrTimeInputAttribute,*pWriteCtrTimeInputAttribute;

typedef struct{
    /*Specifies whether or not this function automatically starts the task if you do not start it.*/
    ViBoolean bAutoStart;
    /*The amount of time, in seconds, to wait for this function to write all the samples.*/
    ViReal64 dTimeout;
    /*The amount of time the pulse is high.*/
    ViReal64 dHighTime;
    /*The amount of time the pulse is low.*/
    ViReal64 dLowTime;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}WriteCtrTimeScalarInputAttribute,*pWriteCtrTimeScalarInputAttribute;

typedef struct{
    /*The number of samples, per channel, to write. */
    ViInt32 nNumSampsPerChan;
    /*Specifies whether or not this function automatically starts the task if you do not start it.*/
    ViBoolean bAutoStart;
    /*The amount of time, in seconds, to wait for this function to write all the samples.*/
    ViReal64 dTimeout;
    /*Specifies how the samples are arranged, either interleaved or noninterleaved.
     * DAQmx_Val_GroupByChannel  Group by channel (noninterleaved)
     * DAQmx_Val_GroupByScanNumber  Group by sample (interleaved) */
    ViBoolean bDataLayout;
    /*The samples to write to the task.*/
    ViUInt8 unWriteArray;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}WriteDigitalLinesInputAttribute,*pWriteDigitalLinesInputAttribute;

typedef struct{
    /*Specifies whether or not this function automatically starts the task if you do not start it.*/
    ViBoolean bAutoStart;
    /*The amount of time, in seconds, to wait for this function to write all the samples.*/
    ViReal64 dTimeout;
    /*A 32-bit integer sample to write to the task.*/
    ViUInt32 unValue;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}WriteDigitalScalarU32InputAttribute,*pWriteDigitalScalarU32InputAttribute;

typedef struct{
    /*The number of samples, per channel, to write. */
    ViInt32 nNumSampsPerChan;
    /*Specifies whether or not this function automatically starts the task if you do not start it.*/
    ViBoolean bAutoStart;
    /*The amount of time, in seconds, to wait for this function to write all the samples.*/
    ViReal64 dTimeout;
    /*Specifies how the samples are arranged, either interleaved or noninterleaved.
     * DAQmx_Val_GroupByChannel  Group by channel (noninterleaved)
     * DAQmx_Val_GroupByScanNumber  Group by sample (interleaved) */
    ViBoolean bDataLayout;
    /*The samples to write to the task.*/
    ViUInt8 unWriteArray;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}WriteDigitalU8InputAttribute,*pWriteDigitalU8InputAttribute;

typedef struct{
    /*The number of samples, per channel, to write. */
    ViInt32 nNumSampsPerChan;
    /*Specifies whether or not this function automatically starts the task if you do not start it.*/
    ViBoolean bAutoStart;
    /*The amount of time, in seconds, to wait for this function to write all the samples.*/
    ViReal64 dTimeout;
    /*Specifies how the samples are arranged, either interleaved or noninterleaved.
     * DAQmx_Val_GroupByChannel  Group by channel (noninterleaved)
     * DAQmx_Val_GroupByScanNumber  Group by sample (interleaved) */
    ViBoolean bDataLayout;
    /*The samples to write to the task.*/
    ViUInt16 unWriteArray;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}WriteDigitalU16InputAttribute,*pWriteDigitalU16InputAttribute;

typedef struct{
    /*The number of samples, per channel, to write. */
    ViInt32 nNumSampsPerChan;
    /*Specifies whether or not this function automatically starts the task if you do not start it.*/
    ViBoolean bAutoStart;
    /*The amount of time, in seconds, to wait for this function to write all the samples.*/
    ViReal64 dTimeout;
    /*Specifies how the samples are arranged, either interleaved or noninterleaved.
     * DAQmx_Val_GroupByChannel  Group by channel (noninterleaved)
     * DAQmx_Val_GroupByScanNumber  Group by sample (interleaved) */
    ViBoolean bDataLayout;
    /*The samples to write to the task.*/
    ViUInt32 unWriteArray;
    /*Reserved for future use. Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}WriteDigitalU32InputAttribute,*pWriteDigitalU32InputAttribute;

typedef struct{
    /*The number of samples per channel to write.*/
    ViInt32 nNumSamps;
    /*Specifies whether or not this function automatically starts the task if you do not start it.*/
    ViBoolean bAutoStart;
    /*The amount of time, in seconds, to wait for this function to write all the samples. */
    ViReal64 dTimeout;
    /*The raw samples to write to the task.*/
    void *vWriteArray;
    /*Reserved for future use. 
     * Pass NULL to this parameter.*/
    ViBoolean *bReserved;
}WriteRawInputAttribute,*pWriteRawInputAttribute;

typedef struct{
    ViReal64 amplitude;
    ViReal64 frequency;
    ViReal64 phase;
}WaveformAttribute, *pWaveformAttribute;

typedef struct{
    ViInt16 WaveformType;
    //Generate waveform
    WaveformAttribute WaveformInput;
    /*The number of samples, per channel, to read. 
     * The default value of -1 (DAQmx_Val_Auto) reads all available samples. */
    ViInt32 nNumSampsPerChan;
    /*Specifies whether or not this function automatically starts the task if you do not start it.*/
    ViBoolean bAutoStart;
    /*The amount of time, in seconds, to wait for the function to read the sample(s). 
     * To specify an infinite wait, pass -1 (DAQmx_Val_WaitInfinitely). */
    ViReal64 dTimeout;
    /*Writes multiple floating-point samples to a task that contains one or more analog output channels.*/
    WriteAnalogF64InputAttribute WriteAnalogF64Input;
    /*Writes a floating-point sample to a task that contains a single analog output channel.*/
    WriteAnalogScalarF64InputAttribute WriteAnalogScalarF64Input;
    /*Writes unscaled signed integer samples to the task.*/
    WriteBinaryI16InputAttribute WriteBinaryI16Input;
    /*Writes unscaled, unsigned 16-bit integer samples to the task.*/
    WriteBinaryU16InputAttribute WriteBinaryU16Input;
    /*Writes a new pulse frequency and duty cycle to each channel in a continuous counter output task that contains one or more channels.*/
    WriteCtrFreqInputAttribute WriteCtrFreqInput;
    /*Writes a new pulse frequency and duty cycle to a continuous counter output task that contains a single channel.*/
    WriteCtrFreqScalarInputAttribute WriteCtrFreqScalarInput;
    /*Writes new pulse high tick counts and low tick counts to each channel in a continuous counter output task that contains one or more channels.*/
    WriteCtrTicksInputAttribute WriteCtrTicksInput;
    /*Writes a new pulse high tick count and low tick count to a continuous counter output task that contains a single channel.*/
    WriteCtrTicksScalarInputAttribute WriteCtrTicksScalarInput;
    /*Writes a new pulse high time and low time to each channel in a continuous counter output task that contains one or more channels.*/
    WriteCtrTimeInputAttribute WriteCtrTimeInput;
    /*Writes a new pulse high time and low time to a continuous counter output task that contains a single channel.*/
    WriteCtrTimeScalarInputAttribute WriteCtrTimeScalarInput;
    /*Writes multiple samples to each digital line in a task.*/
    WriteDigitalLinesInputAttribute WriteDigitalLinesInput;
    /*Writes a single 32-bit unsigned integer sample to a task that contains a single digital output channel.*/
    WriteDigitalScalarU32InputAttribute WriteDigitalScalarU32Input;
    /*Writes multiple 8-bit unsigned integer samples to a task that contains one or more digital output channels.*/
    WriteDigitalU8InputAttribute WriteDigitalU8Input;
    /*Writes multiple 16-bit unsigned integer samples to a task that contains one or more digital output channels.*/
    WriteDigitalU16InputAttribute WriteDigitalU16Input;
    /*Writes multiple 32-bit unsigned integer samples to a task that contains one or more digital output channels.*/
    WriteDigitalU32InputAttribute WriteDigitalU32Input;
    /*Writes raw samples to a task. There is no scaling, parsing, or separation of the samples.*/
    WriteRawInputAttribute WriteRawInput;
}WaveformGenAttribute,*pWaveformGenAttribute;

typedef struct{
    OutputChannelConfigureAttribute OutputGenChanAttr;
    TimingConfigureAttribute  TimingAttr;
    TriggerConfigureAttribute TriggerAttr;
}SignalGenField, *pSignalGenField;

typedef struct{
    InputChannelConfigureAttribute InputGenChanAttr;
    TimingConfigureAttribute  TimingAttr;
    TriggerConfigureAttribute TriggerAttr;
    ConfigureLoggingAttribute LoggingAttr;
}SignalAcqField, *pSignalAcqField;

typedef struct {
    //Specifies the channel of Device
    ViChar* pszPhysicalChannelName;
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel. 
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode 
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The source terminal of the Sample Clock.*/
    ViConstString szSource;
    //Specifies the number of samples.
    ViUInt32 dwNumberofSamples;
    //Specifies the I/Q rate for the acquisition. The value is expressed in samples per second (S/s).
    ViReal32 dwSampleRate;
    //Specifies the Trigger property
    TriggerConfigureAttribute triggerAttr;
    /*The path to the TDMS file to which you want to log data.*/
    ViConstString szFilePath;
    /* The name of the group to create within the TDMS file for data from this task. 
     * If you append data to an existing file and the specified group already exists, NI-DAQmx appends a number symbol and a number to the group name, incrementing that number until finding a group name that does not exist. 
     * For example, if you specify a group name of Voltage Task, and that group already exists, NI-DAQmx assigns the group name Voltage Task #1, then Voltage Task #2. 
     * If you do not specify a group name, NI-DAQmx uses the name of the task.
     * For digital input tasks, NI-DAQmx creates a group for each virtual channel in the task. 
     * For each created group, NI-DAQmx appends a hyphen and the virtual channel name to the group name.
     */
    ViChar* pszWaveformName;
}DAQmxMeasureAttribute, *pDAQmxMeasureAttribute;

typedef enum{
    DAQMX_VAL_TRIGGER_TYPE_ANALOG_EDGESTART = 0,
    DAQMX_VAL_TRIGGER_TYPE_ANALOG_MULTIEDGESTART,
    DAQMX_VAL_TRIGGER_TYPE_DIGIT_EDGESTART,
    DAQMX_VAL_TRIGGER_TYPE_DISABLE,        
}CCDAQTRIGGERTYPE;

/*************************************************************************************************/
#include <map>
#include "string.h"
using namespace std;

class CCDAQmxsgSignalAttribute
{
public:
    CCDAQmxsgSignalAttribute()
    {
        dwMinVal = -10.0;
        dwMaxVal =  10.0;
        szSource = CCRFSA_VAL_ONBOARD_CLOCK_STR;
        dwSampleRate = 1000;
        dwNumberofSamples = 1000;
        TriggerType = DAQMX_VAL_TRIGGER_TYPE_DISABLE;
        triggerAttr.DigEdgeStartTrig.szTriggerSource = "";
        triggerAttr.DigEdgeStartTrig.nTriggerEdge = DAQmx_Val_Rising;
        
        WaveformType = DAQMX_VAL_WAVEFORM_TYPE_SINE;
        dwFrequency = 1000;
        dwPowerLevel = 0.0;
        dwImpedanceVal = 1;
        
    }
    CCDAQmxsgSignalAttribute(const CCDAQmxsgSignalAttribute& attr)
    {
        dwMinVal = attr.dwMinVal;
        dwMaxVal = attr.dwMaxVal;
        szSource = attr.szSource;
        dwSampleRate = attr.dwSampleRate;
        dwNumberofSamples = attr.dwNumberofSamples;
        TriggerType = attr.TriggerType;
        triggerAttr = attr.triggerAttr;
        
        WaveformType = attr.WaveformType;
        dwFrequency = attr.dwFrequency;
        dwPowerLevel = attr.dwPowerLevel;
        dwImpedanceVal = attr.dwImpedanceVal;
    }
    CCDAQmxsgSignalAttribute(const CCDAQmxsgSignalAttribute* pAttr)
    {
        dwMinVal = pAttr->dwMinVal;
        dwMaxVal = pAttr->dwMaxVal;
        szSource = pAttr->szSource;
        dwSampleRate = pAttr->dwSampleRate;
        dwNumberofSamples = pAttr->dwNumberofSamples;
        TriggerType = pAttr->TriggerType;
        triggerAttr = pAttr->triggerAttr;
        
        WaveformType = pAttr->WaveformType;
        dwFrequency = pAttr->dwFrequency;
        dwPowerLevel = pAttr->dwPowerLevel;
        dwImpedanceVal = pAttr->dwImpedanceVal;
    }
public:
    //The minimum value, in units, that you expect to generate
    ViReal64 dwMinVal;
    //TThe maximum value, in units, that you expect to generate
    ViReal64 dwMaxVal;
    //Specifies the type of wave
    ViInt16 WaveformType;
    //Specifies the frequency of the generated RF signal, in hertz. Units: hertz (Hz)
    ViReal64 dwFrequency;
    //Specifies either the amplitude of the audio signal. Units: dBm
    ViReal64 dwPowerLevel;
    //Specifies the impedance of chip
    ViReal64 dwImpedanceVal;
    //Specifies the number of samples.
    ViUInt32 dwNumberofSamples;
    /*The source terminal of the Sample Clock.*/
    ViConstString szSource;
    //Specifies the I/Q rate for the acquisition. The value is expressed in samples per second (S/s).
    ViReal32 dwSampleRate;
    //Specifies the Trigger property
    TriggerConfigureAttribute triggerAttr;
    CCDAQTRIGGERTYPE TriggerType;
};

class CCDAQmxMeasureAttribute
{
public:
    CCDAQmxMeasureAttribute()
    {
        nTerminalConfig = DAQmx_Val_Diff;
        szSource = CCRFSA_VAL_ONBOARD_CLOCK_STR;
        dwMinVal = -10.0;
        dwMaxVal =  10.0;
        dwNumberofSamples = 100;
        dwSampleRate = 1000;
        TriggerType = DAQMX_VAL_TRIGGER_TYPE_DISABLE;
        triggerAttr.DigEdgeStartTrig.szTriggerSource = "";
        triggerAttr.DigEdgeStartTrig.nTriggerEdge = DAQmx_Val_Rising;
        triggerAttr.bReTriggerable = true;
        triggerAttr.dwDelay = 0;

        //szFilePath = (ViChar*)"C:/MuTest/bin/demo.tdms";
        //pszWaveformName = VI_NULL;
    }
    CCDAQmxMeasureAttribute(const CCDAQmxMeasureAttribute& attr)
    {
        //int nSizeFile = strlen(attr.szFilePath)+1;
        //int nSizeName = strlen(attr.pszWaveformName)+1;
        dwMinVal = attr.dwMinVal;
        dwMaxVal = attr.dwMaxVal;
        nTerminalConfig = attr.nTerminalConfig;
        szSource = attr.szSource;
        dwNumberofSamples = attr.dwNumberofSamples;
        dwSampleRate = attr.dwSampleRate;
        TriggerType = attr.TriggerType;
        triggerAttr = attr.triggerAttr;
        /*
        szFilePath = new ViChar[nSizeFile];
        memset(szFilePath, 0x00, nSizeFile);
        memcpy(szFilePath,attr.szFilePath,nSizeFile);
        pszWaveformName = new ViChar[nSizeName];
        memset(pszWaveformName, 0x00, nSizeName);
        memcpy(pszWaveformName,attr.pszWaveformName,nSizeName);
        */
    }
    CCDAQmxMeasureAttribute(const CCDAQmxMeasureAttribute* pAttr)
    {
        //int nSizeFile = strlen(pAttr->szFilePath)+1;
        //int nSizeName = strlen(pAttr->pszWaveformName)+1;
        dwMinVal = pAttr->dwMinVal;
        dwMaxVal = pAttr->dwMaxVal;
        nTerminalConfig = pAttr->nTerminalConfig;
        szSource = pAttr->szSource;
        dwNumberofSamples = pAttr->dwNumberofSamples;
        dwSampleRate = pAttr->dwSampleRate;
        TriggerType = pAttr->TriggerType;
        triggerAttr = pAttr->triggerAttr;
        /*
        szFilePath = new ViChar[nSizeFile];
        memset(szFilePath, 0x00, nSizeFile);
        memcpy(szFilePath,pAttr->szFilePath,nSizeFile);
        pszWaveformName = new ViChar[nSizeName];
        memset(pszWaveformName, 0x00, nSizeName);
        memcpy(pszWaveformName,pAttr->pszWaveformName,nSizeName);
        */
    }

public:
    //The minimum value, in units, that you expect to measure
    ViReal64 dwMinVal;
    //TThe maximum value, in units, that you expect to measure
    ViReal64 dwMaxVal;
    /*The input terminal configuration for the channel.
     * DAQmx_Val_Cfg_Default  At run time, NI-DAQmx chooses the default terminal configuration for the channel. 
     * DAQmx_Val_RSE  Referenced single-ended mode 
     * DAQmx_Val_NRSE  Non-referenced single-ended mode 
     * DAQmx_Val_Diff  Differential mode 
     * DAQmx_Val_PseudoDiff  Pseudodifferential mode */
    ViInt32 nTerminalConfig;
    /*The source terminal of the Sample Clock.*/
    ViConstString szSource;
    //Specifies the number of samples.
    ViUInt32 dwNumberofSamples;
    //Specifies the I/Q rate for the acquisition. The value is expressed in samples per second (S/s).
    ViReal32 dwSampleRate;
    //Specifies the Trigger property
    TriggerConfigureAttribute triggerAttr;
    CCDAQTRIGGERTYPE TriggerType;
    /*The path to the TDMS file to which you want to log data.*/
    //ViChar* szFilePath;
    /* The name of the group to create within the TDMS file for data from this task. 
     * If you append data to an existing file and the specified group already exists, NI-DAQmx appends a number symbol and a number to the group name, incrementing that number until finding a group name that does not exist. 
     * For example, if you specify a group name of Voltage Task, and that group already exists, NI-DAQmx assigns the group name Voltage Task #1, then Voltage Task #2. 
     * If you do not specify a group name, NI-DAQmx uses the name of the task.
     * For digital input tasks, NI-DAQmx creates a group for each virtual channel in the task. 
     * For each created group, NI-DAQmx appends a hyphen and the virtual channel name to the group name.
     */
    //ViChar* pszWaveformName;
};

class DLLAPI CCFetchAudioResults : public CCResultsArray<DAQMXMeasureResult>
{
public:
    CCFetchAudioResults();
    ~CCFetchAudioResults();
public:
    void RemoveAll();
};

#endif	/* CCDAQMXSTRUCTDEF_H */

