#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIColorWell.h>)
//
//  UIColorWell.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIControl.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UIColorWell : UIControl

/// Title for the color picker.
///
/// Should explain what kind of color to pick. Example values are "Stroke Color" or "Fill Color".
@property (nullable, nonatomic, copy) NSString *title;

/// Controls whether alpha is supported or not.
///
/// If set to `NO` users are only able to pick fully opaque colors.
@property (nonatomic) BOOL supportsAlpha;

/// Sets the selected color on the color picker and is updated when the user changes the selection.
/// Does support KVO and does send `UIControlEventValueChanged`.
@property (nullable, nonatomic, strong) UIColor *selectedColor;

/// If set to `NO` the eyedropper functionality is not supported for this color well.
@property (nonatomic) BOOL supportsEyedropper API_AVAILABLE(ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// The maximum exposure to apply to a color when returned by the color well.
@property (nonatomic) CGFloat maximumLinearExposure API_AVAILABLE(ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIColorWell.h>
#endif
