/*
        NSStatusBar.h
        Application Kit
        Copyright (c) 1997-2015, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>

NS_ASSUME_NONNULL_BEGIN

@class NSColor;
@class NSFont;
@class NSStatusItem;
@class NSMutableArray;

static const CGFloat NSVariableStatusItemLength = -1.0;
static const CGFloat NSSquareStatusItemLength = -2.0;

@interface NSStatusBar : NSObject
{
 @private
    id             _items;
    void           *_fReserved1;
    void           *_fReserved2;
    NSInteger      _registeredForNote;
}

+ (NSStatusBar*)systemStatusBar;

- (NSStatusItem*)statusItemWithLength:(CGFloat)length;
- (void)removeStatusItem:(NSStatusItem*)item;

@property (getter=isVertical, readonly) BOOL vertical;
@property (readonly) CGFloat thickness;

@end

NS_ASSUME_NONNULL_END
