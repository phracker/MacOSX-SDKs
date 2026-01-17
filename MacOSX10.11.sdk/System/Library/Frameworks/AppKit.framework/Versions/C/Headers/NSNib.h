/*
	NSNib.h
	Application Kit
	Copyright (c) 2003-2015, Apple Inc.
	All rights reserved.

NSNib serves as a wrapper around a single InterfaceBuilder nib.  When an NSNib instance is created from a nib file, all of the data needed to instantiate the nib (the object graph as well as images and sounds that might be in the nib bundle) are read from the disk, however the nib is not instantiated until you call one of the instantiation methods.

As such, a nib that is used repeatedly can be loaded from the disk only once, and can then perform countless instantiations, thereby reducing hits to the disk (at the expense of added memory for keeping the unarchived nib data around).

NSNib implements NSCoding protocol.  For example, using NSNib, the entire contents of a nib can be archived and sent to another system for unarchiving.  The target system need not save the nib locally to open it (a shortcoming of the current NSBundle nib loading API).  NSNib's implementation encodes all sound and image resources contained locally within the nib bundle.  Note, it DOES NOT encode resources that are referenced outside of the nib bundle.

As are all NSObjects, instantiated nib objects are allocated in a memory zone (NSZone).  If an NSNibOwner is provided for instantiation, then the objects will be allocated in the owner's zone.  If no NSNibOwner is provided, the resulting objects will be allocated in the default zone.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

@class NSIBObjectData;

@interface NSNib : NSObject <NSCoding> {
   @private
    NSData *_data;
    NSArray *_images;
    NSArray *_sounds;
    NSBundle *_bundle;
    struct _NSNibFlags {
        unsigned int _isKeyed:1;
        unsigned int _inheritsDecodeTimeBundle:1;
        unsigned int _inheritsDecodeTimePath:1;
        unsigned int _reserved:29;
    } _flags;
    NSString *_path;
    id reserved2;
}


// Initializes an instance with a nib file called nibName in the specified bundle.
// If bundle is nil, it tries to find the nib in the main bundle.
// The resulting bundle is used for locating resources such as images and localized
// strings.
//
- (nullable instancetype)initWithNibNamed:(NSString *)nibName bundle:(nullable NSBundle *)bundle;

// Initializes an instance with nib data and specified bundle for locating resources
// such as images and localized strings. If bundle is nil, the main bundle is assumed.
// 
- (instancetype)initWithNibData:(NSData *)nibData bundle:(nullable NSBundle *)bundle NS_AVAILABLE_MAC(10_8);

// Instantiates objects in the nib file with the specified owner.
// Upon success, the method returns YES and the optional out-parameter topLevelObjects is
// populated with the top level objects of the nib. The objects adhere to the standard
// Cocoa memory management rules and are autoreleased. IBOutlet properties to top level
// objects should be strong (retain) to demonstrate ownership and prevent deallocation.
// Alternatively, one may hold a strong reference to the top level objects array.
//
- (BOOL)instantiateWithOwner:(nullable id)owner topLevelObjects:(NSArray * __nonnull * __nullable)topLevelObjects NS_AVAILABLE_MAC(10_8);

@end

@interface NSNib (NSDeprecated)
- (null_unspecified id)initWithContentsOfURL:(null_unspecified NSURL *)nibFileURL NS_DEPRECATED_MAC(10_0, 10_8); // Deprecated in Mac OS X 10.8
- (BOOL)instantiateNibWithExternalNameTable:(null_unspecified NSDictionary *)externalNameTable NS_DEPRECATED_MAC(10_0, 10_8); // Deprecated in Mac OS X 10.8
- (BOOL)instantiateNibWithOwner:(null_unspecified id)owner topLevelObjects:(NSArray * __null_unspecified* __null_unspecified)topLevelObjects NS_DEPRECATED_MAC(10_3, 10_8); // Deprecated in Mac OS X 10.8
@end

// ** External Name Table Keys **
APPKIT_EXTERN NSString * NSNibOwner NS_DEPRECATED_MAC(10_0, 10_8); // Deprecated in Mac OS X 10.8
APPKIT_EXTERN NSString * NSNibTopLevelObjects NS_DEPRECATED_MAC(10_0, 10_8); // Deprecated in Mac OS X 10.8

NS_ASSUME_NONNULL_END
