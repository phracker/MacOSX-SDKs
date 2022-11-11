#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIVibrancyEffect.h>)
//
//  UIVibrancyEffect.h
//  UIKit
//
//  Copyright © 2016-2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIVisualEffect.h>
#import <UIKit/UIKitDefines.h>

@class UIBlurEffect;

NS_ASSUME_NONNULL_BEGIN

/* UIVibrancyEffect amplifies and adjusts the color of content layered behind the view, allowing content placed inside the contentView to become more vivid. It is intended to be placed over, or as a subview of, a UIVisualEffectView that has been configured with a UIBlurEffect. This effect only affects content added to the contentView. Because the vibrancy effect is color dependent, subviews added to the contentView need to be tintColorDidChange aware and must be prepared to update themselves accordingly. UIImageView will need its image to have a rendering mode of UIImageRenderingModeAlwaysTemplate to receive the proper effect.
 */
UIKIT_EXTERN API_AVAILABLE(ios(8.0)) NS_SWIFT_UI_ACTOR
@interface UIVibrancyEffect : UIVisualEffect

+ (UIVibrancyEffect *)effectForBlurEffect:(UIBlurEffect *)blurEffect;

@end


/* Additional vibrancy styles available in iOS 13, intended for use with the "system material" UIBlurEffect styles.
 *
 * These vibrancy styles, combined with those blur effect styles, cause only the alpha component of the content
 * to be used. Color information is ignored. (UIVibrancyEffectStyleLabel is an exception; it passes color through.)
 */
typedef NS_ENUM(NSInteger, UIVibrancyEffectStyle) {
    /* Vibrancy for text labels.
     */
    UIVibrancyEffectStyleLabel,
    UIVibrancyEffectStyleSecondaryLabel,
    UIVibrancyEffectStyleTertiaryLabel,
    UIVibrancyEffectStyleQuaternaryLabel,

    /* Vibrancy for thicker filled areas.
     */
    UIVibrancyEffectStyleFill,
    UIVibrancyEffectStyleSecondaryFill,
    UIVibrancyEffectStyleTertiaryFill,

    /* Vibrancy for separator lines.
     */
    UIVibrancyEffectStyleSeparator,

} API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);

@interface UIVibrancyEffect (AdditionalStyles)

+ (UIVibrancyEffect *)effectForBlurEffect:(UIBlurEffect *)blurEffect style:(UIVibrancyEffectStyle)style API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIVibrancyEffect.h>
#endif
