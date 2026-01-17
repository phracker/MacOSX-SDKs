/*
     File:       ColorSync/CMDeviceIntegration.h
 
     Contains:   Color Management Device Interfaces
 
     Version:    ColorSync-174.3.3~45
 
     Copyright:  © 2000-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __CMDEVICEINTEGRATION__
#define __CMDEVICEINTEGRATION__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __CMAPPLICATION__
#include <ColorSync/CMApplication.h>
#endif

#ifndef __CMICCPROFILE__
#include <ColorSync/CMICCProfile.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

/*
    The current versions of the data structure
    containing information on registered devices.
*/
enum {
  cmDeviceInfoVersion1          = 0x00010000,
  cmDeviceProfileInfoVersion1   = 0x00010000,
  cmDeviceProfileInfoVersion2   = 0x00020000
};

enum {
  cmCurrentDeviceInfoVersion    = cmDeviceInfoVersion1,
  cmCurrentProfileInfoVersion   = cmDeviceProfileInfoVersion1
};

/*
    Certain APIs require a device ID or profile ID.  
    In some cases, a "default ID" can be used.
*/
enum {
  cmDefaultDeviceID             = 0,
  cmDefaultProfileID            = 0
};

/*
    Possible values for device states accessible by the
    CMGetDeviceState() and CMSetDeviceState() APIs.
*/
enum {
  cmDeviceStateDefault          = 0x00000000,
  cmDeviceStateOffline          = 0x00000001,
  cmDeviceStateBusy             = 0x00000002,
  cmDeviceStateForceNotify      = (long)0x80000000,
  cmDeviceStateDeviceRsvdBits   = 0x00FF0000,
  cmDeviceStateAppleRsvdBits    = (long)0xFF00FFFF
};

/*
    Possible values for flags passed to the
    CMIterateDeviceProfiles() API.
    
    "Factory" profiles are registered via the
    CMSetDeviceFactoryProfiles() API.
    
    "Custom" profiles are those which are meant to take
    the place of the factory profiles, as a result of
    customization or calibration.  These profiles are
    registered via the CMSetDeviceProfiles() API.
    
    To retrieve all of the the former for all devices,
    use cmIterateFactoryDeviceProfiles as the flags
    value when calling CMIterateDeviceProfiles().
    
    To retrieve only the latter for all devices, use
    the cmIterateCustomDeviceProfiles, as the flags
    value when calling CMIterateDeviceProfiles().
    
    To get the profiles in use for all devices, use
    cmIterateCurrentDeviceProfiles as the flags value.
    This will replace the factory profiles with any
    overrides, yielding the currently used set.
    
    To get all profiles, without replacement, use
    cmIterateAllDeviceProfiles. 
*/
enum {
  cmIterateFactoryDeviceProfiles = 0x00000001,
  cmIterateCustomDeviceProfiles = 0x00000002,
  cmIterateCurrentDeviceProfiles = 0x00000003,
  cmIterateAllDeviceProfiles    = 0x00000004,
  cmIterateDeviceProfilesMask   = 0x0000000F
};

/*
    Errors returned by CMDeviceIntegration APIs
*/
enum {
  cmDeviceDBNotFoundErr         = -4227, /* Prefs not found/loaded */
  cmDeviceAlreadyRegistered     = -4228, /* Re-registration of device */
  cmDeviceNotRegistered         = -4229, /* Device not found */
  cmDeviceProfilesNotFound      = -4230, /* Profiles not found */
  cmInternalCFErr               = -4231 /* CoreFoundation failure */
};


