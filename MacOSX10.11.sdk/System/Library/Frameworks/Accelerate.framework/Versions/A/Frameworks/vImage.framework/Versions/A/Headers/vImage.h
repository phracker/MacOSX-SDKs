
/****************************************************************************************************************************************************************
 *                                                                                                                                                              *
 *  The main vImage documentation is available in the vImage Programming Guide:                                                                                 *
 *                                                                                                                                                              *
 *    OS X: https://developer.apple.com/library/mac/documentation/Performance/Conceptual/vImage/Introduction/Introduction.html                                  *
 *    iOS:  https://developer.apple.com/library/ios/documentation/Performance/Conceptual/vImage/Introduction/Introduction.html                                  *
 *                                                                                                                                                              *
 *  However, that resource, generously provided by ADC, is updated infrequently. In order to provide more timely documentation for newer vImage API, these      *
 *  headers contain additional headerdoc documentation in the comments.  The vImage headerdoc documentation can be viewed in lovely HTML as follows:            *
 *                                                                                                                                                              *
 *    /usr/bin/headerdoc2html -o ~/vImage_docs \                                                                                                                *
 *            `xcrun --sdk {iphoneos|macosx} --show-sdk-path`/System/Library/Frameworks/Accelerate.framework/Frameworks/vImage.framework/Headers                *
 *        # Select the single platform for the SDK you are working with. vImage APIs generally stay in sync between platforms.                                  *
 *        # (or using system headers from command line tools: /System/Library/Frameworks/Accelerate.framework/Frameworks/vImage.framework/Headers)              *
 *    /usr/bin/gatherheaderdoc ~/vImage_docs                                                                                                                    *
 *    open ~/vImage_docs/masterTOC.html                                                                                                                         *
 *                                                                                                                                                              *
 *  For more on using headerdoc:                                                                                                                                *
 *    https://developer.apple.com/library/mac/documentation/DeveloperTools/Conceptual/HeaderDoc/usage/usage.html#//apple_ref/doc/uid/TP40001215-CH337-CDEBBJJA  *
 *                                                                                                                                                              *
 *  vImage headerdoc documentation is a work in progress, and currently only covers recent additions. (Documenting old features already present in the vImage   *
 *  Programming Guide would compete for engineering time against vImage development itself.) Most functions not covered in headerdoc should be documented in    *
 *  the vImage Programming Guide. Please file a bug if you encounter a function documented in neither resource.    http://bugreporter.apple.com                 *
 *                                                                                                                                                              *
 *  Option clicking a vImage symbol in Xcode will often bring up online help with information assembled from both resources.                                    *
 *                                                                                                                                                              *
 ****************************************************************************************************************************************************************/

#ifndef VIMAGE_H
#define VIMAGE_H

