/*-
 * SPDX-License-Identifier: BSD-2-Clause-FreeBSD
 *
 * Copyright (c) 2000-2008 Poul-Henning Kamp
 * Copyright (c) 2000-2008 Dag-Erling Coïdan Smørgrav
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer
 *    in this position and unchanged.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *      $FreeBSD$
 */

#ifndef _SYS_SBUF_H_
#define	_SYS_SBUF_H_

#include <sys/_types.h>

#ifdef __APPLE__
#include <stdio.h>
#endif /* __APPLE__ */

#ifdef __APPLE__
#define sbuf usbuf
#define sbuf_drain_func usbuf_drain_func
#define sbuf_new usbuf_new
#define sbuf_new_auto usbuf_new_auto
#define sbuf_get_flags usbuf_get_flags
#define sbuf_clear_flags usbuf_clear_flags
#define sbuf_set_flags usbuf_set_flags
#define sbuf_clear usbuf_clear
#define sbuf_setpos usbuf_setpos
#define sbuf_bcat usbuf_bcat
#define sbuf_bcpy usbuf_bcpy
#define sbuf_cat usbuf_cat
#define sbuf_cpy usbuf_cpy
#define sbuf_printf usbuf_printf
#define sbuf_vprintf usbuf_vprintf
#define sbuf_nl_terminate usbuf_nl_terminate
#define sbuf_putc usbuf_putc
#define sbuf_set_drain usbuf_set_drain
#define sbuf_drain usbuf_drain
#define sbuf_trim usbuf_trim
#define sbuf_error usbuf_error
#define sbuf_finish usbuf_finish
#define sbuf_data usbuf_data
#define sbuf_len usbuf_len
#define sbuf_done usbuf_done
#define sbuf_delete usbuf_delete
#define sbuf_start_section usbuf_start_section
#define sbuf_end_section usbuf_end_section
#define sbuf_hexdump usbuf_hexdump
#define sbuf_count_drain usbuf_count_drain
#define sbuf_printf_drain usbuf_printf_drain
#define sbuf_putbuf usbuf_putbuf
#endif

struct sbuf;
typedef int (sbuf_drain_func)(void *, const char *, int);

/*
 * Structure definition
 */
struct sbuf {
	char		*s_buf;		/* storage buffer */
	sbuf_drain_func	*s_drain_func;	/* drain function */
	void		*s_drain_arg;	/* user-supplied drain argument */
	int		 s_error;	/* current error code */
	ssize_t		 s_size;	/* size of storage buffer */
	ssize_t		 s_len;		/* current length of string */
#ifdef __APPLE__
#define	USBUF_FIXEDLEN	0x00000000	/* fixed length buffer (default) */
#define	USBUF_AUTOEXTEND	0x00000001	/* automatically extend buffer */
#define	USBUF_INCLUDENUL	0x00000002	/* nulterm byte is counted in len */
#define	USBUF_DRAINTOEOR	0x00000004	/* use section 0 as drain EOR marker */
#define	USBUF_NOWAIT	0x00000008	/* Extend with non-blocking malloc */
#define	USBUF_USRFLAGMSK	0x0000ffff	/* mask of flags the user may specify */
#define	USBUF_DYNAMIC	0x00010000	/* s_buf must be freed */
#define	USBUF_FINISHED	0x00020000	/* set by sbuf_finish() */
#define	USBUF_DYNSTRUCT	0x00080000	/* sbuf must be freed */
#define	USBUF_INSECTION	0x00100000	/* set by sbuf_start_section() */
#define	USBUF_DRAINATEOL	0x00200000	/* drained contents ended in \n */
#else
#define	SBUF_FIXEDLEN	0x00000000	/* fixed length buffer (default) */
#define	SBUF_AUTOEXTEND	0x00000001	/* automatically extend buffer */
#define	SBUF_INCLUDENUL	0x00000002	/* nulterm byte is counted in len */
#define	SBUF_DRAINTOEOR	0x00000004	/* use section 0 as drain EOR marker */
#define	SBUF_NOWAIT	0x00000008	/* Extend with non-blocking malloc */
#define	SBUF_USRFLAGMSK	0x0000ffff	/* mask of flags the user may specify */
#define	SBUF_DYNAMIC	0x00010000	/* s_buf must be freed */
#define	SBUF_FINISHED	0x00020000	/* set by sbuf_finish() */
#define	SBUF_DYNSTRUCT	0x00080000	/* sbuf must be freed */
#define	SBUF_INSECTION	0x00100000	/* set by sbuf_start_section() */
#define	SBUF_DRAINATEOL	0x00200000	/* drained contents ended in \n */
#endif /* __APPLE__ */
	int		 s_flags;	/* flags */
	ssize_t		 s_sect_len;	/* current length of section */
	ssize_t		 s_rec_off;	/* current record start offset */
};

