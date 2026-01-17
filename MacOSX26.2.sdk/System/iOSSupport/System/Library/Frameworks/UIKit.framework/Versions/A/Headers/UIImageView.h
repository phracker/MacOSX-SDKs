#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIImageView.h>)
//
//  UIImageView.h
//  UIKit
//
//  Copyright (c) 2006-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UISymbolEffectCompletion.h>

#import <Symbols/NSSymbolEffect.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIImage, UIImageSymbolConfiguration;

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIImageView : UIView 

- (instancetype)initWithImage:(nullable UIImage *)image;
- (instancetype)initWithImage:(nullable UIImage *)image highlightedImage:(nullable UIImage *)highlightedImage API_AVAILABLE(ios(3.0));

@property (nullable, nonatomic, strong) UIImage *image; // default is nil
@property (nullable, nonatomic, strong) UIImage *highlightedImage API_AVAILABLE(ios(3.0)); // default is nil
@property (nullable, nonatomic, strong) UIImageSymbolConfiguration* preferredSymbolConfiguration API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, getter=isUserInteractionEnabled) BOOL userInteractionEnabled; // default is NO

@property (nonatomic, getter=isHighlighted) BOOL highlighted API_AVAILABLE(ios(3.0)); // default is NO

// these allow a set of images to be animated. the array may contain multiple copies of the same

@property (nullable, nonatomic, copy) NSArray<UIImage *> *animationImages; // The array must contain UIImages. Setting hides the single image. default is nil
@property (nullable, nonatomic, copy) NSArray<UIImage *> *highlightedAnimationImages API_AVAILABLE(ios(3.0)); // The array must contain UIImages. Setting hides the single image. default is nil

@property (nonatomic) NSTimeInterval animationDuration;         // for one cycle of images. default is number of images * 1/30th of a second (i.e. 30 fps)
@property (nonatomic) NSInteger      animationRepeatCount;      // 0 means infinite (default is 0)

// When tintColor is non-nil, any template images set on the image view will be colorized with that color.
// The tintColor is inherited through the superview hierarchy. See UIView for more information.
@property (null_resettable, nonatomic, strong) UIColor *tintColor API_AVAILABLE(ios(7.0));

- (void)startAnimating;
- (void)stopAnimating;
@property(nonatomic, readonly, getter=isAnimating) BOOL animating;

/// The preferred treatment to use for HDR images. By default the image view will defer to the value from its traitCollection.
@property (nonatomic, readwrite, assign) UIImageDynamicRange preferredImageDynamicRange API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// The resolved treatment to use for HDR images.
@property (nonatomic, readonly , assign) UIImageDynamicRange imageDynamicRange API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

// if YES, the UIImageView will display a focused appearance when any of its immediate or distant superviews become focused
@property (nonatomic) BOOL adjustsImageWhenAncestorFocused UIKIT_AVAILABLE_TVOS_ONLY(9_0);

// if adjustsImageWhenAncestorFocused is set, the image view may display its image in a larger frame when focused.
// this layout guide can be used to align other elements with the image view's focused frame.
@property(readonly,strong) UILayoutGuide *focusedFrameGuide UIKIT_AVAILABLE_TVOS_ONLY(9_0);

// the overlayContentView will be placed above the image, automatically resized to fill the image view's frame, and created if necessary when this property is accessed.
// You may add your own subviews to this view.
// By default, the overlayContentView will clip its children to the image view's frame. Set the overlayContentView's clipsToBounds property to false to allow views to draw outside of the image.
// On tvOS, if adjustsImageWhenAncestorFocused is true, the overlayContentView will receive the same floating effects as the image when focused.
@property (nonatomic, strong, readonly) UIView *overlayContentView UIKIT_AVAILABLE_TVOS_ONLY(11_0);

// if YES, the UIImageView's focused appearance will support transparency in the image.
// For example, the shadow will be based on the alpha channel of the image; the highlight will be masked to the image's alpha channel, etc.
// This property is only supported for single-layer images, not images will multiple layers like LCRs.
// Additionally, the image view must have the same aspect ratio as its image for this property to be effective.
// Supporting transparency affects performance, so only set this when needed.
@property (nonatomic) BOOL masksFocusEffectToContents UIKIT_AVAILABLE_TVOS_ONLY(11_0);

@end

@interface UIImageView (/*Symbol animation presets*/)

/// Adds a symbol effect to the image view with default options and animation.
- (void)addSymbolEffect:(NSSymbolEffect *)symbolEffect API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// Adds a symbol effect to the image view with specified options and default animation.
- (void)addSymbolEffect:(NSSymbolEffect *)symbolEffect options:(NSSymbolEffectOptions *)options API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// Adds a symbol effect to the image view with specified options and animation.
- (void)addSymbolEffect:(NSSymbolEffect *)symbolEffect options:(NSSymbolEffectOptions *)options animated:(BOOL)animated API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// Adds a symbol effect to the image view with specified options, animation, and completion handler.
- (void)addSymbolEffect:(NSSymbolEffect *)symbolEffect options:(NSSymbolEffectOptions *)options animated:(BOOL)animated completion:(nullable UISymbolEffectCompletion)completionHandler API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// Removes from the image view the symbol effect matching the type of effect passed in, with default options and animation.
- (void)removeSymbolEffectOfType:(NSSymbolEffect *)symbolEffect API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// Removes from the image view the symbol effect matching the type of effect passed in, with specified options and default animation.
- (void)removeSymbolEffectOfType:(NSSymbolEffect *)symbolEffect options:(NSSymbolEffectOptions *)options API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// Removes from the image view the symbol effect matching the type of effect passed in, with specified options and animation.
- (void)removeSymbolEffectOfType:(NSSymbolEffect *)symbolEffect options:(NSSymbolEffectOptions *)options animated:(BOOL)animated API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// Removes from the image view the symbol effect matching the type of effect passed in, with specified options, animation, and completion handler.
- (void)removeSymbolEffectOfType:(NSSymbolEffect *)symbolEffect options:(NSSymbolEffectOptions *)options animated:(BOOL)animated completion:(nullable UISymbolEffectCompletion)completionHandler API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// Removes all symbol effects from the image view with default options and animation.
- (void)removeAllSymbolEffects API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// Removes all symbol effects from the image view with specified options and default animation.
- (void)removeAllSymbolEffectsWithOptions:(NSSymbolEffectOptions *)options API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// Removes all symbol effects from the image view with specified options and animation.
- (void)removeAllSymbolEffectsWithOptions:(NSSymbolEffectOptions *)options animated:(BOOL)animated API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// Sets the symbol image on the image view with a symbol content transition and default options.
/// Passing in a non-symbol image will result in undefined behavior.
- (void)setSymbolImage:(UIImage *)symbolImage withContentTransition:(NSSymbolContentTransition *)transition API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// Sets the symbol image on the image view with a symbol content transition and specified options.
/// Passing in a non-symbol image will result in undefined behavior.
- (void)setSymbolImage:(UIImage *)symbolImage withContentTransition:(NSSymbolContentTransition *)transition options:(NSSymbolEffectOptions *)options API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// Sets the symbol image on the image view with a symbol content transition, options, and completion handler.
/// Passing in a non-symbol image will result in undefined behavior.
- (void)setSymbolImage:(UIImage *)symbolImage withContentTransition:(NSSymbolContentTransition *)transition options:(NSSymbolEffectOptions *)options completion:(nullable UISymbolEffectCompletion)completionHandler API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIImageView.h>
#endif
