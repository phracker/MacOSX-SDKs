//
//  MPSCNNKernel.h
//  MPS
//
//  Created by Ian Ollmann on 8/21/16.
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef MPSCNNKernel_h
#define MPSCNNKernel_h

#include <MPSCore/MPSKernel.h>
#include <MPSCore/MPSImage.h>
#include <MPSNeuralNetwork/MPSNeuralNetworkTypes.h>
#include <MPSNeuralNetwork/MPSNNGradientState.h>


/*!
 *  @class      MPSCNNKernel
 *  @dependency This depends on Metal.framework
 *  @abstract   Describes a convolution neural network kernel.
 *  @discussion A MPSCNNKernel consumes one MPSImage and produces one MPSImage.
 *
 *              The region overwritten in the destination MPSImage is described
 *              by the clipRect.  The top left corner of the region consumed (ignoring
 *              adjustments for filter size -- e.g. convolution filter size) is given
 *              by the offset. The size of the region consumed is a function of the
 *              clipRect size and any subsampling caused by pixel strides at work,
 *              e.g. MPSCNNPooling.strideInPixelsX/Y.  Where the offset + clipRect
 *              would cause a {x,y} pixel address not in the image to be read, the
 *              edgeMode is used to determine what value to read there.
 *
 *              The Z/depth component of the offset, clipRect.origin and clipRect.size
 *              indexes which images to use. If the MPSImage contains only a single image
 *              then these should be offset.z = 0, clipRect.origin.z = 0
 *              and clipRect.size.depth = 1. If the MPSImage contains multiple images,
 *              clipRect.size.depth refers to number of images to process. Both source
 *              and destination MPSImages must have at least this many images. offset.z
 *              refers to starting source image index. Thus offset.z + clipRect.size.depth must
 *              be <= source.numberOfImages. Similarly, clipRect.origin.z refers to starting
 *              image index in destination. So clipRect.origin.z + clipRect.size.depth must be
 *              <= destination.numberOfImage.
 *
 *              destinationFeatureChannelOffset property can be used to control where the MPSKernel will
 *              start writing in feature channel dimension. For example, if the destination image has
 *              64 channels, and MPSKernel outputs 32 channels, by default channels 0-31 of destination
 *              will be populated by MPSKernel. But if we want this MPSKernel to populate channel 32-63
 *              of the destination, we can set destinationFeatureChannelOffset = 32.
 *              A good example of this is concat (concatenation) operation in Tensor Flow. Suppose
 *              we have a src = w x h x Ni which goes through CNNConvolution_0 which produces
 *              output O0 = w x h x N0 and CNNConvolution_1 which produces output O1 = w x h x N1 followed
 *              by concatenation which produces O = w x h x (N0 + N1). We can achieve this by creating
 *              an MPSImage with dimensions O = w x h x (N0 + N1) and using this as destination of
 *              both convolutions as follows
 *                  CNNConvolution0: destinationFeatureChannelOffset = 0, this will output N0 channels starting at
 *                                   channel 0 of destination thus populating [0,N0-1] channels.
 *                  CNNConvolution1: destinationFeatureChannelOffset = N0, this will output N1 channels starting at
 *                                   channel N0 of destination thus populating [N0,N0+N1-1] channels.
 *
 *
 *              A MPSCNNKernel can be saved to disk / network using NSCoders such as NSKeyedArchiver. 
 *              When decoding, the system default MTLDevice will be chosen unless the NSCoder adopts 
 *              the <MPSDeviceProvider> protocol.  To accomplish this you will likely need to subclass your
 *              unarchiver to add this method.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), macCatalyst(13.0), tvos(10.0))
@interface MPSCNNKernel : MPSKernel

/*! @abstract   Standard init with default properties per filter type
 *  @param      device      The device that the filter will be used on. May not be NULL.
 *  @result     A pointer to the newly initialized object. This will fail, returning
 *              nil if the device is not supported. Devices must be
 *              MTLFeatureSet_iOS_GPUFamily2_v1 or later.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                NS_DESIGNATED_INITIALIZER;


/*! @property   offset
 *  @abstract   The position of the destination clip rectangle origin relative to the source buffer.
 *  @discussion The offset is defined to be the position of clipRect.origin in source coordinates.
 *              Default: {0,0,0}, indicating that the top left corners of the clipRect and source image align.
 *              offset.z is the index of starting source image in batch processing mode.
 *
 *              See Also: @ref MetalPerformanceShaders.h subsubsection_mpsoffset
 */
@property (readwrite, nonatomic) MPSOffset                offset;

/*! @property   clipRect
 *  @abstract   An optional clip rectangle to use when writing data. Only the pixels in the rectangle will be overwritten.
 *  @discussion A MTLRegion that indicates which part of the destination to overwrite. If the clipRect does not lie
 *              completely within the destination image, the intersection between clip rectangle and destination bounds is
 *              used.   Default: MPSRectNoClip (MPSKernel::MPSRectNoClip) indicating the entire image.
 *              clipRect.origin.z is the index of starting destination image in batch processing mode. clipRect.size.depth
 *              is the number of images to process in batch processing mode.
 *
 *              See Also: @ref MetalPerformanceShaders.h subsubsection_clipRect
 */
@property (readwrite, nonatomic) MTLRegion               clipRect;


/*! @property   destinationFeatureChannelOffset
 *  @abstract   The number of channels in the destination MPSImage to skip before writing output.
 *  @discussion This is the starting offset into the destination image in the feature channel dimension
 *              at which destination data is written.
 *              This allows an application to pass a subset of all the channels in MPSImage as output of MPSKernel.
 *              E.g. Suppose MPSImage has 24 channels and a MPSKernel outputs 8 channels. If
 *              we want channels 8 to 15 of this MPSImage to be used as output, we can set destinationFeatureChannelOffset = 8.
 *              Note that this offset applies independently to each image when the MPSImage
 *              is a container for multiple images and the MPSCNNKernel is processing multiple images (clipRect.size.depth > 1).
 *              The default value is 0 and any value specifed shall be a multiple of 4. If MPSKernel outputs N channels,
 *              the destination image MUST have at least destinationFeatureChannelOffset + N channels. Using a destination
 *              image with insufficient number of feature channels will result in an error.
 *              E.g. if the MPSCNNConvolution outputs 32 channels, and the destination has 64 channels, then it is an error to set
 *              destinationFeatureChannelOffset > 32.
 */
@property (readwrite, nonatomic) NSUInteger              destinationFeatureChannelOffset;

/*! @property   sourceFeatureChannelOffset
 *  @abstract   The number of channels in the source MPSImage to skip before reading the input.
 *  @discussion This is the starting offset into the source image in the feature channel dimension
 *              at which source data is read. Unit: feature channels
 *              This allows an application to read a subset of all the channels in MPSImage as input of MPSKernel.
 *              E.g. Suppose MPSImage has 24 channels and a MPSKernel needs to read 8 channels. If
 *              we want channels 8 to 15 of this MPSImage to be used as input, we can set sourceFeatureChannelOffset = 8.
 *              Note that this offset applies independently to each image when the MPSImage
 *              is a container for multiple images and the MPSCNNKernel is processing multiple images (clipRect.size.depth > 1).
 *              The default value is 0 and any value specifed shall be a multiple of 4. If MPSKernel inputs N channels,
 *              the source image MUST have at least sourceFeatureChannelOffset + N channels. Using a source
 *              image with insufficient number of feature channels will result in an error.
 *              E.g. if the MPSCNNConvolution inputs 32 channels, and the source has 64 channels, then it is an error to set
 *              sourceFeatureChannelOffset > 32.
 */
@property (readwrite, nonatomic) NSUInteger              sourceFeatureChannelOffset;

/*! @property   sourceFeatureChannelMaxCount
 *  @abstract   The maximum number of channels in the source MPSImage to use
 *  @discussion Most filters can insert a slice operation into the filter for free.
 *              Use this to limit the size of the feature channel slice taken from
 *              the input image. If the value is too large, it is truncated to be
 *              the remaining size in the image after the sourceFeatureChannelOffset
 *              is taken into account.  Default: ULONG_MAX
 */
@property (readwrite, nonatomic) NSUInteger              sourceFeatureChannelMaxCount;

/*! @property   edgeMode
 *  @abstract   The MPSImageEdgeMode to use when texture reads stray off the edge of an image
 *  @discussion Most MPSKernel objects can read off the edge of the source image. This can happen
 *              because of a negative offset property, because the offset + clipRect.size is larger
 *              than the source image or because the filter looks at neighboring pixels, such as a
 *              Convolution filter.   Default:  MPSImageEdgeModeZero.
 *
 *              See Also: @ref MetalPerformanceShaders.h subsubsection_edgemode
 *              Note: For @ref MPSCNNPoolingAverage specifying edge mode @ref MPSImageEdgeModeClamp
 *                      is interpreted as a "shrink-to-edge" operation, which shrinks the effective
 *                      filtering window to remain within the source image borders.
 */
@property (readwrite, nonatomic) MPSImageEdgeMode        edgeMode;


/*! @property   kernelWidth
 *  @abstract   The width of the MPSCNNKernel filter window
 *  @discussion This is the horizontal diameter of the region read by the filter for each
 *              result pixel. If the MPSCNNKernel does not have a filter window, then
 *              1 will be returned.
 *
 *              Warning: This property was lowered to this class in ios/tvos 11
 *                       The property may not be available on iOS/tvOS 10 for
 *                       all subclasses of MPSCNNKernel
 */
@property (readonly, nonatomic) NSUInteger              kernelWidth;

/*! @property   kernelHeight
 *  @abstract   The height of the MPSCNNKernel filter window
 *  @discussion This is the vertical diameter of the region read by the filter for each
 *              result pixel. If the MPSCNNKernel does not have a filter window, then 
 *              1 will be returned.
 *
 *              Warning: This property was lowered to this class in ios/tvos 11
 *                       The property may not be available on iOS/tvOS 10 for
 *                       all subclasses of MPSCNNKernel
 */
@property (readonly, nonatomic) NSUInteger              kernelHeight;

/*! @property   strideInPixelsX
 *  @abstract   The downsampling (or upsampling if a backwards filter) factor in the horizontal dimension
 *  @discussion If the filter does not do up or downsampling, 1 is returned.
 *
 *              Warning: This property was lowered to this class in ios/tvos 11
 *                       The property may not be available on iOS/tvOS 10 for
 *                       all subclasses of MPSCNNKernel
 */
@property(readonly, nonatomic) NSUInteger               strideInPixelsX;

/*! @property   strideInPixelsY
 *  @abstract   The downsampling (or upsampling if a backwards filter) factor in the vertical dimension
 *  @discussion If the filter does not do up or downsampling, 1 is returned.
 *
 *              Warning: This property was lowered to this class in ios/tvos 11
 *                       The property may not be available on iOS/tvOS 10 for
 *                       all subclasses of MPSCNNKernel
 */
@property(readonly, nonatomic) NSUInteger               strideInPixelsY;

/*! @property   dilationRateX
 *  @abstract   Stride in source coordinates from one kernel tap to the next in the X dimension.
 */
@property(readonly, nonatomic) NSUInteger               dilationRateX;

/*! @property   dilationRate
 *  @abstract   Stride in source coordinates from one kernel tap to the next in the Y dimension.
 */
@property(readonly, nonatomic) NSUInteger               dilationRateY;


/*! @property   isBackwards
 *  @abstract   YES if the filter operates backwards.
 *  @discussion This influences how strideInPixelsX/Y should be interpreted. 
 *              Most filters either have stride 1 or are reducing, meaning that
 *              the result image is smaller than the original by roughly a factor
 *              of the stride.  A few "backward" filters (e.g convolution transpose) are intended
 *              to "undo" the effects of an earlier forward filter, and so 
 *              enlarge the image. The stride is in the destination coordinate frame
 *              rather than the source coordinate frame.
 */
@property(readonly, nonatomic) BOOL                     isBackwards
                    MPS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0));

/*! @abstract   Returns true if the -encode call modifies the state object it accepts.  */
@property (readonly, nonatomic) BOOL                    isStateModified
                    MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @property   padding
 *  @abstract   The padding method used by the filter
 *  @discussion This influences how the destination image is sized and how
 *              the offset into the source image is set.  It is used by the
 *              -encode methods that return a MPSImage from the left hand side.
 */
@property (readwrite, nonatomic, nonnull, retain) id <MPSNNPadding>    padding
                    MPS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0));

/*! @abstract   Method to allocate the result image for -encodeToCommandBuffer:sourceImage:
 *  @discussion Default: MPSTemporaryImage.defaultAllocator
 */
@property (readwrite, nonatomic, retain, nonnull) id <MPSImageAllocator> destinationImageAllocator
                    MPS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0));



/*! @abstract NSSecureCoding compatability
 *  @discussion While the standard NSSecureCoding/NSCoding method
 *              -initWithCoder: should work, since the file can't
 *              know which device your data is allocated on, we
 *              have to guess and may guess incorrectly.  To avoid
 *              that problem, use initWithCoder:device instead.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSKernel
 *  @param      device      The MTLDevice on which to make the MPSKernel
 *  @return     A new MPSKernel object, or nil if failure. */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER
                            MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0));


/*! @abstract   Encode a MPSCNNKernel into a command Buffer.  The operation shall proceed out-of-place.
 *  @discussion This is the older style of encode which reads the offset, doesn't change it,
 *              and ignores the padding method.
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *  @param      sourceImage         A valid MPSImage object containing the source image.
 *  @param      destinationImage    A valid MPSImage to be overwritten by result image. destinationImage may not alias sourceImage.
*/
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                  sourceImage: (MPSImage * __nonnull) sourceImage
             destinationImage: (MPSImage * __nonnull) destinationImage
                MPS_SWIFT_NAME( encode(commandBuffer:sourceImage:destinationImage:));

/*! @abstract   Encode a MPSCNNKernel with a destination state into a command Buffer.
 *  @discussion This is typically used during training. The state is commonly a MPSNNGradientState.
 *              Please see -resultStateForSourceImages:SourceStates: and batch+temporary variants.
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *  @param      sourceImage         A valid MPSImage object containing the source image.
 *  @param      destinationState    A state to be overwritten by additional state information.
 *  @param      destinationImage    A valid MPSImage to be overwritten by result image. destinationImage may not alias sourceImage. */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                  sourceImage: (MPSImage * __nonnull) sourceImage
             destinationState: (MPSState * __nonnull) destinationState
             destinationImage: (MPSImage * __nonnull) destinationImage
    MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
    MPS_SWIFT_NAME( encode(commandBuffer:sourceImage:destinationState:destinationImage:));

/*! @abstract   Encode a MPSCNNKernel into a command Buffer.  The operation shall proceed out-of-place.
 *  @discussion This is the older style of encode which reads the offset, doesn't change it,
 *              and ignores the padding method.
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *  @param      sourceImages        A valid MPSImage object containing the source images.
 *  @param      destinationImages   A valid MPSImage to be overwritten by result images.
 *                                  destinationImages may not alias sourceImages, even at different
 *                                  indices. */
