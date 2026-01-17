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
#include <MPSNeuralNetwork/MPSCNNNeuron.h>
#include <MPSCore/MPSState.h>
#include <MPSNeuralNetwork/MPSNNGradientState.h>
#include <simd/simd.h>

#ifdef __cplusplus
extern "C" {
#endif


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

/*!
 *  @property   fusedNeuronDescriptor
 *  @discussion This mathod can be used to add a neuron activation funtion of given type with
 *              associated scalar parameters A and B that are shared across all output channels.
 *              Neuron activation fucntion is applied to output of convolution. This is a per-pixel
 *              operation that is fused with convolution kernel itself for best performance.
 *              Note that this method can only be used to fuse neuron of kind for which parameters
 *              A and B are shared across all channels of convoution output. It is an error to call
 *              this method for neuron activation functions like MPSCNNNeuronTypePReLU,
 *              which require per-channel parameter values. For those kind of neuron activation functions,
 *              use appropriate setter functions. Default is descriptor with neuronType MPSCNNNeuronTypeNone.
 *
 *              Note: in certain cases the neuron descriptor will be cached by the MPSNNGraph or the
 *              MPSCNNConvolution. If the neuron type changes after either is made, behavior is undefined.
 */
@property(readwrite, nonatomic, retain) MPSNNNeuronDescriptor* __nonnull fusedNeuronDescriptor
                                        MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3));

/*! @property   neuron
 *  @abstract   MPSCNNNeuron filter to be applied as part of convolution. This is applied after BatchNormalization in the end.
 *              Default is nil.
 *              This is deprecated. You dont need to create MPSCNNNeuron object to fuse with convolution. Use neuron properties
 *              in this descriptor.
 */
@property(readwrite, nonatomic, retain) const MPSCNNNeuron * __nullable  neuron
        MPS_AVAILABLE_STARTING_BUT_DEPRECATED(  "A MPSCNNNeuron:MPSKernel is much too heavy an object to\n"
                                                "represent what is a type code and two floats. It is deprecated.\n"
                                                "Please set fusedNeuronDescriptor property instead.",
                                                ios(10.0, 11.0), tvos(10.0, 11.0));

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
 *              Note: in certain cases the batch normalization parameters will be cached by the MPSNNGraph
 *              or the MPSCNNConvolution. If the batch normalization parameters change after either is made,
 *              behavior is undefined.
 *
 *  @param      mean                        Pointer to an array of floats of mean for each output feature channel
 *  @param      variance                    Pointer to an array of floats of variance for each output feature channel
 *  @param      gamma                       Pointer to an array of floats of gamma for each output feature channel
 *  @param      beta                        Pointer to an array of floats of beta for each output feature channel
 *  @param      epsilon                     A small float value used to have numerical stability in the code
 */
-(void) setBatchNormalizationParametersForInferenceWithMean: (const float * __nullable) mean
                                                   variance: (const float * __nullable) variance
                                                      gamma: (const float * __nullable) gamma
                                                       beta: (const float * __nullable) beta
                                                    epsilon: (const float) epsilon
                                                                MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*!
 *  @abstract   Adds a neuron activation function to convolution descriptor.
 *
 *  @discussion This mathod can be used to add a neuron activation funtion of given type with
 *              associated scalar parameters A and B that are shared across all output channels.
 *              Neuron activation fucntion is applied to output of convolution. This is a per-pixel
 *              operation that is fused with convolution kernel itself for best performance.
 *              Note that this method can only be used to fuse neuron of kind for which parameters
 *              A and B are shared across all channels of convoution output. It is an error to call
 *              this method for neuron activation functions like MPSCNNNeuronTypePReLU,
 *              which require per-channel parameter values. For those kind of neuron activation functions,
 *              use appropriate setter functions.
 *
 *              Note: in certain cases, the neuron descriptor will be cached by the MPSNNGraph or the
 *              MPSCNNConvolution. If the neuron type changes after either is made, behavior is undefined.
 *
 *  @param      neuronType      type of neuron activation function. For full list see MPSCNNNeuronType.h
 *  @param      parameterA      parameterA of neuron activation that is shared across all channels of convolution output.
 *  @param      parameterB      parameterB of neuron activation that is shared across all channels of convolution output.
 */
-(void) setNeuronType: (MPSCNNNeuronType) neuronType
           parameterA: (float) parameterA
           parameterB: (float) parameterB
                                        MPS_AVAILABLE_STARTING_BUT_DEPRECATED( "set fusedNeuronDescriptor property instead",
                                              macos(10.13, 10.13.4), ios(11.0, 11.3), tvos(11.0, 11.3) );

/*!
 *  @abstract   Getter funtion for neuronType set using setNeuronType:parameterA:parameterB method
 */
-(MPSCNNNeuronType) neuronType
                    MPS_AVAILABLE_STARTING_BUT_DEPRECATED( "use fusedNeuronDescriptor property instead",
                                      macos(10.13, 10.13.4), ios(11.0, 11.3), tvos(11.0, 11.3) );

/*!
 *  @abstract   Getter funtion for neuronType set using setNeuronType:parameterA:parameterB method
 */
-(float) neuronParameterA
                    MPS_AVAILABLE_STARTING_BUT_DEPRECATED( "use fusedNeuronDescriptor property instead",
                                      macos(10.13, 10.13.4), ios(11.0, 11.3), tvos(11.0, 11.3) );

/*!
 *  @abstract   Getter funtion for neuronType set using setNeuronType:parameterA:parameterB method
 */
-(float) neuronParameterB
                    MPS_AVAILABLE_STARTING_BUT_DEPRECATED( "use fusedNeuronDescriptor property instead",
                                      macos(10.13, 10.13.4), ios(11.0, 11.3), tvos(11.0, 11.3) );

