#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITableViewHeaderFooterView.h>)
//
//  UITableViewHeaderFooterView.h
//  UIKit
//
//  Copyright (c) 2008-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UITableView.h>

NS_ASSUME_NONNULL_BEGIN

@class UIViewConfigurationState;
@class UIBackgroundConfiguration;
@protocol UIContentConfiguration;
@class UIListContentConfiguration;

UIKIT_EXTERN API_AVAILABLE(ios(6.0))
@interface UITableViewHeaderFooterView : UIView

- (instancetype)initWithReuseIdentifier:(nullable NSString *)reuseIdentifier NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// Returns the current configuration state for the header/footer.
/// To add your own custom state(s), override the getter and call super to obtain an instance with the
/// system properties set, then set your own custom states as desired.
@property (nonatomic, readonly) UIViewConfigurationState *configurationState API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

/// Requests the view update its configuration for its current state. This method is called automatically
/// when the view's `configurationState` may have changed, as well as in other circumstances where an
/// update may be required. Multiple requests may be coalesced into a single update at the appropriate time.
- (void)setNeedsUpdateConfiguration API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

/// Subclasses should override this method and update the view's configuration using the state provided.
/// This method should not be called directly, use `setNeedsUpdateConfiguration` to request an update.
- (void)updateConfigurationUsingState:(UIViewConfigurationState *)state API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

/// Returns a default list content configuration for the header/footer view's style.
- (UIListContentConfiguration *)defaultContentConfiguration API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

/// Setting a content configuration replaces the existing contentView of the header/footer with a new content view instance from the configuration,
/// or directly applies the configuration to the existing content view if the configuration is compatible with the existing content view type.
/// The default value is nil. After a configuration has been set, setting this property to nil will replace the current content view with a new content view.
@property (nonatomic, copy, nullable) id<UIContentConfiguration> contentConfiguration API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));
/// When YES, the header/footer will automatically call -updatedConfigurationForState: on its `contentConfiguration` when the header/footer's
/// configuration state changes, and apply the updated configuration back to the header/footer. The default value is YES.
@property (nonatomic) BOOL automaticallyUpdatesContentConfiguration API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

@property (nonatomic, readonly, strong) UIView *contentView;

// These properties will always return nil when a non-nil `contentConfiguration` is set.
@property (nonatomic, readonly, strong, nullable) UILabel *textLabel API_DEPRECATED("Use UIListContentConfiguration instead, this property will be deprecated in a future release.", ios(6.0, API_TO_BE_DEPRECATED));
@property (nonatomic, readonly, strong, nullable) UILabel *detailTextLabel API_DEPRECATED("Use UIListContentConfiguration instead, this property will be deprecated in a future release.", ios(6.0, API_TO_BE_DEPRECATED)); // only supported for headers in grouped style

/// Setting a background configuration supersedes the header/footer's backgroundView. The default value is nil.
@property (nonatomic, copy, nullable) UIBackgroundConfiguration *backgroundConfiguration API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));
/// When YES, the header/footer will automatically call -updatedConfigurationForState: on its `backgroundConfiguration` when the header/footer's
/// configuration state changes, and apply the updated configuration back to the header/footer. The default value is YES.
@property (nonatomic) BOOL automaticallyUpdatesBackgroundConfiguration API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

// This property is always nil when a non-nil `backgroundConfiguration` is set.
@property (nonatomic, strong, nullable) UIView *backgroundView;

@property (nonatomic, readonly, copy, nullable) NSString *reuseIdentifier;

- (void)prepareForReuse NS_REQUIRES_SUPER;  // if the view is reusable (has a reuse identifier), this is called just before the view is returned from the table view method dequeueReusableHeaderFooterViewWithIdentifier:.  If you override, you MUST call super.

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UITableViewHeaderFooterView.h>
#endif
