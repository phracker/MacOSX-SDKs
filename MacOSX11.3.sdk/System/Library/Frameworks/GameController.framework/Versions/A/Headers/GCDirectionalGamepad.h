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
 The primary directional input surface for the directional gamepad
 
 @note Equivalent to microgamepad.dpad
*/
GAMECONTROLLER_EXTERN NSString *const GCInputDirectionalDpad API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5));

/**
 An optional secondary directional input surface for the directional gamepad. This input is guaranteed to be an 8-way digital dpad with physical Up, Down, Left, Right butttons.
*/
GAMECONTROLLER_EXTERN NSString *const GCInputDirectionalCardinalDpad API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5));

/**
 Directional Gamepad profile.
 
 All controller profiles provide a base level of information about the controller they belong to. A directional gamepad
 features a subset of the possible inputs on a micro gamepad. It guarantees:
    - The gamepad does not support motion, meaning
        - -[GCController motion] is always nil
        - -[GCDirectionalGamepad allowsRotation] is always NO
 
 Additionally, the gamepad may have a digital or analog dpad.
        - -[GCDirectionalGamepad dpad].analog may be YES or NO
        - If -[GCDirectionalGamepad dpad].analog is NO, then -[GCDirectionalGamepad reportsAbsoluteDpadValues] is always YES
 
 A profile maps the hardware notion of a controller into a logical controller. One that a developer can design for
 and depend on, no matter the underlying hardware. If your game supports GCMicroGamepad, but does not need
 the motion and analog dpad functionality of GCMicroGamepad, be sure to add Directional Gamepad to your project's
 supported Game Controller capabilities.
 
 @see GCMicroGamepad
 
 @note If you want to use the additional functionality of GCDirectionalGamepad, you should set GCSupportsMultipleMicroGamepads to YES and handle microgamepad connections separately.
 */
API_AVAILABLE(macos(11.1), ios(14.3), tvos(14.3))
@interface GCDirectionalGamepad : GCMicroGamepad

@end

NS_ASSUME_NONNULL_END
