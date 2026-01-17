//
//  MTLFXSpatialScaler.h
//  MetalFX
//
//  Copyright (c) 2021-2022 Apple Inc. All rights reserved.
//

#import <Metal/Metal.h>
#import <Metal/MTL4Compiler.h>
// Forward declaration of Metal4FX scaler.
@protocol MTL4FXTemporalScaler;

// Forward declaration.
@protocol MTL4FXSpatialScaler;

/// The color space modes for the input and output textures you use with a spatial scaling effect instance.
typedef NS_ENUM(NSInteger, MTLFXSpatialScalerColorProcessingMode) {
    
    /// Indicates your input and output textures use a perceptual color space (sRGB).
    MTLFXSpatialScalerColorProcessingModePerceptual NS_SWIFT_NAME(perceptual) = 0,
    
    /// Indicates your input and output textures use a linear color space in the `[0,1]` range.
    MTLFXSpatialScalerColorProcessingModeLinear NS_SWIFT_NAME(linear) = 1,
    
    /// Indicates your input and output textures use a high dynamic range color space, beyond the `[0,1]` range.
    ///
    /// When you configure this mode, MetalFX performs a reversible tone mapping operation to convert your data to the `[0,1]` range.
    MTLFXSpatialScalerColorProcessingModeHDR NS_SWIFT_NAME(hdr) = 2,
} API_AVAILABLE(macos(13.0), ios(16.0));

// Forward declaration.
@protocol MTLFXSpatialScaler;


/// A set of properties that configure a spatial scaling effect, and a factory method that creates the effect.
API_AVAILABLE(macos(13.0), ios(16.0))
@interface MTLFXSpatialScalerDescriptor : NSObject <NSCopying>

/// The pixel format of the input color texture for the spatial scaler you create with this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat colorTextureFormat;

/// The pixel format of the output texture for the spatial scaler you create with this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat outputTextureFormat;

/// The width of the input color texture for the spatial scaler you create with this descriptor.
@property (readwrite, nonatomic) NSUInteger inputWidth;

/// The height of the input color texture for the spatial scaler you create with this descriptor.
@property (readwrite, nonatomic) NSUInteger inputHeight;

/// The width of the output color texture for the spatial scaler you create with this descriptor.
@property (readwrite, nonatomic) NSUInteger outputWidth;

/// The height of the output color texture for the spatial scaler you create with this descriptor.
@property (readwrite, nonatomic) NSUInteger outputHeight;

/// The color space of the input color texture for the spatial scaler you create with this descriptor.
///
/// This property's default value is ``MTLFXSpatialScalerColorProcessingMode/MTLFXSpatialScalerColorProcessingModePerceptual``.
@property (readwrite, nonatomic) MTLFXSpatialScalerColorProcessingMode colorProcessingMode;

/// Creates a spatial scaler instance for a Metal device.
///
/// - Parameters:
///    - device: The Metal device that creates the spatial scaler.
/// - Returns:
///    A new spatial scaler instance upon success, or `nil` otherwise.
- (nullable id <MTLFXSpatialScaler>)newSpatialScalerWithDevice:(nonnull id<MTLDevice>)device;

/// Creates a spatial scaler instance for a Metal device.
///
/// - Parameters:
///    - device: The Metal device that creates the spatial scaler.
///    - compiler: A compiler instance this method can use to build pipeline state objects.
/// - Returns:
///    A new spatial scaler instance upon success, or `nil` otherwise.
- (nullable id <MTL4FXSpatialScaler>)newSpatialScalerWithDevice:(nonnull id<MTLDevice>)device compiler:(nonnull id<MTL4Compiler>)compiler API_AVAILABLE(macos(26.0), ios(26.0));

/// Queries whether a Metal device supports spatial scaling compatible with Metal 4.
///
/// - Parameters:
///    - device: The GPU device for which this methods tests support.
///
/// - Returns: <doc://com.apple.documentation/documentation/swift/true> if the device supports spatial scaling with
///             Metal 4, <doc://com.apple.documentation/documentation/swift/false> otherwise.
+ (BOOL)supportsMetal4FX:(nonnull id<MTLDevice>)device API_AVAILABLE(macos(26.0), ios(26.0));

/// Returns a Boolean value that indicates whether the spatial scaler works with a GPU.
///
/// - Parameters:
///    - device: An ``MTLDevice`` instance that represents a GPU.
///
/// - Returns: <doc://com.apple.documentation/documentation/swift/true> if the device supports spatial scaling,
///            <doc://com.apple.documentation/documentation/swift/false> otherwise.
+ (BOOL)supportsDevice:(nonnull id<MTLDevice>)device;

@end

