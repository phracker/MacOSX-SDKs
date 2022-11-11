//
//  MLCConvolutionDescriptor.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCConvolutionDescriptor
    @discussion The MLCConvolutionDescriptor specifies a convolution descriptor
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCConvolutionDescriptor : NSObject <NSCopying>

/*! @property   convolutionType
    @abstract   The type of convolution.
 */
@property (readonly, nonatomic) MLCConvolutionType convolutionType;

/*! @property   kernelWidth
    @abstract   The convolution kernel size in x.
 */
@property (readonly, nonatomic) NSUInteger kernelWidth NS_REFINED_FOR_SWIFT;

/*! @property   kernelHeight
    @abstract   The convolution kernel size in y.
 */
@property (readonly, nonatomic) NSUInteger kernelHeight NS_REFINED_FOR_SWIFT;

/*! @property   inputFeatureChannelCount
    @abstract   Number of channels in the input tensor
 */
@property (readonly, nonatomic) NSUInteger inputFeatureChannelCount;

/*! @property   outputFeatureChannelCount
    @abstract   Number of channels in the output tensor
 */
@property (readonly, nonatomic) NSUInteger outputFeatureChannelCount;

/*! @property   strideInX
    @abstract   The stride of the kernel in x.
 */
@property (readonly, nonatomic) NSUInteger strideInX NS_REFINED_FOR_SWIFT;

/*! @property   strideInY
    @abstract   The stride of the kernel in y.
 */
@property (readonly, nonatomic) NSUInteger strideInY NS_REFINED_FOR_SWIFT;

/*! @property   dilationRateInX
    @abstract   The dilation rate i.e. stride of elements in the kernel in x.
 */
@property (readonly, nonatomic) NSUInteger dilationRateInX NS_REFINED_FOR_SWIFT;

/*! @property   dilationRateInY
    @abstract   The dilation rate i.e. stride of elements in the kernel in y.
 */
@property (readonly, nonatomic) NSUInteger dilationRateInY NS_REFINED_FOR_SWIFT;

/*! @property   groupCount
    @abstract   Number of blocked connections from input channels to output channels
 */
@property (readonly, nonatomic) NSUInteger groupCount;

/*! @property   paddingPolicy
    @abstract   The padding policy to use.
 */
@property (readonly, nonatomic) MLCPaddingPolicy paddingPolicy NS_REFINED_FOR_SWIFT;

/*! @property   paddingSizeInX
    @abstract   The pooling size in x (left and right) to use if paddingPolicy is MLCPaddingPolicyUsePaddingSize
 */
@property (readonly, nonatomic) NSUInteger paddingSizeInX NS_REFINED_FOR_SWIFT;

/*! @property   paddingSizeInY
    @abstract   The pooling size in y (top and bottom) to use if paddingPolicy is MLCPaddingPolicyUsePaddingSize
 */
@property (readonly, nonatomic) NSUInteger paddingSizeInY NS_REFINED_FOR_SWIFT;

/*! @property   isConvolutionTranspose
    @abstract   A flag to indicate if this is a convolution transpose
 */
@property (readonly, nonatomic) BOOL isConvolutionTranspose;

/*! @property   usesDepthwiseConvolution
    @abstract   A flag to indicate depthwise convolution
 */
@property (readonly, nonatomic) BOOL usesDepthwiseConvolution;

/*! @abstract   Creates a convolution descriptor with the specified convolution type.
    @param      convolutionType              The type of convolution.
    @param      kernelSizes                  The kernel sizes in x and y.
    @param      inputFeatureChannelCount     The number of feature channels in the input tensor.
    @param      outputFeatureChannelCount    The number of feature channels in the output tensor. When the convolution type is \p MLCConvolutionTypeDepthwise , this value must be a multiple of \p inputFeatureChannelCount .
    @param      groupCount                   The number of groups.
    @param      strides                      The kernel strides in x and y.
    @param      dilationRates                The dilation rates in x and y.
    @param      paddingPolicy                The padding policy.
    @param      paddingSizes                 The padding sizes in x and y if padding policy is \p MLCPaddingPolicyUsePaddingSize .
    @return     A new convolution descriptor.
 */
