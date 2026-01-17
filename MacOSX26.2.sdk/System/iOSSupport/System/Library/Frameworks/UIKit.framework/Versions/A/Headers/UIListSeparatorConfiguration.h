#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIListSeparatorConfiguration.h>)
//
//  UIListSeparatorConfiguration.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIColor.h>
#import <UIKit/UICollectionLayoutList.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIVisualEffect;

typedef NS_ENUM(NSInteger, UIListSeparatorVisibility) {
    /// UICollectionView list sections will resolve this to an appropriate value.
    UIListSeparatorVisibilityAutomatic,
    UIListSeparatorVisibilityVisible,
    UIListSeparatorVisibilityHidden
} API_UNAVAILABLE(watchos);

/// Use the values from the edges in this constant to indicate to the consumer of a UIListSeparatorConfiguration that the value for that
/// edge should be replaced with an appropriate inset.
UIKIT_EXTERN const NSDirectionalEdgeInsets UIListSeparatorAutomaticInsets API_AVAILABLE(ios(14.5)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);

/// This configuration allows for fine grained control of separator appearance in a UICollectionView List section.
/// @see UICollectionLayoutListConfiguration.separatorConfiguration
UIKIT_EXTERN API_AVAILABLE(ios(14.5)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos) NS_SWIFT_UI_ACTOR
@interface UIListSeparatorConfiguration : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Initializes a list separator configuration with the appropriate defaults for the passed in list appearance.
/// @param listAppearance The appearance of the list consuming this separator configuration
- (instancetype)initWithListAppearance:(UICollectionLayoutListAppearance)listAppearance NS_DESIGNATED_INITIALIZER;

/// The visibility of the top separator for the item that this configuration is applied to.
@property (nonatomic) UIListSeparatorVisibility topSeparatorVisibility;

/// The visibility of the bottom separator for the item that this configuration is applied to.
@property (nonatomic) UIListSeparatorVisibility bottomSeparatorVisibility;

/// Insets to apply to the top separator of the item that this configuration is applied to. Defaults to UIListSeparatorAutomaticInsets.
@property (nonatomic) NSDirectionalEdgeInsets topSeparatorInsets;

/// Insets to apply to the bottom separator of the item that this configuration is applied to. Defaults to UIListSeparatorAutomaticInsets.
@property (nonatomic) NSDirectionalEdgeInsets bottomSeparatorInsets;

/// The color to use for the separators for the item this configuration is applied to.
@property (nonatomic, strong) UIColor *color;

/// The color to use for the separators for the item this configuration is applied to, when the item is in a multiple selection group.
@property (nonatomic, strong) UIColor *multipleSelectionColor;

/// The visual effect to use for the separators of the item this configuration is applied to.
@property (nonatomic, copy, nullable) UIVisualEffect *visualEffect API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIListSeparatorConfiguration.h>
#endif
