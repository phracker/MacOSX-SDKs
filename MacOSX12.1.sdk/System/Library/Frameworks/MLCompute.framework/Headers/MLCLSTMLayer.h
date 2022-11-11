//
//  MLCLSTMLayer.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>
#import <MLCompute/MLCLayer.h>
#import <MLCompute/MLCActivationDescriptor.h>
#import <MLCompute/MLCLSTMDescriptor.h>

@class MLCDevice;
@class MLCTensor;
@class MLCTensorParameter;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCLSTMLayer
    @abstract   A LSTM layer
    @discussion The hidden and cell state for inputs and outputs have a layout of [numberOfLayers, numberOfDirections, batchSize, hiddenSize].
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCLSTMLayer : MLCLayer

/*! @property   descriptor
    @abstract   The LSTM descriptor
 */
@property (readonly, nonatomic, copy) MLCLSTMDescriptor *descriptor;

/*! @property   gateActivations
    @abstract   The array of gate activations for input, hidden, cell and output gates
    @discussion The default gate activations are: sigmoid, sigmoid, tanh, sigmoid
 */
@property (readonly, nonatomic, copy) NSArray<MLCActivationDescriptor *> *gateActivations;

/*! @property   outputResultActivation
    @abstract   The output activation descriptor
 */
@property (readonly, nonatomic, copy) MLCActivationDescriptor *outputResultActivation;

/*! @property   inputWeights
    @abstract   The array of tensors describing the input weights for the input, hidden, cell and output gates
 */
@property (readonly, nonatomic, retain) NSArray<MLCTensor *> *inputWeights;

/*! @property   hiddenWeights
    @abstract   The array of tensors describing the hidden weights for the input, hidden, cell and output gates
 */
@property (readonly, nonatomic, retain) NSArray<MLCTensor *> *hiddenWeights;

/*! @property   peepholeWeights
    @abstract   The array of tensors describing the peephole weights for the input, hidden, cell and output gates
 */
@property (readonly, nonatomic, nullable, retain) NSArray<MLCTensor *> *peepholeWeights;

/*! @property   biases
    @abstract   The array of tensors describing the bias terms for the input, hidden, cell and output gates
 */
@property (readonly, nonatomic, nullable, retain) NSArray<MLCTensor *> *biases;

/*! @property   inputWeightsParameters
    @abstract   The input weights tensor parameters used for optimizer update
 */
@property (readonly, nonatomic, retain) NSArray<MLCTensorParameter *> *inputWeightsParameters;

/*! @property   hiddenWeightsParameters
    @abstract   The hidden weights tensor parameters used for optimizer update
 */
@property (readonly, nonatomic, retain) NSArray<MLCTensorParameter *> *hiddenWeightsParameters;

/*! @property   peepholeWeightsParameters
    @abstract   The peephole weights tensor parameters used for optimizer update
 */
@property (readonly, nonatomic, nullable, retain) NSArray<MLCTensorParameter *> *peepholeWeightsParameters;

/*! @property   biasesParameters
    @abstract   The bias tensor parameter used for optimizer update
 */
@property (readonly, nonatomic, nullable, retain) NSArray<MLCTensorParameter *> *biasesParameters;


/*! @abstract   Create a LSTM layer
    @param      descriptor               The LSTM descriptor
    @param      inputWeights           An array of (layerCount * 4) tensors describing the input weights for the
                                 input, hidden, cell and output gates for layer0, layer1.. layer(n-1) for layerCount=n.
    @param      hiddenWeights         An array of (layerCount * 4) tensors describing the hidden weights for the
                                 input, hidden, cell and output gates for layer0, layer1.. layer(n-1) for layerCount=n.
    @return     A new LSTM layer.
 */
+ (instancetype _Nullable)layerWithDescriptor:(MLCLSTMDescriptor *)descriptor
                                 inputWeights:(NSArray<MLCTensor *> *)inputWeights
                                hiddenWeights:(NSArray<MLCTensor *> *)hiddenWeights
                                       biases:(NSArray<MLCTensor *> * _Nullable)biases;

/*! @abstract   Create a LSTM layer
    @param      descriptor               The LSTM descriptor
    @param      inputWeights           An array of (layerCount * 4) tensors describing the input weights for the
                                 input, hidden, cell and output gates for layer0, layer1.. layer(n-1) for layerCount=n.
    @param      hiddenWeights         An array of (layerCount * 4) tensors describing the hidden weights for the
                                 input, hidden, cell and output gates for layer0, layer1.. layer(n-1) for layerCount=n.
    @param      peepholeWeights     An array of (layerCount * 4) tensors describing the peephole weights for the
                                 input, hidden, cell and output gates for layer0, layer1.. layer(n-1) for layerCount=n.
    @return     A new LSTM layer.
 */
+ (instancetype _Nullable)layerWithDescriptor:(MLCLSTMDescriptor *)descriptor
                                 inputWeights:(NSArray<MLCTensor *> *)inputWeights
                                hiddenWeights:(NSArray<MLCTensor *> *)hiddenWeights
                              peepholeWeights:(NSArray<MLCTensor *> * _Nullable)peepholeWeights
                                       biases:(NSArray<MLCTensor *> * _Nullable)biases;

/*! @abstract   Create a LSTM layer
    @param      descriptor                            The LSTM descriptor
    @param      inputWeights                        An array of (layerCount * 4) tensors describing the input weights for the
                                       input, hidden, cell and output gates for layer0, layer1.. layer(n-1) for layerCount=n.
                                       For bidirectional LSTM, the forward time weights for all stacked layers will come first followed by backward time weights
    @param      hiddenWeights                      An array of (layerCount * 4) tensors describing the hidden weights for the
                                       input, hidden, cell and output gates for layer0, layer1.. layer(n-1) for layerCount=n.
                                       For bidirectional LSTM, the forward time weights for all stacked layers will come first followed by backward time weights
    @param      peepholeWeights                 An array of (layerCount * 4) tensors describing the peephole weights for the
                                       input, hidden, cell and output gates for layer0, layer1.. layer(n-1) for layerCount=n.
    @param      biases                               An array of (layerCount * 4) tensors describing the input weights for the
                                       input, hidden, cell and output gates for layer0, layer1.. layer(n-1) for layerCount=n.
                                       For bidirectional LSTM, the forward time bias terms for all stacked layers will come first followed by backward time bias terms
    @param      gateActivations                  An array of 4 neuron descriptors for the input, hidden, cell and output gate activations.
    @param      outputResultActivation  The neuron descriptor used for the activation function applied to output result.  Default is tanh.
    @return     A new  LSTM layer.
 */
+ (instancetype _Nullable)layerWithDescriptor:(MLCLSTMDescriptor *)descriptor
                                 inputWeights:(NSArray<MLCTensor *> *)inputWeights
                                hiddenWeights:(NSArray<MLCTensor *> *)hiddenWeights
                              peepholeWeights:(NSArray<MLCTensor *> * _Nullable)peepholeWeights
                                       biases:(NSArray<MLCTensor *> * _Nullable)biases
                              gateActivations:(NSArray<MLCActivationDescriptor *> *)gateActivations
                       outputResultActivation:(MLCActivationDescriptor *)outputResultActivation;

@end

NS_ASSUME_NONNULL_END
