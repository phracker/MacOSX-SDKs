#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIContentUnavailableButtonProperties.h>)
//
//  UIContentUnavailableButtonProperties.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <UIKit/UIButton.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIButtonConfiguration;
@class UIAction;
@class UIMenu;

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIContentUnavailableButtonProperties : NSObject <NSCopying, NSSecureCoding>

/// The primary action of the button.
@property (nonatomic, copy, nullable) UIAction *primaryAction;

/// An optional menu for the button to display.
@property (nonatomic, copy, nullable) UIMenu *menu;

/// Whether the button is enabled. Default is YES.
@property (nonatomic, getter=isEnabled) BOOL enabled;

/// The role of the button.
@property (nonatomic) UIButtonRole role;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIContentUnavailableButtonProperties.h>
#endif
