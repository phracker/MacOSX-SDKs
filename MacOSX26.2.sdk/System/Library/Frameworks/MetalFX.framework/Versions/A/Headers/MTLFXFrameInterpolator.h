//
//  MTLFXFrameInterpolator.h
//  MetalFX
//
//  Copyright (c) 2024 Apple Inc. All rights reserved.
//

#import <Metal/Metal.h>


#import <Metal/MTL4Compiler.h>

// Forward declaration of Metal4FX interpolator and scaler.
@protocol MTL4FXFrameInterpolator;
@protocol MTL4FXTemporalScaler;
@protocol MTL4FXTemporalDenoisedScaler;
// Forward declaration.
@protocol MTLFXFrameInterpolator;
@protocol MTLFXTemporalScaler;
@protocol MTLFXTemporalDenoisedScaler;

#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos)
#endif
/// A set of properties that configure a frame interpolator, and a factory method that creates the effect.
///
/// A frame interpolator inspects two frames your game or app renders and, based on their properties, generates
/// an extra frame at a fraction of the cost, helping you to increase your frame rate.
///
/// When you configure this descriptor, set the properties that determine the pixel format for each texture to the
/// respective format of the texture you later assign to the scaler. For example, make sure that the format to which
/// you set the ``colorTextureFormat`` property matches the format of the texture you later assign to the interpolator's
/// ``MTLFXFrameInterpolatorDescriptor/colorTexture`` property.
API_AVAILABLE(macos(26.0), ios(26.0))
@interface MTLFXFrameInterpolatorDescriptor : NSObject <NSCopying>

/// The pixel format of the input color texture for the frame interpolator you create with this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat colorTextureFormat;

/// The pixel format of the output color texture for the frame interpolator you create with this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat outputTextureFormat;

/// The pixel format of the input depth texture for the frame interpolator you create with this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat depthTextureFormat;

/// The pixel format of the input motion texture for the frame interpolator you create with this descriptor.
@property (readwrite, nonatomic) MTLPixelFormat motionTextureFormat;
/// The pixel format for the frame interpolator of an input texture containing your game's custom UI.
@property (readwrite, nonatomic, setter=setUITextureFormat:) MTLPixelFormat uiTextureFormat;



@property (nonatomic, retain, nullable) id<MTLFXFrameInterpolatableScaler> scaler;
/// The width, in pixels, of the input motion and depth texture for the frame interpolator.
@property (readwrite, nonatomic) NSUInteger inputWidth;
/// The height, in pixels, of the input motion and depth texture for the frame interpolator.
@property (readwrite, nonatomic) NSUInteger inputHeight;
/// The width, in pixels, of the output color texture for the frame interpolator.
@property (readwrite, nonatomic) NSUInteger outputWidth;
/// The height, in pixels, of the output color texture for the frame interpolator.
@property (readwrite, nonatomic) NSUInteger outputHeight;

/// Creates a frame interpolator instance for a Metal device.
///
/// - Parameters:
///    - device: The Metal device that creates the frame interpolator.
/// - Returns:
///    A new frame interpolator instance upon success, or `nil` otherwise.
- (nullable id <MTLFXFrameInterpolator>)newFrameInterpolatorWithDevice:(nonnull id<MTLDevice>)device;

/// Creates a frame interpolator instance for a Metal device.
///
/// - Parameters:
///    - device: The Metal device that creates the frame interpolator.
///    - compiler: A compiler instance this method can use to build pipeline state objects.
/// - Returns:
///    A new frame interpolator instance upon success, or `nil` otherwise.
- (nullable id <MTL4FXFrameInterpolator>)newFrameInterpolatorWithDevice:(nonnull id<MTLDevice>)device compiler:(nonnull id<MTL4Compiler>)compiler;

/// Queries whether a Metal device supports frame interpolation compatible with a Metal 4 command buffer.
///
/// - Parameters:
///    - device: The GPU device for which this methods tests support.
///
/// - Returns: <doc://com.apple.documentation/documentation/swift/true> if the device supports frame interpolation for
///             Metal 4, <doc://com.apple.documentation/documentation/swift/false> otherwise.
+ (BOOL)supportsMetal4FX:(nonnull id<MTLDevice>)device;

