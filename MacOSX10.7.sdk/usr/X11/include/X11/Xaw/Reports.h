/*
 *
Copyright 1990, 1998  The Open Group

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

#ifndef _Xaw_Reports_h
#define _Xaw_Reports_h

#include <X11/Intrinsic.h>

/*
 * XawPannerReport - this structure is used by the reportCallback of the
 * Panner, Porthole, Viewport, and Scrollbar widgets to report its position.
 * All fields must be filled in, although the changed field may be used as
 * a hint as to which fields have been altered since the last report.
 */
typedef struct {
    unsigned int changed;		/* mask, see below */
    Position slider_x, slider_y;	/* location of slider within outer */
    Dimension slider_width, slider_height;  /* size of slider */
    Dimension canvas_width, canvas_height;  /* size of canvas */
} XawPannerReport;

#define XawPRSliderX		(1 << 0)
#define XawPRSliderY		(1 << 1)
#define XawPRSliderWidth	(1 << 2)
#define XawPRSliderHeight	(1 << 3)
#define XawPRCanvasWidth	(1 << 4)
#define XawPRCanvasHeight	(1 << 5)
#define XawPRAll		(63)	/* union of above */

#define XtNreportCallback "reportCallback"
#define XtCReportCallback "reportCallback"

#endif /* _Xaw_Reports_h */
