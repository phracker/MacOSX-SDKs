//
//  MPSNeuralNetworkTypes.h
//  MPS
//
//  Created by Ian Ollmann on 8/20/16.
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef MPSNeuralNetworkTypes_h
#define MPSNeuralNetworkTypes_h

#import <MPSCore/MPSCoreTypes.h>


#ifdef __cplusplus
extern "C" {
#endif
    
@class MPSImage;
@class MPSImageDescriptor;
@class MPSState;
@class MPSKernel;
@class MPSCNNKernel;
    
/*! @enum       MPSCNNConvolutionFlags
 *  @abstract   Options used to control how kernel weights are stored and used in the CNN kernels.
 *              For future expandability.
 */
#if defined(DOXYGEN)
typedef enum MPSCNNConvolutionFlags
#else
typedef NS_ENUM(NSUInteger, MPSCNNConvolutionFlags)
#endif
{
    /*! Use default options */
    MPSCNNConvolutionFlagsNone      MPS_ENUM_AVAILABLE_STARTING_BUT_DEPRECATED( "Use the Convolution -init method with a MPSCNNConvolutionDataSource instead.", ios(10.0, 11.0), tvos(10.0, 11.0)) MPS_SWIFT_NAME(none)  = 0,
}
#if defined(DOXYGEN)
    MPSCNNConvolutionFlags
#endif
;

#pragma mark -
#pragma mark MPSCNNBinaryConvolutionFlags
    
    /*! @enum       MPSCNNBinaryConvolutionFlags
     *  @abstract   Options used to control CNN Binary convolution kernels.
     */
#if defined(DOXYGEN)
typedef enum MPSCNNBinaryConvolutionFlags
#else
typedef NS_ENUM(NSUInteger, MPSCNNBinaryConvolutionFlags)
#endif
{
    /*! Use default in binary convolution options */
    MPSCNNBinaryConvolutionFlagsNone            MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))  MPS_SWIFT_NAME(none)  = 0,
    /*! Scale the binary convolution operation using the beta-image option as detailed in MPSCNNBinaryConvolution */
    MPSCNNBinaryConvolutionFlagsUseBetaScaling  MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))   = 1 << 0,
}
#if defined(DOXYGEN)
    MPSCNNBinaryConvolutionFlags
#endif
    ;
    
    
    /*! @enum       MPSCNNBinaryConvolutionType
     *  @abstract   Defines what operations are used to perform binary convolution
     */
#if defined(DOXYGEN)
typedef enum MPSCNNBinaryConvolutionType
#else
typedef NS_ENUM(NSUInteger, MPSCNNBinaryConvolutionType)
#endif
{
    /*! Otherwise a normal convolution operation, except that the weights are binary values */
    MPSCNNBinaryConvolutionTypeBinaryWeights    MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))  MPS_SWIFT_NAME(binaryWeights)  = 0,
    /*! Use input image binarization and the XNOR-operation to perform the actual convolution - See MPSCNNBinaryConvolution for details  */
    MPSCNNBinaryConvolutionTypeXNOR  MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0)),
    /*! Use input image binarization and the AND-operation to perform the actual convolution - See MPSCNNBinaryConvolution for details */
    MPSCNNBinaryConvolutionTypeAND  MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0)),
}
#if defined(DOXYGEN)
    MPSCNNBinaryConvolutionType
#endif
;
    
