#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIImage.h>)
//
//  UIImage.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#if __has_include(<CoreImage/CoreImage.h>)
#import <CoreImage/CoreImage.h>
#endif
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIColor.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/NSItemProvider+UIKitAdditions.h>
#if __has_include(<UIFoundation/NSTextAttachment.h>)
#import <UIFoundation/NSTextAttachment.h>
#else
#import <UIKit/NSTextAttachment.h>
#endif

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#if __has_include(<UIKit/UITraitCollection.h>)
@class UITraitCollection, UIImageAsset;
#endif

#if __has_include(<UIKit/UIGraphicsImageRenderer.h>)
@class UIGraphicsImageRendererFormat;
#endif

#if __has_include(<UIKit/UIScreen.h>)
@class UIScreen;
#endif

typedef NS_ENUM(NSInteger, UIImageOrientation) {
    UIImageOrientationUp,            // default orientation
    UIImageOrientationDown,          // 180 deg rotation
    UIImageOrientationLeft,          // 90 deg CCW
    UIImageOrientationRight,         // 90 deg CW
    UIImageOrientationUpMirrored,    // as above but image mirrored along other axis. horizontal flip
    UIImageOrientationDownMirrored,  // horizontal flip
    UIImageOrientationLeftMirrored,  // vertical flip
    UIImageOrientationRightMirrored, // vertical flip
} API_AVAILABLE(watchos(2.0));

/* UIImage will implement the resizing mode the fastest way possible while
 retaining the desired visual appearance.
 Note that if an image's resizable area is one point then UIImageResizingModeTile
 is visually indistinguishable from UIImageResizingModeStretch.
 */
typedef NS_ENUM(NSInteger, UIImageResizingMode) {
#if TARGET_ABI_USES_IOS_VALUES
    UIImageResizingModeTile = 0,
    UIImageResizingModeStretch = 1,
#else /* TARGET_ABI_USES_IOS_VALUES */
    UIImageResizingModeStretch = 0,
    UIImageResizingModeTile = 1,
#endif /* TARGET_ABI_USES_IOS_VALUES */
} API_AVAILABLE(watchos(2.0));

/* Images are created with UIImageRenderingModeAutomatic by default. An image with this mode is interpreted as a template image or an original image based on the context in which it is rendered. For example, navigation bars, tab bars, toolbars, and segmented controls automatically treat their foreground images as templates, while image views and web views treat their images as originals. You can use UIImageRenderingModeAlwaysTemplate to force your image to always be rendered as a template or UIImageRenderingModeAlwaysOriginal to force your image to always be rendered as an original.
 */
typedef NS_ENUM(NSInteger, UIImageRenderingMode) {
    UIImageRenderingModeAutomatic,          // Use the default rendering mode for the context where the image is used
    
    UIImageRenderingModeAlwaysOriginal,     // Always draw the original image, without treating it as a template
    UIImageRenderingModeAlwaysTemplate,     // Always draw the image as a template image, ignoring its color information
} API_AVAILABLE(ios(7.0), watchos(2.0));

@class UIImageConfiguration;
@class UIImageSymbolConfiguration;

UIKIT_EXTERN API_AVAILABLE(ios(2.0), watchos(2.0)) NS_SWIFT_SENDABLE
@interface UIImage : NSObject <NSSecureCoding>

/*
 * Retrieve a system-provided image with the specified name.
 * This will only return system-provided images. If you want a custom
 * image as defined in your own catalogs, you should use +imageNamed:.
 *
 * UIKit applications on macOS may pass NSImageName values (defined in
 * <AppKit/NSImage.h>) for the name to access macOS system images.
 *
 * Returns nil if an image with specified name doesn't exist.
 */
