#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITableView.h>)
//
//  UITableView.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/NSIndexPath+UIKitAdditions.h>
#import <UIKit/UIScrollView.h>
#import <UIKit/UISwipeGestureRecognizer.h>
#import <UIKit/UISwipeActionsConfiguration.h>
#import <UIKit/UITableViewCell.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIDataSourceTranslating.h>
#import <UIKit/UISpringLoadedInteractionSupporting.h>
#import <UIKit/UIDropInteraction.h>
#import <UIKit/UIContextMenuInteraction.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UITableViewStyle) {
    UITableViewStylePlain,          // regular table view
    UITableViewStyleGrouped,        // sections are grouped together
    UITableViewStyleInsetGrouped  API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos)  // grouped sections are inset with rounded corners
};

typedef NS_ENUM(NSInteger, UITableViewScrollPosition) {
    UITableViewScrollPositionNone,
    UITableViewScrollPositionTop,    
    UITableViewScrollPositionMiddle,   
    UITableViewScrollPositionBottom
};                // scroll so row of interest is completely visible at top/center/bottom of view

typedef NS_ENUM(NSInteger, UITableViewRowAnimation) {
    UITableViewRowAnimationFade,
    UITableViewRowAnimationRight,           // slide in from right (or out to right)
    UITableViewRowAnimationLeft,
    UITableViewRowAnimationTop,
    UITableViewRowAnimationBottom,
    UITableViewRowAnimationNone,            // available in iOS 3.0
    UITableViewRowAnimationMiddle,          // available in iOS 3.2.  attempts to keep cell centered in the space it will/did occupy
    UITableViewRowAnimationAutomatic = 100  // available in iOS 5.0.  chooses an appropriate animation style for you
};

// Including this constant string in the array of strings returned by sectionIndexTitlesForTableView: will cause a magnifying glass icon to be displayed at that location in the index.
// This should generally only be used as the first title in the index.
UIKIT_EXTERN NSString *const UITableViewIndexSearch API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(tvos);

// Returning this value from tableView:heightForHeaderInSection: or tableView:heightForFooterInSection: results in a height that fits the value returned from
// tableView:titleForHeaderInSection: or tableView:titleForFooterInSection: if the title is not nil.
UIKIT_EXTERN const CGFloat UITableViewAutomaticDimension API_AVAILABLE(ios(5.0));

@class UITableView, UINib, UITableViewHeaderFooterView, UIVisualEffect;
@protocol UITableViewDataSource, UITableViewDataSourcePrefetching;
@class UIDragItem, UIDragPreviewParameters, UIDragPreviewTarget, UITableViewDropProposal, UITableViewPlaceholder, UITableViewDropPlaceholder;
@protocol UISpringLoadedInteractionContext, UIDragSession, UIDropSession;
@protocol UITableViewDragDelegate, UITableViewDropDelegate, UITableViewDropCoordinator, UITableViewDropItem, UITableViewDropPlaceholderContext;

typedef NS_ENUM(NSInteger, UITableViewRowActionStyle) {
    UITableViewRowActionStyleDefault = 0,
    UITableViewRowActionStyleDestructive = UITableViewRowActionStyleDefault,
    UITableViewRowActionStyleNormal
} API_DEPRECATED("Use UIContextualAction and related APIs instead.", ios(8.0, 13.0)) API_UNAVAILABLE(tvos);

UIKIT_EXTERN API_DEPRECATED("Use UIContextualAction and related APIs instead.", ios(8.0, 13.0)) API_UNAVAILABLE(tvos)
@interface UITableViewRowAction : NSObject <NSCopying>

+ (instancetype)rowActionWithStyle:(UITableViewRowActionStyle)style title:(nullable NSString *)title handler:(void (^)(UITableViewRowAction *action, NSIndexPath *indexPath))handler;

@property (nonatomic, readonly) UITableViewRowActionStyle style;
@property (nonatomic, copy, nullable) NSString *title;
@property (nonatomic, copy, nullable) UIColor *backgroundColor; // default background color is dependent on style
@property (nonatomic, copy, nullable) UIVisualEffect* backgroundEffect;

@end

UIKIT_EXTERN API_AVAILABLE(ios(9.0)) @interface UITableViewFocusUpdateContext : UIFocusUpdateContext

@property (nonatomic, strong, readonly, nullable) NSIndexPath *previouslyFocusedIndexPath;
@property (nonatomic, strong, readonly, nullable) NSIndexPath *nextFocusedIndexPath;

@end

//_______________________________________________________________________________________________________________
// this represents the display and behavior of the cells.

@protocol UITableViewDelegate<NSObject, UIScrollViewDelegate>

@optional

// Display customization

- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath;
- (void)tableView:(UITableView *)tableView willDisplayHeaderView:(UIView *)view forSection:(NSInteger)section API_AVAILABLE(ios(6.0));
- (void)tableView:(UITableView *)tableView willDisplayFooterView:(UIView *)view forSection:(NSInteger)section API_AVAILABLE(ios(6.0));
- (void)tableView:(UITableView *)tableView didEndDisplayingCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath*)indexPath API_AVAILABLE(ios(6.0));
- (void)tableView:(UITableView *)tableView didEndDisplayingHeaderView:(UIView *)view forSection:(NSInteger)section API_AVAILABLE(ios(6.0));
- (void)tableView:(UITableView *)tableView didEndDisplayingFooterView:(UIView *)view forSection:(NSInteger)section API_AVAILABLE(ios(6.0));

