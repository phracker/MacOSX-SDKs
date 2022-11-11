// Copyright © 2020 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
@protocol ASAuthorizationPublicKeyCredentialDescriptor <NSObject, NSSecureCoding, NSCopying>

/*! @abstract An identifier that uniquely identifies a specific credential.
 */
@property (nonatomic, copy) NSData *credentialID;

@end

NS_ASSUME_NONNULL_END
