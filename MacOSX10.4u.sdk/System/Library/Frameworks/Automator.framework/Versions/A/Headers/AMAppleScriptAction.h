/*	
    AMAppleScriptAction.h
    Copyright (C) 2004 Apple Computer, Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/Foundation.h>
#import <Automator/AMBundleAction.h>
#import <OSAKit/OSAScript.h>

// AMAppleScriptAction
// ==================

@interface AMAppleScriptAction : AMBundleAction 
{
@private
    IBOutlet OSAScript *_script;
}

// Accessors
- (OSAScript *)script;
- (void)setScript:(OSAScript *)newScript;

@end
