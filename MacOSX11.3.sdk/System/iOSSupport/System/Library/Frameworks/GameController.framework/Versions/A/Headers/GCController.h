//
//  GCController.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <TargetConditionals.h>

#import <GameController/GameController.h>
#import <GameController/GCExtern.h>
#import <GameController/GCColor.h>

#if TARGET_OS_OSX
#import <IOKit/hid/IOHIDBase.h>
#endif

@class GCMotion;
@class CHHapticEngine;
@class GCDeviceHaptics;
@class GCDeviceLight;
@class GCDeviceBattery;
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Use these constants with NSNotificationCenter to listen to connection and disconnection events.
 
 Use GCControllerDidConnectNotification for observing connections of controllers.
 Use GCControllerDidDisconnectNotification for observing disconnections of controllers.
 
 Connections and disconnections of controllers will also be reflected in the controllers array
 of the GCController class.
 
 The 'object' property of the notification will contain the GCController that was connected or disconnected.
 For example:
 
 - (void)controllerDidConnect:(NSNotification *)note {
 
 GCController *controller = note.object;
 
 ....
 }
 
 @see NSNotificationCenter
 @see GCController.controllers
 */
GAMECONTROLLER_EXTERN NSString *const GCControllerDidConnectNotification API_AVAILABLE(macos(10.9), ios(7.0), tvos(7.0));
GAMECONTROLLER_EXTERN NSString *const GCControllerDidDisconnectNotification API_AVAILABLE(macos(10.9), ios(7.0), tvos(7.0));

/**
Use these constants with NSNotificationCenter to listen to a controller becoming the most recently used controller.
This is a good time to swap out UI to match the new current controller, and unregister any handlers with
 the old current controller.

The 'object' property of the notification will contain the GCController that became the current controller.
For example:

- (void)controllerDidBecomeCurrent:(NSNotification *)note {

GCController *controller = note.object;

...
}

@see NSNotificationCenter
@see GCController.controllers
*/
GAMECONTROLLER_EXTERN NSString *const GCControllerDidBecomeCurrentNotification API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN NSString *const GCControllerDidStopBeingCurrentNotification API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 This is the player index that a connected controller will have if it has never been assigned a player index on the current system.
 Controllers retain the player index they have been assigned between game sessions, so if you wish to unset the player index of a
 controller set it back to this value.
 */
typedef NS_ENUM(NSInteger, GCControllerPlayerIndex) {
    GCControllerPlayerIndexUnset = -1,
    GCControllerPlayerIndex1 = 0,
    GCControllerPlayerIndex2,
    GCControllerPlayerIndex3,
    GCControllerPlayerIndex4,
};


/**
 Controllers are available to an application that links to GameController.framework. There are 2 ways to access controllers
 paired to the system, adopt both to ensure the best user experience:
 
 1: Querying for the the current array or controllers using [GCController controllers].
 2: Registering for Connection/Disconnection notifications from NSNotificationCenter.
 
 Only controllers that support one of the allowed profiles, such as GCExtendedGamepad, will be enumerated. Check for the profile
 supported before using a controller in your application. Ignore a controller that doesn't support a profile that suits
 your application, as the user will expect their controller to either be fully supported or not supported at all.
  */
API_AVAILABLE(macos(10.9), ios(7.0), tvos(7.0))
@interface GCController : NSObject<GCDevice>

/**
 Set this block to be notified when a user intends to suspend or resume the current game state. A controller will have a button
 dedicated to suspending and resuming play and invoking context sensitive actions. During event handling the system will
 notify the application using this block such that the application can handle the suspension and resumption from the given controller.
 
 Use this to implement your canonical transition to a pause menu for example if that is your application's desired handling
 of suspension in play. You may pause and resume based on game state as well so the event is only called each time the
 pause/resume button is pressed.
 
 @note This handler has been deprecated in favor of the Menu button found on GCMicroGamepad and GCExtendedGamepad.
 @see microGamepad
 @see extendedGamepad
 */
@property (nonatomic, copy, nullable) void (^controllerPausedHandler)(GCController *controller) API_DEPRECATED("controllerPausedHandler has been deprecated. Use the Menu button found on the controller's profile, if it exists.", macos(10.9, 10.15), ios(7.0, 13.0), tvos(9.0, 13.0));


