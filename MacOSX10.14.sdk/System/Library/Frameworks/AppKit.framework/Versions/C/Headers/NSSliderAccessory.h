/*
    NSSliderAccessory.h
    Application Kit
    Copyright (c) 2016-2018, Apple Inc.
    All rights reserved.
 */

#import <AppKit/NSAccessibility.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class NSSlider, NSSliderAccessoryBehavior, NSImage;

NS_CLASS_AVAILABLE_MAC(10_12)
@interface NSSliderAccessory : NSObject <NSCoding, NSAccessibility, NSAccessibilityElement> {
@private
    id _content APPKIT_IVAR;
    id _container APPKIT_IVAR;
    NSSliderAccessoryBehavior *_behavior APPKIT_IVAR;
    signed char _enabled: 1 APPKIT_IVAR;

#if !__OBJC2__
    unsigned int _sliderAccessoryReservedFlags: 31 __unused APPKIT_IVAR;
    void *_sliderAccessoryReserved[3] __unused APPKIT_IVAR;
#endif /* !__OBJC2__ */
}

/// Creates an image-based accessory
+ (NSSliderAccessory *)accessoryWithImage:(NSImage *)image;

/// The effect on interaction with the accessory. Defaults to `automaticBehavior`
@property (copy) NSSliderAccessoryBehavior *behavior;

/// Whether or not the accessory is interactive and draws with an enabled appearance. Defaults to YES.
@property (getter=isEnabled) BOOL enabled;

@end


NS_CLASS_AVAILABLE_MAC(10_12)
@interface NSSliderAccessoryBehavior : NSObject <NSCoding, NSCopying>

/// The behavior is automatically picked to be the system standard for the slider's current context, e.g. NSTouchBarItems have `.valueStep` behavior.
@property (class, readonly, copy) NSSliderAccessoryBehavior *automaticBehavior;

/// The value of the slider moves towards the associated value for the accessory with by a delta of the slider's `altIncrementValue`.
@property (class, readonly, copy) NSSliderAccessoryBehavior *valueStepBehavior;

/// The value of the slider is reset to the associated value for the accessory.
@property (class, readonly, copy) NSSliderAccessoryBehavior *valueResetBehavior;

/// The action is sent to the target on interaction. The optional first parameter is an NSSliderAccessory.
+ (NSSliderAccessoryBehavior *)behaviorWithTarget:(nullable id)target action:(SEL)action;

/// The handler block is invoked on interaction. This variant is not codable and will assert in `-encodeWithCoder:`.
+ (NSSliderAccessoryBehavior *)behaviorWithHandler:(void(^)(NSSliderAccessory *))handler;


/// Override point for custom subclasses to handle interaction.
- (void)handleAction:(NSSliderAccessory *)sender;

@end

NS_ASSUME_NONNULL_END
