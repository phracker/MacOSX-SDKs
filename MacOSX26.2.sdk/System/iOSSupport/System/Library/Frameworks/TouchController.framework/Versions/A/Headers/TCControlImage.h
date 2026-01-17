//
//  TCControlImage.h
//  TouchController
//

#if !TARGET_OS_OSX
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Metal/Metal.h>

@class UIImage;

NS_ASSUME_NONNULL_BEGIN

/// Represents an image to be rendered using Metal.
__attribute__((visibility ("default")))
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos)
@interface TCControlImage : NSObject

/// Not available. Use designated initializer.
- (instancetype)init NS_UNAVAILABLE;

/// Creates a new image with the specified texture and size.
///
/// - Parameters:
///   - texture: The Metal texture to use for the image.
///   - size: The size of the image in points.
/// - Returns: A new `TCControlImage` instance.
- (instancetype)initWithTexture:(id<MTLTexture>)texture size:(CGSize)size;

/// Creates a new image with the specified texture, size, highlight texture, offset, and color tint.
///
/// - Parameters:
///   - texture: The Metal texture to use for the image.
///   - size: The size of the image in points.
///   - highlightTexture: The Metal texture to use for the image when highlighted. May be `nil`.
///   - offset: The offset from the center of the parent control in points.
///   - tintColor: The color tint to apply to the texture. The color ref is retained.
/// - Returns: A new `TCControlImage` instance.
- (instancetype)initWithTexture:(id<MTLTexture>)texture size:(CGSize)size highlightTexture:(id<MTLTexture> __nullable)highlightTexture offset:(CGPoint)offset tintColor:(CGColorRef)tintColor NS_DESIGNATED_INITIALIZER;

/// Creates a new image from a CGImage.
///
/// - Parameters:
///   - cgImage: The Core Graphics image to create the texture from.
///   - size: The size of the image in points.
///   - device: The Metal device used to create the texture.
/// - Returns: A new `TCControlImage` instance, or `nil` if texture creation fails.
- (nullable instancetype)initWithCGImage:(CGImageRef)cgImage size:(CGSize)size device:(id<MTLDevice>)device;

/// Creates a new image from a UIImage.
///
/// - Parameters:
///   - uiImage: The UIKit image to create the texture from.
///   - size: The size of the image in points.
///   - device: The Metal device used to create the texture.
/// - Returns: A new `TCControlImage` instance, or `nil` if the UIImage has no backing CGImage
///            or if texture creation fails.
- (nullable instancetype)initWithUIImage:(UIImage *)uiImage size:(CGSize)size device:(id<MTLDevice>)device;


/// The Metal texture to use for the image.
@property (nonatomic, strong) id<MTLTexture> texture;
/// The Metal texture to use for the image when highlighted. May be `nil`.
@property (nonatomic, strong, nullable) id<MTLTexture> highlightTexture;
/// The size of the image in points.
@property (nonatomic, assign) CGSize size;
/// The offset from the center of the parent control in points.
@property (nonatomic, assign) CGPoint offset;
/// The color tint to apply to the texture. The color ref is retained.
@property (nonatomic, assign) CGColorRef tintColor;

@end


NS_ASSUME_NONNULL_END
#endif
