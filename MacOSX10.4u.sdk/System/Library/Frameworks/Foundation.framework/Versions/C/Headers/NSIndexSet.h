/*	NSIndexSet.h
	Copyright (c) 2002-2005, Apple, Inc. All rights reserved.
*/

/* Class for managing set of indexes. The set of valid indexes are 0 .. NSNotFound - 1; trying to use indexes outside this range is an error.  NSIndexSet uses NSNotFound as a return value in cases where the queried index doesn't exist in the set; for instance, when you ask firstIndex and there are no indexes; or when you ask for indexGreaterThanIndex: on the last index, and so on.

The following code snippets can be used to enumerate over the indexes in an NSIndexSet:

    // Forward
    unsigned currentIndex = [set firstIndex];
    while (currentIndex != NSNotFound) {
        ...
        currentIndex = [set indexGreaterThanIndex:currentIndex];
    }
    
    // Backward
    unsigned currentIndex = [set lastIndex];
    while (currentIndex != NSNotFound) {
        ...
        currentIndex = [set indexLessThanIndex:currentIndex];
    }

To enumerate without doing a call per index, you can use the method getIndexes:maxCount:inIndexRange:.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED

@interface NSIndexSet : NSObject <NSCopying, NSMutableCopying, NSCoding> {
@protected   // all instance variables are private
    struct {
        unsigned int _isEmpty:1;
        unsigned int _hasSingleRange:1;
        unsigned int _cacheValid:1;
        unsigned int _reservedArrayBinderController:29;
    } _indexSetFlags;
    union {
        struct {
            NSRange _range;
        } _singleRange;
        struct {
            void *_data;
            void *_reserved;
        } _multipleRanges;
    } _internal;
}

+ (id)indexSet;
+ (id)indexSetWithIndex:(unsigned int)value;
+ (id)indexSetWithIndexesInRange:(NSRange)range;

- (id)init;
- (id)initWithIndex:(unsigned int)value;
- (id)initWithIndexesInRange:(NSRange)range;   // designated initializer
- (id)initWithIndexSet:(NSIndexSet *)indexSet;   // designated initializer

- (BOOL)isEqualToIndexSet:(NSIndexSet *)indexSet;

- (unsigned int)count;

/* The following six methods will return NSNotFound if there is no index in the set satisfying the query. 
*/
- (unsigned int)firstIndex;
- (unsigned int)lastIndex;
- (unsigned int)indexGreaterThanIndex:(unsigned int)value;
- (unsigned int)indexLessThanIndex:(unsigned int)value;
- (unsigned int)indexGreaterThanOrEqualToIndex:(unsigned int)value;
- (unsigned int)indexLessThanOrEqualToIndex:(unsigned int)value;

/* Fills up to bufferSize indexes in the specified range into the buffer and returns the number of indexes actually placed in the buffer; also modifies the optional range passed in by pointer to be "positioned" after the last index filled into the buffer.Example: if the index set contains the indexes 0, 2, 4, ..., 98, 100, for a buffer of size 10 and the range (20, 80) the buffer would contain 20, 22, ..., 38 and the range would be modified to (40, 60).
*/
- (unsigned int)getIndexes:(unsigned int *)indexBuffer maxCount:(unsigned int)bufferSize inIndexRange:(NSRangePointer)range;

- (BOOL)containsIndex:(unsigned int)value;
- (BOOL)containsIndexesInRange:(NSRange)range;
- (BOOL)containsIndexes:(NSIndexSet *)indexSet;

- (BOOL)intersectsIndexesInRange:(NSRange)range;

@end


@interface NSMutableIndexSet : NSIndexSet {
    void *_reserved;
}

- (void)addIndexes:(NSIndexSet *)indexSet;
- (void)removeIndexes:(NSIndexSet *)indexSet;
- (void)removeAllIndexes;
- (void)addIndex:(unsigned int)value;
- (void)removeIndex:(unsigned int)value;
- (void)addIndexesInRange:(NSRange)range;
- (void)removeIndexesInRange:(NSRange)range;

/* For a positive delta, shifts the indexes in [index, INT_MAX] to the right, thereby inserting an "empty space" [index, delta], for a negative delta, shifts the indexes in [index, INT_MAX] to the left, thereby deleting the indexes in the range [index - delta, delta].
*/
- (void)shiftIndexesStartingAtIndex:(unsigned int)index by:(int)delta;   

@end

#endif
