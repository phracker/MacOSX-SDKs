//
//  MTLFXTemporalScaler.h
//  MetalFX
//
//  Copyright (c) 2021-2022 Apple Inc. All rights reserved.
//

#import <Metal/Metal.h>
#import <Metal/MTL4Compiler.h>
// Forward declaration of Metal4FX scaler.
@protocol MTL4FXTemporalScaler;
// Forward declaration.
@protocol MTLFXTemporalScaler;

/// A set of properties that configure a temporal scaling effect, and a factory method that creates the effect.
API_AVAILABLE(macos(13.0), ios(16.0))
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos)
#endif
@interface MTLFXTemporalScalerDescriptor : NSObject <NSCopying>

/// The pixel format of the input color texture for the temporal scaler you create with this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat colorTextureFormat;
/// The pixel format of the input depth texture for the temporal scaler you create with this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat depthTextureFormat;
/// The pixel format of the input motion texture for the temporal scaler you create with this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat motionTextureFormat;
/// The pixel format of the output texture for the temporal scaler you create with this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat outputTextureFormat;

/// The width of the input color texture for the temporal scaler you create with this descriptor.
@property (readwrite, nonatomic) NSUInteger inputWidth;
/// The height of the input color texture for the temporal scaler you create with this descriptor.
@property (readwrite, nonatomic) NSUInteger inputHeight;

/// The width of the output color texture for the temporal scaler you create with this descriptor.
@property (readwrite, nonatomic) NSUInteger outputWidth;
/// The height of the output color texture for the temporal scaler you create with this descriptor.
@property (readwrite, nonatomic) NSUInteger outputHeight;

/// A Boolean value that indicates whether MetalFX calculates the exposure for each frame.
///
/// Set this property to <doc://com.apple.documentation/documentation/swift/true> to create a scaler that automatically
/// calculates the exposure level for each image it scales.
///
/// * Note: Temporal scaler instances that use auto exposure ignore their ``MTLFXTemporalScalerBase/exposureTexture``
/// property.
///
/// This property's default value is <doc://com.apple.documentation/documentation/swift/false>.
@property (readwrite, nonatomic, getter=isAutoExposureEnabled) BOOL autoExposureEnabled;

/// A Boolean value that indicates whether MetalFX compiles a temporal scaling effect’s underlying upscaler as it
/// creates the instance.
///
/// This property gives you the option to decide when it’s better for your app to give MetalFX the time it needs to
/// compile the underlying upscaler of the temporal scaling effect. The two choices are:
///
/// * As you create the effect
/// * After you create the effect, likely when your app needs to upscale the initial textures
///
/// You can create a temporal scaler that can upscale textures at its best speed
/// immediately after you create it by setting this property to <doc://com.apple.documentation/documentation/swift/true>
/// and then calling an initialization method like ``newTemporalScalerWithDevice:``. However, it may take MetalFX more
/// time for that method to return while it creates the denoiser scaler and compiles its underlying pipelines.
///
/// By default, the property is equal to <doc://com.apple.documentation/documentation/swift/false>, which tells MetalFX
/// to quickly create and return the temporal scaling-effect instance, and then compile a faster upscaler in the background.
/// However, this means the effect can take more time to upscale textures while the framework compiles the underlying upscaler.
/// When the framework finishes compiling, the effect runs just as fast as if you set the property to
/// <doc://com.apple.documentation/documentation/swift/true>.
///
/// * Note: The image quality of the effect’s output texture is consistent, whether it’s using the slower interim upscaler
/// or the final, faster upscaler.
///
@property (readwrite, nonatomic) BOOL requiresSynchronousInitialization;

/// A Boolean value that indicates whether the temporal scaler you create with this descriptor uses dynamic resolution.
///
/// When you set this property to <doc://com.apple.documentation/documentation/swift/true> to enable dynamic resolution,
/// scale properties ``inputContentMinScale`` and ``inputContentMaxScale`` represent the input and output resolution
/// both the width and height.
///
/// * Note: The scaler assumes that aspect ratio of the input and output textures doesn't change.
///
@property (readwrite, nonatomic, getter=isInputContentPropertiesEnabled) BOOL inputContentPropertiesEnabled;

