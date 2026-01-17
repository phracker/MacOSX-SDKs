//
//  MPSCNNConvolution.h
//  MPS
//
//  Created by Ian Ollmann on 8/21/16.
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef MPSCNNConvolution_h
#define MPSCNNConvolution_h

#include <MPSNeuralNetwork/MPSCNNKernel.h>
#include <MPSNeuralNetwork/MPSCNNNormalization.h>
#include <MPSNeuralNetwork/MPSCNNNeuronType.h>
#include <MPSCore/MPSState.h>
#include <simd/simd.h>

#ifdef __cplusplus
extern "C" {
#endif


#pragma mark -
#pragma mark MPSCNNNeuron functions


/*!
 *  @class      MPSCNNNeuron
 *  @dependency This depends on Metal.framework
 *  @discussion This filter applies a neuron activation function.
 *              You must use one of the sub-classes of MPSCNNNeuron
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface  MPSCNNNeuron : MPSCNNKernel

/*! @abstract NSSecureCoding compatability
 *  @discussion While the standard NSSecureCoding/NSCoding method
 *              -initWithCoder: should work, since the file can't
 *              know which device your data is allocated on, we
 *              have to guess and may guess incorrectly.  To avoid
 *              that problem, use initWithCoder:device instead.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSKernel
 *  @param      device      The MTLDevice on which to make the MPSKernel
 *  @return     A new MPSKernel object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device;

@end    /* MPSCNNNeuron */


/*!
 *  @class      MPSCNNNeuronLinear
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the linear neuron filter. For each pixel, applies the following function: f(x) = a * x + b
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface  MPSCNNNeuronLinear : MPSCNNNeuron

@property (readonly, nonatomic) float a;
@property (readonly, nonatomic) float b;

/*!
 *  @abstract  Initialize the linear neuron filter
 *  @param     device   The device the filter will run on
 *  @param     a        Filter property "a". See class discussion.
 *  @param     b        Filter property "b". See class discussion.
 *  @return    A valid MPSCNNNeuronLinear object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (float) a
                                     b: (float) b NS_DESIGNATED_INITIALIZER;

/*
 * You must use initWithDevice:a:b instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronLinear */


/*!
 *  @class MPSCNNNeuronReLU
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the ReLU neuron filter.
 *              For each pixel, applies the following function: f(x) = x, if x >= 0
 *                                                                   = a * x if x < 0
 *              This is called Leaky ReLU in literature. Some literature defines
 *              classical ReLU as max(0, x). If you want this behavior, simply pass a = 0
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface  MPSCNNNeuronReLU : MPSCNNNeuron

@property (readonly, nonatomic) float a;

/*!
 *  @abstract  Initialize the ReLU neuron filter
 *  @param     device           The device the filter will run on
 *  @param     a                Filter property "a". See class discussion.
 *  @return    A valid MPSCNNNeuronReLU object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (float) a NS_DESIGNATED_INITIALIZER;

/*
 * Use initWithDevice:a: instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronReLU */

/*!
 *  @class MPSCNNNeuronPReLU
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the parametric ReLU neuron filter.
 *              For each pixel, applies the following function: f(x_i) = x_i, if x_i >= 0
 *                                                                     = a_i * x_i if x_i < 0
 *              i in [0...channels-1]
 *              i.e. parameters a_i are learned and applied to each channel separately. Compare
 *              this to ReLu where parameter a is shared acorss all channels.
 *              See https://arxiv.org/pdf/1502.01852.pdf for details.
*/
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSCNNNeuronPReLU : MPSCNNNeuron

/*!
 *  @abstract  Initialize the PReLU neuron filter
 *  @param     device           The device the filter will run on
 *  @param     a                Array of floats containing per channel value of PReLu parameter
 *  @param     length           Number of flaot values in array a.
 *                              This usually corresponds to number of output channels in convolution layer
 *  @return    A valid MPSCNNNeuronPReLU object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (const float* _Nonnull) a
                                length: (NSUInteger) length NS_DESIGNATED_INITIALIZER;

/*
 * Use initWithDevice:a: instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronPReLU */
    
    
/*!
 *  @class MPSCNNNeuronSigmoid
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the sigmoid neuron filter.  For each pixel, applies the following function: f(x) = 1 / (1 + e^-x)
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface  MPSCNNNeuronSigmoid : MPSCNNNeuron

/*!
 *  @abstract  Initialize a neuron filter
 *  @param      device          The device the filter will run on
 *  @return     A valid MPSCNNNeuronSigmoid object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNNeuronSigmoid */
    
    
/*!
 *  @class MPSCNNNeuronHardSigmoid
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the hard sigmoid neuron filter.  For each pixel, applies the following function: f(x) = clamp((a * x) + b, 0, 1)
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSCNNNeuronHardSigmoid : MPSCNNNeuron

@property (readonly, nonatomic) float a;
@property (readonly, nonatomic) float b;

/*!
 *  @abstract  Initialize a neuron filter
 *  @param     device           The device the filter will run on
 *  @param     a                Filter property "a". See class discussion.
 *  @param     b                Filter property "b". See class discussion.
 *  @return    A valid MPSCNNNeuronHardSigmoid object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (float) a
                                     b: (float) b NS_DESIGNATED_INITIALIZER;
/*
 * Use initWithDevice:a:b: instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronHardSigmoid */


/*!
 *  @class MPSCNNNeuronTanH
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the hyperbolic tangent neuron filter.
 *              For each pixel, applies the following function: f(x) = a * tanh(b * x)
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface  MPSCNNNeuronTanH : MPSCNNNeuron

@property (readonly, nonatomic) float a;
@property (readonly, nonatomic) float b;

/*!
 *  @abstract  Initialize the hyperbolic tangent neuron filter
 *  @param     device           The device the filter will run on
 *  @param     a                Filter property "a". See class discussion.
 *  @param     b                Filter property "b". See class discussion.
 *  @return    A valid MPSCNNNeuronTanH object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (float) a
                                     b: (float) b NS_DESIGNATED_INITIALIZER;
/*
 * Use initWithDevice:a:b: instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronTanH */

/*!
 *  @class MPSCNNNeuronAbsolute
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the absolute neuron filter.  For each pixel, applies the following function: f(x) = | x |
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface  MPSCNNNeuronAbsolute : MPSCNNNeuron

/*!
 *  @abstract  Initialize a neuron filter
 *  @param      device          The device the filter will run on
 *  @return     A valid MPSCNNNeuronAbsolute object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNNeuronAbsolute */


/*!
*  @class MPSCNNNeuronSoftPlus
*  @dependency This depends on Metal.framework
*  @discussion Specifies the parametric softplus neuron filter.
*              For each pixel, applies the following function: f(x) = a * log(1 + e^(b * x))
*/
MPS_CLASS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSCNNNeuronSoftPlus : MPSCNNNeuron

@property (readonly, nonatomic) float a;
@property (readonly, nonatomic) float b;

/*!
 *  @abstract   Initialize a parametric softplus neuron filter
 *  @param      device          The device the filter will run on
 *  @param      a               Filter property "a". See class discussion.
 *  @param      b               Filter property "b". See class discussion.
 *  @return     A valid MPSCNNNeuronSoftPlus object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (float) a
                                     b: (float) b NS_DESIGNATED_INITIALIZER;
/*
 * Use initWithDevice:a:b: instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronSoftPlus */


/*!
*  @class MPSCNNNeuronSoftSign
*  @dependency This depends on Metal.framework
*  @discussion Specifies the softsign neuron filter.
*              For each pixel, applies the following function: f(x) = x / (1 + abs(x))
*/
MPS_CLASS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSCNNNeuronSoftSign : MPSCNNNeuron

/*!
 *  @abstract   Initialize a softsign neuron filter
 *  @param      device          The device the filter will run on
 *  @return     A valid MPSCNNNeuronSoftSign object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNNeuronSoftSign */


/*!
*  @class MPSCNNNeuronELU
*  @dependency This depends on Metal.framework
*  @discussion Specifies the parametric ELU neuron filter.
*              For each pixel, applies the following function: f(x) = [ a * (exp(x) - 1), x <  0
*                                                                     [ x               , x >= 0
*/
MPS_CLASS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSCNNNeuronELU : MPSCNNNeuron

@property (readonly, nonatomic) float a;

/*!
 *  @abstract   Initialize a parametric ELU neuron filter
 *  @param      device          The device the filter will run on
 *  @param      a               Filter property "a". See class discussion.
 *  @return     A valid MPSCNNNeuronELU object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                             a: (float) a NS_DESIGNATED_INITIALIZER;
/*
 * Use initWithDevice:a: instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronELU */

#pragma mark -
#pragma mark MPSCNNConvolutionDescriptor

    
@class MPSNNFilterNode;

/*!
 *  @class      MPSCNNConvolutionDescriptor
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSCNNConvolutionDescriptor specifies a convolution descriptor
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface MPSCNNConvolutionDescriptor : NSObject <NSSecureCoding, NSCopying>

/*! @property   kernelWidth
 *  @abstract   The width of the filter window.  The default value is 3.
 *              Any positive non-zero value is valid, including even values.
 *              The position of the left edge of the filter window is given
 *              by offset.x - (kernelWidth>>1)
 */
@property(readwrite, nonatomic) NSUInteger       kernelWidth;

/*! @property   kernelHeight
 *  @abstract   The height of the filter window.  The default value is 3.
 *              Any positive non-zero value is valid, including even values.
 *              The position of the top edge of the filter window is given
 *              by offset.y - (kernelHeight>>1)
 */
@property(readwrite, nonatomic) NSUInteger       kernelHeight;

/*! @property   inputFeatureChannels
 *  @abstract   The number of feature channels per pixel in the input image.
 */
@property(readwrite, nonatomic) NSUInteger       inputFeatureChannels;

/*! @property   outputFeatureChannels
 *  @abstract   The number of feature channels per pixel in the output image.
 */
@property(readwrite, nonatomic) NSUInteger       outputFeatureChannels;

/*! @property   strideInPixelsX
 *  @abstract   The output stride (downsampling factor) in the x dimension. The default value is 1.
 */
@property(readwrite, nonatomic) NSUInteger      strideInPixelsX;

/*! @property   strideInPixelsY
 *  @abstract   The output stride (downsampling factor) in the y dimension. The default value is 1.
 */
@property(readwrite, nonatomic) NSUInteger      strideInPixelsY;

/*! @property   groups
 *  @abstract   Number of groups input and output channels are divided into. The default value is 1.
 *              Groups lets you reduce the parameterization. If groups is set to n, input is divided into n
 *              groups with inputFeatureChannels/n channels in each group. Similarly output is divided into
 *              n groups with outputFeatureChannels/n channels in each group. ith group in input is only
 *              connected to ith group in output so number of weights (parameters) needed is reduced by factor
 *              of n. Both inputFeatureChannels and outputFeatureChannels must be divisible by n and number of
 *              channels in each group must be multiple of 4.
 */
@property(readwrite, nonatomic) NSUInteger      groups;

/*! @property      dilationRateX
 *  @discussion    dilationRateX property can be used to implement dilated convolution as described in
 *                          https://arxiv.org/pdf/1511.07122v3.pdf
 *                 to aggregate global information in dense prediction problems.
 *                 Default value is 1. When set to value > 1, original kernel width, kW is dilated to
 *
 *                       kW_Dilated = (kW-1)*dilationRateX + 1
 *
 *                 by inserting d-1 zeros between consecutive entries in each row of the original kernel. 
 *                 The kernel is centered based on kW_Dilated.
 */
@property(readwrite, nonatomic) NSUInteger      dilationRateX;

/*! @property      dilationRateY
 *  @discussion    dilationRateY property can be used to implement dilated convolution as described in
 *                          https://arxiv.org/pdf/1511.07122v3.pdf
 *                 to aggregate global information in dense prediction problems.
 *                 Default value is 1. When set to value > 1, original kernel height, kH is dilated to
 *
 *                       kH_Dilated = (kH-1)*dilationRateY + 1
 *
 *                 by inserting d-1 rows of zeros between consecutive row of the original kernel.
 *                 The kernel is centered based on kH_Dilated.
 */
@property(readwrite, nonatomic) NSUInteger      dilationRateY;

/*! @property   neuron
 *  @abstract   MPSCNNNeuron filter to be applied as part of convolution. This is applied after BatchNormalization in the end.
 *              Default is nil.
 *              This is deprecated. You dont need to create MPSCNNNeuron object to fuse with convolution. Use neuron properties
 *              in this descriptor.
 */
@property(readwrite, nonatomic, retain) const MPSCNNNeuron * __nullable  neuron
        MPS_AVAILABLE_STARTING_BUT_DEPRECATED(  "A MPSCNNNeuron:MPSKernel is much too heavy an object to\n"
                                                "represent what is a type code and two floats. It is deprecated.\n"
                                                "Please use the MPSCNNConvolutionNeuronFusedDescriptor  instead.",
                                                ios(10.0, 11.0), tvos(10.0, 11.0));

/*! @abstract   The type of neuron to append to the convolution
 *  @discussion Please see class description for a full list. Default is MPSCNNNeuronTypeNone. */
@property   (readwrite, nonatomic) MPSCNNNeuronType     neuronType;

/*! @abstract   Parameter "a" for the neuron.  Default: 1.0f
 *  @discussion Please see class description for interpretation of a. */
@property   (readwrite, nonatomic) float                neuronParameterA;

/*! @abstract   Parameter "b" for the neuron.  Default: 1.0f
 *  @discussion Please see class description for interpretation of b. */
@property   (readwrite, nonatomic) float                neuronParameterB;

/*! @abstract <NSSecureCoding> support */
@property (class, readonly) BOOL supportsSecureCoding
            MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));
