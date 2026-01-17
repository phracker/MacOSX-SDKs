//
//  MPSNNSlice.h
//  MPSNeuralNetwork
//
//  Created by Aaftab Munshi on 11/27/17.
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef MPSNNSlice_h
#define MPSNNSlice_h

#include <MPSNeuralNetwork/MPSCNNKernel.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  @class      MPSNNSlice
 *  @dependency This depends on Metal.framework
 *  @abstract   Describes a slice operation
 *  @discussion The slice kernel is used to extract a slice from a source MPSImage.  The extracted slice is copied
 *              to a destination MPSImage.  The offset and sourceFeatureChannelOffset specify the following:
 *                  - the (x, y) location in the source image
 *                  - the starting feature channel offset in the source image
 *
 *              The clipRect specifies the starting (x, y) position in the destination image to copy the slice and
 *              the size (width, height) in pixels of the slice.  The featureChannelsInSlice specifies the number of
 *              feature channels to be extracted from the source image for the slice.  The featureChannels extracted
 *              from the slice are copied to the destination MPSImage starting at feature channel offset 0.
 *
 *              Some examples of slice operations can be found at:
 *                   http://mxnet.incubator.apache.org/api/python/ndarray.html?highlight=slice#mxnet.ndarray.slice
 *                   https://www.tensorflow.org/api_docs/python/tf/slice
 */

MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface MPSNNSlice : MPSCNNKernel

/*!
 *  @abstract Initialize a MPSNNSlice kernel
 *  @param    device            The device the filter will run on
 *  @return   A valid MPSNNSlice object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;


-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(__nonnull id<MTLDevice>)device    NS_DESIGNATED_INITIALIZER;

@end  /* MPSNNSlice */


#ifdef __cplusplus
}
#endif

#endif /* MPSNNSlice_h */

