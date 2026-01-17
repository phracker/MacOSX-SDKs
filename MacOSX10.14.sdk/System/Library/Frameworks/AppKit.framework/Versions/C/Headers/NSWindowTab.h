/*
    NSWindowTab.h
    Application Kit
    Copyright (c) 2016-2018, Apple Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/AppKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSWindow, NSView, NSTabBarItem, NSImage;

/* This class encapsulates all the state and properties for a window when it exists in a tabbed window environment. See [NSWindow allowsAutomaticWindowTabbing] and [NSWindow tabbingIdentifier]. These properties can be set at anytime, but will only take effect when the window is shown in a tab.
 */
NS_CLASS_AVAILABLE_MAC(10_13)
@interface NSWindowTab : NSObject {
@private
    NSString *_title APPKIT_IVAR;
    NSAttributedString *_attributedTitle APPKIT_IVAR;
    NSString *_toolTip APPKIT_IVAR;
    NSImage *_image APPKIT_IVAR;
    NSView *_accessoryView APPKIT_IVAR;
    NSTabBarItem *_tabBarItem APPKIT_IVAR;
    __weak NSWindow *_window APPKIT_IVAR;

#if !__OBJC2__
    void *_extraReserved[2] __unused APPKIT_IVAR;
#endif
}

/* The tab title for this window when in a tab. By default it follows the window.title. You can override this by explicitly setting it to something custom. Setting it to nil will make it follow the window.title again. */
@property (copy, null_resettable) NSString *title;

/* The attributed string tab title for this window when in a tab. This value is only used when non-nil; otherwise the title is used. The attributedTitle will use the provided attributes that are explicitly given. Attributes not given, such as the font type, color and size, will default to the correct values for the window tab. */
@property (copy, nullable) NSAttributedString *attributedTitle;

/* The tool tip for this window when in a tab. By default, it is self.title but can be set to something custom. Setting it back to nil will make it follow self.title again.
 */
@property (copy, null_resettable) NSString *toolTip;

/* Get and set the accessory view for this window when it is in a tabbed window. translatesAutoresizingMaskIntoConstraints will automatically be set to NO on the view. Constraints can be created and activated to specify the view's width and height values. A constraint will automatically be added to y-center the view, and to right align the view.
 */
@property (strong, nullable) NSView *accessoryView;

@end


NS_ASSUME_NONNULL_END