// Variable height support

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath;
- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section;
- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section;

// Use the estimatedHeight methods to quickly calculate guessed values which will allow for fast load times of the table.
// If these methods are implemented, the above -tableView:heightForXXX calls will be deferred until views are ready to be displayed, so more expensive logic can be placed there.
- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForRowAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(7.0));
- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForHeaderInSection:(NSInteger)section API_AVAILABLE(ios(7.0));
- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForFooterInSection:(NSInteger)section API_AVAILABLE(ios(7.0));

// Section header & footer information. Views are preferred over title should you decide to provide both

- (nullable UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section;   // custom view for header. will be adjusted to default or specified header height
- (nullable UIView *)tableView:(UITableView *)tableView viewForFooterInSection:(NSInteger)section;   // custom view for footer. will be adjusted to default or specified footer height

// Accessories (disclosures). 

- (UITableViewCellAccessoryType)tableView:(UITableView *)tableView accessoryTypeForRowWithIndexPath:(NSIndexPath *)indexPath API_DEPRECATED("", ios(2.0, 3.0)) API_UNAVAILABLE(tvos);
- (void)tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath:(NSIndexPath *)indexPath;

// Selection

// -tableView:shouldHighlightRowAtIndexPath: is called when a touch comes down on a row. 
// Returning NO to that message halts the selection process and does not cause the currently selected row to lose its selected look while the touch is down.
- (BOOL)tableView:(UITableView *)tableView shouldHighlightRowAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(6.0));
- (void)tableView:(UITableView *)tableView didHighlightRowAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(6.0));
- (void)tableView:(UITableView *)tableView didUnhighlightRowAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(6.0));

// Called before the user changes the selection. Return a new indexPath, or nil, to change the proposed selection.
- (nullable NSIndexPath *)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath;
- (nullable NSIndexPath *)tableView:(UITableView *)tableView willDeselectRowAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(3.0));
// Called after the user changes the selection.
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath;
- (void)tableView:(UITableView *)tableView didDeselectRowAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(3.0));

// Editing

// Allows customization of the editingStyle for a particular cell located at 'indexPath'. If not implemented, all editable cells will have UITableViewCellEditingStyleDelete set for them when the table has editing property set to YES.
- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath;
- (nullable NSString *)tableView:(UITableView *)tableView titleForDeleteConfirmationButtonForRowAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(tvos);

// This method supersedes -tableView:titleForDeleteConfirmationButtonForRowAtIndexPath: if return value is non-nil
- (nullable NSArray<UITableViewRowAction *> *)tableView:(UITableView *)tableView editActionsForRowAtIndexPath:(NSIndexPath *)indexPath API_DEPRECATED_WITH_REPLACEMENT("tableView:trailingSwipeActionsConfigurationForRowAtIndexPath:", ios(8.0, 13.0)) API_UNAVAILABLE(tvos);

// Swipe actions
// These methods supersede -editActionsForRowAtIndexPath: if implemented
// return nil to get the default swipe actions
- (nullable UISwipeActionsConfiguration *)tableView:(UITableView *)tableView leadingSwipeActionsConfigurationForRowAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos);
- (nullable UISwipeActionsConfiguration *)tableView:(UITableView *)tableView trailingSwipeActionsConfigurationForRowAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos);

// Controls whether the background is indented while editing.  If not implemented, the default is YES.  This is unrelated to the indentation level below.  This method only applies to grouped style table views.
- (BOOL)tableView:(UITableView *)tableView shouldIndentWhileEditingRowAtIndexPath:(NSIndexPath *)indexPath;

// The willBegin/didEnd methods are called whenever the 'editing' property is automatically changed by the table (allowing insert/delete/move). This is done by a swipe activating a single row
- (void)tableView:(UITableView *)tableView willBeginEditingRowAtIndexPath:(NSIndexPath *)indexPath API_UNAVAILABLE(tvos);
- (void)tableView:(UITableView *)tableView didEndEditingRowAtIndexPath:(nullable NSIndexPath *)indexPath API_UNAVAILABLE(tvos);

// Moving/reordering

// Allows customization of the target row for a particular row as it is being moved/reordered
- (NSIndexPath *)tableView:(UITableView *)tableView targetIndexPathForMoveFromRowAtIndexPath:(NSIndexPath *)sourceIndexPath toProposedIndexPath:(NSIndexPath *)proposedDestinationIndexPath;               

// Indentation

- (NSInteger)tableView:(UITableView *)tableView indentationLevelForRowAtIndexPath:(NSIndexPath *)indexPath; // return 'depth' of row for hierarchies

// Copy/Paste.  All three methods must be implemented by the delegate.

- (BOOL)tableView:(UITableView *)tableView shouldShowMenuForRowAtIndexPath:(NSIndexPath *)indexPath API_DEPRECATED_WITH_REPLACEMENT("tableView:contextMenuConfigurationForRowAtIndexPath:point:", ios(5.0, 13.0));
- (BOOL)tableView:(UITableView *)tableView canPerformAction:(SEL)action forRowAtIndexPath:(NSIndexPath *)indexPath withSender:(nullable id)sender API_DEPRECATED_WITH_REPLACEMENT("tableView:contextMenuConfigurationForRowAtIndexPath:point:", ios(5.0, 13.0));
- (void)tableView:(UITableView *)tableView performAction:(SEL)action forRowAtIndexPath:(NSIndexPath *)indexPath withSender:(nullable id)sender API_DEPRECATED_WITH_REPLACEMENT("tableView:contextMenuConfigurationForRowAtIndexPath:", ios(5.0, 13.0));