/*! @abstract <NSSecureCoding> support */
- (void)encodeWithCoder:(NSCoder *__nonnull)aCoder
            MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));
/*! @abstract <NSSecureCoding> support */
- (nullable instancetype)initWithCoder:(NSCoder *__nonnull)aDecoder
            MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0)) NS_DESIGNATED_INITIALIZER;

/*!
 *  @abstract   This method is deprecated. Please use neuronType, neuronParameterA and neuronParameterB properites to fuse
 *              neuron with convolution.
 *  @param      kernelWidth             The width of the filter window.  Must be > 0. Large values will take a long time.
 *  @param      kernelHeight            The height of the filter window.   Must be > 0. Large values will take a long time.
 *  @param      inputFeatureChannels    The number of feature channels in the input image. Must be >= 1.
 *  @param      outputFeatureChannels   The number of feature channels in the output image. Must be >= 1.
 *  @param      neuronFilter            An optional neuron filter that can be applied to the output of convolution.
 *  @return     A valid MPSCNNConvolutionDescriptor object or nil, if failure.
 */
+(nonnull instancetype) cnnConvolutionDescriptorWithKernelWidth: (NSUInteger) kernelWidth
                                                   kernelHeight: (NSUInteger) kernelHeight
                                           inputFeatureChannels: (NSUInteger) inputFeatureChannels
                                          outputFeatureChannels: (NSUInteger) outputFeatureChannels
                                                   neuronFilter: (const MPSCNNNeuron * __nullable) neuronFilter
    MPS_AVAILABLE_STARTING_BUT_DEPRECATED( "Please use neuronType, neuronParameterA and neuronParameterB properties instead.",
                                            ios(10.0, 11.0), tvos(10.0, 11.0));

/*!
 *  @abstract   Creates a convolution descriptor.
 *  @param      kernelWidth             The width of the filter window.  Must be > 0. Large values will take a long time.
 *  @param      kernelHeight            The height of the filter window.   Must be > 0. Large values will take a long time.
 *  @param      inputFeatureChannels    The number of feature channels in the input image. Must be >= 1.
 *  @param      outputFeatureChannels   The number of feature channels in the output image. Must be >= 1.
 *  @return     A valid MPSCNNConvolutionDescriptor object or nil, if failure.
 */
+(nonnull instancetype) cnnConvolutionDescriptorWithKernelWidth: (NSUInteger) kernelWidth
                                                   kernelHeight: (NSUInteger) kernelHeight
                                           inputFeatureChannels: (NSUInteger) inputFeatureChannels
                                          outputFeatureChannels: (NSUInteger) outputFeatureChannels
    MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0) );



