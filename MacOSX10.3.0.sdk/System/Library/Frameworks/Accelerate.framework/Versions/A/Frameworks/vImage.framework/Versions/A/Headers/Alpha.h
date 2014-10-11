/*
 *  vImageAlpha.h
 *  vImage Framework
 *
 *  Copyright (c) 2003 Apple Computer. All rights reserved.
 *
 */

#ifndef VIMAGE_ALPHA_H
#define VIMAGE_ALPHA_H	

#include <vImage/vImage_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *
 *	These alpha compositing functions assume that the floating point range is 0.0 (black) to 1.0 (full intensity color).
 *	While values outside these ranges do function correctly (you can have 110% intensity color or -50% color, for example), 
 *	the calculation is done assuming 1.0 represents full intensity color, and 0.0 represents the absence of color. If these 
 *	assumptions are not correct, then the calculation will produce incorrect results. Apple does not currently provide 
 *	alpha compositing functions that work with any floating point range in vImage.  
 *
 *	8 bit functionality assumes that 0 is no color, and 255 is full color. 8 bit functions do saturated clipping before
 *	converting from internal precision back to 8 bits. The internal calculation is done with higher precision.
 *
 */


vImage_Error	vImageAlphaBlend_Planar8( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *srcBottomAlpha, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImageAlphaBlend_PlanarF( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *srcBottomAlpha, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImageAlphaBlend_ARGB8888( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImageAlphaBlend_ARGBFFFF( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error	vImagePremultipliedAlphaBlend_Planar8( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImagePremultipliedAlphaBlend_PlanarF( const vImage_Buffer *srcTop, const vImage_Buffer *srcTopAlpha, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImagePremultipliedAlphaBlend_ARGB8888( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImagePremultipliedAlphaBlend_ARGBFFFF( const vImage_Buffer *srcTop, const vImage_Buffer *srcBottom, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error	vImagePremultiplyData_Planar8( const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImagePremultiplyData_PlanarF( const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImagePremultiplyData_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImagePremultiplyData_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error	vImageUnpremultiplyData_Planar8( const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImageUnpremultiplyData_PlanarF( const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImageUnpremultiplyData_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
vImage_Error	vImageUnpremultiplyData_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

#ifdef __cplusplus
}
#endif

#endif /* vImage_ALPHA_H */


