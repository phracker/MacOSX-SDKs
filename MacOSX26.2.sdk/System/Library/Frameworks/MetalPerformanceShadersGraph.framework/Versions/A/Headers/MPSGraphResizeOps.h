//
//  MPSGraphResizeOps.h
//  MPSGraph
//
//  Created on 3/13/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphResizeOps_h
#define MPSGraphResizeOps_h

NS_ASSUME_NONNULL_BEGIN

/// The resize mode to use for resizing.
typedef NS_ENUM(NSUInteger, MPSGraphResizeMode)
{
    /// Samples the nearest neighbor to the pixel coordinate.
    MPSGraphResizeNearest        MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0)) MPS_SWIFT_NAME(nearest)   =  0L,
    /// Samples the 4 neighbors to the pixel coordinate and uses bilinear interpolation.
    MPSGraphResizeBilinear       MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                           =  1L,
};

/// The rounding mode to use when using nearest resize mode.
typedef NS_ENUM(NSUInteger, MPSGraphResizeNearestRoundingMode)
{
    /// Rounds values to the nearest integer value, with 0.5f offset rounding toward +inf.
    MPSGraphResizeNearestRoundingModeRoundPreferCeil        MPS_ENUM_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0)) MPS_SWIFT_NAME(roundPreferCeil)   =  0L,
    /// Rounds values to the nearest integer value, with 0.5f rounding toward -inf.
    MPSGraphResizeNearestRoundingModeRoundPreferFloor       MPS_ENUM_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0))                                    =  1L,
    /// Rounds values toward +inf.
    MPSGraphResizeNearestRoundingModeCeil                   MPS_ENUM_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0))                                    =  2L,
    /// Rounds values toward -inf.
    MPSGraphResizeNearestRoundingModeFloor                  MPS_ENUM_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0))                                    =  3L,
    /// Rounds values to the nearest integer value, with 0.5f rounding toward the closest even value.
    MPSGraphResizeNearestRoundingModeRoundToEven            MPS_ENUM_AVAILABLE_STARTING(macos(13.2), ios(16.3), tvos(16.3))                                    =  4L,
    /// Rounds values to the nearest integer value, with 0.5f rounding toward the closest odd value.
    MPSGraphResizeNearestRoundingModeRoundToOdd             MPS_ENUM_AVAILABLE_STARTING(macos(13.2), ios(16.3), tvos(16.3))                                    =  5L,
};

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphResizeOps)

/// Creates a Resize operation and returns the result tensor.
///
/// Resamples input images to given size. Result images will be distorted if size is of different aspect ratio. 
/// Resize supports the following modes: 
/// Nearest Neighbor - values are interpolated using the closest neighbor pixel 
/// Bilinear - values are computed using bilinear interpolation of 4 neighboring pixels 
/// Destination indices are computed using direct index scaling by default, with no offset added. 
/// If the centerResult parameter is true, the destination indices will be scaled and shifted to be centered 
/// on the input image. 
/// If the alignCorners parameter is true, the corners of the result images will match the input images. 
/// Scaling will be modified to a factor of (size - 1) / (inputSize - 1). When alignCorners is true, the 
/// centerResult parameter does nothing. 
/// In order to achieve the same behavior as OpenCV's resize and TensorFlowV2's resize, 
/// ```md 
/// centerResult = YES; 
/// alginCorners = NO; 
/// ``` 
/// To achieve the same behavior as TensorFlowV1 resize 
/// ```md 
/// centerResult = NO; 
/// ```
///
/// - Parameters:
///   - imagesTensor: Tensor containing input images.
///   - size: A 2-element shape as [newHeight, newWidth]
///   - mode: The resampling mode to use. If nearest sampling is specifed, RoundPreferCeil mode will be used.
///   - centerResult: Controls if the result image is centered on the input image. When NO, the result will have the top left corner aligned
///   - alignCorners: When YES, the result image will have the same value as the input image in the corners
///   - layout: Specifies what layout the provided tensor is in. The returned tensor will follow the same layout. Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeTensor:(MPSGraphTensor *) imagesTensor
                            size:(MPSShape *) size
                            mode:(MPSGraphResizeMode) mode
                    centerResult:(BOOL) centerResult
                    alignCorners:(BOOL) alignCorners
                          layout:(MPSGraphTensorNamedDataLayout) layout
                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( resize(_:size:mode:centerResult:alignCorners:layout:name:) );

