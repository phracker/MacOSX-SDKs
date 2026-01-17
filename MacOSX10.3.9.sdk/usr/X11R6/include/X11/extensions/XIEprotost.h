/* $Xorg: XIEprotost.h,v 1.7 2001/02/09 02:03:23 xorgcvs Exp $ */
/******************************************************************************


Copyright 1993, 1994, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.


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

#ifndef _XIEPROTOST_H_
#define _XIEPROTOST_H_

#include <X11/Xmd.h>			/* defines things like CARD32 */

#define Drawable CARD32
#define Colormap CARD32
#define GContext CARD32

typedef CARD32	xieTypFloat;

#ifndef WORD64

typedef xieTypFloat 	xieTypConstant[3];

typedef xieTypFloat 	xieTypMatrix[9];

#else /* WORD64 */

typedef CARD8	xieTypConstant[12];

typedef CARD8	xieTypMatrix[36];

#endif /* WORD64 */


typedef CARD8	xieTypAlignment;

typedef CARD8	xieTypArithmeticOp;

typedef CARD16  xieTypColorAllocTechnique;

typedef	CARD32	xieTypColorList;

typedef CARD8	xieTypCompareOp;

typedef CARD16  xieTypConstrainTechnique;

typedef CARD16  xieTypConvertFromRGBTechnique;

typedef CARD16  xieTypConvertToRGBTechnique;

typedef CARD16  xieTypConvolveTechnique;

typedef CARD8	xieTypDataClass;

typedef CARD8	xieTypDataType;

typedef CARD16  xieTypDecodeTechnique;

typedef CARD16  xieTypDitherTechnique;

typedef CARD16  xieTypEncodeTechnique;

typedef CARD32	xieTypPhotospace;

typedef CARD32	xieTypPhotoflo;

typedef struct {
  union {
    struct {
      xieTypPhotospace	nameSpace B32;
      CARD32		floID B32;
    } immed;
    struct {
      CARD32		nameSpace B32;
      xieTypPhotoflo	floID B32;
    } stored;
  } u;
} xieTypExecutable;

typedef CARD8	xieTypExportNotify;

typedef CARD8	xieTypExportState;

typedef CARD16	xieTypGamutTechnique;

typedef CARD16	xieTypGeometryTechnique;

typedef struct {
    CARD32	value B32;
    CARD32	count B32;
} xieTypHistogramData;

typedef CARD16	xieTypHistogramShape;

typedef CARD8	xieTypInterleave;

typedef CARD32	xieTypLevels[3];

typedef	CARD32	xieTypLUT;

typedef CARD8	xieTypMathOp;

typedef CARD8	xieTypOrientation;

typedef CARD8	xieTypPhotofloOutcome;

typedef CARD8	xieTypPhotofloState;

typedef CARD32	xieTypPhotomap;

typedef CARD16	xieTypPhototag;

typedef struct {
    INT32		offsetX B32;
    INT32		offsetY B32;
    xieTypPhototag	domain B16;		
} xieTypProcessDomain;

typedef struct {
    INT32	x B32;
    INT32	y B32;
    CARD32	width B32;
    CARD32	height B32;
} xieTypRectangle;

typedef CARD32	xieTypROI;

typedef CARD8	xieTypServiceClass;

typedef CARD8	xieTypTechniqueGroup;

typedef struct {
    BOOL			needsParam;
    xieTypTechniqueGroup	group;
    CARD16			number B16;
    CARD8			speed;
    CARD8			nameLength;
    CARD16			pad B16;
    /* LISTofCARD8 (nameLength) */
    /* pad (nameLength) */
} xieTypTechniqueRec;

typedef struct {
    xieTypPhototag 	src B16;
    CARD16		pad B16;
    INT32		dstX B32;
    INT32		dstY B32;
} xieTypTile;

typedef CARD8	xieTypTripleofCARD8[3];

typedef CARD16  xieTypTripleofCARD16[3];

typedef CARD32	xieTypTripleofCARD32[3];

typedef CARD16  xieTypWhiteAdjustTechnique;


/*
 * Generic Element
 */

typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
} xieFlo;

/*
 * Import Elements
 */
typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
#if defined(__cplusplus) || defined(c_plusplus)
    xieTypDataClass	c_class;
#else
    xieTypDataClass	class;
#endif
    xieTypOrientation	bandOrder;
    CARD16		pad B16;
    CARD32		length0 B32;
    CARD32		length1 B32;
    CARD32		length2 B32;
    CARD32		levels0 B32;
    CARD32		levels1 B32;
    CARD32		levels2 B32;
} xieFloImportClientLUT;

typedef struct {
    CARD16			elemType B16;
    CARD16			elemLength B16;
    BOOL			notify;
#if defined(__cplusplus) || defined(c_plusplus)
    xieTypDataClass 		c_class;
#else
    xieTypDataClass 		class;
#endif
    CARD16			pad B16;
    CARD32			width0 B32;
    CARD32			width1 B32;
    CARD32			width2 B32;
    CARD32			height0 B32;
    CARD32			height1 B32;
    CARD32			height2 B32;
    CARD32			levels0 B32;
    CARD32			levels1 B32;
    CARD32			levels2 B32;
    xieTypDecodeTechnique	decodeTechnique B16;
    CARD16			lenParams B16;
    /* Technique dependent decode params */
} xieFloImportClientPhoto;

typedef struct {
    CARD16	elemType B16;
    CARD16	elemLength B16;
    CARD32	rectangles B32;
} xieFloImportClientROI;

typedef struct {
    CARD16	elemType B16;
    CARD16	elemLength B16;
    Drawable	drawable B32;
    INT16	srcX B16;
    INT16	srcY B16;
    CARD16	width B16;
    CARD16	height B16;
    CARD32	fill B32;
    BOOL	notify;
    CARD8	pad[3];		
} xieFloImportDrawable;

typedef struct {
    CARD16	elemType B16;
    CARD16	elemLength B16;
    Drawable	drawable B32;
    INT16	srcX B16;
    INT16	srcY B16;
    CARD16	width B16;
    CARD16	height B16;
    CARD32	fill B32;
    CARD32	bitPlane B32;
    BOOL	notify;
    CARD8	pad[3];		
} xieFloImportDrawablePlane;

typedef struct {
    CARD16	elemType B16;
    CARD16	elemLength B16;
    xieTypLUT	lut B32;
} xieFloImportLUT;
 
typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
    xieTypPhotomap	photomap B32;
    BOOL		notify;
    CARD8		pad[3];
} xieFloImportPhotomap;

typedef struct {
    CARD16	elemType B16;
    CARD16	elemLength B16;
    xieTypROI	roi B32;
} xieFloImportROI;


/*
 * Process Elements
 */
typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
    xieTypPhototag	src1 B16;
    xieTypPhototag	src2 B16;
    INT32		domainOffsetX B32;
    INT32		domainOffsetY B32;
    xieTypPhototag	domainPhototag B16;		
#if defined(__cplusplus) || defined(c_plusplus)
    xieTypArithmeticOp	c_operator;
#else
    xieTypArithmeticOp	operator;
#endif
    CARD8		bandMask;
    xieTypFloat		constant0 B32;
    xieTypFloat		constant1 B32;
    xieTypFloat		constant2 B32;
} xieFloArithmetic;

typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
    xieTypPhototag	src1 B16;
    xieTypPhototag	src2 B16;
    xieTypPhototag	src3 B16;
    CARD16		pad B16;
} xieFloBandCombine;

typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
    xieTypPhototag	src B16;
    CARD16		pad B16;
    CARD32		levels B32;
    xieTypFloat		bias B32;
    xieTypFloat		constant0 B32;
    xieTypFloat		constant1 B32;
    xieTypFloat		constant2 B32;
} xieFloBandExtract;

typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
    xieTypPhototag	src B16;
    CARD8		bandNumber;
    CARD8		pad;
} xieFloBandSelect;

typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
    xieTypPhototag	src1 B16;
    xieTypPhototag	src2 B16;
    xieTypPhototag	alpha B16;
    CARD16		pad1 B16;
    INT32		domainOffsetX B32;
    INT32		domainOffsetY B32;
    xieTypPhototag	domainPhototag B16;		
    CARD8		bandMask;
    CARD8		pad2;
    xieTypFloat		constant0 B32;
    xieTypFloat		constant1 B32;
    xieTypFloat		constant2 B32;
    xieTypFloat		alphaConst B32;
} xieFloBlend;

typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
    xieTypPhototag	src1 B16;
    xieTypPhototag	src2 B16;
    INT32		domainOffsetX B32;
    INT32		domainOffsetY B32;
    xieTypPhototag	domainPhototag B16;		
#if defined(__cplusplus) || defined(c_plusplus)
    xieTypCompareOp	c_operator;
#else
    xieTypCompareOp	operator;
#endif
    BOOL		combine;
    xieTypFloat		constant0 B32;
    xieTypFloat		constant1 B32;
    xieTypFloat		constant2 B32;
    CARD8		bandMask;
    CARD8		pad[3];
} xieFloCompare;

typedef struct {
    CARD16			elemType B16;
    CARD16			elemLength B16;
    xieTypPhototag		src B16;
    CARD16			pad B16;
    CARD32			levels0 B32;
    CARD32			levels1 B32;
    CARD32			levels2 B32;
    xieTypConstrainTechnique	constrain B16;
    CARD16			lenParams B16;
    /* Technique dependent constrain params */
} xieFloConstrain;

typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
    xieTypPhototag	src B16;
#if defined(__cplusplus) || defined(c_plusplus)
    xieTypDataClass	c_class;
#else
    xieTypDataClass	class;
#endif
    CARD8		precision;
    Colormap		colormap B32;
} xieFloConvertFromIndex;

typedef struct {
    CARD16			   elemType B16;
    CARD16			   elemLength B16;
    xieTypPhototag		   src B16;
    CARD16			   pad B16;
    xieTypConvertFromRGBTechnique  convert B16;
    CARD16			   lenParams B16;
    /* Technique dependent conversion params */
} xieFloConvertFromRGB;

typedef struct {
    CARD16			elemType B16;
    CARD16			elemLength B16;
    xieTypPhototag		src B16;
    BOOL			notify;
    CARD8			pad;
    Colormap			colormap B32;
    xieTypColorList		colorList B32;
    xieTypColorAllocTechnique	colorAlloc B16;
    CARD16			lenParams B16;
    /* Technique dependent color alloc params */
} xieFloConvertToIndex;

typedef struct {
    CARD16			elemType B16;
    CARD16			elemLength B16;
    xieTypPhototag		src B16;
    CARD16			pad B16;
    xieTypConvertToRGBTechnique	convert B16;
    CARD16			lenParams B16;
    /* Technique dependent conversion params */
} xieFloConvertToRGB;

typedef struct {
    CARD16			elemType B16;
    CARD16			elemLength B16;
    xieTypPhototag		src B16;
    CARD16			pad B16;
    INT32			domainOffsetX B32;
    INT32			domainOffsetY B32;
    xieTypPhototag		domainPhototag B16;		
    CARD8			bandMask;
    CARD8			kernelSize;
    xieTypConvolveTechnique	convolve B16;
    CARD16			lenParams B16;
    /* LISTofFloat (kernelSize^2) */
    /* Technique dependent convolve params */
} xieFloConvolve;

typedef struct {
    CARD16			elemType B16;
    CARD16			elemLength B16;
    xieTypPhototag		src B16;
    CARD8			bandMask;
    CARD8			pad;
    CARD32			levels0 B32;
    CARD32			levels1 B32;
    CARD32			levels2 B32;
    xieTypDitherTechnique	dither B16;
    CARD16			lenParams B16;
    /* Technique dependent dither params */
} xieFloDither;

typedef struct {
    CARD16			elemType B16;
    CARD16			elemLength B16;
    xieTypPhototag 		src B16;
    CARD8			bandMask;
    CARD8			pad;
    CARD32			width B32;
    CARD32			height B32;
    xieTypFloat			a B32;
    xieTypFloat			b B32;
    xieTypFloat			c B32;
    xieTypFloat			d B32;
    xieTypFloat			tx B32;
    xieTypFloat			ty B32;
    xieTypFloat			constant0 B32;
    xieTypFloat			constant1 B32;
    xieTypFloat			constant2 B32;
    xieTypGeometryTechnique	sample B16;
    CARD16			lenParams B16;
    /* Technique dependent sample params */
} xieFloGeometry;

typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
    xieTypPhototag	src1 B16;
    xieTypPhototag	src2 B16;
    INT32		domainOffsetX B32;
    INT32		domainOffsetY B32;
    xieTypPhototag	domainPhototag B16;		
#if defined(__cplusplus) || defined(c_plusplus)
    CARD8		c_operator;
#else
    CARD8		operator;
#endif
    CARD8		bandMask;
    xieTypFloat		constant0 B32;
    xieTypFloat		constant1 B32;
    xieTypFloat		constant2 B32;
} xieFloLogical;

typedef struct {
    CARD16			elemType B16;
    CARD16			elemLength B16;
    xieTypPhototag		src B16;
    CARD16			pad1 B16;
    INT32			domainOffsetX B32;
    INT32			domainOffsetY B32;
    xieTypPhototag		domainPhototag B16;		
    CARD16			pad2 B16;
    xieTypHistogramShape	shape B16;
    CARD16			lenParams B16;
    /* Technique dependent shape params */
} xieFloMatchHistogram;

typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
    xieTypPhototag	src B16;
    CARD16		pad B16;
    INT32		domainOffsetX B32;
    INT32		domainOffsetY B32;
    xieTypPhototag	domainPhototag B16;		
#if defined(__cplusplus) || defined(c_plusplus)
    xieTypMathOp	c_operator;
#else
    xieTypMathOp	operator;
#endif
    CARD8		bandMask;
} xieFloMath;

typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
    CARD16		numTiles B16;
    CARD16		pad B16;
    CARD32		width B32;
    CARD32		height B32;
    xieTypFloat		constant0 B32;
    xieTypFloat		constant1 B32;
    xieTypFloat		constant2 B32;
    /* LISTofTile (numTiles) */
} xieFloPasteUp;

typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
    xieTypPhototag	src B16;
    xieTypPhototag	lut B16;
    INT32		domainOffsetX B32;
    INT32		domainOffsetY B32;
    xieTypPhototag	domainPhototag B16;		
    CARD8		bandMask;
    CARD8		pad;
} xieFloPoint;

typedef struct {
    CARD16			elemType B16;
    CARD16			elemLength B16;
    xieTypPhototag		src B16;
    CARD16			pad B16;
} xieFloUnconstrain;


/*
 * Export Elements
 */
typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
    xieTypPhototag	src B16;
    xieTypExportNotify	notify;
    CARD8		pad1;
    INT32		domainOffsetX B32;
    INT32		domainOffsetY B32;
    xieTypPhototag	domainPhototag B16;		
    CARD16		pad2 B16;
} xieFloExportClientHistogram;

typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
    xieTypPhototag	src B16;
    xieTypExportNotify	notify;
    xieTypOrientation	bandOrder;
    CARD32		start0  B32;
    CARD32		start1  B32;
    CARD32		start2  B32;
    CARD32		length0 B32;
    CARD32		length1 B32;
    CARD32		length2 B32;
} xieFloExportClientLUT;

typedef struct {
    CARD16			elemType B16;
    CARD16			elemLength B16;
    xieTypPhototag		src B16;
    xieTypExportNotify		notify;
    CARD8			pad;
    xieTypEncodeTechnique	encodeTechnique B16;
    CARD16			lenParams B16;
    /* Technique dependent encode params */
} xieFloExportClientPhoto;

typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
    xieTypPhototag	src B16;
    xieTypExportNotify	notify;
    CARD8		pad;
} xieFloExportClientROI;

typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
    xieTypPhototag	src B16;
    INT16		dstX B16;
    INT16		dstY B16;
    CARD16		pad B16;
    Drawable		drawable B32;
    GContext		gc B32;
} xieFloExportDrawable;

typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
    xieTypPhototag	src B16;
    INT16		dstX B16;
    INT16		dstY B16;
    CARD16		pad B16;
    Drawable		drawable B32;
    GContext		gc B32;
} xieFloExportDrawablePlane;

typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
    xieTypPhototag	src B16;
    CARD8		merge;
    CARD8		pad;
    xieTypLUT		lut B32;
    CARD32		start0 B32;
    CARD32		start1 B32;
    CARD32		start2 B32;
} xieFloExportLUT;
 
typedef struct {
    CARD16			elemType B16;
    CARD16			elemLength B16;
    xieTypPhototag		src B16;
    CARD16			pad B16;
    xieTypPhotomap		photomap B32;
    xieTypEncodeTechnique	encodeTechnique B16;
    CARD16			lenParams B16;
    /* Technique dependent encode params */
} xieFloExportPhotomap;

typedef struct {
    CARD16		elemType B16;
    CARD16		elemLength B16;
    xieTypPhototag	src B16;
    CARD16		pad B16;
    xieTypROI		roi B32;
} xieFloExportROI;


/*
 * Technique Parameters
 */

typedef struct {
    xieTypFloat		inputLow0   B32;
    xieTypFloat		inputLow1   B32;
    xieTypFloat		inputLow2   B32;
    xieTypFloat		inputHigh0  B32;
    xieTypFloat		inputHigh1  B32;
    xieTypFloat		inputHigh2  B32;
    CARD32		outputLow0  B32;
    CARD32		outputLow1  B32;
    CARD32		outputLow2  B32;
    CARD32		outputHigh0 B32;
    CARD32		outputHigh1 B32;
    CARD32		outputHigh2 B32;
} xieTecClipScale;

typedef struct {
    CARD32		fill B32;
} xieTecColorAllocAll;

typedef struct {
    xieTypFloat		matchLimit B32;
    xieTypFloat		grayLimit B32;
} xieTecColorAllocMatch;

typedef struct {
    CARD32		maxCells B32;
} xieTecColorAllocRequantize;

typedef struct {
    xieTypFloat			matrix00 B32;
    xieTypFloat			matrix01 B32;
    xieTypFloat			matrix02 B32;
    xieTypFloat			matrix10 B32;
    xieTypFloat			matrix11 B32;
    xieTypFloat			matrix12 B32;
    xieTypFloat			matrix20 B32;
    xieTypFloat			matrix21 B32;
    xieTypFloat			matrix22 B32;
    xieTypWhiteAdjustTechnique	whiteAdjusted B16;
    CARD16			lenParams B16;
    /* Technique dependent white params */
} xieTecRGBToCIELab, xieTecRGBToCIEXYZ;

typedef struct {
    CARD32		levels0 B32;
    CARD32		levels1 B32;
    CARD32		levels2 B32;
    xieTypFloat		lumaRed B32;
    xieTypFloat		lumaGreen B32;
    xieTypFloat		lumaBlue B32;
    xieTypFloat		bias0 B32;
    xieTypFloat		bias1 B32;
    xieTypFloat		bias2 B32;
} xieTecRGBToYCbCr;

typedef struct {
    CARD32		levels0 B32;
    CARD32		levels1 B32;
    CARD32		levels2 B32;
    xieTypFloat		lumaRed B32;
    xieTypFloat		lumaGreen B32;
    xieTypFloat		lumaBlue B32;
    xieTypFloat		scale B32;
} xieTecRGBToYCC;

typedef struct {
    xieTypFloat			matrix00 B32;
    xieTypFloat			matrix01 B32;
    xieTypFloat			matrix02 B32;
    xieTypFloat			matrix10 B32;
    xieTypFloat			matrix11 B32;
    xieTypFloat			matrix12 B32;
    xieTypFloat			matrix20 B32;
    xieTypFloat			matrix21 B32;
    xieTypFloat			matrix22 B32;
    xieTypWhiteAdjustTechnique	whiteAdjusted B16;
    CARD16			lenWhiteParams B16;
    xieTypGamutTechnique	gamutCompress B16;
    CARD16			lenGamutParams B16;
    /* Technique dependent white params */
    /* Technique dependent gamut params */
} xieTecCIELabToRGB, xieTecCIEXYZToRGB;

typedef struct {
    CARD32			levels0 B32;
    CARD32			levels1 B32;
    CARD32			levels2 B32;
    xieTypFloat			lumaRed B32;
    xieTypFloat			lumaGreen B32;
    xieTypFloat			lumaBlue B32;
    xieTypFloat			bias0 B32;
    xieTypFloat			bias1 B32;
    xieTypFloat			bias2 B32;
    xieTypGamutTechnique	gamutCompress B16;
    CARD16			lenGamutParams B16;
    /* Technique dependent gamut params */
} xieTecYCbCrToRGB;

