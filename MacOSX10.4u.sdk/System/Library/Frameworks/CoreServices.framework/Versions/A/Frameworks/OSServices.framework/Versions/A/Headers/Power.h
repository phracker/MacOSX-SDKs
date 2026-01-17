/*
     File:       OSServices/Power.h
 
     Contains:   Power Manager Interfaces.
 
     Version:    OSServices-101.1~790
 
     Copyright:  © 1990-2006 by Apple Computer, Inc.  All rights reserved
 
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

#ifndef __NAMEREGISTRY__
#include <CarbonCore/NameRegistry.h>
#endif

#ifndef __MACERRORS__
#include <CarbonCore/MacErrors.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

enum {
                                        /* Bit positions for ModemByte */
  modemOnBit                    = 0,
  ringWakeUpBit                 = 2,
  modemInstalledBit             = 3,
  ringDetectBit                 = 4,
  modemOnHookBit                = 5
};

enum {
                                        /* masks for ModemByte */
  modemOnMask                   = 0x01,
  ringWakeUpMask                = 0x04,
  modemInstalledMask            = 0x08,
  ringDetectMask                = 0x10,
  modemOnHookMask               = 0x20
};

enum {
                                        /* bit positions for BatteryByte */
  chargerConnBit                = 0,
  hiChargeBit                   = 1,
  chargeOverFlowBit             = 2,
  batteryDeadBit                = 3,
  batteryLowBit                 = 4,
  connChangedBit                = 5
};

enum {
                                        /* masks for BatteryByte */
  chargerConnMask               = 0x01,
  hiChargeMask                  = 0x02,
  chargeOverFlowMask            = 0x04,
  batteryDeadMask               = 0x08,
  batteryLowMask                = 0x10,
  connChangedMask               = 0x20
};

enum {
                                        /* bit positions for SoundMixerByte */
  MediaBaySndEnBit              = 0,
  PCISndEnBit                   = 1,
  ZVSndEnBit                    = 2,
  PCCardSndEnBit                = 3
};

enum {
                                        /* masks for SoundMixerByte */
  MediaBaySndEnMask             = 0x01,
  PCISndEnMask                  = 0x02,
  ZVSndEnMask                   = 0x04,
  PCCardSndEnMask               = 0x08
};

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
  kPMDevicePowerLevel_On        = 0,    /* fully-powered 'On' state (D0 state)    */
  kPMDevicePowerLevel_D1        = 1,    /* not used by Apple system SW         */
  kPMDevicePowerLevel_D2        = 2,    /* not used by Apple system SW         */
  kPMDevicePowerLevel_Off       = 3     /* main PCI bus power 'Off', but PCI standby power available (D3cold state) */
};

/* PowerHandlerProc definition */
typedef CALLBACK_API( OSStatus , PowerHandlerProcPtr )(UInt32 message, void *param, UInt32 refCon, RegEntryID *regEntryID);
typedef STACK_UPP_TYPE(PowerHandlerProcPtr)                     PowerHandlerUPP;
/*
 *  NewPowerHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  DisposePowerHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  InvokePowerHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
   Use kIdleQueueDeviceType as the deviceType argument to AddDevicePowerHandler() to get the
   handler into the idle queue instead of the device sleep queue.
*/
#define kIdleQueueDeviceType    "idle-queue"
/* PCI power management support*/

enum {
  kUseDefaultMinimumWakeTime    = 0,    /* Defaults to 5 minutes*/
  kPowerSummaryVersion          = 1,    /* Version of PowerSummary structure.*/
  kDevicePowerInfoVersion       = 1     /* Version of DevicePowerInfo structure.*/
};

enum {
                                        /* PowerSummary flags*/
  kPCIPowerOffAllowed           = (1L << 0) /* PCI power off is allowed.*/
};

