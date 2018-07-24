
/*!
 *  @header MPSCNNInstanceNormalization.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2018 Apple Inc. All rights reserved.
 *  @abstract MPSKernels to do instance normalization and training
 */

#ifndef MPSCNNInstanceNormalization_h
#define MPSCNNInstanceNormalization_h

#include <MPSNeuralNetwork/MPSCNNKernel.h>
#include <MPSNeuralNetwork/MPSCNNNormalizationWeights.h>

#ifdef __cplusplus
extern "C" {
#endif
   
@class MPSCNNInstanceNormalization;

/*!
 *  @class      MPSCNNInstanceNormalizationGradientState
 *  @dependency This depends on Metal.framework
 *  @discussion A state to hold information necessary to execute a gradient
 *              pass for MPSCNNInstanceNormalization.  Gradient states should
 *              be created by using the forward kernel's methods.  This will
 *              ensure that the state captures all information necessary to
 *              execute the corresponding gradient pass.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@interface MPSCNNInstanceNormalizationGradientState : MPSNNGradientState

/*! @abstract The MPSCNNInstanceNormalization object that created this state object. */
@property (readonly, nonatomic, nonnull, retain) MPSCNNInstanceNormalization * instanceNormalization;

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
 *  Unavailable.  Use MPSCNNInstanceNormalization state creation methods.
 */
+(nonnull instancetype) temporaryStateWithCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                                      textureDescriptor: (MTLTextureDescriptor * __nonnull) descriptor NS_UNAVAILABLE;

+(nonnull instancetype) temporaryStateWithCommandBuffer:(__nonnull id<MTLCommandBuffer>)cmdBuf NS_UNAVAILABLE;
+(nonnull instancetype) temporaryStateWithCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                                             bufferSize: (size_t) bufferSize NS_UNAVAILABLE;

/*!
 *  Unavailable.  Use MPSCNNInstanceNormalization state creation methods.
 */
-(nonnull instancetype) initWithDevice: (__nonnull id <MTLDevice>) device
                     textureDescriptor: (MTLTextureDescriptor * __nonnull) descriptor NS_UNAVAILABLE;

/*!
 *  Unavailable.  Use MPSCNNInstanceNormalization state creation methods.
 */
-(nonnull instancetype) initWithResource: (__nullable id <MTLResource>) resource NS_UNAVAILABLE;

-(nonnull instancetype) initWithDevice: (__nonnull id <MTLDevice>) device
                            bufferSize: (size_t) bufferSize NS_UNAVAILABLE;

@end    /* MPSCNNInstanceNormalizationGradientState */
    
typedef NSArray<MPSCNNInstanceNormalizationGradientState*>  MPSCNNInstanceNormalizationGradientStateBatch
    MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3));
    
/*! @protocol   MPSCNNInstanceNormalizationDataSource
 *  @abstract   The MPSCNNInstanceNormalizationDataSource protocol declares the methods that an
 *              instance of MPSCNNInstanceNormalization uses to initialize the
 *              scale factors (gamma) and bias terms (beta).
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))
@protocol MPSCNNInstanceNormalizationDataSource <NSObject, NSCopying>

@required
    /*!
     *  @abstract   Return a pointer to an array containing the gamma terms.
     */
    -(float* __nullable) gamma;
    
    /*!
     *  @abstract   Return a pointer to an array containing the beta terms.
     */
    -(float* __nullable) beta;
    
    /*!
     *  @property   The number of feature channels over which to normalize.
     */
    @property (readonly, nonatomic) NSUInteger numberOfFeatureChannels;
    
    /*! @abstract   A label that is transferred to the instance normalization filter at init time
     *  @discussion Overridden by a MPSCNNInstanceNormalizationNode.label if it is non-nil.
     */
    -(NSString* __nullable) label;
    
@optional
    
    /*! @abstract       Compute new gamma and beta values using current values and gradients contained within a
     *                  MPSCNNInstanceNormalizationStateBatch.
     *  @discussion     This is for use in the context of training a network within a MPSNNGraph. If you are
     *                  writing your own graph using the low level interface or aren't training instance normalization
     *                  it isn't needed.
     *
     *                  In this mathod, you should perform the update on a GPU, because at the time it is called
     *                  the data isn't in the state objects yet and the CPU can't do the work. You should not attempt
     *                  to update the MPSCNNInstanceNormalization kernel directly with the results. The state object
     *                  returned from the function will be used for that.  A batch of states will be passed in.
     *                  You should accumulate the gradients and then update the weights.
     *
     *                  This operation is expected to also decrement the read count of instanceNormalizationStateBatch by 1,
     *                  if the states are temporary.
     *
     *  @param          commandBuffer                   The command buffer on which to encode the update.
     *
     *  @param          instanceNormalizationStateBatch A batch of MPSCNNInstanceNormalizationGradientState objects containing
     *                                                  current weights and gradients.
     *
     *  @return         A MPSCNNNormalizationGammaAndBetaState object containing updated gamma and beta values.  If NULL no
     *                  update was performed.
     */
    -(MPSCNNNormalizationGammaAndBetaState * __nullable) updateGammaAndBetaWithCommandBuffer: (nonnull id<MTLCommandBuffer>) commandBuffer
                                                             instanceNormalizationStateBatch: (MPSCNNInstanceNormalizationGradientStateBatch* __nonnull) instanceNormalizationStateBatch;
    /*! @abstract       Compute new gamma and beta values using current values and gradients contained within a
     *                  batch MPSCNNInstanceNormalizationState objects.  Perform the update on the CPU.
     *
     *  @param          instanceNormalizationStateBatch A batch of MPSCNNInstanceNormalizationGradientState objects containing
     *                                                  current gamma and beta values and gradients.
     *
     *  @return         A boolean value indicating if the update was performed.
     */
    -(BOOL) updateGammaAndBetaWithInstanceNormalizationStateBatch: (MPSCNNInstanceNormalizationGradientStateBatch* __nonnull) instanceNormalizationStateBatch;
    
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
                                   device:(nullable id <MTLDevice>) device MPS_AVAILABLE_STARTING(macos(10.14), ios(12.0), tvos(12.0));
