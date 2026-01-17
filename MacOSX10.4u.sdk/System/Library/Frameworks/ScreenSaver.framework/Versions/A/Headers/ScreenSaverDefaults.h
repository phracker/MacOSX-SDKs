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
		void			*_reserved4;
		void			*_reserved5;
}

+ (id) defaultsForModuleWithName:(NSString *)inModuleName;

@end
