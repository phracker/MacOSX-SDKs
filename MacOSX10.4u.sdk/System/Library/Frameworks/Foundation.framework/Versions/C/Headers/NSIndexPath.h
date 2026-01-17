/*  NSIndexPath.h
    Copyright (c) 2003-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

@interface NSIndexPath : NSObject <NSCopying, NSCoding> {
	unsigned int *_indexes;
	unsigned int _hash;
	unsigned int _length;
        void *_reserved;
}

+ (NSIndexPath *)indexPathWithIndex:(unsigned int)index;
+ (NSIndexPath *)indexPathWithIndexes:(unsigned int *)indexes length:(unsigned int)length;   

- (id)initWithIndex:(unsigned int)index;
- (id)initWithIndexes:(unsigned int *)indexes length:(unsigned int)length;    // designated initializer

- (NSIndexPath *)indexPathByAddingIndex:(unsigned int)index;
- (NSIndexPath *)indexPathByRemovingLastIndex;

- (unsigned int)indexAtPosition:(unsigned int)position;
- (unsigned int)length;

- (void)getIndexes:(unsigned int *)indexes;

	// comparison support
- (NSComparisonResult)compare:(NSIndexPath *)otherObject; // sorting an array of indexPaths using this comparison results in an array representing nodes in depth-first traversal order

@end

#endif

