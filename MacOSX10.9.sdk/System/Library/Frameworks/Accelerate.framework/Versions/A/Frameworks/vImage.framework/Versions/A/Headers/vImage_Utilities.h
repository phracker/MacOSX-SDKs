/*
 *  vImage_Utilities.h
 *  vImage
 *
 *  Created by Ian Ollmann on 6/7/12.
 *  Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 */

#ifndef vImage_Utilities_h
#define vImage_Utilities_h

#include <vImage/vImage_Types.h>
#include <CoreGraphics/CoreGraphics.h>  /* #define vImage_Utilities_h 1 before including Accelerate headers to turn this header off */

#ifdef __cplusplus
extern "C" {
#endif

/* Decode array constant to use with 16Q12 buffers. Creating your own decode array will not work, because CG defines alpha to always */
/* range from [0, UTYPE_MAX], whereas for the 16Q12 format, it ranges between [0, 4096]. We use the value of the pointer to  */
/* distinguish between the two. */
extern const CGFloat * kvImageDecodeArray_16Q12Format;

/*
 *  vImageBuffer_Init
 *
 *  This function is a convenience method to help initialize a vImage_Buffer struct with a buffer sized 
 *  and aligned for best performance. It will initialize the height, width and rowBytes fields, and allocate 
 *  the pixel storage for you. You are responsible for releasing the memory pointed to by buf->data back to 
 *  the system when you are done with it using free(). If no such allocation is desired, pass  
 *  kvImageNoAllocate in the flags to cause buf->data to be set to NULL and the preferred alignment 
 *  to be returned from the left hand side of the function.
 *
 *  Here is an example of typical usage:
 *
 *      vImage_Buffer buf;
 *      vImage_Error err = vImageBuffer_Init( &buf, height, width, 8 * sizeof(pixel), kvImageNoFlags);
 *      ...
 *
 *  And typical usage using your own allocator (posix_memalign in this case):
 *
 *      vImage_Buffer buf;
 *      ssize_t alignment = vImageBuffer_Init( &buf, height, width, 8 * sizeof(pixel), kvImageNoAllocate);
 *      if( alignment >= 0 )  // <0 is an error
 *          error = posix_memalign( &buf.data, alignment, buf.height * buf.rowBytes );  // An allocator
 *  
 *  Parameters:
 *      buf                 A valid empty vImage_Buffer struct. On return, all fields will be initialized.
 *                          Please see behavior of kvImageNoAllocate in the flags parameter below.
 *
 *      height              The desired height of the image
 *      width               The desired width of the image
 *
 *      pixelBits           The number of bits in a pixel of image data. If the image is in a planar format
 *                          then this is the number of bits per color component. If pixelBits is not divisible
 *                          by 8, then vImage will pad the scanline out to a multiple of a byte so that
 *                          two scanlines can not share the same byte and all scanlines start at the start of 
 *                          a byte.
 *
 *      flags               Must be from the following list:
 *
 *                          kvImageNoAllocate -- on return buf->data is initialized to NULL. A preferred 
 *                              alignment suitable for use with posix_memalign is returned out the left hand 
 *                              side of the function and buf->rowBytes will be set to the preferred rowBytes. 
 *                              If the left hand side return is negative, it is an error code, not a size. 
 *                          
 *                              If the kvImageNoAllocate flag is not passed, then on return buf->data will point 
 *                              to a newly allocated buffer with preferred alignment and rowBytes. An appropriate 
 *                              error code will be returned from the left hand side.
 *
 *                          kvImagePrintDiagnosticsToConsole -- directs the function to print diagnostic information
 *                              to the console in the event of failure. 
 *
 *  Return Value:
 *      On return, buf is initialized to contain the provided height and width and best rowBytes for the image. 
 *      buf->data will also be allocated by default. If kvImageNoAllocate is passed then allocation is skipped, 
 *      buf->data is set to NULL, and the preferred alignment is returned out the left hand side of the
 *      function.  One of the following error codes will be returned out the left hand side.
 *
 *  Error Codes:
 *
 *      >0                              kvImageNoAllocate was passed. The value returned indicates the 
 *                                      preferred alignment (in bytes) for buf->data. buf->data is NULL.
 *
 *      kvImageNoError                  Success
 *
 *      kvImageMemoryAllocationError    you requested that buf->data be allocated but the allocation failed
 *
 *      kvImageUnknownFlagsBit          flags was not from the list above
 */
    
vImage_Error  vImageBuffer_Init( vImage_Buffer           *buf,
                                 vImagePixelCount        height,
                                 vImagePixelCount        width,
                                 uint32_t                pixelBits,
                                 vImage_Flags            flags)
                                 VIMAGE_NON_NULL(1)
                                  __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    

    
/**********************************
 *   Core Graphics interoperation *
 **********************************/
    
/*
 * To create a CGImageRef from a image file on disk, you can do as follows:
 *
 *     CFURLRef path = ...;  // path to image
 *     CGImageSourceRef imageSource = CGImageSourceCreateWithURL( path, optionsDictionary ); // optionsDictionary may be NULL
 *     CGImageRef imageRef = CGImageSourceCreateImageAtIndex( imageSource, imageIndex, optionsDictionary );
 *
 * Similarly, with a chunk of compressed image data in memory:
 *
 *     CFDataRef data = ...;
 *     CGImageSourceRef imageSource = CGImageSourceCreateWithData( path, optionsDictionary );
 *     CGImageRef imageRef = CGImageSourceCreateImageAtIndex( imageSource, imageIndex, optionsDictionary );
 *
 * You can do similar things through AppKit / UIKit with [NSImage initWithContentsOfFile:], 
 * [NSImage initWithContentsOfURL:], or [NSImage initWithData:],  and use [NSImage CGImageForProposedRect:context:hints:]
 * to get out a CGImageRef. 
 *
 * So the remaining problem is how to convert a CGImageRef into a vImage_Buffer and back. Here we present 
 * some APIs to streamline the process:
 */


/* vImage_CGImageFormat
 *
 * This describes the ordering of the color channels, how many there are, the size and type of the data
 * in the color channels and whether the data is premultiplied by alpha or not. This format mirrors the 
 * image format descriptors used by CoreGraphics to create things like CGImage and CGBitmapContextRef. 
 *
 * The byte ordering is applied last. Thus, this vImage_CGImageFormat:
 *
 *      vImage_CGImageFormat format = { 
 *          .bitsPerComponent = 8,
 *          .bitsPerPixel = 32, 
 *          .colorSpace = CGColorSpaceCreateDeviceRGB(),                                    // don't forget to release this!  
 *          .bitmapInfo = kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Little,
 *          .version = 0,                                                                   // must be 0                      
 *          .decode = NULL,             
 *          .renderingIntent = kCGRenderingIntentDefault    
 *      };
 *
 * codes for a little endian ARGB8888 pixel, or what is called in the rest of vImage, BGRA8888. Note: for 16- 
 * and 32-bits per component formats (int16_t, uint16_t, half-float, float) most vImage image filters assume 
 * the data is in host-endian format. (The APIs in this header do not.) Host-endian is little endian for Intel 
 * and ARM, big endian for PowerPC. If the data is not in host-endian format, then you may use 
 * vImagePermuteChannels_ARGB8888 or vImageByteSwap_Planar16U to swap the image data byte ordering.
 *
 * Some examples:
 *      ARGB8888     ->  {8, 32, NULL, alpha first, 0, NULL, kCGRenderingIntentDefault}     alpha first = { kCGImageAlphaFirst, kCGImageAlphaPremultipliedFirst, kCGImageAlphaNoneSkipFirst }
 *      RGBA8888     ->  {8, 32, NULL, alpha last,  0, NULL, kCGRenderingIntentDefault}     alpha last  = { kCGImageAlphaLast,  kCGImageAlphaPremultipliedLast,  kCGImageAlphaNoneSkipLast }
 *      BGRA8888     ->  {8, 32, NULL, alpha first | kCGBitmapByteOrder32Little, 0, NULL, kCGRenderingIntentDefault}
 *      RGB888       ->  {8, 24, NULL, kCGImageAlphaNone | kCGBitmapByteOrderDefault, 0, NULL, kCGRenderingIntentDefault}
 *      RGB565       ->  {5, 16, NULL, kCGImageAlphaNone | kCGBitmapByteOrder16Little, 0, NULL, kCGRenderingIntentDefault}
 *      ARGB1555     ->  {5, 16, NULL, alpha first | kCGBitmapByteOrder16Little, 0, NULL, kCGRenderingIntentDefault}
 *      RGBA16F      ->  {16, 64, NULL, alpha last | kCGBitmapFloatComponents | kCGBitmapByteOrder16Little, 0, NULL, kCGRenderingIntentDefault }
 *      CMYK8888     ->  {8, 32, CGColorSpaceCreateDeviceCMYK(), kCGImageAlphaNone, 0, NULL, kCGRenderingIntentDefault  }
 *      ARGBFFFF premultiplied    ->  {32, 128, NULL, kCGImageAlphaPremultipliedFirst | kCGBitmapFloatComponents | kCGBitmapByteOrder32Little, 0, NULL, kCGRenderingIntentDefault }
 *      ARGBFFFF not-premultiplied -> {32, 128, NULL, kCGImageAlphaFirst | kCGBitmapFloatComponents | kCGBitmapByteOrder32Little, 0, NULL, kCGRenderingIntentDefault }
 *      ARGBFFFF, alpha = 1 ->        {32, 128, NULL, kCGImageAlphaNoneSkipFirst | kCGBitmapFloatComponents | kCGBitmapByteOrder32Little, 0, NULL, kCGRenderingIntentDefault }
 *
 *  Note that some of these formats, particularly RGB565 and 16F formats are supported by vImage but
 *  not necessarily CoreGraphics. They will be converted to a higher precision format as necessary by
 *  vImage in vImageCreateCGImageFromBuffer().
 */
typedef struct
{
    uint32_t                bitsPerComponent;   /* # of bits in each color channel. Expected values: {1, 2, 4, 5, 8, 10, 12, 16, 32}. e.g. Pass 8 for a ARGB8888 image.                     */
    uint32_t                bitsPerPixel;       /* # of bits in each pixel. This is typically bitsPerComponent * (CGColorSpaceGetNumberOfComponents(colorspace) + (hasAlphaChannel?1:0))    */
    CGColorSpaceRef         colorSpace;         /* The color space model for the pixels. See CoreGraphics/CGColorSpace.h. Pass NULL as shorthand for device RGB.                            */
    CGBitmapInfo            bitmapInfo;         /* The CGBitmapInfo describing the color channels. See CoreGraphics/CGImage.h.                                                              */
    uint32_t                version;            /* Reserved for future expansion. Must be 0.                                                                                                */
    const CGFloat           *decode;            /* Decode parameter. See description of CGImageCreate() for its meaning.  NULL indicates a series of {0, 1} pairs.                          */
                                                /*   See also Decode Arrays section of Chapter 4.8 of the PDF specification for a full description.                                         */
    CGColorRenderingIntent  renderingIntent;    /* See CGColorSpace.h. kCGRenderingIntentDefault is typical here. By convention, rendering intent changes that are not accompanied by       */
                                                /*   a colorspace change are ignored.                                                                                                       */
}vImage_CGImageFormat;
     
    
/* 
 *  vImageBuffer_GetSize
 * 
 *  returns height and width of image as CGSize / NSSize, rounded down to
 *  the nearest representable CGFloat that is less than or equal to the
 *  actual size of the image. In practice the conversion will always be 
 *  exact, except for really, really big images. In that case, some part
 *  of the bottom or right edge might be truncated. 
 *                                                                              
 * Rationale: If you attempt your own home-made conversion to CGSize / NSSize by
 *            ordinary C rules and the value rounds, it will round up half the time.
 *            This could lead to a crash later because the height or width
 *            will be reported to be larger than it really is and an ensuing image  
 *            operation will attempt to touch scanlines that don't exist.
 */
CGSize vImageBuffer_GetSize( const vImage_Buffer *buf )
    VIMAGE_NON_NULL(1)
    __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );


