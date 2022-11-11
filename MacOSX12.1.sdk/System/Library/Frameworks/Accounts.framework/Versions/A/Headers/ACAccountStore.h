//
//  ACAccountStore.h
//  Accounts
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accounts/AccountsDefines.h>

typedef NS_ENUM(NSInteger, ACAccountCredentialRenewResult) {
    ACAccountCredentialRenewResultRenewed,  // A new credential was obtained and is now associated with the account.
    ACAccountCredentialRenewResultRejected, // Renewal failed because of a user-initiated action.
    ACAccountCredentialRenewResultFailed,   // A non-user-initiated cancel of the prompt. 
};

typedef void(^ACAccountStoreSaveCompletionHandler)(BOOL success, NSError *error);
typedef void(^ACAccountStoreRemoveCompletionHandler)(BOOL success, NSError *error);
typedef void(^ACAccountStoreRequestAccessCompletionHandler)(BOOL granted, NSError *error);
typedef void(^ACAccountStoreCredentialRenewalHandler)(ACAccountCredentialRenewResult renewResult, NSError *error);

@class ACAccount, ACAccountType;

// The ACAccountStore class provides an interface for accessing and manipulating
// accounts. You must create an ACAccountStore object to retrieve, add and delete
// accounts from the Accounts database.
//
// IMPORTANT NOTE: You MUST keep the account store around for as long as you have
// any objects fetched from that store if you expect other 'sub-fetches' to work,
// most notably being fetching credentials. If you really just want to open the
// store to grab credentials, just be sure to grab the credential object and then
// you can release the owning account and store, e.g.
//
// WARNING: All synchronous methods on ACAccountStore invoke xpc methods
// on accountsd. They are not appropriate to call on a UI Application's main thread.


API_DEPRECATED("Use appropriate non-Apple SDK corresponding to the type of account you want to reference instead", ios(6.0, 15.0), macos(10.8, 12.0))

@interface ACAccountStore : NSObject

// An array of all the accounts in an account database
// WARNING: Synchronous, not appropriate to call on a UI Application's main thread
@property (readonly, weak, NS_NONATOMIC_IOSONLY) NSArray *accounts;

// Returns the account matching the given account identifier
// WARNING: Synchronous, not appropriate to call on a UI Application's main thread
- (ACAccount *)accountWithIdentifier:(NSString *)identifier;

// Returns the account type object matching the account type identifier. See
// ACAccountType.h for well known account type identifiers
// WARNING: Synchronous, not appropriate to call on a UI Application's main thread
- (ACAccountType *)accountTypeWithAccountTypeIdentifier:(NSString *)typeIdentifier;

// Returns the accounts matching a given account type.
// WARNING: Synchronous, not appropriate to call on a UI Application's main thread
- (NSArray *)accountsWithAccountType:(ACAccountType *)accountType;

// Saves the account to the account database. If the account is unauthenticated and the associated account
// type supports authentication, the system will attempt to authenticate with the credentials provided.
// Assuming a successful authentication, the account will be saved to the account store. The completion handler
// for this method is called on an arbitrary queue.
- (void)saveAccount:(ACAccount *)account withCompletionHandler:(ACAccountStoreSaveCompletionHandler)completionHandler;

// DEPRECATED: Please use requestAccessToAccountsWithType:options:completion: instead.
- (void)requestAccessToAccountsWithType:(ACAccountType *)accountType withCompletionHandler:(ACAccountStoreRequestAccessCompletionHandler)handler API_DEPRECATED_WITH_REPLACEMENT("-requestAccessToAccountsWithType:options:completion:", ios(5.0, 6.0)) API_UNAVAILABLE(macos);

// Obtains permission, if necessary, from the user to access protected properties, and utilize accounts
// of a particular type in protected operations, for example OAuth signing. The completion handler for 
// this method is called on an arbitrary queue.
// Certain account types (such as Facebook) require an options dictionary. A list of the required keys
// appears in ACAccountType.h. This method will throw an NSInvalidArgumentException if the options
// dictionary is not provided for such account types. Conversely, if the account type does not require
// an options dictionary, the options parameter must be nil.
- (void)requestAccessToAccountsWithType:(ACAccountType *)accountType options:(NSDictionary *)options completion:(ACAccountStoreRequestAccessCompletionHandler)completion;

// Call this if you discover that an ACAccount's credential is no longer valid.
// For Twitter and Sina Weibo accounts, this method will prompt the user to go to Settings to re-enter their password.
// For Facebook accounts, if your access token became invalid due to regular expiration, this method will obtain a new one.
// However, if the user has deauthorized your app, this renewal request will return ACAccountCredentialRenewResultRejected.
- (void)renewCredentialsForAccount:(ACAccount *)account completion:(ACAccountStoreCredentialRenewalHandler)completionHandler;

// Removes an account from the account store. The completion handler for this method is called on an arbitrary queue.
// This call will fail if you don't have sufficient rights to remove the account in question.
- (void)removeAccount:(ACAccount *)account withCompletionHandler:(ACAccountStoreRemoveCompletionHandler)completionHandler;

@end

// Notification name sent out when the database is changed by an external process, another account store
// in the same process or by calling saveAccount: or removeAccount: on a store you are managing.
// You may need to deal with accounts being removed by an external process while you are using them.
// Note: ensure when you add an observer for this notification, you do so specifying this object specifically.
// Otherwise, you will receive n notifications, one per active ACAccountStore instance in your process.
ACCOUNTS_EXTERN NSString * const ACAccountStoreDidChangeNotification API_DEPRECATED("Public notification deprecated. Internal clients, see private header for replacement", ios(5.0, 14.0), macos(10.8, 11.0), tvos(5.0, 14.0), watchos(1.0, 6.0));
