/*
    NSTitlebarAccessoryViewController.h
    Application Kit
    Copyright (c) 2014, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSViewController.h>
#import <AppKit/NSLayoutConstraint.h>

@class NSClipView;

/* For use with NSWindow's API addTitlebarAccessoryViewController:, etc. */
NS_CLASS_AVAILABLE(10_10, NA)
@interface NSTitlebarAccessoryViewController : NSViewController {
@private
    NSLayoutAttribute _layoutAttribute;
    CGFloat _fullScreenMinHeight;
    NSClipView *_containingClipView;
    CGFloat _revealAmount;
    BOOL _inFullScreen;
    BOOL _isToolbarAccessoryView;
    NSInteger _updateCount;
    
    unsigned int _isInspectorBarView:1;
    unsigned int _forceVisible:1;
    unsigned int _updatingFrame:1;
    unsigned int _registered:1;
    unsigned int _reservedTVC:28;
#if !__OBJC2__
    id _reservedAVC;
    id _reservedAVC2;
#endif
}

/* The layoutAttribute defaults to NSLayoutAttributeBottom, telling the window to place this view controller's view under the titlebar. NSLayoutAttributeRight is also supported, telling the window to place the view controller's view on the right side of the window. All other values are currently invalid and will assert.
 */
@property NSLayoutAttribute layoutAttribute;

/* The fullScreenMinHeight controls the visual minimum height of the view when it is in full screen. It only applies to controllers with the layoutAttribute set to NSLayoutAttributeBottom. Note that the view's height is never actually changed, and it is automatically clipped by an internal clip view.
 
    The minimum height is used when the menu bar is hidden. A minimum height of 0 will fully hide the view when the menu bar is hidden. 
 
    To always show a portion of the view, set the fullScreenMinHeight to some value greater than 0. To always have the view fully shown (i.e.: a fixed height accessory view), set the fullScreenMinHeight to the view.frame.size.height (and be sure to update it if you ever change the view's height).
 
    The default value is 0.
*/
@property CGFloat fullScreenMinHeight;

- (void)viewWillAppear NS_REQUIRES_SUPER;
- (void)viewDidAppear NS_REQUIRES_SUPER;
- (void)viewDidDisappear NS_REQUIRES_SUPER;

/* NOTE: Do not override the -view property! Instead, override loadView, and set the view property in that method (i.e.: self.view = ...; )
 */

@end