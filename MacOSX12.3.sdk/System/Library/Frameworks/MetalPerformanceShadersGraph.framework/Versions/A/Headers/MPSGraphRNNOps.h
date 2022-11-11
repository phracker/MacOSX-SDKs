//
//  MPSGraphRNNOps.h
//  MPSGraphRNNOps
//
//  Created by trantalaiho on 9/29/21.
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef MPSGraphRNNOps_h
#define MPSGraphRNNOps_h


#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @typedef    MPSGraphRNNActivation
 *  @abstract   Activation mode for RNN ops.
 */
typedef NS_ENUM(NSUInteger, MPSGraphRNNActivation)
{
    MPSGraphRNNActivationNone           MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4)) MPS_SWIFT_NAME(none)   =  0L,
    MPSGraphRNNActivationRelu           MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4)),
    MPSGraphRNNActivationTanh           MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4)),
    MPSGraphRNNActivationSigmoid        MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4)),
    MPSGraphRNNActivationHardSigmoid    MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4)),
};


MPS_CLASS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4))
@interface MPSGraphSingleGateRNNDescriptor : NSObject<NSCopying>

/*!
 *  @property   reverse
 *  @discussion If set then the input sequence is passed in reverse time order to the layer.
 *              Note: Ignored when @code bidirectional = YES @endcode.
 *              Default value: @code NO @endcode
 */
@property (readwrite, nonatomic) BOOL reverse;

/*!
 *  @property   bidirectional
 *  @discussion If set then the input sequence is traversed in both directions and the two results
 *              are concatenated together on the channel-axis.
 *              Default value: @code NO @endcode
 */
@property (readwrite, nonatomic) BOOL bidirectional;


/*!
 *  @property   training
 *  @discussion If set then the layer will produce training state tensor as a secondary output.
 *              Default value: @code NO @endcode
 */
@property (readwrite, nonatomic) BOOL training;

/*!
 *  @property   activation
 *  @discussion Activation function to use with the RNN op.
 *              Default value: @code MPSGraphRNNActivationRelu @endcode
 */
@property (readwrite, nonatomic) MPSGraphRNNActivation activation;

+(nullable instancetype) descriptor;

@end

MPS_CLASS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4))
@interface MPSGraphLSTMDescriptor : NSObject<NSCopying>

/*!
 *  @property   reverse
 *  @discussion If set then the input sequence is passed in reverse time order to the layer.
 *              Note: Ignored when @code bidirectional = YES @endcode.
 *              Default value: @code NO @endcode
 */
@property (readwrite, nonatomic) BOOL reverse;

/*!
 *  @property   bidirectional
 *  @discussion If set then the input sequence is traversed in both directions and the two results
 *              are concatenated together on the channel-axis.
 *              Default value: @code NO @endcode
 */
@property (readwrite, nonatomic) BOOL bidirectional;

/*!
 *  @property   produceCell
 *  @discussion If set then this layer will produce the internal cell of the LSTM unit as secondary output.
 *              Default value: @code NO @endcode
 */
@property (readwrite, nonatomic) BOOL produceCell;

/*!
 *  @property   training
 *  @discussion If set then the layer will produce training state tensor as a secondary or third output.
 *              Default value: @code NO @endcode
 */
@property (readwrite, nonatomic) BOOL training;

/*!
 *  @property   forgetGateLast
 *  @discussion If set then the layer will use the gate-ordering `[ i, z, f, o ]` instead of default `[ i, f, z, o ]`.
 *              Default value: @code NO @endcode
 */
@property (readwrite, nonatomic) BOOL forgetGateLast;

/*!
 *  @property   inputGateActivation
 *  @discussion Activation function to use with the input gate of the LSTM  op.
 *              Default value: @code MPSGraphRNNActivationSigmoid @endcode
 */
@property (readwrite, nonatomic) MPSGraphRNNActivation inputGateActivation;

/*!
 *  @property   forgetGateActivation
 *  @discussion Activation function to use with the forget gate of the LSTM  op.
 *              Default value: @code MPSGraphRNNActivationSigmoid @endcode
 */
@property (readwrite, nonatomic) MPSGraphRNNActivation forgetGateActivation;

/*!
 *  @property   cellGateActivation
 *  @discussion Activation function to use with the cell gate of the LSTM  op.
 *              Default value: @code MPSGraphRNNActivationTanh @endcode
 */
@property (readwrite, nonatomic) MPSGraphRNNActivation cellGateActivation;