-(void) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                      sourceImages: (MPSImageBatch * __nonnull) sourceImages
                 destinationImages: (MPSImageBatch * __nonnull) destinationImages
                MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
                MPS_SWIFT_NAME( encodeBatch(commandBuffer:sourceImages:destinationImages:));

/*! @abstract   Encode a MPSCNNKernel with a destination state into a command Buffer.
 *  @discussion This is typically used during training. The state is commonly a MPSNNGradientState.
 *              Please see -resultStateForSourceImages:SourceStates:destinationImage and batch+temporary variants.
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *  @param      sourceImages        A valid MPSImage object containing the source images.
 *  @param      destinationStates   A list of states to be overwritten by results
 *  @param      destinationImages   A valid MPSImage to be overwritten by result images.
 *                                  destinationImages may not alias sourceImages, even at different
 *                                  indices. */
-(void) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                      sourceImages: (MPSImageBatch * __nonnull) sourceImages
                 destinationStates: (MPSStateBatch * __nullable) destinationStates
                 destinationImages: (MPSImageBatch * __nonnull) destinationImages
                MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))    // added in .5 support update
                MPS_SWIFT_NAME( encodeBatch(commandBuffer:sourceImages:destinationStates:destinationImages:));


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
 *                  All images in a batch must have MPSImage.numberOfImages = 1.
 *
 *  @param          commandBuffer       The command buffer
 *  @param          sourceImage         A MPSImage to use as the source images for the filter.
 *  @result         A MPSImage or MPSTemporaryImage allocated per the destinationImageAllocator containing the output of the graph.
 *                  The offset property will be adjusted to reflect the offset used during the encode.
 *                  The returned image will be automatically released when the command buffer completes. If you want to
 *                  keep it around for longer, retain the image. (ARC will do this for you if you use it later.)
 */
-(MPSImage * __nonnull) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                  sourceImage: (MPSImage *  __nonnull) sourceImage
                    MPS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
                    MPS_SWIFT_NAME( encode(commandBuffer:sourceImage:));

/*! @abstract       Encode a MPSCNNKernel into a command Buffer. Create a texture and state to hold the results and return them.
 *  @discussion     In the first iteration on this method, encodeToCommandBuffer:sourceImage:destinationState:destinationImage:
 *                  some work was left for the developer to do in the form of correctly setting the offset property
 *                  and sizing the result buffer. With the introduction of the padding policy (see padding property)
 *                  the filter can do this work itself. If you would like to have some input into what sort of MPSImage
 *                  (e.g. temporary vs. regular) or what size it is or where it is allocated, you may set the
 *                  destinationImageAllocator to allocate the image yourself.
 *
 *                  This method uses the MPSNNPadding padding property to figure out how to size
 *                  the result image and to set the offset property. See discussion in MPSNeuralNetworkTypes.h.
 *                  All images in a batch must have MPSImage.numberOfImages = 1.
 *
 *  @param          commandBuffer       The command buffer
 *  @param          sourceImage         A MPSImage to use as the source images for the filter.
 *  @param          outState            A new state object is returned here.
 *  @result         A MPSImage or MPSTemporaryImage allocated per the destinationImageAllocator containing the output of the graph.
 *                  The offset property will be adjusted to reflect the offset used during the encode.
 *                  The returned image will be automatically released when the command buffer completes. If you want to
 *                  keep it around for longer, retain the image. (ARC will do this for you if you use it later.)
 */
-(MPSImage * __nonnull) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                  sourceImage: (MPSImage *  __nonnull) sourceImage
                             destinationState: (__autoreleasing MPSState * __nullable * __nonnull) outState
                  destinationStateIsTemporary: (BOOL) isTemporary
        MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
        MPS_SWIFT_NAME( encode(commandBuffer:sourceImage:destinationState:destinationStateIsTemporary:));


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
 *                  All images in a batch must have MPSImage.numberOfImages = 1.
 *
 *  @param          commandBuffer       The command buffer
 *  @param          sourceImages         A MPSImages to use as the source images for the filter.
 *  @result         An array of MPSImages or MPSTemporaryImages allocated per the destinationImageAllocator
 *                  containing the output of the graph. The offset property will be adjusted to reflect the
 *                  offset used during the encode. The returned images will be automatically released when
 *                  the command buffer completes. If you want to keep them around for longer, retain the images.
 */
-(MPSImageBatch * __nonnull) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                           sourceImages: (MPSImageBatch *  __nonnull) sourceImages
                        MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
                        MPS_SWIFT_NAME( encodeBatch(commandBuffer:sourceImages:));

/*! @abstract       Encode a MPSCNNKernel into a command Buffer. Create a MPSImageBatch and MPSStateBatch to hold the results and return them.
 *  @discussion     In the first iteration on this method, encodeToCommandBuffer:sourceImage:destinationImage:
 *                  some work was left for the developer to do in the form of correctly setting the offset property
 *                  and sizing the result buffer. With the introduction of the padding policy (see padding property)
 *                  the filter can do this work itself. If you would like to have some input into what sort of MPSImage
 *                  (e.g. temporary vs. regular) or what size it is or where it is allocated, you may set the
 *                  destinationImageAllocator to allocate the image yourself.
 *
 *                  This method uses the MPSNNPadding padding property to figure out how to size
 *                  the result image and to set the offset property. See discussion in MPSNeuralNetworkTypes.h.
 *                  All images in a batch must have MPSImage.numberOfImages = 1.
 *
 *                  Usage:
 *                  @code
 *                  MPSStateBatch * outStates = nil;    // autoreleased
 *                  MPSImageBatch * result = [k encodeBatchToCommandBuffer: cmdBuf
 *                                                            sourceImages: sourceImages
 *                                                       destinationStates: &outStates ];
 *                  @endcode
 *
 *  @param          commandBuffer       The command buffer
 *  @param          sourceImages         A MPSImages to use as the source images for the filter.
 *  @param          outStates            A pointer to storage to hold a MPSStateBatch* where output states are returned
 *  @result         An array of MPSImages or MPSTemporaryImages allocated per the destinationImageAllocator
 *                  containing the output of the graph. The offset property will be adjusted to reflect the
 *                  offset used during the encode. The returned images will be automatically released when
 *                  the command buffer completes. If you want to keep them around for longer, retain the images.
 */
-(MPSImageBatch * __nonnull) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                           sourceImages: (MPSImageBatch *  __nonnull) sourceImages
                                      destinationStates: (__autoreleasing MPSStateBatch * __nullable * __nonnull) outStates
                            destinationStateIsTemporary: (BOOL) isTemporary
                MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))  // added in .5 support update
                MPS_SWIFT_NAME( encodeBatch(commandBuffer:sourceImages:destinationStates:destinationStateIsTemporary:));

/*! @abstract   Allocate a MPSState (subclass) to hold the results from a -encodeBatchToCommandBuffer... operation
 *  @discussion A graph may need to allocate storage up front before executing.  This may be
 *              necessary to avoid using too much memory and to manage large batches.  The function
 *              should allocate any MPSState objects that will be produced by an -encode call
 *              with the indicated sourceImages and sourceStates inputs. Though the states
 *              can be further adjusted in the ensuing -encode call, the states should
 *              be initialized with all important data and all MTLResource storage allocated.
 *              The data stored in the MTLResource need not be initialized, unless the ensuing
 *              -encode call expects it to be.
 *
 *              The MTLDevice used by the result is derived from the source image.
 *              The padding policy will be applied to the filter before this is called
 *              to give it the chance to configure any properties like MPSCNNKernel.offset.
 *
 *              CAUTION:
 *              The kernel must have all properties set to values that will ultimately be
 *              passed to the -encode call that writes to the state, before
 *              -resultStateForSourceImages:sourceStates:destinationImage: is called or behavior is undefined.
 *              Please note that -destinationImageDescriptorForSourceImages:sourceStates:
 *              will alter some of these properties automatically based on the padding policy.
 *              If you intend to call that to make the destination image, then you should
 *              call that before -resultStateForSourceImages:sourceStates:destinationImage:. This will ensure the
 *              properties used in the encode call and in the destination image creation
 *              match those used to configure the state.
 *
 *              The following order is recommended:
 *
 *                  // Configure MPSCNNKernel properties first
 *                  kernel.edgeMode = MPSImageEdgeModeZero;
 *                  kernel.destinationFeatureChannelOffset = 128; // concatenation without the copy
 *                  ...
 *
 *                  // ALERT: will change MPSCNNKernel properties
 *                  MPSImageDescriptor * d = [kernel destinationImageDescriptorForSourceImage: source
 *                                                                               sourceStates: states];
 *                  MPSTemporaryImage * dest = [MPSTemporaryImage temporaryImageWithCommandBuffer: cmdBuf
 *                                                                                imageDescriptor: d];
 *
 *                  // Now that all properties are configured properly, we can make the result state
 *                  // and call encode.
 *                  MPSState * __nullable destState = [kernel resultStateForSourceImage: source
 *                                                                         sourceStates: states
 *                                                                     destinationImage: dest];
 *
 *                  // This form of -encode will be declared by the MPSCNNKernel subclass
 *                  [kernel encodeToCommandBuffer: cmdBuf
 *                                    sourceImage: source
 *                               destinationState: destState
 *                               destinationImage: dest ];
 *
 *              Default: returns nil
 *
 *  @param      sourceImage         The MPSImage consumed by the associated -encode call.
 *  @param      sourceStates        The list of MPSStates consumed by the associated -encode call,
 *                                  for a batch size of 1.
 *  @param      destinationImage    The destination image for the encode call
 *  @return     The list of states produced by the -encode call for batch size of 1.
 *              When the batch size is not 1, this function will be called repeatedly unless
 *              -isResultStateReusedAcrossBatch returns YES. If  -isResultStateReusedAcrossBatch
 *              returns YES, then it will be called once per batch and the MPSStateBatch array will
 *              contain MPSStateBatch.length references to the same object.
 */
-(MPSState * __nullable) resultStateForSourceImage: (MPSImage *__nonnull) sourceImage
                                      sourceStates: (NSArray <MPSState *> *__nullable) sourceStates
                                  destinationImage: (MPSImage *__nonnull) destinationImage
                        MPS_SWIFT_NAME( resultState(sourceImage:sourceStates:destinationImage:))
                        MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));
-(MPSStateBatch * __nullable) resultStateBatchForSourceImage: (MPSImageBatch * __nonnull) sourceImage
                                                sourceStates: (NSArray<MPSStateBatch *> * __nullable) sourceStates
                                            destinationImage: (MPSImageBatch *__nonnull) destinationImage
                        MPS_SWIFT_NAME( resultStateBatch(sourceImage:sourceStates:destinationImage:))
                        MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));


/*! @abstract   Allocate a temporary MPSState (subclass) to hold the results from a -encodeBatchToCommandBuffer... operation
 *  @discussion A graph may need to allocate storage up front before executing.  This may be
 *              necessary to avoid using too much memory and to manage large batches.  The function
 *              should allocate any MPSState objects that will be produced by an -encode call
 *              with the indicated sourceImages and sourceStates inputs. Though the states
 *              can be further adjusted in the ensuing -encode call, the states should
 *              be initialized with all important data and all MTLResource storage allocated.
 *              The data stored in the MTLResource need not be initialized, unless the ensuing
 *              -encode call expects it to be.
 *
 *              The MTLDevice used by the result is derived from the command buffer.
 *              The padding policy will be applied to the filter before this is called
 *              to give it the chance to configure any properties like MPSCNNKernel.offset.
 *
 *              CAUTION:
 *              The kernel must have all properties set to values that will ultimately be
 *              passed to the -encode call that writes to the state, before
 *              -resultStateForSourceImages:sourceStates:destinationImage: is called or behavior is undefined.
 *              Please note that -destinationImageDescriptorForSourceImages:sourceStates:destinationImage:
 *              will alter some of these properties automatically based on the padding policy.
 *              If you intend to call that to make the destination image, then you should
 *              call that before -resultStateForSourceImages:sourceStates:destinationImage:.  This will ensure the
 *              properties used in the encode call and in the destination image creation
 *              match those used to configure the state.
 *
 *              The following order is recommended:
 *
 *                  // Configure MPSCNNKernel properties first
 *                  kernel.edgeMode = MPSImageEdgeModeZero;
 *                  kernel.destinationFeatureChannelOffset = 128; // concatenation without the copy
 *                  ...
 *
 *                  // ALERT: will change MPSCNNKernel properties
 *                  MPSImageDescriptor * d = [kernel destinationImageDescriptorForSourceImage: source
 *                                                                               sourceStates: states];
 *                  MPSTemporaryImage * dest = [MPSTemporaryImage temporaryImageWithCommandBuffer: cmdBuf
 *                                                                                imageDescriptor: d];
 *
 *                  // Now that all properties are configured properly, we can make the result state
 *                  // and call encode.
 *                  MPSState * __nullable destState = [kernel temporaryResultStateForCommandBuffer: cmdBuf
 *                                                                                     sourceImage: source
 *                                                                                    sourceStates: states];
 *
 *                  // This form of -encode will be declared by the MPSCNNKernel subclass
 *                  [kernel encodeToCommandBuffer: cmdBuf
 *                                    sourceImage: source
 *                               destinationState: destState
 *                               destinationImage: dest ];
 *
 *              Default: returns nil
 *
 *  @param      commandBuffer       The command buffer to allocate the temporary storage against
 *                                  The state will only be valid on this command buffer.
 *  @param      sourceImage         The MPSImage consumed by the associated -encode call.
 *  @param      sourceStates        The list of MPSStates consumed by the associated -encode call,
 *                                  for a batch size of 1.
 *  @param      destinationImage    The destination image for the encode call
 *  @return     The list of states produced by the -encode call for batch size of 1.
 *              When the batch size is not 1, this function will be called repeatedly unless
 *              -isResultStateReusedAcrossBatch returns YES. If  -isResultStateReusedAcrossBatch
 *              returns YES, then it will be called once per batch and the MPSStateBatch array will
 *              contain MPSStateBatch.length references to the same object.
 */
-(MPSState * __nullable) temporaryResultStateForCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                                  sourceImage: (MPSImage *__nonnull) sourceImage
                                                 sourceStates: (NSArray <MPSState *> *__nullable) sourceStates
                                             destinationImage: (MPSImage *__nonnull) destinationImage
                         MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
                         MPS_SWIFT_NAME( temporaryResultState(commandBuffer:sourceImage:sourceStates:destinationImage:));
-(MPSStateBatch * __nullable) temporaryResultStateBatchForCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                                            sourceImage: (MPSImageBatch *__nonnull) sourceImage
                                                           sourceStates: (NSArray <MPSStateBatch *> *__nullable) sourceStates
                                                       destinationImage: (MPSImageBatch *__nonnull) destinationImage
                            MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
                            MPS_SWIFT_NAME( temporaryResultStateBatch(commandBuffer:sourceImage:sourceStates:destinationImage:));

/*! @abstract   Returns YES if the same state is used for every operation in a batch
 *  @discussion If NO, then each image in a MPSImageBatch will need a corresponding
 *              (and different) state to go with it. Set to YES to avoid allocating
 *              redundant state in the case when the same state is used all the time.
 *              Default: NO    */
