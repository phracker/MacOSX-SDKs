//
//  MPSNDArrayMultiaryKernel.h
//  MPSNDArray
//
//  Created by Ian Ollmann on 12/20/18.
//  Copyright © 2018 Apple. All rights reserved.
//

#ifndef MPSNDArrayKernel_h
#define MPSNDArrayKernel_h

#include <MPSCore/MPSKernel.h>
#include <MPSCore/MPSNDArray.h>
#include <MPSCore/MPSState.h>
#include <MPSNDArray/MPSNDArrayTypes.h>


MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSNDArrayMultiaryBase : MPSKernel

/*! @abstract   Read offsets to use when addressing a source NDArray
 *  @discussion The coordinate of the position read from this source array which is
 *              used to calculate the result value at [0,0,0,....]
 *              If the position read is actually a contiguous region (e.g. the area covered by
 *              a convolution kernel) then this is the center of that region, rounded down, for
 *              each dimension.
 *  @param      sourceIndex   The index of the source MPSNDArray to which the list of offsets is applied */
-(MPSNDArrayOffsets) offsetsAtSourceIndex: (NSUInteger) sourceIndex;

/*! @abstract   The edge mode used for each source NDArray
 *  @param      sourceIndex   The index of the source image
 *  @return     The MPSImageEdgeMode for that image */
-(MPSImageEdgeMode) edgeModeAtSourceIndex: (NSUInteger) sourceIndex;

/*! @abstract   Get the diameters of the point spread function (PSF) in each dimension
 *  @param      sourceIndex     The MPSNDArrayMultiaryKernel source NDArray to which the kernel will be applied
 *  @return     A list of kernel diameters in each dimension */
-(MPSNDArraySizes) kernelSizesForSourceIndex: (NSUInteger) sourceIndex;

/*! @abstract   Return the downsampling ratio for the kernel in each dimension
 *  @discussion If the filter is a "backwards" filter such as a gradient filter
 *              or convolution transpose, then this is the upsampling ratio and
 *              zeros are inserted in the result.
 *  @param      sourceIndex The index of the source for which the strides apply
 *  @return     The strides from one destination sample to the next in each
 *              dimension of the corresponding source NDArray   */
-(MPSNDArrayOffsets) stridesForSourceIndex: (NSUInteger) sourceIndex;

/*! @abstract   Get the kernel dilation rate for each dimension
 *  @param      sourceIndex The index of the source image for which this applies
 *  @return     The kernel dilation rate for each dimension. */
-(MPSNDArraySizes) dilationRatesForSourceIndex: (NSUInteger) sourceIndex;

/*! @abstract   Method to allocate the result image for -encodeToCommandBuffer:sourceImage:
 *  @discussion Default: MPSTemporaryImage.defaultAllocator  */
@property (readwrite, nonatomic, retain, nonnull) id <MPSNDArrayAllocator> destinationArrayAllocator;

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;


/*! @abstract   Initialize a MPSNDArrayMultiaryKernel
 *  @param      device  The device on which the kernel will run
 *  @param      count   The maximum number of NDArrays read by the kernel
 *  @return     A valid MPSNDArrayMultiaryKernel, or nil if allocation failure. */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           sourceCount: (NSUInteger) count NS_DESIGNATED_INITIALIZER;

/*! @abstract   Initialize a MPSNDArrayMultiaryKernel from a NSCoder
 *  @param      coder   The NSCoder that contains the serialized object
 *  @param      device  The device on which the kernel will run
 *  @return     A valid MPSNDArrayMultiaryKernel, or nil if allocation failure. */
-(nonnull instancetype) initWithCoder: (NSCoder*__nonnull) coder
                               device: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*! @abstract   Initialize a MPSNDArrayMultiaryKernel from a NSCoder
 *  @param      coder   The NSCoder that contains the serialized object */
-(void) encodeWithCoder: (NSCoder * __nonnull) coder;

/*! @abstract   Create a copy with
 *  @param      zone    The NSZone in which to allocate the MPSNDArrayMultiaryKernel object
 *  @param      device  The device on which the new kernel will run. Pass nil for same device.
 *  @return     A valid MPSNDArrayMultiaryKernel, or nil if allocation failure. */
