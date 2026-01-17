//
//  MTLFXTemporalDenoisedScaler.h
//  MetalFX
//
//  Copyright (c) 2021-2022 Apple Inc. All rights reserved.
//

#import <Metal/Metal.h>
#import <simd/simd.h>

#import <Metal/MTL4Compiler.h>
// Forward declaration of Metal4FX scaler.
@protocol MTL4FXTemporalDenoisedScaler;
// Forward declaration.
@protocol MTLFXTemporalDenoisedScaler;

/// A set of properties that configure a denoiser scaler, and a factory method that creates the effect.
///
/// A denoiser scaler helps reduce noise in an image. You typically use this in situations where your pixels are
/// expensive to produce, such as elaborate ray or path tracing situations, to save processing time by producing a
/// noisy image that this scaler then cleans up before presentation.
///
/// When you configure this descriptor, set the properties that determine the pixel format for each texture to the
/// respective format of the texture you later assign to the scaler. For example, make sure that the format to which
/// you set the ``colorTextureFormat`` property matches the format of the texture you later assign to the scaler's
/// ``MTLFXTemporalDenoisedScalerDescriptor/colorTexture`` property.
API_AVAILABLE(macos(26.0), ios(18.0))
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos)
#endif
@interface MTLFXTemporalDenoisedScalerDescriptor : NSObject <NSCopying>

/// The pixel format of the input color texture for the scaler you create with this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat colorTextureFormat;

/// The pixel format of the input depth texture for the scaler you create with this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat depthTextureFormat;

/// The pixel format of the input motion texture for the scaler you create with this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat motionTextureFormat;

/// The pixel format of the input diffuse albedo texture for the scaler you create with this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat diffuseAlbedoTextureFormat;

/// The pixel format of the input specular albedo texture for the scaler you create with this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat specularAlbedoTextureFormat;

/// The pixel format of the input normal texture for the scaler you create with this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat normalTextureFormat;

/// The pixel format of the input roughness texture for the scaler you create with this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat roughnessTextureFormat;

/// The pixel format of the input specular hit texture for the scaler you create with this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat specularHitDistanceTextureFormat;
/// The pixel format of the input denoise strength mask texture for the scaler you create with this descriptor.
///
/// You typically set this to a single-channel texture format.
@property (readwrite, nonatomic) MTLPixelFormat denoiseStrengthMaskTextureFormat;
/// The pixel format of the input transparency overlay texture for the scaler you create with this descriptor.
///
/// You typically set this to a 4-channel RGBA texture format.
@property (readwrite, nonatomic) MTLPixelFormat transparencyOverlayTextureFormat;

/// The pixel format of the output color texture for the scaler you create with this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat outputTextureFormat;

/// The width, in pixels, of the input color texture for the denoiser scaler.
@property (readwrite, nonatomic) NSUInteger inputWidth;
/// The height, in pixels, of the input color texture for the denoiser scaler.
@property (readwrite, nonatomic) NSUInteger inputHeight;

/// The width, in pixels, of the output color texture for the denoiser scaler.
@property (readwrite, nonatomic) NSUInteger outputWidth;
/// The height, in pixels, of the input color texture for the denoiser scaler.
@property (readwrite, nonatomic) NSUInteger outputHeight;

/// A Boolean value that indicates whether MetalFX compiles a temporal scaling effect’s underlying upscaler as it
/// creates the instance.
///
/// This property gives you the option to decide when it’s better for your app to give MetalFX the time it needs to
/// compile the underlying upscaler of the temporal scaling effect. The two choices are:
///
/// * As you create the effect
/// * After you create the effect, likely when your app needs to upscale the initial textures
///
/// You can create a temporal denoised scaler instance that can denoise and upscale textures at its best speed
/// immediately after you create it by setting this property to <doc://com.apple.documentation/documentation/swift/true>
/// and then calling an initialization method like ``newTemporalDenoisedScalerWithDevice:``. However, it may take MetalFX
/// more time for that method to return while it creates the denoiser scaler and compiles its underlying pipelines.
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

