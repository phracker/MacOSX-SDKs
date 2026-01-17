//
//  ACAccountType.h
//  Accounts
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accounts/AccountsDefines.h>

// The identifiers for supported system account types are listed here:
ACCOUNTS_EXTERN NSString * const ACAccountTypeIdentifierTwitter NS_DEPRECATED(10_8, 10_13, 5_0, 11_0, "Use Twitter SDK instead");
ACCOUNTS_EXTERN NSString * const ACAccountTypeIdentifierFacebook NS_DEPRECATED(10_8, 10_13, NA, 11_0, "Use Facebook SDK instead");
ACCOUNTS_EXTERN NSString * const ACAccountTypeIdentifierSinaWeibo NS_DEPRECATED(10_8, 10_13, NA, 11_0, "Use Sina Weibo SDK instead");
ACCOUNTS_EXTERN NSString * const ACAccountTypeIdentifierTencentWeibo NS_DEPRECATED(10_9, 10_13, NA, 11_0, "Use Tencent Weibo SDK instead");
ACCOUNTS_EXTERN NSString * const ACAccountTypeIdentifierLinkedIn NS_DEPRECATED(10_9, 10_13, NA, NA, "Use LinkedIn SDK instead");

// Options dictionary keys for Facebook access, for use with [ACAccountStore requestAccessToAccountsWithType:options:completion:]
ACCOUNTS_EXTERN NSString * const ACFacebookAppIdKey NS_DEPRECATED(10_8, 10_13, NA, 11_0, "Use Facebook SDK instead");            // Your Facebook App ID, as it appears on the Facebook website.
ACCOUNTS_EXTERN NSString * const ACFacebookPermissionsKey NS_DEPRECATED(10_8, 10_13, NA, 11_0, "Use Facebook SDK instead");      // An array of of the permissions you're requesting.
ACCOUNTS_EXTERN NSString * const ACFacebookAudienceKey NS_DEPRECATED(10_8, 10_13, NA, 11_0, "Use Facebook SDK instead");         // Only required when posting permissions are requested.

// Options dictionary values for Facebook access, for use with [ACAccountStore requestAccessToAccountsWithType:options:completion:]
ACCOUNTS_EXTERN NSString * const ACFacebookAudienceEveryone NS_DEPRECATED(10_8, 10_13, NA, 11_0, "Use Facebook SDK instead");    // Posts from your app are visible to everyone.
ACCOUNTS_EXTERN NSString * const ACFacebookAudienceFriends NS_DEPRECATED(10_8, 10_13, NA, 11_0, "Use Facebook SDK instead");     // Posts are visible only to friends.
ACCOUNTS_EXTERN NSString * const ACFacebookAudienceOnlyMe NS_DEPRECATED(10_8, 10_13, NA, 11_0, "Use Facebook SDK instead");      // Posts are visible to the user only.

// Options dictionary keys for LinkedIn access, for use with [ACAccountStore requestAccessToAccountsWithType:options:completion:]
ACCOUNTS_EXTERN NSString * const ACLinkedInAppIdKey NS_DEPRECATED(10_9, 10_13, NA, NA, "Use LinkedIn SDK instead");           // Your LinkedIn App ID (or API Key), as it appears on the LinkedIn website.
ACCOUNTS_EXTERN NSString * const ACLinkedInPermissionsKey NS_DEPRECATED(10_9, 10_13, NA, NA, "Use LinkedIn SDK instead");      // An array of of the LinkedIn permissions you're requesting.

ACCOUNTS_EXTERN NSString *const ACTencentWeiboAppIdKey NS_DEPRECATED(10_9, 10_13, NA, 11_0, "Use Tencent Weibo SDK instead"); //Tencent App ID

// Each account has an associated account type, containing information relevant to all the accounts of that type.
// ACAccountType objects are obtained by using the [ACAccountStore accountTypeWithIdentifier:] method
// or accessing the accountType property for a particular account object. They may also be used to find
// all the accounts of a particular type using [ACAccountStore accountsWithAccountType:]

ACCOUNTS_CLASS_AVAILABLE(10_8, 5_0)
@interface ACAccountType : NSObject

// A human readable description of the account type.
@property (readonly, nonatomic) NSString *accountTypeDescription;

// A unique identifier for the account type. Well known system account type identifiers are listed above.
@property (readonly, nonatomic) NSString *identifier;

// A boolean indicating whether the user has granted access to accounts of this type for your application.
@property (readonly, nonatomic) BOOL     accessGranted;

@end
