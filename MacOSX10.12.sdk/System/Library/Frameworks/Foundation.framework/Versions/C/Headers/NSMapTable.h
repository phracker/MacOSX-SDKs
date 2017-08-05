/*	NSMapTable.h
	Copyright (c) 1994-2016, Apple Inc. All rights reserved.
*/

#import <Foundation/NSPointerFunctions.h>
#import <Foundation/NSString.h>
#import <Foundation/NSEnumerator.h>

#if !defined(__FOUNDATION_NSMAPTABLE__)
#define __FOUNDATION_NSMAPTABLE__ 1

@class NSArray, NSDictionary<KeyType, ObjectType>, NSMapTable;

NS_ASSUME_NONNULL_BEGIN

/****************	Class	****************/

/* An NSMapTable is modeled after a dictionary, although, because of its options, is not a dictionary because it will behave differently.  The major option is to have keys and/or values held "weakly" in a manner that entries will be removed at some indefinite point after one of the objects is reclaimed.  In addition to being held weakly, keys or values may be copied on input or may use pointer identity for equality and hashing.
   An NSMapTable can also be configured to operate on arbitrary pointers and not just objects.  We recommend the C function API for "void *" access.  To configure for pointer use, consult and choose the appropriate NSPointerFunction options or configure and use  NSPointerFunctions objects directly for initialization.
*/

static const NSPointerFunctionsOptions NSMapTableStrongMemory NS_ENUM_AVAILABLE(10_5, 6_0) = NSPointerFunctionsStrongMemory;
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32
static const NSPointerFunctionsOptions NSMapTableZeroingWeakMemory NS_ENUM_DEPRECATED_MAC(10_5, 10_8) = NSPointerFunctionsZeroingWeakMemory;
#endif
static const NSPointerFunctionsOptions NSMapTableCopyIn NS_ENUM_AVAILABLE(10_5, 6_0) = NSPointerFunctionsCopyIn;
static const NSPointerFunctionsOptions NSMapTableObjectPointerPersonality NS_ENUM_AVAILABLE(10_5, 6_0) = NSPointerFunctionsObjectPointerPersonality;
static const NSPointerFunctionsOptions NSMapTableWeakMemory NS_ENUM_AVAILABLE(10_8, 6_0) = NSPointerFunctionsWeakMemory;

typedef NSUInteger NSMapTableOptions;

NS_CLASS_AVAILABLE(10_5, 6_0)
@interface NSMapTable<KeyType, ObjectType> : NSObject <NSCopying, NSCoding, NSFastEnumeration>

- (instancetype)initWithKeyOptions:(NSPointerFunctionsOptions)keyOptions valueOptions:(NSPointerFunctionsOptions)valueOptions capacity:(NSUInteger)initialCapacity NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithKeyPointerFunctions:(NSPointerFunctions *)keyFunctions valuePointerFunctions:(NSPointerFunctions *)valueFunctions capacity:(NSUInteger)initialCapacity NS_DESIGNATED_INITIALIZER;

+ (NSMapTable<KeyType, ObjectType> *)mapTableWithKeyOptions:(NSPointerFunctionsOptions)keyOptions valueOptions:(NSPointerFunctionsOptions)valueOptions;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32
+ (id)mapTableWithStrongToStrongObjects NS_DEPRECATED_MAC(10_5, 10_8);
+ (id)mapTableWithWeakToStrongObjects NS_DEPRECATED_MAC(10_5, 10_8);
+ (id)mapTableWithStrongToWeakObjects NS_DEPRECATED_MAC(10_5, 10_8);
+ (id)mapTableWithWeakToWeakObjects NS_DEPRECATED_MAC(10_5, 10_8);
#endif

+ (NSMapTable<KeyType, ObjectType> *)strongToStrongObjectsMapTable NS_AVAILABLE(10_8, 6_0);
+ (NSMapTable<KeyType, ObjectType> *)weakToStrongObjectsMapTable NS_AVAILABLE(10_8, 6_0); // entries are not necessarily purged right away when the weak key is reclaimed
+ (NSMapTable<KeyType, ObjectType> *)strongToWeakObjectsMapTable NS_AVAILABLE(10_8, 6_0);
+ (NSMapTable<KeyType, ObjectType> *)weakToWeakObjectsMapTable NS_AVAILABLE(10_8, 6_0); // entries are not necessarily purged right away when the weak key or object is reclaimed

/* return an NSPointerFunctions object reflecting the functions in use.  This is a new autoreleased object that can be subsequently modified and/or used directly in the creation of other pointer "collections". */
@property (readonly, copy) NSPointerFunctions *keyPointerFunctions;
@property (readonly, copy) NSPointerFunctions *valuePointerFunctions;

- (nullable ObjectType)objectForKey:(nullable KeyType)aKey;

- (void)removeObjectForKey:(nullable KeyType)aKey;
- (void)setObject:(nullable ObjectType)anObject forKey:(nullable KeyType)aKey;   // add/replace value (CFDictionarySetValue, NSMapInsert)

@property (readonly) NSUInteger count;

- (NSEnumerator<KeyType> *)keyEnumerator;
- (nullable NSEnumerator<ObjectType> *)objectEnumerator;

