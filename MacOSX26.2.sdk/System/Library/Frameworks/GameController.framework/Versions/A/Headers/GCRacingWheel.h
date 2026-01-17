//  
//  GCRacingWheel.h
//  GameController
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameController/GameController.h>

@class GCRacingWheelInput;

NS_ASSUME_NONNULL_BEGIN

/**
 Use these constants with NSNotificationCenter to listen to connection and disconnection events.
 
 Use GCRacingWheelDidConnectNotification for observing connections of racing wheels.
 Use GCRacingWheelDidDisconnectNotification for observing disconnections of racing wheels.
 
 Connections and disconnections of racing wheels will also be reflected in the connectedRacingWheels array
 of the GCRacingWheel class.
 
 The 'object' property of the notification will contain the GCRacingWheel that was connected or disconnected.
 For example:
 
 - (void)wheelDidConnect:(NSNotification *)note {
     GCRacingWheel *controller = note.object;
     ....
 }
 
 @see NSNotificationCenter
 @see GCRacingWheel.connectedRacingWheels
 */
GAMECONTROLLER_EXPORT NSString *const GCRacingWheelDidConnectNotification API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
GAMECONTROLLER_EXPORT NSString *const GCRacingWheelDidDisconnectNotification API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);


API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos)
@interface GCRacingWheel : NSObject <GCDevice>

- (instancetype)init NS_UNAVAILABLE;

/**
 Get the collection of racing wheels currently attached to the system.
 
 @see GCRacingWheelDidConnectNotification
 @see GCRacingWheelDidDisconnectNotification
 */
@property (nonatomic, readonly, class) NSSet<GCRacingWheel*> *connectedRacingWheels;

/**
 A GCRacingWheel must be acquired before your application can begin receiving
 events from it.  Prior to acquisition, your application may only query the
 properties of the racing wheel.  Acquisition is exclusive and may fail.
 */
- (BOOL)acquireDeviceWithError:(NSError * __autoreleasing __nullable * __nullable)error;

/**
 Releases a previous acquisition of the racing wheel.
 */
- (void)relinquishDevice;

/**
 Checks if the racing wheel has been acquired by the application.
 
 This property is observable.
 */
@property (readonly, getter = isAcquired) BOOL acquired;

/** Get the physical input profile for the racing wheel. */
@property (strong, readonly) GCRacingWheelInput *wheelInput;

#pragma mark Snapshots

/**
 A GCRacingWheel may represent a real device managed by the operating system,
 or a snapshot created by the developer.
 
 @see capture
 */
@property (atomic, readonly, getter = isSnapshot) BOOL snapshot;

/**
 Polls the state vector of the racing wheel and saves it to a new instance of
 GCRacingWheel.
 
 If your application is heavily multithreaded this may also be useful to
 guarantee atomicity of input handling as a snapshot will not change based on
 user input once it is taken.
 
 @see snapshot
 @return A new racing wheel with the duplicated state vector of the receiver.
 */
- (GCRacingWheel *)capture;

@end

NS_ASSUME_NONNULL_END
