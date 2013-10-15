/*
 *  CVOpenGLBufferPool.h
 *  CoreVideo
 *
 *  Copyright 2004 Apple Computer, Inc. All rights reserved.
 *
 */

 /*! @header CVOpenGLBufferPool.h
	@copyright 2004 Apple Computer, Inc. All rights reserved.
	@availability Mac OS X 10.4 or later
    @discussion CVOpenGLBufferPool is a utility object for managing a set of CVOpenGLBuffer objects that are going to be recycled.
		   
*/

#if !defined(__COREVIDEO__CVOPENGLBUFFERPOOL_H__)
#define __COREVIDEO__CVOPENGLBUFFERPOOL_H__ 1

#include <CoreVideo/CVBase.h>
#include <CoreVideo/CVReturn.h>
#include <CoreVideo/CVOpenGLBuffer.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct __CVOpenGLBufferPool *CVOpenGLBufferPoolRef;

CV_EXPORT const CFStringRef kCVOpenGLBufferPoolMinimumBufferCountKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

// By default, buffers will age out after one second.   If required, setting an age of zero will disable
// the age-out mechanism completely.
CV_EXPORT const CFStringRef kCVOpenGLBufferPoolMaximumBufferAgeKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CV_EXPORT CFTypeID CVOpenGLBufferPoolGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVOpenGLBufferPoolRetain
    @abstract   Retains a CVOpenGLBufferPoolRef object
    @discussion Equivalent to CFRetain, but NULL safe
    @param      buffer A CVOpenGLBufferPoolRef object that you want to retain.
    @result     A CVOpenGLBufferPoolRef object that is the same as the passed in buffer.
*/
CV_EXPORT CVOpenGLBufferPoolRef CVOpenGLBufferPoolRetain( CVOpenGLBufferPoolRef openGLBufferPool ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // NULL-safe

/*!
    @function   CVOpenGLBufferPoolRelease
    @abstract   Releases a CVOpenGLBufferPoolRef object
    @discussion Equivalent to CFRelease, but NULL safe
    @param      buffer A CVOpenGLBufferPoolRef object that you want to release.
*/
CV_EXPORT void CVOpenGLBufferPoolRelease( CVOpenGLBufferPoolRef openGLBufferPool ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // NULL-safe

/*!
    @function   CVOpenGLBufferPoolCreate
    @abstract   Creates a new OpenGL Buffer pool.
    @discussion Equivalent to CFRelease, but NULL safe
    @param      allocator The CFAllocatorRef to use for allocating this buffer pool.  May be NULL.
    @param      poolAttributes   A CFDictionaryRef containing the attributes to be used for the pool itself.
    @param      openGLBufferAttributes   A CFDictionaryRef containing the attributes to be used for creating new OpenGLBuffers within the pool.
    @param      poolOut   The newly created pool will be placed here
    @result     Returns kCVReturnSuccess on success
*/
CV_EXPORT CVReturn CVOpenGLBufferPoolCreate(CFAllocatorRef allocator,
					   CFDictionaryRef poolAttributes,
					   CFDictionaryRef openGLBufferAttributes,
					   CVOpenGLBufferPoolRef *poolOut) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVOpenGLBufferPoolGetOpenGLBufferAttributes
    @abstract   Returns the pool attributes dictionary for a CVOpenGLBufferPool
    @param      pool  The CVOpenGLBufferPoolRef to retrieve the attributes from
    @result     Returns the pool attributes dictionary, or NULL on failure.
*/
CV_EXPORT CFDictionaryRef CVOpenGLBufferPoolGetAttributes(CVOpenGLBufferPoolRef pool) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVOpenGLBufferPoolGetOpenGLBufferAttributes
    @abstract   Returns the attributes of OpenGL buffers that will be created from this pool.
    @discussion This function is provided for those cases where you may need to know some information about the buffers that
                will be created up front.
    @param      pool  The CVOpenGLBufferPoolRef to retrieve the attributes from
    @result     Returns the OpenGL buffer attributes dictionary, or NULL on failure.
*/
CV_EXPORT CFDictionaryRef CVOpenGLBufferPoolGetOpenGLBufferAttributes(CVOpenGLBufferPoolRef pool) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVOpenGLBufferPoolCreateOpenGLBuffer
    @abstract   Creates a new OpenGLBuffer object from the pool.
    @discussion The function creates a new CVOpenGLBuffer with the default attachments using the OpenGL buffer attributes specifed during pool creation.
    @param      allocator The CFAllocatorRef to use for creating the OpenGL buffer.  May be NULL.
    @param      openGLBufferPool      The CVOpenGLBufferPool that should create the new CVOpenGLBuffer.
    @param      openGLBufferOut   The newly created OpenGL buffer will be placed here
    @result     Returns kCVReturnSuccess on success
*/
CV_EXPORT CVReturn CVOpenGLBufferPoolCreateOpenGLBuffer(CFAllocatorRef allocator, 
						         CVOpenGLBufferPoolRef openGLBufferPool,
							 CVOpenGLBufferRef *openGLBufferOut) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#if defined(__cplusplus)
}
#endif

#endif
