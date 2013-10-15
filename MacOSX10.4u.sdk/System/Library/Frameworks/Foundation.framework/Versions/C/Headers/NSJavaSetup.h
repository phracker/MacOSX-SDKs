/*	NSJavaSetup.h
	Copyright (c) 1997-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSDictionary, NSBundle, NSArray;

FOUNDATION_EXPORT NSString * const NSJavaClasses;
FOUNDATION_EXPORT NSString * const NSJavaRoot;
FOUNDATION_EXPORT NSString * const NSJavaPath;
FOUNDATION_EXPORT NSString * const NSJavaUserPath;
FOUNDATION_EXPORT NSString * const NSJavaLibraryPath;
FOUNDATION_EXPORT NSString * const NSJavaOwnVirtualMachine;

FOUNDATION_EXPORT NSString * const NSJavaPathSeparator;

FOUNDATION_EXPORT BOOL NSJavaNeedsVirtualMachine(NSDictionary *plist);
FOUNDATION_EXPORT BOOL NSJavaProvidesClasses(NSDictionary *plist);
FOUNDATION_EXPORT BOOL NSJavaNeedsToLoadClasses(NSDictionary *plist);

FOUNDATION_EXPORT NSString * const NSJavaWillSetupVirtualMachineNotification;
FOUNDATION_EXPORT NSString * const NSJavaDidSetupVirtualMachineNotification;

FOUNDATION_EXPORT NSString * const NSJavaWillCreateVirtualMachineNotification;
FOUNDATION_EXPORT NSString * const NSJavaDidCreateVirtualMachineNotification;

FOUNDATION_EXPORT id NSJavaSetup(NSDictionary *plist);  // Setup if needed.
FOUNDATION_EXPORT id NSJavaSetupVirtualMachine(void);	// Setup in any case.

FOUNDATION_EXPORT id NSJavaObjectNamedInPath(NSString *name, NSArray *path);

FOUNDATION_EXPORT NSArray *NSJavaClassesFromPath(NSArray *path, NSArray *wanted, BOOL usesyscl, id *vm);
FOUNDATION_EXPORT NSArray *NSJavaClassesForBundle(NSBundle *bundle, BOOL usesyscl, id *vm);

// These functions are obsolete now...

FOUNDATION_EXPORT id NSJavaBundleSetup(NSBundle *bundle, NSDictionary *plist);
FOUNDATION_EXPORT void NSJavaBundleCleanup(NSBundle *bundle, NSDictionary *plist);

