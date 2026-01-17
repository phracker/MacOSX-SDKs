/*
 * tkMacOSX.h --
 *
 *	Declarations of Macintosh specific exported variables and procedures.
 *
 * Copyright (c) 1995-1997 Sun Microsystems, Inc.
 * Copyright 2001, Apple Computer, Inc.
 * Copyright (c) 2005-2007 Daniel A. Steffen <das@users.sourceforge.net>
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 * RCS: @(#) $Id: tkMacOSX.h,v 1.2.2.3 2007/04/29 02:26:47 das Exp $
 */

#ifndef _TKMAC
#define _TKMAC

#ifndef _TK
#include "tk.h"
#endif

#include <Carbon/Carbon.h>

/*
 * Structures and function types for handling Netscape-type in process
 * embedding where Tk does not control the top-level
 */

typedef int (Tk_MacOSXEmbedRegisterWinProc) (int winID, Tk_Window window);
typedef GWorldPtr (Tk_MacOSXEmbedGetGrafPortProc) (Tk_Window window);
typedef int (Tk_MacOSXEmbedMakeContainerExistProc) (Tk_Window window);
typedef void (Tk_MacOSXEmbedGetClipProc) (Tk_Window window, RgnHandle rgn);
typedef void (Tk_MacOSXEmbedGetOffsetInParentProc) (Tk_Window window, Point *ulCorner);

#include "tkPlatDecls.h"

#endif /* _TKMAC */