typedef struct {
    CARD32			levels0 B32;
    CARD32			levels1 B32;
    CARD32			levels2 B32;
    xieTypFloat			lumaRed B32;
    xieTypFloat			lumaGreen B32;
    xieTypFloat			lumaBlue B32;
    xieTypFloat			scale B32;
    xieTypGamutTechnique	gamutCompress B16;
    CARD16			lenGamutParams B16;
    /* Technique dependent gamut params */
} xieTecYCCToRGB;

typedef struct {
    xieTypFloat		constant0 B32;
    xieTypFloat		constant1 B32;
    xieTypFloat		constant2 B32;
} xieTecConvolveConstant;

typedef struct {
    xieTypOrientation	fillOrder;
    xieTypOrientation	pixelOrder;
    CARD8		pixelStride;
    CARD8		leftPad;
    CARD8		scanlinePad;
    CARD8		pad[3];
} xieTecDecodeUncompressedSingle;

typedef struct {
    CARD8		leftPad[3];
    xieTypOrientation	fillOrder;
    CARD8		pixelStride[3];
    xieTypOrientation	pixelOrder;
    CARD8		scanlinePad[3];
    xieTypOrientation	bandOrder;
    xieTypInterleave	interleave;
    CARD8		pad[3];
} xieTecDecodeUncompressedTriple;

typedef struct {
    xieTypOrientation	encodedOrder;
    BOOL		normal;
    BOOL		radiometric;
    CARD8		pad;
} xieTecDecodeG31D, xieTecDecodeG32D, xieTecDecodeG42D,
  xieTecDecodeTIFF2;

typedef struct {
    xieTypOrientation	encodedOrder;
    BOOL		normal;
    CARD16		pad B16;
} xieTecDecodeTIFFPackBits;

typedef struct {
    xieTypInterleave	interleave;
    xieTypOrientation	bandOrder;
    BOOL		upSample;
    CARD8		pad;
} xieTecDecodeJPEGBaseline;

typedef struct {
    xieTypInterleave	interleave;
    xieTypOrientation	bandOrder;
    CARD16		pad B16;
} xieTecDecodeJPEGLossless;

typedef struct {
    CARD8	thresholdOrder;
    CARD8	pad[3];
} xieTecDitherOrdered;

typedef struct {
    CARD8		preference;
    CARD8		pad[3];
} xieTecEncodeServerChoice;

typedef struct {
    xieTypOrientation	fillOrder;
    xieTypOrientation	pixelOrder;
    CARD8		pixelStride;
    CARD8		scanlinePad;
} xieTecEncodeUncompressedSingle;

typedef struct {
    CARD8		pixelStride[3];
    xieTypOrientation	pixelOrder;
    CARD8		scanlinePad[3];
    xieTypOrientation	fillOrder;
    xieTypOrientation	bandOrder;
    xieTypInterleave	interleave;
    CARD16		pad B16;
} xieTecEncodeUncompressedTriple;

typedef struct {
    xieTypOrientation	encodedOrder;
    BOOL		alignEol;
    BOOL		radiometric;
    CARD8		pad;
} xieTecEncodeG31D;

typedef struct {
    xieTypOrientation	encodedOrder;
    BOOL		alignEol;
    BOOL		radiometric;
    BOOL		uncompressed;
    CARD32		kFactor B32;
} xieTecEncodeG32D;

typedef struct {
    xieTypOrientation	encodedOrder;
    BOOL		radiometric;
    BOOL		uncompressed;
    CARD8		pad;
} xieTecEncodeG42D;

typedef struct {
    xieTypInterleave	interleave;
    xieTypOrientation	bandOrder;
    CARD8		horizontalSamples[3];
    CARD8		verticalSamples[3];
    CARD16		lenQtable  B16;	/* multiple of 4 */
    CARD16		lenACtable B16;	/* multiple of 4 */
    CARD16		lenDCtable B16;	/* multiple of 4 */
    CARD16		pad B16;
    /* LISTofCARD8 (Qtable)  */
    /* LISTofCARD8 (ACtable) */
    /* LISTofCARD8 (DCtable) */
} xieTecEncodeJPEGBaseline;

