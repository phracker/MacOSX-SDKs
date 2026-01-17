//
//  ASOneTimeCodeCredential.h
//  AuthenticationServices Framework
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorizationCredential.h>
#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASOneTimeCodeCredential : NSObject <ASAuthorizationCredential>

- (instancetype)init NS_UNAVAILABLE;

/*! @abstract Creates and initializes a new ASOneTimeCodeCredential object.
 @param code the one time code.
 */
+ (instancetype)credentialWithCode:(NSString *)code;

/*! @abstract Initializes an ASOneTimeCodeCredential object.
 @param code the one time code.
 */
- (instancetype)initWithCode:(NSString *)code NS_DESIGNATED_INITIALIZER;

/*! @abstract The code of this credential.
 @result The code string.
 */
@property (nonatomic, readonly, copy) NSString *code;

@end

NS_ASSUME_NONNULL_END

