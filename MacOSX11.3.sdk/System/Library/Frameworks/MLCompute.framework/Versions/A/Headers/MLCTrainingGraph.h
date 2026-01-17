//
//  MLCTrainingGraph.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>

@class MLCTensor;
@class MLCTensorParameter;
@class MLCLayer;
@class MLCDevice;
@class MLCOptimizer;
@class MLCGraph;
@class MLCTensorData;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCTrainingGraph
    @discussion A training graph created from one or more MLCGraph objects
                plus additional layers added directly to the training graph.
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCTrainingGraph : MLCGraph

/*! @property   optimizer
    @abstract   The optimizer to be used with the training graph
 */
@property (readonly, nonatomic, nullable, retain) MLCOptimizer *optimizer;

/*! @property   The device memory size used by the training graph
    @abstract   Returns the total size in bytes of device memory used for all intermediate tensors
                for forward, gradient passes and optimizer update for all layers in the training graph.
                We recommend executing an iteration before checking the device memory size as
                the buffers needed get allocated when the corresponding pass such as gradient,
                optimizer update is executed.
    @return     A NSUInteger value
 */
@property (readonly, nonatomic) NSUInteger   deviceMemorySize;

/*! @abstract   Create a training graph
    @param      graphObjects    The layers from these graph objects will be added to the training graph
    @param      lossLayer           The loss layer to use.  The loss layer can also be added to the training graph
                              using nodeWithLayer:sources:lossLabels
    @param      optimizer           The optimizer to use
    @return     A new training graph object
 */
+ (instancetype)graphWithGraphObjects:(NSArray<MLCGraph *> *)graphObjects
                            lossLayer:(MLCLayer * _Nullable)lossLayer
                            optimizer:(MLCOptimizer * _Nullable)optimizer;

/*! @abstract   Add the list of inputs to the training graph
    @param      inputs           The inputs
    @param      lossLabels  The loss label inputs
    @return     A boolean indicating success or failure
 */
- (BOOL)addInputs:(NSDictionary<NSString *, MLCTensor *> *)inputs
       lossLabels:(NSDictionary<NSString *, MLCTensor *> * _Nullable)lossLabels;

/*! @abstract   Add the list of inputs to the training graph
    @discussion Each input, loss label or label weights tensor is identified by a NSString.
                When the training graph is executed, this NSString is used to identify which data object
                should be as input data for each tensor whose device memory needs to be updated
                before the graph is executed.
    @param      inputs                        The inputs
    @param      lossLabels               The loss label inputs
    @param      lossLabelWeights  The loss label weights
    @return     A boolean indicating success or failure
 */
- (BOOL)addInputs:(NSDictionary<NSString *, MLCTensor *> *)inputs
       lossLabels:(NSDictionary<NSString *, MLCTensor *> * _Nullable)lossLabels
 lossLabelWeights:(NSDictionary<NSString *, MLCTensor *> * _Nullable)lossLabelWeights;

/*! @abstract   Add the list of outputs to the training graph
    @param      outputs           The outputs
    @return     A boolean indicating success or failure
 */
- (BOOL)addOutputs:(NSDictionary<NSString *, MLCTensor *> *)outputs;

/*! @abstract   Add the list of tensors whose contributions are not to be taken when computing gradients during gradient pass
    @param      tensors           The list of tensors
    @return     A boolean indicating success or failure
 */
- (BOOL)stopGradientForTensors:(NSArray<MLCTensor *> *)tensors;

/*! @abstract   Compile the training graph for a device.
    @param      options     The compiler options to use when compiling the training graph
    @param      device       The MLCDevice object
    @return     A boolean indicating success or failure
 */
- (BOOL)compileWithOptions:(MLCGraphCompilationOptions)options
                    device:(MLCDevice *)device;

/*! @abstract   Compile the training graph for a device.
    @discussion Specifying the list of constant tensors when we compile the graph allows MLCompute to perform additional optimizations at compile time.
    @param      options                      The compiler options to use when compiling the training graph
    @param      device                        The MLCDevice object
    @param      inputTensors           The list of input tensors that are constants
    @param      inputTensorsData  The tensor data to be used with these constant input tensors
    @return     A boolean indicating success or failure
 */
- (BOOL)compileWithOptions:(MLCGraphCompilationOptions)options
                    device:(MLCDevice *)device
      inputTensors:(NSDictionary<NSString *, MLCTensor *> * _Nullable)inputTensors
  inputTensorsData:(NSDictionary<NSString *, MLCTensorData *> * _Nullable)inputTensorsData
    MLCOMPUTE_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5));

/*! @abstract   Compile the optimizer to be used with a training graph.
    @discussion Typically the optimizer to be used with a training graph is specifed when the training graph is created using
                graphWithGraphObjects:lossLayer:optimizer.  The optimizer will be compiled in when compileWithOptions:device
                is called if an optimizer is specified with the training graph.  In the case where the optimizer to be used is not known
                when the graph is created or compiled, this method can be used to associate and compile a training graph with an optimizer.
    @param      optimizer       The MLCOptimizer object
    @return     A boolean indicating success or failure
 */
