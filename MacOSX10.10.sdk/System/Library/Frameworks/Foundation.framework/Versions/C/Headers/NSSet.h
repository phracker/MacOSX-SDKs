/*	NSSet.h
	Copyright (c) 1994-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>

@class NSArray, NSDictionary, NSString;

/****************	Immutable Set	****************/

@interface NSSet : NSObject <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>

@property (readonly) NSUInteger count;
- (id)member:(id)object;
- (NSEnumerator *)objectEnumerator;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithObjects:(const id [])objects count:(NSUInteger)cnt NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSSet (NSExtendedSet)

@property (readonly, copy) NSArray *allObjects;
- (id)anyObject;
- (BOOL)containsObject:(id)anObject;
@property (readonly, copy) NSString *description;
- (NSString *)descriptionWithLocale:(id)locale;
- (BOOL)intersectsSet:(NSSet *)otherSet;
- (BOOL)isEqualToSet:(NSSet *)otherSet;
- (BOOL)isSubsetOfSet:(NSSet *)otherSet;

- (void)makeObjectsPerformSelector:(SEL)aSelector;
- (void)makeObjectsPerformSelector:(SEL)aSelector withObject:(id)argument;

- (NSSet *)setByAddingObject:(id)anObject NS_AVAILABLE(10_5, 2_0);
- (NSSet *)setByAddingObjectsFromSet:(NSSet *)other NS_AVAILABLE(10_5, 2_0);
- (NSSet *)setByAddingObjectsFromArray:(NSArray *)other NS_AVAILABLE(10_5, 2_0);

- (void)enumerateObjectsUsingBlock:(void (^)(id obj, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
- (void)enumerateObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);

- (NSSet *)objectsPassingTest:(BOOL (^)(id obj, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
- (NSSet *)objectsWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(id obj, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);

@end

@interface NSSet (NSSetCreation)

+ (instancetype)set;
+ (instancetype)setWithObject:(id)object;
+ (instancetype)setWithObjects:(const id [])objects count:(NSUInteger)cnt;
+ (instancetype)setWithObjects:(id)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
+ (instancetype)setWithSet:(NSSet *)set;
+ (instancetype)setWithArray:(NSArray *)array;

- (instancetype)initWithObjects:(id)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
- (instancetype)initWithSet:(NSSet *)set;
- (instancetype)initWithSet:(NSSet *)set copyItems:(BOOL)flag;
- (instancetype)initWithArray:(NSArray *)array;

@end

/****************	Mutable Set	****************/

@interface NSMutableSet : NSSet

- (void)addObject:(id)object;
- (void)removeObject:(id)object;
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;

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

+ (instancetype)setWithCapacity:(NSUInteger)numItems;

@end

/****************	Counted Set	****************/

@interface NSCountedSet : NSMutableSet {
    @private
    id _table;
    void *_reserved;
}

- (instancetype)initWithCapacity:(NSUInteger)numItems; // designated initializer

- (instancetype)initWithArray:(NSArray *)array;
- (instancetype)initWithSet:(NSSet *)set;

- (NSUInteger)countForObject:(id)object;

- (NSEnumerator *)objectEnumerator;
- (void)addObject:(id)object;
- (void)removeObject:(id)object;

@end

