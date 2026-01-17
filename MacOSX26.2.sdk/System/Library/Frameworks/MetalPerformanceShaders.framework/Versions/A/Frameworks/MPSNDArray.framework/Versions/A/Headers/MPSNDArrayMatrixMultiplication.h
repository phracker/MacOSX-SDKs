/*!
 *  @header MPSNDArrayMatrixMultiplication.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2016 Apple Inc. All rights reserved.
 *  @abstract MetalPerformanceShaders filter base classes
 */
#ifndef MPSNDArrayMatrixMultiplication_h
#define MPSNDArrayMatrixMultiplication_h

#import <MPSCore/MPSKernel.h>
#import <MPSMatrix/MPSMatrixTypes.h>
#import <MPSCore/MPSNDArray.h>
#import <MPSNDArray/MPSNDArrayKernel.h>

/*!
 *  @class      MPSNDArrayMatrixMultiplication
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   A matrix multiplication kernel operating on MPSNDArray objects.
 *
 *  @discussion A MPSNDArrayMatrixMultiplication object computes, for each 2-D matrix within
 *              a 4-D MPSNDArray object:
 *
 *                  D = alpha * A * B + beta * C
 *
 *              A, B, C, and D are matrices which are represented by objects stored
 *              in the two most major dimensions of the MPSNDArray. alpha and beta
 *              are scalar values (of the same data type as values of D and C) which
 *              are applied as shown above.
 *
 *              If an input's 3rd or 4th dimension is 1 its data will be broadcast as
 *              appropriate to the remaining input's 3rd or 4th dimension respectively.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13), macCatalyst(13), tvos(13))
@interface MPSNDArrayMatrixMultiplication : MPSNDArrayMultiaryKernel

/*! @property   alpha
 *
 *  @discussion The scale factor to apply to the product.  Specified in double
 *              precision.  Will be converted to the appropriate precision in the
 *              implementation subject to rounding and/or clamping as necessary.
 *              Defaults to 1.0 at initialization time.
 */
@property (readwrite, nonatomic) double alpha;

/*! @property   beta
 *
 *  @discussion The scale factor to apply to the addend if available.  Specified in double
 *              precision.  Will be converted to the appropriate precision in the
 *              implementation subject to rounding and/or clamping as necessary.
 *              Defaults to 1.0 at initialization time.
 */
@property (readwrite, nonatomic) double beta;

@end    // MPSNDArrayMatrixMultiplication

#endif /* MPSNDArrayMatrixMultiplication_h */