@end    // MPSCNNInstanceNormalizationDataSource
    
/*!
 *  @class      MPSCNNInstanceNormalization
 *  @dependency This depends on Metal.framework
 *  @discussion This kernel normalizes each image, on a per-channel basis, to
 *              have zero mean and unit variance:
 *
 *              for each image:
 *                  for each channel:
 *                      y = (x - mean) * gamma / sqrt(variance + epsilon) + beta;
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3))
@interface MPSCNNInstanceNormalization : MPSCNNKernel
/*! @property   epsilon
 *  @abstract   The epsilon value used to bias the variance when normalizing.
 */
@property(readwrite, nonatomic) float       epsilon;

/*! @abstract   The data source that the object was initialized with */
@property (readonly, nonatomic, nonnull, retain) id <MPSCNNInstanceNormalizationDataSource> dataSource;

/*!
 *  @abstract   Initialize a MPSCNNInstanceNormalization kernel on a device.
 *  @param      dataSource  An object conforming to the MPSCNNInstanceNormalizationDataSource
 *                          protocol which
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                            dataSource: (nonnull id<MPSCNNInstanceNormalizationDataSource>) dataSource NS_DESIGNATED_INITIALIZER;

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
 *  @return     A new MPSCNNInstanceNormalization object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*!
 *  @abstract   Reload data using a data source.
 *
 *  @param      dataSource  The data source which will provide the gamma and beta terms
 *                          to scale and bias the normalized result respectively.
 */
-(void) reloadDataSource: (__nonnull id<MPSCNNInstanceNormalizationDataSource>) dataSource
MPS_AVAILABLE_STARTING_BUT_DEPRECATED( "Please use -reloadGammaAndBetaFromDataSource instead.",
                                      macos(10.13.4, 10.14), ios(11.3,12.0), tvos(11.3, 12.0));

/*!
 *  @abstract   Reinitialize the filter using the data source provided at kernel initialization.
 */
-(void) reloadGammaAndBetaFromDataSource MPS_AVAILABLE_STARTING(macos(10.14), ios(12.0), tvos(12.0));

/*!
 *  @abstract   Reload data using new gamma and beta terms contained within an
 *              MPSCNNInstanceNormalizationGradientState object.
 *
 *  @param      commandBuffer               The command buffer on which to encode the reload.
 *
 *  @param      gammaAndBetaState           The state containing the updated weights which are to
 *                                          be reloaded.
 */
-(void) reloadGammaAndBetaWithCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
                          gammaAndBetaState: (MPSCNNNormalizationGammaAndBetaState* __nonnull) gammaAndBetaState;

/*!
 *  @abstract   Return a MPSCNNInstanceNormalizationGradientState object for the provided
 *              source image, source states, and destination image.
 */
-(MPSCNNInstanceNormalizationGradientState * __nullable) resultStateForSourceImage: (MPSImage *__nonnull) sourceImage
                                                                      sourceStates: (NSArray <MPSState *> *__nullable) sourceStates
                                                                  destinationImage: (MPSImage * __nonnull) destinationImage;

/*! @abstract       Return a temporary MPSCNNInstanceNormalizationGradientState object which may be used with
 *                  a MPSCNNInstanceNormalization filter.
 */
-(MPSCNNInstanceNormalizationGradientState * __nullable) temporaryResultStateForCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                                                                  sourceImage: (MPSImage *__nonnull) sourceImage
                                                                                 sourceStates: (NSArray <MPSState *> *__nullable) sourceStates
                                                                             destinationImage: (MPSImage *__nonnull) destinationImage;
@end    /* MPSCNNInstanceNormalization */

/*!
 *  @class      MPSCNNInstanceNormalizationGradient
 *  @dependency This depends on Metal.framework
 *  @discussion This kernel executes a gradient pass corresponding to MPSCNNInstanceNormalization.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3))
@interface MPSCNNInstanceNormalizationGradient : MPSCNNGradientKernel

@end    /* MPSCNNInstanceNormalizationGradient */
#ifdef __cplusplus
}
#endif


#endif /* MPSCNNInstanceNormalization_h */

