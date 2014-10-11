/*
 * Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef CHUD_CTRL_H
#define CHUD_CTRL_H

/*!
  @header CHUD Control Macros and constants
  Use the CHUD Control Macros and constants to simplify and clarify code that makes use of
  CHUD API calls. A key element of the CHUD API is the "CHUD device." All of the CHUD devices 
  are enumerated as constants, and there are macros to compare and sort devices by their 
  enumerations. All of the CHUD API's function status and error codes are enumerated as well.
  The first rule of using the CHUD API is: "When in doubt, check the status code."
*/

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_CPU_COUNT	 	2	/* maximum number of processors */
#define MAX_MC_COUNT	 	1	/* maximum number of memory controllers */
#define MAX_OS_COUNT		1	/* maximum number of kernels */

/*! 
    @defined MisCPUDevice( dev )
    @abstract returns truth as to whether or not the device constant represents a processor.
    @discussion Use MisCPUDevice to determine if a (potential) argument for a CHUD 
    informational or configuration function represents a processor in the system.
    Pass in the CHUD device constant that needs to be checked. e.g: chudCPU1Dev
*/

#define MisCPUDevice( dev ) \
((dev) == chudCPU1Dev || (dev) == chudCPU2Dev || (dev) == chudAllCPUDev)

/*! 
    @defined MisAltCPUDevice( dev )
    @abstract returns truth as to whether or not the device constant represents an "alternate"
    processor device.
    @discussion An alternate processor device represents a type of CPU that is not present in 
    the system the program executing the CHUD functions is running on, but is available in some 
    other Mac, or portable. Use MisAltCPUDevice to determine if a (potential) argument for a CHUD 
    informational or configuration function represents an alternate processor in the system.
    Pass in the alternate CHUD device constant that needs to be checked. e.g: chudAltCPU1Dev
*/

#define MisAltCPUDevice( dev ) \
((dev) == chudAltCPU1Dev || (dev) == chudAltCPU2Dev || (dev) == chudAltAllCPUDev)

/*! 
    @defined MisMCDevice( dev )
    @abstract returns truth as to whether or not the device constant represents a memory- 
    controller.
    @discussion Use MisMCDevice to determine if a (potential) argument for a CHUD 
    informational or configuration function represents a memory controller in the system.
    Pass in the CHUD device constant that needs to be checked. e.g: chudMCDev
*/

#define MisMCDevice( dev ) \
((dev) == chudMCDev)

/*! 
    @defined MisAPIDevice( dev )
    @abstract returns truth as to whether or not the device constant represents a processor to 
    north-bridge (memory controller) ASIC.
    @discussion Use MisAPIDevice to determine if a (potential) argument for a CHUD 
    informational or configuration function represents a CPU to Memory Controller interface chip 
    in the system.
    Pass in the CHUD device constant that needs to be checked. e.g: chudAPIDev
*/

#define MisAPIDevice( dev ) \
((dev) == chudAPIDev)

/*! 
    @defined MisOSDevice( dev )
    @abstract returns truth as to whether or not the device constant represents an instance of
    the operating system. While the operating system is not a piece of hardware, the CHUD api
    has abstracted performance counters in MacOS X to behave and be available just like the 
    hardware PMCs.
    @discussion Use MisOSDevice to determine if a (potential) argument for a CHUD 
    informational or configuration function represents the Operating System running on the 
    machine.
    Pass in the CHUD device constant that needs to be checked. e.g: chudOSDev
*/

#define MisOSDevice( dev ) \
((dev) == chudOSDev)

/*! 
    @defined MisAltMCDevice( dev )
    @abstract returns truth as to whether or not the device constant represents an alternate 
    memory-controller.
    @discussion Use MisAltMCDevice to determine if a (potential) argument for a CHUD 
    informational or configuration function represents some valid memory controller that is 
    not available in the system that is currently being used.
    Pass in the CHUD device constant that needs to be checked. e.g: chudAltMCDev
*/

#define MisAltMCDevice( dev ) \
((dev) == chudAltMCDev)

