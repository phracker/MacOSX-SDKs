//
//  ABAddressBook.h
//  AddressBook Framework
//
//  Copyright (c) 2003-2007 Apple Inc.  All rights reserved.
//

#import <AddressBook/ABTypedefs.h>
#import <AddressBook/ABGlobals.h>

@class ABRecord;
@class ABPerson;
@class ABGroup;
@class ABSearchElement;
@class ABConverter;

// ================================================================
//      OpenURL support
// ================================================================
// An application can open the AddressBook app and select (and edit) a specific
// person by using the -[NSWorkspace openURL:] API.
//
// To launch (or bring to front) the Address Book app and select a given person
//
// NSString *urlString = [NSString stringWithFormat:@"addressbook://%@", [aPerson uniqueId]];
// [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:urlString]];
//
// To launch (or bring to front) the Address Book app and edit a given person
//
// NSString *urlString = [NSString stringWithFormat:@"addressbook://%@?edit", [aPerson uniqueId]];
// [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:urlString]];

// ================================================================
//      ABAddressBook
// ================================================================

@interface ABAddressBook : NSObject
{
@private
    NSMutableDictionary *_masterCache;
    
    void                *_reserved2;
    void                *_reserved3;
    id                   _reserved4;
    NSMutableDictionary *_tableSchemas;
    NSMutableDictionary *_reserved5;
    __strong void		*_converterPort;
    NSTimer             *_inactivityTimer;
    id                   _reserved;

    id                   _reserved1;
	
    void                *_reserved6;
    void                *_reserved7;

    struct __ABBookflags {
        unsigned int     hasUnsavedChanges:1;
        unsigned int     readOnly:1;
        unsigned int     importMe:1;
        unsigned int     needConversion:1; // only used for puma conversion
        unsigned int     cleanedUp:1;
        unsigned int     importTips:1;
        unsigned int     restoreFromMetaData:1;
        unsigned int     prefsNeedSync:1;
        unsigned int     _reserved:24;
    } _flags;
}

+ (ABAddressBook *)sharedAddressBook;
    // Returns the unique shared instance of ABAddressBook

#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED

+ (ABAddressBook *)addressBook;
    // Returns a new instance of ABAddressBook

#endif

- (NSArray *)recordsMatchingSearchElement:(ABSearchElement *)search;
    // Returns an array of records matching the given search element
    // Raises if search is nil
    // Returns an empty array if no matches

- (BOOL)save;
    // Saves changes made since the last save
    // Return YES if successful (or there was no change)

#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED

- (BOOL)saveAndReturnError:(NSError **)error;
    // Saves changes made since the last save
    // Return YES if successful (or there was no change)

#endif

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

- (BOOL)addRecord:(ABRecord *)record;
    // Adds a record (ABPerson or ABGroup) to the AddressBook database
    // Raises if record is nil
    // Returns YES if the addition was successful

- (BOOL)removeRecord:(ABRecord *)record;
    // Removes a record (ABPerson or ABGroup) from the AddressBook database
    // Raises if record is nil
    // Returns YES if the removal was successful

- (NSArray *)people;
    // Returns an array of all the people in the AddressBook database
    // Returns an empty array in case the DB doesn't contain any people

- (NSArray *)groups;
    // Returns an array of all the groups in the AddressBook database
    // Returns an empty array in case the DB doesn't contain any groups

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (NSString *)recordClassFromUniqueId:(NSString *)uniqueId;
    // Given a record uniqueId returns the record class name

- (NSAttributedString *)formattedAddressFromDictionary:(NSDictionary *)address;
    // Returns an attributed string containing the formatted address.
    // The string's attributes match address dictionary keys (kABAddressStreetKey for example).
    // Each attribute value contains the localized description of the key. (For example, the value
    // of a Canadian kABAddressZIPKey field would be Postal Code)

- (NSString *)defaultCountryCode;
    // Returns the default country code for records without specified codes.

- (NSInteger)defaultNameOrdering;
    // Returns the default name ordering defined by the user in the Address Book preferences.
    // Possible values: kABFirstNameFirst or kABLastNameFirst

#endif

@end