/*!
 *  @abstract   Adds batch normalization for inference, it copies all the float arrays provided, expecting 
 *              outputFeatureChannels elements in each.
 *
 *  @discussion This method will be used to pass in batch normalization parameters to the convolution during the
 *              init call. For inference we modify weights and bias going in convolution or Fully Connected layer to combine
 *              and optimize the layers.
 *
 *
 *              w: weights for a corresponding output feature channel
 *              b: bias for a corresponding output feature channel
 *              W: batch normalized weights for a corresponding output feature channel
 *              B: batch normalized bias for a corresponding output feature channel
 *
 *
 *              I = gamma / sqrt(variance + epsilon), J = beta - ( I * mean )
 *
 *              W = w * I
 *              B = b * I + J
 *
 *              Every convolution has (OutputFeatureChannel * kernelWidth * kernelHeight * InputFeatureChannel) weights
 *
 *              I, J are calculated, for every output feature channel separately to get the corresponding weights and bias
 *              Thus, I, J are calculated and then used for every (kernelWidth * kernelHeight * InputFeatureChannel)
 *              weights, and this is done OutputFeatureChannel number of times for each output channel.
 *
 *              thus, internally, batch normalized weights are computed as:
 *
 *              W[no][i][j][ni] = w[no][i][j][ni] * I[no]
 *
 *              no: index into outputFeatureChannel
 *              i : index into kernel Height
 *              j : index into kernel Width
 *              ni: index into inputFeatureChannel
 *
 *              One usually doesn't see a bias term and batch normalization together as batch normalization potentially cancels
 *              out the bias term after training, but in MPS if the user provides it, batch normalization will use the above 
 *              formula to incorporate it, if user does not have bias terms then put a float array of zeroes in the convolution
 *              init for bias terms of each output feature channel.
 *
 *
 *              this comes from:
 *              https://arxiv.org/pdf/1502.03167v3.pdf
 *
 *
 *  @param      mean                        Pointer to an array of floats of mean for each output feature channel
 *  @param      variance                    Pointer to an array of floats of variance for each output feature channel
 *  @param      gamma                       Pointer to an array of floats of gamma for each output feature channel
 *  @param      beta                        Pointer to an array of floats of beta for each output feature channel
 *  @param      epsilon                     A small float value used to have numerical stability in the code
 */
-(void) setBatchNormalizationParametersForInferenceWithMean: (const float * __nonnull) mean
                                                   variance: (const float * __nonnull) variance
                                                      gamma: (const float * __nullable) gamma
                                                       beta: (const float * __nullable) beta
                                                    epsilon: (const float) epsilon;

@end    /* MPSCNNConvolutionDescriptor */

/*! @abstract         MPSCNNSubPixelConvolutionDescriptor can be used to create MPSCNNConvolution object that does sub pixel upsamling
 *                    and reshaping opeartion as described in
 *                        http://www.cv-foundation.org/openaccess/content_cvpr_2016/papers/Shi_Real-Time_Single_Image_CVPR_2016_paper.pdf
 *  @discussion
 *                   Conceptually MPSCNNConvolution with subPixelScaleFactor > 1 can be thought of as filter performing regular CNN convolution producing N output feature channels at each pixel of
 *                   an intermediate MPSImage followed by a kernel that rearranges/reshapes these N channels at each pixel of intermediate MPSImage into a pixel block of
 *                   size subPixelScaleFactor x subPixelScaleFactor with N/(subPixelScaleFactor * subPixelScaleFactor) featureChannels at each pixel of this pixel block. Thus each pixel in intermedaite
 *                   MPSImage with N channels map to subPixelScaleFactor x subPixelScaleFactor pixel block in final destination MPSImage with N/(subPixelScaleFactor * subPixelScaleFactor) featureChannels.
 *                   MPSCNNConvolution with subPixelScaleFactor > 1 fuses the convolution and reshaping operation into single compute kernel thus not only saving DRAM roundtrip but also memory
 *                   needed for intermediate MPSImage had these operation done separately.
 *                   Let N be the value of outputFeatureChannels property and let r = subPixelScaleFactor.
 *                   Conceptually Convolution will produce intermedaite image Io of dimensions (treated as 3D tensor) width x height x N where
 *                              width = (clipRect.size.width + r - 1) / r
 *                              height = (clipRect.size.height + r -1) / r
 *                   Reshaping happens as follows
 *                   @code
 *                   Destination[clipRect.origin.x+x][clipRect.origin.y+y][c] = Io[ floor(x/r) ][ floor(y/r) ][ (N/r^2) * ( r * mod(y,r) + mod(x,r) ) + c ]
 *                   where x in [0,clipRect.size.width-1], y in [0,clipRect.size.height-1], c in [0,N/r^2 - 1]
 *                   @endcode
 *
 *                   The following conditions must be met:
 *                   1) N (outputFeatureChannels) must be multiple of r^2 (subPixelScaleFactor * subPixelScaleFactor).
 *                   2) The destination MPSImage to encode call must have at least N/r^2 + destinationFeatureChannelOffset channels.
 *                   3) Number of feature channels in reshaped output image (N/r^2) can be any value when groups = 1 but must be multiple of 4 when groups > 1.
*/
MPS_CLASS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0))
@interface MPSCNNSubPixelConvolutionDescriptor : MPSCNNConvolutionDescriptor

/*! @property      subPixelScaleFactor
 *  @discussion    Upsampling scale factor. Each pixel in input is upsampled into a subPixelScaleFactor x subPixelScaleFactor pixel block by rearranging
 *                 the outputFeatureChannels as described above. Default value is 1.
 */
@property(readwrite, nonatomic) NSUInteger      subPixelScaleFactor;

@end
    
/*! @abstract         MPSCNNDepthWiseConvolutionDescriptor can be used to create MPSCNNConvolution object that does depthwise convolution
 *  @discussion
 *                    Depthwise convolution applies different filter to each input feature channel i.e. no cross channel mixing.
 *                    Number of outputFeatureChannels can be greater than number of inputFeatureChannels, in which case convolution
 *                    expects channelMultipler = outputFeactureChannels/inputFeatureChannels number of filters for each input channel.
 *                    This means channelMultipler filters are applied to each input feature channel producing channelMultipler output feature channels.
 *                    All channelMultipler output feature channels produced by single input feature channel are stored togather in output image i.e.
 *                              output[x,y,k*channelMultiplier + q] = input[x,y,k] * filter[k,q]
 *                    where * here denotes convolution.
 *                    group must be 1.
 *                    Weights array returned by MPSCNNConvolutionDataProvier is interpreted as
 *                              Weights [inputFeatureChannels] [channelMultiplier] [kW] [kH]
 *
 *                    Currently only channel multipler of 1 is supported i.e. inputFeatureChannels == outputFeatureChannels
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0))
@interface MPSCNNDepthWiseConvolutionDescriptor : MPSCNNConvolutionDescriptor

/*! @property      channelMultiplier
 *  @discussion    Ratio of outputFeactureChannel to inputFeatureChannels for depthwise convolution i.e. how many output feature channels are
 *                 produced by each input channel.
 */
@property(readonly, nonatomic) NSUInteger      channelMultiplier;

@end
    
/*! @protocol   MPSCNNConvolutionDataSource
 *  @abstract   Provides convolution filter weights and bias terms
 *  @discussion The MPSCNNConvolutionDataSource protocol declares the methods that an
 *              instance of MPSCNNConvolution uses to obtain the weights and bias terms
 *              for the CNN convolution filter.
 *              
 *              Why? CNN weights can be large. If multiple copies of all the weights
 *              for all the convolutions are available unpacked in memory at the same
 *              time, some devices can run out of memory. The MPSCNNConvolutionDataSource
 *              is used to encapsulate a reference to the weights such as a file path,
 *              so that unpacking can be deferred until needed, then purged soon thereafter
 *              so that not all of the data must be in memory at the same time.
 *              MPS does not provide a class that conforms to this protocol. It is up to
 *              the developer to craft his own to encapsulate his data.
 *              
 *              Batch normalization and the neuron activation function are handled using the
 *              -descriptor method.
 *
 *              Thread safety: The MPSCNNConvolutionDataSource object can be called by
 *              threads that are not the main thread. If you will be creating multiple 
 *              MPSNNGraph objects concurrently in multiple threads and these share 
 *              MPSCNNConvolutionDataSources, then the data source objects may be called 
 *              reentrantly.
 */
@protocol MPSCNNConvolutionDataSource <NSObject>

