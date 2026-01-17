/*
     File:       CarbonCore/Components.h
 
     Contains:   Component Manager Interfaces.
 
     Version:    CarbonCore-682.26~1
 
     Copyright:  © 1991-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __COMPONENTS__
#define __COMPONENTS__

#ifndef __MACERRORS__
#include <CarbonCore/MacErrors.h>
#endif

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
#endif

#ifndef __FILES__
#include <CarbonCore/Files.h>
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
  kAppleManufacturer            = 'appl', /* Apple supplied components */
  kComponentResourceType        = 'thng', /* a components resource type */
  kComponentAliasResourceType   = 'thga' /* component alias resource type */
};

enum {
  kAnyComponentType             = 0,
  kAnyComponentSubType          = 0,
  kAnyComponentManufacturer     = 0,
  kAnyComponentFlagsMask        = 0
};

enum {
  cmpThreadSafe                 = 1L << 28, /* component is thread-safe */
  cmpIsMissing                  = 1L << 29,
  cmpWantsRegisterMessage       = 1L << 31
};

enum {
  kComponentOpenSelect          = -1,   /* ComponentInstance for this open */
  kComponentCloseSelect         = -2,   /* ComponentInstance for this close */
  kComponentCanDoSelect         = -3,   /* selector # being queried */
  kComponentVersionSelect       = -4,   /* no params */
  kComponentRegisterSelect      = -5,   /* no params */
  kComponentTargetSelect        = -6,   /* ComponentInstance for top of call chain */
  kComponentUnregisterSelect    = -7,   /* no params */
  kComponentGetMPWorkFunctionSelect = -8, /* some params */
  kComponentExecuteWiredActionSelect = -9, /* QTAtomContainer actionContainer, QTAtom actionAtom, QTCustomActionTargetPtr target, QTEventRecordPtr event */
  kComponentGetPublicResourceSelect = -10 /* OSType resourceType, short resourceId, Handle *resource */
};

/* Component Resource Extension flags */
enum {
  componentDoAutoVersion        = (1 << 0),
  componentWantsUnregister      = (1 << 1),
  componentAutoVersionIncludeFlags = (1 << 2),
  componentHasMultiplePlatforms = (1 << 3),
  componentLoadResident         = (1 << 4)
};



/* Set Default Component flags */
enum {
  defaultComponentIdentical     = 0,
  defaultComponentAnyFlags      = 1,
  defaultComponentAnyManufacturer = 2,
  defaultComponentAnySubType    = 4,
  defaultComponentAnyFlagsAnyManufacturer = (defaultComponentAnyFlags + defaultComponentAnyManufacturer),
  defaultComponentAnyFlagsAnyManufacturerAnySubType = (defaultComponentAnyFlags + defaultComponentAnyManufacturer + defaultComponentAnySubType)
};

/* RegisterComponentResource flags */
enum {
  registerComponentGlobal       = 1,
  registerComponentNoDuplicates = 2,
  registerComponentAfterExisting = 4,
  registerComponentAliasesOnly  = 8
};


struct ComponentDescription {
  OSType              componentType;          /* A unique 4-byte code indentifying the command set */
  OSType              componentSubType;       /* Particular flavor of this instance */
  OSType              componentManufacturer;  /* Vendor indentification */
  unsigned long       componentFlags;         /* 8 each for Component,Type,SubType,Manuf/revision */
  unsigned long       componentFlagsMask;     /* Mask for specifying which flags to consider in search, zero during registration */
};
typedef struct ComponentDescription     ComponentDescription;

