/*
	Copyright (C) 2020 Apple Inc. All Rights Reserved.
*/

#pragma once

#ifndef EXPOSURE_NOTIFICATION_INDIRECT_INCLUDES
#error "Please #import <ExposureNotification/ExposureNotification.h> instead of this file directly."
#endif

#import <ExposureNotification/ENCommon.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class ENExposureConfiguration;
@class ENExposureDetectionSummary;
@class ENExposureInfo;

//===========================================================================================================================
/*!	@brief	Overall status of Exposure Notification on the system.
*/
typedef NS_ENUM( NSInteger, ENStatus )
{
	/// Status of Exposure Notification is unknown. This is the status before ENManager has activated successfully.
	ENStatusUnknown			= 0,
	
	/// Exposure Notification is active on the system.
	ENStatusActive			= 1,
	
	/// Exposure Notification is disabled. setExposureNotificationEnabled:completionHandler can be used to enable it.
	ENStatusDisabled		= 2,
	
	/// Bluetooth has been turned off on the system. Bluetooth is required for Exposure Notification.
	/// Note: this may not match the state of Bluetooth as reported by CoreBluetooth.
	/// Exposure Notification is a system service and can use Bluetooth in situations when apps cannot.
	/// So for the purposes of Exposure Notification, it's better to use this API instead of CoreBluetooth.
	ENStatusBluetoothOff	= 3,
	
	/// Exposure Notification is not active due to system restrictions, such as parental controls.
	/// When in this state, the app cannot enable Exposure Notification.
	ENStatusRestricted		= 4,
	
	/// For future use. Not returned by any APIs yet.
	ENStatusPaused			= 5,

	/// Exposure Notification is not available due to insufficient authorization.
	ENStatusUnauthorized	= 6,
	
}	EN_API_AVAILABLE;

//===========================================================================================================================
/*!	@brief	Activities that occurred while the app might not be running.
*/
typedef NS_OPTIONS( uint32_t, ENActivityFlags )
{
	/// Reserved field
	ENActivityFlagsReserved1							     = ( 1U << 0 ),
	
	/// Reserved field
	ENActivityFlagsReserved2							     = ( 1U << 1 ),
	
	/// The app launched in the background to perform periodic operations on iOS 12.5.
	ENActivityFlagsPeriodicRun      						 = ( 1U << 2 ),
	
	/// The app launched in the foreground to display information about the pre-authorized key release
	ENActivityFlagsPreAuthorizedKeyReleaseNotificationTapped = ( 1U << 3 )
	
}	EN_API_AVAILABLE_V2;

//===========================================================================================================================

/// Invoked after the app is launched to report activities that occurred while the app might not be running.
EN_API_AVAILABLE_V2
typedef void ( ^ENActivityHandler )( ENActivityFlags activityFlags );

/// Invoked when getDiagnosisKeysWithCompletionHandler completes.
/// If it completes successfully, keys will contain the Diagnosis Keys for this device and error will be nil.
/// If it fails, keys will be nil and error indicates the reason it failed.
EN_API_AVAILABLE
typedef void ( ^ENGetDiagnosisKeysHandler )( NSArray <ENTemporaryExposureKey *> * _Nullable keys, NSError * _Nullable error );

/// Invoked when detecting exposures completes. It provides a summary of exposures.
/// If it completes successfully, summary will contain a summary of exposures and error will be nil.
/// If it fails, summary will be nil and error indicates the reason it failed.
EN_API_AVAILABLE
typedef void ( ^ENDetectExposuresHandler )( ENExposureDetectionSummary * _Nullable summary, NSError * _Nullable error );

// Invoked after requestPreAuthorizedDiagnosisKeys if the user pre-authorized
EN_API_AVAILABLE_V3
typedef void ( ^ENDiagnosisKeysAvailableHandler )( NSArray <ENTemporaryExposureKey *> *keys );

/// Invoked when getting exposures completes. It provides info about each exposure.
/// If it completes successfully, exposures will contain info about each exposure and error will be nil.
/// If it fails, exposures will be nil and error indicates the reason it failed.
EN_API_AVAILABLE
typedef void ( ^ENGetExposureInfoHandler )( NSArray <ENExposureInfo *> * _Nullable exposures, NSError * _Nullable error );

/// Invoked when getExposureWindows completes. It provides info about each exposure window.
/// If it completes successfully, exposureWindows will non-nil and error will be nil.
/// If it fails, exposureWindows will be nil and error indicates the reason it failed.
EN_API_AVAILABLE_V2
typedef void ( ^ENGetExposureWindowsHandler )( NSArray <ENExposureWindow *> * _Nullable exposureWindows, NSError * _Nullable error );