/// Queries whether a Metal device supports frame interpolation.
///
/// - Parameters:
///    - device: The GPU device for which this methods tests support.
///
/// - Returns: <doc://com.apple.documentation/documentation/swift/true> if the device supports frame interpolation,
///             <doc://com.apple.documentation/documentation/swift/false> otherwise.
+ (BOOL)supportsDevice:(nonnull id<MTLDevice>)device;

@end

/// A common abstraction to all frame interpolators.
///
/// This protocol defines properties common to all frame interpolators. You access these properties through
/// any frame interpolator instance you create by calling construction methods such as
/// ``MTLFXFrameInterpolatorDescriptor/newFrameInterpolatorWithDevice:``.
///
/// ## Conforming to texture usage requirements
/// 
/// Frame interpolator instances expose properties, such as ``colorTextureUsage``, that indicate requirements for
/// your textures to be compatible with it. These properties indicate the minimum set of ``MTLTextureUsage`` bits
/// that you are responsible for setting in your texture descriptors for this frame interpolator to use them.
///
/// Your game or app can set extra usage bits on your textures without losing compatibility, as long at its maintains
/// the minimum set the interpolator requests.
///
/// ## Assigning input and output textures
///
/// When you use an instance of a class that conforms to this protocol, you typically set its input and output textures,
/// as well as other properties, and then encode its work to a command buffer.
///
/// MetalFX doesn't track that you assign the same texture instances to each property across different batches of work,
/// the only requirement is that you provide textures that match the pixel formats and dimensions you specify in the
/// ``MTLFXFrameInterpolatorDescriptor`` descriptor instance that creates the scaler instance.
///
/// ## Encoding work
///
/// Once you configure all properties for the current frame of your game or app, you indicate to the scaler instance
/// into which command buffer it encodes its work. You achieve this by calling, for example,
/// ``MTLFXFrameInterpolator/encodeToCommandBuffer:``.
///
API_AVAILABLE(macos(26.0), ios(26.0))
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos)
#endif
@protocol MTLFXFrameInterpolatorBase <NSObject>

/// The minimal texture usage options that your app’s input color texture needs in order to support this frame interpolator.
@property (nonatomic, readonly) MTLTextureUsage colorTextureUsage;
/// The minimal texture usage options that your app’s output color texture needs in order to support this frame interpolator.
@property (nonatomic, readonly) MTLTextureUsage outputTextureUsage;
/// The minimal texture usage options that your app’s input depth texture needs in order to support this frame interpolator.
@property (nonatomic, readonly) MTLTextureUsage depthTextureUsage;
/// The minimal texture usage options that your app’s input motion texture needs in order to support this frame interpolator.
@property (nonatomic, readonly) MTLTextureUsage motionTextureUsage;
/// The minimal texture usage options that your app’s input UI texture needs in order to support this frame interpolator.
@property (nonatomic, readonly) MTLTextureUsage uiTextureUsage;

/// The pixel format of the input color texture for this frame interpolator.
@property (nonatomic, readonly) MTLPixelFormat colorTextureFormat;
/// The pixel format of the input depth texture for this frame interpolator.
@property (nonatomic, readonly) MTLPixelFormat depthTextureFormat;
/// The pixel format of the input motion texture for this frame interpolator.
@property (nonatomic, readonly) MTLPixelFormat motionTextureFormat;
/// The pixel format of the output color texture for this frame interpolator.
@property (nonatomic, readonly) MTLPixelFormat outputTextureFormat;

/// The width, in pixels, of the input color texture for the frame interpolator.
@property (nonatomic, readonly) NSUInteger inputWidth;
/// The height, in pixels, of the input color texture for the frame interpolator.
@property (nonatomic, readonly) NSUInteger inputHeight;
/// The width, in pixels, of the output color texture for the frame interpolator.
@property (nonatomic, readonly) NSUInteger outputWidth;
/// The height, in pixels, of the output color texture for the frame interpolator.
@property (nonatomic, readonly) NSUInteger outputHeight;
/// The pixel format of the input UI texture for the frame interpolator.
@property (nonatomic, readonly) MTLPixelFormat uiTextureFormat;

