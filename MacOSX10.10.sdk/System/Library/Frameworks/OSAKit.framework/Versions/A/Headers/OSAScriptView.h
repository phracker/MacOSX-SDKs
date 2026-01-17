/*	
    OSAScriptView.h
    Copyright (C) 2005-2014 Apple Inc. All rights reserved.    
    
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
@property (copy) NSString *source;
@property BOOL usesScriptAssistant;
@property BOOL usesTabs;
@property NSUInteger tabWidth;
@property BOOL wrapsLines;
@property BOOL indentsWrappedLines;
@property NSUInteger indentWidth;

@end
