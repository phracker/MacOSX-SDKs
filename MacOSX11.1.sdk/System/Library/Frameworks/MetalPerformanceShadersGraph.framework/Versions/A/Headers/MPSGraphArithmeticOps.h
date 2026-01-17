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

-(MPSGraphTensor *) identityWithTensor:(MPSGraphTensor *) tensor
                                  name:(NSString * _Nullable) name;

-(MPSGraphTensor *) exponentWithTensor:(MPSGraphTensor *) tensor
                                  name:(NSString * _Nullable) name;

-(MPSGraphTensor *) exponentBase2WithTensor:(MPSGraphTensor *) tensor
                                       name:(NSString * _Nullable) name;

-(MPSGraphTensor *) exponentBase10WithTensor:(MPSGraphTensor *) tensor
                                        name:(NSString * _Nullable) name;

-(MPSGraphTensor *) logarithmWithTensor:(MPSGraphTensor *) tensor
                                   name:(NSString * _Nullable) name;

-(MPSGraphTensor *) logarithmBase2WithTensor:(MPSGraphTensor *) tensor
                                        name:(NSString * _Nullable) name;

-(MPSGraphTensor *) logarithmBase10WithTensor:(MPSGraphTensor *) tensor
                                         name:(NSString * _Nullable) name;

-(MPSGraphTensor *) squareWithTensor:(MPSGraphTensor *) tensor
                                name:(NSString * _Nullable) name;

-(MPSGraphTensor *) squareRootWithTensor:(MPSGraphTensor *) tensor
                                    name:(NSString * _Nullable) name;

-(MPSGraphTensor *) reverseSquareRootWithTensor:(MPSGraphTensor *) tensor
                                           name:(NSString * _Nullable) name;

-(MPSGraphTensor *) reciprocalWithTensor:(MPSGraphTensor *) tensor
                                    name:(NSString * _Nullable) name;

-(MPSGraphTensor *) absoluteWithTensor:(MPSGraphTensor *) tensor
                                  name:(NSString * _Nullable) name;

-(MPSGraphTensor *) negativeWithTensor:(MPSGraphTensor *) tensor
                                  name:(NSString * _Nullable) name;

-(MPSGraphTensor *) signWithTensor:(MPSGraphTensor *) tensor
                              name:(NSString * _Nullable) name;


-(MPSGraphTensor *) signbitWithTensor:(MPSGraphTensor *) tensor
                                 name:(NSString * _Nullable) name;


-(MPSGraphTensor *) ceilWithTensor:(MPSGraphTensor *) tensor
                              name:(NSString * _Nullable) name;


-(MPSGraphTensor *) floorWithTensor:(MPSGraphTensor *) tensor
                               name:(NSString * _Nullable) name;


-(MPSGraphTensor *) roundWithTensor:(MPSGraphTensor *) tensor
                               name:(NSString * _Nullable) name;


-(MPSGraphTensor *) rintWithTensor:(MPSGraphTensor *) tensor
                              name:(NSString * _Nullable) name;


-(MPSGraphTensor *) sinWithTensor:(MPSGraphTensor *) tensor
                             name:(NSString * _Nullable) name;


-(MPSGraphTensor *) cosWithTensor:(MPSGraphTensor *) tensor
                             name:(NSString * _Nullable) name;


-(MPSGraphTensor *) tanWithTensor:(MPSGraphTensor *) tensor
                             name:(NSString * _Nullable) name;


-(MPSGraphTensor *) sinhWithTensor:(MPSGraphTensor *) tensor
                              name:(NSString * _Nullable) name;


-(MPSGraphTensor *) coshWithTensor:(MPSGraphTensor *) tensor
                              name:(NSString * _Nullable) name;


-(MPSGraphTensor *) tanhWithTensor:(MPSGraphTensor *) tensor
                              name:(NSString * _Nullable) name;


-(MPSGraphTensor *) asinWithTensor:(MPSGraphTensor *) tensor
                              name:(NSString * _Nullable) name;


-(MPSGraphTensor *) acosWithTensor:(MPSGraphTensor *) tensor
                              name:(NSString * _Nullable) name;


-(MPSGraphTensor *) atanWithTensor:(MPSGraphTensor *) tensor
                              name:(NSString * _Nullable) name;


-(MPSGraphTensor *) asinhWithTensor:(MPSGraphTensor *) tensor
                               name:(NSString * _Nullable) name;


-(MPSGraphTensor *) acoshWithTensor:(MPSGraphTensor *) tensor
                               name:(NSString * _Nullable) name;


-(MPSGraphTensor *) atanhWithTensor:(MPSGraphTensor *) tensor
                               name:(NSString * _Nullable) name;


-(MPSGraphTensor *) notWithTensor:(MPSGraphTensor *) tensor
                             name:(NSString * _Nullable) name;


-(MPSGraphTensor *) isInfiniteWithTensor:(MPSGraphTensor *) tensor
                                    name:(NSString * _Nullable) name;


-(MPSGraphTensor *) isFiniteWithTensor:(MPSGraphTensor *) tensor
                                  name:(NSString * _Nullable) name;


-(MPSGraphTensor *) isNaNWithTensor:(MPSGraphTensor *) tensor
                               name:(NSString * _Nullable) name;


-(MPSGraphTensor *) erfWithTensor:(MPSGraphTensor *) tensor
                             name:(NSString * _Nullable) name;


