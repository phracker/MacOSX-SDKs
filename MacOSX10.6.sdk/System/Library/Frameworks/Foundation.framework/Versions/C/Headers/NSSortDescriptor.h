/*
	NSSortDescriptor.h
	Foundation
	Copyright (c) 2002-2009, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSSet.h>

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED

@interface NSSortDescriptor : NSObject <NSCoding, NSCopying> {
@private
    NSUInteger _sortDescriptorFlags;
    NSString *_key;
    SEL _selector;
    id _selectorOrBlock;
}

+ (id)sortDescriptorWithKey:(NSString *)key ascending:(BOOL)ascending AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
+ (id)sortDescriptorWithKey:(NSString *)key ascending:(BOOL)ascending selector:(SEL)selector AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

// keys may be key paths
- (id)initWithKey:(NSString *)key ascending:(BOOL)ascending;
- (id)initWithKey:(NSString *)key ascending:(BOOL)ascending selector:(SEL)selector;

- (NSString *)key;
- (BOOL)ascending;
- (SEL)selector;

#if NS_BLOCKS_AVAILABLE
+ (id)sortDescriptorWithKey:(NSString *)key ascending:(BOOL)ascending comparator:(NSComparator)cmptr AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (id)initWithKey:(NSString *)key ascending:(BOOL)ascending comparator:(NSComparator)cmptr AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSComparator)comparator AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
#endif

- (NSComparisonResult)compareObject:(id)object1 toObject:(id)object2;    // primitive - override this method if you want to perform comparisons differently (not key based for example)
- (id)reversedSortDescriptor;    // primitive - override this method to return a sort descriptor instance with reversed sort order

@end

@interface NSSet (NSSortDescriptorSorting)

- (NSArray *)sortedArrayUsingDescriptors:(NSArray *)sortDescriptors AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;    // returns a new array by sorting the objects of the receiver

@end

@interface NSArray (NSSortDescriptorSorting)

- (NSArray *)sortedArrayUsingDescriptors:(NSArray *)sortDescriptors;    // returns a new array by sorting the objects of the receiver

@end

@interface NSMutableArray (NSSortDescriptorSorting)

- (void)sortUsingDescriptors:(NSArray *)sortDescriptors;    // sorts the array itself

@end

#endif

