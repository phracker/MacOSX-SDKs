#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIColor.h>)
//
//  UIColor.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#if __has_include(<CoreImage/CoreImage.h>)
#import <CoreImage/CoreImage.h>
#endif


NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIImage;
@class UITraitCollection;

// A type indicating the prominence of a color.
typedef NS_ENUM(NSInteger, UIColorProminence) {
    UIColorProminencePrimary,
    UIColorProminenceSecondary,
    UIColorProminenceTertiary,
    UIColorProminenceQuaternary,
} NS_SWIFT_NAME(UIColor.Prominence) API_AVAILABLE(visionos(2.0), ios(18.0), tvos(18.0)) API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(2.0), watchos(2.0)) NS_SWIFT_SENDABLE
@interface UIColor : NSObject <NSSecureCoding, NSCopying>

// Convenience methods for creating colors
+ (UIColor *)colorWithWhite:(CGFloat)white alpha:(CGFloat)alpha;
+ (UIColor *)colorWithHue:(CGFloat)hue saturation:(CGFloat)saturation brightness:(CGFloat)brightness alpha:(CGFloat)alpha;
+ (UIColor *)colorWithRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha;
+ (UIColor *)colorWithDisplayP3Red:(CGFloat)displayP3Red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha API_AVAILABLE(ios(10.0), watchos(3.0));
+ (UIColor *)colorWithCGColor:(CGColorRef)cgColor;
+ (UIColor *)colorWithPatternImage:(UIImage *)image;
#if __has_include(<CoreImage/CoreImage.h>)
+ (UIColor *)colorWithCIColor:(CIColor *)ciColor API_AVAILABLE(ios(5.0), watchos(2.0));
#endif

// Initializers for creating colors
- (UIColor *)initWithWhite:(CGFloat)white alpha:(CGFloat)alpha;
- (UIColor *)initWithHue:(CGFloat)hue saturation:(CGFloat)saturation brightness:(CGFloat)brightness alpha:(CGFloat)alpha;
- (UIColor *)initWithRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha;
- (UIColor *)initWithDisplayP3Red:(CGFloat)displayP3Red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha API_AVAILABLE(ios(10.0), watchos(3.0));
- (UIColor *)initWithCGColor:(CGColorRef)cgColor;
- (UIColor *)initWithPatternImage:(UIImage*)image;
#if __has_include(<CoreImage/CoreImage.h>)
- (UIColor *)initWithCIColor:(CIColor *)ciColor API_AVAILABLE(ios(5.0), watchos(2.0));
#endif

/// Generates an HDR color by applying an exposure to the SDR color defined by the red, green, and blue components. The `red`, `green`, and `blue` components have a nominal range of [0..1], `exposure` is a value >= 0. To produce an HDR color, we process the given color in a linear color space, multiplying component values by `2^exposure`. The produced color will have a `contentHeadroom` equal to the linearized exposure value. Each whole value of exposure produces a color that is twice as bright.
- (UIColor *)initWithRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha exposure:(CGFloat)exposure API_AVAILABLE(ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));
+ (UIColor *)colorWithRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha exposure:(CGFloat)exposure API_AVAILABLE(ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// Generates an HDR color by applying an exposure to the SDR color defined by the red, green, and blue components. The `red`, `green`, and `blue` components have a nominal range of [0..1], `linearExposure` is a value >= 1. To produce an HDR color, we process the given color in a linear color space, multiplying component values by `linearExposure `. The produced color will have a `contentHeadroom` equal to `linearExposure`. Each doubling of `linearExposure` produces a color that is twice as bright.
- (UIColor *)initWithRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha linearExposure:(CGFloat)linearExposure API_AVAILABLE(ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));
+ (UIColor *)colorWithRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha linearExposure:(CGFloat)linearExposure API_AVAILABLE(ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// Reinterpret the color by applying a new `contentHeadroom` without changing the color components. Changing the `contentHeadroom` redefines the color relative to a different peak white, changing its behavior under tone mapping and the result of calling `standardDynamicRangeColor`. The new color will have a `contentHeadroom` >= 1.0.
- (UIColor *)colorByApplyingContentHeadroom:(CGFloat)contentHeadroom API_AVAILABLE(ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0)) NS_SWIFT_NAME(applyingContentHeadroom(_:));

// Some convenience methods to create colors.  These colors will be as calibrated as possible.
// These colors are cached.
@property(class, nonatomic, readonly) UIColor *blackColor;      // 0.0 white
@property(class, nonatomic, readonly) UIColor *darkGrayColor;   // 0.333 white
@property(class, nonatomic, readonly) UIColor *lightGrayColor;  // 0.667 white
@property(class, nonatomic, readonly) UIColor *whiteColor;      // 1.0 white
@property(class, nonatomic, readonly) UIColor *grayColor;       // 0.5 white
@property(class, nonatomic, readonly) UIColor *redColor;        // 1.0, 0.0, 0.0 RGB
@property(class, nonatomic, readonly) UIColor *greenColor;      // 0.0, 1.0, 0.0 RGB
@property(class, nonatomic, readonly) UIColor *blueColor;       // 0.0, 0.0, 1.0 RGB
@property(class, nonatomic, readonly) UIColor *cyanColor;       // 0.0, 1.0, 1.0 RGB
@property(class, nonatomic, readonly) UIColor *yellowColor;     // 1.0, 1.0, 0.0 RGB
@property(class, nonatomic, readonly) UIColor *magentaColor;    // 1.0, 0.0, 1.0 RGB
@property(class, nonatomic, readonly) UIColor *orangeColor;     // 1.0, 0.5, 0.0 RGB
@property(class, nonatomic, readonly) UIColor *purpleColor;     // 0.5, 0.0, 0.5 RGB
@property(class, nonatomic, readonly) UIColor *brownColor;      // 0.6, 0.4, 0.2 RGB
@property(class, nonatomic, readonly) UIColor *clearColor;      // 0.0 white, 0.0 alpha