#pragma mark - BinaryArithmeticOps

/*!
 *  @abstract   Create Add op and return the result tensor, it supports broadcasting as well
 *
 *  @code
 *              resultTensor = primaryTensor + secondaryTensor
 *  @endcode
 *
 *  @param      primaryTensor          LHS tensor of the binary Op
 *  @param      secondaryTensor      RHS tensor of the binary Op
 *  @param      name                              name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) additionWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                              secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                         name:(NSString * _Nullable) name
MPS_SWIFT_NAME( addition(_:_:name:) );



/*!
 *  @abstract   Create Subtract op and return the result tensor, it supports broadcasting as well
 *
 *  @code
 *              resultTensor = primaryTensor - secondaryTensor
 *  @endcode
 *
 *  @param      primaryTensor          LHS tensor of the binary Op
 *  @param      secondaryTensor      RHS tensor of the binary Op
 *  @param      name                              name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) subtractionWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                 secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( subtraction(_:_:name:) );



/*!
 *  @abstract   Create Multiply op and return the result tensor, it supports broadcasting as well
 *
 *  @code
 *              resultTensor = primaryTensor * secondaryTensor
 *  @endcode
 *
 *  @param      primaryTensor          LHS tensor of the binary Op
 *  @param      secondaryTensor      RHS tensor of the binary Op
 *  @param      name                              name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) multiplicationWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                    secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( multiplication(_:_:name:) );

/*!
 *  @abstract   Create Divide op and return the result tensor, it supports broadcasting as well
 *
 *  @code
 *              resultTensor = primaryTensor / secondaryTensor
 *  @endcode
 *
 *  @param      primaryTensor          LHS tensor of the binary Op
 *  @param      secondaryTensor      RHS tensor of the binary Op
 *  @param      name                              name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) divisionWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                              secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                         name:(NSString * _Nullable) name
MPS_SWIFT_NAME( division(_:_:name:) );



-(MPSGraphTensor *) moduloWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                            secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                       name:(NSString * _Nullable) name
MPS_SWIFT_NAME( modulo(_:_:name:) );



-(MPSGraphTensor *) powerWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                           secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( power(_:_:name:) );



-(MPSGraphTensor *) minimumWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                             secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                        name:(NSString * _Nullable) name
MPS_SWIFT_NAME( minimum(_:_:name:) );



-(MPSGraphTensor *) maximumWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                             secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                        name:(NSString * _Nullable) name
MPS_SWIFT_NAME( maximum(_:_:name:) );



-(MPSGraphTensor *) equalWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                           secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( equal(_:_:name:) );



-(MPSGraphTensor *) notEqualWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                              secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                         name:(NSString * _Nullable) name
MPS_SWIFT_NAME( notEqual(_:_:name:) );



-(MPSGraphTensor *) lessThanWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                              secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                         name:(NSString * _Nullable) name
MPS_SWIFT_NAME( lessThan(_:_:name:) );



-(MPSGraphTensor *) lessThanOrEqualToWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                       secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                                  name:(NSString * _Nullable) name
MPS_SWIFT_NAME( lessThanOrEqualTo(_:_:name:) );



-(MPSGraphTensor *) greaterThanWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                 secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( greaterThan(_:_:name:) );



-(MPSGraphTensor *) greaterThanOrEqualToWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                          secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                                     name:(NSString * _Nullable) name
MPS_SWIFT_NAME( greaterThanOrEqualTo(_:_:name:) );



-(MPSGraphTensor *) logicalANDWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( logicalAND(_:_:name:) );



-(MPSGraphTensor *) logicalORWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                               secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                          name:(NSString * _Nullable) name
MPS_SWIFT_NAME( logicalOR(_:_:name:) );



-(MPSGraphTensor *) logicalNANDWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                 secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( logicalNAND(_:_:name:) );



-(MPSGraphTensor *) logicalNORWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( logicalNOR(_:_:name:) );



-(MPSGraphTensor *) logicalXORWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( logicalXOR(_:_:name:) );



-(MPSGraphTensor *) logicalXNORWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                 secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( logicalXNOR(_:_:name:) );



-(MPSGraphTensor *) atan2WithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                           secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                      name:(NSString * _Nullable) name;




#pragma mark - TernaryArithmeticOps

-(MPSGraphTensor *) selectWithPredicateTensor:(MPSGraphTensor *) predicateTensor
                          truePredicateTensor:(MPSGraphTensor *) truePredicateTensor
                         falsePredicateTensor:(MPSGraphTensor *) falseSelectTensor
                                         name:(NSString * _Nullable) name
MPS_SWIFT_NAME( select(predicate:trueTensor:falseTensor:name:) );


-(MPSGraphTensor *) clampWithTensor:(MPSGraphTensor *) tensor
                     minValueTensor:(MPSGraphTensor *) minValueTensor
                     maxValueTensor:(MPSGraphTensor *) maxValueTensor
                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( clamp(_:min:max:name:) );



#pragma mark - ConvenienceMathOps

-(MPSGraphTensor *) divisionNoNaNWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                   secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                              name:(NSString * _Nullable) name
MPS_SWIFT_NAME( divisionNoNaN(_:_:name:) );

-(MPSGraphTensor *) floorModuloWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                 secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( floorModulo(_:_:name:) );

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphArithmeticOps_h */
