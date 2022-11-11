//
//  GCControllerTouchpad.h
//  GameControllerFramework_iOS
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <GameController/GCControllerElement.h>

@class GCControllerDirectionPad;
@class GCControllerButtonInput;

NS_ASSUME_NONNULL_BEGIN

/**
 Represents the current state of a touch event on a touchpad.
 */
typedef NS_ENUM(NSInteger, GCTouchState) {
    GCTouchStateUp,
    GCTouchStateDown,
    GCTouchStateMoving
} NS_SWIFT_NAME(GCControllerTouchpad.TouchState);

/**
 A touchpad is a touch-based two axis input with a notion of "touch state". It keeps track of
 whether the touchpad is actively being touched, and generates events based on a
 change in touch state.
 */
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface GCControllerTouchpad : GCControllerElement

/**
 Button is the button built into the touch surface.
 
 */
@property (nonatomic, readonly) GCControllerButtonInput *button;

/**
 Set this block if you want to be notified when an axis or the touch state changes.
 
 @param touchpad the touchpad collection whose axes or touch state has been modified.
 @param xValue the value x axis was set to at the time the handler fired.
 @param yValue the value y axis was set to at the time the handler fired.
 @param buttonValue the value of the touch surface button at the time the handler fired.
 @param buttonPressed the pressed state of the touch surface button at the time the handler fired.
 */
typedef void (^GCControllerTouchpadHandler)(GCControllerTouchpad *touchpad, float xValue, float yValue, float buttonValue, BOOL buttonPressed);

/**
 Called when a touch event begins on the touchpad.
 */
@property (nonatomic, copy, nullable) GCControllerTouchpadHandler touchDown;

/**
 Called when a touch event continues on the touchpad, but not when it begins or ends.
 */
@property (nonatomic, copy, nullable) GCControllerTouchpadHandler touchMoved;

/**
 Called when a touch event ends on the touchpad.
 */
@property (nonatomic, copy, nullable) GCControllerTouchpadHandler touchUp;

/**
 The touch surface is a 2-axis control that represents the position of a touch event on the touchpad.
 
 The axes will indicate the most recent touch position - a non-zero value does not indicate that the
 surface is being touched, and a value of (0, 0) does not indicate the surface is not being touched.
 
 @see touchState - Should be polled in conjunction with touchSurface to determine if values are valid
 */
@property (nonatomic, readonly) GCControllerDirectionPad *touchSurface;

/**
 Indicates the current state of the touch event on the touchpad.
 */
@property (nonatomic, readonly) GCTouchState touchState;

/**
 The touchpad can use the raw position values of its surface as D-pad values, or it can create a virtual dpad centered around the first contact point with the surface.
 
 If NO; a smaller sliding window is created around the initial touch point and subsequent movement is relative to that center. Movement outside the window will slide the window with it to re-center it. This is great for surfaces where there is no clear sense of a middle and drift over time is an issue.
 
 If YES; the absolute values are used and any drift will have to managed manually either through user traning or by a developer using the dpad.
 
 The default value for this property is YES, meaning the touch surface's raw positional values are reported.
 */
@property (nonatomic) BOOL reportsAbsoluteTouchSurfaceValues;

/**
 Sets the normalized value for the touchpad's axes, as well as its current touch and button state.
 
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see touchSurface
 @see touchState
 */
- (void)setValueForXAxis:(float)xAxis yAxis:(float)yAxis touchDown:(BOOL)touchDown buttonValue:(float)buttonValue;

@end

NS_ASSUME_NONNULL_END