-(BOOL)     isResultStateReusedAcrossBatch MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @abstract   Returns YES if the filter must be run over the entire batch before its
 *              results may be used
 *  @discussion Nearly all filters do not need to see the entire batch all at once and can
 *              operate correctly with partial batches. This allows the graph to
 *              strip-mine the problem, processing the graph top to bottom on a subset
 *              of the batch at a time, dramatically reducing memory usage. As the full
 *              nominal working set for a graph is often so large that it may not fit
 *              in memory, sub-batching may be required forward progress.
 *
 *              Batch normalization statistics on the other hand must complete the batch
 *              before the statistics may be used to normalize the images in the batch
 *              in the ensuing normalization filter. Consequently, batch normalization statistics
 *              requests the graph insert a batch barrier following it by returning
 *              YES from -appendBatchBarrier. This tells the graph to complete the batch
 *              before any dependent filters can start. Note that the filter itself may
 *              still be subject to sub-batching in its operation. All filters must be able to
 *              function without seeing the entire batch in a single -encode call. Carry
 *              over state that is accumulated across sub-batches is commonly carried in
 *              a shared MPSState containing a MTLBuffer. See -isResultStateReusedAcrossBatch.
 *
 *              Caution: on most supported devices, the working set may be so large
 *              that the graph may be forced to throw away and recalculate most
 *              intermediate images in cases where strip-mining can not occur because
 *              -appendBatchBarrier returns YES. A single batch barrier can commonly
 *              cause a memory size increase and/or performance reduction by many fold
 *              over the entire graph.  Filters of this variety should be avoided.
 *
 *              Default: NO
 */
-(BOOL)     appendBatchBarrier MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @abstract   Get a suggested destination image descriptor for a source image
 *  @discussion Your application is certainly free to pass in any destinationImage
 *              it likes to encodeToCommandBuffer:sourceImage:destinationImage,
 *              within reason. This is the basic design for iOS 10. This method
 *              is therefore not required.
 *
 *              However, calculating the MPSImage size and MPSCNNKernel properties
 *              for each filter can be tedious and complicated work, so this method
 *              is made available to automate the process. The application may
 *              modify the properties of the descriptor before a MPSImage is made from
 *              it, so long as the choice is sensible for the kernel in question.
 *              Please see individual kernel descriptions for restrictions.
 *
 *              The expected timeline for use is as follows:
 *
 *                1) This method is called:
 *                  a) The default MPS padding calculation is applied. It
 *                     uses the MPSNNPaddingMethod of the .padding property to
 *                     provide a consistent addressing scheme over the graph.
 *                     It creates the MPSImageDescriptor and adjusts the .offset
 *                     property of the MPSNNKernel. When using a MPSNNGraph, the
 *                     padding is set using the MPSNNFilterNode as a proxy.
 *
 *                  b) This method may be overridden by MPSCNNKernel subclass
 *                     to achieve any customization appropriate to the object type.
 *
 *                  c) Source states are then applied in order. These may modify the
 *                     descriptor and may update other object properties. See:
 *                      -destinationImageDescriptorForSourceImages:sourceStates:
 *                       forKernel:suggestedDescriptor:  This is the typical way
 *                      in which MPS may attempt to influence the operation of
 *                      its kernels.
 *
 *                  d) If the .padding property has a custom padding policy method
 *                      of the same name, it is called. Similarly, it may also adjust
 *                      the descriptor and any MPSCNNKernel properties. This is the
 *                      typical way in which your application may attempt to influence
 *                      the operation of the MPS kernels.
 *
 *                2) A result is returned from this method and the caller
 *                     may further adjust the descriptor and kernel properties
 *                     directly.
 *
 *                3) The caller uses the descriptor to make a new MPSImage to
 *                   use as the destination image for the -encode call in step 5.
 *
 *                4) The caller calls -resultStateForSourceImage:sourceStates:destinationImage:
 *                    to make any result states needed for the kernel. If there isn't
 *                    one, it will return nil. A variant is available to return a
 *                    temporary state instead.
 *
 *                5) a -encode method is called to encode the kernel.
 *
 *              The entire process 1-5 is more simply achieved by just calling an -encode...
 *              method that returns a MPSImage out the left hand sid of the method. Simpler
 *              still, use the MPSNNGraph to coordinate the entire process from end to end.
 *              Opportunities to influence the process are of course reduced, as (2) is no longer
 *              possible with either method. Your application may opt to use the five step method
 *              if it requires greater customization as described, or if it would like to estimate
 *              storage in advance based on the sum of MPSImageDescriptors before processing
 *              a graph. Storage estimation is done by using the MPSImageDescriptor to create
 *              a MPSImage (without passing it a texture), and then call -resourceSize. As long
 *              as the MPSImage is not used in an encode call and the .texture property is not
 *              invoked, the underlying MTLTexture is not created.
 *
 *              No destination state or destination image is provided as an argument to this
 *              function because it is expected they will be made / configured after this
 *              is called. This method is expected to auto-configure important object properties
 *              that may be needed in the ensuing destination image and state creation steps.
 *
 *  @param      sourceImages    A array of source images that will be passed into the -encode call
 *                              Since MPSCNNKernel is a unary kernel, it is an array of length 1.
 *  @param      sourceStates    An optional array of source states that will be passed into the -encode call
 *  @return     an image descriptor allocated on the autorelease pool
 */
-(MPSImageDescriptor*__nonnull) destinationImageDescriptorForSourceImages: (NSArray<MPSImage *> * __nonnull) sourceImages
                                                             sourceStates: (NSArray<MPSState *> * __nullable) sourceStates
                                MPS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
                                MPS_SWIFT_NAME( destinationImageDescriptor(sourceImages:sourceStates:));


/*! @abstract   The size of extra MPS heap storage allocated while the kernel is encoding
 *  @discussion This is best effort and just describes things that are likely to end up on the MPS heap. It does not
 *              describe all allocation done by the -encode call.  It is intended for use with high water calculations
 *              for MTLHeap sizing. Allocations are typically for temporary storage needed for multipass algorithms.
 *              This interface should not be used to detect multipass algorithms. */
-(NSUInteger) encodingStorageSizeForSourceImage: (MPSImage *__nonnull) sourceImage
                                   sourceStates: (NSArray <MPSState *> *__nullable) sourceStates
                               destinationImage: (MPSImage *__nullable) destinationImage
            MPS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
            MPS_SWIFT_NAME( encodingStorageSize(sourceImage:sourceStates:destinationImage:));

/*! @abstract   The size of extra MPS heap storage allocated while the kernel is encoding a batch
 *  @discussion This is best effort and just describes things that are likely to end up on the MPS heap. It does not
 *              describe all allocation done by the -encode call.  It is intended for use with high water calculations
 *              for MTLHeap sizing. Allocations are typically for temporary storage needed for multipass algorithms.
 *              This interface should not be used to detect multipass algorithms.  */
-(NSUInteger) batchEncodingStorageSizeForSourceImage: (MPSImageBatch * __nonnull) sourceImage
                                        sourceStates: (NSArray<MPSStateBatch *> * __nullable) sourceStates
                                    destinationImage: (MPSImageBatch *__nullable) destinationImage
            MPS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
            MPS_SWIFT_NAME( batchEncodingStorageSize(sourceImage:sourceStates:destinationImage:));


@end


/*!
 *  @class      MPSCNNBinaryKernel
 *  @dependency This depends on Metal.framework
 *  @abstract   Describes a convolution neural network kernel.
 *  @discussion A MPSCNNKernel consumes two MPSImages, primary and secondary, and produces one MPSImage.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface MPSCNNBinaryKernel : MPSKernel

/*! @abstract   Standard init with default properties per filter type
 *  @param      device      The device that the filter will be used on. May not be NULL.
 *  @result     A pointer to the newly initialized object. This will fail, returning
 *              nil if the device is not supported. Devices must be
 *              MTLFeatureSet_iOS_GPUFamily2_v1 or later.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                NS_DESIGNATED_INITIALIZER;

/*! @property   primaryOffset
 *  @abstract   The position of the destination clip rectangle origin relative to the primary source buffer.
 *  @discussion The offset is defined to be the position of clipRect.origin in source coordinates.
 *              Default: {0,0,0}, indicating that the top left corners of the clipRect and primary source image align.
 *              offset.z is the index of starting source image in batch processing mode.
 *
 *              See Also: @ref subsubsection_mpsoffset
 */
@property (readwrite, nonatomic) MPSOffset                primaryOffset;

/*! @property   secondaryOffset
 *  @abstract   The position of the destination clip rectangle origin relative to the secondary source buffer.
 *  @discussion The offset is defined to be the position of clipRect.origin in source coordinates.
 *              Default: {0,0,0}, indicating that the top left corners of the clipRect and secondary source image align.
 *              offset.z is the index of starting source image in batch processing mode.
 *
 *              See Also: @ref subsubsection_mpsoffset
 */
@property (readwrite, nonatomic) MPSOffset                secondaryOffset;

/*! @property   clipRect
 *  @abstract   An optional clip rectangle to use when writing data. Only the pixels in the rectangle will be overwritten.
 *  @discussion A MTLRegion that indicates which part of the destination to overwrite. If the clipRect does not lie
 *              completely within the destination image, the intersection between clip rectangle and destination bounds is
 *              used.   Default: MPSRectNoClip (MPSKernel::MPSRectNoClip) indicating the entire image.
 *              clipRect.origin.z is the index of starting destination image in batch processing mode. clipRect.size.depth
 *              is the number of images to process in batch processing mode.
 *
 *              See Also: @ref subsubsection_clipRect
 */
@property (readwrite, nonatomic) MTLRegion               clipRect;

/*! @property   destinationFeatureChannelOffset
 *  @abstract   The number of channels in the destination MPSImage to skip before writing output.
 *  @discussion This is the starting offset into the destination image in the feature channel dimension
 *              at which destination data is written.
 *              This allows an application to pass a subset of all the channels in MPSImage as output of MPSKernel.
 *              E.g. Suppose MPSImage has 24 channels and a MPSKernel outputs 8 channels. If
 *              we want channels 8 to 15 of this MPSImage to be used as output, we can set destinationFeatureChannelOffset = 8.
 *              Note that this offset applies independently to each image when the MPSImage
 *              is a container for multiple images and the MPSCNNKernel is processing multiple images (clipRect.size.depth > 1).
 *              The default value is 0 and any value specifed shall be a multiple of 4. If MPSKernel outputs N channels,
 *              destination image MUST have at least destinationFeatureChannelOffset + N channels. Using a destination
 *              image with insufficient number of feature channels result in an error.
 *              E.g. if the MPSCNNConvolution outputs 32 channels, and destination has 64 channels, then it is an error to set
 *              destinationFeatureChannelOffset > 32.
 */
@property (readwrite, nonatomic) NSUInteger              destinationFeatureChannelOffset;

/*! @property   primarySourceFeatureChannelOffset
 *  @abstract   The number of channels in the primary source MPSImage to skip before reading the input.
 *  @discussion This is the starting offset into the primary source image in the feature channel dimension
 *              at which source data is read. Unit: feature channels
 *              This allows an application to read a subset of all the channels in MPSImage as input of MPSKernel.
 *              E.g. Suppose MPSImage has 24 channels and a MPSKernel needs to read 8 channels. If
 *              we want channels 8 to 15 of this MPSImage to be used as input, we can set primarySourceFeatureChannelOffset = 8.
 *              Note that this offset applies independently to each image when the MPSImage
 *              is a container for multiple images and the MPSCNNKernel is processing multiple images (clipRect.size.depth > 1).
 *              The default value is 0 and any value specifed shall be a multiple of 4. If MPSKernel inputs N channels,
 *              the source image MUST have at least primarySourceFeatureChannelOffset + N channels. Using a source
 *              image with insufficient number of feature channels will result in an error.
 *              E.g. if the MPSCNNConvolution inputs 32 channels, and the source has 64 channels, then it is an error to set
 *              primarySourceFeatureChannelOffset > 32.
 */
@property (readwrite, nonatomic) NSUInteger              primarySourceFeatureChannelOffset MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @property   secondarySourceFeatureChannelOffset
 *  @abstract   The number of channels in the secondary source MPSImage to skip before reading the input.
 *  @discussion This is the starting offset into the secondary source image in the feature channel dimension
 *              at which source data is read. Unit: feature channels
 *              This allows an application to read a subset of all the channels in MPSImage as input of MPSKernel.
 *              E.g. Suppose MPSImage has 24 channels and a MPSKernel needs to read 8 channels. If
 *              we want channels 8 to 15 of this MPSImage to be used as input, we can set secondarySourceFeatureChannelOffset = 8.
 *              Note that this offset applies independently to each image when the MPSImage
 *              is a container for multiple images and the MPSCNNKernel is processing multiple images (clipRect.size.depth > 1).
 *              The default value is 0 and any value specifed shall be a multiple of 4. If MPSKernel inputs N channels,
 *              the source image MUST have at least primarySourceFeatureChannelOffset + N channels. Using a source
 *              image with insufficient number of feature channels will result in an error.
 *              E.g. if the MPSCNNConvolution inputs 32 channels, and the source has 64 channels, then it is an error to set
 *              primarySourceFeatureChannelOffset > 32.
 */
@property (readwrite, nonatomic) NSUInteger              secondarySourceFeatureChannelOffset MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @property   primarySourceFeatureChannelMaxCount
 *  @abstract   The maximum number of channels in the primary source MPSImage to use
 *  @discussion Most filters can insert a slice operation into the filter for free.
 *              Use this to limit the size of the feature channel slice taken from
 *              the input image. If the value is too large, it is truncated to be
 *              the remaining size in the image after the sourceFeatureChannelOffset
 *              is taken into account.  Default: ULONG_MAX
 */
@property (readwrite, nonatomic) NSUInteger              primarySourceFeatureChannelMaxCount;

/*! @property   secondarySourceFeatureChannelMaxCount
 *  @abstract   The maximum number of channels in the secondary source MPSImage to use
 *  @discussion Most filters can insert a slice operation into the filter for free.
 *              Use this to limit the size of the feature channel slice taken from
 *              the input image. If the value is too large, it is truncated to be
 *              the remaining size in the image after the sourceFeatureChannelOffset
 *              is taken into account.  Default: ULONG_MAX
 */
@property (readwrite, nonatomic) NSUInteger              secondarySourceFeatureChannelMaxCount;

/*! @property   primaryEdgeMode
 *  @abstract   The MPSImageEdgeMode to use when texture reads stray off the edge of the primary source image
 *  @discussion Most MPSKernel objects can read off the edge of the source image. This can happen
 *              because of a negative offset property, because the offset + clipRect.size is larger
 *              than the source image or because the filter looks at neighboring pixels, such as a
 *              Convolution filter.   Default:  MPSImageEdgeModeZero.
 *
 *              See Also: @ref subsubsection_edgemode
 */
@property (readwrite, nonatomic) MPSImageEdgeMode        primaryEdgeMode;

