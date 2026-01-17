/*!
 * @header vImage_CVUtilities.h
 *  vImage.framework
 *
 *  Created by Ian Ollmann on 12/5/13.
 *  @copyright Copyright (c) 2013-2104 Apple Inc. All rights reserved.
 *
 *  @discussion vImage_CVUtilities.h provides a suite of high level APIs to facilitate conversion between CVPixelBufferRef
 *  formats and the set of formats describable by CoreGraphics types, including the core formats used by vImage for most
 *  image filters.  The API should support nearly any CoreVideo format or Core Graphics format in a generic (format neutral)
 *  manner.  Conversions by default are color corrected as necessary.  (The recipe for the correction is taken from ColorSync
 *  but vImage does the heavy lifting, usually running from 3-156 times faster.)  High level interfaces are available to 
 *  read/write data directly to/from CVPixelBufferRefs to vImage_Buffers.  Lower level interfaces are provided to allow the
 *  process to be broken apart a bit, to either respond to errors or eliminate redundant calculation.
 *
 *  Additionally, various RGB <-> CoreVideo basic conversions are available in vImage/Conversion.h.  These provide direct 
 *  access to the fast low level conversions available here. They are useful when you know exactly what formats you are working
 *  with ahead of time and just want to do that with a minimum of fuss.
 */
 
#ifndef vImage_CVUtilities_h
/*!
 *  @define vImage_CVUtilities_h
 *  @abstract Preprocessor symbol to make sure the header is only included once. 
 *  @discussion Set vImage_CVUtilities_h to 1 before including Accelerate headers to turn this header off. 
 *              You may wish to do that if the inclusion of CoreVideo/CVPixelBuffer.h is causing problems for your build.
 */
#define vImage_CVUtilities_h 1


#include <vImage/vImage_Utilities.h>
#include <vImage/Conversion.h>
#include <CoreVideo/CVPixelBuffer.h>  /* #define vImage_CVUtilities_h 1 before including Accelerate headers to turn this header off */

#ifdef __cplusplus
extern "C" {
#endif

/*
 *   CoreVideo interoperation:
 *     High Level interface
 */
    
    
/*!
 * @functiongroup vImage_Buffer Initialization
 */
    

/*!
 * @function vImageBuffer_InitWithCVPixelBuffer
 *
 * @abstract Initializes a vImage_Buffer to contain a representation of the CVPixelBufferRef provided.
 * @discussion It does the following:
 *
 *  <pre>
 *  @textblock
 *      o   Set buffer->height and buffer->width to match the size of the provided image.
 *
 *      o   set buffer->rowBytes for good performance                               (see kvImageDoNotAllocate flag below)
 *
 *      o   allocate a region of memory and assign a pointer to it to buffer->data  (see kvImageDoNotAllocate flag below)
 *
 *      o   convert the pixels contained in the image to the desired format and write to buffer->data.
 *  @/textblock
 *  </pre>
 *
 *
 * The entire image is converted. If you want to convert less, you can do so using vImageConvert_AnyToAny and a converter prepared with 
 * vImageConverter_CreateForCVToCGImageFormat.
 *
 *      @param buffer           A pointer to a vImage_Buffer structure to be initialized. The height and width fields will be overwritten
 *                              with the size of the CVPixelBuffer. Please see the kvImageDoNotAllocate flag description below for
 *                              options about how the buffer->data and buffer->rowBytes field is handled.
 *
 *      @param desiredFormat    image format for the vImage_Buffer.
 *
 *      @param cvPixelBuffer    A CVPixelBufferRef for the image. It is not necessary to lock the CVPixelBuffer before calling this function.
 *
 *      @param cvImageFormat    An optional vImageCVImageFormatRef to specify the pixel format of the CVPixelBuffer.
 *
 *                                  If NULL, vImage attempts to discover this information automatically from the CVPixelBuffer. However, sometimes
 *                                  necessary color information in the CVPixelBuffer is missing, preventing conversion.  An error will be returned.
 *                                  See kvImageCVImageFormat return codes for this function for more information. To supply vImage with complete
 *                                  color information, provide a complete vImageCVImageFormatRef here.
 *
 *                                  If not NULL, the cvImageFormat is used instead of looking to the CVPixelBufferRef for color information. If the
 *                                  cvImageFormat is also incomplete, a kvImageCVImageFormat_ error code will be returned.
 *
 *      @param backgroundColor  In cases where the vImage_Buffer format specifies opaque alpha and the cvPixelBuffer is has non-opaque alpha, the
 *                              image will be composited against a background color to remove the alpha before writing to the vImage_Buffer. The
 *                              background color is given in the colorspace of the desiredFormat.
 *
 *
 *      @param flags    The following flags are understood by this function:
 *
 *          <pre>
 *          @textblock
 *          kvImageDoNotAllocate        Under normal operation, new memory is allocated to hold the image pixels and its address is written
 *                                      to buffer->data. You are responsible for freeing that data when you are done with it, using free(). 
 *                                      When the kvImageDoNotAllocate flag is set, the buffer->data pointer and buffer->rowBytes is used unmodified.  
 *                                      This is intended to allow you to allocate the buffer yourself, or write directly into part of another image.
 *                                      Use CVPixelBufferGetHeight() and CVPixelBufferGetWidth() to find the size of the result buffer.
 *
 *          kvImageDoNotTile            Disable internal multithreading. This may be desired if you are extracting many
 *                                      such images in parallel, or are otherwise attempting to keep CPU utilization to
 *                                      a single core.
 *
 *          kvImageHighQualityResampling    For some CVPixelBuffer formats, the chroma channels are subsampled. This flag directs
 *                                          vImage to spend extra time where it can to give better image quality.
 *
 *          kvImagePrintDiagnosticsToConsole    In case of an error, print human readable error messages to the Apple System Logger (Console).
 *                                              This is useful for debugging, but probably should not be on for a shipping application.
 *          @/textblock
 *          </pre>
 *
 *  @return
 *          <pre>
 *          @textblock
 *      kvImageMemoryAllocationError            buffer->data was not able to be allocated.
 *
 *      kvImageBufferSizeMismatch               buffer and cvPixelBuffer are not the same height and width
 *
 *      kvImageCVImageFormat_ConversionMatrix   The conversion matrix is missing from the CVPixelBuffer / vImageCVImageFormatRef. See note below.
 *
 *      kvImageCVImageFormat_ChromaSiting       The chroma siting info is missing from the CVPixelBuffer / vImageCVImageFormatRef. See note below.
 *
 *      kvImageCVImageFormat_ColorSpace         The colorspace containing primaries and transfer function is missing from the CVPixelBuffer / vImageCVImageFormatRef.
 *
 *      kvImageInvalidParameter                 buffer is NULL
 *
 *      kvImageInvalidImageObject               cvPixelBuffer is NULL or can not be locked
 *
 *      kvImageInvalidImageFormat               desiredFormat is NULL or points to an illegal CG image format
 *
 *      Note: Some CVPixelBuffers have incompletely specified color information. This makes it impossible for vImage to do the conversion.
 *            When this happens, you will get one of the kvImageCVImageFormat_ errors above. To proceed, create a vImageCVImageFormatRef, add
 *            the missing information and pass as the cvImageFormat parameter. It is possible that more than one piece of information is missing.
 *            If the vImageCVImageFormatRef is missing information, then you will also get these errors.
 *          @/textblock
 *          </pre>
 *
 * Returned image notes:
 *
 *      vImage here conforms to CoreVideo practice of substituting gamma 1/1.961 for kCVImageBufferTransferFunction_ITU_R_709_2 and
 *      kCVImageBufferTransferFunction_SMPTE_240M_1995 instead of using the ITU-R BT.709-5 specified transfer function.  You may
 *      manually set the transfer function using vImageCreateRGBColorSpaceWithPrimariesAndTransferFunction() and vImageCVImageFormat_SetColorSpace().
 *      vImageCreateRGBColorSpaceWithPrimariesAndTransferFunction() does not make this substitution.
 */
vImage_Error vImageBuffer_InitWithCVPixelBuffer( vImage_Buffer *buffer,
                                                 vImage_CGImageFormat *desiredFormat,
                                                 CVPixelBufferRef cvPixelBuffer,
                                                 vImageCVImageFormatRef cvImageFormat,
                                                 const CGFloat *backgroundColor,
                                                 vImage_Flags flags )
                                                 VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );


/*!
 * @functiongroup vImageBuffer export
 */

