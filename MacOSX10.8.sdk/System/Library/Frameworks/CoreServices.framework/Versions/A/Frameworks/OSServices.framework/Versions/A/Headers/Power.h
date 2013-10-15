/*
     File:       OSServices/Power.h
 
     Contains:   *** DEPRECATED *** Power Manager Interfaces.
 
     Copyright:  (c) 1990-2011 Apple Inc. All rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __POWER__
#define __POWER__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
#endif

#ifndef __MULTIPROCESSING__
#include <CarbonCore/Multiprocessing.h>
#endif

#ifndef __MACERRORS__
#include <CarbonCore/MacErrors.h>
#endif



#include <Availability.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

enum {
                                        /* commands to SleepQRec sleepQProc */
  kSleepRequest                 = 1,
  kSleepDemand                  = 2,
  kSleepWakeUp                  = 3,
  kSleepRevoke                  = 4,
  kSleepUnlock                  = 4,
  kSleepDeny                    = 5,    /* A non-zero value clients can use to deny requests*/
  kSleepNow                     = 6,
  kDozeDemand                   = 7,
  kDozeWakeUp                   = 8,
  kDozeRequest                  = 9,    /* additional messages for Power Mgr 2.0*/
  kEnterStandby                 = 10,   /* Idle Queue Only*/
  kEnterRun                     = 11,   /* Idle Queue Only*/
  kSuspendRequest               = 12,
  kSuspendDemand                = 13,
  kSuspendRevoke                = 14,
  kSuspendWakeUp                = 15,
  kGetPowerLevel                = 16,
  kSetPowerLevel                = 17,
  kDeviceInitiatedWake          = 18,
  kWakeToDoze                   = 19,
  kDozeToFullWakeUp             = 20,
  kGetPowerInfo                 = 21,
  kGetWakeOnNetInfo             = 22,
  kSuspendWakeToDoze            = 23,
  kEnterIdle                    = 24,   /* Idle Queue Only*/
  kStillIdle                    = 25,   /* Idle Queue Only*/
  kExitIdle                     = 26    /* Idle Queue Only*/
};

enum {
                                        /* SleepQRec.sleepQFlags */
  noCalls                       = 1,
  noRequest                     = 2,
  slpQType                      = 16,
  sleepQType                    = 16
};

/* System Activity Selectors */
/* Notes:  The IdleActivity selector is not available unless the hasAggressiveIdling PMFeatures bit is set.     */
/* Use IdleActivity where you used to use OverallAct if necessary. OverallAct will only delay power cycling     */
/* if it's enabled, and will delay sleep by a small amount when hasAggressiveIdling is set.  Don't use          */
/* IdleActivity unless hasAggressiveIdling is set; when hasAggressiveIdling is not set, the use of IdleActivity */
/* is undefined, and well do different things depending on which Power Manager is currently running.            */
enum {
  OverallAct                    = 0,    /* Delays idle sleep by small amount                          */
  UsrActivity                   = 1,    /* Delays idle sleep and dimming by timeout time              */
  NetActivity                   = 2,    /* Delays idle sleep and power cycling by small amount        */
  HDActivity                    = 3,    /* Delays hard drive spindown and idle sleep by small amount  */
  IdleActivity                  = 4     /* Delays idle sleep by timeout time                          */
};

typedef struct SleepQRec                SleepQRec;
typedef SleepQRec *                     SleepQRecPtr;
typedef CALLBACK_API( long , SleepQProcPtr )(long message, SleepQRecPtr qRecPtr);
typedef STACK_UPP_TYPE(SleepQProcPtr)   SleepQUPP;