/// A Boolean value that indicates whether MetalFX calculates the exposure for each frame.
///
/// Set this property to <doc://com.apple.documentation/documentation/swift/true> to create a scaler that automatically
/// calculates the exposure level for each image it scales.
///
/// * Note: Denoiser scaler instances that use auto exposure ignore their ``MTLFXTemporalScalerBase/exposureTexture``
/// property.
///
/// This property's default value is <doc://com.apple.documentation/documentation/swift/false>.
@property (readwrite, nonatomic, getter=isAutoExposureEnabled) BOOL autoExposureEnabled;

/// A Boolean value that indicates whether a scaler you create from this descriptor applies a reactive mask.
@property (readwrite, nonatomic, getter=isReactiveMaskTextureEnabled) BOOL reactiveMaskTextureEnabled;

/// The pixel format of the reactive mask input texture for a scaler you create from this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat reactiveMaskTextureFormat;

/// A Boolean value indicating whether the scaler evaluates a specular hit distance texture as part of its operation.
@property (readwrite, nonatomic, getter=isSpecularHitDistanceTextureEnabled) BOOL specularHitDistanceTextureEnabled;

/// A Boolean value indicating whether the scaler evaluates a denoise strength mask texture as part of its operation.
@property (readwrite, nonatomic, getter=isDenoiseStrengthMaskTextureEnabled) BOOL denoiseStrengthMaskTextureEnabled;
/// A Boolean value indicating whether the scaler evaluates a transparency overlay texture as part of its operation.
@property (readwrite, nonatomic, getter=isTransparencyOverlayTextureEnabled) BOOL transparencyOverlayTextureEnabled;

/// Creates a denoiser scaler instance for a Metal device.
///
/// - Parameters:
///    - device: The Metal device that creates the denoiser scaler.
/// - Returns:
///    A denoiser scaler instance upon success, or `nil` otherwise.
- (nullable id <MTLFXTemporalDenoisedScaler>)newTemporalDenoisedScalerWithDevice:(nonnull id<MTLDevice>)device;

/// Creates a denoiser scaler instance for a Metal device.
///
/// - Parameters:
///    - device: The Metal device that creates the denoiser scaler.
///    - compiler: A compiler instance this method can use to build pipeline state objects.
/// - Returns:
///    A denoiser scaler instance upon success, or `nil` otherwise.
-(nullable id <MTL4FXTemporalDenoisedScaler>)newTemporalDenoisedScalerWithDevice:(nonnull id<MTLDevice>)device compiler:(nonnull id<MTL4Compiler>)compiler;

/// Returns the smallest temporal scaling factor the device supports as a floating-point value.
///
/// - Parameters:
///    - device: The Metal device for which this method checks the minimum input content scale it supports.
///
/// - Returns: the minimum input content scale the GPU device supports.
+ (float)supportedInputContentMinScaleForDevice:(nonnull id<MTLDevice>)device;

/// Returns the largest temporal scaling factor the device supports as a floating-point value.
///
/// - Parameters:
///    - device: The Metal device for which this method checks the maximum input content scale it supports.
///
/// - Returns: the maximum input content scale the GPU device supports.
+ (float)supportedInputContentMaxScaleForDevice:(nonnull id<MTLDevice>)device;

/// Queries whether a Metal device supports denosing scaling compatible on Metal 4.
///
/// - Parameters:
///    - device: The GPU device for which this methods tests support.
///
/// - Returns: <doc://com.apple.documentation/documentation/swift/true> if the device supports denoising scaling for
///             Metal 4, <doc://com.apple.documentation/documentation/swift/false> otherwise.
+ (BOOL)supportsMetal4FX:(nonnull id<MTLDevice>)device;

/// Queries whether a Metal device supports denoising scaling.
///
/// - Parameters:
///    - device: The GPU device for which this methods tests support.
///
/// - Returns: <doc://com.apple.documentation/documentation/swift/true> if the device supports denoising scaling,
///             <doc://com.apple.documentation/documentation/swift/false> otherwise.
+ (BOOL)supportsDevice:(nonnull id<MTLDevice>)device;

@end

