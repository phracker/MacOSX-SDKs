//
//  GCMouse.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <GameController/GameController.h>
#import <GameController/GCExtern.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Use these constants with NSNotificationCenter to listen to connection and disconnection events.
 
 Use GCMouseDidConnectNotification for observing connections of mice.
 Use GCMouserDidDisconnectNotification for observing disconnections of mice.
 
 Connections and disconnections of mice will also be reflected in the mice array
 of the GCMouse class.
 
 The 'object' property of the notification will contain the GCMouse that was connected or disconnected.
 For example:
 
 - (void)controllerDidConnect:(NSNotification *)note {
 
 GCMouse *mouse = note.object;
 
 ....
 }
 
 @see NSNotificationCenter
 @see GCMouse.mice
 */
GAMECONTROLLER_EXTERN NSString *const GCMouseDidConnectNotification API_AVAILABLE(macos(11.0), ios(14.0));
GAMECONTROLLER_EXTERN NSString *const GCMouseDidDisconnectNotification API_AVAILABLE(macos(11.0), ios(14.0));

/**
Use these constants with NSNotificationCenter to listen to a controller becoming the most recently used mouse.
This is a good time to swap out UI to match the new current mouse, and unregister any handlers with
 the old current controller.

The 'object' property of the notification will contain the GCMouse that became the current one.
For example:

- (void)mouseDidBecomeCurrent:(NSNotification *)note {

GCMouse *mouse = note.object;

...
}

@see NSNotificationCenter
@see GCMouse.mice
@see GCMouse.current
*/
GAMECONTROLLER_EXTERN NSString *const GCMouseDidBecomeCurrentNotification API_AVAILABLE(macos(11.0), ios(14.0));
GAMECONTROLLER_EXTERN NSString *const GCMouseDidStopBeingCurrentNotification API_AVAILABLE(macos(11.0), ios(14.0));

/**
 Mice are available to an application that links to GameController.framework. There are 2 ways to access mice
 paired to the system. Adopt both to ensure the best user experience:
 
 1: Querying for the current array of mice using [GCMouse mice]
 2: Registering for Connection/Disconnection notifications from NSNotificationCenter.
 */
API_AVAILABLE(macos(11.0), ios(14.0))
@interface GCMouse : NSObject<GCDevice>

/**
 Unlike GCController GCMouse supports only one input profile
 Profile contains mouse buttons, scroll wheel and  pointer delta.
 */
@property (nonatomic, strong, readonly, nullable) GCMouseInput *mouseInput;

/**
 The most recently used mouse device. If a user actuates a mouse input, that mouse will become the current one.
 @see GCMouseDidBecomeCurrentNotification
 @see GCMouseDidStopBeingCurrentNotification
 */
@property (class, atomic, strong, readonly, nullable) GCMouse *current;

/*
 Get a list of mice currently attached to the system
 
 @see GCMouseDidConnectNotification
 @see GCMouseDidDisconnectNotification
 */
+ (NSArray<GCMouse *> *)mice;

@end

NS_ASSUME_NONNULL_END