@required
    
    /*! @abstract   Alerts MPS what sort of weights are provided by the object
     *  @discussion For MPSCNNConvolution, MPSDataTypeUInt8, MPSDataTypeFloat16
     *              and MPSDataTypeFloat32 are supported for normal convolutions
     *              using MPSCNNConvolution. MPSCNNBinaryConvolution assumes weights to be
     *              of type MPSDataTypeUInt32 always.
     */
    -(MPSDataType)  dataType;
    
    /*! @abstract   Return a MPSCNNConvolutionDescriptor as needed 
     *  @discussion MPS will not modify this object other than perhaps to retain it.
     *              User should set the appropriate neuron in the creation of convolution descriptor
     *              and for batch normalization use:
     *  @code       
     *              -setBatchNormalizationParametersForInferenceWithMean:variance:gamma:beta:epsilon:
     *  @endcode
     *
     *  @return     A MPSCNNConvolutionDescriptor that describes the kernel housed by this object.
     */
    -(MPSCNNConvolutionDescriptor * __nonnull) descriptor;
    
    /*! @abstract   Returns a pointer to the weights for the convolution.
     *  @discussion The type of each entry in array is given by -dataType. The number
     *              of entries is equal to:
     *              @code
     *                  inputFeatureChannels * outputFeatureChannels * kernelHeight * kernelWidth
     *              @endcode
     *              The layout of filter weight is as a 4D tensor (array)
     *              weight[ outputChannels ][ kernelHeight ][ kernelWidth ][ inputChannels / groups ]
     *
     *              Frequently, this function is a single line of code to return
     *              a pointer to memory allocated in -load.
     *
     *              Batch normalization parameters are set using -descriptor.
     *
     *              Note: For binary-convolutions the layout of the weights are:
     *                  weight[ outputChannels ][ kernelHeight ][ kernelWidth ][ floor((inputChannels/groups)+31) / 32 ]
     *              with each 32 sub input feature channel index specified in machine byte order, so that for example
     *              the 13th feature channel bit can be extracted using bitmask = (1U << 13).
     */
    -(void * __nonnull) weights;
 
    /*! @abstract   Returns a pointer to the bias terms for the convolution.
     *  @discussion Each entry in the array is a single precision IEEE-754 float
     *              and represents one bias. The number of entries is equal
     *              to outputFeatureChannels.
     *
     *              Frequently, this function is a single line of code to return
     *              a pointer to memory allocated in -load. It may also just
     *              return nil.
     *
     *              Note: bias terms are always float, even when the weights are not.
     */
    -(float * __nullable) biasTerms;

    
    /*! @abstract   Alerts the data source that the data will be needed soon
     *  @discussion Each load alert will be balanced by a purge later, when MPS
     *              no longer needs the data from this object.
     *              Load will always be called atleast once after initial construction
     *              or each purge of the object before anything else is called.
     *  @return     Returns YES on success.  If NO is returned, expect MPS
     *              object construction to fail.
     */
    -(BOOL) load;
    
    /*! @abstract   Alerts the data source that the data is no longer needed
     *  @discussion Each load alert will be balanced by a purge later, when MPS
     *              no longer needs the data from this object.
     */
    -(void) purge;
    
    
    /*! @abstract   A label that is transferred to the convolution at init time
     *  @discussion Overridden by a MPSCNNConvolutionNode.label if it is non-nil.
     */
    -(NSString*__nullable) label;
   
    /* MPSDataTypeUInt8 weight containers must implement one and only one of the following optional methods: */
@optional
    /*! @abstract       A list of per-output channel limits that describe the 8-bit range
     *  @discussion     This returns a pointer to an array of vector_float2[outputChannelCount] 
     *                  values. The first value in the vector is the minimum value in the range.
     *                  The second value in the vector is the maximum value in the range. 
     *
     *                  The 8-bit weight value is interpreted as:
     *                  @code
     *                      float unorm8_weight = uint8_weight / 255.0f;    // unorm8_weight has range [0,1.0]
     *                      float max = range[outputChannel].y;
     *                      float min = range[outputChannel].x;
     *                      float weight = unorm8_weight * (max - min) + min
     *                  @endcode
     */
    -(vector_float2 * __nonnull) rangesForUInt8Kernel;
    
    
    /*! @abstract       A pointer to a 256 entry lookup table containing the values to use for the weight range [0,255]
     */
    -(float * __nonnull) lookupTableForUInt8Kernel;
    
@end
    
    
#pragma mark -
#pragma mark MPSCNNConvolution

/*!
 *  @class      MPSCNNConvolutionState
 *  @discussion The MPSCNNConvolutionState is returned by encode call of MPSCNNConvolution.
 *              It will be consumed by MPSCNNConvolutionTranspose which needs size of source used by corresponding
 *              MPSCNNConvolution in forward pass to correctly size its destination. User is responsible for 
 *              releasing it after it is consumed.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSCNNConvolutionState : MPSState <MPSImageSizeEncodingState>

/*! @property   kernelWidth
 *  @abstract   The width of the kernel MPSCNNConvolution*/
@property(readonly, nonatomic) NSUInteger       kernelWidth;

/*! @property   kernelHeight
 *  @abstract   The height of the kernel MPSCNNConvolution */
@property(readonly, nonatomic) NSUInteger       kernelHeight;

/*! @property   sourceOffset
 *  @abstract   The offset to the source image set on MPSCNNConvolution during the encode call.
 *              This may have been set by the padding policy provided by the user. */
@property(readonly, nonatomic) MPSOffset        sourceOffset;

@end

/*!
 *  @class      MPSCNNConvolution
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSCNNConvolution specifies a convolution.
 *              The MPSCNNConvolution convolves the input image with a set of filters, each producing one feature map in the output image.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface  MPSCNNConvolution : MPSCNNKernel

/*! @property   inputFeatureChannels
 *  @abstract   The number of feature channels per pixel in the input image.
 */
@property(readonly, nonatomic) NSUInteger       inputFeatureChannels;

/*! @property   outputFeatureChannels
 *  @abstract   The number of feature channels per pixel in the output image.
 */
@property(readonly, nonatomic) NSUInteger       outputFeatureChannels;

/*! @property   groups
 *  @abstract   Number of groups input and output channels are divided into.
 */
@property(readonly, nonatomic) NSUInteger      groups;

/*! @property   subPixelScaleFactor
 *  @abstract   Sub pixel scale factor which was passed in as part of MPSCNNConvolutionDescriptor when creating this MPSCNNConvolution object.
 */
@property(readonly, nonatomic) NSUInteger      subPixelScaleFactor;

/*! @property   dilationRateX
 *  @abstract   Dilation rate which was passed in as part of MPSCNNConvolutionDescriptor when creating this MPSCNNConvolution object.
 */
@property(readonly, nonatomic) NSUInteger      dilationRateX;

/*! @property   dilationRate
 *  @abstract   Dilation rate which was passed in as part of MPSCNNConvolutionDescriptor when creating this MPSCNNConvolution object.
 */
@property(readonly, nonatomic) NSUInteger      dilationRateY;

/*! @property   neuron
 *  @abstract   MPSCNNNeuron filter to be applied as part of convolution.
 *              Can be nil in wich case no neuron activation fuction is applied.
 */
@property(readonly, nonatomic) const MPSCNNNeuron * __nullable  neuron
    MPS_AVAILABLE_STARTING_BUT_DEPRECATED( "A MPSCNNNeuron is much too heavy for this purpose. Please use MPSCNNConvolutionNeuronFusedDescriptor instead.",
                                            ios(10.0, 11.0), tvos(10.0, 11.0) );

/*! @abstract   The type of neuron to append to the convolution
 *  @discussion Please see class description for a full list. Default is MPSCNNNeuronTypeNone. */
@property   (readonly, nonatomic) MPSCNNNeuronType     neuronType;

/*! @abstract   Parameter "a" for the neuron.  Default: 1.0f
 *  @discussion Please see class description for interpretation of a. */
@property   (readonly, nonatomic) float                neuronParameterA;

/*! @abstract   Parameter "b" for the neuron.  Default: 1.0f
 *  @discussion Please see class description for interpretation of b. */
@property   (readonly, nonatomic) float                neuronParameterB;

/*! @abstract   Channel multiplier.
 *  @discussion For convolution created with MPSCNNDepthWiseConvolutionDescriptor, it is the number of
 *              output feature channels for each input channel. See MPSCNNDepthWiseConvolutionDescriptor for more details.
 *              Default is 0 which means regular CNN convolution.
 */
@property   (readonly, nonatomic) NSUInteger           channelMultiplier;

