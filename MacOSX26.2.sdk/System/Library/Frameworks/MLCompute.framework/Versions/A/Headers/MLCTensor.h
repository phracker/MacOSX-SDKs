//
//  MLCTensor.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>

@class MLCDevice;
@class MLCTensorDescriptor;
@class MLCTensorData;
@class MLCTensorOptimizerDeviceData;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCTensor
    @discussion A tensor object
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.0, 14.0, 14.0)
@interface MLCTensor : NSObject<NSCopying>

/*! @property   tensorID
    @abstract   The tensor ID
    @discussion A unique number to identify each tensor.  Assigned when the tensor is created.
 */
@property (readonly, nonatomic) NSUInteger tensorID;

/*! @property   descriptor
    @abstract   The tensor descriptor
 */
@property (readonly, nonatomic, copy) MLCTensorDescriptor *descriptor;

/*! @property   data
    @abstract   The tensor data
*/
@property (readonly, nonatomic, nullable, retain) NSData *data;

/*! @property   label
    @abstract   A string to help identify this object.
 */
@property (readwrite, nonatomic, copy) NSString *label;

/*! @property   device
    @abstract   The device associated with this tensor.
 */
@property (readonly, nonatomic, nullable, retain) MLCDevice *device;

/*! @property   optimizer buffers to use if tensor is used as a parameter
    @abstract   These are the host side optimizer (momentum and velocity) buffers which developers can query and initialize
    @discussion When customizing optimizer data, the contents of these buffers must be initialized before executing optimizer
                update for a graph.
 */
@property (readonly, nonatomic, copy) NSArray<MLCTensorData *> *optimizerData;

/*! @property   optimizer device buffers to use if tensor is used as a parameter
    @abstract   These are the device side optimizer (momentum and velocity) buffers which developers can query
 */
@property (readonly, nonatomic, copy) NSArray<MLCTensorOptimizerDeviceData *> *optimizerDeviceData;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*
 * create a tensor with or without data.
 * for example, for weights used by convolution or mean, variance, beta, and gamma parameters
 * with batch normalization will create a tensor with data.
 */

/*! @abstract   Create a MLCTensor object
    @discussion Create a tensor object without any data
    @return     A new MLCTensor object
 */
+ (instancetype)tensorWithDescriptor:(MLCTensorDescriptor *)tensorDescriptor;

/*! @abstract   Create a MLCTensor object
    @discussion Create a tensor object initialized with a random initializer such as Glorot Uniform.
    @param      tensorDescriptor              The tensor descriptor
    @param      randomInitializerType   The random initializer type
    @return     A new MLCTensor object
 */
+ (instancetype)tensorWithDescriptor:(MLCTensorDescriptor *)tensorDescriptor
               randomInitializerType:(MLCRandomInitializerType)randomInitializerType;

/*! @abstract   Create a MLCTensor object
    @discussion Create a tensor object with a MLCTensorData object that specifies the tensor data buffer
    @param      tensorDescriptor              The tensor descriptor
    @param      fillData                      The scalar data to fill to tensor with
    @return     A new MLCTensor object
 */
+ (instancetype)tensorWithDescriptor:(MLCTensorDescriptor *)tensorDescriptor
                        fillWithData:(NSNumber *)fillData;

/*! @abstract   Create a MLCTensor object
    @discussion Create a tensor object with a MLCTensorData object that specifies the tensor data buffer
    @param      tensorDescriptor              The tensor descriptor
    @param      data                                         The random initializer type
    @return     A new MLCTensor object
 */
+ (instancetype)tensorWithDescriptor:(MLCTensorDescriptor *)tensorDescriptor
                                data:(MLCTensorData *)data;

#pragma mark - Convenience Methods

/*! @abstract   Create a MLCTensor object
    @discussion Create a tensor object without any data.  The tensor data type is MLCDataTypeFloat32.
    @param      shape                           The tensor shape
    @return     A new MLCTensor object
 */
+ (instancetype)tensorWithShape:(NSArray<NSNumber *> *)shape
    NS_REFINED_FOR_SWIFT;

