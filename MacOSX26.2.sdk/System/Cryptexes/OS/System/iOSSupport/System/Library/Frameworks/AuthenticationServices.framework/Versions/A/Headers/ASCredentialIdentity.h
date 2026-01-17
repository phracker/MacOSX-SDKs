//
//  ASCredentialIdentity.h
//  AuthenticationServices Framework
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class ASCredentialServiceIdentifier;

/*! @protocol ASCredentialIdentity
 An ASCredentialIdentity is used to describe an identity that can use a service upon successful authentication.
 Use this class to save entries into ASCredentialIdentityStore.
 */
AS_EXTERN API_AVAILABLE(ios(17.0), macos(14.0)) API_UNAVAILABLE(tvos, watchos)
@protocol ASCredentialIdentity <NSObject>

/*! @abstract Get the service identifier.
 */
@property (nonatomic, readonly, strong) ASCredentialServiceIdentifier *serviceIdentifier;

/*! @abstract Get the user.
 */
@property (nonatomic, readonly, copy) NSString *user;

/*! @abstract Get the record identifier.
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