-(nonnull instancetype) copyWithZone: (NSZone*__nullable) zone
                              device: (nullable id <MTLDevice>) device;

-(MPSState * __nullable) resultStateForSourceArrays: (NSArray <MPSNDArray *> * __nonnull) sourceArrays
                                       sourceStates: (NSArray <MPSState *> *__nullable) sourceStates
                                   destinationArray: (MPSNDArray *__nonnull) destinationArray;

/*! @abstract   Return a descriptor suitable for allocating a NSArray to receive the result
 *  @discussion The object properties (kernelSize, offsets, edgeMode, etc.) should be properly
 *              configured as if the -encode call was about to be made, before this method is
 *              called. Those properties may affect the results.
 *  @param      sources     The list of sources passed into the -encode call
 *  @param      state       The source state object, if any passed to the -encode call
 *  @return     a valid MPSNDArrayDescriptor that may be used to create a MPSNDArray to used to
 *              hold the results of this kernel.    */
-(MPSNDArrayDescriptor * __nonnull) destinationArrayDescriptorForSourceArrays: (NSArray <MPSNDArray*> * __nonnull)  sources
                                                                  sourceState: (MPSState * __nullable) state;

@end


MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSNDArrayMultiaryKernel : MPSNDArrayMultiaryBase

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           sourceCount: (NSUInteger) count NS_DESIGNATED_INITIALIZER;

/* NSSecureCoding support */
-(nonnull instancetype) initWithCoder: (NSCoder*__nonnull) coder
                               device: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

// Inference encode calls
/*! @abstract   Encode a simple inference NDArray kernel and return a NDArray to hold the result
 *  @param      cmdBuf          The command buffer into which to encode the kernel
 *  @param      sourceArrays    The list of sources for the filter in a NSArray.
 *                              Ordering to be defined by subclass
 *  @result     A newly allocated MPSNDArray that will contain the result of the calculation
 *              when the command buffer completes successfully. */
-(MPSNDArray * __nonnull) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                                   sourceArrays: (NSArray <MPSNDArray *> * __nonnull) sourceArrays;

/*! @abstract   Encode a simple inference NDArray kernel and return a NDArray to hold the result
 *  @param      cmdBuf          The command buffer into which to encode the kernel
 *  @param      sourceArrays    The list of sources for the filter in a NSArray.
 *                              Ordering to be defined by subclass
 *  @param      destination     The NDArray to receive the result */
-(void) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                 sourceArrays: (NSArray <MPSNDArray *> * __nonnull) sourceArrays
             destinationArray: (MPSNDArray *__nonnull) destination;


// Forward training encode calls
/*! @abstract   Encode a simple inference NDArray kernel and return a NDArray to hold the result
 *  @param      cmdBuf          The command buffer into which to encode the kernel
 *  @param      sourceArrays    The list of sources for the filter in a NSArray.
 *                              Ordering to be defined by subclass
 *  @param      outGradientState If non-nil, the address output gradient state is written to this address
 *  @param      outputStateIsTemporary  If YES, the state if any will be allocated to contain temporary textures and buffers as needed
 *  @result     A newly allocated MPSNDArray that will contain the result of the calculation
 *              when the command buffer completes successfully. */
-(MPSNDArray * __nonnull) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                                   sourceArrays: (NSArray <MPSNDArray *> * __nonnull) sourceArrays
                                    resultState: (MPSState * __nullable * __nullable) outGradientState
                         outputStateIsTemporary: (BOOL) outputStateIsTemporary;


/*! @abstract   Encode a simple inference NDArray kernel and return a NDArray to hold the result
 *  @param      cmdBuf          The command buffer into which to encode the kernel
 *  @param      sourceArrays    The list of sources for the filter in a NSArray.
 *                              Ordering to be defined by subclass
 *  @param      outGradientState The output gradient state to record the operation for later use by gradient
 *  @param      destination     A destination array to contain the result of the calculation
 *              when the command buffer completes successfully. */
-(void) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                 sourceArrays: (NSArray <MPSNDArray *> * __nonnull) sourceArrays
                  resultState: (MPSState * __nullable) outGradientState
             destinationArray: (MPSNDArray * __nonnull) destination;

