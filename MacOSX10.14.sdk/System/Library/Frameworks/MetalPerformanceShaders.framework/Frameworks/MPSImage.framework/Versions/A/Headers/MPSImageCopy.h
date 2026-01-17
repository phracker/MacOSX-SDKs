/*!
 *  @header MPSImageCopy.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2017 Apple Inc. All rights reserved.
 *  @abstract MetalPerformanceShaders histogram filters
 */

#ifndef MPS_MPSImageCopy_h
#define MPS_MPSImageCopy_h

#include <MPSCore/MPSImage.h>
#include <MPSImage/MPSImageKernel.h>
#include <MPSMatrix/MPSMatrix.h>
#include <simd/simd.h>

/*!
 *  @class      MPSImageCopyToMatrix
 *  @discussion The MPSImageCopyToMatrix copies image data to a MPSMatrix.
 *              The image data is stored in a row of a matrix.  The dataLayout
 *              specifies the order in which the feature channels in the MPSImage
 *              get stored in the matrix.  If MPSImage stores a batch of images,
 *              the images are copied into multiple rows, one row per image.
 *
 *              The number of elements in a row in the matrix must be >= image width * 
 *              image height * number of featureChannels in the image.
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSImageCopyToMatrix : MPSKernel

/*! @property   destinationMatrixOrigin
 *
 *  @discussion The origin, relative to [0, 0] in the destination matrix, at which to
 *              start writing results.  This property is modifiable and defaults
 *              to [0, 0] at initialization time.  If a different origin is desired
 *              then this should be modified prior to encoding the kernel.  The z
 *              value must be 0.
 */
@property (readwrite, nonatomic) MTLOrigin destinationMatrixOrigin;

/*! @property   destinationMatrixBatchIndex
 *
 *  @discussion The index of the destination matrix in the batch.  This property is
 *              modifiable and defaults to 0 at initialization time.  
 */
@property (readwrite, nonatomic) NSUInteger destinationMatrixBatchIndex;

/*! @property   dataLayout
 *  @abstract   The data layout to use
 *  @discussion Returns the data layout.  When copying from a MPSImage to a MPSMatrix, this
 *              describes the order in which the image values are stored in the buffer associated
 *              with the MPSMatrix.
 *              Default: MPSDataLayoutFeatureChannelsxHeightxWidth
 */
@property (readonly, nonatomic)  MPSDataLayout dataLayout;

/*!
 *  @abstract Initialize a MPSMatrixCopy object on a device
 *  @param    device        The device the kernel will run on
 *  @param    dataLayout    The data layout
 *  @return   A valid MPSMatrixCopy object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                            dataLayout: (MPSDataLayout) dataLayout NS_DESIGNATED_INITIALIZER;

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
 *  @abstract Encode a kernel that copies a MPSImage to a MPSMatrix into a command buffer
 *            using a MTLComputeCommandEncoder.
 *  @discussion The kernel copies feature channels from sourceImage to the buffer
 *              associated with destinationMatrix.  The kernel will not begin to execute until
 *              after the command buffer has been enqueued and committed.
 *
 *              NOTE: The destinationMatrix.dataType must match the feature channel data type in sourceImage.
 *
 *  @param  commandBuffer       A valid MTLCommandBuffer.
 *  @param  sourceImage         A valid MPSImage describing the image to copy from.
 *  @param  destinationMatrix   A valid MPSMatrix or MPSTemporaryMatrix object describing the matrix to copy to.
 *
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                  sourceImage: (nonnull MPSImage *) sourceImage
            destinationMatrix: (nonnull MPSMatrix *) destinationMatrix
        MPS_SWIFT_NAME(encode(commandBuffer:sourceImage:destinationMatrix:));

/*!
 *  @abstract Encode a kernel that copies a MPSImageBatch to a MPSMatrix into a command buffer
 *            using a MTLComputeCommandEncoder.
 *  @discussion The kernel copies feature channels from sourceImage to the buffer
 *              associated with destinationMatrix.  The kernel will not begin to execute until
 *              after the command buffer has been enqueued and committed.
 *              Each image will be copied to its own row in the matrix, starting with row
 *              destinationMatrixOrigin.x.
 *
 *              NOTE: The destinationMatrix.dataType must match the feature channel data type in sourceImage.
 *              NOTE: All the images in the source batch should be of the same size and have numberOfImages = 1.
 *
 *
 *  @param  commandBuffer       A valid MTLCommandBuffer.
 *  @param  sourceImages        A valid MPSImageBatch describing the images to copy from.
 *  @param  destinationMatrix   A valid MPSMatrix or MPSTemporaryMatrix object describing the matrix to copy to.
 *
 */
