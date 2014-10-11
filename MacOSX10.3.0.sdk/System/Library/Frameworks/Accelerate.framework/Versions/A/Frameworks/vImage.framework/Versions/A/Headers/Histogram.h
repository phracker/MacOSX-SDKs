/*
 *  Histogram.h
 *  vImage_Framework
 *
 *  Copyright (c) 2003 Apple Computer. All rights reserved.
 *
 */

#ifndef VIMAGE_HISTOGRAM_H
#define VIMAGE_HISTOGRAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <vImage/vImage_Types.h>

vImage_Error vImageHistogramCalculation_Planar8( const vImage_Buffer *src, 
		unsigned int *histogram, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageHistogramCalculation_PlanarF( const vImage_Buffer *src, 
		unsigned int *histogram, unsigned int histogram_entries, Pixel_F minVal, Pixel_F maxVal, 
		vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageHistogramCalculation_ARGB8888( const vImage_Buffer *src, 
		unsigned int *histogram[4], vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageHistogramCalculation_ARGBFFFF( const vImage_Buffer *src, 
		unsigned int *histogram[4], unsigned int histogram_entries, Pixel_F minVal, Pixel_F maxVal, 
		vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageEqualization_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageEqualization_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, 
		unsigned int histogram_entries, Pixel_F minVal, Pixel_F maxVal, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageEqualization_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageEqualization_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, 
		unsigned int histogram_entries,  Pixel_F minVal, Pixel_F maxVal, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageHistogramSpecification_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, 
		const unsigned int *desired_histogram, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageHistogramSpecification_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, 
		const unsigned int *desired_histogram, unsigned int histogram_entries, Pixel_F minVal, Pixel_F maxVal, 
		vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageHistogramSpecification_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, 
		const unsigned int *desired_histogram[4], vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageHistogramSpecification_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, 
		const unsigned int *desired_histogram[4], unsigned int histogram_entries, Pixel_F minVal, Pixel_F maxVal, 
		vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageContrastStretch_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageContrastStretch_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, 
		unsigned int histogram_entries, Pixel_F minVal, Pixel_F maxVal, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageContrastStretch_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageContrastStretch_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, 
		unsigned int histogram_entries, Pixel_F minVal, Pixel_F maxVal, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageEndsInContrastStretch_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, 
		unsigned int percent_low, unsigned int percent_high, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageEndsInContrastStretch_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, 
		unsigned int percent_low, unsigned int percent_high, 
		unsigned int histogram_entries, Pixel_F minVal, Pixel_F maxVal, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageEndsInContrastStretch_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, 
		const unsigned int percent_low[4], const unsigned int percent_high[4], vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

vImage_Error vImageEndsInContrastStretch_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, 
		const unsigned int percent_low[4], const unsigned int percent_high[4], 
		unsigned int histogram_entries, Pixel_F minVal, Pixel_F maxVal, vImage_Flags flags )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

size_t vImageGetMinimumTempBufferSizeForHistogram( const vImage_Buffer *src, const vImage_Buffer *dest, 
		unsigned int histogram_entries, vImage_Flags flags, size_t bytesPerPixel )    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

#ifdef __cplusplus
}
#endif

#endif