/*! @abstract   Create a MLCTensor object
    @discussion Create a tensor object initialized with a random initializer such as Glorot Uniform.
                The tensor data type is MLCDataTypeFloat32
    @param      shape                                       The tensor shape
    @param      randomInitializerType   The random initializer type
    @return     A new MLCTensor object
 */
+ (instancetype)tensorWithShape:(NSArray<NSNumber *> *)shape
          randomInitializerType:(MLCRandomInitializerType)randomInitializerType
    NS_REFINED_FOR_SWIFT;

/*! @abstract   Create a MLCTensor object
    @discussion Create a tensor object initialized with a random initializer such as Glorot Uniform.
                The tensor data type is MLCDataTypeFloat32
    @param      shape                                       The tensor shape
    @param      randomInitializerType   The random initializer type
    @param      dataType                    The tensor data type
    @return     A new MLCTensor object
 */
+ (instancetype)tensorWithShape:(NSArray<NSNumber *> *)shape
          randomInitializerType:(MLCRandomInitializerType)randomInitializerType
                       dataType:(MLCDataType)dataType
    NS_REFINED_FOR_SWIFT;

/*! @abstract   Create a MLCTensor object
    @discussion Create a tensor object without any data
    @param      shape                           The tensor shape
    @param      dataType                    The tensor data type
    @return     A new MLCTensor object
 */
+ (instancetype)tensorWithShape:(NSArray<NSNumber *> *)shape
                       dataType:(MLCDataType)dataType
    NS_REFINED_FOR_SWIFT;

/*! @abstract   Create a MLCTensor object
    @discussion Create a tensor object with data
    @param      shape                           The tensor shape
    @param      data                             The tensor data
    @param      dataType                    The tensor data type
    @return     A new MLCTensor object
 */
+ (instancetype)tensorWithShape:(NSArray<NSNumber *> *)shape
                           data:(MLCTensorData *)data
                       dataType:(MLCDataType)dataType
    NS_REFINED_FOR_SWIFT;

/*! @abstract   Create a MLCTensor object
    @discussion Create a tensor object with data
    @param      shape                  The tensor shape
    @param      fillData               The scalar value to initialize the tensor data with
    @param      dataType               The tensor data type
    @return     A new MLCTensor object
 */
+ (instancetype)tensorWithShape:(NSArray<NSNumber *> *)shape
                   fillWithData:(NSNumber *)fillData
                       dataType:(MLCDataType)dataType
    NS_REFINED_FOR_SWIFT;

/*! @abstract   Create a MLCTensor  object
    @discussion Create a NCHW tensor object with tensor data type = MLCDataTypeFloat32
    @param      width                           The tensor width
    @param      height                         The tensor height
    @param      featureChannelCount     Number of feature channels
    @param      batchSize                  The tensor batch size
    @return     A new MLCTensor object
 */
+ (instancetype)tensorWithWidth:(NSUInteger)width
                         height:(NSUInteger)height
            featureChannelCount:(NSUInteger)featureChannelCount
                      batchSize:(NSUInteger)batchSize;

/*! @abstract   Create a MLCTensor  object
    @discussion Create a NCHW tensor object initialized with a scalar value
    @param      width                           The tensor width
    @param      height                         The tensor height
    @param      featureChannelCount     Number of feature channels
    @param      batchSize                  The tensor batch size
    @param      fillData           The scalar value to initialize the tensor data with
    @param      dataType                    The tensor data type
    @return     A new MLCTensorData object
 */
+ (instancetype)tensorWithWidth:(NSUInteger)width
                         height:(NSUInteger)height
            featureChannelCount:(NSUInteger)featureChannelCount
                      batchSize:(NSUInteger)batchSize
                   fillWithData:(float)fillData
                       dataType:(MLCDataType)dataType;

/*! @abstract   Create a MLCTensor  object
    @discussion Create a NCHW tensor object initialized with a random initializer type.
                The tensor data type is MLCDataTypeFloat32
    @param      width                                      The tensor width
    @param      height                                    The tensor height
    @param      featureChannelCount                Number of feature channels
    @param      batchSize                              The tensor batch size
    @param      randomInitializerType   The random initializer type
    @return     A new MLCTensor object
 */
