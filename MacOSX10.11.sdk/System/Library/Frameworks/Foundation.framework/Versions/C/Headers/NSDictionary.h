/*	NSDictionary.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>

@class NSArray<ObjectType>, NSSet<ObjectType>, NSString, NSURL;

/****************	Immutable Dictionary	****************/

NS_ASSUME_NONNULL_BEGIN

@interface NSDictionary<__covariant KeyType, __covariant ObjectType> : NSObject <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>

@property (readonly) NSUInteger count;
- (nullable ObjectType)objectForKey:(KeyType)aKey;
- (NSEnumerator<KeyType> *)keyEnumerator;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
#if TARGET_OS_WIN32
- (instancetype)initWithObjects:(const ObjectType [])objects forKeys:(const KeyType [])keys count:(NSUInteger)cnt;
#else
- (instancetype)initWithObjects:(const ObjectType [])objects forKeys:(const KeyType <NSCopying> [])keys count:(NSUInteger)cnt NS_DESIGNATED_INITIALIZER;
#endif
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSDictionary<KeyType, ObjectType> (NSExtendedDictionary)

@property (readonly, copy) NSArray<KeyType> *allKeys;
- (NSArray<KeyType> *)allKeysForObject:(ObjectType)anObject;
@property (readonly, copy) NSArray<ObjectType> *allValues;
@property (readonly, copy) NSString *description;
@property (readonly, copy) NSString *descriptionInStringsFileFormat;
- (NSString *)descriptionWithLocale:(nullable id)locale;
- (NSString *)descriptionWithLocale:(nullable id)locale indent:(NSUInteger)level;
- (BOOL)isEqualToDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary;
- (NSEnumerator<ObjectType> *)objectEnumerator;
- (NSArray<ObjectType> *)objectsForKeys:(NSArray<KeyType> *)keys notFoundMarker:(ObjectType)marker;
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically; // the atomically flag is ignored if url of a type that cannot be written atomically.

- (NSArray<KeyType> *)keysSortedByValueUsingSelector:(SEL)comparator;
// count refers to the number of elements in the dictionary
- (void)getObjects:(ObjectType __unsafe_unretained [])objects andKeys:(KeyType __unsafe_unretained [])keys count:(NSUInteger)count NS_AVAILABLE(10_7, 5_0);

- (nullable ObjectType)objectForKeyedSubscript:(KeyType)key NS_AVAILABLE(10_8, 6_0);

- (void)enumerateKeysAndObjectsUsingBlock:(void (^)(KeyType key, ObjectType obj, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
- (void)enumerateKeysAndObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(KeyType key, ObjectType obj, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);

- (NSArray<KeyType> *)keysSortedByValueUsingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);
- (NSArray<KeyType> *)keysSortedByValueWithOptions:(NSSortOptions)opts usingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);

