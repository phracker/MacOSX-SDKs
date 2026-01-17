/* GNU C varargs support for the PowerPC with either the Apple/AIX, V.4 or Windows NT calling sequences */

#if defined(_AIX) || defined (__APPLE__)
/* AIX support */
/* Define __gnuc_va_list.  */

#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST
typedef char *__gnuc_va_list;
#endif

/* If this is for internal libc use, don't define anything but
   __gnuc_va_list.  */
#if defined (_STDARG_H) || defined (_VARARGS_H)

#ifdef _STDARG_H /* stdarg.h support */

/* Calling __builtin_next_arg gives the proper error message if LASTARG is
   not indeed the last argument.  */
#define va_start(AP, LASTARG) 						\
 (AP = ((__gnuc_va_list) __builtin_next_arg (LASTARG)))

#else /* varargs.h support */

/* In GCC version 2, we want an ellipsis at the end of the declaration
   of the argument list.  GCC version 1 can't parse it.  */

#if __GNUC__ > 1
#define __va_ellipsis ...
#else
#define __va_ellipsis
#endif

/* These macros implement traditional (non-ANSI) varargs
   for GNU C.  */

#define va_alist  __builtin_va_alist
/* The ... causes current_function_varargs to be set in cc1.  */
#define va_dcl    int __builtin_va_alist; __va_ellipsis

#define va_start(AP)  AP=(char *) &__builtin_va_alist

#endif /* _STDARG_H */

#undef va_end
void va_end (__gnuc_va_list);		/* Defined in libgcc.a */
#define va_end(AP)	((void)0)

/* We cast to void * and then to TYPE * because this avoids
   a warning about increasing the alignment requirement.  */

#define __va_rounded_size(TYPE) ((sizeof (TYPE) + 3) & ~3)
#define __va_align(AP, TYPE)						\
     ((((unsigned long)(AP)) + ((__alignof__ (TYPE) == 16) ? 15 : 3))	\
      & ~((__alignof__ (TYPE) == 16) ? 15 : 3))

#define va_arg(AP,TYPE)							\
( *(TYPE *) (void *) ((AP = (char *) (__va_align(AP, TYPE)		\
			    + __va_rounded_size(TYPE)))			\
	    - __va_rounded_size(TYPE)))

/* Copy __gnuc_va_list into another variable of this type.  */
#define __va_copy(dest, src) (dest) = (src)

#endif /* _STDARG_H */


#else
#ifndef _WIN32
/* System V.4 support */
/* Define __gnuc_va_list.  */

#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST

#ifndef _SYS_VA_LIST_H
#define _SYS_VA_LIST_H		/* Solaris sys/va_list.h */

/* Solaris decided to rename overflow_arg_area to input_arg_area,
   so handle it via a macro.  */
#define __va_overflow(AP) (AP)->overflow_arg_area

/* Note that the names in this structure are in the user's namespace, but
   that the V.4 abi explicitly states that these names should be used.  */
typedef struct __va_list_tag {
  unsigned char gpr;		/* index into the array of 8 GPRs stored in the
				   register save area gpr=0 corresponds to r3,
				   gpr=1 to r4, etc. */
  unsigned char fpr;		/* index into the array of 8 FPRs stored in the
				   register save area fpr=0 corresponds to f1,
				   fpr=1 to f2, etc. */
  char *overflow_arg_area;	/* location on stack that holds the next
				   overflow argument */
  char *reg_save_area;		/* where r3:r10 and f1:f8, if saved are stored */
} __va_list[1], __gnuc_va_list[1];

#else /* _SYS_VA_LIST */

typedef __va_list __gnuc_va_list;
#define __va_overflow(AP) (AP)->input_arg_area

#endif /* not _SYS_VA_LIST */
#endif /* not __GNUC_VA_LIST */

/* If this is for internal libc use, don't define anything but
   __gnuc_va_list.  */
#if defined (_STDARG_H) || defined (_VARARGS_H)

/* Register save area located below the frame pointer */
#ifndef __VA_PPC_H__
#define __VA_PPC_H__
typedef struct {
  long   __gp_save[8];		/* save area for GP registers */
  double __fp_save[8];		/* save area for FP registers */
} __va_regsave_t;

/* Macros to access the register save area */
/* We cast to void * and then to TYPE * because this avoids
   a warning about increasing the alignment requirement.  */
#define __VA_FP_REGSAVE(AP,OFS,TYPE)					\
  ((TYPE *) (void *) (&(((__va_regsave_t *)				\
			 (AP)->reg_save_area)->__fp_save[OFS])))

