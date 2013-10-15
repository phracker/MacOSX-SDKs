/*	NSHashTable.h
	Copyright (c) 1994-2013, Apple Inc. All rights reserved.
*/

#import <Foundation/NSPointerFunctions.h>
#import <Foundation/NSString.h>
#import <Foundation/NSEnumerator.h>

#if !defined(__FOUNDATION_NSHASHTABLE__)
#define __FOUNDATION_NSHASHTABLE__ 1

@class NSArray, NSSet, NSHashTable;


/* An NSHashTable is modeled after a set, although, because of its options, is not a set because it can behave differently (for example, if pointer equality is specified two isEqual strings will both be entered).  The major option is to provide for "weak" references that are removed automatically, but at some indefinite point in the future.
   An NSHashTable can also be configured to operate on arbitrary pointers and not just objects.  We recommend the C function API for "void *" access.  To configure for pointer use, consult and choose the appropriate NSPointerFunctionsOptions or configure or use an NSPointerFunctions object itself for initialization.
*/

enum {
    NSHashTableStrongMemory NS_ENUM_AVAILABLE(10_5, 6_0) = 0, // NSPointerFunctionsStrongMemory
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32
    NSHashTableZeroingWeakMemory NS_ENUM_DEPRECATED_MAC(10_5, 10_8) = NSPointerFunctionsZeroingWeakMemory,
#endif
    NSHashTableCopyIn NS_ENUM_AVAILABLE(10_5, 6_0) = NSPointerFunctionsCopyIn,
    NSHashTableObjectPointerPersonality NS_ENUM_AVAILABLE(10_5, 6_0) = NSPointerFunctionsObjectPointerPersonality,
    NSHashTableWeakMemory NS_ENUM_AVAILABLE(10_8, 6_0) = NSPointerFunctionsWeakMemory
};

typedef NSUInteger NSHashTableOptions;

NS_CLASS_AVAILABLE(10_5, 6_0)
@interface NSHashTable : NSObject <NSCopying, NSCoding, NSFastEnumeration>

- (id)initWithOptions:(NSPointerFunctionsOptions)options capacity:(NSUInteger)initialCapacity;
- (id)initWithPointerFunctions:(NSPointerFunctions *)functions capacity:(NSUInteger)initialCapacity;

// conveniences

+ (id)hashTableWithOptions:(NSPointerFunctionsOptions)options;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32
+ (id)hashTableWithWeakObjects NS_DEPRECATED_MAC(10_5, 10_8);  // GC zeroing, otherwise unsafe unretained
#endif

+ (id)weakObjectsHashTable NS_AVAILABLE(10_8, 6_0); // entries are not necessarily purged right away when the weak object is reclaimed


/* return an NSPointerFunctions object reflecting the functions in use.  This is a new autoreleased object that can be subsequently modified and/or used directly in the creation of other pointer "collections". */
- (NSPointerFunctions *)pointerFunctions;

- (NSUInteger)count;
- (id)member:(id)object;
- (NSEnumerator *)objectEnumerator;

- (void)addObject:(id)object;
- (void)removeObject:(id)object;


- (void)removeAllObjects;

- (NSArray *)allObjects;    // convenience

- (id)anyObject;
- (BOOL)containsObject:(id)anObject;

- (BOOL)intersectsHashTable:(NSHashTable *)other;
- (BOOL)isEqualToHashTable:(NSHashTable *)other;
- (BOOL)isSubsetOfHashTable:(NSHashTable *)other;

- (void)intersectHashTable:(NSHashTable *)other;
- (void)unionHashTable:(NSHashTable *)other;
- (void)minusHashTable:(NSHashTable *)other;

- (NSSet *)setRepresentation;  // create a set of the contents

@end


#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32

/****************	(void *) Hash table operations	****************/

typedef struct {NSUInteger _pi; NSUInteger _si; void *_bs;} NSHashEnumerator;

FOUNDATION_EXPORT void NSFreeHashTable(NSHashTable *table);
FOUNDATION_EXPORT void NSResetHashTable(NSHashTable *table);
FOUNDATION_EXPORT BOOL NSCompareHashTables(NSHashTable *table1, NSHashTable *table2);
FOUNDATION_EXPORT NSHashTable *NSCopyHashTableWithZone(NSHashTable *table, NSZone *zone);
FOUNDATION_EXPORT void *NSHashGet(NSHashTable *table, const void *pointer);
FOUNDATION_EXPORT void NSHashInsert(NSHashTable *table, const void *pointer);
FOUNDATION_EXPORT void NSHashInsertKnownAbsent(NSHashTable *table, const void *pointer);
FOUNDATION_EXPORT void *NSHashInsertIfAbsent(NSHashTable *table, const void *pointer);
FOUNDATION_EXPORT void NSHashRemove(NSHashTable *table, const void *pointer);
FOUNDATION_EXPORT NSHashEnumerator NSEnumerateHashTable(NSHashTable *table);
FOUNDATION_EXPORT void *NSNextHashEnumeratorItem(NSHashEnumerator *enumerator);
FOUNDATION_EXPORT void NSEndHashTableEnumeration(NSHashEnumerator *enumerator);
FOUNDATION_EXPORT NSUInteger NSCountHashTable(NSHashTable *table);
FOUNDATION_EXPORT NSString *NSStringFromHashTable(NSHashTable *table);
FOUNDATION_EXPORT NSArray *NSAllHashTableObjects(NSHashTable *table);


/****************	Legacy	****************/

typedef struct {
    NSUInteger	(*hash)(NSHashTable *table, const void *);
    BOOL	(*isEqual)(NSHashTable *table, const void *, const void *);
    void	(*retain)(NSHashTable *table, const void *);
    void	(*release)(NSHashTable *table, void *);
    NSString 	*(*describe)(NSHashTable *table, const void *);
} NSHashTableCallBacks;

FOUNDATION_EXPORT NSHashTable *NSCreateHashTableWithZone(NSHashTableCallBacks callBacks, NSUInteger capacity, NSZone *zone);
FOUNDATION_EXPORT NSHashTable *NSCreateHashTable(NSHashTableCallBacks callBacks, NSUInteger capacity);


FOUNDATION_EXPORT const NSHashTableCallBacks NSIntegerHashCallBacks NS_AVAILABLE_MAC(10_5);
FOUNDATION_EXPORT const NSHashTableCallBacks NSNonOwnedPointerHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSNonRetainedObjectHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSObjectHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSOwnedObjectIdentityHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSOwnedPointerHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSPointerToStructHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSIntHashCallBacks NS_DEPRECATED_MAC(10_0, 10_5);

#else

#if defined(__has_include)
#if __has_include(<Foundation/NSHashTablePriv.h>)
#include <Foundation/NSHashTablePriv.h>
#endif
#endif

#endif

#endif