+ (instancetype)descriptorWithType:(MLCConvolutionType)convolutionType
                       kernelSizes:(NSArray<NSNumber *> *)kernelSizes
          inputFeatureChannelCount:(NSUInteger)inputFeatureChannelCount
         outputFeatureChannelCount:(NSUInteger)outputFeatureChannelCount
                        groupCount:(NSUInteger)groupCount
                           strides:(NSArray<NSNumber *> *)strides
                     dilationRates:(NSArray<NSNumber *> *)dilationRates
                     paddingPolicy:(MLCPaddingPolicy)paddingPolicy
                      paddingSizes:(NSArray<NSNumber *> * _Nullable)paddingSizes
    NS_REFINED_FOR_SWIFT;

/*! @abstract   Create a MLCConvolutionDescriptor object
    @param      kernelWidth                         The kernel size in x
    @param      kernelHeight                       The kernel size in x
    @param      inputFeatureChannelCount     The number of feature channels in the input tensor
    @param      outputFeatureChannelCount   The number of feature channels in the output tensor
    @return     A new MLCConvolutionDescriptor object.
 */
+ (instancetype)descriptorWithKernelWidth:(NSUInteger)kernelWidth
                             kernelHeight:(NSUInteger)kernelHeight
                 inputFeatureChannelCount:(NSUInteger)inputFeatureChannelCount
                outputFeatureChannelCount:(NSUInteger)outputFeatureChannelCount
    NS_REFINED_FOR_SWIFT;

/*! @abstract   Create a MLCConvolutionDescriptor object
    @param      kernelSizes                         The kernel sizes in x and y
    @param      inputFeatureChannelCount     The number of feature channels in the input tensor
    @param      outputFeatureChannelCount   The number of feature channels in the output tensor
    @param      strides                                  The kernel strides in x and y
    @param      paddingPolicy                    The padding policy
    @param      paddingSizes                      The padding sizes in x and y if padding policy is MLCPaddingPolicyUsePaddingSIze
    @return     A new MLCConvolutionDescriptor object.
 */
+ (instancetype)descriptorWithKernelSizes:(NSArray<NSNumber *> *)kernelSizes
                 inputFeatureChannelCount:(NSUInteger)inputFeatureChannelCount
                outputFeatureChannelCount:(NSUInteger)outputFeatureChannelCount
                                  strides:(NSArray<NSNumber *> *)strides
                            paddingPolicy:(MLCPaddingPolicy)paddingPolicy
                             paddingSizes:(NSArray<NSNumber *> * _Nullable)paddingSizes
    NS_REFINED_FOR_SWIFT;

/*! @abstract   Create a MLCConvolutionDescriptor object
    @param      kernelSizes                         The kernel sizes in x and y
    @param      inputFeatureChannelCount     The number of feature channels in the input tensor
    @param      outputFeatureChannelCount   The number of feature channels in the output tensor
    @param      groupCount                           Number of groups
    @param      strides                                  The kernel strides in x and y
    @param      dilationRates                    The dilation rates in x and y
    @param      paddingPolicy                    The padding policy
    @param      paddingSizes                      The padding sizes in x and y if padding policy is MLCPaddingPolicyUsePaddingSIze
    @return     A new MLCConvolutionDescriptor object.
 */
+ (instancetype)descriptorWithKernelSizes:(NSArray<NSNumber *> *)kernelSizes
                 inputFeatureChannelCount:(NSUInteger)inputFeatureChannelCount
                outputFeatureChannelCount:(NSUInteger)outputFeatureChannelCount
                               groupCount:(NSUInteger)groupCount
                                  strides:(NSArray<NSNumber *> *)strides
                            dilationRates:(NSArray<NSNumber *> *)dilationRates
                            paddingPolicy:(MLCPaddingPolicy)paddingPolicy
                             paddingSizes:(NSArray<NSNumber *> * _Nullable)paddingSizes
    NS_REFINED_FOR_SWIFT;

