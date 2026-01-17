//
//  ASAuthorizationController.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <AuthenticationServices/ASAuthorizationCustomMethod.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class ASAuthorization;
@class ASAuthorizationRequest;
@class ASAuthorizationController;
@class ASCPublicKeyAccountRegistrationOptions;

NS_SWIFT_UI_ACTOR
AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@protocol ASAuthorizationControllerDelegate <NSObject>
@optional

- (void)authorizationController:(ASAuthorizationController *)controller didCompleteWithAuthorization:(ASAuthorization *)authorization NS_SWIFT_NAME(authorizationController(controller:didCompleteWithAuthorization:));
- (void)authorizationController:(ASAuthorizationController *)controller didCompleteWithError:(NSError *)error  NS_SWIFT_NAME(authorizationController(controller:didCompleteWithError:));

- (void)authorizationController:(ASAuthorizationController *)controller didCompleteWithCustomMethod:(ASAuthorizationCustomMethod)method  NS_SWIFT_NAME(authorizationController(_:didCompleteWithCustomMethod:)) API_AVAILABLE(tvos(15.0)) API_UNAVAILABLE(ios, macos, watchos);
@end

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos)
NS_SWIFT_UI_ACTOR
@protocol ASAuthorizationControllerPresentationContextProviding <NSObject>
@required

#if !TARGET_OS_WATCH
/*! @abstract Return a view anchor that is most appropriate for athorization UI to be presented over.  This view will be used as a hint if a credential provider requires user interaction.
 */
- (ASPresentationAnchor)presentationAnchorForAuthorizationController:(ASAuthorizationController *)controller;
#endif

@end

typedef NS_OPTIONS(NSUInteger, ASAuthorizationControllerRequestOptions) {
    /// When used for sign-in requests, tell the authorization controller that it should only be presented if there are credentials immediately available on the local device.
    /// When used for registration requests, tell the authorization controller that it should only be presented if the local device is currently set up to fulfill at least one of the request types.
    ASAuthorizationControllerRequestOptionPreferImmediatelyAvailableCredentials API_UNAVAILABLE(tvos, watchos) = 1 << 0,
} NS_SWIFT_NAME(ASAuthorizationController.RequestOptions) API_AVAILABLE(ios(16.0), macos(13.0)) API_UNAVAILABLE(tvos, watchos);

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@interface ASAuthorizationController : NSObject

/*! @abstract Authorization requests that are being serviced by this controller
 */
@property (nonatomic, readonly, strong) NSArray<ASAuthorizationRequest *> *authorizationRequests;

/*! @abstract This delegate will be invoked upon completion of the authorization indicating success or failure.
 Delegate is required to receive the results of authorization.
 */
@property (nonatomic, weak, nullable) id <ASAuthorizationControllerDelegate> delegate;

/*! @abstract This delegate will be invoked upon needing a presentation context to display authorization UI.
 */
@property (nonatomic, weak, nullable) id <ASAuthorizationControllerPresentationContextProviding> presentationContextProvider API_UNAVAILABLE(watchos);

/*! @abstract A list of custom authorization methods that may be displayed in the authorization UI.

 If the user selects one of these methods, instead of attempting to secure an authorization for the requests, the
 controller will call authorizationController:didCompleteWithCustomMethod: with the selected method, allowing
 the client to perform the requested authorization.
 */
@property (nonatomic, copy) NSArray<ASAuthorizationCustomMethod> *customAuthorizationMethods API_AVAILABLE(tvos(15.0)) API_UNAVAILABLE(ios, macos, watchos);

/*! @abstract Initialize the controller with authorization requests.
 
 @param authorizationRequests At least one request should be provided. Requests of same type maybe honored in first in first out order
 */
- (instancetype)initWithAuthorizationRequests:(NSArray<ASAuthorizationRequest *> *)authorizationRequests NS_DESIGNATED_INITIALIZER;

/*! @abstract Initiate the authorization flows. Upon completion, the delegate will be called with either success or failure.
 Certain authorization flows may require a presentation context. The @c presentationContextProvider will be called
 to provide it.

 The instance will remain retained until the flow is either completed or canceled, and the delegate callback is made.
 */
- (void)performRequests;

/*! @abstract Initiate the authorization flows for requests that support AutoFill presentation. UI will be shown when
 focusing a text field with the appropriate text content type. Upon completion, the delegate will be called with either success
 or failure.

 The instance will remain retained until the flow is either completed or canceled, and the delegate callback is made.
 */
- (void)performAutoFillAssistedRequests API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos);

/*! @abstract Initiate the authorization flows. Upon completion, the delegate will be called with either success or failure.
 Certain authorization flows may require a presentation context. The @c presentationContextProvider will be called
 to provide it.

 Calling this method with no options is the same as calling @c performRequests. The instance will remain retained until
 the flow is either completed or canceled, and the delegate callback is made.
 */
- (void)performRequestsWithOptions:(ASAuthorizationControllerRequestOptions)options NS_SWIFT_NAME(performRequests(options:)) API_AVAILABLE(ios(16.0), macos(13.0)) API_UNAVAILABLE(watchos, tvos);

/*! @abstract Cancel the running authorization flows, if there are any. If a flow is canceled, the delegate callback will
 be made indicating the cancel.
 */
- (void)cancel API_AVAILABLE(macos(13.0), ios(16.0), tvos(18.0)) API_UNAVAILABLE(watchos);

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
