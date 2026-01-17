/*
 *  CVMetalBufferCache.h
 *  CoreVideo
 *
 *  Copyright (c) 2023 Apple Inc. All rights reserved.
 */

/*! @header CVMetalBufferCache.h
   @copyright 2023 Apple Inc. All rights reserved.
   @availability iOS 18.0 or later. mac 15.0 or later.
   @discussion A CoreVideo Metal buffer derives from a buffer, and is used for supplying buffers to Metal.
*/

#if !defined(__COREVIDEO__CVMETALBUFFERCACHE_H__)
#define __COREVIDEO__CVMETALBUFFERCACHE_H__ 1

#include <CoreVideo/CVBase.h>
#include <CoreVideo/CVReturn.h>
#include <CoreVideo/CVImageBuffer.h>
#include <CoreVideo/CVMetalBuffer.h>

#if COREVIDEO_SUPPORTS_IOSURFACE && COREVIDEO_SUPPORTS_METAL

#if defined(__cplusplus)
extern "C" {
#endif

// By default, buffers will age out after one second.
// Setting a maximum buffer age of zero will disable the age-out mechanism completely.
// CVMetalBufferCacheFlush() can be used to force eviction in either case.
CV_EXPORT const CFStringRef CV_NONNULL kCVMetalBufferCacheMaximumBufferAgeKey API_AVAILABLE(macosx(15.0), ios(18.0), tvos(18.0)) API_UNAVAILABLE(watchos);

typedef struct CV_BRIDGED_TYPE(id) __CVMetalBufferCache *CVMetalBufferCacheRef CV_SWIFT_NONSENDABLE;

CV_EXPORT CFTypeID CVMetalBufferCacheGetTypeID(void) API_AVAILABLE(macosx(15.0), ios(18.0), tvos(18.0)) API_UNAVAILABLE(watchos);

#if defined(__OBJC__)

@protocol MTLDevice;
    
/*!
    @function   CVMetalBufferCacheCreate
    @abstract   Creates a new Buffer Cache.
    @param      allocator The CFAllocatorRef to use for allocating the cache.  May be NULL.
    @param      cacheAttributes A CFDictionaryRef containing the attributes of the cache itself. May be NULL.
    @param      metalDevice The Metal device for which the buffer objects will be created.
    @param      cacheOut   The newly created buffer cache will be placed here
    @result     Returns kCVReturnSuccess on success
*/
CV_EXPORT CVReturn CVMetalBufferCacheCreate(
    CFAllocatorRef CV_NULLABLE allocator,
    CFDictionaryRef CV_NULLABLE cacheAttributes,
    id<MTLDevice> CV_NONNULL metalDevice,
    CV_RETURNS_RETAINED_PARAMETER CVMetalBufferCacheRef CV_NULLABLE * CV_NONNULL cacheOut
) API_AVAILABLE(macosx(15.0), ios(18.0), tvos(18.0)) API_UNAVAILABLE(watchos);

#endif // __OBJC__

/*!
    @function   CVMetalBufferCacheCreateBuffer
    @abstract   Creates a CVMetalBuffer object from an existing CVImageBuffer
    @param      allocator The CFAllocatorRef to use for allocating the CVMetalBuffer object. May be NULL.
    @param      bufferCache The buffer cache object that will manage the buffer.
    @param      buffer The CVImageBuffer that you want to create a CVMetalBuffer from.
    @param      bufferOut The newly created buffer object will be placed here.
    @result     Returns kCVReturnSuccess on success
    @discussion Creates or returns a cached CVMetalBuffer object mapped to the CVImageBuffer.
                This creates a live binding between the CVImageBuffer and underlying CVMetalBuffer buffer object.
 
                IMPORTANT NOTE: Clients should retain CVMetalBuffer objects until they are done using the images in them.
                Retaining a CVMetalBuffer is your way to indicate that you're still using the image in the buffer, and that it should not be recycled yet.
*/
CV_EXPORT CVReturn CVMetalBufferCacheCreateBufferFromImage(
    CFAllocatorRef CV_NULLABLE allocator,
    CVMetalBufferCacheRef CV_NONNULL bufferCache,
    CVImageBufferRef CV_NONNULL imageBuffer,
    CV_RETURNS_RETAINED_PARAMETER CVMetalBufferRef CV_NULLABLE * CV_NONNULL bufferOut
) API_AVAILABLE(macosx(15.0), ios(18.0), tvos(18.0)) API_UNAVAILABLE(watchos);

/*!
    @function   CVMetalBufferCacheFlush
    @abstract   Performs internal housekeeping/recycling operations
    @discussion This call must be made periodically to give the buffer cache a chance to do internal housekeeping operations.
    @param      bufferCache The buffer cache object to flush
    @param      options Currently unused, set to 0.
*/
CV_EXPORT void CVMetalBufferCacheFlush(
    CVMetalBufferCacheRef CV_NONNULL bufferCache,
    CVOptionFlags options
) API_AVAILABLE(macosx(15.0), ios(18.0), tvos(18.0)) API_UNAVAILABLE(watchos);

#if defined(__cplusplus)
}
#endif

#endif // COREVIDEO_SUPPORTS_IOSURFACE && COREVIDEO_SUPPORTS_METAL

#endif // __COREVIDEO__CVMETALBUFFERCACHE_H__
