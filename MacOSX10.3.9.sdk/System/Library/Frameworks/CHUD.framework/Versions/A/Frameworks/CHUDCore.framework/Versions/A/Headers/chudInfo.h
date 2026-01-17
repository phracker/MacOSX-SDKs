/*
 * Copyright (c) 2002-2004 Apple Computer, Inc. All rights reserved.
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

#ifndef CHUD_INFO_H
#define CHUD_INFO_H

/*!
  @header CHUD Informational Macros and constants & CHUD Informational Functions
  Much time is spent inquiring about the characteristics, and performance monitoring
  capabilities of a system. The CHUD Info functions provide a mechanism to request
  this information. Information is available for every device that has performance
  monitoring capabilities.

  Use the CHUD Informational Macros and constants to simplify and clarify code that makes use of
  CHUD "Info" calls. 
  
  Most of the information routines require arguments of the chud_device_t type. See the chudCtrl.h documentation for the definitions of these constants.
*/

#include <CHUDCore/chudCtrl.h>
#include <CHUDCore/chudPMCs.h>

#ifdef __cplusplus
extern "C" {
#endif

// PowerPC processor classes

/*!
    @typedef ppc_processor_class_t
    @abstract   The CHUD Tools API provides these enumerations to allow programs to distinguish between the various
    PowerPC (PPC) CPUs that are present in Apple's product line
    @discussion There are four distinct classes of PowerPC processors in service that the CHUD framework 
    is capable of accessing and controlling for the purpose of performance profiling. While there are some older
    systems out there that could potentially be profiled by CHUD Tools we have limited the framework to "modern" 
    PowerPC CPUs that can run MacOS X.
    @constant PPC_CLASS_UNKNOWN it's a PowerPC processor but CHUD Tools cannot profile it
    @constant PPC_750	more commonly called a "G3" processor, found in G3 iMacs, all iBooks, old PowerMacs and PowerBooks.
    @constant PPC_7400	the first "G4" processor, found in Power Macs, and early Ti-books
    @constant PPC_7450	the "G4+" or "G4e" processor found in modern Ti-books, XServes, and PowerMacs
    @constant PPC_970   the "G5" processor found in the PowerMac G5
*/
typedef enum  {
    PPC_CLASS_UNKNOWN	= 0,
    PPC_750  		= 1,
    PPC_7400 		= 2,
    PPC_7450 		= 3,
    PPC_970		= 4
} ppc_processor_class_t;

// PowerPC processor types
/*!
    @typedef ppc_processor_t
    @abstract   The CHUD Tools API provides these enumerations to allow programs to distinguish further between the various
    PowerPC (PPC) CPUs that are present in Apple's product line. 
    @discussion Each Processor Class may have multiple "types" in it.
    there are generally small differences in the design or performance characteristics of each processor type in a class
    usually based on the process used to create the part and the frequency and cache sizes available to the processor type.
    @constant PPC_TYPE_UNKNOWN it's a PowerPC processor but CHUD Tools cannot profile it, or report it's specific characteristics.
    @constant MOT_750	an early Motorola produced G3 processor.
    @constant IBM_750CX	a modification of the Motorola G3 by IBM
    @constant IBM_750FX	a further refinement of the G3 processor by IBM
    @constant IBM_750CXe  the fastest lowset power G3 available from IBM
    @constant MOT_7400  the first G4 from Motorola
    @constant MOT_7410  a subsequent speed boost and power reduced G4 from Motorola
    @constant MOT_7457 512K L2 cache, frequency increased G4e processor with advanced power management from Motorola
    @constant MOT_7450  the second generation G4 architecture from Motorola
    @constant MOT_7455  frequency increased, power reduced G4e processor from Motorola
    @constant MOT_7457 512K L2 cache, frequency increased G4e processor from Motorola
    @constant IBM_970  a third generation PowerPC consumer level processor from IBM
    @constant IBM_970FX 970 core manufactured in IBMÕs 90 nm copper process technology (lower power, smaller die size)
*/
typedef enum  {
    PPC_TYPE_UNKNOWN	= 0,
    MOT_750		= 750,
    IBM_750CX 		= 751,
    IBM_750FX 		= 752,
    IBM_750CXe		= 753,
    MOT_7400 		= 7400,
    MOT_7410 		= 7410,
    MOT_7447A		= 7448,
    MOT_7450 		= 7450,
    MOT_7455 		= 7455,
    MOT_7457		= 7457,
    IBM_970		= 970,
    IBM_970FX		= 975
} ppc_processor_t;

// memory controller types
/*!
    @typedef memory_controller_t
    @abstract   The CHUD Tools API provides these enumerations to allow programs to determine which nort-bridge 
    chipset is installed in a Macintosh, and how to profile it, if possible. 
    @discussion 
    @constant MC_NONE	This constant is used for system modeling, and when the memory controller has no performance monitor counters on it.
    @constant MC_UNIN_UNKNOWN The Apple memory controller type cannot be determined from the available revision information, 
    or modeling of alternate system configurations is desired.
    @constant MC_MPC106 An early PowerPC compatible memory controller from Motorola, CHUD Tools cannot profile this M/C but they are aware of it.
    @constant MC_UNIN10 The first modern Apple memory controller, used in G4 based Macs
    @constant MC_UNIN10_PANGEA This memory controller is part of many G3 iMac chipsets, combined with an I/O controller.
    @constant MC_UNIN15 This memory controller is built into many G4 PowerMacs, and early Ti-PowerBooks
    @constant MC_U2 This memory controller supports DDR memory and is used in modern G4 PowerMacs, and XServes 
    @constant MC_U2_INTREPID This memory controller is part of the G4 iMac chipsets, combined with an I/O controller.
    @constant MC_U3 This memory controller uses a point to point interface between processors and is found in PowerMacs G5s
    @constant MC_U3_HEAVY PowerMac G5 memory controller with support for ECC memory.
*/
typedef enum  {
    MC_NONE		= 0,
    MC_UNIN_UNKNOWN	= 1000,	/* Uni-North (Unknown Type) */
    MC_MPC106		= 106,	/* Motorola MPC106 (Grackle) */
    MC_UNIN10		= 10,	/* Uni-North 1.0 */
    MC_UNIN10_PANGEA	= 11,	/* Uni-North 1.0 (integrated into Pangea) */
    MC_UNIN15		= 15,	/* Uni-North 1.5 */
    MC_U2		= 20,	/* U2 */
    MC_U2_INTREPID	= 21,	/* U2 (integrated into Intrepid) */
    MC_U3		= 30,	/* U3 */
    MC_U3_HEAVY		= 34	/* U3 Heavy */
} memory_controller_t;

// io controller types
/*!
    @typedef io_controller_t
    @abstract   The CHUD Tools API provides these enumerations to allow programs to determine which south-bridge 
    chipset is installed in a Macintosh, and how to profile it, if possible. 
    @discussion 
    @constant IOC_NONE This constant is used for system modeling, and when the I/O controller has no performance monitor counters on it.
    @constant IOC_KEYLARGO_UNKNOWN The Apple I/O controller type cannot be determined from the available revision information, 
    or modeling of alternate system configurations is desired
    @constant IOC_KEYLARGO The first modern Apple I/O controller, used in most G3 and G4 Macs, and XServes.
    @constant IOC_KEYLARGO_PANGEA The Apple I/O controller, as part of a combined chipset used in most G3 iMacs, and G3 portables.
    @constant IOC_KEYLARGO_INTREPID The Apple I/O controller, as part of a combined chipset used in most G4 iMacs, and G4 portables.
    @constant IOC_K2 The Apple I/O controller used in the PowerMac G5
    @constant IOC_K2_UNKNOWN the I/O controller is a K2 variant but currently unsupported by CHUD Tools.
*/
//  @constant IOC_SHASTA Apple I/O controller
typedef enum  {
    IOC_NONE			= 0,
    IOC_KEYLARGO_UNKNOWN 	= 1000,	/* KeyLargo (Unknown Type) */
    IOC_KEYLARGO		= 16,	/* KeyLargo */
    IOC_KEYLARGO_PANGEA		= 17,	/* KeyLargo (integrated into Pangea) */
    IOC_KEYLARGO_INTREPID	= 18,	/* KeyLargo (integrated into Intrepid) */
    IOC_K2			= 32,	/* K2 */
    IOC_K2_UNKNOWN		= 2000	/* K2 (Unknown Type) */
} io_controller_t;

//Operating system types
/*!
    @typedef operating_system_t
    @abstract   The CHUD Tools API provides these enumerations to allow programs to determine which operating system 
    variant is currently running . 
    @discussion 
    @constant OS_NONE
    @constant OS_UNKNOWN
    @constant OS_X_10_0
    @constant OS_X_10_1
    @constant OS_X_10_2
    @constant OS_X_10_3
*/
typedef enum {
    OS_NONE		= 0,
    OS_UNKNOWN		= 1,
    OS_X_10_0		= 4,	/* MacOS X 10.0 */
    OS_X_10_1		= 5,	/* MacOS X 10.1 */
    OS_X_10_2		= 6,	/* MacOS X 10.2 */
    OS_X_10_3		= 7,	/* MacOS X 10.3 */
} operating_system_t;

#define OS_X_CHEETAH	OS_X_10_0
#define OS_X_PUMA	OS_X_10_1
#define OS_X_JAGUAR	OS_X_10_2
#define OS_X_PANTHER	OS_X_10_3

#ifndef CHUD_KEXT
/*!
 @function chudProcessorFreq 
 @discussion return the external clock frequency (Hz) of the cpu(s) in the system
 @param void
 @result float
*/
float   chudProcessorFreq( void );
/*!
 @function  chudTimebaseFreq
 @discussion returns the frequency (Hz) used to mark the passage of
 time in the system.  It's usually 1/4 the system bus-frequency
 but it varies a bit.  SBF / TBF = Bus Cycles/Timebase-'tick'
 @param void
 @result timebase frequency
*/
float	chudTimebaseFreq( void );
/*!
 @function  chudBusFreq
 @discussion returns the frequency (Hz) of the System Bus
 @param void
 @result bus frequency
*/
float	chudBusFreq( void );
/*!
 @function  chudProcessorMHz
 @discussion returns the CPU external clock frequency in megahertz (MHz)
 it's a simple convenience that returns the CPU frequency already divided by a million.
 @param void
 @result chudProcessorFreq/1000000.0 float
*/
float 	chudProcessorMHz( void );

/*!
 @function  chudProcessorCount
 @discussion returns an integer count of the enabled CPUs in the system
 @param void
 @result enabled cpu count
*/
int	chudProcessorCount( void );
/*!
 @function  chudPhysicalProcessorCount
 @discussion returns an integer count of the total CPUs in the system
 @param void
 @result hardware cpu count
*/
int 	chudPhysicalProcessorCount( void );
/*!
 @function chudProcessorType
 @discussion returns an integer representing the 'type' of cpu in the system
 @param dev a processor chud_device_t, like chudCPU1Dev
 @result processor type (see chudInfo.h)
*/
int	chudProcessorType( chud_device_t dev );
/*!
 @function  chudProcessorClass
 @discussion returns an integer representing the class of cpu in the system
 @param dev chud_device_id where dev == chudCPU1Dev, chudCPU2Dev, chudAllCPUDev, or
 chudAltCPU1Dev, chudAltCPU2Dev, or chudAltAllCPUDev
 @result int processor class
*/
int	chudProcessorClass( chud_device_t dev );
/*!
 @function chudProcessorName
 @discussion return a C-string representing the class of processor as the 
 working name given the processor chip during its development.
 @param dev where dev == chudCPU1Dev, chudCPU2Dev, chudAllCPUDev, or
 chudAltCPU1Dev, chudAltCPU2Dev, or chudAltAllCPUDev
 @result (char *)
*/
char *	chudProcessorName( chud_device_t dev );
 /*!
 @function chudProcessorVersion
 @discussion output the unsigned int (4-byte) representation of the contents of the 
 1st CPU's Processor Version Register (PVR)
 @param *vers unsigned int
 @result chudSuccess, chudNotInitialized
 */
int	chudProcessorVersion( unsigned int *vers );
/*!
 @function  chudProcessorRev
 @discussion return the cpu revision data broken down into major
 minor and technology revision values
 @param *major
 @param *minor
 @param *tech
 @result chudSuccess, chudNotInitialized
*/
int	chudProcessorRev( int *major, int *minor, int *tech );
/*!
 @function chudProcessorCacheConfig
 @discussion return the sizes of the available CPU caches and if they are enabled
 NOTE: L1 caches can never be disabled
 @param *iL1Size_p
 @param *dL1Size_p
 @param *L2Size_p
 @param *L2Enabled_p
 @param *L3Size_p
 @param *L3Enabled_p
 @result chudSuccess
 */
int 	chudProcessorCacheConfig(int *iL1Size_p, int *dL1Size_p, int *L2Size_p, 
                                 int *L2Enabled_p, int *L3Size_p, int *L3Enabled_p);
 /*!
 @function chudProcessorPowerSavingConfig
 @discussion return the boolean state of CPU power saving
 @param *napEnabled_p 0=disabled, 1=enabled
 @result chudSuccess
 */
int 	chudProcessorPowerSavingConfig(int *napEnabled_p);

 /*!
 @function chudMCCount
 @discussion returns a count of enabled memory controllers that have PMCs
 that can be accessed
 @param void
 @result count of MC's that are enabled, and have PMC's
 */
int     chudMCCount( void );
 /*!
 @function chudMCRev
 @discussion returns a 4 byte hexadecimal representation of the memory 
 controller's revision number
 @param void
 @result a hex unsigned int
 */
int	chudMCRev( void );
/*!
 @function chudMCType
 @discussion returns a constant that represents the type or class of Memory
 Controller enabled in the system, that has PMC's Chud can access.
 @param dev: chud_device_t where dev == chudMCDev, or chudAltMCDev
 @result See chudInfo.h for valid MC controller types
 */
int 	chudMCType( chud_device_t dev );
 /*!
 @function chudMCName
 @discussion return a C-string representing the class of memory controller 
 @param dev: chud_device_t an MC device chudMCDev, or chudAltMCDev
 @result (char *)
 */
char *	chudMCName( chud_device_t dev );

 /*!
 @function chudIOCCount
 @discussion returns a count of io controllers
 @param void
 @result count of IOCs
 */
int	chudIOCCount(void);
 /*!
 @function chudIOCRev
 @discussion returns a 4 byte hexadecimal representation of the io 
 controller's revision number
 @param void
 @result a hex unsigned int
 */
int	chudIOCRev( void );
 /*!
 @function chudIOCType
 @discussion returns a constant that represents the type or class of IO
 Controller enabled in the system.
 @param dev: chud_device_t where dev == chudIOCDev, or chudAltIOCDev
 @result See chudInfo.h for valid IO controller types
 */
int	chudIOCType( chud_device_t dev );
 /*!
 @function chudIOCName
 @discussion return a C-string representing the class of io controller 
 @param dev: chud_device_id must be chudIOCDev, or chudAltIOCDev
 @result (char *)
 */
char *	chudIOCName( chud_device_t dev );
/*!
 @function chudOSBuild
 @discussion returns the build of the operating system
 @param void
 @result build of the operating system
 */
char *	chudOSBuild( void );
 /*!
 @function chudOSType
 @discussion returns a constant that represents the type or class of Operating
 System
 @param dev: chud_device_t where dev ==  chudOSDev or chudAltOSDev
 @result See chuInfo.h for valid OS types
 */
int	chudOSType( chud_device_t dev );
 /*!
 @function chudOSName
 @discussion returns the product name of the operating system
 @param dev: chud_device_t, where dev ==  chudOSDev or chudAltOSDev
 @result product name of the operating system
 */
char *	chudOSName( chud_device_t dev );
 /*!
 @function chudOSVersion( chud_device_t dev )
 @discussion returns the version of the operating system
 @param dev: chud_device_t where dev ==  chudOSDev or chudAltOSDev
 @result version of the operating system
 */
char *	chudOSVersion( chud_device_t dev );

 /*!
 @function chudPMCCount
 @discussion return the number of Performance Monitor Counters available
 in a system component, either a cpu, a memory controller, OS Device type, or an alternate device type
 @param dev: chud_device_t 
 @result count of available pmc's
*/
int	chudPMCCount( chud_device_t dev);

 /*!
 @function chudEthernetMACAddress
 @discussion returns the hardware ethernet (MAC) address of the
 built-in (primary) ethernet port
 @param void
 @result ethernet MAC address as an array of bytes.
 */
char *	chudPrimaryEnetMACAddress( void );

 /*!
 @function chudMachineClass
 @discussion returns the name of the machine class (e.g. "PowerBook3,5")
 @param void
 @result machine class name
 */
char *	chudMachineClass( void );

/*!
 @function chudSystemMemorySize
 @discussion Returns the amount of memory known to the system (does not include memory hidden from the system with the maxmem=#MB boot arg). Hidden memory is used by the BlizBuffer (sees chudMapBlizBuffer).
 To set the amount of hidden memory in the system use the following command from the Terminal:
   sudo nvram boot-args="maxmem=N"
 where N is the number of MB the system will be aware of.
 @result bytes of memory known to the system
 */
uint64_t chudSystemMemorySize(void);
/*!
 @function chudPhysicalMemorySize
 @discussion Returns the total amount of memory physically installed in the system. Includes any memory known to the operating system as well as any memory hidden from the system with the maxmem=#MB boot arg.
 @result bytes of total memory installed in the system
 */
uint64_t chudPhysicalMemorySize(void);

//functions for setting up alternate device info
 /*!
 @function chudSetAltProcessorInfo
 @discussion change the processor information by setting the class and type to one of 
 the valid choices, but not necessarily the settings that represent the processor in 
 the running system. It does not change the running info settings. This provides a way to inquire about other Macintosh architectures without actually running on every other architecture.
 @param ptype: ppc_processor_t
 @result integer status
 */
int	chudSetAltProcessorInfo( ppc_processor_t ptype );
 /*!
 @function chudSetAltMemCtrlInfo
 @discussion change the memory controller information by setting the class and type
 to one of the valid choices, but not necessarily the settings that represent 
 the mem. controller in the running system. It does not change the running info settings 
 @param mct: memory_controller_t
 @result integer status
 */
int	chudSetAltMemCtrlInfo( memory_controller_t mct );
 /*!
 @function chudSetAltIOCtrlInfo
 @discussion change the processor information by setting the class and type
 to one of the valid choices, but not necessarily the settings that represent 
 the processor in the running system. It does not change the running info settings
 @param ioct: io_controller_t 
 @result integer status
 */
int	chudSetAltIOCtrlInfo( io_controller_t ioct );
 /*!
 @function chudSetAltOSInfo
 @discussion change the processor information by setting the class and type
 to one of the valid choices, but not necessarily the settings that represent 
 the processor in the running system. It does not change the running info settings.
 Except for the availability of OS PMC events,
 there aren't any interesting differences (from the CHUD Tools perspective, at least)
 between different operating system versions.
 @param void
 @result integer status
*/
int 	chudSetAltOSInfo( operating_system_t os );

#endif /* !CHUD_KEXT */

#ifdef __cplusplus
}
#endif

#endif /* CHUD_INFO_H */