/*! 
    @defined MisAltAPIDevice( dev )
    @abstract returns truth as to whether or not the device constant represents a processor to 
    north-bridge (memory controller) ASIC.
    @discussion Use MisAltAPIDevice to determine if a (potential) argument for a CHUD 
    informational or configuration function represents a valid CPU to Memory Controller interface 
    chip in some Apple system, but not the current system.
    Pass in the CHUD device constant that needs to be checked. e.g: chudAltAPIDev
*/

#define MisAltAPIDevice( dev ) \
((dev) == chudAltAPIDev)

/*! 
    @defined MisAltOSDevice( dev )
    @abstract returns truth as to whether or not the device constant represents an instance of
    a MacOS X operating system version.
    @discussion Use MisAltOSDevice to determine if a (potential) argument for a CHUD 
    informational or configuration function represents a valid Operating System that could run 
    on the an Apple computer.
    Pass in the CHUD device constant that needs to be checked. e.g: chudAltOSDev
*/

#define MisAltOSDevice( dev ) \
((dev) == chudAltOSDev)

/*! 
    @defined MdeviceIndex( dev )
    @abstract returns a zero-based integer index that represents the order of the device, in the 
    cases where there can be multiple devices of a given type (processors in particular) in a 
    system.
    @discussion Use MdeviceIndex to convert a device type into a simple integer index (handy for 
    accessing device specific data stored in array fashion...one entry in an array for each device 
    of a particular type)
    Pass in the CHUD device constant that needs to be checked. e.g: chudCPU1Dev will yield a '0',
    while chudCPU2Dev returns a '1.' 
*/
#define MdeviceIndex( dev ) \
(((dev) == chudCPU1Dev || (dev) == chudMCDev || (dev) == chudOSDev || (dev) == chudAltCPU1Dev || (dev) == chudAllCPUDev || (dev) == chudAltAllCPUDev)?0:1)

/*! 
    @defined MindexToCPUDevice( idx )
    @abstract returns a chud_device_t (chud device type enumeration) based on the integer index 
    passed in.
    @discussion Use MindexToCPUDevice to convert a simple integer index into a device enum-
    eration.
    Pass in a '0' and chudCPU1Dev is returned; pass in a 1 and chudCPU2 is returned. 
*/
#define MindexToCPUDevice( index ) \
((index)?chudCPU2Dev:chudCPU1Dev)

/*! 
    @defined MindexToAltCPUDevice( idx )
    @abstract returns a chud_device_t (chud device type enumeration) based on the integer index 
    passed in.
    @discussion Use MindexToAltCPUDevice to convert a simple integer index into a device enum-
    eration.
    Pass in a '0' and chudAltCPU1Dev is returned; pass in a 1 and chudAltCPU2 is returned. 
*/
#define MindexToAltCPUDevice( index ) \
((index)?chudAltCPU2Dev:chudAltCPU1Dev)

/*! 
    @defined MisStrictCPUDevice( dev )
    @abstract returns truth as to whether or not the device constant represents a processor. But
    using the constant chudAllCPUDev will yield a false result
    @discussion Use MisStrictCPUDevice to determine if a (potential) argument for a CHUD 
    informational or configuration function represents a specific processor in the system.
    Pass in the CHUD device constant that needs to be checked. e.g: chudCPU1Dev
*/

#define MisStrictCPUDevice( dev ) \
((dev) == chudCPU1Dev || (dev) == chudCPU2Dev)

/*! 
    @defined MisStrictAltCPUDevice( dev )
    @abstract returns truth as to whether or not the device constant represents an alternate 
    processor. Using the constant chudAltAllCPUDev will yield a false result
    @discussion Use MisStrictAltCPUDevice to determine if a (potential) argument for a CHUD 
    informational or configuration function represents a specific processor in some system.
    Pass in the CHUD device constant that needs to be checked. e.g: chudAltCPU1Dev
*/

#define MisStrictAltCPUDevice( dev ) \
((dev) == chudAltCPU1Dev || (dev) == chudAltCPU2Dev)