/// The smallest scale factor the temporal scaler you create with this descriptor can use to generate output textures.
@property (readwrite, nonatomic) float inputContentMinScale;

/// The largest scale factor the temporal scaler you create with this descriptor can use to generate output textures.
@property (readwrite, nonatomic) float inputContentMaxScale;


/// A Boolean value that indicates whether a temporal scaler you create with the descriptor applies a reactive mask.
@property (readwrite, nonatomic, getter=isReactiveMaskTextureEnabled) BOOL reactiveMaskTextureEnabled API_AVAILABLE(macos(14.4), ios(17.4));

/// The pixel format of the reactive mask input texture for a temporal scaler you create with the descriptor.
@property (readwrite, nonatomic) MTLPixelFormat reactiveMaskTextureFormat API_AVAILABLE(macos(14.4), ios(17.4));

/// Creates a temporal scaler instance for a Metal device.
///
/// - Parameters:
///    - device: The Metal device that creates the temporal scaler.
/// - Returns:
///    A new temporal scaler instance upon success, or `nil` otherwise.
- (nullable id <MTLFXTemporalScaler>)newTemporalScalerWithDevice:(nonnull id<MTLDevice>)device;

/// Creates a temporal scaler instance for a Metal device.
///
/// - Parameters:
///    - device: The Metal device that creates the temporal scaler.
///    - compiler: A compiler instance this method can use to build pipeline state objects.
/// - Returns:
///    A new temporal scaler instance upon success, or `nil` otherwise.
- (nullable id <MTL4FXTemporalScaler>)newTemporalScalerWithDevice:(nonnull id<MTLDevice>)device compiler:(nonnull id<MTL4Compiler>)compiler API_AVAILABLE(macos(26.0), ios(26.0));

/// Returns the smallest temporal scaling factor the device supports as a floating-point value.
///
/// - Parameters:
///    - device: The Metal device for which this method performs this check.
///
/// - Returns: the minimum input content scale the GPU device supports.
+ (float)supportedInputContentMinScaleForDevice:(nonnull id<MTLDevice>)device API_AVAILABLE(macos(14.0), ios(17.0));

/// Returns the largest temporal scaling factor the device supports as a floating-point value.
///
/// - Parameters:
///    - device: The Metal device for which this method performs this check.
///
/// - Returns: the maximum input content scale the GPU device supports.
+ (float)supportedInputContentMaxScaleForDevice:(nonnull id<MTLDevice>)device API_AVAILABLE(macos(14.0), ios(17.0));

/// Returns a Boolean value that indicates whether the temporal scaler works with a GPU.
///
/// - Parameters:
///    - device: A device instance that represents a GPU.
///
/// - Returns: <doc://com.apple.documentation/documentation/swift/true> if the device supports temporal scaling,
///            <doc://com.apple.documentation/documentation/swift/false> otherwise.
+ (BOOL)supportsDevice:(nonnull id<MTLDevice>)device;

/// Queries whether a Metal device supports temporal scaling compatible with Metal 4.
///
/// - Parameters:
///    - device: The GPU device for which this methods tests support.
///
/// - Returns: <doc://com.apple.documentation/documentation/swift/true> if the device supports temporal scaling with
///             Metal 4, <doc://com.apple.documentation/documentation/swift/false> otherwise.
+ (BOOL)supportsMetal4FX:(nonnull id<MTLDevice>)device API_AVAILABLE(macos(26.0), ios(26.0));

@end

@protocol MTLFXFrameInterpolatableScaler <NSObject>

@end


