/*
     File:       DiscRecording/DRCoreDevice.h
 
     Contains:   Device interfaces for DiscRecording.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef _H_DRCoreDevice
#define _H_DRCoreDevice

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef _H_DRCoreObject
#include <DiscRecording/DRCoreObject.h>
#endif

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

#ifndef _MATH_H_
#include <math.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _IOKIT_IOKITLIB_H
#include <IOKit/IOKitLib.h>
#endif

/*!
	@typedef DRDeviceRef
	This is the type of a reference to DRDevices.
*/
typedef struct __DRDevice* DRDeviceRef;

/*!
	@function	DRDeviceGetTypeID
	@abstract	Returns the type identifier of all DRDevice instances.
*/
extern
CFTypeID DRDeviceGetTypeID()
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRCopyDeviceArray
	@abstract	Returns an array of all the writable devices connected to the system at the time.
	@discussion	Devices can come and go on the system at any time thanks to Firewire, USB and even
				things like MediaBay in PowerBooks. Therefore there's no way to get a list of devices
				at any particular time that is guaranteed to be correct for the lifetime of the 
				program. In general, knowing that device existence is dynamic, it's better to 
				listen for <tt>kDRDeviceAppearedNotification</tt> and <tt>kDRDeviceDisappearedNotification</tt>
				notifications and keep your own list of devices attached. This function can be useful for 
				initially populating that list of devices, but shouldn't be relied on for long term storage.
	@result		A CFArray containg the devices attached to the computer at the time the function 
				is called.
*/
extern
CFArrayRef DRCopyDeviceArray()
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRDeviceCopyDeviceForBSDName
	@abstract	Returns the device reference corresponding the the BSD device name passed in.
	@param		name	The /dev entry for the device (i.e., disk1)
	@result		A DRDevice reference for the device corresponding to the bsdName.
*/
extern
DRDeviceRef DRDeviceCopyDeviceForBSDName(CFStringRef name)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRDeviceCopyDeviceForIORegistryEntryPath
	@abstract	Returns the device reference corresponding the the IORegistry entry.
	@param		path	The IORegistry entry path corresponding to the device. 
	@result		A DRDevice reference for the device corresponding to the IORegistry entry path.
*/
extern
DRDeviceRef DRDeviceCopyDeviceForIORegistryEntryPath(CFStringRef path)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRDeviceIsValid
	@abstract	Determines whether the device is still attached and turned on.
	@discussion	Since devices can come and go while a client still has a reference to them,
				this function is provided so clients can check to see if a device reference
				they are holding on to is still able to be used properly.
	@param		device	The device reference to check.
	@result		A boolean indicating whether the device reference is still usable (TRUE) or not (FALSE).
*/
extern
Boolean DRDeviceIsValid(DRDeviceRef device)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRDeviceOpenTray
	@abstract	Command the device to open up it's tray.
	@discussion	This function will open the tray of the device (if it has one) if and only if
				the device does not currently have mounted media. 
	@param		device	The device reference for which open the tray.
	@result		An error code indicating if the tray could be opened.
*/
extern
OSStatus DRDeviceOpenTray(DRDeviceRef device)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRDeviceCloseTray
	@abstract	Command the device to close it's tray.
	@discussion	This function will close the tray of the device (if it has one). 
	@param		device	The device reference for which close the tray.
	@result		An error code indicating if the tray could be closed.
*/
extern
OSStatus DRDeviceCloseTray(DRDeviceRef device)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRDeviceEjectMedia
	@abstract	Command the device to unmount and eject media.
	@discussion	If the media cannot be unmounted, then this function will fail and return an error.
				If there is no media in the drive, then this is functionally equivalent to 
				DRDeviceOpenTray.
	@param		device	The device reference for which eject media.
	@result		An error code indicating whether the media could be ejected.
