/*	NSProcessInfo.h
	Copyright (c) 1994-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

enum {	/* Constants returned by -operatingSystem */
	NSWindowsNTOperatingSystem = 1,
	NSWindows95OperatingSystem,
	NSSolarisOperatingSystem,
	NSHPUXOperatingSystem,
	NSMACHOperatingSystem,
	NSSunOSOperatingSystem,
	NSOSF1OperatingSystem
};

@class NSArray, NSString, NSDictionary;

@interface NSProcessInfo : NSObject {
    @private	
    NSDictionary	*environment;
    NSArray		*arguments;
    NSString		*hostName;    
    NSString		*name;
    void		*reserved;
}

+ (NSProcessInfo *)processInfo;	

- (NSDictionary *)environment;

- (NSArray *)arguments;

- (NSString *)hostName;

- (NSString *)processName;

- (int)processIdentifier;

- (void)setProcessName:(NSString *)newName;

- (NSString *)globallyUniqueString;

- (NSUInteger)operatingSystem;
- (NSString *)operatingSystemName;

- (NSString *)operatingSystemVersionString AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
	/* Human readable, localized; appropriate for displaying to user or using in bug emails and such; NOT appropriate for parsing */

- (NSUInteger)processorCount AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (NSUInteger)activeProcessorCount AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (unsigned long long)physicalMemory AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (NSTimeInterval)systemUptime AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

/* Disable or reenable the ability to be quickly killed. The default implementations of these methods increment or decrement, respectively, a counter whose value is 1 when the process is first created. When the counter's value is 0 the application is considered to be safely killable and may be killed by the operating system without any notification or event being sent to the process first. If an application's Info.plist has an NSSupportsSuddenTermination entry whose value is true then NSApplication invokes -enableSuddenTermination automatically during application launch, which typically renders the process killable right away. You can also manually invoke -enableSuddenTermination right away in, for example, agents or daemons that don't depend on AppKit. After that, you can invoke these methods whenever the process has work it must do before it terminates. For example:
 - NSUserDefaults uses these to prevent process killing between the time at which a default has been set and the time at which the preferences file including that default has been written to disk.
 - NSDocument uses these to prevent process killing between the time at which the user has made a change to a document and the time at which the user's change has been written to disk.
 - You can use these whenever your application defers work that must be done before the application terminates. If for example your application ever defers writing something to disk, and it has an NSSupportsSuddenTermination entry in its Info.plist so as not to contribute to user-visible delays at logout or shutdown time, it must invoke -disableSuddenTermination when the writing is first deferred and -enableSuddenTermination after the writing is actually done.
*/
- (void)disableSuddenTermination AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)enableSuddenTermination AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

#endif

@end