/* vImageCGImageFormat_GetComponentCount
 *
 * Convenience function to calculate number of channels (color + alpha) for a given image format
 * If format->colorSpace is NULL, device RGB is used.
 */
uint32_t vImageCGImageFormat_GetComponentCount( const vImage_CGImageFormat *format )
    VIMAGE_NON_NULL(1)
    __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

/*
 * vImageCGImageFormat_IsEqual
 *
 * returns nonzero if two vImage_CGImageFormats are the same
 * if either operand is NULL, the result is false.
 * if vImage_CGImageFormat.colorSpace is NULL, device RGB is used.
 */
Boolean vImageCGImageFormat_IsEqual( const vImage_CGImageFormat *f1,  const vImage_CGImageFormat *f2 )
    __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

    
/* vImageBuffer_InitWithCGImage
 *
 * This function will initialize a vImage_Buffer struct with an image from a CGImageRef.
 * By default, a new region of memory to hold the image data will be allocated by this function. It is your
 * responsibility to return this memory to the system using free() when you are done using it. You may
 * optionally allocate the memory region yourself by passing in the kvImageNoAllocate flag. 
 *
 * You may release the CGImageRef and format->colorspace upon successful return of this function.
 *
 * Paramters:
 *
 *  buf             A pointer to a valid vImage_Buffer struct. The fields of the structure pointed to by buf will
 *                  be updated to point to a vImage_Buffer representation of the CGImage. By default, a newly 
 *                  allocated piece of memory will be used to hold the image. You are responsible
 *                  for releasing the memory pointed to by buf->data back to the system using free().
 *
 *                  If you want to allocate the buf->data and initialize rowBytes yourself, then you may pass 
 *                  kvImageNoAllocate in the flags parameter. This will cause the buf->data and rowBytes values  
 *                  passed into the function to be used directly without modification.  You may find vImageBuffer_Init,  
 *                  vImageCGImageFormat_GetPixelBits, CGImageGetWidth and CGImageGetHeight helpful in sizing your buffer.
 *
 *  format          The desired image format associated with the output buf. You may pass NULL for the colorspace,
 *                  in which case device RGB will be used. 
 *
 *  backgroundColor If the CGImageRef encodes an alpha (or mask) and the output format does not have alpha then the
 *                  result will be flattened against a background color. See vImageConverter_CreateWithCGImageFormat
 *                  and functions like vImageFlatten_ARGB8888ToRGB888 for more on flattening. The background color here is
 *                  a series of values of range [0,1] interpreted according to the colorspace passed in format. Example: If 
 *                  the format encodes for a AGBR 8-bit image (kCGImageAlphaLast, kCGBitmapByteOrder32Little), then this would be
 *                  {red, green, blue}, the canonical ordering for a RGB colorspace, as an array of three CGFloats.  
 *                  If NULL is passed, an array full of zeros is used. The backgroundColor must have at least as many
 *                  CGFloats in it as the colorspace has color channels. See CGColorSpaceGetNumberOfComponents.
 *
 *  image           a valid CGImageRef to be used as source data.
 *
 *  flags           You may set the following flags:
 *
 *                  kvImageNoAllocate       the buf->data and buf->rowBytes values passed in are used without modification.
 *                                          This allows you to allocate your own buffer to hold the result. See buf description
 *                                          above.
 *
 *                  kvImagePrintDiagnosticsToConsole    In the event of a problem, print out some helpful debug messages.
 *
 *                  kvImageDoNoTile         It is possible that vImage will have to do an image format conversion from the
 *                                          image native format to the desired format. This will turn off multithreading for
 *                                          that step and any other vImage work that is multithreaded. Since any such conversions
 *                                          are likely happening outside your tiling engine, use of this flag here is 
 *                                          probably counterproductive. In rare cases, it might be valuable as a method to 
 *                                          leave unoccupied some cores for other tasks, if you have other multithreaded time 
 *                                          sensitive tasks running. Likewise, if you are converting multiple images concurrently,
 *                                          it might be helpful to avoid oversubscribing the system.
 *                                          
 *
 *  Return Values:
 *      If the call succeeds, kvImageNoError is returned and the memory region pointed to by buf will be initialized to 
 *      describe a valid repesentation of the CGImageRef. 
 *
 *      If the call fails, then one of the following error codes will be returned and buf->data will be set to NULL.
 *
 *          kvImageUnknownFlagsBit              flags must be kvImageNoFlags or kvImageNoAllocate
 *          kvImageMemoryAllocationError        Not enough memory to allocate buf->data 
 *          kvImageInvalidParameter             format->bitmapInfo has unknown bits set
 *          kvImageInvalidParameter             format->version is not 0
 *          kvImageInvalidParameter             format->decode is not NULL
 *          kvImageInvalidParameter             format->bitsPerComponent is not in {0,1,2,4,5,8,16,32}
 *          kvImageInvalidImageFormat           format->renderingIntent is not a known value
 *          kvImageNullPointerArgument          format may not be NULL
 *          kvImageNullPointerArgument          image may not be NULL
 *          kvImageInternalError                Something unexpected went wrong. Please file a bug. 
 *
 *  You are responsible for returning the memory referenced by buf->data to the system using free() when you are done with it. 
 */
    
