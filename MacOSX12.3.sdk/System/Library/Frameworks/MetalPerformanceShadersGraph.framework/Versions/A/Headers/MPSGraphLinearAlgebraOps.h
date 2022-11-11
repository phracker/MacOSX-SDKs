//
//  MPSGraphLinearAlgebraOps.h
//  MPSGraph
//
//  Created by local on 1/21/22.
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#ifndef MPSGraphLinearAlgebraOps_h
#define MPSGraphLinearAlgebraOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN


MPS_CLASS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4))
@interface MPSGraph(MPSGraphLinearAlgebraOps)

/*!
 *  @abstract   Create band part op and return the result
 *  @discussion Copies a diagonal band of values from input tensor to a result tensor of the same size.
 *              A coordinate @code [..., i, j] @endcode is in the band if
 *              @code
 *              (numLower < 0 || (i-j) <= numLower) && (numUpper < 0 || (j-i) <= numUpper)
 *              @endcode
 *              Values outside of the band are set to 0.
 *
 *  @param      inputTensor            The source tensor to copy
 *  @param      numLower            The number of diagonals in the lower triangle to keep. If -1, keep all
 *  @param      numUpper            The number of diagonals in the upper triangle to keep. If -1, keep all
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) bandPartWithTensor:(MPSGraphTensor *) inputTensor
                              numLower:(NSInteger) numLower
                              numUpper:(NSInteger) numUpper
                                  name:(NSString * _Nullable) name
MPS_SWIFT_NAME( bandPart(_:numLower:numUpper:name:) );

/*!
 *  @abstract   Create band part op and return the result
 *  @discussion See above discussion of bandPartWithTensor: numLower: numUpper: name:
 *
 *  @param      inputTensor            The source tensor to copy
 *  @param      numLowerTensor            Scalar Int32 tensor. The number of diagonals in the lower triangle to keep. If -1, keep all.
 *  @param      numUpperTensor            Scalar Int32 tensor. The number of diagonals in the upper triangle to keep. If -1, keep all.
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) bandPartWithTensor:(MPSGraphTensor *) inputTensor
                        numLowerTensor:(MPSGraphTensor *) numLowerTensor
                        numUpperTensor:(MPSGraphTensor *) numUpperTensor
                                  name:(NSString * _Nullable) name
MPS_SWIFT_NAME( bandPart(_:numLowerTensor:numUpperTensor:name:) );

@end

NS_ASSUME_NONNULL_END


#endif /* MPSGraphLinearAlgebraOps_h */