#define __VA_GP_REGSAVE(AP,OFS,TYPE)					\
  ((TYPE *) (void *) (&(((__va_regsave_t *)				\
			 (AP)->reg_save_area)->__gp_save[OFS])))

/* Common code for va_start for both varargs and stdarg.  This depends
   on the format of rs6000_args in rs6000.h.  The fields used are:

   #0	GWORDS			# words used for GP registers
   #1	FREGNO			next available FP register
   #2	NARGS_PROTOTYPE		# args left in the current prototype
   #3	ORIG_NARGS		original value of NARGS_PROTOTYPE
   #4	VARARGS_OFFSET		offset from frame pointer of varargs area */

#define __va_gwords		__builtin_args_info (0)
#define __va_fregno		__builtin_args_info (1)
#define	__va_nargs		__builtin_args_info (2)
#define __va_orig_nargs		__builtin_args_info (3)
#define __va_varargs_offset	__builtin_args_info (4)

#define __va_start_common(AP, LASTARG, FAKE)				\
__extension__ ({							\
   register int __gwords = __va_gwords - FAKE;				\
									\
   (AP)->gpr = (__gwords < 8) ? __gwords : 8;				\
   (AP)->fpr = __va_fregno - 33;					\
   (AP)->reg_save_area = (((char *) __builtin_frame_address (0))	\
			  + __va_varargs_offset);			\
   __va_overflow(AP) = __builtin_next_arg(LASTARG) - FAKE * sizeof (int); \
   (void)0;								\
})

#ifdef _STDARG_H /* stdarg.h support */

/* Calling __builtin_next_arg gives the proper error message if LASTARG is
   not indeed the last argument.  */
#define va_start(AP,LASTARG) __va_start_common (AP, LASTARG, 0)

#else /* varargs.h support */

#define va_start(AP) __va_start_common (AP, __va_1st_arg, 1)
#define va_alist __va_1st_arg
#define va_dcl register int va_alist; ...

#endif /* _STDARG_H */

#ifdef _SOFT_FLOAT
#define __va_float_p(TYPE)	0
#else
#define __va_float_p(TYPE)	(__builtin_classify_type(*(TYPE *)0) == 8)
#endif

#define __va_vector_p(TYPE)	(__builtin_classify_type(*(TYPE *)0) == -2)

#define __va_longlong_p(TYPE) \
  ((__builtin_classify_type(*(TYPE *)0) == 1) && (sizeof(TYPE) == 8))

#define __va_aggregate_p(TYPE)	(__builtin_classify_type(*(TYPE *)0) >= 12)
#define __va_size(TYPE)		((sizeof(TYPE) + sizeof (long) - 1) / sizeof (long))

/* This symbol isn't defined.  It is used to flag type promotion violations
   at link time.  We can only do this when optimizing.  Use __builtin_trap
   instead of abort so that we don't require a prototype for abort.

   __builtin_trap stuff is not available on the gcc-2.95 branch, so we just
   avoid calling it for now.  */

#ifdef __OPTIMIZE__
extern void __va_arg_type_violation(void) __attribute__((__noreturn__));
#else
#define __va_arg_type_violation()
#endif

