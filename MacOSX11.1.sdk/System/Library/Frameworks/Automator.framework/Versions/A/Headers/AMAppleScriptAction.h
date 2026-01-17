/*	
    AMAppleScriptAction.h
    Copyright (C) 2004-2006, 2014 Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/Foundation.h>
#import <Automator/AMBundleAction.h>
#import <OSAKit/OSAScript.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(ios)

// AMAppleScriptAction

NS_CLASS_AVAILABLE_MAC(10_4)
@interface AMAppleScriptAction : AMBundleAction
{
	@private
	IBOutlet OSAScript *_script;
}

// Accessors
@property (copy, nonatomic, nullable) OSAScript *script;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