struct ResourceSpec {
  OSType              resType;                /* 4-byte code    */
  short               resID;                  /*         */
};
typedef struct ResourceSpec             ResourceSpec;
struct ComponentResource {
  ComponentDescription  cd;                   /* Registration parameters */
  ResourceSpec        component;              /* resource where Component code is found */
  ResourceSpec        componentName;          /* name string resource */
  ResourceSpec        componentInfo;          /* info string resource */
  ResourceSpec        componentIcon;          /* icon resource */
};
typedef struct ComponentResource        ComponentResource;
typedef ComponentResource *             ComponentResourcePtr;
typedef ComponentResourcePtr *          ComponentResourceHandle;
struct ComponentPlatformInfo {
  long                componentFlags;         /* flags of Component */
  ResourceSpec        component;              /* resource where Component code is found */
  short               platformType;           /* gestaltSysArchitecture result */
};
typedef struct ComponentPlatformInfo    ComponentPlatformInfo;
struct ComponentResourceExtension {
  long                componentVersion;       /* version of Component */
  long                componentRegisterFlags; /* flags for registration */
  short               componentIconFamily;    /* resource id of Icon Family */
};
typedef struct ComponentResourceExtension ComponentResourceExtension;
struct ComponentPlatformInfoArray {
  long                count;
  ComponentPlatformInfo  platformArray[1];
};
typedef struct ComponentPlatformInfoArray ComponentPlatformInfoArray;
struct ExtComponentResource {
  ComponentDescription  cd;                   /* registration parameters */
  ResourceSpec        component;              /* resource where Component code is found */
  ResourceSpec        componentName;          /* name string resource */
  ResourceSpec        componentInfo;          /* info string resource */
  ResourceSpec        componentIcon;          /* icon resource */
  long                componentVersion;       /* version of Component */
  long                componentRegisterFlags; /* flags for registration */
  short               componentIconFamily;    /* resource id of Icon Family */
  long                count;                  /* elements in platformArray */
  ComponentPlatformInfo  platformArray[1];
};
typedef struct ExtComponentResource     ExtComponentResource;
typedef ExtComponentResource *          ExtComponentResourcePtr;
typedef ExtComponentResourcePtr *       ExtComponentResourceHandle;
struct ComponentAliasResource {
  ComponentResource   cr;                     /* Registration parameters */
  ComponentDescription  aliasCD;              /* component alias description */
};
typedef struct ComponentAliasResource   ComponentAliasResource;
/*  Structure received by Component:        */
struct ComponentParameters {
  UInt8               flags;                  /* call modifiers: sync/async, deferred, immed, etc */
  UInt8               paramSize;              /* size in bytes of actual parameters passed to this call */
  short               what;                   /* routine selector, negative for Component management calls */
  long                params[1];              /* actual parameters for the indicated routine */
};
typedef struct ComponentParameters      ComponentParameters;
struct ComponentRecord {
  long                data[1];
};
typedef struct ComponentRecord          ComponentRecord;
typedef ComponentRecord *               Component;
struct ComponentInstanceRecord {
  long                data[1];
};
typedef struct ComponentInstanceRecord  ComponentInstanceRecord;
typedef ComponentInstanceRecord *       ComponentInstance;
struct RegisteredComponentRecord {
  long                data[1];
};
typedef struct RegisteredComponentRecord RegisteredComponentRecord;
typedef RegisteredComponentRecord *     RegisteredComponentRecordPtr;
struct RegisteredComponentInstanceRecord {
  long                data[1];
};
typedef struct RegisteredComponentInstanceRecord RegisteredComponentInstanceRecord;
typedef RegisteredComponentInstanceRecord * RegisteredComponentInstanceRecordPtr;
typedef long                            ComponentResult;
enum {
  platform68k                   = 1,    /* platform type (response from gestaltComponentPlatform) */
  platformPowerPC               = 2,    /* (when gestaltComponentPlatform is not implemented, use */
  platformInterpreted           = 3,    /* gestaltSysArchitecture) */
  platformWin32                 = 4,
  platformPowerPCNativeEntryPoint = 5,
  platformIA32NativeEntryPoint  = 6
};

enum {
  platformIRIXmips              = 1000,
  platformSunOSsparc            = 1100,
  platformSunOSintel            = 1101,
  platformLinuxppc              = 1200,
  platformLinuxintel            = 1201,
  platformAIXppc                = 1300,
  platformNeXTIntel             = 1400,
  platformNeXTppc               = 1401,
  platformNeXTsparc             = 1402,
  platformNeXT68k               = 1403,
  platformMacOSx86              = 1500
};

