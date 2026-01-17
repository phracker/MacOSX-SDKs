/*
    NSTouch.h
    Application Kit
    Copyright (c) 2009-2017, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObjCRuntime.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSDate.h>

NS_ASSUME_NONNULL_BEGIN

@class NSView;

typedef NS_OPTIONS(NSUInteger, NSTouchPhase) {
    NSTouchPhaseBegan           = 1U << 0,
    NSTouchPhaseMoved           = 1U << 1,
    NSTouchPhaseStationary      = 1U << 2,
    NSTouchPhaseEnded           = 1U << 3,
    NSTouchPhaseCancelled       = 1U << 4,

    NSTouchPhaseTouching        = NSTouchPhaseBegan | NSTouchPhaseMoved | NSTouchPhaseStationary,
    NSTouchPhaseAny             = NSUIntegerMax
} NS_ENUM_AVAILABLE_MAC(10_7);

typedef NS_ENUM(NSInteger, NSTouchType) {
    NSTouchTypeDirect,      // A direct touch from a finger (on a screen)
    NSTouchTypeIndirect,      // An indirect touch (not a screen)
} NS_ENUM_AVAILABLE_MAC(10_12_2);

typedef NS_OPTIONS(NSUInteger, NSTouchTypeMask) {
    NSTouchTypeMaskDirect      = (1 <<  NSTouchTypeDirect),      // A direct touch from a finger (on a screen)
    NSTouchTypeMaskIndirect    = (1 <<  NSTouchTypeIndirect),      // An indirect touch (not a screen)
} NS_ENUM_AVAILABLE_MAC(10_12_2);

NS_INLINE NSTouchTypeMask NSTouchTypeMaskFromType(NSTouchType type) { return (1 << type); }

/* Unlike the iPhone, NSTouch objects do not persist for the life of the touch.
*/
NS_CLASS_AVAILABLE(10_6, NA)
@interface NSTouch : NSObject <NSCopying> {
@private
    NSInteger _index;
    id _identity;
    NSTouchPhase _phase;
    NSPoint _pos1;
    NSInteger _privateFlags;
    NSView *_view;
    id _reserved1;
    NSPoint _pos0;
    NSInteger _reserved4;
    id _device;
    NSSize  _deviceSize;
    NSInteger _contextId;
    NSTimeInterval _timestamp;
#if ! __LP64__
    id _reserved8;
#endif
}

/* Properties of this touch */
/* Use the identity property to track changes to a particular touch during the touch's life. While touch identities may be re-used, they are unique during the life of the touch, even when multiple devices are present. Note: identity objects implement the NSCopying protocol so that they may be used as keys in an NSDictionary. Use isEqual: to compare two touch identities.
*/
@property (readonly, strong) id<NSObject, NSCopying> identity;
@property (readonly) NSTouchPhase phase;
@property (readonly) NSPoint normalizedPosition; // Scaled absolute position is in [0,1], where (0, 0) is the lower left of the surface.
@property (readonly, getter=isResting) BOOL resting;

/* Properties of the underlying touch device */ 
@property (nullable, readonly, strong) id device; // The digitizer that generated the touch. Useful to distinguish touches emanating from multiple-device scenario

/* The range of the touch device in points (72ppi). Note: 0,0 is the lower left of the surface.
*/
@property (readonly) NSSize deviceSize;

@end

@interface NSTouch (NSTouchBar)
/* A touch can only be one type at a time */
@property(readonly) NSTouchType type NS_AVAILABLE_MAC(10_12_2);

/* These two methods are only valid for Direct touches. A nil view means the touch location in the root container of touch. */
- (NSPoint)locationInView:(nullable NSView *)view NS_AVAILABLE_MAC(10_12_2);
- (NSPoint)previousLocationInView:(nullable NSView *)view NS_AVAILABLE_MAC(10_12_2);
@end

NS_ASSUME_NONNULL_END

