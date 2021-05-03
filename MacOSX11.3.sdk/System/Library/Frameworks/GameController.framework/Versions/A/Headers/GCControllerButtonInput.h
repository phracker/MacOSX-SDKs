//
//  GCControllerButtonInput.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//


#import <GameController/GCControllerElement.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.9), ios(7.0), tvos(7.0))
@interface GCControllerButtonInput : GCControllerElement

/**
 Set this block if you want to be notified when the value on this button changes.
 
 @param button the element that has been modified.
 @param value the value the button was set to at the time the valueChangedHandler fired.
 @param pressed the pressed state of the button at the time the valueChangedHandler fired.
 @see value
 @see pressed
 */
typedef void (^GCControllerButtonValueChangedHandler)(GCControllerButtonInput *button, float value, BOOL pressed);
@property (nonatomic, copy, nullable) GCControllerButtonValueChangedHandler valueChangedHandler;

/**
 Set this block if you want to be notified when only the pressed state on this button changes. This
 will get called less often than the valueChangedHandler with the additional feature of the pressed state
 being different to the last time it was called.
 */
@property (nonatomic, copy, nullable) GCControllerButtonValueChangedHandler pressedChangedHandler API_AVAILABLE(macos(10.10), ios(8.0), tvos(8.0));

/**
 Set this block if you want to be notified when the touched state on this button changes.
  
 @param button the element that has been modified.
 @param value the value the button was set to at the time the valueChangedHandler fired.
 @param pressed the pressed state of the button at the time the valueChangedHandler fired.
 @param touched the touched state of the button at the time the valueChangedHandler fired.
 @see value
 @see pressed
*/
typedef void (^GCControllerButtonTouchedChangedHandler)(GCControllerButtonInput *button, float value, BOOL pressed, BOOL touched);
@property (nonatomic, copy, nullable) GCControllerButtonTouchedChangedHandler touchedChangedHandler API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 A normalized value for the input. Between 0 and 1 for button inputs. Values are saturated and thus never exceed the range of [0, 1].
 @see valueChangedHandler
 @see pressed
 */
@property (nonatomic, readonly) float value;

/**
 Buttons are mostly used in a digital sense, thus we have a recommended method for checking for pressed state instead of
 interpreting the value.
 
 As a general guideline a button is pressed if the value exceeds 0. However there may be hysterisis applied
 to counter noisy input values, thus incidental values around the threshold value may not trigger a change
 in pressed state.
 
 Others buttons may support two-stage actuation, where the button reports a value between 0 and 1 but is only considered
 pressed when its value is greater than some threshold other than 0.
 @see pressedChangedHandler
 @see value
 */
@property (nonatomic, readonly, getter = isPressed) BOOL pressed;

/**
 Some buttons feature capacitive touch capabilities where the user can touch the button
 without pressing it. In such cases, a button will be touched before it is pressed.
 
 For buttons without capacitive sensing, the touched state is true if the value exceeds 0.
 
 @see touchChangedHandler
 @see pressed
 */
@property (nonatomic, readonly, getter = isTouched) BOOL touched;

/**
 Sets the normalized value for the button input. Will update the pressed state of the button.

 @param value the value to set the input to.
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see value
 */
- (void)setValue:(float)value API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

@end

NS_ASSUME_NONNULL_END