/**
 The most recently used game controller. If a user actuates a game controller input, that controller will become the current one.
 
 @note This is useful for single player games where you only care about whether an input is pressed, and not where it came from. You
 will still need to register for changes to GCController.current so that your UI can remain up-to-date with the current controller.
 */
@property (class, atomic, strong, readonly, nullable) GCController *current API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 Whether the current application should monitor and respond to game controller events when it is not the frontmost application.
 
 @example If shouldMonitorBackgroundEvents is NO, and the application is not the frontmost application, any inputs from a game controller will
 not be forwarded to the application. Once the application becomes the frontmost application, game controller events will be forwarded.
 
 @note Starting with macOS Big Sur 11.3, shouldMonitorBackgroundEvents will be NO by default. For applications built prior to macOS Big Sur 11.3,
 (or running on devices with an earlier version of macOS), shouldMonitorBackgroundEvents will be YES by default. On iOS and tvOS, this property is ignored.
 */
@property (class, nonatomic, readwrite) BOOL shouldMonitorBackgroundEvents API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5));


/**
 A controller may be form fitting or otherwise closely attached to the device. This closeness to other inputs on the device
 may suggest that interaction with the device may use other inputs easily. This is presented to developers to allow them to
 make informed decisions about UI and interactions to choose for their game in this situation.
 */
@property (nonatomic, readonly, getter = isAttachedToDevice) BOOL attachedToDevice;

/**
 A controller may represent a real device managed by the operating system, or a virtual snapshot created by the developer.
 If a controller is directly created by the developer, it is considered to be a snapshot, allowing direct writes to any
 GCControllerElement of its profiles. If the controller is not snapshot, the system will reject any write requests to GCControllerElement.
 
 @see controllerWithMicroGamepad
 @see controllerWithExtendedGamepad
 @see capture
 */
@property (atomic, readonly, getter = isSnapshot) BOOL snapshot API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/**
 A player index for the controller, defaults to GCControllerPlayerIndexUnset.
 
 This can be set both for the application to keep track of controllers and as a signal to make a controller display a player
 index on a set of LEDs or some other mechanism.
 
 A controller is not guaranteed to have a visual display of the playerIndex, playerIndex does not persist for a controller
 with regards to a system.
 
 Negative values less than GCControllerPlayerIndexUnset will just map back to GCControllerPlayerIndexUnset when read back.
 */
@property (nonatomic) GCControllerPlayerIndex playerIndex;

/**
 Gets the battery information if controller supports one
 
 This property is useful when you try to notify your user to change or charge controller before it runs out of battery life
 or simply display the current battery level and status.
 */
@property (nonatomic, copy, readonly, nullable) GCDeviceBattery *battery API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 Gets the profile for the controller that suits current application.
 
 There are several supported profiles, with an additional optional profile for motion as well.
 Each controller may be able to map its inputs into all profiles or just one kind of profile. Query for the controller
 profile that suits your game, the simplest kind will be supported by the broadest variety
 of controllers. A controller supporting the Extended Gamepad profile for example supports the Gamepad profile and more.
 As such it can always be used just in the Gamepad profile if that suits the game.
 
 A physical controller that supports a profile must support it completely. That means that all buttons and axis inputs must
 be valid inputs that a developer can utilize.
 
 If a controller does not support the given profile the returned value will be nil. Use this to filter controllers if the
 application requires a specific kind of profile.
 @see motion
 */
@property (nonatomic, strong, readonly, nullable) GCGamepad *gamepad API_DEPRECATED_WITH_REPLACEMENT("extendedGamepad", macos(10.9, 10.12), ios(7.0, 10.0), tvos(7.0, 10.0));
@property (nonatomic, strong, readonly, nullable) GCMicroGamepad *microGamepad;
@property (nonatomic, strong, readonly, nullable) GCExtendedGamepad *extendedGamepad;


/**
 Gets the motion input profile. This profile is optional and may be available if the controller is attached to a device that supports motion.
 If this is nil the controller does not support motion input and only the gamepad & extendedGamepad profiles are available.
 @see gamepad
 @see extendedGamepad
 */
