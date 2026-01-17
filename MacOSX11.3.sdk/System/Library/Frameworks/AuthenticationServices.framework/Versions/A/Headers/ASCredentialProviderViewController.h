//
//  ASCredentialProviderViewController.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASCredentialProviderExtensionContext.h>
#import <AuthenticationServices/ASCredentialServiceIdentifier.h>
#import <AuthenticationServices/ASFoundation.h>
#import <AuthenticationServices/ASPasswordCredentialIdentity.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

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
- (void)provideCredentialWithoutUserInteractionForIdentity:(ASPasswordCredentialIdentity *)credentialIdentity;

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
- (void)prepareInterfaceToProvideCredentialForIdentity:(ASPasswordCredentialIdentity *)credentialIdentity;

/*! @abstract Prepare the view controller to show user interface when the user enables your extension.
 @discussion The system calls this method after your extension is enabled by the user in Settings. You can
 use this method to give the user a chance to configure the extension or to provide credential identities
 to the system. After the configuration is done, call -[ASCredentialProviderExtensionContext completeExtensionConfigurationRequest].
 @note This method only gets called if your extension supports this functionality by specifying
 "ASCredentialProviderExtensionShowsConfigurationUI": YES in its extension attributes.
 */
- (void)prepareInterfaceForExtensionConfiguration;

@end

NS_ASSUME_NONNULL_END
