//
//  MPSMatrixSoftmax.h
//  MPSMatrix
//
//  Created by Teemu Rantalaiho on 7/23/17.
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef MPSMatrixSoftmax_h
#define MPSMatrixSoftmax_h

#import <MPSCore/MPSKernel.h>
#import <MPSMatrix/MPSMatrixTypes.h>


/*!
 *  @class      MPSMatrixSoftMax
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   A softmax kernel that operates on matrices.
 *
 *  @discussion A MPSMatrixSoftMax object computes:
 *
 *                  B_ij = Exp { A_ij } / ( Sum_k Exp { A_ik } )
 *
 *              A and B are matrices which are represented by MPSMatrix
 *              objects. This filter computes the same result for MPSMatrices as
 *              MPSCNNSoftMax filter does for MPSImages by interpreting the columns
 *              of the matrix as feature channels, that is the sum runs over column indices.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSMatrixSoftMax : MPSMatrixUnaryKernel

/*! @property   sourceRows
 *
 *  @discussion The number of rows to consider from the source in the operation.
 *              This property is modifiable and defaults to NSUIntegerMax and the number is
 *              adjusted dynamically at kernel encode time (see encodeToCommandBuffer) to
 *              fit into the source matrix available starting from sourceMatrixOrigin.x,
 *              indicating that by default the whole source matrix is used.
 *              If a different size is desired then this should be modified prior to
 *              encoding the kernel. It is the user's responsibility to ensure that the
 *              resultMatrix parameter in encodeToCommandBuffer is large enough
 *              to accommodate the results of this operation, otherwise the results of
 *              the encode call are undefined.
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
 *              encoding the kernel. It is the user's responsibility to ensure that the
 *              resultMatrix parameter in encodeToCommandBuffer is large enough
 *              to accommodate the results of this operation, otherwise the results of
 *              the encode call are undefined.
 *              NOTE: sourceMatrixOrigin and resultMatrixOrigin from MPSMatrixUnaryKernel
 *              can be used to control the starting points in the source and destination
 *              at kernel encode time (see encodeToCommandBuffer).
 */
@property (readwrite, nonatomic) NSUInteger sourceColumns;


/*!
 *  @abstract   Initialize an MPSMatrixSoftMax object on a device for a given size.
 *
 *  @param      device          The device on which the kernel will execute.
 *
 *  @return     A valid MPSMatrixSoftMax object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>) device
NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0) );


/*!
 *  @abstract   Encode a MPSMatrixSoftMax object to a command buffer.
 *
 *  @param      commandBuffer   A valid MTLCommandBuffer to receive the encoded kernel.
 *
 *  @param      inputMatrix     A valid MPSMatrix object which specifies the input matrix.
 *
 *  @param      resultMatrix    A valid MPSMatrix object which specifies the matrix which will
 *                              be overwritten by the result.
 *
 *  @discussion Certain constraints apply to the sizes of the matrices depending on the sizes requested at
 *              initialization time as well as the origins at the time this routine is called:
 *
 *              The result matrix must be large enough to hold a two dimensional array of 'sourceRows' rows and
 *              'sourceColumns' columns beginning at resultMatrixOrigin.
 *
 *              Each matrix within the range specified by batchStart and batchSize, which also specifies
 *              a valid set of matrices within inputMatrix and resultMatrix, will
 *              be processed.
 *
 *              The datatypes of the matrices inputMatrix and resultMatrix must match and be either
 *              MPSDataTypeFloat32 or MPSDataTypeFloat16.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                  inputMatrix: (MPSMatrix * __nonnull) inputMatrix
                 resultMatrix: (MPSMatrix * __nonnull) resultMatrix
MPS_SWIFT_NAME(encode(commandBuffer:inputMatrix:resultMatrix:));


/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSMatrixSoftMax
 *  @param      device      The MTLDevice on which to make the MPSMatrixSoftMax
 *  @return     A new MPSMatrixSoftMax object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

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

@end // MPSMatrixSoftMax


/*!
 *  @class      MPSMatrixLogSoftMax
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   A logarithmic softmax kernel that operates on matrices.
 *
 *  @discussion A MPSMatrixLogSoftMax object computes:
 *
 *                  B_ij = ln { Exp { A_ij } / ( Sum_k Exp { A_ik } ) } = A_ij - ln { Sum_k Exp { A_ik } }
 *
 *              A and B are matrices which are represented by MPSMatrix
 *              objects. This filter computes the same result for MPSMatrices as
 *              MPSCNNLogSoftMax filter does for MPSImages by interpreting the columns
 *              of the matrix as feature channels, that is the sum runs over column indices.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSMatrixLogSoftMax : MPSMatrixSoftMax

@end // MPSMatrixLogSoftMax

/*!
 *  @class      MPSMatrixSoftMaxGradient
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   Computes the gradient corresponding to a forward MPSMatrixSoftMax object.
 *
 *  @discussion A MPSMatrixSoftMaxGradient object computes:
 *
 *                  dL_dX_ij = Y_ij * (dL_dY_ij - sum_k(dL_dY_ik * Y_ik)
 *
 *              Where dL_dX is the resulting gradient of the loss function with respect to
 *              the original input to the forward MPSMatrixSoftMax operation, Y is
 *              the output of the forward MPSMatrixSoftMax operation, and dL_dY is the
 *              gradient of the loss function with respect to Y.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.14), ios(12.0), tvos(12.0))
@interface MPSMatrixSoftMaxGradient : MPSMatrixBinaryKernel

/*! @property   sourceRows
 *
 *  @discussion The number of rows to consider from the sources in the operation.
 *              This property is modifiable and defaults to NSUIntegerMax and the number is
 *              adjusted dynamically at kernel encode time (see encodeToCommandBuffer) to
 *              fit into the source matrices available starting from
 *              [primary/secondary]SourceMatrixOrigin.x, indicating that by default the
 *              whole source matrix is used. If a different size is desired then this should
 *              be modified prior to encoding the kernel. It is the user's responsibility to
 *              ensure that the resultMatrix parameter in encodeToCommandBuffer is large enough
 *              to accommodate the results of this operation, otherwise the results of
 *              the encode call are undefined.
 *              NOTE: primarySourceMatrixOrigin, secondarySourceMatrixOrigin and resultMatrixOrigin
 *              from MPSMatrixBinaryKernel can be used to control the starting points in the primary
 *              source, secondary source, and result matrices respectively.
 */
