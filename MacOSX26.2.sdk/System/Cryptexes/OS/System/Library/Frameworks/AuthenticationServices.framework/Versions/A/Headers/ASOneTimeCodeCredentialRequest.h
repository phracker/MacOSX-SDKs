// Copyright © 2023 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASCredentialRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class ASOneTimeCodeCredentialIdentity;

AS_EXTERN API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASOneTimeCodeCredentialRequest : NSObject<ASCredentialRequest>

- (instancetype)init NS_UNAVAILABLE;

/*! @abstract Initializes an instance of ASOneTimeCodeCredentialRequest.
 @param credentialIdentity the credential identity to use for this request.
 */
- (instancetype)initWithCredentialIdentity:(ASOneTimeCodeCredentialIdentity *)credentialIdentity NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
