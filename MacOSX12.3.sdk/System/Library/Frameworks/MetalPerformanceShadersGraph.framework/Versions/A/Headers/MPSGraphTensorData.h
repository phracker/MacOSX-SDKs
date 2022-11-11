//
//  MPSGraphTensorData.h
//  MPSGraph
//
//  Created on 2/4/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphTensorData_h
#define MPSGraphTensorData_h

#import <MetalPerformanceShadersGraph/MPSGraphCore.h>
#import <MetalPerformanceShadersGraph/MPSGraphDevice.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class      MPSGraphTensorData
 *  @abstract   Representation of a compute datatype
 *  @discussion MPSGraphTensorData is how we pass data to an MPSGraph, a reference will be taken to your data and used just in time when MPSGraph is run.
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraphTensorData : NSObject

/*! @property   shape
 *  @discussion shape of the tensorData
 */
@property (readonly, copy, nonatomic) MPSShape *shape;

/*! @property   dataType
 *  @discussion dataType of the tensorData
 */
@property (readonly, nonatomic) MPSDataType dataType;

/*! @property   device
 *  @discussion device of the tensorData
 */
@property (readonly, nonatomic) MPSGraphDevice * device;

/*! @abstract   Initialize an MPSGraphTensorData with an NSData on an MPSDevice
 *  @param      device  MPSDevice on which the MPSGraphTensorData exists
 *  @param      data  NSData from which to copy the contents
 *  @param      shape  shape of the output tensor
 *  @param      dataType  dataType of the placeholder tensor
 *  @return     A valid MPSGraphTensorData, or nil if allocation failure.
 */

-(instancetype) initWithDevice:(MPSGraphDevice *) device
                          data:(NSData *) data
                         shape:(MPSShape *) shape
                      dataType:(MPSDataType) dataType;

/*! @abstract   Initialize an MPSGraphTensorData with an MTLBuffer
 *              The device of the MTLBuffer will be used to get the MPSDevice for this MPSGraphTensorData.
 *  @param      buffer  MTLBuffer to be used within the MPSGraphTensorData
 *  @param      shape  shape of the output tensor
 *  @param      dataType  dataType of the placeholder tensor
 *  @return     A valid MPSGraphTensorData, or nil if allocation failure.
 */
-(instancetype) initWithMTLBuffer:(id<MTLBuffer>) buffer
                            shape:(MPSShape *) shape
                         dataType:(MPSDataType) dataType
MPS_SWIFT_NAME( init(_:shape:dataType:) );

/*! @abstract   Initialize an MPSGraphTensorData with an MTLBuffer
 *              The device of the MTLBuffer will be used to get the MPSDevice for this MPSGraphTensorData.
 *  @param      buffer  MTLBuffer to be used within the MPSGraphTensorData
 *  @param      shape  shape of the output tensor
 *  @param      dataType  dataType of the placeholder tensor
 *  @param      rowBytes rowBytes for the fastest moving dimension, must be larger than or equal to sizeOf(dataType) * shape[rank - 1] and must be a multiple of sizeOf(dataType)
 *  @return     A valid MPSGraphTensorData, or nil if allocation failure.
 */
-(instancetype) initWithMTLBuffer:(id<MTLBuffer>) buffer
                            shape:(MPSShape *) shape
                         dataType:(MPSDataType) dataType
                         rowBytes:(NSUInteger) rowBytes
MPS_SWIFT_NAME( init(_:shape:dataType:rowBytes:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/*! @abstract   Initialize an MPSGraphTensorData with an MPSMatrix
 *              The device of the MPSMatrix will be used to get the MPSDevice for this MPSGraphTensorData.
 *  @param      matrix  MPSMatrix to be used within the MPSGraphTensorData
 *  @return     A valid MPSGraphTensorData, or nil if allocation failure.
 *  @note       If matrix.matrices == 1, then a rank 2 tensor is returned, otherwise rank 3.
 */
-(instancetype) initWithMPSMatrix:(MPSMatrix *) matrix
MPS_SWIFT_NAME( init(_:) );

/*! @abstract   Initialize an MPSGraphTensorData with an MPSMatrix enforcing rank of the result.
 *              The device of the MPSMatrix will be used to get the MPSDevice for this MPSGraphTensorData.
 *  @param      matrix  MPSMatrix to be used within the MPSGraphTensorData
 *  @param      rank  The rank of the resulting TensorData tensor. NOTE: must be within { 1, ... ,16 }.
 *  @return     A valid MPSGraphTensorData of given rank, or nil if allocation failure.
 */
-(instancetype) initWithMPSMatrix:(MPSMatrix *) matrix
                             rank:(NSUInteger) rank
MPS_SWIFT_NAME( init(_:rank:) );



/*! @abstract   Initialize an MPSGraphTensorData with an MPSVector
 *              The device of the MPSVector will be used to get the MPSDevice for this MPSGraphTensorData.
 *  @param      vector  MPSVector to be used within the MPSGraphTensorData
 *  @return     A valid MPSGraphTensorData, or nil if allocation failure.
 *  @note       If vector.vectors == 1, then a rank 1 tensor is returned, otherwise rank 2.
 */
-(instancetype) initWithMPSVector:(MPSVector *) vector
MPS_SWIFT_NAME( init(_:) );

/*! @abstract   Initialize an MPSGraphTensorData with an MPSVector  enforcing rank of the result.
 *              The device of the MPSVector will be used to get the MPSDevice for this MPSGraphTensorData.
 *  @param      vector  MPSVector to be used within the MPSGraphTensorData
 *  @param      rank  The rank of the resulting TensorData tensor. NOTE: must be within { 1, ... ,16 }.
 *  @return     A valid MPSGraphTensorData, or nil if allocation failure.
 *  @note       If vector.vectors == 1, then a rank 1 tensor is returned, otherwise rank 2.
 */
-(instancetype) initWithMPSVector:(MPSVector *) vector
                             rank:(NSUInteger) rank
MPS_SWIFT_NAME( init(_:rank:) );



/*! @abstract   Initialize an MPSGraphTensorData with an MPSNDArray
 *              The device of the MPSNDArray will be used to get the MPSDevice for this MPSGraphTensorData.
 *  @param      ndarray  MPSNDArray to be used within the MPSGraphTensorData
 *  @return     A valid MPSGraphTensorData, or nil if allocation failure.
 */
-(instancetype) initWithMPSNDArray:(MPSNDArray *) ndarray
MPS_SWIFT_NAME( init(_:) );

/*! @abstract   Initialize an MPSGraphTensorData with an MPSImage batch, the dataLayout used will be NHWC,
 *              call a transpose or permute to change to a layout of your choice.
 *  @param      imageBatch  The device on which the kernel will run
 *  @return     A valid MPSGraphTensorData, or nil if allocation failure.
 */
-(instancetype) initWithMPSImageBatch:(MPSImageBatch *) imageBatch
MPS_SWIFT_NAME( init(_:) );

/*! @abstract   Return an mpsndarray object will copy contents if the contents are not stored in an MPSNDArray
 *  @return     A valid MPSNDArray, or nil if allocation fails.
 */
-(MPSNDArray *)mpsndarray;

@end

NS_ASSUME_NONNULL_END


#endif /* MPSGraphTensorData_h */
