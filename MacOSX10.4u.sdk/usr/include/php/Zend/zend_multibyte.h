/*
   +----------------------------------------------------------------------+
   | Zend Engine                                                          |
   +----------------------------------------------------------------------+
   | Copyright (c) 1998-2003 Zend Technologies Ltd. (http://www.zend.com) |
   +----------------------------------------------------------------------+
   | This source file is subject to version 2.00 of the Zend license,     |
   | that is bundled with this package in the file LICENSE, and is        | 
   | available through the world-wide-web at the following url:           |
   | http://www.zend.com/license/2_00.txt.                                |
   | If you did not receive a copy of the Zend license and are unable to  |
   | obtain it through the world-wide-web, please send a note to          |
   | license@zend.com so we can mail you a copy immediately.              |
   +----------------------------------------------------------------------+
   | Authors: Masaki Fujimoto <masaki-f@fides.dti.ne.jp>                  |
   |          Rui Hirokawa <hirokawa@php.net>                             |
   +----------------------------------------------------------------------+
*/

/*	$Id: zend_multibyte.h,v 1.3.2.1.8.1 2006/01/01 13:46:49 sniper Exp $ */

#ifndef ZEND_MULTIBYTE_H
#define ZEND_MULTIBYTE_H

#ifdef ZEND_MULTIBYTE

typedef int (*zend_multibyte_filter)(char **str, int *str_length, const char *buf,
		int length TSRMLS_DC);

typedef char* (*zend_encoding_detector)(const char *string, int length, char *list
		TSRMLS_DC);

typedef int (*zend_encoding_converter)(char **to, int *to_length, const char *from,
		int from_length, const char *encoding_to, const char *encoding_from 
		TSRMLS_DC);

typedef int (*zend_multibyte_oddlen)(const char *string, int length, const char 
		*encoding TSRMLS_DC);

typedef struct _zend_encoding {
	zend_multibyte_filter input_filter;		/* escape input filter */
	zend_multibyte_filter output_filter;	/* escape output filter */
	const char *name;					/* encoding name */
	const char *(*aliases)[];			/* encoding name aliases */
	int compatible;						/* we can parse without any escaping? */
} zend_encoding;


BEGIN_EXTERN_C()
ZEND_API int zend_multibyte_set_script_encoding(char *encoding_list, 
		int encoding_list_size TSRMLS_DC);

ZEND_API int zend_multibyte_set_internal_encoding(char *encoding_name, 
		int encoding_name_size TSRMLS_DC);

ZEND_API int zend_multibyte_set_functions(zend_encoding_detector
		encoding_detector, zend_encoding_converter encoding_converter,
		zend_multibyte_oddlen multibyte_oddlen TSRMLS_DC);

ZEND_API int zend_multibyte_set_filter(zend_encoding *onetime_encoding
		TSRMLS_DC);

ZEND_API zend_encoding* zend_multibyte_fetch_encoding(char *encoding_name);

ZEND_API int zend_multibyte_encoding_filter(char **to, int *to_length, const char
		*from, int from_length TSRMLS_DC);

/* in zend_language_scanner.l */
ZEND_API void zend_yyinput_again(zend_multibyte_filter old_input_filter,
		zend_encoding *old_encoding TSRMLS_DC);
ZEND_API int zend_read_file(TSRMLS_D);

/* input/output filter(s) */
int sjis_input_filter(char **buf, int *length, const char *sjis, int sjis_length
		TSRMLS_DC);
int sjis_output_filter(char **sjis, int *sjis_length, const char *buf, int length
		TSRMLS_DC);
END_EXTERN_C()

#endif /* ZEND_MULTIBYTE */

#endif /* ZEND_MULTIBYTE_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 tw=78
 * vim<600: sw=4 ts=4 tw=78
 */