/// The color texture that this frame interpolator evaluates.
///
/// You are responsible for ensuring the usage and pixel format of the texture you assign to this property matches the
/// texture usage ``colorTextureUsage`` requests and the pixel format that ``colorTextureFormat`` requests.
@property (nonatomic, retain, nullable) id<MTLTexture> colorTexture;

/// The previous color texture for this frame interpolator during the last call to encode work into a command buffer.
///
/// The frame interpolator typically uses the previous color texture as part of its operation. When you call
/// ``MTLFXFrameInterpolator/encodeToCommandBuffer:`` and its ``shouldResetHistory`` property is
/// <doc://com.apple.documentation/documentation/swift/false>, then you are responsible for assigning to this property
/// the data that in ``colorTexture`` from the previous call to ``MTLFXFrameInterpolator/encodeToCommandBuffer:``.
///
/// Additionally, you are responsible for ensuring the usage and pixel format of the texture you assign to this property matches the
/// texture usage ``colorTextureUsage`` requests and the pixel format that ``colorTextureFormat`` requests.
@property (nonatomic, retain, nullable) id<MTLTexture> prevColorTexture;


/// The depth texture this frame interpolator evaluates.
///
/// You are responsible for ensuring the usage and pixel format of the texture you assign to this property matches the
/// texture usage ``depthTextureUsage`` requests and the pixel format that ``depthTextureFormat`` requests.
@property (nonatomic, retain, nullable) id<MTLTexture> depthTexture;

/// The motion texture this frame interpolator evaluates.
///
/// You are responsible for ensuring the usage and pixel format of the texture you assign to this property matches the
/// texture usage ``motionTextureUsage`` requests and the pixel format that ``motionTextureFormat`` requests.
@property (nonatomic, retain, nullable) id<MTLTexture> motionTexture;

/// The horizontal scale factor the frame interpolator applies to the input motion texture.
///
/// The frame interpolator converts the horizontal component of each value in ``motionTexture`` into fragment (pixel)
/// coordinates by multiplying it by this property’s value.
///
/// If you set this property's value to `1.0`, this interpolator expects that each pixel's motion vector points
/// to the location where that pixel is in the ``prevColorTexture``. For example, in Metal's standard device coordinates
/// where `(0,0)` represents the upper-left corner of the framebuffer, the motion vectors for an object that moves down
/// and to the right in the ``colorTexture`` by `10` pixels would be `(-10,-10)`.
@property (nonatomic) float motionVectorScaleX;

/// The vertical scale factor the frame interpolator applies to the input motion texture.
///
/// The frame interpolator converts the horizontal component of each value in ``motionTexture`` into fragment (pixel)
/// coordinates by multiplying it by this property’s value.
///
/// If you set this property's value to `1.0`, this interpolator expects that each pixel's motion vector points
/// to the location where that pixel is in the ``prevColorTexture``. For example, in Metal's standard device coordinates
/// where `(0,0)` represents the upper-left corner of the framebuffer, the motion vectors for an object that moves down
/// and to the right in the ``colorTexture`` by `10` pixels would be `(-10,-10)`.
@property (nonatomic) float motionVectorScaleY;


/// The length of the time interval, in seconds, between time of current and previous frame.
@property (readwrite, nonatomic) float deltaTime;

/// The near plane distance that corresponds to the frustrum that renders the scene into the color buffer.
@property (readwrite, nonatomic) float nearPlane;

/// The far plane distance that corresponds to the frustrum that renders the scene into the color buffer.
@property (readwrite, nonatomic) float farPlane;

/// The vertical field of view angle, in degrees, of the camera that renders the scene into the color buffer.
///
/// In a 3D game, you set this value to the field of view you use to create your perspective matrix.
@property (readwrite, nonatomic) float fieldOfView;