/// Invoked when getUserTraveled completes.
EN_API_AVAILABLE_V2
typedef void ( ^ENGetUserTraveledHandler )( BOOL traveled, NSError * _Nullable error );

//===========================================================================================================================
/*!	@brief	Manages Exposure Notification functionality.
*/
EN_API_AVAILABLE_EXPORT
@interface ENManager : NSObject

// MARK: == General ==

//---------------------------------------------------------------------------------------------------------------------------
/*!	@defgroup	General
	
	Before an instance of this class can be used, activateWithCompletionHandler must be called. If that completes 
	successfully, the remaining properties and methods on the class can be used. Note activating this object doesn't
	enable Exposure Notification. It only allows this object to be used. Once activated, Exposure Notification can be 
	enabled with setExposureNotificationEnabled:completionHandler, if needed.
	
	If the app no longer needs an instance of this class, invalidate must be called. This stops any outstanding operations
	and causes the invalidation handler to be invoked.
	
	Note: invalidation is asynchronous so it's possible for handlers to be invoked after calling invalidate. 
	The invalidation handler will be invoked when invalidation has finished. No handlers will be invoked after that.
	The invalidation handler will be invoked exactly once even if invalidate is called multiple times.
	Once invalidate is called, the object cannot be reused. A new object must be created for subsequent use.
	
	All strong references are cleared when invalidation completes to break potential retain cycles.
	You don't need to use weak references within your handlers to avoid retain cycles when using this class.
*/

/// Invoked when the app is launched for an activity while it might not be running.
/// When the app is launched, it should create an ENManager instance, set this handler, and then activate the manager.
@property (readwrite, copy, nullable, nonatomic) ENActivityHandler activityHandler EN_API_AVAILABLE_V2;

/// Dispatch queue to invoke handlers on. Defaults to the main queue.
#if defined( OS_OBJECT_USE_OBJC ) && OS_OBJECT_USE_OBJC
@property (readwrite, strong, nonatomic) dispatch_queue_t dispatchQueue;
#endif

/// Overall status of Exposure Notification. KVO may be used to monitor for changes.
@property (readonly, assign, nonatomic) ENStatus exposureNotificationStatus;

/// Invoked exactly once when invalidation completes. This property is cleared before it's invoked to break retain cycles.
@property (readwrite, copy, nullable, nonatomic) dispatch_block_t invalidationHandler;

/// Activates the object to prepare it for use. Properties may not be usable until the completion handler reports success.
- (void) activateWithCompletionHandler:(ENErrorHandler) completionHandler;

/// Stops any outstanding operations and invalidates this object. Once this is called, the object can no longer be used.
/// To start using ENManager again, a new instance of the class must be created and activated.
- (void) invalidate;

/// Reports if the user traveled within an exposure period (e.g. 14 days).
- (void) getUserTraveledWithCompletionHandler:(ENGetUserTraveledHandler) completionHandler
EN_API_AVAILABLE_V2;

// MARK: == Authorization ==

//---------------------------------------------------------------------------------------------------------------------------
/*!	@defgroup	Authorization
	
	Before Exposure Notification can be enabled by the app, the user must consent and give permission to the app.
	When the app first starts using Exposure Notification functionality, such as enabling it, the user will be prompted
	by the system to ask for permission. If the user grants permission, the API can be used normally. If the user denies
	the app, Exposure Notification APIs will return ENErrorCodeNotAuthorized.
*/

/// Reports the current authorization status of the app.
/// Apps can use this property to preflight authorization in order to determine if the user will be prompted.
@property (class, readonly, assign, nonatomic) ENAuthorizationStatus authorizationStatus;

// MARK: == Settings ==

//---------------------------------------------------------------------------------------------------------------------------
/*!	@defgroup	Settings
	
	This allows the app to determine and change settings related to Exposure Notification.
*/

/// Indicates if Exposure Notification is enabled on the system. KVO may be used to monitor for changes.
/// This will be NO until activateWithCompletionHandler has completed successfully.
/// Note that even if it's enabled, it may be inactive for other reasons, such as Bluetooth being turned off.
/// The exposureNotificationStatus property can be monitored for the overall status of Exposure Notification.
@property (readonly, assign, nonatomic) BOOL exposureNotificationEnabled;

/// Enables or disables Exposure Notification.
/// If not previously authorized, this shows a user dialog for consent to enable Exposure Notification.
/// Note: Disabling stops Bluetooth advertising and scanning related to Exposure Notification, but the 
/// Diagnosis Keys and data will remain.
- (void) setExposureNotificationEnabled:(BOOL) enabled completionHandler:(ENErrorHandler) completionHandler;

