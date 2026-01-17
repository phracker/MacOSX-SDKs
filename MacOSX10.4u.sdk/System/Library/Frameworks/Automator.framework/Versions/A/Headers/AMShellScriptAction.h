/*	
    AMShellScriptAction.h
    Copyright (C) 2005 Apple Computer, Inc. All rights reserved.    
    
    Public header file.
*/

#import <Cocoa/Cocoa.h>
#import <Automator/AMBundleAction.h>

// AMShellScriptAction
// ==================

@interface AMShellScriptAction : AMBundleAction 
{
}

// If you want to automatically have the class remap '\r' to '\n'
// before passing it to your shell script, override this to return YES (default=NO).
- (BOOL) remapLineEndings;

// Use this string (default=@"\n") to join multiple fields
// e.g., use @"\0" for null-terminated strings for use with xargs -0
- (NSString *) inputFieldSeparator;

// If non-nil, use this string (default=inputFieldSeparator) to break the text output
// into multiple fields, which will be return as an NSArray
- (NSString *) outputFieldSeparator;

@end