/*!
    @typedef chud_device_t
    @abstract Most functions throughout the CHUD API require a "device specifier." These device
    specifiers, or just "devices," are limited to the set described here.  
    @discussion While there are many CHUD functions that are fairly obvious regarding which
    devices are valid, There are also many "generic functions" that apply to any valid 
    device specifier. For example: the function chudPMCCount() can take any one of chudCPU1Dev, 
    chudMCDev, chudOSDev, chudIOCDev, chudAPIDev, or any of the 'Alt' devices. Basically, any 
    device that has "PMCs" (performance monitor counter registers) can return a count of how many
    it has.
    @constant chudCPU1Dev  represents the processor in slot 1 of the system being profiled.
    @constant chudCPU2Dev  represents the processor in slot 2 of the system being profiled.
    @constant chudAllCPUDev represents both of the processors in the system being profiled.
    @constant chudMCDev	 represents the memory controller, or north-bridge chip of the system 
    being profiled.
    @constant chudIOCDev represents the I/O controller, or south-bridge chip of the system being 
    profiled.
    @constant chudAPIDev represents the interface ASIC between the processor and the north-bridge 
    in the system being profiled.
    @constant chudHTDev	represents the HyperTransport(tm) interface ASIC in the north-bridge of 
    the system being profiled
    @constant chudOSDev	 represents the operating system running on the hardware being profiled

    @constant chudAltCPU1Dev represents a processor that is used  in slot 1, in some other Apple 
    computer, not processor 1 in the current system.
    @constant chudAltCPU2Dev represents a processor that is used  in slot 2, in some other Apple 
    computer, not processor 2 in the current system.
    @constant chudAltAllCPUDev represents both processors used in some other Apple computer, not 
    the current system.
    @constant chudAltMCDev represents a memory controller in some other Apple computer, not in 
    the current system.
    @constant chudAltIOCDev represents an I/O controller in some other Apple computer, not in the
    current system.
    @constant chudAltAPIDev represents the interface ASIC between the processor and the memory 
    controller in some other Apple computer, not in the current system.
    some other Apple computer.
    @constant chudAltHTDev represents the HyperTransport(tm) interface ASIC in the north-bridge 
    of some other Apple computer.
    @constant chudAltOSDev represents a different version of the operating system. Not the OS 
    running on the hardware being profiled.
        
    @constant chudTimerDev refers to the mechanism built into CHUD used to acquire performance 
    data-samples at regular (wall-clock) timed intervals.
    @constant chudUserDev refers to the mechanism built into CHUD used to acquire performance 
    data-samples only when explicitly requested by the operator interacting with the profiling 
    software in some way.

    @constant chudAllDev is really here for completeness sake and is not (currently) used in the
    CHUD API.
    @constant chudNoDev is really here for completeness sake and is not (currently) used in the
    CHUD API.
    
*/

typedef void (*chudCallbackFunc)(unsigned long _instnc, unsigned long _commnd);
typedef void (*chudCallbackFuncData)(unsigned long _instnc, unsigned long _commnd, int data);

/* device types */
typedef enum {
    chudNoDev		=  0,
    chudAltAllCPUDev	=  -4,
    chudAllCPUDev	=  -3,
    chudAllDev 		=  -2,
    chudUserDev 	=  16,
    chudCPU1Dev 	=  32,
    chudCPU2Dev 	=  33,
    chudMCDev 		=  64,
    chudOSDev 		=  96,
    chudIOCDev		= 111,
    chudTimerDev	= 128,
    chudAPIDev		= 192,
    chudHTDev		= 320,
    chudAltCPU1Dev	= 432,
    chudAltCPU2Dev	= 433,
    chudAltMCDev 	= 464,
    chudAltOSDev 	= 496,
    chudAltIOCDev	= 511,
    chudAltAPIDev	= 592,
} chud_device_t;

