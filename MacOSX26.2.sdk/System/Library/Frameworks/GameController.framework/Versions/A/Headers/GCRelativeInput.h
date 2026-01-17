//  
//  GCRelativeInput.h
//  GameController
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol GCPhysicalInputElement;
@protocol GCPhysicalInputSource;

NS_ASSUME_NONNULL_BEGIN

/**
 An object conforming to \c GCRelativeInput represents an input that reports
 its change in position along an axis (delta) since the previous event.
 Relative inputs have no fixed origin from which a coordinate syatem can be
 defined.
 */
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0))
@protocol GCRelativeInput <NSObject>

/**
 Set this block to be notified when the delta of the input changes.
 
 @param delta
 The amount that the input has changed since the last time
 \c deltaDidChangeHandler fired.
 */
@property (atomic, copy, nullable) void (^deltaDidChangeHandler)(__kindof id<GCPhysicalInputElement> element, id<GCRelativeInput> input, float delta);

/**
 The last reported delta for the input.
 */
@property (readonly) float delta;

/**
 Check if the input can support more than just digital values.
 
 Defaults to \c YES for most relative inputs.
 */
@property (readonly, getter = isAnalog) BOOL analog;

/**
 The timestamp of the last change.
 
 This time interval is not relative to any specific point in time.  You can
 subtract a previous timestamp from the current timestamp to determine the time
 (in seconds) between changes to the value.
 */
@property (readonly) NSTimeInterval lastDeltaTimestamp;

/**
 The interval (in seconds) between the timestamp of the last change and the
 current time.
 
 This should be treated as a lower bound of the event latency.  It may not
 include (wired or wireless) transmission latency, or latency accrued on
 the device before the event was transmitted to the host.
 */
@property (readonly) NSTimeInterval lastDeltaLatency;

/**
 An object describing the physical action(s) the user performs to manipulate
 this input.
 */
@property (copy, readonly) NSSet<id<GCPhysicalInputSource>> *sources API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));

@end


NS_ASSUME_NONNULL_END