// Focus

- (BOOL)tableView:(UITableView *)tableView canFocusRowAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(9.0));
- (BOOL)tableView:(UITableView *)tableView shouldUpdateFocusInContext:(UITableViewFocusUpdateContext *)context API_AVAILABLE(ios(9.0));
- (void)tableView:(UITableView *)tableView didUpdateFocusInContext:(UITableViewFocusUpdateContext *)context withAnimationCoordinator:(UIFocusAnimationCoordinator *)coordinator API_AVAILABLE(ios(9.0));
- (nullable NSIndexPath *)indexPathForPreferredFocusedViewInTableView:(UITableView *)tableView API_AVAILABLE(ios(9.0));

// Spring Loading

// Allows opting-out of spring loading for an particular row.
// If you want the interaction effect on a different subview of the spring loaded cell, modify the context.targetView property. The default is the cell.
// If this method is not implemented, the default is YES except when the row is part of a drag session.
- (BOOL)tableView:(UITableView *)tableView shouldSpringLoadRowAtIndexPath:(NSIndexPath *)indexPath withContext:(id<UISpringLoadedInteractionContext>)context API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

// Multiple Selection

/* Allows a two-finger pan gesture to automatically transition the table view into editing mode and start selecting cells.
 *
 * If this method returns YES, allow the user to start selecting multiple contiguous cells via a two-finger pan gesture. If
 * the table view is already in editing mode, the user can also select multiple cells via a one-finger pan gesture along the
 * edge of the table that contains editing controls (checkboxes).
 *
 * In order to support this behavior, you must also set allowsMultipleSelectionDuringEditing to YES.
 *
 * If this method is not implemented, the default is NO.
 */
- (BOOL)tableView:(UITableView *)tableView shouldBeginMultipleSelectionInteractionAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);

/* Called right after the multi-select pan gesture begins and the table view is automatically transitioned into editing mode.
 *
 * In your app, this would be a good opportunity to update the state of your UI to reflect the fact that the user is now selecting
 * multiple items at once; such as updating buttons to say "Done" instead of "Select"/"Edit", for instance.
 */
- (void)tableView:(UITableView *)tableView didBeginMultipleSelectionInteractionAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);

/* Called when the multi-select interaction ends.
 *
 * At this point, the table view will remain in multi-select mode, but this delegate method is called to indicate that the multiple
 * selection gesture or hardware keyboard interaction has ended.
 */
- (void)tableViewDidEndMultipleSelectionInteraction:(UITableView *)tableView API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);

/*!
 * @abstract Called when the interaction begins.
 *
 * @param tableView  This UITableView.
 * @param indexPath  IndexPath of the row for which a configuration is being requested.
 * @param point      Location of the interaction in the table view's coordinate space
 *
 * @return A UIContextMenuConfiguration describing the menu to be presented. Return nil to prevent the interaction from beginning.
 *         Returning an empty configuration causes the interaction to begin then fail with a cancellation effect. You might use this
 *         to indicate to users that it's possible for a menu to be presented from this element, but that there are no actions to
 *         present at this particular time.
 */
- (nullable UIContextMenuConfiguration *)tableView:(UITableView *)tableView contextMenuConfigurationForRowAtIndexPath:(NSIndexPath *)indexPath point:(CGPoint)point API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @abstract Called when the interaction begins. Return a UITargetedPreview to override the default preview created by the table view.
 *
 * @param tableView      This UITableView.
 * @param configuration  The configuration of the menu about to be displayed by this interaction.
 */
- (nullable UITargetedPreview *)tableView:(UITableView *)tableView previewForHighlightingContextMenuWithConfiguration:(UIContextMenuConfiguration *)configuration API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @abstract Called when the interaction is about to dismiss. Return a UITargetedPreview describing the desired dismissal target.
 * The interaction will animate the presented menu to the target. Use this to customize the dismissal animation.
 *
 * @param tableView      This UITableView.
 * @param configuration  The configuration of the menu displayed by this interaction.
 */
- (nullable UITargetedPreview *)tableView:(UITableView *)tableView previewForDismissingContextMenuWithConfiguration:(UIContextMenuConfiguration *)configuration API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @abstract Called when the interaction is about to "commit" in response to the user tapping the preview.
 *
 * @param tableView      This UITableView.
 * @param configuration  Configuration of the currently displayed menu.
 * @param animator       Commit animator. Add animations to this object to run them alongside the commit transition.
 */
- (void)tableView:(UITableView *)tableView willPerformPreviewActionForMenuWithConfiguration:(UIContextMenuConfiguration *)configuration animator:(id<UIContextMenuInteractionCommitAnimating>)animator API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @abstract Called when the table view is about to display a menu.
 *
 * @param tableView       This UITableView.
 * @param configuration   The configuration of the menu about to be displayed.
 * @param animator        Appearance animator. Add animations to run them alongside the appearance transition.
 */
- (void)tableView:(UITableView *)tableView willDisplayContextMenuWithConfiguration:(UIContextMenuConfiguration *)configuration animator:(nullable id<UIContextMenuInteractionAnimating>)animator API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @abstract Called when the table view's context menu interaction is about to end.
 *
 * @param tableView       This UITableView.
 * @param configuration   Ending configuration.
 * @param animator        Disappearance animator. Add animations to run them alongside the disappearance transition.
 */
- (void)tableView:(UITableView *)tableView willEndContextMenuInteractionWithConfiguration:(UIContextMenuConfiguration *)configuration animator:(nullable id<UIContextMenuInteractionAnimating>)animator API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos);

@end

UIKIT_EXTERN NSNotificationName const UITableViewSelectionDidChangeNotification;

typedef NS_ENUM(NSInteger, UITableViewSeparatorInsetReference) {
    // The value set to the separatorInset property is interpreted as an offset from the edges of the cell.
    UITableViewSeparatorInsetFromCellEdges,
    
    // The value set to the separatorInset property is interpreted as an offset from the automatic separator insets.
    UITableViewSeparatorInsetFromAutomaticInsets
} API_AVAILABLE(ios(11.0), tvos(11.0));


//_______________________________________________________________________________________________________________

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) @interface UITableView : UIScrollView <NSCoding, UIDataSourceTranslating>

- (instancetype)initWithFrame:(CGRect)frame style:(UITableViewStyle)style NS_DESIGNATED_INITIALIZER; // must specify style at creation. -initWithFrame: calls this with UITableViewStylePlain
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly) UITableViewStyle style;

@property (nonatomic, weak, nullable) id <UITableViewDataSource> dataSource;
@property (nonatomic, weak, nullable) id <UITableViewDelegate> delegate;
@property (nonatomic, weak, nullable) id <UITableViewDataSourcePrefetching> prefetchDataSource API_AVAILABLE(ios(10.0));
@property (nonatomic, weak, nullable) id <UITableViewDragDelegate> dragDelegate API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);
@property (nonatomic, weak, nullable) id <UITableViewDropDelegate> dropDelegate API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

@property (nonatomic) CGFloat rowHeight;             // default is UITableViewAutomaticDimension
@property (nonatomic) CGFloat sectionHeaderHeight;   // default is UITableViewAutomaticDimension
@property (nonatomic) CGFloat sectionFooterHeight;   // default is UITableViewAutomaticDimension
@property (nonatomic) CGFloat estimatedRowHeight API_AVAILABLE(ios(7.0)); // default is UITableViewAutomaticDimension, set to 0 to disable
@property (nonatomic) CGFloat estimatedSectionHeaderHeight API_AVAILABLE(ios(7.0)); // default is UITableViewAutomaticDimension, set to 0 to disable
@property (nonatomic) CGFloat estimatedSectionFooterHeight API_AVAILABLE(ios(7.0)); // default is UITableViewAutomaticDimension, set to 0 to disable

@property (nonatomic) UIEdgeInsets separatorInset API_AVAILABLE(ios(7.0)) UI_APPEARANCE_SELECTOR; // allows customization of the frame of cell separators; see also the separatorInsetReference property. Use UITableViewAutomaticDimension for the automatic inset for that edge.
@property (nonatomic) UITableViewSeparatorInsetReference separatorInsetReference API_AVAILABLE(ios(11.0), tvos(11.0)); // Changes how custom separatorInset values are interpreted. The default value is UITableViewSeparatorInsetFromCellEdges

@property (nonatomic, strong, nullable) UIView *backgroundView API_AVAILABLE(ios(3.2)); // the background view will be automatically resized to track the size of the table view.  this will be placed as a subview of the table view behind all cells and headers/footers.  default may be non-nil for some devices.

@property (nonatomic, readonly, nullable) UIContextMenuInteraction *contextMenuInteraction API_UNAVAILABLE(ios) API_UNAVAILABLE(watchos, tvos);

// Info

@property (nonatomic, readonly) NSInteger numberOfSections;
- (NSInteger)numberOfRowsInSection:(NSInteger)section;

- (CGRect)rectForSection:(NSInteger)section;                                    // includes header, footer and all rows
- (CGRect)rectForHeaderInSection:(NSInteger)section;
- (CGRect)rectForFooterInSection:(NSInteger)section;
- (CGRect)rectForRowAtIndexPath:(NSIndexPath *)indexPath;

- (nullable NSIndexPath *)indexPathForRowAtPoint:(CGPoint)point;                         // returns nil if point is outside of any row in the table
- (nullable NSIndexPath *)indexPathForCell:(UITableViewCell *)cell;                      // returns nil if cell is not visible
- (nullable NSArray<NSIndexPath *> *)indexPathsForRowsInRect:(CGRect)rect;                              // returns nil if rect not valid

- (nullable __kindof UITableViewCell *)cellForRowAtIndexPath:(NSIndexPath *)indexPath;   // returns nil if cell is not visible or index path is out of range
@property (nonatomic, readonly) NSArray<__kindof UITableViewCell *> *visibleCells;
@property (nonatomic, readonly, nullable) NSArray<NSIndexPath *> *indexPathsForVisibleRows;

- (nullable UITableViewHeaderFooterView *)headerViewForSection:(NSInteger)section API_AVAILABLE(ios(6.0));
- (nullable UITableViewHeaderFooterView *)footerViewForSection:(NSInteger)section API_AVAILABLE(ios(6.0));

