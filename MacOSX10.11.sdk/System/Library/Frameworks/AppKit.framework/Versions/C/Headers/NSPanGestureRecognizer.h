/*
    NSPanGestureRecognizer.h
    Application Kit
    Copyright (c) 2013-2015, Apple Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/NSGestureRecognizer.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_10, NA)
@interface NSPanGestureRecognizer : NSGestureRecognizer <NSCoding> {
@private
    NSPoint _location;
    NSPoint _translation;
    NSUInteger _buttonMask;
    NSInteger _buttonCount;
    id _velocityFilter;
    CGFloat private0;
    CGFloat private1;
    struct __pgrFlags {
        unsigned int    reserved:32;
    } __pgrFlags;
    id _reserved0;
#ifndef __OBJC2__
    NSInteger _reserved1;
#endif
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

NS_ASSUME_NONNULL_END
