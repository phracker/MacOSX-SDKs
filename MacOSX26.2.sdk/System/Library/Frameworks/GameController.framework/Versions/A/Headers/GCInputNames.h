//
//  GCInputNames.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameController/GCExtern.h>

API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
__attribute__((objc_non_runtime_protocol)) NS_REFINED_FOR_SWIFT
@protocol GCPhysicalInputElementName
@end

API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
__attribute__((objc_non_runtime_protocol)) NS_REFINED_FOR_SWIFT
@protocol GCButtonElementName <GCPhysicalInputElementName>
@end

API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
__attribute__((objc_non_runtime_protocol)) NS_REFINED_FOR_SWIFT
@protocol GCAxisElementName <GCPhysicalInputElementName>
@end

API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
__attribute__((objc_non_runtime_protocol)) NS_REFINED_FOR_SWIFT
@protocol GCSwitchElementName <GCPhysicalInputElementName>
@end

API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
__attribute__((objc_non_runtime_protocol)) NS_REFINED_FOR_SWIFT
@protocol GCDirectionPadElementName <GCPhysicalInputElementName>
@end


typedef NSString<GCPhysicalInputElementName> *const GCInputElementName NS_REFINED_FOR_SWIFT NS_TYPED_EXTENSIBLE_ENUM;
typedef NSString<GCButtonElementName> *const GCInputButtonName NS_REFINED_FOR_SWIFT NS_TYPED_EXTENSIBLE_ENUM;
typedef NSString<GCAxisElementName> *const GCInputAxisName NS_REFINED_FOR_SWIFT NS_TYPED_EXTENSIBLE_ENUM;
typedef NSString<GCSwitchElementName> *const GCInputSwitchName NS_REFINED_FOR_SWIFT NS_TYPED_EXTENSIBLE_ENUM;
typedef NSString<GCDirectionPadElementName> *const GCInputDirectionPadName NS_REFINED_FOR_SWIFT NS_TYPED_EXTENSIBLE_ENUM;


/**
A set of commonly used strings that can be used to access controller buttons
 
@example controller.physicalInputProfile.buttons[GCInputButtonA]
 
@see GCController.h
@see GCPhysicalInputProfile.h
*/

GAMECONTROLLER_EXPORT GCInputButtonName GCInputButtonA API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) NS_SWIFT_NAME(a);
GAMECONTROLLER_EXPORT GCInputButtonName GCInputButtonB API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) NS_SWIFT_NAME(b);
GAMECONTROLLER_EXPORT GCInputButtonName GCInputButtonX API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) NS_SWIFT_NAME(x);
GAMECONTROLLER_EXPORT GCInputButtonName GCInputButtonY API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) NS_SWIFT_NAME(y);

GAMECONTROLLER_EXPORT GCInputDirectionPadName GCInputDirectionPad API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) NS_SWIFT_NAME(directionPad);

GAMECONTROLLER_EXPORT GCInputDirectionPadName GCInputThumbstick API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0));
GAMECONTROLLER_EXPORT GCInputDirectionPadName GCInputLeftThumbstick API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXPORT GCInputDirectionPadName GCInputRightThumbstick API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

GAMECONTROLLER_EXPORT GCInputButtonName GCInputThumbstickButton API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0));
GAMECONTROLLER_EXPORT GCInputButtonName GCInputLeftThumbstickButton API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXPORT GCInputButtonName GCInputRightThumbstickButton API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/*
 * Grip Buttons
 */

GAMECONTROLLER_EXTERN GCInputButtonName GCInputGripButton API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0));

/*
 * Shoulder Buttons
 */

GAMECONTROLLER_EXPORT GCInputButtonName GCInputLeftShoulder API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXPORT GCInputButtonName GCInputRightShoulder API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 *  Identifies the button element located at the top-left/right of a gamepad,
 *  between the left/right shoulder button and the gamepad's horizontal center.
 */
GAMECONTROLLER_EXPORT GCInputButtonName GCInputLeftBumper API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1));
GAMECONTROLLER_EXPORT GCInputButtonName GCInputRightBumper API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1));

