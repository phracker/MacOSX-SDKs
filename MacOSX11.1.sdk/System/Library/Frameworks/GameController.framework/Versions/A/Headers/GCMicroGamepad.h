//
//  GCMicroGamepad.h
//  GameController
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <GameController/GCExtern.h>
#import <GameController/GCPhysicalInputProfile.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class GCController;
@class GCMicroGamepadSnapshot;
@class GCControllerDirectionPad;
@class GCControllerElement;
@class GCControllerButtonInput;

/**
 Micro Gamepad profile.
 
 All controller profiles provide a base level of information about the controller they belong to.
 
 A profile maps the hardware notion of a controller into a logical controller. One that a developer can design for
 and depend on, no matter the underlying hardware.
 */
API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunguarded-availability"
@interface GCMicroGamepad : GCPhysicalInputProfile
#pragma clang diagnostic pop

/**
 A profile keeps a reference to the controller that this profile is mapping input from.
 */
#if !__has_feature(objc_arc)
@property (nonatomic, readonly, assign) GCController *controller;
#else
@property (nonatomic, readonly, weak) GCController *controller;
#endif

/**
 Set this block if you want to be notified when a value on a element changed. If multiple elements have changed this block will be called
 for each element that changed. As elements in a collection, such as the axis in a dpad, tend to change at the same time and thus
 will only call this once with the collection as the element.
 
 @param gamepad this gamepad that is being used to map the raw input data into logical values on controller elements such as the dpad or the buttons.
 @param element the element that has been modified.
 */
typedef void (^GCMicroGamepadValueChangedHandler)(GCMicroGamepad *gamepad, GCControllerElement *element);
@property (nonatomic, copy, nullable) GCMicroGamepadValueChangedHandler valueChangedHandler;

/**
 Polls the state vector of the controller and saves it to a snapshot. The snapshot is stored in a device independent
 format that can be serialized and used at a later date. This is useful for features such as quality assurance,
 save game or replay functionality among many.
 
 If your application is heavily multithreaded this may also be useful to guarantee atomicity of input handling as
 a snapshot will not change based on user input once it is taken.
 
 @see GCMicroGamepadSnapshot
 */
- (GCMicroGamepadSnapshot *)saveSnapshot API_DEPRECATED("GCMicroGamepadSnapshot has been deprecated, use [GCController capture] instead", macos(10.9, 10.15), ios(7.0, 13.0), tvos(7.0, 13.0));

/**
 Optionally analog in the Micro profile. All the elements of this directional input are either analog or digital.
 */
@property (nonatomic, readonly, strong) GCControllerDirectionPad *dpad;

/**
 The Micro profile has two buttons that are optionally analog in the Micro profile.
 Button A is the primary action button, it indicates affirmative action and should be used to advance in menus
 or perform the primary action in gameplay.
 */
@property (nonatomic, readonly, strong) GCControllerButtonInput *buttonA;

/**
 Button X is the secondary action button, it indicates an alternate affirmative action and should be used to perform
 a secondary action. If there is no secondary action it should be used as equivalent to buttonA.
 
 Unlike on other profiles there is no negative button on this profile. Instead the menu button should be
 used to present menu content or to retreat in a menu flow.
 @see buttonA
 */
@property (nonatomic, readonly, strong) GCControllerButtonInput *buttonX;

/**
 Button menu is the primary menu button, and should be used to enter the main menu and pause the game.
 */
@property (nonatomic, readonly) GCControllerButtonInput *buttonMenu API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/**
 The Micro profile can use the raw position values of the touchpad on the remote as D-pad values, or it can create a virtual dpad centered around the first contact point with the surface.
 
 If NO; a smaller sliding window is created around the initial touch point and subsequent movement is relative to that center. Movement outside the window will slide the window with it to re-center it. This is great for surfaces where there is no clear sense of a middle and drift over time is an issue.
 
 If YES; the absolute values are used and any drift will have to managed manually either through user traning or by a developer using the dpad.
 
 The default value for this property is NO, meaning a sliding window is used for the dpad.
 */
@property (nonatomic) BOOL reportsAbsoluteDpadValues;

/**
 Allows the Micro profile to monitor the orientation of the controller, if the controller is positioned in landscape orientation, D-pad input values will be transposed 90 degrees to match the new orientation.
 
 The default value for this property is NO.
 */
@property (nonatomic) BOOL allowsRotation;

/**
 Sets the state vector of the micro gamepad to a copy of the input micro gamepad's state vector.
 
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see GCController.snapshot
 */
- (void) setStateFromMicroGamepad:(GCMicroGamepad *)microGamepad API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

@end


NS_ASSUME_NONNULL_END