/*!
 *  @abstract   Add per-channel neuron parameters A for PReLu neuron activation functions.
 *
 *  @discussion This method sets the neuron to PReLU, zeros parameters A and B and sets the per-channel
 *              neuron parameters A to an array containing a unique value of A for each output feature
 *              channel.
 *
 *              If the neuron function is f(v,a,b), it will apply
 *
 *                     OutputImage(x,y,i) = f( ConvolutionResult(x,y,i), A[i], B[i] ) where i in [0,outputFeatureChannels-1]
 *
 *              See https://arxiv.org/pdf/1502.01852.pdf for details.
 *
 *              All other neuron types, where parameter A
 *              and parameter B are shared across channels must be set using
 *              -setNeuronOfType:parameterA:parameterB:
 *
 *              If batch normalization parameters are set, batch normalization will occur before
 *              neuron application i.e. output of convolution is first batch normalized followed
 *              by neuron activation. This function automatically sets neuronType to MPSCNNNeuronTypePReLU.
 *
 *              Note: in certain cases the neuron descriptor will be cached by the MPSNNGraph or the
 *              MPSCNNConvolution. If the neuron type changes after either is made, behavior is undefined.
 *
 *  @param      A       An array containing per-channel float values for neuron parameter A.
 *                      Number of entries must be equal to outputFeatureChannels.
 */
-(void) setNeuronToPReLUWithParametersA: (NSData* __nonnull) A
                            MPS_AVAILABLE_STARTING_BUT_DEPRECATED( "use fusedNeuronDescriptor property instead",
                                      macos(10.13, 10.13.4), ios(11.0, 11.3), tvos(11.0, 11.3) );

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
 *                              Weights [inputFeatureChannels] [channelMultiplier] [kH] [kW]
 *                            = Weights [ inputFeatureChannels * channelMultiplier ] [kH] [kW]
 *                            = Weights [ outputFeatureChannels ] [kH] [kW]
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
    
/*! @enum        MPSCNNWeightsQuantizationType
 *  @discussion A value to specify a type of quantization used to generate quantized UInt weights.
 *              Same scheme will be used to dequantize weights to fp16 for CNN convolution.
 *
 *  @constant   MPSCNNWeightsQuantizationTypeNone       No quantization. Weights are fp16 or fp32
 *  @constant   MPSCNNWeightsQuantizationTypeLinear     Linear quantization of range in which weights lie in 2^b bins where b
                                                        is bit depth of quantized coefficients.
 *  @constant   MPSCNNWeightsQuantizationTypeLookupTable A lookup table of 2^b entries is used to map b-bit quantized weight to floating point value.
 */
#if defined(DOXYGEN)
    typedef enum MPSCNNWeightsQuantizationType
#else
    typedef NS_ENUM(uint32_t, MPSCNNWeightsQuantizationType)
#endif
    {
        MPSCNNWeightsQuantizationTypeNone           MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(11.0), tvos(11.0)) MPS_SWIFT_NAME(none) = 0,
        MPSCNNWeightsQuantizationTypeLinear         MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(11.0), tvos(11.0)) MPS_SWIFT_NAME(none) = 1,
        MPSCNNWeightsQuantizationTypeLookupTable    MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(11.0), tvos(11.0)) MPS_SWIFT_NAME(none) = 2,
    }
#if defined(DOXYGEN)
    MPSCNNWeightsQuantizationType
#endif
    ;

    
@class MPSCNNConvolution;
@protocol MPSCNNConvolutionDataSource;
/*!
 *  @class      MPSCNNConvolutionGradientState
 *  @discussion The MPSCNNConvolutionGradientState is returned by resultStateForSourceImage:sourceStates method on MPSCNNConvolution object.
 *              Note that resultStateForSourceImage:sourceStates:destinationImage creates the object on autoreleasepool.
 *              It will be consumed by MPSCNNConvolutionGradient. This used by MPSCNNConvolutionTranspose encode call
 *              that returns MPSImage on left hand side to correctly size the destination.
 *              Note that state objects are not usable across batches i.e. when batch is done you should nuke the state object and create
 *              new one for next batch.
 *
 *              This state exposes the gradient with respect to weights and biases, as computed by the MPSCNNConvolutionGradient kernel, as a metal buffer to be used
 *              during weights and biases update. The standard weights and biases update formula is:
 *
 *                        weights(t+1) = f(weights(t), gradientForWeights(t)) and
 *                        biases(t+1) = f(biases(t), gradientForBiases(t)),
 *
 *              where the weights(t)/biases(t) are the wegihts and the biases at step t that are provided by data source provider used to create MPSCNNConvolution and
 *              MPSCNNConvoltuionGradient objects. There are multiple ways user can update weights and biases as described below:
 *
 *              1) For check pointing, i.e. updating weights/biases and storing:
 *                   once the command buffer on which MPSCNNConvolutionGradient is enqueued is done (e.g. in command
 *                 buffer completion callback), the application can simply use
 *                                    float* delta_w = (float*)((char*)[gradientForWeights contents]);
 *                                    float* delta_b = (float*)((char*)[gradientForBiases contents]);
 *                  to update the weights and biases in the data provider directly.
 *                  The application can instead provide a metal kernel that reads from gradientForWeights and gradientForBiases buffer and the buffer created using data provided by the data source
 *                  to do any kind of update it will like to do, then read back the updated weights/biases and store to the data source. Note that lifetime of the
 *                  gradientForWeights and gradientForBiases buffer is the same as the MPSCNNConvolutionGradientState. So it's the applications's responsibility to make sure the buffer is alive
 *                  (retained) when the update kernel is running if the command buffer doesn't retain the buffer. Also, in order to gaurantee that the buffer is correctly
 *                  synchronized for CPU side access, it is the application's responsibility to call
 *                                     [gradientState synchronizeOnCommandBuffer:]
 *                  before accessing data from the buffer.
 *
 *              2) For a CPU side update, once the weights and biases in the data source provider are updated as above, the original MPSCNNConvolution and
 *                 MPSCNNConvolutionGradient objects need to be updated with the new weigths and biases by calling the
 *                       -(void) reloadWeightsAndBiasesFromDataSource
 *                 method. Again application needs to call [gradientState synchronizeOnCommandBuffer:] before touching data on CPU side.
 *
 *              3) The above CPU side update requires command buffer to be done. If the application doesn't want to update its data source provider object and would prefer to directly
 *                 enqueue an update of the internal MPSCNNConvolution and MPSCNNConvolutionGradient weights/biases buffers on the GPU without CPU side involvement, it needs to do
 *                 following:
 *                     i) get gradientForWeights and gradientForBiases buffers from this gradient state object and set it as source of update kernel
 *                    ii) create a temporary buffer, dest, of same size and set it as destination of update kernel
 *                   iii) enqueue update kernel on command buffer
 *                    iv) call reloadWeightsAndBiasesWithCommandBuffer:dest:weightsOffset:biasesOffset on MPSCNNConvolution and MPSCNNConvolutionGradient objects. This
 *                        will reload the weights from application's update kernel in dest on GPU without CPU side involvement.
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface MPSCNNConvolutionGradientState : MPSNNGradientState <MPSImageSizeEncodingState>

/*! @property   gradientForWeights
 *  @abstract   A buffer that contains the loss function gradients with respect to weights.
 *              Each value in the buffer is a float. The layout of the gradients with respect to the weights is the same as
 *              the weights layout provided by data source i.e. it can be interpreted as 4D array
 *
 *                   gradientForWeights[outputFeatureChannels][kernelHeight][kernelWidth][inputFeatureChannels/groups]
 */
