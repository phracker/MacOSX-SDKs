/*	NSIndexSet.h
	Copyright (c) 2002-2011, Apple Inc. All rights reserved.
*/

/* Class for managing set of indexes. The set of valid indexes are 0 .. NSNotFound - 1; trying to use indexes outside this range is an error.  NSIndexSet uses NSNotFound as a return value in cases where the queried index doesn't exist in the set; for instance, when you ask firstIndex and there are no indexes; or when you ask for indexGreaterThanIndex: on the last index, and so on.

The following code snippets can be used to enumerate over the indexes in an NSIndexSet:

    // Forward
    NSUInteger currentIndex = [set firstIndex];
    while (currentIndex != NSNotFound) {
        ...
        currentIndex = [set indexGreaterThanIndex:currentIndex];
    }
    
    // Backward
    NSUInteger currentIndex = [set lastIndex];
    while (currentIndex != NSNotFound) {
        ...
        currentIndex = [set indexLessThanIndex:currentIndex];
    }

To enumerate without doing a call per index, you can use the method getIndexes:maxCount:inIndexRange:.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

@interface NSIndexSet : NSObject <NSCopying, NSMutableCopying, NSCoding> {
    @protected   // all instance variables are private
    struct {
        NSUInteger _isEmpty:1;
        NSUInteger _hasSingleRange:1;
        NSUInteger _cacheValid:1;
        NSUInteger _reservedArrayBinderController:29;
    } _indexSetFlags;
    union {
        struct {
            NSRange _range;
        } _singleRange;
        struct {
            void *  __strong _data;
            void *_reserved;
        } _multipleRanges;
    } _internal;
}

+ (id)indexSet;
+ (id)indexSetWithIndex:(NSUInteger)value;
+ (id)indexSetWithIndexesInRange:(NSRange)range;

- (id)init;
- (id)initWithIndex:(NSUInteger)value;
- (id)initWithIndexesInRange:(NSRange)range;   // designated initializer
- (id)initWithIndexSet:(NSIndexSet *)indexSet;   // designated initializer

- (BOOL)isEqualToIndexSet:(NSIndexSet *)indexSet;

- (NSUInteger)count;

/* The following six methods will return NSNotFound if there is no index in the set satisfying the query. 
*/
- (NSUInteger)firstIndex;
- (NSUInteger)lastIndex;
- (NSUInteger)indexGreaterThanIndex:(NSUInteger)value;
- (NSUInteger)indexLessThanIndex:(NSUInteger)value;
- (NSUInteger)indexGreaterThanOrEqualToIndex:(NSUInteger)value;
- (NSUInteger)indexLessThanOrEqualToIndex:(NSUInteger)value;

/* Fills up to bufferSize indexes in the specified range into the buffer and returns the number of indexes actually placed in the buffer; also modifies the optional range passed in by pointer to be "positioned" after the last index filled into the buffer.Example: if the index set contains the indexes 0, 2, 4, ..., 98, 100, for a buffer of size 10 and the range (20, 80) the buffer would contain 20, 22, ..., 38 and the range would be modified to (40, 60).
*/
- (NSUInteger)getIndexes:(NSUInteger *)indexBuffer maxCount:(NSUInteger)bufferSize inIndexRange:(NSRangePointer)range;

- (NSUInteger)countOfIndexesInRange:(NSRange)range NS_AVAILABLE(10_5, 2_0);

- (BOOL)containsIndex:(NSUInteger)value;
- (BOOL)containsIndexesInRange:(NSRange)range;
- (BOOL)containsIndexes:(NSIndexSet *)indexSet;

- (BOOL)intersectsIndexesInRange:(NSRange)range;

#if NS_BLOCKS_AVAILABLE
- (void)enumerateIndexesUsingBlock:(void (^)(NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
- (void)enumerateIndexesWithOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
- (void)enumerateIndexesInRange:(NSRange)range options:(NSEnumerationOptions)opts usingBlock:(void (^)(NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);

- (NSUInteger)indexPassingTest:(BOOL (^)(NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
- (NSUInteger)indexWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
- (NSUInteger)indexInRange:(NSRange)range options:(NSEnumerationOptions)opts passingTest:(BOOL (^)(NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);

- (NSIndexSet *)indexesPassingTest:(BOOL (^)(NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
- (NSIndexSet *)indexesWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
- (NSIndexSet *)indexesInRange:(NSRange)range options:(NSEnumerationOptions)opts passingTest:(BOOL (^)(NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);

/*
 The following three convenience methods allow you to enumerate the indexes in the receiver by ranges of contiguous indexes. The performance of these methods is not guaranteed to be any better than if they were implemented with enumerateIndexesInRange:options:usingBlock:. However, depending on the receiver's implementation, they may perform better than that.
 
 If the specified range for enumeration intersects a range of contiguous indexes in the receiver, then the block will be invoked with the intersection of those two ranges.
*/
- (void)enumerateRangesUsingBlock:(void (^)(NSRange range, BOOL *stop))block NS_AVAILABLE(10_7, 5_0);
- (void)enumerateRangesWithOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(NSRange range, BOOL *stop))block NS_AVAILABLE(10_7, 5_0);
- (void)enumerateRangesInRange:(NSRange)range options:(NSEnumerationOptions)opts usingBlock:(void (^)(NSRange range, BOOL *stop))block NS_AVAILABLE(10_7, 5_0);


#endif

@end

@interface NSMutableIndexSet : NSIndexSet {
    @protected
    void *_reserved;
}

- (void)addIndexes:(NSIndexSet *)indexSet;
- (void)removeIndexes:(NSIndexSet *)indexSet;
- (void)removeAllIndexes;
- (void)addIndex:(NSUInteger)value;
- (void)removeIndex:(NSUInteger)value;
- (void)addIndexesInRange:(NSRange)range;
- (void)removeIndexesInRange:(NSRange)range;

/* For a positive delta, shifts the indexes in [index, INT_MAX] to the right, thereby inserting an "empty space" [index, delta], for a negative delta, shifts the indexes in [index, INT_MAX] to the left, thereby deleting the indexes in the range [index - delta, delta].
*/
- (void)shiftIndexesStartingAtIndex:(NSUInteger)index by:(NSInteger)delta;   

@end