@property (readwrite, nonatomic) NSUInteger sourceRows;

/*! @property   sourceColumns
 *
 *  @discussion The number of columns to consider from the sources in the operation.
 *              This property is modifiable and defaults to NSUIntegerMax and the number is
 *              adjusted dynamically at kernel encode time (see encodeToCommandBuffer) to
 *              fit into the source matrices available starting from [primary/secondary]SourceMatrixOrigin.y,
 *              indicating that by default the whole source matrix is used.
 *              If a different size is desired then this should be modified prior to
 *              encoding the kernel. It is the user's responsibility to ensure that the
 *              resultMatrix parameter in encodeToCommandBuffer is large enough
 *              to accommodate the results of this operation, otherwise the results of
 *              the encode call are undefined.
 *              NOTE: primarySourceMatrixOrigin, secondarySourceMatrixOrigin and resultMatrixOrigin
 *              from MPSMatrixBinaryKernel can be used to control the starting points in the primary
 *              source, secondary source, and result matrices respectively.
 */
@property (readwrite, nonatomic) NSUInteger sourceColumns;


/*!
 *  @abstract   Initialize an MPSMatrixSoftMaxGradient object on a device.
 *
 *  @param      device          The device on which the kernel will execute.
 *
 *  @return     A valid MPSMatrixSoftMaxGradient object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*!
 *  @abstract   Encode a MPSMatrixSoftMaxGradient object to a command buffer.
 *
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded kernel.
 *
 *  @param      gradientMatrix      A MPSMatrix object containing gradient values with respect
 *                                  to the forward operation's output.  dL_dY in the class
 *                                  description.
 *
 *  @param      forwardOutputMatrix A MPSMatrix object containing the output values from the
 *                                  forward operation.  Y in the class description.
 *
 *  @param      resultMatrix        The MPSMatrix object to hold the resulting gradient values
 *                                  with respect to the forward operation's input.  dL_dX in the
 *                                  class description.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
               gradientMatrix: (MPSMatrix * __nonnull) gradientMatrix
          forwardOutputMatrix: (MPSMatrix * __nonnull) forwardOutputMatrix
                 resultMatrix: (MPSMatrix * __nonnull) resultMatrix;


/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSMatrixSoftMaxGradient
 *  @param      device      The MTLDevice on which to make the MPSMatrixSoftMaxGradient
 *  @return     A new MPSMatrixSoftMaxGradient object, or nil if failure.
 */
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

@end // MPSMatrixSoftMaxGradient

/*!
 *  @class      MPSMatrixLogSoftMaxGradient
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   Computes the gradient corresponding to a forward MPSMatrixLogSoftMax object.
 *
 *  @discussion A MPSMatrixLogSoftMaxGradient object computes:
 *
 *                  dL_dX_ij = dL_dY_ij - exp(Y_ij * sum_k(dL_dY_ik))
 *
 *              Where dL_dX is the resulting gradient of the loss function with respect to
 *              the original input to the forward MPSMatrixLogSoftMax operation, Y is
 *              the output of the forward MPSMatrixLogSoftMax operation, and dL_dY is the
 *              gradient of the loss function with respect to Y.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.14), ios(12.0), tvos(12.0))
@interface MPSMatrixLogSoftMaxGradient : MPSMatrixSoftMaxGradient

@end // MPSMatrixLogSoftMaxGradient

#endif /* MPSMatrixSoftmax_h */
