#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UICollectionView.h>)
//
//  UICollectionView.h
//  UIKit
//
//  Copyright (c) 2011-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/NSIndexPath+UIKitAdditions.h>
#import <UIKit/UIScrollView.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIDataSourceTranslating.h>
#import <UIKit/UIDropInteraction.h>
#import <UIKit/UISpringLoadedInteractionSupporting.h>
#import <UIKit/UIContextMenuInteraction.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_OPTIONS(NSUInteger, UICollectionViewScrollPosition) {
    UICollectionViewScrollPositionNone                 = 0,
    
    // The vertical positions are mutually exclusive to each other, but are bitwise or-able with the horizontal scroll positions.
    // Combining positions from the same grouping (horizontal or vertical) will result in an NSInvalidArgumentException.
    UICollectionViewScrollPositionTop                  = 1 << 0,
    UICollectionViewScrollPositionCenteredVertically   = 1 << 1,
    UICollectionViewScrollPositionBottom               = 1 << 2,
    
    // Likewise, the horizontal positions are mutually exclusive to each other.
    UICollectionViewScrollPositionLeft                 = 1 << 3,
    UICollectionViewScrollPositionCenteredHorizontally = 1 << 4,
    UICollectionViewScrollPositionRight                = 1 << 5
} API_UNAVAILABLE(watchos);


typedef NS_ENUM(NSInteger, UICollectionViewReorderingCadence) {
    UICollectionViewReorderingCadenceImmediate,
    UICollectionViewReorderingCadenceFast,
    UICollectionViewReorderingCadenceSlow
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

typedef NS_ENUM(NSInteger, UICollectionViewSelfSizingInvalidation) {
    /// No updates will take place when -invalidateIntrinsicContentSize is called on a self-sizing cell or its contentView.
    UICollectionViewSelfSizingInvalidationDisabled,
    /// Calling -invalidateIntrinsicContentSize on a self-sizing cell or its contentView will cause it to be resized if necessary.
    UICollectionViewSelfSizingInvalidationEnabled,
    /// Calling -invalidateIntrinsicContentSize on a self-sizing cell or its contentView will cause it to be resized if necessary, and
    /// any Auto Layout changes within the contentView of a self-sizing cell will automatically trigger -invalidateIntrinsicContentSize.
    UICollectionViewSelfSizingInvalidationEnabledIncludingConstraints,
} API_AVAILABLE(ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

@class UICollectionView, UICollectionReusableView, UICollectionViewCell, UICollectionViewLayout, UICollectionViewTransitionLayout, UICollectionViewLayoutAttributes, UITouch, UINib;
@class UIDragItem, UIDragPreviewParameters, UIDragPreviewTarget;
@class UICollectionViewDropProposal, UICollectionViewPlaceholder, UICollectionViewDropPlaceholder;
@class UICollectionViewCellRegistration, UICollectionViewSupplementaryRegistration;
@class UIWindowSceneActivationConfiguration;
@protocol UIDataSourceTranslating, UISpringLoadedInteractionContext;
@protocol UIDragSession, UIDropSession;
@protocol UICollectionViewDragDelegate, UICollectionViewDropDelegate, UICollectionViewDropCoordinator, UICollectionViewDropItem, UICollectionViewDropPlaceholderContext;

// layout transition block signature
typedef void (^UICollectionViewLayoutInteractiveTransitionCompletion)(BOOL completed, BOOL finished) API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UICollectionViewFocusUpdateContext : UIFocusUpdateContext

@property (nonatomic, strong, readonly, nullable) NSIndexPath *previouslyFocusedIndexPath;
@property (nonatomic, strong, readonly, nullable) NSIndexPath *nextFocusedIndexPath;

@end

API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UICollectionViewDataSource <NSObject>
@required

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section;

// The cell that is returned must be retrieved from a call to -dequeueReusableCellWithReuseIdentifier:forIndexPath:
- (__kindof UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath;

@optional

- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView;

// The view that is returned must be retrieved from a call to -dequeueReusableSupplementaryViewOfKind:withReuseIdentifier:forIndexPath:
- (UICollectionReusableView *)collectionView:(UICollectionView *)collectionView viewForSupplementaryElementOfKind:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath;

- (BOOL)collectionView:(UICollectionView *)collectionView canMoveItemAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(9.0));
- (void)collectionView:(UICollectionView *)collectionView moveItemAtIndexPath:(NSIndexPath *)sourceIndexPath toIndexPath:(NSIndexPath*)destinationIndexPath API_AVAILABLE(ios(9.0));

/// Returns a list of index titles to display in the index view (e.g. ["A", "B", "C" ... "Z", "#"])
- (nullable NSArray<NSString *> *)indexTitlesForCollectionView:(UICollectionView *)collectionView API_AVAILABLE(ios(14.0), tvos(10.2)) API_UNAVAILABLE(watchos);

/// Returns the index path that corresponds to the given title / index. (e.g. "B",1)
/// Return an index path with a single index to indicate an entire section, instead of a specific item.
- (NSIndexPath *)collectionView:(UICollectionView *)collectionView indexPathForIndexTitle:(NSString *)title atIndex:(NSInteger)index API_AVAILABLE(ios(14.0), tvos(10.2)) API_UNAVAILABLE(watchos);

@end

API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UICollectionViewDataSourcePrefetching <NSObject>
@required
// indexPaths are ordered ascending by geometric distance from the collection view
- (void)collectionView:(UICollectionView *)collectionView prefetchItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths API_AVAILABLE(ios(10.0));

@optional
// indexPaths that previously were considered as candidates for pre-fetching, but were not actually used; may be a subset of the previous call to -collectionView:prefetchItemsAtIndexPaths:
- (void)collectionView:(UICollectionView *)collectionView cancelPrefetchingForItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths  API_AVAILABLE(ios(10.0));

@end


API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UICollectionViewDelegate <UIScrollViewDelegate>
@optional

// Methods for notification of selection/deselection and highlight/unhighlight events.
// The sequence of calls leading to selection from a user touch is:
//
// (when the touch begins)
// 1. -collectionView:shouldHighlightItemAtIndexPath:
// 2. -collectionView:didHighlightItemAtIndexPath:
//
// (when the touch lifts)
// 3. -collectionView:shouldSelectItemAtIndexPath: or -collectionView:shouldDeselectItemAtIndexPath:
// 4. -collectionView:didSelectItemAtIndexPath: or -collectionView:didDeselectItemAtIndexPath:
// 5. -collectionView:didUnhighlightItemAtIndexPath:
- (BOOL)collectionView:(UICollectionView *)collectionView shouldHighlightItemAtIndexPath:(NSIndexPath *)indexPath;
- (void)collectionView:(UICollectionView *)collectionView didHighlightItemAtIndexPath:(NSIndexPath *)indexPath;
- (void)collectionView:(UICollectionView *)collectionView didUnhighlightItemAtIndexPath:(NSIndexPath *)indexPath;
- (BOOL)collectionView:(UICollectionView *)collectionView shouldSelectItemAtIndexPath:(NSIndexPath *)indexPath;
- (BOOL)collectionView:(UICollectionView *)collectionView shouldDeselectItemAtIndexPath:(NSIndexPath *)indexPath; // called when the user taps on an already-selected item in multi-select mode
- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath;
- (void)collectionView:(UICollectionView *)collectionView didDeselectItemAtIndexPath:(NSIndexPath *)indexPath;

/*!
 * @abstract Called to determine if a primary action can be performed for the item at the given indexPath.
 * See @c collectionView:performPrimaryActionForItemAtIndexPath: for more details about primary actions.
 *
 * @param collectionView This UICollectionView
 * @param indexPath NSIndexPath of the item
 *
 * @return `YES` if the primary action can be performed; otherwise `NO`. If not implemented, defaults to `YES` when not editing
 * and `NO` when editing.
 */
- (BOOL)collectionView:(UICollectionView *)collectionView canPerformPrimaryActionForItemAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

/*!
 * @abstract Called when the primary action should be performed for the item at the given indexPath.
 *
 * @discussion Primary actions allow you to distinguish between a change of selection (which can be based on focus changes or
 * other indirect selection changes) and distinct user actions. Primary actions are performed when the user selects a cell without extending
 * an existing selection. This is called after @c shouldSelectItem and @c didSelectItem , regardless of whether the cell's selection
 * state was allowed to change.
 *
 * As an example, use @c didSelectItemAtIndexPath for updating state in the current view controller (i.e. buttons, title, etc) and
 * use the primary action for navigation or showing another split view column.
 *
 * @param collectionView This UICollectionView
 * @param indexPath NSIndexPath of the item to perform the action on
 */
- (void)collectionView:(UICollectionView *)collectionView performPrimaryActionForItemAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

- (void)collectionView:(UICollectionView *)collectionView willDisplayCell:(UICollectionViewCell *)cell forItemAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(8.0));
- (void)collectionView:(UICollectionView *)collectionView willDisplaySupplementaryView:(UICollectionReusableView *)view forElementKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(8.0));
- (void)collectionView:(UICollectionView *)collectionView didEndDisplayingCell:(UICollectionViewCell *)cell forItemAtIndexPath:(NSIndexPath *)indexPath;
- (void)collectionView:(UICollectionView *)collectionView didEndDisplayingSupplementaryView:(UICollectionReusableView *)view forElementOfKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)indexPath;

