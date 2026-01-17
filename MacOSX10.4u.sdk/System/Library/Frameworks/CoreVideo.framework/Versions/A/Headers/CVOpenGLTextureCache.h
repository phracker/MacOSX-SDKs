/*
 *  CVOpenGLTextureCache.h
 *  CoreVideo
 *
 *  Copyright 2004 Apple Computer, Inc. All rights reserved.
 *
 */

#if !defined(__COREVIDEO__CVOPENGLTEXTURECACHE_H__)
#define __COREVIDEO__CVOPENGLTEXTURECACHE_H__ 1

#include <CoreVideo/CVBase.h>
#include <CoreVideo/CVReturn.h>
#include <CoreVideo/CVBuffer.h>
#include <CoreVideo/CVOpenGLTexture.h>
#include <OpenGL/OpenGL.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
    @typedef	CVOpenGLTextureCacheRef
    @abstract   CoreVideo OpenGL Texture Cache

*/
typedef struct __CVOpenGLTextureCache *CVOpenGLTextureCacheRef;

CV_EXPORT CFTypeID CVOpenGLTextureCacheGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVOpenGLTextureCacheRetain
    @abstract   Retains a CVOpenGLTextureCache object
    @discussion Equivalent to CFRetain, but NULL safe
    @param      buffer A CVOpenGLTextureCache object that you want to retain.
    @result     A CVOpenGLTextureCache object that is the same as the passed in buffer.
*/
CV_EXPORT CVOpenGLTextureCacheRef CVOpenGLTextureCacheRetain( CVOpenGLTextureCacheRef textureCache ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // NULL-safe

/*!
    @function   CVOpenGLTextureCacheRelease
    @abstract   Releases a CVOpenGLTextureCache object
    @discussion Equivalent to CFRelease, but NULL safe
    @param      buffer A CVOpenGLTextureCache object that you want to release.
*/
CV_EXPORT void CVOpenGLTextureCacheRelease( CVOpenGLTextureCacheRef textureCache ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // NULL-safe

/*!
    @function   CVOpenGLTextureCacheCreate
    @abstract   Creates a new Texture Cache.
    @param      allocator The CFAllocatorRef to use for allocating the cache.  May be NULL.
    @param      cacheAttributes A CFDictionaryRef containing the attributes of the cache itself.   May be NULL.
    @param      cglContext The OpenGL context into which the texture objects will be created
    @param      cglPixelFormat The OpenGL pixel format object used to create the passed in OpenGL context
    @param      textureAttributes A CFDictionaryRef containing the attributes to be used for creating the CVOpenGLTexture objects.  May be NULL.
    @param      cacheOut   The newly created texture cache will be placed here
    @result     Returns kCVReturnSuccess on success
*/
CV_EXPORT CVReturn CVOpenGLTextureCacheCreate(
					CFAllocatorRef allocator,
					CFDictionaryRef cacheAttributes,
					CGLContextObj cglContext,
					CGLPixelFormatObj cglPixelFormat,
					CFDictionaryRef textureAttributes,
					CVOpenGLTextureCacheRef *cacheOut) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVOpenGLTextureCacheCreateTextureFromImage
    @abstract   Creates a CVOpenGLTexture object from an existing CVImageBuffer
    @param      allocator The CFAllocatorRef to use for allocating the CVOpenGLTexture object.  May be NULL.
    @param      textureCache The texture cache object that will manage the texture
    @param      sourceImage The CVImageBuffer that you want to create a CVOpenGLTexture from.
    @param      attributes For Future use only! - The desired buffer attributes for the CVOpenGLTexture.
    @param      textureOut The newly created texture object will be placed here.
    @result     Returns kCVReturnSuccess on success
*/
CV_EXPORT CVReturn CVOpenGLTextureCacheCreateTextureFromImage(CFAllocatorRef allocator,
								       CVOpenGLTextureCacheRef textureCache,
								       CVImageBufferRef sourceImage,
								       CFDictionaryRef attributes,
								       CVOpenGLTextureRef *textureOut) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVOpenGLTextureCacheFlush
    @abstract   Performs internal housekeeping/recycling operations
    @discussion This call must be made periodically to give the texture cache a chance to make OpenGL calls
                on the OpenGL context used to create it in order to do housekeeping operations.
    @param      textureCache The texture cache object to flush
    @param      options Currently unused, set to 0.
    @result     Returns kCVReturnSuccess on success
*/
CV_EXPORT void CVOpenGLTextureCacheFlush(CVOpenGLTextureCacheRef textureCache, CVOptionFlags options) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#if defined(__cplusplus)
}
#endif

#endif
