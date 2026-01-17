#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIBarButtonItemBadge.h>)
//
//  UIBarButtonItemBadge.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN NS_SWIFT_UI_ACTOR NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos)
API_UNAVAILABLE(watchos, tvos)
/// A badge to be rendered on a bar button item.
@interface UIBarButtonItemBadge : NSObject <NSCopying, NSSecureCoding>
/// Creates a badge with the specified `count`.
/// 
/// The count is localized when shown, and will update
/// when the app’s locale changes.
+ (instancetype)badgeWithCount:(NSUInteger)count NS_SWIFT_NAME(badgeWithCount(_:));

/// Creates a badge with the specified `string`.
+ (instancetype)badgeWithString:(NSString *)stringValue NS_SWIFT_NAME(badgeWithString(_:));

/// Creates a badge that's empty, and just renders the badge background
/// with no content.
+ (instancetype)indicatorBadge;

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, copy, nullable) NSString *stringValue;

/// The badge's background color. A `nil` value will be treated as an indication to use the system default.
@property (nonatomic, strong, nullable) UIColor *backgroundColor;

/// The badge's foreground color. A `nil` value will be treated as an indication to use the system default.
@property (nonatomic, strong, nullable) UIColor *foregroundColor;

/// The font to use for the badge. A `nil` value will be treated as an indication to use the system default.
@property (nonatomic, strong, nullable) UIFont *font;

@end

@interface UIBarButtonItem (Badging)
/// Sets a badge on the bar button item. Currently only supported in navigation bars.
@property (nonatomic, readwrite, nullable, strong) UIBarButtonItemBadge *badge NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos, watchos);
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIBarButtonItemBadge.h>
#endif
