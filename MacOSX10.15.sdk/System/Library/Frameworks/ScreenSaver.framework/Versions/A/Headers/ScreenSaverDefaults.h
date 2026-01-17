/*
	ScreenSaverDefaults.h
	ScreenSaver
	Copyright (c) 2000-2016, Apple Inc.
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
}

+ (nullable instancetype) defaultsForModuleWithName:(NSString *)inModuleName;

@end

NS_ASSUME_NONNULL_END
