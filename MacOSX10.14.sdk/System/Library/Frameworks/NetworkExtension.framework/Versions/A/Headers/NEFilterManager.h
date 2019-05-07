/*
 * Copyright (c) 2013-2015, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEFilterManager.h
 * @discussion This file declares the NEFilterManager API. The NEFilterManager API is used to configure and control content filtering services.
 *
 * This API is part of NetworkExtension.framework.
 *
 * This API is used to create filter configurations.
 */

#if defined(__cplusplus)
#define NEFILTER_EXPORT extern "C"
#else
#define NEFILTER_EXPORT extern
#endif

@class NEFilterProviderConfiguration;

/*!
 * @typedef NEFilterError
 * @abstract Filter error codes
 */
typedef NS_ENUM(NSInteger, NEFilterManagerError) {
	/*! @const NEFilterManagerErrorConfigurationInvalid The filter configuration is invalid */
	NEFilterManagerErrorConfigurationInvalid = 1,
	/*! @const NEFilterManagerErrorConfigurationDisabled The filter configuration is not enabled. */
	NEFilterManagerErrorConfigurationDisabled = 2,
	/*! @const NEFilterManagerErrorConfigurationStale The filter configuration needs to be loaded. */
	NEFilterManagerErrorConfigurationStale = 3,
	/*! @const NEFilterManagerErrorConfigurationCannotBeRemoved The filter configuration cannot be removed. */
	NEFilterManagerErrorConfigurationCannotBeRemoved = 4,
} API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*! @const NEFilterErrorDomain The filter error domain */
NEFILTER_EXPORT NSString * const NEFilterErrorDomain API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*! @const NEFilterConfigurationDidChangeNotification Name of the NSNotification that is posted when the filter configuration changes. */
NEFILTER_EXPORT NSString * const NEFilterConfigurationDidChangeNotification API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @interface NEFilterManager
 * @discussion The NEFilterManager class declares the programmatic interface for an object that manages content filtering configurations.
 *
 * NEFilterManager declares methods and properties for configuring and controlling a filter.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEFilterManager : NSObject

/*!
 * @method sharedManager
 * @return The singleton NEFilterManager object for the calling process.
 */
+ (NEFilterManager *)sharedManager API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method loadFromPreferencesWithCompletionHandler:
 * @discussion This function loads the current filter configuration from the caller's filter preferences.
 * @param completionHandler A block that will be called when the load operation is completed. The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
- (void)loadFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method removeFromPreferencesWithCompletionHandler:
 * @discussion This function removes the filter configuration from the caller's filter preferences. If the filter is enabled, the filter becomes disabled.
 * @param completionHandler A block that will be called when the remove operation is completed. The NSError passed to this block will be nil if the remove operation succeeded, non-nil otherwise.
 */
- (void)removeFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method saveToPreferencesWithCompletionHandler:
 * @discussion This function saves the filter configuration in the caller's filter preferences. If the filter is enabled, it will become active.
 * @param completionHandler A block that will be called when the save operation is completed. The NSError passed to this block will be nil if the save operation succeeded, non-nil otherwise.
 */
- (void)saveToPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property localizedDescription
 * @discussion A string containing a description of the filter.
 */
@property (copy, nullable) NSString *localizedDescription API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property providerConfiguration
 * @discussion An NEFilterProviderConfiguration object containing the provider-specific portion of the filter configuration.
 */
@property (strong, nullable) NEFilterProviderConfiguration *providerConfiguration API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property enabled
 * @discussion Toggles the enabled status of the filter. Setting this property will disable filter configurations of other apps. This property will be set to NO when other filter configurations are enabled.
 */
@property (getter=isEnabled) BOOL enabled API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