/*!
 * @function vImageBuffer_CopyToCVPixelBuffer
 * @abstract Copies the contents of the vImage_Buffer to a CVPixelBufferRef.
 * @discussion If the format of the vImage_Buffer doesn't match the CVPixelBuffer format, the image will be converted to the CVPixelBuffer 
 *              format as part of the copy.
 *
 *  The entire CVPixelBuffer is overwritten. If you want to copy less, you can do so using vImageConvert_AnyToAny and a converter prepared
 *  with vImageConverter_CreateForCFToCVImageFormat.
 *
 *  vImage here conforms to CoreVideo practice of substituting gamma 1/1.961 for kCVImageBufferTransferFunction_ITU_R_709_2 and
 *  kCVImageBufferTransferFunction_SMPTE_240M_1995 instead of using the ITU-R BT.709-5 specified transfer function.  You may
 *  manually set the transfer function using vImageCreateRGBColorSpaceWithPrimariesAndTransferFunction() and vImageCVImageFormat_SetColorSpace().
 *  ImageCreateRGBColorSpaceWithPrimariesAndTransferFunction() does not make this substitution.
 *
 *
 *      @param buffer          A pointer to a vImage_Buffer containing the pixels to be copied (converted) to the CVPixelBuffer. May not be NULL.
 *
 *      @param bufferFormat    The format of buffer. May not be NULL.
 *
 *      @param cvPixelBuffer   The CVPixelBufferRef where the image will be written.  It should be a valid, preallocated CVPixelBufferRef
 *                      set to the desired image type (which need not match bufferFormat).  It is not necessary to lock the 
 *                      CVPixelBuffer before calling this function. May not be NULL.
 *
 *      @param cvImageFormat   An optional vImageCVImageFormatRef to specify the pixel format of the CVPixelBuffer.
 *
 *                      If NULL, vImage attempts to discover this information automatically. However, sometimes necessary color information
 *                      in the CVPixelBuffer is missing, preventing conversion.  An error will be returned. See kvImageCVImageFormat return 
 *                      codes for this function for more information. To supply vImage with complete color information, provide a complete 
 *                      vImageCVImageFormatRef here.
 *
 *                      If not NULL, the cvImageFormat is used instead of looking to the CVPixelBufferRef for color information. If the 
 *                      cvImageFormat is also incomplete, a kvImageCVImageFormat_ error code will be returned.
 *
 *                          CAUTION: In this case, it is your responsibility to make sure that the CVPixelBuffer has the right 
 *                                   attachments for matrix, chroma siting and colorspace as necessary to be properly decoded.
 *                                   vImage does not set these things for you.
 *
 *      @param backgroundColor If bufferFormat->bitmapInfo encodes kCGImageAlphaPremultipliedLast, kCGImageAlphaPremultipliedFirst,
 *                      kCGImageAlphaLast or kCGImageAlphaFirst -- that is, has a real alpha channel -- and the CVPixelBuffer
 *                      does not (most CV pixel formats don't) then the image will be flattened against a solid color to remove
 *                      the alpha information. You can select which color that is here. The background color is a CGFloat[3] 
 *                      (red, green, blue) in the RGB colorspace of the CVPixelBuffer. (YpCbCr images reference a RGB colorspace
 *                      through a matrix like ITU-709. That is the RGB colorspace we are talking about here.)  
 *
 *                      This parameter may be NULL, indicating black. 
 *
 *                      If you want to skip flattening, you can substitute in kCGImageAlphaNoneSkipFirst/Last for the encoding of
 *                      the input buffer. This may lead to undesired results in the case of premultiplied alpha however, when alpha 
 *                      is not all either 1.0 or 0. In that case, unpremultiply it first as a separate pass. Unpremultiplication may 
 *                      be more costly than just flattening it, but does not introduce regions of background color into the image.
 *
 *      @param flags           The following flags are understood by this function:
 *
 *          <pre>
 *          @textblock
 *          kvImageNoFlags                      Default operation.
 *
 *          kvImageDoNotTile                    Turn internal multithreading off. This may be helpful in cases where you already have
 *                                              many such operations going concurrently, and in cases where it is desirable to keep
 *                                              CPU utilization to a single core.
 *
 *          kvImageHighQualityResampling        For some CVPixelBuffer formats, the chroma channels are subsampled. This flag directs
 *                                              vImage to spend extra time where it can to give better image quality.
 *
 *          kvImagePrintDiagnosticsToConsole    In case of an error, print human readable error messages to the Apple System Logger (Console).
 *                                              This is useful for debugging, but probably should not be on for a shipping application.
 *          @/textblock
 *          </pre>
 *
 *      @return  
 *          <pre>
 *          @textblock
 *          kvImageNoError                          Success
 *
 *          kvImageInvalidImageFormat               bufferFormat is NULL or encodes an invalid format
 *
 *          kvImageBufferSizeMismatch               buffer and cvPixelBuffer are not the same height and width
 *
 *          kvImageNullPointerArgument              buffer and cvPixelBuffer may not be NULL
 *
 *          kvImageCVImageFormat_ConversionMatrix   The conversion matrix is missing from the CVPixelBuffer / vImageCVImageFormatRef. See note below.
 *
 *          kvImageCVImageFormat_ChromaSiting       The chroma siting info is missing from the CVPixelBuffer / vImageCVImageFormatRef. See note below.
 *
 *          kvImageCVImageFormat_ColorSpace         The colorspace containing primaries and transfer function is missing from the CVPixelBuffer / vImageCVImageFormatRef.
 *          @/textblock
 *          </pre>
 *
 *          Note: Some CVPixelBuffers have incompletely specified color information. This makes it impossible for vImage to do the conversion.
 *            When this happens, you will get one of the kvImageCVImageFormat_ errors above. To proceed, create a vImageCVImageFormatRef, add
 *            the missing information and pass as the cvImageFormat parameter. It is possible that more than one piece of information is missing.
 *
 */
vImage_Error vImageBuffer_CopyToCVPixelBuffer( const vImage_Buffer *buffer,
                                               const vImage_CGImageFormat *bufferFormat,
                                               CVPixelBufferRef cvPixelBuffer,
                                               vImageCVImageFormatRef cvImageFormat,
                                               const CGFloat *backgroundColor,
                                               vImage_Flags flags )
                                               VIMAGE_NON_NULL( 1, 2, 3) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );


/**************************
 *  Low level interfaces: *
 **************************/
    
/*
 *  While it is expected that the high level interfaces above will work for most, there are two common situation where more work may be required:
 *
 *  Sometimes CVPixelBuffers are missing information attached to them that is needed to convert them to other formats. The vImageCVImageFormatRef
 *  allows you to repair this problem prior to proceeding with conversions using the above high level interfaces or vImageConvert_AnyToAny.   
 *  The vImageCVImageFormatRef also provides additional control over how the conversion is done.
 *
 *  In addition, when the same conversion is done repeatedly, such as when converting multiple frames from the same movie, the high level interfaces
 *  presented above may incur some unnecessary overhead because they are redundantly introspecting pixel format and creating/destroying the same 
 *  objects over and over. Beaking apart the conversion process into substeps allows you to recycle work from earlier conversions to save time. 
 *  Both vImageCVImageFormatRefs and vImageConverterRefs can be reused multiple times, by multiple threads concurrently, if needed.
 */

 
/*!
 * @functiongroup vImageCVImageFormatRef methods
 */
    
/*!
 * @function vImageCVImageFormat_CreateWithCVPixelBuffer
 * @abstract Used to create a vImageCVImageFormatRef to describe the pixel format of an existing CVPixelBufferRef.
 *
 * @discussion If the CVPixelBufferRef has incomplete pixel format information, the vImageCVImageFormatRef will also be incomplete. Not all
 * missing fields ultimately will prove to be necessary, however.  If a function that consumes a vImageCVImageFormatRef returns a
 * vImageCVImageFormatError code, please add the missing information and try again. See "vImageCVImageFormatRef Accessors" below.
 *
 * @param buffer        The CBPixelBufferRef on which to base the vImageCVImageFormatRef
 *
 * @return
 *  On success, a non-NULL vImageCVImageFormatRef is returned. The vImageCVImageFormatRef has a retain count of 1. You are responsible
 *  for releasing it when you are done with it.
 */
vImageCVImageFormatRef vImageCVImageFormat_CreateWithCVPixelBuffer( CVPixelBufferRef buffer )
                                                                    __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );


    
