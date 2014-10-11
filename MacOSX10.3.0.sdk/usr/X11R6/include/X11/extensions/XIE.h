/* $Xorg: XIE.h,v 1.4 2001/02/09 02:03:23 xorgcvs Exp $ */
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

#ifndef _XIE_H_
#define _XIE_H_


/* Extension Name and version number */

#define xieExtName		"XIE"

#define xieMajorVersion		5
#define xieMinorVersion		0
#define xieEarliestMinorVersion	0
#define xieLatestMinorVersion	0


/* ServiceClass */

#ifdef  XIE_DIS
#define XIE_FULL 0
#else
#define XIE_FULL 1
#endif

#define xieValFull		1
#define xieValDIS		2


/* Limits */

#define xieValMaxBands		3


/* Alignment */

#define xieValAlignable		1
#define xieValArbitrary		2


/* ArithmeticOp */

#define xieValAdd		1
#define xieValSub		2
#define xieValSubRev		3
#define xieValMul		4
#define xieValDiv		5
#define xieValDivRev		6
#define xieValMin		7
#define xieValMax		8
#define xieValGamma		9


/* ColorAllocTechnique */

#define xieValColorAllocDefault		0
#define xieValColorAllocAll		2
#define xieValColorAllocMatch		4
#define xieValColorAllocRequantize	6


/* Colorspace conversions */

#define xieValRGBToCIELab	2
#define xieValRGBToCIEXYZ	4
#define xieValRGBToYCbCr	6
#define xieValRGBToYCC		8

#define xieValCIELabToRGB	2
#define xieValCIEXYZToRGB	4
#define xieValYCbCrToRGB	6
#define xieValYCCToRGB		8


/* CompareOp */

#define xieValLT	1
#define xieValLE	2
#define xieValEQ	3
#define xieValNE	4
#define xieValGT	5
#define xieValGE	6


/* ConstrainTechnique */

#define xieValConstrainClipScale	2
#define xieValConstrainHardClip		4


/* ConvolveTechnique */

#define xieValConvolveDefault		0
#define xieValConvolveConstant		2
#define xieValConvolveReplicate		4


/* DataClass */

#define xieValSingleBand	1
#define xieValTripleBand	2

/* DataType */

#define xieValConstrained	1
#define xieValUnconstrained	2


/* DecodeTechnique */

#define xieValDecodeUncompressedSingle	2     	/* bitonal & grayscale */
#define xieValDecodeUncompressedTriple	3     	/* color */
#define xieValDecodeG31D		4     	/* FAX */
#define xieValDecodeG32D		6     	/* FAX */
#define xieValDecodeG42D		8     	/* FAX */
#define xieValDecodeJPEGBaseline	10     	/* grayscale & color */
#define xieValDecodeJPEGLossless	12     	/* grayscale & color */
#define xieValDecodeTIFF2		14     	/* TIFF modified G31D */
#define xieValDecodeTIFFPackBits	16     	/* TIFF APPLE FORMAT */


/* DitherTechnique */

#define xieValDitherDefault		0
#define xieValDitherErrorDiffusion	2
#define xieValDitherOrdered		4


/* EncodeTechnique */

#define xieValEncodeServerChoice	1	/* (to photomaps) */
#define xieValEncodeUncompressedSingle	2     	/* bitonal & grayscale */
#define xieValEncodeUncompressedTriple	3     	/* color */
#define xieValEncodeG31D		4    	/* FAX */
#define xieValEncodeG32D		6     	/* FAX */
#define xieValEncodeG42D		8     	/* FAX */
#define xieValEncodeJPEGBaseline	10     	/* grayscale & color */
#define xieValEncodeJPEGLossless	12     	/* grayscale & color */
#define xieValEncodeTIFF2		14     	/* TIFF modified G31D */
#define xieValEncodeTIFFPackBits	16     	/* TIFF APPLE FORMAT */

/* ServerChoice preference hints */

#define xieValPreferDefault		0
#define xieValPreferSpace		1
#define xieValPreferTime		2

/* JPEG-Lossless predictor */

#define xieValPredictorNone	0
#define xieValPredictorA	1
#define xieValPredictorB	2
#define xieValPredictorC	3
#define xieValPredictorABC	4
#define xieValPredictorABC2	5
#define xieValPredictorBAC2	6
#define xieValPredictorAB2	7


/* ExportNotify */

#define xieValDisable		1
#define xieValFirstData		2
#define xieValNewData		3


/* ExportState */

#define xieValExportDone	1
#define xieValExportMore	2
#define xieValExportEmpty	3
#define xieValExportError	4


/* GamutTechnique */

#define xieValGamutDefault	0
#define xieValGamutNone		1
#define xieValGamutClipRGB	2


/* GeometryTechnique */