vImage_Error vImageBuffer_InitWithCGImage(  vImage_Buffer        *  buf,            /* A pointer to a vImage_Buffer struct to be overwritten */
                                            vImage_CGImageFormat *  format,         /* see above. May not be NULL. */
                                            const CGFloat        *  backgroundColor,/* see above. May be NULL, which indicates all 0's in the destination color format */
                                            CGImageRef              image,          /* the CGImageRef from which to make the vImageRef */
                                            vImage_Flags            flags  )        /* see flags above  */
                                            VIMAGE_NON_NULL(1,2,4)
                                            __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );  


        
/* 
 * vImageCreateCGImageFromBuffer
 *
 * This function creates a CGImageRef using the image data in a vImage_Buffer. The CGImageRef has a retain count of 1.
 * By default, a copy of the image data is made. This allows the function to convert to a CG-friendly format as necessary
 * and allows you to continue to use the vImage_Buffer without causing problems for the CGImageRef. 
 *
 * No copy mode
 * ------------
 * When the kvImageNoAllocate flag is passed, then "no-copy" operation is said to occur. Ownership of the memory region  
 * pointed to by buf->data is transferred to the CGImageRef and it becomes private to and owned by that object and will 
 * be used without modification. The memory region pointed to by buf->data will be destroyed when the CGImageRef is 
 * destroyed. Caution: CGImageRefs are defined to be immutable once created. Behavior is undefined if you create
 * a CGImageRef then modify the pixels in its backing store.
 *
 * No-copy mode can be a little fussy about formats. When a format is rejected, kvImageInvalidImageFormat will be returned. 
 * Formats that are likely to succeed are 8-bit unsigned, 16-bit unsigned and 32-bit floating-point. The image should be 
 * kCGImageAlphaNone, kCGImageAlphaLast, kCGImageAlphaPremultipliedLast or kCGImageAlphaNoneSkipLast, and decode = NULL. 
 * The image should be in host endian mode. This is kCGBitmapByteOrderDefault for 8-bit per component images, and or larger 
 * types, the endianness is given by the endianness of the host system and the size is given by the size of the pixel 
 * (bitsPerComponent < 8) or channel (bitsPerComponent > 8). For example RGB565 data should be kCGBitmapByteOrder16Little 
 * and 32-bit floating point data should be kCGBitmapByteOrder32Little on little endian processors. 
 *
 * It is recommended that if no-copy mode fails, that you try again without the kvImageNoAllocate flag. The call probably 
 * will succeed.
 *
 * Parameters:
 * -----------
 *  buf             The vImage_Buffer from which to make the CGImageRef
 *
 *  format          The image format of the vImage_Buffer. format may not be NULL.  format->colorspace may be NULL, 
 *                  in which case device RGB will be used.  The colorspace is retained as needed by the new CGImage. 
 *
 *  callback        In no-copy mode, this callback is called to destroy the buf->data when the CGImageRef no longer needs it. 
 *                  If NULL is passed for the callback, then free() will be used to destroy buf->data.  userData will be 
 *                  passed to the callback function as the userData parameter and buf->data passed as the buf_data parameter.
 *
 *                  This parameter has no effect if kvImageNoAllocate is not in flags. 
 *
 *                  The callback may be called at any time from any thread. It is possible for it to be called before 
 *                  vImageCreateCGImageFromBuffer returns.  
 *
 *                  The callback will not be called if the returned CGImageRef is NULL.
 *
 *  userData        The value to pass to the callbacks userData parameter. If callback is NULL or kvImageNoAllocate
 *                  is passed in flags, this value is ignored.  
 *                  
 *  flags           The following flags are allowed:
 *
 *                  kvImageNoAllocate                   Causes vImageCreateCGImageFromBuffer to run in no-copy mode.
 *                                                      Ownership of the memory pointed to by buf->data is transferred 
 *                                                      to the CGImageRef.  You'll need to set up a callback and userData
 *                                                      to manage releasing the memory back to the system when the CGImage
 *                                                      is done with it.
 *
 *                  kvImagePrintDiagnosticsToConsole    In the event of a problem, print out some helpful debug messages.
 *
 *                  kvImageHighQualityResampling        Sometimes the system will ask for the image to be resampled to
 *                                                      a smaller size. If that happens vImageAffineWarp_<fmt> will be
 *                                                      called. In that case, the value of this bit will be used to
 *                                                      determine whether Lanczos3 or Lanczos5 resampling is used.
 *
 *                  kvImageDoNotTile                    Disables multithreading in any conversions that need to be done.
 *                                                      Since it seems likely any such conversions will not be running in
 *                                                      the context of your tiling engine (if you wrote one) in this case, 
 *                                                      this flag is probably counterproductive in this context. Conversions
 *                                                      can happen later, after this call returns, when the image is drawn.
 *
 *  error           if not NULL, points to a more informative error code to describe what went wrong on exit. May be NULL.
 *                  Testing the result against NULL is sufficient to detect success or failure. kvImagePrintDiagnosticsToConsole
 *                  is another way to get error information.
 *
 * Return Value:
 *      On success, the returned CGImageRef will be non-NULL. If error is not NULL, kvImageNoError will be written there. 
 *      On failure, NULL will be returned, and if error is not NULL, a more informative error code will be written there. 
 *          
 *  Error Values:
 *      kvImageUnknownFlagsBit              flags was not from the list described in the flags parameter above
 *      kvImageMemoryAllocationError        Not enough memory to allocate the new CGImageRef
 *      kvImageInvalidParameter             format->bitmapInfo has unknown bits set
 *      kvImageInvalidParameter             format->bitsPerComponent is not in {5,8,16,32}
 *      kvImageInvalidImageFormat           format->renderingIntent is not a known value
 *      kvImageNullPointerArgument          format may not be NULL
 *      kvImageNullPointerArgument          buf may not be NULL
 *
 */
    
