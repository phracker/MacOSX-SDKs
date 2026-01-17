/*	NSSet.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray, NSDictionary, NSEnumerator, NSString;

/****************	Immutable Set	****************/

@interface NSSet : NSObject <NSCopying, NSMutableCopying, NSCoding>

- (unsigned)count;
- (id)member:(id)object;
- (NSEnumerator *)objectEnumerator;

@end

@interface NSSet (NSExtendedSet)

- (NSArray *)allObjects;
- (id)anyObject;
- (BOOL)containsObject:(id)anObject;
- (NSString *)description;
- (NSString *)descriptionWithLocale:(NSDictionary *)locale;
- (BOOL)intersectsSet:(NSSet *)otherSet;
- (BOOL)isEqualToSet:(NSSet *)otherSet;
- (BOOL)isSubsetOfSet:(NSSet *)otherSet;

- (void)makeObjectsPerformSelector:(SEL)aSelector;
- (void)makeObjectsPerformSelector:(SEL)aSelector withObject:(id)argument;

@end

@interface NSSet (NSSetCreation)

+ (id)set;
+ (id)setWithArray:(NSArray *)array;
+ (id)setWithObject:(id)object;
+ (id)setWithObjects:(id)firstObj, ...;
- (id)initWithArray:(NSArray *)array;
- (id)initWithObjects:(id *)objects count:(unsigned)count;
- (id)initWithObjects:(id)firstObj, ...;
- (id)initWithSet:(NSSet *)set;
- (id)initWithSet:(NSSet *)set copyItems:(BOOL)flag;

+ (id)setWithSet:(NSSet *)set;
+ (id)setWithObjects:(id *)objs count:(unsigned)cnt;

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

+ (id)setWithCapacity:(unsigned)numItems;
- (id)initWithCapacity:(unsigned)numItems;
    
@end

/****************	Counted Set	****************/

@interface NSCountedSet : NSMutableSet {
    @private
    void *_table;
    void *_reserved;
}

- (id)initWithCapacity:(unsigned)numItems; // designated initializer

- (id)initWithArray:(NSArray *)array;
- (id)initWithSet:(NSSet *)set;

- (unsigned)countForObject:(id)object;

- (NSEnumerator *)objectEnumerator;
- (void)addObject:(id)object;
- (void)removeObject:(id)object;

@end

