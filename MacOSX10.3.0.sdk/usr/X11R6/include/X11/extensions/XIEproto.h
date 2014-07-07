/* $Xorg: XIEproto.h,v 1.6 2001/02/09 02:03:23 xorgcvs Exp $ */
/******************************************************************************
Copyright 1993, 1994, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from The Open Group.


				NOTICE

This software is being provided by AGE Logic, Inc. under the
following license.  By obtaining, using and/or copying this software,
you agree that you have read, understood, and will comply with these
terms and conditions:

     Permission to use, copy, modify, distribute and sell this
     software and its documentation for any purpose and without
     fee or royalty and to grant others any or all rights granted
     herein is hereby granted, provided that you agree to comply
     with the following copyright notice and statements, including
     the disclaimer, and that the same appears on all copies and
     derivative works of the software and documentation you make.
     
     "Copyright 1993, 1994 by AGE Logic, Inc."
     
     THIS SOFTWARE IS PROVIDED "AS IS".  AGE LOGIC MAKES NO
     REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.  By way of
     example, but not limitation, AGE LOGIC MAKE NO
     REPRESENTATIONS OR WARRANTIES OF MERCHANTABILITY OR FITNESS
     FOR ANY PARTICULAR PURPOSE OR THAT THE SOFTWARE DOES NOT
     INFRINGE THIRD-PARTY PROPRIETARY RIGHTS.  AGE LOGIC 
     SHALL BEAR NO LIABILITY FOR ANY USE OF THIS SOFTWARE.  IN NO
     EVENT SHALL EITHER PARTY BE LIABLE FOR ANY INDIRECT,
     INCIDENTAL, SPECIAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOSS
     OF PROFITS, REVENUE, DATA OR USE, INCURRED BY EITHER PARTY OR
     ANY THIRD PARTY, WHETHER IN AN ACTION IN CONTRACT OR TORT OR
     BASED ON A WARRANTY, EVEN IF AGE LOGIC LICENSEES
     HEREUNDER HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH
     DAMAGES.
    
     The name of AGE Logic, Inc. may not be used in
     advertising or publicity pertaining to this software without
     specific, written prior permission from AGE Logic.

     Title to this software shall at all times remain with AGE
     Logic, Inc.
******************************************************************************/

#ifndef _XIEPROTO_H_
#define _XIEPROTO_H_

#include <X11/extensions/XIEprotost.h>

#define Drawable CARD32
#define Colormap CARD32
#define GContext CARD32


typedef struct {        
    CARD8       reqType;
    CARD8       opcode;
    CARD16      length B16;
} xieReq;

typedef struct {        
    CARD8       reqType;
    CARD8       opcode;
    CARD16      length B16;
    CARD16      majorVersion B16;
    CARD16      minorVersion B16;
} xieQueryImageExtensionReq;

typedef struct {
    CARD8               type;
    CARD8               data;
    CARD16              sequenceNum B16;
    CARD32              length B32;
    CARD16              majorVersion B16;
    CARD16              minorVersion B16;
    xieTypServiceClass  serviceClass;
    xieTypAlignment     alignment;
    CARD16		unconstrainedMantissa B16;
    INT32		unconstrainedMaxExp B32;
    INT32		unconstrainedMinExp B32;
    CARD8		pad2[8];
    /* LISTofCARD32 (constrained-levels) */
} xieQueryImageExtensionReply;

typedef struct {        
    CARD8                       reqType;
    CARD8                       opcode;
    CARD16                      length B16;
    xieTypTechniqueGroup        techniqueGroup;
    CARD8                       pad[3];
} xieQueryTechniquesReq;

typedef struct {
    CARD8       type;
    CARD8       data;
    CARD16      sequenceNum B16;
    CARD32      length B32;
    CARD16      numTechniques B16;
    CARD8       pad[22];
    /* LISTofTechniqueRec (numTechniques) */
} xieQueryTechniquesReply;

typedef struct {        
    CARD8               reqType;
    CARD8               opcode;
    CARD16              length B16;
    xieTypColorList     colorList B32;  
} xieCreateColorListReq;

typedef struct {        
    CARD8               reqType;
    CARD8               opcode;
    CARD16              length B16;
    xieTypColorList     colorList B32;  
} xieDestroyColorListReq;

