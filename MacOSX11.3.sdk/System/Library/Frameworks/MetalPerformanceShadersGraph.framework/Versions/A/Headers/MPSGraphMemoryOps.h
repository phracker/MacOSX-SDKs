//
//  MPSGraphMemoryOps.h
//  MetalPerformanceShadersGraph
//
//  Created on 11/10/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#ifndef MPSGraphMemoryOps_h
#define MPSGraphMemoryOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraphVariableOp : MPSGraphOperation

/*! @property   shape
 *  @discussion shape of the variable
 */
@property (readonly, nonnull, nonatomic) MPSShape *shape;

/*! @property   dataType
 *  @discussion dataType of the variable
 */
@property (readonly, nonatomic) MPSDataType dataType;

@end

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MemoryOps)

/*!
 *  @abstract   Create a placeholder op and return the result tensor
 *
 *
 *  @param      shape                            shape of the output tensor, nil shape will result in an unranked tensor
 *  @param      dataType                     dataType of the placeholder tensor
 *  @param      name                              name for the placeholder operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) placeholderWithShape:(MPSShape * _Nullable) shape
                                dataType:(MPSDataType) dataType
                                    name:(NSString * _Nullable) name
MPS_SWIFT_NAME( placeholder(shape:dataType:name:) );

/*!
 *  @abstract   Create a placeholder op and return the result tensor
 *              dataType of the placeholder tensor set to MPSDataTypeFloat32
 *
 *  @param      shape                            shape of the output tensor, nil shape will result in an unranked tensor
 *  @param      name                              name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) placeholderWithShape:(MPSShape * _Nullable) shape
                                    name:(NSString * _Nullable) name
MPS_SWIFT_NAME( placeholder(shape:name:) );


/*!
 *  @abstract   Create a constant op and return the result tensor
 *
 *  @param      data                              data for the tensor, number of bytes should be sizeof(dataType) * numberOfElements
 *  @param      shape                            shape of the output tensor, has to be statically shaped
 *  @param      dataType                     dataType of theconstant tensor
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) constantWithData:(NSData *) data
                               shape:(MPSShape *) shape
                            dataType:(MPSDataType) dataType
MPS_SWIFT_NAME( constant(_:shape:dataType:) );

/*!
 *  @abstract   Create a constant op and return the result tensor
 *
 *  @param      scalar                          scalar to fill the entire tensor values with
 *  @param      dataType                     dataType of the constant tensor
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) constantWithScalar:(double) scalar
                              dataType:(MPSDataType) dataType
MPS_SWIFT_NAME( constant(_:dataType:) );

/*!
 *  @abstract   Create a constant op and return the result tensor
 *
 *  @param      scalar                          scalar to fill the entire tensor values with
 *  @param      shape                            shape of the output tensor. @[], @[@1] or @[@-1] means that the shape will be resolved via shape inference at runtime
 *  @param      dataType                     dataType of the constant tensor
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) constantWithScalar:(double) scalar
                                 shape:(MPSShape *) shape
                              dataType:(MPSDataType) dataType
MPS_SWIFT_NAME( constant(_:shape:dataType:) );

/*!
 *  @abstract   Create a variable op and return the result tensor
 *
 *  @param      data                              data for the tensor, number of bytes should be sizeof(dataType) * numberOfElements
 *  @param      shape                            shape of the output tensor, has to be statically shaped
 *  @param      dataType                     dataType of theconstant tensor
 *  @param      name                              name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) variableWithData:(NSData *) data
                               shape:(MPSShape *) shape
                            dataType:(MPSDataType) dataType
                                name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create a read op which reads at this point of execution of the graph and return the result tensor
 *
 *  @param      variable                     variable resource tensor to read from
 *  @param      name                              name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) readVariable:(MPSGraphTensor *) variable
                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( read(_:name:) );

/*!
 *  @abstract   Create a read op which reads at this point of execution of the graph and return the result tensor
 *
 *  @param      variable                     variable resource tensor to read from
 *  @param      tensor                         tensor to assign to variable
 *  @param      name                              name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphOperation *) assignVariable:(MPSGraphTensor *) variable
                    withValueOfTensor:(MPSGraphTensor *) tensor
                                 name:(NSString * _Nullable) name
MPS_SWIFT_NAME( assign(_:tensor:name:) );


@end


NS_ASSUME_NONNULL_END

#endif /* MPSGraphMemoryOps_h */
