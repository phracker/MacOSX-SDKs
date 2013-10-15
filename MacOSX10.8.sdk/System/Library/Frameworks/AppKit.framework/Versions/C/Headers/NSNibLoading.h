/*
	NSNibLoading.h
	Application Kit
	Copyright (c) 1994-2012, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSBundle.h>

@class NSString, NSDictionary;

@interface NSBundle(NSNibLoading)

- (BOOL)loadNibNamed:(NSString *)nibName owner:(id)owner topLevelObjects:(NSArray **)topLevelObjects NS_AVAILABLE_MAC(10_8);
    /* Load a nib from this bundle with the specified file name and owner. Upon success, the method returns success or failure. The out-parameter topLevelObjects is populated with the top level objects of the nib. Unlike legacy methods, the objects adhere to the standard cocoa memory management rules; it is necessary to keep a strong reference to them by using IBOutlets or holding a reference to the array to prevent the nib contents from being deallocated.  Outlets to top level objects should be strong (retain) to demonstrate ownership and prevent deallocation. */

@end

@interface NSObject (NSNibAwaking)
- (void)awakeFromNib;
    /* On Mac OS X 10.6 and later, NSObject provides an implementation of awakeFromNib. This means that you can safely call through to [super awakeFromNib] in an overridden implementation when running on Mac OS X 10.6 and later. */
@end

@interface NSBundle (NSNibLoadingDeprecated)
+ (BOOL)loadNibFile:(NSString *)fileName externalNameTable:(NSDictionary *)context withZone:(NSZone *)zone; // Deprecated in Mac OS X 10.8
+ (BOOL)loadNibNamed:(NSString *)nibName owner:(id)owner; // Deprecated in Mac OS X 10.8
- (BOOL)loadNibFile:(NSString *)fileName externalNameTable:(NSDictionary *)context withZone:(NSZone *)zone; // Deprecated in Mac OS X 10.8
@end