@end


MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSNDArrayMultiaryGradientKernel : MPSNDArrayMultiaryBase

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           sourceCount: (NSUInteger) count NS_UNAVAILABLE;

/* NSSecureCoding support */
-(nonnull instancetype) initWithCoder: (NSCoder*__nonnull) coder
                               device: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*! @abstract   Initialize a MPSNDArrayMultiaryKernel
 *  @param      device                The device on which the kernel will run
 *  @param      count                 The maximum number of NDArrays read by the kernel
 *  @param      sourceGradientIndex   The source index for which gradient will be calculated
 *  @return     A valid MPSNDArrayMultiaryKernel, or nil if allocation failure. */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           sourceCount: (NSUInteger) count
                   sourceGradientIndex: (NSUInteger) sourceGradientIndex NS_DESIGNATED_INITIALIZER;

//RFC:  While this design is nice as it allows the same set of source arrays to
//      be used for forward and gradient passees, it causes a problem for the
//      getters and setters of properties like offset, kernel size, etc.
//      There is currently no way to manually set this information for the gradient.
//      This may not be viewed as a problem as this information is automatically
//      set by the gradient state.

// Gradient encode methods
// Inference encode calls.
-(MPSNDArray * __nonnull) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                                   sourceArrays: (NSArray <MPSNDArray *> * __nonnull) sources
                                 sourceGradient: (MPSNDArray * __nonnull) gradient
                                  gradientState: (MPSState * __nonnull) state;

-(void) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                 sourceArrays: (NSArray <MPSNDArray *> * __nonnull) sources
               sourceGradient: (MPSNDArray * __nonnull) gradient
                gradientState: (MPSState * __nonnull) state
             destinationArray: (MPSNDArray *__nonnull) destination;

@end



MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSNDArrayUnaryKernel : MPSNDArrayMultiaryKernel

/*! @property  offsets
 *  @abstract  The coordinate of the position read from this source array which is
 *             used to calculate the result value at [0,0,0,....]
 *             If the position read is actually a contiguous region (e.g. the area covered by
 *             a convolution kernel) then this is the center of that region, rounded down, for
 *             each dimension.
 *             Default: 0,0,0...
 */
@property (readonly, nonatomic)  MPSNDArrayOffsets offsets;

/*! @property  edgeMode
 *  @abstract  The edge mode used for a source NDArray
 *             Default: MPSImageEdgeModeZero
 */
@property (readonly, nonatomic)  MPSImageEdgeMode edgeMode;

/*! @property  kernelSizes
 *  @abstract  The diameters of the point spread function in each dimension for a source NDArray
 *             Default: 1
 */
@property (readonly, nonatomic)  MPSNDArraySizes kernelSizes;

/*! @property  kernelStrides
 *  @abstract  If the filter is a "backwards" filter such as a gradient filter
 *             or convolution transpose, then this is the upsampling ratio and
 *             zeros are inserted in the result.
 *             Default: 1
 */
@property (readonly, nonatomic)  MPSNDArrayOffsets strides;

/*! @property  dilationRate
 *  @abstract  The stride in each dimension from one PSF tap to an adjacent
 *             PSF tap. Default: 1
 */
@property (readonly, nonatomic)  MPSNDArraySizes dilationRates;

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;


-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           sourceCount: (NSUInteger) count NS_UNAVAILABLE;

/* NSSecureCoding support */
-(nonnull instancetype) initWithCoder: (NSCoder*__nonnull) coder
                               device: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

// Inference encode calls
/*! @abstract   Encode a simple inference NDArray kernel and return a NDArray to hold the result
 *  @param      cmdBuf          The command buffer into which to encode the kernel
 *  @param      sourceArray     The source for the filter in an NSArray.
 *  @result     A newly allocated MPSNDArray that will contain the result of the calculation
 *              when the command buffer completes successfully. */
-(MPSNDArray * __nonnull) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                                    sourceArray: (MPSNDArray *__nonnull) sourceArray;

/*! @abstract   Encode a simple inference NDArray kernel and return a NDArray to hold the result
 *  @param      cmdBuf          The command buffer into which to encode the kernel
 *  @param      sourceArray     The source for the filter in an NSArray.
 *  @param      destination     The NDArray to receive the result */
