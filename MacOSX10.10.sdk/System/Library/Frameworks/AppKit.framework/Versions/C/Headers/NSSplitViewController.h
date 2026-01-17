/*
    NSSplitViewController.h
    Application Kit
    Copyright (c) 2014, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSViewController.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSSplitView.h>

@class NSSplitViewItem;

/*!
 * NSSplitViewController is a container view controller that manages side-by-side (horizontal or vertical) children view controllers.
 * Views are lazily loaded. For instance, adding a collapsed SplitViewItem will not load the associated ViewController's view until it is uncollapsed.
 * The NSSplitViewController is set as the delegate of its managed NSSplitView. Any overrides of NSSplitViewDelegate methods must call super.
 * Only the \c -vertical, \c -autosaveName, and divider properties should be manipulated on the managed NSSplitView. Changing other properties (such as delegate, manipulating subviews, holding priorities) will cause an exception to be thrown.
 * Autolayout must be used with NSSplitViewController to properly control the layout of the child views and the animations of collapses and reveals. e.g., Constraints can be used to setup whether a window should grow/shrink or stay the same size when showing and hiding a sidebar.
 * NSViewController's methods \c -addChildViewController:, \c -insertViewController:atIndex:, and \c -removeChildViewControllerAtIndex: can all be used as convience methods to add children; default SplitViewItems will be appropriately created or destroyed.
 */
NS_CLASS_AVAILABLE_MAC(10_10)
@interface NSSplitViewController : NSViewController <NSSplitViewDelegate> {
@private
    NSSplitView *_splitView;
    id _splitViewControllerPrivateData;
    struct {
        unsigned int _reserved:32;
    } _splitViewControllerFlags;
}

/// The split view managed by the SplitViewController. This can be used to customize view properties such as the dividerStyle, vertical, and autosaveName. It is not guaranteed to be the save view as the receivers 'view' property. The default created splitView is vertical with a dividerStyle of \c NSSplitViewDividerStyleThin. To provide a custom NSSplitView, set the splitView property anytime before self.viewLoaded is YES (e.g., before calling super in -viewDidLoad).
@property (strong) NSSplitView *splitView;

/// The array of SplitViewItems that correspond to the current child view controllers. After a child view controller is added to the receiving splitViewController, a NSSplitViewItem with the default values will be created for it. Once the child is removed, its corresponding splitViewItem will be removed from the splitViewItems array. Setting this will call through to \c -insertSplitViewItem:atIndex and \c -removeSplitViewItem: for items that are new or need removal.
@property (copy) NSArray *splitViewItems;

/*!
 * Adds a SplitViewItem to the end of the SplitViewController. If the receiver's view is loaded and the SplitViewItem is not collapsed, the SplitViewItem's viewController's view will be loaded and added to the splitView. This calls through to -insertSplitViewItem:atIndex:.
 * \param splitViewItem The SplitViewItem to add. It must have a viewController set by the time it is added or an exception will be thrown. An exception will also be thrown if splitViewItem is nil.
 */
- (void)addSplitViewItem:(NSSplitViewItem *)splitViewItem;

/*!
 * Adds a SplitViewItem to a given index in the SplitViewController. If the receiver's view is loaded and the SplitViewItem is not collapsed, the SplitViewItem's viewController's view will be loaded and added to the \c splitView. Subclasses must call through \c -insertSplitViewItem:atIndex: to add a SplitViewItem.
 * \param splitViewItem The SplitViewItem to add. It must have a \c viewController set by the time it is added or an exception will be thrown. An exception will also be thrown if splitViewItem is nil.
 * \param index The index to add the SplitViewItem at. Will throw an exception if \c index < 0 or \c index > \c splitViewItems.count
 */
- (void)insertSplitViewItem:(NSSplitViewItem *)splitViewItem atIndex:(NSInteger)index;

/*!
 * Removes a SplitViewItem from the receiver. The layout of the \c splitView will be adjusted for its removal. Subclasses must call through \c -removeSplitViewItem: to remove a SplitViewItem.
 * \param splitViewItem The SplitViewItem to remove. An exception will be thrown if \c splitViewItem is not in the SplitViewController or if it is nil.
 */
