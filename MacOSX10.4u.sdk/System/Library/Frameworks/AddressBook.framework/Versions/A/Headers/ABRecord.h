//
//  ABRecord.h
//  AddressBook Framework
//
//  Copyright (c) 2002-2003 Apple Computer. All rights reserved.
//

#import <Foundation/Foundation.h>

// ================================================================================
//	interface ABRecord
// ================================================================================
// ABRecord represents a row in the AddressBook database

@interface ABRecord : NSObject
{
@private
    NSString            *_UIDString;
    NSMutableDictionary *_changedProperties;
    NSMutableDictionary *_temporaryCache;
    unsigned int         _hash;
}
- (id)valueForProperty:(NSString *)property;
    // Returns the value of a given property. The type of the value depends on the property type.
    // The retuned object is immutable (NSString not NSMutableString, ABMultiValue not ABMutableMultiValue, etc..)
    // Raises if property is nil

- (BOOL)setValue:(id)value forProperty:(NSString *)property;
    // Set the value of a given property. The type of the value must match the property type.
    // Raises if property is nil or value not of the correct type
    // Returns YES if the value was set successfully

- (BOOL)removeValueForProperty:(NSString *)property;
    // Remove the value of a given property. Subsequent calls to -valueForProperty on the same
    // property will return nil.
    // Raises if property is nil
    // Returns YES if the value was removed successfully

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (BOOL)isReadOnly;
    // Returns whether or not the record is read only.
#endif

@end

// ================================================================================
//	interface ABRecord(ABRecord_Convenience)
// ================================================================================

@interface ABRecord(ABRecord_Convenience)

- (NSString *)uniqueId;
    // Convenience method to return the unique ID of a record.
    // Equivalent to -valueForProperty:kABUIDProperty
@end