/*!
 *  @abstract   Initializes a convolution kernel
 *  @param      device                          The MTLDevice on which this MPSCNNConvolution filter will be used
 *  @param      convolutionDescriptor           A pointer to a MPSCNNConvolutionDescriptor.
 *  @param      kernelWeights                   A pointer to a weights array.  Each entry is a float value. The number of entries is =
 *                                              inputFeatureChannels * outputFeatureChannels * kernelHeight * kernelWidth
 *                                              The layout of filter weight is so that it can be reinterpreted as 4D tensor (array)
 *                                              weight[ outputChannels ][ kernelHeight ][ kernelWidth ][ inputChannels / groups ]
 *                                              Weights are converted to half float (fp16) internally for best performance.
 *  @param      biasTerms                       A pointer to bias terms to be applied to the convolution output.  Each entry is a float value.
 *                                              The number of entries is = numberOfOutputFeatureMaps
 *  @param      flags                           Currently unused. Pass MPSCNNConvolutionFlagsNone
 *
 *  @return     A valid MPSCNNConvolution object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                 convolutionDescriptor: (const MPSCNNConvolutionDescriptor * __nonnull) convolutionDescriptor
                         kernelWeights: (const float * __nonnull) kernelWeights
                             biasTerms: (const float * __nullable) biasTerms
                                 flags: (MPSCNNConvolutionFlags) flags  NS_DESIGNATED_INITIALIZER
        MPS_AVAILABLE_STARTING_BUT_DEPRECATED( "Please use  -initWithDevice:convolutionDescriptor:weights: instead.",
                                               ios(10.0, 11.0), tvos(10.0, 11.0) );

/*!
 *  @abstract   Initializes a convolution kernel
 *  @param      device                          The MTLDevice on which this MPSCNNConvolution filter will be used
 *  @param      weights                         A pointer to a object that conforms to the MPSCNNConvolutionDataSource
 *                                              protocol. The MPSCNNConvolutionDataSource protocol declares the methods that an
 *                                              instance of MPSCNNConvolution uses to obtain the weights and bias terms 
 *                                              for the CNN convolution filter.
 *
 *  @return     A valid MPSCNNConvolution object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                               weights: (nonnull id <MPSCNNConvolutionDataSource>) weights NS_DESIGNATED_INITIALIZER
                                        MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*! @abstract NSSecureCoding compatability
 *  @discussion While the standard NSSecureCoding/NSCoding method
 *              -initWithCoder: should work, since the file can't
 *              know which device your data is allocated on, we
 *              have to guess and may guess incorrectly.  To avoid
 *              that problem, use initWithCoder:device instead.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSKernel
 *  @param      device      The MTLDevice on which to make the MPSKernel
 *  @return     A new MPSKernel object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
                                        MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*
 * Use initWithDevice:weights instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 *  @abstract   Encode a MPSCNNKernel into a command Buffer.  The operation shall proceed out-of-place.
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *  @param      sourceImage         A valid MPSImage object containing the source image.
 *  @param      destinationImage    A valid MPSImage to be overwritten by result image. destinationImage may not alias sourceImage.
 *  @param      outState            A pointer to recieve a state that is consumed by MPSCNNConvolutionTranspose.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                  sourceImage: (MPSImage * __nonnull) sourceImage
             destinationImage: (MPSImage * __nonnull) destinationImage
                        state: (__autoreleasing MPSCNNConvolutionState * __nonnull * __nonnull) outState
            MPS_SWIFT_NAME( encode(commandBuffer:sourceImage:destinationImage:MPSCNNConvolutionState:))
            MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));


@end    /* MPSCNNConvolution */

#pragma mark -
#pragma mark MPSCNNFullyConnected layer

/*!
 *  @class      MPSCNNFullyConnected
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSCNNFullyConnected specifies a fully connected convolution layer a.k.a. Inner product
 *              layer. A fully connected CNN layer is one where every input channel is connected
 *              to every output channel. The kernel width is equal to width of source image
 *              and the kernel height is equal to the height of source image. Width and height of the output
 *              is 1x1. Thus, it takes a srcW x srcH x Ni MPSCNNImage, convolves it with Weights[No][SrcW][srcH][Ni]
 *              and produces a 1 x 1 x No output. The following must be true:
 *@code
 *                         kernelWidth  == source.width
 *                         kernelHeight == source.height
 *                         clipRect.size.width == 1
 *                         clipRect.size.height == 1
 *@endcode
 *              One can think of a fully connected layer as a matrix multiplication that flattens an image into a vector of length
 *              srcW*srcH*Ni. The weights are arragned in a matrix of dimension No x (srcW*srcH*Ni) for product output vectors
 *              of length No. The strideInPixelsX, strideInPixelsY, and group must be 1. Offset is not applicable and is ignored.
 *              Since clipRect is clamped to the destination image bounds, if the destination is 1x1, one doesn't need to set the
 *              clipRect.
 *
 *              Note that one can implement an inner product using MPSCNNConvolution by setting
 *@code
 *                     offset = (kernelWidth/2,kernelHeight/2)
 *                     clipRect.origin = (ox,oy), clipRect.size = (1,1)
 *                     strideX = strideY = group = 1
 *@endcode
 *              However, using the MPSCNNFullyConnected for this is better for performance as it lets us choose the most
 *              performant method which may not be possible when using a general convolution. For example,
 *              we may internally use matrix multiplication or special reduction kernels for a specific platform.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface  MPSCNNFullyConnected : MPSCNNConvolution

/*!
 *  @abstract   Initializes a fully connected kernel.
 *
 *  @param      device                          The MTLDevice on which this MPSCNNFullyConnected filter will be used
 *  @param      fullyConnectedDescriptor        A pointer to a MPSCNNConvolutionDescriptor. strideInPixelsX, strideInPixelsY and group
 *                                              properties of fullyConnectedDescriptor must be set to 1 (default).
 *  @param      kernelWeights                   A pointer to a weights array.  Each entry is a float value. The number of entries is =
 *                                              inputFeatureChannels * outputFeatureChannels * kernelHeight * kernelWidth
 *                                              The layout of filter weight is so that it can be reinterpreted as 4D tensor (array)
 *                                              weight[ outputChannels ][ kernelHeight ][ kernelWidth ][ inputChannels / groups ]
 *                                              Weights are converted to half float (fp16) internally for best performance.
 *  @param      biasTerms                       A pointer to bias terms to be applied to the convolution output.  Each entry is a float value.
 *                                              The number of entries is = numberOfOutputFeatureMaps
 *  @param      flags                           Currently unused. Pass MPSCNNConvolutionFlagsNone
 *
 *  @return     A valid MPSCNNConvolution object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                 convolutionDescriptor: (const MPSCNNConvolutionDescriptor * __nonnull) fullyConnectedDescriptor
                         kernelWeights: (const float * __nonnull) kernelWeights
                             biasTerms: (const float * __nullable) biasTerms
                                 flags: (MPSCNNConvolutionFlags) flags  NS_DESIGNATED_INITIALIZER
        MPS_AVAILABLE_STARTING_BUT_DEPRECATED( "Please use  -initWithDevice:convolutionDescriptor:weights: instead.",
                                               ios(10.0, 11.0), tvos(10.0, 11.0) );

/*!
 *  @abstract   Initializes a fully connected kernel
 *  @param      device                          The MTLDevice on which this MPSCNNFullyConnected filter will be used
 *  @param      weights                         A pointer to a object that conforms to the MPSCNNConvolutionDataSource
 *                                              protocol. The MPSCNNConvolutionDataSource protocol declares the methods that an
 *                                              instance of MPSCNNFullyConnected uses to obtain the weights and bias terms
 *                                              for the CNN fully connected filter.
 *
 *  @return     A valid MPSCNNFullyConnected object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                               weights: (nonnull id <MPSCNNConvolutionDataSource>) weights NS_DESIGNATED_INITIALIZER
                                                MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*! @abstract NSSecureCoding compatability
 *  @discussion While the standard NSSecureCoding/NSCoding method
 *              -initWithCoder: should work, since the file can't
 *              know which device your data is allocated on, we
 *              have to guess and may guess incorrectly.  To avoid
 *              that problem, use initWithCoder:device instead.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSKernel
 *  @param      device      The MTLDevice on which to make the MPSKernel
 *  @return     A new MPSKernel object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
                                                MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*
 * Use initWithDevice:weights instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 * NOTE:    The encodeToCommandBuffer API in MPSCNNKernel can be used to encode a inner product kernel to a MTLCommandBuffer.
 *          The source and destination must be MPSImage.
 */

@end    /* MPSCNNFullyConnected */
    
#pragma mark -
#pragma mark MPSCNNConvolutionTranspose
    
