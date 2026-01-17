/*
        NSStatusBar.h
        Application Kit
        Copyright (c) 1997-2018, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/AppKitDefines.h>

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
    id             _items APPKIT_IVAR;
    void           *_fReserved1 APPKIT_IVAR;
    void           *_fReserved2 __unused APPKIT_IVAR;
    NSInteger      _registeredForNote APPKIT_IVAR;
}

@property (class, readonly, strong) NSStatusBar *systemStatusBar;

- (NSStatusItem*)statusItemWithLength:(CGFloat)length;
- (void)removeStatusItem:(NSStatusItem*)item;

@property (getter=isVertical, readonly) BOOL vertical;
@property (readonly) CGFloat thickness;

@end

NS_ASSUME_NONNULL_END
