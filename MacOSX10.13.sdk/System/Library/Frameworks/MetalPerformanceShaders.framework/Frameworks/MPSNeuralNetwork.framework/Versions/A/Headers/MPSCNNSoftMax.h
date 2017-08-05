//
//  MPSCNNSoftMax.h
//  MPS
//
//  Created by Ian Ollmann on 8/21/16.
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef MPSCNNSoftMax_h
#define MPSCNNSoftMax_h

#include <MPSNeuralNetwork/MPSCNNKernel.h>

#ifdef __cplusplus
extern "C" {
#endif


/*!
 *  @class      MPSCNNSoftMax
 *  @dependency This depends on Metal.framework
 *  @discussion The softmax filter is a neural transfer function and is useful for classification tasks.
 *              The softmax filter is applied across feature channels and in a convolutional manner at all
 *              spatial locations. The softmax filter can be seen as the combination of an
 *              activation function (exponential) and a normalization operator.
 *              For each feature channel per pixel in an image in a feature map, the softmax filter computes the following:
 *                  result channel in pixel = exp(pixel(x,y,k))/sum(exp(pixel(x,y,0)) ... exp(pixel(x,y,N-1))
 *                      where N is the number of feature channels
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface MPSCNNSoftMax : MPSCNNKernel

@end    /* MPSCNNSoftMax */

/*!
 *  @class      MPSCNNLogSoftMax
 *  @dependency This depends on Metal.framework
 *  @discussion The logarithmic softmax filter can be achieved by taking the natural logarithm of the
 *              the result of the softmax filter. The results are often used to construct a loss function to be
 *              minimized when training neural networks.
 *              For each feature channel per pixel in an image in a feature map, the logarithmic softmax filter
 *              computes the following:
 *                  result channel in pixel = pixel(x,y,k)) - ln{sum(exp(pixel(x,y,0)) ... exp(pixel(x,y,N-1))}
 *                      where N is the number of feature channels and y = ln{x} satisfies e^y = x.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface MPSCNNLogSoftMax : MPSCNNKernel

@end    /* MPSCNNLogSoftMax */

#ifdef __cplusplus
}
#endif

    
#endif /* MPSCNNSoftMax_h */