/// Creates a Resize operation and returns the result tensor.
///
/// Resamples input images to given size. Result images will be distorted if size is of different aspect ratio. 
/// Resize supports the following modes: 
/// Nearest Neighbor - values are interpolated using the closest neighbor pixel 
/// Bilinear - values are computed using bilinear interpolation of 4 neighboring pixels 
/// Destination indices are computed using direct index scaling by default, with no offset added. 
/// If the centerResult parameter is true, the destination indices will be scaled and shifted to be centered 
/// on the input image. 
/// If the alignCorners parameter is true, the corners of the result images will match the input images. 
/// Scaling will be modified to a factor of (size - 1) / (inputSize - 1). When alignCorners is true, the 
/// centerResult parameter does nothing. 
/// In order to achieve the same behavior as OpenCV's resize and TensorFlowV2's resize, 
/// ```md 
/// centerResult = YES; 
/// alginCorners = NO; 
/// ``` 
/// To achieve the same behavior as TensorFlowV1 resize 
/// ```md 
/// centerResult = NO; 
/// ```
///
/// - Parameters:
///   - imagesTensor: Tensor containing input images.
///   - size: 1D Int32 or Int64 tensor. A 2-element shape as [newHeight, newWidth]
///   - mode: The resampling mode to use. If nearest sampling is specifed, RoundPreferCeil mode will be used.
///   - centerResult: Controls if the result image is centered on the input image. When NO, the result will have the top left corner aligned
///   - alignCorners: When YES, the result image will have the same value as the input image in the corners
///   - layout: Specifies what layout the provided tensor is in. The returned tensor will follow the same layout. Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeTensor:(MPSGraphTensor *) imagesTensor
                      sizeTensor:(MPSGraphTensor *) size
                            mode:(MPSGraphResizeMode) mode
                    centerResult:(BOOL) centerResult
                    alignCorners:(BOOL) alignCorners
                          layout:(MPSGraphTensorNamedDataLayout) layout
                            name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
MPS_SWIFT_NAME( resize(_:sizeTensor:mode:centerResult:alignCorners:layout:name:) );

/// Creates a Resize operation and returns the result tensor.
///
/// Resamples input images to given size. Result images will be distorted if size is of different aspect ratio.
/// Resize supports the following modes:
/// Nearest Neighbor - values are interpolated using the closest neighbor pixel
/// Bilinear - values are computed using bilinear interpolation of 4 neighboring pixels
/// Destination indices are computed using direct index scaling by default, with no offset added.
/// If the centerResult parameter is true, the destination indices will be scaled and shifted to be centered
/// on the input image.
/// If the alignCorners parameter is true, the corners of the result images will match the input images.
/// Scaling will be modified to a factor of (size - 1) / (inputSize - 1). When alignCorners is true, the
/// centerResult parameter does nothing.
/// In order to achieve the same behavior as OpenCV's resize and TensorFlowV2's resize,
/// ```md
/// centerResult = YES;
/// alginCorners = NO;
/// ```
/// To achieve the same behavior as TensorFlowV1 resize
/// ```md
/// centerResult = NO;
/// ```
///
/// - Parameters:
///   - imagesTensor: Tensor containing input images.
///   - size: The target size of the result tensor. 1D Int32 or Int64 tensor of size equal to rank of input.
///   - mode: The resampling mode to use. If nearest sampling is specifed, RoundPreferCeil mode will be used.
///   - centerResult: Controls if the result image is centered on the input image. When NO, the result will have the top left corner aligned
///   - alignCorners: When YES, the result image will have the same value as the input image in the corners
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeTensor:(MPSGraphTensor *) imagesTensor
                      sizeTensor:(MPSGraphTensor *) size
                            mode:(MPSGraphResizeMode) mode
                    centerResult:(BOOL) centerResult
                    alignCorners:(BOOL) alignCorners
                            name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
