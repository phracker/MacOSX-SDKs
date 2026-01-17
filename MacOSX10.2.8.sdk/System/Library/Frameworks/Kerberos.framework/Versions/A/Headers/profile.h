/*
 * This file is auto generated.
 * Please do not edit it.
 */

#ifndef _KRB5_PROFILE_H

/* Environment dependent macros */
#define SIZEOF_LONG		4
#define SIZEOF_INT		4
#define SIZEOF_SHORT	2
#define	HAVE_STDARG_H		1
#define HAVE_SYS_TYPES_H	1


/* Error tables from prof_err.h */
#define initialize_prof_error_table()
#define PROF_VERSION                             (-1429577728L)
#define PROF_MAGIC_NODE                          (-1429577727L)
#define PROF_NO_SECTION                          (-1429577726L)
#define PROF_NO_RELATION                         (-1429577725L)
#define PROF_ADD_NOT_SECTION                     (-1429577724L)
#define PROF_SECTION_WITH_VALUE                  (-1429577723L)
#define PROF_BAD_LINK_LIST                       (-1429577722L)
#define PROF_BAD_GROUP_LVL                       (-1429577721L)
#define PROF_BAD_PARENT_PTR                      (-1429577720L)
#define PROF_MAGIC_ITERATOR                      (-1429577719L)
#define PROF_SET_SECTION_VALUE                   (-1429577718L)
#define PROF_EINVAL                              (-1429577717L)
#define PROF_READ_ONLY                           (-1429577716L)
#define PROF_SECTION_NOTOP                       (-1429577715L)
#define PROF_SECTION_SYNTAX                      (-1429577714L)
#define PROF_RELATION_SYNTAX                     (-1429577713L)
#define PROF_EXTRA_CBRACE                        (-1429577712L)
#define PROF_MISSING_OBRACE                      (-1429577711L)
#define PROF_MAGIC_PROFILE                       (-1429577710L)
#define PROF_MAGIC_SECTION                       (-1429577709L)
#define PROF_TOPSECTION_ITER_NOSUPP              (-1429577708L)
#define PROF_INVALID_SECTION                     (-1429577707L)
#define PROF_END_OF_SECTIONS                     (-1429577706L)
#define PROF_BAD_NAMESET                         (-1429577705L)
#define PROF_NO_PROFILE                          (-1429577704L)
#define PROF_MAGIC_FILE                          (-1429577703L)
#define PROF_MAGIC_FILE_DATA                     (-1429577702L)
#define PROF_FAIL_OPEN                           (-1429577701L)
#define PROF_EXISTS                              (-1429577700L)
#define PROF_BAD_BOOLEAN                         (-1429577699L)
#define PROF_BAD_INTEGER                         (-1429577698L)
#define ERROR_TABLE_BASE_prof                    (-1429577728L)
/*
 * profile.h
 */

#ifndef _KRB5_PROFILE_H
#define _KRB5_PROFILE_H

#if defined(macintosh) || (defined(__MACH__) && defined(__APPLE__))
	#include <TargetConditionals.h>
    #if TARGET_RT_MAC_CFM
        #error "Use KfM 4.0 SDK headers for CFM compilation."
    #endif
#endif

#if defined(__cplusplus) && !defined(PROFILEINT_BEGIN_DECLS)
#define PROFILEINT_BEGIN_DECLS	extern "C" {
#define PROFILEINT_END_DECLS	}
#else
#define PROFILEINT_BEGIN_DECLS
#define PROFILEINT_END_DECLS
#endif

#if TARGET_OS_MAC
    #if defined(__MWERKS__)
        #pragma import on
        #pragma enumsalwaysint on
    #endif
    #pragma options align=mac68k
#endif

PROFILEINT_BEGIN_DECLS

/* We use file paths as unique file identifiers */
#if TARGET_OS_MAC
    #define COPY_RESOURCE_FORK 1
#endif

#ifndef KRB5_CALLCONV
#define KRB5_CALLCONV
#define KRB5_CALLCONV_C
#define KRB5_DLLIMP
#define GSS_DLLIMP
#define KRB5_EXPORTVAR
#define FAR
#define NEAR
#endif

typedef struct _profile_t *profile_t;

/*
 * Used by the profile iterator in prof_get.c
 */
#define PROFILE_ITER_LIST_SECTION	0x0001
#define PROFILE_ITER_SECTIONS_ONLY	0x0002
#define PROFILE_ITER_RELATIONS_ONLY	0x0004

