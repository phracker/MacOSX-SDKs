/*	SBApplication.h
	Copyright (c) 2006, Apple, Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <CoreServices/CoreServices.h>
#import <ScriptingBridge/SBObject.h>


@interface SBApplication : SBObject <NSCoding>

- (id) initWithBundleIdentifier:(NSString *)ident;
- (id) initWithURL:(NSURL *)url;
- (id) initWithProcessIdentifier:(pid_t)pid;
	// Initializers.  These will dynamically create a subclass of SBApplication
	// based on the target application's scripting interface and return an
	// instance of that class.  (If the application does not have a scripting
	// interface, they will return an instance of SBApplication.)

+ (id) applicationWithBundleIdentifier:(NSString *) ident;
+ (id) applicationWithURL:(NSURL *) url;
+ (id) applicationWithProcessIdentifier:(pid_t) pid;
	// Convenience factory methods.  "[SBApplication applicationWith...:]" is
	// equivalent to "[[[SBApplication alloc] initWith...:] autorelease]".

- (Class) classForScriptingClass:(NSString *) className;
	// Returns the Objective-C class that represents the specified scripting object
	// class.  The class name is as it appears in the scripting interface, for
	// example, "document".

- (BOOL) isRunning;
	// Is the application running?  This may be "NO" for instances initialized with a
	// bundle identifier or URL; SBApplication does not launch the application until it's
	// necessary to send it an event.

- (void) activate;
	// Bring the application to the foreground.

- (id) delegate;
- (void) setDelegate:(id)delegate;
	// Delegate for event handling; see the SBApplicationDelegate protocol.

- (LSLaunchFlags) launchFlags;
- (void) setLaunchFlags:(LSLaunchFlags)flags;
	// Mode flags for launching applications; see LSOpenApplication for parameter details.

- (AESendMode) sendMode;
- (void) setSendMode:(AESendMode)sendMode;
	// Mode flags for sending events; see AESendMessage for parameter details.

- (long) timeout;
- (void) setTimeout:(long)timeout;
	// How long to wait for an event reply, in ticks; see AESendMessage.

@end


@interface NSObject (SBApplicationDelegate)

- (id) eventDidFail:(const AppleEvent *)event withError:(NSError *)error;
	// The target application failed to handle the event.  If you return a result,
	// it will become the result of the -sendEvent that failed.

@end


@interface SBApplication (SBGlueInterface)
// These methods, while public, are primarily intended for use by sdp-generated glue
// code.  You are not expected to use them directly, but you may, for example, to control
// a generic application without glue.

- (NSDictionary *) classNamesForCodes;
	// Returns a dictionary mapping from 4-byte codes (as NSNumbers) to class names (as
	// NSStrings).  This allows other methods that return SBObjects to return a particular
	// subclass of SBObject.

- (NSDictionary *) codesForPropertyNames;
	// Returns a dictionary mapping from property names to 4-byte codes (as NSNumbers).
	// This allows -[SBElementArray filteredArrayUsingPredicate:] to construct an object
	// specifier from the predicate.

@end
