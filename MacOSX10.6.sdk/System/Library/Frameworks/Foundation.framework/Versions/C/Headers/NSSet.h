/*	NSSet.h
	Copyright (c) 1994-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>

@class NSArray, NSDictionary, NSString;

/****************	Immutable Set	****************/

@interface NSSet : NSObject <NSCopying, NSMutableCopying, NSCoding, NSFastEnumeration>

- (NSUInteger)count;
- (id)member:(id)object;
- (NSEnumerator *)objectEnumerator;

@end

@interface NSSet (NSExtendedSet)

- (NSArray *)allObjects;
- (id)anyObject;
- (BOOL)containsObject:(id)anObject;
- (NSString *)description;
- (NSString *)descriptionWithLocale:(id)locale;
- (BOOL)intersectsSet:(NSSet *)otherSet;
- (BOOL)isEqualToSet:(NSSet *)otherSet;
- (BOOL)isSubsetOfSet:(NSSet *)otherSet;

- (void)makeObjectsPerformSelector:(SEL)aSelector;
- (void)makeObjectsPerformSelector:(SEL)aSelector withObject:(id)argument;

- (NSSet *)setByAddingObject:(id)anObject AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (NSSet *)setByAddingObjectsFromSet:(NSSet *)other AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (NSSet *)setByAddingObjectsFromArray:(NSArray *)other AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

#if NS_BLOCKS_AVAILABLE
- (void)enumerateObjectsUsingBlock:(void (^)(id obj, BOOL *stop))block AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)enumerateObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, BOOL *stop))block AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (NSSet *)objectsPassingTest:(BOOL (^)(id obj, BOOL *stop))predicate AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSSet *)objectsWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(id obj, BOOL *stop))predicate AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
#endif

@end

@interface NSSet (NSSetCreation)

+ (id)set;
+ (id)setWithObject:(id)object;
+ (id)setWithObjects:(id *)objects count:(NSUInteger)cnt;
+ (id)setWithObjects:(id)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
+ (id)setWithSet:(NSSet *)set;
+ (id)setWithArray:(NSArray *)array;

- (id)initWithObjects:(id *)objects count:(NSUInteger)cnt;
- (id)initWithObjects:(id)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
- (id)initWithSet:(NSSet *)set;
- (id)initWithSet:(NSSet *)set copyItems:(BOOL)flag;
- (id)initWithArray:(NSArray *)array;

@end

/****************	Mutable Set	****************/

@interface NSMutableSet : NSSet

- (void)addObject:(id)object;
- (void)removeObject:(id)object;

@end

@interface NSMutableSet (NSExtendedMutableSet)

- (void)addObjectsFromArray:(NSArray *)array;
- (void)intersectSet:(NSSet *)otherSet;
- (void)minusSet:(NSSet *)otherSet;
- (void)removeAllObjects;
- (void)unionSet:(NSSet *)otherSet;

- (void)setSet:(NSSet *)otherSet;

@end

@interface NSMutableSet (NSMutableSetCreation)

+ (id)setWithCapacity:(NSUInteger)numItems;
- (id)initWithCapacity:(NSUInteger)numItems;
    
@end

/****************	Counted Set	****************/

@interface NSCountedSet : NSMutableSet {
    @private
    id _table;
    void *_reserved;
}

- (id)initWithCapacity:(NSUInteger)numItems; // designated initializer

- (id)initWithArray:(NSArray *)array;
- (id)initWithSet:(NSSet *)set;

- (NSUInteger)countForObject:(id)object;

- (NSEnumerator *)objectEnumerator;
- (void)addObject:(id)object;
- (void)removeObject:(id)object;

@end