+ (instancetype)tensorWithWidth:(NSUInteger)width
                         height:(NSUInteger)height
            featureChannelCount:(NSUInteger)featureChannelCount
                      batchSize:(NSUInteger)batchSize
          randomInitializerType:(MLCRandomInitializerType)randomInitializerType;

/*! @abstract   Create a MLCTensor  object
    @discussion Create a NCHW tensor object with a tensor data object
                The tensor data type is MLCDataTypeFloat32.
    @param      width                           The tensor width
    @param      height                         The tensor height
    @param      featureChannelCount     Number of feature channels
    @param      batchSize                  The tensor batch size
    @param      data                             The tensor data
    @return     A new MLCTensor object
 */
+ (instancetype)tensorWithWidth:(NSUInteger)width
                         height:(NSUInteger)height
            featureChannelCount:(NSUInteger)featureChannelCount
                      batchSize:(NSUInteger)batchSize
                           data:(MLCTensorData *)data;

/*! @abstract   Create a MLCTensor  object
    @discussion Create a NCHW tensor object with a tensor data object
                The tensor data type is MLCDataTypeFloat32.
    @param      width                           The tensor width
    @param      height                         The tensor height
    @param      featureChannelCount     Number of feature channels
    @param      batchSize                  The tensor batch size
    @param      data                             The tensor data
    @param      dataType                    The tensor data type
    @return     A new MLCTensor object
 */
+ (instancetype)tensorWithWidth:(NSUInteger)width
                         height:(NSUInteger)height
            featureChannelCount:(NSUInteger)featureChannelCount
                      batchSize:(NSUInteger)batchSize
                           data:(MLCTensorData *)data
                       dataType:(MLCDataType)dataType;

/*! @abstract   Create a MLCTensor  object
    @discussion Create a tensor typically used by a recurrent layer
                The tensor data type is MLCDataTypeFloat32.
    @param      sequenceLength       The length of sequences stored in the tensor
    @param      featureChannelCount     Number of feature channels
    @param      batchSize                  The tensor batch size
    @return     A new MLCTensor object
 */
+ (instancetype)tensorWithSequenceLength:(NSUInteger)sequenceLength
                     featureChannelCount:(NSUInteger)featureChannelCount
                               batchSize:(NSUInteger)batchSize;


/*! @abstract   Create a MLCTensor  object
    @discussion Create a tensor typically used by a recurrent layer
                The tensor data type is MLCDataTypeFloat32.
    @param      sequenceLength                   The length of sequences stored in the tensor
    @param      featureChannelCount                 Number of feature channels
    @param      batchSize                              The tensor batch size
    @param      randomInitializerType   The random initializer type
    @return     A new MLCTensor object
 */
+ (instancetype)tensorWithSequenceLength:(NSUInteger)sequenceLength
                     featureChannelCount:(NSUInteger)featureChannelCount
                               batchSize:(NSUInteger)batchSize
                   randomInitializerType:(MLCRandomInitializerType)randomInitializerType;

/*! @abstract   Create a MLCTensor  object
    @discussion Create a tensor typically used by a recurrent layer
                The tensor data type is MLCDataTypeFloat32.
    @param      sequenceLength       The length of sequences stored in the tensor
    @param      featureChannelCount     Number of feature channels
    @param      batchSize                  The tensor batch size
    @param      data                             The tensor data
    @return     A new MLCTensor object
 */
+ (instancetype)tensorWithSequenceLength:(NSUInteger)sequenceLength
                     featureChannelCount:(NSUInteger)featureChannelCount
                               batchSize:(NSUInteger)batchSize
                                    data:(MLCTensorData * _Nullable)data;


/*! @abstract   Create a MLCTensor  object
    @discussion Create a tensor of variable length sequences typically used by a recurrent layer
                The tensor data type is MLCDataTypeFloat32.
    @param      sequenceLengths                 An array of sequence lengths
    @param      sortedSequences                 A flag to indicate if the sequence lengths are sorted.  If yes, they must be sorted in descending order
    @param      featureChannelCount                 Number of feature channels
    @param      batchSize                              The tensor batch size
    @param      randomInitializerType   The random initializer type
    @return     A new MLCTensor object
 */
