/*
 *  Conversion.h
 *  vImage_Framework
 *
 *  Copyright (c) 2003 Apple Computer. All rights reserved.
 *
 */

#ifndef VIMAGE_CONVERSION_H
#define VIMAGE_CONVERSION_H

#include <vImage/vImage_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

vImage_Error vImageClip_PlanarF(const vImage_Buffer* src, const vImage_Buffer* dest, Pixel_F maxFloat, Pixel_F minFloat, vImage_Flags flags)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageConvert_Planar8toPlanarF(const vImage_Buffer *src, const vImage_Buffer *dest, Pixel_F maxFloat, Pixel_F minFloat, vImage_Flags flags)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageConvert_PlanarFtoPlanar8(const vImage_Buffer *src, const vImage_Buffer *dest, Pixel_F maxFloat, Pixel_F minFloat, vImage_Flags flags)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageConvert_Planar8toARGB8888(const vImage_Buffer *srcA, const vImage_Buffer *srcR, const vImage_Buffer *srcG, const vImage_Buffer *srcB, const vImage_Buffer *dest, vImage_Flags flags)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageConvert_ARGB8888toPlanar8(const vImage_Buffer *srcARGB, const vImage_Buffer *destA, const vImage_Buffer *destR, const vImage_Buffer *destG, const vImage_Buffer *destB, vImage_Flags flags)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageConvert_ChunkyToPlanar8( const void *srcChannels[], const vImage_Buffer *destPlanarBuffers[], unsigned int channelCount, size_t srcStrideBytes, unsigned int srcWidth, unsigned int srcHeight, unsigned int srcRowBytes, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageConvert_PlanarToChunky8( const vImage_Buffer *srcPlanarBuffers[], void *destChannels[], unsigned int channelCount, size_t destStrideBytes, unsigned int destWidth, unsigned int destHeight, unsigned int destRowBytes, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageConvert_ChunkyToPlanarF( const void *srcChannels[], const vImage_Buffer *destPlanarBuffers[], unsigned int channelCount, size_t srcStrideBytes, unsigned int srcWidth, unsigned int srcHeight, unsigned int srcRowBytes, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageConvert_PlanarToChunkyF( const vImage_Buffer *srcPlanarBuffers[], void *destChannels[], unsigned int channelCount, size_t destStrideBytes, unsigned int destWidth, unsigned int destHeight, unsigned int destRowBytes, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageConvert_16SToF( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageConvert_16UToF( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageConvert_FTo16S( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageConvert_FTo16U( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageConvert_PlanarFtoARGBFFFF(const vImage_Buffer *srcA, const vImage_Buffer *srcR, const vImage_Buffer *srcG, const vImage_Buffer *srcB, const vImage_Buffer *dest, vImage_Flags flags)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageConvert_ARGBFFFFtoPlanarF(const vImage_Buffer *srcARGB, const vImage_Buffer *destA, const vImage_Buffer *destR, const vImage_Buffer *destG, const vImage_Buffer *destB, vImage_Flags flags)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageTableLookUp_ARGB8888(const vImage_Buffer *src, const vImage_Buffer *dest, const Pixel_8 alphaTable[256], const Pixel_8 redTable[256], const  Pixel_8 greenTable[256], const  Pixel_8 blueTable[256], vImage_Flags flags)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageTableLookUp_Planar8(const vImage_Buffer *src, const vImage_Buffer *dest, const Pixel_8 table[256], vImage_Flags flags)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

#ifdef __cplusplus
}
#endif

#endif