/*! @property   secondaryEdgeMode
 *  @abstract   The MPSImageEdgeMode to use when texture reads stray off the edge of the primary source image
 *  @discussion Most MPSKernel objects can read off the edge of the source image. This can happen
 *              because of a negative offset property, because the offset + clipRect.size is larger
 *              than the source image or because the filter looks at neighboring pixels, such as a
 *              Convolution filter.   Default:  MPSImageEdgeModeZero.
 *
 *              See Also: @ref subsubsection_edgemode
 */
@property (readwrite, nonatomic) MPSImageEdgeMode        secondaryEdgeMode;

/*! @property   primaryKernelWidth
 *  @abstract   The width of the MPSCNNBinaryKernel filter window
 *  @discussion This is the horizontal diameter of the region read by the filter for each
 *              result pixel. If the MPSCNNKernel does not have a filter window, then
 *              1 will be returned.
 */
@property (readonly, nonatomic) NSUInteger              primaryKernelWidth MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @property   primaryKernelHeight
 *  @abstract   The height of the MPSCNNBinaryKernel filter window
 *  @discussion This is the vertical diameter of the region read by the filter for each
 *              result pixel. If the MPSCNNKernel does not have a filter window, then
 *              1 will be returned.
 */
@property (readonly, nonatomic) NSUInteger              primaryKernelHeight MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @property   kernelWidth
 *  @abstract   The width of the MPSCNNBinaryKernel filter window for the second image source
 *  @discussion This is the horizontal diameter of the region read by the filter for each
 *              result pixel. If the MPSCNNBinaryKernel does not have a filter window, then
 *              1 will be returned.
 */
@property (readonly, nonatomic) NSUInteger              secondaryKernelWidth MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @property   kernelHeight
 *  @abstract   The height of the MPSCNNBinaryKernel filter window for the second image source
 *  @discussion This is the vertical diameter of the region read by the filter for each
 *              result pixel. If the MPSCNNBinaryKernel does not have a filter window, then
 *              1 will be returned.
 */
@property (readonly, nonatomic) NSUInteger              secondaryKernelHeight MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));


/*! @property   primaryStrideInPixelsX
 *  @abstract   The downsampling (or upsampling if a backwards filter) factor in the horizontal dimension
 *              for the primary source image
 *  @discussion If the filter does not do up or downsampling, 1 is returned.
 */
@property(readwrite, nonatomic) NSUInteger              primaryStrideInPixelsX MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @property   primaryStrideInPixelsY
 *  @abstract   The downsampling (or upsampling if a backwards filter) factor in the vertical dimension
 *              for the primary source image
 *  @discussion If the filter does not do up or downsampling, 1 is returned.
 */
@property(readwrite, nonatomic) NSUInteger              primaryStrideInPixelsY MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @property   secondaryStrideInPixelsX
 *  @abstract   The downsampling (or upsampling if a backwards filter) factor in the horizontal dimension
 *              for the secondary source image
 *  @discussion If the filter does not do up or downsampling, 1 is returned.
 */
@property(readwrite, nonatomic) NSUInteger              secondaryStrideInPixelsX MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @property   secondaryStrideInPixelsY
 *  @abstract   The downsampling (or upsampling if a backwards filter) factor in the vertical dimension
 *              for the secondary source image
 *  @discussion If the filter does not do up or downsampling, 1 is returned.
 */
@property(readwrite, nonatomic) NSUInteger              secondaryStrideInPixelsY MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @property   dilationRateX
 *  @abstract   Stride in source coordinates from one kernel tap to the next in the X dimension.
 */
@property(readonly, nonatomic) NSUInteger               primaryDilationRateX MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @property   dilationRate
 *  @abstract   Stride in source coordinates from one kernel tap to the next in the Y dimension.
 */
@property(readonly, nonatomic) NSUInteger               primaryDilationRateY MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @property   dilationRateX
 *  @abstract   Stride in source coordinates from one kernel tap to the next in the X dimension.
 *  @discussion As applied to the secondary source image.
 */
@property(readonly, nonatomic) NSUInteger               secondaryDilationRateX MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @property   dilationRate
 *  @abstract   Stride in source coordinates from one kernel tap to the next in the Y dimension.
 *  @discussion As applied to the secondary source image.
 */
@property(readonly, nonatomic) NSUInteger               secondaryDilationRateY MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));


/*! @property   isBackwards
 *  @abstract   YES if the filter operates backwards.
 *  @discussion This influences how strideInPixelsX/Y should be interpreted.
 */
@property(readonly, nonatomic) BOOL                     isBackwards;

/*! @abstract   Returns true if the -encode call modifies the state object it accepts.  */
@property (readonly, nonatomic) BOOL                    isStateModified
        MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));


/*! @property   padding
 *  @abstract   The padding method used by the filter
 *  @discussion This influences how strideInPixelsX/Y should be interpreted.
 *              Default:  MPSNNPaddingMethodAlignCentered | MPSNNPaddingMethodAddRemainderToTopLeft | MPSNNPaddingMethodSizeSame
 *              Some object types (e.g. MPSCNNFullyConnected) may override this default with something appropriate to its operation.
 */
@property (readwrite, nonatomic, nonnull, retain) id <MPSNNPadding>    padding;

/*! @abstract   Method to allocate the result image for -encodeToCommandBuffer:sourceImage:
 *  @discussion Default: MPSTemporaryImage.defaultAllocator
 */
@property (readwrite, nonatomic, retain, nonnull) id <MPSImageAllocator>  destinationImageAllocator;



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

/*!
 *  @abstract   Encode a MPSCNNKernel into a command Buffer.  The operation shall proceed out-of-place.
 *  @discussion This is the older style of encode which reads the offset, doesn't change it,
 *              and ignores the padding method.
 *  @param      commandBuffer        A valid MTLCommandBuffer to receive the encoded filter
 *  @param      primaryImage         A valid MPSImage object containing the primary source image.
 *  @param      secondaryImage       A valid MPSImage object containing the secondary source image.
 *  @param      destinationImage     A valid MPSImage to be overwritten by result image. destinationImage may not alias primarySourceImage or secondarySourceImage.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                 primaryImage: (MPSImage * __nonnull) primaryImage
               secondaryImage: (MPSImage * __nonnull) secondaryImage
             destinationImage: (MPSImage * __nonnull) destinationImage
                MPS_SWIFT_NAME( encode(commandBuffer:primaryImage:secondaryImage:destinationImage:));

/*!
 *  @abstract   Encode a MPSCNNKernel into a command Buffer.  The operation shall proceed out-of-place.
 *  @discussion This is the older style of encode which reads the offset, doesn't change it,
 *              and ignores the padding method. Multiple images are processed concurrently.
 *              All images must have MPSImage.numberOfImages = 1.
 *  @param      commandBuffer         A valid MTLCommandBuffer to receive the encoded filter
 *  @param      primaryImages         An array of MPSImage objects containing the primary source images.
 *  @param      secondaryImages       An array MPSImage objects containing the secondary source images.
 *  @param      destinationImages     An array of MPSImage objects to contain the result images.
 *                                    destinationImages may not alias primarySourceImages or secondarySourceImages
 *                                    in any manner.
 */
-(void) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                     primaryImages: (MPSImageBatch * __nonnull) primaryImages
                   secondaryImages: (MPSImageBatch * __nonnull) secondaryImages
                 destinationImages: (MPSImageBatch * __nonnull) destinationImages
                MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
                MPS_SWIFT_NAME( encodeBatch(commandBuffer:primaryImages:secondaryImages:destinationImages:));

/*! @abstract       Encode a MPSCNNKernel into a command Buffer. Create a texture to hold the result and return it.
 *  @discussion     In the first iteration on this method, encodeToCommandBuffer:sourceImage:destinationImage:
 *                  some work was left for the developer to do in the form of correctly setting the offset property
 *                  and sizing the result buffer. With the introduction of the padding policy (see padding property)
 *                  the filter can do this work itself. If you would like to have some input into what sort of MPSImage
 *                  (e.g. temporary vs. regular) or what size it is or where it is allocated, you may set the
 *                  destinationImageAllocator to allocate the image yourself.
 *
 *                  This method uses the MPSNNPadding padding property to figure out how to size
 *                  the result image and to set the offset property.  See discussion in MPSNeuralNetworkTypes.h.
 *
 *  @param          commandBuffer       The command buffer
 *  @param          primaryImage        A MPSImages to use as the primary source images for the filter.
 *  @param          secondaryImage      A MPSImages to use as the secondary source images for the filter.
 *  @result         A MPSImage or MPSTemporaryImage allocated per the destinationImageAllocator containing the output of the graph.
 *                  The returned image will be automatically released when the command buffer completes. If you want to
 *                  keep it around for longer, retain the image. (ARC will do this for you if you use it later.)
 */
-(MPSImage * __nonnull) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                 primaryImage: (MPSImage * __nonnull) primaryImage
                               secondaryImage: (MPSImage * __nonnull) secondaryImage
                        MPS_SWIFT_NAME( encode(commandBuffer:primaryImage:secondaryImage:));

/*! @abstract       Encode a MPSCNNKernel into a command Buffer. Create textures to hold the results and return them.
 *  @discussion     In the first iteration on this method, encodeBatchToCommandBuffer:sourceImage:destinationImage:
 *                  some work was left for the developer to do in the form of correctly setting the offset property
 *                  and sizing the result buffer. With the introduction of the padding policy (see padding property)
 *                  the filter can do this work itself. If you would like to have some input into what sort of MPSImage
 *                  (e.g. temporary vs. regular) or what size it is or where it is allocated, you may set the
 *                  destinationImageAllocator to allocate the image yourself.
 *
 *                  This method uses the MPSNNPadding padding property to figure out how to size
 *                  the result image and to set the offset property.  See discussion in MPSNeuralNetworkTypes.h.
 *                  All images in a batch must have MPSImage.numberOfImages = 1.
 *
 *  @param          commandBuffer       The command buffer
 *  @param          primaryImage        A MPSImages to use as the primary source images for the filter.
 *  @param          secondaryImage      A MPSImages to use as the secondary source images for the filter.
 *  @result         A MPSImage or MPSTemporaryImage allocated per the destinationImageAllocator containing the output of the graph.
 *                  The returned image will be automatically released when the command buffer completes. If you want to
 *                  keep it around for longer, retain the image. (ARC will do this for you if you use it later.)
 */
-(MPSImageBatch * __nonnull) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                          primaryImages: (MPSImageBatch * __nonnull) primaryImage
                                        secondaryImages: (MPSImageBatch * __nonnull) secondaryImage
                        MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
                        MPS_SWIFT_NAME( encodeBatch(commandBuffer:primaryImages:secondaryImages:));

/*! @abstract       Encode a MPSCNNKernel into a command Buffer. Create a texture and state to hold the results and return them.
 *  @discussion     In the first iteration on this method, encodeToCommandBuffer:sourceImage:destinationState:destinationImage:
 *                  some work was left for the developer to do in the form of correctly setting the offset property
 *                  and sizing the result buffer. With the introduction of the padding policy (see padding property)
 *                  the filter can do this work itself. If you would like to have some input into what sort of MPSImage
 *                  (e.g. temporary vs. regular) or what size it is or where it is allocated, you may set the
 *                  destinationImageAllocator to allocate the image yourself.
 *
 *                  This method uses the MPSNNPadding padding property to figure out how to size
 *                  the result image and to set the offset property. See discussion in MPSNeuralNetworkTypes.h.
 *                  All images in a batch must have MPSImage.numberOfImages = 1.
 *
 *  @param          commandBuffer       The command buffer
 *  @param          primaryImage        A MPSImage to use as the source images for the filter.
 *  @param          secondaryImage      A MPSImage to use as the source images for the filter.
 *  @param          outState            The address of location to write the pointer to the result state of the operation
 *  @param          isTemporary         YES if the outState should be a temporary object
 *  @result         A MPSImage or MPSTemporaryImage allocated per the destinationImageAllocator containing the output of the graph.
 *                  The offset property will be adjusted to reflect the offset used during the encode.
 *                  The returned image will be automatically released when the command buffer completes. If you want to
 *                  keep it around for longer, retain the image. (ARC will do this for you if you use it later.)
 */
-(MPSImage * __nonnull) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                 primaryImage: (MPSImage *  __nonnull) primaryImage
                               secondaryImage: (MPSImage *  __nonnull) secondaryImage
                             destinationState: (__autoreleasing MPSState * __nullable * __nonnull) outState
                  destinationStateIsTemporary: (BOOL) isTemporary
                    MPS_SWIFT_NAME( encode(commandBuffer:primaryImage:secondaryImage:destinationState:destinationStateIsTemporary:))
                    MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @abstract       Encode a MPSCNNKernel into a command Buffer. Create a texture and state to hold the results and return them.
 *  @discussion     In the first iteration on this method, encodeToCommandBuffer:sourceImage:destinationState:destinationImage:
 *                  some work was left for the developer to do in the form of correctly setting the offset property
 *                  and sizing the result buffer. With the introduction of the padding policy (see padding property)
 *                  the filter can do this work itself. If you would like to have some input into what sort of MPSImage
 *                  (e.g. temporary vs. regular) or what size it is or where it is allocated, you may set the
 *                  destinationImageAllocator to allocate the image yourself.
 *
 *                  This method uses the MPSNNPadding padding property to figure out how to size
 *                  the result image and to set the offset property. See discussion in MPSNeuralNetworkTypes.h.
 *                  All images in a batch must have MPSImage.numberOfImages = 1.
 *
 *  @param          commandBuffer       The command buffer
 *  @param          primaryImages       A MPSImage to use as the source images for the filter.
 *  @param          secondaryImages     A MPSImage to use as the source images for the filter.
 *  @param          outState            A new state object is returned here.
 *  @param          isTemporary         YES if the outState should be a temporary object
 *  @result         A MPSImage or MPSTemporaryImage allocated per the destinationImageAllocator containing the output of the graph.
 *                  The offset property will be adjusted to reflect the offset used during the encode.
 *                  The returned image will be automatically released when the command buffer completes. If you want to
 *                  keep it around for longer, retain the image. (ARC will do this for you if you use it later.)
 */
-(MPSImageBatch * __nonnull) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                          primaryImages: (MPSImageBatch *  __nonnull) primaryImages
                                        secondaryImages: (MPSImageBatch *  __nonnull) secondaryImages
                                      destinationStates: (__autoreleasing MPSStateBatch * __nullable * __nonnull) outState
                            destinationStateIsTemporary: (BOOL) isTemporary
            MPS_SWIFT_NAME( encodeBatch(commandBuffer:primaryImages:secondaryImages:destinationStates:destinationStateIsTemporary:))
            MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));



