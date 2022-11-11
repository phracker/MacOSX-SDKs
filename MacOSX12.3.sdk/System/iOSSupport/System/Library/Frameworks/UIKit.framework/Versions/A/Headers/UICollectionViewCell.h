#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UICollectionViewCell.h>)
//
//  UICollectionViewCell.h
//  UIKit
//
//  Copyright (c) 2011-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UICollectionView.h>

NS_ASSUME_NONNULL_BEGIN

@class UICollectionViewLayout;
@class UICollectionView;
@class UICollectionViewLayoutAttributes;
@class UILongPressGestureRecognizer;
@class UICellConfigurationState;
@class UIBackgroundConfiguration;
@protocol UIContentConfiguration;
@class UICollectionViewCell;

typedef NS_ENUM(NSInteger, UICollectionViewCellDragState) {
    UICollectionViewCellDragStateNone,
    /* The cell is in the "lifting" state.
     */
    UICollectionViewCellDragStateLifting,
    
    /* A cell in the "dragging" state is left behind with a
     * "ghosted" appearance to denote where the drag
     * started from.
     */
    UICollectionViewCellDragStateDragging
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

UIKIT_EXTERN API_AVAILABLE(ios(6.0)) NS_SWIFT_UI_ACTOR
@interface UICollectionReusableView : UIView

@property (nonatomic, readonly, copy, nullable) NSString *reuseIdentifier;

// Override point.
// Called by the collection view before the instance is returned from the reuse queue.
// Subclassers must call super.
- (void)prepareForReuse NS_REQUIRES_SUPER;

// Classes that want to support custom layout attributes specific to a given UICollectionViewLayout subclass can apply them here.
// This allows the view to work in conjunction with a layout class that returns a custom subclass of UICollectionViewLayoutAttributes from -layoutAttributesForItem: or the corresponding layoutAttributesForHeader/Footer methods.
// -applyLayoutAttributes: is then called after the view is added to the collection view and just before the view is returned from the reuse queue.
// Note that -applyLayoutAttributes: is only called when attributes change, as defined by -isEqual:.
- (void)applyLayoutAttributes:(UICollectionViewLayoutAttributes *)layoutAttributes;

// Override these methods to provide custom UI for specific layouts.
- (void)willTransitionFromLayout:(UICollectionViewLayout *)oldLayout toLayout:(UICollectionViewLayout *)newLayout;
- (void)didTransitionFromLayout:(UICollectionViewLayout *)oldLayout toLayout:(UICollectionViewLayout *)newLayout;

- (UICollectionViewLayoutAttributes *)preferredLayoutAttributesFittingAttributes:(UICollectionViewLayoutAttributes *)layoutAttributes API_AVAILABLE(ios(8.0));

@end


typedef void (^UICollectionViewCellConfigurationUpdateHandler)(__kindof UICollectionViewCell *cell, UICellConfigurationState *state) API_AVAILABLE(ios(15.0), tvos(15.0), watchos(8.0));

UIKIT_EXTERN API_AVAILABLE(ios(6.0)) NS_SWIFT_UI_ACTOR
@interface UICollectionViewCell : UICollectionReusableView

/// Returns the current configuration state for the cell.
/// To add your own custom state(s), override the getter and call super to obtain an instance with the
/// system properties set, then set your own custom states as desired.
@property (nonatomic, readonly) UICellConfigurationState *configurationState API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

/// Requests the cell update its configuration for its current state. This method is called automatically
/// when the cell's `configurationState` may have changed, as well as in other circumstances where an
/// update may be required. Multiple requests may be coalesced into a single update at the appropriate time.
- (void)setNeedsUpdateConfiguration API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

/// Subclasses should override this method and update the cell's configuration using the state provided.
/// This method should not be called directly, use `setNeedsUpdateConfiguration` to request an update.
- (void)updateConfigurationUsingState:(UICellConfigurationState *)state API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));
/// Optional block-based alternative to overriding `-updateConfigurationUsingState:` in a subclass. This handler
/// is called after `-updateConfigurationUsingState:`. Setting a new handler triggers `setNeedsUpdateConfiguration`.
@property (nonatomic, copy, nullable) UICollectionViewCellConfigurationUpdateHandler configurationUpdateHandler API_AVAILABLE(ios(15.0), tvos(15.0), watchos(8.0));

/// Setting a content configuration replaces the existing contentView of the cell with a new content view instance from the configuration,
/// or directly applies the configuration to the existing content view if the configuration is compatible with the existing content view type.
/// The default value is nil. After a configuration has been set, setting this property to nil will replace the current content view with a new content view.
@property (nonatomic, copy, nullable) id<UIContentConfiguration> contentConfiguration API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));
/// When YES, the cell will automatically call -updatedConfigurationForState: on its `contentConfiguration` when the cell's
/// configuration state changes, and apply the updated configuration back to the cell. The default value is YES.
@property (nonatomic) BOOL automaticallyUpdatesContentConfiguration API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

@property (nonatomic, readonly) UIView *contentView; // add custom subviews to the cell's contentView

// Cells become highlighted when the user touches them.
// The selected state is toggled when the user lifts up from a highlighted cell.
// Override these methods to provide custom UI for a selected or highlighted state.
// The collection view may call the setters inside an animation block.
@property (nonatomic, getter=isSelected) BOOL selected;
@property (nonatomic, getter=isHighlighted) BOOL highlighted;

// Override this method to modify the visual appearance for a particular
// dragState.
//
// Call super if you want to add to the existing default implementation.
//
- (void)dragStateDidChange:(UICollectionViewCellDragState)dragState API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos);

/// Setting a background configuration supersedes the cell's backgroundView and selectedBackgroundView. The default value is nil.
@property (nonatomic, copy, nullable) UIBackgroundConfiguration *backgroundConfiguration API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));
/// When YES, the cell will automatically call -updatedConfigurationForState: on its `backgroundConfiguration` when the cell's
/// configuration state changes, and apply the updated configuration back to the cell. The default value is YES.
@property (nonatomic) BOOL automaticallyUpdatesBackgroundConfiguration API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

// These properties are always nil when a non-nil `backgroundConfiguration` is set.
// The background view is a subview behind all other views.
// If selectedBackgroundView is different than backgroundView, it will be placed above the background view and animated in on selection.
@property (nonatomic, strong, nullable) UIView *backgroundView;
@property (nonatomic, strong, nullable) UIView *selectedBackgroundView;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UICollectionViewCell.h>
#endif