/*
 *  NewSleepQUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern SleepQUPP
NewSleepQUPP(SleepQProcPtr userRoutine)                       __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);


/*
 *  DisposeSleepQUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeSleepQUPP(SleepQUPP userUPP)                           __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);


/*
 *  InvokeSleepQUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern long
InvokeSleepQUPP(
  long          message,
  SleepQRecPtr  qRecPtr,
  SleepQUPP     userUPP)                                      __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);


#ifdef __cplusplus
  inline SleepQUPP                                            NewSleepQUPP(SleepQProcPtr userRoutine) { return userRoutine; }
  inline void                                                 DisposeSleepQUPP(SleepQUPP) { }
  inline long                                                 InvokeSleepQUPP(long message, SleepQRecPtr qRecPtr, SleepQUPP userUPP) { return (*userUPP)(message, qRecPtr); }
#else
  #define NewSleepQUPP(userRoutine)                           ((SleepQUPP)userRoutine)
  #define DisposeSleepQUPP(userUPP)
  #define InvokeSleepQUPP(message, qRecPtr, userUPP)          (*userUPP)(message, qRecPtr)
#endif

struct SleepQRec {
  SleepQRecPtr        sleepQLink;             /* pointer to next queue element           */
  short               sleepQType;             /* queue element type (must be SleepQType) */
  SleepQUPP           sleepQProc;             /* pointer to sleep universal proc ptr     */
  short               sleepQFlags;            /* flags                                   */
};

/*
 *  GetCPUSpeed()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use sysctlbyname("hw.cpufrequency"). Found in <sys/sysctl.h>.
 *  
 *  Discussion:
 *    GetCPUSpeed() returns the current effective clock speed of the
 *    CPU in megahertz.
 *  
 *  Result:
 *    the current effective clock speed of the CPU in megahertz.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.8
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
GetCPUSpeed(void)                                             __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_8,__IPHONE_NA,__IPHONE_NA);


/*
 *  SleepQInstall()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use IORegisterForSystemPower(). Found in <IOKit/pwr_mgt/IOPMLib.h>.
 *  
 *  Discussion:
 *    Adds an entry to the sleep queue.
 *  
 *  Parameters:
 *    
 *    qRecPtr:
 *      A pointer to a sleep queue record to be installed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.8
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SleepQInstall(SleepQRecPtr qRecPtr)                           __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_8,__IPHONE_NA,__IPHONE_NA);


/*
 *  SleepQRemove()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use IODeregisterForSystemPower(). Found in <IOKit/pwr_mgt/IOPMLib.h>.
 *  
 *  Discussion:
 *    Remove an entry from the sleep queue.
 *  
 *  Parameters:
 *    
 *    qRecPtr:
 *      A pointer to a sleep queue record to be removed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.8
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SleepQRemove(SleepQRecPtr qRecPtr)                            __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_8,__IPHONE_NA,__IPHONE_NA);


/*
 *  MaximumProcessorSpeed()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use sysctlbyname("hw.cpufrequency_max"). Found in <sys/sysctl.h>.
 *  
 *  Discussion:
 *    MaximumProcessorSpeed() returns the maximum effective clock speed
 *    of the CPU in megahertz.
 *  
 *  Result:
 *    the maximum effective clock speed of the CPU in megahertz.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.8
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern short 
MaximumProcessorSpeed(void)                                   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_8,__IPHONE_NA,__IPHONE_NA);


/*
 *  MinimumProcessorSpeed()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use sysctlbyname("hw.cpufrequency_min"). Found in <sys/sysctl.h>.
 *  
 *  Discussion:
 *    MinimumProcessorSpeed() returns the minimum effective clock speed
 *    of the CPU in megahertz. Before Mac OS X 10.4, this function
 *    always returns the maximum cpu speed, not the minimum as expected.
 *  
 *  Result:
 *    the minimum effective clock speed of the CPU in megahertz.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework but deprecated in 10.8
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern short 
MinimumProcessorSpeed(void)                                   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_8,__IPHONE_NA,__IPHONE_NA);


/*
 *  CurrentProcessorSpeed()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use sysctlbyname("hw.cpufrequency"). Found in <sys/sysctl.h>.
 *  
 *  Discussion:
 *    CurrentProcessorSpeed() returns the current effective clock speed
 *    of the CPU in megahertz. Before Mac OS X 10.4, this function
 *    always returns the maximum cpu speed, not the actual current
 *    speed the processor is running at.  One MHz represents one
 *    million cycles per second.
 *  
 *  Result:
 *    the current effective clock speed of the CPU in megahertz.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.8
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern short 
CurrentProcessorSpeed(void)                                   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_8,__IPHONE_NA,__IPHONE_NA);


/*
 *  BatteryCount()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use IOPowerSources API. Found in <IOKit/ps/IOPowerSources.h>.
 *  
 *  Summary:
 *    Return the count of batteries installed on this computer.
 *  
 *  Result:
 *    the count of batteries installed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.8
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern short 
BatteryCount(void)                                            __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_8,__IPHONE_NA,__IPHONE_NA);


/*
 *  UpdateSystemActivity()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use IOPMAssertionCreateWithName(). Found in <IOKit/pwr_mgt/IOPMLib.h>.
 *  
 *  Summary:
 *    You can use the UpdateSystemActivity function to notify the Power
 *    Manager that activity has taken place.
 *
 *  Discussion:
 *    The UpdateSystemActivity function is used to notify the Power
 *    Manager that activity has taken place and the timers used to
 *    measure idle time should be updated to the time of this call.
 *    This function can be used by device drivers to prevent the
 *    computer from entering a low-power mode while critical activity
 *    is taking place on a particular device. The function is passed a
 *    parameter indicating the type of activity that has
 *    occurred.
 *
 *    This function is slightly different from DelaySystemIdle, which
 *    should be used to prevent sleep or idle during a critical
 *    section. UpdateSystemActivity simply updates the tick count for
 *    the activity type selected. Conversely, DelaySystemIdle actually
 *    moves the counter to some number of ticks into the future, which
 *    allows the caller to go off and do somethingwithout fear of
 *    idling.
 *
 *    The valid types of activity are:
 *    Value Name       Value        Description
 *    OverallAct       0            general type of activity
 *    UsrActivity      1            user activity (i.e.keyboard or mouse)
 *    NetActivity      2            interaction with network(s)
 *    HDActivity       3            hard disk or storage device in use
 *
 *  Parameters:
 *
 *    activity:
 *      The type of activity which has occurred.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.8
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern OSErr 
UpdateSystemActivity(UInt8 activity)                          __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_8,__IPHONE_NA,__IPHONE_NA);


#if !__LP64__

/* definitions for HDQueueElement.hdFlags   */
enum {
  kHDQueuePostBit               = 0,    /* 1 = call this routine on the second pass     */
  kHDQueuePostMask              = (1 << kHDQueuePostBit)
};