+ (instancetype _Nullable)tensorWithSequenceLengths:(NSArray<NSNumber *> *)sequenceLengths
                                    sortedSequences:(BOOL)sortedSequences
                                featureChannelCount:(NSUInteger)featureChannelCount
                                          batchSize:(NSUInteger)batchSize
                              randomInitializerType:(MLCRandomInitializerType)randomInitializerType
    NS_REFINED_FOR_SWIFT;

/*! @abstract   Create a MLCTensor  object
    @discussion Create a tensor of variable length sequences typically used by a recurrent layer
                The tensor data type is MLCDataTypeFloat32.
    @param      sequenceLengths     An array of sequence lengths
    @param      sortedSequences     A flag to indicate if the sequence lengths are sorted.  If yes, they must be sorted in descending order
    @param      featureChannelCount     Number of feature channels
    @param      batchSize                  The tensor batch size
    @param      data                             The tensor data
    @return     A new MLCTensor object
 */
+ (instancetype _Nullable)tensorWithSequenceLengths:(NSArray<NSNumber *> *)sequenceLengths
                                    sortedSequences:(BOOL)sortedSequences
                                featureChannelCount:(NSUInteger)featureChannelCount
                                          batchSize:(NSUInteger)batchSize
                                               data:(MLCTensorData * _Nullable)data
    NS_REFINED_FOR_SWIFT;


#pragma mark - Methods that operate on data or optimizer data associated with a tensor

/*! @abstract   Returns a Boolean value indicating whether the underlying data has valid floating-point numerics, i.e. it
                does not contain NaN or INF floating-point values.
 */
@property (readonly, nonatomic) BOOL hasValidNumerics;

/*! @abstract   Synchronize the data in host memory.
    @discussion Synchronize the data in host memory i.e. tensor.data with latest contents in device memory
                This should only be called once the graph that this tensor is used with has finished execution;
                Otherwise the results in device memory may not be up to date.
                NOTE:  This method should not be called from a completion callback when device is the GPU.
    @return     Returns YES if success, NO if there is a failure to synchronize
 */
- (BOOL)synchronizeData;

/*! @abstract   Synchronize the optimizer data in host memory.
    @discussion Synchronize the optimizer data in host memory with latest contents in device memory
                This should only be called once the graph that this tensor is used with has finished execution;
                Otherwise the results in device memory may not be up to date.
                NOTE:  This method should not be called from a completion callback when device is the GPU.
    @return     Returns YES if success, NO if there is a failure to synchronize
*/
- (BOOL)synchronizeOptimizerData;

/*! @abstract   Copy tensor data from device memory to user specified memory
    @discussion Before copying tensor data from device memory, one may need to synchronize the device memory for example
                when device is the GPU.  The synchronizeWithDevice argumet can be set appropraitely to indicate this.
                For CPU this is ignored.  If the tensor has been specified in outputs of a graph using addOutputs,
                synchronizeWithDevice should be set to NO.
                NOTE:  This method should only be called once the graph that this tensor is used with has finished execution;
                Otherwise the results in device memory may not be up to date.  synchronizeWithDevice must be set to NO
                when this method is called from a completion callback for GPU.
    @param bytes                                     The user specified data in which to copy
    @param length                                   The size in bytes to copy
    @param synchronizeWithDevice  Whether to synchronize device memory if device is GPU
    @return     Returns YES if success, NO if there is a failure to synchronize
 */
- (BOOL)copyDataFromDeviceMemoryToBytes:(void *)bytes
                                 length:(NSUInteger)length
                  synchronizeWithDevice:(BOOL)synchronizeWithDevice;

/*! @abstract   Associates the given data to the tensor. If the device is GPU, also copies the data to the device memory.
                Returns true if the data is successfully associated with the tensor and copied to the device.
    @discussion The caller must guarantee the lifetime of the underlying memory of \p data for the entirety of the tensor's
                lifetime.  For input tensors, we recommend that the bindAndwriteData method provided by MLCTrainingGraph
                and MLCInferenceGraph be used.  This method should only be used to allocate and copy data to device memory
                for tensors that are typically layer parameters such as weights, bias for convolution layers, beta, gamma for
                normalization layers.
    @param      data             The data to associated with the tensor
    @param      device           The compute device
    @return     A Boolean value indicating whether the data is successfully associated with the tensor and copied to the device.
*/
- (BOOL)bindAndWriteData:(MLCTensorData *)data
                toDevice:(MLCDevice *)device;

