//
//  GCExtendedGamepad.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <GameController/GameController.h>

NS_ASSUME_NONNULL_BEGIN

@class GCController;
@class GCExtendedGamepadSnapshot;

/**
 Extended Gamepad profile. Has all the physical features of a Standard Gamepad and more.
 
 In comparison to the Standard gamepad, The directional pad on an Extended gamepad is optionally analog
 as the two thumbsticks provided are required to be analog.
 
 All controller profiles provide a base level of information about the controller they belong to.
 
 A profile maps the hardware notion of a controller into a logical controller. One that a developer can
 design for and depend on, no matter the underlying hardware.
 */
GAMECONTROLLER_EXPORT
@interface GCExtendedGamepad : NSObject

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
typedef void (^GCExtendedGamepadValueChangedHandler)(GCExtendedGamepad *gamepad, GCControllerElement *element);
@property (nonatomic, copy, nullable) GCExtendedGamepadValueChangedHandler valueChangedHandler;

/**
 Polls the state vector of the controller and saves it to a snapshot. The snapshot is stored in a device independent
 format that can be serialized and used at a later date. This is useful for features such as quality assurance,
 save game or replay functionality among many.
 
 If your application is heavily multithreaded this may also be useful to guarantee atomicity of input handling as
 a snapshot will not change based on user input once it is taken.
 */
- (GCExtendedGamepadSnapshot *)saveSnapshot;

/**
 Required to be analog in the Extended profile. All the elements of this directional input are thus analog.
 */
@property (nonatomic, readonly) GCControllerDirectionPad *dpad;

/**
 All face buttons are required to be analog in the Extended profile. These must be arranged
 in the diamond pattern given below:
 
   Y
  / \
 X   B
  \ /
   A
 
 */
@property (nonatomic, readonly) GCControllerButtonInput *buttonA;
@property (nonatomic, readonly) GCControllerButtonInput *buttonB;
@property (nonatomic, readonly) GCControllerButtonInput *buttonX;
@property (nonatomic, readonly) GCControllerButtonInput *buttonY;

/**
 A thumbstick is a 2-axis control that is physically required to be analog. All the elements of this directional input are thus analog.
 */
@property (nonatomic, readonly) GCControllerDirectionPad *leftThumbstick;

/**
 A thumbstick is a 2-axis control that is physically required to be analog. All the elements of this directional input are thus analog.
 */
@property (nonatomic, readonly) GCControllerDirectionPad *rightThumbstick;

/**
 Shoulder buttons are required to be analog inputs.
 */
@property (nonatomic, readonly) GCControllerButtonInput *leftShoulder;
/**
 Shoulder buttons are required to be analog inputs.
 */
@property (nonatomic, readonly) GCControllerButtonInput *rightShoulder;

/**
 Triggers are required to be analog inputs. Common uses would be acceleration and decelleration in a driving game for example.
 */
@property (nonatomic, readonly) GCControllerButtonInput *leftTrigger;
@property (nonatomic, readonly) GCControllerButtonInput *rightTrigger;

@end

NS_ASSUME_NONNULL_END
