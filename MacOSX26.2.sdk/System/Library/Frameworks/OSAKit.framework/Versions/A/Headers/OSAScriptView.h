/*	
    OSAScriptView.h
    Copyright (C) 2005-2015 Apple Inc. All rights reserved.    
    
    Public header file.
*/


#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN
API_UNAVAILABLE_BEGIN(ios)

@class OSAScriptViewPrivate;

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

API_UNAVAILABLE_END
NS_ASSUME_NONNULL_END
