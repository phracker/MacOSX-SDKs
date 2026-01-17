/*
 * Copyright (c) 2019 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEDNSSettingsManager.h
 * @discussion This file declares the NEDNSSettingsManager API. The NEDNSSettingsManager API is used to directly configure DNS settings on the system.
 *
 * This API is part of NetworkExtension.framework.
 *
 * This API is used to configure DNS settings on the system.  On Demand rules can be used to specify when the configuration should take effect.
 */

#if defined(__cplusplus)
#define NEDNSSETTINGS_EXPORT extern "C"
#else
#define NEDNSSETTINGS_EXPORT extern
#endif

@class NEDNSSettings;
@class NEOnDemandRule;

/*!
 * @typedef NEDNSSettingsManagerError
 * @abstract DNS Settings Manager error codes
 */
typedef NS_ENUM(NSInteger, NEDNSSettingsManagerError) {
	/*! @const NEDNSSettingsManagerErrorConfigurationInvalid The DNS settings manager is invalid */
	NEDNSSettingsManagerErrorConfigurationInvalid = 1,
	/*! @const NEDNSSettingsManagerErrorConfigurationDisabled The DNS settings manager is not enabled. */
	NEDNSSettingsManagerErrorConfigurationDisabled = 2,
	/*! @const NEDNSSettingsManagerErrorConfigurationStale The DNS settings manager needs to be loaded. */
	NEDNSSettingsManagerErrorConfigurationStale = 3,
	/*! @const NEDNSSettingsManagerErrorConfigurationCannotBeRemoved The DNS settings manager cannot be removed. */
	NEDNSSettingsManagerErrorConfigurationCannotBeRemoved = 4,
} API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(watchos, tvos);

/*! @const NEDNSSettingsManagerErrorDomain The DNS settings error domain */
NEDNSSETTINGS_EXPORT NSString * const NEDNSSettingsErrorDomain API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(watchos, tvos);

/*! @const NEDNSSettingsConfigurationDidChangeNotification Name of the NSNotification that is posted when the DNS settings configuration changes. */
NEDNSSETTINGS_EXPORT NSString * const NEDNSSettingsConfigurationDidChangeNotification API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @interface NEDNSSettingsManager
 * @discussion The NEDNSSettingsManager class declares the programmatic interface for an object that manages DNS settings configurations.
 *
 * NEDNSSettingsManager declares methods and properties for configuring and controlling DNS settings on the system.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEDNSSettingsManager : NSObject

/*!
 * @method sharedManager
 * @return The singleton NEDNSSettingsManager object for the calling process.
 */
+ (NEDNSSettingsManager *)sharedManager API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method loadFromPreferencesWithCompletionHandler:
 * @discussion This function loads the current DNS settings configuration from the caller's DNS settings preferences.
 * @param completionHandler A block that will be called when the load operation is completed. The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
- (void)loadFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method removeFromPreferencesWithCompletionHandler:
 * @discussion This function removes the DNS settings configuration from the caller's DNS settings preferences. If the DNS settings are enabled, the DNS settings becomes disabled.
 * @param completionHandler A block that will be called when the remove operation is completed. The NSError passed to this block will be nil if the remove operation succeeded, non-nil otherwise.
 */
- (void)removeFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method saveToPreferencesWithCompletionHandler:
 * @discussion This function saves the DNS settingsconfiguration in the caller's DNS settings preferences. If the DNS settings are enabled, they will become active.
 * @param completionHandler A block that will be called when the save operation is completed. The NSError passed to this block will be nil if the save operation succeeded, non-nil otherwise.
 */
- (void)saveToPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property localizedDescription
 * @discussion A string containing a description of the DNS settings.
 */
@property (copy, nullable) NSString *localizedDescription API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property dnsSettings
 * @discussion An NEDNSSettings object containing the DNS resolver configuration to apply to the system.
 */
@property (strong, nullable) NEDNSSettings *dnsSettings API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property onDemandRules
 * @discussion An array of NEOnDemandRule objects. If nil, the associated DNS settings will always apply. If non-nil, the array describes the networks on which the DNS configuration should take effect or not.
 */
@property (copy, nullable) NSArray<NEOnDemandRule *> *onDemandRules API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property enabled
 * @discussion Checks the enabled status of the DNS settings. DNS settings must be enabled by the user in Settings or System Preferences.
 */
@property (readonly, getter=isEnabled) BOOL enabled API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

