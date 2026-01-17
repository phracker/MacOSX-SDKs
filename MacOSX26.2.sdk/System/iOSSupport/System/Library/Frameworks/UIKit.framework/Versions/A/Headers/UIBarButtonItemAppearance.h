#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIBarButtonItemAppearance.h>)
//
//  UIBarButtonItemAppearance.h
//  UIKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIBarButtonItem.h>

@class UIImage;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIBarButtonItemStateAppearance : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Text attributes to be used for rendering title text. If the font or color are unspecified, appropriate defaults are supplied.
@property (nonatomic, readwrite, copy) NSDictionary<NSAttributedStringKey, id> *titleTextAttributes;

/// An offset to apply to the button's title position
@property (nonatomic, readwrite, assign) UIOffset titlePositionAdjustment;

/// A background image to display around the button
@property (nonatomic, readwrite, strong, nullable) UIImage *backgroundImage;

/// An offset to apply to the backgroundImage.
@property (nonatomic, readwrite, assign) UIOffset backgroundImagePositionAdjustment;

@end

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIBarButtonItemAppearance : NSObject<NSCopying, NSSecureCoding>

/// Construct an appearance for the UIBarButtonItemStylePlain style.
- (instancetype)init;

/// Construct an appearance with default values for the given style.
- (instancetype)initWithStyle:(UIBarButtonItemStyle)style NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (instancetype)copy;

/// Reset this appearance to that of a given style.
- (void)configureWithDefaultForStyle:(UIBarButtonItemStyle)style;

/// The appearance when the bar button item is in the normal control state.
@property (nonatomic, readonly, strong) UIBarButtonItemStateAppearance *normal;

/// The appearance when the bar button item is in the highlighted control state. If unspecified, then synthesized from the normal state.
@property (nonatomic, readonly, strong) UIBarButtonItemStateAppearance *highlighted;

/// The appearance when the bar button item is in the disabled control state. If unspecified, then synthesized from the normal state.
@property (nonatomic, readonly, strong) UIBarButtonItemStateAppearance *disabled;

/// The appearance when the bar button item is in the focused control state. If unspecified, then synthesized from the highlighted state.
@property (nonatomic, readonly, strong) UIBarButtonItemStateAppearance *focused;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIBarButtonItemAppearance.h>
#endif
