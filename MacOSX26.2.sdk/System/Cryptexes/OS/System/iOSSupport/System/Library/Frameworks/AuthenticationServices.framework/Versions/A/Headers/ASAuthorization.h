//
//  ASAuthorization.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NSString * ASAuthorizationScope API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0)) NS_SWIFT_NAME(ASAuthorization.Scope) NS_TYPED_EXTENSIBLE_ENUM;

AS_EXTERN ASAuthorizationScope const ASAuthorizationScopeFullName API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));
AS_EXTERN ASAuthorizationScope const ASAuthorizationScopeEmail API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));

@protocol ASAuthorizationProvider, ASAuthorizationCredential;

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@interface ASAuthorization : NSObject

/*! @abstract Provider which was used to generate this authorization response.
 */
@property (nonatomic, readonly, strong) id <ASAuthorizationProvider> provider;

/*! @abstract The credential that was returned by the authorization provider. Authorization provider type should be used to determine how to introspect the credential.
 */
@property (nonatomic, readonly, strong) id <ASAuthorizationCredential> credential;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
