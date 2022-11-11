//
//  CLSDefines.h
//  ClassKit
//
//  Copyright © 2018-2021 Apple Inc. All rights reserved.
//

#ifndef CLSDEFINES_H
#define CLSDEFINES_H

#import <Foundation/Foundation.h>

#if !defined(__cplusplus)
#define CLS_EXTERN extern __attribute__((visibility("default")))
#else
#define CLS_EXTERN extern "C" __attribute__((visibility("default")))
#endif

#if !defined(__cplusplus)
#define CLS_EXTERN_HIDDEN extern __attribute__((visibility("hidden")))
#else
#define CLS_EXTERN_HIDDEN extern "C" __attribute__((visibility("hidden")))
#endif


CLS_EXTERN NSString * const CLSErrorCodeDomain API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @enum      CLSErrorCode

 @constant  CLSErrorCodeNone                         No error.
 @constant  CLSErrorCodeClassKitUnavailable       	 ClassKit is not available on this device.
 @constant  CLSErrorCodeInvalidArgument              An invalid argument was provided to the API.
 @constant  CLSErrorCodeInvalidModification          Attempted to modify a readonly object.
 @constant  CLSErrorCodeAuthorizationDenied          The application is not authorized to perform the requested operation.
 @constant  CLSErrorCodeDatabaseInaccessible         Protected ClassKit is inaccessible because the device is locked.
 @constant  CLSErrorCodeLimits                       Limits exceeded.
 @constant  CLSErrorCodeInvalidCreate                Attempted to save new object that already exists in the data store.
 @constant  CLSErrorCodeInvalidUpdate                Failed to save updated object in the data store.
 @constant  CLSErrorCodePartialFailure               Returned if an operation resulted in a mix of successes and failures.
 @constant  CLSErrorCodeInvalidAccountCredentials    Returned if an operation failed because the user MAID account credentials are invalid.
 */
typedef NS_ERROR_ENUM(CLSErrorCodeDomain, CLSErrorCode) {
    CLSErrorCodeNone = 0,
    CLSErrorCodeClassKitUnavailable,
    CLSErrorCodeInvalidArgument,
    CLSErrorCodeInvalidModification,
    CLSErrorCodeAuthorizationDenied,
    CLSErrorCodeDatabaseInaccessible,
    CLSErrorCodeLimits,
    CLSErrorCodeInvalidCreate,
    CLSErrorCodeInvalidUpdate,
    CLSErrorCodePartialFailure,
    CLSErrorCodeInvalidAccountCredentials API_AVAILABLE(ios(15.1), macos(12.0), macCatalyst(15.1)) API_UNAVAILABLE(watchos, tvos)
} API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

typedef NSString * CLSErrorUserInfoKey NS_EXTENSIBLE_STRING_ENUM API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract   Any object that caused a failure will be available in - [NSError userInfo]; under this key.
 */
CLS_EXTERN CLSErrorUserInfoKey const CLSErrorObjectKey API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract   If multiple objects cause errors we return an error with code `CLSErrorCodePartialFailure` which will contain an array of errors in - [NSError userInfo]; under this key.
 */
CLS_EXTERN CLSErrorUserInfoKey const CLSErrorUnderlyingErrorsKey API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract   Errors with the code `CLSErrorCodePartialFailure` may contain an array of successful entities in - [NSError userInfo]; under this key.
 */
CLS_EXTERN CLSErrorUserInfoKey const CLSErrorSuccessfulObjectsKey API_AVAILABLE(ios(15.0), macos(12.0), macCatalyst(15.0)) API_UNAVAILABLE(watchos, tvos);

typedef NSString * CLSPredicateKeyPath NS_EXTENSIBLE_STRING_ENUM API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

CLS_EXTERN CLSPredicateKeyPath const CLSPredicateKeyPathDateCreated API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSPredicateKeyPath const CLSPredicateKeyPathIdentifier API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSPredicateKeyPath const CLSPredicateKeyPathTitle API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSPredicateKeyPath const CLSPredicateKeyPathUniversalLinkURL API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSPredicateKeyPath const CLSPredicateKeyPathTopic API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);
CLS_EXTERN CLSPredicateKeyPath const CLSPredicateKeyPathParent API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

#endif // CLSDEFINES_H
