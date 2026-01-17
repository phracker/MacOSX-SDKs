/*
	ScreenSaverDefaults.h
	ScreenSaver
	Copyright (c) 2000-2, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/Foundation.h>

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

+ (id) defaultsForModuleWithName:(NSString *)inModuleName;

@end
