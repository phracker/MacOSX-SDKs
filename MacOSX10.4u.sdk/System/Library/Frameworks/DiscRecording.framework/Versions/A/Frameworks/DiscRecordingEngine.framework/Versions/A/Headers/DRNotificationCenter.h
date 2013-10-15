/*
     File:       DiscRecordingEngine/DRNotificationCenter.h
 
     Contains:   Interface for registering to receive notifications from 
				 DiscRecording. 
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!	@header 	DRNotificationCenter.h
	@abstract	Register to receive notifications from Disc Recording.
	@discussion	A @link DRNotificationCenter DRNotificationCenter @/link object (or simply, notification center) is
				essentially a notification dispatch table. It notifies all observers of
				notifications meeting specific criteria. This information is encapsulated in
				NSNotification objects, also known as notifications. Client objects register
				themselves with the notification center as observers of specific notifications
				posted by DiscRecording. When an event occurs, Disc Recording posts an appropriate
				notification to the notification center. The notification center dispatches a
				message to each registered observer, passing the notification as the sole
				argument.
				
				There are two main differences between a @link DRNotificationCenter DRNotificationCenter @/link and the
				NSNotificationCenter from Foundation. First is that only DiscRecording
				posts notifications received through this mechanism. You use this to 
				obtain device plug/unplug events, burn status, etc. Second, there can be
				multple notification centers active at once. Each run loop of your application
				will have it's own notification center and notifications from that notification
				center will be posted to the runloop it was created on.
*/

#import <Foundation/Foundation.h>

#import <DiscRecordingEngine/DRCoreNotifications.h>

/*!
	@class 		DRNotificationCenter
	@discussion	A DRNotificationCenter object (or simply, notification center) is
				essentially a notification dispatch table. It notifies all observers of
				notifications meeting specific criteria. This information is encapsulated in
				NSNotification objects, also known as notifications. Client objects register
				themselves with the notification center as observers of specific notifications
				posted by DiscRecording. When an event occurs, DiscRecording posts an appropriate
				notification to the notification center. The notification center dispatches a
				message to each registered observer, passing the notification as the sole
				argument.
				
				There are two main differences between a DRNotificationCenter and the
				NSNotificationCenter from Foundation. First is that only Disc Recording
				posts notifications received through this mechanism. You use this to 
				obtain device plug/unplug events, burn status, etc. Second, there can be
				multple notification centers active at once. Each run loop of your application
				will have it's own notification center and notifications from that notification
				center will be posted to the runloop it was created on.
*/
@interface DRNotificationCenter : NSObject 
{ 
@private
	void*	_ref;
}

/*!
	@method			currentRunLoopCenter
	@abstract		Creates an initializes a DRNotificationCenter
	@discussion		The instance returned sends Disc Recording notifications only
					to the current run loop. If you want to receive notifications 
					on another run loop, this method must be called from that runloop.
	@result			A shared DRNotificationCenter object.
*/
+ (DRNotificationCenter*) currentRunLoopCenter;

/*!
	@method			addObserver:selector:name:object:
	@abstract		Adds an observer to the receiver.
	@discussion		Registers anObserver to receive notifications with the name notificationName
					and/or containing anObject. When a notification of name notificationName
					containing the object anObject is posted, anObserver receives an aSelector
					message with this notification as the argument. The method for the selector
					specified in aSelector must have one and only one argument. If notificationName
					is nil, the notification center notifies the observer of all notifications with
					an object matching anObject. If anObject is nil, the notification center
					notifies the observer of all notifications with the name notificationName.
					
					The notification center does not retain anObserver or anObject. Therefore, you
					should always send @link //apple_ref/occ/instm/DRNotificationCenter/removeObserver:name:object: removeObserver:name:object: @/link to the notification center 
					before releasing these objects.
	@param			observer	The observer to send notifications to.
	@param			aSelector	The selector to call
	@param			notificationName	The notification to listen for
	@param			anObject	The object to limit notifications for.
*/
- (void)addObserver:(id)observer selector:(SEL)aSelector name:(NSString *)notificationName object:(id)anObject;

/*!
	@method			removeObserver:name:object:
	@abstract		Removes anObserver from receiving notifications.
	@discussion		Removes anObserver as the observer of notifications with the name
					notificationName and object anObject from the receiver. Be sure to invoke this
					method before deallocating the observer object or any object specified in 
					@link //apple_ref/occ/instm/DRNotificationCenter/addObserver:selector:name:object: addObserver:selector:name:object: @/link.
	@param			observer	The observer to remove
	@param			aName		The notification the remove the observer from.
	@param			anObject	The object the observer was listening for.
*/
- (void)removeObserver:(id)observer name:(NSString *)aName object:(id)anObject;

@end