@property (readonly, nonatomic) __nonnull id<MTLBuffer> gradientForWeights;

/*! @property   gradientForBiases
 *  @abstract   A buffer that contains the loss function gradients with respect to biases.
 */
@property (readonly, nonatomic) __nonnull id<MTLBuffer> gradientForBiases;

/*! @property   convolution
 *  @abstract   The convolution filter that produced the state. */
@property (readonly, nonatomic, retain, nonnull) MPSCNNConvolution * convolution;

@end
    
typedef NSArray<MPSCNNConvolutionGradientState*>  MPSCNNConvolutionGradientStateBatch
        MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3));

/*!
 *  @class      MPSCNNConvolutionWeightsAndBiasesState
 *  @discussion The MPSCNNConvolutionWeightsAndBiasesState is returned by exportWeightsAndBiasesWithCommandBuffer: method on MPSCNNConvolution object.
 *              This is mainly used for GPU side weights/biases update process.
 *              During training, application can keep a copy of weights, velocity, momentum MTLBuffers in its data source, update the weights (in-place or out of place)
 *              with gradients obtained from MPSCNNConvolutionGradientState and call [MPSCNNConvolution reloadWeightsAndBiasesWithCommandBuffer] with resulting updated
 *              MTLBuffer. If application does not want to keep a copy of weights/biases, it can call [MPSCNNConvolution exportWeightsAndBiasesWithCommandBuffer:] to get
 *              the current weights from convolution itself, do the updated and call reloadWithCommandBuffer.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface MPSCNNConvolutionWeightsAndBiasesState : MPSState

/*! @property   weights
 *  @abstract   A buffer that contains the weights.
 *              Each value in the buffer is a float. The layout of the weights with respect to the weights is the same as
 *              the weights layout provided by data source i.e. it can be interpreted as 4D array
 *
 *                   weights[outputFeatureChannels][kernelHeight][kernelWidth][inputFeatureChannels/groups]
 */
@property (readonly, nonatomic) __nonnull id<MTLBuffer> weights;

/*! @property   biases
 *  @abstract   A buffer that contains the biases. Each value is float and there are ouputFeatureChannels values.
 */
@property (readonly, nonatomic) __nullable id<MTLBuffer> biases;

- (nonnull instancetype) initWithWeights: (__nonnull id<MTLBuffer>) weights
                                  biases: (__nullable id<MTLBuffer>) biases;

- (nonnull instancetype) initWithDevice: (__nonnull id<MTLDevice>) device
               cnnConvolutionDescriptor: (MPSCNNConvolutionDescriptor* __nonnull) descriptor;

