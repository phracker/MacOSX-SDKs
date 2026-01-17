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

/// The class that defines the parameters for a variable.
MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraphVariableOp : MPSGraphOperation

/// The shape of the variable.
@property (readonly, nonnull, nonatomic) MPSShape *shape;

/// The data type of the variable.
@property (readonly, nonatomic) MPSDataType dataType;

@end

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MemoryOps)

/// Creates a placeholder operation and returns the result tensor.
///
/// - Parameters:
///   - shape: The shape of the output tensor. A nil shape will result in an unranked tensor.
///   - dataType: The dataType of the placeholder tensor.
///   - name: The name for the placeholder operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) placeholderWithShape:(MPSShape * _Nullable) shape
                                dataType:(MPSDataType) dataType
                                    name:(NSString * _Nullable) name
MPS_SWIFT_NAME( placeholder(shape:dataType:name:) );

/// Creates a placeholder operation and returns the result tensor with the dataType of the placeholder tensor set to 32 bit float.
///
/// - Parameters:
///   - shape: The shape of the output tensor. A nil shape will result in an unranked tensor.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) placeholderWithShape:(MPSShape * _Nullable) shape
                                    name:(NSString * _Nullable) name
MPS_SWIFT_NAME( placeholder(shape:name:) );


/// Creates a constant op with a given shape and data, and returns the result tensor.
///
/// - Parameters:
///   - data: The data for the tensor. The number of bytes should be sizeof(dataType)numberOfElements.
///   - shape: The shape of the output tensor. This has to be statically shaped.
///   - dataType: The dataType of theconstant tensor.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) constantWithData:(NSData *) data
                               shape:(MPSShape *) shape
                            dataType:(MPSDataType) dataType
MPS_SWIFT_NAME( constant(_:shape:dataType:) );

/// Creates a constant operation and returns the result tensor.
///
/// - Parameters:
///   - scalar: The scalar value to fill the entire tensor values with.
///   - dataType: The dataType of the constant tensor.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) constantWithScalar:(double) scalar
                              dataType:(MPSDataType) dataType
MPS_SWIFT_NAME( constant(_:dataType:) );

/// Creates a constant op with a given shape and returns the result tensor.
///
/// - Parameters:
///   - scalar: The scalar value to fill the entire tensor values with.
///   - shape: The shape of the output tensor.
///   - dataType: The dataType of the constant tensor.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) constantWithScalar:(double) scalar
                                 shape:(MPSShape *) shape
                              dataType:(MPSDataType) dataType
MPS_SWIFT_NAME( constant(_:shape:dataType:) );

/// Creates a complex constant op with the MPSDataTypeComplexFloat32 data type and returns the result tensor.
///
/// - Parameters:
///   - realPart: The real part of the complex scalar to fill the entire tensor values with.
///   - imaginaryPart: The imaginary part of the complex scalar to fill the entire tensor values with.
///   - dataType: The dataType of the constant tensor.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) constantWithRealPart:(double) realPart
                           imaginaryPart:(double) imaginaryPart
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
MPS_SWIFT_NAME( complexConstant(realPart:imaginaryPart:) );

/// Creates a complex constant operation and returns the result tensor.
///
/// - Parameters:
///   - realPart: The real part of the complex scalar to fill the entire tensor values with.
///   - imaginaryPart: The imaginary part of the complex scalar to fill the entire tensor values with.
///   - dataType: The dataType of the constant tensor.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) constantWithRealPart:(double) realPart
                           imaginaryPart:(double) imaginaryPart
                                dataType:(MPSDataType) dataType
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
MPS_SWIFT_NAME( complexConstant(realPart:imaginaryPart:dataType:) );

/// Creates a complex constant op with a given shape and returns the result tensor.
///
/// - Parameters:
///   - realPart: The real part of the complex scalar to fill the entire tensor values with.
///   - imaginaryPart: The imaginary part of the complex scalar to fill the entire tensor values with.
///   - shape: The shape of the output tensor. This has to be statically shaped.
///   - dataType: The dataType of the constant tensor.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) constantWithRealPart:(double) realPart
                           imaginaryPart:(double) imaginaryPart
                                   shape:(MPSShape *) shape
                                dataType:(MPSDataType) dataType
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
MPS_SWIFT_NAME( complexConstant(realPart:imaginaryPart:shape:dataType:) );

/// Creates a variable operation and returns the result tensor.
///
/// - Parameters:
///   - data: The data for the tensor. The number of bytes should be sizeof(dataType)numberOfElements.
///   - shape: The shape of the output tensor. This has to be statically shaped.
///   - dataType: The dataType of the constant tensor.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) variableWithData:(NSData *) data
                               shape:(MPSShape *) shape
                            dataType:(MPSDataType) dataType
                                name:(NSString * _Nullable) name;

/// Creates a variable from an input tensor.
///
/// - Parameters:
///   - tensor: The tensor from which to form the variable.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
    -(MPSGraphTensor *) variableFromTensorWithTensor:(MPSGraphTensor * _Nonnull) tensor
                                                name:(NSString * _Nullable) name
MPS_SWIFT_NAME( variableFromTensor(_:name:) )
MPS_AVAILABLE_STARTING(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0));

/// Creates a read op which reads at this point of execution of the graph and returns the result tensor.
///
/// - Parameters:
///   - variable: The variable resource tensor to read from.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) readVariable:(MPSGraphTensor *) variable
                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( read(_:name:) );

/// Creates an assign operation which writes at this point of execution of the graph.
///
/// - Parameters:
///   - variable: The variable resource tensor to assign to.
///   - tensor: The tensor to assign to the variable.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphOperation *) assignVariable:(MPSGraphTensor *) variable
                    withValueOfTensor:(MPSGraphTensor *) tensor
                                 name:(NSString * _Nullable) name
MPS_SWIFT_NAME( assign(_:tensor:name:) );


@end


NS_ASSUME_NONNULL_END

#endif /* MPSGraphMemoryOps_h */
