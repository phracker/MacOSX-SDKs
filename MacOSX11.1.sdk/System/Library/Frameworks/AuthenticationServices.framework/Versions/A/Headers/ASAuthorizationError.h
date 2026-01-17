//
//  ASAuthorizationError.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN NSErrorDomain const ASAuthorizationErrorDomain API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));

typedef NS_ERROR_ENUM(ASAuthorizationErrorDomain, ASAuthorizationError) {
    ASAuthorizationErrorUnknown = 1000,
    ASAuthorizationErrorCanceled = 1001,
    ASAuthorizationErrorInvalidResponse = 1002,
    ASAuthorizationErrorNotHandled = 1003,
    ASAuthorizationErrorFailed = 1004,
} API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));

NS_ASSUME_NONNULL_END