- (void)scrollToRowAtIndexPath:(NSIndexPath *)indexPath atScrollPosition:(UITableViewScrollPosition)scrollPosition animated:(BOOL)animated;
- (void)scrollToNearestSelectedRowAtScrollPosition:(UITableViewScrollPosition)scrollPosition animated:(BOOL)animated;

// Reloading and Updating

// Allows multiple insert/delete/reload/move calls to be animated simultaneously. Nestable.
- (void)performBatchUpdates:(void (NS_NOESCAPE ^ _Nullable)(void))updates completion:(void (^ _Nullable)(BOOL finished))completion API_AVAILABLE(ios(11.0), tvos(11.0));

// Use -performBatchUpdates:completion: instead of these methods, which will be deprecated in a future release.
- (void)beginUpdates;
- (void)endUpdates;

- (void)insertSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation;
- (void)deleteSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation;
- (void)reloadSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation API_AVAILABLE(ios(3.0));
- (void)moveSection:(NSInteger)section toSection:(NSInteger)newSection API_AVAILABLE(ios(5.0));

- (void)insertRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation;
- (void)deleteRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation;
- (void)reloadRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation API_AVAILABLE(ios(3.0));
- (void)moveRowAtIndexPath:(NSIndexPath *)indexPath toIndexPath:(NSIndexPath *)newIndexPath API_AVAILABLE(ios(5.0));

// Returns YES if the table view is in the middle of reordering, is displaying a drop target gap, or has drop placeholders. If possible, avoid calling -reloadData while there are uncommitted updates to avoid interfering with user-initiated interactions that have not yet completed.
@property (nonatomic, readonly) BOOL hasUncommittedUpdates API_AVAILABLE(ios(11.0), tvos(11.0));

// Reloads everything from scratch. Redisplays visible rows. Note that this will cause any existing drop placeholder rows to be removed.
- (void)reloadData;

// Reloads the section index bar.
- (void)reloadSectionIndexTitles API_AVAILABLE(ios(3.0));

// Editing. When set, rows show insert/delete/reorder controls based on data source queries

@property (nonatomic, getter=isEditing) BOOL editing;                             // default is NO. setting is not animated.
- (void)setEditing:(BOOL)editing animated:(BOOL)animated;

@property (nonatomic) BOOL allowsSelection API_AVAILABLE(ios(3.0));  // default is YES. Controls whether rows can be selected when not in editing mode
@property (nonatomic) BOOL allowsSelectionDuringEditing;                                 // default is NO. Controls whether rows can be selected when in editing mode
@property (nonatomic) BOOL allowsMultipleSelection API_AVAILABLE(ios(5.0));                // default is NO. Controls whether multiple rows can be selected simultaneously
@property (nonatomic) BOOL allowsMultipleSelectionDuringEditing API_AVAILABLE(ios(5.0));   // default is NO. Controls whether multiple rows can be selected simultaneously in editing mode

// Selection

@property (nonatomic, readonly, nullable) NSIndexPath *indexPathForSelectedRow; // returns nil or index path representing section and row of selection.
@property (nonatomic, readonly, nullable) NSArray<NSIndexPath *> *indexPathsForSelectedRows API_AVAILABLE(ios(5.0)); // returns nil or a set of index paths representing the sections and rows of the selection.

// Selects and deselects rows. These methods will not call the delegate methods (-tableView:willSelectRowAtIndexPath: or tableView:didSelectRowAtIndexPath:), nor will it send out a notification.
- (void)selectRowAtIndexPath:(nullable NSIndexPath *)indexPath animated:(BOOL)animated scrollPosition:(UITableViewScrollPosition)scrollPosition;
- (void)deselectRowAtIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated;

// Appearance

@property (nonatomic) NSInteger sectionIndexMinimumDisplayRowCount;                                                      // show special section index list on right when row count reaches this value. default is 0
@property (nonatomic, strong, nullable) UIColor *sectionIndexColor API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;                   // color used for text of the section index
@property (nonatomic, strong, nullable) UIColor *sectionIndexBackgroundColor API_AVAILABLE(ios(7.0)) UI_APPEARANCE_SELECTOR;         // the background color of the section index while not being touched
@property (nonatomic, strong, nullable) UIColor *sectionIndexTrackingBackgroundColor API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR; // the background color of the section index while it is being touched

@property (nonatomic) UITableViewCellSeparatorStyle separatorStyle API_UNAVAILABLE(tvos); // default is UITableViewCellSeparatorStyleSingleLine
@property (nonatomic, strong, nullable) UIColor *separatorColor UI_APPEARANCE_SELECTOR API_UNAVAILABLE(tvos); // default is the standard separator gray
@property (nonatomic, copy, nullable) UIVisualEffect *separatorEffect API_AVAILABLE(ios(8.0)) UI_APPEARANCE_SELECTOR API_UNAVAILABLE(tvos); // effect to apply to table separators

@property (nonatomic) BOOL cellLayoutMarginsFollowReadableWidth API_AVAILABLE(ios(9.0)); // if cell layout margins are derived from the width of the readableContentGuide. default is NO.
@property (nonatomic) BOOL insetsContentViewsToSafeArea API_AVAILABLE(ios(11.0), tvos(11.0)); // default value is YES

