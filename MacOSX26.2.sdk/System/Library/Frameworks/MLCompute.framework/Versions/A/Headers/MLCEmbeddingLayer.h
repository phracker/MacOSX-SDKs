//
//  MLCEmbeddingLayer.h
//  MLCompute
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MLCompute/MLCLayer.h>

@class MLCEmbeddingDescriptor;
@class MLCTensorParameter;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCEmbeddingLayer
 *  @abstract   An embedding layer which stores the words embedding
 *  @discussion For details refer to: https://pytorch.org/docs/stable/nn.html#embedding
 *              Only supported on CPU and can only be used as the first layer in a graph. If needs to be used with another graph compiled for a GPU device,
 *              a second graph containing the embedding layer can be created first. The result of this layer can then be fed as an input to the second graph
 *              and respectively the gradient result of the first layer of the second graph can be passed to this graph for weight update.
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.0, 14.0, 14.0)
@interface MLCEmbeddingLayer : MLCLayer

@property (readonly, nonatomic, copy) MLCEmbeddingDescriptor *descriptor;

/*! @property   weights
 *  @abstract   The array of word embeddings
 */
@property (readonly, nonatomic, retain) MLCTensor *weights;

/*! @property   weightsParameter
    @abstract   The weights tensor parameter used for optimizer update
 */
@property (readonly, nonatomic, retain) MLCTensorParameter *weightsParameter;

+ (instancetype)layerWithDescriptor:(MLCEmbeddingDescriptor *)descriptor
                            weights:(MLCTensor *)weights;

@end

NS_ASSUME_NONNULL_END