enum {
                                        /* DevicePowerInfo flags*/
  kDevicePCIPowerOffAllowed     = (1L << 0), /* PCI power off is allowed for device.*/
  kDeviceSupportsPMIS           = (1L << 1), /* Device supports Power Mgt Interface Spec.*/
  kDeviceCanAssertPMEDuringSleep = (1L << 2), /* Device can assert PME# during sleep.*/
  kDeviceUsesCommonLogicPower   = (1L << 3), /* Device uses common-logic power*/
  kDeviceDriverPresent          = (1L << 4), /* Driver present for device.*/
  kDeviceDriverSupportsPowerMgt = (1L << 5) /* Driver installed a power handler.*/
};

struct DevicePowerInfo {
  UInt32              version;                /* Version of this structure.*/
  RegEntryID          regID;                  /* RegEntryID for device.*/
  OptionBits          flags;                  /* Flags*/
  UInt32              minimumWakeTime;        /* Minimum seconds before sleeping again.*/
  UInt32              sleepPowerNeeded;       /* Milliwatts needed in the sleep state.*/
};
typedef struct DevicePowerInfo          DevicePowerInfo;
struct PowerSummary {
  UInt32              version;                /* Version of this structure.*/
  OptionBits          flags;                  /* Flags*/
  UInt32              sleepPowerAvailable;    /* Milliwatts available during sleep.*/
  UInt32              sleepPowerNeeded;       /* Milliwatts needed during sleep.*/
  UInt32              minimumWakeTime;        /* Minimum seconds before sleeping again.*/
  ItemCount           deviceCount;            /* Number of device power info records.*/
  DevicePowerInfo     devices[1];             /* Array of device power info records.*/
};
typedef struct PowerSummary             PowerSummary;
enum {
                                        /* SleepQRec.sleepQFlags */
  noCalls                       = 1,
  noRequest                     = 2,
  slpQType                      = 16,
  sleepQType                    = 16
};

/* Power Mgt Apple Event types and errors */
enum {
                                        /* power mgt class*/
  kAEMacPowerMgtEvt             = 'pmgt', /* event ids*/
  kAEMacToWake                  = 'wake',
  kAEMacLowPowerSaveData        = 'pmsd',
  kAEMacEmergencySleep          = 'emsl',
  kAEMacEmergencyShutdown       = 'emsd'
};


/*
   These are result values returned by a Power Handler when queries
   by the Power Mgr if the device which that Power Handler represents
   woke the machine.
*/
enum {
  kDeviceDidNotWakeMachine      = 0,    /* device did NOT wake machine*/
  kDeviceRequestsFullWake       = 1,    /* device did wake machine and requests full wakeup*/
  kDeviceRequestsWakeToDoze     = 2     /* device did wake machine and requests partial wakeup*/
};

/* bits in bitfield returned by PMFeatures */
enum {
  hasWakeupTimer                = 0,    /* 1=wakeup timer is supported                    */
  hasSharedModemPort            = 1,    /* 1=modem port shared by SCC and internal modem       */
  hasProcessorCycling           = 2,    /* 1=processor cycling is supported                */
  mustProcessorCycle            = 3,    /* 1=processor cycling should not be turned off          */
  hasReducedSpeed               = 4,    /* 1=processor can be started up at reduced speed        */
  dynamicSpeedChange            = 5,    /* 1=processor speed can be switched dynamically       */
  hasSCSIDiskMode               = 6,    /* 1=SCSI Disk Mode is supported                 */
  canGetBatteryTime             = 7,    /* 1=battery time can be calculated                */
  canWakeupOnRing               = 8,    /* 1=can wakeup when the modem detects a ring          */
  hasDimmingSupport             = 9,    /* 1=has dimming support built in (DPMS standby by default)   */
  hasStartupTimer               = 10,   /* 1=startup timer is supported                    */
  hasChargeNotification         = 11,   /* 1=client can determine of charge connect status change notifications available */
  hasDimSuspendSupport          = 12,   /* 1=supports dimming LCD and CRT to DPMS suspend state     */
  hasWakeOnNetActivity          = 13,   /* 1=hardware supports wake on network activity          */
  hasWakeOnLid                  = 14,   /* 1=hardware can wake when opened                   */
  canPowerOffPCIBus             = 15,   /* 1=hardware can power off PCI bus during sleep if cards allow */
  hasDeepSleep                  = 16,   /* 1=hardware supports deep sleep (hibernation) mode   */
  hasSleep                      = 17,   /* 1=hardware supports normal (PowerBook-like) sleep   */
  supportsServerModeAPIs        = 18,   /* 1=hardware supports server mode API routines          */
  supportsUPSIntegration        = 19,   /* 1=hardware support UPS integration and reporting      */
  hasAggressiveIdling           = 20,   /* 1=Power Manager only resets OverallAct on UsrActvity     */
  supportsIdleQueue             = 21    /* 1=Power Manager supports the idle queue              */
};

