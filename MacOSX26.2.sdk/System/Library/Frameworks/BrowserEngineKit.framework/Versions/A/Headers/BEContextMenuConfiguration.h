//
//  BEContextMenuConfiguration.h
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <BrowserEngineKit/BEMacros.h>

#if BROWSERENGINEKIT_HAS_UIVIEW
#import <UIKit/UIContextMenuConfiguration.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/**
 *  A specialized `UIContextMenuConfiguration` object to defer a context menu presentation when the
 *  when the context menu gestures are first recognized and a possible menu presentation is not immediately known.
 */
BROWSERENGINE_EXTERN API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface BEContextMenuConfiguration : UIContextMenuConfiguration

/// Fulfills the configuration with a concrete configuration. Once fulfilled, the context menu presentation will begin.
/// You should call this method as soon as you have determined that a menu presentation is possible for the configuration, as to
/// minimize the delay between the context menu gesture's recognition and the menu's presentation. If no menu presentation is possible,
/// fulfill with a `nil` configuration.
///
/// There is a system-defined timeout before the configuration is cancelled, where no menu presents. This method returns `YES` if the
/// configuration did successfully prepare, and `NO` otherwise.
///
/// @NOTE: The fulfilled configuration is used by `UIContextMenuInteractionDelegate` when referencing any `UIContextMenuConfiguration`,
/// rather than this object.
- (BOOL)fulfillUsingConfiguration:(nullable UIContextMenuConfiguration *)configuration;

/// Creates a new configuration for the context menu interaction.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// For a concrete configuration, use the parent `UIContextMenuConfiguration` class instead.
+ (instancetype)configurationWithIdentifier:(nullable id<NSCopying>)identifier
                            previewProvider:(nullable UIContextMenuContentPreviewProvider)previewProvider
                             actionProvider:(nullable UIContextMenuActionProvider)actionProvider NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#endif // BROWSERENGINEKIT_HAS_UIVIEW
