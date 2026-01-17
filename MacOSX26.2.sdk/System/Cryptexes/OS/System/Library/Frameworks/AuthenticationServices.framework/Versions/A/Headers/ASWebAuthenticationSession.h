//
//  ASWebAuthenticationSession.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

@class ASWebAuthenticationSessionCallback;

NS_ASSUME_NONNULL_BEGIN

@protocol ASWebAuthenticationPresentationContextProviding;

AS_EXTERN API_AVAILABLE(ios(12.0), macCatalyst(13.0), macos(10.15), watchos(6.2), tvos(16.0))
NSErrorDomain const ASWebAuthenticationSessionErrorDomain;

/*! @enum ASWebAuthenticationSessionErrorCode
 @abstract Error code of the NSError object passed in by ASWebAuthenticationSessionCompletionHandler.
 @constant ASWebAuthenticationSessionErrorCodeCanceledLogin The user has canceled login by cancelling the
 alert asking for permission to log in to this app, or by dismissing the view controller for loading the
 authentication webpage.
 @constant ASWebAuthenticationSessionErrorCodePresentationContextNotProvided A valid presentationContextProvider
 was not found when -start was called. Ensure this property was not nil when -start was called.
 @constant ASWebAuthenticationSessionErrorCodePresentationContextInvalid The presentation context returned
 was not elligible to show the authentication UI. For iOS, validate that the UIWindow is in a foreground scene.
 */
typedef NS_ERROR_ENUM(ASWebAuthenticationSessionErrorDomain, ASWebAuthenticationSessionErrorCode) {
    ASWebAuthenticationSessionErrorCodeCanceledLogin = 1,
    ASWebAuthenticationSessionErrorCodePresentationContextNotProvided API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos) = 2,
    ASWebAuthenticationSessionErrorCodePresentationContextInvalid API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos) = 3,
} API_AVAILABLE(ios(12.0), macCatalyst(13.0), macos(10.15), watchos(6.2), tvos(16.0));

typedef void (^ASWebAuthenticationSessionCompletionHandler)(NSURL *_Nullable callbackURL, NSError *_Nullable error) NS_SWIFT_NAME(ASWebAuthenticationSession.CompletionHandler);

/*!
 @class ASWebAuthenticationSession
 An ASWebAuthenticationSession object can be used to authenticate a user with a web service, even if the web service is run
 by a third party. ASWebAuthenticationSession puts the user in control of whether they want to use their existing logged-in
 session from Safari. The app provides a URL that points to the authentication webpage. The page will be loaded in a secure
 view controller. From the webpage, the user can authenticate herself and grant access to the app.
 On completion, the service will send a callback URL with an authentication token, and this URL will be passed to the app by
 ASWebAuthenticationSessionCompletionHandler.

 The callback URL usually has a custom URL scheme. For the app to receive the callback URL, it needs to either register the
 custom URL scheme in its Info.plist, or set the scheme to callbackURLScheme argument in the initializer.

 If the user has already logged into the web service in Safari or other apps via ASWebAuthenticationSession, it is possible to
 share the existing login information. An alert will be presented to get the user's consent for sharing their existing login
 information. If the user cancels the alert, the session will be canceled, and the completion handler will be called with
 the error code ASWebAuthenticationSessionErrorCodeCanceledLogin.

 If the user taps Cancel when showing the login webpage for the web service, the session will be canceled, and the completion
 handler will be called with the error code ASWebAuthenticationSessionErrorCodeCanceledLogin.

 The app can cancel the session by calling -[ASWebAuthenticationSession cancel]. This will also dismiss the view controller that
 is showing the web service's login page.
 */
AS_EXTERN API_AVAILABLE(ios(12.0), macCatalyst(13.0), macos(10.15), watchos(6.2), tvos(16.0))
@interface ASWebAuthenticationSession : NSObject

