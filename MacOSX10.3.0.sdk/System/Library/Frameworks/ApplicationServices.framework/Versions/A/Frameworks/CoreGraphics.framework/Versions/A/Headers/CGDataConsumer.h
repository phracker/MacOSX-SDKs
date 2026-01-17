/* CoreGraphics - CGDataConsumer.h
 * Copyright (c) 1999-2000 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGDATACONSUMER_H_
#define CGDATACONSUMER_H_

typedef struct CGDataConsumer *CGDataConsumerRef;

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFURL.h>
#include <stddef.h>

CG_EXTERN_C_BEGIN

/* Callbacks for accessing data.
 * `putBytes' copies `count' bytes from `buffer' to the consumer, and
 * returns the number of bytes copied.  It should return 0 if no more data
 * can be written to the consumer.
 * `releaseConsumer', if non-NULL, is called when the consumer is freed. */

struct CGDataConsumerCallbacks {
    size_t (*putBytes)(void *info, const void *buffer, size_t count);
    void (*releaseConsumer)(void *info);
};
typedef struct CGDataConsumerCallbacks CGDataConsumerCallbacks;

/* Return the CFTypeID for CGDataConsumerRefs. */

CG_EXTERN CFTypeID CGDataConsumerGetTypeID(void);

/* Create a data consumer using `callbacks' to handle the data.  `info' is
 * passed to each of the callback functions. */

CG_EXTERN CGDataConsumerRef CGDataConsumerCreate(void *info, const CGDataConsumerCallbacks *callbacks);

/* Create a data consumer which writes data to `url'. */

CG_EXTERN CGDataConsumerRef CGDataConsumerCreateWithURL(CFURLRef url);

/* Equivalent to `CFRetain(consumer)'. */

CG_EXTERN CGDataConsumerRef CGDataConsumerRetain(CGDataConsumerRef consumer);

/* Equivalent to `CFRelease(consumer)'. */

CG_EXTERN void CGDataConsumerRelease(CGDataConsumerRef consumer);

CG_EXTERN_C_END

#endif	/* CGDATACONSUMER_H_ */