/* bits in bitfield returned by GetIntModemInfo and set by SetIntModemState */
enum {
  hasInternalModem              = 0,    /* 1=internal modem installed               */
  intModemRingDetect            = 1,    /* 1=internal modem has detected a ring          */
  intModemOffHook               = 2,    /* 1=internal modem is off hook               */
  intModemRingWakeEnb           = 3,    /* 1=wakeup on ring is enabled                 */
  extModemSelected              = 4,    /* 1=external modem selected             */
  modemSetBit                   = 15    /* 1=set bit, 0=clear bit (SetIntModemState)   */
};

/* bits in BatteryInfo.flags                                    */
/* ("chargerConnected" doesn't mean the charger is plugged in)  */
enum {
  batteryInstalled              = 7,    /* 1=battery is currently connected             */
  batteryCharging               = 6,    /* 1=battery is being charged               */
  chargerConnected              = 5,    /* 1=charger is connected to the PowerBook         */
  upsConnected                  = 4,    /* 1=there is a UPS connected               */
  upsIsPowerSource              = 3     /* 1=UPS is source of power                */
};

enum {
  HDPwrQType                    = 0x4844, /* 'HD' hard disk spindown queue element type     */
  PMgrStateQType                = 0x504D /* 'PM' Power Manager state queue element type       */
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
  pmSleepTimeoutChangedMask     = (1 << pmSleepTimeoutChanged),
  pmSleepEnableChangedMask      = (1 << pmSleepEnableChanged),
  pmHardDiskTimeoutChangedMask  = (1 << pmHardDiskTimeoutChanged),
  pmHardDiskSpindownChangedMask = (1 << pmHardDiskSpindownChanged),
  pmDimmingTimeoutChangedMask   = (1 << pmDimmingTimeoutChanged),
  pmDimmingEnableChangedMask    = (1 << pmDimmingEnableChanged),
  pmDiskModeAddressChangedMask  = (1 << pmDiskModeAddressChanged),
  pmProcessorCyclingChangedMask = (1 << pmProcessorCyclingChanged),
  pmProcessorSpeedChangedMask   = (1 << pmProcessorSpeedChanged),
  pmWakeupTimerChangedMask      = (1 << pmWakeupTimerChanged),
  pmStartupTimerChangedMask     = (1 << pmStartupTimerChanged),
  pmHardDiskPowerRemovedbyUserMask = (1 << pmHardDiskPowerRemovedbyUser),
  pmChargeStatusChangedMask     = (1 << pmChargeStatusChanged),
  pmPowerLevelChangedMask       = (1 << pmPowerLevelChanged),
  pmWakeOnNetActivityChangedMask = (1 << pmWakeOnNetActivityChanged)
};

