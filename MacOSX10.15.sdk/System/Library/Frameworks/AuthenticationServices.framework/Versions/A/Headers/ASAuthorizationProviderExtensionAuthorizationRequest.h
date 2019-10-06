//
//  ASAuthorizationProviderExtensionAuthorizationRequest.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * ASAuthorizationProviderAuthorizationOperation API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(macCatalyst, watchos, tvos) NS_TYPED_EXTENSIBLE_ENUM;

@class ASAuthorizationProviderExtensionAuthorizationRequest;

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(macCatalyst, watchos, tvos)
@protocol ASAuthorizationProviderExtensionAuthorizationRequestHandler <NSObject>

/*! @abstract Called to begin the authorization. It’s called on the main thread.
 */
- (void)beginAuthorizationWithRequest:(ASAuthorizationProviderExtensionAuthorizationRequest *)request;

@optional

/*! @abstract Called when the authorization was canceled by authorization service. It’s called on the main thread.
 */
- (void)cancelAuthorizationWithRequest:(ASAuthorizationProviderExtensionAuthorizationRequest *)request;

@end

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(macCatalyst, watchos, tvos)
@interface ASAuthorizationProviderExtensionAuthorizationRequest : NSObject

/*! @abstract Call when authorization was not handled.
 */
- (void)doNotHandle;

/*! @abstract Call when authorization needs to be canceled from some reason (for example user pressed Cancel button).
 */
- (void)cancel;

/*! @abstract Call when authorization succeeded without any output.
 */
- (void)complete;

/*! @abstract Call when authorization succeeded with an authorization tokens stored in HTTP headers.
 */
- (void)completeWithHTTPAuthorizationHeaders:(NSDictionary<NSString *, NSString *> *)httpAuthorizationHeaders NS_SWIFT_NAME(complete(httpAuthorizationHeaders:));

/*! @abstract Call when authorization succeeded with a HTTP response.
 */
- (void)completeWithHTTPResponse:(NSHTTPURLResponse *)httpResponse httpBody:(nullable NSData *)httpBody NS_SWIFT_NAME(complete(httpResponse:httpBody:));

/*! @abstract Call when authorization failed with an error.
 */
- (void)completeWithError:(NSError *)error NS_SWIFT_NAME(complete(error:));

/*! @abstract Asks authorization service to show extension view controller. If the controller cannot be shown an error is returned.
 */
- (void)presentAuthorizationViewControllerWithCompletion:(void(^)(BOOL success, NSError * _Nullable error))completion;

/*! @abstract Request URL with all components.
 */
@property (nonatomic, readonly) NSURL *url;

/*! @abstract Operation to be executed by the extension.
 */
@property (nonatomic, readonly) ASAuthorizationProviderAuthorizationOperation requestedOperation;

/*! @abstract Request HTTP headers.
 */
@property (nonatomic, readonly) NSDictionary<NSString *, NSString *> *httpHeaders;

/*! @abstract Request body.
 */
@property (nonatomic, readonly) NSData *httpBody;

/*! @abstract Realm.
 */
@property (nonatomic, readonly, copy) NSString *realm;

/*! @abstract Extension data from extension configuration provided by MDM stored as a property-list.
 */
@property (nonatomic, readonly) NSDictionary *extensionData;

/*! @abstract Identification of the calling application.
 */
@property (nonatomic, readonly, copy) NSString *callerBundleIdentifier;

/*! @abstract Authorization options.
 */
@property (nonatomic, readonly) NSDictionary *authorizationOptions;

@end

NS_ASSUME_NONNULL_END
