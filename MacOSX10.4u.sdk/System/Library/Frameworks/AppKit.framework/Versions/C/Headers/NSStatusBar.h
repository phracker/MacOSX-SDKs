/*
        NSStatusBar.h
        Application Kit
        Copyright (c) 1997-2005, Apple Computer, Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>

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
    long            _fReserved1;
    long            _fReserved2;
    long            _fReserved3;
}

+ (NSStatusBar*) systemStatusBar;

- (NSStatusItem*) statusItemWithLength:(float)length;
- (void) removeStatusItem:(NSStatusItem*)item;

- (BOOL)     isVertical;
- (float)    thickness;

@end