GAMECONTROLLER_EXPORT GCInputButtonName GCInputTrigger API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0));
GAMECONTROLLER_EXPORT GCInputButtonName GCInputLeftTrigger API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXPORT GCInputButtonName GCInputRightTrigger API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/*
 * Back Buttons
 *
 * Some gamepads include additional buttons or triggers on their underside.
 * Because the number and layout of bottom buttons can vary by controller, the
 * Game Controller framework identifies them by their ease of operation.  The
 * back left and right buttons at the first position are located nearest the
 * natural rest position of the user's fingers and are suitable for actions
 * requiring repeated inputs.  The buttons at the 'second' position may require
 * the user to move their fingers to press and should be used for less frequent
 * actions.
 *
 * Example view looking at the underside of a gamepad with four back buttons
 * arranged horizontally:
 *
 *     +---------------------------------------------------------------+
 *     |                       Controller top                          |
 *     +---------------------------------------------------------------+
 *     |                                                               |
 *   R | [(R) 0]  [(R) 1]                             [(L) 1]  [(L) 0] | L
 *     |                                                               |
 *     +---------------------------------------------------------------|
 *     |             Controller bottom (nearest the user)              |
 *     +---------------------------------------------------------------+
 */

/* Note: The `position` argument begins at index 0. */
GAMECONTROLLER_EXPORT GCInputButtonName GCInputBackLeftButton(NSInteger position) NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1));
GAMECONTROLLER_EXPORT GCInputButtonName GCInputBackRightButton(NSInteger position) NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1));

GAMECONTROLLER_EXPORT GCInputButtonName GCInputButtonHome API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXPORT GCInputButtonName GCInputButtonMenu API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXPORT GCInputButtonName GCInputButtonOptions API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXPORT GCInputButtonName GCInputButtonShare API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));

/**
A set of strings commonly used to access Xbox buttons
 
@example controller.physicalInputProfile.buttons[GCInputButtonPaddleOne]
 
@see GCController.h
@see GCPhysicalInputProfile.h
*/
GAMECONTROLLER_EXPORT GCInputButtonName GCInputXboxPaddleOne API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXPORT GCInputButtonName GCInputXboxPaddleTwo API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXPORT GCInputButtonName GCInputXboxPaddleThree API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXPORT GCInputButtonName GCInputXboxPaddleFour API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
A set of strings commonly used to access DualShock buttons
 
@example controller.physicalInputProfile.dpads[GCInputDualShockTouchpadOne]
 
@see GCController.h
@see GCPhysicalInputProfile.h
*/
GAMECONTROLLER_EXPORT GCInputDirectionPadName GCInputDualShockTouchpadOne API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXPORT GCInputDirectionPadName GCInputDualShockTouchpadTwo API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXPORT GCInputButtonName GCInputDualShockTouchpadButton API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
A set of strings commonly used by racing wheels.
*/
GAMECONTROLLER_EXPORT GCInputAxisName GCInputSteeringWheel API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
GAMECONTROLLER_EXPORT GCInputElementName GCInputShifter API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
GAMECONTROLLER_EXPORT GCInputButtonName GCInputPedalAccelerator API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
GAMECONTROLLER_EXPORT GCInputButtonName GCInputPedalBrake API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
GAMECONTROLLER_EXPORT GCInputButtonName GCInputPedalClutch API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
GAMECONTROLLER_EXPORT GCInputButtonName GCInputLeftPaddle API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
GAMECONTROLLER_EXPORT GCInputButtonName GCInputRightPaddle API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);

/// Gets the name of an arcade button at a certain position.
GAMECONTROLLER_EXPORT GCInputButtonName GCInputArcadeButtonName(NSInteger row, NSInteger column) NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0));


#pragma mark - (Spatial) Stylus Buttons

/** The stylus tip button used to detect contact with a surface.  */
GAMECONTROLLER_EXPORT GCInputButtonName GCInputStylusTip API_AVAILABLE(visionos(26.0)) API_UNAVAILABLE(macos, ios, tvos);

/**
 *  The stylus side button nearest the tip.
 *
 *  A spatial stylus has at least two buttons arranged vertically along the
 *  barrel.  The primary button is the button nearest the tip.
 */
GAMECONTROLLER_EXPORT GCInputButtonName GCInputStylusPrimaryButton API_AVAILABLE(visionos(26.0)) API_UNAVAILABLE(macos, ios, tvos);

/**
 *  The stylus side button above the primary button.
 *
 *  A spatial stylus has at least two buttons arranged vertically along the
 *  barrel.  The secondary button is located above the primary button when
 *  the stylus is held with the tip pointing down.
 */
GAMECONTROLLER_EXPORT GCInputButtonName GCInputStylusSecondaryButton API_AVAILABLE(visionos(26.0)) API_UNAVAILABLE(macos, ios, tvos);
