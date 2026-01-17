//
//  MPSGraphArithmeticOps.h
//  MetalPerformanceShadersGraph
//
//  Created on 11/10/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#ifndef MPSGraphArithmeticOps_h
#define MPSGraphArithmeticOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN


MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphArithmeticOps)


#pragma mark - UnaryArithmeticOps

/// Copies the input tensor values into the output, behaving as an identity operation.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object which is a copy of the input.
-(MPSGraphTensor *) identityWithTensor:(MPSGraphTensor *) tensor
                                  name:(NSString * _Nullable) name;

/// Applies the natural exponent to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) exponentWithTensor:(MPSGraphTensor *) tensor
                                  name:(NSString * _Nullable) name;

/// Applies an exponent with base 2 to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) exponentBase2WithTensor:(MPSGraphTensor *) tensor
                                       name:(NSString * _Nullable) name;

/// Applies an exponent with base 10 to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) exponentBase10WithTensor:(MPSGraphTensor *) tensor
                                        name:(NSString * _Nullable) name;

/// Computes the natural logarithm to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) logarithmWithTensor:(MPSGraphTensor *) tensor
                                   name:(NSString * _Nullable) name;

/// Computes the logarithm with base 2 to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) logarithmBase2WithTensor:(MPSGraphTensor *) tensor
                                        name:(NSString * _Nullable) name;

/// Computes the logarithm with base 10 to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) logarithmBase10WithTensor:(MPSGraphTensor *) tensor
                                         name:(NSString * _Nullable) name;

/// Applies the square operation to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) squareWithTensor:(MPSGraphTensor *) tensor
                                name:(NSString * _Nullable) name;

/// Applies the square root operation to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) squareRootWithTensor:(MPSGraphTensor *) tensor
                                    name:(NSString * _Nullable) name;

/// Applies the reciprocal square root operation to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) reciprocalSquareRootWithTensor:(MPSGraphTensor *) tensor
                                              name:(NSString * _Nullable) name
MPS_SWIFT_NAME( reciprocalSquareRoot(_:name:) )
MPS_AVAILABLE_STARTING(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0));

/// Applies the reverse square root operation to the input tensor elements.
///
/// The reverse square root operation is the reciprocal of the square root.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) reverseSquareRootWithTensor:(MPSGraphTensor *) tensor
                                           name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING_BUT_DEPRECATED("reciprocalSquareRootWithTensor",
                                      macos(11.0, 15.0), ios(14.0, 18.0), tvos(14.0, 18.0));

/// Applies the reciprocal operation to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) reciprocalWithTensor:(MPSGraphTensor *) tensor
                                    name:(NSString * _Nullable) name;

/// Returns the absolute values of the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) absoluteWithTensor:(MPSGraphTensor *) tensor
                                  name:(NSString * _Nullable) name;

/// Returns the absolute square of the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation..
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) absoluteSquareWithTensor:(MPSGraphTensor *) tensor
                                        name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
MPS_SWIFT_NAME( absoluteSquare(tensor:name:) );

/// Applies negative to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) negativeWithTensor:(MPSGraphTensor *) tensor
                                  name:(NSString * _Nullable) name;

/// Returns the sign of the input tensor elements.
///
/// This operation returns 1.0 if the correspnding input element is greater than 0,
/// -1.0 if it is lesser than 0, -0.0 if it is equal to -0.0, and
/// +0.0 if it is equal to +0.0.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) signWithTensor:(MPSGraphTensor *) tensor
                              name:(NSString * _Nullable) name;

/// Returns the sign bit of the input tensor elements.
///
/// This operation returns `true` if the sign bit is set for the correspnding floating-point input element,
/// otherwise it returns `false`.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) signbitWithTensor:(MPSGraphTensor *) tensor
                                 name:(NSString * _Nullable) name;

/// Applies the ceiling operation to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) ceilWithTensor:(MPSGraphTensor *) tensor
                              name:(NSString * _Nullable) name;

/// Applies the floor operation to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) floorWithTensor:(MPSGraphTensor *) tensor
                               name:(NSString * _Nullable) name;

/// Rounds the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) roundWithTensor:(MPSGraphTensor *) tensor
                               name:(NSString * _Nullable) name;

/// Rounds the input tensor elements by rounding to nearest even.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) rintWithTensor:(MPSGraphTensor *) tensor
                              name:(NSString * _Nullable) name;

/// Applies the sine operation to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) sinWithTensor:(MPSGraphTensor *) tensor
                             name:(NSString * _Nullable) name;

/// Applies the cosine operation to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) cosWithTensor:(MPSGraphTensor *) tensor
                             name:(NSString * _Nullable) name;

