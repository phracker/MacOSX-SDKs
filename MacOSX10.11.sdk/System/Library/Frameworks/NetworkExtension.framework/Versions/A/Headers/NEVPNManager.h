/*
 * Copyright (c) 2013-2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

/*!
 * @file NEVPNManager.h
 * @discussion This file declares the NEVPNManager API. The NEVPNManager API is used to configure and control Virtual Private Network (VPN) tunnels.
 *
 * This API is part of NetworkExtension.framework.
 *
 * This API is used to create VPN configurations. The VPN tunnel can be started manually, or On Demand rules can be created that will start the VPN tunnel automatically when specific network events occur.
 */

#if !TARGET_OS_IPHONE && !TARGET_IPHONE_SIMULATOR
#import <Security/Security.h>
#endif

NS_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
#define NEVPN_EXPORT extern "C"
#else
#define NEVPN_EXPORT extern
#endif

@class NEVPNConnection;
@class NEVPNProtocol;
@class NEOnDemandRule;

/*!
 * @typedef NEVPNError
 * @abstract VPN error codes
 */
typedef NS_ENUM(NSInteger, NEVPNError) {
    /*! @const NEVPNErrorConfigurationInvalid The VPN configuration is invalid */
    NEVPNErrorConfigurationInvalid = 1,
    /*! @const NEVPNErrorConfigurationDisabled The VPN configuration is not enabled. */
    NEVPNErrorConfigurationDisabled = 2,
    /*! @const NEVPNErrorConnectionFailed The connection to the VPN server failed. */
    NEVPNErrorConnectionFailed = 3,
    /*! @const NEVPNErrorConfigurationStale The VPN configuration is stale and needs to be loaded. */
    NEVPNErrorConfigurationStale = 4,
    /*! @const NEVPNErrorConfigurationReadWriteFailed The VPN configuration cannot be read from or written to disk. */
    NEVPNErrorConfigurationReadWriteFailed = 5,
    /*! @const NEVPNErrorConfigurationUnknown An unknown configuration error occurred. */
    NEVPNErrorConfigurationUnknown = 6,
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*! @const NEVPNErrorDomain The VPN error domain */
NEVPN_EXPORT NSString * const NEVPNErrorDomain NS_AVAILABLE(10_10, 8_0);

/*! @const NEVPNConfigurationChangeNotification Name of the NSNotification that is posted when the VPN configuration changes. */
NEVPN_EXPORT NSString * const NEVPNConfigurationChangeNotification NS_AVAILABLE(10_10, 8_0);

/*!
 * @interface NEVPNManager
 * @discussion The NEVPNManager class declares the programmatic interface for an object that manages Virtual Private Network (VPN) configurations.
 *
 * NEVPNManager declares methods and properties for configuring and controlling a VPN.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NEVPNManager : NSObject

/*!
 * @method sharedManager
 * @return The singleton NEVPNManager object for the calling process.
 */
+ (NEVPNManager *)sharedManager NS_AVAILABLE(10_10, 8_0);

/*!
 * @method loadFromPreferencesWithCompletionHandler:
 * @discussion This function loads the current VPN configuration from the caller's VPN preferences.
 * @param completionHandler A block that will be called on the main thread when the load operation is completed. The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
- (void)loadFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 8_0);

/*!
 * @method removeFromPreferencesWithCompletionHandler:
 * @discussion This function removes the VPN configuration from the caller's VPN preferences. If the VPN is enabled, has VPN On Demand enabled, and has VPN On Demand rules, the VPN is disabled and the VPN On Demand rules are de-activated.
 * @param completionHandler A block that will be called on the main thread when the remove operation is completed. The NSError passed to this block will be nil if the remove operation succeeded, non-nil otherwise.
 */
- (void)removeFromPreferencesWithCompletionHandler:(nullable void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 8_0);

/*!
 * @method saveToPreferencesWithCompletionHandler:
 * @discussion This function saves the VPN configuration in the caller's VPN preferences. If the VPN is enabled, has VPN On Demand enabled, and has VPN On Demand rules, the VPN On Demand rules are activated.
 *
 * @param completionHandler A block that will be called on the main thread when the save operation is completed. The NSError passed to this block will be nil if the save operation succeeded, non-nil otherwise.
 */
- (void)saveToPreferencesWithCompletionHandler:(nullable void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 8_0);

#if !TARGET_OS_IPHONE && !TARGET_IPHONE_SIMULATOR
/*!
 * @method setAuthorization:
 * @discussion This function sets an authorization object that can be used to obtain the authorization rights necessary to modify the system VPN configuration.
 * @param authorization The AuthorizationRef to use to obtain rights.
 */
- (void)setAuthorization:(AuthorizationRef)authorization NS_AVAILABLE(10_10, NA);
#endif

/*!
 * @property onDemandRules
 * @discussion An array of NEOnDemandRule objects.
 */
@property (copy, nullable) NSArray<NEOnDemandRule *> *onDemandRules NS_AVAILABLE(10_10, 8_0);

/*!
 * @property onDemandEnabled
 * @discussion Toggles VPN On Demand.
 */
@property (getter=isOnDemandEnabled) BOOL onDemandEnabled NS_AVAILABLE(10_10, 8_0);

/*!
 * @property localizedDescription
 * @discussion A string containing a description of the VPN.
 */
@property (copy, nullable) NSString *localizedDescription NS_AVAILABLE(10_10, 8_0);

/*!
 * @property protocol
 * @discussion An NEVPNProtocol object containing the protocol-specific portion of the VPN configuration.
 */
@property (strong, nullable) NEVPNProtocol *protocol NS_DEPRECATED(10_10, 10_11, 8_0, 9_0, "Use protocolConfiguration instead");

/*!
 * @property protocolConfiguration
 * @discussion An NEVPNProtocol object containing the protocol-specific portion of the VPN configuration.
 */
@property (strong, nullable) NEVPNProtocol *protocolConfiguration NS_AVAILABLE(10_11, 9_0);

/*!
 * @property connection
 * @discussion The NEVPNConnection object used for controlling the VPN tunnel.
 */
@property (readonly) NEVPNConnection *connection NS_AVAILABLE(10_10, 8_0);

/*!
 * @property enabled
 * @discussion Toggles the enabled status of the VPN. Setting this property will disable VPN configurations of other apps. This property will be set to NO  when other VPN configurations are enabled.
 */
@property (getter=isEnabled) BOOL enabled NS_AVAILABLE(10_10, 8_0);

@end

NS_ASSUME_NONNULL_END

