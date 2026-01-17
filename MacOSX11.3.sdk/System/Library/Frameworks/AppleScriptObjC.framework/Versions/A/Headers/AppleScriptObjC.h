/*
	AppleScriptObjC.h
	Copyright (c) 2008-2009, Apple Inc.  All rights reserved
*/

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSBundle (AppleScriptObjectiveC)

- (void) loadAppleScriptObjectiveCScripts AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

NS_ASSUME_NONNULL_END
