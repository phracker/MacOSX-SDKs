//
//  MLCPoolingDescriptor.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCPoolingDescriptor
    @discussion The MLCPoolingDescriptor specifies a pooling descriptor.
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.0, 14.0, 14.0)
@interface MLCPoolingDescriptor : NSObject <NSCopying>

/*! @property   poolingType
    @abstract   The pooling operation
 */
@property (readonly, nonatomic) MLCPoolingType poolingType NS_REFINED_FOR_SWIFT;

/*! @property   kernelWidth
    @abstract   The pooling kernel size in x.
 */
@property (readonly, nonatomic) NSUInteger kernelWidth NS_REFINED_FOR_SWIFT;

/*! @property   kernelHeight
    @abstract   The pooling kernel size in y.
 */
@property (readonly, nonatomic) NSUInteger kernelHeight NS_REFINED_FOR_SWIFT;

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

/*! @property   paddingPolicy
    @abstract   The padding policy to use.
 */
@property (readonly, nonatomic) MLCPaddingPolicy paddingPolicy NS_REFINED_FOR_SWIFT;

/*! @property   paddingSizeInX
    @abstract   The padding size in x (left and right) to use if paddingPolicy is MLCPaddingPolicyUsePaddingSize
 */
@property (readonly, nonatomic) NSUInteger paddingSizeInX NS_REFINED_FOR_SWIFT;

/*! @property   paddingSizeInY
    @abstract   The padding size in y (top and bottom) to use if paddingPolicy is MLCPaddingPolicyUsePaddingSize
 */
@property (readonly, nonatomic) NSUInteger paddingSizeInY NS_REFINED_FOR_SWIFT;

/*! @property   countIncludesPadding
    @abstract   Include the zero-padding in the averaging calculation if true.  Used only with average pooling.
 */
@property (readonly, nonatomic) BOOL countIncludesPadding NS_REFINED_FOR_SWIFT;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;


/*! @abstract   Create a MLCPoolingDescriptor object
    @param      poolingType    The pooling function
    @param      kernelSize      The kernel sizes in x and y
    @param      stride               The kernel strides in x and y
    @return     A new MLCPoolingDescriptor object.
 */
+ (instancetype)poolingDescriptorWithType:(MLCPoolingType)poolingType
                               kernelSize:(NSUInteger)kernelSize
                                   stride:(NSUInteger)stride
    NS_REFINED_FOR_SWIFT;

/*! @abstract   Create a MLCPoolingDescriptor object for a max pooling function
    @param      kernelSizes        The kernel sizes in x and y
    @param      strides                 The kernel strides in x and y
    @param      paddingPolicy    The padding policy
    @param      paddingSizes      The padding sizes in x and y if padding policy is MLCPaddingPolicyUsePaddingSIze
    @return     A new MLCPoolingDescriptor object.
 */
+ (instancetype)maxPoolingDescriptorWithKernelSizes:(NSArray<NSNumber *> *)kernelSizes
                                            strides:(NSArray<NSNumber *> *)strides
                                      paddingPolicy:(MLCPaddingPolicy)paddingPolicy
                                       paddingSizes:(NSArray<NSNumber *> * _Nullable)paddingSizes
    NS_REFINED_FOR_SWIFT
    NS_SWIFT_NAME(init(__maxPoolingWithKernelSizes:strides:paddingPolicy:paddingSizes:));

/*! @abstract   Create a MLCPoolingDescriptor object for a max pooling function
    @param      kernelSizes        The kernel sizes in x and y
    @param      strides                 The kernel strides in x and y
    @param      dilationRates    The kernel dilation rates in x and y
    @param      paddingPolicy    The padding policy
    @param      paddingSizes      The padding sizes in x and y if padding policy is MLCPaddingPolicyUsePaddingSIze
    @return     A new MLCPoolingDescriptor object.
 */
+ (instancetype)maxPoolingDescriptorWithKernelSizes:(NSArray<NSNumber *> *)kernelSizes
                                            strides:(NSArray<NSNumber *> *)strides
                                      dilationRates:(NSArray<NSNumber *> *)dilationRates
                                      paddingPolicy:(MLCPaddingPolicy)paddingPolicy
                                       paddingSizes:(NSArray<NSNumber *> * _Nullable)paddingSizes
    NS_REFINED_FOR_SWIFT
    NS_SWIFT_NAME(init(__maxPoolingWithKernelSizes:strides:dilationRates:paddingPolicy:paddingSizes:));