MPS_SWIFT_NAME( resize(_:sizeTensor:mode:centerResult:alignCorners:name:) );

/// Resamples input images to given size using nearest neighbor sampling. 
///
/// This API allows for the rounding mode to be specified.
/// Resamples input images to given size. Result images will be distorted if size is of different aspect ratio.
/// Resize supports the following modes:
/// Nearest Neighbor - values are interpolated using the closest neighbor pixel
/// Bilinear - values are computed using bilinear interpolation of 4 neighboring pixels
/// Destination indices are computed using direct index scaling by default, with no offset added.
/// If the centerResult parameter is true, the destination indices will be scaled and shifted to be centered
/// on the input image.
/// If the alignCorners parameter is true, the corners of the result images will match the input images.
/// Scaling will be modified to a factor of (size - 1) / (inputSize - 1). When alignCorners is true, the
/// centerResult parameter does nothing.
/// In order to achieve the same behavior as OpenCV's resize and TensorFlowV2's resize,
/// ```md
/// centerResult = YES;
/// alginCorners = NO;
/// ```
/// To achieve the same behavior as TensorFlowV1 resize
/// ```md
/// centerResult = NO;
/// ```
///
/// - Parameters:
///   - imagesTensor: Tensor containing input images.
///   - size: 1D Int32 or Int64 tensor. A 2-element shape as [newHeight, newWidth]
///   - nearestRoundingMode: The rounding mode to use when using nearest resampling. Default is roundPreferCeil.
///   - centerResult: Controls if the result image is centered on the input image. When NO, the result will have the top left corner aligned
///   - alignCorners: When YES, the result image will have the same value as the input image in the corners
///   - layout: Specifies what layout the provided tensor is in. The returned tensor will follow the same layout. Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeNearestWithTensor:(MPSGraphTensor *) imagesTensor
                                 sizeTensor:(MPSGraphTensor *) size
                        nearestRoundingMode:(MPSGraphResizeNearestRoundingMode) nearestRoundingMode
                               centerResult:(BOOL) centerResult
                               alignCorners:(BOOL) alignCorners
                                     layout:(MPSGraphTensorNamedDataLayout) layout
                                       name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0))
MPS_SWIFT_NAME( resizeNearest(_:sizeTensor:nearestRoundingMode:centerResult:alignCorners:layout:name:) );

/// Creates a Resize operation and returns the result tensor.
///
/// Resamples input images to given size using nearest neighbor sampling. Result images will be distorted if
/// size is of different aspect ratio.
/// Destination indices are computed using direct index scaling by default, with no offset added.
/// If the centerResult parameter is true, the destination indices will be scaled and shifted to be centered
/// on the input image.
/// If the alignCorners parameter is true, the corners of the result images will match the input images.
/// Scaling will be modified to a factor of (size - 1) / (inputSize - 1). When alignCorners is true, the
/// centerResult parameter does nothing.
/// In order to achieve the same behavior as OpenCV's resize and TensorFlowV2's resize,
/// ```md
/// centerResult = YES;
/// alginCorners = NO;
/// ```
/// To achieve the same behavior as TensorFlowV1 resize
/// ```md
/// centerResult = NO;
/// ```
///
/// - Parameters:
///   - imagesTensor: Tensor containing input images.
///   - size: The target size of the result tensor. 1D Int32 or Int64 tensor of size equal to rank of input.
///   - nearestRoundingMode: The rounding mode to use when using nearest resampling. Default is roundPreferCeil.
///   - centerResult: Controls if the result image is centered on the input image. When NO, the result will have the top left corner aligned
///   - alignCorners: When YES, the result image will have the same value as the input image in the corners
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeNearestWithTensor:(MPSGraphTensor *) imagesTensor
                                 sizeTensor:(MPSGraphTensor *) size
                        nearestRoundingMode:(MPSGraphResizeNearestRoundingMode) nearestRoundingMode
                               centerResult:(BOOL) centerResult
                               alignCorners:(BOOL) alignCorners
                                       name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