/*!
 *  @class      MPSCNNConvolutionTranspose
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSCNNConvolutionTranspose specifies a transposed convolution.
 *              The MPSCNNConvolutionTranspose convolves the input image with a set of filters, each producing one feature map in the output image.
 *
 *              Some third-party frameworks may rotate the weights spatially by 180 degrees for Convolution Transpose. MPS uses the weights
 *              specified by the developer as-is and does not perform any rotation. The developer may need to rotate the weights appropriately
 *              in case this rotation is needed before the convolution transpose is applied.
 *
 *              When the stride in any dimension is greater than 1, the convolution transpose puts (stride - 1) zeroes in-between the source 
 *              image pixels to create an expanded image. Then a convolution is done over the expanded image to generate the output of the 
 *              convolution transpose.
 *
 *              Intermediate image size = (srcSize - 1) * Stride + 1
 *
 *              Examples:
 *
 *
 *  @code
 *              So in case of sride == 2 (this behaves same in both dimensions)
 *
 *              Source image:
 *               _______________
 *              |   |   |   |   |
 *              | 1 | 2 | 3 | 4 |
 *              |   |   |   |   |
 *               ---------------
 *
 *              Intermediate Image:
 *               ___________________________
 *              |   |   |   |   |   |   |   |
 *              | 1 | 0 | 2 | 0 | 3 | 0 | 4 |
 *              |   |   |   |   |   |   |   |
 *               ---------------------------
 *
 *
 *              NOTE on Offset:
 *              There are 2 types of offsets defined:
 *              1) The Offset defined in MPSCNNKernel from which MPSCNNConvolutionTranspose inherits. This offset is applied to from where
 *                 the kernel will be applied on the source.
 *              2) The kernelOffsetX and kernelOffsetY which is the offset applied to the kernel when it is finally applied on the intermediate
 *                 image.
 *
 *              So totalOffset = Offset * stride + kernelOffset
 *
 *              The offset defined by user refers to the coordinate frame of the expanded image
 *              (we are showing only 1 dimension X it can be extended to Y dimension as well) :
 *
 *              X indicates where the convolution transpose begins:
 *
 *              Intermediate Image:  Offset = 0, kernelOffset = 0
 *               ___________________________
 *              |   |   |   |   |   |   |   |
 *              | 1 | 0 | 2 | 0 | 3 | 0 | 4 |
 *              | X |   |   |   |   |   |   |
 *               ---------------------------
 *
 *
 *              X indicates where the convolution transpose begins:
 *
 *              Intermediate Image:  Offset = 0, kernelOffset = 1
 *               ___________________________
 *              |   |   |   |   |   |   |   |
 *              | 1 | 0 | 2 | 0 | 3 | 0 | 4 |
 *              |   | X |   |   |   |   |   |
 *               ---------------------------
 *
 *
 *              X indicates where the convolution transpose begins:
 *
 *              Intermediate Image:  Offset = 0, kernelOffset = -1
 *                 ___________________________
 *                |   |   |   |   |   |   |   |
 *              X | 1 | 0 | 2 | 0 | 3 | 0 | 4 |
 *                |   |   |   |   |   |   |   |
 *                 ---------------------------
 *
 *
 *
 *
 *              So if the user wanted to apply an offset of 2 on the source image of convolution transpose:
 *
 *              Source image:
 *               _______________
 *              |   |   |   |   |
 *              | 1 | 2 | 3 | 4 |
 *              |   |   | X |   |
 *               ---------------
 *
 *              offset = 2, kernelOffset = 0
 *
 *              Intermediate Image:
 *               ___________________________
 *              |   |   |   |   |   |   |   |
 *              | 1 | 0 | 2 | 0 | 3 | 0 | 4 |
 *              |   |   |   |   | X |   |   |
 *               ---------------------------
 *
 * @endcode
 *
 */


MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSCNNConvolutionTranspose : MPSCNNKernel

/*! @property   inputFeatureChannels
 *  @abstract   The number of feature channels per pixel in the input image.
 */
@property(readonly, nonatomic) NSUInteger       inputFeatureChannels;

/*! @property   outputFeatureChannels
 *  @abstract   The number of feature channels per pixel in the output image.
 */
@property(readonly, nonatomic) NSUInteger       outputFeatureChannels;

/*! @property   kernelOffsetX
 *  @abstract   Offset in X from which the kernel starts sliding
 */
@property(readwrite, nonatomic) NSInteger      kernelOffsetX;

/*! @property   kernelOffsetY
 *  @abstract   Offset in Y from which the kernel starts sliding
 */
@property(readwrite, nonatomic) NSInteger      kernelOffsetY;

/*! @property   groups
 *  @abstract   Number of groups input and output channels are divided into.
 */
@property(readonly, nonatomic) NSUInteger      groups;


/*!
 *  @abstract   Initializes a convolution kernel
 *  @param      device                          The MTLDevice on which this MPSCNNConvolutionTranspose filter will be used
 *  @param      weights                         A pointer to a object that conforms to the MPSCNNConvolutionDataSource
 *                                              protocol. The MPSCNNConvolutionDataSource protocol declares the methods that an
 *                                              instance of MPSCNNConvolutionTranspose uses to obtain the weights and bias terms
 *                                              for the CNN convolutionTranspose filter. Currently we support only Float32 weights.
 *
 *  @return     A valid MPSCNNConvolution object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                               weights: (nonnull id <MPSCNNConvolutionDataSource>) weights NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*
 * Use initWithDevice:convolutionDescriptor:kernelWeights:biasTerms instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*! @abstract <NSSecureCoding> support */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*! @abstract       Encode a MPSCNNKernel into a command Buffer. Create a texture to hold the result and return it.
 *  @discussion     In the first iteration on this method, encodeToCommandBuffer:sourceImage:destinationImage:
 *                  some work was left for the developer to do in the form of correctly setting the offset property
 *                  and sizing the result buffer. With the introduction of the padding policy (see padding property)
 *                  the filter can do this work itself. If you would like to have some input into what sort of MPSImage
 *                  (e.g. temporary vs. regular) or what size it is or where it is allocated, you may set the
 *                  destinationImageAllocator to allocate the image yourself.
 *
 *                  This method uses the MPSNNPadding padding property to figure out how to size
 *                  the result image and to set the offset property. See discussion in MPSNeuralNetworkTypes.h.
 *
 *                  Note: the regular encodeToCommandBuffer:sourceImage: method may be used when no state is needed,
 *                  such as when the convolution transpose operation is not balanced by a matching convolution object upstream.
 *
 *  @param          commandBuffer       The command buffer
 *  @param          sourceImage         A MPSImage to use as the source images for the filter.
 *  @param          convolutionState    A valid MPSCNNConvolutionState from the MPSCNNConvoluton counterpart to this MPSCNNConvolutionTranspose.
 *                                      If there is no forward convolution counterpart, pass NULL here. This state affects the sizing
 *                                      the result.
 *  @result         A MPSImage or MPSTemporaryImage allocated per the destinationImageAllocator containing the output of the graph.
 *                  The offset property will be adjusted to reflect the offset used during the encode.
 *                  The returned image will be automatically released when the command buffer completes. If you want to
 *                  keep it around for longer, retain the image. (ARC will do this for you if you use it later.)
 */
-(MPSImage * __nonnull) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                  sourceImage: (MPSImage *  __nonnull) sourceImage
                             convolutionState: (MPSCNNConvolutionState * __nullable) convolutionState
                    MPS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
                    MPS_SWIFT_NAME( encode(commandBuffer:sourceImage:convolutionState:));


@end    /* MPSCNNConvolutionTranspose */
    


#pragma mark -
#pragma mark MPSCNNBinaryConvolution

