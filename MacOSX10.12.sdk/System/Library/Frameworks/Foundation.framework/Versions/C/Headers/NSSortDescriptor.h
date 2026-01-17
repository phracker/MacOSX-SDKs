/*
	NSSortDescriptor.h
	Foundation
	Copyright (c) 2002-2016, Apple Inc. All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSOrderedSet.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSSortDescriptor : NSObject <NSSecureCoding, NSCopying> {
@private
    NSUInteger _sortDescriptorFlags;
    NSString *_key;
    SEL _selector;
    id _selectorOrBlock;
}

+ (instancetype)sortDescriptorWithKey:(nullable NSString *)key ascending:(BOOL)ascending NS_AVAILABLE(10_6, 4_0);
+ (instancetype)sortDescriptorWithKey:(nullable NSString *)key ascending:(BOOL)ascending selector:(nullable SEL)selector NS_AVAILABLE(10_6, 4_0);

// keys may be key paths
- (instancetype)initWithKey:(nullable NSString *)key ascending:(BOOL)ascending;
- (instancetype)initWithKey:(nullable NSString *)key ascending:(BOOL)ascending selector:(nullable SEL)selector;
- (nullable instancetype)initWithCoder:(NSCoder *)coder;

@property (nullable, readonly, copy) NSString *key;
@property (readonly) BOOL ascending;
@property (nullable, readonly) SEL selector;

- (void)allowEvaluation NS_AVAILABLE(10_9, 7_0); // Force a sort descriptor which was securely decoded to allow evaluation

+ (instancetype)sortDescriptorWithKey:(nullable NSString *)key ascending:(BOOL)ascending comparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);

- (instancetype)initWithKey:(nullable NSString *)key ascending:(BOOL)ascending comparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);

@property (readonly) NSComparator comparator NS_AVAILABLE(10_6, 4_0);

- (NSComparisonResult)compareObject:(id)object1 toObject:(id)object2;    // primitive - override this method if you want to perform comparisons differently (not key based for example)
@property (readonly, retain) id reversedSortDescriptor;    // primitive - override this method to return a sort descriptor instance with reversed sort order

@end

@interface NSSet<ObjectType> (NSSortDescriptorSorting)

- (NSArray<ObjectType> *)sortedArrayUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors NS_AVAILABLE(10_6, 4_0);    // returns a new array by sorting the objects of the receiver

@end

@interface NSArray<ObjectType> (NSSortDescriptorSorting)

- (NSArray<ObjectType> *)sortedArrayUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors;    // returns a new array by sorting the objects of the receiver

@end

@interface NSMutableArray<ObjectType> (NSSortDescriptorSorting)

- (void)sortUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors;    // sorts the array itself

@end

@interface NSOrderedSet<ObjectType> (NSKeyValueSorting)

// returns a new array by sorting the objects of the receiver
- (NSArray<ObjectType> *)sortedArrayUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors NS_AVAILABLE(10_7, 5_0);

@end

@interface NSMutableOrderedSet<ObjectType> (NSKeyValueSorting)

// sorts the ordered set itself
- (void)sortUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors NS_AVAILABLE(10_7, 5_0);

@end

NS_ASSUME_NONNULL_END