+ (nonnull instancetype) temporaryCNNConvolutionWeightsAndBiasesStateWithCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
                                                              cnnConvolutionDescriptor: (MPSCNNConvolutionDescriptor* __nonnull) descriptor;

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
@protocol MPSCNNConvolutionDataSource <NSCopying, NSObject>

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
     *              Note: load may be called to merely inspect the descriptor.
     *              In some circumstances, it may be worthwhile to postpone
     *              weight and bias construction until they are actually needed
     *              to save touching memory and keep the working set small.
     *              The load function is intended to be an opportunity to open
     *              files or mark memory no longer purgeable. 
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
    
    /* MPSDataTypeUInt8 weight containers must implement one of the following optional methods.
       If quantizationMode method returns linear, rangesForUInt8Kernel must be implemented.
       If quantizationMode method returns lookupTable, lookupTableForUInt8Kernel should be returned.
     */
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
    
    /*! @abstract       Quantizaiton type of weights. If it returns MPSCNNWeightsQuantizationTypeLookupTable,
     *                  lookupTableForUInt8Kernel method must be implmented. if it returns MPSCNNWeightsQuantizationTypeLookupLinear,
     *                  rangesForUInt8Kernel method must be implemented.
     */
    -(MPSCNNWeightsQuantizationType) weightsQuantizationType;
    
    /*! @abstract   Callback for the MPSNNGraph to update the convolution weights on GPU.
     *  @discussion It is the resposibility of this method to decrement the read count of both the gradientState
     *              and the sourceState before returning.  BUG: prior to macOS 10.14, ios/tvos 12.0, the MPSNNGraph
     *              incorrectly decrements the readcount of the gradientState after this method is called.
     *
     *  @param      commandBuffer   The command buffer on which to do the update.
     *                              MPSCNNConvolutionGradientNode.MPSNNTrainingStyle controls where you want your update
     *                              to happen. Provide implementation of this function for GPU side update.
     *  @param      gradientState   A state object produced by the MPSCNNConvolution and updated by MPSCNNConvolutionGradient
     *                              containing weight gradients.
     *  @param      sourceState     A state object containing the convolution weights
     *  @return     If NULL, no update occurs. If nonnull, the result will be used to update the
     *              weights in the MPSNNGraph  */
    -(MPSCNNConvolutionWeightsAndBiasesState* __nullable) updateWithCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
                                                                    gradientState: (MPSCNNConvolutionGradientState* __nonnull) gradientState
                                                                      sourceState: (MPSCNNConvolutionWeightsAndBiasesState* __nonnull) sourceState
                                                                                        MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3));
    
    /*! @abstract   Callback for the MPSNNGraph to update the convolution weights on CPU.
     *                               MPSCNNConvolutionGradientNode.MPSNNTrainingStyle controls where you want your update
     *                              to happen. Provide implementation of this function for CPU side update.
     *  @param      gradientState   A state object produced by the MPSCNNConvolution and updated by MPSCNNConvolutionGradient
     *                              containing weight gradients. MPSNNGraph is responsible for calling [gradientState synchronizeOnCommandBuffer:]
     *                              so that application get correct gradients for CPU side update.
     *  @param      sourceState     A state object containing the convolution weights used. MPSCNNConvolution and MPSCNNConvolutionGradient reloadWeightsWithDataSource
     *                              will be called right after this method is called. Note that the weights returned here may not match the weights
     *                              in your data source due to conversion loss. These are the weights actually used, and should
     *                              be what you use to calculate the new weights. Your copy may be incorrect. Write the new weights
     *                              to your copy and return them out the left hand side.
     * @return                      TRUE if success/no error, FALSE in case of failure.
     */
    - (BOOL) updateWithGradientState: (MPSCNNConvolutionGradientState* __nonnull) gradientState
                         sourceState: (MPSCNNConvolutionWeightsAndBiasesState* __nonnull) sourceState
                                         MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3));

    /*! @abstract  When copyWithZone:device on convolution is called, data source copyWithZone:device
     *             will be called if data source object responds to this selector. If not, copyWithZone:
     *             will be called if data source responds to it. Otherwise, it is simply retained.
     *             This is to allow application to make a separate copy of data source in convolution
     *             when convolution itself is coplied, for example when copying training graph for running
     *             on second GPU so that weights update on two different GPUs dont end up stomping same
     *             data source.
     */

    -(nonnull instancetype) copyWithZone: (nullable NSZone*) zone
                                  device: (nullable id <MTLDevice>) device MPS_AVAILABLE_STARTING(macos(10.14), ios(12.0), tvos(12.0));


@end
    
#pragma mark -
#pragma mark MPSCNNConvolution

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

/*! @property   dataSource
 *  @abstract   dataSource with which convolution object was created
 */
@property(readonly, nonatomic, retain, nonnull) id<MPSCNNConvolutionDataSource>      dataSource;

/*! @property   subPixelScaleFactor
 *  @abstract   Sub pixel scale factor which was passed in as part of MPSCNNConvolutionDescriptor when creating this MPSCNNConvolution object.
 */
@property(readonly, nonatomic) NSUInteger      subPixelScaleFactor;

/*! @property   neuron
 *  @abstract   MPSCNNNeuron filter to be applied as part of convolution.
 *              Can be nil in wich case no neuron activation fuction is applied.
 */
@property(readonly, nonatomic) const MPSCNNNeuron * __nullable  neuron
    MPS_AVAILABLE_STARTING_BUT_DEPRECATED( "A MPSCNNNeuron is much too heavy for this purpose. Please set fusedNeuronDescriptor property of convolution descriptor instead.",
                                            ios(10.0, 11.0), tvos(10.0, 11.0) );

/*! @abstract   The type of neuron to append to the convolution
 *  @discussion Please see class description for a full list. Default is MPSCNNNeuronTypeNone. */
@property   (readonly, nonatomic) MPSCNNNeuronType     neuronType
    MPS_AVAILABLE_STARTING_BUT_DEPRECATED( "Use fusedNeuronDesciptor instead.",
                                        macos(10.13, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0) );

/*! @abstract   Parameter "a" for the neuron.  Default: 1.0f
 *  @discussion Please see class description for interpretation of a. */
@property   (readonly, nonatomic) float                neuronParameterA
    MPS_AVAILABLE_STARTING_BUT_DEPRECATED( "Use fusedNeuronDesciptor instead.",
                                        macos(10.13, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0) );

/*! @abstract   Parameter "b" for the neuron.  Default: 1.0f
 *  @discussion Please see class description for interpretation of b. */
@property   (readonly, nonatomic) float                neuronParameterB
    MPS_AVAILABLE_STARTING_BUT_DEPRECATED( "Use fusedNeuronDesciptor instead.",
                                        macos(10.13, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0) );

/*! @abstract   Parameter "c" for the neuron.  Default: 1.0f
 *  @discussion Please see class description for interpretation of c. */
@property   (readonly, nonatomic) float                neuronParameterC
    MPS_AVAILABLE_STARTING_BUT_DEPRECATED( "Use fusedNeuronDesciptor instead.",
                                        macos(10.13, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0) );

/*! @abstract   Fused neuron descritor passed in convolution descriptor for fusion with convolution.
 *  @discussion Please see class description for interpretation of c. */
@property (readonly, nonatomic) MPSNNNeuronDescriptor* __nullable fusedNeuronDescriptor
                                MPS_CLASS_AVAILABLE_STARTING( macos(10.14), ios(12.0), tvos(12.0));