+ (nullable UIImage *)systemImageNamed:(NSString *)name API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));
+ (nullable UIImage *)systemImageNamed:(NSString *)name withConfiguration:(nullable UIImageConfiguration *)configuration API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));
#if __has_include(<UIKit/UITraitCollection.h>)
+ (nullable UIImage *)systemImageNamed:(NSString *)name compatibleWithTraitCollection:(nullable UITraitCollection *)traitCollection API_AVAILABLE(ios(13.0),tvos(13.0)) API_UNAVAILABLE(watchos);
#endif
/**
 * Retrieve a system-provided image with the specified name and variable value (between 0 and 1).
 *
 * This will only return system-provided images. If you want a custom image as defined in your own catalogs,
 * you should use @c +imageNamed:inBundle:variableValue:withConfiguration:.
 *
 * Returns @c nil if an image with specified name doesn't exist.
 */
+ (nullable UIImage *)systemImageNamed:(NSString *)name variableValue:(double)value withConfiguration:(nullable UIImageConfiguration *)configuration API_AVAILABLE(ios(16.0), macCatalyst(16.0), tvos(16.0), watchos(9.0));

+ (nullable UIImage *)imageNamed:(NSString *)name;      // load from main bundle
+ (nullable UIImage *)imageNamed:(NSString *)name inBundle:(nullable NSBundle *)bundle withConfiguration:(nullable UIImageConfiguration *)configuration API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));
#if __has_include(<UIKit/UITraitCollection.h>)
+ (nullable UIImage *)imageNamed:(NSString *)name inBundle:(nullable NSBundle *)bundle compatibleWithTraitCollection:(nullable UITraitCollection *)traitCollection API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(watchos);
#endif
/**
 * Retrieve a image with the specified name and variable value (between 0 and 1).
 *
 * This will only return custom images defined in your own catalogs. If you want a system-provided image,
 * you should use @c +systemImageNamed:variableValue:withConfiguration:.
 *
 * Returns @c nil if an image with specified name doesn't exist.
 */
+ (nullable UIImage *)imageNamed:(NSString *)name inBundle:(nullable NSBundle *)bundle variableValue:(double)value withConfiguration:(nullable UIImageConfiguration *)configuration API_AVAILABLE(ios(16.0), macCatalyst(16.0), tvos(16.0), watchos(9.0));

+ (nullable UIImage *)imageWithContentsOfFile:(NSString *)path;
+ (nullable UIImage *)imageWithData:(NSData *)data;
+ (nullable UIImage *)imageWithData:(NSData *)data scale:(CGFloat)scale API_AVAILABLE(ios(6.0), watchos(2.0));
+ (UIImage *)imageWithCGImage:(CGImageRef)cgImage;
+ (UIImage *)imageWithCGImage:(CGImageRef)cgImage scale:(CGFloat)scale orientation:(UIImageOrientation)orientation API_AVAILABLE(ios(4.0), watchos(2.0));
#if __has_include(<CoreImage/CoreImage.h>)
+ (UIImage *)imageWithCIImage:(CIImage *)ciImage API_AVAILABLE(ios(5.0), watchos(2.0));
+ (UIImage *)imageWithCIImage:(CIImage *)ciImage scale:(CGFloat)scale orientation:(UIImageOrientation)orientation API_AVAILABLE(ios(6.0), watchos(2.0));
#endif

- (nullable instancetype)initWithContentsOfFile:(NSString *)path;
- (nullable instancetype)initWithData:(NSData *)data;
- (nullable instancetype)initWithData:(NSData *)data scale:(CGFloat)scale API_AVAILABLE(ios(6.0), watchos(2.0));
- (instancetype)initWithCGImage:(CGImageRef)cgImage;
- (instancetype)initWithCGImage:(CGImageRef)cgImage scale:(CGFloat)scale orientation:(UIImageOrientation)orientation API_AVAILABLE(ios(4.0), watchos(2.0));
#if __has_include(<CoreImage/CoreImage.h>)
- (instancetype)initWithCIImage:(CIImage *)ciImage API_AVAILABLE(ios(5.0), watchos(2.0));
- (instancetype)initWithCIImage:(CIImage *)ciImage scale:(CGFloat)scale orientation:(UIImageOrientation)orientation API_AVAILABLE(ios(6.0), watchos(2.0));
#endif

