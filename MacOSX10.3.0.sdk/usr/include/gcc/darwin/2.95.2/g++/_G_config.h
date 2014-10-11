#ifndef _G_config_h
#define _G_config_h

#include <sys/types.h>

#define _G_LIB_VERSION "2.8.0"
#define _G_NAMES_HAVE_UNDERSCORE 1
#define _G_VTABLE_LABEL_HAS_LENGTH 1
#define _G_VTABLE_LABEL_PREFIX "___vt_"
#define _G_USING_THUNKS
#define _G_VTABLE_LABEL_PREFIX_ID __vt_
#define _G_HAVE_ST_BLKSIZE 1

typedef  short  _G_int16_t;
typedef unsigned short _G_uint16_t;
typedef  int  _G_int32_t;
typedef unsigned int _G_uint32_t;

typedef  long long _G_int64_t;
typedef unsigned long long _G_uint64_t;

typedef unsigned long _G_clock_t;
typedef int _G_dev_t;
typedef int64_t _G_fpos_t;
typedef unsigned int _G_gid_t;
typedef unsigned int _G_ino_t;
typedef unsigned short _G_mode_t;
typedef unsigned short _G_nlink_t;
typedef int64_t _G_off_t;
typedef int _G_pid_t;
#ifndef __PTRDIFF_TYPE__
#define __PTRDIFF_TYPE__ int
#endif
typedef __PTRDIFF_TYPE__ _G_ptrdiff_t;
typedef unsigned int _G_sigset_t;
#ifndef __SIZE_TYPE__
#define __SIZE_TYPE__ long unsigned int
#endif
typedef __SIZE_TYPE__ _G_size_t;
typedef long _G_time_t;
typedef unsigned int _G_uid_t;
typedef int _G_wchar_t;

#define _G_BUFSIZ 1024 /* default */
#define _G_FOPEN_MAX 32 /* default */
#define _G_FILENAME_MAX 1024 /* default */
#if defined (__cplusplus) || defined (__STDC__)
#define _G_ARGS(ARGLIST) ARGLIST
#else
#define _G_ARGS(ARGLIST) ()
#endif
#if !defined (__GNUG__) || defined (__STRICT_ANSI__)
#define _G_NO_NRV
#endif
#if !defined (__GNUG__)
#define _G_NO_EXTERN_TEMPLATES
#endif
typedef int _G_ssize_t;
typedef int /* default */ _G_wint_t;
#ifdef __ppc__
#define _G_NEED_STDARG_H
#define _G_va_list __gnuc_va_list
#elif defined (__i386__)
typedef void * _G_va_list;
#else
#warning Not defining _G_va_list because target processor is unknown!
#endif
#define _G_signal_return_type void
#define _G_sprintf_return_type int
#define _G_HAVE_ATEXIT 1
#define _G_HAVE_SYS_RESOURCE 1
#define _G_HAVE_SYS_TIMES 1
#define _G_HAVE_SYS_SOCKET 1
#define _G_HAVE_SYS_CDEFS 1
#define _G_HAVE_SYS_WAIT 1
#define _G_HAVE_UNISTD 1
#define _G_HAVE_DIRENT 1
#define _G_HAVE_CURSES 1
#define _G_MATH_H_INLINES 0
#define _G_HAVE_BOOL 1
#define _G_HAVE_PRINTF_FP 0
#define _G_HAVE_LONG_DOUBLE_IO 0
#undef NULL
#define __need_NULL
#include <stddef.h>
#endif /* !_G_config_h */