typedef struct {        
    CARD8               reqType;
    CARD8               opcode;
    CARD16              length B16;
    xieTypColorList     colorList B32;  
} xiePurgeColorListReq;

typedef struct {        
    CARD8               reqType;
    CARD8               opcode;
    CARD16              length B16;
    xieTypColorList     colorList B32;  
} xieQueryColorListReq;

typedef struct {
    CARD8       type;
    CARD8       data;
    CARD16      sequenceNum B16;
    CARD32      length B32;
    Colormap    colormap B32;
    CARD8       pad[20];
    /* LISTofCARD32 (length) */
} xieQueryColorListReply;

typedef struct {        
    CARD8       reqType;
    CARD8       opcode;
    CARD16      length B16;
    xieTypLUT   lut B32;
} xieCreateLUTReq;

typedef struct {        
    CARD8       reqType;
    CARD8       opcode;
    CARD16      length B16;
    xieTypLUT   lut B32;
} xieDestroyLUTReq;

typedef struct {        
    CARD8               reqType;
    CARD8               opcode;
    CARD16              length B16;
    xieTypPhotomap      photomap B32;
} xieCreatePhotomapReq;

typedef struct {        
    CARD8               reqType;
    CARD8               opcode;
    CARD16              length B16;
    xieTypPhotomap      photomap B32;
} xieDestroyPhotomapReq;

typedef struct {        
    CARD8               reqType;
    CARD8               opcode;
    CARD16              length B16;
    xieTypPhotomap      photomap B32;
} xieQueryPhotomapReq;

typedef struct {
    CARD8                       type;
    BOOL                        populated;
    CARD16                      sequenceNum B16;
    CARD32                      length B32;
    xieTypDataClass             dataClass;
    xieTypDataType		dataType;
    xieTypDecodeTechnique       decodeTechnique B16;
    CARD32                      width0 B32;
    CARD32                      width1 B32;
    CARD32                      width2 B32;
    CARD32                      height0 B32;
    CARD32                      height1 B32;
    CARD32                      height2 B32;
    CARD32                      levels0 B32;
    CARD32                      levels1 B32;
    CARD32                      levels2 B32;
} xieQueryPhotomapReply;

typedef struct {        
    CARD8       reqType;
    CARD8       opcode;
    CARD16      length B16;
    xieTypROI   roi B32;
} xieCreateROIReq;

typedef struct {        
    CARD8       reqType;
    CARD8       opcode;
    CARD16      length B16;
    xieTypROI   roi B32;
} xieDestroyROIReq;

typedef struct {
    CARD8               reqType;
    CARD8               opcode;
    CARD16              length B16;
    xieTypPhotospace    nameSpace B32;
} xieCreatePhotospaceReq;

typedef struct {
    CARD8               reqType;
    CARD8               opcode;
    CARD16              length B16;
    xieTypPhotospace    nameSpace B32;
} xieDestroyPhotospaceReq;

typedef struct {
    CARD8		reqType;
    CARD8		opcode;
    CARD16		length B16;
    xieTypPhotospace    nameSpace B32;
    CARD32		floID B32;
    CARD16		numElements B16;
    BOOL		notify;
    CARD8		pad;                    
    /* LISTofPhotoElement (numElements) */
} xieExecuteImmediateReq;
 
typedef struct {
    CARD8               reqType;
    CARD8               opcode;
    CARD16              length B16;
    xieTypPhotoflo      floID B32;
    CARD16              numElements B16;
    CARD16              pad B16;                        
    /* LISTofPhotoElement (numElements) */
} xieCreatePhotofloReq;

typedef struct {
    CARD8               reqType;
    CARD8               opcode;
    CARD16              length B16;
    xieTypPhotoflo      floID B32;
} xieDestroyPhotofloReq;

typedef struct {
    CARD8               reqType;
    CARD8               opcode;
    CARD16              length B16;
    xieTypPhotoflo      floID B32;
    BOOL                notify;
    CARD8               pad[3];                 
} xieExecutePhotofloReq;

typedef struct {
    CARD8               reqType;
    CARD8               opcode;
    CARD16              length B16;
    xieTypPhotoflo      floID B32;
    xieTypPhototag      start B16;
    CARD16              numElements B16;
    /* LISTofPhotoElement (numElements) */
} xieModifyPhotofloReq;

