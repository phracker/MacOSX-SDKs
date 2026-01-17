/*
        NSWindowScripting.h
        AppKit Framework
        Copyright (c) 1997-2001, Apple Computer, Inc.
        All rights reserved.
*/

#import <AppKit/NSWindow.h>

@class NSCloseCommand;
@class NSScriptCommand;

@interface NSWindow (NSScripting)

- (BOOL)hasCloseBox;
- (BOOL)hasTitleBar;
- (BOOL)isFloatingPanel;
- (BOOL)isModalPanel;
- (BOOL)isResizable;
- (BOOL)isZoomable;
- (BOOL)isMiniaturizable;
    // Read-only keys, so no "set" methods.

- (void)setIsZoomed:(BOOL)flag;
- (void)setIsMiniaturized:(BOOL)flag;
- (void)setIsVisible:(BOOL)flag;
    // "get" methods for these three exist already in NSWindow.

- (int)orderedIndex;
- (void)setOrderedIndex:(int)index;

- (id)handleSaveScriptCommand:(NSScriptCommand *)command;
- (id)handleCloseScriptCommand:(NSCloseCommand *)command;
- (id)handlePrintScriptCommand:(NSScriptCommand *)command;

@end