-(void) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                  sourceArray: (MPSNDArray *__nonnull) sourceArray
             destinationArray: (MPSNDArray *__nonnull) destination;


// Forward training encode calls
/*! @abstract   Encode a simple inference NDArray kernel and return a NDArray to hold the result
 *  @param      cmdBuf          The command buffer into which to encode the kernel
 *  @param      sourceArray     The source for the filter in an NSArray.
 *  @param      outGradientState If non-nil, the address output gradient state is written to this address
 *  @param      outputStateIsTemporary  If YES, the state if any will be allocated to contain temporary textures and buffers as needed
 *  @result     A newly allocated MPSNDArray that will contain the result of the calculation
 *              when the command buffer completes successfully. */
-(MPSNDArray * __nonnull) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                                    sourceArray: (MPSNDArray *__nonnull) sourceArray
                                    resultState: (MPSState * __nullable * __nullable) outGradientState
                         outputStateIsTemporary: (BOOL) outputStateIsTemporary;


/*! @abstract   Encode a simple inference NDArray kernel and return a NDArray to hold the result
 *  @param      cmdBuf          The command buffer into which to encode the kernel
 *  @param      sourceArray     The source for the filter in an NSArray.
 *  @param      outGradientState The output gradient state to record the operation for later use by gradient
 *  @param      destination     A destination array to contain the result of the calculation
 *              when the command buffer completes successfully. */
-(void) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                  sourceArray: (MPSNDArray *__nonnull) sourceArray
                  resultState: (MPSState * __nullable) outGradientState
             destinationArray: (MPSNDArray * __nonnull) destination;

@end


MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSNDArrayUnaryGradientKernel : MPSNDArrayMultiaryGradientKernel

//RFC:  While this design is nice as it allows the same set of source arrays to
//      be used for forward and gradient passees, it causes a problem for the
//      getters and setters of properties like offset, kernel size, etc.
//      There is currently no way to manually set this information for the gradient.
//      This may not be viewed as a problem as this information is automatically
//      set by the gradient state.

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;


-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           sourceCount: (NSUInteger) count
                   sourceGradientIndex: (NSUInteger) sourceGradientIndex NS_UNAVAILABLE;

/* NSSecureCoding support */
-(nonnull instancetype) initWithCoder: (NSCoder*__nonnull) coder
                               device: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

// Gradient encode methods
// Inference encode calls.
-(MPSNDArray * __nonnull) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                                    sourceArray: (MPSNDArray *__nonnull) sourceArray
                                 sourceGradient: (MPSNDArray * __nonnull) gradient
                                  gradientState: (MPSState * __nonnull) state;

-(void) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                  sourceArray: (MPSNDArray *__nonnull) sourceArray
               sourceGradient: (MPSNDArray * __nonnull) gradient
                gradientState: (MPSState * __nonnull) state
             destinationArray: (MPSNDArray *__nonnull) destination;

@end




MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSNDArrayBinaryKernel : MPSNDArrayMultiaryKernel

/*! @property  primaryOffsets
 *  @abstract  The coordinate of the position read from this source array which is
 *             used to calculate the result value at [0,0,0,....]
 *             If the position read is actually a contiguous region (e.g. the area covered by
 *             a convolution kernel) then this is the center of that region, rounded down, for
 *             each dimension.
 *             Default: 0,0,0...
 */
@property (readonly, nonatomic)  MPSNDArrayOffsets primaryOffsets;

/*! @property  primaryEdgeMode
 *  @abstract  The edge mode used for a source NDArray
 *             Default: MPSImageEdgeModeZero
 */
@property (readonly, nonatomic)  MPSImageEdgeMode primaryEdgeMode;

/*! @property  primaryKernelSizes
 *  @abstract  The diameters of the point spread function in each dimension for a source NDArray
 *             Default: 1
 */
@property (readonly, nonatomic)  MPSNDArraySizes primaryKernelSizes;

/*! @property  primaryStrides
 *  @abstract  If the filter is a "backwards" filter such as a gradient filter
 *             or convolution transpose, then this is the upsampling ratio and
 *             zeros are inserted in the result.
 *             Default: 1
 */
