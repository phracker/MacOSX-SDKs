/*
        NSTextList.h
	Copyright (c) 2004-2007, Apple Inc.
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
    void *_listPrimary;
    void *_listSecondary;
}

- (id)initWithMarkerFormat:(NSString *)format options:(NSUInteger)mask;
- (NSString *)markerFormat;
- (NSUInteger)listOptions;
- (NSString *)markerForItemNumber:(NSInteger)itemNum;

@end

#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */
