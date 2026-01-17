/*
    NSSplitViewController.h
    Application Kit
    Copyright (c) 2014-2015, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <AppKit/NSViewController.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSSplitView.h>

NS_ASSUME_NONNULL_BEGIN

@class NSSplitViewItem;


/// This constant can be used with any sizing related \c NSSplitViewController properties to get the default system behavior.
APPKIT_EXTERN const CGFloat NSSplitViewControllerAutomaticDimension NS_AVAILABLE_MAC(10_11);

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

/// The split view managed by the SplitViewController. This can be used to customize view properties such as the dividerStyle, vertical, and autosaveName. It is not guaranteed to be the same view as the receivers 'view' property. The default created splitView is vertical with a dividerStyle of \c NSSplitViewDividerStyleThin. To provide a custom NSSplitView, set the splitView property anytime before self.viewLoaded is YES.
@property (strong) NSSplitView *splitView;

/// The array of SplitViewItems that correspond to the current child view controllers. After a child view controller is added to the receiving splitViewController, a NSSplitViewItem with the default values will be created for it. Once the child is removed, its corresponding splitViewItem will be removed from the splitViewItems array. Setting this will call through to \c -insertSplitViewItem:atIndex and \c -removeSplitViewItem: for items that are new or need removal.
@property (copy) NSArray<__kindof NSSplitViewItem *> *splitViewItems;

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
- (nullable NSSplitViewItem *)splitViewItemForViewController:(NSViewController *)viewController;

/*!
 * The minimum thickness in the primary axis of split view (width for "vertical", height otherwise) before sidebar items will automatically collapse. If reshown in fullscreen, they will overlay over the other split items.
 * Auto-collapsed sidebars will automatically uncollapse if the thickness is increased back to or past the minimum thickness.
 * Defaults to \c NSSplitViewControllerAutomaticDimension, which will use the effective minimum sizes of the split view item views as described by constraints in the window to determine the minimum size for inline sidebars. Once constraints establishing the minimum size can't be satisfied for all non-collapsed split panes, all sidebars will auto-collapse. When fullscreen, if a sidebar tries to uncollapse in this state, it will overlay.
 */
@property CGFloat minimumThicknessForInlineSidebars NS_AVAILABLE_MAC(10_11);

/* Overridden methods from NSViewController. These require a call to super if overriden by a subclass */
- (void)viewDidLoad NS_REQUIRES_SUPER;

/* Implemented methods from NSSplitViewDelegate. These require a call to super if overriden by a subclass */
- (BOOL)splitView:(NSSplitView *)splitView canCollapseSubview:(NSView *)subview NS_REQUIRES_SUPER;
- (BOOL)splitView:(NSSplitView *)splitView shouldCollapseSubview:(NSView *)subview forDoubleClickOnDividerAtIndex:(NSInteger)dividerIndex NS_REQUIRES_SUPER;
- (BOOL)splitView:(NSSplitView *)splitView shouldHideDividerAtIndex:(NSInteger)dividerIndex NS_REQUIRES_SUPER; // By default, NSSplitViewController hides the first and last dividers if their outer neighbor is collapsed
- (NSRect)splitView:(NSSplitView *)splitView effectiveRect:(NSRect)proposedEffectiveRect forDrawnRect:(NSRect)drawnRect ofDividerAtIndex:(NSInteger)dividerIndex NS_REQUIRES_SUPER;
- (NSRect)splitView:(NSSplitView *)splitView additionalEffectiveRectOfDividerAtIndex:(NSInteger)dividerIndex NS_REQUIRES_SUPER;
@end

@interface NSSplitViewController (NSSplitViewControllerToggleSidebarAction)

/// Animatedly collapses or uncollapses the first sidebar split view item in the receiver. Does nothing if the receiver does not contain any sidebars.
- (IBAction)toggleSidebar:(nullable id)sender NS_AVAILABLE_MAC(10_11);

@end


typedef NS_ENUM(NSInteger, NSSplitViewItemBehavior) {
    NSSplitViewItemBehaviorDefault,
    NSSplitViewItemBehaviorSidebar,
    NSSplitViewItemBehaviorContentList
} NS_AVAILABLE_MAC(10_11);

typedef NS_ENUM(NSInteger, NSSplitViewItemCollapseBehavior) {
    /// The item uses the default collapsing behavior for its set `behavior`. The default may change over time.
    NSSplitViewItemCollapseBehaviorDefault,
    /// The item prefers to keep the other panes at their current size and position on screen, potentially growing or shrinking the window in the direction to best preserve that. But it will break that preference in order to keep the window fully on screen or when in full screen.
    NSSplitViewItemCollapseBehaviorPreferResizingSplitViewWithFixedSiblings,
    /// The item prefers to resize the other split panes. This will be broken when uncollapsing if the item can't fully uncollapse before hitting the minimum size of the other panes or the window.
    NSSplitViewItemCollapseBehaviorPreferResizingSiblingsWithFixedSplitView,
    /// The item will collapse/uncollapse purely from a constraint animation, with a constraint priority of the item’s `holdingPriority`. This could result in a partial internal content resize and window resize, and has no implications for keeping the window on screen. External constraints can be used to tweak exactly how the animation affects item, sibling, and window size and positions.
    NSSplitViewItemCollapseBehaviorUseConstraints
} NS_AVAILABLE_MAC(10_11);


/// This constant can be used with any sizing related \c NSSplitViewItem properties to unset their values.
APPKIT_EXTERN const CGFloat NSSplitViewItemUnspecifiedDimension NS_AVAILABLE_MAC(10_11);

/*!
 * NSSplitViewItem implements the items used in an NSSplitViewController.
 * The item describes a child ViewController's state in a SplitViewController, e.g. its collapsibility, holding priority and other metrics, and collapsed state.
 */
NS_CLASS_AVAILABLE_MAC(10_10)
@interface NSSplitViewItem : NSObject <NSAnimatablePropertyContainer, NSCoding> {
@private
    id _splitViewItemPrivateData;
    struct {
        unsigned int _collapsed:1;
        unsigned int _canCollapse:1;
        unsigned int _isOverlaid:1;
        unsigned int _revealsOnEdgeHoverInFullscreen:1;
        unsigned int _springLoaded:1;
        unsigned int _reserved:27;
    } _flags;
}

/*!
 * Creates an autoreleased SplitViewItem that represents the provided ViewController. All other properties are left at their default.
 * \param viewController The view controller used to set the viewController property
 * \return An autoreleased SplitViewItem.
 */
+ (instancetype)splitViewItemWithViewController:(NSViewController *)viewController;

/*!
 * Creates a split view item representing a sidebar for the provided ViewController.
 * Sidebars have standard system behavior, specifically:
 *  - Translucent material background
 *  - The ability to collapse/uncollapse on split view size changes
 *  - The ability to overlay at small split view sizes when in fullscreen
 *  - canCollapse is set to YES
 *  - minimumThickness and maximumThickness are set to the standard minimum and maximum sidebar size
 *  - preferredThicknessFraction is set to the standard fraction for sidebars (0.15)
 *  - springLoaded is set to YES
 * \param viewController The view controller used to set the viewController property
 * \return An autoreleased SplitViewItem that acts as a sidebar.
 */
+ (instancetype)sidebarWithViewController:(NSViewController *)viewController NS_SWIFT_NAME(init(sidebarWithViewController:)) NS_AVAILABLE_MAC(10_11);

/*!
 * Creates a split view item representing a content list for the provided ViewController, akin to Mail's message list, Note's note list.
 * Content lists have system standard defaults, specifically:
 *  - minimumThickness and maximumThickness are set to the system standard for content lists
 *  - automaticMaximumThickness is set to the system standard for content lists
 *  - preferredThicknessFraction is set to the standard fraction for content lists (0.28 when a neighbor sidebar is visible, 0.33 if not)
 * \param viewController The view controller used to set the viewController property
 * \return An autoreleased SplitViewItem that acts as a content list.
 */