*/
extern
OSStatus DRDeviceEjectMedia(DRDeviceRef device)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRDeviceAcquireMediaReservation
	@abstract	Indicate an interest in the blank media reservation.
	@discussion	Blank media participates in a reservation system thats allows applications to express
				their claim on blank media to other applications.  Indicating an interest in the reservation
				isn't enough to assume its been acquired, as there are likely to be other applications in
				the system whom have also indicated an interest in the blank media reservation.  You will
				receive a kDRDeviceStatusChangedNotification with a value of <tt>TRUE</tt> for the
				kDRDeviceMediaIsReservedKey when the blank media reservation has been acquired.
				
				This function may be called multiple times. Each time it is called, a call to
				DRDeviceReleaseMediaReservation must be made at a later time, otherwise the process will
				never fully rescind its interest in the blank media reservation.
	@param		device	The device reference for which to indicate an interest.
*/
extern
void DRDeviceAcquireMediaReservation(DRDeviceRef device)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRDeviceReleaseMediaReservation
	@abstract	Rescind an interest in the blank media reservation.
	@discussion	The interest in the blank media reservations will be rescinded.  If the process currently
				has an acquired reservation, it will be released and passed on to the next interested process.
	@param		device	The device reference for which to rescind an interest.
*/
extern
void DRDeviceReleaseMediaReservation(DRDeviceRef device)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRDeviceAcquireExclusiveAccess
	@abstract	Acquire exclusive device access.
	@discussion	Attempts to acquire an exclusive access session with the device. If 
				this is accuired, the device is unusable by any other process. Because 
				of this all volumes mounted from media in the drive must be unmounted
				before exclusive access can be granted.
				
				This function may be called multiple times. Each time it is called,
				a call to DRDeviceReleaseExclusiveAccess must be made at a later time,
				otherwise the process will never release its exclusive access.
	@param		device	The device reference for which to acquire exclusive access.
	@result		An error code indicating whether exclusive access could be acquired.
*/
extern
OSStatus DRDeviceAcquireExclusiveAccess(DRDeviceRef device)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRDeviceReleaseExclusiveAccess
	@abstract	Release exclusive device access.
	@discussion	This function will release one request for exclusice access made by a process
				that called DRDeviceAcquireExclusiveAccess. A call to this function must be
				made for every call to DRDeviceAcquireExclusiveAccess, otherwise the process
				will never release its exclusive access.
	@param		device	The device reference for which to release exclusive access.
*/
extern
void DRDeviceReleaseExclusiveAccess(DRDeviceRef device)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceAppearedNotification
	@discussion	DR uses this string constant to notify you that a device has become available.
				Since device existence is dynamic, you should maintain your own list 
				of attached devices and rely on notifications to keep the list current.
*/
extern const CFStringRef kDRDeviceAppearedNotification				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceDisappearedNotification
	@discussion	DR uses this string constant to notify you that a device is no longer available.
				Since device existence is dynamic, you should maintain your own list 
				of attached devices and rely on notifications to keep the list current.
 */
extern const CFStringRef kDRDeviceDisappearedNotification			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRDeviceCopyInfo
	@abstract	Returns information about the device.
	@discussion	The dictionary this function returns contains information that
				identifies the device and describes its capabilites (such as if it
				can burn to CDs, DVDs, it's vendor's name, the product identifier, etc).
				describing the devices capabilities
	@param		device	The device to obtain information for.
	@result		A CFDictionary of information identifying the device and it's capabilities.
*/
extern
CFDictionaryRef DRDeviceCopyInfo(DRDeviceRef device)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*---------------
 *	Keys for the dictionary returned by DRDeviceCopyInfo 
 */
/*!
	@const kDRDeviceSupportLevelKey
	@discussion	A key for the dictionary returned by DRDeviceCopyInfo. The value of this key is 
				a CFString indicating how well the engine supports the device.
*/
extern const CFStringRef kDRDeviceSupportLevelKey					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceSupportLevelNone
	@discussion	One of the values for kDRDeviceSupportLevelKey. This value indicates that
				the engine provides no support for this device.