/// Applies the tangent operation to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) tanWithTensor:(MPSGraphTensor *) tensor
                             name:(NSString * _Nullable) name;

/// Applies the hyperbolic sine operation to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) sinhWithTensor:(MPSGraphTensor *) tensor
                              name:(NSString * _Nullable) name;

/// Applies the hyperbolic cosine operation to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) coshWithTensor:(MPSGraphTensor *) tensor
                              name:(NSString * _Nullable) name;

/// Applies the hyperbolic tangent operation to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) tanhWithTensor:(MPSGraphTensor *) tensor
                              name:(NSString * _Nullable) name;

/// Applies the inverse sine operation to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) asinWithTensor:(MPSGraphTensor *) tensor
                              name:(NSString * _Nullable) name;

/// Applies the inverse cosine operation to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) acosWithTensor:(MPSGraphTensor *) tensor
                              name:(NSString * _Nullable) name;

/// Applies the inverse tangent operation to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) atanWithTensor:(MPSGraphTensor *) tensor
                              name:(NSString * _Nullable) name;

/// Applies the inverse hyperbolic sine operation to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) asinhWithTensor:(MPSGraphTensor *) tensor
                               name:(NSString * _Nullable) name;

/// Applies the inverse hyperbolic cosine operation to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) acoshWithTensor:(MPSGraphTensor *) tensor
                               name:(NSString * _Nullable) name;

/// Applies the inverse hyperbolic tangent operation to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) atanhWithTensor:(MPSGraphTensor *) tensor
                               name:(NSString * _Nullable) name;

/// Applies the logical NOT operation to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) notWithTensor:(MPSGraphTensor *) tensor
                             name:(NSString * _Nullable) name;

/// Checks if the input tensor elements are infinite or not.
///
/// If the input tensor element is infinite, the operation returns `true`, else it returns `false`.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) isInfiniteWithTensor:(MPSGraphTensor *) tensor
                                    name:(NSString * _Nullable) name;

/// Checks if the input tensor elements are finite or not.
///
/// If the input tensor element is finite, the operation returns `true`, else it returns `false`.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) isFiniteWithTensor:(MPSGraphTensor *) tensor
                                  name:(NSString * _Nullable) name;

/// Checks if the input tensor elements are `NaN` or not.
///
/// If the input tensor element is `NaN`, the operation returns `true`, else it returns `false`.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) isNaNWithTensor:(MPSGraphTensor *) tensor
                               name:(NSString * _Nullable) name;

/// Applies the error function to the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) erfWithTensor:(MPSGraphTensor *) tensor
                             name:(NSString * _Nullable) name;

/// Applies the truncate operation to the input tensor elements.
///
/// This operation applies the floor operation to positive inputs and ceiling operation to negative inputs.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) truncateWithTensor:(MPSGraphTensor *) tensor
                                  name:(NSString * _Nullable) name
MPS_SWIFT_NAME( truncate(_:name:) )
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// Applies the bitwise NOT operation to the input tensor element.
///
///  This operation only accepts integer tensors.
///
/// - Parameters:
///   - tensor: The input tensor, which must be of integer type.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) bitwiseNOTWithTensor:(MPSGraphTensor *) tensor
                                    name:(NSString * _Nullable) name
MPS_SWIFT_NAME( bitwiseNOT(_:name:) )
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1));

/// Returns the population count of the input tensor elements.
///
///  This operation only accepts integer tensors, and returns the number of bits set in the input element.
///
/// - Parameters:
///   - tensor: The input tensor, which must be of integer type.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) bitwisePopulationCountWithTensor:(MPSGraphTensor *) tensor
                                                name:(NSString * _Nullable) name
MPS_SWIFT_NAME( bitwisePopulationCount(_:name:) )
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1));

/// Returns the complex conjugate of the input tensor elements.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation..
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) conjugateWithTensor:(MPSGraphTensor *) tensor
                                   name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
MPS_SWIFT_NAME( conjugate(tensor:name:) );

#pragma mark - BinaryArithmeticOps

/// Adds two input tensors.
///
/// This operation creates an add operation and returns the result tensor. It supports broadcasting as well. 
/// ```md 
/// resultTensor = primaryTensor + secondaryTensor 
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) additionWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                              secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                         name:(NSString * _Nullable) name
MPS_SWIFT_NAME( addition(_:_:name:) );



/// Subtracts the second input tensor from the first.
///
/// This operation creates a subtract operation and returns the result tensor. It supports broadcasting as well. 
/// ```md 
/// resultTensor = primaryTensor - secondaryTensor 
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) subtractionWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                 secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( subtraction(_:_:name:) );



