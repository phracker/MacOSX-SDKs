//
//  ACAccountType.h
//  Accounts
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accounts/AccountsDefines.h>

// The identifiers for supported system account types are listed here:
ACCOUNTS_EXTERN NSString * const ACAccountTypeIdentifierTwitter NS_AVAILABLE(10_8, 5_0);
ACCOUNTS_EXTERN NSString * const ACAccountTypeIdentifierFacebook NS_AVAILABLE(10_8, NA);
ACCOUNTS_EXTERN NSString * const ACAccountTypeIdentifierSinaWeibo NS_AVAILABLE(10_8, NA);

// Each account has an associated account type, containing information relevant to all the accounts of that type.
// ACAccountType objects are obtained by using the [ACAccountStore accountTypeWithIdentifier:] method
// or accessing the accountType property for a particular account object. They may also be used to find
// all the accounts of a particular type using [ACAccountStore accountsWithAccountType:]

ACCOUNTS_CLASS_AVAILABLE(10_8, 5_0)
@interface ACAccountType : NSObject

// A human readable description of the account type.
@property (readonly, NS_NONATOMIC_IOSONLY) NSString *accountTypeDescription;

// A unique identifier for the account type. Well known system account type identifiers are listed above.
@property (readonly, NS_NONATOMIC_IOSONLY) NSString *identifier;

// A boolean indicating whether the user has granted access to accounts of this type for your application.
@property (readonly, NS_NONATOMIC_IOSONLY) BOOL     accessGranted;

@end
