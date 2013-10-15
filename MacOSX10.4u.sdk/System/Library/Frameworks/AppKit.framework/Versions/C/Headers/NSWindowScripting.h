/*
        NSWindowScripting.h
        AppKit Framework
        Copyright (c) 1997-2004, Apple Computer, Inc.
        All rights reserved.
*/

#import <AppKit/NSWindow.h>

@class NSCloseCommand;
@class NSScriptCommand;

@interface NSWindow(NSScripting)

// Key value coding (KVC) compliant get-accessors for the same-named attributes declared in Cocoa's definition of the Standard Suite.  The -isMiniaturized, -isVisible, and -isZoomed methods, declared in NSWindow.h, also serve as KVC accessors.
- (BOOL)hasCloseBox;
- (BOOL)hasTitleBar;
- (BOOL)isFloatingPanel;
- (BOOL)isMiniaturizable;
- (BOOL)isModalPanel;
- (BOOL)isResizable;
- (BOOL)isZoomable;
- (int)orderedIndex;

// Key value coding compliant set-accessors for the like-named attributes declared in Cocoa's definition of the Standard Suite.  Attributes that don't have corresponding methods here are read-only.
- (void)setIsMiniaturized:(BOOL)flag;
- (void)setIsVisible:(BOOL)flag;
- (void)setIsZoomed:(BOOL)flag;
- (void)setOrderedIndex:(int)index;

// Handlers for script commands declared in Cocoa's definition of the Standard suite.
- (id)handleCloseScriptCommand:(NSCloseCommand *)command;
- (id)handlePrintScriptCommand:(NSScriptCommand *)command;
- (id)handleSaveScriptCommand:(NSScriptCommand *)command;

@end
