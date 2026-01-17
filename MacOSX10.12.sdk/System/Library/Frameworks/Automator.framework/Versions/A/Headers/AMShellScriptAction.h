/*	
    AMShellScriptAction.h
    Copyright (C) 2005-2006, 2014 Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/Foundation.h>
#import <Automator/AMBundleAction.h>


NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_MAC(10_4)
@interface AMShellScriptAction : AMBundleAction 

// If you want to automatically have the class remap '\r' to '\n'
// before passing it to your shell script, override this to return YES (default=NO).
@property (readonly) BOOL remapLineEndings;

// Use this string (default=@"\n") to join multiple fields
// e.g., use @"\0" for null-terminated strings for use with xargs -0
@property (readonly, copy) NSString *inputFieldSeparator;

// If non-nil, use this string (default=inputFieldSeparator) to break the text output
// into multiple fields, which will be return as an NSArray
@property (readonly, copy) NSString *outputFieldSeparator;

@end

NS_ASSUME_NONNULL_END