- (BOOL)compileOptimizer:(MLCOptimizer *)optimizer;

/*! @abstract   Link mutiple training graphs
    @discussion This is used to link subsequent training graphs with first training sub-graph.
                This method should be used when we have tensors shared by one or more layers in multiple sub-graphs
    @param      graphs       The list of training graphs to link
    @return     A boolean indicating success or failure
 */
- (BOOL)linkWithGraphs:(NSArray<MLCTrainingGraph *> *)graphs;

/*! @abstract   Get the gradient tensor for an input tensor
    @param      input   The input tensor
    @return     The gradient tensor
 */
- (MLCTensor * _Nullable)gradientTensorForInput:(MLCTensor *)input;

/*! @abstract   Get the source gradient tensors for a layer in the training graph
    @param      layer   A layer in the training graph
    @return     A list of tensors
 */
- (NSArray<MLCTensor *> *)sourceGradientTensorsForLayer:(MLCLayer *)layer;

/*! @abstract   Get the result gradient tensors for a layer in the training graph
    @param      layer   A layer in the training graph
    @return     A list of tensors
 */
- (NSArray<MLCTensor *> *)resultGradientTensorsForLayer:(MLCLayer *)layer;

/*! @abstract   Get the gradient data for a trainable parameter associated with a layer
    @discussion This can be used to get the gradient data for weights or biases parameters associated with a convolution,
                fully connected or convolution transpose layer
    @param      parameter   The updatable parameter associated with the layer
    @param      layer   A layer in the training graph.  Must be one of the following:
                      - MLCConvolutionLayer
                      - MLCFullyConnectedLayer
                      - MLCBatchNormalizationLayer
                      - MLCInstanceNormalizationLayer
                      - MLCGroupNormalizationLayer
                      - MLCLayerNormalizationLayer
                      - MLCEmbeddingLayer
                      - MLCMultiheadAttentionLayer
    @return     The gradient data.  Will return nil if the layer is marked as not trainable or if
                training graph is not executed with separate calls to forward and gradient passes.
*/
- (NSData * _Nullable)gradientDataForParameter:(MLCTensor *)parameter
                                         layer:(MLCLayer *)layer;

/*! @abstract   Allocate an entry for a user specified gradient for a tensor
    @param      tensor   A result tensor produced by a layer in the training graph
                       that is input to some user specified code and will need to
                       provide a user gradient during the gradient pass.
    @return     A gradient tensor
 */
- (MLCTensor * _Nullable)allocateUserGradientForTensor:(MLCTensor *)tensor;

/*! @abstract   Execute the training graph (forward, gradient and optimizer update) with given source and label data
    @discussion Execute the training graph with given source and label data.  If an optimizer is specified, the optimizer update is applied.
                If MLCExecutionOptionsSynchronous is specified in 'options', this method returns after the graph has been executed.
                Otherwise, this method returns after the graph has been queued for execution. The completion handler is called after the graph
                has finished execution.
    @param      inputsData                               The data objects to use for inputs
    @param      lossLabelsData                      The data objects to use for loss labels
    @param      lossLabelWeightsData         The data objects to use for loss label weights
    @param      batchSize                                 The batch size to use.  For a graph where batch size changes between layers this value must be 0.
    @param      options                                      The execution options
    @param      completionHandler                The completion handler
    @return     A boolean indicating success or failure
*/
- (BOOL)executeWithInputsData:(NSDictionary<NSString *, MLCTensorData *> *)inputsData
               lossLabelsData:(NSDictionary<NSString *, MLCTensorData *> * _Nullable)lossLabelsData
         lossLabelWeightsData:(NSDictionary<NSString *, MLCTensorData *> * _Nullable)lossLabelWeightsData
                    batchSize:(NSUInteger)batchSize
                      options:(MLCExecutionOptions)options
            completionHandler:(MLCGraphCompletionHandler _Nullable)completionHandler
    NS_SWIFT_NAME(execute(inputsData:lossLabelsData:lossLabelWeightsData:batchSize:options:completionHandler:));


/*! @abstract   Execute the training graph (forward, gradient and optimizer update) with given source and label data
    @param      inputsData                               The data objects to use for inputs
    @param      lossLabelsData                      The data objects to use for loss labels
    @param      lossLabelWeightsData         The data objects to use for loss label weights
    @param      outputsData                             The data objects to use for outputs
    @param      batchSize                                 The batch size to use.  For a graph where batch size changes between layers this value must be 0.
    @param      options                                     The execution options
    @param      completionHandler               The completion handler
    @return     A boolean indicating success or failure
*/
- (BOOL)executeWithInputsData:(NSDictionary<NSString *, MLCTensorData *> *)inputsData
               lossLabelsData:(NSDictionary<NSString *, MLCTensorData *> * _Nullable)lossLabelsData
         lossLabelWeightsData:(NSDictionary<NSString *, MLCTensorData *> * _Nullable)lossLabelWeightsData
                  outputsData:(NSDictionary<NSString *, MLCTensorData *> * _Nullable)outputsData
                    batchSize:(NSUInteger)batchSize
                      options:(MLCExecutionOptions)options
            completionHandler:(MLCGraphCompletionHandler _Nullable)completionHandler
    NS_SWIFT_NAME(execute(inputsData:lossLabelsData:lossLabelWeightsData:outputsData:batchSize:options:completionHandler:));

