/*
 *  CVMetalBuffer.h
 *  CoreVideo
 *
 *  Copyright (c) 2023 Apple Inc. All rights reserved.
 */
 
 /*! @header CVMetalBuffer.h
	@copyright 2023 Apple Inc. All rights reserved.
	@availability iOS 18.0 or later. mac 15.0 or later.
    @discussion A CoreVideo Metal buffer derives from a buffer, and is used for supplying buffers to Metal.
*/

#if !defined(__COREVIDEO_CVMETALBUFFER_H__)
#define __COREVIDEO_CVMETALBUFFER_H__ 1

#include <CoreVideo/CVBase.h>
#include <CoreVideo/CVReturn.h>
#include <CoreVideo/CVImageBuffer.h>
#include <CoreFoundation/CoreFoundation.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

#if COREVIDEO_SUPPORTS_IOSURFACE && COREVIDEO_SUPPORTS_METAL

/*!
    @typedef    CVMetalBufferRef
    @abstract   Metal buffer based CVPixelBuffer wrapped buffer
    @discussion IMPORTANT NOTE: Clients should retain CVMetalBuffer objects until they are done using the contents in them.
                Retaining a CVMetalBuffer is your way to indicate that you're still using the image in the buffer, and that it should not be recycled yet.
*/
typedef CVBufferRef CVMetalBufferRef CV_SWIFT_NONSENDABLE;
    
CV_EXPORT CFTypeID CVMetalBufferGetTypeID(void) API_AVAILABLE(macosx(15.0), ios(18.0), tvos(18.0)) API_UNAVAILABLE(watchos);

    
#if defined(__OBJC__)
@protocol MTLBuffer;
/*!
    @function   CVMetalBufferGetBuffer
    @abstract   Returns the Metal MTLBuffer object of the CVMetalBufferRef
    @param      buffer Target CVMetalBuffer
    @result     Metal buffer
*/
CV_EXPORT id<MTLBuffer> CV_NULLABLE CVMetalBufferGetBuffer(CVMetalBufferRef CV_NONNULL buffer) API_AVAILABLE(macosx(15.0), ios(18.0), tvos(18.0)) API_UNAVAILABLE(watchos);

#endif // defined(__OBJC__)

#endif // COREVIDEO_SUPPORTS_IOSURFACE && COREVIDEO_SUPPORTS_METAL
	
#if defined(__cplusplus)
}
#endif

#endif
