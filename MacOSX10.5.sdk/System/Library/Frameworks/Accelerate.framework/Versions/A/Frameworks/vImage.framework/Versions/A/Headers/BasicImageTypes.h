/*
 *  BasicImageTypes.h
 *  vImage Framework
 *
 *  Copyright (c) 2004 Apple Computer. All rights reserved.
 *
 */

#ifndef VIMAGE_BASIC_IMAGE_TYPES_H
#define VIMAGE_BASIC_IMAGE_TYPES_H	

#include <vImage/vImage_Types.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 *  PNG + Tiff filter
 *
 *  difference Style described in PNG filter definition: http://www.w3.org/TR/PNG-Filters.html
 *  Implements PNG decompression filtering for filter method 0 of the PNG standard, section 9.2
 *
 *  Per PNG specifications, pixels that are outside of the src buffer are presumed to have value 
 *  0, for filter types that specify that pixels other than the immediate source pixel be considered.
 *
 *  Due to the way some of the filter modes operate, this filter is always applied in place. 
 */
 
enum
{

    kvImage_PNG_FILTER_VALUE_NONE  = 0,
    kvImage_PNG_FILTER_VALUE_SUB   = 1,
    kvImage_PNG_FILTER_VALUE_UP    = 2,
    kvImage_PNG_FILTER_VALUE_AVG   = 3,
    kvImage_PNG_FILTER_VALUE_PAETH = 4
};
 
vImage_Error  vImagePNGDecompressionFilter( const vImage_Buffer *buffer, 
                                            vImagePixelCount    startScanline,
                                            vImagePixelCount    scanlineCount,
                                            uint32_t            bitsPerPixel,          
                                            uint32_t            filterMethodNumber, /* must be 0 */
                                            uint32_t            filterType,         /* For filter method 0, value 0-4 inclusive */
                                            vImage_Flags        flags)  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
 

#ifdef __cplusplus
}
#endif

#endif