/*!
 *  @property   outputGateActivation
 *  @discussion Activation function to use with the output gate of the LSTM  op.
 *              Default value: @code MPSGraphRNNActivationSigmoid @endcode
 */
@property (readwrite, nonatomic) MPSGraphRNNActivation outputGateActivation;

/*!
 *  @property   activation
 *  @discussion Activation function to use with the current cell value of the LSTM  op.
 *              Default value: @code MPSGraphRNNActivationTanh @endcode
 */
@property (readwrite, nonatomic) MPSGraphRNNActivation activation;

+(nullable instancetype) descriptor;

@end

MPS_CLASS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4))
@interface MPSGraph(MPSGraphRNNOps)

/*!
 *  @abstract   Create a single-gate RNN op and return the value and optionally training state tensor.
 *  @discussion This operation returns tensors `h` and optionally `z` that are defined recursively as follows:
 *              @code
 *                for t = 0 to T-1
 *                   z[t] = x[t] W^T + (h[t-1] * m) R^T + b
 *                   h[t] = activation( z[t] ), where
 *              @endcode
 *              `W` is optional @ref inputWeight, `R` is @ref recurrentWeight, `b` is @ref bias, `m` is optional @mask,
 *              `x[t]` is @ref source `h[t]` is the first output, `z[t]` is the second output (optional) and `h[-1]` is @ref initState.
 *              See @ref MPSGraphSingleGateRNNDescriptor for different `activation` options.
 *
 *  @param      source                          Tensor containing the source data `x[t]` - shape should be [T,N,I].
 *                                In case `inputWeight = nil` and `bidirectional = NO` then the layout is [T,N,H]
 *                                and for `inputWeight = nil` and `bidirectional = YES` the layout is [T,N,2H].
 *  @param      recurrentWeight      Tensor containing the recurrent weights `R`.
 *                                For `bidirectional` the layout is [2,H,H] and otherwise it is [H,H].
 *  @param      inputWeight               Tensor containing the input weights matrix `W` - optional, if missing assumes diagonal unit-matrix.
 *                                For `bidirectional` the layout is [2H,I] and otherwise it is [H,I].
 *  @param      bias                               Tensor containing the bias `b` - optional, if missing assumes zeroes.
 *                                For `bidirectional` the layout is [2H] and otherwise it is [H].
 *  @param      initState                    Initial internal state of the RNN `h[-1]` - optional, if missing assumes zeroes.
 *                                For `bidirectional` the layout is [N,2H] and otherwise it is [N,H].
 *  @param      mask                               Tensor containing the mask `m` - optional, if missing assumes ones. Useful for dropout.
 *  @param      descriptor                  The RNN op definition.
 *  @param      name                               The name for the operation.
 *
 *  @return     A valid MPSGraphTensor array of size 1 or 2, depending on value of @ref  `descriptor.training`.
 *              The layout of the both outputs are [T,N,H] or [T,N,2H] for bidirectional.
 */

-(NSArray<MPSGraphTensor *> *) singleGateRNNWithSourceTensor:(MPSGraphTensor *) source
                                             recurrentWeight:(MPSGraphTensor *) recurrentWeight
                                                 inputWeight:(MPSGraphTensor * _Nullable) inputWeight
                                                        bias:(MPSGraphTensor * _Nullable) bias
                                                   initState:(MPSGraphTensor * _Nullable) initState
                                                        mask:(MPSGraphTensor * _Nullable) mask
                                                  descriptor:(MPSGraphSingleGateRNNDescriptor *) descriptor
                                                        name:(NSString * _Nullable) name