// These methods provide support for copy/paste actions on cells.
// All three should be implemented if any are.
- (BOOL)collectionView:(UICollectionView *)collectionView shouldShowMenuForItemAtIndexPath:(NSIndexPath *)indexPath API_DEPRECATED_WITH_REPLACEMENT("collectionView:contextMenuConfigurationForItemsAtIndexPaths:point:", ios(6.0, 13.0)) API_UNAVAILABLE(visionos, watchos);
- (BOOL)collectionView:(UICollectionView *)collectionView canPerformAction:(SEL)action forItemAtIndexPath:(NSIndexPath *)indexPath withSender:(nullable id)sender API_DEPRECATED_WITH_REPLACEMENT("collectionView:contextMenuConfigurationForItemsAtIndexPaths:point:", ios(6.0, 13.0)) API_UNAVAILABLE(visionos, watchos);
- (void)collectionView:(UICollectionView *)collectionView performAction:(SEL)action forItemAtIndexPath:(NSIndexPath *)indexPath withSender:(nullable id)sender API_DEPRECATED_WITH_REPLACEMENT("collectionView:contextMenuConfigurationForItemsAtIndexPaths:point:", ios(6.0, 13.0)) API_UNAVAILABLE(visionos, watchos);

// support for custom transition layout
- (nonnull UICollectionViewTransitionLayout *)collectionView:(UICollectionView *)collectionView transitionLayoutForOldLayout:(UICollectionViewLayout *)fromLayout newLayout:(UICollectionViewLayout *)toLayout;

