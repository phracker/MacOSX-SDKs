//
//  ASCredentialProviderViewController.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASCredentialProviderExtensionContext.h>
#import <AuthenticationServices/ASCredentialServiceIdentifier.h>
#import <AuthenticationServices/ASFoundation.h>
#import <AuthenticationServices/ASOneTimeCodeCredentialIdentity.h>
#import <AuthenticationServices/ASPasswordCredentialIdentity.h>
#import <Foundation/Foundation.h>

#import <AuthenticationServices/ASAuthorizationPublicKeyCredentialRegistrationRequest.h>
#import <AuthenticationServices/ASCredentialRequest.h>
#import <AuthenticationServices/ASPasskeyCredentialRequestParameters.h>

#import <AuthenticationServices/ASSavePasswordRequest.h>
#import <AuthenticationServices/ASGeneratePasswordsRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class ASPasskeyCredentialRequest;

AS_EXTERN API_AVAILABLE(ios(12.0), macCatalyst(14.0), macos(11.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASCredentialProviderViewController : ASViewController

@property (nonatomic, readonly, strong) ASCredentialProviderExtensionContext *extensionContext;

/*! @abstract Prepare the view controller to show a list of credentials.
 @param serviceIdentifiers the array of service identifiers.
 @discussion This method is called by the system to prepare the extension's view controller to present the list of credentials.
 A service identifier array is passed which can be used to filter or prioritize the credentials that closely match each service.
 The service identifier array could have zero or more items. If there are more than one item in the array, items with lower indexes
 represent more specific identifiers for which a credential is being requested. For example, the array could contain identifiers
 [m.example.com, example.com] with the first item representing the more specifc service that requires a credential.
 If the array of service identifiers is empty, it is expected that the credential list should still show credentials that the user can pick from.
 */
- (void)prepareCredentialListForServiceIdentifiers:(NSArray<ASCredentialServiceIdentifier *> *)serviceIdentifiers;

/*! @abstract Prepare the view controller to show a list of passkey and password credentials.
 @param serviceIdentifiers the array of service identifiers.
 @param requestParameters the parameters of the active passkey request.
 @discussion This method is called by the system to prepare the extension's view controller to present the list of credentials.
 A service identifier array is passed which can be used to filter or prioritize the credentials that closely match each service.
 The service identifier array could have zero or more items. If there is more than one item in the array, items with lower indexes
 represent more specific identifiers for which a credential is being requested. For example, the array could contain identifiers
 [m.example.com, example.com] with the first item representing the more specifc service that requires a credential.
 If the array of service identifiers is empty, it is expected that the credential list should still show credentials that the user can pick from.
 If a passkey credential is selected, the extension should use the requestParameters object to complete the request using the selected
 passkey credential.
 */
- (void)prepareCredentialListForServiceIdentifiers:(NSArray<ASCredentialServiceIdentifier *> *)serviceIdentifiers requestParameters:(ASPasskeyCredentialRequestParameters *)requestParameters API_AVAILABLE(ios(17.0), macos(14.0)) API_UNAVAILABLE(watchos, tvos);

/*! @abstract Prepare the view controller to show a list of one time code credentials.
 @param serviceIdentifiers the array of service identifiers.
 @discussion This method is called by the system to prepare the extension's view controller to present the list of credentials.
 A service identifier array is passed which can be used to filter or prioritize the credentials that closely match each service.
 The service identifier array could have zero or more items. If there is more than one item in the array, items with lower indexes
 represent more specific identifiers for which a credential is being requested. For example, the array could contain identifiers
 [m.example.com, example.com] with the first item representing the more specifc service that requires a credential.
 If the array of service identifiers is empty, it is expected that the credential list should still show credentials that the user can pick from.
 */
- (void)prepareOneTimeCodeCredentialListForServiceIdentifiers:(NSArray<ASCredentialServiceIdentifier *> *)serviceIdentifiers API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos);


/*! @abstract Attempt to provide the user-requested credential without any user interaction.
 @param credentialIdentity the credential identity for which a credential should be provided.
 @discussion After the user selects a credential identity, the system may ask your extension to provide the credential without showing any
 user interface if possible to enhance the user experience. If your extension can accomplish this (for example, the user’s passwords database is
 still unlocked from a recent interaction), call -[ASCredentialProviderExtensionContext completeRequestWithSelectedCredential:completionHandler:]
 to provide the credential.
 If an error occurs, call -[ASCredentialProviderExtensionContext cancelRequestWithError:] and pass an error with domain
 ASExtensionErrorDomain and an appropriate error code from ASExtensionErrorCode.  For example, if your extension requires user interaction
 because the passwords database needs to be unlocked, pass an error with code ASExtensionErrorCodeUserInteractionRequired.
 @note When this method is called, your extension's view controller is not present on the screen. Do not attempt or expect to show any user
 interface in this method.
 */
- (void)provideCredentialWithoutUserInteractionForIdentity:(ASPasswordCredentialIdentity *)credentialIdentity
API_DEPRECATED_WITH_REPLACEMENT("provideCredentialWithoutUserInteractionForRequest:", ios(12.0, 17.0), macos(11.0, 14.0))
    ;

/// Attempt to provide the user-requested credential without any user interaction.
///
/// After the user selects a credential identity, the system will create a credential request, the contents of
/// which will depend on whether the credential to use is a password or passkey. The request type will match
/// the type of credential that was requested. Refer to `ASPasswordCredentialRequest`,
/// `ASPasskeyCredentialRequest`, and `ASOneTimeCodeCredentialRequest` for details.
///
/// The system may ask your extension to provide the credential without showing any user interface if possible
/// to enhance the user experience. If your extension can accomplish this (for example, the user’s passwords
/// database is still unlocked from a recent interaction), call `-[ASCredentialProviderExtensionContext completeRequestWithSelectedCredential:completionHandler:]`
/// for password credentials, `-[ASCredentialProviderExtensionContext completeAssertionRequestWithSelectedPasskeyCredential:completionHandler:]` for passkey credentials,
/// or `-[ASCredentialProviderExtensionContext completeOneTimeCodeRequestWithSelectedCredential:completionHandler:]` for one time code credentials.
/// If an error occurs, call `-[ASCredentialProviderExtensionContext cancelRequestWithError:]`
/// and pass an error with domain `ASExtensionErrorDomain` and an appropriate error code from
/// `ASExtensionErrorCode`. For example, if your extension requires user interaction because the
/// passwords database needs to be unlocked, pass an error with code `ASExtensionErrorCodeUserInteractionRequired`.
///
/// In order for your extension to be presented in the list of options for passkey assertion requests, your
/// extension needs to specify a true value for the Information Property List key `ProvidesPasskeys`
/// under the `ASCredentialProviderExtensionCapabilities` dictionary.
///
///     Info.plist
///     ├─ NSExtension
///         ├─ NSExtensionAttributes
///             ├─ ASCredentialProviderExtensionCapabilities
///                 ├─ ProvidesPasskeys => true
///
/// Similarly, your extension needs to specify a true value for the Information Property List key `ProvidesOneTimeCodes`
/// under the `ASCredentialProviderExtensionCapabilities` dictionary in order to be presented in
/// the list of options for one time code requests.
///
/// - Note: When this method is called, your extension's view controller is not present on the screen. Do not
///   attempt or expect to show any user interface in this method.
///
/// - Parameter credentialRequest: The credential request for which a credential should be provided.
- (void)provideCredentialWithoutUserInteractionForRequest:(id <ASCredentialRequest>)credentialRequest API_AVAILABLE(ios(17.0), macos(14.0)) API_UNAVAILABLE(watchos, tvos);

/*! @abstract Prepare the view controller to show user interface for providing the user-requested credential.
 @param credentialIdentity the credential identity for which a credential should be provided.
 @discussion The system calls this method when your extension cannot provide the requested credential without user interaction.
 Set up the view controller for any user interaction required to provide the requested credential only. The user interaction should
 be limited in nature to operations required for providing the requested credential. An example is showing an authentication UI to
 unlock the user's passwords database.
 Call -[ASCredentialProviderExtensionContext completeRequestWithSelectedCredential:completionHandler:] to provide the credential.
 If an error occurs, call -[ASCredentialProviderExtensionContext cancelRequestWithError:] and pass an error with domain
 ASExtensionErrorDomain and an appropriate error code from ASExtensionErrorCode. For example, if the credential identity cannot
 be found in the database, pass an error with code ASExtensionErrorCodeCredentialIdentityNotFound.
 */
- (void)prepareInterfaceToProvideCredentialForIdentity:(ASPasswordCredentialIdentity *)credentialIdentity
API_DEPRECATED_WITH_REPLACEMENT("prepareInterfaceToProvideCredentialForRequest:", ios(12.0, 17.0), macos(11.0, 14.0))
    ;

/*! @abstract Prepare the view controller to show user interface for providing the user-requested credential.
 @param credentialRequest the credential request for which a credential should be provided.
 @discussion The system calls this method when your extension cannot provide the requested credential without user interaction.
 Set up the view controller for any user interaction required to provide the requested credential only. The user interaction should
 be limited in nature to operations required for providing the requested credential. An example is showing an authentication UI to
 unlock the user's passwords database.
 Call -[ASCredentialProviderExtensionContext completeRequestWithSelectedCredential:completionHandler:] for password credentials or
 -[ASCredentialProviderExtensionContext completeAssertionRequestWithSelectedPasskeyCredential:completionHandler:] for passkey credentials.
 If an error occurs, call -[ASCredentialProviderExtensionContext cancelRequestWithError:] and pass an error with domain
 ASExtensionErrorDomain and an appropriate error code from ASExtensionErrorCode. For example, if the credential identity cannot
 be found in the database, pass an error with code ASExtensionErrorCodeCredentialIdentityNotFound.
 */
- (void)prepareInterfaceToProvideCredentialForRequest:(id <ASCredentialRequest>)credentialRequest API_AVAILABLE(ios(17.0), macos(14.0)) API_UNAVAILABLE(watchos, tvos);

/*! @abstract Prepare the view controller to show user interface when the user enables your extension.
 @discussion The system calls this method after your extension is enabled by the user in Settings. You can
 use this method to give the user a chance to configure the extension or to provide credential identities
 to the system. After the configuration is done, call -[ASCredentialProviderExtensionContext completeExtensionConfigurationRequest].
 @note This method only gets called if your extension supports this functionality by specifying
 "ASCredentialProviderExtensionShowsConfigurationUI": YES in its extension attributes.
 */
- (void)prepareInterfaceForExtensionConfiguration;

/// Prepare UI to register a passkey for the specified relying party.
///
/// The system calls this method when the user selects your extension to use for creating a passkey. In order
/// for your extension to be presented in the list of options for passkey registration requests, your extension
/// needs to specify a true value for the Information Property List key `ProvidesPasskeys` under the
/// `ASCredentialProviderExtensionCapabilities` dictionary.
///
///     Info.plist
///     ├─ NSExtension
///         ├─ NSExtensionAttributes
///             ├─ ASCredentialProviderExtensionCapabilities
///                 ├─ ProvidesPasskeys => true
///
/// This method will present your extension's UI for user authentication before creating the passkey. Once the
/// passkey is created, your extension should call `-[ASCredentialProviderExtensionContext completeRegistrationRequestWithSelectedPasskeyCredential:completionHandler:]`
/// with the newly created ASPasskeyCredential object. If an error occurs, call
/// `-[ASCredentialProviderExtensionContext cancelRequestWithError:]` and pass an
/// error with domain `ASExtensionErrorDomain` and an appropriate error code from `ASExtensionErrorCode`.
///
/// - Parameter registrationRequest: The passkey registration request parameters needed to
///   register a new passkey.
- (void)prepareInterfaceForPasskeyRegistration:(id <ASCredentialRequest>)registrationRequest API_AVAILABLE(ios(17.0), macos(14.0)) API_UNAVAILABLE(watchos, tvos);

/// Perform a conditional passkey registration, if possible.
///
/// This method will be called for handling conditional passkey registration requests. A conditional passkey registration request allows
/// your extension to opportunistically register passkeys in the background, if and only if you believe the user is in a good state to do
/// so. Your extension decides can decide what conditions make sense for whether to fulfill or reject this request. For example, an
/// extension may decide to register a passkey only if all of the following conditions are met:
/// - The user's vault is currently unlocked.
/// - The user name for the registration request matches that for an existing saved password.
/// - The matching saved password was filled recently.
/// - The user does not already have a passkey for this account.
///
///
/// Fulfilling this request should not remove a user's saved password for this account, but it may mean that the passkey will be
/// preferred over the password in future AutoFill invocations, if both are supported.
///
/// Your extension should complete this request by calling `-[ASCredentialProviderExtensionContext completeRegistrationRequestWithSelectedPasskeyCredential:completionHandler:]`
/// or`-[ASCredentialProviderExtensionContext cancelRequestWithError:]`, like for standard registration requests.
/// However, this request is not allowed to show UI and `ASExtensionErrorCodeUserInteractionRequired` will be treated
/// like any other error. The intent of this API is to provide a method of performing a background registration only where easy and
/// convenient, so no blocking UI or error should ever be shown.
///
/// To indicate support for this feature, add `SupportsConditionalPasskeyRegistration` under the
/// `ASCredentialProviderExtensionCapabilities` dictionary.
///
///     Info.plist
///     ├─ NSExtension
///         ├─ NSExtensionAttributes
///             ├─ ASCredentialProviderExtensionCapabilities
///                 ├─ SupportsConditionalPasskeyRegistration => true
- (void)performPasskeyRegistrationWithoutUserInteractionIfPossible:(ASPasskeyCredentialRequest *)registrationRequest NS_SWIFT_NAME(performWithoutUserInteractionIfPossible(passkeyRegistration:)) AS_API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

/// Receive report when a relying party indicates that a passkey's user name was updated.
///
/// This method will be called for handling passkey updates when a relying party reports an update using the `ASCredentialUpdater` API.
/// This update should be handled in the background, so no blocking UI or error should ever be shown.
///
/// - Parameter relyingParty: Relying party (website) that the credential is saved for.
/// - Parameter userHandle: User identifier.
/// - Parameter newName: The new user name for the credential.
///
/// To indicate support for this feature, add `SupportsCredentialUpdate` under the
/// `ASCredentialProviderExtensionCapabilities` dictionary.
///
///     Info.plist
///     ├─ NSExtension
///         ├─ NSExtensionAttributes
///             ├─ ASCredentialProviderExtensionCapabilities
///                 ├─ SupportsCredentialUpdate => true
- (void)reportPublicKeyCredentialUpdateForRelyingParty:(NSString *)relyingParty userHandle:(NSData *)userHandle newName:(NSString *)newName;

/// Receive report when a relying party indicates an invalid passkey credential.
///
/// This method will be called for handling passkey updates when a relying party reports the credential is no longer valid using the `ASCredentialUpdater` API.
/// You may hide or remove this credential.
/// This update should be handled in the background, so no blocking UI or error should ever be shown.
///
/// - Parameter relyingParty: Relying party (website) that the credential is saved for.
/// - Parameter credentialID: An identifier that uniquely identifies the passkey.
///
/// To indicate support for this feature, add `SupportsCredentialUpdate` under the
/// `ASCredentialProviderExtensionCapabilities` dictionary.
///
///     Info.plist
///     ├─ NSExtension
///         ├─ NSExtensionAttributes
///             ├─ ASCredentialProviderExtensionCapabilities
///                 ├─ SupportsCredentialUpdate => true
- (void)reportUnknownPublicKeyCredentialForRelyingParty:(NSString *)relyingParty credentialID:(NSData *)credentialID;

/// Receive report when relying party sends a snapshot of all the accepted credentials for an account.
///
/// This method will be called for handling passkey updates when a relying party sends a list of accepted credentials using the `ASCredentialUpdater` API.
/// You may hide or remove any credential not present in the accepted credentials list.
/// This update should be handled in the background, so no blocking UI or error should ever be shown.
///
/// - Parameter relyingParty: Relying party (website) that the credential is saved for.
/// - Parameter userHandle: User identifier.
/// - Parameter acceptedCredentialIDs: An array of identifiers that uniquely identifies the accepted credentials.
///
/// To indicate support for this feature, add `SupportsCredentialUpdate` under the
/// `ASCredentialProviderExtensionCapabilities` dictionary.
///
///     Info.plist
///     ├─ NSExtension
///         ├─ NSExtensionAttributes
///             ├─ ASCredentialProviderExtensionCapabilities
///                 ├─ SupportsCredentialUpdate => true
- (void)reportAllAcceptedPublicKeyCredentialsForRelyingParty:(NSString *)relyingParty userHandle:(NSData *)userHandle acceptedCredentialIDs:(NSArray<NSData *> *)acceptedCredentialIDs;

/// Receive report when relying party indicates a password credential is no longer needed for a given user name.
///
/// This method will be called for handling password credential updates when a relying party indicates a password is no longer needed using the `ASCredentialUpdater` API.
/// You may hide or remove the credential.
/// This update should be handled in the background, so no blocking UI or error should ever be shown.
///
/// - Parameter domain: The website domain that the credential is saved for.
/// - Parameter userName: The account user name.
///
/// To indicate support for this feature, add `SupportsCredentialUpdate` under the
/// `ASCredentialProviderExtensionCapabilities` dictionary.
///
///     Info.plist
///     ├─ NSExtension
///         ├─ NSExtensionAttributes
///             ├─ ASCredentialProviderExtensionCapabilities
///                 ├─ SupportsCredentialUpdate => true
- (void)reportUnusedPasswordCredentialForDomain:(NSString *)domain userName:(NSString *)userName;

/// Attempt to save a password credential.
///
/// To return results, you must call  ``ASCredentialProviderExtensionContext/completeSavePasswordRequest(completionHandler:)``.
/// - Parameter request: The request to save a password.
/// - Note: When this method is called, your extension's view controller is not present on the screen.
/// You can request user interaction by calling ``ASCredentialProviderExtensionContext/cancelRequest(with:)``, using ``ASExtensionError/userInteractionRequired``.
///
/// To indicate support for this feature, add `SupportsSavePasswordCredentials` under the
/// `ASCredentialProviderExtensionCapabilities` dictionary.
///
///     Info.plist
///     ├─ NSExtension
///         ├─ NSExtensionAttributes
///             ├─ ASCredentialProviderExtensionCapabilities
///                 ├─ SupportsSavePasswordCredentials => true
- (void)performSavePasswordRequestWithoutUserInteractionIfPossible:(ASSavePasswordRequest *)savePasswordRequest
    NS_SWIFT_NAME(performWithoutUserInteractionIfPossible(savePasswordRequest:))
    API_AVAILABLE(ios(26.2), visionos(26.2))
    API_UNAVAILABLE(macos, tvos, watchos);

/// Prepares the interface to display a prompt to save a password credential.
///
/// The system calls this method to tell your extension’s view controller to prepare to present a prompt to save a password credential.
/// After calling this method, the system presents the view controller to the user.
///
/// Upon success, call ``ASCredentialProviderExtensionContext/completeSavePasswordRequest(completionHandler:)``.
///
/// Always provide a way for someone to cancel the operation from your view controller, for example, by including a Cancel button in the navigation bar.
/// When someone cancels the operation, call ``ASCredentialProviderExtensionContext/cancelRequest(with:)``, using ``ASExtensionError/userCanceled``.
/// - Parameter request: The request to save a password.
- (void)prepareInterfaceForSavePasswordRequest:(ASSavePasswordRequest *)savePasswordRequest
    NS_SWIFT_NAME(prepareInterface(for:))
    API_AVAILABLE(ios(26.2), visionos(26.2))
    API_UNAVAILABLE(macos, tvos, watchos);

/// Attempt to generate passwords based on developer-specified rules.
///
/// To return results, you must call ``ASCredentialProviderExtensionContext/completeGeneratePasswordRequest(results:completionHandler:)`.
/// - Parameter request: The request to generate a password.
/// - Note: When this method is called, your extension's view controller is not present on the screen.
/// ``ASExtensionError/userInteractionRequired`` will not be honored and treated as a failure.
/// - Note: You should not update or replace any existing credentials when this API is called.
///
/// To indicate support for this feature, add `SupportsGeneratePasswordCredentials` under the
/// `ASCredentialProviderExtensionCapabilities` dictionary.
///
///     Info.plist
///     ├─ NSExtension
///         ├─ NSExtensionAttributes
///             ├─ ASCredentialProviderExtensionCapabilities
///                 ├─ SupportsSavePasswordCredentials => true
///                 ├─ SupportsGeneratePasswordCredentials => true
- (void)performGeneratePasswordsRequestWithoutUserInteraction:(ASGeneratePasswordsRequest *)generatePasswordsRequest
    NS_SWIFT_NAME(performWithoutUserInteraction(generatePasswordsRequest:))
    API_AVAILABLE(ios(26.2), visionos(26.2))
    API_UNAVAILABLE(macos, tvos, watchos);

/// Prepares the interface to display a prompt to generate passwords based on developer-specified rules.
///
/// The system calls this method to tell your extension’s view controller to prepare to present a prompt to generate passwords.
/// After calling this method, the system presents the view controller to the user.
///
/// Upon success, call ``ASCredentialProviderExtensionContext/completeGeneratePasswordRequest(results:completionHandler:)``.
///
/// Always provide a way for someone to cancel the operation from your view controller, for example, by including a Cancel button in the navigation bar.
/// When someone cancels the operation, call ``ASCredentialProviderExtensionContext/cancelRequest(with:)``, using ``ASExtensionError/userCanceled``.
/// - Parameter request: The request to generate a password.
/// - Note: This flow can only be initiated by the user. It will not be triggered from `-performGeneratePasswordsRequestWithoutUserInteraction:`
/// - Note: You should not update or replace any existing credentials when this API is called.
///
/// Support of this feature is implied by default when adding support for generating passwords.
/// You can opt out of showing UI by adding the `SupportsGeneratePasswordCredentialsWithUI` under the
/// `ASCredentialProviderExtensionCapabilities` dictionary.
/// When opting out, you must provide a value of `false` as the default value for this field is `true`.
/// When you opt out, the OS will provide a relevant experience after requesting generated passwords from your extension.
///
///     Info.plist
///     ├─ NSExtension
///         ├─ NSExtensionAttributes
///             ├─ ASCredentialProviderExtensionCapabilities
///                 ├─ SupportsSavePasswordCredentials => true
///                 ├─ SupportsGeneratePasswordCredentials => true
///                 ├─ SupportsGeneratePasswordCredentialsWithUI => true
- (void)prepareInterfaceForGeneratePasswordsRequest:(ASGeneratePasswordsRequest *)generatePasswordsRequest
    NS_SWIFT_NAME(prepareInterface(for:))
    API_AVAILABLE(ios(26.2), visionos(26.2))
    API_UNAVAILABLE(macos, tvos, watchos);

@end

NS_ASSUME_NONNULL_END
