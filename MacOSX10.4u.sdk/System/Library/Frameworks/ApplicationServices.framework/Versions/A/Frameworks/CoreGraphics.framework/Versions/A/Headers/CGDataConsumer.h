/* CoreGraphics - CGDataConsumer.h
 * Copyright (c) 1999-2004 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGDATACONSUMER_H_
#define CGDATACONSUMER_H_

typedef struct CGDataConsumer *CGDataConsumerRef;

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFURL.h>
#include <stddef.h>

CG_EXTERN_C_BEGIN

/* This callback is called to copy `count' bytes from `buffer' to the
 * data consumer. */

typedef size_t (*CGDataConsumerPutBytesCallback)(void *info, const void *buffer, size_t count);

/* This callback is called to release the `info' pointer when the data
 * provider is freed. */

typedef void (*CGDataConsumerReleaseInfoCallback)(void *info);

/* Callbacks for accessing data.
 * `putBytes' copies `count' bytes from `buffer' to the consumer, and
 * returns the number of bytes copied.  It should return 0 if no more data
 * can be written to the consumer.
 * `releaseConsumer', if non-NULL, is called when the consumer is freed. */

struct CGDataConsumerCallbacks {
    CGDataConsumerPutBytesCallback putBytes;
    CGDataConsumerReleaseInfoCallback releaseConsumer;
};
typedef struct CGDataConsumerCallbacks CGDataConsumerCallbacks;

/* Return the CFTypeID for CGDataConsumerRefs. */

CG_EXTERN CFTypeID CGDataConsumerGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Create a data consumer using `callbacks' to handle the data.  `info' is
 * passed to each of the callback functions. */

CG_EXTERN CGDataConsumerRef CGDataConsumerCreate(void *info, const CGDataConsumerCallbacks *callbacks);

/* Create a data consumer which writes data to `url'. */

CG_EXTERN CGDataConsumerRef CGDataConsumerCreateWithURL(CFURLRef url);

/* Create a data consumer which writes to `data'. */

CG_EXTERN CGDataConsumerRef CGDataConsumerCreateWithCFData(CFMutableDataRef data) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Equivalent to `CFRetain(consumer)'. */

CG_EXTERN CGDataConsumerRef CGDataConsumerRetain(CGDataConsumerRef consumer);

/* Equivalent to `CFRelease(consumer)'. */

CG_EXTERN void CGDataConsumerRelease(CGDataConsumerRef consumer);

CG_EXTERN_C_END

#endif	/* CGDATACONSUMER_H_ */