@property(nonatomic,readonly) CGSize size; // reflects orientation setting. In iOS 4.0 and later, this is measured in points. In 3.x and earlier, measured in pixels
@property(nullable, nonatomic,readonly) CGImageRef CGImage; // returns underlying CGImageRef or nil if CIImage based
- (nullable CGImageRef)CGImage NS_RETURNS_INNER_POINTER CF_RETURNS_NOT_RETAINED;
#if __has_include(<CoreImage/CoreImage.h>)
@property(nullable,nonatomic,readonly) CIImage *CIImage API_AVAILABLE(ios(5.0), watchos(2.0)); // returns underlying CIImage or nil if CGImageRef based
#endif
@property(nonatomic,readonly) UIImageOrientation imageOrientation; // this will affect how the image is composited
@property(nonatomic,readonly) CGFloat scale API_AVAILABLE(ios(4.0), watchos(2.0));

@property(nonatomic,readonly,getter=isSymbolImage) BOOL symbolImage API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));

// animated images. When set as UIImageView.image, animation will play in an infinite loop until removed. Drawing will render the first image

+ (nullable UIImage *)animatedImageNamed:(NSString *)name duration:(NSTimeInterval)duration API_AVAILABLE(ios(5.0), watchos(2.0));  // read sequence of files with suffix starting at 0 or 1
+ (nullable UIImage *)animatedResizableImageNamed:(NSString *)name capInsets:(UIEdgeInsets)capInsets duration:(NSTimeInterval)duration API_AVAILABLE(ios(5.0), watchos(2.0)); // sequence of files
+ (nullable UIImage *)animatedResizableImageNamed:(NSString *)name capInsets:(UIEdgeInsets)capInsets resizingMode:(UIImageResizingMode)resizingMode duration:(NSTimeInterval)duration API_AVAILABLE(ios(6.0), watchos(2.0));
+ (nullable UIImage *)animatedImageWithImages:(NSArray<UIImage *> *)images duration:(NSTimeInterval)duration API_AVAILABLE(ios(5.0), watchos(2.0));

@property(nullable, nonatomic,readonly) NSArray<UIImage *> *images API_AVAILABLE(ios(5.0), watchos(2.0)); // default is nil for non-animated images
@property(nonatomic,readonly) NSTimeInterval duration API_AVAILABLE(ios(5.0), watchos(2.0)); // total duration for all frames. default is 0 for non-animated images

// the these draw the image 'right side up' in the usual coordinate system with 'point' being the top-left.

- (void)drawAtPoint:(CGPoint)point;                                                        // mode = kCGBlendModeNormal, alpha = 1.0
- (void)drawAtPoint:(CGPoint)point blendMode:(CGBlendMode)blendMode alpha:(CGFloat)alpha;
- (void)drawInRect:(CGRect)rect;                                                           // mode = kCGBlendModeNormal, alpha = 1.0
- (void)drawInRect:(CGRect)rect blendMode:(CGBlendMode)blendMode alpha:(CGFloat)alpha;

- (void)drawAsPatternInRect:(CGRect)rect; // draws the image as a CGPattern

- (UIImage *)resizableImageWithCapInsets:(UIEdgeInsets)capInsets API_AVAILABLE(ios(5.0), watchos(2.0)); // create a resizable version of this image. the interior is tiled when drawn.
- (UIImage *)resizableImageWithCapInsets:(UIEdgeInsets)capInsets resizingMode:(UIImageResizingMode)resizingMode API_AVAILABLE(ios(6.0), watchos(2.0)); // the interior is resized according to the resizingMode

@property(nonatomic,readonly) UIEdgeInsets capInsets API_AVAILABLE(ios(5.0), watchos(2.0));   // default is UIEdgeInsetsZero for non resizable images
@property(nonatomic,readonly) UIImageResizingMode resizingMode API_AVAILABLE(ios(6.0), watchos(2.0)); // default is UIImageResizingModeTile