CGImageRef vImageCreateCGImageFromBuffer( const vImage_Buffer *buf,
                                          const vImage_CGImageFormat *format,
                                          void (*callback)(void *userData, void *buf_data),
                                          void *userData,
                                          vImage_Flags flags,
                                          vImage_Error *error )
                                          VIMAGE_NON_NULL(1,2)
                                          __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );     
    

    
    
/*
 *  vImageConverter
 *
 *  The vImageConverter is an opaque type which contains information needed to do a rapid conversion from
 *  one image type to another. Sometimes, it can take a significant amount of time to figure out how to convert
 *  from one format to another. It wouldn't be good to do that redundantly for a bunch of small images. The 
 *  vImageConversionSetup allows us to set up the conversion once and reuse the information many times, to 
 *  keep net latencies low. 
 *
 *  Note that creating a vImageConverter can at times take a while. While usually it is quick, it might have
 *  to do things like load other frameworks in the system (e.g. Colorsync) if they are not loaded already,
 *  or build a lookup table. It is a good idea to setup your conversions in advance and reuse the conversion
 *  objects.  The objects are thread safe. You can use the same object in multiple threads concurrently. They
 *  follow standard retain / release semantics and can be used as CFTypeRefs.
 */
    
typedef struct vImageConverter * vImageConverterRef;

/*
 *  vImageConverter_Retain
 *  vImageConverter_Release
 *
 *  These provide for standard retain and release semantics for the vImageConverter. vImageConverter objects
 *  are created with a reference count of 1.  Use vImageConverter_Release to decrement the count by 1.  Use
 *  vImageConverter_Retain to increment the count by 1.  When the reference count reaches 0, the object is 
 *  destroyed.
 *
 *  Like all of vImage, these interfaces are thread safe and may be called reentrantly. 
 *
 *  Parameters:
 *
 *      converter           The vImageConverter to retain or release. If NULL, then nothing happens.
 *
 */
void vImageConverter_Retain( vImageConverterRef converter ) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
void vImageConverter_Release( vImageConverterRef converter ) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 ); 