/*!
 *  @class      MPSCNNBinaryConvolution
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSCNNBinaryConvolution specifies a convolution with binary weights and an input image using binary approximations.
 *              The MPSCNNBinaryConvolution optionally first binarizes the input image and then convolves the result with a set of
 *              binary-valued filters, each producing one feature map in the output image (which is a normal image)
 *
 *              The output is computed as follows:
 *
 *                  out[i, x, y, c] = ( sum_{dx,dy,f} in[i,x+dx, y+dy, f] x B[c,dx,dy,f] )
 *                                      * scale[c] * beta[i,x,y] + bias[c], where
 *
 *              the sum over dx,dy is over the spatial filter kernel window defined by 'kernelWidth' and 'KernelHeight',
 *              sum over 'f' is over the input feature channel indices within group, 'B' contains the binary weights, interpreted as
 *              {-1,1} or { 0, 1 } and scale[c] is the 'outputScaleTerms' array and bias is the 'outputBiasTerms' array. Above 'i' is
 *              the image index in batch the sum over input channels 'f' runs through the group indices.
 *
 *              The convolution operator 'x' is defined by MPSCNNBinaryConvolutionType passed in at initialization time of the filter
 *              (@see initWithDevice).
 *              In case 'type' = MPSCNNBinaryConvolutionTypeBinaryWeights, the input image is not binarized at all
 *                  and the convolution is computed interpreting the weights as [ 0, 1 ] -> { -1, 1 } with the given scaling terms.
 *              In case 'type' = MPSCNNBinaryConvolutionTypeXNOR the convolution is computed by first binarizing the input image
 *                  using the sign function 'bin(x) = x < 0 ? -1 : 1' and the convolution multiplication is done with the
 *                  XNOR-operator !(x ^ y) = delta_xy = { (x==y) ? 1 : 0 },
 *                  and scaled according to the optional scaling operations. Note that we output the values of the bitwise convolutions
 *                  to interval { -1, 1 }, which means that the output of the XNOR-operator is scaled implicitly as follows:
 *                      r = 2 * ( !(x ^ y) ) - 1 = { -1, 1 }.
 *                  This means that for a dot-product of two 32-bit words the result is:
 *                      r = 2 * popcount(!(x ^ y) ) - 32 = 32 - 2 * popcount( x ^ y ) = { -32, -30, ..., 30, 32 }.
 *              In case 'type' = MPSCNNBinaryConvolutionTypeAND the convolution is computed by first binarizing the input image
 *                  using the sign function 'bin(x) = x < 0 ? -1 : 1' and the convolution multiplication is done with the
 *                  AND-operator (x & y) = delta_xy * delta_x1 = { (x==y==1) ? 1 : 0 }.
 *                  and scaled according to the optional scaling operations. Note that we output the values of the AND-operation is
 *                  assumed to lie in { 0, 1 } interval and hence no more implicit scaling takes place.
 *                  This means that for a dot-product of two 32-bit words the result is:
 *                      r = popcount(x & y) = { 0, ..., 31, 32 }.
 *
 *              The input data can be pre-offset and scaled by providing the 'inputBiasTerms' and 'inputScaleTerms' parameters for the
 *              initialization functions and this can be used for example to accomplish batch normalization of the data. The scaling of
 *              input values happens before possible beta-image computation.
 *
 *              The parameter 'beta' above is an optional image which is used to compute scaling factors for each spatial position and image index.
 *              For the XNOR-Net based networks this is computed as follows: beta[i,x,y] = sum_{dx,dy} A[i, x+dx, y+dy] / (kx * ky), where
 *              (dx,dy) are summed over the convolution filter window [ -kx/2, (kx-1)/2], [ -ky/2, (ky-1)/2 ] and
 *              A[i,x,y] = sum_{c} abs( in[i,x,y,c] ) / Nc, where 'in' is the original input image (in full precision) and Nc is the
 *              number of input channels in the input image. Parameter 'beta' is not passed as input and to enable beta-scaling the user can
 *              provide 'MPSCNNBinaryConvolutionFlagsUseBetaScaling' in the flags parameter in the initialization functions.
 *
 *              Finally the normal activation neuron is applied and the result is written to the output image.
 *
 *              NOTE: MPSCNNBinaryConvolution does not currently support groups > 1.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSCNNBinaryConvolution : MPSCNNKernel

@property(readonly, nonatomic) NSUInteger       inputFeatureChannels;

/*! @property   outputFeatureChannels
 *  @abstract   The number of feature channels per pixel in the output image.
 */
@property(readonly, nonatomic) NSUInteger       outputFeatureChannels;


/*!
 *  @abstract   Initializes a binary convolution kernel with binary weights and a single scaling term.
 *  @param      device                          The MTLDevice on which this MPSCNNBinaryConvolution filter will be used
 *  @param      convolutionData                 A pointer to a object that conforms to the MPSCNNConvolutionDataSource protocol.
 *                                              The MPSCNNConvolutionDataSource protocol declares the methods that an
 *                                              instance of MPSCNNBinaryConvolution uses to obtain the weights and bias terms as
 *                                              well as the convolution descriptor.
 *                                              Each entry in the convolutionData:weights array is a 32-bit unsigned integer value
 *                                              and each bit represents one filter weight (given in machine byte order).
 *                                              The featurechannel indices increase from the least significant bit within the 32-bits.
 *                                              The number of entries is =
 *                                              ceil( inputFeatureChannels/32.0 ) * outputFeatureChannels * kernelHeight * kernelWidth
 *                                              The layout of filter weight is so that it can be reinterpreted as a 4D tensor (array)
 *                                              weight[ outputChannels ][ kernelHeight ][ kernelWidth ][ ceil( inputChannels / 32.0 ) ]
 *                                              (The ordering of the reduction from 4D tensor to 1D is per C convention. The index based on
 *                                              inputchannels varies most rapidly, followed by kernelWidth, then kernelHeight and finally
 *                                              outputChannels varies least rapidly.)
 *  @param      scaleValue                      A floating point value used to scale the entire convolution.
 *  @param      type                            What kind of binarization strategy is to be used.
 *  @param      flags                           See documentation above and documentation of MPSCNNBinaryConvolutionFlags.
 *
 *  @return     A valid MPSCNNBinaryConvolution object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                       convolutionData: (nonnull id <MPSCNNConvolutionDataSource>) convolutionData
                            scaleValue: (float) scaleValue
                                  type: (MPSCNNBinaryConvolutionType) type
                                 flags: (MPSCNNBinaryConvolutionFlags) flags;




/*!
 *  @abstract   Initializes a binary convolution kernel with binary weights as well as both pre and post scaling terms.
 *  @param      device                          The MTLDevice on which this MPSCNNBinaryConvolution filter will be used
 *  @param      convolutionData                 A pointer to a object that conforms to the MPSCNNConvolutionDataSource protocol.
 *                                              The MPSCNNConvolutionDataSource protocol declares the methods that an
 *                                              instance of MPSCNNBinaryConvolution uses to obtain the weights and the convolution descriptor.
 *                                              Each entry in the convolutionData:weights array is a 32-bit unsigned integer value
 *                                              and each bit represents one filter weight (given in machine byte order).
 *                                              The featurechannel indices increase from the least significant bit within the 32-bits.
 *                                              The number of entries is =
 *                                              ceil( inputFeatureChannels/32.0 ) * outputFeatureChannels * kernelHeight * kernelWidth
 *                                              The layout of filter weight is so that it can be reinterpreted as a 4D tensor (array)
 *                                              weight[ outputChannels ][ kernelHeight ][ kernelWidth ][ ceil( inputChannels / 32.0 ) ]
 *                                              (The ordering of the reduction from 4D tensor to 1D is per C convention. The index based on
 *                                              inputchannels varies most rapidly, followed by kernelWidth, then kernelHeight and finally
 *                                              outputChannels varies least rapidly.)
 *  @param      outputBiasTerms                 A pointer to bias terms to be applied to the convolution output.  Each entry is a float value.
 *                                              The number of entries is = numberOfOutputFeatureMaps. If nil then 0.0 is used for bias.
 *                                              The values stored in the pointer are copied in and the array can be freed after this function returns.
 *  @param      outputScaleTerms                A pointer to scale terms to be applied to binary convolution results per output feature channel.
 *                                              Each entry is a float value. The number of entries is = numberOfOutputFeatureMaps. If nil then 1.0 is used.
 *                                              The values stored in the pointer are copied in and the array can be freed after this function returns.
 *  @param      inputBiasTerms                  A pointer to offset terms to be applied to the input before convolution and before input scaling.
 *                                              Each entry is a float value. The number of entries is 'inputFeatureChannels'. If NULL then 0.0 is used for bias.
 *                                              The values stored in the pointer are copied in and the array can be freed after this function returns.
 *  @param      inputScaleTerms                 A pointer to scale terms to be applied to the input before convolution, but after input biasing.
 *                                              Each entry is a float value. The number of entries is 'inputFeatureChannels'. If nil then 1.0 is used.
 *                                              The values stored in the pointer are copied in and the array can be freed after this function returns.
 *  @param      type                            What kind of binarization strategy is to be used.
 *  @param      flags                           See documentation above and documentation of MPSCNNBinaryConvolutionFlags.
 *
 *  @return     A valid MPSCNNBinaryConvolution object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                       convolutionData: (nonnull id <MPSCNNConvolutionDataSource>) convolutionData
                       outputBiasTerms: (const float * __nullable) outputBiasTerms
                      outputScaleTerms: (const float * __nullable) outputScaleTerms
                        inputBiasTerms: (const float * __nullable) inputBiasTerms
                       inputScaleTerms: (const float * __nullable) inputScaleTerms
                                  type: (MPSCNNBinaryConvolutionType) type
                                 flags: (MPSCNNBinaryConvolutionFlags) flags;


/*! @abstract NSSecureCoding compatability
 *  @discussion While the standard NSSecureCoding/NSCoding method
 *              -initWithCoder: should work, since the file can't
 *              know which device your data is allocated on, we
 *              have to guess and may guess incorrectly.  To avoid
 *              that problem, use initWithCoder:device instead.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSKernel
 *  @param      device      The MTLDevice on which to make the MPSKernel
 *  @return     A new MPSKernel object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
            MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));


/*
 * Use initWithDevice:convolutionDescriptor:kernelWeights:biasTerms:scaleTerms:betaImage:flags instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 * NOTE:    The encodeToCommandBuffer API in MPSCNNKernel can be used to encode a XNOR convolution kernel to a MTLCommandBuffer.
 */


