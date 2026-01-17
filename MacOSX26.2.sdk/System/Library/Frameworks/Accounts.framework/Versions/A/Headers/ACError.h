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
    ACErrorAccountMissingRequiredProperty = 2,  // Account wasn't saved because it is missing a required property.
    ACErrorAccountAuthenticationFailed = 3,     // Account wasn't saved because authentication of the supplied credential failed.
    ACErrorAccountTypeInvalid = 4,              // Account wasn't saved because the account type is invalid.
    ACErrorAccountAlreadyExists = 5,            // Account wasn't added because it already exists.
    ACErrorAccountNotFound = 6,                 // Account wasn't deleted because it could not be found.
    ACErrorPermissionDenied = 7,                // The operation didn't complete because the user denied permission.
    ACErrorAccessInfoInvalid = 8,               // The client's access info dictionary has incorrect or missing values.
    ACErrorClientPermissionDenied = 9,          // Your client does not have access to the requested data.
    ACErrorAccessDeniedByProtectionPolicy = 10,  // Due to the current protection policy in effect, we couldn't fetch a credential
    ACErrorCredentialNotFound = 11,              // Yo, I tried to find your credential, but it must have run off!
    ACErrorFetchCredentialFailed = 12,           // Something bad happened on the way to the keychain
    ACErrorStoreCredentialFailed = 13,           // Unable to store credential
    ACErrorRemoveCredentialFailed = 14,          // Unable to remove credential
    ACErrorUpdatingNonexistentAccount = 15,      // Account save failed because the account being updated has been removed.
    ACErrorInvalidClientBundleID = 16,           // The client making the request does not have a valid bundle ID.
    ACErrorDeniedByPlugin = 17,                  // A plugin prevented the expected action to occur.
    ACErrorCoreDataSaveFailed = 18,              // Something broke below us when we tried to the CoreData store.
    ACErrorFailedSerializingAccountInfo = 19,
    ACErrorInvalidCommand = 20,
    ACErrorMissingTransportMessageID = 21,
    ACErrorCredentialItemNotFound = 22,          // Credential item wasn't saved because it could not be found.
    ACErrorCredentialItemNotExpired = 23,        // Credential item wasn't removed because it has not yet expired.
} ACErrorCode;
