#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UINavigationBarAppearance.h>)
//
//  UINavigationBarAppearance.h
//  UIKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIBarAppearance.h>
#import <UIKit/UIBarButtonItemAppearance.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) NS_SWIFT_UI_ACTOR
@interface UINavigationBarAppearance : UIBarAppearance

/// Inline Title text attributes. If the font or color are unspecified, appropriate defaults are supplied.
@property (nonatomic, readwrite, copy) NSDictionary<NSAttributedStringKey, id> *titleTextAttributes;
/// An additional adjustment to the inline title's position.
@property (nonatomic, readwrite, assign) UIOffset titlePositionAdjustment;

/// Large Title text attributes. If the font or color are unspecified, appropriate defaults are supplied.
@property (nonatomic, readwrite, copy) NSDictionary<NSAttributedStringKey, id> *largeTitleTextAttributes;

/// The appearance for plain-style bar button items
@property (nonatomic, readwrite, copy) UIBarButtonItemAppearance *buttonAppearance;

/// The appearance for done-style bar button items
@property (nonatomic, readwrite, copy) UIBarButtonItemAppearance *doneButtonAppearance;

/// The appearance for back buttons. Defaults are drawn from buttonAppearance when appropriate.
@property (nonatomic, readwrite, copy) UIBarButtonItemAppearance *backButtonAppearance;

/// The image shown on the leading edge of the back button.
@property (nonatomic, readonly, strong) UIImage *backIndicatorImage;
/// This image is used to mask content flowing underneath the backIndicatorImage during push & pop transitions
@property (nonatomic, readonly, strong) UIImage *backIndicatorTransitionMaskImage;
/// Set the backIndicatorImage & backIndicatorTransitionMaskImage images. If either image is nil, then both images will be reset to their default.
- (void)setBackIndicatorImage:(nullable UIImage *)backIndicatorImage transitionMaskImage:(nullable UIImage *)backIndicatorTransitionMaskImage;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UINavigationBarAppearance.h>
#endif
