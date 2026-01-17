//  
//  GCLinearInput.h
//  GameController
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol GCPhysicalInputElement;
@protocol GCPhysicalInputSource;
@protocol GCPhysicalInputExtents;

NS_ASSUME_NONNULL_BEGIN

/**
 An object conforming to \c GCLinearInput represents an input that produces
 normalized values in the unit interval - between [0, 1].
 */
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0))
@protocol GCLinearInput <NSObject>

/**
 Set this block to be notified when the value of the input changes.
 
 @param element the element that has been modified.
 @param input the input that has been modified.
 @param value the value the axis was set to at the time the valueDidChangeHandler fired.
 */
@property (atomic, copy, nullable) void (^valueDidChangeHandler)(__kindof id<GCPhysicalInputElement> element, id<GCLinearInput> input, float value);

/**
 A normalized value for the axis input, between 0 and 1 (inclusive). The values
 are deadzoned and saturated before they are returned so there is no value
 outside the range.  Deadzoning does not remove values from the range, the full
 0 to 1 magnitude of values are possible from the input.

 You can rely on a value of 0 meaning the value is inside the deadzone.  Any
 value greater than zero is not in the deadzone.
 */
@property (readonly) float value;

/**
 Check if the input can support more than just digital values.
 
 If \c YES, the input can produce any value between [0, 1].  Otherwise, the
 input only produces the values 0 or 1.
 */
@property (readonly, getter = isAnalog) BOOL analog;

/**
 Check if the input value "rolls over" when reaching either the extreme high
 or low value.  For example, some dials can be rotated past the position that
 represents their maximum value, causing the next reported value to roll over.
 
 Defaults to NO for most inputs.
 */
@property (readonly) BOOL canWrap;

/**
 The timestamp of the last value.
 
 This time interval is not relative to any specific point in time.  You can
 subtract a previous timestamp from the current timestamp to determine the time
 (in seconds) between changes to the value.
 */
@property (readonly) NSTimeInterval lastValueTimestamp;

/**
 The interval (in seconds) between the timestamp of the last event and the
 current time.
 
 This should be treated as a lower bound of the event latency.  It may not
 include (wired or wireless) transmission latency, or latency accrued on
 the device before the event was transmitted to the host.
 */
@property (readonly) NSTimeInterval lastValueLatency;

/**
 An object describing the physical extents of the input, if the input represents
 a physical unit of measurement.
 */
@property (readonly, nullable) id<GCPhysicalInputExtents> physicalExtents API_AVAILABLE(macos(26.2), ios(26.2), tvos(26.2), visionos(26.2));


/**
 An object describing the physical action(s) the user performs to manipulate
 this input.
 */
@property (copy, readonly) NSSet<id<GCPhysicalInputSource>> *sources API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));

@end


NS_ASSUME_NONNULL_END