/// A common abstraction to all denoiser scalers.
///
/// This protocol defines properties common to all denoiser scalers. You access these properties through
/// any denoiser scaler instance you create by calling construction methods such as
/// ``MTLFXTemporalDenoisedScalerDescriptor/newTemporalDenoisedScalerWithDevice:``.
///
/// ### Conforming to texture usage requirements
///
/// Denoiser scaler instances expose properties, such as ``colorTextureUsage``, that indicate requirements for
/// your textures to be compatible with it. These properties indicate the minimum set of ``MTLTextureUsage`` bits
/// that you are responsible for setting in your texture descriptors for this denoise scaler to use them.
///
/// Your game or app can set extra usage bits on your textures without losing compatibility, as long at its maintains
/// the minimum set the denoiser scaler requests.
///
/// ### Assigning input and output textures
///
/// When you use an instance of a class that conforms to this protocol, you typically set its input and output textures,
/// as well as other properties, and then encode its work to a command buffer.
///
/// MetalFX doesn't track that you assign the same texture instances to each property across different batches of work,
/// the only requirement is that you provide textures that match the pixel formats and dimensions you specify in the
/// ``MTLFXTemporalDenoisedScalerDescriptor`` descriptor instance that creates the scaler instance.
///
/// ### Encoding work
///
/// Once you configure all properties for the current frame of your game or app, you indicate to the scaler instance
/// into which command buffer it encodes its work. You achieve this by calling, for example,
/// ``MTLFXTemporalDenoisedScaler/encodeToCommandBuffer:``.
///
API_AVAILABLE(macos(26.0), ios(26.0))
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos)
#endif
@protocol MTLFXTemporalDenoisedScalerBase <MTLFXFrameInterpolatableScaler>

/// The minimal texture usage options that your app’s input color texture needs in order to support this denoiser scaler.
@property (nonatomic, readonly) MTLTextureUsage colorTextureUsage;

/// The minimal texture usage options that your app’s input depth texture needs in order to support this denoiser scaler.
@property (nonatomic, readonly) MTLTextureUsage depthTextureUsage;

/// The minimal texture usage options that your app’s input motion texture needs in order to support this denoiser scaler.
@property (nonatomic, readonly) MTLTextureUsage motionTextureUsage;

/// The minimal texture usage options that your app’s input reactive texture needs in order to support this denoiser scaler.
@property (nonatomic, readonly) MTLTextureUsage reactiveTextureUsage;

/// The minimal texture usage options that your app’s input diffuse albedo texture needs in order to support this denoiser scaler.
@property (nonatomic, readonly) MTLTextureUsage diffuseAlbedoTextureUsage;

/// The minimal texture usage options that your app’s input specular albedo texture needs in order to support this denoiser scaler.
@property (nonatomic, readonly) MTLTextureUsage specularAlbedoTextureUsage;

/// The minimal texture usage options that your app’s input normal texture needs in order to support this denoiser scaler.
@property (nonatomic, readonly) MTLTextureUsage normalTextureUsage;

/// The minimal texture usage options that your app’s input roughness texture needs in order to support this denoiser scaler.
@property (nonatomic, readonly) MTLTextureUsage roughnessTextureUsage;

/// The minimal texture usage options that your app’s input specular hit texture needs in order to support this denoiser scaler.
@property (nonatomic, readonly) MTLTextureUsage specularHitDistanceTextureUsage;

/// The minimal texture usage options that your app’s input denoise strength texture needs in order to support this denoiser scaler.
@property (nonatomic, readonly) MTLTextureUsage denoiseStrengthMaskTextureUsage;
/// The minimal texture usage options that your app’s input transparency overlay texture needs in order to support this denoiser scaler.
@property (nonatomic, readonly) MTLTextureUsage transparencyOverlayTextureUsage;

/// The minimal texture usage options that your app’s output texture needs in order to support this denoiser scaler.
@property (nonatomic, readonly) MTLTextureUsage outputTextureUsage;

/// Assigns the color texture this scaler evaluates.
///
/// You are responsible for ensuring the usage and pixel format of the texture you assign to this property matches the
/// texture usage ``colorTextureUsage`` requests and the pixel format that
/// ``MTLFXTemporalDenoisedScalerDescriptor/colorTextureFormat`` requests.
@property (nonatomic, retain, nullable) id<MTLTexture> colorTexture;

