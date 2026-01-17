/*
        NSStatusBar.h
        Application Kit
        Copyright (c) 1997-2024, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

@class NSColor;
@class NSFont;
@class NSMutableArray;
@class NSStatusItem;

static const CGFloat NSVariableStatusItemLength = -1.0;
static const CGFloat NSSquareStatusItemLength = -2.0;

@interface NSStatusBar : NSObject

@property (class, strong, readonly) NSStatusBar *systemStatusBar;

- (NSStatusItem *)statusItemWithLength:(CGFloat)length;
- (void)removeStatusItem:(NSStatusItem *)item;

@property (getter=isVertical, readonly) BOOL vertical;
@property (readonly) CGFloat thickness;

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
