/*
	NSSortDescriptor.h
	Foundation
	Copyright (c) 2002-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSArray.h>

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED

@interface NSSortDescriptor : NSObject <NSCoding, NSCopying> {
@private
    struct __sortDescriptorFlags {
        unsigned int _ascending:1;
        unsigned int _reservedSortDescriptor:31;
    } _sortDescriptorFlags;
    NSString *_key;
    SEL _selector;
    NSString *_selectorName;
}

// keys may be key paths
- (id)initWithKey:(NSString *)key ascending:(BOOL)ascending;
- (id)initWithKey:(NSString *)key ascending:(BOOL)ascending selector:(SEL)selector;

- (NSString *)key;
- (BOOL)ascending;
- (SEL)selector;

- (NSComparisonResult)compareObject:(id)object1 toObject:(id)object2;    // primitive - override this method if you want to perform comparisons differently (not key based for example)
- (id)reversedSortDescriptor;    // primitive - override this method to return a sort descriptor instance with reversed sort order

@end

@interface NSArray (NSSortDescriptorSorting)

- (NSArray *)sortedArrayUsingDescriptors:(NSArray *)sortDescriptors;    // returns a new array by sorting the objects of the receiver

@end

@interface NSMutableArray (NSSortDescriptorSorting)

- (void)sortUsingDescriptors:(NSArray *)sortDescriptors;    // sorts the array itself

@end

#endif
