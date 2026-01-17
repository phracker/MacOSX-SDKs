//  
//  GCControllerInput.h
//  GameController
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <GameController/GCDevicePhysicalInput.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
@interface GCControllerInputState : NSObject <GCDevicePhysicalInputState>
@end


API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
@interface GCControllerLiveInput : GCControllerInputState <GCDevicePhysicalInput>

/**
 *  Get a view of the controller's input without any system-level control
 *  remapping applied.
 *
 *  Developers should avoid implementing their own control remapping
 *  functionality and to instead direct users to the system game controller
 *  settings to remap controls.  If you choose to implement your own
 *  control remapping functionality, or if your app streams controller input
 *  to a remote device that implements control remapping functionality, you
 *  should access controller physical input through this interface.
 */
@property (readonly, nullable) GCControllerLiveInput *unmappedInput;

/* GCDevicePhysicalInput re-declarations with better type information. */
- (GCControllerInputState *)capture;
- (nullable GCControllerInputState<GCDevicePhysicalInputStateDiff> *)nextInputState;

@end

NS_ASSUME_NONNULL_END
