/*	NSProcessInfo.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

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

- (unsigned int)operatingSystem;
- (NSString *)operatingSystemName;

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (NSString *)operatingSystemVersionString;	/* Human readable, localized; appropriate for displaying to user or using in bug emails and such; NOT appropriate for parsing */
#endif

@end