MPS_SWIFT_NAME( resizeNearest(_:sizeTensor:nearestRoundingMode:centerResult:alignCorners:name:) );

/// Resamples input images to given size using bilinear sampling. 
/// 
/// Resamples input images to given size using nearest neighbor sampling. Result images will be distorted if
/// size is of different aspect ratio.
/// Destination indices are computed using direct index scaling by default, with no offset added.
/// If the centerResult parameter is true, the destination indices will be scaled and shifted to be centered
/// on the input image.
/// If the alignCorners parameter is true, the corners of the result images will match the input images.
/// Scaling will be modified to a factor of (size - 1) / (inputSize - 1). When alignCorners is true, the
/// centerResult parameter does nothing.
/// In order to achieve the same behavior as OpenCV's resize and TensorFlowV2's resize,
/// ```md
/// centerResult = YES;
/// alginCorners = NO;
/// ```
/// To achieve the same behavior as TensorFlowV1 resize
/// ```md
/// centerResult = NO;
/// ```
///
/// - Parameters:
///   - imagesTensor: Tensor containing input images.
///   - size: 1D Int32 or Int64 tensor. A 2-element shape as [newHeight, newWidth]
///   - centerResult: Controls if the result image is centered on the input image. When NO, the result will have the top left corner aligned
///   - alignCorners: When YES, the result image will have the same value as the input image in the corners
///   - layout: Specifies what layout the provided tensor is in. The returned tensor will follow the same layout. Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeBilinearWithTensor:(MPSGraphTensor *) imagesTensor
                                  sizeTensor:(MPSGraphTensor *) size
                                centerResult:(BOOL) centerResult
                                alignCorners:(BOOL) alignCorners
                                      layout:(MPSGraphTensorNamedDataLayout) layout
                                        name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0))
MPS_SWIFT_NAME( resizeBilinear(_:sizeTensor:centerResult:alignCorners:layout:name:) );

/// Creates a Resize operation and returns the result tensor.
///
/// Resamples input images to given size using bilinear sampling. Result images will be distorted if
/// size is of different aspect ratio.
/// Destination indices are computed using direct index scaling by default, with no offset added.
/// If the centerResult parameter is true, the destination indices will be scaled and shifted to be centered
/// on the input image.
/// If the alignCorners parameter is true, the corners of the result images will match the input images.
/// Scaling will be modified to a factor of (size - 1) / (inputSize - 1). When alignCorners is true, the
/// centerResult parameter does nothing.
/// In order to achieve the same behavior as OpenCV's resize and TensorFlowV2's resize,
/// ```md
/// centerResult = YES;
/// alginCorners = NO;
/// ```
/// To achieve the same behavior as TensorFlowV1 resize
/// ```md
/// centerResult = NO;
/// ```
///
/// - Parameters:
///   - imagesTensor: Tensor containing input images.
///   - size: The target size of the result tensor. 1D Int32 or Int64 tensor of size equal to rank of input.
///   - centerResult: Controls if the result image is centered on the input image. When NO, the result will have the top left corner aligned
///   - alignCorners: When YES, the result image will have the same value as the input image in the corners
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeBilinearWithTensor:(MPSGraphTensor *) imagesTensor
                                  sizeTensor:(MPSGraphTensor *) size
                                centerResult:(BOOL) centerResult
                                alignCorners:(BOOL) alignCorners
                                        name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