*/
extern const CFStringRef kDRDeviceSupportLevelNone					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceSupportLevelVendorSupported
	@discussion	One of the values for kDRDeviceSupportLevelKey. This value indicates that
				the engine supports the vendor of this device.
*/
extern const CFStringRef kDRDeviceSupportLevelVendorSupported		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceSupportLevelAppleSupported
	@discussion	One of the values for kDRDeviceSupportLevelKey. This value indicates that
				the engine fully supports the device.
*/
extern const CFStringRef kDRDeviceSupportLevelAppleSupported		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceSupportLevelAppleShipping
	@discussion	One of the values for kDRDeviceSupportLevelKey. This value indicates that
				the engine fully supports the device and it has shipped in a machine made by Apple.
*/
extern const CFStringRef kDRDeviceSupportLevelAppleShipping			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceIORegistryEntryPathKey
	@discussion	A key for the dictionary returned by DRDeviceCopyInfo. The value of this key is 
				a CFString containing a copy of the path to the device entry in the IORegistry.
*/
extern const CFStringRef kDRDeviceIORegistryEntryPathKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceWriteCapabilitiesKey
	@discussion	A key for the dictionary returned by DRDeviceCopyInfo. The value of this key is 
				a CFDictionary containing the capabilities the drive has for writing to different 
				media.
*/
extern const CFStringRef kDRDeviceWriteCapabilitiesKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceCanWriteKey
	@discussion	A key for the dictionary for kDRDeviceWriteCapabilitiesKey. The value of this key 
				is a CFBoolean indicating if the device can write to some type of media.
*/
extern const CFStringRef kDRDeviceCanWriteKey						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceCanWriteCDKey
	@discussion	A key for the dictionary for kDRDeviceWriteCapabilitiesKey. The value of this key 
				is a CFBoolean indicating if the device can write to some type of CD based media.
*/
extern const CFStringRef kDRDeviceCanWriteCDKey						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceCanWriteCDRKey
	@discussion	A key for the dictionary for kDRDeviceWriteCapabilitiesKey. The value of this key 
				is a CFBoolean indicating if the device can write to CD-R media.
*/
extern const CFStringRef kDRDeviceCanWriteCDRKey					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceCanWriteCDRWKey
	@discussion	A key for the dictionary for kDRDeviceWriteCapabilitiesKey. The value of this key 
				is a CFBoolean indicating if the device can write to CD-RW media.
*/
extern const CFStringRef kDRDeviceCanWriteCDRWKey					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceCanWriteDVDKey
	@discussion	A key for the dictionary for kDRDeviceWriteCapabilitiesKey. The value of this key 
				is a CFBoolean indicating if the device can write to some type of DVD based media.
*/
extern const CFStringRef kDRDeviceCanWriteDVDKey					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceCanWriteDVDRKey
	@discussion	A key for the dictionary for kDRDeviceWriteCapabilitiesKey. The value of this key 
				is a CFBoolean indicating if the device can write to DVD-R media.
*/
extern const CFStringRef kDRDeviceCanWriteDVDRKey					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceCanWriteDVDRWKey
	@discussion	A key for the dictionary for kDRDeviceWriteCapabilitiesKey. The value of this key 
				is a CFBoolean indicating if the device can write to DVD-RW media.
*/
extern const CFStringRef kDRDeviceCanWriteDVDRWKey					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceCanWriteDVDRAMKey
	@discussion	A key for the dictionary for kDRDeviceWriteCapabilitiesKey. The value of this key 
				is a CFBoolean indicating if the device can write to DVD-RAM media.
*/
extern const CFStringRef kDRDeviceCanWriteDVDRAMKey					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceCanWriteCDTextKey
	@discussion	A key for the dictionary for kDRDeviceWriteCapabilitiesKey. The value of this key 
				is a CFBoolean indicating if the device can CDText information to media.
