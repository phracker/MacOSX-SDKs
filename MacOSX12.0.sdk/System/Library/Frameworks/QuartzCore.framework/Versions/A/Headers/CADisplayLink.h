/* CoreAnimation - CADisplayLink.h

   Copyright (c) 2009-2021, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CABase.h>
#import <QuartzCore/CAFrameRateRange.h>
#import <Foundation/NSObject.h>

@class NSString, NSRunLoop;

NS_ASSUME_NONNULL_BEGIN

/** Class representing a timer bound to the display vsync. **/

API_AVAILABLE(ios(3.1), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos)
@interface CADisplayLink : NSObject
{
@private
  void *_impl;
}

/* Create a new display link object for the main display. It will
 * invoke the method called 'sel' on 'target', the method has the
 * signature '(void)selector:(CADisplayLink *)sender'. */

+ (CADisplayLink *)displayLinkWithTarget:(id)target selector:(SEL)sel;

/* Adds the receiver to the given run-loop and mode. Unless paused, it
 * will fire every vsync until removed. Each object may only be added
 * to a single run-loop, but it may be added in multiple modes at once.
 * While added to a run-loop it will implicitly be retained. */

- (void)addToRunLoop:(NSRunLoop *)runloop forMode:(NSRunLoopMode)mode;

/* Removes the receiver from the given mode of the runloop. This will
 * implicitly release it when removed from the last mode it has been
 * registered for. */

- (void)removeFromRunLoop:(NSRunLoop *)runloop forMode:(NSRunLoopMode)mode;

/* Removes the object from all runloop modes (releasing the receiver if
 * it has been implicitly retained) and releases the 'target' object. */

- (void)invalidate;

/* The current time, and duration of the display frame associated with
 * the most recent target invocation. Time is represented using the
 * normal Core Animation conventions, i.e. Mach host time converted to
 * seconds. */

@property(readonly, nonatomic) CFTimeInterval timestamp;
@property(readonly, nonatomic) CFTimeInterval duration;

/* The next timestamp that the client should target their render for. */

@property(readonly, nonatomic) CFTimeInterval targetTimestamp
    API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0));

/* When true the object is prevented from firing. Initial state is
 * false. */

@property(getter=isPaused, nonatomic) BOOL paused;

/* Defines how many display frames must pass between each time the
 * display link fires. Default value is one, which means the display
 * link will fire for every display frame. Setting the interval to two
 * will cause the display link to fire every other display frame, and
 * so on. The behavior when using values less than one is undefined.
 * DEPRECATED - use preferredFramesPerSecond. */

@property(nonatomic) NSInteger frameInterval
  API_DEPRECATED("preferredFramesPerSecond", ios(3.1, 10.0), 
                 watchos(2.0, 3.0), tvos(9.0, 10.0));

/* Defines the desired callback rate in frames-per-second for this display
 * link. If set to zero, the default value, the display link will fire at the
 * native cadence of the display hardware. The display link will make a
 * best-effort attempt at issuing callbacks at the requested rate. */

@property(nonatomic) NSInteger preferredFramesPerSecond
  API_DEPRECATED_WITH_REPLACEMENT ("preferredFrameRateRange",
                                   ios(10.0, API_TO_BE_DEPRECATED),
                                   watchos(3.0, API_TO_BE_DEPRECATED),
                                   tvos(10.0, API_TO_BE_DEPRECATED));

/* Defines the range of desired callback rate in frames-per-second for this
   display link. If the range contains the same minimum and maximum frame rate,
   this property is identical as preferredFramesPerSecond. Otherwise, the actual
   callback rate will be dynamically adjusted to better align with other
   animation sources. */

@property(nonatomic) CAFrameRateRange preferredFrameRateRange
    API_AVAILABLE(ios(15.0), watchos(8.0), tvos(15.0));

@end

NS_ASSUME_NONNULL_END
