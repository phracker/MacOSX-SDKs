/*!
 *  @header MPSImageKeypoint.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2017 Apple Inc. All rights reserved.
 *  @abstract MetalPerformanceShaders Keypoint filters
 */

#ifndef MPS_MPSImageKeypoint_h
#define MPS_MPSImageKeypoint_h

#include <MPSImage/MPSImageKernel.h>
#include <simd/simd.h>

/*!
 *  @brief      Specifies information to find the keypoints in an image.
 */
typedef struct
{
    NSUInteger maximumKeypoints;    /**< maximum number of keypoints */
    float minimumThresholdValue;    /**< minimum threshold value -  value between 0.0 and 1.0f */
} MPSImageKeypointRangeInfo;

/*!
 *  @brief      Specifies keypoint information.
 */
typedef struct
{
    vector_ushort2 keypointCoordinate;  /**< keypoint (x, y) coordinate */
    float keypointColorValue;           /**< keypoint color value */
} MPSImageKeypointData;


/*!
 *  @class      MPSImageFindKeypoints
 *  @discussion The MPSImageFindKeypoints kernel is used to find a list of keypoints whose values are >= minimumPixelThresholdValue
 *              in MPSImageKeypointRangeInfo. The keypoints are generated for a specified region in the image.  
 *              The pixel format of the source image must be MTLPixelFormatR8Unorm.
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSImageFindKeypoints : MPSKernel

/*! @property   keypointRangeInfo
 *  @abstract   Return a structure describing the keypoint range info
 *  @discussion Returns a MPSImageKeypointRangeInfo structure 
 */
@property (readonly, nonatomic)  MPSImageKeypointRangeInfo keypointRangeInfo;

/*!
 *  @abstract Specifies information to find keypoints in an image.
 *  @param    device    The device the filter will run on
 *  @param    info      Pointer to the MPSImageKeypointRangeInfo struct
 *  @return   A valid MPSImageFindKeypoints object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                  info: (const MPSImageKeypointRangeInfo * __nonnull) info NS_DESIGNATED_INITIALIZER;

/* You must use initWithDevice:keypointRangeInfo: instead */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device            NS_UNAVAILABLE;

/*! @abstract NSSecureCoding compatability
 *  @discussion While the standard NSSecureCoding/NSCoding method
 *              -initWithCoder: should work, since the file can't
 *              know which device your data is allocated on, we
 *              have to guess and may guess incorrectly.  To avoid
 *              that problem, use initWithCoder:device instead.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSKernel
 *  @param      device      The MTLDevice on which to make the MPSKernel
 *  @return     A new MPSKernel object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*!
 *  @abstract Encode the filter to a command buffer using a MTLComputeCommandEncoder.
 *  @discussion The filter will not begin to execute until after the command
 *  buffer has been enqueued and committed.
 *
 *  @param  commandBuffer               A valid MTLCommandBuffer.
 *  @param  source                      A valid MTLTexture containing the source image for the filter.
 *  @param  regions                     An array of rectangles that describe regions in the image.
 *                                      The list of keypoints is generated for each individual rectangle specifed.
 *  @param  keypointCountBuffer         The list of keypoints for each specified region
 *  @param  keypointCountBufferOffset   Byte offset into keypointCountBufferOffset buffer at which to write the keypoint results.
 *                                      Must be a multiple of 32 bytes.
 *  @param  keypointDataBuffer          A valid MTLBuffer to receive the keypoint data results for each rectangle.
 *                                      The keypoint data for keypoints in each rectangle are stored consecutively.
 *                                      The keypoint data for each rectangle starts at the following offset:
 *                                          MPSImageKeypointRangeInfo.maximumKeyPoints * rectangle index
 *  @param  keypointDataBufferOffset    Byte offset into keypointData buffer at which to write the keypoint results.
 *                                      Must be a multiple of 32 bytes.
 *
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                sourceTexture: (nonnull id <MTLTexture>) source
                      regions: (const MTLRegion * __nonnull) regions
              numberOfRegions: (NSUInteger) numberOfRegions
          keypointCountBuffer: (nonnull id <MTLBuffer>) keypointCountBuffer
    keypointCountBufferOffset: (NSUInteger) keypointCountBufferOffset
           keypointDataBuffer: (nonnull id <MTLBuffer>) keypointDataBuffer
     keypointDataBufferOffset: (NSUInteger) keypointDataBufferOffset;

@end  /* MPSImageFindKeypoints */

#endif  /* MPSImageKeypoint.h */

