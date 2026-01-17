//
//  ASCredentialProviderExtensionContext.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASExtensionErrors.h>
#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

@class ASOneTimeCodeCredential;

@class ASPasskeyAssertionCredential;
@class ASPasskeyRegistrationCredential;

@class ASGeneratedPassword;

@class ASPasswordCredential;

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(12.0), macCatalyst(14.0), macos(11.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASCredentialProviderExtensionContext : NSExtensionContext

/*! @abstract Complete the request by providing the user selected credential.
 @param credential the credential that the user has selected.
 @param completionHandler optionally contains any work which the extension may need to perform after the request has been completed,
 as a background-priority task. The `expired` parameter will be YES if the system decides to prematurely terminate a previous
 non-expiration invocation of the completionHandler.
 @discussion Calling this method will eventually dismiss the associated view controller.
 */
- (void)completeRequestWithSelectedCredential:(ASPasswordCredential *)credential completionHandler:(void(^ _Nullable)(BOOL expired))completionHandler
    NS_SWIFT_DISABLE_ASYNC
    ;

/*! @abstract Complete the assertion request by providing the user selected passkey credential.
 @param credential the credential that the user has selected. Includes assertion response.
 @param completionHandler optionally contains any work which the extension may need to perform after the request has been completed,
 as a background-priority task. The `expired` parameter will be YES if the system decides to prematurely terminate a previous
 non-expiration invocation of the completionHandler.
 @discussion Calling this method will eventually dismiss the associated view controller.
 */
- (void)completeAssertionRequestWithSelectedPasskeyCredential:(ASPasskeyAssertionCredential *)credential completionHandler:(void(^ _Nullable)(BOOL expired))completionHandler NS_SWIFT_NAME(completeAssertionRequest(using:completionHandler:)) API_AVAILABLE(ios(17.0), macos(14.0)) API_UNAVAILABLE(watchos, tvos);

/*! @abstract Complete the registration request by providing the newly created passkey credential.
 @param credential the credential that was created in response to the registration request.
 @param completionHandler optionally contains any work which the extension may need to perform after the request has been completed,
 as a background-priority task. The `expired` parameter will be YES if the system decides to prematurely terminate a previous
 non-expiration invocation of the completionHandler.
 @discussion Calling this method will eventually dismiss the associated view controller.
 */
- (void)completeRegistrationRequestWithSelectedPasskeyCredential:(ASPasskeyRegistrationCredential *)credential completionHandler:(void(^ _Nullable)(BOOL expired))completionHandler API_AVAILABLE(ios(17.0), macos(14.0)) NS_SWIFT_NAME(completeRegistrationRequest(using:completionHandler:)) API_UNAVAILABLE(watchos, tvos);

/*! @abstract Complete the request by providing the user selected one time code credential.
 @param credential the credential that the user has selected.
 @param completionHandler optionally contains any work which the extension may need to perform after the request has been completed,
 as a background-priority task. The `expired` parameter will be YES if the system decides to prematurely terminate a previous
 non-expiration invocation of the completionHandler.
 @discussion Calling this method will eventually dismiss the associated view controller.
 */
- (void)completeOneTimeCodeRequestWithSelectedCredential:(ASOneTimeCodeCredential *)credential completionHandler:(void(^ _Nullable)(BOOL expired))completionHandler NS_SWIFT_NAME(completeOneTimeCodeRequest(using:completionHandler:)) API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos);


/// Signal that a password request was successfully saved.
/// - parameter completionHandler: An optional block your extension can provide to perform any cleanup work after the system has captured the results.
/// The expired parameter is true if the system decides to prematurely end a previous non-expiration invocation of the completion handler.
/// - note: You are responsible for updating the ASCredentialIdentityStore.
- (void)completeSavePasswordRequestWithCompletionHandler:(void (^ _Nullable)(BOOL expired))completionHandler NS_SWIFT_NAME(completeSavePasswordRequest(completionHandler:)) API_AVAILABLE(ios(26.2), visionos(26.2)) API_UNAVAILABLE(macos, tvos, watchos);
/// Return potential passwords for the given request.
/// - parameter results: Potential passwords that the user can select. You can provide multiple options for increased flexibility on the user's behalf.
/// These results should be returned in priority order.
/// - parameter completionHandler: An optional block your extension can provide to perform any cleanup work after the system has captured the results.
/// The expired parameter is true if the system decides to prematurely end a previous non-expiration invocation of the completion handler.
- (void)completeGeneratePasswordRequestWithResults:(NSArray<ASGeneratedPassword *> *)results completionHandler:(void (^ _Nullable)(BOOL expired))completionHandler NS_SWIFT_NAME(completeGeneratePasswordRequest(results:completionHandler:)) API_AVAILABLE(ios(26.2), visionos(26.2)) API_UNAVAILABLE(macos, tvos, watchos);

/*! @abstract Complete the request to configure the extension.
 @discussion Calling this method will eventually dismiss the associated view controller.
 */
- (void)completeExtensionConfigurationRequest;

- (void)completeRequestReturningItems:(nullable NSArray *)items completionHandler:(void (^ _Nullable)(BOOL))completionHandler NS_UNAVAILABLE;

/*! @abstract Cancels the request.
 @param error error's domain should be ASExtensionErrorDomain and the code should be a value of type ASExtensionErrorCode.
 @discussion The extension should call this method when the user cancels the action or a failure occurs.
 */
- (void)cancelRequestWithError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