/*! @enum        MPSNNConvolutionAccumulatorPrecisionOption
 *  @memberof    MPSCNNConvolution
 *  @abstract    Options set on MPSCNNConvolution objects to control precision of accumulator used.
 *  @discussion  Convolution operation involves sequence of multiply-accumulate operation i.e.
 *                         accumulator = imageData * weight + accumulator
 *               Default MPSDataType for both imageData and weight is MPSDataTypeFloat16 i.e. half precision float.
 *               Multiply-accumulate result (imageData * weight + accumulator) needs to be rounded to precision of accumulator.
 *               MPS allows either half float or full float accumulator type using appropriate flags.
 *               The choice of accmulator precision should be based on how much precision loss application can sustain
 *               without significanly affecting accuracy of network.
 *               The default accumulator precision is half (MPSNNConvolutionAccumulatorPrecisionOptionFloat).
 *               If accumulation of computational rounding error in the result is excessive,
 *               user can specify MPSNNConvolutionAccumulatorPrecisionOptionFloat for full float accumulator.
 *               Note that on some devices, which do not provide IEEE compliant half arithmetic (A10 and older), half precision
 *               accumulator can cause excessive loss of precision causing severe loss in accuracy. MPS automatically
 *               ignores this option on those hardware and uses full float accumulator. On hardware that does support IEEE
 *               compliant half arithmetic and half accumulator does meet applications accuracy requirements, it can provide
 *               significant performance benefits.
 */
    
#if defined(DOXYGEN)
typedef enum MPSNNConvolutionAccumulatorPrecisionOption
#else
typedef NS_OPTIONS(NSUInteger, MPSNNConvolutionAccumulatorPrecisionOption)
#endif
{
    /*! Set accumulator type to half precision float. */
    MPSNNConvolutionAccumulatorPrecisionOptionHalf        MPS_ENUM_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3)) MPS_SWIFT_NAME(half) = 0U,
        
    /*! Set accumulator type to single precision float. */
    MPSNNConvolutionAccumulatorPrecisionOptionFloat        MPS_ENUM_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3)) MPS_SWIFT_NAME(float)  = 1U << 0,
        
};

/*! @enum       MPSNNTrainingStyle
 *  @abstract   Options that control how the MPSNNGraph nodes are trained
 *  @discussion Nodes tha are trainable conform to the MPSNNTrainableNode protocol.
 *              This adds a MPSNNTrainingStyle property to the node that may be used
 *              to influence when and where the neural network training paramers such as
 *              convolution weights are updated. */
#if defined(DOXYGEN)
typedef enum MPSNNTrainingStyle
#else
typedef NS_OPTIONS(NSUInteger, MPSNNTrainingStyle)
#endif
{
    /*! Do not train this node, for example in transfer learning */
    MPSNNTrainingStyleUpdateDeviceNone  MPS_ENUM_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))  MPS_SWIFT_NAME(UpdateDeviceNone) = 0,

    /*! The weight update pass will be called in a command buffer completion callback, with a nil command buffer */
    MPSNNTrainingStyleUpdateDeviceCPU   MPS_ENUM_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3)) = 1,

    /*! The weight update pass will be called immediately after the gradient pass is encoded, with a nonnull command buffer */
    MPSNNTrainingStyleUpdateDeviceGPU   MPS_ENUM_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3)) = 2,
}
#if defined(DOXYGEN)
MPSNNTrainingStyle
#endif
;

#if defined(DOXYGEN)
    typedef enum MPSCNNBatchNormalizationFlags
#else
    typedef NS_OPTIONS(NSUInteger, MPSCNNBatchNormalizationFlags)
#endif
    {
        /*! Default Settings */
        MPSCNNBatchNormalizationFlagsDefault  MPS_ENUM_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3))  MPS_SWIFT_NAME(Default) = 0,
        
        /*! Statistics are calculated if another node consumes the gradient node (training). The data source is used otherwise. */
        MPSCNNBatchNormalizationFlagsCalculateStatisticsAutomatic   MPS_ENUM_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3)) MPS_SWIFT_NAME(CalculateStatisticsAutomatic) = MPSCNNBatchNormalizationFlagsDefault,

        /*! Statistics are calculated always */
        MPSCNNBatchNormalizationFlagsCalculateStatisticsAlways      MPS_ENUM_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3)) = 1,

        /*! Statistics are never calculated. Predefined values from the data source are used instead */
        MPSCNNBatchNormalizationFlagsCalculateStatisticsNever       MPS_ENUM_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3)) = 2,

        /*! Bits used for  MPSCNNBatchNormalizationFlagsCalculateStatistics*/
        MPSCNNBatchNormalizationFlagsCalculateStatisticsMask        MPS_ENUM_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), tvos(11.3)) = 3,
    }
