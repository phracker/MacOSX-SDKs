/* CoreGraphics - CGPDFContentStream.h
 * Copyright (c) 2004 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGPDFCONTENTSTREAM_H_
#define CGPDFCONTENTSTREAM_H_

typedef struct CGPDFContentStream *CGPDFContentStreamRef;

#include <CoreGraphics/CGPDFPage.h>

CG_EXTERN_C_BEGIN

/* Create a content stream from `page'. */

CG_EXTERN CGPDFContentStreamRef CGPDFContentStreamCreateWithPage(CGPDFPageRef page) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Create a content stream from `stream'. */

CG_EXTERN CGPDFContentStreamRef CGPDFContentStreamCreateWithStream(CGPDFStreamRef stream, CGPDFDictionaryRef streamResources, CGPDFContentStreamRef parent) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Increment the retain count of `cs'. */

CG_EXTERN CGPDFContentStreamRef CGPDFContentStreamRetain(CGPDFContentStreamRef cs) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Decrement the retain count of `cs'. */

CG_EXTERN void CGPDFContentStreamRelease(CGPDFContentStreamRef cs) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Return the array of CGPDFStreamRefs comprising the entire content stream
 * of `cs'. */

CG_EXTERN CFArrayRef CGPDFContentStreamGetStreams(CGPDFContentStreamRef cs) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Return the resource named `name' in category `category' of the resource
 * dictionaries of `cs'. */

CG_EXTERN CGPDFObjectRef CGPDFContentStreamGetResource(CGPDFContentStreamRef cs, const char *category, const char *name) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CG_EXTERN_C_END

#endif	/* CGPDFCONTENTSTREAM_H_ */