@property (nonatomic, strong, nullable) UIView *tableHeaderView;                           // accessory view for above row content. default is nil. not to be confused with section header
@property (nonatomic, strong, nullable) UIView *tableFooterView;                           // accessory view below content. default is nil. not to be confused with section footer

- (nullable __kindof UITableViewCell *)dequeueReusableCellWithIdentifier:(NSString *)identifier;  // Used by the delegate to acquire an already allocated cell, in lieu of allocating a new one.
- (__kindof UITableViewCell *)dequeueReusableCellWithIdentifier:(NSString *)identifier forIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(6.0)); // newer dequeue method guarantees a cell is returned and resized properly, assuming identifier is registered
- (nullable __kindof UITableViewHeaderFooterView *)dequeueReusableHeaderFooterViewWithIdentifier:(NSString *)identifier API_AVAILABLE(ios(6.0));  // like dequeueReusableCellWithIdentifier:, but for headers/footers

// Beginning in iOS 6, clients can register a nib or class for each cell.
// If all reuse identifiers are registered, use the newer -dequeueReusableCellWithIdentifier:forIndexPath: to guarantee that a cell instance is returned.
// Instances returned from the new dequeue method will also be properly sized when they are returned.
- (void)registerNib:(nullable UINib *)nib forCellReuseIdentifier:(NSString *)identifier API_AVAILABLE(ios(5.0));
- (void)registerClass:(nullable Class)cellClass forCellReuseIdentifier:(NSString *)identifier API_AVAILABLE(ios(6.0));

- (void)registerNib:(nullable UINib *)nib forHeaderFooterViewReuseIdentifier:(NSString *)identifier API_AVAILABLE(ios(6.0));
- (void)registerClass:(nullable Class)aClass forHeaderFooterViewReuseIdentifier:(NSString *)identifier API_AVAILABLE(ios(6.0));

// Focus

@property (nonatomic) BOOL remembersLastFocusedIndexPath API_AVAILABLE(ios(9.0)); // defaults to NO. If YES, when focusing on a table view the last focused index path is focused automatically. If the table view has never been focused, then the preferred focused index path is used.

// When enabled, the table view ensures that selection is automatically triggered when focus moves to a cell.
@property (nonatomic) BOOL selectionFollowsFocus API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos);

// Drag & Drop

// To enable intra-app drags on iPhone, set this to YES.
// You can also force drags to be disabled for this table view by setting this to NO.
// By default, this will return YES on iPad and NO on iPhone.
@property (nonatomic) BOOL dragInteractionEnabled API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

// YES if a drag session is currently active. A drag session begins after rows are "lifted" from the table view.
@property (nonatomic, readonly) BOOL hasActiveDrag API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

// YES if table view is currently tracking a drop session.
@property (nonatomic, readonly) BOOL hasActiveDrop API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

@end

#if TARGET_OS_IOS
@interface UITableView (UIDragAndDrop) <UISpringLoadedInteractionSupporting>
@end
#endif

//_______________________________________________________________________________________________________________
// this protocol represents the data model object. as such, it supplies no information about appearance (including the cells)

@protocol UITableViewDataSource<NSObject>

@required

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section;

// Row display. Implementers should *always* try to reuse cells by setting each cell's reuseIdentifier and querying for available reusable cells with dequeueReusableCellWithIdentifier:
// Cell gets various attributes set automatically based on table (separators) and data source (accessory views, editing controls)

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;

@optional

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView;              // Default is 1 if not implemented