#ifndef HD_COLUMN_MASK
#define	HD_COLUMN_MASK	0xff
#define	HD_DELIM_MASK	0xff00
#define	HD_OMIT_COUNT	(1 << 16)
#define	HD_OMIT_HEX	(1 << 17)
#define	HD_OMIT_CHARS	(1 << 18)
#endif /* HD_COLUMN_MASK */

#ifdef __APPLE__
#define	SBUF_FIXEDLEN	USBUF_FIXEDLEN
#define	SBUF_AUTOEXTEND	USBUF_AUTOEXTEND
#define	SBUF_INCLUDENUL	USBUF_INCLUDENUL
#define	SBUF_DRAINTOEOR	USBUF_DRAINTOEOR
#define	SBUF_NOWAIT	USBUF_NOWAIT
#define	SBUF_USRFLAGMSK	USBUF_USRFLAGMSK
#define	SBUF_DYNAMIC	USBUF_DYNAMIC
#define	SBUF_FINISHED	USBUF_FINISHED
#define	SBUF_DYNSTRUCT	USBUF_DYNSTRUCT
#define	SBUF_INSECTION	USBUF_INSECTION
#define	SBUF_DRAINATEOL	USBUF_DRAINATEOL
#endif /* __APPLE__ */

__BEGIN_DECLS
/*
 * API functions
 */
struct sbuf	*sbuf_new(struct sbuf *, char *, int, int);
#ifdef __APPLE__
#define		 usbuf_new_auto()				\
	usbuf_new(NULL, NULL, 0, SBUF_AUTOEXTEND)
#else
#define		 sbuf_new_auto()				\
	sbuf_new(NULL, NULL, 0, SBUF_AUTOEXTEND)
#endif
int		 sbuf_get_flags(struct sbuf *);
void		 sbuf_clear_flags(struct sbuf *, int);
void		 sbuf_set_flags(struct sbuf *, int);
void		 sbuf_clear(struct sbuf *);
int		 sbuf_setpos(struct sbuf *, ssize_t);
int		 sbuf_bcat(struct sbuf *, const void *, size_t);
int		 sbuf_bcpy(struct sbuf *, const void *, size_t);
int		 sbuf_cat(struct sbuf *, const char *);
int		 sbuf_cpy(struct sbuf *, const char *);
int		 sbuf_printf(struct sbuf *, const char *, ...)
	__printflike(2, 3);
#ifdef __APPLE__
int		 sbuf_vprintf(struct sbuf *, const char *, va_list)
#else
int		 sbuf_vprintf(struct sbuf *, const char *, __va_list)
#endif
	__printflike(2, 0);
int		 sbuf_nl_terminate(struct sbuf *);
int		 sbuf_putc(struct sbuf *, int);
void		 sbuf_set_drain(struct sbuf *, sbuf_drain_func *, void *);
int		 sbuf_drain(struct sbuf *);
int		 sbuf_trim(struct sbuf *);
int		 sbuf_error(const struct sbuf *);
int		 sbuf_finish(struct sbuf *);
char		*sbuf_data(struct sbuf *);
ssize_t		 sbuf_len(struct sbuf *);
int		 sbuf_done(const struct sbuf *);
void		 sbuf_delete(struct sbuf *);
void		 sbuf_start_section(struct sbuf *, ssize_t *);
ssize_t		 sbuf_end_section(struct sbuf *, ssize_t, size_t, int);
void		 sbuf_hexdump(struct sbuf *, const void *, int, const char *,
		     int);
int		 sbuf_count_drain(void *arg, const char *data, int len);
int		 sbuf_printf_drain(void *arg, const char *data, int len);
void		 sbuf_putbuf(struct sbuf *);

#ifdef _KERNEL
struct uio;
struct sbuf	*sbuf_uionew(struct sbuf *, struct uio *, int *);
int		 sbuf_bcopyin(struct sbuf *, const void *, size_t);
int		 sbuf_copyin(struct sbuf *, const void *, size_t);
#endif
__END_DECLS

#endif
