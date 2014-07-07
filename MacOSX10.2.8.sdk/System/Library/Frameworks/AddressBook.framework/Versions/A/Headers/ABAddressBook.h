//
//  ABAddressBook.h
//  AddressBook Framework
//
//  Copyright (c) 2002 Apple Computer. All rights reserved.
//

#import <AddressBook/ABTypedefs.h>
#import <AddressBook/ABGlobals.h>

@class ABRecord;
@class ABPerson;
@class ABGroup;
@class ABSearchElement;
@class ABConverter;

// ================================================================
//	OpenURL support
// ================================================================
// An application can open the AddressBook app and select (or edit) a specific
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
//	ABAddressBook
// ================================================================

@interface ABAddressBook : NSObject
{
@private
    id                   _personIndexer;
    NSMutableDictionary *_masterCache;

    NSMutableArray      *_insertedRecords;
    NSMutableArray      *_modifiedRecords;
    NSMutableArray      *_deletedRecords;
    NSMutableDictionary *_tableSchemas;
    NSMutableDictionary *_propertyTypes;
    void		*_converterPort;
    NSTimer             *_inactivityTimer;

    unsigned int         _insertedPeople;
    unsigned int         _deletedPeople;

    struct __ABBookflags {
        unsigned int     haveFileLock:1;
        unsigned int     hasUnsavedChanges:1;
        unsigned int     readOnly:1;
        unsigned int     importMe:1;
        unsigned int     needConversion:1;
        unsigned int     _reserved:27;
    } _flags;
}

+ (ABAddressBook *)sharedAddressBook;
    // Returns the unique shared instance of ABAddressBook

- (NSArray *)recordsMatchingSearchElement:(ABSearchElement *)search;
    // Returns an array of record matching the given search element
    // Raises if search is nil
    // Returns an empty array if no matches

- (BOOL)save;
    // Saves changes made since the last save
    // Return YES if sucessfull (or there was no change)

- (BOOL)hasUnsavedChanges;
    // Returns YES if they are unsaved changes
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
    // Adds a record (ABPerson or ABGroup) to the AddressBook Database
    // Raises if record is nil
    // Returns YES if the addition was successful

- (BOOL)removeRecord:(ABRecord *)record;
    // Removes a record (ABPerson or ABGroup) from the AddressBook Database
    // Raises if record is nil
    // Returns YES if the removal was successful

- (NSArray *)people;
    // Returns an array of all the people in the AddressBook database
    // Returns an empty array in case the DB doesn't contain any body

- (NSArray *)groups;
    // Returns an array of all the groups in the AddressBook database
    // Returns an empty array in case the DB doesn't contain any groups

@end
