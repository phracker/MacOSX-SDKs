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

typedef NS_ENUM(NSUInteger, MPSGraphResizeMode)
{
    MPSGraphResizeNearest        MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0)) MPS_SWIFT_NAME(nearest)   =  0L,
    MPSGraphResizeBilinear       MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                           =  1L,
};

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphResizeOps)

/*!
 *  @abstract   Create Resize op and return the result tensor
 *  @discussion Resamples input images to given size. Result images will be distorted if size is of different aspect ratio.
 *              Resize supports the following modes:
 *                  Nearest Neighnor - values are interpolated using the closest neighbor pixel
 *                  Bilinear - values are computed using bilinear interpolation of 4 neighboring pixels
 *
 *              Destination indices are computed using direct index scaling by default, with no offset added.
 *              If the centerResult parameter is true, the destination indices will be scaled and shifted to be centered
 *              on the input image.
 *              If the alignCorners parameter is true, the corners of the result images will match the input images.
 *              Scaling will be modified to a factor of (size - 1) / (inputSize - 1). When alignCorners is true, the
 *              centerResult parameter does nothing.
 *
 *              In order to achieve the same behavior as OpenCV's resize and TensorFlowV2's resize,
 *              @code
 *                  centerResult = YES;
 *                  alginCorners = NO;
 *              @endcode
 *
 *              To achieve the same behavior as TensorFlowV1 resize
 *              @code
 *                  centerResult = NO;
 *              @endcode
 *
 *  @param      imagesTensor    Tensor containing input images.
 *  @param      size                      A 2-element shape as [newHeight, newWidth]
 *  @param      mode                      The resampling mode to use.
 *  @param      centerResult    Controls if the result image is centered on the input image. When NO, the result will have the top left corner aligned
 *  @param      alignCorners    When YES, the result image will have the same value as the input image in the corners
 *  @param      layout                  Specifies what layout the provided tensor is in. The returned tensor will follow the same layout.
 *                            Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
 *  @param      name                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) resizeTensor:(MPSGraphTensor *) imagesTensor
                            size:(MPSShape *) size
                            mode:(MPSGraphResizeMode) mode
                    centerResult:(BOOL) centerResult
                    alignCorners:(BOOL) alignCorners
                          layout:(MPSGraphTensorNamedDataLayout) layout
                            name:(NSString * _Nullable) name;


/*!
 *  @abstract   Create Resize gradient op and return the result tensor
 *  @discussion Computes the gradient for the forward pass Resize op with identical parameters.
 *              See discussion of resizeTensor for more in depth description of resize paramters.
 *
 *  @param      gradient             Incoming gradient tensor
 *  @param      input                    Forward pass input tensor
 *  @param      mode                      The resampling mode to use.
 *  @param      centerResult    Controls if the result image is centered on the input image. When NO, the result will have the top left corner aligned
 *  @param      alignCorners    When YES, the result image will have the same value as the input image in the corners
 *  @param      layout                  Specifies what layout the provided tensor is in. The returned tensor will follow the same layout.
 *                            Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
 *  @param      name                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) resizeWithGradientTensor:(MPSGraphTensor *) gradient
                                       input:(MPSGraphTensor *) input
                                        mode:(MPSGraphResizeMode) mode
                                centerResult:(BOOL) centerResult
                                alignCorners:(BOOL) alignCorners
                                      layout:(MPSGraphTensorNamedDataLayout) layout
                                        name:(NSString * _Nullable) name;

@end

NS_ASSUME_NONNULL_END


#endif /* MPSGraphResizeOps_h */
