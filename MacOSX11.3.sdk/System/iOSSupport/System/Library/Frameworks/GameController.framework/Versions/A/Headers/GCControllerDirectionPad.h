//
//  GCControllerDirectionPad.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//


#import <GameController/GCControllerElement.h>

@class GCControllerAxisInput;
@class GCControllerButtonInput;
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A direction pad is a common grouping of 2 axis inputs where the input can also be interpreted as 2 sets of mutually exclusive button pairs.
 Only one button in each pair, {up, down} and {left, right}, can be pressed at any one time.
 */
API_AVAILABLE(macos(10.9), ios(7.0), tvos(7.0))
@interface GCControllerDirectionPad : GCControllerElement

/**
 Set this block if you want to be notified when the value on this axis changes.
 
 @param dpad the direction pad collection whose axis have been modified.
 @param xValue the value the x axis was set to at the time the valueChangedHandler fired.
 @param yValue the value the y axis was set to at the time the valueChangedHandler fired.
 */
typedef void (^GCControllerDirectionPadValueChangedHandler)(GCControllerDirectionPad *dpad, float xValue, float yValue);
@property (nonatomic, copy, nullable) GCControllerDirectionPadValueChangedHandler valueChangedHandler;

@property (nonatomic, readonly) GCControllerAxisInput *xAxis;
@property (nonatomic, readonly) GCControllerAxisInput *yAxis;

@property (nonatomic, readonly) GCControllerButtonInput *up;
@property (nonatomic, readonly) GCControllerButtonInput *down;

@property (nonatomic, readonly) GCControllerButtonInput *left;
@property (nonatomic, readonly) GCControllerButtonInput *right;

/**
 Sets the normalized value for the direction pad's axis inputs. Will update the states of the direction pad's button inputs as well.
 
 @param xAxis the value to set the xAxis of the touchpad to.
 @param yAxis the value to set the yAxis of the touchpad to.
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see value
 @see pressed
 */
- (void)setValueForXAxis:(float)xAxis yAxis:(float)yAxis API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

@end

NS_ASSUME_NONNULL_END