/*! @abstract Returns an ASWebAuthenticationSession object.
 @param URL the initial URL pointing to the authentication webpage. Only supports URLs with http:// or https:// schemes.
 @param callbackURLScheme the custom URL scheme that the app expects in the callback URL.
 @param completionHandler the completion handler which is called when the session is completed successfully or canceled by user.
 */
- (instancetype)initWithURL:(NSURL *)URL callbackURLScheme:(nullable NSString *)callbackURLScheme completionHandler:(ASWebAuthenticationSessionCompletionHandler)completionHandler API_DEPRECATED("Use initWithURL:callback:completionHandler: instead", ios(12.0, API_TO_BE_DEPRECATED), macCatalyst(13.0, API_TO_BE_DEPRECATED), macos(10.15, API_TO_BE_DEPRECATED), watchos(6.2, API_TO_BE_DEPRECATED), tvos(16.0, API_TO_BE_DEPRECATED));

- (instancetype)initWithURL:(NSURL *)URL callback:(ASWebAuthenticationSessionCallback *)callback completionHandler:(ASWebAuthenticationSessionCompletionHandler)completionHandler API_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4), visionos(1.1));

/*! @abstract Provides context to target where in an application's UI the authorization view should be shown. A provider
 must be set prior to calling -start, otherwise the authorization view cannot be displayed. If deploying to iOS prior to
 13.0, the desired window is inferred by the application's key window.
 */
@property (nonatomic, weak) id <ASWebAuthenticationPresentationContextProviding> presentationContextProvider API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

/*! @abstract Indicates whether this session should ask the browser for an ephemeral session.
 @discussion Ephemeral web browser sessions do not not share cookies or other browsing data with a user's normal browser session.
 This value is NO by default. Setting this property after calling -[ASWebAuthenticationSession start] has no effect.
 */
@property (nonatomic) BOOL prefersEphemeralWebBrowserSession API_AVAILABLE(ios(13.0), macos(10.15), watchos(6.2)) API_UNAVAILABLE(tvos);

/// Any additional header fields to be set when loading the initial URL.
/// All header field names must start with the "X-" prefix.
@property (nonatomic, nullable) NSDictionary<NSString *, NSString *> *additionalHeaderFields API_AVAILABLE(ios(17.4), macos(14.4), tvos(17.4), watchos(10.4), visionos(1.1));

/*! @abstract Returns whether the session can be successfully started. This property returns the same value as calling -start,
 but without the side effect of actually starting the session.
 */
@property (nonatomic, readonly) BOOL canStart API_AVAILABLE(ios(13.4), macos(10.15.4), watchos(6.2));

/*! @abstract Starts the ASWebAuthenticationSession instance after it is instantiated.
 @discussion start can only be called once for an ASWebAuthenticationSession instance. This also means calling start on a
 canceled session will fail.
 @result Returns YES if the session starts successfully.
 */
- (BOOL)start;

/*! @abstract Cancel an ASWebAuthenticationSession. If the view controller is already presented to load the webpage for
 authentication, it will be dismissed. Calling cancel on an already canceled session will have no effect.
 */
- (void)cancel API_UNAVAILABLE(tvos);

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

/*! @abstract Provides context to target where in an application's UI the authorization view should be shown.
 */
API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(tvos, watchos)
NS_SWIFT_UI_ACTOR
@protocol ASWebAuthenticationPresentationContextProviding <NSObject>

#if !TARGET_OS_WATCH
/*! @abstract Return the ASPresentationAnchor in the closest proximity to where a user interacted with your app to trigger
 authentication. If starting an ASWebAuthenticationSession on first launch, use the application's main window.
 @param session The session requesting a presentation anchor.
 @result The ASPresentationAnchor most closely associated with the UI used to trigger authentication.
 */
- (ASPresentationAnchor)presentationAnchorForWebAuthenticationSession:(ASWebAuthenticationSession *)session;
#endif

@end

NS_ASSUME_NONNULL_END
