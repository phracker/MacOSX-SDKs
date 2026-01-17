/* $Xorg: lbxbufstr.h,v 1.3 2000/08/18 04:05:45 coskrey Exp $ */
/*
 * Copyright 1988, 1989, 1990, 1994 Network Computing Devices, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation for any purpose is hereby granted without fee, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name Network Computing Devices, Inc. not be
 * used in advertising or publicity pertaining to distribution of this 
 * software without specific, written prior permission.
 * 
 * THIS SOFTWARE IS PROVIDED `AS-IS'.  NETWORK COMPUTING DEVICES, INC.,
 * DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING WITHOUT
 * LIMITATION ALL IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, OR NONINFRINGEMENT.  IN NO EVENT SHALL NETWORK
 * COMPUTING DEVICES, INC., BE LIABLE FOR ANY DAMAGES WHATSOEVER, INCLUDING
 * SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES, INCLUDING LOSS OF USE,
 * DATA, OR PROFITS, EVEN IF ADVISED OF THE POSSIBILITY THEREOF, AND
 * REGARDLESS OF WHETHER IN AN ACTION IN CONTRACT, TORT OR NEGLIGENCE,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 * 
 */
/* $XFree86$ */

#ifndef _BUFFERSTR_H_
#define _BUFFERSTR_H_

#include <X11/extensions/lbxbuf.h>

/*
 * ZLIB Input/Output buffer
 */
typedef struct _zlibbuffer {
	char 	*bufbase;
	char	*bufend;
	char	*bufptr;
	int  	bufcnt;
} ZlibBuffer;

#define BYTES_AVAIL(inbuf, len)	\
	(((inbuf)->bufcnt >= (len)) ? (inbuf)->bufptr : NULL)

#endif	/* _BUFFERSTR_H_ */