*/
extern const CFStringRef kDRDeviceCanWriteCDTextKey					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceCanTestWriteCDKey
	@discussion	A key for the dictionary for kDRDeviceWriteCapabilitiesKey. The value of this key 
				is a CFBoolean indicating if the device can perform a test write to CD media.
*/
extern const CFStringRef kDRDeviceCanTestWriteCDKey					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceCanTestWriteDVDKey
	@discussion	A key for the dictionary for kDRDeviceWriteCapabilitiesKey. The value of this key 
				is a CFBoolean indicating if the device can perform a test write to DVD media.
*/
extern const CFStringRef kDRDeviceCanTestWriteDVDKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceCanUnderrunProtectCDKey
	@discussion	A key for the dictionary for kDRDeviceWriteCapabilitiesKey. The value of this key 
				is a CFBoolean indicating if the device has burn underrun protection when writing
				to CD media.
*/
extern const CFStringRef kDRDeviceCanUnderrunProtectCDKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceCanUnderrunProtectDVDKey
	@discussion	A key for the dictionary for kDRDeviceWriteCapabilitiesKey. The value of this key 
				is a CFBoolean indicating if the device has burn underrun protection when writing
				to DVD media.
*/
extern const CFStringRef kDRDeviceCanUnderrunProtectDVDKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceVendorNameKey
	@discussion	A key for the dictionary returned by DRDeviceCopyInfo. The value of this key is 
				a CFString containing the vendor name extracted from the device.
*/
extern const CFStringRef kDRDeviceVendorNameKey						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceProductNameKey
	@discussion	A key for the dictionary returned by DRDeviceCopyInfo. The value of this key is 
				a CFString containing the product name extracted from the device.
*/
extern const CFStringRef kDRDeviceProductNameKey					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceFirmwareRevisionKey
	@discussion	A key for the dictionary returned by DRDeviceCopyInfo. The value of this key is 
				a CFString containing the firmware revision extracted from the device.
*/
extern const CFStringRef kDRDeviceFirmwareRevisionKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDevicePhysicalInterconnectKey
	@discussion	A key for the dictionary returned by DRDeviceCopyInfo. The value of this key is 
				a CFString containing the type of the bus the device is on.
*/
extern const CFStringRef kDRDevicePhysicalInterconnectKey			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDevicePhysicalInterconnectFireWire
	@discussion	One possible value of the kDRDevicePhysicalInterconnectKey. Indicates the
				device is physically connected by a FireWire bus.
*/
extern const CFStringRef kDRDevicePhysicalInterconnectFireWire		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDevicePhysicalInterconnectUSB
	@discussion	One possible value of the kDRDevicePhysicalInterconnectKey. Indicates the
				device is physically connected by a USB bus.
*/
extern const CFStringRef kDRDevicePhysicalInterconnectUSB			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDevicePhysicalInterconnectATAPI
	@discussion	One possible value of the kDRDevicePhysicalInterconnectKey. Indicates the
				device is physically connected by an ATAPI bus.
*/
extern const CFStringRef kDRDevicePhysicalInterconnectATAPI			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDevicePhysicalInterconnectSCSI
	@discussion	One possible value of the kDRDevicePhysicalInterconnectKey. Indicates the
				device is physically connected by a SCSI bus.
*/
extern const CFStringRef kDRDevicePhysicalInterconnectSCSI			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDevicePhysicalInterconnectLocationKey
	@discussion	A key for the dictionary returned by DRDeviceCopyInfo. The value of this
				key is a CFString containing the physical interconnect location.
*/
extern const CFStringRef kDRDevicePhysicalInterconnectLocationKey	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDevicePhysicalInterconnectLocationInternal
	@discussion	One possible value of the kDRDevicePhysicalInterconnectLocationKey.
				Indicates the device is physically located on an internal bus.
*/
extern const CFStringRef kDRDevicePhysicalInterconnectLocationInternal	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDevicePhysicalInterconnectLocationExternal
	@discussion	One possible value of the kDRDevicePhysicalInterconnectLocationKey.
				Indicates the device is physically located on an external bus.