/*!
 * @function vImageCVImageFormat_Create
 * @abstract Create a vImageCVImageFormatRef (low level).
 * @discussion This function creates a vImageCVImageFormatRef from first principles. In most cases, vImageCVImageFormat_CreateWithCVPixelBuffer
 *              is easier, but if your video pipeline doesn't use CoreVideo, or you need absolute control then this is your alternative.
 *
 *              Other fields not given by function parameters like number of channels, channel names, and channel description are automatically 
 *              configured using the imageFormatType. User data is set separately with vImageCVImageFormat_SetUserData.
 *
 *
 * @param imageFormatType       A CVPixelFormatType such as '2vuy'. See CVPixelBuffer.h for the complete list.
 *
 * @param  matrix               A vImage_ARGBToYpCbCrMatrix showing how to convert from RGB to the YpCbCr format. This may be NULL. However, it
 *                              is required for conversions involving YpCbCr images, so for YpCbCr images you will be eventually forced to set the matrix
 *                              using vImageCVImageFormat_CopyConversionMatrix before you can make a vImageConverterRef with this object.  
 *                              There are some predefined conversion matrices in Conversion.h for Rec 601 and 709 formats.
 *
 * @param  cvImageBufferChromaLocation   See kCVImageBufferChromaLocationTopFieldKey in CVImageBuffer.h for a list of chroma locations.
 *                              kCVImageBufferChromaLocation_Center is typical.  This may be NULL. However, for YpCbCr formats with downsampled
 *                              chroma, you will be ultimately forced to set a chroma location using vImageCVImageFormat_SetChromaSiting, before
 *                              a vImageConverterRef can be made with this object.
 *
 * @param  baseColorspace       For RGB and monochrome images, this is the colorspace of the image.
 *
 *                              For YpCbCr images, this is the colorspace of the RGB image before it was converted to YpCbCr using the ARGB-to-YpCbCr
 *                              conversion matrix (see matrix parameter above). The colorspace is defined based on the YpCbCr format RGB primaries
 *                              and transfer function.
 *
 *                              This may be NULL. However, you will eventually be forced to set set a colorspace for all image types, before
 *                              a vImageConvertRef can be made with this object.
 *
 * @param  alphaIsOneHint       Typically this is 0. If your image format has an alpha channel, but you know the image is fully opaque,
 *                              or want it to be treated as opaque, you can set this to 1. This may allow for faster conversions to
 *                              opaque formats.
 *
 *
 * @return
 *   On success, a non-NULL vImageCVImageFormatRef will be returned, which encodes the information contained in the above parameters. The 
 *   vImageCVImageFormatRef has a retain count of 1.  You must release it when you are done with it.
 *
 *   On failure, NULL is returned.
 */
vImageCVImageFormatRef vImageCVImageFormat_Create( uint32_t imageFormatType,                        // see kCVPixelFormatType_ defined in enum in CVPixelBuffer.h
                                                   const vImage_ARGBToYpCbCrMatrix *matrix,         // See also predefined constants in Conversion.h for 601/709/etc.
                                                   CFStringRef cvImageBufferChromaLocation,         // e.g. kCVImageBufferChromaLocation_Center
                                                   CGColorSpaceRef baseColorspace,                  // e.g. CGColorSpaceCreateWithName(kCGColorSpaceSRGB)
                                                   int  alphaIsOneHint                              // Set to 1 if the image has an alpha channel, and all the values in there are opaque. 0 otherwise.
                                                  ) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );


/*!
 *  @function vImageCVImageFormat_Copy
 *  @abstract Makes a copy of a vImageCVImageFormatRef.
 *  @discussion The new vImageCVFormatRef is different from the old one in that:
 *
 *      o       Its reference count is 1
 *
 *      o       The userData field and destructor callback are not copied, and are initialized to NULL.
 *
 *  Usually, it is preferable to simply retain a vImageCVImageFormatRef rather than copy it. You may wish to copy a vImageCVImageFormatRef if
 *  you want to modify an existing vImageCVImageFormatRef but can't because it is being read by another thread, or to replace another software layer's
 *  userData pointer with your own.  By convention, the new vImageCVImageFormatRef is considered to have been created by the software layer that called
 *  vImageCVImageFormat_Copy.
 *
 *  @param format  The vImageCVImageFormatRef to copy.
 *
 *  @return
 *  On success, a non-NULL vImageCVImageFormatRef is returned. Its reference count is 1. You are responsible for releasing it when you are done with it.
 *  On failure, this function returns NULL.
 */
vImageCVImageFormatRef vImageCVImageFormat_Copy( vImageConstCVImageFormatRef format ) VIMAGE_NON_NULL(1) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );

/*!
 * @function vImageCVImageFormat_Retain
 * @abstract Retains a vImageCVImageFormatRef
 * @discussion The vImageCVImageFormatRef follows standard retain/release semantics.
 *
 * vImageCVImageFormat_Retain causes the object's reference count to be incremented.
 *
 * vImageCVImageFormat_Release causes the object's reference count to be decremented. When the reference count reaches 0, 
 * the userDataReleaseCallback (if any) is called, and the object is then destroyed. The userDataReleaseCallback can access 
 * the vImageCVImageFormatRef, but can not prevent vImageCVImageFormatRef destruction. For this reason, the 
 * userDataReleaseCallback should be careful who it hands off control to in case that software layer
 * attempts to retain the vImageCVImageFormatRef. This will result in undefined behavior.
 *
 * @param fmt   The vImageCVImageFormatRef to retain
 *
 * fmt may be NULL, in which case nothing occurs.
 */
void vImageCVImageFormat_Retain( vImageCVImageFormatRef fmt ) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );

/*!
 * @function vImageCVImageFormat_Release
 * @abstract Releases a vImageCVImageFormatRef
 * @discussion The vImageCVImageFormatRef follows standard retain/release semantics.
 *
 * vImageCVImageFormat_Retain causes the object's reference count to be incremented.
 *
 * vImageCVImageFormat_Release causes the object's reference count to be decremented. When the reference count reaches 0,
 * the userDataReleaseCallback (if any) is called, and the object is then destroyed. The userDataReleaseCallback can access
 * the vImageCVImageFormatRef, but can not prevent vImageCVImageFormatRef destruction. For this reason, the
 * userDataReleaseCallback should be careful who it hands off control to in case that software layer
 * attempts to retain the vImageCVImageFormatRef. This will result in undefined behavior.
 *
 * @param fmt   The vImageCVImageFormatRef to release
 *
 * fmt may be NULL, in which case nothing occurs.
 */
void vImageCVImageFormat_Release( vImageCVImageFormatRef fmt ) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );

/*! 
 *  @typedef vImageCVImageFormatError
 *  @abstract  Additional error codes for functions that use the vImageCVImageFormatRef
 *  @discussion It is possible for a vImageCVImageFormatRef to contain incomplete information. This frequently happens 
 *              when it is created from a CVPixelBufferRef which itself has incomplete formatting information. It can
 *              also happen by design as the result of something like vImageCVImageFormat_SetColorSpace(fmt, NULL). When
 *              this occurs, the vImageCVImageFormatRef may not contain enough information to perform a requested conversion
 *              (e.g. vImageBuffer_InitWithCVPixelBuffer). In such cases, a vImageCVImageFormatError will be returned
 *              from the left hand side of the function to indicate which field is absent.
 *
 *  @constant   kvImageCVImageFormat_NoError    No error. The conversion was successfully completed. 
 *
 *  @constant   kvImageCVImageFormat_ConversionMatrix The conversion matrix is absent and required. The conversion matrix
 *              provides the conversion from RGB to Y'CbCr.
 *
 *  @constant   kvImageCVImageFormat_ChromaSiting  The chroma siting information is absent.  Chroma siting indicates the position
 *              of chrominance information relative to luminance samples when chrominance is sub-sampled. 
 *
 *  @constant   kvImageCVImageFormat_ColorSpace The colorspace of the image is missing. If Y'CbCr, this is the colorspace of the
 *              RGB image from which the Y'CbCr pixels were calculated. Otherwise, it is the colorspace of the pixels themselves. 
 *              Most CVPixelBuffer formats only allow one or two colorspace models (e.g. kCGColorSpaceModelRGB)
 *
 *  @constant   kvImageCVImageFormat_VideoChannelDescription    The range and clipping information is missing. This is unlikely
 *              to occur, since the information is initialized automatically based on the imageFormatType (See vImageCVImageFormat_Create.)
 *
 *  @constant   kvImageCVImageFormat_AlphaIsOneHint    The alpha-is-one hint tells vImage that the alpha channel (if any) is opaque.
 *                                                      This hint may be used to avoid some computation to flatten the alpha channel
 *                                                      in some cases. Because it is a hint, it can not be missing.
 */
    
/* Additional error codes for functions that consume a vImageCVImageFormatRef */
typedef VIMAGE_CHOICE_ENUM( vImageCVImageFormatError, ssize_t )
{
    kvImageCVImageFormat_NoError                            VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 )  = 0,
    kvImageCVImageFormat_ConversionMatrix                   VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 )  = -21600,
    kvImageCVImageFormat_ChromaSiting                       VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 )  = -21601,
    kvImageCVImageFormat_ColorSpace                         VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 )  = -21602,
    kvImageCVImageFormat_VideoChannelDescription            VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 )  = -21603,
    kvImageCVImageFormat_AlphaIsOneHint                     VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 )  = -21604,
};

/*!
    @typedef        vImageChannelDescription
    @abstract       A description of the range and clamp limits for a pixel format
    @discussion     The vImageChannelDescription is provided to allow for "video range" formats and detailed
                    control overclamping on a per-channel basis. The min and max control clamping limits. Values 
                    outside the range [min, max] are clamped to be in that range.  The zero and full values give
                    the normal range and bias for the format. They are the encodings for 0.0 and 1.0 respectively.
                    (0.0 and 0.5 for Chroma.)
 
    @field          min     The minimum encoded value allowed. Values less than this encoding are clamped to this value.
    @field          zero    The encoding for the value 0.0.   For example, for 8-bit chroma data this would be 128. For 
                            8-bit full range Luminance, this is 0. 8-bit video range Luminance is 16. 
    @field          full    The encoding for 1.0 (0.5 for chroma). 
    @field          max     The maximum allowed encoding. Values greater than this are clamped to this value.
 
    @seealso        vImage_YpCbCrPixelRange
    @seealso        vImageCVImageFormatRef channel descriptions
 */
    