MPS_SWIFT_NAME( resizeBilinear(_:sizeTensor:centerResult:alignCorners:name:) );

/// Resamples input images to given size using the provided scale and offset. 
/// Destination indices are computed using 
/// ```md 
/// dst_indices = (src_indicesscale) + offset 
/// ``` 
/// For most use cases passing the scale and offset directly is unnecessary, and it is 
/// preferable to use the API specifying centerResult and alignCorners.
///
/// - Parameters:
///   - imagesTensor: Tensor containing input images.
///   - size: 1D Int32 or Int64 tensor. A 2-element shape as [newHeight, newWidth]
///   - scaleOffset: 1D float tensor. A 4-element shape as [scaleY, scaleX, offsetY, offsetX]
///   - mode: The resampling mode to use. If nearest sampling is specifed, RoundPreferCeil mode will be used.
///   - layout: Specifies what layout the provided tensor is in. The returned tensor will follow the same layout. Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeTensor:(MPSGraphTensor *) imagesTensor
                      sizeTensor:(MPSGraphTensor *) size
               scaleOffsetTensor:(MPSGraphTensor *) scaleOffset
                            mode:(MPSGraphResizeMode) mode
                          layout:(MPSGraphTensorNamedDataLayout) layout
                            name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0))
MPS_SWIFT_NAME( resize(_:sizeTensor:scaleOffsetTensor:mode:layout:name:) );

/// Creates a Resize operation and returns the result tensor.
///
/// Resamples input images to given size using the provided scale and offset.
/// Destination indices are computed using
/// ```md
/// dst_indices = (src_indices * scale) + offset
/// ```
/// For most use cases passing the scale and offset directly is unnecessary, and it is
/// preferable to use the API specifying centerResult and alignCorners.
///
/// - Parameters:
///   - imagesTensor: Tensor containing input images.
///   - size: The target size of the result tensor.  1D Int32 or Int64 tensor of size equal to rank of input.
///   - scale: 1D float tensor of size equal to rank of input.
///   - offset: 1D float tensor of size equal to rank of input.
///   - mode: The resampling mode to use. If nearest sampling is specifed, RoundPreferCeil mode will be used.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeTensor:(MPSGraphTensor *) imagesTensor
                      sizeTensor:(MPSGraphTensor *) size
                     scaleTensor:(MPSGraphTensor *) scale
                    offsetTensor:(MPSGraphTensor *) offset
                            mode:(MPSGraphResizeMode) mode
                            name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
MPS_SWIFT_NAME( resize(_:sizeTensor:scaleTensor:offsetTenor:mode:name:) );

/// Resamples input images to given size using the provided scale and offset and nearest neighbor sampling 
/// See above discussion for more details.
///
/// - Parameters:
///   - imagesTensor: Tensor containing input images.
///   - size: 1D Int32 or Int64 tensor. A 2-element shape as [newHeight, newWidth]
///   - scaleOffset: 1D float tensor. A 4-element shape as [scaleY, scaleX, offsetY, offsetX]
///   - nearestRoundingMode: The rounding mode to use when using nearest resampling.
///   - layout: Specifies what layout the provided tensor is in. The returned tensor will follow the same layout. Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeNearestWithTensor:(MPSGraphTensor *) imagesTensor
                                 sizeTensor:(MPSGraphTensor *) size
                          scaleOffsetTensor:(MPSGraphTensor *) scaleOffset
                        nearestRoundingMode:(MPSGraphResizeNearestRoundingMode) nearestRoundingMode
                                     layout:(MPSGraphTensorNamedDataLayout) layout
                                       name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0))
MPS_SWIFT_NAME( resizeNearest(_:sizeTensor:scaleOffsetTensor:nearestRoundingMode:layout:name:) );

