//
//  ACAccountType.h
//  Accounts
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accounts/AccountsDefines.h>

// The identifiers for supported system account types are listed here:
ACCOUNTS_EXTERN NSString * const ACAccountTypeIdentifierTwitter API_DEPRECATED("Use Twitter SDK instead", ios(5.0, 11.0), macos(10.8, 10.13));
ACCOUNTS_EXTERN NSString * const ACAccountTypeIdentifierFacebook API_DEPRECATED("Use Facebook SDK instead", ios(6.0, 11.0), macos(10.8, 10.13));
ACCOUNTS_EXTERN NSString * const ACAccountTypeIdentifierSinaWeibo API_DEPRECATED("Use Sina Weibo SDK instead", ios(6.0, 11.0), macos(10.8, 10.13));
ACCOUNTS_EXTERN NSString * const ACAccountTypeIdentifierTencentWeibo API_DEPRECATED("Use Tencent Weibo SDK instead", ios(7.0, 11.0), macos(10.9, 10.13));
ACCOUNTS_EXTERN NSString * const ACAccountTypeIdentifierLinkedIn API_DEPRECATED("Use LinkedIn SDK instead", macos(10.9, 10.13)) API_UNAVAILABLE(ios);

// Options dictionary keys for Facebook access, for use with [ACAccountStore requestAccessToAccountsWithType:options:completion:]
ACCOUNTS_EXTERN NSString * const ACFacebookAppIdKey API_DEPRECATED("Use Facebook SDK instead", ios(6.0, 11.0), macos(10.8, 10.13)); // Your Facebook App ID, as it appears on the Facebook website.
ACCOUNTS_EXTERN NSString * const ACFacebookPermissionsKey API_DEPRECATED("Use Facebook SDK instead", ios(6.0, 11.0), macos(10.8, 10.13)); // An array of of the permissions you're requesting.
ACCOUNTS_EXTERN NSString * const ACFacebookAudienceKey API_DEPRECATED("Use Facebook SDK instead", ios(6.0, 11.0), macos(10.8, 10.13)); // Only required when posting permissions are requested.

// Options dictionary values for Facebook access, for use with [ACAccountStore requestAccessToAccountsWithType:options:completion:]
ACCOUNTS_EXTERN NSString * const ACFacebookAudienceEveryone API_DEPRECATED("Use Facebook SDK instead", ios(6.0, 11.0), macos(10.8, 10.13)); // Posts from your app are visible to everyone.
ACCOUNTS_EXTERN NSString * const ACFacebookAudienceFriends API_DEPRECATED("Use Facebook SDK instead", ios(6.0, 11.0), macos(10.8, 10.13)); // Posts are visible only to friends.
ACCOUNTS_EXTERN NSString * const ACFacebookAudienceOnlyMe API_DEPRECATED("Use Facebook SDK instead", ios(6.0, 11.0), macos(10.8, 10.13)); // Posts are visible to the user only.

// Options dictionary keys for LinkedIn access, for use with [ACAccountStore requestAccessToAccountsWithType:options:completion:]
ACCOUNTS_EXTERN NSString * const ACLinkedInAppIdKey API_DEPRECATED("Use LinkedIn SDK instead", macos(10.9, 10.13)) API_UNAVAILABLE(ios); // Your LinkedIn App ID (or API Key), as it appears on the LinkedIn website.
ACCOUNTS_EXTERN NSString * const ACLinkedInPermissionsKey API_DEPRECATED("Use LinkedIn SDK instead", macos(10.9, 10.13)) API_UNAVAILABLE(ios); // An array of of the LinkedIn permissions you're requesting.

ACCOUNTS_EXTERN NSString * const ACTencentWeiboAppIdKey API_DEPRECATED("Use Tencent Weibo SDK instead", ios(7.0, 11.0), macos(10.9, 10.13)); // Tencent App ID

// Each account has an associated account type, containing information relevant to all the accounts of that type.
// ACAccountType objects are obtained by using the [ACAccountStore accountTypeWithIdentifier:] method
// or accessing the accountType property for a particular account object. They may also be used to find
// all the accounts of a particular type using [ACAccountStore accountsWithAccountType:]


API_DEPRECATED("Use appropriate non-Apple SDK corresponding to the type of account you want to reference instead", ios(6.0, 15.0), macos(10.8, 12.0))

@interface ACAccountType : NSObject

// A human readable description of the account type.
@property (readonly, nonatomic) NSString *accountTypeDescription;

// A unique identifier for the account type. Well known system account type identifiers are listed above.
@property (readonly, nonatomic) NSString *identifier;

// A boolean indicating whether the user has granted access to accounts of this type for your application.
@property (readonly, nonatomic) BOOL     accessGranted;

@end