typedef struct vImageChannelDescription
{
    CGFloat           min;        /* e.g. Minimum allowed value for format. e.g. {16, 16, 16, 0} for {Y', Cb, Cr, A} 8-bit video range                                  */
    CGFloat           zero;       /* e.g. Encoded value for 0.0   e.g. {0, 128, 128, 0} for {Y', Cb, Cr, A} 8-bit video range                                           */
    CGFloat           full;       /* e.g. Encoded value for 1.0, (0.5 for Chroma).  e.g. {235, 240, 240, 255} for {Y', Cb, Cr, A} 8-bit video range, full range alpha   */
    CGFloat           max;        /* e.g. Maximum allowed value for format. e,g, {235, 240, 240, 255} to clamp to {Y', Cb, Cr, A} 8-bit video range, full range alpha   */
                                  /*                                             {0xff, 0xff, 0xff, 0xff} to clamp to full range                                        */
}vImageChannelDescription;
    
/*!
 *  @typedef    vImageMatrixType
 *  @abstract   An enumeration of RGB -> Y'CbCr conversion matrix types. 
 *  @description    Currently, only one matrix type is available. Additional formats are reserved for future expansion.
 *
 *  @constant   kvImageMatrixType_ARGBToYpCbCrMatrix    A vImage_ARGBToYpCbCrMatrix
 */
typedef VIMAGE_CHOICE_ENUM( vImageMatrixType, uint32_t )
{
    /* No matrix required for this format. NULL will be returned. Attempts to set this matrix are ignored. */
    kvImageMatrixType_None                  VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 ) = 0,

    /* A vImage_ARGBToYpCbCrMatrix */
    kvImageMatrixType_ARGBToYpCbCrMatrix    VIMAGE_ENUM_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 ) = 1,

    /* other values are reserved for future expansion. For example, BT.2020 would probably require a new matrix type for constant luminance. */
};
    
    
/*!
 *  @function vImageCVImageFormat_GetFormatCode
 *  @abstract Return the kCVPixelFormatType_ (4 character code) that encodes the pixel format.
 *  @discussion The kCVPixelFormatType_ of a CoreVideo pixel buffer is given by a four character code (4CC), such as '2vuy'. It describes the number of channels,
 *              channel packing order, bits per component (except in one case), and usually range information like whether it is full range or
 *              video range.
 *  @param format   The vImageCVImageFormatRef for which the 4 character code is desired.
 *  @return  A 4CC in host-endian format.
 *  @seealso See CoreVideo/CVPixelBuffer.h for a list of defined 4 character image type codes.
 */
uint32_t        vImageCVImageFormat_GetFormatCode( vImageConstCVImageFormatRef format )  VIMAGE_NON_NULL(1) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );
    
/*!
 *  @function vImageCVImageFormat_GetChannelCount
 *  @abstract Return the the number of color channels in the image, including alpha.
 *  @discussion The channels may be interleaved or planar. For RGBA, the result is 4. For 'yuvs' this is 3. This does not return
 *              the same results as vImageConverter_GetNumberOfSourceBuffers / vImageConverter_GetNumberOfSourceBuffers, which
 *              instead describe the number of vImage_Buffers to pass to vImageConvert_AnyToAny. Some vImage_Buffers contain
 *              multiple channels.
 *  @param format   The vImageCVImageFormatRef for which the number of channels is desired.
 *  @return  A uint32_t containing the number of channels
 */
uint32_t        vImageCVImageFormat_GetChannelCount( vImageConstCVImageFormatRef format)  VIMAGE_NON_NULL(1) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );

/*!
 *  @function vImageCVImageFormat_GetChannelNames
 *  @abstract Get a const kvImageBufferTypeCode_EndOfList-terminated array indicating the names of the channels in the buffer.
 *  @discussion The array is owned by the vImageCvImageFormatRef and will cease to be valid when the object is destroyed. 
 *              This function is not useful to discover the correct vImage_Buffer order for a call to vImageConvert_AnyToAny().
 *  @param format   The vImageCVImageFormatRef for which the channel names are desired.
 *  @return  A const pointer to an array of vImageBufferTypeCodes indicating the names of the channels in the image.
 *  @seealso  vImageConverter_GetSourceBufferOrder
 *  @seealso vImageConverter_GetDestinationBufferOrder
 */
const vImageBufferTypeCode *vImageCVImageFormat_GetChannelNames( vImageConstCVImageFormatRef format)  VIMAGE_NON_NULL(1) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );

/*!
 *  @function vImageCVImageFormat_GetColorSpace
 *  @abstract Get the colorspace associated with the image.
 *  @discussion If the image format is a Y'CbCr image format, this is the RGB colorspace of the image after the inverse 
 *              RGB->YpCbCr conversion matrix is applied. Otherwise, it is the colorspace of the pixels in the image.
 *  @param format   The vImageCVImageFormatRef for which the colorspace is desired.
 *  @return  The colorspace (if any) that is returned is referenced by the vImageCVImageFormatRef and will be released
 *           when that object is destroyed. This function may return NULL, indicating an absence of colorspace information.
 */
CGColorSpaceRef vImageCVImageFormat_GetColorSpace( vImageConstCVImageFormatRef format) VIMAGE_NON_NULL(1) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );
    

/*!
 *  @function vImageCVImageFormat_SetColorSpace
 *  @abstract Set the colorspace associated with the image.
 *  @discussion If the image format is a Y'CbCr image format, this sets the RGB colorspace of the image before the
 *              RGB->YpCbCr conversion matrix was applied. Otherwise, it is the colorspace of the pixels in the image.
 *              A non-NULL colorspace must be present before a vImageCVImageFormatRef can be used to do a conversion.
 *  @param format       The vImageCVImageFormatRef for which the colorspace is to be set.
 *  @param colorspace   The new colorspace.  May be NULL, indicating missing colorspace information.
 *  @return  On Success, kvImageNoError. An error will be returned if the colorspace model doesn't match what is expected
 *           for the image format type. For example, a 'RGBA' image must be kCGColorSpaceModelRGB.  Y'CbCr images expect a
 *           RGB colorspace. The new colorspace will be retained and he old one will be released.
 *
 *           On failure, nothing occurs.
 */
vImage_Error    vImageCVImageFormat_SetColorSpace( vImageCVImageFormatRef format, CGColorSpaceRef colorspace ) VIMAGE_NON_NULL(1) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );
 
/*!
 *  @function vImageCVImageFormat_GetChromaSiting
 *  @abstract Get the chroma-siting for the image.
 *  @discussion When Y'CbCr images have subsampled chroma, the position of the chroma samples relative to the luminance samples needs to be
 *              specified. Chroma siting information is only needed for Y'CbCr images that are not 444.
 *  @param format       The vImageCVImageFormatRef for which the chroma siting information is desired.
 *  @return  Returns a CFStringRef that describes the positioning of the chroma samples. Eligible string return values are listed 
 *           in CoreVideo/CVImageBuffer.h.   The result is NULL if the chroma siting information is missing.
 *  @seealso kCVImageBufferChromaLocationTopFieldKey
 */
CFStringRef     vImageCVImageFormat_GetChromaSiting( vImageConstCVImageFormatRef format ) VIMAGE_NON_NULL(1) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );

/*!
 *  @function vImageCVImageFormat_SetChromaSiting
 *  @abstract Set the chroma-siting for the image.
 *  @discussion When Y'CbCr images have subsampled chroma, the position of the chroma samples relative to the luminance samples needs to be
 *              specified. Chroma siting information is only needed for Y'CbCr images that are not 444. The new siting name will be retained.
 *              The old siting will be released. This function has no effect for image format types that do not require siting information.
 *  @param format       The vImageCVImageFormatRef for which the chroma siting information is desired.
 *  @param siting       The new siting information for the format. May be NULL.
 *  @return  
 *      <pre>
 *      @textblock
 *          kvImageNoError                  Success
 *
 *          kvImageInvalidImageFormat       format is NULL
 *          
 *          kvImageInvalidParameter         siting is not a recognized CFStringRef from the set of values appearing in CoreVideo/CVImageBuffer.h.
 *      @/textblock
 *      </pre>
 *  @seealso kCVImageBufferChromaLocationTopFieldKey
 */
vImage_Error    vImageCVImageFormat_SetChromaSiting( vImageCVImageFormatRef format, CFStringRef siting) VIMAGE_NON_NULL(1) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );
 