*/
extern const CFStringRef kDRDevicePhysicalInterconnectLocationExternal	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDevicePhysicalInterconnectLocationUnknown
	@discussion	One possible value of the kDRDevicePhysicalInterconnectLocationKey.
				Indicates its indeterminate to software whether the device is
				physically located on an internal or external bus.
*/
extern const CFStringRef kDRDevicePhysicalInterconnectLocationUnknown	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceStatusChangedNotification
	@discussion	Notification of device status change, usually in regards to media.
				The info parameter is equivalent to the CFDictionaryRef returned
				from a call to DRDeviceCopyStatus.
*/
extern const CFStringRef kDRDeviceStatusChangedNotification			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRDeviceCopyStatus
	@abstract	Returns information about the status of device.
	@discussion	This function returns information about the status of the device. This
				information includes whether media is present or not, andif it's present 
				a descripton of media (its size, kind, etc). 
	@param		device	The device to obtain information for.
	@result		A CFDictionary of information identifying the status of the device and 
				any media.
*/
extern
CFDictionaryRef DRDeviceCopyStatus(DRDeviceRef device)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*---------------
 *	Keys for the dictionary returned by DRDeviceCopyStatus 
 */
/*!
	@const kDRDeviceIsBusyKey
	@discussion	A key for the dictionary returned by DRDeviceCopyStatus. The value of this key is 
				a CFBoolean indicating if the device is busy doing something.
*/
extern const CFStringRef kDRDeviceIsBusyKey							AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceIsTrayOpenKey
	@discussion	A key for the dictionary returned by DRDeviceCopyStatus. The value of this key is 
				a CFBoolean indicating if the device's tray is open.
*/
extern const CFStringRef kDRDeviceIsTrayOpenKey						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceMaximumWriteSpeedKey
	@discussion	A key for the dictionary returned by DRDeviceCopyStatus. The value of this key is 
				a CFNumber containing the maximum write speed in KB/s.
*/
extern const CFStringRef kDRDeviceMaximumWriteSpeedKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceCurrentWriteSpeedKey
	@discussion	A key for the dictionary returned by DRDeviceCopyStatus. The value of this key is 
				a CFNumber containing the current write speed in KB/s.
*/
extern const CFStringRef kDRDeviceCurrentWriteSpeedKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceMediaStateKey
	@discussion	A key for the dictionary returned by DRDeviceCopyStatus. The value of this key is 
				a CFString containing information about the state of the media.
*/
extern const CFStringRef kDRDeviceMediaStateKey						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDeviceMediaStateMediaPresent
	@discussion	One possible value of the kDRDeviceMediaStateKey. Indicates some kind of media is 
				present in the drive.
*/
extern const CFStringRef kDRDeviceMediaStateMediaPresent			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDeviceMediaStateInTransition
	@discussion	One possible value of the kDRDeviceMediaStateKey. Indicates the media is in
				transition - typically spinning up after being inserted or spinning down in 
				preparation for ejecting.
*/
extern const CFStringRef kDRDeviceMediaStateInTransition			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDeviceMediaStateNone
	@discussion	One possible value of the kDRDeviceMediaStateKey. Indicates there is no media
				present in the drive.
*/
extern const CFStringRef kDRDeviceMediaStateNone					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
	
/*!
	@constant kDRDeviceMediaInfoKey
	@discussion A key for the dictionary returned by DRDeviceCopyStatus. The value of this key is 
				a CFDictionary containing information about the media in the drive.
*/
extern const CFStringRef kDRDeviceMediaInfoKey						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceMediaClassKey
	@discussion	A key for the dictionary for kDRDeviceMediaInfoKey. The value of this key 
				is a CFString containing the class of media present in the drive.