/* System Activity Selectors */
/* Notes:  The IdleActivity selector is not available unless the hasAggressiveIdling PMFeatures bit is set. */
/*         Use IdleActivity where you used to use OverallAct if necessary.  OverallAct will only            */
/*         delay power cycling if it's enabled, and will delay sleep by a small amount when                 */
/*         hasAggressiveIdling is set.  Don't use IdleActivity unless hasAggressiveIdling is set; when      */
/*         hasAggressiveIdling is not set, the use of IdleActivity is undefined, and well do different      */
/*         things depending on which Power Manager is currently running.                                    */
enum {
  OverallAct                    = 0,    /* Delays idle sleep by small amount                 */
  UsrActivity                   = 1,    /* Delays idle sleep and dimming by timeout time          */
  NetActivity                   = 2,    /* Delays idle sleep and power cycling by small amount         */
  HDActivity                    = 3,    /* Delays hard drive spindown and idle sleep by small amount  */
  IdleActivity                  = 4     /* Delays idle sleep by timeout time                 */
};

/* Storage Media sleep mode defines */
enum {
  kMediaModeOn                  = 0,    /* Media active (Drive spinning and at full power)    */
  kMediaModeStandBy             = 1,    /* Media standby (not implemented)    */
  kMediaModeSuspend             = 2,    /* Media Idle (not implemented)   */
  kMediaModeOff                 = 3     /* Media Sleep (Drive not spinning and at min power, max recovery time)   */
};

enum {
  kMediaPowerCSCode             = 70
};


/* definitions for HDQueueElement.hdFlags   */
enum {
  kHDQueuePostBit               = 0,    /* 1 = call this routine on the second pass     */
  kHDQueuePostMask              = (1 << kHDQueuePostBit)
};

struct ActivityInfo {
  short               ActivityType;           /* Type of activity to be fetched.  Same as UpdateSystemActivity Selectors */
  unsigned long       ActivityTime;           /* Time of last activity (in ticks) of specified type. */
};
typedef struct ActivityInfo             ActivityInfo;
/* information returned by GetScaledBatteryInfo */
struct BatteryInfo {
  UInt8               flags;                  /* misc flags (see below)                  */
  UInt8               warningLevel;           /* scaled warning level (0-255)               */
  UInt8               reserved;               /* reserved for internal use             */
  UInt8               batteryLevel;           /* scaled battery level (0-255)               */
};
typedef struct BatteryInfo              BatteryInfo;

typedef SInt8                           ModemByte;
typedef SInt8                           BatteryByte;
typedef SInt8                           SoundMixerByte;
typedef long                            PMResultCode;
typedef struct SleepQRec                SleepQRec;
typedef SleepQRec *                     SleepQRecPtr;
typedef struct HDQueueElement           HDQueueElement;
typedef struct PMgrQueueElement         PMgrQueueElement;
typedef CALLBACK_API( long , SleepQProcPtr )(long message, SleepQRecPtr qRecPtr);
typedef CALLBACK_API( void , HDSpindownProcPtr )(HDQueueElement * theElement);
typedef CALLBACK_API( void , PMgrStateChangeProcPtr )(PMgrQueueElement *theElement, long stateBits);
typedef STACK_UPP_TYPE(SleepQProcPtr)                           SleepQUPP;
typedef STACK_UPP_TYPE(HDSpindownProcPtr)                       HDSpindownUPP;
typedef STACK_UPP_TYPE(PMgrStateChangeProcPtr)                  PMgrStateChangeUPP;
struct SleepQRec {
  SleepQRecPtr        sleepQLink;             /* pointer to next queue element          */
  short               sleepQType;             /* queue element type (must be SleepQType)       */
  SleepQUPP           sleepQProc;             /* pointer to sleep universal proc ptr         */
  short               sleepQFlags;            /* flags                       */
};

struct HDQueueElement {
  struct HDQueueElement * hdQLink;            /* pointer to next queue element          */
  short               hdQType;                /* queue element type (must be HDPwrQType)       */
  short               hdFlags;                /* miscellaneous flags                   */
  HDSpindownUPP       hdProc;                 /* pointer to routine to call           */
  long                hdUser;                 /* user-defined (variable storage, etc.)   */
};