#if defined(DOXYGEN)
    MPSCNNBatchNormalizationFlags
#endif
    ;

    
/*! @enum       MPSNNPaddingMethod
 *  @abstract   How to pad MPSNNGraph image nodes
 *  @discussion The MPSNNGraph must make automatic decisions about how big to make the result
 *              of each filter node. This is typically determined by a combination of input
 *              image size, size of the filter window (e.g. convolution weights), filter stride,
 *              and a description of how much extra space beyond the edges of the image to allow 
 *              the filter read. By knowing the properties of the filter, we can then infer 
 *              the size of the result image.  Most of this information is known to the MPSNNGraph
 *              as part of its normal operation. However, the amount of padding to add and where
 *              to add it is a matter of choice left to you, the developer. Different neural network
 *              frameworks such as TensorFlow and Caffe make different choices here.  Depending on where
 *              your network was trained, you will need to adjust the policies used by MPS during inference. 
 *              In the event that the padding method is not simply described by this enumeration, you may
 *              provide you own custom policy definition by overriding the -destinationImageDescriptorForSourceImages:
 *              sourceStates:forKernel:suggestedDescriptor: method in a custom MPSNNPadding child 
 *              class.
 *
 *              Common values that influence the size of the result image by adjusting the amount of 
 *              padding added to the source images:
 *                  - MPSNNPaddingMethodSizeValidOnly  Result values are only produced for the area that
 *                                                     is guaranteed to have all of its input values
 *                                                     defined (i.e. not off the edge).  This produces
 *                                                     the smallest result image.
 *                  - MPSNNPaddingMethodSizeSame       The result image is the same size as the input
 *                                                     image. If the stride is not 1, then the result
 *                                                     is scaled accordingly.  
 *                  - MPSNNPaddingMethodSizeFull       Result values are produced for any position for which
 *                                                     at least one input value is defined (i.e. not off
 *                                                     the edge)
 *                  - MPSNNPaddingMethodCustom     The sizing and centering policy is given by the
 *                                                     [MPSNNPadding destinationImageDescriptorForSourceImages:
 *                                                     sourceStates:forKernel:suggestedDescriptor:]
 *
 *              Except possibly when MPSNNPaddingMethodCustom is used, the area within the source 
 *              image that is read will be centered on the source image. Even so, at times the area can
 *              not be perfectly centered because the source image has odd size and the region read
 *              has even size, or vice versa. In such cases, you may use the following values to 
 *              select where to put the extra padding:
 *
 *                  - MPSNNPaddingMethodAddRemainderToTopLeft     Leftover padding is added to the top or left
 *                                                                side of image as appropriate.
 *                  - MPSNNPaddingMethodAddRemainderToBottomRight Leftover padding is added to the bottom or right
 *                                                                side of image as appropriate.
 *
 *              Here again, different external frameworks may use different policies. 
 *
 *              In some cases, Caffe intoduces the notion of a region beyond the padding which is invalid. 
 *              This can happen when the padding is set to a width narrower than what is needed for a destination
 *              size. In such cases, MPSNNPaddingMethodExcludeEdges is used to adjust normalization factors
 *              for filter weights (particularly in pooling) such that invalid regions beyond the padding are 
 *              not counted towards the filter area.  Currently, only pooling supports this feature. Other filters
 *              ignore it.
 *
 *              The MPSNNPaddingMethodSize and a MPSNNPaddingMethodAddRemainder policy always appear together
 *              in the MPSNNPaddingMethod. There is no provision for a MPSNNPaddingMethodSize without a remainder
 *              policy or vice versa. It is in practice used as a bit field.
 *
 *              Most MPSNN filters are considered forward filters. Some (e.g. convolution transpose)
 *              are considered reverse filters. For the reverse filters, the image stride is measured in destination
 *              values rather than source values and has the effect of enlarging the image rather than reducing it.
 *              When a reverse filter is used to "undo" the effects of a forward filter, the MPSNNPaddingMethodSize should
 *              be the opposite of the forward MPSNNPaddingMethod.  For example, if the forward filter used 
 *              MPSNNPaddingMethodSizeValidOnly | MPSNNPaddingMethodAddRemainderToTopLeft, the reverse filter should use
 *              MPSNNPaddingMethodSizeFull | MPSNNPaddingMethodAddRemainderToTopLeft. Some consideration of the geometry 
 *              of inputs and outputs will reveal why this is so. It is usually not important to adjust the centering
 *              method because the size of the reverse result generally doesn't suffer from centering asymmetries. That is:
 *              the size would usually be given by:
 *              @code
 *              static int DestSizeReverse( int sourceSize, int stride, int filterWindowSize, Style style ) {
 *                  return (sourceSize-1) * stride + 1 + style  * (filterWindowSize-1);  // style = {-1,0,1} for valid-only, same, full
 *              }
 *              @endcode
 *              so the result size is exactly the one needed for the source size and there are no centering problems.
 *              In some cases where the reverse pass is intended to completely reverse a forward pass, the MPSState
 *              object produced by the forward pass should be used to determine the size of the reverse pass result
 *              image.
 *
 *              Tensorflow does not appear to provide a full padding method, but instead appears to use its valid-only
 *              padding mode for reverse filters to in effect achieve what is called MPSNNPaddingMethodSizeFull here.
 *
 *              MPSGetPaddingPolicy() is provided as a convenience to make shorter work of MPSNNPaddingMethods and policies.
 *
 *              Walkthrough of operation of padding policy:
 *              ===========================================
 *                  Most MPSCNNKernels have two types of -encode calls. There is one for which you must pass in
 *              a preallocated MPSImage to receive the results.  This is for manual configuration. It assumes you know
 *              what you are doing, and asks you to correctly set a diversity of properties to correctly position image
 *              inputs and size results. It does not use the padding policy. You must size the result correctly, set the
 *              clipRect, offset and other properties as needed yourself.
 *                  Layered on top of that is usually another flavor of -encode call that returns a destination image 
 *              instead from the left hand side of the function. It is designed to automatically configure itself based
 *              on the MPSCNNKernel.paddingPolicy. When this more automated -encode... method is called, it invokes a 
 *              method in the MPSKernel that looks at the MPSNNPaddingMethod bitfield of the policy. Based on the 
 *              information therein and the size of the input images and other filter properties, it determines the size 
 *              of the output, sets the offset property, and returns an appropriate MPSImageDescriptor for the destination 
 *              image.
 *                  If you set the MPSNNPaddingMethodCustom bit in the MPSNNPaddingMethod, then the MPSNNPadding
 *              -destinationImageDescriptorForSourceImages:sourceStates:forKernel:suggestedDescriptor: method
 *              is called. The MPSImageDescriptor prepared earlier is passed in as the last parameter. You can
 *              use this descriptor or modify as needed.  In addition, you can adjust any properties of the MPSKernel
 *              with which it will be used. If, for example, the descriptor is not the right MPSFeatureChannelFormat, you
 *              can change it, or make your own MPSImageDescriptor based on the one handed to you. This is your opportunity
 *              to customize the configuration of the MPSKernel. In some cases (e.g. MPSNNDefaultPadding.paddingForTensorflowAveragePooling
 *              you might change other properties such as the filter edging mode, or adjust the offset that was already
 *              set for you. When the kernel is fully configured, return the MPSImageDescriptor.
 *                  The MPSImageDescriptor is then passed to the MPSCNNKernel.destinationImageAllocator to allocate
 *              the image. You might provide such an allocator if you want to use your own custom MTLHeap rather 
 *              than the MPS internal heap. The allocator can be set either directly in the MPSCNNKernel or through the 
 *              MPSNNImageNode.allocator property. 
 *                  It is intended that most of the time, default values for padding method and destination image allocator
 *              should be good enough. Only minimal additional configuration should be required, apart from occasional
 *              adjustments to set the MPSNNPaddingMethod when something other than default padding for the object is
 *              needed.  If you find yourself encumbered by frequent adjustments of this kind, you might find it 
 *              to your advantage to subclass MPSNNFilterNodes or MPSCNNKernels to adjust the default padding policy and
 *              allocator at initialization time.
 *
 *              tensorFlowSame = MPSNNPaddingMethodAddRemainderToBottomRight | MPSNNPaddingMethodAlignCentered | MPSNNPaddingMethodSizeSame
 *
 *              In some cases, a custom padding policy may be preferable to a custom MPSImageAllocator for adjusting MPSImage
 *              characteristics. The MPS provided MPSImageAllocators are more efficient at allocating image batches than
 *              naive code, and should be used when possible. However, custom padding policies may prevent the MPSNNGraph
 *              from fusing away nodes involving images created by the padding policy because it doesn't know what the
 *              custom padding policy does. If the changes made by the padding policy modify to the MPSImageDescriptor
 *              alone (and not, critically, the MPSKernel properties or image dimensions) then it may be acceptable to pass
 *              MPSNNPaddingMethodCustomWhitelistForNodeFusion, which allows the fusion to proceed even with a custom
 *              padding policy. In usage of MPSNNPaddingMethodCustomWhitelistForNodeFusion, you are guaranteeing to MPS
 *              that it can fuse the node with an adjacent filter node if it can. It makes no further checks.   You can
 *              get a detailed printout of graph optimizations including reasons why they didn't happen by setting the
 *              MPS_LOG_INFO environment variable.
 *
 *              What happens when my node is fused?
 *                  In this case, the image described by the padding policy is never made, the custom padding policy method
 *              -destinationImageDescriptorForSourceImages:sourceStates:forKernel:suggestedDescriptor: is never called
 *              and data is passed directy from one MPSKernel to another without precision loss. This generally only happens
 *              for MPSKernels that do not change the size of the image, for example batch normalization, neuron filters,
 *              and gradients of the same.  For such filters, all padding method size, remainder and alignment options
 *              produce identical results and so can be ignored. Only the custom padding method has the capability of changing
 *              the results, for example by changing the destination size or MPSCNNKernel.offset, which is why it must be
 *              explicitly whitelisted away if fusion is to occur.
 */
    
    
