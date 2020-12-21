//
//  GCInputNames.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <GameController/GCExtern.h>

/**
A set of commonly used strings that can be used to access controller buttons
 
@example controller.physicalInputProfile.buttons[GCInputButtonA]
 
@see GCController.h
@see GCPhysicalInputProfile.h
*/

GAMECONTROLLER_EXTERN NSString *const GCInputButtonA API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN NSString *const GCInputButtonB API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN NSString *const GCInputButtonX API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN NSString *const GCInputButtonY API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

GAMECONTROLLER_EXTERN NSString *const GCInputDirectionPad API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN NSString *const GCInputLeftThumbstick API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN NSString *const GCInputRightThumbstick API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

GAMECONTROLLER_EXTERN NSString *const GCInputLeftShoulder API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN NSString *const GCInputRightShoulder API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN NSString *const GCInputLeftTrigger API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN NSString *const GCInputRightTrigger API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN NSString *const GCInputLeftThumbstickButton API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN NSString *const GCInputRightThumbstickButton API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

GAMECONTROLLER_EXTERN NSString *const GCInputButtonHome API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN NSString *const GCInputButtonMenu API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN NSString *const GCInputButtonOptions API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
A set of strings commonly used to access Xbox buttons
 
@example controller.physicalInputProfile.buttons[GCInputButtonPaddleOne]
 
@see GCController.h
@see GCPhysicalInputProfile.h
*/
GAMECONTROLLER_EXTERN NSString *const GCInputXboxPaddleOne API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN NSString *const GCInputXboxPaddleTwo API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN NSString *const GCInputXboxPaddleThree API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN NSString *const GCInputXboxPaddleFour API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
A set of strings commonly used to access DualShock buttons
 
@example controller.physicalInputProfile.dpads[GCInputDualShockTouchpadOne]
 
@see GCController.h
@see GCPhysicalInputProfile.h
*/
GAMECONTROLLER_EXTERN NSString *const GCInputDualShockTouchpadOne API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN NSString *const GCInputDualShockTouchpadTwo API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN NSString *const GCInputDualShockTouchpadButton API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