#define va_arg(AP,TYPE)							   \
__extension__ (*({							   \
  register TYPE *__ptr;							   \
									   \
  if (__va_vector_p (TYPE))						   \
    {									   \
      __va_overflow(AP) = (char*)(((long)(__va_overflow(AP)) + 15) & ~15); \
      __ptr = (TYPE *) (void *) (__va_overflow(AP));			   \
      __va_overflow(AP) += __va_size (TYPE) * sizeof (long);		   \
    }									   \
  else									\
  if (__va_float_p (TYPE) && sizeof (TYPE) < 16)			   \
    {									   \
      unsigned char __fpr = (AP)->fpr;					   \
      if (__fpr < 8)							   \
	{								   \
	  __ptr = __VA_FP_REGSAVE (AP, __fpr, TYPE);			   \
	  (AP)->fpr = __fpr + 1;					   \
	}								   \
      else if (sizeof (TYPE) == 8)					   \
	{								   \
	  unsigned long __addr = (unsigned long) (__va_overflow (AP));	   \
	  __ptr = (TYPE *)((__addr + 7) & -8);				   \
	  __va_overflow (AP) = (char *)(__ptr + 1);			   \
	}								   \
      else								   \
	{								   \
	  /* float is promoted to double.  */				   \
	  __va_arg_type_violation ();					   \
	}								   \
    }									   \
									   \
  /* Aggregates and long doubles are passed by reference.  */		   \
  else if (__va_aggregate_p (TYPE) || __va_float_p (TYPE))		   \
    {									   \
      unsigned char __gpr = (AP)->gpr;					   \
      if (__gpr < 8)							   \
	{								   \
	  __ptr = * __VA_GP_REGSAVE (AP, __gpr, TYPE *);		   \
	  (AP)->gpr = __gpr + 1;					   \
	}								   \
      else								   \
	{								   \
	  TYPE **__pptr = (TYPE **) (__va_overflow (AP));		   \
	  __ptr = * __pptr;						   \
	  __va_overflow (AP) = (char *) (__pptr + 1);			   \
	}								   \
    }									   \
									   \
  /* Only integrals remaining.  */					   \
  else									   \
    {									   \
      /* longlong is aligned.  */					   \
      if (sizeof (TYPE) == 8)						   \
	{								   \
	  unsigned char __gpr = (AP)->gpr;				   \
	  if (__gpr < 7)						   \
	    {								   \
	      __gpr += __gpr & 1;					   \
	      __ptr = __VA_GP_REGSAVE (AP, __gpr, TYPE);		   \
	      (AP)->gpr = __gpr + 2;					   \
	    }								   \
	  else								   \
	    {								   \
	      unsigned long __addr = (unsigned long) (__va_overflow (AP)); \
	      __ptr = (TYPE *)((__addr + 7) & -8);			   \
	      (AP)->gpr = 8;						   \
	      __va_overflow (AP) = (char *)(__ptr + 1);			   \
	    }								   \
	}								   \
      else if (sizeof (TYPE) == 4)					   \
	{								   \
	  unsigned char __gpr = (AP)->gpr;				   \
	  if (__gpr < 8)						   \
	    {								   \
	      __ptr = __VA_GP_REGSAVE (AP, __gpr, TYPE);		   \
	      (AP)->gpr = __gpr + 1;					   \
	    }								   \
	  else								   \
	    {								   \
	      __ptr = (TYPE *) __va_overflow (AP);			   \
	      __va_overflow (AP) = (char *)(__ptr + 1);			   \
	    }								   \
	}								   \
      else								   \
	{								   \
	  /* Everything else was promoted to int.  */			   \
	  __va_arg_type_violation ();					   \
	}								   \
    }									   \
  __ptr;								   \
}))

#define va_end(AP)	((void)0)

/* Copy __gnuc_va_list into another variable of this type.  */
#define __va_copy(dest, src) *(dest) = *(src)

#endif /* __VA_PPC_H__ */
#endif /* defined (_STDARG_H) || defined (_VARARGS_H) */


#else
/* Windows NT */
/* Define __gnuc_va_list.  */

#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST
typedef char *__gnuc_va_list;
#endif /* not __GNUC_VA_LIST */

/* If this is for internal libc use, don't define anything but
   __gnuc_va_list.  */
#if defined (_STDARG_H) || defined (_VARARGS_H)

#define __va_start_common(AP, LASTARG, FAKE)				\
  ((__builtin_saveregs ()), ((AP) = ((char *) &LASTARG) + __va_rounded_size (AP)), 0)

#ifdef _STDARG_H /* stdarg.h support */

/* Calling __builtin_next_arg gives the proper error message if LASTARG is
   not indeed the last argument.  */
#define va_start(AP,LASTARG)						\
  (__builtin_saveregs (),						\
   (AP) = __builtin_next_arg (LASTARG),					\
   0)

#else /* varargs.h support */

#define va_start(AP)							\
  (__builtin_saveregs (),						\
   (AP) = __builtin_next_arg (__va_1st_arg) - sizeof (int),		\
   0)

#define va_alist __va_1st_arg
#define va_dcl register int __va_1st_arg; ...

#endif /* _STDARG_H */

#define __va_rounded_size(TYPE) ((sizeof (TYPE) + 3) & ~3)
#define __va_align(AP, TYPE)						\
     ((((unsigned long)(AP)) + ((sizeof (TYPE) >= 8) ? 7 : 3))		\
      & ~((sizeof (TYPE) >= 8) ? 7 : 3))

#define va_arg(AP,TYPE)							\
( *(TYPE *)((AP = (char *) (__va_align(AP, TYPE)			\
			    + __va_rounded_size(TYPE)))			\
	    - __va_rounded_size(TYPE)))

#define va_end(AP)	((void)0)

/* Copy __gnuc_va_list into another variable of this type.  */
#define __va_copy(dest, src) (dest) = (src)

#endif /* defined (_STDARG_H) || defined (_VARARGS_H) */
#endif /* Windows NT */
#endif /* not _AIX */