// Focus
- (BOOL)collectionView:(UICollectionView *)collectionView canFocusItemAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(9.0));
- (BOOL)collectionView:(UICollectionView *)collectionView shouldUpdateFocusInContext:(UICollectionViewFocusUpdateContext *)context API_AVAILABLE(ios(9.0));
- (void)collectionView:(UICollectionView *)collectionView didUpdateFocusInContext:(UICollectionViewFocusUpdateContext *)context withAnimationCoordinator:(UIFocusAnimationCoordinator *)coordinator API_AVAILABLE(ios(9.0));
- (nullable NSIndexPath *)indexPathForPreferredFocusedViewInCollectionView:(UICollectionView *)collectionView API_AVAILABLE(ios(9.0));

/// Determines if the item at the specified index path should also become selected when focus moves to it.
/// If the collection view's global selectionFollowsFocus is enabled, this method will allow you to override that behavior on a per-index path basis. This method is not called if selectionFollowsFocus is disabled.
- (BOOL)collectionView:(UICollectionView *)collectionView selectionFollowsFocusForItemAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos);

- (NSIndexPath *)collectionView:(UICollectionView *)collectionView targetIndexPathForMoveOfItemFromOriginalIndexPath:(NSIndexPath *)originalIndexPath atCurrentIndexPath:(NSIndexPath *)currentIndexPath toProposedIndexPath:(NSIndexPath *)proposedIndexPath API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);
- (NSIndexPath *)collectionView:(UICollectionView *)collectionView targetIndexPathForMoveFromItemAtIndexPath:(NSIndexPath *)currentIndexPath toProposedIndexPath:(NSIndexPath *)proposedIndexPath API_DEPRECATED_WITH_REPLACEMENT("collectionView:targetIndexPathForMoveOfItemFromOriginalIndexPath:atCurrentIndexPath:toProposedIndexPath:", ios(9.0, 15.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);

- (CGPoint)collectionView:(UICollectionView *)collectionView targetContentOffsetForProposedContentOffset:(CGPoint)proposedContentOffset API_AVAILABLE(ios(9.0)); // customize the content offset to be applied during transition or update animations

// Editing
/* Asks the delegate to verify that the given item is editable.
 *
 * @param collectionView The collection view object requesting this information.
 * @param indexPath An index path locating an item in `collectionView`.
 *
 * @return `YES` if the item is editable; otherwise, `NO`. Defaults to `YES`.
 */
- (BOOL)collectionView:(UICollectionView *)collectionView canEditItemAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);

// Spring Loading

/* Allows opting-out of spring loading for an particular item.
 *
 * If you want the interaction effect on a different subview of the spring loaded cell, modify the context.targetView property.
 * The default is the cell.
 *
 * If this method is not implemented, the default is YES.
 */
- (BOOL)collectionView:(UICollectionView *)collectionView shouldSpringLoadItemAtIndexPath:(NSIndexPath *)indexPath withContext:(id<UISpringLoadedInteractionContext>)context API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

// Multiple Selection

/* Allows a two-finger pan gesture to automatically enable allowsMultipleSelection and start selecting multiple cells.
 *
 * After a multi-select gesture is recognized, this method will be called before allowsMultipleSelection is automatically
 * set to YES to allow the user to select multiple contiguous items using a two-finger pan gesture across the constrained
 * scroll direction.
 *
 * If the collection view has no constrained scroll direction (i.e., the collection view scrolls both horizontally and vertically),
 * then this method will not be called and the multi-select gesture will be disabled.
 *
 * If this method is not implemented, the default is NO.
 */
- (BOOL)collectionView:(UICollectionView *)collectionView shouldBeginMultipleSelectionInteractionAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);

/* Called right after allowsMultipleSelection is set to YES if -collectionView:shouldBeginMultipleSelectionInteractionAtIndexPath:
 * returned YES.
 *
 * In your app, this would be a good opportunity to update the state of your UI to reflect the fact that the user is now selecting
 * multiple items at once; such as updating buttons to say "Done" instead of "Select"/"Edit", for instance.
 */
- (void)collectionView:(UICollectionView *)collectionView didBeginMultipleSelectionInteractionAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);

/* Called when the multi-select interaction ends.
 *
 * At this point, the collection view will remain in multi-select mode, but this delegate method is called to indicate that the
 * multiple selection gesture or hardware keyboard interaction has ended.
 */
- (void)collectionViewDidEndMultipleSelectionInteraction:(UICollectionView *)collectionView API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);


/*!
 * @abstract Called when a context menu is invoked from this collection view.
 *
 * @param collectionView  The @c UICollectionView.
 * @param indexPaths      An array of index paths on which the menu acts.
 * @param point           Touch location in the collection view's coordinate space.
 *
 * @return A @c UIContextMenuConfiguration describing the menu to be presented. Return nil to prevent the interaction from beginning.
 *         Returning an empty configuration causes the interaction to begin then fail with a cancellation effect. You might use this
 *         to indicate to users that it's possible for a menu to be presented from this element, but that there are no actions to
 *         present at this particular time.
 *
 * @discussion  The @c indexPaths array may contain 0-many items:
 *              - An empty array indicates that the menu was invoked in the space between cells (or any location that does not map to an item index path).
 *              - An array with multiple index paths indicates that the menu was invoked on an item within a multiple selection.
 */
- (nullable UIContextMenuConfiguration *)collectionView:(UICollectionView *)collectionView
           contextMenuConfigurationForItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths
                                                  point:(CGPoint)point API_AVAILABLE(ios(16.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @abstract Called when a context menu interaction begins in this collection view to request a preview for the interaction's initial highlight effect.
 *           Return a @c UITargetedPreview corresponding to the item at the given indexPath.
 *
 * @param collectionView  The @c UICollectionView.
 * @param configuration   Configuration of the menu that will be presented if the interaction proceeds.
 * @param indexPath       Index path of the item at which the interaction is occurring.
 */
- (nullable UITargetedPreview *)collectionView:(UICollectionView *)collectionView
                      contextMenuConfiguration:(UIContextMenuConfiguration *)configuration
            highlightPreviewForItemAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(16.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @abstract Called when a context menu presented from this collection view is dismissed. Return a @c UITargetedPreview corresponding to the item at the given indexPath.
 *
 * @param collectionView  The @c UICollectionView.
 * @param configuration   Configuration of the menu being dismissed.
 * @param indexPath       Index path of the item to which the menu is being dismissed.
 */
- (nullable UITargetedPreview *)collectionView:(UICollectionView *)collectionView
                      contextMenuConfiguration:(UIContextMenuConfiguration *)configuration
            dismissalPreviewForItemAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(16.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @abstract Called when the interaction is about to "commit" in response to the user tapping the preview.
 *
 * @param collectionView  The @c UICollectionView.
 * @param configuration   Configuration of the currently displayed menu.
 * @param animator        Commit animator. Add animations to this object to run them alongside the commit transition.
 */
- (void)collectionView:(UICollectionView *)collectionView willPerformPreviewActionForMenuWithConfiguration:(UIContextMenuConfiguration *)configuration animator:(id<UIContextMenuInteractionCommitAnimating>)animator API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @abstract Called when the collection view is about to display a menu.
 *
 * @param collectionView  The @c UICollectionView.
 * @param configuration   The configuration of the menu about to be displayed.
 * @param animator        Appearance animator. Add animations to run them alongside the appearance transition.
 */
- (void)collectionView:(UICollectionView *)collectionView willDisplayContextMenuWithConfiguration:(UIContextMenuConfiguration *)configuration animator:(nullable id<UIContextMenuInteractionAnimating>)animator API_AVAILABLE(ios(13.2), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @abstract Called when the collection view's context menu interaction is about to end.
 *
 * @param collectionView  The @c UICollectionView.
 * @param configuration   Ending configuration.
 * @param animator        Disappearance animator. Add animations to run them alongside the disappearance transition.
 */
- (void)collectionView:(UICollectionView *)collectionView willEndContextMenuInteractionWithConfiguration:(UIContextMenuConfiguration *)configuration animator:(nullable id<UIContextMenuInteractionAnimating>)animator API_AVAILABLE(ios(13.2), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @abstract Return a valid @c UIWindowSceneActivationConfiguration to allow for the cell to be expanded into a new scene. Return nil to prevent the interaction from starting.
 *
 * @param collectionView The collection view
 * @param indexPath The index path of the cell being interacted with
 * @param point The centroid of the interaction in the collection view's coordinate space.
 */
- (nullable UIWindowSceneActivationConfiguration *)collectionView:(UICollectionView *)collectionView sceneActivationConfigurationForItemAtIndexPath:(NSIndexPath *)indexPath point:(CGPoint)point API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @abstract Called when the interaction begins.
 *
 * @param collectionView  The @c UICollectionView.
 * @param indexPath       IndexPath of the item for which a configuration is being requested.
 * @param point           Touch location in the collection view's coordinate space
 *
 * @return A UIContextMenuConfiguration describing the menu to be presented. Return nil to prevent the interaction from beginning.
 *         Returning an empty configuration causes the interaction to begin then fail with a cancellation effect. You might use this
 *         to indicate to users that it's possible for a menu to be presented from this element, but that there are no actions to
 *         present at this particular time. If the non-deprecated replacement for the configuration, highlight preview, or dismissal preview methods is implemented this method is not called.
 */
- (nullable UIContextMenuConfiguration *)collectionView:(UICollectionView *)collectionView
             contextMenuConfigurationForItemAtIndexPath:(NSIndexPath *)indexPath
                                                  point:(CGPoint)point API_DEPRECATED_WITH_REPLACEMENT("collectionView:contextMenuConfigurationForItemsAtIndexPaths:point:", ios(13.0, 16.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @abstract Called when the interaction begins. Return a UITargetedPreview describing the desired highlight preview.
 *           If the non-deprecated replacement for the configuration, highlight preview, or dismissal preview methods is implemented this method is not called.
 *
 * @param collectionView  The @c UICollectionView.
 * @param configuration   The configuration of the menu about to be displayed by this interaction.
 */
- (nullable UITargetedPreview *)collectionView:(UICollectionView *)collectionView previewForHighlightingContextMenuWithConfiguration:(UIContextMenuConfiguration *)configuration API_DEPRECATED_WITH_REPLACEMENT("collectionView:contextMenuConfiguration:highlightPreviewForItemAtIndexPath:", ios(13.0, 16.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @abstract Called when the interaction is about to dismiss. Return a UITargetedPreview describing the desired dismissal target.
 *           The interaction will animate the presented menu to the target. Use this to customize the dismissal animation.
 *           If the non-deprecated replacement for the configuration, highlight preview, or dismissal preview methods is implemented this method is not called.
 *
 * @param collectionView  The @c UICollectionView.
 * @param configuration   The configuration of the menu displayed by this interaction.
 */
- (nullable UITargetedPreview *)collectionView:(UICollectionView *)collectionView previewForDismissingContextMenuWithConfiguration:(UIContextMenuConfiguration *)configuration API_DEPRECATED_WITH_REPLACEMENT("collectionView:contextMenuConfiguration:dismissalPreviewForItemAtIndexPath:", ios(13.0, 16.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos, tvos);

@end

UIKIT_EXTERN API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UICollectionView : UIScrollView <UIDataSourceTranslating>

- (instancetype)initWithFrame:(CGRect)frame collectionViewLayout:(UICollectionViewLayout *)layout NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property (nonatomic, strong) UICollectionViewLayout *collectionViewLayout;
@property (nonatomic, weak, nullable) id <UICollectionViewDelegate> delegate;
@property (nonatomic, weak, nullable) id <UICollectionViewDataSource> dataSource;

@property (nonatomic, weak, nullable) id<UICollectionViewDataSourcePrefetching> prefetchDataSource API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, getter=isPrefetchingEnabled) BOOL prefetchingEnabled API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos);

@property (nonatomic, weak, nullable) id <UICollectionViewDragDelegate> dragDelegate API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);
@property (nonatomic, weak, nullable) id <UICollectionViewDropDelegate> dropDelegate API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);


/*
 * You can force drags to be disabled for this collection view by setting this to NO.
 * As of iOS 15, this is true for both iPhone and iPad by default. Prior to iOS 15, it defaulted to false on iPhone.
 */
@property (nonatomic) BOOL dragInteractionEnabled API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

@property (nonatomic, readonly, nullable) UIContextMenuInteraction *contextMenuInteraction API_AVAILABLE(ios(13.2), tvos(17.0)) API_UNAVAILABLE(watchos);

/* Reordering cadence affects how easily reordering occurs while dragging around a reorder-capable drop destination.
 * Default is UICollectionViewReorderingCadenceImmediate.
 */
@property (nonatomic) UICollectionViewReorderingCadence reorderingCadence API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

@property (nonatomic) UICollectionViewSelfSizingInvalidation selfSizingInvalidation API_AVAILABLE(ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

@property (nonatomic, strong, nullable) UIView *backgroundView; // will be automatically resized to track the size of the collection view and placed behind all cells and supplementary views.

// For each reuse identifier that the collection view will use, register either a class or a nib from which to instantiate a cell.
// If a nib is registered, it must contain exactly 1 top level object which is a UICollectionViewCell.
// If a class is registered, it will be instantiated via alloc/initWithFrame:
- (void)registerClass:(nullable Class)cellClass forCellWithReuseIdentifier:(NSString *)identifier;
- (void)registerNib:(nullable UINib *)nib forCellWithReuseIdentifier:(NSString *)identifier API_DEPRECATED("Loading Interface Builder products will not be supported in a future version of visionOS.", visionos(1.0, 1.0));

- (void)registerClass:(nullable Class)viewClass forSupplementaryViewOfKind:(NSString *)elementKind withReuseIdentifier:(NSString *)identifier;
- (void)registerNib:(nullable UINib *)nib forSupplementaryViewOfKind:(NSString *)kind withReuseIdentifier:(NSString *)identifier API_DEPRECATED("Loading Interface Builder products will not be supported in a future version of visionOS.", visionos(1.0, 1.0));

- (__kindof UICollectionViewCell *)dequeueReusableCellWithReuseIdentifier:(NSString *)identifier forIndexPath:(NSIndexPath *)indexPath;
- (__kindof UICollectionReusableView *)dequeueReusableSupplementaryViewOfKind:(NSString *)elementKind withReuseIdentifier:(NSString *)identifier forIndexPath:(NSIndexPath *)indexPath;

- (__kindof UICollectionViewCell *)dequeueConfiguredReusableCellWithRegistration:(UICollectionViewCellRegistration*)registration forIndexPath:(NSIndexPath*)indexPath item:(id)item API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);
- (__kindof UICollectionReusableView *)dequeueConfiguredReusableSupplementaryViewWithRegistration:(UICollectionViewSupplementaryRegistration*)registration forIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);

// These properties control whether items can be selected, and if so, whether multiple items can be simultaneously selected.
@property (nonatomic) BOOL allowsSelection; // default is YES
@property (nonatomic) BOOL allowsMultipleSelection; // default is NO

@property (nonatomic, readonly, nullable) NSArray<NSIndexPath *> *indexPathsForSelectedItems; // returns nil or an array of selected index paths
- (void)selectItemAtIndexPath:(nullable NSIndexPath *)indexPath animated:(BOOL)animated scrollPosition:(UICollectionViewScrollPosition)scrollPosition;
- (void)deselectItemAtIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated;

// Returns YES if the collection view is reordering or has drop placeholders.
@property (nonatomic, readonly) BOOL hasUncommittedUpdates API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos);

// Note: -reloadData will discard any uncommitted updates (e.g. placeholders)
- (void)reloadData; // discard the dataSource and delegate data and requery as necessary

- (void)setCollectionViewLayout:(UICollectionViewLayout *)layout animated:(BOOL)animated; // transition from one layout to another
- (void)setCollectionViewLayout:(UICollectionViewLayout *)layout animated:(BOOL)animated completion:(void (^ __nullable)(BOOL finished))completion NS_SWIFT_DISABLE_ASYNC API_AVAILABLE(ios(7.0));

- (UICollectionViewTransitionLayout *)startInteractiveTransitionToCollectionViewLayout:(UICollectionViewLayout *)layout completion:(nullable UICollectionViewLayoutInteractiveTransitionCompletion)completion API_AVAILABLE(ios(7.0));
- (void)finishInteractiveTransition API_AVAILABLE(ios(7.0));
- (void)cancelInteractiveTransition API_AVAILABLE(ios(7.0));

// Information about the current state of the collection view.

@property (nonatomic, readonly) NSInteger numberOfSections;
- (NSInteger)numberOfItemsInSection:(NSInteger)section;

- (nullable UICollectionViewLayoutAttributes *)layoutAttributesForItemAtIndexPath:(NSIndexPath *)indexPath;
- (nullable UICollectionViewLayoutAttributes *)layoutAttributesForSupplementaryElementOfKind:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath;

- (nullable NSIndexPath *)indexPathForItemAtPoint:(CGPoint)point;
- (nullable NSIndexPath *)indexPathForCell:(UICollectionViewCell *)cell;

/// Gets the index path of the specified supplementary view.
/// @param supplementaryView The supplementary or decoration view whose index path you want.
/// @return The index path of the specified view if it is in the collection view, else `nil`.
- (nullable NSIndexPath *)indexPathForSupplementaryView:(UICollectionReusableView *)supplementaryView;

// Returns any existing visible or prepared cell for the index path. Returns nil when no cell exists, or if index path is out of range.
- (nullable __kindof UICollectionViewCell *)cellForItemAtIndexPath:(NSIndexPath *)indexPath;

@property (nonatomic, readonly) NSArray<__kindof UICollectionViewCell *> *visibleCells;
@property (nonatomic, readonly) NSArray<NSIndexPath *> *indexPathsForVisibleItems;

- (nullable UICollectionReusableView *)supplementaryViewForElementKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(9.0));
- (NSArray<UICollectionReusableView *> *)visibleSupplementaryViewsOfKind:(NSString *)elementKind API_AVAILABLE(ios(9.0));
- (NSArray<NSIndexPath *> *)indexPathsForVisibleSupplementaryElementsOfKind:(NSString *)elementKind API_AVAILABLE(ios(9.0));

// Interacting with the collection view.

- (void)scrollToItemAtIndexPath:(NSIndexPath *)indexPath atScrollPosition:(UICollectionViewScrollPosition)scrollPosition animated:(BOOL)animated;

// These methods allow dynamic modification of the current set of items in the collection view
- (void)insertSections:(NSIndexSet *)sections;
- (void)deleteSections:(NSIndexSet *)sections;
- (void)moveSection:(NSInteger)section toSection:(NSInteger)newSection;
- (void)reloadSections:(NSIndexSet *)sections;

- (void)insertItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;
- (void)deleteItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;
- (void)moveItemAtIndexPath:(NSIndexPath *)indexPath toIndexPath:(NSIndexPath *)newIndexPath;
- (void)reloadItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;
// Reconfigures any existing cells for the items. Reconfiguring is more efficient than reloading an item, as it does not replace the
// existing cell with a new cell. Prefer reconfiguring over reloading unless you actually need an entirely new cell for the item.
- (void)reconfigureItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

- (void)performBatchUpdates:(void (NS_NOESCAPE ^ _Nullable)(void))updates completion:(void (^ _Nullable)(BOOL finished))completion NS_SWIFT_DISABLE_ASYNC; // allows multiple insert/delete/reload/move calls to be animated simultaneously. Nestable.

// Support for reordering
- (BOOL)beginInteractiveMovementForItemAtIndexPath:(NSIndexPath *)indexPath API_AVAILABLE(ios(9.0)); // returns NO if reordering was prevented from beginning - otherwise YES
- (void)updateInteractiveMovementTargetPosition:(CGPoint)targetPosition API_AVAILABLE(ios(9.0));
- (void)endInteractiveMovement API_AVAILABLE(ios(9.0));
- (void)cancelInteractiveMovement API_AVAILABLE(ios(9.0));

// Support for Focus
@property (nonatomic) BOOL remembersLastFocusedIndexPath API_AVAILABLE(ios(9.0)); // defaults to NO. If YES, when focusing on a collection view the last focused index path is focused automatically. If the collection view has never been focused, then the preferred focused index path is used.

/// When enabled, the collection view ensures that selection is automatically triggered when focus moves to a cell.
/// Defaults to a system derived value based on platform and other properties of the collection view.
@property (nonatomic) BOOL selectionFollowsFocus API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos);

/// Determines if the collection view allows its cells to become focused.
/// When collectionView:canFocusItemAtIndexPath: is implemented, its return value takes precedence over this method.
/// Defaults to a system derived value based on platform and other properties of the collection view.
@property (nonatomic) BOOL allowsFocus API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

/// Determines if the collection view allows its cells to become focused while editing.
/// When collectionView:canFocusItemAtIndexPath: is implemented, its return value takes precedence over this method.
/// Defaults to a system derived value based on platform and other properties of the collection view.
@property (nonatomic) BOOL allowsFocusDuringEditing API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

// Drag & Drop

/* YES if a drag session is currently active. A drag session begins after items are "lifted" from the collection view.
 */
@property (nonatomic, readonly) BOOL hasActiveDrag API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

/* YES if collection view is currently tracking a drop session.
 */
@property (nonatomic, readonly) BOOL hasActiveDrop API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

// Editing

/* Controls the editing state for the receiver.
 */
@property (nonatomic, getter=isEditing) BOOL editing API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);

/* Controls whether an item can be selected when the receiver is editing.
 * Defaults to NO.
 */
@property (nonatomic) BOOL allowsSelectionDuringEditing API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);


/* Controls whether multiple item selection can occur when the receiver is editing.
 * Defaults to NO.
 */
@property (nonatomic) BOOL allowsMultipleSelectionDuringEditing API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);

@end

// _______________________________________________________________________________________________________________
// Drag & Drop


#if TARGET_OS_IOS
@interface UICollectionView (UIDragAndDrop) <UISpringLoadedInteractionSupporting>
@end
#endif

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@protocol UICollectionViewDragDelegate <NSObject>

@required

/* Provide items to begin a drag associated with a given indexPath.
 * If an empty array is returned a drag session will not begin.
 */
- (NSArray<UIDragItem *> *)collectionView:(UICollectionView *)collectionView itemsForBeginningDragSession:(id<UIDragSession>)session atIndexPath:(NSIndexPath *)indexPath;

@optional

/* Called to request items to add to an existing drag session in response to the add item gesture.
 * You can use the provided point (in the collection view's coordinate space) to do additional hit testing if desired.
 * If not implemented, or if an empty array is returned, no items will be added to the drag and the gesture
 * will be handled normally.
 */
- (NSArray<UIDragItem *> *)collectionView:(UICollectionView *)collectionView itemsForAddingToDragSession:(id<UIDragSession>)session atIndexPath:(NSIndexPath *)indexPath point:(CGPoint)point;

/* Allows customization of the preview used for the item being lifted from or cancelling back to the collection view.
 * If not implemented or if nil is returned, the entire cell will be used for the preview.
 */