@property (readonly, nonatomic)  MPSNDArrayOffsets primaryStrides;

/*! @property  primaryDilationRate
 *  @abstract  The stride in each dimension from one PSF tap to an adjacent
 *             PSF tap. Default: 1
 */
@property (readonly, nonatomic)  MPSNDArraySizes primaryDilationRates;


/*! @property  secondaryOffsets
 *  @abstract  The coordinate of the position read from this source array which is
 *             used to calculate the result value at [0,0,0,....]
 *             If the position read is actually a contiguous region (e.g. the area covered by
 *             a convolution kernel) then this is the center of that region, rounded down, for
 *             each dimension.
 *             Default: 0,0,0...
 */
@property (readonly, nonatomic)  MPSNDArrayOffsets secondaryOffsets;

/*! @property  secondaryEdgeMode
 *  @abstract  The edge mode used for a source NDArray
 *             Default: MPSImageEdgeModeZero
 */
@property (readonly, nonatomic)  MPSImageEdgeMode secondaryEdgeMode;

/*! @property  secondaryKernelSizes
 *  @abstract  The diameters of the point spread function in each dimension for a source NDArray
 *             Default: 1
 */
@property (readonly, nonatomic)  MPSNDArraySizes secondaryKernelSizes;

/*! @property  secondaryStrides
 *  @abstract  If the filter is a "backwards" filter such as a gradient filter
 *             or convolution transpose, then this is the upsampling ratio and
 *             zeros are inserted in the result.
 *             Default: 1
 */
@property (readonly, nonatomic)  MPSNDArrayOffsets secondaryStrides;

/*! @property  secondaryDilationRate
 *  @abstract  The stride in each dimension from one PSF tap to an adjacent
 *             PSF tap. Default: 1
 */
@property (readonly, nonatomic)  MPSNDArraySizes secondaryDilationRates;

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;


-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           sourceCount: (NSUInteger) count NS_UNAVAILABLE;

/* NSSecureCoding support */
-(nonnull instancetype) initWithCoder: (NSCoder*__nonnull) coder
                               device: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

// Inference encode calls
/*! @abstract   Encode a simple inference NDArray kernel and return a NDArray to hold the result
 *  @param      cmdBuf                 The command buffer into which to encode the kernel
 *  @param      primarySourceArray     The primary source for the filter in an NSArray.
 *  @param      secondarySourceArray   The secondary source for the filter in an NSArray.
 *  @result     A newly allocated MPSNDArray that will contain the result of the calculation
 *              when the command buffer completes successfully. */
-(MPSNDArray * __nonnull) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                             primarySourceArray: (MPSNDArray *__nonnull) primarySourceArray
                           secondarySourceArray: (MPSNDArray *__nonnull) secondarySourceArray;

/*! @abstract   Encode a simple inference NDArray kernel and return a NDArray to hold the result
 *  @param      cmdBuf          The command buffer into which to encode the kernel
 *  @param      primarySourceArray     The primary source for the filter in an NSArray.
 *  @param      secondarySourceArray   The secondary source for the filter in an NSArray.
 *  @param      destination     The NDArray to receive the result */
-(void) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
           primarySourceArray: (MPSNDArray *__nonnull) primarySourceArray
         secondarySourceArray: (MPSNDArray *__nonnull) secondarySourceArray
             destinationArray: (MPSNDArray *__nonnull) destination;


// Forward training encode calls
/*! @abstract   Encode a simple inference NDArray kernel and return a NDArray to hold the result
 *  @param      cmdBuf          The command buffer into which to encode the kernel
 *  @param      primarySourceArray     The primary source for the filter in an NSArray.
 *  @param      secondarySourceArray   The secondary source for the filter in an NSArray.
 *  @param      outGradientState If non-nil, the address output gradient state is written to this address
 *  @param      outputStateIsTemporary  If YES, the state if any will be allocated to contain temporary textures and buffers as needed
 *  @result     A newly allocated MPSNDArray that will contain the result of the calculation
 *              when the command buffer completes successfully. */