/*!
 *  @header vImage.h
 *  @copyright Copyright (c) 2002-2015 by Apple Inc. All rights reserved.
 *  @compilerflag  -framework Accelerate
 *  @charset utf-8
 *
 *  @discussion
 *
 *  <pre> @textblock
 *    Data Formats
 *    ------------
 *    Most functions are available in four flavors, one for each of the four standard data formats supported
 *    by vImage. These are:
 *
 *    8 bit planar integer data  -- "Planar8":
 *        The buffer contains a single color channel (e.g. red) as an array of packed unsigned chars.
 *
 *    32 bit planar floating point data -- "PlanarF":
 *        The buffer contains a single color channel (e.g. red) as an array of packed floats.
 *
 *    8 bit ARGB interleaved integer data -- "ARGB8888":
 *        The buffer contains four interleaved color channels in the order alpha, red, green, blue, in a
 *        packed array of unsigned chars. (This is a standard 32 bit ARGB color pixel, with 8 bits per channel).
 *
 *    32 bit ARGB interleaved floating point data -- "ARGBFFFF":
 *        The buffer contains four interleaved color channels in the order alpha, red, green, blue, in a
 *        packed array of floats.
 *
 *    Many functions are also available in Planar and ARGB versions of unsigned and signed 16-bit integer, 16S and
 *    16U respectively.
 *
 *    PERFORMANCE ADVISORY: Performance of the planar versions of these functions will in some cases
 *    be *MUCH* better than their interleaved counterparts. Most operations are done in register with planar
 *    data, even if the starting data format was an interleaved format. By using planar data formats,
 *    you avoid the de-interleave, re-interleave cost in each function call. In addition, where calculation
 *    on the alpha channel is not desired, the computational cost and cache usage for planar formats is
 *    in principle 3/4 the cost of interleaved formats for four channel data. Finally planar data is a natural
 *    form of tiling that works well when used with multiple serial filters. When applying multiple filters to
 *    a image, apply them all to one channel, then repeat the sequence for the next channel and so forth until
 *    all the color channels are calculated. This will help keep key data in the caches and in some cases may
 *    produce profound performance improvements.
 *
 *    The presumed value range for 8 bit color channels is 0 to 255, with 0 being black and 255 being full intensity color.
 *    For floating point data, 0.0f is black and 1.0f is full intensity color. Values outside this range are allowed for
 *    floating point data. Except where noted, FP calculations do not clip values outside the range 0.0f ... 1.0f. In certain
 *    cases (most notably geometry operations that involve resampling and colvolutions), it is possible that input data
 *    that is entirely withing the range 0.0f ... 1.0f will produce results that are slightly outside that range. A separate
 *    floating point clipping function is provided if clipping is required.
 *
 *    Other floating point ranges (e.g. 0.0f ... 255.0f) are likely to also work since most functions in vImage are linear.
 *    However, they are not extensively tested.
 *
 *    vImage_Buffers
 *    --------------
 *    Most vImage functions attempt to fill a destination buffer with pixels drawn from an input buffer using some
 *    transformation. In some cases, the operation would require that pixels outside the area covered by the input
 *    buffer be used to fill the output buffer. The input vImage_Buffer defines the absolute limit of the area of
 *    data that may be read by the function. The function will not stray outside of this area in its attempt to
 *    fill the destination with pixels. How a function copes with edge cases when data is unavailable is dependent
 *    on the function.
 *
 *        typedef struct vImage_Buffer
 *        {
 *            void                *data;		// Pointer to the top left pixel of the buffer.
 *            vImagePixelCount	  height;		// The height (in pixels) of the buffer
 *            vImagePixelCount    width;		// The width (in pixels) of the buffer
 *            size_t              rowBytes;	    // The number of bytes in a pixel row
 *        }vImage_Buffer;
 *
 *    Some functions may operate only on a rectangular subset of pixels in the input buffer. This is useful for tiling
 *    or for when image operations are only desired to be applied to part of an image. The top left corner of the subset
 *    is provided by a X and Y offset into the vImage_Buffer passed as the input buffer. The height and width of the input
 *    region of interest is in many cases given by the height and width of the destination buffer. The geometry operators
 *    use non-rectangular input regions of interest making it difficult to predict which pixels will be used. In this case,
 *    the offsets (if any) are the offsets into the input region of interest for the case where the scale factor is 1.0 and
 *    shear and translate are 0.0f.
 *
 *    Please be aware that many functions, especially those that require kernels or which do resampling, will read
 *    outside the input region of interest. Some extra care with multithreaded code may be required in those cases to make
 *    sure nobody is changing data outside the region of interest that is read by the function while the function is operating.
 *    At no time will a function read outside the vImage_Buffer within which the region of interest resides.
 *
 *    So as to make multithreaded tiled (stripmined) algorithms easy to write, vImage makes two guarantees:
 *
 *        (1) vImage will never write data outside of the destination vImage_Buffer. vImage will not try to cheat this
 *            guarantee by reading data outside the destination buffer and writing it back unmodified.
 *
 *        (2) vImage will never read data outside of the area passed to it as the input vImage_Buffer.
 *
 *    The state of the output vImage_Buffer while a vImage function is working on it is undefined. There may be times when
 *    a pixel in the ROI is neither the starting data or the finished result, but instead the result of some
 *    intermediate calculation. The calculation is complete when the function returns.
 *
 *    Note that although a vImage_Buffer struct may be marked const, this does not mean that the pixel data that
 *    it points to is also const. It is merely an indication that it is safe to reuse the struct between function
 *    calls. Except where noted, the pixel data in the input buffers will not be changed by the function. vImage
 *    does not go to extreme lengths to guarantee this however, so for example you may pass the same buffer as input
 *    and output to a function, in which case the input buffer will be changed.
 *    Caution: except where otherwise documented, most vImage functions do not work correctly in place.
 *
 *    Performance advisory: If the rowBytes of a vImage_Buffer is a integer power of 2, performance may be adversely
 *    affected on some functions. (This is a side effect of how some machines handle address arithmetic
 *    internally. It is not something we can solve in software, except by setting rowBytes differently. ) 
 *    In some cases, it may also be advantageous to pad rowbytes out to 16 bytes. Using vImageBuffer_Init() 
 *    in vImage/vImage_Utilities.h will help sidestep this issue. It will attempt tune rowBytes to benefit the 
 *    current architecture.
 *
 *    It is not required that you do set up your buffers exactly this way, however. To protect your investment in
 *    preexisting data structures, vImage is designed to work with any (natural) data alignment and any rowBytes.
 *    Floats must be 4 byte aligned. RowBytes must of course be greater than or equal to width * bytesPerPixel.
 *    BytesPerPixel values are as follows:
 *
 *        Buffer Data Format	Size
 *        ------------------	----
 *        planar uint8		    sizeof( Pixel_8)		// 1 byte
 *        planar float		    sizeof( Pixel_F )		// 4 bytes
 *        ARGB uint8			sizeof( Pixel_8888)		// 4 bytes
 *        ARGB float			sizeof( Pixel_FFFF )	// 16 bytes
 *
 *
 *
 *    Tiling / Strip Mining and Multithreading
 *    ----------------------------------------
 *    In general, the size of the data segment that you operate on is critical to the performance of vImage. In
 *    many cases, the number of pixels that may be processed per second can be up to an order of magnitude lower
 *    for large buffers than for small ones.  A common method to fix this is to operate on small chunks of the image
 *    at a time. Typically, you would apply all the filters one after another to one chunk, before going on to the next
 *    chunk. In this way, the data is much more likely to be in the caches when you need it. This motif is easily
 *    multithreaded in principle, since different processors can work on different chunks concurrently in many
 *    cases.
 *
 *    All vImage functions are thread safe and may be called reentrantly.
 *
 *    A quick test to do to see if tiling is good for you is to measure the number of pixels that you can process
 *    per second for very large (>4 MB uncompressed) and reasonably small (< 256 kB uncompressed) images. If the
 *    number of pixels you can process per unit time is much improved for smaller images over large ones then tiling
 *    is likely to be helpful.
 *
 *    It is important to whenever possible make sure the tile fits in the caches. In general, the data processed in
 *    a single tile (including input and output buffers) should be less than 256 kB, though in some cases there may
 *    be a performance advantage to even smaller buffers. We have found that for many, 16-32 kB is a better number.
 *    In many cases, you will only see performance improvement if the tile is significantly wider than it is tall,
 *    for example 16 rows tall and 1024 horizontal bytes of pixels wide has been observed to be twice as fast as
 *    64x128. Clearly having a tile wider than the image isn't very helpful.
 *
 *    A convenience method for making a vImage_Buffer that refers to a rectangular sub-region of another vImage_Buffer:
 *
 *      // Calculate a vImage_Buffer descriptor for a sub-rectangle within an image
 *      // This function does not attempt to ensure that the tile fits in the image.
 *      vImage_Buffer   MyMakeTileFromImage( const vImage_Buffer *image,
 *                                           unsigned long startColumn, // x coordinate of top left corner of tile
 *                                           unsigned long startRow,    // y coordinate of top left corner of tile
 *                                           unsigned long tileHeight,  // number of rows in tile
 *                                           unsigned long tileWidth,   // number of columns in tile
 *                                           size_t pixelBytes ){       // number of bytes in pixel
 *          return (vImage_Buffer){
 *              .data = (void*) ((char*) image->data + startColumn * pixelBytes + startRow * image->rowBytes),
 *              .height = tileHeight,
 *              .width = tileWidth,
 *              .rowBytes = image->rowBytes
 *          };
 *      }
 *
 *    CAUTION:  This will cause vImage to believe the edges of the image are at the edges of the tile. Usually that 
 *              doesn't affect the result, but will for convolultions, morphology operations and geometry operations
 *              --  things that take a edge mode flag.  For such routines, the start of the tile is declared using
 *              a srcOffsetToROI_X/Y  and the size of the tile is inferred from the destination image size.
 *
 *    Sometimes you may want to flip an image vertically. In vImage, this can be done cheaply by adjusting the pointer
 *    to point to the last scanline of the image and setting rowBytes negative, for either the source or destination
 *    image:
 *
 *      static inline vImage_Buffer MyFlipVertical( const vImage_Buffer *b ) __attribute__ ((always_inline,nodebug));
 *      static inline vImage_Buffer MyFlipVertical( const vImage_Buffer *b ){
 *          return (vImage_Buffer){ .data = (void*) ( (char*)b->data + b->rowBytes * (b->height-1)),
 *                                  .height = b->height,
 *                                  .width = b->width,
 *                                  .rowBytes = -b->rowBytes };
 *      }
 *
 *    CAUTION:  While vImage will put up with this sort of abuse, other frameworks may not. Make sure the data is
 *              right side up before passing it to anyone else.
 *
 *    Real Time Applications
 *    ----------------------
 *    vImage attempts to avoid doing things that will damage its suitability for use in real time applications.
 *    vImage will in general never take a lock, or do things that might involve taking a lock, such as allocating
 *    memory. Functions that may take a lock will be documented as such.  Some functions take temporary buffers
 *    as arguments. If you do not provide a temporary buffer, they may call malloc.
 *
 *    Unused Flag Bits
 *    ----------------
 *    Many of the bits in the vImage_Flags datatype are currently unused. Apple reserves all bits in the flags field
 *    for their exclusive use. You must set all unused bits to 0 in the flags field. If you do not do this, in the
 *    future some of these bits may become active and your application may start doing unexpected things when image
 *    processing.
 *
 *    Getting Data in and out of vImage
 *    ---------------------------------
 *    Since vImage will simply use your data in place in your objects, interfacing with your existing image pipeline
 *    should be a simple matter of intializing the vImage_Buffer struct fields to correspond to the location and
 *    and shape of your data.  
 * 
 *    When the objects are not yours and are opaque, then getting data in and out of those objects can be a little
 *    more work.  Most image frameworks have a method to import and export raw data. These are often simple to use
 *    but the data is frequently not in the format you wanted. In such cases, please see vImage/vImage_Utilities.h for
 *    vImageConvert_AnyToAny() which can convert nearly any image format to nearly any other one with full colorspace
 *    conversion, if desired, even on iOS. This should help you convert the output of one imaging library into 
 *    something useful for another one.  (It is used by ImageIO.framework for example, to convert the many different 
 *    image buffer formats produced by PNG, JPEG, GIF, TIFF, etc. to formats more favored by CoreGraphics, CoreAnimation 
 *    and CoreImage, for example.)  The conversions are vectorized and multithreaded to minimize time and energy 
 *    consumption.
 *
 *    If the opaque image object comes from CoreGraphics (CGImageRef) or CoreVideo (CVPixelBufferRef), then high level
 *    convenience routines are provided to import and export data from those sources as vImage_Buffers. See
 *    vImage/vImage_Utilities.h and vImage/vImage_CVUtilities.h respectively for these.  Since the conversions go through
 *    the same vImageConvert_AnyToAny core, it is possible to convert all the way from a YUV 420 format out to CMYK for
 *    a printer in a single function call, or anywhere inbetween, if you want. A few formats like 565 and half float not 
 *    usually part of CG are supported as a bonus.
 *
 *   @/textblock </pre>
 */


