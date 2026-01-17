/*
    NSClickGestureRecognizer.h
    Application Kit
    Copyright (c) 2013-2017, Apple Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/NSGestureRecognizer.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_10, NA)
@interface NSClickGestureRecognizer : NSGestureRecognizer <NSCoding> {
@private
    NSInteger _flags;
    NSPoint _location;
    NSUInteger _buttonMask;
    NSInteger _numberOfClicksRequired;
    NSInteger _currentButtonCount;
    NSInteger _activeButtonCount;
    NSInteger _currentClickCount;
    id _reserved0;
    id _reserved1;
}

/* bitfield of the button(s) required to recognize this click where bit 0 is the primary button, 1 is the secondary button, etc...
   NSClickGestureRecognizer dynamically returns YES to delay primary, secondary and other mouse events depending on this value.
*/
@property NSUInteger buttonMask; // Defaults to 0x1

/* the number of clicks required to match */
@property NSInteger numberOfClicksRequired; // Defaults to 1

@property NSInteger numberOfTouchesRequired NS_AVAILABLE_MAC(10_12_2);
@end

NS_ASSUME_NONNULL_END
