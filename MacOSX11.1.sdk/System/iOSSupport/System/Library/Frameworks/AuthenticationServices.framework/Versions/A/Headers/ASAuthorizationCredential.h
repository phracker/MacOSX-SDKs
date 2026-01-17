//
//  ASAuthorizationCredential.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@protocol ASAuthorizationCredential <NSObject, NSCopying, NSSecureCoding>

@end

NS_ASSUME_NONNULL_END
