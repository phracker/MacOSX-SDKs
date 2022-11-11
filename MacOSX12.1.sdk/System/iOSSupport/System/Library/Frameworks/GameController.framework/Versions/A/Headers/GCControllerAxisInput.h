//
//  GCControllerAxisInput.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//


#import <GameController/GameController.h>
#import <GameController/GCExtern.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.9), ios(7.0), tvos(7.0))
@interface GCControllerAxisInput : GCControllerElement

/**
 Set this block if you want to be notified when the value on this axis changes.
 
 @param axis the element that has been modified.
 @param value the value the axis was set to at the time the valueChangedHandler fired.
 */
typedef void (^GCControllerAxisValueChangedHandler)(GCControllerAxisInput *axis, float value);
@property (nonatomic, copy, nullable) GCControllerAxisValueChangedHandler valueChangedHandler;

/**
 A normalized value for the input, between -1 and 1 for axis inputs. The values are deadzoned and saturated before they are returned
 so there is no value ouside the range. Deadzoning does not remove values from the range, the full 0 to 1 magnitude of values
 are possible from the input.

 As an axis is often used in a digital sense, you can rely on a value of 0 meaning the axis is inside the deadzone.
 Any value greater than or less than zero is not in the deadzone.
 */
@property (nonatomic, readonly) float value;

/**
 Sets the normalized value for the input.
 
 @param value the value to set the input to.
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see value
 */
- (void)setValue:(float)value API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

@end

NS_ASSUME_NONNULL_END