struct PMgrQueueElement {
  struct PMgrQueueElement * pmQLink;          /* pointer to next queue element          */
  short               pmQType;                /* queue element type (must be PMgrStateQType)    */
  short               pmFlags;                /* miscellaneous flags                   */
  long                pmNotifyBits;           /* bitmap of which changes to be notified for */
  PMgrStateChangeUPP  pmProc;                 /* pointer to routine to call           */
  long                pmUser;                 /* user-defined (variable storage, etc.)   */
};


struct BatteryTimeRec {
  unsigned long       expectedBatteryTime;    /* estimated battery time remaining (seconds) */
  unsigned long       minimumBatteryTime;     /* minimum battery time remaining (seconds)     */
  unsigned long       maximumBatteryTime;     /* maximum battery time remaining (seconds)     */
  unsigned long       timeUntilCharged;       /* time until battery is fully charged (seconds)*/
};
typedef struct BatteryTimeRec           BatteryTimeRec;

struct WakeupTime {
  unsigned long       wakeTime;               /* wakeup time (same format as current time)   */
  Boolean             wakeEnabled;            /* 1=enable wakeup timer, 0=disable wakeup timer  */
  SInt8               filler;
};
typedef struct WakeupTime               WakeupTime;

struct StartupTime {
  unsigned long       startTime;              /* startup time (same format as current time)     */
  Boolean             startEnabled;           /* 1=enable startup timer, 0=disable startup timer    */
  SInt8               filler;
};
typedef struct StartupTime              StartupTime;
/* PowerSource version*/
enum {
  kVersionOnePowerSource        = 1,
  kVersionTwoPowerSource        = 2,
  kCurrentPowerSourceVersion    = kVersionTwoPowerSource
};

/* PowerSourceAttrs bits*/

enum {
  bSourceIsBattery              = 0,    /* power source is battery*/
  bSourceIsAC                   = 1,    /* power source is AC*/
  bSourceCanBeCharged           = 2,    /* power source can be charged*/
  bSourceIsUPS                  = 3,    /* power source is UPS. NOTE: software should set bSourceIsBattery and bSourceIsAC also, as appropriate*/
  bSourceProvidesWarnLevels     = 4,    /* power source provides low power and dead battery warning levels*/
  kSourceIsBatteryMask          = (1 << bSourceIsBattery),
  kSourceIsACMask               = (1 << bSourceIsAC),
  kSourceCanBeChargedMask       = (1 << bSourceCanBeCharged),
  kSourceIsUPSMask              = (1 << bSourceIsUPS),
  kSourceProvidesWarnLevelsMask = (1 << bSourceProvidesWarnLevels)
};

/* PowerSourceFlags bits*/

enum {
  bSourceIsAvailable            = 0,    /* power source is installed*/
  bSourceIsCharging             = 1,    /* power source being charged*/
  bChargerIsAttached            = 2,    /* a charger is connected*/
  kSourceIsAvailableMask        = (1 << bSourceIsAvailable),
  kSourceIsChargingMask         = (1 << bSourceIsCharging),
  kChargerIsAttachedMask        = (1 << bChargerIsAttached)
};

/* Power Capacity Types*/

enum {
  kCapacityIsActual             = 0,    /* current capacity is expessed as actual capacity in same units as max*/
  kCapacityIsPercentOfMax       = 1     /* current capacity is expressed as a percentage of maximumCapacity*/
};

/* Net Activity Wake Options*/
enum {
  kConfigSupportsWakeOnNetBit   = 0,
  kWakeOnNetAdminAccessesBit    = 1,
  kWakeOnAllNetAccessesBit      = 2,
  kUnmountServersBeforeSleepingBit = 3,
  kConfigSupportsWakeOnNetMask  = (1 << kConfigSupportsWakeOnNetBit),
  kWakeOnNetAdminAccessesMask   = (1 << kWakeOnNetAdminAccessesBit),
  kWakeOnAllNetAccessesMask     = (1 << kWakeOnAllNetAccessesBit),
  kUnmountServersBeforeSleepingMask = (1 << kUnmountServersBeforeSleepingBit)
};

