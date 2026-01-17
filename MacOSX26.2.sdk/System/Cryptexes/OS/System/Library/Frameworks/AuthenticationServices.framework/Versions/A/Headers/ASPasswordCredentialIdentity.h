//
//  ASPasswordCredentialIdentity.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

#import <AuthenticationServices/ASCredentialIdentity.h>

NS_ASSUME_NONNULL_BEGIN

@class ASCredentialServiceIdentifier;

/*! @class ASPasswordCredentialIdentity
 An ASPasswordCredentialIdentity is used to describe an identity that can use a service upon successful password based authentication.
 Use this class to save entries into ASCredentialIdentityStore.
 */
AS_EXTERN API_AVAILABLE(ios(12.0), macCatalyst(14.0), macos(11.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASPasswordCredentialIdentity : NSObject <NSCopying, NSSecureCoding, ASCredentialIdentity>

- (instancetype)init NS_UNAVAILABLE;

/*! @abstract Initializes an instance of ASPasswordCredentialIdentity.
 @param serviceIdentifier the service identifier for which this credential identity is valid.
 @param user the user that can authenticate into the service indicated by the serviceIdentifier.
 @param recordIdentifier an optional string to uniquely identify this record in your local database.
 */
- (instancetype)initWithServiceIdentifier:(ASCredentialServiceIdentifier *)serviceIdentifier user:(NSString *)user recordIdentifier:(nullable NSString *)recordIdentifier NS_DESIGNATED_INITIALIZER;

/*! @abstract Creates and initializes an instance of ASPasswordCredentialIdentity.
 @param serviceIdentifier the service identifier for which this credential identity is valid.
 @param user the user that can authenticate into the service indicated by the serviceIdentifier.
 @param recordIdentifier an optional string to uniquely identify this record in your local database.
 */
+ (instancetype)identityWithServiceIdentifier:(ASCredentialServiceIdentifier *)serviceIdentifier user:(NSString *)user recordIdentifier:(nullable NSString *)recordIdentifier;

/*! @abstract Get the service identifier.
 @result The service identifier for this credential identity.
 */
@property (nonatomic, readonly, strong) ASCredentialServiceIdentifier *serviceIdentifier;

/*! @abstract Get the user.
 @result The user string.
 */
@property (nonatomic, readonly, copy) NSString *user;

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