/*! @abstract   Allocate a MPSState (subclass) to hold the results from a -encodeBatchToCommandBuffer... operation
 *  @discussion A graph may need to allocate storage up front before executing.  This may be
 *              necessary to avoid using too much memory and to manage large batches.  The function
 *              should allocate a MPSState object (if any) that will be produced by an -encode call
 *              with the indicated sourceImages and sourceStates inputs. Though the states
 *              can be further adjusted in the ensuing -encode call, the states should
 *              be initialized with all important data and all MTLResource storage allocated.
 *              The data stored in the MTLResource need not be initialized, unless the ensuing
 *              -encode call expects it to be.
 *
 *              The MTLDevice used by the result is derived from the source image.
 *              The padding policy will be applied to the filter before this is called
 *              to give it the chance to configure any properties like MPSCNNKernel.offset.
 *
 *              CAUTION: the result state should be made after the kernel properties are
 *                       configured for the -encode call that will write to the state, and
 *                       after -destinationImageDescriptorForSourceImages:sourceStates:
 *                       is called (if it is called). Otherwise, behavior is undefined.
 *                       Please see the description of
 *                       -[MPSCNNKernel resultStateForSourceImage:sourceStates:destinationImage:] for more.
 *
 *              Default: returns nil
 *
 *  @param      primaryImage        The MPSImage consumed by the associated -encode call.
 *  @param      secondaryImage      The MPSImage consumed by the associated -encode call.
 *  @param      sourceStates        The list of MPSStates consumed by the associated -encode call,
 *                                  for a batch size of 1.
 *  @return     The list of states produced by the -encode call for batch size of 1.
 *              When the batch size is not 1, this function will be called repeatedly unless
 *              -isResultStateReusedAcrossBatch returns YES. If  -isResultStateReusedAcrossBatch
 *              returns YES, then it will be called once per batch and the MPSStateBatch array will
 *              contain MPSStateBatch.length references to the same object.
 */
-(MPSState * __nullable) resultStateForPrimaryImage: (MPSImage * __nonnull) primaryImage
                                     secondaryImage: (MPSImage * __nonnull) secondaryImage
                                       sourceStates: (NSArray <MPSState *> *__nullable) sourceStates
                                   destinationImage: (MPSImage * __nonnull) destinationImage
                            MPS_SWIFT_NAME( resultState(primaryImage:secondaryImage:sourceStates:destinationImage:))
                            MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

-(MPSStateBatch * __nullable) resultStateBatchForPrimaryImage: (MPSImageBatch * __nonnull) primaryImage
                                               secondaryImage: (MPSImageBatch * __nonnull) secondaryImage
                                                 sourceStates: (NSArray <MPSStateBatch *> *__nullable) sourceStates
                                             destinationImage: (MPSImageBatch * __nonnull) destinationImage
                            MPS_SWIFT_NAME( resultStateBatch(primaryImage:secondaryImage:sourceStates:destinationImage:))
                            MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));


/*! @abstract   Allocate a temporary MPSState (subclass) to hold the results from a -encodeBatchToCommandBuffer... operation
 *  @discussion A graph may need to allocate storage up front before executing.  This may be
 *              necessary to avoid using too much memory and to manage large batches.  The function
 *              should allocate any MPSState objects that will be produced by an -encode call
 *              with the indicated sourceImages and sourceStates inputs. Though the states
 *              can be further adjusted in the ensuing -encode call, the states should
 *              be initialized with all important data and all MTLResource storage allocated.
 *              The data stored in the MTLResource need not be initialized, unless the ensuing
 *              -encode call expects it to be.
 *
 *              The MTLDevice used by the result is derived from the command buffer.
 *              The padding policy will be applied to the filter before this is called
 *              to give it the chance to configure any properties like MPSCNNKernel.offset.
 *
 *              CAUTION: the result state should be made after the kernel properties are
 *                       configured for the -encode call that will write to the state, and
 *                       after -destinationImageDescriptorForSourceImages:sourceStates:
 *                       is called (if it is called). Otherwise, behavior is undefined.
 *                       Please see the description of
 *                       -[MPSCNNKernel resultStateForSourceImage:sourceStates:destinationImage] for more.
 *
 *              Default: returns nil
 *
 *  @param      commandBuffer       The command buffer to allocate the temporary storage against
 *                                  The state will only be valid on this command buffer.
 *  @param      primaryImage        The MPSImage consumed by the associated -encode call.
 *  @param      secondaryImage      The MPSImage consumed by the associated -encode call.
 *  @param      sourceStates        The list of MPSStates consumed by the associated -encode call,
 *                                  for a batch size of 1.
 *  @return     The list of states produced by the -encode call for batch size of 1.
 *              When the batch size is not 1, this function will be called repeatedly unless
 *              -isResultStateReusedAcrossBatch returns YES. If  -isResultStateReusedAcrossBatch
 *              returns YES, then it will be called once per batch and the MPSStateBatch array will
 *              contain MPSStateBatch.length references to the same object.
 */
-(MPSState * __nullable) temporaryResultStateForCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                                 primaryImage: (MPSImage *__nonnull) primaryImage
                                               secondaryImage: (MPSImage *__nonnull) secondaryImage
                                                 sourceStates: (NSArray <MPSState *> *__nullable) sourceStates
                                             destinationImage: (MPSImage *__nonnull) destinationImage
                        MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
                        MPS_SWIFT_NAME( temporaryResultState(commandBuffer:primaryImage:secondaryImage:sourceStates:destinationImage:));

-(MPSStateBatch * __nullable) temporaryResultStateBatchForCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                                           primaryImage: (MPSImageBatch *__nonnull) primaryImage
                                                         secondaryImage: (MPSImageBatch *__nonnull) secondaryImage
                                                           sourceStates: (NSArray <MPSStateBatch *> *__nullable) sourceStates
                                                       destinationImage: (MPSImageBatch *__nonnull) destinationImage
                        MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
                        MPS_SWIFT_NAME( temporaryResultStateBatch(commandBuffer:primaryImage:secondaryImage:sourceStates:destinationImage:));

/*! @abstract   Returns YES if the same state is used for every operation in a batch
 *  @discussion If NO, then each image in a MPSImageBatch will need a corresponding
 *              (and different) state to go with it. Set to YES to avoid allocating
 *              redundant state in the case when the same state is used all the time.
 *              Default: NO    */
-(BOOL)     isResultStateReusedAcrossBatch MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @abstract   Returns YES if the filter must be run over the entire batch before its
 *              results may be considered complete
 *  @discussion The MPSNNGraph may split batches into sub-batches to save memory. However,
 *              some filters, like batch statistics calculations, need to operate over
 *              the entire batch to calculate a valid result, in this case, the mean and
 *              variance per channel over the set of images.
 *
 *              In such cases, the accumulated result is commonly stored in a MPSState
 *              containing a MTLBuffer. (MTLTextures may not be able to be read from
 *              and written to in the same filter on some devices.) -isResultStateReusedAcrossBatch
 *              is set to YES, so that the state is allocated once and passed in for each
 *              sub-batch and the filter accumulates its results into it, one sub-batch
 *              at a time. Note that sub-batches may frequently be as small as 1.
 *
 *              Default: NO
 */
-(BOOL)     appendBatchBarrier MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @abstract   Get a suggested destination image descriptor for a source image
 *  @discussion Your application is certainly free to pass in any destinationImage
 *              it likes to encodeToCommandBuffer:sourceImage:destinationImage,
 *              within reason. This is the basic design for iOS 10. This method
 *              is therefore not required.
 *
 *              However, calculating the MPSImage size and MPSCNNBinaryKernel properties
 *              for each filter can be tedious and complicated work, so this method
 *              is made available to automate the process. The application may
 *              modify the properties of the descriptor before a MPSImage is made from
 *              it, so long as the choice is sensible for the kernel in question.
 *              Please see individual kernel descriptions for restrictions.
 *
 *              The expected timeline for use is as follows:
 *
 *                1) This method is called:
 *                  a) The default MPS padding calculation is applied. It
 *                     uses the MPSNNPaddingMethod of the .padding property to
 *                     provide a consistent addressing scheme over the graph.
 *                     It creates the MPSImageDescriptor and adjusts the .offset
 *                     property of the MPSNNKernel. When using a MPSNNGraph, the
 *                     padding is set using the MPSNNFilterNode as a proxy.
 *
 *                  b) This method may be overridden by MPSCNNBinaryKernel subclass
 *                     to achieve any customization appropriate to the object type.
 *
 *                  c) Source states are then applied in order. These may modify the
 *                     descriptor and may update other object properties. See:
 *                      -destinationImageDescriptorForSourceImages:sourceStates:
 *                       forKernel:suggestedDescriptor:  This is the typical way
 *                      in which MPS may attempt to influence the operation of
 *                      its kernels.
 *
 *                  d) If the .padding property has a custom padding policy method
 *                      of the same name, it is called. Similarly, it may also adjust
 *                      the descriptor and any MPSCNNBinaryKernel properties. This is the
 *                      typical way in which your application may attempt to influence
 *                      the operation of the MPS kernels.
 *
 *                2) A result is returned from this method and the caller
 *                     may further adjust the descriptor and kernel properties
 *                     directly.
 *
 *                3) The caller uses the descriptor to make a new MPSImage to
 *                   use as the destination image for the -encode call in step 5.
 *
 *                4) The caller calls -resultStateForSourceImage:sourceStates:destinationImage:
 *                    to make any result states needed for the kernel. If there isn't
 *                    one, it will return nil. A variant is available to return a
 *                    temporary state instead.
 *
 *                5) a -encode method is called to encode the kernel.
 *
 *              The entire process 1-5 is more simply achieved by just calling an -encode...
 *              method that returns a MPSImage out the left hand sid of the method. Simpler
 *              still, use the MPSNNGraph to coordinate the entire process from end to end.
 *              Opportunities to influence the process are of course reduced, as (2) is no longer
 *              possible with either method. Your application may opt to use the five step method
 *              if it requires greater customization as described, or if it would like to estimate
 *              storage in advance based on the sum of MPSImageDescriptors before processing
 *              a graph. Storage estimation is done by using the MPSImageDescriptor to create
 *              a MPSImage (without passing it a texture), and then call -resourceSize. As long
 *              as the MPSImage is not used in an encode call and the .texture property is not
 *              invoked, the underlying MTLTexture is not created.
 *
 *              No destination state or destination image is provided as an argument to this
 *              function because it is expected they will be made / configured after this
 *              is called. This method is expected to auto-configure important object properties
 *              that may be needed in the ensuing destination image and state creation steps.
 *
 *  @param      sourceImages    A array of source images that will be passed into the -encode call
 *                              Since MPSCNNBinaryKernel is a binary kernel, it is an array of length 2.
 *  @param      sourceStates    An optional array of source states that will be passed into the -encode call
 *  @return     an image descriptor allocated on the autorelease pool
 */
-(MPSImageDescriptor*__nonnull) destinationImageDescriptorForSourceImages: (NSArray<MPSImage *> * __nonnull) sourceImages
                                                             sourceStates: (NSArray<MPSState *> * __nullable) sourceStates;

/*! @abstract   The size of extra MPS heap storage allocated while the kernel is encoding
 *  @discussion This is best effort and just describes things that are likely to end up on the MPS heap. It does not
 *              describe all allocation done by the -encode call.  It is intended for use with high water calculations
 *              for MTLHeap sizing. Allocations are typically for temporary storage needed for multipass algorithms.
 *              This interface should not be used to detect multipass algorithms.  */
-(NSUInteger) encodingStorageSizeForPrimaryImage: (MPSImage *__nonnull) primaryImage
                                  secondaryImage: (MPSImage *__nonnull) secondaryImage
                                    sourceStates: (NSArray <MPSState *> *__nullable) sourceStates
                                destinationImage: (MPSImage *__nullable) destinationImage
    MPS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
    MPS_SWIFT_NAME( encodingStorageSize(primaryImage:secondaryImage:sourceStates:destinationImage:));

/*! @abstract   The size of extra MPS heap storage allocated while the kernel is encoding a batch
 *  @discussion This is best effort and just describes things that are likely to end up on the MPS heap. It does not
 *              describe all allocation done by the -encode call.  It is intended for use with high water calculations
 *              for MTLHeap sizing. Allocations are typically for temporary storage needed for multipass algorithms.
 *              This interface should not be used to detect multipass algorithms.  */
-(NSUInteger) batchEncodingStorageSizeForPrimaryImage: (MPSImageBatch * __nonnull) primaryImage
                                       secondaryImage: (MPSImageBatch * __nonnull) secondaryImage
                                         sourceStates: (NSArray<MPSStateBatch *> * __nullable) sourceStates
                                     destinationImage: (MPSImageBatch *__nullable) destinationImage
    MPS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
    MPS_SWIFT_NAME( batchEncodingStorageSize(primaryImage:secondaryImage:sourceStates:destinationImage:));

@end


/*! @class  MPSCNNGradientKernel
 *  @discussion Gradient kernels are the backwards pass of a MPSCNNKernel
 *              used during training to calculate gradient back propagation.
 *              These take as arguments the gradient result from the next filter
 *              and the source image for the forward version of the filter.
 *              There is also a MPSNNGradientState passed from MPSCNNKernel
 *              to MPSCNNGradientKernel that contains information about the
 *              MPSCNNKernel parameters at the time it encoded and possibly
 *              also additional MTLResources to enable it to do its job.
 *
 *@code
 *          Training graph (partial):
 *
 *              ---> input image ---------> MPSCNNKernel ------>  resultImage ------>-->-->-->.
 *                             \                  |                                           |
 *                              '------.    MPSNNGradientState                         loss estimation
 *                                      \         |                                           |
 *                                       V        V                                           V
 *              <--- result gradient <- MPSCNNGradientKernel <---  input gradient <--<--<--<---'
 *
 *              In general operation, starting with the input image, the sequence of events is:
 *              1a)  Invoke padding policy to find result size for MPSCNNKernel.  This
 *                   also configures some MPSCNNKernel parameters such as offset.
 *              1b)  Use the MPSImageDescriptor from 1a to make resultImage.
 *              1c)  Call MPSCNNKernel -encode...
 *              2) stages 1a-c are repeated for other forward passes in the inference portion of the graph
 *              3) We estimate the loss resulting from the whole inference computation so far (see MPSCNNLoss.h>
 *              4) stages 5a-c are repeated for corresponding backward gradient passes in the graph
 *              5a) Invoke padding policy on the MPSCNNGradientKernel shown above. This sets the
 *                  MPSCNNGradientKernel parameters to correspond with those in the forward pass
 *              5b) The result gradient for the MPSCNNGradientKernel is created from the MPSImageDescriptor from 5a
 *              5c) Call MPSCNNGradientKernel -encode with the input image, input gradient, result gradient and MPSNNGradientState
 *              6) pass the result gradient on to leftward gradient passes.
 *@endcode
 *
 *              For MPSCNNKernels that are trained, there may be other accompanying training kernels that
 *              need to be called in addition to the gradient kernel to update convolution weights or batch
 *              normalization parameters, for example. Steps 1a-c and 5a-c can be combined in a single -encode
 *              call. These return the result image or gradient out the left hand side.
 *
 *              For purposes of inheritance the gradient image is the MPSCNNBinaryKernel primary image
 *              and the source image is the MPSCNNBinaryKernel secondary image. Various secondary properties
 *              such as kernel size are copies of the forward inference pass parameters of similar name
 *              are set automatically when -[MPSCNNGradientKernel destinationImageDescriptorForSourceImages:sourceStates:]
 *              is called.
 */

MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface MPSCNNGradientKernel : MPSCNNBinaryKernel

