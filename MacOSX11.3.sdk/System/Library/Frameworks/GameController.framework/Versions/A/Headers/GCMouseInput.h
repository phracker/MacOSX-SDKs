//
//  GCMouseInput.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <GameController/GCExtern.h>
#import <GameController/GCPhysicalInputProfile.h>

@class GCDeviceCursor;
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Mouse profile that represent a physical mouse object with two axis cursor, two axis scroll,
 left button, optional right and middle buttons and optional set of auxiliary buttons.
 
 It only provides information about raw mouse movement deltas. For the valid cursor position
 at given point in time, use UIHoverGestureRecognizer and NSEvent.mouseLocation.
 */
API_AVAILABLE(macos(11.0), ios(14.0))
@interface GCMouseInput : GCPhysicalInputProfile

/**
 Set this block if you want to be notified when the mouse was moved
 @param mouse this mouse that is being used for input
 @param deltaX the value of raw mouse delta along x axis. Not affected by mouse sensitivity settings
 @param deltaY the value of raw mouse delta along y axis. Not affected by mouse sensitivity settings
*/
typedef void (^GCMouseMoved)(GCMouseInput* mouse, float deltaX, float deltaY);
@property (nonatomic, copy, nullable) GCMouseMoved mouseMovedHandler;

/**
 Scroll is a dpad with undefined range.
 */
@property(readonly, nonatomic) GCDeviceCursor* scroll;

/**
 Mouse buttons that can be used only as digital inputs
 */
@property (nonatomic, readonly) GCDeviceButtonInput *leftButton;
@property (nullable, nonatomic, readonly) GCDeviceButtonInput *rightButton;
@property (nullable, nonatomic, readonly) GCDeviceButtonInput *middleButton;
@property (nullable, nonatomic, readonly) NSArray<GCDeviceButtonInput*> *auxiliaryButtons;

@end

NS_ASSUME_NONNULL_END
