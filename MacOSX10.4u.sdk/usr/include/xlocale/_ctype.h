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

#ifndef _XLOCALE__CTYPE_H_
#define _XLOCALE__CTYPE_H_

__BEGIN_DECLS
int     digittoint_l(int, locale_t);
int     isalnum_l(int, locale_t);
int     isalpha_l(int, locale_t);
int     isblank_l(int, locale_t);
int     iscntrl_l(int, locale_t);
int     isdigit_l(int, locale_t);
int     isgraph_l(int, locale_t);
int     ishexnumber_l(int, locale_t);
int     isideogram_l(int, locale_t);
int     islower_l(int, locale_t);
int     isnumber_l(int, locale_t);
int     isphonogram_l(int, locale_t);
int     isprint_l(int, locale_t);
int     ispunct_l(int, locale_t);
int     isrune_l(int, locale_t);
int     isspace_l(int, locale_t);
int     isspecial_l(int, locale_t);
int     isupper_l(int, locale_t);
int     isxdigit_l(int, locale_t);
int     tolower_l(int, locale_t);
int     toupper_l(int, locale_t);
__END_DECLS

#define	digittoint_l(c, l)	__maskrune_l((c), 0xFF, (l))
#define	ishexnumber_l(c, l)	__istype_l((c), _CTYPE_X, (l))
#define	isideogram_l(c, l)	__istype_l((c), _CTYPE_I, (l))
#define	isnumber_l(c, l)	__istype_l((c), _CTYPE_D, (l))
#define	isphonogram_l(c, l)	__istype_l((c), _CTYPE_Q, (l))
#define	isrune_l(c, l)		__istype_l((c),  0xFFFFFF00L, (l))
#define	isspecial_l(c, l)	__istype_l((c), _CTYPE_T, (l))
#define isalnum_l(c, l)		__istype_l((c), (_CTYPE_A|_CTYPE_D), (l))
#define isalpha_l(c, l)		__istype_l((c), _CTYPE_A, (l))
#define isblank_l(c, l)		__istype_l((c), _CTYPE_B, (l))
#define iscntrl_l(c, l)		__istype_l((c), _CTYPE_C, (l))
#define isdigit_l(c, l)		__istype_l((c), _CTYPE_D, (l))
#define isgraph_l(c, l)		__istype_l((c), _CTYPE_G, (l))
#define islower_l(c, l)		__istype_l((c), _CTYPE_L, (l))
#define isprint_l(c, l)		__istype_l((c), _CTYPE_R, (l))
#define ispunct_l(c, l)		__istype_l((c), _CTYPE_P, (l))
#define isspace_l(c, l)		__istype_l((c), _CTYPE_S, (l))
#define isupper_l(c, l)		__istype_l((c), _CTYPE_U, (l))
#define isxdigit_l(c, l)	__istype_l((c), _CTYPE_X, (l))
#define tolower_l(c, l)		__tolower_l(c, (l))
#define toupper_l(c, l)		__toupper_l(c, (l))

/* See comments in <machine/_type.h> about __darwin_ct_rune_t. */
__BEGIN_DECLS
unsigned long		___runetype_l(__darwin_ct_rune_t, locale_t);
__darwin_ct_rune_t	___tolower_l(__darwin_ct_rune_t, locale_t);
__darwin_ct_rune_t	___toupper_l(__darwin_ct_rune_t, locale_t);
__END_DECLS

/*
 * Use inline functions if we are allowed to and the compiler supports them.
 */
#if !defined(_DONT_USE_CTYPE_INLINE_) && \
    (defined(_USE_CTYPE_INLINE_) || defined(__GNUC__) || defined(__cplusplus))

__BEGIN_DECLS
int             	__maskrune_l(__darwin_ct_rune_t, unsigned long, locale_t);
__END_DECLS

static __inline int
__istype_l(__darwin_ct_rune_t _c, unsigned long _f, locale_t _l)
{
	return !!(isascii(_c) ? (_DefaultRuneLocale.__runetype[_c] & _f)
		: __maskrune_l(_c, _f, _l));
}

static __inline __darwin_ct_rune_t
__toupper_l(__darwin_ct_rune_t _c, locale_t _l)
{
	return isascii(_c) ? _DefaultRuneLocale.__mapupper[_c]
		: ___toupper_l(_c, _l);
}

static __inline __darwin_ct_rune_t
__tolower_l(__darwin_ct_rune_t _c, locale_t _l)
{
	return isascii(_c) ? _DefaultRuneLocale.__maplower[_c]
		: ___tolower_l(_c, _l);
}

static __inline int
__wcwidth_l(__darwin_ct_rune_t _c, locale_t _l)
{
	unsigned int _x;

	if (_c == 0)
		return (0);
	_x = (unsigned int)__maskrune_l(_c, _CTYPE_SWM|_CTYPE_R, _l);
	if ((_x & _CTYPE_SWM) != 0)
		return ((_x & _CTYPE_SWM) >> _CTYPE_SWS);
	return ((_x & _CTYPE_R) != 0 ? 1 : -1);
}

#else /* not using inlines */

__BEGIN_DECLS
int             	__maskrune_l(__darwin_ct_rune_t, unsigned long, locale_t);   
int			__istype_l(__darwin_ct_rune_t, unsigned long, locale_t);
__darwin_ct_rune_t	__toupper_l(__darwin_ct_rune_t, locale_t);
__darwin_ct_rune_t	__tolower_l(__darwin_ct_rune_t, locale_t);
int             	__wcwidth_l(__darwin_ct_rune_t, locale_t);   
__END_DECLS
#endif /* using inlines */

#endif /* _XLOCALE__CTYPE_H_ */