/// The depth texture this scaler evaluates.
///
/// You are responsible for ensuring the usage and pixel format of the texture you assign to this property matches the
/// texture usage ``depthTextureUsage`` requests and the pixel format that
/// ``MTLFXTemporalDenoisedScalerDescriptor/depthTextureFormat`` requests.
@property (nonatomic, retain, nullable) id<MTLTexture> depthTexture;

/// The motion texture this scaler evaluates.
///
/// You are responsible for ensuring the usage and pixel format of the texture you assign to this property matches the
/// texture usage ``motionTextureUsage`` requests and the pixel format that
/// ``MTLFXTemporalDenoisedScalerDescriptor/motionTextureFormat`` requests.
@property (nonatomic, retain, nullable) id<MTLTexture> motionTexture;

/// The diffuse albedo texture this scaler evaluates.
///
/// You are responsible for ensuring the usage and pixel format of the texture you assign to this property matches the
/// texture usage ``diffuseAlbedoTextureUsage`` requests and the pixel format that
/// ``MTLFXTemporalDenoisedScalerDescriptor/diffuseAlbedoTextureFormat`` requests.
@property (nonatomic, retain, nullable) id<MTLTexture> diffuseAlbedoTexture;

/// The specular albedo texture this scaler evaluates.
///
/// You are responsible for ensuring the usage and pixel format of the texture you assign to this property matches the
/// texture usage ``specularAlbedoTextureUsage`` requests and the pixel format that
/// ``MTLFXTemporalDenoisedScalerDescriptor/specularAlbedoTextureFormat`` requests.
@property (nonatomic, retain, nullable) id<MTLTexture> specularAlbedoTexture;

/// The normal texture this scaler evaluates.
///
/// You are responsible for ensuring the usage and pixel format of the texture you assign to this property matches the
/// texture usage ``normalTextureUsage`` requests and the pixel format that
/// ``MTLFXTemporalDenoisedScalerDescriptor/normalTextureFormat`` requests.
@property (nonatomic, retain, nullable) id<MTLTexture> normalTexture;

/// The roughness texture this scaler evaluates.
///
/// You are responsible for ensuring the usage and pixel format of the texture you assign to this property matches the
/// texture usage ``roughnessTextureUsage`` requests and the pixel format that
/// ``MTLFXTemporalDenoisedScalerDescriptor/roughnessTextureFormat`` requests.
@property (nonatomic, retain, nullable) id<MTLTexture> roughnessTexture;

/// The specular hit texture this scaler evaluates.
///
/// You are responsible for ensuring the usage and pixel format of the texture you assign to this property matches the
/// texture usage ``specularHitDistanceTextureUsage`` requests and the pixel format that
/// ``MTLFXTemporalDenoisedScalerDescriptor/specularHitDistanceTextureFormat`` requests.
@property (nonatomic, retain, nullable) id<MTLTexture> specularHitDistanceTexture;

/// The denoise strength mask texture this scaler evaluates.
///
/// Use this single-channel texture to mark, at a per-pixel level, areas that this denoiser ignores. To configure a pixel
/// that the denoiser ignores, provide `1.0` as the value at that pixel's corresponding location on this texture.
///
/// You are responsible for ensuring the usage and pixel format of the texture you assign to this property matches the
/// texture usage ``denoiseStrengthMaskTextureUsage`` requests and the pixel format that
/// ``MTLFXTemporalDenoisedScalerDescriptor/denoiseStrengthMaskTextureFormat`` requests.
@property (nonatomic, retain, nullable) id<MTLTexture> denoiseStrengthMaskTexture;

/// The transparency overlay texture that this scaler evaluates.
///
/// Use this RGBA texture to provide to the denoiser an overlay with your transparent pixels, such as the output
/// of your particle systems. MetalFX interprets this to be a texture in linear color space, with the RGB channels
/// ranging between `0` and infinity, and the alpha channel in the range `[0,1]`, representing the opacity of the pixel.
///
/// You are responsible for ensuring the usage and pixel format of the texture you assign to this property matches the
/// texture usage ``transparencyOverlayTextureUsage`` requests and the pixel format that
/// ``MTLFXTemporalDenoisedScalerDescriptor/transparencyOverlayTextureFormat`` requests.
@property (nonatomic, retain, nullable) id<MTLTexture> transparencyOverlayTexture;