- (NSSet<KeyType> *)keysOfEntriesPassingTest:(BOOL (^)(KeyType key, ObjectType obj, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
- (NSSet<KeyType> *)keysOfEntriesWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(KeyType key, ObjectType obj, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);

@end

@interface NSDictionary<KeyType, ObjectType> (NSDeprecated)
/// This method is unsafe because it could potentially cause buffer overruns. You should use -getObjects:andKeys:count:
- (void)getObjects:(ObjectType __unsafe_unretained [])objects andKeys:(KeyType __unsafe_unretained [])keys;
@end

@interface NSDictionary<KeyType, ObjectType> (NSDictionaryCreation)

+ (instancetype)dictionary;
+ (instancetype)dictionaryWithObject:(ObjectType)object forKey:(KeyType <NSCopying>)key;
#if TARGET_OS_WIN32
+ (instancetype)dictionaryWithObjects:(const ObjectType [])objects forKeys:(const KeyType [])keys count:(NSUInteger)cnt;
#else
+ (instancetype)dictionaryWithObjects:(const ObjectType [])objects forKeys:(const KeyType <NSCopying> [])keys count:(NSUInteger)cnt;
#endif

+ (instancetype)dictionaryWithObjectsAndKeys:(id)firstObject, ... NS_REQUIRES_NIL_TERMINATION NS_SWIFT_UNAVAILABLE("Use dictionary literals instead");

+ (instancetype)dictionaryWithDictionary:(NSDictionary<KeyType, ObjectType> *)dict;
+ (instancetype)dictionaryWithObjects:(NSArray<ObjectType> *)objects forKeys:(NSArray<KeyType <NSCopying>> *)keys;

- (instancetype)initWithObjectsAndKeys:(id)firstObject, ... NS_REQUIRES_NIL_TERMINATION;
- (instancetype)initWithDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary;
- (instancetype)initWithDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary copyItems:(BOOL)flag;
- (instancetype)initWithObjects:(NSArray<ObjectType> *)objects forKeys:(NSArray<KeyType <NSCopying>> *)keys;

+ (nullable NSDictionary<KeyType, ObjectType> *)dictionaryWithContentsOfFile:(NSString *)path;
+ (nullable NSDictionary<KeyType, ObjectType> *)dictionaryWithContentsOfURL:(NSURL *)url;
- (nullable NSDictionary<KeyType, ObjectType> *)initWithContentsOfFile:(NSString *)path;
- (nullable NSDictionary<KeyType, ObjectType> *)initWithContentsOfURL:(NSURL *)url;

@end

/****************	Mutable Dictionary	****************/

@interface NSMutableDictionary<KeyType, ObjectType> : NSDictionary<KeyType, ObjectType>

- (void)removeObjectForKey:(KeyType)aKey;
- (void)setObject:(ObjectType)anObject forKey:(KeyType <NSCopying>)aKey;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSMutableDictionary<KeyType, ObjectType> (NSExtendedMutableDictionary)

- (void)addEntriesFromDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary;
- (void)removeAllObjects;
- (void)removeObjectsForKeys:(NSArray<KeyType> *)keyArray;
- (void)setDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary;
- (void)setObject:(nullable ObjectType)obj forKeyedSubscript:(KeyType <NSCopying>)key NS_AVAILABLE(10_8, 6_0);

@end

@interface NSMutableDictionary<KeyType, ObjectType> (NSMutableDictionaryCreation)

+ (instancetype)dictionaryWithCapacity:(NSUInteger)numItems;

+ (nullable NSMutableDictionary<KeyType, ObjectType> *)dictionaryWithContentsOfFile:(NSString *)path;
+ (nullable NSMutableDictionary<KeyType, ObjectType> *)dictionaryWithContentsOfURL:(NSURL *)url;
- (nullable NSMutableDictionary<KeyType, ObjectType> *)initWithContentsOfFile:(NSString *)path;
- (nullable NSMutableDictionary<KeyType, ObjectType> *)initWithContentsOfURL:(NSURL *)url;

@end

@interface NSDictionary<KeyType, ObjectType> (NSSharedKeySetDictionary)

/*  Use this method to create a key set to pass to +dictionaryWithSharedKeySet:.
 The keys are copied from the array and must be copyable.
 If the array parameter is nil or not an NSArray, an exception is thrown.
 If the array of keys is empty, an empty key set is returned.
 The array of keys may contain duplicates, which are ignored (it is undefined which object of each duplicate pair is used).
 As for any usage of hashing, is recommended that the keys have a well-distributed implementation of -hash, and the hash codes must satisfy the hash/isEqual: invariant.
 Keys with duplicate hash codes are allowed, but will cause lower performance and increase memory usage.
 */
+ (id)sharedKeySetForKeys:(NSArray<KeyType <NSCopying>> *)keys NS_AVAILABLE(10_8, 6_0);

@end

@interface NSMutableDictionary<KeyType, ObjectType> (NSSharedKeySetDictionary)

/*  Create a mutable dictionary which is optimized for dealing with a known set of keys.
 Keys that are not in the key set can still be set into the dictionary, but that usage is not optimal.
 As with any dictionary, the keys must be copyable.
 If keyset is nil, an exception is thrown.
 If keyset is not an object returned by +sharedKeySetForKeys:, an exception is thrown.
 */
+ (NSMutableDictionary<KeyType, ObjectType> *)dictionaryWithSharedKeySet:(id)keyset NS_AVAILABLE(10_8, 6_0);

@end

NS_ASSUME_NONNULL_END
