//
//  ASExtensionErrors.h
//  AuthenticationServices Framework
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

AS_EXTERN API_AVAILABLE(ios(12.0), macCatalyst(14.0), macos(11.0)) API_UNAVAILABLE(tvos, watchos)
NSErrorDomain const ASExtensionErrorDomain;

typedef NS_ERROR_ENUM(ASExtensionErrorDomain, ASExtensionErrorCode) {
    ASExtensionErrorCodeFailed = 0,
    ASExtensionErrorCodeUserCanceled = 1,
    ASExtensionErrorCodeUserInteractionRequired = 100,
    ASExtensionErrorCodeCredentialIdentityNotFound = 101,
} API_AVAILABLE(ios(12.0), macCatalyst(14.0), macos(11.0)) API_UNAVAILABLE(tvos, watchos);

/*! @abstract A key that specifies an error string to be shown to the user when an extension request fails.
*/
AS_EXTERN NSErrorUserInfoKey const ASExtensionLocalizedFailureReasonErrorKey API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos, watchos);
