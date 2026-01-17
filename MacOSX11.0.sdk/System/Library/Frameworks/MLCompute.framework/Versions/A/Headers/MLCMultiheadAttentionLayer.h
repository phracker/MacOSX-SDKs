//
//  MLCMultiheadAttentionLayer.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>
#import <MLCompute/MLCLayer.h>
#import <MLCompute/MLCMultiheadAttentionDescriptor.h>

@class MLCDevice;
@class MLCTensor;
@class MLCTensorData;
@class MLCTensorParameter;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCMultiheadAttentionLayer
    @abstract   A multi-head attention layer
    @discussion A multi-head "Scaled Dot-Product Attention" layer which attends to one or more entries in the input key-value pairs
                N=Batch, S=source length, L=target length, E = model(embedding) dimension
                The sources to this layer are of shapes: Query:(N,L,E), Key:(N,S,E), Value:(N,S,E), KeyMask:(N,S), AttentionMask(1,L,S)
                where KeyMask and AttentionMask are optional and none, either or both of them can be passed.
                Output is of shape:(N,L,E). Only the case of modelDim = keyDim = valueDim is currently supported,
                For details refer to: https://pytorch.org/docs/stable/nn.html#multiheadattention
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCMultiheadAttentionLayer : MLCLayer

/*! @property   descriptor
    @abstract   The multi-head attention descriptor
 */
@property (readonly, nonatomic, copy) MLCMultiheadAttentionDescriptor *descriptor;

/*! @property   weights
    @abstract   The weights of query, key, value and output projections
 */
@property (readonly, nonatomic, retain) NSArray<MLCTensor *> *weights;

/*! @property   biases
    @abstract   The biases of query, key, value and output projections
 */
@property (readonly, nonatomic, retain, nullable) NSArray<MLCTensor *> *biases;

/*! @property   attentionBiases
    @abstract   The biases added to key and value
 */
@property (readonly, nonatomic, retain, nullable) NSArray<MLCTensor *> *attentionBiases;

/*! @property   weightsParameters
    @abstract   The weights tensor parameters used for optimizer update
 */
@property (readonly, nonatomic, retain) NSArray<MLCTensorParameter *> *weightsParameters;

/*! @property   biasesParameters
    @abstract   The biases tensor parameters used for optimizer update
 */
@property (readonly, nonatomic, nullable, retain) NSArray<MLCTensorParameter *> *biasesParameters;

/*! @abstract   Create a multi-head attention layer
    @param      weights  weights corresponding to query, key, value and output projections for all heads
    @param      biases  Optional, biases corresponding to query, key, value and output projections for all heads
    @param      attentionBiases  Optional, An array of biases added to the key and value respectively
    @return     A new MultiheadAttention layer
 */
+ (instancetype _Nullable)layerWithDescriptor:(MLCMultiheadAttentionDescriptor *)descriptor
                                      weights:(NSArray<MLCTensor *> *)weights
                                       biases:(NSArray<MLCTensor *> * _Nullable)biases
                              attentionBiases:(NSArray<MLCTensor *> * _Nullable)attentionBiases;


@end

NS_ASSUME_NONNULL_END