typedef struct {
    xieTypInterleave	interleave;
    xieTypOrientation	bandOrder;
    CARD16		lenTable B16;	/* multiple of 4 */
    CARD8		predictor[3];
    CARD8		pad;
    /* LISTofCARD8 (table) */
} xieTecEncodeJPEGLossless;

typedef struct {
    xieTypOrientation	encodedOrder;
    BOOL		radiometric;
    CARD16		pad B16;
} xieTecEncodeTIFF2;

typedef struct {
    xieTypOrientation	encodedOrder;
    CARD8		pad[3];
} xieTecEncodeTIFFPackBits;

typedef struct {
    INT16	simple B16;
    CARD16	pad B16;
} xieTecGeomAntialiasByArea;

typedef struct {
    INT16	kernelSize B16;
    CARD16	pad B16;
} xieTecGeomAntialiasByLowpass;

typedef struct {
    CARD8	radius;
    BOOL	simple;
    CARD16	pad B16;
    xieTypFloat	sigma B32;
    xieTypFloat	normalize B32;
} xieTecGeomGaussian;

typedef struct {
    CARD8	modify;
    CARD8	pad[3];
} xieTecGeomNearestNeighbor;

typedef struct {
    xieTypFloat		mean B32;
    xieTypFloat		sigma B32;
} xieTecHistogramGaussian;

typedef struct {
    BOOL		shapeFactor;
    CARD8		pad[3];
    xieTypFloat		constant B32;
} xieTecHistogramHyperbolic;

typedef struct {
    xieTypFloat		whitePoint0 B32;
    xieTypFloat		whitePoint1 B32;
    xieTypFloat		whitePoint2 B32;
} xieTecWhiteAdjustCIELabShift;


/*
 * SIZEOF values
 */
#define sz_xieTypAlignment			1
#define sz_xieTypArithmeticOp			1
#define sz_xieTypColorAllocTechnique		2
#define sz_xieTypColorList			4
#define sz_xieTypCompareOp			1
#define sz_xieTypConstant			12
#define sz_xieTypConstrainTechnique		2
#define sz_xieTypConvertFromRGBTechnique	2
#define sz_xieTypConvertToRGBTechnique		2
#define sz_xieTypConvolveTechnique		2
#define sz_xieTypDataClass			1
#define sz_xieTypDataType			1
#define sz_xieTypDecodeTechnique		2
#define sz_xieTypDitherTechnique		2
#define sz_xieTypEncodeTechnique		2
#define sz_xieTypPhotospace			4
#define sz_xieTypPhotoflo			4
#define sz_xieTypExecutable			8
#define sz_xieTypExportNotify			1
#define sz_xieTypExportState			1
#define sz_xieTypFloat				4
#define sz_xieTypGamutTechnique			2
#define sz_xieTypGeometryTechnique		2
#define sz_xieTypHistogramData			8
#define sz_xieTypHistogramShape			2
#define sz_xieTypInterleave			1
#define sz_xieTypLevels				12
#define sz_xieTypLUT				4
#define sz_xieTypMathOp				1
#define sz_xieTypMatrix				36
#define sz_xieTypOrientation			1
#define sz_xieTypPhotofloOutcome		1
#define sz_xieTypPhotofloState			1
#define sz_xieTypPhotomap			4
#define sz_xieTypPhototag			2
#define sz_xieTypProcessDomain			12
#define sz_xieTypRectangle			16
#define sz_xieTypROI				4
#define sz_xieTypServiceClass			1
#define sz_xieTypTechniqueGroup			1
#define sz_xieTypTechniqueRec			8
#define sz_xieTypTile				12
#define sz_xieTypTripleofCARD8			3
#define sz_xieTypTripleofCARD16			6
#define sz_xieTypTripleofCARD32			12
#define sz_xieTypWhiteAdjustTechnique		2
#define sz_xieFloImportClientLUT		32
#define sz_xieFloImportClientPhoto		48
#define sz_xieFloImportClientROI		8
#define sz_xieFloImportDrawable			24
#define sz_xieFloImportDrawablePlane		28
#define sz_xieFloImportLUT			8
#define sz_xieFloImportPhotomap			12
#define sz_xieFloImportROI			8
#define sz_xieFloArithmetic			32
#define sz_xieFloBandCombine			12
#define sz_xieFloBandExtract			28
#define sz_xieFloBandSelect			8
#define sz_xieFloBlend				40
#define sz_xieFloCompare			36
#define sz_xieFloConstrain			24
#define sz_xieFloConvertFromIndex		12
#define sz_xieFloConvertFromRGB			12
#define sz_xieFloConvertToIndex			20
#define sz_xieFloConvertToRGB			12
#define sz_xieFloConvolve			24
#define sz_xieFloDither				24
#define sz_xieFloGeometry			56
#define sz_xieFloLogical			32
#define sz_xieFloMatchHistogram			24
#define sz_xieFloMath				20
#define sz_xieFloPasteUp			28
#define sz_xieFloPoint				20
#define sz_xieFloUnconstrain			8
#define sz_xieFloExportClientHistogram		20
#define sz_xieFloExportClientLUT		32
#define sz_xieFloExportClientPhoto		12
#define sz_xieFloExportClientROI		8
#define sz_xieFloExportDrawable			20
#define sz_xieFloExportDrawablePlane		20
#define sz_xieFloExportLUT			24
#define sz_xieFloExportPhotomap			16
#define sz_xieFloExportROI			12
#define sz_xieTecColorAllocAll			4
#define sz_xieTecColorAllocMatch		8
#define sz_xieTecColorAllocRequantize		4
#define sz_xieTecClipScale			48
#define sz_xieTecHardClip			0
#define sz_xieTecRGBToCIELab			40
#define sz_xieTecRGBToCIEXYZ			40
#define sz_xieTecRGBToYCbCr			36
#define sz_xieTecRGBToYCC			28
#define sz_xieTecYCbCrToRGB			40
#define sz_xieTecYCCToRGB			32
#define sz_xieTecCIELabToRGB			44
#define sz_xieTecCIEXYZToRGB			44
#define sz_xieTecConvolveConstant		12
#define sz_xieTecConvolveReplicate		0
#define sz_xieTecDecodeUncompressedSingle	8
#define sz_xieTecDecodeUncompressedTriple	16
#define sz_xieTecDecodeG31D			4
#define sz_xieTecDecodeG32D			4
#define sz_xieTecDecodeG42D			4
#define sz_xieTecDecodeTIFF2			4
#define sz_xieTecDecodeTIFFPackBits		4
#define sz_xieTecDecodeJPEGBaseline		4
#define sz_xieTecDecodeJPEGLossless		4
#define sz_xieTecDitherOrdered			4
#define sz_xieTecDitherErrorDiffusion		4
#define sz_xieTecEncodeServerChoice		4
#define sz_xieTecEncodeUncompressedSingle	4
#define sz_xieTecEncodeUncompressedTriple	12
#define sz_xieTecEncodeG31D			4
#define sz_xieTecEncodeG32D			8
#define sz_xieTecEncodeG42D			4
#define sz_xieTecEncodeJPEGBaseline		16
#define sz_xieTecEncodeJPEGLossless		8
#define sz_xieTecEncodeTIFF2			4
#define sz_xieTecEncodeTIFFPackBits		4
#define sz_xieTecGamutNone			0
#define sz_xieTecGamutClipRGB			0
#define sz_xieTecGeomAntialias			0
#define sz_xieTecGeomAntialiasByArea		4
#define sz_xieTecGeomAntialiasByLowpass		4
#define sz_xieTecGeomBilinearInterpolation	0
#define sz_xieTecGeomGaussian			12
#define sz_xieTecGeomNearestNeighbor		4
#define sz_xieTecHistogramFlat			0
#define sz_xieTecHistogramGaussian		8
#define sz_xieTecHistogramHyperbolic		8
#define sz_xieTecWhiteAdjustNone		0
#define sz_xieTecWhiteAdjustCIELabShift		12

#undef Drawable
#undef Colormap
#undef GContext

#endif /* _XIEPROTOST_H_ */
