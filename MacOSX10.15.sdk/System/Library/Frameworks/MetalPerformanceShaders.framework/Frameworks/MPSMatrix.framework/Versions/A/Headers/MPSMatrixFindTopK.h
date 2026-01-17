//
//  MPSMatrixFindTopK.h
//  MPSMatrix
//
//  Created by Teemu Rantalaiho on 8/11/17.
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef MPSMatrixFindTopK_h
#define MPSMatrixFindTopK_h

#import <MPSCore/MPSKernel.h>
#import <MPSMatrix/MPSMatrixTypes.h>


/*!
 *  @class      MPSMatrixFindTopK
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   A kernel that find top-K values and their corresponding indices withing a row of a matrix
 *
 *  @discussion A MPSMatrixFindTopK object computes finds the 'k' largest values within
 *              a row of a matrix and returns the value found and the index of the entry
 *              in the source matrix. This operation is performed independently on the
 *              rows and matrices in batch of the source matrix.
 *
 */

MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface MPSMatrixFindTopK : MPSMatrixUnaryKernel

/*! @property   sourceRows
 *
 *  @discussion The number of rows to consider from the source in the operation.
 *              This property is modifiable and defaults to NSUIntegerMax and the number is
 *              adjusted dynamically at kernel encode time (see encodeToCommandBuffer) to
 *              fit into the source matrix available starting from sourceMatrixOrigin.x,
 *              indicating that by default the whole source matrix is used.
 *              If a different size is desired then this should be modified prior to
 *              encoding the kernel.
 *              It is the user's responsibility to ensure that the resultIndexMatrix and resultValueMatrix
 *              parameters in encodeToCommandBuffer are large enough to accommodate the results of this
 *              operation, otherwise the results of the encode call are undefined.
 *              NOTE: sourceMatrixOrigin and resultMatrixOrigin from MPSMatrixUnaryKernel
 *              can be used to control the starting points in the source and destination
 *              at kernel encode time (see encodeToCommandBuffer).
 */
@property (readwrite, nonatomic) NSUInteger sourceRows;

/*! @property   sourceColumns
 *
 *  @discussion The number of columns to consider from the source in the operation.
 *              This property is modifiable and defaults to NSUIntegerMax and the number is
 *              adjusted dynamically at kernel encode time (see encodeToCommandBuffer) to
 *              fit into the source matrix available starting from sourceMatrixOrigin.y,
 *              indicating that by default the whole source matrix is used.
 *              If a different size is desired then this should be modified prior to
 *              encoding the kernel.
 *              It is the user's responsibility to ensure that the resultIndexMatrix and resultValueMatrix
 *              parameters in encodeToCommandBuffer are large enough to accommodate the results of this
 *              operation, otherwise the results of the encode call are undefined.
 *              NOTE: sourceMatrixOrigin and resultMatrixOrigin from MPSMatrixUnaryKernel
 *              can be used to control the starting points in the source and destination
 *              at kernel encode time (see encodeToCommandBuffer).
 */
@property (readwrite, nonatomic) NSUInteger sourceColumns;

/*! @property   indexOffset
 *
 *  @discussion Specifies a number that will be added to all the indices written to
 *              resultIndexMatrix in encodeToCommandBuffer. This value can be used
 *              to offset later computations for example by adding the value for
 *              the source matrix column offset sourceMatrixOrigin.y.
 *              Example: Let numberOfTopKValues be 3, let the source be the following:
 *
 *                  source = [ 6.0, 3.0, 8.0, 1.0, 9.0, 4.0, 5.0 ]
 *
 *              and let the sourceMatrixOrigin.y = 2.
 *
 *              Then if indexOffset = 2 then the result value and result index matrices will be:
 *
 *                  result values  = [ 9.0, 8.0, 5.0 ]
 *                  result indices = [  4 ,  2 ,  6  ],
 *
 *              which gives the user indices into the original source matrix.
 *
 *              On the other hand if the indexOffset = 0 then the results  are as follows:
 *
 *                  result values  = [ 9.0, 8.0, 5.0 ]
 *                  result indices = [  2 ,  0 ,  4  ],
 *
 *              which on the other hand gives the user indices into the submatrix starting
 *              from sourceMatrixOrigin.y == 2.
 *
 *              This property is modifiable and defaults to 0. If a different behavior
 *              is desired then this should be modified prior to encoding the kernel.
 */