- (nullable UIDragPreviewParameters *)collectionView:(UICollectionView *)collectionView dragPreviewParametersForItemAtIndexPath:(NSIndexPath *)indexPath;

/* Called after the lift animation has completed to signal the start of a drag session.
 * This call will always be balanced with a corresponding call to -collectionView:dragSessionDidEnd:
 */
- (void)collectionView:(UICollectionView *)collectionView dragSessionWillBegin:(id<UIDragSession>)session;

/* Called to signal the end of the drag session.
 */
- (void)collectionView:(UICollectionView *)collectionView dragSessionDidEnd:(id<UIDragSession>)session;


/* Controls whether move operations (see UICollectionViewDropProposal.operation) are allowed for the drag session.
 * If not implemented this will default to YES.
 */
- (BOOL)collectionView:(UICollectionView *)collectionView dragSessionAllowsMoveOperation:(id<UIDragSession>)session;

/* Controls whether the drag session is restricted to the source application.
 * If YES the current drag session will not be permitted to drop into another application.
 * If not implemented this will default to NO.
 */
- (BOOL)collectionView:(UICollectionView *)collectionView dragSessionIsRestrictedToDraggingApplication:(id<UIDragSession>)session;

@end

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@protocol UICollectionViewDropDelegate <NSObject>

