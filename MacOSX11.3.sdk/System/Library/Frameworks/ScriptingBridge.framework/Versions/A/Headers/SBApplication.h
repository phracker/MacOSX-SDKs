/*	SBApplication.h
	Copyright (c) 2006, Apple, Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <CoreServices/CoreServices.h>
#import <ScriptingBridge/SBObject.h>


NS_ASSUME_NONNULL_BEGIN

@protocol SBApplicationDelegate;

NS_CLASS_AVAILABLE(10_5, NA)
@interface SBApplication : SBObject <NSCoding>

- (nullable __kindof SBApplication *) initWithBundleIdentifier:(NSString *)ident;
- (nullable __kindof SBApplication *) initWithURL:(NSURL *)url;
- (nullable __kindof SBApplication *) initWithProcessIdentifier:(pid_t)pid;
	// Initializers.  These will dynamically create a subclass of SBApplication
	// based on the target application's scripting interface and return an
	// instance of that class.  (If the application does not have a scripting
	// interface, they will return an instance of SBApplication.)

+ (nullable __kindof SBApplication *) applicationWithBundleIdentifier:(NSString *) ident;
+ (nullable __kindof SBApplication *) applicationWithURL:(NSURL *) url;
+ (nullable __kindof SBApplication *) applicationWithProcessIdentifier:(pid_t) pid;
	// Convenience factory methods.  "[SBApplication applicationWith...:]" is
	// equivalent to "[[[SBApplication alloc] initWith...:] autorelease]".

- (nullable Class) classForScriptingClass:(NSString *) className;
	// Returns the Objective-C class that represents the specified scripting object
	// class.  The class name is as it appears in the scripting interface, for
	// example, "document".

@property (readonly, getter=isRunning) BOOL running;
	// Is the application running?  This may be "NO" for instances initialized with a
	// bundle identifier or URL; SBApplication does not launch the application until it's
	// necessary to send it an event.

- (void) activate;
	// Bring the application to the foreground.

@property (nullable, strong) id <SBApplicationDelegate> delegate;
	// Delegate for event handling; see the SBApplicationDelegate protocol.

@property LSLaunchFlags launchFlags;
	// Mode flags for launching applications; see LSOpen.h.

@property AESendMode sendMode;
	// Mode flags for sending events; see AESendMessage for parameter details.

@property long timeout;
	// How long to wait for an event reply, in ticks; see AESendMessage.

@end


@protocol SBApplicationDelegate

- (nullable id) eventDidFail:(const AppleEvent *)event withError:(NSError *)error;
	// The target application failed to handle the event.  If you return a result,
	// it will become the result of the -sendEvent that failed.

@end

NS_ASSUME_NONNULL_END
