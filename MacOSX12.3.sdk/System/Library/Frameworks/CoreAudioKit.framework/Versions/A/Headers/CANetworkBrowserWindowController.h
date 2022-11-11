/*
	File:      CANetworkBrowserWindowController.h
 
	Contains:  Class definition for a window controller that displays available network audio devices (including AVB). The user can connect to one or more of those devices to use exclusively with his mac.
 
	Copyright: (c) 2015 by Apple, Inc. All rights reserved.
 
	Bugs?:      For bug reports, consult the following page on the World Wide Web:
 
	http://developer.apple.com/bugreporter/
 */

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@class CANetworkBrowserImpl;

/*!
 @class CANetworkBrowserWindowController
 @abstract  A window controller object that can present a window that displays available network audio devices (including AVB). The user can connect to one or more of those devices to use exclusively with his mac.
 
 @discussion To use this class, create an instance of the CANetworkBrowserWindowController, initialize it, and call showWindow: to display the UI.
 */
API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios, tvos, watchos)
@interface CANetworkBrowserWindowController : NSWindowController {
@private
    CANetworkBrowserImpl *_impl;
}

/*!
 * @discussion Provides a check for determining if the current machine hardware supports AVB.
 * @return True if AVB is supported.
 */
+(BOOL) isAVBSupported;

/*!
 * @discussion Designated initializer
   @return initialized instance of CANetworkBrowerWindowController
 */
-(instancetype) init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
