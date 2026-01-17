//
//  ASAuthorizationAppleIDRequest.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorization.h>
#import <AuthenticationServices/ASAuthorizationOpenIDRequest.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@interface ASAuthorizationAppleIDRequest : ASAuthorizationOpenIDRequest

/*! @abstract If you have been previously vended a 'user' value through ASAuthorization response, you may set it here to provide additional context to identity provider.
 
 @see ASAuthorizationAppleIDCredential doc for the description of this property in context of response.
 */
@property (nonatomic, copy, nullable) NSString *user;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