/// An upscaling effect that generates a higher resolution texture in a render pass by analyzing multiple input
/// textures over time.
///
/// The MetalFX temporal scaler increases the size of your input texture to a larger output texture. You can use the
/// scaler to upscale every frame of your app’s scene or rendering in real time. With a scaler, you can draw more
/// complicated scenes in less time by intentionally rendering to a lower resolution to save time before upscaling.
///
/// Create an ``MTLFXTemporalScaler`` instance by following these steps:
/// 1. Create and configure an ``MTLFXTemporalScalerDescriptor`` instance.
/// 2. Call the descriptor’s ``newTemporalScalerWithDevice:`` method.
///
/// Upscale a rendering by following these steps for every render pass:
/// 1. Set the temporal scaler’s ``colorTexture`` property to the input texture.
/// 2. Set the scaler’s ``inputContentWidth`` and ``inputContentHeight`` properties.
/// 3. Set the scaler’s ``outputTexture`` property to your destination texture.
/// 4. Encode the upscale commands to a command buffer by calling the temporal scaler’s
/// ``MTLFXTemporalScaler/encodeToCommandBuffer:`` method.
/// 
/// ## Conforming to texture usage requirements
///
/// Temporal scalers expose properties, such as ``colorTextureUsage``, that indicate requirements for
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
/// ``MTLFXTemporalScalerDescriptor`` descriptor instance that creates the scaler instance.
///
@protocol MTLFXTemporalScalerBase <MTLFXFrameInterpolatableScaler>

/// The minimal texture usage options that your app’s input color texture needs in order to support this scaler.
@property (nonatomic, readonly) MTLTextureUsage colorTextureUsage;
/// The minimal texture usage options that your app’s input depth texture needs in order to support this scaler.
@property (nonatomic, readonly) MTLTextureUsage depthTextureUsage;
/// The minimal texture usage options that your app’s motion texture needs in order to support this scaler.
@property (nonatomic, readonly) MTLTextureUsage motionTextureUsage;
/// The minimal texture usage options that your app’s reactive texture needs in order to support this scaler.
@property (nonatomic, readonly) MTLTextureUsage reactiveTextureUsage;

/// The minimal texture usage options that your output texture needs in order to support this scaler.
@property (nonatomic, readonly) MTLTextureUsage outputTextureUsage;

/// The width, in pixels, of the region within the color texture the scaler uses as its input.
@property (nonatomic) NSUInteger inputContentWidth;
/// The height, in pixels, of the region within the color texture the scaler uses as its input.
@property (nonatomic) NSUInteger inputContentHeight;

/// An input color texture you set for the scaler that supports the correct color texture usage options.
@property (nonatomic, retain, nullable) id<MTLTexture> colorTexture;
/// An input depth texture you set for the scaler that supports the correct color texture usage options.
@property (nonatomic, retain, nullable) id<MTLTexture> depthTexture;
/// An input motion texture you set for the scaler that supports the correct color texture usage options.
@property (nonatomic, retain, nullable) id<MTLTexture> motionTexture;

/// The output texture into which this scaler writes its output.
///
/// You are responsible for providing a texture with a private `storageMode` to this property.
@property (nonatomic, retain, nullable) id<MTLTexture> outputTexture;

/// The exposure texture this scaler uses.
///
/// Create and assign a 1x1  ``MTLPixelFormatR16Float``  texture to assign to this property. MetalFX reads the R channel
/// of the texel at position `(0,0)` and uses it as the exposure value. It then uses this value to multiply the input color.
///
/// For best performance, use the GPU to generate the exposure value and store it into this texture.
///
/// * Note: The temporal scaler ignores this property if you create it with a descriptor that has its
/// ``MTLFXTemporalScalerDescriptor/autoExposureEnabled`` property set to
/// <doc://com.apple.documentation/documentation/swift/true>.
@property (nonatomic, retain, nullable) id<MTLTexture> exposureTexture;

/// The reactive-mask texture input this scaler uses.
///
/// This texture helps guide the denoiser when objects move quickly in a scene with inaccurate motion information,
/// such as when they involve alpha blending. In these situations, you can get better results by guiding MetalFX whether
/// to favor the current frame on a per-pixel basis with a reactive mask texture.
///
/// When providing this texture, you are responsible for ensuring each pixel is in the range `[0.0, 1.0]`, where a value:
/// * Equal to `0.0` tells MetalFX to follow its normal behavior for the corresponding pixel
/// * Equal to `1.0` tells MetalFX to ignore temporal history for the corresponding pixel
/// * In the range `(0.0, 1.0)` proportionally blends the effect for the corresponding pixel
///
@property (nonatomic, retain, nullable) id<MTLTexture> reactiveMaskTexture;
/// A pre-exposure value this scaler evaluates.
///
/// If the input color texture you assign to ``colorTexture`` is pre-multiplied by fixed value, set this property
/// to that same fixed value so MetalFX divides input color by it. This is not a common situation and you typically
/// don't need to assign a value to this property.
@property (nonatomic) float preExposure;

