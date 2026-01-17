//
//  MLCGraph.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>

@class MLCTensor;
@class MLCLayer;
@class MLCTensorData;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCGraph
    @discussion A graph of layers that can be used to build a training or inference graph
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.0, 14.0, 14.0)
@interface MLCGraph : NSObject

/*! @abstract   The device to be used when compiling and executing a graph
 */
@property (readonly, nonatomic, nullable, retain) MLCDevice *device;

/*! @abstract   Layers in the graph
 */
@property (readonly, nonatomic) NSArray<MLCLayer *> *layers;

/*! @abstract   Creates a new graph.
    @return     A new graph.
 */
+ (instancetype)graph;

/*! @abstract A DOT representation of the graph.
    @discussion For more info on the DOT language, refer to https://en.wikipedia.org/wiki/DOT_(graph_description_language).
                Edges that have a dashed lines are those that have stop gradients, while those with solid lines don't.
*/
@property (readonly, nonatomic) NSString *summarizedDOTDescription;

/*! @abstract   Add a layer to the graph
    @param      layer        The layer
    @param      source      The source tensor
    @return     A result tensor
 */
- (MLCTensor * _Nullable)nodeWithLayer:(MLCLayer *)layer
                                source:(MLCTensor *)source;

/*! @abstract   Add a layer to the graph
    @param      layer        The layer
    @param      sources    A list of source tensors
    @discussion For variable length sequences of LSTMs/RNNs layers, create an MLCTensor of sortedSequenceLengths and pass it as the last index (i.e. index 2 or 4) of sources. This tensor must of be type MLCDataTypeInt32.
    @return     A result tensor
 */
- (MLCTensor * _Nullable)nodeWithLayer:(MLCLayer *)layer
                               sources:(NSArray<MLCTensor *> *)sources;

/*! @abstract   Add a layer to the graph
    @param      layer                       The layer
    @param      sources                   A list of source tensors
    @param      disableUpdate     A flag to indicate if optimizer update should be disabled for this layer
    @discussion For variable length sequences of LSTMs/RNNs layers, create an MLCTensor of sortedSequenceLengths and pass it as the last index (i.e. index 2 or 4) of sources. This tensor must of be type MLCDataTypeInt32.
    @return     A result tensor
 */
- (MLCTensor * _Nullable)nodeWithLayer:(MLCLayer *)layer
                               sources:(NSArray<MLCTensor *> *)sources
                         disableUpdate:(BOOL)disableUpdate;

/*! @abstract   Add a loss layer to the graph
    @param      layer                      The loss layer
    @param      lossLabels           The loss labels tensor
    @discussion For variable length sequences of LSTMs/RNNs layers, create an MLCTensor of sortedSequenceLengths and pass it as the last index (i.e. index 2 or 4) of sources. This tensor must of be type MLCDataTypeInt32.
    @return     A result tensor
 */
- (MLCTensor * _Nullable)nodeWithLayer:(MLCLayer *)layer
                               sources:(NSArray<MLCTensor *> *)sources
                            lossLabels:(NSArray<MLCTensor *> *)lossLabels;

/*! @abstract   Add a split layer to the graph
    @param      source                         The source tensor
    @param      splitCount                The number of splits
    @param      dimension                  The dimension to split the source tensor
    @return     A result tensor
 */
- (NSArray<MLCTensor *> * _Nullable)splitWithSource:(MLCTensor *)source
                                         splitCount:(NSUInteger)splitCount
                                          dimension:(NSUInteger)dimension
NS_SWIFT_NAME(split(source:splitCount:dimension:));

/*! @abstract   Add a split layer to the graph
    @param      source                                     The source tensor
    @param      splitSectionLengths        The lengths of each split section
    @param      dimension                              The dimension to split the source tensor
    @return     A result tensor
 */
- (NSArray<MLCTensor *> * _Nullable)splitWithSource:(MLCTensor *)source
                                splitSectionLengths:(NSArray<NSNumber *> *)splitSectionLengths
                                          dimension:(NSUInteger)dimension
NS_REFINED_FOR_SWIFT;

/*! @abstract   Add a concat layer to the graph
    @param      sources      The source tensors to concatenate
    @param      dimension  The concatenation dimension
    @return     A result tensor
 */
- (MLCTensor * _Nullable)concatenateWithSources:(NSArray<MLCTensor *> *)sources
                                      dimension:(NSUInteger)dimension
NS_SWIFT_NAME(concatenate(sources:dimension:));

/*! @abstract   Add a reshape layer to the graph
    @param      shape                     An array representing the shape of result tensor
    @param      source                   The source tensor
    @return     A result tensor
 */
- (MLCTensor * _Nullable)reshapeWithShape:(NSArray<NSNumber *> *)shape
                                   source:(MLCTensor *)source
NS_REFINED_FOR_SWIFT;

/*! @abstract   Add a transpose layer to the graph
    @param      dimensions NSArray<NSNumber *> representing the desired ordering of dimensions
                The dimensions array specifies the input axis source for each output axis, such that the
                K'th element in the dimensions array specifies the input axis source for the K'th axis in the
                output.  The batch dimension which is typically axis 0 cannot be transposed.
    @return     A result tensor
 */
