/*
 * Copyright (c) 2020-2021 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
* @file NEAppPushManager.h
* @discussion This file declares the NEAppPushManager API. The NEAppPushManager API is used to configure and manage a life cycle of NEAppPushProvider.
*
* This API is part of NetworkExtension.framework.
*/

#if defined(__cplusplus)
#define NEAPPPUSH_EXPORT extern "C"
#else
#define NEAPPPUSH_EXPORT extern
#endif

@protocol NEAppPushDelegate;

/*! @const NEAppPushErrorDomain The app push manager error domain */
NEAPPPUSH_EXPORT NSErrorDomain const NEAppPushErrorDomain API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @typedef NEAppPushManagerError
 * @abstract App Push Manager error codes
 */
typedef NS_ERROR_ENUM(NEAppPushErrorDomain, NEAppPushManagerError) {
	/*! @const NEAppPushManagerErrorConfigurationInvalid The app push configuration is invalid */
	NEAppPushManagerErrorConfigurationInvalid = 1,
	/*! @const NEAppPushManagerErrorConfigurationNotLoaded The app push configuration is not loaded */
	NEAppPushManagerErrorConfigurationNotLoaded = 2,
	/*! @const NEAppPushManagerErrorInternalError Internal error in API task handling*/
	NEAppPushManagerErrorInternalError = 3,
	/*! @const NEAppPushManagerErrorInactiveSession This operation is invalid on inactive session */
	NEAppPushManagerErrorInactiveSession = 4,
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @interface NEPrivateLTENetwork
 * @discussion The NEPrivateLTENetwork class declares an object that contains the parameters of a private LTE network.
 */
API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED
@interface NEPrivateLTENetwork : NSObject<NSCopying, NSSecureCoding>

/*!
 * @property mobileCountryCode
 * @discussion Mobile Country Code of the private LTE network.
 */
@property (copy) NSString *mobileCountryCode API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property mobileNetworkCode
 * @discussion Mobile Network Code of the private LTE network.
 */
@property (copy) NSString *mobileNetworkCode API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property trackingAreaCode
 * @discussion Tracking Area Code of the private LTE network. This property is only applicable for band 48 private LTE networks.
 */
@property (copy, nullable) NSString *trackingAreaCode API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

@end

/*!
 * @interface NEAppPushManager
 * @discussion The NEAppPushManager class declares a programmatic interface to configure NEAppPushProvider.
 *
 * NEAppPushManager declares methods and properties for configuring and managing life cycle of app push provider.
 *
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED
@interface NEAppPushManager : NSObject

/*!
 * @property matchSSIDs
 * @discussion An array of Wi-Fi SSID strings. If the SSID string of current Wi-Fi network matches with one of these strings then the NEAppPushProvider
 *	is started. The upper limit of number of SSIDs is 10.
 */
@property (copy) NSArray<NSString *> *matchSSIDs API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property matchPrivateLTENetworks
 * @discussion An array of NEPrivateLTENetwork objects. If the properties of current private LTE network match with properties of one of these NEPrivateLTENetwork objects then the
 * NEAppPushProvider is started. The upper limit of number of private LTE networks is 10. For private LTE networks that are not band 48, the device must be supervised in order to perform the match
 */
@property (copy) NSArray<NEPrivateLTENetwork *> *matchPrivateLTENetworks API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property providerConfiguration
 * @discussion A dictionary containing vendor-specific key-value pairs, where the data type of values must be one of the data types supported by property list. Values of user defined data
 * 	type are not supported. This dictionary is passed as-is to NEAppPushProvider when is it is started or notified for other specified reasons.
 */
@property (copy) NSDictionary<NSString *, id> *providerConfiguration API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property providerBundleIdentifier
 * @discussion A string containing the bundle identifier of the NEAppPushProvider.
 */
@property (copy, nullable) NSString *providerBundleIdentifier API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property delegate
 * @discussion An instance of type NEAppPushDelegate that is required to receive incoming call informarion from the provider.
*/
@property (readwrite, weak, nullable) id<NEAppPushDelegate> delegate;

/*!
 * @method loadAllFromPreferencesWithCompletionHandler:
 * @discussion This class method asynchronously reads all of the saved configurations and returns them as an array of NEAppPushManager objects.
 * @param completionHandler A block that takes an array of NEAppPushManager objects. The array passed to the block may be empty if no configurations
 * 		  were successfully read from the disk. The NSError object passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
+ (void)loadAllFromPreferencesWithCompletionHandler:(void (^)(NSArray<NEAppPushManager *> * __nullable managers, NSError * __nullable error))completionHandler API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;


/*!
 * @method loadFromPreferencesWithCompletionHandler:
 * @discussion This method loads the saved configuration from the persistent store.
 * @param completionHandler A block that will be called when the load operation is completed. The NSError object passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
- (void)loadFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @method removeFromPreferencesWithCompletionHandler:
 * @discussion This method removes the configuration from the persistent store.
 * @param completionHandler A block that will be called when the remove operation is completed. The NSError object passed to this block will be nil if the remove operation succeeded, non-nil otherwise.
 */
- (void)removeFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @method saveToPreferencesWithCompletionHandler:
 * @discussion This method saves the configuration in the persistent store.
 * @param completionHandler A block that will be called when the save operation is completed. The NSError object passed to this block will be nil if the save operation succeeded, non-nil otherwise.
 */
- (void)saveToPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property localizedDescription
 * @discussion A string containing a description of the app push manager.
 */
@property (copy, nullable) NSString *localizedDescription API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property enabled
 * @discussion Toggles the enabled status of the configuration. This property will be set to NO when the same app saves another configuration that overlaps with this configuration.
 */
@property (getter=isEnabled) BOOL enabled API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property active
 * @discussion If set to YES, it indicates the associated configuration is in use. Use KVO to watch for changes.
 */
@property (readonly, getter=isActive) BOOL active API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

@end

/*!
 * @protocol NEAppPushDelegate
 * @discussion Delegate for NEAppPushManager.
*/

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED
@protocol NEAppPushDelegate<NSObject>

@required

/*!
 * @method appPushManager:didReceiveIncomingCallWithUserInfo:userInfo
 * @discussion This delegate method is called when the provider reports incoming call using reportIncomingCommunicationWithUserInfo method.
 * @param userInfo A dictionary of custom information that the provider passes to reportIncomingCommunicationWithUserInfo method.
*/
- (void)appPushManager:(NEAppPushManager *)manager didReceiveIncomingCallWithUserInfo:(NSDictionary *)userInfo API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
