//
//  ACAccountCredential.h
//  Accounts
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accounts/AccountsDefines.h>

// An existing credential may be provided when creating an account.
// For example, to create a system Twitter account using an existing OAuth token/secret pair:
//
// 1. Create the new account instance.
// 2. Set the account type.
// 3. Create an ACAccountCredential using your existing OAuth token/secret and set the account's credential property.
// 4. Save the account.
//
// The account will be validated and saved as a system account.

API_AVAILABLE(ios(5.0), macos(10.8))
@interface ACAccountCredential : NSObject

- (instancetype)initWithOAuthToken:(NSString *)token tokenSecret:(NSString *)secret;

- (instancetype)initWithOAuth2Token:(NSString *)token 
                       refreshToken:(NSString *)refreshToken
                         expiryDate:(NSDate *)expiryDate;

// This property is only valid for OAuth2 credentials
@property (copy, nonatomic) NSString *oauthToken;

@end