/// The output texture into which this denoiser scaler writes its output.
///
/// You are responsible for providing a texture with a private `storageMode` to this property.
@property (nonatomic, retain, nullable) id<MTLTexture> outputTexture;

/// An exposure texture that this denoiser scaler evaluates.
///
/// Create and assign a 1x1  `MTLPixelFormatR16Float`  texture to assign to this property. MetalFX reads the R channel
/// of the texel at position `(0,0)` and uses it as the exposure value. It then uses this value to multiply the input color.
///
/// For best performance, use the GPU to generate the exposure value and store it into this texture.
///
/// * Note: The temporal scaler ignores this property if you create it with a descriptor that has its
/// ``MTLFXTemporalScalerDescriptor/autoExposureEnabled`` property set to
/// <doc://com.apple.documentation/documentation/swift/true>.
@property (nonatomic, retain, nullable) id<MTLTexture> exposureTexture;

/// A pre-exposure value for this scaler to evaluate.
///
/// If the input color texture you assign to ``colorTexture`` is pre-multiplied by fixed value, set this property
/// to that same fixed value so MetalFX divides input color by it. This is not a common situation and you typically
/// don't need to assign a value to this property.
@property (nonatomic) float preExposure;


/// A reactive-mask texture input for this scaler to evaluate.
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

/// The horizontal component of the subpixel sampling coordinate you use to generate the color texture input.
///
/// This property indicates the horizontal pixel offset this scaler samples to return to the frame's reference frame.
@property (nonatomic) float jitterOffsetX;


/// The vertical component of the subpixel sampling coordinate you use to generate the color texture input.
///
/// This property indicates the vertical pixel offset this scaler samples to return to the frame's reference frame.
@property (nonatomic) float jitterOffsetY;

/// The horizontal scale factor the denoiser scaler applies to the input motion texture.
///
/// The scaler converts the horizontal component of each value in ``motionTexture`` into fragment (pixel)
/// coordinates by multiplying it by this property’s value.
///
/// If you set this property's value to `1.0`, this denoiser scaler expects that each pixel's motion vector points
/// to that pixel's location in the ``colorTexture`` at the time of the last call to encode this scaler's work. For example,
/// in Metal's standard device coordinates, where `(0,0)` represents the upper-left corner of the framebuffer, the motion
/// vectors for an object that moves down and to the right in the ``colorTexture`` by `10` pixels would be `(-10,-10)`.
@property (nonatomic) float motionVectorScaleX;

/// The vertical scale factor the denoiser scaler applies to the input motion texture.
///
/// The scaler converts the horizontal component of each value in ``motionTexture`` into fragment (pixel)
/// coordinates by multiplying it by this property’s value.
///
/// If you set this property's value to `1.0`, this denoiser scaler expects that each pixel's motion vector points
/// to that pixel's location in the ``colorTexture`` at the time of the last call to encode this scaler's work. For example,
/// in Metal's standard device coordinates, where `(0,0)` represents the upper-left corner of the framebuffer, the motion
/// vectors for an object that moves down and to the right in the ``colorTexture`` by `10` pixels would be `(-10,-10)`.
@property (nonatomic) float motionVectorScaleY;

/// A Boolean property indicating whether to reset history.
///
/// Set this property to <doc://com.apple.documentation/documentation/swift/true> to invalidate history, for example
/// when there is a scene cut in your game.
@property (nonatomic) BOOL shouldResetHistory;

/// A Boolean value that indicates whether the depth texture uses zero to represent the farthest distance.
///
/// This property's default value is <doc://com.apple.documentation/documentation/swift/true>.
@property (readwrite, nonatomic, getter=isDepthReversed) BOOL depthReversed;

