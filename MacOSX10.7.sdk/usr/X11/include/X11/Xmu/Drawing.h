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

/*
 * The interfaces described by this header file are for miscellaneous utilities
 * and are not part of the Xlib standard.
 */

#ifndef _XMU_DRAWING_H_
#define _XMU_DRAWING_H_

#include <X11/Xlib.h>
#include <X11/Xfuncproto.h>

#include <stdio.h>
#if ! defined(_XtIntrinsic_h) && ! defined(PIXEL_ALREADY_TYPEDEFED)
typedef unsigned long Pixel;
#endif

_XFUNCPROTOBEGIN

void XmuDrawRoundedRectangle
(
 Display		*dpy,
 Drawable	 	draw,
 GC 			gc,
 int			x,
 int			y,
 int			w,
 int			h,
 int			ew,
 int			eh
 );

void XmuFillRoundedRectangle
(
 Display		*dpy,
 Drawable 		draw,
 GC 			gc,
 int			x,
 int			y,
 int			w,
 int			h,
 int			ew,
 int			eh
 );

void XmuDrawLogo
(
 Display		*dpy,
 Drawable 		drawable,
 GC			gcFore,
 GC			gcBack,
 int			x,
 int			y,
 unsigned int		width,
 unsigned int		height
 );

Pixmap XmuCreatePixmapFromBitmap
(
 Display		*dpy,
 Drawable 		d,
 Pixmap 		bitmap,
 unsigned int		width,
 unsigned int		height,
 unsigned int		depth,
 unsigned long		fore,
 unsigned long		back
);

Pixmap XmuCreateStippledPixmap
(
 Screen			*screen,
 Pixel			fore,
 Pixel			back,
 unsigned int		depth
 );

void XmuReleaseStippledPixmap
(
 Screen			*screen,
 Pixmap 		pixmap
 );

Pixmap XmuLocateBitmapFile
(
 Screen			*screen,
 _Xconst char		*name,
 char			*srcname_return,
 int 			srcnamelen,
 int			*width_return,
 int			*height_return,
 int			*xhot_return,
 int			*yhot_return
 );

Pixmap XmuLocatePixmapFile
(
 Screen			*screen,
 _Xconst char		*name,
 unsigned long		fore,
 unsigned long		back,
 unsigned int		depth,
 char			*srcname_return,
 int 			srcnamelen,
 int			*width_return,
 int			*height_return,
 int			*xhot_return,
 int			*yhot_return
 );

int XmuReadBitmapData
(
 FILE			*fstream,
 unsigned int		*width_return,
 unsigned int		*height_return,
 unsigned char		**datap_return,
 int			*xhot_return,
 int			*yhot_return
);

int XmuReadBitmapDataFromFile
(
 _Xconst char		*filename,
 unsigned int		*width_return,
 unsigned int		*height_return,
 unsigned char		**datap_return,
 int			*xhot_return,
 int			*yhot_return
 );

_XFUNCPROTOEND

#endif /* _XMU_DRAWING_H_ */
