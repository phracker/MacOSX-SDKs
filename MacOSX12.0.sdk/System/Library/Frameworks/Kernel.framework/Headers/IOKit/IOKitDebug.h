/*
 * Copyright (c) 1998-2019 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#ifndef _IOKIT_IOKITDEBUG_H
#define _IOKIT_IOKITDEBUG_H

#include <IOKit/IOTypes.h>


#ifdef __cplusplus

#include <libkern/c++/OSObject.h>
#include <libkern/c++/OSDictionary.h>
#include <libkern/c++/OSSerialize.h>

class IOKitDiagnostics : public OSObject
{
	OSDeclareDefaultStructors(IOKitDiagnostics);

public:
	static OSObject * diagnostics( void );
	virtual bool serialize(OSSerialize *s) const APPLE_KEXT_OVERRIDE;
private:
	static void updateOffset( OSDictionary * dict,
	    UInt64 value, const char * name );
};

#endif /* __cplusplus */

enum {
	// loggage
	kIOLogAttach        =         0x00000001ULL,
	kIOLogProbe         =         0x00000002ULL,
	kIOLogStart         =         0x00000004ULL,
	kIOLogRegister      =         0x00000008ULL,
	kIOLogMatch         =         0x00000010ULL,
	kIOLogConfig        =         0x00000020ULL,
	kIOLogYield         =         0x00000040ULL,
	kIOLogPower         =         0x00000080ULL,
	kIOLogMapping       =         0x00000100ULL,
	kIOLogCatalogue     =         0x00000200ULL,
	kIOLogTracePower    =         0x00000400ULL,  // Obsolete: Use iotrace=0x00000400ULL to enable now
	kIOLogDebugPower    =         0x00000800ULL,
	kIOLogServiceTree   =         0x00001000ULL,
	kIOLogDTree         =         0x00002000ULL,
	kIOLogMemory        =         0x00004000ULL,
	kIOLogKextMemory    =         0x00008000ULL,
	kOSLogRegistryMods  =         0x00010000ULL,// Log attempts to modify registry collections
	kIOLogPMRootDomain  =         0x00020000ULL,
	kOSRegistryModsMode =         0x00040000ULL,// Change default registry modification handling - panic vs. log
//    kIOTraceIOService   =         0x00080000ULL,  // Obsolete: Use iotrace=0x00080000ULL to enable now
	kIOLogHibernate     =         0x00100000ULL,
	kIOStatistics       =         0x04000000ULL,
	kIOSleepWakeWdogOff =         0x40000000ULL,
	kIOKextSpinDump     =         0x80000000ULL,

	// debug aids - change behaviour
	kIONoFreeObjects    =         0x00100000ULL,
//    kIOLogSynchronous   =         0x00200000ULL,  // IOLog completes synchronously -- obsolete
	kIOTracking         =         0x00400000ULL,
	kIOWaitQuietPanics  =         0x00800000ULL,
	kIOWaitQuietBeforeRoot =      0x01000000ULL,
	kIOTrackingBoot     =         0x02000000ULL,

	_kIODebugTopFlag    = 0x8000000000000000ULL// force enum to be 64 bits
};

enum {
	kIOKitDebugUserOptions = 0
	    | kIOLogAttach
	    | kIOLogProbe
	    | kIOLogStart
	    | kIOLogRegister
	    | kIOLogMatch
	    | kIOLogConfig
	    | kIOLogYield
	    | kIOLogPower
	    | kIOLogMapping
	    | kIOLogCatalogue
	    | kIOLogTracePower
	    | kIOLogDebugPower
	    | kOSLogRegistryMods
	    | kIOLogPMRootDomain
	    | kOSRegistryModsMode
	    | kIOLogHibernate
	    | kIOSleepWakeWdogOff
	    | kIOKextSpinDump
	    | kIOWaitQuietPanics
};