@required

/* Called when the user initiates the drop.
 * Use the dropCoordinator to specify how you wish to animate the dropSession's items into their final position as
 * well as update the collection view's data source with data retrieved from the dropped items.
 * If the supplied method does nothing, default drop animations will be supplied and the collection view will
 * revert back to its initial pre-drop session state.
 */
- (void)collectionView:(UICollectionView *)collectionView performDropWithCoordinator:(id<UICollectionViewDropCoordinator>)coordinator;

@optional

/* If NO is returned no further delegate methods will be called for this drop session.
 * If not implemented, a default value of YES is assumed.
 */
- (BOOL)collectionView:(UICollectionView *)collectionView canHandleDropSession:(id<UIDropSession>)session;

/* Called when the drop session begins tracking in the collection view's coordinate space.
 */
- (void)collectionView:(UICollectionView *)collectionView dropSessionDidEnter:(id<UIDropSession>)session;

/* Called frequently while the drop session being tracked inside the collection view's coordinate space.
 * When the drop is at the end of a section, the destination index path passed will be for a item that does not yet exist (equal
 * to the number of items in that section), where an inserted item would append to the end of the section.
 * The destination index path may be nil in some circumstances (e.g. when dragging over empty space where there are no cells).
 * Note that in some cases your proposal may not be allowed and the system will enforce a different proposal.
 * You may perform your own hit testing via -[UIDropSession locationInView]
 */
- (UICollectionViewDropProposal *)collectionView:(UICollectionView *)collectionView dropSessionDidUpdate:(id<UIDropSession>)session withDestinationIndexPath:(nullable NSIndexPath *)destinationIndexPath;

/* Called when the drop session is no longer being tracked inside the collection view's coordinate space.
 */
- (void)collectionView:(UICollectionView *)collectionView dropSessionDidExit:(id<UIDropSession>)session;

/* Called when the drop session completed, regardless of outcome. Useful for performing any cleanup.
 */
- (void)collectionView:(UICollectionView *)collectionView dropSessionDidEnd:(id<UIDropSession>)session;

/* Allows customization of the preview used for the item being dropped.
 * If not implemented or if nil is returned, the entire cell will be used for the preview.
 *
 * This will be called as needed when animating drops via -[UICollectionViewDropCoordinator dropItem:toItemAtIndexPath:]
 * (to customize placeholder drops, please see UICollectionViewDropPlaceholder.previewParametersProvider)
 */
- (nullable UIDragPreviewParameters *)collectionView:(UICollectionView *)collectionView dropPreviewParametersForItemAtIndexPath:(NSIndexPath *)indexPath;

@end

typedef NS_ENUM(NSInteger, UICollectionViewDropIntent) {
    /* Collection view will accept the drop, but the location is not yet known and will be determined later.
     * Will not open a gap. You may wish to provide some visual treatment to communicate this to the user.
     */
    UICollectionViewDropIntentUnspecified,
    
    /* The drop will be placed in item(s) inserted at the destination index path.
     * Opens a gap at the specified location simulating the final dropped layout.
     */
    UICollectionViewDropIntentInsertAtDestinationIndexPath,
    
    /* The drop will be placed inside the item at the destination index path (e.g. the item is a container of other items).
     * Will not open a gap. Collection view will highlight the item at the destination index path.
     */
    UICollectionViewDropIntentInsertIntoDestinationIndexPath,
    
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);


UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UICollectionViewDropProposal : UIDropProposal

- (instancetype)initWithDropOperation:(UIDropOperation)operation intent:(UICollectionViewDropIntent)intent;

/* The default is UICollectionViewDropIntentUnspecified.
 */
