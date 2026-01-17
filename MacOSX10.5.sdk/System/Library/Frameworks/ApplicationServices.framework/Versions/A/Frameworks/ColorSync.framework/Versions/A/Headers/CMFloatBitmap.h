/*
     File:       ColorSync/CMFloatBitmap.h
 
     Contains:   ColorSync types and API for floating point operations
 
     Copyright:  2004-2005 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult http://developer.apple.com/bugreporter/
 
*/
#ifndef __CMFLOATBITMAP__
#define __CMFLOATBITMAP__

#ifndef __CMTYPES__
#include <ColorSync/CMTypes.h>
#endif

#include <ColorSync/CMBase.h>

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif


#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint on
#endif

enum CMFloatBitmapFlags {
  kCMFloatBitmapFlagsNone       = 0,
  kCMFloatBitmapFlagsAlpha      = 1,
  kCMFloatBitmapFlagsAlphaPremul = 2,
  kCMFloatBitmapFlagsRangeClipped = 4
};
typedef enum CMFloatBitmapFlags CMFloatBitmapFlags;

/*!
    @struct     CMFloatBitmap
    @abstract       A new struture that defines and arbritrary map of float color values.
    @discussion     The struture defines a pixel array of dimensions [height][width][chans] 
                    where 'chans' is the number of channels in the colorspace plus an optional one for alpha.
                    The actual memory pointed to by the structure can contain a variety of possible arrangements. 
                    The actual data values can be chuncky or planar. The channels can by in any order.
<PRE>

Examples:
a) float* p contains a 640w by 480h bitmap of chunky RGB data
    CMFloatBitmap map = { 0,         // version
                {p, p+1, p+2},       // base addrs of R,G,B
                480, 640,            // height, width
                640*3,               // rowStride
                3,                   // colStride
                cmRGBData,
                kCMFloatBitmapFlagsNone};
b) float* p contains a 640w by 480h bitmap of chunky BGRA data
    CMFloatBitmap map = { 0,         // version
                {p+2, p+1, p, p+3},  // base addrs of R,G,B,A
                480, 640,            // height, width
                640*4,               // rowStride
                3,                   // colStride
                cmRGBData,
                kCMFloatBitmapFlagsAlpha};
c) float* p contains a 640w by 480h bitmap of planar CMYK data
    CMFloatBitmap map = { 0,        // version
                {p, p+640*480 , p+2*640*480 , p+3*640*480},
                480, 640,           // height, width
                640,                // rowStride
                1,                  // colStride
                cmCMYKData,
                kCMFloatBitmapFlagsNone};
</PRE>
        
    @field      version     The version number of this structure to allow for future expansion.
                            Should contain 0 for now.
    
    @field      buffers     The base address for each channel in canonical order.
                            The canonical order for RGB is R,G,B. CMYK is C,M,Y,K etc.
                            A maximum of sixteen channels is supported.
                            Another way to think of this is 
                                buffers[c] = &(pixelArray[0][0][c])
                                
    @field      height      The height (in pixels) of the bitmap.

    @field      width       The width (in pixels) of the bitmap.

    @field      rowStride   The number of floats to skip to move from one row to the next.
                            This is typically (width*chans) for chunky pixel buffers or (width) for planar.
                            Can be negative if the image is vertically flipped.

    @field      colStride   The number of floats to skip to move from one column to the next.
                            This is typically (chans) for chunky pixel buffers or (1) for planar.
                            Can be negative if the image is horizontally flipped.

    @field      space       The colorspace of the data (e.g cmRGBdata cmCMYKData)

    @field      flags       Holds bits to specify the alpha type of the data.
                            The remaining bits are reserved for future use.

*/
typedef struct CMFloatBitmap {
  unsigned long       version;
  float *             buffers[16];
  size_t              height;
  size_t              width;
  ptrdiff_t           rowStride;
  ptrdiff_t           colStride;
  OSType              space;
  CMFloatBitmapFlags  flags;
} CMFloatBitmap;
 
 
 
/* D50 illuminant {0.9642, 1.0000, 0.8249} */
CSEXTERN const float kCMIlluminantD50[3]                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
 
 
/* D65 illuminant {0.9504, 1.0000, 1.0889}*/
CSEXTERN const float kCMIlluminantD65[3]                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
 
 

/*!
    @function   CMFloatBitmapMakeChunky
    @abstract   A handy funtion to fill in a CMFloatBitmap.
    @discussion Returns a filled in CMFloatBitmap structure given a single buffer of chunky data with no alpha.
    @param      buffer  (in) address of interleaved data
    @param      height  (in) height of bitmap in pixels
    @param      width   (in) width of bitmap in pixels
    @param      space   (in) colorsapce of the data
    @result     a filled in CMFloatBitmap
*/
CSEXTERN CMFloatBitmap 
CMFloatBitmapMakeChunky(
  float *  buffer,
  size_t   height,
  size_t   width,
  OSType   space)                                             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*!
    @function   CMConvertXYZFloatBitmap
    @abstract   Used to convert CMFloatBitmaps between the related colorspaces XYZ, Yxy, Lab, and Luv.
    @discussion The buffer data from the source CMFloatBitmap is converted into the buffer data
                specified the destination CMFloatBitmap.  Converion "in-place" is allowed.
    @param      src     (in) description of source data buffer to convert from
    @param      srcIlluminantXYZ    (in) required if src->space is XYZ or Yxy
    @param      dst     (in,out) description of destination data buffer to convert to
    @param      dstIlluminantXYZ    (in) required if dst->space is XYZ or Yxy
    @param      method  (in) the chromatic adaptation method to use
*/
CSEXTERN CMError 
CMConvertXYZFloatBitmap(
  const CMFloatBitmap *   src,
  const float             srcIlluminantXYZ[3],
  CMFloatBitmap *         dst,
  const float             dstIlluminantXYZ[3],
  CMChromaticAdaptation   method)                             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*!
    @function   CMConvertRGBFloatBitmap
    @abstract   Used to convert CMFloatBitmaps between the related colorspaces RGB, HSV, and HLS.
    @discussion The buffer data from the source CMFloatBitmap is converted into the buffer data
                specified the destination CMFloatBitmap.  Converion "in-place" is allowed.
    @param      src     (in) description of source data buffer to convert from
    @param      dst     (in,out) description of destination data buffer to convert to
*/
CSEXTERN CMError 
CMConvertRGBFloatBitmap(
  const CMFloatBitmap *  src,
  CMFloatBitmap *        dst)                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*!
    @function   CMMatchFloatBitmap
    @abstract   Used to convert CMFloatBitmaps using a CMWorldRef.
    @discussion The buffer data from the source CMFloatBitmap is converted into the buffer data
                specified the destination CMFloatBitmap.  Converion "in-place" is allowed.
    @param      cw      (in) the CMWorldRef to convert with
    @param      src     (in) description of source data buffer to convert from
    @param      dst     (in,out) description of destination data buffer to convert to
*/
CSEXTERN CMError 
CMMatchFloatBitmap(
  CMWorldRef             cw,
  const CMFloatBitmap *  src,
  CMFloatBitmap *        dst)                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;




#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint reset
#endif


#ifdef __cplusplus
}
#endif

#endif /* __CMFLOATBITMAP__ */