typedef struct {
    CARD8               reqType;
    CARD8               opcode;
    CARD16              length B16;
    xieTypPhotoflo      floID B32;
    CARD16              numElements B16;
    CARD16              pad B16;
    /* LISTofPhotoElement (numElements) */
} xieRedefinePhotofloReq;

typedef struct {
    CARD8               reqType;
    CARD8               opcode;
    CARD16              length B16;
    CARD32              nameSpace B32;
    CARD32              floID B32;
    xieTypPhototag      element B16;
    BOOL                final;
    CARD8               bandNumber;
    CARD32              byteCount B32;
    /* LISTofCARD8 (byteCount) */
    /* pad (byteCount) */
} xiePutClientDataReq;

typedef struct {
    CARD8               reqType;
    CARD8               opcode;
    CARD16              length B16;
    CARD32              nameSpace B32;
    CARD32              floID B32;
    CARD32              maxBytes B32;
    xieTypPhototag      element B16;
    BOOL                terminate;
    CARD8               bandNumber;
} xieGetClientDataReq;

typedef struct {
    CARD8       type;
    CARD8       newState;
    CARD16      sequenceNum B16;
    CARD32      length B32;
    CARD32      byteCount B32;
    CARD8       pad[20];
    /* LISTofCARD8 (byteCount) */
    /* pad (byteCount) */
} xieGetClientDataReply;

typedef struct {
    CARD8       reqType;
    CARD8       opcode;
    CARD16      length B16;
    CARD32      nameSpace B32;
    CARD32      floID B32;
} xieQueryPhotofloReq;

typedef struct {
    CARD8       type;
    CARD8       state;
    CARD16      sequenceNum B16;
    CARD32      length B32;
    CARD16      expectedCount B16;
    CARD16      availableCount B16;
    CARD8       pad[20];
    /* LISTofPhototag (expectedCount) */
    /* pad (expectedCount * 2) */
    /* LISTofPhototag (availableCount) */
    /* pad (availableCount * 2) */
} xieQueryPhotofloReply;

typedef struct {
    CARD8       reqType;
    CARD8       opcode;
    CARD16      length B16;
    CARD32      nameSpace B32;
    CARD32      floID B32;
} xieAwaitReq;

typedef struct {
    CARD8       reqType;
    CARD8       opcode;
    CARD16      length B16;
    CARD32      nameSpace B32;
    CARD32      floID B32;
} xieAbortReq;


/*
 * Request codes
 */

#define X_ieQueryImageExtension		1
#define X_ieQueryTechniques		2
#define X_ieCreateColorList		3
#define X_ieDestroyColorList		4
#define X_iePurgeColorList		5
#define X_ieQueryColorList		6
#define X_ieCreateLUT			7
#define X_ieDestroyLUT			8
#define X_ieCreatePhotomap		9
#define X_ieDestroyPhotomap		10
#define X_ieQueryPhotomap		11
#define X_ieCreateROI			12
#define X_ieDestroyROI			13
#define X_ieCreatePhotospace		14
#define X_ieDestroyPhotospace		15
#define X_ieExecuteImmediate		16
#define X_ieCreatePhotoflo		17
#define X_ieDestroyPhotoflo		18
#define X_ieExecutePhotoflo		19
#define X_ieModifyPhotoflo		20
#define X_ieRedefinePhotoflo		21
#define X_iePutClientData		22
#define X_ieGetClientData		23
#define X_ieQueryPhotoflo		24
#define X_ieAwait			25
#define X_ieAbort			26

#define xieNumProtoReq			26


/*
 * Events
 */
typedef struct {
    CARD8			event;
    xieTypPhotofloOutcome	outcome;
    CARD16			sequenceNum B16;
    CARD32			time B32;
    CARD32			instanceNameSpace B32;
    CARD32			instanceFloID B32;
    CARD8			pad[16];
} xiePhotofloDoneEvn;

