/*
     File:       DiscRecording/DRCoreNotifications.h
 
     Contains:   DiscRecording notification interfaces.
 
      Version:   Technology: Mac OS X
                 Release:    Mac OS X
 
    Copyright:   (c) 2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef _H_DRCoreNotifications
#define _H_DRCoreNotifications

#if PRAGMA_ONCE
#pragma once
#endif

#include <DiscRecording/DRCoreObject.h>

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*!
	@typedef DRNotificationCenterRef
	This is the type of a reference to DRNotificationCenter instances.
*/
typedef struct __DRNotificationCenter*		DRNotificationCenterRef;

/*!
    @typedef 	DRNotificationCallback
    @abstract	The function called to deliver a notification.
    @param 		center		The center this callback is associated with.
    @param		observer	Observer specified when callback was added.
    @param		name		The notification name.
    @param		object		The object this notification is associated with, will be NULL
    						for notifications without associated objects.
    @param		info		A dictionary with more associated notification information,
    						will be NULL for notifications without associated information.
*/
typedef void (*DRNotificationCallback)(DRNotificationCenterRef center,void *observer,CFStringRef name,DRTypeRef object,CFDictionaryRef info);

/*!
	@function	DRNotificationCenterGetTypeID
	@abstract	Returns the type identifier of all DRNotificationCenter instances.
*/
extern
CFTypeID DRNotificationCenterGetTypeID(void)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRNotificationCenterCreate
	@abstract	Creates a notification center that can be used to register for
				and receive asyncronous notifications.
	@result		A reference to a new DRNotificationCenter.
*/
extern
DRNotificationCenterRef DRNotificationCenterCreate(void)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRNotificationCenterCreateRunLoopSource
	@abstract	Creates a run loop source upon which notifications will be received.
	@param		center			The notification center to get the run loop source for.
								If this parameter is not a valid DRNotificationCenter,
								the behavior is undefined. 
	@result		A reference to a CFRunLoopSource.
*/
extern
CFRunLoopSourceRef DRNotificationCenterCreateRunLoopSource(DRNotificationCenterRef center)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRNotificationCenterAddObserver
	@abstract	Adds an observer callback for the named notification.
    @param 		center		The center to add an observer callback to.
    @param 		observer	The observer to add, which gets passed to the callback.
    @param 		callback	The callback to use for notification delivery.
    @param 		name		The notification name for adding the observer.
    @param 		object		The object the notification name is associated with.
	@result		A reference to a CFRunLoopSource.
*/
extern
void DRNotificationCenterAddObserver(DRNotificationCenterRef center,const void *observer,DRNotificationCallback callback,CFStringRef name,DRTypeRef object)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRNotificationCenterRemoveObserver
	@abstract	Adds an observer callback for the named notification.
    @param 		center		The center to remove the observer callback from.
    @param 		observer	The observer to remove.
    @param 		name		The notification name for removing the observer.
    @param 		object		The object the notification name is associated with.
	@result		A reference to a CFRunLoopSource.
*/
extern
void DRNotificationCenterRemoveObserver(DRNotificationCenterRef center,const void *observer,CFStringRef name,DRTypeRef object)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#ifdef __cplusplus
}
#endif

#endif /* _H_DRCoreNotifications */
