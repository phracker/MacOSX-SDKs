/*
 * Copyright (c) 2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _XLOCALE___WCTYPE_H_
#define _XLOCALE___WCTYPE_H_

__BEGIN_DECLS
int	iswalnum_l(wint_t, locale_t);
int	iswalpha_l(wint_t, locale_t);
int	iswcntrl_l(wint_t, locale_t);
int	iswctype_l(wint_t, wctype_t, locale_t);
int	iswdigit_l(wint_t, locale_t);
int	iswgraph_l(wint_t, locale_t);
int	iswlower_l(wint_t, locale_t);
int	iswprint_l(wint_t, locale_t);
int	iswpunct_l(wint_t, locale_t);
int	iswspace_l(wint_t, locale_t);
int	iswupper_l(wint_t, locale_t);
int	iswxdigit_l(wint_t, locale_t);
wint_t	towlower_l(wint_t, locale_t);
wint_t	towupper_l(wint_t, locale_t);
wctype_t
	wctype_l(const char *, locale_t);
__END_DECLS

#define	iswalnum_l(wc, l)		__istype_l((wc), _CTYPE_A|_CTYPE_D, (l))
#define	iswalpha_l(wc, l)		__istype_l((wc), _CTYPE_A, (l))
#define	iswcntrl_l(wc, l)		__istype_l((wc), _CTYPE_C, (l))
#define	iswctype_l(wc, charclass, l)	__istype_l((wc), (charclass), (l))
#define	iswdigit_l(wc, l)		__istype_l((wc), _CTYPE_D, (l))
#define	iswgraph_l(wc, l)		__istype_l((wc), _CTYPE_G, (l))
#define	iswlower_l(wc, l)		__istype_l((wc), _CTYPE_L, (l))
#define	iswprint_l(wc, l)		__istype_l((wc), _CTYPE_R, (l))
#define	iswpunct_l(wc, l)		__istype_l((wc), _CTYPE_P, (l))
#define	iswspace_l(wc, l)		__istype_l((wc), _CTYPE_S, (l))
#define	iswupper_l(wc, l)		__istype_l((wc), _CTYPE_U, (l))
#define	iswxdigit_l(wc, l)		__istype_l((wc), _CTYPE_X, (l))
#define	towlower_l(wc, l)		__tolower_l((wc), (l))
#define	towupper_l(wc, l)		__toupper_l((wc), (l))

#endif /* _XLOCALE___WCTYPE_H_ */
