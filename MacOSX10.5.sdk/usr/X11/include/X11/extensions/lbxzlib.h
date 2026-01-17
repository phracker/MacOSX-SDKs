/* $Xorg: lbxzlib.h,v 1.3 2000/08/18 04:05:45 coskrey Exp $ */
/*
 * Copyright 1993 Network Computing Devices
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of NCD. not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  NCD. makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * NCD. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL NCD.
 * BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN 
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Author:  Dale Tonogai, Network Computing Devices
 */

#ifndef _ZLIB_H_
#define _ZLIB_H_

#define ZLIB_STRCOMP_OPT	"XC-ZLIB"
#define ZLIB_STRCOMP_OPT_LEN	7

#define ZLIB_PACKET_HDRLEN	2
#define ZLIB_MAX_DATALEN	0xfff
#define ZLIB_MAX_PLAIN		270
#define ZLIB_MAX_OUTLEN		(ZLIB_MAX_PLAIN << 1)

#define ZLIB_COMPRESS_FLAG	0x80
#define ZLIB_DATALEN_MASK	0x0f

#define ZLIB_PUT_PKTHDR(p, len, compflag) \
    { \
	(p)[0] = ((unsigned)(len)) >> 8 | ((compflag) ? ZLIB_COMPRESS_FLAG : 0);\
	(p)[1] = (len) & 0xff; \
    }

#define ZLIB_GET_DATALEN(p) \
	((((unsigned)((p)[0] & ZLIB_DATALEN_MASK)) << 8) | (unsigned)(p)[1])

#define ZLIB_COMPRESSED(p) ((p)[0] & ZLIB_COMPRESS_FLAG)

struct ZlibInfo;

extern void * ZlibInit ( int fd, int level );
extern void ZlibFree ( struct ZlibInfo *comp );
extern int ZlibFlush ( int fd );
extern int ZlibStuffInput ( int fd, unsigned char *buffer, int buflen );
extern void ZlibCompressOn ( int fd );
extern void ZlibCompressOff ( int fd );
extern int ZlibWrite ( int fd, unsigned char *buffer, int buflen );
extern int ZlibWriteV ( int fd, struct iovec *iov, int iovcnt );
extern int ZlibRead ( int fd, unsigned char *buffer, int buflen );
extern int ZlibInputAvail ( int fd );


#endif /* _ZLIB_H_ */
