//
//  MPSGraphSortOps.h
//  MPSGraph
//
//  Created on 6/30/22.
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#ifndef MPSGraphSortOps_h
#define MPSGraphSortOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphSortOps)

/// Sorts the elements of the input tensor along the specified axis.
///
/// - Parameters:
///   - tensor: The input tensor
///   - axis: The tensor dimension over which you sort the tensor
///   - descending: If true, reverse the sort direction
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) sortWithTensor:(MPSGraphTensor *) tensor
                              axis:(NSInteger) axis
                        descending:(BOOL) descending
                              name:(NSString * _Nullable) name
MPS_SWIFT_NAME( sort(_:axis:descending:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// Sorts the elements of the input tensor along the specified axis.
///
/// - Parameters:
///   - tensor: The input tensor
///   - axisTensor: The tensor dimension over which you sort the tensor
///   - descending: If true, reverse the sort direction
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) sortWithTensor:(MPSGraphTensor *) tensor
                        axisTensor:(MPSGraphTensor *) axisTensor
                        descending:(BOOL) descending
                              name:(NSString * _Nullable) name
MPS_SWIFT_NAME( sort(_:axisTensor:descending:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// Sorts the elements of the input tensor along the specified axis.
///
/// - Parameters:
///   - tensor: The input tensor
///   - axis: The tensor dimension over which you sort the tensor
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) sortWithTensor:(MPSGraphTensor *) tensor
                              axis:(NSInteger) axis
                              name:(NSString * _Nullable) name
MPS_SWIFT_NAME( sort(_:axis:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// Sorts the elements of the input tensor along the specified axis.
///
/// - Parameters:
///   - tensor: The input tensor
///   - axisTensor: The tensor dimension over which you sort the tensor
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) sortWithTensor:(MPSGraphTensor *) tensor
                        axisTensor:(MPSGraphTensor *) axisTensor
                              name:(NSString * _Nullable) name
MPS_SWIFT_NAME( sort(_:axisTensor:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// Computes the indices that sort the elements of the input tensor along the specified axis.
///
/// - Parameters:
///   - tensor: The input tensor
///   - axis: The tensor dimension over which you sort the tensor
///   - descending: If true, reverse the sort direction
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object with 32-bit integer data type
-(MPSGraphTensor *) argSortWithTensor:(MPSGraphTensor *) tensor
                                 axis:(NSInteger) axis
                           descending:(BOOL) descending
                                 name:(NSString * _Nullable) name
MPS_SWIFT_NAME( argSort(_:axis:descending:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1));

/// Computes the indices that sort the elements of the input tensor along the specified axis.
///
/// - Parameters:
///   - tensor: The input tensor
///   - axisTensor: The tensor dimension over which you sort the tensor
///   - descending: If true, reverse the sort direction
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object with 32-bit integer data type
-(MPSGraphTensor *) argSortWithTensor:(MPSGraphTensor *) tensor
                           axisTensor:(MPSGraphTensor *) axisTensor
                           descending:(BOOL) descending
                                 name:(NSString * _Nullable) name
MPS_SWIFT_NAME( argSort(_:axisTensor:descending:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1));

/// Computes the indices that sort the elements of the input tensor along the specified axis.
///
/// - Parameters:
///   - tensor: The input tensor
///   - axis: The tensor dimension over which you sort the tensor
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object with 32-bit integer data type
-(MPSGraphTensor *) argSortWithTensor:(MPSGraphTensor *) tensor
                                 axis:(NSInteger) axis
                                 name:(NSString * _Nullable) name
MPS_SWIFT_NAME( argSort(_:axis:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1));

/// Computes the indices that sort the elements of the input tensor along the specified axis.
///
/// - Parameters:
///   - tensor: The input tensor
///   - axisTensor: The tensor dimension over which you sort the tensor
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object with 32-bit integer data type
-(MPSGraphTensor *) argSortWithTensor:(MPSGraphTensor *) tensor
                           axisTensor:(MPSGraphTensor *) axisTensor
                                 name:(NSString * _Nullable) name
MPS_SWIFT_NAME( argSort(_:axisTensor:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1));

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphArgSortOps_h */