#if defined(DOXYGEN)
    typedef enum MPSNNPaddingMethod
#else
    typedef NS_OPTIONS(NSUInteger, MPSNNPaddingMethod)
#endif
    {
        // The first two bits describe how to position the region read within the source image
        MPSNNPaddingMethodAlignCentered                  MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0)) MPS_SWIFT_NAME(centered)  = 0,    ///< Extra padding pixels are distributed as evenly as possible to all sides
        MPSNNPaddingMethodAlignTopLeft                   MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))  = 1,    ///< Extra padding pixels appear on top and left sides
        MPSNNPaddingMethodAlignBottomRight               MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))  = 2,    ///< Extra padding pixels appear on the bottom and right sides
        MPSNNPaddingMethodAlign_reserved                 MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))  = 3,    ///< Extra padding pixels are not defined.
        MPSNNPaddingMethodAlignMask = MPSNNPaddingMethodAlign_reserved,

        
        // The next two bits describe which sides the extra padding goes in the case where the total amount of padding
        // in a dimension is not an even number and the alignment is centered. This typically happens when the filter window size is even.
        MPSNNPaddingMethodAddRemainderToTopLeft          MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0)) MPS_SWIFT_NAME(topLeft) = 0UL << 2,     ///< Extra padding pixels are accumulated to top and left sides
        MPSNNPaddingMethodAddRemainderToTopRight         MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))  = 1UL << 2,
        MPSNNPaddingMethodAddRemainderToBottomLeft       MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))  = 2UL << 2,
        MPSNNPaddingMethodAddRemainderToBottomRight      MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))  = 3UL << 2,     ///< Extra padding pixels are accumulated to bottom and right sides
        MPSNNPaddingMethodAddRemainderToMask = MPSNNPaddingMethodAddRemainderToBottomRight,
        
        // The next thirteen bits describe the size of the padding area
        MPSNNPaddingMethodSizeValidOnly                 MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0)) MPS_SWIFT_NAME(validOnly) = 0,               ///< The result is the largest image for which *all* source pixels are valid for result pixels
        MPSNNPaddingMethodSizeSame                      MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))  = 1UL << 4,        ///< The result is the same size as the input image (before strides)
        MPSNNPaddingMethodSizeFull                      MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))  = 2UL << 4,        ///< The result is the largest image for which *any* source pixel is valid for result pixels
        MPSNNPaddingMethodSize_reserved                 MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))  = 3UL << 4,
        MPSNNPaddingMethodCustomWhitelistForNodeFusion  MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), tvos(12.0))  = (1UL << 13),   ///< By itself, MPSNNPaddingMethodCustom will inhibit automatic fusion between nodes producing and consuming the image described by the padding policy. MPSNNPaddingMethodCustomWhitelistForNodeFusion signals that the custom method is benign and fusion may go ahead.
        MPSNNPaddingMethodCustom                        MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))  = (1UL << 14),   ///< Use destinationImageDescriptorForSourceImages:sourceStates:forKernel:suggestedDescriptor: to calculate padding and offset.
        MPSNNPaddingMethodSizeMask                      MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))  = 0x7f0,

        /*! The caffe framework constrains the average pooling area to the limits of the padding area in cases
         * where a pixel would read beyond the padding area. Set this bit for Caffe emulation with average pooling.
         */
        MPSNNPaddingMethodExcludeEdges     MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))  = (1UL << 15),
    }