enum {
  mpWorkFlagDoWork              = (1 << 0),
  mpWorkFlagDoCompletion        = (1 << 1),
  mpWorkFlagCopyWorkBlock       = (1 << 2),
  mpWorkFlagDontBlock           = (1 << 3),
  mpWorkFlagGetProcessorCount   = (1 << 4),
  mpWorkFlagGetIsRunning        = (1 << 6)
};

enum {
  cmpAliasNoFlags               = 0,
  cmpAliasOnlyThisFile          = 1
};

typedef UInt32                          CSComponentsThreadMode;
enum {
  kCSAcceptAllComponentsMode    = 0,
  kCSAcceptThreadSafeComponentsOnlyMode = 1
};

/*
 *  CSSetComponentsThreadMode()
 *  
 *  Summary:
 *    Set whether or not using thread-unsafe components is allowed on
 *    the current thread.
 *  
 *  Discussion:
 *    When set to kCSAcceptThreadSafeComponentsOnlyMode, the current
 *    thread can only make thread-safe calls. Applications and other
 *    high-level code that wants to call QuickTime (and other) APIs
 *    from preemptive threads should call  SetComponentsThreadMode(
 *    kCSAcceptThreadSafeComponentsOnlyMode );  from their thread
 *    beforehand. The safeguard flag should only be left
 *    kCSAcceptAllComponentsMode for the main thread and other threads
 *    that participate in cooperative locking with it (such as the
 *    Carbon Thread Manager-style cooperative threads and application 
 *    threads that perform private locking).
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    mode:
 *      The thread-safety mode in current thread.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
CSSetComponentsThreadMode(CSComponentsThreadMode mode)        AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  CSGetComponentsThreadMode()
 *  
 *  Summary:
 *    Get the current thread's thread-safety mode.
 *  
 *  Discussion:
 *    Returns kCSAcceptThreadSafeComponentsOnlyMode if only thread-safe
 *    components are allowed in current thread and
 *    kCSAcceptAllComponentsMode if all components are accepted
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CSComponentsThreadMode 
CSGetComponentsThreadMode(void)                               AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


struct ComponentMPWorkFunctionHeaderRecord {
  UInt32              headerSize;
  UInt32              recordSize;
  UInt32              workFlags;
  UInt16              processorCount;
  UInt8               unused;
  UInt8               isRunning;
};
typedef struct ComponentMPWorkFunctionHeaderRecord ComponentMPWorkFunctionHeaderRecord;
typedef ComponentMPWorkFunctionHeaderRecord * ComponentMPWorkFunctionHeaderRecordPtr;
typedef CALLBACK_API( ComponentResult , ComponentMPWorkFunctionProcPtr )(void *globalRefCon, ComponentMPWorkFunctionHeaderRecordPtr header);
typedef CALLBACK_API( ComponentResult , ComponentRoutineProcPtr )(ComponentParameters *cp, Handle componentStorage);
typedef CALLBACK_API( OSErr , GetMissingComponentResourceProcPtr )(Component c, OSType resType, short resID, void *refCon, Handle *resource);
typedef STACK_UPP_TYPE(ComponentMPWorkFunctionProcPtr)          ComponentMPWorkFunctionUPP;
typedef STACK_UPP_TYPE(ComponentRoutineProcPtr)                 ComponentRoutineUPP;
typedef STACK_UPP_TYPE(GetMissingComponentResourceProcPtr)      GetMissingComponentResourceUPP;
/*
    The parameter list for each ComponentFunction is unique. It is
    therefore up to users to create the appropriate procInfo for their
    own ComponentFunctions where necessary.
*/
typedef UniversalProcPtr                ComponentFunctionUPP;
/*
 *  NewComponentFunctionUPP()
 *  
 *  Discussion:
 *    For use in writing a Carbon compliant Component.  It is used to
 *    create a ComponentFunctionUPP needed to call
 *    CallComponentFunction in the Components dispatch routine.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ComponentFunctionUPP 
NewComponentFunctionUPP(
  ProcPtr        userRoutine,
  ProcInfoType   procInfo)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeComponentFunctionUPP()
 *  
 *  Discussion:
 *    For use in writing a Carbon compliant Component.  It is used to
 *    dispose of a ComponentFunctionUPP created by
 *    NewComponentFunctionUPP.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void 
DisposeComponentFunctionUPP(ComponentFunctionUPP userUPP)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



#if TARGET_RT_MAC_CFM
/* 
    CallComponentUPP is a global variable exported from InterfaceLib.
    It is the ProcPtr passed to CallUniversalProc to manually call a component function.
*/
/*
 *  CallComponentUPP
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UniversalProcPtr CallComponentUPP;
#endif

#define ComponentCallNow( callNumber, paramSize ) \
    FIVEWORDINLINE( 0x2F3C,paramSize,callNumber,0x7000,0xA82A )

/********************************************************
*                                                       *
*               APPLICATION LEVEL CALLS                 *
*                                                       *
********************************************************/
/********************************************************
* Component Database Add, Delete, and Query Routines
********************************************************/
/*
 *  RegisterComponent()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Component 
RegisterComponent(
  ComponentDescription *  cd,
  ComponentRoutineUPP     componentEntryPoint,
  short                   global,
  Handle                  componentName,
  Handle                  componentInfo,
  Handle                  componentIcon)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RegisterComponentResource()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Component 
RegisterComponentResource(
  ComponentResourceHandle   cr,
  short                     global)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  UnregisterComponent()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
UnregisterComponent(Component aComponent)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FindNextComponent()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Component 
FindNextComponent(
  Component               aComponent,
  ComponentDescription *  looking)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CountComponents()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
CountComponents(ComponentDescription * looking)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetComponentInfo()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetComponentInfo(
  Component               aComponent,
  ComponentDescription *  cd,
  Handle                  componentName,
  Handle                  componentInfo,
  Handle                  componentIcon)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetComponentListModSeed()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetComponentListModSeed(void)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetComponentTypeModSeed()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetComponentTypeModSeed(OSType componentType)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/********************************************************
* Component Instance Allocation and dispatch routines
********************************************************/
/*
 *  OpenAComponent()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
OpenAComponent(
  Component            aComponent,
  ComponentInstance *  ci)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OpenComponent()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentInstance 
OpenComponent(Component aComponent)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CloseComponent()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CloseComponent(ComponentInstance aComponentInstance)          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetComponentInstanceError()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetComponentInstanceError(ComponentInstance aComponentInstance) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/********************************************************
* Component aliases
********************************************************/
/*
 *  ResolveComponentAlias()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Component 
ResolveComponentAlias(Component aComponent)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/********************************************************
* Component public resources and public string lists
********************************************************/
/* Note: GetComponentPublicResource returns a Handle, not a resource.  The caller must dispose it with DisposeHandle. */
/*
 *  GetComponentPublicResource()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 4.0 and later
 */
