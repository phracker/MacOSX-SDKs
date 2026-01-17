//
//  ASPasswordCredentialRequest.h
//  AuthenticationServices Framework
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASCredentialRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class ASPasswordCredentialIdentity;

/*! @class This class encapsulates a password request made to a credential provider extension.
 */
AS_EXTERN API_AVAILABLE(ios(17.0), macCatalyst(17.0), macos(14.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASPasswordCredentialRequest : NSObject <ASCredentialRequest>

- (instancetype)init NS_UNAVAILABLE;

/*! @abstract Initializes an instance of ASPasswordCredentialRequest.
 @param credentialIdentity the credential identity to use for this request.
 */
- (instancetype)initWithCredentialIdentity:(ASPasswordCredentialIdentity *)credentialIdentity NS_DESIGNATED_INITIALIZER;

/*! @abstract Creates and initializes an instance of ASPasswordCredentialRequest.
 @param credentialIdentity the credential identity to use for this request.
 */
+ (instancetype)requestWithCredentialIdentity:(ASPasswordCredentialIdentity *)credentialIdentity;

@end

NS_ASSUME_NONNULL_END
