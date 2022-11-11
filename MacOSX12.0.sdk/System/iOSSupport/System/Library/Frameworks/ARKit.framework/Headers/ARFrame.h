//
//  ARFrame.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>
#import <UIKit/UIKit.h>
#import <simd/simd.h>
#import <ARKit/ARHitTestResult.h>
#import <ARKit/ARRaycastQuery.h>

#import <ARKit/ARGeoTrackingTypes.h>

@class ARAnchor;
@class ARCamera;
@class ARLightEstimate;
@class ARPointCloud;
@class AVDepthData;
@class ARBody2D;
@class ARDepthData;

@protocol MTLTexture;

NS_ASSUME_NONNULL_BEGIN

/**
 Segmentation classes which defines a pixel's semantic label.
 @discussion When running a configuration with 'ARFrameSemanticPersonSegmentation' every pixel in the
 segmentationBuffer on the ARFrame will conform to one of these classes.
 @see -[ARConfiguration setFrameSemantics:]
 @see -[ARFrame segmentationBuffer]
*/
API_AVAILABLE(ios(13.0))
typedef NS_ENUM(uint8_t, ARSegmentationClass) {

     /* Pixel has been not been classified. */
    ARSegmentationClassNone      = 0,

    /* Pixel has been classified as person. */
    ARSegmentationClassPerson    = 255

} NS_SWIFT_NAME(ARFrame.SegmentationClass);

/**
 A value describing the world mapping status for the area visible in a given frame.
 */
API_AVAILABLE(ios(12.0))
typedef NS_ENUM(NSInteger, ARWorldMappingStatus) {
    /** World mapping is not available. */
    ARWorldMappingStatusNotAvailable,
    
    /** World mapping is available but has limited features.
     For the device's current position, the session’s world map is not recommended for relocalization. */
    ARWorldMappingStatusLimited,
    
    /** World mapping is actively extending the map with the user's motion.
     The world map will be relocalizable for previously visited areas but is still being updated for the current space. */
    ARWorldMappingStatusExtending,
    
    /** World mapping has adequately mapped the visible area.
     The map can be used to relocalize for the device's current position. */
    ARWorldMappingStatusMapped
} NS_SWIFT_NAME(ARFrame.WorldMappingStatus);

/**
 An object encapsulating the state of everything being tracked for a given moment in time.
 @discussion The model provides a snapshot of all data needed to render a given frame.
 */
API_AVAILABLE(ios(11.0))
@interface ARFrame : NSObject <NSCopying>

/**
 A timestamp identifying the frame.
 */
@property (nonatomic, readonly) NSTimeInterval timestamp;


/**
 The frame’s captured image.
 */
@property (nonatomic, readonly) CVPixelBufferRef capturedImage;

/**
 A tileable texture that contains image noise matching the current camera streams
 noise properties.
 
 @discussion A camera stream depicts image noise that gives the captured image
    a grainy look and varies with light conditions.
 The variations are stored along the depth dimension of the camera grain texture
 and can be selected at runtime using the camera grain intensity of the current frame.
 */
@property (nonatomic, nullable, readonly) id<MTLTexture> cameraGrainTexture API_AVAILABLE(ios(13.0));

/**
 The frame’s camera grain intensity in range 0 to 1.
 
 @discussion A camera stream depicts image noise that gives the captured image
 a grainy look and varies with light conditions.
 The camera grain intensity can be used to select a texture slice from the frames
 camera grain texture.
 */
@property (nonatomic, readonly) float cameraGrainIntensity API_AVAILABLE(ios(13.0));

/**
 The frame’s captured depth data.
 @discussion Depth data is only provided with face tracking on frames where depth data was captured.
 */
@property (nonatomic, strong, nullable, readonly) AVDepthData *capturedDepthData;

/**
 A timestamp identifying the depth data.
 */
@property (nonatomic, readonly) NSTimeInterval capturedDepthDataTimestamp;

/**
 The camera used to capture the frame’s image.
 @discussion The camera provides the device’s position and orientation as well as camera parameters.
 */
@property (nonatomic, copy, readonly) ARCamera *camera;

/**
 A list of anchors in the scene.
 */
@property (nonatomic, copy, readonly) NSArray<__kindof ARAnchor *> *anchors;

/**
 A light estimate representing the light in the scene.
 @discussion Returns nil if there is no light estimation.
 */