/*! @abstract   Create a MLCConvolutionDescriptor object for convolution transpose
    @param      kernelWidth                         The kernel size in x
    @param      kernelHeight                       The kernel size in x
    @param      inputFeatureChannelCount     The number of feature channels in the input tensor
    @param      outputFeatureChannelCount   The number of feature channels in the output tensor
    @return     A new MLCConvolutionDescriptor object.
 */
+ (instancetype)convolutionTransposeDescriptorWithKernelWidth:(NSUInteger)kernelWidth
                                                 kernelHeight:(NSUInteger)kernelHeight
                                     inputFeatureChannelCount:(NSUInteger)inputFeatureChannelCount
                                    outputFeatureChannelCount:(NSUInteger)outputFeatureChannelCount
    NS_SWIFT_NAME(init(transposeWithKernelWidth:kernelHeight:inputFeatureChannelCount:outputFeatureChannelCount:));

/*! @abstract   Create a MLCConvolutionDescriptor object for convolution transpose
    @param      kernelSizes                         The kernel sizes in x and y
    @param      inputFeatureChannelCount     The number of feature channels in the input tensor
    @param      outputFeatureChannelCount   The number of feature channels in the output tensor
    @param      strides                                  The kernel strides in x and y
    @param      paddingPolicy                    The padding policy
    @param      paddingSizes                      The padding sizes in x and y if padding policy is MLCPaddingPolicyUsePaddingSIze
    @return     A new MLCConvolutionDescriptor object.
 */
+ (instancetype)convolutionTransposeDescriptorWithKernelSizes:(NSArray<NSNumber *> *)kernelSizes
                                     inputFeatureChannelCount:(NSUInteger)inputFeatureChannelCount
                                    outputFeatureChannelCount:(NSUInteger)outputFeatureChannelCount
                                                      strides:(NSArray<NSNumber *> *)strides
                                                paddingPolicy:(MLCPaddingPolicy)paddingPolicy
                                                 paddingSizes:(NSArray<NSNumber *> * _Nullable)paddingSizes
    NS_REFINED_FOR_SWIFT
    NS_SWIFT_NAME(init(__transposeWithKernelSizes:inputFeatureChannelCount:outputFeatureChannelCount:strides:paddingPolicy:paddingSizes:));

/*! @abstract   Create a MLCConvolutionDescriptor object for convolution transpose
    @param      kernelSizes                         The kernel sizes in x and y
    @param      inputFeatureChannelCount     The number of feature channels in the input tensor
    @param      outputFeatureChannelCount   The number of feature channels in the output tensor
    @param      groupCount                           Number of groups
    @param      strides                                  The kernel strides in x and y
    @param      dilationRates                    The dilation rates in x and y
    @param      paddingPolicy                    The padding policy
    @param      paddingSizes                      The padding sizes in x and y if padding policy is MLCPaddingPolicyUsePaddingSIze
    @return     A new MLCConvolutionDescriptor object.
 */
+ (instancetype)convolutionTransposeDescriptorWithKernelSizes:(NSArray<NSNumber *> *)kernelSizes
                                     inputFeatureChannelCount:(NSUInteger)inputFeatureChannelCount
                                    outputFeatureChannelCount:(NSUInteger)outputFeatureChannelCount
                                                   groupCount:(NSUInteger)groupCount
                                                      strides:(NSArray<NSNumber *> *)strides
                                                dilationRates:(NSArray<NSNumber *> *)dilationRates
                                                paddingPolicy:(MLCPaddingPolicy)paddingPolicy
                                                 paddingSizes:(NSArray<NSNumber *> * _Nullable)paddingSizes
    NS_REFINED_FOR_SWIFT
    NS_SWIFT_NAME(init(__transposeWithKernelSizes:inputFeatureChannelCount:outputFeatureChannelCount:groupCount:strides:dilationRates:paddingPolicy:paddingSizes:));


