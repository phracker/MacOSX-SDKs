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
- (NSUInteger)tabWidth;
- (void)setTabWidth:(NSUInteger)tabWidth;
- (BOOL)wrapsLines;
- (void)setWrapsLines:(BOOL)wrapsLines;
- (BOOL)indentsWrappedLines;
- (void)setIndentsWrappedLines:(BOOL)indentsWrappedLines;
- (NSUInteger)indentWidth;
- (void)setIndentWidth:(NSUInteger)indentWidth;

@end
