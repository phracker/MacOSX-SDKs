//  
//  GCTouchedStateInput.h
//  GameController
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol GCPhysicalInputElement;
@protocol GCPhysicalInputSource;

NS_ASSUME_NONNULL_BEGIN

/**
 An object conforming to \c GCTouchedStateInput represents the touched state of
 an element.
 
 Some buttons feature capacitive touch capabilities, where the user can touch
 the button without pressing it.  In such cases, a button can be touched without
 being pressed.
 */
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0))
@protocol GCTouchedStateInput <NSObject>

/**
 Set this block if you want to be notified when the touched state changes.
 */
@property (atomic, copy, nullable) void (^touchedDidChangeHandler)(__kindof id<GCPhysicalInputElement> element, id<GCTouchedStateInput> input, BOOL touched);

/**
 Some buttons feature capacitive touch capabilities, where the user can touch
 the button without pressing it. In such cases, a button will be touched before
 it is pressed.
 
 @see touchedDidChangeHandler
 @see GCPressedStateInput
 */
@property (readonly, getter = isTouched) BOOL touched;

/**
 The timestamp of the last touched state change.
 
 This time interval is not relative to any specific point in time.  You can
 subtract a previous timestamp from the returned timestamp to determine the time
 (in seconds) between changes to the value.
 */
@property (readonly) NSTimeInterval lastTouchedStateTimestamp;

/**
 The interval (in seconds) between the timestamp of the last touched state
 change and the current time.
 
 This should be treated as a lower bound of the event latency.  It may not
 include (wired or wireless) transmission latency, or latency accrued on
 the device before the event was transmitted to the host.
 */
@property (readonly) NSTimeInterval lastTouchedStateLatency;

/**
 An object describing the physical action(s) the user performs to manipulate
 this input.
 */
@property (copy, readonly) NSSet<id<GCPhysicalInputSource>> *sources API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));

@end


NS_ASSUME_NONNULL_END