@property (nonatomic, strong, nullable, readonly) ARLightEstimate *lightEstimate;

/**
 Feature points in the scene with respect to the frame’s origin.
 @discussion The feature points are only provided for configurations using world tracking.
 */
@property (nonatomic, strong, nullable, readonly) ARPointCloud *rawFeaturePoints;

/**
 The status of world mapping for the area visible to the frame.
 @discussion This can be used to identify the state of the world map for the visible area and if additional scanning
 should be done before saving a world map.
 */
@property (nonatomic, readonly) ARWorldMappingStatus worldMappingStatus API_AVAILABLE(ios(12.0));

/**
 A buffer that represents the segmented content of the capturedImage.
 @discussion In order to identify to which class a pixel has been classified one needs to compare its intensity value with the values
 found in `ARSegmentationClass`.
 @see ARSegmentationClass
 @see -[ARConfiguration setFrameSemantics:]
*/
@property (nonatomic, nullable, readonly) CVPixelBufferRef segmentationBuffer API_AVAILABLE(ios(13.0));

/**
 A buffer that represents the estimated depth values for a performed segmentation.
 @discussion For each non-background pixel in the segmentation buffer the corresponding depth value can be accessed in this buffer.
 @see -[ARConfiguration setFrameSemantics:]
 @see -[ARFrame segmentationBuffer]
 */
@property (nonatomic, nullable, readonly) CVPixelBufferRef estimatedDepthData API_AVAILABLE(ios(13.0));

/**
 A detected body in the current frame.
 @see -[ARConfiguration setFrameSemantics:]
 */
@property (nonatomic, nullable, readonly) ARBody2D *detectedBody API_AVAILABLE(ios(13.0));


/**
 The status of geo tracking.
 */
@property (nonatomic, strong, nullable, readonly) ARGeoTrackingStatus *geoTrackingStatus API_AVAILABLE(ios(14.0));


/**
 Scene depth data.
 @see ARFrameSemanticSceneDepth.
 @see -[ARConfiguration setFrameSemantics:]
 */
@property (nonatomic, strong, nullable, readonly) ARDepthData *sceneDepth API_AVAILABLE(ios(14.0));

/**
 Scene depth data, smoothed for temporal consistency.
 @see ARFrameSemanticSmoothedSceneDepth.
 @see -[ARConfiguration setFrameSemantics:]
 */
@property (nonatomic, strong, nullable, readonly) ARDepthData *smoothedSceneDepth API_AVAILABLE(ios(14.0));

/**
 Searches the frame for objects corresponding to a point in the captured image.
 
 @discussion A 2D point in the captured image’s coordinate space can refer to any point along a line segment
 in the 3D coordinate space. Hit-testing is the process of finding objects in the world located along this line segment.
 @param point A point in the image-space coordinate system of the captured image.
 Values should range from (0,0) - upper left corner to (1,1) - lower right corner.
 @param types The types of results to search for.
 @return An array of all hit-test results sorted from nearest to farthest.
 */
- (NSArray<ARHitTestResult *> *)hitTest:(CGPoint)point types:(ARHitTestResultType)types API_DEPRECATED("Use [ARSession raycast:]", ios(11.0, 14.0));

/**
 Creates a raycast query originating from the point on the captured image, aligned along the center of the field of view of the camera.
 @discussion A 2D point in the captured image’s coordinate space and the field of view of the frame's camera is used to create a ray in the 3D cooridnate space originating at the point.
 @param point A point in the image-space coordinate system of the captured image.
 Values should range from (0,0) - upper left corner to (1,1) - lower right corner.
 @param target Type of target where the ray should terminate.
 @param alignment Alignment of the target.
 */
- (ARRaycastQuery *)raycastQueryFromPoint:(CGPoint)point allowingTarget:(ARRaycastTarget)target alignment:(ARRaycastTargetAlignment)alignment API_AVAILABLE(ios(13.0));

/**
 Returns a display transform for the provided viewport size and orientation.
 
 @discussion The display transform can be used to convert normalized points in the image-space coordinate system
 of the captured image to normalized points in the view’s coordinate space. The transform provides the correct rotation
 and aspect-fill for presenting the captured image in the given orientation and size.
 @param orientation The orientation of the viewport.
 @param viewportSize The size of the viewport.
 */
- (CGAffineTransform)displayTransformForOrientation:(UIInterfaceOrientation)orientation viewportSize:(CGSize)viewportSize;


/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
