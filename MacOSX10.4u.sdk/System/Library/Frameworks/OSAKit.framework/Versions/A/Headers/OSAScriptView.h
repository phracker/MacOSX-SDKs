/*	
    OSAScriptView.h
    Copyright (C) 2005 Apple Computer, Inc. All rights reserved.    
    
    Public header file.
*/


#import <Cocoa/Cocoa.h>

@class OSAScriptViewPrivate;

// OSAScriptView
// =============

@interface OSAScriptView : NSTextView
{
@private
	OSAScriptViewPrivate *_private;
}

// Accessors
- (NSString *)source;
- (void)setSource:(NSString *)source;
- (BOOL)usesScriptAssistant;
- (void)setUsesScriptAssistant:(BOOL)usesScriptAssistant;
- (BOOL)usesTabs;
- (void)setUsesTabs:(BOOL)usesTabs;
- (int)tabWidth;
- (void)setTabWidth:(int)tabWidth;
- (BOOL)wrapsLines;
- (void)setWrapsLines:(BOOL)wrapsLines;
- (BOOL)indentsWrappedLines;
- (void)setIndentsWrappedLines:(BOOL)indentsWrappedLines;
- (int)indentWidth;
- (void)setIndentWidth:(int)indentWidth;

@end
