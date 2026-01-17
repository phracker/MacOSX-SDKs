/*
	ScreenSaverDefaults.h
	ScreenSaver
	Copyright (c) 2000-2020, Apple Inc.
	All rights reserved.
*/

#import <Foundation/Foundation.h>

API_UNAVAILABLE_BEGIN(ios, tvos, watchos)
NS_ASSUME_NONNULL_BEGIN

/// A class that defines a set of methods for saving and restoring user defaults
/// for screen savers.
///
/// ``ScreenSaverDefaults`` gives you access to preference values you need to
/// configure your screen saver. Because multiple apps can load a screen saver,
/// you can’t use the standard
/// <doc://com.apple.documentation/documentation/foundation/nsuserdefaults>
/// object to store preferences. Instead, instantiate this class using the
/// ``ScreenSaverDefaults/defaultsForModuleWithName:`` method, which takes your
/// screen saver’s bundle identifier as a parameter. The resulting object gives
/// you a way to store your preference values and associate them only with your
/// screen saver. Use the inherited
/// <doc://com.apple.documentation/documentation/foundation/nsuserdefaults>
/// methods to load, store, or modify values.
@interface ScreenSaverDefaults : NSUserDefaults
{
@private
	NSMutableDictionary		*_defaults;
	NSMutableDictionary		*_registeredDefaults;
	NSString				*_userName;
	NSString				*_domainName;
	BOOL					_dirty;
}

/// Returns a screen saver defaults instance that reads and writes defaults for the specified
/// module.
///
/// - Parameters:
///   - inModuleName: The bundle identifier for the module.
+ (nullable instancetype) defaultsForModuleWithName:(NSString *)inModuleName;

@end

NS_ASSUME_NONNULL_END
API_UNAVAILABLE_END
