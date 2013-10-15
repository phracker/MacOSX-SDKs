/*
 * NSJavaConfiguration.h
 *
 * Copyright (c) 1997-2001, Apple Computer, Inc.
 * All Rights Reserved.
 *
 * LaurentR- April, 2000
 *    - added:
 *             NSDefaultJavaLibraryKey
 *             NSDefaultJavaDebugLibraryKey
 *             NSDefaultObjCJavaLibraryKey
 *             NSDefaultObjCJavaDebugLibraryKey
 *             NSJavaVMArgumentsKey
 */

#import <Foundation/Foundation.h>

// The configuration dictionary contains a set of vendor-specific key/value
// pairs and a set of default key/value pairs.  If no vendor is specified,
// NSJavaConfiguration uses the NSDefaultJavaVendorKey key to determine which
// vendor-specific dictionary should be searched before the top-level dictionary// is searched.  eg.:
/*
    {
	Vendor = sun;
	default = {
	    DefaultClasspath = "/NextLibrary/Java";
	};
	next = {
	    Compiler = "/usr/bin/javac";
	    VM = "/usr/bin/java";
	};
	sun = {
	    Compiler = "/NextLibrary/JDK/bin/javac";
	    VM = "/NextLibrary/JDK/bin/java";
	};
    }
*/
// In this case, if no vendor is specified, the `sun' mappings will be searched
// first.  The value for `VM' would be "/NextLibrary/JDK/bin/java" and the value
// for `DefaultClasspath' would be "/NextLibrary/Java".
//
// This search patter is applied to three dictionaries, in order:
//    - the JavaConfiguration dictionary in the defaults for the application
//    - the dictionary in the "JavaConfiguration" domain of the user defaults
//    - the configuration file (/NextLibrary/Java/JavaConfig.plist).
// This permits per-application, per-user and per-system specifications.


extern NSString *NSDefaultJavaVendorKey;

extern NSString *NSDefaultJavaVMKey;
extern NSString *NSDefaultJavaCompilerKey;
extern NSString *NSDefaultJavaClassPathKey;
extern NSString *NSDefaultJavaLibraryKey;
extern NSString *NSDefaultJavaDebugLibraryKey;
extern NSString *NSDefaultObjCJavaLibraryKey;
extern NSString *NSDefaultObjCJavaDebugLibraryKey;
extern NSString *NSJavaVMArgumentsKey;


@interface NSJavaConfiguration : NSObject
{
    NSString *_vendorName;
}

+ (NSJavaConfiguration *) defaultConfiguration;

+ (NSJavaConfiguration *) configurationForVendor:(NSString *)vendorName;
+ (NSArray *) vendorNames;

- init;
- initWithVendor:(NSString *)vendorName;
- (NSString *) vendorName;

- valueForKey:(NSString *)keyName;
- valueForKey:(NSString *)keyName expandEnvironmentVariables:(BOOL)flag;

@end

