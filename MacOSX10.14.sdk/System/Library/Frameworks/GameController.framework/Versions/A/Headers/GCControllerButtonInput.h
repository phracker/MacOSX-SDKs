//
//  GCControllerButtonInput.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <GameController/GameController.h>

NS_ASSUME_NONNULL_BEGIN

GAMECONTROLLER_EXPORT
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
@property (nonatomic, copy, nullable) GCControllerButtonValueChangedHandler pressedChangedHandler NS_AVAILABLE(10_10, 8_0);

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
 @see pressedChangedHandler
 @see value
 */
@property (nonatomic, readonly, getter = isPressed) BOOL pressed;

@end

NS_ASSUME_NONNULL_END

