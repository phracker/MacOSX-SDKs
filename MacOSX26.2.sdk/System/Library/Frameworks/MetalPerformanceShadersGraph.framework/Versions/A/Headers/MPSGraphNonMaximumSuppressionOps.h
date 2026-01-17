//
//  MPSGraphNonMaximumSuppressionOps.h
//  MetalPerformanceShadersGraph
//
//  Created on 5/11/23.
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#ifndef MPSGraphNonMaximumSuppressionOps_h
#define MPSGraphNonMaximumSuppressionOps_h

#import <MetalPerformanceShadersGraph/MetalPerformanceShadersGraph.h>

NS_ASSUME_NONNULL_BEGIN

/// The non-maximum suppression coordinate mode.
///
/// The coordinate mode to use. At initialization defaults to MPSGraphNonMaximumSuppressionCoordinateModeCornersHeightFirst.
/// This mode specifies the representation used for the 4 box coordinate values.
/// Center coordinate modes define a centered box and the box dimensions.
/// ```md
/// CornersHeightFirst:
///     [h_start, w_start, h_end, w_end]
/// CornersWidthFirst:
///     [w_start, h_start, w_end, h_end]
/// CentersHeightFirst:
///     [h_center, w_center, box_height, box_width]
/// CentersWidthFirst:
///     [w_center, w_center, box_height, box_width]
/// ```
typedef NS_ENUM(NSUInteger, MPSGraphNonMaximumSuppressionCoordinateMode)
{
    MPSGraphNonMaximumSuppressionCoordinateModeCornersHeightFirst    MPS_ENUM_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0)) MPS_SWIFT_NAME(explicit)   =  0L,
    MPSGraphNonMaximumSuppressionCoordinateModeCornersWidthFirst     MPS_ENUM_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))                            =  1L,
    MPSGraphNonMaximumSuppressionCoordinateModeCentersHeightFirst    MPS_ENUM_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))                            =  2L,
    MPSGraphNonMaximumSuppressionCoordinateModeCentersWidthFirst     MPS_ENUM_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))                            =  3L,
};

MPS_CLASS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
@interface MPSGraph(MPSGraphNonMaximumSuppressionOps)

/// Creates a nonMaximumumSuppression operation and returns the result tensor.
/// - Parameters:
///   - boxesTensor: A tensor containing the coordinates of the input boxes. Must be a rank 3 tensor of shape [N,B,4] of type ``MPSDataTypeFloat32``
///   - scoresTensor: A tensor containing the scores of the input boxes. Must be a rank 3 tensor of shape [N,B,K] of type ``MPSDataTypeFloat32``
///   - IOUThreshold: The threshold for when to reject boxes based on their Intersection Over Union. Valid range is [0,1].
///   - scoreThreshold: The threshold for when to reject boxes based on their score, before IOU suppression.
///   - perClassSuppression: When this is specified a box will only suppress another box if they have the same class.
///   - coordinateMode: The coordinate mode the box coordinates are provided in.
///   - name: The name for the operation.
-(MPSGraphTensor *) nonMaximumSuppressionWithBoxesTensor:(MPSGraphTensor *) boxesTensor
                                            scoresTensor:(MPSGraphTensor *) scoresTensor
                                            IOUThreshold:(float) IOUThreshold
                                          scoreThreshold:(float) scoreThreshold
                                     perClassSuppression:(BOOL) perClassSuppression
                                          coordinateMode:(MPSGraphNonMaximumSuppressionCoordinateMode) coordinateMode
                                                    name:(NSString * _Nullable) name;

/// Creates a nonMaximumumSuppression operation and returns the result tensor.
/// - Parameters:
///   - boxesTensor: A tensor containing the coordinates of the input boxes. Must be a rank 3 tensor of shape [N,B,4] of type ``MPSDataTypeFloat32``
///   - scoresTensor: A tensor containing the scores of the input boxes. Must be a rank 3 tensor of shape [N,B,1] of type ``MPSDataTypeFloat32``
///   - classIndicesTensor: A tensor containing the class indices of the input boxes. Must be a rank 2 tensor of shape [N,B] of type ``MPSDataTypeInt32``
///   - IOUThreshold: The threshold for when to reject boxes based on their Intersection Over Union. Valid range is [0,1].
///   - scoreThreshold: The threshold for when to reject boxes based on their score, before IOU suppression.
///   - perClassSuppression: When this is specified a box will only suppress another box if they have the same class.
///   - coordinateMode: The coordinate mode the box coordinates are provided in.
///   - name: The name for the operation.
-(MPSGraphTensor *) nonMaximumSuppressionWithBoxesTensor:(MPSGraphTensor *) boxesTensor
                                            scoresTensor:(MPSGraphTensor *) scoresTensor
                                      classIndicesTensor:(MPSGraphTensor *) classIndicesTensor
                                            IOUThreshold:(float) IOUThreshold
                                          scoreThreshold:(float) scoreThreshold
                                     perClassSuppression:(BOOL) perClassSuppression
                                          coordinateMode:(MPSGraphNonMaximumSuppressionCoordinateMode) coordinateMode
                                                    name:(NSString * _Nullable) name;

@end

NS_ASSUME_NONNULL_END


#endif /* MPSGraphNonMaximumSuppressionOps_h */