/*!
 *  @function vImageCVImageFormat_GetConversionMatrix
 *  @abstract Get the RGB -> Y'CbCr conversion matrix for the image.
 *  @discussion  Y'CbCr images are defined in terms of a RGB image and a conversion matrix from that RGB format to Y'CbCr. 
 *               The conversion frequently has the form:
 *
 *          <pre>
 *          @textblock
 *              Y' =  R_Yp * R  + G_Yp * G + B_Yp * B       Y' = [0, 1.0]
 *              Cb = k0 * (B - Y')                          Cb = [-0.5, 0.5]
 *              Cr = k1 * (R - Y')                          Cr = [-0.5, 0.5]
 *          @/textblock
 *          </pre>
 *
 *      That can be reformulated as a 3x3 matrix operation. The element names here correspond to the fields in the vImage_ARGBToYpCbCrMatrix type:
 *
 *          <pre>
 *          @textblock
 *              | Y' |   | R_Yp        G_Yp     B_Yp      |   | R |
 *              | Cb | = | R_Cb        G_Cb     B_Cb_R_Cr | * | G |
 *              | Cr |   | B_Cb_R_Cr   G_Cr     B_Cr      |   | B |
 *          @/textblock
 *          </pre>
 *
 *      Most Y'CbCr conversion matrices are of this form. However, some conversion matrices, such as that proposed to ITU-R BT.2020 for 
 *      constant luminance, are more complicated.
 *
 *      It is possible for the matrix to be absent. Y'CbCr image types may not be converted without a conversion matrix.
 *
 *  @param format       The vImageCVImageFormatRef for which the matrix is desired
 *  @param outType      A pointer to a variable of type vImageMatrixType.
 *  @return  A pointer to a matrix will be returned from the left hand side of the function. The memory pointed to by outType will be
 *              overwritten with the type of the matrix returned.  The returned matrix may be NULL, indicating an absent matrix.
 *
 *          The matrix is owned by the vImageCvImageFormatRef and will cease to be valid when the vImageCvImageFormatRef is destroyed.
 *
 *  @seealso vImage_ARGBToYpCbCrMatrix and vImageMatrixType
 */
const           void * vImageCVImageFormat_GetConversionMatrix( vImageConstCVImageFormatRef format, vImageMatrixType *outType)  VIMAGE_NON_NULL(1) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );

    
/*!
 *  @function vImageCVImageFormat_CopyConversionMatrix
 *  @abstract Set the RGB -> Y'CbCr conversion matrix for the image.
 *  @discussion  matrix is copied to the vImageCVImageFormatRef's internal matrix storage.
 *
 *  Y'CbCr images are defined in terms of a RGB image and a conversion matrix from that RGB format to Y'CbCr.
 *               The conversion frequently has the form:
 *
 *          <pre>
 *          @textblock
 *              Y' =  R_Yp * R  + G_Yp * G + B_Yp * B       Y' = [0, 1.0]
 *              Cb = k0 * (B - Y')                          Cb = [-0.5, 0.5]
 *              Cr = k1 * (R - Y')                          Cr = [-0.5, 0.5]
 *          @/textblock
 *          </pre>
 *
 *      That can be reformulated as a 3x3 matrix operation. The element names here correspond to the fields in the vImage_ARGBToYpCbCrMatrix type:
 *
 *          <pre>
 *          @textblock
 *              | Y' |   | R_Yp        G_Yp     B_Yp      |   | R |
 *              | Cb | = | R_Cb        G_Cb     B_Cb_R_Cr | * | G |
 *              | Cr |   | B_Cb_R_Cr   G_Cr     B_Cr      |   | B |
 *          @/textblock
 *          </pre>
 *
 *      Most Y'CbCr conversion matrices are of this form. However, some conversion matrices, such as that proposed to ITU-R BT.2020 for
 *      constant luminance, are more complicated.
 *
 *      It is possible for the matrix to be absent. Y'CbCr image types may not be converted without a conversion matrix.
 *
 *  @param format       The vImageCVImageFormatRef for which the matrix is desired
 *  @param matrix       The matrix data to be copied to the vImageCVImageFormatRef. If the matrix is a constant predefined by vImage, 
 *                      the address shall be preserved, and returned unmodified by vImageCVImageFormat_GetConversionMatrix.
 *                      The matrix must have a matrix inverse.
 *  @param inType       The type of the matrix. The only type defined for OS X.10 and iOS 8.0 is kvImageMatrixType_ARGBToYpCbCrMatrix, which is a vImage_ARGBToYpCbCrMatrix.
 *
 *  @return  
 *          <pre>
 *          @textblock
 *           kvImageNoError             Success.
 *
 *           kvImageInvalidParameter    The matrix type did not match that required for the image format.
 *
 *           kvImageInvalidParameter    The matrix is not invertible. (See console for log in this case.)
 *          @/textblock
 *          </pre>
 *
 *  @seealso vImage_ARGBToYpCbCrMatrix 
 *  @seealso vImageMatrixType
 */
vImage_Error    vImageCVImageFormat_CopyConversionMatrix(vImageCVImageFormatRef format, const void *matrix, vImageMatrixType inType)  VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );

/*!
 *  @function vImageCVImageFormat_GetAlphaHint
 *  @abstract Get the alpha-is-one hint from a vImageCVImageFormatRef
 *  @discussion  Some image formats have an alpha channel. Sometimes, the alpha channel for the entire image is known to be 1.0 (fully opaque).
 *               In some circumstances, that knowledge can be used to eliminate work from a conversion to make it faster, especially when converting
 *               to a format without an alpha channel.  If the alpha-is-one hint is non-zero, it indicates that the alpha channel is fully opaque. 
 *
 *               Images that do not have an alpha channel will also return non-zero.
 *
 *               There are a few image formats that have room for an alpha channel (kCVPixelFormatType_16BE555, kCVPixelFormatType_16LE555, 
 *               kCVPixelFormatType_30RGB) but which do not have an alpha channel. Setting the alpha-is-one hint to 0 does not add an alpha
 *               channel to these image types. 
 *
 *               The alpha-is-one hint is a hint.  It can not be absent in a way that will prevent conversion. If it is not set or is zero, and 
 *               the image format has alpha, then the alpha channel will be included in the calculation. If the result format has alpha, the alpha
 *               will propagate there. If the result format does not have alpha, the image will be flattened against the indicated background color
 *               for the conversion.
 *
 *  @param format       The vImageCVImageFormatRef for which the colorspace is to be set.
 *  @return  0  Alpha is not known to be opaque, or the hint has not been set.
 *
 *           non-zero  Alpha is known to be fully opaque, even if the values encoded for alpha in the image are not 1.0.
 */
int             vImageCVImageFormat_GetAlphaHint( vImageConstCVImageFormatRef format)  VIMAGE_NON_NULL(1) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );
    
/*!
 *  @function vImageCVImageFormat_SetAlphaHint
 *  @abstract Set the alpha-is-one hint for a vImageCVImageFormatRef
 *  @discussion  Some image formats have an alpha channel. Sometimes, the alpha channel for the entire image is known to be 1.0 (fully opaque).
 *               In some circumstances, that knowledge can be used to eliminate work from a conversion to make it faster, especially when converting
 *               to a format without an alpha channel.  If the alpha-is-one hint is non-zero, it indicates that the alpha channel is fully opaque.
 *
 *               The alpha-is-one hint is a hint.  It can not be absent in a way that will prevent conversion. If it is not set or is zero, and
 *               the image format has alpha, then the alpha channel will be included in the calculation. If the result format has alpha, the alpha
 *               will propagate there. If the result format does not have alpha, the image will be flattened against the indicated background color
 *               for the conversion.
 *
 *               There are a few image formats that have room for a small alpha channel (kCVPixelFormatType_16BE555, kCVPixelFormatType_16LE555,
 *               kCVPixelFormatType_30RGB) but which do not have an alpha channel. Setting the alpha-is-one hint to 0 does not add an alpha
 *               channel to these image types.  If this behavior is desired, such image formats can generally be described using a vImage_CGImageFormat.
 *               If so, you can set the vImage_CGImageFormat.bitmap info to an appropriate CGImageAlphaInfo for the desired treatment for the alpha
 *               channel and convert using vImageConverter_CreateWithCGImageFormat() + vImageConvert_AnyToAny().
 *
 *  @param format       The vImageCVImageFormatRef for which the colorspace is to be set.
 *  @parma alphaIsOne   The new value for the alpha-is-one hint.
 *  @return  kvImageNoError             Success.
 *
 *           kvImageInvalidParameter    format is NULL
 */
vImage_Error    vImageCVImageFormat_SetAlphaHint( vImageCVImageFormatRef format, int alphaIsOne)  VIMAGE_NON_NULL(1) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );
    
/*!
 *  @function vImageCVImageFormat_GetChannelDescription
 *  @abstract Get the channel description for a particular channel type
 *  @discussion  The channel description gives information about the range of values and clamping for a image color channel.
 *
 *  @param format       The vImageCVImageFormatRef that the channel description is for.
 *  @parma type         The type of the channel that you wish information about. Example: kvImageBufferTypeCode_Luminance
 *  @return  A const pointer to a vImageChannelDescription struct. The data in the structure may not be modified and belongs to the vImageCVImageFormatRef.
 *           It is destroyed when the vImageCVImageFormatRef is destroyed.
 *  @seealso vImageChannelDescription
 */