/*
   Clients can register for notifications of device changes:
      Notification         Description                           Sent by API
    ----------------      -----------                           -----------
      DeviceRegistered      a device was registered               CMRegisterColorDevice()  
      DeviceUnregistered    a device was unregistered             CMUnregisterColorDevice()
      DeviceOnline          a device's state changed to Online    CMSetDeviceState()
      DeviceOffline         a device's state changed to Offline   CMSetDeviceState()
      DeviceState           a device's state changed              CMSetDeviceState()
      DefaultDevice         a class' default device changed       CMSetDefaultDevice()
      DeviceProfiles        a device's profiles changed           CMSetDeviceFactoryProfiles(), CMSetDeviceProfiles()
      DefaultDeviceProfile  a device's default profile ID changed CMSetDeviceDefaultProfileID()
      DisplayDeviceProfiles a display device's profiles changed   CMSetDeviceFactoryProfiles(), CMSetDeviceProfiles()
*/
#define kCMDeviceRegisteredNotification     CFSTR("CMDeviceRegisteredNotification")
#define kCMDeviceUnregisteredNotification   CFSTR("CMDeviceUnregisteredNotification")
#define kCMDeviceOnlineNotification         CFSTR("CMDeviceOnlineNotification")
#define kCMDeviceOfflineNotification        CFSTR("CMDeviceOfflineNotification")
#define kCMDeviceStateNotification          CFSTR("CMDeviceStateNotification")
#define kCMDefaultDeviceNotification        CFSTR("CMDefaultDeviceNotification")
#define kCMDeviceProfilesNotification       CFSTR("CMDeviceProfilesNotification")
#define kCMDefaultDeviceProfileNotification CFSTR("CMDefaultDeviceProfileNotification")
#define kCMDisplayDeviceProfilesNotification CFSTR("CMDisplayDeviceProfilesNotification")

/*
    Device state data.
*/
typedef UInt32                          CMDeviceState;
/*
    A CMDeviceID must be unique within a device's class.
*/
typedef UInt32                          CMDeviceID;
/*
    A CMDeviceProfileID must only be unique per device.
*/
typedef UInt32                          CMDeviceProfileID;
/*
    DeviceClass type.
*/
enum {
  cmScannerDeviceClass          = 'scnr',
  cmCameraDeviceClass           = 'cmra',
  cmDisplayDeviceClass          = 'mntr',
  cmPrinterDeviceClass          = 'prtr',
  cmProofDeviceClass            = 'pruf'
};