MPS_SWIFT_NAME( singleGateRNN(_:recurrentWeight:inputWeight:bias:initState:mask:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

-(NSArray<MPSGraphTensor *> *) singleGateRNNWithSourceTensor:(MPSGraphTensor *) source
                                             recurrentWeight:(MPSGraphTensor *) recurrentWeight
                                                 inputWeight:(MPSGraphTensor * _Nullable) inputWeight
                                                        bias:(MPSGraphTensor * _Nullable) bias
                                                   initState:(MPSGraphTensor * _Nullable) initState
                                                  descriptor:(MPSGraphSingleGateRNNDescriptor *) descriptor
                                                        name:(NSString * _Nullable) name
MPS_SWIFT_NAME( singleGateRNN(_:recurrentWeight:inputWeight:bias:initState:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

-(NSArray<MPSGraphTensor *> *) singleGateRNNWithSourceTensor:(MPSGraphTensor *) source
                                             recurrentWeight:(MPSGraphTensor *) recurrentWeight
                                                   initState:(MPSGraphTensor * _Nullable) initState
                                                  descriptor:(MPSGraphSingleGateRNNDescriptor *) descriptor
                                                        name:(NSString * _Nullable) name
MPS_SWIFT_NAME( singleGateRNN(_:recurrentWeight:initState:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/*!
 *  @abstract   Create a single-gate RNN gradient op and return the gradient tensor values.
 *
 *  @param      source                          Tensor containing the source data `x[t]` - shape should be [T,N,I].
 *                                In case `inputWeight = nil` and `bidirectional = NO` then the layout is [T,N,H]
 *                                and for `inputWeight = nil` and `bidirectional = YES` the layout is [T,N,2H].
 *  @param      recurrentWeight      Tensor containing the recurrent weights `R`.
 *                                For `bidirectional` the layout is [2,H,H] and otherwise it is [H,H].
 *                                Note: For `bidirectional` this tensor must have a static shape.
 *  @param      sourceGradient         Input gradient, that is gradient of a tensor wrt. to first output of the forward pass.
 *  @param      zState                          The second output of `singleGateRNNWithSourceTensor` with @ref `descriptor.training = true`.
 *  @param      stateGradient           Input gradient coming from the future timestep - optional, if missing assumes zeroes.
 *  @param      inputWeight               Tensor containing the input weights matrix `W` - optional, if missing assumes diagonal unit-matrix.
 *                                For `bidirectional` the layout is [2H,I] and otherwise it is [H,I].
 *  @param      bias                               Tensor containing the bias `b` - optional, if missing assumes zeroes.
 *                                For `bidirectional` the layout is [2H] and otherwise it is [H].
 *  @param      initState                    Initial internal state of the RNN `h[-1]` - optional, if missing assumes zeroes.
 *                                For `bidirectional` the layout is [N,2H] and otherwise it is [N,H].
 *  @param      mask                               Tensor containing the mask `m` - optional, if missing assumes ones. Useful for dropout.
 *  @param      descriptor                  The RNN op definition.
 *  @param      name                               The name for the operation.
 *
 *  @return     A valid MPSGraphTensor array containing gradients for each input tensor, except for `sourceGradient` and `mask`.
 *              In case an input is nil, no gradient will be returned for it.
 *              The order of the gradients will be: for source, for recurrentWeight, for inputWeight, for bias, for initState.
 */

-(NSArray<MPSGraphTensor *> *) singleGateRNNGradientsWithSourceTensor:(MPSGraphTensor *) source
                                                      recurrentWeight:(MPSGraphTensor *) recurrentWeight
                                                       sourceGradient:(MPSGraphTensor *) sourceGradient
                                                               zState:(MPSGraphTensor *) zState
                                                        stateGradient:(MPSGraphTensor * _Nullable) stateGradient
                                                          inputWeight:(MPSGraphTensor * _Nullable) inputWeight
                                                                 bias:(MPSGraphTensor * _Nullable) bias
                                                            initState:(MPSGraphTensor * _Nullable) initState
                                                                 mask:(MPSGraphTensor * _Nullable) mask
                                                           descriptor:(MPSGraphSingleGateRNNDescriptor *) descriptor
                                                                 name:(NSString * _Nullable) name
MPS_SWIFT_NAME( singleGateRNNGradients(_:recurrentWeight:sourceGradient:zState:stateGradient:inputWeight:bias:initState:mask:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

-(NSArray<MPSGraphTensor *> *) singleGateRNNGradientsWithSourceTensor:(MPSGraphTensor *) source
                                                      recurrentWeight:(MPSGraphTensor *) recurrentWeight
                                                       sourceGradient:(MPSGraphTensor *) sourceGradient
                                                               zState:(MPSGraphTensor *) zState
                                                          inputWeight:(MPSGraphTensor * _Nullable) inputWeight
                                                                 bias:(MPSGraphTensor * _Nullable) bias
                                                            initState:(MPSGraphTensor * _Nullable) initState
                                                                 mask:(MPSGraphTensor * _Nullable) mask
                                                           descriptor:(MPSGraphSingleGateRNNDescriptor *) descriptor
                                                                 name:(NSString * _Nullable) name
MPS_SWIFT_NAME( singleGateRNNGradients(_:recurrentWeight:sourceGradient:zState:inputWeight:bias:initState:mask:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

-(NSArray<MPSGraphTensor *> *) singleGateRNNGradientsWithSourceTensor:(MPSGraphTensor *) source
                                                      recurrentWeight:(MPSGraphTensor *) recurrentWeight
                                                       sourceGradient:(MPSGraphTensor *) sourceGradient
                                                               zState:(MPSGraphTensor *) zState
                                                          inputWeight:(MPSGraphTensor * _Nullable) inputWeight
                                                                 bias:(MPSGraphTensor * _Nullable) bias
                                                            initState:(MPSGraphTensor * _Nullable) initState
                                                           descriptor:(MPSGraphSingleGateRNNDescriptor *) descriptor
                                                                 name:(NSString * _Nullable) name
MPS_SWIFT_NAME( singleGateRNNGradients(_:recurrentWeight:sourceGradient:zState:inputWeight:bias:initState:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

-(NSArray<MPSGraphTensor *> *) singleGateRNNGradientsWithSourceTensor:(MPSGraphTensor *) source
                                                      recurrentWeight:(MPSGraphTensor *) recurrentWeight
                                                       sourceGradient:(MPSGraphTensor *) sourceGradient
                                                               zState:(MPSGraphTensor *) zState
                                                            initState:(MPSGraphTensor * _Nullable) initState
                                                           descriptor:(MPSGraphSingleGateRNNDescriptor *) descriptor
                                                                 name:(NSString * _Nullable) name
MPS_SWIFT_NAME( singleGateRNNGradients(_:recurrentWeight:sourceGradient:zState:initState:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/*!
 *  @abstract   Create a LSTM op and return the value and optionally the cell state and optionally the training state tensor.
 *  @discussion This operation returns tensors `h` and optionally `c` and optionally `z` that are defined recursively as follows:
 *              @code
 *                for t = 0 to T-1
 *                   z[t] = [i, f, z, o][t] = f( (h[t-1] m) R^T + x'[t] + p*c[t-1] )`
 *                   x'[t] = x[t] W^T + b
 *                   c[t] = f[t] * c[t-1] + i[t] * z[t]
 *                   h[t] = o[t] * g(c[t]), where
 *              @endcode
 *              `W` is optional @ref inputWeight, `R` is @ref recurrentWeight, `b` is optional @ref bias, `m` is optional @mask,
 *              `x[t]` is @ref source `h[t]` is the first output, `c[t]` is the second output (optional),
 *              `z[t]` is either the second or third output (optional), `h[-1]` is @ref initCell.  and `h[-1]` is @ref initState.
 *              `p` is an optional peephole vector.
 *              See @ref MPSGraphLSTMDescriptor for different `activation` options for `f()` and `g()`.
 *
 *  @param      source                          Tensor containing the source data `x[t]` - shape should be [T,N,I].
 *                                In case `inputWeight = nil` and `bidirectional = NO` then the layout is [T,N,4H]
 *                                and for `inputWeight = nil` and `bidirectional = YES` the layout is [T,N,8H].
 *  @param      recurrentWeight      Tensor containing the recurrent weights `R`.
 *                                For `bidirectional` the layout is [2,4H,H] and otherwise it is [4H,H].
 *  @param      inputWeight               Tensor containing the input weights matrix `W` - optional, if missing assumes diagonal unit-matrix.
 *                                For `bidirectional` the layout is [8H,I] and otherwise it is [4H,I].
 *  @param      bias                               Tensor containing the bias `b` - optional, if missing assumes zeroes.
 *                                For `bidirectional` the layout is [8H] and otherwise it is [4H].
 *  @param      initState                    Initial internal state of the LSTM `h[-1]` - optional, if missing assumes zeroes.
 *                                For `bidirectional` the layout is [N,2H] and otherwise it is [N,H].
 *  @param      initCell                      Initial internal cell of the LSTM `h[-1]` - optional, if missing assumes zeroes.
 *                                For `bidirectional` the layout is [N,2H] and otherwise it is [N,H].
 *  @param      mask                               Tensor containing the mask `m` - optional, if missing assumes ones. Useful for dropout.
 *  @param      peephole                      Tensor containing the peephole vector `v` - optional, if missing assumes zeroes.
 *                                Shape is [4H], ie. a vector for each gate, or [2,4H] for bidirectional.
 *  @param      descriptor                  The LSTM op definition.
 *  @param      name                               The name for the operation.
 *
 *  @return     A valid MPSGraphTensor array of size 1 or 2 or 3, depending on value of @ref  `descriptor.produceCell` and @ref  `descriptor.training`.
 *              The layout of the both state and cell outputs are [T,N,H] or [T,N,2H] for bidirectional,
 *              and the layout of the trainingState output is [T,N,4H] or [T,N,8H] for bidirectional,.
 */

-(NSArray<MPSGraphTensor *> *) LSTMWithSourceTensor:(MPSGraphTensor *) source
                                    recurrentWeight:(MPSGraphTensor *) recurrentWeight
                                        inputWeight:(MPSGraphTensor * _Nullable) inputWeight
                                               bias:(MPSGraphTensor * _Nullable) bias
                                          initState:(MPSGraphTensor * _Nullable) initState
                                           initCell:(MPSGraphTensor * _Nullable) initCell
                                               mask:(MPSGraphTensor * _Nullable) mask
                                           peephole:(MPSGraphTensor * _Nullable) peephole
                                         descriptor:(MPSGraphLSTMDescriptor *) descriptor
                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( LSTM(_:recurrentWeight:inputWeight:bias:initState:initCell:mask:peephole:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

-(NSArray<MPSGraphTensor *> *) LSTMWithSourceTensor:(MPSGraphTensor *) source
                                    recurrentWeight:(MPSGraphTensor *) recurrentWeight
                                        inputWeight:(MPSGraphTensor * _Nullable) inputWeight
                                               bias:(MPSGraphTensor * _Nullable) bias
                                          initState:(MPSGraphTensor * _Nullable) initState
                                           initCell:(MPSGraphTensor * _Nullable) initCell
                                         descriptor:(MPSGraphLSTMDescriptor *) descriptor
                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( LSTM(_:recurrentWeight:inputWeight:bias:initState:initCell:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

-(NSArray<MPSGraphTensor *> *) LSTMWithSourceTensor:(MPSGraphTensor *) source
                                    recurrentWeight:(MPSGraphTensor *) recurrentWeight
                                          initState:(MPSGraphTensor * _Nullable) initState
                                           initCell:(MPSGraphTensor * _Nullable) initCell
                                         descriptor:(MPSGraphLSTMDescriptor *) descriptor
                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( LSTM(_:recurrentWeight:initState:initCell:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/*!
 *  @abstract   Create a LSTM gradient op and return the gradient tensor values.
 *
 *  @param      source                          Tensor containing the source data `x[t]` - shape should be [T,N,I].
 *                                In case `inputWeight = nil` and `bidirectional = NO` then the layout is [T,N,4H]
 *                                and for `inputWeight = nil` and `bidirectional = YES` the layout is [T,N,8H].
 *  @param      recurrentWeight      Tensor containing the recurrent weights `R`.
 *                                For `bidirectional` the layout is [2,4H,H] and otherwise it is [4H,H].
 *  @param      sourceGradient         Input gradient, that is gradient of a tensor wrt. to first output of the forward pass.
 *  @param      cellOutputFwd           The second output of `LSTMWithSourceTensor` with @ref `descriptor.training = true` or `descriptor.produceCell = true`.
 *  @param      zState                          The third output of `LSTMWithSourceTensor` with @ref `descriptor.training = true`.
 *  @param      stateGradient           Input gradient for state coming from the future timestep - optional, if missing assumes zeroes.
 *  @param      cellGradient             Input gradient for cell coming from the future timestep - optional, if missing assumes zeroes.
 *  @param      inputWeight               Tensor containing the input weights matrix `W` - optional, if missing assumes diagonal unit-matrix.
 *                                For `bidirectional` the layout is [8H,I] and otherwise it is [4H,I].
 *  @param      bias                               Tensor containing the bias `b` - optional, if missing assumes zeroes.
 *                                For `bidirectional` the layout is [8H] and otherwise it is [4H].
 *  @param      initState                    Initial internal state of the LSTM `h[-1]` - optional, if missing assumes zeroes.
 *                                For `bidirectional` the layout is [N,2H] and otherwise it is [N,H].
 *  @param      initCell                      Initial internal cell of the LSTM `h[-1]` - optional, if missing assumes zeroes.
 *                                For `bidirectional` the layout is [N,2H] and otherwise it is [N,H].
 *  @param      mask                               Tensor containing the mask `m` - optional, if missing assumes ones. Useful for dropout.
 *  @param      peephole                      Tensor containing the peephole vector `v` - optional, if missing assumes zeroes. Shape is [8H], ie. a vector for each gate.
 *  @param      descriptor                  The LSTM op definition.
 *  @param      name                               The name for the operation.
 *
 *  @return     A valid MPSGraphTensor array containing gradients for each input tensor, except for `sourceGradient` and `mask`.
 *              In case an input is nil, no gradient will be returned for it.
 *              The order of the gradients will be: for source, for recurrentWeight, for inputWeight, for bias, for peephole, for initState, for initCell.
 */

-(NSArray<MPSGraphTensor *> *) LSTMGradientsWithSourceTensor:(MPSGraphTensor *) source
                                             recurrentWeight:(MPSGraphTensor *) recurrentWeight
                                              sourceGradient:(MPSGraphTensor *) sourceGradient
                                                      zState:(MPSGraphTensor *) zState
                                               cellOutputFwd:(MPSGraphTensor *) cellOutputFwd
                                               stateGradient:(MPSGraphTensor * _Nullable) stateGradient
                                                cellGradient:(MPSGraphTensor * _Nullable) cellGradient
                                                 inputWeight:(MPSGraphTensor * _Nullable) inputWeight
                                                        bias:(MPSGraphTensor * _Nullable) bias
                                                   initState:(MPSGraphTensor * _Nullable) initState
                                                    initCell:(MPSGraphTensor * _Nullable) initCell
                                                        mask:(MPSGraphTensor * _Nullable) mask
                                                    peephole:(MPSGraphTensor * _Nullable) peephole
                                                  descriptor:(MPSGraphLSTMDescriptor *) descriptor
                                                        name:(NSString * _Nullable) name
MPS_SWIFT_NAME( LSTMGradients(_:recurrentWeight:sourceGradient:zState:cellOutputFwd:stateGradient:cellGradient:inputWeight:bias:initState:initCell:mask:peephole:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

-(NSArray<MPSGraphTensor *> *) LSTMGradientsWithSourceTensor:(MPSGraphTensor *) source
                                             recurrentWeight:(MPSGraphTensor *) recurrentWeight
                                              sourceGradient:(MPSGraphTensor *) sourceGradient
                                                      zState:(MPSGraphTensor *) zState
                                               cellOutputFwd:(MPSGraphTensor *) cellOutputFwd
                                                 inputWeight:(MPSGraphTensor * _Nullable) inputWeight
                                                        bias:(MPSGraphTensor * _Nullable) bias
                                                   initState:(MPSGraphTensor * _Nullable) initState
                                                    initCell:(MPSGraphTensor * _Nullable) initCell
                                                        mask:(MPSGraphTensor * _Nullable) mask
                                                  descriptor:(MPSGraphLSTMDescriptor *) descriptor
                                                        name:(NSString * _Nullable) name
MPS_SWIFT_NAME( LSTMGradients(_:recurrentWeight:sourceGradient:zState:cellOutputFwd:inputWeight:bias:initState:initCell:mask:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

-(NSArray<MPSGraphTensor *> *) LSTMGradientsWithSourceTensor:(MPSGraphTensor *) source
                                             recurrentWeight:(MPSGraphTensor *) recurrentWeight
                                              sourceGradient:(MPSGraphTensor *) sourceGradient
                                                      zState:(MPSGraphTensor *) zState
                                               cellOutputFwd:(MPSGraphTensor *) cellOutputFwd
                                                 inputWeight:(MPSGraphTensor * _Nullable) inputWeight
                                                        bias:(MPSGraphTensor * _Nullable) bias
                                                   initState:(MPSGraphTensor * _Nullable) initState
                                                    initCell:(MPSGraphTensor * _Nullable) initCell
                                                  descriptor:(MPSGraphLSTMDescriptor *) descriptor
                                                        name:(NSString * _Nullable) name
MPS_SWIFT_NAME( LSTMGradients(_:recurrentWeight:sourceGradient:zState:cellOutputFwd:inputWeight:bias:initState:initCell:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

-(NSArray<MPSGraphTensor *> *) LSTMGradientsWithSourceTensor:(MPSGraphTensor *) source
                                             recurrentWeight:(MPSGraphTensor *) recurrentWeight
                                              sourceGradient:(MPSGraphTensor *) sourceGradient
                                                      zState:(MPSGraphTensor *) zState
                                               cellOutputFwd:(MPSGraphTensor *) cellOutputFwd
                                                  descriptor:(MPSGraphLSTMDescriptor *) descriptor
                                                        name:(NSString * _Nullable) name
MPS_SWIFT_NAME( LSTMGradients(_:recurrentWeight:sourceGradient:zState:cellOutputFwd:descriptor:name:))
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

@end

NS_ASSUME_NONNULL_END
#endif /* MPSGraphRNNOps_h */
