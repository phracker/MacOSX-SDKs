/*
        NSTextList.h
        Copyright (c) 2004-2011, Apple Inc.
        All rights reserved.

        Class to represent text lists.
*/

#import <Foundation/NSObject.h>


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
- (void)setStartingItemNumber:(NSInteger)itemNum NS_AVAILABLE_MAC(10_6);
- (NSInteger)startingItemNumber NS_AVAILABLE_MAC(10_6);

@end