/*! @abstract   Channel multiplier.
 *  @discussion For convolution created with MPSCNNDepthWiseConvolutionDescriptor, it is the number of
 *              output feature channels for each input channel. See MPSCNNDepthWiseConvolutionDescriptor for more details.
 *              Default is 0 which means regular CNN convolution.
 */
@property   (readonly, nonatomic) NSUInteger           channelMultiplier;

/*! @abstract    Precision of accumulator used in convolution.
 *  @discussion  See MPSNeuralNetworkTypes.h for discussion. Default is MPSNNConvolutionAccumulatorPrecisionOptionFloat.
 */
@property   (readwrite, nonatomic) MPSNNConvolutionAccumulatorPrecisionOption accumulatorPrecisionOption
                                                                      MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3));

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

/*!
 *  @abstract   Initializes a convolution kernel
 *              WARNING:                        This API is depreated and will be removed in the future. It cannot be used
 *                                              when training. Also serialization/unserialization wont work for MPSCNNConvolution
 *                                              objects created with this init. Please move onto using initWithDevice:weights:.
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

/*! @abstract   Allocate a MPCNNConvolutionGradientSState to hold the results from a -encodeBatchToCommandBuffer... operation
 *
 *  @param      sourceImage         The MPSImage consumed by the associated -encode call.
 *  @param      sourceStates        The list of MPSStates consumed by the associated -encode call,
 *                                  for a batch size of 1.
 *  @return     The list of states produced by the -encode call for batch size of 1.
 *              -isResultStateReusedAcrossBatch returns YES for MPSCNNConvolution so same
 *              state is used across entire batch. State object is not reusasable across batches.
 */
-(MPSCNNConvolutionGradientState * __nullable) resultStateForSourceImage: (MPSImage *__nonnull) sourceImage
                                                            sourceStates: (NSArray <MPSState *> *__nullable) sourceStates
                                                        destinationImage: (MPSImage *__nonnull) destinationImage
                                                                                MPS_SWIFT_NAME( resultState(sourceImage:sourceStates:destinationImage:))
                                                                                MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3));

/* To be used with batch encode call. Since same state is used across entire batch, it will return copy of same state in returned NSArray*/
-(MPSCNNConvolutionGradientStateBatch * __nullable) resultStateBatchForSourceImage: (MPSImageBatch * __nonnull) sourceImage
                                                                      sourceStates: (NSArray<MPSStateBatch *> * __nullable) sourceStates
                                                                  destinationImage:(MPSImageBatch * _Nonnull)destinationImage
                                                                    MPS_SWIFT_NAME( resultStateBatch(sourceImage:sourceStates:destinationImage:))
                                                                    MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3));

-(MPSCNNConvolutionGradientState * __nullable) temporaryResultStateForCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                                                        sourceImage: (MPSImage *__nonnull) sourceImage
                                                                       sourceStates: (NSArray <MPSState *> *__nullable) sourceStates
                                                                   destinationImage: (MPSImage * __nonnull)destinationImage
                                                                    MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3))
                                                                    MPS_SWIFT_NAME( temporaryResultState(commandBuffer:sourceImage:sourceStates:destinationImage:));

-(MPSCNNConvolutionGradientStateBatch * __nullable) temporaryResultStateBatchForCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                                                                  sourceImage: (MPSImageBatch *__nonnull) sourceImage
                                                                                 sourceStates: (NSArray <MPSStateBatch *> *__nullable) sourceStates
                                                                             destinationImage: (MPSImageBatch *__nonnull) destinationImage
                                                                    MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3))
                                                                    MPS_SWIFT_NAME( temporaryResultStateBatch(commandBuffer:sourceImage:sourceStates:destinationImage:));

/*! @abstract   CPU side reload. Reload the updated weights and biases from data provider into internal weights and bias buffers. Weights and biases
 *              gradients needed for update are obtained from MPSCNNConvolutionGradientState object. Data provider passed in init call is used for this purpose.
 */
-(void) reloadWeightsAndBiasesFromDataSource
            MPS_AVAILABLE_STARTING(macos(10.14), ios(12.0), tvos(12.0));

/*! Deprecated. dataSource will be ignored. */
-(void) reloadWeightsAndBiasesWithDataSource: (__nonnull id<MPSCNNConvolutionDataSource>) dataSource
            MPS_AVAILABLE_STARTING_BUT_DEPRECATED("Please use -reloadWeightsAndBiasesFromDataSource instead. ", macos(10.13.4, 10.14), ios(11.3, 12.0), tvos(11.3, 12.0));


/*! @abstract   GPU side reload. Reload the updated weights and biases from update buffer produced by application enqueued metal kernel into internal weights
 *              and biases buffer. Weights and biases gradients needed for update are obtained from MPSCNNConvolutionGradientState object's gradientForWeights and gradientForBiases metal buffer.
 *
 *  @param      commandBuffer      Metal command buffer on which application update kernel was enqueued consuming MPSCNNConvolutionGradientState's gradientForWeights and gradientForBiases buffers
 *                                 and producing updateBuffer metal buffer.
 *  @param      state              MPSCNNConvolutionWeightsAndBiasesState containing weights and biases buffers which have updated weights produced by application's update kernel.
 *                                 The state readcount will be decremented.
 *
 */
-(void) reloadWeightsAndBiasesWithCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
                                          state: (MPSCNNConvolutionWeightsAndBiasesState* __nonnull) state
                                    MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3));

/*! @abstract   GPU side export. Enqueue a kernel to export current weights and biases stored in MPSCNNConvoltion's internal buffers into weights and biases MTLBuffer
 *              returned in MPSCNNConvolutionWeightsAndBiasesState.
 *
 *  @param      commandBuffer              Metal command buffer on which export kernel is enqueued.
 *  @param      resultStateCanBeTemporary  If FALSE, state returned will be non-temporary. If TRUE, returned state may or may not be temporary.
 *  @return     MPSCNNConvolutionWeightsAndBiasesState containing weights and biases buffer to which weights got exported. This state and be
                temporary or non-temporary depending on the flag resultStateCanBeTemporary
 */