/*! @abstract   Standard init with default properties per filter type
 *  @param      device      The device that the filter will be used on. May not be NULL.
 *  @result     A pointer to the newly initialized object. This will fail, returning
 *              nil if the device is not supported. Devices must be
 *              MTLFeatureSet_iOS_GPUFamily2_v1 or later.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
NS_DESIGNATED_INITIALIZER;


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


/*! @property   kernelOffsetX
 *  @abstract   Offset in the kernel reference frame to position the kernel in the X dimension
 *  @discussion In some cases, the input gradient must be upsampled with zero insertion
 *              to account for things like strides in the forward MPSCNNKernel pass.
 *              As such, the offset, which describes a X,Y offset in the source coordinate
 *              space is insufficient to fully describe the offset applied to a kernel.
 *              The kernel offset is the offset after upsampling. Both the source offset
 *              and kernel offset are additive:  effective offset = source offset * stride + kernel offset.
 *              The offset is applied to the (upsampled) source gradient  */
@property (readwrite, nonatomic) NSInteger                kernelOffsetX;

/*! @property   kernelOffsetY
 *  @abstract   Offset in the kernel reference frame to position the kernel in the Y dimension
 *  @discussion In some cases, the input gradient must be upsampled with zero insertion
 *              to account for things like strides in the forward MPSCNNKernel pass.
 *              As such, the offset, which describes a X,Y offset in the source coordinate
 *              space is insufficient to fully describe the offset applied to a kernel.
 *              The kernel offset is the offset after upsampling. Both the source offset
 *              and kernel offset are additive:  effective offset = source offset * stride + kernel offset.
*               The offset is applied to the (upsampled) source gradient */
@property (readwrite, nonatomic) NSInteger                kernelOffsetY;

/*! @abstract   Encode a gradient filter and return a gradient
 *  @discussion During training, gradient filters are used to calculate the gradient
 *              associated with the loss for each feature channel in the forward pass
 *              source image. For those nodes that are trainable, these are then used
 *              to refine the value used in the trainable parameter. They consume
 *              a source gradient image which contains the gradients corresponding
 *              with the forward pass destination image, and calculate the gradients
 *              corresponding to the forward pass source image.
 *
 *              A gradient filter consumes a MPSNNGradientState object which captured
 *              various forward pass properties such as offset and edgeMode at the time
 *              the forward pass was encoded. These are transferred to the MPSCNNBinaryKernel
 *              secondary image properties automatically when this method creates its
 *              destination image.
 *
 *  @param      commandBuffer   The MTLCommandBuffer on which to encode
 *  @param      sourceGradient  The gradient image from the "next" filter in the graph (in the inference direction)
 *  @param      sourceImage     The image used as source image by the forward inference pass
 *  @param      gradientState   The MPSNNGradientState or MPSNNBinaryGradientState subclass produced by the forward
 *                              inference pass
 *  @result   The result gradient from the gradient filter */
-(MPSImage*__nonnull) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) commandBuffer
                             sourceGradient: (MPSImage * __nonnull ) sourceGradient        // a.k.a. primaryImage
                                sourceImage: (MPSImage * __nonnull ) sourceImage           // source Image from forward pass, a.k.a. secondaryImage
                              gradientState: (MPSState * __nonnull ) gradientState         // MPSNNGradientState/MPSNNBinaryGradientState from forward pass;
            MPS_SWIFT_NAME( encode(commandBuffer:sourceGradient:sourceImage:gradientState:));

/*! @abstract   Encode a gradient filter and return a gradient
 *  @discussion During training, gradient filters are used to calculate the gradient
 *              associated with the loss for each feature channel in the forward pass
 *              source image. For those nodes that are trainable, these are then used
 *              to refine the value used in the trainable parameter. They consume
 *              a source gradient image which contains the gradients corresponding
 *              with the forward pass destination image, and calculate the gradients
 *              corresponding to the forward pass source image.
 *
 *              A gradient filter consumes a MPSNNGradientState object which captured
 *              various forward pass properties such as offset and edgeMode at the time
 *              the forward pass was encoded. These are transferred to the MPSCNNBinaryKernel
 *              secondary image properties automatically when you use -[MPSCNNGradientKernel
 *              destinationImageDescriptorForSourceImages:sourceStates:]. If you do not call
 *              this method, then you are responsible for configuring all of the primary and
 *              secondary image properties in MPSCNNBinaryKernel. Please see class description
 *              for expected ordering of operations.
 *
 *  @param      commandBuffer   The MTLCommandBuffer on which to encode
 *  @param      sourceGradient  The gradient image from the "next" filter in the graph
 *  @param      sourceImage     The image used as source image from the forward pass
 *  @param      gradientState   The MPSNNGradientState and MPSNNBinaryGradientState subclass produced by the
 *                              forward pass
 *  @param      destinationGradient  The MPSImage into which to write the filter result*/
-(void) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) commandBuffer
               sourceGradient: (MPSImage * __nonnull ) sourceGradient        // a.k.a. primaryImage
                  sourceImage: (MPSImage * __nonnull ) sourceImage           // source Image from forward pass, a.k.a. secondaryImage
                gradientState: (MPSState * __nonnull ) gradientState         // MPSNNGradientState/MPSNNBinaryGradientState from forward pass;
          destinationGradient: (MPSImage * __nonnull ) destinationGradient
    MPS_SWIFT_NAME( encode(commandBuffer:sourceGradient:sourceImage:gradientState:destinationGradient:));

/*! @abstract   Encode a gradient filter and return a gradient
 *  @discussion During training, gradient filters are used to calculate the gradient
 *              associated with the loss for each feature channel in the forward pass
 *              source image. For those nodes that are trainable, these are then used
 *              to refine the value used in the trainable parameter. They consume
 *              a source gradient image which contains the gradients corresponding
 *              with the forward pass destination image, and calculate the gradients
 *              corresponding to the forward pass source image.
 *
 *              A gradient filter consumes a MPSNNGradientState object which captured
 *              various forward pass properties such as offset and edgeMode at the time
 *              the forward pass was encoded. These are transferred to the MPSCNNBinaryKernel
 *              secondary image properties automatically when this method creates its
 *              destination image.
 *  @param      commandBuffer    The MTLCommandBuffer on which to encode
 *  @param      sourceGradients  The gradient images from the "next" filter in the graph
 *  @param      sourceImages     The images used as source image from the forward pass
 *  @param      gradientStates   The MPSNNGradientState or MPSNNBinaryGradientState subclass produced by the
 *                               forward pass
 */
-(MPSImageBatch*__nonnull) encodeBatchToCommandBuffer: (__nonnull id <MTLCommandBuffer>) commandBuffer
                                      sourceGradients: (MPSImageBatch * __nonnull ) sourceGradients        // a.k.a. primaryImage
                                         sourceImages: (MPSImageBatch * __nonnull ) sourceImages           // source Image from forward pass, a.k.a. secondaryImage
                                       gradientStates: (MPSStateBatch * __nonnull ) gradientStates
        MPS_SWIFT_NAME( encodeBatch(commandBuffer:sourceGradients:sourceImages:gradientStates:));

/*! @abstract   Encode a gradient filter and return a gradient
 *  @discussion During training, gradient filters are used to calculate the gradient
 *              associated with the loss for each feature channel in the forward pass
 *              source image. For those nodes that are trainable, these are then used
 *              to refine the value used in the trainable parameter. They consume
 *              a source gradient image which contains the gradients corresponding
 *              with the forward pass destination image, and calculate the gradients
 *              corresponding to the forward pass source image.
 *
 *              A gradient filter consumes a MPSNNGradientState object which captured
 *              various forward pass properties such as offset and edgeMode at the time
 *              the forward pass was encoded. These are transferred to the MPSCNNBinaryKernel
 *              secondary image properties automatically when you use -[MPSCNNGradientKernel
 *              destinationImageDescriptorForSourceImages:sourceStates:]. If you do not call
 *              this method, then you are responsible for configuring all of the primary and
 *              secondary image properties in MPSCNNBinaryKernel. Please see class description
 *              for expected ordering of operations.
 *  @param      commandBuffer    The MTLCommandBuffer on which to encode
 *  @param      sourceGradients  The gradient images from the "next" filter in the graph
 *  @param      sourceImages     The image used as source images from the forward pass
 *  @param      gradientStates   An array of the MPSNNGradientState or MPSNNBinaryGradientState subclass
 *                               produced by the forward pass
 *  @param      destinationGradients  The MPSImages into which to write the filter result */
-(void) encodeBatchToCommandBuffer: (__nonnull id <MTLCommandBuffer>) commandBuffer
                   sourceGradients: (MPSImageBatch * __nonnull ) sourceGradients        // a.k.a. primaryImage
                      sourceImages: (MPSImageBatch * __nonnull ) sourceImages           // source Image from forward pass, a.k.a. secondaryImage
                    gradientStates: (MPSStateBatch * __nonnull ) gradientStates
              destinationGradients: (MPSImageBatch * __nonnull ) destinationGradients
        MPS_SWIFT_NAME( encodeBatch(commandBuffer:sourceGradients:sourceImages:gradientStates:destinationGradients:));

@end

#pragma mark -

/*!
 *  @class      MPSCNNMultiaryKernel
 *  @dependency This depends on Metal.framework
 *  @abstract   Describes a  neural network kernel with multiple image sources.
 *  @discussion A MPSCNNKernel consumes multiple MPSImages, possibly a MPSState, and produces one MPSImage.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSCNNMultiaryKernel : MPSKernel

/*! @abstract   Standard init with default properties per filter type
 *  @param      device      The device that the filter will be used on. May not be NULL.
 *  @param      sourceCount The number of source images or MPSImageBatches
 *  @result     A pointer to the newly initialized object. This will fail, returning
 *              nil if the device is not supported. Devices must be
 *              MTLFeatureSet_iOS_GPUFamily2_v1 or later.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           sourceCount: (NSUInteger) sourceCount NS_DESIGNATED_INITIALIZER;

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*! @abstract   The number of source images accepted by the kernel */
@property (readonly, nonatomic) NSUInteger  sourceCount;

/*! @property   clipRect
 *  @abstract   An optional clip rectangle to use when writing data. Only the pixels in the rectangle will be overwritten.
 *  @discussion A MTLRegion that indicates which part of the destination to overwrite. If the clipRect does not lie
 *              completely within the destination image, the intersection between clip rectangle and destination bounds is
 *              used.   Default: MPSRectNoClip (MPSKernel::MPSRectNoClip) indicating the entire image.
 *              clipRect.origin.z is the index of starting destination image in batch processing mode. clipRect.size.depth
 *              is the number of images to process in batch processing mode.
 *
 *              See Also: @ref subsubsection_clipRect
 */
@property (readwrite, nonatomic) MTLRegion               clipRect;

/*! @property   destinationFeatureChannelOffset
 *  @abstract   The number of channels in the destination MPSImage to skip before writing output.
 *  @discussion This is the starting offset into the destination image in the feature channel dimension
 *              at which destination data is written.
 *              This allows an application to pass a subset of all the channels in MPSImage as output of MPSKernel.
 *              E.g. Suppose MPSImage has 24 channels and a MPSKernel outputs 8 channels. If
 *              we want channels 8 to 15 of this MPSImage to be used as output, we can set destinationFeatureChannelOffset = 8.
 *              Note that this offset applies independently to each image when the MPSImage
 *              is a container for multiple images and the MPSCNNKernel is processing multiple images (clipRect.size.depth > 1).
 *              The default value is 0 and any value specifed shall be a multiple of 4. If MPSKernel outputs N channels,
 *              destination image MUST have at least destinationFeatureChannelOffset + N channels. Using a destination
 *              image with insufficient number of feature channels result in an error.
 *              E.g. if the MPSCNNConvolution outputs 32 channels, and destination has 64 channels, then it is an error to set
 *              destinationFeatureChannelOffset > 32.
 */
@property (readwrite, nonatomic) NSUInteger              destinationFeatureChannelOffset;

/*! @property   isBackwards
 *  @abstract   YES if the filter operates backwards.
 *  @discussion This influences how strideInPixelsX/Y should be interpreted.
 */
@property(readonly, nonatomic) BOOL                     isBackwards;

/*! @abstract   Returns true if the -encode call modifies the state object it accepts.  */
@property (readonly, nonatomic) BOOL                    isStateModified;

/*! @property   padding
 *  @abstract   The padding method used by the filter
 *  @discussion This influences how strideInPixelsX/Y should be interpreted.
 *              Default:  MPSNNPaddingMethodAlignCentered | MPSNNPaddingMethodAddRemainderToTopLeft | MPSNNPaddingMethodSizeSame
 *              Some object types (e.g. MPSCNNFullyConnected) may override this default with something appropriate to its operation.
 */
@property (readwrite, nonatomic, nonnull, retain) id <MPSNNPadding>    padding;

/*! @abstract   Method to allocate the result image for -encodeToCommandBuffer:sourceImage:
 *  @discussion Default: MPSTemporaryImage.defaultAllocator
 */
@property (readwrite, nonatomic, retain, nonnull) id <MPSImageAllocator>  destinationImageAllocator;


/*! @abstract   The positon of the destination clip rectangle origin relative to each source buffer
 *  @discussion The offset is defined to be the position of clipRect.origin in source coordinates.
 *              Default: {0,0,0}, indicating that the top left corners of the clipRect and source image align.
 *              offset.z is the index of starting source image in batch processing mode.
 *  @param      index   The index of the source image described by the offset
 *  @return     A MPSOffset for that image */
-(MPSOffset)  offsetAtIndex: (NSUInteger) index;

/*! @abstract   Set the positon of the destination clip rectangle origin relative to each source buffer
 *  @discussion The offset is defined to be the position of clipRect.origin in source coordinates.
 *              Default: {0,0,0}, indicating that the top left corners of the clipRect and source image align.
 *              offset.z is the index of starting source image in batch processing mode.
 *  @param      offset  The new offset
 *  @param      index   The index of the source image described by the offset */
-(void)  setOffset: (MPSOffset) offset
           atIndex: (NSUInteger) index;

/*! @abstract   The number of channels in the source MPSImage to skip before reading the input.
 *  @discussion This is the starting offset into the  source image in the feature channel dimension
 *              at which source data is read. Unit: feature channels
 *              This allows an application to read a subset of all the channels in MPSImage as input of MPSKernel.
 *              E.g. Suppose MPSImage has 24 channels and a MPSKernel needs to read 8 channels. If
 *              we want channels 8 to 15 of this MPSImage to be used as input, we can set sourceFeatureChannelOffset[0] = 8.
 *              Note that this offset applies independently to each image when the MPSImage
 *              is a container for multiple images and the MPSCNNKernel is processing multiple images (clipRect.size.depth > 1).
 *              The default value is 0 and any value specifed shall be a multiple of 4. If MPSKernel inputs N channels,
 *              the source image MUST have at least primarySourceFeatureChannelOffset + N channels. Using a source
 *              image with insufficient number of feature channels will result in an error.
 *              E.g. if the MPSCNNConvolution inputs 32 channels, and the source has 64 channels, then it is an error to set
 *              primarySourceFeatureChannelOffset > 32.
 *  @param      index   The index of the source image that the feature channel offset describes
 *  @return     The source feature channel offset */
