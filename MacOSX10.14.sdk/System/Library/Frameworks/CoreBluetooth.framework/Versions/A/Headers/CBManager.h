/*
 *	@file CBManager.h
 *	@framework CoreBluetooth
 *
 *  @discussion Entry point to the central role.
 *
 *	@copyright 2016 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>
#import <Foundation/Foundation.h>

NS_CLASS_AVAILABLE(10_13, 10_0)
CB_EXTERN_CLASS @interface CBManager : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 *  @enum CBManagerState
 *
 *  @discussion Represents the current state of a CBManager.
 *
 *  @constant CBManagerStateUnknown       State unknown, update imminent.
 *  @constant CBManagerStateResetting     The connection with the system service was momentarily lost, update imminent.
 *  @constant CBManagerStateUnsupported   The platform doesn't support the Bluetooth Low Energy Central/Client role.
 *  @constant CBManagerStateUnauthorized  The application is not authorized to use the Bluetooth Low Energy role.
 *  @constant CBManagerStatePoweredOff    Bluetooth is currently powered off.
 *  @constant CBManagerStatePoweredOn     Bluetooth is currently powered on and available to use.
 *
 */
typedef NS_ENUM(NSInteger, CBManagerState) {
	CBManagerStateUnknown = 0,
	CBManagerStateResetting,
	CBManagerStateUnsupported,
	CBManagerStateUnauthorized,
	CBManagerStatePoweredOff,
	CBManagerStatePoweredOn,
} NS_ENUM_AVAILABLE(10_13, 10_0);

/*!
 *  @property state
 *
 *  @discussion The current state of the manager, initially set to <code>CBManagerStateUnknown</code>.
 *				Updates are provided by required delegate method {@link managerDidUpdateState:}.
 *
 */
@property(nonatomic, assign, readonly) CBManagerState state;

@end
