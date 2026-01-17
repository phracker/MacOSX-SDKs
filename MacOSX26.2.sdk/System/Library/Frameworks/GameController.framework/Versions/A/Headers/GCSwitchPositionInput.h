//
//  GCSwitchPositionInput.h
//  GameController
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol GCPhysicalInputElement;
@protocol GCPhysicalInputSource;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0))
@protocol GCSwitchPositionInput <NSObject>

/**
 Set this block if you want to be notified when the value on the switch changes.
 
 @param input the element that has been modified.
 @see value
 */
@property (atomic, copy, nullable) void (^positionDidChangeHandler)(__kindof id<GCPhysicalInputElement> element, id<GCSwitchPositionInput> input, NSInteger position);

/**
 The switch's position.
 
 @see valueDidChangeHandler
 */
@property (readonly) NSInteger position;

/**
 The (inclusive) bounds of possible position values for the switch.
 */
@property (readonly) NSRange positionRange;

/**
 \c YES if the switch input can only transition to positions that are adjacent
 to the current position.
 */
@property (readonly, getter = isSequential) BOOL sequential;

/**
 Check if the position input value can "roll over" when reaching either of its
 bounds.
 
 This will always be \c YES for non-sequential switch inputs.
 */
@property (readonly) BOOL canWrap;

/**
 The timestamp of the last value.
 
 This time interval is not relative to any specific point in time.  You can
 subtract a previous timestamp from the returned timestamp to determine the time
 (in seconds) between changes to the value.
 */
@property (readonly) NSTimeInterval lastPositionTimestamp;

/**
 The interval (in seconds) between the timestamp of the last event and the
 current time.
 
 This should be treated as a lower bound of the event latency.  It may not
 include (wired or wireless) transmission latency, or latency accrued on
 the device before the event was transmitted to the host.
 */
@property (readonly) NSTimeInterval lastPositionLatency;

/**
 An object describing the physical action(s) the user performs to manipulate
 this input.
 */
@property (copy, readonly) NSSet<id<GCPhysicalInputSource>> *sources API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));

@end


NS_ASSUME_NONNULL_END