- (nullable NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section;    // fixed font style. use custom view (UILabel) if you want something different
- (nullable NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section;

// Editing

// Individual rows can opt out of having the -editing property set for them. If not implemented, all rows are assumed to be editable.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath;

// Moving/reordering

// Allows the reorder accessory view to optionally be shown for a particular row. By default, the reorder control will be shown only if the datasource implements -tableView:moveRowAtIndexPath:toIndexPath:
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath;

// Index

- (nullable NSArray<NSString *> *)sectionIndexTitlesForTableView:(UITableView *)tableView;                               // return list of section titles to display in section index view (e.g. "ABCD...Z#")
- (NSInteger)tableView:(UITableView *)tableView sectionForSectionIndexTitle:(NSString *)title atIndex:(NSInteger)index;  // tell table which section corresponds to section title/index (e.g. "B",1))

// Data manipulation - insert and delete support

// After a row has the minus or plus button invoked (based on the UITableViewCellEditingStyle for the cell), the dataSource must commit the change
// Not called for edit actions using UITableViewRowAction - the action's handler will be invoked instead
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath;

// Data manipulation - reorder / moving support

- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)sourceIndexPath toIndexPath:(NSIndexPath *)destinationIndexPath;

@end


// _______________________________________________________________________________________________________________
// this protocol can provide information about cells before they are displayed on screen.

@protocol UITableViewDataSourcePrefetching <NSObject>

@required

// indexPaths are ordered ascending by geometric distance from the table view
- (void)tableView:(UITableView *)tableView prefetchRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;

@optional

// indexPaths that previously were considered as candidates for pre-fetching, but were not actually used; may be a subset of the previous call to -tableView:prefetchRowsAtIndexPaths:
- (void)tableView:(UITableView *)tableView cancelPrefetchingForRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;

@end


// _______________________________________________________________________________________________________________
// Drag & Drop

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@protocol UITableViewDragDelegate <NSObject>

@required

// Provide items to begin a drag associated with a given index path.
// You can use -[session locationInView:] to do additional hit testing if desired.
// If an empty array is returned a drag session will not begin.
- (NSArray<UIDragItem *> *)tableView:(UITableView *)tableView itemsForBeginningDragSession:(id<UIDragSession>)session atIndexPath:(NSIndexPath *)indexPath;

@optional

// Called to request items to add to an existing drag session in response to the add item gesture.
// You can use the provided point (in the table view's coordinate space) to do additional hit testing if desired.
// If not implemented, or if an empty array is returned, no items will be added to the drag and the gesture
// will be handled normally.
- (NSArray<UIDragItem *> *)tableView:(UITableView *)tableView itemsForAddingToDragSession:(id<UIDragSession>)session atIndexPath:(NSIndexPath *)indexPath point:(CGPoint)point;

// Allows customization of the preview used for the row when it is lifted or if the drag cancels.
// If not implemented or if nil is returned, the entire cell will be used for the preview.
- (nullable UIDragPreviewParameters *)tableView:(UITableView *)tableView dragPreviewParametersForRowAtIndexPath:(NSIndexPath *)indexPath;

// Called after the lift animation has completed to signal the start of a drag session.
// This call will always be balanced with a corresponding call to -tableView:dragSessionDidEnd:
- (void)tableView:(UITableView *)tableView dragSessionWillBegin:(id<UIDragSession>)session;

// Called to signal the end of the drag session.
- (void)tableView:(UITableView *)tableView dragSessionDidEnd:(id<UIDragSession>)session;

// Controls whether move operations are allowed for the drag session.
// If not implemented, defaults to YES.
- (BOOL)tableView:(UITableView *)tableView dragSessionAllowsMoveOperation:(id<UIDragSession>)session;

// Controls whether the drag session is restricted to the source application.
// If not implemented, defaults to NO.
- (BOOL)tableView:(UITableView *)tableView dragSessionIsRestrictedToDraggingApplication:(id<UIDragSession>)session;

@end


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@protocol UITableViewDropDelegate <NSObject>

@required

// Called when the user initiates the drop.
// Use the drop coordinator to access the items in the drop and the final destination index path and proposal for the drop,
// as well as specify how you wish to animate each item to its final position.
// If your implementation of this method does nothing, default drop animations will be supplied and the table view will
// revert back to its initial state before the drop session entered.
- (void)tableView:(UITableView *)tableView performDropWithCoordinator:(id<UITableViewDropCoordinator>)coordinator;

@optional

// If NO is returned no further delegate methods will be called for this drop session.
// If not implemented, a default value of YES is assumed.
- (BOOL)tableView:(UITableView *)tableView canHandleDropSession:(id<UIDropSession>)session;

// Called when the drop session begins tracking in the table view's coordinate space.
- (void)tableView:(UITableView *)tableView dropSessionDidEnter:(id<UIDropSession>)session;

// Called frequently while the drop session being tracked inside the table view's coordinate space.
// When the drop is at the end of a section, the destination index path passed will be for a row that does not yet exist (equal
// to the number of rows in that section), where an inserted row would append to the end of the section.
// The destination index path may be nil in some circumstances (e.g. when dragging over empty space where there are no cells).
// Note that in some cases your proposal may not be allowed and the system will enforce a different proposal.
// You may perform your own hit testing via -[session locationInView:]
- (UITableViewDropProposal *)tableView:(UITableView *)tableView dropSessionDidUpdate:(id<UIDropSession>)session withDestinationIndexPath:(nullable NSIndexPath *)destinationIndexPath;

// Called when the drop session is no longer being tracked inside the table view's coordinate space.
- (void)tableView:(UITableView *)tableView dropSessionDidExit:(id<UIDropSession>)session;

// Called when the drop session completed, regardless of outcome. Useful for performing any cleanup.
- (void)tableView:(UITableView *)tableView dropSessionDidEnd:(id<UIDropSession>)session;

// Allows customization of the preview used when dropping to a newly inserted row.
// If not implemented or if nil is returned, the entire cell will be used for the preview.
- (nullable UIDragPreviewParameters *)tableView:(UITableView *)tableView dropPreviewParametersForRowAtIndexPath:(NSIndexPath *)indexPath;

@end


typedef NS_ENUM(NSInteger, UITableViewDropIntent) {
    // Table view will accept the drop, but the location is not yet known and will be determined later.
    // Will not open a gap. You may wish to provide some visual treatment to communicate this to the user.
    UITableViewDropIntentUnspecified,
    
    // The drop will be placed in row(s) inserted at the destination index path.
    // Opens a gap at the specified location simulating the final dropped layout.
    UITableViewDropIntentInsertAtDestinationIndexPath,
    
    // The drop will be placed inside the row at the destination index path (e.g. the row is a container of other items).
    // Will not open a gap. Table view will highlight the row at the destination index path.
    UITableViewDropIntentInsertIntoDestinationIndexPath,
    
    // The table view will automatically choose between .insertAtDestinationIndexPath and
    // .insertIntoDestinationIndexPath depending on the position of the drop. This should be used instead
    // of .insertIntoDestinationIndexPath when the item being dropped can either be placed inside the row
    // at the destination index path or inserted in a new row at the index path of the container row.
    UITableViewDropIntentAutomatic
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);


UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@interface UITableViewDropProposal : UIDropProposal

- (instancetype)initWithDropOperation:(UIDropOperation)operation intent:(UITableViewDropIntent)intent;

// The default is UITableViewDropIntentUnspecified.
@property (nonatomic, readonly) UITableViewDropIntent intent;

@end


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@protocol UITableViewDropCoordinator <NSObject>

// Ordered list of items available for this drop.
@property (nonatomic, readonly) NSArray<id<UITableViewDropItem>> *items;

// The last hit-tested index path known during the drop session.
// When the drop is at the end of a section, this index path will be for a row that does not yet exist (equal
// to the number of rows in that section), where an inserted row would append to the end of the section.
// This index path may be nil in some circumstances (e.g. when dragging over empty space where there are no cells),
// and if it is nil, the proposal's intent will always be UITableViewDropIntentUnspecified.
@property (nonatomic, readonly, nullable) NSIndexPath *destinationIndexPath;

// The current drop proposal at the time of the drop.
@property (nonatomic, readonly) UITableViewDropProposal *proposal;

// The drop session.
@property (nonatomic, readonly) id<UIDropSession> session;

// Animate the dragItem to an automatically inserted placeholder row.
// Once the dragItem data is available, you can exchange the temporary placeholder cell with the final cell using the placeholder context
// method -commitInsertionWithDataSourceUpdates:
- (id<UITableViewDropPlaceholderContext>)dropItem:(UIDragItem *)dragItem toPlaceholder:(UITableViewDropPlaceholder *)placeholder;

// Animate the dragItem to a row that you inserted at this index path.
// You must call -performBatchUpdates:completion: to update your data source and insert a new row into the table view prior to calling this method.
// If desired, use the drop delegate method -tableView:dropPreviewParametersForRowAtIndexPath: to provide preview parameters.
- (id<UIDragAnimating>)dropItem:(UIDragItem *)dragItem toRowAtIndexPath:(NSIndexPath *)indexPath;

// Animate the dragItem to a rect inside an existing row.
// The rect is in the coordinate space of the cell at this index path.
// The item will be animated with an aspect fit scale transform to fit inside the rect. Use a rect with zero size to shrink the item to a single point.
- (id<UIDragAnimating>)dropItem:(UIDragItem *)dragItem intoRowAtIndexPath:(NSIndexPath *)indexPath rect:(CGRect)rect;

// Animate the dragItem to a location specified by the UIDragPreviewTarget.
// The -[UITableViewDropItem previewSize] may be helpful to compute an appropriate transform.
- (id<UIDragAnimating>)dropItem:(UIDragItem *)dragItem toTarget:(UIDragPreviewTarget *)target;

@end


UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@interface UITableViewPlaceholder : NSObject

// A placeholder cell will be dequeued for the reuse identifier and inserted at the specified index path without requiring a data source update.
// You may use UITableViewAutomaticDimension for the rowHeight to have the placeholder cell self-size if the table view is using estimated row heights.
- (instancetype)initWithInsertionIndexPath:(NSIndexPath *)insertionIndexPath reuseIdentifier:(NSString *)reuseIdentifier rowHeight:(CGFloat)rowHeight NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

// Called whenever the placeholder cell is visible to update the contents of the cell.
@property (nonatomic, nullable, copy) void(^cellUpdateHandler)(__kindof UITableViewCell *);

@end

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@interface UITableViewDropPlaceholder : UITableViewPlaceholder

// Allows customization of the preview used when dropping to a placeholder.
// If no block is set, or if nil is returned, the entire cell will be used for the preview.
@property (nonatomic, nullable, copy) UIDragPreviewParameters * _Nullable (^previewParametersProvider)(__kindof UITableViewCell *);

@end


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@protocol UITableViewDropItem <NSObject>

// Retrieve drop data from the dragItem's itemProvider.
@property (nonatomic, readonly) UIDragItem *dragItem;

// If this drop item is also from this table view this index path will specify the location of the row it came from.
// If the dragItem comes from some other source (e.g. another source inside or outside of the app), or if the source
// table view is updated or reloaded after the drag begins, this index path will be nil.
// This is useful for directly accessing the model object in your data source instead of using the item provider
// to retrieve the data.
@property (nonatomic, readonly, nullable) NSIndexPath *sourceIndexPath;

// May be useful for computing the UIDragPreviewTarget transform for UITableViewDropCoordinator dropItem:toTarget:
// Returns CGSizeZero if the dragItem does not have a visible drop preview.
@property (nonatomic, readonly) CGSize previewSize;

@end


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@protocol UITableViewDropPlaceholderContext <UIDragAnimating>

// The drag item this placeholder was created for.
@property (nonatomic, readonly) UIDragItem *dragItem;

// Exchange the placeholder for the final cell.
// You are only responsible for updating your data source inside the block using the provided insertionIndexPath.
// If the placeholder is no longer available (e.g. -reloadData has been called) the dataSourceUpdates block
// will not be executed and this will return NO.
- (BOOL)commitInsertionWithDataSourceUpdates:(void(NS_NOESCAPE ^)(NSIndexPath *insertionIndexPath))dataSourceUpdates;

// If the placeholder is no longer needed or you wish to manually insert a cell for the drop data, you can
// remove the placeholder via this method.
// If the placeholder is no longer available (e.g. -reloadData has been called) this will return NO.
- (BOOL)deletePlaceholder;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UITableView.h>
#endif
