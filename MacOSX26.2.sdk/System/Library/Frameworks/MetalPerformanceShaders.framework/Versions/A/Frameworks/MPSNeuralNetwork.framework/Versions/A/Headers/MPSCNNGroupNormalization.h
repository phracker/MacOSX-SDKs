/*!
 *  @header MPSCNNGroupNormalization.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2018 Apple Inc. All rights reserved.
 *  @abstract MPSKernels to do group normalization and training
 */

#ifndef MPSCNNGroupNormalization_h
#define MPSCNNGroupNormalization_h

#include <MPSNeuralNetwork/MPSCNNKernel.h>
#include <MPSNeuralNetwork/MPSCNNNormalizationWeights.h>

#ifdef __cplusplus
extern "C" {
#endif
    
@class MPSCNNGroupNormalization;

/*!
 *  @class      MPSCNNGroupNormalizationGradientState
 *  @dependency This depends on Metal.framework
 *  @discussion A state to hold information necessary to execute a gradient
 *              pass for MPSCNNGroupNormalization.  Gradient states should
 *              be created by using the forward kernel's methods.  This will
 *              ensure that the state captures all information necessary to
 *              execute the corresponding gradient pass.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSCNNGroupNormalizationGradientState : MPSNNGradientState

/*! @abstract The MPSCNNGroupNormalization object that created this state object. */
@property (readonly, nonatomic, nonnull, retain) MPSCNNGroupNormalization * groupNormalization;

/*!
 *  @abstract   Return an MTLBuffer object with the state's current gamma values.
 */
@property (readonly, nonatomic) __nullable id<MTLBuffer> gamma;

/*!
 *  @abstract   Return an MTLBuffer object with the state's current beta values..
 */
@property (readonly, nonatomic) __nullable id<MTLBuffer> beta;

/*!
 *  @property   The MTLBuffer containing the gradient values for gamma.
 */
@property (readonly, nonatomic) __nonnull id<MTLBuffer> gradientForGamma;

/*!
 *  @property   The MTLBuffer containing the gradient values for beta.
 */
@property (readonly, nonatomic) __nonnull id<MTLBuffer> gradientForBeta;

/*!
 *  Unavailable.  Use MPSCNNGroupNormalization state creation methods.
 */
+(nonnull instancetype) temporaryStateWithCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                                      textureDescriptor: (MTLTextureDescriptor * __nonnull) descriptor NS_UNAVAILABLE;

+(nonnull instancetype) temporaryStateWithCommandBuffer:(__nonnull id<MTLCommandBuffer>)cmdBuf NS_UNAVAILABLE;
+(nonnull instancetype) temporaryStateWithCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                                             bufferSize: (size_t) bufferSize NS_UNAVAILABLE;

/*!
 *  Unavailable.  Use MPSCNNGroupNormalization state creation methods.
 */
-(nonnull instancetype) initWithDevice: (__nonnull id <MTLDevice>) device
                     textureDescriptor: (MTLTextureDescriptor * __nonnull) descriptor NS_UNAVAILABLE;

/*!
 *  Unavailable.  Use MPSCNNGroupNormalization state creation methods.
 */
-(nonnull instancetype) initWithResource: (__nullable id <MTLResource>) resource NS_UNAVAILABLE;

-(nonnull instancetype) initWithDevice: (__nonnull id <MTLDevice>) device
                            bufferSize: (size_t) bufferSize NS_UNAVAILABLE;

@end    /* MPSCNNGroupNormalizationGradientState */

typedef NSArray<MPSCNNGroupNormalizationGradientState*>  MPSCNNGroupNormalizationGradientStateBatch
MPS_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0));

/*! @protocol   MPSCNNGroupNormalizationDataSource
 *  @abstract   The MPSCNNGroupNormalizationDataSource protocol declares the methods that an
 *              group of MPSCNNGroupNormalization uses to initialize the
 *              scale factors (gamma) and bias terms (beta).
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@protocol MPSCNNGroupNormalizationDataSource <NSObject, NSCopying>

@required
/*!
 *  @abstract   Return a pointer to an array containing the gamma terms.
 *  @discussion Must have numberOfFeatureChannels values since scaling is done per feature channel.
 */
