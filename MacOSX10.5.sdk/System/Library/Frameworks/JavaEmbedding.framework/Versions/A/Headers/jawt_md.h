/*
 * @(#)jawt_md.h    1.2 99/05/27
 *
 * Copyright 1999 by Sun Microsystems, Inc.,
 * 901 San Antonio Road, Palo Alto, California, 94303, U.S.A.
 * All rights reserved.
 *
 * This software is the confidential and proprietary information
 * of Sun Microsystems, Inc. ("Confidential Information").  You
 * shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Sun.
 */

#ifndef _JAVASOFT_JAWT_MD_H_
#define _JAVASOFT_JAWT_MD_H_

#include "jawt.h"

#include <ApplicationServices/ApplicationServices.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * MacOSX-specific declarations for AWT native interface.
 * See notes in jawt.h for an example of use.
 */
typedef struct jawt_MacDrawingSurfaceInfo
{
    // QuickDraw stuff
	GDevice*        fQDDevice;
	GrafPtr         fQDPort;
	WindowRef       fQDWindow;
    
    // CoreGraphics stuff
	CGRect       	fLocationInParent; // in CG coordinate space
	UInt32 			fCGWindowID;
	UInt32 			fCGConnectionID;

} JAWT_MacDrawingSurfaceInfo;

#ifdef __cplusplus
}
#endif

#endif /* !_JAVASOFT_JAWT_MD_H_ */