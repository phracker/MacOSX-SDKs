//
//  SAError.h
//  SafetyKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

SA_EXTERN NSErrorDomain SAErrorDomain API_AVAILABLE(ios(16.0), macos(13.0), watchos(10.1)) API_UNAVAILABLE(tvos);

/*!
 @enum      SAErrorCode

 @constant  SAErrorNotAuthorized           The application is not authorized to perform the requested operation.
 @constant  SAErrorNotAllowed          The API is restricted on this device at the current time.
 @constant  SAErrorInvalidArgument         An invalid argument was provided to the API.
 @constant  SAErrorOperationFailed         The requested operation failed, retrying may succeed.
 */
typedef NS_ERROR_ENUM(SAErrorDomain, SAErrorCode) {
    SAErrorNotAuthorized = 1,
    SAErrorNotAllowed,
    SAErrorInvalidArgument,
    SAErrorOperationFailed,
} API_AVAILABLE(ios(16.0), macos(13.0), watchos(10.1)) API_UNAVAILABLE(tvos);

NS_ASSUME_NONNULL_END
