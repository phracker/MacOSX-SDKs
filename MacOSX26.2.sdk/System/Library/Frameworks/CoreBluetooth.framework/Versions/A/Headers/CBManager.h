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
 *	@seealso  authorization
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

/*!
 *  @enum CBManagerAuthorization
 *
 *  @discussion Represents the current authorization state of a CBManager.
 *
 *  @constant CBManagerAuthorizationStatusNotDetermined			User has not yet made a choice with regards to this application.
 *  @constant CBManagerAuthorizationStatusRestricted			This application is not authorized to use bluetooth. The user cannot change this application’s status,
 * 																possibly due to active restrictions such as parental controls being in place.
 *  @constant CBManagerAuthorizationStatusDenied				User has explicitly denied this application from using bluetooth.
 *  @constant CBManagerAuthorizationStatusAuthorizedAlways		User has authorized this application to use bluetooth always.
 *
 */
typedef NS_ENUM(NSInteger, CBManagerAuthorization) {
	CBManagerAuthorizationNotDetermined = 0,
	CBManagerAuthorizationRestricted,
	CBManagerAuthorizationDenied,
	CBManagerAuthorizationAllowedAlways
} NS_ENUM_AVAILABLE(10_15, 13_0);

/*!
 *  @property authorization
 *
 *  @discussion The current authorization of the manager, initially set to <code>CBManagerAuthorizationNotDetermined</code>.
 *				Updates are provided by required delegate method {@link managerDidUpdateState:}.
 *  @seealso	state
 */
@property(nonatomic, assign, readonly) CBManagerAuthorization authorization API_DEPRECATED_WITH_REPLACEMENT("CBManager.authorization", ios(13.0,13.1));


/*!
 *  @property authorization
 *
 *  @discussion The current authorization of the manager, initially set to <code>CBManagerAuthorizationNotDetermined</code>.
 *  			You can check this in your implementation of required delegate method {@link managerDidUpdateState:}. You can also use it to check authorization status before allocating CBManager.
 *  @seealso	state
 */
@property(class, nonatomic, assign, readonly) CBManagerAuthorization authorization API_AVAILABLE(macos(10.15), ios(13.1), watchos(6.0), tvos(13.0));

@end