-(NSUInteger) sourceFeatureChannelOffsetAtIndex: (NSUInteger) index;

/*! @abstract   Set the number of channels in the source MPSImage to skip before reading the input.
 *  @discussion This is the starting offset into the  source image in the feature channel dimension
 *              at which source data is read. Unit: feature channels
 *              This allows an application to read a subset of all the channels in MPSImage as input of MPSKernel.
 *              E.g. Suppose MPSImage has 24 channels and a MPSKernel needs to read 8 channels. If
 *              we want channels 8 to 15 of this MPSImage to be used as input, we can set sourceFeatureChannelOffset[0] = 8.
 *              Note that this offset applies independently to each image when the MPSImage
 *              is a container for multiple images and the MPSCNNKernel is processing multiple images (clipRect.size.depth > 1).
 *              The default value is 0 and any value specifed shall be a multiple of 4. If MPSKernel inputs N channels,
 *              the source image MUST have at least primarySourceFeatureChannelOffset + N channels. Using a source
 *              image with insufficient number of feature channels will result in an error.
 *              E.g. if the MPSCNNConvolution inputs 32 channels, and the source has 64 channels, then it is an error to set
 *              primarySourceFeatureChannelOffset > 32.
 *  @param      index   The index of the source image that the feature channel offset describes
 *  @param      offset The source feature channel offset */
-(void) setSourceFeatureChannelOffset: (NSUInteger) offset
                              atIndex: (NSUInteger) index;

/*! @abstract   The maximum number of channels in the source MPSImage to use
 *  @discussion Most filters can insert a slice operation into the filter for free.
 *              Use this to limit the size of the feature channel slice taken from
 *              the input image. If the value is too large, it is truncated to be
 *              the remaining size in the image after the sourceFeatureChannelOffset
 *              is taken into account.  Default: ULONG_MAX
 *  @param      index The index of the source image to which the max count refers
 *  @return     The source feature channel max count */
-(NSUInteger) sourceFeatureChannelMaxCountAtIndex: (NSUInteger) index;

/*! @abstract   Set the maximum number of channels in the source MPSImage to use
 *  @discussion Most filters can insert a slice operation into the filter for free.
 *              Use this to limit the size of the feature channel slice taken from
 *              the input image. If the value is too large, it is truncated to be
 *              the remaining size in the image after the sourceFeatureChannelOffset
 *              is taken into account.  Default: ULONG_MAX
 *  @param      count The new source feature channel max count
 *  @param      index The index of the source image to which the max count refers */
-(void) setSourceFeatureChannelMaxCount: (NSUInteger) count
                                atIndex: (NSUInteger) index;

/*! @abstract   The MPSImageEdgeMode to use when texture reads stray off the edge of the primary source image
 *  @discussion Most MPSKernel objects can read off the edge of the source image. This can happen
 *              because of a negative offset property, because the offset + clipRect.size is larger
 *              than the source image or because the filter looks at neighboring pixels, such as a
 *              Convolution filter.   Default:  MPSImageEdgeModeZero.
 *
 *              See Also: @ref subsubsection_edgemode
 *  @param      index   The index of the source image to which the edge mode refers
 *  @return     The edge mode for that source image */
-(MPSImageEdgeMode) edgeModeAtIndex: (NSUInteger) index;

/*! @abstract   Set the MPSImageEdgeMode to use when texture reads stray off the edge of the primary source image
 *  @discussion Most MPSKernel objects can read off the edge of the source image. This can happen
 *              because of a negative offset property, because the offset + clipRect.size is larger
 *              than the source image or because the filter looks at neighboring pixels, such as a
 *              Convolution filter.   Default:  MPSImageEdgeModeZero.
 *
 *              See Also: @ref subsubsection_edgemode
 *  @param      edgeMode    The new edge mode to use
 *  @param      index       The index of the source image to which the edge mode refers */
-(void) setEdgeMode: (MPSImageEdgeMode) edgeMode
            atIndex: (NSUInteger) index;

/*! @abstract   The width of the kernel filter window
 *  @discussion This is the horizontal diameter of the region read by the filter for each
 *              result pixel. If the MPSCNNKernel does not have a filter window, then
 *              1 will be returned.
 *  @param      index   The index of the source image to which the kernel width refers */
-(NSUInteger) kernelWidthAtIndex: (NSUInteger) index;

/*! @abstract   Set the width of the kernel filter window
 *  @discussion This is the horizontal diameter of the region read by the filter for each
 *              result pixel. If the MPSCNNKernel does not have a filter window, then
 *              1 will be returned.
 *  @param      width   The new width
 *  @param      index   The index of the source image to which the kernel width refers */
-(void) setKernelWidth: (NSUInteger) width
               atIndex: (NSUInteger) index;

/*! @abstract   The height of the kernel filter window
 *  @discussion This is the horizontal diameter of the region read by the filter for each
 *              result pixel. If the MPSCNNKernel does not have a filter window, then
 *              1 will be returned.
 *  @param      index   The index of the source image to which the kernel width refers */
-(NSUInteger) kernelHeightAtIndex: (NSUInteger) index;

/*! @abstract   Set the height of the kernel filter window
 *  @discussion This is the horizontal diameter of the region read by the filter for each
 *              result pixel. If the MPSCNNKernel does not have a filter window, then
 *              1 will be returned.
 *  @param      height   The new width
 *  @param      index   The index of the source image to which the kernel width refers */
-(void) setKernelHeight: (NSUInteger) height
               atIndex: (NSUInteger) index;

/*! @abstract   The downsampling factor in the horizontal dimension for the source image
 *  @param      index   The index of the source Image
 *  @discussion If the filter does not do up or downsampling, 1 is returned.
 *  @return     The stride */
-(NSUInteger) strideInPixelsXatIndex: (NSUInteger) index;

/*! @abstract   The downsampling factor in the horizontal dimension for the source image
 *  @discussion If the filter does not do up or downsampling, 1 is returned.  Default: 1
 *  @param      index   The index of the source Image
 *  @param      stride The stride for the source image */
-(void) setStrideInPixelsX: (NSUInteger) stride
                   atIndex: (NSUInteger) index;

/*! @abstract   The downsampling factor in the vertical dimension for the source image
 *  @param      index   The index of the source Image
 *  @discussion If the filter does not do up or downsampling, 1 is returned.
 *  @return     The stride */
-(NSUInteger) strideInPixelsYatIndex: (NSUInteger) index;

/*! @abstract   The downsampling factor in the vertical dimension for the source image
 *  @discussion If the filter does not do up or downsampling, 1 is returned.  Default: 1
 *  @param      index   The index of the source Image
 *  @param      stride The stride for the source image */
-(void) setStrideInPixelsY: (NSUInteger) stride
                   atIndex: (NSUInteger) index;


/*! @abstract   Stride in source coordinates from one kernel tap to the next in the X dimension.
 *  @param      index   The index of the source image to which the dilation rate applies
 *  @return     The dilation rate   */
-(NSUInteger) dilationRateXatIndex: (NSUInteger) index;

/*! @abstract   Set the stride in source coordinates from one kernel tap to the next in the X dimension.
 *  @param      index   The index of the source image to which the dilation rate applies
 *  @param      dilationRate The dilation rate   */
-(void) setDilationRateX: (NSUInteger) dilationRate
                 atIndex: (NSUInteger) index;

/*! @abstract   Stride in source coordinates from one kernel tap to the next in the Y dimension.
 *  @param      index   The index of the source image to which the dilation rate applies
 *  @return     The dilation rate   */
-(NSUInteger) dilationRateYatIndex: (NSUInteger) index;

/*! @abstract   Set the stride in source coordinates from one kernel tap to the next in the Y dimension.
 *  @param      index   The index of the source image to which the dilation rate applies
 *  @param      dilationRate The dilation rate   */
-(void) setDilationRateY: (NSUInteger) dilationRate
                 atIndex: (NSUInteger) index;



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

/*!
 *  @abstract   Encode a MPSCNNKernel into a command Buffer.  The operation shall proceed out-of-place.
 *  @discussion This is the older style of encode which reads the offset, doesn't change it,
 *              and ignores the padding method.
 *  @param      commandBuffer        A valid MTLCommandBuffer to receive the encoded filter
 *  @param      sourceImages         An array containing the source images
 *  @param      destinationImage     A valid MPSImage to be overwritten by result image. destinationImage may not alias primarySourceImage or secondarySourceImage.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                 sourceImages: (NSArray<MPSImage *> * __nonnull) sourceImages
             destinationImage: (MPSImage * __nonnull) destinationImage
    MPS_SWIFT_NAME( encode(commandBuffer:sourceImages:destinationImage:));

/*!
 *  @abstract   Encode a MPSCNNKernel into a command Buffer.  The operation shall proceed out-of-place.
 *  @discussion This is the older style of encode which reads the offset, doesn't change it,
 *              and ignores the padding method. Multiple images are processed concurrently.
 *              All images must have MPSImage.numberOfImages = 1.
 *  @param      commandBuffer         A valid MTLCommandBuffer to receive the encoded filter
 *  @param      sourceImages          An array of image batches containing the source images.
 *  @param      destinationImages     An array of MPSImage objects to contain the result images.
 *                                    destinationImages may not alias primarySourceImages or secondarySourceImages
 *                                    in any manner.
 */
-(void) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                      sourceImages: (NSArray<MPSImageBatch *> * __nonnull) sourceImages
                 destinationImages: (MPSImageBatch * __nonnull) destinationImages
    MPS_SWIFT_NAME( encodeBatch(commandBuffer:sourceImages:destinationImages:));

/*! @abstract       Encode a MPSCNNKernel into a command Buffer. Create a texture to hold the result and return it.
 *  @discussion     In the first iteration on this method, encodeToCommandBuffer:sourceImage:destinationImage:
 *                  some work was left for the developer to do in the form of correctly setting the offset property
 *                  and sizing the result buffer. With the introduction of the padding policy (see padding property)
 *                  the filter can do this work itself. If you would like to have some input into what sort of MPSImage
 *                  (e.g. temporary vs. regular) or what size it is or where it is allocated, you may set the
 *                  destinationImageAllocator to allocate the image yourself.
 *
 *                  This method uses the MPSNNPadding padding property to figure out how to size
 *                  the result image and to set the offset property.  See discussion in MPSNeuralNetworkTypes.h.
 *
 *  @param          commandBuffer       The command buffer
 *  @param          sourceImages        An array of MPSImages to use as the source images for the filter.
 *  @result         A MPSImage or MPSTemporaryImage allocated per the destinationImageAllocator containing the output of the graph.
 *                  The returned image will be automatically released when the command buffer completes. If you want to
 *                  keep it around for longer, retain the image. (ARC will do this for you if you use it later.)
 */
-(MPSImage * __nonnull) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                 sourceImages: (NSArray<MPSImage *>* __nonnull) sourceImages
        MPS_SWIFT_NAME( encode(commandBuffer:sourceImages:));

/*! @abstract       Encode a MPSCNNKernel into a command Buffer. Create textures to hold the results and return them.
 *  @discussion     In the first iteration on this method, encodeBatchToCommandBuffer:sourceImage:destinationImage:
 *                  some work was left for the developer to do in the form of correctly setting the offset property
 *                  and sizing the result buffer. With the introduction of the padding policy (see padding property)
 *                  the filter can do this work itself. If you would like to have some input into what sort of MPSImage
 *                  (e.g. temporary vs. regular) or what size it is or where it is allocated, you may set the
 *                  destinationImageAllocator to allocate the image yourself.
 *
 *                  This method uses the MPSNNPadding padding property to figure out how to size
 *                  the result image and to set the offset property.  See discussion in MPSNeuralNetworkTypes.h.
 *                  All images in a batch must have MPSImage.numberOfImages = 1.
 *
 *  @param          commandBuffer       The command buffer
 *  @param          sourceImageBatches  An array of image batches to use as the source images for the filter.
 *  @result         A MPSImage or MPSTemporaryImage allocated per the destinationImageAllocator containing the output of the graph.
 *                  The returned image will be automatically released when the command buffer completes. If you want to
 *                  keep it around for longer, retain the image. (ARC will do this for you if you use it later.)
 */
-(MPSImageBatch * __nonnull) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                           sourceImages: (NSArray<MPSImageBatch *> * __nonnull) sourceImageBatches
        MPS_SWIFT_NAME( encodeBatch(commandBuffer:sourceImages:));

/*! @abstract       Encode a MPSCNNKernel into a command Buffer. Create a texture and state to hold the results and return them.
 *  @discussion     In the first iteration on this method, encodeToCommandBuffer:sourceImage:destinationState:destinationImage:
 *                  some work was left for the developer to do in the form of correctly setting the offset property
 *                  and sizing the result buffer. With the introduction of the padding policy (see padding property)
 *                  the filter can do this work itself. If you would like to have some input into what sort of MPSImage
 *                  (e.g. temporary vs. regular) or what size it is or where it is allocated, you may set the
 *                  destinationImageAllocator to allocate the image yourself.
 *
 *                  This method uses the MPSNNPadding padding property to figure out how to size
 *                  the result image and to set the offset property. See discussion in MPSNeuralNetworkTypes.h.
 *                  All images in a batch must have MPSImage.numberOfImages = 1.
 *
 *  @param          commandBuffer       The command buffer
 *  @param          sourceImages        An array of MPSImages to use as the source images for the filter.
 *  @param          outState            The address of location to write the pointer to the result state of the operation
 *  @param          isTemporary         YES if the outState should be a temporary object
 *  @result         A MPSImage or MPSTemporaryImage allocated per the destinationImageAllocator containing the output of the graph.
 *                  The offset property will be adjusted to reflect the offset used during the encode.
 *                  The returned image will be automatically released when the command buffer completes. If you want to
 *                  keep it around for longer, retain the image. (ARC will do this for you if you use it later.)
 */
-(MPSImage * __nonnull) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                 sourceImages: (NSArray<MPSImage *> *  __nonnull) sourceImages
                             destinationState: (__autoreleasing MPSState * __nullable * __nonnull) outState
                  destinationStateIsTemporary: (BOOL) isTemporary
    MPS_SWIFT_NAME( encode(commandBuffer:sourceImages:destinationState:destinationStateIsTemporary:));

/*! @abstract       Encode a MPSCNNKernel into a command Buffer. Create a texture and state to hold the results and return them.
 *  @discussion     In the first iteration on this method, encodeToCommandBuffer:sourceImage:destinationState:destinationImage:
 *                  some work was left for the developer to do in the form of correctly setting the offset property
 *                  and sizing the result buffer. With the introduction of the padding policy (see padding property)
 *                  the filter can do this work itself. If you would like to have some input into what sort of MPSImage
 *                  (e.g. temporary vs. regular) or what size it is or where it is allocated, you may set the
 *                  destinationImageAllocator to allocate the image yourself.
 *
 *                  This method uses the MPSNNPadding padding property to figure out how to size
 *                  the result image and to set the offset property. See discussion in MPSNeuralNetworkTypes.h.
 *                  All images in a batch must have MPSImage.numberOfImages = 1.
 *
 *  @param          commandBuffer       The command buffer
 *  @param          sourceImageBatches  An array of batches to use as the source images for the filter.
 *  @param          outState            A new state object is returned here.
 *  @param          isTemporary         YES if the outState should be a temporary object
 *  @result         A MPSImage or MPSTemporaryImage allocated per the destinationImageAllocator containing the output of the graph.
 *                  The offset property will be adjusted to reflect the offset used during the encode.
 *                  The returned image will be automatically released when the command buffer completes. If you want to
 *                  keep it around for longer, retain the image. (ARC will do this for you if you use it later.)
 */
