/*
 * PSres.h
 *
 * (c) Copyright 1991-1994 Adobe Systems Incorporated.
 * All rights reserved.
 * 
 * Permission to use, copy, modify, distribute, and sublicense this software
 * and its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notices appear in all copies and that
 * both those copyright notices and this permission notice appear in
 * supporting documentation and that the name of Adobe Systems Incorporated
 * not be used in advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.  No trademark license
 * to use the Adobe trademarks is hereby granted.  If the Adobe trademark
 * "Display PostScript"(tm) is used to describe this software, its
 * functionality or for any other purpose, such use shall be limited to a
 * statement that this software works in conjunction with the Display
 * PostScript system.  Proper trademark attribution to reflect Adobe's
 * ownership of the trademark shall be given whenever any such reference to
 * the Display PostScript system is made.
 * 
 * ADOBE MAKES NO REPRESENTATIONS ABOUT THE SUITABILITY OF THE SOFTWARE FOR
 * ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
 * ADOBE DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON- INFRINGEMENT OF THIRD PARTY RIGHTS.  IN NO EVENT SHALL ADOBE BE LIABLE
 * TO YOU OR ANY OTHER PARTY FOR ANY SPECIAL, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE, STRICT LIABILITY OR ANY OTHER ACTION ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.  ADOBE WILL NOT
 * PROVIDE ANY TRAINING OR OTHER SUPPORT FOR THE SOFTWARE.
 * 
 * Adobe, PostScript, and Display PostScript are trademarks of Adobe Systems
 * Incorporated which may be registered in certain jurisdictions
 * 
 * Author:  Adobe Systems Incorporated
 */
/* $XFree86: xc/include/DPS/PSres.h,v 1.2 2000/06/07 22:02:55 tsi Exp $ */

#ifndef _PSres_h
#define _PSres_h

extern char *PSResFontOutline, *PSResFontPrebuilt, *PSResFontAFM,
	*PSResFontBDF, *PSResFontFamily, *PSResFontBDFSizes,
	*PSResForm, *PSResPattern, *PSResEncoding, *PSResProcSet;

typedef enum {PSSaveReturnValues, PSSaveByType, PSSaveEverything}
	PSResourceSavePolicy;

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern int ListPSResourceFiles(char *psResourcePathOverride,
			       char *defaultPath,
			       char *resourceType,
			       char *resourceName,
			       char ***resourceNamesReturn,
			       char ***resourceFilesReturn);

extern int ListPSResourceTypes(char *psResourcePathOverride,
			       char *defaultPath,
			       char ***resourceTypeReturn);

extern void FreePSResourceStorage(int everything);

extern void SetPSResourcePolicy(PSResourceSavePolicy policy,
				int willList,
				char **resourceTypes);

typedef int (*PSResourceEnumerator)(char *resourceType,
				    char *resourceName,
				    char *resourceFile,
				    char *privateData);

extern void EnumeratePSResourceFiles(char *psResourcePathOverride,
				     char *defaultPath,
				     char *resourceType,
				     char *resourceName,
				     PSResourceEnumerator enumerator,
				     char *privateData);

extern int CheckPSResourceTime(char *psResourcePathOverride,
			       char *defaultPath);

typedef char *(*PSResMallocProc)(int size);

typedef char *(*PSResReallocProc)(char *ptr,
				  int size);

typedef void (*PSResFreeProc)(char *ptr);

typedef void (*PSResFileWarningHandlerProc)(char *fileNamem, char *extraInfo);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

extern PSResMallocProc PSResMalloc;

extern PSResReallocProc PSResRealloc;

extern PSResFreeProc PSResFree;

extern PSResFileWarningHandlerProc PSResFileWarningHandler;

#endif /* _PSres_h */
