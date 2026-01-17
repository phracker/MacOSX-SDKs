//
//  ASAuthorizationPasswordProvider.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorizationPasswordRequest.h>
#import <AuthenticationServices/ASAuthorizationProvider.h>
#import <AuthenticationServices/ASFoundation.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@interface ASAuthorizationPasswordProvider : NSObject <ASAuthorizationProvider>

- (ASAuthorizationPasswordRequest *)createRequest;

@end

NS_ASSUME_NONNULL_END
