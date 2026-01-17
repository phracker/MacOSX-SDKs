#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIContentConfiguration.h>)
//
//  UIContentConfiguration.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@protocol UIConfigurationState;
@class UIView;
@class UITraitCollection;
@protocol UIContentView;

API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIContentConfiguration <NSObject, NSCopying>

/// Initializes and returns a new instance of the content view using this configuration.
- (__kindof UIView<UIContentView> *)makeContentView;

/// Returns a copy of the configuration updated for the specified state, by applying the configuration's default values for that state to any properties that have not been customized.
- (instancetype)updatedConfigurationForState:(id<UIConfigurationState>)state;

@end


API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIContentView <NSObject>

/// Returns the current configuration of the view. Setting this property applies the new configuration to the view.
@property (nonatomic, copy) id<UIContentConfiguration> configuration;

@optional

/// Whether this view is compatible with the provided configuration, meaning the view supports
/// it being set to the `configuration` property and is capable of updating itself for the
/// configuration. If not implemented, the view is assumed to be compatible with configuration
/// classes that match the class of the view's existing configuration.
- (BOOL)supportsConfiguration:(id<UIContentConfiguration>)configuration API_AVAILABLE(ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIContentConfiguration.h>
#endif