// Types, defines, flags and error codes
#include <vImage/vImage_Types.h>

// Alpha compositing, premultiplication, unpremultiplication
#include <vImage/Alpha.h>

// Sharpen, blur, edge detection, deconvolution
#include <vImage/Convolution.h>

// Hundreds of functions to convert from one image format to another.
#include <vImage/Conversion.h>

// Change the shape of an image by resizing it, vertical/horizontal reflect, rotation, shearing and affine warp.
#include <vImage/Geometry.h>

// Get a histogram. Make an image conform to a histogram.
#include <vImage/Histogram.h>

// Reshape structure elements in an image. Enlarge dark or light features. Close holes. Erode thin structures.
#include <vImage/Morphology.h>

// some limited support for PNG encoding
#include <vImage/BasicImageTypes.h>

// Gamma, polynomials, rationals, matrix multiplication (for hue saturation and brightness)
#include <vImage/Transform.h>

// The utility headers providing CG and CV interoperability pull in higher-level system headers that assume
// objective-c support that is not availble unless you are using clang as your compiler.
#if defined __clang__
// Convert any image format to nearly any other one. Exchange data with CGImageRefs
#include <vImage/vImage_Utilities.h>

// Import and export video frames from CVPixelBufferRefs
#include <vImage/vImage_CVUtilities.h>
#endif


#endif /* VIMAGE_H */