-(MPSNDArray * __nonnull) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                             primarySourceArray: (MPSNDArray *__nonnull) primarySourceArray
                           secondarySourceArray: (MPSNDArray *__nonnull) secondarySourceArray
                                    resultState: (MPSState * __nullable * __nullable) outGradientState
                         outputStateIsTemporary: (BOOL) outputStateIsTemporary;


/*! @abstract   Encode a simple inference NDArray kernel and return a NDArray to hold the result
 *  @param      cmdBuf          The command buffer into which to encode the kernel
 *  @param      primarySourceArray     The primary source for the filter in an NSArray.
 *  @param      secondarySourceArray   The secondary source for the filter in an NSArray.
 *  @param      outGradientState The output gradient state to record the operation for later use by gradient
 *  @param      destination     A destination array to contain the result of the calculation
 *              when the command buffer completes successfully. */
-(void) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
           primarySourceArray: (MPSNDArray *__nonnull) primarySourceArray
         secondarySourceArray: (MPSNDArray *__nonnull) secondarySourceArray
                  resultState: (MPSState * __nullable) outGradientState
             destinationArray: (MPSNDArray * __nonnull) destination;

@end


/*!
 *  @class      MPSNDArrayDivisionPrimaryGradient
 *
 *  @dependency This depends on Metal.framework.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13), macCatalyst(13), tvos(13))
@interface MPSNDArrayBinaryPrimaryGradientKernel : MPSNDArrayMultiaryGradientKernel

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           sourceCount: (NSUInteger) count
                   sourceGradientIndex: (NSUInteger) sourceGradientIndex NS_UNAVAILABLE;

-(nonnull instancetype) initWithDevice:(id<MTLDevice> _Nonnull)device NS_DESIGNATED_INITIALIZER;

/* NSSecureCoding support */
-(nonnull instancetype) initWithCoder: (NSCoder*__nonnull) coder
                               device: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

// Gradient encode methods
// Inference encode calls.
-(MPSNDArray * __nonnull) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                             primarySourceArray: (MPSNDArray *__nonnull) primarySourceArray
                           secondarySourceArray: (MPSNDArray *__nonnull) secondarySourceArray
                                 sourceGradient: (MPSNDArray * __nonnull) gradient
                                  gradientState: (MPSState * __nonnull) state;

-(void) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
           primarySourceArray: (MPSNDArray *__nonnull) primarySourceArray
         secondarySourceArray: (MPSNDArray *__nonnull) secondarySourceArray
               sourceGradient: (MPSNDArray * __nonnull) gradient
                gradientState: (MPSState * __nonnull) state
             destinationArray: (MPSNDArray *__nonnull) destination;

@end    // MPSNDArrayDivisionPrimaryGradient

/*!
 *  @class      MPSNDArrayDivisionSecondaryGradient
 *
 *  @dependency This depends on Metal.framework.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.15), ios(13), macCatalyst(13), tvos(13))
@interface MPSNDArrayBinarySecondaryGradientKernel : MPSNDArrayMultiaryGradientKernel

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           sourceCount: (NSUInteger) count
                   sourceGradientIndex: (NSUInteger) sourceGradientIndex NS_UNAVAILABLE;

-(nonnull instancetype) initWithDevice:(id<MTLDevice> _Nonnull)device NS_DESIGNATED_INITIALIZER;

/* NSSecureCoding support */
-(nonnull instancetype) initWithCoder: (NSCoder*__nonnull) coder
                               device: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

// Gradient encode methods
// Inference encode calls.
-(MPSNDArray * __nonnull) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                             primarySourceArray: (MPSNDArray *__nonnull) primarySourceArray
                           secondarySourceArray: (MPSNDArray *__nonnull) secondarySourceArray
                                 sourceGradient: (MPSNDArray * __nonnull) gradient
                                  gradientState: (MPSState * __nonnull) state;

-(void) encodeToCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
           primarySourceArray: (MPSNDArray *__nonnull) primarySourceArray
         secondarySourceArray: (MPSNDArray *__nonnull) secondarySourceArray
               sourceGradient: (MPSNDArray * __nonnull) gradient
                gradientState: (MPSState * __nonnull) state
             destinationArray: (MPSNDArray *__nonnull) destination;

@end    // MPSNDArrayDivisionSecondaryGradient


#endif /* MPSNDArrayKernel_h */

