/*
 *  CVPixelBufferIOSurface.h
 *  CoreVideo
 *
 *  Copyright (c) 2010 Apple Computer, Inc. All rights reserved.
 *
 */
 
  /*! @header CVPixelBufferIOSurface.h
	@copyright 2010 Apple Computer, Inc. All rights reserved.
	@availability Mac OS X 10.4 or later
    @discussion routines for accessing and manipulating IOSurface backings for CVPixelBuffers
		   
*/

#if !defined(__COREVIDEO_CVPIXELBUFFERIOSURFACE_H__)
#define __COREVIDEO_CVPIXELBUFFERIOSURFACE_H__ 1

#include <TargetConditionals.h>

#if COREVIDEO_SUPPORTS_IOSURFACE
#include <IOSurface/IOSurface.h>
#endif // COREVIDEO_SUPPORTS_IOSURFACE

#if defined(__cplusplus)
extern "C" {
#endif

// Ensures that CGLTexImageIOSurface2D() will succeed in creating a valid texture object from the CVPixelBuffer's IOSurface.
CV_EXPORT const CFStringRef kCVPixelBufferIOSurfaceOpenGLTextureCompatibilityKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;	// CFBoolean
// Ensures that CGLTexImageIOSurface2D() will succeed in creating a valid texture object from the CVPixelBuffer's IOSurface AND that the resulting texture may be used as a color buffer attachment to a OpenGL frame buffer object.
CV_EXPORT const CFStringRef kCVPixelBufferIOSurfaceOpenGLFBOCompatibilityKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;	// CFBoolean
// Ensures that the CVPixelBuffer's IOSurfaceRef can be displayed in an CoreAnimation CALayer.
CV_EXPORT const CFStringRef kCVPixelBufferIOSurfaceCoreAnimationCompatibilityKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;	// CFBoolean


#if COREVIDEO_SUPPORTS_IOSURFACE

/*!
	@function   CVPixelBufferGetIOSurface
	@abstract   Returns the IOSurface backing the pixel buffer, or NULL if it is not backed by an IOSurface.
	@param      pixelBuffer Target PixelBuffer.
*/
CV_EXPORT IOSurfaceRef CVPixelBufferGetIOSurface(CVPixelBufferRef pixelBuffer) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!
    @function   CVPixelBufferCreateWithIOSurface
    @abstract   Call to create a single CVPixelBuffer for a passed-in IOSurface.
    @discussion The CVPixelBuffer will retain the IOSurface.
    	IMPORTANT NOTE: If you are using IOSurface to share CVPixelBuffers between processes
    	and those CVPixelBuffers are allocated via a CVPixelBufferPool, it is important
    	that the CVPixelBufferPool does not reuse CVPixelBuffers whose IOSurfaces are still
    	in use in other processes.  
    	CoreVideo and IOSurface will take care of this for if you use IOSurfaceCreateMachPort 
    	and IOSurfaceLookupFromMachPort, but NOT if you pass IOSurfaceIDs.
    @param      surface		            The IOSurface to wrap.
    @param      pixelBufferAttributes   A dictionary with additional attributes for a a pixel buffer. This parameter is optional. See PixelBufferAttributes for more details.
    @param      pixelBufferOut          The new pixel buffer will be returned here
    @result     returns kCVReturnSuccess on success.
*/
CV_EXPORT CVReturn CVPixelBufferCreateWithIOSurface(
		CFAllocatorRef allocator,
		IOSurfaceRef surface,
		CFDictionaryRef pixelBufferAttributes,
		CVPixelBufferRef *pixelBufferOut) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

#endif // COREVIDEO_SUPPORTS_IOSURFACE


#if defined(__cplusplus)
}
#endif

#endif
