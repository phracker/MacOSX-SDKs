//
//  HKDefines.h
//  HealthKit
//
//  Copyright (c) 2013-2025 Apple Inc. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

#if !defined(__cplusplus)
#define HK_EXTERN extern __attribute__((visibility("default")))
#else
#define HK_EXTERN extern "C" __attribute__((visibility("default")))
#endif

HK_EXTERN NSString * const HKErrorDomain API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @enum      HKErrorCode

 @constant  HKUnknownError                      Unknown error.
 @constant  HKErrorHealthDataUnavailable        HealthKit is not available on this device.
 @constant  HKErrorHealthDataRestricted         HealthKit is restricted on this device.
 @constant  HKErrorInvalidArgument              An invalid argument was provided to the API.
 @constant  HKErrorAuthorizationDenied          The application is not authorized to perform the requested operation.
 @constant  HKErrorAuthorizationNotDetermined   The user has not yet chosen whether the application is authorized to
                                                perform the requested operation.
 @constant  HKErrorDatabaseInaccessible         Protected health data is inaccessible because the device is locked.
 @constant  HKErrorUserCanceled                 The user canceled the operation.
 @constant  HKErrorAnotherWorkoutSessionStarted Another primary workout session has started or is already ongoing by this or another application.
 @constant  HKErrorUserExitedWorkoutSession     User exited the application while a workout session was running.
 @constant  HKErrorRequiredAuthorizationDenied  The user has not granted the application authorization to access
                                                required data types.
 @constant  HKErrorNoData                       No data is available for the requested query and predicate, and so the
                                                query's result could not be meaningfully computed.
 @constant  HKErrorWorkoutActivityNotAllowed    A workout session is not allowed to be created for the activity type.
 @constant  HKErrorDataSizeExceeded             The provided data's size exceeds the maximum allowed.
 @constant  HKErrorBackgroundWorkoutSessionNotAllowed   A workout session is not allowed to start or prepare when this app is in the background.
 @constant  HKErrorNotPermissibleForGuestUserMode   Protected Health data changes are not allowed in Guest User mode on visionOS.
 */
typedef NS_ENUM(NSInteger, HKErrorCode) {
    HKUnknownError = 0,
    HKNoError API_DEPRECATED_WITH_REPLACEMENT("HKUnknownError", ios(8.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED)) = HKUnknownError,
    HKErrorHealthDataUnavailable = 1,
    HKErrorHealthDataRestricted,
    HKErrorInvalidArgument,
    HKErrorAuthorizationDenied,
    HKErrorAuthorizationNotDetermined,
    HKErrorDatabaseInaccessible,
    HKErrorUserCanceled,
    HKErrorAnotherWorkoutSessionStarted         API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0)),
    HKErrorUserExitedWorkoutSession             API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0)),
    HKErrorRequiredAuthorizationDenied          API_AVAILABLE(ios(12.0), watchos(5.0), macCatalyst(13.0), macos(13.0)),
    HKErrorNoData                               API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0)),
    HKErrorWorkoutActivityNotAllowed            API_AVAILABLE(ios(17.0), watchos(10.0), macCatalyst(17.0), macos(14.0)),
    HKErrorDataSizeExceeded                     API_AVAILABLE(ios(17.0), watchos(10.0), macCatalyst(17.0), macos(14.0)),
    HKErrorBackgroundWorkoutSessionNotAllowed   API_AVAILABLE(ios(17.0), watchos(10.0), macCatalyst(17.0), macos(14.0)),
    HKErrorNotPermissibleForGuestUserMode       API_AVAILABLE(ios(18.0), visionos(2.0)),
} API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @enum      HKUpdateFrequency
 */
typedef NS_ENUM(NSInteger, HKUpdateFrequency) {
    HKUpdateFrequencyImmediate = 1,
    HKUpdateFrequencyHourly,
    HKUpdateFrequencyDaily,
    HKUpdateFrequencyWeekly,
} API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @enum      HKAuthorizationStatus
 @abstract  This enumerated type is used to indicate the currently granted authorization status for a specific
            HKObjectType.

 @constant  HKAuthorizationStatusNotDetermined      The user has not yet made a choice regarding whether this
                                                    application may save objects of the specified type.
 @constant  HKAuthorizationStatusSharingDenied      This application is not allowed to save objects of the specified type.
 @constant  HKAuthorizationStatusSharingAuthorized  This application is authorized to save objects of the specified type.
 */
typedef NS_ENUM(NSInteger, HKAuthorizationStatus) {
    HKAuthorizationStatusNotDetermined = 0,
    HKAuthorizationStatusSharingDenied,
    HKAuthorizationStatusSharingAuthorized,
} API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

/*!
 @enum      HKAuthorizationRequestStatus
 @abstract  This enumerated type is used to indicate whether it is necessary to request authorization from the user.

 @constant  HKAuthorizationRequestStatusUnknown         The authorization request status could not be determined because
                                                        an error occurred.
 @constant  HKAuthorizationRequestStatusShouldRequest   The application should request authorization from the user.
 @constant  HKAuthorizationRequestStatusUnnecessary     Requesting authorization from the user is unnecessary.
 */
typedef NS_ENUM(NSInteger, HKAuthorizationRequestStatus) {
    HKAuthorizationRequestStatusUnknown = 0,
    HKAuthorizationRequestStatusShouldRequest,
    HKAuthorizationRequestStatusUnnecessary,
} API_AVAILABLE(ios(12.0), watchos(5.0), macCatalyst(13.0), macos(13.0));

/// Returns the set of `HKCategoryValueSleepAnalysis` values that are considered to be asleep.
HK_EXTERN NSSet<NSNumber *> * HKCategoryValueSleepAnalysisAsleepValues(void) API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0)) NS_REFINED_FOR_SWIFT;

NS_ASSUME_NONNULL_END

#import <HealthKit/HKCategoryValues.h>
#import <HealthKit/HKCharacteristicValues.h>