-(float* __nullable) gamma;

/*!
 *  @abstract   Return a pointer to an array containing the beta terms.
 *  @discussion Must have numberOfFeatureChannels values since scaling is done per feature channel.
 */
-(float* __nullable) beta;

/*!
 *  @property   The number of feature channels that are normalized.
 */
@property (readonly, nonatomic) NSUInteger numberOfFeatureChannels;
    
/*! @property   The number of groups used.
 *  @discussion numberOfFeatureChannels/numberOfGroups channels are normalized together.
 */
@property (readwrite, nonatomic) NSUInteger numberOfGroups;

/*! @abstract   A label that is transferred to the group normalization filter at init time
 *  @discussion Overridden by a MPSCNNGroupNormalizationNode.label if it is non-nil.
 */
-(NSString* __nullable) label;

@optional

/*! @abstract       Compute new gamma and beta values using current values and gradients contained within a
 *                  MPSCNNGroupNormalizationStateBatch.
 *  @discussion     This is for use in the context of training a network within a MPSNNGraph. If you are
 *                  writing your own graph using the low level interface or aren't training group normalization
 *                  it isn't needed.
 *
 *                  In this mathod, you should perform the update on a GPU, because at the time it is called
 *                  the data isn't in the state objects yet and the CPU can't do the work. You should not attempt
 *                  to update the MPSCNNGroupNormalization kernel directly with the results. The state object
 *                  returned from the function will be used for that.  A batch of states will be passed in.
 *                  You should accumulate the gradients and then update the weights.
 *
 *                  This operation is expected to also decrement the read count of groupNormalizationStateBatch by 1,
 *                  if the states are temporary.
 *
 *  @param          commandBuffer                   The command buffer on which to encode the update.
 *
 *  @param          groupNormalizationStateBatch A batch of MPSCNNGroupNormalizationGradientState objects containing
 *                                                  current weights and gradients.
 *
 *  @return         A MPSCNNNormalizationGammaAndBetaState object containing updated gamma and beta values.  If NULL no
 *                  update was performed.
 */
-(MPSCNNNormalizationGammaAndBetaState * __nullable)
    updateGammaAndBetaWithCommandBuffer: (nonnull id<MTLCommandBuffer>) commandBuffer
           groupNormalizationStateBatch: (MPSCNNGroupNormalizationGradientStateBatch* __nonnull) groupNormalizationStateBatch;
/*! @abstract       Compute new gamma and beta values using current values and gradients contained within a
 *                  batch MPSCNNGroupNormalizationState objects.  Perform the update on the CPU.
 *
 *  @param          groupNormalizationStateBatch A batch of MPSCNNGroupNormalizationGradientState objects containing
 *                                                  current gamma and beta values and gradients.
 *
 *  @return         A boolean value indicating if the update was performed.
 */
-(BOOL) updateGammaAndBetaWithGroupNormalizationStateBatch: (MPSCNNGroupNormalizationGradientStateBatch* __nonnull) groupNormalizationStateBatch;

/*! @abstract       An optional tiny number to use to maintain numerical stability.
 *  @discussion     output_image = (input_image - mean[c]) * gamma[c] / sqrt(variance[c] + epsilon) + beta[c];
 *                  Defalt value if method unavailable: FLT_MIN   */
-(float) epsilon;

/*!
 *  Optional NSSecureCoding compatibility.
 */
- (void)encodeWithCoder:(NSCoder * __nonnull)aCoder;

- (nullable instancetype)initWithCoder:(NSCoder * __nonnull)aDecoder; // NS_DESIGNATED_INITIALIZER

@property (class, readonly) BOOL supportsSecureCoding;

/*!
 *  @abstract   Optional copy method to create a copy of the data source for use with a new device.
 *
 *  @param      zone    The NSZone on which to allocate.
 *  @param      device  The device where the kernel which uses this data source will be used.
 *
 *  @result     A pointer to a copy of this data source.
 */
