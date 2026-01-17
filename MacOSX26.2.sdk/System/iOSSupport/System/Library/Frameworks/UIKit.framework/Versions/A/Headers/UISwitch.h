#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISwitch.h>)
//
//  UISwitch.h
//  UIKit
//
//  Copyright (c) 2008-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UISwitchStyle) {
    UISwitchStyleAutomatic = 0,  // The style most appropriate to the current UIUserInterfaceIdiom
    UISwitchStyleCheckbox,       // The AppKit-style checkbox — only supported for Catalyst in the Mac idiom
    UISwitchStyleSliding         // The on/off sliding style switch — classic iOS appearance.
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, watchos);

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UISwitch : UIControl <NSCoding>

@property(nullable, nonatomic, strong) UIColor *onTintColor API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;
@property(nullable, nonatomic, strong) UIColor *thumbTintColor API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;

@property(nullable, nonatomic, strong) UIImage *onImage API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;
@property(nullable, nonatomic, strong) UIImage *offImage API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;

/// The title displayed alongside the switch, positioned appropriately for the @c UIUserInterfaceIdiom.
/// @note This property is only supported for Catalyst in the Mac idiom.
@property(nullable, nonatomic, copy) NSString *title API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, watchos);

/// The switch's display style. This property always returns a concrete, resolved style (never UISwitchStyleAutomatic).
@property(nonatomic, readonly) UISwitchStyle style API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, watchos);

/// Request a style for the switch. If the style changed, then the switch may resize.
@property(nonatomic) UISwitchStyle preferredStyle API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, watchos);

@property(nonatomic,getter=isOn) BOOL on;

- (instancetype)initWithFrame:(CGRect)frame NS_DESIGNATED_INITIALIZER;      // This class enforces a size appropriate for the control, and so the frame size is ignored.

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (void)setOn:(BOOL)on animated:(BOOL)animated; // does not send action

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISwitch.h>
#endif
