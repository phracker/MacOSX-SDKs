/*
    NSPanGestureRecognizer.h
    Application Kit
    Copyright (c) 2013-2018, Apple Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/NSGestureRecognizer.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_10, NA)
@interface NSPanGestureRecognizer : NSGestureRecognizer <NSCoding> {
@private
    NSPoint _location APPKIT_IVAR;
    NSPoint _translation APPKIT_IVAR;
    NSUInteger _buttonMask APPKIT_IVAR;
    NSInteger _buttonCount APPKIT_IVAR;
    id _velocityFilter APPKIT_IVAR;
    CGFloat private0 __unused APPKIT_IVAR;
    CGFloat private1 __unused APPKIT_IVAR;
    struct __pgrFlags {
        unsigned int    reserved0:1;
        unsigned int    reserved:31;
    } __pgrFlags __unused APPKIT_IVAR;
    id _reserved0 APPKIT_IVAR;
    id _reserved1 __unused APPKIT_IVAR;
}

/* bitfield of the button(s) required to recognize this click where bit 0 is the primary button, 1 is the secondary button, etc...
   NSClickGestureRecognizer.h dynamically returns YES to delay primary, secondary and other mouse events depending on this value.
*/
@property NSUInteger buttonMask; // Defaults to 0x1

/* translation in the coordinate system of the specified view */
- (NSPoint)translationInView:(nullable NSView*)view;
- (void)setTranslation:(NSPoint)translation inView:(nullable NSView*)view;

/* velocity of the pan in points/second in the coordinate system of the specified view */
- (NSPoint)velocityInView:(nullable NSView*)view;

@end

@interface NSPanGestureRecognizer (NSTouchBar)
@property NSInteger numberOfTouchesRequired NS_AVAILABLE_MAC(10_12_2);
@end

NS_ASSUME_NONNULL_END
