//
//  ARMatteGenerator.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ARFrame;

@protocol MTLTexture;
@protocol MTLCommandBuffer;
@protocol MTLDevice;

NS_ASSUME_NONNULL_BEGIN

/**
 The resolution at which the matte is to be generated.
 @discussion The matte generated per frame can be full resolution of the captured camera image or half resolution. The caller chooses one of the options from ARMatteResolution during initialization.
 */
API_AVAILABLE(ios(13.0))
typedef NS_ENUM(NSInteger, ARMatteResolution) {
    
    /* Matte generated at camera image resolution. */
    ARMatteResolutionFull      = 0,
    
    /* Matte generated at half the camera image resolution. */
    ARMatteResolutionHalf    = 1
    
} NS_SWIFT_NAME(ARMatteGenerator.Resolution);

/**
 An object designed to generate either full resolution or half resolution matte given the ARFrame.
 @discussion The caller initializes the object once and calls the alpha matte generation API for every ARFrame with the captured image and segmentation stencil.
 */
API_AVAILABLE(ios(13.0))
@interface ARMatteGenerator : NSObject

/**
 Initializes an instance of ARMatteGenerator.
 
 @discussion For efficient creation of alpha mattes in real time it is recommended to instantiate this object only once and to generate an alpha matte for every incoming frame.
 @see ARFrame
 @see -[ARMatteGenerator generateMatteFromFrame:commandBuffer:]
 @param device The device the filter will run on.
 @param matteResolution The resolution at which the matte is to be generated. Set using one of the values from 'ARMatteResolution'.
 @see ARMatteResolution
 @return Instance of ARMatteGenerator.
 */
- (instancetype)initWithDevice:(id <MTLDevice>)device matteResolution:(ARMatteResolution)matteResolution NS_DESIGNATED_INITIALIZER;

/**
 Generates alpha matte at either full resolution or half the resolution of the captured image.
 
 @param frame Current ARFrame containing camera image and segmentation stencil. The caller is to ensure that a valid segmentation buffer is present.
 @param commandBuffer Metal command buffer for encoding matting related operations. The command buffer is committed by the caller externally.
 @return Alpha matte MTLTexture for the given ARFrame at full resolution or half resolution as chosen by the  caller during initialization.
 */
- (id <MTLTexture>)generateMatteFromFrame:(ARFrame*)frame commandBuffer:(id <MTLCommandBuffer>)commandBuffer;

/**
 Generates dilated depth at the resolution of the segmentation stencil.
 @discussion The caller can use depth information when compositing a virtual object with the captured scene. This API returns the dilated linear depth to the caller. The reprojection of this depth to the caller's scene space is carried out externally.
 @param frame Current ARFrame containing camera image and estimated depth buffer. The caller is to ensure that a valid depth buffer is present.
 @param commandBuffer Metal command buffer for encoding depth dilation operations. The command buffer is committed by the caller externally.
 @return Dilated depth MTLTexture for the given ARFrame at the segmentation stencil resolution. The texture consists of a single channel and is of type float16.
 */
- (id <MTLTexture>)generateDilatedDepthFromFrame:(ARFrame*)frame commandBuffer:(id <MTLCommandBuffer>)commandBuffer;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
