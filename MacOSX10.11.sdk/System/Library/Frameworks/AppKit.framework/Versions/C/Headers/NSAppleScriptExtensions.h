/*
	NSAppleScriptExtensions.h
	Application Kit
	Copyright (c) 2002-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSAppleScript.h>

NS_ASSUME_NONNULL_BEGIN

@class NSAttributedString;



@interface NSAppleScript(NSExtensions)

// Return the syntax-highlighted source code of the script if the script has been compiled and its source code is available, nil otherwise.  It is possible for an NSAppleScript that has been instantiated with -initWithContentsOfURL:error: to be a script for which the source code is not available, but is nonetheless executable.
@property (nullable, readonly, strong) NSAttributedString *richTextSource;

@end

NS_ASSUME_NONNULL_END

