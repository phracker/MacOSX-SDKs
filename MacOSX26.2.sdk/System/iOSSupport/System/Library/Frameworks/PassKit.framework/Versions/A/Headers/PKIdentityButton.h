#if !__has_include(<PassKitUI/PKIdentityButton.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKIdentityButton.h
//    PassKit
//
//  Copyright © 2022 Apple, Inc. All rights reserved.
//

#ifndef __PKIDENTITYBUTTON_H
#define __PKIDENTITYBUTTON_H

#import <TargetConditionals.h>

#if TARGET_OS_IOS

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/// Denotes the visual style of the PKIdentityButton
typedef NS_ENUM(NSInteger, PKIdentityButtonStyle) {
    PKIdentityButtonStyleBlack = 0,
    PKIdentityButtonStyleBlackOutline
} NS_SWIFT_NAME(PKIdentityButton.Style) API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, watchos, tvos);

/// Denotes the label displayed on a PKIdentityButton
typedef NS_ENUM(NSInteger, PKIdentityButtonLabel) {
    /// Button with text "Verify Identity with Apple Wallet"
    PKIdentityButtonLabelVerifyIdentity = 0,

    /// Button with text "Verify with Apple Wallet"
    PKIdentityButtonLabelVerify,

    /// Button with text "Verify Age with Apple Wallet"
    PKIdentityButtonLabelVerifyAge,

    /// Button with text "Continue with Apple Wallet"
    PKIdentityButtonLabelContinue,
} NS_SWIFT_NAME(PKIdentityButton.Label) API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, watchos, tvos);

/// Button to show to the user to trigger the identity verification flow via PKIdentityAuthorizationController.
/// This class should not be subclassed.
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface PKIdentityButton : UIControl

+ (instancetype)buttonWithLabel:(PKIdentityButtonLabel)label style:(PKIdentityButtonStyle)style;

- (instancetype)initWithLabel:(PKIdentityButtonLabel)label style:(PKIdentityButtonStyle)style NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithFrame:(CGRect)frame NS_UNAVAILABLE;
- (instancetype)initWithFrame:(CGRect)frame primaryAction:(nullable UIAction *)primaryAction NS_UNAVAILABLE;

@property (nonatomic, assign) CGFloat cornerRadius;

@end

NS_ASSUME_NONNULL_END

#endif // TARGET_OS_IOS

#endif // __PKIDENTITYBUTTON_H

#else
#if !TARGET_OS_OSX 
#import <TargetConditionals.h>
#import <PassKitUI/PKIdentityButton.h>
#endif
#endif