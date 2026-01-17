//
//  MLCTensorDescriptor.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCTensorDescriptor
    @discussion The MLCTensorDescriptor specifies a tensor descriptor.
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCTensorDescriptor : NSObject <NSCopying>

/*! @property   dataType
    @abstract   The tensor data type.  The default is MLCDataTypeFloat32.
 */
@property (readonly, nonatomic) MLCDataType dataType;

/*! @property   dimensionCount
    @abstract   The number of dimensions in the tensor
 */
@property (readonly, nonatomic) NSUInteger dimensionCount;

/*! @property   shape
    @abstract   The size in each dimension
 */
@property (readonly, nonatomic, copy) NSArray<NSNumber *> *shape NS_REFINED_FOR_SWIFT;

/*! @property   stride
    @abstract   The stride in bytes in each dimension
 */
@property (readonly, nonatomic, copy) NSArray<NSNumber *> *stride NS_REFINED_FOR_SWIFT;

/*! @property   tensorAllocationSizeInBytes
    @abstract   The allocation size in bytes for a tensor.
 */
@property (readonly, nonatomic) NSUInteger tensorAllocationSizeInBytes;

/*! @property   sequenceLengths
    @abstract   TODO
 */
@property (readonly, nonatomic, nullable, copy) NSArray<NSNumber *> *sequenceLengths NS_REFINED_FOR_SWIFT;

/*! @property   sortedSequences
    @abstract   Specifies whether the sequences are sorted or not.
 */
@property (readonly, nonatomic) BOOL sortedSequences;

/*! @property   batchSizePerSequenceStep
    @abstract   The batch size for each sequence
    @discussion We populate this only when sequenceLengths is valid. The length of this array should be
                the maximum sequence length in sequenceLengths (i.e sequenceLengths[0]).
 */
@property (readonly, nonatomic, nullable, copy) NSArray<NSNumber *> *batchSizePerSequenceStep NS_REFINED_FOR_SWIFT;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*! @property   maxTensorDimensions
    @abstract   The maximum number of tensor dimensions supported
 */
@property (class, nonatomic, readonly) NSUInteger maxTensorDimensions;

/*! @abstract   Create a MLCTensorDescriptor object
    @param      shape       The tensor shape
    @param      dataType    The tensor data type
    @return     A new MLCTensorDescriptor object or nil if failure.
 */
+ (instancetype _Nullable)descriptorWithShape:(NSArray<NSNumber *> *)shape
                                     dataType:(MLCDataType)dataType
    NS_REFINED_FOR_SWIFT;

/*! @abstract   Create a MLCTensorDescriptor object
    @param      shape              The tensor shape
    @param      sequenceLengths    The sequence lengths in tensor
    @param      sortedSequences    A boolean to indicate whether sequences are sorted
    @param      dataType           The tensor data type
    @return     A new MLCTensorDescriptor object or nil if failure.
    @discussion This method is provided as an easy to use API to create sequence tensors used by recurrent layers.
 */
+ (instancetype _Nullable)descriptorWithShape:(NSArray<NSNumber *> *)shape
                              sequenceLengths:(NSArray<NSNumber *> *)sequenceLengths
                              sortedSequences:(BOOL)sortedSequences
                                     dataType:(MLCDataType)dataType
    NS_REFINED_FOR_SWIFT;

/*! @abstract   Create a MLCTensorDescriptor object
    @param      width              The tensor width
    @param      height             The tensor height
    @param      featureChannels    The number of feature channels
    @param      batchSize          The batch size
    @return     A new MLCTensorDescriptor object or nil if failure.
    @discussion This method is provided as an easy to use API to create [NCHW] tensors used by convolutional layers.
*/
+ (instancetype _Nullable)descriptorWithWidth:(NSUInteger)width
                                       height:(NSUInteger)height
                          featureChannelCount:(NSUInteger)featureChannels
                                    batchSize:(NSUInteger)batchSize;

/*! @abstract   Create a MLCTensorDescriptor object
    @param      width              The tensor width
    @param      height             The tensor height
    @param      featureChannelCount    The number of feature channels
    @param      batchSize          The batch size
    @param      dataType           The tensor data type
    @return     A new MLCTensorDescriptor object or nil if failure.
    @discussion This method is provided as an easy to use API to create [NCHW] tensors used by convolutional layers.
 */
+ (instancetype _Nullable)descriptorWithWidth:(NSUInteger)width
                                       height:(NSUInteger)height
                          featureChannelCount:(NSUInteger)featureChannelCount
                                    batchSize:(NSUInteger)batchSize
                                     dataType:(MLCDataType)dataType;

/*! @abstract   Create a MLCTensorDescriptor object
    @param      width                                      The tensor width
    @param      height                                    The tensor height
    @param      inputFeatureChannelCount     The number of input feature channels
    @param      outputFeatureChannelCount   The number of output feature channels
    @param      dataType                                The tensor data type
    @return     A new MLCTensorDescriptor object or nil if failure.
    @discussion This method is provided as an easy to use API to create a weight tensor.
 */
+ (instancetype _Nullable)convolutionWeightsDescriptorWithWidth:(NSUInteger)width
                                                         height:(NSUInteger)height
                                       inputFeatureChannelCount:(NSUInteger)inputFeatureChannelCount
                                      outputFeatureChannelCount:(NSUInteger)outputFeatureChannelCount
                                                       dataType:(MLCDataType)dataType
    NS_SWIFT_NAME(init(convolutionWeightsWithWidth:height:inputFeatureChannelCount:outputFeatureChannelCount:dataType:));

/*! @abstract   Create a MLCTensorDescriptor object
    @param      inputFeatureChannelCount     The number of input feature channels
    @param      outputFeatureChannelCount   The number of output feature channels
    @param      dataType                                The tensor data type
    @return     A new MLCTensorDescriptor object or nil if failure.
    @discussion This method is provided as an easy to use API to create a weight tensor for a kernel of size 1.
 */
+ (instancetype _Nullable)convolutionWeightsDescriptorWithInputFeatureChannelCount:(NSUInteger)inputFeatureChannelCount
                                                         outputFeatureChannelCount:(NSUInteger)outputFeatureChannelCount
                                                                          dataType:(MLCDataType)dataType
    NS_SWIFT_NAME(init(convolutionWeightsWithInputFeatureChannelCount:outputFeatureChannelCount:dataType:));

/*! @abstract   Create a MLCTensorDescriptor object
    @param      featureChannelCount     The number of input feature channels
    @param      dataType                     The tensor data type
    @return     A new MLCTensorDescriptor object or nil if failure.
    @discussion This method is provided as an easy to use API to create a bias tensor.
 */
+ (instancetype _Nullable)convolutionBiasesDescriptorWithFeatureChannelCount:(NSUInteger)featureChannelCount
                                                                    dataType:(MLCDataType)dataType
    NS_SWIFT_NAME(init(convolutionBiasesWithFeatureChannelCount:dataType:));

@end

NS_ASSUME_NONNULL_END
