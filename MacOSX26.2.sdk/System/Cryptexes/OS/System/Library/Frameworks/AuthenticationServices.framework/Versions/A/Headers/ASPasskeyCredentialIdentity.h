//
//  ASPasskeyCredentialIdentity.h
//  AuthenticationServices Framework
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASCredentialIdentity.h>
#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class ASPasskeyCredentialIdentity
 An ASPasswordCredentialIdentity is used to describe an identity that can use a service upon successful passkey based authentication.
 Use this class to save entries into ASCredentialIdentityStore.
 */
AS_EXTERN API_AVAILABLE(ios(17.0), macos(14.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASPasskeyCredentialIdentity : NSObject <NSCopying, NSSecureCoding, ASCredentialIdentity>

- (instancetype)init NS_UNAVAILABLE;

/*! @abstract Initialize an instance of ASPasskeyCredentialIdentity.
 @param relyingPartyIdentifier relying party for this credential.
 @param userName user name associated with this credential.
 @param credentialID credential ID of this passkey credential.
 @param userHandle user handle data of this passkey credential.
 @param recordIdentifier identifier used by credential provider extension to identify this credential.
 */
- (instancetype)initWithRelyingPartyIdentifier:(NSString *)relyingPartyIdentifier userName:(NSString *)userName credentialID:(NSData *)credentialID userHandle:(NSData *)userHandle recordIdentifier:(nullable NSString *)recordIdentifier NS_REFINED_FOR_SWIFT;

/*! @abstract Create and initialize an instance of ASPasskeyCredentialIdentity.
 @param relyingPartyIdentifier relying party for this credential.
 @param userName user name associated with this credential.
 @param credentialID credential ID of this passkey credential.
 @param userHandle user handle data of this passkey credential.
 @param recordIdentifier identifier used by credential provider extension to identify this credential.
 */
+ (instancetype)identityWithRelyingPartyIdentifier:(NSString *)relyingPartyIdentifier userName:(NSString *)userName credentialID:(NSData *)credentialID userHandle:(NSData *)userHandle recordIdentifier:(nullable NSString *)recordIdentifier;

/*! @abstract The relying party identifier of this passkey credential.
 @discussion This field is reported as the serviceIdentifier property of ASCredentialIdentity.
 */
@property (nonatomic, readonly, copy) NSString *relyingPartyIdentifier;

/*! @abstract The user name of this passkey credential.
 @discussion This field is reported as the user property of ASCredentialIdentity.
 */
@property (nonatomic, readonly, copy) NSString *userName;

/*! @abstract The credential ID of this passkey credential.
 @discussion This field is used to identify the correct credential to use based on relying party request parameters.
 */
@property (nonatomic, readonly, copy) NSData *credentialID;

/*! @abstract The user handle of this passkey credential.
 @discussion This field is used to identify the correct credential to use based on relying party request parameters. 
 */
@property (nonatomic, readonly, copy) NSData *userHandle;

/*! @abstract Get the record identifier.
 @result The record identifier.
 @discussion You can utilize the record identifier to uniquely identify the credential identity in your local database.
 */
@property (nonatomic, readonly, copy, nullable) NSString *recordIdentifier;

/*! @abstract Get or set the rank of the credential identity object.
 @discussion The system may utilize the rank to decide which credential identity precedes the other
 if two identities have the same service identifier. A credential identity with a larger rank value
 precedes one with a smaller value if both credential identities have the same service identifier.
 The default value of this property is 0.
 */
@property (nonatomic) NSInteger rank;

@end

NS_ASSUME_NONNULL_END