/// Creates a Resize operation and returns the result tensor.
///
/// Resamples input images to given size using the provided scale and offset and nearest neighbor sampling.
/// Destination indices are computed using
/// ```md
/// dst_indices = (src_indices * scale) + offset
/// ```
/// For most use cases passing the scale and offset directly is unnecessary, and it is
/// preferable to use the API specifying centerResult and alignCorners.
///
/// - Parameters:
///   - imagesTensor: Tensor containing input images.
///   - size: The target size of the result tensor.  1D Int32 or Int64 tensor of size equal to rank of input.
///   - scale: 1D float tensor of size equal to rank of input.
///   - offset: 1D float tensor of size equal to rank of input.
///   - nearestRoundingMode: The rounding mode to use when using nearest resampling. Default is roundPreferCeil.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeNearestWithTensor:(MPSGraphTensor *) imagesTensor
                                 sizeTensor:(MPSGraphTensor *) size
                                scaleTensor:(MPSGraphTensor *) scale
                               offsetTensor:(MPSGraphTensor *) offset
                        nearestRoundingMode:(MPSGraphResizeNearestRoundingMode) nearestRoundingMode
                                       name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
MPS_SWIFT_NAME( resizeNearest(_:sizeTensor:scaleTensor:offsetTensor:nearestRoundingMode:name:) );

/// Resamples input images to given size using the provided scale and offset and bilinear sampling 
/// See above discussion for more details.
///
/// - Parameters:
///   - imagesTensor: Tensor containing input images.
///   - size: 1D Int32 or Int64 tensor. A 2-element shape as [newHeight, newWidth]
///   - scaleOffset: 1D float tensor. A 4-element shape as [scaleY, scaleX, offsetY, offsetX]
///   - nearestRoundingMode: The rounding mode to use when using nearest resampling.
///   - layout: Specifies what layout the provided tensor is in. The returned tensor will follow the same layout. Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeBilinearWithTensor:(MPSGraphTensor *) imagesTensor
                                  sizeTensor:(MPSGraphTensor *) size
                           scaleOffsetTensor:(MPSGraphTensor *) scaleOffset
                                      layout:(MPSGraphTensorNamedDataLayout) layout
                                        name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0))
MPS_SWIFT_NAME( resizeBilinear(_:sizeTensor:scaleOffsetTensor:layout:name:) );

/// Creates a Resize operation and returns the result tensor.
///
/// Resamples input images to given size using the provided scale and offset and bilinear sampling.
/// Destination indices are computed using
/// ```md
/// dst_indices = (src_indices * scale) + offset
/// ```
/// For most use cases passing the scale and offset directly is unnecessary, and it is
/// preferable to use the API specifying centerResult and alignCorners.
///
/// - Parameters:
///   - imagesTensor: Tensor containing input images.
///   - size: The target size of the result tensor.  1D Int32 or Int64 tensor of size equal to rank of input.
///   - scale: 1D float tensor of size equal to rank of input.
///   - offset: 1D float tensor of size equal to rank of input.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeBilinearWithTensor:(MPSGraphTensor *) imagesTensor
                                  sizeTensor:(MPSGraphTensor *) size
                                 scaleTensor:(MPSGraphTensor *) scale
                                offsetTensor:(MPSGraphTensor *) offset
                                        name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
MPS_SWIFT_NAME( resizeBilinear(_:sizeTensor:scaleTensor:offsetTensor:name:) );

/// Creates a Resize gradient operation and returns the result tensor.
///
/// Computes the gradient for the forward pass Resize op with identical parameters. 
/// See discussion of resizeTensor for more in depth description of resize paramters.
///
/// - Parameters:
///   - gradient: Incoming gradient tensor
///   - input: Forward pass input tensor
///   - mode: The resampling mode to use. If nearest sampling is specifed, RoundPreferCeil mode will be used.
///   - centerResult: Controls if the result image is centered on the input image. When NO, the result will have the top left corner aligned
///   - alignCorners: When YES, the result image will have the same value as the input image in the corners
///   - layout: Specifies what layout the provided tensor is in. The returned tensor will follow the same layout. Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeWithGradientTensor:(MPSGraphTensor *) gradient
                                       input:(MPSGraphTensor *) input
                                        mode:(MPSGraphResizeMode) mode
                                centerResult:(BOOL) centerResult
                                alignCorners:(BOOL) alignCorners
                                      layout:(MPSGraphTensorNamedDataLayout) layout
                                        name:(NSString * _Nullable) name;