/*! @abstract   Create a MLCConvolutionDescriptor object for depthwise convolution
    @param      kernelWidth                         The kernel size in x
    @param      kernelHeight                       The kernel size in x
    @param      inputFeatureChannelCount     The number of feature channels in the input tensor
    @param      channelMultiplier            The channel multiplier
    @return     A new MLCConvolutionDescriptor object.
 */
+ (instancetype)depthwiseConvolutionDescriptorWithKernelWidth:(NSUInteger)kernelWidth
                                                 kernelHeight:(NSUInteger)kernelHeight
                                     inputFeatureChannelCount:(NSUInteger)inputFeatureChannelCount
                                            channelMultiplier:(NSUInteger)channelMultiplier
    NS_SWIFT_NAME(init(depthwiseWithKernelWidth:kernelHeight:inputFeatureChannelCount:channelMultiplier:));

/*! @abstract   Create a MLCConvolutionDescriptor object for depthwise convolution
    @param      kernelSizes                         The kernel sizes in x and y
    @param      inputFeatureChannelCount     The number of feature channels in the input tensor
    @param      channelMultiplier            The channel multiplier
    @param      strides                                  The kernel strides in x and y
    @param      paddingPolicy                    The padding policy
    @param      paddingSizes                      The padding sizes in x and y if padding policy is MLCPaddingPolicyUsePaddingSIze
    @return     A new MLCConvolutionDescriptor object.
 */
+ (instancetype)depthwiseConvolutionDescriptorWithKernelSizes:(NSArray<NSNumber *> *)kernelSizes
                                     inputFeatureChannelCount:(NSUInteger)inputFeatureChannelCount
                                            channelMultiplier:(NSUInteger)channelMultiplier
                                                      strides:(NSArray<NSNumber *> *)strides
                                                paddingPolicy:(MLCPaddingPolicy)paddingPolicy
                                                 paddingSizes:(NSArray<NSNumber *> * _Nullable)paddingSizes
    NS_REFINED_FOR_SWIFT
    NS_SWIFT_NAME(init(__depthwiseWithKernelSizes:inputFeatureChannelCount:channelMultiplier:strides:paddingPolicy:paddingSizes:));

/*! @abstract   Create a MLCConvolutionDescriptor object for depthwise convolution
    @param      kernelSizes                         The kernel sizes in x and y
    @param      inputFeatureChannelCount     The number of feature channels in the input tensor
    @param      channelMultiplier            The channel multiplier
    @param      strides                                  The kernel strides in x and y
    @param      dilationRates                    The dilation rates in x and y
    @param      paddingPolicy                    The padding policy
    @param      paddingSizes                      The padding sizes in x and y if padding policy is MLCPaddingPolicyUsePaddingSIze
    @return     A new MLCConvolutionDescriptor object.
 */
+ (instancetype)depthwiseConvolutionDescriptorWithKernelSizes:(NSArray<NSNumber *> *)kernelSizes
                                     inputFeatureChannelCount:(NSUInteger)inputFeatureChannelCount
                                            channelMultiplier:(NSUInteger)channelMultiplier
                                                      strides:(NSArray<NSNumber *> *)strides
                                                dilationRates:(NSArray<NSNumber *> *)dilationRates
                                                paddingPolicy:(MLCPaddingPolicy)paddingPolicy
                                                 paddingSizes:(NSArray<NSNumber *> * _Nullable)paddingSizes
    NS_REFINED_FOR_SWIFT
    NS_SWIFT_NAME(init(__depthwiseWithKernelSizes:inputFeatureChannelCount:channelMultiplier:strides:dilationRates:paddingPolicy:paddingSizes:));

@end

NS_ASSUME_NONNULL_END
