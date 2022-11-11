//
//  ASAuthorizationController.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <AuthenticationServices/ASAuthorizationCustomMethod.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class ASAuthorization;
@class ASAuthorizationRequest;
@class ASAuthorizationController;

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@protocol ASAuthorizationControllerDelegate <NSObject>
@optional

- (void)authorizationController:(ASAuthorizationController *)controller didCompleteWithAuthorization:(ASAuthorization *)authorization NS_SWIFT_NAME(authorizationController(controller:didCompleteWithAuthorization:));
- (void)authorizationController:(ASAuthorizationController *)controller didCompleteWithError:(NSError *)error  NS_SWIFT_NAME(authorizationController(controller:didCompleteWithError:));

- (void)authorizationController:(ASAuthorizationController *)controller didCompleteWithCustomMethod:(ASAuthorizationCustomMethod)method  NS_SWIFT_NAME(authorizationController(_:didCompleteWithCustomMethod:)) API_AVAILABLE(tvos(15.0)) API_UNAVAILABLE(ios, macos, watchos);
@end

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos)
@protocol ASAuthorizationControllerPresentationContextProviding <NSObject>
@required

#if !TARGET_OS_WATCH
/*! @abstract Return a view anchor that is most appropriate for athorization UI to be presented over.  This view will be used as a hint if a credential provider requires user interaction.
 */
- (ASPresentationAnchor)presentationAnchorForAuthorizationController:(ASAuthorizationController *)controller;
#endif

@end


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

/*! @abstract Initiate the authorization flows.  Upon completion, the delegate will be called with either success or failure.
 Certain authorization flows may require a presentation context, the presentationContextProvider will be called to provider it.
 
 The instance will remain retained until the user completes the flow and the delegate callback is made.
 */
- (void)performRequests;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
