//
//  ASPasswordCredential.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <AuthenticationServices/ASAuthorizationCredential.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(12.0), macos(10.15), tvos(13.0), watchos(6.0))
@interface ASPasswordCredential : NSObject <ASAuthorizationCredential>

/*! @abstract Initializes an ASPasswordCredential object.
 @param user the user.
 @param password the password.
 */
- (instancetype)initWithUser:(NSString *)user password:(NSString *)password;

/*! @abstract Creates and initializes a new ASPasswordCredential object.
 @param user the user.
 @param password the password.
 */
+ (instancetype)credentialWithUser:(NSString *)user password:(NSString *)password;

/*! @abstract The user name of this credential.
 @result The user string.
 */
@property (nonatomic, copy, readonly) NSString *user;

/*! @abstract The password of this credential.
 @result The password string.
 */
@property (nonatomic, copy, readonly) NSString *password;

@end

NS_ASSUME_NONNULL_END
