//
//  VSAccountMetadata.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <os/availability.h>
#import <Foundation/NSObject.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSDate;
@class NSString;
@class VSAccountProviderResponse;

/// A collection of information about a subscriber's account.
VS_EXPORT API_AVAILABLE(ios(10.0), tvos(10.0)) API_UNAVAILABLE(macCatalyst)
@interface VSAccountMetadata : NSObject

/// A value that uniquely identifies the account provider.
/// You may use this value to brand your app.
@property (nonatomic, readonly, copy, nullable) NSString *accountProviderIdentifier;

/// Specifies when the user might need to re-authenticate with the account provider.
/// The value might be nil if the user is not currently authenticated.
@property (nonatomic, readonly, copy, nullable) NSDate *authenticationExpirationDate;

/// An opaque blob of data that can be used to cryptographically verify that the
/// SAML AttributeQuery response actually came from the account provider.
@property (nonatomic, readonly, copy, nullable) NSData *verificationData;

/// The SAML AttributeQuery response received from the account provider.
/// The value might be nil if your account metadata request did not specify any SAML attributes or if the user does not have a valid authentication.
@property (nonatomic, readonly, copy, nullable) NSString *SAMLAttributeQueryResponse;

/// The response received from the account provider.
/// The value might be nil if your account metadata request did not specify any
/// attributes, or if the user does not have a valid authentication.
@property (nonatomic, readonly, strong, nullable) VSAccountProviderResponse *accountProviderResponse
API_AVAILABLE(ios(10.2), tvos(10.1));

@end

NS_ASSUME_NONNULL_END