const           vImageChannelDescription *vImageCVImageFormat_GetChannelDescription( vImageConstCVImageFormatRef format, vImageBufferTypeCode type )
                                                                                    VIMAGE_NON_NULL(1) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );
    
/*!
 *  @function vImageCVImageFormat_CopyChannelDescription
 *  @abstract Set the channel description for a particular channel type
 *  @discussion  The channel description gives information about the range of values and clamping for a image color channel.
 *
 *  @param format       The vImageCVImageFormatRef that the channel description is for.
 *  @param desc         A pointer to a new vImageChannelDescription to use for the channel type.  The data is copied into the vImageCVImageFormatRef.
 *  @param type         The type of the channel that you wish to set information about. Example: kvImageBufferTypeCode_Luminance
 *  @return  kvImageNoError     Success
 *
 *           kvImageInvalidParameter    An invalid vImageBufferTypeCode, either out of range, or the channel type does not appear in the image format
 *  @seealso vImageChannelDescription
 */
vImage_Error    vImageCVImageFormat_CopyChannelDescription( vImageCVImageFormatRef format, const vImageChannelDescription *desc, vImageBufferTypeCode type )
                                                            VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );
    
/*!
 *  @function vImageCVImageFormat_GetUserData
 *  @abstract Get the user info pointer attached to the image format
 *  @discussion  There may be extra information that you wish to attach to a vImageCVImageFormatRef.  It might be a pthread_rwlock_t to help prevent
 *               concurrent access to the vImageCVImageFormatRef while it is being modified, or perhaps additional metadata about the image format 
 *               that you may need later. It may even just a pointer to an object you wrote which wraps the vImageCVImageFormatRef. 
 *
 *               The user data pointer is available for you to use to store a reference to this information. The token is opaque to vImage. vImage
 *               only returns it when asked via vImageCVImageFormat_GetUserData.  It can be set with vImageCVImageFormat_SetUserData.
 *
 *  @param format       The vImageCVImageFormatRef to get the userData from.
 *  @return  The address of the userData. It will be NULL if no userData has been set.
 *  @seealso vImageCVImageFormat_SetUserData
 */
void *          vImageCVImageFormat_GetUserData( vImageConstCVImageFormatRef format)   VIMAGE_NON_NULL(1) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );

/*!
 *  @function vImageCVImageFormat_SetUserData
 *  @abstract  Sets the userData pointer and a userDataReleaseCallback function
 *  @seealso vImageCVImageFormat_SetUserData
 *  @discussion  The userDataReleaseCallback is called when the vImageCVImageFormatRef is destroyed. You may access the vImageCVImageFormatRef
 *               during the callback function. However vImageCVImageFormat_Retain() will not prevent the destruction of the object in that context.
 *               The userDataReleaseCallback will also be called on the previous user data in the event that vImageCVImageFormat_SetUserData
 *               is called to replace one set of user date with another. 
 *
 *              CAUTION: vImage does not attempt to do anything smart when the old and new userData are actually the same or differ only by callback.
 *
 *              vImage does not attempt to free the user data when the vImageCVImageFormatRef is destroyed. If the userData needs to
 *              be freed/released/etc. at this time, then you should do so in your userDataReleaseCallback.
 *
 *              vImageCVImageFormat_SetUserData function is not atomic. vImageCVImageFormat_SetUserData is not safe to call reentrantly.
 *
 *              Since there can be only one userData attached to a vImageCVImageFormatRef, the userData field is reserved by convention
 *              for exclusive use by the app/framework/library that created the vImageCVImageFormatRef.  If you need to attach your own
 *              userData to a vImageCVImageFormatRef that you did not create, make a copy of it with vImageCVImageFormat_Copy.  The new 
 *              copy will not have userData attached to it.
 *
 *  @param format       The vImageCVImageFormatRef to get the userData from.
 *  @param userdata     The new userData pointer.
 *  @return  kvImageNoError - Success
 *
 *           kvImageInvalidImageFormat  -format is NULL
 *  @param     userDataReleaseCallback   The callback that is called when the vImageCVImageFormatRef is destroyed, or when the userData is replaced with
 *                                      another one.
 *  @param     callback_fmt The vImageCVImageFormatRef that the userData is attached to.
 *  @param     callback_userData    The userData field attached to callback_fmt.
 *
 */
vImage_Error    vImageCVImageFormat_SetUserData(vImageCVImageFormatRef format, void * userData, void (*userDataReleaseCallback)(vImageCVImageFormatRef callback_fmt, void *callback_userData) )   VIMAGE_NON_NULL(1) __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );
    
   
/*! @functiongroup  Low level colorspace initialization */
    
typedef struct vImageTransferFunction
{
    CGFloat c0, c1, c2, c3, gamma;          // R' = c0 * pow( c1 * R + c2, gamma ) + c3,    (R >= cutoff)
    CGFloat cutoff;                         // See immediately above and below.  For no linear region (no below segment), pass -INFINITY here.
    CGFloat c4, c5;                         // R' = c4 * R + c5                             (R < cutoff)
}vImageTransferFunction;

typedef struct vImageRGBPrimaries
{
    float red_x, green_x, blue_x, white_x;
    float red_y, green_y, blue_y, white_y;
}vImageRGBPrimaries;
   
/*!
 * @function vImageCreateRGBColorSpaceWithPrimariesAndTransferFunction
 *
 * @abstract Create a RGB colorspace based on primitives typically found in Y'CbCr specifications
 *
 * @discussion This function may be used to create a CGColorSpaceRef to correspond with a given set of color
 * primaries and transfer function. This defines a RGB colorspace. (A Y'CbCr colorspace is defined as a RGB
 * colorspace and a conversion matrix from RGB to Y'CbCr.) The color primaries give the extent of a colorspace
 * in x,y,z space and the transfer function gives the transformation from linear color to non-linear color that
 * the pixels actually reside in.
 *
 *   <pre>
 *   @textblock
 *      Example:  ITU-R BT.709-5
 *
 *          const vImageTransferFunction f709 =
 *          {  // 1.2 transfer function
 *              .c0 = 1.099,
 *              .c1 = 1.0,
 *              .c2 = 0.0,
 *              .c3 = -0.099,
 *              .gamma = 0.45,
 *              .cutoff = 0.018,
 *              .c4 = 4.5,
 *              .c5 = 0
 *          };
 *
 *          const vImageRGBPrimaries p709 =
 *          {
 *              .red_x = .64,               // 1.3 red
 *              .green_x = .30,             // 1.3 green
 *              .blue_x = .15,              // 1.3 blue
 *              .white_x = 0.3127,          // 1.4 white
 *
 *              .red_y = .33,               // 1.3 red
 *              .green_y = .60,             // 1.3 green
 *              .blue_y = .06,              // 1.3 blue
 *              .white_y = 0.3290           // 1.4 white
 *          };
 *
 *          vImage_Error err = kvImageNoError;
 *          CGColorSpaceRef colorSpace = vImageCreateRGBColorSpaceWithPrimariesAndTransferFunction( &p709, &f709, kvImageNoFlags, &err );
 *          @/textblock
 *          </pre>
 *
 *  Other methods to create a RGB colorspace:
 *
 *      You may find it easier to use CVImageBufferCreateColorSpaceFromAttachments or CVImageBufferGetColorSpace, in some cases.
 *      If there is enough color information attached to a CVPixelBuffer, you can also get one using vImageCVImageFormat_CreateWithCVPixelBuffer().
 *      There are also many ways to create a RGB CGColorSpace in CoreGraphics/CGColorSpace.h.
 *
 *   <pre>
 *   @textblock
 *      Note: This low level function does not conform to CoreVideo practice of automatically substituting gamma 1/1.961
 *      for kCVImageBufferTransferFunction_ITU_R_709_2 and kCVImageBufferTransferFunction_SMPTE_240M_1995 instead of using
 *      the ITU-R BT.709-5 specified transfer function. (vImageBuffer_InitWithCVPixelBuffer and vImageBuffer_CopyToCVPixelBuffer
 *      do.) If you would like that behavior, you can use the following transfer function:
 *
 *      const vImageTransferFunction f709_Apple =
 *      {
 *          .c0 = 1.0,
 *          .c1 = 1.0,
 *          .c2 = 0.0,
 *          .c3 = 0,
 *          .gamma = 1.0/1.961,
 *          .cutoff = -INFINITY,
 *          .c4 = 1,
 *          .c5 = 0
 *      };
 *    @/textblock
 *    </pre>
 *
 *
 *  @param  primaries   A set of x, y tristimulus values to defined the color primaries for the RGB colorspace. Here:
 *
 *          <pre>
 *          @textblock
 *                          x = X/(X+Y+Z),  y = Y/(X+Y+Z)
 *          @/textblock
 *          </pre>
 *
 *                      where X, Y, and Z are from CIEXYZ. z is derived automatically from x and y.
 *  
 *  @param  tf          The transfer function to convert from linear RGB (using above primaries) to non-linear RGB.
 *                      The transfer function here is defined in the style of ITU-R BT.709 and is the inverse
 *                      operation of what appears in a ICC color profile.
 *
 *  @param  flags       Currently the only flag recognized here is  kvImagePrintDiagnosticsToConsole, which may be used to
 *                      debug the colorspace creation when it fails. 
 *
 *  @param  error       May be NULL. If not NULL, a vImage_Error code is written to the memory pointed to by error to
 *                      indicate success or failure of the operation.
 *
 *
 *  @result On success, a non-NULL RGB CGColorSpaceRef will be returned.  The color space has a reference count of 1.
 *          You are responsible for releasing the colorspace when you are done with it to return the memory back
 *          to the system. If error is not NULL, kvImageNoError is written to *error.
 *
 *          On failure, NULL will be returned and one of the following errors is written to *error if error is non-NULL:
 *
 *          <pre>
 *          @textblock
 *          Errors:
 *
 *              kvImageInvalidParameter         tf->gamma = 0       (transfer function is not round-trippable)
 *              kvImageInvalidParameter         primaries define XYZ <-> RGB matrix which is not invertible
 *          @/textblock
 *          </pre>
 *
 *
 */