*/
extern const CFStringRef kDRDeviceMediaClassKey						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDeviceMediaClassCD
	@discussion	One possible value of the kDRDeviceMediaClassKey. Indicates the media
				is some type of CD based media.
*/
extern const CFStringRef kDRDeviceMediaClassCD						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDeviceMediaClassDVD
	@discussion	One possible value of the kDRDeviceMediaClassKey. Indicates the media
				is some type of DVD based media.
*/
extern const CFStringRef kDRDeviceMediaClassDVD						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDeviceMediaClassUnknown
	@discussion	One possible value of the kDRDeviceMediaClassKey.  Indicates the media
				class is unknown.
*/
extern const CFStringRef kDRDeviceMediaClassUnknown					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceMediaTypeKey
	@discussion	A key for the dictionary for kDRDeviceMediaInfoKey. The value of this key 
				is a CFString containing the type of media present in the drive.
*/
extern const CFStringRef kDRDeviceMediaTypeKey						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDeviceMediaTypeCDROM
	@discussion	One possible value of the kDRDeviceMediaTypeKey. Indicates the media
				is a CD-ROM.
*/
extern const CFStringRef kDRDeviceMediaTypeCDROM					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDeviceMediaTypeCDR
	@discussion	One possible value of the kDRDeviceMediaTypeKey. Indicates the media
				is a CD-R.
*/
extern const CFStringRef kDRDeviceMediaTypeCDR						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDeviceMediaTypeCDRW
	@discussion	One possible value of the kDRDeviceMediaTypeKey. Indicates the media
				is a CD-RW.
*/
extern const CFStringRef kDRDeviceMediaTypeCDRW						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDeviceMediaTypeDVDROM
	@discussion	One possible value of the kDRDeviceMediaTypeKey. Indicates the media
				is a DVD-ROM.
*/
extern const CFStringRef kDRDeviceMediaTypeDVDROM					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDeviceMediaTypeDVDRAM
	@discussion	One possible value of the kDRDeviceMediaTypeKey. Indicates the media
				is a DVD-RAM.
*/
extern const CFStringRef kDRDeviceMediaTypeDVDRAM					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDeviceMediaTypeDVDR
	@discussion	One possible value of the kDRDeviceMediaTypeKey. Indicates the media
				is a DVD-R.
*/
extern const CFStringRef kDRDeviceMediaTypeDVDR						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDeviceMediaTypeDVDRW
	@discussion	One possible value of the kDRDeviceMediaTypeKey. Indicates the media
				is a DVD-RW.
*/
extern const CFStringRef kDRDeviceMediaTypeDVDRW					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDeviceMediaTypeDVDPlusRW
	@discussion	One possible value of the kDRDeviceMediaTypeKey. Indicates the media
				is a DVD+RW.
*/
extern const CFStringRef kDRDeviceMediaTypeDVDPlusRW				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDeviceMediaTypeUnknown
	@discussion	One possible value of the kDRDeviceMediaTypeKey. Indicates the media
				type is unknown.
*/
extern const CFStringRef kDRDeviceMediaTypeUnknown					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceMediaBSDNameKey
	@discussion	A key for the dictionary for kDRDeviceMediaInfoKey. The value of this key 
				is a CFString containing the BSD name assigned to the device.
*/
extern const CFStringRef kDRDeviceMediaBSDNameKey					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceMediaIsBlankKey
	@discussion	A key for the dictionary for kDRDeviceMediaInfoKey. The value of this key 
				is a CFBoolean indicating the media has no data on it.
*/
extern const CFStringRef kDRDeviceMediaIsBlankKey					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceMediaIsAppendableKey
	@discussion	A key for the dictionary for kDRDeviceMediaInfoKey. The value of this key 
				is a CFBoolean indicating that the media is appendable and new sessions can 
				be written.
*/
extern const CFStringRef kDRDeviceMediaIsAppendableKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceMediaIsErasableKey
	@discussion	A key for the dictionary for kDRDeviceMediaInfoKey. The value of this key 
				is a CFBoolean indicating that the media can be erased.