extern OSErr 
GetComponentPublicResource(
  Component   aComponent,
  OSType      resourceType,
  short       resourceID,
  Handle *    theResource)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetComponentPublicResourceList()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 4.0 and later
 */
extern OSErr 
GetComponentPublicResourceList(
  OSType                           resourceType,
  short                            resourceID,
  long                             flags,
  ComponentDescription *           cd,
  GetMissingComponentResourceUPP   missingProc,
  void *                           refCon,
  void *                           atomContainerPtr)          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetComponentPublicIndString()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 4.0 and later
 */
extern OSErr 
GetComponentPublicIndString(
  Component   aComponent,
  Str255      theString,
  short       strListID,
  short       index)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/********************************************************
*                                                       *
*                   CALLS MADE BY COMPONENTS            *
*                                                       *
********************************************************/
/********************************************************
* Component Management routines
********************************************************/
/*
 *  SetComponentInstanceError()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetComponentInstanceError(
  ComponentInstance   aComponentInstance,
  OSErr               theError)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetComponentRefcon()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetComponentRefcon(Component aComponent)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetComponentRefcon()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetComponentRefcon(
  Component   aComponent,
  long        theRefcon)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OpenComponentResFile()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern short 
OpenComponentResFile(Component aComponent)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OpenAComponentResFile()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
OpenAComponentResFile(
  Component   aComponent,
  short *     resRef)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CloseComponentResFile()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CloseComponentResFile(short refnum)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Note: GetComponentResource returns a Handle, not a resource.  The caller must dispose it with DisposeHandle. */