#define xieValGeomDefault		0
#define xieValGeomAntialias		2
#define xieValGeomAntialiasByArea	4
#define xieValGeomAntialiasByLPF	6
#define xieValGeomBilinearInterp	8
#define xieValGeomGaussian		10
#define xieValGeomNearestNeighbor	12


/* NearestNeighbor modify */

#define xieValFavorDown		1
#define xieValFavorUp		2
#define xieValRoundNW		3
#define xieValRoundNE		4
#define xieValRoundSE		5
#define xieValRoundSW		6


/* HistogramShape */

#define	xieValHistogramFlat		2
#define	xieValHistogramGaussian		4
#define	xieValHistogramHyperbolic	6


/* Interleave */

#define xieValBandByPixel	1
#define xieValBandByPlane	2


/* MathOp */

#define xieValExp	1
#define xieValLn	2
#define xieValLog2	3
#define xieValLog10	4
#define xieValSquare	5
#define xieValSqrt	6


/* Orientation */

#define xieValLSFirst		1
#define xieValMSFirst		2


/* PhotofloOutcome */

#define xieValFloSuccess	1
#define xieValFloAbort		2
#define xieValFloError		3


/* PhotofloState */

#define xieValInactive		1
#define xieValActive		2
#define xieValNonexistent	3


/* TechniqueGroup */

#define	xieValDefault		0
#define	xieValAll		1
#define	xieValColorAlloc	2
#define	xieValConstrain		4
#define	xieValConvertFromRGB	6
#define	xieValConvertToRGB	8
#define	xieValConvolve		10
#define	xieValDecode		12
#define	xieValDither		14
#define	xieValEncode		16
#define	xieValGamut		18
#define	xieValGeometry		20
#define	xieValHistogram		22
#define	xieValWhiteAdjust	24

#define xieValMaxTechGroup	24


/* WhiteAdjustTechnique */

#define	xieValWhiteAdjustDefault	0
#define	xieValWhiteAdjustNone		1
#define	xieValWhiteAdjustCIELabShift	2


/* Photoflo elements */

#define xieElemImportClientLUT		1
#define xieElemImportClientPhoto	2
#define xieElemImportClientROI		3
#define xieElemImportDrawable		4
#define xieElemImportDrawablePlane	5
#define xieElemImportLUT		6
#define xieElemImportPhotomap		7
#define xieElemImportROI		8
#define xieElemArithmetic		9
#define xieElemBandCombine		10
#define xieElemBandExtract		11
#define xieElemBandSelect		12
#define xieElemBlend			13
#define xieElemCompare			14
#define xieElemConstrain		15
#define xieElemConvertFromIndex		16
#define xieElemConvertFromRGB		17
#define xieElemConvertToIndex		18
#define xieElemConvertToRGB		19
#define xieElemConvolve			20
#define xieElemDither			21
#define xieElemGeometry			22
#define xieElemLogical			23
#define xieElemMatchHistogram		24
#define xieElemMath			25
#define xieElemPasteUp			26
#define xieElemPoint			27
#define xieElemUnconstrain		28
#define xieElemExportClientHistogram	29
#define xieElemExportClientLUT		30
#define xieElemExportClientPhoto	31
#define xieElemExportClientROI		32
#define xieElemExportDrawable		33
#define xieElemExportDrawablePlane	34
#define xieElemExportLUT		35
#define xieElemExportPhotomap		36
#define xieElemExportROI		37

#define xieMaxElem			37


/* Event Codes */

#define xieEvnNoColorAlloc		0
#define xieEvnNoDecodeNotify		1
#define xieEvnNoExportAvailable		2
#define xieEvnNoImportObscured		3
#define xieEvnNoPhotofloDone		4

#define xieNumEvents			5


/* Error Codes */

#define xieErrNoColorList	0
#define xieErrNoLUT		1
#define xieErrNoPhotoflo	2
#define xieErrNoPhotomap	3
#define xieErrNoPhotospace	4
#define xieErrNoROI		5
#define xieErrNoFlo		6

#define xieNumErrors		7


/* Flo Error Codes */

#define xieErrNoFloAccess	   1
#define xieErrNoFloAlloc	   2
#define xieErrNoFloColormap	   3
#define xieErrNoFloColorList	   4
#define xieErrNoFloDomain	   5
#define xieErrNoFloDrawable	   6
#define xieErrNoFloElement	   7
#define xieErrNoFloGC		   8
#define xieErrNoFloID		   9
#define xieErrNoFloLength	  10
#define xieErrNoFloLUT		  11
#define xieErrNoFloMatch	  12
#define xieErrNoFloOperator	  13
#define xieErrNoFloPhotomap	  14
#define xieErrNoFloROI		  15
#define xieErrNoFloSource	  16
#define xieErrNoFloTechnique	  17
#define xieErrNoFloValue	  18
#define xieErrNoFloImplementation 19

#define xieNumFloErrors		  19

#endif /* _XIE_H_ */
