//
//  GameController.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <TargetConditionals.h>

#import <GameController/GCExtern.h>
#import <GameController/GCTypes.h>
#import <GameController/GCColor.h>

#import <GameController/GCProductCategories.h>


#import <GameController/GCDevice.h>

#import <GameController/GCDevicePhysicalInput.h>
#import <GameController/GCPhysicalInputElement.h>
#import <GameController/GCPhysicalInputSource.h>
#import <GameController/GCPhysicalInputExtents.h>
#import <GameController/GCLinearInput.h>
#import <GameController/GCAxisInput.h>
#import <GameController/GCAxis2DInput.h>
#import <GameController/GCRelativeInput.h>
#import <GameController/GCPressedStateInput.h>
#import <GameController/GCTouchedStateInput.h>
#import <GameController/GCSwitchPositionInput.h>
#import <GameController/GCButtonElement.h>
#import <GameController/GCAxisElement.h>
#import <GameController/GCSwitchElement.h>
#import <GameController/GCDirectionPadElement.h>

#import <GameController/GCDeviceLight.h>
#import <GameController/GCDeviceBattery.h>

#import <GameController/GCControllerElement.h>
#import <GameController/GCControllerAxisInput.h>
#import <GameController/GCControllerButtonInput.h>
#import <GameController/GCControllerDirectionPad.h>
#import <GameController/GCControllerTouchpad.h>
#import <GameController/GCDualSenseAdaptiveTrigger.h>
#import <GameController/GCDeviceCursor.h>

#import <GameController/GCMotion.h>

#import <GameController/GCPhysicalInputProfile.h>
#import <GameController/GCInputNames.h>

#import <GameController/GCGamepad.h>
#import <GameController/GCGamepadSnapshot.h>

#import <GameController/GCExtendedGamepad.h>
#import <GameController/GCExtendedGamepadSnapshot.h>

#import <GameController/GCKeyCodes.h>
#import <GameController/GCKeyNames.h>
#import <GameController/GCKeyboardInput.h>
#import <GameController/GCMouseInput.h>

#import <GameController/GCXboxGamepad.h>
#import <GameController/GCDualShockGamepad.h>
#import <GameController/GCDualSenseGamepad.h>

#import <GameController/GCMicroGamepad.h>
#import <GameController/GCMicroGamepadSnapshot.h>
#import <GameController/GCDirectionalGamepad.h>

#import <GameController/GCController.h>
#import <GameController/GCStylus.h>

#import <GameController/GCKeyboard.h>
#import <GameController/GCMouse.h>

#import <GameController/GCRacingWheel.h>
#import <GameController/GCRacingWheelInput.h>
#import <GameController/GCSteeringWheelElement.h>
#import <GameController/GCGearShifterElement.h>

#import <GameController/GCDeviceHaptics.h>

#import <GameController/GCEventViewController.h>
#import <GameController/GCEventInteraction.h>
#import <GameController/GCGameControllerActivationContext.h>
#import <GameController/GCGameControllerSceneDelegate.h>
#if __has_include(<GameController/GCVirtualController.h>)
#import <GameController/GCVirtualController.h>
#endif

#import <GameController/GCSyntheticDeviceKeys.h>
