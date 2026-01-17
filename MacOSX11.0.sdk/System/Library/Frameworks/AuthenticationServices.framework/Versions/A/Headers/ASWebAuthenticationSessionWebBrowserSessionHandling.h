//
//  ASWebAuthenticationSessionWebBrowserSessionHandling.h
//  AuthenticationServices Framework
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>

@class ASWebAuthenticationSessionRequest;

AS_EXTERN API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos)
@protocol ASWebAuthenticationSessionWebBrowserSessionHandling
- (void)beginHandlingWebAuthenticationSessionRequest:(ASWebAuthenticationSessionRequest *)request;
- (void)cancelWebAuthenticationSessionRequest:(ASWebAuthenticationSessionRequest *)request;
@end
