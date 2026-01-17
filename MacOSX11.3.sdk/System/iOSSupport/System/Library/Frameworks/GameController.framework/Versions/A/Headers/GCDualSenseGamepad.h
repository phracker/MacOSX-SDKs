//  
//  GCDualSenseGamepad.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <GameController/GCExtendedGamepad.h>
#import <GameController/GCDualSenseAdaptiveTrigger.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The GCDualSenseGamepad profile represents any supported DualSense controller.

 @see GCExtendedGamepad
 @see GCMotion
*/
API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5))
@interface GCDualSenseGamepad : GCExtendedGamepad

/**
 DualSense controllers have a touchpad with a button and two-finger tracking.
*/
@property (nonatomic, readonly) GCControllerButtonInput *touchpadButton;
@property (nonatomic, readonly) GCControllerDirectionPad *touchpadPrimary;
@property (nonatomic, readonly) GCControllerDirectionPad *touchpadSecondary;

/**
 Triggers are required to be analog inputs. Common uses would be acceleration and decelleration in a driving game for example.
 
 The DualSense has adaptive triggers, allowing you to specify a dynamic resistance force that is applied when pulling the trigger. This can,
 for example, be used to emulate the feeling of pulling back a bow string, firing a weapon, or pulling a lever.
 */
@property (nonatomic, readonly) GCDualSenseAdaptiveTrigger *leftTrigger;
@property (nonatomic, readonly) GCDualSenseAdaptiveTrigger *rightTrigger;

@end

NS_ASSUME_NONNULL_END