typedef char* profile_filespec_t;	/* path as C string */
typedef char* profile_filespec_list_t;	/* list of : separated paths, C string */
typedef const char* const_profile_filespec_t;	/* path as C string */
typedef const char* const_profile_filespec_list_t;	/* list of : separated paths, C string */

#if !defined(PROTOTYPE)
#if defined(__STDC__) || defined(__cplusplus) || defined(_MSDOS) || defined(_WIN32)
#define PROTOTYPE(x) x
#else
#define PROTOTYPE(x) ()
#endif
#endif

KRB5_DLLIMP long KRB5_CALLCONV profile_init
	PROTOTYPE ((const_profile_filespec_t *files, profile_t *ret_profile));

KRB5_DLLIMP long KRB5_CALLCONV profile_init_path
	PROTOTYPE ((const_profile_filespec_list_t filelist, profile_t *ret_profile));

/* On Mac Carbon, also provide FSSpec variants */
#if TARGET_OS_MAC && defined(__FILES__)
KRB5_DLLIMP long KRB5_CALLCONV FSp_profile_init
	PROTOTYPE ((const FSSpec* files, profile_t *ret_profile));

KRB5_DLLIMP long KRB5_CALLCONV FSp_profile_init_path
	PROTOTYPE ((const FSSpec* files, profile_t *ret_profile));
#endif

KRB5_DLLIMP long KRB5_CALLCONV profile_flush
	PROTOTYPE ((profile_t profile));

KRB5_DLLIMP void KRB5_CALLCONV profile_abandon
	PROTOTYPE ((profile_t profile));

KRB5_DLLIMP void KRB5_CALLCONV profile_release
	PROTOTYPE ((profile_t profile));

KRB5_DLLIMP long KRB5_CALLCONV profile_get_values
	PROTOTYPE ((profile_t profile, const char **names, char ***ret_values));

KRB5_DLLIMP void KRB5_CALLCONV profile_free_list
	PROTOTYPE ((char **list));

KRB5_DLLIMP long KRB5_CALLCONV profile_get_string
	PROTOTYPE((profile_t profile, const char *name, const char *subname, 
			const char *subsubname, const char *def_val,
			char **ret_string));
KRB5_DLLIMP long KRB5_CALLCONV profile_get_integer
	PROTOTYPE((profile_t profile, const char *name, const char *subname,
			const char *subsubname, int def_val,
			int *ret_default));

KRB5_DLLIMP long KRB5_CALLCONV profile_get_boolean
	PROTOTYPE((profile_t profile, const char *name, const char *subname,
			const char *subsubname, int def_val,
			int *ret_default));

KRB5_DLLIMP long KRB5_CALLCONV profile_get_relation_names
	PROTOTYPE((profile_t profile, const char **names, char ***ret_names));

KRB5_DLLIMP long KRB5_CALLCONV profile_get_subsection_names
	PROTOTYPE((profile_t profile, const char **names, char ***ret_names));

KRB5_DLLIMP long KRB5_CALLCONV profile_iterator_create
	PROTOTYPE((profile_t profile, const char **names,
		   int flags, void **ret_iter));

KRB5_DLLIMP void KRB5_CALLCONV profile_iterator_free
	PROTOTYPE((void **iter_p));
	
KRB5_DLLIMP long KRB5_CALLCONV profile_iterator
	PROTOTYPE((void	**iter_p, char **ret_name, char **ret_value));

KRB5_DLLIMP void KRB5_CALLCONV profile_release_string PROTOTYPE((char *str));

KRB5_DLLIMP long KRB5_CALLCONV profile_update_relation
	PROTOTYPE((profile_t profile, const char **names, 
		   const char *old_value, const char *new_value));

KRB5_DLLIMP long KRB5_CALLCONV profile_clear_relation
	PROTOTYPE((profile_t profile, const char **names));

KRB5_DLLIMP long KRB5_CALLCONV profile_rename_section
	PROTOTYPE((profile_t profile, const char **names, 
		   const char *new_name));

KRB5_DLLIMP long KRB5_CALLCONV profile_add_relation
	PROTOTYPE((profile_t profile, const char **names, 
		   const char *new_value));

#if TARGET_OS_MAC
    #if defined(__MWERKS__)
        #pragma enumsalwaysint reset
        #pragma import reset
    #endif
	#pragma options align=reset
#endif

PROFILEINT_END_DECLS

#endif /* _KRB5_PROFILE_H */
#endif /* _KRB5_PROFILE_H  */