enum {
                                        /* depreciated commands to SleepQRec sleepQProc */
  sleepRequest                  = kSleepRequest,
  sleepDemand                   = kSleepDemand,
  sleepWakeUp                   = kSleepWakeUp,
  sleepRevoke                   = kSleepRevoke,
  sleepUnlock                   = kSleepUnlock,
  sleepDeny                     = kSleepDeny,
  sleepNow                      = kSleepNow,
  dozeDemand                    = kDozeDemand,
  dozeWakeUp                    = kDozeWakeUp,
  dozeRequest                   = kDozeRequest,
  enterStandby                  = kEnterStandby,
  enterRun                      = kEnterRun,
  suspendRequestMsg             = kSuspendRequest,
  suspendDemandMsg              = kSuspendDemand,
  suspendRevokeMsg              = kSuspendRevoke,
  suspendWakeUpMsg              = kSuspendWakeUp,
  getPowerLevel                 = kGetPowerLevel,
  setPowerLevel                 = kSetPowerLevel
};

/* Power Handler func messages */
typedef UInt32                          PowerLevel;
/* Power levels corresponding to PCI Bus Power Management Interface Spec (PMIS) */
enum {
  kPMDevicePowerLevel_On        = 0,    /* fully-powered 'On' state (D0 state) */
  kPMDevicePowerLevel_D1        = 1,    /* not used by Apple system SW         */
  kPMDevicePowerLevel_D2        = 2,    /* not used by Apple system SW         */
  kPMDevicePowerLevel_Off       = 3     /* main PCI bus power 'Off', but PCI standby power available (D3cold state) */
};


