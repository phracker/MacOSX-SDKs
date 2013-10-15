/*
* $Xorg: AsciiSrcP.h,v 1.4 2001/02/09 02:03:42 xorgcvs Exp $
*/


/***********************************************************

Copyright 1987, 1988, 1994, 1998  The Open Group

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
/* $XFree86: xc/lib/Xaw/AsciiSrcP.h,v 1.8 2001/01/17 19:42:25 dawes Exp $ */

/*
 * AsciiSrcP.h - Private Header for Ascii Text Source.
 *
 * This is the private header file for the Ascii Text Source.
 * It is intended to be used with the Text widget, the simplest way to use
 * this text source is to use the AsciiText Object.
 *
 * Date:    June 29, 1989
 *
 * By:      Chris D. Peterson
 *          MIT X Consortium 
 *          kit@expo.lcs.mit.edu
 */

#ifndef _XawAsciiSrcP_h
#define _XawAsciiSrcP_h

#include <X11/Xaw/TextSrcP.h>
#include <X11/Xaw/AsciiSrc.h>

#ifdef L_tmpnam
#define TMPSIZ L_tmpnam
#else
#ifdef PATH_MAX
#define TMPSIZ PATH_MAX
#else
#define TMPSIZ 1024		/* bytes to allocate for tmpnam */
#endif
#endif

typedef struct _Piece {		/* Piece of the text file of BUFSIZ allocated 
				   characters */
    char *text;			/* The text in this buffer */
    XawTextPosition used;	/* The number of characters of this buffer 
				   that have been used */
    struct _Piece *prev, *next;	/* linked list pointers */
} Piece;

typedef struct _AsciiSrcClassPart {
    XtPointer extension;
} AsciiSrcClassPart;

/* Full class record */
typedef struct _AsciiSrcClassRec {
    ObjectClassPart     object_class;
    TextSrcClassPart	text_src_class;
    AsciiSrcClassPart	ascii_src_class;
} AsciiSrcClassRec;

extern AsciiSrcClassRec asciiSrcClassRec;

/* New fields for the AsciiSrc object */
typedef struct _AsciiSrcPart {
    /* resources */
    char *string;		/* either the string, or the
				   file name, depending upon the type */
    XawAsciiType type;		/* either string or disk */
    XawTextPosition piece_size;	/* Size of text buffer for each piece */
    Boolean data_compression;	/* compress to minimum memory automatically
				   on save? */
#ifdef OLDXAW
    XtCallbackList callback;
#endif
    Boolean use_string_in_place;/* Use the string passed in place */
    int ascii_length;		/* length field for ascii string emulation */

#ifdef ASCII_DISK
    String filename;		/* name of file for Compatability */
#endif /* ASCII_DISK */

    /* private */
    Boolean is_tempfile;	/* Is this a temporary file? */
#ifdef OLDXAW
    Boolean changes;
#endif
    Boolean allocated_string;	/* Have I allocated the
				   string in ascii_src->string? */
    XawTextPosition length; 	/* length of file */
    Piece *first_piece;		/* first piece of the text */
#ifndef OLDXAW
    XtPointer pad[4];	/* for future use and keep binary compatability */
#endif
} AsciiSrcPart;

/* instance record */
typedef struct _AsciiSrcRec {
    ObjectPart    object;
    TextSrcPart   text_src;
    AsciiSrcPart  ascii_src;
} AsciiSrcRec;

#endif /* _XawAsciiSrcP_h */ 
