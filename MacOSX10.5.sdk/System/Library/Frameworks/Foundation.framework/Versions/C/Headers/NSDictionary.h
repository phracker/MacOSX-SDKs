/*	NSDictionary.h
	Copyright (c) 1994-2007, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>

@class NSArray, NSString, NSURL;

/****************	Immutable Dictionary	****************/

@interface NSDictionary : NSObject <NSCopying, NSMutableCopying, NSCoding, NSFastEnumeration>

- (NSUInteger)count;
- (id)objectForKey:(id)aKey;
- (NSEnumerator *)keyEnumerator;

@end

@interface NSDictionary (NSExtendedDictionary)

- (NSArray *)allKeys;
- (NSArray *)allKeysForObject:(id)anObject;    
- (NSArray *)allValues;
- (NSString *)description;
- (NSString *)descriptionInStringsFileFormat;
- (NSString *)descriptionWithLocale:(id)locale;
- (NSString *)descriptionWithLocale:(id)locale indent:(NSUInteger)level;
- (BOOL)isEqualToDictionary:(NSDictionary *)otherDictionary;
- (NSEnumerator *)objectEnumerator;
- (NSArray *)objectsForKeys:(NSArray *)keys notFoundMarker:(id)marker;
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically; // the atomically flag is ignored if url of a type that cannot be written atomically.

- (NSArray *)keysSortedByValueUsingSelector:(SEL)comparator;
- (void)getObjects:(id *)objects andKeys:(id *)keys;

@end

@interface NSDictionary (NSDictionaryCreation)

+ (id)dictionary;
+ (id)dictionaryWithObject:(id)object forKey:(id)key;
+ (id)dictionaryWithObjects:(id *)objects forKeys:(id *)keys count:(NSUInteger)cnt;
+ (id)dictionaryWithObjectsAndKeys:(id)firstObject, ... NS_REQUIRES_NIL_TERMINATION;
+ (id)dictionaryWithDictionary:(NSDictionary *)dict;
+ (id)dictionaryWithObjects:(NSArray *)objects forKeys:(NSArray *)keys;

- (id)initWithObjects:(id *)objects forKeys:(id *)keys count:(NSUInteger)cnt;
- (id)initWithObjectsAndKeys:(id)firstObject, ... NS_REQUIRES_NIL_TERMINATION;
- (id)initWithDictionary:(NSDictionary *)otherDictionary;
- (id)initWithDictionary:(NSDictionary *)otherDictionary copyItems:(BOOL)flag;
- (id)initWithObjects:(NSArray *)objects forKeys:(NSArray *)keys;

+ (id)dictionaryWithContentsOfFile:(NSString *)path;
+ (id)dictionaryWithContentsOfURL:(NSURL *)url;
- (id)initWithContentsOfFile:(NSString *)path;
- (id)initWithContentsOfURL:(NSURL *)url;

@end

/****************	Mutable Dictionary	****************/

@interface NSMutableDictionary : NSDictionary

- (void)removeObjectForKey:(id)aKey;
- (void)setObject:(id)anObject forKey:(id)aKey;

@end

@interface NSMutableDictionary (NSExtendedMutableDictionary)

- (void)addEntriesFromDictionary:(NSDictionary *)otherDictionary;
- (void)removeAllObjects;
- (void)removeObjectsForKeys:(NSArray *)keyArray;
- (void)setDictionary:(NSDictionary *)otherDictionary;

@end

@interface NSMutableDictionary (NSMutableDictionaryCreation)

+ (id)dictionaryWithCapacity:(NSUInteger)numItems;
- (id)initWithCapacity:(NSUInteger)numItems;

@end

