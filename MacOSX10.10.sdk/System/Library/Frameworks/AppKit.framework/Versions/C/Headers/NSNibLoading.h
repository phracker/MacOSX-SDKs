/*
	NSNibLoading.h
	Application Kit
	Copyright (c) 1994-2014, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSBundle.h>

@class NSString, NSDictionary;

@interface NSBundle(NSNibLoading)

- (BOOL)loadNibNamed:(NSString *)nibName owner:(id)owner topLevelObjects:(NSArray **)topLevelObjects NS_AVAILABLE_MAC(10_8);
    /* Load a nib from this bundle with the specified file name and owner. Upon success, the method returns YES and the optional out-parameter topLevelObjects is populated with the top level objects of the nib. The objects adhere to the standard Cocoa memory management rules and are autoreleased. IBOutlet properties to top level objects should be strong (retain) to demonstrate ownership and prevent deallocation. Alternatively, one may hold a strong reference to the top level objects array. */

@end

@interface NSObject (NSNibAwaking)
- (void)awakeFromNib;
    /* On Mac OS X 10.6 and later, NSObject provides an implementation of awakeFromNib. This means that you can safely call through to [super awakeFromNib] in an overridden implementation when running on Mac OS X 10.6 and later. */
- (void)prepareForInterfaceBuilder NS_AVAILABLE_MAC(10_10);
@end

@interface NSBundle (NSNibLoadingDeprecated)
+ (BOOL)loadNibFile:(NSString *)fileName externalNameTable:(NSDictionary *)context withZone:(NSZone *)zone NS_DEPRECATED_MAC(10_0, 10_8); // Deprecated in Mac OS X 10.8
+ (BOOL)loadNibNamed:(NSString *)nibName owner:(id)owner NS_DEPRECATED_MAC(10_0, 10_8); // Deprecated in Mac OS X 10.8
- (BOOL)loadNibFile:(NSString *)fileName externalNameTable:(NSDictionary *)context withZone:(NSZone *)zone NS_DEPRECATED_MAC(10_0, 10_8); // Deprecated in Mac OS X 10.8
@end