- (nonnull instancetype) copyWithZone:(nullable NSZone *)zone
device:(nullable id <MTLDevice>) device;
@end    // MPSCNNGroupNormalizationDataSource

/*!
 *  @class      MPSCNNGroupNormalization
 *  @dependency This depends on Metal.framework
 *  @discussion This kernel normalizes each image, on a per-group basis, to
 *              have zero mean and unit variance:
 *
 *              for each image:
 *                  for each channel:
 *                      y = (x - mean) * gamma / sqrt(variance + epsilon) + beta;
 *
 *              The mean and variance are computed per group of channels, as given by the dataSource.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSCNNGroupNormalization : MPSCNNKernel
/*! @property  epsilon
*  @abstract   The epsilon value used to bias the variance when normalizing.
*/
@property(readwrite, nonatomic) float       epsilon;

/*! @abstract   The data source that the object was initialized with */
@property (readonly, nonatomic, nonnull, retain) id <MPSCNNGroupNormalizationDataSource> dataSource;

/*!
*  @abstract   Initialize a MPSCNNGroupNormalization kernel on a device.
*  @param      dataSource  An object conforming to the MPSCNNGroupNormalizationDataSource
*                          protocol which
*/
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        dataSource: (nonnull id<MPSCNNGroupNormalizationDataSource>) dataSource NS_DESIGNATED_INITIALIZER;

/*!
* Use initWithDevice:dataSource instead
*/
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*! @abstract NSSecureCoding compatability
*  @discussion While the standard NSSecureCoding/NSCoding method
*              -initWithCoder: should work, since the file can't
*              know which device your data is allocated on, we
*              have to guess and may guess incorrectly.  To avoid
*              that problem, use initWithCoder:device instead.
*  @param      aDecoder    The NSCoder subclass with your serialized MPSKernel
*  @param      device      The MTLDevice on which to make the MPSKernel
*  @return     A new MPSCNNGroupNormalization object, or nil if failure.
*/
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                            device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*!
*  @abstract   Reinitialize the filter using the data source provided at kernel initialization.
*/
-(void) reloadGammaAndBetaFromDataSource;

/*!
*  @abstract   Reload data using new gamma and beta terms contained within an
*              MPSCNNGroupNormalizationGradientState object.
*
*  @param      commandBuffer               The command buffer on which to encode the reload.
*
*  @param      gammaAndBetaState           The state containing the updated weights which are to
*                                          be reloaded.
*/
-(void) reloadGammaAndBetaWithCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
                      gammaAndBetaState: (MPSCNNNormalizationGammaAndBetaState* __nonnull) gammaAndBetaState;

/*!
*  @abstract   Return a MPSCNNGroupNormalizationGradientState object for the provided
*              source image, source states, and destination image.
*/
-(MPSCNNGroupNormalizationGradientState * __nullable) resultStateForSourceImage: (MPSImage *__nonnull) sourceImage
                                                                  sourceStates: (NSArray <MPSState *> *__nullable) sourceStates
                                                              destinationImage: (MPSImage * __nonnull) destinationImage;

/*! @abstract       Return a temporary MPSCNNGroupNormalizationGradientState object which may be used with
*                  a MPSCNNGroupNormalization filter.
*/
-(MPSCNNGroupNormalizationGradientState * __nullable) temporaryResultStateForCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                                                              sourceImage: (MPSImage *__nonnull) sourceImage
                                                                             sourceStates: (NSArray <MPSState *> *__nullable) sourceStates
                                                                         destinationImage: (MPSImage *__nonnull) destinationImage;
@end    /* MPSCNNGroupNormalization */

/*!
 *  @class      MPSCNNGroupNormalizationGradient
 *  @dependency This depends on Metal.framework
 *  @discussion This kernel executes a gradient pass corresponding to MPSCNNGroupNormalization.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSCNNGroupNormalizationGradient : MPSCNNGradientKernel

@end    /* MPSCNNGroupNormalizationGradient */
#ifdef __cplusplus
}
#endif


#endif /* MPSCNNGroupNormalization_h */