/* bits in bitfield returned by PMFeatures */
enum {
  hasWakeupTimer                = 0,    /* 1=wakeup timer is supported                           */
  hasSharedModemPort            = 1,    /* 1=modem port shared by SCC and internal modem         */
  hasProcessorCycling           = 2,    /* 1=processor cycling is supported                      */
  mustProcessorCycle            = 3,    /* 1=processor cycling should not be turned off          */
  hasReducedSpeed               = 4,    /* 1=processor can be started up at reduced speed        */
  dynamicSpeedChange            = 5,    /* 1=processor speed can be switched dynamically         */
  hasSCSIDiskMode               = 6,    /* 1=SCSI Disk Mode is supported                         */
  canGetBatteryTime             = 7,    /* 1=battery time can be calculated                      */
  canWakeupOnRing               = 8,    /* 1=can wakeup when the modem detects a ring            */
  hasDimmingSupport             = 9,    /* 1=has dimming support built in (DPMS standby by default) */
  hasStartupTimer               = 10,   /* 1=startup timer is supported                          */
  hasChargeNotification         = 11,   /* 1=client can determine of charge connect status change notifications available */
  hasDimSuspendSupport          = 12,   /* 1=supports dimming LCD and CRT to DPMS suspend state  */
  hasWakeOnNetActivity          = 13,   /* 1=hardware supports wake on network activity          */
  hasWakeOnLid                  = 14,   /* 1=hardware can wake when opened                       */
  canPowerOffPCIBus             = 15,   /* 1=hardware can power off PCI bus during sleep if cards allow */
  hasDeepSleep                  = 16,   /* 1=hardware supports deep sleep (hibernation) mode     */
  hasSleep                      = 17,   /* 1=hardware supports normal (PowerBook-like) sleep     */
  supportsServerModeAPIs        = 18,   /* 1=hardware supports server mode API routines          */
  supportsUPSIntegration        = 19,   /* 1=hardware support UPS integration and reporting      */
  hasAggressiveIdling           = 20,   /* 1=Power Manager only resets OverallAct on UsrActvity  */
  supportsIdleQueue             = 21    /* 1=Power Manager supports the idle queue               */
};

enum {
  HDPwrQType                    = 0x4844, /* 'HD' hard disk spindown queue element type  */
  PMgrStateQType                = 0x504D /* 'PM' Power Manager state queue element type  */
};

/* client notification bits in PMgrQueueElement.pmNotifyBits */
enum {
  pmSleepTimeoutChanged         = 0,
  pmSleepEnableChanged          = 1,
  pmHardDiskTimeoutChanged      = 2,
  pmHardDiskSpindownChanged     = 3,
  pmDimmingTimeoutChanged       = 4,
  pmDimmingEnableChanged        = 5,
  pmDiskModeAddressChanged      = 6,
  pmProcessorCyclingChanged     = 7,
  pmProcessorSpeedChanged       = 8,
  pmWakeupTimerChanged          = 9,
  pmStartupTimerChanged         = 10,
  pmHardDiskPowerRemovedbyUser  = 11,
  pmChargeStatusChanged         = 12,
  pmPowerLevelChanged           = 13,
  pmWakeOnNetActivityChanged    = 14
};

enum {
  pmSleepTimeoutChangedMask        = (1 << pmSleepTimeoutChanged),
  pmSleepEnableChangedMask         = (1 << pmSleepEnableChanged),
  pmHardDiskTimeoutChangedMask     = (1 << pmHardDiskTimeoutChanged),
  pmHardDiskSpindownChangedMask    = (1 << pmHardDiskSpindownChanged),
  pmDimmingTimeoutChangedMask      = (1 << pmDimmingTimeoutChanged),
  pmDimmingEnableChangedMask       = (1 << pmDimmingEnableChanged),
  pmDiskModeAddressChangedMask     = (1 << pmDiskModeAddressChanged),
  pmProcessorCyclingChangedMask    = (1 << pmProcessorCyclingChanged),
  pmProcessorSpeedChangedMask      = (1 << pmProcessorSpeedChanged),
  pmWakeupTimerChangedMask         = (1 << pmWakeupTimerChanged),
  pmStartupTimerChangedMask        = (1 << pmStartupTimerChanged),
  pmHardDiskPowerRemovedbyUserMask = (1 << pmHardDiskPowerRemovedbyUser),
  pmChargeStatusChangedMask        = (1 << pmChargeStatusChanged),
  pmPowerLevelChangedMask          = (1 << pmPowerLevelChanged),
  pmWakeOnNetActivityChangedMask   = (1 << pmWakeOnNetActivityChanged)
};