/*
 *  GetComponentResource()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetComponentResource(
  Component   aComponent,
  OSType      resType,
  short       resID,
  Handle *    theResource)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetComponentIndString()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetComponentIndString(
  Component   aComponent,
  Str255      theString,
  short       strListID,
  short       index)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/********************************************************
* Component Instance Management routines
********************************************************/
/*
 *  GetComponentInstanceStorage()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Handle 
GetComponentInstanceStorage(ComponentInstance aComponentInstance) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetComponentInstanceStorage()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetComponentInstanceStorage(
  ComponentInstance   aComponentInstance,
  Handle              theStorage)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetComponentInstanceA5()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetComponentInstanceA5(ComponentInstance aComponentInstance)  AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  SetComponentInstanceA5()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  CountComponentInstances()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
CountComponentInstances(Component aComponent)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* useful helper routines for convenient method dispatching */
/*
 *  CallComponentFunction()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
CallComponentFunction(
  ComponentParameters *  params,
  ComponentFunctionUPP   func)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CallComponentFunctionWithStorage()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
CallComponentFunctionWithStorage(
  Handle                 storage,
  ComponentParameters *  params,
  ComponentFunctionUPP   func)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CallComponentFunctionWithStorageProcInfo()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 */
extern long 
CallComponentFunctionWithStorageProcInfo(
  Handle                 storage,
  ComponentParameters *  params,
  ProcPtr                func,
  ProcInfoType           funcProcInfo)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DelegateComponentCall()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
DelegateComponentCall(
  ComponentParameters *  originalParams,
  ComponentInstance      ci)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDefaultComponent()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetDefaultComponent(
  Component   aComponent,
  short       flags)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OpenDefaultComponent()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentInstance 
OpenDefaultComponent(
  OSType   componentType,
  OSType   componentSubType)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OpenADefaultComponent()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
OpenADefaultComponent(
  OSType               componentType,
  OSType               componentSubType,
  ComponentInstance *  ci)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CaptureComponent()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Component 
CaptureComponent(
  Component   capturedComponent,
  Component   capturingComponent)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  UncaptureComponent()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
UncaptureComponent(Component aComponent)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RegisterComponentResourceFile()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
RegisterComponentResourceFile(
  short   resRefNum,
  short   global)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetComponentIconSuite()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetComponentIconSuite(
  Component   aComponent,
  Handle *    iconSuite)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 * These calls allow you to register a file system entity.  The
 * Component Manager will "do the right thing" with the entity,
 * whether it is a standard resource fork based CFM component, CFM
 * bundle, mach-o bundle, or packaged bundle.  
 *
 * The *Entries calls allow you to specify a component description
 * which will be used to register selective components.  (Passing
 * NULL, 0 means to register all components.  
 */
/*
 *  RegisterComponentFile()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
RegisterComponentFile(
  const FSSpec *  spec,
  short           global)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RegisterComponentFileEntries()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
RegisterComponentFileEntries(
  const FSSpec *                spec,
  short                         global,
  const ComponentDescription *  toRegister,          /* can be NULL */
  UInt32                        registerCount)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RegisterComponentFileRef()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
RegisterComponentFileRef(
  const FSRef *  ref,
  short          global)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RegisterComponentFileRefEntries()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
RegisterComponentFileRefEntries(
  const FSRef *                 ref,
  short                         global,
  const ComponentDescription *  toRegister,          /* can be NULL */
  UInt32                        registerCount)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/********************************************************
*                                                       *
*           Direct calls to the Components              *
*                                                       *
********************************************************/
/* Old style names*/

/*
 *  ComponentFunctionImplemented()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
ComponentFunctionImplemented(
  ComponentInstance   ci,
  short               ftnNumber)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetComponentVersion()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetComponentVersion(ComponentInstance ci)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ComponentSetTarget()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
ComponentSetTarget(
  ComponentInstance   ci,
  ComponentInstance   target)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* New style names*/