/// Creates a Resize gradient operation and returns the result tensor.
///
/// Computes the gradient for the forward pass Resize op with identical parameters. 
/// See discussion of resizeTensor for more in depth description of resize paramters.
///
/// - Parameters:
///   - gradient: Incoming gradient tensor
///   - input: Forward pass input tensor
///   - nearestRoundingMode: The rounding mode to use when using nearest resampling.
///   - centerResult: Controls if the result image is centered on the input image. When NO, the result will have the top left corner aligned
///   - alignCorners: When YES, the result image will have the same value as the input image in the corners
///   - layout: Specifies what layout the provided tensor is in. The returned tensor will follow the same layout. Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeNearestWithGradientTensor:(MPSGraphTensor *) gradient
                                              input:(MPSGraphTensor *) input
                                nearestRoundingMode:(MPSGraphResizeNearestRoundingMode) nearestRoundingMode
                                       centerResult:(BOOL) centerResult
                                       alignCorners:(BOOL) alignCorners
                                             layout:(MPSGraphTensorNamedDataLayout) layout
                                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// Creates a Resize gradient operation and returns the result tensor.
///
/// Computes the gradient for the forward pass Resize op with identical parameters. 
/// See discussion of resizeTensor for more in depth description of resize paramters.
///
/// - Parameters:
///   - gradient: Incoming gradient tensor
///   - input: Forward pass input tensor
///   - centerResult: Controls if the result image is centered on the input image. When NO, the result will have the top left corner aligned
///   - alignCorners: When YES, the result image will have the same value as the input image in the corners
///   - layout: Specifies what layout the provided tensor is in. The returned tensor will follow the same layout. Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeBilinearWithGradientTensor:(MPSGraphTensor *) gradient
                                               input:(MPSGraphTensor *) input
                                        centerResult:(BOOL) centerResult
                                        alignCorners:(BOOL) alignCorners
                                              layout:(MPSGraphTensorNamedDataLayout) layout
                                                name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));


/// Creates a Resize gradient operation and returns the result tensor.
///
/// Computes the gradient for the forward pass Resize op with identical parameters. 
/// See discussion of resizeTensor for more in depth description of resize paramters.
///
/// - Parameters:
///   - gradient: Incoming gradient tensor
///   - input: Forward pass input tensor
///   - scaleOffset: 1D float tensor. A 4-element shape as [scaleY, scaleX, offsetY, offsetX]
///   - mode: The resampling mode to use. If nearest sampling is specifed, RoundPreferCeil mode will be used.
///   - layout: Specifies what layout the provided tensor is in. The returned tensor will follow the same layout. Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeWithGradientTensor:(MPSGraphTensor *) gradient
                                       input:(MPSGraphTensor *) input
                           scaleOffsetTensor:(MPSGraphTensor *) scaleOffset
                                        mode:(MPSGraphResizeMode) mode
                                      layout:(MPSGraphTensorNamedDataLayout) layout
                                        name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// Creates a Resize gradient operation and returns the result tensor.
///
/// Computes the gradient for the forward pass Resize op with identical parameters. 
/// See discussion of resizeTensor for more in depth description of resize paramters.
///
/// - Parameters:
///   - gradient: Incoming gradient tensor
///   - input: Forward pass input tensor
///   - scale: 1D float tensor of size equal to rank of input.
///   - offset: 1D float tensor of size equal to rank of input.
///   - mode: The resampling mode to use. If nearest sampling is specifed, RoundPreferCeil mode will be used.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeWithGradientTensor:(MPSGraphTensor *) gradient
                                       input:(MPSGraphTensor *) input
                                 scaleTensor:(MPSGraphTensor *) scale
                                offsetTensor:(MPSGraphTensor *) offset
                                        mode:(MPSGraphResizeMode) mode
                                        name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));

