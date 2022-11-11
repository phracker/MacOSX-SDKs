/*
	ScreenSaverDefaults.h
	ScreenSaver
	Copyright (c) 2000-2020, Apple Inc.
	All rights reserved.
*/

#import <Foundation/Foundation.h>

API_UNAVAILABLE_BEGIN(ios, tvos, watchos)
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
API_UNAVAILABLE_END