-(void) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                      sourceImages: (nonnull MPSImageBatch *) sourceImages
                 destinationMatrix: (nonnull MPSMatrix *) destinationMatrix
    MPS_SWIFT_NAME(encodeBatch(commandBuffer:sourceImages:destinationMatrix:))
    MPS_AVAILABLE_STARTING(macos(10.14), ios(12.0), tvos(12.0));




@end  /* MPSImageCopy */

/*!
 *  @class      MPSMatrixCopyToImage
 *  @discussion The MPSMatrixCopyToImage copies matrix data to a MPSImage.
 *              The operation is the reverse of MPSImageCopyToMatrix.
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.14), ios(12.0), tvos(12.0))
@interface  MPSMatrixCopyToImage : MPSKernel

/*! @property   sourceMatrixOrigin
 *
 *  @discussion The origin, relative to [0, 0] in the source matrix.
 *              This property is modifiable and defaults
 *              to [0, 0] at initialization time.  If a different origin is desired
 *              then this should be modified prior to encoding the kernel.  The z
 *              value must be 0.
 */
@property (readwrite, nonatomic) MTLOrigin sourceMatrixOrigin;

/*! @property   sourceMatrixBatchIndex
 *
 *  @discussion The index of the source matrix in the batch.  This property is
 *              modifiable and defaults to 0 at initialization time.
 */
@property (readwrite, nonatomic) NSUInteger sourceMatrixBatchIndex;

/*! @property   dataLayout
 *  @abstract   The data layout to use
 *  @discussion Returns the data layout.  When copying from a MPSMatrix to a MPSImage, this
 *              describes the order in which the image values are to be stored in the buffer associated
 *              with the MPSMatrix.
 *              Default: MPSDataLayoutFeatureChannelsxHeightxWidth
 */
@property (readonly, nonatomic)  MPSDataLayout dataLayout;

/*!
 *  @abstract Initialize a MPSMatrixCopyToImage object on a device
 *  @param    device        The device the kernel will run on
 *  @param    dataLayout    The data layout
 *  @return   A valid MPSMatrixCopyToImage object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                            dataLayout: (MPSDataLayout) dataLayout NS_DESIGNATED_INITIALIZER;

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
 *  @abstract Encode a kernel that copies a MPSMatrix to a MPSImage into a command buffer
 *            using a MTLComputeCommandEncoder.
 *  @discussion The kernel copies feature channels from sourceMatrix to the destinationImage.
 *              The kernel will not begin to execute until
 *              after the command buffer has been enqueued and committed.
 *
 *              NOTE: The sourceMatrix.dataType must match the feature channel data type in destinationImage.
 *
 *  @param  commandBuffer       A valid MTLCommandBuffer.
 *  @param  sourceMatrix        A valid MPSMatrix or MPSTemporaryMatrix object describing the source matrix.
 *  @param  destinationImage    A valid MPSImage describing the image to copy to.
 *
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                 sourceMatrix: (nonnull MPSMatrix *) sourceMatrix
             destinationImage: (nonnull MPSImage *) destinationImage
MPS_SWIFT_NAME(encode(commandBuffer:sourceMatrix:destinationImage:));


/*!
 *  @abstract Encode a kernel that copies a MPSMatrix to a MPSImageBatch into a command buffer
 *            using a MTLComputeCommandEncoder.
 *  @discussion The kernel copies feature channels from sourceImage to the buffer
 *              associated with destinationMatrix.  The kernel will not begin to execute until
 *              after the command buffer has been enqueued and committed.
 *              Each image will be copied to its own row in the matrix, starting with row
 *              destinationMatrixOrigin.x.
 *
 *              NOTE: The destinationMatrix.dataType must match the feature channel data type in sourceImage.
 *              NOTE: All the images in the source batch should be of the same size and have numberOfImages = 1.
 *
 *
 *  @param  commandBuffer       A valid MTLCommandBuffer.
 *  @param  sourceMatrix        A valid MPSMatrix or MPSTemporaryMatrix object describing the source matrix.
 *  @param  destinationImages   A valid MPSImageBatch describing the images to copy to.
 *
 */
-(void) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                      sourceMatrix: (nonnull MPSMatrix *) sourceMatrix
                 destinationImages: (nonnull MPSImageBatch *) destinationImages
MPS_SWIFT_NAME(encodeBatch(commandBuffer:sourceMatrix:destinationImages:))
MPS_AVAILABLE_STARTING(macos(10.14), ios(12.0), tvos(12.0));




@end  /* MPSMatrixCopyToImage */



#endif  /* MPSImageCopy.h */
