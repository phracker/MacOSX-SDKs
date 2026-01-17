//
//  GCKeyboard.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <GameController/GameController.h>
#import <GameController/GCExtern.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Use these constants with NSNotificationCenter to listen to connection and disconnection events
 
 Use GCKeyboardDidConnectNotification for observing keyboard connection
 Use GCKeyboardDidDisconnectNotification for observing keyboard disconnection
 
 The 'object' property of the notification will contain the GCKeyboard that was connected or disconnected.
 
 @see NSNotificationCetner
 @note All connected keyboards are coalesced into one keyboard object, so notification about connection/disconnection will only be delivered once until last keyboard disconnects.
 */
GAMECONTROLLER_EXTERN NSString *const GCKeyboardDidConnectNotification API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN NSString *const GCKeyboardDidDisconnectNotification API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 GCKeyboard is available to an application that links to GameController.framework
 There are 2 ways to access keyboard paired to the system:
 1: Querying for the coalescedKeyboard using [GCKeyboard coalescedKeyboard]
 2: Registering for Connection/Disconnection notifications from NSNotificationCenter
 
 @note All connected keyboards are coalesced into one keyboard object, so notification about connection/disconnection will only be delivered once.
 */
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface GCKeyboard : NSObject<GCDevice>

/**
 Unlike GCController GCKeyboard only has one input profile.
 
 This profile allows you to query buttons and button state
 */
@property (nonatomic, strong, readonly, nullable) GCKeyboardInput *keyboardInput API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 Keyboard object that represents all keyboards connected to the device
 Should be used to query key states every time input needs to be handled
 */
@property (class, atomic, strong, readonly, nullable) GCKeyboard *coalescedKeyboard API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

@end

NS_ASSUME_NONNULL_END
