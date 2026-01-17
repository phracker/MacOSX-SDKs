//
//  ASOneTimeCodeCredentialIdentity.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASCredentialIdentity.h>
#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class ASCredentialServiceIdentifier;

/*! @class ASOneTimeCodeCredentialIdentity
 An ASOneTimeCodeCredentialIdentity is used to describe an identity that can use a service upon successful one time code based authentication.
 Use this class to save entries into ASCredentialIdentityStore.
 */
AS_EXTERN API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASOneTimeCodeCredentialIdentity : NSObject<NSCopying, NSSecureCoding, ASCredentialIdentity>

- (instancetype)init NS_UNAVAILABLE;

/*! @abstract Initializes an instance of ASOneTimeCodeCredentialIdentity.
 @param serviceIdentifier The service identifier for which this credential identity is valid.
 @param label A user-provided label to identify the one time code.
 @param recordIdentifier An optional string to uniquely identify this record in your local database.
 */
- (instancetype)initWithServiceIdentifier:(ASCredentialServiceIdentifier *)serviceIdentifier label:(NSString *)label recordIdentifier:(nullable NSString *)recordIdentifier;

/*! @abstract A label to identify the one time code, typically supplied by the user.
 This string will be shown in the AutoFill suggestion for this one time code credential.
 */
@property (nonatomic, readonly, copy) NSString *label;

@end

NS_ASSUME_NONNULL_END

