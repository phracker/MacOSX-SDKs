/*	NSHashTable.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>

/****************	Data structure	****************/

typedef struct _NSHashTable NSHashTable;

typedef struct {
    unsigned	(*hash)(NSHashTable *table, const void *);
    BOOL	(*isEqual)(NSHashTable *table, const void *, const void *);
    void	(*retain)(NSHashTable *table, const void *);
    void	(*release)(NSHashTable *table, void *);
    NSString 	*(*describe)(NSHashTable *table, const void *);
} NSHashTableCallBacks;
    
typedef struct {unsigned _pi; unsigned _si; void *_bs;} NSHashEnumerator;

/****************	Hash table operations	****************/

FOUNDATION_EXPORT NSHashTable *NSCreateHashTableWithZone(NSHashTableCallBacks callBacks, unsigned capacity, NSZone *zone);
FOUNDATION_EXPORT NSHashTable *NSCreateHashTable(NSHashTableCallBacks callBacks, unsigned capacity);
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
FOUNDATION_EXPORT unsigned NSCountHashTable(NSHashTable *table);
FOUNDATION_EXPORT NSString *NSStringFromHashTable(NSHashTable *table);
FOUNDATION_EXPORT NSArray *NSAllHashTableObjects(NSHashTable *table);

/****************	Common hash table callbacks	****************/

FOUNDATION_EXPORT const NSHashTableCallBacks NSIntHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSNonOwnedPointerHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSNonRetainedObjectHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSObjectHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSOwnedObjectIdentityHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSOwnedPointerHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSPointerToStructHashCallBacks;

