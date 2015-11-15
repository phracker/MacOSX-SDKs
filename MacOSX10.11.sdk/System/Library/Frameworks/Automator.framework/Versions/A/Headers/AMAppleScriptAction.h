/*	
    AMAppleScriptAction.h
    Copyright (C) 2004-2006, 2014 Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/Foundation.h>
#import <Automator/AMBundleAction.h>
#import <OSAKit/OSAScript.h>

NS_ASSUME_NONNULL_BEGIN

// AMAppleScriptAction
// ==================

NS_CLASS_AVAILABLE_MAC(10_4)
@interface AMAppleScriptAction : AMBundleAction {
@private
    IBOutlet OSAScript *_script;
}

// Accessors
@property (strong) OSAScript *script;

@end

NS_ASSUME_NONNULL_END