- (void)removeSplitViewItem:(NSSplitViewItem *)splitViewItem;

/*!
 * Returns the corresponding SplitViewItem for a given child ViewController.
 * \param viewController The ViewController to look up.
 * \return The corresponding SplitViewItem. Returns nil if \c viewController is not a child of the SplitViewController.
 */
- (NSSplitViewItem *)splitViewItemForViewController:(NSViewController *)viewController;

/* Overridden methods from NSViewController. These require a call to super if overriden by a subclass */
- (void)viewDidLoad NS_REQUIRES_SUPER;

/* Implemented methods from NSSplitViewDelegate. These require a call to super if overriden by a subclass */
- (BOOL)splitView:(NSSplitView *)splitView canCollapseSubview:(NSView *)subview NS_REQUIRES_SUPER;
- (BOOL)splitView:(NSSplitView *)splitView shouldCollapseSubview:(NSView *)subview forDoubleClickOnDividerAtIndex:(NSInteger)dividerIndex NS_REQUIRES_SUPER;
- (BOOL)splitView:(NSSplitView *)splitView shouldHideDividerAtIndex:(NSInteger)dividerIndex NS_REQUIRES_SUPER; // By default, NSSplitViewController hides the first and last dividers if their outer neighbor is collapsed
- (NSRect)splitView:(NSSplitView *)splitView effectiveRect:(NSRect)proposedEffectiveRect forDrawnRect:(NSRect)drawnRect ofDividerAtIndex:(NSInteger)dividerIndex NS_REQUIRES_SUPER;
- (NSRect)splitView:(NSSplitView *)splitView additionalEffectiveRectOfDividerAtIndex:(NSInteger)dividerIndex NS_REQUIRES_SUPER;
@end


/*!
 * NSSplitViewItem implements the items used in an NSSplitViewController.
 * The item describes a child ViewController's state in a SplitViewController, i.e. its collapsibility, holding priority, and collapsed state.
 */
NS_CLASS_AVAILABLE_MAC(10_10)
@interface NSSplitViewItem : NSObject <NSAnimatablePropertyContainer, NSCoding> {
@private
    id _splitViewItemPrivateData;
    struct {
        unsigned int _collapsed:1;
        unsigned int _canCollapseFromDrag:1;
        unsigned int _canCollapseFromDoubleClickOnDivider:1;
        unsigned int _reserved:29;
    } _flags;
}

/*!
 * Creates an autoreleased SplitViewItem that represents the provided ViewController. All other properties are left at their default.
 * \param viewController The view controller used to set the viewController property
 * \return An autoreleased SplitViewItem.
 */
+ (instancetype)splitViewItemWithViewController:(NSViewController *)viewController;

/// The view controller represented by the SplitViewItem. An exception will be thrown if a new viewController is set while the receiving SplitViewItem is added to a SplitViewController.
@property (strong) NSViewController *viewController;

/// Whether or not the child ViewController corresponding to the SplitViewItem is collapsed in the SplitViewController. The default is \c NO. This can be set with the animator proxy to animate the collapse or uncollapse. The exact animation used can be customized by setting it in the -animations dictionary with a key of "collapsed". If this is set to YES before it is added to the SplitViewController, it will be initially collapsed and the SplitViewController will not cause the view to be loaded until it is uncollapsed. This is KVC/KVO compliant and will be updated if the value changes from user interaction.
@property (getter=isCollapsed) BOOL collapsed;

/// Whether or not the child view controller is collapsible from user interaction - whether by dragging or double clicking a divider. The default is \c NO.
@property BOOL canCollapse;

/// Sets the priority under which a SplitViewItem will hold its width (for a vertical split view) or height (for a horizontal split view). The view with the lowest priority will be the first to take on additional width if the split view grows or shrinks. The default is \c NSLayoutPriorityDefaultLow.
@property NSLayoutPriority holdingPriority;
@end