CGColorSpaceRef vImageCreateRGBColorSpaceWithPrimariesAndTransferFunction( const vImageRGBPrimaries *primaries,
                                                                           const vImageTransferFunction *tf,
                                                                           CGColorRenderingIntent intent,
                                                                           vImage_Flags flags,
                                                                           vImage_Error *error )
                                                                           VIMAGE_NON_NULL(1,2)
                                                                           __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );



/*! @functiongroup  vImageConverterRef creation */
    
/*!
 *  @function vImageConverter_CreateForCGToCVImageFormat
 *
 *  @abstract Create a vImageConverterRef that converts a CoreGraphics formatted image to CoreVideo formatted image
 *
 *  @discussion  This creates a vImageConverterRef which may be used with vImageConvert_AnyToAny to convert a
 *              CoreGraphics formatted image, as described by a vImage_CGImageFormat to CV image data, the format of 
 *              which is given by a vImageCVImageFormatRef.
 *
 *
 *  @param  srcFormat       The vImage_CGImageFormat that describes the pixel format associated with the source image buffers.
 *
 *  @param  destFormat      The vImageCVImageFormatRef that describes the pixel format associated with the destination buffers.
 *
 *  @param  backgroundColor In cases where the source format has an alpha channel and the destination does not (or is kCGImageAlphaNoneSkipFirst/Last)
 *                               the conversion will remove the alpha channel by flattening it against an opaque background color. The background color
 *                               is given as CGFloat[3] {red, green, blue} (sRGB).
 *
 *  @param  flags           The following flags are honored:
 *
 *          <pre>
 *          @textblock
 *              kvImagePrintDiagnosticsToConsole    cause extra information to be sent to Apple System Logger (Console) in case of failure
 *
 *              kvImageHighQualityResampling        In some cases, chroma may have to be up or downsampled as part of the conversion
 *                                                  When this flag bit is set, it instructs the converter to spend extra time to achieve better
 *                                                  image quality.
 *
 *              kvImageDoNotTile                    Disable multithreading in the conversion step when this converter is used with vImageConvert_AnyToAny.
 *          @/textblock
 *          </pre>
 *
 *
 *  @param  error           An optional pointer to a vImage_Error in which the returned error code is written.  
 *                          Error be NULL, in which case no error value will be written.
 *          
 *
 *  @result On success, a non-NULL vImageConverteRef will be returned, suitable for use with vImageConvert_AnyToAny(). If
 *          error is non-NULL, kvImageNoError will be written to *error, indicating success. You must release the 
 *          vImageConverterRef when you are done with it, to return its resources to the system.  It has a reference count of 1.
 *
 *          On failure, a NULL vImageConverteRef will be returned. If error is non-NULL, an error code will be written to 
 *          *error.  Some possible error values:
 *          
 *          <pre>
 *          @textblock
 *          kvImageNoError                      Success. No error occurred. A non-NULL vImageConverterRef will be returned.
 *
 *          kvImageInternalError                Your usage was likely correct, but something appears to be very wrong inside
 *                                              vImage. Please file a bug, with a reproducible example of this failure. Please
 *                                              also try the kvImagePrintDiagnosticsToConsole flag for more information.
 *
 *          kvImageInvalidImageFormat           The vImage_CGImageFormat is invalid. kvImagePrintDiagnosticsToConsole may provide
 *                                              more information.
 *
 *          kvImageInvalidCVImageFormat         The vImageCVImageFormatRef is invalid. Probably, the vImageCVImageFormatRef is
 *                                              incomplete. This can happen when a vImageCVImageFormatRef is created from a 
 *                                              CVPixelBufferRef and that itself has incomplete conversion information. Please 
 *                                              see "vImageCVImageFormatRef Repair" above. kvImagePrintDiagnosticsToConsole
 *                                              may provide more information.
 *
 *          kvImageCVImageFormat_ConversionMatrix   The conversion matrix is missing from the vImageCVImageFormatRef. Please add one.
 *          kvImageCVImageFormat_ChromaSiting       The chroma siting info is missing from the vImageCVImageFormatRef. Please add.
 *          kvImageCVImageFormat_ColorSpace         The colorspace containing primaries and transfer function is missing from the vImageCVImageFormatRef.
 *          @/textblock
 *          </pre>
 *
 *  @seealso    vImageBuffer_InitForCopyToCVPixelBuffer When converting from CVPixelBuffer types with vImageConvert_AnyToAny, the CV format sometimes contains multiple data planes which are in turn represented by multiple vImage_Buffers.
 *  @seealso    vImageConverter_GetDestinationBufferOrder for manual ordering information
 */
    
 vImageConverterRef vImageConverter_CreateForCGToCVImageFormat( const vImage_CGImageFormat *srcFormat,
                                                                vImageCVImageFormatRef destFormat,
                                                                const CGFloat *backgroundColor,
                                                                vImage_Flags flags,
                                                                vImage_Error *error )
                                                                VIMAGE_NON_NULL(1,2)
                                                                __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );
/*!
 *  @function vImageConverter_CreateForCVToCGImageFormat
 *
 *  @abstract Create a vImageConverterRef that converts a CoreVideo formatted image to a CoreGraphics formatted image
 *
 *  @discussion  This creates a vImageConverterRef which may be used with vImageConvert_AnyToAny to do conversions of
 *              CV image data, as described by a vImageCVImageFormatRef to CoreGraphics formatted image data, as 
 *              described by a vImage_CGImageFormat.
 *
 *
 *  @param  srcFormat       The vImageCVImageFormatRef that describes the pixel format associated with the source image buffers.
 *
 *  @param  destFormat      The vImage_CGImageFormat that describes the pixel format associated with the destination buffers.
 *
 *  @param  backgroundColor In cases where the source format has an alpha channel and the destination does not (or is kCGImageAlphaNoneSkipFirst/Last)
 *                               the conversion will remove the alpha channel by flattening it against an opaque background color. The background color
 *                               is given as CGFloat[3] {red, green, blue} (sRGB).
 *
 *  @param  flags           The following flags are honored:
 *
 *          <pre>
 *          @textblock
 *              kvImagePrintDiagnosticsToConsole    cause extra information to be sent to Apple System Logger (Console) in case of failure
 *
 *              kvImageHighQualityResampling        In some cases, chroma may have to be up or downsampled as part of the conversion
 *                                                  When this flag bit is set, it instructs the converter to spend extra time to achieve better
 *                                                  image quality.
 *
 *              kvImageDoNotTile                    Disable multithreading in the conversion step when this converter is used with vImageConvert_AnyToAny.
 *          @/textblock
 *          </pre>
 *
 *
 *  @param  error           An optional pointer to a vImage_Error in which the returned error code is written.
 *                          Error be NULL, in which case no error value will be written.
 *
 *
 *  @result On success, a non-NULL vImageConverteRef will be returned, suitable for use with vImageConvert_AnyToAny(). If
 *          error is non-NULL, kvImageNoError will be written to *error, indicating success. You must release the
 *          vImageConverterRef when you are done with it, to return its resources to the system.  It has a reference count of 1.
 *
 *          On failure, a NULL vImageConverteRef will be returned. If error is non-NULL, an error code will be written to
 *          *error.  Some possible error values:
 *
 *          <pre>
 *          @textblock
 *          kvImageNoError                      Success. No error occurred. A non-NULL vImageConverterRef will be returned.
 *
 *          kvImageInternalError                Your usage was likely correct, but something appears to be very wrong inside
 *                                              vImage. Please file a bug, with a reproducible example of this failure. Please
 *                                              also try the kvImagePrintDiagnosticsToConsole flag for more information.
 *
 *          kvImageInvalidImageFormat           The vImage_CGImageFormat is invalid. kvImagePrintDiagnosticsToConsole may provide
 *                                              more information.
 *
 *          kvImageInvalidCVImageFormat         The vImageCVImageFormatRef is invalid. Probably, the vImageCVImageFormatRef is
 *                                              incomplete. This can happen when a vImageCVImageFormatRef is created from a
 *                                              CVPixelBufferRef and that itself has incomplete conversion information. Please
 *                                              see "vImageCVImageFormatRef Repair" above. kvImagePrintDiagnosticsToConsole
 *                                              may provide more information.
 *
 *          kvImageCVImageFormat_ConversionMatrix   The conversion matrix is missing from the vImageCVImageFormatRef. Please add one.
 *          kvImageCVImageFormat_ChromaSiting       The chroma siting info is missing from the vImageCVImageFormatRef. Please add.
 *          kvImageCVImageFormat_ColorSpace         The colorspace containing primaries and transfer function is missing from the vImageCVImageFormatRef.
 *          @/textblock
 *          </pre>
 *
 *  @seealso    vImageBuffer_InitForCopyFromCVPixelBuffer When converting from CVPixelBuffer types with vImageConvert_AnyToAny, the CV format sometimes contains multiple data planes which are in turn represented by multiple vImage_Buffers.
 *  @seealso    vImageConverter_GetSourceBufferOrder for manual ordering information
 */
