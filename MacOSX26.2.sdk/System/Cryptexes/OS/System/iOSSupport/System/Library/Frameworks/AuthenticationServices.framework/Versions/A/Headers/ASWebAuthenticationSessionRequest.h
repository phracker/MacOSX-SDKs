//
//  ASWebAuthenticationSessionRequest.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@class ASWebAuthenticationSessionCallback;
@class ASWebAuthenticationSessionRequest;

AS_EXTERN API_AVAILABLE(macCatalyst(13.0), macos(10.15)) API_UNAVAILABLE(ios, tvos)
@protocol ASWebAuthenticationSessionRequestDelegate <NSObject>
@optional
- (void)authenticationSessionRequest:(ASWebAuthenticationSessionRequest *)authenticationSessionRequest didCompleteWithCallbackURL:(NSURL *)callbackURL;
- (void)authenticationSessionRequest:(ASWebAuthenticationSessionRequest *)authenticationSessionRequest didCancelWithError:(NSError *)error;
@end

AS_EXTERN API_AVAILABLE(macCatalyst(13.0), macos(10.15)) API_UNAVAILABLE(ios, tvos)
@interface ASWebAuthenticationSessionRequest : NSObject <NSSecureCoding, NSCopying>

@property (readonly, nonatomic) NSUUID *UUID;
@property (readonly, nonatomic) NSURL *URL;

@property (nullable, readonly, nonatomic, copy) NSString *callbackURLScheme API_DEPRECATED("Use `callback` to match all callback types.", macCatalyst(13.0, 17.4), macosx(10.15, 14.4));

@property (readonly, nonatomic) BOOL shouldUseEphemeralSession;
@property (nullable, nonatomic, weak) id<ASWebAuthenticationSessionRequestDelegate> delegate;

/// Additional headers to be sent when loading the initial URL.
/// These should _only_ apply to the initial page, and should not overwrite any headers normally sent by the browser.
/// Add `AdditionalHeaderFieldsAreSupported: true` to `ASWebAuthenticationSessionWebBrowserSupportCapabilities` in your browser's Info.plist file to indicate support for this.
@property (nonatomic, nullable, readonly) NSDictionary<NSString *, NSString *> *additionalHeaderFields API_AVAILABLE(macCatalyst(17.4), macos(14.4));

/// The callback to listen for to complete this request.
/// Check all main-frame navigations loaded during the request with this callback. It is used to handle all callback types, including custom schemes and HTTPS navigations.
/// When a match is found, invoke `-completeWithCallbackURL:` with that URL.
/// Add `CallbackURLMatchingIsSupported: true` to `ASWebAuthenticationSessionWebBrowserSupportCapabilities` in your browser's Info.plist file to indicate support for this.
@property (nonatomic, nullable, readonly) ASWebAuthenticationSessionCallback *callback API_AVAILABLE(macCatalyst(17.4), macos(14.4));

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (void)cancelWithError:(NSError *)error;
- (void)completeWithCallbackURL:(NSURL *)url;
@end

NS_ASSUME_NONNULL_END
