//
//  ACError.h
//  Accounts
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accounts/AccountsDefines.h>

ACCOUNTS_EXTERN NSString * const ACErrorDomain API_AVAILABLE(ios(5.0), macos(10.8));

typedef enum ACErrorCode {
    ACErrorUnknown = 1,
    ACErrorAccountMissingRequiredProperty,  // Account wasn't saved because it is missing a required property.
    ACErrorAccountAuthenticationFailed,     // Account wasn't saved because authentication of the supplied credential failed.
    ACErrorAccountTypeInvalid,              // Account wasn't saved because the account type is invalid.
    ACErrorAccountAlreadyExists,            // Account wasn't added because it already exists.
    ACErrorAccountNotFound,                 // Account wasn't deleted because it could not be found.
    ACErrorPermissionDenied,                // The operation didn't complete because the user denied permission.
    ACErrorAccessInfoInvalid,               // The client's access info dictionary has incorrect or missing values.
    ACErrorClientPermissionDenied,          // Your client does not have access to the requested data.
    ACErrorAccessDeniedByProtectionPolicy,  // Due to the current protection policy in effect, we couldn't fetch a credential
    ACErrorCredentialNotFound,              // Yo, I tried to find your credential, but it must have run off!
    ACErrorFetchCredentialFailed,           // Something bad happened on the way to the keychain
    ACErrorStoreCredentialFailed,           // Unable to store credential
    ACErrorRemoveCredentialFailed,          // Unable to remove credential
    ACErrorUpdatingNonexistentAccount,      // Account save failed because the account being updated has been removed.
    ACErrorInvalidClientBundleID,           // The client making the request does not have a valid bundle ID.
    ACErrorDeniedByPlugin,                  // A plugin prevented the expected action to occur.
    ACErrorCoreDataSaveFailed,              // Something broke below us when we tried to the CoreData store.
    ACErrorFailedSerializingAccountInfo,
    ACErrorInvalidCommand,
    ACErrorMissingTransportMessageID,
    ACErrorCredentialItemNotFound,          // Credential item wasn't saved because it could not be found.
    ACErrorCredentialItemNotExpired,        // Credential item wasn't removed because it has not yet expired.
} ACErrorCode;
