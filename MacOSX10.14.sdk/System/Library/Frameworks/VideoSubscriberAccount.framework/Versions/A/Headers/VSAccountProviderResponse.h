//
//  VSAccountProviderResponse.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/NSObject.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// An opaque protocol name, to be coordinated with specific account providers.
typedef NSString *VSAccountProviderAuthenticationScheme NS_EXTENSIBLE_STRING_ENUM;

/// The authentication scheme for responses that use the SAML protocol.
VS_EXTERN VSAccountProviderAuthenticationScheme const VSAccountProviderAuthenticationSchemeSAML
NS_SWIFT_NAME(saml)
API_AVAILABLE(ios(10.2), tvos(10.1));

/// A value object that encapsulates the response given by an account provider.
VS_EXPORT API_AVAILABLE(ios(10.2), tvos(10.1))
@interface VSAccountProviderResponse : NSObject

/// Identifies the protocol used in constructing this response.
@property (nonatomic, readonly, copy) VSAccountProviderAuthenticationScheme authenticationScheme;

/// The status code for this response.
/// May be nil if there is no meaningful value for this type of response.
@property (nonatomic, readonly, copy, nullable) NSString *status;

/// The raw response from the provider.
/// May be nil if the response contained security-sensitive information.
@property (nonatomic, readonly, copy, nullable) NSString *body;

@end

NS_ASSUME_NONNULL_END
