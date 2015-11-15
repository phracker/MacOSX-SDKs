/*
	ScreenSaverDefaults.h
	ScreenSaver
	Copyright (c) 2000-2, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ScreenSaverDefaults : NSUserDefaults
{
@private
	NSMutableDictionary		*_defaults;
	NSMutableDictionary		*_registeredDefaults;
	NSString				*_userName;
	NSString				*_domainName;
	BOOL					_dirty;
	BOOL					_screenLockPrefChanged;
}

+ (nullable instancetype) defaultsForModuleWithName:(NSString *)inModuleName;

@end

NS_ASSUME_NONNULL_END