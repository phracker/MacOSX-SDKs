/* CoreGraphics - CGPDFOperatorTable.h
 * Copyright (c) 2004 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGPDFOPERATORTABLE_H_
#define CGPDFOPERATORTABLE_H_

typedef struct CGPDFOperatorTable *CGPDFOperatorTableRef;

#include <CoreGraphics/CGPDFScanner.h>

typedef void (*CGPDFOperatorCallback)(CGPDFScannerRef scanner, void *info);

CG_EXTERN_C_BEGIN

/* Return an empty operator table. */

CG_EXTERN CGPDFOperatorTableRef CGPDFOperatorTableCreate(void) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Increment the retain count of `table'. */

CG_EXTERN CGPDFOperatorTableRef CGPDFOperatorTableRetain(CGPDFOperatorTableRef table) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Decrement the retain count of `table'. */

CG_EXTERN void CGPDFOperatorTableRelease(CGPDFOperatorTableRef table) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Set the callback for the operator named `name' to `callback' */

CG_EXTERN void CGPDFOperatorTableSetCallback(CGPDFOperatorTableRef table, const char *name, CGPDFOperatorCallback callback) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CG_EXTERN_C_END

#endif	/* CGPDFOPERATORTABLE_H_ */
