/* CoreGraphics - CGPSConverter.h
 * Copyright (c) 2003 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGPSCONVERTER_H_
#define CGPSCONVERTER_H_

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGDataConsumer.h>
#include <CoreGraphics/CGDataProvider.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFString.h>

typedef struct CGPSConverter *CGPSConverterRef;

CG_EXTERN_C_BEGIN

/* CGPSConverter callbacks.
 *
 * `version' is the version number of the structure passed in as a
 * parameter to the converter creation functions. The structure defined
 * below is version 0.
 *
 * `beginDocument', if non-NULL, is called at the beginning of the
 * conversion of the PostScript document.
 *
 * `endDocument', if non-NULL, is called at the end of conversion of the
 * PostScript document.
 *
 * `beginPage', if non-NULL, is called at the start of the conversion of
 * each page in the PostScript document.
 *
 * `endPage', if non-NULL, is called at the end of the conversion of each
 * page in the PostScript document.
 *
 * `noteProgress', if non-NULL, is called periodically during the
 * conversion to indicate that conversion is proceeding.
 *
 * `noteMessage', if non-NULL, is called to pass any messages that might
 * result during the conversion.
 *
 * `releaseInfo', if non-NULL, is called when the converter is
 * deallocated. */

typedef void (*CGPSConverterBeginDocumentCallback)(void *info);

typedef void (*CGPSConverterEndDocumentCallback)(void *info, bool success);

typedef void (*CGPSConverterBeginPageCallback)(void *info, size_t pageNumber, CFDictionaryRef pageInfo);

typedef void (*CGPSConverterEndPageCallback)(void *info, size_t pageNumber, CFDictionaryRef pageInfo);

typedef void (*CGPSConverterProgressCallback)(void *info);

typedef void (*CGPSConverterMessageCallback)(void *info, CFStringRef message);

typedef void (*CGPSConverterReleaseInfoCallback)(void *info);

struct CGPSConverterCallbacks {
    unsigned int version;
    CGPSConverterBeginDocumentCallback beginDocument;
    CGPSConverterEndDocumentCallback endDocument;
    CGPSConverterBeginPageCallback beginPage;
    CGPSConverterEndPageCallback endPage;
    CGPSConverterProgressCallback noteProgress;
    CGPSConverterMessageCallback noteMessage;
    CGPSConverterReleaseInfoCallback releaseInfo;
};
typedef struct CGPSConverterCallbacks CGPSConverterCallbacks;

/* Create a CGPSConverter, using `callbacks' to populate its callback
 * table. Each callback will be supplied the `info' value when called. */

CG_EXTERN CGPSConverterRef CGPSConverterCreate(void *info, const CGPSConverterCallbacks *callbacks, CFDictionaryRef options) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Use `converter' to convert PostScript data to PDF data.  The PostScript
 * data is supplied by `provider'; the resulting PDF is written to
 * `consumer'.  Returns true if the conversion succeeded; false
 * otherwise. */

CG_EXTERN bool CGPSConverterConvert(CGPSConverterRef converter, CGDataProviderRef provider, CGDataConsumerRef consumer, CFDictionaryRef options) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Tell the `converter' to abort conversion at the next possible
 * opportunity. */

CG_EXTERN bool CGPSConverterAbort(CGPSConverterRef converter) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Return true if `converter' is currently converting data. */

CG_EXTERN bool CGPSConverterIsConverting(CGPSConverterRef converter) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Return the CFTypeID of the CGPSConverter class. */

CG_EXTERN CFTypeID CGPSConverterGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

CG_EXTERN_C_END

#endif /* CGPSCONVERTER_H_ */