// Support for constraint-based layout (auto layout)
// The alignmentRectInsets of a UIImage are used by UIImageView and other UIView and UIControl
//  subclasses that take custom images to determine the view's alignment rect insets for
//  constraint-based layout.
// The default alignmentRectInsets are UIEdgeInsetsZero.
- (UIImage *)imageWithAlignmentRectInsets:(UIEdgeInsets)alignmentInsets API_AVAILABLE(ios(6.0), watchos(2.0));
@property(nonatomic,readonly) UIEdgeInsets alignmentRectInsets API_AVAILABLE(ios(6.0), watchos(2.0));

// Create a version of this image with the specified rendering mode. By default, images have a rendering mode of UIImageRenderingModeAutomatic.
- (UIImage *)imageWithRenderingMode:(UIImageRenderingMode)renderingMode API_AVAILABLE(ios(7.0), watchos(2.0));
@property(nonatomic, readonly) UIImageRenderingMode renderingMode API_AVAILABLE(ios(7.0), watchos(2.0));

#if __has_include(<UIKit/UIGraphicsImageRenderer.h>)
// Returns an optimal UIGraphicsImageRendererFormat instance for this image, maintaining pixel format and color space.
@property (nonatomic, readonly) UIGraphicsImageRendererFormat *imageRendererFormat API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos);
#endif

#if __has_include(<UIKit/UITraitCollection.h>)
@property (nonatomic, readonly, copy) UITraitCollection *traitCollection API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(watchos); // describes the image in terms of its traits
@property (nullable, nonatomic, readonly) UIImageAsset *imageAsset API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(watchos); // The asset is not encoded along with the image. Returns nil if the image is not CGImage based.
#endif

// Creates a version of this image that, when assigned to a UIImageView’s image property, draws its underlying image contents horizontally mirrored when running under a right-to-left language. Affects the flipsForRightToLeftLayoutDirection property; does not affect the imageOrientation property.
// This method cannot be used to create a left-to-right version of a right-to-left source image, and will be deprecated in a future release. New code should instead use -imageWithHorizontallyFlippedOrientation to construct a UIImageAsset.
- (UIImage *)imageFlippedForRightToLeftLayoutDirection API_AVAILABLE(ios(9.0), watchos(2.0));
@property (nonatomic, readonly) BOOL flipsForRightToLeftLayoutDirection API_AVAILABLE(ios(9.0), watchos(2.0));

// Creates a version of this image with an imageOrientation property that is horizontally mirrored from this image’s. Does not affect the flipsForRightToLeftLayoutDirection property.
- (UIImage *)imageWithHorizontallyFlippedOrientation API_AVAILABLE(ios(10.0), watchos(3.0));

/*
 * The baseline offset is expressed in points from the bottom of the image (positive = up, negative = down).
 * If the image doesn't have a defined baseline, this value will be 0, but you can
 * use -hasBaseline to see if it actually has one defined (because it is perfectly possible to have
 * a baseline with the value of 0).
 */
@property (nonatomic, readonly) CGFloat baselineOffsetFromBottom API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0)) NS_REFINED_FOR_SWIFT;
@property (nonatomic, readonly) BOOL hasBaseline API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0)) NS_REFINED_FOR_SWIFT;
- (UIImage *)imageWithBaselineOffsetFromBottom:(CGFloat)baselineOffset API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));
- (UIImage *)imageWithoutBaseline API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));

/*
 * Configuration support
 * ---------------------
 * This describes the configuration of the image.
 * Depending on which type of image, the configuration might be different.
 * Symbol images will always have a UIImageSymbolConfiguration, even if you give it another
 * type of configuration (it will merge the trait info from the other configuration into
 * its current configuration).
 * Images start off with an unspecified configuration but can be modified by the methods below.
 * The preferred ways of adding configurations for displaying images is to specify them on
 * the image view, but it is possible to modify images with a more specific configuration.
 */
@property (nullable, nonatomic, copy, readonly) __kindof UIImageConfiguration *configuration API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));

