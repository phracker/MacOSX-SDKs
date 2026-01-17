/*
        NSTextList.h
        Copyright (c) 2004-2005, Apple Computer, Inc.  All rights reserved.

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
    unsigned _listFlags;
    void *_listPrimary;
    void *_listSecondary;
}

- (id)initWithMarkerFormat:(NSString *)format options:(unsigned)mask;
- (NSString *)markerFormat;
- (unsigned)listOptions;
- (NSString *)markerForItemNumber:(int)itemNum;

@end

#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */
