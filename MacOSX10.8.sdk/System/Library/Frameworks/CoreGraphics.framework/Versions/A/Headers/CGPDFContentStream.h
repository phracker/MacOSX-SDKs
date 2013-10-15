/* CoreGraphics - CGPDFContentStream.h
   Copyright (c) 2004-2011 Apple Inc.
   All rights reserved. */

#ifndef CGPDFCONTENTSTREAM_H_
#define CGPDFCONTENTSTREAM_H_

typedef struct CGPDFContentStream *CGPDFContentStreamRef;

#include <CoreGraphics/CGPDFPage.h>

/* Create a content stream from `page'. */

CG_EXTERN CGPDFContentStreamRef CGPDFContentStreamCreateWithPage(
  CGPDFPageRef page) CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Create a content stream from `stream'. */

CG_EXTERN CGPDFContentStreamRef CGPDFContentStreamCreateWithStream(
  CGPDFStreamRef stream, CGPDFDictionaryRef streamResources,
  CGPDFContentStreamRef parent)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Increment the retain count of `cs'. */

CG_EXTERN CGPDFContentStreamRef CGPDFContentStreamRetain(
  CGPDFContentStreamRef cs) CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Decrement the retain count of `cs'. */

CG_EXTERN void CGPDFContentStreamRelease(CGPDFContentStreamRef cs)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Return the array of CGPDFStreamRefs comprising the entire content stream
   of `cs'. */

CG_EXTERN CFArrayRef CGPDFContentStreamGetStreams(CGPDFContentStreamRef cs)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Return the resource named `name' in category `category' of the resource
   dictionaries of `cs'. */

CG_EXTERN CGPDFObjectRef CGPDFContentStreamGetResource(
  CGPDFContentStreamRef cs, const char *category, const char *name)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

#endif /* CGPDFCONTENTSTREAM_H_ */
