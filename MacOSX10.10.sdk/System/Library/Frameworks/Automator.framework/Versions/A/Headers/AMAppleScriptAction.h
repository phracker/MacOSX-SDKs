/*	
    AMAppleScriptAction.h
    Copyright (C) 2004-2006, 2014 Apple Inc. All rights reserved.    
    
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
@property (strong) OSAScript *script;

@end