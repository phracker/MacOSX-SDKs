/*
 *  vImage.h
 *
 *  Copyright (c) 2002 Apple Computer. All rights reserved.
 *
 */

#ifndef VIMAGE_H
#define VIMAGE_H

/*!
 *  @charset utf-8
 */


/*  Data Formats
    ------------
    Most functions are available in four flavors, one for each of the four standard data formats supported 
    by vImage. These are:
    
    8 bit planar integer data  -- "Planar8":
        The buffer contains a single color channel (e.g. red) as an array of packed unsigned chars. 

    32 bit planar floating point data -- "PlanarF":
        The buffer contains a single color channel (e.g. red) as an array of packed floats. 

    8 bit ARGB interleaved integer data -- "ARGB8888":
        The buffer contains four interleaved color channels in the order alpha, red, green, blue, in a 
        packed array of unsigned chars. (This is a standard 32 bit ARGB color pixel, with 8 bits per channel).

    32 bit ARGB interleaved floating point data -- "ARGBFFFF":
        The buffer contains four interleaved color channels in the order alpha, red, green, blue, in a 
        packed array of floats. 
        
    PERFORMANCE ADVISORY: Performance of the planar versions of these functions will in some cases 
    be *MUCH* better than their interleaved counterparts. Most operations are done in register with planar 
    data, even if the starting data format was an interleaved format. By using planar data formats,
    you avoid the de-interleave, re-interleave cost in each function call. In addition, where calculation
    on the alpha channel is not desired, the computational cost and cache usage for planar formats is 
    in principle 3/4 the cost of interleaved formats for four channel data. Finally planar data is a natural
    form of tiling that works well when used with multiple serial filters. When applying multiple filters to
    a image, apply them all to one channel, then repeat the sequence for the next channel and so forth until
    all the color channels are calculated. This will help keep key data in the caches and in some cases may
    produce profound performance improvements. 
    
    The presumed value range for 8 bit color channels is 0 to 255, with 0 being black and 255 being full intensity color. 
    For floating point data, 0.0f is black and 1.0f is full intensity color. Values outside this range are allowed for 
    floating point data. Except where noted, FP calculations do not clip values outside the range 0.0f ... 1.0f. In certain
    cases (most notably geometry operations that involve resampling and colvolutions), it is possible that input data
    that is entirely withing the range 0.0f ... 1.0f will produce results that are slightly outside that range. A separate
    floating point clipping function is provided if clipping is required. 
    
    Other floating point ranges (e.g. 0.0f ... 255.0f) are likely to also work since most functions in vImage are linear. 
    However, they are not extensively tested. 

    vImage_Buffers 
    --------------
    Most vImage functions attempt to fill a destination buffer with pixels drawn from an input buffer using some 
    transformation. In some cases, the operation would require that pixels outside the area covered by the input
    buffer be used to fill the output buffer. The input vImage_Buffer defines the absolute limit of the area of 
    data that may be read by the function. The function will not stray outside of this area in its attempt to 
    fill the destination with pixels. How a function copes with edge cases when data is unavailable is dependent 
    on the function.
    
        typedef struct vImage_Buffer
        {
            void                *data;		// Pointer to the top left pixel of the buffer.	
            vImagePixelCount	height;		// The height (in pixels) of the buffer		
            vImagePixelCount	width;		// The width (in pixels) of the buffer 		
            size_t              rowBytes;	// The number of bytes in a pixel row		
        }vImage_Buffer;
            
    Some functions may operate only on a rectangular subset of pixels in the input buffer. This is useful for tiling
    or for when image operations are only desired to be applied to part of an image. The top left corner of the subset
    is provided by a X and Y offset into the vImage_Buffer passed as the input buffer. The height and width of the input
    region of interest is in many cases given by the height and width of the destination buffer. The geometry operators
    use non-rectangular input regions of interest making it difficult to predict which pixels will be used. In this case,
    the offsets (if any) are the offsets into the input region of interest for the case where the scale factor is 1.0 and
    shear and translate are 0.0f.   
    
    Please be aware that many functions, especially those that require kernels or which do resampling, will read 
    outside the input region of interest. Some extra care with multithreaded code may be required in those cases to make 
    sure nobody is changing data outside the region of interest that is read by the function while the function is operating. 
    At no time will a function read outside the vImage_Buffer within which the region of interest resides.
    
    So as to make multithreaded tiled (stripmined) algorithms easy to write, vImage makes two guarantees: 
    
        (1) vImage will never write data outside of the destination vImage_Buffer. vImage will not try to cheat this 
            guarantee by reading data outside the destination buffer and writing it back unmodified. 
            
        (2) vImage will never read data outside of the area passed to it as the input vImage_Buffer.  
            
    The state of the output vImage_Buffer while a vImage function is working on it is undefined. There may be times when
    a pixel in the ROI is neither the starting data or the finished result, but instead the result of some 
    intermediate calculation. The calculation is complete when the function returns. 
    
    Note that although a vImage_Buffer struct may be marked const, this does not mean that the pixel data that 
    it points to is also const. It is merely an indication that it is safe to reuse the struct between function 
    calls. Except where noted, the pixel data in the input buffers will not be changed by the function. vImage 
    does not go to extreme lengths to guarantee this however, so for example you may pass the same buffer as input 
    and output to a function, in which case the input buffer will be changed. 
    Caution: except where otherwise documented, most vImage functions do not work correctly in place. 
    
    Performance advisory: If the rowBytes of a vImage_Buffer is a integer power of 2, performance may be adversely 
    affected on some functions. (This is a side effect of how some PowerPC machines handle address arithmetic 
    internally. It is not something we can solve in software. ) In some cases, it may also be advantageous to pad 
    rowbytes out to 16 bytes. Here is some sample code for creating a vImage_Buffer for maximum performance:
    
        #include <stdlib.h>
        
        void MyInitBuffer( vImage_Buffer *result, int height, int width, size_t bytesPerPixel )
        {
            size_t rowBytes = width * bytesPerPixel;
        
            //Widen rowBytes out to a integer multiple of 16 bytes
            rowBytes = (rowBytes + 15) & ~15;
        
            //Make sure we are not an even power of 2 wide. 
            //Will loop a few times for rowBytes <= 16.
            while( 0 == (rowBytes & (rowBytes - 1) ) )
                rowBytes += 16;	//grow rowBytes
            
            //Set up the buffer
            result->height = height;
            result->width = width;
            result->rowBytes = rowBytes;
            result->data = malloc( rowBytes * height ); 
        }
        
        void MyFreeBuffer( vImage_Buffer *buffer )
        {
            if( buffer && buffer->data )
                free( buffer->data );
        }
    
    It is not required that you do set up your buffers exactly this way, however. To protect your investment in 
    preexisting data structures, vImage is designed to work with any (natural) data alignment and any rowBytes. 
    Floats must be 4 byte aligned. RowBytes must of course be greater than or equal to width * bytesPerPixel. 
    BytesPerPixel values are as follows:
    
        Buffer Data Format	Size
        ------------------	----
        planar uint8		sizeof( Pixel_8)		// 1 byte
        planar float		sizeof( Pixel_F )		// 4 bytes
        ARGB uint8			sizeof( Pixel_8888)		// 4 bytes
        ARGB float			sizeof( Pixel_FFFF )	// 16 bytes
			
    

    Tiling / Strip Mining and Multithreading
    ----------------------------------------
    In general, the size of the data segment that you operate on is critical to the performance of vImage. In
    many cases, the number of pixels that may be processed per second can be up to an order of magnitude lower
    for large buffers than for small ones.  A common method to fix this is to operate on small chunks of the image 
    at a time. Typically, you would apply all the filters one after another to one chunk, before going on to the next 
    chunk. In this way, the data is much more likely to be in the caches when you need it. This motif is easily 
    multithreaded in principle, since different processors can work on different chunks concurrently in many
    cases.  
        
    All vImage functions are thread safe and may be called reentrantly. 
    
    A quick test to do to see if tiling is good for you is to measure the number of pixels that you can process
    per second for very large (>4 MB uncompressed) and reasonably small (< 256 kB uncompressed) images. If the 
    number of pixels you can process per unit time is much improved for smaller images over large ones then tiling
    is likely to be helpful. 
    
    It is important to whenever possible make sure the tile fits in the caches. In general, the data processed in 
    a single tile (including input and output buffers) should be less than 256 kB, though in some cases there may 
    be a performance advantage to even smaller buffers. We have found that for many, 16-32 kB is a better number. 
    In many cases, you will only see performance improvement if the tile is significantly wider than it is tall, 
    for example 16 rows tall and 1024 horizontal bytes of pixels wide has been observed to be twice as fast as 
    64x128. Clearly having a tile wider than the image isn't very helpful. 
    
    Real Time Applications
    ----------------------
    vImage attempts to avoid doing things that will damage its suitability for use in real time applications. 
    vImage will in general never take a lock, or do things that might involve taking a lock, such as allocating
    memory. Functions that may take a lock will be documented as such.  Some functions take temporary buffers 
    as arguments. If you do not provide a temporary buffer, they may call malloc.
    
    Unused Flag Bits
    ----------------
    Many of the bits in the vImage_Flags datatype are currently unused. Apple reserves all bits in the flags field 
    for their exclusive use. You must set all unused bits to 0 in the flags field. If you do not do this, in the
    future some of these bits may become active and your application may start doing unexpected things when image 
    processing.
    
*/


#include <vImage/vImage_Types.h>
#include <vImage/Alpha.h>
#include <vImage/Convolution.h>
#include <vImage/Conversion.h>
#include <vImage/Geometry.h>
#include <vImage/Histogram.h>
#include <vImage/Morphology.h>
#include <vImage/BasicImageTypes.h>         /* New for MacOS X.4 and later */
#include <vImage/Transform.h>               /* New for MacOS X.4 and later */
#include <vImage/vImage_Utilities.h>
#include <vImage/vImage_CVUtilities.h>

#endif /* VIMAGE_H */