/// The ratio between width and height of the screen.
///
/// In a 3D game, you set this value to the same aspect ratio you use to create your perspective matrix, which is
/// typically `width/height`.
@property (readwrite, nonatomic) float aspectRatio;

/// An optional texture containing your game's custom UI that this frame interpolator evaluates.
///
/// The frame interpolator uses this property to overlay your custom UI on any frame data it produces into ``outputTexture``.
///
/// Use property ``uiTextureComposited`` to indicate to this frame interpolator if this texture contains a precomposition of
/// ``colorTexture``and UI.
@property (nonatomic, retain, nullable, setter=setUITexture:) id<MTLTexture> uiTexture;


/// The horizontal component of the subpixel sampling coordinate you use to generate the color texture input.
///
/// This property indicates the horizontal pixel offset this interpolator samples to return to the frame's reference frame.
@property (nonatomic) float jitterOffsetX;

/// The vertical component of the subpixel sampling coordinate you use to generate the color texture input.
///
/// This property indicates the vertical pixel offset this interpolator samples to return to the frame's reference frame.
@property (nonatomic) float jitterOffsetY;


/// A Boolean value that controls whether this frame interpolator interprets the color texture to include your game's custom UI.
///
/// Set this property to <doc://com.apple.documentation/documentation/swift/true> when property ``uiTexture`` contains
/// a precomposition of any custom UI image on top of the color image.
///
/// When you enable this property, the frame interpolator decomposites the color image ``colorTexture`` references from
/// the UI ``uiTexture`` references before compositing the UI on to the ``outputTexture``.
///
/// This property's default value is <doc://com.apple.documentation/documentation/swift/false>.
@property (readwrite, nonatomic, getter=isUITextureComposited, setter=setIsUITextureComposited:) BOOL uiTextureComposited;



/// A Boolean property indicating whether to reset history.
///
/// Set this property to <doc://com.apple.documentation/documentation/swift/true> to invalidate history, for example
/// when there is a scene cut in your game.
///
/// When you set this property to <doc://com.apple.documentation/documentation/swift/false>, you are responsible for
/// ensuring the property ``prevColorTexture`` contains frame data corresponding to that in ``colorTexture`` during
/// your previous call to ``MTLFXFrameInterpolator/encodeToCommandBuffer:``.
@property (nonatomic) BOOL shouldResetHistory;

/// The output texture into which this frame interpolator writes its output.
///
/// You are responsible for providing a texture with a private `storageMode` to this property.
@property (nonatomic, retain, nullable) id<MTLTexture> outputTexture;

/// An optional fence that this frame interpolator waits for and updates.
///
/// Use this property for synchronizing access to untracked resources.
@property (nonatomic, retain, nullable) id<MTLFence> fence;

/// A Boolean value that indicates whether the depth texture uses zero to represent the farthest distance.
///
/// This property's default value is <doc://com.apple.documentation/documentation/swift/true>.
@property (readwrite, nonatomic, getter=isDepthReversed) BOOL depthReversed;

@end

/// An effect that generates textures by interpolating two input textures.
///
/// You create instances of this class by calling ``MTLFXFrameInterpolatorDescriptor/newFrameInterpolatorWithDevice:``.
///
/// When using instances of objects conforming to this protocol, you configure the different properties it
/// inherits from protocol ``MTLFXFrameInterpolatorBase`` and then call ``encodeToCommandBuffer:`` to
/// encode its work into a Metal command buffer.
///
/// See ``MTLFXFrameInterpolatorBase`` for more details on configuring and using frame interpolators.
///
API_AVAILABLE(macos(26.0), ios(26.0))
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos)
#endif
@protocol MTLFXFrameInterpolator <MTLFXFrameInterpolatorBase>

/// Encode this frame interpolator's work into a command buffer.
///
/// - Parameters:
///    - commandBuffer: A command buffer into which this frame interpolator encodes work.
///    
- (void)encodeToCommandBuffer:(nonnull id<MTLCommandBuffer>)commandBuffer;

@end