- (void)removeAllObjects;

- (NSDictionary<KeyType, ObjectType> *)dictionaryRepresentation;  // create a dictionary of contents
@end

NS_ASSUME_NONNULL_END


#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32

NS_ASSUME_NONNULL_BEGIN

/****************	void * Map table operations	****************/

typedef struct {NSUInteger _pi; NSUInteger _si; void * _Nullable _bs;} NSMapEnumerator;



FOUNDATION_EXPORT void NSFreeMapTable(NSMapTable *table);
FOUNDATION_EXPORT void NSResetMapTable(NSMapTable *table);
FOUNDATION_EXPORT BOOL NSCompareMapTables(NSMapTable *table1, NSMapTable *table2);
FOUNDATION_EXPORT NSMapTable *NSCopyMapTableWithZone(NSMapTable *table, NSZone * _Nullable zone);
FOUNDATION_EXPORT BOOL NSMapMember(NSMapTable *table, const void *key, void * _Nullable * _Nullable originalKey, void * _Nullable * _Nullable value);
FOUNDATION_EXPORT void * _Nullable NSMapGet(NSMapTable *table, const void * _Nullable key);
FOUNDATION_EXPORT void NSMapInsert(NSMapTable *table, const void * _Nullable key, const void * _Nullable value);
FOUNDATION_EXPORT void NSMapInsertKnownAbsent(NSMapTable *table, const void * _Nullable key, const void * _Nullable value);
FOUNDATION_EXPORT void * _Nullable NSMapInsertIfAbsent(NSMapTable *table, const void * _Nullable key, const void * _Nullable value);
FOUNDATION_EXPORT void NSMapRemove(NSMapTable *table, const void * _Nullable key);
FOUNDATION_EXPORT NSMapEnumerator NSEnumerateMapTable(NSMapTable *table);
FOUNDATION_EXPORT BOOL NSNextMapEnumeratorPair(NSMapEnumerator *enumerator, void * _Nullable * _Nullable key, void * _Nullable * _Nullable value);
FOUNDATION_EXPORT void NSEndMapTableEnumeration(NSMapEnumerator *enumerator);
FOUNDATION_EXPORT NSUInteger NSCountMapTable(NSMapTable *table);
FOUNDATION_EXPORT NSString *NSStringFromMapTable(NSMapTable *table);
FOUNDATION_EXPORT NSArray *NSAllMapTableKeys(NSMapTable *table);
FOUNDATION_EXPORT NSArray *NSAllMapTableValues(NSMapTable *table);


/****************     Legacy     ***************************************/

typedef struct {
    NSUInteger	(* _Nullable hash)(NSMapTable *table, const void *);
    BOOL	(* _Nullable isEqual)(NSMapTable *table, const void *, const void *);
    void	(* _Nullable retain)(NSMapTable *table, const void *);
    void	(* _Nullable release)(NSMapTable *table, void *);
    NSString 	* _Nullable (* _Nullable describe)(NSMapTable *table, const void *);
    const void	* _Nullable notAKeyMarker;
} NSMapTableKeyCallBacks;
    
#define NSNotAnIntMapKey	((const void *)NSIntegerMin)
#define NSNotAnIntegerMapKey	((const void *)NSIntegerMin)
#define NSNotAPointerMapKey	((const void *)UINTPTR_MAX)

typedef struct {
    void	(* _Nullable retain)(NSMapTable *table, const void *);
    void	(* _Nullable release)(NSMapTable *table, void *);
    NSString 	* _Nullable(* _Nullable describe)(NSMapTable *table, const void *);
} NSMapTableValueCallBacks;

FOUNDATION_EXPORT NSMapTable *NSCreateMapTableWithZone(NSMapTableKeyCallBacks keyCallBacks, NSMapTableValueCallBacks valueCallBacks, NSUInteger capacity, NSZone * _Nullable zone);
FOUNDATION_EXPORT NSMapTable *NSCreateMapTable(NSMapTableKeyCallBacks keyCallBacks, NSMapTableValueCallBacks valueCallBacks, NSUInteger capacity);


/****************	Common map table key callbacks	****************/

FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSIntegerMapKeyCallBacks NS_AVAILABLE_MAC(10_5);
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSNonOwnedPointerMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSNonOwnedPointerOrNullMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSNonRetainedObjectMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSObjectMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSOwnedPointerMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSIntMapKeyCallBacks NS_DEPRECATED_MAC(10_0, 10_5);

/****************	Common map table value callbacks	****************/

FOUNDATION_EXPORT const NSMapTableValueCallBacks NSIntegerMapValueCallBacks NS_AVAILABLE_MAC(10_5);
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSNonOwnedPointerMapValueCallBacks;
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSObjectMapValueCallBacks;
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSNonRetainedObjectMapValueCallBacks;
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSOwnedPointerMapValueCallBacks;
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSIntMapValueCallBacks NS_DEPRECATED_MAC(10_0, 10_5);

NS_ASSUME_NONNULL_END

#else

#if defined(__has_include)
#if __has_include(<Foundation/NSMapTablePriv.h>)
#include <Foundation/NSMapTablePriv.h>
#endif
#endif

#endif

#endif

