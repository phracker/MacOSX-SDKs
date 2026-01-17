/*
    File:       CMIOHardwareSystem.h

    Contains:   API for communicating with CoreMediaIO hardware

    Copyright:  © 2005-2010 by Apple Inc., all rights reserved.
*/


#if !defined(__CMIOHardwareSystem_h__)
#define __CMIOHardwareSystem_h__

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark Overview
/*!
    @header CMIOHardwareSystem
    The CMIOObjects in the DAL are arranged in a containment hierarchy, the root of the hierarchy being the one and only instance of the CMIOSystemObject class. The properties of the
    CMIOSystemObject describe the global settings such as the various default devices. The CMIOSystemObject also contains all the CMIODevices that are available.
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark Includes

#include <CoreFoundation/CFArray.h>
#include <CoreMediaIO/CMIOHardwareObject.h>


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIOSystemObject Types

/*!
    @typedef        CMIOHardwarePropertyID
    @abstract       A CMIOHardwarePropertyID is an integer that identifies a specific piece of information about the CMIOSystemObject.
*/
typedef CMIOObjectPropertySelector CMIOHardwarePropertyID;

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIOSystemObject Constants

/*!
    @enum           CMIOSystemObject Class Constants
    @abstract       Various constants related to the CMIOSystemObject.
    @discussion     
    @constant       kCMIOSystemObjectClassID
                        The CMIOClassID that identifies the CMIOSystemObject class.
    @constant       kCMIOObjectSystemObject
                        The CMIOObjectID that always refers to the one and only instance of the CMIOSystemObject.
*/
enum
{
    kCMIOSystemObjectClassID    = 'asys',
    kCMIOObjectSystemObject     = 1UL
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIOSystemObject Properties

/*!
    @enum           CMIOSystemObject Properties
    @abstract       CMIOObjectPropertySelector values that apply to the CMIOSystemObject.
    @discussion     The CMIOSystemObject has one scope, kCMIOObjectPropertyScopeGlobal, and only a master element.

    @constant       kCMIOHardwarePropertyProcessIsMaster
                        A UInt32 where 1 means that the current process contains the master instance of the DAL. The master instance of the DAL is the only instance in which plug-ins should
                        save/restore their devices' settings.
    @constant       kCMIOHardwarePropertyIsInitingOrExiting
                        A UInt32 whose value will be non-zero if the DAL is either in the midst of initializing or in the midst of exiting the process.
    @constant       kCMIOHardwarePropertyDevices
                        An array of the CMIODeviceIDs that represent all the devices currently available to the system.
    @constant       kCMIOHardwarePropertyDefaultInputDevice
                        The CMIODeviceID of the default input CMIODevice.
    @constant       kCMIOHardwarePropertyDefaultOutputDevice
                        The CMIODeviceID of the default output CMIODevice.
    @constant       kCMIOHardwarePropertyDeviceForUID
                        Using a AudioValueTranslation structure, this property translates the input CFStringRef containing a UID into the CMIODeviceID that refers to the CMIODevice
                        with that UID. This property will return kCMIODeviceUnknown if the given UID does not match any currently available CMIODevice.
    @constant       kCMIOHardwarePropertySleepingIsAllowed
                        A UInt32 where 1 means that the process will allow the CPU to idle sleep even if there is IO in progress. A 0 means that the CPU will not be allowed to idle
                        sleep. Note that this property won't affect when the CPU is forced to sleep.
    @constant       kCMIOHardwarePropertyUnloadingIsAllowed
                        A UInt32 where 1 means that this process wants the DAL to unload itself after a period of inactivity where there are no streams active and no listeners registered
                        with any CMIOObject.
    @constant       kCMIOHardwarePropertyPlugInForBundleID
                        Using a AudioValueTranslation structure, this property translates the input CFString containing a bundle ID into the CMIOObjectID of the CMIOPlugIn that
                        corresponds to it. This property will return kCMIOObjectUnkown if the given bundle ID doesn't match any CMIOPlugIns.
    @constant       kCMIOHardwarePropertyUserSessionIsActiveOrHeadless
                        A UInt32 where a value other than 0 indicates that the login session of the user of the process is either an active console session or a headless session.
    @constant       kCMIOHardwarePropertySuspendedBySystem
                        A UInt32 where a value of 0 indicates the hardware is not suspended due to a system action, and a value of 1 means that it is.
                        For example, if a fast user switch occurs, the system will suspend all devices. While suspended, no operartions can be performed on any devices.
                        This property is never settable.
    @constant       kCMIOHardwarePropertyAllowScreenCaptureDevices
                        A UInt32 where 1 means that screen capture devices will be presented to the process. A 0 means screen capture devices will be ignored. By default, this property is 1.
*/
enum
{
    kCMIOHardwarePropertyProcessIsMaster                = 'mast',
    kCMIOHardwarePropertyIsInitingOrExiting             = 'inot',
    kCMIOHardwarePropertyDevices                        = 'dev#',
    kCMIOHardwarePropertyDefaultInputDevice             = 'dIn ',
    kCMIOHardwarePropertyDefaultOutputDevice            = 'dOut',
    kCMIOHardwarePropertyDeviceForUID                   = 'duid',
    kCMIOHardwarePropertySleepingIsAllowed              = 'slep',
    kCMIOHardwarePropertyUnloadingIsAllowed             = 'unld',
    kCMIOHardwarePropertyPlugInForBundleID              = 'pibi',
    kCMIOHardwarePropertyUserSessionIsActiveOrHeadless  = 'user',
    kCMIOHardwarePropertySuspendedBySystem              = 'sbys',
    kCMIOHardwarePropertyAllowScreenCaptureDevices      = 'yes '
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif
