// Copyright © 2023 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASFoundation.h>

AS_HEADER_AUDIT_BEGIN(nullability, sendability)

NS_REFINED_FOR_SWIFT
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
AS_API_AVAILABLE(macos(13.5), macCatalyst(16.6), ios(17.4)) API_UNAVAILABLE(tvos, watchos, visionos)
#else
AS_API_AVAILABLE(macos(13.5), macCatalyst(16.6), ios(17.4)) API_UNAVAILABLE(tvos, watchos)
#endif
typedef NS_ENUM(NSInteger, ASPublicKeyCredentialClientDataCrossOriginValue) {
    ASPublicKeyCredentialClientDataCrossOriginValueNotSet,
    ASPublicKeyCredentialClientDataCrossOriginValueCrossOrigin,
    ASPublicKeyCredentialClientDataCrossOriginValueSameOriginWithAncestors,
};

NS_REFINED_FOR_SWIFT AS_EXTERN
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
AS_API_AVAILABLE(macos(13.5), macCatalyst(16.6), ios(17.4)) API_UNAVAILABLE(tvos, watchos, visionos)
#else
AS_API_AVAILABLE(macos(13.5), macCatalyst(16.6), ios(17.4)) API_UNAVAILABLE(tvos, watchos)
#endif
/// This object represents the client data for a public key credential request, as defined in the WebAuthentication standard.
@interface ASPublicKeyCredentialClientData : NSObject
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithChallenge:(NSData *)challenge origin:(NSString *)origin;

/// The challenge to be signed during the operation.
@property (nonatomic) NSData *challenge;

/// The origin for where the request was performed.
@property (nonatomic) NSString *origin;

/// The top-level origin, if applicable.
@property (nonatomic, nullable) NSString *topOrigin;

/// Indicates whether this is a cross-origin request, if applicable.
@property (nonatomic) ASPublicKeyCredentialClientDataCrossOriginValue crossOrigin;

@end

AS_HEADER_AUDIT_END(nullability, sendability)
