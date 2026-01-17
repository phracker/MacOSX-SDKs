//  
//  GCRacingWheelInput.h
//  GameController
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <GameController/GCDevicePhysicalInput.h>

@protocol GCButtonInput;
@protocol GCSwitchInput;
@class GCSteeringWheelElement;
@class GCGearShifterElement;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos)
@interface GCRacingWheelInputState : NSObject <GCDevicePhysicalInputState>

/** The steering wheel element. */
@property (readonly) GCSteeringWheelElement *wheel;

@property (readonly, nullable) id<GCButtonElement> acceleratorPedal;

@property (readonly, nullable) id<GCButtonElement> brakePedal;

@property (readonly, nullable) id<GCButtonElement> clutchPedal;

/**
 The element representing an attached gear shifter accessory.
 
 Note that this element only represents an external gear shifter accessory.
 Many racing wheels have a pair of built in paddle buttons that can be used for
 sequential gear shifting.  Those buttons are can be looked up with the
 \c GCInputLeftPaddle and \c GCInputRightPaddle input names.
 */
@property (readonly, nullable) GCGearShifterElement *shifter;

@end



API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos)
@interface GCRacingWheelInput : GCRacingWheelInputState <GCDevicePhysicalInput>

/**
 Polls the current state vector of the racing wheel input and saves it to a new
 instance.
 */
- (GCRacingWheelInputState *)capture;

- (nullable GCRacingWheelInputState<GCDevicePhysicalInputStateDiff> *)nextInputState;

@end

NS_ASSUME_NONNULL_END