typedef OSType                          CMDeviceClass;
/*
    CMDeviceScope
    Structure specifying a device's or a device setting's scope.
*/
struct CMDeviceScope {
  CFStringRef         deviceUser;             /* kCFPreferencesCurrentUser | _AnyUser */
  CFStringRef         deviceHost;             /* kCFPreferencesCurrentHost | _AnyHost */
};
typedef struct CMDeviceScope            CMDeviceScope;
typedef CMDeviceScope                   CMDeviceProfileScope;
/*
    CMDeviceInfo
    Structure containing information on a given device.
*/
struct CMDeviceInfo {
  UInt32              dataVersion;            /* cmDeviceInfoVersion1 */
  CMDeviceClass       deviceClass;            /* device class */
  CMDeviceID          deviceID;               /* device ID */
  CMDeviceScope       deviceScope;            /* device's scope */
  CMDeviceState       deviceState;            /* Device State flags */
  CMDeviceProfileID   defaultProfileID;       /* Can change */
  CFDictionaryRef *   deviceName;             /* Ptr to storage for CFDictionary of */
                                              /* localized device names (could be nil) */
  UInt32              profileCount;           /* Count of registered profiles */
  UInt32              reserved;               /* Reserved for use by ColorSync */
};
typedef struct CMDeviceInfo             CMDeviceInfo;
typedef CMDeviceInfo *                  CMDeviceInfoPtr;
/*
    CMDeviceProfileInfo
    Structure containing information on a device profile.
*/
struct CMDeviceProfileInfo {
  UInt32              dataVersion;            /* cmDeviceProfileInfoVersion1 */
  CMDeviceProfileID   profileID;              /* The identifier for this profile */
  CMProfileLocation   profileLoc;             /* The profile's location */
  CFDictionaryRef     profileName;            /* CFDictionary of localized profile names */
  UInt32              reserved;               /* Reserved for use by ColorSync */
};
typedef struct CMDeviceProfileInfo      CMDeviceProfileInfo;
struct NCMDeviceProfileInfo {
  UInt32              dataVersion;            /* cmDeviceProfileInfoVersion2 */
  CMDeviceProfileID   profileID;              /* The identifier for this profile */
  CMProfileLocation   profileLoc;             /* The profile's location */
  CFDictionaryRef     profileName;            /* CFDictionary of localized profile names */
  CMDeviceProfileScope  profileScope;         /* The scope this profile applies to */
  UInt32              reserved;               /* Reserved for use by ColorSync */
};
typedef struct NCMDeviceProfileInfo     NCMDeviceProfileInfo;
/*
    CMDeviceProfileArray
    Structure containing the profiles for a device.
*/
struct CMDeviceProfileArray {
  UInt32              profileCount;           /* Count of profiles in array */
  CMDeviceProfileInfo  profiles[1];           /* The profile info records */
};
typedef struct CMDeviceProfileArray     CMDeviceProfileArray;
typedef CMDeviceProfileArray *          CMDeviceProfileArrayPtr;
/*
    Caller-supplied iterator functions
*/
typedef CALLBACK_API_C( OSErr , CMIterateDeviceInfoProcPtr )(const CMDeviceInfo *deviceInfo, void *refCon);
typedef CALLBACK_API_C( OSErr , CMIterateDeviceProfileProcPtr )(const CMDeviceInfo *deviceInfo, const NCMDeviceProfileInfo *profileInfo, void *refCon);
/*
    Device Registration
*/
/*
 *  CMRegisterColorDevice()
 *  
 *  Summary:
 *    Registers a device with ColorSync
 *  
 *  Discussion:
 *    For a device to be recognized by ColorSync it needs to register
 *    itself via this API.  After calling this API, the
 *    CMSetDeviceFactoryProfiles API should be called to specify the
 *    initial modes and profiles for the device. Registration need only
 *    happen once, when the device is installed.
 *  
 *  Parameters:
 *    
 *    deviceClass:
 *      (in) Device class to add
 *    
 *    deviceID:
 *      (in) Device id to add
 *    
 *    deviceName:
 *      (in) Dictionary containing localized names
 *    
 *    deviceScope:
 *      (in) Scope where information should be stored
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMRegisterColorDevice(
  CMDeviceClass          deviceClass,
  CMDeviceID             deviceID,
  CFDictionaryRef        deviceName,
  const CMDeviceScope *  deviceScope)                         AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CMUnregisterColorDevice()
 *  
 *  Summary:
 *    Unregisters a device with ColorSync
 *  
 *  Discussion:
 *    When a device is no longer to be used on a system (as opposed to
 *    just being offline), it should be unregistered. If a device is
 *    temporariy shut down or disconnected it need not be unregistered
 *    unless the device driver knows that it will not be used (e.g.
 *    being deinstalled) or cannot access the device profiles without
 *    the device.
 *  
 *  Parameters:
 *    
 *    deviceClass:
 *      (in) Device class to remove
 *    
 *    deviceID:
 *      (in) Device id to remove
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMUnregisterColorDevice(
  CMDeviceClass   deviceClass,
  CMDeviceID      deviceID)                                   AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
    Default Device accessors
*/
/*
 *  CMSetDefaultDevice()
 *  
 *  Summary:
 *    Specifeis the default device of a class
 *  
 *  Parameters:
 *    
 *    deviceClass:
 *      (in) Device class to modify
 *    
 *    deviceID:
 *      (in) Device id to make default
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMSetDefaultDevice(
  CMDeviceClass   deviceClass,
  CMDeviceID      deviceID)                                   AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CMGetDefaultDevice()
 *  
 *  Summary:
 *    Returns the default device of a class
 *  
 *  Parameters:
 *    
 *    deviceClass:
 *      (in) Device class to query
 *    
 *    deviceID:
 *      (out) Returns default device for class
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMGetDefaultDevice(
  CMDeviceClass   deviceClass,
  CMDeviceID *    deviceID)                                   AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
    Device Profile Registration & Access
*/
/*
 *  CMSetDeviceFactoryProfiles()
 *  
 *  Summary:
 *    Registers a device's factory profiles with ColorSync
 *  
 *  Discussion:
 *    This API establishes the profiles used by a particular device for
 *    it's various modes. It is meant to be called once, right after
 *    device registration to notify ColorSync of the device's profiles.
 *  
 *  Parameters:
 *    
 *    deviceClass:
 *      (in) Device class to modify
 *    
 *    deviceID:
 *      (in) Device id to modify
 *    
 *    defaultProfID:
 *      (in) The id of the default profile
 *    
 *    deviceProfiles:
 *      (in) List of profile IDs, names, and locations
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMSetDeviceFactoryProfiles(
  CMDeviceClass                 deviceClass,
  CMDeviceID                    deviceID,
  CMDeviceProfileID             defaultProfID,
  const CMDeviceProfileArray *  deviceProfiles)               AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CMGetDeviceFactoryProfiles()
 *  
 *  Summary:
 *    Returns all the device's factory profiles
 *  
 *  Discussion:
 *    This API allows the caller to retrieve the original profiles for
 *    a device. These may differ from the profiles currently in use for
 *    that device in the case where factory profiles have been
 *    overriden with custom profiles.
 *  
 *  Parameters:
 *    
 *    deviceClass:
 *      (in) Device class to query
 *    
 *    deviceID:
 *      (in) Device id to query (can be cmDefaultDeviceID)
 *    
 *    defaultProfID:
 *      (out) Returns id of default mode (optional)
 *    
 *    arraySize:
 *      (in/out) Size of buffer passed in / Returns size of array in
 *      bytes
 *    
 *    deviceProfiles:
 *      (out) Returns list of profile IDs, names, and locations
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMGetDeviceFactoryProfiles(
  CMDeviceClass           deviceClass,
  CMDeviceID              deviceID,
  CMDeviceProfileID *     defaultProfID,        /* can be NULL */
  UInt32 *                arraySize,
  CMDeviceProfileArray *  deviceProfiles)                     AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CMSetDeviceProfiles()
 *  
 *  Summary:
 *    Specifies custom overide profiles for a device
 *  
 *  Discussion:
 *    This API provides a way to overide the factory profiles of a
 *    device for a particular mode or modes. To set custom profiles,
 *    the profileScope and deviceProfiles params must be valid. To
 *    remove all custom profiles of a device, pass in nil for the
 *    profileScope and deviceProfiles parameters.
 *  
 *  Parameters:
 *    
 *    deviceClass:
 *      (in) Device class to change
 *    
 *    deviceID:
 *      (in) Device id to change (can be cmDefaultDeviceID)
 *    
 *    profileScope:
 *      (in) Scope where information should be stored (or nil to remove
 *      all)
 *    
 *    deviceProfiles:
 *      (in) Profiles to set (or nil to remove all)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMSetDeviceProfiles(
  CMDeviceClass                 deviceClass,
  CMDeviceID                    deviceID,
  const CMDeviceProfileScope *  profileScope,         /* can be NULL */
  const CMDeviceProfileArray *  deviceProfiles)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CMGetDeviceProfiles()
 *  
 *  Summary:
 *    Returns all the device's current profiles
 *  
 *  Discussion:
 *    This API allows the caller to retrieve the current profiles for a
 *    device.
 *  
 *  Parameters:
 *    
 *    deviceClass:
 *      (in) Device class to query
 *    
 *    deviceID:
 *      (in) Device id to query (can be cmDefaultDeviceID)
 *    
 *    arraySize:
 *      (in/out) Size of buffer passed in / Returns size of array in
 *      bytes
 *    
 *    deviceProfiles:
 *      (out) Returns list of profile IDs, names, and locations
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMGetDeviceProfiles(
  CMDeviceClass           deviceClass,
  CMDeviceID              deviceID,
  UInt32 *                arraySize,
  CMDeviceProfileArray *  deviceProfiles)                     AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CMSetDeviceDefaultProfileID()
 *  
 *  Summary:
 *    Specifies a device's default profile mode
 *  
 *  Discussion:
 *    This API allows the caller to change the default profile ID for a
 *    device. The initial default is established when
 *    CMSetDeviceFactoryProfiles is called.
 *  
 *  Parameters:
 *    
 *    deviceClass:
 *      (in) Device class to modify
 *    
 *    deviceID:
 *      (in) Device id to modify (can be cmDefaultDeviceID)
 *    
 *    defaultProfID:
 *      (in) New device default
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMSetDeviceDefaultProfileID(
  CMDeviceClass       deviceClass,
  CMDeviceID          deviceID,
  CMDeviceProfileID   defaultProfID)                          AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CMGetDeviceDefaultProfileID()
 *  
 *  Summary:
 *    Returns the default profile ID for a device
 *  
 *  Parameters:
 *    
 *    deviceClass:
 *      (in) Device class to query
 *    
 *    deviceID:
 *      (in) Device id to query (can be cmDefaultDeviceID)
 *    
 *    defaultProfID:
 *      (out) Returns id of default profile
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMGetDeviceDefaultProfileID(
  CMDeviceClass        deviceClass,
  CMDeviceID           deviceID,
  CMDeviceProfileID *  defaultProfID)                         AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CMSetDeviceProfile()
 *  
 *  Summary:
 *    Specifies a custom overide profile for a device
 *  
 *  Discussion:
 *    This API provides a way to change one of the profiles used by a
 *    device for a particular mode. It can be called after device
 *    registration by calibration applications to reset a device's
 *    profile from its factory default to a custom calibrated profile.
 *  
 *  Parameters:
 *    
 *    deviceClass:
 *      (in) Device class to modify
 *    
 *    deviceID:
 *      (in) Device id to modify (can be cmDefaultDeviceID)
 *    
 *    profileScope:
 *      (in) Scope where information should be stored
 *    
 *    profileID:
 *      (in) Profile id to modify (can be cmDefaultProfileID)
 *    
 *    profileLoc:
 *      (in) New profile location
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMSetDeviceProfile(
  CMDeviceClass                 deviceClass,
  CMDeviceID                    deviceID,
  const CMDeviceProfileScope *  profileScope,
  CMDeviceProfileID             profileID,
  const CMProfileLocation *     profileLoc)                   AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CMGetDeviceProfile()
 *  
 *  Summary:
 *    Returns the location of the current profile for a given device
 *    class, device ID, and profile ID
 *  
 *  Parameters:
 *    
 *    deviceClass:
 *      (in) Device class to query
 *    
 *    deviceID:
 *      (in) Device id to query (can be cmDefaultDeviceID)
 *    
 *    profileID:
 *      (in) Profile id to query (can be cmDefaultDeviceID)
 *    
 *    profileLoc:
 *      (out) Returns profile location
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMGetDeviceProfile(
  CMDeviceClass        deviceClass,
  CMDeviceID           deviceID,
  CMDeviceProfileID    profileID,
  CMProfileLocation *  profileLoc)                            AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
    Other Device State/Info accessors
