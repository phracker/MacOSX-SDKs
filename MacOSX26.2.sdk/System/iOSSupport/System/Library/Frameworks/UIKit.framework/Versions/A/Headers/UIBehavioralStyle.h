#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIBehavioralStyle.h>)
//
//  UIBehavioralStyle.h
//  UIKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <UIKit/UISlider.h>
#import <UIKit/UIButton.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(watchos, tvos)
/// Behavioral Styles are values that determine how a class — such as a view or control — behaves. This includes how the control is drawn, and what behaviors it supports. For example, handling certain customizations in one style, but not another.
typedef NS_ENUM(NSUInteger, UIBehavioralStyle) {
    /// The system will choose the most appropriate style for the targetted platform.
    UIBehavioralStyleAutomatic = 0,

    /// A style and set of behaviors best for iOS/iPadOS applications
    UIBehavioralStylePad,

    /// A style and set of behaviors best for macOS applications
    UIBehavioralStyleMac,
} API_UNAVAILABLE(watchos);

API_AVAILABLE(ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(watchos, tvos)
@interface UIButton (UIBehavioralStyle)

/// The button's behavioral style. This property always returns a concrete, resolved style (never UIBehavioralStyleAutomatic).
@property (nonatomic, readonly) UIBehavioralStyle behavioralStyle API_AVAILABLE(ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(watchos, tvos);

/// Request a style for the button. If the style changed, the button will redraw and its metrics may change.
@property (nonatomic) UIBehavioralStyle preferredBehavioralStyle API_AVAILABLE(ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(watchos, tvos);

@end

API_AVAILABLE(ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(watchos, tvos)
@interface UISlider (UIBehavioralStyle)

/// The slider's behavioral style. This property always returns a concrete, resolved style (never UIBehavioralStyleAutomatic).
@property (nonatomic, readonly) UIBehavioralStyle behavioralStyle API_AVAILABLE(ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(watchos, tvos);

/// Request a style for the slider. If the style changes, the slider will redraw and its metrics may change.
@property (nonatomic) UIBehavioralStyle preferredBehavioralStyle API_AVAILABLE(ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIBehavioralStyle.h>
#endif