/*! @abstract   Associates the given optimizer data and device data buffers to the tensor.
                Returns true if the data is successfully associated with the tensor and copied to the device.
    @discussion The caller must guarantee the lifetime of the underlying memory of \p data for the entirety of the tensor's
                lifetime.  The \p deviceData buffers are allocated by MLCompute.  This method must be called
                before executeOptimizerUpdateWithOptions or executeWithInputsData is called for the training graph.
    @param      data                The optimizer data to be associated with the tensor
    @param      deviceData  The optimizer device data to be associated with the tensor
    @return     A Boolean value indicating whether the data is successfully associated with the tensor .
*/
- (BOOL)bindOptimizerData:(NSArray<MLCTensorData *> *)data
               deviceData:(NSArray<MLCTensorOptimizerDeviceData *> * _Nullable)deviceData;


/*! @abstract   Converts a 32-bit floating-point tensor with given scale and a zero point
                Returns a quantized tensor
    @param      type  The quantized data type.  Must be MLCDataTypeInt8, MLCDataTypeUInt8 or MLCDataTypeInt32
    @param      scale  The scale to apply in quantization
    @param      bias The offset value that maps to float zero
    @return     A quantized tensor
*/
- (MLCTensor * _Nullable)tensorByQuantizingToType:(MLCDataType)type
                                            scale:(float)scale
                                             bias:(NSInteger)bias
    NS_SWIFT_NAME(quantized(to:scale:bias:))
    MLCOMPUTE_AVAILABLE_STARTING(macos(12.0), ios(15), tvos(15));

/*! @abstract   Converts a 32-bit floating-point tensor with given scale and a zero point
                Returns a quantized tensor
    @param      type  The quantized data type.  Must be MLCDataTypeInt8, MLCDataTypeUInt8 or MLCDataTypeInt32
    @param      scale  The scale to apply in quantization
    @param      bias The offset value that maps to float zero
    @param      axis The dimension on which to apply per-channel quantization
    @return     A quantized tensor
*/
- (MLCTensor * _Nullable)tensorByQuantizingToType:(MLCDataType)type
                                            scale:(MLCTensor *)scale
                                             bias:(MLCTensor *)bias
                                             axis:(NSInteger)axis
    NS_SWIFT_NAME(quantized(to:scale:bias:axis:))
    MLCOMPUTE_AVAILABLE_STARTING(macos(12.0), ios(15), tvos(15));

/*! @abstract   Converts a quantized tensor to a 32-bit floating-point tensor
                Returns a de-quantized tensor
    @param      type  The de-quantized data type.  Must be MLCFloat32
    @param      scale  The scale thst was used for the quantized data
    @param      bias The offset value that maps to float zero used for the quantized data
    @return     A quantized tensor
*/
- (MLCTensor * _Nullable)tensorByDequantizingToType:(MLCDataType)type
                                              scale:(MLCTensor *)scale
                                               bias:(MLCTensor *)bias
    NS_SWIFT_NAME(dequantized(to:scale:zeroPoint:))
    MLCOMPUTE_AVAILABLE_STARTING(macos(12.0), ios(15), tvos(15));

/*! @abstract   Converts a quantized tensor to a 32-bit floating-point tensor
                Returns a de-quantized tensor
    @param      type  The de-quantized data type.  Must be MLCFloat32
    @param      scale  The scale thst was used for the quantized data
    @param      bias The offset value that maps to float zero used for the quantized data
    @param      axis The dimension on which to apply per-channel quantization
    @return     A quantized tensor
*/
- (MLCTensor * _Nullable)tensorByDequantizingToType:(MLCDataType)type
                                              scale:(MLCTensor *)scale
                                               bias:(MLCTensor *)bias
                                               axis:(NSInteger)axis
    NS_SWIFT_NAME(dequantized(to:scale:bias:axis:))
    MLCOMPUTE_AVAILABLE_STARTING(macos(12.0), ios(15), tvos(15));

@end

NS_ASSUME_NONNULL_END