vImageConverterRef vImageConverter_CreateForCVToCGImageFormat( vImageCVImageFormatRef srcFormat,
                                                               const vImage_CGImageFormat *destFormat,
                                                               const CGFloat *backgroundColor,
                                                               vImage_Flags flags,
                                                               vImage_Error *error )
                                                               VIMAGE_NON_NULL(1,2)
                                                               __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );

 
/*! @functiongroup  vImage_Buffer Initialization */
    

/*!
 * @function vImageBuffer_InitForCopyToCVPixelBuffer
 *
 * @abstract Initialize an array of vImage_Buffers in the right order to convert a image to a CV formatted image
 *
 * @discussion When converting to CVPixelBuffer types with vImageConvert_AnyToAny, the CV format sometimes contains 
 * multiple data planes which are in turn represented by multiple vImage_Buffers. (These are passed in as an array 
 * of vImage_Buffers to vImageConvert_AnyToAny().)  To make it easier to order the buffers correctly, we provide
 * vImageBuffer_InitForCopyToCVPixelBuffer, which initializes an array vImage_Buffer structs  in the order expected by
 * vImageConvert_AnyToAny. With appropriate flags, the conversion can be made to occur directly into the CVPixelBufferRef 
 * backing store.
 *
 * You are responsible for updating any missing / incorrect color information in the pixelBuffer after writing to it.
 *
 * @param buffers   A pointer to an array of vImage_Buffer structs to be overwritten. The buffers will be initialized 
 *                  in the correct order for use with vImageConvert_AnyToAny and the provided converter. On entry, 
 *                  buffers must point to a valid region of memory of size no smaller than number_of_buffers * 
 *                  sizeof(vImage_Buffer). The number_of_buffers is given by vImageConverter_GetNumberOfDestinationBuffers.
 *                  The buffers pointer may not be NULL.
 *
 * @param converter The converter that will be used to do the conversion.  May not be NULL.
 *
 * @param pixelBuffer   A locked (use CVPixelBufferLockBaseAddress) CVPixelBufferRef.
 *
 * @param  flags    kvImageNoAllocate must be used.  The following flags are allowed:
 *
 *          <pre>
 *          @textblock
 *              kvImageNoFlags                      Default operation.
 *
 *              kvImagePrintDiagnosticsToConsole    Print diagnostic messages to the console in the event an error occurs
 *
 *              kvImageNoAllocate                   Instructs the function to initialized the buffers to directly write to a
 *                                                  locked CVPixelBufferRef. You  may unlock the CVPixelBufferRef after 
 *                                                  vImageConvert_AnyToAny has returned. Once the pixelBuffer is unlocked, 
 *                                                  the vImage_Buffers initialized by this function are no longer valid and 
 *                                                  must be reinitialized.
 *
 *          @/textblock
 *          </pre>
 *
 * @return  The following error codes may be returned:
 *
 *          <pre>
 *          @textblock
 *      kvImageNoError                  Success
 *
 *      kvImageNullPointerArgument      buffers is NULL.
 *      kvImageNullPointerArgument      converter is NULL.
 *
 *      kvImageInvalidParameter         pixelBuffer is not NULL but kvImageNoAllocate was not passed in flags. See pixelBuffer description above.
 *
 *      kvImageUnknownFlagsBit          An unknown / unhandled flags bit was set in flags.
 *
 *      kvImageInternalError            Something is very wrong inside vImage. This shouldn't happen. Please file a bug, along with a 
 *                                      reproducible failure case.
 *          @/textblock
 *          </pre>
 *
 * @seealso ImageConverter_GetDestinationBufferOrder for another method to initialize the vImage_Buffers in the right order for vImageConvert_AnyToAny.
 *
 */
vImage_Error vImageBuffer_InitForCopyToCVPixelBuffer( vImage_Buffer *buffers,
                                                      const vImageConverterRef converter,
                                                      const CVPixelBufferRef pixelBuffer,
                                                      vImage_Flags flags )
                                                      VIMAGE_NON_NULL(1,2,3)
                                                      __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );

/*!
 * @function vImageBuffer_InitForCopyFromCVPixelBuffer
 *
 * @abstract Initialize an array of vImage_Buffers in the right order to convert CV formatted image to another image format
 *
 * @discussion When converting from CVPixelBuffer types with vImageConvert_AnyToAny, the CV format sometimes contains
 * multiple data planes which are in turn represented by multiple vImage_Buffers. (These are passed in as an array
 * of vImage_Buffers to vImageConvert_AnyToAny().)  To make it easier to order the buffers correctly, we provide
 * vImageBuffer_InitForCopyFromCVPixelBuffer, which initializes an array vImage_Buffer structs  in the order expected by
 * vImageConvert_AnyToAny. With appropriate flags, the conversion can be made to occur directly from the CVPixelBufferRef
 * backing store.
 *
 * @param buffers   A pointer to an array of vImage_Buffer structs to be read. The buffers will be initialized
 *                  in the correct order for use with vImageConvert_AnyToAny and the provided converter. On entry,
 *                  buffers must point to a valid region of memory of size no smaller than number_of_buffers *
 *                  sizeof(vImage_Buffer). The number_of_buffers is given by vImageConverter_GetNumberOfSourceBuffers.
 *                  The buffers pointer may not be NULL.
 *
 * @param converter The converter that will be used to do the conversion.  May not be NULL.
 *
 * @param pixelBuffer   A locked (use CVPixelBufferLockBaseAddress) CVPixelBufferRef.
 *
 * @param  flags    kvImageNoAllocate must be used. The following flags are allowed:
 *
 *          <pre>
 *          @textblock
 *              kvImageNoFlags                      Default operation.
 *
 *              kvImagePrintDiagnosticsToConsole    Print diagnostic messages to the console in the event an error occurs
 *
 *              kvImageNoAllocate                   Instructs the function to initialized the buffers to directly read from a
 *                                                  locked CVPixelBufferRef. You  may unlock the CVPixelBufferRef after
 *                                                  vImageConvert_AnyToAny has returned. Once the pixelBuffer is unlocked,
 *                                                  the vImage_Buffers initialized by this function are no longer valid and
 *                                                  must be reinitialized.
 *
 *          @/textblock
 *          </pre>
 *
 * @return  The following error codes may be returned:
 *
 *          <pre>
 *          @textblock
 *      kvImageNoError                  Success
 *
 *      kvImageNullPointerArgument      buffers is NULL.
 *      kvImageNullPointerArgument      converter is NULL.
 *
 *      kvImageInvalidParameter         pixelBuffer is not NULL but kvImageNoAllocate was not passed in flags. See pixelBuffer description above.
 *
 *      kvImageUnknownFlagsBit          An unknown / unhandled flags bit was set in flags.
 *
 *      kvImageInternalError            Something is very wrong inside vImage. This shouldn't happen. Please file a bug, along with a
 *                                      reproducible failure case.
 *          @/textblock
 *          </pre>
 *
 * @seealso  vImageConverter_GetSourceBufferOrder vImageConverter_GetSourceBufferOrder for another method to initialize the vImage_Buffers in the right order for vImageConvert_AnyToAny.
 *
 */
vImage_Error vImageBuffer_InitForCopyFromCVPixelBuffer( vImage_Buffer *buffers,
                                                        const vImageConverterRef converter,
                                                        const CVPixelBufferRef pixelBuffer,
                                                        vImage_Flags flags )
                                                        VIMAGE_NON_NULL(1,2,3)
                                                        __OSX_AVAILABLE_STARTING( __MAC_10_10, __IPHONE_8_0 );



#ifdef __cplusplus
    }
#endif


#endif  /* vImage_vImage_CVUtilities_h */