@property (readwrite, nonatomic) NSUInteger indexOffset;

/*! @property   numberOfTopKValues
 *
 *  @discussion The number of highest values (and their indices) to be found in each row
 *              by the kernel. This property is initialized in the kernel initialization call
 *              initWithDevice, but can be modified before encoding the kernel.
 *              Must be less or equal to 16 and requesting more values results in undefined behavior.
 *              It is the user's responsibility to ensure that the resultIndexMatrix and resultValueMatrix
 *              parameters in encodeToCommandBuffer are large enough to accommodate the results of this
 *              operation, otherwise the results of the encode call are undefined.
 */
@property (readwrite, nonatomic) NSUInteger numberOfTopKValues;


/*!
 *  @abstract   Initialize an MPSMatrixFindTopK object on a device for a given size.
 *
 *  @param      device              The device on which the kernel will execute.
 *  @param      numberOfTopKValues  The number of largest values to find from each row,
 *                                  must be less or equal to 16.
 *
 *  @return     A valid MPSMatrixFindTopK object or nil, if failure.
 */

// FIXME: Fix availability macros to 10.14 and 12.0 once we get there
-(nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>) device
                    numberOfTopKValues: (NSUInteger) numberOfTopKValues
NS_DESIGNATED_INITIALIZER;



/*!
 @discussion Use the above initialization method instead.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;


/*!
 *  @abstract   Encode a MPSMatrixFindTopK object to a command buffer.
 *
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded kernel.
 *
 *  @param      inputMatrix         A valid MPSMatrix object which specifies the input matrix.
 *
 *  @param      resultIndexMatrix   A valid MPSMatrix object which specifies the matrix which will
 *                                  be overwritten by the result indices.
 *                                  This matrix must have datatype MPSDataTypeUInt32.
 *  @param      resultValueMatrix   A valid MPSMatrix object which specifies the matrix which will
 *                                  be overwritten by the result values.
 *
 *  @discussion Certain constraints apply to the sizes of the matrices depending on the sizes requested at
 *              initialization time as well as the origins at the time this routine is called:
 *
 *              Both result matrices must be large enough to hold a two dimensional array of 'sourceRows' rows and
 *              'numberOfTopKValues' columns beginning at resultMatrixOrigin.
 *
 *              The source matrix must be large enough to contain at least 'numberOfTopKValues' values
 *              starting from sourceMatrixOrigin.y.
 *
 *              Each matrix within the range specified by batchStart and batchSize, which also specifies a valid
 *              set of matrices within inputMatrix, resultIndexMatrix and resultValueMatrix, will be processed.
 *
 *              The datatypes of the matrices inputMatrix and resultValueMatrix must match and be either
 *              MPSDataTypeFloat32 or MPSDataTypeFloat16.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                  inputMatrix: (MPSMatrix * __nonnull) inputMatrix
            resultIndexMatrix: (MPSMatrix * __nonnull) resultIndexMatrix
            resultValueMatrix: (MPSMatrix * __nonnull) resultValueMatrix
MPS_SWIFT_NAME(encode(commandBuffer:inputMatrix:resultIndexMatrix:resultValueMatrix:));



/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSMatrixFindTopK
 *  @param      device      The MTLDevice on which to make the MPSMatrixFindTopK
 *  @return     A new MPSMatrixFindTopK object, or nil if failure.
 */

// FIXME: Fix availability macros to 10.14 and 12.0 once we get there
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*!
 *  @abstract   Make a copy of this kernel for a new device - @see MPSKernel
 *  @param      zone        The NSZone in which to allocate the object
 *  @param      device      The device for the new MPSKernel. If nil, then use
 *                          self.device.
 *  @result     a pointer to a copy of this MPSKernel. This will fail, returning
 *              nil if the device is not supported. Devices must be
 *              MTLFeatureSet_iOS_GPUFamily2_v1 or later.
 */

- (nonnull instancetype) copyWithZone:(nullable NSZone *)zone
                               device:(nullable id <MTLDevice>) device;

@end // MPSMatrixFindTopK


#endif /* MPSMatrixFindTopK_h */
