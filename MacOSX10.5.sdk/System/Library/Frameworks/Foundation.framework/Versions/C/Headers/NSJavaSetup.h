/*	NSJavaSetup.h
	Copyright (c) 1997-2007, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED
#warning The API is this header is obsolete and deprecated in 10.5.
#warning Stop using this API and including this header.
#endif

@class NSString, NSDictionary, NSBundle, NSArray;

FOUNDATION_EXPORT NSString * const NSJavaClasses DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSJavaRoot DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSJavaPath DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSJavaUserPath DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSJavaLibraryPath DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSJavaOwnVirtualMachine DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

FOUNDATION_EXPORT NSString * const NSJavaPathSeparator DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

FOUNDATION_EXPORT BOOL NSJavaNeedsVirtualMachine(NSDictionary *plist) DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT BOOL NSJavaProvidesClasses(NSDictionary *plist) DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT BOOL NSJavaNeedsToLoadClasses(NSDictionary *plist) DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

FOUNDATION_EXPORT NSString * const NSJavaWillSetupVirtualMachineNotification DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSJavaDidSetupVirtualMachineNotification DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

FOUNDATION_EXPORT NSString * const NSJavaWillCreateVirtualMachineNotification DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSJavaDidCreateVirtualMachineNotification DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

FOUNDATION_EXPORT id NSJavaSetup(NSDictionary *plist) DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;  // Setup if needed.
FOUNDATION_EXPORT id NSJavaSetupVirtualMachine(void) DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;	// Setup in any case.

FOUNDATION_EXPORT id NSJavaObjectNamedInPath(NSString *name, NSArray *path) DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

FOUNDATION_EXPORT NSArray *NSJavaClassesFromPath(NSArray *path, NSArray *wanted, BOOL usesyscl, id *vm) DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSArray *NSJavaClassesForBundle(NSBundle *bundle, BOOL usesyscl, id *vm) DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

// These functions are obsolete now...

FOUNDATION_EXPORT id NSJavaBundleSetup(NSBundle *bundle, NSDictionary *plist) DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT void NSJavaBundleCleanup(NSBundle *bundle, NSDictionary *plist) DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

