/*
	File:  VTPixelRotationProperties.h
	
	Framework:  VideoToolbox
	
	Copyright 2021 Apple Inc. All rights reserved.
	
	Standard properties for VTPixelRotationSession.
*/

#ifndef VTPIXELROTATIONPROPERTIES_H
#define VTPIXELROTATIONPROPERTIES_H

#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>

#include <CoreFoundation/CoreFoundation.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

CM_ASSUME_NONNULL_BEGIN

/*! 
	@constant	kVTPixelRotationPropertyKey_Rotation
	@abstract
		Specifies the amount of rotation in degrees.
	@discussion
		Specifies the amount of rotation to apply when copying source to destination.
		Valid values: kVTRotation_0, kVTRotation_CW90, kVTRotation_180, and kVTRotation_CCW90
		default is kVTRotation_0.
*/

VT_EXPORT const CFStringRef kVTPixelRotationPropertyKey_Rotation API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

VT_EXPORT const CFStringRef kVTRotation_0 		API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTRotation_CW90	API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTRotation_180		API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);
VT_EXPORT const CFStringRef kVTRotation_CCW90	API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@constant	kVTPixelRotationPropertyKey_FlipHorizontalOrientation
	@abstract
		Specifies the horizontal flip.
	@discussion
		kVTPixelRotationPropertyKey_FlipHorizontalOrientation must pass a CFBoolean as value. true will apply a horizontal flip after the rotation.
		default is false;
*/

VT_EXPORT const CFStringRef kVTPixelRotationPropertyKey_FlipHorizontalOrientation API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@constant	kVTPixelRotationPropertyKey_FlipVerticalOrientation
	@abstract
		Specifies the vertical flip.
	@discussion
		kVTPixelRotationPropertyKey_FlipVerticalOrientation must pass a CFBoolean as value. true will apply a vertical flip after the rotation.
		default is false;
*/

VT_EXPORT const CFStringRef kVTPixelRotationPropertyKey_FlipVerticalOrientation API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

CM_ASSUME_NONNULL_END

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif // VTPIXELROTATIONPROPERTIES_H
