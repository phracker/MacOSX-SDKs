/*
 * Copyright 1991 by OMRON Corporation
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name OMRON not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  OMRON make no representations
 * about the suitability of this software for any purpose.  It is provided
 * "as is" without express or implied warranty.
 *
 * OMRON DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL OMRON BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTUOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 *      Author: Li Yuhong	 OMRON Corporation
 */


/***********************************************************

Copyright 1987, 1988, 1991, 1994, 1998  The Open Group

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


Copyright 1987, 1988 by Digital Equipment Corporation, Maynard, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*
 * MultiSrcP.h - Private Header for Multi Text Source.
 *
 * This is the private header file for the Multi Text Source.
 * It is intended to be used with the Text widget, the simplest way to use
 * this text source is to use the MultiText Object.
 *
 * Date:    June 29, 1989
 *
 * By:      Chris D. Peterson
 *          MIT X Consortium 
 *          kit@expo.lcs.mit.edu
 */

/* 
 * This file was changed from AsciiSrcP.h.
 *
 * By Li Yuhong, Sept. 18, 1990
 */

#ifndef _XawMultiSrcP_h
#define _XawMultiSrcP_h

#include <X11/Xfuncproto.h>
#include <X11/Xaw/TextSrcP.h>
#include <X11/Xaw/MultiSrc.h>

#ifdef L_tmpnam
#define TMPSIZ L_tmpnam
#else
#ifdef PATH_MAX
#define TMPSIZ PATH_MAX
#else
#define TMPSIZ 1024		/* bytes to allocate for tmpnam */
#endif
#endif

typedef struct _MultiPiece {	/* Piece of the text file of BUFSIZ allocated 
				   characters */
    wchar_t* text;		/* The text in this buffer */
    XawTextPosition used;	/* The number of characters of this buffer 
				   that have been used */
    struct _MultiPiece *prev, *next;	/* linked list pointers */
} MultiPiece;

/* New fields for the MultiSrc object class */
typedef struct _MultiSrcClassPart {
    XtPointer extension;
} MultiSrcClassPart;

/* Full class record */
typedef struct _MultiSrcClassRec {
    ObjectClassPart     object_class;
    TextSrcClassPart	text_src_class;
    MultiSrcClassPart	multi_src_class;
} MultiSrcClassRec;

extern MultiSrcClassRec multiSrcClassRec;

/* New fields for the MultiSrc object */
typedef struct _MultiSrcPart {
    /* resources */
    XIC ic;			/* for X Input Method */
    XtPointer string;		/* either the string, or the file name, depend-
				   ing upon the `type'.  ALWAYS IN MB FORMAT */
    XawAsciiType type;		/* either string or disk */
    XawTextPosition piece_size;	/* Size of text buffer for each piece */
    Boolean data_compression;	/* compress to minimum memory automatically
				   on save? */
#ifdef OLDXAW
    XtCallbackList callback;
#endif
    Boolean use_string_in_place;/* Use the string passed in place */
    int multi_length;		/* length field for multi string emulation */

    /* private */

    Boolean is_tempfile;	  /* Is this a temporary file? */
#ifdef OLDXAW
    Boolean changes;
#endif
    Boolean allocated_string;	/* Have I allocated the
				   string in multi_src->string? */
    XawTextPosition length; 	/* length of file - IN CHARACTERS, NOT BYTES */
    MultiPiece *first_piece;	/* first piece of the text */
#ifndef OLDXAW
    XtPointer pad[4];	/* for future use and keep binary compatability */
#endif
} MultiSrcPart;

/* Full instance record */
typedef struct _MultiSrcRec {
  ObjectPart    object;
  TextSrcPart	text_src;
  MultiSrcPart	multi_src;
} MultiSrcRec;

_XFUNCPROTOBEGIN

void _XawMultiSourceFreeString
(
 Widget		w
 );

_XFUNCPROTOEND

#endif /* _XawMultiSrcP_h */
