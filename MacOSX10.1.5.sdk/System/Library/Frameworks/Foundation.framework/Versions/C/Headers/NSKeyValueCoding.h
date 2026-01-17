/*	NSKeyValueCoding.h
	Copyright 1994-2001, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSArray, NSDictionary;

@interface NSObject (NSKeyValueCoding)

- (id)valueForKey:(NSString *)key;
- (void)takeValue:(id)value forKey:(NSString *)key;
- (id)storedValueForKey:(NSString *)key;
- (void)takeStoredValue:(id)value forKey:(NSString *)key;
+ (BOOL)accessInstanceVariablesDirectly;
+ (BOOL)useStoredAccessor;

@end

@interface NSObject (NSKeyValueCodingExtras)

- (id)valueForKeyPath:(NSString *)key;
- (void)takeValue:(id)value forKeyPath:(NSString *)key;
- (NSDictionary *)valuesForKeys:(NSArray *)keys;
- (void)takeValuesFromDictionary:(NSDictionary *)dictionary;

@end

@interface NSObject (NSKeyValueCodingException)

- (id)handleQueryWithUnboundKey:(NSString *)key;
- (void)handleTakeValue:(id)value forUnboundKey:(NSString *)key;
- (void)unableToSetNilForKey:(NSString *)key;

@end