/* Power Source capacity usage types*/
enum {
  kCurrentCapacityIsActualValue = 0,    /* currentCapacity is a real value in same units as maxCapacity*/
  kCurrentCapacityIsPercentOfMax = 1    /* currentCapacity is expressed as a percentage of maxCapacity.*/
};


typedef SInt16                          PowerSourceID;
struct PowerSourceParamBlock {
  PowerSourceID       sourceID;               /* unique id assigned by Power Mgr*/
  UInt16              sourceCapacityUsage;    /* how currentCapacity is used*/
  UInt32              sourceVersion;          /* version of this record*/
  OptionBits          sourceAttr;             /* attribute flags (see below)*/
  OptionBits          sourceState;            /* state flags (see below)*/
  UInt32              currentCapacity;        /* current capacity, in*/
                                              /*   milliwatts or %*/
  UInt32              maxCapacity;            /* full capacity, in milliwatts*/
  UInt32              timeRemaining;          /* time left to deplete, */
                                              /*   in milliwatt-hours*/
  UInt32              timeToFullCharge;       /* time to charge, */
                                              /*   in milliwatt-hours*/
  UInt32              voltage;                /* voltage in millivolts*/
  SInt32              current;                /* current in milliamperes */
                                              /*  (negative if consuming, */
                                              /*   positive if charging)*/
  UInt32              lowWarnLevel;           /* low warning level in milliwatts (or % if sourceCapacityUsage is %)*/
  UInt32              deadWarnLevel;          /* dead warning level in milliwatts (or % if sourceCapacityUsage is %)*/
  UInt32              reserved[16];           /* for future expansion*/
};
typedef struct PowerSourceParamBlock    PowerSourceParamBlock;
typedef PowerSourceParamBlock *         PowerSourceParamBlockPtr;
/*
 *  DisableWUTime()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DisableWUTime(void)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  SetWUTime()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetWUTime(long wuTime)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  GetWUTime()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetWUTime(
  long *  wuTime,
  Byte *  wuFlag)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  BatteryStatus()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
BatteryStatus(
  Byte *  status,
  Byte *  power)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  ModemStatus()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
ModemStatus(Byte * status)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  GetCPUSpeed()
 *  
 *  Discussion:
 *    GetCPUSpeed() returns the current effective clock speed of the
 *    CPU in megahertz.
 *  
 *  Result:
 *    the current effective clock speed of the CPU in megahertz.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
GetCPUSpeed(void)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  IdleUpdate()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Power Manager is deprecated in Mac OS X.  Some of this
 *    functionality is provided in similar form in IOKit; some is
 *    provided in the Carbon and Cocoa frameworks.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
IdleUpdate(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  EnableIdle()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Power Manager is deprecated in Mac OS X.  Some of this
 *    functionality is provided in similar form in IOKit; some is
 *    provided in the Carbon and Cocoa frameworks.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
EnableIdle(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  DisableIdle()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    The Power Manager is deprecated in Mac OS X.  Some of this
 *    functionality is provided in similar form in IOKit; some is
 *    provided in the Carbon and Cocoa frameworks.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisableIdle(void)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  SleepQInstall()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SleepQInstall(SleepQRecPtr qRecPtr)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SleepQRemove()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SleepQRemove(SleepQRecPtr qRecPtr)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AOn()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated on Mac OS X.  IOKit may provide
 *    replacement functionality depending on what this was being used
 *    for.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
AOn(void)                                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  AOnIgnoreModem()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated on Mac OS X.  IOKit may provide
 *    replacement functionality depending on what this was being used
 *    for.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
AOnIgnoreModem(void)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  BOn()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated on Mac OS X.  IOKit may provide
 *    replacement functionality depending on what this was being used
 *    for.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
BOn(void)                                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  AOff()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated on Mac OS X.  IOKit may provide
 *    replacement functionality depending on what this was being used
 *    for.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
AOff(void)                                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  BOff()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated on Mac OS X.  IOKit may provide
 *    replacement functionality depending on what this was being used
 *    for.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
BOff(void)                                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;



/* Public Power Management API  */
/*
 *  PMSelectorCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern short 
PMSelectorCount(void)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMFeatures()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern UInt32 
PMFeatures(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetSleepTimeout()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern UInt8 
GetSleepTimeout(void)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  SetSleepTimeout()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern void 
SetSleepTimeout(UInt8 timeout)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  GetHardDiskTimeout()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern UInt8 
GetHardDiskTimeout(void)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  SetHardDiskTimeout()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern void 
SetHardDiskTimeout(UInt8 timeout)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  HardDiskPowered()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern Boolean 
HardDiskPowered(void)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  SpinDownHardDisk()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern void 
SpinDownHardDisk(void)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  IsSpindownDisabled()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern Boolean 
IsSpindownDisabled(void)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  SetSpindownDisable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern void 
SetSpindownDisable(Boolean setDisable)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HardDiskQInstall()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern OSErr 
HardDiskQInstall(HDQueueElement * theElement)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  HardDiskQRemove()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern OSErr 
HardDiskQRemove(HDQueueElement * theElement)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  GetScaledBatteryInfo()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern void 
GetScaledBatteryInfo(
  short          whichBattery,
  BatteryInfo *  theInfo)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  AutoSleepControl()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern void 
AutoSleepControl(Boolean enableSleep)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  GetIntModemInfo()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern UInt32 
GetIntModemInfo(void)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  SetIntModemState()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern void 
SetIntModemState(short theState)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  MaximumProcessorSpeed()
 *  
 *  Discussion:
 *    MaximumProcessorSpeed() returns the maximum effective clock speed
 *    of the CPU in megahertz.
 *  
 *  Result:
 *    the maximum effective clock speed of the CPU in megahertz.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern short 
MaximumProcessorSpeed(void)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MinimumProcessorSpeed()
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
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern short 
MinimumProcessorSpeed(void)                                   AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CurrentProcessorSpeed()
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
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern short 
CurrentProcessorSpeed(void)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FullProcessorSpeed()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern Boolean 
FullProcessorSpeed(void)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetProcessorSpeed()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern Boolean 
SetProcessorSpeed(Boolean fullSpeed)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetSCSIDiskModeAddress()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern short 
GetSCSIDiskModeAddress(void)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  SetSCSIDiskModeAddress()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern void 
SetSCSIDiskModeAddress(short scsiAddress)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  GetWakeupTimer()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern void 
GetWakeupTimer(WakeupTime * theTime)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  SetWakeupTimer()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern void 
SetWakeupTimer(WakeupTime * theTime)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  IsProcessorCyclingEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern Boolean 
IsProcessorCyclingEnabled(void)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  EnableProcessorCycling()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern void 
EnableProcessorCycling(Boolean enable)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BatteryCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern short 
BatteryCount(void)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetBatteryVoltage()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern Fixed 
GetBatteryVoltage(short whichBattery)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  GetBatteryTimes()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern void 
GetBatteryTimes(
  short             whichBattery,
  BatteryTimeRec *  theTimes)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  GetDimmingTimeout()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern UInt8 
GetDimmingTimeout(void)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  SetDimmingTimeout()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern void 
SetDimmingTimeout(UInt8 timeout)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  DimmingControl()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern void 
DimmingControl(Boolean enableSleep)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  IsDimmingControlDisabled()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern Boolean 
IsDimmingControlDisabled(void)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  IsAutoSlpControlDisabled()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern Boolean 
IsAutoSlpControlDisabled(void)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  PMgrStateQInstall()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern OSErr 
PMgrStateQInstall(PMgrQueueElement * theElement)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  PMgrStateQRemove()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern OSErr 
PMgrStateQRemove(PMgrQueueElement * theElement)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  UpdateSystemActivity()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern OSErr 
UpdateSystemActivity(UInt8 activity)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DelaySystemIdle()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern OSErr 
DelaySystemIdle(void)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  GetStartupTimer()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern OSErr 
GetStartupTimer(StartupTime * theTime)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  SetStartupTimer()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern OSErr 
SetStartupTimer(StartupTime * theTime)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  GetLastActivity()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.0 and later
 */