/*
 *  CallComponentOpen()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
CallComponentOpen(
  ComponentInstance   ci,
  ComponentInstance   self)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CallComponentClose()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
CallComponentClose(
  ComponentInstance   ci,
  ComponentInstance   self)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CallComponentCanDo()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
CallComponentCanDo(
  ComponentInstance   ci,
  short               ftnNumber)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CallComponentVersion()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
CallComponentVersion(ComponentInstance ci)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CallComponentRegister()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
CallComponentRegister(ComponentInstance ci)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CallComponentTarget()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
CallComponentTarget(
  ComponentInstance   ci,
  ComponentInstance   target)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CallComponentUnregister()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
CallComponentUnregister(ComponentInstance ci)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CallComponentGetMPWorkFunction()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
CallComponentGetMPWorkFunction(
  ComponentInstance             ci,
  ComponentMPWorkFunctionUPP *  workFunction,
  void **                       refCon)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CallComponentGetPublicResource()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 4.0 and later
 */
extern ComponentResult 
CallComponentGetPublicResource(
  ComponentInstance   ci,
  OSType              resourceType,
  short               resourceID,
  Handle *            resource)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
    CallComponentDispatch is a CarbonLib routine that replaces CallComponent inline glue
    to call a component function.
 */
/*
 *  CallComponentDispatch()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
CallComponentDispatch(ComponentParameters * cp)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* UPP call backs */
/*
 *  NewComponentMPWorkFunctionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ComponentMPWorkFunctionUPP
NewComponentMPWorkFunctionUPP(ComponentMPWorkFunctionProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewComponentRoutineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ComponentRoutineUPP
NewComponentRoutineUPP(ComponentRoutineProcPtr userRoutine)   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewGetMissingComponentResourceUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern GetMissingComponentResourceUPP
NewGetMissingComponentResourceUPP(GetMissingComponentResourceProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeComponentMPWorkFunctionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeComponentMPWorkFunctionUPP(ComponentMPWorkFunctionUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeComponentRoutineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeComponentRoutineUPP(ComponentRoutineUPP userUPP)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeGetMissingComponentResourceUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeGetMissingComponentResourceUPP(GetMissingComponentResourceUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeComponentMPWorkFunctionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ComponentResult
InvokeComponentMPWorkFunctionUPP(
  void *                                  globalRefCon,
  ComponentMPWorkFunctionHeaderRecordPtr  header,
  ComponentMPWorkFunctionUPP              userUPP)            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeComponentRoutineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ComponentResult
InvokeComponentRoutineUPP(
  ComponentParameters *  cp,
  Handle                 componentStorage,
  ComponentRoutineUPP    userUPP)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeGetMissingComponentResourceUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeGetMissingComponentResourceUPP(
  Component                       c,
  OSType                          resType,
  short                           resID,
  void *                          refCon,
  Handle *                        resource,
  GetMissingComponentResourceUPP  userUPP)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/* ProcInfos */

/* MixedMode ProcInfo constants for component calls */
enum {
    uppComponentFunctionImplementedProcInfo    = 0x000002F0,
    uppGetComponentVersionProcInfo             = 0x000000F0,
    uppComponentSetTargetProcInfo              = 0x000003F0,
    uppCallComponentOpenProcInfo               = 0x000003F0,
    uppCallComponentCloseProcInfo              = 0x000003F0,
    uppCallComponentCanDoProcInfo              = 0x000002F0,
    uppCallComponentVersionProcInfo            = 0x000000F0,
    uppCallComponentRegisterProcInfo           = 0x000000F0,
    uppCallComponentTargetProcInfo             = 0x000003F0,
    uppCallComponentUnregisterProcInfo         = 0x000000F0,
    uppCallComponentGetMPWorkFunctionProcInfo  = 0x00000FF0,
    uppCallComponentGetPublicResourceProcInfo  = 0x00003BF0
};







#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __COMPONENTS__ */

