/* CoreGraphics - CGDataProvider.h
 * Copyright (c) 1999-2000 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGDATAPROVIDER_H_
#define CGDATAPROVIDER_H_

typedef struct CGDataProvider *CGDataProviderRef;

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFURL.h>
#include <stddef.h>

CG_EXTERN_C_BEGIN

/* Callbacks for sequentially accessing data.
 * `getBytes' is called to copy `count' bytes from the provider's data to
 * `buffer'.  It should return the number of bytes copied, or 0 if there's
 * no more data.
 * `skipBytes' is called to skip ahead in the provider's data by `count' bytes.
 * `rewind' is called to rewind the provider to the beginning of the data.
 * `releaseProvider', if non-NULL, is called when the provider is freed. */

struct CGDataProviderCallbacks {
    size_t (*getBytes)(void *info, void *buffer, size_t count);
    void (*skipBytes)(void *info, size_t count);
    void (*rewind)(void *info);
    void (*releaseProvider)(void *info);
};
typedef struct CGDataProviderCallbacks CGDataProviderCallbacks;

/* Callbacks for directly accessing data.
 * `getBytePointer', if non-NULL, is called to return a pointer to the
 * provider's entire block of data.
 * `releaseBytePointer', if non-NULL, is called to release a pointer to
 * the provider's entire block of data.
 * `getBytes', if non-NULL, is called to copy `count' bytes at offset
 * `offset' from the provider's data to `buffer'.  It should return the
 * number of bytes copied, or 0 if there's no more data.
 * `releaseProvider', if non-NULL, is called when the provider is freed.
 * At least one of `getBytePointer' or `getBytes' must be non-NULL.  */

struct CGDataProviderDirectAccessCallbacks {
    const void *(*getBytePointer)(void *info);
    void (*releaseBytePointer)(void *info, const void *pointer);
    size_t (*getBytes)(void *info, void *buffer, size_t offset, size_t count);
    void (*releaseProvider)(void *info);
};
typedef struct CGDataProviderDirectAccessCallbacks CGDataProviderDirectAccessCallbacks;

/* Return the CFTypeID for CGDataProviderRefs. */

CG_EXTERN CFTypeID CGDataProviderGetTypeID(void);

/* Create a sequential-access data provider using `callbacks' to provide
 * the data.  `info' is passed to each of the callback functions. */

CG_EXTERN CGDataProviderRef CGDataProviderCreate(void *info, const CGDataProviderCallbacks *callbacks);

/* Create a direct-access data provider using `callbacks' to supply `size'
 * bytes of data. `info' is passed to each of the callback functions. */

CG_EXTERN CGDataProviderRef CGDataProviderCreateDirectAccess(void *info, size_t size, const CGDataProviderDirectAccessCallbacks *callbacks);

/* Create a direct-access data provider using `data', an array of `size'
 * bytes.  `releaseData' is called when the data provider is freed, and is
 * passed `info' as its first argument. */

CG_EXTERN CGDataProviderRef CGDataProviderCreateWithData(void *info, const void *data, size_t size, void (*releaseData)(void *info, const void *data, size_t size));

/* Create a data provider using `url'. */

CG_EXTERN CGDataProviderRef CGDataProviderCreateWithURL(CFURLRef url);

/* Equivalent to `CFRetain(provider)'. */

CG_EXTERN CGDataProviderRef CGDataProviderRetain(CGDataProviderRef provider);

/* Equivalent to `CFRelease(provider)'. */

CG_EXTERN void CGDataProviderRelease(CGDataProviderRef provider);

/** DEPRECATED FUNCTIONS **/

/* Don't use this function; use CFDataProviderCreateWithURL instead. */

CG_EXTERN CGDataProviderRef CGDataProviderCreateWithFilename(const char *filename);

CG_EXTERN_C_END

#endif	/* CGDATAPROVIDER_H_ */
