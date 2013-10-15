/* CoreGraphics - CGPDFOperatorTable.h
 * Copyright (c) 2004-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGPDFOPERATORTABLE_H_
#define CGPDFOPERATORTABLE_H_

typedef struct CGPDFOperatorTable *CGPDFOperatorTableRef;

#include <CoreGraphics/CGPDFScanner.h>

typedef void (*CGPDFOperatorCallback)(CGPDFScannerRef scanner, void *info);

/* Return an empty operator table. */

CG_EXTERN CGPDFOperatorTableRef CGPDFOperatorTableCreate(void)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Increment the retain count of `table'. */

CG_EXTERN CGPDFOperatorTableRef CGPDFOperatorTableRetain(CGPDFOperatorTableRef
    table) CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Decrement the retain count of `table'. */

CG_EXTERN void CGPDFOperatorTableRelease(CGPDFOperatorTableRef table)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Set the callback for the operator named `name' to `callback' */

CG_EXTERN void CGPDFOperatorTableSetCallback(CGPDFOperatorTableRef table,
    const char *name, CGPDFOperatorCallback callback)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

#endif	/* CGPDFOPERATORTABLE_H_ */
