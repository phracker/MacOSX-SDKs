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

@class MPSState;

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
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
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
 *              destination image MUST have at least destinationFeatureChannelOffset + N channels. Using a destination
 *              image with insufficient number of feature channels result in an error.
 *              E.g. if the MPSCNNConvolution outputs 32 channels, and destination has 64 channels, then it is an error to set
 *              destinationFeatureChannelOffset > 32.
 */
@property (readwrite, nonatomic) NSUInteger              destinationFeatureChannelOffset;

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

/*! @property   isBackwards
 *  @abstract   YES if the filter operates backwards.
 *  @discussion This influences how strideInPixelsX/Y should be interpreted. 
 *              Most filters either have stride 1 or are reducing, meaning that
 *              the result image is smaller than the original by roughly a factor
 *              of the stride.  A few "backward" filters (e.g unpooling) are intended
 *              to "undo" the effects of an earlier forward filter, and so 
 *              enlarge the image. The stride is in the destination coordinate frame
 *              rather than the source coordinate frame.
 */
@property(readonly, nonatomic) BOOL                     isBackwards
                    MPS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0));

/*! @property   padding
 *  @abstract   The padding method used by the filter
 *  @discussion This influences how the destination image is sized and how
 *              the offset into the source image is set.  It is used by the
 *              -encode methods that return a MPSImage from the left hand side.
 */
@property (readwrite, nonatomic, nonnull, retain) id <MPSNNPadding>    padding
                    MPS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0));

/*! @abstract   Method to allocate the result image for -encodeToCommandBuffer:sourceImage:
 *  @discussion Default: MPSTemporaryImage.defaultAllocator
 */
@property (readwrite, nonatomic, retain, nonnull) id <MPSImageAllocator> destinationImageAllocator
                    MPS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0));


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


/*!
 *  @abstract   Encode a MPSCNNKernel into a command Buffer.  The operation shall proceed out-of-place.
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
 *  @param          commandBuffer       The command buffer
 *  @param          sourceImage         A MPSImage to use as the source images for the filter.
 *  @result         A MPSImage or MPSTemporaryImage allocated per the destinationImageAllocator containing the output of the graph.
 *                  The offset property will be adjusted to reflect the offset used during the encode.
 *                  The returned image will be automatically released when the command buffer completes. If you want to
 *                  keep it around for longer, retain the image. (ARC will do this for you if you use it later.)
 */
-(MPSImage * __nonnull) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                  sourceImage: (MPSImage *  __nonnull) sourceImage
                MPS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
                MPS_SWIFT_NAME( encode(commandBuffer:sourceImage:));

@end


/*!
 *  @class      MPSCNNBinaryKernel
 *  @dependency This depends on Metal.framework
 *  @abstract   Describes a convolution neural network kernel.
 *  @discussion A MPSCNNKernel consumes two MPSImages, primary and secondary, and produces one MPSImage.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
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

/*! @property   kernelWidth
 *  @abstract   The width of the MPSCNNKernel filter window
 *  @discussion This is the horizontal diameter of the region read by the filter for each
 *              result pixel. If the MPSCNNKernel does not have a filter window, then
 *              1 will be returned.
 */
@property (readonly, nonatomic) NSUInteger              kernelWidth;

/*! @property   kernelHeight
 *  @abstract   The height of the MPSCNNKernel filter window
 *  @discussion This is the vertical diameter of the region read by the filter for each
 *              result pixel. If the MPSCNNKernel does not have a filter window, then
 *              1 will be returned.
 */
@property (readonly, nonatomic) NSUInteger              kernelHeight;

/*! @property   primaryStrideInPixelsX
 *  @abstract   The downsampling (or upsampling if a backwards filter) factor in the horizontal dimension
 *              for the primary source image
 *  @discussion If the filter does not do up or downsampling, 1 is returned.
 */
@property(readonly, nonatomic) NSUInteger               primaryStrideInPixelsX;

/*! @property   primaryStrideInPixelsY
 *  @abstract   The downsampling (or upsampling if a backwards filter) factor in the vertical dimension
 *              for the primary source image
 *  @discussion If the filter does not do up or downsampling, 1 is returned.
 */
@property(readonly, nonatomic) NSUInteger               primaryStrideInPixelsY;

/*! @property   secondaryStrideInPixelsX
 *  @abstract   The downsampling (or upsampling if a backwards filter) factor in the horizontal dimension
 *              for the secondary source image
 *  @discussion If the filter does not do up or downsampling, 1 is returned.
 */
@property(readonly, nonatomic) NSUInteger               secondaryStrideInPixelsX;

/*! @property   secondaryStrideInPixelsY
 *  @abstract   The downsampling (or upsampling if a backwards filter) factor in the vertical dimension
 *              for the secondary source image
 *  @discussion If the filter does not do up or downsampling, 1 is returned.
 */
@property(readonly, nonatomic) NSUInteger               secondaryStrideInPixelsY;

/*! @property   isBackwards
 *  @abstract   YES if the filter operates backwards.
 *  @discussion This influences how strideInPixelsX/Y should be interpreted.
 */
@property(readonly, nonatomic) BOOL                     isBackwards;

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


@end

#endif /* MPSCNNKernel_h */

