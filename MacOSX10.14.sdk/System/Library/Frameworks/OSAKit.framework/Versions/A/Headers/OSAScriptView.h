/*	
    OSAScriptView.h
    Copyright (C) 2005-2015 Apple Inc. All rights reserved.    
    
    Public header file.
*/


#import <Cocoa/Cocoa.h>

@class OSAScriptViewPrivate;

NS_ASSUME_NONNULL_BEGIN

// OSAScriptView
// =============

@interface OSAScriptView : NSTextView
{
@private
	OSAScriptViewPrivate *_private;
}

// Accessors
@property (nullable, copy) NSString *source;
@property BOOL usesScriptAssistant;
@property BOOL usesTabs;
@property NSUInteger tabWidth;
@property BOOL wrapsLines;
@property BOOL indentsWrappedLines;
@property NSUInteger indentWidth;

@end

NS_ASSUME_NONNULL_END
