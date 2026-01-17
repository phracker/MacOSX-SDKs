/* CoreGraphics - CGDataProvider.h
 * Copyright (c) 1999-2004 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGDATAPROVIDER_H_
#define CGDATAPROVIDER_H_

typedef struct CGDataProvider *CGDataProviderRef;

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFURL.h>
#include <stddef.h>

CG_EXTERN_C_BEGIN

/* This callback is called to copy `count' bytes from the sequential data
 * stream to `buffer'. */

typedef size_t (*CGDataProviderGetBytesCallback)(void *info, void *buffer, size_t count);

/* This callback is called to skip `count' bytes forward in the sequential
 * data stream. */

typedef void (*CGDataProviderSkipBytesCallback)(void *info, size_t count);

/* This callback is called to rewind to the beginning of sequential data
 * stream. */

typedef void (*CGDataProviderRewindCallback)(void *info);

/* This callback is called to release the `info' pointer when the data
 * provider is freed. */

typedef void (*CGDataProviderReleaseInfoCallback)(void *info);

/* Callbacks for sequentially accessing data.
 * `getBytes' is called to copy `count' bytes from the sequential data
 *   stream to `buffer'.  It should return the number of bytes copied, or 0
 *   if there's no more data.
 * `skipBytes' is called to skip ahead in the sequential data stream by
 *   `count' bytes.
 * `rewind' is called to rewind the sequential data stream to the beginning
 *   of the data.
 * `releaseProvider', if non-NULL, is called to release the `info' pointer
 *   when the provider is freed. */

struct CGDataProviderCallbacks {
    CGDataProviderGetBytesCallback getBytes;
    CGDataProviderSkipBytesCallback skipBytes;
    CGDataProviderRewindCallback rewind;
    CGDataProviderReleaseInfoCallback releaseProvider;
};
typedef struct CGDataProviderCallbacks CGDataProviderCallbacks;

/* This callback is called to get a pointer to the entire block of data. */

typedef const void *(*CGDataProviderGetBytePointerCallback)(void *info);

/* This callback is called to release the pointer to entire block of
 * data. */

typedef void (*CGDataProviderReleaseBytePointerCallback)(void *info, const void *pointer);

/* This callback is called to copy `count' bytes at byte offset `offset'
 * into `buffer'. */

typedef size_t (*CGDataProviderGetBytesAtOffsetCallback)(void *info, void *buffer, size_t offset, size_t count);

/* Callbacks for directly accessing data.
 * `getBytePointer', if non-NULL, is called to return a pointer to the
 *   provider's entire block of data.
 * `releaseBytePointer', if non-NULL, is called to release a pointer to
 *   the provider's entire block of data.
 * `getBytes', if non-NULL, is called to copy `count' bytes at offset
 * `offset' from the provider's data to `buffer'.  It should return the
 *   number of bytes copied, or 0 if there's no more data.
 * `releaseProvider', if non-NULL, is called when the provider is freed.
 *
 * At least one of `getBytePointer' or `getBytes' must be non-NULL.  */

struct CGDataProviderDirectAccessCallbacks {
    CGDataProviderGetBytePointerCallback getBytePointer;
    CGDataProviderReleaseBytePointerCallback releaseBytePointer;
    CGDataProviderGetBytesAtOffsetCallback getBytes;
    CGDataProviderReleaseInfoCallback releaseProvider;
};
typedef struct CGDataProviderDirectAccessCallbacks CGDataProviderDirectAccessCallbacks;

/* Return the CFTypeID for CGDataProviderRefs. */

CG_EXTERN CFTypeID CGDataProviderGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Create a sequential-access data provider using `callbacks' to provide
 * the data.  `info' is passed to each of the callback functions. */

CG_EXTERN CGDataProviderRef CGDataProviderCreate(void *info, const CGDataProviderCallbacks *callbacks);

/* Create a direct-access data provider using `callbacks' to supply `size'
 * bytes of data. `info' is passed to each of the callback functions. */

CG_EXTERN CGDataProviderRef CGDataProviderCreateDirectAccess(void *info, size_t size, const CGDataProviderDirectAccessCallbacks *callbacks);

/* The callback used by `CGDataProviderCreateWithData'. */

typedef void (*CGDataProviderReleaseDataCallback)(void *info, const void *data, size_t size);

/* Create a direct-access data provider using `data', an array of `size'
 * bytes.  `releaseData' is called when the data provider is freed, and is
 * passed `info' as its first argument. */

CG_EXTERN CGDataProviderRef CGDataProviderCreateWithData(void *info, const void *data, size_t size, CGDataProviderReleaseDataCallback releaseData);

/* Create a direct-access data provider which reads from `data'. */

CG_EXTERN CGDataProviderRef CGDataProviderCreateWithCFData(CFDataRef data) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Create a data provider using `url'. */

CG_EXTERN CGDataProviderRef CGDataProviderCreateWithURL(CFURLRef url);

/* Equivalent to `CFRetain(provider)'. */

CG_EXTERN CGDataProviderRef CGDataProviderRetain(CGDataProviderRef provider);

/* Equivalent to `CFRelease(provider)'. */

CG_EXTERN void CGDataProviderRelease(CGDataProviderRef provider);

/** DEPRECATED FUNCTIONS **/

/* Don't use this function; use CGDataProviderCreateWithURL instead. */

CG_EXTERN CGDataProviderRef CGDataProviderCreateWithFilename(const char *filename);

CG_EXTERN_C_END

#endif	/* CGDATAPROVIDER_H_ */