/*
 *  vImageConverter_CreateWithCGImageFormat
 *
 *  Creates a vImageConverter for image types common to CoreGraphics.  The vImageConverter is intended
 *  to be used (and reused, possibly reentrantly) with vImageConvert_AnyToAny to convert images from one
 *  format to another.
 *
 *  Parameters:
 *      srcFormat       a pointer to a populated vImage_CGImageFormat struct describing the image format
 *                      of the source image. If the CGColorSpaceRef is NULL, device RGB will be used
 *                      as the default value. The CGColorSpaceRef will be retained by this function. It
 *                      will be released when the vImageConverter is destroyed.
 *
 *      destFormat      a pointer to a populated vImage_CGImageFormat struct describing the image format
 *                      of the destination image. If the CGColorSpaceRef is NULL, device RGB will be
 *                      used as the default value. The CGColorSpaceRef will be retained by this function.
 *                      It will be released when the vImageConverter is destroyed.
 *
 *      backgroundColor Points to an array of floats to be used as a background color if one is needed. The 
 *                      backgroundColor range is assumed to be [0,1]. The channel ordering and number of color 
 *                      channels must match the natural order of the destination colorSpace (e.g. RGB or CMYK). 
 *                      The backgroundColor may be NULL if no background color is needed. 
 *
 *                      A background color is used when the image is converted from an alpha-containing format 
 *                      to an alpha-none format, in which case the alpha is removed by compositing against the 
 *                      opaque background color pointed to by this parameter. If the image is instead converted 
 *                      from one alpha containing format to another, then the image will be premultiplied or 
 *                      unpremultiplied as necessary and no background color is necessary. (For unpremultiplication, 
 *                      the result color value for pixels with alpha 0 is 0.)  Likewise, when converting between
 *                      alpha-none formats, a background color is not use. In the case of kCGImageAlphaNone ->
 *                      kCGImageAlphaNoneSkipFirst/Last, the vacant alpha channel is filled in with 1.0. If NULL
 *                      is passed here, then 0 will be used for the color channels. 
 *
 *                      The vImageConverter will contain a copy of the data passed in this field.  
 *
 *      flags           Any of the following flags are allowed:
 *
 *                      kvImagePrintDiagnosticsToConsole    In the event of a problem, print out some helpful debug 
 *                                                          messages.
 *
 *                      kvImageDoNotTile                    A converter created with this flag will operate as if
 *                                                          kvImageDoNotTile was passed to vImageConvert_AnyToAny
 *                                                          whether it was or not.
 *
 *      error           May be NULL.  If not NULL, then a vImage_Error is returned here. The vImage_Error will
 *                      be less than 0 if an error condition occurred. Checking the vImageConverter to make sure
 *                      it is non-NULL is sufficient to verify success or failure of the function.
 *
 *  Return value:
 *      A vImageConverter object with reference count of 1 is returned. If the call fails due to an error, then NULL 
 *  will always be returned. Use vImageConverter_Release to release your reference to it and allow the resources used 
 *  by the converter to be returned to the system.
 *
 *  If error is not NULL, an error code will be written to that address on return. See below:
 *
 *  Error Values:
 *      The following error values can occur. In cases where the error code is not sufficient to quickly determine
 *      the problem, the kvImagePrintDiagnosticsToConsole flag should provide additional diagnostic info.
 *
 *      kvImageNoError                      Success. 
 *
 *      kvImageNullPointerArgument          srcFormat and/or destFormat is NULL.
 *
 *      kvImageUnknownFlagsBit              Currently only kvImagePrintDiagnosticsToConsole and kvImageDoNotTile are 
 *                                          allowed. All other bits in the flags field must be 0.
 *
 *      kvImageInvalidParameter             backgroundColor is NULL and the conversion needed a backgroundColor
 *
 *      kvImageInvalidImageFormat           bitsPerComponent must be in {1,2,4,5,8,12,16,32}.
 *      kvImageInvalidImageFormat           The base colorspace must be grayscale for destination images using indexed color.
 *      kvImageInvalidImageFormat           The colorspace may be indexed color for images only if it is {1,2,4,8} bitsPerComponent
 *                                          and kCGImageAlphaNone.
 *      kvImageInvalidImageFormat           vImage_CGImageFormat.bitmapInfo & kCGBitmapAlphaInfoMask  does not encode a valid alpha
 *      kvImageInvalidImageFormat           floating point formats must be 16 or 32 bits per component. 16-bit floats are  
 *                                          IEEE-754-2008 binary16 interchange format  (a.k.a. OpenEXR half float). 32-bit floats 
 *                                          are the standard IEEE-754-2008 binary32 interchange format. (a.k.a float in C/C++/ObjC)
 *      kvImageInvalidImageFormat           format->renderingIntent is not a known value
 *
 *      kvImageInternalError                The converter was unable to find a path from the source format to the destination format.
 *                                          This should not happen and indicates incorrect operation of the function. Please file a bug.
 *                                          The kvImagePrintDiagnosticsToConsole flag will provide additional diagnostic info.
 *
 *  Image Format Notes:
 *      CG Integer images map the range [0,1.0] (black to full color intensity) to the range [0, TYPE_MAX]. A 8-bit unsigned image
 *  has a range [0,255] and a 16-bit signed image has a range [0,32767]. Floating point images map [0,1.0] to [0,1.0]. Some formats,
 *  like floating-point and signed integers are capable of representing values outside of that range. Conversions involving these
 *  formats will occasionally produce results outside of [0,1]. If the conversion causes a value to go out of the representable range
 *  for the underlying type, it will be clamped to the nearest representable value. This can happen in normal operation during color 
 *  correction. You can clamp floating-point results back into [0,1] using vImageClip_PlanarF, if you like.
 *
 *      Usually, colors must be direct mapped. Indexed color is supported format->bitsPerComponent and format->.bitsPerPixel are 1,2,4 
 *  or 8, and equal (i.e. grayscale) only. Indexed color is not supported for the destination image. Images with indexed color must use 
 *  (kCGImageAlphaNone | kCGBitmapByteOrderDefault) as the bitmapInfo. It is usually faster with indexed color spaces to use 
 *  vImageConvert_AnyToAny to convert the color table rather than the image itself when possible, because the table is usually much 
 *  smaller than the image. vImageConvert_AnyToAny can not do that automatically for you behind the scenes because it does not return 
 *  a modified colorspace.
 *
 *  Device Colorspaces:
 *  Because vImage has no concept of a rendering context or destination graphics device, vImage maps device RGB, device grayscale 
 *  and device CMYK to a virtual device which is not your display. The virtual device uses kColorSyncGenericGrayGamma22Profile, 
 *  kColorSyncSRGBProfile and kColorSyncGenericCMYKProfile respectively. If you want the image to be converted to the right colorspace 
 *  for your display device, you will need to pass in the CGColorSpaceRef for that device obtained from an API like CGDisplayCopyColorSpace().
 *
 *  Black Point Compensation:
 *  By default, BPC is off for this function. If you want black point compensation or other advanced ColorSync effects, construct your
 *  own ColorSyncTransformRef and pass the associated "code fragment" to vImageConverter_CreateWithColorSyncCodeFragment.
 */
 
vImageConverterRef vImageConverter_CreateWithCGImageFormat( const vImage_CGImageFormat *srcFormat,
                                                            const vImage_CGImageFormat *destFormat,
                                                            const CGFloat *backgroundColor,          
                                                            vImage_Flags flags,
                                                            vImage_Error *error )
                                                            VIMAGE_NON_NULL(1,2)
                                                            __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );


/*
 *  vImageConverter_CreateWithColorSyncCodeFragment
 *
 *  vImageConverter_CreateWithColorSyncCodeFragment is like vImageConverter_CreateWithCGImageFormat, except that
 *  instead of creating its own colorspace transform for any colorspace conversions, it uses the one you pass in.
 *  This gives you greater control over the fine details of colorspace conversion, for exacting color fidelity.
 *  The colorspaces for source and destination images must refer to colorspaces that have the same number of channels
 *  as the codeFragment is designed to accept / produce.
 *
 *  Parameters:
 *      See vImageConverter_CreateWithCGImageFormat above for a description of most parameters
 *
 *      codeFragment    A code fragment created with ColorSyncTransformCopyProperty( kColorSyncTransformFullConversionData,
 *                      kColorSyncTransformParametricConversionData or kColorSyncTransformSimplifiedConversionData)
 *                      May be NULL.  If NULL, no colorspace conversion / correction is done. In this case, 
 *                      behavior is undefined if the colorspaces do not have the same channel order or have a 
 *                      different number of channels or the colorspaces are not from the same family. 
 *                      kColorSyncTransformFullConversionData is required for black point compensation.
 *
 *  Error Values:
 *      See vImageConverter_CreateWithCGImageFormat above for a description of most errors.
 *
 *      kvImageInvalidImageFormat       codeFragment was found to be otherwise invalid / unusable
 */
    
vImageConverterRef vImageConverter_CreateWithColorSyncCodeFragment( CFTypeRef codeFragment,
                                                                    const vImage_CGImageFormat *srcFormat,
                                                                    const vImage_CGImageFormat *destFormat,
                                                                    const CGFloat *backgroundColor,         
                                                                    vImage_Flags flags,
                                                                    vImage_Error *error )
                                                                    VIMAGE_NON_NULL(1,2)
                                                                    __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

    
/*
 *  vImageConverter_MustOperateOutOfPlace
 *
 *  Returns kvImageOutOfPlaceOperationRequired if the conversion requires different buffers for input 
 *  and output data. In-place operation is considered to mean srcs[i].data = dests[i].data 
 *  and srcs[i].rowBytes = dests[i].rowBytes. Other styles of partial buffer overlap produce undefined behavior. 
 *
 *  The list of source and destination buffers is optional. Results are as follows:
 *
 *      srcs = dests = NULL         kvImageNoError if any conversion with this converter is guaranteed to work in place,
 *                                  provided that srcs[i].data = dests[i].data and srcs[i].rowBytes = dests[i].rowBytes.
 *                                  If there exists at least one combination of height and width for which in place operation
 *                                  is not possible with this converter, then kvImageOutOfPlaceOperationRequired will be returned. 
 *
 *      srcs != NULL, dests = NULL  kvImageNullPointerArgument
 *      srcs = NULL, dests != NULL  kvImageNullPointerArgument
 *  
 *      srcs != NULL, dests != NULL kvImageNoError if the conversion will successfully operate in place for this particular 
 *                                  combination of heights, widths and rowBytes. In this case, vImage does not check to see if the 
 *                                  buffers overlap. It presumes that srcs[i].data = dests[i].data.  This is intended to allow 
 *                                  you to defer allocation until later.  If in place operation will not work, then 
 *                                  kvImageOutOfPlaceOperationRequired is returned. 
 *
 *  In no case during this function call does vImage examine the contents of the memory pointed to by srcs[i].data or dests[i].data. 
 *
 *  Parameters:
 *      converter           The converter to check
 *
 *      srcs                The list of source buffers you plan to use with vImageConvert_AnyToAny. May be NULL.
 *      dests               The list of destination buffers you plan to use with vImageConvert_AnyToAny. May be NULL.
 *
 *      flags               The flags you plan to pass to vImageConvert_AnyToAny. 
 *
 *                              Note: in the case of kvImagePrintDiagnosticsToConsole, the flag means print 
 *                              error information to the console for errors caught by vImageConverter_MustOperateOutOfPlace,  
 *                              not vImageConvert_AnyToAny. At times, vImageConverter_MustOperateOutOfPlace may fail because 
 *                              it detects an error condition that would cause vImageConvert_AnyToAny to fail.
 *
 *  Error Codes:
 *      kvImageNoError                      In-place operation will work
 *      kvImageNullPointerArgument          The converter may not be NULL
 *      kvImageNullPointerArgument          srcs and dests must either both be NULL or neither must be NULL. 
 *      kvImageInvalidParameter             The converter is invalid
 *      kvImageUnknownFlagsBit              An unknown / unsupported flag was used
 *      kvImageOutOfPlaceOperationRequired  vImageConvert_AnyToAny requires separate buffers be used for this operation
 */
vImage_Error vImageConverter_MustOperateOutOfPlace( const vImageConverterRef converter,
                                                    const vImage_Buffer *srcs,
                                                    const vImage_Buffer *dests,
                                                    vImage_Flags flags)
                VIMAGE_NON_NULL(1)
                __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    
    
/*
 *  vImageConvert_AnyToAny
 *
 *  With an appropriately configured vImageConverter, convert the image channels found in srcs
 *  to the image channels found in dests.
 *
 *  Parameters:
 *      srcs        a pointer to an array of vImage_Buffer structs that describe the color planes that make
 *                  up the input image. Please see the description of the function that created the
 *                  vImageConverter for the ordering and number of input buffers.
 *
 *     dests        a pointer to an array of vImage_Buffer structs that describe the color planes that make
 *                  up the result image. Please see the description of the function that created the
 *                  vImageConverter for the ordering and number of output buffers.
 *
 *   tempBuffer     May be NULL. If not NULL, the memory pointed to by tempBuffer will be used as scratch space
 *                  by the function. The size of the tempBuffer can be determined by passing kvImageGetTempBufferSize
 *                  to the in the flags parameter. See below. If NULL is passed here and a tempBuffer is needed '
 *                  (temp buffer size > 0) then the function will allocate one on the heap and free it before
 *                  returning. This may run more slowly, both because of the allocation cost and the cost of VM
 *                  faults to zero fill pages as they are used. NULL is the right option when the function is
 *                  used infrequently or convenience is valued.
 *
 *     flags        The following flags are allowed. Other flags will trigger an error.
 *
 *                  kvImagePrintDiagnosticsToConsole    In the event of a problem, print out some helpful debug messages.
 *
 *                  kvImageGetTempBufferSize            No image conversion work is done. The value returned out the
 *                                                      left hand side of the function is the an error code if it is
 *                                                      less than zero. Otherwise, it is the size of the tempBuffer
 *                                                      to be passed into the function. The size may be 0.
 *
 *                  kvImageDoNotTile                    Disables internal multithreading.  You may wish to pass this
 *                                                      flag if you are doing your own threading and think it will
 *                                                      conflict with vImage's attempts to do the same.
 *
 *  Operating in place
 *      Please use vImageConverter_MustOperateOutOfPlace() to determine whether a particular conversion can operate in place. 
 *  For an in-place conversion to work, it is required that srcs[i].data = dests[i].data and srcs[i].rowBytes = dests[i].rowBytes. 
 *
 *  Flags:  Flags may be drawn from any combination of the following list. 
 *
 *      kvImageDoNotTile                    Disables internal multithreading. You may wish to do this if the function is
 *                                          called within the context of your own threaded tiling code. 
 *      kvImagePrintDiagnosticsToConsole    On failure, additional information will be printed to the console.
 *      kvImageNoFlags                      No flags.
 *
 *  Error codes:
 *      kvImageNoError                      Success!
 *      kvImageMemoryAllocationError        NULL was passed in tempBuffer and vImage failed to allocate its own
 *                                              temp buffer
 *      kvImageBufferSizeMismatch           The source buffer(s) must be at least as large as the destination buffer(s)
 *                                           (src.height >= dest.height && src.width >= dest.width)
 *      kvImageUnknownFlagsBit              A flag was passed to the vImageConverter creation function which is
 *                                          unrecognized or not appropriate to this function
 *      kvImageNullPointerArgument          converter is NULL
 *      kvImageInvalidParameter             One of the buffers pointed to by srcs or dests has a NULL vImage_Buffer.data pointer
 *      kvImageUnknownFlagsBit              An unknown or unsupported flags bit was set.
 *      kvImageInvalidImageFormat           if a byte ordering is specified (e.g. kCGBitmapByteOrder16Little), the buffer.rowBytes
 *                                          must be multiple of 2 (kCGBitmapByteOrder16Little, kCGBitmapByteOrder16Big) or
 *                                          4 (kCGBitmapByteOrder32Little, kCGBitmapByteOrder32Big)
 *
 *  Please see description below for alignment and endianness requirements and performance tips. 
 *
 */
