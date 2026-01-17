//
//  ASSavePasswordRequest.h
//  AuthenticationServices Framework
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//


#import <AuthenticationServices/ASCredentialServiceIdentifier.h>
#import <AuthenticationServices/ASPasswordCredential.h>

#import <AuthenticationServices/ASGeneratedPasswordKind.h>

AS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, ASSavePasswordRequestEvent) {
    /// The save event that occurs when a user has expressly stated they wish to save the credential.
    ///
    /// The expected behavior is to save "new" or "updated" credentials.
    ///
    /// Providers may request any additional information from the user necessary to support the save operation.
    ASSavePasswordRequestEventUserInitiated,
    /// The save event that occurs when a form is submitted or removed from the screen without prompting the user.
    ///
    /// The recommended behavior is to save "new" credentials, and ask the user if they wish to overwrite "updated" credentials.
    ///
    /// Providers may request any additional information from the user necessary to support the save operation.
    ASSavePasswordRequestEventFormDidDisappear,
    /// A save event that occurs when generated password is filled into a not yet submitted form.
    ///
    /// The recommended behavior is to save "new" credentials as pending accounts.
    /// This event will generally be followed by a userInitiated or formDidDisappear event.
    ///
    /// Providers should not request any additional information from the user as that will not be transmitted back to the form.
    ASSavePasswordRequestEventGeneratedPasswordFilled,
}
API_AVAILABLE(ios(26.2), visionos(26.2))
API_UNAVAILABLE(macos, tvos, watchos)
NS_SWIFT_NAME(ASSavePasswordRequest.Event);

AS_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.2), visionos(26.2))
API_UNAVAILABLE(macos, tvos, watchos)
@interface ASSavePasswordRequest : NSObject <NSCopying, NSSecureCoding>

/// The identifier of the service for which the the credential should be associated.
@property (nonatomic, readonly) ASCredentialServiceIdentifier *serviceIdentifier;

/// The credential to save.
@property (nonatomic, readonly) ASPasswordCredential *credential;

/// A user-displayable name for the password credential to be saved.
///
/// This is independent of the service identifier and should be used for identifying the individual credential.
@property (nonatomic, readonly, nullable) NSString *title;

/// An ID that represents a form's session.
@property (nonatomic, readonly) NSString *sessionID;

/// The type of event that the save request represents.
@property (nonatomic, readonly) ASSavePasswordRequestEvent event;

/// For passwordFilled events, this is the kind of password that was created.
@property (nonatomic, readonly, nullable) ASGeneratedPasswordKind passwordKind;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithServiceIdentifier:(ASCredentialServiceIdentifier *)serviceIdentifier credential:(ASPasswordCredential *)credential sessionID:(NSString *)sessionID event:(ASSavePasswordRequestEvent)event;

- (instancetype)initWithServiceIdentifier:(ASCredentialServiceIdentifier *)serviceIdentifier credential:(ASPasswordCredential *)credential title:(nullable NSString *)title sessionID:(NSString *)sessionID event:(ASSavePasswordRequestEvent)event;

- (instancetype)initWithServiceIdentifier:(ASCredentialServiceIdentifier *)serviceIdentifier credential:(ASPasswordCredential *)credential sessionID:(NSString *)sessionID event:(ASSavePasswordRequestEvent)event passwordKind:(nullable ASGeneratedPasswordKind)passwordKind;

- (instancetype)initWithServiceIdentifier:(ASCredentialServiceIdentifier *)serviceIdentifier credential:(ASPasswordCredential *)credential title:(nullable NSString *)title sessionID:(NSString *)sessionID event:(ASSavePasswordRequestEvent)event passwordKind:(nullable ASGeneratedPasswordKind)passwordKind;

@end

AS_HEADER_AUDIT_END(nullability, sendability)

