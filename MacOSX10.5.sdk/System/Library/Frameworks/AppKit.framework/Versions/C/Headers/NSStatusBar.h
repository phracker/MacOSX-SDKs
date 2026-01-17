/*
        NSStatusBar.h
        Application Kit
        Copyright (c) 1997-2007, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>

@class NSColor;
@class NSFont;
@class NSStatusItem;
@class NSMutableArray;

#define	NSVariableStatusItemLength	(-1)
#define	NSSquareStatusItemLength	(-2)

@interface NSStatusBar : NSObject
{
 @private
    NSMutableArray* _actions;
    void           *_fReserved1;
    void           *_fReserved2;
    void           *_fReserved3;
}

+ (NSStatusBar*)systemStatusBar;

- (NSStatusItem*)statusItemWithLength:(CGFloat)length;
- (void)removeStatusItem:(NSStatusItem*)item;

- (BOOL)isVertical;
- (CGFloat)thickness;

@end
