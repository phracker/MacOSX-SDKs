// Copyright © 2022 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class ASAuthorizationWebBrowserPlatformPublicKeyCredential;

#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_AVAILABLE(macos(13.3), macCatalyst(16.4), ios(17.4)) API_UNAVAILABLE(tvos, watchos, visionos)
#else
API_AVAILABLE(macos(13.3), macCatalyst(16.4), ios(17.4)) API_UNAVAILABLE(tvos, watchos)
#endif
typedef NS_ENUM(NSInteger, ASAuthorizationWebBrowserPublicKeyCredentialManagerAuthorizationState) {
    ASAuthorizationWebBrowserPublicKeyCredentialManagerAuthorizationStateAuthorized,
    ASAuthorizationWebBrowserPublicKeyCredentialManagerAuthorizationStateDenied,
    ASAuthorizationWebBrowserPublicKeyCredentialManagerAuthorizationStateNotDetermined,
} NS_SWIFT_NAME(ASAuthorizationWebBrowserPublicKeyCredentialManager.AuthorizationState);

AS_SWIFT_SENDABLE
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
AS_EXTERN API_AVAILABLE(macos(13.3), macCatalyst(16.4), ios(17.4)) API_UNAVAILABLE(tvos, watchos, visionos)
#else
AS_EXTERN API_AVAILABLE(macos(13.3), macCatalyst(16.4), ios(17.4)) API_UNAVAILABLE(tvos, watchos)
#endif
@interface ASAuthorizationWebBrowserPublicKeyCredentialManager : NSObject

@property (class, nonatomic, readonly) BOOL isDeviceConfiguredForPasskeys API_AVAILABLE(macos(26.2), ios(26.2));

- (instancetype)init NS_DESIGNATED_INITIALIZER;

- (void)requestAuthorizationForPublicKeyCredentials:(void (^)(ASAuthorizationWebBrowserPublicKeyCredentialManagerAuthorizationState authorizationState))completionHandler NS_SWIFT_NAME(requestAuthorizationForPublicKeyCredentials(_:));

- (void)platformCredentialsForRelyingParty:(NSString *)relyingParty completionHandler:(void (^)(NSArray<ASAuthorizationWebBrowserPlatformPublicKeyCredential *> *))completionHandler NS_REFINED_FOR_SWIFT;

@property (nonatomic, readonly) ASAuthorizationWebBrowserPublicKeyCredentialManagerAuthorizationState authorizationStateForPlatformCredentials;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