-(MPSImageBatch * __nonnull) encodeBatchToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                           sourceImages: (NSArray<MPSImageBatch *> * __nonnull) sourceImageBatches
                                      destinationStates: (__autoreleasing MPSStateBatch * __nullable * __nonnull) outState
                            destinationStateIsTemporary: (BOOL) isTemporary
    MPS_SWIFT_NAME( encodeBatch(commandBuffer:sourceImages:destinationStates:destinationStateIsTemporary:));



/*! @abstract   Returns YES if the same state is used for every operation in a batch
 *  @discussion If NO, then each image in a MPSImageBatch will need a corresponding
 *              (and different) state to go with it. Set to YES to avoid allocating
 *              redundant state in the case when the same state is used all the time.
 *              Default: NO    */
-(BOOL)     isResultStateReusedAcrossBatch;

/*! @abstract   Returns YES if the filter must be run over the entire batch before its
 *              results may be used
 *  @discussion Nearly all filters do not need to see the entire batch all at once and can
 *              operate correctly with partial batches. This allows the graph to
 *              strip-mine the problem, processing the graph top to bottom on a subset
 *              of the batch at a time, dramatically reducing memory usage. As the full
 *              nominal working set for a graph is often so large that it may not fit
 *              in memory, sub-batching may be required forward progress.
 *
 *              Batch normalization statistics on the other hand must complete the batch
 *              before the statistics may be used to normalize the images in the batch
 *              in the ensuing normalization filter. Consequently, batch normalization statistics
 *              requests the graph insert a batch barrier following it by returning
 *              YES from -appendBatchBarrier. This tells the graph to complete the batch
 *              before any dependent filters can start. Note that the filter itself may
 *              still be subject to sub-batching in its operation. All filters must be able to
 *              function without seeing the entire batch in a single -encode call. Carry
 *              over state that is accumulated across sub-batches is commonly carried in
 *              a shared MPSState containing a MTLBuffer. See -isResultStateReusedAcrossBatch.
 *
 *              Caution: on most supported devices, the working set may be so large
 *              that the graph may be forced to throw away and recalculate most
 *              intermediate images in cases where strip-mining can not occur because
 *              -appendBatchBarrier returns YES. A single batch barrier can commonly
 *              cause a memory size increase and/or performance reduction by many fold
 *              over the entire graph.  Filters of this variety should be avoided.
 *
 *              Default: NO
 */
-(BOOL)     appendBatchBarrier;

/*! @abstract   Allocate a MPSState (subclass) to hold the results from a -encodeBatchToCommandBuffer... operation
 *  @discussion A graph may need to allocate storage up front before executing.  This may be
 *              necessary to avoid using too much memory and to manage large batches.  The function
 *              should allocate any MPSState objects that will be produced by an -encode call
 *              with the indicated sourceImages and sourceStates inputs. Though the states
 *              can be further adjusted in the ensuing -encode call, the states should
 *              be initialized with all important data and all MTLResource storage allocated.
 *              The data stored in the MTLResource need not be initialized, unless the ensuing
 *              -encode call expects it to be.
 *
 *              The MTLDevice used by the result is derived from the source image.
 *              The padding policy will be applied to the filter before this is called
 *              to give it the chance to configure any properties like MPSCNNKernel.offset.
 *
 *              CAUTION:
 *              The kernel must have all properties set to values that will ultimately be
 *              passed to the -encode call that writes to the state, before
 *              -resultStateForSourceImages:sourceStates:destinationImage: is called or behavior is undefined.
 *              Please note that -destinationImageDescriptorForSourceImages:sourceStates:
 *              will alter some of these properties automatically based on the padding policy.
 *              If you intend to call that to make the destination image, then you should
 *              call that before -resultStateForSourceImages:sourceStates:destinationImage:. This will ensure the
 *              properties used in the encode call and in the destination image creation
 *              match those used to configure the state.
 *
 *              The following order is recommended:
 *
 *                  // Configure MPSCNNKernel properties first
 *                  kernel.edgeMode = MPSImageEdgeModeZero;
 *                  kernel.destinationFeatureChannelOffset = 128; // concatenation without the copy
 *                  ...
 *
 *                  // ALERT: will change MPSCNNKernel properties
 *                  MPSImageDescriptor * d = [kernel destinationImageDescriptorForSourceImage: source
 *                                                                               sourceStates: states];
 *                  MPSTemporaryImage * dest = [MPSTemporaryImage temporaryImageWithCommandBuffer: cmdBuf
 *                                                                                imageDescriptor: d];
 *
 *                  // Now that all properties are configured properly, we can make the result state
 *                  // and call encode.
 *                  MPSState * __nullable destState = [kernel resultStateForSourceImage: source
 *                                                                         sourceStates: states
 *                                                                     destinationImage: dest];
 *
 *                  // This form of -encode will be declared by the MPSCNNKernel subclass
 *                  [kernel encodeToCommandBuffer: cmdBuf
 *                                    sourceImage: source
 *                               destinationState: destState
 *                               destinationImage: dest ];
 *
 *              Default: returns nil
 *
 *  @param      sourceImages        The MPSImage consumed by the associated -encode call.
 *  @param      sourceStates        The list of MPSStates consumed by the associated -encode call,
 *                                  for a batch size of 1.
 *  @param      destinationImage    The destination image for the encode call
 *  @return     The list of states produced by the -encode call for batch size of 1.
 *              When the batch size is not 1, this function will be called repeatedly unless
 *              -isResultStateReusedAcrossBatch returns YES. If  -isResultStateReusedAcrossBatch
 *              returns YES, then it will be called once per batch and the MPSStateBatch array will
 *              contain MPSStateBatch.length references to the same object.
 */
-(MPSState * __nullable) resultStateForSourceImages: (NSArray<MPSImage *> *__nonnull) sourceImages
                                       sourceStates: (NSArray <MPSState *> *__nullable) sourceStates
                                   destinationImage: (MPSImage *__nonnull) destinationImage
        MPS_SWIFT_NAME( resultState(sourceImages:sourceStates:destinationImage:));
-(MPSStateBatch * __nullable) resultStateBatchForSourceImages: (NSArray<MPSImageBatch *> * __nonnull) sourceImages
                                                 sourceStates: (NSArray<MPSStateBatch *> * __nullable) sourceStates
                                             destinationImage: (MPSImageBatch *__nonnull) destinationImage
        MPS_SWIFT_NAME( resultStateBatch(sourceImages:sourceStates:destinationImage:));


/*! @abstract   Allocate a temporary MPSState (subclass) to hold the results from a -encodeBatchToCommandBuffer... operation
 *  @discussion A graph may need to allocate storage up front before executing.  This may be
 *              necessary to avoid using too much memory and to manage large batches.  The function
 *              should allocate any MPSState objects that will be produced by an -encode call
 *              with the indicated sourceImages and sourceStates inputs. Though the states
 *              can be further adjusted in the ensuing -encode call, the states should
 *              be initialized with all important data and all MTLResource storage allocated.
 *              The data stored in the MTLResource need not be initialized, unless the ensuing
 *              -encode call expects it to be.
 *
 *              The MTLDevice used by the result is derived from the command buffer.
 *              The padding policy will be applied to the filter before this is called
 *              to give it the chance to configure any properties like MPSCNNKernel.offset.
 *
 *              CAUTION:
 *              The kernel must have all properties set to values that will ultimately be
 *              passed to the -encode call that writes to the state, before
 *              -resultStateForSourceImages:sourceStates:destinationImage: is called or behavior is undefined.
 *              Please note that -destinationImageDescriptorForSourceImages:sourceStates:destinationImage:
 *              will alter some of these properties automatically based on the padding policy.
 *              If you intend to call that to make the destination image, then you should
 *              call that before -resultStateForSourceImages:sourceStates:destinationImage:.  This will ensure the
 *              properties used in the encode call and in the destination image creation
 *              match those used to configure the state.
 *
 *              The following order is recommended:
 *
 *                  // Configure MPSCNNKernel properties first
 *                  kernel.edgeMode = MPSImageEdgeModeZero;
 *                  kernel.destinationFeatureChannelOffset = 128; // concatenation without the copy
 *                  ...
 *
 *                  // ALERT: will change MPSCNNKernel properties
 *                  MPSImageDescriptor * d = [kernel destinationImageDescriptorForSourceImage: source
 *                                                                               sourceStates: states];
 *                  MPSTemporaryImage * dest = [MPSTemporaryImage temporaryImageWithCommandBuffer: cmdBuf
 *                                                                                imageDescriptor: d];
 *
 *                  // Now that all properties are configured properly, we can make the result state
 *                  // and call encode.
 *                  MPSState * __nullable destState = [kernel temporaryResultStateForCommandBuffer: cmdBuf
 *                                                                                     sourceImage: source
 *                                                                                    sourceStates: states];
 *
 *                  // This form of -encode will be declared by the MPSCNNKernel subclass
 *                  [kernel encodeToCommandBuffer: cmdBuf
 *                                    sourceImage: source
 *                               destinationState: destState
 *                               destinationImage: dest ];
 *
 *              Default: returns nil
 *
 *  @param      commandBuffer       The command buffer to allocate the temporary storage against
 *                                  The state will only be valid on this command buffer.
 *  @param      sourceImage         The MPSImage consumed by the associated -encode call.
 *  @param      sourceStates        The list of MPSStates consumed by the associated -encode call,
 *                                  for a batch size of 1.
 *  @param      destinationImage    The destination image for the encode call
 *  @return     The list of states produced by the -encode call for batch size of 1.
 *              When the batch size is not 1, this function will be called repeatedly unless
 *              -isResultStateReusedAcrossBatch returns YES. If  -isResultStateReusedAcrossBatch
 *              returns YES, then it will be called once per batch and the MPSStateBatch array will
 *              contain MPSStateBatch.length references to the same object.
 */
-(MPSState * __nullable) temporaryResultStateForCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                                 sourceImages: (NSArray <MPSImage *> *__nonnull) sourceImage
                                                 sourceStates: (NSArray <MPSState *> *__nullable) sourceStates
                                             destinationImage: (MPSImage *__nonnull) destinationImage
    MPS_SWIFT_NAME( temporaryResultState(commandBuffer:sourceImages:sourceStates:destinationImage:));
-(MPSStateBatch * __nullable) temporaryResultStateBatchForCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                                           sourceImages: (NSArray <MPSImageBatch *> *__nonnull) sourceImage
                                                           sourceStates: (NSArray <MPSStateBatch *> *__nullable) sourceStates
                                                       destinationImage: (MPSImageBatch *__nonnull) destinationImage
    MPS_SWIFT_NAME( temporaryResultStateBatch(commandBuffer:sourceImages:sourceStates:destinationImage:));


/*! @abstract   Get a suggested destination image descriptor for a source image
 *  @discussion Your application is certainly free to pass in any destinationImage
 *              it likes to encodeToCommandBuffer:sourceImage:destinationImage,
 *              within reason. This is the basic design for iOS 10. This method
 *              is therefore not required.
 *
 *              However, calculating the MPSImage size and MPSCNNKernel properties
 *              for each filter can be tedious and complicated work, so this method
 *              is made available to automate the process. The application may
 *              modify the properties of the descriptor before a MPSImage is made from
 *              it, so long as the choice is sensible for the kernel in question.
 *              Please see individual kernel descriptions for restrictions.
 *
 *              The expected timeline for use is as follows:
 *
 *                1) This method is called:
 *                  a) The default MPS padding calculation is applied. It
 *                     uses the MPSNNPaddingMethod of the .padding property to
 *                     provide a consistent addressing scheme over the graph.
 *                     It creates the MPSImageDescriptor and adjusts the .offset
 *                     property of the MPSNNKernel. When using a MPSNNGraph, the
 *                     padding is set using the MPSNNFilterNode as a proxy.
 *
 *                  b) This method may be overridden by MPSCNNKernel subclass
 *                     to achieve any customization appropriate to the object type.
 *
 *                  c) Source states are then applied in order. These may modify the
 *                     descriptor and may update other object properties. See:
 *                      -destinationImageDescriptorForSourceImages:sourceStates:
 *                       forKernel:suggestedDescriptor:  This is the typical way
 *                      in which MPS may attempt to influence the operation of
 *                      its kernels.
 *
 *                  d) If the .padding property has a custom padding policy method
 *                      of the same name, it is called. Similarly, it may also adjust
 *                      the descriptor and any MPSCNNKernel properties. This is the
 *                      typical way in which your application may attempt to influence
 *                      the operation of the MPS kernels.
 *
 *                2) A result is returned from this method and the caller
 *                     may further adjust the descriptor and kernel properties
 *                     directly.
 *
 *                3) The caller uses the descriptor to make a new MPSImage to
 *                   use as the destination image for the -encode call in step 5.
 *
 *                4) The caller calls -resultStateForSourceImage:sourceStates:destinationImage:
 *                    to make any result states needed for the kernel. If there isn't
 *                    one, it will return nil. A variant is available to return a
 *                    temporary state instead.
 *
 *                5) a -encode method is called to encode the kernel.
 *
 *              The entire process 1-5 is more simply achieved by just calling an -encode...
 *              method that returns a MPSImage out the left hand sid of the method. Simpler
 *              still, use the MPSNNGraph to coordinate the entire process from end to end.
 *              Opportunities to influence the process are of course reduced, as (2) is no longer
 *              possible with either method. Your application may opt to use the five step method
 *              if it requires greater customization as described, or if it would like to estimate
 *              storage in advance based on the sum of MPSImageDescriptors before processing
 *              a graph. Storage estimation is done by using the MPSImageDescriptor to create
 *              a MPSImage (without passing it a texture), and then call -resourceSize. As long
 *              as the MPSImage is not used in an encode call and the .texture property is not
 *              invoked, the underlying MTLTexture is not created.
 *
 *              No destination state or destination image is provided as an argument to this
 *              function because it is expected they will be made / configured after this
 *              is called. This method is expected to auto-configure important object properties
 *              that may be needed in the ensuing destination image and state creation steps.
 *
 *  @param      sourceImages    A array of source images that will be passed into the -encode call
 *                              Since MPSCNNKernel is a unary kernel, it is an array of length 1.
 *  @param      sourceStates    An optional array of source states that will be passed into the -encode call
 *  @return     an image descriptor allocated on the autorelease pool
 */
-(MPSImageDescriptor*__nonnull) destinationImageDescriptorForSourceImages: (NSArray<MPSImage *> * __nonnull) sourceImages
                                                             sourceStates: (NSArray<MPSState *> * __nullable) sourceStates
                MPS_SWIFT_NAME( destinationImageDescriptor(sourceImages:sourceStates:));

@end


#endif /* MPSCNNKernel_h */