/*!
    @typedef chud_status_t
    @abstract Every function in the CHUD API either returns or sets a "status value." The valid 
    status values are limited to the set described here.  
    @discussion Most functions return the status value as an integer upon their return. But some 
    are limited in that they must return a non-integer value, like a character array, or a 
    boolean. Every function in the CHUD API will set its status value before it returns. The CHUD 
    API is robust, but not foolproof. Remember to take advantage of the status values, and the 
    status strings that can be requested at any time. CHUD status values are all large negative 
    integers, except for "chudSucess" which is a zero. Most of these status values should be self 
    explainatory...
    @constant --generic--
    @constant chudSuccess  generic status relaying the proper completion of a function's task.
    @constant chudFailure  generic error the function has exited early for some reason.
    @constant chudInvalidIndex an array subscript or event index is out of bounds
    @constant chudInvalidValue the argument is out of range for the function or the device the 
    function will operate on.
    @constant chudInvalidUnits the unit type or the value of the unit argument is out of range
    @constant chudInvalidMemoryPointer 
    @constant chudMemAllocFailure
    @constant chudIOKitFailure
    @constant chudMachFailure
    @constant chudInvalidArgument
    @constant chudFunctionNotImplemented
    @constant chudInvalidAddress        
    @constant chudBootstrapFailure
    @constant chudUnknownCpu
    @constant chudNotInitialized
    @constant chudCleanupMustBeCalledFirst
    @constant --devices--
    @constant chudBadDeviceID
    @constant chudDeviceNotSupported
    @constant chudDeviceNotPresent
    @constant chudSamplingDeviceNotSet
    @constant --PMCs--
    @constant chudBadPmcID
    @constant chudReservedEvent
    @constant chudInvalidEvent
    @constant chudBadFilterMode
    @constant chudBadPMCMode
    @constant chudPMItriggerNotSet
    @constant chudInvalidFunctionalUnit
    @constant chudBadInstructionMatchMode
    @constant chudBadIOPMarkMode
    @constant chudBadIDUMask
    @constant chudBadIDUMatch
    @constant --Processes/Threading--    
    @constant chudCheckPIDFailure
    @constant chudCheckTaskFailure
    @constant chudCheckThreadFailure
    @constant --shortcuts--
    @constant chudNoShortcutFileOpen
    @constant chudNoBuiltinShortcutFile
    @constant chudNoUserShortcutFile
    @constant chudInvalidShortcutIndex
    @constant chudShortcutListFull
    @constant chudNoShortcutActive
    @constant chudInvalidShortcutFile
    @constant chudShortcutSaveFailure
    @constant --global hot keys--
    @constant chudAddHotkeyFailed
    @constant chudRemoveHotkeyFailed
    @constant chudNoHotkeyCallback
    @constant chudInvalidModifierKey
    @constant --sampling--
    @constant chudSampleFacilityInUse
    @constant chudWaitingForSampleFacility
    @constant chudSampleFacilityNotAcquired
    @constant chudMapSampleBufferFailure
    @constant chudNoSamplesAvailable
    @constant --remote sampling--
    @constant chudRemoteFacilityInUse
    @constant chudRemoteFacilityNoServer
    @constant chudRemoteFacilityNotAcquired
    @constant --kernel extensions--
    @constant chudUtilsKextNotLoaded
    @constant chudProfKextNotLoaded
    @constant --alternate devices--
    @constant chudNoAlternateProcessorInfo
    @constant chudNoAlternateMemoryControllerInfo
    @constant chudNoAlternateIOControllerInfo
    @constant chudNoAlternateOSInfo
    @constant chudInvalidProcessorClass
    @constant chudInvalidProcessorType
    @constant chudInvalidMemoryControllerType
    @constant chudInvalidIOControllerType
    @constant chudInvalidOSType
    @constant --serial communication--
    @constant chudNoSerialPortsDetected
    @constant chudSerialDeviceNameTooLong
    @constant chudOpenSerialPortFailed
    @constant chudModifySerialPortSettingsFailed
    @constant chudOpenTTYDeviceFailed
    @constant chudNoOpenSerialPort
    @constant chudSetTTYattrsFailedCheckErrno
    @constant chudGetTTYattrsFailedCheckErrno
    @constant chudReadSerialTTYFailedCheckErrno
    @constant chudReadSerialTTYRetriesExhaustedCheckErrno
    @constant chudWriteSerialTTYFailedCheckErrno
    @constant chudInvalidDataBuffer
    @constant chudFailedToAllocateSerialPortInfo
    @constant --opaque sample buffer state--
    @constant chudUnsupportedStateVersion
*/