enum {
	kIOTraceInterrupts              =               0x00000001ULL,  // Trace primary interrupts
	kIOTraceWorkLoops               =               0x00000002ULL,  // Trace workloop activity
	kIOTraceEventSources    =               0x00000004ULL,  // Trace non-passive event sources
	kIOTraceIntEventSource  =               0x00000008ULL,  // Trace IOIES and IOFIES sources
	kIOTraceCommandGates    =               0x00000010ULL,  // Trace command gate activity
	kIOTraceTimers                  =               0x00000020ULL,  // Trace timer event source activity

	kIOTracePowerMgmt               =               0x00000400ULL,  // Trace power management changes

	kIOTraceIOService       =               0x00080000ULL,  // registerService/termination

	kIOTraceCompatBootArgs  =               kIOTraceIOService | kIOTracePowerMgmt
};

enum {
	kIODKEnable             = 0x00000001ULL,
	kIODKLogSetup   = 0x00000002ULL,
	kIODKLogIPC             = 0x00000004ULL,
	kIODKLogPM             = 0x00000008ULL,
	kIODKLogMessages = 0x00000010ULL,

	kIODKDisablePM = 0x000000100ULL,
	kIODKDisableDextLaunch = 0x00001000ULL,
	kIODKDisableDextTag    = 0x00002000ULL,
	kIODKDisableCDHashChecking  = 0x00004000ULL,
	kIODKDisableEntitlementChecking = 0x00008000ULL,
	kIODKDisableCheckInTokenVerification = 0x00010000ULL,
};


extern SInt64    gIOKitDebug;
extern SInt64    gIOKitTrace;
extern SInt64    gIODKDebug;

#ifdef __cplusplus

typedef kern_return_t (*IOCoreAnalyticsSendEventProc)(
	uint64_t       options,
	OSString     * eventName,
	OSDictionary * eventPayload);


#endif /* __cplusplus */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
class IORegistryPlane;
#endif

extern void    IOPrintPlane(
#ifdef __cplusplus
	const IORegistryPlane * plane
#else
	const struct IORegistryPlane * plane
#endif
	);
#ifndef _OSCPPDEBUG_H
extern void    OSPrintMemory( void );
#endif
#define IOPrintMemory OSPrintMemory

#if defined(KERNEL) && defined(__cplusplus)
kern_return_t
IOSetCoreAnalyticsSendEventProc(IOCoreAnalyticsSendEventProc proc);
#endif /* defined(KERNEL) && defined(__cplusplus) */

#define kIOKitDiagnosticsClientClassName "IOKitDiagnosticsClient"

enum{
	kIOKitDiagnosticsClientType = 0x99000002
};


struct IOKitDiagnosticsParameters {
	size_t    size;
	uint64_t  value;
	uint32_t  options;
	uint32_t  tag;
	uint32_t  zsize;
	uint32_t  reserved[8];
};
typedef struct IOKitDiagnosticsParameters IOKitDiagnosticsParameters;

enum{
	kIOTrackingCallSiteBTs = 16,
};

struct IOTrackingCallSiteInfo {
	uint32_t          count;
	pid_t             addressPID;
	mach_vm_address_t address;
	mach_vm_size_t    size[2];
	pid_t             btPID;
	mach_vm_address_t bt[2][kIOTrackingCallSiteBTs];
};

#define kIOMallocTrackingName   "IOMalloc"
#define kIOWireTrackingName     "IOWire"
#define kIOMapTrackingName      "IOMap"


enum{
	kIOTrackingExcludeNames      = 0x00000001,
};

enum{
	kIOTrackingGetTracking       = 0x00000001,
	kIOTrackingGetMappings       = 0x00000002,
	kIOTrackingResetTracking     = 0x00000003,
	kIOTrackingStartCapture      = 0x00000004,
	kIOTrackingStopCapture       = 0x00000005,
	kIOTrackingSetMinCaptureSize = 0x00000006,
	kIOTrackingLeaks             = 0x00000007,
	kIOTrackingInvalid           = 0xFFFFFFFE,
};


#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* ! _IOKIT_IOKITDEBUG_H */
