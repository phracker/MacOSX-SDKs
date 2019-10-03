#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIToolbar.h>)
//
//  UIToolbar.h
//  UIKit
//
//  Copyright (c) 2006-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIView.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UIApplication.h>
#import <UIKit/UIBarButtonItem.h>
#import <UIKit/UIBarCommon.h>

NS_ASSUME_NONNULL_BEGIN

@class UIBarButtonItem, UIColor, UIToolbarAppearance;
@protocol UIToolbarDelegate;

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(tvos) @interface UIToolbar : UIView <UIBarPositioning>

@property(nonatomic) UIBarStyle barStyle UI_APPEARANCE_SELECTOR API_UNAVAILABLE(tvos); // default is UIBarStyleDefault
@property(nullable, nonatomic, copy) NSArray<UIBarButtonItem *> *items; // get/set visible UIBarButtonItem. default is nil. changes not animated. shown in order

/*
 New behavior on iOS 7.
 Default is YES.
 You may force an opaque background by setting the property to NO.
 If the toolbar has a custom background image, the default is inferred
 from the alpha values of the image—YES if it has any pixel with alpha < 1.0
 If you send setTranslucent:YES to a bar with an opaque custom background image
 it will apply a system opacity less than 1.0 to the image.
 If you send setTranslucent:NO to a bar with a translucent custom background image
 it will provide an opaque background for the image using the bar's barTintColor if defined, or black
 for UIBarStyleBlack or white for UIBarStyleDefault if barTintColor is nil.
 */
@property(nonatomic,assign,getter=isTranslucent) BOOL translucent API_AVAILABLE(ios(3.0)) UI_APPEARANCE_SELECTOR; // Default is NO on iOS 6 and earlier. Always YES if barStyle is set to UIBarStyleBlackTranslucent

- (void)setItems:(nullable NSArray<UIBarButtonItem *> *)items animated:(BOOL)animated;   // will fade in or out or reorder and adjust spacing

/*
 The behavior of tintColor for bars has changed on iOS 7.0. It no longer affects the bar's background
 and behaves as described for the tintColor property added to UIView.
 To tint the bar's background, please use -barTintColor.
 */
@property(null_resettable, nonatomic, strong) UIColor *tintColor;
@property(nullable, nonatomic, strong) UIColor *barTintColor API_AVAILABLE(ios(7.0)) UI_APPEARANCE_SELECTOR;  // default is nil

/* Use these methods to set and access custom background images for toolbars.
      Default is nil. When non-nil the image will be used instead of the system image for toolbars in the
 specified position.
      For the barMetrics argument, UIBarMetricsDefault is the fallback.
 
 DISCUSSION: Interdependence of barStyle, tintColor, backgroundImage.
 When barStyle or tintColor is set as well as the bar's background image,
 the bar buttons (unless otherwise customized) will inherit the underlying
 barStyle or tintColor.
 */
- (void)setBackgroundImage:(nullable UIImage *)backgroundImage forToolbarPosition:(UIBarPosition)topOrBottom barMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;
- (nullable UIImage *)backgroundImageForToolbarPosition:(UIBarPosition)topOrBottom barMetrics:(UIBarMetrics)barMetrics API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;

/* Default is nil. When non-nil, a custom shadow image to show instead of the default shadow image. For a custom shadow to be shown, a custom background image must also be set with -setBackgroundImage:forToolbarPosition:barMetrics: (if the default background image is used, the default shadow image will be used).
 */
- (void)setShadowImage:(nullable UIImage *)shadowImage forToolbarPosition:(UIBarPosition)topOrBottom API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;
- (nullable UIImage *)shadowImageForToolbarPosition:(UIBarPosition)topOrBottom API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;

/// Describes the appearance attributes for the toolbar to use when it is displayed with its standard height.
@property (nonatomic, readwrite, copy) UIToolbarAppearance *standardAppearance UI_APPEARANCE_SELECTOR API_AVAILABLE(ios(13.0));
/// Describes the appearance attributes for the toolbar to use when it is displayed with its compact height. If not set, the standardAppearance will be used instead.
@property (nonatomic, readwrite, copy, nullable) UIToolbarAppearance *compactAppearance UI_APPEARANCE_SELECTOR API_AVAILABLE(ios(13.0));

@property(nullable, nonatomic, weak) id<UIToolbarDelegate> delegate API_AVAILABLE(ios(7.0)); // You may not set the delegate when the toolbar is managed by a UINavigationController.

@end

API_UNAVAILABLE(tvos)
@protocol UIToolbarDelegate <UIBarPositioningDelegate>
@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIToolbar.h>
#endif
