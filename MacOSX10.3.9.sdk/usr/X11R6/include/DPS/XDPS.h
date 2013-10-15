/*
  XDPS.h -- DPS extension constants, analogous to X.h

Copyright 1988-1994 Adobe Systems Incorporated.
Portions Copyright 1988, 1989 Digital Equipment Corporation.

Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby granted,
provided that the above copyright notices appear in all copies and
that both those copyright notices and this permission notice appear
in supporting documentation, and that the names of Adobe Systems 
Incorporated and Digital Equipment Corporation not be used in 
advertising or publicity pertaining to distribution of the software 
without specific, written prior permission.  Adobe Systems Incorporated
and Digital Equipment Corporation make no representations about the 
suitability of this software for any purpose.  It is provided "as is" 
without express or implied warranty.

ADOBE SYSTEMS INCORPORATED AND DIGITAL EQUIPMENT CORPORATION DISCLAIM
ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL ADOBE
SYSTEMS INCORPORATED AND DIGITAL EQUIPMENT CORPORATION BE LIABLE FOR
ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES 
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN 
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT 
OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

Author: Adobe Systems Incorporated and Digital Equipment Corporation
  
*/


#ifndef _XDPS_h
#define _XDPS_h

#include <X11/Xmd.h>

/*
 * Number of events and errors required by extension
 */
#define NPSEVENTS		3               /* L2-DPS/PROTO 9 change */
#define NPSERRORS		3               /* L2-DPS/PROTO 9 change */

#define NPSEVENTS_P8		2
#define NPSERRORS_P8		2


/*
 * For XPSNotifyContext: types of notification.
 */

#define PSKILL			0
#define PSINTERRUPT		1
#define PSUNFREEZE		2


/*
 * For XPSGetStatus: types of status.
 */

#define PSSTATUSERROR		0
#define PSRUNNING		1
#define PSNEEDSINPUT		2
#define PSZOMBIE		3
#define PSFROZEN		4

#define PSNUMSTATUS		4 /* Number of real status codes */

/*
 * For XPSSetStatusMask: Status Masks
 */

#define PSRUNNINGMASK           0x0001
#define PSNEEDSINPUTMASK        0x0002
#define PSZOMBIEMASK            0x0004
#define PSFROZENMASK            0x0008


/*
 * Error codes (offset from extension error base)
 */

#define PSERRORBADCONTEXT	0
#define PSERRORBADSPACE		1
#define PSERRORABORT		2             /* L2-DPS/PROTO 9 addition */


/*
 * Event codes (offset from extension event base)
 */

#define PSEVENTOUTPUT		0
#define PSEVENTSTATUS		1
#define PSEVENTREADY		2             /* L2-DPS/PROTO 9 addition */


/*
 * Request field types
 */

typedef int	 ContextPSID;
typedef XID	 ContextXID;
typedef XID	 SpaceXID;


/*
 * Floating point types (the same as in dpsfriends.h).
 */

#ifndef DPS_HI_IEEE

#define DPS_HI_IEEE	128
#define DPS_LO_IEEE	129
#define DPS_HI_NATIVE	130
#define DPS_LO_NATIVE	131

#endif /* not DPS_HI_IEEE */

#endif /* _XDPS_h */
