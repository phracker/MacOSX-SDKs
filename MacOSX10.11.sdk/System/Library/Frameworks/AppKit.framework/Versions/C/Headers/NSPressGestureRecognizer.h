/*
    NSPressGestureRecognizer.h
    Application Kit
    Copyright (c) 2013-2015, Apple Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/NSGestureRecognizer.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_10, NA)
@interface NSPressGestureRecognizer : NSGestureRecognizer <NSCoding> {
@private
    NSPoint _location;
    NSUInteger _buttonMask;
    NSTimeInterval _minimumPressDuration;
    CGFloat _allowableMovement;
    NSInteger _buttonCount;
    NSInteger _lcflags;
#ifndef __OBJC2__
    NSInteger _reserved1;
#endif
}

/* bitfield of the button(s) required to recognize this click where bit 0 is the primary button, 1 is the secondary button, etc...
   NSPressGestureRecognizer dynamically returns YES to delay primary, secondary and other mouse events depending on this value.
*/
@property NSUInteger buttonMask; // Defaults to 0x1

/* Time in seconds the mouse button must be held down for the gesture to be recognized */
@property NSTimeInterval minimumPressDuration; // Defaults to the user double-click interval

/* Maximum movement in screen points allowed before the gesture fails. Once recognized (after minimumPressDuration) there is no limit on cursor movement for the remainder of the gesture tracking
*/
@property CGFloat allowableMovement; // in screen points. Defaults to double-click distance

@end

NS_ASSUME_NONNULL_END