/// Multiplies two input tensors.
///
/// This operation creates a multiply operation and returns the result tensor. It supports broadcasting as well. 
/// ```md 
/// resultTensor = primaryTensor * secondaryTensor 
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) multiplicationWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                    secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( multiplication(_:_:name:) );

/// Divides the first input tensor by the second.
///
/// This operation creates a divide operation and returns the result tensor. It supports broadcasting as well. 
/// ```md 
/// resultTensor = primaryTensor / secondaryTensor 
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) divisionWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                              secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                         name:(NSString * _Nullable) name
MPS_SWIFT_NAME( division(_:_:name:) );


/// Returns the remainder obtained by dividing the first input tensor by the second.
///
/// This operation creates a modulo operation and returns the result tensor. It supports broadcasting as well. 
/// ```md
/// resultTensor = primaryTensor % secondaryTensor
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) moduloWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                            secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                       name:(NSString * _Nullable) name
MPS_SWIFT_NAME( modulo(_:_:name:) );


/// Returns the elementwise result of raising the first tensor to the power of the second tensor.
///
/// This operation creates a power operation and returns the result tensor. It supports broadcasting as well. 
/// ```md
/// resultTensor = pow(primaryTensor, secondaryTensor)
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) powerWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                           secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( power(_:_:name:) );


/// Returns the elementwise minimum of the input tensors.
///
/// This operation creates a minimum operation and returns the result tensor. It supports broadcasting as well. 
/// ```md
/// resultTensor = min(primaryTensor, secondaryTensor)
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) minimumWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                             secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                        name:(NSString * _Nullable) name
MPS_SWIFT_NAME( minimum(_:_:name:) );


/// Returns the elementwise maximum of the input tensors.
///
/// This operation creates a maximum operation and returns the result tensor. It supports broadcasting as well. 
/// ```md
/// resultTensor = max(primaryTensor, secondaryTensor)
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) maximumWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                             secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                        name:(NSString * _Nullable) name
MPS_SWIFT_NAME( maximum(_:_:name:) );

/// Returns the elementwise minimum of the input tensors, while propagating `NaN` values.
///
/// This operation creates a minimum with `NaN` propagation operation and returns the result tensor. This means that
/// if any of the elementwise operands is `NaN`, the result is `NaN`.
/// It supports broadcasting as well. 
/// ```md 
/// resultTensor = isNaN(primaryTensor) || isNan(secondaryTensor) ? NaN : min(primaryTensor, secondaryTensor) 
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) minimumWithNaNPropagationWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                               secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                                          name:(NSString * _Nullable) name
                                                MPS_SWIFT_NAME( minimumWithNaNPropagation(_:_:name:) )
                                                MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Returns the elementwise maximum of the input tensors, while propagating `NaN` values.
///
/// This operation creates a maximum with `NaN` propagation operation and returns the result tensor. This means that
/// if any of the elementwise operands is `NaN`, the result is `NaN`.
/// It supports broadcasting as well. 
/// ```md 
/// resultTensor = isNaN(primaryTensor) || isNan(secondaryTensor) ? NaN : max(primaryTensor, secondaryTensor) 
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) maximumWithNaNPropagationWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                               secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                                          name:(NSString * _Nullable) name
                                                MPS_SWIFT_NAME( maximumWithNaNPropagation(_:_:name:) )
                                                MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Returns the elementwise equality check of the input tensors.
///
/// This operation creates a equal operation and returns the result tensor. It supports broadcasting as well. 
/// ```md
/// resultTensor = primaryTensor == secondaryTensor
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) equalWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                           secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( equal(_:_:name:) );


/// Returns the elementwise inequality check of the input tensors.
///
/// This operation creates a not equal operation and returns the result tensor. It supports broadcasting as well. 
/// ```md
/// resultTensor = primaryTensor != secondaryTensor
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) notEqualWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                              secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                         name:(NSString * _Nullable) name
MPS_SWIFT_NAME( notEqual(_:_:name:) );


/// Checks in an elementwise manner if the first input tensor is less than the second.
///
/// This operation creates a `lessThan` operation and returns the result tensor. It supports broadcasting as well. 
/// ```md
/// resultTensor = primaryTensor < secondaryTensor
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) lessThanWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                              secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                         name:(NSString * _Nullable) name
MPS_SWIFT_NAME( lessThan(_:_:name:) );