#if defined(DOXYGEN)
    MPSNNPaddingMethod
#endif
;

    
/*! @protocol   MPSNNPadding
 *  @abstract   A method to describe how MPSCNNKernels should pad images when data outside the image is needed
 *  @discussion Different (non-Apple) CNN frameworks have different policies for how to size the result
 *              of a CNN filter and what padding to add around the edges.  Some filters such
 *              as pooling and convolution read from neighboring feature channel (pixel) values.
 *              Four predefined MPSPaddingMethods are available: MPSNNPaddingMethodValidOnly,
 *              MPSNNPaddingMethodFull, MPSNNPaddingMethodSameTL, MPSNNPaddingMethodSameBR. You
 *              may also implement your own padding definition with a block that conforms
 *              to this prototype.
 */
@protocol MPSNNPadding <NSObject, NSSecureCoding>
    
    @required
    /*! @abstract   Get the preferred padding method for the node */
    -(MPSNNPaddingMethod) paddingMethod;
    
    @optional
    /*! A human readable string that describes the padding policy. Useful for verbose debugging support. */
    -(NSString*__nonnull) label;        // FIXME:  to be made @required
    
    /*! @abstract       Determine padding and sizing of result images
     *  @discussion     A MPSNNPaddingMethod must both return a valid MPSImageDescriptor
     *                  and set the MPSKernel.offset to the correct value.  This is a 
     *                  required feature if the MPSNNPaddingMethodCustom bit is set in
     *                  the paddingMethod.
     *
     *                  Some code that may prove helpful:
     *
     *                  @code
     *                  const int centeringPolicy = 0;  // When kernelSize is even: 0 pad bottom right. 1 pad top left.    Centers the kernel for even sized kernels.
     *
     *                  typedef enum Style{
     *                      StyleValidOnly = -1,
     *                      StyleSame = 0,
     *                      StyleFull = 1
     *                  }Style;
     *
     *                  // Typical destination size in one dimension for forward filters (most filters)
     *                  static int DestSize( int sourceSize, int stride, int filterWindowSize, Style style ){
     *                      sourceSize += style * (filterWindowSize - 1);       // adjust how many pixels we are allowed to read
     *                      return (sourceSize + stride - 1) / stride;          // sourceSize / stride, round up
     *                  }
     *
     *                  // Typical destination size in one dimension for reverse filters (e.g. convolution transpose)
     *                  static int DestSizeReverse( int sourceSize, int stride, int filterWindowSize, Style style ){
     *                      return (sourceSize-1) * stride +        // center tap for the last N-1 results. Take stride into account
     *                              1 +                             // center tap for the first result
     *                              style * (filterWindowSize-1);   // add or subtract (or ignore) the filter extent
     *                  }
     *
     *                  // Find the MPSOffset in one dimension
     *                  static int Offset( int sourceSize, int stride, int filterWindowSize, Style style ){
     *                      // The correction needed to adjust from position of left edge to center per MPSOffset definition
     *                      int correction = filterWindowSize / 2;
     *
     *                      // exit if all we want is to start consuming pixels at the left edge of the image.
     *                      if( 0 )
     *                          return correction;
     *
     *                      // Center the area consumed in the source image:
     *                      // Calculate the size of the destination image
     *                      int destSize = DestSize( sourceSize, stride, filterWindowSize, style ); // use DestSizeReverse here instead as appropriate
     *
     *                      // calculate extent of pixels we need to read in source to populate the destination
     *                      int readSize = (destSize-1) * stride + filterWindowSize;
     *
     *                      // calculate number of missing pixels in source
     *                      int extraSize = readSize - sourceSize;
     *
     *                      // number of missing pixels on left side
     *                      int leftExtraPixels = (extraSize + centeringPolicy) / 2;
     *
     *                      // account for the fact that the offset is based on the center pixel, not the left edge
     *                      return correction - leftExtraPixels;
     *                  }
     *                  @endcode
     *
     *  @param          sourceImages        The list of source images to be used
     *  @param          sourceStates        The list of source states to be used
     *  @param          kernel              The MPSKernel the padding method will be applied to. Set the kernel.offset
     *  @param          inDescriptor        MPS will prepare a starting guess based on the padding policy (exclusive of
     *                                      MPSNNPaddingMethodCustom) set for the object. You should adjust the offset 
     *                                      and image size accordingly. It is on an autoreleasepool.
     *
     *  @return         The MPSImageDescriptor to use to make a MPSImage to capture the results from the filter. 
     *                  The MPSImageDescriptor is assumed to be on an autoreleasepool. Your method must also set the
     *                  kernel.offset property.
     */
    -(MPSImageDescriptor * __nonnull) destinationImageDescriptorForSourceImages: (NSArray <MPSImage *> *__nonnull) sourceImages
                                                                   sourceStates: (NSArray <MPSState *> * __nullable) sourceStates
                                                                      forKernel: (MPSKernel * __nonnull) kernel
                                                            suggestedDescriptor: (MPSImageDescriptor * __nonnull) inDescriptor;

    /*! @abstract   Make a "inverted" padding policy suitable for a training gradient pass.  */
    -(instancetype __nullable) inverse MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3));

