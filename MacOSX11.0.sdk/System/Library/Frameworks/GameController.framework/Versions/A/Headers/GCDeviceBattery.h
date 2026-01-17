//
//  GCDeviceBattery.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <GameController/GCExtern.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 This is the battery status and it's represented by one of the following values:
 GCControllerBatteryStateUnknown means that the current state of battery is unknown or cannot be determined
 GCControllerBatteryStateDischarging means that controller is on battery and discharging at this moment
 GCControllerBatteryStateCharging means that controller is plugged in, but it's battery level is less than 100%
 GCControllerBatteryStateFull means that controller is plugged in and it's battery level is 100%
 */
typedef NS_ENUM(NSInteger, GCDeviceBatteryState) {
    GCDeviceBatteryStateUnknown = -1,
    GCDeviceBatteryStateDischarging,
    GCDeviceBatteryStateCharging,
    GCDeviceBatteryStateFull
} NS_SWIFT_NAME(GCDeviceBattery.State);

/**
 A controller battery is an abstract representation of the battery level and battery status of a GCController instance.
*/
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface GCDeviceBattery : NSObject

/**
 This is the battery level for controller.
 Battery level ranges from 0.0 (fully discharged) to 1.0 (100% charged) and defaults to 0
*/
@property(nonatomic, readonly) float batteryLevel;

/**
 A battery state for controller, defaults to GCControllerBatteryStateUnknown
 
 @note This property might be useful if you display the information about currently connected controller for player's convenience
 */
@property(nonatomic, readonly) GCDeviceBatteryState batteryState;


- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