- (MLCTensor * _Nullable)transposeWithDimensions:(NSArray<NSNumber *> *)dimensions
                                          source:(MLCTensor *)source
NS_REFINED_FOR_SWIFT;


/*! @abstract   Add a select layer to the graph
    @param      sources            The source tensors
    @param      condition        The condition mask
    @return     A result tensor
 */
- (MLCTensor * _Nullable)selectWithSources:(NSArray<MLCTensor *> *)sources
                                 condition:(MLCTensor *)condition
MLCOMPUTE_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5))
NS_REFINED_FOR_SWIFT;

/*! @abstract   Add a scatter layer to the graph
    @param      dimension             The dimension along which to index
    @param      source                    The updates to use with scattering with index positions specified in indices to result tensor
    @param      indices                  The index of elements to scatter
    @param      copyFrom                The source tensor whose data is  to be first copied to the result tensor
    @param      reductionType     The reduction type applied for all values in source tensor that are scattered to a specific location in the result tensor.
                                Must be: MLCReductionTypeNone or MLCReductionTypeSum.
    @return     A result tensor
 */
- (MLCTensor * _Nullable)scatterWithDimension:(NSUInteger)dimension
                                       source:(MLCTensor *)source
                                      indices:(MLCTensor *)indices
                                     copyFrom:(MLCTensor *)copyFrom
                                reductionType:(MLCReductionType)reductionType
MLCOMPUTE_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5));

/*! @abstract   Add a gather layer to the graph
    @param      dimension       The dimension along which to index
    @param      source              The source tensor
    @param      indices            The index of elements to gather
    @return     A result tensor
 */
- (MLCTensor * _Nullable)gatherWithDimension:(NSUInteger)dimension
                                      source:(MLCTensor *)source
                                     indices:(MLCTensor *)indices
MLCOMPUTE_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5));


/*! @abstract   Associates data with input tensors. If the device is GPU, also copies the data to the device memory.
                Returns true if the data is successfully associated with input tensors.
    @discussion This function should be used if you execute the forward, gradient and optimizer updates independently.
                Before the forward pass is executed, the inputs should be written to device memory.  Similarly, before the
                gradient pass is executed, the inputs (typically the initial gradient tensor) should be written to device
                memory.  The caller must guarantee the lifetime of the underlying memory of each value of \p inputsData
                for the entirety of each corresponding input tensor's lifetime.
    @param      inputsData        The input data to use to write to device memory
    @param      inputTensors    The list of tensors to perform writes on
    @param      device                 The device
    @param      batchSize          The batch size.  This should be set to the actual batch size that may be used when we execute
                              the graph and can be a value less than or equal to the batch size specified in the tensor.
                              If set to 0, we use batch size specified in the tensor.
    @param      synchronous     Whether to execute the copy to the device synchronously.  For performance, asynchronous
                             execution is recommended.
    @return     A Boolean value indicating whether the data is successfully associated with the tensor.
 */
- (BOOL)bindAndWriteData:(NSDictionary<NSString *, MLCTensorData *> *)inputsData
               forInputs:(NSDictionary<NSString *, MLCTensor *> *)inputTensors
                toDevice:(MLCDevice *)device
               batchSize:(NSUInteger)batchSize
             synchronous:(BOOL)synchronous;

/*! @abstract   Associates data with input tensors. If the device is GPU, also copies the data to the device memory.
                Returns true if the data is successfully associated with input tensors.
    @discussion This function should be used if you execute the forward, gradient and optimizer updates independently.
                Before the forward pass is executed, the inputs should be written to device memory.  Similarly, before the
                gradient pass is executed, the inputs (typically the initial gradient tensor) should be written to device
                memory.  The caller must guarantee the lifetime of the underlying memory of each value of \p inputsData
                for the entirety of each corresponding input tensor's lifetime.
    @param      inputsData        The input data to use to write to device memory
    @param      inputTensors    The list of tensors to perform writes on
    @param      device                 The device
    @param      synchronous     Whether to execute the copy to the device synchronously.  For performance, asynchronous
                             execution is recommended.
    @return     A Boolean value indicating whether the data is successfully associated with the tensor.
 */
- (BOOL)bindAndWriteData:(NSDictionary<NSString *, MLCTensorData *> *)inputsData
               forInputs:(NSDictionary<NSString *, MLCTensor *> *)inputTensors
                toDevice:(MLCDevice *)device
             synchronous:(BOOL)synchronous;

/*! @abstract   Get the source tensors for a layer in the training graph
    @param      layer   A layer in the training graph
    @return     A list of tensors
 */
- (NSArray<MLCTensor *> *)sourceTensorsForLayer:(MLCLayer *)layer;

/*! @abstract   Get the result tensors for a layer in the training graph
    @param      layer   A layer in the training graph
    @return     A list of tensors
 */
- (NSArray<MLCTensor *> *)resultTensorsForLayer:(MLCLayer *)layer;

@end

NS_ASSUME_NONNULL_END