@end

/*! @abstract   This class provides some pre-rolled padding policies for common tasks
 *  @discussion You are, of course, welcome to write your own class that conforms to
 *              The MPSNNPadding protocol and use that instead.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSNNDefaultPadding : NSObject <MPSNNPadding>

/*! @abstract   Fetch a well known object that implements a non-custom padding method
 *  @discussion For custom padding methods, you will need to implement an object that conforms
 *              to the full MPSNNPadding protocol, including NSSecureCoding.
 *  @param      method  A MPSNNPaddingMethod
 *  @return     An object that implements <MPSNNPadding> for use with MPSNNGraphNodes.
 */
+ (instancetype __nonnull) paddingWithMethod: (MPSNNPaddingMethod) method;

/*! @abstract       A padding policy that attempts to reproduce TensorFlow behavior for average pooling
 *  @discussion     Most TensorFlow padding is covered by the standard MPSNNPaddingMethod encodings.
 *                  You can use +paddingWithMethod to get quick access to MPSNNPadding objects, when
 *                  default filter behavior isn't enough. (It often is.)  However, the edging for
 *                  max pooling in TensorFlow is a bit unusual.
 *
 *                  This padding method attempts to reproduce TensorFlow padding for average pooling.
 *                  In addition to setting MPSNNPaddingMethodSizeSame | MPSNNPaddingMethodAlignCentered |
 *                  MPSNNPaddingMethodAddRemainderToBottomRight, it also configures the filter to run with
 *                  MPSImageEdgeModeClamp, which (as a special case for average pooling only), normalizes the
 *                  sum of contributing samples to the area of valid contributing pixels only.
 *
 *                  @code
 *                      // Sample implementation for the tensorflowPoolingPaddingPolicy returned
 *                       -(MPSNNPaddingMethod) paddingMethod{ return MPSNNPaddingMethodCustom | MPSNNPaddingMethodSizeSame; }
 *
 *                       -(MPSImageDescriptor * __nonnull) destinationImageDescriptorForSourceImages: (NSArray <MPSImage *> *__nonnull) sourceImages
 *                                                                                      sourceStates: (NSArray <MPSState *> * __nullable) sourceStates
 *                                                                                         forKernel: (MPSKernel * __nonnull) kernel
 *                                                                               suggestedDescriptor: (MPSImageDescriptor * __nonnull) inDescriptor
 *                       {
 *
 *                          ((MPSCNNKernel *)kernel).edgeMode = MPSImageEdgeModeClamp;
 *
 *                          return inDescriptor;
 *                       }
 *                  @endcode
 */
