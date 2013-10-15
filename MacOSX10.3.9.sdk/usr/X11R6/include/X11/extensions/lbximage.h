/* $Xorg: lbximage.h,v 1.4 2001/02/09 02:03:24 xorgcvs Exp $ */

/******************************************************************************

Copyright 1994, 1998  The Open Group

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

******************************************************************************/
/* $XFree86: xc/include/extensions/lbximage.h,v 1.4 2001/12/20 19:28:54 tsi Exp $ */

#ifndef _LBX_IMAGE_H_
#define _LBX_IMAGE_H_

#include <X11/Xfuncproto.h>

_XFUNCPROTOBEGIN

typedef struct _LbxBitmapCompMethod {

    char *methodName;
    int inited;
    int methodOpCode;	/* to be filled on reply from server */

    int (*compInit)(
#if NeedFunctionPrototypes
	void
#endif
    );

    int (*compFunc)(
#if NeedFunctionPrototypes
	unsigned char *		/* inbuf */,
	unsigned char *		/* outbuf */,
	int			/* outbufSize */,
	int			/* image_bytes */,
	int			/* pixels_per_line */,
	int			/* padded_bytes_per_scanline */,
	int			/* reverse_bits */,
	int *			/* bytesCompressed */
#endif
    );

    int (*decompFunc)(
#if NeedFunctionPrototypes
	unsigned char *		/* inbuf */,
	unsigned char *		/* outbuf */,
	int			/* image_bytes */,
	int			/* pixels_per_line */,
	int			/* padded_bytes_per_scanline */,
	int			/* reverse_bits */
#endif
    );

} LbxBitmapCompMethod;


#define LBX_MAX_DEPTHS 5

typedef struct _LbxPixmapCompMethod {

    char *methodName;
    unsigned formatMask;
    int depthCount;
    int depths[LBX_MAX_DEPTHS];
    int inited;
    int methodOpCode;	/* to be filled on reply from server */

    int (*compInit)(
#if NeedFunctionPrototypes
	void
#endif
    );

    int (*compFunc)(
#if NeedFunctionPrototypes
	char *			/* inbuf */,
	char *			/* outbuf */,
	int			/* outbufSize */,
	int			/* format */,
	int			/* depth */,
	int			/* num_scan_lines */,
	int			/* scan_line_size */,
	int *			/* bytesCompressed */
#endif
    );

    int (*decompFunc)(
#if NeedFunctionPrototypes
	char *			/* inbuf */,
	char *			/* outbuf */,
	int			/* num_scan_lines */,
	int			/* scan_line_size */
#endif
    );

} LbxPixmapCompMethod;


extern int LbxImageEncodePackBits (
#if NeedFunctionPrototypes
char *			/* inbuf */,
char *			/* outbuf */,
int			/* outbufSize */,
int			/* format */,
int			/* depth */,
int			/* num_scan_lines */,
int			/* scan_line_size */,
int *			/* bytesCompressed */
#endif
);

extern int LbxImageEncodeFaxG42D (
#if NeedFunctionPrototypes
unsigned char *		/* inbuf */,
unsigned char *		/* outbuf */,
int			/* outbufSize */,
int			/* image_bytes */,
int			/* pixels_per_line */,
int			/* padded_bytes_per_scanline */,
int			/* reverse_bits */,
int *			/* bytesCompressed */
#endif
);

extern int LbxImageDecodePackBits (
#if NeedFunctionPrototypes
char *			/* inbuf */,
char *			/* outbuf */,
int			/* num_scan_lines */,
int			/* scan_line_size */
#endif
);

extern int LbxImageDecodeFaxG42D (
#if NeedFunctionPrototypes
unsigned char *		/* inbuf */,
unsigned char *		/* outbuf */,
int			/* image_bytes */,
int			/* pixels_per_line */,
int			/* padded_bytes_per_scanline */,
int			/* reverse_bits */
#endif
);

_XFUNCPROTOEND

#define LBX_IMAGE_COMPRESS_SUCCESS		0
#define LBX_IMAGE_COMPRESS_NO_SUPPORT		1
#define LBX_IMAGE_COMPRESS_BAD_MALLOC		2
#define LBX_IMAGE_COMPRESS_NOT_WORTH_IT		3

#endif /* _LBX_IMAGE_H_ */