extern OSErr 
GetLastActivity(ActivityInfo * theActivity)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  GetSoundMixerState()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.1 and later
 */
extern OSErr 
GetSoundMixerState(SoundMixerByte * theSoundMixerByte)        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  SetSoundMixerState()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.1 and later
 */
extern OSErr 
SetSoundMixerState(SoundMixerByte * theSoundMixerByte)        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  GetDimSuspendState()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.1 and later
 */
extern Boolean 
GetDimSuspendState(void)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  SetDimSuspendState()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.0
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in PowerMgrLib 1.1 and later
 */
extern void 
SetDimSuspendState(Boolean dimSuspendState)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;


/*
 *  GetCoreProcessorTemperature()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in PowerMgrLib 2.0 and later
 */


/*
 *  GetWakeOnNetworkOptions()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in PowerMgrLib 2.0 and later
 */


/*
 *  SetWakeOnNetworkOptions()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in PowerMgrLib 2.0 and later
 */


/*
 *  AddPowerSource()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in PowerMgrLib 2.0 and later
 */


/*
 *  RemovePowerSource()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in PowerMgrLib 2.0 and later
 */


/*
 *  UpdatePowerSource()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in PowerMgrLib 2.0 and later
 */


/*
 *  IsServerModeEnabled()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in PowerMgrLib 2.0 and later
 */


