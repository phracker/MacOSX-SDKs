#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIToolbarAppearance.h>)
//
//  UIToolbarAppearance.h
//  UIKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIBarAppearance.h>
#import <UIKit/UIBarButtonItemAppearance.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIToolbarAppearance : UIBarAppearance

/// The appearance for plain-style bar button items
@property (nonatomic, readwrite, copy) UIBarButtonItemAppearance *buttonAppearance;

/// The appearance attributes for Prominent buttons.
///
/// Use this property to configure the appearance of bar button items that use `UIBarButtonItemStyleProminent`.
/// If the navigation bar doesn't have any buttons using this style, this property has no effect.
@property (nonatomic, readwrite, copy) UIBarButtonItemAppearance *prominentButtonAppearance API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos);

/// The appearance for done-style bar button items
@property (nonatomic, readwrite, copy) UIBarButtonItemAppearance *doneButtonAppearance API_DEPRECATED_WITH_REPLACEMENT("prominentButtonAppearance", ios(13.0, 26.0), tvos(13.0, 26.0)) API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIToolbarAppearance.h>
#endif