*/
/*
 *  CMSetDeviceState()
 *  
 *  Summary:
 *    Specifies the state of a device
 *  
 *  Discussion:
 *    This API provides access for the device management layer to
 *    update the state of a particular device. For example, a device
 *    can be offline, busy, calibrated, etc. The state data passed in
 *    replaces the old state data with the new value.
 *  
 *  Parameters:
 *    
 *    deviceClass:
 *      (in) Device class to modify
 *    
 *    deviceID:
 *      (in) Device id to modify (can be cmDefaultDeviceID)
 *    
 *    deviceState:
 *      (in) New device state
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMSetDeviceState(
  CMDeviceClass   deviceClass,
  CMDeviceID      deviceID,
  CMDeviceState   deviceState)                                AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CMGetDeviceState()
 *  
 *  Summary:
 *    Returns the state of a device.
 *  
 *  Parameters:
 *    
 *    deviceClass:
 *      (in) Device class to query
 *    
 *    deviceID:
 *      (in) Device id to query (can be cmDefaultDeviceID)
 *    
 *    deviceState:
 *      (out) Returns device state
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMGetDeviceState(
  CMDeviceClass    deviceClass,
  CMDeviceID       deviceID,
  CMDeviceState *  deviceState)                               AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CMGetDeviceInfo()
 *  
 *  Summary:
 *    Returns information about a device.
 *  
 *  Discussion:
 *    This API returns information about a registered device. If, on
 *    input, deviceInfo->deviceName is nil then the name is not
 *    returned. If the caller wants the device name dictionary
 *    returned, then the caller should provide in
 *    deviceInfo->deviceName the address where this API should store
 *    the CFDictionaryRef. The caller is responsible for disposing of
 *    the name dictionary.
 *  
 *  Parameters:
 *    
 *    deviceClass:
 *      (in) Device class to query
 *    
 *    deviceID:
 *      (in) Device id to query (can be cmDefaultDeviceID)
 *    
 *    deviceInfo:
 *      (in/out) Returns device information
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMGetDeviceInfo(
  CMDeviceClass   deviceClass,
  CMDeviceID      deviceID,
  CMDeviceInfo *  deviceInfo)                                 AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
    Device Info & Profile Iterators
*/
/*
 *  CMIterateColorDevices()
 *  
 *  Summary:
 *    Returns information about all devices to a callback procedure.
 *  
 *  Discussion:
 *    This API allows the caller to get device information about all
 *    registered color devices.  If provided, the supplied proceedure
 *    will be called once for each registered device, passing in the
 *    device info and the supplied refcon. If the caller passes in a
 *    pointer to a seed value that is the same as the current seed
 *    value, then the callback proc is not called.
 *  
 *  Parameters:
 *    
 *    proc:
 *      (in) Client callback proc (optional)
 *    
 *    seed:
 *      (in/out) seed value (optional)
 *    
 *    count:
 *      (out) Returns count of devices (optional)
 *    
 *    refCon:
 *      (in) Passed to callback proc (optional)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMIterateColorDevices(
  CMIterateDeviceInfoProcPtr   proc,
  UInt32 *                     seed,         /* can be NULL */
  UInt32 *                     count,        /* can be NULL */
  void *                       refCon)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CMIterateDeviceProfiles()
 *  
 *  Summary:
 *    Returns information about profiles of all devices to a callback
 *    procedure.
 *  
 *  Discussion:
 *    This API allows the caller to get device information about
 *    profiles of all registered color devices.  If provided, the
 *    supplied proceedure will be called once for each registered
 *    device, passing in the device info, the profile info and the
 *    supplied refcon. If the caller passes in a pointer to a seed
 *    value that is the same as the current seed value, then the
 *    callback proc is not called.
 *  
 *  Parameters:
 *    
 *    proc:
 *      (in) Client callback proc (optional)
 *    
 *    seed:
 *      (in/out) seed value (optional)
 *    
 *    count:
 *      (out) Returns count of devices (optional)
 *    
 *    flags:
 *      (in) Options for which set of profiles are to be iterated. It
 *      can have the following possible values:
 *      cmIterateFactoryDeviceProfiles, cmIterateCustomDeviceProfiles,
 *      cmIterateCurrentDeviceProfiles, cmIterateAllDeviceProfiles or
 *      0. The flag value 0 behaves like cmIterateCurrentDeviceProfiles.
 *    
 *    refCon:
 *      (in) Passed to callback proc (optional)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMIterateDeviceProfiles(
  CMIterateDeviceProfileProcPtr   proc,
  UInt32 *                        seed,         /* can be NULL */
  UInt32 *                        count,        /* can be NULL */
  UInt32                          flags,
  void *                          refCon)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __CMDEVICEINTEGRATION__ */

