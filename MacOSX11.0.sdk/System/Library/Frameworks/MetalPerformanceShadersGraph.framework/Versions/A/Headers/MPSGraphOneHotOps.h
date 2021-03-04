//
//  MPSOneHotOps.h
//  MPSGraph
//
//  Created on 3/18/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSOneHotOps_h
#define MPSOneHotOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphOneHotOps)

/*!
 *  @abstract   Create  oneHot op and return the result tensor
 *
 *  @discussion Creates a tensor of rank equal to the indicesTensor rank + 1.
 *              A new axis is inserted at the axis specified, or the minor axis if axis is -1.
 *              The values at the indices in the indicesTensor will have the onValue,
 *              and all other values will be set to the offValue.
 *
 *  @param      indicesTensor            Tensor of indices for on values
 *  @param      depth                              Depth of the oneHot vector along the axis
 *  @param      axis                                The axis to insert the new oneHot vector at.
 *                                 Defaults to -1, the minor axis
 *  @param      dataType                       MPSDataType of the result tensor
 *                                 Defaults to MPSDataTypeFloat
 *  @param      onValue                         The value for indices designated by the indicesTensor. This value must match the specified data type.
 *                                 Defaults to 1.0f
 *  @param      offValue                       The value for indices not designated by the indicesTensor. This value must match the specified data type.
 *                                 Defaults to 0.0f
 *  @param      name                                Name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
*/
-(MPSGraphTensor *) oneHotWithIndicesTensor:(MPSGraphTensor *) indicesTensor
                                      depth:(NSUInteger) depth
                                       axis:(NSUInteger) axis
                                   dataType:(MPSDataType) dataType
                                    onValue:(double) onValue
                                   offValue:(double) offValue
                                       name:(NSString * _Nullable) name;

-(MPSGraphTensor *) oneHotWithIndicesTensor:(MPSGraphTensor *) indicesTensor
                                      depth:(NSUInteger) depth
                                   dataType:(MPSDataType) dataType
                                    onValue:(double) onValue
                                   offValue:(double) offValue
                                       name:(NSString * _Nullable) name;

-(MPSGraphTensor *) oneHotWithIndicesTensor:(MPSGraphTensor *) indicesTensor
                                      depth:(NSUInteger) depth
                                       axis:(NSUInteger) axis
                                   dataType:(MPSDataType) dataType
                                       name:(NSString * _Nullable) name;

-(MPSGraphTensor *) oneHotWithIndicesTensor:(MPSGraphTensor *) indicesTensor
                                      depth:(NSUInteger) depth
                                       axis:(NSUInteger) axis
                                       name:(NSString * _Nullable) name;

-(MPSGraphTensor *) oneHotWithIndicesTensor:(MPSGraphTensor *) indicesTensor
                                      depth:(NSUInteger) depth
                                   dataType:(MPSDataType) dataType
                                       name:(NSString * _Nullable) name;

-(MPSGraphTensor *) oneHotWithIndicesTensor:(MPSGraphTensor *) indicesTensor
                                      depth:(NSUInteger) depth
                                       name:(NSString * _Nullable) name;

@end

NS_ASSUME_NONNULL_END


#endif /* MPSOneHotOps_h */