/*
 * Create a new image by replacing the existing configuration with a new one.
 * For symbol images this will always result in an image with a UIImageSymbolConfiguration,
 * even if you give it another type of configuration (the trait info from the new configuration
 * will be merged into the current symbol configuration resulting in anew symbol configuration).
 * For non-symbol images, this will replace the configuration of the image with a new one.
 *
 * Important note! Given (for example):
 *
 *    image = image(named:"the_image").withRenderingMode(.alwaysTemplate)

 * the following two statements aren't exactly equivalent:
 *
 *    a = image.imageAsset.withConfiguration(configuration)
 *    b = image.withConfiguration(configuration)
 *
 * The first one will resolve the image again from the asset catalog (if it is originating from one),
 * resulting in a fresh image without any modifications. In other words, `a` won't have the
 * rendering mode change set anymore, and it will be "reverted" to `.automatic`.
 * The second one will resolve the image, but apply and changes that were made to the image.
 * That means that `b` might be a different image, but it will still have the same rendering mode
 * as `image`.
 */
- (UIImage *)imageWithConfiguration:(UIImageConfiguration *)configuration API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));

/*
 * Symbol configuration support
 * ----------------------------
 * This describes the symbol configuration of a symbol image.
 * Symbol images start off with an unspecified configuration but can be modified by using
 * `image.withConfiguration(:)`.
 *
 * However... the preferred ways of adding configurations for displaying images is to specify
 * them on the image view using `preferredSymbolConfiguration`, but it is possible to modify
 * images with a more specific configuration. This include image related traits, for example
 * you can use this to fix a symbol image to a dynamic type style at a fixed preferred content size
 * category.
 */
@property (nullable, nonatomic, copy, readonly) UIImageSymbolConfiguration *symbolConfiguration API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));

/*
 * This is a convenience method to apply another symbol configuration over an existing one.
 * If the image doesn't have a symbol configuration, it will just merge the traits of the existing
 * with the new one (where the new traits override the old traits).
 *
 * Create a new image by applying the specified configuration over the existing one.
 * This only works if the configuration already has a configuration (i.e. is a symbol image).
 * The image will be configured with a combination of both configurations.
 *
 * If you use this on a symbol image with other layout modifications done (e.g. changed baseline),
 * those changes will be lost and overwritten with the new configuration's layout properties.
 * This applies to size, contentInsets and baseline.
 */
- (nullable UIImage *)imageByApplyingSymbolConfiguration:(UIImageSymbolConfiguration *)configuration API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));


- (UIImage *)imageWithTintColor:(UIColor *)color API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));
- (UIImage *)imageWithTintColor:(UIColor *)color renderingMode:(UIImageRenderingMode)renderingMode API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));

#if __has_include(<UIKit/UIScreen.h>)

/// Decodes an image synchronously and provides a new one for display in views and animations.
/// 
/// @return A new version of the image object for display. If the system can’t decode the image, this method returns `nil`.
///
/// @note The prepared `UIImage` is not related to the original image. If the properties of the screen (such as its resolution or color gamut) change, or if the image is displayed on a different screen that the one it was prepared for, it may not render correctly.
- (nullable UIImage *)imageByPreparingForDisplay API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

/// Decodes an image asynchronously and provides a new one for display in views and animations.
///
/// The completion handler will be invoked on a private queue. Be sure to return to the main queue before assigning the prepared image to an image view.
///
/// @param completionHandler A block to invoke with the prepared image. If preparation failed (for example, because the image data is corrupt), @c image will be `nil`.
///
/// @note The prepared `UIImage` is not related to the original image. If the properties of the screen (such as its resolution or color gamut) change, or if the image is displayed on a different screen that the one it was prepared for, it may not render correctly.
- (void)prepareForDisplayWithCompletionHandler:(void (^)(UIImage *_Nullable))completionHandler NS_SWIFT_ASYNC_NAME(byPreparingForDisplay()) API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