// Set the color: Sets the fill and stroke colors in the current drawing context. Should be implemented by subclassers.
- (void)set;

// Set the fill or stroke colors individually. These should be implemented by subclassers.
- (void)setFill;
- (void)setStroke;

// Convenience methods for getting components.
// If the receiver is of a compatible color space, any non-NULL parameters are populated and 'YES' is returned. Otherwise, the parameters are left unchanged and 'NO' is returned.
- (BOOL)getWhite:(nullable CGFloat *)white alpha:(nullable CGFloat *)alpha API_AVAILABLE(ios(5.0), watchos(2.0));
- (BOOL)getHue:(nullable CGFloat *)hue saturation:(nullable CGFloat *)saturation brightness:(nullable CGFloat *)brightness alpha:(nullable CGFloat *)alpha API_AVAILABLE(ios(5.0), watchos(2.0));
- (BOOL)getRed:(nullable CGFloat *)red green:(nullable CGFloat *)green blue:(nullable CGFloat *)blue alpha:(nullable CGFloat *)alpha API_AVAILABLE(ios(5.0), watchos(2.0));

// Returns a color in the same color space as the receiver with the specified alpha component.
- (UIColor *)colorWithAlphaComponent:(CGFloat)alpha;

// Access the underlying CGColor or CIColor.
@property(nonatomic,readonly) CGColorRef CGColor;
- (CGColorRef)CGColor NS_RETURNS_INNER_POINTER CF_RETURNS_NOT_RETAINED;
#if __has_include(<CoreImage/CoreImage.h>)
@property(nonatomic,readonly) CIColor   *CIColor API_AVAILABLE(ios(5.0), watchos(2.0));
#endif

/// The linear brightness multiplier that was applied when generating this color. Colors created with an exposure by UIColor create CGColors that are tagged with a contentHeadroom value. While CGColors created without a contentHeadroom tag will return 0 from CGColorGetHeadroom, UIColors generated in a similar fashion return a linearExposure of 1.0.
@property (nonatomic, readonly, assign) CGFloat linearExposure API_AVAILABLE(ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// In some cases it is useful to recover the color that was base SDR color that was exposed to generate the given HDR color. If a color's `linearExposure` is >1, then this will return the base SDR color.
@property (nonatomic, readonly, copy) UIColor *standardDynamicRangeColor API_AVAILABLE(ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

@end


@interface UIColor (UINSItemProvider) <NSItemProviderReading, NSItemProviderWriting>

@end


#if __has_include(<CoreImage/CoreImage.h>)
@interface CIColor(UIKitAdditions)

- (instancetype)initWithColor:(UIColor *)color API_AVAILABLE(ios(5.0), watchos(2.0));

@end
#endif

@interface UIColor (UIColorNamedColors)
+ (nullable UIColor *)colorNamed:(NSString *)name API_AVAILABLE(ios(11.0), watchos(4.0));      // load from main bundle
+ (nullable UIColor *)colorNamed:(NSString *)name inBundle:(nullable NSBundle *)bundle compatibleWithTraitCollection:(nullable UITraitCollection *)traitCollection API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos);
@end

@interface UIColor (DynamicColors)

/* Create a dynamic color with a provider.
 * When methods are called on this color that need color component values,
 * the provider is called with UITraitCollection.currentTraitCollection.
 * The provider should use that trait collection to decide a more fundamental UIColor to return.
 * As much as possible, use the given trait collection to make that decision, not other state.
 */

+ (UIColor *)colorWithDynamicProvider:(UIColor * (^)(UITraitCollection *traitCollection))dynamicProvider API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);
- (UIColor *)initWithDynamicProvider:(UIColor * (^)(UITraitCollection *traitCollection))dynamicProvider API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

/* Resolve any color to its most fundamental form (a non-dynamic color) for a specific trait collection.
 */
- (UIColor *)resolvedColorWithTraitCollection:(UITraitCollection *)traitCollection API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

@end

@interface UIColor (ProminenceSupport)

// Returns a color as the receiver with the specified prominence.
- (UIColor *)colorWithProminence:(UIColorProminence)prominence API_AVAILABLE(visionos(2.0), ios(18.0), tvos(18.0)) API_UNAVAILABLE(watchos);

@property(nonatomic, readonly) UIColorProminence prominence API_AVAILABLE(visionos(2.0), ios(18.0), tvos(18.0)) API_UNAVAILABLE(watchos);
@end


NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIColor.h>
#endif
