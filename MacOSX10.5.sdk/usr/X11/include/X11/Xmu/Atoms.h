/* $Xorg: Atoms.h,v 1.4 2001/02/09 02:03:51 xorgcvs Exp $ */

/* 

Copyright 1988, 1998  The Open Group

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

*/
/* $XFree86: xc/lib/Xmu/Atoms.h,v 1.6 2001/01/17 19:42:53 dawes Exp $ */

/*
 * The interfaces described by this header file are for miscellaneous utilities
 * and are not part of the Xlib standard.
 */

#ifndef _XMU_ATOMS_H_
#define _XMU_ATOMS_H_

#include <X11/Intrinsic.h>
#include <X11/Xfuncproto.h>

typedef struct _AtomRec *AtomPtr;

extern AtomPtr
    _XA_ATOM_PAIR,
    _XA_CHARACTER_POSITION,
    _XA_CLASS,
    _XA_CLIENT_WINDOW,
    _XA_CLIPBOARD,
    _XA_COMPOUND_TEXT,
    _XA_DECNET_ADDRESS,
    _XA_DELETE,
    _XA_FILENAME,
    _XA_HOSTNAME,
    _XA_IP_ADDRESS,
    _XA_LENGTH,
    _XA_LIST_LENGTH,
    _XA_NAME,
    _XA_NET_ADDRESS,
    _XA_NULL,
    _XA_OWNER_OS,
    _XA_SPAN,
    _XA_TARGETS,
    _XA_TEXT,
    _XA_TIMESTAMP,
    _XA_USER,
    _XA_UTF8_STRING;

#define XA_ATOM_PAIR(d)		XmuInternAtom(d, _XA_ATOM_PAIR)
#define XA_CHARACTER_POSITION(d) XmuInternAtom(d, _XA_CHARACTER_POSITION)
#define XA_CLASS(d)		XmuInternAtom(d, _XA_CLASS)
#define XA_CLIENT_WINDOW(d)	XmuInternAtom(d, _XA_CLIENT_WINDOW)
#define XA_CLIPBOARD(d)		XmuInternAtom(d, _XA_CLIPBOARD)
#define XA_COMPOUND_TEXT(d)	XmuInternAtom(d, _XA_COMPOUND_TEXT)
#define XA_DECNET_ADDRESS(d)	XmuInternAtom(d, _XA_DECNET_ADDRESS)
#define XA_DELETE(d)		XmuInternAtom(d, _XA_DELETE)
#define XA_FILENAME(d)		XmuInternAtom(d, _XA_FILENAME)
#define XA_HOSTNAME(d)		XmuInternAtom(d, _XA_HOSTNAME)
#define XA_IP_ADDRESS(d)	XmuInternAtom(d, _XA_IP_ADDRESS)
#define XA_LENGTH(d)		XmuInternAtom(d, _XA_LENGTH)
#define XA_LIST_LENGTH(d)	XmuInternAtom(d, _XA_LIST_LENGTH)
#define XA_NAME(d)		XmuInternAtom(d, _XA_NAME)
#define XA_NET_ADDRESS(d)	XmuInternAtom(d, _XA_NET_ADDRESS)
#define XA_NULL(d)		XmuInternAtom(d, _XA_NULL)
#define XA_OWNER_OS(d)		XmuInternAtom(d, _XA_OWNER_OS)
#define XA_SPAN(d)		XmuInternAtom(d, _XA_SPAN)
#define XA_TARGETS(d)		XmuInternAtom(d, _XA_TARGETS)
#define XA_TEXT(d)		XmuInternAtom(d, _XA_TEXT)
#define XA_TIMESTAMP(d)		XmuInternAtom(d, _XA_TIMESTAMP)
#define XA_USER(d)		XmuInternAtom(d, _XA_USER)
#define XA_UTF8_STRING(d)	XmuInternAtom(d, _XA_UTF8_STRING)

_XFUNCPROTOBEGIN

char *XmuGetAtomName
(
 Display	*dpy,
 Atom		atom
 );

Atom XmuInternAtom
(
 Display	*dpy,
 AtomPtr	atom_ptr
 );

void XmuInternStrings
(
 Display	*dpy,
 String		*names,
 Cardinal    	count,
 Atom		*atoms_return
);

AtomPtr XmuMakeAtom
(
 _Xconst char	*name
 );

char *XmuNameOfAtom
(
 AtomPtr	atom_ptr
 );

_XFUNCPROTOEND

#endif /* _XMU_ATOMS_H_ */