- (nullable UIImage *)imageByPreparingThumbnailOfSize:(CGSize)size API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

- (void)prepareThumbnailOfSize:(CGSize)size completionHandler:(void (^)(UIImage *_Nullable))completionHandler NS_SWIFT_ASYNC_NAME(byPreparingThumbnail(ofSize:)) API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

#endif

/// Indicates that this image is tagged for display of high dynamic range content.
@property(nonatomic, assign, readonly) BOOL isHighDynamicRange API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0));

/// Returns a new image that will render within the standard range.
- (UIImage *)imageRestrictedToStandardDynamicRange API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0));

@end

@interface UIImage (PreconfiguredSystemImages)

@property (class, readonly, strong) UIImage *actionsImage API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));
@property (class, readonly, strong) UIImage *addImage API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));
@property (class, readonly, strong) UIImage *removeImage API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));
@property (class, readonly, strong) UIImage *checkmarkImage API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));
@property (class, readonly, strong) UIImage *strokedCheckmarkImage API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));

@end


#if TARGET_OS_IOS
@interface UIImage (NSItemProvider) <NSItemProviderReading, NSItemProviderWriting, UIItemProviderPresentationSizeProviding>
#else
@interface UIImage (NSItemProvider) <NSItemProviderReading, NSItemProviderWriting>
#endif

@end

#if UIKIT_HAS_UIFOUNDATION_SYMBOLS
@interface NSTextAttachment (UIImage)

+ (NSTextAttachment *)textAttachmentWithImage:(UIImage *)image API_AVAILABLE(ios(13.0),tvos(13.0)) API_UNAVAILABLE(watchos);

@end
#endif


@interface UIImage(UIImageDeprecated)

// use resizableImageWithCapInsets: and capInsets.

- (UIImage *)stretchableImageWithLeftCapWidth:(NSInteger)leftCapWidth topCapHeight:(NSInteger)topCapHeight API_UNAVAILABLE(tvos);
@property(nonatomic,readonly) NSInteger leftCapWidth API_UNAVAILABLE(tvos);   // default is 0. if non-zero, horiz. stretchable. right cap is calculated as width - leftCapWidth - 1
@property(nonatomic,readonly) NSInteger topCapHeight API_UNAVAILABLE(tvos);   // default is 0. if non-zero, vert. stretchable. bottom cap is calculated as height - topCapWidth - 1

@end


#if __has_include(<CoreImage/CoreImage.h>)
@interface CIImage(UIKitAdditions)

- (nullable instancetype)initWithImage:(UIImage *)image API_AVAILABLE(ios(5.0), watchos(2.0));
- (nullable instancetype)initWithImage:(UIImage *)image options:(nullable NSDictionary<CIImageOption, id> *)options API_AVAILABLE(ios(5.0), watchos(2.0));

@end
#endif

/// return image as PNG. May return nil if image has no CGImageRef or invalid bitmap format
UIKIT_EXTERN NSData * __nullable UIImagePNGRepresentation(UIImage * __nonnull image) NS_SWIFT_NAME(UIImage.pngData(self:)) API_AVAILABLE(watchos(2.0));
/// return image as JPEG. May return nil if image has no CGImageRef or invalid bitmap format. compression is 0(most)..1(least)
UIKIT_EXTERN NSData * __nullable UIImageJPEGRepresentation(UIImage * __nonnull image, CGFloat compressionQuality) NS_SWIFT_NAME(UIImage.jpegData(self:compressionQuality:)) API_AVAILABLE(watchos(2.0));
/// Returns HEIC data representing the image, or nil if such a representation could not be generated. HEIC is recommended for efficiently storing all kinds of images, including those with high dynamic range content.
UIKIT_EXTERN NSData * __nullable UIImageHEICRepresentation(UIImage * __nonnull image) API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0)) NS_SWIFT_NAME(UIImage.heicData(self:));

NS_HEADER_AUDIT_END(nullability, sendability)


#else
#import <UIKitCore/UIImage.h>
#endif