typedef struct HDQueueElement                         HDQueueElement;
typedef struct PMgrQueueElement                       PMgrQueueElement;
typedef CALLBACK_API( void , HDSpindownProcPtr )      (HDQueueElement * theElement);
typedef CALLBACK_API( void , PMgrStateChangeProcPtr ) (PMgrQueueElement *theElement, long stateBits);
typedef STACK_UPP_TYPE(HDSpindownProcPtr)             HDSpindownUPP;
typedef STACK_UPP_TYPE(PMgrStateChangeProcPtr)        PMgrStateChangeUPP;

struct HDQueueElement {
  struct HDQueueElement * hdQLink;            /* pointer to next queue element           */
  short               hdQType;                /* queue element type (must be HDPwrQType) */
  short               hdFlags;                /* miscellaneous flags                     */
  HDSpindownUPP       hdProc;                 /* pointer to routine to call              */
  long                hdUser;                 /* user-defined (variable storage, etc.)   */
};

struct PMgrQueueElement {
  struct PMgrQueueElement * pmQLink;          /* pointer to next queue element               */
  short               pmQType;                /* queue element type (must be PMgrStateQType) */
  short               pmFlags;                /* miscellaneous flags                         */
  long                pmNotifyBits;           /* bitmap of which changes to be notified for  */
  PMgrStateChangeUPP  pmProc;                 /* pointer to routine to call                  */
  long                pmUser;                 /* user-defined (variable storage, etc.)       */
};


/*
 *  SetSpindownDisable()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern void 
SetSpindownDisable(Boolean setDisable)                        __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);


/*
 *  PMSelectorCount()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern short 
PMSelectorCount(void)                                         __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);


/*
 *  PMFeatures()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern UInt32 
PMFeatures(void)                                              __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);


/*
 *  SetProcessorSpeed()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern Boolean 
SetProcessorSpeed(Boolean fullSpeed)                          __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);


/*
 *  FullProcessorSpeed()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern Boolean 
FullProcessorSpeed(void)                                      __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);


/*
 *  NewHDSpindownUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern HDSpindownUPP
NewHDSpindownUPP(HDSpindownProcPtr userRoutine)               __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);


/*
 *  NewPMgrStateChangeUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern PMgrStateChangeUPP
NewPMgrStateChangeUPP(PMgrStateChangeProcPtr userRoutine)     __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);


/*
 *  DisposeHDSpindownUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeHDSpindownUPP(HDSpindownUPP userUPP)                   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);


/*
 *  DisposePMgrStateChangeUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposePMgrStateChangeUPP(PMgrStateChangeUPP userUPP)         __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);


/*
 *  InvokeHDSpindownUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeHDSpindownUPP(
  HDQueueElement *  theElement,
  HDSpindownUPP     userUPP)                                  __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);


/*
 *  InvokePMgrStateChangeUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokePMgrStateChangeUPP(
  PMgrQueueElement *  theElement,
  long                stateBits,
  PMgrStateChangeUPP  userUPP)                                __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);


#ifdef __cplusplus
  inline HDSpindownUPP                                        NewHDSpindownUPP(HDSpindownProcPtr userRoutine) { return userRoutine; }
  inline PMgrStateChangeUPP                                   NewPMgrStateChangeUPP(PMgrStateChangeProcPtr userRoutine) { return userRoutine; }
  inline void                                                 DisposeHDSpindownUPP(HDSpindownUPP) { }
  inline void                                                 DisposePMgrStateChangeUPP(PMgrStateChangeUPP) { }
  inline void                                                 InvokeHDSpindownUPP(HDQueueElement * theElement, HDSpindownUPP userUPP) { (*userUPP)(theElement); }
  inline void                                                 InvokePMgrStateChangeUPP(PMgrQueueElement * theElement, long stateBits, PMgrStateChangeUPP userUPP) { (*userUPP)(theElement, stateBits); }
#else
  #define NewHDSpindownUPP(userRoutine)                       ((HDSpindownUPP)userRoutine)
  #define NewPMgrStateChangeUPP(userRoutine)                  ((PMgrStateChangeUPP)userRoutine)
  #define DisposeHDSpindownUPP(userUPP)
  #define DisposePMgrStateChangeUPP(userUPP)
  #define InvokeHDSpindownUPP(theElement, userUPP)            (*userUPP)(theElement)
  #define InvokePMgrStateChangeUPP(theElement, stateBits, userUPP) (*userUPP)(theElement, stateBits)
#endif


#endif  /* !__LP64__ */

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __POWER__ */