/// Creates a Resize gradient operation and returns the result tensor.
///
/// Computes the gradient for the forward pass Resize op with identical parameters.
/// See discussion of resizeTensor for more in depth description of resize paramters.
///
/// - Parameters:
///   - gradient: Incoming gradient tensor
///   - input: Forward pass input tensor
///   - scaleOffset: 1D float tensor. A 4-element shape as [scaleY, scaleX, offsetY, offsetX]
///   - nearestRoundingMode: The rounding mode to use when using nearest resampling.
///   - layout: Specifies what layout the provided tensor is in. The returned tensor will follow the same layout. Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeNearestWithGradientTensor:(MPSGraphTensor *) gradient
                                              input:(MPSGraphTensor *) input
                                  scaleOffsetTensor:(MPSGraphTensor *) scaleOffset
                                nearestRoundingMode:(MPSGraphResizeNearestRoundingMode) nearestRoundingMode
                                             layout:(MPSGraphTensorNamedDataLayout) layout
                                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// Creates a Resize gradient operation and returns the result tensor.
///
/// Computes the gradient for the forward pass Resize op with nearest neighbor sampling and identical parameters.
/// See discussion of resizeTensor for more in depth description of resize paramters.
///
/// - Parameters:
///   - gradient: Incoming gradient tensor
///   - input: Forward pass input tensor
///   - scale: 1D float tensor of size equal to rank of input.
///   - offset: 1D float tensor of size equal to rank of input.
///   - nearestRoundingMode: The rounding mode to use when using nearest resampling. Default is roundPreferCeil.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeNearestWithGradientTensor:(MPSGraphTensor *) gradient
                                              input:(MPSGraphTensor *) input
                                        scaleTensor:(MPSGraphTensor *) scale
                                       offsetTensor:(MPSGraphTensor *) offset
                                nearestRoundingMode:(MPSGraphResizeNearestRoundingMode) nearestRoundingMode
                                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));

/// Creates a Resize gradient operation and returns the result tensor.
///
/// Computes the gradient for the forward pass Resize op with bilinear sampling and identical parameters.
/// See discussion of resizeTensor for more in depth description of resize paramters.
///
/// - Parameters:
///   - gradient: Incoming gradient tensor
///   - input: Forward pass input tensor
///   - scaleOffset: 1D float tensor. A 4-element shape as [scaleY, scaleX, offsetY, offsetX]
///   - layout: Specifies what layout the provided tensor is in. The returned tensor will follow the same layout. Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeBilinearWithGradientTensor:(MPSGraphTensor *) gradient
                                               input:(MPSGraphTensor *) input
                                   scaleOffsetTensor:(MPSGraphTensor *) scaleOffset
                                              layout:(MPSGraphTensorNamedDataLayout) layout
                                                name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// Creates a Resize gradient operation and returns the result tensor.
///
/// Computes the gradient for the forward pass Resize op with bilinear sampling and identical parameters.
///
/// - Parameters:
///   - gradient: Incoming gradient tensor
///   - input: Forward pass input tensor
///   - scale: 1D float tensor of size equal to rank of input.
///   - offset: 1D float tensor of size equal to rank of input.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object
-(MPSGraphTensor *) resizeBilinearWithGradientTensor:(MPSGraphTensor *) gradient
                                               input:(MPSGraphTensor *) input
                                         scaleTensor:(MPSGraphTensor *) scale
                                        offsetTensor:(MPSGraphTensor *) offset
                                                name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));


@end

NS_ASSUME_NONNULL_END


#endif /* MPSGraphResizeOps_h */
