/* CoreGraphics - CGPDFStream.h
 * Copyright (c) 2002-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGPDFSTREAM_H_
#define CGPDFSTREAM_H_

typedef struct CGPDFStream *CGPDFStreamRef;

enum CGPDFDataFormat {
    CGPDFDataFormatRaw, CGPDFDataFormatJPEGEncoded, CGPDFDataFormatJPEG2000
};
typedef enum CGPDFDataFormat CGPDFDataFormat;

#include <CoreGraphics/CGPDFDictionary.h>
#include <CoreGraphics/CGPDFStream.h>
#include <CoreFoundation/CFData.h>

/* Return the dictionary of `stream'. */

CG_EXTERN CGPDFDictionaryRef CGPDFStreamGetDictionary(CGPDFStreamRef stream)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Return the data of `stream'. */

CG_EXTERN CFDataRef CGPDFStreamCopyData(CGPDFStreamRef stream,
    CGPDFDataFormat *format)
    CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

#endif /* CGPDFSTREAM_H_ */
