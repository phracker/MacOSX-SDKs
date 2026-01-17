#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIBlurEffect.h>)
//
//  UIBlurEffect.h
//  UIKit
//
//  Copyright © 2016-2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIVisualEffect.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UIBlurEffectStyle) {
    /* Traditional blur styles.
     */
    UIBlurEffectStyleExtraLight,
    UIBlurEffectStyleLight,
    UIBlurEffectStyleDark,
    UIBlurEffectStyleExtraDark API_AVAILABLE(tvos(10.0)) API_UNAVAILABLE(ios) API_UNAVAILABLE(watchos),

    /* Styles which automatically show one of the traditional blur styles,
     * depending on the user interface style.
     *
     * Regular displays either Light or Dark.
     */
    UIBlurEffectStyleRegular API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos),
    /* Prominent displays either ExtraLight, Dark (on iOS), or ExtraDark (on tvOS).
     */
    UIBlurEffectStyleProminent API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos),

    /*
     * Blur styles available in iOS 13.
     *
     * Styles which automatically adapt to the user interface style:
     */
    UIBlurEffectStyleSystemUltraThinMaterial        API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos),
    UIBlurEffectStyleSystemThinMaterial             API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos),
    UIBlurEffectStyleSystemMaterial                 API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos),
    UIBlurEffectStyleSystemThickMaterial            API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos),
    UIBlurEffectStyleSystemChromeMaterial           API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos),

    /* And always-light and always-dark versions:
     */
    UIBlurEffectStyleSystemUltraThinMaterialLight   API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos),
    UIBlurEffectStyleSystemThinMaterialLight        API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos),
    UIBlurEffectStyleSystemMaterialLight            API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos),
    UIBlurEffectStyleSystemThickMaterialLight       API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos),
    UIBlurEffectStyleSystemChromeMaterialLight      API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos),

    UIBlurEffectStyleSystemUltraThinMaterialDark    API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos),
    UIBlurEffectStyleSystemThinMaterialDark         API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos),
    UIBlurEffectStyleSystemMaterialDark             API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos),
    UIBlurEffectStyleSystemThickMaterialDark        API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos),
    UIBlurEffectStyleSystemChromeMaterialDark       API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos)

} API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(watchos);

/* UIBlurEffect will provide a blur that appears to have been applied to the content layered behind the UIVisualEffectView. Views added to the contentView of a blur visual effect are not blurred themselves. */
UIKIT_EXTERN API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIBlurEffect : UIVisualEffect

+ (UIBlurEffect *)effectWithStyle:(UIBlurEffectStyle)style;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIBlurEffect.h>
#endif