@property (nonatomic, readonly) UICollectionViewDropIntent intent;

@end


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@protocol UICollectionViewDropCoordinator <NSObject>

/* Ordered list of items available for this drop.
 */
@property (nonatomic, readonly) NSArray<id<UICollectionViewDropItem>> *items;

/* The last hit-tested index path known during the drop session.
 * If this is nil, the proposal's intent will be .unspecified
 */
@property (nonatomic, readonly, nullable) NSIndexPath *destinationIndexPath;

/* The current drop proposal at the time of the drop.
 */
@property (nonatomic, readonly) UICollectionViewDropProposal *proposal;


@property (nonatomic, readonly) id<UIDropSession> session;

/* Animate the dragItem to an automatically inserted placeholder item.
 *
 * A placeholder cell will be created for the reuse identifier and inserted at the specified indexPath without requiring a dataSource update.
 *
 * The cellUpdateHandler will be called whenever the placeholder cell becomes visible; -collectionView:cellForItemAtIndexPath: will not be called
 * for the placeholder.
 *
 * Once the dragItem data is available, you can exchange the temporary placeholder cell with the final cell using
 * the placeholder context method -commitInsertionWithDataSourceUpdates:
 *
 * UICollectionViewDropPlaceholderContext also conforms to UIDragAnimating to allow adding alongside animations and completion handlers.
 */
- (id<UICollectionViewDropPlaceholderContext>)dropItem:(UIDragItem *)dragItem toPlaceholder:(UICollectionViewDropPlaceholder*)placeholder;

/* Animate the dragItem to a newly inserted item at the specified index path.
 * You must call -performBatchUpdates:completion: to update your data source and insert a new item into the collection view prior to calling this method.
 *
 * To tweak the appearance of the preview being dropping (e.g. supply a clipping path), see -collectionView:dropPreviewParametersForItemAtIndexPath:
 */
- (id<UIDragAnimating>)dropItem:(UIDragItem *)dragItem toItemAtIndexPath:(NSIndexPath *)indexPath;

/* Animate the dragItem to a rect inside an existing item.
 * The rect is in the coordinate space of the cell at this index path.
 * The item will be animated with an aspect fit scale transform to fit inside the rect. Use a rect with zero size to shrink the item to a single point.
 */
- (id<UIDragAnimating>)dropItem:(UIDragItem *)dragItem intoItemAtIndexPath:(NSIndexPath *)indexPath rect:(CGRect)rect;

/* Animate the dragItem to a location specified by the UIDragPreviewTarget.
 */
- (id<UIDragAnimating>)dropItem:(UIDragItem *)dragItem toTarget:(UIDragPreviewTarget *)target;

@end

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos,watchos) NS_SWIFT_UI_ACTOR
@interface UICollectionViewPlaceholder : NSObject

- (instancetype)initWithInsertionIndexPath:(NSIndexPath*)insertionIndexPath reuseIdentifier:(NSString *)reuseIdentifier NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/* Called whenever the placeholder cell is visible to update the contents of the cell.
 */
@property (nonatomic, nullable, copy) void(^cellUpdateHandler)(__kindof UICollectionViewCell *);

@end

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos,watchos) NS_SWIFT_UI_ACTOR
@interface UICollectionViewDropPlaceholder : UICollectionViewPlaceholder

/* If specified, will be used to modify the appearance (e.g. visiblePath to supply a "cut out" region of the placeholder cell) of the animating dropped item.
 * Handler will be called as-needed.
 */
@property (nonatomic, nullable, copy) UIDragPreviewParameters * _Nullable (^previewParametersProvider)(__kindof UICollectionViewCell *);
@end


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@protocol UICollectionViewDropItem <NSObject>

@property (nonatomic, readonly) UIDragItem *dragItem;

/* If this drop item is also from this collection view this indexPath will specify the location of the item.
 * If the dragItem comes from some other source (e.g. another source inside or outside of the app), it will be nil.
 * This is useful for directly accessing the model objects in the data source instead of using the item provider
 * to retrieve the data.
 */
@property (nonatomic, readonly, nullable) NSIndexPath *sourceIndexPath;

/* May be useful for computing the UIDragPreviewTarget transform for UICollectionViewDropCoordinator dropItem:toTarget:
 * Returns CGSizeZero if the dragItem does not have a visible drop preview.
 */
@property (nonatomic, readonly) CGSize previewSize;

@end


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@protocol UICollectionViewDropPlaceholderContext <UIDragAnimating>

/* Retrieve drop data from the dragItem's itemProvider.
 */
@property (nonatomic, readonly) UIDragItem *dragItem;


/* Exchange the placeholder for the final cell.
 * You are only responsible for updating your data source inside the block using the provided insertionIndexPath.
 * If the placeholder is no longer available (e.g. -reloadData has been called) the dataSourceUpdates block
 * will not be executed and this will return NO.
 */
- (BOOL)commitInsertionWithDataSourceUpdates:(void(NS_NOESCAPE ^)(NSIndexPath *insertionIndexPath))dataSourceUpdates;

/* If the placeholder is no longer needed or you wish to manually insert a cell for the drop data, you can
 * remove the placeholder via this method.
 * If the placeholder is no longer available (e.g. -reloadData has been called) this will return NO.
 */
- (BOOL)deletePlaceholder;

/* Call this method to request an update of the placeholder cell's content via the updateCellHandler.
 * This will only be called if the placeholder is visible. If the placeholder becomes visible via scrolling,
 * the updateCellHandler will automatically be called.
 */
- (void)setNeedsCellUpdate;

@end



NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UICollectionView.h>
#endif