/// Checks in an elementwise manner if the first input tensor is less than or equal to the second.
///
/// This operation creates a `lessThanOrEqualTo` operation and returns the result tensor. It supports broadcasting as well. 
/// ```md
/// resultTensor = primaryTensor <= secondaryTensor
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) lessThanOrEqualToWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                       secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                                  name:(NSString * _Nullable) name
MPS_SWIFT_NAME( lessThanOrEqualTo(_:_:name:) );


/// Checks in an elementwise manner if the first input tensor is greater than the second.
///
/// This operation creates a `greaterThan` operation and returns the result tensor. It supports broadcasting as well. 
/// ```md
/// resultTensor = primaryTensor > secondaryTensor
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) greaterThanWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                 secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( greaterThan(_:_:name:) );

/// Checks in an elementwise manner if the first input tensor is greater than or equal to the second.
///
/// This operation creates a `greaterThanOrEqual` operation and returns the result tensor. It supports broadcasting as well. 
/// ```md
/// resultTensor = primaryTensor < secondaryTensor
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) greaterThanOrEqualToWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                          secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                                     name:(NSString * _Nullable) name
MPS_SWIFT_NAME( greaterThanOrEqualTo(_:_:name:) );

/// Returns the elementwise logical AND of the input tensors.
///
/// This operation creates a logical AND operation and returns the result tensor. It supports broadcasting as well. 
/// ```md
/// resultTensor = primaryTensor && secondaryTensor
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) logicalANDWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( logicalAND(_:_:name:) );


/// Returns the elementwise logical OR of the input tensors.
///
/// This operation creates a logical OR operation and returns the result tensor. It supports broadcasting as well. 
/// ```md
/// resultTensor = primaryTensor || secondaryTensor
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) logicalORWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                               secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                          name:(NSString * _Nullable) name
MPS_SWIFT_NAME( logicalOR(_:_:name:) );


/// Returns the elementwise logical NAND of the input tensors.
///
/// This operation creates a logical NAND operation and returns the result tensor. It supports broadcasting as well. 
/// ```md
/// resultTensor = !(primaryTensor && secondaryTensor)
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) logicalNANDWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                 secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( logicalNAND(_:_:name:) );


/// Returns the elementwise logical NOR of the input tensors.
///
/// This operation creates a logical NOR operation and returns the result tensor. It supports broadcasting as well. 
/// ```md
/// resultTensor = !(primaryTensor || secondaryTensor)
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) logicalNORWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( logicalNOR(_:_:name:) );


/// Returns the elementwise logical XOR of the input tensors.
///
/// This operation creates a logical XOR operation and returns the result tensor. It supports broadcasting as well. 
/// ```md
/// resultTensor = XOR(primaryTensor, secondaryTensor)
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) logicalXORWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( logicalXOR(_:_:name:) );


/// Returns the elementwise logical XNOR of the input tensors.
///
/// This operation creates a logical XNOR operation and returns the result tensor. It supports broadcasting as well. 
/// ```md
/// resultTensor = XNOR(primaryTensor, secondaryTensor)
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) logicalXNORWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                 secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( logicalXNOR(_:_:name:) );

/// Returns the elementwise two-argument arctangent of the input tensors.
///
/// This operation creates a `atan2` operation and returns the result tensor. It supports broadcasting as well. 
/// Graph computes arc tangent of primaryTensor over secondaryTensor.
/// ```md
/// resultTensor = atan2(primaryTensor, secondaryTensor)
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) atan2WithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                           secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                      name:(NSString * _Nullable) name;

/// Returns the elementwise bitwise AND of binary representations of two integer tensors.
///
/// - Parameters:
///   - primaryTensor: The primary input tensor, must be of integer type.
///   - secondaryTensor: The secondary input tensor, must be of integer type.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) bitwiseANDWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( bitwiseAND(_:_:name:) )
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1));

/// Returns the elementwise bitwise OR of binary representations of two integer tensors.
///
/// - Parameters:
///   - primaryTensor: The primary input tensor, must be of integer type.
///   - secondaryTensor: The secondary input tensor, must be of integer type.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) bitwiseORWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                               secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                          name:(NSString * _Nullable) name
MPS_SWIFT_NAME( bitwiseOR(_:_:name:) )
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1));

/// Returns the elementwise bitwise XOR of binary representations of two integer tensors.
///
/// - Parameters:
///   - primaryTensor: The primary input tensor, must be of integer type.
///   - secondaryTensor: The secondary input tensor, must be of integer type.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) bitwiseXORWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( bitwiseXOR(_:_:name:) )
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1));

/// Returns the elementwise left-shifted binary representations of the primary integer by the secondary tensor amount.
///
/// - Parameters:
///   - primaryTensor: The primary input tensor, must be of integer type.
///   - secondaryTensor: The secondary input tensor, must be of integer type.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) bitwiseLeftShiftWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                      secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                                 name:(NSString * _Nullable) name
MPS_SWIFT_NAME( bitwiseLeftShift(_:_:name:) )
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1));