@property (nonatomic, strong, readonly, nullable) GCMotion *motion API_AVAILABLE(macos(10.10), ios(8.0), tvos(8.0));

/**
 Gets the light for the controller, if one exists.
 
 A controller's light can be used to signal information to the player, such as using different light colors based on the player
 index. It can also be used to react to in-game events and enhance user immersion.
 */
@property (nonatomic, retain, readonly, nullable) GCDeviceLight *light API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 Gets the haptics for the controller, if one exists.
 
 Use this property to create CHHapticEngine instances according to your needs. 
 
 @note Haptics are a drain on the controller's battery, and can be distracting when used excessively. 
 */
@property (nonatomic, retain, readonly, nullable) GCDeviceHaptics *haptics API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));


/**
 Polls the state vector of the controller and saves it to a new and writable instance of GCController.
 
 If your application is heavily multithreaded this may also be useful to guarantee atomicity of input handling as
 a snapshot will not change based on user input once it is taken.
 
 @see snapshot
 @return A new controller with the duplicated state vector of the current controller
 */
- (GCController *)capture API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/**
 Get a list of controllers currently attached to the system.
 
 @see GCControllerDidConnectNotification
 @see GCControllerDidDisconnectNotification
 */
+ (NSArray<GCController *> *)controllers;


/**
 Start discovery of new wireless controllers that are discoverable. This is an asynchronous and the supplied completionHandler
 will get called once no more devices can be found. If there are already multiple controllers available for use, there
 may be little reason to automatically start discovery of new wireless controllers. In this situation it may be best to
 allow the user to start discovery manually via in-game UI.
 
 Once discovery has started new controllers will notify themselves as connected via GCControllerDidConnectNotification.
 As the notification arrives the controller is also available in the controllers array.

 The completionHandler could be used to update UI and/or game state to indicate that no more controllers will be found
 and the current set of controllers is what is available for use in the game.
 
 If a completionHandler was provided, it will be called once when discovery stops. Either from an explicit call to
 stopWirelessControllerDiscovery or from timing out or stopping in its natural course of operation. Thus the
 completionHandler will at most be called once per call to startWirelessControllerDiscoveryWithCompletionHandler:.
 
 The completionHandler may also not get called at all, if for example startWirelessControllerDiscoveryWithCompletionHandler:
 is called multiple times during dicovery. For this case the net effect is that the completionHandler is replaced with each call
 and only the last one set before discovery stops will be called.
 
 @param completionHandler an optional handler that is called when discovery stops. (may be nil, in which case you will not be notified when discovery stops)
 @see stopWirelessControllerDiscovery
 @see controllers
 */
+ (void)startWirelessControllerDiscoveryWithCompletionHandler:(nullable void (^)(void))completionHandler;

/**
 If no more controllers are needed, depending on game state or number of controllers supported by a game, the discovery
 process can be stopped. Calling stopWirelessControllerDiscovery when no discovery is currently in progress will return
 immediately without any effect, thus it is safe to call even if the completionHandler of
 startWirelessControllerDiscoveryWithCompletionHandler: has been called.
 
 @see startWirelessControllerDiscoveryWithCompletionHandler:
 */
+ (void)stopWirelessControllerDiscovery;

/**
 Creates a controller with a micro gamepad profile.
 
 This controller will be considered a snapshot, allowing developers to write to any GCControllerElement of its profiles.
 
 @see snapshot
 @return A new controller with a micro gamepad profile
 */
+ (GCController *)controllerWithMicroGamepad API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/**
 Creates a controller with an extended gamepad profile.
 
 This controller will be considered a snapshot, allowing developers to write to any GCControllerElement of its profiles.
 
 @see snapshot
 @return A new controller with an extended gamepad profile
 */
+ (GCController *)controllerWithExtendedGamepad API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

#if TARGET_OS_OSX
/**
 Returns YES if the given HID device is supported by the Game Controller framework, and will have an associated GCController instance.
 
 @note This is not cheap, be sure to cache the result
 */
+ (BOOL)supportsHIDDevice:(IOHIDDeviceRef)device API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios, tvos);
#endif

@end

NS_ASSUME_NONNULL_END