@end    /* MPSCNNBinaryConvolution */



#pragma mark -
#pragma mark MPSCNNBinaryFullyConnected

/*!
 *  @class      MPSCNNBinaryFullyConnected
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSCNNBinaryFullyConnected specifies a fully connected convolution layer with binary weights
 *              and optionally binarized input image.
 *              See @ref MPSCNNFullyConnected for details on the fully connected layer and
 *              MPSCNNBinaryConvolution for binary convolutions.
 *
 *              The default padding policy for MPSCNNBinaryConvolution is different from most 
 *              filters. It uses MPSNNPaddingMethodSizeValidOnly instead of MPSNNPaddingMethodSizeSame.
 */

MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface  MPSCNNBinaryFullyConnected : MPSCNNBinaryConvolution


/*!
 *  @abstract   Initializes a binary fully connected kernel with binary weights and a single scaling term.
 *
 *  @param      device                          The MTLDevice on which this MPSCNNBinaryFullyConnected filter will be used
 *  @param      convolutionData                 A pointer to a object that conforms to the MPSCNNConvolutionDataSource protocol.
 *                                              The MPSCNNConvolutionDataSource protocol declares the methods that an
 *                                              instance of MPSCNNBinaryFullyConnected uses to obtain the weights and bias terms as
 *                                              well as the convolution descriptor.
 *                                              Each entry in the convolutionData:weights array is a 32-bit unsigned integer value
 *                                              and each bit represents one filter weight (given in machine byte order).
 *                                              The featurechannel indices increase from the least significant bit within the 32-bits.
 *                                              The number of entries is =
 *                                              ceil( inputFeatureChannels/32.0 ) * outputFeatureChannels * kernelHeight * kernelWidth
 *                                              The layout of filter weight is so that it can be reinterpreted as a 4D tensor (array)
 *                                              weight[ outputChannels ][ kernelHeight ][ kernelWidth ][ ceil( inputChannels / 32.0 ) ]
 *                                              (The ordering of the reduction from 4D tensor to 1D is per C convention. The index based on
 *                                              inputchannels varies most rapidly, followed by kernelWidth, then kernelHeight and finally
 *                                              outputChannels varies least rapidly.)
 *  @param      scaleValue                      A single floating point value used to scale the entire convolution.
 *                                              Each entry is a float value. The number of entries is 'inputFeatureChannels'. If nil then 1.0 is used.
 *  @param      type                            What kind of binarization strategy is to be used.
 *  @param      flags                           See documentation above and documentation of MPSCNNBinaryConvolutionFlags.
 *
 *  @return     A valid MPSCNNBinaryFullyConnected object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                       convolutionData: (nonnull id <MPSCNNConvolutionDataSource>) convolutionData
                            scaleValue: (float) scaleValue
                                  type: (MPSCNNBinaryConvolutionType) type
                                 flags: (MPSCNNBinaryConvolutionFlags) flags;



/*!
 *  @abstract   Initializes a binary fully connected kernel with binary weights as well as both pre and post scaling terms.
 *
 *  @param      device                          The MTLDevice on which this MPSCNNBinaryFullyConnected filter will be used
 *  @param      convolutionData                 A pointer to a object that conforms to the MPSCNNConvolutionDataSource protocol.
 *                                              The MPSCNNConvolutionDataSource protocol declares the methods that an
 *                                              instance of MPSCNNBinaryFullyConnected uses to obtain the weights and the convolution descriptor.
 *                                              Each entry in the convolutionData:weights array is a 32-bit unsigned integer value
 *                                              and each bit represents one filter weight (given in machine byte order).
 *                                              The featurechannel indices increase from the least significant bit within the 32-bits.
 *                                              The number of entries is =
 *                                              ceil( inputFeatureChannels/32.0 ) * outputFeatureChannels * kernelHeight * kernelWidth
 *                                              The layout of filter weight is so that it can be reinterpreted as a 4D tensor (array)
 *                                              weight[ outputChannels ][ kernelHeight ][ kernelWidth ][ ceil( inputChannels / 32.0 ) ]
 *                                              (The ordering of the reduction from 4D tensor to 1D is per C convention. The index based on
 *                                              inputchannels varies most rapidly, followed by kernelWidth, then kernelHeight and finally
 *                                              outputChannels varies least rapidly.)
 *
 *  @param      outputBiasTerms                 A pointer to bias terms to be applied to the convolution output.  Each entry is a float value.
 *                                              The number of entries is = numberOfOutputFeatureMaps. If nil then 0.0 is used for bias.
 *                                              The values stored in the pointer are copied in and the array can be freed after this function returns.
 *  @param      outputScaleTerms                A pointer to scale terms to be applied to binary convolution results per output feature channel.
 *                                              Each entry is a float value. The number of entries is = numberOfOutputFeatureMaps. If nil then 1.0 is used.
 *                                              The values stored in the pointer are copied in and the array can be freed after this function returns.
 *  @param      inputBiasTerms                  A pointer to offset terms to be applied to the input before convolution and before input scaling.
 *                                              Each entry is a float value. The number of entries is 'inputFeatureChannels'. If NULL then 0.0 is used for bias.
 *                                              The values stored in the pointer are copied in and the array can be freed after this function returns.
 *  @param      inputScaleTerms                 A pointer to scale terms to be applied to the input before convolution, but after input biasing.
 *                                              Each entry is a float value. The number of entries is 'inputFeatureChannels'. If nil then 1.0 is used.
 *                                              The values stored in the pointer are copied in and the array can be freed after this function returns.
 *  @param      type                            What kind of binarization strategy is to be used.
 *  @param      flags                           See documentation above and documentation of MPSCNNBinaryConvolutionFlags.
 *
 *  @return     A valid MPSCNNBinaryFullyConnected object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                       convolutionData: (nonnull id <MPSCNNConvolutionDataSource>) convolutionData
                       outputBiasTerms: (const float * __nullable) outputBiasTerms
                      outputScaleTerms: (const float * __nullable) outputScaleTerms
                        inputBiasTerms: (const float * __nullable) inputBiasTerms
                       inputScaleTerms: (const float * __nullable) inputScaleTerms
                                  type: (MPSCNNBinaryConvolutionType) type
                                 flags: (MPSCNNBinaryConvolutionFlags) flags;



/*! @abstract NSSecureCoding compatability
 *  @discussion While the standard NSSecureCoding/NSCoding method
 *              -initWithCoder: should work, since the file can't
 *              know which device your data is allocated on, we
 *              have to guess and may guess incorrectly.  To avoid
 *              that problem, use initWithCoder:device instead.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSKernel
 *  @param      device      The MTLDevice on which to make the MPSKernel
 *  @return     A new MPSKernel object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));


/*
 * Use initWithDevice:convolutionDescriptor:kernelWeights:biasTerms:scaleTerms:betaImage:flags instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 * NOTE:    The encodeToCommandBuffer API in MPSCNNKernel can be used to encode a inner product kernel to a MTLCommandBuffer.
 */

@end    /* MPSCNNBinaryFullyConnected */






#ifdef __cplusplus
}
#endif


#endif /* MPSCNNConvolution_h */
