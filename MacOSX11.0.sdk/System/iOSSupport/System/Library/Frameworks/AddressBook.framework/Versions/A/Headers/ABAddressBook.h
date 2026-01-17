/*
 *  ABAddressBook.h
 *  AddressBook
 *
 *  Copyright (c) 2010-2015 Apple Inc. All rights reserved.
 *
 */

#ifndef __ABAddressBook__
#define __ABAddressBook__

#include <AddressBook/AddressBookDefines.h>
#include <AddressBook/ABRecord.h>

#include <CoreFoundation/CoreFoundation.h>


AB_EXTERN const CFStringRef ABAddressBookErrorDomain AB_DEPRECATED("use CNErrorDomain");

enum {
    kABOperationNotPermittedByStoreError = 0,   // deprecated, use CNErrorCodePolicyViolation
    kABOperationNotPermittedByUserError         // deprecated, use CNErrorCodeAuthorizationDenied
};

typedef CFTypeRef ABAddressBookRef AB_DEPRECATED("use CNContactStore");

// To check the app's access to contact data. Based upon the access, the app could
// display or hide its UI elements that would access any AddressBook API.
//
// kABAuthorizationStatusNotDetermined
// The user has not yet made a choice regarding whether this app can access the data class.
//
// kABAuthorizationStatusRestricted
// This application is not authorized to access the data class. The user cannot change
// this application’s status, possibly due to active restrictions such as parental controls
// being in place.
//
// kABAuthorizationStatusDenied
// The user explicitly denied access to the data class for this application.
//
// kABAuthorizationStatusAuthorized
// This application is authorized to access the data class.
//
typedef CF_ENUM(CFIndex, ABAuthorizationStatus) {
    kABAuthorizationStatusNotDetermined = 0,    // deprecated, use CNAuthorizationStatusNotDetermined
    kABAuthorizationStatusRestricted,           // deprecated, use CNAuthorizationStatusRestricted
    kABAuthorizationStatusDenied,               // deprecated, use CNAuthorizationStatusDenied
    kABAuthorizationStatusAuthorized            // deprecated, use CNAuthorizationStatusAuthorized
} AB_DEPRECATED("use CNAuthorizationStatus");
AB_EXTERN ABAuthorizationStatus ABAddressBookGetAuthorizationStatus(void) AB_DEPRECATED("use [CNContactStore authorizationStatusForEntityType:]");

// Call ABAddressBookCreateWithOptions to create an instance of AddressBook. The
// ABAddressBookRef will initially not have access to contact data. The app must
// then call ABAddressBookRequestAccessWithCompletion to request this access.
// The options argument is reserved for future use. Currently it will always be NULL.
// If access to contact data is already restricted or denied, this will fail returning
// a NULL ABAddressBookRef with error kABOperationNotPermittedByUserError.
AB_EXTERN ABAddressBookRef ABAddressBookCreateWithOptions(CFDictionaryRef options, CFErrorRef* error) AB_DEPRECATED("use [[CNContactStore alloc] init]");

AB_EXTERN ABAddressBookRef ABAddressBookCreate(void) AB_DEPRECATED("use [[CNContactStore alloc] init]");

// Users are able to grant or deny access to contact data on a per-app basis. To request
// access to contact data, call ABAddressBookRequestAccessWithCompletion. This will not
// block the app while the user is being asked to grant or deny access. Until access has
// been granted, a non-NULL ABAddressBookRef will not contain any contacts and any attempt to
// modify contacts will fail with CFErrorRef returning kABOperationNotPermittedByUserError.
// The user will only be prompted the first time access is requested; any subsequent calls
// to ABAddressBookCreateWithOptions will use the existing permissions. The completion
// handler is called on an arbitrary queue. If the ABAddressBookRef is used throughout the app,
// then all usage should be dispatched to the same queue to use ABAddressBookRef in a
// thread-safe manner.
typedef void(^ABAddressBookRequestAccessCompletionHandler)(bool granted, CFErrorRef error) AB_DEPRECATED("");
AB_EXTERN void ABAddressBookRequestAccessWithCompletion(ABAddressBookRef addressBook,  ABAddressBookRequestAccessCompletionHandler completion) AB_DEPRECATED("use [CNContactStore requestAccessForEntityType:completionHandler:]");

AB_EXTERN bool ABAddressBookSave(ABAddressBookRef addressBook, CFErrorRef* error) AB_DEPRECATED("use [CNContactStore executeSaveRequest:error:]");
AB_EXTERN bool ABAddressBookHasUnsavedChanges(ABAddressBookRef addressBook) AB_DEPRECATED("");

AB_EXTERN bool ABAddressBookAddRecord(ABAddressBookRef addressBook, ABRecordRef record, CFErrorRef* error) AB_DEPRECATED("use CNSaveRequest");
AB_EXTERN bool ABAddressBookRemoveRecord(ABAddressBookRef addressBook, ABRecordRef record, CFErrorRef* error) AB_DEPRECATED("use CNSaveRequest");

// Some labels are special keys representing generic labels. Use this function to obtain
// a localized string for a label to display to a user.
AB_EXTERN CFStringRef ABAddressBookCopyLocalizedLabel(CFStringRef label) AB_DEPRECATED("use [CNLabeledValue localizedStringForLabel:]");

// Register an external change callback if you want to be informed of changes to the
// shared Address Book database by other instances or processes. The callback will be
// invoked by CFRunLoop on the thread where it was registered. The ABAddressBook does
// not take any action by default to flush or synchronize cached state with the database.
// If you want to ensure that you don't see any stale values, use ABAddressBookRevert().

// The info argument may eventually contain information describing the change. Currently
// it will always be NULL.
typedef void (*ABExternalChangeCallback)(ABAddressBookRef addressBook, CFDictionaryRef info, void *context) AB_DEPRECATED("");

AB_EXTERN void ABAddressBookRegisterExternalChangeCallback(ABAddressBookRef addressBook, ABExternalChangeCallback callback, void *context) AB_DEPRECATED("use CNContactStoreDidChangeNotification");

// When unregistering a callback both the callback and the context need to match the ones
// that were registered.
AB_EXTERN void ABAddressBookUnregisterExternalChangeCallback(ABAddressBookRef addressBook, ABExternalChangeCallback callback, void *context) AB_DEPRECATED("");

// ABAddressBookRevert() discards all cached properties and any unsaved changes so that
// records and properties retrieved subsequently will reflect any changes made by external
// ABAddressBook instances. If records were deleted externally, the corresponding ABRecord
// instances will return NULL for all properties. If necessary you can identify these
// deleted records by checking whether the class accessor (eg. ABPersonGetPersonWithRecordID())
// returns the record.
AB_EXTERN void ABAddressBookRevert(ABAddressBookRef addressBook) AB_DEPRECATED("refetch CN objects");

#endif
