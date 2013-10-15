/* $Xorg: lbxdeltastr.h,v 1.3 2000/08/18 04:05:45 coskrey Exp $ */
/*
 * Copyright 1993 Network Computing Devices
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of NCD. not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  NCD. makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * NCD. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL NCD.
 * BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN 
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#ifndef LBX_DELTA_STRUCT_H
#define LBX_DELTA_STRUCT_H

#define MIN_CACHEABLE_LEN		8

#define DELTA_CACHEABLE(pcache, len)	\
	((len) > MIN_CACHEABLE_LEN && (len) <= (pcache)->maxDeltasize)

/*
 * An entry in the delta compactor cache
 */
typedef struct _LBXDeltaElem {
    int			length;
    unsigned char	*buf;
} LBXDeltaElemRec, *LBXDeltaElemPtr;


/*
 * Delta compactor cache
 */
typedef struct _LBXDeltas {
    unsigned short	nDeltas;
    unsigned short	maxDeltasize;
    LBXDeltaElemPtr	deltas;
    unsigned short	nextDelta;
    unsigned short	activeDeltas;	/* only needed for outgoing */
} LBXDeltasRec, *LBXDeltasPtr;


/*
 * Motion delta cache
 */

typedef struct {
    BYTE swapped;
    BYTE detail;
    CARD16 sequenceNumber B16;
    Time time B32;
    Window root B32, event B32, child B32;
    INT16 rootX B16, rootY B16, eventX B16, eventY B16;
    KeyButMask state B16;
    BOOL sameScreen;		
} lbxMotionCache;


/*
 * Motion delta events
 */

typedef struct {
    BYTE type;		/* always eventBase + LbxQuickMotionDeltaEvent */
    CARD8 deltaTime;
    INT8 deltaX;
    INT8 deltaY;
} lbxQuickMotionDeltaEvent;
#define sz_lbxQuickMotionDeltaEvent 4

typedef struct {
    BYTE type;		/* always eventBase + LbxEvent */
    BYTE lbxType;	/* LbxMotionDeltaEvent */
    INT8 deltaX;
    INT8 deltaY;
    CARD16 deltaTime B16;
    CARD16 deltaSequence B16;
} lbxMotionDeltaEvent;
#define sz_lbxMotionDeltaEvent 8

extern int LBXInitDeltaCache ( LBXDeltasPtr pcache, int nDeltas, 
			       int maxDeltasize );
extern void LBXFreeDeltaCache ( LBXDeltasPtr pcache );
extern int LBXDeltaMinDiffs ( LBXDeltasPtr pcache, unsigned char *inmsg, 
			      int inmsglen, int maxdiff, int *pindex );
extern void LBXEncodeDelta ( LBXDeltasPtr pcache, unsigned char *inmsg, 
			     int ndiff, int index, unsigned char *buf );
extern int LBXDecodeDelta ( LBXDeltasPtr pcache, xLbxDiffItem *deltas, 
			    int ndiff, int index, unsigned char **buf );
extern void LBXAddDeltaOut ( LBXDeltasPtr pcache, unsigned char *inmsg, 
			     int inmsglen );
extern void LBXAddDeltaIn ( LBXDeltasPtr pcache, unsigned char *inmsg, 
			    int inmsglen );

#endif /* LBX_DELTA_STRUCT_H */
