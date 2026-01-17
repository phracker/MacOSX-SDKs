/*
        NSTextList.h
        Copyright (c) 2004-2009, Apple Inc.
        All rights reserved.

        Class to represent text lists.
*/

#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

enum {
    NSTextListPrependEnclosingMarker = (1 << 0)
};

@interface NSTextList : NSObject <NSCoding, NSCopying> {
    /*All instance variables are private*/
    NSString *_markerFormat;
    NSUInteger _listFlags;
    NSInteger _startIndex;
    void *_listSecondary;
}

- (id)initWithMarkerFormat:(NSString *)format options:(NSUInteger)mask;
- (NSString *)markerFormat;
- (NSUInteger)listOptions;
- (NSString *)markerForItemNumber:(NSInteger)itemNum;
- (void)setStartingItemNumber:(NSInteger)itemNum AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSInteger)startingItemNumber AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */
