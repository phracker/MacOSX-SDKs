//
//  GCXboxGamepad.h
//  GameController
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <GameController/GCExtendedGamepad.h>

/**
 The GCXboxGamepad profile represents any supported Xbox controller.

 @see GCExtendedGamepad
*/
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface GCXboxGamepad : GCExtendedGamepad

/**
 Some Xbox controller variants can support up to four additional buttons.
 
 @example The standard Bluetooth-enabled Xbox Wireless Controller does not have paddle buttons
 @example The Xbox Elite Wireless Controller has four extra digital buttons.
 
 @note The four extra digital buttons on the Xbox Elite Wireless Controller are only directly addressable when the controller
    is on its default mapping profile. Otherwise, the paddle buttons are directly bound to other inputs on the controller.
 */
@property (nonatomic, readonly, nullable) GCControllerButtonInput *paddleButton1;
@property (nonatomic, readonly, nullable) GCControllerButtonInput *paddleButton2;
@property (nonatomic, readonly, nullable) GCControllerButtonInput *paddleButton3;
@property (nonatomic, readonly, nullable) GCControllerButtonInput *paddleButton4;

@end