/*! @abstract   Execute the forward pass of the training graph
    @param      batchSize                         The batch size to use.  For a graph where batch size changes between layers this value must be 0.
    @param      options                             The execution options
    @param      completionHandler       The completion handler
    @return     A boolean indicating success or failure
 */
- (BOOL)executeForwardWithBatchSize:(NSUInteger)batchSize
                            options:(MLCExecutionOptions)options
                  completionHandler:(MLCGraphCompletionHandler _Nullable)completionHandler
    NS_SWIFT_NAME(executeForward(batchSize:options:completionHandler:));

/*! @abstract   Execute the forward pass for the training graph
    @param      batchSize                         The batch size to use.  For a graph where batch size changes between layers this value must be 0.
    @param      options                             The execution options
    @param      outputsData                     The data objects to use for outputs
    @param      completionHandler       The completion handler
    @return     A boolean indicating success or failure
 */
- (BOOL)executeForwardWithBatchSize:(NSUInteger)batchSize
                            options:(MLCExecutionOptions)options
                        outputsData:(NSDictionary<NSString *, MLCTensorData *> * _Nullable)outputsData
                  completionHandler:(MLCGraphCompletionHandler _Nullable)completionHandler
    NS_SWIFT_NAME(executeForward(batchSize:options:outputsData:completionHandler:));

/*! @abstract   Execute the gradient pass of the training graph
    @param      batchSize                         The batch size to use.  For a graph where batch size changes between layers this value must be 0.
    @param      options                             The execution options
    @param      completionHandler       The completion handler
    @return     A boolean indicating success or failure
 */
- (BOOL)executeGradientWithBatchSize:(NSUInteger)batchSize
                             options:(MLCExecutionOptions)options
                   completionHandler:(MLCGraphCompletionHandler _Nullable)completionHandler
    NS_SWIFT_NAME(executeGradient(batchSize:options:completionHandler:));

/*! @abstract   Execute the gradient pass of the training graph
    @param      batchSize                         The batch size to use.  For a graph where batch size changes between layers this value must be 0.
    @param      options                             The execution options
    @param      outputsData                     The data objects to use for outputs
    @param      completionHandler       The completion handler
    @return     A boolean indicating success or failure
 */
- (BOOL)executeGradientWithBatchSize:(NSUInteger)batchSize
                             options:(MLCExecutionOptions)options
                         outputsData:(NSDictionary<NSString *, MLCTensorData *> * _Nullable)outputsData
                   completionHandler:(MLCGraphCompletionHandler _Nullable)completionHandler
    NS_SWIFT_NAME(executeGradient(batchSize:options:outputsData:completionHandler:));

/*! @abstract   Execute the optimizer update pass of the training graph
    @param      options                             The execution options
    @param      completionHandler       The completion handler
    @return     A boolean indicating success or failure
 */
- (BOOL)executeOptimizerUpdateWithOptions:(MLCExecutionOptions)options
                        completionHandler:(MLCGraphCompletionHandler _Nullable)completionHandler
    NS_SWIFT_NAME(executeOptimizerUpdate(options:completionHandler:));


/*! @abstract   Synchronize updates (weights/biases from convolution, fully connected and LSTM layers, tensor parameters)
                from device memory to host memory.
 */
- (void)synchronizeUpdates;

/*! @abstract   Set the input tensor parameters that also will be updated by the optimizer
    @discussion These represent the list of input tensors to be updated when we execute the optimizer update
                Weights, bias or beta, gamma tensors are not included in this list.  MLCompute automatically
                adds them to the parameter list based on whether the layer is marked as updatable or not.
    @param      parameters   The list of input tensors to be updated by the optimizer
    @return     A boolean indicating success or failure
 */
- (BOOL)setTrainingTensorParameters:(NSArray<MLCTensorParameter *> *)parameters
    NS_SWIFT_NAME(setTrainingTensorParameters(_:));

/*! @abstract   Associates the given optimizer data and device data buffers with the tensor.
                Returns true if the data is successfully associated with the tensor and copied to the device.
    @discussion The caller must guarantee the lifetime of the underlying memory of \p data for the entirety of the tensor's
                lifetime.  The \p deviceData buffers are allocated by MLCompute.  This method must be called
                before executeOptimizerUpdateWithOptions or executeWithInputsData is called for the training graph.
                We recommend using this method instead of using [MLCTensor bindOptimizerData] especially if the
                optimizer update is being called multiple times for each batch.
    @param      data                The optimizer data to be associated with the tensor
    @param      deviceData  The optimizer device data to be associated with the tensor
    @param      tensor           The tensor
    @return     A Boolean value indicating whether the data is successfully associated with the tensor .
*/
- (BOOL)bindOptimizerData:(NSArray<MLCTensorData *> *)data
               deviceData:(NSArray<MLCTensorOptimizerDeviceData *> * _Nullable)deviceData
               withTensor:(MLCTensor *)tensor;

@end

NS_ASSUME_NONNULL_END