*/
extern const CFStringRef kDRDeviceMediaIsErasableKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceMediaIsReservedKey
	@discussion	A key for the dictionary for kDRDeviceMediaInfoKey. The value of this key 
				is a CFBoolean indicating that the media is reserved for exclusive use by
				the current process.
*/
extern const CFStringRef kDRDeviceMediaIsReservedKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceMediaBlocksFreeKey
	@discussion	A key for the dictionary for kDRDeviceMediaInfoKey. The value of this key 
				is a CFNumber containing the number of free blocks on the media.
*/
extern const CFStringRef kDRDeviceMediaBlocksFreeKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
	
/*!
	@const kDRDeviceMediaBlocksUsedKey
	@discussion	A key for the dictionary for kDRDeviceMediaInfoKey. The value of this key 
				is a CFNumber containing the number of blocks used by data on the media.
*/
extern const CFStringRef kDRDeviceMediaBlocksUsedKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceMediaTrackCountKey
	@discussion	A key for the dictionary for kDRDeviceMediaInfoKey. The value of this key 
				is a CFNumber containing the number of tracks on the media in all sessions.
*/
extern const CFStringRef kDRDeviceMediaTrackCountKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
	
/*!
	@const kDRDeviceMediaSessionCountKey
	@discussion	A key for the dictionary for kDRDeviceMediaInfoKey. The value of this key 
				is a CFNumber containing the number of sessions on the media.
*/
extern const CFStringRef kDRDeviceMediaSessionCountKey				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRDeviceBurnSpeedsKey
	@discussion	A key for the dictionary returned by DRDeviceCopyStatus. The value of this key 
				is a CFArray containing the possible burn speeds available to use. This key may not
				be available if there is no media in the drive.
*/
extern const CFStringRef kDRDeviceBurnSpeedsKey						AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDeviceBurnSpeedCD1x
	@discussion	Predefined value for the minimum CD burn speed of 176.4 KB/s.
*/
extern const float	kDRDeviceBurnSpeedCD1x							AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDeviceBurnSpeedDVD1x
	@discussion	Predefined value for the minimum DVD burn speed of 1385.0 KB/s.
*/
extern const float	kDRDeviceBurnSpeedDVD1x							AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const	kDRDeviceBurnSpeedMax
	@discussion	Predefined value for the maximum speed a device can burn at.
*/
extern const float	kDRDeviceBurnSpeedMax							AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@defined DRDeviceKPSForCDXFactor
	@discussion	Macro for converting from the x-factor (1x, 8x, 20x, etc) to the real KB/s value 
				for a CD burn.
*/
#define DRDeviceKPSForCDXFactor(xfactor)	((float)(xfactor) * kDRDeviceBurnSpeedCD1x)

/*!
	@defined DRDeviceKPSForDVDXFactor
	@discussion	Macro for converting from the x-factor (1x, 8x, 20x, etc) to the real KB/s value 
				for a DVD burn.
*/
#define DRDeviceKPSForDVDXFactor(xfactor)	((float)(xfactor) * kDRDeviceBurnSpeedDVD1x)

/*!
	@defined DRDeviceCDXFactorForKPS
	@discussion	Macro for converting from the KB/s to the equivalent x-factor (1x, 8x, 20x, etc)
				for a CD burn.
*/
#define DRDeviceCDXFactorForKPS(kps)		(UInt32)floor((kps)/kDRDeviceBurnSpeedCD1x + 0.5)

/*!
	@defined DRDeviceDVDXFactorForKPS
	@discussion	Macro for converting from the KB/s to the equivalent x-factor (1x, 8x, 20x, etc)
				for a DVD burn.
*/
#define DRDeviceDVDXFactorForKPS(kps)		(UInt32)floor((kps)/kDRDeviceBurnSpeedDVD1x + 0.5)

#ifdef __cplusplus
}
#endif

#endif /* _H_DRCoreDevice */
