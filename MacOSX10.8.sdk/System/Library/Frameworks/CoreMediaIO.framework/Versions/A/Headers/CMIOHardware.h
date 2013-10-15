/*
    File:       CMIOHardware.h

    Contains:   API for communicating with CoreMediaIO hardware

    Copyright:  © 2005-2010 by Apple Inc., all rights reserved.
*/


#if !defined(__CMIOHardware_h__)
#define __CMIOHardware_h__

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark Overview
/*!
    @header CMIOHardware
    The CoreMediaIO device abstraction layer (DAL) provides an abstraction through which applications can access media hardware. To do this, the DAL provides a small set of objects that
    provide access to the various pieces of the system. The base class for all CoreMediaIO objects is the class CMIOObject. Other important classes include CMIOSystemObject, CMIODevice,
    CMIOStream, and CMIOControl.
    
    The class of a CMIOObject determines the basic functionality of the object in terms of what functions will operate on it as well as the set of properties that can be expected to be
    implemented by the object. The set of available classes for objects is limited to those defined here. There are no other classes. The set of classes is arranged in a hierarchy such that
    one class inherits the properties/routines of it's super class.



    The base class for all CMIOObjects is the class CMIOObject. As such, each CMIOObject will provide basic properties such as it's class, it's human readable name, and the other
    CMIOObjects it contains. Other important classes include CMIOSystemObject, CMIODevice, and CMIOStream.

    The CMIOObjects in the DAL are arranged in a containment hierarchy. The root of the hierarchy is the one and only instance of the CMIOSystemObject class. The properties of the
    CMIOSystemObject describe the process global settings such as the various default devices and the notification run loop. The CMIOSystemObject also contains all the CMIODevices
    that are available.

    Instances of the CMIODevice class encapsulate individual media devices.
    
    CMIODevices contain instances of the CMIOStream class. A CMIOStream represents a single conduit of data for transferring across the user/kernel boundary. As such, CMIOStreams
    are the gatekeepers of format information. Each has it's own format and list of available formats. These formats are not constrained, and may include encoded formats and non-media
    formats.

    Both CMIODevices and CMIOStreams can contain instances of the CMIOControl class or it's many subclasses. A CMIOControl provides properties that describe/manipulate a
    particular aspect of the object such as gain, mute, data source selection, etc.
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark Includes

#include <CoreMediaIO/CMIOHardwareObject.h>
#include <CoreMediaIO/CMIOHardwareSystem.h>
#include <CoreMediaIO/CMIOHardwareDevice.h>
#include <CoreMediaIO/CMIOHardwareStream.h>
#include <CoreMediaIO/CMIOHardwareControl.h>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark Error Constants

/*!
    @enum           Error Constants
    @abstract       The error constants unique to the DAL.
    @discussion     These are the error constants that are unique to the DAL. Note that the DAL's functions can and will return other codes that are not listed here. While these constants
                    give a general idea of what might have gone wrong during the execution of an API call, if an API call returns anything other than kCMIOHardwareNoError it is to be
                    viewed as the same failure regardless of what constant is actually returned.
    @constant       kCMIOHardwareNoError
                        The function call completed successfully.
    @constant       kCMIOHardwareNotStoppedError
                        The function call requires that the hardware be stopped but it isn't.
    @constant       kCMIOHardwareNotRunningError
                        The function call requires that the hardware be running but it isn't.
    @constant       kCMIOHardwareUnspecifiedError
                        The function call failed while doing something that doesn't provide any error messages.
    @constant       kCMIOHardwareUnknownPropertyError
                        The CMIOObject doesn't know about the property at the given address.
    @constant       kCMIOHardwareBadPropertySizeError
                        An improperly sized buffer was provided when accessing the data of a property.
    @constant       kCMIOHardwareIllegalOperationError
                        The requested operation couldn't be completed.
    @constant       kCMIOHardwareBadObjectError
                        The CMIOObjectID passed to the function doesn't map to a valid CMIOObject.
    @constant       kCMIOHardwareBadDeviceError
                        The CMIODeviceID passed to the function doesn't map to a valid CMIODevice.
    @constant       kCMIOHardwareBadStreamError
                        The CMIOStreamID passed to the function doesn't map to a valid CMIOStream.
    @constant       kCMIOHardwareUnsupportedOperationError
                        The CMIOObject doesn't support the requested operation.
    @constant       kCMIOHardwareSuspendedBySystemError
                        The function call failed because because access been suspended by the system.
    @constant       kCMIODeviceUnsupportedFormatError
                        The CMIOStream doesn't support the requested format.
    @constant       kCMIODevicePermissionsError
                        The requested operation can't be completed because the process doesn't have permission.
*/
enum
{
    kCMIOHardwareNoError                    = 0,
    kCMIOHardwareNotStoppedError            = 'run ',
    kCMIOHardwareNotRunningError            = 'stop',
    kCMIOHardwareUnspecifiedError           = 'what',
    kCMIOHardwareUnknownPropertyError       = 'who?',
    kCMIOHardwareBadPropertySizeError       = '!siz',
    kCMIOHardwareIllegalOperationError      = 'nope',
    kCMIOHardwareBadObjectError             = '!obj',
    kCMIOHardwareBadDeviceError             = '!dev',
    kCMIOHardwareBadStreamError             = '!str',
    kCMIOHardwareUnsupportedOperationError  = 'unop',
    kCMIOHardwareSuspendedBySystemError     = 'deny',
    kCMIODeviceUnsupportedFormatError       = '!dat',
    kCMIODevicePermissionsError             = '!hog'
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIOPlugIn Constants

/*!
    @enum           CMIOPlugIn Class Constants
    @abstract       Various constants related to CMIOPlugIns.
    @discussion     
    @constant       kCMIOPlugInClassID
                        The CMIOClassID that identifies the CMIOPlugIn class.
*/
enum
{
    kCMIOPlugInClassID  = 'aplg'
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIOPlugIn Properties

/*!
    @enum           CMIOPlugIn Properties
    @abstract       CMIOObjectPropertySelector values that apply to CMIOPlugIns.
    @discussion     CMIOPlugIn is a subclass of CMIOObject that represents a plug-in loaded by the DAL that conforms to the API in <CMIOHardware/CMIOHardwarePlugIn.h>. CMIOPlugIns have
                    one scope, kCMIOObjectPropertyScopeGlobal, and only a master element.
    @constant       kCMIOPlugInPropertyBundleID
                        A CFString that contains the bundle identifier for the CMIOPlugIn. The caller is responsible for releasing the returned CFObject.
*/
enum
{
    kCMIOPlugInPropertyBundleID = 'piid'
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif
#endif