/*
 *  EnableServerMode()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in PowerMgrLib 2.0 and later
 */


/* 
   NumBatteriesInstalled is different from BatteryCount in that it
   indicates how many batteries are actually available at the time
   it is called (including UPS batteries). BatteryCount shows a 
   static number of batteries a machine is capable of holding which does NOT
   include UPS batteries. So, while a desktop might show a BatteryCount
   of zero, its NumBatteriesInstalled value might be 1 or more if a UPS
   is attached. 
*/
/*
 *  NumBatteriesInstalled()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in PowerMgrLib 2.0 and later
 */


/* Power Handler Management */
/*
 *  IsPCIPowerOffDisabled()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.1 and later
 */


/*
 *  EnablePCIPowerOff()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.1 and later
 */


/*
 *  AddDevicePowerHandler()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.1 and later
 */


/*
 *  RemoveDevicePowerHandler()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.1 and later
 */


/*
 *  RemoveDevicePowerHandlerForProc()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.1 and later
 */


/*
 *  GetDevicePowerLevel()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.1 and later
 */


/*
 *  SetDevicePowerLevel()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DriverServicesLib 1.1 and later
 */



/*
 *  NewSleepQUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern SleepQUPP
NewSleepQUPP(SleepQProcPtr userRoutine)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewHDSpindownUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern HDSpindownUPP
NewHDSpindownUPP(HDSpindownProcPtr userRoutine)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewPMgrStateChangeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern PMgrStateChangeUPP
NewPMgrStateChangeUPP(PMgrStateChangeProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeSleepQUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeSleepQUPP(SleepQUPP userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeHDSpindownUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeHDSpindownUPP(HDSpindownUPP userUPP)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposePMgrStateChangeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposePMgrStateChangeUPP(PMgrStateChangeUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeSleepQUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern long
InvokeSleepQUPP(
  long          message,
  SleepQRecPtr  qRecPtr,
  SleepQUPP     userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeHDSpindownUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeHDSpindownUPP(
  HDQueueElement *  theElement,
  HDSpindownUPP     userUPP)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokePMgrStateChangeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokePMgrStateChangeUPP(
  PMgrQueueElement *  theElement,
  long                stateBits,
  PMgrStateChangeUPP  userUPP)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __POWER__ */

