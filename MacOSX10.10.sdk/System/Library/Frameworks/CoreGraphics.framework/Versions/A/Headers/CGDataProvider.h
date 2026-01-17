/* CoreGraphics - CGDataProvider.h
   Copyright (c) 1999-2011 Apple Inc.
   All rights reserved. */

#ifndef CGDATAPROVIDER_H_
#define CGDATAPROVIDER_H_

typedef struct CGDataProvider *CGDataProviderRef;

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFURL.h>
#include <sys/types.h>

CF_IMPLICIT_BRIDGING_ENABLED

/* This callback is called to copy `count' bytes from the sequential data
   stream to `buffer'. */

typedef size_t (*CGDataProviderGetBytesCallback)(void *info, void *buffer,
  size_t count);

/* This callback is called to skip `count' bytes forward in the sequential
   data stream. It should return the number of bytes that were actually
   skipped. */

typedef off_t (*CGDataProviderSkipForwardCallback)(void *info, off_t count);

/* This callback is called to rewind to the beginning of sequential data
   stream. */

typedef void (*CGDataProviderRewindCallback)(void *info);

/* This callback is called to release the `info' pointer when the data
   provider is freed. */

typedef void (*CGDataProviderReleaseInfoCallback)(void *info);

/* Callbacks for sequentially accessing data.
   `version' is the version of this structure. It should be set to 0.
   `getBytes' is called to copy `count' bytes from the sequential data
     stream to `buffer'. It should return the number of bytes copied, or 0
     if there's no more data.
   `skipForward' is called to skip ahead in the sequential data stream by
     `count' bytes.
   `rewind' is called to rewind the sequential data stream to the beginning
     of the data.
   `releaseInfo', if non-NULL, is called to release the `info' pointer when
     the provider is freed. */

struct CGDataProviderSequentialCallbacks {
  unsigned int version;
  CGDataProviderGetBytesCallback getBytes;
  CGDataProviderSkipForwardCallback skipForward;
  CGDataProviderRewindCallback rewind;
  CGDataProviderReleaseInfoCallback releaseInfo;
};
typedef struct CGDataProviderSequentialCallbacks
  CGDataProviderSequentialCallbacks;

/* This callback is called to get a pointer to the entire block of data. */

typedef const void *(*CGDataProviderGetBytePointerCallback)(void *info);

/* This callback is called to release the pointer to entire block of
   data. */

typedef void (*CGDataProviderReleaseBytePointerCallback)(void *info,
  const void *pointer);

/* This callback is called to copy `count' bytes at byte offset `position'
   into `buffer'. */

typedef size_t (*CGDataProviderGetBytesAtPositionCallback)(void *info,
  void *buffer, off_t position, size_t count);

/* Callbacks for directly accessing data.
   `version' is the version of this structure. It should be set to 0.
   `getBytePointer', if non-NULL, is called to return a pointer to the
     provider's entire block of data.
   `releaseBytePointer', if non-NULL, is called to release a pointer to the
     provider's entire block of data.
   `getBytesAtPosition', if non-NULL, is called to copy `count' bytes at
     offset `position' from the provider's data to `buffer'. It should
     return the number of bytes copied, or 0 if there's no more data.
   `releaseInfo', if non-NULL, is called to release the `info' pointer when
     the provider is freed.

   At least one of `getBytePointer' or `getBytesAtPosition' must be
   non-NULL. */

struct CGDataProviderDirectCallbacks {
  unsigned int version;
  CGDataProviderGetBytePointerCallback getBytePointer;
  CGDataProviderReleaseBytePointerCallback releaseBytePointer;
  CGDataProviderGetBytesAtPositionCallback getBytesAtPosition;
  CGDataProviderReleaseInfoCallback releaseInfo;
};
typedef struct CGDataProviderDirectCallbacks CGDataProviderDirectCallbacks;

/* Return the CFTypeID for CGDataProviderRefs. */

CG_EXTERN CFTypeID CGDataProviderGetTypeID(void)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Create a sequential-access data provider using `callbacks' to provide the
   data. `info' is passed to each of the callback functions. */

CG_EXTERN CGDataProviderRef CGDataProviderCreateSequential(void *info,
  const CGDataProviderSequentialCallbacks *callbacks)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Create a direct-access data provider using `callbacks' to supply `size'
   bytes of data. `info' is passed to each of the callback functions.
   The underlying data must not change for the life of the data provider. */

CG_EXTERN CGDataProviderRef CGDataProviderCreateDirect(void *info, off_t size,
  const CGDataProviderDirectCallbacks *callbacks)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* The callback used by `CGDataProviderCreateWithData'. */

typedef void (*CGDataProviderReleaseDataCallback)(void *info, const void *data,
  size_t size);

/* Create a direct-access data provider using `data', an array of `size'
   bytes. `releaseData' is called when the data provider is freed, and is
   passed `info' as its first argument. */

CG_EXTERN CGDataProviderRef CGDataProviderCreateWithData(void *info,
  const void *data, size_t size, CGDataProviderReleaseDataCallback releaseData)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a direct-access data provider which reads from `data'. */

CG_EXTERN CGDataProviderRef CGDataProviderCreateWithCFData(CFDataRef data)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Create a data provider reading from `url'. */

CG_EXTERN CGDataProviderRef CGDataProviderCreateWithURL(CFURLRef url)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Create a data provider reading from `filename'. */

CG_EXTERN CGDataProviderRef
  CGDataProviderCreateWithFilename(const char *filename)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Equivalent to `CFRetain(provider)', but doesn't crash (as CFRetain does)
   if `provider' is NULL. */

CG_EXTERN CGDataProviderRef CGDataProviderRetain(CGDataProviderRef provider)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Equivalent to `CFRelease(provider)', but doesn't crash (as CFRelease
   does) if `provider' is NULL. */

CG_EXTERN void CGDataProviderRelease(CGDataProviderRef provider)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return a copy of the data specified by provider. Returns NULL if a
   complete copy of the data can't be obtained (for example, if the
   underlying data is too large to fit in memory). */

CG_EXTERN CFDataRef CGDataProviderCopyData(CGDataProviderRef provider)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGDATAPROVIDER_H_ */
