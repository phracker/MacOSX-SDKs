//
//  ASAuthorizationAppleIDButton.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>

typedef NS_ENUM(NSInteger, ASAuthorizationAppleIDButtonType) {
    ASAuthorizationAppleIDButtonTypeSignIn,
    ASAuthorizationAppleIDButtonTypeContinue,

    ASAuthorizationAppleIDButtonTypeSignUp API_AVAILABLE(ios(13.2), macos(10.15.1), tvos(13.1)) API_UNAVAILABLE(watchos),

    ASAuthorizationAppleIDButtonTypeDefault = ASAuthorizationAppleIDButtonTypeSignIn,
} NS_SWIFT_NAME(ASAuthorizationAppleIDButton.ButtonType) API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);


typedef NS_ENUM(NSInteger, ASAuthorizationAppleIDButtonStyle) {
    ASAuthorizationAppleIDButtonStyleWhite,
    ASAuthorizationAppleIDButtonStyleWhiteOutline,
    ASAuthorizationAppleIDButtonStyleBlack,
} NS_SWIFT_NAME(ASAuthorizationAppleIDButton.Style) API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);


NS_ASSUME_NONNULL_BEGIN

#if TARGET_OS_IPHONE
AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos)
@interface ASAuthorizationAppleIDButton : UIControl
#else
AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos)
@interface ASAuthorizationAppleIDButton : NSControl <NSAccessibilityButton>
#endif

+ (instancetype)buttonWithType:(ASAuthorizationAppleIDButtonType)type style:(ASAuthorizationAppleIDButtonStyle)style;

- (instancetype)initWithAuthorizationButtonType:(ASAuthorizationAppleIDButtonType)type authorizationButtonStyle:(ASAuthorizationAppleIDButtonStyle)style NS_DESIGNATED_INITIALIZER;

/*! @abstract Set a custom corner radius to be used by this button.
 */
@property (nonatomic, assign) IBInspectable CGFloat cornerRadius API_UNAVAILABLE(tvos);

@end

NS_ASSUME_NONNULL_END
