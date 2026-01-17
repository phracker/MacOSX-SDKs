//
//  CNRenderingSession.h
//  Cinematic
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <Metal/Metal.h>

@class CNRenderingSessionFrameAttributes;
@class CNRenderingSessionAttributes;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CNRenderingQuality) {
    CNRenderingQualityThumbnail,
    CNRenderingQualityPreview,
    CNRenderingQualityExport,
    CNRenderingQualityExportHigh,
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);


NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
/// Movie-wide information required by the rendering session.
@interface CNRenderingSessionAttributes : NSObject

/// Load rendering session attributes from an asset asynchronously.
+ (void)loadFromAsset:(AVAsset *)asset
    completionHandler:(void (^)(CNRenderingSessionAttributes * _Nullable sessionAttributes,
                                NSError * _Nullable error))completionHandler;

/// Rendering version used to render the original.
@property (readonly) NSInteger renderingVersion;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
/// Frame-specific information required to render a frame in a rendering session.
@interface CNRenderingSessionFrameAttributes : NSObject <NSCopying, NSMutableCopying>

/// Initialize rendering frame attributes from a sample buffer read from a cinematic metadata track.
/// - Parameters:
///   - sampleBuffer: A sample buffer read from the timed cinematic metadata track of a cinematic asset.
///   - sessionAttributes: Rendering session attributes loaded from a cinematic asset.
- (nullable instancetype)initWithSampleBuffer:(CMSampleBufferRef)sampleBuffer
                            sessionAttributes:(CNRenderingSessionAttributes *)sessionAttributes;

/// Initialize rendering frame attributes from a timed metadata group read from a cinematic metadata track.
/// - Parameters:
///   - metadataGroup: An AVTimedMetadataGroup read from the timed cinematic metadata track of a cinematic asset.
///   - sessionAttributes: Rendering session attributes loaded from a cinematic asset.
- (nullable instancetype)initWithTimedMetadataGroup:(AVTimedMetadataGroup *)metadataGroup
                                  sessionAttributes:(CNRenderingSessionAttributes *)sessionAttributes;

/// The disparity value which represents the focus plane at which the rendered image should be in focus.
///
/// A larger disparity results in the focus plane being closer to the camera. The scale and offset of disparity is not defined.
/// It is best practice to obtain disparity values from detections or by interpolation between known disparity values.
@property float focusDisparity;

/// The f-stop value which inversely affects the aperture used to render the image.
///
/// A smaller f/ number results in larger bokeh and a shallower depth of field in the rendered image.
@property float fNumber;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface CNRenderingSession : NSObject

-(instancetype)initWithCommandQueue:(id<MTLCommandQueue>)commandQueue
                  sessionAttributes:(CNRenderingSessionAttributes *)sessionAttributes
                 preferredTransform:(CGAffineTransform)preferredTransform
                            quality:(CNRenderingQuality)quality;

@property (readonly, strong) id<MTLCommandQueue> commandQueue;
@property (readonly, strong) CNRenderingSessionAttributes *sessionAttributes;
@property (readonly) CGAffineTransform preferredTransform;
@property (readonly) CNRenderingQuality quality;


/// Encode a command to render a shallow depth of field (SDoF) image to a pixel buffer.
/// - Parameters:
///   - commandBuffer: the metal command buffer on which to encode the command
///   - frameAttributes: controls the focus distance and aperture of the rendering
///   - sourceImage: a pixel buffer read from the cinematicVideoTrack
///   - sourceDisparity: a pixel buffer read from the cinematicDisparityTrack
///   - destinationImage: the pixel buffer to which the SDoF image is rendered
/// - Returns: whether encoding the render command was successful
- (BOOL)encodeRenderToCommandBuffer:(id<MTLCommandBuffer>)commandBuffer
                    frameAttributes:(CNRenderingSessionFrameAttributes *)frameAttributes
                        sourceImage:(CVPixelBufferRef)sourceImage
                    sourceDisparity:(CVPixelBufferRef)sourceDisparity
                   destinationImage:(CVPixelBufferRef)destinationImage;

/// Encode a command to render a shallow depth of field (SDoF) image to a metal texture as RGBA.
/// - Parameters:
///   - commandBuffer: the metal command buffer on which to encode the command
///   - frameAttributes: controls the focus distance and aperture of the rendering
///   - sourceImage: a pixel buffer read from the cinematicVideoTrack
///   - sourceDisparity: a pixel buffer read from the cinematicDisparityTrack
///   - destinationRGBA: a metal texture to which the SDoF image is rendered in RGBA format
/// - Returns: whether encoding the render command was successful
- (BOOL)encodeRenderToCommandBuffer:(id<MTLCommandBuffer>)commandBuffer
                    frameAttributes:(CNRenderingSessionFrameAttributes *)frameAttributes
                        sourceImage:(CVPixelBufferRef)sourceImage
                    sourceDisparity:(CVPixelBufferRef)sourceDisparity
                    destinationRGBA:(id<MTLTexture>)destinationRGBA;

/// Encode a command to render a shallow depth of field (SDoF) image to two metal textures as luma and chroma.
/// - Parameters:
///   - commandBuffer: the metal command buffer on which to encode the command
///   - frameAttributes: controls the focus distance and aperture of the rendering
///   - sourceImage: a pixel buffer read from the cinematicVideoTrack
///   - sourceDisparity: a pixel buffer read from the cinematicDisparityTrack
///   - destinationLuma: a metal texture to which the luma of the SDoF image is rendered
///   - destinationChroma: a metal texture to which the chroma of the SDoF image is rendered
/// - Returns: whether encoding the render command was successful
- (BOOL)encodeRenderToCommandBuffer:(id<MTLCommandBuffer>)commandBuffer
                    frameAttributes:(CNRenderingSessionFrameAttributes *)frameAttributes
                        sourceImage:(CVPixelBufferRef)sourceImage
                    sourceDisparity:(CVPixelBufferRef)sourceDisparity
                    destinationLuma:(id<MTLTexture>)destinationLuma
                  destinationChroma:(id<MTLTexture>)destinationChroma;

/// The pixel format types supported for the input source.
///
/// Use with kCVPixelBufferPixelFormatTypeKey in the video compositor's sourcePixelBufferAttributes dictionary when implementing AVVideoCompositing.
///
@property (class, readonly, strong) NSArray<NSNumber *> *sourcePixelFormatTypes;

/// The pixel format types supported for the output destination.
///
/// Use with kCVPixelBufferPixelFormatTypeKey in the video compositor's requiredPixelBufferAttributesForRenderContext dictionary when implementing AVVideoCompositing.
///
@property (class, readonly, strong) NSArray<NSNumber *> *destinationPixelFormatTypes;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
