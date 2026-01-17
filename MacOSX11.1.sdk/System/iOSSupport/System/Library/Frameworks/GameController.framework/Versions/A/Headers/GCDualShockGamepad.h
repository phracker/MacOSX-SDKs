//
//  GCDualShockGamepad.h
//  GameController
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <GameController/GCExtendedGamepad.h>

/**
 The GCDualShockGamepad profile represents any supported DualShock 4 controller. 

 @see GCExtendedGamepad
 @see GCMotion
*/
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface GCDualShockGamepad : GCExtendedGamepad

/**
 DualShock controllers have a touchpad with a button and two-finger tracking.
*/
@property (nonatomic, readonly) GCControllerButtonInput *touchpadButton;
@property (nonatomic, readonly) GCControllerDirectionPad *touchpadPrimary;
@property (nonatomic, readonly) GCControllerDirectionPad *touchpadSecondary;

@end