typedef struct {
    CARD8			event;
    CARD8			pad1;
    CARD16			sequenceNum B16;
    CARD32			time B32;
    CARD32			instanceNameSpace B32;
    CARD32			instanceFloID B32;
    xieTypPhototag		src B16;
    CARD16			type B16;
    CARD32			pad2 B32;
    CARD32			pad3 B16;
    CARD32			pad4 B32;
} xieFloEvn;

typedef struct {
    CARD8			event;
    CARD8			pad1;
    CARD16			sequenceNum B16;
    CARD32			time B32;
    CARD32			instanceNameSpace B32;
    CARD32			instanceFloID B32;
    xieTypPhototag		src B16;
    CARD16			type B16;
    xieTypColorList		colorList B32;
    xieTypColorAllocTechnique	colorAllocTechnique B16;
    CARD16			pad2 B16;
    CARD32			data B32;
} xieColorAllocEvn;

typedef struct {
    CARD8			event;
    CARD8			bandNumber;
    CARD16			sequenceNum B16;
    CARD32			time B32;
    CARD32			instanceNameSpace B32;
    CARD32			instanceFloID B32;
    xieTypPhototag		src B16;
    CARD16			type B16;
    xieTypDecodeTechnique	decodeTechnique B16;
    BOOL			aborted;
    CARD8			pad;
    CARD32			width B32;
    CARD32		        height B32;
} xieDecodeNotifyEvn;

typedef struct {
    CARD8		event;
    CARD8		bandNumber;
    CARD16		sequenceNum B16;
    CARD32		time B32;
    CARD32		instanceNameSpace B32;
    CARD32		instanceFloID B32;
    xieTypPhototag	src B16;
    CARD16		type B16;
    CARD32		data0 B32;
    CARD32		data1 B32;
    CARD32		data2 B32;
} xieExportAvailableEvn;

typedef struct {
    CARD8		event;
    CARD8		pad;
    CARD16		sequenceNum B16;
    CARD32		time B32;
    CARD32		instanceNameSpace B32;
    CARD32		instanceFloID B32;
    xieTypPhototag	src B16;
    CARD16		type B16;
    Window		window B32;
    INT16		x B16;
    INT16		y B16;
    CARD16		width B16;
    CARD16		height B16;
} xieImportObscuredEvn;


/*
 * Errors
 */
typedef struct {
    CARD8	      error;
    CARD8             code;
    CARD16            sequenceNum B16;
    CARD32            resourceID B32;
    CARD16	      minorOpcode B16;
    CARD8	      majorOpcode;
    CARD8             pad[21];
} xieResourceErr;

typedef struct {
    CARD8             error;
    CARD8             code;
    CARD16            sequenceNum B16;
    CARD32            floID B32;
    CARD16	      minorOpcode B16;
    CARD8	      majorOpcode;
    CARD8             floErrorCode;
    CARD32            nameSpace B32;
    xieTypPhototag    phototag B16;
    CARD16            type B16;
    CARD32	      resourceID B32;
    CARD8             pad[8];
} xieFloResourceErr;

typedef struct {
    CARD8             error;
    CARD8             code;
    CARD16            sequenceNum B16;
    CARD32            floID B32;
    CARD16	      minorOpcode B16;
    CARD8	      majorOpcode;
    CARD8             floErrorCode;
    CARD32            nameSpace B32;
    xieTypPhototag    phototag B16;
    CARD16            type B16;
    CARD8             pad[12];
} xieFloErr, xieFloAccessErr, xieFloAllocErr, xieFloElementErr,
  xieFloLengthErr, xieFloMatchErr, xieFloSourceErr, xieFloImplementationErr;

typedef struct {
    CARD8             error;
    CARD8             code;
    CARD16            sequenceNum B16;
    CARD32            floID B32;
    CARD16	      minorOpcode B16;
    CARD8	      majorOpcode;
    CARD8             floErrorCode;
    CARD32            nameSpace B32;
    xieTypPhototag    phototag B16;
    CARD16            type B16;
    xieTypPhototag    domainSrc B16;
    CARD8             pad[10];
} xieFloDomainErr;

typedef struct {
    CARD8             error;
    CARD8             code;
    CARD16            sequenceNum B16;
    CARD32            floID B32;
    CARD16	      minorOpcode B16;
    CARD8	      majorOpcode;
    CARD8             floErrorCode;
    CARD32            nameSpace B32;
    CARD8             pad[16];
} xieFloIDErr;