// MARK: == Exposure Detection ==

//---------------------------------------------------------------------------------------------------------------------------
/*!	@defgroup	Exposure Detection
	
	This allows an app to supply positive diagnosis keys from a server and a configuration to detect exposure.
*/

/// Detects exposures using the specified configuration to control the scoring algorithm.
/// This uses the diagnosis keys already known to the system.
/// Only available to apps with ENAPIVersion 2 or higher.
- (NSProgress *)
	detectExposuresWithConfiguration:	(ENExposureConfiguration *) configuration
	completionHandler:					(ENDetectExposuresHandler)	completionHandler
EN_API_AVAILABLE_V2
NS_SWIFT_NAME(detectExposures(configuration:completionHandler:));

/// Detects exposures using the specified configuration to control the scoring algorithm and URLs to specify the 
/// files containing diagnosis keys the app has downloaded. The diagnosis key files must be signed appropriately.
/// When the app's ENAPIVersion is 2 or higher, keys already known to the system are included in the analysis.
- (NSProgress *)
	detectExposuresWithConfiguration:	(ENExposureConfiguration *) configuration
	diagnosisKeyURLs:					(NSArray <NSURL *> *)		diagnosisKeyURLs
	completionHandler:					(ENDetectExposuresHandler)	completionHandler
NS_SWIFT_NAME(detectExposures(configuration:diagnosisKeyURLs:completionHandler:));

/// Gets info about each exposure from the summary provided when exposure detection completes.
/// Using this API will inform the user that their exposure details have been revealed to the app.
/// The user explanation string will be displayed as part of the UI to inform the user of using this API.
- (NSProgress *)
	getExposureInfoFromSummary:	(ENExposureDetectionSummary *)	summary
	userExplanation:			(NSString *)					userExplanation
	completionHandler:			(ENGetExposureInfoHandler)		completionHandler
API_DEPRECATED( "Use getExposureWindowsFromSummary, if needed.", ios( 13.5, 13.6 ) )
NS_SWIFT_NAME(getExposureInfo(summary:userExplanation:completionHandler:));

/// Gets info about each exposure window from the summary provided when exposure detection completes.
- (NSProgress *)
	getExposureWindowsFromSummary:	(ENExposureDetectionSummary *)	summary
	completionHandler:				(ENGetExposureWindowsHandler)	completionHandler
EN_API_AVAILABLE_V2
NS_SWIFT_NAME(getExposureWindows(summary:completionHandler:));

// MARK: == Diagnosis Keys and Data ==

//---------------------------------------------------------------------------------------------------------------------------
/*!	@defgroup	Diagnosis Keys and Data
	
	If a user has a positive diagnosis, they have the option to upload their keys to allow other users to determine if 
	they may have been exposed. This should only be used after proper verification is performed and after the user has 
	agreed to share this information.
*/

/// Requests the temporary exposure keys used by this device to share with a server.
/// Each use of this API will present the user with system UI to authorize it.
- (void) getDiagnosisKeysWithCompletionHandler:(ENGetDiagnosisKeysHandler) completionHandler;

/// Requests the temporary exposure keys, including the current key, used by this device for testing.
/// Each use of this API will present the user with system UI to authorize it.
/// WARNING: This API is only for use by developers. It requires a special entitlement that is not allowed in the app store.
/// It's only intended to allow developers to test without needing to wait 24 hours for a key to be released.
- (void) getTestDiagnosisKeysWithCompletionHandler:(ENGetDiagnosisKeysHandler) completionHandler;

/// Invoked after requestPreAuthorizedDiagnosisKeys if user authorization is still valid.
@property (readwrite, copy, nullable, nonatomic) ENDiagnosisKeysAvailableHandler diagnosisKeysAvailableHandler
EN_API_AVAILABLE_V3;

/// Authorizes a one-time, future release of diagnosis keys without a user prompt at the time of release.
/// This allows the user to authorize ahead of time in case they are unable to approve at the time of positive diagnosis.
/// WARNING: Application should be in foreground to request the authorization
- (void) preAuthorizeDiagnosisKeysWithCompletionHandler:(ENErrorHandler) completionHandler
EN_API_AVAILABLE_V3;

/// Requests diagnosis keys after previously using preAuthorizeDiagnosisKeys successfully.
/// This will display a notification to the user for the user to know the keys will be returned.
/// Keys are returned by invoking diagnosisKeysAvailable, which must be set before calling this.
- (void) requestPreAuthorizedDiagnosisKeysWithCompletionHandler:(ENErrorHandler) completionHandler
EN_API_AVAILABLE_V3;

@end

NS_ASSUME_NONNULL_END
