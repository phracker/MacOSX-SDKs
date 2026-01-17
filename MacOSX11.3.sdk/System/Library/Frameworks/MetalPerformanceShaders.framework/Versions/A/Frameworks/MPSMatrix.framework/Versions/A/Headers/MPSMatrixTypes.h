//
//  MPSMatrixTypes.h
//  MPS
//
//  Created on 8/20/16.
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef MPSMatrixTypes_h
#define MPSMatrixTypes_h

#ifndef __METAL_VERSION__
#   include <stdint.h>  // For uint32_t.
#endif

// Hide the rest of the header from metal shading language
#ifndef __METAL_VERSION__

#import <MPSCore/MPSKernel.h>
#import <MPSCore/MPSCoreTypes.h>
#import <MPSCore/MPSKernelTypes.h>
#import <MPSCore/MPSMatrix.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! @class      MPSMatrixUnaryKernel
 *  @dependency This depends on Metal.framework
 *  @discussion A MPSMatrixUnaryKernel consumes one MPSMatrix and produces one MPSMatrix.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface MPSMatrixUnaryKernel : MPSKernel

/*! @property   sourceMatrixOrigin
 *
 *  @discussion The origin, relative to [0, 0] in the source matrix, at which to
 *              start reading values.  This property is modifiable and defaults to
 *              [0, 0] at initialization time.  If a different origin is desired then
 *              this should be modified prior to encoding the kernel.  The z value
 *              must be 0.
 */
@property (readwrite, nonatomic) MTLOrigin sourceMatrixOrigin;

/*! @property   resultMatrixOrigin
 *
 *  @discussion The origin, relative to [0, 0] in the result matrix, at which to
 *              start writing results.  This property is modifiable and defaults
 *              to [0, 0] at initialization time.  If a different origin is desired
 *              then this should be modified prior to encoding the kernel.  The z
 *              value must be 0.
 */
@property (readwrite, nonatomic) MTLOrigin resultMatrixOrigin;

/*! @property   batchStart
 *
 *  @discussion The index of the first matrix in the batch.  This property is
 *              modifiable and defaults to 0 at initialization time.  If
 *              batch processing should begin at a different matrix this value
 *              should be modified prior to encoding the kernel.
 */
@property (readwrite, nonatomic) NSUInteger batchStart;

/*! @property   batchSize
 *
 *  @discussion The number of matrices in the batch to process.  This property
 *              is modifiable and by default allows all matrices available at
 *              encoding time to be processed.  If a single matrix should be
 *              processed set this value to 1.
 */
@property (readwrite, nonatomic) NSUInteger batchSize;

@end // MPSMatrixUnaryKernel

/*!
 *  @class      MPSMatrixBinaryKernel
 *  @dependency This depends on Metal.framework
 *  @discussion A MPSMatrixBinaryKernel consumes two MPSMatrix objects and produces
 *              one MPSMatrix object.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface MPSMatrixBinaryKernel : MPSKernel
/*! @property   primarySourceMatrixOrigin
 *
 *  @discussion The origin, relative to [0, 0] in the primary source matrix, at which to
 *              start reading values.  This property is modifiable and defaults to
 *              [0, 0] at initialization time.  If a different origin is desired then
 *              this should be modified prior to encoding the kernel.  The z value
 *              must be 0.
 */
@property (readwrite, nonatomic) MTLOrigin primarySourceMatrixOrigin;

/*! @property   secondarySourceMatrixOrigin
 *
 *  @discussion The origin, relative to [0, 0] in the secondary source matrix, at which to
 *              start reading values.  This property is modifiable and defaults to
 *              [0, 0] at initialization time.  If a different origin is desired then
 *              this should be modified prior to encoding the kernel.  The z value
 *              must be 0.
 */
@property (readwrite, nonatomic) MTLOrigin secondarySourceMatrixOrigin;

/*! @property   resultMatrixOrigin
 *
 *  @discussion The origin, relative to [0, 0] in the result matrix, at which to
 *              start writing results.  This property is modifiable and defaults
 *              to [0, 0] at initialization time.  If a different origin is desired
 *              then this should be modified prior to encoding the kernel.  The z
 *              value must be 0.
 */
@property (readwrite, nonatomic) MTLOrigin resultMatrixOrigin;

/*! @property   batchStart
 *
 *  @discussion The index of the first matrix in the batch.  This property is
 *              modifiable and defaults to 0 at initialization time.  If
 *              batch processing should begin at a different matrix this value
 *              should be modified prior to encoding the kernel.
 */
@property (readwrite, nonatomic) NSUInteger batchStart;

/*! @property   batchSize
 *
 *  @discussion The number of matrices in the batch to process.  This property
 *              is modifiable and by default allows all matrices available at
 *              encoding time to be processed.  If a single matrix should be
 *              processed set this value to 1.
 */
@property (readwrite, nonatomic) NSUInteger batchSize;
@end // MPSMatrixBinaryKernel

#ifdef __cplusplus
}   // extern "C"
#endif

#endif // __METAL_VERSION__
#endif /* MPSMatrixTypes_h */