/// The horizontal component of the subpixel sampling coordinate you use to generate the color texture input.
///
/// This property indicates the horizontal pixel offset this scaler samples to return to the frame's reference frame.
@property (nonatomic) float jitterOffsetX;

/// The vertical component of the subpixel sampling coordinate you use to generate the color texture input.
///
/// This property indicates the vertical pixel offset this scaler samples to return to the frame's reference frame.
@property (nonatomic) float jitterOffsetY;

/// The horizontal scale factor the scaler applies to the input motion texture.
///
/// The scaler converts the horizontal component of each value in ``motionTexture`` into fragment (pixel)
/// coordinates by multiplying it by this property’s value.
///
/// If you set this property's value to `1.0`, this temporal scaler expects that each pixel's motion vector points
/// to that pixel's location in the ``colorTexture`` at the time of the last call to encode this scaler's work. For example,
/// in Metal's standard device coordinates, where `(0,0)` represents the upper-left corner of the framebuffer, the motion
/// vectors for an object that moves down and to the right in the ``colorTexture`` by `10` pixels would be `(-10,-10)`.
@property (nonatomic) float motionVectorScaleX;

/// The vertical scale factor the scaler applies to the input motion texture.
///
/// The scaler converts the horizontal component of each value in ``motionTexture`` into fragment (pixel)
/// coordinates by multiplying it by this property’s value.
///
/// If you set this property's value to `1.0`, this temporal scaler expects that each pixel's motion vector points
/// to that pixel's location in the ``colorTexture`` at the time of the last call to encode this scaler's work. For example,
/// in Metal's standard device coordinates, where `(0,0)` represents the upper-left corner of the framebuffer, the motion
/// vectors for an object that moves down and to the right in the ``colorTexture`` by `10` pixels would be `(-10,-10)`.
@property (nonatomic) float motionVectorScaleY;

/// A Boolean that indicates whether the temporal scaler discards historical data from previous frames.
@property (nonatomic) BOOL reset;

/// A Boolean value that indicates whether the depth texture uses zero to represent the farthest distance.
@property (readwrite, nonatomic, getter=isDepthReversed) BOOL depthReversed;

/// The pixel format of the input color texture for this this scaler.
@property (nonatomic, readonly) MTLPixelFormat colorTextureFormat;
/// The pixel format of the input depth texture for this this scaler.
@property (nonatomic, readonly) MTLPixelFormat depthTextureFormat;
/// The pixel format of the input motion texture for this this scaler.
@property (nonatomic, readonly) MTLPixelFormat motionTextureFormat;
/// The pixel format of the input reactive mask texture for this this scaler.
@property (nonatomic, readonly) MTLPixelFormat reactiveMaskTextureFormat;
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

/// The smallest scale factor the temporal scaler can use to generate output textures.
@property (nonatomic, readonly) float inputContentMinScale;
/// The largest scale factor the temporal scaler can use to generate output textures.
@property (nonatomic, readonly) float inputContentMaxScale;

/// An optional fence that you provide to synchronize your app’s untracked resources.
@property (nonatomic, retain, nullable) id<MTLFence> fence;

@end

/// An upscaling effect that generates a higher resolution texture in a render pass by analyzing multiple input textures over time.
///
/// You create instances of this class by calling ``MTLFXTemporalScalerDescriptor/newTemporalScalerWithDevice:``.
///
/// When using instances of objects conforming to this protocol, you configure the different properties it
/// inherits from protocol ``MTLFXTemporalScalerBase`` and then call ``encodeToCommandBuffer:`` to
/// encode its work into a Metal command buffer.
///
/// See ``MTLFXTemporalScalerBase`` for more details on configuring and using spatial scalers.
///
API_AVAILABLE(macos(13.0), ios(16.0))
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos)
#endif
@protocol MTLFXTemporalScaler <MTLFXTemporalScalerBase>

/// Encode this spatial scaler work into a command buffer.
///
/// - Parameters:
///    - commandBuffer: A command buffer into which this spatial scaler encodes work.
///
- (void)encodeToCommandBuffer:(nonnull id<MTLCommandBuffer>)commandBuffer;

@end
