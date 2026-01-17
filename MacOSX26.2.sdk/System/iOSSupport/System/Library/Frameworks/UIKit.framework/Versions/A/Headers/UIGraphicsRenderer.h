#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIGraphicsRenderer.h>)
//
//  UIGraphicsRenderer.h
//  UIKit
//
//  Copyright (c) 2016-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>


NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*
 UIGraphicsRendererFormat is an object that describes the particular properties of the
 context created by its associated renderer class.
 */
UIKIT_EXTERN API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos)
@interface UIGraphicsRendererFormat : NSObject <NSCopying>

// returns a default configured format object, best suited for the current device.
+ (instancetype)defaultFormat API_AVAILABLE(ios(10.0)) API_DEPRECATED_WITH_REPLACEMENT("preferredFormat", tvos(10.0, 11.0)) API_UNAVAILABLE(watchos);

// Returns a new format object best suited for the main screen’s current configuration.
+ (instancetype)preferredFormat API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

// returns the bounds for drawing into the owning UIGraphicsRendererContext.
@property (nonatomic, readonly) CGRect bounds;
@end

/*
 A UIGraphicsRendererContext provides primitive drawing routines not provided through other
 UIKit classes (UIImage, UIBezierPath, etc) in addition to providing access to the underlying
 CGContextRef.
 */
UIKIT_EXTERN API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos)
@interface UIGraphicsRendererContext : NSObject
@property (nonatomic, readonly) CGContextRef CGContext;
@property (nonatomic, readonly) __kindof UIGraphicsRendererFormat *format;

- (void)fillRect:(CGRect)rect;
- (void)fillRect:(CGRect)rect blendMode:(CGBlendMode)blendMode;

- (void)strokeRect:(CGRect)rect;
- (void)strokeRect:(CGRect)rect blendMode:(CGBlendMode)blendMode;

- (void)clipToRect:(CGRect)rect;
@end

/*
 An abstract base class for creating graphics renderers. Do not use this class directly.
 */
UIKIT_EXTERN API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos)
@interface UIGraphicsRenderer : NSObject
// Creates a new UIGraphicsRenderer instance with the provides bounds and format, or a defaultFormat if none is provided.
// The format instance is copied by the initializer, and the provided instance may be immediately reused
// for creating other renderer instances with the same or different bounds.
- (instancetype)initWithBounds:(CGRect)bounds;
- (instancetype)initWithBounds:(CGRect)bounds format:(UIGraphicsRendererFormat *)format NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly) __kindof UIGraphicsRendererFormat *format; // The renderer format used to create this renderer instance. returned by copy.
@property (nonatomic, readonly) BOOL allowsImageOutput; // If YES, this renderer may be used to generate CGImageRefs.
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIGraphicsRenderer.h>
#endif
