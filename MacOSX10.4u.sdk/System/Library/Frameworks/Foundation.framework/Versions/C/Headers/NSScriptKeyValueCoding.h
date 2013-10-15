/*
	NSScriptKeyValueCoding.h
	Copyright (c) 1997-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString;

extern NSString *NSOperationNotSupportedForKeyException;
// This exception can be raised by KVC methods that want to explicitly disallow certain manipulations or accesses.  For instance, a setKey: method for a read-only key can raise this exception.

@interface NSObject(NSScriptKeyValueCoding)

- (id)valueAtIndex:(unsigned)index inPropertyWithKey:(NSString *)key;
    // Retrieve a single value from a multi-value key.  This actually works with a single-value key as well if the index is 0.
    // The method -valueIn<Key>AtIndex: will be used if it exists

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED

- (id)valueWithName:(NSString *)name inPropertyWithKey:(NSString *)key;
    // Retrieve a single value from a multi-value key.
    // The method -valueIn<Key>WithName: will be invoked if it exists.  The declared type of the method's parameter must be NSString *.  Otherwise an NSUnknownKeyException will be thrown.

- (id)valueWithUniqueID:(id)uniqueID inPropertyWithKey:(NSString *)key;
    // Retrieve a single value from a multi-value key.  uniqueID must be either an NSNumber or an NSString.
    // The method -valueIn<Key>WithUniqueID: will be invoked if it exists.  The declared type of the unique ID parameter must be id, NSNumber *, NSString *, or one of the scalar types that can be encapsulated by NSNumber.  Otherwise an NSUnknownKeyException will be thrown.

#endif

- (void)replaceValueAtIndex:(unsigned)index inPropertyWithKey:(NSString *)key withValue:(id)value;
- (void)insertValue:(id)value atIndex:(unsigned)index inPropertyWithKey:(NSString *)key;
- (void)removeValueAtIndex:(unsigned)index fromPropertyWithKey:(NSString *)key;
    // Replace/insert/remove a single value in a multi-value key.
    // The methods:
    //     replaceIn<Key>:atIndex:
    //     insertIn<Key>:atIndex:
    //     removeFrom<Key>AtIndex:
    // will be used if they exist

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED

- (void)insertValue:(id)value inPropertyWithKey:(NSString *)key;
// Insert a single value in a multi-value key, at a reasonable index.  The method -insertIn<Key>: will be invoked if it exists.  Otherwise an NSUnknownKeyException will be thrown.

#endif

- (id)coerceValue:(id)value forKey:(NSString *)key;
    // Uses type info from the class description and NSScriptCoercionHandler to attempt to convert the given value to the proper type, if necessary.
    // The method coerceValueFor<Key>: will be used if it exists.
    
@end