- (MPSCNNConvolutionWeightsAndBiasesState* __nonnull) exportWeightsAndBiasesWithCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
                                                                    resultStateCanBeTemporary: (BOOL) resultStateCanBeTemporary
                                                                     MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3));

@end    /* MPSCNNConvolution */
    
/*! @enum       MPSCNNConvolutionGradientOption
 *  @memberof   MPSCNNConvolutionGradient
 *  @abstract   Options used to control which gradient to compute
 */
#if defined(DOXYGEN)
    typedef enum MPSCNNConvolutionGradientOption
#else
    typedef NS_OPTIONS(NSUInteger, MPSCNNConvolutionGradientOption)
#endif
{
    // Only compute gradient with respect to data
    MPSCNNConvolutionGradientOptionGradientWithData              MPS_ENUM_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3)) MPS_SWIFT_NAME(gradientWithData)           = 1U,
    
    // Only compute gradient with respect to weights and bias
    MPSCNNConvolutionGradientOptionGradientWithWeightsAndBias    MPS_ENUM_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3)) MPS_SWIFT_NAME(gradientWithWeightsAndBias) = 2U,
    
    // Compute both gradients
    MPSCNNConvolutionGradientOptionAll                           MPS_ENUM_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3)) MPS_SWIFT_NAME(gradientWithWeightsAndBias) = MPSCNNConvolutionGradientOptionGradientWithData | MPSCNNConvolutionGradientOptionGradientWithWeightsAndBias
};
    
/*!
 *  @class      MPSCNNConvolutionGradient
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSCNNConvolutionGradient implementents backward propagation of gradient i.e. it computes the gradient of loss function
 *              with respect input data of corresonding forward convolution and gradient of loss function with respect to weights and bias
 *              of corresponding convolution in forward pass.
 *
 *              Gradient with respect to data
 *              ==============================
 *              Gradient with respect to input data of corresponding forward convolution will be written in destination image passed to
 *              encode call of MPSCNNConvolutionGradient.
 *              This step is similar to convolution transpose in that the strided convolution in forward pass become zero filled convolution in
 *              backward propagation of gradients. The difference between MPSCNNConvolutionTranspose and gradient wrt data is how the
 *              weights, that are provided by data source, are interpreted. MPSCNNConvolution and MPSCNNConvolutionTranspose interpret weights
 *              provided by data source as
 *                                          weights[outputFeatureChannels][kernelWidth][kernelHeight][inputFeatureChannels]
 *              whereas convoution gradient with respect to data interpret the weights as
 *                                          weights[inputFeatureChannels][kernelWidth][kernelHeight][outputFeatureChannels]
 *              i.e. weights are transposed in inputFeatureChannels/outputFeatureChannels dimension and also rotated 180 degress in spatial dimension
 *
 *              User should use the same data source provider to initialize MPSCNNConvolutionGradient as is used to initialize corresponding
 *              forward MPSCNNConvolution. Implementation will do the transposition/shuffling needed.
 *              Thus, while the forward MPSCNNConvolution takes sourceImage of inputFeatureChannels and convolves it with
 *              Wt[outputFeatureChannels][kernelHeight][kernelWidth][inputFeatureChannels] to produce destinationImage of outputFeatureChannels,
 *              MPSConvolutionGradient takes sourceGradient of outputFeatureChannels which is out of previous layer (nomally neuron backward layer),
 *              convolves it with transposed and rotated weights and produces destinationGradient of inputFeatureChannels.
 *              If the user decide to double buffer data source provider i.e. different data source providers are passed to forward MPSCNNConvolution object and
 *              corresponding MPSCNNConvolutionGradient object, it is user responsibility to make sure both data source providers provide same weights/bias data
 *              and have same properties in convolution descriptor else behavior is undefined.
 *
 *              Gradient with respect to weights and bias
 *              =========================================
 *              Gradient with respect to weights and bias are returned in MPSCNNConvolutionGradientState object to be used in weights update functions.
 *              If I denotes the input image to corresponding MPSCNNConvolution in forward pass and E denoates the loss gradient from previous layer
 *              (normally neuron backward layer) in backward pass, gradient of E with respect to weights is
 *
 *              delta_E/delta_Wkpqc = sum_i sum_j [ E(i - primaryOffset.x,j - primaryOffset.y, k) * I( secondaryStrideInPixelX*i + secondaryOffset.x - secondaryDilationRateX*secondaryKernelWidth/2 + secondaryDilationRateX*p,
 *                                                                                                     secondaryStrideinPixelY*i + secondaryOffset.y - secondaryDilationRateY*secondaryKernelHeight/2 + secondaryDilationRateY*q, c) ]
 *
 *              where i goes over 0..W-1 and j goes over 0..H-1, (W,H) being width and height of E.
 *              p in [0, secondaryKernelWidth-1]
 *              q in [0, secondaryKernelHeight-1]
 *              c in [0, inputeFeatureChannels/groups - 1]
 *              k in [0, outputFeatureChannels]
 *
 *              and gradient with respect to bias
 *
 *              delta_E/delta_bk = sum_i sum_j [ E(i - primaryOffset.x,j - primaryOffset.y, k) ]
 *
 *              These gradients with respect to weights and bias are returned as buffers in MPSCNNConvolutionGradientState object passed in the encode call.
 *              These are consumed by MPSCNNConvolution object's -updateWeightsAndBias:MPSCNNConvolutionGradientState* method for CPU side update and
 *              encodeWeightsAndBiasUpdate:commandBuffer:MPSCNNConvolutionGradientState* method of MPSCNNConvolution object for GPU side update.
 *              UPdated weights and biases are computed as
 *
 *                         Wkpqc_new = Wkpqc_old + delta_E/delta_Wkpqc
 *                         bk_new = bk_old + delta_E/delta_bk
 *
 *              Note that MPSCNNConvolutionGradientState objects's buffers that contain gradients, for CPU side update, will only contain
 *              valid data after command buffer is complete so
 *              its only makes sense to call -updateWeightsAndBias method on MPSCNNConvolution objects after command bufer is
 *              complete. One can achieve this by enqueueing a command buffer completion handler block that make this call.
 *              Since MPSCNNConvolutionGradientState is used across command buffers i.e. its created in forward pass, consumed by  MPSCNNConvolutionGradient in backward pass in same command buffer and passed onto MPSCNNConvolution updateWeightsAndBias method
 *              after completion of command buffer, it cannot be a temporary state.
 *
 *              In order to gaurantee consistency between forward pass (MPSCNNConvolution) and weights gradient computation in this filter, certain requirements
 *              must be met.
 *              1) Dimensions of loss gradient E from previous layer in backward pass must be equal to clipRect.size of corresponding MPSCNNConvolution in forward pass.
 *                 This is to gaurantee that only those pixels for which weights/bias contributed in destination of forward pass end up contributing to weights/bias gradient update.
 *                 If the dimension of loss gradient E from previous layer is not equal to clipRect.size of corresponding forward MPSCNNConvolution,
 *                    i) one can insert a slice operation to extract out the region of size clipRect.size from appropriate offset in E and set primaryOffset = 0 Or
 *                   ii) set primatryOffset to offset in E at which valid data starts and make sure data outside is zeroed.
 *              2) secondaryOffset should be set to what offset property of MPSCNNConvolution was set to in forward pass.
 *
 *              Currently back propagation for gradients is only supported for regualar convolution and depthwise convolution. Back propagation
 *              sub-pixel convolution are not supported. So channelMultiplier and subPixelScaleFactor must be one.
*/
MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSCNNConvolutionGradient : MPSCNNGradientKernel