/// An upscaling effect that generates a higher resolution texture in a render pass by spatially analyzing an input texture.
///
/// The MetalFX spatial scaler increases the size of your input texture to a larger output texture. You can use the
/// scaler to upscale every frame of your app’s scene or rendering in real time. With a scaler, you can draw more
/// complicated scenes in less time by intentionally rendering to a lower resolution to save time before upscaling.
///
/// Create an ``MTLFXSpatialScaler`` instance following these steps:
/// 1. Create and configure an ``MTLFXSpatialScalerDescriptor`` instance.
/// 2. Call the descriptor’s ``newSpatialScalerWithDevice:`` method.
///
/// Upscale a rendering by following these steps for every render pass:
/// 1. Set the spatial scaler’s ``colorTexture`` property to the input texture.
/// 2. Set the scaler’s ``inputContentWidth`` and ``inputContentHeight`` properties.
/// 3. Set the scaler’s ``outputTexture`` property to your destination texture.
///
/// Encode the upscale commands to a command buffer by calling the spatial scaler’s ``encodeToCommandBuffer:`` method.
///
/// ## Conforming to texture usage requirements
///
/// Spatial scalers expose properties, such as ``colorTextureUsage``, that indicate requirements for
/// your textures to be compatible with it. These properties indicate the minimum set of ``MTLTextureUsage`` bits
/// that you are responsible for setting in your texture descriptors for this spatial scaler to use them.
///
/// Your game or app can set extra usage bits on your textures without losing compatibility, as long at its maintains
/// the minimum set the scaler requests.
///
/// ## Assigning input and output textures
///
/// When you use an instance of a class that conforms to this protocol, you typically set its input and output textures,
/// as well as other properties, and then encode its work to a command buffer.
///
/// MetalFX doesn't track that you assign the same texture instances to each property across different batches of work,
/// the only requirement is that you provide textures that match the pixel formats and dimensions you specify in the
/// ``MTLFXSpatialScalerDescriptor`` descriptor instance that creates the scaler instance.
///
@protocol MTLFXSpatialScalerBase <NSObject>

/// The minimal texture usage options that your app’s input color texture needs in order to support this scaler.
@property (nonatomic, readonly) MTLTextureUsage colorTextureUsage;
/// The minimal texture usage options that your app’s output color texture needs in order to support this scaler.
@property (nonatomic, readonly) MTLTextureUsage outputTextureUsage;

/// The width, in pixels, of the region within the color texture the scaler uses as its input.
@property (nonatomic) NSUInteger inputContentWidth;
/// The height, in pixels, of the region within the color texture the scaler uses as its input.
@property (nonatomic) NSUInteger inputContentHeight;

/// Input color texture you set for the scaler that supports the correct color texture usage options.
@property (nonatomic, retain, nullable) id<MTLTexture> colorTexture;

/// The output texture into which this scaler writes its output.
///
/// You are responsible for providing a texture with a private `storageMode` to this property.
@property (nonatomic, retain, nullable) id<MTLTexture> outputTexture;

/// The pixel format of the input color texture for this this scaler.
@property (nonatomic, readonly) MTLPixelFormat colorTextureFormat;
/// The pixel format of the output color texture for this this scaler.
@property (nonatomic, readonly) MTLPixelFormat outputTextureFormat;
/// The width, in pixels, of the input color texture for this scaler.
@property (nonatomic, readonly) NSUInteger inputWidth;
/// The height, in pixels, of the input color texture for this scaler.
@property (nonatomic, readonly) NSUInteger inputHeight;
/// The width, in pixels, of the output color texture for this scaler.
@property (nonatomic, readonly) NSUInteger outputWidth;
/// The height, in pixels, of the output color texture for this scaler.
@property (nonatomic, readonly) NSUInteger outputHeight;
/// The color processing mode you set in this spatial scaler’s descriptor.
@property (nonatomic, readonly) MTLFXSpatialScalerColorProcessingMode colorProcessingMode;

/// An optional fence that you provide to synchronize your app’s untracked resources.
@property (nonatomic, retain, nullable) id<MTLFence> fence;

@end

/// An upscaling effect that generates a higher resolution texture in a render pass by spatially analyzing an input texture.
///
/// You create instances of this class by calling ``MTLFXSpatialScalerDescriptor/newSpatialScalerWithDevice:``.
///
/// When using instances of objects conforming to this protocol, you configure the different properties it
/// inherits from protocol ``MTLFXSpatialScalerBase`` and then call ``encodeToCommandBuffer:`` to
/// encode its work into a Metal command buffer.
///
/// See ``MTLFXSpatialScalerBase`` for more details on configuring and using spatial scalers.
///
API_AVAILABLE(macos(13.0), ios(16.0))
@protocol MTLFXSpatialScaler <MTLFXSpatialScalerBase>

/// Encode this spatial scaler work into a command buffer.
///
/// - Parameters:
///    - commandBuffer: A command buffer into which this spatial scaler encodes work.
///
- (void)encodeToCommandBuffer:(nonnull id<MTLCommandBuffer>)commandBuffer;

@end

