/* CoreGraphics - CGPDFStream.h
 * Copyright (c) 2002-2007 Apple Inc.
 * All rights reserved.
 */

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

CG_EXTERN_C_BEGIN

/* Return the dictionary of `stream'. */

CG_EXTERN CGPDFDictionaryRef CGPDFStreamGetDictionary(CGPDFStreamRef stream) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Return the data of `stream'. */

CG_EXTERN CFDataRef CGPDFStreamCopyData(CGPDFStreamRef stream, CGPDFDataFormat *format) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

CG_EXTERN_C_END

#endif	/* CGPDFSTREAM_H_ */