typedef struct {
    CARD8             error;
    CARD8             code;
    CARD16            sequenceNum B16;
    CARD32            floID B32;
    CARD16	      minorOpcode B16;
    CARD8	      majorOpcode;
    CARD8             floErrorCode;
    CARD32            nameSpace B32;
    xieTypPhototag    phototag B16;
    CARD16            type B16;
#if defined(__cplusplus) || defined(c_plusplus)
    CARD8             c_operator;
#else
    CARD8             operator;
#endif
    CARD8             pad[11];
} xieFloOperatorErr;

typedef struct {
    CARD8             error;
    CARD8             code;
    CARD16            sequenceNum B16;
    CARD32            floID B32;
    CARD16	      minorOpcode B16;
    CARD8	      majorOpcode;
    CARD8             floErrorCode;
    CARD32            nameSpace B32;
    xieTypPhototag    phototag B16;
    CARD16            type B16;
    CARD16            techniqueNumber B16;
    CARD16            lenTechParams B16;
    CARD8             techniqueGroup;
    CARD8             pad[7];
} xieFloTechniqueErr;

typedef struct {
    CARD8             error;
    CARD8             code;
    CARD16            sequenceNum B16;
    CARD32            floID B32;
    CARD16	      minorOpcode B16;
    CARD8	      majorOpcode;
    CARD8             floErrorCode;
    CARD32            nameSpace B32;
    xieTypPhototag    phototag B16;
    CARD16            type B16;
    CARD32            badValue B32;
    CARD8             pad[8];
} xieFloValueErr;



/*
 * SIZEOF values
 */
#define sz_xieReq                        4
#define sz_xieQueryImageExtensionReq     8
#define sz_xieQueryImageExtensionReply  32
#define sz_xieQueryTechniquesReq         8
#define sz_xieQueryTechniquesReply      32
#define sz_xieCreateColorListReq         8
#define sz_xieDestroyColorListReq        8
#define sz_xiePurgeColorListReq          8
#define sz_xieQueryColorListReq          8
#define sz_xieQueryColorListReply       32
#define sz_xieCreateLUTReq               8
#define sz_xieDestroyLUTReq              8
#define sz_xieCreatePhotomapReq          8
#define sz_xieDestroyPhotomapReq         8
#define sz_xieQueryPhotomapReq           8
#define sz_xieQueryPhotomapReply        48
#define sz_xieCreateROIReq               8
#define sz_xieDestroyROIReq              8
#define sz_xieCreatePhotospaceReq        8
#define sz_xieDestroyPhotospaceReq       8
#define sz_xieExecuteImmediateReq       16
#define sz_xieCreatePhotofloReq         12
#define sz_xieDestroyPhotofloReq         8
#define sz_xieExecutePhotofloReq        12
#define sz_xieModifyPhotofloReq         12
#define sz_xieRedefinePhotofloReq       12
#define sz_xiePutClientDataReq          20
#define sz_xieGetClientDataReq          20
#define sz_xieGetClientDataReply        32
#define sz_xieQueryPhotofloReq          12
#define sz_xieQueryPhotofloReply        32
#define sz_xieAwaitReq                  12
#define sz_xieAbortReq                  12

#define sz_xiePhotofloDoneEvn		32
#define sz_xieColorAllocEvn		32
#define sz_xieDecodeNotifyEvn		32
#define sz_xieExportAvailableEvn	32
#define sz_xieImportObscuredEvn		32
#define sz_xieFloEvn			32

#define sz_xieResourceErr		32
#define sz_xieFloAccessErr		32
#define sz_xieFloAllocErr		32
#define sz_xieFloElementErr		32
#define sz_xieFloIDErr			32
#define sz_xieFloLengthErr		32
#define sz_xieFloMatchErr		32
#define sz_xieFloSourceErr		32
#define sz_xieFloDomainErr		32
#define sz_xieFloOperatorErr		32
#define sz_xieFloTechniqueErr		32
#define sz_xieFloValueErr		32
#define sz_xieFloImplementationErr	32
#define sz_xieFloErr			32

#undef Drawable
#undef Colormap
#undef GContext

#endif /* _XIEPROTO_H_ */
