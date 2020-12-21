//  
//  GCDirectionalGamepad.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameController/GCMicroGamepad.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Directional Gamepad profile.
 
 All controller profiles provide a base level of information about the controller they belong to. A directional gamepad
 features a subset of the possible inputs on a micro gamepad. It guarantees:
    - The gamepad does not support motion, meaning
        - -[GCController motion] is always nil
        - -[GCDirectionalGamepad allowsRotation] is always NO
    - The gamepad has a digital dpad, meaning
        - -[GCDirectionalGamepad dpad].analog is always NO
        - -[GCDirectionalGamepad reportsAbsoluteDpadValues] is always YES
 
 A profile maps the hardware notion of a controller into a logical controller. One that a developer can design for
 and depend on, no matter the underlying hardware. If your game supports GCMicroGamepad, but does not need
 the motion and analog dpad functionality of GCMicroGamepad, be sure to add Directional Gamepad to your project's
 supported Game Controller capabilities.
 
 @see GCMicroGamepad
 */
API_AVAILABLE(macos(11.1), ios(14.3), tvos(14.3))
@interface GCDirectionalGamepad : GCMicroGamepad

@end

NS_ASSUME_NONNULL_END
