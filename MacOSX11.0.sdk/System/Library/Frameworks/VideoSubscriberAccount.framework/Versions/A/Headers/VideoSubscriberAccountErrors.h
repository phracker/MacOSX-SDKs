//
//  VideoSubscriberAccountErrors.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <os/availability.h>
#import <Foundation/NSObjCRuntime.h>
#import <Foundation/NSError.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSString;

/// The domain of all errors returned by VideoSubscriberAccount framework.
VS_EXTERN NSErrorDomain const VSErrorDomain
API_AVAILABLE(ios(10.0), tvos(10.0)) API_UNAVAILABLE(macCatalyst);

/// A key that can be used to obtain the subscription provider's SAML response string from an error user info dictionary.
VS_EXTERN NSErrorUserInfoKey const VSErrorInfoKeySAMLResponse
API_AVAILABLE(ios(10.0), tvos(10.0)) API_UNAVAILABLE(macCatalyst);

/// A key that can be used to obtain the subscription provider's SAML status code string from an error user info dictionary.
VS_EXTERN NSErrorUserInfoKey const VSErrorInfoKeySAMLResponseStatus
API_AVAILABLE(ios(10.0), tvos(10.0)) API_UNAVAILABLE(macCatalyst);

/// A key that can be used to obtain the account provider's response object from an error user info dictionary.
VS_EXTERN NSErrorUserInfoKey const VSErrorInfoKeyAccountProviderResponse
API_AVAILABLE(ios(10.2), tvos(10.1)) API_UNAVAILABLE(macCatalyst);

/// A key that can be used to obtain the identifier string of the user's unsupported subscription provider from an error user info dictionary.
VS_EXTERN NSErrorUserInfoKey const VSErrorInfoKeyUnsupportedProviderIdentifier
API_AVAILABLE(ios(10.3), tvos(10.3)) API_UNAVAILABLE(macCatalyst);

typedef NS_ENUM(NSInteger, VSErrorCode)
{
    VSErrorCodeAccessNotGranted = 0, // The user has not granted the app access to their subscription information.
    VSErrorCodeUnsupportedProvider = 1, // The system does not currently support the user's subscription provider.
    VSErrorCodeUserCancelled = 2, // The request was cancelled by the user.
    VSErrorCodeServiceTemporarilyUnavailable = 3, // The request failed, but a subsequent attempt might succeed.
    VSErrorCodeProviderRejected = 4, // The user's subscription provider did not allow the request to proceed, e.g. because the subscription tier doesn't include the resource, or interactive reauthentication is required, but the request does not allow interruption.
    VSErrorCodeInvalidVerificationToken = 5, // The request's verification token was rejected by the user's subscription provider.
    VSErrorCodeRejected = 6, // For use by TV Provider applications only.
    VSErrorCodeUnsupported = 7 // The TV Provider feature is not supported in the device's current region.
}
API_AVAILABLE(ios(10.0), tvos(10.0)) API_UNAVAILABLE(macCatalyst);

NS_ASSUME_NONNULL_END