/*! @property   sourceGradientFeatureChannels
 *  @abstract   The number of feature channels per pixel in the gradient image (primarySource) of encode call. This is same is outputFeatureChannels
 *              or the feature channels of destination image in forward convolution i.e. dataSource.descriptor.outputFeatureChannels
 */
@property(readonly, nonatomic) NSUInteger       sourceGradientFeatureChannels;

/*! @property   sourceImageFeatureChannels
 *  @abstract   The number of feature channels per pixel in the input image to forward convolution which is used here as secondarySource.
 *              This is same as dataSource.descriptor.inputFeatureChannels. This is also the number of feature channels in destinatin image
 *              here i.e. gradient with respect to data.
 */
@property(readonly, nonatomic) NSUInteger       sourceImageFeatureChannels;

/*! @property   groups
 *  @abstract   Number of groups input and output channels are divided into.
 */
@property(readonly, nonatomic) NSUInteger      groups;

/*! @abstract   Channel multiplier.
 *  @discussion For convolution created with MPSCNNDepthWiseConvolutionDescriptor, it is the number of
 *              output feature channels for each input channel. See MPSCNNDepthWiseConvolutionDescriptor for more details.
 *              Default is 0 which means regular CNN convolution. Currently only channelMultiplier of 1 is supported i.e. inputChannels == outputChannels
 */
@property   (readonly, nonatomic) NSUInteger           channelMultiplier;

/*! @property   dataSource
 *  @abstract   dataSource with which gradient object was created
 */
@property(readonly, nonatomic, retain, nonnull) id<MPSCNNConvolutionDataSource>      dataSource;


/*! @property   gradientOption
 *  @abstract   Option to control which gradient to compute. Default is MPSCNNConvolutionGradientOptionAll
 *              which means both gradient with respect to data and gradient with respect to weight and bias are computed.
 */
@property(readwrite, nonatomic) MPSCNNConvolutionGradientOption      gradientOption;

/*! @abstract    Property to control serialization of weights and bias.
 *  @discussion  During serialization of convolution object in -encodeWithCoder call, weights and biases are saved so that convolution
 *               object can be properly unserialized/restored in -initWithCoder call. If data source provied is NSSecureCoding compliant,
 *               data source is serialized else weights and biases are serialized.
 *               As weights/biases data may be several MB and these are same for both gradient and forward convolution object,
 *               application may already have weights/biases on disk through convolution, it can
 *               save disk space by setting this property false so convolution gradient object does not end up storing another copy of weights/biases.
 *               Default is NO. When application decides to set it to NO, it MUST call
 *                              -(void) reloadWeightsAndBiasesFromDataSource
 *               after initWithCoder has initialized convolution object.
 */
@property   (readwrite, nonatomic) BOOL serializeWeightsAndBiases
                            MPS_AVAILABLE_STARTING_BUT_DEPRECATED( "This is deprecated and doesn't do anything. It is here for backward compatibility. MPSCNNConvolutionGradient doesn't serialize weights. It gets weight from state.convolution.dataSource on first use i.e. first encodeToCommandBuffer call",
                                      macos(10.13.4, 10.14), ios(11.3, 12.0), tvos(11.3, 12.0) );

/*!
 *  @abstract   Initializes a convolution gradient (with respect to weights and bias) object.
 *  @param      device                          The MTLDevice on which this MPSCNNConvolutionGradient filter will be used
 *  @param      weights                         A pointer to a object that conforms to the MPSCNNConvolutionDataSource
 *                                              protocol. Note that same data source as provided to forward convolution should be used.
 *
 *  @return     A valid MPSCNNConvolutionGradient object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                               weights: (nonnull id <MPSCNNConvolutionDataSource>) weights NS_DESIGNATED_INITIALIZER;

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
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*
 * Use initWithDevice:weights instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*! @abstract   CPU side reload. Reload the updated weights and biases from data provider into internal weights and bias buffers. Weights and biases
 *              gradients needed for update are obtained from MPSCNNConvolutionGradientState object. Data provider passed in init call is used for this purpose.
 */
