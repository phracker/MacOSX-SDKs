/* CoreGraphics - CGPDFScanner.h
 * Copyright (c) 2004 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGPDFSCANNER_H_
#define CGPDFSCANNER_H_

typedef struct CGPDFScanner *CGPDFScannerRef;

#include <CoreGraphics/CGPDFContentStream.h>
#include <CoreGraphics/CGPDFOperatorTable.h>

CG_EXTERN_C_BEGIN

/* Create a scanner. */

CG_EXTERN CGPDFScannerRef CGPDFScannerCreate(CGPDFContentStreamRef cs, CGPDFOperatorTableRef table, void *info) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Retain `scanner'. */

CG_EXTERN CGPDFScannerRef CGPDFScannerRetain(CGPDFScannerRef scanner) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Release `scanner'. */

CG_EXTERN void CGPDFScannerRelease(CGPDFScannerRef scanner) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Scan the content stream of `scanner'. Returns true if the entire stream
 * was scanned successfully; false if scanning failed for some reason (for
 * example, if the stream's data is corrupted). */

CG_EXTERN bool CGPDFScannerScan(CGPDFScannerRef scanner) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Return the content stream associated with `scanner'. */

CG_EXTERN CGPDFContentStreamRef CGPDFScannerGetContentStream(CGPDFScannerRef scanner) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Pop an object from the stack of `scanner' and return it in `value'. */

CG_EXTERN bool CGPDFScannerPopObject(CGPDFScannerRef scanner, CGPDFObjectRef *value) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Pop an object from the stack of `scanner' and, if it's a boolean, return
 * it in `value'. Return false if the top of the stack isn't a boolean. */

CG_EXTERN bool CGPDFScannerPopBoolean(CGPDFScannerRef scanner, CGPDFBoolean *value) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Pop an object from the stack of `scanner' and, if it's an integer,
 * return it in `value'. Return false if the top of the stack isn't an
 * integer. */

CG_EXTERN bool CGPDFScannerPopInteger(CGPDFScannerRef scanner, CGPDFInteger *value) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Pop an object from the stack of `scanner' and, if it's a number, return
 * it in `value'. Return false if the top of the stack isn't a number. */

CG_EXTERN bool CGPDFScannerPopNumber(CGPDFScannerRef scanner, CGPDFReal *value) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Pop an object from the stack of `scanner' and, if it's a name, return it
 * in `value'. Return false if the top of the stack isn't a name. */

CG_EXTERN bool CGPDFScannerPopName(CGPDFScannerRef scanner, const char **value) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Pop an object from the stack of `scanner' and, if it's a string, return
 * it in `value'. Return false if the top of the stack isn't a string. */

CG_EXTERN bool CGPDFScannerPopString(CGPDFScannerRef scanner, CGPDFStringRef *value) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Pop an object from the stack of `scanner' and, if it's an array, return
 * it in `value'. Return false if the top of the stack isn't an array. */

CG_EXTERN bool CGPDFScannerPopArray(CGPDFScannerRef scanner, CGPDFArrayRef *value) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Pop an object from the stack of `scanner' and, if it's a dictionary,
 * return it in `value'. Return false if the top of the stack isn't a
 * dictionary. */

CG_EXTERN bool CGPDFScannerPopDictionary(CGPDFScannerRef scanner, CGPDFDictionaryRef *value) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Pop an object from the stack of `scanner' and, if it's a stream, return
 * it in `value'. Return false if the top of the stack isn't a stream. */

CG_EXTERN bool CGPDFScannerPopStream(CGPDFScannerRef scanner, CGPDFStreamRef *value) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CG_EXTERN_C_END

#endif	/* CGPDFSCANNER_H_ */