/* status and return codes */
typedef enum {
    // generic
    chudSuccess             	=      0,
    chudFailure			= -10999,
    chudInvalidIndex,
    chudInvalidValue,
    chudInvalidUnits,
    chudInvalidMemoryPointer,
    chudMemAllocFailure,
    chudIOKitFailure,
    chudMachFailure,
    chudInvalidArgument,
    chudFunctionNotImplemented,
    chudInvalidAddress,
            
    // init
    chudBootstrapFailure	= -11999,
    chudUnknownCpu,
    chudNotInitialized,
    chudCleanupMustBeCalledFirst,
    
    // device
    chudBadDeviceID		= -12999,
    chudDeviceNotSupported,
    chudDeviceNotPresent,
    chudSamplingDeviceNotSet,
    
    // pmc
    chudBadPmcID		= -13999,
    chudReservedEvent,
    chudInvalidEvent,
    chudBadFilterMode,
    chudBadPMCMode,
    chudPMItriggerNotSet,
    chudInvalidMUX,
    chudBadInstructionMatchMode,
    chudBadIOPMarkMode,
    chudBadIDUMask,
    chudBadIDUMatch,
    
    // thread/task
    chudCheckPIDFailure		= -14999,
    chudCheckTaskFailure,
    chudCheckThreadFailure,

    // shortcut
    chudNoShortcutFileOpen	= -15999,
    chudNoBuiltinShortcutFile,
    chudNoUserShortcutFile,
    chudInvalidShortcutIndex,
    chudShortcutListFull,
    chudNoShortcutActive,
    chudInvalidShortcutFile,
    chudShortcutSaveFailure,
    chudNoShortcutsForCPUtype,
    chudShortcutsMergedNewCPUDictionary,
    chudShortcutsReadFromSystemPrefs,
    chudShortcutsReadFromUserPrefs,
    
    // hotkey
    chudAddHotkeyFailed		= -16999,
    chudRemoveHotkeyFailed,
    chudNoHotkeyCallback,
    chudInvalidModifierKey,
    
    // sample facility
    chudSampleFacilityInUse	= -17999,
    chudWaitingForSampleFacility,
    chudSampleFacilityNotAcquired,
    chudMapSampleBufferFailure,
    chudNoSamplesAvailable,
    
    // remote facility
    chudRemoteFacilityInUse	= -18999,
    chudRemoteFacilityNoServer,
    chudRemoteFacilityNotAcquired,
    
    // kext
    chudUtilsKextNotLoaded	= -19999,
    chudProfKextNotLoaded,

    // alternate info
    chudNoAlternateProcessorInfo = -20999,
    chudNoAlternateMemoryControllerInfo,
    chudNoAlternateIOControllerInfo,
    chudNoAlternateOSInfo,
    chudInvalidProcessorClass,
    chudInvalidProcessorType,
    chudInvalidMemoryControllerType,
    chudInvalidIOControllerType,
    chudInvalidOSType,
    
    // serial communication
    chudNoSerialPortsDetected = -21999,
    chudSerialDeviceNameTooLong,
    chudOpenSerialPortFailed,
    chudModifySerialPortSettingsFailed,
    chudOpenTTYDeviceFailed,
    chudNoOpenSerialPort,
    chudSetTTYattrsFailedCheckErrno,
    chudGetTTYattrsFailedCheckErrno,
    chudReadSerialTTYFailedCheckErrno,
    chudReadSerialTTYRetriesExhaustedCheckErrno,
    chudWriteSerialTTYFailedCheckErrno,
    chudInvalidDataBuffer,
    chudFailedToAllocateSerialPortInfo,
    // opaque sample buffer state 
    chudUnsupportedStateVersion = -22999,
    
} chud_status_t;


#ifndef CHUD_KEXT
#include <stdio.h>

int	chudInitialize( void );
void	chudCleanup( void );
int	chudIsReady( void ); 

void	chudSetErrorLogFile( FILE *err );
void	chudTrapOnErrors( int doTrapOnErrors );

int	chudGetStatusVal( void ); 
char *	chudGetStatusStr( void ); 

unsigned int chudFrameworkVersion( void );
unsigned int chudProfKextVersion( void );
unsigned int chudUtilsKextVersion( void );

#endif /* !CHUD_KEXT */

#ifdef __cplusplus
}
#endif

#endif /* CHUD_CTRL_H */