vImage_Error vImageConvert_AnyToAny( const vImageConverterRef converter,
                                     const vImage_Buffer * srcs,    /* an array of vImage_Buffer structs describing source data planes */
                                     const vImage_Buffer * dests,   /* an array of vImage_Buffer structs describing destination data planes */
                                     void  *tempBuffer,             /* may be NULL */
                                     vImage_Flags  flags
                                    )
                                    VIMAGE_NON_NULL(1,2,3)
                                    __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    
/*
 *  General vImage alignment requirements:
 *  ======================================
 *  All scanlines must be at least byte aligned
 *      A single byte of image data may not span multiple rows of the image.  For example, if the image is 1 bit per pixel monochrome, then
 *      8 pixels fit in a byte. If the width of such an image is not divisible by 8, then the potential exists that the first part of a byte might
 *      lie in one image row and the rest of the byte in the next. It would even be possible that one byte could span up to 8 scanlines if the
 *      image width is 1 pixel! These cases are not allowed. Implicit in the design of using a rowBytes instead of a rowBits describe the image
 *      is that each row must be exactly an integral number of bytes. When the width of the image is such that it would not naturally be so, the
 *      caller must pad out the remaining bits on the image row so that the next row starts on a byte boundary. This is done by setting the rowBytes
 *      to be at least (width * bitsPerPixel + 7) / 8 bytes. When planar images are used then this becomes rowBytes = (width * bitsPerComponent + 7) / 8.
 *
 *      In many cases, images that do not pad rows out to an integral number of bytes can still be processed by vImage by setting
 *      width = height * width and height = 1. However, operating on images with a single row may defeat internal multithreading, so performance
 *      may suffer. (Please use kvImageDoNotTile to defeat internal multithreading if that is your goal. That is its purpose.)  Cleverer schemes that
 *      redivide the image into a larger number of byte aligned rows may be devised.
 *
 *  Some image formats must have 2- or 4-byte aligned scanlines and may need to be host endian
 *      Images with components that are 16-bits in size (e.g. 16U and half float images) or pixels which are 16-bits in size and which do not
 *      have channel boundaries at byte boundaries (e.g. RGB565 and ARGB1555, but not GrayscaleAlpha88) must have vImage_Buffer.data 2-byte aligned and
 *      vImage_Buffer.rowBytes a multiple of 2. Likewise, 32-bits per component (e.g. float or a putative ARGB-2-10-10-10 format) must be 4 byte aligned
 *      and rowBytes a multiple of 4. Failure to conform to 2- and 4-byte alignment restrictions may result in undefined behavior -- at minimum poor
 *      performance and on some systems it can cause a program fault.
 *
 *      Except where otherwise explicitly allowed by the vImageConverter_Create function (e.g. vImage_CGImageFormat.bitmapInfo might be kCGBitmapByteOrder16Big
 *      even on little endian systems) these cases must also conform to the native endianness of the host system. For example, floating-point data on an Intel
 *      system is normally expected to be little-endian unless the converter provides a means to say that it is not. Please see the vImageConverter_Create
 *      function that you plan to use for additional restrictions that may apply.
 *
 *  Performance tips:
 *  =================
 *
 *  Alignment
 *  ---------
 *  Performance will typically improve with even greater alignment up to cacheline aligned image rows. vImageBuffer_Init() can be used to get vImage's
 *  estimation of what sort of row padding is generally likely to work best on the current machine for a given image and pixel size. 
 *
 *  Memory reuse
 *  ------------
 *  It can also be quite helpful to reuse vImage_Buffers and operate in-place so as to avoid spending time in zero-fill faults zeroing the contents 
 *  of newly allocated buffers. (These will show up in Instruments traces as time spent in kernel VM activity.) However, caching unused buffers for 
 *  extended periods of time can contribute to degradation of overall system performance in low memory situations so recycling of buffers is usually 
 *  best done when good temporal locality is expected. LibCache may be helpful for avoiding such problems when it is not known with certainty that the 
 *  buffer will be reused immediately.
 *
 *  Tiling and multithreading
 *  -------------------------
 *  Most vImage functions, including vImageConvert_AnyToAny, will automatically split up work across multiple processors (when available) if there is 
 *  enough image data to warrant it. It can take some time to wake up other processors or redirect their attention from their current task to a new one, 
 *  so multithreading is not attempted if it seems likely the current processor can complete the work before the attention of the other cores can be 
 *  redirected to work on the problem. With some exceptions, the work is typically divided at boundaries between image rows. (To be clear, tiles can be 
 *  taller than just one row.) So, for some functions, if you break up the work to one scanline at a time, it will never multithread. Exactly which functions
 *  do that is subject to change. If you want to stop multithreading, please use kvImageDoNotTile.
 *  
 *  The size of the tile chosen by the function varies by function. Some do little computation and so need the lowest possible load/store latencies to 
 *  run at top speed. Others do more work per byte are consequently not so dependent on low memory access latencies, so may work equally well with tiles 
 *  closer to the size of the L2 or L3 caches and so may use larger tiles. Some computationally intense functions may not care if the data is in cache 
 *  at all. Each vImage function will tile its workload as it sees fit without regard to what other vImage functions may have done or plan to do. 
 *
 *  While this scheme generally works well, you can often do much better with a little work especially in cases where multiple vImage functions are called 
 *  back to back for a few reasons: 
 *
 *      First of all, if the image is larger than the caches, then as new pixels are produced, they will cause earlier result pixels from the same image 
 *  to be flushed to more remote levels of the cache or ultimately out to DRAM (or even disk in low memory situations!) to make room for the new results. When 
 *  it is time to call the next vImage function on the result, you may find that even though you just worked on it, part of the image is not in the cache and 
 *  so you have to pay some time to load it back in again when it as needed. This can happen over and over again with each new vImage filter.  A similar 
 *  story may occur for smaller images as data is flushed from level 1 to level 2 to level 3 of the cache to make room for new data. It would be faster if 
 *  you could somehow move on to the next vImage filter while a region of the image is still in the cache before it is evicted to make room for the rest 
 *  of the image. We will get to the how a little later. 
 *
 *      Second, since processor cores are usually assigned by vImage to work on parts of the image on a first-come first-served basis to keep per-call latency
 *  down, it is probably common that different cores will work on different parts of the image in each successive vImage call, even in cases where the tiling 
 *  strategies between two back to back vImage calls are otherwise similar. That is, in the first vImage function call, the top left corner might be done by 
 *  processor 1 and in the next vImage function call by processor 3. The next time you call the same code, it might be processor 2 and processor 5 that do 
 *  the work on that region. Unfortunately, in many current processor architectures, the faster cache levels (level 1 and 2) are often not shared with most 
 *  of the other cores and it can take more time for the other cores to get data from them. It would be faster if you could somehow convince the same core to 
 *  operate on the same region of the image each time, because only then do we have some guarantee that the faster cache levels are doing us any good between 
 *  back to back calls.
 *
 *      Third, just as it may take some time to get all the processors redirected to work on a particular task, you may also lose some time because 
 *  they don't all finish at the same time. Some processors end up waiting for others to finish before the vImage call can return. Here one expects this 
 *  time lost to be a tiny fraction of the overall time for large images, but for medium sized ones it may weigh against overall performance. (Smaller images
 *  may not even bother to multithread in such cases.) When you advance to the next back-to-back vImage call, some of the cores might have gone to sleep or 
 *  moved on to unrelated work waiting for other cores to finish, and now you have to wait for them to get back on task again. You could reduce overall latency
 *  if you could somehow convince the next filter to start on regions that are done without having to wait for all of the regions of the image to be done, 
 *  so that the cores stay busy and don't get distracted. 
 *
 *      Fourth, doing back-to-back-to-back vImage calls probably means having a bunch of intermediate vImage_Buffers hanging around that take up memory.
 *  In cases where the intermediate computation has to be done in some higher precision, like floating-point, some of these can be quite big. It would be
 *  very helpful to somehow make those go away, or at least go on a diet. 
 *
 *  So, how is this collection of problems fixed? Well, first of all, you don't /have/ to fix anything. Even with all of that, it should still work pretty
 *  well. If pretty well is not good enough, then the solution is to manage the threading yourself. Lets say you want to apply 4 vImage filters (A, B, C and 
 *  D) to an image in a back-to-back fashion. First you break up the result image into a bunch of smaller chunks, called tiles. These should be small enough 
 *  to fit conformably in the cache but not so small that we devote too much time doing setup tasks like parameter checking or initializing variables repeatedly. 
 *  (You can figure out the right size later when it all works. Guess for now.) Starting from the result tiles, work backward. For each tile in the output of D, 
 *  figure out which pixels from C are needed as input. This defines the set of tiles produced by C. In cases where the function needs to look at nearby pixels 
 *  to calculate a result pixel (e.g. Convolution or various Morphology filters) then it is possible that the C-produced tiles may overlap a bit. The process is 
 *  then repeated moving backward through B and A until we arrive at the starting image. We can now trace each result tile through a bunch of discrete image 
 *  fragments back up to a region in the original image. Since we know that we have all the input pixels we need to calculate a result tile at each stage, we 
 *  can apply filters A,B,C and D in series to a tile without needing to worry about what is happening in the other tiles. Thus, each tile can be operated on 
 *  by a different thread, and multithreading becomes trivial.
 *
 *  Consider the implications. Since each tile of data is operated on by a single thread and threads usually do not gratuitously hop around from core to core 
 *  (very much) the result from filter A on that tile should usually be in the right L1 or L2 cache when we call filter B to consume the result from A for that region,
 *  provided that we call filter B on that tile from that thread right away and don't run off and do other things. The same goes for filters C and D. So, you 
 *  are now probably getting better-than-good-enough temporal cache locality.  Observe also that it is generally not required that the intermediate (A,B or 
 *  C product) tiles be stored in memory that is contiguous with other tiles from the same intermediate image. They can be their own little chunks of memory 
 *  stored somewhere else. Maybe you even put them on the stack -- which probably will avoid most zero fill faults and is quick to allocate. In fact, if the 
 *  output tiles are of the same size, then as the thread finishes one tile, you can just reuse those small intermediate buffers that hold the intermediate 
 *  tiles for the next tile. The intermediate image then never exists as a whole at any given time and so you never have to allocate storage for most of it.  
 *  This gives you better-than-good-enough memory usage. Floating-point is starting to look a lot better! Next, because each tile is not waiting on its fellows, 
 *  you can begin working on filter B as soon as the thread is done with filter A. There is no more waiting for filter A to be done on the entire image before 
 *  B can be started. Threads go idle less. There is probably still bit of time lost to waiting for cores to spin up and some for the last thread to finish on 
 *  exit, but it is amortized over four filters instead of each filter. 
 *
 *  Recall that in standard opertaion, vImage will still be trying to multithread behind your back for all these little tiles. This will cause the threads to 
 *  oversubscribe the number of cores. Work that was supposed to be done by one thread is now split up to many. Threads may hop around from core to core much 
 *  more looking for a place to run, defeating cache locality. You may spend a lot of time waiting for cores to redirect to the next job with lots of little 
 *  jobs. The Instruments system trace looks like a tangled knot of threads playing musical chairs for a limited number of cores. To stop this, pass the 
 *  kvImageDoNotTile flag to make sure vImage is running only on the thread you assign to it.
 */

    
#ifdef __cplusplus
    }
#endif

#endif  /* vImage_Utilities_h */

