//
//  AuthenticationServices.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <AuthenticationServices/ASWebAuthenticationSession.h>
#import <AuthenticationServices/ASWebAuthenticationSessionRequest.h>
#import <AuthenticationServices/ASWebAuthenticationSessionWebBrowserSessionHandling.h>
#import <AuthenticationServices/ASWebAuthenticationSessionWebBrowserSessionManager.h>

#import <AuthenticationServices/ASCredentialIdentityStore.h>
#import <AuthenticationServices/ASCredentialIdentityStoreState.h>
#import <AuthenticationServices/ASCredentialProviderExtensionContext.h>
#import <AuthenticationServices/ASCredentialServiceIdentifier.h>
#import <AuthenticationServices/ASPasswordCredential.h>
#import <AuthenticationServices/ASPasswordCredentialIdentity.h>

#import <AuthenticationServices/ASAuthorization.h>
#import <AuthenticationServices/ASAuthorizationAppleIDCredential.h>
#import <AuthenticationServices/ASAuthorizationAppleIDProvider.h>
#import <AuthenticationServices/ASAuthorizationAppleIDRequest.h>
#import <AuthenticationServices/ASAuthorizationController.h>
#import <AuthenticationServices/ASAuthorizationCredential.h>
#import <AuthenticationServices/ASAuthorizationError.h>
#import <AuthenticationServices/ASAuthorizationOpenIDRequest.h>
#import <AuthenticationServices/ASAuthorizationPasswordProvider.h>
#import <AuthenticationServices/ASAuthorizationProvider.h>
#import <AuthenticationServices/ASAuthorizationRequest.h>
#import <AuthenticationServices/ASAuthorizationSingleSignOnCredential.h>
#import <AuthenticationServices/ASAuthorizationSingleSignOnProvider.h>
#import <AuthenticationServices/ASAuthorizationSingleSignOnRequest.h>
#import <AuthenticationServices/ASAuthorizationProviderExtensionAuthorizationRequest.h>

#if TARGET_OS_IOS && !(defined(TARGET_OS_MACCATALYST) && TARGET_OS_MACCATALYST)
#import <AuthenticationServices/ASCredentialProviderViewController.h>
#endif

#if !TARGET_OS_WATCH
#import <AuthenticationServices/ASAuthorizationAppleIDButton.h>
#endif