+ (instancetype __nonnull) paddingForTensorflowAveragePooling MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3));  // same size centering mode

/*! @abstract Typical pooling padding policy for valid only mode */
+ (instancetype __nonnull) paddingForTensorflowAveragePoolingValidOnly  MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), tvos(11.3));

/*! @abstract  Human readable description of what the padding policy does */
-(NSString * __nonnull) label;

@end
   
/*! @abstract   MPSStates conforming to this protocol contain information about a image size elsewhere in the graph
 *  @discussion In some graphs a sequence of operations are done, then they are undone ins a series of 'reverse' 
 *              operations. Examples might be pooling vs pooling gradient / upsampling,  or convolution vs. convolution transpose.
 *              In such cases, the 'reverse' pass generally is converting from a smaller image to a larger image,
 *              and there is insufficient information to do this correctly. Several answers exist and we don't know
 *              which is correct.
 *
 *              As an example, consider trying to 'undo' integer division with a multiplication. The expression c = a/b 
 *              is incomplete because there is also a remainder, which may constitute information lost. If we want to 
 *              reconstitute a based on c and b, we need to use a = c * b + remainder, not just a = c*b.  Similarly, when
 *              undoing a downsizing operation, we need the original size to find which answer in the range of
 *              a = c*b + [0,b-1] is the right one. */
@protocol MPSImageSizeEncodingState <NSObject>
    /*! @abstract   The width of the source image passed to MPSCNNConvolution encode call. */
    @property(readonly, nonatomic) NSUInteger       sourceWidth;
    
    /*! @abstract   The height of the source image passed to MPSCNNConvolution encode call. */
    @property(readonly, nonatomic) NSUInteger       sourceHeight;
    
@end
    
#ifdef __cplusplus
}
#endif

#endif /* MPSNeuralNetworkTypes_h */