+ (instancetype)contentListWithViewController:(NSViewController *)viewController NS_SWIFT_NAME(init(contentListWithViewController:)) NS_AVAILABLE_MAC(10_11);

/// The standard behavior type of the receiver. See initializers for descriptions of each behavior.
@property (readonly) NSSplitViewItemBehavior behavior NS_AVAILABLE_MAC(10_11);

/// The view controller represented by the SplitViewItem. An exception will be thrown if a new viewController is set while the receiving SplitViewItem is added to a SplitViewController.
@property (strong) NSViewController *viewController;

/// Whether or not the child ViewController corresponding to the SplitViewItem is collapsed in the SplitViewController. The default is \c NO. This can be set with the animator proxy to animate the collapse or uncollapse. The exact animation used can be customized by setting it in the -animations dictionary with a key of "collapsed". If this is set to YES before it is added to the SplitViewController, it will be initially collapsed and the SplitViewController will not cause the view to be loaded until it is uncollapsed. This is KVC/KVO compliant and will be updated if the value changes from user interaction.
@property (getter=isCollapsed) BOOL collapsed;

/// Whether or not the child view controller is collapsible from user interaction - whether by dragging or double clicking a divider. The default is \c NO.
@property BOOL canCollapse;

/// The resize behavior when the receiver toggles its `collapsed` state programmatically, both animatedly and not. Defaults to `.Default`.
@property NSSplitViewItemCollapseBehavior collapseBehavior NS_AVAILABLE_MAC(10_11);

/// A convenience to set the minimum thickness of the split view item -- width for "vertical" split views, height otherwise. If NSSplitViewItemUnspecifiedDimension, no minimum size is enforced by the SplitViewItem, although constraints in the contained view hierarchy might have constraints specify some minimum size on their own. Defaults to NSSplitViewItemUnspecifiedDimension.
@property CGFloat minimumThickness NS_AVAILABLE_MAC(10_11);

/// A convenience to set the maximum thickness of the split view item -- width for "vertical" split views, height otherwise. If NSSplitViewItemUnspecifiedDimension, no maximum size is enforced by the SplitViewItem, although constraints in the contained view hierarchy might have constraints specify some maximum size on their own. Defaults to NSSplitViewItemUnspecifiedDimension.
@property CGFloat maximumThickness NS_AVAILABLE_MAC(10_11);

/// The percentage of the contained NSSplitView that the NSSplitViewItem prefers to encompass. This is used when double-clicking on a neighbor divider to return to that standard ratio. As well as after entering fullscreen to determine the initial size of the receiver. Defaults to NSSplitViewItemUnspecifiedDimension, which means no resize will occur on double-clicks, and the absolute size is preserved when entering fullscreen.
@property CGFloat preferredThicknessFraction NS_AVAILABLE_MAC(10_11);

/// Sets the priority under which a SplitViewItem will hold its width (for a vertical split view) or height (for a horizontal split view). The view with the lowest priority will be the first to take on additional width if the split view grows or shrinks. The default is \c NSLayoutPriorityDefaultLow.
@property NSLayoutPriority holdingPriority;

/// The maximum thickness of the split view item when resizing due to automatic sizing, such as entering fullscreen with a set preferredThicknessFraction or proportional sizing. The user can still resize up to the absolute maximum size by dragging the divider or otherwise. If NSSplitViewItemUnspecifiedDimension, no automatic maximum is enforced. Defaults to NSSplitViewItemUnspecifiedDimension.
@property CGFloat automaticMaximumThickness NS_AVAILABLE_MAC(10_11);

/// If YES, the split view item can be temporarily uncollapsed during a drag by hovering or deep clicking on its neighboring divider. Defaults to NO.
@property (getter=isSpringLoaded) BOOL springLoaded NS_AVAILABLE_MAC(10_11);

@end

NS_ASSUME_NONNULL_END
