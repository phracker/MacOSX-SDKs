/*
        NSTextList.h
        Copyright (c) 2004-2014, Apple Inc.
        All rights reserved.

        Class to represent text lists.
*/

#import <Foundation/NSObject.h>


typedef NS_OPTIONS(NSUInteger, NSTextListOptions) {
    NSTextListPrependEnclosingMarker = (1 << 0)
};

@interface NSTextList : NSObject <NSCoding, NSCopying> {
    /*All instance variables are private*/
    NSString *_markerFormat;
    NSUInteger _listFlags;
    NSInteger _startIndex;
    void *_listSecondary;
}

- (instancetype)initWithMarkerFormat:(NSString *)format options:(NSUInteger)mask;
@property (readonly, copy) NSString *markerFormat;
@property (readonly) NSTextListOptions listOptions;
- (NSString *)markerForItemNumber:(NSInteger)itemNum;
@property NSInteger startingItemNumber NS_AVAILABLE_MAC(10_6);

@end