/// The pixel format of the input color texture for this denoiser scaler.
@property (nonatomic, readonly) MTLPixelFormat colorTextureFormat;
/// The pixel format of the input depth texture for this denoiser scaler.
@property (nonatomic, readonly) MTLPixelFormat depthTextureFormat;
/// The pixel format of the input motion texture for this denoiser scaler.
@property (nonatomic, readonly) MTLPixelFormat motionTextureFormat;
/// The pixel format of the input diffuse albedo texture for this denoiser scaler.
@property (nonatomic, readonly) MTLPixelFormat diffuseAlbedoTextureFormat;
/// The pixel format of the input specular albedo for this denoiser scaler.
@property (nonatomic, readonly) MTLPixelFormat specularAlbedoTextureFormat;
/// The pixel format of the input normal texture for this denoiser scaler.
@property (nonatomic, readonly) MTLPixelFormat normalTextureFormat;
/// The pixel format of the input normal texture for this denoiser scaler.
@property (nonatomic, readonly) MTLPixelFormat roughnessTextureFormat;
/// The pixel format of the input specular hit distance texture for this denoiser scaler.
@property (nonatomic, readonly) MTLPixelFormat specularHitDistanceTextureFormat;
/// The pixel format of the input denoise strength mask texture for this denoiser scaler.
@property (nonatomic, readonly) MTLPixelFormat denoiseStrengthMaskTextureFormat;
/// The pixel format of the input transparency overlay texture for this denoiser scaler.
@property (nonatomic, readonly) MTLPixelFormat transparencyOverlayTextureFormat;
/// The pixel format of the input reactive mask texture for this denoiser scaler.
@property (nonatomic, readonly) MTLPixelFormat reactiveMaskTextureFormat;
/// The pixel format of the output color texture for this denoiser scaler.
@property (nonatomic, readonly) MTLPixelFormat outputTextureFormat;
/// The width, in pixels, of the input color texture for the scaler.
@property (nonatomic, readonly) NSUInteger inputWidth;
/// The height, in pixels, of the input color texture for the scaler.
@property (nonatomic, readonly) NSUInteger inputHeight;
/// The width, in pixels, of the output color texture for the scaler.
@property (nonatomic, readonly) NSUInteger outputWidth;
/// The height, in pixels, of the output color texture for the scaler.
@property (nonatomic, readonly) NSUInteger outputHeight;
/// The minimum input content scale this scaler supports.
@property (nonatomic, readonly) float inputContentMinScale;
/// The maximum input content scale this scaler supports.
@property (nonatomic, readonly) float inputContentMaxScale;

/// The world-to-view transformation matrix this scaler uses as part of its operation.
@property (nonatomic) simd_float4x4 worldToViewMatrix;
/// The view-to-clip coordinates transformation matrix this scaler uses as part of its operation.
@property (nonatomic) simd_float4x4 viewToClipMatrix;

/// An optional fence that this denoiser scaler waits for and updates.
///
/// Use this property for synchronizing access to untracked resources.
@property (nonatomic, retain, nullable) id<MTLFence> fence;

@end

/// An upscaling effect that generates a higher resolution texture in a render pass by analyzing multiple input textures
/// over time and removing noise.
///
/// You create instances of this class by calling ``MTLFXTemporalScalerDescriptor/newTemporalScalerWithDevice:``.
///
/// When using instances of objects conforming to this protocol, you configure the different properties it
/// inherits from protocol ``MTLFXTemporalDenoisedScalerBase`` and then call ``encodeToCommandBuffer:`` to
/// encode its work into a Metal command buffer.
///
/// See ``MTLFXTemporalDenoisedScalerBase`` for more details on configuring and using denoiser scalers.
///
API_AVAILABLE(macos(26.0), ios(18.0))
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos)
#endif
@protocol MTLFXTemporalDenoisedScaler <MTLFXTemporalDenoisedScalerBase>

/// Encode this scaler denoiser's work into a command buffer.
///
/// - Parameters:
///    - commandBuffer: A command buffer into which this scaler denoiser encodes work.
///
- (void)encodeToCommandBuffer:(nonnull id<MTLCommandBuffer>)commandBuffer;

@end

