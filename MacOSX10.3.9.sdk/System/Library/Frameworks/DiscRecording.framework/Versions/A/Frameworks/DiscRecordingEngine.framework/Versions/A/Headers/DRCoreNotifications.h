/*
     File:       DiscRecordingEngine/DRCoreNotifications.h
 
     Contains:   Disc Recording notification interfaces.
 
      Version:   Technology: Mac OS X
                 Release:    Mac OS X
 
    Copyright:   (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!	@header 	
	@abstract		Disc Recording notification interfaces.

	@discussion		
*/

#ifndef _H_DRCoreNotifications
#define _H_DRCoreNotifications

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef _H_DRCoreObject
#include <DiscRecordingEngine/DRCoreObject.h>
#endif

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*!
	@typedef DRNotificationCenterRef
	@abstract	The type of a reference to a DRNotificationCenter object.
*/
typedef struct __DRNotificationCenter*		DRNotificationCenterRef;

/*!
    @typedef 	DRNotificationCallback
    @abstract	Delivers a notification.
    @param 		center		The notification center that this callback is associated with.
    @param		observer	The observer specified when this callback was added.
    @param		name		The notification name.
    @param		object		The object that this notification is associated with, or
    						<tt>NULL</tt> when there is no associated object.
    @param		info		A dictionary object containing additional
    						notification information, or <tt>NULL</tt> when
    						there is no associated object.
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
	@result		Returns reference to a new DRNotificationCenter object.
*/
extern
DRNotificationCenterRef DRNotificationCenterCreate(void)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRNotificationCenterCreateRunLoopSource
	@abstract	Creates a run-loop source object for a notification center.
	@param		center	The notification center that the new run-loop source 
						object is for.
								
						If this parameter is not a valid DRNotificationCenter
						object, the behavior is undefined. 
	@result				Returns a reference to a CFRunLoopSource object.
*/
extern
CFRunLoopSourceRef DRNotificationCenterCreateRunLoopSource(DRNotificationCenterRef center)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRNotificationCenterAddObserver
	@abstract	Adds an observer callback for a notification center.
    @param 		center		The notification center that the new observer callback 
    						is for.
    @param 		observer	The observer callback to add, which gets passed to the callback.
    @param 		callback	The observer callback to use for notification delivery.
    @param 		name		The notification name for adding the observer.
    @param 		object		The object the notification name is associated with.
*/
extern
void DRNotificationCenterAddObserver(DRNotificationCenterRef center,const void *observer,DRNotificationCallback callback,CFStringRef name,DRTypeRef object)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRNotificationCenterRemoveObserver
	@abstract	Removes an observer callback from a notification center.
    @param 		center		The notification center that the observer callback will be removed from.
    @param 		observer	The observer callback to remove.
    @param 		name		The notification name for removing the observer callback.
    @param 		object		The object the notification name is associated with.
*/
extern
void DRNotificationCenterRemoveObserver(DRNotificationCenterRef center,const void *observer,CFStringRef name,DRTypeRef object)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#ifdef __cplusplus
}
#endif

#endif /* _H_DRCoreNotifications */
