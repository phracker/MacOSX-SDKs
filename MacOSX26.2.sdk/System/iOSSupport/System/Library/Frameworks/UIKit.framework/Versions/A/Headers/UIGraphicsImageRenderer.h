#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIGraphicsImageRenderer.h>)
//
//  UIGraphicsImageRenderer.h
//  UIKit
//
//  Copyright (c) 2016-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIGraphicsRenderer.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIImage.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIGraphicsImageRendererContext;

typedef void (^UIGraphicsImageDrawingActions)(UIGraphicsImageRendererContext *rendererContext) API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIGraphicsImageRendererFormatRange) {
    UIGraphicsImageRendererFormatRangeUnspecified = -1,
    UIGraphicsImageRendererFormatRangeAutomatic = 0,
    UIGraphicsImageRendererFormatRangeExtended,
    UIGraphicsImageRendererFormatRangeStandard
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos)
@interface UIGraphicsImageRendererFormat : UIGraphicsRendererFormat

@property (nonatomic) CGFloat scale; // display scale of the context. The preferredFormat uses the scale most appropriate for the main screen's current configuration.
@property (nonatomic) BOOL opaque; // indicates the bitmap context will draw fully opaque. The preferredFormat sets this to NO.
@property (nonatomic) BOOL prefersExtendedRange API_DEPRECATED("Use the preferredRange property instead", ios(10.0, 12.0)) API_UNAVAILABLE(visionos, watchos); // indicates the bitmap context should draw into a context capable of rendering extended color images. The preferredFormat sets this according to the main screen's current configuration.
@property (nonatomic, readonly, assign) BOOL supportsHighDynamicRange API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos); /// indicates if the format supports high dynamic range rendering.

@property (nonatomic) UIGraphicsImageRendererFormatRange preferredRange API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos);

// Returns a format optimized for the specified trait collection, taking into account properties such as displayScale and displayGamut.
// Traits that are not specified will be ignored, with their corresponding format properties defaulting to the values in preferredFormat.
+ (instancetype)formatForTraitCollection:(UITraitCollection *)traitCollection API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos);
@end

UIKIT_EXTERN API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos)
@interface UIGraphicsImageRendererContext : UIGraphicsRendererContext
@property (nonatomic, readonly) UIImage *currentImage; // Returns a UIImage representing the current state of the renderer's CGContext
@end

UIKIT_EXTERN API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos)
@interface UIGraphicsImageRenderer : UIGraphicsRenderer
- (instancetype)initWithSize:(CGSize)size;
- (instancetype)initWithSize:(CGSize)size format:(UIGraphicsImageRendererFormat *)format NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithBounds:(CGRect)bounds format:(UIGraphicsImageRendererFormat *)format NS_DESIGNATED_INITIALIZER;

// Returns a UIImage rendered with the contents of the CGContext after the imageRenderBlock executes.
// If the options provided to the renderer contain a rect with a zero width or height size, this will return an empty UIImage.
- (UIImage *)imageWithActions:(NS_NOESCAPE UIGraphicsImageDrawingActions)actions;

// These return compressed image data with the contents of the image drawn in the renderer block.
- (NSData *)PNGDataWithActions:(NS_NOESCAPE UIGraphicsImageDrawingActions)actions;
- (NSData *)JPEGDataWithCompressionQuality:(CGFloat)compressionQuality actions:(NS_NOESCAPE UIGraphicsImageDrawingActions)actions;
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIGraphicsImageRenderer.h>
#endif
