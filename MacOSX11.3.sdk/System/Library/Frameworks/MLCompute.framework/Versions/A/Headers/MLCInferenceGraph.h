//
//  MLCInferenceGraph.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>

@class MLCTensor;
@class MLCLayer;
@class MLCDevice;
@class MLCTensorData;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCInferenceGraph
    @discussion An inference graph created from one or more MLCGraph objects
                plus additional layers added directly to the inference graph.
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCInferenceGraph : MLCGraph

/*! @property   The device memory size used by the inference graph
    @abstract   Returns the total size in bytes of device memory used by all intermediate tensors in the inference graph
    @return     A NSUInteger value
 */
@property (readonly, nonatomic) NSUInteger   deviceMemorySize;


+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*! @abstract   Create an inference graph
    @param      graphObjects    The layers from these graph objects will be added to the training graph
    @return     A new inference graph object
 */
+ (instancetype)graphWithGraphObjects:(NSArray<MLCGraph *> *)graphObjects;

/*! @abstract   Add the list of inputs to the inference graph
    @param      inputs           The inputs
    @return     A boolean indicating success or failure
 */
- (BOOL)addInputs:(NSDictionary<NSString *, MLCTensor *> *)inputs;

/*! @abstract   Add the list of inputs to the inference graph
    @discussion Each input, loss label or label weights tensor is identified by a NSString.
                When the inference graph is executed, this NSString is used to identify which data object
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

/*! @abstract   Add the list of outputs to the inference graph
    @param      outputs           The outputs
    @return     A boolean indicating success or failure
 */
- (BOOL)addOutputs:(NSDictionary<NSString *, MLCTensor *> *)outputs;

/*! @abstract   Compile the training graph for a device.
    @param      options     The compiler options to use when compiling the training graph
    @param      device       The MLCDevice object
    @return     A boolean indicating success or failure
 */
- (BOOL)compileWithOptions:(MLCGraphCompilationOptions)options
                    device:(MLCDevice *)device;

/*! @abstract   Compile the inference graph for a device.
    @discussion Specifying the list of constant tensors when we compile the graph allows MLCompute to perform additional optimizations at compile time.
    @param      options                      The compiler options to use when compiling the inference graph
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

/*! @abstract   Link mutiple inference graphs
    @discussion This is used to link subsequent inference graphs with first inference sub-graph.
                This method should be used when we have tensors shared by one or more layers in multiple sub-graphs
    @param      graphs     The list of inference graphs to link
    @return     A boolean indicating success or failure
 */
- (BOOL)linkWithGraphs:(NSArray<MLCInferenceGraph *> *)graphs
    NS_SWIFT_NAME(link(with:));

/*! @abstract   Execute the inference graph with given input data
    @discussion Execute the inference graph given input data.
                If MLCExecutionOptionsSynchronous is specified in 'options', this method returns after the graph has been executed.
                Otherwise, this method returns after the graph has been queued for execution.  The completion handler  is called after the graph has finished execution.
    @param      inputsData                       The data objects to use for inputs
    @param      batchSize                         The batch size to use.  For a graph where batch size changes between layers this value must be 0.
    @param      options                             The execution options
    @param      completionHandler       The completion handler
    @return     A boolean indicating success or failure
*/
- (BOOL)executeWithInputsData:(NSDictionary<NSString *, MLCTensorData *> *)inputsData
                    batchSize:(NSUInteger)batchSize
                      options:(MLCExecutionOptions)options
            completionHandler:(MLCGraphCompletionHandler _Nullable)completionHandler
    NS_SWIFT_NAME(execute(inputsData:batchSize:options:completionHandler:));

/*! @abstract   Execute the inference graph with given input data
    @discussion Execute the inference graph given input data.
                If MLCExecutionOptionsSynchronous is specified in 'options', this method returns after the graph has been executed.
                Otherwise, this method returns after the graph has been queued for execution.  The completion handler  is called after the graph has finished execution.
    @param      inputsData                       The data objects to use for inputs
    @param      outputsData                     The data objects to use for outputs
    @param      batchSize                         The batch size to use.  For a graph where batch size changes between layers this value must be 0.
    @param      options                             The execution options
    @param      completionHandler       The completion handler
    @return     A boolean indicating success or failure
*/
- (BOOL)executeWithInputsData:(NSDictionary<NSString *, MLCTensorData *> *)inputsData
                  outputsData:(NSDictionary<NSString *, MLCTensorData *> * _Nullable)outputsData
                    batchSize:(NSUInteger)batchSize
                      options:(MLCExecutionOptions)options
            completionHandler:(MLCGraphCompletionHandler _Nullable)completionHandler
    NS_SWIFT_NAME(execute(inputsData:outputsData:batchSize:options:completionHandler:));


/*! @abstract   Execute the inference graph with given input data
    @discussion Execute the inference graph given input data.
                If MLCExecutionOptionsSynchronous is specified in 'options', this method returns after the graph has been executed.
                Otherwise, this method returns after the graph has been queued for execution.  The completion handler  is called after the graph has finished execution.
    @param      inputsData                       The data objects to use for inputs
    @param      lossLabelsData              The data objects to use for loss labels
    @param      lossLabelWeightsData The data objects to use for loss label weights
    @param      batchSize                         The batch size to use.  For a graph where batch size changes between layers this value must be 0.
    @param      options                             The execution options
    @param      completionHandler       The completion handler
    @return     A boolean indicating success or failure
*/
- (BOOL)executeWithInputsData:(NSDictionary<NSString *, MLCTensorData *> *)inputsData
               lossLabelsData:(NSDictionary<NSString *, MLCTensorData *> * _Nullable)lossLabelsData
         lossLabelWeightsData:(NSDictionary<NSString *, MLCTensorData *> * _Nullable)lossLabelWeightsData
                    batchSize:(NSUInteger)batchSize
                      options:(MLCExecutionOptions)options
            completionHandler:(MLCGraphCompletionHandler _Nullable)completionHandler
    NS_SWIFT_NAME(execute(inputsData:lossLabelsData:lossLabelWeightsData:batchSize:options:completionHandler:));


/*! @abstract   Execute the inference graph with given input data
    @discussion Execute the inference graph given input data.
                If MLCExecutionOptionsSynchronous is specified in 'options', this method returns after the graph has been executed.
                Otherwise, this method returns after the graph has been queued for execution.  The completion handler  is called after the graph has finished execution.
    @param      inputsData                       The data objects to use for inputs
    @param      lossLabelsData              The data objects to use for loss labels
    @param      lossLabelWeightsData The data objects to use for loss label weights
    @param      outputsData                     The data objects to use for outputs
    @param      batchSize                         The batch size to use.  For a graph where batch size changes between layers this value must be 0.
    @param      options                             The execution options
    @param      completionHandler       The completion handler
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

@end

NS_ASSUME_NONNULL_END
