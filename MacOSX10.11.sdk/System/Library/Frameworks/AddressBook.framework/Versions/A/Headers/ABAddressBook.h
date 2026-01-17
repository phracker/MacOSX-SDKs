//
//  ABAddressBook.h
//  AddressBook Framework
//
//  Copyright (c) 2003-2007 Apple Inc.  All rights reserved.
//

#ifndef __ABADDRESSBOOK__
#define __ABADDRESSBOOK__

#import <AddressBook/ABTypedefs.h>
#import <AddressBook/ABGlobals.h>

enum {
	ABAddRecordsError = 1001,
	ABRemoveRecordsError = 1002,
	ABPropertyValueValidationError = 1012,
	ABPropertyUnsupportedBySourceError = 1013,
	ABPropertyReadOnlyError = 1014
};

extern NSString *ABAddressBookErrorDomain AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;
extern NSString *ABMultiValueIdentifiersErrorKey AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

@class ABRecord;
@class ABPerson;
@class ABGroup;
@class ABSearchElement;

// ================================================================
//      OpenURL support
// ================================================================
// An application can open the Contacts app and select (and edit) a specific
// person by using the -[NSWorkspace openURL:] API.
//
// To launch (or bring to front) the Contacts app and select a given person
//
// NSString *urlString = [NSString stringWithFormat:@"addressbook://%@", [aPerson uniqueId]];
// [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:urlString]];
//
// To launch (or bring to front) the Contacts app and edit a given person
//
// NSString *urlString = [NSString stringWithFormat:@"addressbook://%@?edit", [aPerson uniqueId]];
// [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:urlString]];

// ================================================================
//      ABAddressBook
// ================================================================

@interface ABAddressBook : NSObject
{
@private
    id                   _reserved8;
    
    void                *_reserved2 __unused;
    void                *_reserved3 __unused;
    id                   _reserved4;
    NSMutableDictionary *_tableSchemas;
    NSMutableDictionary *_reserved5 __unused;
    void                *_converterPort __unused;
    NSTimer             *_inactivityTimer;
    id                   _reserved;

    id                   _reserved1;
	
    void                *_reserved6 __unused;
    void                *_reserved7 __unused;

    struct __ABBookflags {
        unsigned int     hasUnsavedChanges:1;
        unsigned int     readOnly:1;
        unsigned int     importMe:1;
        unsigned int     needConversion:1; // only used for puma conversion
        unsigned int     cleanedUp:1;
        unsigned int     importTips:1;
        unsigned int     restoreFromMetaData:1;
        unsigned int     prefsNeedSync:1;
        unsigned int     waitingForReset:1;
        unsigned int     enforcesConstraints:1;
        unsigned int     tracksAllSources:1;
        unsigned int     _reserved:21;
    } _flags;
}

+ (ABAddressBook *)sharedAddressBook;
    // Returns the unique shared instance of ABAddressBook
    // Returns nil if the address book database cannot be initialized 

+ (ABAddressBook *)addressBook AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
    // Returns a new instance of ABAddressBook
    // Instances of ABAddressBook and its records should only be used
    // on the thread where they were created.
    // Returns nil if the address book database cannot be initialized.

- (NSArray *)recordsMatchingSearchElement:(ABSearchElement *)search;
    // Returns an array of records matching the given search element
    // Raises if search is nil
    // Returns an empty array if no matches

- (BOOL)save;
    // Saves changes made since the last save
    // Return YES if successful (or there was no change)

- (BOOL)saveAndReturnError:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
    // Saves changes made since the last save
    // Return YES if successful (or there was no change)

- (BOOL)hasUnsavedChanges;
    // Returns YES if there are unsaved changes
    // The unsaved changes flag is automatically set when changes are made

- (ABPerson *)me;
    // Returns the person that represents the user
    // Returns nil if "me" was never set

- (void)setMe:(ABPerson *)moi;
    // Sets "Me" to moi.
    // Pass nil to clear "Me"

- (ABRecord *)recordForUniqueId:(NSString *)uniqueId;
    // Returns a record (ABPerson or ABGroup) matching a given unique ID
    // Raises if uniqueId is nil
    // Returns nil if the record could not be found

- (BOOL)addRecord:(ABRecord *)record error:(NSError**)error AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;
    // Adds a record (ABPerson or ABGroup) to the AddressBook database.
    // Raises if record is nil
    // Returns YES if the addition was successful
    // When returning NO, includes additional information in error when its given value is not nil
    // It is more efficient to use -[ABRecord initWithAddressBook:] where possible.

- (BOOL)addRecord:(ABRecord *)record;
    // Adds a record (ABPerson or ABGroup) to the AddressBook database.
    // It is more efficient to use -[ABRecord initWithAddressBook:] where possible.

- (BOOL)removeRecord:(ABRecord *)record error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;
    //  Removes a record (ABPerson or ABGroup) from the AddressBook database
    //  Raises if record is nil
    //  Returns YES if the removal was successful
    //  When returning NO, includes additional information in error when its given value is not nil

- (BOOL)removeRecord:(ABRecord *)record;
    // Removes a record (ABPerson or ABGroup) from the AddressBook database
    // Raises if record is nil
    // Returns YES if the removal was successful

- (NSArray *)people;
    // Returns an array of all the people in the AddressBook database
    // Returns an empty array if the DB doesn't contain any people

- (NSArray *)groups;
    // Returns an array of all the groups in the AddressBook database
    // Returns an empty array if the DB doesn't contain any groups

- (NSString *)recordClassFromUniqueId:(NSString *)uniqueId AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    // Given a record uniqueId returns the record class name

- (NSAttributedString *)formattedAddressFromDictionary:(NSDictionary *)address AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    // Returns an attributed string containing the formatted address.
    // The string's attributes match address dictionary keys (kABAddressStreetKey for example).
    // Each attribute value contains the localized description of the key. (For example, the value
    // of a Canadian kABAddressZIPKey field would be Postal Code)

- (NSString *)defaultCountryCode AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    // Returns the default country code for records without specified codes.

- (NSInteger)defaultNameOrdering AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    // Returns the default name ordering defined by the user in the Contacts preferences.
    // Possible values: kABFirstNameFirst or kABLastNameFirst


@end

#endif // __ABADDRESSBOOK__