-(void) reloadWeightsAndBiasesFromDataSource;

/*! @abstract   GPU side reload. Reload the updated weights and biases from update buffer produced by application enqueued metal kernel into internal weights
 *              and biases buffer. Weights and biases gradients needed for update are obtained from MPSCNNConvolutionGradientState object's gradientForWeights and gradientForBiases metal buffer.
 *
 *  @param      commandBuffer      Metal command buffer on which application update kernel was enqueued consuming MPSCNNConvolutionGradientState's gradientForWeights and gradientForBiases buffer
 *                                 and producing updateBuffer metal buffer.
 *  @param      state              MPSCNNConvolutionWeightsAndBiasesState containing weights and biases buffers which have updated weights produced by application's update kernel.
 *
 */
-(void) reloadWeightsAndBiasesWithCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
                                          state: (MPSCNNConvolutionWeightsAndBiasesState* __nonnull) state
                                                MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3));

@end    /* MPSCNNConvolutionGradient */

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

/*!
 *  @abstract   Initializes a convolution kernel
 *              WARNING:                        This API is depreated and will be removed in the future. It cannot be used
 *                                              when training. Also serialization/unserialization wont work for MPSCNNConvolution
 *                                              objects created with this init. Please move onto using initWithDevice:weights:.
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
    
/*!
 *  @class      MPSCNNFullyConnectedGradient
 *  @dependency This depends on Metal.framework
 *  @discussion Compute the gradient for fully connected layer.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3))
@interface  MPSCNNFullyConnectedGradient : MPSCNNConvolutionGradient

/*!
 *  @abstract   Initializes a convolution gradient (with respect to weights and bias) object.
 *  @param      device                          The MTLDevice on which this MPSCNNConvolutionGradient filter will be used
 *  @param      weights                         A pointer to a object that conforms to the MPSCNNConvolutionDataSource
 *                                              protocol. Note that same data source as provided to forward convolution should be used.
 *
 *  @return     A valid MPSCNNConvolutionGradient object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                               weights: (nonnull id <MPSCNNConvolutionDataSource>) weights NS_DESIGNATED_INITIALIZER;

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
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*
 * Use initWithDevice:weights instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*
 *  call base class (MPSCNNConvolutionGradient) reload methods for reloading weights/biases during training
 */

@end    /* MPSCNNConvolutionGradient */
    
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

/*! @abstract    Precision of accumulator used in convolution.
 *  @discussion  See MPSNeuralNetworkTypes.h for discussion. Default is MPSNNConvolutionAccumulatorPrecisionOptionFloat.
 */
@property   (readwrite, nonatomic) MPSNNConvolutionAccumulatorPrecisionOption accumulatorPrecisionOption
                                                    MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3));

/*!
 *  @abstract   Initializes a convolution transpose kernel
 *  @param      device                          The MTLDevice on which this MPSCNNConvolutionTranspose filter will be used
 *  @param      weights                         A pointer to a object that conforms to the MPSCNNConvolutionDataSource
 *                                              protocol. The MPSCNNConvolutionDataSource protocol declares the methods that an
 *                                              instance of MPSCNNConvolutionTranspose uses to obtain the weights and bias terms
 *                                              for the CNN convolutionTranspose filter. Currently we support only Float32 weights.
 *
 *  @return     A valid MPSCNNConvolutionTranspose object.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                               weights: (nonnull id <MPSCNNConvolutionDataSource>) weights NS_DESIGNATED_INITIALIZER;

/*
 * Use initWithDevice:convolutionDescriptor:kernelWeights:biasTerms instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*! @abstract <NSSecureCoding> support */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

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
 *  @param          convolutionGradientState    A valid MPSCNNConvolutionGradientState from the MPSCNNConvoluton counterpart to this MPSCNNConvolutionTranspose.
 *                                      If there is no forward convolution counterpart, pass NULL here. This state affects the sizing
 *                                      the result.
 *  @result         A MPSImage or MPSTemporaryImage allocated per the destinationImageAllocator containing the output of the graph.
 *                  The offset property will be adjusted to reflect the offset used during the encode.
 *                  The returned image will be automatically released when the command buffer completes. If you want to
 *                  keep it around for longer, retain the image. (ARC will do this for you if you use it later.)
 */
-(MPSImage * __nonnull) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                  sourceImage: (MPSImage *  __nonnull) sourceImage
                     convolutionGradientState: (MPSCNNConvolutionGradientState * __nullable) convolutionGradientState
                        MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3))
                        MPS_SWIFT_NAME( encode(commandBuffer:sourceImage:convolutionGradientState:));

-(MPSImageBatch * __nonnull) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                           sourceImages: (MPSImageBatch *  __nonnull) sourceImage
                              convolutionGradientStates: (MPSCNNConvolutionGradientStateBatch * __nullable) convolutionGradientState
                        MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3))
                        MPS_SWIFT_NAME( encodeBatch(commandBuffer:sourceImages:convolutionGradientStates:));

-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                  sourceImage: (MPSImage *  __nonnull) sourceImage
     convolutionGradientState: (MPSCNNConvolutionGradientState * __nullable) convolutionGradientState
             destinationImage: (MPSImage * __nonnull) destinationImage
                        MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
                        MPS_SWIFT_NAME(encode(commandBuffer:sourceImage:convolutionGradientState:destinationImage:));

-(void) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                      sourceImages: (MPSImageBatch *  __nonnull) sourceImage
         convolutionGradientStates: (MPSCNNConvolutionGradientStateBatch * __nullable) convolutionGradientState
                 destinationImages: (MPSImageBatch * __nonnull) destinationImage
                        MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
                        MPS_SWIFT_NAME(encodeBatch(commandBuffer:sourceImages:convolutionGradientStates:destinationImages:));


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
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;


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
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;


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