/*! @abstract   Create a MLCPoolingDescriptor object for an average pooling function
    @param      kernelSizes                      The kernel sizes in x and y
    @param      strides                               The kernel strides in x and y
    @param      paddingPolicy                  The padding policy
    @param      paddingSizes                    The padding sizes in x and y if padding policy is MLCPaddingPolicyUsePaddingSIze
    @param      countIncludesPadding   Whether to include zero padding in the averaging calculation
    @return     A new MLCPoolingDescriptor object.
 */
+ (instancetype)averagePoolingDescriptorWithKernelSizes:(NSArray<NSNumber *> *)kernelSizes
                                                strides:(NSArray<NSNumber *> *)strides
                                          paddingPolicy:(MLCPaddingPolicy)paddingPolicy
                                           paddingSizes:(NSArray<NSNumber *> * _Nullable)paddingSizes
                                   countIncludesPadding:(BOOL)countIncludesPadding
    NS_REFINED_FOR_SWIFT
    NS_SWIFT_NAME(init(__averagePoolingWithKernelSizes:strides:paddingPolicy:paddingSizes:countIncludesPadding:));

/*! @abstract   Create a MLCPoolingDescriptor object for an average pooling function
    @param      kernelSizes                      The kernel sizes in x and y
    @param      strides                               The kernel strides in x and y
    @param      dilationRates                  The kernel dilation rates in x and y
    @param      paddingPolicy                  The padding policy
    @param      paddingSizes                    The padding sizes in x and y if padding policy is MLCPaddingPolicyUsePaddingSIze
    @param      countIncludesPadding   Whether to include zero padding in the averaging calculation
    @return     A new MLCPoolingDescriptor object.
 */
+ (instancetype)averagePoolingDescriptorWithKernelSizes:(NSArray<NSNumber *> *)kernelSizes
                                                strides:(NSArray<NSNumber *> *)strides
                                          dilationRates:(NSArray<NSNumber *> *)dilationRates
                                          paddingPolicy:(MLCPaddingPolicy)paddingPolicy
                                           paddingSizes:(NSArray<NSNumber *> * _Nullable)paddingSizes
                                   countIncludesPadding:(BOOL)countIncludesPadding
    NS_REFINED_FOR_SWIFT
    NS_SWIFT_NAME(init(__averagePoolingWithKernelSizes:strides:dilationRates:paddingPolicy:paddingSizes:countIncludesPadding:));

/*! @abstract   Create a MLCPoolingDescriptor object for a L2 norm pooling function
    @param      kernelSizes        The kernel sizes in x and y
    @param      strides                 The kernel strides in x and y
    @param      paddingPolicy    The padding policy
    @param      paddingSizes      The padding sizes in x and y if padding policy is MLCPaddingPolicyUsePaddingSIze
    @return     A new MLCPoolingDescriptor object.
 */
+ (instancetype)l2NormPoolingDescriptorWithKernelSizes:(NSArray<NSNumber *> *)kernelSizes
                                               strides:(NSArray<NSNumber *> *)strides
                                         paddingPolicy:(MLCPaddingPolicy)paddingPolicy
                                          paddingSizes:(NSArray<NSNumber *> * _Nullable)paddingSizes
    NS_REFINED_FOR_SWIFT
    NS_SWIFT_NAME(init(__l2NormPoolingWithKernelSizes:strides:paddingPolicy:paddingSizes:));

/*! @abstract   Create a MLCPoolingDescriptor object for a L2 norm pooling function
    @param      kernelSizes        The kernel sizes in x and y
    @param      strides                 The kernel strides in x and y
    @param      dilationRates    The kernel dilation rates in x and y
    @param      paddingPolicy    The padding policy
    @param      paddingSizes      The padding sizes in x and y if padding policy is MLCPaddingPolicyUsePaddingSIze
    @return     A new MLCPoolingDescriptor object.
 */
+ (instancetype)l2NormPoolingDescriptorWithKernelSizes:(NSArray<NSNumber *> *)kernelSizes
                                               strides:(NSArray<NSNumber *> *)strides
                                         dilationRates:(NSArray<NSNumber *> *)dilationRates
                                         paddingPolicy:(MLCPaddingPolicy)paddingPolicy
                                          paddingSizes:(NSArray<NSNumber *> * _Nullable)paddingSizes
    NS_REFINED_FOR_SWIFT
    NS_SWIFT_NAME(init(__l2NormPoolingWithKernelSizes:strides:dilationRates:paddingPolicy:paddingSizes:));

@end

NS_ASSUME_NONNULL_END
