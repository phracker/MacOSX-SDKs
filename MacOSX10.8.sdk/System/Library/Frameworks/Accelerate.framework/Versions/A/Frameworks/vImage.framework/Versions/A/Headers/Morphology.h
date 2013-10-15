/*
 *  Morphology.h
 *  vImage_Framework
 *
 *  Copyright (c) 2002 Apple Computer. All rights reserved.
 *
 */

#ifndef VIMAGE_MORPHOLOGY_H
#define VIMAGE_MORPHOLOGY_H

#include <vImage/vImage_Types.h>


#ifdef __cplusplus
extern "C" {
#endif

/*  Morphology functions 
    -------------------- 
    Min is a special case for an Erode function with a kernel that contains all the same value. 
    Max is a special case for a Dilate function with a kernel that contains all the same value.
    
    The Erode and Dilate functions do saturated clipping to prevent overflow for UInt8 and ARGB_8888 types.
        No clipping is performed for floating point types. 
    Erode and Dilate handle the edges (areas where the kernel extends beyond the edges of the input buffer)
        by testing only those parts of the kernel that do overlay the input buffer. 
        
    An Open filter may be created by doing an Erode followed by a Dilate.
    A Close filter may be created by doing a Dilate followed by an Erode.
    
    A kernel populated with only one value lets us make some significant algorithmic optimizations. The 
    calculation time for the Dilate and Erode functions are proportional to M*N for a square kernel of 
    dimensions M x N.  The calculation time for the Min and Max functions is roughly proportional to 
    Log2(N) + Log2(M). The speed difference can be orders of magnitude for large kernels. We suggest 
    you use Min/Max instead of Dilate/Erode when possible. 
        
    The temp buffers should be the size returned by vImageGetMinimumTempBufferSizeForMinMax() or larger.
    
    The source and destination buffers must not overlap. Exception: They may overlap if you pass in a temporary buffer
    to Min or Max and you also pass the kvImageDoNotTile flag.
    
    In MacOS X.3, Panther, Min and Max do not respond to kvImageLeaveAlphaUnchanged for interleaved data formats. 
    Due to the large difference in speed between Min/Max and Dilate/Erode for large kernels, developers who wish 
    to do Min/Max with kvImageLeaveAlphaUnchanged should convert the data format to planar, then call Min/Max on the
    appropriate color channels and then convert back to the desired interleaved format. 
    
    Developers should be aware that it is incorrect to call any Morphology function on image data that is 
    premultiplied by the alpha channel. Doing so may result in images containing color channel data that 
    is larger than the alpha channel for some pixels. 
 
    The ARGB8888 and ARGBFFFF forms of these functions work equally well for other channel orders such as 
    RGBA8888 and BGRAFFFF.
*/
vImage_Error vImageDilate_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const unsigned char *kernel, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error vImageDilate_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const float *kernel, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error vImageDilate_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const unsigned char *kernel, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error vImageDilate_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const float *kernel, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

vImage_Error vImageErode_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const unsigned char *kernel, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error vImageErode_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const float *kernel, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error vImageErode_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const unsigned char *kernel, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error vImageErode_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const float *kernel, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

vImage_Error vImageMax_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error vImageMax_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error vImageMax_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error vImageMax_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

vImage_Error vImageMin_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error vImageMin_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error vImageMin_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
vImage_Error vImageMin_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags )    __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*
 * It is recommended that you use the kvImageGetTempBufferSize flag with the appropriate function, instead of using this API 
 * Simply pass the kvImageGetTempBufferSize flag in addition to all the regular parameters. The size will be returned in the  
 * vImage_Error result.  kvImageGetTempBufferSize is for MacOS X.4 and later. 
 */
size_t	vImageGetMinimumTempBufferSizeForMinMax( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags, size_t bytesPerPixel )    __OSX_AVAILABLE_BUT_DEPRECATED( __MAC_10_3, __MAC_10_4, __IPHONE_NA, __IPHONE_NA );

#ifdef __cplusplus
}
#endif

#endif /* MORPHOLOGY_H */