/// Returns the elementwise right-shifted binary representations of the primary integer by the secondary tensor amount.
///
/// - Parameters:
///   - primaryTensor: The primary input tensor, must be of integer type.
///   - secondaryTensor: The secondary input tensor, must be of integer type.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) bitwiseRightShiftWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                       secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                                  name:(NSString * _Nullable) name
MPS_SWIFT_NAME( bitwiseRightShift(_:_:name:) )
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1));


#pragma mark - TernaryArithmeticOps

/// Selects values from either the true or false predicate tensor, depending on the values in the first input.
///
/// This operation creates a select operation and returns the result tensor. It supports broadcasting as well. 
/// ```md
/// resultTensor = select(predicateTensor, truePredicateTensor, falseSelectTensor)
/// ```
///
/// - Parameters:
///   - predicateTensor: The predicate tensor.
///   - truePredicateTensor: The tensor to select values from if predicate is true.
///   - falseSelectTensor: The tensor to select values from if predicate is false.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) selectWithPredicateTensor:(MPSGraphTensor *) predicateTensor
                          truePredicateTensor:(MPSGraphTensor *) truePredicateTensor
                         falsePredicateTensor:(MPSGraphTensor *) falseSelectTensor
                                         name:(NSString * _Nullable) name
MPS_SWIFT_NAME( select(predicate:trueTensor:falseTensor:name:) );

/// Clamps the values in the first tensor between the corresponding values in the minimum and maximum value tensor.
///
/// This operation creates a clamp operation and returns the result tensor. It supports broadcasting as well. 
/// ```md
/// resultTensor = clamp(tensor, minValueTensor, maxValueTensor)
/// ```
///
/// - Parameters:
///   - tensor: The tensor to be clamped.
///   - minValueTensor: The tensor with min values to clamp to.
///   - minValueTensor: The tensor with max values to clamp to.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) clampWithTensor:(MPSGraphTensor *) tensor
                     minValueTensor:(MPSGraphTensor *) minValueTensor
                     maxValueTensor:(MPSGraphTensor *) maxValueTensor
                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( clamp(_:min:max:name:) );



#pragma mark - ConvenienceMathOps
/// Divides the first input tensor by the second, with the result being 0 if the denominator is 0.
///
/// ```md
/// resultTensor = select(secondaryTensor, primaryTensor / secondaryTensor, 0)
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) divisionNoNaNWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                   secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                              name:(NSString * _Nullable) name
MPS_SWIFT_NAME( divisionNoNaN(_:_:name:) );

/// Returns the remainder of floor divison between the primary and secondary tensor.
/// 
/// Creates a floorModulo operation and returns the result tensor, it supports broadcasting as well, returns 0 if divisor is 0.
/// ```md
/// resultTensor = primaryTensor - (floor(primaryTensor / secondaryTensor) * secondaryTensor)
/// ```
///
/// - Parameters:
///   - primaryTensor: The LHS tensor of the binary Op.
///   - secondaryTensor: The RHS tensor of the binary Op.
///   - name: An optional string which serves as an identifier for the operation.
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) floorModuloWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                 secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( floorModulo(_:_:name:) );

#pragma mark - ComplexOps

/// Returns the real part of a tensor.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation..
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) realPartOfTensor:(MPSGraphTensor *) tensor
                                name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
MPS_SWIFT_NAME( realPartOfTensor(tensor:name:) );

/// Returns the imaginary part of a tensor.
///
/// - Parameters:
///   - tensor: The input tensor.
///   - name: An optional string which serves as an identifier for the operation..
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) imaginaryPartOfTensor:(MPSGraphTensor *) tensor
                                     name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
MPS_SWIFT_NAME( imaginaryPartOfTensor(tensor:name:) );

/// Returns a complex tensor from the two input tensors.
///
/// - Parameters:
///   - realTensor: The real part of the complex tensor.
///   - imaginaryTensor: The imaginary part of the complex tensor.
///   - name: An optional string which serves as an identifier for the operation..
/// - Returns: A valid `MPSGraphTensor` object containing the elementwise result of the applied operation.
-(MPSGraphTensor *) complexTensorWithRealTensor:(MPSGraphTensor *) realTensor
                                imaginaryTensor:(MPSGraphTensor *) imaginaryTensor
                                           name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
MPS_SWIFT_NAME( complexTensor(realTensor:imaginaryTensor:name:) );

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphArithmeticOps_h */
