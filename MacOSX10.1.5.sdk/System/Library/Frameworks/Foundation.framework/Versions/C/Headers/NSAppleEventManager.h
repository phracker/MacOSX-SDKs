/*	NSAppleEventManager.h
	Copyright 1997-2001, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <ApplicationServices/ApplicationServices.h>

@class NSAppleEventDescriptor;

extern const double NSAppleEventTimeOutDefault;
extern const double NSAppleEventTimeOutNone;

extern NSString *NSAppleEventManagerWillProcessFirstEventNotification;

@interface NSAppleEventManager : NSObject {

    @private
    void *privateData;

}

// Get the pointer to the program's single NSAppleEventManager.
+ (NSAppleEventManager *)sharedAppleEventManager;

// Set or remove a handler for a specific kind of Apple Event.  The handler method should have the same signature as:
// - (void)handleAppleEvent:(NSAppleEventDescriptor *)event withReplyEvent:(NSAppleEventDescriptor *)replyEvent;
// When it is invoked, the value of the first parameter will be the event to be handled.  The value of the second parameter will be the reply event to fill in.  A reply event object will always be passed in (replyEvent will never be nil), but it should not be touched if the event sender has not requested a reply, which is indicated by [replyEvent descriptorType]==typeNull.
- (void)setEventHandler:(id)handler andSelector:(SEL)handleEventSelector forEventClass:(AEEventClass)eventClass andEventID:(AEEventID)eventID;
- (void)removeEventHandlerForEventClass:(AEEventClass)eventClass andEventID:(AEEventID)eventID;

// Given an event, reply event, and refCon of the sort passed into Apple Event handler functions that can be registered with AEInstallEventHandler(), dispatch the event to a handler that has been registered with -setEventHandler:andSelector:forEventClass:andEventID:.
// This method is primarily meant for Cocoa's internal use.  It does not send events to other applications!
- (OSErr)dispatchRawAppleEvent:(const AppleEvent *)theAppleEvent withRawReply:(AppleEvent *)theReply handlerRefCon:(UInt32)handlerRefCon;

@end
