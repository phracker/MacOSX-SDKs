//
//  ABRecord.h
//  AddressBook Framework
//
//  Copyright (c) 2003-2007 Apple Inc.  All rights reserved.
//

#ifndef __ABRECORD__
#define __ABRECORD__

#import <Foundation/Foundation.h>

@class ABAddressBook;


// ================================================================================
//	interface ABRecord
// ================================================================================
// ABRecord represents a row in the AddressBook database

@interface ABRecord : NSObject
{
@private
	id		_databaseImpl;
	id   _reserved1;
	id   _reserved2;
	id   _reserved3;
// pre leopard:
/*
    NSString            *_UIDString;
    NSMutableDictionary *_changedProperties;
    NSMutableDictionary *_temporaryCache;
    unsigned int         _hash;
*/
}

- (id)init;
	// on Mac OS X 10.5 and later equivalent to initWithAddressBook:[ABAddressBook addressBook]

- (id)initWithAddressBook:(ABAddressBook *)addressBook AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; // designated initializer
	// Initializes the ABRecord within the given AddressBook.
	// (Prior to 10.7, contacts will be stored locally.)

- (id)valueForProperty:(NSString *)property;
    // Returns the value of a given property. The type of the value depends on the property type.
    // The retuned object is immutable (NSString not NSMutableString, ABMultiValue not ABMutableMultiValue, etc..)
    // Raises if property is nil

- (BOOL)setValue:(id)value forProperty:(NSString *)property error:(NSError**)error AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;
    // Set the value of a given property. The type of the value must match the property type.
    // Raises if property is nil or value not of the correct type
    // Returns YES if the value was set successfully
    // When returning NO, includes additional information in error when its given value is not nil

- (BOOL)setValue:(id)value forProperty:(NSString *)property;
    // Set the value of a given property. The type of the value must match the property type.
    // Raises if property is nil or value not of the correct type
    // Returns YES if the value was set successfully

- (BOOL)removeValueForProperty:(NSString *)property;
    // Remove the value of a given property. Subsequent calls to -valueForProperty on the same
    // property will return nil.
    // Raises if property is nil
    // Returns YES if the value was removed successfully

- (BOOL)isReadOnly AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
    // Returns whether or not the record is read only.

@end

// ================================================================================
//	interface ABRecord(ABRecord_Convenience)
// ================================================================================

@interface ABRecord(ABRecord_Convenience)

@property (readonly, copy) NSString * uniqueId;
    // Convenience method to return the unique ID of a record.
    // Equivalent to -valueForProperty:kABUIDProperty

@property (readonly, copy) NSString * displayName AVAILABLE_MAC_OS_X_VERSION_10_10_AND_LATER;
    // Returns a formatted name suitable for displaying to the user.
    // The return value is only defined for ABPerson and ABGroup.

@end

#endif // __ABRECORD__
