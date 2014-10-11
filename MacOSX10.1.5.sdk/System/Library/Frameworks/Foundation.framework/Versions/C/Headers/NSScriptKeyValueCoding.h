/*	NSScriptKeyValueCoding.h
	Copyright 1997-2001, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString;

extern NSString *NSOperationNotSupportedForKeyException;
// This exception can be raised by KVC methods that want to explicitly disallow certain manipulations or accesses.  For instance, a setKey: method for a read-only key can raise this exception.

@interface NSObject(NSScriptKeyValueCoding)

- (id)valueAtIndex:(unsigned)index inPropertyWithKey:(NSString *)key;
    // Retrieve a single value from a multi-value key.  This actually works with a single-value key as well if the index is 0.
    // The method valueIn<Key>AtIndex: will be used if it exists

- (void)replaceValueAtIndex:(unsigned)index inPropertyWithKey:(NSString *)key withValue:(id)value;
- (void)insertValue:(id)value atIndex:(unsigned)index inPropertyWithKey:(NSString *)key;
- (void)removeValueAtIndex:(unsigned)index fromPropertyWithKey:(NSString *)key;
    // Replace/insert/remove a single value in a multi-value key.
    // The methods:
    //     replaceIn<Key>:atIndex:
    //     insertIn<Key>:atIndex:
    //     removeFrom<Key>AtIndex:
    // will be used if they exist

- (id)coerceValue:(id)value forKey:(NSString *)key;
    // Uses type info from the class description and NSScriptCoercionHandler to attempt to convert the given value to the proper type, if necessary.
    // The method coerceValueFor<Key>: will be used if it exists.
    
@end
