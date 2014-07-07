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

#ifndef CHUD_INFO_H
#define CHUD_INFO_H

/*!
  @header CHUD Informational Macros and constants
  Use the CHUD Informational Macros and constants to simplify and clarify code that makes use of
  CHUD "Info" calls. Much time is spent inquiring about the characteristics, and performance 
  monitoring capabilities of a system. The CHUD Info functions provide a mechanism to request 
  this information. Information is available for every device that has performance monitoring
  capabilities.
*/

#include <CHUD/chudCtrl.h>
#include <CHUD/chudPMCs.h>

#ifdef __cplusplus
extern "C" {
#endif

// PowerPC processor classes

/*!
    @typedef ppc_processor_class_t
    @abstract   The CHUD API provides these enumerations to allow programs to distinguish between the various
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
    @abstract   The CHUD API provides these enumerations to allow programs to distinguish further between the various
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
    @constant MOT_7450  the second generation G4 architecture from Motorola
    @constant MOT_7455  frequency increased, power reduced G4e processor from Motorola
    @constant IBM_970  a third generation PowerPC consumer level processor from IBM
*/
typedef enum  {
    PPC_TYPE_UNKNOWN	= 0,
    MOT_750		= 750,
    IBM_750CX 		= 751,
    IBM_750FX 		= 752,
    IBM_750CXe		= 753,
    MOT_7400 		= 7400,
    MOT_7410 		= 7410,
    MOT_7450 		= 7450,
    MOT_7455 		= 7455,
    IBM_970		= 970
} ppc_processor_t;

// memory controller types
/*!
    @typedef memory_controller_t
    @abstract   The CHUD API provides these enumerations to allow programs to determine which nort-bridge 
    chipset is installed in a Macintosh, and how to profile it, if possible. 
    @discussion 
    @constant MC_NONE	This constant is used for system modeling, and when the memory controller has no performance monitor counters on it.
    @constant MC_UNIN_UNKNOWN The Apple memory controller type cannot be determined from the available revision information, 
    or modeling of alternate system configurations is desired.
    @constant MC_MPC106 An early PowerPC compatible memory controller from Motorola, CHUD Tools cannot profile this M/C but they are aware of it.
    @constant MC_UNIN10 The first modern Apple memory controller, used in G4 based Macs
    @constant MC_UNIN10_PANGEA This memory controller is part of many G3 iMac chipsets, combined with an I/O controller.
    @constant MC_UNIN15 This memory controller is built into many G4 PowerMacs, and early Ti-PowerBooks
    @constant MC_UNIN20 This memory controller supports DDR memory and is used in modern G4 PowerMacs, and XServes 
    @constant MC_UNIN20_INTREPID This memory controller is part of the G4 iMac chipsets, combined with an I/O controller.
    @constant MC_UNIN30 This memory controller uses a point to point interface between processors and is found in PowerMacs G5s
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
    MC_U3		= 30	/* U3 */
} memory_controller_t;

// io controller types
/*!
    @typedef io_controller_t
    @abstract   The CHUD API provides these enumerations to allow programs to determine which south-bridge 
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
    @abstract   The CHUD API provides these enumerations to allow programs to determine which operating system 
    variant is currently running . 
    @discussion 
    @constant OS_NONE
    @constant OS_UNKNOWN
    @constant OS_X_10_0
    @constant OS_X_10_1
    @constant OS_X_10_2
    @constant OS_X_PANTHER
*/
typedef enum {
    OS_NONE		= 0,
    OS_UNKNOWN		= 1,
    OS_X_10_0		= 4,	/* MacOS X 10.0 */
    OS_X_10_1		= 5,	/* MacOS X 10.1 */
    OS_X_10_2		= 6,	/* MacOS X 10.2 */
    OS_X_PANTHER	= 7,	/* MacOS X 10.3 */
} operating_system_t;

#ifndef CHUD_KEXT
float   chudProcessorFreq( void );
float	chudTimebaseFreq( void );
float	chudBusFreq( void );
float 	chudProcessorMHz( void );

int	chudProcessorCount( void );
int	chudProcessorType( chud_device_t dev );
int	chudProcessorClass( chud_device_t dev );
char *	chudProcessorName( chud_device_t dev );
int	chudProcessorVersion( unsigned int *vers );
int	chudProcessorRev( int *major, int *minor, int *tech );
int 	chudProcessorCacheConfig(int *iL1Size_p, int *dL1Size_p, int *L2Size_p, 
                                 int *L2Enabled_p, int *L3Size_p, int *L3Enabled_p);
int 	chudProcessorPowerSavingConfig(int *napEnabled_p);

int     chudMCCount( void );
int	chudMCRev( void );
int 	chudMCType( chud_device_t dev );
char *	chudMCName( chud_device_t dev );

int	chudIOCCount(void);
int	chudIOCRev( void );
int	chudIOCType( chud_device_t dev );
char *	chudIOCName( chud_device_t dev );

char *	chudOSBuild( void );
int	chudOSType( chud_device_t dev );
char *	chudOSName( chud_device_t dev );
char *	chudOSVersion( chud_device_t dev );

int	chudPMCCount( chud_device_t dev);

char *	chudPrimaryEnetMACAddress( void );

char *	chudMachineClass( void );

uint64_t chudSystemMemorySize(void);
uint64_t chudPhysicalMemorySize(void);

//functions for setting up alternate device info
int	chudSetAltProcessorInfo( ppc_processor_t ptype );
int	chudSetAltMemCtrlInfo( memory_controller_t mct );
int	chudSetAltIOCtrlInfo( io_controller_t ioct );
int 	chudSetAltOSInfo( operating_system_t os );

#endif /* !CHUD_KEXT */

#ifdef __cplusplus
}
#endif

#endif /* CHUD_INFO_H */
